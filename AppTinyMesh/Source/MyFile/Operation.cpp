#include "myFile/Operation.h"

Union::Union()
{
}

Union::Union(Node* a, Node* b)
{
	this->a = a;
	this->b = b;
}

double Union::Value(const Vector& p) const
{
	return std::min(a->Value(p),b->Value(p));
}

Smooth_union::Smooth_union()
{
}

Smooth_union::Smooth_union(Node* a, Node* b, double offset)
{
	this->a = a;
	this->b = b;
	this->offset = offset;
}

double Smooth_union::Value(const Vector& p) const
{
	double va = a->Value(p);
	double vb = b->Value(p);
	double r = std::max(va, vb) - std::min(va, vb);
	double h = std::max(offset - r, 0.0)/offset;
	double off = (offset * pow(h, 3))/6.0;
	return std::min(va, vb) - off;

}

Intersection::Intersection()
{
}

Intersection::Intersection(Node* a, Node* b)
{
	this->a = a;
	this->b = b;
}

double Intersection::Value(const Vector& p) const
{
	return std::max(a->Value(p), b->Value(p));
}

Smooth_intersection::Smooth_intersection()
{
}

Smooth_intersection::Smooth_intersection(Node* a, Node* b, double offset)
{
	this->a = a;
	this->b = b;
	this->offset = offset;
}

double Smooth_intersection::Value(const Vector& p) const
{
	double va = a->Value(p);
	double vb = b->Value(p);
	double r = std::max(va, vb) - std::min(va, vb);
	double h = std::max(offset - r, 0.0) / offset;
	double off = (offset * pow(h, 3)) / 6.0;
	return std::max(a->Value(p), b->Value(p)) + off;
}


Substract::Substract()
{
}

Substract::Substract(Node* a, Node* b)
{
	this->a = a;
	this->b = b;
}

double Substract::Value(const Vector& p) const
{
	return std::max(-a->Value(p), b->Value(p));
}

Smooth_substract::Smooth_substract()
{
}

Smooth_substract::Smooth_substract(Node* a, Node* b, double offset)
{
	this->a = a;
	this->b = b;
	this->offset = offset;
}

double Smooth_substract::Value(const Vector& p) const
{
	double va = a->Value(p);
	double vb = b->Value(p);
	double r = std::max(va, vb) - std::min(va, vb);
	double h = std::max(offset - r, 0.0) / offset;
	double off = (offset * pow(h, 3)) / 6.0;
	return std::max(-a->Value(p), b->Value(p)) - off;
}

Melange::Melange()
{
}

Melange::Melange(Node* a, Node* b)
{
	this->a = a;
	this->b = b;
}

double Melange::Value(const Vector& p) const
{
	return a->Value(p) + b->Value(p);
}


Deformation::Deformation()
{
}

Deformation::Deformation(Node* a, Transform b)
{
	this->a = a;
	this->b = b;
}

double Deformation::Value(const Vector& p) const
{
	
	return a->Value(b(p));
}



Torsion_helico::Torsion_helico()
{
}

Torsion_helico::Torsion_helico(Node* A, double force_deformation)
{
	this->A = A;
	this->force_deformation = force_deformation;

}

double Torsion_helico::Value(const Vector& p) const
{
	double c = cos(force_deformation * p[1]);
	double s = sin(force_deformation * p[1]);
	double xdef = p[0] * c + p[2] * (-s);
	double ydef = p[0] * s + p[2] * c;
	return A->Value(Vector(xdef, ydef, p[1]));
}


Noise::Noise()
{

}

Noise::Noise(Node* N)
{
	this->N = N;
}

double Noise::Value(const Vector& p) const
{
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	float noiseData = noise.GetNoise((float)p[0], (float)p[2], (float)p[1]);
	return N->Value(p) + Norm(p - noiseData * p)	;
}
