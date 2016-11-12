/*
 * 作业类的定义文件
 *
 * Created by lyj on 11/7/16.
 */
#ifndef _UPLOAD_H_
#define _UPLOAD_H_
#include<iostream>
#include<string>

using namespace std;

class Upload{
private:
	string _id;
	string _sid;
	string _wid;
	string _content;
	int _score;
	//vector<Student> _stuVec;
public:
	Upload():_score(-1){}
	Upload(string sid,string wid,string content):_id(wid+"_"+sid),_sid(sid),_wid(wid),_content(content),_score(-1){}
	Upload(string sid,string wid):_id(wid+"_"+sid),_sid(sid),_wid(wid),_score(-1){}

	string getId()const{return _id;}
	string getSid()const{return _sid;}
	string getWid()const{return _wid;}
	string getContent()const{return _content;}
	int getScore()const{return _score;}
	

	void setId(string id){_id=id;}
	void setSid(string sid){_sid=sid;}

	void setWid(string wid){_wid=wid;}
	void setContent(string content){_content=content;}
	void setScore(int score){_score=score;}
	string toString(){return _sid+" "+_wid+" "+_content;}
};
#endif