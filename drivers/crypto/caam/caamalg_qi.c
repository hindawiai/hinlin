<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Freescale FSL CAAM support क्रम crypto API over QI backend.
 * Based on caamalg.c
 *
 * Copyright 2013-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 */

#समावेश "compat.h"
#समावेश "ctrl.h"
#समावेश "regs.h"
#समावेश "intern.h"
#समावेश "desc_constr.h"
#समावेश "error.h"
#समावेश "sg_sw_qm.h"
#समावेश "key_gen.h"
#समावेश "qi.h"
#समावेश "jr.h"
#समावेश "caamalg_desc.h"
#समावेश <crypto/xts.h>
#समावेश <यंत्र/unaligned.h>

/*
 * crypto alg
 */
#घोषणा CAAM_CRA_PRIORITY		2000
/* max key is sum of AES_MAX_KEY_SIZE, max split key size */
#घोषणा CAAM_MAX_KEY_SIZE		(AES_MAX_KEY_SIZE + \
					 SHA512_DIGEST_SIZE * 2)

#घोषणा DESC_MAX_USED_BYTES		(DESC_QI_AEAD_GIVENC_LEN + \
					 CAAM_MAX_KEY_SIZE)
#घोषणा DESC_MAX_USED_LEN		(DESC_MAX_USED_BYTES / CAAM_CMD_SZ)

काष्ठा caam_alg_entry अणु
	पूर्णांक class1_alg_type;
	पूर्णांक class2_alg_type;
	bool rfc3686;
	bool geniv;
	bool nodkp;
पूर्ण;

काष्ठा caam_aead_alg अणु
	काष्ठा aead_alg aead;
	काष्ठा caam_alg_entry caam;
	bool रेजिस्टरed;
पूर्ण;

काष्ठा caam_skcipher_alg अणु
	काष्ठा skcipher_alg skcipher;
	काष्ठा caam_alg_entry caam;
	bool रेजिस्टरed;
पूर्ण;

/*
 * per-session context
 */
काष्ठा caam_ctx अणु
	काष्ठा device *jrdev;
	u32 sh_desc_enc[DESC_MAX_USED_LEN];
	u32 sh_desc_dec[DESC_MAX_USED_LEN];
	u8 key[CAAM_MAX_KEY_SIZE];
	dma_addr_t key_dma;
	क्रमागत dma_data_direction dir;
	काष्ठा alginfo adata;
	काष्ठा alginfo cdata;
	अचिन्हित पूर्णांक authsize;
	काष्ठा device *qidev;
	spinlock_t lock;	/* Protects multiple init of driver context */
	काष्ठा caam_drv_ctx *drv_ctx[NUM_OP];
	bool xts_key_fallback;
	काष्ठा crypto_skcipher *fallback;
पूर्ण;

काष्ठा caam_skcipher_req_ctx अणु
	काष्ठा skcipher_request fallback_req;
पूर्ण;

अटल पूर्णांक aead_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_aead_alg *alg = container_of(crypto_aead_alg(aead),
						 typeof(*alg), aead);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	u32 ctx1_iv_off = 0;
	u32 *nonce = शून्य;
	अचिन्हित पूर्णांक data_len[2];
	u32 inl_mask;
	स्थिर bool ctr_mode = ((ctx->cdata.algtype & OP_ALG_AAI_MASK) ==
			       OP_ALG_AAI_CTR_MOD128);
	स्थिर bool is_rfc3686 = alg->caam.rfc3686;
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(ctx->jrdev->parent);

	अगर (!ctx->cdata.keylen || !ctx->authsize)
		वापस 0;

	/*
	 * AES-CTR needs to load IV in CONTEXT1 reg
	 * at an offset of 128bits (16bytes)
	 * CONTEXT1[255:128] = IV
	 */
	अगर (ctr_mode)
		ctx1_iv_off = 16;

	/*
	 * RFC3686 specअगरic:
	 *	CONTEXT1[255:128] = अणुNONCE, IV, COUNTERपूर्ण
	 */
	अगर (is_rfc3686) अणु
		ctx1_iv_off = 16 + CTR_RFC3686_NONCE_SIZE;
		nonce = (u32 *)((व्योम *)ctx->key + ctx->adata.keylen_pad +
				ctx->cdata.keylen - CTR_RFC3686_NONCE_SIZE);
	पूर्ण

	/*
	 * In हाल |user key| > |derived key|, using DKP<imm,imm> would result
	 * in invalid opcodes (last bytes of user key) in the resulting
	 * descriptor. Use DKP<ptr,imm> instead => both भव and dma key
	 * addresses are needed.
	 */
	ctx->adata.key_virt = ctx->key;
	ctx->adata.key_dma = ctx->key_dma;

	ctx->cdata.key_virt = ctx->key + ctx->adata.keylen_pad;
	ctx->cdata.key_dma = ctx->key_dma + ctx->adata.keylen_pad;

	data_len[0] = ctx->adata.keylen_pad;
	data_len[1] = ctx->cdata.keylen;

	अगर (alg->caam.geniv)
		जाओ skip_enc;

	/* aead_encrypt shared descriptor */
	अगर (desc_अंतरभूत_query(DESC_QI_AEAD_ENC_LEN +
			      (is_rfc3686 ? DESC_AEAD_CTR_RFC3686_LEN : 0),
			      DESC_JOB_IO_LEN, data_len, &inl_mask,
			      ARRAY_SIZE(data_len)) < 0)
		वापस -EINVAL;

	ctx->adata.key_अंतरभूत = !!(inl_mask & 1);
	ctx->cdata.key_अंतरभूत = !!(inl_mask & 2);

	cnstr_shdsc_aead_encap(ctx->sh_desc_enc, &ctx->cdata, &ctx->adata,
			       ivsize, ctx->authsize, is_rfc3686, nonce,
			       ctx1_iv_off, true, ctrlpriv->era);

skip_enc:
	/* aead_decrypt shared descriptor */
	अगर (desc_अंतरभूत_query(DESC_QI_AEAD_DEC_LEN +
			      (is_rfc3686 ? DESC_AEAD_CTR_RFC3686_LEN : 0),
			      DESC_JOB_IO_LEN, data_len, &inl_mask,
			      ARRAY_SIZE(data_len)) < 0)
		वापस -EINVAL;

	ctx->adata.key_अंतरभूत = !!(inl_mask & 1);
	ctx->cdata.key_अंतरभूत = !!(inl_mask & 2);

	cnstr_shdsc_aead_decap(ctx->sh_desc_dec, &ctx->cdata, &ctx->adata,
			       ivsize, ctx->authsize, alg->caam.geniv,
			       is_rfc3686, nonce, ctx1_iv_off, true,
			       ctrlpriv->era);

	अगर (!alg->caam.geniv)
		जाओ skip_givenc;

	/* aead_givencrypt shared descriptor */
	अगर (desc_अंतरभूत_query(DESC_QI_AEAD_GIVENC_LEN +
			      (is_rfc3686 ? DESC_AEAD_CTR_RFC3686_LEN : 0),
			      DESC_JOB_IO_LEN, data_len, &inl_mask,
			      ARRAY_SIZE(data_len)) < 0)
		वापस -EINVAL;

	ctx->adata.key_अंतरभूत = !!(inl_mask & 1);
	ctx->cdata.key_अंतरभूत = !!(inl_mask & 2);

	cnstr_shdsc_aead_givencap(ctx->sh_desc_enc, &ctx->cdata, &ctx->adata,
				  ivsize, ctx->authsize, is_rfc3686, nonce,
				  ctx1_iv_off, true, ctrlpriv->era);

skip_givenc:
	वापस 0;
पूर्ण

अटल पूर्णांक aead_setauthsize(काष्ठा crypto_aead *authenc, अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(authenc);

	ctx->authsize = authsize;
	aead_set_sh_desc(authenc);

	वापस 0;
पूर्ण

अटल पूर्णांक aead_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
		       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(jrdev->parent);
	काष्ठा crypto_authenc_keys keys;
	पूर्णांक ret = 0;

	अगर (crypto_authenc_extractkeys(&keys, key, keylen) != 0)
		जाओ badkey;

	dev_dbg(jrdev, "keylen %d enckeylen %d authkeylen %d\n",
		keys.authkeylen + keys.enckeylen, keys.enckeylen,
		keys.authkeylen);
	prपूर्णांक_hex_dump_debug("key in @" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);

	/*
	 * If DKP is supported, use it in the shared descriptor to generate
	 * the split key.
	 */
	अगर (ctrlpriv->era >= 6) अणु
		ctx->adata.keylen = keys.authkeylen;
		ctx->adata.keylen_pad = split_key_len(ctx->adata.algtype &
						      OP_ALG_ALGSEL_MASK);

		अगर (ctx->adata.keylen_pad + keys.enckeylen > CAAM_MAX_KEY_SIZE)
			जाओ badkey;

		स_नकल(ctx->key, keys.authkey, keys.authkeylen);
		स_नकल(ctx->key + ctx->adata.keylen_pad, keys.enckey,
		       keys.enckeylen);
		dma_sync_single_क्रम_device(jrdev->parent, ctx->key_dma,
					   ctx->adata.keylen_pad +
					   keys.enckeylen, ctx->dir);
		जाओ skip_split_key;
	पूर्ण

	ret = gen_split_key(jrdev, ctx->key, &ctx->adata, keys.authkey,
			    keys.authkeylen, CAAM_MAX_KEY_SIZE -
			    keys.enckeylen);
	अगर (ret)
		जाओ badkey;

	/* postpend encryption key to auth split key */
	स_नकल(ctx->key + ctx->adata.keylen_pad, keys.enckey, keys.enckeylen);
	dma_sync_single_क्रम_device(jrdev->parent, ctx->key_dma,
				   ctx->adata.keylen_pad + keys.enckeylen,
				   ctx->dir);

	prपूर्णांक_hex_dump_debug("ctx.key@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, ctx->key,
			     ctx->adata.keylen_pad + keys.enckeylen, 1);

skip_split_key:
	ctx->cdata.keylen = keys.enckeylen;

	ret = aead_set_sh_desc(aead);
	अगर (ret)
		जाओ badkey;

	/* Now update the driver contexts with the new shared descriptor */
	अगर (ctx->drv_ctx[ENCRYPT]) अणु
		ret = caam_drv_ctx_update(ctx->drv_ctx[ENCRYPT],
					  ctx->sh_desc_enc);
		अगर (ret) अणु
			dev_err(jrdev, "driver enc context update failed\n");
			जाओ badkey;
		पूर्ण
	पूर्ण

	अगर (ctx->drv_ctx[DECRYPT]) अणु
		ret = caam_drv_ctx_update(ctx->drv_ctx[DECRYPT],
					  ctx->sh_desc_dec);
		अगर (ret) अणु
			dev_err(jrdev, "driver dec context update failed\n");
			जाओ badkey;
		पूर्ण
	पूर्ण

	memzero_explicit(&keys, माप(keys));
	वापस ret;
badkey:
	memzero_explicit(&keys, माप(keys));
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक des3_aead_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
			    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_authenc_keys keys;
	पूर्णांक err;

	err = crypto_authenc_extractkeys(&keys, key, keylen);
	अगर (unlikely(err))
		वापस err;

	err = verअगरy_aead_des3_key(aead, keys.enckey, keys.enckeylen) ?:
	      aead_setkey(aead, key, keylen);

	memzero_explicit(&keys, माप(keys));
	वापस err;
पूर्ण

अटल पूर्णांक gcm_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	पूर्णांक rem_bytes = CAAM_DESC_BYTES_MAX - DESC_JOB_IO_LEN -
			ctx->cdata.keylen;

	अगर (!ctx->cdata.keylen || !ctx->authsize)
		वापस 0;

	/*
	 * Job Descriptor and Shared Descriptor
	 * must fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_QI_GCM_ENC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
		ctx->cdata.key_virt = ctx->key;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	cnstr_shdsc_gcm_encap(ctx->sh_desc_enc, &ctx->cdata, ivsize,
			      ctx->authsize, true);

	/*
	 * Job Descriptor and Shared Descriptor
	 * must fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_QI_GCM_DEC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
		ctx->cdata.key_virt = ctx->key;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	cnstr_shdsc_gcm_decap(ctx->sh_desc_dec, &ctx->cdata, ivsize,
			      ctx->authsize, true);

	वापस 0;
पूर्ण

अटल पूर्णांक gcm_setauthsize(काष्ठा crypto_aead *authenc, अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(authenc);
	पूर्णांक err;

	err = crypto_gcm_check_authsize(authsize);
	अगर (err)
		वापस err;

	ctx->authsize = authsize;
	gcm_set_sh_desc(authenc);

	वापस 0;
पूर्ण

अटल पूर्णांक gcm_setkey(काष्ठा crypto_aead *aead,
		      स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	पूर्णांक ret;

	ret = aes_check_keylen(keylen);
	अगर (ret)
		वापस ret;

	prपूर्णांक_hex_dump_debug("key in @" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);

	स_नकल(ctx->key, key, keylen);
	dma_sync_single_क्रम_device(jrdev->parent, ctx->key_dma, keylen,
				   ctx->dir);
	ctx->cdata.keylen = keylen;

	ret = gcm_set_sh_desc(aead);
	अगर (ret)
		वापस ret;

	/* Now update the driver contexts with the new shared descriptor */
	अगर (ctx->drv_ctx[ENCRYPT]) अणु
		ret = caam_drv_ctx_update(ctx->drv_ctx[ENCRYPT],
					  ctx->sh_desc_enc);
		अगर (ret) अणु
			dev_err(jrdev, "driver enc context update failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (ctx->drv_ctx[DECRYPT]) अणु
		ret = caam_drv_ctx_update(ctx->drv_ctx[DECRYPT],
					  ctx->sh_desc_dec);
		अगर (ret) अणु
			dev_err(jrdev, "driver dec context update failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rfc4106_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	पूर्णांक rem_bytes = CAAM_DESC_BYTES_MAX - DESC_JOB_IO_LEN -
			ctx->cdata.keylen;

	अगर (!ctx->cdata.keylen || !ctx->authsize)
		वापस 0;

	ctx->cdata.key_virt = ctx->key;

	/*
	 * Job Descriptor and Shared Descriptor
	 * must fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_QI_RFC4106_ENC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	cnstr_shdsc_rfc4106_encap(ctx->sh_desc_enc, &ctx->cdata, ivsize,
				  ctx->authsize, true);

	/*
	 * Job Descriptor and Shared Descriptor
	 * must fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_QI_RFC4106_DEC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	cnstr_shdsc_rfc4106_decap(ctx->sh_desc_dec, &ctx->cdata, ivsize,
				  ctx->authsize, true);

	वापस 0;
पूर्ण

अटल पूर्णांक rfc4106_setauthsize(काष्ठा crypto_aead *authenc,
			       अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(authenc);
	पूर्णांक err;

	err = crypto_rfc4106_check_authsize(authsize);
	अगर (err)
		वापस err;

	ctx->authsize = authsize;
	rfc4106_set_sh_desc(authenc);

	वापस 0;
पूर्ण

अटल पूर्णांक rfc4106_setkey(काष्ठा crypto_aead *aead,
			  स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	पूर्णांक ret;

	ret = aes_check_keylen(keylen - 4);
	अगर (ret)
		वापस ret;

	prपूर्णांक_hex_dump_debug("key in @" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);

	स_नकल(ctx->key, key, keylen);
	/*
	 * The last four bytes of the key material are used as the salt value
	 * in the nonce. Update the AES key length.
	 */
	ctx->cdata.keylen = keylen - 4;
	dma_sync_single_क्रम_device(jrdev->parent, ctx->key_dma,
				   ctx->cdata.keylen, ctx->dir);

	ret = rfc4106_set_sh_desc(aead);
	अगर (ret)
		वापस ret;

	/* Now update the driver contexts with the new shared descriptor */
	अगर (ctx->drv_ctx[ENCRYPT]) अणु
		ret = caam_drv_ctx_update(ctx->drv_ctx[ENCRYPT],
					  ctx->sh_desc_enc);
		अगर (ret) अणु
			dev_err(jrdev, "driver enc context update failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (ctx->drv_ctx[DECRYPT]) अणु
		ret = caam_drv_ctx_update(ctx->drv_ctx[DECRYPT],
					  ctx->sh_desc_dec);
		अगर (ret) अणु
			dev_err(jrdev, "driver dec context update failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rfc4543_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	पूर्णांक rem_bytes = CAAM_DESC_BYTES_MAX - DESC_JOB_IO_LEN -
			ctx->cdata.keylen;

	अगर (!ctx->cdata.keylen || !ctx->authsize)
		वापस 0;

	ctx->cdata.key_virt = ctx->key;

	/*
	 * Job Descriptor and Shared Descriptor
	 * must fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_QI_RFC4543_ENC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	cnstr_shdsc_rfc4543_encap(ctx->sh_desc_enc, &ctx->cdata, ivsize,
				  ctx->authsize, true);

	/*
	 * Job Descriptor and Shared Descriptor
	 * must fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_QI_RFC4543_DEC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	cnstr_shdsc_rfc4543_decap(ctx->sh_desc_dec, &ctx->cdata, ivsize,
				  ctx->authsize, true);

	वापस 0;
पूर्ण

अटल पूर्णांक rfc4543_setauthsize(काष्ठा crypto_aead *authenc,
			       अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(authenc);

	अगर (authsize != 16)
		वापस -EINVAL;

	ctx->authsize = authsize;
	rfc4543_set_sh_desc(authenc);

	वापस 0;
पूर्ण

अटल पूर्णांक rfc4543_setkey(काष्ठा crypto_aead *aead,
			  स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	पूर्णांक ret;

	ret = aes_check_keylen(keylen - 4);
	अगर (ret)
		वापस ret;

	prपूर्णांक_hex_dump_debug("key in @" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);

	स_नकल(ctx->key, key, keylen);
	/*
	 * The last four bytes of the key material are used as the salt value
	 * in the nonce. Update the AES key length.
	 */
	ctx->cdata.keylen = keylen - 4;
	dma_sync_single_क्रम_device(jrdev->parent, ctx->key_dma,
				   ctx->cdata.keylen, ctx->dir);

	ret = rfc4543_set_sh_desc(aead);
	अगर (ret)
		वापस ret;

	/* Now update the driver contexts with the new shared descriptor */
	अगर (ctx->drv_ctx[ENCRYPT]) अणु
		ret = caam_drv_ctx_update(ctx->drv_ctx[ENCRYPT],
					  ctx->sh_desc_enc);
		अगर (ret) अणु
			dev_err(jrdev, "driver enc context update failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (ctx->drv_ctx[DECRYPT]) अणु
		ret = caam_drv_ctx_update(ctx->drv_ctx[DECRYPT],
					  ctx->sh_desc_dec);
		अगर (ret) अणु
			dev_err(jrdev, "driver dec context update failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skcipher_setkey(काष्ठा crypto_skcipher *skcipher, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen, स्थिर u32 ctx1_iv_off)
अणु
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा caam_skcipher_alg *alg =
		container_of(crypto_skcipher_alg(skcipher), typeof(*alg),
			     skcipher);
	काष्ठा device *jrdev = ctx->jrdev;
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);
	स्थिर bool is_rfc3686 = alg->caam.rfc3686;
	पूर्णांक ret = 0;

	prपूर्णांक_hex_dump_debug("key in @" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);

	ctx->cdata.keylen = keylen;
	ctx->cdata.key_virt = key;
	ctx->cdata.key_अंतरभूत = true;

	/* skcipher encrypt, decrypt shared descriptors */
	cnstr_shdsc_skcipher_encap(ctx->sh_desc_enc, &ctx->cdata, ivsize,
				   is_rfc3686, ctx1_iv_off);
	cnstr_shdsc_skcipher_decap(ctx->sh_desc_dec, &ctx->cdata, ivsize,
				   is_rfc3686, ctx1_iv_off);

	/* Now update the driver contexts with the new shared descriptor */
	अगर (ctx->drv_ctx[ENCRYPT]) अणु
		ret = caam_drv_ctx_update(ctx->drv_ctx[ENCRYPT],
					  ctx->sh_desc_enc);
		अगर (ret) अणु
			dev_err(jrdev, "driver enc context update failed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (ctx->drv_ctx[DECRYPT]) अणु
		ret = caam_drv_ctx_update(ctx->drv_ctx[DECRYPT],
					  ctx->sh_desc_dec);
		अगर (ret) अणु
			dev_err(jrdev, "driver dec context update failed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aes_skcipher_setkey(काष्ठा crypto_skcipher *skcipher,
			       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	पूर्णांक err;

	err = aes_check_keylen(keylen);
	अगर (err)
		वापस err;

	वापस skcipher_setkey(skcipher, key, keylen, 0);
पूर्ण

अटल पूर्णांक rfc3686_skcipher_setkey(काष्ठा crypto_skcipher *skcipher,
				   स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	u32 ctx1_iv_off;
	पूर्णांक err;

	/*
	 * RFC3686 specअगरic:
	 *	| CONTEXT1[255:128] = अणुNONCE, IV, COUNTERपूर्ण
	 *	| *key = अणुKEY, NONCEपूर्ण
	 */
	ctx1_iv_off = 16 + CTR_RFC3686_NONCE_SIZE;
	keylen -= CTR_RFC3686_NONCE_SIZE;

	err = aes_check_keylen(keylen);
	अगर (err)
		वापस err;

	वापस skcipher_setkey(skcipher, key, keylen, ctx1_iv_off);
पूर्ण

अटल पूर्णांक ctr_skcipher_setkey(काष्ठा crypto_skcipher *skcipher,
			       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	u32 ctx1_iv_off;
	पूर्णांक err;

	/*
	 * AES-CTR needs to load IV in CONTEXT1 reg
	 * at an offset of 128bits (16bytes)
	 * CONTEXT1[255:128] = IV
	 */
	ctx1_iv_off = 16;

	err = aes_check_keylen(keylen);
	अगर (err)
		वापस err;

	वापस skcipher_setkey(skcipher, key, keylen, ctx1_iv_off);
पूर्ण

अटल पूर्णांक des3_skcipher_setkey(काष्ठा crypto_skcipher *skcipher,
				स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस verअगरy_skcipher_des3_key(skcipher, key) ?:
	       skcipher_setkey(skcipher, key, keylen, 0);
पूर्ण

अटल पूर्णांक des_skcipher_setkey(काष्ठा crypto_skcipher *skcipher,
			       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस verअगरy_skcipher_des_key(skcipher, key) ?:
	       skcipher_setkey(skcipher, key, keylen, 0);
पूर्ण

अटल पूर्णांक xts_skcipher_setkey(काष्ठा crypto_skcipher *skcipher, स्थिर u8 *key,
			       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा device *jrdev = ctx->jrdev;
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(jrdev->parent);
	पूर्णांक ret = 0;
	पूर्णांक err;

	err = xts_verअगरy_key(skcipher, key, keylen);
	अगर (err) अणु
		dev_dbg(jrdev, "key size mismatch\n");
		वापस err;
	पूर्ण

	अगर (keylen != 2 * AES_KEYSIZE_128 && keylen != 2 * AES_KEYSIZE_256)
		ctx->xts_key_fallback = true;

	अगर (ctrlpriv->era <= 8 || ctx->xts_key_fallback) अणु
		err = crypto_skcipher_setkey(ctx->fallback, key, keylen);
		अगर (err)
			वापस err;
	पूर्ण

	ctx->cdata.keylen = keylen;
	ctx->cdata.key_virt = key;
	ctx->cdata.key_अंतरभूत = true;

	/* xts skcipher encrypt, decrypt shared descriptors */
	cnstr_shdsc_xts_skcipher_encap(ctx->sh_desc_enc, &ctx->cdata);
	cnstr_shdsc_xts_skcipher_decap(ctx->sh_desc_dec, &ctx->cdata);

	/* Now update the driver contexts with the new shared descriptor */
	अगर (ctx->drv_ctx[ENCRYPT]) अणु
		ret = caam_drv_ctx_update(ctx->drv_ctx[ENCRYPT],
					  ctx->sh_desc_enc);
		अगर (ret) अणु
			dev_err(jrdev, "driver enc context update failed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (ctx->drv_ctx[DECRYPT]) अणु
		ret = caam_drv_ctx_update(ctx->drv_ctx[DECRYPT],
					  ctx->sh_desc_dec);
		अगर (ret) अणु
			dev_err(jrdev, "driver dec context update failed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * aead_edesc - s/w-extended aead descriptor
 * @src_nents: number of segments in input scatterlist
 * @dst_nents: number of segments in output scatterlist
 * @iv_dma: dma address of iv क्रम checking continuity and link table
 * @qm_sg_bytes: length of dma mapped h/w link table
 * @qm_sg_dma: bus physical mapped address of h/w link table
 * @assoclen: associated data length, in CAAM endianness
 * @assoclen_dma: bus physical mapped address of req->assoclen
 * @drv_req: driver-specअगरic request काष्ठाure
 * @sgt: the h/w link table, followed by IV
 */
काष्ठा aead_edesc अणु
	पूर्णांक src_nents;
	पूर्णांक dst_nents;
	dma_addr_t iv_dma;
	पूर्णांक qm_sg_bytes;
	dma_addr_t qm_sg_dma;
	अचिन्हित पूर्णांक assoclen;
	dma_addr_t assoclen_dma;
	काष्ठा caam_drv_req drv_req;
	काष्ठा qm_sg_entry sgt[];
पूर्ण;

/*
 * skcipher_edesc - s/w-extended skcipher descriptor
 * @src_nents: number of segments in input scatterlist
 * @dst_nents: number of segments in output scatterlist
 * @iv_dma: dma address of iv क्रम checking continuity and link table
 * @qm_sg_bytes: length of dma mapped h/w link table
 * @qm_sg_dma: bus physical mapped address of h/w link table
 * @drv_req: driver-specअगरic request काष्ठाure
 * @sgt: the h/w link table, followed by IV
 */
काष्ठा skcipher_edesc अणु
	पूर्णांक src_nents;
	पूर्णांक dst_nents;
	dma_addr_t iv_dma;
	पूर्णांक qm_sg_bytes;
	dma_addr_t qm_sg_dma;
	काष्ठा caam_drv_req drv_req;
	काष्ठा qm_sg_entry sgt[];
पूर्ण;

अटल काष्ठा caam_drv_ctx *get_drv_ctx(काष्ठा caam_ctx *ctx,
					क्रमागत optype type)
अणु
	/*
	 * This function is called on the fast path with values of 'type'
	 * known at compile समय. Invalid arguments are not expected and
	 * thus no checks are made.
	 */
	काष्ठा caam_drv_ctx *drv_ctx = ctx->drv_ctx[type];
	u32 *desc;

	अगर (unlikely(!drv_ctx)) अणु
		spin_lock(&ctx->lock);

		/* Read again to check अगर some other core init drv_ctx */
		drv_ctx = ctx->drv_ctx[type];
		अगर (!drv_ctx) अणु
			पूर्णांक cpu;

			अगर (type == ENCRYPT)
				desc = ctx->sh_desc_enc;
			अन्यथा /* (type == DECRYPT) */
				desc = ctx->sh_desc_dec;

			cpu = smp_processor_id();
			drv_ctx = caam_drv_ctx_init(ctx->qidev, &cpu, desc);
			अगर (!IS_ERR(drv_ctx))
				drv_ctx->op_type = type;

			ctx->drv_ctx[type] = drv_ctx;
		पूर्ण

		spin_unlock(&ctx->lock);
	पूर्ण

	वापस drv_ctx;
पूर्ण

अटल व्योम caam_unmap(काष्ठा device *dev, काष्ठा scatterlist *src,
		       काष्ठा scatterlist *dst, पूर्णांक src_nents,
		       पूर्णांक dst_nents, dma_addr_t iv_dma, पूर्णांक ivsize,
		       क्रमागत dma_data_direction iv_dir, dma_addr_t qm_sg_dma,
		       पूर्णांक qm_sg_bytes)
अणु
	अगर (dst != src) अणु
		अगर (src_nents)
			dma_unmap_sg(dev, src, src_nents, DMA_TO_DEVICE);
		अगर (dst_nents)
			dma_unmap_sg(dev, dst, dst_nents, DMA_FROM_DEVICE);
	पूर्ण अन्यथा अणु
		dma_unmap_sg(dev, src, src_nents, DMA_BIसूचीECTIONAL);
	पूर्ण

	अगर (iv_dma)
		dma_unmap_single(dev, iv_dma, ivsize, iv_dir);
	अगर (qm_sg_bytes)
		dma_unmap_single(dev, qm_sg_dma, qm_sg_bytes, DMA_TO_DEVICE);
पूर्ण

अटल व्योम aead_unmap(काष्ठा device *dev,
		       काष्ठा aead_edesc *edesc,
		       काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	पूर्णांक ivsize = crypto_aead_ivsize(aead);

	caam_unmap(dev, req->src, req->dst, edesc->src_nents, edesc->dst_nents,
		   edesc->iv_dma, ivsize, DMA_TO_DEVICE, edesc->qm_sg_dma,
		   edesc->qm_sg_bytes);
	dma_unmap_single(dev, edesc->assoclen_dma, 4, DMA_TO_DEVICE);
पूर्ण

अटल व्योम skcipher_unmap(काष्ठा device *dev, काष्ठा skcipher_edesc *edesc,
			   काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);

	caam_unmap(dev, req->src, req->dst, edesc->src_nents, edesc->dst_nents,
		   edesc->iv_dma, ivsize, DMA_BIसूचीECTIONAL, edesc->qm_sg_dma,
		   edesc->qm_sg_bytes);
पूर्ण

अटल व्योम aead_करोne(काष्ठा caam_drv_req *drv_req, u32 status)
अणु
	काष्ठा device *qidev;
	काष्ठा aead_edesc *edesc;
	काष्ठा aead_request *aead_req = drv_req->app_ctx;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(aead_req);
	काष्ठा caam_ctx *caam_ctx = crypto_aead_ctx(aead);
	पूर्णांक ecode = 0;

	qidev = caam_ctx->qidev;

	अगर (unlikely(status))
		ecode = caam_jr_strstatus(qidev, status);

	edesc = container_of(drv_req, typeof(*edesc), drv_req);
	aead_unmap(qidev, edesc, aead_req);

	aead_request_complete(aead_req, ecode);
	qi_cache_मुक्त(edesc);
पूर्ण

/*
 * allocate and map the aead extended descriptor
 */
अटल काष्ठा aead_edesc *aead_edesc_alloc(काष्ठा aead_request *req,
					   bool encrypt)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा caam_aead_alg *alg = container_of(crypto_aead_alg(aead),
						 typeof(*alg), aead);
	काष्ठा device *qidev = ctx->qidev;
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	पूर्णांक src_nents, mapped_src_nents, dst_nents = 0, mapped_dst_nents = 0;
	पूर्णांक src_len, dst_len = 0;
	काष्ठा aead_edesc *edesc;
	dma_addr_t qm_sg_dma, iv_dma = 0;
	पूर्णांक ivsize = 0;
	अचिन्हित पूर्णांक authsize = ctx->authsize;
	पूर्णांक qm_sg_index = 0, qm_sg_ents = 0, qm_sg_bytes;
	पूर्णांक in_len, out_len;
	काष्ठा qm_sg_entry *sg_table, *fd_sgt;
	काष्ठा caam_drv_ctx *drv_ctx;

	drv_ctx = get_drv_ctx(ctx, encrypt ? ENCRYPT : DECRYPT);
	अगर (IS_ERR(drv_ctx))
		वापस (काष्ठा aead_edesc *)drv_ctx;

	/* allocate space क्रम base edesc and hw desc commands, link tables */
	edesc = qi_cache_alloc(GFP_DMA | flags);
	अगर (unlikely(!edesc)) अणु
		dev_err(qidev, "could not allocate extended descriptor\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (likely(req->src == req->dst)) अणु
		src_len = req->assoclen + req->cryptlen +
			  (encrypt ? authsize : 0);

		src_nents = sg_nents_क्रम_len(req->src, src_len);
		अगर (unlikely(src_nents < 0)) अणु
			dev_err(qidev, "Insufficient bytes (%d) in src S/G\n",
				src_len);
			qi_cache_मुक्त(edesc);
			वापस ERR_PTR(src_nents);
		पूर्ण

		mapped_src_nents = dma_map_sg(qidev, req->src, src_nents,
					      DMA_BIसूचीECTIONAL);
		अगर (unlikely(!mapped_src_nents)) अणु
			dev_err(qidev, "unable to map source\n");
			qi_cache_मुक्त(edesc);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण अन्यथा अणु
		src_len = req->assoclen + req->cryptlen;
		dst_len = src_len + (encrypt ? authsize : (-authsize));

		src_nents = sg_nents_क्रम_len(req->src, src_len);
		अगर (unlikely(src_nents < 0)) अणु
			dev_err(qidev, "Insufficient bytes (%d) in src S/G\n",
				src_len);
			qi_cache_मुक्त(edesc);
			वापस ERR_PTR(src_nents);
		पूर्ण

		dst_nents = sg_nents_क्रम_len(req->dst, dst_len);
		अगर (unlikely(dst_nents < 0)) अणु
			dev_err(qidev, "Insufficient bytes (%d) in dst S/G\n",
				dst_len);
			qi_cache_मुक्त(edesc);
			वापस ERR_PTR(dst_nents);
		पूर्ण

		अगर (src_nents) अणु
			mapped_src_nents = dma_map_sg(qidev, req->src,
						      src_nents, DMA_TO_DEVICE);
			अगर (unlikely(!mapped_src_nents)) अणु
				dev_err(qidev, "unable to map source\n");
				qi_cache_मुक्त(edesc);
				वापस ERR_PTR(-ENOMEM);
			पूर्ण
		पूर्ण अन्यथा अणु
			mapped_src_nents = 0;
		पूर्ण

		अगर (dst_nents) अणु
			mapped_dst_nents = dma_map_sg(qidev, req->dst,
						      dst_nents,
						      DMA_FROM_DEVICE);
			अगर (unlikely(!mapped_dst_nents)) अणु
				dev_err(qidev, "unable to map destination\n");
				dma_unmap_sg(qidev, req->src, src_nents,
					     DMA_TO_DEVICE);
				qi_cache_मुक्त(edesc);
				वापस ERR_PTR(-ENOMEM);
			पूर्ण
		पूर्ण अन्यथा अणु
			mapped_dst_nents = 0;
		पूर्ण
	पूर्ण

	अगर ((alg->caam.rfc3686 && encrypt) || !alg->caam.geniv)
		ivsize = crypto_aead_ivsize(aead);

	/*
	 * Create S/G table: req->assoclen, [IV,] req->src [, req->dst].
	 * Input is not contiguous.
	 * HW पढ़ोs 4 S/G entries at a समय; make sure the पढ़ोs करोn't go beyond
	 * the end of the table by allocating more S/G entries. Logic:
	 * अगर (src != dst && output S/G)
	 *      pad output S/G, अगर needed
	 * अन्यथा अगर (src == dst && S/G)
	 *      overlapping S/Gs; pad one of them
	 * अन्यथा अगर (input S/G) ...
	 *      pad input S/G, अगर needed
	 */
	qm_sg_ents = 1 + !!ivsize + mapped_src_nents;
	अगर (mapped_dst_nents > 1)
		qm_sg_ents += pad_sg_nents(mapped_dst_nents);
	अन्यथा अगर ((req->src == req->dst) && (mapped_src_nents > 1))
		qm_sg_ents = max(pad_sg_nents(qm_sg_ents),
				 1 + !!ivsize + pad_sg_nents(mapped_src_nents));
	अन्यथा
		qm_sg_ents = pad_sg_nents(qm_sg_ents);

	sg_table = &edesc->sgt[0];
	qm_sg_bytes = qm_sg_ents * माप(*sg_table);
	अगर (unlikely(दुरत्व(काष्ठा aead_edesc, sgt) + qm_sg_bytes + ivsize >
		     CAAM_QI_MEMCACHE_SIZE)) अणु
		dev_err(qidev, "No space for %d S/G entries and/or %dB IV\n",
			qm_sg_ents, ivsize);
		caam_unmap(qidev, req->src, req->dst, src_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		qi_cache_मुक्त(edesc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (ivsize) अणु
		u8 *iv = (u8 *)(sg_table + qm_sg_ents);

		/* Make sure IV is located in a DMAable area */
		स_नकल(iv, req->iv, ivsize);

		iv_dma = dma_map_single(qidev, iv, ivsize, DMA_TO_DEVICE);
		अगर (dma_mapping_error(qidev, iv_dma)) अणु
			dev_err(qidev, "unable to map IV\n");
			caam_unmap(qidev, req->src, req->dst, src_nents,
				   dst_nents, 0, 0, DMA_NONE, 0, 0);
			qi_cache_मुक्त(edesc);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	edesc->src_nents = src_nents;
	edesc->dst_nents = dst_nents;
	edesc->iv_dma = iv_dma;
	edesc->drv_req.app_ctx = req;
	edesc->drv_req.cbk = aead_करोne;
	edesc->drv_req.drv_ctx = drv_ctx;

	edesc->assoclen = cpu_to_caam32(req->assoclen);
	edesc->assoclen_dma = dma_map_single(qidev, &edesc->assoclen, 4,
					     DMA_TO_DEVICE);
	अगर (dma_mapping_error(qidev, edesc->assoclen_dma)) अणु
		dev_err(qidev, "unable to map assoclen\n");
		caam_unmap(qidev, req->src, req->dst, src_nents, dst_nents,
			   iv_dma, ivsize, DMA_TO_DEVICE, 0, 0);
		qi_cache_मुक्त(edesc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	dma_to_qm_sg_one(sg_table, edesc->assoclen_dma, 4, 0);
	qm_sg_index++;
	अगर (ivsize) अणु
		dma_to_qm_sg_one(sg_table + qm_sg_index, iv_dma, ivsize, 0);
		qm_sg_index++;
	पूर्ण
	sg_to_qm_sg_last(req->src, src_len, sg_table + qm_sg_index, 0);
	qm_sg_index += mapped_src_nents;

	अगर (mapped_dst_nents > 1)
		sg_to_qm_sg_last(req->dst, dst_len, sg_table + qm_sg_index, 0);

	qm_sg_dma = dma_map_single(qidev, sg_table, qm_sg_bytes, DMA_TO_DEVICE);
	अगर (dma_mapping_error(qidev, qm_sg_dma)) अणु
		dev_err(qidev, "unable to map S/G table\n");
		dma_unmap_single(qidev, edesc->assoclen_dma, 4, DMA_TO_DEVICE);
		caam_unmap(qidev, req->src, req->dst, src_nents, dst_nents,
			   iv_dma, ivsize, DMA_TO_DEVICE, 0, 0);
		qi_cache_मुक्त(edesc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	edesc->qm_sg_dma = qm_sg_dma;
	edesc->qm_sg_bytes = qm_sg_bytes;

	out_len = req->assoclen + req->cryptlen +
		  (encrypt ? ctx->authsize : (-ctx->authsize));
	in_len = 4 + ivsize + req->assoclen + req->cryptlen;

	fd_sgt = &edesc->drv_req.fd_sgt[0];
	dma_to_qm_sg_one_last_ext(&fd_sgt[1], qm_sg_dma, in_len, 0);

	अगर (req->dst == req->src) अणु
		अगर (mapped_src_nents == 1)
			dma_to_qm_sg_one(&fd_sgt[0], sg_dma_address(req->src),
					 out_len, 0);
		अन्यथा
			dma_to_qm_sg_one_ext(&fd_sgt[0], qm_sg_dma +
					     (1 + !!ivsize) * माप(*sg_table),
					     out_len, 0);
	पूर्ण अन्यथा अगर (mapped_dst_nents <= 1) अणु
		dma_to_qm_sg_one(&fd_sgt[0], sg_dma_address(req->dst), out_len,
				 0);
	पूर्ण अन्यथा अणु
		dma_to_qm_sg_one_ext(&fd_sgt[0], qm_sg_dma + माप(*sg_table) *
				     qm_sg_index, out_len, 0);
	पूर्ण

	वापस edesc;
पूर्ण

अटल अंतरभूत पूर्णांक aead_crypt(काष्ठा aead_request *req, bool encrypt)
अणु
	काष्ठा aead_edesc *edesc;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	पूर्णांक ret;

	अगर (unlikely(caam_congested))
		वापस -EAGAIN;

	/* allocate extended descriptor */
	edesc = aead_edesc_alloc(req, encrypt);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	/* Create and submit job descriptor */
	ret = caam_qi_enqueue(ctx->qidev, &edesc->drv_req);
	अगर (!ret) अणु
		ret = -EINPROGRESS;
	पूर्ण अन्यथा अणु
		aead_unmap(ctx->qidev, edesc, req);
		qi_cache_मुक्त(edesc);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aead_encrypt(काष्ठा aead_request *req)
अणु
	वापस aead_crypt(req, true);
पूर्ण

अटल पूर्णांक aead_decrypt(काष्ठा aead_request *req)
अणु
	वापस aead_crypt(req, false);
पूर्ण

अटल पूर्णांक ipsec_gcm_encrypt(काष्ठा aead_request *req)
अणु
	वापस crypto_ipsec_check_assoclen(req->assoclen) ? : aead_crypt(req,
					   true);
पूर्ण

अटल पूर्णांक ipsec_gcm_decrypt(काष्ठा aead_request *req)
अणु
	वापस crypto_ipsec_check_assoclen(req->assoclen) ? : aead_crypt(req,
					   false);
पूर्ण

अटल व्योम skcipher_करोne(काष्ठा caam_drv_req *drv_req, u32 status)
अणु
	काष्ठा skcipher_edesc *edesc;
	काष्ठा skcipher_request *req = drv_req->app_ctx;
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा caam_ctx *caam_ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा device *qidev = caam_ctx->qidev;
	पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);
	पूर्णांक ecode = 0;

	dev_dbg(qidev, "%s %d: status 0x%x\n", __func__, __LINE__, status);

	edesc = container_of(drv_req, typeof(*edesc), drv_req);

	अगर (status)
		ecode = caam_jr_strstatus(qidev, status);

	prपूर्णांक_hex_dump_debug("dstiv  @" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, req->iv,
			     edesc->src_nents > 1 ? 100 : ivsize, 1);
	caam_dump_sg("dst    @" __stringअगरy(__LINE__)": ",
		     DUMP_PREFIX_ADDRESS, 16, 4, req->dst,
		     edesc->dst_nents > 1 ? 100 : req->cryptlen, 1);

	skcipher_unmap(qidev, edesc, req);

	/*
	 * The crypto API expects us to set the IV (req->iv) to the last
	 * ciphertext block (CBC mode) or last counter (CTR mode).
	 * This is used e.g. by the CTS mode.
	 */
	अगर (!ecode)
		स_नकल(req->iv, (u8 *)&edesc->sgt[0] + edesc->qm_sg_bytes,
		       ivsize);

	qi_cache_मुक्त(edesc);
	skcipher_request_complete(req, ecode);
पूर्ण

अटल काष्ठा skcipher_edesc *skcipher_edesc_alloc(काष्ठा skcipher_request *req,
						   bool encrypt)
अणु
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा device *qidev = ctx->qidev;
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	पूर्णांक src_nents, mapped_src_nents, dst_nents = 0, mapped_dst_nents = 0;
	काष्ठा skcipher_edesc *edesc;
	dma_addr_t iv_dma;
	u8 *iv;
	पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);
	पूर्णांक dst_sg_idx, qm_sg_ents, qm_sg_bytes;
	काष्ठा qm_sg_entry *sg_table, *fd_sgt;
	काष्ठा caam_drv_ctx *drv_ctx;

	drv_ctx = get_drv_ctx(ctx, encrypt ? ENCRYPT : DECRYPT);
	अगर (IS_ERR(drv_ctx))
		वापस (काष्ठा skcipher_edesc *)drv_ctx;

	src_nents = sg_nents_क्रम_len(req->src, req->cryptlen);
	अगर (unlikely(src_nents < 0)) अणु
		dev_err(qidev, "Insufficient bytes (%d) in src S/G\n",
			req->cryptlen);
		वापस ERR_PTR(src_nents);
	पूर्ण

	अगर (unlikely(req->src != req->dst)) अणु
		dst_nents = sg_nents_क्रम_len(req->dst, req->cryptlen);
		अगर (unlikely(dst_nents < 0)) अणु
			dev_err(qidev, "Insufficient bytes (%d) in dst S/G\n",
				req->cryptlen);
			वापस ERR_PTR(dst_nents);
		पूर्ण

		mapped_src_nents = dma_map_sg(qidev, req->src, src_nents,
					      DMA_TO_DEVICE);
		अगर (unlikely(!mapped_src_nents)) अणु
			dev_err(qidev, "unable to map source\n");
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		mapped_dst_nents = dma_map_sg(qidev, req->dst, dst_nents,
					      DMA_FROM_DEVICE);
		अगर (unlikely(!mapped_dst_nents)) अणु
			dev_err(qidev, "unable to map destination\n");
			dma_unmap_sg(qidev, req->src, src_nents, DMA_TO_DEVICE);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण अन्यथा अणु
		mapped_src_nents = dma_map_sg(qidev, req->src, src_nents,
					      DMA_BIसूचीECTIONAL);
		अगर (unlikely(!mapped_src_nents)) अणु
			dev_err(qidev, "unable to map source\n");
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	qm_sg_ents = 1 + mapped_src_nents;
	dst_sg_idx = qm_sg_ents;

	/*
	 * Input, output HW S/G tables: [IV, src][dst, IV]
	 * IV entries poपूर्णांक to the same buffer
	 * If src == dst, S/G entries are reused (S/G tables overlap)
	 *
	 * HW पढ़ोs 4 S/G entries at a समय; make sure the पढ़ोs करोn't go beyond
	 * the end of the table by allocating more S/G entries.
	 */
	अगर (req->src != req->dst)
		qm_sg_ents += pad_sg_nents(mapped_dst_nents + 1);
	अन्यथा
		qm_sg_ents = 1 + pad_sg_nents(qm_sg_ents);

	qm_sg_bytes = qm_sg_ents * माप(काष्ठा qm_sg_entry);
	अगर (unlikely(दुरत्व(काष्ठा skcipher_edesc, sgt) + qm_sg_bytes +
		     ivsize > CAAM_QI_MEMCACHE_SIZE)) अणु
		dev_err(qidev, "No space for %d S/G entries and/or %dB IV\n",
			qm_sg_ents, ivsize);
		caam_unmap(qidev, req->src, req->dst, src_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* allocate space क्रम base edesc, link tables and IV */
	edesc = qi_cache_alloc(GFP_DMA | flags);
	अगर (unlikely(!edesc)) अणु
		dev_err(qidev, "could not allocate extended descriptor\n");
		caam_unmap(qidev, req->src, req->dst, src_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* Make sure IV is located in a DMAable area */
	sg_table = &edesc->sgt[0];
	iv = (u8 *)(sg_table + qm_sg_ents);
	स_नकल(iv, req->iv, ivsize);

	iv_dma = dma_map_single(qidev, iv, ivsize, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(qidev, iv_dma)) अणु
		dev_err(qidev, "unable to map IV\n");
		caam_unmap(qidev, req->src, req->dst, src_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		qi_cache_मुक्त(edesc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	edesc->src_nents = src_nents;
	edesc->dst_nents = dst_nents;
	edesc->iv_dma = iv_dma;
	edesc->qm_sg_bytes = qm_sg_bytes;
	edesc->drv_req.app_ctx = req;
	edesc->drv_req.cbk = skcipher_करोne;
	edesc->drv_req.drv_ctx = drv_ctx;

	dma_to_qm_sg_one(sg_table, iv_dma, ivsize, 0);
	sg_to_qm_sg(req->src, req->cryptlen, sg_table + 1, 0);

	अगर (req->src != req->dst)
		sg_to_qm_sg(req->dst, req->cryptlen, sg_table + dst_sg_idx, 0);

	dma_to_qm_sg_one(sg_table + dst_sg_idx + mapped_dst_nents, iv_dma,
			 ivsize, 0);

	edesc->qm_sg_dma = dma_map_single(qidev, sg_table, edesc->qm_sg_bytes,
					  DMA_TO_DEVICE);
	अगर (dma_mapping_error(qidev, edesc->qm_sg_dma)) अणु
		dev_err(qidev, "unable to map S/G table\n");
		caam_unmap(qidev, req->src, req->dst, src_nents, dst_nents,
			   iv_dma, ivsize, DMA_BIसूचीECTIONAL, 0, 0);
		qi_cache_मुक्त(edesc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	fd_sgt = &edesc->drv_req.fd_sgt[0];

	dma_to_qm_sg_one_last_ext(&fd_sgt[1], edesc->qm_sg_dma,
				  ivsize + req->cryptlen, 0);

	अगर (req->src == req->dst)
		dma_to_qm_sg_one_ext(&fd_sgt[0], edesc->qm_sg_dma +
				     माप(*sg_table), req->cryptlen + ivsize,
				     0);
	अन्यथा
		dma_to_qm_sg_one_ext(&fd_sgt[0], edesc->qm_sg_dma + dst_sg_idx *
				     माप(*sg_table), req->cryptlen + ivsize,
				     0);

	वापस edesc;
पूर्ण

अटल अंतरभूत bool xts_skcipher_ivsize(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);

	वापस !!get_unaligned((u64 *)(req->iv + (ivsize / 2)));
पूर्ण

अटल अंतरभूत पूर्णांक skcipher_crypt(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा skcipher_edesc *edesc;
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(ctx->jrdev->parent);
	पूर्णांक ret;

	/*
	 * XTS is expected to वापस an error even क्रम input length = 0
	 * Note that the हाल input length < block size will be caught during
	 * HW offloading and वापस an error.
	 */
	अगर (!req->cryptlen && !ctx->fallback)
		वापस 0;

	अगर (ctx->fallback && ((ctrlpriv->era <= 8 && xts_skcipher_ivsize(req)) ||
			      ctx->xts_key_fallback)) अणु
		काष्ठा caam_skcipher_req_ctx *rctx = skcipher_request_ctx(req);

		skcipher_request_set_tfm(&rctx->fallback_req, ctx->fallback);
		skcipher_request_set_callback(&rctx->fallback_req,
					      req->base.flags,
					      req->base.complete,
					      req->base.data);
		skcipher_request_set_crypt(&rctx->fallback_req, req->src,
					   req->dst, req->cryptlen, req->iv);

		वापस encrypt ? crypto_skcipher_encrypt(&rctx->fallback_req) :
				 crypto_skcipher_decrypt(&rctx->fallback_req);
	पूर्ण

	अगर (unlikely(caam_congested))
		वापस -EAGAIN;

	/* allocate extended descriptor */
	edesc = skcipher_edesc_alloc(req, encrypt);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	ret = caam_qi_enqueue(ctx->qidev, &edesc->drv_req);
	अगर (!ret) अणु
		ret = -EINPROGRESS;
	पूर्ण अन्यथा अणु
		skcipher_unmap(ctx->qidev, edesc, req);
		qi_cache_मुक्त(edesc);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक skcipher_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस skcipher_crypt(req, true);
पूर्ण

अटल पूर्णांक skcipher_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस skcipher_crypt(req, false);
पूर्ण

अटल काष्ठा caam_skcipher_alg driver_algs[] = अणु
	अणु
		.skcipher = अणु
			.base = अणु
				.cra_name = "cbc(aes)",
				.cra_driver_name = "cbc-aes-caam-qi",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aes_skcipher_setkey,
			.encrypt = skcipher_encrypt,
			.decrypt = skcipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
		पूर्ण,
		.caam.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CBC,
	पूर्ण,
	अणु
		.skcipher = अणु
			.base = अणु
				.cra_name = "cbc(des3_ede)",
				.cra_driver_name = "cbc-3des-caam-qi",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_skcipher_setkey,
			.encrypt = skcipher_encrypt,
			.decrypt = skcipher_decrypt,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = DES3_EDE_BLOCK_SIZE,
		पूर्ण,
		.caam.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_CBC,
	पूर्ण,
	अणु
		.skcipher = अणु
			.base = अणु
				.cra_name = "cbc(des)",
				.cra_driver_name = "cbc-des-caam-qi",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = des_skcipher_setkey,
			.encrypt = skcipher_encrypt,
			.decrypt = skcipher_decrypt,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = DES_BLOCK_SIZE,
		पूर्ण,
		.caam.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_CBC,
	पूर्ण,
	अणु
		.skcipher = अणु
			.base = अणु
				.cra_name = "ctr(aes)",
				.cra_driver_name = "ctr-aes-caam-qi",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = ctr_skcipher_setkey,
			.encrypt = skcipher_encrypt,
			.decrypt = skcipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			.chunksize = AES_BLOCK_SIZE,
		पूर्ण,
		.caam.class1_alg_type = OP_ALG_ALGSEL_AES |
					OP_ALG_AAI_CTR_MOD128,
	पूर्ण,
	अणु
		.skcipher = अणु
			.base = अणु
				.cra_name = "rfc3686(ctr(aes))",
				.cra_driver_name = "rfc3686-ctr-aes-caam-qi",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = rfc3686_skcipher_setkey,
			.encrypt = skcipher_encrypt,
			.decrypt = skcipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE +
				       CTR_RFC3686_NONCE_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE +
				       CTR_RFC3686_NONCE_SIZE,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.chunksize = AES_BLOCK_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES |
					   OP_ALG_AAI_CTR_MOD128,
			.rfc3686 = true,
		पूर्ण,
	पूर्ण,
	अणु
		.skcipher = अणु
			.base = अणु
				.cra_name = "xts(aes)",
				.cra_driver_name = "xts-aes-caam-qi",
				.cra_flags = CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = xts_skcipher_setkey,
			.encrypt = skcipher_encrypt,
			.decrypt = skcipher_decrypt,
			.min_keysize = 2 * AES_MIN_KEY_SIZE,
			.max_keysize = 2 * AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
		पूर्ण,
		.caam.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_XTS,
	पूर्ण,
पूर्ण;

अटल काष्ठा caam_aead_alg driver_aeads[] = अणु
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "rfc4106(gcm(aes))",
				.cra_driver_name = "rfc4106-gcm-aes-caam-qi",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = rfc4106_setkey,
			.setauthsize = rfc4106_setauthsize,
			.encrypt = ipsec_gcm_encrypt,
			.decrypt = ipsec_gcm_decrypt,
			.ivsize = 8,
			.maxauthsize = AES_BLOCK_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_GCM,
			.nodkp = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "rfc4543(gcm(aes))",
				.cra_driver_name = "rfc4543-gcm-aes-caam-qi",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = rfc4543_setkey,
			.setauthsize = rfc4543_setauthsize,
			.encrypt = ipsec_gcm_encrypt,
			.decrypt = ipsec_gcm_decrypt,
			.ivsize = 8,
			.maxauthsize = AES_BLOCK_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_GCM,
			.nodkp = true,
		पूर्ण,
	पूर्ण,
	/* Galois Counter Mode */
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "gcm(aes)",
				.cra_driver_name = "gcm-aes-caam-qi",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = gcm_setkey,
			.setauthsize = gcm_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = 12,
			.maxauthsize = AES_BLOCK_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_GCM,
			.nodkp = true,
		पूर्ण
	पूर्ण,
	/* single-pass ipsec_esp descriptor */
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(md5),cbc(aes))",
				.cra_driver_name = "authenc-hmac-md5-"
						   "cbc-aes-caam-qi",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_MD5 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(md5),"
					    "cbc(aes)))",
				.cra_driver_name = "echainiv-authenc-hmac-md5-"
						   "cbc-aes-caam-qi",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_MD5 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha1-"
						   "cbc-aes-caam-qi",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA1 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha1),"
					    "cbc(aes)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha1-cbc-aes-caam-qi",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA1 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha224),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha224-"
						   "cbc-aes-caam-qi",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA224 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha224),"
					    "cbc(aes)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha224-cbc-aes-caam-qi",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA224 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha256),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha256-"
						   "cbc-aes-caam-qi",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA256 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha256),"
					    "cbc(aes)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha256-cbc-aes-"
						   "caam-qi",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA256 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha384),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha384-"
						   "cbc-aes-caam-qi",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA384 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha384),"
					    "cbc(aes)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha384-cbc-aes-"
						   "caam-qi",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA384 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha512),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha512-"
						   "cbc-aes-caam-qi",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA512 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha512),"
					    "cbc(aes)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha512-cbc-aes-"
						   "caam-qi",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA512 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(md5),cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-md5-"
						   "cbc-des3_ede-caam-qi",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_MD5 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(md5),"
					    "cbc(des3_ede)))",
				.cra_driver_name = "echainiv-authenc-hmac-md5-"
						   "cbc-des3_ede-caam-qi",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_MD5 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha1-"
						   "cbc-des3_ede-caam-qi",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA1 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha1),"
					    "cbc(des3_ede)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha1-"
						   "cbc-des3_ede-caam-qi",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA1 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha224),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha224-"
						   "cbc-des3_ede-caam-qi",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA224 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha224),"
					    "cbc(des3_ede)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha224-"
						   "cbc-des3_ede-caam-qi",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA224 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha256),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha256-"
						   "cbc-des3_ede-caam-qi",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA256 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha256),"
					    "cbc(des3_ede)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha256-"
						   "cbc-des3_ede-caam-qi",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA256 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha384),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha384-"
						   "cbc-des3_ede-caam-qi",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA384 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha384),"
					    "cbc(des3_ede)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha384-"
						   "cbc-des3_ede-caam-qi",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA384 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha512),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha512-"
						   "cbc-des3_ede-caam-qi",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA512 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha512),"
					    "cbc(des3_ede)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha512-"
						   "cbc-des3_ede-caam-qi",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA512 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(md5),cbc(des))",
				.cra_driver_name = "authenc-hmac-md5-"
						   "cbc-des-caam-qi",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES_BLOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_MD5 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(md5),"
					    "cbc(des)))",
				.cra_driver_name = "echainiv-authenc-hmac-md5-"
						   "cbc-des-caam-qi",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES_BLOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_MD5 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),cbc(des))",
				.cra_driver_name = "authenc-hmac-sha1-"
						   "cbc-des-caam-qi",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA1 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha1),"
					    "cbc(des)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha1-cbc-des-caam-qi",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA1 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha224),cbc(des))",
				.cra_driver_name = "authenc-hmac-sha224-"
						   "cbc-des-caam-qi",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES_BLOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA224 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha224),"
					    "cbc(des)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha224-cbc-des-"
						   "caam-qi",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES_BLOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA224 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha256),cbc(des))",
				.cra_driver_name = "authenc-hmac-sha256-"
						   "cbc-des-caam-qi",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA256 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha256),"
					    "cbc(des)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha256-cbc-des-"
						   "caam-qi",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA256 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha384),cbc(des))",
				.cra_driver_name = "authenc-hmac-sha384-"
						   "cbc-des-caam-qi",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES_BLOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA384 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha384),"
					    "cbc(des)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha384-cbc-des-"
						   "caam-qi",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES_BLOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA384 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha512),cbc(des))",
				.cra_driver_name = "authenc-hmac-sha512-"
						   "cbc-des-caam-qi",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES_BLOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA512 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha512),"
					    "cbc(des)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha512-cbc-des-"
						   "caam-qi",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = DES_BLOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_CBC,
			.class2_alg_type = OP_ALG_ALGSEL_SHA512 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.geniv = true,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल पूर्णांक caam_init_common(काष्ठा caam_ctx *ctx, काष्ठा caam_alg_entry *caam,
			    bool uses_dkp)
अणु
	काष्ठा caam_drv_निजी *priv;
	काष्ठा device *dev;

	/*
	 * distribute tfms across job rings to ensure in-order
	 * crypto request processing per tfm
	 */
	ctx->jrdev = caam_jr_alloc();
	अगर (IS_ERR(ctx->jrdev)) अणु
		pr_err("Job Ring Device allocation for transform failed\n");
		वापस PTR_ERR(ctx->jrdev);
	पूर्ण

	dev = ctx->jrdev->parent;
	priv = dev_get_drvdata(dev);
	अगर (priv->era >= 6 && uses_dkp)
		ctx->dir = DMA_BIसूचीECTIONAL;
	अन्यथा
		ctx->dir = DMA_TO_DEVICE;

	ctx->key_dma = dma_map_single(dev, ctx->key, माप(ctx->key),
				      ctx->dir);
	अगर (dma_mapping_error(dev, ctx->key_dma)) अणु
		dev_err(dev, "unable to map key\n");
		caam_jr_मुक्त(ctx->jrdev);
		वापस -ENOMEM;
	पूर्ण

	/* copy descriptor header ढाँचा value */
	ctx->cdata.algtype = OP_TYPE_CLASS1_ALG | caam->class1_alg_type;
	ctx->adata.algtype = OP_TYPE_CLASS2_ALG | caam->class2_alg_type;

	ctx->qidev = dev;

	spin_lock_init(&ctx->lock);
	ctx->drv_ctx[ENCRYPT] = शून्य;
	ctx->drv_ctx[DECRYPT] = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक caam_cra_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा caam_skcipher_alg *caam_alg =
		container_of(alg, typeof(*caam_alg), skcipher);
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(tfm);
	u32 alg_aai = caam_alg->caam.class1_alg_type & OP_ALG_AAI_MASK;
	पूर्णांक ret = 0;

	अगर (alg_aai == OP_ALG_AAI_XTS) अणु
		स्थिर अक्षर *tfm_name = crypto_tfm_alg_name(&tfm->base);
		काष्ठा crypto_skcipher *fallback;

		fallback = crypto_alloc_skcipher(tfm_name, 0,
						 CRYPTO_ALG_NEED_FALLBACK);
		अगर (IS_ERR(fallback)) अणु
			pr_err("Failed to allocate %s fallback: %ld\n",
			       tfm_name, PTR_ERR(fallback));
			वापस PTR_ERR(fallback);
		पूर्ण

		ctx->fallback = fallback;
		crypto_skcipher_set_reqsize(tfm, माप(काष्ठा caam_skcipher_req_ctx) +
					    crypto_skcipher_reqsize(fallback));
	पूर्ण

	ret = caam_init_common(ctx, &caam_alg->caam, false);
	अगर (ret && ctx->fallback)
		crypto_मुक्त_skcipher(ctx->fallback);

	वापस ret;
पूर्ण

अटल पूर्णांक caam_aead_init(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_alg *alg = crypto_aead_alg(tfm);
	काष्ठा caam_aead_alg *caam_alg = container_of(alg, typeof(*caam_alg),
						      aead);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(tfm);

	वापस caam_init_common(ctx, &caam_alg->caam, !caam_alg->caam.nodkp);
पूर्ण

अटल व्योम caam_निकास_common(काष्ठा caam_ctx *ctx)
अणु
	caam_drv_ctx_rel(ctx->drv_ctx[ENCRYPT]);
	caam_drv_ctx_rel(ctx->drv_ctx[DECRYPT]);

	dma_unmap_single(ctx->jrdev->parent, ctx->key_dma, माप(ctx->key),
			 ctx->dir);

	caam_jr_मुक्त(ctx->jrdev);
पूर्ण

अटल व्योम caam_cra_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(tfm);

	अगर (ctx->fallback)
		crypto_मुक्त_skcipher(ctx->fallback);
	caam_निकास_common(ctx);
पूर्ण

अटल व्योम caam_aead_निकास(काष्ठा crypto_aead *tfm)
अणु
	caam_निकास_common(crypto_aead_ctx(tfm));
पूर्ण

व्योम caam_qi_algapi_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(driver_aeads); i++) अणु
		काष्ठा caam_aead_alg *t_alg = driver_aeads + i;

		अगर (t_alg->रेजिस्टरed)
			crypto_unरेजिस्टर_aead(&t_alg->aead);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(driver_algs); i++) अणु
		काष्ठा caam_skcipher_alg *t_alg = driver_algs + i;

		अगर (t_alg->रेजिस्टरed)
			crypto_unरेजिस्टर_skcipher(&t_alg->skcipher);
	पूर्ण
पूर्ण

अटल व्योम caam_skcipher_alg_init(काष्ठा caam_skcipher_alg *t_alg)
अणु
	काष्ठा skcipher_alg *alg = &t_alg->skcipher;

	alg->base.cra_module = THIS_MODULE;
	alg->base.cra_priority = CAAM_CRA_PRIORITY;
	alg->base.cra_ctxsize = माप(काष्ठा caam_ctx);
	alg->base.cra_flags |= (CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY |
				CRYPTO_ALG_KERN_DRIVER_ONLY);

	alg->init = caam_cra_init;
	alg->निकास = caam_cra_निकास;
पूर्ण

अटल व्योम caam_aead_alg_init(काष्ठा caam_aead_alg *t_alg)
अणु
	काष्ठा aead_alg *alg = &t_alg->aead;

	alg->base.cra_module = THIS_MODULE;
	alg->base.cra_priority = CAAM_CRA_PRIORITY;
	alg->base.cra_ctxsize = माप(काष्ठा caam_ctx);
	alg->base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY |
			      CRYPTO_ALG_KERN_DRIVER_ONLY;

	alg->init = caam_aead_init;
	alg->निकास = caam_aead_निकास;
पूर्ण

पूर्णांक caam_qi_algapi_init(काष्ठा device *ctrldev)
अणु
	काष्ठा caam_drv_निजी *priv = dev_get_drvdata(ctrldev);
	पूर्णांक i = 0, err = 0;
	u32 aes_vid, aes_inst, des_inst, md_vid, md_inst;
	अचिन्हित पूर्णांक md_limit = SHA512_DIGEST_SIZE;
	bool रेजिस्टरed = false;

	/* Make sure this runs only on (DPAA 1.x) QI */
	अगर (!priv->qi_present || caam_dpaa2)
		वापस 0;

	/*
	 * Register crypto algorithms the device supports.
	 * First, detect presence and attributes of DES, AES, and MD blocks.
	 */
	अगर (priv->era < 10) अणु
		u32 cha_vid, cha_inst;

		cha_vid = rd_reg32(&priv->ctrl->perfmon.cha_id_ls);
		aes_vid = cha_vid & CHA_ID_LS_AES_MASK;
		md_vid = (cha_vid & CHA_ID_LS_MD_MASK) >> CHA_ID_LS_MD_SHIFT;

		cha_inst = rd_reg32(&priv->ctrl->perfmon.cha_num_ls);
		des_inst = (cha_inst & CHA_ID_LS_DES_MASK) >>
			   CHA_ID_LS_DES_SHIFT;
		aes_inst = cha_inst & CHA_ID_LS_AES_MASK;
		md_inst = (cha_inst & CHA_ID_LS_MD_MASK) >> CHA_ID_LS_MD_SHIFT;
	पूर्ण अन्यथा अणु
		u32 aesa, mdha;

		aesa = rd_reg32(&priv->ctrl->vreg.aesa);
		mdha = rd_reg32(&priv->ctrl->vreg.mdha);

		aes_vid = (aesa & CHA_VER_VID_MASK) >> CHA_VER_VID_SHIFT;
		md_vid = (mdha & CHA_VER_VID_MASK) >> CHA_VER_VID_SHIFT;

		des_inst = rd_reg32(&priv->ctrl->vreg.desa) & CHA_VER_NUM_MASK;
		aes_inst = aesa & CHA_VER_NUM_MASK;
		md_inst = mdha & CHA_VER_NUM_MASK;
	पूर्ण

	/* If MD is present, limit digest size based on LP256 */
	अगर (md_inst && md_vid  == CHA_VER_VID_MD_LP256)
		md_limit = SHA256_DIGEST_SIZE;

	क्रम (i = 0; i < ARRAY_SIZE(driver_algs); i++) अणु
		काष्ठा caam_skcipher_alg *t_alg = driver_algs + i;
		u32 alg_sel = t_alg->caam.class1_alg_type & OP_ALG_ALGSEL_MASK;

		/* Skip DES algorithms अगर not supported by device */
		अगर (!des_inst &&
		    ((alg_sel == OP_ALG_ALGSEL_3DES) ||
		     (alg_sel == OP_ALG_ALGSEL_DES)))
			जारी;

		/* Skip AES algorithms अगर not supported by device */
		अगर (!aes_inst && (alg_sel == OP_ALG_ALGSEL_AES))
			जारी;

		caam_skcipher_alg_init(t_alg);

		err = crypto_रेजिस्टर_skcipher(&t_alg->skcipher);
		अगर (err) अणु
			dev_warn(ctrldev, "%s alg registration failed\n",
				 t_alg->skcipher.base.cra_driver_name);
			जारी;
		पूर्ण

		t_alg->रेजिस्टरed = true;
		रेजिस्टरed = true;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(driver_aeads); i++) अणु
		काष्ठा caam_aead_alg *t_alg = driver_aeads + i;
		u32 c1_alg_sel = t_alg->caam.class1_alg_type &
				 OP_ALG_ALGSEL_MASK;
		u32 c2_alg_sel = t_alg->caam.class2_alg_type &
				 OP_ALG_ALGSEL_MASK;
		u32 alg_aai = t_alg->caam.class1_alg_type & OP_ALG_AAI_MASK;

		/* Skip DES algorithms अगर not supported by device */
		अगर (!des_inst &&
		    ((c1_alg_sel == OP_ALG_ALGSEL_3DES) ||
		     (c1_alg_sel == OP_ALG_ALGSEL_DES)))
			जारी;

		/* Skip AES algorithms अगर not supported by device */
		अगर (!aes_inst && (c1_alg_sel == OP_ALG_ALGSEL_AES))
			जारी;

		/*
		 * Check support क्रम AES algorithms not available
		 * on LP devices.
		 */
		अगर (aes_vid  == CHA_VER_VID_AES_LP && alg_aai == OP_ALG_AAI_GCM)
			जारी;

		/*
		 * Skip algorithms requiring message digests
		 * अगर MD or MD size is not supported by device.
		 */
		अगर (c2_alg_sel &&
		    (!md_inst || (t_alg->aead.maxauthsize > md_limit)))
			जारी;

		caam_aead_alg_init(t_alg);

		err = crypto_रेजिस्टर_aead(&t_alg->aead);
		अगर (err) अणु
			pr_warn("%s alg registration failed\n",
				t_alg->aead.base.cra_driver_name);
			जारी;
		पूर्ण

		t_alg->रेजिस्टरed = true;
		रेजिस्टरed = true;
	पूर्ण

	अगर (रेजिस्टरed)
		dev_info(ctrldev, "algorithms registered in /proc/crypto\n");

	वापस err;
पूर्ण
