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
#ifndef GliderWindow_h
#define GliderWindow_h

#include "Glider.h"
#include "TableWindow.h"

class QWidget;
class IDataBase;

class GliderWindow: public TableWindow
{
	Q_OBJECT
	public:
		GliderWindow(QWidget* parent, const QString &name, Qt::WindowFlags wflags);

	private:
		void setGliderToRow(uint row, Glider &glider);

	private slots:
		void file_new();

		void file_edit();

		void file_delete();

		void file_update();

	private:
		enum Fields{Manufacturer, Model, Serial, Flights, Airtime};

		IDataBase *m_pDb;
		Glider::GliderListType m_gliderList;
};

#endif
