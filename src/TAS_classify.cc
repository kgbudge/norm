/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * TAS_classify.cc
 * Copyright (C) 2015 Kent G. Budge <kgb@kgbudge.com>
 * 
 * norm is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * norm is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "composition.hh"

//-----------------------------------------------------------------------------//
std::string TAS_classify()
{
	// Determine the TAS classification

	double silica = SiO2/wtotal;
	double alkali = (Na2O+K2O)/wtotal;
	double magnesium = MgO/wtotal;
	double 	titanium = TiO2/wtotal;

	// High magnesium?
	if (alkali < 0.02 && silica<0.53 && magnesium>=0.18)
	{	
		if (alkali > 0.01)
		{
			return std::string("picrite");	
		}
		else if (titanium > 0.01)
		{
			return std::string("meimechite");	
		}
		else
		{
			return std::string("komatiite");	
		}
	}
	else  if (silica>=0.53 && silica<0.63 && magnesium>=0.08 && titanium < 0.005)
	{
		return std::string("boninite");	
	}
	// Not high magnesium
	else if ((silica <= 0.41 || alkali>=0.07+(silica-0.41)*(0.14-0.07)/(0.525-0.41)) &&
	         alkali<=0.14+(silica-0.525)*(0.117-0.14)/(0.576-0.525))
	{
		// Further criteria to separate leucitite, nephelinite, melanephelinite, basanite, and tephrite
		if (K2O >= Na2O)
		{
			return std::string("leucitite");	
		}
		else if (ne>=20)
		{
			return std::string("nephelinite");	
		}
		else if (ab>=5)
		{
			if (ol > 10)
			{
				return std::string("basanite");	
			}
			else
			{
				return std::string("tephrite");	
			}
		}
		else
		{
			return std::string("melanephelinite");	
		}
	}
	else if (silica>=0.41 && silica<=0.45 && alkali<=0.03)
	{
		return std::string("picrobasalt");
	}
	else if (silica>=0.45 && silica<=0.52 && alkali<=0.05)
	{
		return std::string("basalt");
	}
	else if (silica>=0.52 && silica<=0.57 && alkali<=0.05+(silica-0.52)*(0.059-0.05)/(0.57-0.52))
	{
		return std::string("basaltic andesite");
	}
	else if (silica>=0.57 && silica<=0.63 && alkali<=0.059+(silica-0.57)*(0.07-0.059)/(0.63-0.57))
	{
		return std::string("andesite");
	}
	else if (silica>=0.63 && 
	         alkali<=0.07+(silica-0.63)*(0.08-0.07)/(0.69-0.63) &&
	         alkali<=0.08+(silica-0.69)*(0.0-0.08)/(0.77-0.69))
	{
		return std::string("dacite");
	}
	else if (silica>=0.69 && alkali>=0.08+(silica-0.69)*(0.0-0.08)/(0.77-0.69))
	{
		return std::string("rhyolite");
	}
	else if (silica>=0.41 &&
	         alkali<=0.07+(silica-0.41)*(0.094-0.07)/(0.45-0.41) &&
	         alkali<=0.094+(silica-0.45)*(0.073-0.094)/(0.494-0.45) && 
	         (silica<=0.45 || alkali>=0.05+(silica-0.45)*(0.073-0.05)/(0.494-0.45)) &&
	         alkali>=0.03)
	{
		// Further criteria to separate leucitite, nephelinite, melanephelinite, basanite, and tephrite
		if (K2O >= Na2O)
		{
			return std::string("leucitite");	
		}
		else if (ne>=20)
		{
			return std::string("nephelinite");	
		}
		else if (ab>=5)
		{
			if (ol > 10)
			{
				return std::string("basanite");	
			}
			else
			{
				return std::string("tephrite");	
			}
		}
		else
		{
			return std::string("melanephelinite");	
		}
	}
	else if (alkali<=0.05+(silica-0.45)*(0.073-0.05)/(0.494-0.45) &&
	         alkali<=0.073+(silica-0.494)*(0.05-0.073)/(0.52-0.494) && 
	         alkali>=0.05)
	{
		if (Na2O - 0.02*wtotal > K2O)
		{
			return std::string("hawaiite");
		}
		else
		{
			return std::string("potassic trachybasalt");
		}
	}
	else if (alkali<=0.073+(silica-0.494)*(0.093-0.073)/(0.53-0.494) &&
	         alkali<=0.093+(silica-0.53)*(0.059-0.093)/(0.57-0.53) && 
	         alkali>=0.073+(silica-0.494)*(0.05-0.073)/(0.52-0.494) &&
	         alkali>=0.05+(silica-0.52)*(0.059-0.05)/(0.57-0.52))
	{
		if (Na2O - 0.02*wtotal > K2O)
		{
			return std::string("mugearite");
		}
		else
		{
			return std::string("shoshonite");
		}
	}
	else if (alkali<=0.093+(silica-0.53)*(0.117-0.093)/(0.576-0.53) &&
	         alkali<=0.117+(silica-0.576)*(0.07-0.117)/(0.63-0.576) && 
	         alkali>=0.093+(silica-0.53)*(0.059-0.093)/(0.57-0.53) &&
	         alkali>=0.059+(silica-0.57)*(0.07-0.059)/(0.63-0.57))
	{
		if (Na2O - 0.02*wtotal > K2O)
		{
			return std::string("benmoreite");
		}
		else
		{
			return std::string("latite");
		}
	}
	else if (alkali<=0.117+(silica-0.576)*(0.117-0.093)/(0.576-0.53) &&
	         silica<=0.69 && 
	         alkali>=0.117+(silica-0.576)*(0.07-0.117)/(0.63-0.576) &&
	         alkali>=0.07+(silica-0.63)*(0.08-0.07)/(0.69-0.63))
	{
		// Distinguish trachyte from trachydacite
		double felsic = nSiO2 + orc + ab + an + lc + ne;
		if (nSiO2 < 0.2*felsic)
		{
			return std::string("trachyte");
		}
		else
		{
			return std::string("trachydacite");
		}
	}
	else if (alkali<=0.094+(silica-0.45)*(0.115-0.094)/(0.484-0.45) &&
	         alkali<=0.115+(silica-0.484)*(0.093-0.115)/(0.53-0.484) && 
	         alkali>=0.094+(silica-0.45)*(0.073-0.094)/(0.494-0.45) &&
	         alkali>=0.073+(silica-0.494)*(0.093-0.073)/(0.53-0.494))
	{
		return std::string("phonotephrite");
	}
	else if (alkali>=0.14+(silica-0.525)*(0.117-0.14)/(0.576-0.525) &&
	         alkali>=0.117+(silica-0.576)*(0.117-0.093)/(0.576-0.53))
	{
		return std::string("phonolite");
	}
	else
	{
		return std::string("<undetermined>");
	}
}