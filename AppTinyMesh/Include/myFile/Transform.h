#pragma once
#include <math.h>
#include "mathematics.h"


# define M_PI           3.14159265358979323846  /* pi */

float radians(const float deg);
float degrees(const float rad);

struct Transform
{
    Transform(
        const float t00 = 1, const float t01 = 0, const float t02 = 0, const float t03 = 0,
        const float t10 = 0, const float t11 = 1, const float t12 = 0, const float t13 = 0,
        const float t20 = 0, const float t21 = 0, const float t22 = 1, const float t23 = 0,
        const float t30 = 0, const float t31 = 0, const float t32 = 0, const float t33 = 1);

    Transform(const Vector& x, const Vector& y, const Vector& z, const Vector& w);

    Transform& column(const unsigned id, const float t0, const float t1, const float t2, const float t3);

    Transform& row(const unsigned id, const float t0, const float t1, const float t2, const float t3);


    Transform& column_major(const float matrix[16]);

    Transform& row_major(const float matrix[16]);

    Vector operator[] (const unsigned c) const;

    Vector operator() (const Vector& v) const;

    Transform operator() (const Transform& b) const;

    Transform transpose() const;
    Transform inverse() const;
    Transform normal() const;

    const float* data() const { return &m[0][0]; }

    float m[4][4];
};

Transform Identity();

Transform Transpose(const Transform& m);
Transform Inverse(const Transform& m);
Transform Normal(const Transform& m);

Transform Scale(const float x, const float y, const float z);
inline Transform Scale(const float s) { return Scale(s, s, s); }

Transform Translation(const Vector& v);
Transform Translation(const float x, const float y, const float z);

Transform RotationX(const float angle);
Transform RotationY(const float angle);
Transform RotationZ(const float angle);

Transform compose_transform(const Transform& a, const Transform& b);
Transform operator* (const Transform& a, const Transform& b);

#include <iostream>

inline std::ostream& operator<<(std::ostream& o, const Transform& t)
{
    o << t.m[0][0] << " " << t.m[0][1] << " " << t.m[0][2] << " " << t.m[0][3] << " " << std::endl;
    o << t.m[1][0] << " " << t.m[1][1] << " " << t.m[1][2] << " " << t.m[1][3] << " " << std::endl;
    o << t.m[2][0] << " " << t.m[2][1] << " " << t.m[2][2] << " " << t.m[2][3] << " " << std::endl;
    o << t.m[3][0] << " " << t.m[3][1] << " " << t.m[3][2] << " " << t.m[3][3] << " " << std::endl;
    return o;
}


