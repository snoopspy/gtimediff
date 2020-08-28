#include <chrono>
#include <thread>
#include "../gtimediff.h"

using namespace std;

void doSomething(int msec) {
	this_thread::sleep_for(chrono::milliseconds(msec));
}

int main() {
	GTimeDiff td;
	for (int i = 0; i < 10; i++) {
		td.check(1111);
		doSomething(10);
		td.check(2222);
		doSomething(20);
		td.check(3333);
		doSomething(30);
		td.check(4444);
		doSomething(40);
	}
	td.report();
}
