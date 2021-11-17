#include "sphere.h"

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    QVector3D oc = r.origin() - center;
    auto a = r.direction().lengthSquared();
    auto half_b = Ray::dot(oc, r.direction());
    auto c = oc.lengthSquared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;

    if (discriminant < 0)
    {
        return false;
    }

    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;

    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;

        if (root < t_min || t_max < root)
        {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    QVector3D outward_normal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outward_normal);
    //rec.normal = (rec.p - center) / radius;

    return true;
}
