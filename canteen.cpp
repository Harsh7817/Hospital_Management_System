#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

class MenuItem 
{
public:
    string name;
    double price;
    int stock;

    MenuItem(string name, double price, int stock)
        : name(name), price(price), stock(stock) {}

    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    void setPrice(double newPrice) { price = newPrice; }
    void setStock(int newStock) { stock = newStock; }

    void displayItem() const 
    {
        cout << left << setw(20) << name 
             << setw(10) << price 
             << setw(10) << stock << endl;
    }

    void saveToFile(ofstream& file) const 
    {
        file << name << "," << price << "," << stock << endl;
    }
};
class Order 
{
public:
    string customerName;
    map<string, int> orderedItems; // Item name and quantity
    double totalCost;

    Order(string customerName) : customerName(customerName), totalCost(0) {}

    void addItem(const string& itemName, int quantity, double itemPrice) 
    {
        orderedItems[itemName] += quantity;
        totalCost += quantity * itemPrice;
    }

    void displayOrder() const 
    {
        cout << "\nOrder for: " << customerName << "\n";
        cout << left << setw(20) << "Item Name" << setw(10) << "Quantity" << setw(10) << "Total" << endl;
        cout << string(40, '-') << endl;

        for (const auto& item : orderedItems) 
        {
            const string& itemName = item.first;
            int quantity = item.second;

            cout << left << setw(20) << itemName 
                 << setw(10) << quantity 
                 << setw(10) << quantity * totalCost / orderedItems.size() << endl;
        }

        cout << "\nTotal Cost: " << totalCost << " INR\n";
    }

    void saveOrderToFile(ofstream& file) const 
    {
        file << "Customer: " << customerName << endl;
        file << "Items:" << endl;

        for (const auto& item : orderedItems) {
            file << item.first << " x " << item.second << endl;
        }

        file << "Total Cost: " << totalCost << " INR" << endl;
        file << "-----------------------------" << endl;
    }

    double getTotalCost() const { return totalCost; }
};
class Canteen 
{
public:
    vector<MenuItem> menu;
    vector<Order> orders;

    // Helper to find menu item by name
    MenuItem* findMenuItem(const string& itemName) 
    {
        for (auto& item : menu) 
        {
            if (item.getName() == itemName) 
            {
                return &item;
            }
        }
        return nullptr;
    }

    // Load menu from file
    void loadMenuFromFile(const string& filename) 
    {
        ifstream file(filename);
        if (!file) 
        {
            cout << "No menu data found. Starting fresh...\n";
            return;
        }

        string name;
        double price;

        int stock;
        while (file >> ws, getline(file, name, ',')) 
        {
            file >> price;
            file.ignore(1, ',');
            file >> stock;
            menu.emplace_back(name, price, stock);
        }
        file.close();
        cout << "Menu loaded successfully!\n";
    }

    // Save menu to file
    void saveMenuToFile(const string& filename) const 
    {
        ofstream file(filename);
    
        for (const auto& item : menu) 
        {
            item.saveToFile(file);
        }
        file.close();
        cout << "Menu saved successfully!\n";
    }

    // Display menu
    void displayMenu() const 
    {
        if (menu.empty()) 
        {
            cout << "The menu is empty!\n";
            return;
        }

        cout << left << setw(20) << "Item Name" 
             << setw(10) << "Price" 
             << setw(10) << "Stock" << endl;
        cout << string(40, '-') << endl;
        for (const auto& item : menu) 
        {
            item.displayItem();
        }
    }

    // Add a new menu item
    void addMenuItem() 
    {
        string name;
        double price;
        int stock;

        cout << "Enter the name of the new item: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter the price: ";
        cin >> price;

        cout << "Enter the stock quantity: ";
        cin >> stock;

        menu.emplace_back(name, price, stock);
        cout << "New item added successfully!\n";
    }

    // Place an order
    void placeOrder() 
    {
        string customerName;
        cout << "Enter the customer's name: ";
        cin.ignore();
        getline(cin, customerName);

        Order order(customerName);
        string itemName;
        int quantity;

        while (true) 
        {
            cout << "\nEnter item name to order (or type 'done' to finish): ";
            getline(cin, itemName);

            if (itemName == "done") 
            {
                break;
            }

            MenuItem* item = findMenuItem(itemName);
            if (item) 
            {
                cout << "Enter quantity: ";
                cin >> quantity;
                cin.ignore();

                if (quantity <= item->getStock()) 
                {
                    item->setStock(item->getStock() - quantity);
                    order.addItem(itemName, quantity, item->getPrice());
                    cout << "Added to order successfully!\n";
                } 
                else 
                {
                    cout << "Not enough stock available for " << itemName << ".\n";
                }

            } 

            else 
            {
                cout << "Item not found in the menu.\n";
            }
        }

        orders.push_back(order);
        cout << "Order placed successfully!\n";
        order.displayOrder();
    }

    // Display total revenue
    void displayRevenue() const 
    {
        double totalRevenue = 0;
        for (const auto& order : orders) 
        {
            totalRevenue += order.getTotalCost();
        }
        cout << "\nTotal Revenue: " << totalRevenue << " INR\n";
    }

    void displayOrders() const 
    {
        cout << "\n===== Orders =====\n";
        for (const auto& order : orders) 
        {
            order.displayOrder();
        }
    }
};
// int main() 
//{
//     Canteen canteen;
//     canteen.loadMenuFromFile("menu.txt");
//     while (true) 
//     {
//         cout << "\n===== Canteen Management System =====\n";
//
//         cout << "1. Display Menu\n";
//         cout << "2. Add Menu Item\n";
//         cout << "3. Place Order\n";
//         cout << "4. Display Revenue\n";
//         cout << "5. Display Orders\n";
//         cout << "6. Save Menu and Exit\n";
//
//         int choice;
//         cout << "Enter your choice: ";
//         cin >> choice;
//         switch (choice) 
//         {
//             case 1:
//                 canteen.displayMenu();
//                 break;
//
//             case 2:
//                 canteen.addMenuItem();
//                 break;
//
//             case 3:
//                 canteen.placeOrder();
//                 break;
//
//             case 4:
//                 canteen.displayRevenue();
//                 break;
//
//             case 5:
//                 canteen.displayOrders();
//                 break;
//
//             case 6:
//                 canteen.saveMenuToFile("menu.txt");
//                 cout << "Exiting...\n";
//                 return 0;
//
//             default:
//                 cout << "Invalid choice! Please try again.\n";
//         }
//
//     }
//
// }
