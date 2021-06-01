#ifndef STRING_H
#define STRING_H

//5. lab String5 fileja, kommentek nélkül
#include <iostream>

class String {
    char *pData;        ///< pointer az adatra
    size_t len;         ///< hossz lezáró nulla nélkül
public:
    void printDbg(const char *txt = "") const {
        std::cout << txt << "[" << len << "], "
                  << (pData ? pData : "(NULL)") << '|' << std::endl;
    }
    String();

    size_t size() const { return len; }
    const char* c_str() const { return pData;}


    ~String();

    String(const char c);
    String(const char* s);
    String(const String& s);

    String& operator=(const String& s);
    String operator+(const char c) const ;
    String operator+(const char* s) const;
    String operator+(const String& s) const;

    String operator+(const int num) const;

    const char& operator[](size_t i) const;
    char& operator[](size_t i);


}; /// Itt az osztály deklarációjának vége


String operator+(const char c, const String& s);
std::ostream& operator<<(std::ostream& os, String& s);
std::istream& operator>>(std::istream& is, String& s);





#endif
