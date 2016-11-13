/*
 * 操作数据库中学生表的dao（Data Access Objec）类的实现
 *
 * Created by lyj on 11/6/16.
 */
#include "StudentDao.h"

DBUtil* StudentDao::dBUtil=DBUtil::getInstance();
::_RecordsetPtr StudentDao::pRecordset=NULL;

bool StudentDao::insertRecord( const Student& s,string tableName)
{
	string sql="insert into "+tableName+"(sid,sname,spassword) value('"+s.getId()+"','"+s.getName()+"','"+s.getPassword()+"');";
	return dBUtil->executeSQL(sql.c_str());
}
bool StudentDao::updateName(Student& s,string newName,string tableName)
{
	s.setName(newName);
	string sql="update "+tableName+" set tname='"+newName+"' where tid='"+s.getId()+"';";
	return dBUtil->executeSQL(sql.c_str());
}
bool StudentDao::updatePassword(Student& s,string newPassword,string tableName)
{
	s.setPassword(newPassword);
	string sql="update "+tableName+" set spassword='"+newPassword+"' where sid='"+s.getId()+"';";
	return dBUtil->executeSQL(sql.c_str());
}

bool StudentDao::find(const string id,const string password,string tableName)
{
	string sql="select * from "+tableName+" where sid='"+id+"' and spassword='"+password+"';";
	pRecordset=dBUtil->getRecordSet(sql.c_str());
	if(!pRecordset->adoEOF)
		return true;
	else
		return false;
}

Student StudentDao::findStudentBySid(const string& sid,string tableName){
	string sql="select * from "+tableName+" where sid='"+sid+"';";
	pRecordset=dBUtil->getRecordSet(sql.c_str());
	Student s;
	if(!pRecordset->adoEOF)
	{
		
		string tid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("sid"));
		string tname=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("sname"));
		string tpassword=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("spassword"));
		s.setId(tid);
		s.setName(tname);
	    s.setPassword(tpassword);
		//cout<<c.toString()<<endl;

	}
	return s;
}

vector<Student> StudentDao::findAllStudents(string tableName){
    string sql="select sname,sid from "+tableName;
    pRecordset=dBUtil->getRecordSet(sql.c_str());
    vector<Student> ss;
    while(!(pRecordset->adoEOF))
    {
        Student s;
        string sname=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("sname"));
        string sid=(LPSTR)(LPCSTR)_bstr_t(pRecordset->GetCollect("sid"));
        s.setId(sid);
        s.setName(sname);
        ss.push_back(s);
        //printf("%s,%s added \n",sid.c_str(),sname.c_str());
        pRecordset->MoveNext();
    }
    return ss;
}
