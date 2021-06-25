<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AMD Cryptographic Coprocessor (CCP) crypto API support
 *
 * Copyright (C) 2013,2017 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 */

#अगर_अघोषित __CCP_CRYPTO_H__
#घोषणा __CCP_CRYPTO_H__

#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/ccp.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/skcipher.h>
#समावेश <crypto/पूर्णांकernal/rsa.h>

/* We want the module name in front of our messages */
#अघोषित pr_fmt
#घोषणा	pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#घोषणा	CCP_LOG_LEVEL	KERN_INFO

#घोषणा CCP_CRA_PRIORITY	300

काष्ठा ccp_crypto_skcipher_alg अणु
	काष्ठा list_head entry;

	u32 mode;

	काष्ठा skcipher_alg alg;
पूर्ण;

काष्ठा ccp_crypto_aead अणु
	काष्ठा list_head entry;

	u32 mode;

	काष्ठा aead_alg alg;
पूर्ण;

काष्ठा ccp_crypto_ahash_alg अणु
	काष्ठा list_head entry;

	स्थिर __be32 *init;
	u32 type;
	u32 mode;

	/* Child algorithm used क्रम HMAC, CMAC, etc */
	अक्षर child_alg[CRYPTO_MAX_ALG_NAME];

	काष्ठा ahash_alg alg;
पूर्ण;

काष्ठा ccp_crypto_akcipher_alg अणु
	काष्ठा list_head entry;

	काष्ठा akcipher_alg alg;
पूर्ण;

अटल अंतरभूत काष्ठा ccp_crypto_skcipher_alg *
	ccp_crypto_skcipher_alg(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);

	वापस container_of(alg, काष्ठा ccp_crypto_skcipher_alg, alg);
पूर्ण

अटल अंतरभूत काष्ठा ccp_crypto_ahash_alg *
	ccp_crypto_ahash_alg(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_alg *alg = tfm->__crt_alg;
	काष्ठा ahash_alg *ahash_alg;

	ahash_alg = container_of(alg, काष्ठा ahash_alg, halg.base);

	वापस container_of(ahash_alg, काष्ठा ccp_crypto_ahash_alg, alg);
पूर्ण

/***** AES related defines *****/
काष्ठा ccp_aes_ctx अणु
	/* Fallback cipher क्रम XTS with unsupported unit sizes */
	काष्ठा crypto_skcipher *tfm_skcipher;

	क्रमागत ccp_engine engine;
	क्रमागत ccp_aes_type type;
	क्रमागत ccp_aes_mode mode;

	काष्ठा scatterlist key_sg;
	अचिन्हित पूर्णांक key_len;
	u8 key[AES_MAX_KEY_SIZE * 2];

	u8 nonce[CTR_RFC3686_NONCE_SIZE];

	/* CMAC key काष्ठाures */
	काष्ठा scatterlist k1_sg;
	काष्ठा scatterlist k2_sg;
	अचिन्हित पूर्णांक kn_len;
	u8 k1[AES_BLOCK_SIZE];
	u8 k2[AES_BLOCK_SIZE];
पूर्ण;

काष्ठा ccp_aes_req_ctx अणु
	काष्ठा scatterlist iv_sg;
	u8 iv[AES_BLOCK_SIZE];

	काष्ठा scatterlist tag_sg;
	u8 tag[AES_BLOCK_SIZE];

	/* Fields used क्रम RFC3686 requests */
	u8 *rfc3686_info;
	u8 rfc3686_iv[AES_BLOCK_SIZE];

	काष्ठा ccp_cmd cmd;

	काष्ठा skcipher_request fallback_req;	// keep at the end
पूर्ण;

काष्ठा ccp_aes_cmac_req_ctx अणु
	अचिन्हित पूर्णांक null_msg;
	अचिन्हित पूर्णांक final;

	काष्ठा scatterlist *src;
	अचिन्हित पूर्णांक nbytes;

	u64 hash_cnt;
	अचिन्हित पूर्णांक hash_rem;

	काष्ठा sg_table data_sg;

	काष्ठा scatterlist iv_sg;
	u8 iv[AES_BLOCK_SIZE];

	काष्ठा scatterlist buf_sg;
	अचिन्हित पूर्णांक buf_count;
	u8 buf[AES_BLOCK_SIZE];

	काष्ठा scatterlist pad_sg;
	अचिन्हित पूर्णांक pad_count;
	u8 pad[AES_BLOCK_SIZE];

	काष्ठा ccp_cmd cmd;
पूर्ण;

काष्ठा ccp_aes_cmac_exp_ctx अणु
	अचिन्हित पूर्णांक null_msg;

	u8 iv[AES_BLOCK_SIZE];

	अचिन्हित पूर्णांक buf_count;
	u8 buf[AES_BLOCK_SIZE];
पूर्ण;

/***** 3DES related defines *****/
काष्ठा ccp_des3_ctx अणु
	क्रमागत ccp_engine engine;
	क्रमागत ccp_des3_type type;
	क्रमागत ccp_des3_mode mode;

	काष्ठा scatterlist key_sg;
	अचिन्हित पूर्णांक key_len;
	u8 key[AES_MAX_KEY_SIZE];
पूर्ण;

काष्ठा ccp_des3_req_ctx अणु
	काष्ठा scatterlist iv_sg;
	u8 iv[AES_BLOCK_SIZE];

	काष्ठा ccp_cmd cmd;
पूर्ण;

/* SHA-related defines
 * These values must be large enough to accommodate any variant
 */
#घोषणा MAX_SHA_CONTEXT_SIZE	SHA512_DIGEST_SIZE
#घोषणा MAX_SHA_BLOCK_SIZE	SHA512_BLOCK_SIZE

काष्ठा ccp_sha_ctx अणु
	काष्ठा scatterlist opad_sg;
	अचिन्हित पूर्णांक opad_count;

	अचिन्हित पूर्णांक key_len;
	u8 key[MAX_SHA_BLOCK_SIZE];
	u8 ipad[MAX_SHA_BLOCK_SIZE];
	u8 opad[MAX_SHA_BLOCK_SIZE];
	काष्ठा crypto_shash *hmac_tfm;
पूर्ण;

काष्ठा ccp_sha_req_ctx अणु
	क्रमागत ccp_sha_type type;

	u64 msg_bits;

	अचिन्हित पूर्णांक first;
	अचिन्हित पूर्णांक final;

	काष्ठा scatterlist *src;
	अचिन्हित पूर्णांक nbytes;

	u64 hash_cnt;
	अचिन्हित पूर्णांक hash_rem;

	काष्ठा sg_table data_sg;

	काष्ठा scatterlist ctx_sg;
	u8 ctx[MAX_SHA_CONTEXT_SIZE];

	काष्ठा scatterlist buf_sg;
	अचिन्हित पूर्णांक buf_count;
	u8 buf[MAX_SHA_BLOCK_SIZE];

	/* CCP driver command */
	काष्ठा ccp_cmd cmd;
पूर्ण;

काष्ठा ccp_sha_exp_ctx अणु
	क्रमागत ccp_sha_type type;

	u64 msg_bits;

	अचिन्हित पूर्णांक first;

	u8 ctx[MAX_SHA_CONTEXT_SIZE];

	अचिन्हित पूर्णांक buf_count;
	u8 buf[MAX_SHA_BLOCK_SIZE];
पूर्ण;

/***** RSA related defines *****/

काष्ठा ccp_rsa_ctx अणु
	अचिन्हित पूर्णांक key_len; /* in bits */
	काष्ठा scatterlist e_sg;
	u8 *e_buf;
	अचिन्हित पूर्णांक e_len;
	काष्ठा scatterlist n_sg;
	u8 *n_buf;
	अचिन्हित पूर्णांक n_len;
	काष्ठा scatterlist d_sg;
	u8 *d_buf;
	अचिन्हित पूर्णांक d_len;
पूर्ण;

काष्ठा ccp_rsa_req_ctx अणु
	काष्ठा ccp_cmd cmd;
पूर्ण;

#घोषणा	CCP_RSA_MAXMOD	(4 * 1024 / 8)
#घोषणा	CCP5_RSA_MAXMOD	(16 * 1024 / 8)

/***** Common Context Structure *****/
काष्ठा ccp_ctx अणु
	पूर्णांक (*complete)(काष्ठा crypto_async_request *req, पूर्णांक ret);

	जोड़ अणु
		काष्ठा ccp_aes_ctx aes;
		काष्ठा ccp_rsa_ctx rsa;
		काष्ठा ccp_sha_ctx sha;
		काष्ठा ccp_des3_ctx des3;
	पूर्ण u;
पूर्ण;

पूर्णांक ccp_crypto_enqueue_request(काष्ठा crypto_async_request *req,
			       काष्ठा ccp_cmd *cmd);
काष्ठा scatterlist *ccp_crypto_sg_table_add(काष्ठा sg_table *table,
					    काष्ठा scatterlist *sg_add);

पूर्णांक ccp_रेजिस्टर_aes_algs(काष्ठा list_head *head);
पूर्णांक ccp_रेजिस्टर_aes_cmac_algs(काष्ठा list_head *head);
पूर्णांक ccp_रेजिस्टर_aes_xts_algs(काष्ठा list_head *head);
पूर्णांक ccp_रेजिस्टर_aes_aeads(काष्ठा list_head *head);
पूर्णांक ccp_रेजिस्टर_sha_algs(काष्ठा list_head *head);
पूर्णांक ccp_रेजिस्टर_des3_algs(काष्ठा list_head *head);
पूर्णांक ccp_रेजिस्टर_rsa_algs(काष्ठा list_head *head);

#पूर्ण_अगर
