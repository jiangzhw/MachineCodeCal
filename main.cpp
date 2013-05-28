#include <QtGui/QApplication>
#include<QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //指定依赖的库路径
    qApp->addLibraryPath("./Plugins");
    QString libPath=QObject::tr("");
    //添加依赖库
    foreach(QString str,qApp->libraryPaths()){
        libPath.append(str);
        libPath.append("\n");
    }
    //指定字符编码，防止中文乱码
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    MainWindow w;
    w.show();
    
    return a.exec();
}
