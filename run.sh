#!/bin/sh

gcc ./trees/main.c ./trees/avl-tree/avltree-counter.c ./trees/b-tree/btree-counter.c ./trees/red-black-tree/redblacktree-counter.c -o ./trees/main.o

./trees/main.o

./image-generator/venv/bin/python ./image-generator/main.py


