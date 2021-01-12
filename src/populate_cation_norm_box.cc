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
void populate_cation_norm_box()
{
	using namespace std;
	
	CIPW_Columns m_Columns;
	Glib::RefPtr<Gtk::ListStore> list_store_cation = Gtk::ListStore::create(m_Columns);
	list_store_cation->set_sort_column(1, Gtk::SORT_DESCENDING);

	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;


	string sMgFe = tostring(wMgFe, 2);

	if (ap>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "apatite";
		row[m_Columns.m_col_number] = ap;
	}

	if (il>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "ilmenite";
		row[m_Columns.m_col_number] = il;
	}

	if (orc>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "orthoclase";
		row[m_Columns.m_col_number] = orc;
	}

	if (ab>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "albite";
		row[m_Columns.m_col_number] = ab;
	}

	if (an>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "anorthite";
		row[m_Columns.m_col_number] = an;
	}

	if (C>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "corundum";
		row[m_Columns.m_col_number] = C;
	}

	if (ac>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "acmite";
		row[m_Columns.m_col_number] = ac;
	}

	if (ns>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "sodium metasilicate";
		row[m_Columns.m_col_number] = ns;
	}

	if (mt>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "magnetite";
		row[m_Columns.m_col_number] = mt;
	}

	if (hm>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "hematite";
		row[m_Columns.m_col_number] = hm;
	}

	if (di>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "augite ("+sMgFe+')';
		row[m_Columns.m_col_number] = di;
	}

	if (wo>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "wollastonite";
		row[m_Columns.m_col_number] = wo;
	}

	if (hy>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "hypersthene ("+sMgFe+')';
		row[m_Columns.m_col_number] = hy;
	}

	if (Q>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "quartz";
		row[m_Columns.m_col_number] = Q;
	}

	if (ol>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "olivine ("+sMgFe+')';
		row[m_Columns.m_col_number] = ol;
	}

	if (tn>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "sphene";
		row[m_Columns.m_col_number] = tn;
	}

	if (ru>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "rutile";
		row[m_Columns.m_col_number] = ru;
	}

	if (pf>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "perovskite";
		row[m_Columns.m_col_number] = pf;
	}

	if (ne>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "nepheline";
		row[m_Columns.m_col_number] = ne;
	}

	if (lc>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "leucite";
		row[m_Columns.m_col_number] = lc;
	}

	if (cs>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "calcium orthosilicate";
		row[m_Columns.m_col_number] = cs;
	}

	if (pr>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "pyrite";
		row[m_Columns.m_col_number] = pr;
	}

	if (cm>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "chromite";
		row[m_Columns.m_col_number] = cm;
	}

	if (kp>0.0)
	{
		iter = list_store_cation->append();
		row = *iter;
		row[m_Columns.m_col_text] = "kaliophilite";
		row[m_Columns.m_col_number] = kp;
	}

	tree_view_cation->remove_all_columns();
	tree_view_cation->set_model(list_store_cation);
	tree_view_cation->append_column("Mineral", m_Columns.m_col_text);
	tree_view_cation->append_column("cation %", m_Columns.m_col_number);
}
