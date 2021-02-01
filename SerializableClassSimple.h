#ifndef SERIALIZABLE_CLASS_SIMPLE_H
#define SERIALIZABLE_CLASS_SIMPLE_H

#include <iostream>

#include "Serializable.h"

using namespace std;

/**
* Class which can be serialized and doesn't own any pointers so the serialized size is allways the same
 */
class SerializableClassSimple : public Serializable
{
private:
	float m_latitude;
	float m_longitude;

public:
	SerializableClassSimple() : m_longitude(0.0f), m_latitude(0.0f) {};
	SerializableClassSimple(float longitude, float latitude) : m_longitude(longitude), m_latitude(latitude){};
	const float getLongitude() { return m_longitude; };
	const float getLatitude() { return m_latitude; };

	size_t getBinarySize() const override
	{
		//just two floats to be saved
		return sizeof(float) << 1;
	}

	void write(void* buffer) const override
	{
		float* floatBuff = static_cast<float*>(buffer);
		floatBuff[0] = m_longitude;
		floatBuff[1] = m_latitude;

	};

	void readNext(void* buffer) override
	{
		float* floatBuff = static_cast<float*>(buffer);
		m_longitude = floatBuff[0];
		m_latitude = floatBuff[1];
	};

	void printInfo() override
	{
		cout << "SerializableClassSimple long: " << m_longitude << ", lat: " << m_latitude << endl;
	}
};

#endif //SERIALIZABLE_CLASS_SIMPLE_H