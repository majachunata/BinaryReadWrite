#ifndef IO_HANDLER_H
#define IO_HANDLER_H

/**
* Input Output Handler interface defines basic functionality for every class operating on serialized data
 */
class IOHandler
{
public:
	/**
	 * Load data of given amount to prepared buffer
	 * @param dst stays for destination buffer where to put data
	 * @param amount says how much do we want to load
	 * @retval indicates amount of data actually loaded
	 */
	virtual size_t loadData(char* dst, const int amount) = 0;

	/**
	 * Save data from buffer of given size
	 * @param src is source buffer we want to save
	 * @param amount says how large buffer do we want to save
	 */
	virtual void saveData(const char* src, const int amount) = 0;

	virtual ~IOHandler() {};
};

#endif //IO_HANDLER_H