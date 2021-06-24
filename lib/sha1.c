<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SHA1 routine optimized to करो word accesses rather than byte accesses,
 * and to aव्योम unnecessary copies पूर्णांकo the context array.
 *
 * This was based on the git SHA1 implementation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/bitops.h>
#समावेश <crypto/sha1.h>
#समावेश <यंत्र/unaligned.h>

/*
 * If you have 32 रेजिस्टरs or more, the compiler can (and should)
 * try to change the array[] accesses पूर्णांकo रेजिस्टरs. However, on
 * machines with less than ~25 रेजिस्टरs, that won't really work,
 * and at least gcc will make an unholy mess of it.
 *
 * So to aव्योम that mess which just slows things करोwn, we क्रमce
 * the stores to memory to actually happen (we might be better off
 * with a 'W(t)=(val);asm("":"+m" (W(t))' there instead, as
 * suggested by Artur Skawina - that will also make gcc unable to
 * try to करो the silly "optimize away loads" part because it won't
 * see what the value will be).
 *
 * Ben Herrenschmidt reports that on PPC, the C version comes बंद
 * to the optimized यंत्र with this (ie on PPC you करोn't want that
 * 'volatile', since there are lots of रेजिस्टरs).
 *
 * On ARM we get the best code generation by क्रमcing a full memory barrier
 * between each SHA_ROUND, otherwise gcc happily get wild with spilling and
 * the stack frame size simply explode and perक्रमmance goes करोwn the drain.
 */

#अगर_घोषित CONFIG_X86
  #घोषणा setW(x, val) (*(अस्थिर __u32 *)&W(x) = (val))
#या_अगर defined(CONFIG_ARM)
  #घोषणा setW(x, val) करो अणु W(x) = (val); __यंत्र__("":::"memory"); पूर्ण जबतक (0)
#अन्यथा
  #घोषणा setW(x, val) (W(x) = (val))
#पूर्ण_अगर

/* This "rolls" over the 512-bit array */
#घोषणा W(x) (array[(x)&15])

/*
 * Where करो we get the source from? The first 16 iterations get it from
 * the input data, the next mix it from the 512-bit array.
 */
#घोषणा SHA_SRC(t) get_unaligned_be32((__u32 *)data + t)
#घोषणा SHA_MIX(t) rol32(W(t+13) ^ W(t+8) ^ W(t+2) ^ W(t), 1)

#घोषणा SHA_ROUND(t, input, fn, स्थिरant, A, B, C, D, E) करो अणु \
	__u32 TEMP = input(t); setW(t, TEMP); \
	E += TEMP + rol32(A,5) + (fn) + (स्थिरant); \
	B = ror32(B, 2); पूर्ण जबतक (0)

#घोषणा T_0_15(t, A, B, C, D, E)  SHA_ROUND(t, SHA_SRC, (((C^D)&B)^D) , 0x5a827999, A, B, C, D, E )
#घोषणा T_16_19(t, A, B, C, D, E) SHA_ROUND(t, SHA_MIX, (((C^D)&B)^D) , 0x5a827999, A, B, C, D, E )
#घोषणा T_20_39(t, A, B, C, D, E) SHA_ROUND(t, SHA_MIX, (B^C^D) , 0x6ed9eba1, A, B, C, D, E )
#घोषणा T_40_59(t, A, B, C, D, E) SHA_ROUND(t, SHA_MIX, ((B&C)+(D&(B^C))) , 0x8f1bbcdc, A, B, C, D, E )
#घोषणा T_60_79(t, A, B, C, D, E) SHA_ROUND(t, SHA_MIX, (B^C^D) ,  0xca62c1d6, A, B, C, D, E )

/**
 * sha1_transक्रमm - single block SHA1 transक्रमm (deprecated)
 *
 * @digest: 160 bit digest to update
 * @data:   512 bits of data to hash
 * @array:  16 words of workspace (see note)
 *
 * This function executes SHA-1's पूर्णांकernal compression function.  It updates the
 * 160-bit पूर्णांकernal state (@digest) with a single 512-bit data block (@data).
 *
 * Don't use this function.  SHA-1 is no दीर्घer considered secure.  And even अगर
 * you करो have to use SHA-1, this isn't the correct way to hash something with
 * SHA-1 as this करोesn't handle padding and finalization.
 *
 * Note: If the hash is security sensitive, the caller should be sure
 * to clear the workspace. This is left to the caller to aव्योम
 * unnecessary clears between chained hashing operations.
 */
व्योम sha1_transक्रमm(__u32 *digest, स्थिर अक्षर *data, __u32 *array)
अणु
	__u32 A, B, C, D, E;

	A = digest[0];
	B = digest[1];
	C = digest[2];
	D = digest[3];
	E = digest[4];

	/* Round 1 - iterations 0-16 take their input from 'data' */
	T_0_15( 0, A, B, C, D, E);
	T_0_15( 1, E, A, B, C, D);
	T_0_15( 2, D, E, A, B, C);
	T_0_15( 3, C, D, E, A, B);
	T_0_15( 4, B, C, D, E, A);
	T_0_15( 5, A, B, C, D, E);
	T_0_15( 6, E, A, B, C, D);
	T_0_15( 7, D, E, A, B, C);
	T_0_15( 8, C, D, E, A, B);
	T_0_15( 9, B, C, D, E, A);
	T_0_15(10, A, B, C, D, E);
	T_0_15(11, E, A, B, C, D);
	T_0_15(12, D, E, A, B, C);
	T_0_15(13, C, D, E, A, B);
	T_0_15(14, B, C, D, E, A);
	T_0_15(15, A, B, C, D, E);

	/* Round 1 - tail. Input from 512-bit mixing array */
	T_16_19(16, E, A, B, C, D);
	T_16_19(17, D, E, A, B, C);
	T_16_19(18, C, D, E, A, B);
	T_16_19(19, B, C, D, E, A);

	/* Round 2 */
	T_20_39(20, A, B, C, D, E);
	T_20_39(21, E, A, B, C, D);
	T_20_39(22, D, E, A, B, C);
	T_20_39(23, C, D, E, A, B);
	T_20_39(24, B, C, D, E, A);
	T_20_39(25, A, B, C, D, E);
	T_20_39(26, E, A, B, C, D);
	T_20_39(27, D, E, A, B, C);
	T_20_39(28, C, D, E, A, B);
	T_20_39(29, B, C, D, E, A);
	T_20_39(30, A, B, C, D, E);
	T_20_39(31, E, A, B, C, D);
	T_20_39(32, D, E, A, B, C);
	T_20_39(33, C, D, E, A, B);
	T_20_39(34, B, C, D, E, A);
	T_20_39(35, A, B, C, D, E);
	T_20_39(36, E, A, B, C, D);
	T_20_39(37, D, E, A, B, C);
	T_20_39(38, C, D, E, A, B);
	T_20_39(39, B, C, D, E, A);

	/* Round 3 */
	T_40_59(40, A, B, C, D, E);
	T_40_59(41, E, A, B, C, D);
	T_40_59(42, D, E, A, B, C);
	T_40_59(43, C, D, E, A, B);
	T_40_59(44, B, C, D, E, A);
	T_40_59(45, A, B, C, D, E);
	T_40_59(46, E, A, B, C, D);
	T_40_59(47, D, E, A, B, C);
	T_40_59(48, C, D, E, A, B);
	T_40_59(49, B, C, D, E, A);
	T_40_59(50, A, B, C, D, E);
	T_40_59(51, E, A, B, C, D);
	T_40_59(52, D, E, A, B, C);
	T_40_59(53, C, D, E, A, B);
	T_40_59(54, B, C, D, E, A);
	T_40_59(55, A, B, C, D, E);
	T_40_59(56, E, A, B, C, D);
	T_40_59(57, D, E, A, B, C);
	T_40_59(58, C, D, E, A, B);
	T_40_59(59, B, C, D, E, A);

	/* Round 4 */
	T_60_79(60, A, B, C, D, E);
	T_60_79(61, E, A, B, C, D);
	T_60_79(62, D, E, A, B, C);
	T_60_79(63, C, D, E, A, B);
	T_60_79(64, B, C, D, E, A);
	T_60_79(65, A, B, C, D, E);
	T_60_79(66, E, A, B, C, D);
	T_60_79(67, D, E, A, B, C);
	T_60_79(68, C, D, E, A, B);
	T_60_79(69, B, C, D, E, A);
	T_60_79(70, A, B, C, D, E);
	T_60_79(71, E, A, B, C, D);
	T_60_79(72, D, E, A, B, C);
	T_60_79(73, C, D, E, A, B);
	T_60_79(74, B, C, D, E, A);
	T_60_79(75, A, B, C, D, E);
	T_60_79(76, E, A, B, C, D);
	T_60_79(77, D, E, A, B, C);
	T_60_79(78, C, D, E, A, B);
	T_60_79(79, B, C, D, E, A);

	digest[0] += A;
	digest[1] += B;
	digest[2] += C;
	digest[3] += D;
	digest[4] += E;
पूर्ण
EXPORT_SYMBOL(sha1_transक्रमm);

/**
 * sha1_init - initialize the vectors क्रम a SHA1 digest
 * @buf: vector to initialize
 */
व्योम sha1_init(__u32 *buf)
अणु
	buf[0] = 0x67452301;
	buf[1] = 0xefcdab89;
	buf[2] = 0x98badcfe;
	buf[3] = 0x10325476;
	buf[4] = 0xc3d2e1f0;
पूर्ण
EXPORT_SYMBOL(sha1_init);
