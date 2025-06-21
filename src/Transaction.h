#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <openssl/rsa.h>

class Transaction {
public:
    std::string from;
    std::string to;
    float value;
    std::string sig;
    int nonce;
    unsigned int sigLen;

    Transaction(std::string from, std::string to, float value, int nonce);
    void sign(RSA* privKey);
    bool verify(RSA* pubKey) const;
    bool isValid(RSA* pubKey) const;
};

#endif
