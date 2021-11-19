#include "hitrecord.h"
#include "utility.h"

QVector3D HitRecord::pointsInRange() const
{
    return _pointsInRange;
}

void HitRecord::setPointsInRange(const QVector3D& p)
{
    _pointsInRange = p;
}

QVector3D HitRecord::normal() const
{
    return _normal;
}

void HitRecord::setInRange(double t)
{
    _inRange = t;
}

double HitRecord::inRange() const
{
    return _inRange;
}

bool HitRecord::frontFace() const
{
    return _frontFace;
}

void HitRecord::setFaceNormal(const Ray& r, const QVector3D& outwardNormal)
{
    _frontFace = Utility::dot(r.direction(), outwardNormal) < 0;
    _normal = _frontFace ? outwardNormal :-outwardNormal;
}

AbstractMaterial* HitRecord::material()
{
    return _material;
}

void HitRecord::setMaterial(AbstractMaterial* m)
{
    _material = m;
}
