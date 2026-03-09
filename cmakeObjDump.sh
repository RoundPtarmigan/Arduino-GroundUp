#! /usr/bin/bash

OBJDUMP="avr-objdump"
SYMB_DUMP_FLAGS="-t"
LST_DUMP_FLAGS="-d -h"

if [ "$#" -ne 1 ]; then
    echo BAD ARGS
else
    $OBJDUMP $SYMB_DUMP_FLAGS $1 > $1.symb
    $OBJDUMP $LST_DUMP_FLAGS $1 > $1.lst
fi