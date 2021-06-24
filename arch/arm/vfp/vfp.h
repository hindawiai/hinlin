<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/arch/arm/vfp/vfp.h
 *
 *  Copyright (C) 2004 ARM Limited.
 *  Written by Deep Blue Solutions Limited.
 */

अटल अंतरभूत u32 vfp_shअगरtright32jamming(u32 val, अचिन्हित पूर्णांक shअगरt)
अणु
	अगर (shअगरt) अणु
		अगर (shअगरt < 32)
			val = val >> shअगरt | ((val << (32 - shअगरt)) != 0);
		अन्यथा
			val = val != 0;
	पूर्ण
	वापस val;
पूर्ण

अटल अंतरभूत u64 vfp_shअगरtright64jamming(u64 val, अचिन्हित पूर्णांक shअगरt)
अणु
	अगर (shअगरt) अणु
		अगर (shअगरt < 64)
			val = val >> shअगरt | ((val << (64 - shअगरt)) != 0);
		अन्यथा
			val = val != 0;
	पूर्ण
	वापस val;
पूर्ण

अटल अंतरभूत u32 vfp_hi64to32jamming(u64 val)
अणु
	u32 v;

	यंत्र(
	"cmp	%Q1, #1		@ vfp_hi64to32jamming\n\t"
	"movcc	%0, %R1\n\t"
	"orrcs	%0, %R1, #1"
	: "=r" (v) : "r" (val) : "cc");

	वापस v;
पूर्ण

अटल अंतरभूत व्योम add128(u64 *resh, u64 *resl, u64 nh, u64 nl, u64 mh, u64 ml)
अणु
	यंत्र(	"adds	%Q0, %Q2, %Q4\n\t"
		"adcs	%R0, %R2, %R4\n\t"
		"adcs	%Q1, %Q3, %Q5\n\t"
		"adc	%R1, %R3, %R5"
	    : "=r" (nl), "=r" (nh)
	    : "0" (nl), "1" (nh), "r" (ml), "r" (mh)
	    : "cc");
	*resh = nh;
	*resl = nl;
पूर्ण

अटल अंतरभूत व्योम sub128(u64 *resh, u64 *resl, u64 nh, u64 nl, u64 mh, u64 ml)
अणु
	यंत्र(	"subs	%Q0, %Q2, %Q4\n\t"
		"sbcs	%R0, %R2, %R4\n\t"
		"sbcs	%Q1, %Q3, %Q5\n\t"
		"sbc	%R1, %R3, %R5\n\t"
	    : "=r" (nl), "=r" (nh)
	    : "0" (nl), "1" (nh), "r" (ml), "r" (mh)
	    : "cc");
	*resh = nh;
	*resl = nl;
पूर्ण

अटल अंतरभूत व्योम mul64to128(u64 *resh, u64 *resl, u64 n, u64 m)
अणु
	u32 nh, nl, mh, ml;
	u64 rh, rma, rmb, rl;

	nl = n;
	ml = m;
	rl = (u64)nl * ml;

	nh = n >> 32;
	rma = (u64)nh * ml;

	mh = m >> 32;
	rmb = (u64)nl * mh;
	rma += rmb;

	rh = (u64)nh * mh;
	rh += ((u64)(rma < rmb) << 32) + (rma >> 32);

	rma <<= 32;
	rl += rma;
	rh += (rl < rma);

	*resl = rl;
	*resh = rh;
पूर्ण

अटल अंतरभूत व्योम shअगरt64left(u64 *resh, u64 *resl, u64 n)
अणु
	*resh = n >> 63;
	*resl = n << 1;
पूर्ण

अटल अंतरभूत u64 vfp_hi64multiply64(u64 n, u64 m)
अणु
	u64 rh, rl;
	mul64to128(&rh, &rl, n, m);
	वापस rh | (rl != 0);
पूर्ण

अटल अंतरभूत u64 vfp_estimate_भाग128to64(u64 nh, u64 nl, u64 m)
अणु
	u64 mh, ml, remh, reml, termh, terml, z;

	अगर (nh >= m)
		वापस ~0ULL;
	mh = m >> 32;
	अगर (mh << 32 <= nh) अणु
		z = 0xffffffff00000000ULL;
	पूर्ण अन्यथा अणु
		z = nh;
		करो_भाग(z, mh);
		z <<= 32;
	पूर्ण
	mul64to128(&termh, &terml, m, z);
	sub128(&remh, &reml, nh, nl, termh, terml);
	ml = m << 32;
	जबतक ((s64)remh < 0) अणु
		z -= 0x100000000ULL;
		add128(&remh, &reml, remh, reml, mh, ml);
	पूर्ण
	remh = (remh << 32) | (reml >> 32);
	अगर (mh << 32 <= remh) अणु
		z |= 0xffffffff;
	पूर्ण अन्यथा अणु
		करो_भाग(remh, mh);
		z |= remh;
	पूर्ण
	वापस z;
पूर्ण

/*
 * Operations on unpacked elements
 */
#घोषणा vfp_sign_negate(sign)	(sign ^ 0x8000)

/*
 * Single-precision
 */
काष्ठा vfp_single अणु
	s16	exponent;
	u16	sign;
	u32	signअगरicand;
पूर्ण;

यंत्रlinkage s32 vfp_get_भग्न(अचिन्हित पूर्णांक reg);
यंत्रlinkage व्योम vfp_put_भग्न(s32 val, अचिन्हित पूर्णांक reg);

/*
 * VFP_SINGLE_MANTISSA_BITS - number of bits in the mantissa
 * VFP_SINGLE_EXPONENT_BITS - number of bits in the exponent
 * VFP_SINGLE_LOW_BITS - number of low bits in the unpacked signअगरicand
 *  which are not propagated to the भग्न upon packing.
 */
#घोषणा VFP_SINGLE_MANTISSA_BITS	(23)
#घोषणा VFP_SINGLE_EXPONENT_BITS	(8)
#घोषणा VFP_SINGLE_LOW_BITS		(32 - VFP_SINGLE_MANTISSA_BITS - 2)
#घोषणा VFP_SINGLE_LOW_BITS_MASK	((1 << VFP_SINGLE_LOW_BITS) - 1)

/*
 * The bit in an unpacked भग्न which indicates that it is a quiet NaN
 */
#घोषणा VFP_SINGLE_SIGNIFICAND_Qन_अंक	(1 << (VFP_SINGLE_MANTISSA_BITS - 1 + VFP_SINGLE_LOW_BITS))

/*
 * Operations on packed single-precision numbers
 */
#घोषणा vfp_single_packed_sign(v)	((v) & 0x80000000)
#घोषणा vfp_single_packed_negate(v)	((v) ^ 0x80000000)
#घोषणा vfp_single_packed_असल(v)	((v) & ~0x80000000)
#घोषणा vfp_single_packed_exponent(v)	(((v) >> VFP_SINGLE_MANTISSA_BITS) & ((1 << VFP_SINGLE_EXPONENT_BITS) - 1))
#घोषणा vfp_single_packed_mantissa(v)	((v) & ((1 << VFP_SINGLE_MANTISSA_BITS) - 1))

/*
 * Unpack a single-precision भग्न.  Note that this वापसs the magnitude
 * of the single-precision भग्न mantissa with the 1. अगर necessary,
 * aligned to bit 30.
 */
अटल अंतरभूत व्योम vfp_single_unpack(काष्ठा vfp_single *s, s32 val)
अणु
	u32 signअगरicand;

	s->sign = vfp_single_packed_sign(val) >> 16,
	s->exponent = vfp_single_packed_exponent(val);

	signअगरicand = (u32) val;
	signअगरicand = (signअगरicand << (32 - VFP_SINGLE_MANTISSA_BITS)) >> 2;
	अगर (s->exponent && s->exponent != 255)
		signअगरicand |= 0x40000000;
	s->signअगरicand = signअगरicand;
पूर्ण

/*
 * Re-pack a single-precision भग्न.  This assumes that the भग्न is
 * alपढ़ोy normalised such that the MSB is bit 30, _not_ bit 31.
 */
अटल अंतरभूत s32 vfp_single_pack(काष्ठा vfp_single *s)
अणु
	u32 val;
	val = (s->sign << 16) +
	      (s->exponent << VFP_SINGLE_MANTISSA_BITS) +
	      (s->signअगरicand >> VFP_SINGLE_LOW_BITS);
	वापस (s32)val;
पूर्ण

#घोषणा VFP_NUMBER		(1<<0)
#घोषणा VFP_ZERO		(1<<1)
#घोषणा VFP_DENORMAL		(1<<2)
#घोषणा VFP_अनन्त		(1<<3)
#घोषणा VFP_न_अंक			(1<<4)
#घोषणा VFP_न_अंक_SIGNAL		(1<<5)

#घोषणा VFP_Qन_अंक		(VFP_न_अंक)
#घोषणा VFP_Sन_अंक		(VFP_न_अंक|VFP_न_अंक_SIGNAL)

अटल अंतरभूत पूर्णांक vfp_single_type(काष्ठा vfp_single *s)
अणु
	पूर्णांक type = VFP_NUMBER;
	अगर (s->exponent == 255) अणु
		अगर (s->signअगरicand == 0)
			type = VFP_अनन्त;
		अन्यथा अगर (s->signअगरicand & VFP_SINGLE_SIGNIFICAND_Qन_अंक)
			type = VFP_Qन_अंक;
		अन्यथा
			type = VFP_Sन_अंक;
	पूर्ण अन्यथा अगर (s->exponent == 0) अणु
		अगर (s->signअगरicand == 0)
			type |= VFP_ZERO;
		अन्यथा
			type |= VFP_DENORMAL;
	पूर्ण
	वापस type;
पूर्ण

#अगर_अघोषित DEBUG
#घोषणा vfp_single_normaliseround(sd,vsd,fpscr,except,func) __vfp_single_normaliseround(sd,vsd,fpscr,except)
u32 __vfp_single_normaliseround(पूर्णांक sd, काष्ठा vfp_single *vs, u32 fpscr, u32 exceptions);
#अन्यथा
u32 vfp_single_normaliseround(पूर्णांक sd, काष्ठा vfp_single *vs, u32 fpscr, u32 exceptions, स्थिर अक्षर *func);
#पूर्ण_अगर

/*
 * Double-precision
 */
काष्ठा vfp_द्विगुन अणु
	s16	exponent;
	u16	sign;
	u64	signअगरicand;
पूर्ण;

/*
 * VFP_REG_ZERO is a special रेजिस्टर number क्रम vfp_get_द्विगुन
 * which वापसs (द्विगुन)0.0.  This is useful क्रम the compare with
 * zero inकाष्ठाions.
 */
#अगर_घोषित CONFIG_VFPv3
#घोषणा VFP_REG_ZERO	32
#अन्यथा
#घोषणा VFP_REG_ZERO	16
#पूर्ण_अगर
यंत्रlinkage u64 vfp_get_द्विगुन(अचिन्हित पूर्णांक reg);
यंत्रlinkage व्योम vfp_put_द्विगुन(u64 val, अचिन्हित पूर्णांक reg);

#घोषणा VFP_DOUBLE_MANTISSA_BITS	(52)
#घोषणा VFP_DOUBLE_EXPONENT_BITS	(11)
#घोषणा VFP_DOUBLE_LOW_BITS		(64 - VFP_DOUBLE_MANTISSA_BITS - 2)
#घोषणा VFP_DOUBLE_LOW_BITS_MASK	((1 << VFP_DOUBLE_LOW_BITS) - 1)

/*
 * The bit in an unpacked द्विगुन which indicates that it is a quiet NaN
 */
#घोषणा VFP_DOUBLE_SIGNIFICAND_Qन_अंक	(1ULL << (VFP_DOUBLE_MANTISSA_BITS - 1 + VFP_DOUBLE_LOW_BITS))

/*
 * Operations on packed single-precision numbers
 */
#घोषणा vfp_द्विगुन_packed_sign(v)	((v) & (1ULL << 63))
#घोषणा vfp_द्विगुन_packed_negate(v)	((v) ^ (1ULL << 63))
#घोषणा vfp_द्विगुन_packed_असल(v)	((v) & ~(1ULL << 63))
#घोषणा vfp_द्विगुन_packed_exponent(v)	(((v) >> VFP_DOUBLE_MANTISSA_BITS) & ((1 << VFP_DOUBLE_EXPONENT_BITS) - 1))
#घोषणा vfp_द्विगुन_packed_mantissa(v)	((v) & ((1ULL << VFP_DOUBLE_MANTISSA_BITS) - 1))

/*
 * Unpack a द्विगुन-precision भग्न.  Note that this वापसs the magnitude
 * of the द्विगुन-precision भग्न mantissa with the 1. अगर necessary,
 * aligned to bit 62.
 */
अटल अंतरभूत व्योम vfp_द्विगुन_unpack(काष्ठा vfp_द्विगुन *s, s64 val)
अणु
	u64 signअगरicand;

	s->sign = vfp_द्विगुन_packed_sign(val) >> 48;
	s->exponent = vfp_द्विगुन_packed_exponent(val);

	signअगरicand = (u64) val;
	signअगरicand = (signअगरicand << (64 - VFP_DOUBLE_MANTISSA_BITS)) >> 2;
	अगर (s->exponent && s->exponent != 2047)
		signअगरicand |= (1ULL << 62);
	s->signअगरicand = signअगरicand;
पूर्ण

/*
 * Re-pack a द्विगुन-precision भग्न.  This assumes that the भग्न is
 * alपढ़ोy normalised such that the MSB is bit 30, _not_ bit 31.
 */
अटल अंतरभूत s64 vfp_द्विगुन_pack(काष्ठा vfp_द्विगुन *s)
अणु
	u64 val;
	val = ((u64)s->sign << 48) +
	      ((u64)s->exponent << VFP_DOUBLE_MANTISSA_BITS) +
	      (s->signअगरicand >> VFP_DOUBLE_LOW_BITS);
	वापस (s64)val;
पूर्ण

अटल अंतरभूत पूर्णांक vfp_द्विगुन_type(काष्ठा vfp_द्विगुन *s)
अणु
	पूर्णांक type = VFP_NUMBER;
	अगर (s->exponent == 2047) अणु
		अगर (s->signअगरicand == 0)
			type = VFP_अनन्त;
		अन्यथा अगर (s->signअगरicand & VFP_DOUBLE_SIGNIFICAND_Qन_अंक)
			type = VFP_Qन_अंक;
		अन्यथा
			type = VFP_Sन_अंक;
	पूर्ण अन्यथा अगर (s->exponent == 0) अणु
		अगर (s->signअगरicand == 0)
			type |= VFP_ZERO;
		अन्यथा
			type |= VFP_DENORMAL;
	पूर्ण
	वापस type;
पूर्ण

u32 vfp_द्विगुन_normaliseround(पूर्णांक dd, काष्ठा vfp_द्विगुन *vd, u32 fpscr, u32 exceptions, स्थिर अक्षर *func);

u32 vfp_estimate_वर्ग_मूल_signअगरicand(u32 exponent, u32 signअगरicand);

/*
 * A special flag to tell the normalisation code not to normalise.
 */
#घोषणा VFP_न_अंक_FLAG	0x100

/*
 * A bit pattern used to indicate the initial (unset) value of the
 * exception mask, in हाल nothing handles an inकाष्ठाion.  This
 * करोesn't include the न_अंक flag, which get masked out beक्रमe
 * we check क्रम an error.
 */
#घोषणा VFP_EXCEPTION_ERROR	((u32)-1 & ~VFP_न_अंक_FLAG)

/*
 * A flag to tell vfp inकाष्ठाion type.
 *  OP_SCALAR - this operation always operates in scalar mode
 *  OP_SD - the inकाष्ठाion exceptionally ग_लिखोs to a single precision result.
 *  OP_DD - the inकाष्ठाion exceptionally ग_लिखोs to a द्विगुन precision result.
 *  OP_SM - the inकाष्ठाion exceptionally पढ़ोs from a single precision opeअक्रम.
 */
#घोषणा OP_SCALAR	(1 << 0)
#घोषणा OP_SD		(1 << 1)
#घोषणा OP_DD		(1 << 1)
#घोषणा OP_SM		(1 << 2)

काष्ठा op अणु
	u32 (* स्थिर fn)(पूर्णांक dd, पूर्णांक dn, पूर्णांक dm, u32 fpscr);
	u32 flags;
पूर्ण;

यंत्रlinkage व्योम vfp_save_state(व्योम *location, u32 fpexc);
