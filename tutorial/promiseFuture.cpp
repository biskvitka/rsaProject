#include <iostream>
#include <thread>
#include <future>

using namespace std;

void initializer(promise<int> * promObj) {
    cout << "Inside thread" << endl;
    promObj->set_value(32);
}

int main(void) {
    promise<int> promiseObj;
    future<int> futureObj = promiseObj.get_future();
    thread th(initializer, &promiseObj);
    cout << futureObj.get() << endl;
    th.join();


    return 0;
}
