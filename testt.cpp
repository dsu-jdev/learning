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

template<class T>
struct List {
	T *data;
	List<T> *next;
};

struct Map {
	string id;
	List<Object> *obj;
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

void putMap(Map *map, string id, List<Object> *obj) {
	Map *i = map;
	while (i->next != NULL && i->next->id != id) {
		i = i->next;
	}

	if (i->next == NULL) {
		i->next = new Map;
	}

	i->next->id = id;
	i->next->obj = obj;
}

List<Object> *getMap(Map *map, string id) {
	Map *m = map;
	while (m->id != id) {
		m = m->next;
	}

	return m->obj;
}

List<Map> *MAP = new List<Map>;

void readData(char *mapFile) {
	string str;
	string id;
	List<Object> *lObj = new List<Object>;
	ifstream ifs(mapFile);
	while (ifs >> str) {
		if (str.find("MAP") == 0) {
			if (lObj->next != NULL) {
//				addMap()
			}
			Map *map = new Map;
			id = str.substr(3);
			putMap(map, id, NULL);
			addList(MAP, map);
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
			delete(obj);
		}
	}
}

int main(int argc, char **argv) {
	Map *map = new Map;
	putMap(map, "abc", NULL);
	putMap(map, "def", NULL);
	putMap(map, "abc", new List<Object>);
}

