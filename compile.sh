#!/bin/sh
make clean
make
./bin/g85zip

# compresion
# ./bin/g85zip /home/gabriel/demotext.txt -c

# descompresion
# ./bin/g85zip /home/gabriel/demotext.txt -d

# ./bin/g85zip /home/gabriel/FreeDOS.vdi -c
# gdb ./bin/g85zip "/home/gabriel/FreeDOS.vdi" -c
# ./bin/g85zip /home/gabriel/datos.csv -c
# gdb "./bin/g85zip /home/gabriel/demotext.txt -c"
# ./bin/g85zip