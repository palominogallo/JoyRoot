#ifndef UTILS1_HH
#define UTILS1_HH

#include "def.hh"

class Utils1 {
	public:

  	//! Default Constructor
  	Utils1();

    //! Destructor
    virtual ~Utils1();

	public:
    //! Printing and text
    static void MyPrint( TCanvas *c, TString motherdirectory, TString localdirectory, TString name );
		static TString centText(const TString s, const int w);
		static TString centText(Double_t value, const int w);
		static TString centText(Float_t value, const int w);
		static TString centText(Int_t value, const int w);

    //! Calculations
    static Double_t getErrorMeansRatio( TH1F *h1,  TH1F *h2 );
    static Float_t getRelativeDifference( const TH1 *h1, const TH1 *h2, Float_t &Error );
    static Float_t getDifference( const TH1 *h1, const TH1 *h2, Float_t &Error );
    static Float_t getMedian( const TH1 *h1 );
    static Bool_t getFloatMedian( std::vector<Float_t> &v, Float_t &median );

    //! Book histo
    static TH1F* bookTH1F( TString name, TString title, Int_t nbins, Float_t xmin, Float_t xmax, Bool_t binSize=true );
    static TH1D* bookTH1D( TString name, TString title, Int_t nbins, Float_t xmin, Float_t xmax, Bool_t binSize=true );
    static TH2F* bookTH2F( TString name, TString title, Int_t xbins, Float_t xmin, Float_t xmax, Int_t ybins, Float_t ymin, Float_t ymax );
    static TH2D* bookTH2D( TString name, TString title, Int_t xbins, Float_t xmin, Float_t xmax, Int_t ybins, Float_t ymin, Float_t ymax );
    static TProfile* bookTProfile( TString name, TString title, Int_t nbins, Float_t xmin, Float_t xmax );

    //! retrieve histo from root file
    static TH1F* getTH1F( TFile* file, TString name );
    static TH1D* getTH1D( TFile* file, TString name );
    static TH2F* getTH2F( TFile* file, TString name );
    static TH2D* getTH2D( TFile* file, TString name );
    static TProfile* getTProfile( TFile* file, TString name );

		//! work  with TStrings
		static void splitTwoTStrings( const TString a, TString &a1, TString &a2, TString token="," );

};

#endif


