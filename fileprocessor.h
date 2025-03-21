#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QMap>

class FileProcessor : public QObject {
    Q_OBJECT

public:
    FileProcessor (QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void processFile(const QString &file, const QString &outputPath, bool deleteInput, bool overwrite, const QByteArray &xorValue);

signals:
    void fileProcessed(const QString &inputFile, const QString &outputFile);
    void finished();
private:
    QMap<QString, int> map;
};

#endif // FILEPROCESSOR_H
