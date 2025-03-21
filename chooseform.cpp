#include "chooseform.h"
#include "ui_chooseform.h"
#include "mainwindow.h"

ChooseForm::ChooseForm(QWidget *parent, QStringList* sL)
    : QDialog(parent)
    , ui(new Ui::ChooseForm)
    , stringList(*sL)
{


    ui->setupUi(this);

    for(auto item : stringList)
    {
        this->ui->listWidget->addItem(item);
    }

}

ChooseForm::~ChooseForm()
{
    delete ui;
}

void ChooseForm::on_pushButton_clicked()
{
    this->ui->listWidget->addItem(ui->textEdit->toPlainText());
    stringList << ui->textEdit->toPlainText();
}


void ChooseForm::on_pushButton_2_clicked()
{
    if(!ui->listWidget->currentItem())return;
    auto itr = stringList.begin();
    for(itr; itr!=stringList.end(); itr++)
    {
        if(*itr == ui->listWidget->currentItem()->text())
        {
            break;

        }
    }
    if(itr != stringList.end())
        stringList.erase(itr);
    delete ui->listWidget->currentItem();

}

QStringList ChooseForm::getStingList()
{
    return this->stringList;
}

void ChooseForm::on_pushButton_3_clicked()
{
    MainWindow *w = dynamic_cast<MainWindow*>(this->parent());
    w->setStringList(this);
    delete this;
}

