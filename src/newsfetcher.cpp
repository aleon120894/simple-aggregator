#include "newsfetcher.h"
#include <iostream>
#include <thread>
#include <chrono>

std::vector<NewsItem> fetchNews(const std::string& source)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if (source == "War") {
        return {
            { "War News: Russia", "russian forces.", "https://example.com/war1", "2024-07-24" },
            { "War News: Ukraine", "Ukrainian army defends city.", "https://example.com/war2", "2024-07-24" },
            { "War News: Ceasefire", "Talks of ceasefire begin.", "https://example.com/war3", "2024-07-23" }
        };
    } else if (source == "IT News") {
        return {
            { "IT News: New CPU Released", "Intel releases new processor.", "https://example.com/it1", "2024-07-24" },
            { "IT News:  Vulnerability Found", "Security flaw discovered in popular library.", "https://example.com/it2", "2024-07-24" },
            { "IT News:  Framework Update", "React 19 is now available.", "https://example.com/it3", "2024-07-23" }
        };
    } else if (source == "Alerts") {
        return {
            { "Alert: Severe Weather", "Tornado warning issued.", "https://example.com/alert1", "2024-07-24" },
            { "Alert: Traffic Jam", "Major traffic delay on Highway 1.", "https://example.com/alert2", "2024-07-24" },
            { "Alert:  Power Outage", "Power outage in downtown area.", "https://example.com/alert3", "2024-07-23" }
        };
    } else {
        return {};
    }
}
