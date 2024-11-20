#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <optional>

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
#include <edm4hep/utils/vector_utils.h>

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
#include "edm4eic/ReconstructedParticle.h"

#include "edm4eic/MCRecoParticleAssociationCollection.h"


#include "edm4eic/ClusterCollection.h"
#include "edm4eic/Cluster.h"
#include "edm4eic/ClusterData.h"

#include "edm4eic/CalorimeterHitCollectionData.h"
#include "edm4eic/CalorimeterHitCollection.h"
#include "edm4eic/CalorimeterHitData.h"
#include "edm4eic/CalorimeterHit.h"
#include "edm4eic/CalorimeterHitObj.h"

#include "edm4eic/TrackSegmentCollection.h"
#include "edm4eic/TrackPoint.h"

#include "fastjet/ClusterSequence.hh"

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
#include "HistogramsJets.h"
#include "BasicUtil.h"
//#include "EICutil.h"

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
using namespace fastjet;

int readFrameRootReco(TString list = "data/test.list", TString ofname = "output/output_test.root", long nevents = -1);
int MakeEvent(podio::ROOTReader *reader, unsigned ev);

fastjet::PseudoJet createPseudoJet(double energy, double eta, double phi);


bool printEvNum = true;
bool debug = false;

int main(int argc, char **argv)
{
	readFrameRootReco();

	return 1;
}

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
	CreateHistogramsJets();

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

	auto& RecParticles_coll  = frame.get<edm4eic::ReconstructedParticleCollection>("ReconstructedChargedParticles");

	auto& nHCal_hitscoll = frame.get<edm4eic::CalorimeterHitCollection>("HcalEndcapNRecHits");
	auto& nHCal_Cluster_Rec_coll = frame.get<edm4eic::ClusterCollection>("HcalEndcapNClusters");
	auto& nHCal_Cluster_MC_coll = frame.get<edm4eic::ClusterCollection>("HcalEndcapNTruthClusters");

	// grab collections
	auto& segments = frame.get<edm4eic::TrackSegmentCollection>("CalorimeterTrackProjections");

	int nPartFinal = 0;
	int nPartonsOut = 0;
	int iParton_1 = 0;
	int iParton_2 = 0;

	bool Parton_1_inAcc = false;
	bool Parton_2_inAcc = false;

	int nJetsInAcc = 0;

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

	// create a jet definition:
	// a jet algorithm with a given radius parameter
	//----------------------------------------------------------
	double R = 1.0;
	double p = -1.0;
	fastjet::JetDefinition jet_def(fastjet::antikt_algorithm, R);
	//fastjet::JetDefinition jet_def(fastjet::ee_kt_algorithm);
	//fastjet::JetDefinition jet_def(fastjet::ee_genkt_algorithm, R, p);
	//fastjet::JetDefinition jet_def_meas(fastjet::ee_kt_algorithm);

	vector<fastjet::PseudoJet> input_particles;
	vector<fastjet::PseudoJet> input_particles_meas;
	vector<fastjet::PseudoJet> input_particles_meas_nHCal;
	vector<fastjet::PseudoJet> input_particles_meas_no_nHCal;


	cout<<"Starting!"<<endl;

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
		//if(mcMom.Eta()<-4.14 ||  mcMom.Eta()>-1.18)	continue;
		//if(mcEnd.z()>-3250)	continue;

		nMCpart++;

		if(debug)
		{
			cout<<"MCParticle px = "<<mcMom.x()<<endl;
			cout<<"MCParticle py = "<<mcMom.y()<<endl;
			cout<<"MCParticle pz = "<<mcMom.z()<<endl;
		}



		// read in input particles
		//----------------------------------------------------------
		input_particles.push_back(fastjet::PseudoJet(mcMom.x(),mcMom.y(),mcMom.z(),mcpart.getEnergy()));
		//cout<<"input_particles add = "<<i<<endl;


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



		if(!RecParticles_coll.isValid())
			cout<<"ReconstructedChargedParticles does not exist!"<<endl;

		if(debug) cout<<"MCParticles size = "<<RecParticles_coll.size()<<endl;




		for (unsigned rec_iter = 0; rec_iter < RecParticles_coll.size(); ++rec_iter) {

			edm4eic::ReconstructedParticle recopart =  RecParticles_coll.at(rec_iter);

			TVector3 recoMom(recopart.getMomentum().x, recopart.getMomentum().y, recopart.getMomentum().z);

			// read in input particles
			//----------------------------------------------------------
			input_particles_meas.push_back(fastjet::PseudoJet(recoMom.x(),recoMom.y(),recoMom.z(),recopart.getEnergy()));
			//cout<<"input_particles add = "<<i<<endl;

			input_particles_meas_nHCal.push_back(fastjet::PseudoJet(recoMom.x(),recoMom.y(),recoMom.z(),recopart.getEnergy()));

			input_particles_meas_no_nHCal.push_back(fastjet::PseudoJet(recoMom.x(),recoMom.y(),recoMom.z(),recopart.getEnergy()));

		}


		// Track-cluster projections ///////////////////////////////////////////

		int nClustNotMatched = 0;

		// loop over clusters
		for (unsigned iClust = 0; iClust < nHCal_Cluster_Rec_coll.size(); ++iClust) {
		    //for (size_t iClust = 0; edm4eic::Cluster cluster : nHCal_Cluster_Rec_coll) {

			edm4eic::Cluster cluster = nHCal_Cluster_Rec_coll.at(iClust);


		      // grab eta/phi of cluster
		      const double etaClust  = edm4hep::utils::eta( cluster.getPosition() );
		      const double phiClust  = edm4hep::utils::angleAzimuthal( cluster.getPosition() );

		      // match based on eta/phi dstiance
		      //double distMatch = std::numeric_limits<double>::max();
		      double distMatch = 0.3;

		      // loop over projections to find matching one
		      std::optional<edm4eic::TrackPoint> match;
		      for (edm4eic::TrackSegment segment : segments) {
		        for (edm4eic::TrackPoint projection : segment.getPoints()) {

		          // ignore if not pointing to calo or at face of calo, nHCal = 113
		          const bool isInSystem = (projection.system == 113);
		          const bool isAtFace   = (projection.surface == 1);
		          if (!isInSystem || !isAtFace) continue;

		          // grab eta/phi of projection
		          const double etaProject = edm4hep::utils::eta( projection.position );
		          const double phiProject = edm4hep::utils::angleAzimuthal( projection.position );

		          // get distance to projection
		          const double distProject = std::hypot(
		            etaClust - etaProject,
		            phiClust - phiProject
		          );

		          // if smallest distance found, update variables accordingly
		          if (distProject < distMatch) {
		            distMatch = distProject;
		            match     = projection;
		          }

		        }  // end point loop
		      }  // end segment loop


		      // do analysis if match was found...
		      if ( !match.has_value() ) {
		        //edm4eic::TrackPoint matchedProject = match.value();
		        //std::cout << "        Found match! match = " << matchedProject << std::endl;
		        ++nClustNotMatched;


				TVector3 cluPos(cluster.getPosition().x, cluster.getPosition().y, cluster.getPosition().z);

		        input_particles_meas_nHCal.push_back(createPseudoJet(cluster.getEnergy(), cluPos.Eta(), cluPos.Phi()));

		      }
		      //++nClustTotal;


		    }  // end cluster loop

		//if(nClustNotMatched > 0)

		// JETS ////////////////////////////////////////////////////////////////


	    // run the jet clustering with the above jet definition
	    //----------------------------------------------------------
	    fastjet::ClusterSequence clust_seq(input_particles, jet_def);
	    fastjet::ClusterSequence clust_seq_meas(input_particles_meas, jet_def);
	    fastjet::ClusterSequence clust_seq_meas_nHCal(input_particles_meas_nHCal, jet_def);
	    fastjet::ClusterSequence clust_seq_meas_no_nHCal(input_particles_meas_no_nHCal, jet_def);


	    // get the resulting jets ordered in pt
	    //----------------------------------------------------------
	    double ptmin = 4.0; // 5.0 [GeV/c]
	    double Emin = 0.0; // 5.0 [GeV/c]
	    vector<fastjet::PseudoJet> inclusive_jets_unsorted;
	    vector<fastjet::PseudoJet> measured_jets_unsorted;
	    vector<fastjet::PseudoJet> measured_jets_nHCal_unsorted;
	    vector<fastjet::PseudoJet> measured_jets_no_nHCal_unsorted;

	    vector<fastjet::PseudoJet> inclusive_jets;
	    vector<fastjet::PseudoJet> measured_jets;
	    vector<fastjet::PseudoJet> measured_jets_nHCal;
	    vector<fastjet::PseudoJet> measured_jets_no_nHCal;

	    //vector<fastjet::PseudoJet> inclusive_jets = sorted_by_pt(clust_seq.inclusive_jets(ptmin));
	    //inclusive_jets = sorted_by_E(clust_seq.inclusive_jets(ptmin));
	    //measured_jets = sorted_by_E(clust_seq_meas.inclusive_jets(ptmin));

	    vector<fastjet::PseudoJet> inclusive_jets_precut = sorted_by_E(clust_seq.inclusive_jets(ptmin));
	    vector<fastjet::PseudoJet> measured_jets_precut = sorted_by_E(clust_seq_meas.inclusive_jets(ptmin));
	    vector<fastjet::PseudoJet> measured_jets_nHCal_precut = sorted_by_E(clust_seq_meas_nHCal.inclusive_jets(ptmin));
	    vector<fastjet::PseudoJet> measured_jets_no_nHCal_precut = sorted_by_E(clust_seq_meas_no_nHCal.inclusive_jets(ptmin));



	    // apply energy cut
	    for (int i = 0; i < inclusive_jets_precut.size(); ++i)
	    {
			fastjet::PseudoJet jet = inclusive_jets_precut[i];

			if(jet.E()<Emin) continue;

			if(jet.eta()>=-4.14 &&  jet.eta()<=4.2) nJetsInAcc++;

			inclusive_jets_unsorted.push_back(jet);
		}

	    for (int i = 0; i < measured_jets_precut.size(); ++i)
	    {
			fastjet::PseudoJet jet = measured_jets_precut[i];

			if(jet.E()<Emin) continue;

			measured_jets_unsorted.push_back(jet);
		}

	    for (int i = 0; i < measured_jets_nHCal_precut.size(); ++i)
	    {
			fastjet::PseudoJet jet = measured_jets_nHCal_precut[i];

			if(jet.E()<Emin) continue;

			measured_jets_nHCal_unsorted.push_back(jet);
		}

	    for (int i = 0; i < measured_jets_no_nHCal_precut.size(); ++i)
	    {
			fastjet::PseudoJet jet = measured_jets_no_nHCal_precut[i];

			if(jet.E()<Emin) continue;

			measured_jets_no_nHCal_unsorted.push_back(jet);
		}

	    // sort jets vs. energy
	/*
	    inclusive_jets = sorted_by_E(inclusive_jets_unsorted);
	    measured_jets = sorted_by_E(measured_jets_unsorted);
	    measured_jets_nHCal = sorted_by_E(measured_jets_nHCal_unsorted);
	    measured_jets_no_nHCal = sorted_by_E(measured_jets_no_nHCal_unsorted);
	    */

	    // sort jets vs. pT
	    inclusive_jets = sorted_by_pt(inclusive_jets_unsorted);
	    measured_jets = sorted_by_pt(measured_jets_unsorted);
	    measured_jets_nHCal = sorted_by_pt(measured_jets_nHCal_unsorted);
	    measured_jets_no_nHCal = sorted_by_pt(measured_jets_no_nHCal_unsorted);

		//cout<<"inclusive_jets size = "<<inclusive_jets.size()<<endl;
		//cout<<"measured_jets size = "<<measured_jets.size()<<endl;



		h_Event_nJets->Fill(inclusive_jets.size());
		h_Event_nJets_meas->Fill(measured_jets.size());
		h_Event_nJets_meas_nHCal->Fill(measured_jets_nHCal.size());
		h_Event_nJets_meas_no_nHCal->Fill(measured_jets_no_nHCal.size());

		// summary
		bool anyHcal_jets = false;
		bool anyHcal_jets_meas = false;
		bool anyHcal_jets_meas_nHCal = false;
		bool anyHcal_jets_meas_no_nHCal = false;
		bool bHCalJet = false;
		bool bHCalJet_meas = false;
		int nHCal_jets = 0;
		int nHCal_jets_meas = 0;

/*		//int nHCal_jets = FillHCals(h_Event_HCal_jets, hist_eta_energy_tmp, hist_eta_energy_denom_tmp, anyHcal_jets);
		FillHCalsJets(h_Event_HCal_jets, inclusive_jets);
		FillHCalsJets(h_Event_HCal_jets_meas, measured_jets);
		FillHCalsJets(h_Event_HCal_jets_meas_nHCal, measured_jets_nHCal);
		FillHCalsJets(h_Event_HCal_jets_meas_no_nHCal, measured_jets_no_nHCal);

		FillHCalsJetsShare(h_Event_HCal_jets_meas_full, measured_jets);
*/

		for (unsigned int i = 0; i < inclusive_jets.size(); i++) {

			fastjet::PseudoJet jet = inclusive_jets[i];

			int HCal_id = 0; // none = 0, nHCal = 1, bHCal = 2, LFHCAL = 3

			// nHCal
			if(-4.14 < jet.eta() && jet.eta() < -1.18)
			{
				anyHcal_jets = true;
				nHCal_jets++;
				HCal_id = 1;
			}

			// bHCal
			if(-1.1 < jet.eta() && jet.eta() < 1.1)
			{
				anyHcal_jets = true;
				bHCalJet = true;
				HCal_id = 2;
			}

			// LFHCal
			if(1.2 < jet.eta() && jet.eta() < 4.2)
			{
				anyHcal_jets = true;
				HCal_id = 3;
			}


			double jet_p = sqrt(jet.pt2()+jet.pz()*jet.pz());

			h_Jet_nPart->Fill(jet.constituents().size());
			h_Jet_mass->Fill(jet.m());
		    //h_Jet_charge->Fill(jet.m());
			h_Jet_E->Fill(jet.E());
			h_Jet_p->Fill(jet_p);
			h_Jet_pT->Fill(jet.pt());
			h_Jet_eta->Fill(jet.eta());


			for (unsigned int j = i; j < inclusive_jets.size(); j++) {

				if(i==j) continue;

				fastjet::PseudoJet jet2 = inclusive_jets[j];

				h_Jet_deta->Fill(jet.eta()-jet2.eta());
			}

			vector<PseudoJet> constituents = jet.constituents();

			for (int j = 0; j < constituents.size(); ++j) {

				if(bHCalJet) h_Jet_bHCal_part_eta->Fill(constituents[j].eta());
				h_Jet_HCal_part_eta->Fill(constituents[j].eta(), HCal_id);
			}

		} // inclusive_jets

		for (unsigned int i = 0; i < measured_jets.size(); i++) {

			fastjet::PseudoJet jet = measured_jets[i];

			int HCal_meas_id = 0; // none = 0, nHCal = 1, bHCal = 2, LFHCAL = 3

			// nHCal
			if(-4.14 < jet.eta() && jet.eta() < -1.18)
			{
				anyHcal_jets_meas = true;
				nHCal_jets_meas++;
				HCal_meas_id = 1;
			}

			// bHCal
			if(-1.1 < jet.eta() && jet.eta() < 1.1)
			{
				anyHcal_jets_meas = true;
				bHCalJet_meas = true;
				HCal_meas_id = 2;
			}

			// LFHCal
			if(1.2 < jet.eta() && jet.eta() < 4.2)
			{
				anyHcal_jets_meas = true;
				HCal_meas_id = 3;
			}

		double jet_p = sqrt(jet.pt2()+jet.pz()*jet.pz());

		h_Jet_meas_nPart->Fill(jet.constituents().size());
		h_Jet_meas_mass->Fill(jet.m());
	    //h_Jet_meas_charge->Fill(jet.m());
		h_Jet_meas_E->Fill(jet.E());
		h_Jet_meas_p->Fill(jet_p);
		h_Jet_meas_pT->Fill(jet.pt());
		h_Jet_meas_eta->Fill(jet.eta());

		for (unsigned int j = i; j < measured_jets.size(); j++) {

			if(i==j) continue;

			fastjet::PseudoJet jet2 = measured_jets[j];

			h_Jet_meas_deta->Fill(jet.eta()-jet2.eta());
		}


		vector<PseudoJet> measured_constituents = jet.constituents();

		for (int j = 0; j < measured_constituents.size(); ++j) {

			if(bHCalJet) h_Jet_meas_bHCal_part_eta->Fill(measured_constituents[j].eta());
			h_Jet_meas_HCal_part_eta->Fill(measured_constituents[j].eta(), HCal_meas_id);
		}
	} // meas_jets




		for (unsigned int i = 0; i < measured_jets_nHCal.size(); i++) {

			fastjet::PseudoJet jet = measured_jets_nHCal[i];

			int HCal_meas_id = 0; // none = 0, nHCal = 1, bHCal = 2, LFHCAL = 3
/*
			// nHCal
			if(-4.14 < jet.eta() && jet.eta() < -1.18)
			{
				anyHcal_jets_meas = true;
				nHCal_jets_meas++;
				HCal_meas_id = 1;
			}

			// bHCal
			if(-1.1 < jet.eta() && jet.eta() < 1.1)
			{
				anyHcal_jets_meas = true;
				bHCalJet_meas = true;
				HCal_meas_id = 2;
			}

			// LFHCal
			if(1.2 < jet.eta() && jet.eta() < 4.2)
			{
				anyHcal_jets_meas = true;
				HCal_meas_id = 3;
			}*/

		double jet_p = sqrt(jet.pt2()+jet.pz()*jet.pz());

		h_Jet_meas_nHCal_nPart->Fill(jet.constituents().size());
		h_Jet_meas_nHCal_mass->Fill(jet.m());
	    //h_Jet_meas_nHCal_charge->Fill(jet.m());
		h_Jet_meas_nHCal_E->Fill(jet.E());
		h_Jet_meas_nHCal_p->Fill(jet_p);
		h_Jet_meas_nHCal_pT->Fill(jet.pt());
		h_Jet_meas_nHCal_eta->Fill(jet.eta());

		for (unsigned int j = i; j < measured_jets_nHCal.size(); j++) {

			if(i==j) continue;

			fastjet::PseudoJet jet2 = measured_jets_nHCal[j];

			h_Jet_meas_nHCal_deta->Fill(jet.eta()-jet2.eta());
		}


		vector<PseudoJet> measured_constituents = jet.constituents();

		for (int j = 0; j < measured_constituents.size(); ++j) {

			if(bHCalJet) h_Jet_meas_bHCal_part_eta->Fill(measured_constituents[j].eta());
			h_Jet_meas_HCal_part_eta->Fill(measured_constituents[j].eta(), HCal_meas_id);
		}
	} // meas_jets_nHCal



	for (unsigned int i = 0; i < measured_jets_no_nHCal.size(); i++) {

		fastjet::PseudoJet jet = measured_jets_no_nHCal[i];

		//int HCal_meas_id = 0; // none = 0, nHCal = 1, bHCal = 2, LFHCAL = 3
/*
		// nHCal
		if(-4.14 < jet.eta() && jet.eta() < -1.18)
		{
			anyHcal_jets_meas = true;
			nHCal_jets_meas++;
			HCal_meas_id = 1;
		}*/

		// bHCal
		if(-1.1 < jet.eta() && jet.eta() < 1.1)
		{
			anyHcal_jets_meas_no_nHCal = true;
			//bHCalJet_meas = true;
			//HCal_meas_id = 2;
		}

		// LFHCal
		if(1.2 < jet.eta() && jet.eta() < 4.2)
		{
			anyHcal_jets_meas_no_nHCal = true;
			//HCal_meas_id = 3;
		}


		double jet_p = sqrt(jet.pt2()+jet.pz()*jet.pz());

		h_Jet_meas_no_nHCal_nPart->Fill(jet.constituents().size());
		h_Jet_meas_no_nHCal_mass->Fill(jet.m());
	    //h_Jet_meas_no_nHCal_charge->Fill(jet.m());
		h_Jet_meas_no_nHCal_E->Fill(jet.E());
		h_Jet_meas_no_nHCal_p->Fill(jet_p);
		h_Jet_meas_no_nHCal_pT->Fill(jet.pt());
		h_Jet_meas_no_nHCal_eta->Fill(jet.eta());

	} // measured_jets_no_nHCal




	// jets ------------------

	if(inclusive_jets.size() >= 2)
	{

		fastjet::PseudoJet jet1 = inclusive_jets[0];
		fastjet::PseudoJet jet2 = inclusive_jets[1];

		double jet1_p = sqrt(jet1.pt2()+jet1.pz()*jet1.pz());
		double jet2_p = sqrt(jet2.pt2()+jet2.pz()*jet2.pz());

		h_Jets_eta->Fill(jet1.eta(), jet2.eta());
		h_Jets_phi->Fill(jet1.phi(), jet2.phi());
		h_Jets_p->Fill(jet1_p, jet2_p);
		h_Jets_pT->Fill(jet1.pt(), jet2.pt());
		h_Jets_E->Fill(jet1.E(), jet2.E());
	}

	if(measured_jets.size() >= 2)
	{
		h_Jets_meas_eta->Fill(measured_jets[0].eta(), measured_jets[1].eta());

		fastjet::PseudoJet jet1 = measured_jets[0];
		fastjet::PseudoJet jet2 = measured_jets[1];

		double jet1_p = sqrt(jet1.pt2()+jet1.pz()*jet1.pz());
		double jet2_p = sqrt(jet2.pt2()+jet2.pz()*jet2.pz());

		h_Jets_meas_eta->Fill(jet1.eta(), jet2.eta());
		h_Jets_meas_phi->Fill(jet1.phi(), jet2.phi());
		h_Jets_meas_p->Fill(jet1_p, jet2_p);
		h_Jets_meas_pT->Fill(jet1.pt(), jet2.pt());
		h_Jets_meas_E->Fill(jet1.E(), jet2.E());
	}

	if(measured_jets_no_nHCal.size() >= 2)
	{
		h_Jets_meas_eta->Fill(measured_jets_no_nHCal[0].eta(), measured_jets_no_nHCal[1].eta());

		fastjet::PseudoJet jet1 = measured_jets_no_nHCal[0];
		fastjet::PseudoJet jet2 = measured_jets_no_nHCal[1];

		double jet1_p = sqrt(jet1.pt2()+jet1.pz()*jet1.pz());
		double jet2_p = sqrt(jet2.pt2()+jet2.pz()*jet2.pz());

		h_Jets_meas_no_nHCal_eta->Fill(jet1.eta(), jet2.eta());
		h_Jets_meas_no_nHCal_phi->Fill(jet1.phi(), jet2.phi());
		h_Jets_meas_no_nHCal_p->Fill(jet1_p, jet2_p);
		h_Jets_meas_no_nHCal_pT->Fill(jet1.pt(), jet2.pt());
		h_Jets_meas_no_nHCal_E->Fill(jet1.E(), jet2.E());
	}



	// measured jets vs. partons

	int jetid1 = -1;
	int jetid2 = -1;

	//FindPartonJet(measured_jets, event[iParton_1], event[iParton_2], jetid1, jetid2);
/*
	if(jetid1 >= 0)
	{
		h_Jets_meas_Partons_eta->Fill(event[iParton_1].eta(), measured_jets[jetid1].eta());
		h_Jets_meas_Partons_phi->Fill(event[iParton_1].phi(), measured_jets[jetid1].phi());
		h_Jets_meas_Partons_E->Fill(event[iParton_1].e(), measured_jets[jetid1].E());

		h_Jet_meas_Parton_eta1->Fill(event[iParton_1].eta(), measured_jets[jetid1].eta());
		h_Jet_meas_Parton_phi1->Fill(event[iParton_1].phi(), measured_jets[jetid1].phi());
		h_Jet_meas_Parton_E1->Fill(event[iParton_1].e(), measured_jets[jetid1].E());
	}

	if(jetid2 >= 0)
	{
		h_Jets_meas_Partons_eta->Fill(event[iParton_2].eta(), measured_jets[jetid2].eta());
		h_Jets_meas_Partons_phi->Fill(event[iParton_2].phi(), measured_jets[jetid2].phi());
		h_Jets_meas_Partons_E->Fill(event[iParton_2].e(), measured_jets[jetid2].E());

		h_Jet_meas_Parton_eta2->Fill(event[iParton_2].eta(), measured_jets[jetid2].eta());
		h_Jet_meas_Parton_phi2->Fill(event[iParton_2].phi(), measured_jets[jetid2].phi());
		h_Jet_meas_Parton_E2->Fill(event[iParton_2].e(), measured_jets[jetid2].E());
	}
*/



	return 1;

}

// Function to create a PseudoJet from a calorimeter cluster
fastjet::PseudoJet createPseudoJet(double energy, double eta, double phi) {
    double pt = energy / std::cosh(eta); // Transverse momentum
    double px = pt * std::cos(phi);     // x-component of momentum
    double py = pt * std::sin(phi);     // y-component of momentum
    double pz = pt * std::sinh(eta);    // z-component of momentum

    return fastjet::PseudoJet(px, py, pz, energy);
}
