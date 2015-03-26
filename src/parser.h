#ifndef PARSER_H
#define PARSER_H

class Parser {
    Parser();
    ~Parser();
    getCurrentSource(Configuration conf);
    getMangaList(CurlRequest cr);
};

#endif
