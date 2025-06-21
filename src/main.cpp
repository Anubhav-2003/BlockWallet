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

    aliceWallet.bal = 100;
    bobWallet.bal = 100;
    charlieWallet.bal = 0;

    accountList.push_back(&aliceWallet);
    accountList.push_back(&bobWallet);
    accountList.push_back(&charlieWallet);

    Transaction paymentOne = aliceWallet.sendFunds(bobWallet, 50);
    Transaction paymentTwo = bobWallet.sendFunds(charlieWallet, 30);

    ledger.addTransaction(paymentOne);
    ledger.addTransaction(paymentTwo);

    ledger.minePendingTransactions();

    ledger.updateWallets(accountList);

    if (ledger.verifyBlockchain()) {
        std::cout << "Blockchain is valid.\n";
    } else {
        std::cout << "Blockchain is not valid!\n";
    }

    ledger.displayBlockchain();

    for (const auto& account : accountList) {
        std::cout << "Wallet " << account->name << " has balance: " << account->bal << std::endl;
    }

    return 0;
}
