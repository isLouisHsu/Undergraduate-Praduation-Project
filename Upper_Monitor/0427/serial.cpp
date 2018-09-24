#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * *初始化串口参数
 */
void MainWindow::InitSerialPort()
{
    serial.setPortName(ui->comboBox_SerialPort->currentText());
    serial.setBaudRate(QSerialPort::Baud9600);
    //serial.setBaudRate(QSerialPort::Baud38400);
    serial.setDataBits(QSerialPort::Data8);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
}

/*
 * * 发送控制数据
 */
void MainWindow::SendAngleAndDistanceData(char dirAngle, char angle, ushort distance)
{
    unsigned char TxData[8]={0,0,0,0,0,0,0,0};

    if(serial.isOpen())
    {
        TxData[0] = 0x5a;
        TxData[1] = dirAngle;
        TxData[2] = angle;
        TxData[3] = IsInView;
        TxData[5] = distance & 0x00ff;
        TxData[6] = distance / 256;
        TxData[7] = 0x61;

        serial.write((const char*)TxData, 8);
    }
}

/*
 * * 读串口数据
 */
void MainWindow::ReadCom()
{
    //QByteArray temp = serial.readAll();
    //if (!temp.isEmpty())
    //{
        //temp += '\n';
        //qDebug(temp);
    //}
}

/*
 * *(原发送，现不用)发送控制数据
 */
void MainWindow::SendControlData(char dirAngle,char angle,char reserved,char dirSpeed,ushort speed)
{
    unsigned char TxData[8];

    if(serial.isOpen())
    {
        //最大转角在上位机设定为25度：陈20170503
        if (angle > 25) angle = 25;
        else if(angle < 2) angle = 0;

        TxData[0] = 0x5a;
        TxData[1] = dirAngle;
        TxData[2] = angle;
        TxData[3] = reserved;
        TxData[4] = dirSpeed;
        TxData[5] = speed & 0x00ff;
        TxData[6] = speed / 256;
        TxData[7] = 0x61;

    #ifdef SHOW_DEBUG
        qDebug("%d,%d,%d,%d,%d,%d",
            TxData[1], TxData[2], TxData[3], TxData[4], TxData[5], TxData[6]);
    #endif

        serial.write((const char*)TxData, 8);
    }
}
