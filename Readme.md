MPlayer last.fm Scrobbler {#readmeTitle}
=========================
A command line application that plays audio files with MPlayer and scrobbles them to last.fm. Supports mp3, mp4, flac and ogg.
{#description}

Usage
-----
`mplayerlastfm.sh <glob>`
`play_directory.sh`

Prerequisites
-------------
* Get and setup [lastfmsubmitd](http://www.red-bean.com/~decklin/software/lastfmsubmitd/ "http://www.red-bean.com/~decklin/software/lastfmsubmitd/")
* Install [taglib](http://developer.kde.org/~wheeler/taglib.html "http://developer.kde.org/~wheeler/taglib.html") 
* mplayer

Install 
-------
* run `make.sh` to compile `taginfo` 
* run `install.sh` (might need sudo) to install `mplayerlastfm.sh` as `/usr/local/bin/mplayerlastfm` and `play_directory.sh` as `/usr/local/bin/play_directory.sh`  
or Install `mplayerlastfm.sh` in your `$PATH` e.g '/usr/local/bin/m' for easy use



mplayerlastfm.sh
----------------
Set these variables before running mplayerlastfm.sh to set your preferences.

	LASTFM_PLAYER        default mplayer
	TAGINFO              default taginfo
	LASTFM_SUBMIT        default lastfmsubmit
	SCROBBLER_ECHO       default true
	DISPLAY_TRACK_INFO   default true

play_directory.sh
-----------------
Allows the user to choose which directory to play using `mplayerlastfm.sh`. 
if the directory contains *4* directory album 1 to album 4 then running `play_directory.sh`
will result in:

	1) Album 1    3) Album 3  
	2) Album 3    4) Album 4
	#? 

Where the user type the number e.g 3 to pick Album 3.  It play recursively all files in the directory. 

Set these variables before running play_directory.sh to set your preferences.

	MPLAYER_LASTFM default mplayerlastfm
	MPN_DIR        defualt $HOME/Music

`MPN_DIR` is directory to play from. 
 
Issues
------
* q' interrupts only playback of current file; press and *hold* ctrl-C to skip.  
 Even if you skip file immediately with Enter or 'q' it will scrobble

Deamon
------
* There is also a  version that works like a `deamon` in the  `Deamon` directory, has a lot more prerequisites but is more efficient and less tested.  

Licence
-------
[Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License](http://creativecommons.org/licenses/by-nc-sa/3.0/ "Full details")

Authors
-------
* Bilal Hussain