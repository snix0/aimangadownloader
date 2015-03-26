#ifndef MANGAOBJECT_HPP
#define MANGAOBJECT_HPP

#include <string>
#include <vector>

struct MangaObject {
    std::string title;
    std::string description;
    std::string date_modified;
    std::vector<std::string> tags;
};

#endif
