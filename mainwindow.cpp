#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSettings>
#include<QDebug>
#include<QMessageBox>
#include<QAxObject>
#include <windows.h>
#include<stdio.h>
#include<QUuid>
#include <tchar.h>
#include <QFile>
#include<QNetworkInterface>
#include<QCryptographicHash>
#include<QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAxObject *objIWbemLocator = new QAxObject("WbemScripting.SWbemLocator");
    //ui->textBrowser->setHtml(objIWbemLocator->generateDocumentation());
    QAxObject *objWMIService = objIWbemLocator->querySubObject("ConnectServer(QString&,QString&)",QString("."),QString("root\\cimv2"));

    QString query = QString("SELECT * FROM Win32_Processor WHERE (ProcessorId IS NOT NULL)");
    QAxObject *objInterList = objWMIService->querySubObject("ExecQuery(QString&))", query);


    QAxObject *enum1 = objInterList->querySubObject("_NewEnum");
    //ui->textBrowser_4->setHtml(enum1->generateDocumentation());
    IEnumVARIANT* enumInterface = 0;
    enum1->queryInterface(IID_IEnumVARIANT, (void**)&enumInterface);

    //ui->textBrowser_4->setHtml(enumInterface->);
    enumInterface->Reset();
    // QAxObject *item = 0;

    //qDebug()<<"the count of objinterlist is "<<QString::number(objInterList->dynamicCall("Count").toInt());
    for (int i = 0; i < objInterList->dynamicCall("Count").toInt(); i++) {
        VARIANT *theItem = (VARIANT*)malloc(sizeof(VARIANT));
        if (enumInterface->Next(1,theItem,NULL) != S_FALSE){
            QAxObject *item = new QAxObject((IUnknown *)theItem->punkVal);
            //ui->textBrowser_4->setHtml(item->generateDocumentation());



            QString doc=item->generateDocumentation();
            QFile outFile("D:/debuglog.html");
            outFile.open(QIODevice::WriteOnly|QIODevice::Append);
            QTextStream ts(&outFile);
            ts<<doc<<endl;
            if(item){
                qDebug() <<" string is "<<item->dynamicCall("ProcessorId").toString();
            }

            // item->
            //QString val =
            qDebug()<<"item name is "<< item->property("objectName").toString();

        }



    }


    /*
    //make a new startup object
    QAxObject *objConfig = objStartup->querySubObject("SpawnInstance_()");
    //set some startup attributes
    //SW_HIDE = 12;
    // SW_SHOWMAXIMIZED = 3;
    // SW_MINIMIZE = 6;
    objConfig->dynamicCall("ShowWindow",SW_SHOWMAXIMIZED);
    objConfig->dynamicCall("FillAttribute", 192);
    objConfig->dynamicCall("Title","abc123");

    //try to create a new process. There seem to be some problems with this code still but it works without crashing.
    QAxObject *objProcess = objWMIService->querySubObject("Get(QString&)",QString("Win32_Process"));
    QVariant v1 = qVariantFromValue(objConfig);
    int output1;
    QVariant v2 = qVariantFromValue((void *)&output1);
    objProcess->dynamicCall("Create(QString&,QString&,QVariant&,QVariant&)","cmd.exe /k echo \"hello\"","c:\\",v1,v2);
    //now try something new. Get a list of running processes.
    QAxObject *returnList = objWMIService->querySubObject("ExecQuery(QString&)",QString("select * from win32_process"));
    //we can see how many processes there are:
    qDebug() << "count: " << returnList->dynamicCall("Count");


    //but how do you loop over them ???
    //Here are some things I was going to try before I gave up and asked the forum.
    QAxObject *enum1 = returnList->querySubObject("_NewEnum");
    IEnumVARIANT* enumInterface; //to get this, include <windows.h>

    enum1->queryInterface(IID_IEnumVARIANT, (void**)&enumInterface);
    enumInterface->Reset(); //start at the beginning of the list.
    for (int i=0;i<returnList->dynamicCall("Count").toInt();i++)
    {
        VARIANT *theItem;
        enumInterface->Next(1,theItem,NULL);
        QAxObject *item = new QAxObject((IUnknown *)theItem->punkVal);
        qDebug() << item->dynamicCall("Caption");
    }

 */
    //#define IID_IEnumerable "{496b0abe-cdee-11d3-88e8-00902754c43a}";

    //#define IID_IEnumerator "{496B0ABF-CDEE-11D3-88E8-00902754C43A}";
    //for(; ! e.atEnd(); e.moveNext())
    //{
    // x = e.item();
    // WScript.Echo(x.Name);
    //}
    //QAxObject *tryLooping = returnList->queryInterface(IID_IEnumerable);

    //IEnumerable* testthis;

    //QAxObject *loop1 = returnList->querySubObject("GetEnumerator()");


    /*
    QAxObject *objIWbemLocator = new QAxObject("WbemScripting.SWbemLocator");

    QAxObject *objWMIService = objIWbemLocator->querySubObject("SWbemServices");
         QString query = QString("SELECT * FROM Win32_Processor WHERE (ProcessorId IS NOT NULL)");
         QAxObject *objInterList = objWMIService->querySubObject(
                  "ExecQuery(QString&))", query);
             QAxObject *enum1 = objInterList->querySubObject("NewEnum");
     IEnumVARIANT* enumInterface = 0;
          enum1->queryInterface((const QUuid)IID_IEnumVARIANT, (void**)&enumInterface);

          enumInterface->Reset();
          QAxObject *item = 0;
          for (int i = 0; i < objInterList->dynamicCall("Count").toInt(); i++) {
            VARIANT *theItem = (VARIANT*)malloc(sizeof(VARIANT));
            if (enumInterface->Next(1,theItem,NULL) == S_FALSE) {
              qDebug("enum next failed");
              delete theItem;
              delete objIWbemLocator;

            }else{
;
            }
}
          */

    //delete reg;
    //QSettings *reg = new QSettings("HKEY_CURRENT_USER\\Software\\yinhaifan", QSettings::NativeFormat);
    //reg->setValue("registered",true);
    // delete reg;
    //  当然reg->setValue还可以写入字符串，整型之类的数据。
    //  比如reg->setValue("registered","yes");
    //  2、用QString读注册表
    //QSettings *reg = new QSettings("HKEY_CURRENT_USER\\Software\\yinhaifan", QSettings::NativeFormat);
    /*
    if (reg->value("registered",false).toBool())
    {
        QMessageBox::information(NULL,"information","registered");
    }else{
        qDebug()<<"not registerted!";
    }*/
    /*
    //  1、用QSettings写注册表
    QSettings *reg = new QSettings("HKEY_CURRENT_USER\\Software\\qCloudSecChk",QSettings::NativeFormat);
    reg->setValue("activeCode","2140sfijpiwqr0821740");
    QString info=reg->value("activeCode").toString();
    QString info2=reg->value("test").toString();
    qDebug()<<"activecode is "<<info;
    qDebug()<<"info2 is "<<info2;
    delete reg;*/
    // QSettings *reg = new QSettings("HKEY_CURRENT_USER\\Software\\yinhaifan", QSettings::NativeFormat); if (reg->value("registered",false).toBool()) { QMessageBox::information(NULL,"information","registered"); } delete reg;
    /*
    QString lpRootPathName = "C:\\";
        LPTSTR lpVolumeNameBuffer=new TCHAR[12];//磁盘卷标
        DWORD nVolumeNameSize=12;// 卷标的字符串长度
        DWORD VolumeSerialNumber;//硬盘序列号
        DWORD MaximumComponentLength;// 最大的文件长度
        LPTSTR lpFileSystemNameBuffer=new TCHAR[10];// 存储所在盘符的分区类型的长指针变量
        DWORD nFileSystemNameSize=10;// 分区类型的长指针变量所指向的字符串长度
        DWORD FileSystemFlags;// 文件系统的一此标志

        GetVolumeInformation((LPTSTR)lpRootPathName.utf16(),
          lpVolumeNameBuffer, nVolumeNameSize,
          &VolumeSerialNumber, &MaximumComponentLength,
          &FileSystemFlags,
          lpFileSystemNameBuffer, nFileSystemNameSize);
       // __cpuid();
        qDebug() << VolumeSerialNumber;*/

    this->getCPUID1();
     this->getCPUID2();
   this->getHDLogicalID();
    this->getMac();
     this->getCPUManID();
    for(int i=0;i<6;i++)
    this->getWMIHWInfo(i);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


QString MainWindow::getWMIHWInfo(int type){
    /*
//1.当前原生网卡地址：
SELECT MACAddress  FROM Win32_NetworkAdapter WHERE (MACAddress IS NOT NULL) AND (NOT (PNPDeviceID LIKE 'ROOT%'))
// 2.硬盘序列号
SELECT PNPDeviceID FROM Win32_DiskDrive WHERE(SerialNumber IS NOT NULL) AND (MediaType LIKE 'Fixed hard disk%')
//3.获取主板序列号
SELECT SerialNumber FROM Win32_BaseBoard WHERE (SerialNumber IS NOT NULL)
// 4.处理器ID
SELECT ProcessorId  FROM Win32_Processor WHERE (ProcessorId IS NOT NULL)
// 5.BIOS序列号
SELECT SerialNumber  FROM Win32_BIOS WHERE (SerialNumber IS NOT NULL)
// 6.主板型号
    SELECT Product FROM Win32_BaseBoard WHERE (Product IS NOT NULL)*/

    QString hwInfo=tr("");
    QStringList sqlCmd;
    sqlCmd.clear();
    sqlCmd<<tr("SELECT MACAddress  FROM Win32_NetworkAdapter WHERE (MACAddress IS NOT NULL) AND (NOT (PNPDeviceID LIKE 'ROOT%'))");
    //注意qt调用 wmi时，对查询语句要求很严格，所以 like之类的句子务必精确才能有结果出来
    sqlCmd<<tr("SELECT PNPDeviceID  FROM  Win32_DiskDrive WHERE( PNPDeviceID IS NOT NULL) AND (MediaType LIKE 'Fixed%')");
    sqlCmd<<tr("SELECT SerialNumber FROM Win32_BaseBoard WHERE (SerialNumber IS NOT NULL)");
    sqlCmd<<tr("SELECT ProcessorId  FROM Win32_Processor WHERE (ProcessorId IS NOT NULL)");
    sqlCmd<<tr("SELECT SerialNumber  FROM Win32_BIOS WHERE (SerialNumber IS NOT NULL)");
    sqlCmd<<tr("SELECT Product FROM Win32_BaseBoard WHERE (Product IS NOT NULL)");

    QStringList columnName;
    columnName.clear();
    columnName<<tr("MACAddress");
    columnName<<tr("PNPDeviceID");
    columnName<<tr("SerialNumber");
    columnName<<tr("ProcessorId");
    columnName<<tr("SerialNumber");
    columnName<<tr("Product");


    QAxObject *objIWbemLocator = new QAxObject("WbemScripting.SWbemLocator");
   // ui->textBrowser->setHtml(objIWbemLocator->generateDocumentation());
    QAxObject *objWMIService = objIWbemLocator->querySubObject("ConnectServer(QString&,QString&)",QString("."),QString("root\\cimv2"));
    QString query=tr("");
    if(type<sqlCmd.size())
            query=sqlCmd.at(type);

    QAxObject *objInterList = objWMIService->querySubObject("ExecQuery(QString&))", query);
    QAxObject *enum1 = objInterList->querySubObject("_NewEnum");
    //需要 include windows.h
    IEnumVARIANT* enumInterface = 0;
    enum1->queryInterface(IID_IEnumVARIANT, (void**)&enumInterface);
    enumInterface->Reset();

   // qDebug()<<"number is "<<QString::number(objInterList->dynamicCall("Count").toInt());
    for (int i = 0; i < objInterList->dynamicCall("Count").toInt(); i++) {
  //qDebug()<<__FILE__<<__LINE__;
        VARIANT *theItem = (VARIANT*)malloc(sizeof(VARIANT));
        if (enumInterface->Next(1,theItem,NULL) != S_FALSE){
     //        qDebug()<<__FILE__<<__LINE__;
            QAxObject *item = new QAxObject((IUnknown *)theItem->punkVal);
   //          qDebug()<<__FILE__<<__LINE__;
            if(item){
                if(type<columnName.size()){
                    QByteArray datagram(columnName.at(type).toAscii()); //Or
                       const char* tempConstChar = datagram.data();
                    qDebug()<<"the query is "<<query<<" and cn is "<<QString::fromAscii(tempConstChar);
                hwInfo=item->dynamicCall(tempConstChar).toString();
                ui->textBrowser_5->append(tr("\r\n query is %1:, result is %2").arg(query).arg(hwInfo));
                }

                qDebug() <<" string is "<<hwInfo;
            }else{
                qDebug() <<" item is null";
            }
        }else{
            qDebug() <<" item is false";
        }
    }
     //this->getCPUManID();
    return hwInfo;
}

QString MainWindow::getHDLogicalID(){
    /*char cVolume[256];                                         //
    char cFileSysName[256];
    DWORD dwSerialNum;                                          //硬盘序列号
    DWORD dwFileNameLength;
    DWORD dwFileSysFlag;

    ::GetVolumeInformation(L"C://", cVolume, 256, &dwSerialNum, &dwFileNameLength, &dwFileSysFlag, cFileSysName, 256);
    */
    DWORD VolumeSerialNumber;
    GetVolumeInformation(L"C:\\",NULL,0,&VolumeSerialNumber,NULL,NULL,NULL,0);
    ui->textBrowser_5->append(tr("\r\n disknum is %1").arg(QString::number(VolumeSerialNumber,16).toUpper()));
    return QString::number(VolumeSerialNumber,16).toUpper();
}

QString MainWindow::getCPUManID(){
    //用来存储信息
    DWORD deax;
    DWORD debx;
    DWORD decx;
    DWORD dedx;

    char ID[25];//存储制造商信息
    memset(ID,0,sizeof(ID));//先清空数组 ID
    __asm
    {
        mov eax,0
                cpuid
                mov deax,eax
                mov debx,ebx
                mov decx,ecx
                mov dedx,edx
    }

    memcpy(ID+0,&debx,4);//制造商信息前四个字符复制到数组
    memcpy(ID+4,&dedx,4);//中间四个
    memcpy(ID+8,&decx,4);//最后四个
    //如果返回 char * ,会出现乱码;故返回 string 值
    qDebug()<<"manufacture id is "<<QString::fromLocal8Bit(ID);
    return QString::fromLocal8Bit(ID);

}

QString MainWindow::getMac(){
    QString macAddress=tr("");
    QList<QNetworkAddressEntry> lclInfAE;
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface iface, list)
    {
        //保证获取的是本地IP地址，不是虚拟机，隧道 之类的网络地址
        //以下这句可优化
        if(!(iface.humanReadableName().contains("VMware",Qt::CaseInsensitive))&&!(iface.humanReadableName().contains("Tunnel",Qt::CaseInsensitive))&&!(iface.humanReadableName().contains("Tunneling",Qt::CaseInsensitive))&&!(iface.humanReadableName().contains("Loopback",Qt::CaseInsensitive))&&!(iface.humanReadableName().contains("Pseudo",Qt::CaseInsensitive))){
            qDebug()<<"caught iface name is "<<iface.humanReadableName();
            if(iface.hardwareAddress()!=tr("")){
                macAddress=iface.hardwareAddress().toUpper();
                qDebug()<<"hdmac is "<<macAddress;
            }

        }
 }
    ui->textBrowser_5->append(tr("\r\n MAC is %1").arg(macAddress));
    return macAddress;

}


QString MainWindow::getCPUID1(){
    char    OEMString[13];
    QString result=tr("");
    int    iEAXValue,iEBXValue,iECXValue,iEDXValue;
    _asm
    {
        mov     eax,0
                cpuid
                mov     DWORD     PTR     OEMString,ebx
                mov     DWORD     PTR     OEMString+4,edx
                mov     DWORD     PTR     OEMString+8,ecx
                mov     BYTE     PTR     OEMString+12,0
    }

    // SetDlgItemText(IDC_STATIC1,OEMString);  //CPU 供应商 名称
    qDebug()<<"manufacture id is "<<QString(OEMString);
    _asm
    {
        mov     eax,1
                cpuid
                mov     iEAXValue,eax
                mov     iEBXValue,ebx
                mov     iECXValue,ecx
                mov     iEDXValue,edx
    }

    int iCPUFamily=(0xf00 & iEAXValue)>>8;
    char Family[10]={0};
    _itoa_s(iCPUFamily,Family,10);
    // SetDlgItemText(IDC_STATIC2,Family);    //CPU系列
    qDebug()<<"cpu family is "<<QString(Family);

    _asm
    {
        mov     eax,2
                CPUID
    }

    char szCPUID[129]={NULL};
    char szTmp[33]={NULL};
    unsigned long s1 = 0,s2=0;

    _asm
    {
        mov     eax,01h
                xor     edx,edx
                cpuid
                mov     s1,edx
                mov     s2,eax
    }
    //大写16 进制，宽度占8 个位置，右对齐
    sprintf_s(szTmp, "%08X%08X", s1, s2);
    strcpy_s(szCPUID, szTmp);
    _asm
    {
        mov     eax,03h
                xor     ecx,ecx
                xor     edx,edx
                cpuid
                mov     s1,edx
                mov     s2,ecx
    }
    sprintf_s(szTmp, "%08X%08X", s1, s2);
    strcat_s(szCPUID, szTmp);
    // SetDlgItemText(IDC_STATIC3,szCPUID);   //CPUID号
    qDebug()<<"cpuid2 is "<<QString(szCPUID);

    ui->textBrowser_5->append(tr("\r\n cpuid1 is %1").arg(QString(szCPUID)));
    result=QString(szCPUID).toUpper();
    return result;


}

QString MainWindow::getCPUID2(){
    DWORD   dwId1, dwId2, dwId3, dwId4;
    char   szCompany[13];
    PCHAR   pCompany = szCompany;
    szCompany[12]=0;

    _asm
    {
        pushfd
                pushad
                //取得CPU的ID号
                mov   eax,1   //功能号
                _emit   0x0f
                _emit   0xa2
                mov   dwId1,eax
                mov   dwId2,ebx
                mov   dwId3,ecx
                mov   dwId4,edx

                //取得CPU的制造公司名称
                mov   edi,pCompany   //功能号
                mov   eax,0
                _emit   0x0f
                _emit   0xa2
                mov   eax,ebx
                stosd
                mov   eax,edx
                stosd
                mov   eax,ecx
                stosd
                popad
                popfd
    }

    DWORD dwResult = 0;
    DWORD dwTemp1 = dwId1 << 12;
    DWORD dwTemp2 = dwId2 << 8 ;
    DWORD dwTemp3 = dwId3 << 4;


    QString res=tr("splitted string is %1_%2_%3_%4").arg(QString::number(dwTemp1,16)).arg(QString::number(dwTemp2,16)).arg(QString::number(dwTemp3,16)).arg(QString::number(dwId4,16));
    dwResult = dwTemp1 + dwTemp2 + dwTemp3 + dwId4;
    QString result=QString::number(dwResult,16).toUpper();
    qDebug()<<"the result is "<<result;
    QString cpy=QString::fromLocal8Bit(szCompany);
    ui->textBrowser_5->append(res+tr("\r\n cpuid2 is :")+result.toUpper()+tr("\r\n company is :")+cpy);
    return result;
}


QString MainWindow::getMachineCode(int type){

    QString machineInfo=tr("");
    machineInfo.append(this->getCPUID1());
    machineInfo.append(tr("@"));
    machineInfo.append(this->getCPUID2());
    machineInfo.append(tr("@"));
    for(int i=0;i<6;i++){
        machineInfo.append(this->getWMIHWInfo(i));
        machineInfo.append(tr("@"));
    }

    machineInfo.append(this->getHDLogicalID());
    machineInfo.append(tr("@"));
    machineInfo.append(this->getMac());

    QCryptographicHash sha1(QCryptographicHash::Sha1);

    QByteArray datagram(machineInfo.toAscii());
    const char* tempConstChar = datagram.data();
    sha1.addData(tempConstChar);
    QString  machineCode=sha1.result().toHex();

    if(type==1){
        QClipboard *board = QApplication::clipboard();
        board->setText(machineCode);
       // QMessageBox::information (NULL,QObject::tr("机器码"),QObject::tr("机器码已经复制到粘贴板上,\r\n请发给软件供应商以获取激活码"));
    }



    return machineCode;




}


QString MainWindow::calActiveCode(QString machineCode){

    QString originalStr120=ui->parm1->toPlainText()+machineCode+ui->parm2->toPlainText()+ui->parm3->toPlainText()+QString::number(ui->parm4->value());


     //       +machineCode+tr("ihepJiangzhengwei@@@%1").arg(QString::number(validays));

    QCryptographicHash sha1(QCryptographicHash::Sha1);

    QByteArray datagram(originalStr120.toAscii());
    const char* tempConstChar = datagram.data();
    sha1.addData(tempConstChar);
    QString  activeCode=sha1.result().toHex();

    QClipboard *board = QApplication::clipboard();

    board->setText(activeCode);
    ui->activeCodeLineEdit->setText(activeCode);
    return activeCode;


}

void MainWindow::on_pushButton_clicked()
{
    this->calActiveCode(ui->parmMC->toPlainText());
}
