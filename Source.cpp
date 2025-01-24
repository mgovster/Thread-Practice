/*
Created By: Matt Govia
SU ID: 644471631
HW03
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <fstream>

using namespace std;

mutex mtx;
condition_variable cv;
bool ready{ false };

void PartWorker(int id) {
	unique_lock<mutex> lck(mtx);
	ready = false;

	cout << endl;
	for (int i = 10; i < 20; i++) {
		cout << "Part " << i << "\n";
	}
	std::this_thread::sleep_for(chrono::microseconds(300));
	cout << endl;
	ready = true;
	cv.notify_one();
	lck.unlock();
}



void ProductWorker(int id) {
	unique_lock<mutex> lck(mtx);
	cout << endl;
	cv.wait(lck, []() { return ready; });
	for (int i = 0; i < 5; i++) {
		cout << "Prod " << i << "\n";
	}
	std::this_thread::sleep_for(chrono::microseconds(3000));
	//ready = false;
	cout << endl;

	//ready = false;
	cv.notify_all();
	lck.unlock();
}


int main() {
	const int m = 20, n = 16; //m: number of Part Workers
	//n: number of Product Workers
	//m>n
	thread partW[m];
	thread prodW[n];
	for (int i = 0; i < n; i++) {
		partW[i] = thread(PartWorker, i);
		prodW[i] = thread(ProductWorker, i);
	}
	for (int i = n; i < m; i++) {
		partW[i] = thread(PartWorker, i);
	}
	/* Join the threads to the main threads */
	for (int i = 0; i < n; i++) {
		partW[i].join();
		prodW[i].join();
	}
	for (int i = n; i < m; i++) {
		partW[i].join();
	}
	cout << "Finish!" << endl;
	return 0;
}
