#ifndef CHOOSEFORM_H
#define CHOOSEFORM_H


#include <QDialog>

namespace Ui {
class ChooseForm;
}

class ChooseForm : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseForm(QWidget *parent = nullptr, QStringList *sL = new QStringList);
    ~ChooseForm();
    QStringList getStingList();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ChooseForm *ui;

    QStringList stringList;
};

#endif // CHOOSEFORM_H
