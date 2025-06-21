# README for Transaction.cpp

This file contains the implementation of the `Transaction` class, which is used for creating and managing transactions within a blockchain.

## Class Methods

### Constructor

- `Transaction::Transaction(std::string from, std::string to, float value, int nonce)`: Initializes a new transaction with sender, receiver, amount of transaction, and a nonce.

### Signing Method

- `void sign(RSA* privateKey)`: Signs the transaction using the RSA private key. It creates a SHA-256 hash of the transaction data and then signs it. The signature and its length are stored as member variables of the class.

### Verification Methods

- `bool verify(RSA* pubKey) const`: Verifies the transaction's signature using the RSA public key. It creates a SHA-256 hash of the transaction data and then verifies the stored signature.

- `bool isValid(RSA* pubKey) const`: Checks the overall validity of the transaction, which includes verifying the signature and ensuring that the amount is greater than zero and the nonce is non-negative.

### Debugging Method

- `void debugPrintHash(unsigned char* hash, size_t len)`: Prints the hash in hexadecimal format for debugging purposes.

## Dependencies

- `Transaction.h`: The `Transaction` class is defined in this header file.
- OpenSSL: This is used for cryptographic functions, specifically SHA-256 for hashing and RSA for signing and verifying.

## Example Usage

```cpp
#include "Transaction.h"
#include <openssl/rsa.h>
#include <iostream>

int main() {
    RSA* senderKey = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    RSA* receiverKey = RSA_generate_key(2048, RSA_F4, NULL, NULL);

    Transaction tx("alice", "bob", 100.0, 1);

    tx.sign(senderKey);

    if (tx.isValid(senderKey)) {
        std::cout << "Transaction is valid.\n";
    } else {
        std::cout << "Transaction is invalid.\n";
    }

    RSA_free(senderKey);
    RSA_free(receiverKey);

    return 0;
}
```

In this example, RSA key pairs are generated for the sender and the receiver. A transaction is then initialized, signed, and verified.

## Note
This README assumes that a `Transaction` class exists and is used for the `transactions` vector. The `Transaction` class should have members like `sender`, `receiver`, and `amount`.
  
## Authors
- Anubhav Banerjee