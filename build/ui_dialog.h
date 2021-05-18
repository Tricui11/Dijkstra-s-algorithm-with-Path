/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGroupBox *mapGroupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *mapGridLayout;
    QGroupBox *inputGroupBox;
    QCheckBox *checkBox_IsRandomFill;
    QPushButton *pushButton_GenMap;
    QLineEdit *lineEdit_N;
    QLineEdit *lineEdit_M;
    QLabel *labelM;
    QLabel *labelN;
    QLabel *labelMin;
    QLineEdit *lineEdit_Min;
    QLabel *labelMax;
    QLineEdit *lineEdit_Max;
    QLineEdit *lineEdit_XFreq;
    QLabel *labelXFreq;
    QGroupBox *outputGroupBox;
    QLabel *label_Fuel;
    QLabel *label_Steps;
    QLineEdit *lineEdit_Steps;
    QLineEdit *lineEdit_Fuel;
    QPushButton *pushButton_Solve;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(800, 600);
        mapGroupBox = new QGroupBox(Dialog);
        mapGroupBox->setObjectName(QString::fromUtf8("mapGroupBox"));
        mapGroupBox->setGeometry(QRect(30, 20, 601, 551));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        mapGroupBox->setFont(font);
        mapGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"\n"
"border: 3px solid blue;\n"
"border-radius: 6px;\n"
"padding: 0 8px;\n"
"background : lightyellow;\n"
"\n"
"}"));
        gridLayoutWidget = new QWidget(mapGroupBox);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 30, 561, 501));
        mapGridLayout = new QGridLayout(gridLayoutWidget);
        mapGridLayout->setObjectName(QString::fromUtf8("mapGridLayout"));
        mapGridLayout->setContentsMargins(0, 0, 0, 0);
        inputGroupBox = new QGroupBox(Dialog);
        inputGroupBox->setObjectName(QString::fromUtf8("inputGroupBox"));
        inputGroupBox->setGeometry(QRect(650, 60, 131, 221));
        QFont font1;
        font1.setPointSize(12);
        font1.setItalic(true);
        inputGroupBox->setFont(font1);
        inputGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"\n"
"border: 1px solid blue;\n"
"border-radius: 6px;\n"
"padding: 0 8px;\n"
"background : lightgreen;\n"
"\n"
"}"));
        checkBox_IsRandomFill = new QCheckBox(inputGroupBox);
        checkBox_IsRandomFill->setObjectName(QString::fromUtf8("checkBox_IsRandomFill"));
        checkBox_IsRandomFill->setGeometry(QRect(30, 150, 81, 20));
        QFont font2;
        font2.setPointSize(9);
        font2.setItalic(false);
        checkBox_IsRandomFill->setFont(font2);
        pushButton_GenMap = new QPushButton(inputGroupBox);
        pushButton_GenMap->setObjectName(QString::fromUtf8("pushButton_GenMap"));
        pushButton_GenMap->setGeometry(QRect(10, 180, 111, 24));
        pushButton_GenMap->setFont(font2);
        pushButton_GenMap->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"border: 2px solid gray;\n"
"border-radius: 6px;\n"
"padding: 0 8px;\n"
"background : blue;\n"
"color: white;\n"
"\n"
"}"));
        lineEdit_N = new QLineEdit(inputGroupBox);
        lineEdit_N->setObjectName(QString::fromUtf8("lineEdit_N"));
        lineEdit_N->setGeometry(QRect(70, 30, 28, 18));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setItalic(false);
        lineEdit_N->setFont(font3);
        lineEdit_N->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"\n"
"color : blue;\n"
"\n"
"}"));
        lineEdit_M = new QLineEdit(inputGroupBox);
        lineEdit_M->setObjectName(QString::fromUtf8("lineEdit_M"));
        lineEdit_M->setGeometry(QRect(70, 50, 28, 18));
        lineEdit_M->setFont(font3);
        lineEdit_M->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"\n"
"color : blue;\n"
"\n"
"}"));
        labelM = new QLabel(inputGroupBox);
        labelM->setObjectName(QString::fromUtf8("labelM"));
        labelM->setGeometry(QRect(40, 50, 16, 18));
        labelM->setFont(font2);
        labelN = new QLabel(inputGroupBox);
        labelN->setObjectName(QString::fromUtf8("labelN"));
        labelN->setGeometry(QRect(40, 31, 16, 18));
        labelN->setFont(font2);
        labelMin = new QLabel(inputGroupBox);
        labelMin->setObjectName(QString::fromUtf8("labelMin"));
        labelMin->setGeometry(QRect(30, 70, 31, 20));
        labelMin->setFont(font2);
        lineEdit_Min = new QLineEdit(inputGroupBox);
        lineEdit_Min->setObjectName(QString::fromUtf8("lineEdit_Min"));
        lineEdit_Min->setGeometry(QRect(70, 70, 41, 18));
        lineEdit_Min->setFont(font3);
        lineEdit_Min->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"\n"
"color : blue;\n"
"\n"
"}"));
        labelMax = new QLabel(inputGroupBox);
        labelMax->setObjectName(QString::fromUtf8("labelMax"));
        labelMax->setGeometry(QRect(30, 90, 31, 20));
        labelMax->setFont(font2);
        lineEdit_Max = new QLineEdit(inputGroupBox);
        lineEdit_Max->setObjectName(QString::fromUtf8("lineEdit_Max"));
        lineEdit_Max->setGeometry(QRect(70, 90, 41, 18));
        lineEdit_Max->setFont(font3);
        lineEdit_Max->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"\n"
"color : blue;\n"
"\n"
"}"));
        lineEdit_XFreq = new QLineEdit(inputGroupBox);
        lineEdit_XFreq->setObjectName(QString::fromUtf8("lineEdit_XFreq"));
        lineEdit_XFreq->setGeometry(QRect(70, 130, 41, 18));
        lineEdit_XFreq->setFont(font3);
        lineEdit_XFreq->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"\n"
"color : blue;\n"
"\n"
"}"));
        labelXFreq = new QLabel(inputGroupBox);
        labelXFreq->setObjectName(QString::fromUtf8("labelXFreq"));
        labelXFreq->setGeometry(QRect(10, 110, 71, 41));
        labelXFreq->setFont(font2);
        labelXFreq->setWordWrap(true);
        outputGroupBox = new QGroupBox(Dialog);
        outputGroupBox->setObjectName(QString::fromUtf8("outputGroupBox"));
        outputGroupBox->setGeometry(QRect(650, 360, 131, 161));
        outputGroupBox->setFont(font1);
        outputGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"\n"
"border: 1px solid red;\n"
"border-radius: 6px;\n"
"padding: 0 8px;\n"
"background : yellow;\n"
"\n"
"}"));
        label_Fuel = new QLabel(outputGroupBox);
        label_Fuel->setObjectName(QString::fromUtf8("label_Fuel"));
        label_Fuel->setGeometry(QRect(20, 70, 41, 18));
        label_Fuel->setFont(font2);
        label_Steps = new QLabel(outputGroupBox);
        label_Steps->setObjectName(QString::fromUtf8("label_Steps"));
        label_Steps->setGeometry(QRect(20, 40, 41, 18));
        label_Steps->setFont(font2);
        lineEdit_Steps = new QLineEdit(outputGroupBox);
        lineEdit_Steps->setObjectName(QString::fromUtf8("lineEdit_Steps"));
        lineEdit_Steps->setGeometry(QRect(70, 40, 41, 22));
        lineEdit_Steps->setFont(font3);
        lineEdit_Steps->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"\n"
"color : red;\n"
"\n"
"}"));
        lineEdit_Steps->setReadOnly(true);
        lineEdit_Fuel = new QLineEdit(outputGroupBox);
        lineEdit_Fuel->setObjectName(QString::fromUtf8("lineEdit_Fuel"));
        lineEdit_Fuel->setGeometry(QRect(70, 70, 41, 22));
        lineEdit_Fuel->setFont(font3);
        lineEdit_Fuel->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"\n"
"color : red;\n"
"\n"
"}"));
        lineEdit_Fuel->setReadOnly(true);
        pushButton_Solve = new QPushButton(outputGroupBox);
        pushButton_Solve->setObjectName(QString::fromUtf8("pushButton_Solve"));
        pushButton_Solve->setGeometry(QRect(30, 110, 71, 24));
        pushButton_Solve->setFont(font2);
        pushButton_Solve->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"border: 2px solid gray;\n"
"border-radius: 6px;\n"
"padding: 0 8px;\n"
"background : red;\n"
"color: white;\n"
"\n"
"}"));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        mapGroupBox->setTitle(QCoreApplication::translate("Dialog", "Rover's map", nullptr));
        inputGroupBox->setTitle(QCoreApplication::translate("Dialog", "Input", nullptr));
        checkBox_IsRandomFill->setText(QCoreApplication::translate("Dialog", "Fill random", nullptr));
        pushButton_GenMap->setText(QCoreApplication::translate("Dialog", "Generate map", nullptr));
        labelM->setText(QCoreApplication::translate("Dialog", "M:", nullptr));
        labelN->setText(QCoreApplication::translate("Dialog", "N:", nullptr));
        labelMin->setText(QCoreApplication::translate("Dialog", "Min:", nullptr));
        labelMax->setText(QCoreApplication::translate("Dialog", "Max:", nullptr));
        labelXFreq->setText(QCoreApplication::translate("Dialog", "X frequency 1 to :", nullptr));
        outputGroupBox->setTitle(QCoreApplication::translate("Dialog", "Output", nullptr));
        label_Fuel->setText(QCoreApplication::translate("Dialog", " Fuel:", nullptr));
        label_Steps->setText(QCoreApplication::translate("Dialog", "Steps:", nullptr));
        pushButton_Solve->setText(QCoreApplication::translate("Dialog", "Solve", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
