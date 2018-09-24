/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QLabel *label_14;
    QLineEdit *lineEdit_Angle;
    QLabel *label_17;
    QLineEdit *lineEdit_DirAngle;
    QLabel *label_13;
    QLineEdit *lineEdit_AreaMin;
    QLineEdit *lineEdit_ThreVal;
    QLabel *label_4;
    QLineEdit *lineEdit_BlurSize;
    QLabel *label_5;
    QLabel *label_12;
    QLineEdit *lineEdit_Distance;
    QGroupBox *groupBox_4;
    QPushButton *pushButton_OpenCam;
    QPushButton *pushButton_OpenPort;
    QComboBox *comboBox_SerialPort;
    QComboBox *comboBox_CameraPath;
    QPushButton *pushButton_TakePhoto;
    QPushButton *pushButton_Calibrate;
    QGroupBox *groupBox_3;
    QLabel *label;
    QLabel *label_Frame;
    QLabel *label_7;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_Frame_resized;
    QLabel *label_Frame_gray;
    QLabel *label_Frame_binary;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(957, 443);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(370, 10, 661, 161));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(200, 100, 51, 21));
        lineEdit_Angle = new QLineEdit(groupBox);
        lineEdit_Angle->setObjectName(QStringLiteral("lineEdit_Angle"));
        lineEdit_Angle->setGeometry(QRect(280, 90, 81, 33));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 100, 68, 21));
        lineEdit_DirAngle = new QLineEdit(groupBox);
        lineEdit_DirAngle->setObjectName(QStringLiteral("lineEdit_DirAngle"));
        lineEdit_DirAngle->setEnabled(true);
        lineEdit_DirAngle->setGeometry(QRect(90, 90, 81, 33));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(390, 50, 71, 21));
        lineEdit_AreaMin = new QLineEdit(groupBox);
        lineEdit_AreaMin->setObjectName(QStringLiteral("lineEdit_AreaMin"));
        lineEdit_AreaMin->setGeometry(QRect(460, 40, 91, 33));
        lineEdit_ThreVal = new QLineEdit(groupBox);
        lineEdit_ThreVal->setObjectName(QStringLiteral("lineEdit_ThreVal"));
        lineEdit_ThreVal->setGeometry(QRect(90, 40, 81, 33));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 50, 51, 21));
        lineEdit_BlurSize = new QLineEdit(groupBox);
        lineEdit_BlurSize->setObjectName(QStringLiteral("lineEdit_BlurSize"));
        lineEdit_BlurSize->setGeometry(QRect(280, 40, 81, 33));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(200, 50, 71, 21));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(390, 100, 68, 21));
        lineEdit_Distance = new QLineEdit(groupBox);
        lineEdit_Distance->setObjectName(QStringLiteral("lineEdit_Distance"));
        lineEdit_Distance->setGeometry(QRect(460, 90, 91, 33));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 10, 341, 161));
        pushButton_OpenCam = new QPushButton(groupBox_4);
        pushButton_OpenCam->setObjectName(QStringLiteral("pushButton_OpenCam"));
        pushButton_OpenCam->setGeometry(QRect(140, 30, 111, 51));
        pushButton_OpenPort = new QPushButton(groupBox_4);
        pushButton_OpenPort->setObjectName(QStringLiteral("pushButton_OpenPort"));
        pushButton_OpenPort->setGeometry(QRect(140, 90, 111, 51));
        comboBox_SerialPort = new QComboBox(groupBox_4);
        comboBox_SerialPort->setObjectName(QStringLiteral("comboBox_SerialPort"));
        comboBox_SerialPort->setGeometry(QRect(10, 90, 121, 51));
        comboBox_CameraPath = new QComboBox(groupBox_4);
        comboBox_CameraPath->setObjectName(QStringLiteral("comboBox_CameraPath"));
        comboBox_CameraPath->setGeometry(QRect(10, 30, 121, 51));
        pushButton_TakePhoto = new QPushButton(groupBox_4);
        pushButton_TakePhoto->setObjectName(QStringLiteral("pushButton_TakePhoto"));
        pushButton_TakePhoto->setEnabled(false);
        pushButton_TakePhoto->setGeometry(QRect(260, 30, 61, 51));
        pushButton_Calibrate = new QPushButton(groupBox_4);
        pushButton_Calibrate->setObjectName(QStringLiteral("pushButton_Calibrate"));
        pushButton_Calibrate->setEnabled(false);
        pushButton_Calibrate->setGeometry(QRect(260, 90, 61, 51));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 180, 931, 211));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(480, 20, 91, 21));
        label_Frame = new QLabel(groupBox_3);
        label_Frame->setObjectName(QStringLiteral("label_Frame"));
        label_Frame->setEnabled(false);
        label_Frame->setGeometry(QRect(480, 50, 201, 151));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 20, 101, 21));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setEnabled(true);
        label_2->setGeometry(QRect(710, 20, 101, 21));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(250, 20, 121, 21));
        label_Frame_resized = new QLabel(groupBox_3);
        label_Frame_resized->setObjectName(QStringLiteral("label_Frame_resized"));
        label_Frame_resized->setGeometry(QRect(20, 50, 201, 151));
        label_Frame_gray = new QLabel(groupBox_3);
        label_Frame_gray->setObjectName(QStringLiteral("label_Frame_gray"));
        label_Frame_gray->setEnabled(false);
        label_Frame_gray->setGeometry(QRect(710, 50, 201, 151));
        label_Frame_binary = new QLabel(groupBox_3);
        label_Frame_binary->setObjectName(QStringLiteral("label_Frame_binary"));
        label_Frame_binary->setGeometry(QRect(250, 50, 201, 151));
        MainWindow->setCentralWidget(centralWidget);
        groupBox_3->raise();
        groupBox_4->raise();
        groupBox->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 957, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(pushButton_OpenCam, pushButton_TakePhoto);
        QWidget::setTabOrder(pushButton_TakePhoto, pushButton_Calibrate);
        QWidget::setTabOrder(pushButton_Calibrate, pushButton_OpenPort);
        QWidget::setTabOrder(pushButton_OpenPort, lineEdit_ThreVal);
        QWidget::setTabOrder(lineEdit_ThreVal, lineEdit_BlurSize);
        QWidget::setTabOrder(lineEdit_BlurSize, lineEdit_AreaMin);
        QWidget::setTabOrder(lineEdit_AreaMin, lineEdit_Angle);
        QWidget::setTabOrder(lineEdit_Angle, lineEdit_Distance);
        QWidget::setTabOrder(lineEdit_Distance, lineEdit_DirAngle);
        QWidget::setTabOrder(lineEdit_DirAngle, comboBox_SerialPort);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Upper Monitor", Q_NULLPTR));
        groupBox->setTitle(QString());
        label_14->setText(QApplication::translate("MainWindow", "\350\247\222\345\272\246\357\274\232", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "\350\247\222\345\272\246\346\226\271\345\220\221\357\274\232", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "\351\235\242\347\247\257\351\230\210\345\200\274\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\351\230\210\345\200\274\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\346\273\244\346\263\242\357\274\232", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "\350\267\235\347\246\273\357\274\232", Q_NULLPTR));
        groupBox_4->setTitle(QString());
        pushButton_OpenCam->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\347\233\270\346\234\272", Q_NULLPTR));
        pushButton_OpenPort->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        comboBox_SerialPort->clear();
        comboBox_SerialPort->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "COM1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "COM2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "COM3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "COM4", Q_NULLPTR)
         << QApplication::translate("MainWindow", "COM5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "COM6", Q_NULLPTR)
         << QApplication::translate("MainWindow", "COM7", Q_NULLPTR)
         << QApplication::translate("MainWindow", "COM8", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ttyUSB0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ttyUSB1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ttyUSB2", Q_NULLPTR)
        );
        comboBox_CameraPath->clear();
        comboBox_CameraPath->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2", Q_NULLPTR)
        );
        comboBox_CameraPath->setCurrentText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        pushButton_TakePhoto->setText(QApplication::translate("MainWindow", "\346\213\215\347\205\247", Q_NULLPTR));
        pushButton_Calibrate->setText(QApplication::translate("MainWindow", "\346\240\207\345\256\232", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        label->setText(QApplication::translate("MainWindow", "\345\216\237\345\233\276", Q_NULLPTR));
        label_Frame->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "\347\237\253\346\255\243\345\233\276", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\345\216\237\345\233\276\357\274\210\347\201\260\345\272\246\345\233\276\357\274\211", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\345\216\237\345\233\276\357\274\210\344\272\214\345\200\274\345\214\226\357\274\211", Q_NULLPTR));
        label_Frame_resized->setText(QString());
        label_Frame_gray->setText(QString());
        label_Frame_binary->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
