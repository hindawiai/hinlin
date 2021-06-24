<शैली गुरु>
/* Copyright (C) 2016 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 *
 * This file is provided under a dual BSD/GPLv2 license.
 *
 * SipHash: a fast लघु-input PRF
 * https://131002.net/siphash/
 *
 * This implementation is specअगरically क्रम SipHash2-4 क्रम a secure PRF
 * and HalfSipHash1-3/SipHash1-3 क्रम an insecure PRF only suitable क्रम
 * hashtables.
 */

#समावेश <linux/siphash.h>
#समावेश <यंत्र/unaligned.h>

#अगर defined(CONFIG_DCACHE_WORD_ACCESS) && BITS_PER_LONG == 64
#समावेश <linux/dcache.h>
#समावेश <यंत्र/word-at-a-समय.स>
#पूर्ण_अगर

#घोषणा SIPROUND \
	करो अणु \
	v0 += v1; v1 = rol64(v1, 13); v1 ^= v0; v0 = rol64(v0, 32); \
	v2 += v3; v3 = rol64(v3, 16); v3 ^= v2; \
	v0 += v3; v3 = rol64(v3, 21); v3 ^= v0; \
	v2 += v1; v1 = rol64(v1, 17); v1 ^= v2; v2 = rol64(v2, 32); \
	पूर्ण जबतक (0)

#घोषणा PREAMBLE(len) \
	u64 v0 = 0x736f6d6570736575ULL; \
	u64 v1 = 0x646f72616e646f6dULL; \
	u64 v2 = 0x6c7967656e657261ULL; \
	u64 v3 = 0x7465646279746573ULL; \
	u64 b = ((u64)(len)) << 56; \
	v3 ^= key->key[1]; \
	v2 ^= key->key[0]; \
	v1 ^= key->key[1]; \
	v0 ^= key->key[0];

#घोषणा POSTAMBLE \
	v3 ^= b; \
	SIPROUND; \
	SIPROUND; \
	v0 ^= b; \
	v2 ^= 0xff; \
	SIPROUND; \
	SIPROUND; \
	SIPROUND; \
	SIPROUND; \
	वापस (v0 ^ v1) ^ (v2 ^ v3);

u64 __siphash_aligned(स्थिर व्योम *data, माप_प्रकार len, स्थिर siphash_key_t *key)
अणु
	स्थिर u8 *end = data + len - (len % माप(u64));
	स्थिर u8 left = len & (माप(u64) - 1);
	u64 m;
	PREAMBLE(len)
	क्रम (; data != end; data += माप(u64)) अणु
		m = le64_to_cpup(data);
		v3 ^= m;
		SIPROUND;
		SIPROUND;
		v0 ^= m;
	पूर्ण
#अगर defined(CONFIG_DCACHE_WORD_ACCESS) && BITS_PER_LONG == 64
	अगर (left)
		b |= le64_to_cpu((__क्रमce __le64)(load_unaligned_zeropad(data) &
						  bytemask_from_count(left)));
#अन्यथा
	चयन (left) अणु
	हाल 7: b |= ((u64)end[6]) << 48; fallthrough;
	हाल 6: b |= ((u64)end[5]) << 40; fallthrough;
	हाल 5: b |= ((u64)end[4]) << 32; fallthrough;
	हाल 4: b |= le32_to_cpup(data); अवरोध;
	हाल 3: b |= ((u64)end[2]) << 16; fallthrough;
	हाल 2: b |= le16_to_cpup(data); अवरोध;
	हाल 1: b |= end[0];
	पूर्ण
#पूर्ण_अगर
	POSTAMBLE
पूर्ण
EXPORT_SYMBOL(__siphash_aligned);

#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
u64 __siphash_unaligned(स्थिर व्योम *data, माप_प्रकार len, स्थिर siphash_key_t *key)
अणु
	स्थिर u8 *end = data + len - (len % माप(u64));
	स्थिर u8 left = len & (माप(u64) - 1);
	u64 m;
	PREAMBLE(len)
	क्रम (; data != end; data += माप(u64)) अणु
		m = get_unaligned_le64(data);
		v3 ^= m;
		SIPROUND;
		SIPROUND;
		v0 ^= m;
	पूर्ण
#अगर defined(CONFIG_DCACHE_WORD_ACCESS) && BITS_PER_LONG == 64
	अगर (left)
		b |= le64_to_cpu((__क्रमce __le64)(load_unaligned_zeropad(data) &
						  bytemask_from_count(left)));
#अन्यथा
	चयन (left) अणु
	हाल 7: b |= ((u64)end[6]) << 48; fallthrough;
	हाल 6: b |= ((u64)end[5]) << 40; fallthrough;
	हाल 5: b |= ((u64)end[4]) << 32; fallthrough;
	हाल 4: b |= get_unaligned_le32(end); अवरोध;
	हाल 3: b |= ((u64)end[2]) << 16; fallthrough;
	हाल 2: b |= get_unaligned_le16(end); अवरोध;
	हाल 1: b |= end[0];
	पूर्ण
#पूर्ण_अगर
	POSTAMBLE
पूर्ण
EXPORT_SYMBOL(__siphash_unaligned);
#पूर्ण_अगर

/**
 * siphash_1u64 - compute 64-bit siphash PRF value of a u64
 * @first: first u64
 * @key: the siphash key
 */
u64 siphash_1u64(स्थिर u64 first, स्थिर siphash_key_t *key)
अणु
	PREAMBLE(8)
	v3 ^= first;
	SIPROUND;
	SIPROUND;
	v0 ^= first;
	POSTAMBLE
पूर्ण
EXPORT_SYMBOL(siphash_1u64);

/**
 * siphash_2u64 - compute 64-bit siphash PRF value of 2 u64
 * @first: first u64
 * @second: second u64
 * @key: the siphash key
 */
u64 siphash_2u64(स्थिर u64 first, स्थिर u64 second, स्थिर siphash_key_t *key)
अणु
	PREAMBLE(16)
	v3 ^= first;
	SIPROUND;
	SIPROUND;
	v0 ^= first;
	v3 ^= second;
	SIPROUND;
	SIPROUND;
	v0 ^= second;
	POSTAMBLE
पूर्ण
EXPORT_SYMBOL(siphash_2u64);

/**
 * siphash_3u64 - compute 64-bit siphash PRF value of 3 u64
 * @first: first u64
 * @second: second u64
 * @third: third u64
 * @key: the siphash key
 */
u64 siphash_3u64(स्थिर u64 first, स्थिर u64 second, स्थिर u64 third,
		 स्थिर siphash_key_t *key)
अणु
	PREAMBLE(24)
	v3 ^= first;
	SIPROUND;
	SIPROUND;
	v0 ^= first;
	v3 ^= second;
	SIPROUND;
	SIPROUND;
	v0 ^= second;
	v3 ^= third;
	SIPROUND;
	SIPROUND;
	v0 ^= third;
	POSTAMBLE
पूर्ण
EXPORT_SYMBOL(siphash_3u64);

/**
 * siphash_4u64 - compute 64-bit siphash PRF value of 4 u64
 * @first: first u64
 * @second: second u64
 * @third: third u64
 * @क्रमth: क्रमth u64
 * @key: the siphash key
 */
u64 siphash_4u64(स्थिर u64 first, स्थिर u64 second, स्थिर u64 third,
		 स्थिर u64 क्रमth, स्थिर siphash_key_t *key)
अणु
	PREAMBLE(32)
	v3 ^= first;
	SIPROUND;
	SIPROUND;
	v0 ^= first;
	v3 ^= second;
	SIPROUND;
	SIPROUND;
	v0 ^= second;
	v3 ^= third;
	SIPROUND;
	SIPROUND;
	v0 ^= third;
	v3 ^= क्रमth;
	SIPROUND;
	SIPROUND;
	v0 ^= क्रमth;
	POSTAMBLE
पूर्ण
EXPORT_SYMBOL(siphash_4u64);

u64 siphash_1u32(स्थिर u32 first, स्थिर siphash_key_t *key)
अणु
	PREAMBLE(4)
	b |= first;
	POSTAMBLE
पूर्ण
EXPORT_SYMBOL(siphash_1u32);

u64 siphash_3u32(स्थिर u32 first, स्थिर u32 second, स्थिर u32 third,
		 स्थिर siphash_key_t *key)
अणु
	u64 combined = (u64)second << 32 | first;
	PREAMBLE(12)
	v3 ^= combined;
	SIPROUND;
	SIPROUND;
	v0 ^= combined;
	b |= third;
	POSTAMBLE
पूर्ण
EXPORT_SYMBOL(siphash_3u32);

#अगर BITS_PER_LONG == 64
/* Note that on 64-bit, we make HalfSipHash1-3 actually be SipHash1-3, क्रम
 * perक्रमmance reasons. On 32-bit, below, we actually implement HalfSipHash1-3.
 */

#घोषणा HSIPROUND SIPROUND
#घोषणा HPREAMBLE(len) PREAMBLE(len)
#घोषणा HPOSTAMBLE \
	v3 ^= b; \
	HSIPROUND; \
	v0 ^= b; \
	v2 ^= 0xff; \
	HSIPROUND; \
	HSIPROUND; \
	HSIPROUND; \
	वापस (v0 ^ v1) ^ (v2 ^ v3);

u32 __hsiphash_aligned(स्थिर व्योम *data, माप_प्रकार len, स्थिर hsiphash_key_t *key)
अणु
	स्थिर u8 *end = data + len - (len % माप(u64));
	स्थिर u8 left = len & (माप(u64) - 1);
	u64 m;
	HPREAMBLE(len)
	क्रम (; data != end; data += माप(u64)) अणु
		m = le64_to_cpup(data);
		v3 ^= m;
		HSIPROUND;
		v0 ^= m;
	पूर्ण
#अगर defined(CONFIG_DCACHE_WORD_ACCESS) && BITS_PER_LONG == 64
	अगर (left)
		b |= le64_to_cpu((__क्रमce __le64)(load_unaligned_zeropad(data) &
						  bytemask_from_count(left)));
#अन्यथा
	चयन (left) अणु
	हाल 7: b |= ((u64)end[6]) << 48; fallthrough;
	हाल 6: b |= ((u64)end[5]) << 40; fallthrough;
	हाल 5: b |= ((u64)end[4]) << 32; fallthrough;
	हाल 4: b |= le32_to_cpup(data); अवरोध;
	हाल 3: b |= ((u64)end[2]) << 16; fallthrough;
	हाल 2: b |= le16_to_cpup(data); अवरोध;
	हाल 1: b |= end[0];
	पूर्ण
#पूर्ण_अगर
	HPOSTAMBLE
पूर्ण
EXPORT_SYMBOL(__hsiphash_aligned);

#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
u32 __hsiphash_unaligned(स्थिर व्योम *data, माप_प्रकार len,
			 स्थिर hsiphash_key_t *key)
अणु
	स्थिर u8 *end = data + len - (len % माप(u64));
	स्थिर u8 left = len & (माप(u64) - 1);
	u64 m;
	HPREAMBLE(len)
	क्रम (; data != end; data += माप(u64)) अणु
		m = get_unaligned_le64(data);
		v3 ^= m;
		HSIPROUND;
		v0 ^= m;
	पूर्ण
#अगर defined(CONFIG_DCACHE_WORD_ACCESS) && BITS_PER_LONG == 64
	अगर (left)
		b |= le64_to_cpu((__क्रमce __le64)(load_unaligned_zeropad(data) &
						  bytemask_from_count(left)));
#अन्यथा
	चयन (left) अणु
	हाल 7: b |= ((u64)end[6]) << 48; fallthrough;
	हाल 6: b |= ((u64)end[5]) << 40; fallthrough;
	हाल 5: b |= ((u64)end[4]) << 32; fallthrough;
	हाल 4: b |= get_unaligned_le32(end); अवरोध;
	हाल 3: b |= ((u64)end[2]) << 16; fallthrough;
	हाल 2: b |= get_unaligned_le16(end); अवरोध;
	हाल 1: b |= end[0];
	पूर्ण
#पूर्ण_अगर
	HPOSTAMBLE
पूर्ण
EXPORT_SYMBOL(__hsiphash_unaligned);
#पूर्ण_अगर

/**
 * hsiphash_1u32 - compute 64-bit hsiphash PRF value of a u32
 * @first: first u32
 * @key: the hsiphash key
 */
u32 hsiphash_1u32(स्थिर u32 first, स्थिर hsiphash_key_t *key)
अणु
	HPREAMBLE(4)
	b |= first;
	HPOSTAMBLE
पूर्ण
EXPORT_SYMBOL(hsiphash_1u32);

/**
 * hsiphash_2u32 - compute 32-bit hsiphash PRF value of 2 u32
 * @first: first u32
 * @second: second u32
 * @key: the hsiphash key
 */
u32 hsiphash_2u32(स्थिर u32 first, स्थिर u32 second, स्थिर hsiphash_key_t *key)
अणु
	u64 combined = (u64)second << 32 | first;
	HPREAMBLE(8)
	v3 ^= combined;
	HSIPROUND;
	v0 ^= combined;
	HPOSTAMBLE
पूर्ण
EXPORT_SYMBOL(hsiphash_2u32);

/**
 * hsiphash_3u32 - compute 32-bit hsiphash PRF value of 3 u32
 * @first: first u32
 * @second: second u32
 * @third: third u32
 * @key: the hsiphash key
 */
u32 hsiphash_3u32(स्थिर u32 first, स्थिर u32 second, स्थिर u32 third,
		  स्थिर hsiphash_key_t *key)
अणु
	u64 combined = (u64)second << 32 | first;
	HPREAMBLE(12)
	v3 ^= combined;
	HSIPROUND;
	v0 ^= combined;
	b |= third;
	HPOSTAMBLE
पूर्ण
EXPORT_SYMBOL(hsiphash_3u32);

/**
 * hsiphash_4u32 - compute 32-bit hsiphash PRF value of 4 u32
 * @first: first u32
 * @second: second u32
 * @third: third u32
 * @क्रमth: क्रमth u32
 * @key: the hsiphash key
 */
u32 hsiphash_4u32(स्थिर u32 first, स्थिर u32 second, स्थिर u32 third,
		  स्थिर u32 क्रमth, स्थिर hsiphash_key_t *key)
अणु
	u64 combined = (u64)second << 32 | first;
	HPREAMBLE(16)
	v3 ^= combined;
	HSIPROUND;
	v0 ^= combined;
	combined = (u64)क्रमth << 32 | third;
	v3 ^= combined;
	HSIPROUND;
	v0 ^= combined;
	HPOSTAMBLE
पूर्ण
EXPORT_SYMBOL(hsiphash_4u32);
#अन्यथा
#घोषणा HSIPROUND \
	करो अणु \
	v0 += v1; v1 = rol32(v1, 5); v1 ^= v0; v0 = rol32(v0, 16); \
	v2 += v3; v3 = rol32(v3, 8); v3 ^= v2; \
	v0 += v3; v3 = rol32(v3, 7); v3 ^= v0; \
	v2 += v1; v1 = rol32(v1, 13); v1 ^= v2; v2 = rol32(v2, 16); \
	पूर्ण जबतक (0)

#घोषणा HPREAMBLE(len) \
	u32 v0 = 0; \
	u32 v1 = 0; \
	u32 v2 = 0x6c796765U; \
	u32 v3 = 0x74656462U; \
	u32 b = ((u32)(len)) << 24; \
	v3 ^= key->key[1]; \
	v2 ^= key->key[0]; \
	v1 ^= key->key[1]; \
	v0 ^= key->key[0];

#घोषणा HPOSTAMBLE \
	v3 ^= b; \
	HSIPROUND; \
	v0 ^= b; \
	v2 ^= 0xff; \
	HSIPROUND; \
	HSIPROUND; \
	HSIPROUND; \
	वापस v1 ^ v3;

u32 __hsiphash_aligned(स्थिर व्योम *data, माप_प्रकार len, स्थिर hsiphash_key_t *key)
अणु
	स्थिर u8 *end = data + len - (len % माप(u32));
	स्थिर u8 left = len & (माप(u32) - 1);
	u32 m;
	HPREAMBLE(len)
	क्रम (; data != end; data += माप(u32)) अणु
		m = le32_to_cpup(data);
		v3 ^= m;
		HSIPROUND;
		v0 ^= m;
	पूर्ण
	चयन (left) अणु
	हाल 3: b |= ((u32)end[2]) << 16; fallthrough;
	हाल 2: b |= le16_to_cpup(data); अवरोध;
	हाल 1: b |= end[0];
	पूर्ण
	HPOSTAMBLE
पूर्ण
EXPORT_SYMBOL(__hsiphash_aligned);

#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
u32 __hsiphash_unaligned(स्थिर व्योम *data, माप_प्रकार len,
			 स्थिर hsiphash_key_t *key)
अणु
	स्थिर u8 *end = data + len - (len % माप(u32));
	स्थिर u8 left = len & (माप(u32) - 1);
	u32 m;
	HPREAMBLE(len)
	क्रम (; data != end; data += माप(u32)) अणु
		m = get_unaligned_le32(data);
		v3 ^= m;
		HSIPROUND;
		v0 ^= m;
	पूर्ण
	चयन (left) अणु
	हाल 3: b |= ((u32)end[2]) << 16; fallthrough;
	हाल 2: b |= get_unaligned_le16(end); अवरोध;
	हाल 1: b |= end[0];
	पूर्ण
	HPOSTAMBLE
पूर्ण
EXPORT_SYMBOL(__hsiphash_unaligned);
#पूर्ण_अगर

/**
 * hsiphash_1u32 - compute 32-bit hsiphash PRF value of a u32
 * @first: first u32
 * @key: the hsiphash key
 */
u32 hsiphash_1u32(स्थिर u32 first, स्थिर hsiphash_key_t *key)
अणु
	HPREAMBLE(4)
	v3 ^= first;
	HSIPROUND;
	v0 ^= first;
	HPOSTAMBLE
पूर्ण
EXPORT_SYMBOL(hsiphash_1u32);

/**
 * hsiphash_2u32 - compute 32-bit hsiphash PRF value of 2 u32
 * @first: first u32
 * @second: second u32
 * @key: the hsiphash key
 */
u32 hsiphash_2u32(स्थिर u32 first, स्थिर u32 second, स्थिर hsiphash_key_t *key)
अणु
	HPREAMBLE(8)
	v3 ^= first;
	HSIPROUND;
	v0 ^= first;
	v3 ^= second;
	HSIPROUND;
	v0 ^= second;
	HPOSTAMBLE
पूर्ण
EXPORT_SYMBOL(hsiphash_2u32);

/**
 * hsiphash_3u32 - compute 32-bit hsiphash PRF value of 3 u32
 * @first: first u32
 * @second: second u32
 * @third: third u32
 * @key: the hsiphash key
 */
u32 hsiphash_3u32(स्थिर u32 first, स्थिर u32 second, स्थिर u32 third,
		  स्थिर hsiphash_key_t *key)
अणु
	HPREAMBLE(12)
	v3 ^= first;
	HSIPROUND;
	v0 ^= first;
	v3 ^= second;
	HSIPROUND;
	v0 ^= second;
	v3 ^= third;
	HSIPROUND;
	v0 ^= third;
	HPOSTAMBLE
पूर्ण
EXPORT_SYMBOL(hsiphash_3u32);

/**
 * hsiphash_4u32 - compute 32-bit hsiphash PRF value of 4 u32
 * @first: first u32
 * @second: second u32
 * @third: third u32
 * @क्रमth: क्रमth u32
 * @key: the hsiphash key
 */
u32 hsiphash_4u32(स्थिर u32 first, स्थिर u32 second, स्थिर u32 third,
		  स्थिर u32 क्रमth, स्थिर hsiphash_key_t *key)
अणु
	HPREAMBLE(16)
	v3 ^= first;
	HSIPROUND;
	v0 ^= first;
	v3 ^= second;
	HSIPROUND;
	v0 ^= second;
	v3 ^= third;
	HSIPROUND;
	v0 ^= third;
	v3 ^= क्रमth;
	HSIPROUND;
	v0 ^= क्रमth;
	HPOSTAMBLE
पूर्ण
EXPORT_SYMBOL(hsiphash_4u32);
#पूर्ण_अगर
