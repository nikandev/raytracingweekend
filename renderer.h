#ifndef RENDERER_H
#define RENDERER_H

#include <QThread>
#include <QObject>
#include <QRgb>
#include <QImage>
#include "camera.h"
#include "hittable.h"

class Renderer : public QThread
{
        Q_OBJECT
    public:
        Renderer(int imageWidth, Camera* camera, HittableList* world, QObject* parent = nullptr);
        void run() override;
    signals:
        void updateProgressBar(int progress);
        void imageDone(QImage image);
    private:
        int _imageWidth;
        Camera* _camera;
        HittableList* _world;
        QRgb colorValue(QVector3D pixelColor, int samplesPerPixel);
        static QVector3D rayColor(const Ray& r, const Hittable& world, int depth);
};

#endif // RENDERER_H
