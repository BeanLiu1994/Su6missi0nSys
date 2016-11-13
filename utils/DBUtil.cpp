/*
 * �������ݿ�Ĺ������ʵ��
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
	//Ϊ�����ַ������û��������븳��ֵ����ͬ�����ݿ����������ַ�����ͬ
    conStr=(char *)"DSN=visg;Server=visg.nju.edu.cn;Database=submissionSystem";
    username=(char *)"app";
    password=(char *)"visg";
}

void DBUtil::initDBUtil()
{
 ::CoInitialize(NULL);//   ��ʼ��OLE/COM�⻷��   ��Ϊ����ADO�ӿ���׼�� 
 //AfxOleInit();//used in MFC
 HRESULT hr;
 try
 {
  
  hr = m_pConnection.CreateInstance("ADODB.Connection");///����Connection����
  hr = m_pConnection->Open( conStr,username, password, adModeUnknown);
  if(SUCCEEDED(hr))
   cout<<endl;
   cout<<"�������ݿ�sucess"<<endl;
 
 }
 catch(_com_error e)///��׽�쳣
 {
  //��MFC������������ʾ����ĵ�����Ϣ��
  //CString errormessage;
  //errormessage.Format("�������ݿ�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
  //AfxMessageBox(errormessage);///��ʾ������Ϣ
  cout<<"�������ݿ�ʧ�ܣ�\r\n������Ϣ��"<<e.Description()<<endl;
  
  
 }
}
_RecordsetPtr & DBUtil::getRecordSet(_bstr_t bstrSQL)
{
 try
 {
  cout<<bstrSQL<<endl;
  //�������ݿ⣬���connection����Ϊ�գ��������������ݿ�
  if(m_pConnection==NULL)
   initDBUtil();
  //������¼������
  m_pRecordset.CreateInstance(_uuidof(Recordset));
  m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
 }
 catch(_com_error e)
 {
   
  cout<<e.Description()<<endl;
  
 }
 //���ؼ�¼��
 return m_pRecordset;
}
bool DBUtil::executeSQL(_bstr_t bstrSQL)
{
 try
 {
  //�Ƿ��Ѿ��������ݿ�
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
 //�رռ�¼��������
 if(m_pRecordset !=NULL)
  m_pRecordset->Close();
  m_pConnection->Close();
 //�ͷŻ���
 ::CoUninitialize();//�ر�ole/com�⣬�ͷ���Դ
 cout<<"�˳����ݿ�"<<endl;


}
