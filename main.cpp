
// include statements
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>

//namespace std
using namespace std;

//User Input
int MenuInput;
char CaseChoice;

// item structure
struct Item {
    string itemName;
    int quantity;
};

// map to link itemCode with Item
map<int, Item> inventory;

// placeholder function to quick sort
void quickSort() {
    return;
}

// placeholder function to search
void binarySearch() {
    return;
}

// main method
int main()
{   
    //hashmap, [ItemCode, Name, quantity]
    inventory= {
    { 1, {"Uniform", 27}},
    { 2, {"Pants", 40}},
    { 3, {"ID Lace", 30}},
    { 4, {"LongSleeveShirtGigaBooBooWahWah", 11}},
    { 5, {"PLUSH OF DOOM", 67}}
    };
    // while loop that encompasses entire program
    while (true) {
        cout<<"----------------------------"<<endl<<"|        BEIAS Menu        |"<<endl<<"----------------------------"<<endl;
        cout<<"|[1] -- Check Current Inventory"<<endl;
        cout<<"|[2] -- Add Item To Inventory"<<endl;
        cout<<"|[3] -- Search For An Item Within Inventory"<<endl;
        cout<<"|[0] -- Exit"<<endl<<endl;

        // user input
        cin>>MenuInput;

        // switch statement for user input
        switch (MenuInput)
        {

        // display inventory case
        case 1:
            cout << endl << "| ------------------ | Current Inventory | ------------------ |" << endl;
            cout << left << setw(8)  << "[Code]"
                 << setw(40) << "[Item Name]"
                 << setw(10) << "[Quantity]" << endl;
            cout << "| ----------------------------------------------------------- |" << endl;
            
            /* const, auto, and & are all keywords to alter how the for loop goes thru the data structure, item : inventory is the range in which it will function */
            for (const auto &item : inventory) {
                cout << left << setw(8) << item.first
                    << setw(40) << item.second.itemName
                    << setw(10) << item.second.quantity << endl;
            }
            
            cout << "| ----------------------------------------------------------- |" << endl << endl;
            cout << "Continue to Menu? (y/n): ";
            cin >> CaseChoice;
            if(CaseChoice=='y'){
                cout<<"\n";break;}
            else{
                return 0;}

        // adding item to inventory (placeholder)
        case 2:
            cout << "";
            break;

        // searching for a certain item in inventory (placeholder)
        case 3:
            cout << "";
            break;

        // exit case
        case 0:
            cout<<endl<<"[ Exiting BEIAS.. | Thank you for your usage! ] "<<endl;
            return 0;
            break;

        // the Default Case
        default:
            break;
        }


    } 

    // return 0
    return 0;
}
