#!/bin/bash
# mplayerlastfm - simple scrobbling mplayer wrapper
#
# Bilal Hussain
#
# Prerequisites:
#	* Get and setup lastfmsubmitd http://www.red-bean.com/~decklin/software/lastfmsubmitd/
#   * Install taglib http://developer.kde.org/~wheeler/taglib.html
#   * Get taginfo in this repo (https://github.com/Bilalh/mplayer-last.fm-scrobbler/blob/master/taginfo.cpp)
#   * mplayer
# Install this script in your $PATH e.g '/usr/local/bin/m' for easy use
#
#  Press  Ctrl-\ to quit
#
# Known problems:
#	* 'q' interrupts only playback of current file; press and *hold* ctrl-C
#	* even if you skip file immediately with Enter or 'q', it gets scrobbled - see below
#
# Song info will be submitted after you finish listening to the song;
# if you are SKIPPING a track and don't want it to appear, press Ctrl-C
# in mplayer - it will skip to the next track without scrobbling.
#

#Set defaults
player=${LASTFM_PLAYER:=mplayer}
taginfo=${TAGINFO:=taginfo}
scrobbler=${LASTFM_SUBMIT:=lastfmsubmit}

function scrobble () {
	read album;
	read artist;
	read title;
	read time;	
	
	[ "$album" = "1" ] && album=""
	echo "### $scrobbler -e utf8 -l \"$time\" -a \"$artist\" -b \"$album\" --title \"$title\""
	$scrobbler -e utf8 -l "$time" -a "$artist" -b "$album" --title "$title"
}

trap "exit"  HUP PIPE KILL QUIT TERM EXIT
for f; do
	$player "$f" || continue

	case "$f" in
	*.mp3 | *.m4a | *.flac | *.ogg )
		$taginfo -short "$f" \
		|  scrobble
		;;
	esac
done
