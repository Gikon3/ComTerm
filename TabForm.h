#ifndef TABFORM_H
#define TABFORM_H

#include <QWidget>

namespace Ui {
class TabForm;
}

class TabForm : public QWidget
{
    Q_OBJECT

public:
    explicit TabForm(QWidget *parent = nullptr);
    ~TabForm();
    void append(const QByteArray& array);

private slots:
    void rxClearPushButtonClicked();
    void txClearPushButtonClicked();

private:
    Ui::TabForm *ui;
};

#endif // TABFORM_H
