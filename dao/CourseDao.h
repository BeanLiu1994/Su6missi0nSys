/*
 * �������ݿ��пγ̱��dao��Data Access Objec����Ķ���
 *
 * Created by lyj on 11/6/16.
 */

#ifndef _COURSEDAO_H
#define _COURSEDAO_H

#include "../entity/Teacher.h"
#include "../entity/Course.h"
#include "../utils/DBUtil.h"
#include<vector>
//ѧ���������ݿ��е�����
const static string COURSE_TABLE_NAME="course";

class CourseDao{
private:
	static DBUtil *dBUtil;
	static ::_RecordsetPtr pRecordset;
	CourseDao(){}
public:

	//����һ���γ̵ļ�¼
	static bool insertRecord(const Course& s,string tableName=COURSE_TABLE_NAME);
	//��������
	static bool updateName(Course& s,string NewName, string tableName=COURSE_TABLE_NAME);
	//����Tid
	static bool updateTid(Course& s,string NewTid, string tableName=COURSE_TABLE_NAME);
	//������ʦ��id�ҳ�����ʦִ�̵Ŀγ̵�id
	static vector<Course> findCourseByTid(const Teacher& s,string tableName=COURSE_TABLE_NAME);
	static vector<Course> findCourseByTid(const string& tid,string tableName=COURSE_TABLE_NAME);
	//����course��id���ظ�course
	static Course findCourseByCid(const string& cid,string tableName=COURSE_TABLE_NAME);
	//�������пγ���Ϣ
	static vector<Course> findAllCourses(string tableName=COURSE_TABLE_NAME);

};

#endif