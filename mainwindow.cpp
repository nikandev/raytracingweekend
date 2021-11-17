#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderer.h"
#include "sphere.h"
#include "utility.h"

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
    _camera = new Camera();
}

void MainWindow::buildWorld()
{
    QVector3D p = QVector3D(0,0,-1);
    _world.add(QSharedPointer<Sphere>::create(p, 0.5));
    QVector3D p1 = QVector3D(0,-100.5,-1);
    _world.add(QSharedPointer<Sphere>::create(p1, 100));
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
