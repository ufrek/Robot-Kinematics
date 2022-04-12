#pragma once
#ifndef TRAININGDATA_H
#define TRAININGDATA_H
#include "DataSet.h"
class TrainingData :
    public DataSet
{
public:
    TrainingData();
    void importAction(); //file name

private:
};
#endif

