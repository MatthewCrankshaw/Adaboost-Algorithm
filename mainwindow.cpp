#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_create_data_clicked()
{
    int dataset_size =  ui->spinBox_size_dataset->value();
    int boosing_rounds = ui->spinBox_boosing_rounds->value();
    int maxXY = ui->spinBox_max_X_Y->value();

    adb = new adaboost(dataset_size, boosing_rounds, maxXY);

    adb->create_data();

    QString output;
    output = "Size of Dataset: " + QString::number(dataset_size) + "\nNumber of boosing rounds: " + QString::number(boosing_rounds) + "\nMax x and y: " + QString::number(maxXY) + "\n";
    output += adb->get_data_as_string();
    ui->textEdit_data->setText(output);
}

void MainWindow::on_pushButton_train_clicked()
{
    if(adb == NULL){
        QString output = "Error please create data first!";
        qDebug() << output;
        ui->textEdit_classifiers->setText(output);
        return;
    }

    adb->train_adaboost();
    QString output;
    output = adb->get_weak_classifiers_as_string();
    ui->textEdit_classifiers->setText(output);
}
