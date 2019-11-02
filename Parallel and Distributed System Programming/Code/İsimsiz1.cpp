#include <stdio.h>
#include <iostream> 
#include <stdlib.h> 
#include <math.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <windows.h> 

int main()
{
    int r=6000, c=6000, len=0; 
    int *ptrFirst, *ptrSecond, *ptrFinally ,**first,**second,**multiply; 
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
	 
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    printf("\n\n"); 
    for(int i=0; i<r; ++i){
     	 for(int j=0; j<r; ++j){
     	 	for(int k=0; k<r; ++k){
               multiply[i][j]+= first[i][k]*second[k][j];
            }
		  }
	 }
	 
	GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    printf("\n\n");
  return 0;
} 
