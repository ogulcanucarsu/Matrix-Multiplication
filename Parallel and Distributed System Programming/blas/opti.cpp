#include<stdio.h>
#include<stdlib.h>
#include<lapacke.h>
#include<cblas.h>

void matrisyaz(char baslik[], double *matris, int boyut)    {
    int i, j;

    printf("%s = [\n", baslik);
    for(i = 0; i < boyut; i++)   {
        for(j = 0; j < boyut; j++)   {
            printf("%f  ", matris[i * boyut + j]);
        }
        if(i == (boyut-1))   printf("  ]\n\n");
        else                 printf(";\n");
    }

}


int main(int argc, char* argv[])        {
    double *matrisA, *matrisB, *matrisC;
    int boyut = 3;
    int i, j;
    lapack_int lapack_boyut;
    int *ipiv;

    if(argc > 1)   {
        boyut = atoi(argv[1]);
    }

    lapack_boyut = boyut;
    srand (time(NULL));    // initialize random seed
    matrisA = (double *)malloc(boyut * boyut * sizeof(double));
    matrisB = (double *)malloc(boyut * boyut * sizeof(double));
    matrisC = (double *)malloc(boyut * boyut * sizeof(double));
    ipiv = (int *)malloc(boyut * sizeof(int));

    for(i = 0; i < boyut; i++)  {
        for(j = 0; j < boyut; j++)  {
            // rastgele A matrisi uret ve Bye kopyala.
            matrisB[i * boyut + j] = matrisA[i * boyut + j] = (double)(rand() % 9);
            // matrisC[i * boyut + j] = 0;
        }
    }

    matrisyaz("A matrisi", matrisA, boyut);
    LAPACKE_dgetrf(LAPACK_ROW_MAJOR, lapack_boyut, lapack_boyut, matrisA,
                   lapack_boyut, ipiv );

//lapack_int LAPACKE_dgetrf( int matrix_layout, lapack_int m, lapack_int n,
//                           double* a, lapack_int lda, lapack_int* ipiv );

    matrisyaz("LU sonrasi matrisA", matrisA, boyut);
    LAPACKE_dgetri(LAPACK_ROW_MAJOR, lapack_boyut, matrisA, lapack_boyut, ipiv);

//lapack_int LAPACKE_dgetri( int matrix_layout, lapack_int n, double* a,
//                           lapack_int lda, const lapack_int* ipiv );

    matrisyaz("matrisA'nin tersi", matrisA, boyut);
    cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans, lapack_boyut,
                 lapack_boyut, lapack_boyut, 1.0, matrisA, lapack_boyut,
                 matrisB, lapack_boyut, 0.0, matrisC, lapack_boyut);

//void cblas_dgemm(CBLAS_LAYOUT layout, CBLAS_TRANSPOSE TransA,
//                 CBLAS_TRANSPOSE TransB, const int M, const int N,
//                 const int K, const double alpha, const double *A,
//                 const int lda, const double *B, const int ldb,
//                 const double beta, double *C, const int ldc);

    matrisyaz("carpim", matrisC, boyut);

    free(matrisA);
    free(matrisB);
    free(matrisC);
    free(ipiv);

    return 0;
}
