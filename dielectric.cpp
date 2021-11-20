#include "dielectric.h"
#include "utility.h"

bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, QVector3D& colorAttenuation, Ray& scattered) const
{
    colorAttenuation = QVector3D(1.0, 1.0, 1.0);
    double refractionRatio = rec.frontFace() ? (1.0/_refractionIndex) : _refractionIndex;

    QVector3D unitDirection = Utility::unitVector(r_in.direction());

    double cosTheta = fmin(Utility::dot(-unitDirection, rec.normal()), 1.0);
    double sinTheta = sqrt(1.0 - cosTheta*cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0;
    QVector3D direction;

    if (cannotRefract || Utility::reflectance(cosTheta, refractionRatio) > Utility::randomDouble())
        direction = Utility::reflect(unitDirection, rec.normal());
    else
        direction = Utility::refract(unitDirection, rec.normal(), refractionRatio);

    scattered = Ray(rec.pointsInRange(), direction);

    return true;
}
