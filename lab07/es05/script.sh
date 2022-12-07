#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 process interval"
    exit 1
fi

for i in $(echo {1..6}); do
    process=$(ps -el | tr -s " " | cut -f 2,4,14 -d " " | grep -E -e "Z [0-9]+ $1")
    if [ $? ]; then
        echo "Process $1 zombie at iteration $i"
    else
        echo "Process $1 not zombie at iteration $i"
        break
    fi
    sleep $2
done

echo $process

if [ $? ]; then
    pid=$(echo $process | cut -f 2 -d " ")
    echo "Killing process $1 with PID $pid"
    kill -9 "$pid"
fi