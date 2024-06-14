#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "placwindow.h"
#include "qdialog.h"
#include <QMainWindow>
#include <QDir>
#include <QStringLiteral>
#include <qobject.h>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OK_clicked();
    void anuluj_clicked();
    void plac_clicked();
    void kproduktToJson();
    void jsonToProdukt();
    void jsonToKprodukt();
    void doZaplaty();
    void gotowka_clicked();
    void karta_clicked();
    void odswierz();
    void usunProdukty();
    void updateContent();
    void updateJson();
protected:
     void showEvent(QShowEvent * event);
private:
    Ui::MainWindow *ui;
    PlacWindow *p;
    QDialog kartaInfo;
    float suma;
    QJsonObject content;
    int ilosc[16];

};


#endif // MAINWINDOW_H
