/*
 * HistDrawOpt.h
 *
 *  Created on: 26 sie 2015
 *      Author: Khaless
 */

#include "TString.h"

#ifndef HISTDRAWOPT_H_
#define HISTDRAWOPT_H_

TString getHistDrawOpt(TObject *obj, Bool_t &logScale, Bool_t &logScaleX, Bool_t &logScaleY);

TString getHistDrawOpt(TObject *obj, Bool_t &logScale, Bool_t &logScaleX, Bool_t &logScaleY)
{
	TString drawOpt;

	TString name = obj->GetName();

	//cout<<name<<endl;

	if(!name.CompareTo("h_Events")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_Events_types")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "eTEXT45";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Events_Diffractive")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}
	if(!name.CompareTo("h_Events_nPartonsOut")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_nPart_final")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_nJets")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_nJets_meas")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_xQ2")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kTRUE;
	}

	if(!name.CompareTo("h_Event_yQ2")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}

	if(!name.CompareTo("h_Event_xy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kTRUE;
	}
	if(!name.CompareTo("h_Event_nHCal_xQ2")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kTRUE;
	}

	if(!name.CompareTo("h_Event_nHCal_yQ2")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}

	if(!name.CompareTo("h_Event_nHCal_xy")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kTRUE;
	}

	if(!name.CompareTo("h_Event_nPion_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_nPion_n")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_nKaon_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_nKaon_n")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_nProton_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_nProton_n")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_nElectron_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_nElectron_n")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_nNeutron")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_nGamma")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		//logScale=kTRUE;
	}

	if(!name.CompareTo("h_Particle_eta_wE")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 100.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}

	if(!name.CompareTo("h_Event_HCal_jets")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colzTEXT";
		objH2->SetStats(false);
		objH2->SetMarkerSize(1.8);
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		logScale=kTRUE;
		logScaleX=kFALSE;
	}

	if(!name.CompareTo("h_Event_HCal_jets_meas")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colzTEXT";
		objH2->SetStats(false);
		objH2->SetMarkerSize(1.8);
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		logScale=kTRUE;
		logScaleX=kFALSE;
	}

	if(!name.CompareTo("h_Event_HCal_jets_meas_no_nHCal")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colzTEXT";
		objH2->SetStats(false);
		objH2->SetMarkerSize(1.8);
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		logScale=kTRUE;
		logScaleX=kFALSE;
	}

	if(!name.CompareTo("h_Event_HCal_jets_meas_full")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colzTEXT";
		objH2->SetStats(false);
		objH2->SetMarkerSize(1.8);
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		logScale=kTRUE;
		logScaleX=kFALSE;
	}

	if(!name.CompareTo("h_Event_Q2")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Event_x")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
		logScaleX=kTRUE;
	}
	if(!name.CompareTo("h_Event_y")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}


	if(!name.CompareTo("h_Event_nHCal_0_Q2")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Event_nHCal_0_x")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
		logScaleX=kTRUE;
	}
	if(!name.CompareTo("h_Event_nHCal_0_y")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}


	if(!name.CompareTo("h_Event_nHCal_1_Q2")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Event_nHCal_1_x")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
		logScaleX=kTRUE;
	}
	if(!name.CompareTo("h_Event_nHCal_1_y")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}


	if(!name.CompareTo("h_Event_nHCal_2_Q2")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Event_nHCal_2_x")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
		logScaleX=kTRUE;
	}
	if(!name.CompareTo("h_Event_nHCal_2_y")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}


	if(!name.CompareTo("h_Event_AllHCal_Q2")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Event_AllHCal_x")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
		logScaleX=kTRUE;
	}
	if(!name.CompareTo("h_Event_AllHCal_y")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}




	if(!name.CompareTo("h_Event_JetMeas_nHCal_0_Q2")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Event_JetMeas_nHCal_0_x")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
		logScaleX=kTRUE;
	}
	if(!name.CompareTo("h_Event_JetMeas_nHCal_0_y")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}


	if(!name.CompareTo("h_Event_JetMeas_nHCal_1_Q2")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Event_JetMeas_nHCal_1_x")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
		logScaleX=kTRUE;
	}
	if(!name.CompareTo("h_Event_JetMeas_nHCal_1_y")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}


	if(!name.CompareTo("h_Event_JetMeas_nHCal_2_Q2")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Event_JetMeas_nHCal_2_x")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
		logScaleX=kTRUE;
	}
	if(!name.CompareTo("h_Event_JetMeas_nHCal_2_y")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}


	if(!name.CompareTo("h_Event_JetMeas_AllHCal_Q2")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Event_JetMeas_AllHCal_x")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
		logScaleX=kTRUE;
	}
	if(!name.CompareTo("h_Event_JetMeas_AllHCal_y")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}

	if(!name.CompareTo("h_Partons_status")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 24.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Partons_types")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 24.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Partons_types_anti")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 24.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}

	if(!name.CompareTo("h_Partons_eta")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Partons_phi")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Partons_p")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Partons_pT")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}

	if(!name.CompareTo("h_Parton_eta_p")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Parton_eta_pT")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Parton_eta_E")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}


	if(!name.CompareTo("h_Parton_x_eta")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kTRUE;
	}
	if(!name.CompareTo("h_Parton_y_eta")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Parton_x_eta1")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kTRUE;
	}
	if(!name.CompareTo("h_Parton_y_eta1")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Parton_x_eta2")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kTRUE;
	}
	if(!name.CompareTo("h_Parton_y_eta2")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}


	if(!name.CompareTo("h_Particle_eta")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}

	if(!name.CompareTo("h_Particle_eta_p")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		objH2->GetYaxis()->SetRangeUser(0.0, 20.0);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Particle_eta_pT")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		objH2->GetYaxis()->SetRangeUser(0.0, 20.0);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Particle_eta_E")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		objH2->GetYaxis()->SetRangeUser(0.0, 20.0);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}


	if(!name.CompareTo("h_Jet_nPart")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 30.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_mass")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_charge")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_pT")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_eta")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_deta")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}


	if(!name.CompareTo("h_Jets_eta")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_phi")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_p")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_pT")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_E")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}

	if(!name.CompareTo("h_Jet_meas_nPart")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 30.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_mass")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_charge")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_pT")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_eta")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_eta")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}


	if(!name.CompareTo("h_Jets_meas_eta")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_meas_phi")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_meas_p")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_meas_pT")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_meas_E")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}


	if(!name.CompareTo("h_Jet_bHCal_part_eta")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_bHCal_part_eta")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}


	if(!name.CompareTo("h_Jet_HCal_part_eta")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jet_meas_HCal_part_eta")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}




	// Jets measured

	if(!name.CompareTo("h_Jet_meas_no_nHCal_nPart")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 30.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_no_nHCal_mass")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_no_nHCal_charge")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_no_nHCal_E")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_no_nHCal_p")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_no_nHCal_pT")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		objH1->GetXaxis()->SetRangeUser(0.0, 20.0);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_no_nHCal_eta")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}
	if(!name.CompareTo("h_Jet_meas_no_nHCal_deta")) {
		TH1 *objH1 = dynamic_cast<TH1*>(obj);
		drawOpt = "e";
		//objH1->GetXaxis()->SetRangeUser(0.0, 1.1);
		//objH1->RebinX(16);
		//drawOpt = "e";
		logScale=kTRUE;
	}


	if(!name.CompareTo("h_Jets_meas_no_nHCal_eta")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_meas_no_nHCal_phi")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_meas_no_nHCal_p")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_meas_no_nHCal_pT")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_meas_no_nHCal_E")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}


	// measured jets vs. partons
	if(!name.CompareTo("h_Jets_meas_Partons_eta")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_meas_Partons_phi")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jets_meas_Partons_E")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jet_meas_Parton_eta1")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jet_meas_Parton_phi1")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jet_meas_Parton_E1")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jet_meas_Parton_eta2")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jet_meas_Parton_phi2")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}
	if(!name.CompareTo("h_Jet_meas_Parton_E2")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		//objH2->RebinY(4);
		//objH2->RebinX(4);
		//objH2->GetYaxis()->SetRangeUser(0.0, 1.1);
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//drawOpt = "e";
		//logScale=kTRUE;
		logScaleX=kFALSE;
	}


/*
	if(!name.CompareTo("NtracksBvsF")) {
		TH2 *objH2 = dynamic_cast<TH2*>(obj);
		drawOpt = "colz";
		logScale=kFALSE;
		//objH2->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		//objH2->GetYaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
		objH2->SetTitle("Number of tracks backward vs. forward");
		objH2->GetXaxis()->SetTitle("Ntracks backward");
		objH2->GetYaxis()->SetTitle("Ntracks forward");
	}
*/



	return drawOpt;
}



#endif /* HISTDRAWOPT_H_ */
