#ifndef MEDICINE_H
#define MEDICINE_H
#include<iostream>
#include<string>
using namespace std;
class medicine
{
    public:
        string mname;
        int mprice;
        
        void addmedicine();
        void msavetofile();
        int tbill();
};
#endif