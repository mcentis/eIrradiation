// from B2a

#include "SensSD.hh"
#include "HistoManager.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4Event.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SensSD::SensSD(const G4String& name,
                         const G4String& hitsCollectionName) 
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SensSD::~SensSD() 
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SensSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection

  fHitsCollection 
    = new SensHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce

  G4int hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool SensSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{  

  // make sure that this is the first step in the volume
  if(aStep->IsFirstStepInVolume() == false)
    return false;

  // event ID
  const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();
  if(!evt) return false;
  G4int eID = evt->GetEventID();

  const G4Track* track = aStep->GetTrack();
  
  SensHit* newHit = new SensHit();
  newHit->SetEvtID(eID);
  newHit->SetTrackID(track->GetTrackID());
  newHit->SetEkin(track->GetKineticEnergy());
  newHit->SetPDGencoding(track->GetParticleDefinition()->GetPDGEncoding());
  newHit->SetPos(aStep->GetPreStepPoint()->GetPosition());

  fHitsCollection->insert( newHit );

  //newHit->Print();

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SensSD::EndOfEvent(G4HCofThisEvent*)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance(); 
  
  G4int nofHits = fHitsCollection->entries();
  if(nofHits == 0)
    return;

  G4int pdgenc = 0;
  G4double energy = 0;
  G4int histId = -1;
  for(G4int i=0; i < nofHits; i++){
    pdgenc = (*fHitsCollection)[i]->GetPDGencoding();
    energy = (*fHitsCollection)[i]->GetEkin();

    // fill ntuple (id = 0)
    analysisManager->FillNtupleIColumn(0, 0, (*fHitsCollection)[i]->GetEvtID());
    analysisManager->FillNtupleIColumn(0, 1, (*fHitsCollection)[i]->GetTrackID());
    analysisManager->FillNtupleIColumn(0, 2, pdgenc);
    analysisManager->FillNtupleDColumn(0, 3, energy);
    analysisManager->FillNtupleDColumn(0, 4, (*fHitsCollection)[i]->GetPos()[0]);
    analysisManager->FillNtupleDColumn(0, 5, (*fHitsCollection)[i]->GetPos()[1]);
    analysisManager->FillNtupleDColumn(0, 6, (*fHitsCollection)[i]->GetPos()[2]);
    analysisManager->AddNtupleRow(0);

    // fill histograms
    if(pdgenc == 11 || pdgenc == -11) // electron or positron
      histId = 0;
    else if(pdgenc == 22) // gamma
      histId = 1;
    else
      histId = 2; // all other particles

    analysisManager->FillH1(histId, energy);
  }
  
  if ( verboseLevel>1 ) { 
    //G4int nofHits = fHitsCollection->entries();
     G4cout << G4endl
            << "-------->Hits Collection: in this event they are " << nofHits 
            << " hits in the silicon detector: " << G4endl;
     for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
