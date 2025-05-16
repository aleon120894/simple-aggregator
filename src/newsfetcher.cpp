#include "newsfetcher.h"
#include <iostream>
#include <thread>
#include <chrono>

#include <curl/curl.h>  // For fetching the RSS data
#include "pugixml.hpp" // For parsing the XML


size_t writeCallback(char* buffer, size_t size, size_t nitems, std::string* data) {
    size_t totalSize = size * nitems;
    data->append(buffer, totalSize);
    return totalSize;
}

std::vector<NewsItem> fetchNews(const std::string& source) {
    std::vector<NewsItem> newsItems;
    std::string rssData;
    std::string rssURL;

    // 1. Get RSS Feed URL
    if (source == "Tech News") { // Corrected source name
        rssURL = "https://www.bbc.com/news/world/rss.xml";
    } else if (source == "World News") {  // Corrected source name
        rssURL = "https://www.wired.com/feed/rss";
    } else if (source == "Sports News") {  // Corrected source name
        rssURL = "https://www.cbsnews.com/latest/rss/main";
    } else {
        std::cout << "fetchNews: Unknown source: " << source << std::endl;
        return {};
    }
    std::cout << "fetchNews: Fetching from URL: " << rssURL << std::endl;

    // 2. Fetch the XML data using libcurl, handling redirects
    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, rssURL.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rssData);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            return {};
        }
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "curl_easy_init() failed" << std::endl;
        return {};
    }
    std::cout << "fetchNews: Data received from curl, size: " << rssData.size() << " bytes" << std::endl;

    // 3. Parse the XML data using pugixml
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(rssData.c_str());
    if (!result) {
        std::cerr << "XML parse error: " << result.description() << std::endl;
        std::cout << "XML Content causing error:\n" << rssData << std::endl;
        return {};
    }
    std::cout << "fetchNews: XML parsed successfully" << std::endl;

    // 4. Extract the news items from the XML structure
    for (pugi::xpath_node xpath_item : doc.select_nodes("//item")) {
        pugi::xml_node item = xpath_item.node();
        NewsItem newsItem;
        newsItem.title = item.child_value("title");
        newsItem.description = item.child_value("description");
        newsItem.link = item.child_value("link");
        newsItem.pubDate = item.child_value("pubDate");
        newsItems.push_back(newsItem);
        std::cout << "fetchNews: Extracted title: " << newsItem.title << std::endl;
    }
    std::cout << "fetchNews: Number of news items found: " << newsItems.size() << std::endl;
    return newsItems;
}
