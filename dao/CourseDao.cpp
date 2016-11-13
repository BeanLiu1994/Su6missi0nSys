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
bool CourseDao::deleteRecord(const string& cid, string tableName)
{
    string sql="delete from "+tableName+" where cid='"+cid+"';";
	pRecordset=dBUtil->getRecordSet(sql.c_str());
	return true;
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
bool CourseDao::updateName(Course& s,string NewName, string tableName)
{
	s.setName(NewName);
	string sql="update "+tableName+" set cname='"+NewName+"' where cid='"+s.getId()+"';";
	return dBUtil->executeSQL(sql.c_str());
}
bool CourseDao::updateTid(Course& s,string Tid, string tableName)
{
	s.setTeacherId(Tid);
	string sql="update "+tableName+" set tid='"+Tid+"' where cid='"+s.getId()+"';";
	return dBUtil->executeSQL(sql.c_str());
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
vector<Course> CourseDao::findAllCourses(string tableName){
    string sql="select cname,cid,tid from "+tableName;
    pRecordset=dBUtil->getRecordSet(sql.c_str());
    vector<Course> ss;
    while(!(pRecordset->adoEOF))
    {
        Course c;
        string cname=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("cname"));
        string cid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("cid"));
		string tid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("tid"));
        c.setId(cid);
        c.setName(cname);
		c.setTeacherId(tid);
        ss.push_back(c);
        //printf("%s,%s added \n",cid.c_str(),cname.c_str());
        pRecordset->MoveNext();
    }
    return ss;
}
