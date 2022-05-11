# Motion Primitives
In this project, we record a behavior that moves the robot arm fro the cradle to the rest position and calculate Gaussian Mixture Models to fit change in angles over time for each motor. We then take these models and make the robot arm move based on these models. We have combined 3 different actions (cradle to home position, drawing a line, home position to cradle) and used interpolation bettween the end of one action and the beginnning of the next action. 

In the Motion Primitives Folder, there is a project Folder titled "Gaussian Mixture Model" that contains a python file to run Gaussian Mixture Model fitting to a provided csv file. In this example, we used the Record project from the Programming By Demonstration to record a training data set so that we can fit a Gaussian Mixture Model to it.

We then copy the output of the Gaussian Mixture Model Fitting into the Motion Primitive project and use a loop from 0 to 1 with a small incrementing step to iterate over each of the 6 Gaussian Mixture Models and update the output angles of these models to each motor. To put things simply, we are playing back recorded actions by using a calculated model of these actions.

### GMM Motor Data Visualization
![GMM Data](https://github.com/CoachGeorgia/Robot-Kinematics/blob/main/docs/source/GMM%20Visualization%20Home%20to%20Cradle%20S.png?raw=true)
