#ifndef HITTABLE_H
#define HITTABLE_H

#include <QSharedPointer>
#include <QVector3D>
#include "ray.h"
#include "hitrecord.h"

class Hittable
{
    public:
        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

class HittableList : public Hittable
{
    public:
        HittableList() {}
        HittableList(Hittable* object) { _objects.append(object); }

        void clear() { _objects.clear(); }
        void add(Hittable* object) { _objects.append(object); }

        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    public:
        QList<Hittable*> _objects;
};

#endif // HITTABLE_H
