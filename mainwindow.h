#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QString>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString shell_command(QString *command, QString par);

public slots:
    void slot_excute_shell();
    void slot_read_buf();
    void slot_read_finish();

private:
    Ui::MainWindow *ui;


    QLineEdit *console;
    QLabel    *console_label;
    QString   result_output;
    QString   result_err_output;
    QString   *cur_path;
    QString   *temp_path;
};

#endif // MAINWINDOW_H
