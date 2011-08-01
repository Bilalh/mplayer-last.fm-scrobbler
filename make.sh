#!/bin/sh
echo "making taginfo"
g++ -O2 `taglib-config  --cflags --libs`  taginfo.cpp  -o taginfo

