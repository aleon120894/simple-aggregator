#ifndef NEWSDISPLAY_H
#define NEWSDISPLAY_H

#include <vector>
#include "newsitem.h"

void displayNewsItem(const NewsItem& item);
void displayNews(const std::vector<NewsItem>& item);

#endif // NEWSDISPLAY_H
