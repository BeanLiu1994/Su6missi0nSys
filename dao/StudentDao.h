/*
 * �������ݿ���ѧ�����dao��Data Access Objec����Ķ���
 *
 * Created by lyj on 11/6/16.
 */

#ifndef _STUDENTDAO_H
#define _STUDENTDAO_H

#include "../entity/Student.h"
#include "../utils/DBUtil.h"
#include <vector>
using namespace std;
//ѧ���������ݿ��е�����
const static string STU_TABLE_NAME="student";

class StudentDao{
private:
	static DBUtil *dBUtil;
	static ::_RecordsetPtr pRecordset;
	StudentDao(){}
public:

	//����һ��ѧ���ļ�¼
	static bool insertRecord(const Student& s,string tableName=STU_TABLE_NAME);
	//ɾ��ѧ��
	static bool deleteRecord(const string& sid,string tableName=STU_TABLE_NAME);
	//�޸�ѧ��������
	static bool updateName(Student& s,string newName,string tableName=STU_TABLE_NAME);
	//�޸�ѧ��������
	static bool updatePassword(Student& s,const string newPassword,string tableName=STU_TABLE_NAME);
	//��¼ʱ����˺ź�����
	static bool find(const string id,const string password,string tableName=STU_TABLE_NAME);
	//����ѧ����id���ظ�ѧ��
	static Student findStudentBySid(const string& sid,string tableName=STU_TABLE_NAME);
	//��������ѧ����Ϣ
	static vector<Student> findAllStudents(string tableName=STU_TABLE_NAME);
};

#endif
