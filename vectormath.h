#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>
#include <initializer_list>
#include <math.h>

// class to handle matrix 3d
template <class T>
class Matrix3d
{
private:
    T** m_data;

public:
    Matrix3d() {
        m_data = new T * [3];
        for (int i = 0; i < 3; i++)
            m_data[i] = new T[3];
    }
    Matrix3d(const std::initializer_list<std::initializer_list<T>>& list_ext) {
        assert(list_ext.size() == 3);
        m_data = new T * [3];
        for (int i = 0; i < 3; i++)
            m_data[i] = new T[3];
        int i = 0, j = 0;
        for (auto& list_int : list_ext)
        {
            assert(list_int.size() == 3);
            j == 0;
            for (auto& element : list_int)
            {
                m_data[i][j] = element;
                j++;
            }
            i++;
        }
    }

    void erase() {
        for (int i = 0; i < 3; i++)
            delete[] m_data[i];
        delete[] m_data;
        m_data = nullptr;
    }

    const T* operator[](const int r) const {
        assert(r >= 0 && r < 3);
        return m_data[r];
    }

    T* operator[](const int r) {
        assert(r >= 0 && r < 3);
        return m_data[r];
    }

    Matrix3d<T>& operator=(const std::initializer_list<std::initializer_list<T>> list_ext) {
        assert(list_ext.size() == 3);

        this->erase();

        m_data = new T * [3];
        for (int i = 0; i < 3; i++)
            m_data[i] = new T[3];
        int i = 0, j = 0;
        for (auto& list_int : list_ext)
        {
            assert(list_int.size() == 3);
            j = 0;
            for (auto& element : list_int)
            {
                m_data[i][j] = element;
                j++;
            }
            i++;
        }

        return (*this);
    }

    Matrix3d<T>& operator=(const Matrix3d<T>& m) {
        this->erase();

        m_data = new T * [3];
        for (int i = 0; i < 3; i++)
            m_data[i] = new T[3];

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                m_data[i][j] = m[i][j];
        return (*this);
    }

    ~Matrix3d() {
        for (int i = 0; i < 3; i++)
            delete[] m_data[i];
        delete[] m_data;
    }
};

// print details(matrix)
template <typename T>
std::ostream& operator<<(std::ostream& out, Matrix3d<T>& m) {
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
            out << m[r][c] << " ";
        out << "\n";
    }
    return out;
}

// matrix equality check
template <typename T>
bool operator==(Matrix3d<T> m1, Matrix3d<T> m2) {
    int s = 0;
    for (int r = 0; r < m1.getNumRows(); r++)
        for (int c = 0; c < m1.getNumCols(); c++)
            s += (m1[r][c] == m2[r][c]);

    if (s == m1.getNumRows() * m1.getNumCols())
        return true;
    else
        return false;
}

// matrix inequality check
template <typename T>
bool operator!=(Matrix3d<T> m1, Matrix3d<T> m2) {
    int s = 0;
    for (int r = 0; r < m1.getNumRows(); r++)
        for (int c = 0; c < m1.getNumCols(); c++)
            s += (m1[r][c] == m2[r][c]);

    if (s == m1.getNumRows() * m1.getNumCols())
        return false;
    else
        return true;
}

// Matrix addition
template <typename T>
Matrix3d<T> operator+(const Matrix3d<T>& left, const Matrix3d<T>& right) {
    return { {left[0][0] + right[0][0], left[0][1] + right[0][1], left[0][2] + right[0][2]},
            {left[1][0] + right[1][0], left[1][1] + right[1][1], left[1][2] + right[1][2]},
            {left[2][0] + right[2][0], left[2][1] + right[2][1], left[2][2] + right[2][2]} };
}

// Matrix addtion and assignment
template <typename T>
Matrix3d<T>& operator+=(Matrix3d<T>& left, const Matrix3d<T>& right) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            left[r][c] += right[r][c];

    return left;
}

// Matrix subtraction
template <typename T>
Matrix3d<T> operator-(const Matrix3d<T>& left, const Matrix3d<T>& right) {
    return { {left[0][0] - right[0][0], left[0][1] - right[0][1], left[0][2] - right[0][2]},
            {left[1][0] - right[1][0], left[1][1] - right[1][1], left[1][2] - right[1][2]},
            {left[2][0] - right[2][0], left[2][1] - right[2][1], left[2][2] - right[2][2]} };
}

// Matrix subtraction and assignment
template <typename T>
Matrix3d<T>& operator-=(Matrix3d<T>& left, const Matrix3d<T>& right) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            left[r][c] -= right[r][c];

    return left;
}

// Matrix negation
template <typename T>
Matrix3d<T>& operator-(Matrix3d<T>& left) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            left[r][c] = -left[r][c];

    return left;
}

// Matrix Multiplication by scaler and assignment
template <typename T, typename U>
Matrix3d<T>& operator*=(Matrix3d<T>& left, const U& right) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            left[r][c] *= right;
    return left;
}

// Matrix Multplication by scaler by right
template <typename T, typename U>
Matrix3d<T> operator*(const Matrix3d<T>& left, const U& right) {
    return { {left[0][0] * right, left[0][1] * right, left[0][2] * right},
            {left[1][0] * right, left[1][1] * right, left[1][2] * right},
            {left[2][0] * right, left[2][1] * right, left[2][2] * right} };
}

// Matrix Multplication by scaler by left
template <typename T, typename U>
Matrix3d<T> operator*(const U& left, const Matrix3d<T>& right) {
    return { {left * right[0][0], left * right[0][1], left * right[0][2]},
            {left * right[1][0], left * right[1][1], left * right[1][2]},
            {left * right[2][0], left * right[2][1], left * right[2][2]} };
}

// Matrix Multiplication
template <typename T>
Matrix3d<T> operator*(Matrix3d<T>& left, Matrix3d<T>& right) {
    T _00 = left[0][0] * right[0][0] + left[0][1] * right[1][0] + left[0][2] * right[2][0];
    T _01 = left[0][0] * right[0][1] + left[0][1] * right[1][1] + left[0][2] * right[2][1];
    T _02 = left[0][0] * right[0][2] + left[0][1] * right[1][2] + left[0][2] * right[2][2];

    T _10 = left[1][0] * right[0][0] + left[1][1] * right[1][0] + left[1][2] * right[2][0];
    T _11 = left[1][0] * right[0][1] + left[1][1] * right[1][1] + left[1][2] * right[2][1];
    T _12 = left[1][0] * right[0][2] + left[1][1] * right[1][2] + left[1][2] * right[2][2];

    T _20 = left[2][0] * right[0][0] + left[2][1] * right[1][0] + left[2][2] * right[2][0];
    T _21 = left[2][0] * right[0][1] + left[2][1] * right[1][1] + left[2][2] * right[2][1];
    T _22 = left[2][0] * right[0][2] + left[2][1] * right[1][2] + left[2][2] * right[2][2];

    return { {_00, _01, _02}, {_10, _11, _12}, {_20, _21, _22} };
}

// devide and assignment of matrix by scaler
template <typename T, typename U>
Matrix3d<T>& operator/=(Matrix3d<T>& left, U right) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            left[r][c] /= right;
    return left;
}

// divide operator of matrix by scaler
template <typename T, typename U>
Matrix3d<T> operator/(Matrix3d<T> left, U right) {
    return { {left[0][0] / right, left[0][1] / right, left[0][2] / right},
            {left[1][0] / right, left[1][1] / right, left[1][2] / right},
            {left[2][0] / right, left[2][1] / right, left[2][2] / right} };
}

// magnitude of vector
template <typename V2>
float Magnitude(const V2& v) {
    return sqrt(static_cast<float>(v.x * v.x + v.y * v.y));
}

// return unitvector
template <typename V2>
V2 UnitVector(const V2& v) {
    return v / Magnitude;
}

// vector magnitude comparison
template <typename V2>
bool operator<(const V2& v1, const V2& v2) {
    if (Magnitude(v1) < Magnitude(v2))
        return true;
    return false;
}

// vector magnitude comparison
template <typename V2>
bool operator>(const V2& v1, const V2& v2) {
    if (Magnitude(v1) > Magnitude(v2))
        return true;
    return false;
}

// 3d Vector Math
template <typename T>
sf::Vector3<T> operator*(const Matrix3d<T>& m, const sf::Vector3<T>& v) {
    return sf::Vector3<T>(
        m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
        m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
        m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
}