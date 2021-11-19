#include "sphere.h"
#include "utility.h"

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    QVector3D oc = r.origin() -  _center;
    auto a = r.direction().lengthSquared();
    auto half_b = Utility::dot(oc, r.direction());
    auto c = oc.lengthSquared() - _radius*_radius;

    auto discriminant = half_b*half_b - a*c;

    if (discriminant < 0)
    {
        return false;
    }

    auto sqrtd = sqrt(discriminant);
    auto root = (-half_b - sqrtd) / a;

    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;

        if (root < t_min || t_max < root)
        {
            return false;
        }
    }

    rec.setInRange(root);
    rec.setPointsInRange(r.at(rec.inRange()));
    QVector3D outwardNormal = (rec.pointsInRange() - _center) / _radius;
    rec.setFaceNormal(r, outwardNormal);
    rec.setMaterial(_material);

    return true;
}
