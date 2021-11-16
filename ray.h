#ifndef RAY_H
#define RAY_H

#include <QVector3D>
#include <QRgb>

using color = QVector3D;
using point3 = QVector3D;
using vec3 = QVector3D;

class Ray //Listing 8
{
    public:
        Ray();
        Ray(const point3& origin, const QVector3D& direction);
        point3 origin() const  { return _orig; }
        QVector3D direction() const { return _dir; }
        point3 at(double t) const { return _orig + t*_dir; }
        static double dot(const vec3& u, const vec3& v);
    private:
        point3 _orig;
        QVector3D _dir;
};

#endif // RAY_H
