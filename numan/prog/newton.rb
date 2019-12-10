# -*- coding: utf-8 -*-

def input(prompt="", &map)
  print prompt
  str = STDIN.gets
  return map[str] if block_given?
  str
end

puts "ニュートン法でx^2=aになるxを探します"
puts "x^2=a <-> x^2-a = 0"
a = input("a = ", &:to_f)

f = proc { |x| x ** 2.0 - a }
g = proc { |x| 2.0 * x }

EPS = 1e-8 # 打切り誤差
LIMIT = 30 # 打切り回数

x = 1 # 初期値
step = 0
while step < LIMIT
  puts "step #{step}. x = #{x}"
  sleep 0.1
  x_next = x-f.(x)/g.(x)
  break if (x-x_next).abs <= EPS
  x = x_next
  step += 1
end
p x
