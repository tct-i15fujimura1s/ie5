#!/usr/bin/ruby
# -*- coding: utf-8 -*-


Sym = Struct.new(:char, :count, :sign)
Unit = Struct.new(:left, :right, :count)

data = STDIN.read

length = data.length
ps = Hash.new { |_, key| Sym[key, 0, ''] }
data.chars do |c|
  pc = ps[c]
  pc.count += 1
  ps[c] = pc
end

syms = ps.values.sort { |t, u| u.count <=> t.count }
syms_ = syms.dup

p ps

def append sym, sig
  if sym.kind_of? Unit
    append sym.left, sig
    append sym.right, sig
  else
    sym.sign += sig
  end
end

while syms.size > 2
  t, u = *syms.pop(2)
  append t, '0'
  append u, '1'
  v = Unit[t, u, t.count + u.count]
  if (i = syms.rindex { |s| s.count >= v.count })
    syms.insert i, v
  else
    syms.unshift v
  end
end

puts "%4s %5s %s" % ["sym.", "prob.", "sig."]
syms_.each do |sym|
  puts "%4s %5.3f %s" % [sym.char.inspect, sym.count.to_f / length, sym.sign]
end

SymEl = Struct.new(:char, :bits, :sign)

stbl = {}
syms_.each do |sym|
  stbl[sym.char] = SymEl[sym.char, sym.sign.length, sym.sign.to_i(2)]
end

@bytes = []

def cut_bytes(value, bits)
  while bits >= 8
    bits -= 8
    byte = (value >> bits) & 0xff
    @bytes << byte
    puts "<- " + byte.to_s(2).rjust(8, '0')
  end
  value &= 0xff
  [value, bits]
end

value, bits = *data.chars.inject([0, 0]) do |(value, bits), c|
  sym = stbl[c]
  bits += sym.bits
  value = value << sym.bits | sym.sign
  puts "    " + value.to_s(2).rjust(bits, '0')
  cut_bytes(value, bits)
end
value, bits = *cut_bytes(value, bits)
@bytes << (value & (0xff >> bits)) if bits > 0
@bytes << bits

puts "data:"
@bytes.each_slice(8) do |row|
  puts "  " + row.map { |i| "%02x" % i }.join(" ")
end
