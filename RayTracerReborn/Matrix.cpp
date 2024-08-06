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

std::unique_ptr<Matrix> Matrix::GetIdentityMatrix() {
  return std::make_unique<Matrix>(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
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
// MAYBE MAKE SO IT WORKS WITH MORE THAN ONE SIZE OF MATRIX
// USED FOR MAT4 MATRICIES ONLY
// CHECK FOR NULLPTR UPON RETURN
std::unique_ptr<Matrix> Matrix::operator*(Matrix& rhs) {
  if (!(Height() == rhs.Height())) {
    std::cout << "MATRICIES ARE NOT THE SAME SIZE" << std::endl;
    return nullptr;
  } else {
    std::unique_ptr<Matrix> result = std::make_unique<Matrix>();
    for (int row = 0; row < Height(); row++) {
      for (int col = 0; col < Width(); col++) {
        result->GetMatrix()[row][col] =
          (GetMatrix()[row][0] * rhs.GetMatrix()[0][col]) +
          (GetMatrix()[row][1] * rhs.GetMatrix()[1][col]) +
          (GetMatrix()[row][2] * rhs.GetMatrix()[2][col]) +
          (GetMatrix()[row][3] * rhs.GetMatrix()[3][col]);
      }
    }
    return result;
  }
}
// ONLY FOR MAT4 
std::unique_ptr<Tuple> Matrix::operator*(Tuple& rhs) {
  if (!(Height() == 4.0f)) {
    std::cout << "MATRICIES MULTIPLICATION ONLY AVAILABLE FOR MAT4" << std::endl;
    return nullptr;
  } else {
    Matrix result(4.0, 1.0f);
    for (int row = 0; row < result.Height(); row++) {
      for (int col = 0; col < result.Width(); col++) {
        result.GetMatrix()[row][col] =
          GetMatrix()[row][0] * rhs.X() +
          GetMatrix()[row][1] * rhs.Y() +
          GetMatrix()[row][2] * rhs.Z() +
          GetMatrix()[row][3] * rhs.W();
      }
    }
    return std::make_unique<Tuple>(result.GetMatrix()[0][0], result.GetMatrix()[1][0], result.GetMatrix()[2][0], result.GetMatrix()[3][0]);
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
  } else if (!(MatrixMultiplyTest())) {
    return;
  } else if (!(MatrixMultiplyByTupleTest())) {
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

bool Matrix::MatrixMultiplyTest() {
  Matrix mat_4_a(
     1.0f, 2.0f, 3.0f, 4.0f,
     5.0f, 6.0f, 7.0f, 8.0f,
     9.0f, 8.0f, 7.0f, 6.0f,
     5.0f, 4.0f, 3.0f, 2.0f);
  Matrix mat_4_b(
    -2.0f, 1.0f, 2.0f,  3.0f,
     3.0f, 2.0f, 1.0f, -1.0f,
     4.0f, 3.0f, 6.0f,  5.0f,
     1.0f, 2.0f, 7.0f,  8.0f);

  Matrix mat_4_solution(
     20.0f, 22.0f, 50.0f , 48.0f ,
     44.0f, 54.0f, 114.0f, 108.0f,
     40.0f, 58.0f, 110.0f, 102.0f,
     16.0f, 26.0f, 46.0f , 42.0f);

  std::unique_ptr<Matrix> result = mat_4_a * mat_4_b;
  if (!(*result == mat_4_solution)) {
    std::cout << "MULTIPLY MATRICIES TEST  FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Matrix::MatrixMultiplyByTupleTest() {
  Matrix mat_4_a(
    1.0f, 2.0f, 3.0f, 4.0f,
    2.0f, 4.0f, 4.0f, 2.0f,
    8.0f, 6.0f, 4.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f);
  Tuple test_t(1.0f, 2.0f, 3.0f, 1.0f);
  Tuple test_solution_t(18.0f, 24.0f, 33.0f, 1.0f);
  std::unique_ptr<Tuple> result = mat_4_a * test_t;

  if (!(*result == test_solution_t)) {
    std::cout << "MULTIPLY MATRICIES TEST  FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}
