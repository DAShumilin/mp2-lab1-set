// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    this->MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.MaxPower)
{
    this->BitField = s.BitField;
    this->MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf.GetLength())
{
    this->BitField = bf;
    this->MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    TBitField tmp(this->MaxPower);
    tmp = this->BitField;

    return tmp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return this->MaxPower;;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (this->BitField.GetBit(Elem) == 1) {
        return 1;
    }
    else {
        return 0;
    }
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (*this == s) {
        return *this;
    }

    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;

    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    if (this->MaxPower != s.MaxPower) {
        return 0;
    }
    else if ((this->MaxPower == s.MaxPower) && (this->BitField == s.BitField)) {
        return 1;
    }
    else {
        return 0;
    }
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet& s) // объединение
{
    TSet tmp(this->MaxPower > s.MaxPower ? this->MaxPower : s.MaxPower);
    tmp.BitField = this->BitField | s.BitField;

    return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet tmp(this->MaxPower);
    tmp.BitField = this->BitField;
    tmp.InsElem(Elem);

    return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet tmp(this->MaxPower);
    tmp.BitField = this->BitField;
    tmp.DelElem(Elem);

    return tmp;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet tmp(this->MaxPower > s.MaxPower ? this->MaxPower : s.MaxPower);
    tmp.BitField = this->BitField & s.BitField;

    return tmp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet tmp(this->MaxPower);
    tmp.BitField = ~this->BitField;

    return tmp;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    ostr << s.BitField;

    return ostr;
}