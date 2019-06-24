// ConsoleAppForStreams.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

int main()
{
	try
	{
		 OFileStream fileOut("Test.txt");

		 std::vector<char> buf;
		 OMemoryStream memoryOut(buf);
		 OConsoleStream consoleOut;

		 std::string tmp = "012345678901234567890123456789";
		 fileOut.Write(tmp.c_str(), tmp.length());
		 memoryOut.Write(tmp.c_str(), tmp.length());
		 memoryOut.Show();

		consoleOut.Write(tmp.c_str(), tmp.length());
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}

	 



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

