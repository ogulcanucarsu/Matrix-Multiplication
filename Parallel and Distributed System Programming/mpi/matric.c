#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define SIZE 2000

MPI_Status status;

static int first_matrix[SIZE][SIZE],second_matrix[SIZE][SIZE],multiply_matrix[SIZE][SIZE];

int main(int argc, char **argv)
{
  int number_core,core_id,number_workers;
  int source,destination,satir,offset;
  int i,j,k;
  double start_time, end_time;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &core_id);
  MPI_Comm_size(MPI_COMM_WORLD, &number_core);

  if(number_core > 1){
number_workers = number_core-1;

 if (core_id == 0) {

   for (i=0; i<SIZE; i++) {
     for (j=0; j<SIZE; j++) {
first_matrix[i][j]= rand()%21+10;
     }
   }
   for (i=0; i<SIZE; i++) {
     for (j=0; j<SIZE; j++) {
second_matrix[i][j]= rand()%21+10;
     }
   }
   satir = SIZE/number_workers;
   offset = 0;
   start_time = MPI_Wtime();
   printf("Basladi. Core sayisi: %d ,  Boyut: %d \n",number_core,SIZE);
   for (destination=1; destination<=number_workers; destination++)
   {
     MPI_Send(&offset, 1, MPI_INT, destination, 1, MPI_COMM_WORLD);
     MPI_Send(&satir, 1, MPI_INT, destination, 1, MPI_COMM_WORLD);
     MPI_Send(&first_matrix[offset][0], satir*SIZE, MPI_INT,destination,1, MPI_COMM_WORLD);
     MPI_Send(&second_matrix, SIZE*SIZE, MPI_INT, destination, 1, MPI_COMM_WORLD);
     offset = offset + satir;
   }
   for (i=1; i<=number_workers; i++)
   {
     source = i;
     MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
     MPI_Recv(&satir, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
     MPI_Recv(&multiply_matrix[offset][0], satir*SIZE, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
   }
 
   end_time = MPI_Wtime();
   printf("Bitti. Süre: %f saniye\n", end_time-start_time);
 }
 if (core_id > 0) {
   source = 0;
   MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
   MPI_Recv(&satir, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
   MPI_Recv(&first_matrix, satir*SIZE, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
   MPI_Recv(&second_matrix, SIZE*SIZE, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
   for (i=0; i<SIZE; i++){
     for (j=0; j<SIZE; j++){
for (k=0; k<SIZE; k++){
 multiply_matrix[i][j] += first_matrix[i][k] * second_matrix[k][j];
}
     }
   }
   MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
   MPI_Send(&satir, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
   MPI_Send(&multiply_matrix, satir*SIZE, MPI_INT, 0, 2, MPI_COMM_WORLD);
 }
  } else {
   printf ("Lutfen cekirdek sayisini arttýriniz.\n");
  }
  MPI_Finalize();
}
