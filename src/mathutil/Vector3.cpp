#include <stdio.h>
#include <math.h>

#include "Vector3.h"

#define _EPSILON (0.0001)

CVector3::CVector3(
	)
{
	value_[0] = 0.0;
	value_[1] = 0.0;
	value_[2] = 0.0;

}

CVector3::CVector3(
	const CVector3& vector_in
	)
{
	value_[0] = vector_in.value_[0];
	value_[1] = vector_in.value_[1];
	value_[2] = vector_in.value_[2];
}

CVector3::CVector3(
	const double& x_in,
	const double& y_in,
	const double& z_in
	)
{
	value_[0] = x_in;
	value_[1] = y_in;
	value_[2] = z_in;
}


CVector3&
CVector3::operator=(
	const CVector3& vector_in
	)
{
	if(&vector_in != this)
	{
		value_[0] = vector_in.value_[0];
		value_[1] = vector_in.value_[1];
		value_[2] = vector_in.value_[2];
	}

	return *this;
}

double&
CVector3::operator[](
	const unsigned short index_in
	)
{
	if(index_in > 2)
		throw;

	return value_[index_in];
}

double
CVector3::operator[](
	const unsigned short index_in
	) const
{
	if(index_in > 2)
		throw;

	return value_[index_in];
}

void
CVector3::set(
	const double& x_in, 
	const double& y_in,
	const double& z_in
	)
{
	value_[0] = x_in;
	value_[1] = y_in;
	value_[2] = z_in;
}

void
CVector3::get(
	double& x_out, 
	double& y_out,
	double& z_out
	) const
{
	x_out = value_[0];
	y_out = value_[1];
	z_out = value_[2];
}

bool
CVector3::operator==(
	const CVector3& vector_in
	) const
{
	if( (fabs(value_[0] - vector_in.value_[0]) >    _EPSILON)
		|| (fabs(value_[1] - vector_in.value_[1]) > _EPSILON)
		|| (fabs(value_[2] - vector_in.value_[2]) > _EPSILON))
		return false;
	return true;
}

bool
CVector3::operator!=(
	const CVector3& vector_in
	) const
{
	return( !(*this == vector_in) );
}

CVector3
CVector3::operator-(
	) const
{
	return CVector3(
		-value_[0],
		-value_[1],
		-value_[2]
		);
}

CVector3
operator-(
	const CVector3& vector0_in,
	const CVector3& vector1_in
	)
{
	return CVector3(
		vector0_in.value_[0] - vector1_in.value_[0],
		vector0_in.value_[1] - vector1_in.value_[1],
		vector0_in.value_[2] - vector1_in.value_[2]
		);
}

CVector3
operator+(
	const CVector3& vector0_in,
	const CVector3& vector1_in
	)
{
	return CVector3(
		vector0_in.value_[0] + vector1_in.value_[0],
		vector0_in.value_[1] + vector1_in.value_[1],
		vector0_in.value_[2] + vector1_in.value_[2]
		);
}

double
operator*(
	const CVector3& vector0_in,
	const CVector3& vector1_in
	)
{
	return(
		  vector0_in.value_[0] * vector1_in.value_[0]
		+ vector0_in.value_[1] * vector1_in.value_[1]
		+ vector0_in.value_[2] * vector1_in.value_[2]
		);
}

double
CVector3::getInnerProduct(
	const CVector3& vector_in
	) const
{
	return(
		value_[0] * vector_in.value_[0]
		+ value_[1] * vector_in.value_[1]
		+ value_[2] * vector_in.value_[2]
		);
}
  
CVector3
operator*(
	const double& scalar_in,
	const CVector3& vector_in
	)
{
	return CVector3(
		scalar_in * vector_in.value_[0],
		scalar_in * vector_in.value_[1],
		scalar_in * vector_in.value_[2]
		);
}

CVector3
operator*(
	const CVector3& vector_in,
	const double& scalar_in
	)
{
	return CVector3(
		vector_in.value_[0] * scalar_in,
		vector_in.value_[1] * scalar_in,
		vector_in.value_[2] * scalar_in
		);
}



CVector3
operator/(
	const CVector3& vector_in,
	const double& scalar_in
	)
{
	return CVector3(
		vector_in.value_[0] / scalar_in,
		vector_in.value_[1] / scalar_in,
		vector_in.value_[2] / scalar_in
		);
}

CVector3&
CVector3::operator+=(
	const CVector3& vector_in
	)
{
	value_[0]    += vector_in.value_[0];
	value_[1]    += vector_in.value_[1];
	value_[2]    += vector_in.value_[2];
	return *this;
}

CVector3&
CVector3::operator-=(
	const CVector3& vector_in
	)
{
	value_[0]    -= vector_in.value_[0];
	value_[1]    -= vector_in.value_[1];
	value_[2]    -= vector_in.value_[2];

	return *this;
}

CVector3&
CVector3::operator*=(
	const double& scalar_in
	)
{
	value_[0]    *= scalar_in;
	value_[1]    *= scalar_in;
	value_[2]    *= scalar_in;

	return *this;
}

CVector3&
CVector3::operator/=(
	const double& scalar_in
	)
{
	value_[0]    /= scalar_in;
	value_[1]    /= scalar_in;
	value_[2]    /= scalar_in;

	return *this;
}

double
CVector3::getLength(
	) const
{
    return sqrt(
		value_[0] * value_[0] 
		+ value_[1] * value_[1]
		+ value_[2] * value_[2]
		);
}

void
CVector3::normalize(
	)
{
	double length;
	length = getLength();

	//if( fabs( length ) < _EPSILON )
	//	throw;

	value_[0] /= length;
	value_[1] /= length;
	value_[2] /= length;
}

bool
CVector3::isNormalized(
	) const
{
	double length;
	length = getLength();

	if(fabs(length - 1.0) > _EPSILON)
		return false;
	return true;
}

bool
CVector3::isNil(
	) const
{
	double length;
	length = getLength();

	if(fabs(length) > _EPSILON)
		return false;
	return true;
}


CVector3 CVector3::crossProduct(CVector3 v1, CVector3 v2){
	CVector3 v = CVector3((v1[1]*v2[2])-(v1[2]*v2[1]),
						(v1[2]*v2[0])-(v1[0]*v2[2]),
						(v1[0]*v2[1])-(v1[1]*v2[0]));
	return v;
}
