#include <typeinfo>

#include "BinaryWriter.h"
#include "IOHandler.h"
#include "SerializableClassSimple.h"
#include "SerializableClassWithPointer.h"

BinaryWriter::BinaryWriter(IOHandler* ioHandler) : m_ioHandler(ioHandler), m_bufferSize(DEFAULT_BUFFER_SIZE), m_bufferPos(0)
{
	m_buffer = new char[m_bufferSize];
}

BinaryWriter::~BinaryWriter()
{
	flushBuffer();
	delete m_buffer;
	delete m_ioHandler;
}

bool BinaryWriter::reserveBuffer(size_t buffSize)
{
	size_t rest = m_bufferSize - m_bufferPos - 1;
	if (buffSize < rest)
	{
		return true;
	}

	flushBuffer();
	if (buffSize < m_bufferSize)
	{
		return true;
	}

	//TODO: enlarge buffer twice - up to some limit

	return false;
}

bool BinaryWriter::write(Serializable* src)
{
	//structure: total size, class name size, class name, instance data
	//structure has to correspond with the one in BinaryReader::readNext()

	string typeName(typeid(*src).name());
	size_t nameSize = typeName.size() + sizeof(char);
	size_t srcBinSize = src->getBinarySize();

	size_t sizeNeeded = (sizeof(size_t) << 1) + nameSize + srcBinSize;
	if (reserveBuffer(sizeNeeded))
	{
		std::memcpy(&m_buffer[m_bufferPos], &sizeNeeded, sizeof(size_t));
		m_bufferPos += sizeof(size_t);
		
		std::memcpy(&m_buffer[m_bufferPos], &nameSize, sizeof(size_t));
		m_bufferPos += sizeof(size_t);

		std::memcpy(&m_buffer[m_bufferPos], typeName.c_str() + '\0', nameSize);
		m_bufferPos += nameSize;
		
		src->write(&m_buffer[m_bufferPos]);
		m_bufferPos += srcBinSize;

		flushBuffer();
		return true;
	}
	
	return false;
}

void BinaryWriter::flushBuffer()
{
	m_ioHandler->saveData(m_buffer, m_bufferPos);
	m_bufferPos = 0;
}