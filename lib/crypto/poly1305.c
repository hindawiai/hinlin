<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Poly1305 authenticator algorithm, RFC7539
 *
 * Copyright (C) 2015 Martin Willi
 *
 * Based on खुला करोमुख्य code by Andrew Moon and Daniel J. Bernstein.
 */

#समावेश <crypto/पूर्णांकernal/poly1305.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>

व्योम poly1305_init_generic(काष्ठा poly1305_desc_ctx *desc,
			   स्थिर u8 key[POLY1305_KEY_SIZE])
अणु
	poly1305_core_setkey(&desc->core_r, key);
	desc->s[0] = get_unaligned_le32(key + 16);
	desc->s[1] = get_unaligned_le32(key + 20);
	desc->s[2] = get_unaligned_le32(key + 24);
	desc->s[3] = get_unaligned_le32(key + 28);
	poly1305_core_init(&desc->h);
	desc->buflen = 0;
	desc->sset = true;
	desc->rset = 2;
पूर्ण
EXPORT_SYMBOL_GPL(poly1305_init_generic);

व्योम poly1305_update_generic(काष्ठा poly1305_desc_ctx *desc, स्थिर u8 *src,
			     अचिन्हित पूर्णांक nbytes)
अणु
	अचिन्हित पूर्णांक bytes;

	अगर (unlikely(desc->buflen)) अणु
		bytes = min(nbytes, POLY1305_BLOCK_SIZE - desc->buflen);
		स_नकल(desc->buf + desc->buflen, src, bytes);
		src += bytes;
		nbytes -= bytes;
		desc->buflen += bytes;

		अगर (desc->buflen == POLY1305_BLOCK_SIZE) अणु
			poly1305_core_blocks(&desc->h, &desc->core_r, desc->buf,
					     1, 1);
			desc->buflen = 0;
		पूर्ण
	पूर्ण

	अगर (likely(nbytes >= POLY1305_BLOCK_SIZE)) अणु
		poly1305_core_blocks(&desc->h, &desc->core_r, src,
				     nbytes / POLY1305_BLOCK_SIZE, 1);
		src += nbytes - (nbytes % POLY1305_BLOCK_SIZE);
		nbytes %= POLY1305_BLOCK_SIZE;
	पूर्ण

	अगर (unlikely(nbytes)) अणु
		desc->buflen = nbytes;
		स_नकल(desc->buf, src, nbytes);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(poly1305_update_generic);

व्योम poly1305_final_generic(काष्ठा poly1305_desc_ctx *desc, u8 *dst)
अणु
	अगर (unlikely(desc->buflen)) अणु
		desc->buf[desc->buflen++] = 1;
		स_रखो(desc->buf + desc->buflen, 0,
		       POLY1305_BLOCK_SIZE - desc->buflen);
		poly1305_core_blocks(&desc->h, &desc->core_r, desc->buf, 1, 0);
	पूर्ण

	poly1305_core_emit(&desc->h, desc->s, dst);
	*desc = (काष्ठा poly1305_desc_ctx)अणुपूर्ण;
पूर्ण
EXPORT_SYMBOL_GPL(poly1305_final_generic);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Martin Willi <martin@strongswan.org>");
