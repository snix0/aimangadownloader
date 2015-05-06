#include <vector>
#include <string>
#include <iostream> //TODO: FOR DEBUGGING PURPOSES ONLY
#include <sstream>

#include <libxml/tree.h>
#include <libxml/HTMLparser.h>
#include <libxml++/libxml++.h>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Types.hpp>
#include <curlpp/Options.hpp>
#include <curl/curl.h>

#include <glib.h>

#include "curlpprequest.hpp"
#include <QString>
#include <QTextStream>
#include <QUrl>

using namespace curlpp::options;

#define HEADER_ACCEPT "Accept:text/html,application/xhtml+xml,application/xml"
#define HEADER_USER_AGENT "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.17 (KHTML, like Gecko) Chrome/24.0.1312.70 Safari/537.17"
//#define HEADER_MOBILE_USER_AGENT "Mozilla/5.0 (Linux; <Android Version>; <Build Tag etc.>) AppleWebKit/<WebKit Rev> (KHTML, like Gecko) Chrome/<Chrome Rev> Mobile Safari/<WebKit Rev>"

CurlRequest::CurlRequest() {
    curlpp::Cleanup myCleanup;
    curlpp::Easy myRequest;
}

CurlRequest::~CurlRequest() {
}

size_t CurlRequest::FileCallback(FILE* f, const void* ptr, size_t size, size_t nmemb) { 
    return std::fwrite(ptr, size, nmemb, f); 
}

std::vector<QString> CurlRequest::requestList() {
    FILE* out = fopen("mangalist", "w");
    QTextStream text_stream(out);
    std::vector<QString> result;
    std::ostringstream os;
    curlpp::Cleanup myCleanup;
    curlpp::Easy myRequest;
    std::list<std::string> headers;

    headers.push_back(HEADER_ACCEPT);
    headers.push_back(HEADER_USER_AGENT);
    myRequest.setOpt(new curlpp::options::HttpHeader(headers));
    myRequest.setOpt(new curlpp::options::FollowLocation(true));

    if (out) {
        for (int i = 0; i != 12000; i+=1000) {
        myRequest.setOpt<Url>("https://bato.to/comic/_/comics/?per_page=1000&st="+std::to_string(i));
        os << myRequest;
        std::string response = os.str();

        xmlDoc* doc = htmlReadDoc((xmlChar*)response.c_str(), NULL, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
        xmlNode* node = xmlDocGetRootElement(doc);
        xmlpp::Element* root = new xmlpp::Element(node);

        std::string path_to_title = "//*/tr[@class=\"__topic \"]//a/text()";
        auto titles = root->find(path_to_title);

        std::string path_to_url = "//*/tr[@class=\"__topic \"]//a/@href";
        auto urls = root->find(path_to_url);

        std::cout << "LOADING MANGA LIST..." << (i/(double)12750)*100 << "%" << std::endl; //TODO: static cast?
        if (!path_to_title.empty())
            for (int j = 0; j != 1000; ++j) {
            //std::cout << "title is " << dynamic_cast<xmlpp::ContentNode*>(elements[i])->get_content() << std::endl;
            QString manga_title = QString::fromUtf8(dynamic_cast<xmlpp::ContentNode*>(titles[j])->get_content().c_str());
            QString manga_link = QString::fromUtf8(dynamic_cast<xmlpp::Attribute*>(urls[j])->get_value().c_str());
            result.push_back(manga_title+"|"+manga_link);
            text_stream << manga_title+"|"+manga_link << "\n";
            }
        else
            std::cout << "NOTHING FOUND" << std::endl;

        //cleanup
        os.str("");
        delete root;
        xmlFreeDoc(doc);
        }
        std::cout << "COMPLETED" << std::endl;
    }
    std::cout << "FINISHED" << std::endl;
    return result;
}

QUrl CurlRequest::getImageLink(QString url) {
    curlpp::Cleanup myCleanup;
    curlpp::Easy myRequest;
    std::ostringstream os;
    std::list<std::string> headers;

    headers.push_back(HEADER_ACCEPT);
    headers.push_back(HEADER_USER_AGENT);
    myRequest.setOpt(new curlpp::options::HttpHeader(headers));
    myRequest.setOpt(new curlpp::options::FollowLocation(true));

    myRequest.setOpt<Url>(url.toUtf8().constData());
    os << myRequest;
    std::string response = os.str();

    xmlDoc* doc = htmlReadDoc((xmlChar*)response.c_str(), NULL, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    xmlNode* node = xmlDocGetRootElement(doc);
    xmlpp::Element* root = new xmlpp::Element(node);

    std::string path_to_image = "//div[@class=\"ipsBox\"]/div/div/img/@src";
    auto image = root->find(path_to_image);
    std::cout << dynamic_cast<xmlpp::Attribute*>(image[0])->get_value() << std::endl;
    return QString::fromUtf8(dynamic_cast<xmlpp::Attribute*>(image[0])->get_value().c_str());
}

QString CurlRequest::getChapters(QString url) {
    curlpp::Cleanup myCleanup;
    curlpp::Easy myRequest;
    std::ostringstream os;
    std::list<std::string> headers;

    headers.push_back(HEADER_ACCEPT);
    headers.push_back(HEADER_USER_AGENT);
    myRequest.setOpt(new curlpp::options::HttpHeader(headers));
    myRequest.setOpt(new curlpp::options::FollowLocation(true));

    myRequest.setOpt<Url>(url.toUtf8().constData());
    os << myRequest;
    std::string response = os.str();

    xmlDoc* doc = htmlReadDoc((xmlChar*)response.c_str(), NULL, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    xmlNode* node = xmlDocGetRootElement(doc);
    xmlpp::Element* root = new xmlpp::Element(node);

    std::string path_to_chapter = ".//div/table[@class=\"ipb_table chapters_list\"]/tbody/tr[@class=\"row lang_English chapter_row\"]/td/a/@href";
    auto chapter_link = root->find(path_to_chapter);
    for (auto i = 0; i != chapter_link.size(); ++i) {
        std::cout << dynamic_cast<xmlpp::Attribute*>(chapter_link[i])->get_value() << std::endl;
    }
    return QString::fromUtf8(dynamic_cast<xmlpp::Attribute*>(chapter_link[0])->get_value().c_str());
}

xmlpp::NodeSet CurlRequest::getChapterImages(QString url) {
    curlpp::Cleanup myCleanup;
    curlpp::Easy myRequest;
    std::ostringstream os;
    std::list<std::string> headers;

    headers.push_back(HEADER_ACCEPT);
    headers.push_back(HEADER_USER_AGENT);
    myRequest.setOpt(new curlpp::options::HttpHeader(headers));
    myRequest.setOpt(new curlpp::options::FollowLocation(true));

    myRequest.setOpt<Url>(url.toUtf8().constData());
    os << myRequest;
    std::string response = os.str();

    xmlDoc* doc = htmlReadDoc((xmlChar*)response.c_str(), NULL, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    xmlNode* node = xmlDocGetRootElement(doc);
    xmlpp::Element* root = new xmlpp::Element(node);

    std::string path_to_chapter_page = "//img[@id=\"comic_page\"]/@src";
    return root->find(path_to_chapter_page);
}

void CurlRequest::getImage(QUrl url) {

    curlpp::Cleanup myCleanup;
    curlpp::Easy myRequest;
    std::cout << url.fileName().toStdString() << std::endl;
    FILE* file = std::fopen(url.fileName().toStdString().c_str(), "w");
    if (file) {
        curlpp::types::WriteFunctionFunctor functor(utilspp::BindFirst(utilspp::make_functor(&FileCallback), file));
        curlpp::options::WriteFunction *getFileOpt = new curlpp::options::WriteFunction(functor);
        myRequest.setOpt(getFileOpt);

        myRequest.setOpt<Url>(QString(url.toEncoded()).toStdString());
        myRequest.perform();
    }
}

void CurlRequest::getAllImages(xmlpp::NodeSet links) {
    for (int i = 0; i != links.size(); ++i) {
        getImage(QString::fromUtf8(dynamic_cast<xmlpp::Attribute*>(links[i])->get_value().c_str()));
    }
}

//
//std::string CurlRequest::getDescription(MangaObject mo) {
//
//}
//
//std::vector<std::string> CurlRequest::getTags(MangaObject mo) {
//    
//}
//
//std::string CurlRequest::getDateModified(MangaObject mo) {
//
//}


