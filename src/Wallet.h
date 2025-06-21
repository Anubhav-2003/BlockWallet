#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>
#include <openssl/rsa.h>
#include "Transaction.h"

class Wallet {
public:
    Wallet(std::string name);
    ~Wallet();

    Transaction sendFunds(Wallet& dest, float value);
    void updateBalance(const std::vector<Transaction>& txs);
    void printWalletData() const;

    std::string name;
    float bal;
    RSA* pubKey;

private:
    RSA* privKey;
    void genKeys();
};

#endif
