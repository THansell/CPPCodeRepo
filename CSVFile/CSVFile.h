#ifndef CSVFILE_H
#define CSVFILE_H

#include <istream>
#include <string>
#include <vector>


class CSVFile {
  private:
    std::vector<std::vector<std::string>> table;
  public:
    CSVFile();
    CSVFile(std::string);
    CSVFile(std::istream &csvFile );
    bool empty();
    void read(std::string);
    void read(std::istream &csvFile );
    unsigned int lineCount();
    unsigned int dataCount();
    unsigned int headerColumnCount();
    unsigned int dataColumnCount( unsigned int );
    std::string headerValue( unsigned int );
    std::string dataValue( unsigned int, unsigned int );
    std::vector<std::string> headers();
    std::string headersAsString() ;
    std::vector<std::vector<std::string>> all();
    std::vector<std::vector<std::string>> data();
};
#endif
