#ifndef ZAPOCTOVKA_HUGENUMBERTYPE_H
#define ZAPOCTOVKA_HUGENUMBERTYPE_H

#include <iostream>

using namespace std;

class hugeNumberType{
    int size;
    int *number;
public:
    string stringNumber;
    hugeNumberType();
    hugeNumberType(const string &str);
    ~hugeNumberType();

    int getSize() {return size;};
    int getOneNumber(int index) {return number[index];};
    void setOneNumber(int index, int value);
    void print();

    hugeNumberType& operator=(const hugeNumberType &hnt);
};

string removeFirstZeros(string str);
hugeNumberType hpow(int number, int exp);

hugeNumberType operator+(hugeNumberType &a, hugeNumberType &b);
hugeNumberType operator-(hugeNumberType &a, hugeNumberType &b);
hugeNumberType operator/(hugeNumberType &a, hugeNumberType &b);
bool operator==(hugeNumberType &a, hugeNumberType &b);
hugeNumberType operator*(hugeNumberType &a, int b);
hugeNumberType operator*(int a, hugeNumberType b);
hugeNumberType operator*(hugeNumberType a, hugeNumberType b);

#endif //ZAPOCTOVKA_HUGENUMBERTYPE_H