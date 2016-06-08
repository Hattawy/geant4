// This code implementation is the intellectual property of
// neutron_hp -- header file
// J.P. Wellisch, Nov-1996
// A prototype of the low energy neutron transport model.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4NeutronHPHe3InelasticFS.hh,v 1.3 1999/07/02 09:59:09 johna Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
#ifndef G4NeutronHPHe3InelasticFS_h
#define G4NeutronHPHe3InelasticFS_h 1

#include "globals.hh"
#include "G4Track.hh"
#include "G4ParticleChange.hh"
#include "G4NeutronHPInelasticCompFS.hh"
#include "G4NeutronHPAngular.hh"
#include "G4NeutronHPEnergyDistribution.hh"
#include "G4NeutronHPEnAngCorrelation.hh"
#include "G4NeutronHPPhotonDist.hh"

class G4NeutronHPHe3InelasticFS : public G4NeutronHPInelasticCompFS
{
  public:
  
  G4NeutronHPHe3InelasticFS(){}
  ~G4NeutronHPHe3InelasticFS(){}
  void Init (G4double A, G4double Z, G4String & dirName, G4String & aFSType);
  G4ParticleChange * ApplyYourself(const G4Track & theTrack);
  G4NeutronHPFinalState * New() 
  {
   G4NeutronHPHe3InelasticFS * theNew = new G4NeutronHPHe3InelasticFS;
   return theNew;
  }
  
  private:
  
};
#endif