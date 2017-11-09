# include "TFile.h"
# include "TGraphErrors.h"
# include "TCanvas.h"
# include "TF1.h"
# include "TH1.h"
# include "TH2.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include "TStyle.h"
# include <fstream>
# include <iostream>

Bool_t close_plots = kFALSE;
Bool_t gridlines = kFALSE;

# include "style.h"

static const int nptbins = 18;
static const double ptbins[] = {0.30,  0.40,  0.50,  0.60,  0.80,  1.00,  1.25,  1.50,  2.00,  2.50,  3.00,
                     3.50,  4.00,  5.00,  6.00,  7.00,  8.00,  10.00,  12.00};
static const int netabins = 12;
static const double etabins[] = {-2.4, -2.0, -1.6, -1.2, -0.8, -0.4,  0.0,
                     0.4,  0.8,  1.2,  1.6,  2.0,  2.4};
static const int nratbins = 6;
static const double ratbins[] = {0.0,  0.4,  0.8,  1.2,  1.6,  2.0,  2.4};
static const int ncentbins = 8;
static const int centBins[] = {0, 10, 20, 30, 40, 50, 60, 70, 80};
static const int nanals = 16;
string AnalNames[] = {
  // 0         1             2             3             4             5             6             7
  "v1SP",   "v1SP_mid",   "v1SP_102",   "v1SP_106",   "v1SP_110",   "v1SP_114",   "v1SP_118",   "v1SP_122",
  // 8         9            10            11            12            13            14            15
  "v1SPmc", "v1SPmc_mid", "v1SPmc_102", "v1SPmc_106", "v1SPmc_110", "v1SPmc_114", "v1SPmc_118", "v1SPmc_122"
};

using namespace std;

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

TH1D * ratiov1odd_eta[nanals][ncentbins];
TH1D * ratiov1even_eta[nanals][ncentbins];

TH1D * runParms[nanals];

void intV1_eta()
{

    TH1::SetDefaultSumw2();

    TFile * tfin = new TFile("../outputs/final_outputs/v1Int.root");

    //-- retrieve histograms from final output file
    for (int i = 0; i<nanals; i++) {
        for (int cbin = 0; cbin<ncentbins; cbin++) {
            v1p_eta[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_eta/%d-%d/v1p_eta_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v1m_eta[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_eta/%d-%d/v1m_eta_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v1odd_eta[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_eta/%d-%d/v1odd_eta_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v1even_eta[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_eta/%d-%d/v1even_eta_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));

            v112p_eta[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_eta/%d-%d/v112p_eta_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v112m_eta[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_eta/%d-%d/v112m_eta_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v112odd_eta[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_eta/%d-%d/v112odd_eta_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v112even_eta[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_eta/%d-%d/v112even_eta_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));

            v123p_eta[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_eta/%d-%d/v123p_eta_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v123m_eta[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_eta/%d-%d/v123m_eta_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v123odd_eta[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_eta/%d-%d/v123odd_eta_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v123even_eta[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_eta/%d-%d/v123even_eta_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));

            ratiov1odd_eta[i][cbin] = new TH1D(Form("ratiov1odd_eta_%s_%d",AnalNames[i].data(),cbin), "", nratbins, ratbins);
            ratiov1even_eta[i][cbin] = new TH1D(Form("ratiov1even_eta_%s_%d",AnalNames[i].data(),cbin), "", nratbins, ratbins);
        }
    }

    //-- plotting options

    for (int i = 0; i<nanals; i++) {
        for (int cbin = 0; cbin<ncentbins; cbin++) {
            v1p_eta[i][cbin]->SetMarkerColor(kRed);
            v1p_eta[i][cbin]->SetLineColor(kRed);
            v1p_eta[i][cbin]->SetMarkerStyle(21);
            v1p_eta[i][cbin]->SetMarkerSize(1.1);

            v1m_eta[i][cbin]->SetMarkerColor(kBlue);
            v1m_eta[i][cbin]->SetLineColor(kBlue);
            v1m_eta[i][cbin]->SetMarkerStyle(21);
            v1m_eta[i][cbin]->SetMarkerSize(1.1);

            v1odd_eta[i][cbin]->SetMarkerColor(kBlue);
            v1odd_eta[i][cbin]->SetLineColor(kBlue);
            v1odd_eta[i][cbin]->SetMarkerStyle(21);
            v1odd_eta[i][cbin]->SetMarkerSize(1.1);

            v1even_eta[i][cbin]->SetMarkerColor(kBlue);
            v1even_eta[i][cbin]->SetLineColor(kBlue);
            v1even_eta[i][cbin]->SetMarkerStyle(21);
            v1even_eta[i][cbin]->SetMarkerSize(1.1);
        }
    }


    //-- make plots
    if (!fopen("plots","r")) system("mkdir plots");
    if (!fopen("plots/intv1","r")) system("mkdir plots/intv1");
    if (!fopen("plots/intv1/intv1_eta","r")) system("mkdir plots/intv1/intv1_eta");

    int anal; // choice of analysis


    // integrated v1(eta) using HF+/- for each centrality bin
    anal = 7;
    if (!fopen(Form("plots/intv1/intv1_eta/int%s",AnalNames[anal].data()),"r")) system(Form("mkdir plots/intv1/intv1_eta/int%s",AnalNames[anal].data()));

    TCanvas * cv1HFpm_eta = new TCanvas("cv1HFpm_eta","cv1HFpm_eta",1100,630);
    TH1D * hv1HFpm_eta_tmp = new TH1D("hv1HFpm_eta", "", 40, -2.5, 2.5);
    hv1HFpm_eta_tmp->SetTitle("");
    hv1HFpm_eta_tmp->SetStats(0);
    hv1HFpm_eta_tmp->SetXTitle("#eta");
    hv1HFpm_eta_tmp->SetYTitle("v_{1}");
    hv1HFpm_eta_tmp->GetYaxis()->SetRangeUser(-0.19, 0.19);
    hv1HFpm_eta_tmp->SetNdivisions(509);
    cv1HFpm_eta->Divide(4,2,0,0);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1HFpm_eta = (TPad *) cv1HFpm_eta->cd(cbin+1);
        if (gridlines) padv1HFpm_eta->SetGrid();
        if (cbin == 3 || cbin == 7) padv1HFpm_eta->SetRightMargin(0.02);
        TH1D * hv1HFpm_eta = (TH1D *) hv1HFpm_eta_tmp->Clone(Form("hv1HFpm_eta_%c",cbin));
        if (cbin == 0) {
            hv1HFpm_eta->GetYaxis()->SetTitleSize(0.07);
            hv1HFpm_eta->GetYaxis()->SetTitleOffset(1.33);
            hv1HFpm_eta->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 4) {
            hv1HFpm_eta->GetXaxis()->CenterTitle();
            hv1HFpm_eta->GetXaxis()->SetTitleSize(0.06);
            hv1HFpm_eta->GetXaxis()->SetTitleOffset(1.12);
            hv1HFpm_eta->GetXaxis()->SetLabelSize(0.06);
            hv1HFpm_eta->GetXaxis()->SetLabelOffset(0.018);
            hv1HFpm_eta->GetYaxis()->SetTitleSize(0.06);
            hv1HFpm_eta->GetYaxis()->SetTitleOffset(1.50);
            hv1HFpm_eta->GetYaxis()->SetLabelSize(0.05);
            hv1HFpm_eta->GetYaxis()->SetLabelOffset(0.010);
        }
        if (cbin >=5) {
            hv1HFpm_eta->GetXaxis()->CenterTitle();
            hv1HFpm_eta->GetXaxis()->SetTitleSize(0.07);
            hv1HFpm_eta->GetXaxis()->SetTitleOffset(1.00);
            hv1HFpm_eta->GetXaxis()->SetLabelSize(0.07);
            hv1HFpm_eta->GetXaxis()->SetLabelOffset(0.008);
        }
        hv1HFpm_eta->Draw();
        v1p_eta[anal][cbin]->Draw("same");
        v1m_eta[anal][cbin]->Draw("same");

        TPaveText * txv1HFpm_eta;
        if (cbin == 0) txv1HFpm_eta = new TPaveText(0.25, 0.04, 0.46, 0.17,"NDC");
        else if (cbin >= 1 && cbin <= 3) txv1HFpm_eta = new TPaveText(0.06, 0.04, 0.26, 0.17,"NDC");
        else if (cbin == 4) txv1HFpm_eta = new TPaveText(0.25, 0.21, 0.46, 0.30,"NDC");
        else txv1HFpm_eta = new TPaveText(0.06, 0.21, 0.26, 0.30,"NDC");
        SetTPaveTxt(txv1HFpm_eta, 18);
        txv1HFpm_eta->AddText(Form("%d-%d%%",centBins[cbin],centBins[cbin+1]));
        txv1HFpm_eta->Draw();
    }
    cv1HFpm_eta->cd(1);
    TPaveText * txv1HFpm_eta_1 = new TPaveText(0.23, 0.73, 0.82, 0.95,"NDC");
    SetTPaveTxt(txv1HFpm_eta_1, 18);
    txv1HFpm_eta_1->AddText("#bf{CMS} #it{Preliminary}");
    txv1HFpm_eta_1->AddText("0.3 < p_{T} < 3.0 (GeV/c)");
    txv1HFpm_eta_1->Draw();

    cv1HFpm_eta->cd(2);
    TLegend * legv1HFpm_eta = new TLegend(0.07, 0.75, 0.26, 0.95);
    SetLegend(legv1HFpm_eta, 18);
    legv1HFpm_eta->AddEntry(v1p_eta[anal][0]," HF+","p");
    legv1HFpm_eta->AddEntry(v1m_eta[anal][0]," HF-","p");
    legv1HFpm_eta->Draw();

    cv1HFpm_eta->Print(Form("plots/intv1/intv1_eta/int%s/v1_pm_eta_%s.png",AnalNames[anal].data(),AnalNames[anal].data()),"png");
    if (close_plots) cv1HFpm_eta->Close();



    // integrated v1^odd(eta) using HF for each centrality bin

    TCanvas * cv1HFodd_eta = new TCanvas("cv1HFodd_eta","cv1HFodd_eta",1100,630);
    TH1D * hv1HFodd_eta_tmp = new TH1D("hv1HFodd_eta", "", 40, -2.5, 2.5);
    hv1HFodd_eta_tmp->SetTitle("");
    hv1HFodd_eta_tmp->SetStats(0);
    hv1HFodd_eta_tmp->SetXTitle("#eta");
    hv1HFodd_eta_tmp->SetYTitle("v_{1}^{odd}");
    hv1HFodd_eta_tmp->GetYaxis()->SetRangeUser(-0.06, 0.06);
    hv1HFodd_eta_tmp->SetNdivisions(509);
    cv1HFodd_eta->Divide(4,2,0,0);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1HFodd_eta = (TPad *) cv1HFodd_eta->cd(cbin+1);
        if (gridlines) padv1HFodd_eta->SetGrid();
        if (cbin == 3 || cbin == 7) padv1HFodd_eta->SetRightMargin(0.02);
        TH1D * hv1HFodd_eta = (TH1D *) hv1HFodd_eta_tmp->Clone(Form("hv1HFodd_eta_%c",cbin));
        if (cbin == 0) {
            hv1HFodd_eta->GetYaxis()->SetTitleSize(0.07);
            hv1HFodd_eta->GetYaxis()->SetTitleOffset(1.33);
            hv1HFodd_eta->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 4) {
            hv1HFodd_eta->GetXaxis()->CenterTitle();
            hv1HFodd_eta->GetXaxis()->SetTitleSize(0.06);
            hv1HFodd_eta->GetXaxis()->SetTitleOffset(1.12);
            hv1HFodd_eta->GetXaxis()->SetLabelSize(0.06);
            hv1HFodd_eta->GetXaxis()->SetLabelOffset(0.018);
            hv1HFodd_eta->GetYaxis()->SetTitleSize(0.06);
            hv1HFodd_eta->GetYaxis()->SetTitleOffset(1.50);
            hv1HFodd_eta->GetYaxis()->SetLabelSize(0.05);
            hv1HFodd_eta->GetYaxis()->SetLabelOffset(0.010);
        }
        if (cbin >=5) {
            hv1HFodd_eta->GetXaxis()->CenterTitle();
            hv1HFodd_eta->GetXaxis()->SetTitleSize(0.07);
            hv1HFodd_eta->GetXaxis()->SetTitleOffset(1.00);
            hv1HFodd_eta->GetXaxis()->SetLabelSize(0.07);
            hv1HFodd_eta->GetXaxis()->SetLabelOffset(0.008);
        }
        hv1HFodd_eta->Draw();
        v1odd_eta[anal][cbin]->Draw("same");

        TPaveText * txv1HFodd_eta;
        if (cbin == 0) txv1HFodd_eta = new TPaveText(0.25, 0.04, 0.46, 0.17,"NDC");
        else if (cbin >= 1 && cbin <= 3) txv1HFodd_eta = new TPaveText(0.06, 0.04, 0.26, 0.17,"NDC");
        else if (cbin == 4) txv1HFodd_eta = new TPaveText(0.25, 0.21, 0.46, 0.30,"NDC");
        else txv1HFodd_eta = new TPaveText(0.06, 0.21, 0.26, 0.30,"NDC");
        SetTPaveTxt(txv1HFodd_eta, 18);
        txv1HFodd_eta->AddText(Form("%d-%d%%",centBins[cbin],centBins[cbin+1]));
        txv1HFodd_eta->Draw();
    }
    cv1HFodd_eta->cd(1);
    TPaveText * txv1HFodd_eta_1 = new TPaveText(0.23, 0.73, 0.82, 0.95,"NDC");
    SetTPaveTxt(txv1HFodd_eta_1, 18);
    txv1HFodd_eta_1->AddText("#bf{CMS} #it{Preliminary}");
    txv1HFodd_eta_1->AddText("0.3 < p_{T} < 3.0 (GeV/c)");
    txv1HFodd_eta_1->Draw();

    cv1HFodd_eta->Print(Form("plots/intv1/intv1_eta/int%s/v1_odd_eta_%s.png",AnalNames[anal].data(),AnalNames[anal].data()),"png");
    if (close_plots) cv1HFodd_eta->Close();



    // integrated v1^even(eta) using HF for each centrality bin

    TCanvas * cv1HFeven_eta = new TCanvas("cv1HFeven_eta","cv1HFeven_eta",1100,630);
    TH1D * hv1HFeven_eta_tmp = new TH1D("hv1HFeven_eta", "", 40, -2.5, 2.5);
    hv1HFeven_eta_tmp->SetTitle("");
    hv1HFeven_eta_tmp->SetStats(0);
    hv1HFeven_eta_tmp->SetXTitle("#eta");
    hv1HFeven_eta_tmp->SetYTitle("v_{1}^{even}");
    hv1HFeven_eta_tmp->GetYaxis()->SetRangeUser(-0.15, 0.0);
    hv1HFeven_eta_tmp->SetNdivisions(509);
    cv1HFeven_eta->Divide(4,2,0,0);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1HFeven_eta = (TPad *) cv1HFeven_eta->cd(cbin+1);
        if (gridlines) padv1HFeven_eta->SetGrid();
        if (cbin == 3 || cbin == 7) padv1HFeven_eta->SetRightMargin(0.02);
        TH1D * hv1HFeven_eta = (TH1D *) hv1HFeven_eta_tmp->Clone(Form("hv1HFeven_eta_%c",cbin));
        if (cbin == 0) {
            hv1HFeven_eta->GetYaxis()->SetTitleSize(0.07);
            hv1HFeven_eta->GetYaxis()->SetTitleOffset(1.33);
            hv1HFeven_eta->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 4) {
            hv1HFeven_eta->GetXaxis()->CenterTitle();
            hv1HFeven_eta->GetXaxis()->SetTitleSize(0.06);
            hv1HFeven_eta->GetXaxis()->SetTitleOffset(1.12);
            hv1HFeven_eta->GetXaxis()->SetLabelSize(0.06);
            hv1HFeven_eta->GetXaxis()->SetLabelOffset(0.018);
            hv1HFeven_eta->GetYaxis()->SetTitleSize(0.06);
            hv1HFeven_eta->GetYaxis()->SetTitleOffset(1.50);
            hv1HFeven_eta->GetYaxis()->SetLabelSize(0.05);
            hv1HFeven_eta->GetYaxis()->SetLabelOffset(0.010);
        }
        if (cbin >=5) {
            hv1HFeven_eta->GetXaxis()->CenterTitle();
            hv1HFeven_eta->GetXaxis()->SetTitleSize(0.07);
            hv1HFeven_eta->GetXaxis()->SetTitleOffset(1.00);
            hv1HFeven_eta->GetXaxis()->SetLabelSize(0.07);
            hv1HFeven_eta->GetXaxis()->SetLabelOffset(0.008);
        }
        hv1HFeven_eta->Draw();
        v1even_eta[anal][cbin]->Draw("same");

        TPaveText * txv1HFeven_eta;
        if (cbin == 0) txv1HFeven_eta = new TPaveText(0.25, 0.04, 0.46, 0.17,"NDC");
        else if (cbin >= 1 && cbin <= 3) txv1HFeven_eta = new TPaveText(0.06, 0.04, 0.26, 0.17,"NDC");
        else if (cbin == 4) txv1HFeven_eta = new TPaveText(0.25, 0.21, 0.46, 0.30,"NDC");
        else txv1HFeven_eta = new TPaveText(0.06, 0.21, 0.26, 0.30,"NDC");
        SetTPaveTxt(txv1HFeven_eta, 18);
        txv1HFeven_eta->AddText(Form("%d-%d%%",centBins[cbin],centBins[cbin+1]));
        txv1HFeven_eta->Draw();
    }
    cv1HFeven_eta->cd(1);
    TPaveText * txv1HFeven_eta_1 = new TPaveText(0.23, 0.14, 0.82, 0.36,"NDC");
    SetTPaveTxt(txv1HFeven_eta_1, 18);
    txv1HFeven_eta_1->AddText("#bf{CMS} #it{Preliminary}");
    txv1HFeven_eta_1->AddText("0.3 < p_{T} < 3.0 (GeV/c)");
    txv1HFeven_eta_1->Draw();

    cv1HFeven_eta->Print(Form("plots/intv1/intv1_eta/int%s/v1_even_eta_%s.png",AnalNames[anal].data(),AnalNames[anal].data()),"png");
    if (close_plots) cv1HFeven_eta->Close();



    // integrated v1(eta) using Track+/- for each centrality bin
    anal = 15;
    if (!fopen(Form("plots/intv1/intv1_eta/int%s",AnalNames[anal].data()),"r")) system(Form("mkdir plots/intv1/intv1_eta/int%s",AnalNames[anal].data()));

    TCanvas * cv1Trkpm_eta = new TCanvas("cv1Trkpm_eta","cv1Trkpm_eta",1100,630);
    TH1D * hv1Trkpm_eta_tmp = new TH1D("hv1Trkpm_eta", "", 40, -2.5, 2.5);
    hv1Trkpm_eta_tmp->SetTitle("");
    hv1Trkpm_eta_tmp->SetStats(0);
    hv1Trkpm_eta_tmp->SetXTitle("#eta");
    hv1Trkpm_eta_tmp->SetYTitle("v_{1}");
    hv1Trkpm_eta_tmp->GetYaxis()->SetRangeUser(-0.19, 0.19);
    hv1Trkpm_eta_tmp->SetNdivisions(509);
    cv1Trkpm_eta->Divide(4,2,0,0);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1Trkpm_eta = (TPad *) cv1Trkpm_eta->cd(cbin+1);
        if (gridlines) padv1Trkpm_eta->SetGrid();
        if (cbin == 3 || cbin == 7) padv1Trkpm_eta->SetRightMargin(0.02);
        TH1D * hv1Trkpm_eta = (TH1D *) hv1Trkpm_eta_tmp->Clone(Form("hv1Trkpm_eta_%c",cbin));
        if (cbin == 0) {
            hv1Trkpm_eta->GetYaxis()->SetTitleSize(0.07);
            hv1Trkpm_eta->GetYaxis()->SetTitleOffset(1.33);
            hv1Trkpm_eta->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 4) {
            hv1Trkpm_eta->GetXaxis()->CenterTitle();
            hv1Trkpm_eta->GetXaxis()->SetTitleSize(0.06);
            hv1Trkpm_eta->GetXaxis()->SetTitleOffset(1.12);
            hv1Trkpm_eta->GetXaxis()->SetLabelSize(0.06);
            hv1Trkpm_eta->GetXaxis()->SetLabelOffset(0.018);
            hv1Trkpm_eta->GetYaxis()->SetTitleSize(0.06);
            hv1Trkpm_eta->GetYaxis()->SetTitleOffset(1.50);
            hv1Trkpm_eta->GetYaxis()->SetLabelSize(0.05);
            hv1Trkpm_eta->GetYaxis()->SetLabelOffset(0.010);
        }
        if (cbin >=5) {
            hv1Trkpm_eta->GetXaxis()->CenterTitle();
            hv1Trkpm_eta->GetXaxis()->SetTitleSize(0.07);
            hv1Trkpm_eta->GetXaxis()->SetTitleOffset(1.00);
            hv1Trkpm_eta->GetXaxis()->SetLabelSize(0.07);
            hv1Trkpm_eta->GetXaxis()->SetLabelOffset(0.008);
        }
        hv1Trkpm_eta->Draw();
        v1p_eta[anal][cbin]->Draw("same");
        v1m_eta[anal][cbin]->Draw("same");

        TPaveText * txv1Trkpm_eta;
        if (cbin == 0) txv1Trkpm_eta = new TPaveText(0.25, 0.04, 0.46, 0.17,"NDC");
        else if (cbin >= 1 && cbin <= 3) txv1Trkpm_eta = new TPaveText(0.06, 0.04, 0.26, 0.17,"NDC");
        else if (cbin == 4) txv1Trkpm_eta = new TPaveText(0.25, 0.21, 0.46, 0.30,"NDC");
        else txv1Trkpm_eta = new TPaveText(0.06, 0.21, 0.26, 0.30,"NDC");
        SetTPaveTxt(txv1Trkpm_eta, 18);
        txv1Trkpm_eta->AddText(Form("%d-%d%%",centBins[cbin],centBins[cbin+1]));
        txv1Trkpm_eta->Draw();
    }
    cv1Trkpm_eta->cd(1);
    TPaveText * txv1Trkpm_eta_1 = new TPaveText(0.23, 0.73, 0.82, 0.95,"NDC");
    SetTPaveTxt(txv1Trkpm_eta_1, 18);
    txv1Trkpm_eta_1->AddText("#bf{CMS} #it{Preliminary}");
    txv1Trkpm_eta_1->AddText("0.3 < p_{T} < 3.0 (GeV/c)");
    txv1Trkpm_eta_1->Draw();

    cv1Trkpm_eta->cd(2);
    TLegend * legv1Trkpm_eta = new TLegend(0.07, 0.75, 0.26, 0.95);
    SetLegend(legv1Trkpm_eta, 18);
    legv1Trkpm_eta->AddEntry(v1p_eta[anal][0]," Tracker+","p");
    legv1Trkpm_eta->AddEntry(v1m_eta[anal][0]," Tracker-","p");
    legv1Trkpm_eta->Draw();

    cv1Trkpm_eta->Print(Form("plots/intv1/intv1_eta/int%s/v1_pm_eta_%s.png",AnalNames[anal].data(),AnalNames[anal].data()),"png");
    if (close_plots) cv1Trkpm_eta->Close();



    // integrated v1^even(eta) using the tracker (actually called v1odd in output file)

    TCanvas * cv1Trkeven_eta = new TCanvas("cv1Trkeven_eta","cv1Trkeven_eta",1100,630);
    TH1D * hv1Trkeven_eta_tmp = new TH1D("hv1Trkeven_eta", "", 40, -2.5, 2.5);
    hv1Trkeven_eta_tmp->SetTitle("");
    hv1Trkeven_eta_tmp->SetStats(0);
    hv1Trkeven_eta_tmp->SetXTitle("#eta");
    hv1Trkeven_eta_tmp->SetYTitle("v_{1}^{even}");
    hv1Trkeven_eta_tmp->GetYaxis()->SetRangeUser(-0.06, 0.06);
    hv1Trkeven_eta_tmp->SetNdivisions(509);
    cv1Trkeven_eta->Divide(4,2,0,0);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1Trkeven_eta = (TPad *) cv1Trkeven_eta->cd(cbin+1);
        if (gridlines) padv1Trkeven_eta->SetGrid();
        if (cbin == 3 || cbin == 7) padv1Trkeven_eta->SetRightMargin(0.02);
        TH1D * hv1Trkeven_eta = (TH1D *) hv1Trkeven_eta_tmp->Clone(Form("hv1Trkeven_eta_%c",cbin));
        if (cbin == 0) {
            hv1Trkeven_eta->GetYaxis()->SetTitleSize(0.07);
            hv1Trkeven_eta->GetYaxis()->SetTitleOffset(1.33);
            hv1Trkeven_eta->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 4) {
            hv1Trkeven_eta->GetXaxis()->CenterTitle();
            hv1Trkeven_eta->GetXaxis()->SetTitleSize(0.06);
            hv1Trkeven_eta->GetXaxis()->SetTitleOffset(1.12);
            hv1Trkeven_eta->GetXaxis()->SetLabelSize(0.06);
            hv1Trkeven_eta->GetXaxis()->SetLabelOffset(0.018);
            hv1Trkeven_eta->GetYaxis()->SetTitleSize(0.06);
            hv1Trkeven_eta->GetYaxis()->SetTitleOffset(1.50);
            hv1Trkeven_eta->GetYaxis()->SetLabelSize(0.05);
            hv1Trkeven_eta->GetYaxis()->SetLabelOffset(0.010);
        }
        if (cbin >=5) {
            hv1Trkeven_eta->GetXaxis()->CenterTitle();
            hv1Trkeven_eta->GetXaxis()->SetTitleSize(0.07);
            hv1Trkeven_eta->GetXaxis()->SetTitleOffset(1.00);
            hv1Trkeven_eta->GetXaxis()->SetLabelSize(0.07);
            hv1Trkeven_eta->GetXaxis()->SetLabelOffset(0.008);
        }
        hv1Trkeven_eta->Draw();
        v1odd_eta[anal][cbin]->Draw("same");

        TPaveText * txv1Trkeven_eta;
        if (cbin == 0) txv1Trkeven_eta = new TPaveText(0.25, 0.04, 0.46, 0.17,"NDC");
        else if (cbin >= 1 && cbin <= 3) txv1Trkeven_eta = new TPaveText(0.06, 0.04, 0.26, 0.17,"NDC");
        else if (cbin == 4) txv1Trkeven_eta = new TPaveText(0.25, 0.21, 0.46, 0.30,"NDC");
        else txv1Trkeven_eta = new TPaveText(0.06, 0.21, 0.26, 0.30,"NDC");
        SetTPaveTxt(txv1Trkeven_eta, 18);
        txv1Trkeven_eta->AddText(Form("%d-%d%%",centBins[cbin],centBins[cbin+1]));
        txv1Trkeven_eta->Draw();
    }
    cv1Trkeven_eta->cd(1);
    TPaveText * txv1Trkeven_eta_1 = new TPaveText(0.23, 0.73, 0.82, 0.95,"NDC");
    SetTPaveTxt(txv1Trkeven_eta_1, 18);
    txv1Trkeven_eta_1->AddText("#bf{CMS} #it{Preliminary}");
    txv1Trkeven_eta_1->AddText("0.3 < p_{T} < 3.0 (GeV/c)");
    txv1Trkeven_eta_1->Draw();

    cv1Trkeven_eta->Print(Form("plots/intv1/intv1_eta/int%s/v1_odd_eta_%s.png",AnalNames[anal].data(),AnalNames[anal].data()),"png");
    if (close_plots) cv1Trkeven_eta->Close();

}
