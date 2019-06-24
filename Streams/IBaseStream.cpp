#include "stdafx.h"
#include "IBaseStream.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IBaseStream::CheckParameters(const char* buffer, int numberOfBytes)
{
	if (numberOfBytes <= 0)
	{
		throw(std::exception("Error! The number of bytes for reading / writing cannot be less than or equal zero!"));
	}
	if (!buffer)
	{
		throw(std::exception("Error! The buffer is incorrect!"));
	}
}

IFileStream::IFileStream(std::string fileName)
{
	m_object.open(fileName.c_str(), std::ios::in);

	if (!m_object)
	{
		throw(std::exception("Error! The filestream object hasn't been created successfully!"));
	}
}

size_t IFileStream::Read(char* buffer, int numberOfBytes)
{
	CheckParameters(buffer, numberOfBytes);

	m_object.read(buffer, numberOfBytes);
	
	return numberOfBytes;
}

OFileStream::OFileStream(std::string fileName)
{
	m_object.open(fileName.c_str(), std::ios::out);

	if (!m_object)
	{
		throw(std::exception("Error! The filestream object hasn't been created successfully!"));
	}
}

size_t OFileStream::Write(const char* buffer, int numberOfBytes)
{
	CheckParameters(buffer, numberOfBytes);

	m_object.write(buffer, numberOfBytes);

	return numberOfBytes;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMemoryStream::IMemoryStream(std::vector<char> buffer) : m_buffer(buffer) { }

size_t IMemoryStream::Read(char* buffer, int numberOfBytes)
{
	CheckParameters(buffer, numberOfBytes);

	for (int i = 0; i < numberOfBytes; i++)
	{
		buffer[i] = m_buffer[i];
	}

	return numberOfBytes;
}




OMemoryStream::OMemoryStream(std::vector<char> buffer) : m_buffer(buffer) { }

size_t OMemoryStream::Write(const char* buffer, int numberOfBytes)
{
	CheckParameters(buffer, numberOfBytes);

	for (int i = 0; i < m_buffer.size(); i++)
	{
		m_buffer.push_back(buffer[i]);
	}

	return numberOfBytes;
}

void OMemoryStream::Show()
{
	std::cout << "Memory buffer:\n ";
	for (int i = 0; i < m_buffer.size(); i++)
	{
		std::cout << m_buffer[i];
	}
	std::cout << std::endl;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

size_t OConsoleStream::Write(const char* buffer, int numberOfBytes)
{
	CheckParameters(buffer, numberOfBytes);

	std::cout.write(buffer, numberOfBytes);
	std::cout << std::endl;

	return numberOfBytes;
}

size_t IConsoleStream::Read(char* buffer, int numberOfBytes)
{
	CheckParameters(buffer, numberOfBytes);

	std::cout << "Enter anything to the console:\n";
	std::cin.read(buffer, numberOfBytes);

	return std::cin.gcount();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IComposingStream::AddStream(IBaseStream* object)
{
	if (!object)
	{
		throw(std::exception("Error! The stream object is incorrect!"));
	}

	m_streams.push_back(object);
}

void IComposingStream::RemoveStream(IBaseStream* object)
{
	if (!object)
	{
		throw(std::exception("Error! The stream object is incorrect!"));
	}

	std::remove(m_streams.begin(), m_streams.end(), object);
}

size_t IComposingStream::Read(char* buffer, int numberOfBytes)
{
	for (unsigned int i = 0; i < m_streams.size(); i++)
	{
		for (unsigned int j = 0; j < numberOfBytes; j++)
		{
			buffer[j] = '\0';
		}

		m_streams[i]->Read(buffer, numberOfBytes);
	}

	return m_streams.size() * numberOfBytes;
}




void OComposingStream::AddStream(IBaseStream* object)
{
	if (!object)
	{
		throw(std::exception("Error! The stream object is incorrect!"));
	}

	m_streams.push_back(object);
}

void OComposingStream::RemoveStream(IBaseStream* object)
{
	if (!object)
	{
		throw(std::exception("Error! The stream object is incorrect!"));
	}

	std::remove(m_streams.begin(), m_streams.end(), object);
}

size_t OComposingStream::Write(const char* buffer, int numberOfBytes)
{
	for (unsigned int i = 0; i < m_streams.size(); i++)
	{
		m_streams[i]->Write(buffer, numberOfBytes);
	}

	return m_streams.size() * numberOfBytes;
}



