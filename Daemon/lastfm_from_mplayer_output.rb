#!/usr/bin/env ruby19  -wKU
require "yaml"
require "pp"
require 'escape'

LASTFM_SUBMIT = '/usr/local/bin/lastfmsubmit'
METADATA_FILE = "/Users/bilalh/Movies/.Movie/OpeningP/_metadata.yaml"
output        = $stderr

scrobbler_echo = ENV['SCROBBLER_ECHO']    || true
use_taginfo    = ENV['USE_TAGINFO']       || false
scrobbler_echo = false if !scrobbler_echo || scrobbler_echo == 'false'
# use_taginfo    = false if !use_taginfo    || use_taginfo    == 'false'


display = ENV['DISPLAY_TRACK_INFO']    || true
display = false if !display || display == 'false'

`echo "get_property path" >>  ~/.mplayer/pipe`
sleep 0.1
filepath_with_name = `tail -n1 ~/.mplayer/output`
filepath = filepath_with_name[/.*?=(.*)/,1]
m = {} 

if use_taginfo then
	arr = `taginfo --short #{Escape.shell_command [filepath] } 2>/dev/null`.split(/\n/)
	exit if arr.length == 0
	m = {title:arr[0], album:arr[1], artist:arr[2], length:arr[3]}
	output.puts('# ' + `taginfo --info #{Escape.shell_command [filepath]} 2>/dev/null`) if display
else
	filepath = File.basename filepath
	metadata = YAML::load( File.open(METADATA_FILE)) || (puts "no metadata file"; exit)
	m = metadata[File.basename filepath] || (puts "no metadata for '#{File.basename filepath}'"; exit)
	
	# m[:length] = `mediaInfo --Inform='Video;%Duration/String3%' "#{File.basename filepath}" | sed "s/\.[0-9][0-9]*$//"` 
	m[:length] = "1:30" # fake length because of flv
	output.puts "# #{m[:artist]} - #{m[:title]} - #{m[:album]}" if display
end


output.puts %{# #{LASTFM_SUBMIT} -e utf8 -a "#{m[:artist]}" -b "#{m[:album]}" --title "#{m[:title]}" -l "#{m[:length]}"} if scrobbler_echo
# scrobbles the track

artist, album, title = Escape.shell_single_word(m[:artist]),  Escape.shell_single_word(m[:album]),  (Escape.shell_single_word m[:title])
# puts "# #{artist}, #{album}, #{title}"

puts `kill $(ps aux | grep lastfmsubmitd | grep -v grep  | awk '{print $2}') &>/dev/null;\ 
#{LASTFM_SUBMIT} -e utf8 -a #{artist} -b #{album} --title #{title} -l "#{m[:length]}"; lastfmsubmitd&`


