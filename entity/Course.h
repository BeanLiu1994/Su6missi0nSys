/*
 * 课程实体类的定义文件
 *
 * Created by lyj on 11/6/16.
 */
#ifndef _COURSE_H_
#define _COURSE_H_
#include<iostream>
#include<string>
#include <vector>
#include "Student.h"
using namespace std;

class Course{
private:

	string _id;
	string _name;
	string _teacherId;
	//vector<Student> _stuVec;
public:
	Course(){};
	Course(string id,string name,string teacherId):_id(id),_name(name),_teacherId(teacherId){}
	string getId() const{return _id;}
	string getName()const{return _name;}
	string getTeacherId()const{return _teacherId;}
	void setId(string id){_id=id;}
	void setName(string name){_name=name;}
	void setTeacherId(string teacherId){_teacherId=teacherId;}
	string toString(){return _id+" "+_name+" "+_teacherId;}
};
#endif