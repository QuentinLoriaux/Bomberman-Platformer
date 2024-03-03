#!/bin/bash

# Check if user is root
if [ "$(id -u)" != "0" ]; then
    echo "This script must be run as root" 1>&2
    exit 1
fi

# Update package lists
apt update

# Install libsfml-dev
apt install libsfml-dev -y

# Install librapidxml-dev
apt install librapidxml-dev -y

# Install clang++-16
apt install clang-16 -y

# Run make in current directory
make

# Execute the resulting binary
./Bomberman_Plat.x