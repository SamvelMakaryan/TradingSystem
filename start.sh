#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi

cd build

cmake ..

make

if [ $? -eq 0 ]; then
    ./TradingSystem
else
    echo "Build failed. TradingSystem executable was not created."
fi
