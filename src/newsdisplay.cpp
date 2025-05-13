#include "newsdisplay.h"
#include <iostream>
#include <iomanip>


void displayNewsItem(const NewsItem& item)
{

    std::cout << "Source: " << item.source << std::endl;
    std::cout << "Title: " << item.title << std::endl;
    std::cout << "Description: " << item.description << std::endl;
    std::cout << "Link: " << item.link << std::endl;
    std::cout << "Published: " << item.pubDate << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void displayNews(const std::vector<NewsItem>& news)
{
    if(news.empty()) {
        std::cout << "No news to display." << std::endl;
        return;
    }
    for(const auto& item : news) {
        displayNewsItem(item);
    }
}
