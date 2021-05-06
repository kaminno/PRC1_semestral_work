#include <iostream>
#include "hugeNumberType.h"

using namespace std;


// Konstruktory a destruktor


hugeNumberType::hugeNumberType()
        : size(0), stringNumber(""), number(nullptr)
{}

hugeNumberType::hugeNumberType(const string &str)
        : size(str.length()), number(nullptr), stringNumber(str)
{
    bool minus = false;
    stringNumber =  removeFirstZeros(stringNumber);
    if(stringNumber[0] == '-'){
        minus = true;
        stringNumber[0] = '0';
        stringNumber = removeFirstZeros(stringNumber);
    }
    size = stringNumber.length();
    if(size > 200){
        cerr << "To large number" << endl;
    }
    number = new int[size];
    for(int i = 0; i < size; i++){
        number[i] = stringNumber[i] - '0';
    }
    if(minus){
        number[0] = -number[0];
    }
}

hugeNumberType::~hugeNumberType()=default;



// Pomocné funkce


// Funkce odstraní přebytečné nuly na začátku čísla
string removeFirstZeros(string str){
    int l = str.size();
    string newStr;
    bool firstZero = true;
    for(int i = 0; i < l; i++){
        if(str[i] == '0' && firstZero){
            continue;
        }
        else{
            newStr += str[i];
            firstZero = false;
        }
    }
    if(newStr.empty()){
        return "0";
    }
    return newStr;
}

// Funkce otočí řetězec
string reverseString(string str){
    int n = str.size();
    string nstr;
    for(int i = 0; i < n; i++){
        nstr += str[n - i - 1];
    }
    return nstr;
}

// Funkce sečte dvě kladná čísla typu hugeNumberType
hugeNumberType addition(hugeNumberType a, hugeNumberType b){
    string finalResult;
    int length = 0, res, z = 0, an, bn;
    bool az = false, bz = false;
    if(a.getOneNumber(0) < 0){
        az = true;
    }
    if(b.getOneNumber(0) < 0){
        bz = true;
    }

    while(true){
        a.setOneNumber(0, abs(a.getOneNumber(0)));
        b.setOneNumber(0, abs(b.getOneNumber(0)));

        // Nastavení správných hodnot pro výpočet
        if(length >= a.getSize()){
            an = 0;
        }
        else{
            an = a.getOneNumber(a.getSize() - length - 1);
        }
        if(length >= b.getSize()){
            bn = 0;
        }
        else{
            bn = b.getOneNumber(b.getSize() - length - 1);
        }
        res = an + bn + z;
        if(res > 9){
            res -= 10;
            z = 1;
        }
        else{
            z = 0;
        }
        finalResult += (char)(res + 48);

        // Ukončovací sekvence
        if(length >= a.getSize() && length >= b.getSize()){
            finalResult = reverseString(finalResult);
            hugeNumberType fr = hugeNumberType(finalResult);
            if(az){
                a.setOneNumber(0, -a.getOneNumber(0));
            }
            if(bz){
                b.setOneNumber(0, -b.getOneNumber(0));
            }
            return fr;
        }
        length++;
    }
}

// Funkce odečte dvě kladná čísla typu hugeNumberType
hugeNumberType subtractions(hugeNumberType a, hugeNumberType b){
    string finalResult;
    int length = 0, res, z = 0, an, bn;
    bool az = false, bz = false;
    if(a.getOneNumber(0) < 0){
        az = true;
    }
    if(b.getOneNumber(0) < 0){
        bz = true;
    }

    while(true){
        a.setOneNumber(0, abs(a.getOneNumber(0)));
        b.setOneNumber(0, abs(b.getOneNumber(0)));

        // Nastavení správných hodnot pro výpočet
        if(length >= a.getSize()){
            an = 0;
        }
        else{
            an = a.getOneNumber(a.getSize() - length - 1);
        }
        if(length >= b.getSize()){
            bn = 0;
        }
        else{
            bn = b.getOneNumber(b.getSize() - length - 1);
        }
        res = an - (bn + z);
        if(res < 0){
            res += 10;
            z = 1;
        }
        else{
            z = 0;
        }
        finalResult += (char)(res + 48);
        // Ukončovací sekvence
        if(length >= a.getSize() && length >= b.getSize()){
            finalResult = reverseString(finalResult);
            hugeNumberType fr = hugeNumberType(finalResult);
            if(az){
                a.setOneNumber(0, -a.getOneNumber(0));
            }
            if(bz){
                b.setOneNumber(0, -b.getOneNumber(0));
            }
            return fr;
        }
        length++;
    }
}

// Funkce porovná císla typu hugeNumberType
bool compare(hugeNumberType a, hugeNumberType b){
    if(a.getSize() > b.getSize()){
        return true;
    }
    else if(a.getSize() < b.getSize()){
        return false;
    }
    else{
        for(int i = 0; i < a.getSize(); i++){
            if(abs(a.getOneNumber(i)) > abs(b.getOneNumber(i))){
                return true;
            }
            if(abs(a.getOneNumber(i)) < abs(b.getOneNumber(i))){
                return false;
            }
        }
    }
}

// Funkce pow() vracející typ hugeNumberType
hugeNumberType hpow(int number, int exp){
    hugeNumberType result = hugeNumberType("1");
    for(int i = 0; i < exp; i++){
        result = result * number;
    }
    return result;
}

// Funkce vracející absolutní hodnotu
int ab(int a){
    if(a < 0){
        return (-a);
    }
    return a;
}



// Přetížené operátory


hugeNumberType& hugeNumberType::operator=(const hugeNumberType &a){
    this->size = a.size;
    this->stringNumber = a.stringNumber;
    this->number = new int[this->size];
    for(int i = 0; i < this->size; i++){
        this->number[i] = a.number[i];
    }
    return *this;
}

bool operator==(hugeNumberType &a, hugeNumberType &b){
    if(a.getSize() != b.getSize()){
        return  false;
    }
    return !(a.stringNumber != b.stringNumber);
}

hugeNumberType operator+(hugeNumberType &a, hugeNumberType &b){
    if((a.getOneNumber(0) < 0 && b.getOneNumber(0) < 0) || (a.getOneNumber(0) > 0 && b.getOneNumber(0) > 0)){
        if(a.getOneNumber(0) < 0 && b.getOneNumber(0) < 0){
            hugeNumberType h = addition(a, b);
            h.setOneNumber(0, -h.getOneNumber(0));
            return h;
        }
        return addition(a, b);
    }
    else{
        bool az = false, bz = false;
        if(a.getOneNumber(0) < 0){
            az = true;
        }
        if(b.getOneNumber(0) < 0){
            bz = true;
        }
        if(compare(a, b)){
            hugeNumberType h = subtractions(a, b);
            if(az){
                h.setOneNumber(0, -h.getOneNumber(0));
                return h;
            }
            return h;
        }
        else{
            hugeNumberType h = subtractions(b, a);
            if(bz){
                h.setOneNumber(0, -h.getOneNumber(0));
                return h;
            }
            return h;
        }
    }
}

hugeNumberType operator-(hugeNumberType &a, hugeNumberType &b){
    if(a.getOneNumber(0) < 0 && b.getOneNumber(0) < 0){
        if(compare(a, b)){
            hugeNumberType h = subtractions(a, b);
            h.setOneNumber(0, -h.getOneNumber(0));
            return h;
        }
        else{
            hugeNumberType h = subtractions(b, a);
            return h;
        }
    }
    else if(a.getOneNumber(0) < 0 && b.getOneNumber(0) >= 0){
        hugeNumberType h = addition(a, b);
        h.setOneNumber(0, -h.getOneNumber(0));
        return h;
    }
    else if(a.getOneNumber(0) >= 0 && b.getOneNumber(0) < 0){
        hugeNumberType h = addition(a, b);
        return h;
    }
    else{
        if(compare(a, b)){
            hugeNumberType h = subtractions(a, b);
            return h;
        }
        else{
            hugeNumberType h = subtractions(b, a);
            h.setOneNumber(0, -h.getOneNumber(0));
            return h;
        }
    }
}

hugeNumberType operator*(hugeNumberType a, hugeNumberType b){
    int aSize = a.getSize()-1, bSize = b.getSize()-1;
    int fm, currentNumber, rest = 0;
    hugeNumberType dec, result = hugeNumberType("0"), semiresult = hugeNumberType("0");
    bool negative = false, az = false, bz = false;
    if((a.getOneNumber(0) < 0 && b.getOneNumber(0) > 0) || (a.getOneNumber(0) > 0 && b.getOneNumber(0) < 0)){
        negative = true;
    }
    if(a.getOneNumber(0) < 0){
        az = true;
    }
    if(b.getOneNumber(0) < 0){
        bz = true;
    }
    a.setOneNumber(0, ab(a.getOneNumber(0)));
    b.setOneNumber(0, ab(b.getOneNumber(0)));
    for(int i = 0; i <= bSize+1; i++){
        dec = hpow(10, i);
        for(int j = 0; j <= aSize+1; j++){
            fm = b.getOneNumber(bSize - i) * a.getOneNumber(aSize - j);
            currentNumber = (fm % 10) + rest;
            if(currentNumber > 9){
                currentNumber -= 10;
                rest = 1;
            }
            else{
                rest = 0;
            }
            hugeNumberType hugeCurrentNumber = currentNumber * hpow(10, j);
            semiresult = semiresult + hugeCurrentNumber;
            rest = ((fm - rest)/10)+rest;
        }
        for(int l = 1; l < dec.getSize(); l++){
            semiresult = semiresult * 10;
        }
        result = result + semiresult;
        semiresult = hugeNumberType("0");
    }
    hugeNumberType h = result;
    if(az){
        a.setOneNumber(0, -a.getOneNumber(0));
    }
    if(bz){
        b.setOneNumber(0, -b.getOneNumber(0));
    }
    if(negative){
        h.setOneNumber(0, -h.getOneNumber(0));
    }
    return h;
}

hugeNumberType operator*(hugeNumberType &a, int b){
    hugeNumberType result = hugeNumberType("0");
    for(int i = 0; i < b; i++){
        result = result + a;
    }
    return result;
}

hugeNumberType operator*(int a, hugeNumberType b){
    hugeNumberType result = hugeNumberType("0");
    for(int i = 0; i < a; i++){
        result = result + b;
    }
    return result;
}

hugeNumberType operator/(hugeNumberType &a, hugeNumberType &b){
    bool negative = false, az = false, bz = false;
    if((a.getOneNumber(0) < 0 && b.getOneNumber(0) > 0) || (a.getOneNumber(0) > 0 && b.getOneNumber(0) < 0)){
        negative = true;
    }

    hugeNumberType result = hugeNumberType("0"), semiresult = a, z = result;
    hugeNumberType one = hugeNumberType("1");

    if(b == result){
        cerr << "Nelze dělit nulou!" << endl;
        return result;
    }
    else if(a == result){
        return result;
    }

    int exp = 0;
    hugeNumberType semisemiresult, dec;

    if(a == b){
        if(a.getOneNumber(0) < 0 xor b.getOneNumber(0) < 0){
            one.setOneNumber(0, -1);
            return one;
        }
        return one;
    }
    else if(b == one){
        result = a;
        if(b.getOneNumber(0) < 0){
            result.setOneNumber(0, -result.getOneNumber(0));
            return result;
        }
        return result;
    }
    else if(compare(a, b)){
        if(a.getOneNumber(0) < 0){
            az = true;
            a.setOneNumber(0, abs(a.getOneNumber(0)));
        }
        if(b.getOneNumber(0) < 0){
            bz = true;
            b.setOneNumber(0, abs(b.getOneNumber(0)));
        }
        while(compare(semiresult, b)){
            if(semiresult.getSize() - b.getSize() < 5){
                if(compare(semiresult - b, hugeNumberType("0"))){
                    result = result + one;
                    semiresult = semiresult - b;
                }
            }
            else{
                for(int i = 0; i < b.getSize(); i++){
                    if(semiresult.getOneNumber(i) < b.getOneNumber(i)){
                        exp = semiresult.getSize() - b.getSize() - 1;
                        break;
                    }
                    exp = semiresult.getSize() - b.getSize() - 1;
                }
                dec = hpow(10, exp);
                semisemiresult = b * dec;
                semiresult = semiresult - semisemiresult;
                result = result + dec;
            }
        }
    }
    else{
        cerr << "Nelze provést celočíselné dělení" << endl;
    }
    if(az){
        a.setOneNumber(0, -a.getOneNumber(0));
    }
    if(bz){
        b.setOneNumber(0, -b.getOneNumber(0));
    }
    if(negative){
        result.setOneNumber(0, -result.getOneNumber(0));
    }
    return result;
}



// Ostatní metody


// Metoda nastaví číslo na zadané pozici
void hugeNumberType::setOneNumber(int index, int value) {
    if(value <= 9){
        number[index] = value;
    }
    else{
        cerr << "zadáváš příliš veliké číslo" << endl;
        return;
    }
}

// Metoda vypíše číslo na standardní výstup
void hugeNumberType::print(){
    if(number[0] < 0){
        cout << "-" << stringNumber << endl;
    }
    else
        cout << stringNumber << endl;
}