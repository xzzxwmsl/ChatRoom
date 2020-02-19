﻿#include "connect.h"
#include "dialogregister.h"
#include "ui_dialogregister.h"

#include <QSqlQuery>
#include <qmessagebox.h>

DialogRegister::DialogRegister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRegister)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);// 禁止最大化按钮
    setFixedSize(this->width(),this->height());//禁止该变窗口大小

    //设置背景
   setBackground(":/Pictures/background3.png");//这里可以换

    this->setWindowTitle(QStringLiteral("Chat"));//设置title
    ui->username->setPlaceholderText(QStringLiteral("        Input UserName         "));
    ui->username->setClearButtonEnabled(true);

    ui->password->setPlaceholderText(QStringLiteral("        Input PassWord         "));
    ui->password->setEchoMode(QLineEdit::Password);//设置为密码格式
    ui->password->setClearButtonEnabled(true);

    ui->IP->setPlaceholderText("Input host name");

    ui->passwordagain->setPlaceholderText(QStringLiteral("        Password Again         "));
    ui->passwordagain->setEchoMode(QLineEdit::Password);//设置为密码格式
    ui->passwordagain->setClearButtonEnabled(true);
}

DialogRegister::~DialogRegister()
{
    delete ui;
}



void DialogRegister::on_Register_clicked()
{
    QString username = ui->username->text();
    QString passwordOnce = ui->password->text();
    QString passwordTwice = ui->passwordagain->text();
    ip=ui->IP->text();

    if(!username.isEmpty() && !passwordOnce.isEmpty() && !passwordTwice.isEmpty()&& !ip.isEmpty()){

        if(passwordOnce!=passwordTwice){
            QMessageBox::information(this,QStringLiteral("Tips"),QStringLiteral("different between password"),QMessageBox::Ok);
        }else{
            //向数据库插入信息
            if(isRight(username,passwordOnce)){
                QMessageBox::information(this,QStringLiteral("Tips"),QStringLiteral("Register successfully"),QMessageBox::Ok);
                emit send(username,passwordOnce,ip); //向父窗口发送信息
                this->close();
            }else{
                QMessageBox::information(this,QStringLiteral("Tips"),QStringLiteral(" same username"),QMessageBox::Ok);
            }

        }

    }else{
        QMessageBox::information(this,QStringLiteral("Tips"),QStringLiteral("Input Username or Password or IP"),QMessageBox::Ok);
    }
}

void DialogRegister::on_Cancel_clicked()
{
    this->close();
}

void DialogRegister::setBackground(QString src){
    QImage Image;
    Image.load(src);
    QPixmap pixmap = QPixmap::fromImage(Image);
    QPixmap fitpixmap = pixmap.scaled(400, 404, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(fitpixmap));
    this->setPalette(pal);
}

bool DialogRegister::isRight(QString username, QString password)
{
    Connect *con = new Connect(ip);
    if(con->right()){
        QSqlQuery query;
        query.prepare("INSERT INTO usr (name, password) "
                              "VALUES (:name, :password)");
        query.bindValue(":name", username);
        query.bindValue(":password", password);
        if(query.exec()){
            return true;
        }
    }

    return false;

}
