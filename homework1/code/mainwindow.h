#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    static int kernel_size;
    static double para_sigma;
    ~MainWindow();

private slots:
    void on_loadPicture_clicked();

    void on_Roberts_clicked();

    void on_Prewitt_clicked();

    void on_Sobel_clicked();

    void on_Gaussian_clicked();

    void on_Mean_clicked();

    void on_Median_clicked();

    void on_Kernel_Size_valueChanged(int value);

    void on_Sigma_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QPixmap *pPixmap;
};

#endif // MAINWINDOW_H
