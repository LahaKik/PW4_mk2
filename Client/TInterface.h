#pragma once
#include <qtwidgets-config.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qmessagebox.h>

//#include <string>

class TInterface :
    public QWidget
{
    Q_OBJECT
        QLineEdit**** LEditArr;
    QPushButton* CalculateBut, * TransposeBut;
    QLabel* DeterminantLabel, * RankLabel;
    uint size;
    const float Scale = 1.5;

    //number* GetValues();
public:
    TInterface(uint, QWidget* parent = nullptr);

    ~TInterface();

public slots:
    void reception(QString);

private slots:
    void formRequest();

signals:
    void request(QString);
};



class AdditionalInterface
    : public QWidget
{
    Q_OBJECT
        QPushButton* ConfirmBut;
    QLabel* SizeLabel;
    QLineEdit* SizeValue;
    uint size;
    TInterface* fc;
public:
    AdditionalInterface(TInterface*, QWidget* parent = nullptr);

    ~AdditionalInterface()
    {
        delete ConfirmBut;
        delete SizeLabel;
        delete SizeValue;
        delete fc;
    }
public slots:
    void Confirm();

signals:
    void ChangedSize(TInterface*);
};