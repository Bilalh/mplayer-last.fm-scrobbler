MPlayer last.fm Scrobbler Deamon {#readmeTitle}
================================
A deamon that scrobbles the current playing track on reaching 50%.
{#description}

Usage
-----
`last_fm_scrobble_on_mplayer_played_50 &` 
`last_fm_scrobble_on_mplayer_played_50_with_info &` 

Prerequisites
-------------
* Get and setup [lastfmsubmitd](http://www.red-bean.com/~decklin/software/lastfmsubmitd/ "http://www.red-bean.com/~decklin/software/lastfmsubmitd/")
* Install [taglib](http://developer.kde.org/~wheeler/taglib.html "http://developer.kde.org/~wheeler/taglib.html") 
* mplayer
* ruby 1.9
* escape gem

Install 
-------
* Set the path to your MPlayer FIFO in the files
	* a FIFO can be made by doing `mkfifo ~/.mplayer/pipe`
* run `make`
* run `make install`
* make sure that `/usr/local/bin` is in your `$PATH`

Options
-------
By editing the C file `#defines` and the ruby file's vars

See
---
* [mplayer.sh](https://github.com/Bilalh/Bash-Scripts/blob/master/mplayer.sh, "mplayer.sh") contains function for controlling MPlayer and playing media files.
* [mplayer setting](https://github.com/Bilalh/MPlayer-Settings) for the setting used in the above link.


Issues
------
None Yet

Licence
-------
[Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License](http://creativecommons.org/licenses/by-nc-sa/3.0/ "Full details")

Authors
-------
* Bilal Hussain