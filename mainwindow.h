#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMath>
#include "ray.h"
#include "hittable.h"
#include "sphere.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

const double infinity = std::numeric_limits<double>::infinity();
const double pi = M_PI;
const float _aspectRatio = 16.0 / 9.0;

QT_END_NAMESPACE

struct Camera
{
        float viewportHeight;
        float viewportWidth;
        float focalLength;
        point3 origin;
        vec3 horizontal;
        vec3 vertical;
        vec3 lowerLeftCorner;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    QImage* _image;
    Camera* _camera;
    HittableList _world;
    point3* _origin;
    void buildImage();
    void buildCamera();
    void buildWorld();
    void render();
    QVector3D unitVector(vec3 v);
    color rayColor(const Ray& r, const Hittable& world);
    double hitsSphere(const point3& center, double radius, const Ray& r);
    double degreesToRadians(double degrees) { return degrees * pi / 180.0; };
};
#endif // MAINWINDOW_H
