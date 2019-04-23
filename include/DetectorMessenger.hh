// from B2a

#ifndef DETECTORMESSENGER_HH
#define DETECTORMESSENGER_HH

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/// Messenger class that defines commands for DetectorConstruction.
///
/// It implements commands:
/// - /eIrrad/det/absorberThickness value unit

class DetectorMessenger: public G4UImessenger
{
public:
  DetectorMessenger(DetectorConstruction* );
  virtual ~DetectorMessenger();
    
  virtual void SetNewValue(G4UIcommand*, G4String);
    
private:
  DetectorConstruction*  fDetectorConstruction;

  G4UIdirectory*           feIrradDirectory;
  G4UIdirectory*           fDetDirectory;

  G4UIcmdWithADoubleAndUnit* fabsorberThickCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
