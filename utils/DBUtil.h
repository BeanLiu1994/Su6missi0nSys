/*
 * �������ݿ�Ĺ�����Ķ���
 *
 * Created by lyj on 11/6/16.
 */
#ifndef _DBUTIL_H_
#define _DBUTIL_H_

//����msado15������EOF������ΪadoEOF
#import "../lib/msado15.dll" no_namespace rename("EOF","adoEOF") rename("BOF","adoBOF")
class DBUtil
{ 
    private:
          ::_ConnectionPtr m_pConnection;
          ::_RecordsetPtr m_pRecordset;
		  char* conStr;
		  char* username;
		  char* password;
		  
		  //�������û�ͨ�����췽�����ʵ���������õ���ģʽ��ȷ��DBUtilֻ��һ��ʵ��
		 DBUtil();

          //��ʼ��-�������ݿ�
          void initDBUtil();
    public:
		//���DBUtil��ʵ����ʹ���˵���ģʽ�ķ���
		static DBUtil* getInstance();
		

          //ִ�в�ѯ�����ؽ����
          ::_RecordsetPtr & getRecordSet(_bstr_t bstrSQL);
          //ִ��sql��䣬�������ݿ�
         bool executeSQL(_bstr_t bstrSQL);
		  //�˳����ݿ�����
         void exitConnect();
		 
		 ~DBUtil(){			
				exitConnect();		 
		 }
};

#endif