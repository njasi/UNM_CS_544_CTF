#!/bin/sh

gcc -o /real /real.c
gcc -o /fake /fake.c
gcc -o /manager /manager.c

/manager &

touch /tmp/started
sleep infinity
