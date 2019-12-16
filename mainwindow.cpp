#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::moveCursor(int t_arg)
{
    Q_UNUSED(t_arg);
    QJsonObject _jobj;
    _jobj["target"] = "mouse";
    _jobj["method"] = "move";
    _jobj["x"] = ui->spinBox->value();
    _jobj["y"] = ui->spinBox_2->value();
    qDebug() << sock->write(QJsonDocument(_jobj).toJson());
    qDebug() << sock->waitForBytesWritten();

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sock = new QTcpSocket;
//    tcpSocket->bind(QHostAddress("192.168.0.107"), 10101);
    connect(sock, &QTcpSocket::bytesWritten, this, &MainWindow::bytesWritten);
    connect(sock, &QTcpSocket::connected, this, &MainWindow::_connected);


    connect(sock, &QTcpSocket::readyRead, [&] () {
        QByteArray _array = sock->readAll();
        if(_array.isEmpty())
            qDebug() << "read empty";
        else {
            qDebug() << "read" << _array << _array.toInt(nullptr, 16);
        }
    });




//    connect(tcpSocket, &QTcpSocket::error, [] (QAbstractSocket::SocketError t_error) {
//        qDebug() << "socket connected";
//    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_connected()
{
    qDebug() << "_connected";
}

void MainWindow::bytesWritten(qint64 t_cout)
{
}

void MainWindow::on_pushButton_clicked()
{
    QJsonObject _jobj;
    _jobj["target"] = "mouse";
    _jobj["method"] = "move";
    _jobj["x"] = ui->spinBox->value();
    _jobj["y"] = ui->spinBox_2->value() + 1;
    qDebug() << sock->write(QJsonDocument(_jobj).toJson());
    qDebug() << sock->waitForBytesWritten();
}

void MainWindow::on_pushButton_2_clicked()
{
    QJsonObject _jobj;
    QThread::msleep(300);
    _jobj["target"] = "mouse";
    _jobj["method"] = "click";
    if(ui->radioButton->isChecked())
        _jobj["code"] = "BTN_LEFT";
    else {
        _jobj["code"] = "BTN_RIGHT";
    }
//    QThread::sleep(1);
    qDebug() << sock->write(QJsonDocument(_jobj).toJson());
    qDebug() << sock->waitForBytesWritten();

}

void MainWindow::on_pushButton_3_clicked()
{
    QJsonObject _jobj;
    _jobj["target"] = "keyboard";
    _jobj["method"] = "type";
    _jobj["text"] = ui->textEdit->toPlainText();
    qDebug() << sock->write(QJsonDocument(_jobj).toJson());
    qDebug() << sock->waitForBytesWritten();
}

void MainWindow::on_pushButton_5_clicked()
{
    if(ui->radioButton_3->isChecked()) {
        sock->connectToHost("127.0.0.1", 10101);
    } else {
//        sock->connectToHost("192.168.0.107", 10101);
                sock->connectToHost("192.168.0.106", 10101);

    }
    if(!sock->waitForConnected(5000)) {
        qDebug() << " Error";
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    QJsonObject _jobj;
    _jobj["target"] = "mouse";
    _jobj["method"] = "move_click";
    _jobj["x"] = ui->spinBox->value();
    _jobj["y"] = ui->spinBox_2->value();
    if(ui->radioButton->isChecked())
        _jobj["code"] = "BTN_LEFT";
    else {
        _jobj["code"] = "BTN_RIGHT";
    }
    QThread::sleep(1);
    qDebug() << sock->write(QJsonDocument(_jobj).toJson());
    qDebug() << sock->waitForBytesWritten();
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    moveCursor(arg1);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    moveCursor(arg1);
}

void MainWindow::on_pushButton_7_clicked()
{
    QJsonObject _jobj;
    _jobj["target"] = "keyboard";
    _jobj["method"] = "press";
    _jobj["code"] = ui->lineEdit->text();
    sock->write(QJsonDocument(_jobj).toJson());
    sock->waitForBytesWritten();
}

void MainWindow::on_pushButton_8_clicked()
{
    QJsonObject _jobj;
    _jobj["target"] = "keyboard";
    _jobj["method"] = "release";
    _jobj["code"] = ui->lineEdit->text();
    sock->write(QJsonDocument(_jobj).toJson());
    sock->waitForBytesWritten();
}

void MainWindow::on_pushButton_9_clicked()
{
    QThread::sleep(1);
    QJsonDocument _jDoc = QJsonDocument::fromJson(ui->textEdit_2->toPlainText().toUtf8());
    qDebug() << _jDoc.object();
    sock->write(_jDoc.toJson());
    sock->waitForBytesWritten();

}

void MainWindow::on_textEdit_2_textChanged()
{
    QByteArray _array = ui->textEdit_2->toPlainText().toUtf8();
    if(_array.isEmpty())
        return;
    if(_array[_array.size()- 1] == '\n') {
        _array.remove(_array.size() - 1, 1);
        ui->textEdit_2->clear();
        ui->textEdit_2->setText(_array);
        QJsonDocument _jDoc = QJsonDocument::fromJson(ui->textEdit_2->toPlainText().toUtf8());
        qDebug() << _jDoc.object();
        sock->write(_jDoc.toJson());
        sock->waitForBytesWritten();
    }
}

void MainWindow::on_pushButton_4_clicked()
{


    QJsonObject _jMsgToSend;
    _jMsgToSend["x"] = 1033;
    _jMsgToSend["y"] = 165;
    _jMsgToSend["target"] = "mouse";
    _jMsgToSend["method"] = "move_click";
    _jMsgToSend["code"] = "BTN_LEFT";

    qDebug() << _jMsgToSend["x"].toInt() << _jMsgToSend["y"].toInt();

    for(int i = 0; i < 7; i++) {
        sock->write(QJsonDocument(_jMsgToSend).toJson());
        while(sock->waitForBytesWritten() != true);
        QThread::msleep(10);

    }


}

void MainWindow::on_pushButton_10_clicked()
{
    QJsonObject _jMsgToSend2;
    _jMsgToSend2["x"] = 1033;
    _jMsgToSend2["y"] = 485;
    _jMsgToSend2["target"] = "mouse";
    _jMsgToSend2["method"] = "move_click";
    _jMsgToSend2["code"] = "BTN_LEFT";

    qDebug() << _jMsgToSend2["x"].toInt() << _jMsgToSend2["y"].toInt();

    for(int i = 0; i < 7; i++) {
        sock->write(QJsonDocument(_jMsgToSend2).toJson());
        while(sock->waitForBytesWritten() != true);
        QThread::msleep(10);

    }



}
