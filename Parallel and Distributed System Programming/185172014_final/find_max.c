/*
 1 Integer -> 4 byte
 10 Integer -> 40 byte
 100 Integer -> 400 byte 
 1000 Integer -> 4000 byte = 4 MB
 10.000 Integer -> 40.000 byte = 40 MB
 100.000 Integer -> 400.000 byte = 400 MB
 1.000.000 Integer -> 4.000.000 byte = 4000 MB = 4GB
*/

/*
printf("Dizi uzunlugu %d\n",array_len);
printf("cekirdek sayisi %d\n", num_proc);
printf("Bolum %d\n", quotient);
printf("Kalan %d\n", rem);
*/

#include "mpi.h"        
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAX_LEN 10000  

int find_max(int local_array[ ],int length)
{
   int i;  
   int max;
   max = local_array[0];
   for (i=1;i<length;++i)
   if (local_array[i] > max){
		max = local_array[i];
	}
   return max;
}

int main (int argc, char *argv[])
{
  int my_rank;  
  int rank;    
  int num_proc;    
  int array_len;
  int quotient;
  int rem;
  int sub_start;  
  int sub_len;
  int search_array[MAX_LEN];
  int my_max;
  int global_max;
  int local_max;
  double start_time, end_time;
  MPI_Status   status;

  MPI_Init(&argc, &argv);    
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
   
  if (my_rank == 0) {
         array_len =10000;  
         
         MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
         quotient = array_len / num_proc;
         rem = array_len % num_proc;

		if(num_proc <= 1 ){
		printf("Lutfen cekirdek sayisini arttrin.\n");
		MPI_Finalize();    
		return 0;
		}

        int i;
        for (i=0;i<array_len;++i){
        search_array[i] = rand();
}
start_time = MPI_Wtime();
        printf("Basladi.Boyut: %d \n",array_len);
        
        for (rank=1; rank < rem; ++rank){
             sub_len = quotient+1;
             sub_start = rank*quotient+rank;
             MPI_Send(&sub_len,1,MPI_INT,rank,0,MPI_COMM_WORLD);
             MPI_Send(&(search_array[sub_start]),sub_len, MPI_INT, rank, 0, MPI_COMM_WORLD);
        }
        for (rank=1; rank < num_proc; ++rank){
             sub_len = quotient;
             sub_start = rank*quotient+rem;
             MPI_Send(&sub_len,1,MPI_INT,rank,0,MPI_COMM_WORLD);
             MPI_Send(&(search_array[rank*quotient+rem]),quotient, MPI_INT, rank, 0, MPI_COMM_WORLD);
}

        if (rem==0){
         sub_len=quotient-1;
}
        else{
          sub_len=quotient+1;
}
        global_max = find_max(search_array,sub_len);
        
        for (rank=1;rank<num_proc;++rank){
             MPI_Recv(&local_max,1,MPI_INT,MPI_ANY_SOURCE,0,
                            MPI_COMM_WORLD, &status);
             if (local_max > global_max)
                  global_max = local_max;
        }
        
        end_time = MPI_Wtime();
   printf("Bitti. Süre: %f saniye\n", end_time-start_time);
        printf("En buyuk eleman %d\n", global_max);
    }
    else {  

        MPI_Recv(&sub_len,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        MPI_Recv(search_array,sub_len,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        my_max = find_max(search_array,sub_len);
   MPI_Send(&my_max,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }
           
  MPI_Finalize();      
return 0;
}
