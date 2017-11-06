# include "TFile.h"
# include "TGraphErrors.h"
# include "TCanvas.h"
# include "TH1D.h"
# include "TH2D.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include "TStyle.h"
# include <fstream>
# include <iostream>

Bool_t close_plots = kFALSE;
Bool_t gridlines = kFALSE;

# include "style.h"

static const int ncentbins = 8;
static const double centBins[] = {0, 10, 20, 30, 40, 50, 60, 70, 80};
static const int nanals = 16;
string AnalNames[] = {
    // 0         1             2             3             4             5             6             7
    "v1SP",   "v1SP_mid",   "v1SP_102",   "v1SP_106",   "v1SP_110",   "v1SP_114",   "v1SP_118",   "v1SP_122",
    // 8         9            10            11            12            13            14            15
    "v1SPmc", "v1SPmc_mid", "v1SPmc_102", "v1SPmc_106", "v1SPmc_110", "v1SPmc_114", "v1SPmc_118", "v1SPmc_122"
};

using namespace std;

TH1D * v1p_pt[nanals][ncentbins];
TH1D * v1m_pt[nanals][ncentbins];
TH1D * v1odd_pt[nanals][ncentbins];
TH1D * v1even_pt[nanals][ncentbins];

TH1D * v112p_pt[nanals][ncentbins];
TH1D * v112m_pt[nanals][ncentbins];
TH1D * v112odd_pt[nanals][ncentbins];
TH1D * v112even_pt[nanals][ncentbins];

TH1D * v123p_pt[nanals][ncentbins];
TH1D * v123m_pt[nanals][ncentbins];
TH1D * v123odd_pt[nanals][ncentbins];
TH1D * v123even_pt[nanals][ncentbins];

TH1D * v1p_eta[nanals][ncentbins];
TH1D * v1m_eta[nanals][ncentbins];
TH1D * v1odd_eta[nanals][ncentbins];
TH1D * v1even_eta[nanals][ncentbins];

TH1D * v112p_eta[nanals][ncentbins];
TH1D * v112m_eta[nanals][ncentbins];
TH1D * v112odd_eta[nanals][ncentbins];
TH1D * v112even_eta[nanals][ncentbins];

TH1D * v123p_eta[nanals][ncentbins];
TH1D * v123m_eta[nanals][ncentbins];
TH1D * v123odd_eta[nanals][ncentbins];
TH1D * v123even_eta[nanals][ncentbins];

TH1D * runParms[nanals];

void v1plot_eta()
{

    TFile * tfinInt = new TFile("../outputs_final/v1Int.root");
    for (int i = 0; i<nanals; i++) {
        runParms[i] = (TH1D *) tfinInt->Get(Form("%s/runParms",AnalNames[i].data()));
        for (int cbin = 0; cbin<ncentbins; cbin++) {
            v1p_pt[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_pt/%d-%d/v1p_pt_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v1m_pt[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_pt/%d-%d/v1m_pt_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v1odd_pt[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_pt/%d-%d/v1odd_pt_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v1even_pt[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_pt/%d-%d/v1even_pt_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));

            v112p_pt[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_pt/%d-%d/v112p_pt_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v112m_pt[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_pt/%d-%d/v112m_pt_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v112odd_pt[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_pt/%d-%d/v112odd_pt_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v112even_pt[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_pt/%d-%d/v112even_pt_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));

            v123p_pt[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_pt/%d-%d/v123p_pt_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v123m_pt[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_pt/%d-%d/v123m_pt_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v123odd_pt[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_pt/%d-%d/v123odd_pt_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v123even_pt[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_pt/%d-%d/v123even_pt_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));

            v1p_eta[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_eta/%d-%d/v1p_eta_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v1m_eta[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_eta/%d-%d/v1m_eta_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v1odd_eta[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_eta/%d-%d/v1odd_eta_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v1even_eta[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_eta/%d-%d/v1even_eta_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));

            v112p_eta[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_eta/%d-%d/v112p_eta_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v112m_eta[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_eta/%d-%d/v112m_eta_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v112odd_eta[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_eta/%d-%d/v112odd_eta_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v112even_eta[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_eta/%d-%d/v112even_eta_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));

            v123p_eta[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_eta/%d-%d/v123p_eta_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v123m_eta[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_eta/%d-%d/v123m_eta_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v123odd_eta[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_eta/%d-%d/v123odd_eta_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));
            v123even_eta[i][cbin] = (TH1D *) tfinInt->Get(Form("%s/v1_eta/%d-%d/v123even_eta_%s_%d",AnalNames[i].data(),(int)centBins[cbin],(int)centBins[cbin+1],AnalNames[i].data(),cbin));

            v1p_pt[i][cbin]->SetMarkerColor(kRed-7);
            v1p_pt[i][cbin]->SetLineColor(kRed-7);
            v1p_pt[i][cbin]->SetMarkerStyle(21);
            v1p_pt[i][cbin]->SetMarkerSize(1.1);

            v1p_eta[i][cbin]->SetMarkerColor(kRed-7);
            v1p_eta[i][cbin]->SetLineColor(kRed-7);
            v1p_eta[i][cbin]->SetMarkerStyle(21);
            v1p_eta[i][cbin]->SetMarkerSize(1.1);

            v1m_pt[i][cbin]->SetMarkerColor(kCyan-3);
            v1m_pt[i][cbin]->SetLineColor(kCyan-3);
            v1m_pt[i][cbin]->SetMarkerStyle(21);
            v1m_pt[i][cbin]->SetMarkerSize(1.1);

            v1m_eta[i][cbin]->SetMarkerColor(kCyan-3);
            v1m_eta[i][cbin]->SetLineColor(kCyan-3);
            v1m_eta[i][cbin]->SetMarkerStyle(21);
            v1m_eta[i][cbin]->SetMarkerSize(1.1);

            v1odd_pt[i][cbin]->SetMarkerColor(kBlue);
            v1odd_pt[i][cbin]->SetLineColor(kBlue);
            v1odd_pt[i][cbin]->SetMarkerStyle(21);
            v1odd_pt[i][cbin]->SetMarkerSize(1.1);

            v1odd_eta[i][cbin]->SetMarkerColor(kBlue);
            v1odd_eta[i][cbin]->SetLineColor(kBlue);
            v1odd_eta[i][cbin]->SetMarkerStyle(21);
            v1odd_eta[i][cbin]->SetMarkerSize(1.1);

            v1even_pt[i][cbin]->SetMarkerColor(kRed);
            v1even_pt[i][cbin]->SetLineColor(kRed);
            v1even_pt[i][cbin]->SetMarkerStyle(21);
            v1even_pt[i][cbin]->SetMarkerSize(1.1);

            v1even_eta[i][cbin]->SetMarkerColor(kRed);
            v1even_eta[i][cbin]->SetLineColor(kRed);
            v1even_eta[i][cbin]->SetMarkerStyle(21);
            v1even_eta[i][cbin]->SetMarkerSize(1.1);
        }
    }

    //-- make plots

    if (!fopen("plots","r")) system("mkdir plots");

    //-- centrality dependence of v1(eta) using both the HF+ and HF-
    TCanvas * cv1HFpm_eta_scan = new TCanvas("cv1HFpm_eta_scan","cv1HFpm_eta_scan",1200,650);
    cv1HFpm_eta_scan->Divide(4,2,0,0);
    TH1D * hv1HFpm_eta_scan = new TH1D("hv1HFpm_eta_scan", "", 40, -2.6, 2.6);
    hv1HFpm_eta_scan->SetXTitle("#eta");
    hv1HFpm_eta_scan->SetYTitle("v_{1}");
    hv1HFpm_eta_scan->GetXaxis()->CenterTitle();
    hv1HFpm_eta_scan->GetYaxis()->CenterTitle();
    hv1HFpm_eta_scan->GetYaxis()->SetRangeUser(-0.175, 0.175);
    hv1HFpm_eta_scan->GetYaxis()->SetNdivisions(509);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1HFpm_eta_scan = (TPad *) cv1HFpm_eta_scan->cd(cbin+1);
        if (gridlines) padv1HFpm_eta_scan->SetGrid();
        if (cbin == 3 || cbin == 7) padv1HFpm_eta_scan->SetRightMargin(0.02);
        TH1D * hv1HFpm_eta_scan_tmp = (TH1D *) hv1HFpm_eta_scan->Clone(Form("hv1HFpm_eta_scan_%d",cbin));
        if (cbin == 4) {
            hv1HFpm_eta_scan_tmp->GetXaxis()->SetTitleSize(0.06);
            hv1HFpm_eta_scan_tmp->GetXaxis()->SetTitleOffset(1.00);
            hv1HFpm_eta_scan_tmp->GetXaxis()->SetLabelSize(0.06);
            hv1HFpm_eta_scan_tmp->GetXaxis()->SetLabelOffset(0.010);
            hv1HFpm_eta_scan_tmp->GetYaxis()->SetTitleSize(0.06);
            hv1HFpm_eta_scan_tmp->GetYaxis()->SetTitleOffset(1.50);
            hv1HFpm_eta_scan_tmp->GetYaxis()->SetLabelSize(0.06);
            hv1HFpm_eta_scan_tmp->GetYaxis()->SetLabelOffset(0.010);
        } else {
            hv1HFpm_eta_scan_tmp->GetXaxis()->SetTitleSize(0.07);
            hv1HFpm_eta_scan_tmp->GetXaxis()->SetTitleOffset(0.86);
            hv1HFpm_eta_scan_tmp->GetXaxis()->SetLabelSize(0.07);
            hv1HFpm_eta_scan_tmp->GetXaxis()->SetLabelOffset(0.005);
            hv1HFpm_eta_scan_tmp->GetYaxis()->SetTitleSize(0.07);
            hv1HFpm_eta_scan_tmp->GetYaxis()->SetTitleOffset(1.29);
            hv1HFpm_eta_scan_tmp->GetYaxis()->SetLabelSize(0.06);
            hv1HFpm_eta_scan_tmp->GetYaxis()->SetLabelOffset(0.010);
        }
        hv1HFpm_eta_scan_tmp->Draw();
        v1p_eta[7][cbin]->Draw("same");
        v1m_eta[7][cbin]->Draw("same");

        TPaveText * txv1HFpm_eta_scan;
        if (cbin == 0)             txv1HFpm_eta_scan = new TPaveText(0.76, 0.84, 0.96, 0.96,"NDC");
        if (cbin >=1 && cbin <=3 ) txv1HFpm_eta_scan = new TPaveText(0.70, 0.84, 0.92, 0.96,"NDC");
        if (cbin == 4)             txv1HFpm_eta_scan = new TPaveText(0.76, 0.85, 0.96, 0.96,"NDC");
        if (cbin >=5 && cbin <=7)  txv1HFpm_eta_scan = new TPaveText(0.70, 0.85, 0.92, 0.96,"NDC");
        SetTPaveTxt(txv1HFpm_eta_scan, 18);
        txv1HFpm_eta_scan->AddText(Form("%d-%d%%",(int)centBins[cbin],(int)centBins[cbin+1]));
        txv1HFpm_eta_scan->Draw();
    }
    cv1HFpm_eta_scan->cd(1);
    TPaveText * txv1HFpm_eta_scan_label0 = new TPaveText(0.23, 0.74, 0.72, 0.94,"NDC");
    SetTPaveTxt(txv1HFpm_eta_scan_label0, 18);
    txv1HFpm_eta_scan_label0->AddText("PbPb #sqrt{s_{NN}} = TeV");
    txv1HFpm_eta_scan_label0->AddText("0.3 < p_{T} < 3.0 (GeV/c)");
    txv1HFpm_eta_scan_label0->Draw();

    cv1HFpm_eta_scan->cd(2);
    TLegend * legv1HFpm_eta_scan = new TLegend(0.06, 0.77, 0.35, 0.95);
    SetLegend(legv1HFpm_eta_scan, 18);
    legv1HFpm_eta_scan->AddEntry(v1p_eta[7][0],"v_{1}{HF+}","p");
    legv1HFpm_eta_scan->AddEntry(v1m_eta[7][0],"v_{1}{HF-}","p");
    legv1HFpm_eta_scan->Draw();

    cv1HFpm_eta_scan->Print("plots/v1HFpm_eta_scan_122.png","png");
    if (close_plots) cv1HFpm_eta_scan->Close();



    //-- centrality dependence of v1odd(eta)
    TCanvas * cv1odd_eta_scan = new TCanvas("cv1odd_eta_scan","cv1odd_eta_scan",1200,650);
    cv1odd_eta_scan->Divide(4,2,0,0);
    TH1D * hv1odd_eta_scan = new TH1D("hv1odd_eta_scan", "", 40, -2.6, 2.6);
    hv1odd_eta_scan->SetXTitle("#eta");
    hv1odd_eta_scan->SetYTitle("v_{1}^{odd}");
    hv1odd_eta_scan->GetXaxis()->CenterTitle();
    hv1odd_eta_scan->GetYaxis()->CenterTitle();
    hv1odd_eta_scan->GetYaxis()->SetRangeUser(-0.05, 0.05);
    hv1odd_eta_scan->GetYaxis()->SetNdivisions(509);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1odd_eta_scan = (TPad *) cv1odd_eta_scan->cd(cbin+1);
        if (gridlines) padv1odd_eta_scan->SetGrid();
        if (cbin == 3 || cbin == 7) padv1odd_eta_scan->SetRightMargin(0.02);
        TH1D * hv1odd_eta_scan_tmp = (TH1D *) hv1odd_eta_scan->Clone(Form("hv1odd_eta_scan_%d",cbin));
        if (cbin == 4) {
            hv1odd_eta_scan_tmp->GetXaxis()->SetTitleSize(0.06);
            hv1odd_eta_scan_tmp->GetXaxis()->SetTitleOffset(1.00);
            hv1odd_eta_scan_tmp->GetXaxis()->SetLabelSize(0.06);
            hv1odd_eta_scan_tmp->GetXaxis()->SetLabelOffset(0.010);
            hv1odd_eta_scan_tmp->GetYaxis()->SetTitleSize(0.06);
            hv1odd_eta_scan_tmp->GetYaxis()->SetTitleOffset(1.50);
            hv1odd_eta_scan_tmp->GetYaxis()->SetLabelSize(0.06);
            hv1odd_eta_scan_tmp->GetYaxis()->SetLabelOffset(0.010);
        } else {
            hv1odd_eta_scan_tmp->GetXaxis()->SetTitleSize(0.07);
            hv1odd_eta_scan_tmp->GetXaxis()->SetTitleOffset(0.86);
            hv1odd_eta_scan_tmp->GetXaxis()->SetLabelSize(0.07);
            hv1odd_eta_scan_tmp->GetXaxis()->SetLabelOffset(0.005);
            hv1odd_eta_scan_tmp->GetYaxis()->SetTitleSize(0.07);
            hv1odd_eta_scan_tmp->GetYaxis()->SetTitleOffset(1.29);
            hv1odd_eta_scan_tmp->GetYaxis()->SetLabelSize(0.06);
            hv1odd_eta_scan_tmp->GetYaxis()->SetLabelOffset(0.010);
        }
        hv1odd_eta_scan_tmp->Draw();
        v1odd_eta[7][cbin]->Draw("same");
        v1odd_eta[6][cbin]->SetMarkerColor(kRed);
        v1odd_eta[6][cbin]->SetMarkerStyle(25);
        v1odd_eta[6][cbin]->Draw("same");
        v1odd_eta[5][cbin]->SetMarkerColor(kGreen+2);
        v1odd_eta[5][cbin]->SetMarkerStyle(24);
        v1odd_eta[5][cbin]->SetMarkerSize(1.2);
        v1odd_eta[5][cbin]->Draw("same");

        TPaveText * txv1odd_eta_scan;
        if (cbin == 0)             txv1odd_eta_scan = new TPaveText(0.76, 0.84, 0.96, 0.96,"NDC");
        if (cbin >=1 && cbin <=3 ) txv1odd_eta_scan = new TPaveText(0.70, 0.84, 0.92, 0.96,"NDC");
        if (cbin == 4)             txv1odd_eta_scan = new TPaveText(0.76, 0.85, 0.96, 0.96,"NDC");
        if (cbin >=5 && cbin <=7)  txv1odd_eta_scan = new TPaveText(0.70, 0.85, 0.92, 0.96,"NDC");
        SetTPaveTxt(txv1odd_eta_scan, 18);
        txv1odd_eta_scan->AddText(Form("%d-%d%%",(int)centBins[cbin],(int)centBins[cbin+1]));
        txv1odd_eta_scan->Draw();
    }
    cv1odd_eta_scan->cd(1);
    TPaveText * txv1odd_eta_scan_label0 = new TPaveText(0.23, 0.74, 0.72, 0.94,"NDC");
    SetTPaveTxt(txv1odd_eta_scan_label0, 18);
    txv1odd_eta_scan_label0->AddText("PbPb #sqrt{s_{NN}} = TeV");
    txv1odd_eta_scan_label0->AddText("0.3 < p_{T} < 3.0 (GeV/c)");
    txv1odd_eta_scan_label0->Draw();

    cv1odd_eta_scan->cd(2);
    TLegend * legv1odd_eta_scan = new TLegend(0.06, 0.67, 0.35, 0.94);
    SetLegend(legv1odd_eta_scan, 18);
    legv1odd_eta_scan->AddEntry(v1odd_eta[7][1],"2.0 < |#eta| < 2.4","p");
    legv1odd_eta_scan->AddEntry(v1odd_eta[6][1],"1.6 < |#eta| < 2.0","p");
    legv1odd_eta_scan->AddEntry(v1odd_eta[5][1],"1.2 < |#eta| < 1.6","p");
    legv1odd_eta_scan->Draw();

    cv1odd_eta_scan->Print("plots/v1odd_eta_scan_122.png","png");
    if (close_plots) cv1odd_eta_scan->Close();



    //-- centrality dependence of HF+ - HF- (eta)
    TCanvas * cv1HFeven_eta_scan = new TCanvas("cv1HFeven_eta_scan","cv1HFeven_eta_scan",1200,650);
    cv1HFeven_eta_scan->Divide(4,2,0,0);
    TH1D * hv1HFeven_eta_scan = new TH1D("hv1HFeven_eta_scan", "", 40, -2.6, 2.6);
    hv1HFeven_eta_scan->SetXTitle("#eta");
    hv1HFeven_eta_scan->SetYTitle("(v_{1}{HF+} - v_{1}{HF-})/2");
    hv1HFeven_eta_scan->GetXaxis()->CenterTitle();
    hv1HFeven_eta_scan->GetYaxis()->CenterTitle();
    hv1HFeven_eta_scan->GetYaxis()->SetRangeUser(-0.12, 0.06);
    hv1HFeven_eta_scan->GetYaxis()->SetNdivisions(509);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1HFeven_eta_scan = (TPad *) cv1HFeven_eta_scan->cd(cbin+1);
        if (gridlines) padv1HFeven_eta_scan->SetGrid();
        if (cbin == 3 || cbin == 7) padv1HFeven_eta_scan->SetRightMargin(0.02);
        TH1D * hv1HFeven_eta_scan_tmp = (TH1D *) hv1HFeven_eta_scan->Clone(Form("hv1HFeven_eta_scan_%d",cbin));
        if (cbin == 4) {
            hv1HFeven_eta_scan_tmp->GetXaxis()->SetTitleSize(0.06);
            hv1HFeven_eta_scan_tmp->GetXaxis()->SetTitleOffset(1.00);
            hv1HFeven_eta_scan_tmp->GetXaxis()->SetLabelSize(0.06);
            hv1HFeven_eta_scan_tmp->GetXaxis()->SetLabelOffset(0.010);
            hv1HFeven_eta_scan_tmp->GetYaxis()->SetTitleSize(0.06);
            hv1HFeven_eta_scan_tmp->GetYaxis()->SetTitleOffset(1.50);
            hv1HFeven_eta_scan_tmp->GetYaxis()->SetLabelSize(0.06);
            hv1HFeven_eta_scan_tmp->GetYaxis()->SetLabelOffset(0.010);
        } else {
            hv1HFeven_eta_scan_tmp->GetXaxis()->SetTitleSize(0.07);
            hv1HFeven_eta_scan_tmp->GetXaxis()->SetTitleOffset(0.86);
            hv1HFeven_eta_scan_tmp->GetXaxis()->SetLabelSize(0.07);
            hv1HFeven_eta_scan_tmp->GetXaxis()->SetLabelOffset(0.005);
            hv1HFeven_eta_scan_tmp->GetYaxis()->SetTitleSize(0.07);
            hv1HFeven_eta_scan_tmp->GetYaxis()->SetTitleOffset(1.29);
            hv1HFeven_eta_scan_tmp->GetYaxis()->SetLabelSize(0.06);
            hv1HFeven_eta_scan_tmp->GetYaxis()->SetLabelOffset(0.010);
        }
        hv1HFeven_eta_scan_tmp->Draw();
        v1even_eta[7][cbin]->Draw("same");

        TPaveText * txv1HFeven_eta_scan;
        if (cbin == 0)             txv1HFeven_eta_scan = new TPaveText(0.76, 0.84, 0.96, 0.96,"NDC");
        if (cbin >=1 && cbin <=3 ) txv1HFeven_eta_scan = new TPaveText(0.70, 0.84, 0.92, 0.96,"NDC");
        if (cbin == 4)             txv1HFeven_eta_scan = new TPaveText(0.76, 0.85, 0.96, 0.96,"NDC");
        if (cbin >=5 && cbin <=7)  txv1HFeven_eta_scan = new TPaveText(0.70, 0.85, 0.92, 0.96,"NDC");
        SetTPaveTxt(txv1HFeven_eta_scan, 18);
        txv1HFeven_eta_scan->AddText(Form("%d-%d%%",(int)centBins[cbin],(int)centBins[cbin+1]));
        txv1HFeven_eta_scan->Draw();
    }
    cv1HFeven_eta_scan->cd(1);
    TPaveText * txv1HFeven_eta_scan_label0 = new TPaveText(0.23, 0.74, 0.72, 0.94,"NDC");
    SetTPaveTxt(txv1HFeven_eta_scan_label0, 18);
    txv1HFeven_eta_scan_label0->AddText("PbPb #sqrt{s_{NN}} = TeV");
    txv1HFeven_eta_scan_label0->AddText("0.3 < p_{T} < 3.0 (GeV/c)");
    txv1HFeven_eta_scan_label0->Draw();

    cv1HFeven_eta_scan->Print("plots/v1HFeven_eta_scan_122.png","png");
    if (close_plots) cv1HFeven_eta_scan->Close();



}
