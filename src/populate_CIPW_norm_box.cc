/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * populate_CIPW_norm_box.cc
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
void populate_CIPW_norm_box()
{
	using namespace std;
	
	CIPW_Columns m_Columns;
	Glib::RefPtr<Gtk::ListStore> list_store_CIPW = Gtk::ListStore::create(m_Columns);
	list_store_CIPW->set_sort_column(1, Gtk::SORT_DESCENDING);

	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;


	string sMgFe = tostring(wMgFe, 2);

	if (ap>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "apatite";
		row[m_Columns.m_col_number] = wap;
	}

	if (il>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "ilmenite";
		row[m_Columns.m_col_number] = wil;
	}

	if (orc>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "orthoclase";
		row[m_Columns.m_col_number] = worc;
	}

	if (ab>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "albite";
		row[m_Columns.m_col_number] = wab;
	}

	if (an>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "anorthite";
		row[m_Columns.m_col_number] = wan;
	}

	if (C>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "corundum";
		row[m_Columns.m_col_number] = wC;
	}

	if (ac>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "acmite";
		row[m_Columns.m_col_number] = wac;
	}

	if (ns>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "sodium metasilicate";
		row[m_Columns.m_col_number] = wns;
	}

	if (mt>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "magnetite";
		row[m_Columns.m_col_number] = wmt;
	}

	if (hm>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "hematite";
		row[m_Columns.m_col_number] = whm;
	}

	if (di>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "augite ("+sMgFe+')';
		row[m_Columns.m_col_number] = wdi;
	}

	if (wo>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "wollastonite";
		row[m_Columns.m_col_number] = wwo;
	}

	if (hy>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "hypersthene ("+sMgFe+')';
		row[m_Columns.m_col_number] = why;
	}

	if (Q>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "quartz";
		row[m_Columns.m_col_number] = wQ;
	}

	if (ol>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "olivine ("+sMgFe+')';
		row[m_Columns.m_col_number] = wol;
	}

	if (tn>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "sphene";
		row[m_Columns.m_col_number] = wtn;
	}

	if (ru>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "rutile";
		row[m_Columns.m_col_number] = wru;
	}

	if (pf>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "perovskite";
		row[m_Columns.m_col_number] = wpf;
	}

	if (ne>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "nepheline";
		row[m_Columns.m_col_number] = wne;
	}

	if (lc>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "leucite";
		row[m_Columns.m_col_number] = wlc;
	}

	if (cs>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "calcium orthosilicate";
		row[m_Columns.m_col_number] = wcs;
	}

	if (pr>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "pyrite";
		row[m_Columns.m_col_number] = wpr;
	}

	if (cm>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "chromite";
		row[m_Columns.m_col_number] = wcm;
	}

	if (kp>0.0)
	{
		iter = list_store_CIPW->append();
		row = *iter;
		row[m_Columns.m_col_text] = "kaliophilite";
		row[m_Columns.m_col_number] = wkp;
	}

	tree_view_CIPW->remove_all_columns();
	tree_view_CIPW->set_model(list_store_CIPW);
	tree_view_CIPW->append_column("Mineral", m_Columns.m_col_text);
	tree_view_CIPW->append_column("Wt %", m_Columns.m_col_number);
}
