/*
 * �������ݿ�����Ŀ���dao��Data Access Objec����Ķ���
 *
 * Created by lyj on 11/6/16.
 */

#ifndef _WORKDAO_H
#define _WORKDAO_H
#include<vector>
#include<string>
#include "../entity/Work.h"
#include "../utils/DBUtil.h"
//ѧ���������ݿ��е�����
const static string WORK_TABLE_NAME="work";

class WorkDao{
private:
	static DBUtil *dBUtil;
	static ::_RecordsetPtr pRecordset;
	WorkDao(){}
public:

	//����һ����Ŀ�ļ�¼
	static bool insertRecord(const Work& s,string tableName=WORK_TABLE_NAME);
	//���ݿγ̺ŷ��ظÿγ����е���ҵ����
	static vector<string> findTimesByCid (const string&cid,string tableName=WORK_TABLE_NAME);	
	
	//������Ŀ�Ŀγ̺ź����η��ظ���Ŀ
	static Work findWork(const string& cid,const string&wtime,string tableName=WORK_TABLE_NAME);
};

#endif