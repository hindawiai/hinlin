<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010-2014, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _SHA_H_
#घोषणा _SHA_H_

#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>

#समावेश "common.h"
#समावेश "core.h"

#घोषणा QCE_SHA_MAX_BLOCKSIZE		SHA256_BLOCK_SIZE
#घोषणा QCE_SHA_MAX_DIGESTSIZE		SHA256_DIGEST_SIZE

काष्ठा qce_sha_ctx अणु
	u8 authkey[QCE_SHA_MAX_BLOCKSIZE];
पूर्ण;

/**
 * काष्ठा qce_sha_reqctx - holds निजी ahash objects per request
 * @buf: used during update, import and export
 * @पंचांगpbuf: buffer क्रम पूर्णांकernal use
 * @digest: calculated digest buffer
 * @buflen: length of the buffer
 * @flags: operation flags
 * @src_orig: original request sg list
 * @nbytes_orig: original request number of bytes
 * @src_nents: source number of entries
 * @byte_count: byte count
 * @count: save count in states during update, import and export
 * @first_blk: is it the first block
 * @last_blk: is it the last block
 * @sg: used to chain sg lists
 * @authkey: poपूर्णांकer to auth key in sha ctx
 * @authklen: auth key length
 * @result_sg: scatterlist used क्रम result buffer
 */
काष्ठा qce_sha_reqctx अणु
	u8 buf[QCE_SHA_MAX_BLOCKSIZE];
	u8 पंचांगpbuf[QCE_SHA_MAX_BLOCKSIZE];
	u8 digest[QCE_SHA_MAX_DIGESTSIZE];
	अचिन्हित पूर्णांक buflen;
	अचिन्हित दीर्घ flags;
	काष्ठा scatterlist *src_orig;
	अचिन्हित पूर्णांक nbytes_orig;
	पूर्णांक src_nents;
	__be32 byte_count[2];
	u64 count;
	bool first_blk;
	bool last_blk;
	काष्ठा scatterlist sg[2];
	u8 *authkey;
	अचिन्हित पूर्णांक authklen;
	काष्ठा scatterlist result_sg;
पूर्ण;

अटल अंतरभूत काष्ठा qce_alg_ढाँचा *to_ahash_पंचांगpl(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	काष्ठा ahash_alg *alg = container_of(crypto_hash_alg_common(ahash),
					     काष्ठा ahash_alg, halg);

	वापस container_of(alg, काष्ठा qce_alg_ढाँचा, alg.ahash);
पूर्ण

बाह्य स्थिर काष्ठा qce_algo_ops ahash_ops;

#पूर्ण_अगर /* _SHA_H_ */
