#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDomDocument>
#include <QtWidgets>
#include "thread.h"
#include "mainwindow.h"

Thread::Thread() {}

QString Thread::getData()
{
    return data;
}

void Thread::run()
{
    const char g_cszUrl[] = "http://feeds.bbci.co.uk/news/rss.xml";
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
    QString hostName { g_cszUrl };
    QNetworkAccessManager manager;
    manager.connectToHost(hostName);
    QUrl url { hostName };
    QNetworkRequest request(url);

    QDomElement elementChannelPrev;


    QScopedPointer<QNetworkReply> pReply(manager.get(request));
    QEventLoop loop;
    connect(pReply.get(), SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    const int cnError = pReply->error();

    if(cnError != 0)
    {
        qDebug() << "HTTP error: " << cnError;
        return;
    }

    QByteArray resData = pReply->readAll();

    QString strErrorMsg;
    int nErrorRow, nErrorCol;
    QDomDocument document;
    const bool cbSuccess = document.setContent(
                resData, true,
                &strErrorMsg, &nErrorRow, &nErrorCol);
//        if(!cbSuccess)
//        {
//            QString error = "XML error at " +
//                    QString::number(nErrorRow) +
//                    " : " +
//                    QString::number(nErrorCol) + ": " + strErrorMsg;
//            errorMessage->showMessage(error);
//            return;
//        }

    /*static*/ QDomElement elementRss = document.firstChildElement("rss");
    if(!elementRss.isNull())
    {
        QDomElement elementChannel = elementRss.firstChildElement("channel");
        while(!elementChannel.isNull())
        {
            QDomElement elementItem = elementChannel.firstChildElement("item");
//                    data = elementChannel.text();

            while(!elementItem.isNull())
            {
                if(isInterruptionRequested()) return;
                data += "title: " + elementItem.firstChildElement("title").text() + "\n";
                data += "description: " + elementItem.firstChildElement("description").text() + "\n";
                data += "pubDate: " + elementItem.firstChildElement("pubDate").text() + "\n";
                data += "link: " + elementItem.firstChildElement("link").text() + "\n";
                emit dataIsReady();
                Sleep(5000);
                elementItem = elementItem.nextSiblingElement("item");
            }
        }

    }

}

