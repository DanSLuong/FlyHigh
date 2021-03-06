/******************************************************************************
 *
 * Author      : Mario Konrad, Mario.Konrad@gmx.net
 * Adapted 2005 by Alex Graf, grafal@sourceforge.net
 *
 * Copyright (C) Mario Konrad
 *
 ******************************************************************************
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 ******************************************************************************/
 
#include <math.h>
#include "Vector.h"

Vector2::Vector2(double x, double y)
{
	m_x = x;
	m_y = y;
}

Vector2::Vector2(const Vector2 &v)
{
	*this = v;
}

void Vector2::set(double a, double b)
{
	m_x = a;
	m_y = b;
}

void Vector2::setCircle(double r, double rad)
{
	m_x = r * cos(rad);
	m_y = r * sin(rad);
}

void Vector2::normalize()
{
	const double mag = sqrt(norm());

	if(mag == 0.0)
		return;

	m_x *= 1.0/mag;
	m_y *= 1.0/mag;
}

double Vector2::norm()
{
	return ((*this)*(*this));
}

double Vector2::length() const
{
	return sqrt(m_x * m_x + m_y * m_y);
}

double Vector2::arc() const
{
	double arc;
	
	// special case 0.0
	if(m_x == 0)
	{
		if(m_y > 0)
		{
			arc = M_PI / 2;
		}
		else
		{
			arc = 3 * M_PI / 2;
		}
	}
	
	if(m_x >= 0)
	{
		if(m_y >= 0)
		{
			// 1. quadrant
			arc = atan(m_y / m_x);
		}
		else
		{
			// 4. quadrant
			arc = 2 * M_PI + atan(m_y / m_x);
		}
	}
	else
	{
		// 2. + 3. quadrant
		arc = M_PI + atan(m_y / m_x);
	}
	
	return arc;
}

void Vector2::rot(double rad)
{
	double c = cos(rad);
	double s = sin(rad);
	double newX;
	double newY;
	
	newX = m_x * c - m_y * s;
	newY = m_x * s + m_y * c;
	
	m_x = newX;
	m_y = newY;
}

double Vector2::x()
{
	return m_x;
}

double Vector2::y()
{
	return m_y;
}

Vector2& Vector2::operator = (const Vector2 &v)
{
	m_x = v.m_x;
	m_y = v.m_y;
	 
	return *this;
}

bool Vector2::operator == (const Vector2 &v)
{ 
	return ((m_x == v.m_x) && (m_y == v.m_y));
}

Vector2& Vector2::operator += (const Vector2 &v)
{
	m_x += v.m_x;
	m_y += v.m_y;
	
	return *this;
}

Vector2& Vector2::operator -= (const Vector2 &v)
{
	m_x -= v.m_x;
	m_y -= v.m_y;
	
	return *this;
}

Vector2& Vector2::operator *= (double f)
{
	m_x *= f;
	m_y *= f;
	
	return *this;
}

Vector2 operator + (const Vector2 &w, const Vector2 &v)
{
	return Vector2(w) += v;
}

Vector2 operator - (const Vector2 &w, const Vector2 &v)
{
	return Vector2(w) -= v;
}

Vector2 operator * (const Vector2 &v, double f)
{
	return Vector2(v) *= f;
}

Vector2 operator * (double f, const Vector2 &v)
{ 
	return Vector2(v) *= f;
}

double operator * (const Vector2 &a, const Vector2 &b)
{
	Vector2 loca = a;
	Vector2 locb = b;

	return (loca.x() * locb.x() + loca.y() + locb.y());
}
