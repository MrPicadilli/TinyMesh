#include "myFile/repeat.h"
#include <random>


Infinite_repeat::Infinite_repeat()
{
}

Infinite_repeat::Infinite_repeat(Node* a, int etape)
{
	this->a = a;
	this->etape = etape;
}

Node* Infinite_repeat::repeater(Node* n, int etape,float rayon, float tour) const
{

	Transform tourne_y, tourne_x, tourne_z;
	for (int i = etape; i >= 0; i--) {
		tourne_y = Translation(0, 0, rayon);
		tourne_y = tourne_y(RotationY((360 / etape) * i));
		tourne_z = Translation(0, rayon, 0);
		tourne_z = tourne_z(RotationZ((360 / etape) * i));
		tourne_x = Translation(0, rayon,0);
		tourne_x = tourne_x(RotationY(45));
		tourne_x = tourne_x(RotationY((360 / etape) * i));

		n = new Union(new Deformation(a, tourne_z), n);


	}
	Node* trinity = n;
	for (int i = tour; i >= 0; i--) {
		n = new Union(new Deformation(trinity, RotationX((360 / tour) * i) ), n);
	}
	return n;

}


Clone::Clone()
{
}

Clone::Clone(Node* a, Transform b)
{
	this->a = a;
	this->t = b;
}

double Clone::Value(const Vector& p) const
{
	return std::min(a->Value(p), a->Value(t(p)));
}

Ray_marching::Ray_marching() {

}
Ray_marching::Ray_marching(Node* a, Vector origine) {
	this->A = a;
	this->origine = origine;
}
Vector Ray_marching::Intercept(Vector direction) {
	double y = 0.1;
	Vector avancement = origine;
	avancement =avancement + 0.1 * direction;
	int limite=0;
	while (A->Value(avancement) > 0 && limite < 250)
	{
		avancement = avancement + 0.1 * direction;
		limite++;

	}


	return limite < 250 ? avancement : Vector(0,0,0);
}



Sphere_tracing::Sphere_tracing() {

}
Sphere_tracing::Sphere_tracing(Node* a, Vector origine) {
	this->A = a;
	this->origine = origine;
}
Vector Sphere_tracing::Intercept(Vector direction) {

	Vector avancement = origine;
	double y = 0.0;

	int limite = 0;
	while (A->Value(avancement) > 0 && limite < 50)
	{
		y = 0.02 * A->Value(avancement);
		if (y < 0.01) {
			y = 0.01;
		}
		else if (y > 1) {
			y = 0.5;
		}
		

		avancement = avancement + y * direction;
		limite++;
	}

	return limite < 50 ? avancement : Vector(0, 0, 0);
}



Ray_marching_machine_gun::Ray_marching_machine_gun() {

}
Ray_marching_machine_gun::Ray_marching_machine_gun(Node* a) {
	this->A = a;
}

Node* Ray_marching_machine_gun::add_matiere_ray_marching(int number_of_shot) {
	double lower_bound = -5;
	double upper_bound = 5;
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	Vector toucher;
	double a_random_double = unif(re);
	Vector origine, direction;
	for (int i = 0; i < number_of_shot; i) {
		a_random_double = unif(re);
		origine = Vector(-10, unif(re), unif(re));
		Ray_marching r1 = Ray_marching(A, origine);
		direction = Vector(10, unif(re), unif(re));
		toucher = r1.Intercept(direction);
		if (toucher != Vector(0, 0, 0)) {
			A = new Union(new Sphere(toucher, 0.5), A);
			i++;
		}
	}

	return A;
}
Node* Ray_marching_machine_gun::add_matiere_sphere_tracing(int number_of_shot) {
	double lower_bound = -5;
	double upper_bound = 5;
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	Vector toucher;
	double a_random_double = unif(re);
	Vector origine, direction;
	for (int i = 0; i < number_of_shot; i) {
		a_random_double = unif(re);
		origine = Vector(-10, unif(re), unif(re));
		Sphere_tracing r1 = Sphere_tracing(A, origine);
		direction = Vector(10, unif(re), unif(re));
		toucher = r1.Intercept(direction);
		if (toucher != Vector(0, 0, 0)) {
			A = new Union(new Sphere(toucher, 0.5), A);
			i++;
		}
	}

	return A;
}
Node* Ray_marching_machine_gun::remove_matiere_ray_marching(int number_of_shot) {
	double lower_bound = -5;
	double upper_bound = 5;
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	Vector toucher;
	double a_random_double = unif(re);
	Vector origine, direction;
	for (int i = 0; i < number_of_shot; i) {
		a_random_double = unif(re);
		origine = Vector(-10, unif(re), unif(re));
		Ray_marching r1 = Ray_marching(A, origine);
		direction = Vector(10, unif(re), unif(re));
		toucher = r1.Intercept(direction);
		if (toucher != Vector(0, 0, 0)) {
			A = new Substract(new Sphere(toucher, 0.5), A);
			i++;
		}
	}

	return A;
}
Node* Ray_marching_machine_gun::remove_matiere_sphere_tracing(int number_of_shot) {
	double lower_bound = -5;
	double upper_bound = 5;
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	Vector toucher;
	double a_random_double = unif(re);
	Vector origine, direction;
	for (int i = 0; i < number_of_shot; i) {
		a_random_double = unif(re);
		origine = Vector(-10, unif(re), unif(re));
		Sphere_tracing r1 = Sphere_tracing(A, origine);
		direction = Vector(10, unif(re), unif(re));
		toucher = r1.Intercept(direction);
		if (toucher != Vector(0, 0, 0)) {
			A = new Substract(new Sphere(toucher, 0.5), A);
			i++;
		}
	}

	return A;
}
