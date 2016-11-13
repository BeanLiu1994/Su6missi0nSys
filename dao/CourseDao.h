/*
 * 操作数据库中课程表的dao（Data Access Objec）类的定义
 *
 * Created by lyj on 11/6/16.
 */

#ifndef _COURSEDAO_H
#define _COURSEDAO_H

#include "../entity/Teacher.h"
#include "../entity/Course.h"
#include "../utils/DBUtil.h"
#include<vector>
//学生表在数据库中的名称
const static string COURSE_TABLE_NAME="course";

class CourseDao{
private:
	static DBUtil *dBUtil;
	static ::_RecordsetPtr pRecordset;
	CourseDao(){}
public:

	//插入一条课程的记录
	static bool insertRecord(const Course& s,string tableName=COURSE_TABLE_NAME);
	//更新名字
	static bool updateName(Course& s,string NewName, string tableName=COURSE_TABLE_NAME);
	//更新Tid
	static bool updateTid(Course& s,string NewTid, string tableName=COURSE_TABLE_NAME);
	//根据老师的id找出该老师执教的课程的id
	static vector<Course> findCourseByTid(const Teacher& s,string tableName=COURSE_TABLE_NAME);
	static vector<Course> findCourseByTid(const string& tid,string tableName=COURSE_TABLE_NAME);
	//根据course的id返回该course
	static Course findCourseByCid(const string& cid,string tableName=COURSE_TABLE_NAME);
	//返回所有课程信息
	static vector<Course> findAllCourses(string tableName=COURSE_TABLE_NAME);

};

#endif