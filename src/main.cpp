#include <iostream>
#include <vector>
#include "Blockchain.h"
#include "Wallet.h"

int main() {
    Blockchain ledger;
    std::vector<Wallet*> accountList;

    Wallet aliceWallet("Alice");
    Wallet bobWallet("Bob");
    Wallet charlieWallet("Charlie");

    aliceWallet.balance = 100;
    bobWallet.balance = 100;
    charlieWallet.balance = 0;

    accountList.push_back(&aliceWallet);
    accountList.push_back(&bobWallet);
    accountList.push_back(&charlieWallet);

    Transaction paymentOne = aliceWallet.sendFunds(bobWallet, 50);
    Transaction paymentTwo = bobWallet.sendFunds(charlieWallet, 30);

    ledger.createTransaction(paymentOne);
    ledger.createTransaction(paymentTwo);

    ledger.minePendingTransactions();

    ledger.notifyWallets(accountList);

    if (ledger.isChainValid()) {
        std::cout << "Blockchain is valid.\n";
    } else {
        std::cout << "Blockchain is not valid!\n";
    }

    ledger.printChain();

    for (const auto& account : accountList) {
        std::cout << "Wallet " << account->id << " has balance: " << account->balance << std::endl;
    }

    return 0;
}
