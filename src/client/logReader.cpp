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
 > FilePath: /zerone216/DCS-demo/src/client/logReader.cpp
 > CreateTime: 2019-12-23 19:47:32
 > ModifyTime: 2019-12-25 20:34:08
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */

#include "logReader.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <iomanip>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

//构造函数
LogReader::LogReader(const string& logFile,const string& loginsFile):m_logFile(logFile),m_loginsFile(loginsFile){}

//备份日志文件
void LogReader::backup(void)throw (BackupException)
{
	cout << "备份日志开始！" <<endl;

	//获取系统当前时间
    time_t now = time(0);
	struct tm* pt = localtime(&now);

	//转换成字符串的备份文件名
	//输出字符串流
	ostringstream oss;
	oss << m_logFile << "." << setw(4) << setfill('0') << pt->tm_year+1900  << setw(2) << pt->tm_mon+1
		<< setw(2) << pt->tm_mday << setw(2) << pt ->tm_hour << setw(2) << pt->tm_min << setw(2) << pt->tm_sec;

	//将字符串输出流转换成string
	m_backupFile = oss.str();

	//拼接执行指令
	string cmd("./backup.sh  ");
	cmd+= m_logFile;
	cmd+= " ";
	cmd+= m_backupFile;

	//执行指令
	int status = system(cmd.c_str());
	if(1 == WEXITSTATUS(status))
	{
      throw BackupException("清空日志文件出错！");
	}
	if(2 == WEXITSTATUS(status))
	{

      throw BackupException("拷贝日志文件出错！");
	}
 
	cout << "备份日志结束！" <<endl;
}

//读取上次未匹配的记录
void LogReader::readLoginsFile(void) throw(ReadException)
{
	cout << "读取上次未匹配记录开始！"<<endl;

	//打开上次未匹配的日志记录
	ifstream ifs(m_loginsFile.c_str(),ios::binary);
	LogRec rec={0};
	if(ifs)
	{
      while(ifs.read((char *)&rec,sizeof(rec)))
	  {
		  //将上次未匹配的记录保存到登入日志列表中
		  m_logins.push_back(rec);
	  }
	  if(!ifs.eof()) //未到文件尾
	  {
          throw ReadException("读取上次未匹配记录未到尾出错！");
	  }
	}

	ifs.close();

	cout << "上次未匹配记录的大小是："<< m_logins.size() << endl;
	cout << "读取上次未匹配记录结束！"<<endl;
}

//读取备份日志文件(本次要采集的日志数据)
void LogReader::readBackupFile(void) throw (ReadException)
{
    cout << "读取备份文件开始!" << endl;

	//打开备份文件
	ifstream ifs(m_backupFile.c_str(),ios::binary);
	if(!ifs)
	{
		throw ReadException("打开备份文件出错！");		
	}
	
	//按照指定的格式读取内容
	struct stat st;
	if(-1 == stat(m_backupFile.c_str(),&st))
	{
        throw ReadException("无法获取到备份文件的大小！");
	}

	//计算有多少条记录
	int records  = st.st_size / 372; //每条记录共372字节
    cout << "备份文件中的总记录数:"<< records <<endl;

	for(int i=0;i<records; i++)
	{
		LogRec log;
		//读取登录名
		ifs.read(log.logname,32);
		ifs.seekg(36,ios::cur);
		ifs.read((char *)&log.pid,4);
		//将网络大端模式字节序的int类型转换为本机的小端模式
		log.pid = ntohl(log.pid);

		//登录类型
		//short type;

		ifs.read((char *)&log.type,2);
		log.type = ntohs(log.type);

		//跳过6个字节
		ifs.seekg(6,ios::cur);

		//登录时间 
		ifs.read((char *)&log.logtime,4);
		log.logtime = ntohl(log.logtime);

		//登录IP
		ifs.seekg(30,ios::cur);
		ifs.read((char *)log.logip,257);

		//跳过1个字节
		ifs.seekg(1,ios::cur);

		//按照登录类型把数据放到不同的链表中，注意把.开头的用户过滤掉
		if(log.logname[0] != '.')
		{
          if(7 == log.type)
		  {
             //压入登入记录链表
			 m_logins.push_back(log); 
		  }
		  if(8 == log.type)
		  {
			  //压入登出记录链表
			  m_logouts.push_back(log);
		  }
		}
	}
	//关闭
	ifs.close();

	cout << "登入链表大小是：" << m_logins.size() << endl;
	cout << "登出链表大小是：" << m_logouts.size() << endl;

	cout << "读取备份文件结束!" << endl;	
}

//匹配登入/登出记录
void LogReader::match(void)
{
	cout << "匹配登入登出记录开始！"<< endl;

	//1.匹配登录数据
	for(list<LogRec>::iterator oit = m_logouts.begin(); oit != m_logouts.end();oit++)
	{
		//2.使用登出数据记录去登入链表中找匹配的记录
		for(list<LogRec>::iterator iit = m_logins.begin(); iit != m_logins.end();iit++)
		{ 
			//3.将匹配的记录组合成一条匹配记录放到匹配链表中，删除已经匹配的记录
			if(!strcmp(oit->logname,iit->logname) &&
					!strcmp(oit->logip,iit->logip) &&
					oit->pid==iit->pid)
			{
				MLogRec log = {"","",0,0,0,0};
				strcpy(log.logname,oit->logname);
				strcpy(log.logip,oit->logip);
				log.pid = oit->pid;
				log.logintime = iit->logtime;
				log.logouttime = oit->logtime;
				log.durations = log.logouttime - log.logintime;
				//放入匹配记录的链表中 
				m_logs.push_back(log);
				//删除已匹配过的登入的记录
				m_logins.erase(iit);
				//跳出内层循环
				break;
			}
		}
	}
	cout << "匹配的链表的大小是:" << m_logs.size() <<endl;
	cout << "匹配登入登出记录结束！"<< endl;
}

//保存未匹配的记录
void LogReader::saveLoginsFile(void) throw (SaveException)
{
	cout << "保存未匹配记录开始!"<<endl;

	//1.判断登入记录链表是否为空
	if(!m_logins.empty())
	{
		ofstream ofs(m_loginsFile.c_str(),ios::binary);
		if(!ofs)
		{
			throw SaveException("打开未匹配登入记录失败");
		}
		//2.判断登入链表是否为空
		while(!m_logins.empty())
		{
			//将链表中第一个元素写入文件中
			ofs.write((const char*)&m_logins.front(),sizeof(LogRec));

			//从链表中删除该记录
			m_logins.pop_front();
		}
		//3.关闭文件
		ofs.close();
	}
	cout << "保存未匹配记录结束！"<<endl;
}

//读取日志
list<MLogRec>& LogReader::readLog(void) throw(ReadException)
{
	cout << "读取日志文件开始！"<< endl;
	try
	{
		//1.备份日志
		backup();
		//2.读取上次未匹配的记录
		readLoginsFile();
		//3.读取备份文件
		readBackupFile();
		//4.匹配登入与登出记录
		match();
		//5.保存未匹配的记录
		saveLoginsFile();
	}
	catch (BackupException){
		throw BackupException("备份异常！");
	}
	catch (ReadException){
		throw ReadException("读取异常！");
	}
	catch (SaveException){
		throw SaveException("存储异常！");
	}
	catch(...)
	{
		throw ReadException("未知异常！");
	}
	cout <<"读取日志文件结束！"<< endl;
	return m_logs;
}
