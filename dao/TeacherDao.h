/*
 * �������ݿ��н�ʦ���dao��Data Access Objec����Ķ���
 *
 * Created by lyj on 11/6/16.
 */

#ifndef _TEACHERDAO_H
#define _TEACHERDAO_H

#include "../entity/Teacher.h"
#include "../entity/Course.h"
#include "../utils/DBUtil.h"

//��ʦ�������ݿ��е�����
const static string TEA_TABLE_NAME="teacher";

class TeacherDao{
private:
	static DBUtil *dBUtil;
	static ::_RecordsetPtr pRecordset;
	TeacherDao(){}
public:
	//����һ����ʦ�ļ�¼
	static bool insertRecord(const Teacher& s,string tableName=TEA_TABLE_NAME);
	//�޸���ʦ������
	static bool updateName(Teacher& s,string newName,string tableName=TEA_TABLE_NAME);
	//�޸���ʦ������
	static bool updatePassword(Teacher& s,string newPassword,string tableName=TEA_TABLE_NAME);
	//ɾ����ʦ
	static bool deleteRecord(const string& tid,string tableName=TEA_TABLE_NAME);
	//��¼ʱ����˺ź�����
	static bool find(const string id,const string password,string tableName=TEA_TABLE_NAME);
	//���ݽ�ʦ��id���ظý�ʦ
	static Teacher findTeacherByTid(const string& tid,string tableName=TEA_TABLE_NAME);
    //������ʦ�Ľ��
    static vector<Teacher> findAllTeachers(string tableName=TEA_TABLE_NAME);
};

#endif
