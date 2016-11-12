/*
 * 操作数据库的工具类的定义
 *
 * Created by lyj on 11/6/16.
 */
#ifndef _DBUTIL_H_
#define _DBUTIL_H_

//导入msado15，并将EOF重命名为adoEOF
#import "../lib/msado15.dll" no_namespace rename("EOF","adoEOF") rename("BOF","adoBOF")
class DBUtil
{ 
    private:
          ::_ConnectionPtr m_pConnection;
          ::_RecordsetPtr m_pRecordset;
		  char* conStr;
		  char* username;
		  char* password;
		  
		  //不允许用户通过构造方法获得实例，而是用单例模式，确保DBUtil只有一份实例
		 DBUtil();

          //初始化-连接数据库
          void initDBUtil();
    public:
		//获得DBUtil的实例，使用了单例模式的方法
		static DBUtil* getInstance();
		

          //执行查询，返回结果集
          ::_RecordsetPtr & getRecordSet(_bstr_t bstrSQL);
          //执行sql语句，更新数据库
         bool executeSQL(_bstr_t bstrSQL);
		  //退出数据库连接
         void exitConnect();
		 
		 ~DBUtil(){			
				exitConnect();		 
		 }
};

#endif