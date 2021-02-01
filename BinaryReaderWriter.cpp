#include "BinaryReaderWriter.h"

BinaryReaderWriter::BinaryReaderWriter(IOHandler* readHandler, IOHandler* writeHandler)
{
	m_serializer = new BinaryWriter(writeHandler);
	m_deserializer = new BinaryReader(readHandler);
}

BinaryReaderWriter::~BinaryReaderWriter()
{
	delete m_serializer;
	delete m_deserializer;
}

bool BinaryReaderWriter::write(Serializable* src)
{
	return m_serializer->write(src);
}

Serializable* BinaryReaderWriter::readNext()
{
	return m_deserializer->readNext();
}