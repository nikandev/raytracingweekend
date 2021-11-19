#include "ray.h"

Ray::Ray(const QVector3D& origin, const QVector3D& direction)
    : _orig(origin), _dir(direction)
{
}
