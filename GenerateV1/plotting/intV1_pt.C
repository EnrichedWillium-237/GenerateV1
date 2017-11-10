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
static const int nadbins = 6;
static const double adbins[] = {0.0,  0.4,  0.8,  1.2,  1.6,  2.0,  2.4};
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

TH1D * v1Stat_pt[nanals][ncentbins];
TH1D * v1Syst_pt[nanals][ncentbins];

TGraphErrors * grv1Stat_pt[nanals][ncentbins];
TGraphErrors * grv1Syst_pt[nanals][ncentbins];

TFile * tfin;

void intV1_pt()
{

    TH1::SetDefaultSumw2();

    tfin = new TFile("../outputs/final_outputs/v1Int_ErrCalc.root");

    for (int i = 0; i<nanals; i++) {
        for (int cbin = 0; cbin<ncentbins; cbin++) {
            v1Stat_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v1Stat_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
            v1Syst_pt[i][cbin] = (TH1D *) tfin->Get(Form("%s/v1_pt/%d-%d/v1Syst_pt_%s_%d",AnalNames[i].data(),centBins[cbin],centBins[cbin+1],AnalNames[i].data(),cbin));
        }
    }

    //-- turn into TGraphErrors
    for (int i = 0; i<nanals; i++) {
        for (int cbin = 0; cbin<ncentbins; cbin++) {
            double npt = v1Stat_pt[i][cbin]->GetNbinsX();
            double x[nptbins];
            double y[nptbins];
            double xerr[nptbins];
            double yerrStat[nptbins];
            double xerrSyst[nptbins];
            double yerrSyst[nptbins];
            for (int pbin = 0; pbin<npt; pbin++) {
                x[pbin] = v1Stat_pt[i][cbin]->GetBinCenter(pbin+1);
                y[pbin] = v1Stat_pt[i][cbin]->GetBinContent(pbin+1);
                xerr[pbin] = 0;
                yerrStat[pbin] = v1Stat_pt[i][cbin]->GetBinError(pbin+1);
                xerrSyst[pbin] = v1Stat_pt[i][cbin]->GetBinCenter(pbin+1)-v1Stat_pt[i][cbin]->GetBinLowEdge(pbin+1);
                yerrSyst[pbin] = v1Syst_pt[i][cbin]->GetBinError(pbin+1);
                //if (i == 15 && cbin == 0) cout<<pbin<<"\t"<<npt<<"\t"<<x[pbin]<<"\t"<<y[pbin]<<endl;
            }
            grv1Stat_pt[i][cbin] = new TGraphErrors(npt, x, y, xerr, yerrStat);
            grv1Syst_pt[i][cbin] = new TGraphErrors(npt, x, y, xerrSyst, yerrSyst);
        }
    }

    //-- plotting options

    for (int i = 0; i<nanals; i++) {
        for (int cbin = 0; cbin<ncentbins; cbin++) {
            grv1Stat_pt[i][cbin]->SetMarkerColor(kBlue);
            grv1Stat_pt[i][cbin]->SetLineColor(kBlue);
            grv1Stat_pt[i][cbin]->SetMarkerStyle(21);
            grv1Stat_pt[i][cbin]->SetMarkerSize(1.1);

            grv1Syst_pt[i][cbin]->SetMarkerColor(kBlue);
            grv1Syst_pt[i][cbin]->SetLineColor(kBlue);
            grv1Syst_pt[i][cbin]->SetMarkerStyle(21);
            grv1Syst_pt[i][cbin]->SetMarkerSize(1.1);
            grv1Syst_pt[i][cbin]->SetFillColor(kRed-7);
        }
    }

    //-- make plots

    if (!fopen("plots","r")) system("mkdir plots");
    if (!fopen("plots/intv1","r")) system("mkdir plots/intv1");
    if (!fopen("plots/intv1/intv1_pt","r")) system("mkdir plots/intv1/intv1_pt");

    int anal; // choice of analysis


    // v1odd(eta) using the tracker event planes
    anal = 15;
    if (!fopen(Form("plots/intv1/intv1_pt/int%s",AnalNames[anal].data()),"r")) system(Form("mkdir plots/intv1/intv1_pt/int%s",AnalNames[anal].data()));

    TCanvas * cv1oddIntTrk_pt = new TCanvas("cv1oddIntTrk_pt","cv1oddIntTrk_pt",1100,620);
    cv1oddIntTrk_pt->Divide(4,2,0,0);
    TH1D * hv1oddIntTrk_pt_tmp = new TH1D("hv1oddIntTrk_pt_tmp", "", 100, 0, 12);
    hv1oddIntTrk_pt_tmp->SetTitle("");
    hv1oddIntTrk_pt_tmp->SetStats(0);
    hv1oddIntTrk_pt_tmp->SetXTitle("p_{T} (GeV/c)");
    hv1oddIntTrk_pt_tmp->SetYTitle("v_{1}^{even}");
    hv1oddIntTrk_pt_tmp->GetYaxis()->SetRangeUser(-0.06, 0.26);
    hv1oddIntTrk_pt_tmp->GetXaxis()->CenterTitle();
    hv1oddIntTrk_pt_tmp->GetYaxis()->CenterTitle();
    hv1oddIntTrk_pt_tmp->GetYaxis()->SetNdivisions(509);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1oddIntTrk_pt = (TPad *) cv1oddIntTrk_pt->cd(cbin+1);
        if (gridlines) padv1oddIntTrk_pt->SetGrid();
        if (cbin == 3 || cbin == 7) padv1oddIntTrk_pt->SetRightMargin(0.02);
        if (cbin<=3) padv1oddIntTrk_pt->SetTopMargin(0.08);
        TH1D * hv1oddIntTrk_pt = (TH1D *) hv1oddIntTrk_pt_tmp->Clone(Form("hv1oddIntTrk_pt_%c",cbin));
        if (cbin == 0) {
            hv1oddIntTrk_pt->GetYaxis()->SetTitleSize(0.07);
            hv1oddIntTrk_pt->GetYaxis()->SetTitleOffset(1.33);
            hv1oddIntTrk_pt->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 4) {
            hv1oddIntTrk_pt->GetXaxis()->SetTitleSize(0.06);
            hv1oddIntTrk_pt->GetXaxis()->SetTitleOffset(1.12);
            hv1oddIntTrk_pt->GetXaxis()->SetLabelSize(0.06);
            hv1oddIntTrk_pt->GetXaxis()->SetLabelOffset(0.018);
            hv1oddIntTrk_pt->GetYaxis()->SetTitleSize(0.06);
            hv1oddIntTrk_pt->GetYaxis()->SetTitleOffset(1.50);
            hv1oddIntTrk_pt->GetYaxis()->SetLabelSize(0.05);
            hv1oddIntTrk_pt->GetYaxis()->SetLabelOffset(0.010);
        }
        if (cbin >=5) {
            hv1oddIntTrk_pt->GetXaxis()->SetTitleSize(0.07);
            hv1oddIntTrk_pt->GetXaxis()->SetTitleOffset(1.00);
            hv1oddIntTrk_pt->GetXaxis()->SetLabelSize(0.07);
            hv1oddIntTrk_pt->GetXaxis()->SetLabelOffset(0.008);
        }
        hv1oddIntTrk_pt->Draw();
        v1Stat_pt[anal][cbin]->Draw("same");
        grv1Stat_pt[anal][cbin]->Draw("same p");

        TPaveText * txv1oddIntTrk_pt_0;
        if (cbin == 0) txv1oddIntTrk_pt_0 = new TPaveText(0.24, 0.54, 0.45, 0.67,"NDC");
        else if (cbin >= 1 && cbin <= 3) txv1oddIntTrk_pt_0 = new TPaveText(0.71, 0.76, 0.91, 0.88,"NDC");
        else if (cbin == 4) txv1oddIntTrk_pt_0 = new TPaveText(0.73, 0.85, 0.95, 0.95,"NDC");
        else txv1oddIntTrk_pt_0 = new TPaveText(0.71, 0.85, 0.91, 0.95,"NDC");
        SetTPaveTxt(txv1oddIntTrk_pt_0, 18);
        txv1oddIntTrk_pt_0->AddText(Form("%d-%d%%",centBins[cbin],centBins[cbin+1]));
        txv1oddIntTrk_pt_0->Draw();
    }
    cv1oddIntTrk_pt->cd(1);
    TPaveText * txv1oddIntTrk_pt_1 = new TPaveText(0.22, 0.65, 0.81, 0.86,"NDC");
    SetTPaveTxt(txv1oddIntTrk_pt_1, 18);
    txv1oddIntTrk_pt_1->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1oddIntTrk_pt_1->AddText("|#eta| < 2.4");
    txv1oddIntTrk_pt_1->Draw();

    TPaveText * txv1oddIntTrk_pt_2 = new TPaveText(0.18, 0.93, 0.58, 1.0,"NDC");
    SetTPaveTxt(txv1oddIntTrk_pt_2, 18);
    txv1oddIntTrk_pt_2->AddText("#bf{CMS} #it{Preliminary}");
    txv1oddIntTrk_pt_2->Draw();

    cv1oddIntTrk_pt->Print(Form("plots/intv1/intv1_pt/int%s/v1oddIntTrk_pt_%s.png",AnalNames[anal].data(),AnalNames[anal].data()),"png");
    if (close_plots) cv1oddIntTrk_pt->Close();



    // v1odd(eta) using the HF event planes with systematics due to antisymmetry
    TCanvas * cv1oddIntTrk_pt_syst = new TCanvas("cv1oddIntTrk_pt_syst","cv1oddIntTrk_pt_syst",1100,620);
    cv1oddIntTrk_pt_syst->Divide(4,2,0,0);
    TH1D * hv1oddIntTrk_pt_syst_tmp = new TH1D("hv1oddIntTrk_pt_syst_tmp", "", 100, 0, 12);
    hv1oddIntTrk_pt_syst_tmp->SetTitle("");
    hv1oddIntTrk_pt_syst_tmp->SetStats(0);
    hv1oddIntTrk_pt_syst_tmp->SetXTitle("p_{T} (GeV/c)");
    hv1oddIntTrk_pt_syst_tmp->SetYTitle("v_{1}^{even}");
    hv1oddIntTrk_pt_syst_tmp->GetYaxis()->SetRangeUser(-0.06, 0.26);
    hv1oddIntTrk_pt_syst_tmp->GetXaxis()->CenterTitle();
    hv1oddIntTrk_pt_syst_tmp->GetYaxis()->CenterTitle();
    hv1oddIntTrk_pt_syst_tmp->GetYaxis()->SetNdivisions(509);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1oddIntTrk_pt_syst = (TPad *) cv1oddIntTrk_pt_syst->cd(cbin+1);
        if (gridlines) padv1oddIntTrk_pt_syst->SetGrid();
        if (cbin == 3 || cbin == 7) padv1oddIntTrk_pt_syst->SetRightMargin(0.02);
        if (cbin<=3) padv1oddIntTrk_pt_syst->SetTopMargin(0.08);
        TH1D * hv1oddIntTrk_pt_syst = (TH1D *) hv1oddIntTrk_pt_syst_tmp->Clone(Form("hv1oddIntTrk_pt_syst_%c",cbin));
        if (cbin == 0) {
            hv1oddIntTrk_pt_syst->GetYaxis()->SetTitleSize(0.07);
            hv1oddIntTrk_pt_syst->GetYaxis()->SetTitleOffset(1.33);
            hv1oddIntTrk_pt_syst->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 4) {
            hv1oddIntTrk_pt_syst->GetXaxis()->SetTitleSize(0.06);
            hv1oddIntTrk_pt_syst->GetXaxis()->SetTitleOffset(1.12);
            hv1oddIntTrk_pt_syst->GetXaxis()->SetLabelSize(0.06);
            hv1oddIntTrk_pt_syst->GetXaxis()->SetLabelOffset(0.018);
            hv1oddIntTrk_pt_syst->GetYaxis()->SetTitleSize(0.06);
            hv1oddIntTrk_pt_syst->GetYaxis()->SetTitleOffset(1.50);
            hv1oddIntTrk_pt_syst->GetYaxis()->SetLabelSize(0.05);
            hv1oddIntTrk_pt_syst->GetYaxis()->SetLabelOffset(0.010);
        }
        if (cbin >=5) {
            hv1oddIntTrk_pt_syst->GetXaxis()->SetTitleSize(0.07);
            hv1oddIntTrk_pt_syst->GetXaxis()->SetTitleOffset(1.00);
            hv1oddIntTrk_pt_syst->GetXaxis()->SetLabelSize(0.07);
            hv1oddIntTrk_pt_syst->GetXaxis()->SetLabelOffset(0.008);
        }
        hv1oddIntTrk_pt_syst->Draw();
        grv1Syst_pt[anal][cbin]->Draw("same []2");
        grv1Stat_pt[anal][cbin]->Draw("same p");

        TPaveText * txv1oddIntTrk_pt_syst_0;
        if (cbin == 0) txv1oddIntTrk_pt_syst_0 = new TPaveText(0.24, 0.54, 0.45, 0.67,"NDC");
        else if (cbin >= 1 && cbin <= 3) txv1oddIntTrk_pt_syst_0 = new TPaveText(0.71, 0.76, 0.91, 0.88,"NDC");
        else if (cbin == 4) txv1oddIntTrk_pt_syst_0 = new TPaveText(0.73, 0.85, 0.95, 0.95,"NDC");
        else txv1oddIntTrk_pt_syst_0 = new TPaveText(0.71, 0.85, 0.91, 0.95,"NDC");
        SetTPaveTxt(txv1oddIntTrk_pt_syst_0, 18);
        txv1oddIntTrk_pt_syst_0->AddText(Form("%d-%d%%",centBins[cbin],centBins[cbin+1]));
        txv1oddIntTrk_pt_syst_0->Draw();
    }
    cv1oddIntTrk_pt_syst->cd(1);
    TPaveText * txv1oddIntTrk_pt_syst_1 = new TPaveText(0.22, 0.65, 0.81, 0.86,"NDC");
    SetTPaveTxt(txv1oddIntTrk_pt_syst_1, 18);
    txv1oddIntTrk_pt_syst_1->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1oddIntTrk_pt_syst_1->AddText("|#eta| < 2.4");
    txv1oddIntTrk_pt_syst_1->Draw();

    TPaveText * txv1oddIntTrk_pt_syst_2 = new TPaveText(0.18, 0.93, 0.58, 1.0,"NDC");
    SetTPaveTxt(txv1oddIntTrk_pt_syst_2, 18);
    txv1oddIntTrk_pt_syst_2->AddText("#bf{CMS} #it{Preliminary}");
    txv1oddIntTrk_pt_syst_2->Draw();

    cv1oddIntTrk_pt_syst->Print(Form("plots/intv1/intv1_pt/int%s/v1oddIntTrk_pt_syst_%s.png",AnalNames[anal].data(),AnalNames[anal].data()),"png");
    if (close_plots) cv1oddIntTrk_pt_syst->Close();


}
