#include <iostream>
#include <thread>
#include <vector>

using namespace std;

class Wallet {
	int mMoney;
public:
	Wallet():mMoney(0) {
	}
	~Wallet(){}
	int getMoney() {
		return mMoney;
	}
	void addMoney(int amount) {
		for (int i = 0; i < amount; ++i ) {
			mMoney++;
		}
	}

};

int testMultithreadWallet () {
	Wallet wallet;
	vector<thread> threads;
	for (int i  = 0; i < 5; ++i) {
		threads.push_back(thread(&Wallet::addMoney, &wallet, 1000));
	}
	
	for (int i = 0; i < threads.size(); ++i) {
		threads.at(i).join();
	}
	return wallet.getMoney(); 	

}
int main(void) {
	int val = 0;
	for (int k = 0; k < 1000; ++k) {
		if ((val = testMultithreadWallet()) != 5000 ) {
			cout << "ERROR : " << val << endl;
		}
	}

	return 0;
}
