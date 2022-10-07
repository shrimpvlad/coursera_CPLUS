#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

#include <vector>
#include <iostream>

using namespace std;

class Matrix
{
public:
  Matrix()
  {

    rows = 0;
    cols = 0;
  }
  Matrix(int num_rows, int num_cols)
  {
    Reset(num_rows, num_cols);
  }
  void Reset(int num_rows, int num_cols)
  {
    if (num_rows < 0)
    {
      throw out_of_range("num_rows must be >= 0");
    }
    if (num_cols < 0)
    {
      throw out_of_range("num_columns must be >= 0");
    }
    if (num_rows == 0 || num_cols == 0)
    {
      rows = cols = 0;
    }
    else
    {
      rows = num_rows;
      cols = num_cols;
      matrix.assign(num_rows, vector<int>(num_cols));
    }
  }
  int &At(int row, int col)
  {
    // if (row < 0 || row > rows)
    //   throw out_of_range("your element doesnt exist");
    // if (col < 0 || col > cols)
    //   throw out_of_range("this col doesnt exist");
    return matrix.at(row).at(col);
  }
  int At(int row, int col) const
  {
    // if (row < 0 || row > rows)
    //   throw out_of_range("your element doesnt exist");
    // if (col < 0 || col > cols)
    //   throw out_of_range("this col doesnt exist");
    return matrix.at(row).at(col);
  }

  int GetNumColumns() const
  {
    return cols;
  }
  int GetNumRows() const
  {
    return rows;
  }

private:
  int rows;
  int cols;
  vector<vector<int> > matrix;
};

istream &operator>>(istream &in, Matrix &matrix)
{
  int num_rows, num_columns;
  in >> num_rows >> num_columns;

  matrix.Reset(num_rows, num_columns);
  for (int row = 0; row < num_rows; ++row)
  {
    for (int column = 0; column < num_columns; ++column)
    {
      in >> matrix.At(row, column);
    }
  }

  return in;
}

ostream &operator<<(ostream &out, const Matrix matrix)
{
  out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
  for (int row = 0; row < matrix.GetNumRows(); ++row)
  {
    for (int column = 0; column < matrix.GetNumColumns(); ++column)
    {
      out << matrix.At(row, column) << " ";
    }
    out << endl;
  }

  return out;
}

bool operator==(const Matrix &matr1, const Matrix &matr2)
{
  if (matr1.GetNumRows() != matr2.GetNumRows() || matr1.GetNumColumns() != matr2.GetNumColumns())
    return false;
  else
  {
    for (int i = 0; i < matr1.GetNumRows(); ++i)
    {
      for (int j = 0; j < matr1.GetNumColumns(); ++j)
        if (matr1.At(i, j) != matr2.At(i, j))
          return false;
    }
  }
  return true;
}
Matrix operator+(const Matrix &matr1, const Matrix &matr2)
{
  if (matr1.GetNumRows() != matr2.GetNumRows() || matr1.GetNumColumns() != matr2.GetNumColumns())
    throw invalid_argument("oooops");
  else
  {
    Matrix new_matrix(matr1.GetNumRows(), matr1.GetNumColumns());
    for (int i = 0; i < matr1.GetNumRows(); ++i)
    {
      for (int j = 0; j < matr1.GetNumColumns(); ++j)
        new_matrix.At(i, j) = matr1.At(i, j) + matr2.At(i, j);
    }
    return new_matrix;
  }
}

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix

int main()
{
  Matrix one;
  Matrix two;
  // cin >> one;
  // cout>>one;
  cin >> one >> two;
  cout << one + two << endl;
  return 0;
}
