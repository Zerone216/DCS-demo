/*
 > Declaration: 
 >  Copyright (c) 2009-2019 Zhang Sheng <zerone216@163.com>
 >  See my homepage: https://zerone216.cn
 > 
 >  This program is free software; you can redistribute it and/or modify it under 
 >  the terms of the GNU General Public License as published by the Free Software 
 >  Foundation, either version 2 or any later version.
 >  
 >  Redistribution and use in source and binary forms, with or without modification,
 >  are permitted provided that the following conditions are met: 
 >  
 >  1. Redistributions of source code must retain the above copyright notice, this
 >  list of conditions and the following disclaimer.
 >  
 >  2. Redistributions in binary form must reproduce the above copyright notice,
 >  this list of conditions and the following disclaimer in the documentation and/or 
 >  other materials provided with the distribution. 
 > 
 >  This program is distributed in the hope that it will be useful, but WITHOUT ANY 
 >  WARRANTY; without even the implied warranty of MERCHANTABILITY or ITNESS FOR A 
 >  PARTICULAR PURPOSE. See the GNU General Public License for more details. A copy 
 >  of the GNU General Public License is available at: 
 >  http://www.fsf.org/licensing/licenses 
 >  
 >  All manufacturing, reproduction, use, and sales rights pertaining to this subject 
 >  matter are governed bythe license agreement. The recipient of this software 
 >  implicitly accepts the terms of the license.
 > 
 > Author: Zhang Sheng
 > FilePath: /zerone216/DCS-demo/src/client/logReader.h
 > CreateTime: 2019-12-23 20:06:35
 > ModifyTime: 2019-12-25 20:32:14
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */


#ifndef __LOGREADER_H__
#define __LOGREADER_H__

#include <string>
#include "data.h"
#include "except.h"
#include <list>

using namespace std;

class LogReader
{

	// 成员变量
	private:
		string m_logFile;//日志文件名
		string m_loginsFile;//剩余的登入记录
		string m_backupFile;//备份文件名
		list<LogRec> m_logins;//所有登入记录 
		list<LogRec> m_logouts;//所有登出记录 
		list<MLogRec> m_logs;//所有匹配记录

	//私有成员函数
	private:
		//备份日志文件
		void backup(void)throw (BackupException);
		//读取上次未匹配的记录
		void readLoginsFile(void) throw(ReadException);
		//读取备份日志文件
		void readBackupFile(void) throw (ReadException);
		//匹配登入/登出记录
		void match(void);
		//保存未匹配的登入记录
		void saveLoginsFile(void) throw (SaveException);

	public:
		//构造函数
		LogReader(const string& logFile,const string& loginsFile);
		//读取日志
		list<MLogRec>&  readLog(void) throw(ReadException);
};

#endif
