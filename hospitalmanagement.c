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
void gotoxy(short x, short y)
{ //Function to setup co-ordinate
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//Declaring The structure for file handling
struct hospitalmanagement
{
    int age;
    char gender;
    char firstName[20];
    char lastName[20];
    char contactNo[12];
    char address[30];
    char email[30];
    char doctor[15];
    char problem[20];
} p, temp_c;

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
            printf("\n\n\t\t\t\t    Login Succesfull.........");
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
    printf("\n\n\t\t4. Edit patients Record: ");
    printf("\n\n\t\t5. Delete Patients Record: ");
    printf("\n\n\t\t6. Exit");
    printf("\n\n\tChoose From 1 to 6: ");
    scanf("%d", &choose);
    switch (choose)
    {
    case 1:
        addRecord();
        break;
    /*case 2:
        funcList();
        break;
    case 3:
        searchRecord();
        break;
    case 4:
        editRecord();
        break;
    case 5:
        dltRecord();
        break;
    case 6:
        exitfunc();
        break;*/
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
    scanf("%c", &p.gender);
    getchar();
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
    //email input
    printf("\nEnter email id: ");
    scanf("%s", p.email);
    getchar();
    //enter problem
    printf("\nEnter patient's problem: ");
    scanf("%[^\n]%*c", p.problem);
    getchar();
    //prescribed doctor
    printf("Enter the name of the doctor: ");
    scanf("%[^\n]%*c", p.doctor);

    //saving the documents in file
    fprintf(fp, "%s %s %c %d %s %s %s %s %s", p.firstName, p.lastName, p.gender, p.age, p.address, p.contactNo, p.email, p.problem, p.doctor);
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
        printf("\n\nThanks for using: ");
        getch();
        mainMenu();
    }
}

//func list function
/*void funclist(){
    int raw;
    FILE* ptr;
    ptr = fopen("Record.dat","r");
    printf("\n\n\t\t\t!!!!!!!!!!!Patients Record!!!!!!!!!!!!!!!!");
    gotoxy(1,50);
    printf("Full Name");
}*/