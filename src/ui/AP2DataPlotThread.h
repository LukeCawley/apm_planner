#ifndef AP2DATAPLOTTHREAD_H
#define AP2DATAPLOTTHREAD_H

#include <QThread>
#include <QVariantMap>
#include <QSqlDatabase>
#include "MAVLinkDecoder.h"
#include "libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink.h"
class AP2DataPlotThread : public QThread
{
    Q_OBJECT
public:
    explicit AP2DataPlotThread(QObject *parent = 0);
    void loadFile(QString file,QSqlDatabase *db);
    void stopLoad() { m_stop = true; }
private:
    void loadDataFieldsFromValues();
    QString m_fileName;
    bool m_stop;
    QSqlDatabase *m_db;
    QString makeInsertTableString(QString tablename, QString variablestr);
    QString makeCreateTableString(QString tablename, QString formatstr,QString variablestr);
    int m_fieldCount;
    MAVLinkDecoder *decoder;
    QMap<QString,QString> m_msgNameToInsertQuery;
protected:
    void run();
signals:
    void startLoad();
    void loadProgress(qint64 pos,qint64 size);
    void payloadDecoded(int index,QString name,QVariantMap map);
    void done(int errors,MAV_TYPE type);
    void error(QString errorstr);
    void lineRead(QString line);
private slots:
    void valueChanged(const int uasId, const QString& name, const QString& unit, const QVariant& value, const quint64 msec);
};

#endif // AP2DATAPLOTTHREAD_H
