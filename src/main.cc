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

#include <iostream>

#define EXTERN
#include "composition.hh"
#include "gui.hh"

//-----------------------------------------------------------------------------//
void on_quit()
{
	main_win->hide();
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
		builder->get_widget("tree_view_cation", tree_view_cation);
		
		builder->get_widget("text_MgNo", text_MgNo);
		builder->get_widget("text_DI", text_DI);

		// Go for it
		kit.run(*main_win);
	}
	return 0;
}


