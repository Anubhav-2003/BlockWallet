#pragma once
#include <vector>
#include <unordered_map>
#include "Block.h"
#include "Transaction.h"
#include "Wallet.h"

class Blockchain {
private:
    std::vector<Block> blockChain;
    std::vector<Transaction> transactionPool;
    std::unordered_map<std::string, RSA*> keyDirectory; 

public:
    Blockchain();

    void addTransaction(Transaction newTransaction);

    void minePendingTransactions();

    bool verifyBlockHash(const Block& currentBlock);

    bool verifyTransaction(const Transaction& transaction);

    bool verifyBlockchain();

    void displayBlockchain();

    void updateWallets(std::vector<Wallet*>& walletList);
};
