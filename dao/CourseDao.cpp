/*
 * 操作数据库中学生表的dao（Data Access Objec）类的实现
 *
 * Created by lyj on 11/6/16.
 */
#include "CourseDao.h"

DBUtil* CourseDao::dBUtil=DBUtil::getInstance();
::_RecordsetPtr CourseDao::pRecordset=NULL;

bool CourseDao::insertRecord( const Course& s,string tableName)
{
	string sql="insert into "+tableName+"(cid,cname,tid) value('"+s.getId()+"','"+s.getName()+"','"+s.getTeacherId()+"');";
	return dBUtil->executeSQL(sql.c_str());
}
vector<Course> CourseDao::findCourseByTid(const Teacher& t,string tableName){
	vector<Course> v=findCourseByTid(t.getId());
	return v;
}
vector<Course> CourseDao::findCourseByTid(const string& tid,string tableName){
	string sql="select * from "+tableName+" where tid='"+tid+"';";
	pRecordset=dBUtil->getRecordSet(sql.c_str());
	vector<Course> v;
	while(!pRecordset->adoEOF)
	{
		
		string cid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("cid"));
		string cname=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("cname"));
		Course c(cid,cname,tid);
		//cout<<c.toString()<<endl;
		v.push_back(c);
		pRecordset->MoveNext();
	}
	return v;
}
Course CourseDao::findCourseByCid(const string& cid,string tableName){
	string sql="select * from "+tableName+" where cid='"+cid+"';";
	pRecordset=dBUtil->getRecordSet(sql.c_str());
	Course c;
	if(!pRecordset->adoEOF)
	{
		
		string cid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("cid"));
		string cname=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("cname"));
		string tid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("tid"));
		c.setId(cid);
		c.setName(cname);
		c.setTeacherId(tid);
		//cout<<c.toString()<<endl;

	}
	return c;
}