#ifndef NEWSFILTER_H
#define NEWSFILTER_H

#include <vector>
#include <string>
#include "newsitem.h"

std::vector<NewsItem> filterNews(const std::vector<NewsItem>& news, const std::string& searchTerm);

#endif // NEWSFILTER_H