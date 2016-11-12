/*
 * 操作数据库中学生表的dao（Data Access Objec）类的定义
 *
 * Created by lyj on 11/6/16.
 */

#ifndef _STUDENTDAO_H
#define _STUDENTDAO_H

#include "../entity/Student.h"
#include "../utils/DBUtil.h"
//学生表在数据库中的名称
const static string STU_TABLE_NAME="student";

class StudentDao{
private:
	static DBUtil *dBUtil;
	static ::_RecordsetPtr pRecordset;
	StudentDao(){}
public:

	//插入一条学生的记录
	static bool insertRecord(const Student& s,string tableName=STU_TABLE_NAME);
	//修改学生的密码
	static bool updatePassword(Student& s,const string newPassword,string tableName=STU_TABLE_NAME);
	//登录时检查账号和密码
	static bool find(const string id,const string password,string tableName=STU_TABLE_NAME);
	//根据学生的id返回该学生
	static Student findStudentBySid(const string& sid,string tableName=STU_TABLE_NAME);
};

#endif