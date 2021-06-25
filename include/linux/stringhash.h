<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_STRINGHASH_H
#घोषणा __LINUX_STRINGHASH_H

#समावेश <linux/compiler.h>	/* For __pure */
#समावेश <linux/types.h>	/* For u32, u64 */
#समावेश <linux/hash.h>

/*
 * Routines क्रम hashing strings of bytes to a 32-bit hash value.
 *
 * These hash functions are NOT GUARANTEED STABLE between kernel
 * versions, architectures, or even repeated boots of the same kernel.
 * (E.g. they may depend on boot-समय hardware detection or be
 * deliberately अक्रमomized.)
 *
 * They are also not पूर्णांकended to be secure against collisions caused by
 * malicious inमाला_दो; much slower hash functions are required क्रम that.
 *
 * They are optimized क्रम pathname components, meaning लघु strings.
 * Even अगर a majority of files have दीर्घer names, the dynamic profile of
 * pathname components skews लघु due to लघु directory names.
 * (E.g. /usr/lib/libsesquipedalianism.so.3.141.)
 */

/*
 * Version 1: one byte at a समय.  Example of use:
 *
 * अचिन्हित दीर्घ hash = init_name_hash;
 * जबतक (*p)
 *	hash = partial_name_hash(छोटे(*p++), hash);
 * hash = end_name_hash(hash);
 *
 * Although this is deचिन्हित क्रम bytes, fs/hfsplus/unicode.c
 * abuses it to hash 16-bit values.
 */

/* Hash courtesy of the R5 hash in reiserfs modulo sign bits */
#घोषणा init_name_hash(salt)		(अचिन्हित दीर्घ)(salt)

/* partial hash update function. Assume roughly 4 bits per अक्षरacter */
अटल अंतरभूत अचिन्हित दीर्घ
partial_name_hash(अचिन्हित दीर्घ c, अचिन्हित दीर्घ prevhash)
अणु
	वापस (prevhash + (c << 4) + (c >> 4)) * 11;
पूर्ण

/*
 * Finally: cut करोwn the number of bits to a पूर्णांक value (and try to aव्योम
 * losing bits).  This also has the property (wanted by the dcache)
 * that the msbits make a good hash table index.
 */
अटल अंतरभूत अचिन्हित पूर्णांक end_name_hash(अचिन्हित दीर्घ hash)
अणु
	वापस hash_दीर्घ(hash, 32);
पूर्ण

/*
 * Version 2: One word (32 or 64 bits) at a समय.
 * If CONFIG_DCACHE_WORD_ACCESS is defined (meaning <यंत्र/word-at-a-समय.स>
 * exists, which describes major Linux platक्रमms like x86 and ARM), then
 * this computes a dअगरferent hash function much faster.
 *
 * If not set, this falls back to a wrapper around the preceding.
 */
बाह्य अचिन्हित पूर्णांक __pure full_name_hash(स्थिर व्योम *salt, स्थिर अक्षर *, अचिन्हित पूर्णांक);

/*
 * A hash_len is a u64 with the hash of a string in the low
 * half and the length in the high half.
 */
#घोषणा hashlen_hash(hashlen) ((u32)(hashlen))
#घोषणा hashlen_len(hashlen)  ((u32)((hashlen) >> 32))
#घोषणा hashlen_create(hash, len) ((u64)(len)<<32 | (u32)(hash))

/* Return the "hash_len" (hash and length) of a null-terminated string */
बाह्य u64 __pure hashlen_string(स्थिर व्योम *salt, स्थिर अक्षर *name);

#पूर्ण_अगर	/* __LINUX_STRINGHASH_H */
