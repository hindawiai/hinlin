<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    NetWinder Floating Poपूर्णांक Emulator
    (c) Rebel.COM, 1998,1999
    (c) Philip Blundell, 2001

    Direct questions, comments to Scott Bambrough <scottb@netwinder.org>

*/

#समावेश "fpa11.h"
#समावेश "softfloat.h"
#समावेश "fpopcode.h"

भग्न32 भग्न32_exp(भग्न32 Fm);
भग्न32 भग्न32_ln(भग्न32 Fm);
भग्न32 भग्न32_sin(भग्न32 rFm);
भग्न32 भग्न32_cos(भग्न32 rFm);
भग्न32 भग्न32_arcsin(भग्न32 rFm);
भग्न32 भग्न32_arctan(भग्न32 rFm);
भग्न32 भग्न32_log(भग्न32 rFm);
भग्न32 भग्न32_tan(भग्न32 rFm);
भग्न32 भग्न32_arccos(भग्न32 rFm);
भग्न32 भग्न32_घात(भग्न32 rFn, भग्न32 rFm);
भग्न32 भग्न32_pol(भग्न32 rFn, भग्न32 rFm);

अटल भग्न32 भग्न32_rsf(काष्ठा roundingData *roundData, भग्न32 rFn, भग्न32 rFm)
अणु
	वापस भग्न32_sub(roundData, rFm, rFn);
पूर्ण

अटल भग्न32 भग्न32_rdv(काष्ठा roundingData *roundData, भग्न32 rFn, भग्न32 rFm)
अणु
	वापस भग्न32_भाग(roundData, rFm, rFn);
पूर्ण

अटल भग्न32 (*स्थिर dyadic_single[16])(काष्ठा roundingData *, भग्न32 rFn, भग्न32 rFm) = अणु
	[ADF_CODE >> 20] = भग्न32_add,
	[MUF_CODE >> 20] = भग्न32_mul,
	[SUF_CODE >> 20] = भग्न32_sub,
	[RSF_CODE >> 20] = भग्न32_rsf,
	[DVF_CODE >> 20] = भग्न32_भाग,
	[RDF_CODE >> 20] = भग्न32_rdv,
	[RMF_CODE >> 20] = भग्न32_rem,

	[FML_CODE >> 20] = भग्न32_mul,
	[FDV_CODE >> 20] = भग्न32_भाग,
	[FRD_CODE >> 20] = भग्न32_rdv,
पूर्ण;

अटल भग्न32 भग्न32_mvf(काष्ठा roundingData *roundData, भग्न32 rFm)
अणु
	वापस rFm;
पूर्ण

अटल भग्न32 भग्न32_mnf(काष्ठा roundingData *roundData, भग्न32 rFm)
अणु
	वापस rFm ^ 0x80000000;
पूर्ण

अटल भग्न32 भग्न32_असल(काष्ठा roundingData *roundData, भग्न32 rFm)
अणु
	वापस rFm & 0x7fffffff;
पूर्ण

अटल भग्न32 (*स्थिर monadic_single[16])(काष्ठा roundingData*, भग्न32 rFm) = अणु
	[MVF_CODE >> 20] = भग्न32_mvf,
	[MNF_CODE >> 20] = भग्न32_mnf,
	[ABS_CODE >> 20] = भग्न32_असल,
	[RND_CODE >> 20] = भग्न32_round_to_पूर्णांक,
	[URD_CODE >> 20] = भग्न32_round_to_पूर्णांक,
	[SQT_CODE >> 20] = भग्न32_वर्ग_मूल,
	[NRM_CODE >> 20] = भग्न32_mvf,
पूर्ण;

अचिन्हित पूर्णांक SingleCPDO(काष्ठा roundingData *roundData, स्थिर अचिन्हित पूर्णांक opcode, FPREG * rFd)
अणु
	FPA11 *fpa11 = GET_FPA11();
	भग्न32 rFm;
	अचिन्हित पूर्णांक Fm, opc_mask_shअगरt;

	Fm = getFm(opcode);
	अगर (CONSTANT_FM(opcode)) अणु
		rFm = getSingleConstant(Fm);
	पूर्ण अन्यथा अगर (fpa11->fType[Fm] == typeSingle) अणु
		rFm = fpa11->fpreg[Fm].fSingle;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	opc_mask_shअगरt = (opcode & MASK_ARITHMETIC_OPCODE) >> 20;
	अगर (!MONADIC_INSTRUCTION(opcode)) अणु
		अचिन्हित पूर्णांक Fn = getFn(opcode);
		भग्न32 rFn;

		अगर (fpa11->fType[Fn] == typeSingle &&
		    dyadic_single[opc_mask_shअगरt]) अणु
			rFn = fpa11->fpreg[Fn].fSingle;
			rFd->fSingle = dyadic_single[opc_mask_shअगरt](roundData, rFn, rFm);
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (monadic_single[opc_mask_shअगरt]) अणु
			rFd->fSingle = monadic_single[opc_mask_shअगरt](roundData, rFm);
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण
