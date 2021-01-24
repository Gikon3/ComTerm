#ifndef COMTERM_H
#define COMTERM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ComTerm; }
QT_END_NAMESPACE

class ComTerm : public QMainWindow
{
    Q_OBJECT

public:
    ComTerm(QWidget *parent = nullptr);
    ~ComTerm();

private:
    Ui::ComTerm *ui;
};
#endif // COMTERM_H
