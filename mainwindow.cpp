#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <QObject>
#include <QGridLayout>
#include <QWidget>
#include <QProcess>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QByteArray>
#include <QMessageBox>
#include <QStringList>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cur_path = new QString(QDir::currentPath());
    temp_path = new QString(QDir::tempPath());

    QWidget *w = new QWidget();



    QPushButton *btn = new QPushButton();
    btn->setText("execute");
    connect(btn,SIGNAL(clicked()),this,SLOT(slot_excute_shell()));

    console = new QLineEdit();
    console_label = new QLabel();
    console_label->setText("请输入。。。");

    QGridLayout *gLayout = new QGridLayout();
    gLayout->addWidget(btn, 0, 0, 1, 1);
    gLayout->addWidget(console, 0, 1, 1, 1);
    //gLayout->addWidget(console_label, 1, 0, 1, 1);
    gLayout->addWidget(ui->tx_output,1, 0, 1, 1);
    //gLayout->addWidget(ui->tx_err_output, 1, 1, 1, 1);

    w->setLayout(gLayout);

    this->setCentralWidget(w);


}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::shell_command(QString *command, QString par)
{

}

void MainWindow::slot_excute_shell()
{
    QProcess *qPro = new QProcess(this);
    QString str_shell = console->text();
    qDebug()<< "----------------------\n" << "console str_shell:  "<< str_shell;
    //QStringList strList = str_shell->split(" ");

    connect(qPro, SIGNAL(readyRead()), this, SLOT(slot_read_buf()));
    connect(qPro, SIGNAL(finished(int)), this, SLOT(slot_read_finish()));


    qPro->start(str_shell);


}

void MainWindow::slot_read_buf()
{
    QProcess *qProcess = (QProcess *)sender();
    QByteArray byteArr_output = qProcess->readAllStandardOutput();
    QByteArray byteArr_err_outpu = qProcess->readAllStandardError();
   // QString str;
    //str.prepend(byteArr);
    //result = &str;
    result_output.prepend(byteArr_output);
    result_err_output.prepend(byteArr_err_outpu);

    //result = QString::prepend(&byteArr);
   // QMessageBox::warning(NULL,"",str);
    //qDebug()<<"slot_read_buf: " << byteArr_output;
   // qDebug() << "slot_read_err_output: " << byteArr_err_outpu;
    //console_label->setText(str);
    //ui->tx_output->setText(result_output);
    //ui->tx_err_output->setText(result_err_output);

}

void MainWindow::slot_read_finish()
{
    //console_label->setText("");
    qDebug()<<"read_finish result_output: "<<result_output;
    qDebug()<<"read_finish result_err_output: "<<result_err_output;
    qDebug() << "###################################\n";
    //console_label->setText(result);



}
