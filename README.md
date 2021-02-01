# BinaryReadWrite
 jednoduchy serializator/deserializator

Kazda trida, ktera jde binarizovat musi implementovat Serializable rozhrani
to znamena implementovat sve vlastni funkce serialize(), deserialize() a getBinarySize()
Ukazkove to jsou SerializableClassSimple a SerializableClassWithPointer. NoserializableClass je tam jen do poctu jako zastupce neceho, co binarizovat nejde.

BinaryReader/BinaryWriter pak umi tyto tridy nacitat/zapisovat za pomoci libovolneho IOHandleru
IOHandlery jsou tridy implementujici rozhranni, ktere jim uklada zpracovat fce loadData() a saveData()
zde muze byt jak prace se soubory, tak treba prave trida pro sitovou komunikaci. Na vstupu/vystupu to je vsak buffer. 
Implementovana je jednoducha verze FileIOHandler, ktera zapisuje vzdy na konec souboru, kdyz uz existuje. MemIOHandler jen v komentari ukazuje moznou praci s bufferem. Sitovou tridu jsem nepokousela.


BinaryReader/BinaryWriter musi pochopitene dodrzovat stejny format zapisu/cteni dat. 
Zde to vypada asi takto |celkova velikost bloku instance|delka nazvu tridy|nazev tridy|blok instance|.
Blok instance si pak kazda Serializable resi sama ve zminenem serialize()/deserialize(). 
Typ tridy pri cteni je zjistovan manualni registraci jednotlivich trid do mapy <typeid.name, lambda vracejici novou instanci>
Je to rychle na implementaci, ale hadam, ze to pujde i hezcim zpusobem. Minimalne jde tridam pridat jeste id a neukladat cely dlouhy nazev do souboru.
Serializator i deserializator maji svuj lokalni buffer na uchovavani rozumneho mnozstvi dat ke zpracovani. tyto bloky si pak predava s IOHandlerem

Trida, co umi oboje (BinaryReaderWriter) velmi jednoduse obsahuje i serializator i deserializator a vsechny sve ulohy jim outsourcuje.

V main je pak jednoducha zkouska kdy se dve tridy zapisou a nasledne prectou ze souboru. Jedna obycejna, jedna s ukazatelem
