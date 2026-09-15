// include statements
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>

//namespace std
using namespace std;

//value for user input
int MenuInput;
int CaseChoice;

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
    //HashMap Index
    inventory = {
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
        cout<<"|[0] -- Exit"<<endl;
        cout<<"Select: ";
        // user input
        cin>>MenuInput;
        
        // switch statement for user input
        switch (MenuInput)
        {
        
        case 1: // display inventory case
            cout << endl << "| ------------------ | Current Inventory | ------------------ |" << endl;
            cout << left << setw(8)<< "[Code]"
                 << setw(40) << "[Item Name]"
                 << setw(10) << "[Quantity]" << endl;
            cout << "| ----------------------------------------------------------- |" << endl;
            
            for (const auto &item : inventory) {
                cout << left<<"  0"<<item.first<<setw(8)<<" "
                    << setw(40) << item.second.itemName
                    << setw(10) << item.second.quantity << endl;
            }
            
            cout << "| ----------------------------------------------------------- |" << endl;
                while(CaseChoice!=4){
                cout<<"|[1] -- Sort By Item Code"<<endl;
                cout<<"|[2] -- Sort By Name"<<endl;
                cout<<"|[3] -- Sort By Quantity"<<endl;
                cout<<"|[4] -- Back To Main Menu"<<endl;
                cout<<"|[0] -- Exit Program"<<endl;
                cout<<"Choice: ";
                cin>> CaseChoice;
                    switch(CaseChoice){
                    case 1://sort by Item code
                    break;
                    
                    case 2://sort by Name
                    break;
                    
                    case 3://sort by Quantity
                    break;
                    
                    case 4://Back to Main Menu
                    break;
                    
                    case 0://Exit program
                    return 0;
                    }
                }
        
        case 2: // adding item to inventory (placeholder)
            cout << "";
            break;

        
        case 3: // searching for a certain item in inventory (placeholder)
            cout << "";
            break;

        
        case 0: // exit case
            cout<<endl<<"[ Exiting BEIAS.. | Thank you for your usage! ] "<<endl;
            return 0;
            break;

        
        default: // the Default Case
            break;
        }


    } 

    return 0;
}
