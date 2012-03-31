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
* [taginfo](https://github.com/Bilalh/mplayer-last.fm-scrobbler/)

Install 
-------
* Makes sure taginfo is in your `$PATH`
* Make a FIFO which can be made by doing `mkfifo ~/.mplayer/pipe`
	* Set the path to your MPlayer FIFO in the source files if not using the above path
* run `make`
* run `make install`
* make sure that `/usr/local/bin` is in your `$PATH`

Options
-------
By editing the C file `#defines` and the ruby file's vars

Keep track of play count
------------------------
By doing `export USE_INCREMENT=true`, the scripts will keep track of play counts. Use `update_itunes_playcounts.rb` to add to iTunes's plays counts.

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