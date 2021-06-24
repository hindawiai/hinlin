<शैली गुरु>
/*
 *  linux/arch/arm/vfp/vfpद्विगुन.c
 *
 * This code is derived in part from John R. Housers softभग्न library, which
 * carries the following notice:
 *
 * ===========================================================================
 * This C source file is part of the SoftFloat IEC/IEEE Floating-poपूर्णांक
 * Arithmetic Package, Release 2.
 *
 * Written by John R. Hauser.  This work was made possible in part by the
 * International Computer Science Institute, located at Suite 600, 1947 Center
 * Street, Berkeley, Calअगरornia 94704.  Funding was partially provided by the
 * National Science Foundation under grant MIP-9311980.  The original version
 * of this code was written as part of a project to build a fixed-poपूर्णांक vector
 * processor in collaboration with the University of Calअगरornia at Berkeley,
 * overseen by Profs. Nelson Morgan and John Wawrzynek.  More inक्रमmation
 * is available through the web page `http://HTTP.CS.Berkeley.EDU/~jhauser/
 * arithmetic/softभग्न.सपंचांगl'.
 *
 * THIS SOFTWARE IS DISTRIBUTED AS IS, FOR FREE.  Although reasonable efक्रमt
 * has been made to aव्योम it, THIS SOFTWARE MAY CONTAIN FAULTS THAT WILL AT
 * TIMES RESULT IN INCORRECT BEHAVIOR.  USE OF THIS SOFTWARE IS RESTRICTED TO
 * PERSONS AND ORGANIZATIONS WHO CAN AND WILL TAKE FULL RESPONSIBILITY FOR ANY
 * AND ALL LOSSES, COSTS, OR OTHER PROBLEMS ARISING FROM ITS USE.
 *
 * Derivative works are acceptable, even क्रम commercial purposes, so दीर्घ as
 * (1) they include prominent notice that the work is derivative, and (2) they
 * include prominent notice akin to these three paragraphs क्रम those parts of
 * this code that are retained.
 * ===========================================================================
 */
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/vfp.h>

#समावेश "vfpinstr.h"
#समावेश "vfp.h"

अटल काष्ठा vfp_द्विगुन vfp_द्विगुन_शेष_qnan = अणु
	.exponent	= 2047,
	.sign		= 0,
	.signअगरicand	= VFP_DOUBLE_SIGNIFICAND_Qन_अंक,
पूर्ण;

अटल व्योम vfp_द्विगुन_dump(स्थिर अक्षर *str, काष्ठा vfp_द्विगुन *d)
अणु
	pr_debug("VFP: %s: sign=%d exponent=%d significand=%016llx\n",
		 str, d->sign != 0, d->exponent, d->signअगरicand);
पूर्ण

अटल व्योम vfp_द्विगुन_normalise_denormal(काष्ठा vfp_द्विगुन *vd)
अणु
	पूर्णांक bits = 31 - fls(vd->signअगरicand >> 32);
	अगर (bits == 31)
		bits = 63 - fls(vd->signअगरicand);

	vfp_द्विगुन_dump("normalise_denormal: in", vd);

	अगर (bits) अणु
		vd->exponent -= bits - 1;
		vd->signअगरicand <<= bits;
	पूर्ण

	vfp_द्विगुन_dump("normalise_denormal: out", vd);
पूर्ण

u32 vfp_द्विगुन_normaliseround(पूर्णांक dd, काष्ठा vfp_द्विगुन *vd, u32 fpscr, u32 exceptions, स्थिर अक्षर *func)
अणु
	u64 signअगरicand, incr;
	पूर्णांक exponent, shअगरt, underflow;
	u32 rmode;

	vfp_द्विगुन_dump("pack: in", vd);

	/*
	 * Infinities and NaNs are a special हाल.
	 */
	अगर (vd->exponent == 2047 && (vd->signअगरicand == 0 || exceptions))
		जाओ pack;

	/*
	 * Special-हाल zero.
	 */
	अगर (vd->signअगरicand == 0) अणु
		vd->exponent = 0;
		जाओ pack;
	पूर्ण

	exponent = vd->exponent;
	signअगरicand = vd->signअगरicand;

	shअगरt = 32 - fls(signअगरicand >> 32);
	अगर (shअगरt == 32)
		shअगरt = 64 - fls(signअगरicand);
	अगर (shअगरt) अणु
		exponent -= shअगरt;
		signअगरicand <<= shअगरt;
	पूर्ण

#अगर_घोषित DEBUG
	vd->exponent = exponent;
	vd->signअगरicand = signअगरicand;
	vfp_द्विगुन_dump("pack: normalised", vd);
#पूर्ण_अगर

	/*
	 * Tiny number?
	 */
	underflow = exponent < 0;
	अगर (underflow) अणु
		signअगरicand = vfp_shअगरtright64jamming(signअगरicand, -exponent);
		exponent = 0;
#अगर_घोषित DEBUG
		vd->exponent = exponent;
		vd->signअगरicand = signअगरicand;
		vfp_द्विगुन_dump("pack: tiny number", vd);
#पूर्ण_अगर
		अगर (!(signअगरicand & ((1ULL << (VFP_DOUBLE_LOW_BITS + 1)) - 1)))
			underflow = 0;
	पूर्ण

	/*
	 * Select rounding increment.
	 */
	incr = 0;
	rmode = fpscr & FPSCR_RMODE_MASK;

	अगर (rmode == FPSCR_ROUND_NEAREST) अणु
		incr = 1ULL << VFP_DOUBLE_LOW_BITS;
		अगर ((signअगरicand & (1ULL << (VFP_DOUBLE_LOW_BITS + 1))) == 0)
			incr -= 1;
	पूर्ण अन्यथा अगर (rmode == FPSCR_ROUND_TOZERO) अणु
		incr = 0;
	पूर्ण अन्यथा अगर ((rmode == FPSCR_ROUND_PLUSINF) ^ (vd->sign != 0))
		incr = (1ULL << (VFP_DOUBLE_LOW_BITS + 1)) - 1;

	pr_debug("VFP: rounding increment = 0x%08llx\n", incr);

	/*
	 * Is our rounding going to overflow?
	 */
	अगर ((signअगरicand + incr) < signअगरicand) अणु
		exponent += 1;
		signअगरicand = (signअगरicand >> 1) | (signअगरicand & 1);
		incr >>= 1;
#अगर_घोषित DEBUG
		vd->exponent = exponent;
		vd->signअगरicand = signअगरicand;
		vfp_द्विगुन_dump("pack: overflow", vd);
#पूर्ण_अगर
	पूर्ण

	/*
	 * If any of the low bits (which will be shअगरted out of the
	 * number) are non-zero, the result is inexact.
	 */
	अगर (signअगरicand & ((1 << (VFP_DOUBLE_LOW_BITS + 1)) - 1))
		exceptions |= FPSCR_IXC;

	/*
	 * Do our rounding.
	 */
	signअगरicand += incr;

	/*
	 * Infinity?
	 */
	अगर (exponent >= 2046) अणु
		exceptions |= FPSCR_OFC | FPSCR_IXC;
		अगर (incr == 0) अणु
			vd->exponent = 2045;
			vd->signअगरicand = 0x7fffffffffffffffULL;
		पूर्ण अन्यथा अणु
			vd->exponent = 2047;		/* infinity */
			vd->signअगरicand = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (signअगरicand >> (VFP_DOUBLE_LOW_BITS + 1) == 0)
			exponent = 0;
		अगर (exponent || signअगरicand > 0x8000000000000000ULL)
			underflow = 0;
		अगर (underflow)
			exceptions |= FPSCR_UFC;
		vd->exponent = exponent;
		vd->signअगरicand = signअगरicand >> 1;
	पूर्ण

 pack:
	vfp_द्विगुन_dump("pack: final", vd);
	अणु
		s64 d = vfp_द्विगुन_pack(vd);
		pr_debug("VFP: %s: d(d%d)=%016llx exceptions=%08x\n", func,
			 dd, d, exceptions);
		vfp_put_द्विगुन(d, dd);
	पूर्ण
	वापस exceptions;
पूर्ण

/*
 * Propagate the NaN, setting exceptions अगर it is संकेतling.
 * 'n' is always a NaN.  'm' may be a number, NaN or infinity.
 */
अटल u32
vfp_propagate_nan(काष्ठा vfp_द्विगुन *vdd, काष्ठा vfp_द्विगुन *vdn,
		  काष्ठा vfp_द्विगुन *vdm, u32 fpscr)
अणु
	काष्ठा vfp_द्विगुन *nan;
	पूर्णांक tn, पंचांग = 0;

	tn = vfp_द्विगुन_type(vdn);

	अगर (vdm)
		पंचांग = vfp_द्विगुन_type(vdm);

	अगर (fpscr & FPSCR_DEFAULT_न_अंक)
		/*
		 * Default NaN mode - always वापसs a quiet NaN
		 */
		nan = &vfp_द्विगुन_शेष_qnan;
	अन्यथा अणु
		/*
		 * Contemporary mode - select the first संकेतling
		 * न_अंक, or अगर neither are संकेतling, the first
		 * quiet न_अंक.
		 */
		अगर (tn == VFP_Sन_अंक || (पंचांग != VFP_Sन_अंक && tn == VFP_Qन_अंक))
			nan = vdn;
		अन्यथा
			nan = vdm;
		/*
		 * Make the NaN quiet.
		 */
		nan->signअगरicand |= VFP_DOUBLE_SIGNIFICAND_Qन_अंक;
	पूर्ण

	*vdd = *nan;

	/*
	 * If one was a संकेतling न_अंक, उठाओ invalid operation.
	 */
	वापस tn == VFP_Sन_अंक || पंचांग == VFP_Sन_अंक ? FPSCR_IOC : VFP_न_अंक_FLAG;
पूर्ण

/*
 * Extended operations
 */
अटल u32 vfp_द्विगुन_भ_असल(पूर्णांक dd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	vfp_put_द्विगुन(vfp_द्विगुन_packed_असल(vfp_get_द्विगुन(dm)), dd);
	वापस 0;
पूर्ण

अटल u32 vfp_द्विगुन_fcpy(पूर्णांक dd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	vfp_put_द्विगुन(vfp_get_द्विगुन(dm), dd);
	वापस 0;
पूर्ण

अटल u32 vfp_द्विगुन_fneg(पूर्णांक dd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	vfp_put_द्विगुन(vfp_द्विगुन_packed_negate(vfp_get_द्विगुन(dm)), dd);
	वापस 0;
पूर्ण

अटल u32 vfp_द्विगुन_fवर्ग_मूल(पूर्णांक dd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	काष्ठा vfp_द्विगुन vdm, vdd;
	पूर्णांक ret, पंचांग;

	vfp_द्विगुन_unpack(&vdm, vfp_get_द्विगुन(dm));
	पंचांग = vfp_द्विगुन_type(&vdm);
	अगर (पंचांग & (VFP_न_अंक|VFP_अनन्त)) अणु
		काष्ठा vfp_द्विगुन *vdp = &vdd;

		अगर (पंचांग & VFP_न_अंक)
			ret = vfp_propagate_nan(vdp, &vdm, शून्य, fpscr);
		अन्यथा अगर (vdm.sign == 0) अणु
 वर्ग_मूल_copy:
			vdp = &vdm;
			ret = 0;
		पूर्ण अन्यथा अणु
 वर्ग_मूल_invalid:
			vdp = &vfp_द्विगुन_शेष_qnan;
			ret = FPSCR_IOC;
		पूर्ण
		vfp_put_द्विगुन(vfp_द्विगुन_pack(vdp), dd);
		वापस ret;
	पूर्ण

	/*
	 * वर्ग_मूल(+/- 0) == +/- 0
	 */
	अगर (पंचांग & VFP_ZERO)
		जाओ वर्ग_मूल_copy;

	/*
	 * Normalise a denormalised number
	 */
	अगर (पंचांग & VFP_DENORMAL)
		vfp_द्विगुन_normalise_denormal(&vdm);

	/*
	 * वर्ग_मूल(<0) = invalid
	 */
	अगर (vdm.sign)
		जाओ वर्ग_मूल_invalid;

	vfp_द्विगुन_dump("sqrt", &vdm);

	/*
	 * Estimate the square root.
	 */
	vdd.sign = 0;
	vdd.exponent = ((vdm.exponent - 1023) >> 1) + 1023;
	vdd.signअगरicand = (u64)vfp_estimate_वर्ग_मूल_signअगरicand(vdm.exponent, vdm.signअगरicand >> 32) << 31;

	vfp_द्विगुन_dump("sqrt estimate1", &vdd);

	vdm.signअगरicand >>= 1 + (vdm.exponent & 1);
	vdd.signअगरicand += 2 + vfp_estimate_भाग128to64(vdm.signअगरicand, 0, vdd.signअगरicand);

	vfp_द्विगुन_dump("sqrt estimate2", &vdd);

	/*
	 * And now adjust.
	 */
	अगर ((vdd.signअगरicand & VFP_DOUBLE_LOW_BITS_MASK) <= 5) अणु
		अगर (vdd.signअगरicand < 2) अणु
			vdd.signअगरicand = ~0ULL;
		पूर्ण अन्यथा अणु
			u64 termh, terml, remh, reml;
			vdm.signअगरicand <<= 2;
			mul64to128(&termh, &terml, vdd.signअगरicand, vdd.signअगरicand);
			sub128(&remh, &reml, vdm.signअगरicand, 0, termh, terml);
			जबतक ((s64)remh < 0) अणु
				vdd.signअगरicand -= 1;
				shअगरt64left(&termh, &terml, vdd.signअगरicand);
				terml |= 1;
				add128(&remh, &reml, remh, reml, termh, terml);
			पूर्ण
			vdd.signअगरicand |= (remh | reml) != 0;
		पूर्ण
	पूर्ण
	vdd.signअगरicand = vfp_shअगरtright64jamming(vdd.signअगरicand, 1);

	वापस vfp_द्विगुन_normaliseround(dd, &vdd, fpscr, 0, "fsqrt");
पूर्ण

/*
 * Equal	:= ZC
 * Less than	:= N
 * Greater than	:= C
 * Unordered	:= CV
 */
अटल u32 vfp_compare(पूर्णांक dd, पूर्णांक संकेत_on_qnan, पूर्णांक dm, u32 fpscr)
अणु
	s64 d, m;
	u32 ret = 0;

	m = vfp_get_द्विगुन(dm);
	अगर (vfp_द्विगुन_packed_exponent(m) == 2047 && vfp_द्विगुन_packed_mantissa(m)) अणु
		ret |= FPSCR_C | FPSCR_V;
		अगर (संकेत_on_qnan || !(vfp_द्विगुन_packed_mantissa(m) & (1ULL << (VFP_DOUBLE_MANTISSA_BITS - 1))))
			/*
			 * Signalling NaN, or संकेतling on quiet NaN
			 */
			ret |= FPSCR_IOC;
	पूर्ण

	d = vfp_get_द्विगुन(dd);
	अगर (vfp_द्विगुन_packed_exponent(d) == 2047 && vfp_द्विगुन_packed_mantissa(d)) अणु
		ret |= FPSCR_C | FPSCR_V;
		अगर (संकेत_on_qnan || !(vfp_द्विगुन_packed_mantissa(d) & (1ULL << (VFP_DOUBLE_MANTISSA_BITS - 1))))
			/*
			 * Signalling NaN, or संकेतling on quiet NaN
			 */
			ret |= FPSCR_IOC;
	पूर्ण

	अगर (ret == 0) अणु
		अगर (d == m || vfp_द्विगुन_packed_असल(d | m) == 0) अणु
			/*
			 * equal
			 */
			ret |= FPSCR_Z | FPSCR_C;
		पूर्ण अन्यथा अगर (vfp_द्विगुन_packed_sign(d ^ m)) अणु
			/*
			 * dअगरferent signs
			 */
			अगर (vfp_द्विगुन_packed_sign(d))
				/*
				 * d is negative, so d < m
				 */
				ret |= FPSCR_N;
			अन्यथा
				/*
				 * d is positive, so d > m
				 */
				ret |= FPSCR_C;
		पूर्ण अन्यथा अगर ((vfp_द्विगुन_packed_sign(d) != 0) ^ (d < m)) अणु
			/*
			 * d < m
			 */
			ret |= FPSCR_N;
		पूर्ण अन्यथा अगर ((vfp_द्विगुन_packed_sign(d) != 0) ^ (d > m)) अणु
			/*
			 * d > m
			 */
			ret |= FPSCR_C;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 vfp_द्विगुन_fcmp(पूर्णांक dd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	वापस vfp_compare(dd, 0, dm, fpscr);
पूर्ण

अटल u32 vfp_द्विगुन_fcmpe(पूर्णांक dd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	वापस vfp_compare(dd, 1, dm, fpscr);
पूर्ण

अटल u32 vfp_द्विगुन_fcmpz(पूर्णांक dd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	वापस vfp_compare(dd, 0, VFP_REG_ZERO, fpscr);
पूर्ण

अटल u32 vfp_द्विगुन_fcmpez(पूर्णांक dd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	वापस vfp_compare(dd, 1, VFP_REG_ZERO, fpscr);
पूर्ण

अटल u32 vfp_द्विगुन_fcvts(पूर्णांक sd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	काष्ठा vfp_द्विगुन vdm;
	काष्ठा vfp_single vsd;
	पूर्णांक पंचांग;
	u32 exceptions = 0;

	vfp_द्विगुन_unpack(&vdm, vfp_get_द्विगुन(dm));

	पंचांग = vfp_द्विगुन_type(&vdm);

	/*
	 * If we have a संकेतling NaN, संकेत invalid operation.
	 */
	अगर (पंचांग == VFP_Sन_अंक)
		exceptions = FPSCR_IOC;

	अगर (पंचांग & VFP_DENORMAL)
		vfp_द्विगुन_normalise_denormal(&vdm);

	vsd.sign = vdm.sign;
	vsd.signअगरicand = vfp_hi64to32jamming(vdm.signअगरicand);

	/*
	 * If we have an infinity or a NaN, the exponent must be 255
	 */
	अगर (पंचांग & (VFP_अनन्त|VFP_न_अंक)) अणु
		vsd.exponent = 255;
		अगर (पंचांग == VFP_Qन_अंक)
			vsd.signअगरicand |= VFP_SINGLE_SIGNIFICAND_Qन_अंक;
		जाओ pack_nan;
	पूर्ण अन्यथा अगर (पंचांग & VFP_ZERO)
		vsd.exponent = 0;
	अन्यथा
		vsd.exponent = vdm.exponent - (1023 - 127);

	वापस vfp_single_normaliseround(sd, &vsd, fpscr, exceptions, "fcvts");

 pack_nan:
	vfp_put_भग्न(vfp_single_pack(&vsd), sd);
	वापस exceptions;
पूर्ण

अटल u32 vfp_द्विगुन_fuito(पूर्णांक dd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	काष्ठा vfp_द्विगुन vdm;
	u32 m = vfp_get_भग्न(dm);

	vdm.sign = 0;
	vdm.exponent = 1023 + 63 - 1;
	vdm.signअगरicand = (u64)m;

	वापस vfp_द्विगुन_normaliseround(dd, &vdm, fpscr, 0, "fuito");
पूर्ण

अटल u32 vfp_द्विगुन_fsito(पूर्णांक dd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	काष्ठा vfp_द्विगुन vdm;
	u32 m = vfp_get_भग्न(dm);

	vdm.sign = (m & 0x80000000) >> 16;
	vdm.exponent = 1023 + 63 - 1;
	vdm.signअगरicand = vdm.sign ? -m : m;

	वापस vfp_द्विगुन_normaliseround(dd, &vdm, fpscr, 0, "fsito");
पूर्ण

अटल u32 vfp_द्विगुन_ftoui(पूर्णांक sd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	काष्ठा vfp_द्विगुन vdm;
	u32 d, exceptions = 0;
	पूर्णांक rmode = fpscr & FPSCR_RMODE_MASK;
	पूर्णांक पंचांग;

	vfp_द्विगुन_unpack(&vdm, vfp_get_द्विगुन(dm));

	/*
	 * Do we have a denormalised number?
	 */
	पंचांग = vfp_द्विगुन_type(&vdm);
	अगर (पंचांग & VFP_DENORMAL)
		exceptions |= FPSCR_IDC;

	अगर (पंचांग & VFP_न_अंक)
		vdm.sign = 0;

	अगर (vdm.exponent >= 1023 + 32) अणु
		d = vdm.sign ? 0 : 0xffffffff;
		exceptions = FPSCR_IOC;
	पूर्ण अन्यथा अगर (vdm.exponent >= 1023 - 1) अणु
		पूर्णांक shअगरt = 1023 + 63 - vdm.exponent;
		u64 rem, incr = 0;

		/*
		 * 2^0 <= m < 2^32-2^8
		 */
		d = (vdm.signअगरicand << 1) >> shअगरt;
		rem = vdm.signअगरicand << (65 - shअगरt);

		अगर (rmode == FPSCR_ROUND_NEAREST) अणु
			incr = 0x8000000000000000ULL;
			अगर ((d & 1) == 0)
				incr -= 1;
		पूर्ण अन्यथा अगर (rmode == FPSCR_ROUND_TOZERO) अणु
			incr = 0;
		पूर्ण अन्यथा अगर ((rmode == FPSCR_ROUND_PLUSINF) ^ (vdm.sign != 0)) अणु
			incr = ~0ULL;
		पूर्ण

		अगर ((rem + incr) < rem) अणु
			अगर (d < 0xffffffff)
				d += 1;
			अन्यथा
				exceptions |= FPSCR_IOC;
		पूर्ण

		अगर (d && vdm.sign) अणु
			d = 0;
			exceptions |= FPSCR_IOC;
		पूर्ण अन्यथा अगर (rem)
			exceptions |= FPSCR_IXC;
	पूर्ण अन्यथा अणु
		d = 0;
		अगर (vdm.exponent | vdm.signअगरicand) अणु
			exceptions |= FPSCR_IXC;
			अगर (rmode == FPSCR_ROUND_PLUSINF && vdm.sign == 0)
				d = 1;
			अन्यथा अगर (rmode == FPSCR_ROUND_MINUSINF && vdm.sign) अणु
				d = 0;
				exceptions |= FPSCR_IOC;
			पूर्ण
		पूर्ण
	पूर्ण

	pr_debug("VFP: ftoui: d(s%d)=%08x exceptions=%08x\n", sd, d, exceptions);

	vfp_put_भग्न(d, sd);

	वापस exceptions;
पूर्ण

अटल u32 vfp_द्विगुन_ftouiz(पूर्णांक sd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	वापस vfp_द्विगुन_ftoui(sd, unused, dm, FPSCR_ROUND_TOZERO);
पूर्ण

अटल u32 vfp_द्विगुन_ftosi(पूर्णांक sd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	काष्ठा vfp_द्विगुन vdm;
	u32 d, exceptions = 0;
	पूर्णांक rmode = fpscr & FPSCR_RMODE_MASK;
	पूर्णांक पंचांग;

	vfp_द्विगुन_unpack(&vdm, vfp_get_द्विगुन(dm));
	vfp_द्विगुन_dump("VDM", &vdm);

	/*
	 * Do we have denormalised number?
	 */
	पंचांग = vfp_द्विगुन_type(&vdm);
	अगर (पंचांग & VFP_DENORMAL)
		exceptions |= FPSCR_IDC;

	अगर (पंचांग & VFP_न_अंक) अणु
		d = 0;
		exceptions |= FPSCR_IOC;
	पूर्ण अन्यथा अगर (vdm.exponent >= 1023 + 32) अणु
		d = 0x7fffffff;
		अगर (vdm.sign)
			d = ~d;
		exceptions |= FPSCR_IOC;
	पूर्ण अन्यथा अगर (vdm.exponent >= 1023 - 1) अणु
		पूर्णांक shअगरt = 1023 + 63 - vdm.exponent;	/* 58 */
		u64 rem, incr = 0;

		d = (vdm.signअगरicand << 1) >> shअगरt;
		rem = vdm.signअगरicand << (65 - shअगरt);

		अगर (rmode == FPSCR_ROUND_NEAREST) अणु
			incr = 0x8000000000000000ULL;
			अगर ((d & 1) == 0)
				incr -= 1;
		पूर्ण अन्यथा अगर (rmode == FPSCR_ROUND_TOZERO) अणु
			incr = 0;
		पूर्ण अन्यथा अगर ((rmode == FPSCR_ROUND_PLUSINF) ^ (vdm.sign != 0)) अणु
			incr = ~0ULL;
		पूर्ण

		अगर ((rem + incr) < rem && d < 0xffffffff)
			d += 1;
		अगर (d > 0x7fffffff + (vdm.sign != 0)) अणु
			d = 0x7fffffff + (vdm.sign != 0);
			exceptions |= FPSCR_IOC;
		पूर्ण अन्यथा अगर (rem)
			exceptions |= FPSCR_IXC;

		अगर (vdm.sign)
			d = -d;
	पूर्ण अन्यथा अणु
		d = 0;
		अगर (vdm.exponent | vdm.signअगरicand) अणु
			exceptions |= FPSCR_IXC;
			अगर (rmode == FPSCR_ROUND_PLUSINF && vdm.sign == 0)
				d = 1;
			अन्यथा अगर (rmode == FPSCR_ROUND_MINUSINF && vdm.sign)
				d = -1;
		पूर्ण
	पूर्ण

	pr_debug("VFP: ftosi: d(s%d)=%08x exceptions=%08x\n", sd, d, exceptions);

	vfp_put_भग्न((s32)d, sd);

	वापस exceptions;
पूर्ण

अटल u32 vfp_द्विगुन_ftosiz(पूर्णांक dd, पूर्णांक unused, पूर्णांक dm, u32 fpscr)
अणु
	वापस vfp_द्विगुन_ftosi(dd, unused, dm, FPSCR_ROUND_TOZERO);
पूर्ण


अटल काष्ठा op fops_ext[32] = अणु
	[FEXT_TO_IDX(FEXT_FCPY)]	= अणु vfp_द्विगुन_fcpy,   0 पूर्ण,
	[FEXT_TO_IDX(FEXT_FABS)]	= अणु vfp_द्विगुन_भ_असल,   0 पूर्ण,
	[FEXT_TO_IDX(FEXT_FNEG)]	= अणु vfp_द्विगुन_fneg,   0 पूर्ण,
	[FEXT_TO_IDX(FEXT_FSQRT)]	= अणु vfp_द्विगुन_fवर्ग_मूल,  0 पूर्ण,
	[FEXT_TO_IDX(FEXT_FCMP)]	= अणु vfp_द्विगुन_fcmp,   OP_SCALAR पूर्ण,
	[FEXT_TO_IDX(FEXT_FCMPE)]	= अणु vfp_द्विगुन_fcmpe,  OP_SCALAR पूर्ण,
	[FEXT_TO_IDX(FEXT_FCMPZ)]	= अणु vfp_द्विगुन_fcmpz,  OP_SCALAR पूर्ण,
	[FEXT_TO_IDX(FEXT_FCMPEZ)]	= अणु vfp_द्विगुन_fcmpez, OP_SCALAR पूर्ण,
	[FEXT_TO_IDX(FEXT_FCVT)]	= अणु vfp_द्विगुन_fcvts,  OP_SCALAR|OP_SD पूर्ण,
	[FEXT_TO_IDX(FEXT_FUITO)]	= अणु vfp_द्विगुन_fuito,  OP_SCALAR|OP_SM पूर्ण,
	[FEXT_TO_IDX(FEXT_FSITO)]	= अणु vfp_द्विगुन_fsito,  OP_SCALAR|OP_SM पूर्ण,
	[FEXT_TO_IDX(FEXT_FTOUI)]	= अणु vfp_द्विगुन_ftoui,  OP_SCALAR|OP_SD पूर्ण,
	[FEXT_TO_IDX(FEXT_FTOUIZ)]	= अणु vfp_द्विगुन_ftouiz, OP_SCALAR|OP_SD पूर्ण,
	[FEXT_TO_IDX(FEXT_FTOSI)]	= अणु vfp_द्विगुन_ftosi,  OP_SCALAR|OP_SD पूर्ण,
	[FEXT_TO_IDX(FEXT_FTOSIZ)]	= अणु vfp_द्विगुन_ftosiz, OP_SCALAR|OP_SD पूर्ण,
पूर्ण;




अटल u32
vfp_द्विगुन_fadd_nonnumber(काष्ठा vfp_द्विगुन *vdd, काष्ठा vfp_द्विगुन *vdn,
			  काष्ठा vfp_द्विगुन *vdm, u32 fpscr)
अणु
	काष्ठा vfp_द्विगुन *vdp;
	u32 exceptions = 0;
	पूर्णांक tn, पंचांग;

	tn = vfp_द्विगुन_type(vdn);
	पंचांग = vfp_द्विगुन_type(vdm);

	अगर (tn & पंचांग & VFP_अनन्त) अणु
		/*
		 * Two infinities.  Are they dअगरferent signs?
		 */
		अगर (vdn->sign ^ vdm->sign) अणु
			/*
			 * dअगरferent signs -> invalid
			 */
			exceptions = FPSCR_IOC;
			vdp = &vfp_द्विगुन_शेष_qnan;
		पूर्ण अन्यथा अणु
			/*
			 * same signs -> valid
			 */
			vdp = vdn;
		पूर्ण
	पूर्ण अन्यथा अगर (tn & VFP_अनन्त && पंचांग & VFP_NUMBER) अणु
		/*
		 * One infinity and one number -> infinity
		 */
		vdp = vdn;
	पूर्ण अन्यथा अणु
		/*
		 * 'n' is a NaN of some type
		 */
		वापस vfp_propagate_nan(vdd, vdn, vdm, fpscr);
	पूर्ण
	*vdd = *vdp;
	वापस exceptions;
पूर्ण

अटल u32
vfp_द्विगुन_add(काष्ठा vfp_द्विगुन *vdd, काष्ठा vfp_द्विगुन *vdn,
	       काष्ठा vfp_द्विगुन *vdm, u32 fpscr)
अणु
	u32 exp_dअगरf;
	u64 m_sig;

	अगर (vdn->signअगरicand & (1ULL << 63) ||
	    vdm->signअगरicand & (1ULL << 63)) अणु
		pr_info("VFP: bad FP values in %s\n", __func__);
		vfp_द्विगुन_dump("VDN", vdn);
		vfp_द्विगुन_dump("VDM", vdm);
	पूर्ण

	/*
	 * Ensure that 'n' is the largest magnitude number.  Note that
	 * अगर 'n' and 'm' have equal exponents, we करो not swap them.
	 * This ensures that NaN propagation works correctly.
	 */
	अगर (vdn->exponent < vdm->exponent) अणु
		काष्ठा vfp_द्विगुन *t = vdn;
		vdn = vdm;
		vdm = t;
	पूर्ण

	/*
	 * Is 'n' an infinity or a NaN?  Note that 'm' may be a number,
	 * infinity or a NaN here.
	 */
	अगर (vdn->exponent == 2047)
		वापस vfp_द्विगुन_fadd_nonnumber(vdd, vdn, vdm, fpscr);

	/*
	 * We have two proper numbers, where 'vdn' is the larger magnitude.
	 *
	 * Copy 'n' to 'd' beक्रमe करोing the arithmetic.
	 */
	*vdd = *vdn;

	/*
	 * Align 'm' with the result.
	 */
	exp_dअगरf = vdn->exponent - vdm->exponent;
	m_sig = vfp_shअगरtright64jamming(vdm->signअगरicand, exp_dअगरf);

	/*
	 * If the signs are dअगरferent, we are really subtracting.
	 */
	अगर (vdn->sign ^ vdm->sign) अणु
		m_sig = vdn->signअगरicand - m_sig;
		अगर ((s64)m_sig < 0) अणु
			vdd->sign = vfp_sign_negate(vdd->sign);
			m_sig = -m_sig;
		पूर्ण अन्यथा अगर (m_sig == 0) अणु
			vdd->sign = (fpscr & FPSCR_RMODE_MASK) ==
				      FPSCR_ROUND_MINUSINF ? 0x8000 : 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		m_sig += vdn->signअगरicand;
	पूर्ण
	vdd->signअगरicand = m_sig;

	वापस 0;
पूर्ण

अटल u32
vfp_द्विगुन_multiply(काष्ठा vfp_द्विगुन *vdd, काष्ठा vfp_द्विगुन *vdn,
		    काष्ठा vfp_द्विगुन *vdm, u32 fpscr)
अणु
	vfp_द्विगुन_dump("VDN", vdn);
	vfp_द्विगुन_dump("VDM", vdm);

	/*
	 * Ensure that 'n' is the largest magnitude number.  Note that
	 * अगर 'n' and 'm' have equal exponents, we करो not swap them.
	 * This ensures that NaN propagation works correctly.
	 */
	अगर (vdn->exponent < vdm->exponent) अणु
		काष्ठा vfp_द्विगुन *t = vdn;
		vdn = vdm;
		vdm = t;
		pr_debug("VFP: swapping M <-> N\n");
	पूर्ण

	vdd->sign = vdn->sign ^ vdm->sign;

	/*
	 * If 'n' is an infinity or NaN, handle it.  'm' may be anything.
	 */
	अगर (vdn->exponent == 2047) अणु
		अगर (vdn->signअगरicand || (vdm->exponent == 2047 && vdm->signअगरicand))
			वापस vfp_propagate_nan(vdd, vdn, vdm, fpscr);
		अगर ((vdm->exponent | vdm->signअगरicand) == 0) अणु
			*vdd = vfp_द्विगुन_शेष_qnan;
			वापस FPSCR_IOC;
		पूर्ण
		vdd->exponent = vdn->exponent;
		vdd->signअगरicand = 0;
		वापस 0;
	पूर्ण

	/*
	 * If 'm' is zero, the result is always zero.  In this हाल,
	 * 'n' may be zero or a number, but it doesn't matter which.
	 */
	अगर ((vdm->exponent | vdm->signअगरicand) == 0) अणु
		vdd->exponent = 0;
		vdd->signअगरicand = 0;
		वापस 0;
	पूर्ण

	/*
	 * We add 2 to the destination exponent क्रम the same reason
	 * as the addition हाल - though this समय we have +1 from
	 * each input opeअक्रम.
	 */
	vdd->exponent = vdn->exponent + vdm->exponent - 1023 + 2;
	vdd->signअगरicand = vfp_hi64multiply64(vdn->signअगरicand, vdm->signअगरicand);

	vfp_द्विगुन_dump("VDD", vdd);
	वापस 0;
पूर्ण

#घोषणा NEG_MULTIPLY	(1 << 0)
#घोषणा NEG_SUBTRACT	(1 << 1)

अटल u32
vfp_द्विगुन_multiply_accumulate(पूर्णांक dd, पूर्णांक dn, पूर्णांक dm, u32 fpscr, u32 negate, अक्षर *func)
अणु
	काष्ठा vfp_द्विगुन vdd, vdp, vdn, vdm;
	u32 exceptions;

	vfp_द्विगुन_unpack(&vdn, vfp_get_द्विगुन(dn));
	अगर (vdn.exponent == 0 && vdn.signअगरicand)
		vfp_द्विगुन_normalise_denormal(&vdn);

	vfp_द्विगुन_unpack(&vdm, vfp_get_द्विगुन(dm));
	अगर (vdm.exponent == 0 && vdm.signअगरicand)
		vfp_द्विगुन_normalise_denormal(&vdm);

	exceptions = vfp_द्विगुन_multiply(&vdp, &vdn, &vdm, fpscr);
	अगर (negate & NEG_MULTIPLY)
		vdp.sign = vfp_sign_negate(vdp.sign);

	vfp_द्विगुन_unpack(&vdn, vfp_get_द्विगुन(dd));
	अगर (vdn.exponent == 0 && vdn.signअगरicand)
		vfp_द्विगुन_normalise_denormal(&vdn);
	अगर (negate & NEG_SUBTRACT)
		vdn.sign = vfp_sign_negate(vdn.sign);

	exceptions |= vfp_द्विगुन_add(&vdd, &vdn, &vdp, fpscr);

	वापस vfp_द्विगुन_normaliseround(dd, &vdd, fpscr, exceptions, func);
पूर्ण

/*
 * Standard operations
 */

/*
 * sd = sd + (sn * sm)
 */
अटल u32 vfp_द्विगुन_fmac(पूर्णांक dd, पूर्णांक dn, पूर्णांक dm, u32 fpscr)
अणु
	वापस vfp_द्विगुन_multiply_accumulate(dd, dn, dm, fpscr, 0, "fmac");
पूर्ण

/*
 * sd = sd - (sn * sm)
 */
अटल u32 vfp_द्विगुन_fnmac(पूर्णांक dd, पूर्णांक dn, पूर्णांक dm, u32 fpscr)
अणु
	वापस vfp_द्विगुन_multiply_accumulate(dd, dn, dm, fpscr, NEG_MULTIPLY, "fnmac");
पूर्ण

/*
 * sd = -sd + (sn * sm)
 */
अटल u32 vfp_द्विगुन_fmsc(पूर्णांक dd, पूर्णांक dn, पूर्णांक dm, u32 fpscr)
अणु
	वापस vfp_द्विगुन_multiply_accumulate(dd, dn, dm, fpscr, NEG_SUBTRACT, "fmsc");
पूर्ण

/*
 * sd = -sd - (sn * sm)
 */
अटल u32 vfp_द्विगुन_fnmsc(पूर्णांक dd, पूर्णांक dn, पूर्णांक dm, u32 fpscr)
अणु
	वापस vfp_द्विगुन_multiply_accumulate(dd, dn, dm, fpscr, NEG_SUBTRACT | NEG_MULTIPLY, "fnmsc");
पूर्ण

/*
 * sd = sn * sm
 */
अटल u32 vfp_द्विगुन_fmul(पूर्णांक dd, पूर्णांक dn, पूर्णांक dm, u32 fpscr)
अणु
	काष्ठा vfp_द्विगुन vdd, vdn, vdm;
	u32 exceptions;

	vfp_द्विगुन_unpack(&vdn, vfp_get_द्विगुन(dn));
	अगर (vdn.exponent == 0 && vdn.signअगरicand)
		vfp_द्विगुन_normalise_denormal(&vdn);

	vfp_द्विगुन_unpack(&vdm, vfp_get_द्विगुन(dm));
	अगर (vdm.exponent == 0 && vdm.signअगरicand)
		vfp_द्विगुन_normalise_denormal(&vdm);

	exceptions = vfp_द्विगुन_multiply(&vdd, &vdn, &vdm, fpscr);
	वापस vfp_द्विगुन_normaliseround(dd, &vdd, fpscr, exceptions, "fmul");
पूर्ण

/*
 * sd = -(sn * sm)
 */
अटल u32 vfp_द्विगुन_fnmul(पूर्णांक dd, पूर्णांक dn, पूर्णांक dm, u32 fpscr)
अणु
	काष्ठा vfp_द्विगुन vdd, vdn, vdm;
	u32 exceptions;

	vfp_द्विगुन_unpack(&vdn, vfp_get_द्विगुन(dn));
	अगर (vdn.exponent == 0 && vdn.signअगरicand)
		vfp_द्विगुन_normalise_denormal(&vdn);

	vfp_द्विगुन_unpack(&vdm, vfp_get_द्विगुन(dm));
	अगर (vdm.exponent == 0 && vdm.signअगरicand)
		vfp_द्विगुन_normalise_denormal(&vdm);

	exceptions = vfp_द्विगुन_multiply(&vdd, &vdn, &vdm, fpscr);
	vdd.sign = vfp_sign_negate(vdd.sign);

	वापस vfp_द्विगुन_normaliseround(dd, &vdd, fpscr, exceptions, "fnmul");
पूर्ण

/*
 * sd = sn + sm
 */
अटल u32 vfp_द्विगुन_fadd(पूर्णांक dd, पूर्णांक dn, पूर्णांक dm, u32 fpscr)
अणु
	काष्ठा vfp_द्विगुन vdd, vdn, vdm;
	u32 exceptions;

	vfp_द्विगुन_unpack(&vdn, vfp_get_द्विगुन(dn));
	अगर (vdn.exponent == 0 && vdn.signअगरicand)
		vfp_द्विगुन_normalise_denormal(&vdn);

	vfp_द्विगुन_unpack(&vdm, vfp_get_द्विगुन(dm));
	अगर (vdm.exponent == 0 && vdm.signअगरicand)
		vfp_द्विगुन_normalise_denormal(&vdm);

	exceptions = vfp_द्विगुन_add(&vdd, &vdn, &vdm, fpscr);

	वापस vfp_द्विगुन_normaliseround(dd, &vdd, fpscr, exceptions, "fadd");
पूर्ण

/*
 * sd = sn - sm
 */
अटल u32 vfp_द्विगुन_fsub(पूर्णांक dd, पूर्णांक dn, पूर्णांक dm, u32 fpscr)
अणु
	काष्ठा vfp_द्विगुन vdd, vdn, vdm;
	u32 exceptions;

	vfp_द्विगुन_unpack(&vdn, vfp_get_द्विगुन(dn));
	अगर (vdn.exponent == 0 && vdn.signअगरicand)
		vfp_द्विगुन_normalise_denormal(&vdn);

	vfp_द्विगुन_unpack(&vdm, vfp_get_द्विगुन(dm));
	अगर (vdm.exponent == 0 && vdm.signअगरicand)
		vfp_द्विगुन_normalise_denormal(&vdm);

	/*
	 * Subtraction is like addition, but with a negated opeअक्रम.
	 */
	vdm.sign = vfp_sign_negate(vdm.sign);

	exceptions = vfp_द्विगुन_add(&vdd, &vdn, &vdm, fpscr);

	वापस vfp_द्विगुन_normaliseround(dd, &vdd, fpscr, exceptions, "fsub");
पूर्ण

/*
 * sd = sn / sm
 */
अटल u32 vfp_द्विगुन_fभाग(पूर्णांक dd, पूर्णांक dn, पूर्णांक dm, u32 fpscr)
अणु
	काष्ठा vfp_द्विगुन vdd, vdn, vdm;
	u32 exceptions = 0;
	पूर्णांक पंचांग, tn;

	vfp_द्विगुन_unpack(&vdn, vfp_get_द्विगुन(dn));
	vfp_द्विगुन_unpack(&vdm, vfp_get_द्विगुन(dm));

	vdd.sign = vdn.sign ^ vdm.sign;

	tn = vfp_द्विगुन_type(&vdn);
	पंचांग = vfp_द्विगुन_type(&vdm);

	/*
	 * Is n a न_अंक?
	 */
	अगर (tn & VFP_न_अंक)
		जाओ vdn_nan;

	/*
	 * Is m a न_अंक?
	 */
	अगर (पंचांग & VFP_न_अंक)
		जाओ vdm_nan;

	/*
	 * If n and m are infinity, the result is invalid
	 * If n and m are zero, the result is invalid
	 */
	अगर (पंचांग & tn & (VFP_अनन्त|VFP_ZERO))
		जाओ invalid;

	/*
	 * If n is infinity, the result is infinity
	 */
	अगर (tn & VFP_अनन्त)
		जाओ infinity;

	/*
	 * If m is zero, उठाओ भाग0 exceptions
	 */
	अगर (पंचांग & VFP_ZERO)
		जाओ भागzero;

	/*
	 * If m is infinity, or n is zero, the result is zero
	 */
	अगर (पंचांग & VFP_अनन्त || tn & VFP_ZERO)
		जाओ zero;

	अगर (tn & VFP_DENORMAL)
		vfp_द्विगुन_normalise_denormal(&vdn);
	अगर (पंचांग & VFP_DENORMAL)
		vfp_द्विगुन_normalise_denormal(&vdm);

	/*
	 * Ok, we have two numbers, we can perक्रमm भागision.
	 */
	vdd.exponent = vdn.exponent - vdm.exponent + 1023 - 1;
	vdm.signअगरicand <<= 1;
	अगर (vdm.signअगरicand <= (2 * vdn.signअगरicand)) अणु
		vdn.signअगरicand >>= 1;
		vdd.exponent++;
	पूर्ण
	vdd.signअगरicand = vfp_estimate_भाग128to64(vdn.signअगरicand, 0, vdm.signअगरicand);
	अगर ((vdd.signअगरicand & 0x1ff) <= 2) अणु
		u64 termh, terml, remh, reml;
		mul64to128(&termh, &terml, vdm.signअगरicand, vdd.signअगरicand);
		sub128(&remh, &reml, vdn.signअगरicand, 0, termh, terml);
		जबतक ((s64)remh < 0) अणु
			vdd.signअगरicand -= 1;
			add128(&remh, &reml, remh, reml, 0, vdm.signअगरicand);
		पूर्ण
		vdd.signअगरicand |= (reml != 0);
	पूर्ण
	वापस vfp_द्विगुन_normaliseround(dd, &vdd, fpscr, 0, "fdiv");

 vdn_nan:
	exceptions = vfp_propagate_nan(&vdd, &vdn, &vdm, fpscr);
 pack:
	vfp_put_द्विगुन(vfp_द्विगुन_pack(&vdd), dd);
	वापस exceptions;

 vdm_nan:
	exceptions = vfp_propagate_nan(&vdd, &vdm, &vdn, fpscr);
	जाओ pack;

 zero:
	vdd.exponent = 0;
	vdd.signअगरicand = 0;
	जाओ pack;

 भागzero:
	exceptions = FPSCR_DZC;
 infinity:
	vdd.exponent = 2047;
	vdd.signअगरicand = 0;
	जाओ pack;

 invalid:
	vfp_put_द्विगुन(vfp_द्विगुन_pack(&vfp_द्विगुन_शेष_qnan), dd);
	वापस FPSCR_IOC;
पूर्ण

अटल काष्ठा op fops[16] = अणु
	[FOP_TO_IDX(FOP_FMAC)]	= अणु vfp_द्विगुन_fmac,  0 पूर्ण,
	[FOP_TO_IDX(FOP_FNMAC)]	= अणु vfp_द्विगुन_fnmac, 0 पूर्ण,
	[FOP_TO_IDX(FOP_FMSC)]	= अणु vfp_द्विगुन_fmsc,  0 पूर्ण,
	[FOP_TO_IDX(FOP_FNMSC)]	= अणु vfp_द्विगुन_fnmsc, 0 पूर्ण,
	[FOP_TO_IDX(FOP_FMUL)]	= अणु vfp_द्विगुन_fmul,  0 पूर्ण,
	[FOP_TO_IDX(FOP_FNMUL)]	= अणु vfp_द्विगुन_fnmul, 0 पूर्ण,
	[FOP_TO_IDX(FOP_FADD)]	= अणु vfp_द्विगुन_fadd,  0 पूर्ण,
	[FOP_TO_IDX(FOP_FSUB)]	= अणु vfp_द्विगुन_fsub,  0 पूर्ण,
	[FOP_TO_IDX(FOP_FDIV)]	= अणु vfp_द्विगुन_fभाग,  0 पूर्ण,
पूर्ण;

#घोषणा FREG_BANK(x)	((x) & 0x0c)
#घोषणा FREG_IDX(x)	((x) & 3)

u32 vfp_द्विगुन_cpकरो(u32 inst, u32 fpscr)
अणु
	u32 op = inst & FOP_MASK;
	u32 exceptions = 0;
	अचिन्हित पूर्णांक dest;
	अचिन्हित पूर्णांक dn = vfp_get_dn(inst);
	अचिन्हित पूर्णांक dm;
	अचिन्हित पूर्णांक vecitr, veclen, vecstride;
	काष्ठा op *fop;

	vecstride = (1 + ((fpscr & FPSCR_STRIDE_MASK) == FPSCR_STRIDE_MASK));

	fop = (op == FOP_EXT) ? &fops_ext[FEXT_TO_IDX(inst)] : &fops[FOP_TO_IDX(op)];

	/*
	 * fcvtds takes an sN रेजिस्टर number as destination, not dN.
	 * It also always operates on scalars.
	 */
	अगर (fop->flags & OP_SD)
		dest = vfp_get_sd(inst);
	अन्यथा
		dest = vfp_get_dd(inst);

	/*
	 * f[us]ito takes a sN opeअक्रम, not a dN opeअक्रम.
	 */
	अगर (fop->flags & OP_SM)
		dm = vfp_get_sm(inst);
	अन्यथा
		dm = vfp_get_dm(inst);

	/*
	 * If destination bank is zero, vector length is always '1'.
	 * ARM DDI0100F C5.1.3, C5.3.2.
	 */
	अगर ((fop->flags & OP_SCALAR) || (FREG_BANK(dest) == 0))
		veclen = 0;
	अन्यथा
		veclen = fpscr & FPSCR_LENGTH_MASK;

	pr_debug("VFP: vecstride=%u veclen=%u\n", vecstride,
		 (veclen >> FPSCR_LENGTH_BIT) + 1);

	अगर (!fop->fn)
		जाओ invalid;

	क्रम (vecitr = 0; vecitr <= veclen; vecitr += 1 << FPSCR_LENGTH_BIT) अणु
		u32 except;
		अक्षर type;

		type = fop->flags & OP_SD ? 's' : 'd';
		अगर (op == FOP_EXT)
			pr_debug("VFP: itr%d (%c%u) = op[%u] (d%u)\n",
				 vecitr >> FPSCR_LENGTH_BIT,
				 type, dest, dn, dm);
		अन्यथा
			pr_debug("VFP: itr%d (%c%u) = (d%u) op[%u] (d%u)\n",
				 vecitr >> FPSCR_LENGTH_BIT,
				 type, dest, dn, FOP_TO_IDX(op), dm);

		except = fop->fn(dest, dn, dm, fpscr);
		pr_debug("VFP: itr%d: exceptions=%08x\n",
			 vecitr >> FPSCR_LENGTH_BIT, except);

		exceptions |= except;

		/*
		 * CHECK: It appears to be undefined whether we stop when
		 * we encounter an exception.  We जारी.
		 */
		dest = FREG_BANK(dest) + ((FREG_IDX(dest) + vecstride) & 3);
		dn = FREG_BANK(dn) + ((FREG_IDX(dn) + vecstride) & 3);
		अगर (FREG_BANK(dm) != 0)
			dm = FREG_BANK(dm) + ((FREG_IDX(dm) + vecstride) & 3);
	पूर्ण
	वापस exceptions;

 invalid:
	वापस ~0;
पूर्ण
