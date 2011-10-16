#!/usr/bin/env ruby19
# old Version of the deamon -- takes too much cpu time

current_done = false
FIFO_NAME = File.expand_path "~/.mplayer/pipe"
Command="get_percent_pos\n"
file = open FIFO_NAME, 'w'
file.sync = true
while true
	file.print Command
	sleep 0.4
	pos_with_equals = `tail -n1 ~/.mplayer/output`
	pos = pos_with_equals[/.*=(\d+)/,1].to_i
	
	if !current_done && pos >= 50 then
		`~/Scripts/lastfm_from_mplayer_output.rb`
		current_done = true
	end
			
	if current_done  && pos <50 then
		current_done = false
	end	
	
	sleep 10
end