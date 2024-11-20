/*
 * DrawHistFileReco.h
 *
 *  Created on: 2 mar 2022
 *      Author: Khaless
 */

#ifndef DRAWHISTFILE_H_
#define DRAWHISTFILE_H_

#include "TString.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TFile.h"
#include "TH1.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TKey.h"
#include "TProfile.h"
#include "TGaxis.h"
#include "TList.h"

#include "HistDrawOpt.h"

bool drawFromList(TString name, TString *list, int max = 0);
bool drawFromVector(TString name, vector<TString> *vec);
int drawAny(TString dir, TString fname, TString *list, int max = 0);
int drawAny(TString dir, TString fname, vector<TString> *list);
int drawAnySubDir(TString dir, TString subdir, TString fname, TString *list, int max = 0);
int drawWithProfile(TString dir, TString fname, TString *list, int max = 0);
int drawProfile(TString dir, TString fname, TString *list, int max = 0);

Int_t padw = 800, padh = 600;

/////////////////////////////////////////////////////////////
bool drawFromList(TString name, TString *list, int max)
{

	for (int i = 0; i < max; ++i) {
		if(name == list[i]) return true;
	}
	return false;

}
/////////////////////////////////////////////////////////////
bool drawFromVector(TString name, vector<TString> *vec)
{
	int max = vec->size();

	for (int i = 0; i < max; ++i) {
		if(name == vec->at(i)) return true;
	}
	return false;

}
/////////////////////////////////////////////////////////////
int drawAny(TString dir, TString fname, TString *list, int max)
{
	//Int_t padw = 600, padh = 400;

	TFile *file = new TFile(fname, "READ");
	TIter nextkey(file->GetListOfKeys());
	TKey *key = NULL;
	gSystem->cd(dir);

	TCanvas *cnv = new TCanvas("cnv", "cnv", padw, padh);
	TCanvas *cnv_log = new TCanvas("cnv_log", "cnv_log", padw, padh);

	while (key = (TKey*)nextkey()) {

		TObject *obj = dynamic_cast<TObject*>(key->ReadObj());

		cnv->cd()->SetLogx(0);
		cnv->cd()->SetLogy(0);
		cnv->cd()->SetLogz(0);

		cnv_log->cd()->SetLogx(0);
		cnv_log->cd()->SetLogy(0);
		cnv_log->cd()->SetLogz(0);

		if(obj != NULL)
		{
			TString drawOpt = "e";
			Bool_t logScale = kTRUE;
			Bool_t logScaleX = kFALSE;
			Bool_t logScaleY = kFALSE;

			TString class_name = obj->ClassName();

			TString name = obj->GetName();
			TString name_log = "log_"+name;
			TString names[] = {name};
			TString names_log[] = {name_log};

			//cout<<name<<endl;

			if(!drawFromList(name, list, max))	continue;

			drawOpt = getHistDrawOpt(obj, logScale, logScaleX, logScaleY);

			cout<<drawOpt<<endl;

			cnv->cd();
			if(logScaleX) cnv->cd()->SetLogx();
			if(logScaleY) cnv->cd()->SetLogy();
			obj->Draw(drawOpt);
			//save(cnv, names, 0, "png");
			cnv->cd()->SaveAs(Form("%s.png", name.Data()));

			if(logScale)
			{
				if(!class_name.CompareTo("TH1D")||!class_name.CompareTo("TH1F"))	cnv_log->cd()->SetLogy();
				if(!class_name.CompareTo("TH2D")||!class_name.CompareTo("TH2F"))	cnv_log->cd()->SetLogz();
				if(logScaleX) cnv_log->cd()->SetLogx();
				if(logScaleY) cnv_log->cd()->SetLogy();
				obj->Draw(drawOpt);
				//save(cnv_log, names_log, 0, "png");
				cnv_log->cd()->SaveAs(Form("%s_log.png", name.Data()));
			}
		}
	}

	gSystem->cd("../");

	return 1;
}
/////////////////////////////////////////////////////////////
int drawAny(TString dir, TString fname, vector<TString> *list)
{
	//Int_t padw = 600, padh = 400;

	TFile *file = new TFile(fname, "READ");
	TIter nextkey(file->GetListOfKeys());
	TKey *key = NULL;
	gSystem->cd(dir);

	TCanvas *cnv = new TCanvas("cnv", "cnv", padw, padh);
	TCanvas *cnv_log = new TCanvas("cnv_log", "cnv_log", padw, padh);

	while (key = (TKey*)nextkey()) {

		TObject *obj = dynamic_cast<TObject*>(key->ReadObj());

		cnv->cd()->SetLogx(0);
		cnv->cd()->SetLogy(0);
		cnv->cd()->SetLogz(0);

		cnv_log->cd()->SetLogx(0);
		cnv_log->cd()->SetLogy(0);
		cnv_log->cd()->SetLogz(0);

		if(obj != NULL)
		{
			TString drawOpt = "e";
			Bool_t logScale = kTRUE;
			Bool_t logScaleX = kFALSE;
			Bool_t logScaleY = kFALSE;

			TString class_name = obj->ClassName();

			TString name = obj->GetName();
			TString name_log = "log_"+name;
			TString names[] = {name};
			TString names_log[] = {name_log};

			//cout<<name<<endl;

			if(!drawFromVector(name, list))	continue;

			drawOpt = getHistDrawOpt(obj, logScale, logScaleX, logScaleY);

			cout<<drawOpt<<endl;

			cnv->cd();
			if(logScaleX) cnv->cd()->SetLogx();
			if(logScaleY) cnv->cd()->SetLogy();
			obj->Draw(drawOpt);
			//save(cnv, names, 0, "png");
			cnv->cd()->SaveAs(Form("%s.png", name.Data()));

			if(logScale)
			{
				if(!class_name.CompareTo("TH1D")||!class_name.CompareTo("TH1F"))	cnv_log->cd()->SetLogy();
				if(!class_name.CompareTo("TH2D")||!class_name.CompareTo("TH2F"))	cnv_log->cd()->SetLogz();
				if(logScaleX) cnv_log->cd()->SetLogx();
				if(logScaleY) cnv_log->cd()->SetLogy();
				obj->Draw(drawOpt);
				//save(cnv_log, names_log, 0, "png");
				cnv_log->cd()->SaveAs(Form("%s_log.png", name.Data()));
			}
		}
	}

	gSystem->cd("../");

	return 1;
}
/////////////////////////////////////////////////////////////
int drawAnySubDir(TString dir, TString subdir, TString fname, TString *list, int max)
{
	//Int_t padw = 600, padh = 400;

	TFile *file = new TFile(fname, "READ");
	TList *listdir = dynamic_cast<TList*>(file->Get(subdir));
	TIter nextkey(listdir->MakeIterator());
	TKey *key = NULL;
	gSystem->cd(dir);

	TCanvas *cnv = new TCanvas("cnv", "cnv", padw, padh);
	TCanvas *cnv_log = new TCanvas("cnv_log", "cnv_log", padw, padh);

	while (key = (TKey*)nextkey()) {

		TObject *obj = dynamic_cast<TObject*>(key->ReadObj());

		cnv->cd()->SetLogx(0);
		cnv->cd()->SetLogy(0);
		cnv->cd()->SetLogz(0);

		cnv_log->cd()->SetLogx(0);
		cnv_log->cd()->SetLogy(0);
		cnv_log->cd()->SetLogz(0);

		if(obj != NULL)
		{
			TString drawOpt = "e";
			Bool_t logScale = kTRUE;
			Bool_t logScaleX = kFALSE;
			Bool_t logScaleY = kFALSE;

			TString class_name = obj->ClassName();

			TString name = obj->GetName();
			TString name_log = "log_"+name;
			TString names[] = {name};
			TString names_log[] = {name_log};

			//cout<<name<<endl;
/*
			if(name == subdir) key->cd();
			if(name != subdir) continue;*/

			//if(!drawFromList(name, list, max))	continue;

			drawOpt = getHistDrawOpt(obj, logScale, logScaleX, logScaleY);

			cout<<drawOpt<<endl;

			cnv->cd();
			if(logScaleX) cnv->cd()->SetLogx();
			if(logScaleY) cnv->cd()->SetLogy();
			obj->Draw(drawOpt);
			//save(cnv, names, 0, "png");
			cnv->cd()->SaveAs(Form("%s.png", name.Data()));

			if(logScale)
			{
				if(!class_name.CompareTo("TH1D")||!class_name.CompareTo("TH1F"))	cnv_log->cd()->SetLogy();
				if(!class_name.CompareTo("TH2D")||!class_name.CompareTo("TH2F"))	cnv_log->cd()->SetLogz();
				if(logScaleX) cnv_log->cd()->SetLogx();
				if(logScaleY) cnv_log->cd()->SetLogy();
				obj->Draw(drawOpt);
				//save(cnv_log, names_log, 0, "png");
				cnv_log->cd()->SaveAs(Form("%s_log.png", name.Data()));
			}
		}
	}

	gSystem->cd("../");

	return 1;
}
/////////////////////////////////////////////////////////////
int drawWithProfile(TString dir, TString fname, TString *list, int max)
{
	//Int_t padw = 600, padh = 400;

	TFile *file = new TFile(fname, "READ");
	TIter nextkey(file->GetListOfKeys());
	TKey *key = NULL;
	gSystem->cd(dir);

	TCanvas *cnv = new TCanvas("cnv", "cnv", padw, padh);
	TCanvas *cnv_log = new TCanvas("cnv_log", "cnv_log", padw, padh);

	while (key = (TKey*)nextkey()) {

		TObject *obj = dynamic_cast<TObject*>(key->ReadObj());

		cnv->cd()->SetLogx(0);
		cnv->cd()->SetLogy(0);
		cnv->cd()->SetLogz(0);

		cnv_log->cd()->SetLogx(0);
		cnv_log->cd()->SetLogy(0);
		cnv_log->cd()->SetLogz(0);

		if(obj != NULL)
		{
			TString drawOpt = "e";
			Bool_t logScale = kTRUE;
			Bool_t logScaleX = kFALSE;
			Bool_t logScaleY = kFALSE;

			TString class_name = obj->ClassName();

			TString name = obj->GetName();
			TString name_log = "log_"+name;
			TString names[] = {name};
			TString names_log[] = {name_log};

			if(!drawFromList(name, list, max))	continue;

			drawOpt = getHistDrawOpt(obj, logScale, logScaleX, logScaleY);

			if(!class_name.CompareTo("TProfile")) continue;

			TProfile *profile = (TProfile *)file->Get(name+"_pfx");
			profile->SetLineColor(kBlack);

			cout<<drawOpt<<endl;

			cnv->cd();
			if(logScaleX) cnv->cd()->SetLogx();
			if(logScaleY) cnv->cd()->SetLogy();
			obj->Draw(drawOpt);
			profile->Draw("samee");
			//save(cnv, names, 0, "png");
			cnv->cd()->SaveAs(Form("%s.png", name.Data()));

			if(logScale)
			{
				if(!class_name.CompareTo("TH1D")||!class_name.CompareTo("TH1F"))	cnv_log->cd()->SetLogy();
				if(!class_name.CompareTo("TH2D")||!class_name.CompareTo("TH2F"))	cnv_log->cd()->SetLogz();
				if(logScaleX) cnv_log->cd()->SetLogx();
				if(logScaleY) cnv_log->cd()->SetLogy();
				obj->Draw(drawOpt);
				profile->Draw("samee");
				//cnv_log->cd()->SaveAs();
				//save(cnv_log, names_log, 0, "png");
				cnv_log->cd()->SaveAs(Form("%s_log.png", name.Data()));
			}
		}
	}

	gSystem->cd("../");

	return 1;
}

/////////////////////////////////////////////////////////////
int drawProfile(TString dir, TString fname, TString *list, int max)
{
	//Int_t padw = 600, padh = 400;

	TFile *file = new TFile(fname, "READ");
	TIter nextkey(file->GetListOfKeys());
	TKey *key = NULL;
	gSystem->cd(dir);

	TCanvas *cnv = new TCanvas("cnv", "cnv", padw, padh);
	TCanvas *cnv_log = new TCanvas("cnv_log", "cnv_log", padw, padh);

	while (key = (TKey*)nextkey()) {

		TObject *obj = dynamic_cast<TObject*>(key->ReadObj());

		cnv->cd()->SetLogx(0);
		cnv->cd()->SetLogy(0);
		cnv->cd()->SetLogz(0);

		cnv_log->cd()->SetLogx(0);
		cnv_log->cd()->SetLogy(0);
		cnv_log->cd()->SetLogz(0);

		if(obj != NULL)
		{
			TString drawOpt = "e";
			Bool_t logScale = kTRUE;
			Bool_t logScaleX = kFALSE;
			Bool_t logScaleY = kFALSE;

			TString class_name = obj->ClassName();

			TString name = obj->GetName();
			TString name_log = "log_"+name;
			TString names[] = {name};
			TString names_log[] = {name_log};

			if(!drawFromList(name, list, max))	continue;

			drawOpt = getHistDrawOpt(obj, logScale, logScaleX, logScaleY);

			if(!class_name.CompareTo("TProfile")) continue;

			//TProfile *profile = (TProfile *)file->Get(name+"_pfx");
			//profile->SetLineColor(kBlack);

			cout<<drawOpt<<endl;

			cnv->cd();
			if(logScaleX) cnv->cd()->SetLogx();
			if(logScaleY) cnv->cd()->SetLogy();
			obj->Draw(drawOpt);
			//profile->Draw("samee");
			//save(cnv, names, 0, "png");
			cnv->cd()->SaveAs(Form("%s.png", name.Data()));

			if(logScale)
			{
				if(!class_name.CompareTo("TH1D")||!class_name.CompareTo("TH1F"))	cnv_log->cd()->SetLogy();
				if(!class_name.CompareTo("TH2D")||!class_name.CompareTo("TH2F"))	cnv_log->cd()->SetLogz();
				if(logScaleX) cnv_log->cd()->SetLogx();
				if(logScaleY) cnv_log->cd()->SetLogy();
				obj->Draw(drawOpt);
				//profile->Draw("samee");
				//cnv_log->cd()->SaveAs();
				//save(cnv_log, names_log, 0, "png");
				cnv_log->cd()->SaveAs(Form("%s_log.png", name.Data()));
			}
		}
	}

	gSystem->cd("../");

	return 1;
}


#endif /* DRAWHISTFILE_H_ */
