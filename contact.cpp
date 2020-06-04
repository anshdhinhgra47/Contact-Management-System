#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
int lastmno();
class contact
 {
   int mno;
   char mname[20];
   char city[20];
   char country[10];
   char email[20];
   char mobile[20];
 public:
   void in();
   void show();
   int rmno()
	{
	  return mno;
	}
   char *rmname()
      {
       return mname;
       }
 };

void contact::in()
 {
  clrscr();
  mno=lastmno()+1;
  cout<<"\n Enter your name:";
  gets(mname);
  cout<<"\n Enter your phone number:";
  gets(mobile);
  cout<<"\n Enter your city:";
  gets(city);
  cout<<"\n Enter your country:";
  gets(country);
  cout<<"\n Enter your email address:";
  gets(email);
  }

void contact::show()
 {
  cout<<"\n \t Member Number:"<<mno;
  cout<<"\n \t Name:"<<mname;
  cout<<"\n \t Location:"<<city<<" , "<<country;
  cout<<"\n \t Email Id:"<<email;
  cout<<endl<<endl;
  }


int lastmno()
 {
  fstream fil;
  fil.open("contacts.dat",ios::binary|ios::in);
  fil.seekg(0,ios::end);
  return (fil.tellg()/sizeof(contact));
  }


void enter()
  {
   contact c;
   c.in();
   fstream fil;
   fil.open("contacts.dat",ios::binary|ios::app);
   fil.write((char*)&c,sizeof(c));
   cout<<"\n Contact made !";
fil.close();
getch();
}


void displayall()
 {
  contact c;
  fstream fil;
  fil.open("contacts.dat",ios::binary|ios::in);
cout<<"\n\t===========================================================”;
cout<<"\n \t                    ALL CONTACTS                   ";
cout<<"\n\t===========================================================”;
  while(fil.read((char*)&c,sizeof(c)))
   {
     c.show();
   }
fil.close();
getch();
}


void searchmno()
 {
  contact c;
  int smno;
  int found=0;
  fstream fil;
  fil.open("contacts.dat",ios::binary|ios::in);
  cout<<"\n Please enter your Member Number:";
  cin>>smno;
  while(fil.read((char*)&c,sizeof(c)))
   {
	 if(smno==c.rmno())
	    {
		c.show();
		found++;
	    }

   }
if(found==0)
cout<<"\n Sorry No such contact found !";
fil.close();
getch();
}


void sortbyname()
 {
  fstream fil;
  fil.open("contacts.dat",ios::binary|ios::in|ios::out);
  fil.seekg(0,ios::end);
  int n=fil.tellg()/sizeof(contact);
  contact c1,c2;
  for(int i=0;i<n-1;i++)
    {
      for(int j=0;j<n-i-1;j++)
       {
	 fil.seekg(j*sizeof(contact));
	 fil.read((char*)&c1,sizeof(c1));
	 fil.read((char*)&c2,sizeof(c2));
	  if(strcmpi(c1.rmname(),c2.rmname())>0)
	     {
	       fil.seekp(j*sizeof(contact));
	       fil.write((char*)&c2,sizeof(c2));
	       fil.write((char*)&c1,sizeof(c1));
	       }
	 }
    }
displayall();
fil.close();
getch();
}


void deletecontact()
 {
  int dmno;
  int del=0;
  contact c;
  char ch;
  fstream fil1,fil2;
  fil1.open("contacts.dat",ios::binary|ios::in);
  fil2.open("new.dat",ios::binary|ios::out);
  cout<<"\n Enter the member number you want to delete:";
  cin>>dmno;
  while(fil1.read((char*)&c,sizeof(c)))
    {
      if(dmno==c.rmno())
	     del++;
      else
	 fil2.write((char*)&c,sizeof(c));
    }

if(del==0)
   cout<<"\n No such contact found ! ";
else
  cout<<"\n Contact deleted !";
fil1.close();
fil2.close();
remove("contacts.dat");
rename("new.dat","contacts.dat");
getch();
}



void main()
 {
 clrscr();
  int w;
    do
      {
	clrscr();
	cout<<"\n\t******************************************************";
	cout<<"\n \t       WELCOME TO CONTACT MANAGEMENT SYSTEM          ";
	cout<<"\n\t******************************************************";
	cout<<"\n \t 1. Enter a contact";
	cout<<"\n \t 2. Display all contacts";
	cout<<"\n \t 3. Display all contacts sorted by name";
	cout<<"\n \t 4. Search a contact";
	cout<<"\n \t 5. Delete a contact";
	cout<<"\n \t 6. Exit";
	cout<<"\n Please enter your choice:";
	cin>>w;
	 switch(w)
	   {
	    case 1:clrscr();
		   enter();break;
	    case 2:clrscr();
		   displayall();break;
	    case 3:clrscr();
		   sortbyname();break;
	    case 4:clrscr();
		   searchmno();break;
	    case 5:clrscr();
		   deletecontact();break;
	    case 6:cout<<"\n Good Bye!";break;
	    default:cout<<"\n Please enter the correct choice";
	    }
     }while(w!=6);
 getch();
}

