#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chooseform.h"
#include "fileprocessor.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QThread>
#include <QTimer>
#include <QDebug>

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
    void setStringList(QObject*);

private slots:
    void on_checkBox_3_checkStateChanged(const Qt::CheckState &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void Processing(QStringList inputMask, QString outputPath, bool deleteInput, bool overwrite, QByteArray xorValue);

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    ChooseForm *chooseForm;
    QStringList stringList;
    int numberFiles;
    int curExecFiles;
};
#endif // MAINWINDOW_H
