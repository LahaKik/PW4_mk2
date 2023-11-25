#include "TInterface.h"


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
    DeterminantLabel->setGeometry(10 * Scale, (40 * height + 20) * Scale, 90 * Scale, 20 * Scale);

    RankLabel = new QLabel("Rank:", this);
    RankLabel->setGeometry(10 * Scale, (40 * height) * Scale, 30 * Scale, 20 * Scale);

    RationalNum = new QRadioButton("Rational", this);
    RationalNum->setGeometry((40 * width) * Scale, 70 * Scale, 50 * Scale, 15 * Scale);

    RealNum = new QRadioButton("Real", this);
    RealNum->setGeometry((40 * width) * Scale, 85 * Scale, 50 * Scale, 15 * Scale);

    ComplexNum = new QRadioButton("Complex", this);
    ComplexNum->setGeometry((40 * width) * Scale, 100 * Scale, 50 * Scale, 15 * Scale);

    RationalNum->setChecked(true);

    connect(CalculateBut, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(TransposeBut, SIGNAL(pressed()), this, SLOT(formRequest()));

    connect(RationalNum, SIGNAL(clicked()), this, SLOT(RedrowFilds()));
    connect(RealNum, SIGNAL(clicked()), this, SLOT(RedrowFilds()));
    connect(ComplexNum, SIGNAL(clicked()), this, SLOT(RedrowFilds()));
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
    delete RationalNum;
    delete RealNum;
    delete ComplexNum;
}

void TInterface::RedrowFilds()
{
    if ((QRadioButton*)sender() == RationalNum)
    {
        typeNum = RATIONAL;
        for (uint i = 0; i < ((width > height) ? width : height); i++)
        {
            for (uint j = 0; j < ((width > height) ? width : height); j++)
            {
                LEditArr[i][j][0]->show();
                LEditArr[i][j][1]->show();
                LEditArr[i][j][0]->setGeometry((30 * j + 10) * Scale, (40 * i + 10) * Scale, 15 * Scale, 15 * Scale);
                LEditArr[i][j][1]->setGeometry((30 * j + 10) * Scale, (40 * i + 25) * Scale, 15 * Scale, 15 * Scale);
                if (i >= height || j >= width)
                {
                    LEditArr[i][j][0]->hide();
                    LEditArr[i][j][1]->hide();
                }
            }
        }
    }
    else if ((QRadioButton*)sender() == RealNum)
    {
        typeNum = REAL;
        for (uint i = 0; i < ((width > height) ? width : height); i++)
        {
            for (uint j = 0; j < ((width > height) ? width : height); j++)
            {
                LEditArr[i][j][0]->show();
                LEditArr[i][j][1]->hide();
                LEditArr[i][j][0]->setGeometry((30 * j + 10) * Scale, (40 * i + 10) * Scale, 25 * Scale, 15 * Scale);
                LEditArr[i][j][1]->setGeometry((30 * j + 10) * Scale, (40 * i + 25) * Scale, 15 * Scale, 15 * Scale);
                if (i >= height || j >= width)
                {
                    LEditArr[i][j][0]->hide();
                }
            }
        }
    }
    else if ((QRadioButton*)sender() == ComplexNum)
    {
        typeNum = COMPLEX;
        for (uint i = 0; i < ((width > height) ? width : height); i++)
        {
            for (uint j = 0; j < ((width > height) ? width : height); j++)
            {
                LEditArr[i][j][0]->show();
                LEditArr[i][j][1]->hide();
                LEditArr[i][j][0]->setGeometry((30 * j + 10) * Scale, (40 * i + 10) * Scale, 29 * Scale, 15 * Scale);
                LEditArr[i][j][1]->setGeometry((30 * j + 10) * Scale, (40 * i + 10) * Scale, 29 * Scale, 15 * Scale);
                if (i >= height || j >= width)
                {
                    LEditArr[i][j][0]->hide();
                }
            }
        }
    }
}

void TInterface::reception(QString str)
{
    qDebug() << str;
    int message;
    int AnsTypeNum;
    str >> message;
    str >> AnsTypeNum;
    if (AnsTypeNum != typeNum)
        return;
    switch (message)
    {
    case DETERMINANT_ANSWER:
    {
        if(height == width)
        {
            switch (typeNum)
            {
            case RATIONAL:
            {
                double det;
                int rank;
                str >> det;
                str >> rank;

                DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string(det)));
                RankLabel->setText("Rank:" + QString::fromStdString(std::to_string(rank)));
                break;
            }
            case REAL:
            {
                double det;
                int rank;
                str >> det;
                str >> rank;
                if(det == (int)det)
                    DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string((int)det)));
                else
                    DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string(det)));
                RankLabel->setText("Rank:" + QString::fromStdString(std::to_string(rank)));
                break;
            }
            case COMPLEX:
            {
                double DetRe;
                double DetIm;
                int Rank;
                str >> DetRe;
                str >> DetIm;
                str >> Rank;
                if (DetRe == (int)DetRe && DetIm == (int)DetIm)
                {
                    if (DetIm > 0)
                        DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string((int)DetRe) + "+" + std::to_string((int)DetIm) + "i"));
                    else if (DetIm == 0)
                        DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string((int)DetRe)));
                    else
                        DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string((int)DetRe) + std::to_string((int)DetIm) + "i"));
                }
                else if (DetRe == (int)DetRe && DetIm != (int)DetIm)
                {
                    if (DetIm > 0)
                        DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string((int)DetRe) + "+" + std::to_string(DetIm) + "i"));
                    else if (DetIm == 0)
                        DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string((int)DetRe)));
                    else
                        DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string((int)DetRe) + std::to_string(DetIm) + "i"));
                }
                else if (DetRe != (int)DetRe && DetIm == (int)DetIm)
                {
                    if (DetIm > 0)
                        DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string(DetRe) + "+" + std::to_string((int)DetIm) + "i"));
                    else if (DetIm == 0)
                        DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string(DetRe)));
                    else
                        DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string(DetRe) + std::to_string((int)DetIm) + "i"));
                }
                else
                {
                    if (DetIm > 0)
                        DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string(DetRe) + "+" + std::to_string(DetIm) + "i"));
                    else if (DetIm == 0)
                        DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string(DetRe)));
                    else
                        DeterminantLabel->setText("Determinant:" + QString::fromStdString(std::to_string(DetRe) + std::to_string(DetIm) + "i"));
                }
                RankLabel->setText("Rank:" + QString::fromStdString(std::to_string(Rank)));
                break;
            }
            default:
                break;
            }

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
        switch (AnsTypeNum)
        {
        case RATIONAL:
        {
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
            break;
        }
        case REAL:
        {
            for (uint i = 0; i < ((width > height) ? width : height); i++)
            {
                for (uint j = 0; j < ((width > height) ? width : height); j++)
                {
                    LEditArr[i][j][0]->show();
                    LEditArr[i][j][1]->hide();
                    if (i < Height && j < Width)
                    {
                        double tmpNum;
                        str >> tmpNum;
                        if(tmpNum == (int)tmpNum)
                            LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string((int)tmpNum)));
                        else
                            LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string(tmpNum)));
                    }
                    else
                    {
                        LEditArr[i][j][0]->hide();
                    }
                }
            }
            break;
        }
        case COMPLEX:
        {
            for (uint i = 0; i < ((width > height) ? width : height); i++)
            {
                for (uint j = 0; j < ((width > height) ? width : height); j++)
                {
                    LEditArr[i][j][0]->show();
                    LEditArr[i][j][1]->hide();
                    if (i < Height && j < Width)
                    {
                        double tmpRe;
                        double tmpIm;
                        str >> tmpRe;
                        str >> tmpIm;
                        if(tmpRe == (int)tmpRe && tmpIm == (int)tmpIm)
                        {
                            if (tmpIm > 0)
                                LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string((int)tmpRe) + "+" + std::to_string((int)tmpIm) + "i"));
                            else if (tmpIm == 0)
                                LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string((int)tmpRe)));
                            else
                                LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string((int)tmpRe) + std::to_string((int)tmpIm) + "i"));
                        }
                        else if (tmpRe == (int)tmpRe && tmpIm != (int)tmpIm)
                        {
                            if (tmpIm > 0)
                                LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string((int)tmpRe) + "+" + std::to_string(tmpIm) + "i"));
                            else if (tmpIm == 0)
                                LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string((int)tmpRe)));
                            else
                                LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string((int)tmpRe) + std::to_string(tmpIm) + "i"));
                        }
                        else if (tmpRe != (int)tmpRe && tmpIm == (int)tmpIm)
                        {
                            if (tmpIm > 0)
                                LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string(tmpRe) + "+" + std::to_string((int)tmpIm) + "i"));
                            else if (tmpIm == 0)
                                LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string(tmpRe)));
                            else
                                LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string(tmpRe) + std::to_string((int)tmpIm) + "i"));
                        }
                        else
                        {
                            if (tmpIm > 0)
                                LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string(tmpRe) + "+" + std::to_string(tmpIm) + "i"));
                            else if (tmpIm == 0)
                                LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string(tmpRe)));
                            else
                                LEditArr[i][j][0]->setText(QString::fromStdString(std::to_string(tmpRe) + std::to_string(tmpIm) + "i"));
                        }
                    }
                    else
                    {
                        LEditArr[i][j][0]->hide();
                    }
                }
            }
            break;
        }
        default:
            break;
        }
        height = Height;
        width = Width;
        setFixedSize(60 * width * Scale + 20, 50 * height * Scale + 30);
        CalculateBut->setGeometry((40 * width) * Scale, 10 * Scale, 50 * Scale, 30 * Scale);
        TransposeBut->setGeometry((40 * width) * Scale, 40 * Scale, 50 * Scale, 30 * Scale);
        DeterminantLabel->setGeometry(15 * Scale, (40 * height + 20) * Scale, 90 * Scale, 20 * Scale);
        RankLabel->setGeometry(15 * Scale, (40 * height) * Scale, 30 * Scale, 20 * Scale);
        RationalNum->setGeometry((40 * width) * Scale, 70 * Scale, 50 * Scale, 10 * Scale);
        RealNum->setGeometry((40 * width) * Scale, 85 * Scale, 50 * Scale, 10 * Scale);
        ComplexNum->setGeometry((40 * width) * Scale, 100 * Scale, 50 * Scale, 10 * Scale);
        break;
    }
    case ERROR_MESSAGE:
    {
        qDebug() << "server error";
        QMessageBox warning = QMessageBox(this);
        warning.setText("Server returns error, check that the input is correct");
        warning.exec();
        return;
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

    msg << QString().setNum(typeNum);
    msg << QString().setNum(height);
    msg << QString().setNum(width);
    switch (typeNum)
    {
    case RATIONAL:
    {
        for (uint i = 0; i < height; i++)
        {
            for (uint j = 0; j < width; j++)
            {
                msg << LEditArr[i][j][0]->text();
                msg << LEditArr[i][j][1]->text();
            }
        }
        break;
    }
    case REAL:
    {
        for (uint i = 0; i < height; i++)
        {
            for (uint j = 0; j < width; j++)
            {
                msg << LEditArr[i][j][0]->text();
            }
        }
        break;
    }
    case COMPLEX:
    {
        for (uint i = 0; i < height; i++)
        {
            for (uint j = 0; j < width; j++)
            {
                int indPlus = LEditArr[i][j][0]->text().indexOf("+");
                int indMinus = LEditArr[i][j][0]->text().indexOf("-");
                int indI = LEditArr[i][j][0]->text().indexOf("i");
                if(indPlus > 0 && indMinus <= 0 )
                {
                    msg << LEditArr[i][j][0]->text().left(indPlus) << LEditArr[i][j][0]->text().mid(indPlus + 1, indI - indPlus - 1);
                }
                else if (indPlus == -1 && indMinus == 0)
                {
                    indMinus = LEditArr[i][j][0]->text().indexOf("-", indMinus + 1);
                    if (indMinus != -1)
                        msg << LEditArr[i][j][0]->text().left(indMinus) << LEditArr[i][j][0]->text().mid(indMinus, indI - indMinus);
                    else if (indI != -1)
                        msg << QString().setNum(0) << LEditArr[i][j][0]->text().left(indI);
                    else
                        msg << LEditArr[i][j][0]->text() << QString().setNum(0);
                }
                else if (indPlus == -1 && indMinus > 0)
                {
                    msg << LEditArr[i][j][0]->text().left(indMinus) << LEditArr[i][j][0]->text().mid(indMinus, indI - indMinus);
                }
                else if (indPlus == -1 && indMinus == -1 && indI != -1)
                {
                    msg << QString().setNum(0) << LEditArr[i][j][0]->text().left(indI);
                }
                else
                {
                    msg << LEditArr[i][j][0]->text();
                }
            }
        }
        break;
    }
    default:
        break;
    }
    emit request(msg);
}

#pragma warning(disable:26495)
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

    fc->close();
    delete fc;
    fc = new TInterface(height, width);
    emit ChangedSize(fc);
    fc->show();
    this->hide();
}