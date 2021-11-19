#ifndef HITRECORD_H
#define HITRECORD_H

#include <QSharedPointer>
#include <QVector3D>
#include "ray.h"
#include "common.h"
#include "material.h"

class HitRecord
{
    public:
        QVector3D pointsInRange() const;
        void setPointsInRange(const QVector3D& p);

        QVector3D normal() const;
        void setFaceNormal(const Ray& r, const QVector3D& outwardNormal);

        AbstractMaterial* material();
        void setMaterial(AbstractMaterial* m);

        double inRange() const;
        void setInRange(double t);

        bool frontFace() const;
    private:
        QVector3D _pointsInRange;
        QVector3D _normal;
        AbstractMaterial* _material;
        double _inRange;
        bool _frontFace;
};

#endif // HITRECORD_H
