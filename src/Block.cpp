#include "Block.h"
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

Block::Block(std::vector<Transaction> txs, std::string prev, int diff) {
    this->txs = txs;
    this->prev = prev;
    this->timeStamp = std::time(nullptr);
    this->diff = diff;
    this->nonce = 0;
    this->hash = mine();
}

std::string Block::mine() {
    std::string target(diff, '0');
    while (hash.substr(0, diff) != target) {
        nonce++;
        hash = calcHash();
    }
    return hash;
}

std::string Block::calcHash() const {
    std::stringstream ss;
    ss << std::put_time(std::gmtime(&timeStamp), "%Y-%m-%dT%H:%M:%S");
    for (const auto &t : txs) {
        ss << t.from << t.to << t.value;
    }
    ss << prev << nonce;
    return sha256(ss.str());
}

std::string Block::sha256(const std::string data) const {
    unsigned char h[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, data.c_str(), data.size());
    SHA256_Final(h, &ctx);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)h[i];
    }
    return ss.str();
}
