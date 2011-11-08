#!/usr/bin/env ruby19  -wKU
require 'escape'

output = $stderr

`echo "get_property path" >>  ~/.mplayer/pipe`
sleep 0.1
filepath_with_name = `tail -n1 ~/.mplayer/output`
filepath = filepath_with_name[/.*?=(.*)/,1]

`echo "get_time_pos" >>  ~/.mplayer/pipe`
sleep 0.1
time_with_name = `tail -n1 ~/.mplayer/output`
time = time_with_name[/.*?=(.*)/,1]
time = time.to_f.round
return unless time && filepath
output.puts('# ' + `taginfo --details-colour #{Escape.shell_command [filepath]} #{time}  2>/dev/null`)