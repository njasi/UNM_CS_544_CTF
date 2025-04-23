#!/bin/sh

# compile the program and run it
gcc -o /main /main.c
/main &
touch /tmp/started
sleep infinity
