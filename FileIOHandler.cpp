#include <fstream>

#include "FileIOHandler.h"

using namespace std;

FileIOHandler::FileIOHandler(const char* fileName) : m_fileName(fileName), m_readIdx(0){}

FileIOHandler::~FileIOHandler()
{
	delete m_fileName;
}

size_t FileIOHandler::loadData(char* dst, const int amount)
{
    ifstream file(m_fileName, ios::in | ios::binary);
    if (file.is_open())
    {
		file.seekg(0, ios::end);
		int buffSize = static_cast<int>(file.tellg());
		buffSize -= m_readIdx;
		buffSize = (amount < buffSize) ? amount : buffSize;

		file.seekg(m_readIdx, ios::beg);
        file.read(dst, buffSize);
		file.close();

		m_readIdx += buffSize;

		return buffSize;
    }

	return 0;
}

void FileIOHandler::saveData(char* src, const int amount)
{
	ofstream file(m_fileName, ios::out | ios::app | ios::binary);
	if (file.is_open())
	{
		file.write(src, amount);
		file.close();
	}
}