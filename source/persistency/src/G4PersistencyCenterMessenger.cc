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
// File: G4PersistencyCenterMessenger.cc
//
// History:
//   01.07.18  Youhei Morita  Initial creation (with "fadsclass")

#include "G4PersistencyCenterMessenger.hh"

// Implementation of Constructor #1
G4PersistencyCenterMessenger::G4PersistencyCenterMessenger(G4PersistencyCenter* p)
 : pc(p)
{
  G4std::string name = "/persistency/";
  directory=new G4UIdirectory(name.c_str());
  directory->SetGuidance("Control commands for Persistency package");

  G4std::string cmd = name + "verbose";

  verboseCmd = new G4UIcmdWithAnInteger(cmd.c_str(),this);
  verboseCmd->SetGuidance("Set the verbose level of G4PersistencyManager.");
  verboseCmd->SetGuidance(" 0 : Silent (default)");
  verboseCmd->SetGuidance(" 1 : Display main topics");
  verboseCmd->SetGuidance(" 2 : Display event-level topics");
  verboseCmd->SetGuidance(" 3 : Display debug information");
  verboseCmd->SetParameterName("level",true);
  verboseCmd->SetDefaultValue(0);
  verboseCmd->SetRange("level >=0 && level <=3");

  G4std::string vname = name + "select";

  cmd = vname;
  select = new G4UIcmdWithAString(cmd.c_str(),this);
  select->SetGuidance("Selection of a persistency package");
  select->SetParameterName("Persistency package name", true, true);
  select->SetCandidates("ODBMS ROOT None");

  vname = name + "store/";

  G4UIcommand* directory;

  directory = new G4UIdirectory(vname.c_str());
  directory->SetGuidance("Specifiy object types for store");

  wrObj.push_back("HepMC");
  wrObj.push_back("MCTruth");
  wrObj.push_back("Hits");

  G4std::string guidance;
  int i;

  for ( i = 0; i < 3; i++ )
  {
    cmd = vname + wrObj[i];
    guidance = "Store " + wrObj[i] + " objects for output";
    storeObj.push_back(new G4UIcmdWithAString(cmd.c_str(),this));
    storeObj[i]->SetGuidance(guidance.c_str());
    if ( wrObj[i] == "HepMC" ) {
      storeObj[i]->SetCandidates("on off recycle");
    } else {
      storeObj[i]->SetCandidates("on off");
    }
  }

  vname += "using/";
  directory = new G4UIdirectory(vname.c_str());
  directory->SetGuidance("Select I/O manager for store");

  cmd = vname + "hitIO";
  regHitIO = new G4UIcmdWithAString(cmd.c_str(),this);
  regHitIO->SetGuidance("Resiter Hits I/O Manager");
  regHitIO->SetParameterName("Name of Hits I/O Manager", true, true);

  vname = name + "set/";
  directory = new G4UIdirectory(vname.c_str());
  directory->SetGuidance("Set various parameters"); 

  vname += "writeFile/";
  directory = new G4UIdirectory(vname.c_str());
  directory->SetGuidance("Set output file names for object types");

  for ( i = 0; i < 3; i++ )
  {
    cmd = vname + wrObj[i];
    guidance = "Set an output file name for " + wrObj[i] + ".";
    setWrFile.push_back(new G4UIcmdWithAString(cmd.c_str(),this));
    setWrFile[i]->SetGuidance(guidance.c_str());
    setWrFile[i]->SetParameterName("file name", true, true);
  }

  vname = name + "set/ReadFile/";
  directory = new G4UIdirectory(vname.c_str());
  directory->SetGuidance("Set input file names for object types");

  rdObj.push_back("Hits");

  cmd = vname + rdObj[0];
  guidance = "Set an input file name for " + rdObj[0] + ".";
  setRdFile.push_back(new G4UIcmdWithAString(cmd.c_str(),this));
  setRdFile[0]->SetGuidance(guidance.c_str());
  setRdFile[0]->SetParameterName("file name", true, true);

  cmd = name + "printall";
  printAll = new G4UIcmdWithoutParameter(cmd.c_str(),this);
  printAll->SetGuidance("Print all parameters.");

}

// Implementation of Destructor #1
G4PersistencyCenterMessenger::~G4PersistencyCenterMessenger()
{
  delete directory;
  delete verboseCmd;
  delete select;
  delete regHitIO;
  for ( int i = 0; i < 3; i++ )
  {
    delete storeObj[i];
    delete setWrFile[i];
  }
  delete setRdFile[0];
  delete printAll;
}

// Implementation of SetNewValue
void G4PersistencyCenterMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{
  if (command==verboseCmd)
  {
    pc->SetVerboseLevel(verboseCmd->GetNewIntValue(newValues));
  }
  else if (command==select)
  {
    pc->SelectSystem(newValues);
  }
  else if (command==regHitIO)
  {
    pc->AddHCIOmanager(PopWord(newValues,1," "),PopWord(newValues,2," "));
  }
  else if (command==setRdFile[0])
  {
    pc -> SetReadFile ( rdObj[0],newValues);
  }
  else if (command==printAll)
  {
    pc->PrintAll();
  }
  else
  {
    for( int i=0; i<3; i++ ) {
      if( command==storeObj[i] )
      {
        StoreMode mode = kOff;
        if( newValues == "on" ) {
          mode = kOn;
        } else if ( newValues == "off" ) {
          mode = kOff;
        } else if ( newValues == "recycle" ) {
          mode = kRecycle;
        } else {
          G4cerr << "Unrecognized keyword - \"" << newValues << "\"."
                 << G4endl;
        }
        pc->SetStoreMode(wrObj[i],mode);
        break;
      }
      else if( command==setWrFile[i] )
      {
        pc->SetWriteFile(wrObj[i],newValues);
        break;
      }
    }
  }
}

// Implementation of GetCurrentValue
G4String G4PersistencyCenterMessenger::GetCurrentValue(G4UIcommand* command)
{
  G4String s="Undefined";

  if (command==select)
  {
    return pc->VerboseLevel();
  }
  else if (command==select)
  {
    return pc->CurrentSystem();
  }
  else if (command==regHitIO)
  {
    return pc->CurrentHCIOmanager();
  }
  else if (command==setRdFile[0])
  {
    return pc->CurrentReadFile(rdObj[0]);
  }
  else
  {
    for( int i=0; i<3; i++ ) {
      if( command==storeObj[i] )
      {
        switch (pc->CurrentStoreMode(wrObj[i])) {
          case kOn:
            return "on";
            break;
          case kOff:
            return "off";
            break;
          case kRecycle:
            return "recycle";
            break;
          default:
            return "?????";
            break;
        };
      }
      else if( command==setWrFile[i] )
      {
        return pc->CurrentWriteFile(wrObj[i]);
      }
    }
  }

  return s;
}

// Implementation of PopWord
G4std::string G4PersistencyCenterMessenger::PopWord(G4std::string text, int n, G4std::string delim)
{
  if ( text.length() <= 0 ) return "";
  int p = 0, p0 = 0;
  int p1 = 0;
  for ( int i = 0; i < n; i++ ) {
    p1 = text.find_first_of(delim,p0+1);
    while( p1 == p0+1 ) {
      p0 = p1;
      p1 = text.find_first_of(delim,p0+1);
    }
    p  = p0;
    if ( p1 < 0 ) {
      if ( i+1 < n ) return "";
      p1 = text.length();
      break;
    }
    p0 = p1;
  }
  if (p > 0) p++;
  return text.substr(p,p1-p);
}

// End of G4PersistencyCenterMessenger.cc
