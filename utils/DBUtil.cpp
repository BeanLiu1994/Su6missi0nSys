/*
 * 操作数据库的工具类的实现
 *
 * Created by lyj on 11/6/16.
 */
#include "DBUtil.h"


#include<iostream>
#include<string>
using namespace std;

//DBUtil*  DBUtil::dBUtil=NULL;

DBUtil* DBUtil::getInstance(){
	static DBUtil dBUtil;
	return &dBUtil;

}

DBUtil::DBUtil()
{
	m_pConnection=NULL;
	m_pRecordset=NULL;
	//为连接字符串，用户名，密码赋初值，不同的数据库类型连接字符串不同
    conStr=(char *)"DSN=visg;Server=visg.nju.edu.cn;Database=submissionSystem";
    username=(char *)"app";
    password=(char *)"visg";
}

void DBUtil::initDBUtil()
{
 ::CoInitialize(NULL);//   初始化OLE/COM库环境   ，为访问ADO接口做准备 
 //AfxOleInit();//used in MFC
 HRESULT hr;
 try
 {
  
  hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象
  hr = m_pConnection->Open( conStr,username, password, adModeUnknown);
  if(SUCCEEDED(hr))
   cout<<endl;
   cout<<"连接数据库sucess"<<endl;
 
 }
 catch(_com_error e)///捕捉异常
 {
  //在MFC程序中用于提示错误的弹出消息框
  //CString errormessage;
  //errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
  //AfxMessageBox(errormessage);///显示错误信息
  cout<<"连接数据库失败！\r\n错误信息："<<e.Description()<<endl;
  
  
 }
}
_RecordsetPtr & DBUtil::getRecordSet(_bstr_t bstrSQL)
{
 try
 {
  cout<<bstrSQL<<endl;
  //连接数据库，如果connection对象为空，则重新连接数据库
  if(m_pConnection==NULL)
   initDBUtil();
  //创建记录集对象
  m_pRecordset.CreateInstance(_uuidof(Recordset));
  m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
 }
 catch(_com_error e)
 {
   
  cout<<e.Description()<<endl;
  
 }
 //返回记录集
 return m_pRecordset;
}
bool DBUtil::executeSQL(_bstr_t bstrSQL)
{
 try
 {
  //是否已经连接数据库
  if(m_pConnection ==NULL)
   initDBUtil();
  m_pConnection->Execute(bstrSQL,NULL,adCmdText);
  return true;
 }
 catch(_com_error e)
 {
    //AfxMessageBox(e.Description());
  cout<<e.Description()<<endl;
  return false;
 }
}
void DBUtil::exitConnect()
{
 //关闭记录集和连接
 if(m_pRecordset !=NULL)
  m_pRecordset->Close();
  m_pConnection->Close();
 //释放环境
 ::CoUninitialize();//关闭ole/com库，释放资源
 cout<<"退出数据库"<<endl;


}
