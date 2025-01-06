#include <iostream>
#include <fstream>

#include <string>
#include <unordered_map>

#include <conio.h> // For _getch() to mask password input
#include <ctime> // For logging timestamps
#include <windows.h> // For SetConsoleTextAttribute

#include"patient.cpp"
#include"doctor.cpp"

#include"appointment.cpp"
#include"shortestpath.cpp"

#include"medicine.cpp"
#include"bedmanagement.cpp"
#include"emergency.cpp"
#include"feedback.cpp"
#include"canteen.cpp"
using namespace std;

// Function to set text color
void setColor(int color) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Struct to hold user credentials along with a security question and answer
struct User 
{
    string password;
    string securityQuestion;
    string securityAnswer;
};

// Function to load credentials from a file
unordered_map<string, User> loadCredentials(const string& filename) 
{
    unordered_map<string, User> credentials;
    ifstream file(filename);
    string username, password, securityQuestion, securityAnswer;

    if (!file) 
    {
        cerr << "Error: Unable to open the credentials file: " << filename << endl;
        return credentials;
    }
    while (file >> username >> password) 
    {
        file.ignore(); // Ignore the newline after password
        getline(file, securityQuestion);
        getline(file, securityAnswer);
        credentials[username] = {password, securityQuestion, securityAnswer};
    }

    file.close();
    return credentials;
}

// Function to save new credentials to a file
void saveCredential(const string& filename, const string& username, const User& user) 
{
    ofstream file(filename, ios::app);
    if (!file) 
    {
        cerr << "Error: Unable to open the credentials file: " << filename << endl;
        return;
    }
    file << username << " " << user.password << endl;
    file << user.securityQuestion << endl;
    file << user.securityAnswer << endl;
    file.close();
}

// Function to overwrite credentials in a file
void overwriteCredentials(const string& filename, const unordered_map<string, User>& credentials) 
{
    ofstream file(filename);
    if (!file) 
    {
        cerr << "Error: Unable to open the credentials file: " << filename << endl;
        return;
    }

    // Iterate through the unordered_map using iterators
    for (auto it = credentials.begin(); it != credentials.end(); ++it) 
    {
        const string& username = it->first;
        const User& user = it->second;
        file << username << " " << user.password << endl;
        file << user.securityQuestion << endl;
        file << user.securityAnswer << endl;
    }

    file.close();
}

// Function to read the password with masking
string readPassword() 
{
    string password;
    char ch;
    while (true) 
    {
        ch = _getch(); // Get a single character
        if (ch == '\r')
        { 
            // Enter key
            cout << endl;
            break;
        } 
        else if (ch == '\b' && !password.empty()) 
        { 
            // Backspace
            cout << "\b \b"; // Erase last character on the console
            password.pop_back();
        } 
        else if (ch != '\b') 
        {
            cout << '*';
            password += ch;
        }

    }

    return password;
}

// Function to validate if a password meets the required strength
bool isPasswordStrong(const string& password) 
{

    if (password.length() < 8) 
    {
        return false;
    }
      // Minimum length check
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (char ch : password) 
    {
        if (isupper(ch)) 
        {
            hasUpper = true;
        }
        else if (islower(ch))
        {
            hasLower = true;
        }
        else if (isdigit(ch)) 
        {
            hasDigit = true;
        }
        else if (ispunct(ch)) 
        {
            hasSpecial = true;
        }
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

// Function to validate login
bool validateLogin(const string& filename, const string& username, const string& password) 
{
    unordered_map<string, User> credentials = loadCredentials(filename);
    return credentials.find(username) != credentials.end() && credentials[username].password == password;
}
// Function to log system activities

void logActivity(const string& message) 
{
    ofstream logFile("activity_log.txt", ios::app);
    if (!logFile) 
    {
        cerr << "Error: Unable to open the log file!" << endl;
        return;
    }
    time_t now = time(0);
    char* dt = ctime(&now);
    logFile << "[" << dt << "] " << message << endl;
    logFile.close();
}

// Function for first-time sign-in
void firstTimeSignIn(const string& filename) 
{
    setColor(10); // Set color to green for first-time sign-in
    cout << "First-time Sign-In" << endl;
    setColor(7); // Reset color to default
    cout << "Enter a new username: ";

    string username;
    cin >> username;

    // Ensure username is unique
    unordered_map<string, User> credentials = loadCredentials(filename);

    if (credentials.find(username) != credentials.end()) 
    {
        setColor(12); // Red color for error
        cout << "Username already exists! Please choose a different one." << endl;

        setColor(7); // Reset color to default
        return;
    }

    cout << "Enter a new password: ";
    string password = readPassword();
    
    // Password strength validation
    while (!isPasswordStrong(password)) 
    {
        setColor(12); // Red color for error
        cout << "Password is too weak! It must be at least 8 characters long and contain uppercase, lowercase, digit, and special characters." << endl;

        setColor(7); // Reset color to default
        password = readPassword();
    }

    cin.ignore(); // Ignore leftover newline character
    cout << "Enter a security question: ";

    string securityQuestion;
    getline(cin, securityQuestion);

    cout << "Enter the answer to your security question: ";

    string securityAnswer;
    getline(cin, securityAnswer);

    User newUser = {password, securityQuestion, securityAnswer};
    saveCredential(filename, username, newUser);

    setColor(10); // Green color for success
    cout << "Account created successfully!" << endl;

    setColor(7); // Reset color to default

    logActivity("New user created: " + username);
}

// Function to handle forgot password
void forgotPassword(const string& filename) 
{

    unordered_map<string, User> credentials = loadCredentials(filename);

    setColor(14); // Yellow color for forgot password
    cout << "Forgot Password" << endl;

    setColor(7); // Reset color to default
    cout << "Enter your username: ";

    string username;
    cin >> username;

    if (credentials.find(username) == credentials.end()) 
    {
        setColor(12); // Red color for error
        cout << "Username not found! Please sign up first." << endl;
        setColor(7); // Reset color to default
        return;
    }

    User& user = credentials[username];

    cout << "Answer the following security question to reset your password:" << endl;
    cout << user.securityQuestion << endl;
    cin.ignore();

    string answer;
    getline(cin, answer);
    if (answer != user.securityAnswer) 
    {
        setColor(12); // Red color for error
        cout << "Incorrect answer to the security question. Cannot reset password." << endl;

        setColor(7); // Reset color to default
        return;
    }

    cout << "Enter your new password: ";
    string newPassword = readPassword();
    while (!isPasswordStrong(newPassword)) 
    {
        setColor(12); // Red color for error
        cout << "Password is too weak! It must be at least 8 characters long and contain uppercase, lowercase, digit, and special characters." << endl;
        setColor(7); // Reset color to default
        newPassword = readPassword();
    }

    user.password = newPassword;
    overwriteCredentials(filename, credentials);
    setColor(10); // Green color for success

    cout << "Password updated successfully!" << endl;
    setColor(7); // Reset color to default
    logActivity("Password reset for user: " + username);
}
void adoctormanagement()
{
    cout<<endl<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<"| Welcome to Doctor Management Section|"<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<endl<<endl;

    doctor d;
    int ch;
    cout<<endl;
    cout<<endl;

    cout<<"1.Add Doctor"<<endl;
    cout<<"2.Remove a Doctor"<<endl;
    cout<<"3.Display Doctor's List"<<endl;
    cout<<"4.Go Back to Admin Menu"<<endl;

    cout<<"Enter your choice:";
    cin>>ch;

    switch (ch)
    {
        case 1:
            d.adddoctor();
            cout<<endl;
            adoctormanagement();
            break;

        case 2:
            d.deletedoctor();
            cout<<endl;
            adoctormanagement();
            break;

        case 3:
            d.displaydoctors();
            cout<<endl;
            adoctormanagement();
            break;

        case 4:
            cout<<"Switching to admin menu!!!......"<<endl;
            break;

        default:
            cout<<"Invalid choice!!!"<<endl;
            cout<<"Enter again:";
            cin>>ch;

    }

}
void apatientmanagement()
{
    patient p;
    int ch;

    cout<<endl<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<"| Welcome to Patient Management Section|"<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<endl<<endl;

    cout<<"1.Add Patient"<<endl;
    cout<<"2.Search Patient"<<endl;
    cout<<"3.Remove a Patient"<<endl;
    cout<<"4.Display Patient's List"<<endl;
    cout<<"5.Sort and save Patient's List"<<endl;
    cout<<"6.Go Back to Main Menu"<<endl;

    cout<<"Enter your choice:";
    cin>>ch;

    switch (ch)
    {
        case 1:
            p.addpatient();
            cout<<endl;
            apatientmanagement();
            break;

        case 2:
            p.searchpatient();
            cout<<endl;
            apatientmanagement();
            break;

        case 3:
            p.deletepatient();
            cout<<endl;
            apatientmanagement();
            break;

        case 4:
            p.displaypatientlist();
            cout<<endl;
            apatientmanagement();
            break;

        case 5:
                {
                     vector<patient> sortedPatients = p.getSortedPatientListFromFile();
                     p.saveSortedPatientListToFile(sortedPatients);
                }
               apatientmanagement();
               break;

        case 6:
            cout<<"Switching to main menu!!!......"<<endl;
            break;

        default:
                cout<<"Invalid choice!!!"<<endl;
                cout<<"Enter again:";
                cin>>ch;

    }
}
void amedicinesection()
{
       medicine m;
       int ch;
       cout<<endl;
       cout<<"\n1.Add a new medicine in the list"<<endl;
       cout<<"2.Go to Admin Menu"<<endl;

       cout<<"Enter your choice:";
       cin>>ch;

       switch(ch)
       {
              case 1:
                    m.addmedicine();
                    amedicinesection();
                    break;

              case 2:
                    cout<<"Switching to Admin menu!!!......"<<endl;
                    break;

              default:
                    cout<<"Invalid choice!!!"<<endl;
                    cout<<"Enter again:";
                    cin>>ch;        
       }
}

void abedmanagement()
{
    const string filename = "beds.txt";
    loadBeds(filename);

    int choice;
    while (true) {
        cout << "\nBed Management Menu:\n";
        cout << "1. View Available Beds\n";
        cout << "2. Allocate Bed\n";
        cout << "3. Release Bed\n";
        cout << "4. Search Beds by Ward Type\n";
        cout << "5. View Bed Summary\n";
        cout << "6. Add New Bed\n";  // Option to add new bed
        cout << "7. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
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
                saveBeds(filename);
                cout << "Changes saved. Exiting Bed Management." << endl;
                return;

            default:
                cout << "Invalid choice. Please try again!" << endl;
        }
    }
}

void adisplayBookingHistory() 
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

void asendCapacityAlert() 
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
void adisplayDetailedBeds() 
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

void aadvancedFeatures() 
{
    int choice;

    while (true) 
    {
        cout << "\nAdvanced Features Menu:\n";
        cout << "1. Send Capacity Alerts\n";
        cout << "2. Display Detailed Bed Info\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                asendCapacityAlert();
                break;

            case 2:
                adisplayDetailedBeds();
                break;

            case 3:
                return;

            default:
                cout << "Invalid choice. Please try again!" << endl;
        }

    }

}

void upatientmanagement()
{
    patient p;
    int ch;

    cout<<endl<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<"| Welcome to Patient Management Section|"<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<endl<<endl;

    cout<<"1.Add Patient"<<endl;
    cout<<"2.Search Patient"<<endl;
    cout<<"3.Display Patient's List"<<endl;
    cout<<"4.Go Back to Main Menu"<<endl;

    cout<<"Enter your choice:";
    cin>>ch;

    switch (ch)
    {
        case 1:
            p.addpatient();
            cout<<endl;
            upatientmanagement();
            break;

        case 2:
            p.searchpatient();
            cout<<endl;
            upatientmanagement();
            break;

        case 3:
            p.displaypatientlist();
            cout<<endl;
            upatientmanagement();
            break;

        case 4:
            cout<<"Switching to main menu!!!......"<<endl;
            break;

        default:
            cout<<"Invalid choice!!!"<<endl;
            cout<<"Enter again:";
            cin>>ch;

    }
}

void udoctormanagement()
{
    cout<<endl<<endl;

    cout<<"----------------------------------------"<<endl;
    cout<<"| Welcome to Doctor Management Section|"<<endl;
    cout<<"----------------------------------------"<<endl;
    
    cout<<endl<<endl;

    doctor d;
    int ch;

    cout<<endl;
    cout<<endl;

    cout<<"1.Display Doctor's List"<<endl;
    cout<<"2.Go Back to Main Menu"<<endl;

    cout<<"Enter your choice:";
    cin>>ch;

    switch (ch)
    {
        case 1:
            d.displaydoctors();
            cout<<endl;
            udoctormanagement();
            break;

        case 2:
            cout<<"Switching to main menu!!!......"<<endl;
            break;

        default:
            cout<<"Invalid choice!!!"<<endl;
            cout<<"Enter again:";
            cin>>ch;

    }

}

void appointmentbooking()
{
    appointment a;
    doctor d;

    d.displaydoctors();
    cout<<endl;

    cout<<"The list of doctors is in the format:Doctorid,Doctor name,Experience,Specialization"<<endl;
    a.bookappointment();
}

void locationManagement() 
{
    ShortestPath sp;
    
    // Predefined locations in the hospital

    sp.addLocation("Reception");
    sp.addLocation("Emergency");

    sp.addLocation("ICU");
    sp.addLocation("Pharmacy");

    sp.addLocation("Operation Theater");
    sp.addLocation("Radiology");
    
    // Predefined connections between locations

    sp.addConnection("Reception", "Emergency");
    sp.addConnection("Reception", "Pharmacy");

    sp.addConnection("Emergency", "ICU");
    sp.addConnection("ICU", "Operation Theater");

    sp.addConnection("Operation Theater", "Radiology");
    sp.addConnection("Pharmacy", "Radiology");

    int choice;

        cout << "\nLocation Management:" << endl;
        cout << "1. Display all locations" << endl;
        cout << "2. Find the shortest path" << endl;
        cout << "3. Back to main menu" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                sp.displayLocations();
                locationManagement();
                break;

            case 2: 
                {
                    string start, target;
                    cout << "Enter starting location: ";
                    cin.ignore();
                    getline(cin, start);
                    cout << "Enter target location: ";
                    getline(cin, target);
                    sp.findShortestPath(start, target);
                    locationManagement();
                    break;
                }
            
            case 3:
                cout << "Returning to main menu!" << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        
        };


}

void ubedmanagement()
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
        cout << "7. Save and Exit\n";

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
                saveBeds(filename);
                cout << "Changes saved. Exiting Bed Management." << endl;
                return;

            default:
                cout << "Invalid choice. Please try again!" << endl;
        }

    }
}

void umedicinesection()
{
       medicine m;
       int ch;

       cout<<endl;
       cout<<"1.Calculte Total bill"<<endl;
       cout<<"2.Go to Main Menu"<<endl;

       cout<<"Enter your choice:";
       cin>>ch;

       switch(ch)
       {
              case 1:
                    m.tbill();
                    umedicinesection();
                    break;

              case 2:
                    cout<<"Switching to main menu!!!......"<<endl;
                    break;

              default:
                    cout<<"Invalid choice!!!"<<endl;
                    cout<<"Enter again:";
                    cin>>ch;

       }
}

void emergencyward()
{
     EmergencyWard wardManager("emergency.txt");
     wardManager.manageEmergencyBeds();
}

//admincanteensection
int acanteensection()
{
    Canteen canteen;
    canteen.loadMenuFromFile("menu.txt");

    while (true) 
    {
        cout << "\n===== Canteen Management System =====\n";
        cout << "1. Display Menu\n";
        cout << "2. Add Menu Item\n";
        cout << "3. Place Order\n";
        cout << "4. Display Revenue\n";
        cout << "5. Display Orders\n";
        cout << "6. Save Menu and Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                canteen.displayMenu();
                break;

            case 2:
                canteen.addMenuItem();
                break;

            case 3:
                canteen.placeOrder();
                break;

            case 4:
                canteen.displayRevenue();
                break;

            case 5:
                canteen.displayOrders();
                break;

            case 6:
                canteen.saveMenuToFile("menu.txt");
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";

        }
    }
}

// Admin menu
void adminMenu() 
{
    setColor(9); // Blue color for admin menu
    cout << "\nWelcome Admin! Here are your options:" << endl;
    setColor(7); // Reset color to default

    amenu:
    cout<<endl;
    cout<<"--------------------------"<<endl;
    cout<<"| Welcome to Admin Section|"<<endl;
    cout<<"--------------------------"<<endl;
    cout<<endl;
    cout << "1.Doctor Management" << endl;
    cout << "2.Patient Management" << endl;
    cout << "3.Medicine Section" << endl;
    cout << "4.Bed Management" << endl;
    cout << "5.Advanced Features\n";
    cout << "6.Emergency ward" <<endl;
    cout << "7.Canteen section" << endl;
    cout << "8. Exit" << endl;

    int choice;
    cout<<"Enter your chocie:";
    cin >> choice;

    switch (choice) 
    {
        case 1:
            adoctormanagement();
            goto amenu;
            break;

        case 2:
            apatientmanagement();
            goto amenu;
            break;

        case 3:
            amedicinesection();
            goto amenu;
            break;

        case 4:
            abedmanagement();
            goto amenu;
            break;

        case 5:
            aadvancedFeatures();
            goto amenu;
            break;

        case 6:
            emergencyward();
            goto amenu;
            break;

        case 7:
           acanteensection();
            goto amenu;
            break;    

        case 8:
            cout << "Exiting Admin Menu." << endl;
            return;

        default:
            cout << "Invalid choice. Try again!" << endl;

    }

}

//feedback
struct Feedback 
{
    int feedbackID;        // Unique feedback ID
    string name;           // Name of the person giving feedback
    int rating;            // Experience rating (e.g., 1 to 5)
    string comments;       // Additional comments
    string suggestions;    // Suggestions for improvement
};
vector<Feedback> feedbackList;

 // Helper to generate unique feedback ID
int generateFeedbackID() 
{
    return feedbackList.empty() ? 1 : feedbackList.back().feedbackID + 1;
}

// Load feedback from file
void loadFeedback(const string& filename) 
{
    ifstream file(filename);
    if (!file) 
    {
        cerr << "Error: Unable to open the file: " << filename << endl;
        return;
    }

    feedbackList.clear();

    int feedbackID, rating;
    string name, comments, suggestions;

    while (file >> feedbackID >> rating) {
        file.ignore();
        getline(file, name);
        getline(file, comments);
        getline(file, suggestions);

        feedbackList.push_back({feedbackID, name, rating, comments, suggestions});
    }

    file.close();
    cout << "Feedback records loaded successfully from " << filename << endl;
}

    // Save feedback to file
void saveFeedback(const string& filename) {
    ofstream file(filename, ios::app); // Append mode

    if (!file) 
    {
        cerr << "Error: Unable to open the file: " << filename << endl;
        return;
    }
    for (const auto& feedback : feedbackList) 
    {
        file << feedback.feedbackID << " " << feedback.rating << "\n"
            << feedback.name << "\n"
            << feedback.comments << "\n"
            << feedback.suggestions << "\n";
    }

    file.close();
    cout << "Feedback records saved successfully to " << filename << endl;
}

    // Add a new feedback record
void addFeedback()
{
    Feedback newFeedback;
    newFeedback.feedbackID = generateFeedbackID();

    cout << "\nEnter your name: ";
    cin.ignore();
    getline(cin, newFeedback.name);

    cout << "Rate your experience (1 to 5): ";
    while (!(cin >> newFeedback.rating) || newFeedback.rating < 1 || newFeedback.rating > 5) 
    {
        cout << "Invalid input! Please enter a rating between 1 and 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    cout << "Enter your comments: ";
    getline(cin, newFeedback.comments);

    cout << "Enter any suggestions for improvement: ";
    getline(cin, newFeedback.suggestions);

    feedbackList.push_back(newFeedback);
    cout << "Thank you for your feedback!" << endl;
}

    // Display all feedback records
void displayFeedback() 
{
    if (feedbackList.empty()) 
    {
        cout << "\nNo feedback records available." << endl;
        return;
    }

    cout << "\nFeedback Records:\n";
    cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Rating"
             << setw(30) << "Comments" << setw(30) << "Suggestions" << endl;
    cout << string(100, '-') << endl;

    for (const auto& feedback : feedbackList) 
    {
        cout << setw(10) << feedback.feedbackID
            << setw(20) << feedback.name
            << setw(10) << feedback.rating
            << setw(30) << feedback.comments
            << setw(30) << feedback.suggestions << endl;
    }
}

    // Search feedback by ID
void searchFeedbackByID()
{
    int id;
    cout << "\nEnter Feedback ID to search: ";
    cin >> id;

    bool found = false;
    for (const auto& feedback : feedbackList) 
    {
        if (feedback.feedbackID == id) 
        {
            cout << "\nFeedback Details:\n";
            cout << "ID: " << feedback.feedbackID << "\n"
                    << "Name: " << feedback.name << "\n"
                    << "Rating: " << feedback.rating << "\n"
                    << "Comments: " << feedback.comments << "\n"
                    << "Suggestions: " << feedback.suggestions << endl;
            found = true;
            break;
        }
    }

    if (!found) 
    {
        cout << "No feedback found with ID: " << id << endl;
    }
}

    // Analyze average rating
void analyzeAverageRating() 
{
    if (feedbackList.empty()) 
    {
        cout << "\nNo feedback available to analyze." << endl;
        return;
    }

    int totalRating = 0;
    for (const auto& feedback : feedbackList) 
    {
        totalRating += feedback.rating;
    }

    double averageRating = static_cast<double>(totalRating) / feedbackList.size();
    cout << "\nAverage Experience Rating: " << fixed << setprecision(2) << averageRating << endl;
}

// Delete feedback by ID
void deleteFeedback() 
{
    int id;
    cout << "\nEnter Feedback ID to delete: ";
    cin >> id;

    auto it = remove_if(feedbackList.begin(), feedbackList.end(),
                            [id](const Feedback& fb) { return fb.feedbackID == id; });

    if (it != feedbackList.end())
    {
        feedbackList.erase(it, feedbackList.end());
        cout << "Feedback with ID " << id << " has been deleted." << endl;
    }
    else 
    {
        cout << "No feedback found with ID: " << id << endl;
    }
}

    // Edit feedback by ID
void editFeedback()
{
    int id;
    cout << "\nEnter Feedback ID to edit: ";
    cin >> id;

    for (auto& feedback : feedbackList) 
    {
        if (feedback.feedbackID == id) 
        {
            cout << "Editing Feedback (ID: " << id << ")\n";

            cout << "Current Name: " << feedback.name << "\nEnter new name (or press Enter to keep the same): ";
            cin.ignore();
            string newName;
            getline(cin, newName);
            if (!newName.empty()) feedback.name = newName;

            cout << "Current Rating: " << feedback.rating << "\nEnter new rating (1-5, or 0 to keep the same): ";
            int newRating;
            cin >> newRating;
            if (newRating >= 1 && newRating <= 5) feedback.rating = newRating;

            cin.ignore();
            cout << "Current Comments: " << feedback.comments << "\nEnter new comments (or press Enter to keep the same): ";
            string newComments;
            getline(cin, newComments);
            if (!newComments.empty()) feedback.comments = newComments;

            cout << "Current Suggestions: " << feedback.suggestions << "\nEnter new suggestions (or press Enter to keep the same): ";
            string newSuggestions;
            getline(cin, newSuggestions);
            if (!newSuggestions.empty()) feedback.suggestions = newSuggestions;

            cout << "Feedback updated successfully!" << endl;
            return;
        }
    }

    cout << "No feedback found with ID: " << id << endl;
}

void filterFeedbackByRating() 
{
    int rating;
    cout << "\nEnter rating to filter feedback (1 to 5): ";
    cin >> rating;

    if (rating < 1 || rating > 5) 
    {
        cout << "Invalid rating. Please enter a value between 1 and 5." << endl;
        return;
    }

    cout << "\nFeedback with Rating " << rating << ":\n";
    cout << setw(10) << "ID" << setw(20) << "Name" << setw(30) << "Comments" << setw(30) << "Suggestions" << endl;
    cout << string(100, '-') << endl;

    for (const auto& feedback : feedbackList) 
    {
        if (feedback.rating == rating) 
        {
            cout << setw(10) << feedback.feedbackID
                << setw(20) << feedback.name
                << setw(30) << feedback.comments
                << setw(30) << feedback.suggestions << endl;
        }
    }
}

    // View feedback statistics
void viewFeedbackStats() 
{
    if (feedbackList.empty()) 
    {
        cout << "\nNo feedback available for statistics." << endl;
        return;
    }

    int highest = numeric_limits<int>::min();
    int lowest = numeric_limits<int>::max();

    for (const auto& feedback : feedbackList) 
    {
        highest = max(highest, feedback.rating);
        lowest = min(lowest, feedback.rating);
    }

    cout << "\nFeedback Statistics:\n";
    cout << "Highest Rating: " << highest << "\nLowest Rating: " << lowest << endl;
}

//
int ufeedbackManagement()
{
    FeedbackManager feedbackManager;
    const string filename = "feedback.txt";
    feedbackManager.loadFeedback(filename);  // Load existing feedback records from file

    int choice;
    while (true) 
    {
        cout << "\n--- Hospital Feedback Management ---\n";
        cout << "1. Add Feedback\n";
        cout << "2. View All Feedback\n";
        cout << "3. Search Feedback by ID\n";
        cout << "4. Analyze Average Rating\n";
        cout << "5. View Feedback Statistics\n";
        cout << "6. Filter Feedback by Rating\n";
        cout << "7. Edit Feedback by ID\n";
        cout << "8. Delete Feedback by ID\n";
        cout << "9. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                feedbackManager.addFeedback();
                break;

            case 2:
                feedbackManager.displayFeedback();
                break;

            case 3:
                feedbackManager.searchFeedbackByID();
                break;

            case 4:
                feedbackManager.analyzeAverageRating();
                break;

            case 5:
                feedbackManager.viewFeedbackStats();
                break;

            case 6:
                feedbackManager.filterFeedbackByRating();
                break;

            case 7:
                feedbackManager.editFeedback();
                break;

            case 8:
                feedbackManager.deleteFeedback();
                break;

            case 9:
                feedbackManager.saveFeedback(filename);
                cout << "Thank you for managing feedback. Exiting now." << endl;
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

}

//usercanteensection
int ucanteensection()
{
    Canteen canteen;
    canteen.loadMenuFromFile("menu.txt");

    while (true) 
    {
        cout << "\n===== Canteen Management System =====\n";
        cout << "1. Display Menu\n";
        cout << "2. Add Menu Item\n";
        cout << "3. Place Order\n";
        cout << "4. Display Revenue\n";
        cout << "5. Display Orders\n";
        cout << "6. Save Menu and Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                canteen.displayMenu();
                break;
            case 2:
                canteen.addMenuItem();
                break;
            case 3:
                canteen.placeOrder();
                break;
            case 4:
                canteen.displayRevenue();
                break;
            case 5:
                canteen.displayOrders();
                break;
            case 6:
                canteen.saveMenuToFile("menu.txt");
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }

    }
}

//user menu
void userMenu() 
{
    setColor(6); // Cyan color for user menu
    cout << "\nWelcome User! Here are your options:" << endl;

    setColor(7); // Reset color to default

    umenu:
    cout<<endl<<endl;

    cout<<"--------------------------"<<endl;
    cout<<"| Welcome to User Section|"<<endl;
    cout<<"--------------------------"<<endl;

    cout<<endl<<endl;
    cout << "1.Patient Management" << endl;
    cout << "2.Doctor Management" << endl;
    cout << "3.Schedule a appointment" << endl;
    cout << "4.Find shortest route" << endl;
    cout << "5.Medicine Section" << endl;
    cout << "6.Bed Management" << endl;
    cout << "7.Emergency ward" << endl;
    cout << "8.Feedback Section" << endl;
    cout << "9.Canteen Section" << endl;
    cout << "10. Exit" << endl;

    int choice;
    cout<<"Enter your choice:";

    cin >> choice;

    switch (choice) 
    {
        case 1:
            upatientmanagement();
            goto umenu;
            break;

        case 2:
            udoctormanagement();
            goto umenu;
            break;

        case 3:
            appointmentbooking();
            goto umenu;
            break;

        case 4:
            locationManagement();
            goto umenu;
            break;

        case 5:
            umedicinesection();
            goto umenu;
            break;
        
        case 6:
            ubedmanagement();
            goto umenu;
            break;

        case 7:
            emergencyward();
            goto umenu;
            break; 

        case 8:
            ufeedbackManagement();
            goto umenu;
            break; 

        case 9:
            ucanteensection();
            goto umenu;
            break;

        case 10:
            cout << "Exiting User Menu." << endl;
            return;

        default:
            cout << "Invalid choice. Try again!" << endl;

    }

}

// Login system menu
void loginSystem() 
{
    int choice;

    while (true) 
    {
        setColor(11); // Light blue color for menu
        cout<<endl;

        cout << "\nLogin System:" << endl;
        cout<<endl;

        setColor(6); // yellow color
        cout << "1. Admin Login" << endl;
        cout << "2. User Login" << endl;
        cout << "3. Admin First-Time Sign-In" << endl;
        cout << "4. User First-Time Sign-In" << endl;
        cout << "5. Forgot Password" << endl;
        cout << "6. Exit" << endl;

        setColor(7);//Reset color to default
        cout << "Enter your choice: ";
        cin >> choice;

        string username, password;
        switch (choice) 
        {
            case 1:
                cout << "Enter Admin Username: ";
                cin >> username;

                cout << "Enter Admin Password: ";
                password = readPassword();

                if (validateLogin("login.txt", username, password)) 
                {
                    adminMenu();
                } 
                else 
                {
                    setColor(12); // Red color for error

                    cout << "Invalid Admin credentials. Try again!" << endl;
                    setColor(7); // Reset color to default
                }
                break;

            case 2:
                cout << "Enter User Username: ";
                cin >> username;

                cout << "Enter User Password: ";
                password = readPassword();

                if (validateLogin("signin.txt", username, password)) 
                {
                    userMenu();
                } 

                else 
                {
                    setColor(12); // Red color for error

                    cout << "Invalid User credentials. Try again!" << endl;
                    setColor(7); // Reset color to default
                }
                break;

            case 3:
                firstTimeSignIn("login.txt");
                break;

            case 4:
                firstTimeSignIn("signin.txt");
                break;

            case 5: 
            {
                cout << "Forgot Password for:" << endl;
                cout << "1. Admin" << endl;
                cout << "2. User" << endl;

                cout << "Enter your choice: ";
                int subChoice;
                cin >> subChoice;

                if (subChoice == 1) 
                {
                    forgotPassword("login.txt");
                } 

                else if (subChoice == 2) 
                {
                    forgotPassword("signin.txt");
                } 
                
                else 
                {
                    setColor(12); // Red color for error
                    cout << "Invalid choice. Try again!" << endl;
                    setColor(7); // Reset color to default
                }
                break;
            }

            case 6:
                setColor(9); // Blue color for exit

                cout << "Exiting the system. Goodbye!" << endl;

                setColor(7); // Reset color to default
                return;

            default:
                setColor(12); // Red color for error
                cout << "Invalid choice. Try again!" << endl;
                setColor(7); // Reset color to default

        }

    }

}
int main() 
{
    loginSystem();
    return 0;
}
