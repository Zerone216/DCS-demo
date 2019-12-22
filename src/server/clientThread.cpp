/*
 > Declaration: 
 >  Copyright (c) 2009-2019 Zhang Sheng <zerone216@163.com>
 >  See my homepage: http://www.zerone216.top:8080
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
 > FilePath: /github/zerone216/DCS-demo/src/server/clientThread.cpp
 > CreateTime: 2019-12-22 22:46:20
 > ModifyTime: 2019-12-22 23:17:22
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */


#include "clientThread.h"
#include "logBuffer.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

/*
   private:
   int m_connfd;//客户端socket套节字
 */

//构造函数
ClientThread::ClientThread(int connfd):m_connfd(connfd){}

void ClientThread::run(void)throw(ThreadException){
	//不断将收到客户端的数据放入缓冲区中
	MLogRec log;
	unsigned long long logs;

	for(logs=0;;logs++)
	{
		size_t rlen; //表示已经收到的字节
		//len 表示总的数据包字节大小

		//每次接收完一个完整的MLogRec
		for(size_t len=sizeof(log);len;len-=rlen)
		{
			if((rlen = recv(m_connfd,(char*)&log+(sizeof(log)-len),len,0)) <= 0 ) //0表示客户端断线
			{
				goto escape;
			}
		}

		//由网络字节序转换为本机字节序(大端-->小端)
		log.pid = ntohl(log.pid);
		log.logintime  = ntohl(log.logintime);
		log.logouttime = ntohl(log.logouttime);
		log.durations  = ntohl(log.durations);

		//g_LogBuffer.operator<<(log)
		//将日志压入缓冲池(匹配记录链表)
		g_LogBuffer << log;
	}

escape:
	cout << "接收到" << logs << "条日志记录" << endl;
	//关闭socket
	close(m_connfd);
	//释放当前客户端线程
	delete this;
}
