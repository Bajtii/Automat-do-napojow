#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QStringLiteral>
#include <qobject.h>

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
    void connectButton();
    void anuluj_clicked();
    void plac_clicked();
private:
    Ui::MainWindow *ui;

};


#endif // MAINWINDOW_H
