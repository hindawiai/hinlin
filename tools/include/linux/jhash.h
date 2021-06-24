<शैली गुरु>
#अगर_अघोषित _LINUX_JHASH_H
#घोषणा _LINUX_JHASH_H

/* jhash.h: Jenkins hash support.
 *
 * Copyright (C) 2006. Bob Jenkins (bob_jenkins@burtleburtle.net)
 *
 * https://burtleburtle.net/bob/hash/
 *
 * These are the credits from Bob's sources:
 *
 * lookup3.c, by Bob Jenkins, May 2006, Public Doमुख्य.
 *
 * These are functions क्रम producing 32-bit hashes क्रम hash table lookup.
 * hashword(), hashlittle(), hashlittle2(), hashbig(), mix(), and final()
 * are बाह्यally useful functions.  Routines to test the hash are included
 * अगर SELF_TEST is defined.  You can use this मुक्त क्रम any purpose.  It's in
 * the खुला करोमुख्य.  It has no warranty.
 *
 * Copyright (C) 2009-2010 Jozsef Kadlecsik (kadlec@blackhole.kfki.hu)
 *
 * I've modified Bob's hash to be useful in the Linux kernel, and
 * any bugs present are my fault.
 * Jozsef
 */
#समावेश <linux/bitops.h>
#समावेश <linux/unaligned/packed_काष्ठा.h>

/* Best hash sizes are of घातer of two */
#घोषणा jhash_size(n)   ((u32)1<<(n))
/* Mask the hash value, i.e (value & jhash_mask(n)) instead of (value % n) */
#घोषणा jhash_mask(n)   (jhash_size(n)-1)

/* __jhash_mix -- mix 3 32-bit values reversibly. */
#घोषणा __jhash_mix(a, b, c)			\
अणु						\
	a -= c;  a ^= rol32(c, 4);  c += b;	\
	b -= a;  b ^= rol32(a, 6);  a += c;	\
	c -= b;  c ^= rol32(b, 8);  b += a;	\
	a -= c;  a ^= rol32(c, 16); c += b;	\
	b -= a;  b ^= rol32(a, 19); a += c;	\
	c -= b;  c ^= rol32(b, 4);  b += a;	\
पूर्ण

/* __jhash_final - final mixing of 3 32-bit values (a,b,c) पूर्णांकo c */
#घोषणा __jhash_final(a, b, c)			\
अणु						\
	c ^= b; c -= rol32(b, 14);		\
	a ^= c; a -= rol32(c, 11);		\
	b ^= a; b -= rol32(a, 25);		\
	c ^= b; c -= rol32(b, 16);		\
	a ^= c; a -= rol32(c, 4);		\
	b ^= a; b -= rol32(a, 14);		\
	c ^= b; c -= rol32(b, 24);		\
पूर्ण

/* An arbitrary initial parameter */
#घोषणा JHASH_INITVAL		0xdeadbeef

/* jhash - hash an arbitrary key
 * @k: sequence of bytes as key
 * @length: the length of the key
 * @initval: the previous hash, or an arbitray value
 *
 * The generic version, hashes an arbitrary sequence of bytes.
 * No alignment or length assumptions are made about the input key.
 *
 * Returns the hash value of the key. The result depends on endianness.
 */
अटल अंतरभूत u32 jhash(स्थिर व्योम *key, u32 length, u32 initval)
अणु
	u32 a, b, c;
	स्थिर u8 *k = key;

	/* Set up the पूर्णांकernal state */
	a = b = c = JHASH_INITVAL + length + initval;

	/* All but the last block: affect some 32 bits of (a,b,c) */
	जबतक (length > 12) अणु
		a += __get_unaligned_cpu32(k);
		b += __get_unaligned_cpu32(k + 4);
		c += __get_unaligned_cpu32(k + 8);
		__jhash_mix(a, b, c);
		length -= 12;
		k += 12;
	पूर्ण
	/* Last block: affect all 32 bits of (c) */
	/* All the हाल statements fall through */
	चयन (length) अणु
	हाल 12: c += (u32)k[11]<<24;
	हाल 11: c += (u32)k[10]<<16;
	हाल 10: c += (u32)k[9]<<8;
	हाल 9:  c += k[8];
	हाल 8:  b += (u32)k[7]<<24;
	हाल 7:  b += (u32)k[6]<<16;
	हाल 6:  b += (u32)k[5]<<8;
	हाल 5:  b += k[4];
	हाल 4:  a += (u32)k[3]<<24;
	हाल 3:  a += (u32)k[2]<<16;
	हाल 2:  a += (u32)k[1]<<8;
	हाल 1:  a += k[0];
		 __jhash_final(a, b, c);
	हाल 0: /* Nothing left to add */
		अवरोध;
	पूर्ण

	वापस c;
पूर्ण

/* jhash2 - hash an array of u32's
 * @k: the key which must be an array of u32's
 * @length: the number of u32's in the key
 * @initval: the previous hash, or an arbitray value
 *
 * Returns the hash value of the key.
 */
अटल अंतरभूत u32 jhash2(स्थिर u32 *k, u32 length, u32 initval)
अणु
	u32 a, b, c;

	/* Set up the पूर्णांकernal state */
	a = b = c = JHASH_INITVAL + (length<<2) + initval;

	/* Handle most of the key */
	जबतक (length > 3) अणु
		a += k[0];
		b += k[1];
		c += k[2];
		__jhash_mix(a, b, c);
		length -= 3;
		k += 3;
	पूर्ण

	/* Handle the last 3 u32's: all the हाल statements fall through */
	चयन (length) अणु
	हाल 3: c += k[2];
	हाल 2: b += k[1];
	हाल 1: a += k[0];
		__jhash_final(a, b, c);
	हाल 0:	/* Nothing left to add */
		अवरोध;
	पूर्ण

	वापस c;
पूर्ण


/* __jhash_nwords - hash exactly 3, 2 or 1 word(s) */
अटल अंतरभूत u32 __jhash_nwords(u32 a, u32 b, u32 c, u32 initval)
अणु
	a += initval;
	b += initval;
	c += initval;

	__jhash_final(a, b, c);

	वापस c;
पूर्ण

अटल अंतरभूत u32 jhash_3words(u32 a, u32 b, u32 c, u32 initval)
अणु
	वापस __jhash_nwords(a, b, c, initval + JHASH_INITVAL + (3 << 2));
पूर्ण

अटल अंतरभूत u32 jhash_2words(u32 a, u32 b, u32 initval)
अणु
	वापस __jhash_nwords(a, b, 0, initval + JHASH_INITVAL + (2 << 2));
पूर्ण

अटल अंतरभूत u32 jhash_1word(u32 a, u32 initval)
अणु
	वापस __jhash_nwords(a, 0, 0, initval + JHASH_INITVAL + (1 << 2));
पूर्ण

#पूर्ण_अगर /* _LINUX_JHASH_H */
