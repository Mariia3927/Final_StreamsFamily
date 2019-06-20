// ConsoleAppForStreams.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

int main()
{
	FileStream fileOut("Test.txt", IBaseStream::StreamType::out);

	 std::string buf;
	 MemoryStream memoryOut(buf, IBaseStream::StreamType::out);

	 ConsoleStream consoleOut(IBaseStream::StreamType::out);

	 fileOut.AddStream(&memoryOut);
	 fileOut.AddStream(&consoleOut);

	 std::string tmp = "012345678901234567890123456789";
	 fileOut.Write(tmp.c_str(), tmp.length());

	 memoryOut.Show();



	/*FileStream fileIn("Test.txt", IBaseStream::StreamType::in);

	std::string buf = "012345678901234567890123456789";
	MemoryStream memoryIn(buf, IBaseStream::StreamType::in);

	ConsoleStream consoleIn(IBaseStream::StreamType::in);

	fileIn.AddStream(&memoryIn);
	fileIn.AddStream(&consoleIn);

	char tmp[bufferLength] = "";
	fileIn.Read(tmp, bufferLength);

	memoryIn.Show();*/

}

