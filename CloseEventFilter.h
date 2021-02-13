#ifndef CLOSEEVENTFILTER_H
#define CLOSEEVENTFILTER_H

#include <QObject>
#include <QEvent>

class CloseEventFilter : public QObject
{
    Q_OBJECT
public:
    CloseEventFilter(QObject* aParent);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void closed();
};

#endif // CLOSEEVENTFILTER_H
