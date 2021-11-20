#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QSharedPointer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderer.h"
#include "sphere.h"
#include "utility.h"
#include "metal.h"
#include "lambertian.h"
#include "dielectric.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      _camera(nullptr),
      _world(),
      _origin(nullptr),
      _imageWidth(1024)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    ui->progressBar->setMinimum(0);

    buildCamera();
    buildWorld();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buildCamera()
{
    const double vertFov = 60;
    const double aspectRatio = 16.0 / 9.0;
    const double aperture = 0.1;

    QVector3D lookFrom(13,2,3);
    QVector3D lookAt(0,0,0);
    QVector3D viewUp(0,1,0);

    const double distanceToFocus = 10; //(lookFrom-lookAt).length();

    _camera = new Camera(lookFrom, lookAt, viewUp, vertFov, aspectRatio, aperture, distanceToFocus);
}

void MainWindow::buildWorld()
{
    QVector3D groundColor(0.5, 0.5, 0.5); //Todo: QRgb
    AbstractMaterial* groundMaterial = new Lambertian(groundColor);
    QVector3D groundCenter(0.0, -1000.0, 0.0);
    Hittable* ground(new Sphere(groundCenter, 1000.0, groundMaterial));

    _world.add(ground);

    buildRandomSpheres();
    buildBigSpheres();
}

void MainWindow::buildRandomSpheres()
{
    double radius = 0.2;

    for (int i = -11; i < 11; i++)
    {
        for (int j = -11; j < 11; j++)
        {
            auto materialRandomizer = Utility::randomDouble();
            QVector3D center(i + 0.9*Utility::randomDouble(), 0.2, j + 0.9*Utility::randomDouble());

            if ((center - QVector3D(4, 0.2, 0)).length() > 0.9)
            {
                AbstractMaterial* sphereMaterial = nullptr;

                if (materialRandomizer < 0.8)
                {
                    // diffuse
                    auto albedo = Utility::randomVector() * Utility::randomVector();
                    sphereMaterial = new Lambertian(albedo);
                    Sphere* s = new Sphere(center, radius, sphereMaterial);
                    _world.add(s);

                }
                else if (materialRandomizer < 0.95)
                {
                    // metal
                    auto albedo = Utility::randomVector(0.5, 1);
                    auto fuzz = Utility::randomDoubleBounded(0, 0.5);
                    sphereMaterial = new Metal(albedo, fuzz);
                    Sphere* s = new Sphere(center, radius, sphereMaterial);
                    _world.add(s);
                }
                else
                {
                    // glass
                    sphereMaterial = new Dielectric(1.5);
                    Sphere* s = new Sphere(center, radius, sphereMaterial);
                    _world.add(s);
                }
            }
        }
    }
}

void MainWindow::buildBigSpheres()
{
    const double radius = 1.0;

    QVector3D center(0, 1, 0);
    Sphere* s = new Sphere(center, 1.0, new Dielectric(1.5));
    _world.add(s);

    QVector3D color(0.4, 0.2, 0.1);
    QVector3D center2(-4, 1, 0);
    Sphere* s1 = new Sphere(center2, radius, new Lambertian(color));
    _world.add(s1);

    QVector3D color2(0.7, 0.6, 0.5);
    const double fuzz = 0.0;
    QVector3D center3(4, 1, 0);
    Sphere* s2 = new Sphere(center3, radius, new Metal(color2, fuzz));
    _world.add(s2);
}

void MainWindow::render()
{
    const auto aspectRatio = 16.0 / 9.0;
    const int imageHeight = static_cast<int>(_imageWidth / aspectRatio);
    ui->progressBar->setMaximum(imageHeight);

    Renderer* renderer = new Renderer(_imageWidth, _camera, &_world, this);
    connect(renderer, &Renderer::updateProgressBar, this->ui->progressBar, &QProgressBar::setValue);
    connect(renderer, &Renderer::imageDone, this, &MainWindow::showImage);
    connect(renderer, &Renderer::finished, renderer, &QObject::deleteLater);

    renderer->start();
}

void MainWindow::showImage(QImage image)
{
    QGraphicsScene* scene = new QGraphicsScene();
    bufferizePixmap(QPixmap::fromImage(image));
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(_imagePixmap);
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
}

void MainWindow::bufferizePixmap(QPixmap pixmap)
{
    _imagePixmap = pixmap;
}

double MainWindow::hitsSphere(const QVector3D& center, double radius, const Ray& r)
{
    QVector3D oc = r.origin() - center;
    auto a = r.direction().lengthSquared();
    auto halfB = Utility::dot(oc, r.direction());
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

void MainWindow::on_savePushButton_clicked()
{
    _imagePixmap.save("exported.png", "PNG");
}

void MainWindow::on_renderPushButton_clicked()
{
    render();
}

void MainWindow::on_widthSpinBox_valueChanged(int arg1)
{
    _imageWidth = arg1;
}
