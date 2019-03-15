#ifndef PATH_NAME_H
#define PATH_NAME_H

#include <string>

class PathName {
  private:
    std::string rawName;
    std::string myDirName;
    std::string myBaseName;
    std::string myFileName;
    std::string myExtension;
    void clearMyNames();
  public:
    //
    // constructors
    //
    PathName();
    PathName(const std::string);
    PathName(const std::string, const std::string);
    PathName(const std::string, const std::string, const std::string);
    //
    // setters and getters
    //
    void setRawName(const char*);
    void setRawName(std::string);
    void setDirBase(std::string, std::string);
    void setDirFileExt(std::string, std::string, std::string);
    void append(std::string);
    void clear();
    std::string getRawName();
    // 
    // The rest of the class functionality
    //
    std::string dirname();
    std::string basename();
    std::string file();
    std::string ext();
    bool exists();
    std::string canonicalize();
    bool containsDots();
    bool containsSlash();
    bool isAbsolute();
    bool isRelative();
    bool empty();
    off_t fileSize();
};

#endif // PATH_NAME_H
