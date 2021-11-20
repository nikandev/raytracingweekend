#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QSharedPointer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderer.h"
#include "sphere.h"
#include "utility.h"
#include "materialmetal.h"
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
    const double aperture = 2.0;

    QVector3D lookFrom(-2,2,1);
    QVector3D lookAt(0,0,-1);
    QVector3D viewUp(0,1,0);

    const double distanceToFocus = (lookFrom-lookAt).length();

    _camera = new Camera(lookFrom, lookAt, viewUp, vertFov, aspectRatio, aperture, distanceToFocus);
}

void MainWindow::buildWorld()
{
    QVector3D groundColor(0.8, 0.8, 0.0);
    AbstractMaterial* groundMaterial = new Lambertian(groundColor);
    QVector3D groundCenter(0.0, -100.5, -1.0);
    Hittable* ground(new Sphere(groundCenter, 100.0, groundMaterial));

    double refractionIndex = 1.5;
    AbstractMaterial* centerMaterial = new Dielectric(refractionIndex);
    QVector3D centerCenter(0.0,    0.0, -1.0);
    double centerRadius = 0.5;
    Hittable* center(new Sphere(centerCenter, centerRadius, centerMaterial));

    QVector3D leftColor(0.8, 0.8, 0.8);
    double fuzzCoefficientLeft = 0.0;
    AbstractMaterial* leftMaterial = new MaterialMetal(leftColor, fuzzCoefficientLeft);
    QVector3D leftCenter( -1.0,    0.0, -1.0);
    Hittable* left(new Sphere(leftCenter, 0.5, leftMaterial));

    QVector3D rightColor(0.8, 0.6, 0.2);
    double fuzzCoefficientRight = 1.0;
    AbstractMaterial* rightMaterial = new MaterialMetal(rightColor, fuzzCoefficientRight);
    QVector3D rightCenter( 1.0,    0.0, -1.0);
    Hittable* right(new Sphere(rightCenter, 0.5, rightMaterial));

    _world.add(ground);
    _world.add(center);
    _world.add(left);
    _world.add(right);
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
