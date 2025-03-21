#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , numberFiles(0)
    , curExecFiles(0)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_3_checkStateChanged(const Qt::CheckState &arg1)
{
    ui->textEdit_2->setEnabled(arg1);
}


void MainWindow::on_pushButton_2_clicked()
{
    QString text = QFileDialog::getExistingDirectory(this, "Open Directory", getenv(""), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    ui->textEdit->setMarkdown(text);
}


void MainWindow::on_pushButton_clicked()
{
    chooseForm = new ChooseForm(this, &this->stringList);
    chooseForm->show();
}

void MainWindow::setStringList(QObject *o)
{
    ChooseForm *f = dynamic_cast<ChooseForm*>(o);

    this->stringList = f->getStingList();
}


void MainWindow::on_pushButton_3_clicked()
{
    // тут мы запускаем работу


    this->ui->pushButton_4->setEnabled(true);
    this->ui->pushButton_3->setEnabled(false);


    QStringList inputMask = this->stringList;
    QString outputPath = this->ui->textEdit->toPlainText();
    bool deleteInput = this->ui->checkBox->isChecked();
    bool overwrite = this->ui->checkBox_2->isChecked();
    bool runTimer = this->ui->checkBox_3->isChecked();
    int pollInterval = this->ui->textEdit_2->toPlainText().toInt();
    QByteArray xorValue = QByteArray::fromHex(this->ui->textEdit_3->toPlainText().toUtf8());

    Processing(inputMask, outputPath, deleteInput, overwrite, xorValue);
    if(runTimer)
    {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [this, inputMask, outputPath, deleteInput, overwrite, xorValue]() { if(this->curExecFiles >= this->numberFiles){this->curExecFiles = 0; this->ui->progressBar->setValue(0); Processing(inputMask, outputPath, deleteInput, overwrite, xorValue);} });

        connect(ui->pushButton_4, &QPushButton::clicked, timer, &QTimer::deleteLater);

        timer->start(pollInterval * 1000);
    }

    qDebug() << "Конец!" ;
}

void MainWindow::Processing(QStringList inputMask, QString outputPath, bool deleteInput, bool overwrite, QByteArray xorValue)
{
    QDir().mkdir(outputPath);
    QDir dir("./input");

    QStringList files;

    for(auto item : inputMask)
    {
        files = dir.entryList(files << item, QDir::Files);
    }

    numberFiles = files.size();

    for(const QString &file : files)
    {
        FileProcessor *processor = new FileProcessor;
        QThread *thread = new QThread;
        processor->moveToThread(thread);

        connect(thread, &QThread::started, [processor, file, outputPath, deleteInput, overwrite, xorValue]() {
            processor->processFile(file, outputPath, deleteInput, overwrite, xorValue);
        });

        connect(processor, &FileProcessor::finished, [this]() { /*qDebug() << this->curExecFiles; */this->ui->progressBar->setValue(++this->curExecFiles / this->numberFiles * 100);});
        connect(processor, &FileProcessor::finished, thread, &QThread::quit);
        connect(processor, &FileProcessor::finished, processor, &FileProcessor::deleteLater);


        // connect(ui->pushButton_4, &QPushButton::clicked, thread, &QThread::quit);
        // connect(ui->pushButton_4, &QPushButton::clicked, processor, &FileProcessor::deleteLater);


        connect(thread, &QThread::finished, thread, &QThread::deleteLater);

        // connect(processor, &FileProcessor::fileProcessed, [](const QString &inputFile, const QString &outputFile) {
        //     qDebug() << "Обработан файл:" << inputFile << "->" << outputFile;
        // });

        thread->start();
    }
    return;
}

void MainWindow::on_pushButton_4_clicked()
{
    this->ui->pushButton_4->setEnabled(false);
    this->ui->pushButton_3->setEnabled(true);
}
