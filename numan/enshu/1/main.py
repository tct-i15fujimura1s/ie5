#!/usr/bin/python
import numpy as np

R1, R3, R4, R0 = 4, 4, 5, 1
E = 15

R2 = 0
while R2 <= 10:
    A = np.array([[R1+R2+R0, -R0, -R2], [-R0, R3+R4+R0, -R4], [-R2, -R4, R2+R4]])
    B = np.array([0, 0, E])
    X = np.linalg.solve(A, B)
    I1, I2, I3 = X[0:3]
    print "R2 = %.3f => I0 = %.3f" % (R2, I1 - I2)
    R2 += 0.5
