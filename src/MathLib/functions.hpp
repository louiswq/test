#pragma once

#include <cmath>

namespace math
{

template <typename Type>
bool is_finite(Type x) {
    return std::isfinite(x);
}

template<typename _Tp>
inline constexpr const _Tp abs(const _Tp &a)
{
	return (a < _Tp(0)) ? (-a) : a;
}

template<typename _Tp>
inline constexpr const _Tp &min(const _Tp &a, const _Tp &b)
{
	return (a < b) ? a : b;
}

template<typename _Tp>
inline constexpr const _Tp &max(const _Tp &a, const _Tp &b)
{
	return (a > b) ? a : b;
}

template<typename _Tp>
inline constexpr const _Tp &constrain(const _Tp &val, const _Tp &min_val, const _Tp &max_val)
{
	return (val < min_val) ? min_val : ((val > max_val) ? max_val : val);
}


// Type-safe signum function
template<typename _Tp>
int sign(_Tp val)
{
	return (_Tp(0) < val) - (val < _Tp(0));
}

// Type-safe signum function with zero treated as positive
template<typename T>
int signNoZero(T val)
{
	return (T(0) <= val) - (val < T(0));
}

/*
 * So called exponential curve function implementation.
 * It is essentially a linear combination between a linear and a cubic function.
 * @param value [-1,1] input value to function
 * @param e [0,1] function parameter to set ratio between linear and cubic shape
 *		0 - pure linear function
 *		1 - pure cubic function
 * @return result of function output
 */
template<typename _Tp>
inline const _Tp expo(const _Tp &value, const _Tp &e)
{
	_Tp x = constrain(value, (_Tp) - 1, (_Tp)1);
	return (1 - e) * x + e * x * x * x;
}

/*
 * So called SuperExpo function implementation.
 * It is a 1/(1-x) function to further shape the rc input curve intuitively.
 * I enhanced it compared to other implementations to keep the scale between [-1,1].
 * @param value [-1,1] input value to function
 * @param e [0,1] function parameter to set ratio between linear and cubic shape (see expo)
 * @param g [0,1) function parameter to set SuperExpo shape
 *		0 - pure expo function
 *		0.99 - very strong bent curve, stays zero until maximum stick input
 *		1 - DO NOT USE, division by zero on maxima
 * @return result of function output
 */
template<typename _Tp>
inline const _Tp superexpo(const _Tp &value, const _Tp &e, const _Tp &g)
{
	_Tp x = constrain(value, (_Tp) - 1, (_Tp)1);
	return expo(x, e) * (1 - g) / (1 - fabsf(x) * g);
}

template<typename _Tp>
inline const _Tp deadzone(const _Tp &value, const _Tp &dz)
{
	_Tp x = constrain(value, (_Tp) - 1, (_Tp)1);
	_Tp dzc = constrain(dz, (_Tp) - 1, (_Tp)1);
	// Rescale the input such that we get a piecewise linear function that will be continuous with applied deadzone
	_Tp out = (x - sign(x) * dzc) / (1 - dzc);
	// apply the deadzone (values zero around the middle)
	return out * (fabsf(x) > dzc);
}

template<typename _Tp>
inline const _Tp expo_deadzone(const _Tp &value, const _Tp &e, const _Tp &dz)
{
	return expo(deadzone(value, dz), e);
}


/*
 * Constant, linear, constant function with the two corner points as parameters
 * y_high		   -------
 *				  /
 *				 /
 *				/
 * y_low -------
 *		   x_low   x_high
 */
template<typename _Tp>
inline const _Tp gradual(const _Tp &value, const _Tp &x_low, const _Tp &x_high, const _Tp &y_low, const _Tp &y_high)
{
	if (value < x_low) {
		return y_low;

	} else if (value > x_high) {
		return y_high;

	} else {
		/* linear function between the two points */
		float a = (y_high - y_low) / (x_high - x_low);
		float b = y_low - a * x_low;
		return	a * value + b;
	}
}

inline float radians(float degrees)
{
	return (degrees / 180.0f) * M_PI;
}

inline float degrees(float radians)
{
	return (radians * 180.0f) / M_PI;
}


/**
 * Compare if two floating point numbers are equal
 *
 * NAN is considered equal to NAN and -NAN
 * INFINITY is considered equal INFINITY but not -INFINITY
 *
 * @param x right side of equality check
 * @param y left side of equality check
 * @param eps numerical tolerance of the check
 * @return true if the two values are considered equal, false otherwise
 */
template<typename Type>
bool isEqualF(const Type x, const Type y, const Type eps = 1e-4f)
{
    return (matrix::fabs(x - y) <= eps)
           || (isnan(x) && isnan(y))
           || (isinf(x) && isinf(y) && isnan(x - y));
}

/**
 * Wrap value to stay in range [low, high)
 *
 * @param x input possibly outside of the range
 * @param low lower limit of the allowed range
 * @param high upper limit of the allowed range
 * @return wrapped value inside the range
 */
template<typename Type>
Type wrap(Type x, Type low, Type high) {
    // already in range
    if (low <= x && x < high) {
        return x;
    }

    const Type range = high - low;
    const Type inv_range = Type(1) / range; // should evaluate at compile time, multiplies below at runtime
    const Type num_wraps = floor((x - low) * inv_range);
    return x - range * num_wraps;
}

/**
 * Wrap value in range [-π, π)
 */
template<typename Type>
Type wrap_pi(Type x)
{
    return wrap(x, Type(-M_PI), Type(M_PI));
}

/**
 * Wrap value in range [0, 2π)
 */
template<typename Type>
Type wrap_2pi(Type x)
{
    return wrap(x, Type(0), Type(M_TWOPI));
}
}
