// from AnaEx01

#ifndef HISTOMANAGER_HH
#define HISTOMANAGER_HH

#include "globals.hh"

#include "g4root.hh"
//#include "g4csv.hh"
//#include "g4xml.hh"

class HistoManagerMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
public:
  HistoManager();
  ~HistoManager();
  
  void Book();
  void Save();

  void SetOutFileName(G4String name) {fOutFileName = name;};
  
private:
  HistoManagerMessenger* fMessenger;
  G4bool fFactoryOn;    
  G4String fOutFileName;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

