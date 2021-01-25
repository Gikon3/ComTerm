#ifndef COMDATAFORM_H
#define COMDATAFORM_H

#include <QWidget>

namespace Ui {
class ComDataForm;
}

class ComDataForm : public QWidget
{
    Q_OBJECT

public:
    explicit ComDataForm(QWidget *parent = nullptr);
    ~ComDataForm();

private slots:
    void asciiComboBoxClicked(bool check);
    void hexComboBoxClicked(bool check);

private:
    Ui::ComDataForm *ui;
};

#endif // COMDATAFORM_H
