#include "TInterface.h"
#include "../QtConsoleApplication1/TMessages.h"

TInterface::TInterface(uint height, uint width, QWidget* parent) : height(height), width(width)
{
    setWindowTitle("Matrix");
    setFixedSize(60 * width * Scale + 20, 50 * height * Scale + 30);
    if(width > height)
    {
        LEditArr = new QLineEdit * **[width];
        for (uint i = 0; i < width; i++)
        {
            *(LEditArr + i) = new QLineEdit * *[width];
            for (uint j = 0; j < width; j++)
            {
                *(*(LEditArr + i) + j) = new QLineEdit * [2];
                **(*(LEditArr + i) + j) = new QLineEdit("", this);
                *(*(*(LEditArr + i) + j) + 1) = new QLineEdit("", this);
                LEditArr[i][j][0]->setGeometry((30 * j + 10) * Scale, (40 * i + 10) * Scale, 15 * Scale, 15 * Scale);
                LEditArr[i][j][1]->setGeometry((30 * j + 10) * Scale, (40 * i + 25) * Scale, 15 * Scale, 15 * Scale); 
                if(i >= height)
                {
                    LEditArr[i][j][0]->hide();
                    LEditArr[i][j][1]->hide();
                }
            }
        }
    }
    else
    {
        LEditArr = new QLineEdit * **[height];
        for (uint i = 0; i < height; i++)
        {
            *(LEditArr + i) = new QLineEdit * *[height];
            for (uint j = 0; j < height; j++)
            {
                *(*(LEditArr + i) + j) = new QLineEdit * [2];
                **(*(LEditArr + i) + j) = new QLineEdit("", this);
                *(*(*(LEditArr + i) + j) + 1) = new QLineEdit("", this);
                LEditArr[i][j][0]->setGeometry((30 * j + 10) * Scale, (40 * i + 10) * Scale, 15 * Scale, 15 * Scale);
                LEditArr[i][j][1]->setGeometry((30 * j + 10) * Scale, (40 * i + 25) * Scale, 15 * Scale, 15 * Scale);
                if (j >= width)
                {
                    LEditArr[i][j][0]->hide();
                    LEditArr[i][j][1]->hide();
                }
            }
        }
    }
    CalculateBut = new QPushButton("Calculate", this);
    CalculateBut->setGeometry((40 * width) * Scale, 10 * Scale, 50 * Scale, 30 * Scale);

    TransposeBut = new QPushButton("Transpose", this);
    TransposeBut->setGeometry((40 * width) * Scale, 40 * Scale, 50 * Scale, 30 * Scale);

    DeterminantLabel = new QLabel("Determinant:", this);
    DeterminantLabel->setGeometry(15 * Scale, (40 * height + 20) * Scale, 90 * Scale, 20 * Scale);

    RankLabel = new QLabel("Rank:", this);
    RankLabel->setGeometry(15 * Scale, (40 * height) * Scale, 30 * Scale, 20 * Scale);

    connect(CalculateBut, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(TransposeBut, SIGNAL(pressed()), this, SLOT(formRequest()));
}

TInterface::~TInterface()
{
    if(width > height)
    {
        for (uint i = 0; i < width; i++)
        {
            for (uint j = 0; j < width; j++)
            {
                delete** (*(LEditArr + i) + j);
                delete* (*(*(LEditArr + i) + j) + 1);
                delete[] * (*(LEditArr + i) + j);
            }
            delete[] * (LEditArr + i);
        }
    }
    else
    {
        for (uint i = 0; i < height; i++)
        {
            for (uint j = 0; j < height; j++)
            {
                delete** (*(LEditArr + i) + j);
                delete* (*(*(LEditArr + i) + j) + 1);
                delete[] * (*(LEditArr + i) + j);
            }
            delete[] * (LEditArr + i);
        }
    }
    delete[] LEditArr;
    delete CalculateBut;
    delete TransposeBut;
    delete DeterminantLabel;
    delete RankLabel;
}

void TInterface::reception(QString str)
{
    qDebug() << str;
    int message;
    str >> message;
    switch (message)
    {
    case DETERMINANT_ANSWER:
    {
        if(height == width)
        {
            double det;
            int rank;
            str >> det;
            str >> rank;

            DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string(det)));
            RankLabel->setText("Rank:" + QString::fromStdString(std::to_string(rank)));
        }
        else
        {
            int rank;
            str >> rank;
            RankLabel->setText("Rank:" + QString::fromStdString(std::to_string(rank)));
        }
        break;
    }
    case TRANSPOSE_ANSWER:
    {
        int Height;
        int Width;
        str >> Height;
        str >> Width;
        for (uint i = 0; i < ((width > height) ? width : height); i++)
        {
            for (uint j = 0; j < ((width > height) ? width : height); j++)
            {
                LEditArr[i][j][0]->show();
                LEditArr[i][j][1]->show();
                if (i < Height && j < Width)
                {
                    int tmpUP;
                    int tmpDOWN;
                    str >> tmpUP;
                    str >> tmpDOWN;
                    LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string(tmpUP)));
                    LEditArr[i][j][1]->setText(QString::fromStdString(std::to_string(tmpDOWN)));
                }
                else
                {
                    LEditArr[i][j][0]->hide();
                    LEditArr[i][j][1]->hide();
                }
            }
        }
        height = Height;
        width = Width;
        setFixedSize(60 * width * Scale + 20, 50 * height * Scale + 30);
        CalculateBut->setGeometry((40 * width) * Scale, 10 * Scale, 50 * Scale, 30 * Scale);
        TransposeBut->setGeometry((40 * width) * Scale, 40 * Scale, 50 * Scale, 30 * Scale);
        DeterminantLabel->setGeometry(15 * Scale, (40 * height + 20) * Scale, 90 * Scale, 20 * Scale);
        RankLabel->setGeometry(15 * Scale, (40 * height) * Scale, 30 * Scale, 20 * Scale);

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
    msg << QString().setNum(height);
    msg << QString().setNum(width);
    for (uint i = 0; i < height; i++)
    {
        for (uint j = 0; j < width; j++)
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
    setFixedSize(200, 100);

    SizeLabel = new QLabel("Enter size:", this);
    SizeLabel->setGeometry(35, 10, 55, 20);

    HeightValue = new QLineEdit("", this);
    HeightValue->setGeometry(90, 10, 30, 20);

    WidthValue = new QLineEdit("", this);
    WidthValue->setGeometry(125, 10, 30, 20);

    ConfirmBut = new QPushButton("Continue", this);
    ConfirmBut->setGeometry(5, 45, 190, 45);

    connect(ConfirmBut, SIGNAL(pressed()), this, SLOT(Confirm()));
    connect(WidthValue, SIGNAL(editingFinished()), this, SLOT(Confirm()));
}

void AdditionalInterface::Confirm()
{
    if (HeightValue->text().toUInt() > 15 || WidthValue->text().toUInt() > 15)
    {
        QMessageBox warning = QMessageBox(this);
        warning.setText("Value is too much or negative");

        warning.exec();
        return;
    }
    height = HeightValue->text().toUInt();
    width = WidthValue->text().toUInt();


    fc = new TInterface(height, width);
    emit ChangedSize(fc);
    fc->show();
    this->hide();
}