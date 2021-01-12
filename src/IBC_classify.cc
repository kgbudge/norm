/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * IBC_classify.cc
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
std::string IBC_classify()
{
	// Determine the IBC classification

	if (nNa2O + nK2O > nAl2O3)
	{
		// Peralkaline. 
		
		double F = FeO + 0.8998*Fe2O3;

		if (Al2O3 > 1.33*F)
	   		return std::string("comendite");
		else
			return std::string("pantellerite");
	}
	else
	{
	    double Xnep = ne + 0.6*ab;
	  	double Xolp = ol + 0.75*hy;
		double XQp = Q + 0.4*ab + 0.25*hy;
		double rnorm = 100.0/(Xnep + Xolp + XQp);
		Xnep *= rnorm;
		Xolp *= rnorm;
		XQp *= rnorm;
		double P = 100*an/(an+ab+(5./3.)*ne);
		double XA = Na2O + K2O;
		double XF = FeO + 0.8998*Fe2O3;
		double XM = MgO;
		rnorm = 100.0/(XA + XF + XM);
		XA *= rnorm;
		XF *= rnorm;
		XM *= rnorm;
		if (Xolp >= 40.0 && Xnep <= 1.5*XQp || Xolp <= 40 && Xnep < 15 + 0.8889*XQp)
		{
			// Subalkaline
			double XFcrit = 30.0 + 
				XM*(-1.1085 +
				    XM*(0.47776 +
				        XM*(-3.2552e-2 +
				            XM*(1.00178e-3 +
				                XM*(-1.6738e-5 +
				                    XM*(1.5664e-7 +
				                        XM*(-7.7142E-10 +
				                            XM*1.5559e-12)))))));
			                                                       
			if (P<=40 && XF >= XFcrit ||
			    P>=40 && Al2O3*100/wtotal <= 12 + 0.08*P)
			{
				// tholeiitic
				return subalkaline_K_classify() + "tholeiitic " + subalkaline_classify();
			}
			else
			{
				// calc-alkaline
				return subalkaline_K_classify() + "calc-alkaline " + subalkaline_classify();
			}
		}
		else
		{
			// Alkaline
	        double CI = ol + hy + di + mt + il + hm;
			double Xor = orc;
			double Xabp = ab + (5./3.)*ne;
			double Xanp = an;
			rnorm = 100.0/(Xor + Xabp + Xanp);
			Xor *= rnorm;
			Xanp *= rnorm;
			Xabp *= rnorm;
			double Xabpcrit = Xor*(-28.6217 + 
			                       Xor*(9.2090 + 
			                            Xor*(-1.0154 + 
			                                 Xor*(5.3479e-2  +
			                                      Xor*(-1.3525e-3 +
			                                           Xor*1.3162e-5)))));
			if (Xabp >= Xabpcrit)
			{
				// Sodic
				if (ol>25)
				{
					return "picrite basalt";
				}
				else if (CI>= 30 + (5./6.)*(80 - P))
				{
					return "ankaramite";
				}
				else if (CI >= 30 + (50./55.)*P)
				{
					return "nephelinite";
				}
				else if (CI >= 80 - P)
				{
					return "alkali basalt";
				}
				else if (CI >= 50 - P)
				{
					return "hawaiite";
				}
				else if (CI >= 30 - P)
				{
					return "mugearite";
				}
				else if (CI >= 20 - P)
				{
					return "benmoreite";
				}
				else
				{
					return "sodic trachyte";
				}
			}
			else
			{
				// Potassic
				if (ol>25)
				{
					return "alkalic picrite basalt";
				}
				else if (CI>= 20 + (6./7.)*(80 - P))
				{
					return "ankaramite";
				}
				else if (CI >= 70 - P)
				{
					return "alkali basalt";
				}
				else if (CI >= 40 - P)
				{
					return "trachybasalt";
				}
				else if (CI >= 20 - P)
				{
					return "tristanite";
				}
				else
				{
					return "trachyte";
				}
			}
		}
	}
}