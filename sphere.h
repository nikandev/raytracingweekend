#ifndef SPHERE_H
#define SPHERE_H

#include <QSharedPointer>
#include <QVector3D>
#include "hittable.h"
#include "ray.h"
#include "material.h"

class Sphere : public Hittable
{
    public:
        Sphere();
        explicit Sphere(QVector3D cen, double r,  AbstractMaterial* m)
            : _center(cen), _radius(r), _material(m) {};
        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    private:
        QVector3D _center;
        double _radius;
        AbstractMaterial* _material;
};

#endif // SPHERE_H
