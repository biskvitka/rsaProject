#include <iostream>
#include <thread>

using namespace std;
void threadFunc (int a, int b) {
	cout << "The result is : " << a + b << endl;
}


int main (void) {
	int a = 5, b = 23;	
	thread thr(threadFunc, a, b);
	thr.join();
	
	return 0;
}
