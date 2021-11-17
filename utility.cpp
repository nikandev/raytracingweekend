#include <QRandomGenerator>
#include "utility.h"

QVector3D Utility::unitVector(QVector3D v)
{
    return v / v.length();
}

double Utility::randomDouble()
{
    QRandomGenerator* r = QRandomGenerator::system();
    return r->generateDouble();
}

double Utility::clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
