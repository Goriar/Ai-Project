#include <stdio.h>
#include <math.h>

#include "Vector.h"

#define _EPSILON (0.0001)

CVector::CVector(
	)
{
	value_[0] = 0.0;
	value_[1] = 0.0;

}

CVector::CVector(
	const CVector& vector_in
	)
{
	value_[0] = vector_in.value_[0];
	value_[1] = vector_in.value_[1];
}

CVector::CVector(
	const double& x_in,
	const double& y_in
	)
{
	value_[0] = x_in;
	value_[1] = y_in;
}


CVector&
CVector::operator=(
	const CVector& vector_in
	)
{
	if(&vector_in != this)
	{
		value_[0] = vector_in.value_[0];
		value_[1] = vector_in.value_[1];
	}

	return *this;
}

double&
CVector::operator[](
	const unsigned short index_in
	)
{
	if(index_in > 1)
		throw;

	return value_[index_in];
}

double
CVector::operator[](
	const unsigned short index_in
	) const
{
	if(index_in > 1)
		throw;

	return value_[index_in];
}

void
CVector::set(
	const double& x_in, 
	const double& y_in
	)
{
	value_[0] = x_in;
	value_[1] = y_in;
}

void
CVector::get(
	double& x_out, 
	double& y_out
	) const
{
	x_out = value_[0];
	y_out = value_[1];
}

bool
CVector::operator==(
	const CVector& vector_in
	) const
{
	if( (fabs(value_[0] - vector_in.value_[0]) >    _EPSILON)
		|| (fabs(value_[1] - vector_in.value_[1]) > _EPSILON))
		return false;
	return true;
}

bool
CVector::operator!=(
	const CVector& vector_in
	) const
{
	return( !(*this == vector_in) );
}

CVector
CVector::operator-(
	) const
{
	return CVector(
		-value_[0],
		-value_[1]
		);
}

CVector
operator-(
	const CVector& vector0_in,
	const CVector& vector1_in
	)
{
	return CVector(
		vector0_in.value_[0] - vector1_in.value_[0],
		vector0_in.value_[1] - vector1_in.value_[1]
		);
}

CVector
operator+(
	const CVector& vector0_in,
	const CVector& vector1_in
	)
{
	return CVector(
		vector0_in.value_[0] + vector1_in.value_[0],
		vector0_in.value_[1] + vector1_in.value_[1]
		);
}

double
operator*(
	const CVector& vector0_in,
	const CVector& vector1_in
	)
{
	return(
		  vector0_in.value_[0] * vector1_in.value_[0]
		+ vector0_in.value_[1] * vector1_in.value_[1]
		);
}

double
CVector::getInnerProduct(
	const CVector& vector_in
	) const
{
	return(
		value_[0] * vector_in.value_[0]
		+ value_[1] * vector_in.value_[1]
		);
}
  
CVector
operator*(
	const double& scalar_in,
	const CVector& vector_in
	)
{
	return CVector(
		scalar_in * vector_in.value_[0],
		scalar_in * vector_in.value_[1]
		);
}

CVector
operator*(
	const CVector& vector_in,
	const double& scalar_in
	)
{
	return CVector(
		vector_in.value_[0] * scalar_in,
		vector_in.value_[1] * scalar_in
		);
}



CVector
operator/(
	const CVector& vector_in,
	const double& scalar_in
	)
{
	return CVector(
		vector_in.value_[0] / scalar_in,
		vector_in.value_[1] / scalar_in
		);
}

CVector&
CVector::operator+=(
	const CVector& vector_in
	)
{
	value_[0]    += vector_in.value_[0];
	value_[1]    += vector_in.value_[1];
	return *this;
}

CVector&
CVector::operator-=(
	const CVector& vector_in
	)
{
	value_[0]    -= vector_in.value_[0];
	value_[1]    -= vector_in.value_[1];

	return *this;
}

CVector&
CVector::operator*=(
	const double& scalar_in
	)
{
	value_[0]    *= scalar_in;
	value_[1]    *= scalar_in;

	return *this;
}

CVector&
CVector::operator/=(
	const double& scalar_in
	)
{
	value_[0]    /= scalar_in;
	value_[1]    /= scalar_in;

	return *this;
}

double
CVector::getLength(
	) const
{
    return sqrt(
		value_[0] * value_[0] 
		+ value_[1] * value_[1]
		);
}

void
CVector::normalize(
	)
{
	double length;
	length = getLength();

	//if( fabs( length ) < _EPSILON )
	//	throw;

	value_[0] /= length;
	value_[1] /= length;
}

bool
CVector::isNormalized(
	) const
{
	double length;
	length = getLength();

	if(fabs(length - 1.0) > _EPSILON)
		return false;
	return true;
}

bool
CVector::isNil(
	) const
{
	double length;
	length = getLength();

	if(fabs(length) > _EPSILON)
		return false;
	return true;
}

