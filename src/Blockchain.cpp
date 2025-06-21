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
    Block minedBlock(transactionPool, blockChain.back().hash, 2);
    blockChain.push_back(minedBlock);
    transactionPool.clear();
}

bool Blockchain::verifyBlockHash(const Block& currentBlock) {
    return currentBlock.hash == currentBlock.calcHash();
}

bool Blockchain::verifyTransaction(const Transaction& transaction) {
    return transaction.value > 0;
}

bool Blockchain::verifyBlockchain() {
    for (int i = 1; i < blockChain.size(); ++i) {
        Block currentBlock = blockChain[i];
        Block previousBlock = blockChain[i - 1];

        if (!verifyBlockHash(currentBlock)) {
            return false;
        }

        if (currentBlock.prev != previousBlock.hash) {
            return false;
        }

        for (const auto& transaction : currentBlock.txs) {
            RSA* senderKey = keyDirectory[transaction.from];
            if (!transaction.isValid(senderKey)) {
                return false;
            }
        }
    }
    return true;
}

void Blockchain::displayBlockchain() {
    for (const auto& block : blockChain) {
        std::cout << "Block Timestamp: " << block.timeStamp << std::endl;
        std::cout << "Previous Hash: " << block.prev << std::endl;
        std::cout << "Block Hash: " << block.hash << std::endl;
        std::cout << "Transactions:" << std::endl;
        for (const auto& transaction : block.txs) {
            std::cout << "  Sender: " << transaction.from
                      << " Receiver: " << transaction.to
                      << " Amount: " << transaction.value << std::endl;
        }
        std::cout << "Nonce: " << block.nonce << std::endl << std::endl;
    }
}

void Blockchain::updateWallets(std::vector<Wallet*>& walletList) {
    for (auto& wallet : walletList) {
        keyDirectory[wallet->name] = wallet->pubKey;
        for (auto& block : blockChain) {
            wallet->updateBalance(block.txs);
        }
    }
}
