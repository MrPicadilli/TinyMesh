// Node

#pragma once

#include "Node.h"

class Primitive: public Node
{
public:
	virtual double Value(const Vector& p) const = 0;
};


// Sphere

class Sphere : public Primitive
{
public:
	Sphere();
	Sphere(Vector pos, double rayon);
	double Value(const Vector& p) const;

protected:
	Vector centre;
	double rayon;
};

// Capsule

class Capsule : public Primitive
{
public:
	Capsule();
	Capsule(Vector A, Vector B, double rayon_bout);
	double Value(const Vector& p) const;

protected:
	Vector A, B;
	double rayon_bout;
};

// Cylinder

class Infinite_cylinder : public Primitive
{
public:
	Infinite_cylinder();
	Infinite_cylinder(Vector A, Vector B, double rayon_bout);
	double Value(const Vector& p) const;

protected:
	Vector A, B;
	double largeur;
};

//Cylindre capped

class Cylinder : public Primitive
{
public:
	Cylinder();
	Cylinder(Vector A, Vector B, double rayon_bout);
	double Value(const Vector& p) const;

protected:
	Vector A, B;
	double largeur;
};

class Cone_capped : public Primitive
{
public:
	Cone_capped();
	Cone_capped(Vector A, Vector B, double r1, double r2);
	double Value(const Vector& p) const;

protected:
	double r1, r2;
	Vector A, B;
};


class Seed : public Primitive
{
public:
	Seed();
	Seed(Vector A, Vector B, double rayon);
	double Value(const Vector& p) const;

protected:
	double rayon;
	Vector A, B;
};



