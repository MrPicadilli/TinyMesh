
#include <cassert>
#include <cstdio>
#include <cmath>
#include <algorithm>

#include "myFile/Transform.h"


float radians(const float deg)
{
    return ((float)M_PI / 180.f) * deg;
}

float degrees(const float rad)
{
    return (180.f / (float)M_PI) * rad;
}

Transform::Transform(
    const float t00, const float t01, const float t02, const float t03,
    const float t10, const float t11, const float t12, const float t13,
    const float t20, const float t21, const float t22, const float t23,
    const float t30, const float t31, const float t32, const float t33)
{
    m[0][0] = t00; m[0][1] = t01; m[0][2] = t02; m[0][3] = t03;
    m[1][0] = t10; m[1][1] = t11; m[1][2] = t12; m[1][3] = t13;
    m[2][0] = t20; m[2][1] = t21; m[2][2] = t22; m[2][3] = t23;
    m[3][0] = t30; m[3][1] = t31; m[3][2] = t32; m[3][3] = t33;
}

Transform& Transform::column(const unsigned id, const float t0, const float t1, const float t2, const float t3)
{
    m[0][id] = t0;
    m[1][id] = t1;
    m[2][id] = t2;
    m[3][id] = t3;
    return *this;
}


Transform& Transform::row(const unsigned id, const float t0, const float t1, const float t2, const float t3)
{
    m[id][0] = t0;
    m[id][1] = t1;
    m[id][2] = t2;
    m[id][3] = t3;
    return *this;
}
Transform& Transform::column_major(const float matrix[16])
{
    for (int i = 0; i < 4; i++)
        column(i, matrix[4 * i], matrix[4 * i + 1], matrix[4 * i + 2], matrix[4 * i + 3]);
    return *this;
}

Transform& Transform::row_major(const float matrix[16])
{
    for (int i = 0; i < 4; i++)
        row(i, matrix[4 * i], matrix[4 * i + 1], matrix[4 * i + 2], matrix[4 * i + 3]);
    return *this;
}

Transform::Transform(const Vector& x, const Vector& y, const Vector& z, const Vector& w)
{
    m[0][0] = x[0];  m[0][1] = y[0];  m[0][2] = z[0];  m[0][3] = w[0];
    m[1][0] = x[1];  m[1][1] = y[1];  m[1][2] = z[1];  m[1][3] = w[1];
    m[2][0] = x[2];  m[2][1] = y[2];  m[2][2] = z[2];  m[2][3] = w[2];
    m[3][0] = 0;    m[3][1] = 0;    m[3][2] = 0;    m[3][3] = 1;
}


Vector Transform::operator[] (const unsigned c) const
{
    assert(c < 4);
    return Vector(m[0][c], m[1][c], m[2][c]);
}


Vector Transform::operator() (const Vector& p) const
{
    float x = p[0];
    float y = p[1];
    float z = p[2];

    float xt = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];        // dot(vec4(m[0]), vec4(p, 1))
    float yt = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];        // dot(vec4(m[1]), vec4(p, 1))
    float zt = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];        // dot(vec4(m[2]), vec4(p, 1))
    float wt = m[3][0] * x + m[3][1] * y + m[3][2] * z + m[3][3];        // dot(vec4(m[3]), vec4(p, 1))

    assert(wt != 0);
    float w = 1.f / wt;
    if (wt == 1.f)
        return Vector(xt, yt, zt);
    else
        return Vector(xt * w, yt * w, zt * w);
}

Transform Transform::transpose() const
{
    return Transform(
        m[0][0], m[1][0], m[2][0], m[3][0],
        m[0][1], m[1][1], m[2][1], m[3][1],
        m[0][2], m[1][2], m[2][2], m[3][2],
        m[0][3], m[1][3], m[2][3], m[3][3]);
}


Transform Transform::operator() (const Transform& b) const
{
    return compose_transform(*this, b);
}

Transform Transform::normal() const
{
    return inverse().transpose();
}


Transform Identity()
{
    return Transform();
}

Transform Transpose(const Transform& m)
{
    return m.transpose();
}

Transform Inverse(const Transform& m)
{
    return m.inverse();
}

Transform Normal(const Transform& m)
{
    return m.normal();
}

Transform Scale(const float x, const float y, const float z)
{
    return Transform(
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1);
}

Transform Translation(const Vector& v)
{
    return Transform(
        1, 0, 0, v[0],
        0, 1, 0, v[1],
        0, 0, 1, v[2],
        0, 0, 0, 1);
}

Transform Translation(const float x, const float y, const float z)
{
    return Translation(Vector(x, y, z));
}

Transform RotationX(const float a)
{
    float sin_t = sinf(radians(a));
    float cos_t = cosf(radians(a));

    return Transform(
        1, 0, 0, 0,
        0, cos_t, -sin_t, 0,
        0, sin_t, cos_t, 0,
        0, 0, 0, 1);
}

Transform RotationY(const float a)
{
    float sin_t = sinf(radians(a));
    float cos_t = cosf(radians(a));

    return Transform(
        cos_t, 0, sin_t, 0,
        0, 1, 0, 0,
        -sin_t, 0, cos_t, 0,
        0, 0, 0, 1);
}

Transform RotationZ(const float a)
{
    float sin_t = sinf(radians(a));
    float cos_t = cosf(radians(a));

    return Transform(
        cos_t, -sin_t, 0, 0,
        sin_t, cos_t, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1);
}

Transform compose_transform(const Transform& a, const Transform& b)
{
    Transform m;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];

    return m;
}

Transform operator* (const Transform& a, const Transform& b)
{
    return compose_transform(a, b);
}

Transform Transform::inverse() const
{
    Transform minv = *this;

    int indxc[4], indxr[4];
    int ipiv[4] = { 0, 0, 0, 0 };

    for (int i = 0; i < 4; i++) {
        int irow = -1, icol = -1;
        float big = 0.f;

        // Choose pivot
        for (int j = 0; j < 4; j++) {
            if (ipiv[j] != 1) {
                for (int k = 0; k < 4; k++) {
                    if (ipiv[k] == 0) {
                        if (fabsf(minv.m[j][k]) >= big) {
                            big = std::abs(minv.m[j][k]);
                            irow = j;
                            icol = k;
                        }
                    }
                    else if (ipiv[k] > 1)
                        printf("singular matrix in Transform::inverse()\n");
                }
            }
        }

        assert(irow >= 0 && irow < 4);
        assert(icol >= 0 && icol < 4);

        ++ipiv[icol];
        // Swap rows _irow_ and _icol_ for pivot
        if (irow != icol) {
            for (int k = 0; k < 4; ++k)
                std::swap(minv.m[irow][k], minv.m[icol][k]);
        }

        indxr[i] = irow;
        indxc[i] = icol;
        if (minv.m[icol][icol] == 0.)
            printf("singular matrix in Transform::inverse()\n");

        // Set $m[icol][icol]$ to one by scaling row _icol_ appropriately
        float pivinv = 1.f / minv.m[icol][icol];
        minv.m[icol][icol] = 1.f;
        for (int j = 0; j < 4; j++)
            minv.m[icol][j] *= pivinv;

        // Subtract this row from others to zero out their columns
        for (int j = 0; j < 4; j++) {
            if (j != icol) {
                float save = minv.m[j][icol];
                minv.m[j][icol] = 0;
                for (int k = 0; k < 4; k++)
                    minv.m[j][k] -= minv.m[icol][k] * save;
            }
        }
    }

    // Swap columns to reflect permutation
    for (int j = 3; j >= 0; j--) {
        if (indxr[j] != indxc[j]) {
            for (int k = 0; k < 4; k++)
                std::swap(minv.m[k][indxr[j]], minv.m[k][indxc[j]]);
        }
    }

    return minv;
}
