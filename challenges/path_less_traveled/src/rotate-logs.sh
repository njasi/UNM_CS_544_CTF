#!/bin/bash
echo "logrotate starting\n" >> /home/ctf/log_status.log

/usr/bin/logrotate

NOW=$( date '+%F_%H:%M:%S' )
echo "logrotate has run successfully @ $NOW\n" >> /home/ctf/log_status.log