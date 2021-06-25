<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    NetWinder Floating Poपूर्णांक Emulator
    (c) Rebel.COM, 1998,1999
    (c) Philip Blundell, 1999, 2001

    Direct questions, comments to Scott Bambrough <scottb@netwinder.org>

*/

#समावेश "fpa11.h"
#समावेश "fpopcode.h"
#समावेश "fpa11.inl"
#समावेश "fpmodule.h"
#समावेश "fpmodule.inl"
#समावेश "softfloat.h"

अचिन्हित पूर्णांक Perक्रमmFLT(स्थिर अचिन्हित पूर्णांक opcode);
अचिन्हित पूर्णांक Perक्रमmFIX(स्थिर अचिन्हित पूर्णांक opcode);

अटल अचिन्हित पूर्णांक Perक्रमmComparison(स्थिर अचिन्हित पूर्णांक opcode);

अचिन्हित पूर्णांक EmulateCPRT(स्थिर अचिन्हित पूर्णांक opcode)
अणु

	अगर (opcode & 0x800000) अणु
		/* This is some variant of a comparison (Perक्रमmComparison
		   will sort out which one).  Since most of the other CPRT
		   inकाष्ठाions are oddball हालs of some sort or other it
		   makes sense to pull this out पूर्णांकo a fast path.  */
		वापस Perक्रमmComparison(opcode);
	पूर्ण

	/* Hपूर्णांक to GCC that we'd like a jump table rather than a load of CMPs */
	चयन ((opcode & 0x700000) >> 20) अणु
	हाल FLT_CODE >> 20:
		वापस Perक्रमmFLT(opcode);
		अवरोध;
	हाल FIX_CODE >> 20:
		वापस Perक्रमmFIX(opcode);
		अवरोध;

	हाल WFS_CODE >> 20:
		ग_लिखोFPSR(पढ़ोRegister(getRd(opcode)));
		अवरोध;
	हाल RFS_CODE >> 20:
		ग_लिखोRegister(getRd(opcode), पढ़ोFPSR());
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अचिन्हित पूर्णांक Perक्रमmFLT(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	FPA11 *fpa11 = GET_FPA11();
	काष्ठा roundingData roundData;

	roundData.mode = SetRoundingMode(opcode);
	roundData.precision = SetRoundingPrecision(opcode);
	roundData.exception = 0;

	चयन (opcode & MASK_ROUNDING_PRECISION) अणु
	हाल ROUND_SINGLE:
		अणु
			fpa11->fType[getFn(opcode)] = typeSingle;
			fpa11->fpreg[getFn(opcode)].fSingle = पूर्णांक32_to_भग्न32(&roundData, पढ़ोRegister(getRd(opcode)));
		पूर्ण
		अवरोध;

	हाल ROUND_DOUBLE:
		अणु
			fpa11->fType[getFn(opcode)] = typeDouble;
			fpa11->fpreg[getFn(opcode)].fDouble = पूर्णांक32_to_भग्न64(पढ़ोRegister(getRd(opcode)));
		पूर्ण
		अवरोध;

#अगर_घोषित CONFIG_FPE_NWFPE_XP
	हाल ROUND_EXTENDED:
		अणु
			fpa11->fType[getFn(opcode)] = typeExtended;
			fpa11->fpreg[getFn(opcode)].fExtended = पूर्णांक32_to_भग्नx80(पढ़ोRegister(getRd(opcode)));
		पूर्ण
		अवरोध;
#पूर्ण_अगर

	शेष:
		वापस 0;
	पूर्ण

	अगर (roundData.exception)
		भग्न_उठाओ(roundData.exception);

	वापस 1;
पूर्ण

अचिन्हित पूर्णांक Perक्रमmFIX(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	FPA11 *fpa11 = GET_FPA11();
	अचिन्हित पूर्णांक Fn = getFm(opcode);
	काष्ठा roundingData roundData;

	roundData.mode = SetRoundingMode(opcode);
	roundData.precision = SetRoundingPrecision(opcode);
	roundData.exception = 0;

	चयन (fpa11->fType[Fn]) अणु
	हाल typeSingle:
		अणु
			ग_लिखोRegister(getRd(opcode), भग्न32_to_पूर्णांक32(&roundData, fpa11->fpreg[Fn].fSingle));
		पूर्ण
		अवरोध;

	हाल typeDouble:
		अणु
			ग_लिखोRegister(getRd(opcode), भग्न64_to_पूर्णांक32(&roundData, fpa11->fpreg[Fn].fDouble));
		पूर्ण
		अवरोध;

#अगर_घोषित CONFIG_FPE_NWFPE_XP
	हाल typeExtended:
		अणु
			ग_लिखोRegister(getRd(opcode), भग्नx80_to_पूर्णांक32(&roundData, fpa11->fpreg[Fn].fExtended));
		पूर्ण
		अवरोध;
#पूर्ण_अगर

	शेष:
		वापस 0;
	पूर्ण

	अगर (roundData.exception)
		भग्न_उठाओ(roundData.exception);

	वापस 1;
पूर्ण

/* This inकाष्ठाion sets the flags N, Z, C, V in the FPSR. */
अटल अचिन्हित पूर्णांक Perक्रमmComparison(स्थिर अचिन्हित पूर्णांक opcode)
अणु
	FPA11 *fpa11 = GET_FPA11();
	अचिन्हित पूर्णांक Fn = getFn(opcode), Fm = getFm(opcode);
	पूर्णांक e_flag = opcode & 0x400000;	/* 1 अगर CxFE */
	पूर्णांक n_flag = opcode & 0x200000;	/* 1 अगर CNxx */
	अचिन्हित पूर्णांक flags = 0;

#अगर_घोषित CONFIG_FPE_NWFPE_XP
	भग्नx80 rFn, rFm;

	/* Check क्रम unordered condition and convert all opeअक्रमs to 80-bit
	   क्रमmat.
	   ?? Might be some mileage in aव्योमing this conversion अगर possible.
	   Eg, अगर both opeअक्रमs are 32-bit, detect this and करो a 32-bit
	   comparison (cheaper than an 80-bit one).  */
	चयन (fpa11->fType[Fn]) अणु
	हाल typeSingle:
		//prपूर्णांकk("single.\n");
		अगर (भग्न32_is_nan(fpa11->fpreg[Fn].fSingle))
			जाओ unordered;
		rFn = भग्न32_to_भग्नx80(fpa11->fpreg[Fn].fSingle);
		अवरोध;

	हाल typeDouble:
		//prपूर्णांकk("double.\n");
		अगर (भग्न64_is_nan(fpa11->fpreg[Fn].fDouble))
			जाओ unordered;
		rFn = भग्न64_to_भग्नx80(fpa11->fpreg[Fn].fDouble);
		अवरोध;

	हाल typeExtended:
		//prपूर्णांकk("extended.\n");
		अगर (भग्नx80_is_nan(fpa11->fpreg[Fn].fExtended))
			जाओ unordered;
		rFn = fpa11->fpreg[Fn].fExtended;
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	अगर (CONSTANT_FM(opcode)) अणु
		//prपूर्णांकk("Fm is a constant: #%d.\n",Fm);
		rFm = getExtendedConstant(Fm);
		अगर (भग्नx80_is_nan(rFm))
			जाओ unordered;
	पूर्ण अन्यथा अणु
		//prपूर्णांकk("Fm = r%d which contains a ",Fm);
		चयन (fpa11->fType[Fm]) अणु
		हाल typeSingle:
			//prपूर्णांकk("single.\n");
			अगर (भग्न32_is_nan(fpa11->fpreg[Fm].fSingle))
				जाओ unordered;
			rFm = भग्न32_to_भग्नx80(fpa11->fpreg[Fm].fSingle);
			अवरोध;

		हाल typeDouble:
			//prपूर्णांकk("double.\n");
			अगर (भग्न64_is_nan(fpa11->fpreg[Fm].fDouble))
				जाओ unordered;
			rFm = भग्न64_to_भग्नx80(fpa11->fpreg[Fm].fDouble);
			अवरोध;

		हाल typeExtended:
			//prपूर्णांकk("extended.\n");
			अगर (भग्नx80_is_nan(fpa11->fpreg[Fm].fExtended))
				जाओ unordered;
			rFm = fpa11->fpreg[Fm].fExtended;
			अवरोध;

		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (n_flag)
		rFm.high ^= 0x8000;

	/* test क्रम less than condition */
	अगर (भग्नx80_lt(rFn, rFm))
		flags |= CC_NEGATIVE;

	/* test क्रम equal condition */
	अगर (भग्नx80_eq(rFn, rFm))
		flags |= CC_ZERO;

	/* test क्रम greater than or equal condition */
	अगर (भग्नx80_lt(rFm, rFn))
		flags |= CC_CARRY;

#अन्यथा
	अगर (CONSTANT_FM(opcode)) अणु
		/* Fm is a स्थिरant.  Do the comparison in whatever precision
		   Fn happens to be stored in.  */
		अगर (fpa11->fType[Fn] == typeSingle) अणु
			भग्न32 rFm = getSingleConstant(Fm);
			भग्न32 rFn = fpa11->fpreg[Fn].fSingle;

			अगर (भग्न32_is_nan(rFn))
				जाओ unordered;

			अगर (n_flag)
				rFm ^= 0x80000000;

			/* test क्रम less than condition */
			अगर (भग्न32_lt_nocheck(rFn, rFm))
				flags |= CC_NEGATIVE;

			/* test क्रम equal condition */
			अगर (भग्न32_eq_nocheck(rFn, rFm))
				flags |= CC_ZERO;

			/* test क्रम greater than or equal condition */
			अगर (भग्न32_lt_nocheck(rFm, rFn))
				flags |= CC_CARRY;
		पूर्ण अन्यथा अणु
			भग्न64 rFm = getDoubleConstant(Fm);
			भग्न64 rFn = fpa11->fpreg[Fn].fDouble;

			अगर (भग्न64_is_nan(rFn))
				जाओ unordered;

			अगर (n_flag)
				rFm ^= 0x8000000000000000ULL;

			/* test क्रम less than condition */
			अगर (भग्न64_lt_nocheck(rFn, rFm))
				flags |= CC_NEGATIVE;

			/* test क्रम equal condition */
			अगर (भग्न64_eq_nocheck(rFn, rFm))
				flags |= CC_ZERO;

			/* test क्रम greater than or equal condition */
			अगर (भग्न64_lt_nocheck(rFm, rFn))
				flags |= CC_CARRY;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Both opeअक्रमs are in रेजिस्टरs.  */
		अगर (fpa11->fType[Fn] == typeSingle
		    && fpa11->fType[Fm] == typeSingle) अणु
			भग्न32 rFm = fpa11->fpreg[Fm].fSingle;
			भग्न32 rFn = fpa11->fpreg[Fn].fSingle;

			अगर (भग्न32_is_nan(rFn)
			    || भग्न32_is_nan(rFm))
				जाओ unordered;

			अगर (n_flag)
				rFm ^= 0x80000000;

			/* test क्रम less than condition */
			अगर (भग्न32_lt_nocheck(rFn, rFm))
				flags |= CC_NEGATIVE;

			/* test क्रम equal condition */
			अगर (भग्न32_eq_nocheck(rFn, rFm))
				flags |= CC_ZERO;

			/* test क्रम greater than or equal condition */
			अगर (भग्न32_lt_nocheck(rFm, rFn))
				flags |= CC_CARRY;
		पूर्ण अन्यथा अणु
			/* Promote 32-bit opeअक्रम to 64 bits.  */
			भग्न64 rFm, rFn;

			rFm = (fpa11->fType[Fm] == typeSingle) ?
			    भग्न32_to_भग्न64(fpa11->fpreg[Fm].fSingle)
			    : fpa11->fpreg[Fm].fDouble;

			rFn = (fpa11->fType[Fn] == typeSingle) ?
			    भग्न32_to_भग्न64(fpa11->fpreg[Fn].fSingle)
			    : fpa11->fpreg[Fn].fDouble;

			अगर (भग्न64_is_nan(rFn)
			    || भग्न64_is_nan(rFm))
				जाओ unordered;

			अगर (n_flag)
				rFm ^= 0x8000000000000000ULL;

			/* test क्रम less than condition */
			अगर (भग्न64_lt_nocheck(rFn, rFm))
				flags |= CC_NEGATIVE;

			/* test क्रम equal condition */
			अगर (भग्न64_eq_nocheck(rFn, rFm))
				flags |= CC_ZERO;

			/* test क्रम greater than or equal condition */
			अगर (भग्न64_lt_nocheck(rFm, rFn))
				flags |= CC_CARRY;
		पूर्ण
	पूर्ण

#पूर्ण_अगर

	ग_लिखोConditionCodes(flags);

	वापस 1;

      unordered:
	/* ?? The FPA data sheet is pretty vague about this, in particular
	   about whether the non-E comparisons can ever उठाओ exceptions.
	   This implementation is based on a combination of what it says in
	   the data sheet, observation of how the Acorn emulator actually
	   behaves (and how programs expect it to) and guesswork.  */
	flags |= CC_OVERFLOW;
	flags &= ~(CC_ZERO | CC_NEGATIVE);

	अगर (BIT_AC & पढ़ोFPSR())
		flags |= CC_CARRY;

	अगर (e_flag)
		भग्न_उठाओ(भग्न_flag_invalid);

	ग_लिखोConditionCodes(flags);
	वापस 1;
पूर्ण
