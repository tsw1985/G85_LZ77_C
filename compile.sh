#!/bin/sh
make clean
make
./bin/g85zip /home/gabriel/demotext.txt -c
# ./bin/g85zip