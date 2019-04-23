// from B2a

#include "SensHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<SensHit>* SensHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SensHit::SensHit()
 : G4VHit(),
   fEvtID(-1),
   fTrackID(-1),
   fPDGencoding(0),
   fEkin(0.),
   fPos(G4ThreeVector())
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SensHit::~SensHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SensHit::SensHit(const SensHit& right)
  : G4VHit()
{
  fEvtID       = right.fEvtID;
  fTrackID     = right.fTrackID;
  fPDGencoding = right.fPDGencoding;
  fEkin        = right.fEkin;
  fPos         = right.fPos;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const SensHit& SensHit::operator=(const SensHit& right)
{
  fEvtID       = right.fEvtID;
  fTrackID     = right.fTrackID;
  fPDGencoding = right.fPDGencoding;
  fEkin        = right.fEkin;
  fPos         = right.fPos;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int SensHit::operator==(const SensHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SensHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(fPos);
    circle.SetScreenSize(2.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SensHit::Print()
{
  G4cout
     << "  trackID: " << fTrackID
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
