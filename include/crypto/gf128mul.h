<शैली गुरु>
/* gf128mul.h - GF(2^128) multiplication functions
 *
 * Copyright (c) 2003, Dr Brian Gladman, Worcester, UK.
 * Copyright (c) 2006 Rik Snel <rsnel@cube.dyndns.org>
 *
 * Based on Dr Brian Gladman's (GPL'd) work published at
 * http://fp.gladman.plus.com/cryptography_technology/index.hपंचांग
 * See the original copyright notice below.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */
/*
 ---------------------------------------------------------------------------
 Copyright (c) 2003, Dr Brian Gladman, Worcester, UK.   All rights reserved.

 LICENSE TERMS

 The मुक्त distribution and use of this software in both source and binary
 क्रमm is allowed (with or without changes) provided that:

   1. distributions of this source code include the above copyright
      notice, this list of conditions and the following disclaimer;

   2. distributions in binary क्रमm include the above copyright
      notice, this list of conditions and the following disclaimer
      in the करोcumentation and/or other associated materials;

   3. the copyright holder's name is not used to enकरोrse products
      built using this software without specअगरic written permission.

 ALTERNATIVELY, provided that this notice is retained in full, this product
 may be distributed under the terms of the GNU General Public License (GPL),
 in which हाल the provisions of the GPL apply INSTEAD OF those given above.

 DISCLAIMER

 This software is provided 'as is' with no explicit or implied warranties
 in respect of its properties, including, but not limited to, correctness
 and/or fitness क्रम purpose.
 ---------------------------------------------------------------------------
 Issue Date: 31/01/2006

 An implementation of field multiplication in Galois Field GF(2^128)
*/

#अगर_अघोषित _CRYPTO_GF128MUL_H
#घोषणा _CRYPTO_GF128MUL_H

#समावेश <यंत्र/byteorder.h>
#समावेश <crypto/b128ops.h>
#समावेश <linux/slab.h>

/* Comment by Rik:
 *
 * For some background on GF(2^128) see क्रम example: 
 * http://csrc.nist.gov/groups/ST/toolkit/BCM/करोcuments/proposedmodes/gcm/gcm-revised-spec.pdf 
 *
 * The elements of GF(2^128) := GF(2)[X]/(X^128-X^7-X^2-X^1-1) can
 * be mapped to computer memory in a variety of ways. Let's examine
 * three common हालs.
 *
 * Take a look at the 16 binary octets below in memory order. The msb's
 * are left and the lsb's are right. अक्षर b[16] is an array and b[0] is
 * the first octet.
 *
 * 10000000 00000000 00000000 00000000 .... 00000000 00000000 00000000
 *   b[0]     b[1]     b[2]     b[3]          b[13]    b[14]    b[15]
 *
 * Every bit is a coefficient of some घातer of X. We can store the bits
 * in every byte in little-endian order and the bytes themselves also in
 * little endian order. I will call this lle (little-little-endian).
 * The above buffer represents the polynomial 1, and X^7+X^2+X^1+1 looks
 * like 11100001 00000000 .... 00000000 = अणु 0xE1, 0x00, पूर्ण.
 * This क्रमmat was originally implemented in gf128mul and is used
 * in GCM (Galois/Counter mode) and in ABL (Arbitrary Block Length).
 *
 * Another convention says: store the bits in bigendian order and the
 * bytes also. This is bbe (big-big-endian). Now the buffer above
 * represents X^127. X^7+X^2+X^1+1 looks like 00000000 .... 10000111,
 * b[15] = 0x87 and the rest is 0. LRW uses this convention and bbe
 * is partly implemented.
 *
 * Both of the above क्रमmats are easy to implement on big-endian
 * machines.
 *
 * XTS and EME (the latter of which is patent encumbered) use the ble
 * क्रमmat (bits are stored in big endian order and the bytes in little
 * endian). The above buffer represents X^7 in this हाल and the
 * primitive polynomial is b[0] = 0x87.
 *
 * The common machine word-size is smaller than 128 bits, so to make
 * an efficient implementation we must split पूर्णांकo machine word sizes.
 * This implementation uses 64-bit words क्रम the moment. Machine
 * endianness comes पूर्णांकo play. The lle क्रमmat in relation to machine
 * endianness is discussed below by the original author of gf128mul Dr
 * Brian Gladman.
 *
 * Let's look at the bbe and ble क्रमmat on a little endian machine.
 *
 * bbe on a little endian machine u32 x[4]:
 *
 *  MS            x[0]           LS  MS            x[1]		  LS
 *  ms   ls ms   ls ms   ls ms   ls  ms   ls ms   ls ms   ls ms   ls
 *  103..96 111.104 119.112 127.120  71...64 79...72 87...80 95...88
 *
 *  MS            x[2]           LS  MS            x[3]		  LS
 *  ms   ls ms   ls ms   ls ms   ls  ms   ls ms   ls ms   ls ms   ls
 *  39...32 47...40 55...48 63...56  07...00 15...08 23...16 31...24
 *
 * ble on a little endian machine
 *
 *  MS            x[0]           LS  MS            x[1]		  LS
 *  ms   ls ms   ls ms   ls ms   ls  ms   ls ms   ls ms   ls ms   ls
 *  31...24 23...16 15...08 07...00  63...56 55...48 47...40 39...32
 *
 *  MS            x[2]           LS  MS            x[3]		  LS
 *  ms   ls ms   ls ms   ls ms   ls  ms   ls ms   ls ms   ls ms   ls
 *  95...88 87...80 79...72 71...64  127.120 199.112 111.104 103..96
 *
 * Multiplications in GF(2^128) are mostly bit-shअगरts, so you see why
 * ble (and lbe also) are easier to implement on a little-endian
 * machine than on a big-endian machine. The converse holds क्रम bbe
 * and lle.
 *
 * Note: to have good alignment, it seems to me that it is sufficient
 * to keep elements of GF(2^128) in type u64[2]. On 32-bit wordsize
 * machines this will स्वतःmatically aligned to wordsize and on a 64-bit
 * machine also.
 */
/*	Multiply a GF(2^128) field element by x. Field elements are
    held in arrays of bytes in which field bits 8n..8n + 7 are held in
    byte[n], with lower indexed bits placed in the more numerically
    signअगरicant bit positions within bytes.

    On little endian machines the bit indexes translate पूर्णांकo the bit
    positions within four 32-bit words in the following way

    MS            x[0]           LS  MS            x[1]		  LS
    ms   ls ms   ls ms   ls ms   ls  ms   ls ms   ls ms   ls ms   ls
    24...31 16...23 08...15 00...07  56...63 48...55 40...47 32...39

    MS            x[2]           LS  MS            x[3]		  LS
    ms   ls ms   ls ms   ls ms   ls  ms   ls ms   ls ms   ls ms   ls
    88...95 80...87 72...79 64...71  120.127 112.119 104.111 96..103

    On big endian machines the bit indexes translate पूर्णांकo the bit
    positions within four 32-bit words in the following way

    MS            x[0]           LS  MS            x[1]		  LS
    ms   ls ms   ls ms   ls ms   ls  ms   ls ms   ls ms   ls ms   ls
    00...07 08...15 16...23 24...31  32...39 40...47 48...55 56...63

    MS            x[2]           LS  MS            x[3]		  LS
    ms   ls ms   ls ms   ls ms   ls  ms   ls ms   ls ms   ls ms   ls
    64...71 72...79 80...87 88...95  96..103 104.111 112.119 120.127
*/

/*	A slow generic version of gf_mul, implemented क्रम lle and bbe
 * 	It multiplies a and b and माला_दो the result in a */
व्योम gf128mul_lle(be128 *a, स्थिर be128 *b);

व्योम gf128mul_bbe(be128 *a, स्थिर be128 *b);

/*
 * The following functions multiply a field element by x in
 * the polynomial field representation.  They use 64-bit word operations
 * to gain speed but compensate क्रम machine endianness and hence work
 * correctly on both styles of machine.
 *
 * They are defined here क्रम perक्रमmance.
 */

अटल अंतरभूत u64 gf128mul_mask_from_bit(u64 x, पूर्णांक which)
अणु
	/* a स्थिरant-समय version of 'x & ((u64)1 << which) ? (u64)-1 : 0' */
	वापस ((s64)(x << (63 - which)) >> 63);
पूर्ण

अटल अंतरभूत व्योम gf128mul_x_lle(be128 *r, स्थिर be128 *x)
अणु
	u64 a = be64_to_cpu(x->a);
	u64 b = be64_to_cpu(x->b);

	/* equivalent to gf128mul_table_le[(b << 7) & 0xff] << 48
	 * (see crypto/gf128mul.c): */
	u64 _tt = gf128mul_mask_from_bit(b, 0) & ((u64)0xe1 << 56);

	r->b = cpu_to_be64((b >> 1) | (a << 63));
	r->a = cpu_to_be64((a >> 1) ^ _tt);
पूर्ण

अटल अंतरभूत व्योम gf128mul_x_bbe(be128 *r, स्थिर be128 *x)
अणु
	u64 a = be64_to_cpu(x->a);
	u64 b = be64_to_cpu(x->b);

	/* equivalent to gf128mul_table_be[a >> 63] (see crypto/gf128mul.c): */
	u64 _tt = gf128mul_mask_from_bit(a, 63) & 0x87;

	r->a = cpu_to_be64((a << 1) | (b >> 63));
	r->b = cpu_to_be64((b << 1) ^ _tt);
पूर्ण

/* needed by XTS */
अटल अंतरभूत व्योम gf128mul_x_ble(le128 *r, स्थिर le128 *x)
अणु
	u64 a = le64_to_cpu(x->a);
	u64 b = le64_to_cpu(x->b);

	/* equivalent to gf128mul_table_be[b >> 63] (see crypto/gf128mul.c): */
	u64 _tt = gf128mul_mask_from_bit(a, 63) & 0x87;

	r->a = cpu_to_le64((a << 1) | (b >> 63));
	r->b = cpu_to_le64((b << 1) ^ _tt);
पूर्ण

/* 4k table optimization */

काष्ठा gf128mul_4k अणु
	be128 t[256];
पूर्ण;

काष्ठा gf128mul_4k *gf128mul_init_4k_lle(स्थिर be128 *g);
काष्ठा gf128mul_4k *gf128mul_init_4k_bbe(स्थिर be128 *g);
व्योम gf128mul_4k_lle(be128 *a, स्थिर काष्ठा gf128mul_4k *t);
व्योम gf128mul_4k_bbe(be128 *a, स्थिर काष्ठा gf128mul_4k *t);
व्योम gf128mul_x8_ble(le128 *r, स्थिर le128 *x);
अटल अंतरभूत व्योम gf128mul_मुक्त_4k(काष्ठा gf128mul_4k *t)
अणु
	kमुक्त_sensitive(t);
पूर्ण


/* 64k table optimization, implemented क्रम bbe */

काष्ठा gf128mul_64k अणु
	काष्ठा gf128mul_4k *t[16];
पूर्ण;

/* First initialize with the स्थिरant factor with which you
 * want to multiply and then call gf128mul_64k_bbe with the other
 * factor in the first argument, and the table in the second.
 * Afterwards, the result is stored in *a.
 */
काष्ठा gf128mul_64k *gf128mul_init_64k_bbe(स्थिर be128 *g);
व्योम gf128mul_मुक्त_64k(काष्ठा gf128mul_64k *t);
व्योम gf128mul_64k_bbe(be128 *a, स्थिर काष्ठा gf128mul_64k *t);

#पूर्ण_अगर /* _CRYPTO_GF128MUL_H */
