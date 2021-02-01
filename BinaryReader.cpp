#include <typeinfo>

#include "BinaryReader.h"
#include "IOHandler.h"
#include "SerializableClassSimple.h"
#include "SerializableClassWithPointer.h"

#define DESER_CLASS_NAME_STRING(className)				string(typeid(className).name())
#define DESER_CLASS_INSTANCE_GENERATOR(className)		[](){return new className();}
#define DESER_REGISTER_SERIALIZABLE_CLASS(className)	{DESER_CLASS_NAME_STRING(className), DESER_CLASS_INSTANCE_GENERATOR(className)}

BinaryReader::serializableMapType BinaryReader::serializableMap =
{
	DESER_REGISTER_SERIALIZABLE_CLASS(SerializableClassSimple),
	DESER_REGISTER_SERIALIZABLE_CLASS(SerializableClassWithPointer)
};

BinaryReader::BinaryReader(IOHandler* ioHandler) : m_ioHandler(ioHandler), m_bufferSize(0), m_bufferPos(0)
{
	m_buffer = new char[DEFAULT_BUFFER_SIZE];
}

BinaryReader::~BinaryReader()
{
	delete m_buffer;
	delete m_ioHandler;
}

Serializable* BinaryReader::getInstance(const char* className)
{
	try
	{
		auto constructFunct = serializableMap.at(string(className));
		return constructFunct();
	}
	catch (std::out_of_range outofrange)
	{
		return nullptr;
	}
}

Serializable* BinaryReader::readNext()
{
	//TODO: unknown data exception, reload fail
	//structure: total size, class name size, class name, instance data
	//structure has to correspond with the one in BinaryWriter::write()
	int sizeNeeded = sizeof(size_t) << 1;
	int rest = m_bufferSize - m_bufferPos;
	if (rest < sizeNeeded)
	{
		reloadBuffer();
		if (m_bufferSize == 0)
		{
			return nullptr;
		}
		rest = m_bufferSize - m_bufferPos;
	}
	
	sizeNeeded = *reinterpret_cast<int*>(&m_buffer[m_bufferPos]);
	if (rest < sizeNeeded)
	{
		reloadBuffer();
		if (m_bufferSize == 0)
		{
			return nullptr;
		}
		rest = m_bufferSize - m_bufferPos;
	}

	size_t newBufferPos = m_bufferPos + sizeof(size_t);
	size_t classNameSize = *reinterpret_cast<size_t*>(&m_buffer[newBufferPos]);
	
	newBufferPos += sizeof(size_t);
	char* className = reinterpret_cast<char*>(&m_buffer[newBufferPos]);
	newBufferPos += classNameSize;
	Serializable* obj = getInstance(className);
	if (obj)
	{
		obj->readNext(&m_buffer[newBufferPos]);
		m_bufferPos += sizeNeeded;
	}
	return obj;
}

void BinaryReader::reloadBuffer()
{
	int rest = m_bufferSize - m_bufferPos;
	if (rest > 0)
	{
		std::memcpy(m_buffer, &m_buffer[m_bufferPos], rest);
		m_bufferSize = m_ioHandler->loadData(&m_buffer[rest], DEFAULT_BUFFER_SIZE - rest);
	}
	else
	{
		m_bufferSize = m_ioHandler->loadData(m_buffer, DEFAULT_BUFFER_SIZE);
	}
	m_bufferPos = 0;
}