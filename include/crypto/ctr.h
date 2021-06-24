<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CTR: Counter mode
 *
 * Copyright (c) 2007 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#अगर_अघोषित _CRYPTO_CTR_H
#घोषणा _CRYPTO_CTR_H

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#घोषणा CTR_RFC3686_NONCE_SIZE 4
#घोषणा CTR_RFC3686_IV_SIZE 8
#घोषणा CTR_RFC3686_BLOCK_SIZE 16

अटल अंतरभूत पूर्णांक crypto_ctr_encrypt_walk(काष्ठा skcipher_request *req,
					  व्योम (*fn)(काष्ठा crypto_skcipher *,
						     स्थिर u8 *, u8 *))
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	पूर्णांक blocksize = crypto_skcipher_chunksize(tfm);
	u8 buf[MAX_CIPHER_BLOCKSIZE];
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

	/* aव्योम पूर्णांकeger भागision due to variable blocksize parameter */
	अगर (WARN_ON_ONCE(!is_घातer_of_2(blocksize)))
		वापस -EINVAL;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक (walk.nbytes > 0) अणु
		u8 *dst = walk.dst.virt.addr;
		u8 *src = walk.src.virt.addr;
		पूर्णांक nbytes = walk.nbytes;
		पूर्णांक tail = 0;

		अगर (nbytes < walk.total) अणु
			tail = walk.nbytes & (blocksize - 1);
			nbytes -= tail;
		पूर्ण

		करो अणु
			पूर्णांक bsize = min(nbytes, blocksize);

			fn(tfm, walk.iv, buf);

			crypto_xor_cpy(dst, src, buf, bsize);
			crypto_inc(walk.iv, blocksize);

			dst += bsize;
			src += bsize;
			nbytes -= bsize;
		पूर्ण जबतक (nbytes > 0);

		err = skcipher_walk_करोne(&walk, tail);
	पूर्ण
	वापस err;
पूर्ण

#पूर्ण_अगर  /* _CRYPTO_CTR_H */
