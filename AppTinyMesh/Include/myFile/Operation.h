// Node

#pragma once
#include "Node.h"
#include "FastNoiseLite.h"

class Operation : public Node
{
public:
	virtual double Value(const Vector& p) const = 0;
};


class Union : public Operation
{
public:
	Union();
	Union(Node* a, Node* b);
	double Value(const Vector& p) const;

protected:
	Node* a;
	Node* b;
};

class Smooth_union : public Operation
{
public:
	Smooth_union();
	Smooth_union(Node* a, Node* b, double offset);
	double Value(const Vector& p) const;

protected:
	Node* a;
	Node* b;
	double offset;
};

class Intersection : public Operation
{
public:
	Intersection();
	Intersection(Node* a, Node* b);
	double Value(const Vector& p) const;

protected:
	Node* a;
	Node* b;
};

class Smooth_intersection : public Operation
{
public:
	Smooth_intersection();
	Smooth_intersection(Node* a, Node* b,double offset);
	double Value(const Vector& p) const;

protected:
	Node* a;
	Node* b;
	double offset;
};

class Substract : public Operation
{
public:
	Substract();
	Substract(Node* a, Node* b);
	double Value(const Vector& p) const;

protected:
	Node* a;
	Node* b;
};

class Smooth_substract : public Operation
{
public:
	Smooth_substract();
	Smooth_substract(Node* a, Node* b,double offset);
	double Value(const Vector& p) const;

protected:
	Node* a;
	Node* b;
	double offset;
};

//f(a rond B)
class Melange : public Operation
{
public:
	
	Melange();
	Melange(Node* a, Node* b);
	double Value(const Vector& p) const;

protected:
	Node* a;
	Node* b;
};

class Deformation : public Operation
{
public:

	Deformation();
	Deformation(Node* a, Transform b);
	double Value(const Vector& p) const;

protected:
	Node* a;
	Transform b;
};



class Torsion_helico : public Operation
{
public:
	Torsion_helico();
	Torsion_helico(Node* A, double force_deformation);
	double Value(const Vector& p) const;

protected:
	Node* A;
	double force_deformation;
};


class Noise : public Operation
{
public:
	Noise();
	Noise(Node* N);
	double Value(const Vector& p) const;

protected:
	Node* N;

};