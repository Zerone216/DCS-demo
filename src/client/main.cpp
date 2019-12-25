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
 > FilePath: /zerone216/DCS-demo/src/client/main.cpp
 > CreateTime: 2019-12-23 21:23:18
 > ModifyTime: 2019-12-25 20:49:59
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */


#include <iostream>
#include "logReader.h"
#include "socketSender.h"
#include "consoleSender.h"
#include "client.h"
#include <cstdlib>
#include <cstring>

/*
   客户端应用程序入口函数
 */
int main(int argc,char* argv[])
{
	try
	{
		// 重置测试日志文件
		string cmd("./reset.sh");
		system(cmd.c_str());

		//初始化日志文件的读取器
		LogReader reader("./wtmpx","logins.dat");

		//日志发送"
		SocketSender sender("127.0.0.1",8888,"./fail.dat");

		Client client(reader,sender);

		client.dataMine();

	}
	catch(ClientException ex)
	{
		cout << ex.what() << endl;
		return -1;
	}
    
	return 0;
}
