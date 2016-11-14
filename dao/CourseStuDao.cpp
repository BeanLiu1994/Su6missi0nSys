/*
 * 操作数据库中老师表的dao（Data Access Objec）类的实现
 *
 * Created by lyj on 11/6/16.
 */
#include "CourseStuDao.h"
#include "CourseDao.h"
#include "StudentDao.h"
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
vector<Course> CourseStuDao::findCourseBySidQuick(const string& sid){
    string sql="select * from course_stu sc,course c where sc.sid='"+sid+"' and sc.cid=c.cid;";
    pRecordset=dBUtil->getRecordSet(sql.c_str());
    vector<Course> v;
    while(!pRecordset->adoEOF)
    {

        string cid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("cid"));
        string cname=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("cname"));
        string tid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("tid"));
        Course c;
        c.setId(cid);
        c.setName(cname);
        c.setTeacherId(tid);
        v.push_back(c);
        pRecordset->MoveNext();
    }
    return v;
}
vector<Student> CourseStuDao::findStudentByCid(const Course& s,string tableName){
    vector<Student> v=findStudentByCid(s.getId());
    return v;
}
vector<Student> CourseStuDao::findStudentByCid(const string& cid,string tableName){
    string sql="select * from "+tableName+" where cid='"+cid+"';";
    pRecordset=dBUtil->getRecordSet(sql.c_str());
    vector<Student> v;
    while(!pRecordset->adoEOF)
    {
        string sid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("sid"));
        Student s=StudentDao::findStudentBySid(sid);
        v.push_back(s);
        pRecordset->MoveNext();
    }
    return v;
}
vector<Student> CourseStuDao::findStudentByCidQuick(const string& cid){
    string sql="select * from course_stu sc,student s where sc.cid='"+cid+"' and sc.sid=s.sid;";
    pRecordset=dBUtil->getRecordSet(sql.c_str());
    vector<Student> v;
    while(!pRecordset->adoEOF)
    {
        string sid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("sid"));
        string sname=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("sname"));
        Student s;
        s.setId(sid);
        s.setName(sname);
        v.push_back(s);
        pRecordset->MoveNext();
    }
    return v;
}
vector<CourseStu> CourseStuDao::findAllCourseStus(string tableName)
{
    string sql="select * from "+tableName+";";
    pRecordset=dBUtil->getRecordSet(sql.c_str());
    vector<CourseStu> v;
    while(!pRecordset->adoEOF)
    {
        string cid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("cid"));
        string sid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("sid"));
        CourseStu c;
        c.setsid(sid);
        c.setcid(cid);
        v.push_back(c);
        pRecordset->MoveNext();
    }
    return v;
}
