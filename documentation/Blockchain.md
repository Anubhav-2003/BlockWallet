# Blockchain.cpp README

## Overview
This file contains the implementation of the `Blockchain` class, which is responsible for creating and managing a blockchain.

## Class Methods

### Constructor

- `Blockchain()`: Initializes a new blockchain with the Genesis Block. The Genesis Block is the first block in the chain and is initialized with an empty list of transactions and a previous hash of `"0"`.

---

### Transaction Methods

- `void addTx(Transaction tx)`: Adds a new transaction to the list of pending transactions.

- `void minePending()`: Mines all pending transactions into a new block and appends it to the blockchain. Clears the list of pending transactions after mining.

---

### Validation Methods

- `bool validBlock(const Block& blk)`: Validates a block's hash by checking if the block's `hash` matches its computed hash.

- `bool validTx(const Transaction& tx)`: Validates a transaction by ensuring its `value` is greater than 0 and that its signature is valid.

- `bool validChain()`: Validates the entire blockchain by:
  - Checking each block's hash.
  - Confirming that each block's `prev` matches the hash of the previous block.
  - Verifying all transactions in every block.

---

### Display Method

- `void print()`: Displays the contents of the blockchain. For each block, it prints its `timeStamp`, `prev`, `hash`, transactions, and `nonce`.

---

### Notification Method

- `void updateWallets(std::vector<Wallet*>& wallets)`: Updates all wallets with new transactions and balances. It updates the public key map and iterates over each wallet to adjust its balance based on the transactions present in the blockchain.

---

## Dependencies

- `Block.h`: Defines the `Block` class for each block in the blockchain.
- `Transaction.h`: Defines the `Transaction` class for creating transactions.
- `Wallet.h`: Defines the `Wallet` class for signing transactions and tracking balances.

---

## Usage

Here’s a basic example of how to use the `Blockchain` class:
```cpp
#include "Blockchain.h"
#include "Wallet.h"

int main() {
    Blockchain bc;

    Wallet w1("Alice");
    Wallet w2("Bob");

    w1.bal = 100.0f;
    w2.bal = 50.0f;

    Transaction t1 = w1.sendFunds(w2, 20.0f);
    Transaction t2 = w2.sendFunds(w1, 10.0f);

    bc.addTx(t1);
    bc.addTx(t2);

    bc.minePending();

    std::vector<Wallet*> wallets = {&w1, &w2};
    bc.updateWallets(wallets);

    bc.print();

    return 0;
}
```
In this example, two wallets are created, and two transactions are created and signed by the respective wallets. The transactions are added to the blockchain, and then the pending transactions are mined into a new block. Finally, the wallets are notified with updated transactions and balances, and the entire blockchain is printed.

## Note
This README assumes that a `Transaction` class exists and is used for the `transactions` vector. The `Transaction` class should have members like `sender`, `receiver`, and `amount`.
  
## Authors
- Anubhav Banerjee