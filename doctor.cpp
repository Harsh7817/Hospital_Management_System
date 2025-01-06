#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"doctor.h"
using namespace std;
void doctor::adddoctor()
{
    cout<<endl;
    cout<<"Enter doctor id:";
    cin>>id;

    cout<<"Enter doctor name:";
    cin.ignore();
    getline(cin,name);
    name.erase(name.find_last_not_of(" \n\r\t") + 1);//Erase extra space

    cout<<"Enter doctor experience(in years):";
    cin>>experience;

    cout<<"Enter doctor's specialization:";
    cin.ignore();
    getline(cin,specialization);
    specialization.erase(specialization.find_last_not_of(" \n\r\t") + 1);

    dsavetofile();
}
void doctor::dsavetofile()
{
    ofstream file("doctor.txt", ios::app);
    file <<id<<","<<name<<","<<experience<<","<<specialization<<endl;

    file.close();

    cout<<"* * * * * * Doctor Details saved successfully * * * * * *"<<endl<<endl;

    cout<<"NOW YOU ARE BEING REDIRECTING TO DOCTOR MANAGEMENT SECTION............."<<endl;
}
void doctor::deletedoctor()
{
    int did;

    cout<<"Enter the id of doctor to delete:";
    cin>>did;

    ifstream file("doctor.txt");
    ofstream tempfile("temp.txt");

    string line;
    bool found=false;

    if(!file)
    {
        cout<<"Error in opening the file!"<<endl;
        return;
    }

    while(getline(file,line))
    {
        string str_did=to_string(did);

        if(line.find(str_did)!=0)
        {
            tempfile<<line<<endl;
        }
        else
        {
            found=true;
        }
    }

    file.close();
    tempfile.close();
    
    if(found)
    {
        remove("doctor.txt");
        rename("temp.txt","doctor.txt");
        cout<<endl;
        cout<<"Doctor with id"<<" "<<did<<" "<<"has been deleted";
    }
    
    else
    {
        cout<<endl;
        cout<<"Doctor with id"<<" "<<did<<" "<<"has not been found";
        remove("temp.txt");
    }
}
void doctor::displaydoctors()
{
    ifstream file("doctor.txt");
    string line;

    if(!file)
    {
        cout<<"Error in opening the file!!"<<endl;
    }

    cout<<endl;
    cout<<"List of Doctors available:"<<endl;
    
    cout<<endl;
    while(getline(file,line))
    {
        cout<<line<<endl;
    }
}
// int main()
// {
//     doctor d;
//     //d.adddoctor();
//     //d.deletedoctor();
//     d.displaydoctors();
// }