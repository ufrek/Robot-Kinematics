#include "Jacobian.h"
#include "Eigen/Dense"
#include <iostream>
#include "ForwardKinematics.h"



Eigen::Matrix<double, 4, 4> Jacobian::getJacobian(double* theta)
{
    std::vector<double> angles;
    for (int i = 0; i < 6; i++)
    {
        angles.push_back(ForwardKinematics::torad(theta[i]));
    }

    int rows = 4, cols = 4;

    Eigen::MatrixXd m(rows, cols);
    //J[3, :] and J[:, 4] have been deleted
    m << (Eigen::Matrix4d() <<
        ((-20.0 * sin(angles[1]) - 5.0 * cos(angles[1]) + 20.0 * cos(angles[1] +
            angles[3]) - 17.415 * cos(angles[1] + angles[3] + angles[4])) * sin(angles[0])), //J[0, 0]

            ((-5.0 * sin(angles[1]) + 20.0 * sin(angles[1] + angles[3]) -
                17.415 * sin(angles[1] + angles[3] + angles[4]) + 20.0 * cos(angles[1]))* cos(angles[1])), //J[0,1]

        ((20.0 * sin(angles[1] + angles[3]) - 17.415 * sin(angles[1] + angles[3] +
            angles[4])) * cos(angles[0])), //J[0,2]

        (-17.415 * sin(angles[1] + angles[3] + angles[4]) * cos(angles[0])), //J[0,3]


        ((20.0 * sin(angles[1]) + 5.0 * cos(angles[1]) - 20.0 * cos(angles[1] +
            angles[3]) + 17.415 * cos(angles[1] + angles[3] + angles[4])) * cos(angles[0])), //J[1,0]

        ((-5.0 * sin(angles[1]) + 20.0 * sin(angles[1] + angles[3]) -
            17.415 * sin(angles[1] + angles[3] + angles[4]) + 20.0 * cos(angles[1])) * sin(angles[0])), //J[1,1]

        ((20.0 * sin(angles[1] + angles[3]) - 17.415 * sin(angles[1] + angles[3] +
            angles[4])) * sin(angles[0])), //J[1,2]

        (-17.415 * sin(angles[0]) * sin(angles[1] + angles[3] + angles[4])), //J[1,3]

        0, //J[2,0]

        (20.0 * sin(angles[1]) + 5.0 * cos(angles[1]) - 20.0 * cos(angles[1] +
            angles[3]) + 17.415 * cos(angles[1] + angles[3] + angles[4])), //J[2,1]

        (-20.0 * cos(angles[1] + angles[3]) + 17.415 * cos(angles[1] + angles[3] +
            theta[4])), //J[2,2]

        (17.415 * cos(angles[1] + angles[3] + angles[4])), //J[2,3]

        0, //J[4,0]
        1, //J[4,1] 
        1, // J[4,2]
        1).finished(); //J[4,3]
       
    //std::cout << m;
      
    return m;
}

	
Eigen::MatrixXd Jacobian::getChangeInAngles(double* currentAngles, std::vector<double> deltaPositions)
{
    
    Eigen::MatrixXd jacobian = Jacobian::getJacobian(currentAngles);
    double determinant = std::abs(jacobian.determinant());
    std::cout << "\nDeterminant: " << determinant << "\n";

    if (determinant > 1)
    {
        Eigen::Matrix4d jInverse = jacobian.inverse();

        
        Eigen::Matrix<double, 4, 1>  m;
        m <<  (deltaPositions[0], deltaPositions[1], deltaPositions[2], deltaPositions[3]);

        // Change in positions for x y and z.
        // Worry about roll later.
        
//TODO: there is some kind of size error here I think
        //double deltaAngles = jInverse;
        Eigen::MatrixXd deltaAngles = jInverse * m;
        

        return deltaAngles;
        
    }
    else
    {
        std::cout << "Jacobian determinant too small";
        Eigen::Matrix<double, 4, 1>  m;
        m << (-999,-999, -999, -999);
        return m;
    }
}
