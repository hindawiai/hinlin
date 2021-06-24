<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 *
 * This is an implementation of the BLAKE2s hash and PRF functions.
 *
 * Inक्रमmation: https://blake2.net/
 *
 */

#समावेश <crypto/पूर्णांकernal/blake2s.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/bug.h>

#अगर IS_ENABLED(CONFIG_CRYPTO_ARCH_HAVE_LIB_BLAKE2S)
#  define blake2s_compress blake2s_compress_arch
#अन्यथा
#  define blake2s_compress blake2s_compress_generic
#पूर्ण_अगर

व्योम blake2s_update(काष्ठा blake2s_state *state, स्थिर u8 *in, माप_प्रकार inlen)
अणु
	__blake2s_update(state, in, inlen, blake2s_compress);
पूर्ण
EXPORT_SYMBOL(blake2s_update);

व्योम blake2s_final(काष्ठा blake2s_state *state, u8 *out)
अणु
	WARN_ON(IS_ENABLED(DEBUG) && !out);
	__blake2s_final(state, out, blake2s_compress);
	memzero_explicit(state, माप(*state));
पूर्ण
EXPORT_SYMBOL(blake2s_final);

व्योम blake2s256_hmac(u8 *out, स्थिर u8 *in, स्थिर u8 *key, स्थिर माप_प्रकार inlen,
		     स्थिर माप_प्रकार keylen)
अणु
	काष्ठा blake2s_state state;
	u8 x_key[BLAKE2S_BLOCK_SIZE] __aligned(__alignof__(u32)) = अणु 0 पूर्ण;
	u8 i_hash[BLAKE2S_HASH_SIZE] __aligned(__alignof__(u32));
	पूर्णांक i;

	अगर (keylen > BLAKE2S_BLOCK_SIZE) अणु
		blake2s_init(&state, BLAKE2S_HASH_SIZE);
		blake2s_update(&state, key, keylen);
		blake2s_final(&state, x_key);
	पूर्ण अन्यथा
		स_नकल(x_key, key, keylen);

	क्रम (i = 0; i < BLAKE2S_BLOCK_SIZE; ++i)
		x_key[i] ^= 0x36;

	blake2s_init(&state, BLAKE2S_HASH_SIZE);
	blake2s_update(&state, x_key, BLAKE2S_BLOCK_SIZE);
	blake2s_update(&state, in, inlen);
	blake2s_final(&state, i_hash);

	क्रम (i = 0; i < BLAKE2S_BLOCK_SIZE; ++i)
		x_key[i] ^= 0x5c ^ 0x36;

	blake2s_init(&state, BLAKE2S_HASH_SIZE);
	blake2s_update(&state, x_key, BLAKE2S_BLOCK_SIZE);
	blake2s_update(&state, i_hash, BLAKE2S_HASH_SIZE);
	blake2s_final(&state, i_hash);

	स_नकल(out, i_hash, BLAKE2S_HASH_SIZE);
	memzero_explicit(x_key, BLAKE2S_BLOCK_SIZE);
	memzero_explicit(i_hash, BLAKE2S_HASH_SIZE);
पूर्ण
EXPORT_SYMBOL(blake2s256_hmac);

अटल पूर्णांक __init mod_init(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_CRYPTO_MANAGER_DISABLE_TESTS) &&
	    WARN_ON(!blake2s_selftest()))
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल व्योम __निकास mod_निकास(व्योम)
अणु
पूर्ण

module_init(mod_init);
module_निकास(mod_निकास);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("BLAKE2s hash function");
MODULE_AUTHOR("Jason A. Donenfeld <Jason@zx2c4.com>");
