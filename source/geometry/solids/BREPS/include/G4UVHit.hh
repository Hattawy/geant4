// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4UVHit.hh,v 1.1 1999/01/07 16:07:37 gunter Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
#ifndef __G4UV_Hit
#define __G4UV_Hit

#include "globals.hh"

class G4UVHit
{
public:
    G4UVHit * next;
    int sub;
    G4double u, v;
    G4UVHit(){u=-1;next=this;}	
    G4UVHit(G4double u_hit, G4double v_hit){u = u_hit; v = v_hit;}
};

#endif