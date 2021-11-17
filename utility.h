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
        static QVector3D randomUnitVector();

        static double randomDouble();
        static double clamp(double x, double min, double max);

        inline static QVector3D randomVector() { return QVector3D(randomDouble(), randomDouble(), randomDouble()); }
        inline static QVector3D randomVector(double min, double max) { return QVector3D(randomDoubleBounded(min, max), randomDoubleBounded(min, max), randomDoubleBounded(min, max)); }
        inline static double randomDoubleBounded(double min, double max) { return min + (max-min)*randomDouble(); };
        inline static double degreesToRadians(double degrees) { return degrees * pi / 180.0; };
};

#endif // UTILITY_H
