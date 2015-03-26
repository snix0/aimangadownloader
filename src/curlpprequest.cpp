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


//
//std::vector<std::string> CurlRequest::requestNew(Configuration conf) { //todo replace with MangaList
//
//}
//
////std::string CurlRequest::getImage(MangaObject mo) {
//
//    FILE* file = std::fopen("temporary.txt", "w");
//    if (file) {
//        curlpp::types::WriteFunctionFunctor functor(utilspp::BindFirst(utilspp::make_functor(&FileCallback), file));
//        curlpp::options::WriteFunction *getFileOpt = new curlpp::options::WriteFunction(functor);
//        myRequest.setOpt(getFileOpt);
//
//        //myRequest.setOpt<Url>("http://bato.to/forums/public/style_images/11_4_logo.png")
//        //myRequest.setOpt<Url>("http://img.bato.to/comics/2014/07/24/g/read53d196e7c8b68/img000002.png");
//        //myRequest.setOpt<Url>("https://bato.to/comic/_/comics/?per_page=30&st=60");
//        //myRequest.perform();
//    }
////}
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


