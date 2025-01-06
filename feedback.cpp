#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include<limits>
#include<algorithm>
using namespace std;

class FeedbackManager 
{
private:
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

public:
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

        while (file >> feedbackID >> rating) 
        {
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
    void saveFeedback(const string& filename) 
    {
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

                if (!newName.empty()) 
                {
                    feedback.name = newName;
                }

                cout << "Current Rating: " << feedback.rating << "\nEnter new rating (1-5, or 0 to keep the same): ";
                int newRating;
                cin >> newRating;

                if (newRating >= 1 && newRating <= 5) 
                {
                    feedback.rating = newRating;
                }

                cin.ignore();
                cout << "Current Comments: " << feedback.comments << "\nEnter new comments (or press Enter to keep the same): ";
                string newComments;
                getline(cin, newComments);
                
                if (!newComments.empty()) 
                {
                    feedback.comments = newComments;
                }

                cout << "Current Suggestions: " << feedback.suggestions << "\nEnter new suggestions (or press Enter to keep the same): ";
                string newSuggestions;
                getline(cin, newSuggestions);
                if (!newSuggestions.empty()) 
                {
                    feedback.suggestions = newSuggestions;
                }

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

};
// int main() 
//{
//     FeedbackManager feedbackManager;
//     const string filename = "feedback.txt";
//     feedbackManager.loadFeedback(filename);  // Load existing feedback records from file

//     int choice;
//     while (true) 
//     {
//         cout << "\n--- Hospital Feedback Management ---\n";
//
//         cout << "1. Add Feedback\n";
//         cout << "2. View All Feedback\n";
//         cout << "3. Search Feedback by ID\n";
//         cout << "4. Analyze Average Rating\n";
//         cout << "5. View Feedback Statistics\n";
//         cout << "6. Filter Feedback by Rating\n";
//         cout << "7. Edit Feedback by ID\n";
//         cout << "8. Delete Feedback by ID\n";
//         cout << "9. Save and Exit\n";
//         cout << "Enter your choice: ";
//         cin >> choice;

//         switch (choice) 
//          {
//             case 1:
//                 feedbackManager.addFeedback();
//                 break;

//             case 2:
//                 feedbackManager.displayFeedback();
//                 break;

//             case 3:
//                 feedbackManager.searchFeedbackByID();
//                 break;

//             case 4:
//                 feedbackManager.analyzeAverageRating();
//                 break;

//             case 5:
//                 feedbackManager.viewFeedbackStats();
//                 break;

//             case 6:
//                 feedbackManager.filterFeedbackByRating();
//                 break;

//             case 7:
//                 feedbackManager.editFeedback();
//                 break;

//             case 8:
//                 feedbackManager.deleteFeedback();
//                 break;

//             case 9:
//                 feedbackManager.saveFeedback(filename);
//                 cout << "Thank you for managing feedback. Exiting now." << endl;
//                 return 0;

//             default:
//                 cout << "Invalid choice! Please try again.\n";
//         }

//     }
// }
