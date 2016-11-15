/*
 * 操作数据库中题目类的dao（Data Access Objec）类的实现
 *
 * Created by lyj on 11/6/16.
 */
#include "WorkDao.h"

DBUtil* WorkDao::dBUtil=DBUtil::getInstance();
::_RecordsetPtr WorkDao::pRecordset=NULL;

bool WorkDao::insertRecord( const Work& s,string tableName)
{
	string sql="insert into "+tableName+"(wid,cid,wtime,wcontent,wanswer,wdeadtime) value('"+s.getId()+"','"+s.getCourseId()+"','"+s.getTime()+"','"+s.getContent()+"','"+s.getAnswer()+"','"+s.getDate()+"');";
	return dBUtil->executeSQL(sql.c_str());
}
Work WorkDao::findWorkByCid(const string& cid,const string&wtime,string tableName){
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
Work WorkDao::findWorkByWid(const string& wid,string tableName)
{
    string sql="select * from "+tableName+" where wid='"+wid+"';";
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

        //cout<<w.toString()<<endl;

    }
    return w;
}
vector<Work> WorkDao::findAllWorks (string tableName)
{
    string sql="select * from "+tableName+";";
    pRecordset=dBUtil->getRecordSet(sql.c_str());
    vector<Work> v;
    Work w;
    while(!pRecordset->adoEOF)
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

        v.push_back(w);
        pRecordset->MoveNext();
    }
    return v;
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
vector<Work> WorkDao::findWorkByCidOnly(const string& cid,string tableName)
{
    string sql="select * from "+tableName+" where cid='"+cid+"';";
    pRecordset=dBUtil->getRecordSet(sql.c_str());
    vector<Work> v;
    Work w;
    while(!pRecordset->adoEOF)
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
        v.push_back(w);
        //cout<<c.toString()<<endl;
        pRecordset->MoveNext();

    }
    return v;
}
bool WorkDao::updateRecord(Work& w,string tableName)
{
    deleteRecord(w.getId());
    return insertRecord(w);
}
bool WorkDao::deleteRecord(const string& wid,string tableName)
{
    string sql="delete from "+tableName+" where wid='"+wid+"';";
    return dBUtil->executeSQL(sql.c_str());
}
