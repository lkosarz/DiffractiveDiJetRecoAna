#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "fmt/core.h"

#include "ROOT/RDataFrame.hxx"
#include <TH1D.h>
#include <TH2D.h>
#include <TRandom3.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TMath.h>
#include <TVector3.h>

#include "TROOT.h"
#include "TRandom.h"
#include "TH3.h"


#include "DD4hep/Detector.h"
#include "DDRec/CellIDPositionConverter.h"

#include <podio/Frame.h>
#include <podio/CollectionBase.h>
#include "podio/ROOTReader.h"
#include "podio/CollectionIDTable.h"
#include "podio/ObjectID.h"


#include "edm4hep/utils/kinematics.h"

#include "edm4hep/MCParticleCollection.h"
#include "edm4hep/MCParticleCollectionData.h"
#include "edm4hep/MCParticle.h"
#include "edm4hep/MCParticleData.h"

#include "edm4hep/SimCalorimeterHitCollectionData.h"
#include "edm4hep/SimCalorimeterHitCollection.h"
#include "edm4hep/SimCalorimeterHitData.h"
#include "edm4hep/SimCalorimeterHit.h"

#include "edm4hep/RawCalorimeterHitData.h"
#include "edm4hep/CalorimeterHitData.h"

#include "edm4hep/CalorimeterHit.h"
#include "edm4hep/CalorimeterHitCollectionData.h"
#include "edm4hep/CalorimeterHitCollection.h"
#include "edm4hep/CalorimeterHitData.h"
#include "edm4hep/CalorimeterHit.h"
#include "edm4hep/CalorimeterHitObj.h"

//dd4hep::sim::Geant4Calorimeter::Hit

#include "edm4eic/ReconstructedParticleCollection.h"
#include "edm4eic/MCRecoParticleAssociationCollection.h"

#include "edm4eic/ClusterCollection.h"
#include "edm4eic/Cluster.h"
#include "edm4eic/ClusterData.h"

#include "edm4eic/CalorimeterHitCollectionData.h"
#include "edm4eic/CalorimeterHitCollection.h"
#include "edm4eic/CalorimeterHitData.h"
#include "edm4eic/CalorimeterHit.h"
#include "edm4eic/CalorimeterHitObj.h"


#include <edm4eic/vector_utils_legacy.h>
#include <edm4hep/Vector3f.h>

///#include "eicd/Vector3f.h"

///#include "eicd/VectorXYZ.h"
//#include "eicd/Cluster.h"
//#include "eicd/ClusterData.h"
//#include "edm4hep/Vector3f.h"
//#include "Vector3D.h"
//include "eic/Vector3D.h"
//#include <eic/vector_utils.h>
//#include "dd4pod/CalorimeterHitData.h"

#include "FileList.h"
#include "HistogramsReco.h"
#include "HistogramsRecoClusters.h"
#include "BasicUtil.h"
#include "EICutil.h"

#pragma link C++ class vector<edm4hep::MCParticleData>+;
#pragma link C++ class vector<eicd::ClusterData>+;
#pragma link C++ class vector<podio::ObjectID>+;
#pragma link C++ class vector<edm4hep::SimCalorimeterHitData>+;
#pragma link C++ class vector<edm4hep::RawCalorimeterHitData>+;

#pragma link C++ class vector<edm4eic::CalorimeterHitData>+;
#pragma link C++ class vector<edm4eic::ClusterData>+;

//edm4hep::MCParticleCollectionData *MCParticles_data = 0;
vector<edm4hep::MCParticleData> *MCParticles_data = 0;
vector<podio::ObjectID> *MCparents_data = 0;
vector<podio::ObjectID> *MCdaughters_data = 0;

vector<edm4eic::CalorimeterHitData> *nHCal_data = 0;

vector<edm4eic::ClusterData> *nHCal_Cluster_Rec_data_vec = 0;
vector<podio::ObjectID> *nHCal_Cluster_Rec_assoc_vec = 0;

vector<edm4eic::ClusterData> *nHCal_Cluster_MC_data_vec = 0;
vector<podio::ObjectID> *nHCal_Cluster_MC_assoc_vec = 0;

using namespace std;
using namespace ROOT;
using namespace TMath;
//using namespace eicd;
using namespace edm4eic;
//using namespace edm4hep;

int readFrameRootReco(TString list = "data/test.list", TString ofname = "output/output_test.root", long nevents = -1);
int MakeEvent(podio::ROOTReader *reader, unsigned ev);


bool printEvNum = true;
bool debug = false;

int readFrameRootReco(TString list, TString ofname, long nevents)
{

	// open file w/ frame reader
	podio::ROOTReader *reader = new podio::ROOTReader();

	std::vector<std::string> filenames = openList(list);
	if(filenames.size() != 0) reader->openFiles(filenames);
	else {
		cout<<"Can't open file list! Exiting."<<endl;
		return 0;
	}

	std::vector<std::string_view> categories = reader->getAvailableCategories();

	cout<<"Available categories:"<<endl;
	PrintStringVector(categories);
	cout<<endl;


	unsigned nEvents = reader->getEntries(podio::Category::Event);
	cout<<"Number of events = "<<nEvents<<endl;

	if(nevents>0) nEvents = nevents;
	


	TFile *output = new TFile(ofname, "recreate");
	output->cd();

	CreateHistogamsReco();
	CreateHistogamsRecoClusters();


	if(nevents>0) nEvents = nevents;

	for(unsigned ev=0; ev<nEvents; ++ev) {

		if(printEvNum) std::cout<<"reading event "<<ev<<std::endl;

		MakeEvent(reader, ev); // execute for each event

		if(debug) std::cout<<"End of event"<<std::endl;

	} // event loop

	std::cout<<"Writing output"<<std::endl;

	output->Write();

	//DeleteHistogamsReco();
	//DeleteHistogamsRecoClusters();

	output->Close();

	std::cout<<"Finished!"<<std::endl;

	delete output;

	return 1;

}



int MakeEvent(podio::ROOTReader *reader, unsigned ev)
{

	// Get frame
    auto frame = podio::Frame(reader->readNextEntry(podio::Category::Event));

    std::vector<std::string> collections_names = frame.getAvailableCollections();

	if (ev==0) PrintStringVector(collections_names);

	//reader->goToEvent(ev);
	//reader->readEvent();
	if(printEvNum) std::cout<<"reading event "<<ev<<std::endl;

	//store->endOfEvent();


	// Get collections
	auto& MCParticles_coll  = frame.get<edm4hep::MCParticleCollection>("MCParticles");
	auto& nHCal_hitscoll = frame.get<edm4eic::CalorimeterHitCollection>("HcalEndcapNRecHits");
	auto& nHCal_Cluster_Rec_coll = frame.get<edm4eic::ClusterCollection>("HcalEndcapNClusters");
	auto& nHCal_Cluster_MC_coll = frame.get<edm4eic::ClusterCollection>("HcalEndcapNTruthClusters");


	int nPion_p = 0;
	int nPion_n = 0;
	int nKaon_p = 0;
	int nKaon_n = 0;
	int nProton_p = 0;
	int nProton_n = 0;
	int nElectron_p = 0;
	int nElectron_n = 0;

	int nNeutron = 0;
	int nGamma = 0;

	int nMCpart = 0;
	int nMCpart_gen = 0;
	int nMCpart_sec = 0;


	h_Events->Fill(1.0);

	// MC particle loop

	if(!MCParticles_coll.isValid())
		cout<<"MCParticleCollection does not exist!"<<endl;

	if(debug) cout<<"MCParticles size = "<<MCParticles_coll.size()<<endl;


	for (unsigned mc_iter = 0; mc_iter < MCParticles_coll.size(); ++mc_iter) {

		edm4hep::MCParticle mcpart =  MCParticles_coll.at(mc_iter);


		if(debug)
		{
			cout<<endl;

			cout<<"MCParticle generator status = "<<mcpart.getGeneratorStatus()<<endl;
			cout<<"MCParticle simulator status = "<<mcpart.getSimulatorStatus()<<endl;
			cout<<"MCParticle isCreatedInSimulation = "<<mcpart.isCreatedInSimulation()<<endl;
		}

		TVector3 mcMom(mcpart.getMomentum().x, mcpart.getMomentum().y, mcpart.getMomentum().z);
		TVector3 mcMomEnd(mcpart.getMomentumAtEndpoint ().x, mcpart.getMomentumAtEndpoint ().y, mcpart.getMomentumAtEndpoint ().z);
		TVector3 mcStart(mcpart.getVertex().x, mcpart.getVertex().y, mcpart.getVertex().z);
		TVector3 mcEnd(mcpart.getEndpoint().x, mcpart.getEndpoint().y, mcpart.getEndpoint().z);

		//vector<edm4hep::MCParticleData> *parents_check = new vector<edm4hep::MCParticleData>;
		//GetMCParentsData(mcpart_data, MCParticles_data, MCparents_data, parents_check);

		auto parents_check = mcpart.getParents();

		if(debug)
		{
			cout<<"MCParticle parents size = "<<parents_check.size()<<endl;
		}

		//if(mcpart.isCreatedInSimulation()) continue; // select primaries, reject secondaries
		//if(!mcpart.isCreatedInSimulation()) continue; // select secondaries, reject primaries
		//if(mcpart.getGeneratorStatus()!=1) continue; // select primaries, reject secondaries
		//if(mcpart.getGeneratorStatus()==1) continue; // select secondaries, reject primaries

		//	Correct!
		if(mcpart.getGeneratorStatus()!=1) continue; // select primaries, reject secondaries
		//if(mcpart.getGeneratorStatus()!=0) continue; // select secondaries, reject primaries
		//if(mcMom.Eta()<-4.0 ||  mcMom.Eta()>-1.0)	continue;
		if(mcMom.Eta()<-4.14 ||  mcMom.Eta()>-1.18)	continue;
		//if(mcEnd.z()>-3250)	continue;

		nMCpart++;

		if(debug)
		{
			cout<<"MCParticle px = "<<mcMom.x()<<endl;
			cout<<"MCParticle py = "<<mcMom.y()<<endl;
			cout<<"MCParticle pz = "<<mcMom.z()<<endl;
		}

		h_MCpart_mass->Fill(mcpart.getMass());
		h_MCpart_charge->Fill(mcpart.getCharge());
		h_MCpart_E->Fill(mcpart.getEnergy());
		h_MCpart_p->Fill(mcMom.Mag());
		h_MCpart_pT->Fill(mcMom.Pt());

		h_MCpart_mom_x->Fill(mcMom.x());
		h_MCpart_mom_y->Fill(mcMom.y());
		h_MCpart_mom_z->Fill(mcMom.z());

		h_MCpart_eta->Fill(mcMom.Eta());
		h_MCpart_etaphi->Fill(mcMom.Eta(), mcMom.Phi());

		h_MCpart_xy->Fill(mcStart.x(), mcStart.y());
		h_MCpart_zr->Fill(mcStart.z(), mcStart.Pt());

		h_MCpart_end_p->Fill(mcMomEnd.Mag());
		h_MCpart_end_pT->Fill(mcMomEnd.Pt());

		h_MCpart_posEnd_xy->Fill(mcEnd.x(), mcEnd.y());
		h_MCpart_posEnd_zr->Fill(mcEnd.z(), mcEnd.Pt());

		h_MCpart_genStatus->Fill(mcpart.getGeneratorStatus());

		if(mcpart.getPDG() == 211) nPion_p++;
		if(mcpart.getPDG() == -211) nPion_n++;
		if(mcpart.getPDG() == 321) nKaon_p++;
		if(mcpart.getPDG() == -321) nKaon_n++;
		if(mcpart.getPDG() == 2212) nProton_p++;
		if(mcpart.getPDG() == -2212) nProton_n++;
		if(mcpart.getPDG() == -11) nElectron_p++;
		if(mcpart.getPDG() == 11) nElectron_n++;

		if(mcpart.getPDG() == 2112) nNeutron++;
		if(mcpart.getPDG() == 22) nGamma++;


		// momentum
		if(mcpart.getPDG() == 211) h_MCpart_Pion_p_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == -211) h_MCpart_Pion_n_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == 321) h_MCpart_Kaon_p_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == -321) h_MCpart_Kaon_n_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == 2212) h_MCpart_Proton_p_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == -2212) h_MCpart_Proton_n_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == -11) h_MCpart_Electron_p_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == 11) h_MCpart_Electron_n_p->Fill(mcMom.Mag());

		if(mcpart.getPDG() == 2112) h_MCpart_Neutron_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == 22) h_MCpart_Gamma_p->Fill(mcMom.Mag());

		// energy
		if(mcpart.getPDG() == 211) h_MCpart_Pion_p_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == -211) h_MCpart_Pion_n_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == 321) h_MCpart_Kaon_p_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == -321) h_MCpart_Kaon_n_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == 2212) h_MCpart_Proton_p_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == -2212) h_MCpart_Proton_n_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == -11) h_MCpart_Electron_p_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == 11) h_MCpart_Electron_n_E->Fill(mcpart.getEnergy());

		if(mcpart.getPDG() == 2112) h_MCpart_Neutron_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == 22) h_MCpart_Gamma_E->Fill(mcpart.getEnergy());


		// eta, momentum
		if(mcpart.getPDG() == 211) h_MCpart_pion_p_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == -211) h_MCpart_pion_n_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == 321) h_MCpart_Kaon_p_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == -321) h_MCpart_Kaon_n_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == 2212) h_MCpart_proton_p_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == -2212) h_MCpart_proton_n_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == -11) h_MCpart_Electron_p_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == 11) h_MCpart_Electron_n_eta_p->Fill(mcMom.Eta(), mcMom.Mag());

		if(mcpart.getPDG() == 2112) h_MCpart_Neutron_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == 22) h_MCpart_Gamma_eta_p->Fill(mcMom.Eta(), mcMom.Mag());

		// eta, energy
		if(mcpart.getPDG() == 211) h_MCpart_Pion_p_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == -211) h_MCpart_Pion_n_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == 321) h_MCpart_Kaon_p_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == -321) h_MCpart_Kaon_n_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == 2212) h_MCpart_Proton_p_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == -2212) h_MCpart_Proton_n_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == -11) h_MCpart_Electron_p_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == 11) h_MCpart_Electron_n_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());

		if(mcpart.getPDG() == 2112) h_MCpart_Neutron_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == 22) h_MCpart_Gamma_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());


		// Generated MC particles
		if(mcpart.getGeneratorStatus()==1)
		{
			h_MCpart_gen_mass->Fill(mcpart.getMass());
			h_MCpart_gen_charge->Fill(mcpart.getCharge());
			h_MCpart_gen_E->Fill(mcpart.getEnergy());
			h_MCpart_gen_p->Fill(mcMom.Mag());
			h_MCpart_gen_pT->Fill(mcMom.Pt());

			h_MCpart_gen_eta->Fill(mcMom.Eta());
			h_MCpart_gen_etaphi->Fill(mcMom.Eta(), mcMom.Phi());

			h_MCpart_gen_xy->Fill(mcStart.x(), mcStart.y());
			h_MCpart_gen_zr->Fill(mcStart.z(), mcStart.Pt());

			h_MCpart_gen_end_p->Fill(mcMomEnd.Mag());
			h_MCpart_gen_end_pT->Fill(mcMomEnd.Pt());

			h_MCpart_gen_posEnd_xy->Fill(mcEnd.x(), mcEnd.y());
			h_MCpart_gen_posEnd_zr->Fill(mcEnd.z(), mcEnd.Pt());

			nMCpart_gen++;
		}


		// Secondary MC particles
		if(mcpart.getGeneratorStatus()==0)
		{
			h_MCpart_sec_mass->Fill(mcpart.getMass());
			h_MCpart_sec_charge->Fill(mcpart.getCharge());
			h_MCpart_sec_E->Fill(mcpart.getEnergy());
			h_MCpart_sec_p->Fill(mcMom.Mag());
			h_MCpart_sec_pT->Fill(mcMom.Pt());

			h_MCpart_sec_eta->Fill(mcMom.Eta());
			h_MCpart_sec_etaphi->Fill(mcMom.Eta(), mcMom.Phi());

			h_MCpart_sec_xy->Fill(mcStart.x(), mcStart.y());
			h_MCpart_sec_zr->Fill(mcStart.z(), mcStart.Pt());

			h_MCpart_sec_end_p->Fill(mcMomEnd.Mag());
			h_MCpart_sec_end_pT->Fill(mcMomEnd.Pt());

			h_MCpart_sec_posEnd_xy->Fill(mcEnd.x(), mcEnd.y());
			h_MCpart_sec_posEnd_zr->Fill(mcEnd.z(), mcEnd.Pt());

			nMCpart_sec++;

			bool parentIsPrimary = false;

			//podio::RelationRange<edm4hep::MCParticle> MCparents = mcpart.getParents();

			//vector<edm4hep::MCParticleData> *parents_data = new vector<edm4hep::MCParticleData>;
			//vector<edm4hep::MCParticleData> *daughters_data = new vector<edm4hep::MCParticleData>;

			auto parents_data = mcpart.getParents();
			auto daughters_data = mcpart.getDaughters();

			for (int parentIter = 0; parentIter < parents_data.size(); ++parentIter) {

				edm4hep::MCParticle mcpart_parent = parents_data.at(parentIter);

				if(mcpart.getGeneratorStatus()==1)	parentIsPrimary = true;
			}

			//for (int parentIter = 0; parentIter < MCparents.size(); ++parentIter) {
/*			for (int parentIter = mcpart_data.parents_begin; parentIter < mcpart_data.parents_end; ++parentIter) {

				//if(!MCParticles_data->at(parentIter).isCreatedInSimulation)	parentIsPrimary = true;

	        	unsigned parentID = MCparents_data->at(parentIter).index;

				edm4hep::MCParticleData mcpart_data_parent = MCParticles_data->at(parentID);
				edm4hep::MCParticle mcpart_parent(mcpart_data_parent.PDG, mcpart_data_parent.generatorStatus, mcpart_data_parent.simulatorStatus, mcpart_data_parent.charge, mcpart_data_parent.time, mcpart_data_parent.mass, mcpart_data_parent.vertex, mcpart_data_parent.endpoint, mcpart_data_parent.momentum, mcpart_data_parent.momentumAtEndpoint, mcpart_data_parent.spin, mcpart_data_parent.colorFlow);

				if(!mcpart_parent.isCreatedInSimulation())	parentIsPrimary = true;
			}*/

			// MC particles - 1st generation daughters
			if(parentIsPrimary)
			{
				h_MCpart_1stgen_daughter_mass->Fill(mcpart.getMass());
				h_MCpart_1stgen_daughter_charge->Fill(mcpart.getCharge());
				h_MCpart_1stgen_daughter_E->Fill(mcpart.getEnergy());
				h_MCpart_1stgen_daughter_p->Fill(mcMom.Mag());
				h_MCpart_1stgen_daughter_pT->Fill(mcMom.Pt());

				h_MCpart_1stgen_daughter_eta->Fill(mcMom.Eta());
				h_MCpart_1stgen_daughter_etaphi->Fill(mcMom.Eta(), mcMom.Phi());

				h_MCpart_1stgen_daughter_xy->Fill(mcStart.x(), mcStart.y());
				h_MCpart_1stgen_daughter_zr->Fill(mcStart.z(), mcStart.Pt());

				h_MCpart_1stgen_daughter_end_p->Fill(mcMomEnd.Mag());
				h_MCpart_1stgen_daughter_end_pT->Fill(mcMomEnd.Pt());

				h_MCpart_1stgen_daughter_posEnd_xy->Fill(mcEnd.x(), mcEnd.y());
				h_MCpart_1stgen_daughter_posEnd_zr->Fill(mcEnd.z(), mcEnd.Pt());
			}

		}	// Secondary MC particles

	} // MCParticles loop

	//h_MCpart->Fill(MCParticles_frame.size());
	//h_MCpart->Fill(MCParticles_data->size());
	h_MCpart->Fill(nMCpart);

	h_MCpart_nPion_p->Fill(nPion_p);
	h_MCpart_nPion_n->Fill(nPion_n);
	h_MCpart_nKaon_p->Fill(nKaon_p);
	h_MCpart_nKaon_n->Fill(nKaon_n);
	h_MCpart_nProton_p->Fill(nProton_p);
	h_MCpart_nProton_n->Fill(nProton_n);
	h_MCpart_nElectron_p->Fill(nElectron_p);
	h_MCpart_nElectron_n->Fill(nElectron_n);

	h_MCpart_nNeutron->Fill(nNeutron);
	h_MCpart_nGamma->Fill(nGamma);

	h_MCpart_nGen->Fill(nMCpart_gen);
	h_MCpart_nSec->Fill(nMCpart_sec);


	if(!nHCal_hitscoll.isValid())
		cout<<"HcalEndcapNHits collection does not exist!"<<endl;

	if(debug) cout<<"HcalEndcapNHits collection size = "<<nHCal_hitscoll.size()<<endl;

	h_nHCal_nhits->Fill(nHCal_hitscoll.size());


		for (unsigned hit_iter = 0; hit_iter < nHCal_hitscoll.size(); ++hit_iter) {

			edm4eic::CalorimeterHit hit_nHCal = nHCal_hitscoll.at(hit_iter);

			if(!hit_nHCal.isAvailable())
				cout<<"CalorimeterHit does not exist! index = "<<hit_nHCal<<endl;


			h_nHCal_hit_E->Fill(hit_nHCal.getEnergy());

			h_nHCal_hit_pos_x->Fill(hit_nHCal.getPosition().x);
			h_nHCal_hit_pos_y->Fill(hit_nHCal.getPosition().y);
			h_nHCal_hit_pos_z->Fill(hit_nHCal.getPosition().z);
			h_nHCal_hit_pos_xy->Fill(hit_nHCal.getPosition().x, hit_nHCal.getPosition().y);

			double rxy_hit = sqrt(hit_nHCal.getPosition().x*hit_nHCal.getPosition().x + hit_nHCal.getPosition().y*hit_nHCal.getPosition().y);


			h_nHCal_hit_pos_rE->Fill(rxy_hit, hit_nHCal.getEnergy());

		} // HcalEndcapNHits loop



		if(!nHCal_Cluster_Rec_coll.isValid())
				cout<<"HcalEndcapNClusters collection does not exist!"<<endl;

		if(debug) cout<<"HcalEndcapNClusters collection size = "<<nHCal_Cluster_Rec_coll.size()<<endl;

		h_nHCal_nclusters_Rec->Fill(nHCal_Cluster_Rec_coll.size());


		for (unsigned clu_iter = 0; clu_iter < nHCal_Cluster_Rec_coll.size(); ++clu_iter) {

			edm4eic::Cluster cluster_nHCal_Rec = nHCal_Cluster_Rec_coll.at(clu_iter);



			h_nHCal_cluster_Rec_E->Fill(cluster_nHCal_Rec.getEnergy());

			h_nHCal_cluster_Rec_pos_x->Fill(cluster_nHCal_Rec.getPosition().x);
			h_nHCal_cluster_Rec_pos_y->Fill(cluster_nHCal_Rec.getPosition().y);
			h_nHCal_cluster_Rec_pos_z->Fill(cluster_nHCal_Rec.getPosition().z);
			h_nHCal_cluster_Rec_pos_xy->Fill(cluster_nHCal_Rec.getPosition().x, cluster_nHCal_Rec.getPosition().y);

			double rxy = sqrt(cluster_nHCal_Rec.getPosition().x*cluster_nHCal_Rec.getPosition().x + cluster_nHCal_Rec.getPosition().y*cluster_nHCal_Rec.getPosition().y);

			h_nHCal_cluster_Rec_pos_rE->Fill(rxy, cluster_nHCal_Rec.getEnergy());

	        for (unsigned clu_iter2 = 0; clu_iter2 < nHCal_Cluster_Rec_coll.size(); ++clu_iter2) {

				edm4eic::Cluster cluster2_nHCal_Rec =  nHCal_Cluster_Rec_coll.at(clu_iter2);

	            if(clu_iter==clu_iter2)	continue;
	            double z1 = cluster_nHCal_Rec.getPosition().z;
	            double z2 = cluster2_nHCal_Rec.getPosition().z;
	            //if(abs(z2-z1) <=10){
	            //TVector3 mcProjPos2 = projTrackZ(mcMom2.Eta(), mcMom2.Phi(), projLayerZ, mcStart2);
	            double diffx2 = pow(cluster_nHCal_Rec.getPosition().x - cluster2_nHCal_Rec.getPosition().x, 2);
	            double diffy2 = pow(cluster_nHCal_Rec.getPosition().y - cluster2_nHCal_Rec.getPosition().y, 2);
	            double diffxy = sqrt(diffx2 + diffy2)/10.0; //convert to cm
	            //TVector3 diffVect = mcProjPos-mcProjPos2;
				//diffVect.SetMag(diffVect.Mag()/10.0); // convert [mm]->[cm]
	            double eta = - log(tan(cluster_nHCal_Rec.getIntrinsicTheta()/2));
	            h_nHCal_clusters_Reco_eta_deltaRxy->Fill(eta, diffxy);
	            //}

	        }


		} // HcalEndcapNClusters loop



		if(!nHCal_Cluster_MC_coll.isValid())
				cout<<"HcalEndcapNTruthClusters collection does not exist!"<<endl;

		if(debug) cout<<"HcalEndcapNTruthClusters collection size = "<<nHCal_Cluster_MC_coll.size()<<endl;

		h_nHCal_nclusters_MC->Fill(nHCal_Cluster_MC_coll.size());


		for (unsigned clu_iter = 0; clu_iter < nHCal_Cluster_MC_coll.size(); ++clu_iter) {

			edm4eic::Cluster cluster_nHCal_MC = nHCal_Cluster_MC_coll.at(clu_iter);


			h_nHCal_cluster_MC_E->Fill(cluster_nHCal_MC.getEnergy());

			h_nHCal_cluster_MC_pos_x->Fill(cluster_nHCal_MC.getPosition().x);
			h_nHCal_cluster_MC_pos_y->Fill(cluster_nHCal_MC.getPosition().y);
			h_nHCal_cluster_MC_pos_z->Fill(cluster_nHCal_MC.getPosition().z);
			h_nHCal_cluster_MC_pos_xy->Fill(cluster_nHCal_MC.getPosition().x, cluster_nHCal_MC.getPosition().y);

			double rxy = sqrt(cluster_nHCal_MC.getPosition().x*cluster_nHCal_MC.getPosition().x + cluster_nHCal_MC.getPosition().y*cluster_nHCal_MC.getPosition().y);

			h_nHCal_cluster_MC_pos_rE->Fill(rxy, cluster_nHCal_MC.getEnergy());

	        for (unsigned clu_iter2 = 0; clu_iter2 < nHCal_Cluster_MC_coll.size(); ++clu_iter2) {

				edm4eic::Cluster cluster2_nHCal_MC =  nHCal_Cluster_MC_coll.at(clu_iter2);

	            if(clu_iter==clu_iter2)	continue;
	            double z1 = cluster_nHCal_MC.getPosition().z;
	            double z2 = cluster2_nHCal_MC.getPosition().z;
	            //if(abs(z2-z1) <=10){
	            //TVector3 mcProjPos2 = projTrackZ(mcMom2.Eta(), mcMom2.Phi(), projLayerZ, mcStart2);
	            double diffx2 = pow(cluster_nHCal_MC.getPosition().x - cluster2_nHCal_MC.getPosition().x, 2);
	            double diffy2 = pow(cluster_nHCal_MC.getPosition().y - cluster2_nHCal_MC.getPosition().y, 2);
	            double diffxy = sqrt(diffx2 + diffy2)/10.0; //convert to cm
	            //TVector3 diffVect = mcProjPos-mcProjPos2;
				//diffVect.SetMag(diffVect.Mag()/10.0); // convert [mm]->[cm]
	            double eta = - log(tan(cluster_nHCal_MC.getIntrinsicTheta()/2));
	            h_nHCal_clusters_MC_eta_deltaRxy->Fill(eta, diffxy);
	            //}

	        }

	        auto MCclu_hit_contribs = cluster_nHCal_MC.getHitContributions();

	        for (int ihitc = 0; ihitc < MCclu_hit_contribs.size(); ++ihitc) {

	        	//edm4hep::CaloHitContribution MCclu_hit_cont = MCclu_hit_contribs.at(ihitc);
	        	auto MCclu_hit_cont = MCclu_hit_contribs.at(ihitc);

	        	//h_nHCal_cluster_MC_hitContribs_pos_xy->Fill(MCclu_hit_cont.getStepPosition().x, MCclu_hit_cont.getStepPosition().y);
			}

	        auto MCclu_hits = cluster_nHCal_MC.getHits();

	        for (int ihit = 0; ihit < MCclu_hits.size(); ++ihit) {

	        	edm4eic::CalorimeterHit MCclu_hit =  MCclu_hits.at(ihit);

	        	h_nHCal_cluster_MC_hits_pos_xy->Fill(MCclu_hit.getPosition().x, MCclu_hit.getPosition().y);
			}

	     //loop over all other clusters, fill histograms with distances between typical clusters (do same for reco)
	     //eventually loop at distances of clusters from neutrons, with all other clusters
	     //look into associations objects in the tree

		} // HcalEndcapNTruthClusters loop

	    //loop over one cluster, and inner loop with all other clusters nad check distances

	return 1;

}

