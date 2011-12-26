#!/bin/sh
echo "installing taginfo, tagformat and mplayerlastfm.sh to /usr/local/bin"
mkdir -p '/usr/local/bin/'
cp taginfo '/usr/local/bin/taginfo'
cp tagformat '/usr/local/bin/tagformat'
cp mplayerlastfm.sh '/usr/local/bin/mplayerlastfm'
cp play_directory.sh '/usr/local/bin/play_directory'
echo "Installed mplayerlastfm.sh as mplayerlastfm and play_directory.sh as play_directory /usr/local/bin"