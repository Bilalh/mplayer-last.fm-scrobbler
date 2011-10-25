CC             = gcc
CFLAGS         = -g -Wall -O2
SCRIPTS        = lastfm_from_mplayer_output.rb lastfm_from_mplayer_output_and_tags.rb audio_info_display.rb

all: last_fm_scrobble_on_mplayer_played_50 last_fm_scrobble_on_mplayer_played_50_with_info

last_fm_scrobble_on_mplayer_played_50: last_fm_scrobble_on_mplayer_played_50.o
	${CC} ${CFlAGS} $^ -o $@

last_fm_scrobble_on_mplayer_played_50_with_info: last_fm_scrobble_on_mplayer_played_50_with_info.o
	${CC} ${CFlAGS} $^ -o $@

install: all
	[ ! -d /usr/local/bin/ ] && mkdir /usr/local/bin/; \
	chmod +x ${SCRIPTS}; \
	cp last_fm_scrobble_on_mplayer_played_50 last_fm_scrobble_on_mplayer_played_50_with_info ${SCRIPTS} /usr/local/bin/