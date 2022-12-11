#define MyAnalysis_cxx
// The class definition in MyAnalysis.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("MyAnalysis.C")
// Root > T->Process("MyAnalysis.C","some options")
// Root > T->Process("MyAnalysis.C+")
//

#include "MyAnalysis.h"
#include <iostream>
#include <TH1F.h>
#include <TLatex.h>

using namespace std;

void MyAnalysis::BuildEvent() {
   
   Muons.clear();
   for (int i = 0; i < NMuon; ++i) {
      MyMuon muon(Muon_Px[i], Muon_Py[i], Muon_Pz[i], Muon_E[i]);
      muon.SetIsolation(Muon_Iso[i]);
      muon.SetCharge(Muon_Charge[i]);
      Muons.push_back(muon);
   }
   
   Electrons.clear();
   for (int i = 0; i < NElectron; ++i) {
      MyElectron electron(Electron_Px[i], Electron_Py[i], Electron_Pz[i], Electron_E[i]);
      electron.SetIsolation(Electron_Iso[i]);
      electron.SetCharge(Electron_Charge[i]);
      Electrons.push_back(electron);
   }
   
   Photons.clear();
   for (int i = 0; i < NPhoton; ++i) {
      MyPhoton photon(Photon_Px[i], Photon_Py[i], Photon_Pz[i], Photon_E[i]);
      photon.SetIsolation(Photon_Iso[i]);
      Photons.push_back(photon);
   }
   
   Jets.clear();
   for (int i = 0; i < NJet; ++i) {
      MyJet jet(Jet_Px[i], Jet_Py[i], Jet_Pz[i], Jet_E[i]);
      jet.SetBTagDiscriminator(Jet_btag[i]);
      jet.SetJetID(Jet_ID[i]);
      Jets.push_back(jet);
   }
   
   hadB.SetXYZM(MChadronicBottom_px, MChadronicBottom_py, MChadronicBottom_pz, 4.8);
   lepB.SetXYZM(MCleptonicBottom_px, MCleptonicBottom_py, MCleptonicBottom_pz, 4.8);
   hadWq.SetXYZM(MChadronicWDecayQuark_px, MChadronicWDecayQuark_py, MChadronicWDecayQuark_pz, 0.0);
   hadWqb.SetXYZM(MChadronicWDecayQuarkBar_px, MChadronicWDecayQuarkBar_py, MChadronicWDecayQuarkBar_pz, 0.0);
   lepWl.SetXYZM(MClepton_px, MClepton_py, MClepton_pz, 0.0);
   lepWn.SetXYZM(MCneutrino_px, MCneutrino_py, MCneutrino_pz, 0.0);
   met.SetXYZM(MET_px, MET_py, 0., 0.);
   
   EventWeight *= weight_factor;
}   

void MyAnalysis::Begin(TTree * /*tree*/) {
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).
   
   TString option = GetOption();
   
}

void MyAnalysis::SlaveBegin(TTree * /*tree*/) {
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   
   TString option = GetOption();
   
   h_Mmumu = new TH1F("Mmumu", "Invariant di-muon mass", 60, 60, 120);
   h_Mmumu->SetXTitle("m_{#mu#mu}");
   h_Mmumu->Sumw2();
   histograms.push_back(h_Mmumu);
   histograms_MC.push_back(h_Mmumu);
   
   h_NJet = new TH1F("NJet", "Number of jets", 7, 0, 7);
   h_NJet->SetXTitle("No. Jets");
   h_NJet->Sumw2();
   histograms.push_back(h_NJet);
   histograms_MC.push_back(h_NJet);
   
   h_NBJet = new TH1F("NBJet", "Number of b-jets", 7, 0, 7);
   h_NBJet->SetXTitle("No. BJets");
   h_NBJet->Sumw2();
   histograms.push_back(h_NBJet);
   histograms_MC.push_back(h_NBJet);
   
   h_NMuon = new TH1F("NMuon", "Number of muons", 7, 0, 7);
   h_NMuon->SetXTitle("No. Muons");
   h_NMuon->Sumw2();
   histograms.push_back(h_NMuon);
   histograms_MC.push_back(h_NMuon);
   
   h_NElectron = new TH1F("NElectron", "Number of electrons", 7, 0, 7);
   h_NElectron->SetXTitle("No. Electrons");
   h_NElectron->Sumw2();
   histograms.push_back(h_NElectron);
   histograms_MC.push_back(h_NElectron);
   
   h_Jet1_Pt = new TH1F("Jet1Pt", "Pt of jet1", 50, 0, 250);
   h_Jet1_Pt->SetXTitle("p_{T,jet1} [GeV]");
   h_Jet1_Pt->Sumw2();
   histograms.push_back(h_Jet1_Pt);
   histograms_MC.push_back(h_Jet1_Pt);
   
   h_Jet2_Pt = new TH1F("Jet2Pt", "Pt of jet2", 50, 0, 250);
   h_Jet2_Pt->SetXTitle("p_{T,jet2} [GeV]");
   h_Jet2_Pt->Sumw2();
   histograms.push_back(h_Jet2_Pt);
   histograms_MC.push_back(h_Jet2_Pt);
   
   h_Jet3_Pt = new TH1F("Jet3Pt", "Pt of jet3", 50, 0, 250);
   h_Jet3_Pt->SetXTitle("p_{T,jet3} [GeV]");
   h_Jet3_Pt->Sumw2();
   histograms.push_back(h_Jet3_Pt);
   histograms_MC.push_back(h_Jet3_Pt);
   
   h_Jet1_Eta = new TH1F("Jet1Eta", "#eta of jet1", 50, -4, 4);
   h_Jet1_Eta->SetXTitle("#eta_{jet1}");
   h_Jet1_Eta->Sumw2();
   histograms.push_back(h_Jet1_Eta);
   histograms_MC.push_back(h_Jet1_Eta);
   
   h_Jet2_Eta = new TH1F("Jet2Eta", "#eta of jet2", 50, -4, 4);
   h_Jet2_Eta->SetXTitle("#eta_{jet2}");
   h_Jet2_Eta->Sumw2();
   histograms.push_back(h_Jet2_Eta);
   histograms_MC.push_back(h_Jet2_Eta);
   
   h_Jet3_Eta = new TH1F("Jet3Eta", "#eta of jet3", 50, -4, 4);
   h_Jet3_Eta->SetXTitle("#eta_{jet3}");
   h_Jet3_Eta->Sumw2();
   histograms.push_back(h_Jet3_Eta);
   histograms_MC.push_back(h_Jet3_Eta);
   
   h_BJet1_Pt = new TH1F("BJet1Pt", "Pt of b-jet1", 50, 0, 250);
   h_BJet1_Pt->SetXTitle("p_{T, bjet1} [GeV]");
   h_BJet1_Pt->Sumw2();
   histograms.push_back(h_BJet1_Pt);
   histograms_MC.push_back(h_BJet1_Pt);
   
   h_BJet2_Pt = new TH1F("BJet2Pt", "Pt of b-jet2", 50, 0, 250);
   h_BJet2_Pt->SetXTitle("p_{T, bjet2} [GeV]");
   h_BJet2_Pt->Sumw2();
   histograms.push_back(h_BJet2_Pt);
   histograms_MC.push_back(h_BJet2_Pt);
   
   h_BJet1_Eta = new TH1F("BJet1Eta", "#eta of b-jet1", 50, -4, 4);
   h_BJet1_Eta->SetXTitle("#eta_{bjet1}");
   h_BJet1_Eta->Sumw2();
   histograms.push_back(h_BJet1_Eta);
   histograms_MC.push_back(h_BJet1_Eta);
   
   h_BJet2_Eta = new TH1F("BJet2Eta", "#eta of b-jet2", 50, -4, 4);
   h_BJet2_Eta->SetXTitle("#eta_{bjet2}");
   h_BJet2_Eta->Sumw2();
   histograms.push_back(h_BJet2_Eta);
   histograms_MC.push_back(h_BJet2_Eta);
   
   h_Muon1_Pt = new TH1F("Muon1Pt", "Pt of muon1", 50, 0, 250);
   h_Muon1_Pt->SetXTitle("p_{T, muon1} [GeV]");
   h_Muon1_Pt->Sumw2();
   histograms.push_back(h_Muon1_Pt);
   histograms_MC.push_back(h_Muon1_Pt);
   
   h_Muon2_Pt = new TH1F("Muon2Pt", "Pt of muon2", 50, 0, 250);
   h_Muon2_Pt->SetXTitle("p_{T, muon2} [GeV]");
   h_Muon2_Pt->Sumw2();
   histograms.push_back(h_Muon2_Pt);
   histograms_MC.push_back(h_Muon2_Pt);
   
   h_Muon1_Eta = new TH1F("Muon1Eta", "#eta of muon1", 50, -4, 4);
   h_Muon1_Eta->SetXTitle("#eta_{muon1}");
   h_Muon1_Eta->Sumw2();
   histograms.push_back(h_Muon1_Eta);
   histograms_MC.push_back(h_Muon1_Eta);
   
   h_Muon2_Eta = new TH1F("Muon2Eta", "#eta of muon2", 50, -4, 4);
   h_Muon2_Eta->SetXTitle("#eta_{muon2}");
   h_Muon2_Eta->Sumw2();
   histograms.push_back(h_Muon2_Eta);
   histograms_MC.push_back(h_Muon2_Eta);
   
   h_Muon1_Iso = new TH1F("Muon1Iso", "Isolation of muon1", 50, 0, 25);
   h_Muon1_Iso->SetXTitle("Muon1 Isolation [GeV]");
   h_Muon1_Iso->Sumw2();
   histograms.push_back(h_Muon1_Iso);
   histograms_MC.push_back(h_Muon1_Iso);
   
   h_Muon2_Iso = new TH1F("Muon2Iso", "Isolation of muon2", 50, 0, 25);
   h_Muon2_Iso->SetXTitle("Muon2 Isolation [GeV]");
   h_Muon2_Iso->Sumw2();
   histograms.push_back(h_Muon2_Iso);
   histograms_MC.push_back(h_Muon2_Iso);
   
   h_Electron1_Pt = new TH1F("Electron1Pt", "Pt of electron1", 50, 0, 250);
   h_Electron1_Pt->SetXTitle("p_{T, electron1} [GeV]");
   h_Electron1_Pt->Sumw2();
   histograms.push_back(h_Electron1_Pt);
   histograms_MC.push_back(h_Electron1_Pt);
      
   h_Electron1_Eta = new TH1F("Electron1Eta", "#eta of electronn1", 50, -4, 4);
   h_Electron1_Eta->SetXTitle("#eta_{electron1}");
   h_Electron1_Eta->Sumw2();
   histograms.push_back(h_Electron1_Eta);
   histograms_MC.push_back(h_Electron1_Eta);

   h_MET = new TH1F("MET", "MET", 30, 0, 300.);
   h_MET->SetXTitle("MET [GeV]");
   h_MET->Sumw2();
   histograms.push_back(h_MET);
   histograms_MC.push_back(h_MET);
   
   h_selectedEvents_Muon1_Pt = new TH1F("selectedEvents_Muon1_Pt", "Pt of muon1 (selected)", 40, 0, 200);
   h_selectedEvents_Muon1_Pt->SetXTitle("p_{T, selected} [GeV]");
   h_selectedEvents_Muon1_Pt->Sumw2();
   histograms.push_back(h_selectedEvents_Muon1_Pt);
   histograms_MC.push_back(h_selectedEvents_Muon1_Pt);
   
   h_selectedEvents_triggered_Muon1_Pt = new TH1F("selectedEvents_triggered_Muon1_Pt",
                                                  "Pt of muon1 (selected and triggered)", 40, 0, 200);
   h_selectedEvents_triggered_Muon1_Pt->SetXTitle("p_{T, triggered} [GeV]");
   h_selectedEvents_triggered_Muon1_Pt->Sumw2();
   histograms.push_back(h_selectedEvents_triggered_Muon1_Pt);
   histograms_MC.push_back(h_selectedEvents_triggered_Muon1_Pt);
   
   h_Mbqqb_mc = new TH1F("Mbqqb_mc", "Invariant hadronic top mass (MC)", 50, 170, 175);
   h_Mbqqb_mc->SetXTitle("m_{hadronic top, MC} [GeV]");
   h_Mbqqb_mc->Sumw2();
   histograms_MC.push_back(h_Mbqqb_mc);
   
   h_Mbln_mc = new TH1F("Mbln_mc", "Invariant leptonic top mass (MC)", 50, 170, 175);
   h_Mbln_mc->SetXTitle("m_{leptonic top, MC} [GeV]");
   h_Mbln_mc->Sumw2();
   histograms_MC.push_back(h_Mbln_mc);
   
   h_Mbqqb_reco = new TH1F("Mbqqb_reco", "Invariant hadronic top mass", 50, 0, 500);
   h_Mbqqb_reco->SetXTitle("m_{hadronic top, RECO} [GeV]");
   h_Mbqqb_reco->Sumw2();
   histograms.push_back(h_Mbqqb_reco);
   histograms_MC.push_back(h_Mbqqb_reco);
   
   h_Mbln_reco = new TH1F("Mbln_reco", "Invariant transverse leptonic top mass", 50, 0, 500);
   h_Mbln_reco->SetXTitle("m_{T, leptonic top, RECO} [GeV]");
   h_Mbln_reco->Sumw2();
   histograms.push_back(h_Mbln_reco);
   histograms_MC.push_back(h_Mbln_reco);
   
   h_nPV = new TH1F("h_nPV", "number of primary vertices", 25, 0, 25);
	h_nPV->SetXTitle("No. PV");
	h_nPV->Sumw2();
	histograms.push_back(h_nPV);
	histograms_MC.push_back(h_nPV);
   
}

Bool_t MyAnalysis::Process(Long64_t entry) {
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either MyAnalysis::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
   
   ++TotalEvents;
   
   GetEntry(entry);
   
   if (TotalEvents % 10000 == 0)
      cout << "Next event -----> " << TotalEvents << endl;
   
   BuildEvent();
   

   //Muon cut'ları
   double MuonPtCut = 25.;
   double MuonRelIsoCut = 0.10;
   
   //   cout << "Jets: " << endl;
   //   for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
   //      cout << "pt, eta, phi, btag, id: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", " << it->IsBTagged() << ", " << it->GetJetID()
   //      << endl;
   //   }
   //   cout << "Muons: " << endl;
   //   for (vector<MyMuon>::iterator it = Muons.begin(); it != Muons.end(); ++it) {
   //      cout << "pt, eta, phi, iso, charge: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", "
   //      << it->GetIsolation() << ", " << it->GetCharge() << endl;
   //   }
   //   cout << "Electrons: " << endl;
   //   for (vector<MyElectron>::iterator it = Electrons.begin(); it != Electrons.end(); ++it) {
   //      cout << "pt, eta, phi, iso, charge: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", "
   //      << it->GetIsolation() << ", " << it->GetCharge() << endl;
   //   }
   //   cout << "Photons: " << endl;
   //   for (vector<MyPhoton>::iterator it = Photons.begin(); it != Photons.end(); ++it) {
   //      cout << "pt, eta, phi, iso: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", " << it->GetIsolation()
   //      << endl;
   //   }
   
   
 
   // Exercise 1

   //Invariant Di-Muon mass
   
   int N_IsoMuon = 0;            //isole edilmiş muon sayısı tanımlandı
   MyMuon *muon1, *muon2;        //muon1 ve muon 2 tanımlandı
   
   
   for (vector<MyMuon>::iterator jt = Muons.begin(); jt != Muons.end(); ++jt) {     //Tüm muonların taranması
      if (jt->IsIsolated(MuonRelIsoCut)) {                                          //Yukarıda tanımlanan cutlara (0.10) eşdeğerse 1 arttır
         ++N_IsoMuon;
         if (N_IsoMuon == 1) muon1 = &(*jt);
         if (N_IsoMuon == 2) muon2 = &(*jt);
      }
   }
   
   h_NMuon->Fill(N_IsoMuon, EventWeight);
   
   if (N_IsoMuon > 1 && triggerIsoMu24) {
      if (muon1->Pt()>MuonPtCut) {
         h_Mmumu->Fill((*muon1 + *muon2).M(), EventWeight);
      }
   }
   
   
   
   // Exercise 2

   //MC / data 
   
   int N_BJet = 0;
   for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {          //jetlerin başlangıç ve bitiş değeri aynı değilse aynı olana kadar arttırır.
      if (it->IsBTagged()) {                                                          //IsVTagged=jetin b kuarktan oluşup oluşmadığı
         ++N_BJet;
      }
   }
   
   int N_Jet = 0;
   int N_BJet_tmp = 0;     //geçici b jet

   //En az bir Isolated muon counter
   
   
   if (triggerIsoMu24 && N_IsoMuon>0) {
      if (muon1->Pt()>MuonPtCut) {
         
         h_nPV->Fill(NPrimaryVertices, EventWeight);
         
         for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
            if (!(it->GetJetID())) continue;
            ++N_Jet;
            if (N_Jet == 1) {
               h_Jet1_Pt->Fill(it->Pt(), EventWeight);
               h_Jet1_Eta->Fill(it->Eta(), EventWeight);
            } else if (N_Jet == 2) {
               h_Jet2_Pt->Fill(it->Pt(), EventWeight);
               h_Jet2_Eta->Fill(it->Eta(), EventWeight);
            } else if (N_Jet == 3) {
               h_Jet3_Pt->Fill(it->Pt(), EventWeight);
               h_Jet3_Eta->Fill(it->Eta(), EventWeight);
            }
            if (it->IsBTagged()) {                                           
               ++N_BJet_tmp;
               if (N_BJet_tmp == 1) {
                  h_BJet1_Pt->Fill(it->Pt(), EventWeight*SF_b);              //SF_b muon-jet verilerinden, jetlerin pt değeri için bir fonksiyon(scale factor)
                  h_BJet1_Eta->Fill(it->Eta(), EventWeight*SF_b);            //b jetler datadan alınmadığı için scale factor ile çarpılıyor
               } else if (N_BJet_tmp == 2) {
                  h_BJet2_Pt->Fill(it->Pt(), EventWeight*SF_b*SF_b);
                  h_BJet2_Eta->Fill(it->Eta(), EventWeight*SF_b*SF_b);
               }
            }
         }

         h_NBJet->Fill(N_BJet, EventWeight*pow(SF_b,N_BJet));
         h_NJet->Fill(N_Jet, EventWeight);
         


         //Isolated muon counter

         int N_IsoMuon_counter = 0;
         for (vector<MyMuon>::iterator jt = Muons.begin(); jt != Muons.end(); ++jt) {
            if (jt->IsIsolated(MuonRelIsoCut)) {
               ++N_IsoMuon_counter;
               if (N_IsoMuon_counter == 1) {
                  h_Muon1_Pt->Fill(jt->Pt(), EventWeight);
                  h_Muon1_Eta->Fill(jt->Eta(), EventWeight);
                  h_Muon1_Iso->Fill(jt->GetIsolation(), EventWeight);
               } else if (N_IsoMuon_counter == 2) {
                  h_Muon2_Pt->Fill(jt->Pt(), EventWeight);
                  h_Muon2_Eta->Fill(jt->Eta(), EventWeight);
                  h_Muon2_Iso->Fill(jt->GetIsolation(), EventWeight);
               }
            }
         }


         //Isolated electron counter


         int N_IsoElectron_counter = 0;
         for (vector<MyElectron>::iterator it = Electrons.begin(); it != Electrons.end(); ++it) {
            if ((it->GetIsolation()/it->Pt()) < MuonRelIsoCut) {
               ++N_IsoMuon_counter;
            }
            if (N_IsoMuon_counter == 1) {
               h_Electron1_Pt->Fill(it->Pt(), EventWeight);
               h_Electron1_Eta->Fill(it->Eta(), EventWeight);
            }
         }
         h_NElectron->Fill(N_IsoElectron_counter, EventWeight);

         
         h_MET->Fill(met.Pt(), EventWeight);                        //missing transverse energy-datadan alındığı gibi fill
         
         }
   } 
  


   // Exercise 3

   //Trigger
   

   if (Muons.size() == 1) {
      if (Muons.at(0).IsIsolated(MuonRelIsoCut)) {
         h_selectedEvents_Muon1_Pt->Fill(Muons.at(0).Pt(), EventWeight);
         if (triggerIsoMu24)
            h_selectedEvents_triggered_Muon1_Pt->Fill(Muons.at(0).Pt(), EventWeight);
      }
   }

   //Acceptance Efficiency    selected events/triggered selected events
 
   GeneratedEvents += EventWeight;
   bool IsSelected = false;
   if (N_IsoMuon == 1) {
      if (muon1->Pt()>MuonPtCut) {
         
         int NBJet = 0;
         for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
            if (it->IsBTagged()) {
               ++NBJet;
            }
         }
         if (NBJet > 1) {
            SelectedEvents += EventWeight*SF_b*SF_b;
            if (triggerIsoMu24) {
               SelectedEvents_triggered += EventWeight*SF_b*SF_b;
               IsSelected = true;
            }
         }
         
      }
   }
 
   // Exercixe 4

   //W'nun parçacıklara bozunumu ve jetlerin invariant mass'i bize top kuarkın kütlesini verir. (top quark mass -> 173 GeV)


   // Hadronik ve leptonik kanalların MC

   h_Mbqqb_mc->Fill((hadB + hadWq + hadWqb).M(), EventWeight);
   h_Mbqqb_mc->Fit("gaus");
   h_Mbln_mc->Fill((lepB + lepWl + lepWn).M(), EventWeight);
   h_Mbln_mc->Fit("gaus");
   
   // Hadronik ve leptonik reco. kanalları için top kuark mass ölçümü
   

   if (IsSelected) {
      
      // Öncelikle hadronik kanal için mass hesaplaması
      // W bosonu için b jetlerin bulunması
      //Jetlerden gelen invariant mass, W bosonunun kütlesini verir.
      // W boson mass 70 < W < 95 arasında olmasını bekliyoruz. (W bosonu mass = 80.379)


      for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {           //jetler üzerinden itterasyon başlatılır. (1. jet->it)
         if (it->IsBTagged()) {                                                           //jetlerin BTagged olup olmadığını kontrol edilir. 
            for (vector<MyJet>::iterator jt = it; jt != Jets.end(); ++jt) {               //İkinci jet kontrol edilir aynı işlemler yapılır (2. jet->jt)
               if (jt != it && !(jt->IsBTagged())) {                               
                  for (vector<MyJet>::iterator kt = jt; kt != Jets.end(); ++kt) {         //Üçüncü jet kontrol edilir aynı işlemler yapılır (3. jet->jt)
                     if (kt != it && kt != jt && !(kt->IsBTagged())) {
                        if (((*jt) + (*kt)).M() > 70 && ((*jt) + (*kt)).M() < 95){        //3 jetin kütlesinin kombinasyonu

                           h_Mbqqb_reco->Fill(((*it) + (*jt) + (*kt)).M(), EventWeight);  //hadronik decay için W bosonu kütlesi hesaplama
                        }
                     }
                  }
               }
            }
         }
      }
      
      // Leptonik kanal için mass hesaplaması


      // Müon ile missing energy (nötrino) birleştirilir. 
      // Missing Energy'nin hesaplamlarda sadece px ve py bileşini var. Bu yüzden z bileşenini W bosonunun kütlesinden yola çıkarak hesaplıyoruz.
      
      for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
         if (it->IsBTagged()) {
            double px = met.Px();                                                                                              //nötrino(missing energy) x bileşeni
            double py = met.Py();                                                                                              //nötrino(missing energy)y bileşeni
            double mW = 80.379;                                                                                                //W bosonu gerçek kütlesi
            double A = pow(mW, 2) / 2. + (muon1->Px() * px + muon1->Py() * py);                                                //missing energy z bileşeni hesaplaması
            double F = (2 * A * (muon1->Pz()))/pow(muon1->Px(), 2) + pow(muon1->Py(), 2);
            double G = ((pow(muon1->E(), 2) * pow(met.Pt(), 2)) - pow(A, 2))/pow(muon1->Px(), 2) + pow(muon1->Py(), 2);        //Slaytta 10. denklem (jet enerji)
            double D = pow(muon1->E(), 2) * (pow(A, 2) - pow(met.Pt(), 2) * (pow(muon1->E(), 2) - pow(muon1->Pz(), 2)));
            


            if (D >= 0) {                                                               //(+) ve (-) değerler alabileceği için 
               double pz = F + sqrt(pow(F, 2));                                         //4-vektör
               double E = sqrt(px * px + py * py + pz * pz);
               TLorentzVector neutrino1(px, py, pz, E);
               h_Mbln_reco->Fill(((*it) + (*muon1) + neutrino1).M(), EventWeight);      //Parçacıkların 4-momentumlari toplanır ve oluşan vektörün kütlesi hesaplanır.
                                                                                        //ROOT’ta TLorentzVectors class'ı kullanılarak elde edilebilir.

            }
 

            //Her durumda son durum parçacıklarının 4-momentumunu bilmeliyiz.(nötrinolar için)
            //Invariant mass son durum parçacıklarının 4-momentumu ile hesaplanır.

            //Kütlesi bilinen parçacıklar için ya da görünür parçacıklara bozunduğu varsayılan yeni parçacıklar aranırken invariant mass kullanılır.

            // z bileşeni aynı zamanda W bosonu kütlesinden hesaplanabilir (2. çözüm)

            if (D > 0) {
               double pz = F-+ sqrt(pow(F, 2));
               double E = sqrt(px * px + py * py + pz * pz);
               TLorentzVector neutrino2(px, py, pz, E);
               h_Mbln_reco->Fill(((*it) + (*muon1) + neutrino2).M(), EventWeight);
            }
         }
      }
   }
   
   return kTRUE;
}

void MyAnalysis::SlaveTerminate() {
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
}

void MyAnalysis::Terminate() {
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
}