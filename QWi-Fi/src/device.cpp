/***This code comes from QHotSpotQML(by H3R3TIC), but it has some changes**/

#include "device.h"

Device::Device(QString name, QString ip, QString mac, QString manufacturer,
               quint64 bytesReaded, quint64 bytesWrited, int connTime, QObject *parent) :
    _name(name)
  , _ip(ip)
  , _mac(mac)
  , _manufacturer(manufacturer)
  , _bytesReaded (bytesReaded)
  , _bytesWrited (bytesWrited)
  , _downloadRate (bytesReaded)
  , _uploadRate (bytesWrited)
  , _connTime(connTime)
  , QObject(parent)
{

}

QString Device::manufacturer() const noexcept
{
    return _manufacturer;
}

int Device::connTime() const noexcept
{
    return _connTime;
}

QString Device::name() const noexcept
{
    return _name;
}

QString Device::mac() const noexcept
{
    return _mac;
}

QString Device::ip() const noexcept
{
    return _ip;
}

quint64 Device::bytesReaded() const noexcept
{
    return _bytesReaded;
}

quint64 Device::bytesWrited() const noexcept
{
    return _bytesWrited;
}

float Device::downloadRate() const noexcept
{
    return _downloadRate;
}

float Device::uploadRate() const noexcept
{
    return _uploadRate;
}

void Device::setName(const QString &name) noexcept
{
    if (_name != name){
        _name = name;
        emit nameChanged(_name);
    }
}

void Device::setMac(const QString &mac) noexcept
{
    if (_mac != mac){
        _mac = mac;
        emit macChanged(_mac);
    }
}

void Device::setIp(const QString &ip) noexcept
{
    if (_ip != ip){
        _ip = ip;
        emit ipChanged(_ip);
    }
}

void Device::setBytesReaded(const quint64 bytesReaded) noexcept
{
    if (_bytesReaded != bytesReaded){
        _bytesReaded = bytesReaded;
        emit bytesReadedChanged(_bytesReaded);
    }
}

void Device::setBytesWrited(const quint64 bytesWrited) noexcept
{
    if (_bytesWrited != bytesWrited){
        _bytesWrited = bytesWrited;
        emit bytesWritedChanged(_bytesWrited);
    }
}

void Device::setDownloadRate(const quint64 downloadRate) noexcept
{
    if (_downloadRate != downloadRate){
        _downloadRate = downloadRate;
        emit downloadRateChanged(_downloadRate);
    }
}

void Device::setUploadRate(const quint64 uploadRate) noexcept
{
    if (_uploadRate != uploadRate){
        _uploadRate = uploadRate;
        emit uploadRateChanged(_uploadRate);
    }
}

void Device::setManufacturer(const QString &manufacturer) noexcept
{
    if (_manufacturer != manufacturer) {
        _manufacturer = manufacturer;
        emit manufacturerChanged(_manufacturer);
    }
}


void Device::setConnTime(const int connTime) noexcept
{
    if (_connTime != connTime) {
        _connTime = connTime;
        emit connTimeChanged(_connTime);
    }
}

