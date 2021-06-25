<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    NetWinder Floating Poपूर्णांक Emulator
    (c) Rebel.COM, 1998,1999

    Direct questions, comments to Scott Bambrough <scottb@netwinder.org>

*/

#समावेश "fpa11.h"
#समावेश "softfloat.h"
#समावेश "fpopcode.h"

जोड़ भग्न64_components अणु
	भग्न64 f64;
	अचिन्हित पूर्णांक i[2];
पूर्ण;

भग्न64 भग्न64_exp(भग्न64 Fm);
भग्न64 भग्न64_ln(भग्न64 Fm);
भग्न64 भग्न64_sin(भग्न64 rFm);
भग्न64 भग्न64_cos(भग्न64 rFm);
भग्न64 भग्न64_arcsin(भग्न64 rFm);
भग्न64 भग्न64_arctan(भग्न64 rFm);
भग्न64 भग्न64_log(भग्न64 rFm);
भग्न64 भग्न64_tan(भग्न64 rFm);
भग्न64 भग्न64_arccos(भग्न64 rFm);
भग्न64 भग्न64_घात(भग्न64 rFn, भग्न64 rFm);
भग्न64 भग्न64_pol(भग्न64 rFn, भग्न64 rFm);

अटल भग्न64 भग्न64_rsf(काष्ठा roundingData *roundData, भग्न64 rFn, भग्न64 rFm)
अणु
	वापस भग्न64_sub(roundData, rFm, rFn);
पूर्ण

अटल भग्न64 भग्न64_rdv(काष्ठा roundingData *roundData, भग्न64 rFn, भग्न64 rFm)
अणु
	वापस भग्न64_भाग(roundData, rFm, rFn);
पूर्ण

अटल भग्न64 (*स्थिर dyadic_द्विगुन[16])(काष्ठा roundingData*, भग्न64 rFn, भग्न64 rFm) = अणु
	[ADF_CODE >> 20] = भग्न64_add,
	[MUF_CODE >> 20] = भग्न64_mul,
	[SUF_CODE >> 20] = भग्न64_sub,
	[RSF_CODE >> 20] = भग्न64_rsf,
	[DVF_CODE >> 20] = भग्न64_भाग,
	[RDF_CODE >> 20] = भग्न64_rdv,
	[RMF_CODE >> 20] = भग्न64_rem,

	/* strictly, these opcodes should not be implemented */
	[FML_CODE >> 20] = भग्न64_mul,
	[FDV_CODE >> 20] = भग्न64_भाग,
	[FRD_CODE >> 20] = भग्न64_rdv,
पूर्ण;

अटल भग्न64 भग्न64_mvf(काष्ठा roundingData *roundData,भग्न64 rFm)
अणु
	वापस rFm;
पूर्ण

अटल भग्न64 भग्न64_mnf(काष्ठा roundingData *roundData,भग्न64 rFm)
अणु
	जोड़ भग्न64_components u;

	u.f64 = rFm;
#अगर_घोषित __ARMEB__
	u.i[0] ^= 0x80000000;
#अन्यथा
	u.i[1] ^= 0x80000000;
#पूर्ण_अगर

	वापस u.f64;
पूर्ण

अटल भग्न64 भग्न64_असल(काष्ठा roundingData *roundData,भग्न64 rFm)
अणु
	जोड़ भग्न64_components u;

	u.f64 = rFm;
#अगर_घोषित __ARMEB__
	u.i[0] &= 0x7fffffff;
#अन्यथा
	u.i[1] &= 0x7fffffff;
#पूर्ण_अगर

	वापस u.f64;
पूर्ण

अटल भग्न64 (*स्थिर monadic_द्विगुन[16])(काष्ठा roundingData *, भग्न64 rFm) = अणु
	[MVF_CODE >> 20] = भग्न64_mvf,
	[MNF_CODE >> 20] = भग्न64_mnf,
	[ABS_CODE >> 20] = भग्न64_असल,
	[RND_CODE >> 20] = भग्न64_round_to_पूर्णांक,
	[URD_CODE >> 20] = भग्न64_round_to_पूर्णांक,
	[SQT_CODE >> 20] = भग्न64_वर्ग_मूल,
	[NRM_CODE >> 20] = भग्न64_mvf,
पूर्ण;

अचिन्हित पूर्णांक DoubleCPDO(काष्ठा roundingData *roundData, स्थिर अचिन्हित पूर्णांक opcode, FPREG * rFd)
अणु
	FPA11 *fpa11 = GET_FPA11();
	भग्न64 rFm;
	अचिन्हित पूर्णांक Fm, opc_mask_shअगरt;

	Fm = getFm(opcode);
	अगर (CONSTANT_FM(opcode)) अणु
		rFm = getDoubleConstant(Fm);
	पूर्ण अन्यथा अणु
		चयन (fpa11->fType[Fm]) अणु
		हाल typeSingle:
			rFm = भग्न32_to_भग्न64(fpa11->fpreg[Fm].fSingle);
			अवरोध;

		हाल typeDouble:
			rFm = fpa11->fpreg[Fm].fDouble;
			अवरोध;

		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	opc_mask_shअगरt = (opcode & MASK_ARITHMETIC_OPCODE) >> 20;
	अगर (!MONADIC_INSTRUCTION(opcode)) अणु
		अचिन्हित पूर्णांक Fn = getFn(opcode);
		भग्न64 rFn;

		चयन (fpa11->fType[Fn]) अणु
		हाल typeSingle:
			rFn = भग्न32_to_भग्न64(fpa11->fpreg[Fn].fSingle);
			अवरोध;

		हाल typeDouble:
			rFn = fpa11->fpreg[Fn].fDouble;
			अवरोध;

		शेष:
			वापस 0;
		पूर्ण

		अगर (dyadic_द्विगुन[opc_mask_shअगरt]) अणु
			rFd->fDouble = dyadic_द्विगुन[opc_mask_shअगरt](roundData, rFn, rFm);
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (monadic_द्विगुन[opc_mask_shअगरt]) अणु
			rFd->fDouble = monadic_द्विगुन[opc_mask_shअगरt](roundData, rFm);
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण
