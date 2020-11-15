/**
 * @file AxisAngle.hpp
 *
 * @author James Goppert <james.goppert@gmail.com>
 */

#pragma once

#include "mathlib.hpp"

namespace matrix
{

template <typename Type>
class Dcm;

template <typename Type>
class Euler;

template <typename Type>
class AxisAngle;

/**
 * AxisAngle class
 *
 * The rotation between two coordinate frames is
 * described by this class.
 */
template<typename Type>
class AxisAngle : public Vector<Type, 3>
{
public:
    typedef Matrix<Type, 3, 1> Matrix31;

    /**
     * Constructor from array
     *
     * @param data_ array
     */
    explicit AxisAngle(const Type data_[3]) :
        Vector<Type, 3>(data_)
    {
    }

    /**
     * Standard constructor
     */
    AxisAngle() = default;

    /**
     * Constructor from Matrix31
     *
     * @param other Matrix31 to copy
     */
    AxisAngle(const Matrix31 &other) :
        Vector<Type, 3>(other)
    {
    }

    /**
     * Constructor from quaternion
     *
     * This sets the instance from a quaternion representing coordinate transformation from
     * frame 2 to frame 1 where the rotation from frame 1 to frame 2 is described
     * by a 3-2-1 intrinsic Tait-Bryan rotation sequence.
     *
     * @param q quaternion
     */
    AxisAngle(const Quaternion<Type> &q)
    {
        AxisAngle &v = *this;
        Type ang = Type(2) * acos(q(0));
        Type mag = sin(ang/2.0f);
        if (fabs(mag) > 0) {
            v(0) = ang*q(1)/mag;
            v(1) = ang*q(2)/mag;
            v(2) = ang*q(3)/mag;
        } else {
            v(0) = 0;
            v(1) = 0;
            v(2) = 0;
        }
    }

    /**
     * Constructor from dcm
     *
     * Instance is initialized from a dcm representing coordinate transformation
     * from frame 2 to frame 1.
     *
     * @param dcm dcm to set quaternion to
     */
    AxisAngle(const Dcm<Type> &dcm)
    {
        AxisAngle &v = *this;
        v = Quaternion<Type>(dcm);
    }

    /**
     * Constructor from euler angles
     *
     * This sets the instance to a quaternion representing coordinate transformation from
     * frame 2 to frame 1 where the rotation from frame 1 to frame 2 is described
     * by a 3-2-1 intrinsic Tait-Bryan rotation sequence.
     *
     * @param euler euler angle instance
     */
    AxisAngle(const Euler<Type> &euler)
    {
        AxisAngle &v = *this;
        v = Quaternion<Type>(euler);
    }

    /**
     * Constructor from 3 axis angle values (unit vector * angle)
     *
     * @param x r_x*angle
     * @param y r_y*angle
     * @param z r_z*angle
     */
    AxisAngle(Type x, Type y, Type z)
    {
        AxisAngle &v = *this;
        v(0) = x;
        v(1) = y;
        v(2) = z;
    }

    /**
     * Constructor from axis and angle
     *
     * @param axis An axis of rotation, normalized if not unit length
     * @param angle The amount to rotate
     */
    AxisAngle(const Matrix31 & axis_, Type angle_)
    {
        AxisAngle &v = *this;
        // make sure axis is a unit vector
        Vector<Type, 3> a = axis_;
        a = a.unit();
        v(0) = a(0)*angle_;
        v(1) = a(1)*angle_;
        v(2) = a(2)*angle_;
    }


    Vector<Type, 3> axis() {
        if (Vector<Type, 3>::norm() > 0) {
            return Vector<Type, 3>::unit();
        } else {
            return Vector3<Type>(1, 0, 0);
        }
    }

    Type angle() {
        return Vector<Type, 3>::norm();
    }
};

typedef AxisAngle<float> AxisAnglef;

} // namespace matrix

/* vim: set et fenc=utf-8 ff=unix sts=0 sw=4 ts=4 : */