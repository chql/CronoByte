#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>
#include <QString>

class ProcessManager : public QObject
{
    Q_OBJECT
public:
    explicit ProcessManager(QObject *parent = 0);
    ~ProcessManager();
    void setStdout(const QString& file);
    void setStdin(const QString& file);
    void setExe(const QString& file);
signals:
    void processFinished(int runTime);
public slots:
    void run();
private:
    QString m_procStdin;
    QString m_procStdout;
    QString m_procExe;
};

#endif // PROCESSMANAGER_H
