#!/bin/bash


reference="$1"
real="$2"


test_data="$(grep -Eo "(-?)([0-9]+)(\.[0-9]+)?" "$reference")"
real_data="$(grep -Eo "(-?)([0-9]+)(\.[0-9]+)?" "$real")"


#echo $?
#echo -e "Test data:\n\t$test_data"
#echo -e "Real data:\n\t$real_data"

if [[ "$test_data" != "$real_data" ]]; then
    exit 1
fi
exit 0;