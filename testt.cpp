#include <iostream>
#include <fstream>

using namespace std;

struct Object {
	string id;
	string name;
	string directory;
	string position;
	string scale;
	string swivelAngle;
};

struct SpecialObject {
	string objID;
	string id;
	string gotoMap;
	string positionMap;
	string positionObj;
	string distance;
};

template<class T>
struct List {
	T *data;
	List<T> *next;
};

struct Map {
	string id;
	List<Object> *listObj;
	Map *next;
};

template<class T>
void addList(List<T> *list, T *data) {
	List<T> *l = new List<T>;
	l->data = data;

	if (list->next == NULL) {
		list->next = l;
		return;
	}

	List<T> *i = list->next;
	while (i->next != NULL) {
		i = i->next;
	}

	i->next = l;
}

template<class T>
T *getList(List<T> *list, int index) {
	List<T> *l = list->next;
	for (int i = 1; i < index; i++) {
		l = l->next;
	}

	return l->data;
}

void printListObject(List<Object> *list) {
	List<Object> *l = list->next;
	while (l != NULL) {
		cout << "\t" << l->data->id << endl;
		cout << "\t" << l->data->name << endl;
		cout << "\t" << l->data->directory << endl;
		cout << "\t" << l->data->position << endl;
		cout << "\t" << l->data->scale << endl;
		cout << "\t" << l->data->swivelAngle << endl;
		cout << endl;
		l = l->next;
	}
}

void putMap(Map *map, string id, List<Object> *obj) {
	Map *i = map;
	while (i->next != NULL && i->next->id != id) {
		i = i->next;
	}

	if (i->next == NULL) {
		i->next = new Map;
	}

	i->next->id = id;
	i->next->listObj = obj;
}

Map *getMap(List<Map> *map, string id) {
	List<Map> *listMap = map;
	while (listMap->data->id != id) {
		listMap = listMap->next;
	}

	return listMap->data;
}

bool existsID(List<Map> *map, string id) {
	List<Map> *listMap = map->next;
	while (listMap->data->id != id) {
		listMap = listMap->next;
		if (listMap == NULL) {
			return false;
		}
	}

	return true;
}

void printMap(Map *map) {
	Map *m = map->next;
	while (m != NULL) {
		cout << m->id << endl;
		printListObject(m->listObj);
		m = m->next;
	}
}

List<Map> *MAP = new List<Map>;

void readData(char *mapFile) {
	string id;
	Map *map;
	List<Object> *listObj = NULL;

	ifstream ifs(mapFile);
	string str;

	while (ifs >> str) {
		if (str.find("MAP") == 0) {
			if (listObj != NULL) {
				putMap(map, id, listObj);
				addList(MAP, map);
			}
			map = new Map;
			listObj = new List<Object>;
			id = str.substr(3);
		}

		string objID;
		if (str.find("OBJ") == 0) {
			Object *obj = new Object;
			objID = str.substr(3);
			obj->id = objID;
			ifs >> obj->name;
			ifs >> obj->directory;
			ifs >> obj->position;
			ifs >> obj->scale;
			ifs >> obj->swivelAngle;

			addList(listObj, obj);
		}

		if (str.find("GOTO") == 0) {
			SpecialObject *obj = new SpecialObject;
			obj->objID = objID;
			obj->id = str.substr(4);
			ifs >> obj->gotoMap;
			ifs >> obj->positionMap;
			ifs >> obj->positionObj;
			ifs >> obj->distance;

//			putMap(map->next, obj->gotoMap, map->next->listObj);
		}
	}
	putMap(map, id, listObj);
	addList(MAP, map);
}

void print(List<Map> *listMap) {
	List<Map> *list = listMap->next;
	while (list != NULL) {
		printMap(list->data);
		list = list->next;
	}
}

//int main(int argc, char **argv) {
//
//	readData((char*) "data.map");
//	print(MAP);
//
////	Object *obj = new Object;
////	obj->directory = "1";
////	obj->id = "1";
////	obj->name = "1";
////	obj->position = "1";
////	obj->scale = "1";
////	obj->swivelAngle = "1";
////
////	List<Object> * listObj = new List<Object>;
////	addList(listObj, obj);
////	Map *map = new Map;
////	putMap(map, "0001", listObj);
////
////	addList(MAP, map);
////
////
////	obj = new Object;
////	obj->directory = "2";
////	obj->id = "2";
////	obj->name = "2";
////	obj->position = "2";
////	obj->scale = "2";
////	obj->swivelAngle = "2";
////
////	listObj = new List<Object>;
////	addList(listObj, obj);
////	map = new Map;
////	putMap(map, "0002", listObj);
////
////	addList(MAP, map);
////
////	printMap(getMap(MAP, "0001"));
//
////	print(MAP);
//
////	cout << existsID(MAP, "0001");
//
//
//}
