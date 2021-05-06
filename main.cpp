#include <iostream>
#include "hugeNumberType.h"

using namespace std;

int main() {
    hugeNumberType h1 = hugeNumberType("1829");
    hugeNumberType h2 = hugeNumberType("37");
    hugeNumberType h3;
    h3 = h1 / h2;
    h1.print();
    h2.print();
    cout << "-----" << endl;
    h3.print();

    return 0;
}
