#include <iostream>
#include <string>

#include "SerializableClassSimple.h"
#include "SerializableClassWithPointer.h"
#include "NoserializableClass.h"

#include "FileIOHandler.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"

using namespace std;

int main()
{
	//init classes to play with
	SerializableClassSimple* serializableSimple = new SerializableClassSimple(27.1127f, 109.3497f);
	string someDescription("Once upon a time");
	SerializableClassWithPointer* serializablePtr = new SerializableClassWithPointer(42, someDescription.c_str() + '\0', someDescription.size() + sizeof(char));
	NoserializableClass* noserializable =  new NoserializableClass(new string("You shall not pass"), 6378);
	
	//write instances to file
	BinaryWriter writer(new FileIOHandler("backup.bin"));
	writer.write(serializableSimple);
	writer.write(serializablePtr);

	//read binary file
	BinaryReader reader(new FileIOHandler("backup.bin"));
	vector<Serializable*> loaded;
	Serializable* dataIn = reader.readNext();
	while (dataIn)
	{
		loaded.push_back(dataIn);
		dataIn = reader.readNext();
	}

	for (auto s : loaded)
	{
		s->printInfo();
	}

	cout << "A to je vse pratele" << endl;
	return 0;
}