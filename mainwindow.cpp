#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "processmanager.h"
#include <QThread>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_thread(new QThread),
    m_procStdin(""),
    m_procStdout(""),
    m_procExe("")
{
    ui->setupUi(this);

    ui->statusBar->addPermanentWidget(ui->statusLabel);
    ui->statusLabel->setText("Aguardando definições...");

    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
}

MainWindow::~MainWindow()
{
    on_actionParar_triggered();
    delete m_thread;
    delete ui;
}

void MainWindow::processFinished(int runTime)
{
    QString unit = "ms";
    double time = (double)runTime;

    if(time >= 1000)
    {
        unit = "s";
        time /= 1000;
    }

    QString str = QString("%1 (%2 %3)").arg(
                                            m_procExe.split("/").last(),
                                            QString::number(time,'g',4),
                                            unit);
    ui->listWidget->addItem(str);

    on_actionParar_triggered();
    ui->listWidget->scrollToBottom();
    ui->listWidget->item(ui->listWidget->count()-1)->setSelected(true);

    ui->statusLabel->setText("Pronto!");
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
}

void MainWindow::checkStatus()
{
    // validacao real sera feita pelo ProcessManager
    if(m_procStdin.length() > 0
            && m_procStdout.length() > 0
            && m_procExe.length() > 0)
    {
        ui->statusLabel->setText("Pronto!");
        ui->pushButton_2->setEnabled(true);
    }
}

void MainWindow::on_actionExecutavel_triggered()
{
    QFileDialog fd(this);

    fd.setAcceptMode(QFileDialog::AcceptOpen);
    fd.setFileMode(QFileDialog::ExistingFile);

#ifdef Q_OS_WIN32
    fd.setNameFilter("Executável do Windows (*.exe)");
#else
    fd.setNameFilter("Executável (*.*)");
#endif

    if(fd.exec() == QDialog::Accepted)
    {
        QString file = fd.selectedFiles().first();
        m_procExe = file;
        ui->lineEdit->setText(file.split('/').last());
    }

    checkStatus();
}

void MainWindow::on_actionEntrada_triggered()
{
    QFileDialog fd(this);

    fd.setAcceptMode(QFileDialog::AcceptOpen);
    fd.setFileMode(QFileDialog::ExistingFile);
    fd.setNameFilter("Qualquer Arquivo (*.*)");

    if(fd.exec() == QDialog::Accepted)
    {
        QString file = fd.selectedFiles().first();
        m_procStdin = file;
        ui->lineEdit_2->setText(file.split('/').last());
    }

    checkStatus();
}

void MainWindow::on_actionSaida_triggered()
{
    QFileDialog fd(this);

    fd.setAcceptMode(QFileDialog::AcceptSave);
    fd.setFileMode(QFileDialog::AnyFile);
    fd.setNameFilter("Qualquer arquivo (*.*)");

    if(fd.exec() == QDialog::Accepted)
    {
        QString file = fd.selectedFiles().first();
        m_procStdout = file;
        ui->lineEdit_3->setText(file.split('/').last());
    }

    checkStatus();
}

void MainWindow::on_toolButton_clicked()
{
    on_actionExecutavel_triggered();
}

void MainWindow::on_toolButton_2_clicked()
{
    on_actionEntrada_triggered();
}

void MainWindow::on_toolButton_3_clicked()
{
    on_actionSaida_triggered();
}

void MainWindow::on_actionRodar_triggered()
{
    ProcessManager *proc = new ProcessManager;

    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->statusLabel->setText("Executando!");

    proc->setExe(m_procExe);
    proc->setStdin(m_procStdin);
    proc->setStdout(m_procStdout);

    connect(proc,SIGNAL(processFinished(int)),SLOT(processFinished(int)));

    proc->connect(m_thread,SIGNAL(started()),SLOT(run()));
    proc->connect(m_thread,SIGNAL(finished()),SLOT(deleteLater()));
    proc->moveToThread(m_thread);

    m_thread->start();
}

void MainWindow::on_actionParar_triggered()
{
    if(m_thread->isFinished() == false)
    {
        m_thread->quit();
        m_thread->wait();
    }
    checkStatus();
}

void MainWindow::on_pushButton_2_clicked()
{
    on_actionRodar_triggered();
}

void MainWindow::on_pushButton_clicked()
{
    on_actionParar_triggered();
}
