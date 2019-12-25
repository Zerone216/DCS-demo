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
 > FilePath: /zerone216/DCS-demo/src/client/except.h
 > CreateTime: 2019-12-23 18:34:42
 > ModifyTime: 2019-12-25 20:27:13
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */

/*定义各种类型的异常*/
#ifndef __EXCEPT_H__
#define __EXCEPT_H__

#include <exception>
#include <string>

using namespace std;

class ClientException:public exception
{
	private:
		string m_msg;//存放异常信息

	public:
		//构造
		ClientException (void):m_msg("客户机异常！"){}
		//构造重载
		ClientException (const string& msg):m_msg("客户机异常")
		{
			m_msg += msg;
			m_msg +="!";
		}
		//析构函数
		~ClientException (void) throw(){}

		//what 
		const char* what(void) const throw()
		{
			// 返回C风格的字符串
			return m_msg.c_str();
		}
};

//Backup异常类
class BackupException:public ClientException
{
	public:
		BackupException (void):ClientException("备份错误！"){}
		//有参构造函数
		BackupException (const string& msg):ClientException(msg){} 
};

//Socket异常类
class SocketException:public ClientException
{
	public:
		SocketException (void):ClientException("Socket错误！"){}
		SocketException (const string& msg):ClientException(msg){} 
};

//Read异常类
class ReadException:public ClientException
{
	public:
		ReadException (void):ClientException("读取错误！"){}
		ReadException (const string& msg):ClientException(msg){} 
};

//Save异常类
class SaveException:public ClientException
{
	public:
		SaveException (void):ClientException("保存错误！"){}
		SaveException (const string& msg):ClientException(msg){} 
};

//Send异常类 
class SendException:public ClientException
{
	public:
		SendException (void):ClientException("发送错误！"){}
		SendException (const string& msg):ClientException(msg){} 
};

#endif