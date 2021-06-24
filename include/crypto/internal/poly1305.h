<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common values क्रम the Poly1305 algorithm
 */

#अगर_अघोषित _CRYPTO_INTERNAL_POLY1305_H
#घोषणा _CRYPTO_INTERNAL_POLY1305_H

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/types.h>
#समावेश <crypto/poly1305.h>

/*
 * Poly1305 core functions.  These only accept whole blocks; the caller must
 * handle any needed block buffering and padding.  'hibit' must be 1 क्रम any
 * full blocks, or 0 क्रम the final block अगर it had to be padded.  If 'nonce' is
 * non-शून्य, then it's added at the end to compute the Poly1305 MAC.  Otherwise,
 * only the Nग-almost-ै-universal hash function (not the full MAC) is computed.
 */

व्योम poly1305_core_setkey(काष्ठा poly1305_core_key *key,
			  स्थिर u8 raw_key[POLY1305_BLOCK_SIZE]);
अटल अंतरभूत व्योम poly1305_core_init(काष्ठा poly1305_state *state)
अणु
	*state = (काष्ठा poly1305_state)अणुपूर्ण;
पूर्ण

व्योम poly1305_core_blocks(काष्ठा poly1305_state *state,
			  स्थिर काष्ठा poly1305_core_key *key, स्थिर व्योम *src,
			  अचिन्हित पूर्णांक nblocks, u32 hibit);
व्योम poly1305_core_emit(स्थिर काष्ठा poly1305_state *state, स्थिर u32 nonce[4],
			व्योम *dst);

#पूर्ण_अगर
