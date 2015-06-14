// this class will download files we need
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include "downloadfile.h"

DownloadFile::DownloadFile() {

}

DownloadFile::~DownloadFile() {

}

void DownloadFile::DownloadUrl(const QString &url, const QString &aPathInClient) { // this function downloads files
    qDebug() << "downloading to " + aPathInClient + " from " + url;
    if (QFile::exists(aPathInClient))
        QFile::remove(aPathInClient);
    QNetworkAccessManager Http;
    QNetworkReply *reply = Http.get(QNetworkRequest(url));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()),&loop, SLOT(quit()));
    loop.exec();
    QUrl aUrl(url);
    QFile file(aPathInClient);
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    delete reply;
}
