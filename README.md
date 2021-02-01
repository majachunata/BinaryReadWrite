# BinaryReadWrite
 Simple serializator/deserializator

Kazda trida, ktera jde binarizovat musi implementovat Serializable rozhrani
to znamena implementovat sve vlastni funkce serialize(), deserialize() a getBinarySize()

Serializator/Deserializator pak umi tyto tridy cist/psat za pomoci libovolneho IOHandleru
Opet jde o tridy implementujici rozhranni, ktere jim uklada zpracovat fce loadData() a saveData()
zde muze byt jak prace se soubory, tak treba prave trida pro sitovou komunikaci. 
Handler ziskava/vydava buffer a jeho velikost. load vraci mnoztvi nahranych dat

Serializator/Deserializator musi pochopitene dodrzovat stejny format zapisu/cteni dat. 
Zde to vypada asi takto |celkova velikost bloku instance|delka nazvu tridy|nazev tridy|blok instance|.
blok instance si pak kazda Serializable resi sama ve zminenem serialize()/deserialize(). Typ tridy pri cteni je podchycen manualni registraci jednotlivich trid do mapy <typeid.name, lambda vracejici novou instanci>
Je to rychle na implementaci, ale hadam, ze to pujde i hezcim zpusobem. Minimalne jde tridam pridat jeste id a neukladat cely dlouhy nazev do souboru.
Serializator i deserializator maji svuj lokalni buffer na uchovavani rozumneho mnozstvi dat ke zpracovani. tyto bloky si pak predava s IOHandlerem

Trida, co umi oboje velmi jednoduse obsahuje i serializator i deserializator a vsechny sve ulohy jim outsourcuje.

V main je pak jednoducha zkouska kdy se dve tridy zapisou a nasledne prectou ze souboru. Jedna obycejna, jedna s ukazatelem
