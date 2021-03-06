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

#include <qdialog.h>
#include <qwidget.h>
#include "AirSpace.h"
#include "AirSpaceFormImpl.h"
#include "IAirSpaceForm.h"

IAirSpaceForm::IAirSpaceForm(QWidget* parent, const QString &caption, AirSpace *pAirSpace)
{
	m_pAirSpaceForm = new AirSpaceFormImpl(parent, caption, pAirSpace);
}

IAirSpaceForm::~IAirSpaceForm()
{
	delete m_pAirSpaceForm;
}

void IAirSpaceForm::show()
{
	m_pAirSpaceForm->show();
}

bool IAirSpaceForm::exec()
{
	return (m_pAirSpaceForm->exec() == QDialog::Accepted);
}

void IAirSpaceForm::setModal(bool modal)
{
	m_pAirSpaceForm->setModal(modal);
}

void IAirSpaceForm::setAirSpace(AirSpace *pAirSpace)
{
	m_pAirSpaceForm->setAirSpace(pAirSpace);
}
