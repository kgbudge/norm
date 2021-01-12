/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * composition.hh
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

#ifndef norm_composition_hh
#define norm_composition_hh

#include <stdexcept>
#include <string>

#ifndef EXTERN
#define EXTERN extern
#endif

//! Weight composition of the sample being analyzed. Not necessarily normalized.
EXTERN double SiO2;
EXTERN double TiO2;
EXTERN double Al2O3;
EXTERN double Fe2O3;
EXTERN double FeO;
EXTERN double MnO;
EXTERN double MgO;
EXTERN double CaO;
EXTERN double Na2O;
EXTERN double K2O;
EXTERN double P2O5;
EXTERN double S;
EXTERN double Cr2O3;

//! Total weight, for normalization
EXTERN double wtotal;


//! Molar composition of the sample being analyzed. These are always normalized.
EXTERN double nSiO2;
EXTERN double nTiO2;
EXTERN double nAl2O3;
EXTERN double nFe2O3;
EXTERN double nFeO;
EXTERN double nMnO;
EXTERN double nMgO;
EXTERN double nCaO;
EXTERN double nNa2O;
EXTERN double nK2O;
EXTERN double nP2O5;
EXTERN double nS;
EXTERN double nCr2O3;

//! Molar normalization
EXTERN double ntotal;

// CIPW norm; molar percentage normalized
EXTERN double Q;
EXTERN double C;
EXTERN double Z;
EXTERN double orc;  // normally written or; this is a problem ...
EXTERN double ab;
EXTERN double an;
EXTERN double lc;
EXTERN double ne;
EXTERN double kp;
EXTERN double ac;
EXTERN double ns;
EXTERN double wo;
EXTERN double di; // == en + fs as solid solution
EXTERN double hy;
EXTERN double ol; // == fo + fa as solid solution
EXTERN double cs;
EXTERN double mt;
EXTERN double cm;
EXTERN double hm;
EXTERN double il;
EXTERN double tn;
EXTERN double pf;
EXTERN double ru;
EXTERN double ap;
EXTERN double fr;
EXTERN double pr;
EXTERN double cc;

EXTERN double rMgFe; // molar percentage of magnesium in ferromagnesian minerals (diopside, olivine)
EXTERN double wMgFe; // weight percentage of magnesium in ferromagnesian minerals

// CIPW norm; weight percentage normalized
EXTERN double wQ;
EXTERN double wC;
EXTERN double wZ;
EXTERN double worc;  // normally written or; this is a problem ...
EXTERN double wab;
EXTERN double wan;
EXTERN double wlc;
EXTERN double wne;
EXTERN double wkp;
EXTERN double wac;
EXTERN double wns;
EXTERN double wwo;
EXTERN double wdi; // == en + fs as solid solution
EXTERN double why;
EXTERN double wol; // == fo + fa as solid solution
EXTERN double wcs;
EXTERN double wmt;
EXTERN double wcm;
EXTERN double whm;
EXTERN double wil;
EXTERN double wtn;
EXTERN double wpf;
EXTERN double wru;
EXTERN double wap;
EXTERN double wfr;
EXTERN double wpr;
EXTERN double wcc;

double calculate_differentiation_index();
void calculate_molar_composition();
void calculate_CIPW_norm();

std::string IBC_classify();
std::string TAS_classify();
std::string subalkaline_classify();
std::string subalkaline_K_classify();

class bad_CIPW : public std::domain_error
{
  public:
    bad_CIPW(std::string const &msg) : std::domain_error(msg) {}
};

#endif
