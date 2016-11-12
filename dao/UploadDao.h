/*
 * �������ݿ�����ҵ���dao��Data Access Objec����Ķ���
 *
 * Created by lyj on 11/7/16.
 */

#ifndef _UPLOADAO_H
#define _UPLOADAO_H
#include<vector>
#include<string>
#include "../entity/Upload.h"
#include "../utils/DBUtil.h"
//ѧ���������ݿ��е�����
const static string UPLOAD_TABLE_NAME="upload";

class UploadDao{
private:
	static DBUtil *dBUtil;
	static ::_RecordsetPtr pRecordset;
	UploadDao(){}
public:

	//����һ����ҵ�ļ�¼
	static bool insertRecord(const Upload& u,string tableName=UPLOAD_TABLE_NAME);
	/*
	//���ݿγ̺ŷ��ظÿγ����е���ҵ����
	static vector<string> findTimesByCid (const string&cid,string tableName=WORK_TABLE_NAME);	
	*/
	//������Ŀ��id��ѧ����id������ص���ҵ
	static Upload findUpload(const string& wid,const string&sid,string tableName=UPLOAD_TABLE_NAME);
	//������ҵid������ҵ�Ĵ�
	static bool updateAns(const Upload&u,string ans,string tableName=UPLOAD_TABLE_NAME);
		//������ҵid������ҵ�ĵ÷�
	static bool updateScore(const Upload&u,int score,string tableName=UPLOAD_TABLE_NAME);
	//������Ŀ��id�ŷ��ظ���Ŀ��ص���ҵ
	static vector<Upload> findUploads (const string& wid,string tableName=UPLOAD_TABLE_NAME);
	
};

#endif
