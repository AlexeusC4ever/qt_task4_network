#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTextStream;
class QDomElement;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getHtmlDoc();
    void outText(const QDomElement &rcParent,
                             const QString &rcChildName);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
