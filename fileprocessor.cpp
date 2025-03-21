#include "fileprocessor.h"


void FileProcessor::processFile(const QString &file, const QString &outputPath, bool deleteInput, bool overwrite, const QByteArray &xorValue)
{

    QDir dir("./input");
    QString inputFilePath = dir.filePath(file);
    QString outputFilePath = outputPath + "\\" + file;

    // Обработка конфликта имен
    if (!overwrite && QFile::exists(outputFilePath)) {

        auto it = map.find(file);
        if (it == map.end())
            map[file] = 0;


        while (QFile::exists(outputFilePath)) {
            outputFilePath = outputPath + "\\" + QString("%1_%2").arg(QFileInfo(file).baseName()).arg(map[file]) + "." + QFileInfo(file).suffix();
            map[file]++;
        }
    }

    // Чтение и модификация файла
    QFile inputFile(inputFilePath);
    QFile outputFile(outputFilePath);


    if (inputFile.open(QIODevice::ReadOnly) ){
        if (outputFile.open(QIODevice::WriteOnly)) {
            while (!inputFile.atEnd()) {
                QByteArray chunk = inputFile.read(8192);
                for (int i = 0; i < chunk.size(); ++i) {
                    chunk[i] = chunk[i] ^ xorValue[i % xorValue.size()];
                }
                outputFile.write(chunk);
            }
            outputFile.close();
        }
        inputFile.close();
    }

    // Удаление входного файла, если необходимо
    if (deleteInput) {
        QFile::remove(inputFilePath);
    }

    emit finished();
    //emit fileProcessed(inputFilePath, outputFilePath);
}
