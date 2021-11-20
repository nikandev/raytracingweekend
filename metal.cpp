#include "metal.h"
#include "utility.h"
#include "hitrecord.h"

bool Metal::scatter(const Ray& in, const HitRecord& rec, QVector3D& attenuation, Ray& scattered) const
{
    QVector3D reflected = Utility::reflect(Utility::unitVector(in.direction()), rec.normal());
    scattered = Ray(rec.pointsInRange(), reflected);
    attenuation = _albedo;
    return (Utility::dot(scattered.direction(), reflected + (_fuzz * Utility::randomInUnitSphere())));
}
