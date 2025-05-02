#!/bin/bash


logutil rotate /var/log/syslog

NOW=$( date '+%F_%H:%M:%S' )
echo "logutil has run successfully @ $NOW" >> /home/*/log_status.log