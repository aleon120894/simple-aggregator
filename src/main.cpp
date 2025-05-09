#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>


int main()
{

    // std::vector<News Item> allNews;
    std::vector<std::string> sources = {"War", "IT News", "Alerts"};
    int choice;
    std::string searchItem;

    do {

        std::cin >> choice;
    } while(choice != 3);

    return 0;
}
