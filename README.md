# Cteni a zapis binarnich dat

Kazda trida, ktera jde binarizovat musi implementovat Serializable rozhrani
to znamena implementovat sve vlastni funkce write(), readNext() a getBinarySize()
Ukazkove to jsou SerializableClassSimple a SerializableClassWithPointer. NoserializableClass je tam jen do poctu jako zastupce neceho, co binarizovat nejde.

BinaryReader/BinaryWriter pak umi tyto tridy nacitat/zapisovat za pomoci libovolneho IOHandleru
IOHandlery jsou tridy implementujici rozhranni, ktere jim uklada zpracovat fce loadData() a saveData()
zde muze byt jak prace se soubory, tak treba prave trida pro sitovou komunikaci. Na vstupu/vystupu to je vsak buffer. 
Implementovana je jednoducha verze FileIOHandler. MemIOHandler jen v komentari ukazuje moznou praci s bufferem. Sitovou tridu jsem nepokousela.

BinaryReader/BinaryWriter musi pochopitene dodrzovat stejny format zapisu/cteni dat. 
Zde to vypada asi takto |celkova velikost bloku instance|delka nazvu tridy|nazev tridy|blok instance|.
Blok instance si pak kazda Serializable resi sama ve zminenem write()/readNext(). 
Typ tridy pri cteni je zjistovan manualni registraci jednotlivich trid do mapy <typeid::name(), lambda vracejici novou instanci>. Statickou mapu drzi BinaryReader. 
Je to rychle na implementaci, ale hadam, ze to pujde i hezcim zpusobem. Minimalne jde tridam pridat jeste id a neukladat cely dlouhy nazev do souboru.
BinaryReader/BinaryWriter maji svuj lokalni buffer na uchovavani rozumneho mnozstvi dat ke zpracovani. tyto bloky si pak predava s IOHandlerem

Trida, co umi oboje (BinaryReaderWriter) velmi jednoduse obsahuje i BinaryReader i BinaryWriter a vsechny sve ulohy jim outsourcuje.

V main je pak jednoducha zkouska kdy se dve tridy zapisou a nasledne prectou ze souboru. Jedna obycejna, jedna s ukazatelem
