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

#define EXTERN
#include "composition.hh"
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

	wtotal = SiO2 + TiO2 + Al2O3 + Fe2O3 + FeO + MnO + MgO + CaO + Na2O + K2O + P2O5 + S + Cr2O3;
	text_total->set_text(tostring(wtotal));

	calculate_molar_composition();
	if (ntotal==0.0) return;

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

	// Magnesium number

	text_MgNo->set_text(tostring((int)(1000*nMgO/(nMgO+nFeO)+0.5)/10.));

	// Determine the CIPW norm

	CIPW_Columns m_Columns;
	Glib::RefPtr<Gtk::ListStore> list_store_CIPW = Gtk::ListStore::create(m_Columns);
	list_store_CIPW->set_sort_column(1, Gtk::SORT_DESCENDING);

	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;

	try
	{
		calculate_CIPW_norm();
		
		text_DI->set_text(tostring(calculate_differentiation_index(), 2));
		
		string sMgFe = tostring(wMgFe, 2);

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

		if (C>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "corundum";
			row[m_Columns.m_col_number] = C;
		}

		if (ac>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "acmite";
			row[m_Columns.m_col_number] = ac;
		}

		if (ns>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "sodium metasilicate";
			row[m_Columns.m_col_number] = ns;
		}

		if (mt>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "magnetite";
			row[m_Columns.m_col_number] = mt;
		}

		if (hm>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "hematite";
			row[m_Columns.m_col_number] = hm;
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

		if (Q>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "quartz";
			row[m_Columns.m_col_number] = Q;
		}

		if (ol>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "olivine ("+sMgFe+')';
			row[m_Columns.m_col_number] = ol;
		}

		if (tn>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "sphene";
			row[m_Columns.m_col_number] = tn;
		}

		if (ru>0.0)
		{
			iter = list_store_CIPW->append();
			row = *iter;
			row[m_Columns.m_col_text] = "rutile";
			row[m_Columns.m_col_number] = ru;
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

		text_tas->set_text(TAS_classify());

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
		tn /=3.48;
		nTiO2 /=4.23;
		pf /=3.98;
		ne /=2.59;
		nK2O /=2.61; // lacking density of potassium silicate, we assume same molar volume as sodium metasilicate
		lc /=2.50;
		cs /=2.9;
		pr /=5.0;
		cm /=4.8;
		kp /=2.59;

		double total = ap + il + orc + ab + an + nAl2O3 + ac + nNa2O + mt + nFe2O3 + di
			+ nCaO + hy + nSiO2 + ol + tn + nTiO2 + pf
			+ ne + nK2O + lc + cs + pr + cm + kp;

		double rnorm = 100.0/total;

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
		tn *= rnorm;
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

		double M = ol + ac + di + hy + mt + cm + nFe2O3 + il + tn + pf + nTiO2
			+ pr + ap + nAl2O3;

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
	catch (bad_CIPW const &err)
	{
		Gtk::MessageDialog dialog(*main_win, "CIPW Norm Fail");
		dialog.set_secondary_text(err.what());
		dialog.run();

		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "<undetermined>";
		row[m_Columns.m_col_number] = 100;
		text_iugs->set_text("<undetermined>");	
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


