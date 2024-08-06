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

void Matrix::SetHeight(float height) {
  m_height = height;
}

void Matrix::SetWidth(float width) {
  m_width = width;
}

std::unique_ptr<Matrix> Matrix::GetIdentityMatrix() {
  return std::make_unique<Matrix>(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}

std::unique_ptr<Matrix> Matrix::Transpose() {
  return std::make_unique<Matrix>(
    GetMatrix()[0][0], GetMatrix()[1][0], GetMatrix()[2][0], GetMatrix()[3][0],
    GetMatrix()[0][1], GetMatrix()[1][1], GetMatrix()[2][1], GetMatrix()[3][1],
    GetMatrix()[0][2], GetMatrix()[1][2], GetMatrix()[2][2], GetMatrix()[3][2],
    GetMatrix()[0][3], GetMatrix()[1][3], GetMatrix()[2][3], GetMatrix()[3][3]
  );
}

std::unique_ptr<Matrix> Matrix::TranslationMatrix(float x, float y, float z) {
  return std::make_unique<Matrix>(
    1.0f, 0.0f, 0.0f, x,
    0.0f, 1.0f, 0.0f, y,
    0.0f, 0.0f, 1.0f, z,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}

std::unique_ptr<Matrix> Matrix::ScalingMatrix(float x, float y, float z) {
  return std::make_unique<Matrix>(
    x, 0.0f, 0.0f, 0.0f,
    0.0f, y, 0.0f, 0.0f,
    0.0f, 0.0f, z, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}

std::unique_ptr<Matrix> Matrix::RotationXMatrix(float radians) {
  return std::make_unique<Matrix>(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, cosf(radians), -sinf(radians), 0.0f,
    0.0f, sinf(radians), cosf(radians), 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}

std::unique_ptr<Matrix> Matrix::RotationYMatrix(float radians) {
  return std::make_unique<Matrix>(
    cosf(radians), 0.0f, sinf(radians), 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    -sinf(radians), 0.0f, cosf(radians), 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}

std::unique_ptr<Matrix> Matrix::RotationZMatrix(float radians) {
  return std::make_unique<Matrix>(
    cosf(radians), -sinf(radians), 0.0f, 0.0f,
    sinf(radians), cosf(radians), 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}

std::unique_ptr<Matrix> Matrix::ShearingMatrix(float xy, float xz, float yx, float yz, float zx, float zy) {
  return std::make_unique<Matrix>(
    1.0f,   xy,   xz, 0.0f,
      yx, 1.0f,   yz, 0.0f,
      zx,   zy, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}

std::unique_ptr<Matrix> Matrix::TranformationMatrix(Matrix& first, Matrix& second) {
  return second * first;
}

std::unique_ptr<Matrix> Matrix::TranformationMatrix(Matrix& first, Matrix& second, Matrix& third) {
  return *(third * second) * first;
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

Matrix& Matrix::operator=(Matrix& rhs) {
  for (int row = 0; row < Height(); row++) {
    for (int col = 0; col < Width(); col++) {
      GetMatrix()[row][col] = rhs.GetMatrix()[row][col];
    }
  }
  return *this;
}

float Matrix::Determinant() {
  float result = 0;

  if (Width() == 2) {
    return GetMatrix()[0][0] * GetMatrix()[1][1] - GetMatrix()[0][1] * GetMatrix()[1][0];
  } else {
    for (int col = 0; col < Width(); col++) {
      result += GetMatrix()[0][col] * Cofactor(0, col);
    }
  }
  return result;
}

std::unique_ptr<Matrix> Matrix::Submatrix(float row, float col) {
  // DONT WANT TO MODIFY ORIGINAL MATRIX SO CREATE A COPY
  Matrix temp = *this;
  // Erase rows and colums from matrix.
  temp.GetMatrix().erase(temp.GetMatrix().begin() + row);
  for (auto& row : temp.GetMatrix()) {
    row.erase(row.begin() + col);
  }
  // Change the Size variables. COULD ALSO MAKE THE PRINT FUNCTION JUST USE .SIZE BUT THIS FUNCTIONS THE SAME o.O
  temp.SetHeight(temp.Height() - 1);
  temp.SetWidth(temp.Width() - 1);
  std::unique_ptr<Matrix> result = std::make_unique<Matrix>(temp);
  return result;
}

float Matrix::Minor(float row, float col) {
  std::unique_ptr<Matrix> sub = Submatrix(row, col);
  return sub->Determinant();
}

float Matrix::Cofactor(float row, float col) {
  float result;
  if ((static_cast<int>(row) + static_cast<int>(col)) % 2 == 0) {
    result = Minor(row, col);
    return result;
  } else {
    result = -(Minor(row, col));
    return result;
  }
}

std::unique_ptr<Matrix> Matrix::Invert() {
  std::unique_ptr<Matrix> result = std::make_unique<Matrix>(Height(), Width());

  if (!(Determinant() == 0)) {
    for (int row = 0; row < Height(); row++) {
      for (int col = 0; col < Width(); col++) {
        float c = Cofactor(row, col);
        result->GetMatrix()[col][row] = c / Determinant();
      }
    }
  } else {
    std::cout << "Matrix is invertible " << std::endl;
    return nullptr;
  }
  return result;
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
  } else if (!(TransposeTest())) {
    return;
  } else if (!(DeterimantTest())) {
    return;
  } else if (!(InversionTest())) {
    return;
  } else if (!(TransformTest())) {
    return;
  } else if (!(ShearingTest())) {
    return;
  } else if (!(TranformChainingTest())) {
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
    std::cout << "MULTIPLY MATRICIES BY TUPLE TEST  FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Matrix::TransposeTest() {
  Matrix mat_4_a(
    0.0f, 9.0f, 3.0f, 0.0f,
    9.0f, 8.0f, 0.0f, 8.0f,
    1.0f, 8.0f, 5.0f, 3.0f,
    0.0f, 0.0f, 5.0f, 8.0f);
  Matrix mat_4_solution(
    0.0f, 9.0f, 1.0f, 0.0f,
    9.0f, 8.0f, 8.0f, 0.0f,
    3.0f, 0.0f, 5.0f, 5.0f,
    0.0f, 8.0f, 3.0f, 8.0f);

  std::unique_ptr<Matrix> result = mat_4_a.Transpose();

  if (!(*result == mat_4_solution)) {
    std::cout << "TRANSPOSE MATRICIES TEST  FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Matrix::DeterimantTest() {
  Matrix mat_3(
     1.0f,  2.0f,  6.0f,
    -5.0f,  8.0f, -4.0f,
     2.0f,  6.0f,  4.0f);
  float success = -196.0f;
  float mat_3_determinant = mat_3.Determinant();
  if (!(Utility::FloatsAreEqual(mat_3_determinant, success))) {
    std::cout << "DETERMINANT MAT 3 FAILED" << std::endl;
    return false;
  }

  Matrix mat_4(
    -2.0f, -8.0f,  3.0f,  5.0f,
    -3.0f,  1.0f,  7.0f,  3.0f,
     1.0f,  2.0f, -9.0f,  6.0f,
    -6.0f,  7.0f,  7.0f, -9.0f);
  success = -4071.0f;
  float mat_4_determinant = mat_4.Determinant();
  if (!(Utility::FloatsAreEqual(mat_4_determinant, success))) {
    std::cout << "DETERMINANT MAT 4 FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Matrix::InversionTest() {
  Matrix mat_4_a(
    -4.0f,  2.0f, -2.0f, -3.0f,
     9.0f,  6.0f,  2.0f,  6.0f,
     0.0f, -5.0f,  1.0f, -5.0f,
     0.0f,  0.0f,  0.0f,  0.0f);
  std::unique_ptr<Matrix> mat_4_a_inversion = mat_4_a.Invert();
  if (!(mat_4_a_inversion == nullptr)) {
    std::cout << "INVERSION TEST 1 FAILED" << std::endl;
    return false;
  }

  Matrix mat_4_b(
   -5.0f,  2.0f,  6.0f, -8.0f,
    1.0f, -5.0f,  1.0f,  8.0f,
    7.0f,  7.0f, -6.0f, -7.0f,
    1.0f, -3.0f,  7.0f,  4.0f);
  Matrix mat_4_b_invert_success(
     0.21805f,  0.45113f,  0.24060f, -0.04511f,
    -0.80825f, -1.45677f, -0.44361f,  0.52068f,
    -0.07895f, -0.22368f, -0.05263f,  0.19737f,
    -0.52256f, -0.81391f, -0.30075f,  0.30639f);
  std::unique_ptr<Matrix> mat_4_b_inversion = mat_4_b.Invert();
  if (!(mat_4_b_invert_success == *mat_4_b_inversion)) {
    std::cout << "INVERSION TEST 2 FAILED" << std::endl;
    return false;
  }

  Matrix mat_4_c(
     8.0f,-5.0f, 9.0f, 2.0f,
     7.0f, 5.0f, 6.0f, 1.0f,
    -6.0f, 0.0f, 9.0f, 6.0f,
    -3.0f, 0.0f,-9.0f,-4.0f);
  Matrix mat_4_c_invert_success(
    -0.15385f,-0.15385f,-0.28205f,-0.53846f,
    -0.07692f, 0.12308f, 0.02564f, 0.03077f,
     0.35897f, 0.35897f, 0.43590f, 0.92308f,
    -0.69231f,-0.69231f,-0.76923f,-1.92308f);
  std::unique_ptr<Matrix> mat_4_c_inversion = mat_4_c.Invert();
  if (!(mat_4_c_invert_success == *mat_4_c_inversion)) {
    std::cout << "INVERSION TEST 3 FAILED" << std::endl;
    return false;
  }

  Matrix mat_4_d(
    9.0f, 3.0f, 0.0f, 9.0f,
   -5.0f,-2.0f,-6.0f,-3.0f,
   -4.0f, 9.0f, 6.0f, 4.0f,
   -7.0f, 6.0f, 6.0f, 2.0f);
  Matrix mat_4_d_invert_success(
    -0.04074f,-0.07778f, 0.14444f,-0.22222f,
    -0.07778f, 0.03333f, 0.36667f,-0.33333f,
    -0.02901f,-0.14630f,-0.10926f, 0.12963f,
     0.17778f, 0.06667f,-0.26667f, 0.33333f);
  std::unique_ptr<Matrix> mat_4_d_inversion = mat_4_d.Invert();
  if (!(mat_4_d_invert_success == *mat_4_d_inversion)) {
    std::cout << "INVERSION TEST 4 FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Matrix::TransformTest() {
  float pi_4 = 0.78539816339;
  float pi_2 = 1.57079632679;


  // TRANSLATION
  std::unique_ptr<Tuple> test_a_p = TupleManager::Instance()->Point(-3.0f, 4.0f, 5.0f);
  std::unique_ptr<Matrix> translation = Matrix::TranslationMatrix(5.0f, -3.0f, 2.0f);
  std::unique_ptr<Tuple> result = *translation * (*test_a_p);
  Tuple translation_success_p(2.0f, 1.0f, 7.0f, 1.0f);
  if (!(*result == translation_success_p)) {
    std::cout << "TRANSLATION TEST FAILED" << std::endl;
    return false;
  }

  // SCALING
  test_a_p = TupleManager::Instance()->Point(-4.0f, 6.0f, 8.0f);
  std::unique_ptr<Matrix> scaling = Matrix::ScalingMatrix(2.0f, 3.0f, 4.0f);
  result = *scaling * (*test_a_p);
  Tuple scaling_success_p(-8.0f, 18.0f, 32.0f, 1.0f);
  if (!(*result == scaling_success_p)) {
    std::cout << "SCALING TEST FAILED" << std::endl;
    return false;
  }

  // ROTATION X
  test_a_p = TupleManager::Instance()->Point(0.0f, 1.0f, 0.0f);
  std::unique_ptr<Matrix> half_quarer_rotation = Matrix::RotationXMatrix(pi_4);
  std::unique_ptr<Matrix> full_quarter_rotation = Matrix::RotationXMatrix(pi_2);
  Tuple rotation_x_half_success(0.0f, sqrtf(2.0f) / 2.0f, sqrtf(2.0f) / 2.0f, 1.0f);
  Tuple rotation_x_full_success(0.0f, 0.0f, 1.0f, 1.0f);
  result = *half_quarer_rotation * (*test_a_p);
  if (!(*result == rotation_x_half_success)) {
    std::cout << "ROTATION X HALF TEST FAILED" << std::endl;
    return false;
  }
  result = *full_quarter_rotation * (*test_a_p);
  if (!(*result == rotation_x_full_success)) {
    std::cout << "ROTATION X HALF TEST FAILED" << std::endl;
    return false;
  }

  // ROTATION Y
  test_a_p = TupleManager::Instance()->Point(0.0f, 0.0f, 1.0f);
  half_quarer_rotation = Matrix::RotationYMatrix(pi_4);
  full_quarter_rotation = Matrix::RotationYMatrix(pi_2);
  Tuple rotation_y_half_success(sqrtf(2.0f) / 2.0f, 0.0f, sqrtf(2.0f) / 2.0f, 1.0f);
  Tuple rotation_y_full_success(1.0f, 0.0f, 0.0f, 1.0f);
  result = *half_quarer_rotation * (*test_a_p);
  if (!(*result == rotation_y_half_success)) {
    std::cout << "ROTATION Y HALF TEST FAILED" << std::endl;
    return false;
  }
  result = *full_quarter_rotation * (*test_a_p);
  if (!(*result == rotation_y_full_success)) {
    std::cout << "ROTATION Y HALF TEST FAILED" << std::endl;
    return false;
  }

  // ROTATION Z
  test_a_p = TupleManager::Instance()->Point(0.0f, 1.0f, 0.0f);
  // PI / 4
  half_quarer_rotation = Matrix::RotationZMatrix(pi_4);
  // PI / 2
  full_quarter_rotation = Matrix::RotationZMatrix(pi_2);
  Tuple rotation_z_half_success(-sqrtf(2.0f) / 2.0f, sqrtf(2.0f) / 2.0f, 0.0f, 1.0f);
  Tuple rotation_z_full_success(-1.0f, 0.0f, 0.0f, 1.0f);
  result = *half_quarer_rotation * (*test_a_p);
  if (!(*result == rotation_z_half_success)) {
    std::cout << "ROTATION Z HALF TEST FAILED" << std::endl;
    return false;
  }
  result = *full_quarter_rotation * (*test_a_p);
  if (!(*result == rotation_z_full_success)) {
    std::cout << "ROTATION Z HALF TEST FAILED" << std::endl;
    return false;
  }
}

bool Matrix::ShearingTest() {
  std::unique_ptr<Matrix> shearing = Matrix::ShearingMatrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  std::unique_ptr<Tuple> test_p = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  std::unique_ptr<Tuple> result = *shearing * (*test_p);
  Tuple shearing_success(5.0f, 3.0f, 4.0f, 1.0f);
  if (!(*result == shearing_success)) {
    std::cout << "SHEARING TEST 1 FAILED" << std::endl;
    return false;
  }

  shearing = Matrix::ShearingMatrix(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  test_p = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  result = *shearing * (*test_p);
  shearing_success = Tuple(6.0f, 3.0f, 4.0f, 1.0f);
  if (!(*result == shearing_success)) {
    std::cout << "SHEARING TEST 2 FAILED" << std::endl;
    return false;
  }

  shearing = Matrix::ShearingMatrix(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
  test_p = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  result = *shearing * (*test_p);
  shearing_success = Tuple(2.0f, 5.0f, 4.0f, 1.0f);
  if (!(*result == shearing_success)) {
    std::cout << "SHEARING TEST 3 FAILED" << std::endl;
    return false;
  }

  shearing = Matrix::ShearingMatrix(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
  test_p = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  result = *shearing * (*test_p);
  shearing_success = Tuple(2.0f, 7.0f, 4.0f, 1.0f);
  if (!(*result == shearing_success)) {
    std::cout << "SHEARING TEST 4 FAILED" << std::endl;
    return false;
  }

  shearing = Matrix::ShearingMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  test_p = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  result = *shearing * (*test_p);
  shearing_success = Tuple(2.0f, 3.0f, 6.0f, 1.0f);
  if (!(*result == shearing_success)) {
    std::cout << "SHEARING TEST 5 FAILED" << std::endl;
    return false;
  }

  shearing = Matrix::ShearingMatrix(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
  test_p = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  result = *shearing * (*test_p);
  shearing_success = Tuple(2.0f, 3.0f, 7.0f, 1.0f);
  if (!(*result == shearing_success)) {
    std::cout << "SHEARING TEST 5 FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Matrix::TranformChainingTest() {
  float pi_4 = 0.78539816339;
  float pi_2 = 1.57079632679;
  
  std::unique_ptr<Tuple> test_p = TupleManager::Instance()->Point(1.0f, 0.0f, 1.0f);
  std::unique_ptr<Matrix> rotation_x = Matrix::RotationXMatrix(pi_2);
  std::unique_ptr<Matrix> scale = Matrix::ScalingMatrix(5.0f, 5.0f, 5.0f);
  std::unique_ptr<Matrix> translate = Matrix::TranslationMatrix(10.0f, 5.0f, 7.0f);
  std::unique_ptr<Matrix> transform = Matrix::TranformationMatrix(*rotation_x, *scale, *translate);
  Tuple test_success_p(15.0f, 0.0f, 7.0f, 1.0f);
  std::unique_ptr<Tuple> result = *transform * (*test_p);
  if (!(*result == test_success_p)) {
    std::cout << "TRANSFORM CHAINGING TEST FAILED" << std::endl;
    return false;
  } else {
    return true;
  }

}
