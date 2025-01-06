#ifndef PATIENT_H
#define PATIENT_H
//for using multiple times
#include<iostream>
#include<string>
#include<vector>

using namespace std;
class patient
{
    public:
        int id;
        int age;
        int priority;

        string name;
        string disease;

        void addpatient();
        void psavetofile();
        void searchpatient();
        void deletepatient();
        void displaypatientlist();
        
        vector<patient> getPatientListFromFile();
        vector<patient> getSortedPatientListFromFile();
        void saveSortedPatientListToFile(const vector<patient>& sortedPatientList);
};

#endif
