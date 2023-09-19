#pragma once
#include <stdexcept>
#include <string>

using namespace std;

template <class T, unsigned int dim>
class MathVec {
public:
	MathVec(T);	
	MathVec(const MathVec&);
	MathVec(MathVec&&) noexcept;
	~MathVec();
	void set(unsigned int index, T value);
	T get(unsigned int index) const;	
	MathVec<T, dim>& operator=(const MathVec<T, dim>& v2);
	MathVec<T, dim>& operator=(MathVec<T, dim>&& v2) noexcept;
	T& operator[](unsigned int);


protected:
	T* data;
};

template <class T>
class MathVec2 : public MathVec<T, 2> {
public:
	MathVec2(T a, T b);
	MathVec2(const MathVec2&);
	MathVec2(const MathVec<T, 2>&);
	MathVec2<T>& operator=(MathVec<T, 2>& v2);
};

template <class T>
class MathVec3 : public MathVec<T, 3> {
public:
	MathVec3(T a, T b, T c);
	MathVec3(const MathVec3&);
	MathVec3<T>(const MathVec2<T>&, T);
	MathVec3(const MathVec<T, 3>&);
	MathVec3<T> crossProduct(MathVec3<T> other);

	MathVec3<T>& operator=(MathVec<T, 3>& v2);
};

template<class T, unsigned int dim>
MathVec<T, dim>::MathVec(T entry) {
	data = new T[dim];
	for (int i = 0; i < dim; i++) data[i] = entry;
}

template<class T, unsigned int dim>
MathVec<T, dim>::MathVec(const MathVec& source) {
	data = new T[dim];
	for (int i = 0; i < dim; i++) data[i] = source.data[i];
}

template<class T, unsigned int dim>
MathVec<T, dim>::MathVec(MathVec&& source) noexcept {
	data = source.data;
	source.data = nullptr;
}

template<class T>
MathVec2<T>::MathVec2(T a, T b) : MathVec<T, 2>(a) {
	this->data[1] = b;	
}

template<class T>
inline MathVec2<T>::MathVec2(const MathVec2& source) : MathVec<T, 2>(source.get(0)) {
	this->data[1] = source.data[1];
}

template<class T>
inline MathVec2<T>::MathVec2(const MathVec<T, 2>& source) : MathVec<T, 2>(source.get(0)) {
	this->data[1] = source.get(1);
}

template<class T>
inline MathVec2<T>& MathVec2<T>::operator=(MathVec<T, 2>& source) {
	data[0] = source.data[0];
	data[1] = source.data[1];
	return *this;
}

template<class T>
MathVec3<T>::MathVec3(T a, T b, T c) : MathVec<T, 3>(a) {
	this->data[1] = b;
	this->data[2] = c;
}

template<class T>
inline MathVec3<T>::MathVec3(const MathVec3& source) : MathVec<T, 3>(source.get(0)) {
	this->data[1] = source.data[1];
	this->data[2] = source.data[2];
}

template<class T>
MathVec3<T>::MathVec3(const MathVec2<T>& source, T third) 
	: MathVec<T, 3>(source.get(0)) {
	this->data[1] = source.get(1);
	this->data[2] = third;
}

template<class T>
inline MathVec3<T>::MathVec3(const MathVec<T, 3>& source) 
	: MathVec<T, 3>(source.get(0)) {
	this->data[1] = source.get(1);
	this->data[2] = source.get(2);
}

template<class T>
inline MathVec3<T> MathVec3<T>::crossProduct(MathVec3<T> other) {
	return MathVec3<T>(
		this->data[1] * other.data[2] - this->data[2] * other.data[1],
		this->data[2] * other.data[0] - this->data[0] * other.data[2],
		this->data[0] * other.data[1] - this->data[1] * other.data[0]
		);
}

template<class T>
inline MathVec3<T>& MathVec3<T>::operator=(MathVec<T, 3>& source) {
	this->data[0] = source.data[0];
	this->data[1] = source.data[1];
	this->data[2] = source.data[2];
	return *this;
}

template<class T, unsigned int dim>
MathVec<T, dim>::~MathVec() {
	delete[] data;
}

template<class T, unsigned int dim>
void MathVec<T, dim>::set(unsigned int index, T value) {
	if (index < 0 || index >= dim)
		throw logic_error("Illegal index: " + to_string(index));
	data[index] = value;
}

template<class T, unsigned int dim>
inline T MathVec<T, dim>::get(unsigned int index) const {
	if (index < 0 || index >= dim)
		throw logic_error("Illegal index: " + to_string(index));
	return data[index];
}

template<class T, unsigned int dim>
MathVec<T, dim>& MathVec<T, dim>::operator=(const MathVec<T, dim>& v2) {
	for (int i = 0; i < dim; i++) {
		data[i] = v2.data[i];
	}
	return *this;
}

template<class T, unsigned int dim>
MathVec<T, dim>& MathVec<T, dim>::operator=(MathVec<T, dim>&& v2) noexcept {
	delete[] data;
	data = v2.data;	
	v2.data = nullptr;
	return *this;
}

template<class T, unsigned int dim>
bool operator==(const MathVec<T, dim>& v1, const MathVec<T, dim>& v2) {	
	for (int i = 0; i < dim; i++) {
		if (v1.get(i) != v2.get(i)) return false;
	}
	return true;
}

template<class T, unsigned int dim>
inline T& MathVec<T, dim>::operator[](unsigned int index) {
	return data[index];
}

template<class T, unsigned int dim>
MathVec<T, dim> operator+(const MathVec<T, dim>& v1, const MathVec<T, dim>& v2) {
	MathVec<T, dim> sum(v1.get(0));
	for (unsigned int i = 0; i < dim; i++) {
		sum.set(i, v1.get(i) + v2.get(i));
	}
	return sum;
}

template<class T, unsigned int dim>
MathVec<T, dim> operator-(const MathVec<T, dim>& v1, const MathVec<T, dim>& v2) {
	MathVec<T, dim> sum(v1.get(0));
	for (unsigned int i = 0; i < dim; i++) {
		sum.set(i, v1.get(i) - v2.get(i));
	}
	return sum;
}

template<class T, unsigned int dim>
T operator*(const MathVec<T, dim>& v1, const MathVec<T, dim>& v2) {
	T result = v1.get(0) * v2.get(0);
	for (unsigned int i = 1; i < dim; i++) {
		result = result + v1.get(i) * v2.get(i);
	}
	return result;
}

template<class T, unsigned int dim>
MathVec<T, dim> operator*(const MathVec<T, dim>& v1, const T& scalar) {
	MathVec<T, dim> v(v1.get(0) * scalar);
	for (unsigned int i = 1; i < dim; i++) {
		v.set(i, v1.get(i) * scalar);
	}
	return v;
}

template<class T, unsigned int dim>
MathVec<T, dim> operator*(const T& scalar, const MathVec<T, dim>& v1) {
	return v1 * scalar;
}

template <class T, unsigned int dim>
string to_string(const MathVec<T, dim>& v) {
    string s = "(";
	for (int i = 0; i < dim; i++) {
		s = s + to_string(v.get(i));
		if (i < dim - 1) s = s + ", ";
	}
	return s + ")";
}
