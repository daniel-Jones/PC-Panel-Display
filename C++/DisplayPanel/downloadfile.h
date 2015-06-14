#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QDir>

class DownloadFile
{
public:
    DownloadFile();
    ~DownloadFile();
    void DownloadUrl(const QString &url, const QString &aPathInClient);
};

#endif // DOWNLOADFILE_H
