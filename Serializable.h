#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

/**
* Serializable interface defines basic functionality for every data type which may be serialized
 */
class Serializable
{
public:
    /**
     * Get size of buffer needed for serializing whole instance
     * @retval size of buffer needed for serializing whole instance
     */
	virtual size_t getBinarySize() const = 0;

    /**
     * Serialize instance to buffer provided
     * @param buffer where to save serialized informations. buffer is expected to be large enough
     */
	virtual void write(void* buffer) const = 0;
	
    /**
     * Fills itself with values deserialized from buffer
     * @param buffer with serialized version of instance data
     */
    virtual void readNext(const void* buffer) = 0;

    /**
     * Prints brief overview of instance data - for demonstration use only
     */
    virtual void printInfo() = 0;

    virtual ~Serializable(){};
};

#endif //SERIALIZABLE_H