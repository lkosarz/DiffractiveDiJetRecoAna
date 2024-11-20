#include <exception>
#include <assert.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>

#include "TString.h"
#include "TClonesArray.h"
#include "TRefArray.h"
#include "TRef.h"
#include "TFile.h"
#include "TArrayI.h"
#include "TTree.h"
#include "TH1.h"
#include "TH1I.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TBranch.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TPaveLabel.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TKey.h"
#include "TProfile.h"
#include "TGaxis.h"
#include "TList.h"

#include "DrawHistFile.h"
#include "HistDrawOpt.h"
//Int_t padw = 800, padh = 600;

#include "style.C"

using namespace std;




/////////////////////////////////////////////////////////////
Int_t drawHist() {

	style();
	//gStyle->SetOptStat(0);
	gROOT->ForceStyle();
	//gStyle->SetLineColor(kBlue);
	//gStyle->SetHistLineColor(kBlue);
	gStyle->SetHistLineColor(kBlack);
	gStyle->SetHistLineWidth(2);
	//gStyle->SetPaintTextFormat(".2e");
	gStyle->SetOptTitle(1);
	gStyle->SetOptStat(1);

	TGaxis::SetExponentOffset(0.02, -0.07, "x");


	vector<TString> *list_Events = new vector<TString>;
	vector<TString> *list_Events_special = new vector<TString>;
	vector<TString> *list_Partons = new vector<TString>;
	vector<TString> *list_Particle = new vector<TString>;
	vector<TString> *list_Jets = new vector<TString>;
	vector<TString> *list_Jets_meas = new vector<TString>;
	vector<TString> *list_Jets_meas_nHCal = new vector<TString>;
	vector<TString> *list_Jets_meas_no_nHCal = new vector<TString>;
	vector<TString> *list_Jets_Partons = new vector<TString>;

	// Event
	list_Events->push_back("h_Events");
	list_Events->push_back("h_Events_types");
	list_Events->push_back("h_Events_Diffractive");
	list_Events->push_back("h_Events_nPartonsOut");

	list_Events->push_back("h_Event_nPart_final");
	list_Events->push_back("h_Event_nJets");
	list_Events->push_back("h_Event_nJets_meas");
	list_Events->push_back("h_Event_nJets_meas_no_nHCal");

	list_Events->push_back("h_Event_xQ2");
	list_Events->push_back("h_Event_yQ2");
	list_Events->push_back("h_Event_xy");

	list_Events->push_back("h_Event_nHCal_xQ2");
	list_Events->push_back("h_Event_nHCal_yQ2");
	list_Events->push_back("h_Event_nHCal_xy");

	list_Events->push_back("h_Event_nPion_p");
	list_Events->push_back("h_Event_nPion_n");
	list_Events->push_back("h_Event_nKaon_p");
	list_Events->push_back("h_Event_nKaon_n");
	list_Events->push_back("h_Event_nProton_p");
	list_Events->push_back("h_Event_nProton_n");
	list_Events->push_back("h_Event_nElectron_p");
	list_Events->push_back("h_Event_nElectron_n");

	list_Events->push_back("h_Event_nNeutron");
	list_Events->push_back("h_Event_nGamma");

	list_Events->push_back("h_Event_HCal_jets");
	list_Events->push_back("h_Event_HCal_jets_meas");
	list_Events->push_back("h_Event_HCal_jets_meas_no_nHCal");

	list_Events->push_back("h_Event_HCal_jets_meas_full");

	list_Events->push_back("h_Particle_eta_wE");


	list_Events_special->push_back("h_Event_Q2");
	list_Events_special->push_back("h_Event_x");
	list_Events_special->push_back("h_Event_y");

	list_Events_special->push_back("h_Event_nHCal_0_Q2");
	list_Events_special->push_back("h_Event_nHCal_0_x");
	list_Events_special->push_back("h_Event_nHCal_0_y");

	list_Events_special->push_back("h_Event_nHCal_1_Q2");
	list_Events_special->push_back("h_Event_nHCal_1_x");
	list_Events_special->push_back("h_Event_nHCal_1_y");

	list_Events_special->push_back("h_Event_nHCal_2_Q2");
	list_Events_special->push_back("h_Event_nHCal_2_x");
	list_Events_special->push_back("h_Event_nHCal_2_y");

	list_Events_special->push_back("h_Event_AllHCal_Q2");
	list_Events_special->push_back("h_Event_AllHCal_x");
	list_Events_special->push_back("h_Event_AllHCal_y");

/*
	list_Events_special->push_back("h_Event_JetMeas_nHCal_0_Q2");
	list_Events_special->push_back("h_Event_JetMeas_nHCal_0_x");
	list_Events_special->push_back("h_Event_JetMeas_nHCal_0_y");

	list_Events_special->push_back("h_Event_JetMeas_nHCal_1_Q2");
	list_Events_special->push_back("h_Event_JetMeas_nHCal_1_x");
	list_Events_special->push_back("h_Event_JetMeas_nHCal_1_y");

	list_Events_special->push_back("h_Event_JetMeas_nHCal_2_Q2");
	list_Events_special->push_back("h_Event_JetMeas_nHCal_2_x");
	list_Events_special->push_back("h_Event_JetMeas_nHCal_2_y");

	list_Events_special->push_back("h_Event_JetMeas_AllHCal_Q2");
	list_Events_special->push_back("h_Event_JetMeas_AllHCal_x");
	list_Events_special->push_back("h_Event_JetMeas_AllHCal_y");
*/

	// Outgoing partons
	list_Partons->push_back("h_Partons_status");
	list_Partons->push_back("h_Partons_types");
	list_Partons->push_back("h_Partons_types_anti");

	list_Partons->push_back("h_Partons_eta");
	list_Partons->push_back("h_Partons_phi");
	list_Partons->push_back("h_Partons_p");
	list_Partons->push_back("h_Partons_pT");

	list_Partons->push_back("h_Parton_eta_p");
	list_Partons->push_back("h_Parton_eta_pT");
	list_Partons->push_back("h_Parton_eta_E");

	list_Partons->push_back("h_Parton_x_eta");
	list_Partons->push_back("h_Parton_y_eta");
	list_Partons->push_back("h_Parton_x_eta1");
	list_Partons->push_back("h_Parton_y_eta1");
	list_Partons->push_back("h_Parton_x_eta2");
	list_Partons->push_back("h_Parton_y_eta2");



	// Particles
	list_Particle->push_back("h_Particle_eta");

	list_Particle->push_back("h_Particle_eta_p");
	list_Particle->push_back("h_Particle_eta_pT");
	list_Particle->push_back("h_Particle_eta_E");


	// eta, momentum
	list_Particle->push_back("h_Particle_pion_p_eta_p");
	list_Particle->push_back("h_Particle_pion_n_eta_p");
	list_Particle->push_back("h_Particle_Kaon_p_eta_p");
	list_Particle->push_back("h_Particle_Kaon_n_eta_p");
	list_Particle->push_back("h_Particle_proton_p_eta_p");
	list_Particle->push_back("h_Particle_proton_n_eta_p");
	list_Particle->push_back("h_Particle_Electron_p_eta_p");
	list_Particle->push_back("h_Particle_Electron_n_eta_p");

	list_Particle->push_back("h_Particle_Neutron_eta_p");
	list_Particle->push_back("h_Particle_Gamma_eta_p");
/*
	// eta, transverse momentum pT
	list_Particle->push_back("h_Particle_pion_p_eta_pT");
	list_Particle->push_back("h_Particle_pion_n_eta_pT");
	list_Particle->push_back("h_Particle_Kaon_p_eta_pT");
	list_Particle->push_back("h_Particle_Kaon_n_eta_pT");
	list_Particle->push_back("h_Particle_proton_p_eta_pT");
	list_Particle->push_back("h_Particle_proton_n_eta_pT");
	list_Particle->push_back("h_Particle_Electron_p_eta_pT");
	list_Particle->push_back("h_Particle_Electron_n_eta_pT");

	list_Particle->push_back("h_Particle_Neutron_eta_pT");
	list_Particle->push_back("h_Particle_Gamma_eta_pT");

	// eta, energy
	list_Particle->push_back("h_Particle_Pion_p_eta_E");
	list_Particle->push_back("h_Particle_Pion_n_eta_E");
	list_Particle->push_back("h_Particle_Kaon_p_eta_E");
	list_Particle->push_back("h_Particle_Kaon_n_eta_E");
	list_Particle->push_back("h_Particle_Proton_p_eta_E");
	list_Particle->push_back("h_Particle_Proton_n_eta_E");
	list_Particle->push_back("h_Particle_Electron_p_eta_E");
	list_Particle->push_back("h_Particle_Electron_n_eta_E");

	list_Particle->push_back("h_Particle_Neutron_eta_E");
	list_Particle->push_back("h_Particle_Gamma_eta_E");
*/

	// Jets
	list_Jets->push_back("h_Jet_nPart");
	list_Jets->push_back("h_Jet_mass");
	list_Jets->push_back("h_Jet_charge");
	list_Jets->push_back("h_Jet_E");
	list_Jets->push_back("h_Jet_p");
	list_Jets->push_back("h_Jet_pT");
	list_Jets->push_back("h_Jet_eta");
	list_Jets->push_back("h_Jet_deta");

	list_Jets->push_back("h_Jets_eta");
	list_Jets->push_back("h_Jets_phi");
	list_Jets->push_back("h_Jets_p");
	list_Jets->push_back("h_Jets_pT");
	list_Jets->push_back("h_Jets_E");

	list_Jets->push_back("h_Jet_bHCal_part_eta");
	list_Jets->push_back("h_Jet_HCal_part_eta");


	// Jets measured
	list_Jets_meas->push_back("h_Jet_meas_nPart");
	list_Jets_meas->push_back("h_Jet_meas_mass");
	list_Jets_meas->push_back("h_Jet_meas_charge");
	list_Jets_meas->push_back("h_Jet_meas_E");
	list_Jets_meas->push_back("h_Jet_meas_p");
	list_Jets_meas->push_back("h_Jet_meas_pT");
	list_Jets_meas->push_back("h_Jet_meas_eta");
	list_Jets_meas->push_back("h_Jet_meas_deta");

	list_Jets_meas->push_back("h_Jets_meas_eta");
	list_Jets_meas->push_back("h_Jets_meas_phi");
	list_Jets_meas->push_back("h_Jets_meas_p");
	list_Jets_meas->push_back("h_Jets_meas_pT");
	list_Jets_meas->push_back("h_Jets_meas_E");

	list_Jets_meas->push_back("h_Jet_meas_bHCal_part_eta");
	list_Jets_meas->push_back("h_Jet_meas_HCal_part_eta");


	// Jets measured
	list_Jets_meas_nHCal->push_back("h_Jet_meas_nHCal_nPart");
	list_Jets_meas_nHCal->push_back("h_Jet_meas_nHCal_mass");
	list_Jets_meas_nHCal->push_back("h_Jet_meas_nHCal_charge");
	list_Jets_meas_nHCal->push_back("h_Jet_meas_nHCal_E");
	list_Jets_meas_nHCal->push_back("h_Jet_meas_nHCal_p");
	list_Jets_meas_nHCal->push_back("h_Jet_meas_nHCal_pT");
	list_Jets_meas_nHCal->push_back("h_Jet_meas_nHCal_eta");
	list_Jets_meas_nHCal->push_back("h_Jet_meas_nHCal_deta");

	list_Jets_meas_nHCal->push_back("h_Jets_meas_nHCal_eta");
	list_Jets_meas_nHCal->push_back("h_Jets_meas_nHCal_phi");
	list_Jets_meas_nHCal->push_back("h_Jets_meas_nHCal_p");
	list_Jets_meas_nHCal->push_back("h_Jets_meas_nHCal_pT");
	list_Jets_meas_nHCal->push_back("h_Jets_meas_nHCal_E");


	// Jets measured
	list_Jets_meas_no_nHCal->push_back("h_Jet_meas_no_nHCal_nPart");
	list_Jets_meas_no_nHCal->push_back("h_Jet_meas_no_nHCal_mass");
	list_Jets_meas_no_nHCal->push_back("h_Jet_meas_no_nHCal_charge");
	list_Jets_meas_no_nHCal->push_back("h_Jet_meas_no_nHCal_E");
	list_Jets_meas_no_nHCal->push_back("h_Jet_meas_no_nHCal_p");
	list_Jets_meas_no_nHCal->push_back("h_Jet_meas_no_nHCal_pT");
	list_Jets_meas_no_nHCal->push_back("h_Jet_meas_no_nHCal_eta");
	list_Jets_meas_no_nHCal->push_back("h_Jet_meas_no_nHCal_deta");

	list_Jets_meas_no_nHCal->push_back("h_Jets_meas_no_nHCal_eta");
	list_Jets_meas_no_nHCal->push_back("h_Jets_meas_no_nHCal_phi");
	list_Jets_meas_no_nHCal->push_back("h_Jets_meas_no_nHCal_p");
	list_Jets_meas_no_nHCal->push_back("h_Jets_meas_no_nHCal_pT");
	list_Jets_meas_no_nHCal->push_back("h_Jets_meas_no_nHCal_E");


	// measured jets vs. partons
	list_Jets_Partons->push_back("h_Jets_meas_Partons_eta");
	list_Jets_Partons->push_back("h_Jets_meas_Partons_phi");
	list_Jets_Partons->push_back("h_Jets_meas_Partons_E");

	list_Jets_Partons->push_back("h_Jet_meas_Parton_eta1");
	list_Jets_Partons->push_back("h_Jet_meas_Parton_phi1");
	list_Jets_Partons->push_back("h_Jet_meas_Parton_E1");
	list_Jets_Partons->push_back("h_Jet_meas_Parton_eta2");
	list_Jets_Partons->push_back("h_Jet_meas_Parton_phi2");
	list_Jets_Partons->push_back("h_Jet_meas_Parton_E2");


	//TCanvas *cnv = new TCanvas();
	//cnv->cd();

	TString outputdir = "output";

	gSystem->mkdir(outputdir);
	//gSystem->cd(outputdir);
	//cnv->cd()->SaveAs("hEventStat0.png");
	//gSystem->cd("../");

	gSystem->mkdir("output/Events/");
	gSystem->mkdir("output/Partons/");
	gSystem->mkdir("output/Particles/");
	gSystem->mkdir("output/Jets/");
	gSystem->mkdir("output/Jets_meas/");
	gSystem->mkdir("output/Jets_meas_nHCal/");
	//gSystem->mkdir("output/Jets_meas_no_nHCal/");
	//gSystem->mkdir("output/Jets_meas_partons/");

	//delete cnv;
	//file->Close();

	TString file = "data/diffractiveDiJets_ep_18x275GeV_reco_full.root";
	file = "data/diffractiveDiJets_ep_18x275GeV_anti_kT_pT4GeV_reco_full.root";

	drawAny("output/Events/", file, list_Events);
	gSystem->cd("../");
	//drawAny("output/Events/", file, list_Events_special);
	//gSystem->cd("../");
	//drawAny("output/Partons/", file, list_Partons);
	//gSystem->cd("../");
	drawAny("output/Particles/", file, list_Particle);
	gSystem->cd("../");
	drawAny("output/Jets/", file, list_Jets);
	gSystem->cd("../");
	drawAny("output/Jets_meas/", file, list_Jets_meas);
	gSystem->cd("../");
	drawAny("output/Jets_meas_nHCal/", file, list_Jets_meas_nHCal);
	gSystem->cd("../");
	//drawAny("output/Jets_meas_no_nHCal/", file, list_Jets_meas_no_nHCal);
	//gSystem->cd("../");
	//drawAny("output/Jets_meas_partons/", file, list_Jets_Partons);
	//gSystem->cd("../");


	return 1.0;

}
