// include statements
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <iomanip>
#include <sstream>   //EDITED FOR QUEUE DATE SORTING
#include <ctime>     //EDITED FOR QUEUE DATE SORTING
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

/* makes Entry a readable name so we can just say 
vector<Entry> without expanding 
it into vector<pair<int,Item>> */
using Entry = pair<int, Item>;

//package structure
struct Package {
    int packageID;
    vector<Item> items;
};

// delivery structure
// each item is an Entry (item code + Item) so we know where to put it in the inventory
struct Delivery {
    int deliveryID;
    string dateOfArrival;
    vector<Entry> items;
};

queue<Delivery> deliveryQueue;
int nextDeliveryID = 1;

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

//makes a snapshot of the map into a vector
vector<Entry> toEntries(const map<int, Item> &m){
    return vector<Entry>(m.begin(),m.end());
}

//declaring them early so i dont go insane -kama
void loopThroughQueue();
void addToQueue();
void removeFromQueue();

// placeholder function to quick sort
void quickSort(vector<Entry>& items, int low, int high, int sortType) {
    if (low >= high)
        return;
 
    // choose last item as pivot
    Entry pivot = items[high];
    int i = low - 1;
 
    for (int j = low; j < high; j++)
    {
        bool shouldSwap = false;
        // sort by item code
        if (sortType == 1)
        {
            shouldSwap = items[j].first < pivot.first;
        }
        // sort by item name
        else if (sortType == 2)
        {
            shouldSwap = items[j].second.itemName < pivot.second.itemName;
        }
        // sort by quantity
        else if (sortType == 3)
        {
            shouldSwap = items[j].second.quantity < pivot.second.quantity;
        }
        if (shouldSwap)
        {
            i++;
            Entry temp = items[i];
            items[i] = items[j];
            items[j] = temp;
        }
    }

    // putting pivot in position
    Entry temp2 = items[i + 1];
    items[i + 1] = items[high];
    items[high] = temp2;
    int pivotIndex = i + 1;
    
    // sorting left side
    quickSort(items, low, pivotIndex - 1, sortType);
    // sorting right side
    quickSort(items, pivotIndex + 1, high, sortType);
}
//THIS IS FOR DATE sstream and ctime [[PLEASE CHECK BEFORE ADDING STUFF!!!!]]
bool normalizeDate(const string& input, string& normalized) { //EDITED FOR QUEUE DATE SORTING
    int year, month, day;
    char dash1, dash2;
    string extra;

    istringstream dateStream(input);

    if (!(dateStream >> year >> dash1 >> month >> dash2 >> day) ||
        dash1 != '-' || dash2 != '-' ||
        (dateStream >> extra)) {
        return false;
    }

    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
    tm dateValue = {};
    dateValue.tm_year = year - 1900;
    dateValue.tm_mon = month - 1;
    dateValue.tm_mday = day;
    dateValue.tm_hour = 12;
    mktime(&dateValue);
    // Reject invalid calendar dates such as February 30.
    if (dateValue.tm_year != year - 1900 ||
        dateValue.tm_mon != month - 1 ||
        dateValue.tm_mday != day) {
        return false;
    }
    ostringstream output;
    output << setfill('0')
           << setw(4) << year << '-'
           << setw(2) << month << '-'
           << setw(2) << day;
    normalized = output.str();
    return true;
}
//---------------------------------------------------------------------------------------------------------
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
        cout <<RED<< "[Invalid Code] (Please Retry With A Valid ID)" <<RESET<< endl<<endl;
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
void sortQueueMenu() { //ITS RUDIMENTARY BUT ILL COMBINE THEM SOON
    int sortChoice;

    cout << endl;
    cout << "|[1] -- Sort by Oldest" << endl;
    cout << "|[2] -- Sort by Newest" << endl;
    cout << "Choice: ";

    cin >> sortChoice;

    if (cin.fail() || (sortChoice != 1 && sortChoice != 2)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << RED << "[Invalid choice]" << RESET << endl << endl;
        return;
    }

    vector<Delivery> sortedDeliveries; //EDITED FOR BINARY SEARCH
    queue<Delivery> temp = deliveryQueue;

    while (!temp.empty()) {
        Delivery current = temp.front();
        temp.pop();

        int left = 0; //EDITED FOR BINARY SEARCH
        int right = static_cast<int>(sortedDeliveries.size()) - 1;
        int position = 0;

        // Binary search for the delivery's insertion position.
        while (left <= right) { //EDITED FOR BINARY SEARCH
            int mid = left + (right - left) / 2;

            if (sortChoice == 1) {
                // Oldest first: ascending date order.
                if (sortedDeliveries[mid].dateOfArrival
                    <= current.dateOfArrival) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            } else {
                // Newest first: descending date order.
                if (sortedDeliveries[mid].dateOfArrival
                    >= current.dateOfArrival) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        position = left;

        // Insert the delivery at its calculated position.
        sortedDeliveries.insert(
            sortedDeliveries.begin() + position, current
        ); //EDITED FOR BINARY SEARCH
    }

    // Replace the actual queue with the sorted deliveries.
    deliveryQueue = queue<Delivery>(); //EDITED FOR BINARY SEARCH

    for (const Delivery& d : sortedDeliveries) {
        deliveryQueue.push(d);
    }

    cout << GREEN
         << (sortChoice == 1
             ? "[Queue sorted by oldest arrival date]"
             : "[Queue sorted by newest arrival date]")
         << RESET << endl << endl;
}
//---------------------------------------------------------------------------------------------------------

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
            cout<<endl;return;
            
            case 0://Exit program
            cout<<endl<<"[ Exiting BEIAS.. | Thank you for your usage! ] "<<endl;
            exit(0);
        }
    }
}

// idk how to display stuff
void displayQueue() {
    cout << endl << BOLD<< "| ------------------"<<GREEN<<"| Current Queue | "<<RESET<<"------------------ |"<< endl;
    cout << left <<"\033[1G"<< "[Delivery ID]"<<"\033[17G"<< "[Date Of Arrival]"<<"\033[38G"<< "[Items]"<< endl;
    cout << "| ----------------------------------------------------------- |"<<RESET<< endl;
    loopThroughQueue();
    cout << BOLD <<"| ----------------------------------------------------------- |"<< RESET << endl;
}

// u guys can remove this if u want -kama
void initializeQueue() {

    // initializes d1
    Delivery d1;
    d1.deliveryID = nextDeliveryID++;
    d1.dateOfArrival = "2026-10-11";
    d1.items.push_back(make_pair(1, Item{"Uniform", 10}));
    d1.items.push_back(make_pair(2, Item{"Pants", 5}));

    Delivery d2;
    d2.deliveryID = nextDeliveryID++;
    d2.dateOfArrival = "2026-09-13";
    d2.items.push_back(make_pair(2, Item{"Pants", 11}));
    d2.items.push_back(make_pair(1, Item{"Uniform", 7}));

    deliveryQueue.push(d1);
    deliveryQueue.push(d2);
}

// loops through queue
void loopThroughQueue() {
    if (deliveryQueue.empty()) {
        cout << "  (Queue is empty)" << endl;
        return;
    }

    //create copy of the queue with temp
    queue<Delivery> temp = deliveryQueue;

    //while loop to 
    while (!temp.empty()) {
        const Delivery& d = temp.front();

        // printing deliveryID and date of arrival
        cout << left << "\033[1G" << BLUE << "  " << d.deliveryID << RESET
            << "\033[17G" << d.dateOfArrival << "\033[38G";
        
        // for loop to print items
        for (size_t i = 0; i < d.items.size(); i++) {
            cout << d.items[i].second.itemName << " x" << d.items[i].second.quantity;
            if (i + 1 < d.items.size()) cout << ", ";
        }
        cout << endl;

        // pop value after the print to cycle to the next.
        temp.pop();
    }
}

// adds a delivery to the back of the queue
void addToQueue() {
    Delivery d;
    d.deliveryID = nextDeliveryID;

    string enteredDate; //date is now properly accounted for
    cout << endl << "Date of Arrival (e.g. 2026-10-15): ";
    cin >> enteredDate;

    if (!normalizeDate(enteredDate, d.dateOfArrival)) { //error handling moved here
        cout << RED << "[Invalid date, delivery cancelled]"
             << RESET << endl << endl;
        return;
    }
    
    int count; //moved
    cout << "How many different items in this delivery? ";
    cin >> count;

    // error handling
    if (cin.fail() || count <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << RED << "[Invalid count, delivery cancelled]"
             << RESET << endl << endl;
        return;
    }

    for (int i = 0; i < count; i++) { //moved
        int code, qty;
        string name;

        cout << "Item Code: ";
        cin >> code;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << RED << "[Invalid code, delivery cancelled]"
                 << RESET << endl << endl;
            return;
        }

        //clears line
        cin.ignore(1000, '\n');

        // auto is used to determine what type of variable it is
        auto it = inventory.find(code);

        // conditional block if there is already an existing item under this name within the inventory or if it is unique.
        if (it != inventory.end()) {
            name = it->second.itemName;
            cout << "Item: " << name << endl;
        } else {
            cout << "New item code. Item Name: ";
            getline(cin, name);
        }

        // quantity of item
        cout << "Quantity: ";
        cin >> qty;

        // error handling
        if (cin.fail() || qty <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << RED << "[Invalid quantity, delivery cancelled]" << RESET << endl << endl;
            return;
        }

        // adds another element to end of the container
        d.items.push_back(make_pair(code, Item{name, qty}));
    }

    nextDeliveryID++;
    deliveryQueue.push(d);
    cout << GREEN << "[Delivery #" << d.deliveryID << " added to queue]" << RESET << endl << endl;

}

// removes the delivery at the very front of the queue
void removeFromQueue() {

    // error handling just in case the queue is empty
    if (deliveryQueue.empty()) {
        cout << RED << "[Queue is empty, nothing to process]" << RESET << endl << endl;
        return;
    }

    // oldest delivery, adding of items to inventory from delivery
    Delivery d = deliveryQueue.front();                  // oldest delivery
    for (const Entry& e : d.items) {
        auto it = inventory.find(e.first);

        // conditional block if adding quantity to pre-existing item, else makes a new entry for a unique one
        if (it != inventory.end()) it->second.quantity += e.second.quantity;
        else inventory[e.first] = e.second;              
    }

    // remove from front 
    deliveryQueue.pop();
    cout << GREEN << "[Delivery #" << d.deliveryID << " processed. Inventory updated]"
        << RESET << endl << endl;
}

void deliveryQueueMenu() {
    int SecondMenuChoice;
    while (true) {
        displayQueue();
        cout << "|[1] -- Add Delivery To Queue" << endl;
        cout << "|[2] -- Sort by Date Added" << endl; //sorting it
        cout << "|[3] -- Process Next Delivery (Remove From Front)" << endl;
        cout << "|[4] -- Back To Main Menu" << endl;
        cout << "|[0] -- Exit Program" << endl;
        cout << "Choice: ";

        cin >> SecondMenuChoice;

        switch (SecondMenuChoice) {
            case 1: 
                addToQueue();   
                break;
            case 2: 
                sortQueueMenu(); //EDITED FOR QUEUE DATE SORTING
                break;
            case 3: 
                removeFromQueue(); 
                break;
            case 4: 
                cout << endl; 
                return;
            case 0:
                cout << endl << "[ Exiting BEIAS.. | Thank you for your usage! ] " << endl;
                exit(0);
            default:
                cout << RED << "[Invalid choice]" << RESET << endl << endl;
        }
    }
}

// main method
int main()
{   
    int MenuInput;
    initializeQueue();

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
            deliveryQueueMenu();
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
