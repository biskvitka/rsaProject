#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<math.h>
#include<vector>
#include<cstdlib>
#include<windows.h>

const int numThreads = 2;

using namespace std;
long long d = 0;
int det(int n, std::vector<std::vector<int>>& mat)
{

	if (n == 2) {
		return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
	} else {
		std::vector<std::vector<int>> submat(n, std::vector<int>(n));
		for (int c = 0; c < n; c++)
		{
			int subi = 0; //submatrix's i value
			for (int i = 1; i < n; i++)
			{
				int subj = 0;
				for (int j = 0; j < n; j++)
				{
					if (j == c)
						continue;
					submat[subi][subj] = mat[i][j];
					subj++;
				}
				subi++;

			}
			d = d + (pow(-1, c) * mat[0][c] * det(n - 1, submat));
		}
	}
	return d;
}

int generateAndEvaluateDeterminant(int n) {
	std::vector<std::vector<int>> A(n, std::vector<int>(n));
	srand((unsigned)time(0));
	for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
			A[i][j] = rand()%100;
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	int d = det(n, A);
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