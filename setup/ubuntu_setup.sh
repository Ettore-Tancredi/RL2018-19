#!/bin/bash

printf "Setup will now begin...\n"
sleep 3

printf "\nUpdating OS:\n"
sleep 3
sudo apt-get update
sudo apt-get upgrade

printf "\nInstalling python 3.6:\n"
sleep 3
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt-get update
sudo apt-get install python3.6

printf "\nInstalling numpy:"
sleep 3
python3.6 -m pip install numpy

printf "\nInstalling tkinter:"
sleep 3
sudo apt-get install python3.6-tk

printf "\nInstalling matplotlib:"
sleep 3
sudo apt-get install python3-matplotlib

printf "\nInstalling Atom text editor:\n"
sleep 3
sudo apt install curl
curl -sL https://packagecloud.io/AtomEditor/atom/gpgkey | sudo apt-key add -
sudo sh -c 'echo "deb [arch=amd64] https://packagecloud.io/AtomEditor/atom/any/ any main" > /etc/apt/sources.list.d/atom.list'
sudo apt-get update
sudo apt-get install atom
