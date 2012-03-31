#!/usr/bin/env ruby19 -wKU
require "yaml"
require "pp"
require 'escape'

(puts "#{File.basename $0} playcounts_yaml"; exit) unless ARGV.length == 1
puts "#{ARGV[0]} does exist" unless File.exists? ARGV[0]

play_counts = YAML::load  File.open ARGV[0]

play_counts.each_pair do |filepath, count|
	arr = `taginfo --short2 #{Escape.shell_command [filepath] } 2>/dev/null`.split(/\n/)
	(output.puts "# No Taginfo for #{filepath}";exit ) if arr.length == 0
	m = {title:arr[0], album:arr[1], artist:arr[2], length:arr[3], tracknum:arr[4], disknum:arr[5]}
	puts %{increment_playcount.applescript #{Escape.shell_command [m[:album],m[:tracknum],m[:disknum]]} #{count}}
	`increment_playcount.applescript #{Escape.shell_command [m[:album],m[:tracknum],m[:disknum]]} #{count}`
end