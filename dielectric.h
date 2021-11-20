#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include <QVector3D>
#include "material.h"
#include "hitrecord.h"

class Dielectric : public AbstractMaterial
{
    public:
        Dielectric(double refractionIndex) : _refractionIndex(refractionIndex) {};
        virtual bool scatter(const Ray& r_in, const HitRecord& rec, QVector3D& colorAttenuation, Ray& scattered) const override;
    private:
        double _refractionIndex;
};

#endif // DIELECTRIC_H
