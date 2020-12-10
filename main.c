#include <stdio.h>
#include <stdlib.h>
#include <strings.h>



#define BOOKS "books.txt"
#define LENDING "lendings.txt"



int auth();
void lib();
void stu();
void screen(int index);
void borrowed_books();
void bookmenu();
void lendings();
int fines();
void addBook();
void filereadbooks(); 
void addLender();

//Global variables       -----------------------------------
int finesamount = 500;
int no_of_books = 0;
int lended_books = 5;
char books[100][100];
char author[100][100];
int copies[100];
char lender[100][100];
char lendbook[100][100];
int date[100];
int no_of_books;
//-------------------------------------------------------------------
int main(void)
{	
	
	int option = 0;
	while (1)
	{
	system("cls");
	printf("\t\t\t\tLIBRARY MANAGEMENT SYSTEM\n");
	printf("\t\t\t\t\t Login as a:\n\t\t\t 1 - Librarian\n\t\t\t 2 - Student\n\t\t\t 3 - Exit \n");
	filereadbooks();
	lendings();
	printf("\nEnter your option : ");
	scanf("%d", &option);
	if (option == 1)
	{
		if (auth() == 10)
		{
			lib();
		}
		else{
			continue;
		}
	}
	else if ( option == 2)
	{
		stu();
	}
	else{
		break;
	}
	}
}

void filereadbooks()
{
	char *token;
	FILE *fp = NULL;
	fp = fopen(BOOKS, "r");
	char buffer [1024];
	int i = 0;
	srand(time(0));
	if (fp == NULL)
	{
		printf("Error \n");
		
	}
	rewind(fp);
	while(fgets(buffer, 1024, fp) != NULL)
	{
		
		token = strtok(buffer, ",");
		strcpy(books[i], token);
		token = strtok(NULL, ",");
		strcpy(author[i], token);
		copies[i] = (rand() % 25) + 1;
		++i;
	}
	no_of_books = i;
	fclose(fp);
	fp = NULL;
}


void lib()
{
	int option = -1;
	while (1)
	{
	system("cls");
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tWelcome Librarian!\n");
    printf("\t\t\t1-View Inventory\n\t\t\t2-View Lendings\n\t\t\t3-Issue a Book\n\t\t\t4-Add a book\n\t\t\t5-exit\n\t\t\t");
    printf("Enter the number associated with the option: ");
    scanf("%d", &option);
    if (option == 1)
    {
        bookmenu();
    }
    else if (option == 2)
    {
        borrowed_books();
    }
    else if (option == 3)
    {
        addLender();
    }
    else if (option == 4)
    {
        addBook();
    }
    else if (option == 5)
    {
		return;
	}
	}
}

void stu()
{
    int option = 0;
    while (1)
	{
	system("cls");
    printf("-------------------------           Welcome Students!            --------------------------------------------------------------------------\n");
    printf("Welcome Students!\n");
    printf("\n\t\t\t1-View borrowed books\n\t\t\t2-Fines\n\t\t\t3-List books availabe\n\t\t\t4-Lend a book\n\t\t\t5-exit\n");
    printf("Enter the number before the option to choose the action: ");
    scanf("%d", &option);
    if (option == 3)
    {
        bookmenu();
    }
    else if (option == 1)
    {
        lendings();
    }
    else if (option == 2)
    {
        fines();
    }
    else if(option==5)
    {
    	return;
	}
	
    /*else (option == 4)
    {
        stulending();
    }*/
	}
}




// Add lender function here
void addLender()
{

	system("cls");
	char name[20], title[20];
	
	printf("\n\n\t\tEnter the name of the student : ");
	scanf(" %[^\n]s", &name);
	strcpy(lender[no_of_lendings], name);
	
	printf("Enter the name of the book : ");
	scanf(" %[^\n]s", &title);
	strcpy(lendbook[no_of_lendings], title);
	
	date[no_of_lendings] = 24 * 7;
	printf("The student has 7 days to return the book.");
	no_of_lendings++;
	printf("No of lending : %d", no_of_lendings);
	FILE *fp;
	fp = fopen("Lending.txt", "w");
	int i;
	for (i = 0; i < no_of_lendings; i++)
	{
		fprintf( fp,"%s,%s,%d\n", lender[i], lendbook[i], date[i]);
	}
	fclose(fp);
	fp = NULL;
	return;
}



// login
int auth()
{
	char garbage_variable;
	int incorrect = 1;
	int found = -1;
	while (incorrect <= 3 && found == -1)
	{
	char password[8] = {'p', 'a', 's', 's','w','o','r', 'd'};
	char libps[20];
	found = 1;
	char c = ' ';
	system("cls");
	printf("\n\n\n\n\t\t\t\t\tWELCOME LIBRARIAN.\n");
	int i = 0;
	printf("\t\t\t\t\tEnter password : ");
	while (c != 13 && c != '\r' && c!='\n' && c != 10)
	{ 
	c = getch();
	if (c == 8)
	{
		continue;
	}
	else {
		if ( c != 13 && c != '\n' && c != '\r')
		{
			printf("*");
			libps[i] = c;
			i++;
		}
	}
	}
		
	if ( i == 8)
	{
		for ( i = 0; i < 8; i++ )
		{
			if (libps[i] != password[i])
			{
				found = -1;
			}
		}
	}
	else {
			
			found = -1;
	}
	if (found == -1 )
	{
		printf("\n\n\t\t\t\t\tPassword Not Found\n");
		++incorrect;
		printf("\t\t\t\t\tYou have %d attempt(s) left. Press Enter to continue", 3 - incorrect);
		scanf("%c", &garbage_variable);
	}
	else 
	{
		printf("\n\n\t\t\t\t\tPassword Found\n");
		return 10;
	}
	
	}
	return -10;
}

void bookmenu()
{

	system("cls");
	printf("--------------------------------------Books page--------------------------------------------------------------------------\n");
	char bookgarbage;
	int i = 0;
	printf("%3s %25s %20s %6s\n","SNo", "Title", "Author", "Copies");
	for (i = 0; i < 5; i++)
	{
		printf("%3d %25s %20s %6d\n", i+1, books[i], author[i], copies[i]);
	}
	printf("\nPress Enter to exit : ");
	scanf(" %c", &bookgarbage);
	return;
}


void lendings()
	{
		
		char *token;
		FILE *fp = NULL;
		fp = fopen("Lending.txt", "r");
		char buffer [1024];
		int i = 0;
		srand(time(0));
		if (fp == NULL)
		{
			printf("Error \n");
			return;
		}
		rewind(fp);
		while(fgets(buffer, 1024, fp) != NULL)
		{
		
			token = strtok(buffer, ",");
			strcpy(lender[i], token);
			token = strtok(NULL, ",");
			strcpy(lendbook[i], token);
			token = strtok(NULL, ",");
			sscanf(token, "%d", &date[i]);
			++i;
		}
		fclose(fp);
		no_of_lendings = i;
		fp = NULL;
		printf("No of lending : %d", no_of_lendings);
		getch();
		return;
}

int fines()
{
	int late = 50, damaged = 1000, condition;
	printf("1 - %d is the fine for returning books late.\n", late);
	printf("2 - %d is the fine for returning damaged books.\n", damaged);
    printf("\n\t Enter 1 for late repayment and 2 for damaged books\n");
    scanf("%d", &condition);
    if (condition == 1)
    {
        printf("Take 50 rupees from the student\n");
        finesamount += late;
        printf("%d is the total value of fine collected\n", finesamount);
    }
    else if (condition == 2)
    {
        printf("Take 10000 rupees from the student:\n");
        finesamount += damaged;
        printf("%d is the total value of fine collected\n", finesamount);
    }
    return finesamount;
}


void borrowed_books()
{
    system("cls");
    //Borrowed books by students
    int i;
    printf("%3s %15s %15s %6s\n","SNo", "Student", "Book", "Days Left");
    for (i = 0; i < 5; i++)
	{
		printf("%3d %15s %15s %6d\n", i+1, lender[i], lendbook[i], date[i] / 24);
	}
	printf("\nPress Enter to exit : ");
	getch();
    
}

void addBook()
{
    /*
	char name[100];
    int i;
    printf("Enter the name of the book you want to add :");
    fgets(name, sizeof(name), stdin);
    strcpy(arr[number_of_books], name);
    number_of_books++;
    	for (i = 0; i < number_of_books; i++)
	{
		printf("%d - ", i+1);
		puts(arr[i]);
	}
	*/
}
