#ifndef PLOT1_HH
#define PLOT1_HH

#include "def.hh"

class Plot1 {
	public:

  	//! Default Constructor
  	Plot1();

    //! Destructor
    virtual ~Plot1();

	public:
		static void draw1histo( const TH1* hist, TString goption="HISTO", TString pos="TR" );
		static void draw2histo( const TH2* hist, TString goption="colz" );
		static void drawprofile( const TProfile* hist, Int_t color = kRed-4 );
		static void drawgausfit( const TH1* hist, Double_t min, Double_t max );
		static void drawDgausfit( const TH1* hist, Double_t min, Double_t max );
		static void set_axis( TH1 *h );
		static void set_axis( TH2 *h );
		static void set_axis( TProfile *h );
		static void set_axis( TGraph *gr );
		static void set_axis( THStack *gr );
		static void set_root_env();
		static void set_root_stats();
		static void set_gradient_color();
		static void decode_position( std::string opts, Double_t size, Int_t &align, Double_t &x_label, Double_t &y_label );
		static void decode_legend_position( Double_t &x1, Double_t &y1, Double_t &x2, Double_t &y2, std::string opts, Int_t nHists,
    		 												const Int_t longestTitleSize , Double_t size );
		static void add_histo_title( TString title, Double_t my_title_size = 0.05, Int_t my_title_font = 62 );
		static void add_plot_label( TString label, Double_t x, Double_t y, Double_t size = 0.05, Int_t color = 1, Int_t font = 62, Int_t align = 22, Double_t angle = 0 );

    static TCanvas* getCanvas( TString name, TString title );
    static TCanvas* getCanvasSQ( TString name, TString title );

    static TLegend* getLegend1TL( Float_t text_zize = 0.044 );
    static TLegend* getLegend2TL( Float_t text_size = 0.044 );
    static TLegend* getLegend3TL( Float_t text_size = 0.044 );
    static TLegend* getLegend1TR( Float_t text_size = 0.044 );
    static TLegend* getLegend2TR( Float_t text_size = 0.044 );
    static TLegend* getLegend3TR( Float_t text_size = 0.044 );
    static TLegend* getLegend2BL();
    static TLegend* getLegend2BR();
    static TLegend* getLegendTC();
    static TLegend* getLegendTLDataMC();


// Advanced
    static void draw_line( Double_t xmin, Double_t xmax, Double_t ymin, Double_t ymax, Int_t color=0 );
    static void draw_horizontal_line( Double_t x, Double_t ymin, Double_t ymax, Int_t color=0 );
    static void draw_vertical_line( Double_t y, Double_t xmin, Double_t xmax, Int_t color=0 );
    static void draw_arrow( Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t color=0, Float_t size=.04, Option_t *kind="|>" );
    static void draw_cut_1L( Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax, Int_t color=0, Float_t size=.04 );
    static void draw_cut_1R( Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax, Int_t color=0, Float_t size=.04 );

};

#endif


