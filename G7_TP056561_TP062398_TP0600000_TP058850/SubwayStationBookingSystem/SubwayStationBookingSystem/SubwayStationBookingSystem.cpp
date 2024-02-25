#include <iostream>
#include <iomanip>
#include <sstream>
#include <regex>
#include <format>
#include <chrono>
#include <ctime> 
#pragma warning(disable : 4996)

using namespace std;


//Initializing global variables
int selection;
string passengerUsername, separator = "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";


//Initializing methods
void PassengerMainMenu();
void ChooseRoute();
void TwoCity(string sourceID, string destinationID, string route);
void CheckTwoCity(string fromRoute);
void PassengerLogin();
void PassengerRegister();
void SearchSubwayStation();
void SearchTransaction();
void SelectionSortPassengerName();
void TransactionPage(string sourceID, string destinationID, double totalfair, int totalTime);
void SelectionSortByTransactionID();
void DisplayAdminSubwayStation();
void EditSubwayStationDetails(string sID);
void DeletePassengerTicketInfo(string tranID);
void EditTicketTransactionDetails(string transID);
void DisplayPurchaseTransaction();
void AdminMainMenu();
bool AdminLogin();



//Subway Station linked list
struct SubwayStation {
    string sID, sName, sPrevID, sNextID, sNearbySpot;  //or sPrevName, sNextName
    int sPrevDistance, sNextDistance, sPrevTravelTime, sNextTravelTime;
    double sPrevFair, sNextFair;

    SubwayStation* sNextAddress;
    SubwayStation* sPrevAddress;

}*sHead, * sTail, * sCurrent;

//subway station newnode function creation
SubwayStation* createSubwayNewNode(string sID, string sName, string sPrevID, string sNextID, string sNearbySpot,
    int sPrevDistance, int sNextDistance, int sPrevTravelTime, int sNextTravelTime,
    double sPrevFair, double sNextFair) {

    SubwayStation* sNewnode = new SubwayStation;

    sNewnode->sID = sID;
    sNewnode->sName = sName;
    sNewnode->sPrevID = sPrevID;
    sNewnode->sNextID = sNextID;
    sNewnode->sNearbySpot = sNearbySpot;
    sNewnode->sPrevDistance = sPrevDistance;
    sNewnode->sNextDistance = sNextDistance;
    sNewnode->sPrevTravelTime = sPrevTravelTime;
    sNewnode->sNextTravelTime = sNextTravelTime;
    sNewnode->sPrevFair = sPrevFair;
    sNewnode->sNextFair = sNextFair;
    sNewnode->sNextAddress = NULL;
    sNewnode->sPrevAddress = NULL;

    return sNewnode;
}

//Inserting subway station at the end of list
void insertSubwayToEnd(SubwayStation* sNewnode)
{
    //situation 1: list empty
    if (sHead == NULL)
    {
        sHead = sTail = sNewnode; //changes for doubly
    }
    //situation 2: list not empty
    else
    {
        sNewnode->sPrevAddress = sTail;
        sTail->sNextAddress = sNewnode;
        sTail = sNewnode;
    }
}

void insertToFrontOfList(SubwayStation* sNewnode) //how to insert to the front of the list
{
    //situation 1: List still empty
    if (sHead == NULL)
    {
        sHead = sNewnode;
    }
    else
    {
        sNewnode->sNextAddress = sHead;
        sHead = sNewnode;
    }
}


//STORE AVAILABLE SUBWAY STATION DETAIL IN DOUBLE LINKED LIST
void insertDefaultSubwayStationDetails()
{
    SubwayStation* sNewnode1 = new SubwayStation;
    sNewnode1->sID = "S001";
    sNewnode1->sName = "Titiwangsa";
    sNewnode1->sPrevID = "NULL";
    sNewnode1->sNextID = "S002";
    sNewnode1->sNearbySpot = "Lake Titiwangsa";
    sNewnode1->sPrevDistance = NULL;
    sNewnode1->sNextDistance = 4;
    sNewnode1->sPrevTravelTime = NULL;
    sNewnode1->sNextTravelTime = 3;
    sNewnode1->sPrevFair = NULL;
    sNewnode1->sNextFair = 0.40;
    sNewnode1->sNextAddress = NULL;
    sNewnode1->sPrevAddress = NULL;

    SubwayStation* sNewnode2 = new SubwayStation;
    sNewnode2->sID = "S002";
    sNewnode2->sName = "PWTC";
    sNewnode2->sPrevID = "S001";
    sNewnode2->sNextID = "S003";
    sNewnode2->sNearbySpot = "Tirta Spa";
    sNewnode2->sPrevDistance = 4;
    sNewnode2->sNextDistance = 8;
    sNewnode2->sPrevTravelTime = 3;
    sNewnode2->sNextTravelTime = 7;
    sNewnode2->sPrevFair = 0.40;
    sNewnode2->sNextFair = 0.80;
    sNewnode2->sNextAddress = NULL;
    sNewnode2->sPrevAddress = NULL;

    SubwayStation* sNewnode3 = new SubwayStation;
    sNewnode3->sID = "S003";
    sNewnode3->sName = "Sultan Ismail";
    sNewnode3->sPrevID = "S002";
    sNewnode3->sNextID = "S004";
    sNewnode3->sNearbySpot = "Clinic";
    sNewnode3->sPrevDistance = 8;
    sNewnode3->sNextDistance = 8;
    sNewnode3->sPrevTravelTime = 7;
    sNewnode3->sNextTravelTime = 7;
    sNewnode3->sPrevFair = 0.80;
    sNewnode3->sNextFair = 0.80;
    sNewnode3->sNextAddress = NULL;
    sNewnode3->sPrevAddress = NULL;

    SubwayStation* sNewnode4 = new SubwayStation;
    sNewnode4->sID = "S004";
    sNewnode4->sName = "Majlis Jamek";
    sNewnode4->sPrevID = "S003";
    sNewnode4->sNextID = "S005";
    sNewnode4->sNearbySpot = "Sports Direct";
    sNewnode4->sPrevDistance = 8;
    sNewnode4->sNextDistance = 6;
    sNewnode4->sPrevTravelTime = 7;
    sNewnode4->sNextTravelTime = 5;
    sNewnode4->sPrevFair = 0.80;
    sNewnode4->sNextFair = 0.60;
    sNewnode4->sNextAddress = NULL;
    sNewnode4->sPrevAddress = NULL;

    SubwayStation* sNewnode5 = new SubwayStation;
    sNewnode5->sID = "S005";
    sNewnode5->sName = "Plaza Rakyat";
    sNewnode5->sPrevID = "S004";
    sNewnode5->sNextID = "S006";
    sNewnode5->sNearbySpot = "Sports Toto";
    sNewnode5->sPrevDistance = 6;
    sNewnode5->sNextDistance = 10;
    sNewnode5->sPrevTravelTime = 5;
    sNewnode5->sNextTravelTime = 9;
    sNewnode5->sPrevFair = 0.60;
    sNewnode5->sNextFair = 1.00;
    sNewnode5->sNextAddress = NULL;
    sNewnode5->sPrevAddress = NULL;

    SubwayStation* sNewnode6 = new SubwayStation;
    sNewnode6->sID = "S006";
    sNewnode6->sName = "Hang Tuah";
    sNewnode6->sPrevID = "S005";
    sNewnode6->sNextID = "S007";
    sNewnode6->sNearbySpot = "Barkey Sports";
    sNewnode6->sPrevDistance = 10;
    sNewnode6->sNextDistance = 5;
    sNewnode6->sPrevTravelTime = 9;
    sNewnode6->sNextTravelTime = 4;
    sNewnode6->sPrevFair = 1.00;
    sNewnode6->sNextFair = 0.50;
    sNewnode6->sNextAddress = NULL;
    sNewnode6->sPrevAddress = NULL;

    SubwayStation* sNewnode7 = new SubwayStation;
    sNewnode7->sID = "S007";
    sNewnode7->sName = "Pudu";
    sNewnode7->sPrevID = "S006";
    sNewnode7->sNextID = "S008";
    sNewnode7->sNearbySpot = "Younique Sports";
    sNewnode7->sPrevDistance = 5;
    sNewnode7->sNextDistance = 5;
    sNewnode7->sPrevTravelTime = 4;
    sNewnode7->sNextTravelTime = 4;
    sNewnode7->sPrevFair = 0.50;
    sNewnode7->sNextFair = 0.50;
    sNewnode7->sNextAddress = NULL;
    sNewnode7->sPrevAddress = NULL;

    SubwayStation* sNewnode8 = new SubwayStation;
    sNewnode8->sID = "S008";
    sNewnode8->sName = "Chan Sow Lin";
    sNewnode8->sPrevID = "S007";
    sNewnode8->sNextID = "NULL";
    sNewnode8->sNearbySpot = "JK Sports";
    sNewnode8->sPrevDistance = 5;
    sNewnode8->sNextDistance = NULL;
    sNewnode8->sPrevTravelTime = 4;
    sNewnode8->sNextTravelTime = NULL;
    sNewnode8->sPrevFair = 0.50;
    sNewnode8->sNextFair = NULL;
    sNewnode8->sNextAddress = NULL;
    sNewnode8->sPrevAddress = NULL;

    insertSubwayToEnd(sNewnode1);
    insertSubwayToEnd(sNewnode2);
    insertSubwayToEnd(sNewnode3);
    insertSubwayToEnd(sNewnode4);
    insertSubwayToEnd(sNewnode5);
    insertSubwayToEnd(sNewnode6);
    insertSubwayToEnd(sNewnode7);
    insertSubwayToEnd(sNewnode8);
}


//Passenger Structure
struct Passenger {
    string pID, pUsername, pPassword, pName, pGender, pContactNum, pEmail, pHouseAddress;
    int pAge, pIC;

    Passenger* pNextAddress;

}*pHead, * pCurrent, * pTail;


//Passenger newnode function creation
Passenger* createPassengerNewNode(string pID, string pUsername, string pPassword, string pName,
    string pGender, string pContactNum, string pEmail, string pHouseAddress,
    int pAge, int pIC) {

    Passenger* pNewnode = new Passenger;

    pNewnode->pID = pID;
    pNewnode->pUsername = pUsername;
    pNewnode->pPassword = pPassword;
    pNewnode->pName = pName;
    pNewnode->pGender = pGender;
    pNewnode->pContactNum = pContactNum;
    pNewnode->pEmail = pEmail;
    pNewnode->pHouseAddress = pHouseAddress;
    pNewnode->pAge = pAge;
    pNewnode->pIC = pIC;
    pNewnode->pNextAddress = NULL;

    return pNewnode;
}


//Inserting passenger details at the end of list
void insertPassengerEnd(Passenger* pNewnode)
{
    //situation 1: List still empty
    if (pHead == NULL)
    {
        pHead = pNewnode;
    }
    //situation 2: List not empty
    else
    {
        pCurrent = pHead; //start from first node before traverse

        while (pCurrent->pNextAddress != NULL) //always check which one is the last node, so that we can add the new node to the current last note
        {
            pCurrent = pCurrent->pNextAddress;
        }
        pCurrent->pNextAddress = pNewnode;

    }
}


//Inserting passenger details 
void insertPassengerDetails() {

    Passenger* pNewnode1 = new Passenger;
    pNewnode1->pID = "P001";
    pNewnode1->pUsername = "prem123";
    pNewnode1->pPassword = "12345";
    pNewnode1->pName = "Prem";
    pNewnode1->pGender = "Male";
    pNewnode1->pContactNum = "60123221321";
    pNewnode1->pEmail = "Prem123@gmail.com";
    pNewnode1->pHouseAddress = "Petaling Jaya";
    pNewnode1->pAge = 35;
    pNewnode1->pIC = 352321;
    pNewnode1->pNextAddress = NULL;

    Passenger* pNewnode2 = new Passenger;
    pNewnode2->pID = "P002";
    pNewnode2->pUsername = "rico1234";
    pNewnode2->pPassword = "12345678";
    pNewnode2->pName = "Enrico";
    pNewnode2->pGender = "Male";
    pNewnode2->pContactNum = "60123671321";
    pNewnode2->pEmail = "enrico21@gmail.com";
    pNewnode2->pHouseAddress = "Kuala Lumpur";
    pNewnode2->pAge = 18;
    pNewnode2->pIC = 5342321;
    pNewnode2->pNextAddress = NULL;

    Passenger* pNewnode3 = new Passenger;
    pNewnode3->pID = "P003";
    pNewnode3->pUsername = "elisajane2";
    pNewnode3->pPassword = "123321";
    pNewnode3->pName = "Elisa";
    pNewnode3->pGender = "Female";
    pNewnode3->pContactNum = "60123671975";
    pNewnode3->pEmail = "elisa@gmail.com";
    pNewnode3->pHouseAddress = "Selangor";
    pNewnode3->pAge = 21;
    pNewnode3->pIC = 3242321;
    pNewnode3->pNextAddress = NULL;

    Passenger* pNewnode4 = new Passenger;
    pNewnode4->pID = "P099";
    pNewnode4->pUsername = "keerthana93";
    pNewnode4->pPassword = "43211234";
    pNewnode4->pName = "Keerthana";
    pNewnode4->pGender = "Female";
    pNewnode4->pContactNum = "60151271321";
    pNewnode4->pEmail = "keerthana21@gmail.com";
    pNewnode4->pHouseAddress = "Kuala Lumpur";
    pNewnode4->pAge = 20;
    pNewnode4->pIC = 3524221;
    pNewnode4->pNextAddress = NULL;


    insertPassengerEnd(pNewnode1);
    insertPassengerEnd(pNewnode2);
    insertPassengerEnd(pNewnode3);
    insertPassengerEnd(pNewnode4);
}


//Transaction structure
struct Transaction {
    string tranID, sSrc, sVenue, departTime, arrivalTime, pID, pName, pUsername;
    double  tTickAmt;
    int pIC;

    Transaction* tranNextAddress;

}*tranHead, * tranCurrent, * tranTail;


//transaction newnode function creation
Transaction* createtransactionNewNode(string tranID, string sSrc, string sVenue,
    string departTime, string arrivalTime, string pID, string pName, string pUsername,
    int pIC, double tTickAmt) {

    Transaction* tranNewnode = new Transaction;

    tranNewnode->tranID = tranID;
    tranNewnode->sSrc = sSrc;
    tranNewnode->sVenue = sVenue;
    tranNewnode->departTime = departTime;
    tranNewnode->arrivalTime = arrivalTime;
    tranNewnode->pID = pID;
    tranNewnode->pName = pName;
    tranNewnode->pIC = pIC;
    tranNewnode->pUsername = pUsername;
    tranNewnode->tTickAmt = tTickAmt;

    tranNewnode->tranNextAddress = NULL;
    return tranNewnode;
}


//Inserting transaction to end of linkedlist
void insertTransactionEnd(Transaction* tranNewnode)
{
    if (tranHead == NULL)
    {
        tranHead = tranNewnode;
    }

    else
    {
        tranCurrent = tranHead;

        while (tranCurrent->tranNextAddress != NULL)
        {
            tranCurrent = tranCurrent->tranNextAddress;
        }
        tranCurrent->tranNextAddress = tranNewnode;

    }
}


//Main Menu page
void InitialMainMenu() {
    cout << endl << endl;
    cout << "           Welcome to Subway Station System, what would you like to do?" << endl;
    cout << endl;
    cout << "   1) Login as Passenger" << endl;
    cout << "   2) Login as Administrator" << endl;
    cout << "   3) Register Passenger" << endl;
    cout << "   4) Exit" << endl;
    cout << "" << endl;
    cout << "   Your Option: ";

    do
    {
        if (!(cin >> selection))
        {
            cout << endl;
            cout << "  " << "Invalid input! Please enter proper input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if ((selection >= 1) && (selection <= 4)) {
            if (selection == 1) {
                PassengerLogin();
            }
            else if (selection == 2) {
                AdminLogin();
            }
            else if (selection == 3) {
                PassengerRegister();
            }
            else if (selection == 4) {
                exit;
            }
            break;
        }
        cout << endl;
        cout << "  " << "Please enter a valid option number [1-6]! " << endl;
    } while (true);
}

//check username already taken or not
bool isUsername(string username) {
    bool foundUsername = false;
    pCurrent = pHead;
    while (pCurrent != NULL)
    {
        if (pCurrent->pUsername == username) {
            foundUsername = true;
        }

        pTail = pCurrent;
        pCurrent = pCurrent->pNextAddress;

    }

    return foundUsername;
}


//Register Passener
void PassengerRegister() {
    //gettin last ID of the passenger
    pCurrent = pHead;

    string RegispID;
    int convertID;
    std::ostringstream newpID;

    while (pCurrent != NULL)
    {
        if (pCurrent->pNextAddress == NULL) {
            RegispID = pCurrent->pID;
        }
        pTail = pCurrent;
        pCurrent = pCurrent->pNextAddress;

    }

    //new passenger ID
    RegispID = RegispID.substr(1);
    convertID = std::stoi(RegispID) + 1;
    newpID << "P" << std::setw(3) << std::setfill('0') << convertID;
    RegispID = newpID.str();

    cout << "" << endl;
    cout << "                                      Welcome to Register Page" << endl;
    cout << "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "    Please fill the form below to complete your registration\n" << endl;
    int RegispAge, RegispIC;
    string RegispUsername, RegispPassword, ResgispConfirmPassword, RegispName, RegispGender, RegispEmail, RegispHouseAddress, RegispContactNum;

    do {
        cout << "  Username: ";
        cin >> RegispUsername;
        bool vUsername = isUsername(RegispUsername);
        if (vUsername) {
            cout << "\n\n                             Username Already Taken !! Please Try Again\n\n" << endl;
            continue;
        }

        cout << "  Password: ";
        cin >> RegispPassword;
        cin.ignore();


        cout << "  Confirm Password: ";
        cin >> ResgispConfirmPassword;

        if (RegispPassword != ResgispConfirmPassword) {
            cout << endl;
            cout << "                             Password doesn't match !! Please Try Again\n\n" << endl;
            continue;
        }


        cout << "  Name: ";
        cin.ignore();
        getline(cin, RegispName);

        cout << "  Age: ";
        cin >> RegispAge;
        if (!RegispAge)
        {
            cout << "                              Invalid Age !! Please Try Again \n\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }



        cout << "  Gender (eg: Male/Female): ";
        cin >> RegispGender;
        if (RegispGender == "Male" || RegispGender == "Female")
        {

        }
        else
        {

            cout << endl;
            cout << "                             Invalid Gender !! Please Try Again\n\n" << endl;
            continue;
        }


        cout << "  Contact Number: ";
        cin >> RegispContactNum;


        if (!regex_match(RegispContactNum, regex("^[0-9-]*$")))
        {
            cout << endl;
            cout << "                             Invalid Contact Number !! Please Try Again\n\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << "  Email (eg: test123@gmail.com): ";
        cin >> RegispEmail;
        cin.ignore();


        if (!regex_match(RegispEmail, regex("([_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4}))"))) {
            cout << "                             " << RegispEmail << " : " << "  Invalid Email Format" << endl;
            continue;
        }


        cout << "  House Address : ";
        getline(cin, RegispHouseAddress);


        cout << "  IC (eg: 0108011212/010801-11-212): ";
        cin >> RegispIC;

        if (!RegispIC)
        {
            cout << "                              Invalid IC Number !! Please Try Again\n\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;


    } while (true);


    //passenger confirmation
    cout << endl;
    selection = 0;

    cout << "  Are you sure with the details entered? " << endl;
    cout << "  [1] Yes, submit it!" << endl;
    cout << "  [2] No, would like to enter again!" << endl;
    cout << "  [3] Back to Main Menu" << endl;
    cout << " Your Option: " << endl;

    do
    {
        if (!(cin >> selection))
        {
            cout << "                              Invalid input! Please enter proper input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if ((selection >= 1) && (selection <= 3)) {
            if (selection == 1) {
                cout << endl;
                cout << "                               Register Successful | Thank you for registering !!" << endl;
                Passenger* pNewnode = createPassengerNewNode(RegispID, RegispUsername, RegispPassword, RegispName, RegispGender, RegispContactNum, RegispEmail, RegispHouseAddress, RegispAge, RegispIC);
                insertPassengerEnd(pNewnode);
                PassengerLogin();
                cout << endl;
            }

            if (selection == 2) {
                PassengerRegister();
            }

            if (selection == 3) {
                InitialMainMenu();
            }

            break;
        }
        cout << "                              Please enter a valid option number [1-3]! " << endl;
    } while (true);

}


//Login method for passenger
void PassengerLogin()
{
    pCurrent = pHead;
    bool notfound = true;
    string PassengerUsername, PassengerPassword;
    cout << endl;
    cout << endl;
    cout << "                                                                               Passenger Login" << endl;
    cout << endl;
    cout << separator << endl;
    cout << endl;
    cout << "                                                                 Please input your username and password!" << endl;
    cout << endl;
    cout << endl;
    cout << "                                                                Username: ";
    cin >> PassengerUsername;
    cout << "                                                                Password: ";
    cin >> PassengerPassword;

    if (PassengerUsername.empty() || PassengerPassword.empty()) {
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "                                                                 Empty input found! Please input both username and password." << endl;
    }
    else {

        while (pCurrent != NULL) {
            if (pCurrent->pUsername == PassengerUsername && pCurrent->pPassword == PassengerPassword) {
                cout << endl;
                cout << endl;
                cout << endl;
                cout << "                                                                               ###############################" << endl;
                cout << "                                                                               ##      Login Successful     ##" << endl;
                cout << "                                                                               ###############################" << endl;
                cout << endl;
                cout << endl;
                cout << endl;
                passengerUsername = PassengerUsername;
                PassengerMainMenu();
            }


            pCurrent = pCurrent->pNextAddress;
        }

        if (notfound) {
            cout << endl;
            cout << endl;
            cout << endl;
            cout << "                                                                 Incorrect Password or Username insertion! Please try again." << endl;
            cout << endl;
            cout << endl << endl << endl << endl;
            InitialMainMenu();

        }

    }
}


//Passenger Main Menu method
void PassengerMainMenu()
{
    selection = 0;
    cout << "" << endl;
    cout << "                                                                               Welcome back " << passengerUsername << " !" << endl;
    cout << "" << endl;
    cout << "                                                           Kuala Lumpur Light Rail Transit (LRT) - Titiwangsa Station - Chan Sow Lin Station Route" << endl;
    cout << separator << endl;
    cout << "" << endl;

    //display entire route with two way arrows
    sCurrent = sHead;


    cout << "     [ Station Starts Here ]     ";

    std::ostringstream mainRoute;
    string formatRoute;

    while (sCurrent != NULL)
    {
        mainRoute << sCurrent->sName + "  <->  ";
        formatRoute = mainRoute.str();

        sTail = sCurrent;
        sCurrent = sCurrent->sNextAddress;

    }

    //erasing the last arrow
    cout << formatRoute.erase(formatRoute.length() - 5);

    if (sCurrent == NULL) {
        cout << "  [ Station Ends Here ]" << endl;
    }

    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "   Menu Options [1-4]: " << endl;
    cout << "" << endl;
    cout << "   [1] Purchase Ticket" << endl;
    cout << "   [2] Search Subway Station Details" << endl;
    cout << "   [3] Purchase Transaction History" << endl;
    cout << "   [4] Logout" << endl;
    cout << "" << endl;
    cout << "   Your Option: ";
    do
    {
        if (!(cin >> selection))
        {
            cout << "Invalid input! Please enter proper input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if ((selection >= 1) && (selection <= 4)) {
            if (selection == 1) {
                ChooseRoute();
            }
            if (selection == 2) {
                SearchSubwayStation();
            }

            if (selection == 3) {
                SearchTransaction();
            }
            if (selection == 4) {
                InitialMainMenu();
            }
            break;
        }
        cout << "                              Please enter a valid option number [1-4]! " << endl;
    } while (true);

}


//display all station details from front or End
void DisplayAllSubwayStationDetails(int FrontorEnd) {
    cout << endl;
    cout << "   Start of the Subway Station Line!" << endl;
    cout << endl;
    cout << "                    \x19" << endl;

    if (FrontorEnd == 1) {
        sCurrent = sHead;

        while (sCurrent != NULL) {
            cout << endl;
            cout << "  " << sCurrent->sID << " - " << sCurrent->sName << endl;
            cout << "  ------------------------------------------------" << endl;
            if (sCurrent->sPrevID == "NULL") {
                cout << "  " << "Previous Station ID          : " << " - " << endl;
            }
            else {
                cout << "  " << "Previous Station ID          : " << sCurrent->sPrevID << endl;
            }

            if (sCurrent->sNextID == "NULL") {
                cout << "  " << "Next Station ID              : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station ID              : " << sCurrent->sNextID << endl;
            }


            cout << "  " << "Nearby Spot                  : " << sCurrent->sNearbySpot << endl;

            if (sCurrent->sPrevDistance == NULL) {
                cout << "  " << "Previous Station Distance    : " << " - " << endl;
            }
            else {
                cout << "  " << "Previous Station Distance    : " << sCurrent->sPrevDistance << " KM" << endl;
            }

            if (sCurrent->sNextDistance == NULL) {
                cout << "  " << "Next Station Distance        : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station Distance        : " << sCurrent->sNextDistance << " KM" << endl;
            }

            if (sCurrent->sPrevTravelTime == NULL) {
                cout << "  " << "Previous Station Travel Time : " << " - " << endl;
            }
            else {
                cout << "  " << "Previous Station Travel Time : " << sCurrent->sPrevTravelTime << " MIN" << endl;
            }

            if (sCurrent->sNextTravelTime == NULL) {
                cout << "  " << "Next Station Travel Time     : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station Travel Time     : " << sCurrent->sNextTravelTime << " MIN" << endl;
            }

            if (sCurrent->sPrevFair == NULL) {

                cout << "  " << "Previous Station Fair        : " << " - " << endl;
            }
            else {

                cout << "  " << "Previous Station Fair        : " << "RM " << sCurrent->sPrevFair << endl;
            }

            if (sCurrent->sNextFair == NULL) {
                cout << "  " << "Next Station Fair            : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station Fair            : " << "RM " << sCurrent->sNextFair << endl;
            }


            sCurrent = sCurrent->sNextAddress;
        }

    }
    else if (FrontorEnd == 2) {
        sCurrent = sTail;

        while (sCurrent != NULL) {
            cout << endl;
            cout << "  " << sCurrent->sID << " - " << sCurrent->sName << endl;
            cout << "  ------------------------------------------------" << endl;


            if (sCurrent->sNextID == "NULL") {
                cout << "  " << "Previous Station ID          : " << " - " << endl;
            }
            else {
                cout << "  " << "Previous Station ID          : " << sCurrent->sNextID << endl;
            }

            if (sCurrent->sPrevID == "NULL") {
                cout << "  " << "Next Station ID              : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station ID              : " << sCurrent->sPrevID << endl;
            }


            cout << "  " << "Nearby Spot                  : " << sCurrent->sNearbySpot << endl;

            if (sCurrent->sNextDistance == NULL) {
                cout << "  " << "Previous Station Distance    : " << " - " << endl;
            }
            else {
                cout << "  " << "Previous Station Distance    : " << sCurrent->sNextDistance << " KM" << endl;
            }

            if (sCurrent->sPrevDistance == NULL) {
                cout << "  " << "Next Station Distance        : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station Distance        : " << sCurrent->sPrevDistance << " KM" << endl;
            }

            if (sCurrent->sNextTravelTime == NULL) {
                cout << "  " << "Previous Station Travel Time : " << " - " << endl;
            }
            else {
                cout << "  " << "Previous Station Travel Time : " << sCurrent->sNextTravelTime << " MIN" << endl;
            }

            if (sCurrent->sPrevTravelTime == NULL) {
                cout << "  " << "Next Station Travel Time     : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station Travel Time     : " << sCurrent->sPrevTravelTime << " MIN" << endl;
            }

            if (sCurrent->sNextFair == NULL) {

                cout << "  " << "Previous Station Fair        : " << " - " << endl;
            }
            else {

                cout << "  " << "Previous Station Fair        : " << "RM " << sCurrent->sNextFair << endl;
            }

            if (sCurrent->sPrevFair == NULL) {
                cout << "  " << "Next Station Fair            : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station Fair            : " << "RM " << sCurrent->sPrevFair << endl;
            }

            sCurrent = sCurrent->sPrevAddress;
        }
    }


    cout << endl;
    cout << "                   \x18" << endl;
    cout << endl;

    cout << "   End of the Subway Station Line!" << endl;
    SearchSubwayStation();
}



//Display single subway station details
void DisplaySingleSubwayDetails(int FrontorEnd) {
    int frontorend = FrontorEnd;
    selection = 0;
    if (frontorend == 3) {
        sCurrent = sHead;
        while (sCurrent != NULL) {
            cout << endl;
            cout << "  " << sCurrent->sID << " - " << sCurrent->sName << endl;
            cout << "  ------------------------------------------------" << endl;
            if (sCurrent->sPrevID == "NULL") {
                cout << "  " << "Previous Station ID          : " << " - " << endl;
            }
            else {
                cout << "  " << "Previous Station ID          : " << sCurrent->sPrevID << endl;
            }

            if (sCurrent->sNextID == "NULL") {
                cout << "  " << "Next Station ID              : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station ID              : " << sCurrent->sNextID << endl;
            }


            cout << "  " << "Nearby Spot                  : " << sCurrent->sNearbySpot << endl;

            if (sCurrent->sPrevDistance == NULL) {
                cout << "  " << "Previous Station Distance    : " << " - " << endl;
            }
            else {
                cout << "  " << "Previous Station Distance    : " << sCurrent->sPrevDistance << " KM" << endl;
            }

            if (sCurrent->sNextDistance == NULL) {
                cout << "  " << "Next Station Distance        : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station Distance        : " << sCurrent->sNextDistance << " KM" << endl;
            }

            if (sCurrent->sPrevTravelTime == NULL) {
                cout << "  " << "Previous Station Travel Time : " << " - " << endl;
            }
            else {
                cout << "  " << "Previous Station Travel Time : " << sCurrent->sPrevTravelTime << " MIN" << endl;
            }

            if (sCurrent->sNextTravelTime == NULL) {
                cout << "  " << "Next Station Travel Time     : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station Travel Time     : " << sCurrent->sNextTravelTime << " MIN" << endl;
            }

            if (sCurrent->sPrevFair == NULL) {

                cout << "  " << "Previous Station Fair        : " << " - " << endl;
            }
            else {

                cout << "  " << "Previous Station Fair        : " << "RM " << sCurrent->sPrevFair << endl;
            }

            if (sCurrent->sNextFair == NULL) {
                cout << "  " << "Next Station Fair            : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station Fair            : " << "RM " << sCurrent->sNextFair << endl;
            }

            cout << endl;
            cout << "  ===========================================" << endl;
            cout << "  [1] Next Subway Station" << endl;
            cout << "  [2] Previous Subway Station" << endl;
            cout << "  [3] Back to Subway Stations Details Menu" << endl;
            cout << "  ===========================================" << endl;
            cout << endl;
            cout << "  Your selection : ";
            cin >> selection;

            if (selection == 1) {
                sCurrent = sCurrent->sNextAddress;

            }
            else if (selection == 2) {
                sCurrent = sCurrent->sPrevAddress;
            }
            else if (selection == 3) {
                SearchSubwayStation();
                cout << endl;
            }
            else {
                cout << endl;
                cout << "  " << "Invalid selection input !" << endl;
            }

        }
    }
    else if (frontorend == 4) {
        sCurrent = sTail;

        while (sCurrent != NULL) {
            cout << endl;
            cout << "  " << sCurrent->sID << " - " << sCurrent->sName << endl;
            cout << "  ------------------------------------------------" << endl;


            if (sCurrent->sNextID == "NULL") {
                cout << "  " << "Previous Station ID          : " << " - " << endl;
            }
            else {
                cout << "  " << "Previous Station ID          : " << sCurrent->sNextID << endl;
            }

            if (sCurrent->sPrevID == "NULL") {
                cout << "  " << "Next Station ID              : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station ID              : " << sCurrent->sPrevID << endl;
            }


            cout << "  " << "Nearby Spot                  : " << sCurrent->sNearbySpot << endl;

            if (sCurrent->sNextDistance == NULL) {
                cout << "  " << "Previous Station Distance    : " << " - " << endl;
            }
            else {
                cout << "  " << "Previous Station Distance    : " << sCurrent->sNextDistance << " KM" << endl;
            }

            if (sCurrent->sPrevDistance == NULL) {
                cout << "  " << "Next Station Distance        : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station Distance        : " << sCurrent->sPrevDistance << " KM" << endl;
            }

            if (sCurrent->sNextTravelTime == NULL) {
                cout << "  " << "Previous Station Travel Time : " << " - " << endl;
            }
            else {
                cout << "  " << "Previous Station Travel Time : " << sCurrent->sNextTravelTime << " MIN" << endl;
            }

            if (sCurrent->sPrevTravelTime == NULL) {
                cout << "  " << "Next Station Travel Time     : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station Travel Time     : " << sCurrent->sPrevTravelTime << " MIN" << endl;
            }

            if (sCurrent->sNextFair == NULL) {

                cout << "  " << "Previous Station Fair        : " << " - " << endl;
            }
            else {

                cout << "  " << "Previous Station Fair        : " << "RM " << sCurrent->sNextFair << endl;
            }

            if (sCurrent->sPrevFair == NULL) {
                cout << "  " << "Next Station Fair            : " << " - " << endl;
            }
            else {
                cout << "  " << "Next Station Fair            : " << "RM " << sCurrent->sPrevFair << endl;
            }

            cout << endl;
            cout << "  ===========================================" << endl;
            cout << "  [1] Next Subway Station" << endl;
            cout << "  [2] Previous Subway Station" << endl;
            cout << "  [3] Back to Subway Stations Details Menu" << endl;
            cout << "  ===========================================" << endl;
            cout << endl;
            cout << "  Your selection : ";
            cin >> selection;

            if (selection == 1) {
                sCurrent = sCurrent->sPrevAddress;

            }
            else if (selection == 2) {
                sCurrent = sCurrent->sNextAddress;
            }
            else if (selection == 3) {
                SearchSubwayStation();
                cout << endl;
            }
            else {
                cout << endl;
                cout << "  " << "Invalid selection input !" << endl;
            }


        }

    }


    DisplaySingleSubwayDetails(frontorend);

}


//specific subway station detail
void DisplaySpecificSubwayDetails() {
    selection = 0;
    string stationID, stationName, stationPrevID, stationNextID, stationNearbySpot;
    int stationPrevDistance, stationNextDistance, stationPrevTravelTime, stationNextTravelTime;
    double stationNextFair, stationPrevFair;
    bool checkStationID = true;
    sCurrent = sHead;

    cout << endl;
    cout << "  ===========================================" << endl;
    cout << "  [1] Search Specific Station " << endl;
    cout << "  [2] Back to Subway Stations Details Menu" << endl;
    cout << "  ===========================================" << endl;
    cout << endl;
    cout << "  Your selection : ";
    cin >> selection;

    if (selection == 1) {
        cout << endl;
        cout << "  Enter Station ID (eg: S001) : ";
        cin >> stationID;

        while (sCurrent != NULL) {
            if (sCurrent->sID == stationID) {
                checkStationID = false;
                stationName = sCurrent->sID;
                stationPrevID = sCurrent->sPrevID;
                stationNextID = sCurrent->sNextID;
                stationNearbySpot = sCurrent->sNearbySpot;
                stationPrevDistance = sCurrent->sPrevDistance;
                stationNextDistance = sCurrent->sNextDistance;
                stationPrevTravelTime = sCurrent->sPrevTravelTime;
                stationNextTravelTime = sCurrent->sNextTravelTime;
                stationPrevFair = sCurrent->sPrevFair;
                stationNextFair = sCurrent->sNextFair;
            }
            sCurrent = sCurrent->sNextAddress;
        }
    }
    else if (selection == 2) {
        SearchSubwayStation();
    }
    else {
        cout << endl;
        cout << "  " << "Invalid selection input !" << endl;
        DisplaySpecificSubwayDetails();
    }


    if (checkStationID) {
        cout << endl;
        cout << "      Station ID not exist !" << endl;
    }
    else {
        cout << "      Entered Station Information: " << endl;
        cout << "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;
        cout << "  " << stationID << " - " << stationName << endl;
        cout << endl;

        if (stationPrevID == "NULL") {
            cout << "  " << "Previous Station ID          : " << " - " << endl;
        }
        else {
            cout << "  " << "Previous Station ID          : " << stationPrevID << endl;
        }

        if (stationNextID == "NULL") {
            cout << "  " << "Next Station ID              : " << " - " << endl;
        }
        else {
            cout << "  " << "Next Station ID              : " << stationNextID << endl;
        }


        cout << "  " << "Nearby Spot                  : " << stationNearbySpot << endl;

        if (stationPrevDistance == NULL) {
            cout << "  " << "Previous Station Distance    : " << " - " << endl;
        }
        else {
            cout << "  " << "Previous Station Distance    : " << stationPrevDistance << " KM" << endl;
        }

        if (stationNextDistance == NULL) {
            cout << "  " << "Next Station Distance        : " << " - " << endl;
        }
        else {
            cout << "  " << "Next Station Distance        : " << stationNextDistance << " KM" << endl;
        }

        if (stationPrevTravelTime == NULL) {
            cout << "  " << "Previous Station Travel Time : " << " - " << endl;
        }
        else {
            cout << "  " << "Previous Station Travel Time : " << stationPrevTravelTime << " MIN" << endl;
        }

        if (stationNextTravelTime == NULL) {
            cout << "  " << "Next Station Travel Time     : " << " - " << endl;
        }
        else {
            cout << "  " << "Next Station Travel Time     : " << stationNextTravelTime << " MIN" << endl;
        }

        if (stationPrevFair == NULL) {

            cout << "  " << "Previous Station Fair        : " << " - " << endl;
        }
        else {

            cout << "  " << "Previous Station Fair        : " << "RM " << stationPrevFair << endl;
        }

        if (stationNextFair == NULL) {
            cout << "  " << "Next Station Fair            : " << " - " << endl;
        }
        else {
            cout << "  " << "Next Station Fair            : " << "RM " << stationNextFair << endl;
        }

        cout << endl;
    }
    DisplaySpecificSubwayDetails();
}


//passanger searching subway station details
void SearchSubwayStation() {

    selection = 0;
    cout << "" << endl;
    cout << "                                                           View Subway Station Details" << endl;
    cout << separator << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "   Menu Options [1-6]: " << endl;
    cout << "" << endl;
    cout << "   [1] View All Subway Details From Titiwangsa to Chan Sow Lin" << endl;
    cout << "   [2] View All Subway Details From Chan Sow Lin to Titiwangse" << endl;
    cout << "   [3] View Single Subway Details From Titiwangsa to Chan Sow Lin" << endl;
    cout << "   [4] View Single Subway Details From Chan Sow Lin to Titiwangse" << endl;
    cout << "   [5] Search Subway Station Details" << endl;
    cout << "   [6] Exit to Passanger Main Menu" << endl;
    cout << "" << endl;
    cout << "   Your Option: ";

    do
    {
        if (!(cin >> selection))
        {
            cout << "Invalid input! Please enter proper input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if ((selection >= 1) && (selection <= 6)) {
            if (selection == 1) {
                DisplayAllSubwayStationDetails(selection);
            }
            else if (selection == 2) {
                DisplayAllSubwayStationDetails(selection);
            }
            else if (selection == 3) {
                DisplaySingleSubwayDetails(selection);
            }
            else if (selection == 4) {
                DisplaySingleSubwayDetails(selection);
            }
            else if (selection == 5) {
                DisplaySpecificSubwayDetails();
            }
            else if (selection == 6) {
                PassengerMainMenu();
            }
            break;
        }
        cout << "  " << "Please enter a valid option number [1-6]! " << endl;
    } while (true);



    do
    {
        if (!(cin >> selection))
        {
            cout << "Invalid input! Please enter proper input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if ((selection >= 1) && (selection <= 6)) {
            if (selection == 1) {
                DisplayAllSubwayStationDetails(selection);
            }
            else if (selection == 2) {
                DisplayAllSubwayStationDetails(selection);
            }
            else if (selection == 3) {
                DisplaySingleSubwayDetails(selection);
            }
            else if (selection == 4) {
                DisplaySingleSubwayDetails(selection);
            }
            else if (selection == 5) {
                DisplaySpecificSubwayDetails();
            }
            else if (selection == 6) {
                PassengerMainMenu();
            }
            break;
        }
        cout << "Please enter a valid option number [1-6]! " << endl;
    } while (true);
}


//Checking Two City and validation of user input
void CheckTwoCity(string fromRoute) {
    string sourceStationID;
    string destinationStationID;
    string route = fromRoute;
    bool checkSource = true;
    bool checkDestination = true;

    selection = 0;

    cout << "  Choose which station you currently on by inputting the station ID (Eg: S001):  ";
    cin >> sourceStationID;
    cout << endl;
    cout << "  Choose which station you want to go by inputting the station ID (Eg: S002):  ";
    cin >> destinationStationID;
    cout << endl;
    cout << endl;


    if (sourceStationID.empty() || destinationStationID.empty()) {
        cout << "  Empty Station ID Input. " << endl;
        CheckTwoCity(route);
    }
    else if (sourceStationID == destinationStationID) {
        cout << "  You have inserted the same input!" << endl;
        CheckTwoCity(route);
    }
    else {
        //validation whether both id exists or not
        if (route == "Head") {
            sCurrent = sHead;
            while (sCurrent != NULL) {

                if (sCurrent->sID == sourceStationID)
                {
                    checkSource = false;
                };


                if (sCurrent->sID == destinationStationID)
                {
                    checkDestination = false;
                }


                sCurrent = sCurrent->sNextAddress;

            }

        }
        else if (route == "Tail") {

            sCurrent = sTail;
            while (sCurrent != NULL) {

                if (sCurrent->sID == destinationStationID)
                {
                    checkDestination = false;

                }

                if (sCurrent->sID == sourceStationID)
                {
                    checkSource = false;
                }


                sCurrent = sCurrent->sPrevAddress;

            }
        }

    }

    if (checkSource) {
        cout << "  Invalid Source Station ID." << endl;
        cout << endl;
        CheckTwoCity(route);
    }
    else if (checkDestination) {
        cout << "  Invalid Destination Station ID." << endl;
        cout << endl;
        CheckTwoCity(route);
    }
    else {
        TwoCity(sourceStationID, destinationStationID, route);
    }

}


//displaying two city information and validation of the city ID
void TwoCity(string sourceID, string destinationID, string route)
{
    int totalDistance = 0;
    double totalFair = 0;
    int totalTime = 0;
    string estimatedArrivalTime;

    if (route == "Head") {
        sCurrent = sHead;

        if (sourceID[3] > destinationID[3])
        {
            cout << "=========================================================" << endl;
            cout << "|Invalid Station Order!!, Directing Back to Route Menu!!!|" << endl;
            cout << "=========================================================" << endl;
            ChooseRoute();
        }

        while (sCurrent != NULL) {

            if (sCurrent->sID == sourceID) {

                cout << "    Your Current Station Information: " << endl;
                cout << "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << endl;
                cout << "  " << sCurrent->sID << " - " << sCurrent->sName << endl;
                cout << endl;

                if (sCurrent->sPrevID == "NULL") {
                    cout << "  " << "Previous Station ID          : " << " - " << endl;
                }
                else {
                    cout << "  " << "Previous Station ID          : " << sCurrent->sPrevID << endl;
                }

                if (sCurrent->sNextID == "Null") {
                    cout << "  " << "Next Station ID              : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station ID              : " << sCurrent->sNextID << endl;
                }


                cout << "  " << "Nearby Spot                  : " << sCurrent->sNearbySpot << endl;

                if (sCurrent->sPrevDistance == NULL) {
                    cout << "  " << "Previous Station Distance    : " << " - " << endl;
                }
                else {
                    cout << "  " << "Previous Station Distance    : " << sCurrent->sPrevDistance << " KM" << endl;
                }

                if (sCurrent->sNextDistance == NULL) {
                    cout << "  " << "Next Station Distance        : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station Distance        : " << sCurrent->sNextDistance << " KM" << endl;
                }

                if (sCurrent->sPrevTravelTime == NULL) {
                    cout << "  " << "Previous Station Travel Time : " << " - " << endl;
                }
                else {
                    cout << "  " << "Previous Station Travel Time : " << sCurrent->sPrevTravelTime << " MIN" << endl;
                }

                if (sCurrent->sNextTravelTime == NULL) {
                    cout << "  " << "Next Station Travel Time     : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station Travel Time     : " << sCurrent->sNextTravelTime << " MIN" << endl;
                }

                if (sCurrent->sPrevFair == NULL) {

                    cout << "  " << "Previous Station Fair        : " << " - " << endl;
                }
                else {

                    cout << "  " << "Previous Station Fair        : " << "RM " << sCurrent->sPrevFair << endl;
                }

                if (sCurrent->sNextFair == NULL) {
                    cout << "  " << "Next Station Fair            : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station Fair            : " << "RM " << sCurrent->sNextFair << endl;
                }

                while (sCurrent->sID != destinationID) {
                    totalDistance = sCurrent->sNextDistance + totalDistance;
                    totalFair = sCurrent->sNextFair + totalFair;
                    totalTime = sCurrent->sNextTravelTime + totalTime;
                    sCurrent = sCurrent->sNextAddress;
                }

            }

            cout << endl;

            if (sCurrent->sID == destinationID) {
                cout << "    Your Destionation Station Information: " << endl;
                cout << "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << endl;
                cout << "  " << sCurrent->sID << " - " << sCurrent->sName << endl;
                cout << endl;
                if (sCurrent->sPrevID == "NULL") {
                    cout << "  " << "Previous Station ID          : " << " - " << endl;
                }
                else {
                    cout << "  " << "Previous Station ID          : " << sCurrent->sPrevID << endl;
                }

                if (sCurrent->sNextID == "Null") {
                    cout << "  " << "Next Station ID              : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station ID              : " << sCurrent->sNextID << endl;
                }


                cout << "  " << "Nearby Spot                  : " << sCurrent->sNearbySpot << endl;

                if (sCurrent->sPrevDistance == NULL) {
                    cout << "  " << "Previous Station Distance    : " << " - " << endl;
                }
                else {
                    cout << "  " << "Previous Station Distance    : " << sCurrent->sPrevDistance << " KM" << endl;
                }

                if (sCurrent->sNextDistance == NULL) {
                    cout << "  " << "Next Station Distance        : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station Distance        : " << sCurrent->sNextDistance << " KM" << endl;
                }

                if (sCurrent->sPrevTravelTime == NULL) {
                    cout << "  " << "Previous Station Travel Time : " << " - " << endl;
                }
                else {
                    cout << "  " << "Previous Station Travel Time : " << sCurrent->sPrevTravelTime << " MIN" << endl;
                }

                if (sCurrent->sNextTravelTime == NULL) {
                    cout << "  " << "Next Station Travel Time     : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station Travel Time     : " << sCurrent->sNextTravelTime << " MIN" << endl;
                }

                if (sCurrent->sPrevFair == NULL) {

                    cout << "  " << "Previous Station Fair        : " << " - " << endl;
                }
                else {

                    cout << "  " << "Previous Station Fair        : " << "RM " << sCurrent->sPrevFair << endl;
                }

                if (sCurrent->sNextFair == NULL) {
                    cout << "  " << "Next Station Fair            : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station Fair            : " << "RM " << sCurrent->sNextFair << endl;
                }
            }


            sCurrent = sCurrent->sNextAddress;
        }


        auto start = std::chrono::system_clock::now();
        auto end = std::chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        time_t end_time = std::chrono::system_clock::to_time_t(end) + (totalTime * 60);
        estimatedArrivalTime = std::ctime(&end_time);

        cout << endl;
        cout << "  Total Travel Distance between two cities : " << totalDistance << " KM" << endl;
        cout << "  Total Travel Fair between two cities : " << "RM " << totalFair << endl;
        cout << "  Total Travel Time between two cities : " << totalTime << " minutes" << endl;
        cout << endl;
        cout << "  Estimated Arrival Time from now : " << estimatedArrivalTime << endl;

        cout << endl;
        cout << endl;
        cout << "  Do you want to continue into purchase ticket? " << endl;
        cout << "  [1] Proceed to Ticket Transaction" << endl;
        cout << "  [2] Go back to Choose Route" << endl;
        cout << "" << endl;
        cout << "   Your option : ";
        cin >> selection;

        if (selection == 1) {
            TransactionPage(sourceID, destinationID, totalFair, totalTime);
        }
        else if (selection == 2) {
            ChooseRoute();
        }
        else {
            cout << endl;
            cout << "  Wrong Option have been selected!" << endl;
            TwoCity(sourceID, destinationID, route);
        }


    }
    else if (route == "Tail") {
        sCurrent = sTail;
        if (sourceID[3] < destinationID[3])
        {
            cout << "=========================================================" << endl;
            cout << "|Invalid Station Order!!, Directing Back to Route Menu!!!|" << endl;
            cout << "=========================================================" << endl;
            ChooseRoute();
        }
        while (sCurrent != NULL) {

            if (sCurrent->sID == sourceID) {
                cout << "    Your Current Station Information: " << endl;
                cout << "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << endl;
                cout << "  " << sCurrent->sID << " - " << sCurrent->sName << endl;
                cout << endl;
                if (sCurrent->sNextID == "NULL") {
                    cout << "  " << "Previous Station ID          : " << " - " << endl;
                }
                else {
                    cout << "  " << "Previous Station ID          : " << sCurrent->sNextID << endl;
                }

                if (sCurrent->sPrevID == "Null") {
                    cout << "  " << "Next Station ID              : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station ID              : " << sCurrent->sPrevID << endl;
                }


                cout << "  " << "Nearby Spot                  : " << sCurrent->sNearbySpot << endl;

                if (sCurrent->sNextDistance == NULL) {
                    cout << "  " << "Previous Station Distance    : " << " - " << endl;
                }
                else {
                    cout << "  " << "Previous Station Distance    : " << sCurrent->sNextDistance << " KM" << endl;
                }

                if (sCurrent->sPrevDistance == NULL) {
                    cout << "  " << "Next Station Distance        : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station Distance        : " << sCurrent->sPrevDistance << " KM" << endl;
                }

                if (sCurrent->sNextTravelTime == NULL) {
                    cout << "  " << "Previous Station Travel Time : " << " - " << endl;
                }
                else {
                    cout << "  " << "Previous Station Travel Time : " << sCurrent->sNextTravelTime << " MIN" << endl;
                }

                if (sCurrent->sPrevTravelTime == NULL) {
                    cout << "  " << "Next Station Travel Time     : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station Travel Time     : " << sCurrent->sPrevTravelTime << " MIN" << endl;
                }

                if (sCurrent->sNextFair == NULL) {

                    cout << "  " << "Previous Station Fair        : " << " - " << endl;
                }
                else {

                    cout << "  " << "Previous Station Fair        : " << "RM " << sCurrent->sNextFair << endl;
                }

                if (sCurrent->sPrevFair == NULL) {
                    cout << "  " << "Next Station Fair            : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station Fair            : " << "RM " << sCurrent->sPrevFair << endl;
                }

                while (sCurrent->sID != destinationID) {
                    totalDistance = sCurrent->sPrevDistance + totalDistance;
                    totalFair = sCurrent->sPrevFair + totalFair;
                    totalTime = sCurrent->sPrevTravelTime + totalTime;
                    sCurrent = sCurrent->sPrevAddress;
                }

            }

            cout << endl;
            if (sCurrent->sID == destinationID) {
                cout << "    Your Destination Station Information: " << endl;
                cout << "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << endl;
                cout << "  " << sCurrent->sID << " - " << sCurrent->sName << endl;
                cout << endl;
                if (sCurrent->sNextID == "NULL") {
                    cout << "  " << "Previous Station ID          : " << " - " << endl;
                }
                else {
                    cout << "  " << "Previous Station ID          : " << sCurrent->sNextID << endl;
                }

                if (sCurrent->sPrevID == "Null") {
                    cout << "  " << "Next Station ID              : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station ID              : " << sCurrent->sPrevID << endl;
                }


                cout << "  " << "Nearby Spot                  : " << sCurrent->sNearbySpot << endl;

                if (sCurrent->sNextDistance == NULL) {
                    cout << "  " << "Previous Station Distance    : " << " - " << endl;
                }
                else {
                    cout << "  " << "Previous Station Distance    : " << sCurrent->sNextDistance << " KM" << endl;
                }

                if (sCurrent->sPrevDistance == NULL) {
                    cout << "  " << "Next Station Distance        : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station Distance        : " << sCurrent->sPrevDistance << " KM" << endl;
                }

                if (sCurrent->sNextTravelTime == NULL) {
                    cout << "  " << "Previous Station Travel Time : " << " - " << endl;
                }
                else {
                    cout << "  " << "Previous Station Travel Time : " << sCurrent->sNextTravelTime << " MIN" << endl;
                }

                if (sCurrent->sPrevTravelTime == NULL) {
                    cout << "  " << "Next Station Travel Time     : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station Travel Time     : " << sCurrent->sPrevTravelTime << " MIN" << endl;
                }

                if (sCurrent->sNextFair == NULL) {

                    cout << "  " << "Previous Station Fair        : " << " - " << endl;
                }
                else {

                    cout << "  " << "Previous Station Fair        : " << "RM " << sCurrent->sNextFair << endl;
                }

                if (sCurrent->sPrevFair == NULL) {
                    cout << "  " << "Next Station Fair            : " << " - " << endl;
                }
                else {
                    cout << "  " << "Next Station Fair            : " << "RM " << sCurrent->sPrevFair << endl;
                }
            }


            sCurrent = sCurrent->sPrevAddress;
        }

        auto start = std::chrono::system_clock::now();
        auto end = std::chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        time_t end_time = std::chrono::system_clock::to_time_t(end) + (totalTime * 60);
        estimatedArrivalTime = std::ctime(&end_time);

        cout << endl;
        cout << endl;
        cout << "  Total Travel Distance between two cities : " << totalDistance << " KM" << endl;
        cout << "  Total Travel Fair between two cities : " << "RM " << totalFair << endl;
        cout << "  Total Travel Time between two cities : " << totalTime << " minutes" << endl;
        cout << endl;
        cout << "  Estimated Arrival Time from now : " << estimatedArrivalTime << endl;

        cout << endl;
        cout << endl;
        cout << "  Do you want to continue into purchase ticket? " << endl;
        cout << "  [1] Proceed to Ticket Transaction" << endl;
        cout << "  [2] Go back to Choose Route" << endl;
        cout << endl;
        cout << "   Your option : ";
        cin >> selection;

        if (selection == 1) {
            TransactionPage(sourceID, destinationID, totalFair, totalTime);
        }
        else if (selection == 2) {
            ChooseRoute();
        }
        else {
            cout << endl;
            cout << "  Wrong Option have been selected!" << endl;
            TwoCity(sourceID, destinationID, route);

        }

    }

}


//Displaying transaction page as well as creating it node
void TransactionPage(string sourceID, string destinationID, double totalfair, int totalTime) {

    tranCurrent = tranHead;
    sCurrent = sHead;
    string transID, SourceName, DestinationName, PassengerID, PassengerName, PassengerUsername;
    int PassengerIC, convertingID;
    double TicketAmount;
    std::ostringstream newtID;


    if (tranCurrent == NULL) {
        transID = "T000";
    }
    else {

        while (tranCurrent != NULL) {
            if (tranCurrent->tranNextAddress == NULL)
            {
                transID = tranCurrent->tranID;
            }
            tranTail = tranCurrent;
            tranCurrent = tranCurrent->tranNextAddress;
        }
    }

    string RegispID;
    int convertID;
    std::ostringstream newpID;

    transID = transID.substr(1);
    convertingID = std::stoi(transID) + 1;
    newtID << "T" << std::setw(3) << std::setfill('0') << convertingID;
    transID = newtID.str();

    while (sCurrent != NULL) {
        if (sCurrent->sID.find(sourceID) != string::npos)
        {
            SourceName = sCurrent->sName;
        }
        sCurrent = sCurrent->sNextAddress;
    }
    sCurrent = sHead;

    while (sCurrent != NULL) {
        if (sCurrent->sID.find(destinationID) != string::npos)
        {
            DestinationName = sCurrent->sName;
        }
        sCurrent = sCurrent->sNextAddress;
    }


    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    time_t start_time = std::chrono::system_clock::to_time_t(start);
    time_t end_time = std::chrono::system_clock::to_time_t(end) + (totalTime * 60);

    string CurrentTime = std::ctime(&start_time);
    string ArrivalTime = std::ctime(&end_time);

    PassengerName = pCurrent->pName;
    PassengerID = pCurrent->pID;
    PassengerIC = pCurrent->pIC;
    PassengerUsername = pCurrent->pUsername;
    TicketAmount = totalfair;


    cout << endl;
    cout << endl;
    cout << endl;
    cout << "  " << "                                      Welcome to the Payment Page !!" << endl;
    cout << "  " << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "  " << "===============================" << endl;
    cout << "  " << "|Here Are Your Payment Details|" << endl;
    cout << "  " << "===============================" << endl << endl;

    cout << "  " << "Transaction ID     : " << transID << endl;
    cout << "  " << "Passenger ID       : " << pCurrent->pID << endl;
    cout << "  " << "Passenger Name     : " << pCurrent->pName << endl;
    cout << "  " << "Passenger Username : " << pCurrent->pUsername << endl;
    cout << "  " << "Pasenger IC        : " << pCurrent->pIC << endl;
    cout << "  " << "Source Station     : " << SourceName << endl;
    cout << "  " << "Destination Station: " << DestinationName << endl;
    cout << "  " << "Departure Time     : " << CurrentTime;
    cout << "  " << "Arrival Time       : " << ArrivalTime;
    cout << "  " << "___________________________" << endl;
    cout << "  " << "Total Amount       : " << " RM" << totalfair << endl << endl;
    cout << "  " << "Do You Want to Confirm Your Transaction?" << endl;
    cout << "  " << "[1] Confirm My Transaction" << endl;
    cout << "  " << "[2] I Would Like to Change My Mind" << endl << endl;;
    cout << "  " << "Your Option: ";
    do
    {

        if (!(cin >> selection))
        {
            cout << endl;
            cout << "  " << "Invalid input! Please enter proper input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if ((selection >= 1) && (selection <= 2)) {
            if (selection == 1) {
                Transaction* tranNewnode = createtransactionNewNode(transID, SourceName, DestinationName, CurrentTime, ArrivalTime, PassengerID, PassengerName, PassengerUsername, PassengerIC, TicketAmount);
                insertTransactionEnd(tranNewnode);
                /*insertTransactionFront(tranNewnode);*/
                //displayTranFromtheFront();
                cout << "  " << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "  " << "                                       TRANSACTION SUCCESSFULLY ADDED                        " << endl;
                cout << "  " << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl << endl;
                //displayTranFromtheFront();
                cout << "  " << "Do You Want to Book Another Ticket?" << endl;
                cout << "  " << "[1] Yes" << endl;
                cout << "  " << "[2] No" << endl;
                cout << "  " << "Your Option: ";

                if (!(cin >> selection))
                {
                    cout << "Invalid input! Please enter proper input." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if ((selection >= 1) && (selection <= 2)) {
                    if (selection == 1) {
                        ChooseRoute();
                    }
                    else if (selection == 2) {
                        cout << "\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                        cout << "                            THANK YOU FOR USING THE SUBWAY TICKET BOOKING SERVICE                         " << endl;
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                        PassengerMainMenu();
                    }
                    break;
                }

            }
            else if (selection == 2) {
                cout << "\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "                                       RETURNING BACK TO MAIN MENU                        " << endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                PassengerMainMenu();
            }
            break;
        }
        cout << endl;
        cout << "  " << "Please enter a valid option number [1-2]! " << endl;
    } while (true);

}

//Delete the speicific transaction by inputting the ID
void deletefromspecificlocation(string transID)
{

    Transaction* temp = tranHead;
    Transaction* prev = NULL;

    if (tranHead == NULL)
    {
        cout << "  " << "There is no transaction available" << endl;
        return;
    }


    if (temp != NULL && temp->tranID == transID) {
        tranHead = temp->tranNextAddress;
        delete temp;
        cout << endl;
        cout << "  " << "=====================================" << endl;
        cout << "  " << "|TRANSACTION " << transID << " DELETED|" << endl;
        cout << "  " << "=====================================" << endl;
        return;
    }
    else {
        while (temp != NULL && temp->tranID != transID)
        {
            prev = temp;
            temp = temp->tranNextAddress;
        }
        if (temp == NULL)
        {
            cout << endl;
            cout << "  " << "=========================" << endl;
            cout << "  " << "| TRANSACTION NOT FOUND |" << endl;
            cout << "  " << "=========================" << endl;
            return;
        }
        prev->tranNextAddress = temp->tranNextAddress;
        delete temp;
        cout << "  " << "=====================================" << endl;
        cout << "  " << "|TRANSACTION " << transID << " DELETED|" << endl;
        cout << "  " << "=====================================" << endl;
    }


    SearchTransaction();
}

//Displaying all transaction and also ask user if they want to delete
void DisplayAllTransaction() {
    cout << endl;
    cout << endl;
    cout << endl;
    tranCurrent = tranHead;

    //calling sorting algorithm
    SelectionSortByTransactionID();

    if (tranCurrent == NULL) {
        cout << "  " << "============================================================================" << endl;
        cout << "  " << "|User Transaction Information Empty !! PLEASE TRY TO BOOK TRANSACTION FIRST|" << endl;
        cout << "  " << "============================================================================";
    }
    else {
        if (tranCurrent->pUsername.find(passengerUsername) != string::npos) {
            while (tranCurrent != NULL) {
                if (tranCurrent->tranID == "NULL") {
                    cout << "  " << "Transaction ID         : " << " - " << endl;
                }
                else {
                    cout << "  " << "Transaction ID         : " << tranCurrent->tranID << endl;
                }


                if (tranCurrent->pID == "NULL") {
                    cout << "  " << "Passenger ID           : " << " - " << endl;
                }
                else {
                    cout << "  " << "Passenger ID           : " << tranCurrent->pID << endl;
                }

                if (tranCurrent->pName == "NULL") {
                    cout << "  " << "Passenger Name         : " << " - " << endl;
                }
                else {
                    cout << "  " << "Passenger Name         : " << tranCurrent->pName << endl;
                }

                if (tranCurrent->pIC == NULL) {
                    cout << "  " << "Passenger IC           : " << " - " << endl;
                }
                else {
                    cout << "  " << "Passenger IC           : " << tranCurrent->pIC << endl;
                }

                if (tranCurrent->sSrc == "NULL") {
                    cout << "  " << "Source Station         : " << " - " << endl;
                }
                else {
                    cout << "  " << "Source Station         : " << tranCurrent->sSrc << endl;
                }

                if (tranCurrent->sVenue == "NULL") {

                    cout << "  " << "Destination Station    : " << " - " << endl;
                }
                else {

                    cout << "  " << "Destination Station    : " << tranCurrent->sVenue << endl;
                }

                if (tranCurrent->departTime == "NULL") {
                    cout << "  " << "Departure Time         : ";
                }
                else {
                    cout << "  " << "Departure Time         : " << tranCurrent->departTime;
                }

                if (tranCurrent->arrivalTime == "NULL") {
                    cout << "  " << "Arrival Time           : ";
                }
                else {
                    cout << "  " << "Arrival Time           : " << tranCurrent->departTime;
                }

                if (tranCurrent->tTickAmt == NULL) {
                    cout << "  " << "Ticket Amount          : " << " - " << endl;
                }
                else {
                    cout << "  " << "Ticket Amount          : " << "RM " << tranCurrent->tTickAmt << endl;
                }
                cout << endl;
                cout << "  ------------------------------------------------";
                cout << endl;

                tranCurrent = tranCurrent->tranNextAddress;
            }
        }
        cout << endl << endl;
        cout << "  " << "[1] Delete Transaction " << endl;
        cout << "  " << "[2] Go Back to Search Transaction " << endl;
        cout << "  " << "Your Option: ";
        cin >> selection;

        if (selection == 1)
        {
            string deleteTranID;
            cout << "  " << "Enter Transaction ID You Want to Delete:  ";
            cin >> deleteTranID;
            deletefromspecificlocation(deleteTranID);
        }
        else if (selection == 2)
        {
            cout << endl;
            cout << endl;
            SearchTransaction();
        }

    }
    cout << endl;
    cout << endl;
    SearchTransaction();
}

//specific subway station detail
void DisplaySpecificTransaction() {
    selection = 0;
    string transactionID, pName, pID, sStation, dStation, ArrivalTime, DepartTime, pUsername;
    int pIC;
    double TotalAmount;
    bool checkTransID = true;
    tranCurrent = tranHead;

    if (tranCurrent == NULL) {
        cout << "  " << "============================================================================" << endl;
        cout << "  " << "|User Transaction Information Empty !! PLEASE TRY TO BOOK TRANSACTION FIRST|" << endl;
        cout << "  " << "============================================================================" << endl;
        cout << endl << endl;
    }
    else {

        cout << endl;
        cout << "  ===========================================" << endl;
        cout << "  [1] Search Specific Transaction " << endl;
        cout << "  [2] Back to Transaction Menu" << endl;
        cout << "  ===========================================" << endl;
        cout << endl;
        cout << "  Your selection : ";
        cin >> selection;

        if (selection == 1) {
            cout << endl;
            cout << "  Enter Transaction ID (eg: T001) : ";
            cin >> transactionID;

            while (tranCurrent != NULL) {
                if (tranCurrent->tranID == transactionID) {
                    checkTransID = false;
                    pName = tranCurrent->pName;
                    pID = tranCurrent->pID;
                    pIC = tranCurrent->pIC;
                    sStation = tranCurrent->sSrc;
                    dStation = tranCurrent->sVenue;
                    ArrivalTime = tranCurrent->arrivalTime;
                    DepartTime = tranCurrent->departTime;
                    TotalAmount = tranCurrent->tTickAmt;
                }
                tranCurrent = tranCurrent->tranNextAddress;
            }
        }
        else if (selection == 2) {
            SearchTransaction();
        }
        else {
            cout << "  " << "Invalid selection input !" << endl;
            DisplaySpecificTransaction();
        }


        if (checkTransID) {
            cout << endl;
            cout << "      Transaction ID not exist !" << endl;
        }
        else {
            cout << "\n\n      Entered Transaction Information: " << endl;
            cout << "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl;
            cout << "  " << transactionID << " - " << pName << endl;
            cout << endl;

            if (pID == "NULL") {
                cout << "  " << "Passenger ID           : " << " - " << endl;
            }
            else {
                cout << "  " << "Passenger ID           : " << pID << endl;
            }

            if (pName == "NULL") {
                cout << "  " << "Passenger Name         : " << " - " << endl;
            }
            else {
                cout << "  " << "Passenger Name         : " << pName << endl;
            }

            if (pIC == NULL) {
                cout << "  " << "Passenger IC           : " << " - " << endl;
            }
            else {
                cout << "  " << "Passenger IC           : " << pIC << endl;
            }

            if (sStation == "NULL") {
                cout << "  " << "Source Station         : " << " - " << endl;
            }
            else {
                cout << "  " << "Source Station         : " << sStation << endl;
            }

            if (dStation == "NULL") {

                cout << "  " << "Destination Station    : " << " - " << endl;
            }
            else {

                cout << "  " << "Destination Station    : " << dStation << endl;
            }

            if (DepartTime == "NULL") {
                cout << "  " << "Departure Time         : ";
            }
            else {
                cout << "  " << "Departure Time         : " << DepartTime;
            }

            if (ArrivalTime == "NULL") {
                cout << "  " << "Arrival Time           : ";
            }
            else {
                cout << "  " << "Arrival Time           : " << ArrivalTime;
            }

            if (TotalAmount == NULL) {
                cout << "  " << "Ticket Amount          : " << " - " << endl;
            }
            else {
                cout << "  " << "Ticket Amount          : " << "RM " << TotalAmount << endl;
            }

            cout << endl;
        }

    }

    SearchTransaction();
}

// Search transaction depend on user option
void SearchTransaction() {

    selection = 0;
    cout << "" << endl;
    cout << "                                                           View Transaction Details" << endl;
    cout << separator << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "   Menu Options [1-3]: " << endl;
    cout << "" << endl;
    cout << "   [1] View All Transaction Details " << endl;
    cout << "   [2] Search Transaction Detail" << endl;
    cout << "   [3] Exit to Passanger Main Menu" << endl;;
    cout << "" << endl;
    cout << "   Your Option: ";

    do
    {
        if (!(cin >> selection))
        {
            cout << endl;
            cout << "  " << "Invalid input! Please enter proper input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if ((selection >= 1) && (selection <= 3)) {
            if (selection == 1) {
                //selectionLinked();
                DisplayAllTransaction();
            }
            else if (selection == 2) {
                DisplaySpecificTransaction();
            }
            else if (selection == 3) {
                PassengerMainMenu();
            }
            break;
        }
        cout << endl;
        cout << "  " << "Please enter a valid option number [1-3]! " << endl;
    } while (true);
}

//Display the Subway Station
void ChooseRoute()
{
    selection = 0;
    cout << "" << endl;
    cout << "" << endl;
    cout << "                                                                                 Route Selection Menu!" << endl;
    cout << separator << endl;
    cout << "" << endl;
    cout << "   Choose the Route You Want to Take: " << endl;
    cout << endl;

    sCurrent = sHead;

    cout << "     [ Station Starts Here ]     ";

    std::ostringstream firstRoute;
    string formatRoute;

    while (sCurrent != NULL)
    {
        firstRoute << sCurrent->sName + "  ->  ";
        formatRoute = firstRoute.str();

        sCurrent = sCurrent->sNextAddress;
    }

    //erasing the last arrow
    cout << formatRoute.erase(formatRoute.length() - 5);

    if (sCurrent == NULL)
    {
        cout << "     [ Station Ends Here ]" << endl;
    }

    cout << "" << endl;
    cout << "                                                                                  or" << endl;
    cout << "" << endl;

    //display entire route with two way arrows
    sCurrent = sTail;


    cout << "     [ Station Starts Here ]     ";

    std::ostringstream secondRoute;
    string formatSecondRoute;

    while (sCurrent != NULL)
    {

        secondRoute << sCurrent->sName + "  ->  ";
        formatSecondRoute = secondRoute.str();

        sCurrent = sCurrent->sPrevAddress;

    }

    //erasing the last arrow
    cout << formatSecondRoute.erase(formatSecondRoute.length() - 5);

    if (sCurrent == NULL)
    {
        cout << "     [ Station Ends Here ]" << endl;
    }

    cout << endl;
    cout << endl;

    //User options
    cout << "   [1] Titiwangsa to Chan Sow Lin" << endl;
    cout << "   [2] Chan Sow Lin to Titiwangsa" << endl;
    cout << "   [3] Exit Main Menu" << endl;
    cout << "" << endl;
    cout << "   Your option : ";


    do {
        if (!(cin >> selection))
        {
            cout << "  " << "Invalid input! Please enter proper input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << endl;
        if ((selection >= 1) && (selection <= 3)) {
            if (selection == 1) {
                sCurrent = sHead;

                std::ostringstream firstID, firstFair, firstRoute, firstDistance;
                string formatFirstID, formatFirstFair, formatFirstRoute, formatFirstDistance;

                while (sCurrent != NULL)
                {
                    int numberCharName = size(sCurrent->sName);
                    firstFair << std::string(numberCharName, ' ') << "        RM " << setprecision(2) << fixed << sCurrent->sNextFair << "    ";
                    firstRoute << "(" << sCurrent->sID << ")" << sCurrent->sName + "  -------->  ";
                    firstDistance << std::string(numberCharName, ' ') << "        " << sCurrent->sNextDistance << " KM" << "       ";

                    formatFirstFair = firstFair.str();
                    formatFirstRoute = firstRoute.str();
                    formatFirstDistance = firstDistance.str();

                    sCurrent = sCurrent->sNextAddress;
                }

                //erasing the last arrow and displaying it
                cout << "  Fair    " << formatFirstFair.erase(formatFirstFair.length() - 11);
                cout << endl;
                cout << endl;
                cout << endl;
                cout << "          " << formatFirstRoute.erase(formatFirstRoute.length() - 11);
                cout << endl;
                cout << endl;
                cout << endl;
                cout << "  Distance  " << formatFirstDistance.erase(formatFirstDistance.length() - 11);
                cout << endl;
                cout << endl;

                string routeFrom = "Head";
                CheckTwoCity(routeFrom);

            }
            else if (selection == 2) {
                sCurrent = sTail;
                std::ostringstream secondFair, secondRoute, secondDistance;
                string formatSecondFair, formatSecondRoute, formatSecondDistance;

                while (sCurrent != NULL)
                {

                    int numberCharName = size(sCurrent->sName);
                    secondFair << std::string(numberCharName, ' ') << "        RM " << setprecision(2) << fixed << sCurrent->sPrevFair << "    ";
                    secondRoute << "(" << sCurrent->sID << ")" << sCurrent->sName + "  -------->  ";
                    secondDistance << std::string(numberCharName, ' ') << "        " << sCurrent->sPrevDistance << " KM" << "       ";

                    formatSecondFair = secondFair.str();
                    formatSecondRoute = secondRoute.str();
                    formatSecondDistance = secondDistance.str();

                    sCurrent = sCurrent->sPrevAddress;
                }

                //erasing the last arrow and displaying it
                cout << "  Fair      " << formatSecondFair.erase(formatSecondFair.length() - 11);
                cout << endl;
                cout << endl;
                cout << endl;
                cout << "          " << formatSecondRoute.erase(formatSecondRoute.length() - 11);
                cout << endl;
                cout << endl;
                cout << endl;
                cout << "  Distance   " << formatSecondDistance.erase(formatSecondDistance.length() - 11);
                cout << endl;
                cout << endl;

                string routeFrom = "Tail";
                CheckTwoCity(routeFrom);
            }
            else if (selection == 3) {
                PassengerMainMenu();
            }
            break;

        }
        cout << "  " << "Please enter a valid option number [1-3]! " << endl;
    } while (true);

}

//Sorting the transactionID by descending order
void SelectionSortByTransactionID()
{
    string selectedSort = "default";

    Transaction* sortTransaction = tranHead;

    // Traverse the List
    while (sortTransaction) {
        Transaction* min = sortTransaction;
        Transaction* r = sortTransaction->tranNextAddress;

        // Traverse the unsorted sublist
        while (r) {
            if (min->tranID < r->tranID)
                min = r;

            r = r->tranNextAddress;
        }

        // Swap Data
        string tempTranID = sortTransaction->tranID;
        string tempSourceID = sortTransaction->sSrc;
        string tempDestinationID = sortTransaction->sVenue;
        string tempDepartTime = sortTransaction->departTime;
        string tempArrivalTime = sortTransaction->arrivalTime;
        string tempPID = sortTransaction->pID;
        string tempPName = sortTransaction->pName;
        string tempPUsername = sortTransaction->pUsername;
        int tempPIC = sortTransaction->pIC;
        double tempTicket = sortTransaction->tTickAmt;

        sortTransaction->tranID = min->tranID;
        sortTransaction->sSrc = min->sSrc;
        sortTransaction->sVenue = min->sVenue;
        sortTransaction->departTime = min->departTime;
        sortTransaction->arrivalTime = min->arrivalTime;
        sortTransaction->pID = min->pID;
        sortTransaction->pName = min->pName;
        sortTransaction->pUsername = min->pUsername;
        sortTransaction->pIC = min->pIC;
        sortTransaction->tTickAmt = min->tTickAmt;


        min->tranID = tempTranID;
        min->sSrc = tempSourceID;
        min->sVenue = tempDestinationID;
        min->departTime = tempDepartTime;
        min->arrivalTime = tempArrivalTime;
        min->pID = tempPID;
        min->pName = tempPName;
        min->pUsername = tempPUsername;
        min->pIC = tempPIC;
        min->tTickAmt = tempTicket;

        sortTransaction = sortTransaction->tranNextAddress;

    }
}

//ADMIN START HERE -----------------------------------------------------------------------------------

//Displaying the subway station
void DisplayAdminSubwayStation()
{
    const char separator = ' ';
    const int nameWidth = 16;
    const int numWidth = 16;
    sCurrent = sHead;

    cout << "  " << left << setw(nameWidth) << setfill(separator) << "ID";
    cout << left << setw(nameWidth) << setfill(separator) << "Name";
    cout << left << setw(nameWidth) << setfill(separator) << "Prev ID";
    cout << left << setw(nameWidth) << setfill(separator) << "Next ID";
    cout << left << setw(nameWidth) << setfill(separator) << "Nearby Spots";
    cout << "  " << left << setw(nameWidth) << setfill(separator) << "Prev Distance";
    cout << left << setw(nameWidth) << setfill(separator) << "Next Distance";
    cout << left << setw(nameWidth) << setfill(separator) << "Prev Time";
    cout << left << setw(nameWidth) << setfill(separator) << "Next Time";
    cout << left << setw(nameWidth) << setfill(separator) << "Prev Fair";
    cout << left << setw(nameWidth) << setfill(separator) << "Next Fair";
    cout << endl;

    while (sCurrent != NULL)
    {
        cout << "  " << left << setw(numWidth) << setfill(separator) << sCurrent->sID;
        cout << left << setw(numWidth) << setfill(separator) << sCurrent->sName;
        cout << left << setw(numWidth) << setfill(separator) << sCurrent->sPrevID;
        cout << left << setw(numWidth) << setfill(separator) << sCurrent->sNextID;
        cout << left << setw(numWidth) << setfill(separator) << sCurrent->sNearbySpot;
        cout << "  " << left << setw(numWidth) << setfill(separator) << sCurrent->sPrevDistance;
        cout << left << setw(numWidth) << setfill(separator) << sCurrent->sNextDistance;
        cout << left << setw(numWidth) << setfill(separator) << sCurrent->sPrevTravelTime;
        cout << left << setw(numWidth) << setfill(separator) << sCurrent->sNextTravelTime;
        cout << left << setw(numWidth) << setfill(separator) << sCurrent->sPrevFair;
        cout << left << setw(numWidth) << setfill(separator) << sCurrent->sNextFair;
        cout << endl;
        sCurrent = sCurrent->sNextAddress;
    }
    cout << endl;
}

//validation Station ID
bool isSID(string sID) {
    bool foundID = false;
    sCurrent = sHead;
    while (sCurrent != NULL)
    {
        if (sCurrent->sID == sID) {
            foundID = true;
        }

        sTail = sCurrent;
        sCurrent = sCurrent->sNextAddress;

    }

    return foundID;
}

//Search and edit the subway station
void EditSubwayStationDetails(string sID)
{
    bool checkStationID = true;
    sCurrent = sHead;

    while (sCurrent != NULL)
    {
        if (sCurrent->sID == sID)
        {
            checkStationID = false;
            cout << "  Enter updated previous fare: " << endl;
            cin >> sCurrent->sPrevFair;
            cout << "  Enter updated next station fare: " << endl;
            cin >> sCurrent->sNextFair;
            cout << "  Enter travel time from previous station: " << endl;
            cin >> sCurrent->sPrevTravelTime;
            cout << "  Enter travel time to next station: " << endl;
            cin >> sCurrent->sNextTravelTime;
            cout << "  Enter updated station name: " << endl;
            getline(cin, sCurrent->sName);
            cout << "  Update.....Done!" << endl;

        }
        sCurrent = sCurrent->sNextAddress;
    }
    if (checkStationID) {
        cout << endl << endl;
        cout << "  No Station ID Found" << endl << endl;
    }
}

//Delete the customer ticket information
void DeletePassengerTicketInfo(string tranID)
{
    Transaction* temp = tranHead;
    Transaction* prev = NULL;

    tranCurrent = tranHead;

    if (tranCurrent == NULL) {
        cout << "  " << "============================================================================" << endl;
        cout << "  " << "|User Transaction Information Empty !! PLEASE TRY TO BOOK TRANSACTION FIRST|" << endl;
        cout << "  " << "============================================================================";
    }

    if (temp != NULL && temp->tranID == tranID) {
        tranHead = temp->tranNextAddress;
        delete temp;
        cout << endl;
        cout << "  " << "=====================================" << endl;
        cout << "  " << "|TRANSACTION " << tranID << " DELETED|" << endl;
        cout << "  " << "=====================================" << endl;
        return;
    }
    else {
        while (temp != NULL && temp->tranID != tranID)
        {
            prev = temp;
            temp = temp->tranNextAddress;
        }
        if (temp == NULL)
        {
            cout << endl;
            cout << "  " << "=========================" << endl;
            cout << "  " << "| TRANSACTION NOT FOUND |" << endl;
            cout << "  " << "=========================" << endl;
            return;
        }
        prev->tranNextAddress = temp->tranNextAddress;
        delete temp;
        cout << "  " << "=====================================" << endl;
        cout << "  " << "|TRANSACTION " << tranID << " DELETED|" << endl;
        cout << "  " << "=====================================" << endl;
    }

}


//Search and edit customer ticket information
void EditTicketTransactionDetails(string tranID)
{
    bool checkTransactionID = true;
    tranCurrent = tranHead;
    if (tranCurrent == NULL) {
        cout << "  " << "============================================================================" << endl;
        cout << "  " << "|User Transaction Information Empty !! PLEASE TRY TO BOOK TRANSACTION FIRST|" << endl;
        cout << "  " << "============================================================================";
    }

    while (tranCurrent != NULL)
    {
        if (tranCurrent->tranID == tranID)
        {
            checkTransactionID = false;
            cout << "  Enter updated source station: " << endl;
            cin >> tranCurrent->sSrc;
            cout << "  Enter updated destination station: " << endl;
            cin >> tranCurrent->sVenue;
            cout << "  Enter updated departing time: " << endl;
            cin >> tranCurrent->departTime;
            cout << "  Enter updated arrival time: " << endl;
            cin >> tranCurrent->arrivalTime;
            cout << "  Update.....Done!" << endl;

        }
        tranCurrent = tranCurrent->tranNextAddress;
    }
    if (checkTransactionID) {
        cout << endl << endl;
        cout << "  No Transaction ID Found" << endl << endl;
    }

}

//display customer transaction
void DisplayPurchaseTransaction()
{
    string tranID, sSrc, sVenue, departTime, arrivalTime, pID, pName, pUsername;
    double  tTickAmt;
    int pIC;

    const char separator = ' ';
    const int nameWidth = 16;
    const int numWidth = 16;
    tranCurrent = tranHead;


    if (tranCurrent == NULL) {
        cout << "  " << "============================================================================" << endl;
        cout << "  " << "|User Transaction Information Empty !! PLEASE TRY TO BOOK TRANSACTION FIRST|" << endl;
        cout << "  " << "============================================================================";
    }
    else
    {

        cout << "  " << left << setw(nameWidth) << setfill(separator) << "Transaction ID";
        cout << left << setw(nameWidth) << setfill(separator) << "Source";
        cout << left << setw(nameWidth) << setfill(separator) << "Destination";
        cout << left << setw(nameWidth) << setfill(separator) << "Depart Time";
        cout << left << setw(nameWidth) << setfill(separator) << "Arrival Time";
        cout << left << setw(nameWidth) << setfill(separator) << "ID";
        cout << left << setw(nameWidth) << setfill(separator) << "Name";
        cout << left << setw(nameWidth) << setfill(separator) << "Username";
        cout << left << setw(nameWidth) << setfill(separator) << "IC";
        cout << left << setw(nameWidth) << setfill(separator) << "Ticket Amount";
        cout << endl;

        while (tranCurrent != NULL)
        {
            cout << "  " << left << setw(numWidth) << setfill(separator) << tranCurrent->tranID;
            cout << left << setw(numWidth) << setfill(separator) << tranCurrent->sSrc;
            cout << left << setw(numWidth) << setfill(separator) << tranCurrent->sVenue;
            cout << left << setw(numWidth) << setfill(separator) << tranCurrent->departTime;
            cout << left << setw(numWidth) << setfill(separator) << tranCurrent->arrivalTime;
            cout << left << setw(numWidth) << setfill(separator) << tranCurrent->pID;
            cout << left << setw(numWidth) << setfill(separator) << tranCurrent->pName;
            cout << left << setw(numWidth) << setfill(separator) << tranCurrent->pUsername;
            cout << left << setw(numWidth) << setfill(separator) << tranCurrent->pIC;
            cout << left << setw(numWidth) << setfill(separator) << tranCurrent->tTickAmt;
            cout << endl;
            tranCurrent = tranCurrent->tranNextAddress;
        }
        cout << endl;
    }
}

//Sorting the passenger name by ascending order
void SelectionSortPassengerName() {

    //string selectedSort = "default";

    Transaction* sortTransaction = tranHead;

    // Traverse the List
    while (sortTransaction) {
        Transaction* min = sortTransaction;
        Transaction* r = sortTransaction->tranNextAddress;

        // Traverse the unsorted sublist
        while (r) {
            if (min->pName > r->pName)
                min = r;

            r = r->tranNextAddress;
        }

        // Swap Data
        string tempTranID = sortTransaction->tranID;
        string tempSourceID = sortTransaction->sSrc;
        string tempDestinationID = sortTransaction->sVenue;
        string tempDepartTime = sortTransaction->departTime;
        string tempArrivalTime = sortTransaction->arrivalTime;
        string tempPID = sortTransaction->pID;
        string tempPName = sortTransaction->pName;
        string tempPUsername = sortTransaction->pUsername;
        int tempPIC = sortTransaction->pIC;
        double tempTicket = sortTransaction->tTickAmt;

        sortTransaction->tranID = min->tranID;
        sortTransaction->sSrc = min->sSrc;
        sortTransaction->sVenue = min->sVenue;
        sortTransaction->departTime = min->departTime;
        sortTransaction->arrivalTime = min->arrivalTime;
        sortTransaction->pID = min->pID;
        sortTransaction->pName = min->pName;
        sortTransaction->pUsername = min->pUsername;
        sortTransaction->pIC = min->pIC;
        sortTransaction->tTickAmt = min->tTickAmt;


        min->tranID = tempTranID;
        min->sSrc = tempSourceID;
        min->sVenue = tempDestinationID;
        min->departTime = tempDepartTime;
        min->arrivalTime = tempArrivalTime;
        min->pID = tempPID;
        min->pName = tempPName;
        min->pUsername = tempPUsername;
        min->pIC = tempPIC;
        min->tTickAmt = tempTicket;

        sortTransaction = sortTransaction->tranNextAddress;

    }
}

//displaying passenger by name 
void displayPassengerByName()
{
    cout << endl;
    cout << endl;
    cout << endl;
    tranCurrent = tranHead;
    if (tranCurrent == NULL) {
        cout << "  " << "============================================================================" << endl;
        cout << "  " << "|User Transaction Information Empty !! PLEASE TRY TO BOOK TRANSACTION FIRST|" << endl;
        cout << "  " << "============================================================================";
    }

    //calling the method to sort it
    SelectionSortPassengerName();

    while (tranCurrent != NULL) {
        if (tranCurrent->tranID == "NULL") {
            cout << "  " << "Transaction ID         : " << " - " << endl;
        }
        else {
            cout << "  " << "Transaction ID         : " << tranCurrent->tranID << endl;
        }


        if (tranCurrent->pID == "NULL") {
            cout << "  " << "Passenger ID           : " << " - " << endl;
        }
        else {
            cout << "  " << "Passenger ID           : " << tranCurrent->pID << endl;
        }

        if (tranCurrent->pName == "NULL") {
            cout << "  " << "Passenger Name         : " << " - " << endl;
        }
        else {
            cout << "  " << "Passenger Name         : " << tranCurrent->pName << endl;
        }

        if (tranCurrent->pIC == NULL) {
            cout << "  " << "Passenger IC           : " << " - " << endl;
        }
        else {
            cout << "  " << "Passenger IC           : " << tranCurrent->pIC << endl;
        }

        if (tranCurrent->sSrc == "NULL") {
            cout << "  " << "Source Station         : " << " - " << endl;
        }
        else {
            cout << "  " << "Source Station         : " << tranCurrent->sSrc << endl;
        }

        if (tranCurrent->sVenue == "NULL") {

            cout << "  " << "Destination Station    : " << " - " << endl;
        }
        else {

            cout << "  " << "Destination Station    : " << tranCurrent->sVenue << endl;
        }

        if (tranCurrent->departTime == "NULL") {
            cout << "  " << "Departure Time         : ";
        }
        else {
            cout << "  " << "Departure Time         : " << tranCurrent->departTime;
        }

        if (tranCurrent->arrivalTime == "NULL") {
            cout << "  " << "Arrival Time           : ";
        }
        else {
            cout << "  " << "Arrival Time           : " << tranCurrent->departTime;
        }

        if (tranCurrent->tTickAmt == NULL) {
            cout << "  " << "Ticket Amount          : " << " - " << endl;
        }
        else {
            cout << "  " << "Ticket Amount          : " << "RM " << tranCurrent->tTickAmt << endl;
        }
        cout << endl;
        cout << "  ------------------------------------------------";
        cout << endl;

        tranCurrent = tranCurrent->tranNextAddress;
    }
}


//Main admin menu
void AdminMainMenu()
{
    cout << endl << endl << endl << endl;
    cout << "" << endl;
    cout << "                                                                               Welcome back Admin " << " !" << endl;
    cout << "" << endl;
    cout << "                                                           Kuala Lumpur Light Rail Transit (LRT) - Titiwangsa Station - Chan Sow Lin Station Route" << endl;
    cout << separator << endl;
    cout << "" << endl;
    cout << "                                                                   Current Subway Station List" << endl << endl << endl;
    DisplayAdminSubwayStation();

    int loop = 0;
    string tranID;
    string sID;
    string sName;
    string sPrevID;
    string sNextID;
    string sNearbySpot;
    double sPrevFair;
    double sNextFair;
    int sPrevDistance;
    int sNextDistance;
    int sPrevTravelTime;
    int sNextTravelTime;
    int decision;

    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "   Menu Options [1-7]: " << endl;
    cout << "" << endl;
    cout << "   [1] Add Subway Station" << endl;
    cout << "   [2] Edit Subway Station" << endl;
    cout << "   [3] Sort Transaction by Passenger Name" << endl;
    cout << "   [4] View Transaction" << endl;
    cout << "   [5] Search and Edit Customer Ticket Information" << endl;
    cout << "   [6] Delete Customer Ticket Information" << endl;
    cout << "   [7] Logout " << endl;
    cout << "" << endl;
    cout << "   Your Option: ";
    do
    {
        if (!(cin >> selection))
        {
            cout << "  Invalid input! Please enter proper input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if ((selection >= 1) && (selection <= 7)) {
            if (selection == 1) {
                cout << endl << endl << endl;
                cout << "                       ADD NEW SUBWAY STATION  " << endl << endl;
                cout << endl << endl;
                cout << "   [1] Insert start list" << endl;
                cout << "   [2] Insert end list" << endl << endl;
                cout << "   Your Option: ";
                cin >> decision;

                if (decision == 1) {
                    cout << endl;
                    do {
                        cout << "  Enter Subway ID (eg: S001): ";
                        cin >> sID;
                        bool StationID = isSID(sID);
                        if (StationID) {
                            cout << "\n\n                             Station ID Already Taken !! Please Try Again\n\n" << endl;
                            continue;
                        }
                        cout << "  Enter Subway Name: ";
                        getline(cin >> ws, sName);
                        cout << "  Nearby Spot: ";
                        getline(cin >> ws, sNearbySpot);
                        cout << "  Fare from Next Station (RM): ";
                        cin >> sNextFair;

                        if (!sNextFair)
                        {
                            cout << endl;
                            cout << "                              Invalid Next Fair input !! Please Try Again with numbers only\n\n" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        cout << "  Next Station Distance (KM): ";
                        cin >> sNextDistance;

                        if (!sNextDistance)
                        {
                            cout << endl;
                            cout << "                              Invalid Next Distance input !! Please Try Again with numbers only\n\n" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        cout << "  Travel Time for Next Station (MIN): ";
                        cin >> sNextTravelTime;


                        if (!sNextTravelTime)
                        {
                            cout << endl;
                            cout << "                              Invalid Next Travel Time input !! Please Try Again with numbers only\n\n" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        //setting previous details as null
                        sPrevID = "NULL";
                        sPrevFair = NULL;
                        sPrevDistance = NULL;
                        sPrevTravelTime = NULL;
                        break;
                    } while (true);

                    //getting the current first node of subway station
                    sCurrent = sHead;
                    sNextID = sCurrent->sID;

                    SubwayStation* sNewnode = createSubwayNewNode(sID, sName, sPrevID, sNextID, sNearbySpot, sPrevFair, sNextFair, sPrevDistance, sNextDistance, sPrevTravelTime, sNextTravelTime);
                    insertToFrontOfList(sNewnode);

                    //Updating Previous Details of First Station
                    sCurrent->sPrevID = sID;
                    sCurrent->sPrevFair = sNextFair;
                    sCurrent->sPrevDistance = sNextDistance;
                    sCurrent->sPrevTravelTime = sNextTravelTime;


                }
                else if (decision == 2) {
                    cout << endl;
                    do {
                        cout << "  Enter Subway ID (eg: S001): ";
                        cin >> sID;
                        bool StationID = isSID(sID);
                        if (StationID) {
                            cout << "\n\n                             Station ID Already Taken !! Please Try Again\n\n" << endl;
                            continue;
                        }
                        cout << "  Enter Subway Name: ";
                        getline(cin >> ws, sName);
                        cout << "  Nearby Spot: ";
                        getline(cin >> ws, sNearbySpot);
                        cout << "  Fare from Prev Station (RM): ";
                        cin >> sPrevFair;

                        if (!sPrevFair)
                        {
                            cout << endl;
                            cout << "                              Invalid Previous Fair input !! Please Try Again with numbers only\n\n" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        cout << "  Prev Station Distance (KM): ";
                        cin >> sPrevDistance;

                        if (!sPrevDistance)
                        {
                            cout << endl;
                            cout << "                              Invalid Previous Distance input !! Please Try Again with numbers only\n\n" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        cout << "  Travel Time for Prev Station (MIN): ";
                        cin >> sPrevTravelTime;

                        if (!sPrevTravelTime)
                        {
                            cout << endl;
                            cout << "                              Invalid Previous Travel Time input !! Please Try Again with numbers only\n\n" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        //setting previous details as null
                        sNextID = "NULL";
                        sNextFair = NULL;
                        sNextDistance = NULL;
                        sNextTravelTime = NULL;
                        break;
                    } while (true);

                    //getting the current first node of subway station
                    sCurrent = sTail;
                    sPrevID = sCurrent->sID;

                    SubwayStation* sNewnode = createSubwayNewNode(sID, sName, sPrevID, sNextID, sNearbySpot, sPrevFair, sNextFair, sPrevDistance, sNextDistance, sPrevTravelTime, sNextTravelTime);
                    insertSubwayToEnd(sNewnode);

                    //Updating Next Details of First Station
                    sCurrent->sNextID = sID;
                    sCurrent->sNextFair = sPrevFair;
                    sCurrent->sNextDistance = sPrevDistance;
                    sCurrent->sNextTravelTime = sPrevTravelTime;
                }


                cout << endl << endl;
                cout << "           Updated Subway Station record" << endl << endl;
                AdminMainMenu();

            }
            if (selection == 2) {
                sID = "";
                cout << "  Which record to update? Enter Subway ID: ";
                cin >> sID;
                EditSubwayStationDetails(sID);
                AdminMainMenu();
            }

            if (selection == 3) {
                cout << "  Your sorted list is: " << endl;
                displayPassengerByName();
                AdminMainMenu();
            }
            if (selection == 4) {
                cout << "  Purchase Transaction List" << endl;
                DisplayPurchaseTransaction();
                AdminMainMenu();
            }
            if (selection == 5) {
                string searchID;
                cout << "  " << "Enter Transaction ID You Want to Search:  ";
                cin >> searchID;
                EditTicketTransactionDetails(searchID);
                AdminMainMenu();
            }
            if (selection == 6) {
                string deleteTranID;
                cout << "  " << "Enter Transaction ID You Want to Delete:  ";
                cin >> deleteTranID;
                DeletePassengerTicketInfo(deleteTranID);
                AdminMainMenu();
            }
            if (selection == 7) {
                InitialMainMenu();
            }
        }
        cout << "                              Please enter a valid option number [1-7]! " << endl;
    } while (true);

}


//admin login page
bool AdminLogin()
{
    string Ausername;
    string Apassword;
    string AusernameList[1] = { "Admin" };
    string ApasswordList[1] = { "password" };
    int testArray = 0;

    cout << endl;
    cout << endl;
    cout << "                                                                               Admin Login" << endl;
    cout << endl;
    cout << separator << endl;
    cout << endl;
    cout << "                                                                 Please input your username and password!" << endl;
    cout << endl;
    cout << endl;
    cout << "                                                                Username: ";
    cin >> Ausername;
    cout << "                                                                Password: ";
    cin >> Apassword;

    for (testArray = 0; testArray < sizeof(ApasswordList); testArray++)
    {
        if (Ausername == AusernameList[testArray] && Apassword == ApasswordList[testArray])
        {
            cout << "  Successfully Logged In" << endl;
            AdminMainMenu();

        }
        else
        {
            cout << "  Invalid Username or Password! Try Again." << endl;
            cout << endl << endl << endl << endl;
            InitialMainMenu();
        }
    }
    return 0;
}

//Main Function 
int main()
{
    sHead = NULL;
    pHead = NULL;
    tranHead = NULL;
    insertDefaultSubwayStationDetails();
    insertPassengerDetails();
    InitialMainMenu();

    return 0;
}

