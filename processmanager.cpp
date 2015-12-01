#include "processmanager.h"
#include <QTime>
#include <QFile>
#include <QProcess>

#include <QDebug>

ProcessManager::ProcessManager(QObject *parent) :
    QObject(parent),
    m_procStdin(""),
    m_procStdout(""),
    m_procExe("")
{
}

ProcessManager::~ProcessManager()
{
    qDebug() << "I was destroyed!";
}

void ProcessManager::run()
{
    QProcess proc;

    proc.setStandardInputFile(m_procStdin);
    proc.setStandardOutputFile(m_procStdout);
    proc.setProgram(m_procExe);

    proc.start();
    proc.waitForStarted();

    QTime startTime = QTime::currentTime();

    proc.waitForFinished();

    int runTime = startTime.msecsTo(QTime::currentTime());

    emit processFinished(runTime);
}

void ProcessManager::setExe(const QString &file)
{
    // TODO: Validar existencia do arquivo
    m_procExe = file;
}

void ProcessManager::setStdout(const QString &file)
{
    m_procStdout = file;
}

void ProcessManager::setStdin(const QString &file)
{
    // TODO: Validar existencia do arquivo
    m_procStdin = file;
}
