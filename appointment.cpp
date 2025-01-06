#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"appointment.h"
using namespace std;
bool appointment::checkdoctoravailability(int apid,string date,int pid,string name,int did,string time)
{
    ifstream file("doctor.txt");

    string line;
    bool found=false;

    file.clear();
    file.seekg(0, ios::beg);

    while(getline(file,line))
    {
        size_t pos = line.find(',');
        string doctorID = line.substr(0, pos);
        string sid_str = to_string(did);

        if(doctorID==to_string(did))
        {
            return true;
        }

    }
    return false;
}
bool appointment::checkdoctorconflict(int apid,string date,int pid,string name,int did,string time)
{
    ifstream file("appointment.txt");

    string aline,id,ddate,ttime;
    file.clear();
    file.seekg(0, ios::beg);

    while (getline(file, aline)) 
    {
        size_t pos1 = aline.find(','); // Find the first comma (doctor ID)
        if (pos1 != string::npos) 
        {
            string doctorID = aline.substr(0, pos1); // Extract doctor ID
            size_t pos2 = aline.find(',', pos1 + 1); // Find the second comma (appointment date)

            if (pos2 != string::npos) 
            {
                string apdate = aline.substr(pos1 + 1, pos2 - pos1 - 1); // Extract appointment date
                size_t pos3 = aline.find(',', pos2 + 1); // Find the third comma (appointment time)

                if (pos3 != string::npos) 
                {
                    string aptime = aline.substr(pos2 + 1, pos3 - pos2 - 1); // Extract appointment time

                    // Compare doctor ID, appointment date, and appointment time
                    if (doctorID == to_string(did) && apdate == date && aptime == time) 
                    {
                        return false; // Conflict found
                    }

                }

            }

        }

    }

    return true;
}
void appointment::bookappointment()
{
    cout<<"Enter appointment id:";
    cin>>apid;

    cout<<"Enter date of appointment:";
    cin.ignore();
    getline(cin,date);
  

    cout<<"Enter patient id:";
    cin>>pid;

    cout<<"Enter patient name:";
    cin.ignore();
    getline(cin,name);
   

    cout<<"Enter doctor id:";
    cin>>did;

    cout<<"Enter time of appointment:";
    cin.ignore();
    getline(cin,time);

    
    int a=checkdoctoravailability(apid,date,pid,name,did,time);;
    int b=checkdoctorconflict(apid,date,pid,name,did,time);

    while(!a)
    {
        cout<<"Doctor having id = "<<did<<" is not available."<<endl;
        cout<<endl;
        cout<<"\nEnter doctor id again:";
        cin>>did;
        a=checkdoctoravailability(apid,date,pid,name,did,time);
    }

    if(!b)
    {
        cout<<"Doctor having id = "<<did<<" have another appointment on this time."<<endl;
        cout<<"\nBook Your Appointment Again."<<endl;
        cout<<"\nYou are redirecting to the Main Menu......."<<endl;
        return;
    }

    asavetofile();
    return;
}
void appointment::asavetofile()
{
    ofstream file("appointment.txt",ios::app);
    file<<did<<","<<date<<","<<time<<","<<name<<","<<apid<<","<<pid<<endl;
    file.close();
    cout<<"Appointment Scheduled.\n"<<endl;
}
// int main()
// {
//     appointment a;
//     a.bookappointment();
// }