/***************************************************************************
 *   Copyright (C) 2012 by Alex Graf                                       *
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
 *                                                                         *
 *   It is prohibited to serve or run this code over network p.e. as web   *
 *   service in combination with closed source.                            *
 ***************************************************************************/

wm_include('js/fai.js');
wm_include('js/leg.js');
wm_include('js/measure.js');
wm_include('js/optimizer.js');
wm_include('js/route.js');
wm_include('js/turnpt.js');
wm_include('js/infobox.js');
wm_include('../airspace/js/airspace.js');

var airspaces = [];
var map;
var route;
var measure;
var oldSelect = -1;
var airspaceNr;

function rt_init()
{
	var mapLoaded = false;
	var mapOptions =
	{
		zoom: 9,
		center: new google.maps.LatLng(47.0, 8.5),
		mapTypeId: google.maps.MapTypeId.TERRAIN,
		disableDefaultUI: false,
		mapTypeControl: true,
		panControl: false,
		zoomControl: false,
		streetViewControl: false
	};

	map = new google.maps.Map(document.getElementById('map'), mapOptions);

	google.maps.event.addListener(map, 'idle', function()
	{
		if(!mapLoaded)
		{
			mapLoaded = true;
			route = new Route(map);
			route.setSpeed(22.0);
			route.setChangeCallback(routeChanged);
			measure = new Measure(map);
			measure.setChangeCallback(measureChanged);
			wm_emitAppReady();
		}
	});

	google.maps.event.addListener(map, 'click', function(event)
	{
		// select next airspace
		airspaceNr = oldSelect;

		for(var i=0; i<airspaces.length; i++)
		{
			airspaceNr = (airspaceNr + 1) % airspaces.length;

			if(airspaces[airspaceNr].isInside(event.latLng))
			{
				if(airspaceNr != oldSelect)
				{
					as_selectAirSpaceNr(airspaceNr);
					break; // jump out of loop
				}
			}
		}
	});
}

function as_pushAirSpace(coords, opts)
{
	var latlngs = [];
	var airspace;
	var nr;

	for(nr=0; nr<coords.length; nr++)
	{
		latlngs.push(new google.maps.LatLng(coords[nr][0], coords[nr][1]));
	}

	airspace = new AirSpace(map, latlngs, opts);
	airspaces.push(airspace);
}

function as_selectAirSpaceNr(num)
{
	var airspace;

	if(num < airspaces.length)
	{
		if(oldSelect >= 0)
		{
			airspaces[oldSelect].setSelect(false);
		}

		oldSelect = num;
		airspace = airspaces[num];
		airspace.setSelect(true);
		as_setName(airspace.getName());
		as_setLow(airspace.getLow());
		as_setHigh(airspace.getHigh());
		as_setClass(airspace.getClass());
	}
}

function as_setName(name)
{
	setDivValue("airspace", name);
}

function as_setLow(low)
{
	if(low === 0)
	{
		setDivValue("low", "GND");
	}
	else
	{
		setDivValue("low", low + " m");
	}
}

function as_setHigh(high)
{
	setDivValue("high", high + " m");
}

function as_setClass(airclass)
{
	setDivValue("class", airclass);
}

function rt_setName(name)
{
	var locInput;

	if(route.getEditable())
	{
		locInput = document.getElementById("name");
		locInput.value = name;
	}
	else
	{
		locInput = document.getElementById("sname");
		locInput.innerHTML = name;
	}
}

function rt_getName()
{
	var locInput;
	var name;

	if(route.getEditable())
	{
		locInput = document.getElementById("name");
		name = locInput.value;
	}
	else
	{
		locInput = document.getElementById("sname");
		name = locInput.innerHTML;
	}

	return name;
}

function rt_setTurnPts(turnPts)
{
	var turnPt;
	var tpNr;
	var bounds;
	var latlng;

	bounds = new google.maps.LatLngBounds();
	
	for(tpNr=0; tpNr<turnPts.length; tpNr++)
	{
		latlng = new google.maps.LatLng(turnPts[tpNr][0], turnPts[tpNr][1]);
		bounds.extend(latlng);
		turnPt = new TurnPt(route, latlng, TurnPt.Type.WayPoint);
		route.addTurnPt(turnPt);
	}

	map.fitBounds(bounds);
}

function rt_getTurnPts()
{
	var turnPts;
	var turnPt;
	var turnPtArray = [];
	var tpNr;

	turnPts = route.getTurnPts();

	for(tpNr=0; tpNr<turnPts.length; tpNr++)
	{
		turnPt = turnPts[tpNr];
		turnPtArray.push(new Array(turnPt.getPosition().lat(), turnPt.getPosition().lng(), turnPt.getAltitude()));
	}

	return turnPtArray;
}

function rt_getType()
{
	return route.getType();
}

function rt_getDist()
{
	return route.getDist();
}

function rt_setEditable(en)
{
	var nameInput;
	var snameInput;
	var name;

	name = rt_getName();
	route.setEditable(en);
	rt_setName(name);
	nameInput = document.getElementById("name");
	snameInput = document.getElementById("sname");

	if(en)
	{
		nameInput.style.display = "";
		snameInput.style.display = "none";
	}
	else
	{
		nameInput.style.display = "none";
		snameInput.style.display = "";
	}
}

function rt_speedUp()
{
	var speed;

	if(route.getEditable())
	{
		speed = route.getSpeed();

		if(speed < 50.0)
		{
			route.setSpeed(speed + 0.5);
			updateDurationAndSpeed();
		}
	}
}

function rt_speedDown()
{
	var speed;

	if(route.getEditable())
	{
		speed = route.getSpeed();

		if(speed > 1.0)
		{
			route.setSpeed(speed - 0.5);
			updateDurationAndSpeed();
		}
	}
}

function rt_durationUp()
{
	var duration;

	if(route.getEditable())
	{
		duration = route.getDuration();

		if(duration < 24)
		{
			route.setDuration(duration + 0.5);
			updateDurationAndSpeed();
		}
	}
}

function rt_durationDown()
{
	var duration;

	if(route.getEditable())
	{
		duration = route.getDuration();
		
		if(duration > 1)
		{
			route.setDuration(duration - 0.5);
			updateDurationAndSpeed();
		}
	}
}

function rt_measure(div)
{
	var show;
	
	show = (div.className == "button_up");
	measure.show(show);

	if(show)
	{
		div.className = "button_down";
		div = document.getElementById("smeasure");
		div.innerHTML = "0.0 km";
	}
	else
	{
		div.className = "button_up";
		div = document.getElementById("smeasure");
		div.innerHTML = "Off";
	}
}

function rt_setOk(ok)
{
	wm_emitOk(ok);
}

function setDivValue(divId, value)
{
	var div;

	div = document.getElementById('s' + divId);
	div.innerHTML = value;
}

function routeChanged()
{
	var locInput;

	locInput = document.getElementById("type");
	locInput.innerHTML = Route.ScoreTypeText[route.getType()];

	locInput = document.getElementById("track");
	locInput.innerHTML = route.getTrackDist().toFixed(0) + " km";

	locInput = document.getElementById("distance");
	locInput.innerHTML = route.getDist().toFixed(2) + " km";

	locInput = document.getElementById("score");
	locInput.innerHTML = route.getScore().toFixed(2) + " points";

	updateDurationAndSpeed();
}

function measureChanged()
{
	var div;

	div = document.getElementById("smeasure");
	div.innerHTML = measure.getDist().toFixed(1) + " km";
}

function updateDurationAndSpeed()
{
	var locInput;

	locInput = document.getElementById("speed");
	locInput.value = route.getSpeed().toFixed(1) + " km/h";
	locInput = document.getElementById("duration");
	locInput.value = route.getDuration().toFixed(1) + " h";
}
