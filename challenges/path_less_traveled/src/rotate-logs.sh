#!/bin/bash
echo "logrotate starting\n" >> /home/*/log_status.log

/usr/bin/logrotate

NOW=$( date '+%F_%H:%M:%S' )
echo "logrotate has run successfully @ $NOW\n" >> /home/*/log_status.log