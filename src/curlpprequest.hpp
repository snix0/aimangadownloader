#ifndef CURLREQUEST_HPP
#define CURLREQUEST_HPP

#include <string>
#include <vector>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include "curlpp/cURLpp.hpp"
#include "curlpp/Easy.hpp"
#include "curlpp/Options.hpp"
#include <curl/curl.h>
#include <glibmm.h>
#include <QString>
#include <QUrl>
#include "configuration.hpp"
#include "MangaObject.hpp"

class CurlRequest {
    public:
        CurlRequest();
        ~CurlRequest();
        std::vector<QString> requestList();
        //std::vector<std::string> requestNew(Configuration conf);
        QUrl getImageLink(QString url);
        QVector<QString> getChapters(QString url);
        xmlpp::NodeSet getChapterImages(QString url);
        void getImage(QUrl url);
        void getAllImages(xmlpp::NodeSet links);
        //std::string getDescription(MangaObject mo);
        //std::vector<std::string> getTags(MangaObject mo);
        //std::string getDateModified(MangaObject mo);
        static size_t FileCallback(FILE* f, const void* ptr, size_t size, size_t nmemb);
};

#endif
