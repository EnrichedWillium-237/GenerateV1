# include "TFile.h"
# include "TGraphErrors.h"
# include "TCanvas.h"
# include "TF1.h"
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

TF1 * fv1odd;
TF1 * fv1even;

void SystIntV1_eta()
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

    // calculate ratios
    for (int i = 0; i<nanals; i++) {
        for (int cbin = 0; cbin<ncentbins; cbin++) {
            for (int j = 0; j<6; j++) {
                double v1odd_pos = v1odd_eta[i][cbin]->GetBinContent(12-j);
                double v1odd_neg = v1odd_eta[i][cbin]->GetBinContent(j+1);
                double v1odd_pos_err = v1odd_eta[i][cbin]->GetBinError(12-j);
                double v1odd_neg_err = v1odd_eta[i][cbin]->GetBinError(j+1);

                double v1odd_rat = v1odd_pos/v1odd_neg;
                double v1odd_rat_err = v1odd_rat*sqrt( pow(v1odd_pos_err/v1odd_pos,2) + pow(v1odd_neg_err/v1odd_neg,2) );
                ratiov1odd_eta[i][cbin]->SetBinContent(j+1, v1odd_rat);
                ratiov1odd_eta[i][cbin]->SetBinError(j+1, v1odd_rat_err);

                double v1even_pos = v1even_eta[i][cbin]->GetBinContent(12-j);
                double v1even_neg = v1even_eta[i][cbin]->GetBinContent(j+1);
                double v1even_pos_err = v1even_eta[i][cbin]->GetBinError(12-j);
                double v1even_neg_err = v1even_eta[i][cbin]->GetBinError(j+1);

                double v1even_rat = v1even_pos/v1even_neg;
                double v1even_rat_err = v1even_rat*sqrt( pow(v1even_pos_err/v1even_pos,2) + pow(v1even_neg_err/v1even_neg,2) );
                ratiov1even_eta[i][cbin]->SetBinContent(j+1, v1even_rat);
                ratiov1even_eta[i][cbin]->SetBinError(j+1, v1even_rat_err);

            }
            if (i<=7) ratiov1odd_eta[i][cbin]->Scale(-1);
        }
    }

    //-- plotting options

    for (int i = 0; i<nanals; i++) {
        for (int cbin = 0; cbin<ncentbins; cbin++) {
            ratiov1odd_eta[i][cbin]->SetMarkerColor(kBlack);
            ratiov1odd_eta[i][cbin]->SetLineColor(kBlack);
            ratiov1odd_eta[i][cbin]->SetMarkerStyle(21);
            ratiov1odd_eta[i][cbin]->SetMarkerSize(1.1);

            ratiov1even_eta[i][cbin]->SetMarkerColor(kBlack);
            ratiov1even_eta[i][cbin]->SetLineColor(kBlack);
            ratiov1even_eta[i][cbin]->SetMarkerStyle(21);
            ratiov1even_eta[i][cbin]->SetMarkerSize(1.1);
        }
    }


    //-- make plots
    if (!fopen("plots","r")) system("mkdir plots");
    if (!fopen("plots/intv1","r")) system("mkdir plots/intv1");
    if (!fopen("plots/intv1/intv1_eta","r")) system("mkdir plots/intv1/intv1_eta");

    int anal; // choice of analysis

    TLine * lnetaRatio = new TLine(0.0, 1.0, 2.5, 1.0);
    lnetaRatio->SetLineWidth(1);


    // v1odd(+eta)/v1odd(-eta) for the HF
    anal = 7;
    if (!fopen(Form("plots/intv1/intv1_eta/int%s",AnalNames[anal].data()),"r")) system(Form("mkdir plots/intv1/intv1_eta/int%s",AnalNames[anal].data()));

    TCanvas * cv1HFoddRatio_eta = new TCanvas("cv1HFoddRatio_eta","cv1HFoddRatio_eta",1100,620);
    TH2D * hv1HFoddRatio_eta_tmp = new TH2D("hv1HFoddRatio_eta_tmp", "", 40, 0, 2.5, 40, -10, 10);
    hv1HFoddRatio_eta_tmp->SetTitle("");
    hv1HFoddRatio_eta_tmp->SetStats(0);
    hv1HFoddRatio_eta_tmp->SetXTitle("#eta");
    hv1HFoddRatio_eta_tmp->SetYTitle("|v_{1}(+#eta)/v_{1}(-#eta)|");
    hv1HFoddRatio_eta_tmp->GetXaxis()->SetRangeUser(0, 2.4);
    hv1HFoddRatio_eta_tmp->GetYaxis()->SetRangeUser(0.4, 1.6);
    hv1HFoddRatio_eta_tmp->SetNdivisions(509);
    cv1HFoddRatio_eta->Divide(4,2,0,0);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1HFoddRatio_eta = (TPad *) cv1HFoddRatio_eta->cd(cbin+1);
        if (gridlines) padv1HFoddRatio_eta->SetGrid();
        if (cbin == 3 || cbin == 7) padv1HFoddRatio_eta->SetRightMargin(0.02);
        if (cbin <= 3) padv1HFoddRatio_eta->SetTopMargin(0.08);
        TH1D * hv1HFoddRatio_eta = (TH1D *) hv1HFoddRatio_eta_tmp->Clone(Form("hv1HFoddRatio_eta_%c",cbin));
        if (cbin == 0) {
            hv1HFoddRatio_eta->GetYaxis()->SetTitleSize(0.07);
            hv1HFoddRatio_eta->GetYaxis()->SetTitleOffset(1.33);
            hv1HFoddRatio_eta->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 4) {
            hv1HFoddRatio_eta->GetXaxis()->CenterTitle();
            hv1HFoddRatio_eta->GetXaxis()->SetTitleSize(0.06);
            hv1HFoddRatio_eta->GetXaxis()->SetTitleOffset(1.12);
            hv1HFoddRatio_eta->GetXaxis()->SetLabelSize(0.06);
            hv1HFoddRatio_eta->GetXaxis()->SetLabelOffset(0.018);
            hv1HFoddRatio_eta->GetYaxis()->SetTitleSize(0.06);
            hv1HFoddRatio_eta->GetYaxis()->SetTitleOffset(1.50);
            hv1HFoddRatio_eta->GetYaxis()->SetLabelSize(0.05);
            hv1HFoddRatio_eta->GetYaxis()->SetLabelOffset(0.010);
        }
        if (cbin >=5) {
            hv1HFoddRatio_eta->GetXaxis()->CenterTitle();
            hv1HFoddRatio_eta->GetXaxis()->SetTitleSize(0.07);
            hv1HFoddRatio_eta->GetXaxis()->SetTitleOffset(1.00);
            hv1HFoddRatio_eta->GetXaxis()->SetLabelSize(0.07);
            hv1HFoddRatio_eta->GetXaxis()->SetLabelOffset(0.008);
        }
        hv1HFoddRatio_eta->Draw();
        lnetaRatio->Draw();
        ratiov1odd_eta[anal][cbin]->Draw("same");
        TF1 * fit1 = new TF1("fit1", "pol0", 0, 2.4);
        fit1->SetLineColor(kBlue);
        ratiov1odd_eta[anal][cbin]->Fit(fit1,"QR");
        // ratiov1odd_eta[anal][cbin]->Fit("pol0","Q",0,2.4);
        double par0 = ratiov1odd_eta[anal][cbin]->GetFunction("pol0")->GetParameter(0);
        double par0E = ratiov1odd_eta[anal][cbin]->GetFunction("pol0")->GetParError(0);
        double par0Chi2 = ratiov1odd_eta[anal][cbin]->GetFunction("pol0")->GetChisquare();

        TPaveText * txtxv1HFoddRatio_eta_fit;
        if (cbin == 0) txtxv1HFoddRatio_eta_fit = new TPaveText(0.24, 0.07, 0.74, 0.27,"NDC");
        else if (cbin >= 1 && cbin <= 3) txtxv1HFoddRatio_eta_fit = new TPaveText(0.08, 0.07, 0.56, 0.27,"NDC");
        else if (cbin == 4) txtxv1HFoddRatio_eta_fit = new TPaveText(0.24, 0.21, 0.74, 0.39,"NDC");
        else txtxv1HFoddRatio_eta_fit = new TPaveText(0.08, 0.21, 0.56, 0.39,"NDC");
        SetTPaveTxt(txtxv1HFoddRatio_eta_fit, 16);
        txtxv1HFoddRatio_eta_fit->AddText(Form("mean: %0.4f #pm %0.4f",par0,par0E));
        txtxv1HFoddRatio_eta_fit->AddText(Form("#chi^{2}: %0.4f",par0Chi2));
        txtxv1HFoddRatio_eta_fit->Draw();

        TPaveText * txv1HFoddRatio_eta;
        if (cbin == 0) txv1HFoddRatio_eta = new TPaveText(0.75, 0.78, 0.93, 0.87,"NDC");
        else if (cbin >= 1 && cbin <= 3) txv1HFoddRatio_eta = new TPaveText(0.68, 0.78, 0.86, 0.87,"NDC");
        else if (cbin == 4) txv1HFoddRatio_eta = new TPaveText(0.75, 0.86, 0.93, 0.95,"NDC");
        else txv1HFoddRatio_eta = new TPaveText(0.68, 0.86, 0.86, 0.95,"NDC");
        SetTPaveTxt(txv1HFoddRatio_eta, 18);
        txv1HFoddRatio_eta->AddText(Form("%d-%d%%",centBins[cbin],centBins[cbin+1]));
        txv1HFoddRatio_eta->Draw();
    }
    cv1HFoddRatio_eta->cd(1);
    TPaveText * txv1HFoddRatio_eta_1 = new TPaveText(0.18, 0.93, 0.58, 1.0,"NDC");
    SetTPaveTxt(txv1HFoddRatio_eta_1, 18);
    txv1HFoddRatio_eta_1->AddText("#bf{CMS} #it{Preliminary}");
    txv1HFoddRatio_eta_1->Draw();

    cv1HFoddRatio_eta->Print(Form("plots/intv1/intv1_eta/int%s/v1HFoddRatio_eta_%s.png",AnalNames[anal].data(),AnalNames[anal].data()),"png");
    if (close_plots) cv1HFoddRatio_eta->Close();



    // v1even(+eta)/v1even(-eta) for the HF
    anal = 7;
    if (!fopen(Form("plots/intv1/intv1_eta/int%s",AnalNames[anal].data()),"r")) system(Form("mkdir plots/intv1/intv1_eta/int%s",AnalNames[anal].data()));

    TCanvas * cv1HFevenRatio_eta = new TCanvas("cv1HFevenRatio_eta","cv1HFevenRatio_eta",1100,620);
    TH1D * hv1HFevenRatio_eta_tmp = new TH1D("hv1HFevenRatio_eta_tmp", "", 40, 0, 2.5);
    hv1HFevenRatio_eta_tmp->SetTitle("");
    hv1HFevenRatio_eta_tmp->SetStats(0);
    hv1HFevenRatio_eta_tmp->SetXTitle("#eta");
    hv1HFevenRatio_eta_tmp->SetYTitle("|v_{1}(+#eta)/v_{1}(-#eta)|");
    hv1HFevenRatio_eta_tmp->GetXaxis()->SetRangeUser(0, 2.4);
    hv1HFevenRatio_eta_tmp->GetYaxis()->SetRangeUser(0.95, 1.05);
    hv1HFevenRatio_eta_tmp->SetNdivisions(509);
    cv1HFevenRatio_eta->Divide(4,2,0,0);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padv1HFevenRatio_eta = (TPad *) cv1HFevenRatio_eta->cd(cbin+1);
        if (gridlines) padv1HFevenRatio_eta->SetGrid();
        if (cbin == 3 || cbin == 7) padv1HFevenRatio_eta->SetRightMargin(0.02);
        if (cbin <= 3) padv1HFevenRatio_eta->SetTopMargin(0.08);
        TH1D * hv1HFevenRatio_eta = (TH1D *) hv1HFevenRatio_eta_tmp->Clone(Form("hv1HFevenRatio_eta_%c",cbin));
        if (cbin == 0) {
            hv1HFevenRatio_eta->GetYaxis()->SetTitleSize(0.07);
            hv1HFevenRatio_eta->GetYaxis()->SetTitleOffset(1.33);
            hv1HFevenRatio_eta->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 4) {
            hv1HFevenRatio_eta->GetXaxis()->CenterTitle();
            hv1HFevenRatio_eta->GetXaxis()->SetTitleSize(0.06);
            hv1HFevenRatio_eta->GetXaxis()->SetTitleOffset(1.12);
            hv1HFevenRatio_eta->GetXaxis()->SetLabelSize(0.06);
            hv1HFevenRatio_eta->GetXaxis()->SetLabelOffset(0.018);
            hv1HFevenRatio_eta->GetYaxis()->SetTitleSize(0.06);
            hv1HFevenRatio_eta->GetYaxis()->SetTitleOffset(1.50);
            hv1HFevenRatio_eta->GetYaxis()->SetLabelSize(0.05);
            hv1HFevenRatio_eta->GetYaxis()->SetLabelOffset(0.010);
        }
        if (cbin >=5) {
            hv1HFevenRatio_eta->GetXaxis()->CenterTitle();
            hv1HFevenRatio_eta->GetXaxis()->SetTitleSize(0.07);
            hv1HFevenRatio_eta->GetXaxis()->SetTitleOffset(1.00);
            hv1HFevenRatio_eta->GetXaxis()->SetLabelSize(0.07);
            hv1HFevenRatio_eta->GetXaxis()->SetLabelOffset(0.008);
        }
        hv1HFevenRatio_eta->Draw();
        lnetaRatio->Draw();
        ratiov1even_eta[anal][cbin]->Draw("same");

        TPaveText * txv1HFevenRatio_eta;
        if (cbin == 0) txv1HFevenRatio_eta = new TPaveText(0.75, 0.78, 0.93, 0.87,"NDC");
        else if (cbin >= 1 && cbin <= 3) txv1HFevenRatio_eta = new TPaveText(0.68, 0.78, 0.86, 0.87,"NDC");
        else if (cbin == 4) txv1HFevenRatio_eta = new TPaveText(0.75, 0.86, 0.93, 0.95,"NDC");
        else txv1HFevenRatio_eta = new TPaveText(0.68, 0.86, 0.86, 0.95,"NDC");
        SetTPaveTxt(txv1HFevenRatio_eta, 18);
        txv1HFevenRatio_eta->AddText(Form("%d-%d%%",centBins[cbin],centBins[cbin+1]));
        txv1HFevenRatio_eta->Draw();
    }
    cv1HFevenRatio_eta->cd(1);
    TPaveText * txv1HFevenRatio_eta_1 = new TPaveText(0.18, 0.93, 0.58, 1.0,"NDC");
    SetTPaveTxt(txv1HFevenRatio_eta_1, 18);
    txv1HFevenRatio_eta_1->AddText("#bf{CMS} #it{Preliminary}");
    txv1HFevenRatio_eta_1->Draw();

    cv1HFevenRatio_eta->Print(Form("plots/intv1/intv1_eta/int%s/v1HFevenRatio_eta_%s.png",AnalNames[anal].data(),AnalNames[anal].data()),"png");
    if (close_plots) cv1HFevenRatio_eta->Close();

}
