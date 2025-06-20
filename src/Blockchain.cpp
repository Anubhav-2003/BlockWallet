#include "Blockchain.h"
#include "Wallet.h"
#include <iostream>

Blockchain::Blockchain() {
    std::vector<Transaction> emptyTransactionList;
    blockChain.emplace_back(emptyTransactionList, "0", 2);
}

void Blockchain::addTransaction(Transaction newTransaction) {
    transactionPool.push_back(newTransaction);
}

void Blockchain::minePendingTransactions() {
    Block minedBlock(transactionPool, blockChain.back().blockHash, 2);
    blockChain.push_back(minedBlock);
    transactionPool.clear();
}

bool Blockchain::verifyBlockHash(const Block& currentBlock) {
    return currentBlock.blockHash == currentBlock.generateHash();
}

bool Blockchain::verifyTransaction(const Transaction& transaction) {
    return transaction.amount > 0;
}

bool Blockchain::verifyBlockchain() {
    for (int i = 1; i < blockChain.size(); ++i) {
        Block currentBlock = blockChain[i];
        Block previousBlock = blockChain[i - 1];

        if (!verifyBlockHash(currentBlock)) {
            return false;
        }

        if (currentBlock.prevHash != previousBlock.blockHash) {
            return false;
        }

        for (const auto& transaction : currentBlock.transactions) {
            RSA* senderKey = keyDirectory[transaction.sender];
            if (!transaction.isValid(senderKey)) {
                return false;
            }
        }
    }
    return true;
}

void Blockchain::displayBlockchain() {
    for (const auto& block : blockChain) {
        std::cout << "Block Timestamp: " << block.timestamp << std::endl;
        std::cout << "Previous Hash: " << block.prevHash << std::endl;
        std::cout << "Block Hash: " << block.blockHash << std::endl;
        std::cout << "Transactions:" << std::endl;
        for (const auto& transaction : block.transactions) {
            std::cout << "  Sender: " << transaction.sender
                      << " Receiver: " << transaction.receiver
                      << " Amount: " << transaction.amount << std::endl;
        }
        std::cout << "Nonce: " << block.nonce << std::endl << std::endl;
    }
}

void Blockchain::updateWallets(std::vector<Wallet*>& walletList) {
    for (auto& wallet : walletList) {
        keyDirectory[wallet->id] = wallet->publicKey;
        for (auto& block : blockChain) {
            wallet->updateBalance(block.transactions);
        }
    }
}
