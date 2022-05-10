''' Derive the Jacobian of the Barrett WAM 4-DOF arm
	using the sympy symbolic math package.

		To execute: >> python3 wam_jacobian.py

	Depends on the Sympy "symbolic math" Python library, which can be installed using the following command:

		>> pip3 install --upgrade sympy

	@author Caitrin Eaton
	@date 2019	
'''
import isympy
from sympy import *

init_printing(use_unicode=True)

# Columns of the DH parameter table
ALPHA = 0
A = 1
D = 2
THETA = 3


def frameTransform(alpha, a, d, theta):
    ''' Returns the transformation matrix from frame {i} to {i-1}.'''
    t_adj = Matrix([[cos(theta), -sin(theta), 0, a],
                    [sin(theta) * cos(alpha), cos(theta) * cos(alpha), -sin(alpha), -sin(alpha) * d],
                    [sin(theta) * sin(alpha), cos(theta) * sin(alpha), cos(alpha), cos(alpha) * d],
                    [0, 0, 0, 1]])
    return t_adj


def main():
    # Joint variables
    theta1, theta2, theta3, theta4, theta5, theta6 = symbols('1 2 3 4 5 6')

    # Modified DH parameters (Craig's convention)
    dh = [[0, 0, 113.25, theta1],
          [pi / 2, 0, 0, theta2 - (pi / 2)],
          [0, 200, 0, pi/2],
          [0, 50, 0, theta3 - pi],
          [0, 200, 0, theta4 - pi/2],
          [pi / 2, 0, 0, theta5],
          [0, 0, 17.415, 0]]
    #[[0, 0, 113.25, theta1],
         # [pi / 2, 0, 0, theta2],
         # [0, 200, 0, 0],
         # [0, 50, 0, theta3],
         # [0, 200, 0, theta4],
         # [pi / 2, 0, 0, theta5],
         # [0, 0, 174.15, theta6]]

    # Transformation from the end effector frame {6} to the base frame {0}
    t0 = eye(4)
    for i in range(len(dh)):
        ti = frameTransform(dh[i][ALPHA], dh[i][A], dh[i][D], dh[i][THETA])

        '''print("\nTranslation of frame {0} in frame {1}".format(i+1,i))
        print("-----------------------------------------")
        for row in range( 4 ):
            print( "\t", ti[row,:] )
        print("\n")'''

        t0 = t0 @ ti

    t0 = simplify(t0)

    p0 = t0[0:3, 3]
    p1 = Matrix.vstack(p0, Matrix([[theta5], [theta2 + theta3 + theta4]]))


    print("\nPosition of frame 6 in frame 0:\n")
    for i in range(3):
        print("\t", p0[i])

    # Jacobian: Differentiate translation column of T{0}{6} w.r.t. thetas
    j0 = p1.jacobian(Matrix([theta1, theta2, theta3, theta4, theta5]))
    j0 = simplify(j0)
    print("\nJacobian:\n")
    for row in range(j0.shape[0]):
        for col in range(j0.shape[1]):
            pprint("\tJ[{0}][{1}] = {2}".format(row, col, j0[row, col]))
        print()

    # Determinant of the Jacobian
   # j0det = simplify(j0.det())
    #print("Determinant:\n")
    #print("\t", j0det, "\n")




if __name__ == "__main__":
    main()