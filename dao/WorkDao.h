/*
 * 操作数据库中题目类的dao（Data Access Objec）类的定义
 *
 * Created by lyj on 11/6/16.
 */

#ifndef _WORKDAO_H
#define _WORKDAO_H
#include<vector>
#include<string>
#include "../entity/Work.h"
#include "../utils/DBUtil.h"
//学生表在数据库中的名称
const static string WORK_TABLE_NAME="work";

class WorkDao{
private:
	static DBUtil *dBUtil;
	static ::_RecordsetPtr pRecordset;
	WorkDao(){}
public:

	//插入一道题目的记录
    static bool insertRecord(const Work& s,string tableName=WORK_TABLE_NAME);
    //根据课程号返回该课程所有的作业批次
    static vector<string> findTimesByCid (const string&cid,string tableName=WORK_TABLE_NAME);
	
	//根据题目的课程号和批次返回该题目
    static Work findWork(const string& cid,const string&wtime,string tableName=WORK_TABLE_NAME);
    static Work findWorkByCid(const string& cid,const string&wtime,string tableName=WORK_TABLE_NAME);
    static vector<Work> findWorkByCidOnly(const string& cid,string tableName=WORK_TABLE_NAME);
    //根据题目的Id返回该题目
    static Work findWorkByWid(const string& wid,string tableName=WORK_TABLE_NAME);

    //返回所有的作业
    static vector<Work> findAllWorks (string tableName=WORK_TABLE_NAME);
    //update a Record.
    static bool updateRecord(Work& w,string tableName=WORK_TABLE_NAME);
    //delete a Record.
    static bool deleteRecord(const string& wid,string tableName=WORK_TABLE_NAME);
};

#endif
