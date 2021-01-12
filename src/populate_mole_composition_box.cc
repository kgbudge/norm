/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * populate_mole_composition_box .cc
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

#include "kgb/tostring.h"

#include "composition.hh"
#include "gui.hh"

//-----------------------------------------------------------------------------//
void populate_mole_composition_box()
{
	text_nSiO2->set_text(tostring(nSiO2, 2));
	text_nTiO2->set_text(tostring(nTiO2, 2));
	text_nAl2O3->set_text(tostring(nAl2O3, 2));
	text_nFe2O3->set_text(tostring(nFe2O3, 2));
	text_nFeO->set_text(tostring(nFeO, 2));
	text_nMnO->set_text(tostring(nMnO, 2));
	text_nMgO->set_text(tostring(nMgO, 2));
	text_nCaO->set_text(tostring(nCaO, 2));
	text_nNa2O->set_text(tostring(nNa2O, 2));
	text_nK2O->set_text(tostring(nK2O, 2));
	text_nP2O5->set_text(tostring(nP2O5, 2));
	text_nS->set_text(tostring(nS, 2));
	text_nCr2O3->set_text(tostring(nCr2O3, 2));
}
