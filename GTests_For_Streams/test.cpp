#include "pch.h"



TEST(add_nullptr_instead_of_correct_stream_object, AddStream)
{
	FileStream fStream("Test.txt", IBaseStream::StreamType::out);
	EXPECT_EQ(false, fStream.AddStream(nullptr));
}

TEST(add_object_with_not_equal_type, AddStream)
{
	FileStream fStream("Test.txt", IBaseStream::StreamType::out);
	ConsoleStream cStream(IBaseStream::StreamType::in);
	EXPECT_EQ(false, fStream.AddStream(&cStream));
}

TEST(add_object_with_equal_type, AddStream)
{
	FileStream fStream("Test.txt", IBaseStream::StreamType::out);
	ConsoleStream cStream(IBaseStream::StreamType::out);
	EXPECT_EQ(true, fStream.AddStream(&cStream));
}

TEST(remove_nullptr, RemoveStream)
{
	FileStream fStream("Test.txt", IBaseStream::StreamType::out);
	ConsoleStream cStream(IBaseStream::StreamType::in);
	fStream.AddStream(&cStream);

	EXPECT_EQ(false, fStream.RemoveStream(nullptr));
}

TEST(remove_previous_added_object, RemoveStream)
{
	FileStream fStream("Test.txt", IBaseStream::StreamType::out);
	ConsoleStream cStream(IBaseStream::StreamType::in);
	fStream.AddStream(&cStream);

	EXPECT_EQ(true, fStream.RemoveStream(&cStream));
}

