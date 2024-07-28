#include "myFile/SDF.h"

SDF::SDF()
{
}

SDF::SDF(Node* n)
{
	this->root = n;
}

double SDF::Value(const Vector& p) const
{
	return root->Value(p);
}
