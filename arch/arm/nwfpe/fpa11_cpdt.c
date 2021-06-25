<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    NetWinder Floating Poपूर्णांक Emulator
    (c) Rebel.com, 1998-1999
    (c) Philip Blundell, 1998, 2001

    Direct questions, comments to Scott Bambrough <scottb@netwinder.org>

*/

#समावेश "fpa11.h"
#समावेश "softfloat.h"
#समावेश "fpopcode.h"
#समावेश "fpmodule.h"
#समावेश "fpmodule.inl"

#समावेश <linux/uaccess.h>

अटल अंतरभूत व्योम loadSingle(स्थिर अचिन्हित पूर्णांक Fn, स्थिर अचिन्हित पूर्णांक __user *pMem)
अणु
	FPA11 *fpa11 = GET_FPA11();
	fpa11->fType[Fn] = typeSingle;
	get_user(fpa11->fpreg[Fn].fSingle, pMem);
पूर्ण

अटल अंतरभूत व्योम loadDouble(स्थिर अचिन्हित पूर्णांक Fn, स्थिर अचिन्हित पूर्णांक __user *pMem)
अणु
	FPA11 *fpa11 = GET_FPA11();
	अचिन्हित पूर्णांक *p;
	p = (अचिन्हित पूर्णांक *) &fpa11->fpreg[Fn].fDouble;
	fpa11->fType[Fn] = typeDouble;
#अगर_घोषित __ARMEB__
	get_user(p[0], &pMem[0]);	/* sign & exponent */
	get_user(p[1], &pMem[1]);
#अन्यथा
	get_user(p[0], &pMem[1]);
	get_user(p[1], &pMem[0]);	/* sign & exponent */
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_FPE_NWFPE_XP
अटल अंतरभूत व्योम loadExtended(स्थिर अचिन्हित पूर्णांक Fn, स्थिर अचिन्हित पूर्णांक __user *pMem)
अणु
	FPA11 *fpa11 = GET_FPA11();
	अचिन्हित पूर्णांक *p;
	p = (अचिन्हित पूर्णांक *) &fpa11->fpreg[Fn].fExtended;
	fpa11->fType[Fn] = typeExtended;
	get_user(p[0], &pMem[0]);	/* sign & exponent */
#अगर_घोषित __ARMEB__
	get_user(p[1], &pMem[1]);	/* ms bits */
	get_user(p[2], &pMem[2]);	/* ls bits */
#अन्यथा
	get_user(p[1], &pMem[2]);	/* ls bits */
	get_user(p[2], &pMem[1]);	/* ms bits */
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम loadMultiple(स्थिर अचिन्हित पूर्णांक Fn, स्थिर अचिन्हित पूर्णांक __user *pMem)
अणु
	FPA11 *fpa11 = GET_FPA11();
	रेजिस्टर अचिन्हित पूर्णांक *p;
	अचिन्हित दीर्घ x;

	p = (अचिन्हित पूर्णांक *) &(fpa11->fpreg[Fn]);
	get_user(x, &pMem[0]);
	fpa11->fType[Fn] = (x >> 14) & 0x00000003;

	चयन (fpa11->fType[Fn]) अणु
	हाल typeSingle:
	हाल typeDouble:
		अणु
			get_user(p[0], &pMem[2]);	/* Single */
			get_user(p[1], &pMem[1]);	/* द्विगुन msw */
			p[2] = 0;			/* empty */
		पूर्ण
		अवरोध;

#अगर_घोषित CONFIG_FPE_NWFPE_XP
	हाल typeExtended:
		अणु
			get_user(p[1], &pMem[2]);
			get_user(p[2], &pMem[1]);	/* msw */
			p[0] = (x & 0x80003fff);
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम storeSingle(काष्ठा roundingData *roundData, स्थिर अचिन्हित पूर्णांक Fn, अचिन्हित पूर्णांक __user *pMem)
अणु
	FPA11 *fpa11 = GET_FPA11();
	जोड़ अणु
		भग्न32 f;
		अचिन्हित पूर्णांक i[1];
	पूर्ण val;

	चयन (fpa11->fType[Fn]) अणु
	हाल typeDouble:
		val.f = भग्न64_to_भग्न32(roundData, fpa11->fpreg[Fn].fDouble);
		अवरोध;

#अगर_घोषित CONFIG_FPE_NWFPE_XP
	हाल typeExtended:
		val.f = भग्नx80_to_भग्न32(roundData, fpa11->fpreg[Fn].fExtended);
		अवरोध;
#पूर्ण_अगर

	शेष:
		val.f = fpa11->fpreg[Fn].fSingle;
	पूर्ण

	put_user(val.i[0], pMem);
पूर्ण

अटल अंतरभूत व्योम storeDouble(काष्ठा roundingData *roundData, स्थिर अचिन्हित पूर्णांक Fn, अचिन्हित पूर्णांक __user *pMem)
अणु
	FPA11 *fpa11 = GET_FPA11();
	जोड़ अणु
		भग्न64 f;
		अचिन्हित पूर्णांक i[2];
	पूर्ण val;

	चयन (fpa11->fType[Fn]) अणु
	हाल typeSingle:
		val.f = भग्न32_to_भग्न64(fpa11->fpreg[Fn].fSingle);
		अवरोध;

#अगर_घोषित CONFIG_FPE_NWFPE_XP
	हाल typeExtended:
		val.f = भग्नx80_to_भग्न64(roundData, fpa11->fpreg[Fn].fExtended);
		अवरोध;
#पूर्ण_अगर

	शेष:
		val.f = fpa11->fpreg[Fn].fDouble;
	पूर्ण

#अगर_घोषित __ARMEB__
	put_user(val.i[0], &pMem[0]);	/* msw */
	put_user(val.i[1], &pMem[1]);	/* lsw */
#अन्यथा
	put_user(val.i[1], &pMem[0]);	/* msw */
	put_user(val.i[0], &pMem[1]);	/* lsw */
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_FPE_NWFPE_XP
अटल अंतरभूत व्योम storeExtended(स्थिर अचिन्हित पूर्णांक Fn, अचिन्हित पूर्णांक __user *pMem)
अणु
	FPA11 *fpa11 = GET_FPA11();
	जोड़ अणु
		भग्नx80 f;
		अचिन्हित पूर्णांक i[3];
	पूर्ण val;

	चयन (fpa11->fType[Fn]) अणु
	हाल typeSingle:
		val.f = भग्न32_to_भग्नx80(fpa11->fpreg[Fn].fSingle);
		अवरोध;

	हाल typeDouble:
		val.f = भग्न64_to_भग्नx80(fpa11->fpreg[Fn].fDouble);
		अवरोध;

	शेष:
		val.f = fpa11->fpreg[Fn].fExtended;
	पूर्ण

	put_user(val.i[0], &pMem[0]);	/* sign & exp */
#अगर_घोषित __ARMEB__
	put_user(val.i[1], &pMem[1]);	/* msw */
	put_user(val.i[2], &pMem[2]);
#अन्यथा
	put_user(val.i[1], &pMem[2]);
	put_user(val.i[2], &pMem[1]);	/* msw */
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम storeMultiple(स्थिर अचिन्हित पूर्णांक Fn, अचिन्हित पूर्णांक __user *pMem)
अणु
	FPA11 *fpa11 = GET_FPA11();
	रेजिस्टर अचिन्हित पूर्णांक nType, *p;

	p = (अचिन्हित पूर्णांक *) &(fpa11->fpreg[Fn]);
	nType = fpa11->fType[Fn];

	चयन (nType) अणु
	हाल typeSingle:
	हाल typeDouble:
		अणु
			put_user(p[0], &pMem[2]);	/* single */
			put_user(p[1], &pMem[1]);	/* द्विगुन msw */
			put_user(nType << 14, &pMem[0]);
		पूर्ण
		अवरोध;

#अगर_घोषित CONFIG_FPE_NWFPE_XP
	हाल typeExtended:
		अणु
			put_user(p[2], &pMem[1]);	/* msw */
			put_user(p[1], &pMem[2]);
			put_user((p[0] & 0x80003fff) | (nType << 14), &pMem[0]);
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक Perक्रमmLDF(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	अचिन्हित पूर्णांक __user *pBase, *pAddress, *pFinal;
	अचिन्हित पूर्णांक nRc = 1, ग_लिखो_back = WRITE_BACK(opcode);

	pBase = (अचिन्हित पूर्णांक __user *) पढ़ोRegister(getRn(opcode));
	अगर (REG_PC == getRn(opcode)) अणु
		pBase += 2;
		ग_लिखो_back = 0;
	पूर्ण

	pFinal = pBase;
	अगर (BIT_UP_SET(opcode))
		pFinal += getOffset(opcode);
	अन्यथा
		pFinal -= getOffset(opcode);

	अगर (PREINDEXED(opcode))
		pAddress = pFinal;
	अन्यथा
		pAddress = pBase;

	चयन (opcode & MASK_TRANSFER_LENGTH) अणु
	हाल TRANSFER_SINGLE:
		loadSingle(getFd(opcode), pAddress);
		अवरोध;
	हाल TRANSFER_DOUBLE:
		loadDouble(getFd(opcode), pAddress);
		अवरोध;
#अगर_घोषित CONFIG_FPE_NWFPE_XP
	हाल TRANSFER_EXTENDED:
		loadExtended(getFd(opcode), pAddress);
		अवरोध;
#पूर्ण_अगर
	शेष:
		nRc = 0;
	पूर्ण

	अगर (ग_लिखो_back)
		ग_लिखोRegister(getRn(opcode), (अचिन्हित दीर्घ) pFinal);
	वापस nRc;
पूर्ण

अचिन्हित पूर्णांक Perक्रमmSTF(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	अचिन्हित पूर्णांक __user *pBase, *pAddress, *pFinal;
	अचिन्हित पूर्णांक nRc = 1, ग_लिखो_back = WRITE_BACK(opcode);
	काष्ठा roundingData roundData;

	roundData.mode = SetRoundingMode(opcode);
	roundData.precision = SetRoundingPrecision(opcode);
	roundData.exception = 0;

	pBase = (अचिन्हित पूर्णांक __user *) पढ़ोRegister(getRn(opcode));
	अगर (REG_PC == getRn(opcode)) अणु
		pBase += 2;
		ग_लिखो_back = 0;
	पूर्ण

	pFinal = pBase;
	अगर (BIT_UP_SET(opcode))
		pFinal += getOffset(opcode);
	अन्यथा
		pFinal -= getOffset(opcode);

	अगर (PREINDEXED(opcode))
		pAddress = pFinal;
	अन्यथा
		pAddress = pBase;

	चयन (opcode & MASK_TRANSFER_LENGTH) अणु
	हाल TRANSFER_SINGLE:
		storeSingle(&roundData, getFd(opcode), pAddress);
		अवरोध;
	हाल TRANSFER_DOUBLE:
		storeDouble(&roundData, getFd(opcode), pAddress);
		अवरोध;
#अगर_घोषित CONFIG_FPE_NWFPE_XP
	हाल TRANSFER_EXTENDED:
		storeExtended(getFd(opcode), pAddress);
		अवरोध;
#पूर्ण_अगर
	शेष:
		nRc = 0;
	पूर्ण

	अगर (roundData.exception)
		भग्न_उठाओ(roundData.exception);

	अगर (ग_लिखो_back)
		ग_लिखोRegister(getRn(opcode), (अचिन्हित दीर्घ) pFinal);
	वापस nRc;
पूर्ण

अचिन्हित पूर्णांक Perक्रमmLFM(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	अचिन्हित पूर्णांक __user *pBase, *pAddress, *pFinal;
	अचिन्हित पूर्णांक i, Fd, ग_लिखो_back = WRITE_BACK(opcode);

	pBase = (अचिन्हित पूर्णांक __user *) पढ़ोRegister(getRn(opcode));
	अगर (REG_PC == getRn(opcode)) अणु
		pBase += 2;
		ग_लिखो_back = 0;
	पूर्ण

	pFinal = pBase;
	अगर (BIT_UP_SET(opcode))
		pFinal += getOffset(opcode);
	अन्यथा
		pFinal -= getOffset(opcode);

	अगर (PREINDEXED(opcode))
		pAddress = pFinal;
	अन्यथा
		pAddress = pBase;

	Fd = getFd(opcode);
	क्रम (i = getRegisterCount(opcode); i > 0; i--) अणु
		loadMultiple(Fd, pAddress);
		pAddress += 3;
		Fd++;
		अगर (Fd == 8)
			Fd = 0;
	पूर्ण

	अगर (ग_लिखो_back)
		ग_लिखोRegister(getRn(opcode), (अचिन्हित दीर्घ) pFinal);
	वापस 1;
पूर्ण

अचिन्हित पूर्णांक Perक्रमmSFM(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	अचिन्हित पूर्णांक __user *pBase, *pAddress, *pFinal;
	अचिन्हित पूर्णांक i, Fd, ग_लिखो_back = WRITE_BACK(opcode);

	pBase = (अचिन्हित पूर्णांक __user *) पढ़ोRegister(getRn(opcode));
	अगर (REG_PC == getRn(opcode)) अणु
		pBase += 2;
		ग_लिखो_back = 0;
	पूर्ण

	pFinal = pBase;
	अगर (BIT_UP_SET(opcode))
		pFinal += getOffset(opcode);
	अन्यथा
		pFinal -= getOffset(opcode);

	अगर (PREINDEXED(opcode))
		pAddress = pFinal;
	अन्यथा
		pAddress = pBase;

	Fd = getFd(opcode);
	क्रम (i = getRegisterCount(opcode); i > 0; i--) अणु
		storeMultiple(Fd, pAddress);
		pAddress += 3;
		Fd++;
		अगर (Fd == 8)
			Fd = 0;
	पूर्ण

	अगर (ग_लिखो_back)
		ग_लिखोRegister(getRn(opcode), (अचिन्हित दीर्घ) pFinal);
	वापस 1;
पूर्ण

अचिन्हित पूर्णांक EmulateCPDT(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	अचिन्हित पूर्णांक nRc = 0;

	अगर (LDF_OP(opcode)) अणु
		nRc = Perक्रमmLDF(opcode);
	पूर्ण अन्यथा अगर (LFM_OP(opcode)) अणु
		nRc = Perक्रमmLFM(opcode);
	पूर्ण अन्यथा अगर (STF_OP(opcode)) अणु
		nRc = Perक्रमmSTF(opcode);
	पूर्ण अन्यथा अगर (SFM_OP(opcode)) अणु
		nRc = Perक्रमmSFM(opcode);
	पूर्ण अन्यथा अणु
		nRc = 0;
	पूर्ण

	वापस nRc;
पूर्ण
