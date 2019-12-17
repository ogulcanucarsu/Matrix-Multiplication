#pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline") //Optimization flags
#pragma GCC option("arch=native", "tune=native", "no-zero-upper") //Enable AVX
#pragma GCC target("avx")  //Enable AVX

#include <time.h>    // for clock_t, clock(), CLOCKS_PER_SEC
#include <sys/time.h>
#include <stdio.h> //AVX/SSE Extensions are included in stdio.h
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define DIM 3000

void single_multiply(int rowStart, int rowEnd);
void *thread_multiply(void *offset);
void fill_matrix();

int matrix[DIM][DIM];
int result_matrix[DIM][DIM];

int *matrix_ptr = (int *) &matrix;
int *result_ptr = (int *) &result_matrix;
int cores = 1; //Default
int detect_number_of_cores();

int main() {

    //two instructions needed for pseudo-random float numbers
    srand((unsigned int) time(NULL));

    cores = detect_number_of_cores();
    fill_matrix();

    printf("\n Core sayýsý %i ", cores);

    //time detection struct declaration
    struct timeval start, end;
    gettimeofday(&start, NULL);

    if (cores == 0 || cores == 1) {
        //passing 0 because it has to start from the first row
        single_multiply(0, DIM);

        gettimeofday(&end, NULL);

        long seconds = (end.tv_sec - start.tv_sec);
        long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

        printf("\n\n Time elapsed is %ld seconds and %ld micros\n", seconds, micros);
        return 0;

    } else {
        int rows_por_thread = DIM / cores;
        printf("\n Rows por Thread: %i", rows_por_thread);
        int rest = DIM % cores;
        printf("\n Rest: %i \n", rest);
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
                if (error != 0) {
                    printf("\n Error in thread %i creation", c);
                }
                printf("created thread n %i with argument: %i \n", c, thread_args[c]);
            }
            printf("\n ... working ...");
            for (int c = 0; c < cores; c++) {
                error = pthread_join(threads[c], NULL);
                if (error != 0) {
                    printf("\n Error in thread %i join", c);
                }
                printf("\n Waiting to join thread n: %i", c);
            }

        } else {

            //THE PROBLEM MUST BE INSIDE THIS ELSE STATEMENT

            //execute the multi-thread function n times and the single function th rest remaining times
            printf("\n The number of cores is NOT a divisor of the size of the matrix. \n");

            //create an array of thread-like objects
            pthread_t threads[cores];
            //create an array with the arguments for each thread
            int thread_args[cores];

            //launching the threads according to the available cores
            int i = 0;  //counter for the thread ID
            int entrypoint_residual_rows = 0;   //first unprocessed residual row

            //launching the threads according to the available coreS
            for (int c = 0; c < DIM - rest; c += rows_por_thread) {
                thread_args[i] = c;
                i++;
            }

            entrypoint_residual_rows = cores * rows_por_thread;
            int error;
            //launch the threads
            for (int c = 0; c < cores; c++) {
                error = pthread_create(&threads[c], NULL, thread_multiply, (void *) &thread_args[c]);
                if (error != 0) {
                    printf("\n Error in thread %i creation, exiting...", c);
                }
                printf("created thread n %i with argument: %i \n", c, thread_args[c]);
            }

            printf("\n ... working ...\n");
            //join all the previous generated threads
            for (int c = 0; c < cores; c++) {
                pthread_join(threads[c], NULL);
                printf("\n Waiting to join thread n: %i", c);
            }
            printf("\n entry-point index for the single function %i ", entrypoint_residual_rows);
            single_multiply(entrypoint_residual_rows, DIM);
        }
    }

    gettimeofday(&end, NULL);

    printf("\n All threads joined correctly");

    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    printf("\n\n Time elapsed is %d seconds and %d micros\n", seconds, micros);


    return 0;
}

//detect number of cores of the CPU (logical cores)
int detect_number_of_cores() {
    return (int) 4;
}

//matrix filling function
void fill_matrix() {
    for (int c = 0; c < DIM; c++)
        for (int d = 0; d < DIM; d++) {
            matrix[c][d] = rand()%21+10;
            
    }
}

//row by row multiplication algorithm (mono-thread version)
void single_multiply(int rowStart, int rowEnd) {
    for (int i = rowStart; i < rowEnd; i++) {
        for (int j = 0; j < DIM; j++) {
            *(result_ptr + i * DIM + j) = 0;
            for (int k = 0; k < DIM; k++) {
                *(result_ptr + i * DIM + j) += *(matrix_ptr + i * DIM + k) * *(matrix_ptr + k * DIM + j);
            }
        }
    }
}
void *thread_multiply(void *offset) {
    int *row_offset = (int *) offset;
    printf(" Starting at line %i ending at line %i \n ", *row_offset, *row_offset + (DIM / cores));
    single_multiply(*row_offset, *row_offset + (DIM / cores));
    printf("\n ended at line %i", *row_offset + (DIM / cores));
    return NULL;
}
