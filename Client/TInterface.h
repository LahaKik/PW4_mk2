#pragma once
#include "../QtConsoleApplication1/TMessages.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qtwidgets-config.h>
#include <qwidget.h>

class TInterface :
    public QWidget
{
    Q_OBJECT
    QLineEdit**** LEditArr;
    QPushButton* CalculateBut, * TransposeBut;
    QLabel* DeterminantLabel, * RankLabel;
    QRadioButton* RationalNum, * RealNum, * ComplexNum;
    uint height;
    uint width;
    const float Scale = 1.5;
    TypeNum typeNum = RATIONAL;

public:
    TInterface(uint, uint, QWidget* parent = nullptr);

    ~TInterface();

public slots:
    void reception(QString);

private slots:
    void formRequest();
    void RedrowFilds();

signals:
    void request(QString);
};



class AdditionalInterface
    : public QWidget
{
    Q_OBJECT
    QPushButton* ConfirmBut;
    QLabel* SizeLabel;
    QLineEdit* HeightValue, * WidthValue;
    uint height;
    uint width;
    TInterface* fc;
public:
    AdditionalInterface(TInterface*, QWidget* parent = nullptr);

    ~AdditionalInterface()
    {
        delete ConfirmBut;
        delete SizeLabel;
        delete HeightValue;
        delete WidthValue;
        delete fc;
    }
public slots:
    void Confirm();

signals:
    void ChangedSize(TInterface*);
};