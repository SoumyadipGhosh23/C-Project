/*****Hospital Management System Using C*****/

#include <stdio.h>
#include <conio.h> // for using getch()
#include <stdlib.h>
#include <windows.h> // for using gotoxy()
#include <ctype.h>   //for using toupper(), tolawer()
#include <string.h>

//declaring all the function
void welcomeScreen(char *); //Welcome screen functiom declaration
void title(char *);         //Function to show title
void mainMenu(void);        //mainmenu function declaration
void logInScreen(void);     //login interface function
void addRecord(void);       //function add new record
void funcList(void);        // function to add the patient details
void searchRecord(void);
void editRecord(void);
void dltRecord(void);
void exitfunc(void);

//Declaring The structure for file handling
struct hospitalmanagement
{
    int age;
    char gender;
    char firstName[20];
    char lastName[20];
    char contactNo[12];
    char address[30];
    char doctor[15];
    char problem[20];
} p;

//driver code
void main()
{
    char str[200];
    printf("Enter your hospital name: ");
    scanf("%[^\n]%*c", str);
    welcomeScreen(str);
    title(str);
    logInScreen();
}

//welcome screen
void welcomeScreen(char *str)
{
    printf("\n\n\n\n\t\t\t\t\t******Welcome To******");
    printf("\n\n\t\t\t\t\t   %s", str);
    printf("\n\n\nPress Any Key To Continue");
    getch();
}

//printing the title
void title(char *str)
{
    printf("\n\n\t\t------------------------------------------------------------------------");
    printf("\n\t\t\t\t           %s               ", str);
    printf("\n\n\t\t------------------------------------------------------------------------");
}

//Login Screen
void logInScreen(void)
{
    int count = 0;
    char username[15];
    char password[15];
    char orgUsername[15] = "soumyadip23"; //Original Userid
    char orgPassword[15] = "2307";        //Original Password
    do
    {
        printf("\n\n\t\t\t\t       Enter Username & Password  :");
        printf("\n\nUsername: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);
        if (strcmp(username, orgUsername) == 0 && strcmp(password, orgPassword) == 0)
        {
            printf("\n\n\t\t\t\t      Login Succesfull.........");
            getch();
            mainMenu();
        }
        else
        {
            printf("\n\t\t\tUsername or password is incorrect, Press Any Key to Try Again");
            count++;
            getch();
        }
    } while (count <= 3);
    if (count > 3)
    {
        printf("\n\nYou've crossed the limit  ");
        getch();
        exitfunc();
    }
}

void mainMenu(void)
{
    int choose;
    printf("\n\n\t\t1. Add patients Record: ");
    printf("\n\n\t\t2. List Patient Record: ");
    printf("\n\n\t\t3. Search Patient Record: ");
    printf("\n\n\t\t4. Delete Patients Record: ");
    printf("\n\n\t\t5. Exit ");
    printf("\n\n\tChoose From 1 to 5: ");
    scanf("%d", &choose);
    switch (choose)
    {
    case 1:
        addRecord();
        break;
    case 2:
        funcList();
        break;
    case 3:
        searchRecord();
        break;
    case 4:
        dltRecord();
        break;
    //case 5:
      //  exitfunc();
        //break;
    
    default:
        printf("\n\n\t\tInvalid Entry");
        break;
    }
}

//Function to Exit
void exitfunc(void)
{
    printf("\n\n        Thanks For Using");
    getch();
}

//Function to take all the records and save it in file
void addRecord(void)
{
    char ans;
    int valid = 0;
    FILE *fp;
    fp = fopen("Record.dat", "a"); // We're using a dat file
    printf("\n\n\t\t   !!!!! Add Patients Record !!!!!");

    //Enter First Name
flag1:
    printf("\nEnter First Name: ");
    scanf("%s", p.firstName);
    p.firstName[0] = toupper(p.firstName[0]);
    for (int i = 0; i < strlen(p.firstName); i++)
    {
        if (isalpha(p.firstName[i]))
        {
            valid = 1;
        }
        else
        {
            valid = 0;
            break;
        }
    }
    if (!valid)
    {
        printf("\n\nInvalid! Enter name again");
        goto flag1;
    }

// Enter Last Name
flag2:
    printf("\nEnter Last Name: ");
    scanf("%s", p.lastName);
    p.lastName[0] = toupper(p.lastName[0]);
    for (int i = 0; i < strlen(p.lastName); i++)
    {
        if (isalpha(p.lastName[i]))
        {
            valid = 1;
        }
        else
        {
            valid = 0;
            break;
        }
    }
    if (!valid)
    {
        printf("\n\nInvalid! Enter name again");
        goto flag2;
    }

    //taking the gender input
    printf("\nEnter Gender(M/F): ");
    getchar();
    scanf("%c", &p.gender);
    p.gender = toupper(p.gender);
    //taking age input
    printf("\nEnter Age: ");
    scanf("%d", &p.age);
    getchar();
    //taking address input
    printf("\nEnter Address details: ");
    scanf("%[^\n]%*c", p.address);
    p.address[0] = toupper(p.address[0]);
    //Contact No
    printf("\nContact No: ");
    scanf("%s", p.contactNo);
    getchar();
    //enter problem
    printf("\nEnter patient's problem: ");
    scanf("%[^\n]%*c", p.problem);
    //prescribed doctor
    printf("\nEnter the name of the doctor: ");
    scanf("%[^\n]%*c", p.doctor);

    //saving the documents in file
    fprintf(fp, "%s %s %c %d %s %s %s %s ", p.firstName, p.lastName, p.gender, p.age, p.address, p.contactNo, p.problem, p.doctor);
    printf("\n\n\t\t Information Recorded Successfully!!!!!");
    fclose(fp);
flag3:
    getch();
    printf("\n\nDo you want to save more[Y/N] : ");
    scanf("%c", &ans);
    if (toupper(ans) == 'Y')
    {
        addRecord();
    }
    else
    {
        printf("\n\n\t\t Thanks for using!!!!!! ");
        getch();
        mainMenu();
    }
}

//func list function
void funcList()
{
    int raw = 65;
    FILE *ptr;
    ptr = fopen("Record.dat", "r");
    printf("\n\n\t\t\t!!!!!!!!!!!Patients Record!!!!!!!!!!!!!!!!\n\n");
    printf("  Full Name      Gender    Age        Address        ContactNo        Prblm     Doctor\n");
    printf("-----------------------------------------------------------------------------------------------------\n");
    while (fscanf(ptr, "%s %s %c %d %s %s %s %s", &p.firstName, &p.lastName, &p.gender, &p.age, &p.address, &p.contactNo, &p.problem, &p.doctor) != EOF)
    { 
        printf("%s %s     %c        %d        %s          %s             %s           %s\n",p.firstName,p.lastName,p.gender,p.age,p.address,p.contactNo,p.problem,p.doctor);
    }
    fclose(ptr);
    getch();
    mainMenu();
}

//Func to search record
void searchRecord(void)
{
    int found;
    char ans;
    char name[20];
    FILE *ptr;
    ptr = fopen("Record.dat", "r");
    printf("\n\n\t\t\t...................Search Record..........................\n");
    printf("\nEnter patient name to be viewed: ");
    scanf("%s", name);
    //fflush(stdin); //It will flush the enter key
    name[0] = toupper(name[0]);
    while (fscanf(ptr, "%s %s %c %d %s %s  %s %s", &p.firstName, &p.lastName, &p.gender, &p.age, &p.address, &p.contactNo, &p.problem, &p.doctor) != EOF)

    {
        if (strcmp(p.firstName, name) == 0)
        {
            printf("\n   Full Name      Gender    Age        Address        ContactNo        Prblm     Doctor\n");
            printf("---------------------------------------------------------------------------------------------------\n");
            printf("%s %s     %c        %d       %s       %s           %s        %s\n",p.firstName,p.lastName,p.gender,p.age,p.address,p.contactNo,p.problem,p.doctor);
            found = 1;
        }
    }
  
    if(!found){
        printf("\nRecord Not Found");
        getch();
    }
    fclose(ptr);
    flag:
    printf("\n\nDo you want to search more[Y/N]: ");
    getchar();
    scanf("%c",&ans);
    if (toupper(ans) == 'Y'){
        searchRecord();
    }
    else if(toupper(ans)=='N'){
        printf("\nThank You\n");
        mainMenu();
    }
    else{
        printf("\nWrong Input");
        goto flag;
    }
}

void dltRecord(void){

    int found=0;
    char name[20];
    FILE* tempptr = fopen("temp.dat","w");
    FILE* ptr = fopen("Record.dat","w");
    printf("\n\n\t\t\t...................Delete Record..........................\n");
    printf("Enter Name to delete: ");
    scanf("%s",name);
    name[0]=toupper(name[0]);;
    while (fscanf(ptr, "%s %s %c %d %s %s %s %s", &p.firstName, &p.lastName, &p.gender, &p.age, &p.address, &p.contactNo, &p.problem, &p.doctor) != EOF)
    {
        if(strcmp(p.firstName,name)!= 0){
            fprintf(tempptr,"%s %s %c %d %s %s %s %s",p.firstName, p.lastName, p.gender, p.age, p.address, p.contactNo, p.problem, p.doctor);
        }
        else{
            printf("%s %s     %c        %d        %s       %s         %s      %s\n",p.firstName,p.lastName,p.gender,p.age,p.address,p.contactNo,p.problem,p.doctor);
            found = 1;
        }
    }
    fclose(tempptr);
    fclose(ptr);
    if(found){
        remove("Record.dat");
        rename("temp.dat","Record.dat");
        printf("\nDeleted Successfully");
        getch();
        mainMenu();
    }
    else{
        printf("\nRecord not found!!!");
        getch();
        mainMenu();
    }

}