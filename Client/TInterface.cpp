#include "TInterface.h"
#include "../QtConsoleApplication1/TMessages.h"

TInterface::TInterface(uint size, QWidget* parent) : size(size)
{
    setWindowTitle("Matrix");
    setFixedSize(60 * size * Scale + 20, 50 * size * Scale + 30);
    LEditArr = new QLineEdit * **[size];
    for (uint i = 0; i < size; i++)
    {
        *(LEditArr + i) = new QLineEdit * *[size];
        for (uint j = 0; j < size; j++)
        {
            *(*(LEditArr + i) + j) = new QLineEdit * [2];
            **(*(LEditArr + i) + j) = new QLineEdit("", this);
            *(*(*(LEditArr + i) + j) + 1) = new QLineEdit("", this);
            LEditArr[i][j][0]->setGeometry((30 * j + 10) * Scale, (40 * i + 10) * Scale, 15 * Scale, 15 * Scale);
            LEditArr[i][j][1]->setGeometry((30 * j + 10) * Scale, (40 * i + 25) * Scale, 15 * Scale, 15 * Scale);
        }
    }
    CalculateBut = new QPushButton("Calculate", this);
    CalculateBut->setGeometry((40 * size) * Scale, 10 * Scale, 50 * Scale, 30 * Scale);

    TransposeBut = new QPushButton("Transpose", this);
    TransposeBut->setGeometry((40 * size) * Scale, 40 * Scale, 50 * Scale, 30 * Scale);

    DeterminantLabel = new QLabel("Determinant:", this);
    DeterminantLabel->setGeometry(15 * Scale, (40 * size + 20) * Scale, 90 * Scale, 20 * Scale);

    RankLabel = new QLabel("Rank:", this);
    RankLabel->setGeometry(15 * Scale, (40 * size) * Scale, 30 * Scale, 20 * Scale);

    connect(CalculateBut, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(TransposeBut, SIGNAL(pressed()), this, SLOT(formRequest()));
}

TInterface::~TInterface()
{

    for (uint i = 0; i < size; i++)
    {
        for (uint j = 0; j < size; j++)
        {
            delete** (*(LEditArr + i) + j);
            delete* (*(*(LEditArr + i) + j) + 1);
            delete[] * (*(LEditArr + i) + j);
        }
        delete[] * (LEditArr + i);
    }
    delete[] LEditArr;
    delete CalculateBut;
    delete TransposeBut;
    delete DeterminantLabel;
    delete RankLabel;
}

void TInterface::reception(QString str)
{
    int message;
    str >> message;
    switch (message)
    {
    case DETERMINANT_ANSWER:
    {
        double det;
        int rank;
        str >> det;
        str >> rank;

        DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string(det)));
        RankLabel->setText("Rank:" + QString::fromStdString(std::to_string(rank)));
        break;
    }
    case TRANSPOSE_ANSWER:
    {
        int Size;
        str >> Size;
        if(Size == size)
        {
            for (uint i = 0; i < Size; i++)
            {
                for (uint j = 0; j < Size; j++)
                {
                    int tmpUP;
                    int tmpDOWN;
                    str >> tmpUP;
                    str >> tmpDOWN;
                    LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string(tmpUP)));
                    LEditArr[i][j][1]->setText(QString::fromStdString(std::to_string(tmpDOWN)));
                }
            }
        }
        break;
    }
    case ERROR_MESSAGE:
    {
        qDebug() << "server error";
        break;
    }
    default:
    {
        qDebug() << "unknown answer";
        break;
    }
    }
}

void TInterface::formRequest()
{
    QString msg;
    QPushButton* from = (QPushButton*)sender();
    if (from == CalculateBut)
        msg << QString().setNum(DETERMINANT_REQUEST);
    else if (from == TransposeBut)
        msg << QString().setNum(TRANSPOSE_REQUEST);
    msg << QString().setNum(size);
    for (uint i = 0; i < size; i++)
    {
        for (uint j = 0; j < size; j++)
        {
            msg << LEditArr[i][j][0]->text();
            msg << LEditArr[i][j][1]->text();
        }
    }
    emit request(msg);
}



AdditionalInterface::AdditionalInterface(TInterface* fc, QWidget* parent) : fc(fc)
{
    setWindowTitle("Size");
    setFixedSize(180, 100);

    SizeLabel = new QLabel("Enter size:", this);
    SizeLabel->setGeometry(45, 10, 55, 20);

    SizeValue = new QLineEdit("", this);
    SizeValue->setGeometry(105, 10, 30, 20);

    ConfirmBut = new QPushButton("Continue", this);
    ConfirmBut->setGeometry(5, 45, 170, 45);

    connect(ConfirmBut, SIGNAL(pressed()), this, SLOT(Confirm()));
}

void AdditionalInterface::Confirm()
{
    if (SizeValue->text().toUInt() > 15)
    {
        QMessageBox warning = QMessageBox(this);
        warning.setText("Value is too much or negative");

        warning.exec();
        return;
    }
    size = SizeValue->text().toUInt();


    fc = new TInterface(size);
    emit ChangedSize(fc);
    fc->show();
    this->hide();
}