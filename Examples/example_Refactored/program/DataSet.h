#pragma once
class DataSet
{
private:
	
public:
	virtual void cradleToHomeAngles(float duration) = 0;
	 virtual void DrawAngles(float duration) = 0;
	 virtual void homeToCradleAngles(float duration) = 0;
	 virtual void  CalculateMotorAngles(int actionIndex) = 0;
};
