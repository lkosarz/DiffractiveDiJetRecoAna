/*
 * HistogramsRecoClusters.h
 *
 *  Created on: 23 mar 2023
 *      Author: Khaless
 */

#ifndef HISTOGRAMSRECOCLUSTERS_H_
#define HISTOGRAMSRECOCLUSTERS_H_

#include <TH1.h>
#include <TH1D.h>

#include <TH2.h>
#include <TH2D.h>

#include <TMath.h>

using namespace TMath;

void CreateHistogamsRecoClusters();


// HcalEndcapNClusters

TH1D *h_nHCal_cluster_Rec_E;

TH1D *h_nHCal_nclusters_Rec;

TH1D *h_nHCal_cluster_Rec_pos_x;
TH1D *h_nHCal_cluster_Rec_pos_y;
TH1D *h_nHCal_cluster_Rec_pos_z;
TH2D *h_nHCal_cluster_Rec_pos_xy;

TH2D *h_nHCal_cluster_Rec_pos_rE;

// HcalEndcapNTruthClusters

TH1D *h_nHCal_cluster_MC_E;

TH1D *h_nHCal_nclusters_MC;

TH1D *h_nHCal_cluster_MC_pos_x;
TH1D *h_nHCal_cluster_MC_pos_y;
TH1D *h_nHCal_cluster_MC_pos_z;
TH2D *h_nHCal_cluster_MC_pos_xy;

TH2D *h_nHCal_cluster_MC_pos_rE;

//TH2D *h_nHCal_clusters_MC_eta_deltaRxy;
//TH2D *h_nHCal_clusters_Reco_eta_deltaRxy;


// HcalEndcapNTruthClusters hits
TH2D *h_nHCal_cluster_MC_hits_pos_xy;
TH2D *h_nHCal_cluster_MC_hitContribs_pos_xy;

// cluster distance
TH2D *h_nHCal_clusters_Reco_eta_deltaRxy;
TH2D *h_nHCal_clusters_MC_eta_deltaRxy;


void CreateHistogamsRecoClusters()
{

	// HcalEndcapNClusters
	h_nHCal_cluster_Rec_E = new TH1D("h_nHCal_cluster_Rec_E", "nHCal Rec clusters energy ; E [GeV]; counts", 100000, 0.0, 10.0);

	h_nHCal_nclusters_Rec = new TH1D("h_nHCal_nclusters_Rec", "No. of nHCal Rec clusters ; N_{clu}; counts", 501, -0.5, 500.5);

	h_nHCal_cluster_Rec_pos_x = new TH1D("h_nHCal_cluster_Rec_pos_x", "nHCal Rec cluster position x; x [mm]; counts", 1000, -5000.0, 5000.0);
	h_nHCal_cluster_Rec_pos_y = new TH1D("h_nHCal_cluster_Rec_pos_y", "nHCal Rec cluster position y; y [mm]; counts", 1000, -5000.0, 5000.0);
	h_nHCal_cluster_Rec_pos_z = new TH1D("h_nHCal_cluster_Rec_pos_z", "nHCal Rec cluster position z; y [mm]; counts", 1000, -5000.0, 5000.0);
	h_nHCal_cluster_Rec_pos_xy = new TH2D("h_nHCal_cluster_Rec_pos_xy", "nHCal Rec cluster position xy; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);

	h_nHCal_cluster_Rec_pos_rE = new TH2D("h_nHCal_cluster_Rec_pos_rE", "nHCal Rec cluster energy vs. radial position; r [mm]; E [GeV]; counts", 500, 0.0, 5000.0, 20000, 0.0, 20.0);


	// HcalEndcapNTruthClusters
	h_nHCal_cluster_MC_E = new TH1D("h_nHCal_cluster_MC_E", "nHCal MC clusters energy ; E [GeV]; counts", 100000, 0.0, 10.0);

	h_nHCal_nclusters_MC = new TH1D("h_nHCal_nclusters_MC", "No. of nHCal MC clusters ; N_{clu}; counts", 501, -0.5, 500.5);

	h_nHCal_cluster_MC_pos_x = new TH1D("h_nHCal_cluster_MC_pos_x", "nHCal MC cluster position x; x [mm]; counts", 1000, -5000.0, 5000.0);
	h_nHCal_cluster_MC_pos_y = new TH1D("h_nHCal_cluster_MC_pos_y", "nHCal MC cluster position y; y [mm]; counts", 1000, -5000.0, 5000.0);
	h_nHCal_cluster_MC_pos_z = new TH1D("h_nHCal_cluster_MC_pos_z", "nHCal MC cluster position z; y [mm]; counts", 1000, -5000.0, 5000.0);
	h_nHCal_cluster_MC_pos_xy = new TH2D("h_nHCal_cluster_MC_pos_xy", "nHCal MC cluster position xy; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);

	h_nHCal_cluster_MC_pos_rE = new TH2D("h_nHCal_cluster_MC_pos_rE", "nHCal MC cluster energy vs. radial position; r [mm]; E [GeV]; counts", 500, 0.0, 5000.0, 20000, 0.0, 20.0);

	//h_nHCal_clusters_MC_eta_deltaRxy = new TH2D("h_nHCal_clusters_MC_eta_deltaRxy", "MC cluster pairs #eta vs. #DeltaR_{xy}; #eta [1]; #DeltaR_{xy} [cm]; counts", 100, -10.0, 0.0, 100, 0.0, 500.0);
	//h_nHCal_clusters_Reco_eta_deltaRxy = new TH2D("h_nHCal_clusters_Reco_eta_deltaRxy", "Reco cluster pairs #eta vs. #DeltaR_{xy}; #eta [1]; #DeltaR_{xy} [cm]; counts", 100, -10.0, 0.0, 100, 0.0, 500.0);

	// HcalEndcapNTruthClusters hits
	h_nHCal_cluster_MC_hits_pos_xy = new TH2D("h_nHCal_cluster_MC_hits_pos_xy", "nHCal MC cluster hits position xy; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
	h_nHCal_cluster_MC_hitContribs_pos_xy = new TH2D("h_nHCal_cluster_MC_hitContribs_pos_xy", "nHCal MC cluster hit contributions position xy; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);


	// cluster distance
	h_nHCal_clusters_Reco_eta_deltaRxy = new TH2D("h_nHCal_clusters_Reco_eta_deltaRxy", "Reco clusters pair #eta vs. #DeltaR_{xy}; #eta [1]; #DeltaR_{xy} [cm]; counts", 200, -10.0, 10.0, 5000, 0.0, 500.0);
	h_nHCal_clusters_MC_eta_deltaRxy = new TH2D("h_nHCal_clusters_MC_eta_deltaRxy", "Truth clusters pair #eta vs. #DeltaR_{xy}; #eta [1]; #DeltaR_{xy} [cm]; counts", 200, -10.0, 10.0, 5000, 0.0, 500.0);


	// HcalEndcapNClusters

	h_nHCal_cluster_Rec_pos_x->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_nHCal_cluster_Rec_pos_y->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_nHCal_cluster_Rec_pos_z->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	h_nHCal_cluster_Rec_pos_xy->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_nHCal_cluster_Rec_pos_xy->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	h_nHCal_cluster_Rec_pos_rE->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	// HcalEndcapNTruthClusters

	h_nHCal_cluster_MC_pos_x->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_nHCal_cluster_MC_pos_y->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_nHCal_cluster_MC_pos_z->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	h_nHCal_cluster_MC_pos_xy->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_nHCal_cluster_MC_pos_xy->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	h_nHCal_cluster_MC_pos_rE->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	// HcalEndcapNTruthClusters hits
	h_nHCal_cluster_MC_hits_pos_xy->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_nHCal_cluster_MC_hits_pos_xy->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_nHCal_cluster_MC_hitContribs_pos_xy->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_nHCal_cluster_MC_hitContribs_pos_xy->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);



}


#endif /* HISTOGRAMSRECOCLUSTERS_H_ */
