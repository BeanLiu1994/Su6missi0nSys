/*
 * �������ݿ���ѧ��ѡ��������dao��Data Access Objec����Ķ���
 *
 * Created by lyj on 11/6/16.
 */

#ifndef _COURSESTUDAO_H
#define _COURSESTUDAO_H

#include "../entity/Student.h"
#include "../entity/Course.h"
#include "../utils/DBUtil.h"
#include "../propertymaker.h"
//ѧ��ѡ�α������ݿ��е�����
const static string COURSESTU_TABLE_NAME="course_stu";

class CourseStuDao{
private:
	static DBUtil *dBUtil;
	static ::_RecordsetPtr pRecordset;
	CourseStuDao(){}
public:

	//����һ��ѧ��ѡ�εļ�¼
	static bool insertRecord(const Course& c,const Student& s,string tableName=COURSESTU_TABLE_NAME);
	static bool insertRecord(const string& cid,const string& sid,string tableName=COURSESTU_TABLE_NAME);
	//ɾ��һ��ѡ�μ�¼
	static bool deleteRecord(const Course& c,const Student& s,string tableName=COURSESTU_TABLE_NAME);
	static bool deleteRecord(const string& cid,const string& sid,string tableName=COURSESTU_TABLE_NAME);
	//����ѧ����Ϣ���ظ�����ѡ�γ�
	static vector<Course> findCourseBySid(const Student& s,string tableName=COURSESTU_TABLE_NAME);
	static vector<Course> findCourseBySid(const string& sid,string tableName=COURSESTU_TABLE_NAME);
	//���ݿγ���Ϣ����ѧ����Ϣ
	static vector<Student> findStudentByCid(const Course& c,string tableName=COURSESTU_TABLE_NAME);
	static vector<Student> findStudentByCid(const string& cid,string tableName=COURSESTU_TABLE_NAME);
	//��������
	static vector<CourseStu> findAllCourseStus(string tableName=COURSESTU_TABLE_NAME);
};

#endif