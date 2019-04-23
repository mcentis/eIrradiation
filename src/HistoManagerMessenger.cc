// from DetectorConstructionMessenger

#include "HistoManagerMessenger.hh"
#include "HistoManager.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManagerMessenger::HistoManagerMessenger(HistoManager* HM)
 : G4UImessenger(),
   fHistoManager(HM)
{
  // no need for these two lines, they are defined in detector construction messenger
  // feIrradDirectory = new G4UIdirectory("/eIrrad/");
  // feIrradDirectory->SetGuidance("UI commands specific to this program.");

  fHistoDirectory = new G4UIdirectory("/eIrrad/histo/");
  fHistoDirectory->SetGuidance("HistoManager control");

  fFileNameCmd = new G4UIcmdWithAString("/eIrrad/histo/outFileName",this);
  fFileNameCmd->SetGuidance("Output file name, without extension");
  fFileNameCmd->SetParameterName("outFileName",false);
  fFileNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManagerMessenger::~HistoManagerMessenger()
{
  delete fFileNameCmd;
  // delete feIrradDirectory;
  delete fHistoDirectory;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManagerMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{

  if( command == fFileNameCmd ) {
    fHistoManager->SetOutFileName(newValue);
  }   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
