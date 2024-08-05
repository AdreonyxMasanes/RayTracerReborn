#include "Matrix.hpp"

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

Matrix::Matrix(float width, float height) 
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
  GetMatrix()[0][0] = zero_zero;
  GetMatrix()[0][1] = zero_one;
  GetMatrix()[0][2] = zero_two;
  GetMatrix()[0][3] = zero_three;

  GetMatrix()[1][0] = one_zero;
  GetMatrix()[1][1] = one_one;
  GetMatrix()[1][2] = one_two;
  GetMatrix()[1][3] = one_three;

  GetMatrix()[2][0] = two_zero;
  GetMatrix()[2][1] = two_one;
  GetMatrix()[2][2] = two_two;
  GetMatrix()[2][3] = two_three;

  GetMatrix()[3][0] = three_zero;
  GetMatrix()[3][1] = three_one;
  GetMatrix()[3][2] = three_two;
  GetMatrix()[3][3] = three_three;

}

Matrix::Matrix(float zero_zero, float zero_one, float zero_two,
  float one_zero, float one_one, float one_two,
  float two_zero, float two_one, float two_two) : Matrix(3.0f, 3.0f) {
  GetMatrix()[0][0] = zero_zero;
  GetMatrix()[0][1] = zero_one;
  GetMatrix()[0][2] = zero_two;

  GetMatrix()[1][0] = one_zero;
  GetMatrix()[1][1] = one_one;
  GetMatrix()[1][2] = one_two;

  GetMatrix()[2][0] = two_zero;
  GetMatrix()[2][1] = two_one;
  GetMatrix()[2][2] = two_two;
}

Matrix::Matrix(float zero_zero, float zero_one,
  float one_zero, float one_one) : Matrix(2.0f, 2.0f) {
  GetMatrix()[0][0] = zero_zero;
  GetMatrix()[0][1] = zero_one;

  GetMatrix()[1][0] = one_zero;
  GetMatrix()[1][1] = one_one;
}

float Matrix::Width() {
  return m_width;
}

float Matrix::Height() {
  return m_height;
}

std::vector<std::vector<float>>& Matrix::GetMatrix() {
  return m_matrix;
}

bool Matrix::operator==(Matrix& rhs)  {
  if (Height() == rhs.Height() && Width() == rhs.Width()) {
    for (int row = 0; row < Height(); row++) {
      for (int col = 0; col < Width(); col++) {
        if (!(Utility::FloatsAreEqual(GetMatrix()[row][col], rhs.GetMatrix()[row][col]))) {
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

void Matrix::Print() {
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

void Matrix::RunTest() {
  CreationTest();
  if (!(EqualityTest())) {
    return;
  } else {
    std::cout << "MATRICIES TEST PASSED" << std::endl;
  }
}

void Matrix::CreationTest() {
  Matrix mat_4(
    1.0f , 2.0f , 3.0f , 4.0f,
    5.5f , 6.5f , 7.5f , 8.5f,
    9.0f , 10.0f, 11.0f, 12.0f,
    13.5f, 14.5f, 15.5f, 16.f);
  std::cout << "MAT4: " << std::endl;
  mat_4.Print();

  Matrix mat_3(
    -3.0f, 5.0f,  0.0f,
    1.0f ,-2.0f, -7.0f, 
    0.0f , 1.0f, 1.0f);
  std::cout << "MAT3: " << std::endl;
  mat_3.Print();

  Matrix mat_2(
    -3.0f,  5.0f,
     1.0f, -2.0f);
  std::cout << "MAT2: " << std::endl;
  mat_2.Print();
}

bool Matrix::EqualityTest() {
  Matrix mat_4_a(
    1.0f, 2.0f, 3.0f, 4.0f,
    5.5f, 6.5f, 7.5f, 8.5f,
    9.0f, 10.0f, 11.0f, 12.0f,
    13.5f, 14.5f, 15.5f, 16.f);
  Matrix mat_4_b(
    1.0f, 2.0f, 3.0f, 4.0f,
    5.5f, 6.5f, 7.5f, 8.5f,
    9.0f, 10.0f, 11.0f, 12.0f,
    13.5f, 14.5f, 15.5f, 16.f);
  if (!(mat_4_a == mat_4_b)) {
    std::cout << "MAT EQUALITY TEST FAILED" << std::endl;
    return false;
  }

  
  mat_4_b.GetMatrix()[0][0] = 0.0f;
  if ((mat_4_a == mat_4_b)) {
    std::cout << "MAT EQUALITY TEST 2 FAILED" << std::endl;
    return false;
  }


  Matrix mat_3(
    -3.0f, 5.0f, 0.0f,
    1.0f, -2.0f, -7.0f,
    0.0f, 1.0f, 1.0f);
  if ((mat_3 == mat_4_a)) {
    std::cout << "MAT EQUALITY TEST 3 FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}
