#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include "ray.h"

class Camera
{
    public:
        Camera(QVector3D lookFrom, QVector3D lookAt, QVector3D viewUp, double vertFov, double aspectRatio, double aperture, double focusDistance);
        Ray getRay(double u, double v) const;
    private:
        QVector3D _origin;
        QVector3D _lowerLeftCorner;
        QVector3D _horizontal;
        QVector3D _vertical;
        double _lensRadius;
};

#endif // CAMERA_H
