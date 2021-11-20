#ifndef METAL_H
#define METAL_H

#include <QVector3D>
#include "material.h"
#include "common.h"

class Metal : public AbstractMaterial
{
    public:
        Metal(const QVector3D& color, double fuzzCoeff) : _albedo(color), _fuzz(fuzzCoeff < 1 ? fuzzCoeff : 1) {};
        virtual bool scatter(const Ray& in, const HitRecord& rec, QVector3D& attenuation, Ray& scattered) const override;
    private:
        QVector3D _albedo;
        double _fuzz;
};

#endif // METAL_H
