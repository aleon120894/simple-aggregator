#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "newsitem.h"
#include "newsfetcher.h"
#include "newsdisplay.h"
#include "newsfilter.h"
#include "utils.h"


void getNewsFromSources(const std::vector<std::string>& sources, std::vector<NewsItem>& allNews) 
{
    std::vector<std::thread> threads;
    std::mutex newsMutex;
    std::condition_variable cv;
    std::atomic<int> completedThreads(0);
    const int totalThreads = sources.size();

    auto fetchAndAddNews = [&](const std::string& source) {
        std::vector<NewsItem> news = fetchNews(source);
        {
            std::lock_guard<std::mutex> lock(newsMutex);
            allNews.insert(allNews.end(), news.begin(), news.end());
        }
        if (++completedThreads == totalThreads) {
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

int main() {
    std::vector<NewsItem> allNews;
    std::vector<std::string> sources = {"Tech News", "World News", "Sports News"};
    int choice;
    std::string searchTerm;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    do {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                allNews.clear();
                std::cout << "Fetching news from all sources..." << std::endl;
                getNewsFromSources(sources, allNews);
                displayNews(allNews);
                break;
            case 2: {
                if (allNews.empty()) {
                    std::cout << "Please fetch the news first" << std::endl;
                    break;
                }
                std::cout << "Enter keyword to filter: ";
                std::getline(std::cin, searchTerm);
                std::cout << "main: Filtering news by keyword: \"" << searchTerm << "\"" << std::endl; // Debug
                std::vector<NewsItem> filteredNews = filterNews(allNews, searchTerm);
                std::cout << "main: filterNews returned " << filteredNews.size() << " items." << std::endl; // Debug
                displayNews(filteredNews);
                break;
            }
            case 3:
                std::cout << "Exiting News Aggregator." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 3);

    return 0;
}
