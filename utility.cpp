#include <QRandomGenerator>
#include "utility.h"

QVector3D Utility::unitVector(QVector3D v)
{
    return v / v.length();
}

QVector3D Utility::randomInUnitSphere()
{
    while (true)
    {
        auto p = randomVector(-1,1);

        if (p.lengthSquared() >= 1)
        {
            continue;
        }

        return p;
    }
}

QVector3D Utility::randomUnitVector()
{
    return unitVector(randomInUnitSphere());
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
