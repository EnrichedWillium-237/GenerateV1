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
static const int centBins[] = {0, 10, 20, 30, 40, 50, 60, 70, 80};
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

TH1D * runParms[nanals];

void intV1_pT()
{

    TH1::SetDefaultSumw2();

    TFile * tfin = new TFile("../outputs/final_outputs/v1Int.root");

    //-- retrieve histograms from final output file
    for (int i = 0; i<nanals; i++) {
        for (int cbin = 0; cbin<ncentbins; cbin++) {
            v1p_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v1p_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v1m_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v1m_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v1odd_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v1odd_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v1even_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v1even_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));

            v112p_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v112p_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v112m_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v112m_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v112odd_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v112odd_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v112even_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v112even_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));

            v123p_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v123p_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v123m_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v123m_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v123odd_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v123odd_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v123even_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v123even_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
        }
    }

    //-- plotting options

    for (int i = 0; i<nanals; i++) {
        for (int cbin = 0; cbin<ncentbins; cbin++) {
            v1p_pt[i][cbin]->SetMarkerColor(kRed);
            v1p_pt[i][cbin]->SetLineColor(kRed);
            v1p_pt[i][cbin]->SetMarkerStyle(21);
            v1p_pt[i][cbin]->SetMarkerSize(1.1);

            v1m_pt[i][cbin]->SetMarkerColor(kBlue);
            v1m_pt[i][cbin]->SetLineColor(kBlue);
            v1m_pt[i][cbin]->SetMarkerStyle(21);
            v1m_pt[i][cbin]->SetMarkerSize(1.1);

            v1odd_pt[i][cbin]->SetMarkerColor(kBlue);
            v1odd_pt[i][cbin]->SetLineColor(kBlue);
            v1odd_pt[i][cbin]->SetMarkerStyle(21);
            v1odd_pt[i][cbin]->SetMarkerSize(1.1);

            v1even_pt[i][cbin]->SetMarkerColor(kBlue);
            v1even_pt[i][cbin]->SetLineColor(kBlue);
            v1even_pt[i][cbin]->SetMarkerStyle(21);
            v1even_pt[i][cbin]->SetMarkerSize(1.1);
        }
    }


    //-- make plots
    if (!fopen("plots","r")) system("mkdir plots");
    if (!fopen("plots/intv1","r")) system("mkdir plots/intv1");
    if (!fopen("plots/intv1/intv1_pt","r")) system("mkdir plots/intv1/intv1_pt");

    int anal; // choice of analysis


    // integrated v1(eta) using HF+/- for each centrality bin
    anal = 7;
    if (!fopen(Form("plots/intv1/intv1_pt/int%s",AnalNames[anal].data()),"r")) system(Form("mkdir plots/intv1/intv1_pt/int%s",AnalNames[anal].data()));

    TCanvas * cv1HFpm_pt = new TCanvas("cv1HFpm_pt","cv1HFpm_pt",1100,630);
    TH1D * hv1HFpm_pt_tmp = new TH1D("hv1HFpm_pt", "", 40, 0, 12);
    hv1HFpm_pt_tmp->SetTitle("");
    hv1HFpm_pt_tmp->SetStats(0);
    hv1HFpm_pt_tmp->SetXTitle("p_{T} (GeV/c)");
    hv1HFpm_pt_tmp->SetYTitle("v_{1}");
    hv1HFpm_pt_tmp->GetYaxis()->SetRangeUser(-0.3, 0.3);
    hv1HFpm_pt_tmp->SetNdivisions(509);
    cv1HFpm_pt->Divide(4,2,0,0);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1HFpm_pt = (TPad *) cv1HFpm_pt->cd(cbin+1);
        if (gridlines) padv1HFpm_pt->SetGrid();
        if (cbin == 3 || cbin == 7) padv1HFpm_pt->SetRightMargin(0.02);
        TH1D * hv1HFpm_pt = (TH1D *) hv1HFpm_pt_tmp->Clone(Form("hv1HFpm_pt_%c",cbin));
        if (cbin == 0) {
            hv1HFpm_pt->GetYaxis()->SetTitleSize(0.07);
            hv1HFpm_pt->GetYaxis()->SetTitleOffset(1.33);
            hv1HFpm_pt->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 4) {
            hv1HFpm_pt->GetXaxis()->CenterTitle();
            hv1HFpm_pt->GetXaxis()->SetTitleSize(0.06);
            hv1HFpm_pt->GetXaxis()->SetTitleOffset(1.12);
            hv1HFpm_pt->GetXaxis()->SetLabelSize(0.06);
            hv1HFpm_pt->GetXaxis()->SetLabelOffset(0.018);
            hv1HFpm_pt->GetYaxis()->SetTitleSize(0.06);
            hv1HFpm_pt->GetYaxis()->SetTitleOffset(1.50);
            hv1HFpm_pt->GetYaxis()->SetLabelSize(0.05);
            hv1HFpm_pt->GetYaxis()->SetLabelOffset(0.010);
        }
        if (cbin >=5) {
            hv1HFpm_pt->GetXaxis()->CenterTitle();
            hv1HFpm_pt->GetXaxis()->SetTitleSize(0.07);
            hv1HFpm_pt->GetXaxis()->SetTitleOffset(1.00);
            hv1HFpm_pt->GetXaxis()->SetLabelSize(0.07);
            hv1HFpm_pt->GetXaxis()->SetLabelOffset(0.008);
        }
        hv1HFpm_pt->Draw();
        v1p_pt[anal][cbin]->Draw("same");
        v1m_pt[anal][cbin]->Draw("same");

        TPaveText * txv1HFpm_pt;
        if (cbin == 0) txv1HFpm_pt = new TPaveText(0.25, 0.04, 0.46, 0.17,"NDC");
        else if (cbin >= 1 && cbin <= 3) txv1HFpm_pt = new TPaveText(0.06, 0.04, 0.26, 0.17,"NDC");
        else if (cbin == 4) txv1HFpm_pt = new TPaveText(0.25, 0.21, 0.46, 0.30,"NDC");
        else txv1HFpm_pt = new TPaveText(0.06, 0.21, 0.26, 0.30,"NDC");
        SetTPaveTxt(txv1HFpm_pt, 18);
        txv1HFpm_pt->AddText(Form("%d-%d%%",centBins[cbin],centBins[cbin+1]));
        txv1HFpm_pt->Draw();
    }
    cv1HFpm_pt->cd(1);
    TPaveText * txv1HFpm_pt_1 = new TPaveText(0.23, 0.78, 0.68, 0.94,"NDC");
    SetTPaveTxt(txv1HFpm_pt_1, 18);
    txv1HFpm_pt_1->AddText("#bf{CMS} #it{Preliminary}");
    txv1HFpm_pt_1->AddText("|#eta| < 2.4");
    txv1HFpm_pt_1->Draw();

    cv1HFpm_pt->cd(2);
    TLegend * legv1HFpm_pt = new TLegend(0.07, 0.75, 0.26, 0.95);
    SetLegend(legv1HFpm_pt, 18);
    legv1HFpm_pt->AddEntry(v1p_pt[anal][0]," HF+","p");
    legv1HFpm_pt->AddEntry(v1m_pt[anal][0]," HF-","p");
    legv1HFpm_pt->Draw();

    cv1HFpm_pt->Print(Form("plots/intv1/intv1_pt/int%s/v1_pm_pt_%s.png",AnalNames[anal].data(),AnalNames[anal].data()),"png");
    if (close_plots) cv1HFpm_pt->Close();



    // integrated v1^odd(eta) using HF for each centrality bin

    TCanvas * cv1HFodd_pt = new TCanvas("cv1HFodd_pt","cv1HFodd_pt",1100,630);
    TH1D * hv1HFodd_pt_tmp = new TH1D("hv1HFodd_pt", "", 40, 0, 12);
    hv1HFodd_pt_tmp->SetTitle("");
    hv1HFodd_pt_tmp->SetStats(0);
    hv1HFodd_pt_tmp->SetXTitle("p_{T} (GeV/c)");
    hv1HFodd_pt_tmp->SetYTitle("v_{1}^{odd}");
    hv1HFodd_pt_tmp->GetYaxis()->SetRangeUser(-0.04, 0.04);
    hv1HFodd_pt_tmp->SetNdivisions(509);
    cv1HFodd_pt->Divide(4,2,0,0);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1HFodd_pt = (TPad *) cv1HFodd_pt->cd(cbin+1);
        if (gridlines) padv1HFodd_pt->SetGrid();
        if (cbin == 3 || cbin == 7) padv1HFodd_pt->SetRightMargin(0.02);
        TH1D * hv1HFodd_pt = (TH1D *) hv1HFodd_pt_tmp->Clone(Form("hv1HFodd_pt_%c",cbin));
        if (cbin == 0) {
            hv1HFodd_pt->GetYaxis()->SetTitleSize(0.07);
            hv1HFodd_pt->GetYaxis()->SetTitleOffset(1.33);
            hv1HFodd_pt->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 4) {
            hv1HFodd_pt->GetXaxis()->CenterTitle();
            hv1HFodd_pt->GetXaxis()->SetTitleSize(0.06);
            hv1HFodd_pt->GetXaxis()->SetTitleOffset(1.12);
            hv1HFodd_pt->GetXaxis()->SetLabelSize(0.06);
            hv1HFodd_pt->GetXaxis()->SetLabelOffset(0.018);
            hv1HFodd_pt->GetYaxis()->SetTitleSize(0.06);
            hv1HFodd_pt->GetYaxis()->SetTitleOffset(1.50);
            hv1HFodd_pt->GetYaxis()->SetLabelSize(0.05);
            hv1HFodd_pt->GetYaxis()->SetLabelOffset(0.010);
        }
        if (cbin >=5) {
            hv1HFodd_pt->GetXaxis()->CenterTitle();
            hv1HFodd_pt->GetXaxis()->SetTitleSize(0.07);
            hv1HFodd_pt->GetXaxis()->SetTitleOffset(1.00);
            hv1HFodd_pt->GetXaxis()->SetLabelSize(0.07);
            hv1HFodd_pt->GetXaxis()->SetLabelOffset(0.008);
        }
        hv1HFodd_pt->Draw();
        v1odd_pt[anal][cbin]->Draw("same");

        TPaveText * txv1HFodd_pt;
        if (cbin == 0) txv1HFodd_pt = new TPaveText(0.25, 0.04, 0.46, 0.17,"NDC");
        else if (cbin >= 1 && cbin <= 3) txv1HFodd_pt = new TPaveText(0.06, 0.04, 0.26, 0.17,"NDC");
        else if (cbin == 4) txv1HFodd_pt = new TPaveText(0.25, 0.21, 0.46, 0.30,"NDC");
        else txv1HFodd_pt = new TPaveText(0.06, 0.21, 0.26, 0.30,"NDC");
        SetTPaveTxt(txv1HFodd_pt, 18);
        txv1HFodd_pt->AddText(Form("%d-%d%%",centBins[cbin],centBins[cbin+1]));
        txv1HFodd_pt->Draw();
    }
    cv1HFodd_pt->cd(1);
    TPaveText * txv1HFodd_pt_1 = new TPaveText(0.23, 0.78, 0.68, 0.94,"NDC");
    SetTPaveTxt(txv1HFodd_pt_1, 18);
    txv1HFodd_pt_1->AddText("#bf{CMS} #it{Preliminary}");
    txv1HFodd_pt_1->AddText("|#eta| < 2.4");
    txv1HFodd_pt_1->Draw();

    cv1HFodd_pt->Print(Form("plots/intv1/intv1_pt/int%s/v1_odd_pt_%s.png",AnalNames[anal].data(),AnalNames[anal].data()),"png");
    if (close_plots) cv1HFodd_pt->Close();



    // integrated v1^even(eta) using HF for each centrality bin

    TCanvas * cv1HFeven_pt = new TCanvas("cv1HFeven_pt","cv1HFeven_pt",1100,630);
    TH1D * hv1HFeven_pt_tmp = new TH1D("hv1HFeven_pt", "", 40, 0, 12);
    hv1HFeven_pt_tmp->SetTitle("");
    hv1HFeven_pt_tmp->SetStats(0);
    hv1HFeven_pt_tmp->SetXTitle("p_{T} (GeV/c)");
    hv1HFeven_pt_tmp->SetYTitle("v_{1}^{even}");
    hv1HFeven_pt_tmp->GetYaxis()->SetRangeUser(-0.25, 0.0);
    hv1HFeven_pt_tmp->SetNdivisions(509);
    cv1HFeven_pt->Divide(4,2,0,0);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1HFeven_pt = (TPad *) cv1HFeven_pt->cd(cbin+1);
        if (gridlines) padv1HFeven_pt->SetGrid();
        if (cbin == 3 || cbin == 7) padv1HFeven_pt->SetRightMargin(0.02);
        TH1D * hv1HFeven_pt = (TH1D *) hv1HFeven_pt_tmp->Clone(Form("hv1HFeven_pt_%c",cbin));
        if (cbin == 0) {
            hv1HFeven_pt->GetYaxis()->SetTitleSize(0.07);
            hv1HFeven_pt->GetYaxis()->SetTitleOffset(1.33);
            hv1HFeven_pt->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 4) {
            hv1HFeven_pt->GetXaxis()->CenterTitle();
            hv1HFeven_pt->GetXaxis()->SetTitleSize(0.06);
            hv1HFeven_pt->GetXaxis()->SetTitleOffset(1.12);
            hv1HFeven_pt->GetXaxis()->SetLabelSize(0.06);
            hv1HFeven_pt->GetXaxis()->SetLabelOffset(0.018);
            hv1HFeven_pt->GetYaxis()->SetTitleSize(0.06);
            hv1HFeven_pt->GetYaxis()->SetTitleOffset(1.50);
            hv1HFeven_pt->GetYaxis()->SetLabelSize(0.05);
            hv1HFeven_pt->GetYaxis()->SetLabelOffset(0.010);
        }
        if (cbin >=5) {
            hv1HFeven_pt->GetXaxis()->CenterTitle();
            hv1HFeven_pt->GetXaxis()->SetTitleSize(0.07);
            hv1HFeven_pt->GetXaxis()->SetTitleOffset(1.00);
            hv1HFeven_pt->GetXaxis()->SetLabelSize(0.07);
            hv1HFeven_pt->GetXaxis()->SetLabelOffset(0.008);
        }
        hv1HFeven_pt->Draw();
        v1even_pt[anal][cbin]->Draw("same");

        TPaveText * txv1HFeven_pt;
        if (cbin == 0) txv1HFeven_pt = new TPaveText(0.25, 0.04, 0.46, 0.17,"NDC");
        else if (cbin >= 1 && cbin <= 3) txv1HFeven_pt = new TPaveText(0.06, 0.04, 0.26, 0.17,"NDC");
        else if (cbin == 4) txv1HFeven_pt = new TPaveText(0.25, 0.21, 0.46, 0.30,"NDC");
        else txv1HFeven_pt = new TPaveText(0.06, 0.21, 0.26, 0.30,"NDC");
        SetTPaveTxt(txv1HFeven_pt, 18);
        txv1HFeven_pt->AddText(Form("%d-%d%%",centBins[cbin],centBins[cbin+1]));
        txv1HFeven_pt->Draw();
    }
    cv1HFeven_pt->cd(1);
    TPaveText * txv1HFeven_pt_1 = new TPaveText(0.24, 0.17, 0.69, 0.33,"NDC");
    SetTPaveTxt(txv1HFeven_pt_1, 18);
    txv1HFeven_pt_1->AddText("#bf{CMS} #it{Preliminary}");
    txv1HFeven_pt_1->AddText("|#eta| < 2.4");
    txv1HFeven_pt_1->Draw();

    cv1HFeven_pt->Print(Form("plots/intv1/intv1_pt/int%s/v1_even_pt_%s.png",AnalNames[anal].data(),AnalNames[anal].data()),"png");
    if (close_plots) cv1HFeven_pt->Close();



    // integrated v1(eta) using Track+/- for each centrality bin
    anal = 15;
    if (!fopen(Form("plots/intv1/intv1_pt/int%s",AnalNames[anal].data()),"r")) system(Form("mkdir plots/intv1/intv1_pt/int%s",AnalNames[anal].data()));

    TCanvas * cv1Trkpm_pt = new TCanvas("cv1Trkpm_pt","cv1Trkpm_pt",1100,630);
    TH1D * hv1Trkpm_pt_tmp = new TH1D("hv1Trkpm_pt", "", 40, 0, 12);
    hv1Trkpm_pt_tmp->SetTitle("");
    hv1Trkpm_pt_tmp->SetStats(0);
    hv1Trkpm_pt_tmp->SetXTitle("p_{T} (GeV/c)");
    hv1Trkpm_pt_tmp->SetYTitle("v_{1}");
    hv1Trkpm_pt_tmp->GetYaxis()->SetRangeUser(-0.06, 0.26);
    hv1Trkpm_pt_tmp->SetNdivisions(509);
    cv1Trkpm_pt->Divide(4,2,0,0);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1Trkpm_pt = (TPad *) cv1Trkpm_pt->cd(cbin+1);
        if (gridlines) padv1Trkpm_pt->SetGrid();
        if (cbin == 3 || cbin == 7) padv1Trkpm_pt->SetRightMargin(0.02);
        TH1D * hv1Trkpm_pt = (TH1D *) hv1Trkpm_pt_tmp->Clone(Form("hv1Trkpm_pt_%c",cbin));
        if (cbin == 0) {
            hv1Trkpm_pt->GetYaxis()->SetTitleSize(0.07);
            hv1Trkpm_pt->GetYaxis()->SetTitleOffset(1.33);
            hv1Trkpm_pt->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 4) {
            hv1Trkpm_pt->GetXaxis()->CenterTitle();
            hv1Trkpm_pt->GetXaxis()->SetTitleSize(0.06);
            hv1Trkpm_pt->GetXaxis()->SetTitleOffset(1.12);
            hv1Trkpm_pt->GetXaxis()->SetLabelSize(0.06);
            hv1Trkpm_pt->GetXaxis()->SetLabelOffset(0.018);
            hv1Trkpm_pt->GetYaxis()->SetTitleSize(0.06);
            hv1Trkpm_pt->GetYaxis()->SetTitleOffset(1.50);
            hv1Trkpm_pt->GetYaxis()->SetLabelSize(0.05);
            hv1Trkpm_pt->GetYaxis()->SetLabelOffset(0.010);
        }
        if (cbin >=5) {
            hv1Trkpm_pt->GetXaxis()->CenterTitle();
            hv1Trkpm_pt->GetXaxis()->SetTitleSize(0.07);
            hv1Trkpm_pt->GetXaxis()->SetTitleOffset(1.00);
            hv1Trkpm_pt->GetXaxis()->SetLabelSize(0.07);
            hv1Trkpm_pt->GetXaxis()->SetLabelOffset(0.008);
        }
        hv1Trkpm_pt->Draw();
        v1p_pt[anal][cbin]->Draw("same");
        v1m_pt[anal][cbin]->Draw("same");

        TPaveText * txv1Trkpm_pt;
        if (cbin == 0) txv1Trkpm_pt = new TPaveText(0.75, 0.86, 0.93, 0.95,"NDC");
        else if (cbin >= 1 && cbin <= 3) txv1Trkpm_pt = new TPaveText(0.68, 0.86, 0.86, 0.95,"NDC");
        else if (cbin == 4) txv1Trkpm_pt = new TPaveText(0.75, 0.86, 0.93, 0.95,"NDC");
        else txv1Trkpm_pt = new TPaveText(0.68, 0.86, 0.86, 0.95,"NDC");
        SetTPaveTxt(txv1Trkpm_pt, 18);
        txv1Trkpm_pt->AddText(Form("%d-%d%%",centBins[cbin],centBins[cbin+1]));
        txv1Trkpm_pt->Draw();
    }
    cv1Trkpm_pt->cd(1);
    TPaveText * txv1Trkpm_pt_1 = new TPaveText(0.23, 0.78, 0.68, 0.94,"NDC");
    SetTPaveTxt(txv1Trkpm_pt_1, 18);
    txv1Trkpm_pt_1->AddText("#bf{CMS} #it{Preliminary}");
    txv1Trkpm_pt_1->AddText("|#eta| < 2.4");
    txv1Trkpm_pt_1->Draw();

    cv1Trkpm_pt->cd(2);
    TLegend * legv1Trkpm_pt = new TLegend(0.07, 0.78, 0.40, 0.94);
    SetLegend(legv1Trkpm_pt, 18);
    legv1Trkpm_pt->AddEntry(v1p_pt[anal][0],"Tracker+","p");
    legv1Trkpm_pt->AddEntry(v1m_pt[anal][0],"Tracker-","p");
    legv1Trkpm_pt->Draw();

    cv1Trkpm_pt->Print(Form("plots/intv1/intv1_pt/int%s/v1_pm_pt_%s.png",AnalNames[anal].data(),AnalNames[anal].data()),"png");
    if (close_plots) cv1Trkpm_pt->Close();

}
