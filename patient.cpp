#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include"patient.h"
using namespace std;
vector<patient> patient::getPatientListFromFile() 
{
    vector<patient> patientList;
    ifstream file("patient.txt");
    string line;

    if (!file.is_open()) 
    {
        throw runtime_error("Error: Unable to open the file!");
    }

    while (getline(file, line)) 
    {
        stringstream ss(line);
        string pr,idStr, name, ageStr, disease;

        getline(ss, pr, ',');
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, ageStr, ',');
        getline(ss, disease, ',');

        patient p;
        p.priority=stoi(pr);
        p.id = stoi(idStr);
        p.name = name;
        p.age = stoi(ageStr);
        p.disease = disease;

        patientList.push_back(p);
    }

    file.close();
    return patientList;
}

// Partition function for Quick Sort
int partition(vector<patient>& patientsList, int low, int high) 
{
    int pivotid = patientsList[high].priority;
    int i = low - 1;

    for (int j = low; j < high; j++) 
    {
        if (patientsList[j].priority < pivotid) 
        {
            i++;
            swap(patientsList[i], patientsList[j]);
        }
    }

    swap(patientsList[i + 1], patientsList[high]);
    return i + 1;
}

// Quick Sort function
void quickSort(std::vector<patient>& patientsList, int low, int high) 
{
    if (low < high) 
    {
        int pivot = partition(patientsList, low, high);
        quickSort(patientsList, low, pivot - 1);
        quickSort(patientsList, pivot + 1, high);
    }
}

// Function to retrieve and sort the patient data from the patient.txt file
vector<patient> patient::getSortedPatientListFromFile() 
{
    // Retrieve the patient list from the file
    vector<patient> patientList = getPatientListFromFile();

    // Sort the list using Quick Sort based on the patient's id
    quickSort(patientList, 0, patientList.size() - 1);

    return patientList;
}

// Function to save the sorted patient list back to the file
void patient::saveSortedPatientListToFile(const vector<patient>& sortedPatientList) 
{
    ofstream file("patient.txt");

    if (!file.is_open()) 
    {
        throw runtime_error("Error: Unable to open the file for writing!");
    }

    // Save each patient's data back to the file
    for (const auto& p : sortedPatientList) 
    {
        file <<p.priority<<","<< p.id << "," << p.name << "," << p.age << "," << p.disease << endl;
    }

    file.close();
    cout<<endl;

    cout << "\nSorted patient list has been saved to the file." << endl;
    cout<<"Taking you back to Patient Management.....";
}

void patient::addpatient()
{
    cout<<"Enter patient id:";
    cin>>id;

    cout<<"Enter patient name:";
    cin.ignore();
    getline(cin,name);

    cout<<"Enter patient age:";
    cin>>age;

    cout<<"Enter patient's disease:";
    cin.ignore();
    getline(cin,disease);

    cout<<"Enter patient priority(1 for High, 2 for Medium, 3 for low)";
    cin>>priority;
    cout<<endl;
    psavetofile();
}
void patient::psavetofile()
{
    ofstream file("patient.txt", ios::app);

    file <<id<<","<<priority<<","<<name<<","<<age<<","<<disease<<endl;
    file.close();

    cout<<endl;

    cout<<"* * * * * * Patient data saved successfully * * * * * *"<<endl<<endl;
    cout<<"NOW YOU ARE BEING REDIRECTING TO PATIENT MANAGEMENT SECTION............."<<endl;
}
void patient::searchpatient()
{
    int a,sid;

    ifstream file("patient.txt");
    string search,line,temp;

    bool found=false;

    cout<<"\nEnter search term(1 for id or 2 for name):";
    cin>>a;

    if(!file)
    {
        cout<<"Error in opening the file";
        return;
    }

    if(a==1)
    {
        cout<<"Enter pateint id:";
        cin>>sid;
        cout<<endl;
        cout<<"\nSearching for the data........<<endl";
        cout<<endl;
        file.clear();
        file.seekg(0, ios::beg);

        while(getline(file,line))
        {
            string sid_str = to_string(sid);
            if(line.find(sid_str)==0)
            {
                cout<<"Patient found."<<endl<<endl;
                cout<<line;
                cout<<endl;
                cout<<"Taking you back to the patient management system.....";
                found=true;
                break;
            }
        }
    }
    else if(a==2)
    {
        cout<<"Enter pateint name:";

        cin.ignore();
        getline(cin,search);

        cout<<endl;
        cout<<"Searching for the data........"<<endl;
        cout<<endl;

        file.clear();
        file.seekg(0, ios::beg);

        while(getline(file,line))
        {
            if(line.find(search)!=string::npos)
            {
                cout<<"Patient found."<<endl<<endl;

                cout<<line;
                cout<<endl;

                cout<<"Taking you back to the patient management system.....";
                found=true;

                break;
            }
        }
    }
    else
    {
        cout<<"Incorrect input";
    }
    
    if(!found)
    {
        cout<<"Data not found!!";
        cout<<endl;
        cout<<"Taking you back to the patient management system.....";
    }
    file.close();
   
}
void patient::deletepatient()
{
    int did;

    cout<<"Enter the id of patient to delete:";
    cin>>did;

    ifstream file("patient.txt");
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
        remove("patient.txt");

        rename("temp.txt","patient.txt");

        cout<<endl;

        cout<<"Patient with id"<<" "<<did<<" "<<"has been deleted";
        cout<<endl;
        cout<<"\nTaking you back to the Patient Management System.....";
    }
    else
    {
        cout<<endl;
        cout<<"Patient with id"<<" "<<did<<" "<<"has not been found";
        cout<<endl;
        cout<<"\nTaking you back to the Patient Management System.....";
        remove("temp.txt");
    }
}
void patient::displaypatientlist()
{
    ifstream file("patient.txt");

    string line;

    if(!file)
    {
        cout<<"Error in opening the file!!"<<endl;
    }

    cout<<endl;

    cout<<"\nPatient's list:"<<endl<<endl;
    cout<<endl;

    while(getline(file,line))
    {
        cout<<line<<endl;
    }

    cout<<endl;
    cout<<"\nTaking you back to the Patient Management.....";
}
// int main() 
// {
//     patient p;
//     int choice;

//     while(choice)
//     {
//         cout << "\nMenu: \n";

//         cout << "1. Add Patient\n";
//         cout << "2. Search Patient\n";
//         cout << "3. Delete Patient\n";
//         cout << "4. Display Patient List\n";
//         cout << "5. Sort and Save Patient List\n";
//         cout << "6. Exit\n";

//         cout << "Enter your choice: ";
//         cin >> choice;

//         switch(choice) 
//         {
//             case 1:
//                 // Add a new patient
//                 p.addpatient();
//                 break;
//             case 2:
//                 // Search for a patient
//                 p.searchpatient();
//                 break;
//             case 3:
//                 // Delete a patient
//                 p.deletepatient();
//                 break;
//             case 4:
//                 // Display patient list
//                 p.displaypatientlist();
//                 break;
//             case 5:
//                 // Sort the patient list and save to file
//                 {
//                     vector<patient> sortedPatients = p.getSortedPatientListFromFile();
//                     p.saveSortedPatientListToFile(sortedPatients);
//                 }
//                 break;
//             case 6:
//                 // Exit the program
//                 cout << "Exiting the program.\n";
//                 return 0;
//             default:
//                 cout << "Invalid choice. Please try again.\n";
//         }
//     }

//     return 0;
// }