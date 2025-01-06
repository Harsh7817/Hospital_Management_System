#include<iostream>
#include<fstream>
#include<sstream>
#include"medicine.h"
using namespace std;
void medicine::addmedicine()
{
    cout<<"Enter mediciene price:";
    cin>>mprice;

    cout<<endl;
    cout<<"Enter mediciene name:";
    cin.ignore();
    getline(cin,mname);

    msavetofile();
}
void medicine::msavetofile()
{
    ofstream file("medicine.txt",ios::app);

    file << mname <<"," << mprice<<endl;

    cout<<"New medicine added successfully in the list."<<endl;
    cout<<endl;
    cout<<"Taking you back to the medicine section.....";
}
int medicine::tbill() 
{
    int n;
    int i = 0;
    int totalbill = 0;

    cout<<"Enter the number of medicines you want to purchase:";
    cin>>n;

    while(i < n) 
    {
        string pname;

        cout<<"Enter the name of "<<i+1<<"st medicine: ";
        cin>>pname;

        ifstream file("medicine.txt");
        if (!file.is_open()) 
        {
            cout<<"Error: Could not open the file!"<<endl;
            return -1;
        }

        string line;
        bool found = false;

        while(getline(file, line)) 
        {
            size_t pos = line.find(',');
            if (pos != string::npos) 
            {
                string medname = line.substr(0, pos);
                string pricestr = line.substr(pos + 1);

                if (medname == pname) 
                {
                    int price = stoi(pricestr); 
                    totalbill += price; 

                    found = true;
                    break; 
                }
            }
        }

        if (!found) 
        {
            cout << "Medicine " << pname << " not found in the list." << endl;
        }

        file.close(); 
        i++;
    }

    cout << "The total bill is: " << totalbill << endl;
    cout<<"\nTaking you back to the medicine section.....";
}
// int main()
// {
//     medicine m;
//     //m.addmedicine();
//     m.tbill();
// }