#!/bin/sh

# ffid the sudo complaining issue?
echo "127.0.0.1 $(hostname)" >> /etc/hosts

/manager &

touch /tmp/started
sleep infinity
