#ifndef NEWSFETCHER_H
#define NEWSFETCHER_H

#include <vector>
#include <string>
#include "newsitem.h"

std::vector<NewsItem> fetchNews(const std::string& source);

#endif // NEWSFETCHER_H
