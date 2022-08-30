#include<iostream>
#include"./array.hpp"
#include "./matrix.hpp"
#include "./polynomial.hpp"
#include <ctime>
using namespace std;
clock_t start,stop;
double totalTime;

int main(){
    SparseMatrix m;
    m.Init(3);        //    l hl
    m.Set(1,1,1);       //1 1 2 2
    m.Set(1,1,2);       //1 2 0 2
    m.Set(3,2,0);
    m.Set(5,2,2);
    m.Set(7,2,2);
    m.Set(6,1,2);
    SparseMatrix m2;
    m2.Init(3);
    m2.Set(9,0,0);
    m2.Set(3,1,1);
    SparseMatrix m3=m+m2;
   // m.Display();
   // m2.Display();
    m3.Display();
   // cout<<m.IndexOfCord(2,2);
    //m.Display();
}