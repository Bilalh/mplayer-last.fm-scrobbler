#!/bin/sh
echo "making taginfo"
g++ -O2 `taglib-config  --cflags --libs`  taginfo.cpp  -o taginfo

echo "making tagformat"
g++ -O2 `taglib-config  --cflags --libs`  tagformat.cpp  -o tagformat