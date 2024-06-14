#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "placwindow.h"

#include <QFileDialog>
#include <QToolButton>
#include <QMessageBox>
#include <QShowEvent>

#include <QDir>
#include <QSettings>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    updateContent();
    suma=0;
    ui->setupUi(this);
    ui->Gotowka->hide();
    ui->Karta->hide();
    connect(ui->anuluj, &QPushButton::clicked, this, &MainWindow::anuluj_clicked);
    connect(ui->OK, &QPushButton::clicked, this, &MainWindow::OK_clicked);
    connect(ui->plac, &QPushButton::clicked, this, &MainWindow::plac_clicked );
    connect(ui->Karta, &QPushButton::clicked, this, &MainWindow::karta_clicked );
    connect(ui->Gotowka, &QPushButton::clicked, this, &MainWindow::gotowka_clicked );

    connect(ui->ilosc_1, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_2, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_3, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_4, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_5, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_6, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_7, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_8, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_9, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_10, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_11, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_12, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_13, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_14, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_15, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);
    connect(ui->ilosc_16, &QSpinBox::valueChanged,this, &MainWindow::doZaplaty);

    kartaInfo.setWindowTitle("Transakcja");
    QVBoxLayout *layout = new QVBoxLayout(&kartaInfo);
    QLabel *text = new QLabel("Zaakceptowano transakcje", &kartaInfo);
    layout->addWidget(text);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OK_clicked()
{
    kproduktToJson();
    jsonToProdukt();
}

void MainWindow::anuluj_clicked()
{
    ui->ilosc_1->setEnabled(true);
    ui->ilosc_2->setEnabled(true);
    ui->ilosc_3->setEnabled(true);
    ui->ilosc_4->setEnabled(true);
    ui->ilosc_5->setEnabled(true);
    ui->ilosc_6->setEnabled(true);
    ui->ilosc_7->setEnabled(true);
    ui->ilosc_8->setEnabled(true);
    ui->ilosc_9->setEnabled(true);
    ui->ilosc_10->setEnabled(true);
    ui->ilosc_11->setEnabled(true);
    ui->ilosc_12->setEnabled(true);
    ui->ilosc_13->setEnabled(true);
    ui->ilosc_14->setEnabled(true);
    ui->ilosc_15->setEnabled(true);
    ui->ilosc_16->setEnabled(true);
    ui->ilosc_1->setValue(0);
    ui->ilosc_2->setValue(0);
    ui->ilosc_3->setValue(0);
    ui->ilosc_4->setValue(0);
    ui->ilosc_5->setValue(0);
    ui->ilosc_6->setValue(0);
    ui->ilosc_7->setValue(0);
    ui->ilosc_8->setValue(0);
    ui->ilosc_9->setValue(0);
    ui->ilosc_10->setValue(0);
    ui->ilosc_11->setValue(0);
    ui->ilosc_12->setValue(0);
    ui->ilosc_13->setValue(0);
    ui->ilosc_14->setValue(0);
    ui->ilosc_15->setValue(0);
    ui->ilosc_16->setValue(0);
    ui->plac->setEnabled(false);
    ui->Gotowka->hide();
    ui->Karta->hide();
}

void MainWindow::plac_clicked()
{
    ui->ilosc_1->setEnabled(true);
    ui->ilosc_2->setEnabled(true);
    ui->ilosc_3->setEnabled(true);
    ui->ilosc_4->setEnabled(true);
    ui->ilosc_5->setEnabled(true);
    ui->ilosc_6->setEnabled(true);
    ui->ilosc_7->setEnabled(true);
    ui->ilosc_8->setEnabled(true);
    ui->ilosc_9->setEnabled(true);
    ui->ilosc_10->setEnabled(true);
    ui->ilosc_11->setEnabled(true);
    ui->ilosc_12->setEnabled(true);
    ui->ilosc_13->setEnabled(true);
    ui->ilosc_14->setEnabled(true);
    ui->ilosc_15->setEnabled(true);
    ui->ilosc_16->setEnabled(true);
    ui->Gotowka->show();
    ui->Karta->show();

}

void MainWindow::karta_clicked()
{
    usunProdukty();
    updateJson();
    anuluj_clicked();
    kartaInfo.show();
}

void MainWindow::gotowka_clicked()
{
    usunProdukty();
    updateJson();
    PlacWindow *p = new PlacWindow(this,suma);
    p->show();
    anuluj_clicked();
    this->hide();
}

void MainWindow::kproduktToJson()
{
    content.insert("Nazwa_1", QJsonValue(ui->knazwa_1->toPlainText()));
    content.insert("Ilosc_1", QJsonValue(ui->kilosc_1->value()));
    content.insert("Cena_1", QJsonValue(ui->kcena_1->value()));
    content.insert("Nazwa_2", QJsonValue(ui->knazwa_2->toPlainText()));
    content.insert("Ilosc_2", QJsonValue(ui->kilosc_2->value()));
    content.insert("Cena_2", QJsonValue(ui->kcena_2->value()));
    content.insert("Nazwa_3", QJsonValue(ui->knazwa_3->toPlainText()));
    content.insert("Ilosc_3", QJsonValue(ui->kilosc_3->value()));
    content.insert("Cena_3", QJsonValue(ui->kcena_3->value()));
    content.insert("Nazwa_4", QJsonValue(ui->knazwa_4->toPlainText()));
    content.insert("Ilosc_4", QJsonValue(ui->kilosc_4->value()));
    content.insert("Cena_4", QJsonValue(ui->kcena_4->value()));
    content.insert("Nazwa_5", QJsonValue(ui->knazwa_5->toPlainText()));
    content.insert("Ilosc_5", QJsonValue(ui->kilosc_5->value()));
    content.insert("Cena_5", QJsonValue(ui->kcena_5->value()));
    content.insert("Nazwa_6", QJsonValue(ui->knazwa_6->toPlainText()));
    content.insert("Ilosc_6", QJsonValue(ui->kilosc_6->value()));
    content.insert("Cena_6", QJsonValue(ui->kcena_6->value()));
    content.insert("Nazwa_7", QJsonValue(ui->knazwa_7->toPlainText()));
    content.insert("Ilosc_7", QJsonValue(ui->kilosc_7->value()));
    content.insert("Cena_7", QJsonValue(ui->kcena_7->value()));
    content.insert("Nazwa_8", QJsonValue(ui->knazwa_8->toPlainText()));
    content.insert("Ilosc_8", QJsonValue(ui->kilosc_8->value()));
    content.insert("Cena_8", QJsonValue(ui->kcena_8->value()));
    content.insert("Nazwa_9", QJsonValue(ui->knazwa_9->toPlainText()));
    content.insert("Ilosc_9", QJsonValue(ui->kilosc_9->value()));
    content.insert("Cena_9", QJsonValue(ui->kcena_9->value()));
    content.insert("Nazwa_10", QJsonValue(ui->knazwa_10->toPlainText()));
    content.insert("Ilosc_10", QJsonValue(ui->kilosc_10->value()));
    content.insert("Cena_10", QJsonValue(ui->kcena_10->value()));
    content.insert("Nazwa_11", QJsonValue(ui->knazwa_11->toPlainText()));
    content.insert("Ilosc_11", QJsonValue(ui->kilosc_11->value()));
    content.insert("Cena_11", QJsonValue(ui->kcena_11->value()));
    content.insert("Nazwa_12", QJsonValue(ui->knazwa_12->toPlainText()));
    content.insert("Ilosc_12", QJsonValue(ui->kilosc_12->value()));
    content.insert("Cena_12", QJsonValue(ui->kcena_12->value()));
    content.insert("Nazwa_13", QJsonValue(ui->knazwa_13->toPlainText()));
    content.insert("Ilosc_13", QJsonValue(ui->kilosc_13->value()));
    content.insert("Cena_13", QJsonValue(ui->kcena_13->value()));
    content.insert("Nazwa_14", QJsonValue(ui->knazwa_14->toPlainText()));
    content.insert("Ilosc_14", QJsonValue(ui->kilosc_14->value()));
    content.insert("Cena_14", QJsonValue(ui->kcena_14->value()));
    content.insert("Nazwa_15", QJsonValue(ui->knazwa_15->toPlainText()));
    content.insert("Ilosc_15", QJsonValue(ui->kilosc_15->value()));
    content.insert("Cena_15", QJsonValue(ui->kcena_15->value()));
    content.insert("Nazwa_16", QJsonValue(ui->knazwa_16->toPlainText()));
    content.insert("Ilosc_16", QJsonValue(ui->kilosc_16->value()));
    content.insert("Cena_16", QJsonValue(ui->kcena_16->value()));

    content.insert("gr_1",QJsonValue(ui->gr_1->value()));
    content.insert("gr_2",QJsonValue(ui->gr_2->value()));
    content.insert("gr_10",QJsonValue(ui->gr_10->value()));
    content.insert("gr_20",QJsonValue(ui->gr_20->value()));
    content.insert("gr_5",QJsonValue(ui->gr_5->value()));
    content.insert("gr_50",QJsonValue(ui->gr_50->value()));
    content.insert("zl_1",QJsonValue(ui->zl_1->value()));
    content.insert("zl_2",QJsonValue(ui->zl_2->value()));
    content.insert("zl_5",QJsonValue(ui->zl_5->value()));
    updateJson();
}


void MainWindow::updateContent()
{
    QFile file("data.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::Truncate)) {
        QString val = file.readAll();
        file.close();
        QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
        content = document.object();
    }
    else {
        std::cout << "file open failed: " << std::endl;
    }
}

void MainWindow::updateJson()
{
    QJsonDocument document;
    document.setObject(content);
    QByteArray bytes = document.toJson(QJsonDocument::Indented);
    QFile file("data.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream iStream(&file);
        iStream << bytes;
        file.close();
    }
    else {
        std::cout << "file open failed: " << std::endl;
    }
}

void MainWindow::jsonToProdukt()
{
    updateContent();
    ui->Nazwa_1->setText(content.take("Nazwa_1").toString());
    ui->Cena_1->setText(QString::number(content.take("Cena_1").toDouble(),'f',2));
    ui->ilosc_1->setMaximum(content.take("Ilosc_1").toInt());
    ui->Nazwa_2->setText(content.take("Nazwa_2").toString());
    ui->Cena_2->setText(QString::number(content.take("Cena_2").toDouble(),'f',2));
    ui->ilosc_2->setMaximum(content.take("Ilosc_2").toInt());
    ui->Nazwa_3->setText(content.take("Nazwa_3").toString());
    ui->Cena_3->setText(QString::number(content.take("Cena_3").toDouble(),'f',2));
    ui->ilosc_3->setMaximum(content.take("Ilosc_3").toInt());
    ui->Nazwa_4->setText(content.take("Nazwa_4").toString());
    ui->Cena_4->setText(QString::number(content.take("Cena_4").toDouble(),'f',2));
    ui->ilosc_4->setMaximum(content.take("Ilosc_4").toInt());
    ui->Nazwa_5->setText(content.take("Nazwa_5").toString());
    ui->Cena_5->setText(QString::number(content.take("Cena_5").toDouble(),'f',2));
    ui->ilosc_5->setMaximum(content.take("Ilosc_5").toInt());
    ui->Nazwa_6->setText(content.take("Nazwa_6").toString());
    ui->Cena_6->setText(QString::number(content.take("Cena_6").toDouble(),'f',2));
    ui->ilosc_6->setMaximum(content.take("Ilosc_6").toInt());
    ui->Nazwa_7->setText(content.take("Nazwa_7").toString());
    ui->Cena_7->setText(QString::number(content.take("Cena_7").toDouble(),'f',2));
    ui->ilosc_7->setMaximum(content.take("Ilosc_7").toInt());
    ui->Nazwa_8->setText(content.take("Nazwa_8").toString());
    ui->Cena_8->setText(QString::number(content.take("Cena_8").toDouble(),'f',2));
    ui->ilosc_8->setMaximum(content.take("Ilosc_8").toInt());
    ui->Nazwa_9->setText(content.take("Nazwa_9").toString());
    ui->Cena_9->setText(QString::number(content.take("Cena_9").toDouble(),'f',2));
    ui->ilosc_9->setMaximum(content.take("Ilosc_9").toInt());
    ui->Nazwa_10->setText(content.take("Nazwa_10").toString());
    ui->Cena_10->setText(QString::number(content.take("Cena_10").toDouble(),'f',2));
    ui->ilosc_10->setMaximum(content.take("Ilosc_10").toInt());
    ui->Nazwa_11->setText(content.take("Nazwa_11").toString());
    ui->Cena_11->setText(QString::number(content.take("Cena_11").toDouble(),'f',2));
    ui->ilosc_11->setMaximum(content.take("Ilosc_11").toInt());
    ui->Nazwa_12->setText(content.take("Nazwa_12").toString());
    ui->Cena_12->setText(QString::number(content.take("Cena_12").toDouble(),'f',2));
    ui->ilosc_12->setMaximum(content.take("Ilosc_12").toInt());
    ui->Nazwa_13->setText(content.take("Nazwa_13").toString());
    ui->Cena_13->setText(QString::number(content.take("Cena_13").toDouble(),'f',2));
    ui->ilosc_13->setMaximum(content.take("Ilosc_13").toInt());
    ui->Nazwa_14->setText(content.take("Nazwa_14").toString());
    ui->Cena_14->setText(QString::number(content.take("Cena_14").toDouble(),'f',2));
    ui->ilosc_14->setMaximum(content.take("Ilosc_14").toInt());
    ui->Nazwa_15->setText(content.take("Nazwa_15").toString());
    ui->Cena_15->setText(QString::number(content.take("Cena_15").toDouble(),'f',2));
    ui->ilosc_15->setMaximum(content.take("Ilosc_15").toInt());
    ui->Nazwa_16->setText(content.take("Nazwa_16").toString());
    ui->Cena_16->setText(QString::number(content.take("Cena_16").toDouble(),'f',2));
    ui->ilosc_16->setMaximum(content.take("Ilosc_16").toInt());
}

void MainWindow::jsonToKprodukt()
{
    updateContent();
    ui->knazwa_1->setPlainText(content.take("Nazwa_1").toString());
    ui->kcena_1->setValue(content.take("Cena_1").toDouble());
    ui->kilosc_1->setValue(content.take("Ilosc_1").toInt());
    ui->knazwa_2->setPlainText(content.take("Nazwa_2").toString());
    ui->kcena_2->setValue(content.take("Cena_2").toDouble());
    ui->kilosc_2->setValue(content.take("Ilosc_2").toInt());
    ui->knazwa_3->setPlainText(content.take("Nazwa_3").toString());
    ui->kcena_3->setValue(content.take("Cena_3").toDouble());
    ui->kilosc_3->setValue(content.take("Ilosc_3").toInt());
    ui->knazwa_4->setPlainText(content.take("Nazwa_4").toString());
    ui->kcena_4->setValue(content.take("Cena_4").toDouble());
    ui->kilosc_4->setValue(content.take("Ilosc_4").toInt());
    ui->knazwa_5->setPlainText(content.take("Nazwa_5").toString());
    ui->kcena_5->setValue(content.take("Cena_5").toDouble());
    ui->kilosc_5->setValue(content.take("Ilosc_5").toInt());
    ui->knazwa_6->setPlainText(content.take("Nazwa_6").toString());
    ui->kcena_6->setValue(content.take("Cena_6").toDouble());
    ui->kilosc_6->setValue(content.take("Ilosc_6").toInt());
    ui->knazwa_7->setPlainText(content.take("Nazwa_7").toString());
    ui->kcena_7->setValue(content.take("Cena_7").toDouble());
    ui->kilosc_7->setValue(content.take("Ilosc_7").toInt());
    ui->knazwa_8->setPlainText(content.take("Nazwa_8").toString());
    ui->kcena_8->setValue(content.take("Cena_8").toDouble());
    ui->kilosc_8->setValue(content.take("Ilosc_8").toInt());
    ui->knazwa_9->setPlainText(content.take("Nazwa_9").toString());
    ui->kcena_9->setValue(content.take("Cena_9").toDouble());
    ui->kilosc_9->setValue(content.take("Ilosc_9").toInt());
    ui->knazwa_10->setPlainText(content.take("Nazwa_10").toString());
    ui->kcena_10->setValue(content.take("Cena_10").toDouble());
    ui->kilosc_10->setValue(content.take("Ilosc_10").toInt());
    ui->knazwa_11->setPlainText(content.take("Nazwa_11").toString());
    ui->kcena_11->setValue(content.take("Cena_11").toDouble());
    ui->kilosc_11->setValue(content.take("Ilosc_11").toInt());
    ui->knazwa_12->setPlainText(content.take("Nazwa_12").toString());
    ui->kcena_12->setValue(content.take("Cena_12").toDouble());
    ui->kilosc_12->setValue(content.take("Ilosc_12").toInt());
    ui->knazwa_13->setPlainText(content.take("Nazwa_13").toString());
    ui->kcena_13->setValue(content.take("Cena_13").toDouble());
    ui->kilosc_13->setValue(content.take("Ilosc_13").toInt());
    ui->knazwa_14->setPlainText(content.take("Nazwa_14").toString());
    ui->kcena_14->setValue(content.take("Cena_14").toDouble());
    ui->kilosc_14->setValue(content.take("Ilosc_14").toInt());
    ui->knazwa_15->setPlainText(content.take("Nazwa_15").toString());
    ui->kcena_15->setValue(content.take("Cena_15").toDouble());
    ui->kilosc_15->setValue(content.take("Ilosc_15").toInt());
    ui->knazwa_16->setPlainText(content.take("Nazwa_16").toString());
    ui->kcena_16->setValue(content.take("Cena_16").toDouble());
    ui->kilosc_16->setValue(content.take("Ilosc_16").toInt());

    ui->gr_1->setValue(content.take("gr_1").toInt());
    ui->gr_2->setValue(content.take("gr_2").toInt());
    ui->gr_10->setValue(content.take("gr_10").toInt());
    ui->gr_20->setValue(content.take("gr_20").toInt());
    ui->gr_5->setValue(content.take("gr_5").toInt());
    ui->gr_50->setValue(content.take("gr_50").toInt());
    ui->zl_1->setValue(content.take("zl_1").toInt());
    ui->zl_2->setValue(content.take("zl_2").toInt());
    ui->zl_5->setValue(content.take("zl_5").toInt());
}

void MainWindow::doZaplaty()
{
    suma=0;
    float cena[16];
    ilosc[0]=ui->ilosc_1->value();
    ilosc[1]=ui->ilosc_2->value();
    ilosc[2]=ui->ilosc_3->value();
    ilosc[3]=ui->ilosc_4->value();
    ilosc[4]=ui->ilosc_5->value();
    ilosc[5]=ui->ilosc_6->value();
    ilosc[6]=ui->ilosc_7->value();
    ilosc[7]=ui->ilosc_8->value();
    ilosc[8]=ui->ilosc_9->value();
    ilosc[9]=ui->ilosc_10->value();
    ilosc[10]=ui->ilosc_11->value();
    ilosc[11]=ui->ilosc_12->value();
    ilosc[12]=ui->ilosc_13->value();
    ilosc[13]=ui->ilosc_14->value();
    ilosc[14]=ui->ilosc_15->value();
    ilosc[15]=ui->ilosc_16->value();
    cena[0]=ui->Cena_1->text().toFloat();
    cena[1]=ui->Cena_2->text().toFloat();
    cena[2]=ui->Cena_3->text().toFloat();
    cena[3]=ui->Cena_4->text().toFloat();
    cena[4]=ui->Cena_5->text().toFloat();
    cena[5]=ui->Cena_6->text().toFloat();
    cena[6]=ui->Cena_7->text().toFloat();
    cena[7]=ui->Cena_8->text().toFloat();
    cena[8]=ui->Cena_9->text().toFloat();
    cena[9]=ui->Cena_10->text().toFloat();
    cena[10]=ui->Cena_11->text().toFloat();
    cena[11]=ui->Cena_12->text().toFloat();
    cena[12]=ui->Cena_13->text().toFloat();
    cena[13]=ui->Cena_14->text().toFloat();
    cena[14]=ui->Cena_15->text().toFloat();
    cena[15]=ui->Cena_16->text().toFloat();
    for(int i=0;i<16;i++)
    {
        suma=suma+ilosc[i]*cena[i];
    }
    ui->dozaplaty->setText(QString::number(suma));
    if(suma>0)
        ui->plac->setEnabled(true);
    else
        ui->plac->setEnabled(false);
}

void MainWindow::odswierz()
{
    jsonToProdukt();
    jsonToKprodukt();
}

void MainWindow::showEvent(QShowEvent *event)
{
    event->accept();
    odswierz();
    qDebug() << "QCloseEvent : Widget showed";
}

void MainWindow::usunProdukty()
{

    ui->kilosc_1->setValue(ui->kilosc_1->value()-ilosc[0]);
    ui->kilosc_2->setValue(ui->kilosc_2->value()-ilosc[1]);
    ui->kilosc_3->setValue(ui->kilosc_3->value()-ilosc[2]);
    ui->kilosc_4->setValue(ui->kilosc_4->value()-ilosc[3]);
    ui->kilosc_5->setValue(ui->kilosc_5->value()-ilosc[4]);
    ui->kilosc_6->setValue(ui->kilosc_6->value()-ilosc[5]);
    ui->kilosc_7->setValue(ui->kilosc_7->value()-ilosc[6]);
    ui->kilosc_8->setValue(ui->kilosc_8->value()-ilosc[7]);
    ui->kilosc_9->setValue(ui->kilosc_9->value()-ilosc[8]);
    ui->kilosc_10->setValue(ui->kilosc_10->value()-ilosc[9]);
    ui->kilosc_11->setValue(ui->kilosc_11->value()-ilosc[10]);
    ui->kilosc_12->setValue(ui->kilosc_12->value()-ilosc[11]);
    ui->kilosc_13->setValue(ui->kilosc_13->value()-ilosc[12]);
    ui->kilosc_14->setValue(ui->kilosc_14->value()-ilosc[13]);
    ui->kilosc_15->setValue(ui->kilosc_15->value()-ilosc[14]);
    ui->kilosc_16->setValue(ui->kilosc_16->value()-ilosc[15]);
    kproduktToJson();
}
