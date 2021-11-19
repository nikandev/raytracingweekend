#ifndef MATERIAL_H
#define MATERIAL_H

#include "QVector3D"
#include "ray.h"
#include "common.h"

class HitRecord;

class AbstractMaterial
{
    public:
        virtual bool scatter(const Ray& in, const HitRecord& rec, QVector3D& attenuation, Ray& scattered) const = 0;
};

#endif // MATERIAL_H
