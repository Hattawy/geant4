//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4eBremsstrahlung52.hh,v 1.2 2004/11/10 08:53:18 vnivanch Exp $
// GEANT4 tag $Name: geant4-07-00-cand-01 $
//
// 
//      ------------ G4eBremsstrahlung5252 physics process ------
//                     by Laszlo Urban, 24 July 1996
// 
// 01-10-96 new type G4OrderedTable;  ComputePartialSumSigma()
// 20-03-97 new energy loss+ionisation+brems scheme, L.Urban
// 01-09-98 new method  PrintInfo() 
// 10-02-00 modifications , new e.m. structure, L.Urban
// 07-08-00 new cross section/en.loss parametrisation, LPM flag , L.Urban
// 09-08-01 new methods Store/Retrieve PhysicsTable (mma)
// 19-09-01 come back to previous process name "eBrem"
// 29-10-01 all static functions no more inlined (mma)
// 16-01-03 Migrade to cut per region (V.Ivanchenko)
// 08-08-03 This class is frozen at the release 5.2 (V.Ivanchenko)
// 09-11-04 Remove Store/Retrieve tables (V.Ivantchenko)
//
// ------------------------------------------------------------

// Class description
//
// This class manages the bremsstrahlung for e-/e+
// it inherites from G4VContinuousDiscreteProcess via G4VeEnergyLoss.
//
// Class description - end

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef G4eBremsstrahlung52_h
#define G4eBremsstrahlung52_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "Randomize.hh"
#include "G4VeEnergyLoss.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4OrderedTable.hh"
#include "G4PhysicsTable.hh"
#include "G4PhysicsLogVector.hh"
#include "G4MaterialCutsCouple.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class G4eBremsstrahlung52 : public G4VeEnergyLoss

{
  public:

     G4eBremsstrahlung52(const G4String& processName = "eBrem");

    ~G4eBremsstrahlung52();

     G4bool IsApplicable(const G4ParticleDefinition&);

     void PrintInfoDefinition();

     void BuildPhysicsTable(const G4ParticleDefinition& ParticleType);

     void BuildLossTable(const G4ParticleDefinition& ParticleType);

     void BuildLambdaTable(const G4ParticleDefinition& ParticleType);

     G4double GetMeanFreePath(const G4Track& track,
                              G4double previousStepSize,
                              G4ForceCondition* condition );

     G4VParticleChange *PostStepDoIt(const G4Track& track,
                                     const G4Step&  step);

     G4double GetLambda(G4double KineticEnergy, const G4MaterialCutsCouple* couple);

  protected:

     G4double ComputeMeanFreePath( const G4ParticleDefinition* ParticleType,
                                         G4double KineticEnergy,
                                   const G4MaterialCutsCouple* couple);

     void ComputePartialSumSigma( const G4ParticleDefinition* ParticleType,
                                        G4double KineticEnergy,
                                  const G4MaterialCutsCouple* couple);

     virtual G4double ComputeCrossSectionPerAtom(
                                  const G4ParticleDefinition* ParticleType,
                                        G4double KineticEnergy,
                                        G4double AtomicNumber,
                                        G4double GammaEnergyCut);

  private:

     G4double ComputeBremLoss(G4double Z,G4double natom,G4double T,
                              G4double Cut,G4double x);

     G4double ComputePositronCorrFactorLoss(G4double AtomicNumber,
                                            G4double KineticEnergy,
                                            G4double GammaEnergyCut);

     G4double ComputePositronCorrFactorSigma(G4double AtomicNumber,
                                             G4double KineticEnergy,
                                             G4double GammaEnergyCut);

     G4Element* SelectRandomAtom(const G4MaterialCutsCouple* couple) const;

     G4double ScreenFunction1(G4double ScreenVariable);

     G4double ScreenFunction2(G4double ScreenVariable);

     G4double SupressionFunction(const G4Material* aMaterial,
                                  G4double KineticEnergy,
                                  G4double GammaEnergy) ;

     G4eBremsstrahlung52 & operator=(const G4eBremsstrahlung52 &right);

     G4eBremsstrahlung52(const G4eBremsstrahlung52&);

  protected:

     virtual G4double SecondaryEnergyThreshold(size_t index);

  private:

     G4PhysicsTable* theMeanFreePathTable;

     G4OrderedTable PartialSumSigma;       // partial sum of total crosssection

     static G4double LowerBoundLambda;     // low  energy limit of crossection table
     static G4double UpperBoundLambda;     // high energy limit of crossection table
     static G4int    NbinLambda;           // number of bins in the tables

     G4double MinThreshold;                // minimun value for the production threshold

     G4double LowestKineticEnergy,HighestKineticEnergy; // bining of the Eloss table
     G4int    TotBin;                                   // (from G4VeEnergyLoss)

     static G4double probsup;
     static G4bool LPMflag;

     const std::vector<G4double>* secondaryEnergyCuts;

  public:

     static void SetLowerBoundLambda(G4double val);
     static void SetUpperBoundLambda(G4double val);
     static void SetNbinLambda(G4int n);
     static G4double GetLowerBoundLambda();
     static G4double GetUpperBoundLambda();
     static G4int GetNbinLambda();

     static void   SetLPMflag(G4bool val);
     static G4bool GetLPMflag();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4eBremsstrahlung52.icc"
  
#endif