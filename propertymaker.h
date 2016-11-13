#ifndef PROPERTYMAKER_H
#define PROPERTYMAKER_H

#define MakeProperty(name,type) \
protected: type _##name;\
public: type get##name() const {return _##name;}\
public: void set##name(type t){_##name=t;}

#include <string>
using std::string;

class CourseStu
{
    MakeProperty(sid,string);
    MakeProperty(cid,string);
public :
    CourseStu(){}
};

#endif // PROPERTYMAKER_H
