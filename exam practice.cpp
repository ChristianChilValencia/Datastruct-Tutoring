#include <stdio.h>

int add(int a,int b, int c, int times[2][3][3]);
void display(int a,int b,int c,float average,int times[2][3][3],int count);


int main(){
	int times[2][3][3];
	int a = 0;
	int b = 0;
	int c = 0;
	float average;
	int count = 0;
	
	for(a = 0;a<2;a++){
		printf("Matrix %d: \n", a+1);
		for(b = 0;b<3;b++){
			for(c = 0;c<3;c++){
				scanf("%d",&times[a][b][c]);
			}
		}
	}
	
	average = add(a,b,c,times);
	
	printf("\n");
	
	
	display(a,b,c,average,times,count);
	
	
	

}

int add(int a,int b, int c, int times[2][3][3]){
       int add = 0;
       
		for(a = 1;a<2;a++){
		for(b = 0;b<3;b++){
			for(c = 0;c<3;c++){
				add+=times[a][b][c];
			}
		}
	}
	
	return add;
	
}

void display(int a,int b,int c,float average,int times[2][3][3],int count){
	
		for(a = 1;a<2;a++){
		for(b = 0;b<3;b++){
			for(c = 0;c<3;c++){
				count++;
			}
		}
	}
	
	printf("Matrix 3: \n");
	for(a = 0;a<1;a++){
		for(b = 0;b<3;b++){
			for(c = 0;c<3;c++){
				printf("%.2f ", (times[a][b][c]*average)/count);
			}
			printf("\n");
		}
	}
		
}
   
