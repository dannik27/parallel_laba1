//
// Created by danya on 29.09.2017.
//

#ifndef PARALLEL_LABA1_MATRIX_H
#define PARALLEL_LABA1_MATRIX_H


#include <string>
#include <cstdio>
#include <iostream>

using namespace std;

class Matrix {



public :

    int m,n;
    float **data;

    Matrix(int m, int n){

        if((m<1)||(n<1)){
            printf("ERROR! Uncorrect matrix size.");
            exit(1);
        }

        this->m = m;
        this->n = n;

        data = new float *[m];
        for (int i=0; i<m; i++)
            data[i]=new float [n];

    }

    Matrix(char *filename){

        if(freopen(filename,"r",stdin) == NULL){
            printf("ERROR! File not found.");
            exit(1);
        }

        try{
            //читывание размеров матрицы
            scanf("%i", &m);
            scanf("%i", &n);

            if((m<1)||(n<1)){
                throw 1;
            }

            //Инициализация двумерного массива
            data = new float *[m];
            for (int i=0; i<m; i++)
                data[i]=new float [n];

            //Заполнение матрицы
            for(int i = 0;i < m;i++){
                for(int j = 0;j < n; j++){
                    // Проверка, что матрица меньше указанных размеров
                    if(scanf("%f", &data[i][j]) == EOF){
                        throw 1;
                    }
                }
            }

            // Проверка на то, что матрица больше заявленных размеров, m - любая переменная
            if(scanf("%i", &m) != EOF){
                throw 1;
            }


        }catch(...){
            printf("ERROR! Uncorrect file format.");
            exit(1);
        }






    }

    void print(){
        for(int i = 0;i < m;i++){
            for(int j = 0;j < n; j++){
                printf("%4.2f", data[i][j]);
                printf(" ");
            }
            printf("\n");
        }
        printf("\n");
    }

    ~Matrix(){
        for (int i=0; i<m; i++)
            delete [] data[i];
        delete [] data;
    }


    Matrix* multiply(Matrix *mat) {

        if (this->n != mat->m) {
            printf("ERROR! Matrices are not convergent.");
            exit(1);
        }

        Matrix *res = new Matrix(this->m, mat->n);

        //#pragma omp parallel for
        for (int i = 0; i < res->m; i++) {
            for (int j = 0; j < res->n; j++) {

                float val = 0;
                for (int k = 0; k < this->n; k++) {
                    val += this->data[i][k] * mat->data[k][j];
                }
                res->data[i][j] = val;

            }
        }
        return res;
    }


    Matrix* parallelMultiply(Matrix *mat){

        if(this->n != mat->m){
            printf("ERROR! Matrices are not convergent.");
            exit(1);
        }

        Matrix* res = new Matrix(this->m, mat->n);

        //#pragma omp parallel for
//        #pragma omp parallel for schedule(static)

        #pragma omp parallel for schedule(dynamic, 500)
        for(int i = 0; i < res->m * res->n; i++){
            float val = 0;
            for(int k = 0; k < this->n; k++){
                val += this->data[i % res->m][k] * mat->data[k][i / res->m];
            }
            res->data[i % res->m][i / res->m] = val;
        }
        return res;
    }

    double getHash(){

        double hash = 0;

        hash += this->data[0][0];
        hash += this->data[2][0];
        hash += this->data[0][2];

//        for(int i = 0; i < this->m; i++) {
//            for (int j = 0; j < this->n; j++) {
//                hash += this->data[i][j];
//            }
//
//        }

        return hash;
    }

    bool saveToFile(char* filename){

        freopen(filename,"w",stdout);
        printf("%i %i\n", m, n);
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++) {
                printf("%f ", data[i][j]);
            }
            printf("\n");
        }
        fclose (stdout);
        freopen("CON","w",stdout);



    }



};




#endif //PARALLEL_LABA1_MATRIX_H
