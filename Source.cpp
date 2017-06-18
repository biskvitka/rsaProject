#include<cstdlib>
#include<iostream>
#include<math.h>
#include<vector>
#include<cstdlib>
#include<thread>
#include<chrono>
#include<thread>
#include<future>

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


int evaluateSmallerMatrix(int n, int** &mat) {
    long long d = 0;
	if (n == 2) {
		return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
	} else if (n > 2) {
	    for (int i = 0; i < n; i++) {
            if ( mat[i][0] == 0) {
                continue;
            }
		    int** smallerMatrix = matrixAlloc(n-1); 
            for (int row = 0; row < n; row++) {
                if ( i == row) {
                    continue;
                }

                for (int col = 1; col < n; col++) {
                    if (i < row ) {
                        smallerMatrix[row - 1][col - 1] = mat[row][col];
                    } else {
                        smallerMatrix[row][col - 1] = mat[row][col];
                    }
                }
            }
	        d = d + (pow(-1, i) * mat[i][0] * 
                evaluateSmallerMatrix(n - 1, smallerMatrix));
            matrixDealloc(n - 1, smallerMatrix);
	    }
    }
        return d;
}

int det(int n, int** &mat, int start, int end) {

            cout << "hi" << endl;
    long long d = 0;
	if (n == 2) {
	    return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
	} else if (n > 2) {
	    for (int i = start; i < end; i++) {
            if (mat[i][0] == 0) {
                continue;
            }
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
    	    d = d + (pow(-1, i) * mat[i][0] * evaluateSmallerMatrix(n - 1, smallerMatrix));
            matrixDealloc(n - 1, smallerMatrix);
		}
	}
	return d;
}



int generateAndEvaluateDeterminant(int n) {
    // Create determinant
    int** A;
    matrixInit(A, n);
    
    // Start threads execution
    int threadCount = 14;
    int difference = n / threadCount; 
    vector<future<int>> results;
    int start = 0;
    for (int i = 0;  i < threadCount; ++i, start += difference) {
        if ( i == (threadCount - 1)) {
            results.push_back(async(launch::async, det, n, ref(A), start, n));
        } else {
            results.push_back(async(launch::async, det, n, ref(A), start, start + difference));
        }
    }

    // Get threads results
    long long result = 0;
    for (int i = 0; i < threadCount; ++i) {
            cout << "HERE" << endl;
        result += results[i].get();
        
    }

    // Destroy determinant
    matrixDealloc(n, A);

    // Return result
    return result;
}

int main(int argc, char **argv)
{

    int n;
    cin >> n;
    auto start = std::chrono::high_resolution_clock::now();	
    
    cout << generateAndEvaluateDeterminant(n) << endl;

    auto finish = std::chrono::high_resolution_clock::now();	
    cout << "TIMEEEEE: " 
	    << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start)
	    .count()
        << " milliseconds" << std::endl;
    return 0;
}
