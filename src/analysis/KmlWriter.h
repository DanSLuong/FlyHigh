/***************************************************************************
 *   Copyright (C) 2005 by Alex Graf                                       *
 *   grafal@sourceforge.net                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef KMLWRITER_H
#define KMLWRITER_H

#include <QTextStream>
#include "FlightPoint.h"
#include "FlightPointList.h"
#include "Flight.h"
#include "WayPoint.h"

/**
@author Alex Graf
*/
class KmlWriter
{
	public:
		KmlWriter();

		~KmlWriter();

		void setFlight(Flight &flight);

		void setDeparture(int index);

		void set1stTurnPoint(int index);

		void set2ndTurnPoint(int index);

		void set3rdTurnPoint(int index);

		void setFinish(int index);

		void setFlightPoints(FlightPointList &flightPoints);

		void setTriangle(bool triangle);

		bool save(const QString &name);

	private:
		Flight m_flight;
		int m_departure;
		int m_1stTurnPoint;
		int m_2ndTurnPoint;
		int m_3rdTurnPoint;
		int m_finish;
		FlightPointList m_flightPointList;
		bool m_triangle;

		void streamCoordinates(QTextStream& s);

		void streamOLC(QTextStream& s);

		void streamStart(QTextStream& s);

		void streamLanding(QTextStream& s);
};

#endif
