#ifndef NOSERIALIZABLE_CLASS_H
#define NOSERIALIZABLE_CLASS_H

#include <string>

/**
* Example of class which can't be serialized as it doesn't implement Serializable interface
 */
class NoserializableClass
{
private:
	int m_id;
	std::string* m_name;

public:
	NoserializableClass(std::string* name, int id) : m_name(name), m_id(id) {};
	~NoserializableClass() { delete m_name; };
	const int getId() { return m_id; };
	std::string* getName() { return m_name; };
};

#endif //NOSERIALIZABLE_CLASS_H