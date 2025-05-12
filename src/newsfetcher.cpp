#include "newsfetcher.h"
#include <iostream>
#include <thread>
#include <chrono>

std::vector<NewsItem> fetchNews(const std::string& source)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if(source == "War") {
        return {
            {"War News: "},
            {" "},
            {" "}
        };
    }else if(source == "IT News"){
        return {
            {"IT News: "},
            {" "},
            {" "}
        };
    }else if(source == "Alers"){
        return {
            {"Alerts:"},
            {" "},
            {" "}
        };
    } else {
        return {};
    }
}
