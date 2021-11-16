#include "ray.h"

Ray::Ray(const point3& origin, const QVector3D& direction)
    : _orig(origin), _dir(direction)
{
}

double Ray::dot(const vec3 &u, const vec3 &v)
{
    return u.x() * v.x()
            + u.y() * v.y()
            + u.z() * v.z();
}
