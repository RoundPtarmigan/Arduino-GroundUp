#! /usr/bin/bash

OBJCOPY="/usr/bin/avr-objcopy"
OBJCOPY_FLAGS="-j .text -j .data -O ihex"

if [ "$#" -ne 1 ]; then
    echo BAD ARGS
else
    $OBJCOPY $OBJCOPY_FLAGS $1 $1.hex
fi