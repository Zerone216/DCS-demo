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
 > FilePath: /github/zerone216/DMS-demo/src/server/logThread.cpp
 > CreateTime: 2017-10-14 09:12:55
 > ModifyTime: 2019-12-18 23:00:57
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */


#include "logThread.h"
#include "pthread.h"
#include <iostream>
using namespace std;

//启动线程
void LogThread::start(void)throw (ThreadException)
{
	cout << "启动线程开始"<<endl;
	//创建一个新的线程，将this指针传给线程处理函数，在线程处理函数真正调用run 
	pthread_t tid;
	if(pthread_create(&tid,0,run,this)) //pthread_create()函数参数中没有this，
		//所以调用时封装了一个static的run ，并将当前类作为实参传给了形参
	{
		throw ThreadException("启动线线程失败");
	}
	cout << "启动线程结束"<<endl;
}
void* LogThread::run(void* arg) //静态的run 
{
	//分离当前线程
	pthread_detach(pthread_self());
	//调真正的run函数，在实现类中进行了覆盖
	static_cast<LogThread*>(arg)->run();//将arg转换为当前类类型的指针

	return NULL;
}
