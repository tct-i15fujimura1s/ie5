E = 10
R = 50e+3
C = 200e-6
t = [0]
v = [0]

tMax = 2

def e(t)
  (t % 1 < 0.5) ? E : 0
end

def f(t, v)
  (e(t) - v) / (R * C)
end

h = 0.1

iMax = tMax / h

0.upto(iMax) do |i|
  k1 = h * f(t[i],     v[i])
  k2 = h * f(t[i]+h/2, v[i]+k1/2)
  k3 = h * f(t[i]+h/2, v[i]+k2/2)
  k4 = h * f(t[i]+h,   v[i]+k3)
  t[i+1] = t[i] + h
  v[i+1] = v[i] + (k1 + 2*k2 + 2*k3 + k4)/6
end

t.zip(v) do |(t, v)|
  puts "#{t}\t#{v}"
end
