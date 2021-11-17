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
        static double degreesToRadians(double degrees) { return degrees * pi / 180.0; };
        static double randomDouble();
        static double clamp(double x, double min, double max);
};

#endif // UTILITY_H
