#ifndef NOSERIALIZABLE_CLASS_H
#define NOSERIALIZABLE_CLASS_H

#include <string>

using namespace std;

/**
* Example of class which can't be serialized as it doesn't implement Serializable interface
 */
class NoserializableClass
{
private:
	int m_id;
	string* m_name;

public:
	NoserializableClass(string* name, int id) : m_name(name), m_id(id) {};
	~NoserializableClass() { delete m_name; };
	const int getId() { return m_id; };
	string* getName() { return m_name; };
};

#endif //NOSERIALIZABLE_CLASS_H