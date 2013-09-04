#pragma once

template<class T> class Singleton {

protected:
	Singleton() { if (theInstance) throw; };

public:
	static T *instance() {
		if (NULL == theInstance) {
			theInstance = new T();
		}
		return theInstance;
	}
private:
	static T* theInstance;
};

template<class T> T* Singleton<T>::theInstance = (0);
