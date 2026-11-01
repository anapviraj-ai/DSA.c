#include<stdio.h>
#include<stdlib.h>

int arr[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

void display();
void linear();
void quadratic();
void doublehashig();

int main()
{
    int ch;

    while(1)
    {
        printf("1. Linear probing\n");
        printf("2. Quadratic probing\n");
        printf("3. Double hashing\n");
        printf("4. Exit..\n");
        printf("Enter your choice : ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1:
                linear();
                break;

            case 2:
                quadratic();
                break;
                
            case 3:
                doublehashig();
                break;
                
            case 4:
                printf("\nExiting\n");  
                exit(0);
                
            default :
                printf("\nInvalid choice\n");
        }
    }

    return 0;
}

void display()
{
    printf("\nThe hash table is.");
    for (int i=0; i < 10; i++)
    {
        printf("\narr[%d] = %d ",i,arr[i]);
    }
    printf("\n\n");
}

void linear()
{
    int key, h, i, n, start;
    printf("Enter the no. of elements : ");
    scanf("%d",&n);

    for (i = 0; i < n; i++)
    {
        printf("Enter the element to insert : ");
        scanf("%d",&key);
        
        h = key % 10;
        start = h;

        while (arr[h] != -1)
        {
            h = (h+1) %10;
            if (h == start)
            {
                printf("Hash table is full");
                break ;
            }
        }
        arr[h] = key;
    }
    display();
}

void quadratic()
{
    int key, h, i, n, start, j;
    printf("Enter no. of elements :");
    scanf("%d",&n);

    for(j = 0; j < n; j++)
    {
        printf("Enter no. to insert : ");
        scanf("%d", &key);
        i = 0;

        h = key % 10;
        start = h;

        while(arr[h] != -1)
        {
            h = (h + (i*i)) % 10;
            if (arr[h] == -1)
            {
                break;
            }
            if(i == 10)
            {
                printf("hash is full");
                break;
            }
            i++;
        }
        arr[h] = key;
    }
    display();
}

void doublehashig()
{
    int key, h, i, n, start, j, h1, h2;
    printf("Enter the no. of element : ");
    scanf("%d",&n);

    for (j = 0; j < n; j++)
    {
        printf("Enter no. to insert : " );
        scanf("%d", &key);


        i = 0;
        h1 = key % 10;
        h = h1;

        while(arr[h] != -1)
        {
            h2 = 7 - (key % 7);
            h = (h1 + i*h2)% 10;

            if(arr[h] == -1)
            {
                break;
            } 
            if(i == 10)   
            {
                printf("Hash table is full");
                break;
            }
            i++;
        }
        arr[h] = key;
    }
    display();
}