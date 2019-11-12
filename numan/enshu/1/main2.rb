#!/usr/bin/ruby
require 'matrix'


R1, R3, R4, R0 = 4, 4, 5, 1 #[Ω]
E = 15 #[V]

0.step(by: 0.5, to: 10) { |r2|
  puts "R2 = %4.1f [Ω]:" % r2
  matA = Matrix[[R1+r2+R0, -R0, -r2], [-R0, R3+R4+R0, -R4], [-r2, -R4, r2+R4]]
  vecB = Vector[0, 0, E]
  lup = matA.lup
  matL, matU = lup.l, lup.u
  vecX = lup.solve(vecB)
  i0 = vecX[0] - vecX[1]
  puts <<-EOT
  L = #{matL}
  U = #{matU}
  I0 = #{"%6.3f" % i0} [A]
  EOT
}
