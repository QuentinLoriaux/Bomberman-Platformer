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
if ! command -v clang++-16 &>/dev/null; then
    # If clang++-16 doesn't exist, proceed with installation
    wget https://apt.llvm.org/llvm.sh
    chmod +x llvm.sh
    ./llvm.sh 16
else
    echo "clang++-16 is already installed."
fi

# Install make
apt install make -y

# Run make in current directory
make

# Execute the resulting binary
./Bomberman_Plat.x