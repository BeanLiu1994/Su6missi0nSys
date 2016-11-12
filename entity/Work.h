/*
 * 题目类的定义文件
 *
 * Created by lyj on 11/6/16.
 */
#ifndef _WORK_H_
#define _WORK_H_
#include<iostream>
#include<string>

using namespace std;

class Work{
private:
	string _id;
	string _courseId;
	string _time;
	string _content;
	string _answer;
	string _date;
	//vector<Student> _stuVec;
public:
	Work(){}
	Work(string courseId,string time,string content,string answer,string date):_id(courseId+"_"+time),_courseId(courseId),_time(time),_content(content),_answer(answer),_date(date){}
	Work(string courseId,string time):_id(courseId+"_"+time),_courseId(courseId),_time(time){}

	string getId()const{return _id;}
	string getCourseId()const{return _courseId;}
	string getTime()const{return _time;}
	string getContent()const{return _content;}
	string getAnswer()const{return _answer;}
	string getDate()const{return _date;}

	void setId(string id){_id=id;}
	void setCourseId(string courseId){_courseId=courseId;}

	void setTime(string time){_time=time;}
	void setContent(string content){_content=content;}
	
	void setAnswer(string answer){_answer=answer;}
	void setDate(string date){_date=date;}
	string toString(){return _courseId+" "+_content+" "+_date;}
};
#endif