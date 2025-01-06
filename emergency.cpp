#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm>
#include <sstream>
using namespace std;

class EmergencyWard 
{
private:
    struct Bed 
    {
        int bedID;
        string wardType;
        bool isOccupied;
        string patientName;
        string condition;
    };

    vector<Bed> emergencyBeds;

public:
    // Constructor: Load beds data from the file
    EmergencyWard(const string& filename) 
    {
        loadBeds(filename);
    }

    // Function to load emergency beds from the file
    void loadBeds(const string& filename) 
    {
        ifstream file(filename);
        if (!file) 
        {
            cerr << "Error: Unable to open the file: " << filename << endl;
            return;
        }

        emergencyBeds.clear();  // Clear existing beds data before loading

        int bedID;
        string wardType;
        bool isOccupied;
        string patientName, condition;

        while (file >> bedID >> wardType >> isOccupied) 
        {
            file.ignore();  // Ignore newline
            getline(file, patientName);  // Get the patient name
            getline(file, condition);  // Get the patient's condition
            emergencyBeds.push_back({bedID, wardType, isOccupied, patientName, condition});
        }

        file.close();
        cout << "Emergency beds loaded successfully from " << filename << endl;
    }

    // Function to save emergency beds to the file
    void saveBeds(const string& filename) 
    {
        ofstream file(filename);

        if (!file) 
        {
            cerr << "Error: Unable to open the file: " << filename << endl;
            return;
        }
        for (const auto& bed : emergencyBeds) 
        {
            file << bed.bedID << " " << bed.wardType << " " << bed.isOccupied << " "
                 << bed.patientName << " " << bed.condition << endl;
        }

        file.close();
        cout << "Emergency beds saved successfully to " << filename << endl;
    }

    // Function to display available emergency beds
    void displayAvailableBeds() 
    {
        cout << "\nAvailable Emergency Beds:\n";
        cout << setw(10) << "Bed ID" << setw(15) << "Ward Type" << setw(15) << "Status" << setw(20) << "Condition" << endl;
        cout << "------------------------------------------------------------" << endl;

        for (const auto& bed : emergencyBeds) 
        {

            if (!bed.isOccupied) 
            {
                cout << setw(10) << bed.bedID << setw(15) << bed.wardType << setw(15) << "Available" 
                     << setw(20) << "N/A" << endl;
            }
        }
    }

    // Function to add a new emergency bed
    void addBed() 
    {
        int bedID;
        string wardType;

        bool isOccupied;
        string patientName = "", condition = "N/A";

        // Prompt for bed details
        cout << "\nEnter Bed ID: ";
        cin >> bedID;

        // Check if the bed ID already exists
        for (const auto& bed : emergencyBeds) 
        {
            if (bed.bedID == bedID) 
            {
                cout << "Error: Bed ID already exists. Please try again with a different ID." << endl;
                return;
            }
        }

        cout << "Enter Ward Type (e.g., General, ICU, Emergency): ";
        cin >> wardType;

        cout << "Is the bed occupied? (0 for No, 1 for Yes): ";
        cin >> isOccupied;

        if (isOccupied) 
        {
            cout << "Enter Patient Name: ";
            cin.ignore();  // Ignore leftover newline
            getline(cin, patientName);

            cout << "Enter Patient's Condition (e.g., Critical, Stable): ";
            getline(cin, condition);
        }

        // Add new bed to the vector
        emergencyBeds.push_back({bedID, wardType, isOccupied, patientName, condition});
        cout << "New emergency bed added successfully!" << endl;
    }

    // Function to allocate an emergency bed to a patient
    void allocateBed() 
    {
        int bedID;
        string patientName, condition;

        displayAvailableBeds();
        cout << "\nEnter the Bed ID to allocate: ";
        cin >> bedID;

        bool found = false;
        for (auto& bed : emergencyBeds) 
        {
            if (bed.bedID == bedID && !bed.isOccupied) 
            {
                cout << "Enter Patient Name: ";
                cin.ignore();
                getline(cin, patientName);

                cout << "Enter Patient's Condition (e.g., Critical, Stable): ";
                getline(cin, condition);

                bed.isOccupied = true;
                bed.patientName = patientName;
                bed.condition = condition;
                cout << "Emergency Bed allocated successfully to " << patientName << "!" << endl;
                found = true;
                break;
            }

        }

        if (!found) 
        {
            cout << "Bed ID not available for allocation. Please try again." << endl;
        }

    }

    // Function to release an emergency bed
    void releaseBed() 
    {
        int bedID;

        cout << "\nEnter the Bed ID to release: ";
        cin >> bedID;

        bool found = false;
        for (auto& bed : emergencyBeds) 
        {
            if (bed.bedID == bedID && bed.isOccupied) 
            {
                cout << "Bed released successfully from patient: " << bed.patientName << "!" << endl;
                bed.isOccupied = false;
                bed.patientName = "";
                bed.condition = "N/A";
                found = true;
                break;
            }
        }

        if (!found) 
        {
            cout << "Bed ID not found or is already vacant!" << endl;
        }
    }

    // Function to search for emergency beds by ward type
    void searchBedsByWard() 
    {
        string wardType;

        cout << "\nEnter the Ward Type to search (e.g., General, ICU, Emergency): ";
        cin >> wardType;

        cout << "\nBeds in " << wardType << " Ward:\n";
        cout << setw(10) << "Bed ID" << setw(15) << "Status" << setw(20) << "Patient Name" << setw(20) << "Condition" << endl;
        cout << "--------------------------------------------------" << endl;

        for (const auto& bed : emergencyBeds)
        {
            if (bed.wardType == wardType) 
            {
                cout << setw(10) << bed.bedID
                     << setw(15) << (bed.isOccupied ? "Occupied" : "Available")
                     << setw(20) << (bed.isOccupied ? bed.patientName : "N/A")
                     << setw(20) << (bed.isOccupied ? bed.condition : "N/A") << endl;
            }

        }
    }

    // Function to update bed information
    void updateBed() 
    {
        int bedID;
        cout << "\nEnter the Bed ID to update: ";
        cin >> bedID;

        bool found = false;
        for (auto& bed : emergencyBeds) 
        {

            if (bed.bedID == bedID) 
            {
                cout << "Updating bed with ID: " << bedID << endl;
                cout << "Enter new Ward Type: ";
                cin >> bed.wardType;

                cout << "Enter new Patient Name: ";
                cin.ignore();
                getline(cin, bed.patientName);

                cout << "Enter new Patient's Condition: ";
                getline(cin, bed.condition);

                found = true;
                cout << "Bed updated successfully!" << endl;
                break;
            }

        }

        if (!found) 
        {
            cout << "Bed ID not found!" << endl;
        }

    }

    // Function to sort beds by Bed ID
    void sortBedsByID() 
    {
        sort(emergencyBeds.begin(), emergencyBeds.end(), [](const Bed& a, const Bed& b) 
        {
            return a.bedID < b.bedID;
        });

        cout << "Beds sorted by Bed ID successfully!" << endl;
    }

    // Function to export beds data to CSV file
    void exportToCSV() 
    {

        ofstream file("emergency_beds.csv");

        if (!file) 
        {
            cerr << "Error: Unable to open the CSV file." << endl;
            return;
        }

        file << "Bed ID,Ward Type,Occupied,Patient Name,Condition\n";

        for (const auto& bed : emergencyBeds) 
        {
            file << bed.bedID << ","
                 << bed.wardType << ","
                 << (bed.isOccupied ? "Yes" : "No") << ","
                 << bed.patientName << ","
                 << bed.condition << "\n";
        }

        file.close();
        cout << "Emergency beds data exported to emergency_beds.csv successfully!" << endl;
    }

    // Function to manage emergency beds
    void manageEmergencyBeds() 
    {
        const string filename = "emergency.txt";
        int choice;

        while (true) 
        {
            cout << "\nEmergency Ward Management Menu:\n";

            cout << "1. View Available Emergency Beds\n";
            cout << "2. Allocate Emergency Bed\n";
            cout << "3. Release Emergency Bed\n";
            cout << "4. Search Emergency Beds by Ward Type\n";
            cout << "5. Add New Emergency Bed\n";
            cout << "6. Update Bed Information\n";
            cout << "7. Sort Beds by Bed ID\n";
            cout << "8. Export to CSV\n";
            cout << "9. Save and Exit\n";

            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) 
            {
                case 1:
                    displayAvailableBeds();
                    break;

                case 2:
                    allocateBed();
                    break;

                case 3:
                    releaseBed();
                    break;

                case 4:
                    searchBedsByWard();
                    break;

                case 5:
                    addBed();
                    break;

                case 6:
                    updateBed();
                    break;

                case 7:
                    sortBedsByID();
                    break;

                case 8:
                    exportToCSV();
                    break;

                case 9:
                    saveBeds(filename);
                    cout << "Changes saved. Exiting Emergency Ward Management." << endl;
                    return;

                default:
                    cout << "Invalid choice. Please try again!" << endl;

            }

        }

    }
};

//Main function to drive the program

// int main() 
// {
//     EmergencyWard wardManager("emergency.txt");
//     wardManager.manageEmergencyBeds();
//     return 0;
// }
