#ifndef UTILITY_H
#define UTILITY_H

#include <QVector3D>
#include <QtMath>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = M_PI;

class Utility
{
    public:
        static QVector3D unitVector(QVector3D v);
        static QVector3D randomInUnitSphere();
        static QVector3D randomInUnitDisk();
        static QVector3D randomUnitVector();

        static double randomDouble();
        static double clamp(double x, double min, double max);
        static bool nearZero(const QVector3D& vec);
        static double dot(const QVector3D& u, const QVector3D& v);

        static QVector3D reflect(const QVector3D& falling, const QVector3D& unit);
        static double reflectance(double cosine, double refractionIndex);
        static QVector3D refract(const QVector3D& uv, const QVector3D& n, double etaiOverEtat);

        static QVector3D cross(const QVector3D& u, const QVector3D& v);

        inline static QVector3D randomVector() { return QVector3D(randomDouble(), randomDouble(), randomDouble()); }
        inline static QVector3D randomVector(double min, double max) { return QVector3D(randomDoubleBounded(min, max), randomDoubleBounded(min, max), randomDoubleBounded(min, max)); }
        inline static double randomDoubleBounded(double min, double max) { return min + (max-min)*randomDouble(); };
        inline static double degreesToRadians(double degrees) { return degrees * pi / 180.0; };
};

#endif // UTILITY_H
