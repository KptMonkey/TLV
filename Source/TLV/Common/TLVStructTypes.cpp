#include "TLVStructTypes.h"
bool FTLVHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}