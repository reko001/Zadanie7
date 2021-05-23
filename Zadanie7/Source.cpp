#include <iostream>
#include <algorithm>

class Macierz2D {
private:
	float** m_dane;
public:
	Macierz2D();
	Macierz2D(float);
	Macierz2D(float**);
	Macierz2D(const Macierz2D&);
	~Macierz2D();
	Macierz2D operator=(const Macierz2D&);
	Macierz2D operator+(const Macierz2D&);
	Macierz2D operator+=(const Macierz2D&);
	Macierz2D operator-(const Macierz2D&);
	Macierz2D operator-=(const Macierz2D&);
	Macierz2D operator++();
	Macierz2D operator++(int);
	Macierz2D operator--();
	Macierz2D operator--(int);
	Macierz2D operator*(float);
	Macierz2D operator*=(float);
	Macierz2D operator*(const Macierz2D&);
	Macierz2D operator*=(const Macierz2D&);
	bool operator<(Macierz2D&);
	friend std::ostream& operator<<(std::ostream&, const Macierz2D&);
	friend std::istream& operator>>(std::istream&, const Macierz2D&);
	float getElement(int, int);
	void setElement(float, int, int);
	void makeIdentity();
	Macierz2D transpose();
	float value();
};

Macierz2D::Macierz2D() {
	m_dane = new float* [3];
	for (int i = 0; i < 3; i++) {
		m_dane[i] = new float[3];
		for (int j = 0; j < 3; j++) {
			m_dane[i][j] = 0;
		}
	}
}

Macierz2D::Macierz2D(float arg) {
	m_dane = new float* [3];
	for (int i = 0; i < 3; i++) {
		m_dane[i] = new float[3];
		for (int j = 0; j < 3; j++) {
			m_dane[i][j] = arg;
		}
	}
}

Macierz2D::Macierz2D(float** matrix) {
	m_dane = new float* [3];
	for (int i = 0; i < 3; i++) {
		m_dane[i] = new float[3];
		for (int j = 0; j < 3; j++) {
			m_dane[i][j] = matrix[i][j];
		}
	}
}

Macierz2D::Macierz2D(const Macierz2D& another) {
	m_dane = new float* [3];
	for (int i = 0; i < 3; i++) {
		m_dane[i] = new float[3];
		for (int j = 0; j < 3; j++) {
			m_dane[i][j] = another.m_dane[i][j];
		}
	}
}


Macierz2D::~Macierz2D() {
	for (int i = 0; i < 3; i++) {
		delete[] m_dane[i];
	}
	delete[] m_dane;
}

Macierz2D Macierz2D::operator=(const Macierz2D& matrix) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->m_dane[i][j] = matrix.m_dane[i][j];
		}
	}
	return *this;
}

Macierz2D Macierz2D::operator+(const Macierz2D& matrix) {
	Macierz2D sum;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			sum.m_dane[i][j] = this->m_dane[i][j] + matrix.m_dane[i][j];
		}
	}
	return sum;
}

Macierz2D Macierz2D::operator-(const Macierz2D& matrix) {
	Macierz2D diff;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			diff.m_dane[i][j] = this->m_dane[i][j] - matrix.m_dane[i][j];
		}
	}
	return diff;
}

Macierz2D Macierz2D::operator+=(const Macierz2D& matrix) {
	*this = *this + matrix;
	return *this;
}

Macierz2D Macierz2D::operator-=(const Macierz2D& matrix) {
	*this = *this - matrix;
	return *this;
}

Macierz2D Macierz2D::operator++() {
	*this += 1;
	return *this;
}

Macierz2D Macierz2D::operator++(int) {
	Macierz2D temp;
	temp = *this;
	*this += 1;
	return temp;
}

Macierz2D Macierz2D::operator--() {
	*this -= 1;
	return *this;
}

Macierz2D Macierz2D::operator--(int) {
	Macierz2D temp;
	temp = *this;
	*this -= 1;
	return temp;
}

Macierz2D Macierz2D::operator*(float scalar) {
	Macierz2D result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m_dane[i][j] = this->m_dane[i][j] * scalar;
		}
	}
	return result;
}

Macierz2D Macierz2D::operator*=(float scalar) {
	*this = *this * scalar;
	return *this;
}

Macierz2D Macierz2D::operator*(const Macierz2D& matrix) {
	Macierz2D result;
	float temp;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp = 0;
			for (int k = 0; k < 3; k++) {
				temp += this->m_dane[i][k] * matrix.m_dane[k][j];
			}
			result.m_dane[i][j] = temp;
		}
	}
	return result;
}

Macierz2D Macierz2D::operator*=(const Macierz2D& matrix) {
	*this = *this * matrix;
	return *this;
}

bool Macierz2D::operator<(Macierz2D& matrix) {
	return value() < matrix.value();
}

std::ostream& operator<<(std::ostream& stream, const Macierz2D& matrix) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			stream << matrix.m_dane[i][j] << " ";
		}
		stream << std::endl;
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, const Macierz2D& matrix) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			stream >> matrix.m_dane[i][j];
		}
	}
	return stream;
}

float Macierz2D::getElement(int row, int column) {
	return m_dane[row][column];
}

void Macierz2D::setElement(float arg, int row, int column) {
	m_dane[row][column] = arg;
}

void Macierz2D::makeIdentity() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i != j) {
				m_dane[i][j] = 0;
			}
			else {
				m_dane[i][j] = 1;
			}
		}
	}
}

Macierz2D Macierz2D::transpose() {
	Macierz2D result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m_dane[i][j] = m_dane[j][i];
		}
	}
	return result;
}

float Macierz2D::value() {
	float result = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result += m_dane[i][j];
		}
	}
	return result;
}

int main() {

	Macierz2D matrix1(1);
	Macierz2D matrix2(2);
	Macierz2D suma(1);
	suma = matrix1 + matrix2;
	std::cout << suma;
	suma += matrix1;
	std::cout << suma;
	suma *= 15;
	//std::cin >> matrix2;
	suma = matrix1 *= matrix2;
	std::cout << suma;
	suma = suma.transpose();
	std::cout << suma;
	Macierz2D matrix[3];
	std::cin >> matrix[0] >> matrix[1] >> matrix[2];
	std::cout << std::endl;
	std::cout << matrix[0] << matrix[1] << matrix[2] << std::endl;
	std::cout << matrix[0].value()<<" " << matrix[1].value()<<" " << matrix[2].value()<<" " << std::endl;
	std::sort(matrix, matrix + 3);
	std::cout << matrix[0] << matrix[1] << matrix[2];
}