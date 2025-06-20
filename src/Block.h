#pragma once
#include <string>
#include <vector>
#include <ctime>
#include "Transaction.h"

class Block {
public:
    std::string prev;
    std::string hash;
    std::vector<Transaction> txs;
    std::time_t timeStamp;
    int nonce;
    int diff;

    Block(std::vector<Transaction> txs, std::string prev, int diff);

    std::string mine();
    std::string calcHash() const;
    std::string sha256(const std::string data) const;
};
