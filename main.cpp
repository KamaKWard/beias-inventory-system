// include statements
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
//-------------------------------------------------------------
//Text Style Implementation
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define BG_GRAY "\033[47m"
#define BLACK   "\033[30m"
#define GREEN   "\033[32m"
//-------------------------------------------------------------
#ifdef _WIN32 //activates ANSI codes if the unit doesnt natively have it activated
#include <windows.h>
void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#else
void enableANSI() {} // Not needed on Linux/macOS
#endif
//-------------------------------------------------------------


// DATA STRUCTURES for Item and Package -Kama
// item structure
struct Item {
    string itemName;
    int quantity;
};

//package structure
struct Package {
    int packageID;
    vector<Item> items;
};

/* map to link itemCode with Item
HashMap Index moved out of int main
this contains the true values of the inventory */
map<int, Item> inventory = {
    {1, {"Uniform", 27}},
    {2, {"Pants", 40}},
    {3, {"ID Lace", 30}},
    {4, {"LongSleeveShirtGigaBooBooWahWah", 11}},
    {5, {"PLUSH OF DOOM", 67}}
};

/* makes Entry a readable name so we can just say 
vector<Entry> without expanding 
it into vector<pair<int,Item>> */
using Entry = pair<int, Item>;

//makes a snapshot of the map into a vector
vector<Entry> toEntries(const map<int, Item> &m){
    return vector<Entry>(m.begin(),m.end());
}

//FUNCTIONS BELOW - 8a
// placeholder function to quick sort
void quickSort() {
    return;
}

// placeholder function to search
//I think this is good
void binarySearch() {
    // Make a temporary vector from the inventory map
    vector<Entry> arr = toEntries(inventory);
    int size = arr.size();
    int target;
    cout << endl;
    cout << "[Enter Item Code to search]: ";
    cin >> target;
    if (cin.fail()) { // please optimize later
        cin.clear();// Clear the error state
        cin.ignore(1000, '\n');// Remove invalid input
    cout << endl;
        cout << "[Invalid Code] (Please Retry With A Valid ID)" << endl<<endl;
        return;
    }
    int left = 0;
    int right = size - 1;
    int resultIndex = -1;
    while (left <= right) { //shoutout to old binary code
        int mid = left + (right - left) / 2;
        // Search using the Item Code
        if (arr[mid].first == target) {
            resultIndex = mid;
            break;
        }
        if (arr[mid].first < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    // Display result
    if (resultIndex != -1) {
        cout << endl;
        cout << "[Item Found]" << endl;
        cout << "Item Code : " << arr[resultIndex].first << endl;
        cout << "Item Name : " << arr[resultIndex].second.itemName << endl;
        cout << "Quantity  : " << arr[resultIndex].second.quantity << endl<<endl;

    }
    else {
        cout <<RED<< "[Item Code " << target
             << " not found in the inventory.]" <<RESET<< endl<<endl;
    }
}

//---------------------------------------------------------------------------------------------------------
//Displays
void printRow(int code, const Item&item) //dictates how items are listed
{ 
    cout << left<<"\033[1G"<<BLUE<<"  0"<<code<<RESET
        << "\033[12G" <<item.itemName<<RESET
        << "\033[52G" <<BLUE<< item.quantity << RESET << endl;
}

void printHeader() //header to be used on later menus
{
        cout << endl << BOLD<< "| ------------------"<<GREEN<<"| Current Inventory | "<<RESET<<"------------------ |"<< endl;
        cout << left <<"\033[1G"<< "[Code]"<<"\033[10G"<< "[Item Name]"<<"\033[48G"<< "[Quantity]"<< endl;
        cout << "| ----------------------------------------------------------- |"<<RESET<< endl;
}
void DefaultDisplay() //Display that shows when no sorting option is picked
{
            printHeader();
            for (const auto &entry : inventory) printRow(entry.first, entry.second);
            cout << BOLD <<"| ----------------------------------------------------------- |"<< RESET << endl;
}
//--------------------------------------------------------------------------------------------------------

//function for inserting items into the inventory map
void insertItem() {
    int tempItemCode;
    string tempItemName;
    int tempQuantity;

    cout<<endl<<"[Please input the item code, name of item and quantity.]"<<endl<<"[Item Code (0-99)]: ";
    cin>>tempItemCode;
    cin.ignore();
    
    cout<<endl<<"Item Name: ";
    getline(cin, tempItemName);

    cout<<endl<<"Quantity: ";
    cin>>tempQuantity;

    inventory[tempItemCode] = {tempItemName, tempQuantity};
}

//Function that displays a menu for available sorts upon opening Inventory
void SortMenu(){
    int CaseChoice;
    while(true){
        cout<<"|[1] -- Sort By Item Code"<<endl;
        cout<<"|[2] -- Sort By Name"<<endl;
        cout<<"|[3] -- Sort By Quantity"<<endl;
        cout<<"|[4] -- Back To Main Menu"<<endl;
        cout<<"|[0] -- Exit Program"<<endl;
        cout<<"Choice: ";
        cin>> CaseChoice;
        switch(CaseChoice){
            case 1://sort by Item code
            cout<<endl;break;
                    
            case 2://sort by Name
            cout<<endl;break;
                    
            case 3://sort by Quantity
            cout<<endl;break;
                    
            case 4://Back to Main Menu
            cout<<endl;return;
                    
            case 0://Exit program
            cout<<endl<<"[ Exiting BEIAS.. | Thank you for your usage! ] "<<endl;
            exit(0);
        }
    }
}
// main method
int main()
{   
    int MenuInput;

    // while loop that encompasses entire program
        while (true) {
        cout<<BOLD<<"----------------------------"<<endl<<GREEN<<"|        BEIAS Menu        |"<<RESET<<endl<<"----------------------------"<<endl;
        cout<<"|[1] -- Check Current Inventory"<<endl;
        cout<<"|[2] -- Add Item To Inventory"<<endl;
        cout<<"|[3] -- Search For An Item Within Inventory"<<endl;
        cout<<"|[4] -- Check Delivery Queue"<<endl;
        cout<<"|[5] -- Package Management (Returns / Deliveries)"<<endl;
        cout<<"|[0] -- Exit"<<endl;
        cout<<"Select: ";
        // user input
        cin>>MenuInput;     
        // switch statement for userinput
        switch (MenuInput)
        {
        
        case 1: // display inventory case
            DefaultDisplay();
            SortMenu();
            break;
           
        case 2: // adding item to inventory (placeholder)
            insertItem();
            break;
            
        // input access to binarysearch
        case 3: // searching for a certain item in inventory (placeholder)
            binarySearch();
            break;
        case 4: // delivery queue checking and stuff (placeholder)
            cout << "";
            break;
        case 5: // managing package returns and deliveries!! (placeholder)
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
