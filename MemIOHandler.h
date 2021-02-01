#ifndef MEM_IO_HANDLER_H
#define MEM_IO_HANDLER_H

#include "IOHandler.h"

/**
* Class for read/write binary files implements IOHandler to be compatible with BinaryReader/BinaryWriter
 */
class MemIOHandler : public IOHandler
{
private:
	static constexpr const size_t DEFAULT_BUFFER_SIZE = 1024;

	int m_bufferSize;			//current size of buffer
	const char* m_buffer;		//buffer to hold it all
	int m_readIdx;				//next position to read from
	int m_writeIdx;				//next position to write from

public:
	MemIOHandler();
	~MemIOHandler();
	size_t loadData(char* dst, const int amount) override;
	void saveData(char* src, const int amount) override;
};

#endif //MEM_IO_HANDLER_H