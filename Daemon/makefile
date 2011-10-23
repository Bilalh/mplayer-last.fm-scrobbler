CC             = gcc
CFLAGS         = -g -Wall -O2

last_fm_scrobble_on_mplayer_played_50: last_fm_scrobble_on_mplayer_played_50.o
	${CC} ${CFlAGS} $^ -o $@
  
install: last_fm_scrobble_on_mplayer_played_50
	[ ! -d /usr/local/bin/ ] && mkdir /usr/local/bin/; \
	chmod +x lastfm_from_mplayer_output.rb lastfm_from_mplayer_output_and_tags.rb; \
	cp last_fm_scrobble_on_mplayer_played_50 lastfm_from_mplayer_output.rb lastfm_from_mplayer_output_and_tags.rb /usr/local/bin/