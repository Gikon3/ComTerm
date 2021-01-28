#ifndef TABFORM_H
#define TABFORM_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFile>

namespace Ui {
class TabForm;
}

class TabForm : public QWidget
{
    Q_OBJECT

public:
    explicit TabForm(const QSerialPortInfo &info, bool *ok = nullptr, QWidget *parent = nullptr);
    ~TabForm();
    void retranslate();

private slots:
    void rxClearButtonClicked();
    void txClearButtonClicked();
    void sendButtonClicked();
    void recordToolButtonClicked();
    void recordButtonClicked();
    void sendFileToolButtonClicked();
    void sendFileButtonClicked();

private:
    void txAppend(const QByteArray& array);
    void handleReadyRead();
    QString openExplorer(QString &lastFilePath);

private:
    Ui::TabForm *ui;
    QSerialPort *port;
    QString sendLastFilePath;
    QString recordLastFilePath;
    QFile *recordFile;
};

#endif // TABFORM_H
