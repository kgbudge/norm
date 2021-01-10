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
#include <iostream>
#include <fstream>

#include "kgb/tostring.h"

#include "config.h"


#ifdef ENABLE_NLS
#  include <libintl.h>
#endif



/* For testing propose use the local (not installed) ui file */
//#define UI_FILE PACKAGE_DATA_DIR"/ui/norm.ui"
#define UI_FILE "src/norm.ui"

//-----------------------------------------------------------------------------//
class CIPW_Columns : public Gtk::TreeModelColumnRecord
{
public:

  CIPW_Columns()
    { add(m_col_text); add(m_col_number); }

  Gtk::TreeModelColumn<Glib::ustring> m_col_text;
  Gtk::TreeModelColumn<double> m_col_number;
};

//-----------------------------------------------------------------------------//
using namespace std;

Gtk::Window* main_win;

Gtk::Entry *entry_name;

Gtk::Entry *entry_SiO2;
Gtk::Entry *entry_TiO2;
Gtk::Entry *entry_Al2O3;
Gtk::Entry *entry_Fe2O3;
Gtk::Entry *entry_FeO;
Gtk::Entry *entry_MnO;
Gtk::Entry *entry_MgO;
Gtk::Entry *entry_CaO;
Gtk::Entry *entry_Na2O;
Gtk::Entry *entry_K2O;
Gtk::Entry *entry_P2O5;
Gtk::Entry *entry_S;
Gtk::Entry *entry_Cr2O3;

Gtk::Label *text_nSiO2;
Gtk::Label *text_nTiO2;
Gtk::Label *text_nAl2O3;
Gtk::Label *text_nFe2O3;
Gtk::Label *text_nFeO;
Gtk::Label *text_nMnO;
Gtk::Label *text_nMgO;
Gtk::Label *text_nCaO;
Gtk::Label *text_nNa2O;
Gtk::Label *text_nK2O;
Gtk::Label *text_nP2O5;
Gtk::Label *text_nS;
Gtk::Label *text_nCr2O3;

Gtk::Label *text_total;

Gtk::Label *text_ibc_family;
Gtk::Label *text_tas;
Gtk::Label *text_iugs;

Gtk::Label *text_MgNo;
Gtk::Label *text_DI;

Gtk::TreeView *tree_view_CIPW;

double SiO2;
double TiO2;
double Al2O3;
double Fe2O3;
double FeO;
double MnO;
double MgO;
double CaO;
double Na2O;
double K2O;
double P2O5;
double S;
double Cr2O3;

string file;
string name;

//-----------------------------------------------------------------------------//
void update()
{
	name = entry_name->get_text();

	string text = entry_SiO2->get_text();
	SiO2 = atof(text.c_str());
	text = entry_TiO2->get_text();
	TiO2 = atof(text.c_str());
	text = entry_Al2O3->get_text();
	Al2O3 = atof(text.c_str());
	text = entry_Fe2O3->get_text();
	Fe2O3 = atof(text.c_str());
	text = entry_FeO->get_text();
	FeO = atof(text.c_str());
	text = entry_MnO->get_text();
	MnO = atof(text.c_str());
	text = entry_MgO->get_text();
	MgO = atof(text.c_str());
	text = entry_CaO->get_text();
	CaO = atof(text.c_str());
	text = entry_Na2O->get_text();
	Na2O = atof(text.c_str());
	text = entry_K2O->get_text();
	K2O = atof(text.c_str());
	text = entry_P2O5->get_text();
	P2O5 = atof(text.c_str());
	text = entry_S->get_text();
	S = atof(text.c_str());
	text = entry_Cr2O3->get_text();
	Cr2O3 = atof(text.c_str());

	double wtotal = SiO2 + TiO2 + Al2O3 + Fe2O3 + FeO + MnO + MgO + CaO + Na2O + K2O + P2O5 + S + Cr2O3;
	text_total->set_text(tostring(wtotal));

	// Calculate mole percentages
	
	double nSiO2 = SiO2/60.09;
	double nTiO2 = TiO2/79.90;
	double nAl2O3 = Al2O3/101.96;
	double nFe2O3 = Fe2O3/159.69;
	double nFeO = FeO/71.85;
	double nMnO = MnO/70.94;
	double nMgO = MgO/40.30;
	double nCaO = CaO/56.08;
	double nNa2O = Na2O/61.98;
	double nK2O = K2O/94.20;
	double nP2O5 = P2O5/141.94;
	double nS = S/32.07;
	double nCr2O3 = Cr2O3/151.99;
	
	double total = nSiO2 + nTiO2 + nAl2O3 + nFe2O3 + nFeO + nMnO + nMgO + nCaO + nNa2O + nK2O + nP2O5 + nS + nCr2O3;

	if (total==0.0) return;

	// Magnesium number

	text_MgNo->set_text(tostring((int)(1000*nMgO/(nMgO+nFeO)+0.5)/10.));

	double rnorm = 100.0/total;
	nSiO2 *= rnorm;
	text_nSiO2->set_text(tostring(nSiO2));
	nTiO2 *= rnorm;
	text_nTiO2->set_text(tostring(nTiO2));
	nAl2O3 *= rnorm;
	text_nAl2O3->set_text(tostring(nAl2O3));
	nFe2O3 *= rnorm;
	text_nFe2O3->set_text(tostring(nFe2O3));
	nFeO *= rnorm;
	text_nFeO->set_text(tostring(nFeO));
	nMnO *= rnorm;
	text_nMnO->set_text(tostring(nMnO));
	nMgO *= rnorm;
	text_nMgO->set_text(tostring(nMgO));
	nCaO *= rnorm;
	text_nCaO->set_text(tostring(nCaO));
	nNa2O *= rnorm;
	text_nNa2O->set_text(tostring(nNa2O));
	nK2O *= rnorm;
	text_nK2O->set_text(tostring(nK2O));
	nP2O5 *= rnorm;
	text_nP2O5->set_text(tostring(nP2O5));
	nS *= rnorm;
	text_nS->set_text(tostring(nS));
	nCr2O3 *= rnorm;
	text_nCr2O3->set_text(tostring(nCr2O3));
	
	// Determine the CIPW norm

	bool good = true;

	// Treat manganese as ferrous iron

	nFeO += nMnO;

	// 1.

	double ap = nP2O5;
	nP2O5 = 0.0;
	nCaO -= 3.33*ap;
	if (nCaO<0.0)
	{
		// Phosphate just about always occurs as apatite; all other phosphate species are rare.
		Gtk::MessageDialog dialog(*main_win, "CIPW Norm Fail");
		dialog.set_secondary_text("P2O5 too high for CaO");
		dialog.run();
		
		good = false;
	}
	
	// 2.

	double pr = nS;
	nS = 0.0;
	nFeO -= 0.5*pr;
	if (good && nFeO<0.0)
	{
		// Sulfur might occur as anhydrite or as rare sulfate minerals, but
		// this would be very unusual in volcanic rock. Native sulfur is probably
		// more likely.
		Gtk::MessageDialog dialog(*main_win, "CIPW Norm Fail");
		dialog.set_secondary_text("S too high for FeO");
		dialog.run();
		
		good = false;
	}

	// 3.

	double cm = nCr2O3;
	nCr2O3 = 0.0;
	nFeO -= cm;
	if (good && nFeO<0.0)
	{
		Gtk::MessageDialog dialog(*main_win, "CIPW Norm Fail");
		dialog.set_secondary_text("Cr2O3 too high for FeO");
		dialog.run();
		
		good = false;
	}

	// 4.

	double il;
	if (nTiO2<=nFeO)
	{
		il = nTiO2;
		nTiO2 = 0.0;
		nFeO -= il;
	}
	else
	{
		il = nFeO;
		nFeO = 0.0;
		nTiO2 -= il;
	}

	// 5. Fluorine. Not coded at present. (Would go to fluorine.)
	// 6. Carbonate. Not coded at present. (Would go to calcite, then dolomite, then ankarite.)
	// 7. Zirconium. Not coded at present. Would to to zircon.

	// 8.

	double orc;
	if (nAl2O3>=nK2O)
	{
		orc = nK2O;
		nK2O = 0.0;
		nAl2O3 -= orc;
	}
	else
	{
		orc = nAl2O3;
		nAl2O3 = 0.0;
		nK2O -= orc;
	}
	nSiO2 -= 6*orc;   

	// 8a.

	nSiO2 -= nK2O; // nK2O is now potassium metasilicate

	// 9.

	double ab;
	if (nAl2O3>=nNa2O)
	{
		ab = nNa2O;
		nNa2O = 0.0;
		nAl2O3 -= ab;
	}
	else
	{
		ab = nAl2O3;
		nAl2O3 = 0.0;
		nNa2O -= ab;
	}
	nSiO2 -= 6*ab;

	// 10.

	double an;
	if (nCaO>=nAl2O3)
	{
		an = nAl2O3;
		nAl2O3 = 0.0;
		nCaO -= an;
	}
	else
	{
		an = nCaO;
		nCaO = 0.0;
		nAl2O3 -= an;
	}
	nSiO2 -= 2*an;

	// 10a.

	double sp;
	if (nCaO >= nTiO2)
	{
		sp = nTiO2;
		nTiO2 = 0.0;
		nCaO -= sp;
	}
	else
	{
		sp = nCaO;
		nCaO = 0.0;
		nTiO2 -= sp;
	}
	nSiO2 -= sp;

	// 11.

	double ac;
	if (nFe2O3>=nNa2O)
	{
		ac = nNa2O;
		nNa2O = 0.0;
		nFe2O3 -= ac;
	}
	else
	{
		ac = nFe2O3;
		nFe2O3 = 0;
		nNa2O -= ac;
	}
	nSiO2 -= 4*ac;

	// 12.

	nSiO2 -= nNa2O; // nNa2O is now sodium metasilicate

	// 13.

	double mt;
	if (nFeO>=nFe2O3)
	{
		mt = nFe2O3;
		nFe2O3 = 0.0;
		nFeO -= mt;
	}
	else
	{
		mt = nFeO;
		nFeO = 0;
		nFe2O3 -= mt;
	}

	// 14.

	double nMgFe = nMgO + nFeO;
	double rMgFe = nMgO/(nMgFe + 1.0e-100);
	double wMgFe = 40.30*nMgO/(40.30*nMgO + 71.85*nFeO + 1.0e-100);
	string sMgFe = tostring(static_cast<int>(wMgFe*100));

	// 15.

	double di;
	if (nMgFe >= nCaO)
	{
		di = nCaO;
		nCaO = 0;
		nMgFe -= di;
	}
	else
	{
		di = nMgFe;
		nMgFe = 0.0;
		nCaO -= di;
	}
	nSiO2 -= 2*di;

	// 16.

	double wo = nCaO;
	nSiO2 -= nCaO;
	nCaO = 0;

	// 17.

	double hy = nMgFe;
	nMgFe = 0.0;
	nSiO2 -= hy;

	// 18. If silica left, it's quartz. Remaining steps will be noops.

	// 19.

	double ol = 0, pf = 0, ne = 0, lc = 0, cs = 0, kp = 0.0;
	if (nSiO2<0.0)
	{
		double D = -nSiO2;
		nSiO2 = 0.0;

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

		if (D<=sp)
		{
			pf = D;
			D = 0.0;
			sp -= pf;
		}
		else
		{
			pf = sp;
			sp = 0.0;
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

		if (good && (D>0.0 || lc<0.0) )
		{
			Gtk::MessageDialog dialog(*main_win, "CIPW Norm Fail");
			dialog.set_secondary_text("Silica too undersaturated");
			dialog.run();

			good = false;
		}
	}

	CIPW_Columns m_Columns;
	Glib::RefPtr<Gtk::ListStore> list_store_CIPW = Gtk::ListStore::create(m_Columns);
	list_store_CIPW->set_sort_column(1, Gtk::SORT_DESCENDING);

	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;

	if (!good)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "<undetermined>";
		row[m_Columns.m_col_number] = 100;
		text_iugs->set_text("<undetermined>");	
	}
	else
	{

		// Convert to weight fraction for differentiation index
		
		ap *= 336.21;
		il *= 151.75;
		orc *= 556.67;
		ab *= 524.46;
		an *= 278.21;
		nAl2O3 *= 101.96;
		ac *= 462.02;
		nNa2O *= 122.07;  // sodium metasilicate
		mt *= 231.54;
		nFe2O3 *= 159.69;
		di *= (216.55*rMgFe + 248.09*(1-rMgFe));
		wo *= 116.17;
		hy *= (100.39*rMgFe + 131.93*(1-rMgFe));
		nSiO2 *= 60.09;
		ol *= (140.69*rMgFe + 203.77*(1-rMgFe));
		sp *= 196.07;
		nTiO2 *= 79.90;
		pf *= 135.98;
		ne *= 284.11;
		nK2O *= 154.279;  // potassium metasilicate
		lc *= 436.5;
		cs *= 86.12;
		pr *= 59.98;
		cm *= 223.84;
		kp *= 316.33;
 
		total = ap + il + orc + ab + an + nAl2O3 + ac + nNa2O + mt + nFe2O3 + di + wo + hy + nSiO2 + ol + sp + nTiO2 + pf
			+ ne + nK2O + lc + cs + pr + cm + kp;
		
		rnorm = 100.0/total;

		ap *= rnorm;
		il *= rnorm;
		orc *= rnorm;
		ab *= rnorm;
		an *= rnorm;
		nAl2O3 *= rnorm;
		ac *= rnorm;
		nNa2O *= rnorm;
		mt *= rnorm;
		nFe2O3 *= rnorm;
		di *= rnorm;
		nCaO *= rnorm;
		hy *= rnorm;
		nSiO2 *= rnorm;
		ol *= rnorm;
		sp *= rnorm;
		nTiO2 *= rnorm;
		pf *= rnorm;
		ne *= rnorm;
		nK2O *= rnorm;
		lc *= rnorm;
		cs *= rnorm;
		pr *= rnorm;
		cm *= rnorm;
		kp *= rnorm;

  	    text_DI->set_text(tostring(nSiO2+orc+ab+ne+lc+kp));

		if (ap>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "apatite";
			row[m_Columns.m_col_number] = ap;
		}

		if (il>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "ilmenite";
			row[m_Columns.m_col_number] = il;
		}

		if (orc>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "orthoclase";
			row[m_Columns.m_col_number] = orc;
		}

		if (ab>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "albite";
			row[m_Columns.m_col_number] = ab;
		}

		if (an>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "anorthite";
			row[m_Columns.m_col_number] = an;
		}

		if (nAl2O3>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "corundum";
			row[m_Columns.m_col_number] = nAl2O3;
		}

		if (ac>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "acmite";
			row[m_Columns.m_col_number] = ac;
		}

		if (nNa2O>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "sodium metasilicate";
			row[m_Columns.m_col_number] = nNa2O;
		}

		if (mt>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "magnetite";
			row[m_Columns.m_col_number] = mt;
		}

		if (nFe2O3>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "hematite";
			row[m_Columns.m_col_number] = nFe2O3;
		}

		if (di>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "augite ("+sMgFe+')';
			row[m_Columns.m_col_number] = di;
		}

		if (wo>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "wollastonite";
			row[m_Columns.m_col_number] = wo;
		}

		if (hy>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "hypersthene ("+sMgFe+')';
			row[m_Columns.m_col_number] = hy;
		}

		if (nSiO2>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "quartz";
			row[m_Columns.m_col_number] = nSiO2;
		}

		if (ol>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "olivine ("+sMgFe+')';
			row[m_Columns.m_col_number] = ol;
		}

		if (sp>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "sphene";
			row[m_Columns.m_col_number] = sp;
		}

		if (nTiO2>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "rutile";
			row[m_Columns.m_col_number] = nTiO2;
		}

		if (pf>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "perovskite";
			row[m_Columns.m_col_number] = pf;
		}

		if (ne>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "nepheline";
			row[m_Columns.m_col_number] = ne;
		}

		if (nK2O>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "potassium metasilicate";
			row[m_Columns.m_col_number] = nK2O;
		}

		if (lc>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "leucite";
			row[m_Columns.m_col_number] = lc;
		}

		if (cs>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "calcium orthosilicate";
			row[m_Columns.m_col_number] = cs;
		}

		if (pr>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "pyrite";
			row[m_Columns.m_col_number] = pr;
		}

		if (cm>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "chromite";
			row[m_Columns.m_col_number] = cm;
		}

		if (kp>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "kaliophilite";
			row[m_Columns.m_col_number] = kp;
		}

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
			text_tas->set_text("picrite");	
		}
		else if (titanium > 0.01)
		{
			text_tas->set_text("meimechite");	
		}
		else
		{
			text_tas->set_text("komatiite");	
		}
	}
	else  if (silica>=0.53 && silica<0.63 && magnesium>=0.08 && titanium < 0.005)
	{
		text_tas->set_text("boninite");	
	}
	// Not high magnesium
	else if ((silica <= 0.41 || alkali>=0.07+(silica-0.41)*(0.14-0.07)/(0.525-0.41)) &&
		         alkali<=0.14+(silica-0.525)*(0.117-0.14)/(0.576-0.525))
	{
		// Further criteria to separate leucitite, nephelinite, melanephelinite, basanite, and tephrite
		if (K2O >= Na2O)
		{
		  text_tas->set_text("leucitite");	
		}
		else if (ne>=20)
		{
		  text_tas->set_text("nephelinite");	
		}
		else if (ab>=5)
		{
			if (ol > 10)
			{
		      text_tas->set_text("basanite");	
			}
			else
			{
		      text_tas->set_text("tephrite");	
			}
		}
		else
		{
		  text_tas->set_text("melanephelinite");	
		}
	}
	else if (silica>=0.41 && silica<=0.45 && alkali<=0.03)
	{
		text_tas->set_text("picrobasalt");
	}
	else if (silica>=0.45 && silica<=0.52 && alkali<=0.05)
	{
		text_tas->set_text("basalt");
	}
	else if (silica>=0.52 && silica<=0.57 && alkali<=0.05+(silica-0.52)*(0.059-0.05)/(0.57-0.52))
	{
		text_tas->set_text("basaltic andesite");
	}
	else if (silica>=0.57 && silica<=0.63 && alkali<=0.059+(silica-0.57)*(0.07-0.059)/(0.63-0.57))
	{
		text_tas->set_text("andesite");
	}
	else if (silica>=0.63 && 
	         alkali<=0.07+(silica-0.63)*(0.08-0.07)/(0.69-0.63) &&
	         alkali<=0.08+(silica-0.69)*(0.0-0.08)/(0.77-0.69))
	{
		text_tas->set_text("dacite");
	}
	else if (silica>=0.69 && alkali>=0.08+(silica-0.69)*(0.0-0.08)/(0.77-0.69))
	{
		text_tas->set_text("rhyolite");
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
		  text_tas->set_text("leucitite");	
		}
		else if (ne>=20)
		{
		  text_tas->set_text("nephelinite");	
		}
		else if (ab>=5)
		{
			if (ol > 10)
			{
		      text_tas->set_text("basanite");	
			}
			else
			{
		      text_tas->set_text("tephrite");	
			}
		}
		else
		{
		  text_tas->set_text("melanephelinite");	
		}
	}
	else if (alkali<=0.05+(silica-0.45)*(0.073-0.05)/(0.494-0.45) &&
	         alkali<=0.073+(silica-0.494)*(0.05-0.073)/(0.52-0.494) && 
	         alkali>=0.05)
	{
		if (Na2O - 0.02*wtotal > K2O)
		{
		    text_tas->set_text("hawaiite");
		}
		else
		{
	   	    text_tas->set_text("potassic trachybasalt");
		}
	}
	else if (alkali<=0.073+(silica-0.494)*(0.093-0.073)/(0.53-0.494) &&
	         alkali<=0.093+(silica-0.53)*(0.059-0.093)/(0.57-0.53) && 
	         alkali>=0.073+(silica-0.494)*(0.05-0.073)/(0.52-0.494) &&
	         alkali>=0.05+(silica-0.52)*(0.059-0.05)/(0.57-0.52))
	{
		if (Na2O - 0.02*wtotal > K2O)
		{
		    text_tas->set_text("mugearite");
		}
		else
		{
	   	    text_tas->set_text("shoshonite");
		}
	}
	else if (alkali<=0.093+(silica-0.53)*(0.117-0.093)/(0.576-0.53) &&
	         alkali<=0.117+(silica-0.576)*(0.07-0.117)/(0.63-0.576) && 
	         alkali>=0.093+(silica-0.53)*(0.059-0.093)/(0.57-0.53) &&
	         alkali>=0.059+(silica-0.57)*(0.07-0.059)/(0.63-0.57))
	{
		if (Na2O - 0.02*wtotal > K2O)
		{
		    text_tas->set_text("benmoreite");
		}
		else
		{
	   	    text_tas->set_text("latite");
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
		    text_tas->set_text("trachyte");
		}
		else
		{
		    text_tas->set_text("trachydacite");
		}
	}
	else if (alkali<=0.094+(silica-0.45)*(0.115-0.094)/(0.484-0.45) &&
	         alkali<=0.115+(silica-0.484)*(0.093-0.115)/(0.53-0.484) && 
	         alkali>=0.094+(silica-0.45)*(0.073-0.094)/(0.494-0.45) &&
	         alkali>=0.073+(silica-0.494)*(0.093-0.073)/(0.53-0.494))
	{
		text_tas->set_text("phonotephrite");
	}
	else if (alkali>=0.14+(silica-0.525)*(0.117-0.14)/(0.576-0.525) &&
	         alkali>=0.117+(silica-0.576)*(0.117-0.093)/(0.576-0.53))
	{
		text_tas->set_text("phonolite");
	}
	else
	{
		text_tas->set_text("<undetermined>");
	}

	// Determine the IBC classification

	if (nNa2O + nK2O > nAl2O3)
	{
		text_ibc_family->set_text("PERALKALINE");
	}
	else
	{
		double A = 100*(Na2O + K2O)/wtotal;
		double bSiO2 = 39.0 + A*(3.9492 + A*(-2.1111 + A*(0.86096 + A*(-0.15188 + A*(1.2030e-2 + A*(-3.3539e-4))))));
		if (SiO2*100/wtotal<bSiO2)
		{
			text_ibc_family->set_text("ALKALINE");
		}
		else
		{
			text_ibc_family->set_text("SUBALKALINE");
		}
	}

		// Determine IUGS classification

		// Convert to volume fraction

		ap /=3.16;
		il /=4.9;
		orc /=2.63;
		ab /=2.6;
		an /=2.75;
		nAl2O3 /=3.95;
		ac /=3.55;
		nNa2O /=2.61;
		mt /=5.18;
		nFe2O3 /=5.26;
		di /=(3.28*wMgFe + 3.56*(1-wMgFe));
		nCaO /=2.86;
		hy /=(3.4*wMgFe + 3.9*(1-wMgFe));
		nSiO2 /=2.65;
		ol /=(3.2*wMgFe + 4.5*(1-wMgFe));
		sp /=3.48;
		nTiO2 /=4.23;
		pf /=3.98;
		ne /=2.59;
		nK2O /=2.61; // lacking density of potassium silicate, we assume same molar volume as sodium metasilicate
		lc /=2.50;
		cs /=2.9;
		pr /=5.0;
		cm /=4.8;
		kp /=2.59;
 
		total = ap + il + orc + ab + an + nAl2O3 + ac + nNa2O + mt + nFe2O3 + di + nCaO + hy + nSiO2 + ol + sp + nTiO2 + pf
			+ ne + nK2O + lc + cs + pr + cm + kp;
		
		rnorm = 100.0/total;

		ap *= rnorm;
		il *= rnorm;
		orc *= rnorm;
		ab *= rnorm;
		an *= rnorm;
		nAl2O3 *= rnorm;
		ac *= rnorm;
		nNa2O *= rnorm;
		mt *= rnorm;
		nFe2O3 *= rnorm;
		di *= rnorm;
		nCaO *= rnorm;
		hy *= rnorm;
		nSiO2 *= rnorm;
		ol *= rnorm;
		sp *= rnorm;
		nTiO2 *= rnorm;
		pf *= rnorm;
		ne *= rnorm;
		nK2O *= rnorm;
		lc *= rnorm;
		cs *= rnorm;
		pr *= rnorm;
		cm *= rnorm;
		kp *= rnorm;

		double Q = nSiO2;
		double An = 100*an/(an+ab);
		double A = orc + (An>0.05? 0 : ab);
		double P = an  + (An>0.05? ab : 0);
		double F = ne + lc + kp;
		double M = ol + ac + di + hy + mt + cm + nFe2O3 + il + sp + pf + nTiO2 + pr + ap + nAl2O3;
		double Pfrac = 100*P/(A+P);

		if (M<90)
		{
			if (F==0)
			{
				if (Q<=5)
				{
					if (Pfrac<=10)
					{
						text_iugs->set_text("ALKALI-FELDSPAR SYENITE\ntrachyte");
					}
					else if (Pfrac<=35)
					{
						text_iugs->set_text("SYENITE\ntrachyte");
					}
					else if (Pfrac<=65)
					{
						text_iugs->set_text("MONZONITE\nlatite");
					}
					else if (Pfrac<=90)
					{
						if (An>50)
						{
							text_iugs->set_text("MONZO-GABBRO\nbasalt");
						}
						else
						{
							text_iugs->set_text("MONZO-DIORITE\nandesite");
						}
					}
					else
					{
						if (An>50)
						{
							text_iugs->set_text("GABBRO\nbasalt");
						}
						else
						{
							text_iugs->set_text("DIORITE\nandesite");
						}
					}
				}
				else if (Q<=20)
				{
					if (Pfrac<=10)
					{
						text_iugs->set_text("QUARTZ ALKALI-FELDSPAR SYENITE\ntrachyte");
					}
					else if (Pfrac<=35)
					{
						text_iugs->set_text("QUARTZ SYENITE\nquartz trachyte");
					}
					else if (Pfrac<=65)
					{
						text_iugs->set_text("QUARTZ MONZONITE\nquartz latite");
					}
					else if (Pfrac<=90)
					{
						if (An>50)
						{
							text_iugs->set_text("QUARTZ MONZOGABBRO\nandesite");
						}
						else
						{
							text_iugs->set_text("QUARTZ MONZODIORITE\nandesite");
						}
					}
					else
					{
						if (an>90)
						{
							text_iugs->set_text("QUARTZ ANORTHOSITE");
						}
						else if (An>50)
						{
							text_iugs->set_text("QUARTZ GABBRO\nbasalt");
						}
						else
						{
							text_iugs->set_text("QUARTZ DIORITE\nandesite");
						}
					}
				}
				else if (Q<=60)
				{
					if (Pfrac<=10)
					{
						text_iugs->set_text("ALKALI-FELDSPAR GRANITE\nalkali-feldspar rhyolite");
					}
					else if (Pfrac<=65)
					{
						text_iugs->set_text("GRANITE\nrhyolite");
					}
					else if (Pfrac<=90)
					{
						text_iugs->set_text("GRANODIORITE\ndacite");
					}
					else
					{
						text_iugs->set_text("TONALITE\ndacite");	
					}			
				}
				else if (Q<=90)
				{
					text_iugs->set_text("QUARTZ-RICH GRANITOID\nrhyolite");			
				}
				else
				{
					text_iugs->set_text("QUARTZOLITE\nrhyolite");
				}
			}
			else // F>0
			{
				if (F<=10)
				{
					if (Pfrac<=10)
					{
						text_iugs->set_text("FELDSPATHOID-BEARING ALKALI-FELDSPAR SYENITE\nfeldspathoid-bearing trachyte");
					}
					else if (Pfrac<=35)
					{
						text_iugs->set_text("FELDSPATHOID-BEARING SYENITE\nfeldspathoid-bearing trachyte");	
					}
					else if (Pfrac<=65)
					{
						text_iugs->set_text("FELDSPATHOID-BEARING MONZONITE\nfeldspathoid-bearing latite");	
					}
					else if (Pfrac<=90)
					{
						if (An>50)
						{
							text_iugs->set_text("FELDSPATHOID-BEARING MONZOGABBRO\nfeldspathoid-bearing basalt");	
						}
						else
						{
							text_iugs->set_text("FELDSPATHOID-BEARING MONZODIORITE\nfeldspathoid-bearing basalt");	
						}
					}
					else
					{
						if (An>50)
						{
							text_iugs->set_text("FELDSPATHOID-BEARING GABBRO\nfeldspathoid-bearing basalt");	
						}
						else
						{
							text_iugs->set_text("FELDSPATHOID-BEARING DIORITE\nfeldspathoid-bearing basalt");	
						}
					}
				}
				else if (F<=60)
				{
					if (Pfrac<=10)
					{
						text_iugs->set_text("FELDSPATHOID SYENITE\nphonolite");	
					}
					else if (Pfrac<=50)
					{
						text_iugs->set_text("FELDSPATHOID MONZOSYENITE\ntephritic phonolite");	
					}
					else if (Pfrac<=90)
					{
						if (An>50)
						{
							text_iugs->set_text("FELDSPATHOID MONZOGABBRO\nphonolitic tephrite");	
						}
						else
						{
							text_iugs->set_text("FELDSPATHOID MONZODIORITE\nphonolitic tephrite");	
						}
					}
					else
					{
						if (An>50)
						{
							text_iugs->set_text("FELDSPATHOID GABBRO\nbasanite");	
						}
						else
						{
							text_iugs->set_text("FELDSPATHOID DIORITE\ntephrite");	
						}
					}
				}
				else if (F<=90)
				{
					if (Pfrac<=50)
					{
						text_iugs->set_text("PHONOLITIC FOIDITE\nfoidite");						
					}
					else
					{
						text_iugs->set_text("TEPHRITIC FOIDITE\nfoidite");						
					}
				}
				else
				{
					text_iugs->set_text("FOIDITE\nfoidite");	
				}
			}
		}
		else
		{
			text_iugs->set_text("<ultramafic>");			
		}
	}
		
	tree_view_CIPW->remove_all_columns();
	tree_view_CIPW->set_model(list_store_CIPW);
	tree_view_CIPW->append_column("Mineral", m_Columns.m_col_text);
	tree_view_CIPW->append_column("Wt %", m_Columns.m_col_number);
}

//-----------------------------------------------------------------------------//
void on_new()
{
	file = "";
	name = "";
	entry_name->set_text("");
	entry_SiO2->set_text("0.00");
	entry_TiO2->set_text("0.00");
	entry_Al2O3->set_text("0.00");
	entry_Fe2O3->set_text("0.00");
	entry_FeO->set_text("0.00");
	entry_MnO->set_text("0.00");
	entry_MgO->set_text("0.00");
	entry_CaO->set_text("0.00");
	entry_Na2O->set_text("0.00");
	entry_K2O->set_text("0.00");
	entry_P2O5->set_text("0.00");
	entry_S->set_text("0.00");
	entry_Cr2O3->set_text("0.00");
	update();
}

//-----------------------------------------------------------------------------//
void on_open()
{
	Gtk::FileChooserDialog dialog("Please choose a file",
	                              Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*main_win);

	//Add response buttons the the dialog:
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);

	//Add filters, so that only certain file types can be selected:

	Glib::RefPtr<Gtk::FileFilter> filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_mime_type("text/plain");
	dialog.add_filter(filter_text);

	Glib::RefPtr<Gtk::FileFilter> filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog.add_filter(filter_any);

	//Show the dialog and wait for a user response:
	int result = dialog.run();

	//Handle the response:
	if (result == Gtk::RESPONSE_OK)
	{
		file = dialog.get_filename();
		ifstream in(file.c_str());

		// Read the file contents

		string token;
		in >> token;
		while (in)
		{
			if (token=="name")
			{
				name.clear();
				char c = in.get();
				while (in && isspace(c) && c != '\n')
				{
					c = in.get();
				}
				while (in && c != '\n')
				{
					name += c;
					c = in.get();
				}
				entry_name->set_text(name);
			}
			else if (token=="SiO2")
			{
				in >> token;
				entry_SiO2->set_text(token);
			}
			else if (token=="TiO2")
			{
				in >> token;
				entry_TiO2->set_text(token);
			}
			else if (token=="Al2O3")
			{
				in >> token;
				entry_Al2O3->set_text(token);
			}
			else if (token=="Fe2O3")
			{
				in >> token;
				entry_Fe2O3->set_text(token);
			}
			else if (token=="FeO")
			{
				in >> token;
				entry_FeO->set_text(token);
			}
			else if (token=="MnO")
			{
				in >> token;
				entry_MnO->set_text(token);
			}
			else if (token=="MgO")
			{
				in >> token;
				entry_MgO->set_text(token);
			}
			else if (token=="CaO")
			{
				in >> token;
				entry_CaO->set_text(token);
			}
			else if (token=="Na2O")
			{
				in >> token;
				entry_Na2O->set_text(token);
			}
			else if (token=="K2O")
			{
				in >> token;
				entry_K2O->set_text(token);
			}
			else if (token=="P2O5")
			{
				in >> token;
				entry_P2O5->set_text(token);
			}
			else if (token=="S")
			{
				in >> token;
				entry_S->set_text(token);
			}
			else if (token=="Cr2O3")
			{
				in >> token;
				entry_Cr2O3->set_text(token);
			}
			else
			{
				cerr << token << '?' << endl;
				char c = in.get();
				while (in && c != '\n')
				{
					c = in.get();
				}
			}
			in >> token;
		}
		
		update();
	}
}

//-----------------------------------------------------------------------------//
void do_save()
{
	ofstream out(file.c_str());
	if (!out)
	{
		Gtk::MessageDialog dialog(*main_win, "Save Fail");
		dialog.set_secondary_text("Could not write save file " + file);

		dialog.run();
	}
	else
	{
		out << "name " << name << endl;
		out << "SiO2 " << SiO2 << endl;
		out << "TiO2 " << TiO2 << endl;
		out << "Al2O3 " << Al2O3 << endl;
		out << "Fe2O3 " << Fe2O3 << endl;
		out << "FeO " << FeO << endl;
		out << "MnO " << MnO << endl;
		out << "MgO " << MgO << endl;
		out << "CaO " << CaO << endl;
		out << "Na2O " << Na2O << endl;
		out << "K2O " << K2O << endl;
		out << "P2O5 " << P2O5 << endl;
		out << "S " << S << endl;
		out << "Cr2O3 " << Cr2O3 << endl;
	}
}

//-----------------------------------------------------------------------------//
void on_save_as()
{
	Gtk::FileChooserDialog dialog("Please choose a file",
	                              Gtk::FILE_CHOOSER_ACTION_SAVE);
	dialog.set_transient_for(*main_win);

	//Add response buttons the the dialog:
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Save", Gtk::RESPONSE_OK);

	//Add filters, so that only certain file types can be selected:

	Glib::RefPtr<Gtk::FileFilter> filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_mime_type("text/plain");
	dialog.add_filter(filter_text);

	Glib::RefPtr<Gtk::FileFilter> filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog.add_filter(filter_any);

	//Show the dialog and wait for a user response:
	int result = dialog.run();

	//Handle the response:
	if (result == Gtk::RESPONSE_OK)
	{
		file = dialog.get_filename();
		do_save();
	}
}

//-----------------------------------------------------------------------------//
void on_save()
{
	if (file=="")
	{
		on_save_as();
	}
	else
	{
		do_save();
	}
}

//-----------------------------------------------------------------------------//
void on_quit()
{
	main_win->hide();
}

//-----------------------------------------------------------------------------//
void normalize()
{
	double total = SiO2 + TiO2 + Al2O3 + Fe2O3 + FeO + MnO + MgO + CaO + Na2O + K2O + P2O5 + S + Cr2O3;
	if (total>0.0)
	{
		double rnorm = 100.0/total;
		entry_SiO2->set_text(tostring(SiO2*rnorm));
		entry_TiO2->set_text(tostring(TiO2*rnorm));
		entry_Al2O3->set_text(tostring(Al2O3*rnorm));
		entry_Fe2O3->set_text(tostring(Fe2O3*rnorm));
		entry_FeO->set_text(tostring(FeO*rnorm));
		entry_MnO->set_text(tostring(MnO*rnorm));
		entry_MgO->set_text(tostring(MgO*rnorm));
		entry_CaO->set_text(tostring(CaO*rnorm));
		entry_Na2O->set_text(tostring(Na2O*rnorm));
		entry_K2O->set_text(tostring(K2O*rnorm));
		entry_P2O5->set_text(tostring(P2O5*rnorm));
		entry_S->set_text(tostring(S*rnorm));
		entry_Cr2O3->set_text(tostring(Cr2O3*rnorm));
		update();
	}
}

//-----------------------------------------------------------------------------//
int
main (int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);


	//Load the Glade file and instiate its widgets:
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file(UI_FILE);
	}
	catch (const Glib::FileError & ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	builder->get_widget("main_window", main_win);


	if (main_win)
	{
		// Hook up all the actions
		Gtk::ImageMenuItem *menu_item;
		builder->get_widget("menu_file_new", menu_item);
		menu_item->signal_activate().connect(sigc::ptr_fun(on_new)); 
		builder->get_widget("menu_file_open", menu_item);
		menu_item->signal_activate().connect(sigc::ptr_fun(on_open)); 
		builder->get_widget("menu_file_save", menu_item);
		menu_item->signal_activate().connect(sigc::ptr_fun(on_save)); 
		builder->get_widget("menu_file_save_as", menu_item);
		menu_item->signal_activate().connect(sigc::ptr_fun(on_save_as)); 
		builder->get_widget("menu_file_quit", menu_item);
		menu_item->signal_activate().connect(sigc::ptr_fun(on_quit)); 
				
		builder->get_widget("entry_name", entry_name);
		entry_name->signal_activate().connect(sigc::ptr_fun(update));

		builder->get_widget("entry_SiO2", entry_SiO2);
		entry_SiO2->signal_activate().connect(sigc::ptr_fun(update));
		builder->get_widget("entry_TiO2", entry_TiO2);
		entry_TiO2->signal_activate().connect(sigc::ptr_fun(update));
		builder->get_widget("entry_Al2O3", entry_Al2O3);
		entry_Al2O3->signal_activate().connect(sigc::ptr_fun(update));
		builder->get_widget("entry_Fe2O3", entry_Fe2O3);
		entry_Fe2O3->signal_activate().connect(sigc::ptr_fun(update));
		builder->get_widget("entry_FeO", entry_FeO);
		entry_FeO->signal_activate().connect(sigc::ptr_fun(update));
		builder->get_widget("entry_MnO", entry_MnO);
		entry_MnO->signal_activate().connect(sigc::ptr_fun(update));
		builder->get_widget("entry_MgO", entry_MgO);
		entry_MgO->signal_activate().connect(sigc::ptr_fun(update));
		builder->get_widget("entry_CaO", entry_CaO);
		entry_CaO->signal_activate().connect(sigc::ptr_fun(update));
		builder->get_widget("entry_Na2O", entry_Na2O);
		entry_Na2O->signal_activate().connect(sigc::ptr_fun(update));
		builder->get_widget("entry_K2O", entry_K2O);
		entry_K2O->signal_activate().connect(sigc::ptr_fun(update));
		builder->get_widget("entry_P2O5", entry_P2O5);
		entry_P2O5->signal_activate().connect(sigc::ptr_fun(update));
		builder->get_widget("entry_S", entry_S);
		entry_S->signal_activate().connect(sigc::ptr_fun(update));
		builder->get_widget("entry_Cr2O3", entry_Cr2O3);
		entry_Cr2O3->signal_activate().connect(sigc::ptr_fun(update));

		builder->get_widget("text_nSiO2", text_nSiO2);
		builder->get_widget("text_nTiO2", text_nTiO2);
		builder->get_widget("text_nAl2O3", text_nAl2O3);
		builder->get_widget("text_nFe2O3", text_nFe2O3);
		builder->get_widget("text_nFeO", text_nFeO);
		builder->get_widget("text_nMnO", text_nMnO);
		builder->get_widget("text_nMgO", text_nMgO);
		builder->get_widget("text_nCaO", text_nCaO);
		builder->get_widget("text_nNa2O", text_nNa2O);
		builder->get_widget("text_nK2O", text_nK2O);
		builder->get_widget("text_nP2O5", text_nP2O5);
		builder->get_widget("text_nS", text_nS);
		builder->get_widget("text_nCr2O3", text_nCr2O3);

		Gtk::Button *button;
		builder->get_widget("button_norm", button);
		button->signal_clicked().connect(sigc::ptr_fun(normalize));
		builder->get_widget("button_recalculate", button);
		button->signal_clicked().connect(sigc::ptr_fun(update));

		builder->get_widget("text_total", text_total);

		builder->get_widget("text_ibc_family", text_ibc_family);

		builder->get_widget("text_tas", text_tas);

		builder->get_widget("text_iugs", text_iugs);

		builder->get_widget("tree_view_CIPW", tree_view_CIPW);
		
		builder->get_widget("text_MgNo", text_MgNo);
		builder->get_widget("text_DI", text_DI);

		// Go for it
		kit.run(*main_win);
	}
	return 0;
}


