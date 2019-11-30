#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <cmath>
MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->original_image->setText(" ");
    ui->processed_image->setText(" ");
    
}

MainWindow::~MainWindow()
{
    
    delete ui;
}

int MainWindow::kernel_size=0;
double MainWindow::para_sigma=0;

void MainWindow::on_loadPicture_clicked()
{
    pPixmap=new QPixmap(":/myImages/res/image/photographer.jpeg");
    ui->original_image->setPixmap(*pPixmap);        //load the original image
    ui->loadPicture->setDisabled(true);    //loadPicture banned after clicked

    
}


void MainWindow::on_Prewitt_clicked()
{
    ui->processed_image->setText(" ");        //memset the processed image
    
    QImage  image=pPixmap->toImage();
    unsigned char *pData=image.bits();
    
    QImage img(image);
    unsigned char *npData=img.bits();
    
    int width=image.width();
    int height=image.height();
    
    for(int i=1;i<height-1;i++)
    {
        for(int j=1;j<width-1;j++)
        {
            *(npData+(i*width+j)*4) = sqrt((*(pData+((i-1)*width+j+1)*4)
                                            +  *(pData+(i*width+j+1)*4)
                                            + *(pData+((i+1)*width+j+1)*4)
                                            - *(pData+((i-1)*width+j-1)*4) -  *(pData+(i*width+j-1)*4)
                                            - *(pData+((i+1)*width+j-1)*4))*(*(pData+((i-1)*width+j+1)*4)
                                                                             +  *(pData+(i*width+j+1)*4) +*(pData+((i+1)*width+j+1)*4)
                                                                             - *(pData+((i-1)*width+j-1)*4) -  *(pData+(i*width+j-1)*4)
                                                                             - *(pData+((i+1)*width+j-1)*4)) + (*(pData+((i-1)*width+j-1)*4) +  *(pData+((i-1)*width+j)*4)
                                                                                                                + *(pData+((i-1)*width+j+1)*4) - *(pData+((i+1)*width+j-1)*4)
                                                                                                                - *(pData+((i+1)*width+j)*4)
                                                                                                                - *(pData+((i+1)*width+j+1)*4))* (*(pData+((i-1)*width+j-1)*4) +  *(pData+((i-1)*width+j)*4)
                                                                                                                                                  + *(pData+((i-1)*width+j+1)*4) - *(pData+((i+1)*width+j-1)*4)
                                                                                                                                                  -  *(pData+((i+1)*width+j)*4)
                                                                                                                                                  - *(pData+((i+1)*width+j+1)*4)));
            *(npData+(i*width+j)*4+1)=*(npData+(i*width+j)*4);
            *(npData+(i*width+j)*4+2)=*(npData+(i*width+j)*4);
        }
    }
    QPixmap ConvertPixmap=QPixmap::fromImage(img);
    ui->processed_image->setPixmap(ConvertPixmap);
    
}


void MainWindow::on_Roberts_clicked()
{
    ui->processed_image->setText(" ");        //memset the processed image

    QImage  image=pPixmap->toImage();
    unsigned char *pData=image.bits();

    int width=image.width();
    int height=image.height();

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            *(pData+(i*width+j)*4+2)=abs(*(pData+((i+1)*width+j+1)*4+2)-*(pData+(i*width+j)*4+2))
                    + abs(*(pData+((i+1)*width+j)*4+2)-*(pData+(i*width+j+1)*4+2));    //R
            *(pData+(i*width+j)*4+1)=abs(*(pData+((i+1)*width+j+1)*4+1)-*(pData+(i*width+j)*4+1))
            + abs(*(pData+((i+1)*width+j)*4+1)-*(pData+(i*width+j+1)*4+1));    //G
            *(pData+(i*width+j)*4)=abs(*(pData+((i+1)*width+j+1)*4)-*(pData+(i*width+j)*4))
            + abs(*(pData+((i+1)*width+j)*4)-*(pData+(i*width+j+1)*4));      //B

        }
    }
    QPixmap ConvertPixmap=QPixmap::fromImage(image);
    ui->processed_image->setPixmap(ConvertPixmap);

}

void MainWindow::on_Sobel_clicked()
{
    ui->processed_image->setText(" ");
    
    QImage  image=pPixmap->toImage();
    unsigned char *pData=image.bits();
    
    QImage img(image);
    unsigned char *npData=img.bits();
    
    int width=image.width();
    int height=image.height();
    
    for(int i=1;i<height-1;i++)
    {
        for(int j=1;j<width-1;j++)
        {
            *(npData+(i*width+j)*4) = sqrt((*(pData+((i-1)*width+j+1)*4)
                                            + 2 * *(pData+(i*width+j+1)*4)
                                            + *(pData+((i+1)*width+j+1)*4)
                                            - *(pData+((i-1)*width+j-1)*4) - 2 * *(pData+(i*width+j-1)*4)
                                            - *(pData+((i+1)*width+j-1)*4))*(*(pData+((i-1)*width+j+1)*4)
                                                                             + 2 * *(pData+(i*width+j+1)*4) +*(pData+((i+1)*width+j+1)*4)
                                                                             - *(pData+((i-1)*width+j-1)*4) - 2 * *(pData+(i*width+j-1)*4)
                                                                             - *(pData+((i+1)*width+j-1)*4)) + (*(pData+((i-1)*width+j-1)*4) + 2 * *(pData+((i-1)*width+j)*4)
                                                                                                                + *(pData+((i-1)*width+j+1)*4) - *(pData+((i+1)*width+j-1)*4)
                                                                                                                - 2 * *(pData+((i+1)*width+j)*4)
                                                                                                                - *(pData+((i+1)*width+j+1)*4))* (*(pData+((i-1)*width+j-1)*4) + 2 * *(pData+((i-1)*width+j)*4)
                                                                                                                                                  + *(pData+((i-1)*width+j+1)*4) - *(pData+((i+1)*width+j-1)*4)
                                                                                                                                                  - 2 * *(pData+((i+1)*width+j)*4)
                                                                                                                                                  - *(pData+((i+1)*width+j+1)*4)));
            *(npData+(i*width+j)*4+1)=*(npData+(i*width+j)*4);
            *(npData+(i*width+j)*4+2)=*(npData+(i*width+j)*4);
        }
    }
    QPixmap ConvertPixmap=QPixmap::fromImage(img);
    ui->processed_image->setPixmap(ConvertPixmap);
}

void MainWindow::on_Gaussian_clicked()
{
    int size = 5;
    MainWindow::kernel_size=5;
    double **gaus=new double *[size];
    for(int i=0;i<size;i++)
    {
        gaus[i]=new double[size];
    }
    const double PI=4.0*atan(1.0); //that is pi
    int center=size/2;
    double sigma=10;
    MainWindow::para_sigma=10;
    double sum=0;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            gaus[i][j]=(1/(2*PI*sigma*sigma))*exp(-((i-center)*(i-center)+(j-center)*(j-center))/(2*sigma*sigma));
            sum+=gaus[i][j];
        }
    }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            gaus[i][j]/=sum;
    
    ui->processed_image->setText(" ");
    
    QImage  image=pPixmap->toImage();
    unsigned char *pData=image.bits();
    
    QImage img(image);
    unsigned char *npData=img.bits();
    
    int width=image.width();
    int height=image.height();
    
    for(int i=center;i<height-center;i++)
    {
        for(int j=center;j<width-center;j++)
        {
            *(npData+(i*width+j)*4)=0;
            for (int m=0;m<size;m++)
                for (int n=0;n<size;n++)
                    *(npData+(i*width+j)*4)+=*(pData+((i-center+m)*width+j-center+n)*4)*gaus[m][n];
            *(npData+(i*width+j)*4+1)=*(npData+(i*width+j)*4);
            *(npData+(i*width+j)*4+2)=*(npData+(i*width+j)*4);
        }
    }
    QPixmap ConvertPixmap=QPixmap::fromImage(img);
    ui->processed_image->setPixmap(ConvertPixmap);
}

void MainWindow::on_Mean_clicked()
{
    int size = 3;
    int center =1;
    
    ui->processed_image->setText(" ");
    
    QImage  image=pPixmap->toImage();
    unsigned char *pData=image.bits();
    
    QImage img(image);
    unsigned char *npData=img.bits();
    
    int width=image.width();
    int height=image.height();
    
    for(int i=center;i<height-center;i++)
    {
        for(int j=center;j<width-center;j++)
        {
            *(npData+(i*width+j)*4)=0;
            for (int m=0;m<size;m++)
                for (int n=0;n<size;n++)
                    *(npData+(i*width+j)*4)+=*(pData+((i-center+m)*width+j-center+n)*4)/9;
            *(npData+(i*width+j)*4+1)=*(npData+(i*width+j)*4);
            *(npData+(i*width+j)*4+2)=*(npData+(i*width+j)*4);
        }
    }
    QPixmap ConvertPixmap=QPixmap::fromImage(img);
    ui->processed_image->setPixmap(ConvertPixmap);
}

void MainWindow::on_Median_clicked()
{
    int size = 3;
    int temp[9]={0};
    int center=size/2;
    ui->processed_image->setText(" ");
    
    QImage  image=pPixmap->toImage();
    unsigned char *pData=image.bits();
    
    QImage img(image);
    unsigned char *npData=img.bits();
    
    int width=image.width();
    int height=image.height();
    
    for(int i=center;i<height-center;i++)
    {
        for(int j=center;j<width-center;j++)
        {
            *(npData+(i*width+j)*4)=0;
            int t=0;
            for (int m=0;m<size;m++)
                for (int n=0;n<size;n++)
                {
                    for (int q=0;q<t;q++)
                        if (temp[q]<*(pData+((i-center+m)*width+j-center+n)*4))
                        {
                            for (int p=t;p>q;p--)
                                temp[p]=temp[p-1];
                            temp[q]=*(pData+((i-center+m)*width+j-center+n)*4);
                        }
                        else temp[t]=*(pData+((i-center+m)*width+j-center+n)*4);
                    t++;
                }
            *(npData+(i*width+j)*4)=temp[4];
            *(npData+(i*width+j)*4+1)=*(npData+(i*width+j)*4);
            *(npData+(i*width+j)*4+2)=*(npData+(i*width+j)*4);
        }
    }
    QPixmap ConvertPixmap=QPixmap::fromImage(img);
    ui->processed_image->setPixmap(ConvertPixmap);
}

void MainWindow::on_Kernel_Size_valueChanged(int value)
{
    int size = value*2+1;
    MainWindow::kernel_size=size;
    double **gaus=new double *[size];
    for(int i=0;i<size;i++)
    {
        gaus[i]=new double[size];
    }
    const double PI=4.0*atan(1.0);
    int center=size/2;
    double sigma=MainWindow::para_sigma;
    double sum=0;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            gaus[i][j]=(1/(2*PI*sigma*sigma))*exp(-((i-center)*(i-center)+(j-center)*(j-center))/(2*sigma*sigma));
            sum+=gaus[i][j];
        }
    }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            gaus[i][j]/=sum;
    
    ui->processed_image->setText(" ");
    
    QImage  image=pPixmap->toImage();
    unsigned char *pData=image.bits();
    
    QImage img(image);
    unsigned char *npData=img.bits();
    
    int width=image.width();
    int height=image.height();
    
    for(int i=center;i<height-center;i++)
    {
        for(int j=center;j<width-center;j++)
        {
            *(npData+(i*width+j)*4)=0;
            for (int m=0;m<size;m++)
                for (int n=0;n<size;n++)
                    *(npData+(i*width+j)*4)+=*(pData+((i-center+m)*width+j-center+n)*4)*gaus[m][n];
            *(npData+(i*width+j)*4+1)=*(npData+(i*width+j)*4);
            *(npData+(i*width+j)*4+2)=*(npData+(i*width+j)*4);
        }
    }
    QPixmap ConvertPixmap=QPixmap::fromImage(img);
    ui->processed_image->setPixmap(ConvertPixmap);
}


void MainWindow::on_Sigma_valueChanged(int value)
{
    int size = MainWindow::kernel_size;
    double **gaus=new double *[size];
    for(int i=0;i<size;i++)
    {
        gaus[i]=new double[size];
    }
    const double PI=4.0*atan(1.0);
    int center=size/2;
    double sigma=value/10;
    MainWindow::para_sigma=sigma;
    double sum=0;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            gaus[i][j]=(1/(2*PI*sigma*sigma))*exp(-((i-center)*(i-center)+(j-center)*(j-center))/(2*sigma*sigma));
            sum+=gaus[i][j];
        }
    }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            gaus[i][j]/=sum;
    
    ui->processed_image->setText(" ");
    
    QImage  image=pPixmap->toImage();
    unsigned char *pData=image.bits();
    
    QImage img(image);
    unsigned char *npData=img.bits();
    
    int width=image.width();
    int height=image.height();
    
    for(int i=center;i<height-center;i++)
    {
        for(int j=center;j<width-center;j++)
        {
            *(npData+(i*width+j)*4)=0;
            for (int m=0;m<size;m++)
                for (int n=0;n<size;n++)
                    *(npData+(i*width+j)*4)+=*(pData+((i-center+m)*width+j-center+n)*4)*gaus[m][n];
            *(npData+(i*width+j)*4+1)=*(npData+(i*width+j)*4);
            *(npData+(i*width+j)*4+2)=*(npData+(i*width+j)*4);
        }
    }
    QPixmap ConvertPixmap=QPixmap::fromImage(img);
    ui->processed_image->setPixmap(ConvertPixmap);
}
