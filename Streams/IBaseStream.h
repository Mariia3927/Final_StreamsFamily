#pragma once
#include "stdafx.h"



class IBaseStream
{
public:
	virtual std::size_t Write(const char* buffer, int numberOfBytes) { return 0; };
	virtual std::size_t Read(char* buffer, int numberOfBytes) { return 0; };

	void CheckParameters(const char* buffer, int numberOfBytes);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class IFileStream : public IBaseStream
{
public:
	IFileStream(std::string fileName);
	
	std::size_t Read(char* buffer, int numberOfBytes) override;

private:
	std::fstream m_object;
};


class OFileStream : public IBaseStream
{
public:
	OFileStream(std::string fileName);

	std::size_t Write(const char* buffer, int numberOfBytes) override;

private:
	std::fstream m_object;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class IMemoryStream : public IBaseStream
{
public:
	IMemoryStream(std::vector<char> buffer);

	std::size_t Read(char* buffer, int numberOfBytes) override;

private:
	std::vector<char> m_buffer{};
};


class OMemoryStream : public IBaseStream
{
public:
	OMemoryStream(std::vector<char> buffer);

	std::size_t Write(const char* buffer, int numberOfBytes) override;

	void Show();

private:
	std::vector<char> m_buffer;
};




class IConsoleStream : public IBaseStream
{
public:
	std::size_t Read(char* buffer, int numberOfBytes) override;
};


class OConsoleStream : public IBaseStream
{
public:
	std::size_t Write(const char* buffer, int numberOfBytes) override;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class IComposingStream : public IBaseStream
{
public:
	void AddStream(IBaseStream* object);
	void RemoveStream(IBaseStream* object);
	std::size_t Read(char* buffer, int numberOfBytes) override;

private:
	std::vector<IBaseStream*> m_streams{};
};

class OComposingStream : public IBaseStream
{
public:
	void AddStream(IBaseStream* object);
	void RemoveStream(IBaseStream* object);
	std::size_t Write(const char* buffer, int numberOfBytes) override;

private:
	std::vector<IBaseStream*> m_streams{};
};