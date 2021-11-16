#include <QGraphicsPixmapItem>
#include <QRgb>
#include <QSharedPointer>
#include <QVector3D>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      _image(nullptr),
      _camera(nullptr),
      _world(),
      _origin(nullptr)
{
    ui->setupUi(this);
    buildImage();
    buildCamera();
    buildWorld();
    render();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector3D MainWindow::unitVector(vec3 v)
{
    return v / v.length();
}

void MainWindow::buildImage()
{
    const auto aspectRatio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspectRatio);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(image_height);

    _image = new QImage(image_width, image_height, QImage::Format_RGB32);
}

void MainWindow::buildCamera()
{
    _camera = new Camera();

    _camera->viewportHeight = 2.0;
    _camera->viewportWidth = _aspectRatio * _camera->viewportHeight;
    _camera->focalLength = 1.0;

    _camera->origin = point3(0, 0, 0);
    _camera->horizontal = vec3(_camera->viewportWidth, 0, 0);
    _camera->vertical = vec3(0, _camera->viewportHeight, 0);
    _camera->lowerLeftCorner = _camera->origin - _camera->horizontal/2 - _camera->vertical/2 - vec3(0, 0, _camera->focalLength);
}

void MainWindow::buildWorld()
{
    point3 p = point3(0,0,-1);
    _world.add(QSharedPointer<Sphere>::create(p, 0.5));
}

void MainWindow::render()
{
    QRgb value = 0;

    for (int j = 0; j < _image->height(); j++)
    {
        ui->progressBar->setValue(j + 1);

        for (int i = 0; i < _image->width(); i++)
        {
            auto u = double(i) / (_image->width() - 1);
            auto v = double(j) / (_image->height() - 1);

            Ray r(_camera->origin, _camera->lowerLeftCorner + u * _camera->horizontal + v * _camera->vertical - _camera->origin);

            color pixelColor = rayColor(r, _world);

            int ir = static_cast<int>(255.999 * pixelColor.x());
            int ig = static_cast<int>(255.999 * pixelColor.y());
            int ib = static_cast<int>(255.999 * pixelColor.z());

            value = qRgb(ir, ig, ib);
            _image->setPixel(i, _image->height() - 1 - j, value);
        }
    }

    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*_image));
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
}

color MainWindow::rayColor(const Ray& r, const Hittable& world)
{
    HitRecord rec;

    if (world.hit(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + color(1,1,1));
    }

//    auto t = hitsSphere(point3(0,0,-1), 0.5, r);

//    if (t > 0.0)
//    {
//        vec3 N = unitVector(r.at(t) - vec3(0,0,-1));
//        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
//    }

    vec3 unitDirection = unitVector(r.direction());
//    t = 0.5*(unitDirection.y() + 1.0);
    auto t = 0.5*(unitDirection.y() + 1.0);

    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

double MainWindow::hitsSphere(const point3& center, double radius, const Ray& r)
{
    vec3 oc = r.origin() - center;
    auto a = r.direction().lengthSquared();
    auto halfB = Ray::dot(oc, r.direction());
    auto c = oc.lengthSquared() - radius*radius;
    auto discriminant = halfB * halfB - a * c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-halfB - sqrt(discriminant) ) / (2.0 * a);
    }
}
