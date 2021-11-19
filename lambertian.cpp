#include "lambertian.h"
#include "utility.h"

bool Lambertian::scatter(const Ray& /*in*/, const HitRecord& rec, QVector3D& attenuation, Ray& scattered) const
{
    auto scatterDirection = rec.normal() + Utility::randomUnitVector();

    if (Utility::nearZero(scatterDirection))
    {
        scatterDirection = rec.normal();
    }

    scattered = Ray(rec.pointsInRange(), scatterDirection);
    attenuation = _albedo;
    return true;
}
