#!/usr/bin/env bash

for h in $(cat md5.json | grep output | awk '{split($0,a,": "); print a[2]}' | sed 's/"//g'); do
    echo "| \`${h}\` | \`$(echo "${h}" | xxd -r -p | xxd | awk '{split($0,a," "); print a[10]}')\` | ";
done
