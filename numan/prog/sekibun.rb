def integral(a, b, n, &f)
  m = 2*n
  h = (b - a) / m
  odd = 1.step(m-1, 2).inject(0) { |s, i| s + f[a + h * i] }
  even = 2.step(m-2, 2).inject(0) { |s, i| s + f[a + h * i] }
  return h/3 * (f[a] + f[b] + 4 * odd + 2 * even)
end

def int_iter(label, a, b, l, &f)
  puts "integral #{label} from #{a} to #{b}"
  n = 1
  w = integral(a, b, n, &f)
  puts "  n = #{n}: I = #{w}"
  loop do
    n *= 2
    v = w
    w = integral(a, b, n, &f)
    puts "  n = #{n}: I = #{w}"
    break if (v-w).abs < l
  end
  puts "int[#{a}, #{b}] #{label} dx = #{w}"
end

int_iter("sin(x)", 0.0, Math::PI, 1e-10) { |x| Math.sin(x) }
puts

int_iter("sqrt(1 - x**2)", 0.0, 1.0, 1e-10) { |x| Math.sqrt(1 - x**2) }
