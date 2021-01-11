// subalkaline_classify.cc
//
// Copyright (C) 2021 - Kent G. Budge
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "composition.hh"

std::string subalkaline_classify()
{
	double CI = ol + hy + di + mt + il + hm;
	double P = 100*an/(an+ab+(5./3.)*ne);
	if (ol>25)
	{
		return "picrite basalt";
	}
	else if (CI>=70-P)
	{
		return "basalt";
	}
	else if (CI>=30-0.6*P)
	{
		return "andesite";
	}
	else if (CI>=20-P)
	{
		return "dacite";
	}
	else
	{
		return "rhyolite";
	}
}

std::string subalkaline_K_classify()
{
	double Xor = orc;
	double Xabp = ab + (5./3.)*ne;
	double Xanp = an;
	double rnorm = 100.0/(Xor + Xabp + Xanp);
	Xor *= rnorm;
	Xanp *= rnorm;
	Xabp *= rnorm;

	double Xabpcrit = -0.35 + 
		Xor*(20.4400 +
		     Xor*(-3.6890 +
		          Xor*(3.0554e-1 +
		               Xor*(-1.20000e-2 +
		                    Xor*(2.1157e-4 +
		                         Xor*-1.3482e-6)))));
		     
	if (Xabp <= Xabpcrit)
	{
		return "K-rich ";
	}
	else
	{
		Xabpcrit = 20.2 +
			Xor*(13.4379 +
			     Xor*(-2.2698 +
			          Xor*(2.0202e-1
			               + Xor*(-9.3497e-3 +
			                      Xor*(2.1187e-4 +
			                           Xor*-1.8496e-6)))));
		if (Xabp >= Xabpcrit)
		{
			return "K-poor ";
		}
		else
		{
			return "";
		}
	}
}
