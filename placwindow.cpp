#include "placwindow.h"
#include "./ui_placwindow.h"

#include <QFileDialog>
#include <QToolButton>
#include <QMessageBox>

#include <QDir>
#include <QSettings>
#include <iostream>


PlacWindow::PlacWindow(QMainWindow *parent, float suma)
    : QMainWindow(parent)
    , ui2(new Ui::PlacWindow), suma(suma)
{
    ui2->setupUi(this);
    ui2->Zaplac->setEnabled(false);
    ui2->DoZaplaty->setText(QString::number(suma));
    connect(ui2->Zaplac,&QPushButton::clicked,this,&PlacWindow::zaplac);
    connect(ui2->ngr_1, &QSpinBox::valueChanged,this, &PlacWindow::monety_changed);
    connect(ui2->ngr_2, &QSpinBox::valueChanged,this, &PlacWindow::monety_changed);
    connect(ui2->ngr_5, &QSpinBox::valueChanged,this, &PlacWindow::monety_changed);
    connect(ui2->ngr_10, &QSpinBox::valueChanged,this, &PlacWindow::monety_changed);
    connect(ui2->ngr_20, &QSpinBox::valueChanged,this, &PlacWindow::monety_changed);
    connect(ui2->ngr_50, &QSpinBox::valueChanged,this, &PlacWindow::monety_changed);
    connect(ui2->nzl_1, &QSpinBox::valueChanged,this, &PlacWindow::monety_changed);
    connect(ui2->nzl_2, &QSpinBox::valueChanged,this, &PlacWindow::monety_changed);
    connect(ui2->nzl_5, &QSpinBox::valueChanged,this, &PlacWindow::monety_changed);


    gotowkaInfo.setWindowTitle("Podsumowanie transakcji");
    layout = new QVBoxLayout(&gotowkaInfo);
    QLabel *text1 = new QLabel("Podsumowanie transakcji",&gotowkaInfo);
    layout->addWidget(text1);

    QFile file("data.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::Truncate)) {
        QString val = file.readAll();
        file.close();
        QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
        content = document.object();
        mwa[0]=content.take("gr_1").toInt();
        mwa[1]=content.take("gr_2").toInt();
        mwa[2]=content.take("gr_5").toInt();
        mwa[3]=content.take("gr_10").toInt();
        mwa[4]=content.take("gr_20").toInt();
        mwa[5]=content.take("gr_50").toInt();
        mwa[6]=content.take("zl_1").toInt();
        mwa[7]=content.take("zl_2").toInt();
        mwa[8]=content.take("zl_5").toInt();
    }
    else {
        std::cout << "file open failed: " << std::endl;
    }

}

PlacWindow::~PlacWindow()
{
    parentWidget()->show();
    delete ui2;
}
void PlacWindow::monetyToJson()
{
    QJsonDocument document;
    content.insert("gr_1",QJsonValue(mwa[0]));
    content.insert("gr_2",QJsonValue(mwa[1]));
    content.insert("gr_5",QJsonValue(mwa[2]));
    content.insert("gr_10",QJsonValue(mwa[3]));
    content.insert("gr_20",QJsonValue(mwa[4]));
    content.insert("gr_50",QJsonValue(mwa[5]));
    content.insert("zl_1",QJsonValue(mwa[6]));
    content.insert("zl_2",QJsonValue(mwa[7]));
    content.insert("zl_5",QJsonValue(mwa[8]));
    document.setObject(content);
    QByteArray bytes = document.toJson(QJsonDocument::Indented);
    QFile file("data.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream iStream(&file);
        iStream << bytes;
        file.close();
    } else {
        std::cout << "file open failed: " << std::endl;
    }
}

void PlacWindow::zaplac()
{
    for(int i=0;i<9;i++)
    {
        mwa[i]=mwa[i]+ilosc[i];
    }
    int reszta[9]={0,0,0,0,0,0,0,0,0};

    float tmp=twojaSuma-suma;

    while(tmp>0)
    {
        if(tmp>=5&&mwa[8]>0)
        {
            reszta[8]++;
            mwa[8]--;
            tmp-=5;
        }
        else if(tmp>=2&&mwa[7]>0)
        {
            reszta[7]++;
            mwa[7]--;
            tmp-=2;
        }
        else if(tmp>=1&&mwa[6]>0)
        {
            reszta[6]++;
            mwa[6]--;
            tmp-=1;
        }
        else if(tmp>=0.5&&mwa[5]>0)
        {
            reszta[5]++;
            mwa[5]--;
            tmp-=0.50;
        }
        else if(tmp>=0.2&&mwa[4]>0)
        {
            reszta[4]++;
            mwa[4]--;
            tmp-=0.20;
        }
        else if(tmp>=0.1&&mwa[3]>0)
        {
            reszta[3]++;
            mwa[3]--;
            tmp-=0.10;
        }
        else if(tmp>=0.05&&mwa[2]>0)
        {
            reszta[2]++;
            mwa[2]--;
            tmp-=0.05;
        }
        else if(tmp>=0.02&&mwa[1]>0)
        {
            reszta[1]++;
            mwa[1]--;
            tmp-=0.02;
        }
        else if(tmp>=0.01&&mwa[0]>0)
        {
            reszta[0]++;
            mwa[0]--;
            tmp-=0.01;
        }
        else
        {
            break;
        }
    }

    QLabel *text2 = new QLabel("Zwrócono Monety:"
                               "\n1 gr. "+QString::number(reszta[0])+
                               "\n2 gr. "+QString::number(reszta[1])+
                               "\n5 gr. "+QString::number(reszta[2])+
                               "\n10 gr. "+QString::number(reszta[3])+
                               "\n20 gr. "+QString::number(reszta[4])+
                               "\n50 gr. "+QString::number(reszta[5])+
                               "\n1 zł. "+QString::number(reszta[6])+
                               "\n2 zł. "+QString::number(reszta[7])+
                               "\n5 zł. "+QString::number(reszta[8])
                               , &gotowkaInfo);
    //text2->textFormat()
    layout->addWidget(text2);

    monetyToJson();

    gotowkaInfo.show();
    parentWidget()->show();
    this->hide();
}

void PlacWindow::monety_changed()
{
    podliczenie();
    if(suma<=twojaSuma)
    {
        limitMonet();
        ui2->Zaplac->setEnabled(true);
    }
    else
    {
        relLimitMonet();
        ui2->Zaplac->setEnabled(false);
    }

}

void PlacWindow::podliczenie()
{
    float tmp=0;

    ilosc[0]=ui2->ngr_1->value();
    ilosc[1]=ui2->ngr_2->value();
    ilosc[2]=ui2->ngr_5->value();
    ilosc[3]=ui2->ngr_10->value();
    ilosc[4]=ui2->ngr_20->value();
    ilosc[5]=ui2->ngr_50->value();
    ilosc[6]=ui2->nzl_1->value();
    ilosc[7]=ui2->nzl_2->value();
    ilosc[8]=ui2->nzl_5->value();



    for(int i=0;i<9;i++)
    {
        tmp=tmp+ilosc[i]*wartosc[i];
    }
    twojaSuma=tmp;
    ui2->twojaSuma->setText(QString::number(twojaSuma));

}

void PlacWindow::limitMonet()
{
    ui2->ngr_1->setMaximum(ilosc[0]);
    ui2->ngr_2->setMaximum(ilosc[1]);
    ui2->ngr_5->setMaximum(ilosc[2]);
    ui2->ngr_10->setMaximum(ilosc[3]);
    ui2->ngr_20->setMaximum(ilosc[4]);
    ui2->ngr_50->setMaximum(ilosc[5]);
    ui2->nzl_1->setMaximum(ilosc[6]);
    ui2->nzl_2->setMaximum(ilosc[7]);
    ui2->nzl_5->setMaximum(ilosc[8]);
}

void PlacWindow::relLimitMonet()
{
    ui2->ngr_1->setMaximum(99);
    ui2->ngr_2->setMaximum(99);
    ui2->ngr_5->setMaximum(99);
    ui2->ngr_10->setMaximum(99);
    ui2->ngr_20->setMaximum(99);
    ui2->ngr_50->setMaximum(99);
    ui2->nzl_1->setMaximum(99);
    ui2->nzl_2->setMaximum(99);
    ui2->nzl_5->setMaximum(99);
}

