#ifndef NEWSITEM_H
#define NEWSITEM_H

#include <string>


struct NewsItem {
    std::string title;
    std::string source;
    std::string description;
    std::string link;
    std::string pubDate;
};

#endif // NEWSITEM_H 
