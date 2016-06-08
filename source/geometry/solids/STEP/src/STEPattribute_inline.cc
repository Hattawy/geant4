

//



//
// $Id: STEPattribute_inline.cc,v 1.2 1999/05/21 20:20:49 japost Exp $
// GEANT4 tag $Name: geant4-00-01 $
//

/*
* NIST STEP Core Class Library
* clstepcore/STEPattribute.inline.cc
* May 1995
* K. C. Morris
* David Sauder

* Development of this software was funded by the United States Government,
* and is not subject to copyright.
*/

/*  */

#include <STEPattribute.h>
#include <sdai.h>

//  This is needed so that STEPattribute's can be passed as
//  references to inline functions

STEPattribute::STEPattribute (const STEPattribute& a)
: aDesc (a.aDesc), _derive (0) {}

//  INTEGER
STEPattribute::STEPattribute (const class AttrDescriptor& d, SdaiInteger *p)
: aDesc (&d), _derive (0)
{ ptr.i = p; }

//  BINARY
STEPattribute::STEPattribute (const class AttrDescriptor& d, SdaiBinary *p)
: aDesc (&d), _derive (0)
{ptr.b =p;  }

//  STRING
STEPattribute::STEPattribute (const class AttrDescriptor& d, SdaiString *p)
: aDesc (&d), _derive (0)
{ptr.S =p;  }

//  REAL & NUMBER
STEPattribute::STEPattribute (const class AttrDescriptor& d, SdaiReal *p)
: aDesc (&d), _derive (0)
{ ptr.r = p; }

//  REAL_PTR
/*STEPattribute::STEPattribute (const class AttrDescriptor& d, real **p)
: aDesc (&d), _derive (0)
{ ptr.rp = p; }
*/
//  ENTITY
STEPattribute::STEPattribute (const class AttrDescriptor& d, STEPentity* *p)
: aDesc (&d), _derive (0)
{ ptr.c = p; }

//  AGGREGATE
STEPattribute::STEPattribute (const class AttrDescriptor& d, STEPaggregate *p)
: aDesc (&d), _derive (0)
{ ptr.a =  p; }

//  ENUMERATION  and Logical
STEPattribute::STEPattribute (const class AttrDescriptor& d, STEPenumeration *p)
: aDesc (&d), _derive (0)
{ ptr.e = p;  }

//  SELECT
STEPattribute::STEPattribute (const class AttrDescriptor& d, class SdaiSelect *p)
: aDesc (&d), _derive (0)
{ ptr.sh = p;  }

//  UNDEFINED
STEPattribute::STEPattribute (const class AttrDescriptor& d, SCLundefined *p)
: aDesc (&d), _derive (0)
{ ptr.u = p;  }


const s_String 
STEPattribute::Name() const
	{ return aDesc->Name(); }

const s_String 
STEPattribute::TypeName() const
	{ return aDesc->TypeName(); }

const BASE_TYPE 
STEPattribute::Type() const
{
    return aDesc->Type();
}

const BASE_TYPE 
STEPattribute::NonRefType() const
{ 
    return aDesc->NonRefType();
}

const BASE_TYPE 
STEPattribute::BaseType() const
{ 
    return aDesc->BaseType();
}

/*
const EntityDescriptor *
STEPattribute::ReferentEntity() const
{
    return aDesc->ReferentEntity();
}
*/

const TypeDescriptor * 
STEPattribute::ReferentType() const
{
    return aDesc->ReferentType();
}

BOOLEAN 
STEPattribute::Nullable() const
{
    return (aDesc->Optionality().asInt() == T);
}