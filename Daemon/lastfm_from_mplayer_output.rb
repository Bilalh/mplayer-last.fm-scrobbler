#!/usr/bin/env ruby19  -wKU
require "yaml"
require "pp"

LASTFM_SUBMIT = '/usr/local/bin/lastfmsubmit'
METADATA_FILE = "/Users/bilalh/Movies/.Movie/OpeningP/_metadata.yaml"
output        = $stderr

scrobbler_echo = ENV['SCROBBLER_ECHO']    || true
scrobbler_echo = false if !scrobbler_echo || scrobbler_echo == 'false'

display = ENV['DISPLAY']    || true
display = false if !display || display == 'false'

`echo "get_file_name" >>  ~/.mplayer/pipe`
sleep 0.1
filepath_with_name = `tail -n1 ~/.mplayer/output`
filepath = filepath_with_name[/.*='(.*)'/,1]

# puts filepath
metadata = YAML::load( File.open(METADATA_FILE)) || (puts "no metadata file"; exit)
m = metadata[File.basename filepath] || (puts "no metadata for '#{File.basename filepath}'"; exit)

output.puts "#{m[:artist]} - #{m[:title]} - #{m[:album]}" if display

# length = `mediaInfo --Inform='Video;%Duration/String3%' "#{File.basename filepath}" | sed "s/\.[0-9][0-9]*$//"`
# length.strip!
length = "1:30" # fake length because of flv

output.puts %{#{LASTFM_SUBMIT} -e utf8 -a "#{m[:artist]}" -b "#{m[:album]}" --title "#{m[:title]}" -l "#{length}"} if scrobbler_echo
# scrobbles the track
puts `kill $(ps aux | grep lastfmsubmitd | grep -v grep  | awk '{print $2}') &>/dev/null;\ 
#{LASTFM_SUBMIT} -e utf8 -a "#{m[:artist]}" -b "#{m[:album]}" --title "#{m[:title]}" -l "#{length}"; lastfmsubmitd&`


