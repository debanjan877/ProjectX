#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<string.h>
class garment
{
 int pno;
 char name[50];
 float price,qty,tax,dis;
 int stock;
 public:
	void create_garment()
	{
	 cout<<"\n Enter Garment ID:";
	 cin>>pno;
	 cout<<"\n\n Enter Garment Name:";
	 gets(name);
	 cout<<"\n Enter The Stock Of The Garment:";
	 cin>>stock;
	 cout<<"\n Enter Garment Price:";
	 cin>>price;
	 cout<<"\n Enter The Discount(%) To Be Given:";
	 cin>>dis;
	 }
	void show_garment()
	{
	 cout<<"\n Garment ID: "<<pno;
	 cout<<"\n The name Of The Garment: ";
	 puts(name);
	 cout<<"\n Garment Price: "<<price;
	 cout<<"\n Stock Of The Garment: "<<stock;
	 cout<<"\n Discount: "<<dis;
	 }
  int retpno()
  {return pno;}

  float retprice()
  {return price;}

  char* retname()
  {return name;}

  int retdis()
  {return dis;}

};       //class ends here


//---------------------------------------------------------------------------
//	global declarartion for stream object
//---------------------------------------------------------------------------

  fstream fp;
  garment pr;

//---------------------------------------------------------------------------
//      function to write in file
//---------------------------------------------------------------------------

void write_garment()
    {
     fp.open("ShopX.dat",ios::out|ios::app);
     pr.create_garment();
     fp.write((char*)&pr,sizeof(garment));
     fp.close();
     cout<<"\n\n The Garment Has Been Created Succesfully";
     getch();
     }

//---------------------------------------------------------------------------
//     function to read all records from file
//---------------------------------------------------------------------------

void display_all()
{
     clrscr();
     cout<<"\n\n\n\t DISPLAY ALL RECORD !!!\n\n";
     fp.open("ShopX.dat",ios::in);
     while(fp.read((char*)&pr,sizeof(garment)))
	{
	 pr.show_garment();
	 cout<<"\n\n========================================\n";
	 getch();
	 }
     fp.close();
     getch();
}

//---------------------------------------------------------------------------
//       function to read specific record from file
//---------------------------------------------------------------------------

void display_sp(int n)
{
     int flag=0;
     fp.open("ShopX.dat",ios::in);
     while(fp.read((char*)&pr,sizeof(garment)))
	 {
	  if(pr.retpno()==n)
		 {
		  clrscr();
		  pr.show_garment();
		  flag=1;
		  }
	  }
     fp.close();
if(flag==0)
  cout<<"\n\n Record Does Not Exist";
  getch();
}

//---------------------------------------------------------------------------
//	  function to modify record of file
//---------------------------------------------------------------------------

void modify_garment()
{
      int no,found=0;
      clrscr();
      cout<<"\n\n\t ::To Modify Garment::";
      cout<<"\n\n\t Please Enter Garment ID: ";
      cin>>no;
      fp.open("ShopX.dat",ios::in|ios::out);
      while(fp.read((char*)&pr,sizeof(garment))&&found==0)
	   {
	    if(pr.retpno()==no)
		   {
		    pr.show_garment();
		    cout<<"\n Enter New Garmnet Details: "<<endl;
		    pr.create_garment();
		    int pos=-1*sizeof(pr);
		    fp.seekg(pos,ios::cur);
		    fp.write((char*)&pr,sizeof(garment));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		    }
	   }
     fp.close();
     if(found==0)
     cout<<"\n\n Record Not Found";
     getch();
}

//---------------------------------------------------------------------------
//        function to delete record of file
//---------------------------------------------------------------------------

     void delete_garment()
     {
      int no;
      clrscr();
      cout<<"\n\n\n\t Delete Record";
      cout<<"\n\n Please Enter Garment ID To Be Deleted: ";
      cin>>no;
      fp.open("ShopX.dat",ios::in|ios::out);
      fstream fp2;
      fp2.open("Temp.dat",ios::out);
      fp.seekg(0,ios::beg);
      while(fp.read((char*)&pr,sizeof(garment)))
	   {
	    if(pr.retpno()!=no)
		    {
		     fp2.write((char*)&pr,sizeof(garment));
		     }
	    }
     fp2.close();
     fp.close();
     remove("ShopX.dat");
     rename("Temp.dat","ShopX.dat");
     cout<<"\n\n\t Record Deleted...";
     getch();
     }

//---------------------------------------------------------------------------
//            function to display all garments price list
//---------------------------------------------------------------------------

    void menu()
    {
     clrscr();
     fp.open("ShopX.dat",ios::in);
     if(!fp)
     {
       cout<<" ERROR!!! FILE COULD NOT BE OPENED\n\n Go To Admin Menu To Create File";
       cout<<"\n\n Program Is Closing...";
       getch();
       exit(0);
     }
      cout<<"\t\t== == == == == == == == == == == == == == ==";
      cout<<"\n\t\t SHOPPER'S STOP";
      cout<<"\n\t\t== == == == == == == == == == == == == == == ";
      cout<<"\n\n\t\t **Unique Fabric And Design**";
      cout<<"\n\n\t\t ::GARMENT MENU ::\n\n";
      cout<<"\t\t========================================================\n";
      cout<<"\t\tP.NO.\t\tNAME\t\tPRICE\n";
      cout<<"\t\t========================================================\n";
      while(fp.read((char*)&pr,sizeof(garment)))
	  {
	   cout<<"\t\t"<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
	  }
      fp.close();
}

//--------------------------------------------------------------------------
//     function to place order and generating bills for garmnets
//--------------------------------------------------------------------------

   void place_order()
   {
    int order_arr[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='Y';
    menu();
    cout<<"\n\t\t= = = = = = = = = = = = = = = = = = = = = = = =";
    cout<<"\n\t\t    :: P L A C E   Y O U R   O R D E R::";
    cout<<"\n\t\t= = = = = = = = = = = = = = = = = = = = = = = = \n";
    do{
	cout<<"\n\n\t Enter Garmnet ID: ";
	cin>>order_arr[c];
	cout<<"\n\t Quantity: ";
	cin>>quan[c];
	c++;
	cout<<"\n\t Do You Want To Order Another Garment(Y/N?):";
	cin>>ch;
    }while(ch=='Y' ||ch=='y');
    cout<<"\n\n\n\t THANK YOU FOR PLACING THE ORDER. ";getch();clrscr();
    cout<<"\n\t\t SHOPPER'S STOP ";
    cout<<"\n\n\t\t Unique Fabric And Design...";

    cout<<"\n\n********************* I N V O I C E ************************\n";
    cout<<"\n Pr no.\tPr name\tQuantity\tPrice\tAmount\tAmount after Discount\n";
    for(int x=0;x<=c;x++)
      {
	fp.open("ShopX.dat",ios::in);
	fp.read((char*)&pr,sizeof(garment));
	 while(!fp.eof())
	     {
	      if(pr.retpno()==order_arr[x])
		  {
		   amt=pr.retprice()*quan[x];
		   damt=amt-(amt*pr.retdis()/100);
		   cout<<"\n "<<order_arr[x]<<" \t"<<pr.retname()<<" \t"<<quan[x]<<"\t\t"<<pr.retprice()<<" \t"<<amt<<"\t\t"<<damt;
		   total+=damt;
		   }
	     fp.read((char*)&pr,sizeof(garment));
	     }
	fp.close();
      }
    cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
    getch();
    }

//---------------------------------------------------------------------------
//         INTRODUCTION FUNCTION
//---------------------------------------------------------------------------
void password();
void intro()
{
 clrscr();
 cout<<"\n\n\n";
 cout<<"\n\t\t_________________________________________________________\n";
 cout<<"\t\t|                                                         |\n";
 cout<<"\t\t||     SHOPPER'S STOP    ||\n";
 cout<<"\t\t|                                                         |\n";
 cout<<"\t\t                           fashionising your lifestyle    |\n";
 cout<<"\t\t                                            since 1980    |\n";
 cout<<"\t\t___________________________________________________________\n";
 password();
 getch();
}

//--------------------------------------------------------
//      function to display credits
//--------------------------------------------------------

void admin_menu();
void main1();
void password()
{
char usrnm[20],pswrd[30];
int i;
cout<<"\n\n\n\t\t\t\tUSERNAME : ";
gets(usrnm);
if(strcmp(usrnm,"BJREVHEAD")==0)
{
cout<<"\t\t\t\tPASSWORD : ";
char ch;
for(i=0;(ch=getch())!=13;i++)
{
pswrd[i]=ch;
cout<<"*";
}
pswrd[i]='\0';
if(strcmp(pswrd,"PROJECT")==0)
 main1();
else
{
 cout<<"\n\n\t\t WRONG PASSWORD!!! You Are Not Authorised User...";
 getch();
 exit(0);
}
}

getch();
}

void credit()
{
 clrscr();

 cout<<"\n\n\n\n\n\n\n\t== == == == == == == == == == == == == == == == ==";
 gotoxy(27,9);
 cout<<" :: P R O J E C T :: ";
 cout<<"\n\t== == == == == == == == == == == == == == == == == ";
 cout<<"\n\n\t MADE BY:- \n\n\t\t(SHRIJIT MONDAL)\n\n\n";
 cout<<"\n*******************************************************************";
 cout<<"\n\t SCHOOL:- KENDRIYA VIDYALAYA O.F. DUM DUM ";
 cout<<"\n*******************************************************************";
 getch();
}
void about()
{
  clrscr();
  cout<<"\n\n\n\n\n\n\n\n\t REV SOCIETY pvt ltd.";
  cout<<"\n\n\n\tDESCRIPTION:\n\n\tThis Project Is About Creating Invoice System For A Garment Store.";
  cout<<"\n\n\n\n\n\tProject @copyright protected.";
  getch();
}
//---------------------------------------------------------------
//            ADMINISTER MENU FUNCTION
//---------------------------------------------------------------
void admin_menu()
{
  clrscr();
  char ch2;
  cout<<"\n\n/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*";
  cout<<"\n\t:: A D M I N  M E N U ::";
  cout<<"\n***************************************************************************";
  cout<<"\n\n\t1. CREATE PRODUCT ";
  cout<<"\n\n\t2. DISPLAY ALL PRODUCTS";
  cout<<"\n\n\t3. QUERY ";
  cout<<"\n\n\t4. MODIFY PRODUCT";
  cout<<"\n\n\t5. DELETE PRODUCT";
  cout<<"\n\n\t6. VIEW PRODUCT MENU";
  cout<<"\n\n\t7. BACK TO MAIN MENU";
  cout<<"\n\n\n\t Please Enter Your Choice (1-7) ";
  ch2=getche();
  switch(ch2)
  {
    case '1': clrscr();
	      write_garment();
	      break;
    case '2': display_all();break;
    case '3':
	      int num;
	      clrscr();
	      cout<<"\n\n\tPlease Enter Garment ID:";
	      cin>>num;
	      display_sp(num);
	      break;
    case '4': modify_garment();
    break;
    case '5': delete_garment();
    break;
    case '6': menu();
	      getch();
    case '7':
    break;
    default:cout<<"\a";admin_menu();
  }
}

//---------------------------------------------------------------------------
//            THE MAIN FUNCTION
//---------------------------------------------------------------------------

void main1()
{
  char ch;
// intro();
  do
    {
      clrscr();
      cout<<"==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==";
      cout<<"\n\tSHOPPER'S STOP";
      cout<<"\n==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==";
      cout<<"\n\t**The Garment Shop**";
      cout<<"\n\n\tUnique Fabric And Design...";
      cout<<"\n\n\n\t::M A I N  M E N U ";
      cout<<"\n\n\t01. CUSTOMER";
      cout<<"\n\n\t02. ADMINISTRATOR";
      cout<<"\n\n\t03. CREDITS";
      cout<<"\n\n\t04. ABOUT";
      cout<<"\n\n\t05. EXIT";
      cout<<"\n\n\tPlease Select Your Option (1-5) ";
      ch=getche();
      switch(ch)
      {
	    case '1': clrscr();
		      place_order();
		      getch();
		      break;
	    case '2': admin_menu();
		      break;
	    case '3': credit();
		      break;
	    case '4': about();
		      break;
	    case '5': exit(0);
	    default : cout<<"\a";//Here \a Signifies Sound Alert.
      }
   }while(ch!='5');
}
void main()
{
 clrscr();
 intro();
 getch();
}
//---------------------------------------------------------------------------
//               END OF PROJECT
//---------------------------------------------------------------------------


