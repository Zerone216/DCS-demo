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
 > FilePath: /github/zerone216/DMS-demo/src/server/except.h
 > CreateTime: 2017-10-14 08:51:16
 > ModifyTime: 2019-12-18 22:58:03
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */

/*服务器端各种异常的声明*/
#ifndef __EXCEPT_H__
#define __EXCEPT_H__

#include <exception>
#include <string>

using namespace std;

//基类
class ServerException:public exception
{
	private:
		string m_msg;//存放异常信息
	public:
		ServerException (void):m_msg("服务器异常！"){};
		ServerException(const string& msg):m_msg("服务器异常！")
	{
		m_msg += msg;
		m_msg +="!";
	}
		//析构函数
		~ServerException (void) throw(){}

		//what
		const char * what(void) const throw()
		{
			return m_msg.c_str();
		}
};

//数据库连接异常类
class DBException:public ServerException
{
	public:
		DBException(void):ServerException("数据库错误！"){}
		DBException(const string& msg):ServerException(msg){}
};

//Socket异常类
class SocketException:public ServerException
{
	public:
		SocketException(void):ServerException("Socket 错误！"){}
		SocketException(const string& msg):ServerException(msg){}
};


//线程异常类
class ThreadException:public ServerException
{
	public:
		ThreadException(void):ServerException("线程执行错误！"){}
		ThreadException(const string& msg):ServerException(msg){}
};

#endif
