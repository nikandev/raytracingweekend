#include "camera.h"
#include "utility.h"

Camera::Camera(QVector3D lookFrom, QVector3D lookAt, QVector3D viewUp, double vertFov, double aspectRatio, double aperture, double focusDistance)
{
    auto theta = Utility::degreesToRadians(vertFov);
    auto h = tan(theta/2);

    auto viewportHeight = 2.0 * h;
    auto viewportWidth = aspectRatio * viewportHeight;

    auto w = Utility::unitVector(lookFrom - lookAt);
    auto u = Utility::unitVector(Utility::cross(viewUp, w));
    auto v = Utility::cross(w, u);

    _origin = lookFrom;
    _horizontal = focusDistance * viewportWidth * u;
    _vertical = focusDistance * viewportHeight * v;
    _lowerLeftCorner = _origin - _horizontal/2 - _vertical/2 - (focusDistance * w);

    _lensRadius = aperture / 2;
}

Ray Camera::getRay(double u, double v) const
{
    QVector3D random = _lensRadius * Utility::randomInUnitDisk();
    const double o = u * random.x() + v * random.y();
    QVector3D offset(o, o, o); //looks wrong
    return Ray(_origin + offset, _lowerLeftCorner + u*_horizontal + v*_vertical - _origin - offset);
}
