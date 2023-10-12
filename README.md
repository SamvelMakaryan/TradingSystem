# TradingSystem

TradingSystem is a trading platform that allows users to buy and sell stocks using various trading strategies. Here all information
are stored in appropriate files which are in database directories. This system manages stocks, their prices, traders informations, and transactions in a multithreaded way. Users can get access to history of transactions, manipulate with stocks and traders after the market has closed with specific commands.

## Requirments

-   CMake
-   C++ compiler

## Installation

- clone this repository
    - git clone https://github.com/SamvelMakaryan/TradingSystem.git
- move to 'TradingSystem' directory
- make sure the start.sh script has execute permission if not do
    - chmod +x start.sh
- run start.sh script

## Usage

After running the program creates timer with random number and opens the stock market. Wait until the market closes, then the command line will be open where you can run any of this commands`

- `help` - prints the list of available commands.
- `display` - prints the followings ` 
    - traders info
    - traders stocks
    - transactions
    - stocks
- `add` - adds `
    - trader
    - stock
    - order
- `remove` - removes `
    - trader by id
    - stock by name
- `search` - searches `
    - trader by id
    - stock by name
- `exit` - saves changes and closes the program

### Examples



