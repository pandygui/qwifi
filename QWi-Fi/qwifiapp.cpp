#include <QThread>
#include <QDebug>
#include <QStringList>
#include <QRegExp>
#include <QNetworkInterface>

#include "qwifi_global.h"
#include "qwifiapp.h"
#include "worker.h"

QWiFiApp::QWiFiApp(QObject *parent) : QObject(parent)
{
}

void QWiFiApp::startWiFiAP(QString inthernetIface, QString wifiIface, QString ssid, QString password){
    QStringList arguments;
    arguments << "create_ap" << "--no-virt" << wifiIface << inthernetIface << ssid << password;
    QThread *thread = new QThread(this);
    Worker *worker = new Worker("pkexec", arguments);
    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(readyOutput(QString)),this,SLOT(wifiReadyOutput(QString)));
    connect(worker, SIGNAL(readyErrorOutput(QString)),this,SLOT(wifiReadyErrorOutput(QString)));
    connect(worker, SIGNAL(processfinished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(processfinished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void QWiFiApp::wifiReadyOutput(QString output){

    if(AP_ENABLED.indexIn(output)!=-1){
        setActiveIterface(output.split(":")[0]);
        emit wifiAPStarted();
    }else if(CLIENT_IN_REG_EXP.indexIn(output)!=-1){
        qDebug() << output << "client IN";
         emit  newMessage(output);
    }else if(CLIENT_OUT_REG_EXP.indexIn(output)!=-1){
        qDebug() << output << "client OUT";
         emit  newMessage(output);
    }
}
void QWiFiApp::wifiReadyErrorOutput(QString errorOutput){
    qDebug() << errorOutput;
    emit  newMessage(errorOutput);
}

void QWiFiApp::stopWiFiAP(){
    QProcess *process = new QProcess(this);
    QStringList arguments;
    arguments << "create_ap" << "--stop" << _activeInterface;
    connect(process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
          [=](int exitCode, QProcess::ExitStatus){
        if (exitCode != 0) {
            qDebug() << "Errror ocurred";
        }else{
            setActiveIterface("");
            emit wifiAPStopped();
        }
    });
    process->start("pkexec", arguments);
}

void QWiFiApp::setActiveIterface(QString iface){
    _activeInterface = iface;
}

void QWiFiApp::denyAcces(QString mac,QString ip){

}


