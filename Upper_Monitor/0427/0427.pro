#-------------------------------------------------
#
# Project created by QtCreator 2017-04-25T19:26:35
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 0427
TEMPLATE = app

#Windows Platform:
INCLUDEPATH += E:\opencv\build\include\opencv \
               E:\opencv\build\include\opencv2 \
               E:\opencv\build\include
LIBS += -L E:\opencv\cmakeOpenCV\lib\libopencv_*.a


#INCLUDEPATH += D:\QTOpenCV\include\opencv\
               #D:\QTOpenCV\include\opencv2\
               #D:\QTOpenCV\include
#LIBS += -L D:\QTOpenCV\lib\libopencv_*.a




#Raspiberry Platform:
#INCLUDEPATH += /usr/local/include\
#               /usr/local/include/opencv\
#               /usr/local/include/opencv2

#LIBS += -L/usr/local/lib/ \
#        -lopencv_highgui \
#        -lopencv_core \
#        -lopencv_imgproc \
#        -lopencv_calib3d \
#        -lopencv_imgcodecs \
#        -lopencv_videoio





SOURCES += main.cpp\
           mainwindow.cpp \
           calculation.cpp \
           imageProcess.cpp \
           serial.cpp \
           analyze.cpp \
           cameracalibrate.cpp \
           directionvector.cpp

HEADERS  += mainwindow.h \
            params.h \
            contour.h \
            cameracalibrate.h \
            directionvector.h

FORMS    += mainwindow.ui
