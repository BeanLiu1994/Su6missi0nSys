/*
 * 操作数据库中老师表的dao（Data Access Objec）类的实现
 *
 * Created by lyj on 11/6/16.
 */
#include "CourseStuDao.h"
#include "CourseDao.h"
DBUtil* CourseStuDao::dBUtil=DBUtil::getInstance();
::_RecordsetPtr CourseStuDao::pRecordset=NULL;
bool CourseStuDao::insertRecord( const string& cid,const string& sid,string tableName)
{
	string sql="insert into "+tableName+"(cid,sid) value('"+cid+"','"+sid+"');";
	return dBUtil->executeSQL(sql.c_str());
}
bool CourseStuDao::insertRecord( const Course& c,const Student& s,string tableName)
{
	return insertRecord(c.getId(),s.getId());
}
bool CourseStuDao::deleteRecord( const string& cid,const string& sid,string tableName)
{
	string sql="delete from "+tableName+" where cid='"+cid+"' and sid='"+sid+"';";
	return dBUtil->executeSQL(sql.c_str());
}
bool CourseStuDao::deleteRecord( const Course& c,const Student& s,string tableName)
{
	return deleteRecord(c.getId(),s.getId());
}
vector<Course> CourseStuDao::findCourseBySid(const Student& s,string tableName){
	vector<Course> v=findCourseBySid(s.getId());
	return v;
}
vector<Course> CourseStuDao::findCourseBySid(const string& sid,string tableName){
	string sql="select * from "+tableName+" where sid='"+sid+"';";
	pRecordset=dBUtil->getRecordSet(sql.c_str());
	vector<Course> v;
	while(!pRecordset->adoEOF)
	{
		
		string cid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("cid"));
		Course c=CourseDao::findCourseByCid(cid);
		v.push_back(c);
		pRecordset->MoveNext();
	}
	return v;
}
