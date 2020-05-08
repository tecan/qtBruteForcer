#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::generateCoins() //puts coins in text file to be read in by randomizer
{
  //  qDebug() << "generating coins to textfile";

    QFile file("wordlist.txt");
    if(file.open(QIODevice::ReadWrite |  QIODevice::Append | QIODevice::Text))// QIODevice::Append |
    {
        QTextStream stream(&file);
        file.seek(file.size());

        for(int i=0 ; i < _coins.count() ; i++)
        {
            //stream << QString::number(coini) << ":" <<_coins[i] << endl;
            stream <<_coins[i] << endl;
            coini++;
        }
    }
        _coins.clear();
        file.close();

}

void MainWindow::GenerateCoins3(QString chars,int length,int total)
{
    QString arr = chars;//"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    QString data;
   // _total = 10000;
    _total = total;
    _count = 0;
    _state = false;
 //   _length = 8;
    _length = length;

    for (int i=0; i < _length; i++){
       data += " ";
    }
   // QString data = "        ";


     qDebug() << "running combo util";

    combinationUtil(arr, arr.length(), _length, 0, data, 0);
}

void MainWindow::combinationUtil(QString arr, int n, int r, int index, QString data, int i)
{
    if(_state)
        return;
    if(index == r)
    {
        //qDebug() << data;

        // write to the database
        _coins.append(data);
if (gentotext == 1){
        if(_coins.count() > 80) //if using sql use 300
        {
            generateCoins(); //textversion
        }else{
            generateCoins();
           qDebug() << "putting in last little bit";
        }
}else {
    if(_coins.count() > 100) //if using sql use 300
    {
     //   insertCoins(); //sqlversion
    }else{
     //   insertCoins();
       qDebug() << "putting in last little bit";
    }
}
        _count++;
        if(_count >= _total)
        {
            _state = true;
        }
        return;
    }

    if(i >= n)
        return;

    data[index] = arr[i];
//    data.at(index) = arr.at(i);

    combinationUtil(arr, n, r, index+1, data, i+1);
    combinationUtil(arr, n, r, index, data, i+1);
}

void MainWindow::on_wordlist_clicked()
{
    coini=0;
    gentotext=1;
  GenerateCoins3("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890",ui->length->text().toInt(),ui->ammount->text().toInt());

}

void MainWindow::on_actionexit_triggered()
{
        QApplication::quit();
}

void MainWindow::on_pushButton_clicked()
{
//https://www.linkedin.com/pulse/first-qt-app-simple-port-scanner-brian-warner
    ui->results->setText("");
    QString host = ui ->lineEditHost->text();
    QString startPort = ui ->lineEditStartPort->text();
    quint16 startPortInt = startPort.toUShort();
    QString endPort = ui ->lineEditEndPort->text();
    quint16 endPortInt = endPort.toUShort();
    QString timeout = ui ->lineEditTimeout->text();
    quint16 timeoutInt = timeout.toUShort();
    qInfo() << host;
    QTcpSocket socket;


    for(quint16 i = startPortInt; i < endPortInt; i++){

            socket.connectToHost(host, i);
            if(socket.waitForConnected(timeoutInt)){
                qInfo() << "Open Port: " << i;
                QString openPort = QString::number(i);
                ui->results->append("Port: " + openPort);
                socket.disconnectFromHost();
            }
    }
    ui->results->append("Scan Complete");
   qInfo() << "Scan Complete";
}

void MainWindow::on_crack7z_clicked()
{
    QProcess::execute("7za.exe x -y -p");

//    QProcess process;
//    process.start(file);

//    QProcess::startDetached(QDir::homepath + "/file.exe");
   // 7za.exe x -y -p
}

void MainWindow::on_crack7z_2_clicked()
{
   // unzip -t -P aha t.zip
}

