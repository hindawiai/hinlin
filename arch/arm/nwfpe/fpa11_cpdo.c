<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    NetWinder Floating Poपूर्णांक Emulator
    (c) Rebel.COM, 1998,1999
    (c) Philip Blundell, 2001

    Direct questions, comments to Scott Bambrough <scottb@netwinder.org>

*/

#समावेश "fpa11.h"
#समावेश "fpopcode.h"

अचिन्हित पूर्णांक SingleCPDO(काष्ठा roundingData *roundData, स्थिर अचिन्हित पूर्णांक opcode, FPREG * rFd);
अचिन्हित पूर्णांक DoubleCPDO(काष्ठा roundingData *roundData, स्थिर अचिन्हित पूर्णांक opcode, FPREG * rFd);
अचिन्हित पूर्णांक ExtendedCPDO(काष्ठा roundingData *roundData, स्थिर अचिन्हित पूर्णांक opcode, FPREG * rFd);

अचिन्हित पूर्णांक EmulateCPDO(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	FPA11 *fpa11 = GET_FPA11();
	FPREG *rFd;
	अचिन्हित पूर्णांक nType, nDest, nRc;
	काष्ठा roundingData roundData;

	/* Get the destination size.  If not valid let Linux perक्रमm
	   an invalid inकाष्ठाion trap. */
	nDest = getDestinationSize(opcode);
	अगर (typeNone == nDest)
		वापस 0;

	roundData.mode = SetRoundingMode(opcode);
	roundData.precision = SetRoundingPrecision(opcode);
	roundData.exception = 0;

	/* Compare the size of the opeअक्रमs in Fn and Fm.
	   Choose the largest size and perक्रमm operations in that size,
	   in order to make use of all the precision of the opeअक्रमs.
	   If Fm is a स्थिरant, we just grab a स्थिरant of a size
	   matching the size of the opeअक्रम in Fn. */
	अगर (MONADIC_INSTRUCTION(opcode))
		nType = nDest;
	अन्यथा
		nType = fpa11->fType[getFn(opcode)];

	अगर (!CONSTANT_FM(opcode)) अणु
		रेजिस्टर अचिन्हित पूर्णांक Fm = getFm(opcode);
		अगर (nType < fpa11->fType[Fm]) अणु
			nType = fpa11->fType[Fm];
		पूर्ण
	पूर्ण

	rFd = &fpa11->fpreg[getFd(opcode)];

	चयन (nType) अणु
	हाल typeSingle:
		nRc = SingleCPDO(&roundData, opcode, rFd);
		अवरोध;
	हाल typeDouble:
		nRc = DoubleCPDO(&roundData, opcode, rFd);
		अवरोध;
#अगर_घोषित CONFIG_FPE_NWFPE_XP
	हाल typeExtended:
		nRc = ExtendedCPDO(&roundData, opcode, rFd);
		अवरोध;
#पूर्ण_अगर
	शेष:
		nRc = 0;
	पूर्ण

	/* The CPDO functions used to always set the destination type
	   to be the same as their working size. */

	अगर (nRc != 0) अणु
		/* If the operation succeeded, check to see अगर the result in the
		   destination रेजिस्टर is the correct size.  If not क्रमce it
		   to be. */

		fpa11->fType[getFd(opcode)] = nDest;

#अगर_घोषित CONFIG_FPE_NWFPE_XP
		अगर (nDest != nType) अणु
			चयन (nDest) अणु
			हाल typeSingle:
				अणु
					अगर (typeDouble == nType)
						rFd->fSingle = भग्न64_to_भग्न32(&roundData, rFd->fDouble);
					अन्यथा
						rFd->fSingle = भग्नx80_to_भग्न32(&roundData, rFd->fExtended);
				पूर्ण
				अवरोध;

			हाल typeDouble:
				अणु
					अगर (typeSingle == nType)
						rFd->fDouble = भग्न32_to_भग्न64(rFd->fSingle);
					अन्यथा
						rFd->fDouble = भग्नx80_to_भग्न64(&roundData, rFd->fExtended);
				पूर्ण
				अवरोध;

			हाल typeExtended:
				अणु
					अगर (typeSingle == nType)
						rFd->fExtended = भग्न32_to_भग्नx80(rFd->fSingle);
					अन्यथा
						rFd->fExtended = भग्न64_to_भग्नx80(rFd->fDouble);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
#अन्यथा
		अगर (nDest != nType) अणु
			अगर (nDest == typeSingle)
				rFd->fSingle = भग्न64_to_भग्न32(&roundData, rFd->fDouble);
			अन्यथा
				rFd->fDouble = भग्न32_to_भग्न64(rFd->fSingle);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	अगर (roundData.exception)
		भग्न_उठाओ(roundData.exception);

	वापस nRc;
पूर्ण
