#include <stdio.h>

void inputData(int *, int);
int getFrequency(int *, int, int);


int main(void) {
	const int SIZE = 5; 
	int intArray[SIZE], target, frequency=0;
	
	inputData(intArray, SIZE);
	printf("Input a number to be searched: ");
	scanf("%d", &target);
	frequency = getFrequency(intArray, SIZE, target);
	printf("Frequency = %d\n", frequency);
	return 0;
}

void inputData(int *array, int length) {
	int k;
	
	printf("Input %d integers: ", length);
	for (k=0; k<length; k++)
		scanf("%d", &array[k]);
}

int getFrequency(int *array, int length, int target) {
	int k, count=0;
	
	for (k=0; k<length; k++)	
		if (target == array[k])
			count++;
	
	return count;
}
