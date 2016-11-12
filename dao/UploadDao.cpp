/*
 * 操作数据库中作业类的dao（Data Access Objec）类的实现
 *
 * Created by lyj on 11/7/16.
 */
#include<iostream>
#include<sstream>
using namespace std;
#include "UploadDao.h"

DBUtil* UploadDao::dBUtil=DBUtil::getInstance();
::_RecordsetPtr UploadDao::pRecordset=NULL;

bool UploadDao::insertRecord( const Upload& s,string tableName)
{
	int score=s.getScore();
	string scoreStr;
		stringstream ss;
		ss<<score;
		ss>>scoreStr;
		string sql="insert into "+tableName+"(uid,sid,wid,ucontent,uscore) value('"+s.getId()+"','"+s.getSid()+"','"+s.getWid()+"','"+s.getContent()+"',"+scoreStr+");";
	return dBUtil->executeSQL(sql.c_str());
}
Upload UploadDao::findUpload(const string& wid,const string&sid,string tableName)
{
	string sql="select * from "+tableName+" where wid='"+wid+"' and sid='"+sid+"';";
	pRecordset=dBUtil->getRecordSet(sql.c_str());
	Upload u;
	if(!pRecordset->adoEOF)
	{
		string id=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("uid"));
		string wid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("wid"));
		string sid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("sid"));
		string ucontent=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("ucontent"));
		string scoreStr=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("uscore"));
		//string转int
		int score;
		stringstream ss;
		ss<<scoreStr;
		ss>>score;
		
		u.setId(id);
		u.setWid(wid);
		u.setSid(sid);
		u.setContent(ucontent);
		u.setScore(score);
	}
	return u;
}
bool UploadDao::updateAns(const Upload&u,string ans,string tableName){
	string sql="update "+tableName+" set ucontent='"+ans+"' where uid='"+u.getId()+"';";
	return dBUtil->executeSQL(sql.c_str());
}
bool UploadDao::updateScore(const Upload&u,int score,string tableName){
	string scoreStr;	
	stringstream ss;
	ss<<score;
	ss>>scoreStr;


	string sql="update "+tableName+" set uscore='"+scoreStr+"' where uid='"+u.getId()+"';";
	return dBUtil->executeSQL(sql.c_str());
}
vector<Upload> UploadDao::findUploads (const string& wid,string tableName)
{
	string sql="select * from "+tableName+" where wid='"+wid+"';";
	pRecordset=dBUtil->getRecordSet(sql.c_str());
	vector<Upload> v;
	
	while(!pRecordset->adoEOF)
	{
		Upload u;
		string id=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("uid"));
		string wid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("wid"));
		string sid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("sid"));
		string ucontent=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("ucontent"));
		string scoreStr=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("uscore"));
		//string转int
		int score;
		stringstream ss;
		ss<<scoreStr;
		ss>>score;
		
		u.setId(id);
		u.setWid(wid);
		u.setSid(sid);
		u.setContent(ucontent);
		u.setScore(score);
		v.push_back(u);
		pRecordset->MoveNext();
	}
	
	return v;
}
/*

Work WorkDao::findWork(const string& cid,const string&wtime,string tableName){
	string sql="select * from "+tableName+" where cid='"+cid+"' and wtime="+wtime+";";
	pRecordset=dBUtil->getRecordSet(sql.c_str());
	Work w;
	if(!pRecordset->adoEOF)
	{
		string id=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("wid"));
		string cid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("cid"));
		string wtime=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("wtime"));
		string wcontent=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("wcontent"));
		string wanswer=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("wanswer"));
		string wdeadtime=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("wdeadtime"));
		
		w.setId(id);
		w.setCourseId(cid);
		w.setTime(wtime);
		w.setContent(wcontent);
		w.setAnswer(wanswer);
		w.setDate(wdeadtime);

		//cout<<c.toString()<<endl;

	}
	return w;
}
vector<string> WorkDao::findTimesByCid (const string&cid,string tableName)
{
	string sql="select wtime from "+tableName+" where cid='"+cid+"';";
	pRecordset=dBUtil->getRecordSet(sql.c_str());
	vector<string> v;
	while(!pRecordset->adoEOF)
	{
		
		string wtime=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("wtime"));
	
		v.push_back(wtime);
		pRecordset->MoveNext();
	}
	return v;
}
*/