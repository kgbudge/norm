/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * gui.cc
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

#ifndef norm_gui_hh
#define norm_gui_hh

#include <gtkmm.h>

#ifdef NDEBUG
#define UI_FILE "src/norm.ui"
#else
#define UI_FILE PACKAGE_DATA_DIR"/ui/norm.ui"
#endif

#ifndef EXTERN
#define EXTERN extern
#endif

//-----------------------------------------------------------------------------//
class CIPW_Columns : public Gtk::TreeModelColumnRecord  // Also used for cation norm
{
public:

  CIPW_Columns()
    { add(m_col_text); add(m_col_number); }

  Gtk::TreeModelColumn<Glib::ustring> m_col_text;
  Gtk::TreeModelColumn<double> m_col_number;
};

//-----------------------------------------------------------------------------//
EXTERN Gtk::Window* main_win;

EXTERN Gtk::Entry *entry_name;

EXTERN Gtk::Entry *entry_SiO2;
EXTERN Gtk::Entry *entry_TiO2;
EXTERN Gtk::Entry *entry_Al2O3;
EXTERN Gtk::Entry *entry_Fe2O3;
EXTERN Gtk::Entry *entry_FeO;
EXTERN Gtk::Entry *entry_MnO;
EXTERN Gtk::Entry *entry_MgO;
EXTERN Gtk::Entry *entry_CaO;
EXTERN Gtk::Entry *entry_Na2O;
EXTERN Gtk::Entry *entry_K2O;
EXTERN Gtk::Entry *entry_P2O5;
EXTERN Gtk::Entry *entry_S;
EXTERN Gtk::Entry *entry_Cr2O3;

EXTERN Gtk::Label *text_nSiO2;
EXTERN Gtk::Label *text_nTiO2;
EXTERN Gtk::Label *text_nAl2O3;
EXTERN Gtk::Label *text_nFe2O3;
EXTERN Gtk::Label *text_nFeO;
EXTERN Gtk::Label *text_nMnO;
EXTERN Gtk::Label *text_nMgO;
EXTERN Gtk::Label *text_nCaO;
EXTERN Gtk::Label *text_nNa2O;
EXTERN Gtk::Label *text_nK2O;
EXTERN Gtk::Label *text_nP2O5;
EXTERN Gtk::Label *text_nS;
EXTERN Gtk::Label *text_nCr2O3;

EXTERN Gtk::Label *text_total;

EXTERN Gtk::Label *text_ibc_family;
EXTERN Gtk::Label *text_tas;
EXTERN Gtk::Label *text_iugs;

EXTERN Gtk::Label *text_MgNo;
EXTERN Gtk::Label *text_DI;

EXTERN Gtk::TreeView *tree_view_CIPW;
EXTERN Gtk::TreeView *tree_view_cation;

//! Name of the sample file
EXTERN std::string file;
//! Name of the sample
EXTERN std::string name;

//-----------------------------------------------------------------------------//
void on_new();
void on_open();
void on_save();
void on_save_as();

void clear_cation_norm_box();
void clear_CIPW_norm_box();
void do_save();
void normalize();
void populate_cation_norm_box();
void populate_CIPW_norm_box();
void populate_mole_composition_box();
void read_weight_composition();
void update();

#endif

