/*! @file main.cpp
    @brief parte principal onde o vector pode ser testaddo.
*/

#ifndef VECTOR_h
#define VECTOR_H
#include "../include/vector.h"
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef CSTDLIB
#define CSTDLIB
#include <cstdlib>
#endif

using namespace std;

int main(){
    int a = 5;
    vector<int> l({1, 2, 6, 7, 8, 9 , 88, 0, 78});
    vector<int> m({3, 4, 5});
    //l.erase(l.end());

    cout << m << endl;  
    return 0;
}
