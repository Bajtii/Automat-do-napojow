#ifndef PLACWINDOW_H
#define PLACWINDOW_H

#include "qboxlayout.h"
#include <QMainWindow>
#include <QWidget>
#include <QDir>
#include <QStringLiteral>
#include <qobject.h>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class PlacWindow;
}
QT_END_NAMESPACE

class PlacWindow : public QMainWindow
{
    Q_OBJECT

public:
    PlacWindow(QMainWindow *parent = nullptr,float suma=0);
    ~PlacWindow();
private slots:
    void zaplac();
    void podliczenie();
    void monety_changed();
    void limitMonet();
    void relLimitMonet();
    void monetyToJson();
signals:

private:
    QJsonObject content;
    Ui::PlacWindow *ui2;
    QDialog gotowkaInfo;
    QVBoxLayout *layout;
    float twojaSuma;
    float suma;
    int ilosc[9];   //Monety wybrane przez uzytkownika
    int mwa[9]; //Monet w automacie
    const float wartosc[9]={0.01,0.02,0.05,0.10,0.20,0.50,1.00,2.00,5.00};
};

#endif // PLACWINDOW_H
