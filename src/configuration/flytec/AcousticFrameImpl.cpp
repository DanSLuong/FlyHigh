/***************************************************************************
 *   Copyright (C) 2004 by Alex Graf                                       *
 *   grafal@sourceforge.net                                                         *
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

#include <qcheckbox.h>
#include <qslider.h>
#include <qspinbox.h>

#include "AcousticFrameImpl.h"
extern "C"
{
	#include "flytec_al.h"
}

AcousticFrameImpl::AcousticFrameImpl(QWidget* parent, const char* name, WFlags fl)
: AcousticFrame(parent,name,fl)
{
}

AcousticFrameImpl::~AcousticFrameImpl()
{
}

void AcousticFrameImpl::sinkAcousticToggled(bool b)
{
	checkBox_SinkAcoustic->setChecked(b);
	spinBox_Sink->setEnabled(b);
	spinBox_DownFreq->setEnabled(b);
}

void AcousticFrameImpl::update(QByteArray &arr)
{
	u_char c8value;
	int8_t i8value;
	u_int16_t c16value;
		
	// Base Volume
	slider_Volume->setValue(arr[BASE_VOL_BEEP_POS]);
	
	// Vario Offset
	spinBox_Threshold->setValue(arr[VARIO_OFFSET_POS]);

	// Up Base Frequency
	c16value = arr[UP_BASE_FRQ_POS] << 8;
	c16value += arr[UP_BASE_FRQ_POS+1] ;
	spinBox_UpFreq->setValue(c16value);

	// Frequency Modulation
	slider_FreqMod->setValue(arr[FRQ_MODULATION_POS]);

	// Acoustic Pitch
	slider_Pitch->setValue(arr[ACOUSTIC_PITCH_POS]);

	// Acoustic Integral
	slider_Integration->setValue(arr[ACOUSTIC_I_POS]);
	
	// Sink Acoustic Enabled
	c8value = arr[SINC_ACOUSTIC_EN_POS];
	checkBox_SinkAcoustic->setChecked(c8value);
	spinBox_Sink->setEnabled(c8value > 0);
	spinBox_DownFreq->setEnabled(c8value > 0);

	// Down Base Frequency
	c16value =  arr[DOWN_BASE_FRQ_POS] << 8;
	c16value += arr[DOWN_BASE_FRQ_POS+1];
	spinBox_DownFreq->setValue(c16value);

	// Sink
	i8value = arr[ACOUSTIC_SINK_POS];
	spinBox_Sink->setValue(i8value);
}

void AcousticFrameImpl::store(QByteArray &arr)
{
	u_int16_t c16value;
		
	// Base Volume
	arr[BASE_VOL_BEEP_POS] = (u_char)slider_Volume->value();
	
	// Vario Offset
	arr[VARIO_OFFSET_POS] = (u_char)spinBox_Threshold->value();

	// Up Base Frequency
	c16value = spinBox_UpFreq->value();
	arr[UP_BASE_FRQ_POS] = (u_char)(c16value >> 8);
	arr[UP_BASE_FRQ_POS+1] = (u_char)(c16value & 0xFF);

	// Frequency Modulation
	arr[FRQ_MODULATION_POS] = (u_char)slider_FreqMod->value();

	// Acoustic Pitch
	arr[ACOUSTIC_PITCH_POS] = (u_char)slider_Pitch->value();

	// Acoustic Integral
	arr[ACOUSTIC_I_POS] = (u_char)slider_Integration->value();
	
	// Sink Acoustic Enabled
	arr[SINC_ACOUSTIC_EN_POS] = (u_char)checkBox_SinkAcoustic->isChecked();

	// Down Base Frequency
	c16value = spinBox_DownFreq->value();
	arr[DOWN_BASE_FRQ_POS] = (u_char)(c16value >> 8);
	arr[DOWN_BASE_FRQ_POS+1] = (u_char)(c16value & 0xFF);
	
	// Sink
	arr[ACOUSTIC_SINK_POS] = (int8_t)spinBox_Sink->value();
}


#include "AcousticFrameImpl.moc"

