#pragma once
class DataSet
{
private:
	
public:
	virtual void cradleToHomeAngles(float duration);
	virtual void DrawAngles(float duration);
	virtual void homeToCradleAngles(float duration);
	virtual void CalculateMotorAngles(int actionIndex);
};
