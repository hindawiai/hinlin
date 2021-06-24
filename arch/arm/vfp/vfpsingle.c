<शैली गुरु>
/*
 *  linux/arch/arm/vfp/vfpsingle.c
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

अटल काष्ठा vfp_single vfp_single_शेष_qnan = अणु
	.exponent	= 255,
	.sign		= 0,
	.signअगरicand	= VFP_SINGLE_SIGNIFICAND_Qन_अंक,
पूर्ण;

अटल व्योम vfp_single_dump(स्थिर अक्षर *str, काष्ठा vfp_single *s)
अणु
	pr_debug("VFP: %s: sign=%d exponent=%d significand=%08x\n",
		 str, s->sign != 0, s->exponent, s->signअगरicand);
पूर्ण

अटल व्योम vfp_single_normalise_denormal(काष्ठा vfp_single *vs)
अणु
	पूर्णांक bits = 31 - fls(vs->signअगरicand);

	vfp_single_dump("normalise_denormal: in", vs);

	अगर (bits) अणु
		vs->exponent -= bits - 1;
		vs->signअगरicand <<= bits;
	पूर्ण

	vfp_single_dump("normalise_denormal: out", vs);
पूर्ण

#अगर_अघोषित DEBUG
#घोषणा vfp_single_normaliseround(sd,vsd,fpscr,except,func) __vfp_single_normaliseround(sd,vsd,fpscr,except)
u32 __vfp_single_normaliseround(पूर्णांक sd, काष्ठा vfp_single *vs, u32 fpscr, u32 exceptions)
#अन्यथा
u32 vfp_single_normaliseround(पूर्णांक sd, काष्ठा vfp_single *vs, u32 fpscr, u32 exceptions, स्थिर अक्षर *func)
#पूर्ण_अगर
अणु
	u32 signअगरicand, incr, rmode;
	पूर्णांक exponent, shअगरt, underflow;

	vfp_single_dump("pack: in", vs);

	/*
	 * Infinities and NaNs are a special हाल.
	 */
	अगर (vs->exponent == 255 && (vs->signअगरicand == 0 || exceptions))
		जाओ pack;

	/*
	 * Special-हाल zero.
	 */
	अगर (vs->signअगरicand == 0) अणु
		vs->exponent = 0;
		जाओ pack;
	पूर्ण

	exponent = vs->exponent;
	signअगरicand = vs->signअगरicand;

	/*
	 * Normalise first.  Note that we shअगरt the signअगरicand up to
	 * bit 31, so we have VFP_SINGLE_LOW_BITS + 1 below the least
	 * signअगरicant bit.
	 */
	shअगरt = 32 - fls(signअगरicand);
	अगर (shअगरt < 32 && shअगरt) अणु
		exponent -= shअगरt;
		signअगरicand <<= shअगरt;
	पूर्ण

#अगर_घोषित DEBUG
	vs->exponent = exponent;
	vs->signअगरicand = signअगरicand;
	vfp_single_dump("pack: normalised", vs);
#पूर्ण_अगर

	/*
	 * Tiny number?
	 */
	underflow = exponent < 0;
	अगर (underflow) अणु
		signअगरicand = vfp_shअगरtright32jamming(signअगरicand, -exponent);
		exponent = 0;
#अगर_घोषित DEBUG
		vs->exponent = exponent;
		vs->signअगरicand = signअगरicand;
		vfp_single_dump("pack: tiny number", vs);
#पूर्ण_अगर
		अगर (!(signअगरicand & ((1 << (VFP_SINGLE_LOW_BITS + 1)) - 1)))
			underflow = 0;
	पूर्ण

	/*
	 * Select rounding increment.
	 */
	incr = 0;
	rmode = fpscr & FPSCR_RMODE_MASK;

	अगर (rmode == FPSCR_ROUND_NEAREST) अणु
		incr = 1 << VFP_SINGLE_LOW_BITS;
		अगर ((signअगरicand & (1 << (VFP_SINGLE_LOW_BITS + 1))) == 0)
			incr -= 1;
	पूर्ण अन्यथा अगर (rmode == FPSCR_ROUND_TOZERO) अणु
		incr = 0;
	पूर्ण अन्यथा अगर ((rmode == FPSCR_ROUND_PLUSINF) ^ (vs->sign != 0))
		incr = (1 << (VFP_SINGLE_LOW_BITS + 1)) - 1;

	pr_debug("VFP: rounding increment = 0x%08x\n", incr);

	/*
	 * Is our rounding going to overflow?
	 */
	अगर ((signअगरicand + incr) < signअगरicand) अणु
		exponent += 1;
		signअगरicand = (signअगरicand >> 1) | (signअगरicand & 1);
		incr >>= 1;
#अगर_घोषित DEBUG
		vs->exponent = exponent;
		vs->signअगरicand = signअगरicand;
		vfp_single_dump("pack: overflow", vs);
#पूर्ण_अगर
	पूर्ण

	/*
	 * If any of the low bits (which will be shअगरted out of the
	 * number) are non-zero, the result is inexact.
	 */
	अगर (signअगरicand & ((1 << (VFP_SINGLE_LOW_BITS + 1)) - 1))
		exceptions |= FPSCR_IXC;

	/*
	 * Do our rounding.
	 */
	signअगरicand += incr;

	/*
	 * Infinity?
	 */
	अगर (exponent >= 254) अणु
		exceptions |= FPSCR_OFC | FPSCR_IXC;
		अगर (incr == 0) अणु
			vs->exponent = 253;
			vs->signअगरicand = 0x7fffffff;
		पूर्ण अन्यथा अणु
			vs->exponent = 255;		/* infinity */
			vs->signअगरicand = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (signअगरicand >> (VFP_SINGLE_LOW_BITS + 1) == 0)
			exponent = 0;
		अगर (exponent || signअगरicand > 0x80000000)
			underflow = 0;
		अगर (underflow)
			exceptions |= FPSCR_UFC;
		vs->exponent = exponent;
		vs->signअगरicand = signअगरicand >> 1;
	पूर्ण

 pack:
	vfp_single_dump("pack: final", vs);
	अणु
		s32 d = vfp_single_pack(vs);
#अगर_घोषित DEBUG
		pr_debug("VFP: %s: d(s%d)=%08x exceptions=%08x\n", func,
			 sd, d, exceptions);
#पूर्ण_अगर
		vfp_put_भग्न(d, sd);
	पूर्ण

	वापस exceptions;
पूर्ण

/*
 * Propagate the NaN, setting exceptions अगर it is संकेतling.
 * 'n' is always a NaN.  'm' may be a number, NaN or infinity.
 */
अटल u32
vfp_propagate_nan(काष्ठा vfp_single *vsd, काष्ठा vfp_single *vsn,
		  काष्ठा vfp_single *vsm, u32 fpscr)
अणु
	काष्ठा vfp_single *nan;
	पूर्णांक tn, पंचांग = 0;

	tn = vfp_single_type(vsn);

	अगर (vsm)
		पंचांग = vfp_single_type(vsm);

	अगर (fpscr & FPSCR_DEFAULT_न_अंक)
		/*
		 * Default NaN mode - always वापसs a quiet NaN
		 */
		nan = &vfp_single_शेष_qnan;
	अन्यथा अणु
		/*
		 * Contemporary mode - select the first संकेतling
		 * न_अंक, or अगर neither are संकेतling, the first
		 * quiet न_अंक.
		 */
		अगर (tn == VFP_Sन_अंक || (पंचांग != VFP_Sन_अंक && tn == VFP_Qन_अंक))
			nan = vsn;
		अन्यथा
			nan = vsm;
		/*
		 * Make the NaN quiet.
		 */
		nan->signअगरicand |= VFP_SINGLE_SIGNIFICAND_Qन_अंक;
	पूर्ण

	*vsd = *nan;

	/*
	 * If one was a संकेतling न_अंक, उठाओ invalid operation.
	 */
	वापस tn == VFP_Sन_अंक || पंचांग == VFP_Sन_अंक ? FPSCR_IOC : VFP_न_अंक_FLAG;
पूर्ण


/*
 * Extended operations
 */
अटल u32 vfp_single_भ_असल(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	vfp_put_भग्न(vfp_single_packed_असल(m), sd);
	वापस 0;
पूर्ण

अटल u32 vfp_single_fcpy(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	vfp_put_भग्न(m, sd);
	वापस 0;
पूर्ण

अटल u32 vfp_single_fneg(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	vfp_put_भग्न(vfp_single_packed_negate(m), sd);
	वापस 0;
पूर्ण

अटल स्थिर u16 वर्ग_मूल_oddadjust[] = अणु
	0x0004, 0x0022, 0x005d, 0x00b1, 0x011d, 0x019f, 0x0236, 0x02e0,
	0x039c, 0x0468, 0x0545, 0x0631, 0x072b, 0x0832, 0x0946, 0x0a67
पूर्ण;

अटल स्थिर u16 वर्ग_मूल_evenadjust[] = अणु
	0x0a2d, 0x08af, 0x075a, 0x0629, 0x051a, 0x0429, 0x0356, 0x029e,
	0x0200, 0x0179, 0x0109, 0x00af, 0x0068, 0x0034, 0x0012, 0x0002
पूर्ण;

u32 vfp_estimate_वर्ग_मूल_signअगरicand(u32 exponent, u32 signअगरicand)
अणु
	पूर्णांक index;
	u32 z, a;

	अगर ((signअगरicand & 0xc0000000) != 0x40000000) अणु
		pr_warn("VFP: estimate_sqrt: invalid significand\n");
	पूर्ण

	a = signअगरicand << 1;
	index = (a >> 27) & 15;
	अगर (exponent & 1) अणु
		z = 0x4000 + (a >> 17) - वर्ग_मूल_oddadjust[index];
		z = ((a / z) << 14) + (z << 15);
		a >>= 1;
	पूर्ण अन्यथा अणु
		z = 0x8000 + (a >> 17) - वर्ग_मूल_evenadjust[index];
		z = a / z + z;
		z = (z >= 0x20000) ? 0xffff8000 : (z << 15);
		अगर (z <= a)
			वापस (s32)a >> 1;
	पूर्ण
	अणु
		u64 v = (u64)a << 31;
		करो_भाग(v, z);
		वापस v + (z >> 1);
	पूर्ण
पूर्ण

अटल u32 vfp_single_fवर्ग_मूल(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	काष्ठा vfp_single vsm, vsd;
	पूर्णांक ret, पंचांग;

	vfp_single_unpack(&vsm, m);
	पंचांग = vfp_single_type(&vsm);
	अगर (पंचांग & (VFP_न_अंक|VFP_अनन्त)) अणु
		काष्ठा vfp_single *vsp = &vsd;

		अगर (पंचांग & VFP_न_अंक)
			ret = vfp_propagate_nan(vsp, &vsm, शून्य, fpscr);
		अन्यथा अगर (vsm.sign == 0) अणु
 वर्ग_मूल_copy:
			vsp = &vsm;
			ret = 0;
		पूर्ण अन्यथा अणु
 वर्ग_मूल_invalid:
			vsp = &vfp_single_शेष_qnan;
			ret = FPSCR_IOC;
		पूर्ण
		vfp_put_भग्न(vfp_single_pack(vsp), sd);
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
		vfp_single_normalise_denormal(&vsm);

	/*
	 * वर्ग_मूल(<0) = invalid
	 */
	अगर (vsm.sign)
		जाओ वर्ग_मूल_invalid;

	vfp_single_dump("sqrt", &vsm);

	/*
	 * Estimate the square root.
	 */
	vsd.sign = 0;
	vsd.exponent = ((vsm.exponent - 127) >> 1) + 127;
	vsd.signअगरicand = vfp_estimate_वर्ग_मूल_signअगरicand(vsm.exponent, vsm.signअगरicand) + 2;

	vfp_single_dump("sqrt estimate", &vsd);

	/*
	 * And now adjust.
	 */
	अगर ((vsd.signअगरicand & VFP_SINGLE_LOW_BITS_MASK) <= 5) अणु
		अगर (vsd.signअगरicand < 2) अणु
			vsd.signअगरicand = 0xffffffff;
		पूर्ण अन्यथा अणु
			u64 term;
			s64 rem;
			vsm.signअगरicand <<= !(vsm.exponent & 1);
			term = (u64)vsd.signअगरicand * vsd.signअगरicand;
			rem = ((u64)vsm.signअगरicand << 32) - term;

			pr_debug("VFP: term=%016llx rem=%016llx\n", term, rem);

			जबतक (rem < 0) अणु
				vsd.signअगरicand -= 1;
				rem += ((u64)vsd.signअगरicand << 1) | 1;
			पूर्ण
			vsd.signअगरicand |= rem != 0;
		पूर्ण
	पूर्ण
	vsd.signअगरicand = vfp_shअगरtright32jamming(vsd.signअगरicand, 1);

	वापस vfp_single_normaliseround(sd, &vsd, fpscr, 0, "fsqrt");
पूर्ण

/*
 * Equal	:= ZC
 * Less than	:= N
 * Greater than	:= C
 * Unordered	:= CV
 */
अटल u32 vfp_compare(पूर्णांक sd, पूर्णांक संकेत_on_qnan, s32 m, u32 fpscr)
अणु
	s32 d;
	u32 ret = 0;

	d = vfp_get_भग्न(sd);
	अगर (vfp_single_packed_exponent(m) == 255 && vfp_single_packed_mantissa(m)) अणु
		ret |= FPSCR_C | FPSCR_V;
		अगर (संकेत_on_qnan || !(vfp_single_packed_mantissa(m) & (1 << (VFP_SINGLE_MANTISSA_BITS - 1))))
			/*
			 * Signalling NaN, or संकेतling on quiet NaN
			 */
			ret |= FPSCR_IOC;
	पूर्ण

	अगर (vfp_single_packed_exponent(d) == 255 && vfp_single_packed_mantissa(d)) अणु
		ret |= FPSCR_C | FPSCR_V;
		अगर (संकेत_on_qnan || !(vfp_single_packed_mantissa(d) & (1 << (VFP_SINGLE_MANTISSA_BITS - 1))))
			/*
			 * Signalling NaN, or संकेतling on quiet NaN
			 */
			ret |= FPSCR_IOC;
	पूर्ण

	अगर (ret == 0) अणु
		अगर (d == m || vfp_single_packed_असल(d | m) == 0) अणु
			/*
			 * equal
			 */
			ret |= FPSCR_Z | FPSCR_C;
		पूर्ण अन्यथा अगर (vfp_single_packed_sign(d ^ m)) अणु
			/*
			 * dअगरferent signs
			 */
			अगर (vfp_single_packed_sign(d))
				/*
				 * d is negative, so d < m
				 */
				ret |= FPSCR_N;
			अन्यथा
				/*
				 * d is positive, so d > m
				 */
				ret |= FPSCR_C;
		पूर्ण अन्यथा अगर ((vfp_single_packed_sign(d) != 0) ^ (d < m)) अणु
			/*
			 * d < m
			 */
			ret |= FPSCR_N;
		पूर्ण अन्यथा अगर ((vfp_single_packed_sign(d) != 0) ^ (d > m)) अणु
			/*
			 * d > m
			 */
			ret |= FPSCR_C;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल u32 vfp_single_fcmp(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	वापस vfp_compare(sd, 0, m, fpscr);
पूर्ण

अटल u32 vfp_single_fcmpe(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	वापस vfp_compare(sd, 1, m, fpscr);
पूर्ण

अटल u32 vfp_single_fcmpz(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	वापस vfp_compare(sd, 0, 0, fpscr);
पूर्ण

अटल u32 vfp_single_fcmpez(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	वापस vfp_compare(sd, 1, 0, fpscr);
पूर्ण

अटल u32 vfp_single_fcvtd(पूर्णांक dd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	काष्ठा vfp_single vsm;
	काष्ठा vfp_द्विगुन vdd;
	पूर्णांक पंचांग;
	u32 exceptions = 0;

	vfp_single_unpack(&vsm, m);

	पंचांग = vfp_single_type(&vsm);

	/*
	 * If we have a संकेतling NaN, संकेत invalid operation.
	 */
	अगर (पंचांग == VFP_Sन_अंक)
		exceptions = FPSCR_IOC;

	अगर (पंचांग & VFP_DENORMAL)
		vfp_single_normalise_denormal(&vsm);

	vdd.sign = vsm.sign;
	vdd.signअगरicand = (u64)vsm.signअगरicand << 32;

	/*
	 * If we have an infinity or NaN, the exponent must be 2047.
	 */
	अगर (पंचांग & (VFP_अनन्त|VFP_न_अंक)) अणु
		vdd.exponent = 2047;
		अगर (पंचांग == VFP_Qन_अंक)
			vdd.signअगरicand |= VFP_DOUBLE_SIGNIFICAND_Qन_अंक;
		जाओ pack_nan;
	पूर्ण अन्यथा अगर (पंचांग & VFP_ZERO)
		vdd.exponent = 0;
	अन्यथा
		vdd.exponent = vsm.exponent + (1023 - 127);

	वापस vfp_द्विगुन_normaliseround(dd, &vdd, fpscr, exceptions, "fcvtd");

 pack_nan:
	vfp_put_द्विगुन(vfp_द्विगुन_pack(&vdd), dd);
	वापस exceptions;
पूर्ण

अटल u32 vfp_single_fuito(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	काष्ठा vfp_single vs;

	vs.sign = 0;
	vs.exponent = 127 + 31 - 1;
	vs.signअगरicand = (u32)m;

	वापस vfp_single_normaliseround(sd, &vs, fpscr, 0, "fuito");
पूर्ण

अटल u32 vfp_single_fsito(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	काष्ठा vfp_single vs;

	vs.sign = (m & 0x80000000) >> 16;
	vs.exponent = 127 + 31 - 1;
	vs.signअगरicand = vs.sign ? -m : m;

	वापस vfp_single_normaliseround(sd, &vs, fpscr, 0, "fsito");
पूर्ण

अटल u32 vfp_single_ftoui(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	काष्ठा vfp_single vsm;
	u32 d, exceptions = 0;
	पूर्णांक rmode = fpscr & FPSCR_RMODE_MASK;
	पूर्णांक पंचांग;

	vfp_single_unpack(&vsm, m);
	vfp_single_dump("VSM", &vsm);

	/*
	 * Do we have a denormalised number?
	 */
	पंचांग = vfp_single_type(&vsm);
	अगर (पंचांग & VFP_DENORMAL)
		exceptions |= FPSCR_IDC;

	अगर (पंचांग & VFP_न_अंक)
		vsm.sign = 0;

	अगर (vsm.exponent >= 127 + 32) अणु
		d = vsm.sign ? 0 : 0xffffffff;
		exceptions = FPSCR_IOC;
	पूर्ण अन्यथा अगर (vsm.exponent >= 127 - 1) अणु
		पूर्णांक shअगरt = 127 + 31 - vsm.exponent;
		u32 rem, incr = 0;

		/*
		 * 2^0 <= m < 2^32-2^8
		 */
		d = (vsm.signअगरicand << 1) >> shअगरt;
		rem = vsm.signअगरicand << (33 - shअगरt);

		अगर (rmode == FPSCR_ROUND_NEAREST) अणु
			incr = 0x80000000;
			अगर ((d & 1) == 0)
				incr -= 1;
		पूर्ण अन्यथा अगर (rmode == FPSCR_ROUND_TOZERO) अणु
			incr = 0;
		पूर्ण अन्यथा अगर ((rmode == FPSCR_ROUND_PLUSINF) ^ (vsm.sign != 0)) अणु
			incr = ~0;
		पूर्ण

		अगर ((rem + incr) < rem) अणु
			अगर (d < 0xffffffff)
				d += 1;
			अन्यथा
				exceptions |= FPSCR_IOC;
		पूर्ण

		अगर (d && vsm.sign) अणु
			d = 0;
			exceptions |= FPSCR_IOC;
		पूर्ण अन्यथा अगर (rem)
			exceptions |= FPSCR_IXC;
	पूर्ण अन्यथा अणु
		d = 0;
		अगर (vsm.exponent | vsm.signअगरicand) अणु
			exceptions |= FPSCR_IXC;
			अगर (rmode == FPSCR_ROUND_PLUSINF && vsm.sign == 0)
				d = 1;
			अन्यथा अगर (rmode == FPSCR_ROUND_MINUSINF && vsm.sign) अणु
				d = 0;
				exceptions |= FPSCR_IOC;
			पूर्ण
		पूर्ण
	पूर्ण

	pr_debug("VFP: ftoui: d(s%d)=%08x exceptions=%08x\n", sd, d, exceptions);

	vfp_put_भग्न(d, sd);

	वापस exceptions;
पूर्ण

अटल u32 vfp_single_ftouiz(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	वापस vfp_single_ftoui(sd, unused, m, FPSCR_ROUND_TOZERO);
पूर्ण

अटल u32 vfp_single_ftosi(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	काष्ठा vfp_single vsm;
	u32 d, exceptions = 0;
	पूर्णांक rmode = fpscr & FPSCR_RMODE_MASK;
	पूर्णांक पंचांग;

	vfp_single_unpack(&vsm, m);
	vfp_single_dump("VSM", &vsm);

	/*
	 * Do we have a denormalised number?
	 */
	पंचांग = vfp_single_type(&vsm);
	अगर (vfp_single_type(&vsm) & VFP_DENORMAL)
		exceptions |= FPSCR_IDC;

	अगर (पंचांग & VFP_न_अंक) अणु
		d = 0;
		exceptions |= FPSCR_IOC;
	पूर्ण अन्यथा अगर (vsm.exponent >= 127 + 32) अणु
		/*
		 * m >= 2^31-2^7: invalid
		 */
		d = 0x7fffffff;
		अगर (vsm.sign)
			d = ~d;
		exceptions |= FPSCR_IOC;
	पूर्ण अन्यथा अगर (vsm.exponent >= 127 - 1) अणु
		पूर्णांक shअगरt = 127 + 31 - vsm.exponent;
		u32 rem, incr = 0;

		/* 2^0 <= m <= 2^31-2^7 */
		d = (vsm.signअगरicand << 1) >> shअगरt;
		rem = vsm.signअगरicand << (33 - shअगरt);

		अगर (rmode == FPSCR_ROUND_NEAREST) अणु
			incr = 0x80000000;
			अगर ((d & 1) == 0)
				incr -= 1;
		पूर्ण अन्यथा अगर (rmode == FPSCR_ROUND_TOZERO) अणु
			incr = 0;
		पूर्ण अन्यथा अगर ((rmode == FPSCR_ROUND_PLUSINF) ^ (vsm.sign != 0)) अणु
			incr = ~0;
		पूर्ण

		अगर ((rem + incr) < rem && d < 0xffffffff)
			d += 1;
		अगर (d > 0x7fffffff + (vsm.sign != 0)) अणु
			d = 0x7fffffff + (vsm.sign != 0);
			exceptions |= FPSCR_IOC;
		पूर्ण अन्यथा अगर (rem)
			exceptions |= FPSCR_IXC;

		अगर (vsm.sign)
			d = -d;
	पूर्ण अन्यथा अणु
		d = 0;
		अगर (vsm.exponent | vsm.signअगरicand) अणु
			exceptions |= FPSCR_IXC;
			अगर (rmode == FPSCR_ROUND_PLUSINF && vsm.sign == 0)
				d = 1;
			अन्यथा अगर (rmode == FPSCR_ROUND_MINUSINF && vsm.sign)
				d = -1;
		पूर्ण
	पूर्ण

	pr_debug("VFP: ftosi: d(s%d)=%08x exceptions=%08x\n", sd, d, exceptions);

	vfp_put_भग्न((s32)d, sd);

	वापस exceptions;
पूर्ण

अटल u32 vfp_single_ftosiz(पूर्णांक sd, पूर्णांक unused, s32 m, u32 fpscr)
अणु
	वापस vfp_single_ftosi(sd, unused, m, FPSCR_ROUND_TOZERO);
पूर्ण

अटल काष्ठा op fops_ext[32] = अणु
	[FEXT_TO_IDX(FEXT_FCPY)]	= अणु vfp_single_fcpy,   0 पूर्ण,
	[FEXT_TO_IDX(FEXT_FABS)]	= अणु vfp_single_भ_असल,   0 पूर्ण,
	[FEXT_TO_IDX(FEXT_FNEG)]	= अणु vfp_single_fneg,   0 पूर्ण,
	[FEXT_TO_IDX(FEXT_FSQRT)]	= अणु vfp_single_fवर्ग_मूल,  0 पूर्ण,
	[FEXT_TO_IDX(FEXT_FCMP)]	= अणु vfp_single_fcmp,   OP_SCALAR पूर्ण,
	[FEXT_TO_IDX(FEXT_FCMPE)]	= अणु vfp_single_fcmpe,  OP_SCALAR पूर्ण,
	[FEXT_TO_IDX(FEXT_FCMPZ)]	= अणु vfp_single_fcmpz,  OP_SCALAR पूर्ण,
	[FEXT_TO_IDX(FEXT_FCMPEZ)]	= अणु vfp_single_fcmpez, OP_SCALAR पूर्ण,
	[FEXT_TO_IDX(FEXT_FCVT)]	= अणु vfp_single_fcvtd,  OP_SCALAR|OP_DD पूर्ण,
	[FEXT_TO_IDX(FEXT_FUITO)]	= अणु vfp_single_fuito,  OP_SCALAR पूर्ण,
	[FEXT_TO_IDX(FEXT_FSITO)]	= अणु vfp_single_fsito,  OP_SCALAR पूर्ण,
	[FEXT_TO_IDX(FEXT_FTOUI)]	= अणु vfp_single_ftoui,  OP_SCALAR पूर्ण,
	[FEXT_TO_IDX(FEXT_FTOUIZ)]	= अणु vfp_single_ftouiz, OP_SCALAR पूर्ण,
	[FEXT_TO_IDX(FEXT_FTOSI)]	= अणु vfp_single_ftosi,  OP_SCALAR पूर्ण,
	[FEXT_TO_IDX(FEXT_FTOSIZ)]	= अणु vfp_single_ftosiz, OP_SCALAR पूर्ण,
पूर्ण;





अटल u32
vfp_single_fadd_nonnumber(काष्ठा vfp_single *vsd, काष्ठा vfp_single *vsn,
			  काष्ठा vfp_single *vsm, u32 fpscr)
अणु
	काष्ठा vfp_single *vsp;
	u32 exceptions = 0;
	पूर्णांक tn, पंचांग;

	tn = vfp_single_type(vsn);
	पंचांग = vfp_single_type(vsm);

	अगर (tn & पंचांग & VFP_अनन्त) अणु
		/*
		 * Two infinities.  Are they dअगरferent signs?
		 */
		अगर (vsn->sign ^ vsm->sign) अणु
			/*
			 * dअगरferent signs -> invalid
			 */
			exceptions = FPSCR_IOC;
			vsp = &vfp_single_शेष_qnan;
		पूर्ण अन्यथा अणु
			/*
			 * same signs -> valid
			 */
			vsp = vsn;
		पूर्ण
	पूर्ण अन्यथा अगर (tn & VFP_अनन्त && पंचांग & VFP_NUMBER) अणु
		/*
		 * One infinity and one number -> infinity
		 */
		vsp = vsn;
	पूर्ण अन्यथा अणु
		/*
		 * 'n' is a NaN of some type
		 */
		वापस vfp_propagate_nan(vsd, vsn, vsm, fpscr);
	पूर्ण
	*vsd = *vsp;
	वापस exceptions;
पूर्ण

अटल u32
vfp_single_add(काष्ठा vfp_single *vsd, काष्ठा vfp_single *vsn,
	       काष्ठा vfp_single *vsm, u32 fpscr)
अणु
	u32 exp_dअगरf, m_sig;

	अगर (vsn->signअगरicand & 0x80000000 ||
	    vsm->signअगरicand & 0x80000000) अणु
		pr_info("VFP: bad FP values in %s\n", __func__);
		vfp_single_dump("VSN", vsn);
		vfp_single_dump("VSM", vsm);
	पूर्ण

	/*
	 * Ensure that 'n' is the largest magnitude number.  Note that
	 * अगर 'n' and 'm' have equal exponents, we करो not swap them.
	 * This ensures that NaN propagation works correctly.
	 */
	अगर (vsn->exponent < vsm->exponent) अणु
		काष्ठा vfp_single *t = vsn;
		vsn = vsm;
		vsm = t;
	पूर्ण

	/*
	 * Is 'n' an infinity or a NaN?  Note that 'm' may be a number,
	 * infinity or a NaN here.
	 */
	अगर (vsn->exponent == 255)
		वापस vfp_single_fadd_nonnumber(vsd, vsn, vsm, fpscr);

	/*
	 * We have two proper numbers, where 'vsn' is the larger magnitude.
	 *
	 * Copy 'n' to 'd' beक्रमe करोing the arithmetic.
	 */
	*vsd = *vsn;

	/*
	 * Align both numbers.
	 */
	exp_dअगरf = vsn->exponent - vsm->exponent;
	m_sig = vfp_shअगरtright32jamming(vsm->signअगरicand, exp_dअगरf);

	/*
	 * If the signs are dअगरferent, we are really subtracting.
	 */
	अगर (vsn->sign ^ vsm->sign) अणु
		m_sig = vsn->signअगरicand - m_sig;
		अगर ((s32)m_sig < 0) अणु
			vsd->sign = vfp_sign_negate(vsd->sign);
			m_sig = -m_sig;
		पूर्ण अन्यथा अगर (m_sig == 0) अणु
			vsd->sign = (fpscr & FPSCR_RMODE_MASK) ==
				      FPSCR_ROUND_MINUSINF ? 0x8000 : 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		m_sig = vsn->signअगरicand + m_sig;
	पूर्ण
	vsd->signअगरicand = m_sig;

	वापस 0;
पूर्ण

अटल u32
vfp_single_multiply(काष्ठा vfp_single *vsd, काष्ठा vfp_single *vsn, काष्ठा vfp_single *vsm, u32 fpscr)
अणु
	vfp_single_dump("VSN", vsn);
	vfp_single_dump("VSM", vsm);

	/*
	 * Ensure that 'n' is the largest magnitude number.  Note that
	 * अगर 'n' and 'm' have equal exponents, we करो not swap them.
	 * This ensures that NaN propagation works correctly.
	 */
	अगर (vsn->exponent < vsm->exponent) अणु
		काष्ठा vfp_single *t = vsn;
		vsn = vsm;
		vsm = t;
		pr_debug("VFP: swapping M <-> N\n");
	पूर्ण

	vsd->sign = vsn->sign ^ vsm->sign;

	/*
	 * If 'n' is an infinity or NaN, handle it.  'm' may be anything.
	 */
	अगर (vsn->exponent == 255) अणु
		अगर (vsn->signअगरicand || (vsm->exponent == 255 && vsm->signअगरicand))
			वापस vfp_propagate_nan(vsd, vsn, vsm, fpscr);
		अगर ((vsm->exponent | vsm->signअगरicand) == 0) अणु
			*vsd = vfp_single_शेष_qnan;
			वापस FPSCR_IOC;
		पूर्ण
		vsd->exponent = vsn->exponent;
		vsd->signअगरicand = 0;
		वापस 0;
	पूर्ण

	/*
	 * If 'm' is zero, the result is always zero.  In this हाल,
	 * 'n' may be zero or a number, but it doesn't matter which.
	 */
	अगर ((vsm->exponent | vsm->signअगरicand) == 0) अणु
		vsd->exponent = 0;
		vsd->signअगरicand = 0;
		वापस 0;
	पूर्ण

	/*
	 * We add 2 to the destination exponent क्रम the same reason as
	 * the addition हाल - though this समय we have +1 from each
	 * input opeअक्रम.
	 */
	vsd->exponent = vsn->exponent + vsm->exponent - 127 + 2;
	vsd->signअगरicand = vfp_hi64to32jamming((u64)vsn->signअगरicand * vsm->signअगरicand);

	vfp_single_dump("VSD", vsd);
	वापस 0;
पूर्ण

#घोषणा NEG_MULTIPLY	(1 << 0)
#घोषणा NEG_SUBTRACT	(1 << 1)

अटल u32
vfp_single_multiply_accumulate(पूर्णांक sd, पूर्णांक sn, s32 m, u32 fpscr, u32 negate, अक्षर *func)
अणु
	काष्ठा vfp_single vsd, vsp, vsn, vsm;
	u32 exceptions;
	s32 v;

	v = vfp_get_भग्न(sn);
	pr_debug("VFP: s%u = %08x\n", sn, v);
	vfp_single_unpack(&vsn, v);
	अगर (vsn.exponent == 0 && vsn.signअगरicand)
		vfp_single_normalise_denormal(&vsn);

	vfp_single_unpack(&vsm, m);
	अगर (vsm.exponent == 0 && vsm.signअगरicand)
		vfp_single_normalise_denormal(&vsm);

	exceptions = vfp_single_multiply(&vsp, &vsn, &vsm, fpscr);
	अगर (negate & NEG_MULTIPLY)
		vsp.sign = vfp_sign_negate(vsp.sign);

	v = vfp_get_भग्न(sd);
	pr_debug("VFP: s%u = %08x\n", sd, v);
	vfp_single_unpack(&vsn, v);
	अगर (vsn.exponent == 0 && vsn.signअगरicand)
		vfp_single_normalise_denormal(&vsn);
	अगर (negate & NEG_SUBTRACT)
		vsn.sign = vfp_sign_negate(vsn.sign);

	exceptions |= vfp_single_add(&vsd, &vsn, &vsp, fpscr);

	वापस vfp_single_normaliseround(sd, &vsd, fpscr, exceptions, func);
पूर्ण

/*
 * Standard operations
 */

/*
 * sd = sd + (sn * sm)
 */
अटल u32 vfp_single_fmac(पूर्णांक sd, पूर्णांक sn, s32 m, u32 fpscr)
अणु
	वापस vfp_single_multiply_accumulate(sd, sn, m, fpscr, 0, "fmac");
पूर्ण

/*
 * sd = sd - (sn * sm)
 */
अटल u32 vfp_single_fnmac(पूर्णांक sd, पूर्णांक sn, s32 m, u32 fpscr)
अणु
	वापस vfp_single_multiply_accumulate(sd, sn, m, fpscr, NEG_MULTIPLY, "fnmac");
पूर्ण

/*
 * sd = -sd + (sn * sm)
 */
अटल u32 vfp_single_fmsc(पूर्णांक sd, पूर्णांक sn, s32 m, u32 fpscr)
अणु
	वापस vfp_single_multiply_accumulate(sd, sn, m, fpscr, NEG_SUBTRACT, "fmsc");
पूर्ण

/*
 * sd = -sd - (sn * sm)
 */
अटल u32 vfp_single_fnmsc(पूर्णांक sd, पूर्णांक sn, s32 m, u32 fpscr)
अणु
	वापस vfp_single_multiply_accumulate(sd, sn, m, fpscr, NEG_SUBTRACT | NEG_MULTIPLY, "fnmsc");
पूर्ण

/*
 * sd = sn * sm
 */
अटल u32 vfp_single_fmul(पूर्णांक sd, पूर्णांक sn, s32 m, u32 fpscr)
अणु
	काष्ठा vfp_single vsd, vsn, vsm;
	u32 exceptions;
	s32 n = vfp_get_भग्न(sn);

	pr_debug("VFP: s%u = %08x\n", sn, n);

	vfp_single_unpack(&vsn, n);
	अगर (vsn.exponent == 0 && vsn.signअगरicand)
		vfp_single_normalise_denormal(&vsn);

	vfp_single_unpack(&vsm, m);
	अगर (vsm.exponent == 0 && vsm.signअगरicand)
		vfp_single_normalise_denormal(&vsm);

	exceptions = vfp_single_multiply(&vsd, &vsn, &vsm, fpscr);
	वापस vfp_single_normaliseround(sd, &vsd, fpscr, exceptions, "fmul");
पूर्ण

/*
 * sd = -(sn * sm)
 */
अटल u32 vfp_single_fnmul(पूर्णांक sd, पूर्णांक sn, s32 m, u32 fpscr)
अणु
	काष्ठा vfp_single vsd, vsn, vsm;
	u32 exceptions;
	s32 n = vfp_get_भग्न(sn);

	pr_debug("VFP: s%u = %08x\n", sn, n);

	vfp_single_unpack(&vsn, n);
	अगर (vsn.exponent == 0 && vsn.signअगरicand)
		vfp_single_normalise_denormal(&vsn);

	vfp_single_unpack(&vsm, m);
	अगर (vsm.exponent == 0 && vsm.signअगरicand)
		vfp_single_normalise_denormal(&vsm);

	exceptions = vfp_single_multiply(&vsd, &vsn, &vsm, fpscr);
	vsd.sign = vfp_sign_negate(vsd.sign);
	वापस vfp_single_normaliseround(sd, &vsd, fpscr, exceptions, "fnmul");
पूर्ण

/*
 * sd = sn + sm
 */
अटल u32 vfp_single_fadd(पूर्णांक sd, पूर्णांक sn, s32 m, u32 fpscr)
अणु
	काष्ठा vfp_single vsd, vsn, vsm;
	u32 exceptions;
	s32 n = vfp_get_भग्न(sn);

	pr_debug("VFP: s%u = %08x\n", sn, n);

	/*
	 * Unpack and normalise denormals.
	 */
	vfp_single_unpack(&vsn, n);
	अगर (vsn.exponent == 0 && vsn.signअगरicand)
		vfp_single_normalise_denormal(&vsn);

	vfp_single_unpack(&vsm, m);
	अगर (vsm.exponent == 0 && vsm.signअगरicand)
		vfp_single_normalise_denormal(&vsm);

	exceptions = vfp_single_add(&vsd, &vsn, &vsm, fpscr);

	वापस vfp_single_normaliseround(sd, &vsd, fpscr, exceptions, "fadd");
पूर्ण

/*
 * sd = sn - sm
 */
अटल u32 vfp_single_fsub(पूर्णांक sd, पूर्णांक sn, s32 m, u32 fpscr)
अणु
	/*
	 * Subtraction is addition with one sign inverted.
	 */
	वापस vfp_single_fadd(sd, sn, vfp_single_packed_negate(m), fpscr);
पूर्ण

/*
 * sd = sn / sm
 */
अटल u32 vfp_single_fभाग(पूर्णांक sd, पूर्णांक sn, s32 m, u32 fpscr)
अणु
	काष्ठा vfp_single vsd, vsn, vsm;
	u32 exceptions = 0;
	s32 n = vfp_get_भग्न(sn);
	पूर्णांक पंचांग, tn;

	pr_debug("VFP: s%u = %08x\n", sn, n);

	vfp_single_unpack(&vsn, n);
	vfp_single_unpack(&vsm, m);

	vsd.sign = vsn.sign ^ vsm.sign;

	tn = vfp_single_type(&vsn);
	पंचांग = vfp_single_type(&vsm);

	/*
	 * Is n a न_अंक?
	 */
	अगर (tn & VFP_न_अंक)
		जाओ vsn_nan;

	/*
	 * Is m a न_अंक?
	 */
	अगर (पंचांग & VFP_न_अंक)
		जाओ vsm_nan;

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
	 * If m is zero, उठाओ भाग0 exception
	 */
	अगर (पंचांग & VFP_ZERO)
		जाओ भागzero;

	/*
	 * If m is infinity, or n is zero, the result is zero
	 */
	अगर (पंचांग & VFP_अनन्त || tn & VFP_ZERO)
		जाओ zero;

	अगर (tn & VFP_DENORMAL)
		vfp_single_normalise_denormal(&vsn);
	अगर (पंचांग & VFP_DENORMAL)
		vfp_single_normalise_denormal(&vsm);

	/*
	 * Ok, we have two numbers, we can perक्रमm भागision.
	 */
	vsd.exponent = vsn.exponent - vsm.exponent + 127 - 1;
	vsm.signअगरicand <<= 1;
	अगर (vsm.signअगरicand <= (2 * vsn.signअगरicand)) अणु
		vsn.signअगरicand >>= 1;
		vsd.exponent++;
	पूर्ण
	अणु
		u64 signअगरicand = (u64)vsn.signअगरicand << 32;
		करो_भाग(signअगरicand, vsm.signअगरicand);
		vsd.signअगरicand = signअगरicand;
	पूर्ण
	अगर ((vsd.signअगरicand & 0x3f) == 0)
		vsd.signअगरicand |= ((u64)vsm.signअगरicand * vsd.signअगरicand != (u64)vsn.signअगरicand << 32);

	वापस vfp_single_normaliseround(sd, &vsd, fpscr, 0, "fdiv");

 vsn_nan:
	exceptions = vfp_propagate_nan(&vsd, &vsn, &vsm, fpscr);
 pack:
	vfp_put_भग्न(vfp_single_pack(&vsd), sd);
	वापस exceptions;

 vsm_nan:
	exceptions = vfp_propagate_nan(&vsd, &vsm, &vsn, fpscr);
	जाओ pack;

 zero:
	vsd.exponent = 0;
	vsd.signअगरicand = 0;
	जाओ pack;

 भागzero:
	exceptions = FPSCR_DZC;
 infinity:
	vsd.exponent = 255;
	vsd.signअगरicand = 0;
	जाओ pack;

 invalid:
	vfp_put_भग्न(vfp_single_pack(&vfp_single_शेष_qnan), sd);
	वापस FPSCR_IOC;
पूर्ण

अटल काष्ठा op fops[16] = अणु
	[FOP_TO_IDX(FOP_FMAC)]	= अणु vfp_single_fmac,  0 पूर्ण,
	[FOP_TO_IDX(FOP_FNMAC)]	= अणु vfp_single_fnmac, 0 पूर्ण,
	[FOP_TO_IDX(FOP_FMSC)]	= अणु vfp_single_fmsc,  0 पूर्ण,
	[FOP_TO_IDX(FOP_FNMSC)]	= अणु vfp_single_fnmsc, 0 पूर्ण,
	[FOP_TO_IDX(FOP_FMUL)]	= अणु vfp_single_fmul,  0 पूर्ण,
	[FOP_TO_IDX(FOP_FNMUL)]	= अणु vfp_single_fnmul, 0 पूर्ण,
	[FOP_TO_IDX(FOP_FADD)]	= अणु vfp_single_fadd,  0 पूर्ण,
	[FOP_TO_IDX(FOP_FSUB)]	= अणु vfp_single_fsub,  0 पूर्ण,
	[FOP_TO_IDX(FOP_FDIV)]	= अणु vfp_single_fभाग,  0 पूर्ण,
पूर्ण;

#घोषणा FREG_BANK(x)	((x) & 0x18)
#घोषणा FREG_IDX(x)	((x) & 7)

u32 vfp_single_cpकरो(u32 inst, u32 fpscr)
अणु
	u32 op = inst & FOP_MASK;
	u32 exceptions = 0;
	अचिन्हित पूर्णांक dest;
	अचिन्हित पूर्णांक sn = vfp_get_sn(inst);
	अचिन्हित पूर्णांक sm = vfp_get_sm(inst);
	अचिन्हित पूर्णांक vecitr, veclen, vecstride;
	काष्ठा op *fop;

	vecstride = 1 + ((fpscr & FPSCR_STRIDE_MASK) == FPSCR_STRIDE_MASK);

	fop = (op == FOP_EXT) ? &fops_ext[FEXT_TO_IDX(inst)] : &fops[FOP_TO_IDX(op)];

	/*
	 * fcvtsd takes a dN रेजिस्टर number as destination, not sN.
	 * Technically, अगर bit 0 of dd is set, this is an invalid
	 * inकाष्ठाion.  However, we ignore this क्रम efficiency.
	 * It also only operates on scalars.
	 */
	अगर (fop->flags & OP_DD)
		dest = vfp_get_dd(inst);
	अन्यथा
		dest = vfp_get_sd(inst);

	/*
	 * If destination bank is zero, vector length is always '1'.
	 * ARM DDI0100F C5.1.3, C5.3.2.
	 */
	अगर ((fop->flags & OP_SCALAR) || FREG_BANK(dest) == 0)
		veclen = 0;
	अन्यथा
		veclen = fpscr & FPSCR_LENGTH_MASK;

	pr_debug("VFP: vecstride=%u veclen=%u\n", vecstride,
		 (veclen >> FPSCR_LENGTH_BIT) + 1);

	अगर (!fop->fn)
		जाओ invalid;

	क्रम (vecitr = 0; vecitr <= veclen; vecitr += 1 << FPSCR_LENGTH_BIT) अणु
		s32 m = vfp_get_भग्न(sm);
		u32 except;
		अक्षर type;

		type = fop->flags & OP_DD ? 'd' : 's';
		अगर (op == FOP_EXT)
			pr_debug("VFP: itr%d (%c%u) = op[%u] (s%u=%08x)\n",
				 vecitr >> FPSCR_LENGTH_BIT, type, dest, sn,
				 sm, m);
		अन्यथा
			pr_debug("VFP: itr%d (%c%u) = (s%u) op[%u] (s%u=%08x)\n",
				 vecitr >> FPSCR_LENGTH_BIT, type, dest, sn,
				 FOP_TO_IDX(op), sm, m);

		except = fop->fn(dest, sn, m, fpscr);
		pr_debug("VFP: itr%d: exceptions=%08x\n",
			 vecitr >> FPSCR_LENGTH_BIT, except);

		exceptions |= except;

		/*
		 * CHECK: It appears to be undefined whether we stop when
		 * we encounter an exception.  We जारी.
		 */
		dest = FREG_BANK(dest) + ((FREG_IDX(dest) + vecstride) & 7);
		sn = FREG_BANK(sn) + ((FREG_IDX(sn) + vecstride) & 7);
		अगर (FREG_BANK(sm) != 0)
			sm = FREG_BANK(sm) + ((FREG_IDX(sm) + vecstride) & 7);
	पूर्ण
	वापस exceptions;

 invalid:
	वापस (u32)-1;
पूर्ण
