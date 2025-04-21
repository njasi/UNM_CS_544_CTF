#!/bin/bash


git clone https://github.com/CTFd/CTFd.git

cd CTFd
# make secret key
head -c 64 /dev/urandom > ./CTFd/.ctfd_secret_key


