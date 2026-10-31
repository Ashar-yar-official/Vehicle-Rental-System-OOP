#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//FUNCTIONS PROTOTYPING
void mainMenu();
void cusMenu();
void cusPortal(int foundIndex);
void ownerMenu();
void ownPortal(int foundIndex);
void adminMenu();
void clearScreen();
void printLine(int length);
void saveAllData();
void loadAllData();

//GLOBAL VARIABLES
const int MAX_USERS=10;
int totalCustomers=0;
int totalOwners=0;
int totalVehicles=0;
int cusId[MAX_USERS],ownId[MAX_USERS];
int vehPerOwn[MAX_USERS];



string cusUsername[MAX_USERS],cusPassword[MAX_USERS];
string ownUsername[MAX_USERS],ownPassword[MAX_USERS];
string cusName[MAX_USERS],cusPhone[MAX_USERS],cusEmail[MAX_USERS];
string ownName[MAX_USERS],ownPhone[MAX_USERS],ownEmail[MAX_USERS];
string vehId[MAX_USERS][3],vehName[MAX_USERS][3],vehNumber[MAX_USERS][3];

float vehRpKM[MAX_USERS][3],vehMilage[MAX_USERS][3];
float Revenue=0.0;

bool isCusAvailable[MAX_USERS],isVehAvailable[MAX_USERS][3];
bool cusRentedVehicle[MAX_USERS][MAX_USERS][3];


//CLASSES DECLARATION
class loginAccess{
	private:
		string tempUsername,tempPasswrod;	
	public:
	void getValues(){
		printLine(50);
		cout<<"\tENTER CREDENTIALS \n"<<endl;
		printLine(50);
		cin.ignore();
		cout<<"\n\tENTER USERNAME: ";
		getline(cin,tempUsername);
		cout<<"\tENTER PASSWORD: ";
		getline(cin,tempPasswrod);
	}
	void verifyCustomer(){
		int foundIndex=-1;
		for(int i=0;i<totalCustomers;i++)
		{
			if(tempUsername==cusUsername[i] && tempPasswrod==cusPassword[i])
			{
				foundIndex=i;
				cout<<"\tACCESS GRANTED..."<<endl<<endl;
				printLine(50);
				clearScreen();
				cusPortal( foundIndex);
				break;
			}
		}
		if(foundIndex==-1)
		{
			cout<<"\tACCESS DENIED..."<<endl<<endl;
			printLine(50);
			clearScreen();
			cusMenu();
		}
	}
	void verifyOwner(){
		int foundIndex=-1;
		for(int i=0;i<totalOwners;i++)
		{
			if(tempUsername==ownUsername[i] && tempPasswrod==ownPassword[i])
			{
				foundIndex=i;
				cout<<"\tACCESS GRANTED..."<<endl<<endl;
				printLine(50);
				clearScreen();
				ownPortal( foundIndex);
				break;
			}
		}
		if(foundIndex==-1)
		{
			cout<<"\tACCESS DENIED..."<<endl<<endl;
			printLine(50);
			clearScreen();
			ownerMenu();
			
		}
	}
	void verifyAdmin(){
		
		if(tempUsername=="admin" && tempPasswrod=="admin123")
		{
			cout<<"\tACCESS GRANTED..."<<endl<<endl;
			printLine(50);
			clearScreen();
			adminMenu();
		}
		else{
			cout<<"\tACCESS DENIED..."<<endl<<endl;
			printLine(50);
			clearScreen();
			mainMenu();
		}
		
	}
		
};
class Register{
	public:
	void registerCus(){
		if (totalCustomers >= MAX_USERS)
		{
		    cout << "\tMAXIMUM CUSTOMER LIMIT REACHED." << endl;
		    return;
		}
		printLine(50);
		cout<<"\tCUSTOMER REGISTRATION"<<endl<<endl;
		printLine(50);
		cout<<"\tCUSTOMER NUMBER "<<totalCustomers+1<<endl;
		cusId[totalCustomers]=totalCustomers+1;
		cin.ignore();
		cout << "\tENTER NAME: ";
        getline(cin, cusName[totalCustomers]);
        for (int i = 0; i < totalCustomers; i++)
		{
			if(cusName[totalCustomers] == cusName[i])
			{
				cout<<"\tNAME ALREADY AVAILABLE..."<<endl<<endl;
				return;
			}
		}
		cout<<"\tENTER PHONE NUMBER: ";
		getline(cin,cusPhone[totalCustomers]);
		cout<<"\tENTER EMAIL: ";
		getline(cin,cusEmail[totalCustomers]);
		int foundEmail=-1;
		for(int i=0;i<totalCustomers;i++)
		{
			if(cusEmail[totalCustomers]==cusEmail[i])
			{
				foundEmail=i;
				cout<<"\tEMAIL ADDRESS ALREADY AVAILABLE..."<<endl<<endl;
				return;
			}
		}
		if(foundEmail==-1)
		{
			cusUsername[totalCustomers]=cusEmail[totalCustomers];
		}
		cout<<"\tENTER PASSWORD: ";
		getline(cin,cusPassword[totalCustomers]);
		isCusAvailable[totalCustomers]=false;
		vehPerOwn[totalCustomers]=0;
		clearScreen();
		cout<<"\tCUSTOMER REGISTERED SUCESSFULLY..."<<endl<<endl;
		totalCustomers++;
		saveAllData();
		return;
	}
	void registerOwn(){
		if (totalOwners >= MAX_USERS)
		{
		    cout << "\tMAXIMUM OWNERS LIMIT REACHED." << endl;
		    return;
		}
		printLine(50);
		cout<<"\tOWNER REGISTRATION"<<endl<<endl;
		printLine(50);
		cout<<"\tOWNER NUMBER "<<totalOwners+1<<endl;
		ownId[totalOwners]=totalOwners+1;
		cin.ignore();
		cout << "\tENTER NAME: ";
        getline(cin, ownName[totalOwners]);
        for (int i = 0; i < totalOwners; i++)
		{
			if(ownName[totalOwners] == ownName[i])
			{
				cout<<"\tNAME ALREADY AVAILABLE..."<<endl<<endl;
				return;
			}
		}
		cout<<"\tENTER PHONE NUMBER: ";
		getline(cin,ownPhone[totalOwners]);
		cout<<"\tENTER EMAIL: ";
		getline(cin,ownEmail[totalOwners]);
		int foundEmail=-1;
		for(int i=0;i<totalOwners;i++)
		{
			if(ownEmail[totalOwners]==ownEmail[i])
			{
				foundEmail=i;
				cout<<"\tEMAIL ADDRESS ALREADY AVAILABLE..."<<endl<<endl;
				return;
			}
		}
		if(foundEmail==-1)
		{
			ownUsername[totalOwners]=ownEmail[totalOwners];
		}
		cout<<"\tENTER PASSWORD: ";
		getline(cin,ownPassword[totalOwners]);
		clearScreen();
		cout<<"\tOWNER REGISTERED SUCESSFULLY..."<<endl<<endl;
		totalOwners++;
		saveAllData();
		return;
	}
	void registerVehicle(int foundIndex){
		if (foundIndex < 0 || foundIndex >= totalOwners)
	    {
	        cout << "\tINVALID OWNER." << endl;
	        return;
	    }
		if(vehPerOwn[foundIndex]>=3)
		{
			cout<<"\tMAXIMUM NUMBERS OF CARS ADDED\n"<<endl;
			cusPortal(foundIndex);
		}
		else
		{
			cout<<"\tVEHICLE REGISTRATION "<<endl<<endl;
			printLine(50);
			cout<<"\tVEHICLE ID: "<<foundIndex+1<<"-"<<vehPerOwn[foundIndex]+1<<endl;
			vehId[foundIndex][vehPerOwn[foundIndex]]=to_string(foundIndex + 1) + "-" + to_string(vehPerOwn[foundIndex] + 1);
			cin.ignore();
			cout<<"\tENTER VEHICLE NAME: ";
			getline(cin,vehName[foundIndex][vehPerOwn[foundIndex]]);
			cout<<"\tENTER VEHICLE IDENTIFICATION NUMBER: ";
			getline(cin,vehNumber[foundIndex][vehPerOwn[foundIndex]]);
			for(int i=0;i<totalCustomers;i++)
			{
				for(int j=0;j<vehPerOwn[foundIndex];j++)
				{
					if(vehNumber[foundIndex][vehPerOwn[foundIndex]] == vehNumber[i][j])
					{
						cout<<"\tVEHICLE IDENTIFICATION NUMBER ALREADY AVAILABLE\n"<<endl;
						registerVehicle(foundIndex);
						return;
					}
				}
			}
			cout<<"\tENTER VEHICLE MILEAGE: ";
			cin>>vehMilage[foundIndex][vehPerOwn[foundIndex]];
			cout<<"\tENTER VEHICLE RENT PER KM: ";
			cin>>vehRpKM[foundIndex][vehPerOwn[foundIndex]];
			cout<<"\tVEHICLE STATUS: NOT RENTED "<<endl;
			clearScreen();
			cout<<"\tVEHICLE REGISTERED SUCCESSFULLY...\n"<<endl;
			isVehAvailable[foundIndex][vehPerOwn[foundIndex]] = false;
			vehPerOwn[foundIndex]++;
			totalVehicles++;
			saveAllData();
		}
		
		
	}
			
};
class Management{
	public:
	void cusManagement(){
		printLine(50);
		cout<<"\tCUSTOMER MANAGEMENT"<<endl<<endl;
		printLine(50);
		cout<<"\t1. CUSTOMER DETAILS"<<endl;
		cout<<"\t2. CUSTOMER REGISTRATION "<<endl;
		cout<<"\t3. SEARCH CUSTOMER "<<endl;
		cout<<"\t4. BACK "<<endl;
		
		int option;
		cout<<"\n\tENTER: ";
		
		if(!(cin>>option))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout<<"\tINVALID INPUT! PLEASE ENTER A NUMBER."<<endl;
			cusManagement();
			return;
		}
		if(option==1)
		{
			clearScreen();
			printLine(50);
			cout<<"\t-- CUSTOMER DETAILS --\n"<<endl;
			printLine(50);
			if(totalCustomers==0)
			{
				cout<<"\tNO CUSTOMERS ON PORTAL\n"<<endl;
				cusManagement();
			}
			else{
			for(int i=0;i<totalCustomers;i++)
		{
			cout<<"\tCUSTOMER ID: "<<cusId[i]<<endl;
			cout<<"\tNAME: "<<cusName[i]<<endl;
			cout<<"\tPHONE NUMBER: "<<cusPhone[i]<<endl;
			cout<<"\tEMAIL: "<<cusEmail[i]<<endl;
			if(isCusAvailable[i]==false)
			{
				cout<<"\tCUSTOMER STATUS: NO CAR RENTED"<<endl<<endl;
			}
			else{
				cout<<"\tCUSTOMER STATUS: CAR RENTED"<<endl<<endl;
			}
		}
		cusManagement();
			
			}
		}
		else if(option==2)
		{
			clearScreen();
			Register customer;
			customer.registerCus();
			cusManagement();
		}
		else if(option==3)
		{
			clearScreen();
			printLine(50);
			if(totalCustomers==0)
			{
				cout<<"\tNO CUSTOMERS ON PORTAL"<<endl<<endl;
				cusManagement();
			}
			else{
				cin.ignore();
				string sEmail;
				cout<<"\n\tENTER CUSTOMER EMAIL:";
				getline(cin,sEmail);
				
				int foundIndex=-1;
				for(int i=0;i<totalCustomers;i++)
				{
					if(sEmail==cusEmail[i])
					{
						foundIndex=i;
						printLine(50);
						cout<<"\n\tCUSTOMERS DETAILS\n"<<endl;
						printLine(50);
						cout<<"\tNAME:"<<cusName[i]<<endl;
						cout<<"\tPHONE NUMBER:"<<cusPhone[i]<<endl;
						cout<<"\tEMAIL:"<<cusEmail[i]<<endl;
						break;
					}
				}
				cusManagement();
				if(foundIndex==-1)
				{
					cout<<"\tCUSTOMER NOT FOUND...RETRY!"<<endl;
					cusManagement();
				}
			}
		}
		else if(option==4)
		{
			clearScreen();
			adminMenu();
		}
		else{
			clearScreen();
			cout<<"\tINVALID OPTION...CHOOSE ONLY 1,2,3,4 & 5."<<endl;
			cusManagement();
		}
		
	}
	void ownManagement(){
		printLine(50);
		cout<<"\tOWNER MANAGEMENT"<<endl<<endl;
		printLine(50);
		cout<<"\t1. OWNER DETAILS"<<endl;
		cout<<"\t2. OWNER REGISTRATION "<<endl;
		cout<<"\t3. SEARCH OWNER "<<endl;
		cout<<"\t4. BACK "<<endl;
		
		int option;
		cout<<"\n\tENTER: ";
		
		if(!(cin>>option))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout<<"\tINVALID INPUT! PLEASE ENTER A NUMBER."<<endl;
			ownManagement();
			return;
		}
		if(option==1)
		{
			clearScreen();
			printLine(50);
			cout<<"\t-- OWNER DETAILS --"<<endl;
			printLine(50);
			
			if(totalOwners==0)
			{
				cout<<"\n\tNO OWNERS ON PORTAL\n"<<endl;
				ownManagement();
			}
			else
			{
			for(int i=0;i<totalOwners;i++)
		{
			cout<<"\tOWNER ID: "<<ownId[i]<<endl;
			cout<<"\tNAME: "<<ownName[i]<<endl;
			cout<<"\tPHONE NUMBER: "<<ownPhone[i]<<endl;
			cout<<"\tEMAIL: "<<ownEmail[i]<<endl<<endl;;
		}
		ownManagement();
				
			}
		}
		else if(option==2)
		{
			clearScreen();
			Register owner;
			owner.registerOwn();
			ownManagement();
		}
		else if(option==3)
		{
			clearScreen();
			printLine(50);
			if(totalOwners==0)
			{
				cout<<"\tNO OWNERS ON PORTAL"<<endl<<endl;
				ownManagement();
			}
			else{
				cin.ignore();
				string sEmail;
				cout<<"\n\tENTER OWNER EMAIL:";
				getline(cin,sEmail);
	
				int foundIndex=-1;
				for(int i=0;i<totalOwners;i++)
				{
					if(sEmail==ownEmail[i])
					{
						foundIndex=i;
						printLine(50);
						cout<<"\n\tOWNER DETAILS\n"<<endl;
						printLine(50);
						cout<<"\tNAME:"<<ownName[i]<<endl;
						cout<<"\tPHONE NUMBER:"<<ownPhone[i]<<endl;
						cout<<"\tEMAIL:"<<ownEmail[i]<<endl;
						break;
					}
				}
				ownManagement();
				if(foundIndex==-1)
				{
					cout<<"\tOWNER NOT FOUND...RETRY!"<<endl;
					ownManagement();
				}
			}
		}
		else if(option==4)
		{
			clearScreen();
			adminMenu();
		}
		else{
			clearScreen();
			cout<<"\tINVALID OPTION...CHOOSE ONLY 1,2,3,4 & 5."<<endl;
			ownManagement();
		}
		
	}
	void vehManagement(){
		printLine(50);
		cout<<"\n\t-- VEHICLE MANAGEMENT --\n"<<endl;
		printLine(50);
		cout<<"\t1. VIEW ALL VEHICLES"<<endl;
		cout<<"\t2. VIEW AVAILABLE VEHICLES"<<endl;
		cout<<"\t3. VIEW RENTED VEHICLES"<<endl;
		cout<<"\t4. BACK\n"<<endl;
		
		printLine(50);
		int option;
		cout<<"\n\tENTER: ";
		
		if(!(cin>>option))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout<<"\tINVALID INPUT! PLEASE ENTER A NUMBER."<<endl;
			vehManagement();
			return;
		}
		if(option==1)
		{
			clearScreen();
			printLine(50);
			cout<<"\n\t-- VEHICLE DETAILS --\n"<<endl;
			printLine(50);
			if(totalVehicles==0)
			{
				cout<<"\n\tNO VEHICLES ON PORTAL\n"<<endl;
				vehManagement();
			}
			else{
			
			for(int i=0;i<totalOwners;i++)
			{
				cout<<"\tNAME:  "<<ownName[i]<<endl;
				for(int j=0;j<vehPerOwn[i];j++)
				{
					cout<<endl;
					cout<<"\tVehilcle "<<j+1<<" :"<<endl;
					cout<<"\tVEHICLE ID: "<<vehId[i][j]<<endl;
					cout<<"\tVEHICLE NAME: "<<vehName[i][j]<<endl;
					cout<<"\tVEHICLE IDENTIFICATION NUMBER: "<<vehNumber[i][j]<<endl;
					cout<<"\tVEHICLE MILEAGE: "<<vehMilage[i][j]<<endl;
					cout<<"\tVEHICLE RENT PER KM: "<<vehRpKM[i][j]<<endl;
					if(isVehAvailable[i][j]==false)
					{
						cout<<"\tVEHICLE STATUS: NOT RENTED"<<endl;
					}
					else{
						cout<<"\tVEHICLE STATUS: RENTED"<<endl;
					}
					
				}
				
			}
			
			vehManagement();
				
			}
		}
		else if(option==2)
		{
			clearScreen();
			int foundAvailable=-1;
			printLine(50);
			cout<<"\t-- VEHILCE DETAILS --\n"<<endl;
			printLine(50);
			for(int i=0;i<MAX_USERS;i++)
			{
				for(int j=0;j<vehPerOwn[i];j++)
				{
					if(isVehAvailable[i][j]==false){
						
						foundAvailable=i;
						cout<<"\n\tVEHICLE ID: "<<vehId[i][j]<<endl;
						cout<<"\tVEHICLE NAME: "<<vehName[i][j]<<endl;
						cout<<"\tVEHICLE IDENTIFICATION NUMBER: "<<vehNumber[i][j]<<endl;
						cout<<"\tVEHICLE MILEAGE: "<<vehMilage[i][j]<<endl;
						cout<<"\tVEHICLE RENT PER KM: "<<vehRpKM[i][j]<<endl;
						cout<<"\tVEHICLE STATUS: NOT RENTED\n"<<endl;
					}
				}
			}
			if(foundAvailable==-1)
			{
				cout<<"\tNO VEHICLES AVAILABLE"<<endl;
				vehManagement();
			}
			
			vehManagement();
		}
		else if(option==3)
		{
			clearScreen();
			int foundRented=-1;
			printLine(50);
			cout<<"\t-- VEHILCE DETAILS --\n"<<endl;
			printLine(50);
			for(int i=0;i<MAX_USERS;i++)
			{
				for(int j=0;j<vehPerOwn[i];j++)
				{
					if(isVehAvailable[i][j]==true){
						
						foundRented=i;
						cout<<"\n\tVEHICLE ID: "<<vehId[i][j]<<endl;
						cout<<"\tVEHICLE NAME: "<<vehName[i][j]<<endl;
						cout<<"\tVEHICLE IDENTIFICATION NUMBER: "<<vehNumber[i][j]<<endl;
						cout<<"\tVEHICLE MILEAGE: "<<vehMilage[i][j]<<endl;
						cout<<"\tVEHICLE RENT PER KM: "<<vehRpKM[i][j]<<endl;
						cout<<"\tVEHICLE STATUS: RENTED\n"<<endl;
					}
				}
			}
			if(foundRented==-1)
			{
				cout<<"\tNO RENTED VEHICLES"<<endl;
				vehManagement();
			}
			
			vehManagement();
		}
		else if(option==4)
		{
			clearScreen();
			adminMenu();
		}
		else{
			clearScreen();
			cout<<"\tINVALID CHOICE... CHOOSE ONLY 1,2,3 & 4"<<endl;
			vehManagement();
		}
		
	}
	void transManagement(){
		printLine(50);
		cout<<"\t-- REVENUE GENERATED --\n"<<endl;
		printLine(50);
		cout<<"\tTOTAL REVENUE: "<<Revenue<<endl;
		
	}	
};
class Rent{
	public:
	void rentDetails(int foundIndex){
		cout<<endl;
		printLine(50);
		cout<<"\n\t1. RENT A VEHICLE"<<endl;
		cout<<"\t2. VIEW RENTED VEHICLES"<<endl;
		cout<<"\t3. RETURN VEHICLE"<<endl;
		cout<<"\t4. BACK\n"<<endl;
	
		int option;
		cout<<"\tENTER: ";
		
		if(!(cin>>option))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout<<"\tINVALID INPUT! PLEASE ENTER A NUMBER."<<endl;
			rentDetails(foundIndex);
			return;
		}
		if(option==1)
		{
			clearScreen();
			printLine(50);
			if(isCusAvailable[foundIndex]==false)
			{
			cout<<"\t-- AVAILABLE VEHICLE DETAILS --\n"<<endl;
			printLine(50);
			int foundAvailable=-1;
			for(int i=0;i<MAX_USERS;i++)
			{
				for(int j=0;j<vehPerOwn[i];j++)
				{
					if(isVehAvailable[i][j]==false){
					
						foundAvailable=i;
						cout<<"\n\t-- VEHILCE DETAILS --\n"<<endl;
						cout<<"\tVEHICLE ID: "<<vehId[i][j]<<endl;
						cout<<"\tVEHICLE NAME: "<<vehName[i][j]<<endl;
						cout<<"\tVEHICLE IDENTIFICATION NUMBER: "<<vehNumber[i][j]<<endl;
						cout<<"\tVEHICLE MILEAGE: "<<vehMilage[i][j]<<endl;
						cout<<"\tVEHICLE RENT PER KM: "<<vehRpKM[i][j]<<endl;
						cout<<"\tVEHICLE STATUS: NOT RENTED\n"<<endl;
					}
				}	
			}
			
			if(foundAvailable==-1)
			{
				cout<<"\n\tNO VEHICLES AVAILABLE"<<endl;
				rentDetails(foundIndex);	
			}
			
			cin.ignore();
			char y_n;
			int foundCusNum=-1;
			int foundVehNum=-1;
			string tempRent;
			cout<<endl;
			cout<<"\tENTER VEHICLE IDENTIFICATION NUMBER: ";
			
			getline(cin,tempRent);
			
			for(int i=0;i<MAX_USERS;i++)
			{
				for(int j=0;j<vehPerOwn[i];j++)
				{
					if( vehNumber[i][j] == tempRent ){
						
						foundCusNum=i;
						foundVehNum=j;
						cout<<"\t-- VEHILCE DETAILS --\n"<<endl;
						cout<<"\tVEHICLE ID: "<<vehId[i][j]<<endl;
						cout<<"\tVEHICLE NAME: "<<vehName[i][j]<<endl;
						cout<<"\tVEHICLE IDENTIFICATION NUMBER: "<<vehNumber[i][j]<<endl;
						cout<<"\tVEHICLE MILEAGE: "<<vehMilage[i][j]<<endl;
						cout<<"\tVEHICLE RENT PER KM: "<<vehRpKM[i][j]<<endl;
						if(isVehAvailable[i][j]==false)
						{
							cout<<"\tVEHICLE STATUS: NOT RENTED\n"<<endl;
						}
						else{
							cout<<"\tVEHICLE STATUS: RENTED\n"<<endl;
							cout<<"\n\n\tVEHICLE ALREADY RENTED\n"<<endl;
							rentDetails(foundIndex);
						}
					}
				}	
			}
			
			if( foundVehNum == -1)
			{
				cout<<"\tVEHICLE NOT FOUND !"<<endl;
				rentDetails(foundIndex);
			}
			
			cout<<"\tDO YOU WANT TO RENT THIS VEHICLE: ";
			cin>>y_n;
			
			if(y_n=='Y' || y_n== 'y')
			{
				isVehAvailable[foundCusNum][foundVehNum]= true;
				cusRentedVehicle[foundIndex][foundCusNum][foundVehNum]= true;
				isCusAvailable[foundIndex] = true;
				saveAllData();
				cout<<"\tVEHICLE RENTED TO CUSTOMER "<<endl;
				rentDetails(foundIndex);
			}
			else{
				cout<<"\tCANCELLED..."<<endl;
				rentDetails(foundIndex);
			}
			
			
		
	}
	else{
		cout<<"\tVEHICLE ALREADY RENTED"<<endl;
		rentDetails(foundIndex);
	}	
			}
		else if(option==2)
		{
				clearScreen();
				printLine(50);
				if(isCusAvailable[foundIndex]==false)
				{
					cout<<"\n\tNO VEHICLES RENTED\n"<<endl;
					rentDetails(foundIndex);
				}
				else {
				cout<<"\t-- VEHICLES RENTED --\n"<<endl;
				printLine(50);
				for(int m=0;m<totalVehicles;m++)
				{
					for(int n=0;n<3;n++)
					{
						if(cusRentedVehicle[foundIndex][m][n]==true)
						{
							cout<<"\tVEHICLE ID: "<<vehId[m][n]<<endl;
							cout<<"\tVEHICLE NAME: "<<vehName[m][n]<<endl;
							cout<<"\tVEHICLE IDENTIFICATION NUMBER: "<<vehNumber[m][n]<<endl;
							cout<<"\tVEHICLE MILEAGE: "<<vehMilage[m][n]<<endl;
							cout<<"\tVEHICLE RENT PER KM: "<<vehRpKM[m][n]<<endl;
							cout<<"\tVEHICLE STATUS: RENTED\n\n\n\n"<<endl;
						}
					}
				}
					
				rentDetails(foundIndex);
			}
			}
		else if(option==3)
		{
				clearScreen();
				printLine(50);
				if(isCusAvailable[foundIndex]==false){
					cout<<"\tNO VEHICLES RENTED "<<endl;
					rentDetails(foundIndex);
				}
				else
				{
					cout<<"\tVEHICLES DETAILS\n"<<endl;
					printLine(50);
					for(int a=0;a<totalCustomers;a++)
					{
						for(int b=0;b<totalVehicles;b++)
						{
							for(int c=0;c<3;c++)
							{
								if(cusRentedVehicle[a][b][c]==true)
								{
									cout<<"\tVEHICLE ID: "<<vehId[b][c]<<endl;
									cout<<"\tVEHICLE NAME: "<<vehName[b][c]<<endl;
									cout<<"\tVEHICLE IDENTIFICATION NUMBER: "<<vehNumber[b][c]<<endl;
									cout<<"\tVEHICLE MILEAGE: "<<vehMilage[b][c]<<endl;
									cout<<"\tVEHICLE RENT PER KM: "<<vehRpKM[b][c]<<endl;
									cout<<"\tVEHICLE STATUS: RENTED\n"<<endl;
									char yr_nr;
									cout<<"\tDO YOU WANT TO RETURN THE VEHICLE: ";
									cin>>yr_nr;
					
									if(yr_nr=='y'||yr_nr=='Y')
									{
										float tempMilage;
										cout<<"\n\tENTER MILEAGE OF VEHICLE: ";
										cin>>tempMilage;
						
										if(tempMilage<vehMilage[b][c])
										{
											cout<<"\n\tMILAGE MUST NOT BE LESS THAN "<<vehMilage[b][c]<<"\n\n\n"<<endl;
											rentDetails(foundIndex);
										}
										else{
											float costOfMilage=(tempMilage-vehMilage[b][c])*vehRpKM[b][c];
											cout<<"\n\tYOUR RENTAL COST IS: "<<costOfMilage<<endl;
											cout<<"\t"<<costOfMilage<<" RS PAID TO THE OWNER"<<endl; 
											Revenue = Revenue + costOfMilage;
											vehMilage[b][c]=tempMilage;
											isCusAvailable[foundIndex]=false;
											isVehAvailable[b][c]=false;
											cusRentedVehicle[foundIndex][b][c]=false;
											saveAllData();
											rentDetails(foundIndex);
										}
									}
									else{
										cout<<"\tRETURN VEHICLE CANCELLED"<<endl;
										rentDetails(foundIndex);
									}
								}
							}
						}
					}
				}
					
			}
		else if(option==4)
		{
				clearScreen();
				cusMenu();
		}
		else{
				clearScreen();
				cout<<"\tINVALID CHOICE. CHOOSE ONLY 1,2 & 3..."<<endl;
				cusPortal(foundIndex);
		}
			
			
	
	
	}

};

//MAIN 
int main(){
	loadAllData();
	clearScreen();
	printLine(50);
	cout<<"\tWELCOME TO AUA RENTALS"<<endl<<endl;
	mainMenu();
	
	return 0;
}

//FUNCTIONS DECLARATION
void mainMenu(){
	printLine(50);
	cout<<"\t1. CUSTOMER PORTAL"<<endl;
	cout<<"\t2. OWNER PORTAL"<<endl;
	cout<<"\t3. ADMIN PORTAL"<<endl;
	cout<<"\t4. EXIT\n"<<endl<<endl;
	
	printLine(50);
	int option;
	cout<<"\tENTER: ";
	
	if(!(cin>>option))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout<<"\tINVALID INPUT! PLEASE ENTER A NUMBER."<<endl;
		mainMenu();
		return;
	}
	if(option==1)
	{
		clearScreen();
		cusMenu();
	}
	else if(option==2)
	{
		clearScreen();
		ownerMenu();
	}
	else if(option==3)
	{
		clearScreen();
		loginAccess adm;
		adm.getValues();
		adm.verifyAdmin();
	}
	else if(option==4)
	{
		saveAllData();
		clearScreen();
		cout<<"\tPROGRAM ENDED-----"<<endl;
		return;
	}
	else{
		clearScreen();
		cout<<"\tINVALID OPTION... CHOOSE ONLY 1,2,3,4."<<endl;
		mainMenu();
	}
	
	
}

// CUSTOMER FUNCTIONS
void cusMenu(){
	printLine(50);
	cout<<"\tCUSTOMER PORTAL\n"<<endl;
	printLine(50);
	cout<<"\t1. LOGIN"<<endl;
	cout<<"\t2. REGISTER"<<endl;
	cout<<"\t3. BACK\n"<<endl;
	
	printLine(50);
	int option;
	cout<<"\tENTER: ";
	
	if(!(cin>>option))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout<<"\tINVALID INPUT! PLEASE ENTER A NUMBER."<<endl;
		cusMenu();
		return;
	}
	if(option==1)
	{
		clearScreen();
		loginAccess cus;
		cus.getValues();
		cus.verifyCustomer();
	}
	else if(option==2)
	{
		clearScreen();
		Register customer;
		customer.registerCus();
		cusMenu();
		
	}
	else if(option==3)
	{
		clearScreen();
		mainMenu();
	}
	else{
		clearScreen();
		cout<<"INVALID OPTION...CHOOSE ONLY 1,2,3."<<endl;
		cusMenu();
	}
}
void cusPortal(int foundIndex){
	clearScreen();
	printLine(50);
	cout<<"\t-- CUSTOMER DETAILS --\n"<<endl;
	printLine(50);
	cout<<"\tCUSTOMER ID: "<<cusId[foundIndex]<<endl;
	cout<<"\tNAME: "<<cusName[foundIndex]<<endl;
	cout<<"\tPHONE NUMBER: "<<cusPhone[foundIndex]<<endl;
	cout<<"\tEMAIL: "<<cusEmail[foundIndex]<<endl;
	if(isCusAvailable[foundIndex]==false)
	{
		cout<<"\tCUSTOMER STATUS: NO CAR RENTED"<<endl;
	}
	else{
		cout<<"\tCUSTOMER STATUS: CAR RENTED"<<endl;
	}
	
	Rent rDetails;
	rDetails.rentDetails(foundIndex);	
}

//OWNER FUNCTIONS
void ownerMenu(){
	printLine(50);
	cout<<"\tOWNER PORTAL\n"<<endl;
	printLine(50);
	cout<<"\t1. LOGIN"<<endl;
	cout<<"\t2. REGISTER"<<endl;
	cout<<"\t3. BACK\n"<<endl;
	
	printLine(50);
	int option;
	cout<<"\tENTER: ";

	if(!(cin>>option))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout<<"\tINVALID INPUT! PLEASE ENTER A NUMBER."<<endl;
		ownerMenu();
		return;
	}
	if(option==1)
	{
		clearScreen();
		loginAccess own;
		own.getValues();
		own.verifyOwner();
	}
	else if(option==2)
	{
		clearScreen();
		Register owner;
		owner.registerOwn();
		ownerMenu();
		
	}
	else if(option==3)
	{
		clearScreen();
		mainMenu();
	}
	else{
		clearScreen();
		cout<<"\tINVALID OPTION...CHOOSE ONLY 1,2,3."<<endl;
		ownerMenu();
	}
}
void ownPortal(int foundIndex){
	printLine(50);
	cout<<"\t-- OWNER DETAILS --"<<endl;
	printLine(50);
	cout<<"\tOWNER ID: "<<ownId[foundIndex]<<endl;
	cout<<"\tNAME: "<<ownName[foundIndex]<<endl;
	cout<<"\tPHONE NUMBER: "<<ownPhone[foundIndex]<<endl;
	cout<<"\tEMAIL: "<<ownEmail[foundIndex]<<endl<<endl;
	
	if(vehPerOwn[foundIndex]==0)
	{
		cout<<"\tNO CARS ADDED YET!"<<endl;
	}
	else{
		cout<<"\tVEHICLES: "<<vehPerOwn[foundIndex]<<endl;
	}
	
	cout<<endl;
	printLine(50);
	cout<<"\t1. VIEW VEHICLES"<<endl;
	cout<<"\t2. ADD VEHICLES "<<endl;
	cout<<"\t3. REMOVE VEHICLES "<<endl;
	cout<<"\t4. EXIT "<<endl;
	
	int option;
	cout<<"\n\tENTER: ";
	
	if(!(cin>>option))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout<<"\tINVALID INPUT! PLEASE ENTER A NUMBER."<<endl;
		ownPortal(foundIndex);
		return;
	}
	if(option==1)
	{
		clearScreen();
		printLine(50);
		cout<<"\t-- VEHICLE DETAILS --"<<endl;
		printLine(50);
		
		if(vehPerOwn[foundIndex]==0)
		{
			cout<<"\tNO VEHICLES ON PORTAL\n\n"<<endl;
			ownPortal(foundIndex);	
		}
		else{
		for(int i=foundIndex;i<foundIndex+1;i++)
		{
			for(int j=0;j<vehPerOwn[foundIndex];j++)
			{
				cout<<"\n\tVEHICLE ID: "<<vehId[i][j]<<endl;
				cout<<"\tVEHICLE NAME: "<<vehName[i][j]<<endl;
				cout<<"\tVEHICLE IDENTIFICATION NUMBER: "<<vehNumber[i][j]<<endl;
				cout<<"\tVEHICLE MILEAGE: "<<vehMilage[i][j]<<endl;
				cout<<"\tVEHICLE RENT PER KM: "<<vehRpKM[i][j]<<endl;
				if(isVehAvailable[i][j]==false)
				{
					cout<<"\tVEHICLE STATUS: NOT RENTED"<<endl;
				}
				else{
					cout<<"\tVEHICLE STATUS: RENTED"<<endl;
				}
				
			}
		}
		ownPortal(foundIndex);
			
		}
	}
	else if(option==2)
	{
		clearScreen();
		printLine(50);
		Register vehicle;
		vehicle.registerVehicle(foundIndex);
		ownPortal(foundIndex);
	}
	else if(option==3)
	{
		clearScreen();
		printLine(50);
		cin.ignore();
		string deleteVeh;
		cout<<"\tENTER VEHICLE NUMBER:";
		getline(cin,deleteVeh);
		
		int delIndex=-1;
		for(int i=foundIndex;i<foundIndex+1;i++)
		{
			for(int j=0;j<vehPerOwn[foundIndex];j++)
			{
				if(deleteVeh==vehNumber[i][j])
				{
					delIndex = j;
				
				}
			}
		}
		if(delIndex==-1)
		{
			cout<<"\tVEHICLE NOT FOUND"<<endl;
			ownPortal(foundIndex);
		}
		
		cout<<"\t-- VEHICLE DETAILS --"<<endl;
		cout<<"\tVEHICLE ID: "<<vehId[foundIndex][delIndex]<<endl;
		cout<<"\tVEHICLE NAME: "<<vehName[foundIndex][delIndex]<<endl;
		cout<<"\tVEHICLE IDENTIFICATION NUMBER: "<<vehNumber[foundIndex][delIndex]<<endl;
		cout<<"\tVEHICLE MILEAGE: "<<vehMilage[foundIndex][delIndex]<<endl;
		cout<<"\tVEHICLE RENT PER KM: "<<vehRpKM[foundIndex][delIndex]<<endl;
		if(isVehAvailable[foundIndex][delIndex]==false)
		{
			cout<<"\tVEHICLE STATUS: NOT RENTED"<<endl;
		}
		else{
			cout<<"\tVEHICLE STATUS: RENTED"<<endl;
		}
		
		char confirm;
    	cout << "\n\tARE YOU SURE YOU WANT TO DELETE THIS VEHICLE? (Y/N): ";
    	cin >> confirm;
		
		if (confirm == 'y' || confirm == 'Y') {
			for(int i=foundIndex;i<foundIndex+1;i++)
			{
				for(int j=delIndex;j<vehPerOwn[foundIndex]-1;j++)
				{
					vehId[foundIndex][j]=vehId[foundIndex][j+1];
					vehName[foundIndex][j]=vehName[foundIndex][j+1];
					vehNumber[foundIndex][j]=vehNumber[foundIndex][j+1];
					vehMilage[foundIndex][j]=vehMilage[foundIndex][j+1];
					vehRpKM[foundIndex][j]=vehRpKM[foundIndex][j+1];
					isVehAvailable[foundIndex][j]=isVehAvailable[foundIndex][j+1];
				}
			}
			cout<<"\tVEHICLE DELETED SUCCESSFULLY...\n"<<endl;
			vehPerOwn[foundIndex]--;
			totalVehicles--;
			saveAllData();
			ownPortal(foundIndex);
		}
		else{
			cout<<"\tVEHICLE DELETION CANCELLED"<<endl;
			ownPortal(foundIndex);
		}
		
	}
	else if(option==4)
	{
		clearScreen();
		printLine(50);
		ownerMenu();
	}
	else{
		clearScreen();
		printLine(50);
		cout<<"INVELID CHOICE...CHOOSE ONLY 1,2,3 & 4."<<endl;
		ownerMenu();
	}
}

//ADMIN FUNCTIONS
void adminMenu(){
	printLine(50);
	cout<<"\tADMIN PORTAL"<<endl<<endl;
	printLine(50);
	cout<<"\t1. CUSTOMER MANAGEMENT "<<endl;
	cout<<"\t2. OWNER MANAGEMENT "<<endl;
	cout<<"\t3. VEHICLE MANAGEMENT "<<endl;
	cout<<"\t4. TRANSACTIONS DETAILS "<<endl;
	cout<<"\t5. SAVE / EXIT \n"<<endl;
	
	printLine(50);
	int option;
	cout<<"\tENTER: ";
	
	if(!(cin>>option))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout<<"\tINVALID INPUT! PLEASE ENTER A NUMBER."<<endl;
		adminMenu();
		return;
	}
	if(option==1)
	{
		clearScreen();
		Management cus;
		cus.cusManagement();
		adminMenu();
	}
	else if(option==2)
	{
		clearScreen();
		Management own;
		own.ownManagement();
		adminMenu();
	}
	else if(option==3)
	{
		clearScreen();
		Management veh;
		veh.vehManagement();
		adminMenu();
	}
	else if(option==4)
	{
		clearScreen();
		Management transactions;
		transactions.transManagement();
		adminMenu();
	}
	else if(option==5)
	{
		saveAllData();
		clearScreen();
		mainMenu();
	}
	else{
		clearScreen();
		cout<<"\tINVALID OPTION...CHOOSE ONLY 1,2,3,4 & 5."<<endl;
		adminMenu();
	}
	
}
//HELPER FUNCTIONS
void clearScreen() {
    for (int i = 0; i < 25; i++) {
        cout << endl;
    }
}
void printLine(int length) {
    for (int i = 0; i < length; i++) {
        cout << "=";
    }
    cout << endl;
}

// SAVE ALL DATA TO TEXT FILES
void saveAllData()
{
    // 1. SAVE CUSTOMERS
    ofstream customerFile("CUSTOMERS_DATA.txt");
    for (int i = 0; i < totalCustomers; i++)
    {
        customerFile << cusId[i] << "|"
                     << cusName[i] << "|"
                     << cusPhone[i] << "|"
                     << cusEmail[i] << "|"
                     << cusUsername[i] << "|"
                     << cusPassword[i] << "|"
                     << isCusAvailable[i] << endl;
    }
    customerFile.close();
    // 2. SAVE OWNERS
    ofstream ownerFile("OWNERS_DATA.txt");
    for (int i = 0; i < totalOwners; i++)
    {
        ownerFile << ownId[i] << "|"
                  << ownName[i] << "|"
                  << ownPhone[i] << "|"
                  << ownEmail[i] << "|"
                  << ownUsername[i] << "|"
                  << ownPassword[i] << endl;
    }
    ownerFile.close();
    // 3. SAVE VEHICLES
    ofstream vehicleFile("VEHICLES_DATA.txt");
    for (int i = 0; i < totalOwners; i++)
    {
        for (int j = 0; j < vehPerOwn[i]; j++)
        {
            vehicleFile << i << "|"
                        << vehId[i][j] << "|"
                        << vehName[i][j] << "|"
                        << vehNumber[i][j] << "|"
                        << vehMilage[i][j] << "|"
                        << vehRpKM[i][j] << "|"
                        << isVehAvailable[i][j] << endl;
        }
    }
    vehicleFile.close();
    // 4. SAVE AVAILABLE VEHICLES
    ofstream availableFile("AVAILABLE_VEH_DATA.txt");
    for (int i = 0; i < totalOwners; i++)
    {
        for (int j = 0; j < vehPerOwn[i]; j++)
        {
            if (isVehAvailable[i][j] == false)
            {
                availableFile << "OWNER: " << ownName[i]
                              << "|VEHICLE ID: " << vehId[i][j]
                              << "|NAME: " << vehName[i][j]
                              << "|NUMBER: " << vehNumber[i][j]
                              << "|MILEAGE: " << vehMilage[i][j]
                              << "|RATE PER KM: " << vehRpKM[i][j]
                              << endl;
            }
        }
    }
    availableFile.close();
    // 5. SAVE RENTED VEHICLES
    ofstream rentedFile("RENTED_VEH_DATA.txt");
    for (int i = 0; i < totalOwners; i++)
    {
        for (int j = 0; j < vehPerOwn[i]; j++)
        {
            if (isVehAvailable[i][j] == true)
            {
                rentedFile << "OWNER: " << ownName[i]
                           << "|VEHICLE ID: " << vehId[i][j]
                           << "|NAME: " << vehName[i][j]
                           << "|NUMBER: " << vehNumber[i][j]
                           << "|MILEAGE: " << vehMilage[i][j]
                           << "|RATE PER KM: " << vehRpKM[i][j]
                           << endl;
            }
        }
    }
    rentedFile.close();
    // 6. SAVE REVENUE
    ofstream revenueFile("REVENUE.txt");
    revenueFile << Revenue << endl;
    revenueFile.close();
    // 7. SAVE RENTAL DETAILS INCLUDING ARRAY INDEXES
    ofstream rentFile("RENT_DETAILS.txt");
    for (int c = 0; c < totalCustomers; c++)
    {
        for (int o = 0; o < totalOwners; o++)
        {
            for (int v = 0; v < vehPerOwn[o]; v++)
            {
                if (cusRentedVehicle[c][o][v] == true)
                {
                    rentFile << c << "|"
                             << o << "|"
                             << v << "|"
                             << cusId[c] << "|"
                             << cusName[c] << "|"
                             << cusEmail[c] << "|"
                             << ownName[o] << "|"
                             << vehId[o][v] << "|"
                             << vehName[o][v] << "|"
                             << vehNumber[o][v] << "|"
                             << vehMilage[o][v] << "|"
                             << vehRpKM[o][v] << endl;
                }
            }
        }
    }
    rentFile.close();
    cout << "\n\tALL DATA SAVED SUCCESSFULLY.\n";
}

// LOAD ALL DATA TO TEXT FILES
void loadAllData()
{
    totalCustomers = 0;
    totalOwners = 0;
    totalVehicles = 0;
    Revenue = 0.0;
    for (int i = 0; i < MAX_USERS; i++)
    {
        vehPerOwn[i] = 0;
        isCusAvailable[i] = false;
        for (int o = 0; o < MAX_USERS; o++)
        {
            for (int v = 0; v < 3; v++)
            {
                cusRentedVehicle[i][o][v] = false;
            }
        }
        for (int j = 0; j < 3; j++)
        {
            isVehAvailable[i][j] = false;
        }
    }
    string id, name, phone, email, username, password, status;
    string ownerIndex, vehicleID, vehicleName, vehicleNumber;
    string mileage, rate, revenue;
    // 1. LOAD CUSTOMERS
    ifstream customerFile("CUSTOMERS_DATA.txt");
    while (totalCustomers < MAX_USERS &&
           getline(customerFile, id, '|') &&
           getline(customerFile, name, '|') &&
           getline(customerFile, phone, '|') &&
           getline(customerFile, email, '|') &&
           getline(customerFile, username, '|') &&
           getline(customerFile, password, '|') &&
           getline(customerFile, status))
    {
        cusId[totalCustomers] = stoi(id);
        cusName[totalCustomers] = name;
        cusPhone[totalCustomers] = phone;
        cusEmail[totalCustomers] = email;
        cusUsername[totalCustomers] = username;
        cusPassword[totalCustomers] = password;
        isCusAvailable[totalCustomers] = (status == "1");
        totalCustomers++;
    }
    customerFile.close();
    // 2. LOAD OWNERS
    ifstream ownerFile("OWNERS_DATA.txt");
    while (totalOwners < MAX_USERS &&
           getline(ownerFile, id, '|') &&
           getline(ownerFile, name, '|') &&
           getline(ownerFile, phone, '|') &&
           getline(ownerFile, email, '|') &&
           getline(ownerFile, username, '|') &&
           getline(ownerFile, password))
    {
        ownId[totalOwners] = stoi(id);
        ownName[totalOwners] = name;
        ownPhone[totalOwners] = phone;
        ownEmail[totalOwners] = email;
        ownUsername[totalOwners] = username;
        ownPassword[totalOwners] = password;
        totalOwners++;
    }
    ownerFile.close();
    // 3. LOAD VEHICLES
    ifstream vehicleFile("VEHICLES_DATA.txt");
    while (getline(vehicleFile, ownerIndex, '|') &&
           getline(vehicleFile, vehicleID, '|') &&
           getline(vehicleFile, vehicleName, '|') &&
           getline(vehicleFile, vehicleNumber, '|') &&
           getline(vehicleFile, mileage, '|') &&
           getline(vehicleFile, rate, '|') &&
           getline(vehicleFile, status))
    {
        int i = stoi(ownerIndex);
        if (i >= 0 && i < totalOwners && vehPerOwn[i] < 3)
        {
            int j = vehPerOwn[i];
            vehId[i][j] = vehicleID;
            vehName[i][j] = vehicleName;
            vehNumber[i][j] = vehicleNumber;
            vehMilage[i][j] = stof(mileage);
            vehRpKM[i][j] = stof(rate);
            isVehAvailable[i][j] = (status == "1");
            vehPerOwn[i]++;
            totalVehicles++;
        }
    }
    vehicleFile.close();
    // 4. LOAD REVENUE
    ifstream revenueFile("REVENUE.txt");
    if (getline(revenueFile, revenue))
    {
        Revenue = stof(revenue);
    }
    revenueFile.close();
    // 5. LOAD RENTAL DETAILS
    ifstream rentFile("RENT_DETAILS.txt");
    string customerIndex, ownerArrayIndex, vehicleIndex;
    string customerID, customerName, customerEmail;
    string ownerName, rentVehicleID, rentVehicleName;
    string rentVehicleNumber, rentMileage, rentRate;
    while (getline(rentFile, customerIndex, '|') &&
           getline(rentFile, ownerArrayIndex, '|') &&
           getline(rentFile, vehicleIndex, '|') &&
           getline(rentFile, customerID, '|') &&
           getline(rentFile, customerName, '|') &&
           getline(rentFile, customerEmail, '|') &&
           getline(rentFile, ownerName, '|') &&
           getline(rentFile, rentVehicleID, '|') &&
           getline(rentFile, rentVehicleName, '|') &&
           getline(rentFile, rentVehicleNumber, '|') &&
           getline(rentFile, rentMileage, '|') &&
           getline(rentFile, rentRate))
    {
        int c = stoi(customerIndex);
        int o = stoi(ownerArrayIndex);
        int v = stoi(vehicleIndex);
        if (c >= 0 && c < totalCustomers &&
            o >= 0 && o < totalOwners &&
            v >= 0 && v < vehPerOwn[o])
        {
            cusRentedVehicle[c][o][v] = true;
            isCusAvailable[c] = true;
            isVehAvailable[o][v] = true;
        }
    }
    rentFile.close();
    cout << "\n\tALL DATA LOADED SUCCESSFULLY.\n";
}
