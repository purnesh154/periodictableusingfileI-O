#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char dir[] = "db.txt";

struct element
{
    int no;
    float wt;
    char sym[3];
    char name[10];
};

struct element data[110];

int ptr = 0; 
struct element addElement(int no_, float wt_, char sym_[3], char name_[10] );
void saveEle(struct element e);
void printEle(struct element);
void printAllEle();
void restore();
int searchElementBySym(char sym_[3]);
void UserInputElement();
void displayOptions();
void searchElementOptions();

int main()
{

    int userSelection = 0;
    do
    {
        displayOptions();
        scanf("%d", &userSelection);
        if(userSelection==1)
        {
            UserInputElement();
        }
        else if(userSelection==2)
        {
            printf("\nNumber\tWeight\tSymbol\tName\n");
            printf("--------------------------------\n");
            printAllEle();
        }
        else if(userSelection==3)
        {
            int searchOption = 0;

            searchElementOptions();
            scanf("%d", &searchOption);
            restore();
            if(searchOption==1)
            {
                printf("\nAtomic Number > ");
                int AtomicNumber = 0;
                scanf("%d", &AtomicNumber);
                printf("\nNumber\tWeight\tSymbol\tName\n");
                printf("--------------------------------\n");
                if(data[AtomicNumber-1].no!=0)
                {
                    printEle(data[AtomicNumber-1]);
                }
                else
                {
                    printf("Sorry Element is not present in the database\n");
                }

            }
            else if(searchOption==2)
            {
                printf("\nSymbol > ");
                char sym[3];
                scanf("%s", sym);
                int loc = searchElementBySym(sym);
                if(loc!=-1)
                {
                    printf("\nNumber\tWeight\tSymbol\tName\n");
                    printf("--------------------------------\n");
                    printEle(data[loc]);
                }
                else
                {
                    printf("Sorry Element is not present in the database\n");
                }
            }
            else if(searchOption==3)
            {

            }



        }
    } while (userSelection!=4);
    
    printf("\n\nThanks!!\n\n");

    return 0;
}


void printEle(struct element a1)
{
    // this function prints the details of given structure element
    printf("%d\t| %0.2f\t| %s\t| %s\n", a1.no, a1.wt, a1.sym, a1.name);
}

struct element addElement(int no_, float wt_, char sym_[3], char name_[10] )
{
    struct element temp;
    temp.no = no_;
    temp.wt = wt_;
    strcpy(temp.name, name_);
    strcpy(temp.sym, sym_);
    return temp;
}

void saveEle(struct element e)
{
    FILE *fout;
    fout =fopen(dir, "a");
    fwrite(&e, sizeof(struct element), 1, fout);
    fclose(fout);
}


void printAllEle()
{
    FILE *fin;
    fin =fopen(dir, "r");
    if(fin==NULL)
    {
        printf("Sorry File is empty, try adding elements");
    }
    struct element temp;
    while(fread(&temp, sizeof(struct element), 1, fin))
    {
        printEle(temp);
        // printf("\n");
    }

}





void restore()
{
    FILE *fin;
    fin =fopen(dir, "r");
    if(fin==NULL)
    {
        printf("Sorry File is empty, try adding elements");
    }

    ptr=0;
    struct element temp;
    while(fread(&temp, sizeof(struct element), 1, fin))
    {
        data[ptr]=temp;
        ptr++;
    }
    fclose(fin);

}


int searchElementBySym(char sym_[3])
{
    int i =0;
    while(i<110)
    {
        if(data[i].no==0)
        {
            return -1;
            break;
        }
        if(strcmp(sym_, data[i].sym)==0)
        {
            return i;
            break;
        }
        i++;
    }
    return -1;
}

void   UserInputElement()
{
    int no;
    float wt;
    char sym[3];
    char name[10];
    printf("Element : \nAtomic Number : ");
    scanf("%d", &no);
    printf("Symbol \t: ");
    scanf("%s", sym);
    printf("Atomic Weight : ");
    scanf("%f", &wt);
    printf("Name \t: ");
    scanf("%s", name);
    struct element temp = addElement(no, wt, sym, name);
    saveEle(temp);
}

void displayOptions()
{
    printf("\n--------------------------------");
    printf("\n\nPeriodic Table Program\n");
    printf("\n1 -> Add Element");
    printf("\n2 -> Show All Elements");
    printf("\n3 -> Search Element");
    printf("\n4 -> Exit Program\n\nHome > ");

}


void searchElementOptions()
{
    printf("\n1 -> Search By Atomic Number");
    printf("\n2 -> Search Element By Symbol");
    printf("\n3 -> Go Back\n\nHome/Options > ");
}