#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class QThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void processFinished(int runTime);

    void checkStatus();

    void on_actionExecutavel_triggered();

    void on_actionEntrada_triggered();

    void on_actionSaida_triggered();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_actionRodar_triggered();

    void on_actionParar_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
    QThread *m_thread;
    QString m_procStdin;
    QString m_procStdout;
    QString m_procExe;
};

#endif // MAINWINDOW_H
