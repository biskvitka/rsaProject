#include<cstdlib>
#include<ctime>
#include<iostream>
#include<math.h>
#include<vector>
#include<cstdlib>
//#include<thread>

const int numThreads = 2;

using namespace std;


void matrixInit (int** &matrix, int size) {
    matrix = new int*[size];
	srand((unsigned)time(0));
    for (int i = 0; i <size; i++ ) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
           matrix[i][j] = rand()%10;
           cout << matrix[i][j]<< " ";
        }
        cout << endl;
    }
}

void coutMatrix(int** &matrix, int n) {
    for (int i = 0; i < n; i++ ) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int** matrixAlloc (int size){
    int** matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }
    return matrix;
}

void matrixDealloc (int size, int** &matrix) {
    for (int i = 0; i < size; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

int det(int n, int** &mat) {

    long long d = 0;
	if (n == 2) {
		return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
	} else if (n > 2) {
		for (int i = 0; i < n; i++)
		{
		    int** smallerMatrix = matrixAlloc(n-1); 
            for (int row = 0; row < n; row++) {
                if ( i == row) {
                    continue;
                }
                for (int col = 1; col < n; col++) {
                    if(i < row ) {
                        smallerMatrix[row - 1][col - 1] = mat[row][col];
                    } else {
                        smallerMatrix[row][col - 1] = mat[row][col];
                    }
                }
            }
			d = d + (pow(-1, i) * mat[i][0] * det(n - 1, smallerMatrix));
            matrixDealloc(n - 1, smallerMatrix);
		}
	}
	return d;
}

int generateAndEvaluateDeterminant(int n) {
	int** A;
    matrixInit(A, n);
	int d = det(n, A);
    matrixDealloc(n, A);
	return d;

}

int main(int argc, char **argv)
{
	int n;
	cin >> n;
	cout << generateAndEvaluateDeterminant(n);
	int pkp;
	cin >> pkp;
	return 0;
}
