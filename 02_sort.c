#include <stdio.h>
#include <stdlib.h>

void selection_sort(int arr[100], int n);
void bubble_sort(int arr[100], int n);

int main()
{
    int arr[100], n, ch;

    printf("Enter the size of array : ");
    scanf("%d", &n);

    printf("Enter the array : \n");
    for (int i = 0; i < n; i++)
    {
        printf("arr[%d] : ", i);
        scanf("%d", &arr[i]);
    }

    while (1)
    {
        printf("\n1. Selection sort\n");
        printf("2. Bubble sort\n");
        printf("3. Exit\n");
        printf("Enter your choice. : ");
        scanf("%d",&ch);

        switch (ch)
        {
        case 1:
            selection_sort(arr, n);
            break;

        case 2:
            bubble_sort(arr, n);
            break;

        case 3:
            printf("\nExiting..\n");
            exit(0);

        default:
            printf("Invalid choice");
        }
    }

    return 0;
}

void selection_sort(int arr[100], int n)
{
    int i, j, minIndex, temp;
    printf("\nIn Selection sort..\n");

    for (i = 0; i < n - 1; i++)
    {
        minIndex = i;

        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
            temp = arr[minIndex];
            arr[minIndex] = arr[j];
            arr[j] = temp;
        }
    }

    printf("The sorted array is : \n");
    for (i = 0; i < n; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
}

void bubble_sort(int arr[100], int n)
{
    int i, j, temp;
    printf("\nIn Bubble sort..\n");

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("The sorted array is :\n");
    for (i = 0; i < n; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
}