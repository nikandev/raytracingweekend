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

QVector3D Utility::randomInUnitDisk()
{
    while (true)
    {
        auto p = QVector3D(randomDoubleBounded(-1,1), randomDoubleBounded(-1,1), 0);
        if (p.lengthSquared() >= 1) continue;
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
    return (fabs(vec.x()) < s) && (fabs(vec.y()) < s) && (fabs(vec.z()) < s);
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

double Utility::reflectance(double cosine, double refractionIndex)
{
    // Use Schlick's approximation for reflectance.
    auto r0 = (1-refractionIndex) / (1+refractionIndex);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

QVector3D Utility::refract(const QVector3D& uv, const QVector3D& n, double etaiOverEtat)
{
    auto cosTheta = fmin(dot(-uv, n), 1.0);
    QVector3D rOutPerpendicular =  etaiOverEtat * (uv + cosTheta*n);
    QVector3D rOutParallel = -sqrt(fabs(1.0 - rOutPerpendicular.lengthSquared())) * n;
    return rOutPerpendicular + rOutParallel;
}

QVector3D Utility::cross(const QVector3D& u, const QVector3D& v)
{
    return QVector3D(u.y() * v.z() - u.z() * v.y(),
                     u.z() * v.x() - u.x() * v.z(),
                     u.x() * v.y() - u.y() * v.x());
}

