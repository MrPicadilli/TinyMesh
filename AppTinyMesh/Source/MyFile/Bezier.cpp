#include "myFile/Bezier.h"
#include <random>
#include <iomanip>
Bezier::Bezier()
{

}

Bezier::Bezier(int n, int m, int x_max, int y_max) {
	this->n = n;
	this->m = m;
	this->x_max = x_max;
	this->y_max = y_max;
	double pas_x = 0.0;
	double pas_y = 0.0;
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> distr(-1, 1);
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			points_controle.push_back(Vector(pas_x, pas_y, distr(eng)));
			pas_y += 1;
		}
		pas_y = 0.0;
		pas_x += 1;
	}


}


int Bezier::Index(int i, int j)
{
	return i * n + j;
}

Vector Bezier::castlejau(float s, float t)
{

	QVector<Vector> tempo = points_controle;
	QVector<Vector> pc_y;
	QVector<Vector> pc_x;
	for (size_t a = 0; a < n; a++)
	{

		tempo = points_controle;
		for (size_t j = 1; j < m; j++)
		{
			for (size_t i = 0; i < m - j; i++)
			{
				tempo[a*m +i ] = t * tempo[a * m + i + 1] + (1 - t) * tempo[a * m + i ];

			}

		}
		pc_x.push_back(tempo[a*m]);
	}
	for (int j = 1; j < n; j++)
	{
		for (int i = 0; i < n - j; i++)
		{
			pc_x[i] = s * pc_x[i + 1] + (1 - s) * pc_x[i];
		}
	}

	return pc_x[0];
}

void Bezier::Create_Mesh(QVector<Vector>& points, QVector<int>& indice)
{
	int ind = 0;
	double pas_x = 0.0;
	double pas_y = 0.0;


	for (size_t i = 0; i < x_max; i++)
	{
		for (size_t j = 0; j < y_max; j++)
		{
			points.push_back(castlejau(i/(float)x_max, j / (float)y_max));
		}

	}

	std::cout << "c'est passe" << std::endl;

	for (size_t i = 0; i < x_max-1; i++)
	{
		for (size_t j = 0; j < y_max-1; j++)
		{
			indice.push_back(j + i * x_max);
			indice.push_back(j+1 + i* x_max);
			indice.push_back(j +( (i+1) * x_max));

			indice.push_back(j + 1 + i * x_max);
			indice.push_back(1+j + ((i + 1) * x_max));
			indice.push_back(j + ((i + 1) * x_max));

		}

	}

}

void Bezier::Twist(QVector<Vector>& points, double force_deformation)
{
	for (size_t i = 0; i < points.size(); i++)
	{
		
		double c = cos(force_deformation * points[i][1]);
		double s = sin(force_deformation * points[i][1]);
		double xdef = points[i][0] * c - points[i][2] * s;
		double ydef = points[i][0] * s + points[i][2] * c;
		points[i][0] = xdef;
		points[i][2] = points[i][1];

		points[i][1] = ydef;

	}


}
