/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
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

#include <gtkmm.h>

#include "composition.hh"

//-----------------------------------------------------------------------------//
void calculate_CIPW_norm()
{	
	// Determine the CIPW norm. Weight composition should already be set.

	// Treat manganese as ferrous iron

	double FeO = nFeO + nMnO;

	// 1.

    ap = nP2O5;
	double CaO = nCaO - 3.33*ap;
	if (CaO<0.0)
	{
		// Phosphate just about always occurs as apatite; all other phosphate species are rare.
		throw bad_CIPW("P2O5 too high for CaO");
	}

	// 2.

    pr = nS;
	FeO -= 0.5*pr;
	if (FeO<0.0)
	{
		// Sulfur might occur as anhydrite or as rare sulfate minerals, but
		// this would be very unusual in volcanic rock. Native sulfur is probably
		// more likely.
		throw bad_CIPW("S too high for FeO");
	}

	// 3.

    cm = nCr2O3;
	FeO -= cm;
	if (FeO<0.0)
	{
		throw bad_CIPW("Cr2O3 too high for FeO");
	}

	// 4.

	double TiO2 = nTiO2;
	if (TiO2<=FeO)
	{
		il = TiO2;
		TiO2 = 0.0;
		FeO -= il;
	}
	else
	{
		il = FeO;
		FeO = 0.0;
		TiO2 -= il;
	}

	// 5. Fluorine. Not coded at present. (Would go to fluorine.)
	// 6. Carbonate. Not coded at present. (Would go to calcite, then dolomite, then ankarite.)
	// 7. Zirconium. Not coded at present. Would to to zircon.

	// 8.

	double Al2O3;
	if (nAl2O3<nK2O)
	{
		throw bad_CIPW("K2O too high for Al2O3"); 
	}
	orc = nK2O;
	Al2O3 = nAl2O3 - orc;
	double SiO2 = nSiO2 - 6*orc;   

	// 9.

	double Na2O;
	if (Al2O3>=nNa2O)
	{
		ab = nNa2O;
		Na2O = 0.0;
		Al2O3 -= ab;
	}
	else
	{
		ab = Al2O3;
		Al2O3 = 0.0;
		Na2O -= ab;
	}
	SiO2 -= 6*ab;

	// 10.

	if (CaO>=Al2O3)
	{
		an = Al2O3;
		Al2O3 = 0.0;
		CaO -= an;
		C = 0;
	}
	else
	{
		an = CaO;
		CaO = 0.0;
		C = Al2O3 - an;
		Al2O3 = 0.0;
	}
	SiO2 -= 2*an;

	// 10a.

	if (CaO >= TiO2)
	{
		tn = TiO2;
		ru = 0.0;
		CaO -= tn;
	}
	else
	{
		tn = CaO;
		CaO = 0.0;
		ru = TiO2 - tn;
	}
	SiO2 -= tn;

	// 11.

	double Fe2O3;
	if (nFe2O3>=Na2O)
	{
		ac = Na2O;
		Na2O = 0.0;
		Fe2O3 = nFe2O3 - ac;
	}
	else
	{
		ac = nFe2O3;
		Fe2O3 = 0;
		Na2O -= ac;
	}
	SiO2 -= 4*ac;

	// 12.

	SiO2 -= Na2O; // nNa2O is now sodium metasilicate
	ns = Na2O;
	Na2O = 0.0;

	// 13.

	if (FeO>=Fe2O3)
	{
		mt = Fe2O3;
		Fe2O3 = 0.0;
		FeO -= mt;
		hm = 0.0;
	}
	else
	{
		mt = FeO;
		FeO = 0;
		hm = Fe2O3 - mt;
		Fe2O3 = 0;
	}

	// 14.

	double nMgFe = nMgO + FeO;
	rMgFe = nMgO/(nMgFe + 1.0e-100);
    wMgFe = 40.30*nMgO/(40.30*nMgO + 71.85*FeO + 1.0e-100);

	// 15.

	if (nMgFe >= CaO)
	{
		di = CaO;
		CaO = 0;
		nMgFe -= di;
	}
	else
	{
		di = nMgFe;
		nMgFe = 0.0;
		CaO -= di;
	}
	SiO2 -= 2*di;

	// 16.

    wo = CaO;
	SiO2 -= CaO;
	CaO = 0;

	// 17.

    hy = nMgFe;
	nMgFe = 0.0;
	SiO2 -= hy;

	// 18. If silica left, it's quartz. Remaining steps will be noops.

	// 19.

	ol = 0, pf = 0, ne = 0, lc = 0, cs = 0, kp = 0.0;
	if (SiO2<0.0)
	{
		// Silica-undersaturated
		
		double D = -SiO2;
		Q = 0.0;

		// 20.

		if (D<=hy/2)
		{
			ol = D;
			D = 0;
			hy -= 2*ol;
		}
		else
		{
			ol = hy;
			hy = 0.0;
			D -= ol/2;
		}

		// 21.

		if (D<=tn)
		{
			pf = D;
			D = 0.0;
			tn -= pf;
		}
		else
		{
			pf = tn;
			tn = 0.0;
			D -= pf;
		}

		// 22.

		if (D<=4*ab)
		{
			ne = D/4;
			ab -= D/4;
			D = 0.0;
		}
		else
		{
			ne = ab;
			ab = 0.0;
			D -= 4*ne;
		}

		// 23.

		if (D<=2*orc)
		{
			lc = D/2;
			D = 0.0;
			orc -= lc;
		}
		else
		{
			lc = orc;
			orc = 0.0;
			D -= 2*lc;
		}

		// 24.

		if (D<=wo/2)
		{
			cs = D;
			D = 0.0;
			wo -= 2*D;
		}
		else
		{
			cs = wo/2;
			wo = 0.0;
			D -= cs;
		}

		// 25.

		if (D<=di)
		{
			cs += D/2;
			ol += D/2;
			di -= D;
			D = 0.0;
		}
		else
		{
			cs += di/2;
			ol += di/2;
			D -= di;
			di = 0.0;
		}

		// 26.

		kp = D/2;
		lc -= D/2;
		D = 0.0;

		if (D>0.0 || lc<0.0)
		{
			throw bad_CIPW("Silica too undersaturated");
		}
	}
	else
	{
		// silica-oversaturated
		Q = SiO2;
	}


	// Convert to weight fraction for differentiation index

	ap *= 336.21;
	il *= 151.75;
	orc *= 556.67;
	ab *= 524.46;
	an *= 278.21;
	C *= 101.96;
	ac *= 462.02;
	ns *= 122.07;  // sodium metasilicate
	mt *= 231.54;
	hm *= 159.69;
	di *= (216.55*rMgFe + 248.09*(1-rMgFe));
	wo *= 116.17;
	hy *= (100.39*rMgFe + 131.93*(1-rMgFe));
	Q *= 60.09;
	ol *= (140.69*rMgFe + 203.77*(1-rMgFe));
	tn *= 196.07;
	ru *= 79.90;
	pf *= 135.98;
	ne *= 284.11;
	lc *= 436.5;
	cs *= 86.12;
	pr *= 59.98;
	cm *= 223.84;
	kp *= 316.33;

	double total = ap + il + orc + ab + an + C + ac + ns + mt + hm 
		+ di + wo + hy + Q + ol + tn + ru + pf
		+ ne + lc + cs + pr + cm + kp;

	double rnorm = 100.0/total;

	ap *= rnorm;
	il *= rnorm;
	orc *= rnorm;
	ab *= rnorm;
	an *= rnorm;
	C *= rnorm;
	ac *= rnorm;
	ns *= rnorm;
	mt *= rnorm;
	hm *= rnorm;
	di *= rnorm;
	wo *= rnorm;
	hy *= rnorm;
	Q *= rnorm;
	ol *= rnorm;
	tn *= rnorm;
	ru *= rnorm;
	pf *= rnorm;
	ne *= rnorm;
	lc *= rnorm;
	cs *= rnorm;
	pr *= rnorm;
	cm *= rnorm;
	kp *= rnorm;
}