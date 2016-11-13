/*
 * 操作数据库中教师表的dao（Data Access Objec）类的定义
 *
 * Created by lyj on 11/6/16.
 */

#ifndef _TEACHERDAO_H
#define _TEACHERDAO_H

#include "../entity/Teacher.h"
#include "../entity/Course.h"
#include "../utils/DBUtil.h"

//老师表在数据库中的名称
const static string TEA_TABLE_NAME="teacher";

class TeacherDao{
private:
	static DBUtil *dBUtil;
	static ::_RecordsetPtr pRecordset;
	TeacherDao(){}
public:
	//插入一条老师的记录
	static bool insertRecord(const Teacher& s,string tableName=TEA_TABLE_NAME);
	//修改老师的姓名
	static bool updateName(Teacher& s,string newName,string tableName=TEA_TABLE_NAME);
	//修改老师的密码
	static bool updatePassword(Teacher& s,string newPassword,string tableName=TEA_TABLE_NAME);
	//删除老师
	static bool deleteRecord(const string& tid,string tableName=TEA_TABLE_NAME);
	//登录时检查账号和密码
	static bool find(const string id,const string password,string tableName=TEA_TABLE_NAME);
	//根据教师的id返回该教师
	static Teacher findTeacherByTid(const string& tid,string tableName=TEA_TABLE_NAME);
    //所有老师的结果
    static vector<Teacher> findAllTeachers(string tableName=TEA_TABLE_NAME);
};

#endif
