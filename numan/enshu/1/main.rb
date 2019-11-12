#!/usr/bin/ruby

def lu_decompose3x3(matA) #=> [matL, matU]
  # matA = matL * matU
  l11, l21, l31 = matA[0][0], matA[1][0], matA[2][0]
  u12, u13 = (matA[0][1] / l11), (matA[0][2] / l11)
  l22, l32 = (matA[1][1] - l21 * u12), (matA[2][1] - l31 * u12)
  u23 = (matA[1][2] - l21 * u13) / l22
  l33 = matA[2][2] - l31 * u13 - l32 * u23
  return [ [[l11, 0, 0], [l21, l22, 0], [l31, l32, l33]],
           [[1, u12, u13], [0, 1, u23], [0, 0, 1]] ]
end

R1, R3, R4, R0 = 4, 4, 5, 1 #[Ω]
E = 15 #[V]

0.step(by: 0.5, to: 10) { |r2|
  matA = [[R1+r2+R0, -R0, -r2], [-R0, R3+R4+R0, -R4], [-r2, -R4, r2+R4]]
  vecB = [0, 0, E]
  matL, matU = *lu_decompose3x3(matA)
  y1 = vecB[0] / matL[0][0]
  y2 = (vecB[1] - y1*matL[1][0]) / matL[1][1]
  y3 = (vecB[2] - y1*matL[2][0] - y2*matL[2][1]) / matL[2][2]
  i3 = y3 / matU[2][2]
  i2 = (y2 - i3*matU[1][2]) / matU[1][1]
  i1 = (y1 - i3*matU[0][2] - i2*matU[0][1]) / matU[0][0]
  puts "R2 = %4.1f [Ω] => I0 = %6.3f [A]" % [r2, i1 - i2]
  puts "  L = #{matL}"
  puts "  U = #{matU}"
  puts "  x = #{[i1, i2, i3]}"
}
