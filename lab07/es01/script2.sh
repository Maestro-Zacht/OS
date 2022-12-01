#!/bin/bash

files=$(find "$1" -type f -exec grep -H -n "$2" \{} \;| tr : " " | sort -k1,1 -k2,2n)

for file in $files
do
    echo "$file"
done > "$3"