#!/bin/sh

# fix the sudo complaining issue?
echo "127.0.0.1 $(hostname)" >> /etc/hosts

# make normal workers
for i in $(seq 1 $((RANDOM % 15 + 5)));
do
  /normal &
done

# disguise target
mv /normal /normal.tmp
mv /target /normal
/normal &

# move normal back and make some more
mv /normal.tmp /normal
for i in $(seq 1 $((RANDOM % 15 + 5)));
do
  /normal &
done

rm /normal

touch /tmp/started

sleep infinity
