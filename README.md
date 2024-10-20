# Cryptography Algorithms & Key Store

## Overview
This project is part of **HY-457: Introduction to Secure Systems** at the University of Crete. The assignment consists of two main parts:
1. **Implementation of various cryptographic algorithms** (Part A), including one-time pad encryption, affine cipher, substitution cipher, Trithemius cipher, Scytale cipher, and Rail Fence cipher.
2. **A simple key-value store** with encryption using AES (Part B). The key-value store supports storing and retrieving encrypted key-value pairs securely.

I completed all parts of this assignment and received full marks (10/10).

## Features

### Part A: Cryptography Algorithms

1. **One-Time Pad**:
   - Implements encryption and decryption using the one-time pad technique, where each bit of plaintext is XOR-ed with a randomly generated key.
   - Functions: `one_time_pad_encr`, `one_time_pad_decr`.

2. **Affine Cipher**:
   - Encryption and decryption using affine cipher with the formula (5x + 8) mod 26 for encryption and (21(y - 8)) mod 26 for decryption.
   - Handles both upper and lower case letters.
   - Functions: `affine_encr`, `affine_decr`.

3. **Substitution Cipher Decryptor**:
   - A tool to decrypt a substitution cipher without knowing the key. The tool prompts for letter mappings and performs frequency analysis to assist in decryption.
   - Example cipher: 'Pfim im k pwbp pfkp fkm nwwx wxqjedpwt smixc pfw kzzixw...'.

4. **Trithemius Cipher**:
   - Implements encryption and decryption using the Trithemius cipher, a polyalphabetic substitution cipher that uses a shifting alphabet (tabula recta).
   - Functions: `trithemius_encr`, `trithemius_decr`.

5. **Scytale Cipher**:
   - Encryption and decryption using the Scytale cipher, where text is wrapped around a cylindrical rod.
   - Functions: `scytale_encr`, `scytale_decr`.

6. **Rail Fence Cipher**:
   - Implements the Rail Fence cipher, a transposition cipher that writes the plaintext in a zigzag pattern across multiple rails.
   - Functions: `rail_fence_encr`, `rail_fence_decr`.

### Part B: Key-Value Store
A simple encrypted key-value store that securely stores key-value pairs using AES encryption in CBC mode. The store supports the following operations:

1. **Add a (key, value) pair**:
   - Encrypts and stores a key-value pair in a file using AES encryption with a user-provided password.
   - Command: `kv add -f <filename> key value`

2. **Read a (key, value) pair**:
   - Decrypts and retrieves the value associated with a given key.
   - Command: `kv read -f <filename> key`

3. **Range Read**:
   - Retrieves and decrypts all key-value pairs within a given range of keys.
   - Command: `kv range-read -f <filename> key1 key2`

## How to Run

### Building the Project
This project uses a **Makefile** to compile all the cryptographic functions and the key-value store.

To build the project, run:
```bash
make
```
Running the Cryptography Algorithms
Each function in Part A can be run with its corresponding demo/test file. Examples:

One-Time Pad Encryption:

```bash
./crypto_demo one_time_pad_encr
```
Affine Cipher Encryption:

```bash
./crypto_demo affine_encr
```
Substitution Cipher Decryptor:

```bash
./crypto_demo substitution_decrypt
```
Running the Key-Value Store
Add a Key-Value Pair:

```bash
./kv add -f db.txt <key> <value>

```
Read a Key-Value Pair:

```bash
./kv read -f db.txt <key>
```
Range Read of Key-Value Pairs:

```bash
./kv range-read -f db.txt <key1> <key2>
```
In each operation, you will be prompted to enter the master password for AES encryption/decryption.

Example
Example of the Key-Value Store:

Add an entry:

```bash
$ ./kv add -f db.txt 1 3
```
Enter password: pass
Read an entry:

```bash
$ ./kv read -f db.txt 1
```
Enter password: pass
Key: 1 has value: 3
Range read:

```bash
$ ./kv range-read -f db.txt 1 3
```
Enter password: pass
Key: 1 has value: 3
Project Structure
cs457_crypto.c, cs457_crypto.h: Contains the implementation of cryptographic algorithms (Part A).
kv_store.c: Implements the key-value store with AES encryption (Part B).
Makefile: Build file to compile the project.
README.md: This file.
Additional Information
The project was implemented entirely in C, without external libraries for cryptographic algorithms except OpenSSL for AES encryption.
The provided Makefile compiles all parts of the project.
A test_file is provided for testing all functions.
Frequencies for the substitution cipher were generated using English language corpora.
References
OpenSSL Library: https://www.openssl.org/
AES CBC Mode: https://www.openssl.org/docs/man3.1/man3/EVP_BytesToKey.html
Scytale Cipher: https://en.wikipedia.org/wiki/Scytale
Rail Fence Cipher: https://en.wikipedia.org/wiki/Rail_fence_cipher
Conclusion
This assignment was a comprehensive exploration of classical cryptography algorithms and secure storage using modern cryptographic techniques (AES). All the tasks were successfully implemented and tested.

markdown
Αντιγραφή κώδικα

### Key Sections:
1. **Overview**: Brief description of the project and a summary of its parts.
2. **Features**: Explains all the cryptographic algorithms and the key-value store.
3. **How to Run**: Includes commands for building the project and running specific components.
4. **Example**: Shows example commands to demonstrate how the key-value store works.
5. **Project Structure**: Describes the structure and main files of the project.
6. **Conclusion**: A brief reflection on the assignment.

This `README.md` will help users understand the structure o
