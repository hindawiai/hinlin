<शैली गुरु>
/*
 * Aug 8, 2011 Bob Pearson with help from Joakim Tjernlund and George Spelvin
 * cleaned up code to current version of sparse and added the slicing-by-8
 * algorithm to the बंदly similar existing slicing-by-4 algorithm.
 *
 * Oct 15, 2000 Matt Domsch <Matt_Domsch@dell.com>
 * Nicer crc32 functions/करोcs submitted by linux@horizon.com.  Thanks!
 * Code was from the खुला करोमुख्य, copyright abanकरोned.  Code was
 * subsequently included in the kernel, thus was re-licensed under the
 * GNU GPL v2.
 *
 * Oct 12, 2000 Matt Domsch <Matt_Domsch@dell.com>
 * Same crc32 function was used in 5 other places in the kernel.
 * I made one version, and deleted the others.
 * There are various incantations of crc32().  Some use a seed of 0 or ~0.
 * Some xor at the end with ~0.  The generic crc32() function takes
 * seed as an argument, and करोesn't xor at the end.  Then inभागidual
 * users can करो whatever they need.
 *   drivers/net/smc9194.c uses seed ~0, करोesn't xor with ~0.
 *   fs/jffs2 uses seed 0, करोesn't xor with ~0.
 *   fs/partitions/efi.c uses seed ~0, xor's with ~0.
 *
 * This source code is licensed under the GNU General Public License,
 * Version 2.  See the file COPYING क्रम more details.
 */

/* see: Documentation/staging/crc32.rst क्रम a description of algorithms */

#समावेश <linux/crc32.h>
#समावेश <linux/crc32poly.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश "crc32defs.h"

#अगर CRC_LE_BITS > 8
# define tole(x) ((__क्रमce u32) cpu_to_le32(x))
#अन्यथा
# define tole(x) (x)
#पूर्ण_अगर

#अगर CRC_BE_BITS > 8
# define tobe(x) ((__क्रमce u32) cpu_to_be32(x))
#अन्यथा
# define tobe(x) (x)
#पूर्ण_अगर

#समावेश "crc32table.h"

MODULE_AUTHOR("Matt Domsch <Matt_Domsch@dell.com>");
MODULE_DESCRIPTION("Various CRC32 calculations");
MODULE_LICENSE("GPL");

#अगर CRC_LE_BITS > 8 || CRC_BE_BITS > 8

/* implements slicing-by-4 or slicing-by-8 algorithm */
अटल अंतरभूत u32 __pure
crc32_body(u32 crc, अचिन्हित अक्षर स्थिर *buf, माप_प्रकार len, स्थिर u32 (*tab)[256])
अणु
# अगरdef __LITTLE_ENDIAN
#  define DO_CRC(x) crc = t0[(crc ^ (x)) & 255] ^ (crc >> 8)
#  define DO_CRC4 (t3[(q) & 255] ^ t2[(q >> 8) & 255] ^ \
		   t1[(q >> 16) & 255] ^ t0[(q >> 24) & 255])
#  define DO_CRC8 (t7[(q) & 255] ^ t6[(q >> 8) & 255] ^ \
		   t5[(q >> 16) & 255] ^ t4[(q >> 24) & 255])
# अन्यथा
#  define DO_CRC(x) crc = t0[((crc >> 24) ^ (x)) & 255] ^ (crc << 8)
#  define DO_CRC4 (t0[(q) & 255] ^ t1[(q >> 8) & 255] ^ \
		   t2[(q >> 16) & 255] ^ t3[(q >> 24) & 255])
#  define DO_CRC8 (t4[(q) & 255] ^ t5[(q >> 8) & 255] ^ \
		   t6[(q >> 16) & 255] ^ t7[(q >> 24) & 255])
# endअगर
	स्थिर u32 *b;
	माप_प्रकार    rem_len;
# अगरdef CONFIG_X86
	माप_प्रकार i;
# endअगर
	स्थिर u32 *t0=tab[0], *t1=tab[1], *t2=tab[2], *t3=tab[3];
# अगर CRC_LE_BITS != 32
	स्थिर u32 *t4 = tab[4], *t5 = tab[5], *t6 = tab[6], *t7 = tab[7];
# endअगर
	u32 q;

	/* Align it */
	अगर (unlikely((दीर्घ)buf & 3 && len)) अणु
		करो अणु
			DO_CRC(*buf++);
		पूर्ण जबतक ((--len) && ((दीर्घ)buf)&3);
	पूर्ण

# अगर CRC_LE_BITS == 32
	rem_len = len & 3;
	len = len >> 2;
# अन्यथा
	rem_len = len & 7;
	len = len >> 3;
# endअगर

	b = (स्थिर u32 *)buf;
# अगरdef CONFIG_X86
	--b;
	क्रम (i = 0; i < len; i++) अणु
# अन्यथा
	क्रम (--b; len; --len) अणु
# endअगर
		q = crc ^ *++b; /* use pre increment क्रम speed */
# अगर CRC_LE_BITS == 32
		crc = DO_CRC4;
# अन्यथा
		crc = DO_CRC8;
		q = *++b;
		crc ^= DO_CRC4;
# endअगर
	पूर्ण
	len = rem_len;
	/* And the last few bytes */
	अगर (len) अणु
		u8 *p = (u8 *)(b + 1) - 1;
# अगरdef CONFIG_X86
		क्रम (i = 0; i < len; i++)
			DO_CRC(*++p); /* use pre increment क्रम speed */
# अन्यथा
		करो अणु
			DO_CRC(*++p); /* use pre increment क्रम speed */
		पूर्ण जबतक (--len);
# endअगर
	पूर्ण
	वापस crc;
#अघोषित DO_CRC
#अघोषित DO_CRC4
#अघोषित DO_CRC8
पूर्ण
#पूर्ण_अगर


/**
 * crc32_le_generic() - Calculate bitwise little-endian Ethernet AUTODIN II
 *			CRC32/CRC32C
 * @crc: seed value क्रम computation.  ~0 क्रम Ethernet, someबार 0 क्रम other
 *	 uses, or the previous crc32/crc32c value अगर computing incrementally.
 * @p: poपूर्णांकer to buffer over which CRC32/CRC32C is run
 * @len: length of buffer @p
 * @tab: little-endian Ethernet table
 * @polynomial: CRC32/CRC32c LE polynomial
 */
अटल अंतरभूत u32 __pure crc32_le_generic(u32 crc, अचिन्हित अक्षर स्थिर *p,
					  माप_प्रकार len, स्थिर u32 (*tab)[256],
					  u32 polynomial)
अणु
#अगर CRC_LE_BITS == 1
	पूर्णांक i;
	जबतक (len--) अणु
		crc ^= *p++;
		क्रम (i = 0; i < 8; i++)
			crc = (crc >> 1) ^ ((crc & 1) ? polynomial : 0);
	पूर्ण
# elअगर CRC_LE_BITS == 2
	जबतक (len--) अणु
		crc ^= *p++;
		crc = (crc >> 2) ^ tab[0][crc & 3];
		crc = (crc >> 2) ^ tab[0][crc & 3];
		crc = (crc >> 2) ^ tab[0][crc & 3];
		crc = (crc >> 2) ^ tab[0][crc & 3];
	पूर्ण
# elअगर CRC_LE_BITS == 4
	जबतक (len--) अणु
		crc ^= *p++;
		crc = (crc >> 4) ^ tab[0][crc & 15];
		crc = (crc >> 4) ^ tab[0][crc & 15];
	पूर्ण
# elअगर CRC_LE_BITS == 8
	/* aka Sarwate algorithm */
	जबतक (len--) अणु
		crc ^= *p++;
		crc = (crc >> 8) ^ tab[0][crc & 255];
	पूर्ण
# अन्यथा
	crc = (__क्रमce u32) __cpu_to_le32(crc);
	crc = crc32_body(crc, p, len, tab);
	crc = __le32_to_cpu((__क्रमce __le32)crc);
#पूर्ण_अगर
	वापस crc;
पूर्ण

#अगर CRC_LE_BITS == 1
u32 __pure __weak crc32_le(u32 crc, अचिन्हित अक्षर स्थिर *p, माप_प्रकार len)
अणु
	वापस crc32_le_generic(crc, p, len, शून्य, CRC32_POLY_LE);
पूर्ण
u32 __pure __weak __crc32c_le(u32 crc, अचिन्हित अक्षर स्थिर *p, माप_प्रकार len)
अणु
	वापस crc32_le_generic(crc, p, len, शून्य, CRC32C_POLY_LE);
पूर्ण
#अन्यथा
u32 __pure __weak crc32_le(u32 crc, अचिन्हित अक्षर स्थिर *p, माप_प्रकार len)
अणु
	वापस crc32_le_generic(crc, p, len,
			(स्थिर u32 (*)[256])crc32table_le, CRC32_POLY_LE);
पूर्ण
u32 __pure __weak __crc32c_le(u32 crc, अचिन्हित अक्षर स्थिर *p, माप_प्रकार len)
अणु
	वापस crc32_le_generic(crc, p, len,
			(स्थिर u32 (*)[256])crc32ctable_le, CRC32C_POLY_LE);
पूर्ण
#पूर्ण_अगर
EXPORT_SYMBOL(crc32_le);
EXPORT_SYMBOL(__crc32c_le);

u32 __pure crc32_le_base(u32, अचिन्हित अक्षर स्थिर *, माप_प्रकार) __alias(crc32_le);
u32 __pure __crc32c_le_base(u32, अचिन्हित अक्षर स्थिर *, माप_प्रकार) __alias(__crc32c_le);

/*
 * This multiplies the polynomials x and y modulo the given modulus.
 * This follows the "little-endian" CRC convention that the lsbit
 * represents the highest घातer of x, and the msbit represents x^0.
 */
अटल u32 __attribute_स्थिर__ gf2_multiply(u32 x, u32 y, u32 modulus)
अणु
	u32 product = x & 1 ? y : 0;
	पूर्णांक i;

	क्रम (i = 0; i < 31; i++) अणु
		product = (product >> 1) ^ (product & 1 ? modulus : 0);
		x >>= 1;
		product ^= x & 1 ? y : 0;
	पूर्ण

	वापस product;
पूर्ण

/**
 * crc32_generic_shअगरt - Append @len 0 bytes to crc, in logarithmic समय
 * @crc: The original little-endian CRC (i.e. lsbit is x^31 coefficient)
 * @len: The number of bytes. @crc is multiplied by x^(8*@len)
 * @polynomial: The modulus used to reduce the result to 32 bits.
 *
 * It's possible to parallelize CRC computations by computing a CRC
 * over separate ranges of a buffer, then summing them.
 * This shअगरts the given CRC by 8*len bits (i.e. produces the same effect
 * as appending len bytes of zero to the data), in समय proportional
 * to log(len).
 */
अटल u32 __attribute_स्थिर__ crc32_generic_shअगरt(u32 crc, माप_प्रकार len,
						   u32 polynomial)
अणु
	u32 घातer = polynomial;	/* CRC of x^32 */
	पूर्णांक i;

	/* Shअगरt up to 32 bits in the simple linear way */
	क्रम (i = 0; i < 8 * (पूर्णांक)(len & 3); i++)
		crc = (crc >> 1) ^ (crc & 1 ? polynomial : 0);

	len >>= 2;
	अगर (!len)
		वापस crc;

	क्रम (;;) अणु
		/* "power" is x^(2^i), modulo the polynomial */
		अगर (len & 1)
			crc = gf2_multiply(crc, घातer, polynomial);

		len >>= 1;
		अगर (!len)
			अवरोध;

		/* Square घातer, advancing to x^(2^(i+1)) */
		घातer = gf2_multiply(घातer, घातer, polynomial);
	पूर्ण

	वापस crc;
पूर्ण

u32 __attribute_स्थिर__ crc32_le_shअगरt(u32 crc, माप_प्रकार len)
अणु
	वापस crc32_generic_shअगरt(crc, len, CRC32_POLY_LE);
पूर्ण

u32 __attribute_स्थिर__ __crc32c_le_shअगरt(u32 crc, माप_प्रकार len)
अणु
	वापस crc32_generic_shअगरt(crc, len, CRC32C_POLY_LE);
पूर्ण
EXPORT_SYMBOL(crc32_le_shअगरt);
EXPORT_SYMBOL(__crc32c_le_shअगरt);

/**
 * crc32_be_generic() - Calculate bitwise big-endian Ethernet AUTODIN II CRC32
 * @crc: seed value क्रम computation.  ~0 क्रम Ethernet, someबार 0 क्रम
 *	other uses, or the previous crc32 value अगर computing incrementally.
 * @p: poपूर्णांकer to buffer over which CRC32 is run
 * @len: length of buffer @p
 * @tab: big-endian Ethernet table
 * @polynomial: CRC32 BE polynomial
 */
अटल अंतरभूत u32 __pure crc32_be_generic(u32 crc, अचिन्हित अक्षर स्थिर *p,
					  माप_प्रकार len, स्थिर u32 (*tab)[256],
					  u32 polynomial)
अणु
#अगर CRC_BE_BITS == 1
	पूर्णांक i;
	जबतक (len--) अणु
		crc ^= *p++ << 24;
		क्रम (i = 0; i < 8; i++)
			crc =
			    (crc << 1) ^ ((crc & 0x80000000) ? polynomial :
					  0);
	पूर्ण
# elअगर CRC_BE_BITS == 2
	जबतक (len--) अणु
		crc ^= *p++ << 24;
		crc = (crc << 2) ^ tab[0][crc >> 30];
		crc = (crc << 2) ^ tab[0][crc >> 30];
		crc = (crc << 2) ^ tab[0][crc >> 30];
		crc = (crc << 2) ^ tab[0][crc >> 30];
	पूर्ण
# elअगर CRC_BE_BITS == 4
	जबतक (len--) अणु
		crc ^= *p++ << 24;
		crc = (crc << 4) ^ tab[0][crc >> 28];
		crc = (crc << 4) ^ tab[0][crc >> 28];
	पूर्ण
# elअगर CRC_BE_BITS == 8
	जबतक (len--) अणु
		crc ^= *p++ << 24;
		crc = (crc << 8) ^ tab[0][crc >> 24];
	पूर्ण
# अन्यथा
	crc = (__क्रमce u32) __cpu_to_be32(crc);
	crc = crc32_body(crc, p, len, tab);
	crc = __be32_to_cpu((__क्रमce __be32)crc);
# endअगर
	वापस crc;
पूर्ण

#अगर CRC_BE_BITS == 1
u32 __pure crc32_be(u32 crc, अचिन्हित अक्षर स्थिर *p, माप_प्रकार len)
अणु
	वापस crc32_be_generic(crc, p, len, शून्य, CRC32_POLY_BE);
पूर्ण
#अन्यथा
u32 __pure crc32_be(u32 crc, अचिन्हित अक्षर स्थिर *p, माप_प्रकार len)
अणु
	वापस crc32_be_generic(crc, p, len,
			(स्थिर u32 (*)[256])crc32table_be, CRC32_POLY_BE);
पूर्ण
#पूर्ण_अगर
EXPORT_SYMBOL(crc32_be);
