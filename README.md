# Banking System Project

## Overview

This project is a simple banking system implemented in C++. It allows users to manage client accounts, perform transactions, and update account details using a text file (`Clients.txt`) as a database.

## Features

- List all clients
- Add a new client
- Delete a client
- Update client details
- Find a client by account number
- Perform transactions:
  - Deposit money
  - Withdraw money
  - View total balances
- Navigate through menus for easy use

## File Structure

- `main.cpp` - Contains the main logic of the program
- `Clients.txt` - Stores client information in a structured format

## Data Storage Format

Client data is stored in `Clients.txt` using the following format:

```
AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance
```

Each record is separated by `#//#` to ensure easy parsing.

## Compilation and Execution

### Requirements

- C++ Compiler (e.g., g++)

### Compilation Command

```
g++ main.cpp -o BankingSystem
```

### Run the Program

```
./BankingSystem
```

## Usage

1. Run the program.
2. Select an option from the main menu:
   - View clients
   - Add, delete, or update a client
   - Find a specific client
   - Perform banking transactions
   - Exit the program
3. Follow the on-screen instructions for each operation.

## Future Enhancements

- Implement more feature

## Author

- Developed by Yousef Yasser Hamada
