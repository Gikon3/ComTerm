#ifndef TABFORM_H
#define TABFORM_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class TabForm;
}

class TabForm : public QWidget
{
    Q_OBJECT

public:
    explicit TabForm(QSerialPort *port = nullptr, QWidget *parent = nullptr);
    ~TabForm();
    void rxAppend(const QByteArray& array);

private slots:
    void rxClearPushButtonClicked();
    void txClearPushButtonClicked();
    void sendButtonClicked();

private:
    void txAppend(const QByteArray& array);

private:
    Ui::TabForm *ui;
    QSerialPort *port;
};

#endif // TABFORM_H
