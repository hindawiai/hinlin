<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * caam - Freescale FSL CAAM support क्रम crypto API
 *
 * Copyright 2008-2011 Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 *
 * Based on talitos crypto API driver.
 *
 * relationship of job descriptors to shared descriptors (SteveC Dec 10 2008):
 *
 * ---------------                     ---------------
 * | JobDesc #1  |-------------------->|  ShareDesc  |
 * | *(packet 1) |                     |   (PDB)     |
 * ---------------      |------------->|  (hashKey)  |
 *       .              |              | (cipherKey) |
 *       .              |    |-------->| (operation) |
 * ---------------      |    |         ---------------
 * | JobDesc #2  |------|    |
 * | *(packet 2) |           |
 * ---------------           |
 *       .                   |
 *       .                   |
 * ---------------           |
 * | JobDesc #3  |------------
 * | *(packet 3) |
 * ---------------
 *
 * The SharedDesc never changes क्रम a connection unless rekeyed, but
 * each packet will likely be in a dअगरferent place. So all we need
 * to know to process the packet is where the input is, where the
 * output goes, and what context we want to process with. Context is
 * in the SharedDesc, packet references in the JobDesc.
 *
 * So, a job desc looks like:
 *
 * ---------------------
 * | Header            |
 * | ShareDesc Poपूर्णांकer |
 * | SEQ_OUT_PTR       |
 * | (output buffer)   |
 * | (output length)   |
 * | SEQ_IN_PTR        |
 * | (input buffer)    |
 * | (input length)    |
 * ---------------------
 */

#समावेश "compat.h"

#समावेश "regs.h"
#समावेश "intern.h"
#समावेश "desc_constr.h"
#समावेश "jr.h"
#समावेश "error.h"
#समावेश "sg_sw_sec4.h"
#समावेश "key_gen.h"
#समावेश "caamalg_desc.h"
#समावेश <crypto/engine.h>
#समावेश <crypto/xts.h>
#समावेश <यंत्र/unaligned.h>

/*
 * crypto alg
 */
#घोषणा CAAM_CRA_PRIORITY		3000
/* max key is sum of AES_MAX_KEY_SIZE, max split key size */
#घोषणा CAAM_MAX_KEY_SIZE		(AES_MAX_KEY_SIZE + \
					 CTR_RFC3686_NONCE_SIZE + \
					 SHA512_DIGEST_SIZE * 2)

#घोषणा AEAD_DESC_JOB_IO_LEN		(DESC_JOB_IO_LEN + CAAM_CMD_SZ * 2)
#घोषणा GCM_DESC_JOB_IO_LEN		(AEAD_DESC_JOB_IO_LEN + \
					 CAAM_CMD_SZ * 4)
#घोषणा AUTHENC_DESC_JOB_IO_LEN		(AEAD_DESC_JOB_IO_LEN + \
					 CAAM_CMD_SZ * 5)

#घोषणा CHACHAPOLY_DESC_JOB_IO_LEN	(AEAD_DESC_JOB_IO_LEN + CAAM_CMD_SZ * 6)

#घोषणा DESC_MAX_USED_BYTES		(CAAM_DESC_BYTES_MAX - DESC_JOB_IO_LEN_MIN)
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
	काष्ठा crypto_engine_ctx enginectx;
	u32 sh_desc_enc[DESC_MAX_USED_LEN];
	u32 sh_desc_dec[DESC_MAX_USED_LEN];
	u8 key[CAAM_MAX_KEY_SIZE];
	dma_addr_t sh_desc_enc_dma;
	dma_addr_t sh_desc_dec_dma;
	dma_addr_t key_dma;
	क्रमागत dma_data_direction dir;
	काष्ठा device *jrdev;
	काष्ठा alginfo adata;
	काष्ठा alginfo cdata;
	अचिन्हित पूर्णांक authsize;
	bool xts_key_fallback;
	काष्ठा crypto_skcipher *fallback;
पूर्ण;

काष्ठा caam_skcipher_req_ctx अणु
	काष्ठा skcipher_edesc *edesc;
	काष्ठा skcipher_request fallback_req;
पूर्ण;

काष्ठा caam_aead_req_ctx अणु
	काष्ठा aead_edesc *edesc;
पूर्ण;

अटल पूर्णांक aead_null_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(jrdev->parent);
	u32 *desc;
	पूर्णांक rem_bytes = CAAM_DESC_BYTES_MAX - AEAD_DESC_JOB_IO_LEN -
			ctx->adata.keylen_pad;

	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_AEAD_शून्य_ENC_LEN) अणु
		ctx->adata.key_अंतरभूत = true;
		ctx->adata.key_virt = ctx->key;
	पूर्ण अन्यथा अणु
		ctx->adata.key_अंतरभूत = false;
		ctx->adata.key_dma = ctx->key_dma;
	पूर्ण

	/* aead_encrypt shared descriptor */
	desc = ctx->sh_desc_enc;
	cnstr_shdsc_aead_null_encap(desc, &ctx->adata, ctx->authsize,
				    ctrlpriv->era);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_enc_dma,
				   desc_bytes(desc), ctx->dir);

	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_AEAD_शून्य_DEC_LEN) अणु
		ctx->adata.key_अंतरभूत = true;
		ctx->adata.key_virt = ctx->key;
	पूर्ण अन्यथा अणु
		ctx->adata.key_अंतरभूत = false;
		ctx->adata.key_dma = ctx->key_dma;
	पूर्ण

	/* aead_decrypt shared descriptor */
	desc = ctx->sh_desc_dec;
	cnstr_shdsc_aead_null_decap(desc, &ctx->adata, ctx->authsize,
				    ctrlpriv->era);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_dec_dma,
				   desc_bytes(desc), ctx->dir);

	वापस 0;
पूर्ण

अटल पूर्णांक aead_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_aead_alg *alg = container_of(crypto_aead_alg(aead),
						 काष्ठा caam_aead_alg, aead);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(jrdev->parent);
	u32 ctx1_iv_off = 0;
	u32 *desc, *nonce = शून्य;
	u32 inl_mask;
	अचिन्हित पूर्णांक data_len[2];
	स्थिर bool ctr_mode = ((ctx->cdata.algtype & OP_ALG_AAI_MASK) ==
			       OP_ALG_AAI_CTR_MOD128);
	स्थिर bool is_rfc3686 = alg->caam.rfc3686;

	अगर (!ctx->authsize)
		वापस 0;

	/* शून्य encryption / decryption */
	अगर (!ctx->cdata.keylen)
		वापस aead_null_set_sh_desc(aead);

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
	 * In हाल |user key| > |derived key|, using DKP<imm,imm>
	 * would result in invalid opcodes (last bytes of user key) in
	 * the resulting descriptor. Use DKP<ptr,imm> instead => both
	 * भव and dma key addresses are needed.
	 */
	ctx->adata.key_virt = ctx->key;
	ctx->adata.key_dma = ctx->key_dma;

	ctx->cdata.key_virt = ctx->key + ctx->adata.keylen_pad;
	ctx->cdata.key_dma = ctx->key_dma + ctx->adata.keylen_pad;

	data_len[0] = ctx->adata.keylen_pad;
	data_len[1] = ctx->cdata.keylen;

	अगर (alg->caam.geniv)
		जाओ skip_enc;

	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (desc_अंतरभूत_query(DESC_AEAD_ENC_LEN +
			      (is_rfc3686 ? DESC_AEAD_CTR_RFC3686_LEN : 0),
			      AUTHENC_DESC_JOB_IO_LEN, data_len, &inl_mask,
			      ARRAY_SIZE(data_len)) < 0)
		वापस -EINVAL;

	ctx->adata.key_अंतरभूत = !!(inl_mask & 1);
	ctx->cdata.key_अंतरभूत = !!(inl_mask & 2);

	/* aead_encrypt shared descriptor */
	desc = ctx->sh_desc_enc;
	cnstr_shdsc_aead_encap(desc, &ctx->cdata, &ctx->adata, ivsize,
			       ctx->authsize, is_rfc3686, nonce, ctx1_iv_off,
			       false, ctrlpriv->era);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_enc_dma,
				   desc_bytes(desc), ctx->dir);

skip_enc:
	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (desc_अंतरभूत_query(DESC_AEAD_DEC_LEN +
			      (is_rfc3686 ? DESC_AEAD_CTR_RFC3686_LEN : 0),
			      AUTHENC_DESC_JOB_IO_LEN, data_len, &inl_mask,
			      ARRAY_SIZE(data_len)) < 0)
		वापस -EINVAL;

	ctx->adata.key_अंतरभूत = !!(inl_mask & 1);
	ctx->cdata.key_अंतरभूत = !!(inl_mask & 2);

	/* aead_decrypt shared descriptor */
	desc = ctx->sh_desc_dec;
	cnstr_shdsc_aead_decap(desc, &ctx->cdata, &ctx->adata, ivsize,
			       ctx->authsize, alg->caam.geniv, is_rfc3686,
			       nonce, ctx1_iv_off, false, ctrlpriv->era);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_dec_dma,
				   desc_bytes(desc), ctx->dir);

	अगर (!alg->caam.geniv)
		जाओ skip_givenc;

	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (desc_अंतरभूत_query(DESC_AEAD_GIVENC_LEN +
			      (is_rfc3686 ? DESC_AEAD_CTR_RFC3686_LEN : 0),
			      AUTHENC_DESC_JOB_IO_LEN, data_len, &inl_mask,
			      ARRAY_SIZE(data_len)) < 0)
		वापस -EINVAL;

	ctx->adata.key_अंतरभूत = !!(inl_mask & 1);
	ctx->cdata.key_अंतरभूत = !!(inl_mask & 2);

	/* aead_givencrypt shared descriptor */
	desc = ctx->sh_desc_enc;
	cnstr_shdsc_aead_givencap(desc, &ctx->cdata, &ctx->adata, ivsize,
				  ctx->authsize, is_rfc3686, nonce,
				  ctx1_iv_off, false, ctrlpriv->era);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_enc_dma,
				   desc_bytes(desc), ctx->dir);

skip_givenc:
	वापस 0;
पूर्ण

अटल पूर्णांक aead_setauthsize(काष्ठा crypto_aead *authenc,
				    अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(authenc);

	ctx->authsize = authsize;
	aead_set_sh_desc(authenc);

	वापस 0;
पूर्ण

अटल पूर्णांक gcm_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	u32 *desc;
	पूर्णांक rem_bytes = CAAM_DESC_BYTES_MAX - GCM_DESC_JOB_IO_LEN -
			ctx->cdata.keylen;

	अगर (!ctx->cdata.keylen || !ctx->authsize)
		वापस 0;

	/*
	 * AES GCM encrypt shared descriptor
	 * Job Descriptor and Shared Descriptor
	 * must fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_GCM_ENC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
		ctx->cdata.key_virt = ctx->key;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	desc = ctx->sh_desc_enc;
	cnstr_shdsc_gcm_encap(desc, &ctx->cdata, ivsize, ctx->authsize, false);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_enc_dma,
				   desc_bytes(desc), ctx->dir);

	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_GCM_DEC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
		ctx->cdata.key_virt = ctx->key;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	desc = ctx->sh_desc_dec;
	cnstr_shdsc_gcm_decap(desc, &ctx->cdata, ivsize, ctx->authsize, false);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_dec_dma,
				   desc_bytes(desc), ctx->dir);

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

अटल पूर्णांक rfc4106_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	u32 *desc;
	पूर्णांक rem_bytes = CAAM_DESC_BYTES_MAX - GCM_DESC_JOB_IO_LEN -
			ctx->cdata.keylen;

	अगर (!ctx->cdata.keylen || !ctx->authsize)
		वापस 0;

	/*
	 * RFC4106 encrypt shared descriptor
	 * Job Descriptor and Shared Descriptor
	 * must fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_RFC4106_ENC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
		ctx->cdata.key_virt = ctx->key;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	desc = ctx->sh_desc_enc;
	cnstr_shdsc_rfc4106_encap(desc, &ctx->cdata, ivsize, ctx->authsize,
				  false);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_enc_dma,
				   desc_bytes(desc), ctx->dir);

	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_RFC4106_DEC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
		ctx->cdata.key_virt = ctx->key;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	desc = ctx->sh_desc_dec;
	cnstr_shdsc_rfc4106_decap(desc, &ctx->cdata, ivsize, ctx->authsize,
				  false);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_dec_dma,
				   desc_bytes(desc), ctx->dir);

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

अटल पूर्णांक rfc4543_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	u32 *desc;
	पूर्णांक rem_bytes = CAAM_DESC_BYTES_MAX - GCM_DESC_JOB_IO_LEN -
			ctx->cdata.keylen;

	अगर (!ctx->cdata.keylen || !ctx->authsize)
		वापस 0;

	/*
	 * RFC4543 encrypt shared descriptor
	 * Job Descriptor and Shared Descriptor
	 * must fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_RFC4543_ENC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
		ctx->cdata.key_virt = ctx->key;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	desc = ctx->sh_desc_enc;
	cnstr_shdsc_rfc4543_encap(desc, &ctx->cdata, ivsize, ctx->authsize,
				  false);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_enc_dma,
				   desc_bytes(desc), ctx->dir);

	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_RFC4543_DEC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
		ctx->cdata.key_virt = ctx->key;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	desc = ctx->sh_desc_dec;
	cnstr_shdsc_rfc4543_decap(desc, &ctx->cdata, ivsize, ctx->authsize,
				  false);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_dec_dma,
				   desc_bytes(desc), ctx->dir);

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

अटल पूर्णांक chachapoly_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	u32 *desc;

	अगर (!ctx->cdata.keylen || !ctx->authsize)
		वापस 0;

	desc = ctx->sh_desc_enc;
	cnstr_shdsc_chachapoly(desc, &ctx->cdata, &ctx->adata, ivsize,
			       ctx->authsize, true, false);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_enc_dma,
				   desc_bytes(desc), ctx->dir);

	desc = ctx->sh_desc_dec;
	cnstr_shdsc_chachapoly(desc, &ctx->cdata, &ctx->adata, ivsize,
			       ctx->authsize, false, false);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_dec_dma,
				   desc_bytes(desc), ctx->dir);

	वापस 0;
पूर्ण

अटल पूर्णांक chachapoly_setauthsize(काष्ठा crypto_aead *aead,
				  अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);

	अगर (authsize != POLY1305_DIGEST_SIZE)
		वापस -EINVAL;

	ctx->authsize = authsize;
	वापस chachapoly_set_sh_desc(aead);
पूर्ण

अटल पूर्णांक chachapoly_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	अचिन्हित पूर्णांक saltlen = CHACHAPOLY_IV_SIZE - ivsize;

	अगर (keylen != CHACHA_KEY_SIZE + saltlen)
		वापस -EINVAL;

	ctx->cdata.key_virt = key;
	ctx->cdata.keylen = keylen - saltlen;

	वापस chachapoly_set_sh_desc(aead);
पूर्ण

अटल पूर्णांक aead_setkey(काष्ठा crypto_aead *aead,
			       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
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
	prपूर्णांक_hex_dump_debug("key in @"__stringअगरy(__LINE__)": ",
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
		dma_sync_single_क्रम_device(jrdev, ctx->key_dma,
					   ctx->adata.keylen_pad +
					   keys.enckeylen, ctx->dir);
		जाओ skip_split_key;
	पूर्ण

	ret = gen_split_key(ctx->jrdev, ctx->key, &ctx->adata, keys.authkey,
			    keys.authkeylen, CAAM_MAX_KEY_SIZE -
			    keys.enckeylen);
	अगर (ret) अणु
		जाओ badkey;
	पूर्ण

	/* postpend encryption key to auth split key */
	स_नकल(ctx->key + ctx->adata.keylen_pad, keys.enckey, keys.enckeylen);
	dma_sync_single_क्रम_device(jrdev, ctx->key_dma, ctx->adata.keylen_pad +
				   keys.enckeylen, ctx->dir);

	prपूर्णांक_hex_dump_debug("ctx.key@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, ctx->key,
			     ctx->adata.keylen_pad + keys.enckeylen, 1);

skip_split_key:
	ctx->cdata.keylen = keys.enckeylen;
	memzero_explicit(&keys, माप(keys));
	वापस aead_set_sh_desc(aead);
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

अटल पूर्णांक gcm_setkey(काष्ठा crypto_aead *aead,
		      स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	पूर्णांक err;

	err = aes_check_keylen(keylen);
	अगर (err)
		वापस err;

	prपूर्णांक_hex_dump_debug("key in @"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);

	स_नकल(ctx->key, key, keylen);
	dma_sync_single_क्रम_device(jrdev, ctx->key_dma, keylen, ctx->dir);
	ctx->cdata.keylen = keylen;

	वापस gcm_set_sh_desc(aead);
पूर्ण

अटल पूर्णांक rfc4106_setkey(काष्ठा crypto_aead *aead,
			  स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	पूर्णांक err;

	err = aes_check_keylen(keylen - 4);
	अगर (err)
		वापस err;

	prपूर्णांक_hex_dump_debug("key in @"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);

	स_नकल(ctx->key, key, keylen);

	/*
	 * The last four bytes of the key material are used as the salt value
	 * in the nonce. Update the AES key length.
	 */
	ctx->cdata.keylen = keylen - 4;
	dma_sync_single_क्रम_device(jrdev, ctx->key_dma, ctx->cdata.keylen,
				   ctx->dir);
	वापस rfc4106_set_sh_desc(aead);
पूर्ण

अटल पूर्णांक rfc4543_setkey(काष्ठा crypto_aead *aead,
			  स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	पूर्णांक err;

	err = aes_check_keylen(keylen - 4);
	अगर (err)
		वापस err;

	prपूर्णांक_hex_dump_debug("key in @"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);

	स_नकल(ctx->key, key, keylen);

	/*
	 * The last four bytes of the key material are used as the salt value
	 * in the nonce. Update the AES key length.
	 */
	ctx->cdata.keylen = keylen - 4;
	dma_sync_single_क्रम_device(jrdev, ctx->key_dma, ctx->cdata.keylen,
				   ctx->dir);
	वापस rfc4543_set_sh_desc(aead);
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
	u32 *desc;
	स्थिर bool is_rfc3686 = alg->caam.rfc3686;

	prपूर्णांक_hex_dump_debug("key in @"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);

	ctx->cdata.keylen = keylen;
	ctx->cdata.key_virt = key;
	ctx->cdata.key_अंतरभूत = true;

	/* skcipher_encrypt shared descriptor */
	desc = ctx->sh_desc_enc;
	cnstr_shdsc_skcipher_encap(desc, &ctx->cdata, ivsize, is_rfc3686,
				   ctx1_iv_off);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_enc_dma,
				   desc_bytes(desc), ctx->dir);

	/* skcipher_decrypt shared descriptor */
	desc = ctx->sh_desc_dec;
	cnstr_shdsc_skcipher_decap(desc, &ctx->cdata, ivsize, is_rfc3686,
				   ctx1_iv_off);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_dec_dma,
				   desc_bytes(desc), ctx->dir);

	वापस 0;
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

अटल पूर्णांक des_skcipher_setkey(काष्ठा crypto_skcipher *skcipher,
			       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस verअगरy_skcipher_des_key(skcipher, key) ?:
	       skcipher_setkey(skcipher, key, keylen, 0);
पूर्ण

अटल पूर्णांक des3_skcipher_setkey(काष्ठा crypto_skcipher *skcipher,
				स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस verअगरy_skcipher_des3_key(skcipher, key) ?:
	       skcipher_setkey(skcipher, key, keylen, 0);
पूर्ण

अटल पूर्णांक xts_skcipher_setkey(काष्ठा crypto_skcipher *skcipher, स्थिर u8 *key,
			       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा device *jrdev = ctx->jrdev;
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(jrdev->parent);
	u32 *desc;
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

	/* xts_skcipher_encrypt shared descriptor */
	desc = ctx->sh_desc_enc;
	cnstr_shdsc_xts_skcipher_encap(desc, &ctx->cdata);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_enc_dma,
				   desc_bytes(desc), ctx->dir);

	/* xts_skcipher_decrypt shared descriptor */
	desc = ctx->sh_desc_dec;
	cnstr_shdsc_xts_skcipher_decap(desc, &ctx->cdata);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_dec_dma,
				   desc_bytes(desc), ctx->dir);

	वापस 0;
पूर्ण

/*
 * aead_edesc - s/w-extended aead descriptor
 * @src_nents: number of segments in input s/w scatterlist
 * @dst_nents: number of segments in output s/w scatterlist
 * @mapped_src_nents: number of segments in input h/w link table
 * @mapped_dst_nents: number of segments in output h/w link table
 * @sec4_sg_bytes: length of dma mapped sec4_sg space
 * @bklog: stored to determine अगर the request needs backlog
 * @sec4_sg_dma: bus physical mapped address of h/w link table
 * @sec4_sg: poपूर्णांकer to h/w link table
 * @hw_desc: the h/w job descriptor followed by any referenced link tables
 */
काष्ठा aead_edesc अणु
	पूर्णांक src_nents;
	पूर्णांक dst_nents;
	पूर्णांक mapped_src_nents;
	पूर्णांक mapped_dst_nents;
	पूर्णांक sec4_sg_bytes;
	bool bklog;
	dma_addr_t sec4_sg_dma;
	काष्ठा sec4_sg_entry *sec4_sg;
	u32 hw_desc[];
पूर्ण;

/*
 * skcipher_edesc - s/w-extended skcipher descriptor
 * @src_nents: number of segments in input s/w scatterlist
 * @dst_nents: number of segments in output s/w scatterlist
 * @mapped_src_nents: number of segments in input h/w link table
 * @mapped_dst_nents: number of segments in output h/w link table
 * @iv_dma: dma address of iv क्रम checking continuity and link table
 * @sec4_sg_bytes: length of dma mapped sec4_sg space
 * @bklog: stored to determine अगर the request needs backlog
 * @sec4_sg_dma: bus physical mapped address of h/w link table
 * @sec4_sg: poपूर्णांकer to h/w link table
 * @hw_desc: the h/w job descriptor followed by any referenced link tables
 *	     and IV
 */
काष्ठा skcipher_edesc अणु
	पूर्णांक src_nents;
	पूर्णांक dst_nents;
	पूर्णांक mapped_src_nents;
	पूर्णांक mapped_dst_nents;
	dma_addr_t iv_dma;
	पूर्णांक sec4_sg_bytes;
	bool bklog;
	dma_addr_t sec4_sg_dma;
	काष्ठा sec4_sg_entry *sec4_sg;
	u32 hw_desc[];
पूर्ण;

अटल व्योम caam_unmap(काष्ठा device *dev, काष्ठा scatterlist *src,
		       काष्ठा scatterlist *dst, पूर्णांक src_nents,
		       पूर्णांक dst_nents,
		       dma_addr_t iv_dma, पूर्णांक ivsize, dma_addr_t sec4_sg_dma,
		       पूर्णांक sec4_sg_bytes)
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
		dma_unmap_single(dev, iv_dma, ivsize, DMA_BIसूचीECTIONAL);
	अगर (sec4_sg_bytes)
		dma_unmap_single(dev, sec4_sg_dma, sec4_sg_bytes,
				 DMA_TO_DEVICE);
पूर्ण

अटल व्योम aead_unmap(काष्ठा device *dev,
		       काष्ठा aead_edesc *edesc,
		       काष्ठा aead_request *req)
अणु
	caam_unmap(dev, req->src, req->dst,
		   edesc->src_nents, edesc->dst_nents, 0, 0,
		   edesc->sec4_sg_dma, edesc->sec4_sg_bytes);
पूर्ण

अटल व्योम skcipher_unmap(काष्ठा device *dev, काष्ठा skcipher_edesc *edesc,
			   काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);

	caam_unmap(dev, req->src, req->dst,
		   edesc->src_nents, edesc->dst_nents,
		   edesc->iv_dma, ivsize,
		   edesc->sec4_sg_dma, edesc->sec4_sg_bytes);
पूर्ण

अटल व्योम aead_crypt_करोne(काष्ठा device *jrdev, u32 *desc, u32 err,
			    व्योम *context)
अणु
	काष्ठा aead_request *req = context;
	काष्ठा caam_aead_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा caam_drv_निजी_jr *jrp = dev_get_drvdata(jrdev);
	काष्ठा aead_edesc *edesc;
	पूर्णांक ecode = 0;
	bool has_bklog;

	dev_dbg(jrdev, "%s %d: err 0x%x\n", __func__, __LINE__, err);

	edesc = rctx->edesc;
	has_bklog = edesc->bklog;

	अगर (err)
		ecode = caam_jr_strstatus(jrdev, err);

	aead_unmap(jrdev, edesc, req);

	kमुक्त(edesc);

	/*
	 * If no backlog flag, the completion of the request is करोne
	 * by CAAM, not crypto engine.
	 */
	अगर (!has_bklog)
		aead_request_complete(req, ecode);
	अन्यथा
		crypto_finalize_aead_request(jrp->engine, req, ecode);
पूर्ण

अटल व्योम skcipher_crypt_करोne(काष्ठा device *jrdev, u32 *desc, u32 err,
				व्योम *context)
अणु
	काष्ठा skcipher_request *req = context;
	काष्ठा skcipher_edesc *edesc;
	काष्ठा caam_skcipher_req_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा caam_drv_निजी_jr *jrp = dev_get_drvdata(jrdev);
	पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);
	पूर्णांक ecode = 0;
	bool has_bklog;

	dev_dbg(jrdev, "%s %d: err 0x%x\n", __func__, __LINE__, err);

	edesc = rctx->edesc;
	has_bklog = edesc->bklog;
	अगर (err)
		ecode = caam_jr_strstatus(jrdev, err);

	skcipher_unmap(jrdev, edesc, req);

	/*
	 * The crypto API expects us to set the IV (req->iv) to the last
	 * ciphertext block (CBC mode) or last counter (CTR mode).
	 * This is used e.g. by the CTS mode.
	 */
	अगर (ivsize && !ecode) अणु
		स_नकल(req->iv, (u8 *)edesc->sec4_sg + edesc->sec4_sg_bytes,
		       ivsize);

		prपूर्णांक_hex_dump_debug("dstiv  @" __stringअगरy(__LINE__)": ",
				     DUMP_PREFIX_ADDRESS, 16, 4, req->iv,
				     ivsize, 1);
	पूर्ण

	caam_dump_sg("dst    @" __stringअगरy(__LINE__)": ",
		     DUMP_PREFIX_ADDRESS, 16, 4, req->dst,
		     edesc->dst_nents > 1 ? 100 : req->cryptlen, 1);

	kमुक्त(edesc);

	/*
	 * If no backlog flag, the completion of the request is करोne
	 * by CAAM, not crypto engine.
	 */
	अगर (!has_bklog)
		skcipher_request_complete(req, ecode);
	अन्यथा
		crypto_finalize_skcipher_request(jrp->engine, req, ecode);
पूर्ण

/*
 * Fill in aead job descriptor
 */
अटल व्योम init_aead_job(काष्ठा aead_request *req,
			  काष्ठा aead_edesc *edesc,
			  bool all_contig, bool encrypt)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	पूर्णांक authsize = ctx->authsize;
	u32 *desc = edesc->hw_desc;
	u32 out_options, in_options;
	dma_addr_t dst_dma, src_dma;
	पूर्णांक len, sec4_sg_index = 0;
	dma_addr_t ptr;
	u32 *sh_desc;

	sh_desc = encrypt ? ctx->sh_desc_enc : ctx->sh_desc_dec;
	ptr = encrypt ? ctx->sh_desc_enc_dma : ctx->sh_desc_dec_dma;

	len = desc_len(sh_desc);
	init_job_desc_shared(desc, ptr, len, HDR_SHARE_DEFER | HDR_REVERSE);

	अगर (all_contig) अणु
		src_dma = edesc->mapped_src_nents ? sg_dma_address(req->src) :
						    0;
		in_options = 0;
	पूर्ण अन्यथा अणु
		src_dma = edesc->sec4_sg_dma;
		sec4_sg_index += edesc->mapped_src_nents;
		in_options = LDST_SGF;
	पूर्ण

	append_seq_in_ptr(desc, src_dma, req->assoclen + req->cryptlen,
			  in_options);

	dst_dma = src_dma;
	out_options = in_options;

	अगर (unlikely(req->src != req->dst)) अणु
		अगर (!edesc->mapped_dst_nents) अणु
			dst_dma = 0;
			out_options = 0;
		पूर्ण अन्यथा अगर (edesc->mapped_dst_nents == 1) अणु
			dst_dma = sg_dma_address(req->dst);
			out_options = 0;
		पूर्ण अन्यथा अणु
			dst_dma = edesc->sec4_sg_dma +
				  sec4_sg_index *
				  माप(काष्ठा sec4_sg_entry);
			out_options = LDST_SGF;
		पूर्ण
	पूर्ण

	अगर (encrypt)
		append_seq_out_ptr(desc, dst_dma,
				   req->assoclen + req->cryptlen + authsize,
				   out_options);
	अन्यथा
		append_seq_out_ptr(desc, dst_dma,
				   req->assoclen + req->cryptlen - authsize,
				   out_options);
पूर्ण

अटल व्योम init_gcm_job(काष्ठा aead_request *req,
			 काष्ठा aead_edesc *edesc,
			 bool all_contig, bool encrypt)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	u32 *desc = edesc->hw_desc;
	bool generic_gcm = (ivsize == GCM_AES_IV_SIZE);
	अचिन्हित पूर्णांक last;

	init_aead_job(req, edesc, all_contig, encrypt);
	append_math_add_imm_u32(desc, REG3, ZERO, IMM, req->assoclen);

	/* BUG This should not be specअगरic to generic GCM. */
	last = 0;
	अगर (encrypt && generic_gcm && !(req->assoclen + req->cryptlen))
		last = FIFOLD_TYPE_LAST1;

	/* Read GCM IV */
	append_cmd(desc, CMD_FIFO_LOAD | FIFOLD_CLASS_CLASS1 | IMMEDIATE |
			 FIFOLD_TYPE_IV | FIFOLD_TYPE_FLUSH1 | GCM_AES_IV_SIZE | last);
	/* Append Salt */
	अगर (!generic_gcm)
		append_data(desc, ctx->key + ctx->cdata.keylen, 4);
	/* Append IV */
	append_data(desc, req->iv, ivsize);
	/* End of blank commands */
पूर्ण

अटल व्योम init_chachapoly_job(काष्ठा aead_request *req,
				काष्ठा aead_edesc *edesc, bool all_contig,
				bool encrypt)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	अचिन्हित पूर्णांक assoclen = req->assoclen;
	u32 *desc = edesc->hw_desc;
	u32 ctx_iv_off = 4;

	init_aead_job(req, edesc, all_contig, encrypt);

	अगर (ivsize != CHACHAPOLY_IV_SIZE) अणु
		/* IPsec specअगरic: CONTEXT1[223:128] = अणुNONCE, IVपूर्ण */
		ctx_iv_off += 4;

		/*
		 * The associated data comes alपढ़ोy with the IV but we need
		 * to skip it when we authenticate or encrypt...
		 */
		assoclen -= ivsize;
	पूर्ण

	append_math_add_imm_u32(desc, REG3, ZERO, IMM, assoclen);

	/*
	 * For IPsec load the IV further in the same रेजिस्टर.
	 * For RFC7539 simply load the 12 bytes nonce in a single operation
	 */
	append_load_as_imm(desc, req->iv, ivsize, LDST_CLASS_1_CCB |
			   LDST_SRCDST_BYTE_CONTEXT |
			   ctx_iv_off << LDST_OFFSET_SHIFT);
पूर्ण

अटल व्योम init_authenc_job(काष्ठा aead_request *req,
			     काष्ठा aead_edesc *edesc,
			     bool all_contig, bool encrypt)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_aead_alg *alg = container_of(crypto_aead_alg(aead),
						 काष्ठा caam_aead_alg, aead);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(ctx->jrdev->parent);
	स्थिर bool ctr_mode = ((ctx->cdata.algtype & OP_ALG_AAI_MASK) ==
			       OP_ALG_AAI_CTR_MOD128);
	स्थिर bool is_rfc3686 = alg->caam.rfc3686;
	u32 *desc = edesc->hw_desc;
	u32 ivoffset = 0;

	/*
	 * AES-CTR needs to load IV in CONTEXT1 reg
	 * at an offset of 128bits (16bytes)
	 * CONTEXT1[255:128] = IV
	 */
	अगर (ctr_mode)
		ivoffset = 16;

	/*
	 * RFC3686 specअगरic:
	 *	CONTEXT1[255:128] = अणुNONCE, IV, COUNTERपूर्ण
	 */
	अगर (is_rfc3686)
		ivoffset = 16 + CTR_RFC3686_NONCE_SIZE;

	init_aead_job(req, edesc, all_contig, encrypt);

	/*
	 * अणुREG3, DPOVRDपूर्ण = assoclen, depending on whether MATH command supports
	 * having DPOVRD as destination.
	 */
	अगर (ctrlpriv->era < 3)
		append_math_add_imm_u32(desc, REG3, ZERO, IMM, req->assoclen);
	अन्यथा
		append_math_add_imm_u32(desc, DPOVRD, ZERO, IMM, req->assoclen);

	अगर (ivsize && ((is_rfc3686 && encrypt) || !alg->caam.geniv))
		append_load_as_imm(desc, req->iv, ivsize,
				   LDST_CLASS_1_CCB |
				   LDST_SRCDST_BYTE_CONTEXT |
				   (ivoffset << LDST_OFFSET_SHIFT));
पूर्ण

/*
 * Fill in skcipher job descriptor
 */
अटल व्योम init_skcipher_job(काष्ठा skcipher_request *req,
			      काष्ठा skcipher_edesc *edesc,
			      स्थिर bool encrypt)
अणु
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा device *jrdev = ctx->jrdev;
	पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);
	u32 *desc = edesc->hw_desc;
	u32 *sh_desc;
	u32 in_options = 0, out_options = 0;
	dma_addr_t src_dma, dst_dma, ptr;
	पूर्णांक len, sec4_sg_index = 0;

	prपूर्णांक_hex_dump_debug("presciv@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, req->iv, ivsize, 1);
	dev_dbg(jrdev, "asked=%d, cryptlen%d\n",
	       (पूर्णांक)edesc->src_nents > 1 ? 100 : req->cryptlen, req->cryptlen);

	caam_dump_sg("src    @" __stringअगरy(__LINE__)": ",
		     DUMP_PREFIX_ADDRESS, 16, 4, req->src,
		     edesc->src_nents > 1 ? 100 : req->cryptlen, 1);

	sh_desc = encrypt ? ctx->sh_desc_enc : ctx->sh_desc_dec;
	ptr = encrypt ? ctx->sh_desc_enc_dma : ctx->sh_desc_dec_dma;

	len = desc_len(sh_desc);
	init_job_desc_shared(desc, ptr, len, HDR_SHARE_DEFER | HDR_REVERSE);

	अगर (ivsize || edesc->mapped_src_nents > 1) अणु
		src_dma = edesc->sec4_sg_dma;
		sec4_sg_index = edesc->mapped_src_nents + !!ivsize;
		in_options = LDST_SGF;
	पूर्ण अन्यथा अणु
		src_dma = sg_dma_address(req->src);
	पूर्ण

	append_seq_in_ptr(desc, src_dma, req->cryptlen + ivsize, in_options);

	अगर (likely(req->src == req->dst)) अणु
		dst_dma = src_dma + !!ivsize * माप(काष्ठा sec4_sg_entry);
		out_options = in_options;
	पूर्ण अन्यथा अगर (!ivsize && edesc->mapped_dst_nents == 1) अणु
		dst_dma = sg_dma_address(req->dst);
	पूर्ण अन्यथा अणु
		dst_dma = edesc->sec4_sg_dma + sec4_sg_index *
			  माप(काष्ठा sec4_sg_entry);
		out_options = LDST_SGF;
	पूर्ण

	append_seq_out_ptr(desc, dst_dma, req->cryptlen + ivsize, out_options);
पूर्ण

/*
 * allocate and map the aead extended descriptor
 */
अटल काष्ठा aead_edesc *aead_edesc_alloc(काष्ठा aead_request *req,
					   पूर्णांक desc_bytes, bool *all_contig_ptr,
					   bool encrypt)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	काष्ठा caam_aead_req_ctx *rctx = aead_request_ctx(req);
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	पूर्णांक src_nents, mapped_src_nents, dst_nents = 0, mapped_dst_nents = 0;
	पूर्णांक src_len, dst_len = 0;
	काष्ठा aead_edesc *edesc;
	पूर्णांक sec4_sg_index, sec4_sg_len, sec4_sg_bytes;
	अचिन्हित पूर्णांक authsize = ctx->authsize;

	अगर (unlikely(req->dst != req->src)) अणु
		src_len = req->assoclen + req->cryptlen;
		dst_len = src_len + (encrypt ? authsize : (-authsize));

		src_nents = sg_nents_क्रम_len(req->src, src_len);
		अगर (unlikely(src_nents < 0)) अणु
			dev_err(jrdev, "Insufficient bytes (%d) in src S/G\n",
				src_len);
			वापस ERR_PTR(src_nents);
		पूर्ण

		dst_nents = sg_nents_क्रम_len(req->dst, dst_len);
		अगर (unlikely(dst_nents < 0)) अणु
			dev_err(jrdev, "Insufficient bytes (%d) in dst S/G\n",
				dst_len);
			वापस ERR_PTR(dst_nents);
		पूर्ण
	पूर्ण अन्यथा अणु
		src_len = req->assoclen + req->cryptlen +
			  (encrypt ? authsize : 0);

		src_nents = sg_nents_क्रम_len(req->src, src_len);
		अगर (unlikely(src_nents < 0)) अणु
			dev_err(jrdev, "Insufficient bytes (%d) in src S/G\n",
				src_len);
			वापस ERR_PTR(src_nents);
		पूर्ण
	पूर्ण

	अगर (likely(req->src == req->dst)) अणु
		mapped_src_nents = dma_map_sg(jrdev, req->src, src_nents,
					      DMA_BIसूचीECTIONAL);
		अगर (unlikely(!mapped_src_nents)) अणु
			dev_err(jrdev, "unable to map source\n");
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Cover also the हाल of null (zero length) input data */
		अगर (src_nents) अणु
			mapped_src_nents = dma_map_sg(jrdev, req->src,
						      src_nents, DMA_TO_DEVICE);
			अगर (unlikely(!mapped_src_nents)) अणु
				dev_err(jrdev, "unable to map source\n");
				वापस ERR_PTR(-ENOMEM);
			पूर्ण
		पूर्ण अन्यथा अणु
			mapped_src_nents = 0;
		पूर्ण

		/* Cover also the हाल of null (zero length) output data */
		अगर (dst_nents) अणु
			mapped_dst_nents = dma_map_sg(jrdev, req->dst,
						      dst_nents,
						      DMA_FROM_DEVICE);
			अगर (unlikely(!mapped_dst_nents)) अणु
				dev_err(jrdev, "unable to map destination\n");
				dma_unmap_sg(jrdev, req->src, src_nents,
					     DMA_TO_DEVICE);
				वापस ERR_PTR(-ENOMEM);
			पूर्ण
		पूर्ण अन्यथा अणु
			mapped_dst_nents = 0;
		पूर्ण
	पूर्ण

	/*
	 * HW पढ़ोs 4 S/G entries at a समय; make sure the पढ़ोs करोn't go beyond
	 * the end of the table by allocating more S/G entries.
	 */
	sec4_sg_len = mapped_src_nents > 1 ? mapped_src_nents : 0;
	अगर (mapped_dst_nents > 1)
		sec4_sg_len += pad_sg_nents(mapped_dst_nents);
	अन्यथा
		sec4_sg_len = pad_sg_nents(sec4_sg_len);

	sec4_sg_bytes = sec4_sg_len * माप(काष्ठा sec4_sg_entry);

	/* allocate space क्रम base edesc and hw desc commands, link tables */
	edesc = kzalloc(माप(*edesc) + desc_bytes + sec4_sg_bytes,
			GFP_DMA | flags);
	अगर (!edesc) अणु
		caam_unmap(jrdev, req->src, req->dst, src_nents, dst_nents, 0,
			   0, 0, 0);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	edesc->src_nents = src_nents;
	edesc->dst_nents = dst_nents;
	edesc->mapped_src_nents = mapped_src_nents;
	edesc->mapped_dst_nents = mapped_dst_nents;
	edesc->sec4_sg = (व्योम *)edesc + माप(काष्ठा aead_edesc) +
			 desc_bytes;

	rctx->edesc = edesc;

	*all_contig_ptr = !(mapped_src_nents > 1);

	sec4_sg_index = 0;
	अगर (mapped_src_nents > 1) अणु
		sg_to_sec4_sg_last(req->src, src_len,
				   edesc->sec4_sg + sec4_sg_index, 0);
		sec4_sg_index += mapped_src_nents;
	पूर्ण
	अगर (mapped_dst_nents > 1) अणु
		sg_to_sec4_sg_last(req->dst, dst_len,
				   edesc->sec4_sg + sec4_sg_index, 0);
	पूर्ण

	अगर (!sec4_sg_bytes)
		वापस edesc;

	edesc->sec4_sg_dma = dma_map_single(jrdev, edesc->sec4_sg,
					    sec4_sg_bytes, DMA_TO_DEVICE);
	अगर (dma_mapping_error(jrdev, edesc->sec4_sg_dma)) अणु
		dev_err(jrdev, "unable to map S/G table\n");
		aead_unmap(jrdev, edesc, req);
		kमुक्त(edesc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	edesc->sec4_sg_bytes = sec4_sg_bytes;

	वापस edesc;
पूर्ण

अटल पूर्णांक aead_enqueue_req(काष्ठा device *jrdev, काष्ठा aead_request *req)
अणु
	काष्ठा caam_drv_निजी_jr *jrpriv = dev_get_drvdata(jrdev);
	काष्ठा caam_aead_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा aead_edesc *edesc = rctx->edesc;
	u32 *desc = edesc->hw_desc;
	पूर्णांक ret;

	/*
	 * Only the backlog request are sent to crypto-engine since the others
	 * can be handled by CAAM, अगर मुक्त, especially since JR has up to 1024
	 * entries (more than the 10 entries from crypto-engine).
	 */
	अगर (req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)
		ret = crypto_transfer_aead_request_to_engine(jrpriv->engine,
							     req);
	अन्यथा
		ret = caam_jr_enqueue(jrdev, desc, aead_crypt_करोne, req);

	अगर ((ret != -EINPROGRESS) && (ret != -EBUSY)) अणु
		aead_unmap(jrdev, edesc, req);
		kमुक्त(rctx->edesc);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक chachapoly_crypt(काष्ठा aead_request *req, bool encrypt)
अणु
	काष्ठा aead_edesc *edesc;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	bool all_contig;
	u32 *desc;

	edesc = aead_edesc_alloc(req, CHACHAPOLY_DESC_JOB_IO_LEN, &all_contig,
				 encrypt);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	desc = edesc->hw_desc;

	init_chachapoly_job(req, edesc, all_contig, encrypt);
	prपूर्णांक_hex_dump_debug("chachapoly jobdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	वापस aead_enqueue_req(jrdev, req);
पूर्ण

अटल पूर्णांक chachapoly_encrypt(काष्ठा aead_request *req)
अणु
	वापस chachapoly_crypt(req, true);
पूर्ण

अटल पूर्णांक chachapoly_decrypt(काष्ठा aead_request *req)
अणु
	वापस chachapoly_crypt(req, false);
पूर्ण

अटल अंतरभूत पूर्णांक aead_crypt(काष्ठा aead_request *req, bool encrypt)
अणु
	काष्ठा aead_edesc *edesc;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	bool all_contig;

	/* allocate extended descriptor */
	edesc = aead_edesc_alloc(req, AUTHENC_DESC_JOB_IO_LEN,
				 &all_contig, encrypt);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	/* Create and submit job descriptor */
	init_authenc_job(req, edesc, all_contig, encrypt);

	prपूर्णांक_hex_dump_debug("aead jobdesc@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, edesc->hw_desc,
			     desc_bytes(edesc->hw_desc), 1);

	वापस aead_enqueue_req(jrdev, req);
पूर्ण

अटल पूर्णांक aead_encrypt(काष्ठा aead_request *req)
अणु
	वापस aead_crypt(req, true);
पूर्ण

अटल पूर्णांक aead_decrypt(काष्ठा aead_request *req)
अणु
	वापस aead_crypt(req, false);
पूर्ण

अटल पूर्णांक aead_करो_one_req(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा aead_request *req = aead_request_cast(areq);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा caam_aead_req_ctx *rctx = aead_request_ctx(req);
	u32 *desc = rctx->edesc->hw_desc;
	पूर्णांक ret;

	rctx->edesc->bklog = true;

	ret = caam_jr_enqueue(ctx->jrdev, desc, aead_crypt_करोne, req);

	अगर (ret != -EINPROGRESS) अणु
		aead_unmap(ctx->jrdev, rctx->edesc, req);
		kमुक्त(rctx->edesc);
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक gcm_crypt(काष्ठा aead_request *req, bool encrypt)
अणु
	काष्ठा aead_edesc *edesc;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *jrdev = ctx->jrdev;
	bool all_contig;

	/* allocate extended descriptor */
	edesc = aead_edesc_alloc(req, GCM_DESC_JOB_IO_LEN, &all_contig,
				 encrypt);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	/* Create and submit job descriptor */
	init_gcm_job(req, edesc, all_contig, encrypt);

	prपूर्णांक_hex_dump_debug("aead jobdesc@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, edesc->hw_desc,
			     desc_bytes(edesc->hw_desc), 1);

	वापस aead_enqueue_req(jrdev, req);
पूर्ण

अटल पूर्णांक gcm_encrypt(काष्ठा aead_request *req)
अणु
	वापस gcm_crypt(req, true);
पूर्ण

अटल पूर्णांक gcm_decrypt(काष्ठा aead_request *req)
अणु
	वापस gcm_crypt(req, false);
पूर्ण

अटल पूर्णांक ipsec_gcm_encrypt(काष्ठा aead_request *req)
अणु
	वापस crypto_ipsec_check_assoclen(req->assoclen) ? : gcm_encrypt(req);
पूर्ण

अटल पूर्णांक ipsec_gcm_decrypt(काष्ठा aead_request *req)
अणु
	वापस crypto_ipsec_check_assoclen(req->assoclen) ? : gcm_decrypt(req);
पूर्ण

/*
 * allocate and map the skcipher extended descriptor क्रम skcipher
 */
अटल काष्ठा skcipher_edesc *skcipher_edesc_alloc(काष्ठा skcipher_request *req,
						   पूर्णांक desc_bytes)
अणु
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा caam_skcipher_req_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा device *jrdev = ctx->jrdev;
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	पूर्णांक src_nents, mapped_src_nents, dst_nents = 0, mapped_dst_nents = 0;
	काष्ठा skcipher_edesc *edesc;
	dma_addr_t iv_dma = 0;
	u8 *iv;
	पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);
	पूर्णांक dst_sg_idx, sec4_sg_ents, sec4_sg_bytes;

	src_nents = sg_nents_क्रम_len(req->src, req->cryptlen);
	अगर (unlikely(src_nents < 0)) अणु
		dev_err(jrdev, "Insufficient bytes (%d) in src S/G\n",
			req->cryptlen);
		वापस ERR_PTR(src_nents);
	पूर्ण

	अगर (req->dst != req->src) अणु
		dst_nents = sg_nents_क्रम_len(req->dst, req->cryptlen);
		अगर (unlikely(dst_nents < 0)) अणु
			dev_err(jrdev, "Insufficient bytes (%d) in dst S/G\n",
				req->cryptlen);
			वापस ERR_PTR(dst_nents);
		पूर्ण
	पूर्ण

	अगर (likely(req->src == req->dst)) अणु
		mapped_src_nents = dma_map_sg(jrdev, req->src, src_nents,
					      DMA_BIसूचीECTIONAL);
		अगर (unlikely(!mapped_src_nents)) अणु
			dev_err(jrdev, "unable to map source\n");
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण अन्यथा अणु
		mapped_src_nents = dma_map_sg(jrdev, req->src, src_nents,
					      DMA_TO_DEVICE);
		अगर (unlikely(!mapped_src_nents)) अणु
			dev_err(jrdev, "unable to map source\n");
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		mapped_dst_nents = dma_map_sg(jrdev, req->dst, dst_nents,
					      DMA_FROM_DEVICE);
		अगर (unlikely(!mapped_dst_nents)) अणु
			dev_err(jrdev, "unable to map destination\n");
			dma_unmap_sg(jrdev, req->src, src_nents, DMA_TO_DEVICE);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	अगर (!ivsize && mapped_src_nents == 1)
		sec4_sg_ents = 0; // no need क्रम an input hw s/g table
	अन्यथा
		sec4_sg_ents = mapped_src_nents + !!ivsize;
	dst_sg_idx = sec4_sg_ents;

	/*
	 * Input, output HW S/G tables: [IV, src][dst, IV]
	 * IV entries poपूर्णांक to the same buffer
	 * If src == dst, S/G entries are reused (S/G tables overlap)
	 *
	 * HW पढ़ोs 4 S/G entries at a समय; make sure the पढ़ोs करोn't go beyond
	 * the end of the table by allocating more S/G entries. Logic:
	 * अगर (output S/G)
	 *      pad output S/G, अगर needed
	 * अन्यथा अगर (input S/G) ...
	 *      pad input S/G, अगर needed
	 */
	अगर (ivsize || mapped_dst_nents > 1) अणु
		अगर (req->src == req->dst)
			sec4_sg_ents = !!ivsize + pad_sg_nents(sec4_sg_ents);
		अन्यथा
			sec4_sg_ents += pad_sg_nents(mapped_dst_nents +
						     !!ivsize);
	पूर्ण अन्यथा अणु
		sec4_sg_ents = pad_sg_nents(sec4_sg_ents);
	पूर्ण

	sec4_sg_bytes = sec4_sg_ents * माप(काष्ठा sec4_sg_entry);

	/*
	 * allocate space क्रम base edesc and hw desc commands, link tables, IV
	 */
	edesc = kzalloc(माप(*edesc) + desc_bytes + sec4_sg_bytes + ivsize,
			GFP_DMA | flags);
	अगर (!edesc) अणु
		dev_err(jrdev, "could not allocate extended descriptor\n");
		caam_unmap(jrdev, req->src, req->dst, src_nents, dst_nents, 0,
			   0, 0, 0);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	edesc->src_nents = src_nents;
	edesc->dst_nents = dst_nents;
	edesc->mapped_src_nents = mapped_src_nents;
	edesc->mapped_dst_nents = mapped_dst_nents;
	edesc->sec4_sg_bytes = sec4_sg_bytes;
	edesc->sec4_sg = (काष्ठा sec4_sg_entry *)((u8 *)edesc->hw_desc +
						  desc_bytes);
	rctx->edesc = edesc;

	/* Make sure IV is located in a DMAable area */
	अगर (ivsize) अणु
		iv = (u8 *)edesc->sec4_sg + sec4_sg_bytes;
		स_नकल(iv, req->iv, ivsize);

		iv_dma = dma_map_single(jrdev, iv, ivsize, DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(jrdev, iv_dma)) अणु
			dev_err(jrdev, "unable to map IV\n");
			caam_unmap(jrdev, req->src, req->dst, src_nents,
				   dst_nents, 0, 0, 0, 0);
			kमुक्त(edesc);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		dma_to_sec4_sg_one(edesc->sec4_sg, iv_dma, ivsize, 0);
	पूर्ण
	अगर (dst_sg_idx)
		sg_to_sec4_sg(req->src, req->cryptlen, edesc->sec4_sg +
			      !!ivsize, 0);

	अगर (req->src != req->dst && (ivsize || mapped_dst_nents > 1))
		sg_to_sec4_sg(req->dst, req->cryptlen, edesc->sec4_sg +
			      dst_sg_idx, 0);

	अगर (ivsize)
		dma_to_sec4_sg_one(edesc->sec4_sg + dst_sg_idx +
				   mapped_dst_nents, iv_dma, ivsize, 0);

	अगर (ivsize || mapped_dst_nents > 1)
		sg_to_sec4_set_last(edesc->sec4_sg + dst_sg_idx +
				    mapped_dst_nents - 1 + !!ivsize);

	अगर (sec4_sg_bytes) अणु
		edesc->sec4_sg_dma = dma_map_single(jrdev, edesc->sec4_sg,
						    sec4_sg_bytes,
						    DMA_TO_DEVICE);
		अगर (dma_mapping_error(jrdev, edesc->sec4_sg_dma)) अणु
			dev_err(jrdev, "unable to map S/G table\n");
			caam_unmap(jrdev, req->src, req->dst, src_nents,
				   dst_nents, iv_dma, ivsize, 0, 0);
			kमुक्त(edesc);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	edesc->iv_dma = iv_dma;

	prपूर्णांक_hex_dump_debug("skcipher sec4_sg@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, edesc->sec4_sg,
			     sec4_sg_bytes, 1);

	वापस edesc;
पूर्ण

अटल पूर्णांक skcipher_करो_one_req(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(areq);
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	काष्ठा caam_skcipher_req_ctx *rctx = skcipher_request_ctx(req);
	u32 *desc = rctx->edesc->hw_desc;
	पूर्णांक ret;

	rctx->edesc->bklog = true;

	ret = caam_jr_enqueue(ctx->jrdev, desc, skcipher_crypt_करोne, req);

	अगर (ret != -EINPROGRESS) अणु
		skcipher_unmap(ctx->jrdev, rctx->edesc, req);
		kमुक्त(rctx->edesc);
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	वापस ret;
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
	काष्ठा device *jrdev = ctx->jrdev;
	काष्ठा caam_drv_निजी_jr *jrpriv = dev_get_drvdata(jrdev);
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(jrdev->parent);
	u32 *desc;
	पूर्णांक ret = 0;

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

	/* allocate extended descriptor */
	edesc = skcipher_edesc_alloc(req, DESC_JOB_IO_LEN * CAAM_CMD_SZ);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	/* Create and submit job descriptor*/
	init_skcipher_job(req, edesc, encrypt);

	prपूर्णांक_hex_dump_debug("skcipher jobdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, edesc->hw_desc,
			     desc_bytes(edesc->hw_desc), 1);

	desc = edesc->hw_desc;
	/*
	 * Only the backlog request are sent to crypto-engine since the others
	 * can be handled by CAAM, अगर मुक्त, especially since JR has up to 1024
	 * entries (more than the 10 entries from crypto-engine).
	 */
	अगर (req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)
		ret = crypto_transfer_skcipher_request_to_engine(jrpriv->engine,
								 req);
	अन्यथा
		ret = caam_jr_enqueue(jrdev, desc, skcipher_crypt_करोne, req);

	अगर ((ret != -EINPROGRESS) && (ret != -EBUSY)) अणु
		skcipher_unmap(jrdev, edesc, req);
		kमुक्त(edesc);
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
				.cra_driver_name = "cbc-aes-caam",
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
				.cra_driver_name = "cbc-3des-caam",
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
				.cra_driver_name = "cbc-des-caam",
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
				.cra_driver_name = "ctr-aes-caam",
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
				.cra_driver_name = "rfc3686-ctr-aes-caam",
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
				.cra_driver_name = "xts-aes-caam",
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
	अणु
		.skcipher = अणु
			.base = अणु
				.cra_name = "ecb(des)",
				.cra_driver_name = "ecb-des-caam",
				.cra_blocksize = DES_BLOCK_SIZE,
			पूर्ण,
			.setkey = des_skcipher_setkey,
			.encrypt = skcipher_encrypt,
			.decrypt = skcipher_decrypt,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
		पूर्ण,
		.caam.class1_alg_type = OP_ALG_ALGSEL_DES | OP_ALG_AAI_ECB,
	पूर्ण,
	अणु
		.skcipher = अणु
			.base = अणु
				.cra_name = "ecb(aes)",
				.cra_driver_name = "ecb-aes-caam",
				.cra_blocksize = AES_BLOCK_SIZE,
			पूर्ण,
			.setkey = aes_skcipher_setkey,
			.encrypt = skcipher_encrypt,
			.decrypt = skcipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
		पूर्ण,
		.caam.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_ECB,
	पूर्ण,
	अणु
		.skcipher = अणु
			.base = अणु
				.cra_name = "ecb(des3_ede)",
				.cra_driver_name = "ecb-des3-caam",
				.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
			.setkey = des3_skcipher_setkey,
			.encrypt = skcipher_encrypt,
			.decrypt = skcipher_decrypt,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
		पूर्ण,
		.caam.class1_alg_type = OP_ALG_ALGSEL_3DES | OP_ALG_AAI_ECB,
	पूर्ण,
पूर्ण;

अटल काष्ठा caam_aead_alg driver_aeads[] = अणु
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "rfc4106(gcm(aes))",
				.cra_driver_name = "rfc4106-gcm-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = rfc4106_setkey,
			.setauthsize = rfc4106_setauthsize,
			.encrypt = ipsec_gcm_encrypt,
			.decrypt = ipsec_gcm_decrypt,
			.ivsize = GCM_RFC4106_IV_SIZE,
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
				.cra_driver_name = "rfc4543-gcm-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = rfc4543_setkey,
			.setauthsize = rfc4543_setauthsize,
			.encrypt = ipsec_gcm_encrypt,
			.decrypt = ipsec_gcm_decrypt,
			.ivsize = GCM_RFC4543_IV_SIZE,
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
				.cra_driver_name = "gcm-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = gcm_setkey,
			.setauthsize = gcm_setauthsize,
			.encrypt = gcm_encrypt,
			.decrypt = gcm_decrypt,
			.ivsize = GCM_AES_IV_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_GCM,
			.nodkp = true,
		पूर्ण,
	पूर्ण,
	/* single-pass ipsec_esp descriptor */
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(md5),"
					    "ecb(cipher_null))",
				.cra_driver_name = "authenc-hmac-md5-"
						   "ecb-cipher_null-caam",
				.cra_blocksize = शून्य_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = शून्य_IV_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class2_alg_type = OP_ALG_ALGSEL_MD5 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),"
					    "ecb(cipher_null))",
				.cra_driver_name = "authenc-hmac-sha1-"
						   "ecb-cipher_null-caam",
				.cra_blocksize = शून्य_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = शून्य_IV_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class2_alg_type = OP_ALG_ALGSEL_SHA1 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha224),"
					    "ecb(cipher_null))",
				.cra_driver_name = "authenc-hmac-sha224-"
						   "ecb-cipher_null-caam",
				.cra_blocksize = शून्य_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = शून्य_IV_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class2_alg_type = OP_ALG_ALGSEL_SHA224 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha256),"
					    "ecb(cipher_null))",
				.cra_driver_name = "authenc-hmac-sha256-"
						   "ecb-cipher_null-caam",
				.cra_blocksize = शून्य_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = शून्य_IV_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class2_alg_type = OP_ALG_ALGSEL_SHA256 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha384),"
					    "ecb(cipher_null))",
				.cra_driver_name = "authenc-hmac-sha384-"
						   "ecb-cipher_null-caam",
				.cra_blocksize = शून्य_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = शून्य_IV_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class2_alg_type = OP_ALG_ALGSEL_SHA384 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha512),"
					    "ecb(cipher_null))",
				.cra_driver_name = "authenc-hmac-sha512-"
						   "ecb-cipher_null-caam",
				.cra_blocksize = शून्य_BLOCK_SIZE,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = शून्य_IV_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class2_alg_type = OP_ALG_ALGSEL_SHA512 |
					   OP_ALG_AAI_HMAC_PRECOMP,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(md5),cbc(aes))",
				.cra_driver_name = "authenc-hmac-md5-"
						   "cbc-aes-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(md5),"
					    "cbc(aes)))",
				.cra_driver_name = "echainiv-authenc-hmac-md5-"
						   "cbc-aes-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha1-"
						   "cbc-aes-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha1),"
					    "cbc(aes)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha1-cbc-aes-caam",
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
						   "cbc-aes-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha224),"
					    "cbc(aes)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha224-cbc-aes-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha256),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha256-"
						   "cbc-aes-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha256),"
					    "cbc(aes)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha256-cbc-aes-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha384),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha384-"
						   "cbc-aes-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha384),"
					    "cbc(aes)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha384-cbc-aes-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha512),cbc(aes))",
				.cra_driver_name = "authenc-hmac-sha512-"
						   "cbc-aes-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha512),"
					    "cbc(aes)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha512-cbc-aes-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(md5),cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-md5-"
						   "cbc-des3_ede-caam",
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
						   "cbc-des3_ede-caam",
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
						   "cbc-des3_ede-caam",
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
						   "cbc-des3_ede-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha224),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha224-"
						   "cbc-des3_ede-caam",
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
						   "cbc-des3_ede-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha256),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha256-"
						   "cbc-des3_ede-caam",
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
						   "cbc-des3_ede-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha384),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha384-"
						   "cbc-des3_ede-caam",
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
						   "cbc-des3_ede-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha512),"
					    "cbc(des3_ede))",
				.cra_driver_name = "authenc-hmac-sha512-"
						   "cbc-des3_ede-caam",
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
						   "cbc-des3_ede-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(md5),cbc(des))",
				.cra_driver_name = "authenc-hmac-md5-"
						   "cbc-des-caam",
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
						   "cbc-des-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),cbc(des))",
				.cra_driver_name = "authenc-hmac-sha1-"
						   "cbc-des-caam",
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
						   "hmac-sha1-cbc-des-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha224),cbc(des))",
				.cra_driver_name = "authenc-hmac-sha224-"
						   "cbc-des-caam",
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
						   "hmac-sha224-cbc-des-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha256),cbc(des))",
				.cra_driver_name = "authenc-hmac-sha256-"
						   "cbc-des-caam",
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
						   "hmac-sha256-cbc-des-caam",
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
						   "cbc-des-caam",
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
						   "hmac-sha384-cbc-des-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha512),cbc(des))",
				.cra_driver_name = "authenc-hmac-sha512-"
						   "cbc-des-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "echainiv(authenc(hmac(sha512),"
					    "cbc(des)))",
				.cra_driver_name = "echainiv-authenc-"
						   "hmac-sha512-cbc-des-caam",
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
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(md5),"
					    "rfc3686(ctr(aes)))",
				.cra_driver_name = "authenc-hmac-md5-"
						   "rfc3686-ctr-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES |
					   OP_ALG_AAI_CTR_MOD128,
			.class2_alg_type = OP_ALG_ALGSEL_MD5 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.rfc3686 = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "seqiv(authenc("
					    "hmac(md5),rfc3686(ctr(aes))))",
				.cra_driver_name = "seqiv-authenc-hmac-md5-"
						   "rfc3686-ctr-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES |
					   OP_ALG_AAI_CTR_MOD128,
			.class2_alg_type = OP_ALG_ALGSEL_MD5 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.rfc3686 = true,
			.geniv = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),"
					    "rfc3686(ctr(aes)))",
				.cra_driver_name = "authenc-hmac-sha1-"
						   "rfc3686-ctr-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES |
					   OP_ALG_AAI_CTR_MOD128,
			.class2_alg_type = OP_ALG_ALGSEL_SHA1 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.rfc3686 = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "seqiv(authenc("
					    "hmac(sha1),rfc3686(ctr(aes))))",
				.cra_driver_name = "seqiv-authenc-hmac-sha1-"
						   "rfc3686-ctr-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES |
					   OP_ALG_AAI_CTR_MOD128,
			.class2_alg_type = OP_ALG_ALGSEL_SHA1 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.rfc3686 = true,
			.geniv = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha224),"
					    "rfc3686(ctr(aes)))",
				.cra_driver_name = "authenc-hmac-sha224-"
						   "rfc3686-ctr-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES |
					   OP_ALG_AAI_CTR_MOD128,
			.class2_alg_type = OP_ALG_ALGSEL_SHA224 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.rfc3686 = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "seqiv(authenc("
					    "hmac(sha224),rfc3686(ctr(aes))))",
				.cra_driver_name = "seqiv-authenc-hmac-sha224-"
						   "rfc3686-ctr-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES |
					   OP_ALG_AAI_CTR_MOD128,
			.class2_alg_type = OP_ALG_ALGSEL_SHA224 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.rfc3686 = true,
			.geniv = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha256),"
					    "rfc3686(ctr(aes)))",
				.cra_driver_name = "authenc-hmac-sha256-"
						   "rfc3686-ctr-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES |
					   OP_ALG_AAI_CTR_MOD128,
			.class2_alg_type = OP_ALG_ALGSEL_SHA256 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.rfc3686 = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "seqiv(authenc(hmac(sha256),"
					    "rfc3686(ctr(aes))))",
				.cra_driver_name = "seqiv-authenc-hmac-sha256-"
						   "rfc3686-ctr-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES |
					   OP_ALG_AAI_CTR_MOD128,
			.class2_alg_type = OP_ALG_ALGSEL_SHA256 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.rfc3686 = true,
			.geniv = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha384),"
					    "rfc3686(ctr(aes)))",
				.cra_driver_name = "authenc-hmac-sha384-"
						   "rfc3686-ctr-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES |
					   OP_ALG_AAI_CTR_MOD128,
			.class2_alg_type = OP_ALG_ALGSEL_SHA384 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.rfc3686 = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "seqiv(authenc(hmac(sha384),"
					    "rfc3686(ctr(aes))))",
				.cra_driver_name = "seqiv-authenc-hmac-sha384-"
						   "rfc3686-ctr-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES |
					   OP_ALG_AAI_CTR_MOD128,
			.class2_alg_type = OP_ALG_ALGSEL_SHA384 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.rfc3686 = true,
			.geniv = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha512),"
					    "rfc3686(ctr(aes)))",
				.cra_driver_name = "authenc-hmac-sha512-"
						   "rfc3686-ctr-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES |
					   OP_ALG_AAI_CTR_MOD128,
			.class2_alg_type = OP_ALG_ALGSEL_SHA512 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.rfc3686 = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "seqiv(authenc(hmac(sha512),"
					    "rfc3686(ctr(aes))))",
				.cra_driver_name = "seqiv-authenc-hmac-sha512-"
						   "rfc3686-ctr-aes-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_AES |
					   OP_ALG_AAI_CTR_MOD128,
			.class2_alg_type = OP_ALG_ALGSEL_SHA512 |
					   OP_ALG_AAI_HMAC_PRECOMP,
			.rfc3686 = true,
			.geniv = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "rfc7539(chacha20,poly1305)",
				.cra_driver_name = "rfc7539-chacha20-poly1305-"
						   "caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = chachapoly_setkey,
			.setauthsize = chachapoly_setauthsize,
			.encrypt = chachapoly_encrypt,
			.decrypt = chachapoly_decrypt,
			.ivsize = CHACHAPOLY_IV_SIZE,
			.maxauthsize = POLY1305_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_CHACHA20 |
					   OP_ALG_AAI_AEAD,
			.class2_alg_type = OP_ALG_ALGSEL_POLY1305 |
					   OP_ALG_AAI_AEAD,
			.nodkp = true,
		पूर्ण,
	पूर्ण,
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "rfc7539esp(chacha20,poly1305)",
				.cra_driver_name = "rfc7539esp-chacha20-"
						   "poly1305-caam",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = chachapoly_setkey,
			.setauthsize = chachapoly_setauthsize,
			.encrypt = chachapoly_encrypt,
			.decrypt = chachapoly_decrypt,
			.ivsize = 8,
			.maxauthsize = POLY1305_DIGEST_SIZE,
		पूर्ण,
		.caam = अणु
			.class1_alg_type = OP_ALG_ALGSEL_CHACHA20 |
					   OP_ALG_AAI_AEAD,
			.class2_alg_type = OP_ALG_ALGSEL_POLY1305 |
					   OP_ALG_AAI_AEAD,
			.nodkp = true,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक caam_init_common(काष्ठा caam_ctx *ctx, काष्ठा caam_alg_entry *caam,
			    bool uses_dkp)
अणु
	dma_addr_t dma_addr;
	काष्ठा caam_drv_निजी *priv;
	स्थिर माप_प्रकार sh_desc_enc_offset = दुरत्व(काष्ठा caam_ctx,
						   sh_desc_enc);

	ctx->jrdev = caam_jr_alloc();
	अगर (IS_ERR(ctx->jrdev)) अणु
		pr_err("Job Ring Device allocation for transform failed\n");
		वापस PTR_ERR(ctx->jrdev);
	पूर्ण

	priv = dev_get_drvdata(ctx->jrdev->parent);
	अगर (priv->era >= 6 && uses_dkp)
		ctx->dir = DMA_BIसूचीECTIONAL;
	अन्यथा
		ctx->dir = DMA_TO_DEVICE;

	dma_addr = dma_map_single_attrs(ctx->jrdev, ctx->sh_desc_enc,
					दुरत्व(काष्ठा caam_ctx,
						 sh_desc_enc_dma) -
					sh_desc_enc_offset,
					ctx->dir, DMA_ATTR_SKIP_CPU_SYNC);
	अगर (dma_mapping_error(ctx->jrdev, dma_addr)) अणु
		dev_err(ctx->jrdev, "unable to map key, shared descriptors\n");
		caam_jr_मुक्त(ctx->jrdev);
		वापस -ENOMEM;
	पूर्ण

	ctx->sh_desc_enc_dma = dma_addr;
	ctx->sh_desc_dec_dma = dma_addr + दुरत्व(काष्ठा caam_ctx,
						   sh_desc_dec) -
					sh_desc_enc_offset;
	ctx->key_dma = dma_addr + दुरत्व(काष्ठा caam_ctx, key) -
					sh_desc_enc_offset;

	/* copy descriptor header ढाँचा value */
	ctx->cdata.algtype = OP_TYPE_CLASS1_ALG | caam->class1_alg_type;
	ctx->adata.algtype = OP_TYPE_CLASS2_ALG | caam->class2_alg_type;

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

	ctx->enginectx.op.करो_one_request = skcipher_करो_one_req;

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
	पूर्ण अन्यथा अणु
		crypto_skcipher_set_reqsize(tfm, माप(काष्ठा caam_skcipher_req_ctx));
	पूर्ण

	ret = caam_init_common(ctx, &caam_alg->caam, false);
	अगर (ret && ctx->fallback)
		crypto_मुक्त_skcipher(ctx->fallback);

	वापस ret;
पूर्ण

अटल पूर्णांक caam_aead_init(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_alg *alg = crypto_aead_alg(tfm);
	काष्ठा caam_aead_alg *caam_alg =
		 container_of(alg, काष्ठा caam_aead_alg, aead);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_aead_set_reqsize(tfm, माप(काष्ठा caam_aead_req_ctx));

	ctx->enginectx.op.करो_one_request = aead_करो_one_req;

	वापस caam_init_common(ctx, &caam_alg->caam, !caam_alg->caam.nodkp);
पूर्ण

अटल व्योम caam_निकास_common(काष्ठा caam_ctx *ctx)
अणु
	dma_unmap_single_attrs(ctx->jrdev, ctx->sh_desc_enc_dma,
			       दुरत्व(काष्ठा caam_ctx, sh_desc_enc_dma) -
			       दुरत्व(काष्ठा caam_ctx, sh_desc_enc),
			       ctx->dir, DMA_ATTR_SKIP_CPU_SYNC);
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

व्योम caam_algapi_निकास(व्योम)
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

पूर्णांक caam_algapi_init(काष्ठा device *ctrldev)
अणु
	काष्ठा caam_drv_निजी *priv = dev_get_drvdata(ctrldev);
	पूर्णांक i = 0, err = 0;
	u32 aes_vid, aes_inst, des_inst, md_vid, md_inst, ccha_inst, ptha_inst;
	अचिन्हित पूर्णांक md_limit = SHA512_DIGEST_SIZE;
	bool रेजिस्टरed = false, gcm_support;

	/*
	 * Register crypto algorithms the device supports.
	 * First, detect presence and attributes of DES, AES, and MD blocks.
	 */
	अगर (priv->era < 10) अणु
		u32 cha_vid, cha_inst, aes_rn;

		cha_vid = rd_reg32(&priv->ctrl->perfmon.cha_id_ls);
		aes_vid = cha_vid & CHA_ID_LS_AES_MASK;
		md_vid = (cha_vid & CHA_ID_LS_MD_MASK) >> CHA_ID_LS_MD_SHIFT;

		cha_inst = rd_reg32(&priv->ctrl->perfmon.cha_num_ls);
		des_inst = (cha_inst & CHA_ID_LS_DES_MASK) >>
			   CHA_ID_LS_DES_SHIFT;
		aes_inst = cha_inst & CHA_ID_LS_AES_MASK;
		md_inst = (cha_inst & CHA_ID_LS_MD_MASK) >> CHA_ID_LS_MD_SHIFT;
		ccha_inst = 0;
		ptha_inst = 0;

		aes_rn = rd_reg32(&priv->ctrl->perfmon.cha_rev_ls) &
			 CHA_ID_LS_AES_MASK;
		gcm_support = !(aes_vid == CHA_VER_VID_AES_LP && aes_rn < 8);
	पूर्ण अन्यथा अणु
		u32 aesa, mdha;

		aesa = rd_reg32(&priv->ctrl->vreg.aesa);
		mdha = rd_reg32(&priv->ctrl->vreg.mdha);

		aes_vid = (aesa & CHA_VER_VID_MASK) >> CHA_VER_VID_SHIFT;
		md_vid = (mdha & CHA_VER_VID_MASK) >> CHA_VER_VID_SHIFT;

		des_inst = rd_reg32(&priv->ctrl->vreg.desa) & CHA_VER_NUM_MASK;
		aes_inst = aesa & CHA_VER_NUM_MASK;
		md_inst = mdha & CHA_VER_NUM_MASK;
		ccha_inst = rd_reg32(&priv->ctrl->vreg.ccha) & CHA_VER_NUM_MASK;
		ptha_inst = rd_reg32(&priv->ctrl->vreg.ptha) & CHA_VER_NUM_MASK;

		gcm_support = aesa & CHA_VER_MISC_AES_GCM;
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

		/*
		 * Check support क्रम AES modes not available
		 * on LP devices.
		 */
		अगर (aes_vid == CHA_VER_VID_AES_LP &&
		    (t_alg->caam.class1_alg_type & OP_ALG_AAI_MASK) ==
		    OP_ALG_AAI_XTS)
			जारी;

		caam_skcipher_alg_init(t_alg);

		err = crypto_रेजिस्टर_skcipher(&t_alg->skcipher);
		अगर (err) अणु
			pr_warn("%s alg registration failed\n",
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

		/* Skip CHACHA20 algorithms अगर not supported by device */
		अगर (c1_alg_sel == OP_ALG_ALGSEL_CHACHA20 && !ccha_inst)
			जारी;

		/* Skip POLY1305 algorithms अगर not supported by device */
		अगर (c2_alg_sel == OP_ALG_ALGSEL_POLY1305 && !ptha_inst)
			जारी;

		/* Skip GCM algorithms अगर not supported by device */
		अगर (c1_alg_sel == OP_ALG_ALGSEL_AES &&
		    alg_aai == OP_ALG_AAI_GCM && !gcm_support)
			जारी;

		/*
		 * Skip algorithms requiring message digests
		 * अगर MD or MD size is not supported by device.
		 */
		अगर (is_mdha(c2_alg_sel) &&
		    (!md_inst || t_alg->aead.maxauthsize > md_limit))
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
		pr_info("caam algorithms registered in /proc/crypto\n");

	वापस err;
पूर्ण
