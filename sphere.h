#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere : public Hittable
{
    public:
        Sphere();
        explicit Sphere(point3 cen, double r) : center(cen), radius(r) {};
        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    private:
        point3 center;
        double radius;
};

#endif // SPHERE_H
