#include <iostream>

int MAX_N = 100;

bool test() {
	for (int i = 0; i < MAX_N; i++) {

	}
	return true;
}

int main() {
	for (int testId = 0; testId < MAX_N; testId++){ 
		if (!test()) {
			std::cout << "fail" << std::endl;
			return 1;
		} else {
			if (testId % 10 == 0) {
				std::cout << (testId++) << std::endl;
			}
		}
	}
}
