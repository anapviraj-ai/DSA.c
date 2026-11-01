#include<stdio.h>
#include<stdlib.h>

int linear_search(int arr[100],int n,int key);
int binary_search(int arr[100],int n,int key);

int main()
{
    int arr[100], n, key, i, j, temp, choice, result;

    printf("Enter the no. of students : ");
    scanf("%d",&n);

    printf("Enter the Roll no. :\n");
    for (i=0; i<n; i++){
        scanf("%d",&arr[i]);
    }

    while(1)
    {
        printf("\n1.Linear search\n");
        printf("2.Binary search\n");
        printf("3.Exit.\n");
        printf("Enter your chice : ");
        scanf("%d",&choice);
        
        switch (choice)
        {
            case 1:
            {
                printf("Enter the no. to search :");
                scanf("%d",&key);

                result = linear_search(arr,n,key);

                if (result == -1) {
                    printf("Roll no. is not found.");
                }
                else{
                    printf("Roll no. is found at psition %d.",result+1);
                }
                break;
            }

            case 2:
            {
                for (i = 0; i < n-1; i++)
                {
                    for (j = 0; j < n-i-1; j++)
                    {
                        if (arr[j] > arr[j+1]){
                            temp = arr[j];
                            arr[j] = arr[j+1]; 
                            arr[j+1] = temp;
                        }
                    }
                }

                printf("\nThe array is sorted for Binary search.\n");
                printf("Enter roll no. to search : ");
                scanf("%d",&key);

                result = binary_search(arr,n,key);

                if (result == -1){
                    printf("Roll no. is not found.");
                }
                else{
                    printf("Roll no. found at position %d",result+1);
                }
                break;
            }

            case 3:
                printf("\nExiting...\n");
                exit(0);

            default :
                printf("Invalid choice!");    

        }
    }
    return 0;
}

int linear_search(int arr[100], int n, int key)
{
    for (int i = 0; i < n ; i++){
        if (arr[i] == key){
            return i;
        }    
    }
    return -1;
}

int binary_search(int arr[100], int n, int key)
{
    int low = 0, high = n-1, mid;

    while (low <= high)
    {
        mid = (low + high) / 2 ;

        if (arr[mid] == key ){
            return mid;
        }
        else if (key < arr[mid]){
            high = mid - 1;
        }
        else{
            low = mid + 1; 
        }
    }

    return -1;
}