#!/bin/bash
echo "logrotate starting" >> /home/ctf/log_status.log

# pretend i'm actually using logrotate here, dont want to set it up fully
/usr/sbin/logrotate --version

NOW=$( date '+%F_%H:%M:%S' )
echo "logrotate has run successfully @ $NOW" >> /home/ctf/log_status.log