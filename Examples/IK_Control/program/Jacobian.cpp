#include "Jacobian.h"
#include "Eigen/Dense"
#include <iostream>

Eigen::Matrix<double, 4, 4> Jacobian::getJacobian(std::vector<double> theta)
{
    int rows = 4, cols = 4;

    Eigen::MatrixXf m(rows, cols);
    //J[3, :] and J[:, 4] have been deleted
    m << (Eigen::Matrix4d() <<
        ((-20.0 * sin(theta[1]) - 5.0 * cos(theta[1]) + 20.0 * cos(theta[1] +
            theta[3]) - 17.415 * cos(theta[1] + theta[3] + theta[4])) * sin(theta[0])), //J[0, 0]

            ((-5.0 * sin(theta[1]) + 20.0 * sin(theta[1] + theta[3]) -
                17.415 * sin(theta[1] + theta[3] + theta[4]) + 20.0 * cos(theta[1]))* cos(theta[1])), //J[0,1]

        ((20.0 * sin(theta[1] + theta[3]) - 17.415 * sin(theta[1] + theta[3] +
            theta[4])) * cos(theta[0])), //J[0,2]

        (-17.415 * sin(theta[1] + theta[3] + theta[4]) * cos(theta[0])), //J[0,3]


        ((20.0 * sin(theta[1]) + 5.0 * cos(theta[1]) - 20.0 * cos(theta[1] +
            theta[3]) + 17.415 * cos(theta[1] + theta[3] + theta[4])) * cos(theta[0])), //J[1,0]

        ((-5.0 * sin(theta[1]) + 20.0 * sin(theta[1] + theta[3]) -
            17.415 * sin(theta[1] + theta[3] + theta[4]) + 20.0 * cos(theta[1])) * sin(theta[0])), //J[1,1]

        ((20.0 * sin(theta[1] + theta[3]) - 17.415 * sin(theta[1] + theta[3] +
            theta[4])) * sin(theta[0])), //J[1,2]

        (-17.415 * sin(theta[0]) * sin(theta[1] + theta[3] + theta[4])), //J[1,3]

        0, //J[2,0]

        (20.0 * sin(theta[1]) + 5.0 * cos(theta[1]) - 20.0 * cos(theta[1] +
            theta[3]) + 17.415 * cos(theta[1] + theta[3] + theta[4])), //J[2,1]

        (-20.0 * cos(theta[1] + theta[3]) + 17.415 * cos(theta[1] + theta[3] +
            theta[4])), //J[2,2]

        (17.415 * cos(theta[1] + theta[3] + theta[4])), //J[2,3]

        0, //J[4,0]
        1, //J[4,1] 
        1, // J[4,2]
        1).finished(); //J[4,3]
       
    std::cout << m;
      
    return m;
}

	
double Jacobian::getChangeInAngles(std::vector<double> currentPositions, std::vector<double> deltaPositions)
{
    
    Eigen::Matrix<double, 4, 4> jacobian = Jacobian::getJacobian(currentPositions);

    if (std::abs(jacobian.determinant()) > .0001)
    {
        Eigen::Matrix4d jInverse = jacobian.inverse();
        Eigen::Matrix<double, 4, 1>  m;

//TODO: fix delta roll as last element with correct value
        m << (Eigen::Matrix<double, 4, 1>() << deltaPositions[0], deltaPositions[1], deltaPositions[2], .5f).finished();

//TODO: there is some kind of size error here I think
        double deltaAngles = jInverse.dot(m);
        return deltaAngles;
        
    }
    else
    {
        std::cout << "Jacobian determinant too small";
        return -999;
    }
}
