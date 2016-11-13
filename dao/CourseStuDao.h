/*
 * 操作数据库中学生选课名单的dao（Data Access Objec）类的定义
 *
 * Created by lyj on 11/6/16.
 */

#ifndef _COURSESTUDAO_H
#define _COURSESTUDAO_H

#include "../entity/Student.h"
#include "../entity/Course.h"
#include "../utils/DBUtil.h"
#include "../propertymaker.h"
//学生选课表在数据库中的名称
const static string COURSESTU_TABLE_NAME="course_stu";

class CourseStuDao{
private:
	static DBUtil *dBUtil;
	static ::_RecordsetPtr pRecordset;
	CourseStuDao(){}
public:

	//插入一条学生选课的记录
	static bool insertRecord(const Course& c,const Student& s,string tableName=COURSESTU_TABLE_NAME);
	static bool insertRecord(const string& cid,const string& sid,string tableName=COURSESTU_TABLE_NAME);
	//删除一条选课记录
	static bool deleteRecord(const Course& c,const Student& s,string tableName=COURSESTU_TABLE_NAME);
	static bool deleteRecord(const string& cid,const string& sid,string tableName=COURSESTU_TABLE_NAME);
	//根据学生信息返回该生所选课程
	static vector<Course> findCourseBySid(const Student& s,string tableName=COURSESTU_TABLE_NAME);
	static vector<Course> findCourseBySid(const string& sid,string tableName=COURSESTU_TABLE_NAME);
	//根据课程信息返回学生信息
	static vector<Student> findStudentByCid(const Course& c,string tableName=COURSESTU_TABLE_NAME);
	static vector<Student> findStudentByCid(const string& cid,string tableName=COURSESTU_TABLE_NAME);
	//所有内容
	static vector<CourseStu> findAllCourseStus(string tableName=COURSESTU_TABLE_NAME);
};

#endif