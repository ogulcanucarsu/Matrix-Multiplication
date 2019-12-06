#pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline") //Optimization flags
#pragma GCC option("arch=native", "tune=native", "no-zero-upper") //Enable AVX
#pragma GCC target("avx")  //Enable AVX

#include <stdio.h>
#include <iostream> 
#include <stdlib.h> 
#include <math.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <windows.h> 
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

#define DIM 10000

void single_multiply(int rowStart, int rowEnd);
void *thread_multiply(void *offset);
int cores = 4;
int r=10000, c=10000, len=0; 
int **first,**second;
int **multiply; 	 
int *ptrFirst, *ptrSecond, *ptrFinally;

int main()
{
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
	
	  int rows_por_thread = DIM / cores;
      printf("Thread basina satir sayisi -> %i", rows_por_thread);
      printf("\n");
      int rest = DIM % cores;
      GetLocalTime(&t);
      printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
      printf("\n");
       if (rest == 0) {
            int times = rows_por_thread;
            pthread_t threads[cores];
            int thread_args[cores];
            int i = 0;
            int error;
            for (int c = 0; c < DIM; c += rows_por_thread) {
                thread_args[i] = c;
                i++;
            }
            for (int c = 0; c < cores; c++) {
                error = pthread_create(&threads[c], NULL, thread_multiply, (void *) &thread_args[c]);
                if (error != 0) { //Error durumu kontrol edilir
                    printf("Thread olusurken hata meydana geldi -> %i", c);
                    printf("\n");
                }
                printf("Thread yaratildi n -> %i argumanlari -> %i", c, thread_args[c]);
                printf("\n");
            }
            printf("Threadler calisiyor");
            printf("\n");
            for (int c = 0; c < cores; c++) {
                error = pthread_join(threads[c], NULL);
                if (error != 0) { // Threadler tekrar birleþirken hata durumu
                    printf("Join icin hata alan thread -> %i ", c);
                    printf("\n\n");
                }
                printf("Join icin bekleyen thread n -> %i", c);
                printf("\n");
            }
        } else {
            printf("\n");
            pthread_t threads[cores];
            int thread_args[cores];
            int i = 0;
            int entrypoint_residual_rows = 0;
            for (int c = 0; c < DIM - rest; c += rows_por_thread) {
                thread_args[i] = c;
                i++;
            }
            entrypoint_residual_rows = cores * rows_por_thread;
            int error;
            for (int c = 0; c < cores; c++) {
                error = pthread_create(&threads[c], NULL, thread_multiply, (void *) &thread_args[c]);
                if (error != 0) {
                    printf("Thread olusurken hata meydana geldi -> %i", c);
                    printf("\n");
                }
                printf("Thread yaratildi n:%i argumanlari -> %i", c, thread_args[c]);
                printf("\n");
            }
            printf("Threadler calisiyor");
            printf("\n");
            for (int c = 0; c < cores; c++) {
                pthread_join(threads[c], NULL);
                printf("Join icin hata alan thread -> %i", c);
                printf("\n");
            }
            single_multiply(entrypoint_residual_rows, DIM);
		}
    printf("Butun threalder join oldu");
    printf("\n");
    GetLocalTime(&t);
	printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
	printf("\n");
		
	return 0;
} 
void single_multiply(int rowStart, int rowEnd) {
    for (int i = rowStart; i < rowEnd; i++) {
        for (int j = 0; j < DIM; j++) {
            *(ptrFinally + i * DIM + j) = 0;
            for (int k = 0; k < DIM; k++) {
                *(ptrFinally + i * DIM + j) += *(ptrFirst + i * DIM + k) * *(ptrSecond + k * DIM + j);
            }
        }
    }
}
void *thread_multiply(void *offset) {
    int *row_offset = (int *) offset;
    printf("Isleme basladigi satir -> %i, islemin bitecegi satir -> %i ", *row_offset, *row_offset + (DIM / cores));
   	printf("\n");
    single_multiply(*row_offset, *row_offset + (DIM / cores));
    printf("Islemin bitti, satir -> %i", *row_offset + (DIM / cores));
    printf("\n");
    return NULL;
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
        

