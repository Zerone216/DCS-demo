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
 > FilePath: /zerone216/DCS-demo/src/server/storeThread.cpp
 > CreateTime: 2019-12-23 22:14:48
 > ModifyTime: 2019-12-24 23:03:05
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */

#include "storeThread.h"
#include "data.h"
#include "logBuffer.h"

/*
   private:
   LogDao& m_dao;//数据访问类
 */
//构造
StoreThread::StoreThread(LogDao& dao):m_dao(dao){}

//真正的run函数
void StoreThread::run(void)
{
	//不断从缓冲区中取出数据放到数据库中
	MLogRec log;
	for(;;)
	{
		//g_LogBuffer.operator>>(log);  运算符重载
		g_LogBuffer >> log; //从缓冲区中取数据
		try
		{
			m_dao.insert(log);
		}
		catch(DBException ex)
		{
			cout << ex.what() <<endl;
		}
	}
}
