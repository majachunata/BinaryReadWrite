#include "MemIOHandler.h"

using namespace std;

MemIOHandler::MemIOHandler() : m_bufferSize(DEFAULT_BUFFER_SIZE), m_readIdx(0), m_writeIdx(0)
{
	m_buffer = new char[DEFAULT_BUFFER_SIZE];
}

MemIOHandler::~MemIOHandler()
{
	delete m_buffer;
}

size_t MemIOHandler::loadData(char* dst, const int amount)
{
	//copy min(amount, rest) size of buffer from readIdx
	//shift readIdx
	//return real amount copied
	return 0;
}

void MemIOHandler::saveData(char* src, const int amount)
{
	//check buffer size left
	//enlarge it twice until there is enough space
	//copy data to writeIdx
	//shift writeIdx
}