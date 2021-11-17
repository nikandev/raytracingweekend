#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRgb>
#include <QVector3D>
#include <QImage>
#include "camera.h"
#include "hittable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
        QVector3D* _origin;
        int _imageWidth;
        void buildCamera();
        void buildWorld();
        void render();
        static double hitsSphere(const QVector3D& center, double radius, const Ray& r);
    private slots:
        void showImage(QImage image);
        void on_savePushButton_clicked();
        void on_renderPushButton_clicked();
        void on_widthSpinBox_valueChanged(int arg1);
};
#endif // MAINWINDOW_H
