#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDomDocument>
#include <QtWidgets>
#include <QErrorMessage>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::outText(const QDomElement &rcParent,
                         const QString &rcChildName)
{
    QString data;
    data += "\t<" + rcChildName + ">" + rcParent.firstChildElement(rcChildName).text() + "</" + rcChildName + ">" + "\n";
    ui->label->setText(ui->label->text() + data);
}

void MainWindow::getHtmlDoc()
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
        if(!cbSuccess)
        {
            QErrorMessage *errorMessage = new QErrorMessage;
            QString error = "XML error at " +
                    QString::number(nErrorRow) +
                    " : " +
                    QString::number(nErrorCol) + ": " + strErrorMsg;
            errorMessage->showMessage(error);
            return;
        }

    int mount = 50;
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
                if(mount == 0) return;

                ui->label->setText(ui->label->text() + "<Item>\n");
                outText(elementItem, "title");
                outText(elementItem, "description");
                outText(elementItem, "pubDate");
                outText(elementItem, "link");
                ui->label->setText(ui->label->text() + "</Item>\n");
                elementItem = elementItem.nextSiblingElement("item");
                --mount;
            }
        }
    }
}



