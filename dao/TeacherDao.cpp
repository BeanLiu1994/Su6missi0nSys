/*
 * 操作数据库中老师表的dao（Data Access Objec）类的实现
 *
 * Created by lyj on 11/6/16.
 */
#include "TeacherDao.h"

DBUtil* TeacherDao::dBUtil=DBUtil::getInstance();
::_RecordsetPtr TeacherDao::pRecordset=NULL;
bool TeacherDao::insertRecord( const Teacher& s,string tableName)
{
	string sql="insert into "+tableName+"(tid,tname,tpassword) value('"+s.getId()+"','"+s.getName()+"','"+s.getPassword()+"');";
	return dBUtil->executeSQL(sql.c_str());
}
bool TeacherDao::updatePassword(Teacher& s,string newPassword,string tableName)
{
	s.setPassword(newPassword);
	string sql="update "+tableName+" set tpassword='"+newPassword+"' where tid='"+s.getId()+"';";
	return dBUtil->executeSQL(sql.c_str());
}
bool TeacherDao::updateName(Teacher& s,string newName,string tableName)
{
	s.setName(newName);
	string sql="update "+tableName+" set tname='"+newName+"' where tid='"+s.getId()+"';";
	return dBUtil->executeSQL(sql.c_str());
}
bool TeacherDao::find(const string id,const string password,string tableName)
{
	string sql="select * from "+tableName+" where tid='"+id+"' and tpassword='"+password+"';";
	pRecordset=dBUtil->getRecordSet(sql.c_str());
	if(!pRecordset->adoEOF)
		return true;
	else
		return false;
}
Teacher TeacherDao::findTeacherByTid(const string& tid,string tableName){
	string sql="select * from "+tableName+" where tid='"+tid+"';";
	pRecordset=dBUtil->getRecordSet(sql.c_str());
	Teacher t;
	if(!pRecordset->adoEOF)
	{
		
		string tid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("tid"));
		string tname=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("tname"));
		string tpassword=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("tpassword"));
		t.setId(tid);
		t.setName(tname);
	    t.setPassword(tpassword);
		//cout<<c.toString()<<endl;

	}
	return t;
}

bool TeacherDao::deleteRecord(const string& tid,string tableName){
    string sql="delete from "+tableName+" where tid='"+tid+"';";
    pRecordset=dBUtil->getRecordSet(sql.c_str());
	return true;
}

vector<Teacher> TeacherDao::findAllTeachers(string tableName){
    string sql="select tname,tid from "+tableName;
    pRecordset=dBUtil->getRecordSet(sql.c_str());
    vector<Teacher> ts;
    while(!(pRecordset->adoEOF))
    {
        Teacher t;
        string tname=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("tname"));
        string tid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("tid"));
        t.setId(tid);
        t.setName(tname);
        ts.push_back(t);
        //printf("%s,%s added \n",tid.c_str(),tname.c_str());
        pRecordset->MoveNext();
    }
    return ts;
}
