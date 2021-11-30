#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

class FileSystem
{
public:
	static FileSystem& instance(); // singleton instance of FileSystem
	std::string ReadDrawing(std::string fileName); // read drawing from a file

private:
	FileSystem(); // constructor
};