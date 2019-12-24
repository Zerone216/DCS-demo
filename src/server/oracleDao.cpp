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
 > FilePath: /zerone216/DCS-demo/src/server/oracleDao.cpp
 > CreateTime: 2019-12-23 21:13:52
 > ModifyTime: 2019-12-24 22:59:07
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include "oracleDao.h"

using namespace std;

//构造函数
OracleDao::OracleDao(const string& username,const string& password)
{
	cout <<"连接数据库开始"<<endl;

	cout <<"连接数据库结束"<<endl;
}

//析构函数
OracleDao::~OracleDao(void)
{
	cout <<"关闭数据库开始"<<endl;

	cout <<"关闭数据库结束"<<endl;
}

//插入日志数据
void OracleDao::insert(const MLogRec& log) throw (DBException)
{	
	cout<<"插入数据开始"<<endl;

	cout<<"插入数据结束"<<endl;
}
