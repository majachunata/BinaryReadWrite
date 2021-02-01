#ifndef FILE_IO_HANDLER_H
#define FILE_IO_HANDLER_H

#include "IOHandler.h"

/**
* Class for read/write binary files implements IOHandler to be compatible with BinaryReader/BinaryWriter
 */
class FileIOHandler : public IOHandler
{
private:
	const char* m_fileName;
	int m_readIdx;			//next position to read from

public:
	FileIOHandler(const char* fileName);
	~FileIOHandler();
	size_t loadData(char* dst, const int amount) override;
	void saveData(char* src, const int amount) override;
};

#endif //FILE_IO_HANDLER_H