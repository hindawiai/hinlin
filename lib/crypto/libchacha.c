<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * The ChaCha stream cipher (RFC7539)
 *
 * Copyright (C) 2015 Martin Willi
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>

#समावेश <crypto/algapi.h> // क्रम crypto_xor_cpy
#समावेश <crypto/chacha.h>

व्योम chacha_crypt_generic(u32 *state, u8 *dst, स्थिर u8 *src,
			  अचिन्हित पूर्णांक bytes, पूर्णांक nrounds)
अणु
	/* aligned to potentially speed up crypto_xor() */
	u8 stream[CHACHA_BLOCK_SIZE] __aligned(माप(दीर्घ));

	जबतक (bytes >= CHACHA_BLOCK_SIZE) अणु
		chacha_block_generic(state, stream, nrounds);
		crypto_xor_cpy(dst, src, stream, CHACHA_BLOCK_SIZE);
		bytes -= CHACHA_BLOCK_SIZE;
		dst += CHACHA_BLOCK_SIZE;
		src += CHACHA_BLOCK_SIZE;
	पूर्ण
	अगर (bytes) अणु
		chacha_block_generic(state, stream, nrounds);
		crypto_xor_cpy(dst, src, stream, bytes);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(chacha_crypt_generic);

MODULE_LICENSE("GPL");
