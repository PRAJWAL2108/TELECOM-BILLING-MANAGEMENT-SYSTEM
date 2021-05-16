#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
struct subscriber   //structure for subscriber data
{
char phonenumber[20];
char name[50];
float amount;
}s;
void addrecords();  //function for adding records
void listrecords();  //function for list of record
void modifyrecords();  // function for modifying the record
void searchrecords();    //function for searching the record
void payment();  //function for updating payment of individual subscriber
char get;
int main()  //main function
{
int phonenumber;
int choice;
printf("\n\n\n\n\n\n\n\n\n**************************************************************");
printf("\n\t\t------WELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM---");
printf("\n\t\t****************************************************************");
while (choice!=6)
{
printf("\n Enter\n 1 : for adding new records.\n 2 : for list of records");
printf("\n 3 : for modifying records.\n 4 : for payment");
printf("\n 5 : for searching records.");
printf("\n 6 : for exit\n");
scanf("%d",&choice);
switch(choice)
{
case 1:
addrecords();break;
case 2:
listrecords();break;
case 3:
modifyrecords();break;
case 4:
payment();break;
case 5:
searchrecords();break;
case 6:
printf("\n\n\t\t\t\tTHANK YOU FOR USING OUR SERVICE");
exit(0);
break;
default:
printf("Incorrect Input");
printf("\nAny key to continue");
break;
}
}
}

void addrecords()
{
FILE *f;
int test=1;
f=fopen("file.ojs","ab+");
if(f==0)
{   f=fopen("file.ojs","wb+");
printf("please wait while we configure your computer");
printf("/npress any key to continue");
}
while(test!=27)
{
printf("\n Enter phone number:");
scanf("%s",s.phonenumber);
printf("\n Enter name:");
scanf("%s[^\n]",s.name);
printf("\n Enter amount:");
scanf("%f",&s.amount);
fwrite(&s,sizeof(s),1,f);
printf("1 record successfully added");
printf("\n Press 27 to exit, any other key to add other record:");
scanf("%d",&test);
if(test==27)
break;
}
fclose(f);
}

void listrecords()
{
FILE *f;
int i;
if((f=fopen("file.ojs","rb"))==NULL)
exit(0);
system("cls");
printf("Phone Number\t\tUser Name\t\t\tAmount\n");
for(i=0;i<79;i++)
printf("-");
while(fread(&s,sizeof(s),1,f)==1)
{
printf("\n%-10s\t\t%-20s\t\tRs. %.2f /-",s.phonenumber,s.name,s.amount);
}
printf("\n");
for(i=0;i<79;i++)
printf("-");
fclose(f);
}

void searchrecords()
{
FILE *f;
char phonenumber[20];
int flag=1;
f=fopen("file.ojs","rb+");
if(f==0)
exit(0);
fflush(stdin);
printf("Enter Phone Number to search in our database");
scanf("%s", phonenumber);
while(fread(&s,sizeof(s),1,f)==1)
{
if(strcmp(s.phonenumber,phonenumber)==0)
{
printf(" Record Found ");
printf("\n\nPhonenumber: %s\nName: %s\nAmount: Rs.%0.2f\n",s.phonenumber,s.name,s.amount);
flag=0;
break;
}
else if(flag==1)
{
printf("Requested Phone Number Not found in our database");
}
}
fclose(f);
}

void modifyrecords()
{
FILE *f;
char phonenumber[20];
long int size=sizeof(s);
if((f=fopen("file.ojs","rb+"))==NULL)
exit(0);
printf("Enter phone number of the subscriber to modify:");
scanf("%s[^\n]",phonenumber);
fflush(stdin);
while(fread(&s,sizeof(s),1,f)==1)
{
if(strcmp(s.phonenumber,phonenumber)==0)
{
printf("\n Enter phone number:");
scanf("%s",s.phonenumber);
printf("\n Enter name: ");
fflush(stdin);
scanf("%s[^\n]",s.name);
printf("\n Enter amount: ");
scanf("%f",&s.amount);
fseek(f,-size,SEEK_CUR);
fwrite(&s,sizeof(s),1,f);
break;
}
}
fclose(f);
}

void payment()
{
FILE *f;
char phonenumber[20];
long int size=sizeof(s);
float amt;
int i;
if((f=fopen("file.ojs","rb+"))==NULL)
exit(0);
printf("Enter phone number of the subscriber for payment");
scanf("%s[^\n]",phonenumber);
fflush(stdin);
while(fread(&s,sizeof(s),1,f)==1)
{
if(strcmp(s.phonenumber,phonenumber)==0)
{
printf("\n Phone No.: %s",s.phonenumber);
printf("\n Name: %s",s.name);
printf("\n Current amount: %f",s.amount);
printf("\n");
for(i=0;i<79;i++)
printf("-");
printf("\n\nEnter amount of payment :");
fflush(stdin);
scanf(" %f",&amt);
s.amount=s.amount-amt;
fseek(f,-size,SEEK_CUR);
fwrite(&s,sizeof(s),1,f);
break;
}
}
printf("THANK YOU %s FOR YOUR TIMELY PAYMENTS",s.name);
fclose(f);
}
