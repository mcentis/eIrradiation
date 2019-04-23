// from B2a

#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction* Det)
 : G4UImessenger(),
   fDetectorConstruction(Det)
{
  feIrradDirectory = new G4UIdirectory("/eIrrad/");
  feIrradDirectory->SetGuidance("UI commands specific to this program.");

  fDetDirectory = new G4UIdirectory("/eIrrad/det/");
  fDetDirectory->SetGuidance("Detector construction control");

  fabsorberThickCmd = new G4UIcmdWithADoubleAndUnit("/eIrrad/det/absorberThickness",this);
  fabsorberThickCmd->SetGuidance("Define the thickness of the absorber for the simulation");
  fabsorberThickCmd->SetParameterName("absThickness",false);
  fabsorberThickCmd->SetUnitCategory("Length");
  fabsorberThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete fabsorberThickCmd;
  delete feIrradDirectory;
  delete fDetDirectory;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{

  if( command == fabsorberThickCmd ) {
    fDetectorConstruction->SetAbsThickness(fabsorberThickCmd->GetNewDoubleValue(newValue));
  }   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
