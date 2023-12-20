void dEdx()
{
  const Int_t nev = 1000;
  const Double_t density = 8.960;//g cm3
  const Double_t mass = 0.1057;
  const Double_t length = 0.2;
  app->InitMC("geometry/cubox");
  app->SetPrimaryPDG(-13);

  TH1F* hloss = new TH1F("hloss","; -dE [MeV]",100,0,10);
  TGraph* gdEdx =  new TGraph();
  double momentum = 1;
  for(int i = 0 ; i < nev ; ++i) {
    app->SetPrimaryMomentum(momentum);
    //hprim->Reset();
    app->RunMC(1,!i);
    //get energy deposited in our box
    double loss = app->depEinNode("/EXPH_1/CALB_1");
    loss *= 1000; //MeV
    hloss->Fill(loss);
    loss = loss / density /length; //MeV g-1 cm2
    std::cout << "betagamma:" << momentum/mass << "     -dE/dex:" << loss << '\n';
  }
  gdEdx->SetPoint(gdEdx->GetN(),momentum/mass,hloss->GetMean() / density /length);
  std::cout << hloss->GetMean()  / density /length << '\n';
  TCanvas* c1 = new TCanvas("c1");
  hloss->Draw();
  TCanvas* c2 = new TCanvas("c2");
  c2->Clear();
  c2->cd();
  c2->SetLogx();
  c2->SetLogy();
  gdEdx->Draw("A*");
  gdEdx->GetXaxis()->SetTitle("#beta#gamma");
  gdEdx->GetYaxis()->SetTitle("-dE/dx [MeV g^{-1} cm^{2}]");
  c2->Modified();
  c2->Update();
}
