#include <stdio.h>

int insert(int size, int a[], int element, int temp);
int remove(int size, int a[],int del);
int linear(int size, int a[], int search);
int binary(int size, int a[], int search);

int main(){
	int temp,del;
	int choice;
	int size;
	int search;
	int element;
	
	
	printf("Enter Size of your array: ");
	scanf("%d", &size);
	
    int a[size];
    
    printf("Enter the integer: ");
    for(int i = 0;i<size;i++){
    	scanf("%d", &a[i]);
	}
	printf("\n");
	
	
	do{
		printf("1. Insert\n");
		printf("2. Delete\n");
		printf("3. Linear\n");
		printf("4. Binary\n");
		printf("5. Exit\n\n");
		
	printf("Stored Integer: ");
    for(int i = 0;i<size;i++){
    	printf("%d ", a[i]);
	}
	printf("\n");
	
	printf("Choose: ");
	scanf("%d", &choice);
	
	switch(choice){
		case 1: 
		printf("Which element you want to insert: ");
		scanf("%d", &element);
		printf("Which index you wanna insert: ");
		scanf("%d", &temp);
		temp--;
		printf("\n"); 
		size = insert(size,a, element,temp);
		break;
		case 2:
		printf("Which part you wanna remove: ");
		scanf("%d", &del);
		printf("\n");
		size = remove(size,a,del);
		break;
		case 3: 
		printf("Which integer you wanna find?: ");
		scanf("%d", &search);
		linear(size,a,search);
		break;
		case 4:
		printf("Which integer you wanna find: ");
		scanf("%d", &search);
		binary(size,a,search);
		break;
		case 5: printf("\nThanks for using :)\n"); break;
		default: printf("No such thing cuh\n\n"); break;
	}
		
		
	}while(choice!=5);
}

int insert(int size, int a[], int element, int temp){
	
	if(temp>size){
		printf("Not in the index sorry :(\n");
		return size;
	}
	
	
	for(int i = size;i>=temp;i--){
		a[i+1] = a[i];
	}
	a[temp] = element;
	
	return (size+1);
}

int remove(int size, int a[],int del){
	int found = 0;
	
	for(int i = 0;i<size;i++){
		if(a[i] == del){
			found++;
			for(int j = i;j<size-1;j++){
				a[j] = a[j+1];
			}
		}
	}
	
	if(found > 0){
		return size - 1;
	}else{
		return size;
	}
}

int linear(int size, int a[], int search){
	for(int i = 0;i<size;i++){
		if(search == a[i]){
			printf("Element %d is found at index [%d]\n\n", search,i);
			return size;
		}
	}
	
	printf("No such thing :(\n\n");
	return size;
}

int binary(int size, int a[], int search){
	int left = 0;
	int increase = size;
	int decrease = 0;
	
	while(left<=size-1){
		int mid = left + (size-left)/2;
		
		if(search == a[mid]){
			printf("Element %d is in index %d\n\n", search, a[mid-1]);
			return 1;
		}
		if(a[mid]>search){
			size = mid;
			increase = mid;
		}else{
			left = mid+1;
			decrease = mid;
		}
	}
	
	return size;
}
