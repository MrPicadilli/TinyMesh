// SDF

#pragma once

#include <QtCore/QVector>
#include <implicits.h>
#include <iostream>
#include "Node.h"

class SDF : public AnalyticScalarField
{
public:
	SDF();
	SDF(Node* n);
	double Value(const Vector& p) const;
protected:
	Node* root = nullptr;
};
