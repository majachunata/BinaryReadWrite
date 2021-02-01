#ifndef BINARY_READER_WRITER_H
#define BINARY_READER_WRITER_H

#include "BinaryReader.h"
#include "BinaryWriter.h"
#include "IOHandler.h"

/**
* Class returning Serializable instances from their binarized form and writing Serializable instances to binary form
 */
class BinaryReaderWriter
{
private: 
	BinaryWriter* m_serializer;		//Object handling serialization
	BinaryReader* m_deserializer;	//Object handling deserialization

public:
	BinaryReaderWriter(IOHandler* readHandler, IOHandler* writeHandler);
	~BinaryReaderWriter();

	/**
	 * Binarize given Serializable instance and give it to IOHandler for next steps (save/send..)
	 * @param src is Serializable instance to be serialized
	 * @retval true while succeedd
	 */
	bool write(Serializable* src);
	
	/**
	 * Reads one instance of Serializable class from buffer and move buffer pointer to the next
	 * @retval instance of Serializable class filled by values from its binary representation on buffer
	 */
	Serializable* readNext();
};

#endif //BINARY_READER_WRITER_H