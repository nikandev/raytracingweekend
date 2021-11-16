#ifndef HITTABLE_H
#define HITTABLE_H

#include <QList>
#include <QSharedPointer>
#include "ray.h"

struct HitRecord
{
    point3 p;
    vec3 normal;
    double t;
    bool frontFace;

    inline void setFaceNormal(const Ray& r, const vec3& outward_normal)
    {
        frontFace = Ray::dot(r.direction(), outward_normal) < 0;
        normal = frontFace ? outward_normal :-outward_normal;
    }
};

class Hittable
{
    public:
        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

class HittableList : public Hittable
{
    public:
        HittableList() {}
        HittableList(QSharedPointer<Hittable> object) { _objects.append(object); }

        void clear() { _objects.clear(); }
        void add(QSharedPointer<Hittable> object) { _objects.append(object); }

        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    public:
        QList<QSharedPointer<Hittable>> _objects;
};

#endif // HITTABLE_H
