#!/bin/bash
echo "Installing tools"

echo "gcc-arm-none-eabi"
sudo apt-get install gcc-arm-none-eabi

echo "stlink"
sudo apt-get install stlink-tools

echo "picocom"
sudo apt-get install picocom