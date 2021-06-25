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

#अगर_अघोषित _LINUX_SIPHASH_H
#घोषणा _LINUX_SIPHASH_H

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>

#घोषणा SIPHASH_ALIGNMENT __alignof__(u64)
प्रकार काष्ठा अणु
	u64 key[2];
पूर्ण siphash_key_t;

अटल अंतरभूत bool siphash_key_is_zero(स्थिर siphash_key_t *key)
अणु
	वापस !(key->key[0] | key->key[1]);
पूर्ण

u64 __siphash_aligned(स्थिर व्योम *data, माप_प्रकार len, स्थिर siphash_key_t *key);
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
u64 __siphash_unaligned(स्थिर व्योम *data, माप_प्रकार len, स्थिर siphash_key_t *key);
#पूर्ण_अगर

u64 siphash_1u64(स्थिर u64 a, स्थिर siphash_key_t *key);
u64 siphash_2u64(स्थिर u64 a, स्थिर u64 b, स्थिर siphash_key_t *key);
u64 siphash_3u64(स्थिर u64 a, स्थिर u64 b, स्थिर u64 c,
		 स्थिर siphash_key_t *key);
u64 siphash_4u64(स्थिर u64 a, स्थिर u64 b, स्थिर u64 c, स्थिर u64 d,
		 स्थिर siphash_key_t *key);
u64 siphash_1u32(स्थिर u32 a, स्थिर siphash_key_t *key);
u64 siphash_3u32(स्थिर u32 a, स्थिर u32 b, स्थिर u32 c,
		 स्थिर siphash_key_t *key);

अटल अंतरभूत u64 siphash_2u32(स्थिर u32 a, स्थिर u32 b,
			       स्थिर siphash_key_t *key)
अणु
	वापस siphash_1u64((u64)b << 32 | a, key);
पूर्ण
अटल अंतरभूत u64 siphash_4u32(स्थिर u32 a, स्थिर u32 b, स्थिर u32 c,
			       स्थिर u32 d, स्थिर siphash_key_t *key)
अणु
	वापस siphash_2u64((u64)b << 32 | a, (u64)d << 32 | c, key);
पूर्ण


अटल अंतरभूत u64 ___siphash_aligned(स्थिर __le64 *data, माप_प्रकार len,
				     स्थिर siphash_key_t *key)
अणु
	अगर (__builtin_स्थिरant_p(len) && len == 4)
		वापस siphash_1u32(le32_to_cpup((स्थिर __le32 *)data), key);
	अगर (__builtin_स्थिरant_p(len) && len == 8)
		वापस siphash_1u64(le64_to_cpu(data[0]), key);
	अगर (__builtin_स्थिरant_p(len) && len == 16)
		वापस siphash_2u64(le64_to_cpu(data[0]), le64_to_cpu(data[1]),
				    key);
	अगर (__builtin_स्थिरant_p(len) && len == 24)
		वापस siphash_3u64(le64_to_cpu(data[0]), le64_to_cpu(data[1]),
				    le64_to_cpu(data[2]), key);
	अगर (__builtin_स्थिरant_p(len) && len == 32)
		वापस siphash_4u64(le64_to_cpu(data[0]), le64_to_cpu(data[1]),
				    le64_to_cpu(data[2]), le64_to_cpu(data[3]),
				    key);
	वापस __siphash_aligned(data, len, key);
पूर्ण

/**
 * siphash - compute 64-bit siphash PRF value
 * @data: buffer to hash
 * @size: size of @data
 * @key: the siphash key
 */
अटल अंतरभूत u64 siphash(स्थिर व्योम *data, माप_प्रकार len,
			  स्थिर siphash_key_t *key)
अणु
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)data, SIPHASH_ALIGNMENT))
		वापस __siphash_unaligned(data, len, key);
#पूर्ण_अगर
	वापस ___siphash_aligned(data, len, key);
पूर्ण

#घोषणा HSIPHASH_ALIGNMENT __alignof__(अचिन्हित दीर्घ)
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ key[2];
पूर्ण hsiphash_key_t;

u32 __hsiphash_aligned(स्थिर व्योम *data, माप_प्रकार len,
		       स्थिर hsiphash_key_t *key);
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
u32 __hsiphash_unaligned(स्थिर व्योम *data, माप_प्रकार len,
			 स्थिर hsiphash_key_t *key);
#पूर्ण_अगर

u32 hsiphash_1u32(स्थिर u32 a, स्थिर hsiphash_key_t *key);
u32 hsiphash_2u32(स्थिर u32 a, स्थिर u32 b, स्थिर hsiphash_key_t *key);
u32 hsiphash_3u32(स्थिर u32 a, स्थिर u32 b, स्थिर u32 c,
		  स्थिर hsiphash_key_t *key);
u32 hsiphash_4u32(स्थिर u32 a, स्थिर u32 b, स्थिर u32 c, स्थिर u32 d,
		  स्थिर hsiphash_key_t *key);

अटल अंतरभूत u32 ___hsiphash_aligned(स्थिर __le32 *data, माप_प्रकार len,
				      स्थिर hsiphash_key_t *key)
अणु
	अगर (__builtin_स्थिरant_p(len) && len == 4)
		वापस hsiphash_1u32(le32_to_cpu(data[0]), key);
	अगर (__builtin_स्थिरant_p(len) && len == 8)
		वापस hsiphash_2u32(le32_to_cpu(data[0]), le32_to_cpu(data[1]),
				     key);
	अगर (__builtin_स्थिरant_p(len) && len == 12)
		वापस hsiphash_3u32(le32_to_cpu(data[0]), le32_to_cpu(data[1]),
				     le32_to_cpu(data[2]), key);
	अगर (__builtin_स्थिरant_p(len) && len == 16)
		वापस hsiphash_4u32(le32_to_cpu(data[0]), le32_to_cpu(data[1]),
				     le32_to_cpu(data[2]), le32_to_cpu(data[3]),
				     key);
	वापस __hsiphash_aligned(data, len, key);
पूर्ण

/**
 * hsiphash - compute 32-bit hsiphash PRF value
 * @data: buffer to hash
 * @size: size of @data
 * @key: the hsiphash key
 */
अटल अंतरभूत u32 hsiphash(स्थिर व्योम *data, माप_प्रकार len,
			   स्थिर hsiphash_key_t *key)
अणु
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)data, HSIPHASH_ALIGNMENT))
		वापस __hsiphash_unaligned(data, len, key);
#पूर्ण_अगर
	वापस ___hsiphash_aligned(data, len, key);
पूर्ण

#पूर्ण_अगर /* _LINUX_SIPHASH_H */
