CC             = gcc
CFLAGS         = -g -Wall -O2
SCRIPTS        = *.rb
OBJS           = last_fm_scrobble_on_mplayer_played_50 last_fm_scrobble_on_mplayer_played_50_with_info

all: last_fm_scrobble_on_mplayer_played_50 last_fm_scrobble_on_mplayer_played_50_with_info

last_fm_scrobble_on_mplayer_played_50: last_fm_scrobble_on_mplayer_played_50.o
	${CC} ${CFlAGS} $^ -o $@

last_fm_scrobble_on_mplayer_played_50_with_info: last_fm_scrobble_on_mplayer_played_50_with_info.o
	${CC} ${CFlAGS} $^ -o $@

install: all
	[ ! -d /usr/local/bin/ ] && mkdir /usr/local/bin/; \
	chmod +x ${SCRIPTS}; \
	cp ${OBJS} ${SCRIPTS} /usr/local/bin/
	
clean: 
	rm *.o ${OBJS}