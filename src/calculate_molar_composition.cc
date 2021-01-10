/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * calculate_molar_composition.cc
 * Copyright (C) 2021 Kent G. Budge <kgb@kgbudge.com>
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
void calculate_molar_composition()
{
	// Calculate mole percentages

	nSiO2 = SiO2/60.09;
	nTiO2 = TiO2/79.90;
	nAl2O3 = Al2O3/101.96;
	nFe2O3 = Fe2O3/159.69;
	nFeO = FeO/71.85;
	nMnO = MnO/70.94;
	nMgO = MgO/40.30;
	nCaO = CaO/56.08;
	nNa2O = Na2O/61.98;
	nK2O = K2O/94.20;
	nP2O5 = P2O5/141.94;
	nS = S/32.07;
	nCr2O3 = Cr2O3/151.99;

	ntotal = nSiO2 + nTiO2 + nAl2O3 + nFe2O3 + nFeO + nMnO + nMgO + nCaO + nNa2O + nK2O + nP2O5 + nS + nCr2O3;
	if (ntotal == 0.0) return;

	double rnorm = 100.0/ntotal;
	nSiO2 *= rnorm;
	nTiO2 *= rnorm;
	nAl2O3 *= rnorm;
	nFe2O3 *= rnorm;
	nFeO *= rnorm;
	nMnO *= rnorm;
	nMgO *= rnorm;
	nCaO *= rnorm;
	nNa2O *= rnorm;
	nK2O *= rnorm;
	nP2O5 *= rnorm;
	nS *= rnorm;
	nCr2O3 *= rnorm;
}
