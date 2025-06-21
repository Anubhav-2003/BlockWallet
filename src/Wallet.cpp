#include "Wallet.h"
#include <iostream>
#include <openssl/rand.h>
#include <openssl/pem.h>

Wallet::Wallet(std::string name) : name(name), bal(0.0f), pubKey(nullptr), privKey(nullptr) {
    genKeys();
}

Wallet::~Wallet() {
    if (privKey) {
        RSA_free(privKey);
        privKey = nullptr;
    }
    if (pubKey) {
        RSA_free(pubKey);
        pubKey = nullptr;
    }
}

void Wallet::genKeys() {
    privKey = RSA_new();
    BIGNUM* exp = BN_new();
    BN_set_word(exp, RSA_F4);
    RSA_generate_key_ex(privKey, 2048, exp, nullptr);

    pubKey = RSA_new();
    RSA_set0_key(pubKey, BN_dup(RSA_get0_n(privKey)), BN_dup(exp), nullptr);
    BN_free(exp);

    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bio, pubKey);
    size_t len = BIO_pending(bio);
    char* pubStr = (char*)malloc(len + 1);
    BIO_read(bio, pubStr, len);
    pubStr[len] = 0;
    BIO_free_all(bio);
    free(pubStr);
}

Transaction Wallet::sendFunds(Wallet& dest, float value) {
    int nonce = 12345;
    Transaction tx(name, dest.name, value, nonce);
    tx.sign(privKey);
    return tx;
}

void Wallet::updateBalance(const std::vector<Transaction>& txs) {
    for (const auto& tx : txs) {
        if (tx.from == name) {
            bal -= tx.value;
        }
        if (tx.to == name) {
            bal += tx.value;
        }
    }
}

void Wallet::printWalletData() const {
    std::cout << "Wallet ID: " << name << std::endl;
    std::cout << "Balance: " << bal << std::endl;
    std::cout << "Public Key: " << pubKey << std::endl;
}
