// from B2a

#ifndef SENSHIT_HH
#define SENSHIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

/// hit class
///
/// It defines data members to store the hit data
/// eventID, trackID, particleType, energy, position

class SensHit : public G4VHit
{
public:
  SensHit();
  SensHit(const SensHit&);
  virtual ~SensHit();

  // operators
  const SensHit& operator=(const SensHit&);
  G4int operator==(const SensHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  // methods from base class
  virtual void Draw();
  virtual void Print();

  // Set methods
  void SetEvtID      (G4int evt)        { fEvtID = evt; };
  void SetTrackID    (G4int track)      { fTrackID = track; };
  void SetPDGencoding(G4int enc)        { fPDGencoding = enc; };
  void SetEkin       (G4double e)      { fEkin = e; };
  void SetPos        (G4ThreeVector xyz){ fPos = xyz; };

  // Get methods
  G4int GetEvtID() const       { return fEvtID; };
  G4int GetTrackID() const     { return fTrackID; };
  G4int GetPDGencoding() const { return fPDGencoding; };
  G4double GetEkin() const     { return fEkin; };
  G4ThreeVector GetPos() const { return fPos; };

private:

  G4int fEvtID;  
  G4int fTrackID;
  G4int fPDGencoding; // particle type
  G4double fEkin;     // particle energy
  G4ThreeVector fPos; // position
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<SensHit> SensHitsCollection;

extern G4ThreadLocal G4Allocator<SensHit>* SensHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* SensHit::operator new(size_t)
{
  if(!SensHitAllocator)
      SensHitAllocator = new G4Allocator<SensHit>;
  return (void *) SensHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void SensHit::operator delete(void *hit)
{
  SensHitAllocator->FreeSingle((SensHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
