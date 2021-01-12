## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(pkgdatadir)/ui
ui_DATA = norm.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(NORM_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = norm

norm_SOURCES = \
	main.cc \
	calculate_molar_composition.cc \
        calculate_CIPW_norm.cc \
	calculate_differentiation_index.cc \
	TAS_classify.cc \
	IBC_classify.cc \
	subalkaline_classify.cc \
	on_new.cc \
	on_open.cc \
	update.cc \
	on_save.cc \
	do_save.cc \
	on_save_as.cc \
	normalize.cc \
	read_weight_composition.cc \
	populate_mole_composition_box.cc \
	populate_CIPW_norm_box.cc \
	clear_CIPW_norm_box.cc \
	clear_cation_norm_box.cc \
	populate_cation_norm_box.cc


norm_LDFLAGS = 

norm_LDADD = $(NORM_LIBS)




EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

