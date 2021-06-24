<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_INTEL_FAMILY_H
#घोषणा _ASM_X86_INTEL_FAMILY_H

/*
 * "Big Core" Processors (Bअक्रमed as Core, Xeon, etc...)
 *
 * While adding a new CPUID क्रम a new microarchitecture, add a new
 * group to keep logically sorted out in chronological order. Within
 * that group keep the CPUID क्रम the variants sorted by model number.
 *
 * The defined symbol names have the following क्रमm:
 *	INTEL_FAM6अणुOPTFAMILYपूर्ण_अणुMICROARCHपूर्णअणुOPTDIFFपूर्ण
 * where:
 * OPTFAMILY	Describes the family of CPUs that this beदीर्घs to. Default
 *		is assumed to be "_CORE" (and should be omitted). Other values
 *		currently in use are _ATOM and _XEON_PHI
 * MICROARCH	Is the code name क्रम the micro-architecture क्रम this core.
 *		N.B. Not the platक्रमm name.
 * OPTDIFF	If needed, a लघु string to dअगरferentiate by market segment.
 *
 *		Common OPTDIFFs:
 *
 *			- regular client parts
 *		_L	- regular mobile parts
 *		_G	- parts with extra graphics on
 *		_X	- regular server parts
 *		_D	- micro server parts
 *
 *		Historical OPTDIFFs:
 *
 *		_EP	- 2 socket server parts
 *		_EX	- 4+ socket server parts
 *
 * The #घोषणा line may optionally include a comment including platक्रमm or core
 * names. An exception is made क्रम skylake/kabylake where steppings seem to have gotten
 * their own names :-(
 */

/* Wildcard match क्रम FAM6 so X86_MATCH_INTEL_FAM6_MODEL(ANY) works */
#घोषणा INTEL_FAM6_ANY			X86_MODEL_ANY

#घोषणा INTEL_FAM6_CORE_YONAH		0x0E

#घोषणा INTEL_FAM6_CORE2_MEROM		0x0F
#घोषणा INTEL_FAM6_CORE2_MEROM_L	0x16
#घोषणा INTEL_FAM6_CORE2_PENRYN		0x17
#घोषणा INTEL_FAM6_CORE2_DUNNINGTON	0x1D

#घोषणा INTEL_FAM6_NEHALEM		0x1E
#घोषणा INTEL_FAM6_NEHALEM_G		0x1F /* Auburndale / Havendale */
#घोषणा INTEL_FAM6_NEHALEM_EP		0x1A
#घोषणा INTEL_FAM6_NEHALEM_EX		0x2E

#घोषणा INTEL_FAM6_WESTMERE		0x25
#घोषणा INTEL_FAM6_WESTMERE_EP		0x2C
#घोषणा INTEL_FAM6_WESTMERE_EX		0x2F

#घोषणा INTEL_FAM6_SANDYBRIDGE		0x2A
#घोषणा INTEL_FAM6_SANDYBRIDGE_X	0x2D
#घोषणा INTEL_FAM6_IVYBRIDGE		0x3A
#घोषणा INTEL_FAM6_IVYBRIDGE_X		0x3E

#घोषणा INTEL_FAM6_HASWELL		0x3C
#घोषणा INTEL_FAM6_HASWELL_X		0x3F
#घोषणा INTEL_FAM6_HASWELL_L		0x45
#घोषणा INTEL_FAM6_HASWELL_G		0x46

#घोषणा INTEL_FAM6_BROADWELL		0x3D
#घोषणा INTEL_FAM6_BROADWELL_G		0x47
#घोषणा INTEL_FAM6_BROADWELL_X		0x4F
#घोषणा INTEL_FAM6_BROADWELL_D		0x56

#घोषणा INTEL_FAM6_SKYLAKE_L		0x4E	/* Sky Lake             */
#घोषणा INTEL_FAM6_SKYLAKE		0x5E	/* Sky Lake             */
#घोषणा INTEL_FAM6_SKYLAKE_X		0x55	/* Sky Lake             */
/*                 CASCADELAKE_X	0x55	   Sky Lake -- s: 7     */
/*                 COOPERLAKE_X		0x55	   Sky Lake -- s: 11    */

#घोषणा INTEL_FAM6_KABYLAKE_L		0x8E	/* Sky Lake             */
/*                 AMBERLAKE_L		0x8E	   Sky Lake -- s: 9     */
/*                 COFFEELAKE_L		0x8E	   Sky Lake -- s: 10    */
/*                 WHISKEYLAKE_L	0x8E       Sky Lake -- s: 11,12 */

#घोषणा INTEL_FAM6_KABYLAKE		0x9E	/* Sky Lake             */
/*                 COFFEELAKE		0x9E	   Sky Lake -- s: 10-13 */

#घोषणा INTEL_FAM6_COMETLAKE		0xA5	/* Sky Lake             */
#घोषणा INTEL_FAM6_COMETLAKE_L		0xA6	/* Sky Lake             */

#घोषणा INTEL_FAM6_CANNONLAKE_L		0x66	/* Palm Cove */

#घोषणा INTEL_FAM6_ICELAKE_X		0x6A	/* Sunny Cove */
#घोषणा INTEL_FAM6_ICELAKE_D		0x6C	/* Sunny Cove */
#घोषणा INTEL_FAM6_ICELAKE		0x7D	/* Sunny Cove */
#घोषणा INTEL_FAM6_ICELAKE_L		0x7E	/* Sunny Cove */
#घोषणा INTEL_FAM6_ICELAKE_NNPI		0x9D	/* Sunny Cove */

#घोषणा INTEL_FAM6_LAKEFIELD		0x8A	/* Sunny Cove / Tremont */

#घोषणा INTEL_FAM6_ROCKETLAKE		0xA7	/* Cypress Cove */

#घोषणा INTEL_FAM6_TIGERLAKE_L		0x8C	/* Willow Cove */
#घोषणा INTEL_FAM6_TIGERLAKE		0x8D	/* Willow Cove */
#घोषणा INTEL_FAM6_SAPPHIRERAPIDS_X	0x8F	/* Willow Cove */

#घोषणा INTEL_FAM6_ALDERLAKE		0x97	/* Golden Cove / Gracemont */
#घोषणा INTEL_FAM6_ALDERLAKE_L		0x9A	/* Golden Cove / Gracemont */

/* "Small Core" Processors (Atom) */

#घोषणा INTEL_FAM6_ATOM_BONNELL		0x1C /* Diamondville, Pineview */
#घोषणा INTEL_FAM6_ATOM_BONNELL_MID	0x26 /* Silverthorne, Lincroft */

#घोषणा INTEL_FAM6_ATOM_SALTWELL	0x36 /* Cedarview */
#घोषणा INTEL_FAM6_ATOM_SALTWELL_MID	0x27 /* Penwell */
#घोषणा INTEL_FAM6_ATOM_SALTWELL_TABLET	0x35 /* Cloverview */

#घोषणा INTEL_FAM6_ATOM_SILVERMONT	0x37 /* Bay Trail, Valleyview */
#घोषणा INTEL_FAM6_ATOM_SILVERMONT_D	0x4D /* Avaton, Rangely */
#घोषणा INTEL_FAM6_ATOM_SILVERMONT_MID	0x4A /* Merriefield */

#घोषणा INTEL_FAM6_ATOM_AIRMONT		0x4C /* Cherry Trail, Braswell */
#घोषणा INTEL_FAM6_ATOM_AIRMONT_MID	0x5A /* Moorefield */
#घोषणा INTEL_FAM6_ATOM_AIRMONT_NP	0x75 /* Lightning Mountain */

#घोषणा INTEL_FAM6_ATOM_GOLDMONT	0x5C /* Apollo Lake */
#घोषणा INTEL_FAM6_ATOM_GOLDMONT_D	0x5F /* Denverton */

/* Note: the micro-architecture is "Goldmont Plus" */
#घोषणा INTEL_FAM6_ATOM_GOLDMONT_PLUS	0x7A /* Gemini Lake */

#घोषणा INTEL_FAM6_ATOM_TREMONT_D	0x86 /* Jacobsville */
#घोषणा INTEL_FAM6_ATOM_TREMONT		0x96 /* Elkhart Lake */
#घोषणा INTEL_FAM6_ATOM_TREMONT_L	0x9C /* Jasper Lake */

/* Xeon Phi */

#घोषणा INTEL_FAM6_XEON_PHI_KNL		0x57 /* Knights Landing */
#घोषणा INTEL_FAM6_XEON_PHI_KNM		0x85 /* Knights Mill */

/* Family 5 */
#घोषणा INTEL_FAM5_QUARK_X1000		0x09 /* Quark X1000 SoC */

#पूर्ण_अगर /* _ASM_X86_INTEL_FAMILY_H */
