#!/bin/bash

if  [ $# -eq 0 ]; then
    echo "Insert file name:"
    read directory
elif [ $# -eq 1 ]; then
    directory=$1
else
    echo "$0 directory or $0 and insert directory"
    exit 1
fi

list=$(ls "$directory")
cd "$directory"

for elem in $list; do
    newname=$(echo -n "$elem" | tr a-z A-Z)
    mv "$elem" "$newname"
done