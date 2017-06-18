#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <future>

using namespace std;
using namespace chrono;

string fetchDataFromDB (string recvData) {
    this_thread::sleep_for(seconds(5));
    return "DB_" + recvData;
}

string fetchDataFromFile(string recvData) {
    this_thread::sleep_for(seconds(5));
    return "File_" + recvData;
}

int main (void) {
    system_clock::time_point start = system_clock::now();
    
    future<string> resultFromDB = async(launch::async, fetchDataFromDB, "Data");

    string fileData = fetchDataFromFile("Data");

    string dbData = resultFromDB.get();

    auto end = system_clock::now();

    auto diff = duration_cast<std::chrono::milliseconds> (end - start).count();
    cout << "Total time taken = " << diff << " Seconds" << endl;
    string data = dbData  + "::" + fileData;

    cout << "Data " << data << endl;


    return 0;
}
