#include <iostream> //https://github.com/reko001/Zadanie7
#include <algorithm>
#include <iomanip>
#include <initializer_list>

template<typename T = float, int size = 3>
class Macierz2D {
private:
	T** m_dane;
public:
	Macierz2D();
	Macierz2D(T);
	Macierz2D(T**);
	Macierz2D(std::initializer_list<T>);
	Macierz2D(const Macierz2D<T, size>&);
	~Macierz2D();
	Macierz2D<T, size> operator=(const Macierz2D<T, size>&);
	Macierz2D<T, size> operator+(const Macierz2D<T, size>&);
	Macierz2D<T, size> operator+=(const Macierz2D<T, size>&);
	Macierz2D<T, size> operator-(const Macierz2D<T, size>&);
	Macierz2D<T, size> operator-=(const Macierz2D<T, size>&);
	Macierz2D<T, size> operator++();
	Macierz2D<T, size> operator++(int);
	Macierz2D<T, size> operator--();
	Macierz2D<T, size> operator--(int);
	Macierz2D<T, size> operator*(T);
	Macierz2D<T, size> operator*=(T);
	Macierz2D<T, size> operator*(const Macierz2D<T, size>&);
	Macierz2D<T, size> operator*=(const Macierz2D<T, size>&);
	bool operator<(Macierz2D<T, size>&);
	friend std::istream& operator>>(std::istream&, const Macierz2D<T, size>&);
	T getElement(int, int) const;
	void setElement(T, int, int);
	void makeIdentity();
	Macierz2D<T, size> transpose();
	T value();
};

template<typename T, int size>
Macierz2D<T, size>::Macierz2D() {
	m_dane = new T* [size];
	for (int i = 0; i < size; i++) {
		m_dane[i] = new T[size];
		for (int j = 0; j < size; j++) {
			m_dane[i][j] = 0;
		}
	}
}

template<typename T, int size>
Macierz2D<T, size>::Macierz2D(T arg) {
	m_dane = new T* [size];
	for (int i = 0; i < size; i++) {
		m_dane[i] = new T[size];
		for (int j = 0; j < size; j++) {
			m_dane[i][j] = arg;
		}
	}
}

template<typename T, int size>
Macierz2D<T, size>::Macierz2D(T** matrix) {
	m_dane = new T* [size];
	for (int i = 0; i < size; i++) {
		m_dane[i] = new T[size];
		for (int j = 0; j < size; j++) {
			m_dane[i][j] = matrix[i][j];
		}
	}
}

template<typename T, int size>
Macierz2D<T, size>::Macierz2D(const Macierz2D<T, size>& another) {
	m_dane = new T* [size];
	for (int i = 0; i < size; i++) {
		m_dane[i] = new T[size];
		for (int j = 0; j < size; j++) {
			m_dane[i][j] = another.m_dane[i][j];
		}
	}
}

template<typename T, int size>
Macierz2D<T, size>::Macierz2D(std::initializer_list<T> il) {
	typename std::initializer_list<T>::iterator it = il.begin();
	m_dane = new T* [size];
	for (int i = 0; i < size; i++) {
		m_dane[i] = new T[size];
		for (int j = 0; j < size; j++) {
			m_dane[i][j] = *it++;
		}
	}
}

template<typename T, int size>
Macierz2D<T, size>::~Macierz2D() {
	for (int i = 0; i < size; i++) {
		delete[] m_dane[i];
	}
	delete[] m_dane;
}

template<typename T, int size>
Macierz2D<T, size> Macierz2D<T, size>::operator=(const Macierz2D<T, size>& matrix) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			this->m_dane[i][j] = matrix.m_dane[i][j];
		}
	}
	return *this;
}

template<typename T, int size>
Macierz2D<T, size> Macierz2D<T, size>::operator+(const Macierz2D<T, size>& matrix) {
	Macierz2D<T, size> sum;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			sum.m_dane[i][j] = this->m_dane[i][j] + matrix.m_dane[i][j];
		}
	}
	return sum;
}

template<typename T, int size>
Macierz2D<T, size> Macierz2D<T, size>::operator-(const Macierz2D<T, size>& matrix) {
	Macierz2D<T, size> diff;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			diff.m_dane[i][j] = this->m_dane[i][j] - matrix.m_dane[i][j];
		}
	}
	return diff;
}

template<typename T, int size>
Macierz2D<T, size> Macierz2D<T, size>::operator+=(const Macierz2D<T, size>& matrix) {
	*this = *this + matrix;
	return *this;
}

template<typename T, int size>
Macierz2D<T, size> Macierz2D<T, size>::operator-=(const Macierz2D<T, size>& matrix) {
	*this = *this - matrix;
	return *this;
}

template<typename T, int size>
Macierz2D<T, size> Macierz2D<T, size>::operator++() {
	*this += 1;
	return *this;
}

template<typename T, int size>
Macierz2D<T,size> Macierz2D<T, size>::operator++(int) {
	Macierz2D<T, size> temp;
	temp = *this;
	*this += 1;
	return temp;
}

template<typename T, int size>
Macierz2D<T,size> Macierz2D<T, size>::operator--() {
	*this -= 1;
	return *this;
}

template<typename T, int size>
Macierz2D<T, size> Macierz2D<T, size>::operator--(int) {
	Macierz2D<T,size> temp;
	temp = *this;
	*this -= 1;
	return temp;
}

template<typename T, int size>
Macierz2D<T, size> Macierz2D<T, size>::operator*(T scalar) {
	Macierz2D<T, size> result;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			result.m_dane[i][j] = this->m_dane[i][j] * scalar;
		}
	}
	return result;
}

template<typename T, int size>
Macierz2D<T, size> Macierz2D<T, size>::operator*=(T scalar) {
	*this = *this * scalar;
	return *this;
}

template<typename T, int size>
Macierz2D<T, size> Macierz2D<T, size>::operator*(const Macierz2D<T, size>& matrix) {
	Macierz2D<T, size> result;
	float temp;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			temp = 0;
			for (int k = 0; k < size; k++) {
				temp += this->m_dane[i][k] * matrix.m_dane[k][j];
			}
			result.m_dane[i][j] = temp;
		}
	}
	return result;
}
template<typename T, int size>
Macierz2D<T, size> Macierz2D<T, size>::operator*=(const Macierz2D<T, size>& matrix) {
	*this = *this * matrix;
	return *this;
}

template<typename T, int size>
bool Macierz2D<T, size>::operator<(Macierz2D<T, size>& matrix) {
	return value() < matrix.value();
}

template<typename T, int size>
std::ostream& operator<<(std::ostream& stream, const Macierz2D<T, size>& matrix) {
	std::cout << std::left;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			stream << std::setw(8) << matrix.getElement(i,j) << " ";
		}
		stream << std::endl;
	}
	return stream;
}

template<typename T, int size>
std::istream& operator>>(std::istream& stream, const Macierz2D<T, size>& matrix) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			stream >> matrix.m_dane[i][j];
		}
	}
	return stream;
}

template<typename T, int size>
T Macierz2D<T, size>::getElement(int row, int column) const {
	return m_dane[row][column];
}

template<typename T, int size>
void Macierz2D<T, size>::setElement(T arg, int row, int column) {
	m_dane[row][column] = arg;
}

template<typename T, int size>
void Macierz2D<T, size>::makeIdentity() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i != j) {
				m_dane[i][j] = 0;
			}
			else {
				m_dane[i][j] = 1;
			}
		}
	}
}

template<typename T, int size>
Macierz2D<T, size> Macierz2D<T, size>::transpose() {
	Macierz2D<T, size> result;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			result.m_dane[i][j] = m_dane[j][i];
		}
	}
	return result;
}

template<typename T, int size>
T Macierz2D<T, size>::value() {
	T result = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			result += m_dane[i][j];
		}
	}
	return result;
}

int main() {
	float** m1, ** m2, ** m3;
	m1 = new float* [3];
	m2 = new float* [3];
	m3 = new float* [3];
	srand(static_cast<unsigned> (time(0)));
	for (int i = 0; i < 3; i++) {
		m1[i] = new float[3];
		m2[i] = new float[3];
		m3[i] = new float[3];
		for (int j = 0; j < 3; j++) {
			m1[i][j] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 10);
			m2[i][j] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 10);
			m3[i][j] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 10);
		}
	}
	Macierz2D<float> matrix1(m1);
	Macierz2D<float> matrix2(m2);
	Macierz2D<float> matrix3(m3);
	Macierz2D<float> macierze[3] = { matrix1, matrix2, matrix3 };
	std::cout << "Przed sortowaniem" << std::endl << std::endl;
	std::cout << "Macierz 1" << std::endl << macierze[0] << std::endl << "Macierz 2" <<
		std::endl <<macierze[1] << std::endl << "Macierz 3" << std::endl << macierze[2] << std::endl;
	std::cout << "Wartosci macierzy: " << std::endl << std::endl;
	std::cout << "Macierz 1 : " << macierze[0].value() << std::endl;
	std::cout << "Macierz 2 : " << macierze[1].value() << std::endl;
	std::cout << "Macierz 3 : " << macierze[2].value() << std::endl;
	std::cout << std::endl;
	std::sort(macierze, macierze + 3);
	std::cout << "Po sortowaniu" << std::endl << std::endl;
	std::cout << "Macierz 1" << std::endl << macierze[0] << std::endl << "Macierz 2" <<
		std::endl << macierze[1] << std::endl << "Macierz 3" << std::endl << macierze[2] << std::endl;
	std::cout << "Mnozenie" << std::endl << std::endl;
	std::cout << "Macierz lewa" << std::endl << macierze[0] << std::endl;
	std::cout << "Macierz prawa" << std::endl << macierze[1] << std::endl;
	std::cout << "Macierz wynikowa" << std::endl << macierze[0] * macierze[1] << std::endl;

	//------------------------------------------------------------------------------------------------------
	std::cout << "------------------------------------------------------------------------------------------------" << std::endl<<std::endl;
	std::cout << "Macierz o rozmiarze 4 z elementami typu double" << std::endl;
	Macierz2D<double, 4> md4{5.4, 8.2, 9.0, 8.1, 0.0, 71.333344444, 3.7, 11.2, 8.3, 0.61, 9.99, 10.0, 8.09, 7.76, 1.25, 16.6};
	std::cout << md4 << std::endl;
	std::cout << "Po pomnozeniu przez 2" << std::endl;
	std::cout << (md4 *= 2) << std::endl;
	std::cout << "Transponowana" << std::endl;
	std::cout << md4.transpose() << std::endl;
	Macierz2D<double> md3_1{ 4.144, 9.0, 0.0, 7.1, 0.193, 8.5, 0.0003, 173.1, 91.2 };
	std::cout << "Macierz 1 o rozmiarze 3 z elementami typu double" << std::endl;
	std::cout << md3_1 << std::endl;
	Macierz2D<double> md3_2;
	md3_2.makeIdentity();
	std::cout << "Macierz 2 identycznosciowa o rozmiarze 3" << std::endl;
	std::cout << md3_2 << std::endl;
	std::cout << "Macierz 1 razy macierz 2" << std::endl;
	std::cout << md3_1 * md3_2 << std::endl;
	std::cout << "Macierz 1 plus macierz 2" << std::endl;
	std::cout << md3_1 + md3_2 << std::endl;
}