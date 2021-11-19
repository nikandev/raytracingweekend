#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include <QVector3D>
#include "ray.h"
#include "hitrecord.h"
#include "material.h"

class Lambertian : public AbstractMaterial
{
    public:
        Lambertian(const QVector3D& color) : _albedo(color) {};
        virtual bool scatter(const Ray& in, const HitRecord& rec, QVector3D& attenuation, Ray& scattered) const override;
    private:
        QVector3D _albedo;
};

#endif // LAMBERTIAN_H
