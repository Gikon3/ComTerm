#ifndef TABFORM_H
#define TABFORM_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class TabForm;
}

class TabForm : public QWidget
{
    Q_OBJECT

public:
    explicit TabForm(const QSerialPortInfo &info, bool *ok = nullptr, QWidget *parent = nullptr);
    ~TabForm();

private slots:
    void rxClearPushButtonClicked();
    void txClearPushButtonClicked();
    void sendButtonClicked();

private:
    void txAppend(const QByteArray& array);
    void handleReadyRead();

private:
    Ui::TabForm *ui;
    QSerialPort *port;
};

#endif // TABFORM_H
