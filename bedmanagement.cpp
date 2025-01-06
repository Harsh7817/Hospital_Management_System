#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm>
using namespace std;

// Struct to represent a bed
struct Bed 
{
    int bedID;
    string wardType;   
    bool isOccupied;
    string patientName;
};

struct Booking 
{
    int bedID;
    string patientName;
    string wardType;
    string date; // Booking date
};

// Global vector for managing beds
vector<Bed> beds;
vector<Booking> bookingHistory;

// Function to load bed data from a file
void loadBeds(const string& filename) 
{
    ifstream file(filename);
    if (!file) 
    {
        cerr << "Error: Unable to open the file: " << filename << endl;
        return;
    }

    beds.clear(); // Clear existing data before loading

    int bedID;
    string wardType;
    bool isOccupied;
    string patientName;

    while (file >> bedID >> wardType >> isOccupied) 
    {
        file.ignore(); // Ignore newline
        getline(file, patientName); // Get the patient name
        beds.push_back({bedID, wardType, isOccupied, patientName});
    }

    file.close();
    cout << "Beds loaded successfully from " << filename << endl;
}

// Function to save bed data to a file
void saveBeds(const string& filename) 
{
    ofstream file(filename);
    if (!file) 
    {
        cerr << "Error: Unable to open the file: " << filename << endl;
        return;
    }

    for (const auto& bed : beds) 
    {
        file << bed.bedID << " " << bed.wardType << " " << bed.isOccupied << " " << bed.patientName << endl;
    }

    file.close();
    cout << "Beds saved successfully to " << filename << endl;
}

// Function to display available beds
void displayAvailableBeds() 
{
    cout << "\nAvailable Beds:\n";
    cout << setw(10) << "Bed ID" << setw(15) << "Ward Type" << setw(15) << "Status" << endl;
    cout << "------------------------------------------" << endl;

    for (const auto& bed : beds) 
    {
        if (!bed.isOccupied) 
        {
            cout << setw(10) << bed.bedID << setw(15) << bed.wardType << setw(15) << "Available" << endl;
        }
    }
}

// Function to allocate a bed to a patient
void allocateBed() 
{
    int bedID;
    string patientName;

    displayAvailableBeds();
    cout << "\nEnter the Bed ID to allocate: ";
    cin >> bedID;

    bool found = false;
    for (auto& bed : beds) 
    {
        if (bed.bedID == bedID && !bed.isOccupied) 
        {
            cout << "Enter Patient Name: ";
            cin.ignore();
            getline(cin, patientName);

            bed.isOccupied = true;
            bed.patientName = patientName;
            cout << "Bed allocated successfully to " << patientName << "!" << endl;
            found = true;
            break;
        }
    }

    if (!found) 
    {
        cout << "Bed ID not available for allocation. Please try again." << endl;
    }
}

// Function to release a bed
void releaseBed() 
{
    int bedID;

    cout << "\nEnter the Bed ID to release: ";
    cin >> bedID;

    bool found = false;
    for (auto& bed : beds) 
    {
        if (bed.bedID == bedID && bed.isOccupied) 
        {
            cout << "Bed released successfully from patient: " << bed.patientName << "!" << endl;
            bed.isOccupied = false;

            bed.patientName = "";
            found = true;
            break;
        }
    }

    if (!found) 
    {
        cout << "Bed ID not found or is already vacant!" << endl;
    }
}

// Function to search for beds by ward type
void searchBedsByWard() 
{
    string wardType;

    cout << "\nEnter the Ward Type to search (e.g., General, ICU, Private): ";
    cin >> wardType;

    cout << "\nBeds in " << wardType << " Ward:\n";
    cout << setw(10) << "Bed ID" << setw(15) << "Status" << setw(20) << "Patient Name" << endl;
    cout << "--------------------------------------------------" << endl;


    for (const auto& bed : beds) 
    {

        if (bed.wardType == wardType) 
        {
            cout << setw(10) << bed.bedID
                 << setw(15) << (bed.isOccupied ? "Occupied" : "Available")
                 << setw(20) << (bed.isOccupied ? bed.patientName : "N/A") << endl;
        }
    }
}

// Function to view bed availability summary
void viewBedSummary() 
{
    map<string, int> totalBeds;
    map<string, int> availableBeds;

    for (const auto& bed : beds) 
    {
        totalBeds[bed.wardType]++;
        if (!bed.isOccupied) 
        {
            availableBeds[bed.wardType]++;
        }
    }

    cout << "\nBed Availability Summary:\n";
    cout << setw(15) << "Ward Type" << setw(15) << "Total Beds" << setw(20) << "Available Beds" << endl;
    cout << "--------------------------------------------------" << endl;

    for (const auto& entry : totalBeds) 
    {
        cout << setw(15) << entry.first
             << setw(15) << entry.second
             << setw(20) << availableBeds[entry.first] << endl;
    }
}

// Function to manage beds
// Function to add a new bed
void addBed() 
{
    int bedID;
    string wardType;
    bool isOccupied;
    string patientName = "";

    // Prompt for bed details
    cout << "\nEnter Bed ID: ";
    cin >> bedID;

    // Check if the bed ID already exists
    for (const auto& bed : beds) 
    {
        if (bed.bedID == bedID)
        {
            cout << "Error: Bed ID already exists. Please try again with a different ID." << endl;
            return;
        }
    }

    cout << "Enter Ward Type (e.g., General, ICU, Private): ";
    cin >> wardType;

    cout << "Is the bed occupied? (0 for No, 1 for Yes): ";
    cin >> isOccupied;

    if (isOccupied) 
    {
        cout << "Enter Patient Name: ";
        cin.ignore(); // Ignore leftover newline
        getline(cin, patientName);
    }

    // Add new bed to the vector
    beds.push_back({bedID, wardType, isOccupied, patientName});
    cout << "New bed added successfully!" << endl;
}

void displayBookingHistory() 
{
    cout << "\nBed Booking History:\n";
    cout << setw(10) << "Bed ID" << setw(20) << "Patient Name" << setw(15) << "Ward Type" << setw(15) << "Date" << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (const auto& booking : bookingHistory) 
    {
        cout << setw(10) << booking.bedID
             << setw(20) << booking.patientName
             << setw(15) << booking.wardType
             << setw(15) << booking.date << endl;
    }
}

void sendCapacityAlert() 
{
    map<string, int> totalBeds;
    map<string, int> occupiedBeds;

    for (const auto& bed : beds) 
    {
        totalBeds[bed.wardType]++;
        if (bed.isOccupied) 
        {
            occupiedBeds[bed.wardType]++;
        }
    }

    cout << "\nCapacity Alerts:\n";
    for (const auto& ward : totalBeds) 
    {
        int total = ward.second;
        int occupied = occupiedBeds[ward.first];
        double occupancyRate = (double)occupied / total * 100;

        if (occupancyRate >= 80.0) 
        {
            cout << "Warning: " << ward.first << " ward is at " << occupancyRate << "% capacity!" << endl;
        }

    }
}

// Function to display all beds in a detailed format
void displayDetailedBeds() 
{
    cout << "\nDetailed Bed Information:\n";
    cout << setw(10) << "Bed ID" << setw(15) << "Ward Type" << setw(15) << "Status" << setw(20) << "Patient Name" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (const auto& bed : beds) 
    {
        cout << setw(10) << bed.bedID
             << setw(15) << bed.wardType
             << setw(15) << (bed.isOccupied ? "Occupied" : "Available")
             << setw(20) << (bed.isOccupied ? bed.patientName : "N/A") << endl;
    }

}

void advancedFeatures() 
{
    int choice;

    while (true) 
    {

        cout << "\nAdvanced Features Menu:\n";
        
        cout << "1. View Booking History\n";
        cout << "2. Send Capacity Alerts\n";
        cout << "3. Display Detailed Bed Info\n";
        cout << "4. Back to Main Menu\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                displayBookingHistory();
                break;

            case 2:
                sendCapacityAlert();
                break;

            case 3:
                displayDetailedBeds();
                break;

            case 4:
                return;

            default:
                cout << "Invalid choice. Please try again!" << endl;
        }

    }
}

// Function to manage beds (updated with add bed option)
void manageBeds() 
{
    const string filename = "beds.txt";
    loadBeds(filename);

    int choice;

    while (true) 
    {
        cout << "\nBed Management Menu:\n";

        cout << "1. View Available Beds\n";
        cout << "2. Allocate Bed\n";
        cout << "3. Release Bed\n";
        cout << "4. Search Beds by Ward Type\n";
        cout << "5. View Bed Summary\n";
        cout << "6. Add New Bed\n";  // Option to add new bed
        cout << "7. Advanced Features\n";
        cout << "8. Save and Exit\n";

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
                viewBedSummary();
                break;

            case 6:
                addBed();  // Call the add bed function
                break;

            case 7:
                advancedFeatures();
                break;

            case 8:
                saveBeds(filename);
                cout << "Changes saved. Exiting Bed Management." << endl;
                return;

            default:
                cout << "Invalid choice. Please try again!" << endl;
        }

    }
}

// int main() 
// {
//     manageBeds();
//     return 0;
// }
