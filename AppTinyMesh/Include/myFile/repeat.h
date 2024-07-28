#pragma once
#include "Operation.h"
#include "Primitive.h"

// 11 novembre
class Infinite_repeat
{
public:

	Infinite_repeat();
	Infinite_repeat(Node* a, int etape);
	Node *repeater(Node *n, int etape, float rayon, float tour) const;

protected:
	Node* a;
	int etape;
};

class Clone : public Operation
{
public:
	Clone();
	Clone(Node* a, Transform b);
	double Value(const Vector& p) const;

protected:
	Node* a;
	Transform t;
};

class Ray_marching
{
public:
	Ray_marching();
	Ray_marching(Node* A, Vector origine);
	Vector Intercept(Vector direction);
protected:
	Node* A;
	Vector origine;
};

class Sphere_tracing
{
public:
	Sphere_tracing();
	Sphere_tracing(Node* A, Vector origine);
	Vector Intercept(Vector direction);
protected:
	Node* A;
	Vector origine;
};

class Ray_marching_machine_gun
{
public:
	Ray_marching_machine_gun();
	Ray_marching_machine_gun(Node* A);
	Node* add_matiere_ray_marching(int number_of_shot);
	Node* add_matiere_sphere_tracing(int number_of_shot);
	Node* remove_matiere_ray_marching (int number_of_shot);
	Node * remove_matiere_sphere_tracing(int number_of_shot);
protected:
	Node* A;
};

