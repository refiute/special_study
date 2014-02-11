#!/usr/bin/env ruby
require 'open3'

data = [8, 9, 10, 11, 15, 18, 19, 20, 21, 30, 50, 225, 9847]
tle = [30, 30, 30, 30, 30, 30, 30, 30, 30, 300, 300, 600, 900]

data.each_with_index do |x, idx|
	time_limit = tle[idx]
	puts x
	scale = time_limit >= 300 ? 10 : 1
	Open3.popen3("./genetic_algorithm.out > output/genetic_algorithm_#{x}.out") do |stdin, stdout, stderr, thread|
		stdin.puts "input/data#{x}.in", (20*scale).to_s, (25*scale).to_s, "3", (2*scale).to_s, time_limit.to_s
	end
end
