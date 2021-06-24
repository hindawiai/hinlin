<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Checksum functions क्रम Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

/*  This was derived from arch/alpha/lib/checksum.c  */


#समावेश <linux/module.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/byteorder.h>
#समावेश <net/checksum.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पूर्णांकrinsics.h>


/*  Vector value operations  */
#घोषणा SIGN(x, y)	((0x8000ULL*x)<<y)
#घोषणा CARRY(x, y)	((0x0002ULL*x)<<y)
#घोषणा SELECT(x, y)	((0x0001ULL*x)<<y)

#घोषणा VR_NEGATE(a, b, c, d)	(SIGN(a, 48) + SIGN(b, 32) + SIGN(c, 16) \
	+ SIGN(d, 0))
#घोषणा VR_CARRY(a, b, c, d)	(CARRY(a, 48) + CARRY(b, 32) + CARRY(c, 16) \
	+ CARRY(d, 0))
#घोषणा VR_SELECT(a, b, c, d)	(SELECT(a, 48) + SELECT(b, 32) + SELECT(c, 16) \
	+ SELECT(d, 0))


/* optimized HEXAGON V3 पूर्णांकrinsic version */
अटल अंतरभूत अचिन्हित लघु from64to16(u64 x)
अणु
	u64 sum;

	sum = HEXAGON_P_vrmpyh_PP(x^VR_NEGATE(1, 1, 1, 1),
			     VR_SELECT(1, 1, 1, 1));
	sum += VR_CARRY(0, 0, 1, 0);
	sum = HEXAGON_P_vrmpyh_PP(sum, VR_SELECT(0, 0, 1, 1));

	वापस 0xFFFF & sum;
पूर्ण

/*
 * computes the checksum of the TCP/UDP pseuकरो-header
 * वापसs a 16-bit checksum, alपढ़ोy complemented.
 */
__sum16 csum_tcpudp_magic(__be32 saddr, __be32 daddr,
			  __u32 len, __u8 proto, __wsum sum)
अणु
	वापस (__क्रमce __sum16)~from64to16(
		(__क्रमce u64)saddr + (__क्रमce u64)daddr +
		(__क्रमce u64)sum + ((len + proto) << 8));
पूर्ण

__wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
			  __u32 len, __u8 proto, __wsum sum)
अणु
	u64 result;

	result = (__क्रमce u64)saddr + (__क्रमce u64)daddr +
		 (__क्रमce u64)sum + ((len + proto) << 8);

	/* Fold करोwn to 32-bits so we करोn't lose in the प्रकार-less
	   network stack.  */
	/* 64 to 33 */
	result = (result & 0xffffffffUL) + (result >> 32);
	/* 33 to 32 */
	result = (result & 0xffffffffUL) + (result >> 32);
	वापस (__क्रमce __wsum)result;
पूर्ण
EXPORT_SYMBOL(csum_tcpudp_nofold);

/*
 * Do a 64-bit checksum on an arbitrary memory area..
 *
 * This isn't a great routine, but it's not _horrible_ either. The
 * inner loop could be unrolled a bit further, and there are better
 * ways to करो the carry, but this is reasonable.
 */

/* optimized HEXAGON पूर्णांकrinsic version, with over पढ़ो fixed */
अचिन्हित पूर्णांक करो_csum(स्थिर व्योम *व्योमptr, पूर्णांक len)
अणु
	u64 sum0, sum1, x0, x1, *ptr8_o, *ptr8_e, *ptr8;
	पूर्णांक i, start, mid, end, mask;
	स्थिर अक्षर *ptr = व्योमptr;
	अचिन्हित लघु *ptr2;
	अचिन्हित पूर्णांक *ptr4;

	अगर (len <= 0)
		वापस 0;

	start = 0xF & (16-(((पूर्णांक) ptr) & 0xF)) ;
	mask  = 0x7fffffffUL >> HEXAGON_R_cl0_R(len);
	start = start & mask ;

	mid = len - start;
	end = mid & 0xF;
	mid = mid>>4;
	sum0 = mid << 18;
	sum1 = 0;

	अगर (start & 1)
		sum0 += (u64) (ptr[0] << 8);
	ptr2 = (अचिन्हित लघु *) &ptr[start & 1];
	अगर (start & 2)
		sum1 += (u64) ptr2[0];
	ptr4 = (अचिन्हित पूर्णांक *) &ptr[start & 3];
	अगर (start & 4) अणु
		sum0 = HEXAGON_P_vrmpyhacc_PP(sum0,
			VR_NEGATE(0, 0, 1, 1)^((u64)ptr4[0]),
			VR_SELECT(0, 0, 1, 1));
		sum0 += VR_SELECT(0, 0, 1, 0);
	पूर्ण
	ptr8 = (u64 *) &ptr[start & 7];
	अगर (start & 8) अणु
		sum1 = HEXAGON_P_vrmpyhacc_PP(sum1,
			VR_NEGATE(1, 1, 1, 1)^(ptr8[0]),
			VR_SELECT(1, 1, 1, 1));
		sum1 += VR_CARRY(0, 0, 1, 0);
	पूर्ण
	ptr8_o = (u64 *) (ptr + start);
	ptr8_e = (u64 *) (ptr + start + 8);

	अगर (mid) अणु
		x0 = *ptr8_e; ptr8_e += 2;
		x1 = *ptr8_o; ptr8_o += 2;
		अगर (mid > 1)
			क्रम (i = 0; i < mid-1; i++) अणु
				sum0 = HEXAGON_P_vrmpyhacc_PP(sum0,
					x0^VR_NEGATE(1, 1, 1, 1),
					VR_SELECT(1, 1, 1, 1));
				sum1 = HEXAGON_P_vrmpyhacc_PP(sum1,
					x1^VR_NEGATE(1, 1, 1, 1),
					VR_SELECT(1, 1, 1, 1));
				x0 = *ptr8_e; ptr8_e += 2;
				x1 = *ptr8_o; ptr8_o += 2;
			पूर्ण
		sum0 = HEXAGON_P_vrmpyhacc_PP(sum0, x0^VR_NEGATE(1, 1, 1, 1),
			VR_SELECT(1, 1, 1, 1));
		sum1 = HEXAGON_P_vrmpyhacc_PP(sum1, x1^VR_NEGATE(1, 1, 1, 1),
			VR_SELECT(1, 1, 1, 1));
	पूर्ण

	ptr4 = (अचिन्हित पूर्णांक *) &ptr[start + (mid * 16) + (end & 8)];
	अगर (end & 4) अणु
		sum1 = HEXAGON_P_vrmpyhacc_PP(sum1,
			VR_NEGATE(0, 0, 1, 1)^((u64)ptr4[0]),
			VR_SELECT(0, 0, 1, 1));
		sum1 += VR_SELECT(0, 0, 1, 0);
	पूर्ण
	ptr2 = (अचिन्हित लघु *) &ptr[start + (mid * 16) + (end & 12)];
	अगर (end & 2)
		sum0 += (u64) ptr2[0];

	अगर (end & 1)
		sum1 += (u64) ptr[start + (mid * 16) + (end & 14)];

	ptr8 = (u64 *) &ptr[start + (mid * 16)];
	अगर (end & 8) अणु
		sum0 = HEXAGON_P_vrmpyhacc_PP(sum0,
			VR_NEGATE(1, 1, 1, 1)^(ptr8[0]),
			VR_SELECT(1, 1, 1, 1));
		sum0 += VR_CARRY(0, 0, 1, 0);
	पूर्ण
	sum0 = HEXAGON_P_vrmpyh_PP((sum0+sum1)^VR_NEGATE(0, 0, 0, 1),
		VR_SELECT(0, 0, 1, 1));
	sum0 += VR_NEGATE(0, 0, 0, 1);
	sum0 = HEXAGON_P_vrmpyh_PP(sum0, VR_SELECT(0, 0, 1, 1));

	अगर (start & 1)
		sum0 = (sum0 << 8) | (0xFF & (sum0 >> 8));

	वापस 0xFFFF & sum0;
पूर्ण
