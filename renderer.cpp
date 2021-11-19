#include <QtMath>
#include "material.h"
#include "renderer.h"
#include "utility.h"
#include "ray.h"

Renderer::Renderer(int imageWidth, Camera* camera, HittableList* world, QObject* parent)
    :QThread(parent),
      _imageWidth(imageWidth),
      _camera(camera),
      _world(world)
{
}

void Renderer::run()
{
    const auto aspectRatio = 16.0 / 9.0;
    const int imageHeight = static_cast<int>(_imageWidth / aspectRatio);
    const int samplesPerPixel = 10; //Very heavy effect on operation time
    const int maxDepth = 50;

    QImage* image = new QImage(_imageWidth, imageHeight, QImage::Format_RGB32);

    for (int j = 0; j < imageHeight; j++)
    {
        emit updateProgressBar(j + 1);

        for (int i = 0; i < _imageWidth; i++)
        {
            QVector3D pixelColor(0, 0, 0);

             for (int s = 0; s < samplesPerPixel; s++)
             {
                 auto u = (i + Utility::randomDouble()) / (_imageWidth - 1);
                 auto v = (j + Utility::randomDouble()) / (imageHeight - 1);
                 Ray r = _camera->getRay(u, v);
                 pixelColor += rayColor(r, *_world, maxDepth);
             }

            image->setPixel(i, imageHeight - 1 - j, colorValue(pixelColor, samplesPerPixel));
        }
    }

    emit imageDone(*image);
}

QRgb Renderer::colorValue(QVector3D pixelColor, int samplesPerPixel)
{
    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    auto scale = 1.0 / samplesPerPixel;
    r *= scale;
    g *= scale;
    b *= scale;


//    r *= qSqrt(scale * r); //gamma-correct for gamma=2.0.
//    g *= qSqrt(scale * g);
//    b *= qSqrt(scale * b);

    int ir = static_cast<int>(256  * Utility::clamp(r, 0.0, 0.999));
    int ig = static_cast<int>(256  * Utility::clamp(g, 0.0, 0.999));
    int ib = static_cast<int>(256  * Utility::clamp(b, 0.0, 0.999));

    return qRgb(ir, ig, ib);
}

QVector3D Renderer::rayColor(const Ray& r, const Hittable& world, int depth)
{
    HitRecord rec;

    QVector3D nullColor(0, 0, 0);

    if (depth <= 0)
    {
            return nullColor;
    }

    const double shadowAcneFixCoefficient = 0.001;

    if (world.hit(r, shadowAcneFixCoefficient, infinity, rec))
    {
        Ray scattered;
        QVector3D colorAttenuation;

        AbstractMaterial* material = rec.material();

        if (material->scatter(r, rec, colorAttenuation, scattered))
        {
            return colorAttenuation * rayColor(scattered, world, depth-1);
        }

        return nullColor;
    }

    QVector3D unitDirection = Utility::unitVector(r.direction());
    auto t = 0.5*(unitDirection.y() + 1.0);

    return (1.0 - t) * QVector3D(1.0, 1.0, 1.0) + t * QVector3D(0.5, 0.7, 1.0);
}
