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
 > FilePath: /zerone216/DCS-demo/src/server/logBuffer.h
 > CreateTime: 2019-12-23 19:44:13
 > ModifyTime: 2019-12-24 22:58:36
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */

#ifndef __LOGBUFFER_H__
#define __LOGBUFFER_H__

#include "data.h"

#include <list>
#include <pthread.h>


class LogBuffer
{
	private:
		pthread_mutex_t m_mutex;//互斥量
		pthread_cond_t m_cond;//条件变更
		list <MLogRec> m_logs;//缓冲区链表(客户端上传到服务器的日志数据)

	public:
		LogBuffer(void);

		//压入匹配日志记录到链表中
		LogBuffer& operator << (const MLogRec& log);

		//从链表中取得匹配的日志记录 
		LogBuffer& operator  >> (MLogRec& log);

};

//主要用途就是为方便其它调用模块使用
extern LogBuffer g_LogBuffer;
#endif
