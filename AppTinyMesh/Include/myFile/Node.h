// Node

#pragma once

#include <QtCore/QVector>
#include "myFile/Transform.h"

#include <iostream>
#include "mathematics.h"

class Node
{
protected:
public:
	virtual double Value(const Vector& p) const = 0;
};



