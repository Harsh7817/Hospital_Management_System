#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include<iostream>
#include<string>
using namespace std;
class appointment
{
    public:
    
        int apid,pid,did;
        string name,date,time;
        
        void bookappointment();
        void asavetofile();
        bool checkdoctorconflict(int ,string ,int ,string ,int ,string );
        bool checkdoctoravailability(int ,string ,int ,string ,int ,string );
};

#endif