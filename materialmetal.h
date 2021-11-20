#ifndef MATERIALMETAL_H
#define MATERIALMETAL_H

#include <QVector3D>
#include "material.h"
#include "common.h"

class MaterialMetal : public AbstractMaterial
{
    public:
        MaterialMetal(const QVector3D& color, double fuzzCoeff) : _albedo(color), _fuzz(fuzzCoeff < 1 ? fuzzCoeff : 1) {};
        virtual bool scatter(const Ray& in, const HitRecord& rec, QVector3D& attenuation, Ray& scattered) const override;
    private:
        QVector3D _albedo;
        double _fuzz;
};

#endif // MATERIALMETAL_H
