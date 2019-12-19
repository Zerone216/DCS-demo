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
 > FilePath: /github/zerone216/DMS-demo/src/server/data.h
 > CreateTime: 2017-10-14 08:54:16
 > ModifyTime: 2019-12-18 22:25:37
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */

/*
 自定义登录记录和匹配记录类型
 */
#ifndef __DATA_H__
#define __DATA_H__

#include <iostream>
#include <unistd.h>

using namespace std;

//匹配记录
typedef struct MLogRec
{
	char logname [32];
	char logip[257];
	pid_t pid;
	long logintime;//登录时刻
	long logouttime;//登出时刻
	long durations;//在线时长

	//定义输出运算符重载(cout << MLogRec << endl;)
	friend ostream& operator << (ostream& os,const MLogRec& log)
	{
      return os << log.logname <<"," << log.logip << "," <<
		  log.pid << "," << log.logintime << "," << log.logouttime << "," << log.durations;

    }

}MLogRec;

#endif /* __DATA_H__ */