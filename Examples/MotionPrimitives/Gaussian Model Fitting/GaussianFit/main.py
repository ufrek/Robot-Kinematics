import sys

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
np.set_printoptions( precision=2 )

#Gaussian Model Fitting: 
# #Takes a csv of recorded behavior and fits Gaussian curves over the entire duration of the behavior.

#The recorded csv file format should have 6 values per line, one for each motor angle in the robot arm.

colNames = ['m1', 'm2', 'm3', 'm4', 'm5', 'm6', 'count', 'time']
motorData = pd.read_csv("data/DrawLineonPaper.csv", sep=",")  # ,  usecols=colNames

featureCols = ['m1',  'm2', 'm3',  'm4', 'm5', 'm6',  'time']
#select relevant columnns here
#x = np.array(motorData[motorData.columns[0:5]])
#x = motorData[featureCols].values
#time

n = 738  # input points
k = 14 # changes in direction
fig, ax = plt.subplots(6,1)

def reset_my_index(df):
  res = df[::-1].reset_index(drop=True)
  return(res)

def plotMotor(index):

    Y = motorData[motorData.columns[index]]   # change the column or motor you are analyzing
    np.reshape(Y, Y.size)
    #x = x.values




    #the backwards sigmoid function. This reverses it so it models correctly
    #Y = reset_my_index(Y)


    X = np.linspace( 0, 1, n ).reshape((n,1))


    A = np.ones((n,1))                          # A = input matrix, used in regression to make predictions (and solve for W)

    center = np.linspace(0,1,k)                     # center = the means that define the position of each kernel
    std = np.ones(center.shape)*(1/len(center))     # std = standard deviations that define the width of each kernel

    for i in range( k ):
      G = np.exp( -(X-center[i])**2 / (2*std[i]**2))   # G = Y-cordinates of the i-th gaussian for each time in T
      A = np.hstack((G, A))

      #ax[index].plot(X, G, '-', label=f"kernel {i}")    #plots each individual gaussian


    W = np.linalg.pinv( A.T @ A ) @ A.T @ Y
    Y_pred = A @ W




    ax[index].plot( X, Y, '-k', linewidth=3, label="Angle")
    ax[index].plot( X, Y_pred, '--c', linewidth=3, label="Angle_pred")
    ax[index].plot( True )
    ax[index].set_ylabel("Motor " + str(index))
    ax[index].set_xlabel("Time")

    #print(f"Motor Angles: ")

    #for y in Y.values:
        #print(f"{y} , ")

    #print(f"Weights: {W.T}")

    R = Y_pred - Y
    RSS = np.sum(R**2)
    TSS = np.sum((Y - np.mean(Y))**2)
    R2 = 1 - RSS / TSS
    RMSE = np.sqrt(RSS/n)
   # print(f"RSS  = {RSS:.3f}   <-- residual sum of squares" )
    #print(f"R^2  = {R2:.3f}   <-- coefficient of determination" )
   # print(f"RMSE = {RMSE:.3f}   <-- root mean squared error" )

    #print("Motor : " + str(index))
    #print("Weights: {")

    np.array(W)
    np.set_printoptions(formatter={'float': lambda x: "{0:0.10f}".format(x)})
    #print(W)


    #print("}; \n")


    #print("Centers: {")
    np.array(center)
   # print(center)

    #print("}; \n")

    #print("Deviations: {")
    np.array(std)
   # print(std)

   # print("} \n")

    for i in range(14):
        print(W[i], end=", ")

        print(center[i], end=", ")
        print(std[i], end=",\n")


print("14,")
plotMotor(0)
plotMotor(1)
plotMotor(2)
plotMotor(3)
plotMotor(4)
plotMotor(5)






plt.legend()
plt.show()






