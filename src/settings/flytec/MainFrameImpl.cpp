/***************************************************************************
 *   Copyright (C) 2004 by Alex Graf                                       *
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

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

#include "CorrFrameImpl.h"
#include "VarioFrameImpl.h"
#include "AcousticFrameImpl.h"
#include "VelocityFrameImpl.h"
#include "GPSFrameImpl.h"
#include "DisplayFrameImpl.h"
#include "FlyCalcFrameImpl.h"
#include "DeviceFrameImpl.h"
#include "IFlyHighRC.h"
#include "MemoryFrameImpl.h"
#include "PolareFrameImpl.h"
#include "ProgressDlg.h"
#include "UnitFrameImpl.h"
#include "Frame.h"
#include "IGPSDevice.h"
#include "SmsFrameImpl.h"
#include "MainFrameImpl.h"

MainFrameImpl::MainFrameImpl(QWidget* parent)
:QMainWindow(parent)
{
  setupUi(this);
	QWidget *pWidget;
	VelocityFrameImpl *pVelocityFrame;
	AcousticFrameImpl *pAcousticFrame;
	VarioFrameImpl *pVarioFrame;
	CorrFrameImpl *pCorrFrame;
	GPSFrameImpl *pGPSFrame;
	DisplayFrameImpl *pDisplayFrame;
	FlyCalcFrameImpl *pFlyCalcFrame;
	DeviceFrameImpl *pDeviceFrame;
	MemoryFrameImpl *pMemoryFrame;
	PolareFrameImpl *pPolareFrame;
	UnitFrameImpl *pUnitFrame;
	SmsFrameImpl *pSmsFrame;

	m_fileName = "";

	// make a clean table
	pWidget = toolBox->widget(0);
	toolBox->removeItem(toolBox->indexOf(pWidget));
	pWidget = widgetStack->widget(1);
	widgetStack->removeWidget(pWidget);
  pWidget = widgetStack->widget(0);
	widgetStack->removeWidget(pWidget);

	// Correction
	pCorrFrame = new CorrFrameImpl();
	addPage(pCorrFrame);
	pCorrFrame->setEnabled(true);
	m_FrameList.push_back(pCorrFrame);

	// Vario
	pVarioFrame = new VarioFrameImpl();
	addPage(pVarioFrame);
	m_FrameList.push_back(pVarioFrame);

	// Acoustic
	pAcousticFrame = new AcousticFrameImpl();
	addPage(pAcousticFrame);
	m_FrameList.push_back(pAcousticFrame);

	// Velocity
	pVelocityFrame = new VelocityFrameImpl();
	addPage(pVelocityFrame);
	m_FrameList.push_back(pVelocityFrame);

	// GPS
	pGPSFrame = new GPSFrameImpl();
	addPage(pGPSFrame);
	m_FrameList.push_back(pGPSFrame);

	// Fly Calculator (not available for 5020)
	pFlyCalcFrame = new FlyCalcFrameImpl();
	addPage(pFlyCalcFrame);
	pFlyCalcFrame->setEnabled(false);
	m_FrameList.push_back(pFlyCalcFrame);

	// Device
	pDeviceFrame = new DeviceFrameImpl();
	addPage(pDeviceFrame);
	m_FrameList.push_back(pDeviceFrame);

	// Memory
	pMemoryFrame = new MemoryFrameImpl();
	addPage(pMemoryFrame);
	m_FrameList.push_back(pMemoryFrame);

	// Display
	pDisplayFrame = new DisplayFrameImpl();
	addPage(pDisplayFrame);
	m_FrameList.push_back(pDisplayFrame);

	// Polare
	pPolareFrame = new PolareFrameImpl();
	addPage(pPolareFrame);
	pPolareFrame->setEnabled(false);
	m_FrameList.push_back(pPolareFrame);

	// Unit
	pUnitFrame = new UnitFrameImpl();
	addPage(pUnitFrame);
	m_FrameList.push_back(pUnitFrame);

	// SMS
	pSmsFrame = new SmsFrameImpl();
	addPage(pSmsFrame);
	pSmsFrame->setEnabled(false);
	m_FrameList.push_back(pSmsFrame);

/*	m_pProgressBar = new QProgressBar(statusBar());
	m_pProgressBar->setProgress(0, ft_MemSize/ft_PageSize);
	m_pProgressBar->setShown(false);
	statusBar()->addWidget(m_pProgressBar, 1, true);*/
}

void MainFrameImpl::addPage(QWidget *pFrame)
{
	QWidget *pWidget;

	widgetStack->addWidget(pFrame);
	pWidget = new QWidget(toolBox);
	toolBox->addItem(pWidget, pFrame->windowTitle());
}

/**
void MainFrameImpl::open()
{
	QFile file;
	QString selected;

	selected = QFileDialog::getOpenFileName(this,
																					tr("Open Flytec config file"),
																					IFlyHighRC::pInstance()->lastDir(),
																					"Flytec Config Files (*.flt)");

	file.setFileName(selected);

	if(selected!="" && file.exists())
	{
		IFlyHighRC::pInstance()->setLastDir(QFileInfo(selected).absoluteDir().absolutePath());

		if(file.open(QIODevice::ReadOnly))
		{
			m_flytecMem = file.read(10000);
			file.close();
			updateFrames();
		}
	}
}

void MainFrameImpl::save()
{
	QFile file;
	QString fileName;
	QString selected;

	// suggest filename
	fileName = windowTitle();

	selected = QFileDialog::getSaveFileName(this,
																					tr("Save Flytec config file"),
																					IFlyHighRC::pInstance()->lastDir() + QDir::separator()
																																						 + fileName
																																						 + ".flt",
																					"Flytec Config Files (*.flt)");

	file.setFileName(selected);

	if(selected!="")
	{
		IFlyHighRC::pInstance()->setLastDir(QFileInfo(selected).absoluteDir().absolutePath());

		if(file.open(QIODevice::WriteOnly))
		{
			storeFrames();
			file.write(m_flytecMem);
			file.close();
		}
	}
}
*/

void MainFrameImpl::read()
{
	ProgressDlg dlg(this);

	dlg.beginProgress("read memory...", IGPSDevice::pInstance());

	if(IGPSDevice::pInstance()->open())
	{
		if(IGPSDevice::pInstance()->memoryRead())
		{
			updateFrames();
		}

		IGPSDevice::pInstance()->close();
	}

	dlg.endProgress();
}

void MainFrameImpl::write()
{
	ProgressDlg dlg(this);

	if(QMessageBox::question(this,
													 tr("write configuration"),
													 tr("Write current configuration to the device?"),
													 1,
													 2) == 1)
	{
		storeFrames();

		if(IGPSDevice::pInstance()->open())
		{
			dlg.beginProgress("write memory...", IGPSDevice::pInstance());
			IGPSDevice::pInstance()->memoryWrite();
			IGPSDevice::pInstance()->close();
			dlg.endProgress();
		}
	}
}

void MainFrameImpl::storeFrames()
{
	FrameListType::iterator it;

	// update Frames
	for(it=m_FrameList.begin(); it!=m_FrameList.end(); it++)
	{
		(*it)->store();
	}
}

void MainFrameImpl::updateFrames()
{
	FrameListType::iterator it;

	// update Frames
	for(it=m_FrameList.begin(); it!=m_FrameList.end(); it++)
	{
		(*it)->update();
	}
}
