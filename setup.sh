#!/bin/bash

git clone https://github.com/CTFd/CTFd.git

# config ctfd
cd CTFd
head -c 64 /dev/urandom > ./CTFd/.ctfd_secret_key

# add the docker challenges plugin
cd ../
git clone https://github.com/offsecginger/CTFd-Docker-Challenges
ln -s CTFd/CTFd/plugins/docker_challenges CTFd-Docker-Challenges/docker_challenges

# build the docker stuff
cd CTFd
docker compose build


