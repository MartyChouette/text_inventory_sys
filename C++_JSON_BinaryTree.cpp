#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <algorithm>


using json = nlohmann::json;
using namespace std;

struct InventoryItem {
    int id;
    string name;
    int quantity;
    string description;
    string effect;

};



void add_item(vector<InventoryItem>& inventory);
void remove_item(vector<InventoryItem>& inventory);
void display_inventory(const vector<InventoryItem>& inventory);
void save_inventory(const vector<InventoryItem>& inventory, const string& filename);
void load_inventory(vector<InventoryItem>& inventory, const string& filename);

int main() {
    vector<InventoryItem> inventory;
    load_inventory(inventory, "inventory.json");

    int choice;

    do 
    {
        cout << "1. Add Item\n2. Remove Item\n3. Display Inventory\n4. Save and Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: add_item(inventory); 
            break;
        case 2: remove_item(inventory); 
            break;
        case 3: display_inventory(inventory); 
            break;
        case 4: save_inventory(inventory, "inventory.json"); 
            break;
        default: cout << "Invalid choice. Please try again.\n";
        }
    } 
    while (choice != 4);

    return 0;
}

void add_item(vector<InventoryItem>& inventory) {
    InventoryItem item;
    cout << "Enter item ID: ";
    cin >> item.id;
    cout << "Enter item name: ";
    cin >> item.name;
    cout << "Enter item quantity: ";
    cin >> item.quantity;
    cout << "Enter item description: ";
    cin >> item.description;
    //input if item number is of the affecting (something that interacts with external performers) performers 
    // an other characters, elements, stuff changing something
    cin >> item.effect;
    inventory.push_back(item);
}

void remove_item(vector<InventoryItem>& inventory) {
    int id;
    cout << "Enter item ID to remove: ";
    cin >> id;
    auto it = remove_if(inventory.begin(), inventory.end(), [id](const InventoryItem& item) {
        return item.id == id;
        });
    if (it != inventory.end()) {
        inventory.erase(it, inventory.end());
        cout << "Item removed.\n";
    }
    else {
        cout << "Item not found.\n";
    }
}

void display_inventory(const vector<InventoryItem>& inventory) {
    if (inventory.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }
    for (const auto& item : inventory) {
        cout << "ID: " << item.id << ", Name: " << item.name << ", Quantity: " << item.quantity << endl;
    }
}

void save_inventory(const vector<InventoryItem>& inventory, const string& filename) {
    ofstream ofs(filename);
    if (!ofs.is_open()) {
        cerr << "Could not open file for writing.\n";
        return;
    }

    json j;
    for (const auto& item : inventory) {
        j.push_back({ {"id", item.id}, {"name", item.name}, {"quantity", item.quantity} });
    }

    ofs << j.dump(4);
    ofs.close();
    cout << "Inventory saved to " << filename << endl;  // Debugging output
}

void load_inventory(vector<InventoryItem>& inventory, const string& filename) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cerr << "Could not open file for reading.\n";
        return;
    }

    json j;
    ifs >> j;

    for (const auto& item : j) {
        inventory.push_back({ item["id"], item["name"], item["quantity"] });
    }

    ifs.close();
    cout << "Inventory loaded from " << filename << endl;  // Debugging output
}
