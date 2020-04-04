#include <stdio.h>
#include <iostream> 
#include <stdlib.h> 
#include <math.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <windows.h> 
#include <lapacke.h>
#include <cblas.h>
int main()
{
    int r=10000, c=10000, len=0; 
    int *ptrFirst, *ptrSecond, *ptrFinally;
	int **first,**second;
	int **multiply; 	
    int count = 0,i,j; 
    SYSTEMTIME t;
  
    len = sizeof(int *) * r + sizeof(int) * c * r;
    
    first = (int **)malloc(len); 
    second = (int **)malloc(len);  
    multiply = (int **)malloc(len); 

  
    ptrFirst = (int *)(first + r); 
    ptrSecond = (int *)(second + r); 
    ptrFinally= (int *)(multiply + r); 
    
  
   for(i = 0; i < r; i++) 
        first[i] = (ptrFirst + c * i); 
        
   for(i = 0; i < r; i++) 
        second[i] = (ptrSecond + c * i); 
              
   for(i = 0; i < r; i++) 
        multiply[i] = (ptrFinally + c * i); 		 
        
   for (i = 0; i < r; i++) 
        for (j = 0; j < c; j++) 
            first[i][j] = rand()%21+10;
            
   for (i = 0; i < r; i++) 
        for (j = 0; j < c; j++) 
            second[i][j] = rand()%21+10;
                 			
	 for(int i=0; i<r; ++i){
     	for(int j=0; j<c; ++j){
            multiply[i][j]= 0;
		}
	}
	       
            
    //i, j1, j2, k         
	printf("i, j1, j2, k basladi");
	printf("\n\n");
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    printf("\n\n"); 
    for(int i=0; i<r; ++i){
     	 for(int j=0; j<r; ++j){
     	 	for(int k=0; k<r; ++k){
               multiply[i][k]+= first[i][j]*second[j][k];
            }
		  }
	 }
	 
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
	printf("\n\n");
    printf("i, j1, j2, k bitti");
	printf("\n\n");
    
    
    // j, i1, i2, k       	
	printf(" j, i1, i2, k basladi");
	printf("\n\n");
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    printf("\n\n"); 
    for(int j=0; j<r; ++j){
     	 for(int i=0; i<r; ++i){
     	 	for(int k=0; k<r; ++k){
               multiply[i][k]+= first[i][j]*second[j][k];
            }
		  }
	}
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
	printf("\n\n");
    printf("j, i1, i2, k bitti");
	printf("\n\n");
        
    // i, k1, k2, j    
    printf("i, k1, k2, j basladi");
	printf("\n\n");
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    printf("\n\n"); 
    for(int i=0; i<r; ++i){
     	 for(int k=0; k<r; ++k){
     	 	for(int j=0; j<r; ++j){
               multiply[i][k]+= first[i][j]*second[j][k];
            }
		  }
	}
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
	printf("\n\n");
    printf("i, k1, k2, j bitti");
	printf("\n\n");
    
    // k, i1, i2, j
    printf(" k, i1, i2, j basladi");
	printf("\n\n");
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    printf("\n\n"); 
    for(int k=0; k<r; ++k){
     	 for(int i=0; i<r; ++i){
     	 	for(int j=0; j<r; ++j){
               multiply[i][k]+= first[i][j]*second[j][k];
            }
		  }
	}
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
	printf("\n\n");
    printf(" k, i1, i2, j bitti ");
	printf("\n\n");
	
	//j, k1, k2, i
	printf("j, k1, k2, i basladi");
	printf("\n\n");
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    printf("\n\n"); 
    for(int j=0; j<r; ++j){
     	 for(int k=0; k<r; ++k){
     	 	for(int i=0; i<r; ++i){
               multiply[i][k]+= first[i][j]*second[j][k];
            }
		  }
	}
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
	printf("\n\n");
    printf("j, k1, k2, i bitti ");
	printf("\n\n");
	
	//k, j1, j2, i
	printf("k, j1, j2, i basladi");
	printf("\n\n");
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    printf("\n\n"); 
    for(int k=0; k<r; ++k){
     	 for(int j=0; j<r; ++j){
     	 	for(int i=0; i<r; ++i){
               multiply[i][k]+= first[i][j]*second[j][k];
            }
		  }
	}
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
	printf("\n\n");
    printf("k, j1, j2, i bitti ");
	printf("\n\n");
        
  return 0;
} 
