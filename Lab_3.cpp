#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <Windows.h>
#include <vector>
#include <random>

HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

class Main {
	const int producers = 3;
	const int consumers = 2;

	const int producersSleep = 300;
	const int consumersSleep = 500;

	const int capacity = 200;

	bool stopProducers = false;
	bool pauseProducers = false;

	std::queue<int> queue;

	std::vector<std::thread> producersThreads;
	std::vector<std::thread> consumersThreads;

	std::mutex mutex;

public:
	Main() {

		for (int i = 0; i < producers; i++) {
			producersThreads.push_back(std::thread([&]() {produce(); }));
		}


		for (int i = 0; i < consumers; i++) {
			consumersThreads.push_back(std::thread([&]() {consume(); }));
		}

			
		while (!(GetAsyncKeyState('Q') & 0x8000)) {
			if (queue.size() >= 100) pauseProducers = true;
			if (queue.size() <= 80) pauseProducers = false;
		}

		stopProducers = true;

		for (int i = 0; i < producers; i++) {
			if(producersThreads.at(i).joinable()) producersThreads.at(i).join();
		}

		for (int i = 0; i < consumers; i++) {
			if (consumersThreads.at(i).joinable()) consumersThreads.at(i).join();
		}
		
	}
	
	~Main() {
		return;
	}

	void produce() {
		srand(GetCurrentThreadId() + time(NULL));
		while (true) {
			if (!pauseProducers) {
				int temp = rand() % 100 + 1;

				std::unique_lock<std::mutex> ul(mutex);

				SetConsoleTextAttribute(consoleColor, 15);

				queue.push(temp);

				std::cout << std::endl << "# Производитель <" << GetCurrentThreadId()
					<< "> добавил элемент = <" << temp <<
					">. Размер =  " << queue.size() << std::endl;

				ul.unlock();

				Sleep(producersSleep);
			}

			if (stopProducers) return;
		}
	}

	void consume() {
		if (queue.size() <= 0) return;
		while (true) {
			if (queue.size() <= 0) return;

				std::unique_lock<std::mutex> ul(mutex);

				SetConsoleTextAttribute(consoleColor, 4);

				if (!queue.empty())
				std::cout << std::endl << "@ Потребитель <" << GetCurrentThreadId()
					<< "> взял элемент = <" << queue.front() <<
					">. Размер = " << queue.size() - 1 << std::endl;

				if(!queue.empty()) queue.pop();

				ul.unlock();
			
			Sleep(consumersSleep);
			
		}
	}

};


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SetConsoleTextAttribute(consoleColor, 15);

	std::cout << std::endl << "Нажмите <ENTER>, чтобы запустить программу." << std::endl;
	while (!(GetAsyncKeyState(VK_RETURN) & 0x8000));

	Main main;

	SetConsoleTextAttribute(consoleColor, 15);
	std::cout << std::endl << "Нажмите <ENTER>, чтобы закончить программу." << std::endl;
	while (!(GetAsyncKeyState(VK_RETURN) & 0x8000));

	return 0;
}