/*
 * 操作数据库中作业类的dao（Data Access Objec）类的定义
 *
 * Created by lyj on 11/7/16.
 */

#ifndef _UPLOADAO_H
#define _UPLOADAO_H
#include<vector>
#include<string>
#include "../entity/Upload.h"
#include "../utils/DBUtil.h"
//学生表在数据库中的名称
const static string UPLOAD_TABLE_NAME="upload";

class UploadDao{
private:
	static DBUtil *dBUtil;
	static ::_RecordsetPtr pRecordset;
	UploadDao(){}
public:

	//插入一道作业的记录
	static bool insertRecord(const Upload& u,string tableName=UPLOAD_TABLE_NAME);
	/*
	//根据课程号返回该课程所有的作业批次
	static vector<string> findTimesByCid (const string&cid,string tableName=WORK_TABLE_NAME);	
	*/
	//根据题目的id和学生的id返回相关的作业
	static Upload findUpload(const string& wid,const string&sid,string tableName=UPLOAD_TABLE_NAME);
	//根据作业id更新作业的答案
	static bool updateAns(const Upload&u,string ans,string tableName=UPLOAD_TABLE_NAME);
		//根据作业id更新作业的得分
	static bool updateScore(const Upload&u,int score,string tableName=UPLOAD_TABLE_NAME);
	//根据题目的id号返回该题目相关的作业
	static vector<Upload> findUploads (const string& wid,string tableName=UPLOAD_TABLE_NAME);
	
};

#endif
