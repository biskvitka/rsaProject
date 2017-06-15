#include<thread>
#include<iostream>
#include<algorithm>

using namespace std;
class WorkerThread {

public:
    void operator()() {
	cout << "Wotker thread " << this_thread::get_id();
	cout << " is executind" << endl;
    }
};

int main() {
    vector<std::thread> threadVector;
    for (int i = 0; i < 10; i++ ) {
	threadVector.push_back(std::thread(WorkerThread()));
    }

    cout << "waiting for all the threads to finish " << endl;
    for_each(threadVector.begin(), threadVector.end(), mem_fn(&thread::join));
    cout << "exiting from main " << endl;
    return 0;
}
