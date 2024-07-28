#include "qte.h"

#pragma once
class Bezier
{
public:
	int n, m;
	int x_max, y_max;
	QVector<Vector> points_controle;

	Bezier();
	Bezier(int n, int m, int x_max, int y_max);

	int Index(int i, int j);
	Vector castlejau(float s, float t);
	void Create_Mesh(QVector<Vector>& points, QVector<int>& indice);
	void Twist(QVector<Vector>& points, double force_deformation);
};

