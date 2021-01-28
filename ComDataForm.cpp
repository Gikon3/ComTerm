#include "ComDataForm.h"
#include "ui_ComDataForm.h"

ComDataForm::ComDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComDataForm)
{
    ui->setupUi(this);
}

ComDataForm::~ComDataForm()
{
    delete ui;
}

// slots
void ComDataForm::asciiComboBoxClicked(bool check)
{
    if(check) {
        ui->asciiText->show();
        return;
    }
    ui->asciiText->hide();
}

void ComDataForm::hexComboBoxClicked(bool check)
{
    if(check) {
        ui->hexText->show();
        return;
    }
    ui->hexText->hide();
}
// -- slots

void ComDataForm::clear()
{
    ui->asciiText->clear();
    ui->hexText->clear();
}

void ComDataForm::append(const QByteArray& array)
{
    ui->asciiText->moveCursor(QTextCursor::End);
    ui->asciiText->insertPlainText(array);
    QString strHex;
    QString formatStr(array.toHex().toUpper());
    for(int i = 0; i < formatStr.size() / 2; ++i) {
        strHex += formatStr[i * 2];
        strHex += formatStr[i * 2 + 1] + " ";
    }
    ui->hexText->moveCursor(QTextCursor::End);
    ui->hexText->insertPlainText(strHex);
}

void ComDataForm::retranslate()
{
    ui->retranslateUi(this);
}

void ComDataForm::appendStartFile()
{
    ui->asciiText->appendPlainText(tr("< Start of file >\n"));
    ui->hexText->appendPlainText("\n");
}

void ComDataForm::appendEndFile()
{
    ui->asciiText->appendPlainText(tr("< End of file >\n"));
    ui->hexText->appendPlainText("\n");
}
