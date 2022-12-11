#include "MyAnalysis.h"
#include "Plotter.h"
#include <iostream>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <string>

int main() {
   
   float lumi = 50.;
   
   MyAnalysis *A = new MyAnalysis();
   TChain* ch = new TChain("events");
   ch->Add("files/data.root");
   ch->Process(A);
   
   MyAnalysis *B = new MyAnalysis();
   TChain* ch2 = new TChain("events");
   ch2->Add("files/ttbar.root");
   ch2->Process(B);
   
   MyAnalysis *C = new MyAnalysis();
   TChain* ch3 = new TChain("events");
   ch3->Add("files/wjets.root");
   ch3->Process(C);
   
   MyAnalysis *D = new MyAnalysis();
   TChain* ch4 = new TChain("events");
   ch4->Add("files/dy.root");
   ch4->Process(D);
   
   MyAnalysis *E = new MyAnalysis();
   TChain* ch5 = new TChain("events");
   ch5->Add("files/ww.root");
   ch5->Process(E);
   
   MyAnalysis *F = new MyAnalysis();
   TChain* ch6 = new TChain("events");
   ch6->Add("files/wz.root");
   ch6->Process(F);
   
   MyAnalysis *G = new MyAnalysis();
   TChain* ch7 = new TChain("events");
   ch7->Add("files/zz.root");
   ch7->Process(G);
   
   MyAnalysis *H = new MyAnalysis();
   TChain* ch8 = new TChain("events");
   ch8->Add("files/qcd.root");
   ch8->Process(H);
   
   MyAnalysis *I = new MyAnalysis();
   TChain* ch9 = new TChain("events");
   ch9->Add("files/single_top.root");
   ch9->Process(I);
   
	Plotter P;
	P.SetData(A->histograms, std::string("Data"));
	P.AddBg(B->histograms, std::string("TTbar"));
	P.AddBg(C->histograms, std::string("Wjets"));
	P.AddBg(D->histograms, std::string("DY"));
	P.AddBg(E->histograms, std::string("WW"));
	P.AddBg(F->histograms, std::string("WZ"));
	P.AddBg(G->histograms, std::string("ZZ"));
	P.AddBg(H->histograms, std::string("QCD"));
	P.AddBg(I->histograms, std::string("single Top"));
   
	P.Plot(string("results.pdf"));
   
	Plotter P_MC;
	P_MC.AddBg(B->histograms_MC, std::string("TTbar"));
	P_MC.AddBg(C->histograms_MC, std::string("Wjets"));
	P_MC.AddBg(D->histograms_MC, std::string("DY"));
	P_MC.AddBg(E->histograms_MC, std::string("WW"));
	P_MC.AddBg(F->histograms_MC, std::string("WZ"));
	P_MC.AddBg(G->histograms_MC, std::string("ZZ"));
	P_MC.AddBg(H->histograms_MC, std::string("QCD"));
	P_MC.AddBg(I->histograms_MC, std::string("single Top"));
   P_MC.Plot(string("results_MC.pdf"));
   

   TCanvas *c2 = new TCanvas("c2", "c2", 600, 600);
   TGraphAsymmErrors* h_trigg_eff = new TGraphAsymmErrors(B->h_selectedEvents_triggered_Muon1_Pt, B->h_selectedEvents_Muon1_Pt);   //hata çubukları için
   h_trigg_eff->GetXaxis()->SetTitle("Muon p_{T} [GeV]");
   h_trigg_eff->GetYaxis()->SetTitle("Trigger efficiency");
   h_trigg_eff->UseCurrentStyle();
   h_trigg_eff->Draw("AP");
   c2->Print("Trigger_eff.pdf");


   //TCanvas *c3 = new TCanvas("c3", "c3", 600, 600);
   //h_Mbqqb_mc = new h_Mbqqb_mc((hadB + hadWq + hadWqb).M(), EventWeight);
   //h_Mbqqb_mc->GetXaxis()->SetTitle("Leptonic Top Quark Mass");
   //h_Mbqqb_mc->GetYaxis()->SetTitle("m{leptonic top MC }")
   //h_Mbqqb_mc->UseCurrentStyle();
   //h_Mbqqb_mc->Draw("AP");
   //h_Mbqqb_mc->Print("Leptonictopquarkmasswithgausfit.pdf");


   //TCanvas *c4 = new TCanvas("c4", "c4", 600, 600);
   //h_Mbln_mc = new h_Mbln_mc((lepB + lepWl + lepWn).M(), EventWeight);
   //h_Mbln_mc->GetXaxis()->SetTitle("Hadronic Top Quark Mass");
   //h_Mbln_mc->GetYaxis()->SetTitle("m{hadronic top MC}");
   //h_Mbln_mc->UseCurrentStyle();
   //h_Mbln_mc->Draw("AP");
   //h_Mbln_mc->Print("Hadronictopquarkmasswithgausfit.pdf");




   //cross section hesabı

   // Acceptance (MC)

   cout << "Monte Carlo:" << endl;  //MC verileri yazdıırldı
   cout << "Signal Number of generated events: " << B->GeneratedEvents << endl;
   cout << "Signal Number of selected events: " << B->SelectedEvents << endl;
   cout << "Signal Number of selected and triggered events: " << B->SelectedEvents_triggered << endl;
   cout << endl;
   double acc = B->SelectedEvents / B->GeneratedEvents;
   cout << "Signal Acceptance: " << acc << endl;
   double trigg_eff = B->SelectedEvents_triggered / B->SelectedEvents;
   cout << "Trigger efficiency:" << trigg_eff << endl;
   cout << endl;
   double N_bg = C->SelectedEvents_triggered + D->SelectedEvents_triggered + E->SelectedEvents_triggered + F->SelectedEvents_triggered + G->SelectedEvents_triggered + H->SelectedEvents_triggered + I->SelectedEvents_triggered;
   cout << "Background Number of selected and triggered events:" << N_bg << endl;
   double purity = B->SelectedEvents_triggered / (B->SelectedEvents_triggered + N_bg);  //sinyal/sinyal+BC
   cout << "Purity:" << purity << endl;
   cout << endl;
   cout << "Data:" << endl; //Buraya kadar MC verisi
   cout << "Number of selected and triggered events: " << A->SelectedEvents_triggered << endl;
   double N_bgSub = A->SelectedEvents_triggered - A->SelectedEvents_triggered * (1. - purity);
   cout << "Number of selected and triggered events (bg subtracted): " << N_bgSub << endl;
   double N_corr = N_bgSub / acc / trigg_eff;
   cout << "Acceptance and trigg efficiency corrected yield: " << N_corr << endl;
   cout << "Cross section [pb]: " << N_corr / lumi << endl;                             //Dataya ait cross section verisi
   cout << "-----------------------------------------------" << endl;


//semileptonic vs vs rapora ekkenecek

}   


