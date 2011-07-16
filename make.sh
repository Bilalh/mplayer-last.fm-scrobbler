#!/bin/sh
echo "making taginfo"
g++ `taglib-config  --cflags --libs`  taginfo.cpp  -o taginfo

