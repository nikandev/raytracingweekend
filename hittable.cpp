#include "hittable.h"

bool HittableList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    HitRecord temp;
    bool hitAnything = false;
    auto closestSoFar = t_max;

    for (const auto& object : _objects)
    {
        if (object->hit(r, t_min, closestSoFar, temp))
        {
            hitAnything = true;
            closestSoFar = temp.t;
            rec = temp;
        }
    }

    return hitAnything;
}
