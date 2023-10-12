# TradingSystem

TradingSystem is a trading platform that allows users to buy and sell stocks using various trading strategies. Here all information
are stored in appropriate files which are in database directories. This system manages stocks, their prices, traders informations, and transactions in a multithreaded way. 
Users can get access to history of transactions, manipulate with stocks and traders after the market has closed with specific commands.

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

You can add orders, traders and stocks directly in files. Currently only available strategies for orders are limit and market. The status of order can be confirmed, rejected or waiting,

### Examples
![Screenshot from 2023-10-12 21-19-24](https://github.com/SamvelMakaryan/TradingSystem/assets/123547362/d5bc089c-1299-4329-afdd-9948536925bf)

![Screenshot from 2023-10-12 21-19-34](https://github.com/SamvelMakaryan/TradingSystem/assets/123547362/bfd53eaf-6bde-4351-a50c-6d3301b7ce13)

#### Execution of display transactions command
![Screenshot from 2023-10-12 21-20-19](https://github.com/SamvelMakaryan/TradingSystem/assets/123547362/e5161144-4c89-43eb-821f-d04d08641948)


