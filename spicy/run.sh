#!/bin/bash

# source ../venv/bin/activate

make && python3 parsePcap.py $1
