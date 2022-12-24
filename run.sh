#!/bin/bash

gcc ./trees/main.c ./trees/avl-tree/avltree-counter.c ./trees/b-tree/btree-counter.c ./trees/red-black-tree/redblacktree-counter.c -o ./trees/main.o

./trees/main.o

if ! [ -d ./image-generator/venv ]; then
  echo "No virtual environment found. Installing packages..."
  python -m venv ./image-generator/venv
  source ./image-generator/venv/bin/activate
  pip install -r ./image-generator/requirements.txt
else
  echo "Virtual environment found. Skipping installation of Python packages."
fi


./image-generator/venv/bin/python ./image-generator/generateScatteredPoints.py
./image-generator/venv/bin/python ./image-generator/generateRegression.py

echo "Files generated! Check ./files directory."

