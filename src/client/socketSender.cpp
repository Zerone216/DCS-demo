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
 > FilePath: /zerone216/DCS-demo/src/client/socketSender.cpp
 > CreateTime: 2019-12-23 20:34:17
 > ModifyTime: 2019-12-25 20:47:46
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */

#include "socketSender.h"
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//构造函数重载
SocketSender::SocketSender (const string& ip,short port,const string& failFile):
	m_ip(ip),m_port(port),m_failFile(failFile){}

//虚函数的重写版本
void SocketSender::sendLog(list<MLogRec>& logs)throw (SendException)
{
	cout<<"发送日志记录开始..."<<endl;
	try
	{
		//1.读取发送失败日志
		try
		{
			readFailFile(logs);
		}
		catch(ReadException)
		{
			cout << "读取上次发送失败的日志出错！"<< endl;
		}
		//2.连接远程服务器
		connectServer();
		//3.发送日志
		sendData(logs);
	}
	catch(SocketException)
	{
       //将未来急发送的数据保存
		saveFailFile(logs);
		throw SocketException("连接服务器异常！");			
	}
	catch(SendException)
	{
		//将发送失败的数据保存
		saveFailFile(logs);
		throw SendException("发送数据中异常！");
	}
	cout<<"发送日志记录结束!"<<endl;
}

//连接服务器
void SocketSender::connectServer(void) throw (SocketException)
{
	cout<<"连接服务器开始..."<<endl;
	//1.创建一个socket
	m_sockfd = socket (AF_INET,SOCK_STREAM,0); 

	if(-1 == m_sockfd)
	{
      throw SocketException("创建客户端socket失败！");
	}

	//2.准备通信地址
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);//将本机小端模式端口转成网络大端字节序
	addr.sin_addr.s_addr  = inet_addr(m_ip.c_str());//转换ip地址

	//3.连接服务器
	if(-1 == connect(m_sockfd,(sockaddr*)&addr,sizeof(addr)))
	{
		throw SocketException("连接服务器失败！");
	}
	cout<<"连接服务器结束!"<<endl;

}

//读取上次发送失败日志
void SocketSender::readFailFile(list<MLogRec>& log) throw (ReadException)
{
	cout<<"读取发送失败的日志开始..."<<endl;
	ifstream ifs(m_failFile.c_str(),ios::binary);
	if(!ifs)
	{
		throw ReadException("打开上次发送失败的日志文件出错！");
	}

	MLogRec mlog;
	while(ifs.read((char *)&mlog,sizeof(mlog)))
	{
       log.push_front(mlog);
	}

	//是否正确地读到文件尾
	if(!ifs.eof())
	{
       throw ReadException("读取上次发送失败的日志出错");
	}

	//关闭
	ifs.close();
	//删除文件
	unlink(m_failFile.c_str());

	cout<<"读取发送失败的日志结束!"<<endl;

}

//发送日志
void SocketSender::sendData(list<MLogRec>& log) throw (SendException)
{
	cout<<"发送日志开始..."<<endl;
    while(!log.empty())
	{
		MLogRec mlog = log.front();
		//将本地要发送到网络上的数据作一个转换：小端-->大端
		mlog.pid  = htonl(mlog.pid);
		mlog.logintime = htonl(mlog.logintime);
		mlog.logouttime = htonl(mlog.logouttime);
		mlog.durations = htonl(mlog.durations);

		//发送数据
		if(-1 == send(m_sockfd,&mlog,sizeof(mlog),0))
		{
			close(m_sockfd);
			throw SendException("发送数据失败！");
		}

		//将已经成功发送的数据从链表中弹出
		log.pop_front();
	}
	//关闭socket
	close(m_sockfd);
	cout<<"发送日志结束!"<<endl;
}

//保存发送失败的日志
void SocketSender::saveFailFile(list<MLogRec>& log) throw (SaveException)
{
	cout<<"保存发送失败日志开始..."<<endl;
	if(!log.empty())
	{
		ofstream ofs(m_failFile.c_str(),ios::binary);
		if(!ofs)
		{
			throw SaveException("打开发送失败的日志文件出错");
		}
        while(!log.empty())
		{
			ofs.write((char *)&log.front(),sizeof(MLogRec));
			//删除已经写入过的发送失败的日志
			log.pop_front();			
		}
		//关闭
		ofs.close();
	}
	cout<<"保存发送失败日志结束!"<<endl;
}
