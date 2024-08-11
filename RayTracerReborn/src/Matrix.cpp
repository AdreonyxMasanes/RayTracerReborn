#include "Matrix.hpp"


//TODO REFORMAT WITH CONST CORRECTNESS USING CONST CASTING?
Matrix::Matrix() 
  :m_height(4), m_width(4) {
  for (int row = 0; row < Height(); row++) {
    std::vector<float> temp;
    for (int col = 0; col < Width(); col++) {
      temp.push_back(1.0f);
    }
    m_matrix.push_back(temp);
  }
}

Matrix::Matrix(float height, float width) 
  : m_height(height), m_width(width) {
  for (int row = 0; row < Height(); row++) {
    std::vector<float> temp;
    for (int col = 0; col < Width(); col++) {
      temp.push_back(1.0f);
    }
    m_matrix.push_back(temp);
  }
}

Matrix::Matrix(float zero_zero, float zero_one, float zero_two, float zero_three,
  float one_zero, float one_one, float one_two, float one_three, 
  float two_zero,float two_one, float two_two, float two_three, 
  float three_zero, float three_one, float three_two, float three_three) : Matrix(4.0f, 4.0f) {
  ModifyMatrix()[0][0] = zero_zero;
  ModifyMatrix()[0][1] = zero_one;
  ModifyMatrix()[0][2] = zero_two;
  ModifyMatrix()[0][3] = zero_three;

  ModifyMatrix()[1][0] = one_zero;
  ModifyMatrix()[1][1] = one_one;
  ModifyMatrix()[1][2] = one_two;
  ModifyMatrix()[1][3] = one_three;

  ModifyMatrix()[2][0] = two_zero;
  ModifyMatrix()[2][1] = two_one;
  ModifyMatrix()[2][2] = two_two;
  ModifyMatrix()[2][3] = two_three;

  ModifyMatrix()[3][0] = three_zero;
  ModifyMatrix()[3][1] = three_one;
  ModifyMatrix()[3][2] = three_two;
  ModifyMatrix()[3][3] = three_three;

}

Matrix::Matrix(float zero_zero, float zero_one, float zero_two,
  float one_zero, float one_one, float one_two,
  float two_zero, float two_one, float two_two) : Matrix(3.0f, 3.0f) {
  ModifyMatrix()[0][0] = zero_zero;
  ModifyMatrix()[0][1] = zero_one;
  ModifyMatrix()[0][2] = zero_two;

  ModifyMatrix()[1][0] = one_zero;
  ModifyMatrix()[1][1] = one_one;
  ModifyMatrix()[1][2] = one_two;

  ModifyMatrix()[2][0] = two_zero;
  ModifyMatrix()[2][1] = two_one;
  ModifyMatrix()[2][2] = two_two;
}

Matrix::Matrix(float zero_zero, float zero_one,
  float one_zero, float one_one) : Matrix(2.0f, 2.0f) {
  ModifyMatrix()[0][0] = zero_zero;
  ModifyMatrix()[0][1] = zero_one;

  ModifyMatrix()[1][0] = one_zero;
  ModifyMatrix()[1][1] = one_one;
}

float Matrix::Width() const {
  return m_width;
}

float Matrix::Height() const {
  return m_height;
}

const std::vector<std::vector<float>>& Matrix::GetMatrix() const {
  return m_matrix;
}

std::vector<std::vector<float>>& Matrix::ModifyMatrix()  {
  return m_matrix;
}


void Matrix::SetHeight(float height) {
  m_height = height;
}

void Matrix::SetWidth(float width) {
  m_width = width;
}


Matrix Matrix::Transpose() {
  return Matrix(
    m_matrix[0][0], m_matrix[1][0], m_matrix[2][0], m_matrix[3][0],
    m_matrix[0][1], m_matrix[1][1], m_matrix[2][1], m_matrix[3][1],
    m_matrix[0][2], m_matrix[1][2], m_matrix[2][2], m_matrix[3][2],
    m_matrix[0][3], m_matrix[1][3], m_matrix[2][3], m_matrix[3][3]
  );
}

bool Matrix::operator==(const Matrix& rhs)  const {
  if (Height() == rhs.Height() && Width() == rhs.Width()) {
    for (int row = 0; row < Height(); row++) {
      for (int col = 0; col < Width(); col++) {
        if (!(Utility::FloatsAreEqual(m_matrix[row][col], rhs.GetMatrix()[row][col]))) {
          return false;
        }
      }
    }
    return true;
  } else {
    std::cout << "CAN'T COMPARE MATRICIES OF DIFFERENT DIMENSIONS" << std::endl;
    return false;
  }
  
}
// MAYBE MAKE SO IT WORKS WITH MORE THAN ONE SIZE OF MATRIX
// USED FOR MAT4 MATRICIES ONLY
// CHECK FOR NULLPTR UPON RETURN
Matrix Matrix::operator*(const Matrix& rhs) const{
  if (!(Height() == rhs.Height())) {
    std::cout << "MATRICIES ARE NOT THE SAME SIZE" << std::endl;
  } else {
    Matrix result;
    for (int row = 0; row < Height(); row++) {
      for (int col = 0; col < Width(); col++) {
        result.ModifyMatrix()[row][col] =
          (m_matrix[row][0] * rhs.GetMatrix()[0][col]) +
          (m_matrix[row][1] * rhs.GetMatrix()[1][col]) +
          (m_matrix[row][2] * rhs.GetMatrix()[2][col]) +
          (m_matrix[row][3] * rhs.GetMatrix()[3][col]);
      }
    }
    return result;
  }
}
// ONLY FOR MAT4 
Tuple Matrix::operator*(const Tuple& rhs) const{
  Matrix result(4.0, 1.0f);
  for (int row = 0; row < result.Height(); row++) {
    for (int col = 0; col < result.Width(); col++) {
      result.ModifyMatrix()[row][col] =
        GetMatrix()[row][0] * rhs.X() +
        GetMatrix()[row][1] * rhs.Y() +
        GetMatrix()[row][2] * rhs.Z() +
        GetMatrix()[row][3] * rhs.W();
    }
  }
  return Tuple(result.GetMatrix()[0][0], result.GetMatrix()[1][0], result.GetMatrix()[2][0], result.GetMatrix()[3][0]);
}

Matrix& Matrix::operator=(const Matrix& rhs) {
  for (int row = 0; row < Height(); row++) {
    for (int col = 0; col < Width(); col++) {
      m_matrix[row][col] = rhs.GetMatrix()[row][col];
    }
  }
  return *this;
}

float Matrix::Determinant() const{
  float result = 0;

  if (Width() == 2) {
    return m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];
  } else {
    for (int col = 0; col < Width(); col++) {
      result += GetMatrix()[0][col] * Cofactor(0, col);
    }
  }
  return result;
}

Matrix Matrix::Submatrix(float row, float col) const{
  // DONT WANT TO MODIFY ORIGINAL MATRIX SO CREATE A COPY
  Matrix temp = *this;
  // Erase rows and colums from matrix.
  temp.ModifyMatrix().erase(temp.GetMatrix().begin() + row);
  for (auto& row : temp.ModifyMatrix()) {
    row.erase(row.begin() + col);
  }
  // Change the Size variables. COULD ALSO MAKE THE PRINT FUNCTION JUST USE .SIZE BUT THIS FUNCTIONS THE SAME o.O
  temp.SetHeight(temp.Height() - 1);
  temp.SetWidth(temp.Width() - 1);

  return temp;
}

float Matrix::Minor(float row, float col) const{
  Matrix sub = Submatrix(row, col);
  return sub.Determinant();
}

float Matrix::Cofactor(float row, float col) const{
  float result;
  if ((static_cast<int>(row) + static_cast<int>(col)) % 2 == 0) {
    result = Minor(row, col);
    return result;
  } else {
    result = -(Minor(row, col));
    return result;
  }
}

Matrix Matrix::Invert() const{
  Matrix result = Matrix(Height(), Width());
  float determinant = Determinant();
  if (!(determinant == 0)) {
    for (int row = 0; row < Height(); row++) {
      for (int col = 0; col < Width(); col++) {
        float c = Cofactor(row, col);
        result.ModifyMatrix()[col][row] = c / determinant;
      }
    }
  } /*else {
    std::cout << "Matrix is invertible " << std::endl;
    return nullptr;
  }*/
  return result;
}

void Matrix::Print() const {
  for (int row = 0; row < Height(); row++) {
    for (int col = 0; col < Width(); col++) {
      if (!(col == Width() - 1.0f)) {
        std::cout << GetMatrix()[row][col] << ", ";
      } else {
        std::cout << GetMatrix()[row][col] << std::endl;
      }
    }
  }
}
