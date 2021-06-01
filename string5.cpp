#ifdef _MSC_VER
// MSC ne adjon figyelmeztető üzenetet a C sztringkezelő függvényeire
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Sztringműveletekhez

#include "string5.h"


String::String():len(0){
    pData = new char[len+1];
    pData[0] ='\0';
}

String::String(const char c) :len(1){
    pData = new char[len+1];
    pData[0] = c;
    pData[1] = '\0';
}

String::String(const char* s) :len(strlen(s)){
    pData = new char[len+1];
    strcpy(pData,s);
}


String::String(const String& s):len(s.len){
    pData = new char[len+1];
    strcpy(pData,s.pData);
}


String::~String(){
    delete[] pData;
}

String& String::operator=(const String& s){
    if(&s == this){return *this;}
    len = s.len;
    delete[] pData;
    pData = new char[len+1];
    for(size_t i = 0; i < len+1;++i){
        pData[i] = s.pData[i];
    }
    return *this;
}

const char& String::operator[](size_t i) const{
    if(i >= len){
        throw "Túlindexelés";
    }
    return pData[i];
}
char& String::operator[](size_t i){
    if(i >= len){
        throw "Túlindexelés";
    }
    return pData[i];
}


String String::operator+(char c) const {
    char* ki = new char[len+2];
    for(size_t i = 0; i < len+1;++i){
        ki[i] = pData[i];
    }
    ki[len] = c;
    ki[len+1] ='\0';
    String Ski;
    delete[] Ski.pData;
    Ski.pData = ki;
    Ski.len = len+1;
    return Ski;
}
String String::operator+(const char* s) const{
    size_t slen = strlen(s);
    char* ki = new char[len+slen+1];
    size_t i = 0;
    while(i < len){
        ki[i] = pData[i];
        ++i;
    }
    for(size_t j = 0; j <slen+1;++j){
        ki[i+j] = s[j];
    }
    //strcpy/cat-el nem működött.
    String Ski;
    delete[] Ski.pData;
    Ski.pData = ki;
    Ski.len = strlen(ki);
    return Ski;
}
String String::operator+(const String& s) const{
    return (*this+s.pData);
}

String operator+(const char c, const String& s){
    char* ki = new char[s.size()+2];
    ki[0] = c;
    for(size_t i = 1; i < s.size()+2;++i){
        ki[i] = s.c_str()[i-1];
    }
    String Ski(ki);
    delete[] ki;
    return Ski;
}

std::ostream& operator<<(std::ostream& os, String& s){
    return os << s.c_str();
}


std::istream& operator>>(std::istream& is, String& s){
    char* olv = new char[99];
    /*std::ios_base::fmtflags startflags = is.flags();
    is.flags(startflags | std::ios_base::skipws) ;
    is >> olv;
    is.flags(startflags);*/
    char c = '0';
    while(is.get(c) && c == ' '){
        continue;
    }
    olv[0] = c;
    size_t i = 1;
    while( i < 99 && is.get(c) && c != ' ' && c != '\n' && c != '\0'){
        olv[i] = c;
        ++i;
    }
    olv[i] = '\0';
    s = olv;
    delete[] olv;
    return is;
}

String String::operator+(const int num) const{
    if(num == 0)
        return *this + '0';
    int num2 = num;
    bool n = num < 0;


    String out1;
    if(n)
        num2 *= -1;
    while(num2 > 0){
        out1 = out1 + (char)('0'+ num2 % 10);
        num2 %= 10;
        num2 /= 10;
    }
    if(n)
        out1 = out1 + '-';
    String out2;
    for(size_t i = 0; i < out1.size(); ++i){
        out2 = out2 + out1[out1.size() - i - 1];
    }
    return *this + out2;
}

