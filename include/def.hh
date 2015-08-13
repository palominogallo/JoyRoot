#ifndef def_h
#define def_h

#include "ROOTinclude.hh"

namespace def{

//-- marker settings
const Int_t data_marker = 20;
const Int_t reco_marker = 21;
const Int_t ratio_marker = 20;
const Double_t data_marker_size = 1.0;
const Double_t reco_marker_size = 1.0;
const Double_t ratio_marker_size = 1.0;

//-- line settings
const Int_t data_line_width 	= 1;
const Int_t reco_line_width 	= 2;
const Int_t mc_line_width 		= 3;
const Int_t ratio_line_width 	= 1;
const Double_t Xlegend 			  = 0.5;
const Double_t Ylegend    		= 0.7;


//-- color settings
const Int_t data_color = 1;
const Int_t reco_color = kRed-7;
const Int_t mc_error_style = 3001;
const Int_t mc_color = 2;
const Int_t mc_error_color = 45;
const Int_t ratio_color = 1;

//-- font settings
const Int_t title_font = 62;
const Int_t axis_title_font_x = 22; //bold
const Int_t axis_title_font_y = 22; //bold
const Int_t axis_title_font_z = 32; // italic
const Int_t axis_label_font = 42;
const Int_t axis_label_font_z = 132;
const Double_t title_size = 0.05;
const Double_t axis_title_size_x = 0.06;
const Double_t axis_title_size_y = 0.06;
const Double_t axis_title_size_z = 0.04;
const Double_t axis_label_size = 0.045;
const Double_t axis_label_size_z = 0.035;

//-- Background
const Int_t mc_bg_color = 14;
const Int_t mc_bg_width = 1;
const Int_t mc_bg_line_color = 1;
const Int_t mc_bg_style = 3005;

const Int_t data_bg_color = 12; //gray
const Int_t data_bg_style = 24; //circle

//-- legend
const Double_t height_nspaces_per_hist = 2.;
const Double_t width_xspace_per_letter = .5;
const Double_t legend_text_size        = .035;

//-- layout
const Double_t headroom = 1.3;
const Double_t headroom_error = 2;

//-- Fill out style
const Int_t fillStyle = 3001;

}

#endif
