#ifndef RAY_H
#define RAY_H

#include <QVector3D>

class Ray //Listing 8
{
    public:
        Ray();
        Ray(const QVector3D& origin, const QVector3D& direction);
        QVector3D origin() const  { return _orig; }
        QVector3D direction() const { return _dir; }
        QVector3D at(double t) const { return _orig + t*_dir; }
        static double dot(const QVector3D& u, const QVector3D& v);
    private:
        QVector3D _orig;
        QVector3D _dir;
};

#endif // RAY_H
