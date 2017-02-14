#ifndef DBUSFILEDIALOGMANAGER_H
#define DBUSFILEDIALOGMANAGER_H

#include <QObject>
#include <QDBusObjectPath>

class DBusFileDialogManager : public QObject
{
public:
    explicit DBusFileDialogManager(QObject *parent = 0);

    QDBusObjectPath createDialog(QString key);
    void destroyDialog(const QDBusObjectPath &path);
    QList<QDBusObjectPath> dialogs() const;
    QString errorString() const;

    bool isUseFileChooserDialog() const;

private:
    void onDialogDestroy();

    QString m_errorString;
    QMap<QDBusObjectPath, QObject*> m_dialogObjectMap;
};

#endif // DBUSFILEDIALOGMANAGER_H
