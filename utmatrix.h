// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include <exception>
#include <vector>
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);          // одновременно конструктор по умолчанию
                                            // и конструктор с параметрами
  TVector(const TVector &v); 
  TVector(TVector &&v);// конструктор копирования
  ~TVector();
  int GetSize()   const   { return Size;       } // размер вектора
  int GetStartIndex()const{ return StartIndex; }
  void SetSize(int x)
  {
	  Size = x;
  }
  void SetStartIndex(int x)
  {
	  StartIndex = x;
  }
  ValType* GetVector()const { return pVector; }// индекс первого элемента
  ValType& operator[](int pos); 
  ValType& operator[](int pos) const;// доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение
  int FindIndex()
  {
	  for (int i = (*this).GetStartIndex(); i < (*this).GetSize(); i++)
	  {
		  if (((*this)[i] != 0))return i;
	  }
	  return -1;
  }
 
  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size-v.StartIndex; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
	  for (int i = 0; i < v.Size - v.StartIndex; i++) {
		  out << v.pVector[i] << ' ';
	  }
	out << endl;
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if ((s < 0) || (si < 0) || (s > MAX_VECTOR_SIZE)) throw logic_error("Wrong size");
	pVector = new ValType[s];
	for (int i = 0; i < s; i++)
	{
		pVector[i] = 0;
	}
	StartIndex = si;
	Size = s;
} 

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	
	pVector = new ValType[v.Size];
	for (int i = 0; i < v.Size; i++)
	{
		pVector[i] = v.pVector[i];
	}
	StartIndex = v.StartIndex;
	Size = v.Size;
} 
template <class ValType> //конструктор копирования
TVector<ValType>::TVector( TVector<ValType> &&v)
{

	pVector =v.pVector;
	v.pVector = nullptr;
	StartIndex = v.StartIndex;
	Size = v.Size;
} 
template <class ValType>
TVector<ValType>::~TVector()
{
	if (pVector != nullptr) {
		delete[]pVector;
	}
} 

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos < StartIndex) || (pos < 0) || (pos > Size + StartIndex)) throw logic_error("Invalid index");
    return pVector[pos - StartIndex];
} 
template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)const
{
	if ((pos < StartIndex) || (pos < 0) || (pos > Size + StartIndex)) throw logic_error("Invalid index");
	return pVector[pos - StartIndex];
} 

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (this == &v)return 1;

	if ((this->GetSize() == v.GetSize()) && (this->GetStartIndex() == v.GetStartIndex()))
	{
		for (int i = 0; i < v.GetSize(); i++)
		{
			if (this->pVector[i] != v.pVector[i])
			{
				return 0;
			}
			return 1;
		}
	}
	return 0;
}

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
    return !(*this==v);
} 

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this == &v)
	{
		return (*this);
	}
	if (this->GetSize() == v.GetSize())
	{
		for (int i = 0; i < v.Size; i++)
		{
			pVector[i] = v.pVector[i];
		}
		Size = v.Size;
		StartIndex = v.StartIndex;
		return (*this);
	}
    delete []pVector;
	pVector = new ValType[v.Size];
	for (int i = 0; i < v.Size; i++)
	{
		pVector[i] = v.pVector[i];
	}
	Size = v.Size;
	StartIndex = v.StartIndex;
	return (*this);
} 

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size; i++)
	{
		res.pVector[i] += val;
	}
	return res;
} 

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size; i++)
	{
		res.pVector[i] -= val;
	}
	return res;
} 

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size; i++)
	{
		res.pVector[i] *= val;
	}
	return res;
}

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (this->GetSize() != v.GetSize()) throw logic_error("");
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size; i++)
	{
		res.pVector[i] =res.pVector[i]+ v.pVector[i];
	}
	return res;
} 

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (this->GetSize() != v.GetSize()) throw logic_error("");
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size; i++)
	{
		res.pVector[i] = res.pVector[i] - v.pVector[i];
	}
	return res;
} 

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (this->GetSize() != v.GetSize()) throw logic_error("");
	float res = 0;
	for (int i = 0; i < v.Size; i++)
	{
		res = res + v.pVector[i]*this->pVector[i];
	}
	return sqrt(res);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------

// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание
  //TMatrix( TVector<TVector<ValType> >&& mt);
  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
  void ToLower();  /////
  TMatrix RegularToLower();
  TMatrix RegularToUpper();
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	/*if (s > MAX_MATRIX_SIZE) throw logic_error("Wrong size");
	for (int i = 0; i < this->Size; i++)
	{
		TVector<ValType>res(s, i);                     //Первоначальный вариант
		this->pVector[i] = res;
	}*/
	if (s > MAX_MATRIX_SIZE) throw logic_error("Wrong size");
	for (int i = 0; i < this->Size; i++)
	{
		TVector<ValType>res(s, 0);
		this->pVector[i] = res;
	}
}

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) 
{
	for (int i = this->StartIndex; i < this->Size; i++)     ////
	{
		TVector<ValType>res(mt[i]);
		(*this)[i] = res;
	}

}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) 
{
	for (int i = (*this).GetStartIndex(); i < (*this).GetSize(); i++)    ////
	{
		TVector<ValType>ms(mt[i]);
		(*this)[i] = ms;
	}

}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this == &mt) return 1;

	if (((*this).GetStartIndex() == mt.GetStartIndex()) && ((*this).GetSize() == mt.GetSize()))
	{
		for (int i = mt.GetStartIndex(); i < mt.GetSize(); i++)   ////
		{
			if ((*this)[i] != mt[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
} 

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !((*this) == mt);
} 

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (&mt == this)
	{
		return (*this);
	}
	if (this->GetSize() == mt.GetSize())
	{
		for (int i = 0; i < this->Size; i++)
		{
			(*this).pVector[i] = mt.pVector[i];
		}
		return(*this);
	}
	delete[]pVector;
	pVector = new TVector<ValType>[mt.Size];

	(*this).Size = mt.Size;
	(*this).StartIndex = mt.StartIndex;
	for (int i = (*this).GetStartIndex(); i < (*this).GetSize(); i++)    ////
	{
		(*this)[i] = mt[i];
	}
	return (*this);
} 

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    // благодаря наследованию от TVector<TVector<ValType> > operator+
    // уже есть, надо только его вызвать
	if (mt.Size != (*this).GetSize()) throw logic_error("incorrect size");
	TMatrix<ValType>Res(*this);
	for (int i = Res.GetStartIndex(); i < Res.GetSize(); i++)    ////
	{
		Res[i] = (*this)[i] + mt[i];
	}
	return Res;
} 

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (mt.GetSize() != (*this).GetSize()) throw logic_error("incorrect size");
	TMatrix<ValType>Res(*this);
	for (int i = Res.GetStartIndex(); i < Res.GetSize(); i++)    ////
	{
		Res[i] = (*this)[i] - mt[i];
	}
	return Res;
}
//template<class ValType>
//inline void TMatrix<ValType>::ToLower()
//{
//	vector<ValType> vec;
//	ValType var = 0;
//	TMatrix<ValType> res(*this);
//	for (int i = res.GetStartIndex(); i < res.GetSize(); i++) {
//		TVector<ValType> row(i + 1, 0);
//		res.pVector[i] = row;
//		//res[i] = row;
//	}
//	//cout << res << endl;
//	for (int i = (*this).GetStartIndex(); i < (*this).GetSize(); i++) {
//		//cout << (*this)[i] << endl;
//		for (int j = i; j < this->pVector->GetSize(); j++) {
//			var = (*this)[i][j];
//			//cout << var << " ";
//			vec.push_back(var);
//			//cout << (*this)[i][j] << " ";
//		}
//	}
//	for (int i = res.GetStartIndex(); i < res.GetSize(); i++) {
//		for (int j = 0; j < res[i].GetSize(); j++) {
//			res[i][j] = (*this)[j][i];
//			//cout << res[i][j] << " ";
//		}
//		
//	}
//	cout << res << endl;
//}

template<class ValType>
inline TMatrix<ValType> TMatrix<ValType>::RegularToLower()
{
	//TMatrix tmp(this->Size);
	//for (int i = 0; i < this->Size; i++) {
	//	TVector<ValType> res(i + 1, 0);
	//	tmp.pVector[i] = res;
	//}
	//for (int i = 0; i < tmp.Size; i++) {
	//	for (int j = 0; j < tmp.pVector->GetSize(); j++) {
	//		tmp[i][j] = 5;
	//	}
	//}
	///*for (int i = 0; i < tmp.Size; i++) {
	//	tmp[i] = (*this)[i];
	//}*/
	//for (int i = 0; i < tmp.Size; i++) {
	//	for (int j = 0; j < tmp[i].GetSize(); j++) {
	//		tmp[i][j] = i * 10 + j;
	//	}
	//}
	//cout << tmp << endl;
	//return tmp;

	TMatrix tmp(this->Size);
	for (int i = 0; i < this->Size; i++)
	{
		TVector<ValType>res(i + 1, 0);
		tmp.pVector[i] = res;
	}
	for (int i = 0; i < this->Size; i++) {
		vector<ValType> vec;
		for (int j = 0; j < (*this)[i].GetSize(); j++) {
			vec.push_back((*this)[i][j]);
		}
		/*for (int q = 0; q < vec.size(); q++) {
			cout << vec.at(q) << endl;
			cout << endl;
		}*/
		vec.resize(tmp[i].GetSize());
		for (int k = 0; k < tmp[i].GetSize(); k++) {
			tmp[i][k] = vec.at(k);
		}
	}
	return tmp;
}

template<class ValType>
inline TMatrix<ValType> TMatrix<ValType>::RegularToUpper()
{
	TMatrix tmp(this->Size);
	for (int i = 0; i < this->Size; i++)
	{
		TVector<ValType>res(this->Size, i);
		tmp.pVector[i] = res;
	}
	for (int i = 0; i < this->Size; i++) {
		vector<ValType> vec;
		for (int j = (*this)[i].GetSize() - 1; j >= 0; j--) {
			vec.push_back((*this)[i][j]);
		}
		/*for (int q = 0; q < vec.size(); q++) {
			cout << vec.at(q) << endl;
			cout << endl;
		}*/
		vec.resize(tmp[i].GetSize() - tmp[i].GetStartIndex());
		reverse(vec.begin(), vec.end());
		for (int k = tmp[i].GetStartIndex(); k < tmp[i].GetSize(); k++) {
			tmp[i][k] = vec.at(k - tmp[i].GetStartIndex());
		}
	}
	return tmp;
}





/*template <class ValType> // транспонирование матрицы, кастомный метод
TMatrix<ValType>::TMatrix( TVector<TVector<ValType> > &&mt):TVector<TVector<ValType> >(move(mt))
{
	
	bool f = true;
	for (int i = 0; i < (*this).GetSize(); i++)
	{
		if ((*this)[i][i] == 0)
		{
			int j = -1;
			int k = i+1;
			while ((j == -1) && (k < (*this).GetSize()))
			{
				if((*this)[k][i]!=0)j = k;
				k++;
			}
			
			if (j != -1)
			{
				swap((*this)[i], (*this)[j]);
				f = true;
			}
			else
			{
				f = false;
				
			}
		}
		
		if (f) {
			ValType x = 1 / (*this)[i][i];

			(*this)[i] = (*this)[i] * x;
		
			for (int j = i + 1; j < mt.GetSize(); j++)
			{
				(*this)[j] = (*this)[j] - ((*this)[i] * (*this)[j][i]);
			}
		
		}
		

	}
	cout << (*this);
	for (int i = (*this).GetStartIndex(); i < (*this).GetSize(); i++)   ////
	{
		for (int j = i; j < (*this).GetSize(); j++)
		{
			(*this)[i][j - i] = move((*this)[i][j]);
		}
		
		(*this)[i].SetStartIndex(i);
	}

} */
// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
