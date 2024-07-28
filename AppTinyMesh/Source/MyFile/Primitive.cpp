#include "myFile/Primitive.h"
# define M_PI           3.14159265358979323846  /* pi */

double dot(Vector a, Vector b) {
	return  a[0] * b[0] + a[1] * b[1] + a[2] * b[2];

}

Sphere::Sphere()
{
	this->rayon = 1;
	this->centre = Vector(0, 0, 0);
}

Sphere::Sphere(Vector pos, double rayon)
{
	this->centre = pos;
	this->rayon = rayon;
}

double Sphere::Value(const Vector& p) const
{
	return Norm(p - centre) - rayon;
}

Capsule::Capsule()
{
	this->rayon_bout = 1;
	this->A = Vector(0, 0, 0);
	this->B = Vector(0, 0, 0);

}

Capsule::Capsule(Vector A, Vector B, double rayon_bout)
{
	this->A = A;
	this->B = B;
	this->rayon_bout = rayon_bout;
}

double Capsule::Value(const Vector& p) const
{
	Vector pa = p - A;
	Vector ba = B - A;
	double h = 1;
	h = std::clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);

	
	return Norm(pa - ba * h) - rayon_bout;
}

Infinite_cylinder::Infinite_cylinder() {
	this->largeur = 1;
	this->A = Vector(0, 0, 0);
	this->B = Vector(0, 0, 0);

}


Infinite_cylinder::Infinite_cylinder(Vector A, Vector B, double largeur)
{
	this->A = A;
	this->B = B;
	this->largeur = largeur;
}
double Infinite_cylinder::Value(const Vector& p) const
{
	Vector ba = B - A;
	return Norm(Vector(p[0] - A[0],0, p[2] - A[2])) - largeur;
}


Cylinder::Cylinder()
{
	this->largeur = 1;
	this->A = Vector(0, 0, 0);
	this->B = Vector(0, 0, 0);

}

Cylinder::Cylinder(Vector A, Vector B, double largeur)
{
	this->A = A;
	this->B = B;
	this->largeur = largeur;
}

double Cylinder::Value(const Vector& p) const
{
	Vector ap = A - p;
	Normalize(ap);

	Vector bp = B - p;
	Vector ba = B - A;
	Vector ab = A - B;
	Vector pa = p - A;
	double h = std::clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
	double gauche = -1;
	double droite = -1;
	double interieur = -1;
	if (h == 0.0) {
		//fin au point B
		gauche = dot(bp, ba);
	}
	if (h == 1.0) {
		//fin au point A
		droite = dot(ap, ab);
	}
	else {
		interieur = Norm(pa - (ba * h)) - largeur;
	}
	return std::max(std::max(interieur, gauche), droite);
;
	
}


Cone_capped::Cone_capped()
{
	this->r1 = 1;
	this->r2 = 2;
	this->A = Vector(0, 0, 0);
	this->B = Vector(0, 0, 0);

}

Cone_capped::Cone_capped(Vector A, Vector B,double r1,double r2)
{
	this->A = A;
	this->B = B;
	this->r1 = r1;
	this->r2 = r2;
}



double Cone_capped::Value(const Vector& p) const
{
	Vector pa = p - A;
	Vector ba = B - A;
	double h = std::clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
	double surface = h;
	if (h == 1.0) {
		surface = 0.0;
	}
	double dede = Norm((p-A) - (B-A)*h ) - r2 * surface;
	return dede;
}

Seed::Seed()
{
	this->rayon = 1;
	this->A = Vector(0, 0, 0);
	this->B = Vector(0, 0, 0);

}

Seed::Seed(Vector A, Vector B, double rayon)
{
	this->A = A;
	this->B = B;
	this->rayon = rayon;
}

double Seed::Value(const Vector& p) const
{
	return Norm(Vector(p[0] - this->A[0], 0, p[2] - this->A[2])) - rayon + Norm(p - B) - rayon;
}

