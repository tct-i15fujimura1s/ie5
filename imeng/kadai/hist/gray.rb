#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

def main
  if ARGV.empty?
    puts "Usage: ruby gray.rb FILE.pgm"
    exit 0
  end

  # pgm ファイル読み込み
  content = File.binread ARGV[0]

  pgm = PGM.parse(content)


end

class PGM
  include Enumerable

  def self.parse(src)
    src = src.gsub(/^#.+\n/, '')
    raise "pgm error" unless src =~ /\AP5\s+(\d+)\s+(\d+)\s+(\d+)\s+/
    width, height, max = $1.to_i, $2.to_i, $3.to_i
    src = src[$&.length .. -1]
    pgm = PGM.new(width, height, max)

    bytes = (Math.log2(max + 1) / 8).ceil

    src.chars.each_slice(bytes) do |slice|
      slice.chars.inject(0) { |n, c| n << 8 | c.ord }
    end
  end

  def initialize(width, height, max)
    @width, @height, @max = width, height, max
    @data = Array.new(width * height)
  end

  def [](x, y)
    raise "Index out of range: (#{x},#{y})" if x >= @width or y >= @height
    @data[y * @width + x]
  end

  def []=(x, y, value)
    raise "Index out of range: (#{x},#{y})" if x >= @width or y >= @height
    @data[y * @width + x] = value
  end

  def each
    (1 ... @width).each do |x|
      (1 ... @height).each do |y|
        yield [self[x, y], x, y]
      end
    end
  end
end

main
