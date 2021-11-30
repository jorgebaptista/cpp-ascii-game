#include "FileSystem.h"

FileSystem::FileSystem()
{

}

FileSystem& FileSystem::instance()
{
    static FileSystem *instance = new FileSystem();  // guaranteed to be destroyed
	// instantiated on first use

    return *instance;
}

std::string FileSystem::ReadDrawing(std::string fileName)
{
	std::ifstream t(fileName); // create ifstream variable to read file
	std::stringstream buffer; // create a buffer to pass the contents of the file inside
	buffer << t.rdbuf(); // pass the contents of the file inside buffer

	std::string drawing = buffer.str(); // convert buffer to string

    return drawing; // return the drawing (string)
}
