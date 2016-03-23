#include "Utils1.hh"

//static bool sortfloat (Float_t i,Float_t j)
//{
//  return (i<j);
//}

ClassImp(Utils1)

Utils1::Utils1()
{
}

Utils1::~Utils1()
{
};

//==========================================================
//==========================================================
//! Text and printing
//==========================================================
//==========================================================

//==========================================================
// MyPrint
//==========================================================
void Utils1::MyPrint( TCanvas *c, TString motherdirectory, TString localdirectory, TString name ){
  const int oldVerbosity = gErrorIgnoreLevel;
  gErrorIgnoreLevel = 1001;
  /*
  c->Print( Form( "%s/plots/%s/%s.png", motherdirectory.c_str(), localdirectory.c_str(), name.c_str() ) );
  c->Print( Form( "%s/plots/%s/pdf/%s.pdf",motherdirectory.c_str(), localdirectory.c_str(), name.c_str() ) );
  c->Print( Form( "%s/plots/%s/C/%s.C", motherdirectory.c_str(), localdirectory.c_str(), name.c_str() ) );
  */
  gSystem->Exec("mkdir -p "+ motherdirectory+"/plots/"+localdirectory);
  gSystem->Exec("mkdir -p "+ motherdirectory+"/plots/"+localdirectory+"/eps/");
  gSystem->Exec("mkdir -p "+ motherdirectory+"/plots/"+localdirectory+"/pdf/");
  gSystem->Exec("mkdir -p "+ motherdirectory+"/plots/"+localdirectory+"/C/");

  c->Print( motherdirectory+TString("/plots/")+localdirectory+TString("/eps/")+name+TString(".eps") );
  c->Print( motherdirectory+TString("/plots/")+localdirectory+TString("/pdf/")+name+TString(".pdf") );
  c->Print( motherdirectory+TString("/plots/")+localdirectory+TString("/C/")+name+TString(".C") );
  gErrorIgnoreLevel = oldVerbosity;
}

//==========================================================
// centText
//==========================================================
TString Utils1::centText(const TString s, const int w)
{

	TString ss, spaces = "";
	int padding = w - s.Length();
	for(int i = 0; i < padding/2; i++ ) spaces = spaces + " ";

	ss = spaces+s+spaces;

	if( padding > 0 && padding%2 != 0 ) ss = ss + " ";

	return ss;
}

//==========================================================
// centText
//==========================================================
TString Utils1::centText(Double_t value, const int w)
{
	return centText( Form( "%.3f", value), w );
}

//==========================================================
// centText
//==========================================================
TString Utils1::centText(Float_t value, const int w)
{
	return centText( Form( "%.3f", value), w );
}

//==========================================================
// centText
//==========================================================
TString Utils1::centText(Int_t value, const int w)
{
	return centText( Form( "%d", value), w );
}

//==========================================================
//==========================================================
//! Caculations
//==========================================================
//==========================================================

//==========================================================
// getErrorMeansRatio
//==========================================================
Double_t Utils1::getErrorMeansRatio( TH1F *h1,  TH1F *h2 )
{
  Double_t error1 = h1->GetRMS()/sqrt( h1->Integral() );
  Double_t error2 = h2->GetRMS()/sqrt( h2->Integral() );
  Double_t mean1 = h1->GetMean();
  Double_t mean2 = h2->GetMean();
  Double_t mean3 = mean1 / mean2;
  return mean3*sqrt( pow(error1/mean1,2) + pow(error2/mean2,2) );
}

//==========================================================
// getRelativeDifference
//==========================================================
Float_t Utils1::getRelativeDifference( const TH1 *h1, const TH1 *h2, Float_t &Error )
{
  Float_t M1 = h1->GetMean();
  Float_t E1 = h1->GetRMS() / sqrt(h1->GetEntries());
  Float_t M2 = h2->GetMean();
  Float_t E2 = h2->GetRMS() / sqrt(h2->GetEntries());
  Float_t Subtraction = M1 - M2;
  Float_t ErrorSubtraction =  sqrt( pow(E1,2) + pow(E2,2) ); // to calculate relative error
  Float_t Relative = Subtraction / M2;
  if ( Subtraction !=0 )
    Error = fabs(Relative) * sqrt( pow(ErrorSubtraction/Subtraction,2) + pow(E2/M2,2) );
  else
    Error = 0;

  return Relative;
}
//==========================================================
// getDifference
//==========================================================
Float_t Utils1::getDifference( const TH1 *h1, const TH1 *h2, Float_t &Error )
{
  Float_t M1 = h1->GetMean();
  Float_t E1 = h1->GetRMS() / sqrt(h1->GetEntries());
  Float_t M2 = h2->GetMean();
  Float_t E2 = h2->GetRMS() / sqrt(h2->GetEntries());
  Float_t Subtraction = M1 - M2;
  if ( Subtraction != 0 )
    Error =  sqrt( pow(E1,2) + pow(E2,2) );
  else
    Error = 0;

  return Subtraction;
}

//==========================================================
// getMedian
//==========================================================
Float_t Utils1::getMedian( const TH1 *h1 )
{
  const Int_t nBins = h1->GetXaxis()->GetNbins();
  Double_t x[nBins];
  Double_t w[nBins];

  for (int i = 1; i <= nBins; i++)
  {
    x[i-1] = h1->GetBinCenter(i);
    w[i-1] = h1->GetBinContent(i);
  }

  return  Float_t( TMath::Median(nBins, x, w) );
}

//==========================================================
//==========================================================
//! Histograms
//==========================================================
//==========================================================

//==========================================================
// bookTH1F
//==========================================================
TH1F *Utils1::bookTH1F( TString name, TString title, Int_t nbins, Float_t xmin, Float_t xmax, Bool_t binSize )
{
  TH1F *h = new TH1F( name, title, nbins, xmin, xmax );
	h->SetXTitle( Form("%s %s",h->GetXaxis()->GetTitle(),h->GetZaxis()->GetTitle() ) ); // units
	if ( binSize)
		h->SetYTitle( Form("%s%.2f %s",h->GetYaxis()->GetTitle(), (xmax-xmin)/nbins, h->GetZaxis()->GetTitle() ) );
	else
		h->SetYTitle( Form("%s",h->GetYaxis()->GetTitle() ) );
  return h;
}
//==========================================================
// bookTH1D
//==========================================================
TH1D *Utils1::bookTH1D( TString name, TString title, Int_t nbins, Float_t xmin, Float_t xmax, Bool_t binSize )
{
  TH1D *h = new TH1D( name, title, nbins, xmin, xmax );
  h->SetXTitle( Form("%s %s",h->GetXaxis()->GetTitle(),h->GetZaxis()->GetTitle() ) ); // units
	if ( binSize)
		h->SetYTitle( Form("%s%.2f %s",h->GetYaxis()->GetTitle(), (xmax-xmin)/nbins, h->GetZaxis()->GetTitle() ) );
	else
		h->SetYTitle( Form("%s",h->GetYaxis()->GetTitle() ) );
  return h;
}
//==========================================================
// bookTH2F
//==========================================================
TH2F *Utils1::bookTH2F( TString name, TString title, Int_t xbins, Float_t xmin, Float_t xmax, Int_t ybins, Float_t ymin, Float_t ymax )
{
  TH2F *h = new TH2F( name, title, xbins, xmin, xmax, ybins, ymin, ymax );
  return h;
}
//==========================================================
// bookTH2D
//==========================================================
TH2D *Utils1::bookTH2D( TString name, TString title, Int_t xbins, Float_t xmin, Float_t xmax, Int_t ybins, Float_t ymin, Float_t ymax )
{
  TH2D *h = new TH2D( name, title, xbins, xmin, xmax, ybins, ymin, ymax );
  return h;
}
//==========================================================
// bookTProfile
//==========================================================
TProfile *Utils1::bookTProfile( TString name, TString title, Int_t nbins, Float_t xmin, Float_t xmax )
{
  TProfile *h = new TProfile( name, title, nbins, xmin, xmax );
  return h;
}

//==========================================================
// getTH1F - retrieve
//==========================================================
TH1F *Utils1::getTH1F( TFile* file, TString name )
{
  TH1F *h = (TH1F*)file->Get( name );
  return h;
}
//==========================================================
// getTH1D - retrieve
//==========================================================
TH1D *Utils1::getTH1D( TFile* file, TString name )
{
  TH1D *h = (TH1D*)file->Get( name );
  return h;
}
//==========================================================
// getTH2F - retrieve
//==========================================================
TH2F *Utils1::getTH2F( TFile* file, TString name )
{
  TH2F *h = (TH2F*)file->Get( name );
  return h;
}
//==========================================================
// getTH1D - retrieve
//==========================================================
TH2D *Utils1::getTH2D( TFile* file, TString name )
{
  TH2D *h = (TH2D*)file->Get( name );
  return h;
}
//==========================================================
// getTProfile - retrieve
//==========================================================
TProfile *Utils1::getTProfile( TFile* file, TString name )
{
  TProfile *h = (TProfile*)file->Get( name );
  return h;
}

//==========================================================
// splitTwoTStrings
//==========================================================
void Utils1::splitTwoTStrings( const TString a, TString &a1, TString &a2, TString token )
{
	TObjArray *x = a.Tokenize(token);
	a1 = ( (TObjString*)x->At(0))->GetString();
	a2 = ( (TObjString*)x->At(1))->GetString();
}


//#############################################

