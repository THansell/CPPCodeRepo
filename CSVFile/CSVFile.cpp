#include <istream>
#include <fstream>
#include <string>
#include <vector>

enum class CSVState {
    UnquotedField,
    QuotedField,
    QuotedQuote
};

std::vector<std::string> readCSVRow(const std::string &row) {
    CSVState state = CSVState::UnquotedField;
    std::vector<std::string> fields {""};
    size_t i = 0; // index of the current field
    for (char c : row) {
        switch (state) {
            case CSVState::UnquotedField:
                switch (c) {
                    case ',': // end of field
                              fields.push_back(""); i++;
                              break;
                    case '"': state = CSVState::QuotedField;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedField:
                switch (c) {
                    case '"': state = CSVState::QuotedQuote;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedQuote:
                switch (c) {
                    case ',': // , after closing quote
                              fields.push_back(""); i++;
                              state = CSVState::UnquotedField;
                              break;
                    case '"': // "" -> "
                              fields[i].push_back('"');
                              state = CSVState::QuotedField;
                              break;
                    default:  // end of quote
                              state = CSVState::UnquotedField;
                              break; }
                break;
        }
    }
    return fields;
}

/// Read CSV file, Excel dialect. Accept "quoted fields ""with quotes"""
std::vector<std::vector<std::string>> readCSV(std::istream &in) {
    std::vector<std::vector<std::string>> table;
    std::string row;
    while (!in.eof()) {
        std::getline(in, row);
        if (in.bad() || in.fail()) {
            break;
        }
        auto fields = readCSVRow(row);
        table.push_back(fields);
    }
    return table;
}

#include "CSVFile.h"

CSVFile::CSVFile() {
}

CSVFile::CSVFile( std::string fileName ) {
    this->read( fileName );
}

CSVFile::CSVFile(std::istream &csvFile ) {
    this->read( csvFile );
}

bool CSVFile::empty() {
    return ( this->table.empty() ) ;
}

void CSVFile::read( std::string fileName ) {
   std::ifstream csvFile;
   csvFile.open( fileName );
   this->read( csvFile );
   csvFile.close();
} 

void CSVFile::read(std::istream &csvFile ) {
    this->table.clear();
    if ( !(csvFile.bad() || csvFile.fail()) ) {
        table = readCSV( csvFile );
    }
}

unsigned int CSVFile::lineCount() {
    return table.size();
}

unsigned int CSVFile::dataCount() {
    return (this->lineCount() - 1);
}

unsigned int CSVFile::headerColumnCount() {
    return table[0].size();
}

unsigned int CSVFile::dataColumnCount( unsigned int rowNum ) {
    return table[rowNum].size();
}

std::string CSVFile::headerValue( unsigned int colNum ) {
    return table[0][colNum];
}

std::string CSVFile::dataValue( unsigned int rowNum,
                                unsigned int colNum ) {
    return table[rowNum-1][colNum];
}
std::vector<std::string> CSVFile::headers() {
    return table[0] ;
}
    
std::string CSVFile::headersAsString() {
    std::string antwort = "";
    std::string sep = "";
    for ( std::vector<std::string>::iterator it = table[0].begin();
            it != table[0].end(); it++ ) {
        antwort = antwort + sep + *it ;
        sep = ",";
    }
    return antwort;
}
std::vector<std::vector<std::string>> CSVFile::all() {
    return table;
}

std::vector<std::vector<std::string>> CSVFile::data() {
    std::vector<std::vector<std::string>> antwort = table;
    antwort.erase( antwort.begin() );
    return antwort;
}
