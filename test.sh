#!/bin/zsh

make
./pyxx testing/test.pyxx
cat testing/test.py
python3 testing/test.py
