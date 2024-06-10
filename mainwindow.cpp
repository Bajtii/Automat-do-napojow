#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QToolButton>
#include <QMessageBox>

#include <QDir>
#include <QSettings>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->OK, &QPushButton::clicked, this, &MainWindow::OK_clicked);
    connect(ui->anuluj, &QPushButton::clicked, this, &MainWindow::anuluj_clicked);
    connect(ui->OK, &QPushButton::clicked, this, &MainWindow::OK_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OK_clicked()
{

}

void MainWindow::anuluj_clicked()
{

}

void MainWindow::plac_clicked()
{

}

void MainWindow::connectButton()
{

}
