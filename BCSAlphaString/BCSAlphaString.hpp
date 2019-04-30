#ifndef BCS_ALPHA_STRING_H
#define BSC_ALPHA_STRING_H
#include <string>

class BCSAlphaString {
  private:
    int size;
    std::string value;
  public:
    BCSAlphaString(int);
    BCSAlphaString(int, std::string);
    void setBCSAlphaString(const std::string);
    void operator = (const std::string );
    void toBuffer(char *);
    void fromBuffer(char *);
    std::string toString();
    int getSize();
};

#endif // BCS_ALPHA_STRING_H
