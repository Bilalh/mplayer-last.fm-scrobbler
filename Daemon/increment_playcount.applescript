#!/usr/bin/env osascript -s h
# increments the playcount of the specified track
on run argv
	
	set theAlbum to item 1 of argv as Unicode text
	set theTrackNum to item 2 of argv as integer
	set theDiskNum to item 3 of argv as integer
	set plus to item 4 of argv as integer
	
	--set theAlbum to "Dragon Quest I~IX ~Scene-Separated~ Symphonic Suite"
	--set theTrackNum to 1 as integer
	--set theDiskNum to 1 as integer
	
	tell application "iTunes"
		set aTrack to item 1 of (tracks of playlist "Music" whose album is equal to theAlbum Â
			and track number is equal to theTrackNum Â
			and disc number is equal to theDiskNum)
		set aTrack's played count to (aTrack's played count) + plus
		
	end tell
end run