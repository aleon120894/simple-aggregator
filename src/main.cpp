#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "newsitem.h"
#include "newsfetcher.h"
#include "newsfilter.h"
#include "utils.h"


void getNewsFromSources(const std::vector<std::string>& sources, std::vector<NewsItem>& allNews)
{
    std::vector<std::thread> threads;
    std::mutex newsMutex;
    std::condition_variable cv;
    std::atomic<int> completedThreads(0);
    const int totalThreads = sources.size();

    auto fetchAndAddNews = [&] (const std::string& source) {
        std::vector<NewsItem> news = fetchNews(source);
        {
            std::lock_guard<std::mutex> lock(newsMutex);
            allNews.insert(allNews.end(), news.begin(), news.end());
        }

        if(++completedThreads == totalThreads) {
            cv.notify_one();
        }
    };

    for (const auto& source : sources) {
        threads.emplace_back(fetchAndAddNews, source);
    }

    {
        std::unique_lock<std::mutex> lock(newsMutex);
        cv.wait(lock, [&]{ return completedThreads == totalThreads; });
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

void displayMenu() {
    std::cout << "\nNews Aggregator Menu" << std::endl;
    std::cout << "1. Get All News" << std::endl;
    std::cout << "2. Filter News by Keyword" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}


int main()
{

    std::vector<NewsItem> allNews;
    std::vector<std::string> sources = {"War", "IT News", "Alerts"};
    int choice;
    std::string searchItem;

    do {
        displayMenu();
        std::cin >> choice;
    } while(choice != 3);

    return 0;
}
