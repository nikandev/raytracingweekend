#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include "ray.h"

class Camera
{
    public:
        Camera();
        Ray getRay(double u, double v) const;
    private:
            QVector3D origin;
            QVector3D lower_left_corner;
            QVector3D horizontal;
            QVector3D vertical;
};

#endif // CAMERA_H
