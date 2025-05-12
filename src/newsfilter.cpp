#include "newsfilter.h"
#include "utils.h"
#include <algorithm>


std::vector<NewsItem> filterNews(const std::vector<NewsItem>& news, const std::string& searchItem)
{
    
    std::vector<NewsItem> filteredNews;
    std::string searchTermLower = utils::toLower(searchItem);

    for(const auto& item : news)
    {
        
        std::string titleLower = utils::toLower(item.title);
        std::string descriptionLower = utils::toLower(item.description);

        if(titleLower.find(searchTermLower) != std::string::npos || descriptionLower.find(searchTermLower) != std::string::npos) {
            filteredNews.push_back(item);
        }
    }

    return filteredNews;
}
