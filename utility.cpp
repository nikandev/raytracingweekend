#include <QRandomGenerator>
#include "utility.h"
#

QVector3D Utility::unitVector(QVector3D v)
{
    return v / v.length();
}

QVector3D Utility::randomInUnitSphere()
{
    while (true)
    {
        auto p = randomVector(-1,1);

        if (p.lengthSquared() >= 1)
        {
            continue;
        }

        return p;
    }
}

QVector3D Utility::randomUnitVector()
{
    return unitVector(randomInUnitSphere());
}

double Utility::randomDouble()
{
    QRandomGenerator* r = QRandomGenerator::system();
    return r->generateDouble();
}

double Utility::clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

bool Utility::nearZero(const QVector3D& vec)
{
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;
    return (fabs(vec[0]) < s) && (fabs(vec[1]) < s) && (fabs(vec[2]) < s);
}

double Utility::dot(const QVector3D& u, const QVector3D& v)
{
    return u.x() * v.x() +
           u.y() * v.y() +
           u.z() * v.z();
}

QVector3D Utility::reflect(const QVector3D& falling, const QVector3D& unit)
{
    return falling - 2 * dot(falling,unit) * unit;
}
