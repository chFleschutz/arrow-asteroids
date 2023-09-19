#pragma once
#include "MathVec.h"
#include <string>

using namespace std;


template <class T, unsigned int rowDim, unsigned int colDim>
class MathMatrix {
public:
	MathMatrix(T);
	MathMatrix(const MathMatrix&);
	MathMatrix(MathMatrix&&) noexcept;
	~MathMatrix();
	MathMatrix<T, rowDim, colDim>& operator=(const MathMatrix<T, rowDim, colDim>&);
	MathMatrix<T, rowDim, colDim>& operator=(MathMatrix<T, rowDim, colDim>&&) noexcept;
	T get(unsigned int row, unsigned int col) const;
	void set(unsigned int row, unsigned int col, T value);
	T getNullElement() const;
	MathVec<T, rowDim> getColumn(int index) const;
	MathVec<T, colDim> getRow(int index) const;
	void checkAccessValidity(unsigned int row, unsigned int col) const;

private:
	T nullElement;
	T** data;
};

template <class T, unsigned int rowDim>
class MathMatrixCol : public MathMatrix<T, rowDim, 1> {
	MathMatrixCol(MathVec<T, rowDim>);
};


template <class T, unsigned int colDim>
class MathMatrixRow : public MathMatrix<T, 1, colDim> {
	MathMatrixRow(MathVec<T, colDim>);
};


template<class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim>::MathMatrix(T nullElement) {
	data = new T*[rowDim];
	this->nullElement = nullElement;
	for (unsigned int i = 0; i < rowDim; i++) {
		data[i] = new T[colDim];
		for (unsigned int j = 0; j < colDim; j++) {
			data[i][j] = nullElement;
		}
	}
}

template<class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim>::MathMatrix(const MathMatrix& source) {
	data = new T * [rowDim];
	this->nullElement = source.nullElement;
	for (unsigned int i = 0; i < rowDim; i++) {
		data[i] = new T[colDim];
		for (unsigned int j = 0; j < colDim; j++) {
			data[i][j] = source.data[i][j];
		}
	}
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathMatrix<T, rowDim, colDim>::MathMatrix(MathMatrix&& source) noexcept {
	data = source.data;
	nullElement = source.nullElement;
	source.data = nullptr;
}


template<class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim>::~MathMatrix() {
	if (data != nullptr) {
		for (unsigned int i = 0; i < rowDim; i++) {
			delete[] data[i];
		}
	}
	delete[] data;
}

template<class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim>& MathMatrix<T, rowDim, colDim>::operator=(const MathMatrix<T, rowDim, colDim>& source) {
	this->nullElement = source.nullElement;
	for (unsigned int i = 0; i < rowDim; i++) {
		for (unsigned int j = 0; j < colDim; j++) {
			data[i][j] = source.data[i][j];
		}
	}
	return *this;	
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathMatrix<T, rowDim, colDim>& MathMatrix<T, rowDim, colDim>::operator=(MathMatrix<T, rowDim, colDim>&& source) noexcept {
	data = source.data;
	nullElement = source.nullElement;
	source.data = nullptr;
	return *this;
}



template<class T, unsigned int rowDim, unsigned int colDim>
inline T MathMatrix<T, rowDim, colDim>::getNullElement() const {
	return nullElement;
}


template<class T, unsigned int rowDim, unsigned int colDim>
inline void MathMatrix<T, rowDim, colDim>::checkAccessValidity(unsigned int row, unsigned int col) const {
	if (data == nullptr) 
		throw logic_error("Attempted operation on invalidated matrix.");
	if (row < 0 || row >= rowDim || col < 0 || col >= colDim)
		throw logic_error("Illegal matrix coordinates: (" + to_string(row) + ", " + to_string(col) + ").");
}



template<class T, unsigned int rowDim, unsigned int colDim>
T MathMatrix<T, rowDim, colDim>::get(unsigned int row, unsigned int col) const {
	checkAccessValidity(row, col);
	return data[row][col];
}

template<class T, unsigned int rowDim, unsigned int colDim>
void MathMatrix<T, rowDim, colDim>::set(unsigned int row, unsigned int col, T value) {
	checkAccessValidity(row, col);
	data[row][col] = value;
}


template<class T, unsigned int rowDim, unsigned int colDim>
MathVec<T, rowDim> MathMatrix<T, rowDim, colDim>::getColumn(int index) const {
	MathVec<T, rowDim> v(get(0, 0));
	for (unsigned int i = 0; i < rowDim; i++) {
		v.set(i, v.get(i, index));
	}
	return v;
}


template<class T, unsigned int rowDim, unsigned int colDim>
MathVec<T, colDim> MathMatrix<T, rowDim, colDim>::getRow(int index) const {
	MathVec<T, colDim> v(get(0, 0));
	for (unsigned int i = 0; i < colDim; i++) {
		v.set(i, get(index, i));
	}
	return v;
}

template<class T, unsigned int rowDim>
MathMatrixCol<T, rowDim>::MathMatrixCol(MathVec<T, rowDim> source) {
	data = new T * [rowDim];
	for (unsigned int i = 0; i < rowDim; i++) {
		data[i] = new T[1];
		data[i][0] = source.get(i);
	}
}


template<class T, unsigned int colDim>
MathMatrixRow<T, colDim>::MathMatrixRow(MathVec<T, colDim> source) {
	data = new T * [1];
	data[0] = new T[colDim];
	for (unsigned int i = 0; i < colDim; i++) {
		data[0][i] = source.get(i);
	}
}





template<class T, unsigned int sourceDim, unsigned int interDim, unsigned int destDim>
MathMatrix<T, destDim, sourceDim> operator*(const MathMatrix<T, destDim, interDim>& m1, 
	                                        const MathMatrix<T, interDim, sourceDim>& m2) {
	MathMatrix<T, destDim, sourceDim> m(m1.get(0, 0));
	for (unsigned int i = 0; i < destDim; i++) {
		for (unsigned int j = 0; j < sourceDim; j++) {
			T x = m1.getNullElement();
			for (unsigned int k = 0; k < interDim; k++) {
				x = x + m1.get(i, k) * m2.get(k, j);
			}
			m.set(i, j, x);
		}
	}
	return m;
}


template<class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim> operator+(const MathMatrix<T, rowDim, colDim>& m1, const MathMatrix<T, rowDim, colDim>& m2) {
	MathMatrix<T, rowDim, colDim> m(m1.getNullElement());
	for (unsigned int i = 0; i < rowDim; i++) {
		for (unsigned int j = 0; j < colDim; j++) {
			m.set(i, j, m1.get(i, j) + m2.get(i, j));
		}
	}
	return m;
}




template<class T, unsigned int sourceDim, unsigned int destDim>
MathVec<T, destDim> operator*(const MathMatrix<T, destDim, sourceDim>& m, const MathVec<T, sourceDim>& v) {
	MathVec<T, destDim> res(v.get(0));
	for (unsigned int i = 0; i < destDim; i++) {
		MathVec<T, sourceDim> row = m.getRow(i);
		res.set(i, row * v);
	}
	return res;
}

template<class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim> operator*(const MathMatrix<T, rowDim, colDim>& m, const T& k) {
	MathMatrix<T, rowDim, colDim> res(m.get(0, 0));
	for (unsigned int i = 0; i < rowDim; i++) {
		for (unsigned int j = 0; j < colDim; j++) {
			res.set(i, j, m.get(i, j) * k);
		}
	}
	return res;
}

template<class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim> operator*(const T& k, const MathMatrix<T, rowDim, colDim>& m) {
	return m * k;
}


template<class T, unsigned int rowDim, unsigned int colDim>
string to_string(const MathMatrix<T, rowDim, colDim>& m) {
	string s = "";
	for (int i = 0; i < rowDim; i++) {
		for (int j = 0; j < colDim; j++) {
			s = s + to_string(m.get(i, j));
			if (j < colDim - 1) s = s + ", ";
		}
		s = s + "\n";
	}
	return s;
}



