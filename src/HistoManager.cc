// from AnaEx01

#include "HistoManager.hh"
#include "HistoManagerMessenger.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
 : fFactoryOn(false)
{
  fOutFileName = "eIrrad";
  fMessenger = new HistoManagerMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
      
  // Create directories 
  analysisManager->SetHistoDirectoryName("histograms");
  analysisManager->SetNtupleDirectoryName("trees");
    
  // Open an output file
  //
  G4bool fileOpen = analysisManager->OpenFile(fOutFileName);
  if (! fileOpen) {
    G4cerr << "\n---> HistoManager::Book(): cannot open " 
           << analysisManager->GetFileName() << G4endl;
    return;
  }
  
  // Create histograms.
  // Histogram ids are generated automatically starting from 0.
  // The start value can be changed by:
  // analysisManager->SetFirstHistoId(1);  
  
  // id = 0
  analysisManager->CreateH1("EkinEplusminus","Kinetic energy of electrons or positrons", 5550, 0., 5.55*MeV);
  analysisManager->SetH1XAxisTitle(0, "Energy [MeV]");
  analysisManager->SetH1YAxisTitle(0, "Entries");
  // id = 1
  analysisManager->CreateH1("Egammas","Energy of gammas", 5550, 0., 5.55*MeV);
  analysisManager->SetH1XAxisTitle(1, "Energy [MeV]");
  analysisManager->SetH1YAxisTitle(1, "Entries");
  // id = 2
  analysisManager->CreateH1("EkinOthers","Kinetic energy of other particles", 5550, 0., 5.55*MeV);
  analysisManager->SetH1XAxisTitle(2, "Energy [MeV]");
  analysisManager->SetH1YAxisTitle(2, "Entries");

  // Create ntuples.
  // Ntuples ids are generated automatically starting from 0.
  // The start value can be changed by:
  // analysisManager->SetFirstMtupleId(1);  
  
  // Create 1st ntuple (id = 0)
  analysisManager->CreateNtuple("particles", "All the particles passing through the sensitive volume");
  analysisManager->CreateNtupleIColumn("event"); // column Id = 0
  analysisManager->CreateNtupleIColumn("track"); // column Id = 1
  analysisManager->CreateNtupleIColumn("pdgEncoding"); // column Id = 2
  analysisManager->CreateNtupleDColumn("Ekin"); // column Id = 3
  analysisManager->CreateNtupleDColumn("x"); // column Id = 4
  analysisManager->CreateNtupleDColumn("y"); // column Id = 5
  analysisManager->CreateNtupleDColumn("z"); // column Id = 6
  analysisManager->FinishNtuple();

  fFactoryOn = true;       

  G4cout << "\n----> Output file is open in " 
         << analysisManager->GetFileName() << "." 
         << analysisManager->GetFileType() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Save()
{
  if (! fFactoryOn) return;
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();    
  analysisManager->Write();
  analysisManager->CloseFile(); 
   
  G4cout << "\n----> Histograms and ntuples are saved\n" << G4endl;
      
  delete G4AnalysisManager::Instance();
  fFactoryOn = false;
}

