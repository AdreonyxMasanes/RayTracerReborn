#include "Utility.hpp"


bool Utility::FloatsAreEqual(float a, float b) {
	const float kEpsilon = 0.0001f;
	if (abs(a - b) < kEpsilon) {
		return true;
	} else {
		return false;
	}
}
