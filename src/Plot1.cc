#ifndef PLOT1_CXX
#define PLOT1_CXX 1

#include "Plot1.hh"

ClassImp(Plot1)

Plot1::Plot1(){
};

Plot1::~Plot1(){
};

//==========================================================
// draw common options histo
//==========================================================
void Plot1::draw1histo( const TH1* hist, TString goption, TString pos )
{
	TH1* htemp = (TH1*)hist->Clone(hist->GetName());
	htemp->SetLineColor(kGray +3);
	htemp->SetLineWidth(2);
	htemp->SetFillColor(kAzure-8);
  set_axis(htemp);
	htemp->DrawCopy(goption);	
  add_histo_title( Form("%s", htemp->GetTitle() ) );

	if ( pos != "NO" )
	{
  	float x0 = .67, y0 = .75;
  	if ( pos == "TR" ) x0 = .67;
  	else if ( pos == "TL" ) x0 = .1;
  	add_plot_label( Form( "Mean = %.2f", htemp->GetMean() ), x0 , y0+.1, .04, kGray+3, 42, 12 );
 	 	add_plot_label( Form( "RMS = %.2f", htemp->GetRMS() ), x0 , y0+.05, .04, kGray+3, 42, 12 );
  	add_plot_label( Form( "Entries = %.0f", htemp->GetEntries() ), x0 , y0, .04, kGray+3, 42, 12);
	}

	gPad->Update();
	delete htemp;
}

//==========================================================
// draw common options histo
//==========================================================
void Plot1::draw2histo( const TH2* hist, TString goption){

	TH2* tmp = (TH2*)hist->Clone("tmp");
	tmp->SetLineWidth(2);
 	set_axis(tmp);
	tmp->DrawCopy(goption);	
	gPad->Update();
	
	delete tmp;

}

//==========================================================
// draw profile
//==========================================================
void Plot1::drawprofile( const TProfile* hist, Int_t color){

	TProfile* tmp = (TProfile*)hist->Clone("tmp");
	tmp->SetMarkerColor(color);
	tmp->SetLineWidth(2);
	tmp->SetLineColor(color);
	tmp->SetTitleFont(22); //- titles font
	tmp->GetXaxis()->CenterTitle(kTRUE);
	tmp->GetXaxis()->SetTitleSize(0.05); //- size axis title
	tmp->GetYaxis()->CenterTitle(kTRUE);
	tmp->GetYaxis()->SetTitleSize(0.05); //- size axis title
	tmp->DrawCopy();	

	gPad->Update();
	
	delete tmp;

}
/*void Plot1::drawpoissonfit( const TH1* hist, Double_t min, Double_t max){

  TF1 *pois = new TF1( "pois", "poissonf", min, max );
  pois->SetLineWidth(3); 
  pois->SetLineColor(kRed);
	pois->SetParName(0, "Constant A");
  pois->SetParName(1, "Mean     A");
}
*/
//==========================================================
// draw gaus fit
//==========================================================
void Plot1::drawgausfit( const TH1* hist, Double_t min, Double_t max  ){

	TF1 *g1    = new TF1("g1","gaus",min,max); g1->SetLineWidth(3); g1->SetLineColor(kRed);
	g1->SetParName(0, "Constant A");
  g1->SetParName(1, "Mean     A");
  g1->SetParName(2, "Sigma    A");

	
	TH1F *tfit = (TH1F*)hist->Clone("tfit");
	tfit->Fit(g1,"RQ");


	tfit->SetLineColor(kBlack);
	set_axis(tfit);
	tfit->DrawCopy();

  add_plot_label( Form( "Mean = %.3f", tfit->GetMean() ), 				0.66, 0.84, 0.038, kBlack, 42, 12 );
  add_plot_label( Form( "RMS = %.3f", tfit->GetRMS() ),           0.66, 0.80, 0.038, kBlack, 42, 12 );
  add_plot_label( Form( "Entries = %.0f", tfit->GetEntries() ),   0.66, 0.76, 0.038, kBlack, 42, 12 );
  add_plot_label( Form( "#mu = %.3f", g1->GetParameter( 1 ) ), 		0.66, 0.72, 0.038, kRed, 42, 12 );
  add_plot_label( Form( "#sigma = %.3f", g1->GetParameter( 2 ) ), 0.66, 0.68, 0.038, kRed, 42, 12 );
  add_plot_label( Form( "#chi^{2} = %.1f", g1->GetChisquare( ) ), 0.66, 0.64, 0.038, kRed, 42, 12 );
  add_plot_label( Form( "NDF = %i",   g1->GetNDF() ),          		0.66, 0.60, 0.038, kRed, 42, 12 );
	gPad->Update();

	delete tfit;

}

//==========================================================
// draw Double_t gaus fit
//==========================================================
void Plot1::drawDgausfit( const TH1* hist, Double_t min, Double_t max )
{

	TF1 *g    = new TF1("g","gaus",min,max);
	TF1 *g1    = new TF1("g1","gaus",min,max); g1->SetLineStyle(2); g1->SetLineWidth(3); g1->SetLineColor(kRed);
  TF1 *g2    = new TF1("g2","gaus",min,max); g2->SetLineStyle(8); g2->SetLineWidth(3); g2->SetLineColor(kBlue);
	TF1 *dgaus = new TF1("dgaus","gaus(0) + gaus(3)",min,max); dgaus->SetLineWidth(3); dgaus->SetLineColor(kBlack);

	Double_t par[3], parD[6];
	
	TH1F *hfit = (TH1F*)hist->Clone("tfit");
	hfit->Fit(g,"QR","goff");
	g->GetParameters(&par[0]);
	
	dgaus->SetParameter(0,par[0]);
	dgaus->SetParameter(1,par[1]);
	dgaus->SetParameter(2,par[2]);
	dgaus->SetParameter(3,par[0]/10);
	dgaus->SetParameter(4,par[1]);
	dgaus->SetParameter(5,par[2]*2);

	hfit->Fit(dgaus,"QR");
	dgaus->GetParameters(&parD[0]);

	hfit->SetLineColor(kBlack);
	set_axis(hfit);
	hfit->DrawCopy();

	g1->SetParameters(parD[0],parD[1],parD[2]);
  g2->SetParameters(parD[3],parD[4],parD[5]);
  g1->DrawCopy("SAME");
  g2->DrawCopy("SAME");

  gStyle->SetOptStat(000);
  gStyle->SetOptFit(000);
  Double_t x_legend = .65, y_legend = .74;
  TLegend *leg = new TLegend(x_legend,y_legend,x_legend+0.25,y_legend+0.15);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(g1,Form("Gaussian A"), "L");
  leg->AddEntry(g2,Form("Gaussian B"), "L");
  leg->Draw("same");

  add_plot_label( Form( "A: #mu = %.3f", dgaus->GetParameter( 1 ) ), 0.65, 0.70, 0.04, kRed, 42, 12 );
  add_plot_label( Form( "A: #sigma = %.3f", dgaus->GetParameter( 2 ) ), 0.65, 0.65, 0.04, kRed, 42, 12 );
  add_plot_label( Form( "B: #mu = %.3f", dgaus->GetParameter( 4 ) ), 0.65, 0.60, 0.04, kBlue,  42, 12 );
  add_plot_label( Form( "B: #sigma = %.3f", dgaus->GetParameter( 5 ) ), 0.65, 0.55, 0.04, kBlue,  42, 12 );
  add_plot_label( Form( "#chi^{2} = %.1f", dgaus->GetChisquare( ) ),   0.65, 0.50, 0.04, kBlack,42, 12 );
  add_plot_label( Form( "NDF = %i",   dgaus->GetNDF() ),          0.65, 0.45, 0.04, kBlack,42, 12 );
  add_plot_label( Form( "RMS = %.3f", hfit->GetRMS() ),               0.65, 0.40, 0.04, kBlack,42, 12 );

	gPad->Update();

	delete hfit;
}

// ====================================================================
// set_axis
// ====================================================================
void Plot1::set_axis( TH1 *h, bool center_ytitle )
{
		h->GetXaxis()->SetTitleFont(def::axis_title_font_x);
		h->GetYaxis()->SetTitleFont(def::axis_title_font_y);
		h->GetXaxis()->SetTitleSize(def::axis_title_size_x);
		h->GetYaxis()->SetTitleSize(def::axis_title_size_y);
		h->GetXaxis()->SetLabelFont(def::axis_label_font);
		h->GetYaxis()->SetLabelFont(def::axis_label_font);
		h->GetXaxis()->SetLabelSize(def::axis_label_size);
		h->GetYaxis()->SetLabelSize(def::axis_label_size);
		h->GetXaxis()->CenterTitle(true);
		if(center_ytitle) h->GetYaxis()->CenterTitle(true);
}	

void Plot1::set_axis( TH2 *h )
{
	h->GetXaxis()->SetTitleFont(def::axis_title_font_x);
	h->GetYaxis()->SetTitleFont(def::axis_title_font_y);
	h->GetZaxis()->SetTitleFont(def::axis_title_font_z);
	h->GetXaxis()->SetTitleSize(def::axis_title_size_x);
	h->GetYaxis()->SetTitleSize(def::axis_title_size_y);
	h->GetZaxis()->SetTitleSize(def::axis_title_size_z);

	h->GetXaxis()->SetLabelFont(def::axis_label_font);
	h->GetYaxis()->SetLabelFont(def::axis_label_font);
	h->GetZaxis()->SetLabelFont(def::axis_label_font_z);
	h->GetXaxis()->SetLabelSize(def::axis_label_size);
	h->GetYaxis()->SetLabelSize(def::axis_label_size);
	h->GetZaxis()->SetLabelSize(def::axis_label_size_z);
	h->GetXaxis()->CenterTitle(true);
	h->GetYaxis()->CenterTitle(true);
}

void Plot1::set_axis( TProfile *h )
{
  h->GetXaxis()->SetTitleFont(def::axis_title_font_x);
  h->GetYaxis()->SetTitleFont(def::axis_title_font_y);
  h->GetXaxis()->SetTitleSize(def::axis_title_size_x);
  h->GetYaxis()->SetTitleSize(def::axis_title_size_y);
  h->GetXaxis()->SetLabelFont(def::axis_label_font);
  h->GetYaxis()->SetLabelFont(def::axis_label_font);
  h->GetXaxis()->SetLabelSize(def::axis_label_size);
  h->GetYaxis()->SetLabelSize(def::axis_label_size);
  h->GetXaxis()->CenterTitle(true);
  h->GetYaxis()->CenterTitle(true);
}

void Plot1::set_axis( TGraph *gr )
{
	gr->GetXaxis()->SetTitleFont(def::axis_title_font_x);
	gr->GetYaxis()->SetTitleFont(def::axis_title_font_y);
	gr->GetXaxis()->SetTitleSize(def::axis_title_size_x);
	gr->GetYaxis()->SetTitleSize(def::axis_title_size_y);
	gr->GetXaxis()->SetLabelFont(def::axis_label_font);
	gr->GetYaxis()->SetLabelFont(def::axis_label_font);
	gr->GetXaxis()->SetLabelSize(def::axis_label_size);
	gr->GetYaxis()->SetLabelSize(def::axis_label_size);
	gr->GetXaxis()->CenterTitle(true);
	gr->GetYaxis()->CenterTitle(true);
}

void Plot1::set_axis( THStack *h )
{
	h->GetXaxis()->SetTitleFont(def::axis_title_font_x);
	h->GetYaxis()->SetTitleFont(def::axis_title_font_y);
	h->GetXaxis()->SetTitleSize(def::axis_title_size_x);
	h->GetYaxis()->SetTitleSize(def::axis_title_size_y);
	h->GetXaxis()->SetLabelFont(def::axis_label_font);
	h->GetYaxis()->SetLabelFont(def::axis_label_font);
	h->GetXaxis()->SetLabelSize(def::axis_label_size);
	h->GetYaxis()->SetLabelSize(def::axis_label_size);
	h->GetXaxis()->CenterTitle(true);
	h->GetYaxis()->CenterTitle(true);
}

// ====================================================================
// draw_cut_XX
// ====================================================================
void Plot1::draw_horizontal_line( Double_t y, Double_t xmin, Double_t xmax, bool ndc, TLine *ln )
{
  TLine *line = new TLine( xmin, y, xmax, y );
	if ( ndc ) line->SetNDC();
  if ( ln ) 
	{
		line->SetLineColor( ln->GetLineColor() );
  	line->SetLineWidth( ln->GetLineWidth() );
		line->SetLineStyle( ln->GetLineStyle() );
	}
	else
	{
  	line->SetLineColor(kRed);
  	line->SetLineWidth(2);
		line->SetLineStyle(1);
	}
  line->Draw("SAME");
  gPad->Update();
}

void Plot1::draw_vertical_line( Double_t x, Double_t ymin, Double_t ymax, bool ndc, TLine *ln )
{
  TLine *line = new TLine( x, ymin, x, ymax );
	if ( ndc ) line->SetNDC();
	if ( ln )
	{
  	line->SetLineColor( ln->GetLineColor() );
  	line->SetLineWidth( ln->GetLineWidth() );
		line->SetLineStyle( ln->GetLineStyle() );
	}
	else	
	{
  	line->SetLineColor(kRed);
  	line->SetLineWidth(2);
  	line->SetLineStyle(1);
	}
  line->Draw("SAME");
  gPad->Update();
}

void Plot1::draw_arrow( Double_t x1, Double_t y1, Double_t x2, Double_t y2, Option_t *kind, bool ndc, TLine *ln )
{
  TArrow *arrow = new TArrow( x1, y1, x2, y2, 0.04, kind );
	if ( ndc) arrow->SetNDC();
  arrow->SetAngle(30);
	if ( ln )
	{
  	arrow->SetLineColor( ln->GetLineColor() );
  	arrow->SetFillColor( ln->GetLineColor() );
  	arrow->SetLineWidth( ln->GetLineWidth() );
		arrow->SetLineStyle( ln->GetLineStyle() );
	}	
	else
	{
  	arrow->SetLineColor(kRed);
  	arrow->SetFillColor(kRed);
  	arrow->SetLineWidth(2);
  	arrow->SetLineStyle(1);
	}	
  arrow->Draw();
  gPad->Update();
}

void Plot1::draw_cut_1L( Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax, bool ndc, TLine *line)
{
  draw_vertical_line( xmax, ymin, ymax, ndc, line );
  draw_arrow( xmin, ymax, xmax, ymax, "<", ndc, line );
  gPad->Update();
}

void Plot1::draw_cut_1R( Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax, bool ndc, TLine *line )
{
  draw_vertical_line( xmin, ymin, ymax, ndc, line );
  draw_arrow( xmin, ymax, xmax, ymax, ">", ndc, line );
  gPad->Update();
}


// ====================================================================
// set_root_env
// ====================================================================
void Plot1::set_root_env()
{
	//gStyle->SetOptStat("nmre");
	gStyle->SetOptStat(000);
	gStyle->SetStatX(.99);
	gStyle->SetStatY(.9);
	gStyle->SetOptFit(0);
	gStyle->SetOptTitle(0);

  // Borders
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);

  // Color Scheme - Black & White
  gStyle->SetCanvasColor(0);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);

	gStyle->SetFrameLineWidth(2);

	gStyle->SetPadTopMargin(0.10);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.10);

	gStyle->SetPadTickY(1);
	gStyle->SetPadTickX(1);
	gStyle->SetTitleFontSize(0.07);
	gStyle->SetTitleFont(22);
	gStyle->SetTitleBorderSize(2);

	TGaxis::SetMaxDigits(4);
}

// ====================================================================
// set_root_stats
// ====================================================================
void Plot1::set_root_stats()
{
  gStyle->SetOptStat("mre");
  //gStyle->SetStatBorderSize(0);
  gStyle->SetStatStyle(0);
  gStyle->SetStatFont(42);
	gStyle->SetStatX(.99);
	gStyle->SetStatY(.9);
	gStyle->SetStatFontSize(.08);
	gStyle->SetOptFit(0);
	gStyle->SetOptTitle(0);

  // Borders
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);

  // Color Scheme - Black & White
  gStyle->SetCanvasColor(0);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);

	gStyle->SetFrameLineWidth(2);

	gStyle->SetPadTopMargin(0.10);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.10);

	gStyle->SetPadTickY(1);
	gStyle->SetPadTickX(1);
	gStyle->SetTitleFontSize(0.07);
	gStyle->SetTitleFont(22);
	gStyle->SetTitleBorderSize(2);

	TGaxis::SetMaxDigits(4);

}

// ====================================================================
// set_gradient_color
// ====================================================================
void Plot1::set_gradient_color()
{
	const Int_t NRGBs = 6;
	const Int_t NCont = 150;
	Double_t stops[NRGBs] = { 0.00, 0.03, 0.12, 0.35, 0.70, 1.00 };
	Double_t red[NRGBs]   = { 0.95, 0.70, 0.87, 0.90, 1.00, 0.20 };
	Double_t green[NRGBs] = { 0.95, 0.70, 0.80, 0.50, 0.00, 0.10 };
	Double_t blue[NRGBs]  = { 0.95, 0.70, 0.12, 0.00, 0.00, 0.50 };
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
}
// =================================================
// =================================================
// =================================================
// ====================================================================
// add_plot_label
// ====================================================================
void Plot1::add_plot_label( TString label, Double_t x, Double_t y, Double_t size, Int_t color, Int_t font, Int_t align, Double_t angle, bool ndc)
{
	TLatex *latex = new TLatex( x, y, label );
	if (ndc) latex->SetNDC();
	latex->SetTextSize(size);
	latex->SetTextColor(color);
	latex->SetTextFont(font);
	latex->SetTextAlign(align);
	latex->SetTextAngle(angle);
	latex->Draw();
}

//==========================================================
// add_histo_title
//==========================================================
void Plot1::add_histo_title( TString title, Double_t my_title_size, Int_t my_title_font ){

  add_plot_label(title, 0.5, 1-gStyle->GetPadTopMargin()+0.02, my_title_size, 1, my_title_font, 21);

}

//==========================================================
// Normal Canvas
//==========================================================
TCanvas* Plot1::getCanvas(TString name, TString title)
{
  TCanvas *canvas = new TCanvas(name, title, 600, 500 );
  return canvas;
}
//==========================================================
// Square Canvas
//==========================================================
TCanvas* Plot1::getCanvasSQ(TString name, TString title)
{
  TCanvas *canvas = new TCanvas(name, title, 600, 600);
  return canvas;
}

//==========================================================
// Legend Top Right
//==========================================================
TLegend* Plot1::getLegend1TR( Float_t text_size, Int_t text_font )
{
  Double_t x1 = 0.8;
  Double_t y1 = 0.8;
  Double_t x2 = 1 - gStyle->GetPadRightMargin() - 0.002;
  Double_t y2 = 1 - gStyle->GetPadTopMargin() - 0.005;
  TLegend* legend = new TLegend(x1,y1,x2,y2);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kBlack);
  legend->SetTextSize(text_size);
  legend->SetTextFont(text_font);
  return legend;
}
//==========================================================
// Legend Top Left
//==========================================================
TLegend* Plot1::getLegend1TL( Float_t text_size, Int_t text_font )
{
  Double_t x1 = gStyle->GetPadLeftMargin() + 0.0007;
  Double_t y1 = 0.80;
  Double_t x2 = 0.20;
  Double_t y2 = 1 - gStyle->GetPadTopMargin() - 0.01;
  TLegend* legend = new TLegend(x1,y1,x2,y2);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kBlack);
  legend->SetTextSize(text_size);
  legend->SetTextFont(text_font);
  return legend;
}
//==========================================================
// Legend Top Right
//==========================================================
TLegend* Plot1::getLegend2TR( Float_t text_size, Int_t text_font )
{
  Double_t x1 = 0.7;
  Double_t y1 = 0.70;
  Double_t x2 = 1 - gStyle->GetPadRightMargin() - 0.001;
  Double_t y2 = 1 - gStyle->GetPadTopMargin() - 0.001;
  TLegend* legend = new TLegend(x1,y1,x2,y2);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kBlack);
  legend->SetTextSize(text_size);
  legend->SetTextFont(text_font);
  return legend;
}
//==========================================================
// Legend Top Left
//==========================================================
TLegend* Plot1::getLegend2TL( Float_t text_size, Int_t text_font )
{
  Double_t x1 = gStyle->GetPadLeftMargin() + 0.001;
  Double_t y1 = 0.7;
  Double_t x2 = 0.32;
  Double_t y2 = 1 - gStyle->GetPadTopMargin() - 0.001;
  TLegend* legend = new TLegend(x1,y1,x2,y2);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kBlack);
  legend->SetTextSize(text_size);
  legend->SetTextFont(text_font);
  return legend;
}


//==========================================================
// Legend Top Right
//==========================================================
TLegend* Plot1::getLegend3TR( Float_t text_size, Int_t text_font )
{
  Double_t x1 = 0.6;
  Double_t y1 = 0.6;
  Double_t x2 = 1 - gStyle->GetPadRightMargin() - 0.002;
  Double_t y2 = 1 - gStyle->GetPadTopMargin() - 0.005;
  TLegend* legend = new TLegend(x1,y1,x2,y2);
  legend->SetFillColor(kWhite);
  //legend->SetLineColor(kBlack);
  legend->SetTextSize(text_size);
  legend->SetTextFont(text_font);
  return legend;
}
//==========================================================
//// Legend Top Left
////==========================================================
TLegend* Plot1::getLegend3TL( Float_t text_size, Int_t text_font )
{
  Double_t x1 = gStyle->GetPadLeftMargin() + 0.0005;
  Double_t y1 = 0.60;
  Double_t x2 = 0.40;
  Double_t y2 = 1 - gStyle->GetPadTopMargin() - 0.002;
  TLegend* legend = new TLegend(x1,y1,x2,y2);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kBlack);
  legend->SetTextSize(text_size);
  legend->SetTextFont(text_font);
  return legend;
}

//==========================================================
// Legend Bottom Left
//==========================================================
TLegend* Plot1::getLegend2BL()
{
  Double_t x1 = gStyle->GetPadLeftMargin() + 0.001;
  Double_t y1 = gStyle->GetPadBottomMargin()+ 0.001;
  Double_t x2 = 0.3;
  Double_t y2 = 0.3;
  TLegend* legend = new TLegend(x1,y1,x2,y2);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kBlack);
  legend->SetTextSize(0.044);
  return legend;
}

//==========================================================
// Legend Bottom Right
//==========================================================
TLegend* Plot1::getLegend2BR()
{
  Double_t x2 = 1 - gStyle->GetPadRightMargin() + 0.001 - 0.02;
  Double_t y2 = 0.37;
  Double_t x1 = 0.63;
  Double_t y1 = 0.02 + gStyle->GetPadBottomMargin() - 0.001;
  TLegend* legend = new TLegend(x1,y1,x2,y2);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kBlack);
  legend->SetTextSize(0.044);
  return legend;
}


//==========================================================
// Legend Top Left MC_Data
//==========================================================
TLegend* Plot1::getLegendTLDataMC()
{
  Double_t x1 = gStyle->GetPadRightMargin() + 0.035;
  Double_t y1 = 0.7;
  Double_t x2 = 0.3;
  Double_t y2 = 1 - gStyle->GetPadTopMargin() + 0.04;
  TLegend* legend = new TLegend(x1,y1,x2,y2);
  legend->SetFillColor(kWhite);
  //legend->SetLineColor(kBlack)
  legend->SetTextSize(0.050);
  return legend;
}

//==========================================================
// Legend Top Center
//==========================================================
TLegend* Plot1::getLegendTC()
{
  Double_t x1 = 0.4;
  Double_t y1 = 0.7;
  Double_t x2 = 0.6;
  Double_t y2 = 1 - gStyle->GetPadTopMargin();
  TLegend* legend = new TLegend(x1,y1,x2,y2);
  legend->SetFillColor(kWhite);
  //legend->SetLineColor(kBlack)
  legend->SetTextSize(0.044);
  return legend;
}

//==========================================================
// Get 1 stat text box
//==========================================================
void Plot1::draw1Stat(const TH1F *h1, Int_t Kolor)
{
  Float_t x1, x2, y1, y2;
  y1 = 1-gStyle->GetPadTopMargin()-0.15;
  y2 = 1-gStyle->GetPadTopMargin();
  x1 = 1-gStyle->GetPadLeftMargin()-0.18;
  x2 = 1-gStyle->GetPadRightMargin()+0.001;
  TPaveText *pt1 = new TPaveText(x1,y1,x2,y2,"NDC NB");
  pt1->SetTextColor(Kolor);
  pt1->AddText( Form("Mean %.3f", h1->GetMean()) );
  pt1->AddText( Form("RMS %.3f", h1->GetRMS()) );
  pt1->AddText( Form("Entries %.0f", h1->GetEntries()) );
  gPad->Update();

}

//==========================================================
// get 2 stat text boxes
//==========================================================
void Plot1::draw2Stat(const TH1F *h1, const TH1F *h2, Int_t Kolor1, Int_t Kolor2)
{
  Float_t x1, x2, y1, y2;

  // First histogram (MC)
  y1 = 1-gStyle->GetPadTopMargin()-0.15;
  y2 = 1-gStyle->GetPadTopMargin();
  x1 = 1-gStyle->GetPadLeftMargin()-0.18;
  x2 = 1-gStyle->GetPadRightMargin()+0.001;
  TPaveText *pt1a = new TPaveText(x1,y1,x2-0.10,y2);
  pt1a->SetOption("NB+NDC");
  pt1a->SetBorderSize(0);
  pt1a->SetTextColor(Kolor1);
  pt1a->SetFillStyle(0);
  pt1a->SetTextSize(0.04);
  pt1a->SetTextFont(42);
  pt1a->SetTextAlign(12);
  pt1a->AddText( "Mean" );
  pt1a->AddText( "RMS" );
  pt1a->AddText( "Entries" );
  pt1a->Draw();

  TPaveText *pt1b = new TPaveText(x1+0.10,y1,x2,y2);
  pt1b->SetOption("NB+NDC");
  pt1b->SetBorderSize(0);
  pt1b->SetTextColor(Kolor1);
  pt1b->SetFillStyle(0);;
  pt1b->SetTextSize(0.04);
  pt1b->SetTextFont(42);
  pt1b->SetTextAlign(32);
  pt1b->AddText( Form("%.3f", h1->GetMean()) );
  pt1b->AddText( Form("%.3f", h1->GetRMS()) );
  pt1b->AddText( Form("%.0f", h1->GetEntries()) );
  pt1b->Draw();
  gPad->Update();

  // second histogram (Data)
  y1 = 1-gStyle->GetPadTopMargin()-0.30;
  y2 = 1-gStyle->GetPadTopMargin()-0.15;
  x1 = 1-gStyle->GetPadLeftMargin()-0.18;
  x2 = 1-gStyle->GetPadRightMargin()+0.001;
  TPaveText *pt2a = new TPaveText(x1,y1,x2-0.10,y2);
  pt2a->SetOption("NB+NDC");
  pt2a->SetBorderSize(0);
  pt2a->SetTextColor(Kolor2);
  pt2a->SetFillStyle(0);
  pt2a->SetTextSize(0.04);
  pt2a->SetTextFont(42);
  pt2a->SetTextAlign(12);
  pt2a->AddText( "Mean" );
  pt2a->AddText( "RMS" );
  pt2a->AddText( "Entries" );
  pt2a->Draw("same");

  y1 = 1-gStyle->GetPadTopMargin()-0.30;
  y2 = 1-gStyle->GetPadTopMargin()-0.15;
  x1 = 1-gStyle->GetPadLeftMargin()-0.18;
  x2 = 1-gStyle->GetPadRightMargin()+0.001;
  TPaveText *pt2b = new TPaveText(x1+0.10,y1,x2,y2);
  pt2b->SetOption("NB+NDC");
  pt2b->SetBorderSize(0);
  pt2b->SetTextColor(Kolor2);
  pt2b->SetFillStyle(0);
  pt2b->SetTextSize(0.04);
  pt2b->SetTextFont(42);
  pt2b->SetTextAlign(32);  pt2b->AddText( Form("%.3f", h2->GetMean()) );
  pt2b->AddText( Form("%.3f", h2->GetRMS()) );
  pt2b->AddText( Form("%.0f", h2->GetEntries()) );
  pt2b->Draw("same");
  gPad->Update();

}

#endif

//#############################################
