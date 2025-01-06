// #include<iostream>
// #include<string>
// #include<iomanip>
// #include<fstream>
// #include<sstream>
// #include"patient.cpp"
// #include"doctor.cpp"
// #include"appointment.cpp"
// #include"shortestpath.cpp"
// #include"medicine.cpp"
// using namespace std;
// void patientmanagement()
// {
//     patient p;
//     int ch;

//     cout<<endl<<endl;
//     cout<<"----------------------------------------"<<endl;
//     cout<<"| Welcome to Patient Management Section|"<<endl;
//     cout<<"----------------------------------------"<<endl;
//     cout<<endl<<endl;

//     cout<<"1.Add Patient"<<endl;
//     cout<<"2.Search Patient"<<endl;
//     cout<<"3.Remove a Patient"<<endl;
//     cout<<"4.Display Patient's List"<<endl;
//     cout<<"5.Sort and save Patient's List"<<endl;
//     cout<<"6.Go Back to Main Menu"<<endl;

//     cout<<"Enter your choice:";
//     cin>>ch;

//     switch (ch)
//     {
//         case 1:p.addpatient();
//                cout<<endl;
//                patientmanagement();
//                break;

//         case 2:p.searchpatient();
//                cout<<endl;
//                patientmanagement();
//                break;

//         case 3:p.deletepatient();
//                cout<<endl;
//                patientmanagement();
//                break;

//         case 4:p.displaypatientlist();
//                cout<<endl;
//                patientmanagement();
//                break;

//         case 5:{
//                      vector<patient> sortedPatients = p.getSortedPatientListFromFile();
//                      p.saveSortedPatientListToFile(sortedPatients);
//                }
//                patientmanagement();
//                break;

//         case 6:cout<<"Switching to main menu!!!......"<<endl;
//                break;

//         default:cout<<"Invalid choice!!!"<<endl;
//                 cout<<"Enter again:";
//                 cin>>ch;
//     }
// }
// void doctormanagement()
// {
//     cout<<endl<<endl;
//     cout<<"----------------------------------------"<<endl;
//     cout<<"| Welcome to Doctor Management Section|"<<endl;
//     cout<<"----------------------------------------"<<endl;
//     cout<<endl<<endl;

//     doctor d;
//     int ch;

//     cout<<endl;
//     cout<<endl;
//     cout<<"1.Add Doctor"<<endl;
//     cout<<"2.Remove a Doctor"<<endl;
//     cout<<"3.Display Doctor's List"<<endl;
//     cout<<"4.Go Back to Main Menu"<<endl;

//     cout<<"Enter your choice:";
//     cin>>ch;

//     switch (ch)
//     {
//         case 1:d.adddoctor();
//                cout<<endl;
//                doctormanagement();
//                break;

//         case 2:d.deletedoctor();
//                cout<<endl;
//                doctormanagement();
//                break;

//         case 3:d.displaydoctors();
//                cout<<endl;
//                doctormanagement();
//                break;

//         case 4:cout<<"Switching to main menu!!!......"<<endl;
//                break;

//         default:cout<<"Invalid choice!!!"<<endl;
//                 cout<<"Enter again:";
//                 cin>>ch;

//     }
// }
// void appointmentbooking()
// {
//     appointment a;
//     doctor d;

//     d.displaydoctors();
//     cout<<endl;

//     cout<<"The list of doctors is in the format:Doctorid,Doctor name,Experience,Specialization"<<endl;
//     a.bookappointment();
// }
// void locationManagement() 
// {
//     ShortestPath sp;
    
//     // Predefined locations in the hospital
//     sp.addLocation("Reception");
//     sp.addLocation("Emergency");

//     sp.addLocation("ICU");
//     sp.addLocation("Pharmacy");

//     sp.addLocation("Operation Theater");
//     sp.addLocation("Radiology");
    
//     // Predefined connections between locations
//     sp.addConnection("Reception", "Emergency");
//     sp.addConnection("Reception", "Pharmacy");

//     sp.addConnection("Emergency", "ICU");
//     sp.addConnection("ICU", "Operation Theater");

//     sp.addConnection("Operation Theater", "Radiology");
//     sp.addConnection("Pharmacy", "Radiology");

//     int choice;
//         cout << "\nLocation Management:" << endl;
//         cout << "1. Display all locations" << endl;
//         cout << "2. Find the shortest path" << endl;
//         cout << "3. Back to main menu" << endl;

//         cout << "Enter your choice: ";
//         cin >> choice;

//         switch (choice) 
//         {
//             case 1:sp.displayLocations();
//                    locationManagement();
//                    break;

//             case 2: {string start, target;
//                     cout << "Enter starting location: ";
//                     cin.ignore();
//                     getline(cin, start);
//                     cout << "Enter target location: ";
//                     getline(cin, target);
//                     sp.findShortestPath(start, target);
//                     locationManagement();
//                     break;}
            

//             case 3:
//                 cout << "Returning to main menu!" << endl;
//                 break;

//             default:
//                 cout << "Invalid choice! Please try again." << endl;
//         };
// }
// void medicinesection()
// {
//        medicine m;
//        int ch;
//        cout<<endl;
//        cout<<"\n1.Add a new medicine in the list"<<endl;
//        cout<<"2.Calculte Total bill"<<endl;
//        cout<<"3.Go to Main Menu"<<endl;

//        cout<<"Enter your choice:";
//        cin>>ch;

//        switch(ch)
//        {
//               case 1:m.addmedicine();
//                      medicinesection();
//                      break;

//               case 2:m.tbill();
//                      medicinesection();
//                      break;

//               case 3:cout<<"Switching to main menu!!!......"<<endl;
//                      break;

//               default:cout<<"Invalid choice!!!"<<endl;
//                       cout<<"Enter again:";
//                       cin>>ch;

              
//        }
// }
// int main()
// {
//     cout<<"                                                       "<<"=============================="<<endl;
//     cout<<"                                        "<<"||               "<<"HOSPITAL MANAGEMENT SYSTEM"<<"               ||"<<endl;
//     cout<<"                                                       "<<"=============================="<<endl;

//     cout<<endl<<endl;

//     start:
//     cout<<endl;
//     cout<<"     "<<"----------"<<endl;
//     cout<<"     "<<"|Main Menu|"<<" "<<endl;
//     cout<<"     "<<"----------";

//     cout<<endl<<endl;

//     cout<<"1.Patient Management"<<endl;
//     cout<<"2.Doctor Management"<<endl;
//     cout<<"3.Schedule a appointment"<<endl;
//     cout<<"4.Find shortest route"<<endl;
//     cout<<"5.Medicine Section"<<endl;
//     cout<<"6.Exit"<<endl;

//     int ch;
//     cout<<"Enter your choice:";
//     cin>>ch;

//     switch (ch)
//     {
//         case 1:patientmanagement();
//                goto start;
//                break;

//         case 2:doctormanagement();
//                goto start;
//                break;

//         case 3:appointmentbooking();
//                goto start;
//                break;

//         case 4:locationManagement();
//                goto start;
//                break;

//         case 5:medicinesection();
//                goto start;
//                break;

//         case 6:cout<<"Exiting!!!......"<<endl;
//                break;

//         default:cout<<"Invalid choice!!!"<<endl;
//                 cout<<"Enter again:";
//                 cin>>ch;

//     }
    
// }