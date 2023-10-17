#include <iostream>
#include <cmath>
const float epsilon = 0.0001f;
using namespace std;
namespace matrix {
	template <typename T>
	class Container {
	private:
		int _size;
		T* _arr;
	public:
		Container();

		Container(int size);

		Container(const Container<T>& other);

		int get_size();

		T* get_array();

		T& operator[](int index);

		T operator[](int index) const;

		void swaps(Container<T>& other);

		Container<T>& operator=(const Container<T>& other);

		~Container();

		bool operator==(const Container<T>& other) const;

		bool operator!=(const Container<T>& other) const;
	};

	template <typename T>
	Container<T>::Container() {
		this->_arr = nullptr;
		this->_size = 0;
	}

	template <typename T>
	Container<T>::Container(int size) {
		this->_size = size;
		this->_arr = new T[this->_size];
		for (int i = 0; i < this->_size; ++i) {
			this->_arr[i] = 0;
		}
	}

	template <typename T>
	Container<T>::Container(const Container<T>& other) {
		this->_size = other._size;
		this->_arr = new T[_size];
		for (int i = 0; i < this->_size; ++i) {
			this->_arr[i] = other._arr[i];
		}
	}

	template <typename T>
	int Container<T>::get_size() {
		return _size;
	}

	template <typename T>
	T* Container<T>::get_array() {
		return _arr;
	}

	template <typename T>
	T Container<T>::operator[](int index) const {
		if (index < 0 || index >= this->_size) {
			throw runtime_error("Index out of range");
		}
		return this->_arr[index];
	}

	template <typename T>
	T& Container<T>::operator[](int index) {
		if (index < 0 || index >= this->_size) {
			throw runtime_error("Index out of range");
		}
		return this->_arr[index];
	}

	template <typename T>
	void Container<T>::swaps(Container<T>& other) {
		swap(this->_size, other._size);
		swap(this->_arr, other._arr);
	}

	template <typename T>
	Container<T>& Container<T>::operator=(const Container<T>& other) {
		Container<T> temp(other);
		this->swaps(temp);
		return *this;
	}
	
	template<typename T>
	bool Container<T>::operator==(const Container<T>& other) const {
		if (this->_size == other._size) {
			for (int i = 0; i < this->_size; i++) {
				if ((*this)[i] - other[i]) {
					return false;
				}
			}
			return true;
		}
		return false;
	}

	bool Container<float>::operator==(const Container<float>& other) const {
		if (this->_size == other._size) {
			for (int i = 0; i < this->_size; i++) {
				if (fabs((*this)[i] - other[i]) <= epsilon) {
					return false;
				}
			}
			return true;
		}
		return false;
	}

	template<typename T>
	bool Container<T>::operator!=(const Container<T>& other) const {
		return !((*this) == other);
	}

	template <typename T>
	Container<T>::~Container() {
		if (this->_arr != nullptr) {
			delete[] this->_arr;
			_arr = nullptr;
		}
	}
}