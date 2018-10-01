#ifndef PLOT1_HH
#define PLOT1_HH

#include "def.hh"

class Plot1 : public TObject {
	public:

  	//! Default Constructor
  	Plot1();

    //! Destructor
    virtual ~Plot1();

	public:
		static void drawStatsNumbers( const TH1* hist, TString pos="TR");
		static void draw1histoEBand( const TH1* hist  );
		static void draw1histo( const TH1* hist, TString goption="HISTO", TString pos="TR" );
		static void draw2histo( const TH2* hist, TString goption="colz" );
		static void drawprofile( const TProfile* hist, Int_t color = kRed-4 );
		static void drawgausfit( const TH1* hist, Double_t min, Double_t max );
		static void drawDgausfit( const TH1* hist, Double_t min, Double_t max );
		static void set_axis( TH1 *h, bool center_ytitle = false );
		static void set_axis( TH2 *h );
		static void set_axis( TProfile *h );
		static void set_axis( TGraph *gr );
		static void set_axis( THStack *gr );
		static void set_root_env();
		static void set_root_stats();
		static void set_gradient_color();
		static void add_histo_title( TString title, Double_t my_title_size = 0.05, Int_t my_title_font = 62 );
		static void add_plot_label( TString label, Double_t x, Double_t y, Double_t size = 0.05, Int_t color = 1, Int_t font = 62, Int_t align = 22, Double_t angle = 0, bool ndc = true );

    static TCanvas* getCanvas( TString name, TString title );
    static TCanvas* getCanvasSQ( TString name, TString title );

    static TLegend* getLegendTL( Int_t size = 1, Float_t text_zize = 0.044, Int_t text_font = 62 );
    static TLegend* getSQLegendTL( Int_t size = 1, Float_t text_zize = 0.044, Int_t text_font = 62 );
    static TLegend* getLegendTR( Int_t size = 1, Float_t text_size = 0.044, Int_t text_font = 62 );
    static TLegend* getSQLegendTR( Int_t size = 1, Float_t text_size = 0.044, Int_t text_font = 62 );
    static TLegend* getLegend2BL();
    static TLegend* getLegend2BR();
    static TLegend* getLegendTLDataMC();
    static TLegend* getLegendTC();
    static void draw1Stat(const TH1F *h1, Int_t Kolor);
    static void draw2Stat(const TH1F *h1, const TH1F *h2, Int_t Kolor1, Int_t Kolor2);

// Advanced
    static void draw_horizontal_line( Double_t x, Double_t ymin, Double_t ymax, bool ndc=true, TLine *line=NULL);
    static void draw_vertical_line( Double_t y, Double_t xmin, Double_t xmax, bool ndc=true, TLine *line=NULL );
    static void draw_arrow( Double_t x1, Double_t y1, Double_t x2, Double_t y2, Option_t *kind="|>", bool ndc=true, TLine *line=NULL );
    static void draw_cut_1L( Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax, bool ndc = true, TLine *line=NULL );
    static void draw_cut_1R( Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax, bool ndc = true, TLine *line=NULL );

		ClassDef(Plot1,1); //to define class like TObject, id=1 shoule change if I changed the members
};

#endif
