#include <iostream>
#include <algorithm>
#include <iomanip>
#include <initializer_list>

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
	std::cout << std::left;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			stream << std::setw(8) << matrix.m_dane[i][j] << " ";
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
	Macierz2D matrix1(m1);
	Macierz2D matrix2(m2);
	Macierz2D matrix3(m3);
	Macierz2D macierze[3] = { matrix1, matrix2, matrix3 };
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
}