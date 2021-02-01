#ifndef BINARY_WRITER_H
#define BINARY_WRITER_H

#include <string>
#include <vector>

using namespace std;

class IOHandler;
class Serializable;

/**
* Class converting Serializable classes to binary form
 */
class BinaryWriter

{
private:
	static constexpr const size_t DEFAULT_BUFFER_SIZE = 1024;
	
	IOHandler* m_ioHandler;	//handler class to take care of binarized data

	char* m_buffer;			//internal buffer to save binarized instances
	size_t m_bufferSize;	//current buffer size
	int m_bufferPos;		//current buffer intex to write to

	/**
	 * gives buffer data to IOHandler and make it free for next binarization
	 */
	void flushBuffer();

	/**
	 * Make sure we have enough space for data to be written. Flush while not. Not suited for bigger instancies than DEFAULT_BUFFER_SIZE
	 * @param bufSize says how much space do we need
	 * @retval true if interna buffer is large enough
	 */
	bool reserveBuffer(size_t bufSize);

public:
	BinaryWriter(IOHandler* ioHandler);
	~BinaryWriter();

	/**
	 * Binarize given Serializable instance and give it to IOHandler for next steps (save/send..)
	 * @param src is Serializable instance to be serialized
	 * @retval true while succeedd
	 */
	bool write(Serializable* src);
};

#endif //BINARY_WRITER_H