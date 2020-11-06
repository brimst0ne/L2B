// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "utmatrix.h"
#include <iomanip>
//---------------------------------------------------------------------------

int main()
{
    TMatrix<int> a(5), b(5), c(5), d(5), e(5);
  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки представления треугольных матриц" << endl;
  for (int i = 0; i < 5; i++)
    for (int j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      d[i][j] = i * 10 + j;
      b[i][j] = (i * 10 + j) * 100;
    }
  c = a + b;
  e = b - a;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;
  cout << "Matrix e = b - a" << endl << e << endl;
  cout << d << endl;
  d.ToLower();
  return 0;
}
//---------------------------------------------------------------------------
