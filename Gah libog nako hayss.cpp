#include <stdio.h>

int insert(int size,int a[],int element, int temp);
int remove(int size,int a[], int element, int del);


int main(){
	int choice;
	int size;
	int element,temp;
    int del;

	
	printf("Enter the size first: ");
	scanf("%d", &size);
	
	int a[size];
	
	printf("Enter integer to store: ");
	for(int i = 0;i<size;i++){
		scanf("%d", &a[i]);
	}

	
	do{
	printf("\n=========\n");
	printf("1. Insert\n");
	printf("2. Delete\n");
	printf("3. Exit\n");
	printf("=========\n\n");
	
	printf("Stored Integer: ");
	for(int i = 0;i<size;i++){
		printf("%d ", a[i]);
	}
	
	printf("\n");
	
	printf("\nChoose: ");
	scanf("%d", &choice);
	

	
	switch(choice){
		case 1: 
		printf("Enter the element you wanna insert: ");
		scanf("%d", &element);
		printf("Which in the index you wanna insert: ");
		scanf("%d", &temp);
		temp--;
		size = insert(size,a,element,temp);
		break;
		case 2:
		printf("Enter the element you wanna delete: ");
		scanf("%d", &del); 
		size = remove(size,a,element,del);
		break;
		case 3: printf("\n!!Thanks for Using my friend!!"); break;
		default: printf("Not in the list my friend\n"); break;
	}
		
	}while(choice!=3);
	
	return 0;
}

int insert(int size,int a[],int element, int temp){
	if(temp > size){
		printf("It is not in the index >:(\n");
		return size;		
		}
		
		
	for(int i = size-1;i>=temp;i--){
		a[i+1] = a[i];
	}
   a[temp] = element;
   
   return (size+1);
}

int remove(int size, int a[], int element, int del) {
    int found = 0;  

    for (int i = 0;i<size; i++) {
        if (a[i] == del) {
            found++;
            for (int j = i;j<size-1; j++) {
                a[j] = a[j + 1];
            }
        }
    }

    if (found > 0) {
        printf("Element %d found :)\n", del);
        return size - 1;
    } else {
        printf("No such element with %d\n", del);
        return size;
    }
}
