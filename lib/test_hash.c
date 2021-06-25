<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Test हालs क्रम <linux/hash.h> and <linux/stringhash.h>
 * This just verअगरies that various ways of computing a hash
 * produce the same thing and, क्रम हालs where a k-bit hash
 * value is requested, is of the requested size.
 *
 * We fill a buffer with a 255-byte null-terminated string,
 * and use both full_name_hash() and hashlen_string() to hash the
 * substrings from i to j, where 0 <= i < j < 256.
 *
 * The वापसed values are used to check that __hash_32() and
 * __hash_32_generic() compute the same thing.  Likewise hash_32()
 * and hash_64().
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt "\n"

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/hash.h>
#समावेश <linux/stringhash.h>
#समावेश <linux/prपूर्णांकk.h>

/* 32-bit XORSHIFT generator.  Seed must not be zero. */
अटल u32 __init __attribute_स्थिर__
xorshअगरt(u32 seed)
अणु
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	वापस seed;
पूर्ण

/* Given a non-zero x, वापसs a non-zero byte. */
अटल u8 __init __attribute_स्थिर__
mod255(u32 x)
अणु
	x = (x & 0xffff) + (x >> 16);	/* 1 <= x <= 0x1fffe */
	x = (x & 0xff) + (x >> 8);	/* 1 <= x <= 0x2fd */
	x = (x & 0xff) + (x >> 8);	/* 1 <= x <= 0x100 */
	x = (x & 0xff) + (x >> 8);	/* 1 <= x <= 0xff */
	वापस x;
पूर्ण

/* Fill the buffer with non-zero bytes. */
अटल व्योम __init
fill_buf(अक्षर *buf, माप_प्रकार len, u32 seed)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < len; i++) अणु
		seed = xorshअगरt(seed);
		buf[i] = mod255(seed);
	पूर्ण
पूर्ण

/*
 * Test the various पूर्णांकeger hash functions.  h64 (or its low-order bits)
 * is the पूर्णांकeger to hash.  hash_or accumulates the OR of the hash values,
 * which are later checked to see that they cover all the requested bits.
 *
 * Because these functions (as opposed to the string hashes) are all
 * अंतरभूत, the code being tested is actually in the module, and you can
 * recompile and re-test the module without rebooting.
 */
अटल bool __init
test_पूर्णांक_hash(अचिन्हित दीर्घ दीर्घ h64, u32 hash_or[2][33])
अणु
	पूर्णांक k;
	u32 h0 = (u32)h64, h1, h2;

	/* Test __hash32 */
	hash_or[0][0] |= h1 = __hash_32(h0);
#अगर_घोषित HAVE_ARCH__HASH_32
	hash_or[1][0] |= h2 = __hash_32_generic(h0);
#अगर HAVE_ARCH__HASH_32 == 1
	अगर (h1 != h2) अणु
		pr_err("__hash_32(%#x) = %#x != __hash_32_generic() = %#x",
			h0, h1, h2);
		वापस false;
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

	/* Test k = 1..32 bits */
	क्रम (k = 1; k <= 32; k++) अणु
		u32 स्थिर m = ((u32)2 << (k-1)) - 1;	/* Low k bits set */

		/* Test hash_32 */
		hash_or[0][k] |= h1 = hash_32(h0, k);
		अगर (h1 > m) अणु
			pr_err("hash_32(%#x, %d) = %#x > %#x", h0, k, h1, m);
			वापस false;
		पूर्ण
#अगर_घोषित HAVE_ARCH_HASH_32
		h2 = hash_32_generic(h0, k);
#अगर HAVE_ARCH_HASH_32 == 1
		अगर (h1 != h2) अणु
			pr_err("hash_32(%#x, %d) = %#x != hash_32_generic() "
				" = %#x", h0, k, h1, h2);
			वापस false;
		पूर्ण
#अन्यथा
		अगर (h2 > m) अणु
			pr_err("hash_32_generic(%#x, %d) = %#x > %#x",
				h0, k, h1, m);
			वापस false;
		पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
		/* Test hash_64 */
		hash_or[1][k] |= h1 = hash_64(h64, k);
		अगर (h1 > m) अणु
			pr_err("hash_64(%#llx, %d) = %#x > %#x", h64, k, h1, m);
			वापस false;
		पूर्ण
#अगर_घोषित HAVE_ARCH_HASH_64
		h2 = hash_64_generic(h64, k);
#अगर HAVE_ARCH_HASH_64 == 1
		अगर (h1 != h2) अणु
			pr_err("hash_64(%#llx, %d) = %#x != hash_64_generic() "
				"= %#x", h64, k, h1, h2);
			वापस false;
		पूर्ण
#अन्यथा
		अगर (h2 > m) अणु
			pr_err("hash_64_generic(%#llx, %d) = %#x > %#x",
				h64, k, h1, m);
			वापस false;
		पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
	पूर्ण

	(व्योम)h2;	/* Suppress unused variable warning */
	वापस true;
पूर्ण

#घोषणा SIZE 256	/* Run समय is cubic in SIZE */

अटल पूर्णांक __init
test_hash_init(व्योम)
अणु
	अक्षर buf[SIZE+1];
	u32 string_or = 0, hash_or[2][33] = अणु अणु 0, पूर्ण पूर्ण;
	अचिन्हित tests = 0;
	अचिन्हित दीर्घ दीर्घ h64 = 0;
	पूर्णांक i, j;

	fill_buf(buf, SIZE, 1);

	/* Test every possible non-empty substring in the buffer. */
	क्रम (j = SIZE; j > 0; --j) अणु
		buf[j] = '\0';

		क्रम (i = 0; i <= j; i++) अणु
			u64 hashlen = hashlen_string(buf+i, buf+i);
			u32 h0 = full_name_hash(buf+i, buf+i, j-i);

			/* Check that hashlen_string माला_लो the length right */
			अगर (hashlen_len(hashlen) != j-i) अणु
				pr_err("hashlen_string(%d..%d) returned length"
					" %u, expected %d",
					i, j, hashlen_len(hashlen), j-i);
				वापस -EINVAL;
			पूर्ण
			/* Check that the hashes match */
			अगर (hashlen_hash(hashlen) != h0) अणु
				pr_err("hashlen_string(%d..%d) = %08x != "
					"full_name_hash() = %08x",
					i, j, hashlen_hash(hashlen), h0);
				वापस -EINVAL;
			पूर्ण

			string_or |= h0;
			h64 = h64 << 32 | h0;	/* For use with hash_64 */
			अगर (!test_पूर्णांक_hash(h64, hash_or))
				वापस -EINVAL;
			tests++;
		पूर्ण /* i */
	पूर्ण /* j */

	/* The OR of all the hash values should cover all the bits */
	अगर (~string_or) अणु
		pr_err("OR of all string hash results = %#x != %#x",
			string_or, -1u);
		वापस -EINVAL;
	पूर्ण
	अगर (~hash_or[0][0]) अणु
		pr_err("OR of all __hash_32 results = %#x != %#x",
			hash_or[0][0], -1u);
		वापस -EINVAL;
	पूर्ण
#अगर_घोषित HAVE_ARCH__HASH_32
#अगर HAVE_ARCH__HASH_32 != 1	/* Test is poपूर्णांकless अगर results match */
	अगर (~hash_or[1][0]) अणु
		pr_err("OR of all __hash_32_generic results = %#x != %#x",
			hash_or[1][0], -1u);
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

	/* Likewise क्रम all the i-bit hash values */
	क्रम (i = 1; i <= 32; i++) अणु
		u32 स्थिर m = ((u32)2 << (i-1)) - 1;	/* Low i bits set */

		अगर (hash_or[0][i] != m) अणु
			pr_err("OR of all hash_32(%d) results = %#x "
				"(%#x expected)", i, hash_or[0][i], m);
			वापस -EINVAL;
		पूर्ण
		अगर (hash_or[1][i] != m) अणु
			pr_err("OR of all hash_64(%d) results = %#x "
				"(%#x expected)", i, hash_or[1][i], m);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Issue notices about skipped tests. */
#अगर_घोषित HAVE_ARCH__HASH_32
#अगर HAVE_ARCH__HASH_32 != 1
	pr_info("__hash_32() is arch-specific; not compared to generic.");
#पूर्ण_अगर
#अन्यथा
	pr_info("__hash_32() has no arch implementation to test.");
#पूर्ण_अगर
#अगर_घोषित HAVE_ARCH_HASH_32
#अगर HAVE_ARCH_HASH_32 != 1
	pr_info("hash_32() is arch-specific; not compared to generic.");
#पूर्ण_अगर
#अन्यथा
	pr_info("hash_32() has no arch implementation to test.");
#पूर्ण_अगर
#अगर_घोषित HAVE_ARCH_HASH_64
#अगर HAVE_ARCH_HASH_64 != 1
	pr_info("hash_64() is arch-specific; not compared to generic.");
#पूर्ण_अगर
#अन्यथा
	pr_info("hash_64() has no arch implementation to test.");
#पूर्ण_अगर

	pr_notice("%u tests passed.", tests);

	वापस 0;
पूर्ण

अटल व्योम __निकास test_hash_निकास(व्योम)
अणु
पूर्ण

module_init(test_hash_init);	/* Does everything */
module_निकास(test_hash_निकास);	/* Does nothing */

MODULE_LICENSE("GPL");
