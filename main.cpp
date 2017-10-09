#include <iostream>
#include <ctime>
#include "Matrix.h"


using namespace std;

Matrix* createRandomMatrix(int m, int n);
float randomFloat(float a, float b);

int main() {

   // Matrix *m1 = new Matrix("in_out/input1.txt");
  //  Matrix *m2 = new Matrix("in_out/input2.txt");

  //  Matrix *m3 = m1->multiply(m2);
//    Matrix *m4 = m1->parallelMultiply(m2);

//    m3->saveToFile("in_out/output.txt");

//    m1->print();
//    m2->print();
  //  m3->print();

    Matrix* m5 = createRandomMatrix(460, 760);
    Matrix* m6 = createRandomMatrix(760, 920);

    int start = clock();

    Matrix* m7 = m5->parallelMultiply(m6);

    float stop1 = (clock() - start)/1000.0;
    cout << "runtime = " << stop1 << endl;

    m7->saveToFile("in_out/output.txt");

}

Matrix* createRandomMatrix(int m, int n){

    Matrix *result = new Matrix(m, n);

    for(int i = 0;i < m;i++){
        for(int j = 0;j < n; j++){
            result->data[i][j] = randomFloat(-10, 10);
        }
    }
    return result;
}

float randomFloat(float a, float b) {
    return a + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(b-a)));
}



