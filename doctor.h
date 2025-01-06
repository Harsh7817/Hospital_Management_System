#ifndef DOCTOR_H
#define DOCTOR_H
//for using multiple times
#include<iostream>
#include<string>
using namespace std;
class doctor
{
    public:

        int id,experience;
        string name,specialization;
        
        void adddoctor();
        void dsavetofile();
        void deletedoctor();
        void displaydoctors();
};

#endif