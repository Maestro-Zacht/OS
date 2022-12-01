#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 process interval"
    exit 1
fi

for i in $(echo {1..6}); do
    ps -el | grep -v UID | tr -s " " | cut -f 2,9,13 | grep -E -e "[0-9]+ Z $1"
done