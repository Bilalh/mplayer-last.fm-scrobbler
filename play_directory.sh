scrobber=${MPLAYER_LASTFM:-mplayerlastfm}	
dir=${MPN_DIR:-$HOME/Music}
cd "$dir" 
trap "" INT

export LC_ALL='C';
IFS=$'\x0a';
select OPT in `ls | grep -vP 'cover|ςbz|zoff alias| Renaming' | sort -bf` "." "Cancel"; do
	unset LC_ALL
	if [ "${OPT}" != "Cancel" ]; then
		if [ "$1x" == "-lx" ]; then ls -R "${OPT}"; shift; fi;
		find "${OPT}" \( -iname "*\.mp3" -o -iname "*\.flac"  -o -iname "*\.m4a" -o -iname "*\.ogg"  -o -iname "*\.wma" \) -exec ${scrobber}  $* '{}' +
	fi
	break;
done
unset IFS;
cd "$OLDPWD"
