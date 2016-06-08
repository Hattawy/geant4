// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4RhoZero.hh,v 1.2 1999/04/13 08:38:43 kurasige Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// 
// ------------------------------------------------------------
//      GEANT 4 class header file
//
//      For information related to this code contact:
//      CERN, CN Division, ASD group
//      History: first implementation,  Hisaya Kurashige, 8 June 1998
// **********************************************************************
//  Change both methods to get the pointer into non-inlined H.Kurashige 4 Aug. 1998
// ------------------------------------------------------------

// Each class inheriting from G4VMeson
// corresponds to a particle type; one and only one
// instance for each class is guaranteed.

#ifndef G4RhoZero_h
#define G4RhoZero_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4VMeson.hh"

// ######################################################################
// ###                         RhoZero                                ###
// ######################################################################

class G4RhoZero : public G4VMeson
{
 private:
   static G4RhoZero theRhoZero;
   static G4double  theRhoZeroLengthCut;
   static G4double* theRhoZeroKineticEnergyCuts;

 private: // constructors are hide as private  
   G4RhoZero(
       const G4String&     aName,        G4double            mass,
       G4double            width,        G4double            charge,   
       G4int               iSpin,        G4int               iParity,    
       G4int               iConjugation, G4int               iIsospin,   
       G4int               iIsospin3,    G4int               gParity,
       const G4String&     pType,        G4int               lepton,      
       G4int               baryon,       G4int               encoding,
       G4bool              stable,       G4double            lifetime,
       G4DecayTable        *decaytable
   );

 public:
   virtual ~G4RhoZero(){}
 
   static G4RhoZero*      RhoZeroDefinition();
   static G4RhoZero*      RhoZero();
   static G4double GetCuts() {return theRhoZeroLengthCut;}   
   static G4double* GetCutsInEnergy() {return theRhoZeroKineticEnergyCuts;};

   virtual void        SetCuts(G4double aCut);
};

#endif




