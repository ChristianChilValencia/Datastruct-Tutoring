#include <stdio.h>
#include <string.h>

typedef struct{
	float price[5][20];
	char item[5][20];
}PAP;

int main(){
	PAP p;
	int i;

	
	printf("Enter char: \n");
	for(i = 0;i<5;i++){	
			fgets(p.item[i], sizeof(p.item[i]), stdin);
			p.item[i][strlen(p.item[i]) - 1] = '\0';
	}
	
	printf("Enter Price you Pedofile: \n");
	for(i = 0;i<5;i++){
		scanf("%f", &p.price[i]);
		getchar();
	}
	
	printf("\n");
    
    
    printf("--Items--\n");
   for(i = 0;i<5;i++){
   	printf("%d. %s\n", i+1,p.item[i]);
   }
   printf("\n");
   
    printf("--Price of each item--\n");
	for(i = 0;i<5;i++){
   	printf("%d. %.2f\n",i+1,*p.price[i]);
   }
	
}
