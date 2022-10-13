// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0) {
        throw std::invalid_argument("Error");
    }

    this->BitLen = len;
    this->MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;

    this->pMem = new TELEM[this->MemLen];

    for (int i = 0; i < MemLen; i++) {
        this->pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;

    this->pMem = new TELEM[bf.MemLen];

    for (int i = 0; i < this->MemLen; i++) {
        this->pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] this->pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return (TELEM)1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return this->BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n > this->BitLen) {
        throw std::invalid_argument("Error");
    }

    this->pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n > this->BitLen) {
        throw std::invalid_argument("Error");
    }

    this->pMem[GetMemIndex(n)] &= (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n > this->BitLen) {
        throw std::invalid_argument("Error");
    }

    return (this->pMem[GetMemIndex(n)] & GetMemMask(n)) >> (n % (sizeof(TELEM) * 8));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    TELEM* tmp = new TELEM[bf.MemLen];

    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;

    for (int i = 0; i < this->MemLen; i++) {
        tmp[i] = bf.pMem[i];
    }

    delete[] this->pMem;

    this->pMem = tmp;

    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (this->BitLen != bf.BitLen || this->MemLen != bf.MemLen) {
        return 0;
    }

    for (int i = 0; i < this->MemLen; i++) {
        if (this->pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }

    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return ~(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    TBitField tmp(max(this->BitLen, bf.BitLen));

    for (int i = 0; i < tmp.BitLen; i++) {
        if (i < this->BitLen && GetBit(i) || i < bf.BitLen && bf.GetBit(i))
            tmp.SetBit(i);
    }

    return tmp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    TBitField tmp(max(this->BitLen, bf.BitLen));

    for (int i = 0; i < tmp.BitLen; i++) {
        tmp.SetBit(i);
        if (i >= this->BitLen || i >= bf.BitLen || (!(this->GetBit(i))) || (!bf.GetBit(i))) {
            tmp.ClrBit(i);
        }
    }

    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmpF(BitLen);
    TBitField tmpS(BitLen);

    for (int i = 0; i < this->BitLen; i++) {
        tmpS.SetBit(i);
    }
    for (int i = 0; i < this->MemLen; i++) {
        tmpF.pMem[i] = ~(this->pMem[i]);
    }
    tmpF = tmpS & tmpF;

    return tmpF;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    char in;
    int i = 0;
    istr >> in;
    while (in != ' ') {
        istr >> in;
        if (in == '1') {
            bf.SetBit(i++);
        } else {
            bf.ClrBit(i++);
        }
    }

    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); i++) {
        ostr << bf.GetBit(i);
    }

    return ostr;
}