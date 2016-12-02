#include "maincontent.h"
#include "ui_maincontent.h"
#include "mainwindow.h"
#include <QDebug>
#include <string>
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
MainContent::MainContent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainContent)
{
    ui->setupUi(this);
    cr = new Crypt();
}

MainContent::~MainContent()
{
    delete ui;
}

void MainContent::on_pushButton_3_clicked()
{
    this->hide();
}

void MainContent::setFnameLname(QString log)
{
    ui->label_3->setText(db->getFname(log));
    ui->label_4->setText(db->getLname(log));
    ui->label_6->setText(log);
}

void MainContent::on_pushButton_clicked()
{
    QString text;
    text=ui->lineEdit->text();

    //qDebug()<<
    std::string stdstr= cr->myCrypt(text.toStdString(),"abababababababab","babababababababa",true);

    QString str(stdstr.c_str());

    QString fileName=QFileDialog::getSaveFileName(this,tr("Save File"),
                                                  "/Users/nikitakurganov/Documents/Qt/Files/untitled.txt",
                                                  tr("Text files (*.txt);;All files (*.*)"));

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out<<str;

   // qDebug()<< "encrypt: "<<str;



}

void MainContent::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/Users/nikitakurganov/Documents/Qt/Files",
                                                    tr("Text files (*.txt);;All files (*.*)"));
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray data;
    data = file.readAll();
    std::string stdstr=cr->myCrypt(QString(data).toStdString(),"abababababababab","babababababababa",false);
    QString str1(stdstr.c_str());
    //qDebug()<<"decrypt: "<<str1;
    ui->textEdit->insertPlainText(str1);
}
