
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

bool programEnd = false;
int userInput;

struct Item {
    string itemName;
    int quantity;
};

unordered_map<string, Item> inventory;

void quickSort() {
    return;
}

void binarySearch() {
    return;
}

int main()
{
    inventory["01"] = {"Uniform", 27};
    inventory["02"] = {"Pants", 40};
    inventory["03"] = {"ID Lace", 30};
    inventory["04"] = {"LongSleeveShirtGigaBooBooWahWah", 11};

    while (programEnd != true) {
        cout<<"----------------------------"<<endl<<"|        BEIAS Menu        |"<<endl<<"----------------------------"<<endl;
        cout<<"|[1] -- Check Current Inventory"<<endl;
        cout<<"|[2] -- Add Item To Inventory"<<endl;
        cout<<"|[3] -- Search For An Item Within Inventory"<<endl;
        cout<<"|[0] -- Exit"<<endl<<endl;

        cin>>userInput;

        switch (userInput)
        {
        case 1:
            cout << endl << "| ------------------ | Current Inventory | ------------------ |" << endl;
            cout << left << setw(8)  << "[Code]"
                 << setw(40) << "[Item Name]"
                 << setw(10) << "[Quantity]" << endl;
            cout << "| ----------------------------------------------------------- |" << endl;
            
            for (const auto &item : inventory) {
                cout << left << setw(8) << item.first
                    << setw(40) << item.second.itemName
                    << setw(10) << item.second.quantity << endl;
            }
            
            cout << "| ----------------------------------------------------------- |" << endl << endl;
            break;

        case 2:
            cout << "";
            break;
        
        case 3:
            cout << "";
            break;
        
        case 0:
            cout<<endl<<"[ Exiting BEIAS.. | Thank you for your usage! ] "<<endl;
            programEnd = true;
            break;
        
        default:
            break;
        }


    } 
    

    return 0;
}