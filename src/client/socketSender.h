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
 > FilePath: /zerone216/DCS-demo/src/client/socketSender.h
 > CreateTime: 2019-12-23 20:12:47
 > ModifyTime: 2019-12-25 20:45:12
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */

#ifndef __SOCKETSENDER_H__
#define __SOCKETSENDER_H__

#include "logSender.h"

/*日志发送器logSender接口的子类:抽象类*/
//套接字发送

class SocketSender:public LogSender
{
	private:
		string m_ip;//ip地址
		short m_port;//端口
		string m_failFile;//失败日志文件
		int m_sockfd;//客户端socket 套接字

	public:
		//构造函数重载
		SocketSender(const string& ip,short port,const string& failFile);

		//虚函数的覆盖版本
	    void sendLog(list<MLogRec>& logs)throw (SendException);
		

	private:
		//连接服务器
		void connectServer(void) throw(SocketException);
        //读取失败文件
		void readFailFile(list<MLogRec>& log) throw(ReadException);
		//发送日志
		void sendData(list<MLogRec>& log) throw(SendException);
		//保存失败的日志文件
		void saveFailFile(list<MLogRec>& log) throw(SaveException);

};

#endif
