#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;
using namespace placeholders;

class Application {
    mutex m;
    condition_variable condVar;
    bool dataLoaded;

public:
    Application(): dataLoaded(false) {
    }

    void loadData () {
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Loading data from the XML" << endl;
        lock_guard<mutex> lock(m);
        dataLoaded = true;
        condVar.notify_one();
    }

    bool isDataLoaded () {
        return dataLoaded;
    }
    
    void mainTask() {
        cout << "Do some handshaking" << endl;
        
        unique_lock<mutex> mLock(m);
        condVar.wait(mLock, bind(&Application::isDataLoaded, this));
        cout << "Do processing on the loaded data" << endl;
    }
};

int main(void) {
    Application app;
    thread thread1(&Application::mainTask, &app);
    thread thread2(&Application::loadData, &app);
    
    thread1.join();
    thread2.join();
    return 0;
}
