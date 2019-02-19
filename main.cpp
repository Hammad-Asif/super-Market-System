#include<iostream>
#include<conio.h>
#include<fstream>
#include<string>
#include<windows.h>
using namespace std;
int main();
int size;
void mainMenu();
struct product
{
	string name, proNbr,totalpro,price;	
};
bool logIn()
{
	char id;
	fstream f;
	f.open("login.txt",ios::in);
	if(f)
	{
		f>>id;
		if(id=='1')
		{
			f.close();
			return true;
		}
		f.close();
		loop:
		system("cls");
		string name="",pass="";
		cout<<"\n\n\t\t Log In\n\n\tEnter Name: ";
		cin>>name;
		if(name=="Admin")
		{
			again:
			cout<<"\n\tEnter Password: ";
			cin>>pass;
			if(pass=="admin")
			{
				cout<<"\n\n\n\tCongratulations! You have logged In successfully.";	
				f.open("login.txt",ios::out);
				id='1';
				f<<id;
				return true;
			}
			else
			{
				cout<<"\n\tWrong Password! Enter Password again\n";
				Sleep(1000);
				goto again;
			}
			
	}
	else
	{
		cout<<"Wrong User Name...";
		Sleep(1000);
		goto loop;
	}
	}
	
}
void totallines()
{
	string items="";
	int i=0;
	fstream ifile;
	ifile.open("items.txt",ios::in);
	if(ifile)
	{
		while(getline(ifile,items))
		{
			i++;
		}
		size=i;
		
	}
}
product* loadItems()
{
	product* arrPr=new product[size];//dynamic array
	string items="",itemNbr;
	system("cls");
	fstream ifile;
	ifile.open("items.txt",ios::in|ios::out|ios::app);
	if(ifile)
	{
		char ch;
			int u=0;//index of array
			int com=0;//commas
			while(ifile.get(ch))
			{
				items+=ch;
			}
			//convert string to structure product 
				for(int h=0;h<items.length();h++)
				{
					if(items[h]=='\n')
					{
						u++;
						com=0;
					}
					else if(items[h]==',')
					com++;
					
					else if(com==0)
					{
						arrPr[u].proNbr.push_back(items[h]);				
					}
					else if(com==1)
					{
						arrPr[u].name.push_back(items[h]);
					}
					else if(com==2)
					{
						arrPr[u].totalpro.push_back(items[h]);
					}
					else if(com==3)
					{
						arrPr[u].price.push_back(items[h]);
					}
				}
		}
			
	return arrPr;
}

void makeBill(int price)
{
	int enterPrice=0,remain=price;
	system("cls");
	cout<<"*******Cash Counter*******\n\n";
	cout<<"\tTotal Bill: "<<price<<endl;
	cout<<"\tEnter Amount: ";
	cin>>enterPrice;
	loop:
	remain=remain-enterPrice;
	if(remain>0)
	{
		cout<<"\n\tPlease Enter "<<remain<<" more: ";
		cin>>enterPrice;
		goto loop;
	}
	else if(remain<0)
	{
		cout<<"\n\n\t\tPlease Get remaining amount: "<<-(remain);
		cout<<"\n\n\n\t\t\t\tThanks For Shopping!";
		getch();
	}
	else
	{
		cout<<"\n\n\n\t\t\t\tThanks For Shopping!";
		Sleep(1000);
		getch();
	}
}
void shopping(product* arrPr)
{
	int total=0,price=0,count=0,q;
	to:
	system("cls");
	cout<<"How many items you want to buy? ";
	cin>>total;
	for(int y=0;y<size;y++)
	{
	cout<<"\n\n\n\tNbr: "<<arrPr[y].proNbr<<"\n\tName: "<<arrPr[y].name<<"\n\tTotal Products: "<<arrPr[y].totalpro<<"\n\tPrice: "<<arrPr[y].price;
	}
	if(total>size)
	{
		cout<<"Enter Total items less than or equal to "<<size;
		Sleep(1000);
		goto to;
	}
	string itemNbr="";
	again:
	count++;
	n:
	cout<<"\n\n\tEnter item No. ";
	cin>>itemNbr;
	int index=-1;//index on which item found
	for(int f=0;f<size;f++)
	{
		q=1;
		product pr=arrPr[f];
		if(pr.proNbr==itemNbr)
		{
			index=f;
			lop:
			cout<<"\n\n\tEnter the quantity of "<<pr.name<<": ";
			cin>>q;
			if(q<=atoi(pr.totalpro.c_str()) && q!=0)
			{
				price+=(atoi(pr.price.c_str()))*q;
				q=atoi(pr.totalpro.c_str())-q;
				pr.totalpro=std::to_string(q);
			}
			else if(pr.totalpro!="0")
			{
				cout<<"Quantity must be less than or equal to "<<pr.totalpro<<" and not equal to zero.\n\n\t";
				getch();
				system("cls");
				goto lop;
			}
			else if(pr.totalpro=="0")
			{
				cout<<"\n\n\t\t"<<pr.totalpro<<" Stock out..Select Another item.";
				getch();
				system("cls");
				goto n;
			}
			arrPr[f]=pr;
			break;
		}
	}
	
	if(index==-1)
	{
		cout<<"\n\n\t\tItem not found!";
		Sleep(1000);
		system("cls");
		goto n;
	}
	if(count!=total)
	goto again;
	
	makeBill(price);

	}
void listItems()
{
	totallines();
	product *arrPr;
	arrPr=loadItems();
	for(int y=0;y<size;y++)
		{
		cout<<"\n\n\n\tNbr: "<<arrPr[y].proNbr<<"\n\tName: "<<arrPr[y].name<<"\n\tTotal Products: "<<arrPr[y].totalpro<<"\n\tPrice: "<<arrPr[y].price;
	}getch();	
}
void addItem()
{
	system("cls");
	product pro;
	cout<<"\n*******Add Items*******";
	cout<<"\n\n\tEnter Item Nbr: ";
	cin>>pro.proNbr;
	cout<<"\n\tEnter Item Name: ";
	cin>>pro.name;
	cout<<"\nEnter total Stock of Item: ";
	cin>>pro.totalpro;
	cout<<"\nEnter Price Of Item: ";
	cin>>pro.price;
	fstream  f;
	f.open("items.txt",ios::out|ios::in|ios::app);
	if(f)
	{
		f<<pro.proNbr.c_str()<<","<<pro.name.c_str()<<","<<pro.totalpro.c_str()<<","<<pro.price.c_str()<<"\n";
	}
}
void editItem()
{
	totallines();
	product *arrPr=loadItems();
	string itemNbr;
	loop:
	system("cls");
	cout<<"\n\t\t\tEdit Item";
	cout<<"\n\n\tEnter item No. ";
	cin>>itemNbr;
	int index=-1;//index on which item found
	fstream  f;
	f.open("items.txt",ios::out);
	if(f)
	{
	for(int i=0;i<size;i++)
	{
		if(arrPr[i].proNbr==itemNbr)
		{
			index=i;
			
			product pro;
			pro.proNbr=arrPr[i].proNbr;
			cout<<"\n\tEnter Item Name: ";
			cin>>pro.name;
			cout<<"\nEnter total Stock of Item: ";
			cin>>pro.totalpro;
			cout<<"\nEnter Price Of Item: ";
			cin>>pro.price;
			arrPr[i]=pro;
			break;
		}
	}
	if(index==-1)
	{
		cout<<"\n\n\tItem Not found!";
		getch();
		goto loop;
	}
f.close();
	fstream f;
	f.open("items.txt",ios::out);
	if(f) 
	{
		for(int i=0;i<size;i++)
		{
			f<<arrPr[i].proNbr.c_str()<<","<<arrPr[i].name.c_str()<<","<<arrPr[i].totalpro.c_str()<<","<<arrPr[i].price.c_str()<<"\n";
		}
		getch();
		f.close();
	}
	else
	{
		cout<<"\n\n\tData is not saved";
		getch();
	}
}
	
}
void deletItem()
{
	totallines();
	product *arrPr=loadItems();
	string itemNbr;
	cout<<"\n\n\tEnter item No. ";
	cin>>itemNbr;
	int index=-1;//index on which item found
	fstream  f;
	f.open("items.txt",ios::out);
	if(f)
	{
	for(int i=0;i<size;i++)
	{
		if(arrPr[i].proNbr==itemNbr)
		{
			continue;
		}
		else
		{
			f<<arrPr[i].proNbr.c_str()<<","<<arrPr[i].name.c_str()<<","<<arrPr[i].totalpro.c_str()<<","<<arrPr[i].price.c_str()<<"\n";
		}
}
}
cout<<"Item has been deleted";
getch();
}
void stock()
{	int choice;
	loop:
	system("cls");
	cout<<"\n\n\t\t\tStock Menu";
	cout<<"\n\n\t1-Add Item\n\t2-Edit Item\n\t3-Delete Item\n\t4-List All Items\n\t5-Back To Main Menu\n\tEnter your choice: ";
	cin>>choice;
	switch(choice)
	{
		case 1:
			addItem();
			break;
		case 2:
			editItem();
			break;
		case 3:
			deletItem();
			break;
		case 4:
			{
				listItems();
			}
			break;
		case 5:
			mainMenu();
			break;
		default:
			{
				cout<<"\n\n\t\tInvalid Input! Enter Again ";
				Sleep(1000);
				goto loop;
			}
	}
}
void signOut()
{
	system("cls");
	char id;
	fstream f;
	if(f)
	{
		f.open("login.txt",ios::out);
		id='0';
		f<<id;
	}
	main();
}
void exitProgram(product* arrPr)
{
	fstream f;
	f.open("items.txt",ios::out);
	if(f) 
	{
		for(int i=0;i<size;i++)
		{
			f<<arrPr[i].proNbr.c_str()<<","<<arrPr[i].name.c_str()<<","<<arrPr[i].totalpro.c_str()<<","<<arrPr[i].price.c_str()<<"\n";
		}
		f.close();
	}
	else
	{
		cout<<"\n\n\tData is not saved";
		getch();
	}
}
void mainMenu()
{	int choice;
	loop:
	system("cls");
	cout<<"\n\n\t\t\tMain Menu";
	cout<<"\n\n\t1-Shopping\n\t2-Maintain Stock\n\t3-Sign out\n\t4-Exit\n\tEnter your choice: ";
	cin>>choice;
	switch(choice)
	{
		case 1:
			{
			totallines();
			product *arrPr=loadItems();
			shopping(arrPr);}
			break;
		case 2:
			stock();
			break;
		case 3:
			signOut();
			break;
		case 4:
			{
				totallines();
				product *arrPr=loadItems();
				exitProgram(arrPr);
				exit(0);
			}
			break;
		default:
			{
				cout<<"\n\n\t\tInvalid Input! Enter Again ";
				Sleep(1000);
				goto loop;
			}
	}
	goto loop;
}
int main()
{
	if(logIn())
	{
		mainMenu();
	}
	else
	cout<<"\n\n\tWrong User Name!";
}
