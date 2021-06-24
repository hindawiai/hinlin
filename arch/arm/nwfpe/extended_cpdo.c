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

भग्नx80 भग्नx80_exp(भग्नx80 Fm);
भग्नx80 भग्नx80_ln(भग्नx80 Fm);
भग्नx80 भग्नx80_sin(भग्नx80 rFm);
भग्नx80 भग्नx80_cos(भग्नx80 rFm);
भग्नx80 भग्नx80_arcsin(भग्नx80 rFm);
भग्नx80 भग्नx80_arctan(भग्नx80 rFm);
भग्नx80 भग्नx80_log(भग्नx80 rFm);
भग्नx80 भग्नx80_tan(भग्नx80 rFm);
भग्नx80 भग्नx80_arccos(भग्नx80 rFm);
भग्नx80 भग्नx80_घात(भग्नx80 rFn, भग्नx80 rFm);
भग्नx80 भग्नx80_pol(भग्नx80 rFn, भग्नx80 rFm);

अटल भग्नx80 भग्नx80_rsf(काष्ठा roundingData *roundData, भग्नx80 rFn, भग्नx80 rFm)
अणु
	वापस भग्नx80_sub(roundData, rFm, rFn);
पूर्ण

अटल भग्नx80 भग्नx80_rdv(काष्ठा roundingData *roundData, भग्नx80 rFn, भग्नx80 rFm)
अणु
	वापस भग्नx80_भाग(roundData, rFm, rFn);
पूर्ण

अटल भग्नx80 (*स्थिर dyadic_extended[16])(काष्ठा roundingData*, भग्नx80 rFn, भग्नx80 rFm) = अणु
	[ADF_CODE >> 20] = भग्नx80_add,
	[MUF_CODE >> 20] = भग्नx80_mul,
	[SUF_CODE >> 20] = भग्नx80_sub,
	[RSF_CODE >> 20] = भग्नx80_rsf,
	[DVF_CODE >> 20] = भग्नx80_भाग,
	[RDF_CODE >> 20] = भग्नx80_rdv,
	[RMF_CODE >> 20] = भग्नx80_rem,

	/* strictly, these opcodes should not be implemented */
	[FML_CODE >> 20] = भग्नx80_mul,
	[FDV_CODE >> 20] = भग्नx80_भाग,
	[FRD_CODE >> 20] = भग्नx80_rdv,
पूर्ण;

अटल भग्नx80 भग्नx80_mvf(काष्ठा roundingData *roundData, भग्नx80 rFm)
अणु
	वापस rFm;
पूर्ण

अटल भग्नx80 भग्नx80_mnf(काष्ठा roundingData *roundData, भग्नx80 rFm)
अणु
	rFm.high ^= 0x8000;
	वापस rFm;
पूर्ण

अटल भग्नx80 भग्नx80_असल(काष्ठा roundingData *roundData, भग्नx80 rFm)
अणु
	rFm.high &= 0x7fff;
	वापस rFm;
पूर्ण

अटल भग्नx80 (*स्थिर monadic_extended[16])(काष्ठा roundingData*, भग्नx80 rFm) = अणु
	[MVF_CODE >> 20] = भग्नx80_mvf,
	[MNF_CODE >> 20] = भग्नx80_mnf,
	[ABS_CODE >> 20] = भग्नx80_असल,
	[RND_CODE >> 20] = भग्नx80_round_to_पूर्णांक,
	[URD_CODE >> 20] = भग्नx80_round_to_पूर्णांक,
	[SQT_CODE >> 20] = भग्नx80_वर्ग_मूल,
	[NRM_CODE >> 20] = भग्नx80_mvf,
पूर्ण;

अचिन्हित पूर्णांक ExtendedCPDO(काष्ठा roundingData *roundData, स्थिर अचिन्हित पूर्णांक opcode, FPREG * rFd)
अणु
	FPA11 *fpa11 = GET_FPA11();
	भग्नx80 rFm;
	अचिन्हित पूर्णांक Fm, opc_mask_shअगरt;

	Fm = getFm(opcode);
	अगर (CONSTANT_FM(opcode)) अणु
		rFm = getExtendedConstant(Fm);
	पूर्ण अन्यथा अणु
		चयन (fpa11->fType[Fm]) अणु
		हाल typeSingle:
			rFm = भग्न32_to_भग्नx80(fpa11->fpreg[Fm].fSingle);
			अवरोध;

		हाल typeDouble:
			rFm = भग्न64_to_भग्नx80(fpa11->fpreg[Fm].fDouble);
			अवरोध;

		हाल typeExtended:
			rFm = fpa11->fpreg[Fm].fExtended;
			अवरोध;

		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	opc_mask_shअगरt = (opcode & MASK_ARITHMETIC_OPCODE) >> 20;
	अगर (!MONADIC_INSTRUCTION(opcode)) अणु
		अचिन्हित पूर्णांक Fn = getFn(opcode);
		भग्नx80 rFn;

		चयन (fpa11->fType[Fn]) अणु
		हाल typeSingle:
			rFn = भग्न32_to_भग्नx80(fpa11->fpreg[Fn].fSingle);
			अवरोध;

		हाल typeDouble:
			rFn = भग्न64_to_भग्नx80(fpa11->fpreg[Fn].fDouble);
			अवरोध;

		हाल typeExtended:
			rFn = fpa11->fpreg[Fn].fExtended;
			अवरोध;

		शेष:
			वापस 0;
		पूर्ण

		अगर (dyadic_extended[opc_mask_shअगरt]) अणु
			rFd->fExtended = dyadic_extended[opc_mask_shअगरt](roundData, rFn, rFm);
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (monadic_extended[opc_mask_shअगरt]) अणु
			rFd->fExtended = monadic_extended[opc_mask_shअगरt](roundData, rFm);
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण
