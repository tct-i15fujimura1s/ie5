# -*- coding: utf-8 -*-

def input(prompt="", &map)
  print prompt
  str = STDIN.gets
  return map[str] if block_given?
  str
end

puts "2分法でx^2=aになるxを探します"
a = input("a = ", &:to_f)

def f(x)
  x ** 2
end

e_limit = 1e-8 # 打切り誤差

l, r = 0, 1e+8
step = 0
while (r-l) > e_limit
  c = (r + l) * 0.5
  if step % 10 == 0
    puts "step #{step}. #{l} .. #{r} : #{c}"
    sleep 0.1
  end
  b = f(c)
  if b > a
    r = c
  else
    l = c
  end
end
