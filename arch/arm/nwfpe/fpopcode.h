<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    NetWinder Floating Poपूर्णांक Emulator
    (c) Rebel.COM, 1998,1999
    (c) Philip Blundell, 2001

    Direct questions, comments to Scott Bambrough <scottb@netwinder.org>

*/

#अगर_अघोषित __FPOPCODE_H__
#घोषणा __FPOPCODE_H__


/*
ARM Floating Poपूर्णांक Inकाष्ठाion Classes
| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | 
|c o n d|1 1 0 P|U|u|W|L|   Rn  |v|  Fd |0|0|0|1|  o f f s e t  | CPDT
|c o n d|1 1 0 P|U|w|W|L|   Rn  |x|  Fd |0|0|1|0|  o f f s e t  | CPDT (copro 2)
| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | 
|c o n d|1 1 1 0|a|b|c|d|e|  Fn |j|  Fd |0|0|0|1|f|g|h|0|i|  Fm | CPDO
|c o n d|1 1 1 0|a|b|c|L|e|  Fn |   Rd  |0|0|0|1|f|g|h|1|i|  Fm | CPRT
|c o n d|1 1 1 0|a|b|c|1|e|  Fn |1|1|1|1|0|0|0|1|f|g|h|1|i|  Fm | comparisons
| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | 

CPDT		data transfer inकाष्ठाions
		LDF, STF, LFM (copro 2), SFM (copro 2)
		
CPDO		dyadic arithmetic inकाष्ठाions
		ADF, MUF, SUF, RSF, DVF, RDF,
		POW, RPW, RMF, FML, FDV, FRD, POL

CPDO		monadic arithmetic inकाष्ठाions
		MVF, MNF, ABS, RND, SQT, LOG, LGN, EXP,
		SIN, COS, TAN, ASN, ACS, ATN, URD, NRM
		
CPRT		joपूर्णांक arithmetic/data transfer inकाष्ठाions
		FIX (arithmetic followed by load/store)
		FLT (load/store followed by arithmetic)
		CMF, CNF CMFE, CNFE (comparisons)
		WFS, RFS (ग_लिखो/पढ़ो भग्नing poपूर्णांक status रेजिस्टर)
		WFC, RFC (ग_लिखो/पढ़ो भग्नing poपूर्णांक control रेजिस्टर)

cond		condition codes
P		pre/post index bit: 0 = postindex, 1 = preindex
U		up/करोwn bit: 0 = stack grows करोwn, 1 = stack grows up
W		ग_लिखो back bit: 1 = update base रेजिस्टर (Rn)
L		load/store bit: 0 = store, 1 = load
Rn		base रेजिस्टर
Rd		destination/source रेजिस्टर		
Fd		भग्नing poपूर्णांक destination रेजिस्टर
Fn		भग्नing poपूर्णांक source रेजिस्टर
Fm		भग्नing poपूर्णांक source रेजिस्टर or भग्नing poपूर्णांक स्थिरant

uv		transfer length (TABLE 1)
wx		रेजिस्टर count (TABLE 2)
abcd		arithmetic opcode (TABLES 3 & 4)
ef		destination size (rounding precision) (TABLE 5)
gh		rounding mode (TABLE 6)
j		dyadic/monadic bit: 0 = dyadic, 1 = monadic
i 		स्थिरant bit: 1 = स्थिरant (TABLE 6)
*/

/*
TABLE 1
+-------------------------+---+---+---------+---------+
|  Precision              | u | v | FPSR.EP | length  |
+-------------------------+---+---+---------+---------+
| Single                  | 0 | 0 |    x    | 1 words |
| Double                  | 1 | 1 |    x    | 2 words |
| Extended                | 1 | 1 |    x    | 3 words |
| Packed decimal          | 1 | 1 |    0    | 3 words |
| Expanded packed decimal | 1 | 1 |    1    | 4 words |
+-------------------------+---+---+---------+---------+
Note: x = करोn't care
*/

/*
TABLE 2
+---+---+---------------------------------+
| w | x | Number of रेजिस्टरs to transfer |
+---+---+---------------------------------+
| 0 | 1 |  1                              |
| 1 | 0 |  2                              |
| 1 | 1 |  3                              |
| 0 | 0 |  4                              |
+---+---+---------------------------------+
*/

/*
TABLE 3: Dyadic Floating Poपूर्णांक Opcodes
+---+---+---+---+----------+-----------------------+-----------------------+
| a | b | c | d | Mnemonic | Description           | Operation             |
+---+---+---+---+----------+-----------------------+-----------------------+
| 0 | 0 | 0 | 0 | ADF      | Add                   | Fd := Fn + Fm         |
| 0 | 0 | 0 | 1 | MUF      | Multiply              | Fd := Fn * Fm         |
| 0 | 0 | 1 | 0 | SUF      | Subtract              | Fd := Fn - Fm         |
| 0 | 0 | 1 | 1 | RSF      | Reverse subtract      | Fd := Fm - Fn         |
| 0 | 1 | 0 | 0 | DVF      | Divide                | Fd := Fn / Fm         |
| 0 | 1 | 0 | 1 | RDF      | Reverse भागide        | Fd := Fm / Fn         |
| 0 | 1 | 1 | 0 | POW      | Power                 | Fd := Fn ^ Fm         |
| 0 | 1 | 1 | 1 | RPW      | Reverse घातer         | Fd := Fm ^ Fn         |
| 1 | 0 | 0 | 0 | RMF      | Reमुख्यder             | Fd := IEEE rem(Fn/Fm) |
| 1 | 0 | 0 | 1 | FML      | Fast Multiply         | Fd := Fn * Fm         |
| 1 | 0 | 1 | 0 | FDV      | Fast Divide           | Fd := Fn / Fm         |
| 1 | 0 | 1 | 1 | FRD      | Fast reverse भागide   | Fd := Fm / Fn         |
| 1 | 1 | 0 | 0 | POL      | Polar angle (ArcTan2) | Fd := arctan2(Fn,Fm)  |
| 1 | 1 | 0 | 1 |          | undefined inकाष्ठाion | trap                  |
| 1 | 1 | 1 | 0 |          | undefined inकाष्ठाion | trap                  |
| 1 | 1 | 1 | 1 |          | undefined inकाष्ठाion | trap                  |
+---+---+---+---+----------+-----------------------+-----------------------+
Note: POW, RPW, POL are deprecated, and are available क्रम backwards
      compatibility only.
*/

/*
TABLE 4: Monadic Floating Poपूर्णांक Opcodes
+---+---+---+---+----------+-----------------------+-----------------------+
| a | b | c | d | Mnemonic | Description           | Operation             |
+---+---+---+---+----------+-----------------------+-----------------------+
| 0 | 0 | 0 | 0 | MVF      | Move                  | Fd := Fm              |
| 0 | 0 | 0 | 1 | MNF      | Move negated          | Fd := - Fm            |
| 0 | 0 | 1 | 0 | ABS      | Absolute value        | Fd := असल(Fm)         |
| 0 | 0 | 1 | 1 | RND      | Round to पूर्णांकeger      | Fd := पूर्णांक(Fm)         |
| 0 | 1 | 0 | 0 | SQT      | Square root           | Fd := वर्ग_मूल(Fm)        |
| 0 | 1 | 0 | 1 | LOG      | Log base 10           | Fd := log10(Fm)       |
| 0 | 1 | 1 | 0 | LGN      | Log base e            | Fd := ln(Fm)          |
| 0 | 1 | 1 | 1 | EXP      | Exponent              | Fd := e ^ Fm          |
| 1 | 0 | 0 | 0 | SIN      | Sine                  | Fd := sin(Fm)         |
| 1 | 0 | 0 | 1 | COS      | Cosine                | Fd := cos(Fm)         |
| 1 | 0 | 1 | 0 | TAN      | Tangent               | Fd := tan(Fm)         |
| 1 | 0 | 1 | 1 | ASN      | Arc Sine              | Fd := arcsin(Fm)      |
| 1 | 1 | 0 | 0 | ACS      | Arc Cosine            | Fd := arccos(Fm)      |
| 1 | 1 | 0 | 1 | ATN      | Arc Tangent           | Fd := arctan(Fm)      |
| 1 | 1 | 1 | 0 | URD      | Unnormalized round    | Fd := पूर्णांक(Fm)         |
| 1 | 1 | 1 | 1 | NRM      | Normalize             | Fd := norm(Fm)        |
+---+---+---+---+----------+-----------------------+-----------------------+
Note: LOG, LGN, EXP, SIN, COS, TAN, ASN, ACS, ATN are deprecated, and are
      available क्रम backwards compatibility only.
*/

/*
TABLE 5
+-------------------------+---+---+
|  Rounding Precision     | e | f |
+-------------------------+---+---+
| IEEE Single precision   | 0 | 0 |
| IEEE Double precision   | 0 | 1 |
| IEEE Extended precision | 1 | 0 |
| undefined (trap)        | 1 | 1 |
+-------------------------+---+---+
*/

/*
TABLE 5
+---------------------------------+---+---+
|  Rounding Mode                  | g | h |
+---------------------------------+---+---+
| Round to nearest (शेष)      | 0 | 0 |
| Round toward plus infinity      | 0 | 1 |
| Round toward negative infinity  | 1 | 0 |
| Round toward zero               | 1 | 1 |
+---------------------------------+---+---+
*/

/*
===
=== Definitions क्रम load and store inकाष्ठाions
===
*/

/* bit masks */
#घोषणा BIT_PREINDEX	0x01000000
#घोषणा BIT_UP		0x00800000
#घोषणा BIT_WRITE_BACK	0x00200000
#घोषणा BIT_LOAD	0x00100000

/* masks क्रम load/store */
#घोषणा MASK_CPDT		0x0c000000	/* data processing opcode */
#घोषणा MASK_OFFSET		0x000000ff
#घोषणा MASK_TRANSFER_LENGTH	0x00408000
#घोषणा MASK_REGISTER_COUNT	MASK_TRANSFER_LENGTH
#घोषणा MASK_COPROCESSOR	0x00000f00

/* Tests क्रम transfer length */
#घोषणा TRANSFER_SINGLE		0x00000000
#घोषणा TRANSFER_DOUBLE		0x00008000
#घोषणा TRANSFER_EXTENDED	0x00400000
#घोषणा TRANSFER_PACKED		MASK_TRANSFER_LENGTH

/* Get the coprocessor number from the opcode. */
#घोषणा getCoprocessorNumber(opcode)	((opcode & MASK_COPROCESSOR) >> 8)

/* Get the offset from the opcode. */
#घोषणा getOffset(opcode)		(opcode & MASK_OFFSET)

/* Tests क्रम specअगरic data transfer load/store opcodes. */
#घोषणा TEST_OPCODE(opcode,mask)	(((opcode) & (mask)) == (mask))

#घोषणा LOAD_OP(opcode)   TEST_OPCODE((opcode),MASK_CPDT | BIT_LOAD)
#घोषणा STORE_OP(opcode)  ((opcode & (MASK_CPDT | BIT_LOAD)) == MASK_CPDT)

#घोषणा LDF_OP(opcode)	(LOAD_OP(opcode) && (getCoprocessorNumber(opcode) == 1))
#घोषणा LFM_OP(opcode)	(LOAD_OP(opcode) && (getCoprocessorNumber(opcode) == 2))
#घोषणा STF_OP(opcode)	(STORE_OP(opcode) && (getCoprocessorNumber(opcode) == 1))
#घोषणा SFM_OP(opcode)	(STORE_OP(opcode) && (getCoprocessorNumber(opcode) == 2))

#घोषणा PREINDEXED(opcode)		((opcode & BIT_PREINDEX) != 0)
#घोषणा POSTINDEXED(opcode)		((opcode & BIT_PREINDEX) == 0)
#घोषणा BIT_UP_SET(opcode)		((opcode & BIT_UP) != 0)
#घोषणा BIT_UP_CLEAR(opcode)		((opcode & BIT_DOWN) == 0)
#घोषणा WRITE_BACK(opcode)		((opcode & BIT_WRITE_BACK) != 0)
#घोषणा LOAD(opcode)			((opcode & BIT_LOAD) != 0)
#घोषणा STORE(opcode)			((opcode & BIT_LOAD) == 0)

/*
===
=== Definitions क्रम arithmetic inकाष्ठाions
===
*/
/* bit masks */
#घोषणा BIT_MONADIC	0x00008000
#घोषणा BIT_CONSTANT	0x00000008

#घोषणा CONSTANT_FM(opcode)		((opcode & BIT_CONSTANT) != 0)
#घोषणा MONADIC_INSTRUCTION(opcode)	((opcode & BIT_MONADIC) != 0)

/* inकाष्ठाion identअगरication masks */
#घोषणा MASK_CPDO		0x0e000000	/* arithmetic opcode */
#घोषणा MASK_ARITHMETIC_OPCODE	0x00f08000
#घोषणा MASK_DESTINATION_SIZE	0x00080080

/* dyadic arithmetic opcodes. */
#घोषणा ADF_CODE	0x00000000
#घोषणा MUF_CODE	0x00100000
#घोषणा SUF_CODE	0x00200000
#घोषणा RSF_CODE	0x00300000
#घोषणा DVF_CODE	0x00400000
#घोषणा RDF_CODE	0x00500000
#घोषणा POW_CODE	0x00600000
#घोषणा RPW_CODE	0x00700000
#घोषणा RMF_CODE	0x00800000
#घोषणा FML_CODE	0x00900000
#घोषणा FDV_CODE	0x00a00000
#घोषणा FRD_CODE	0x00b00000
#घोषणा POL_CODE	0x00c00000
/* 0x00d00000 is an invalid dyadic arithmetic opcode */
/* 0x00e00000 is an invalid dyadic arithmetic opcode */
/* 0x00f00000 is an invalid dyadic arithmetic opcode */

/* monadic arithmetic opcodes. */
#घोषणा MVF_CODE	0x00008000
#घोषणा MNF_CODE	0x00108000
#घोषणा ABS_CODE	0x00208000
#घोषणा RND_CODE	0x00308000
#घोषणा SQT_CODE	0x00408000
#घोषणा LOG_CODE	0x00508000
#घोषणा LGN_CODE	0x00608000
#घोषणा EXP_CODE	0x00708000
#घोषणा SIN_CODE	0x00808000
#घोषणा COS_CODE	0x00908000
#घोषणा TAN_CODE	0x00a08000
#घोषणा ASN_CODE	0x00b08000
#घोषणा ACS_CODE	0x00c08000
#घोषणा ATN_CODE	0x00d08000
#घोषणा URD_CODE	0x00e08000
#घोषणा NRM_CODE	0x00f08000

/*
===
=== Definitions क्रम रेजिस्टर transfer and comparison inकाष्ठाions
===
*/

#घोषणा MASK_CPRT		0x0e000010	/* रेजिस्टर transfer opcode */
#घोषणा MASK_CPRT_CODE		0x00f00000
#घोषणा FLT_CODE		0x00000000
#घोषणा FIX_CODE		0x00100000
#घोषणा WFS_CODE		0x00200000
#घोषणा RFS_CODE		0x00300000
#घोषणा WFC_CODE		0x00400000
#घोषणा RFC_CODE		0x00500000
#घोषणा CMF_CODE		0x00900000
#घोषणा CNF_CODE		0x00b00000
#घोषणा CMFE_CODE		0x00d00000
#घोषणा CNFE_CODE		0x00f00000

/*
===
=== Common definitions
===
*/

/* रेजिस्टर masks */
#घोषणा MASK_Rd		0x0000f000
#घोषणा MASK_Rn		0x000f0000
#घोषणा MASK_Fd		0x00007000
#घोषणा MASK_Fm		0x00000007
#घोषणा MASK_Fn		0x00070000

/* condition code masks */
#घोषणा CC_MASK		0xf0000000
#घोषणा CC_NEGATIVE	0x80000000
#घोषणा CC_ZERO		0x40000000
#घोषणा CC_CARRY	0x20000000
#घोषणा CC_OVERFLOW	0x10000000
#घोषणा CC_EQ		0x00000000
#घोषणा CC_NE		0x10000000
#घोषणा CC_CS		0x20000000
#घोषणा CC_HS		CC_CS
#घोषणा CC_CC		0x30000000
#घोषणा CC_LO		CC_CC
#घोषणा CC_MI		0x40000000
#घोषणा CC_PL		0x50000000
#घोषणा CC_VS		0x60000000
#घोषणा CC_VC		0x70000000
#घोषणा CC_HI		0x80000000
#घोषणा CC_LS		0x90000000
#घोषणा CC_GE		0xa0000000
#घोषणा CC_LT		0xb0000000
#घोषणा CC_GT		0xc0000000
#घोषणा CC_LE		0xd0000000
#घोषणा CC_AL		0xe0000000
#घोषणा CC_NV		0xf0000000

/* rounding masks/values */
#घोषणा MASK_ROUNDING_MODE	0x00000060
#घोषणा ROUND_TO_NEAREST	0x00000000
#घोषणा ROUND_TO_PLUS_अनन्त	0x00000020
#घोषणा ROUND_TO_MINUS_अनन्त	0x00000040
#घोषणा ROUND_TO_ZERO		0x00000060

#घोषणा MASK_ROUNDING_PRECISION	0x00080080
#घोषणा ROUND_SINGLE		0x00000000
#घोषणा ROUND_DOUBLE		0x00000080
#घोषणा ROUND_EXTENDED		0x00080000

/* Get the condition code from the opcode. */
#घोषणा getCondition(opcode)		(opcode >> 28)

/* Get the source रेजिस्टर from the opcode. */
#घोषणा getRn(opcode)			((opcode & MASK_Rn) >> 16)

/* Get the destination भग्नing poपूर्णांक रेजिस्टर from the opcode. */
#घोषणा getFd(opcode)			((opcode & MASK_Fd) >> 12)

/* Get the first source भग्नing poपूर्णांक रेजिस्टर from the opcode. */
#घोषणा getFn(opcode)		((opcode & MASK_Fn) >> 16)

/* Get the second source भग्नing poपूर्णांक रेजिस्टर from the opcode. */
#घोषणा getFm(opcode)		(opcode & MASK_Fm)

/* Get the destination रेजिस्टर from the opcode. */
#घोषणा getRd(opcode)		((opcode & MASK_Rd) >> 12)

/* Get the rounding mode from the opcode. */
#घोषणा getRoundingMode(opcode)		((opcode & MASK_ROUNDING_MODE) >> 5)

#अगर_घोषित CONFIG_FPE_NWFPE_XP
अटल अंतरभूत भग्नx80 __pure getExtendedConstant(स्थिर अचिन्हित पूर्णांक nIndex)
अणु
	बाह्य स्थिर भग्नx80 भग्नx80Constant[];
	वापस भग्नx80Constant[nIndex];
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत भग्न64 __pure getDoubleConstant(स्थिर अचिन्हित पूर्णांक nIndex)
अणु
	बाह्य स्थिर भग्न64 भग्न64Constant[];
	वापस भग्न64Constant[nIndex];
पूर्ण

अटल अंतरभूत भग्न32 __pure getSingleConstant(स्थिर अचिन्हित पूर्णांक nIndex)
अणु
	बाह्य स्थिर भग्न32 भग्न32Constant[];
	वापस भग्न32Constant[nIndex];
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक getTransferLength(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	अचिन्हित पूर्णांक nRc;

	चयन (opcode & MASK_TRANSFER_LENGTH) अणु
	हाल 0x00000000:
		nRc = 1;
		अवरोध;		/* single precision */
	हाल 0x00008000:
		nRc = 2;
		अवरोध;		/* द्विगुन precision */
	हाल 0x00400000:
		nRc = 3;
		अवरोध;		/* extended precision */
	शेष:
		nRc = 0;
	पूर्ण

	वापस (nRc);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक getRegisterCount(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	अचिन्हित पूर्णांक nRc;

	चयन (opcode & MASK_REGISTER_COUNT) अणु
	हाल 0x00000000:
		nRc = 4;
		अवरोध;
	हाल 0x00008000:
		nRc = 1;
		अवरोध;
	हाल 0x00400000:
		nRc = 2;
		अवरोध;
	हाल 0x00408000:
		nRc = 3;
		अवरोध;
	शेष:
		nRc = 0;
	पूर्ण

	वापस (nRc);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक getRoundingPrecision(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	अचिन्हित पूर्णांक nRc;

	चयन (opcode & MASK_ROUNDING_PRECISION) अणु
	हाल 0x00000000:
		nRc = 1;
		अवरोध;
	हाल 0x00000080:
		nRc = 2;
		अवरोध;
	हाल 0x00080000:
		nRc = 3;
		अवरोध;
	शेष:
		nRc = 0;
	पूर्ण

	वापस (nRc);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक getDestinationSize(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	अचिन्हित पूर्णांक nRc;

	चयन (opcode & MASK_DESTINATION_SIZE) अणु
	हाल 0x00000000:
		nRc = typeSingle;
		अवरोध;
	हाल 0x00000080:
		nRc = typeDouble;
		अवरोध;
	हाल 0x00080000:
		nRc = typeExtended;
		अवरोध;
	शेष:
		nRc = typeNone;
	पूर्ण

	वापस (nRc);
पूर्ण

बाह्य स्थिर भग्न64 भग्न64Constant[];
बाह्य स्थिर भग्न32 भग्न32Constant[];

#पूर्ण_अगर
