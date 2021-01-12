/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * clear_CIPW_norm_box.cc
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
void clear_cation_norm_box()
{
	CIPW_Columns m_Columns;
	Glib::RefPtr<Gtk::ListStore> list_store_cation = Gtk::ListStore::create(m_Columns);
	list_store_cation->set_sort_column(1, Gtk::SORT_DESCENDING);

	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;

	iter = list_store_cation->append();
	row = *iter;
	row[m_Columns.m_col_text] = "<undetermined>";
	row[m_Columns.m_col_number] = 100;
	text_iugs->set_text("<undetermined>");	

	tree_view_cation->remove_all_columns();
	tree_view_cation->set_model(list_store_cation);
	tree_view_cation->append_column("Mineral", m_Columns.m_col_text);
	tree_view_cation->append_column("Wt %", m_Columns.m_col_number);
}
