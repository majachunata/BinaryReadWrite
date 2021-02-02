#ifndef BINARY_READER_H
#define BINARY_READER_H

#include <string>
#include <functional>
#include <map>

class IOHandler;
class Serializable;

/**
* Class returning Serializable instances from their binarized form
 */
class BinaryReader
{
private:
	static constexpr const size_t DEFAULT_BUFFER_SIZE = 1024;
	
	//map to get new class instance based on class name. Each Serializable has to be inserted to map manually!
	typedef std::map<std::string, std::function<Serializable * ()>> serializableMapType;
	static serializableMapType serializableMap;		

	IOHandler* m_ioHandler;		//handler class to take care of binarized data

	char* m_buffer;				//internal buffer to save binarized instances
	size_t m_bufferSize;		//current buffer size
	int m_bufferPos;			//current buffer index to read from

	/**
	 * Create new instance of Serializable class according to class name given
	 * @param className class name as defined by typeid. Has to be Serializable child
	 * @retval new instance of given Serializable class or nullptr while theres no such class in serializableMap
	 */
	Serializable* getInstance(const char* className);

	/**
	 * Move unused part of buffer at its start and append new data read by IOHandler to fill the rest of buffer
	 */
	void reloadBuffer();

public:
	BinaryReader(IOHandler* ioHandler);
	~BinaryReader();

	/**
	 * Reads one instance of Serializable class from buffer and move buffer pointer to the next
	 * @retval instance of Serializable class filled by values from its binary representation on buffer
	 */
	Serializable* readNext();
};

#endif //BINARY_READER_H