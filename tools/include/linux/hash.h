<शैली गुरु>
#अगर_अघोषित _LINUX_HASH_H
#घोषणा _LINUX_HASH_H
/* Fast hashing routine क्रम पूर्णांकs,  दीर्घs and poपूर्णांकers.
   (C) 2002 Nadia Yvette Chambers, IBM */

#समावेश <यंत्र/types.h>
#समावेश <linux/compiler.h>

/*
 * The "GOLDEN_RATIO_PRIME" is used in अगरs/btrfs/brtfs_inode.h and
 * fs/inode.c.  It's not actually prime any more (the previous primes
 * were actively bad क्रम hashing), but the name reमुख्यs.
 */
#अगर BITS_PER_LONG == 32
#घोषणा GOLDEN_RATIO_PRIME GOLDEN_RATIO_32
#घोषणा hash_दीर्घ(val, bits) hash_32(val, bits)
#या_अगर BITS_PER_LONG == 64
#घोषणा hash_दीर्घ(val, bits) hash_64(val, bits)
#घोषणा GOLDEN_RATIO_PRIME GOLDEN_RATIO_64
#अन्यथा
#त्रुटि Wordsize not 32 or 64
#पूर्ण_अगर

/*
 * This hash multiplies the input by a large odd number and takes the
 * high bits.  Since multiplication propagates changes to the most
 * signअगरicant end only, it is essential that the high bits of the
 * product be used क्रम the hash value.
 *
 * Chuck Lever verअगरied the effectiveness of this technique:
 * http://www.citi.umich.edu/techreports/reports/citi-tr-00-1.pdf
 *
 * Although a अक्रमom odd number will करो, it turns out that the golden
 * ratio phi = (वर्ग_मूल(5)-1)/2, or its negative, has particularly nice
 * properties.  (See Knuth vol 3, section 6.4, exercise 9.)
 *
 * These are the negative, (1 - phi) = phi**2 = (3 - वर्ग_मूल(5))/2,
 * which is very slightly easier to multiply by and makes no
 * dअगरference to the hash distribution.
 */
#घोषणा GOLDEN_RATIO_32 0x61C88647
#घोषणा GOLDEN_RATIO_64 0x61C8864680B583EBull

#अगर_घोषित CONFIG_HAVE_ARCH_HASH
/* This header may use the GOLDEN_RATIO_xx स्थिरants */
#समावेश <यंत्र/hash.h>
#पूर्ण_अगर

/*
 * The _generic versions exist only so lib/test_hash.c can compare
 * the arch-optimized versions with the generic.
 *
 * Note that अगर you change these, any <यंत्र/hash.h> that aren't updated
 * to match need to have their HAVE_ARCH_* define values updated so the
 * self-test will not false-positive.
 */
#अगर_अघोषित HAVE_ARCH__HASH_32
#घोषणा __hash_32 __hash_32_generic
#पूर्ण_अगर
अटल अंतरभूत u32 __hash_32_generic(u32 val)
अणु
	वापस val * GOLDEN_RATIO_32;
पूर्ण

#अगर_अघोषित HAVE_ARCH_HASH_32
#घोषणा hash_32 hash_32_generic
#पूर्ण_अगर
अटल अंतरभूत u32 hash_32_generic(u32 val, अचिन्हित पूर्णांक bits)
अणु
	/* High bits are more अक्रमom, so use them. */
	वापस __hash_32(val) >> (32 - bits);
पूर्ण

#अगर_अघोषित HAVE_ARCH_HASH_64
#घोषणा hash_64 hash_64_generic
#पूर्ण_अगर
अटल __always_अंतरभूत u32 hash_64_generic(u64 val, अचिन्हित पूर्णांक bits)
अणु
#अगर BITS_PER_LONG == 64
	/* 64x64-bit multiply is efficient on all 64-bit processors */
	वापस val * GOLDEN_RATIO_64 >> (64 - bits);
#अन्यथा
	/* Hash 64 bits using only 32x32-bit multiply. */
	वापस hash_32((u32)val ^ __hash_32(val >> 32), bits);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u32 hash_ptr(स्थिर व्योम *ptr, अचिन्हित पूर्णांक bits)
अणु
	वापस hash_दीर्घ((अचिन्हित दीर्घ)ptr, bits);
पूर्ण

/* This really should be called fold32_ptr; it करोes no hashing to speak of. */
अटल अंतरभूत u32 hash32_ptr(स्थिर व्योम *ptr)
अणु
	अचिन्हित दीर्घ val = (अचिन्हित दीर्घ)ptr;

#अगर BITS_PER_LONG == 64
	val ^= (val >> 32);
#पूर्ण_अगर
	वापस (u32)val;
पूर्ण

#पूर्ण_अगर /* _LINUX_HASH_H */
