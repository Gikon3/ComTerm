#include "CloseEventFilter.h"

CloseEventFilter::CloseEventFilter(QObject* aParent)
    : QObject(aParent)
{}

bool CloseEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::Close) {
        emit closed();
        return true;
    }
    return QObject::eventFilter(obj, event);
}
