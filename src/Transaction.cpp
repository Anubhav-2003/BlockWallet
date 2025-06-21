#include "Transaction.h"
#include <openssl/sha.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <iostream>
#include <iomanip>

Transaction::Transaction(std::string from, std::string to, float value, int nonce)
    : from(from), to(to), value(value), nonce(nonce) {}

void Transaction::sign(RSA* privKey) {
    std::string data = from + to + std::to_string(value) + std::to_string(nonce);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);

    unsigned char sigBuf[RSA_size(privKey)];
    unsigned int sigLenLocal;

    if (RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, sigBuf, &sigLenLocal, privKey) != 1) {
        std::cout << "Sign failed\n";
        return;
    }

    sig.assign(reinterpret_cast<char*>(sigBuf), sigLenLocal);
    sigLen = sigLenLocal;
    std::cout << "Sign OK. Length: " << sigLen << "\n";
}

bool Transaction::verify(RSA* pubKey) const {
    ERR_clear_error();

    std::string data = from + to + std::to_string(value) + std::to_string(nonce);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);

    int ok = RSA_verify(NID_sha256, hash, SHA256_DIGEST_LENGTH,
                        reinterpret_cast<const unsigned char*>(sig.data()), sigLen, pubKey);
    if (ok != 1) {
        unsigned long err = ERR_get_error();
        char* errStr = ERR_error_string(err, NULL);
        std::cout << "Verify failed: " << errStr << "\n";
        return false;
    }
    std::cout << "Verify OK\n";
    return true;
}

bool Transaction::isValid(RSA* pubKey) const {
    if (nonce < 0 || value <= 0) {
        return false;
    }
    return verify(pubKey);
}
