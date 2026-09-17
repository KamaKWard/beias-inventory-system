// include statements
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
//THE ITEM DATA IS HERE -8a
// item structure
struct Item {
    string itemName;
    int quantity;
};
// map to link itemCode with Item
//HashMap Index moved out of int main
//this contains the true values of the inventory
map<int, Item> inventory = {
    {1, {"Uniform", 27}},
    {2, {"Pants", 40}},
    {3, {"ID Lace", 30}},
    {4, {"LongSleeveShirtGigaBooBooWahWah", 11}},
    {5, {"PLUSH OF DOOM", 67}}
};
//makes Entry a readable name so we can just say
//vector<Entry> without expanding
//it into vector<pair<int,Item>>
using Entry = pair<int, Item>;
//makes a snapshot of the map into a vector
vector<Entry> toEntries(const map<int, Item> &m){
    return vector<Entry>(m.begin(),m.end());
}
//FUNCTIONS BELOW - 8a
// placeholder function to quick sort
void quickSort(vector<Entry>& items, int low, int high, int sortType) {
    if (low >= high)
        return;
 
    // Choose the last item as pivot
    Entry pivot = items[high];
 
    int i = low - 1;
 
    for (int j = low; j < high; j++)
    {
        bool shouldSwap = false;
 
        // Sort by Item Code
        if (sortType == 1)
        {
            shouldSwap = items[j].first < pivot.first;
        }
 
        // Sort by Item Name
        else if (sortType == 2)
        {
            shouldSwap = items[j].second.itemName < pivot.second.itemName;
        }
 
        // Sort by Quantity
        else if (sortType == 3)
        {
            shouldSwap = items[j].second.quantity < pivot.second.quantity;
        }
 
        if (shouldSwap)
        {
            i++;
            swap(items[i], items[j]);
        }
    }
 
    // Put pivot in correct position
    swap(items[i + 1], items[high]);
 
    int pivotIndex = i + 1;
 
    // Sort left side
    quickSort(items, low, pivotIndex - 1, sortType);
 
    // Sort right side
    quickSort(items, pivotIndex + 1, high, sortType);
}
// placeholder function to search
void binarySearch() {
    return;
}
//---------------------------------------------------------------------------------------------------------
//Displays
void printRow(int code, const Item&item) //dictates how items are listed
{
    cout << left<<"  0"<<code<<setw(8)<<" "
<< setw(40) << item.itemName
<< setw(10) << item.quantity << endl;
}
void printHeader() //header to be used on later menus
{
        cout << endl << "| ------------------ | Current Inventory | ------------------ |" << endl;
    cout << left << setw(8)<< "[Code]"<< setw(40) << "[Item Name]"<< setw(10) << "[Quantity]" << endl;
            cout << "| ----------------------------------------------------------- |" << endl;
}
void DefaultDisplay() //Display that shows when no sorting option is picked
{
            printHeader();
            for (const auto &entry : inventory) printRow(entry.first, entry.second);
            cout << "| ----------------------------------------------------------- |" << endl;
}
//--------------------------------------------------------------------------------------------------------
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
            {
                vector<Entry> items = toEntries(inventory);
 
                quickSort(items, 0, items.size() - 1, 1);
 
                printHeader();
 
                for (const auto& entry : items)
                    printRow(entry.first, entry.second);
 
                cout << "| ----------------------------------------------------------- |" << endl;
 
                break;
            }
            case 2://sort by Name
            {
                vector<Entry> items = toEntries(inventory);
 
                quickSort(items, 0, items.size() - 1, 2);
 
                printHeader();
 
                for (const auto& entry : items)
                    printRow(entry.first, entry.second);
 
                cout << "| ----------------------------------------------------------- |" << endl;
 
                break;
            }
            case 3: // sort by Quantity
            {
                vector<Entry> items = toEntries(inventory);
                quickSort(items, 0, items.size() - 1, 3);
                printHeader();
                for (const auto& entry : items)
                printRow(entry.first, entry.second);
                cout << "| ----------------------------------------------------------- |" << endl;
                break;
}
            case 4://Back to Main Menu
            return;
            case 0://Exit program
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
        cout<<"----------------------------"<<endl<<"|        BEIAS Menu        |"<<endl<<"----------------------------"<<endl;
        cout<<"|[1] -- Check Current Inventory"<<endl;
        cout<<"|[2] -- Add Item To Inventory"<<endl;
        cout<<"|[3] -- Search For An Item Within Inventory"<<endl;
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
