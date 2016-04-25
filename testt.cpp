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
	List<T> *l = list;
	for (int i = 0; i < index; i++) {
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
	List<Map> *lm = map;
	while (lm->data->id != id) {
		lm = lm->next;
	}

	return lm->data;
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
	Map *map = new Map;

void readData(char *mapFile) {
	string id;
	List<Object> *lObj = new List<Object>;

	ifstream ifs(mapFile);
	string str;

	while (ifs >> str) {
		if (str.find("MAP") == 0) {
			id = str.substr(3);
		}

		if (str.find("OBJ") == 0) {
			Object *obj = new Object;
			obj->id = str.substr(3);
			ifs >> obj->name;
			ifs >> obj->directory;
			ifs >> obj->position;
			ifs >> obj->scale;
			ifs >> obj->swivelAngle;

			addList(lObj, obj);
		}

//		if (str.find("GOTO") == 0) {
//			SpecialObject *obj = new SpecialObject;
//			obj->id = str.substr(4);
//			ifs >> obj->gotoMap;
//			ifs >> obj->positionMap;
//			ifs >> obj->positionObj;
//			ifs >> obj->distance;
//
//			Map *m = getMap(MAP, id);
//			m->next->id = obj->gotoMap;
//		}
	}
	putMap(map, "001", lObj);
	printMap(map);
}

void printAll(List<Map> *listMap) {
	List<Map> *lm = listMap;
	while (lm->next != NULL) {
		printMap(lm->data);
		lm = lm->next;
	}
}

int main(int argc, char **argv) {
	readData((char *) "test.txt");
//	printMap(map);
}
