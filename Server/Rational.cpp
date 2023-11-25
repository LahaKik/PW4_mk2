#include "Rational.h"
void Rational::MakeIrreducible()
{
	if (upNum == 0 && downNum != 0)
	{
		downNum = 1;
		return;
	}

	const Uint simpleNum[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277,	281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631,	641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997 };
	std::vector<Uint> simpleDevidersUP;
	std::vector<Uint> simpleDevidersDOWN;
	int signUP = upNum >= 0 ? 1 : -1;
	Uint UPtmp = upNum * signUP;
	Uint DOWNtmp = downNum;
	Uint i = 0;
	while (UPtmp > 1 || DOWNtmp > 1)
	{
		while (UPtmp > 1 && UPtmp % simpleNum[i] == 0)
		{
			simpleDevidersUP.push_back(simpleNum[i]);
			UPtmp /= simpleNum[i];
		}
		while (DOWNtmp > 1 && DOWNtmp % simpleNum[i] == 0)
		{
			simpleDevidersDOWN.push_back(simpleNum[i]);
			DOWNtmp /= simpleNum[i];
		}

		i++;
	}

	if (upNum < downNum)
	{
		Uint i = 0;
		while (i != simpleDevidersUP.size())
		{
			Uint j = 0;
			bool IsDeleted = false;
			while (j != simpleDevidersDOWN.size())
			{
				if (simpleDevidersUP[i] == simpleDevidersDOWN[j])
				{
					IsDeleted = true;
					simpleDevidersUP.erase(simpleDevidersUP.begin() + i);
					simpleDevidersDOWN.erase(simpleDevidersDOWN.begin() + j);
					break;
				}
				else
					j++;
			}
			if (!IsDeleted)
				i++;
		}
	}
	else
	{
		Uint i = 0;
		while (i != simpleDevidersDOWN.size())
		{
			Uint j = 0;
			bool IsDeleted = false;
			while (j != simpleDevidersUP.size())
			{
				if (simpleDevidersUP[j] == simpleDevidersDOWN[i])
				{
					IsDeleted = true;
					simpleDevidersUP.erase(simpleDevidersUP.begin() + j);
					simpleDevidersDOWN.erase(simpleDevidersDOWN.begin() + i);
					break;
				}
				else
					j++;
			}
			if (!IsDeleted)
				i++;
		}
	}

	upNum = signUP;
	for (Uint dev : simpleDevidersUP)
	{
		upNum *= dev;
	}
	downNum = 1;

	for (Uint dev : simpleDevidersDOWN)
	{
		downNum *= dev;
	}
}

QChar Rational::separator = TMessageSeparator;

Rational::Rational(const QByteArray& arr)
{
	int IndSep = arr.indexOf(separator.toLatin1());
	upNum = arr.left(IndSep).toInt();
	downNum = arr.right(arr.length() - IndSep - 1).toInt();
	MakeIrreducible();
}

QByteArray& operator>> (QByteArray& arr, Rational& num)
{
	int IndSep = arr.indexOf(Rational::separator.toLatin1());
	IndSep = arr.indexOf(Rational::separator.toLatin1(), IndSep + 1);
	if (IndSep > 0)
	{
		num = arr.left(IndSep);
		arr = arr.right(arr.length() - IndSep - 1);
	}
	return arr;
}

QString& operator<< (QString& str, const Rational& num)
{
	str.append(QString().setNum(num.upNum));
	str.append(TMessageSeparator);
	str.append(QString().setNum(num.downNum));
	str.append(TMessageSeparator);
	return str;
}

QString Rational::ToQString()
{
	QString str;
	str.append(QString().setNum(upNum));
	str.append(TMessageSeparator);
	str.append(QString().setNum(downNum));
	str.append(TMessageSeparator);
	return str;
}
