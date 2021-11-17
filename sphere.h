#ifndef SPHERE_H
#define SPHERE_H

#include <QVector3D>
#include "hittable.h"
#include "ray.h"

class Sphere : public Hittable
{
    public:
        Sphere();
        explicit Sphere(QVector3D cen, double r) : center(cen), radius(r) {};
        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    private:
        QVector3D center;
        double radius;
};

#endif // SPHERE_H
