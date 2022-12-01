#!/bin/bash

if  [ $# -eq 0 ]; then
    echo "Insert file name:"
    read file
elif [ $# -eq 1 ]; then
    file=$1
else
    echo "$0 file or $0 and insert file"
    exit 1
fi

lines=$(wc -l "$file" | cut -d " " -f 1)

maxchar=-1

while read line
do
    chars=$(echo -n "$line" | wc -m)
    if [ $chars -gt $maxchar ]; then
        maxchar=$chars
    fi
done < "$file"

echo "Longest line: $maxchar"
echo "Number of lines: $lines"