#ifndef SERIALIZABLE_CLASS_WITH_POINTER_H
#define SERIALIZABLE_CLASS_WITH_POINTER_H

#include <iostream>

#include "Serializable.h"

using namespace std;

/**
* Class which can be serialized and owns pointer so the serialized size is different for each instance
 */
class SerializableClassWithPointer : public Serializable
{
private:
	const char* m_desc;
	int m_descLen;
	int m_id;

public:
	SerializableClassWithPointer() : m_id(0), m_desc(nullptr), m_descLen(0) {};
	SerializableClassWithPointer(int id, const char* desc, int descLen) : m_id(id), m_desc(desc), m_descLen(descLen) {};
	~SerializableClassWithPointer()
	{
		delete m_desc;
	}

	int getId() const { return m_id; };
	const char* getDescription() const { return m_desc; };

	size_t getBinarySize() const override
	{
		//two ints + buffer of given length
		return (sizeof(int) << 1) + (m_descLen * sizeof(char));
	}

	void write(void* buffer) const override
	{
		int* intBuff = static_cast<int*>(buffer);
		intBuff[0] = m_id;
		intBuff[1] = m_descLen;
		char* charBuff = static_cast<char*>(buffer);
		charBuff = &charBuff[sizeof(int) << 1];
		std::memcpy(charBuff, m_desc, m_descLen);
	};

	void readNext(const void* buffer) override
	{
		const int* intBuff = static_cast<const int*>(buffer);
	
		m_id = intBuff[0];
		m_descLen = intBuff[1];
		if (m_desc)
		{
			delete m_desc;
		}
		m_desc = new char[m_descLen];

		std::memcpy(const_cast<char*>(m_desc), &intBuff[2], m_descLen);
	};

	void printInfo() override
	{
		cout << "SerializableClassWithPointer id: " << m_id << ", desc: " << m_desc << endl;
	}
};

#endif //SERIALIZABLE_CLASS_WITH_POINTER_H