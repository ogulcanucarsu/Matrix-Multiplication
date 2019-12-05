#include <stdio.h>
#include <iostream> 
#include <stdlib.h> 
#include <math.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <windows.h> 
#include<pthread.h> 
#include<unistd.h> 

//Each thread computes single element in the resultant matrix 
void *mult(void* arg) 
{ 
    int *data = (int *)arg; 
    int k = 0, i = 0; 
      
    int x = data[0]; 
    for (i = 1; i <= x; i++) 
           k += data[i]*data[i+x]; 
      
    int *p = (int*)malloc(sizeof(int)); 
         *p = k; 
      
//Used to terminate a thread and the return value is passed as a pointer 
    pthread_exit(p); 
} 

int main()
{
    int r=2500, c=2500, len=0; 
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
	
	int max = c*r; 
      
    //declaring array of threads of size r1*c2         
    pthread_t *threads; 
    threads = (pthread_t*)malloc(max*sizeof(pthread_t)); 

 	int count2 = 0; 
    //int* data = NULL; 
    for (int i = 0; i < r; i++){
    	     for (int j = 0; j < c; j++) 
        {      
            //storing row and column elements in data  
            //data = (int *)malloc((3000)*sizeof(int)); 
            //data[0] = c1; 
            //for (int k = 0; k < c; k++) 
           //     multiply[k+1] = first[i][k]; 
      
           // for (int k = 0; k < r; k++) 
           //     multiply[k+c+1] = second[k][j]; 
               
             //creating threads 
                pthread_create(&threads[count2++], NULL,mult, (void*)(multiply)); 
                  
        } 
	} 
	
	printf("RESULTANT MATRIX IS :- \n"); 
    for (i = 0; i < c; i++)  
    { 
      void *k; 
        
      //Joining all threads and collecting return value  
      pthread_join(threads[i], &k); 
               
      int *p = (int *)k; 
      printf("%d ",*p); 
      if ((i + 1) % c == 0) 
          printf("\n"); 
    } 
   
	return 0;
} 


  
	       
    /*        
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
	printf("\n\n");*/
        

