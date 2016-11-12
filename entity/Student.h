/*
 * 学生实体类的定义文件
 *
 * Created by lyj on 11/6/16.
 */
#ifndef _STUDENT_H_
#define _STUDENT_H_

#include<iostream>
#include<string>
using namespace std;

class Student{
private:

	string _id;
	string _name;
	string _password;

public:
	Student(){}
	Student(string id,string name,string password):_id(id),_name(name),_password(password){}
	string getId() const{return _id;}
	string getName()const{return _name;}
	string getPassword()const{return _password;}
	void setId(string id){_id=id;}
	void setName(string name){_name=name;}
	void setPassword(string password){_password=password;}
	string toString(){return _id+" "+_name;}
};


#endif