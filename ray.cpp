#include "ray.h"

Ray::Ray(const QVector3D& origin, const QVector3D& direction)
    : _orig(origin), _dir(direction)
{
}

double Ray::dot(const QVector3D &u, const QVector3D &v)
{
    return u.x() * v.x()
            + u.y() * v.y()
            + u.z() * v.z();
}
