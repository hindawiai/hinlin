<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010-2014, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _CIPHER_H_
#घोषणा _CIPHER_H_

#समावेश "common.h"
#समावेश "core.h"

#घोषणा QCE_MAX_KEY_SIZE	64

काष्ठा qce_cipher_ctx अणु
	u8 enc_key[QCE_MAX_KEY_SIZE];
	अचिन्हित पूर्णांक enc_keylen;
	काष्ठा crypto_skcipher *fallback;
पूर्ण;

/**
 * काष्ठा qce_cipher_reqctx - holds निजी cipher objects per request
 * @flags: operation flags
 * @iv: poपूर्णांकer to the IV
 * @ivsize: IV size
 * @src_nents: source entries
 * @dst_nents: destination entries
 * @result_sg: scatterlist used क्रम result buffer
 * @dst_tbl: destination sg table
 * @dst_sg: destination sg poपूर्णांकer table beginning
 * @src_tbl: source sg table
 * @src_sg: source sg poपूर्णांकer table beginning;
 * @cryptlen: crypto length
 */
काष्ठा qce_cipher_reqctx अणु
	अचिन्हित दीर्घ flags;
	u8 *iv;
	अचिन्हित पूर्णांक ivsize;
	पूर्णांक src_nents;
	पूर्णांक dst_nents;
	काष्ठा scatterlist result_sg;
	काष्ठा sg_table dst_tbl;
	काष्ठा scatterlist *dst_sg;
	काष्ठा scatterlist *src_sg;
	अचिन्हित पूर्णांक cryptlen;
	काष्ठा skcipher_request fallback_req;	// keep at the end
पूर्ण;

अटल अंतरभूत काष्ठा qce_alg_ढाँचा *to_cipher_पंचांगpl(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	वापस container_of(alg, काष्ठा qce_alg_ढाँचा, alg.skcipher);
पूर्ण

बाह्य स्थिर काष्ठा qce_algo_ops skcipher_ops;

#पूर्ण_अगर /* _CIPHER_H_ */
