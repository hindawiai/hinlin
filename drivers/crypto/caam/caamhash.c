<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * caam - Freescale FSL CAAM support क्रम ahash functions of crypto API
 *
 * Copyright 2011 Freescale Semiconductor, Inc.
 * Copyright 2018-2019 NXP
 *
 * Based on caamalg.c crypto API driver.
 *
 * relationship of digest job descriptor or first job descriptor after init to
 * shared descriptors:
 *
 * ---------------                     ---------------
 * | JobDesc #1  |-------------------->|  ShareDesc  |
 * | *(packet 1) |                     |  (hashKey)  |
 * ---------------                     | (operation) |
 *                                     ---------------
 *
 * relationship of subsequent job descriptors to shared descriptors:
 *
 * ---------------                     ---------------
 * | JobDesc #2  |-------------------->|  ShareDesc  |
 * | *(packet 2) |      |------------->|  (hashKey)  |
 * ---------------      |    |-------->| (operation) |
 *       .              |    |         | (load ctx2) |
 *       .              |    |         ---------------
 * ---------------      |    |
 * | JobDesc #3  |------|    |
 * | *(packet 3) |           |
 * ---------------           |
 *       .                   |
 *       .                   |
 * ---------------           |
 * | JobDesc #4  |------------
 * | *(packet 4) |
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
#समावेश "caamhash_desc.h"
#समावेश <crypto/engine.h>

#घोषणा CAAM_CRA_PRIORITY		3000

/* max hash key is max split key size */
#घोषणा CAAM_MAX_HASH_KEY_SIZE		(SHA512_DIGEST_SIZE * 2)

#घोषणा CAAM_MAX_HASH_BLOCK_SIZE	SHA512_BLOCK_SIZE
#घोषणा CAAM_MAX_HASH_DIGEST_SIZE	SHA512_DIGEST_SIZE

#घोषणा DESC_HASH_MAX_USED_BYTES	(DESC_AHASH_FINAL_LEN + \
					 CAAM_MAX_HASH_KEY_SIZE)
#घोषणा DESC_HASH_MAX_USED_LEN		(DESC_HASH_MAX_USED_BYTES / CAAM_CMD_SZ)

/* caam context sizes क्रम hashes: running digest + 8 */
#घोषणा HASH_MSG_LEN			8
#घोषणा MAX_CTX_LEN			(HASH_MSG_LEN + SHA512_DIGEST_SIZE)

अटल काष्ठा list_head hash_list;

/* ahash per-session context */
काष्ठा caam_hash_ctx अणु
	काष्ठा crypto_engine_ctx enginectx;
	u32 sh_desc_update[DESC_HASH_MAX_USED_LEN] ____cacheline_aligned;
	u32 sh_desc_update_first[DESC_HASH_MAX_USED_LEN] ____cacheline_aligned;
	u32 sh_desc_fin[DESC_HASH_MAX_USED_LEN] ____cacheline_aligned;
	u32 sh_desc_digest[DESC_HASH_MAX_USED_LEN] ____cacheline_aligned;
	u8 key[CAAM_MAX_HASH_KEY_SIZE] ____cacheline_aligned;
	dma_addr_t sh_desc_update_dma ____cacheline_aligned;
	dma_addr_t sh_desc_update_first_dma;
	dma_addr_t sh_desc_fin_dma;
	dma_addr_t sh_desc_digest_dma;
	क्रमागत dma_data_direction dir;
	क्रमागत dma_data_direction key_dir;
	काष्ठा device *jrdev;
	पूर्णांक ctx_len;
	काष्ठा alginfo adata;
पूर्ण;

/* ahash state */
काष्ठा caam_hash_state अणु
	dma_addr_t buf_dma;
	dma_addr_t ctx_dma;
	पूर्णांक ctx_dma_len;
	u8 buf[CAAM_MAX_HASH_BLOCK_SIZE] ____cacheline_aligned;
	पूर्णांक buflen;
	पूर्णांक next_buflen;
	u8 caam_ctx[MAX_CTX_LEN] ____cacheline_aligned;
	पूर्णांक (*update)(काष्ठा ahash_request *req) ____cacheline_aligned;
	पूर्णांक (*final)(काष्ठा ahash_request *req);
	पूर्णांक (*finup)(काष्ठा ahash_request *req);
	काष्ठा ahash_edesc *edesc;
	व्योम (*ahash_op_करोne)(काष्ठा device *jrdev, u32 *desc, u32 err,
			      व्योम *context);
पूर्ण;

काष्ठा caam_export_state अणु
	u8 buf[CAAM_MAX_HASH_BLOCK_SIZE];
	u8 caam_ctx[MAX_CTX_LEN];
	पूर्णांक buflen;
	पूर्णांक (*update)(काष्ठा ahash_request *req);
	पूर्णांक (*final)(काष्ठा ahash_request *req);
	पूर्णांक (*finup)(काष्ठा ahash_request *req);
पूर्ण;

अटल अंतरभूत bool is_cmac_aes(u32 algtype)
अणु
	वापस (algtype & (OP_ALG_ALGSEL_MASK | OP_ALG_AAI_MASK)) ==
	       (OP_ALG_ALGSEL_AES | OP_ALG_AAI_CMAC);
पूर्ण
/* Common job descriptor seq in/out ptr routines */

/* Map state->caam_ctx, and append seq_out_ptr command that poपूर्णांकs to it */
अटल अंतरभूत पूर्णांक map_seq_out_ptr_ctx(u32 *desc, काष्ठा device *jrdev,
				      काष्ठा caam_hash_state *state,
				      पूर्णांक ctx_len)
अणु
	state->ctx_dma_len = ctx_len;
	state->ctx_dma = dma_map_single(jrdev, state->caam_ctx,
					ctx_len, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(jrdev, state->ctx_dma)) अणु
		dev_err(jrdev, "unable to map ctx\n");
		state->ctx_dma = 0;
		वापस -ENOMEM;
	पूर्ण

	append_seq_out_ptr(desc, state->ctx_dma, ctx_len, 0);

	वापस 0;
पूर्ण

/* Map current buffer in state (अगर length > 0) and put it in link table */
अटल अंतरभूत पूर्णांक buf_map_to_sec4_sg(काष्ठा device *jrdev,
				     काष्ठा sec4_sg_entry *sec4_sg,
				     काष्ठा caam_hash_state *state)
अणु
	पूर्णांक buflen = state->buflen;

	अगर (!buflen)
		वापस 0;

	state->buf_dma = dma_map_single(jrdev, state->buf, buflen,
					DMA_TO_DEVICE);
	अगर (dma_mapping_error(jrdev, state->buf_dma)) अणु
		dev_err(jrdev, "unable to map buf\n");
		state->buf_dma = 0;
		वापस -ENOMEM;
	पूर्ण

	dma_to_sec4_sg_one(sec4_sg, state->buf_dma, buflen, 0);

	वापस 0;
पूर्ण

/* Map state->caam_ctx, and add it to link table */
अटल अंतरभूत पूर्णांक ctx_map_to_sec4_sg(काष्ठा device *jrdev,
				     काष्ठा caam_hash_state *state, पूर्णांक ctx_len,
				     काष्ठा sec4_sg_entry *sec4_sg, u32 flag)
अणु
	state->ctx_dma_len = ctx_len;
	state->ctx_dma = dma_map_single(jrdev, state->caam_ctx, ctx_len, flag);
	अगर (dma_mapping_error(jrdev, state->ctx_dma)) अणु
		dev_err(jrdev, "unable to map ctx\n");
		state->ctx_dma = 0;
		वापस -ENOMEM;
	पूर्ण

	dma_to_sec4_sg_one(sec4_sg, state->ctx_dma, ctx_len, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ahash_set_sh_desc(काष्ठा crypto_ahash *ahash)
अणु
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा device *jrdev = ctx->jrdev;
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(jrdev->parent);
	u32 *desc;

	ctx->adata.key_virt = ctx->key;

	/* ahash_update shared descriptor */
	desc = ctx->sh_desc_update;
	cnstr_shdsc_ahash(desc, &ctx->adata, OP_ALG_AS_UPDATE, ctx->ctx_len,
			  ctx->ctx_len, true, ctrlpriv->era);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_update_dma,
				   desc_bytes(desc), ctx->dir);

	prपूर्णांक_hex_dump_debug("ahash update shdesc@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	/* ahash_update_first shared descriptor */
	desc = ctx->sh_desc_update_first;
	cnstr_shdsc_ahash(desc, &ctx->adata, OP_ALG_AS_INIT, ctx->ctx_len,
			  ctx->ctx_len, false, ctrlpriv->era);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_update_first_dma,
				   desc_bytes(desc), ctx->dir);
	prपूर्णांक_hex_dump_debug("ahash update first shdesc@"__stringअगरy(__LINE__)
			     ": ", DUMP_PREFIX_ADDRESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	/* ahash_final shared descriptor */
	desc = ctx->sh_desc_fin;
	cnstr_shdsc_ahash(desc, &ctx->adata, OP_ALG_AS_FINALIZE, digestsize,
			  ctx->ctx_len, true, ctrlpriv->era);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_fin_dma,
				   desc_bytes(desc), ctx->dir);

	prपूर्णांक_hex_dump_debug("ahash final shdesc@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	/* ahash_digest shared descriptor */
	desc = ctx->sh_desc_digest;
	cnstr_shdsc_ahash(desc, &ctx->adata, OP_ALG_AS_INITFINAL, digestsize,
			  ctx->ctx_len, false, ctrlpriv->era);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_digest_dma,
				   desc_bytes(desc), ctx->dir);

	prपूर्णांक_hex_dump_debug("ahash digest shdesc@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	वापस 0;
पूर्ण

अटल पूर्णांक axcbc_set_sh_desc(काष्ठा crypto_ahash *ahash)
अणु
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा device *jrdev = ctx->jrdev;
	u32 *desc;

	/* shared descriptor क्रम ahash_update */
	desc = ctx->sh_desc_update;
	cnstr_shdsc_sk_hash(desc, &ctx->adata, OP_ALG_AS_UPDATE,
			    ctx->ctx_len, ctx->ctx_len);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_update_dma,
				   desc_bytes(desc), ctx->dir);
	prपूर्णांक_hex_dump_debug("axcbc update shdesc@" __stringअगरy(__LINE__)" : ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	/* shared descriptor क्रम ahash_अणुfinal,finupपूर्ण */
	desc = ctx->sh_desc_fin;
	cnstr_shdsc_sk_hash(desc, &ctx->adata, OP_ALG_AS_FINALIZE,
			    digestsize, ctx->ctx_len);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_fin_dma,
				   desc_bytes(desc), ctx->dir);
	prपूर्णांक_hex_dump_debug("axcbc finup shdesc@" __stringअगरy(__LINE__)" : ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	/* key is immediate data क्रम INIT and INITFINAL states */
	ctx->adata.key_virt = ctx->key;

	/* shared descriptor क्रम first invocation of ahash_update */
	desc = ctx->sh_desc_update_first;
	cnstr_shdsc_sk_hash(desc, &ctx->adata, OP_ALG_AS_INIT, ctx->ctx_len,
			    ctx->ctx_len);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_update_first_dma,
				   desc_bytes(desc), ctx->dir);
	prपूर्णांक_hex_dump_debug("axcbc update first shdesc@" __stringअगरy(__LINE__)
			     " : ", DUMP_PREFIX_ADDRESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	/* shared descriptor क्रम ahash_digest */
	desc = ctx->sh_desc_digest;
	cnstr_shdsc_sk_hash(desc, &ctx->adata, OP_ALG_AS_INITFINAL,
			    digestsize, ctx->ctx_len);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_digest_dma,
				   desc_bytes(desc), ctx->dir);
	prपूर्णांक_hex_dump_debug("axcbc digest shdesc@" __stringअगरy(__LINE__)" : ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
	वापस 0;
पूर्ण

अटल पूर्णांक acmac_set_sh_desc(काष्ठा crypto_ahash *ahash)
अणु
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा device *jrdev = ctx->jrdev;
	u32 *desc;

	/* shared descriptor क्रम ahash_update */
	desc = ctx->sh_desc_update;
	cnstr_shdsc_sk_hash(desc, &ctx->adata, OP_ALG_AS_UPDATE,
			    ctx->ctx_len, ctx->ctx_len);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_update_dma,
				   desc_bytes(desc), ctx->dir);
	prपूर्णांक_hex_dump_debug("acmac update shdesc@" __stringअगरy(__LINE__)" : ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	/* shared descriptor क्रम ahash_अणुfinal,finupपूर्ण */
	desc = ctx->sh_desc_fin;
	cnstr_shdsc_sk_hash(desc, &ctx->adata, OP_ALG_AS_FINALIZE,
			    digestsize, ctx->ctx_len);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_fin_dma,
				   desc_bytes(desc), ctx->dir);
	prपूर्णांक_hex_dump_debug("acmac finup shdesc@" __stringअगरy(__LINE__)" : ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	/* shared descriptor क्रम first invocation of ahash_update */
	desc = ctx->sh_desc_update_first;
	cnstr_shdsc_sk_hash(desc, &ctx->adata, OP_ALG_AS_INIT, ctx->ctx_len,
			    ctx->ctx_len);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_update_first_dma,
				   desc_bytes(desc), ctx->dir);
	prपूर्णांक_hex_dump_debug("acmac update first shdesc@" __stringअगरy(__LINE__)
			     " : ", DUMP_PREFIX_ADDRESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	/* shared descriptor क्रम ahash_digest */
	desc = ctx->sh_desc_digest;
	cnstr_shdsc_sk_hash(desc, &ctx->adata, OP_ALG_AS_INITFINAL,
			    digestsize, ctx->ctx_len);
	dma_sync_single_क्रम_device(jrdev, ctx->sh_desc_digest_dma,
				   desc_bytes(desc), ctx->dir);
	prपूर्णांक_hex_dump_debug("acmac digest shdesc@" __stringअगरy(__LINE__)" : ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc,
			     desc_bytes(desc), 1);

	वापस 0;
पूर्ण

/* Digest hash size अगर it is too large */
अटल पूर्णांक hash_digest_key(काष्ठा caam_hash_ctx *ctx, u32 *keylen, u8 *key,
			   u32 digestsize)
अणु
	काष्ठा device *jrdev = ctx->jrdev;
	u32 *desc;
	काष्ठा split_key_result result;
	dma_addr_t key_dma;
	पूर्णांक ret;

	desc = kदो_स्मृति(CAAM_CMD_SZ * 8 + CAAM_PTR_SZ * 2, GFP_KERNEL | GFP_DMA);
	अगर (!desc) अणु
		dev_err(jrdev, "unable to allocate key input memory\n");
		वापस -ENOMEM;
	पूर्ण

	init_job_desc(desc, 0);

	key_dma = dma_map_single(jrdev, key, *keylen, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(jrdev, key_dma)) अणु
		dev_err(jrdev, "unable to map key memory\n");
		kमुक्त(desc);
		वापस -ENOMEM;
	पूर्ण

	/* Job descriptor to perक्रमm unkeyed hash on key_in */
	append_operation(desc, ctx->adata.algtype | OP_ALG_ENCRYPT |
			 OP_ALG_AS_INITFINAL);
	append_seq_in_ptr(desc, key_dma, *keylen, 0);
	append_seq_fअगरo_load(desc, *keylen, FIFOLD_CLASS_CLASS2 |
			     FIFOLD_TYPE_LAST2 | FIFOLD_TYPE_MSG);
	append_seq_out_ptr(desc, key_dma, digestsize, 0);
	append_seq_store(desc, digestsize, LDST_CLASS_2_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);

	prपूर्णांक_hex_dump_debug("key_in@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, *keylen, 1);
	prपूर्णांक_hex_dump_debug("jobdesc@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	result.err = 0;
	init_completion(&result.completion);

	ret = caam_jr_enqueue(jrdev, desc, split_key_करोne, &result);
	अगर (ret == -EINPROGRESS) अणु
		/* in progress */
		रुको_क्रम_completion(&result.completion);
		ret = result.err;

		prपूर्णांक_hex_dump_debug("digested key@"__stringअगरy(__LINE__)": ",
				     DUMP_PREFIX_ADDRESS, 16, 4, key,
				     digestsize, 1);
	पूर्ण
	dma_unmap_single(jrdev, key_dma, *keylen, DMA_BIसूचीECTIONAL);

	*keylen = digestsize;

	kमुक्त(desc);

	वापस ret;
पूर्ण

अटल पूर्णांक ahash_setkey(काष्ठा crypto_ahash *ahash,
			स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा device *jrdev = ctx->jrdev;
	पूर्णांक blocksize = crypto_tfm_alg_blocksize(&ahash->base);
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(ctx->jrdev->parent);
	पूर्णांक ret;
	u8 *hashed_key = शून्य;

	dev_dbg(jrdev, "keylen %d\n", keylen);

	अगर (keylen > blocksize) अणु
		hashed_key = kmemdup(key, keylen, GFP_KERNEL | GFP_DMA);
		अगर (!hashed_key)
			वापस -ENOMEM;
		ret = hash_digest_key(ctx, &keylen, hashed_key, digestsize);
		अगर (ret)
			जाओ bad_मुक्त_key;
		key = hashed_key;
	पूर्ण

	/*
	 * If DKP is supported, use it in the shared descriptor to generate
	 * the split key.
	 */
	अगर (ctrlpriv->era >= 6) अणु
		ctx->adata.key_अंतरभूत = true;
		ctx->adata.keylen = keylen;
		ctx->adata.keylen_pad = split_key_len(ctx->adata.algtype &
						      OP_ALG_ALGSEL_MASK);

		अगर (ctx->adata.keylen_pad > CAAM_MAX_HASH_KEY_SIZE)
			जाओ bad_मुक्त_key;

		स_नकल(ctx->key, key, keylen);

		/*
		 * In हाल |user key| > |derived key|, using DKP<imm,imm>
		 * would result in invalid opcodes (last bytes of user key) in
		 * the resulting descriptor. Use DKP<ptr,imm> instead => both
		 * भव and dma key addresses are needed.
		 */
		अगर (keylen > ctx->adata.keylen_pad)
			dma_sync_single_क्रम_device(ctx->jrdev,
						   ctx->adata.key_dma,
						   ctx->adata.keylen_pad,
						   DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		ret = gen_split_key(ctx->jrdev, ctx->key, &ctx->adata, key,
				    keylen, CAAM_MAX_HASH_KEY_SIZE);
		अगर (ret)
			जाओ bad_मुक्त_key;
	पूर्ण

	kमुक्त(hashed_key);
	वापस ahash_set_sh_desc(ahash);
 bad_मुक्त_key:
	kमुक्त(hashed_key);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक axcbc_setkey(काष्ठा crypto_ahash *ahash, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा device *jrdev = ctx->jrdev;

	अगर (keylen != AES_KEYSIZE_128)
		वापस -EINVAL;

	स_नकल(ctx->key, key, keylen);
	dma_sync_single_क्रम_device(jrdev, ctx->adata.key_dma, keylen,
				   DMA_TO_DEVICE);
	ctx->adata.keylen = keylen;

	prपूर्णांक_hex_dump_debug("axcbc ctx.key@" __stringअगरy(__LINE__)" : ",
			     DUMP_PREFIX_ADDRESS, 16, 4, ctx->key, keylen, 1);

	वापस axcbc_set_sh_desc(ahash);
पूर्ण

अटल पूर्णांक acmac_setkey(काष्ठा crypto_ahash *ahash, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	पूर्णांक err;

	err = aes_check_keylen(keylen);
	अगर (err)
		वापस err;

	/* key is immediate data क्रम all cmac shared descriptors */
	ctx->adata.key_virt = key;
	ctx->adata.keylen = keylen;

	prपूर्णांक_hex_dump_debug("acmac ctx.key@" __stringअगरy(__LINE__)" : ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);

	वापस acmac_set_sh_desc(ahash);
पूर्ण

/*
 * ahash_edesc - s/w-extended ahash descriptor
 * @sec4_sg_dma: physical mapped address of h/w link table
 * @src_nents: number of segments in input scatterlist
 * @sec4_sg_bytes: length of dma mapped sec4_sg space
 * @bklog: stored to determine अगर the request needs backlog
 * @hw_desc: the h/w job descriptor followed by any referenced link tables
 * @sec4_sg: h/w link table
 */
काष्ठा ahash_edesc अणु
	dma_addr_t sec4_sg_dma;
	पूर्णांक src_nents;
	पूर्णांक sec4_sg_bytes;
	bool bklog;
	u32 hw_desc[DESC_JOB_IO_LEN_MAX / माप(u32)] ____cacheline_aligned;
	काष्ठा sec4_sg_entry sec4_sg[];
पूर्ण;

अटल अंतरभूत व्योम ahash_unmap(काष्ठा device *dev,
			काष्ठा ahash_edesc *edesc,
			काष्ठा ahash_request *req, पूर्णांक dst_len)
अणु
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);

	अगर (edesc->src_nents)
		dma_unmap_sg(dev, req->src, edesc->src_nents, DMA_TO_DEVICE);

	अगर (edesc->sec4_sg_bytes)
		dma_unmap_single(dev, edesc->sec4_sg_dma,
				 edesc->sec4_sg_bytes, DMA_TO_DEVICE);

	अगर (state->buf_dma) अणु
		dma_unmap_single(dev, state->buf_dma, state->buflen,
				 DMA_TO_DEVICE);
		state->buf_dma = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ahash_unmap_ctx(काष्ठा device *dev,
			काष्ठा ahash_edesc *edesc,
			काष्ठा ahash_request *req, पूर्णांक dst_len, u32 flag)
अणु
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);

	अगर (state->ctx_dma) अणु
		dma_unmap_single(dev, state->ctx_dma, state->ctx_dma_len, flag);
		state->ctx_dma = 0;
	पूर्ण
	ahash_unmap(dev, edesc, req, dst_len);
पूर्ण

अटल अंतरभूत व्योम ahash_करोne_cpy(काष्ठा device *jrdev, u32 *desc, u32 err,
				  व्योम *context, क्रमागत dma_data_direction dir)
अणु
	काष्ठा ahash_request *req = context;
	काष्ठा caam_drv_निजी_jr *jrp = dev_get_drvdata(jrdev);
	काष्ठा ahash_edesc *edesc;
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	पूर्णांक ecode = 0;
	bool has_bklog;

	dev_dbg(jrdev, "%s %d: err 0x%x\n", __func__, __LINE__, err);

	edesc = state->edesc;
	has_bklog = edesc->bklog;

	अगर (err)
		ecode = caam_jr_strstatus(jrdev, err);

	ahash_unmap_ctx(jrdev, edesc, req, digestsize, dir);
	स_नकल(req->result, state->caam_ctx, digestsize);
	kमुक्त(edesc);

	prपूर्णांक_hex_dump_debug("ctx@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, state->caam_ctx,
			     ctx->ctx_len, 1);

	/*
	 * If no backlog flag, the completion of the request is करोne
	 * by CAAM, not crypto engine.
	 */
	अगर (!has_bklog)
		req->base.complete(&req->base, ecode);
	अन्यथा
		crypto_finalize_hash_request(jrp->engine, req, ecode);
पूर्ण

अटल व्योम ahash_करोne(काष्ठा device *jrdev, u32 *desc, u32 err,
		       व्योम *context)
अणु
	ahash_करोne_cpy(jrdev, desc, err, context, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम ahash_करोne_ctx_src(काष्ठा device *jrdev, u32 *desc, u32 err,
			       व्योम *context)
अणु
	ahash_करोne_cpy(jrdev, desc, err, context, DMA_BIसूचीECTIONAL);
पूर्ण

अटल अंतरभूत व्योम ahash_करोne_चयन(काष्ठा device *jrdev, u32 *desc, u32 err,
				     व्योम *context, क्रमागत dma_data_direction dir)
अणु
	काष्ठा ahash_request *req = context;
	काष्ठा caam_drv_निजी_jr *jrp = dev_get_drvdata(jrdev);
	काष्ठा ahash_edesc *edesc;
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	पूर्णांक ecode = 0;
	bool has_bklog;

	dev_dbg(jrdev, "%s %d: err 0x%x\n", __func__, __LINE__, err);

	edesc = state->edesc;
	has_bklog = edesc->bklog;
	अगर (err)
		ecode = caam_jr_strstatus(jrdev, err);

	ahash_unmap_ctx(jrdev, edesc, req, ctx->ctx_len, dir);
	kमुक्त(edesc);

	scatterwalk_map_and_copy(state->buf, req->src,
				 req->nbytes - state->next_buflen,
				 state->next_buflen, 0);
	state->buflen = state->next_buflen;

	prपूर्णांक_hex_dump_debug("buf@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, state->buf,
			     state->buflen, 1);

	prपूर्णांक_hex_dump_debug("ctx@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, state->caam_ctx,
			     ctx->ctx_len, 1);
	अगर (req->result)
		prपूर्णांक_hex_dump_debug("result@"__stringअगरy(__LINE__)": ",
				     DUMP_PREFIX_ADDRESS, 16, 4, req->result,
				     digestsize, 1);

	/*
	 * If no backlog flag, the completion of the request is करोne
	 * by CAAM, not crypto engine.
	 */
	अगर (!has_bklog)
		req->base.complete(&req->base, ecode);
	अन्यथा
		crypto_finalize_hash_request(jrp->engine, req, ecode);

पूर्ण

अटल व्योम ahash_करोne_bi(काष्ठा device *jrdev, u32 *desc, u32 err,
			  व्योम *context)
अणु
	ahash_करोne_चयन(jrdev, desc, err, context, DMA_BIसूचीECTIONAL);
पूर्ण

अटल व्योम ahash_करोne_ctx_dst(काष्ठा device *jrdev, u32 *desc, u32 err,
			       व्योम *context)
अणु
	ahash_करोne_चयन(jrdev, desc, err, context, DMA_FROM_DEVICE);
पूर्ण

/*
 * Allocate an enhanced descriptor, which contains the hardware descriptor
 * and space क्रम hardware scatter table containing sg_num entries.
 */
अटल काष्ठा ahash_edesc *ahash_edesc_alloc(काष्ठा ahash_request *req,
					     पूर्णांक sg_num, u32 *sh_desc,
					     dma_addr_t sh_desc_dma)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	काष्ठा ahash_edesc *edesc;
	अचिन्हित पूर्णांक sg_size = sg_num * माप(काष्ठा sec4_sg_entry);

	edesc = kzalloc(माप(*edesc) + sg_size, GFP_DMA | flags);
	अगर (!edesc) अणु
		dev_err(ctx->jrdev, "could not allocate extended descriptor\n");
		वापस शून्य;
	पूर्ण

	state->edesc = edesc;

	init_job_desc_shared(edesc->hw_desc, sh_desc_dma, desc_len(sh_desc),
			     HDR_SHARE_DEFER | HDR_REVERSE);

	वापस edesc;
पूर्ण

अटल पूर्णांक ahash_edesc_add_src(काष्ठा caam_hash_ctx *ctx,
			       काष्ठा ahash_edesc *edesc,
			       काष्ठा ahash_request *req, पूर्णांक nents,
			       अचिन्हित पूर्णांक first_sg,
			       अचिन्हित पूर्णांक first_bytes, माप_प्रकार to_hash)
अणु
	dma_addr_t src_dma;
	u32 options;

	अगर (nents > 1 || first_sg) अणु
		काष्ठा sec4_sg_entry *sg = edesc->sec4_sg;
		अचिन्हित पूर्णांक sgsize = माप(*sg) *
				      pad_sg_nents(first_sg + nents);

		sg_to_sec4_sg_last(req->src, to_hash, sg + first_sg, 0);

		src_dma = dma_map_single(ctx->jrdev, sg, sgsize, DMA_TO_DEVICE);
		अगर (dma_mapping_error(ctx->jrdev, src_dma)) अणु
			dev_err(ctx->jrdev, "unable to map S/G table\n");
			वापस -ENOMEM;
		पूर्ण

		edesc->sec4_sg_bytes = sgsize;
		edesc->sec4_sg_dma = src_dma;
		options = LDST_SGF;
	पूर्ण अन्यथा अणु
		src_dma = sg_dma_address(req->src);
		options = 0;
	पूर्ण

	append_seq_in_ptr(edesc->hw_desc, src_dma, first_bytes + to_hash,
			  options);

	वापस 0;
पूर्ण

अटल पूर्णांक ahash_करो_one_req(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा ahash_request *req = ahash_request_cast(areq);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा device *jrdev = ctx->jrdev;
	u32 *desc = state->edesc->hw_desc;
	पूर्णांक ret;

	state->edesc->bklog = true;

	ret = caam_jr_enqueue(jrdev, desc, state->ahash_op_करोne, req);

	अगर (ret != -EINPROGRESS) अणु
		ahash_unmap(jrdev, state->edesc, req, 0);
		kमुक्त(state->edesc);
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ahash_enqueue_req(काष्ठा device *jrdev,
			     व्योम (*cbk)(काष्ठा device *jrdev, u32 *desc,
					 u32 err, व्योम *context),
			     काष्ठा ahash_request *req,
			     पूर्णांक dst_len, क्रमागत dma_data_direction dir)
अणु
	काष्ठा caam_drv_निजी_jr *jrpriv = dev_get_drvdata(jrdev);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा ahash_edesc *edesc = state->edesc;
	u32 *desc = edesc->hw_desc;
	पूर्णांक ret;

	state->ahash_op_करोne = cbk;

	/*
	 * Only the backlog request are sent to crypto-engine since the others
	 * can be handled by CAAM, अगर मुक्त, especially since JR has up to 1024
	 * entries (more than the 10 entries from crypto-engine).
	 */
	अगर (req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)
		ret = crypto_transfer_hash_request_to_engine(jrpriv->engine,
							     req);
	अन्यथा
		ret = caam_jr_enqueue(jrdev, desc, cbk, req);

	अगर ((ret != -EINPROGRESS) && (ret != -EBUSY)) अणु
		ahash_unmap_ctx(jrdev, edesc, req, dst_len, dir);
		kमुक्त(edesc);
	पूर्ण

	वापस ret;
पूर्ण

/* submit update job descriptor */
अटल पूर्णांक ahash_update_ctx(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा device *jrdev = ctx->jrdev;
	u8 *buf = state->buf;
	पूर्णांक *buflen = &state->buflen;
	पूर्णांक *next_buflen = &state->next_buflen;
	पूर्णांक blocksize = crypto_ahash_blocksize(ahash);
	पूर्णांक in_len = *buflen + req->nbytes, to_hash;
	u32 *desc;
	पूर्णांक src_nents, mapped_nents, sec4_sg_bytes, sec4_sg_src_index;
	काष्ठा ahash_edesc *edesc;
	पूर्णांक ret = 0;

	*next_buflen = in_len & (blocksize - 1);
	to_hash = in_len - *next_buflen;

	/*
	 * For XCBC and CMAC, अगर to_hash is multiple of block size,
	 * keep last block in पूर्णांकernal buffer
	 */
	अगर ((is_xcbc_aes(ctx->adata.algtype) ||
	     is_cmac_aes(ctx->adata.algtype)) && to_hash >= blocksize &&
	     (*next_buflen == 0)) अणु
		*next_buflen = blocksize;
		to_hash -= blocksize;
	पूर्ण

	अगर (to_hash) अणु
		पूर्णांक pad_nents;
		पूर्णांक src_len = req->nbytes - *next_buflen;

		src_nents = sg_nents_क्रम_len(req->src, src_len);
		अगर (src_nents < 0) अणु
			dev_err(jrdev, "Invalid number of src SG.\n");
			वापस src_nents;
		पूर्ण

		अगर (src_nents) अणु
			mapped_nents = dma_map_sg(jrdev, req->src, src_nents,
						  DMA_TO_DEVICE);
			अगर (!mapped_nents) अणु
				dev_err(jrdev, "unable to DMA map source\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			mapped_nents = 0;
		पूर्ण

		sec4_sg_src_index = 1 + (*buflen ? 1 : 0);
		pad_nents = pad_sg_nents(sec4_sg_src_index + mapped_nents);
		sec4_sg_bytes = pad_nents * माप(काष्ठा sec4_sg_entry);

		/*
		 * allocate space क्रम base edesc and hw desc commands,
		 * link tables
		 */
		edesc = ahash_edesc_alloc(req, pad_nents, ctx->sh_desc_update,
					  ctx->sh_desc_update_dma);
		अगर (!edesc) अणु
			dma_unmap_sg(jrdev, req->src, src_nents, DMA_TO_DEVICE);
			वापस -ENOMEM;
		पूर्ण

		edesc->src_nents = src_nents;
		edesc->sec4_sg_bytes = sec4_sg_bytes;

		ret = ctx_map_to_sec4_sg(jrdev, state, ctx->ctx_len,
					 edesc->sec4_sg, DMA_BIसूचीECTIONAL);
		अगर (ret)
			जाओ unmap_ctx;

		ret = buf_map_to_sec4_sg(jrdev, edesc->sec4_sg + 1, state);
		अगर (ret)
			जाओ unmap_ctx;

		अगर (mapped_nents)
			sg_to_sec4_sg_last(req->src, src_len,
					   edesc->sec4_sg + sec4_sg_src_index,
					   0);
		अन्यथा
			sg_to_sec4_set_last(edesc->sec4_sg + sec4_sg_src_index -
					    1);

		desc = edesc->hw_desc;

		edesc->sec4_sg_dma = dma_map_single(jrdev, edesc->sec4_sg,
						     sec4_sg_bytes,
						     DMA_TO_DEVICE);
		अगर (dma_mapping_error(jrdev, edesc->sec4_sg_dma)) अणु
			dev_err(jrdev, "unable to map S/G table\n");
			ret = -ENOMEM;
			जाओ unmap_ctx;
		पूर्ण

		append_seq_in_ptr(desc, edesc->sec4_sg_dma, ctx->ctx_len +
				       to_hash, LDST_SGF);

		append_seq_out_ptr(desc, state->ctx_dma, ctx->ctx_len, 0);

		prपूर्णांक_hex_dump_debug("jobdesc@"__stringअगरy(__LINE__)": ",
				     DUMP_PREFIX_ADDRESS, 16, 4, desc,
				     desc_bytes(desc), 1);

		ret = ahash_enqueue_req(jrdev, ahash_करोne_bi, req,
					ctx->ctx_len, DMA_BIसूचीECTIONAL);
	पूर्ण अन्यथा अगर (*next_buflen) अणु
		scatterwalk_map_and_copy(buf + *buflen, req->src, 0,
					 req->nbytes, 0);
		*buflen = *next_buflen;

		prपूर्णांक_hex_dump_debug("buf@" __stringअगरy(__LINE__)": ",
				     DUMP_PREFIX_ADDRESS, 16, 4, buf,
				     *buflen, 1);
	पूर्ण

	वापस ret;
unmap_ctx:
	ahash_unmap_ctx(jrdev, edesc, req, ctx->ctx_len, DMA_BIसूचीECTIONAL);
	kमुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक ahash_final_ctx(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा device *jrdev = ctx->jrdev;
	पूर्णांक buflen = state->buflen;
	u32 *desc;
	पूर्णांक sec4_sg_bytes;
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा ahash_edesc *edesc;
	पूर्णांक ret;

	sec4_sg_bytes = pad_sg_nents(1 + (buflen ? 1 : 0)) *
			माप(काष्ठा sec4_sg_entry);

	/* allocate space क्रम base edesc and hw desc commands, link tables */
	edesc = ahash_edesc_alloc(req, 4, ctx->sh_desc_fin,
				  ctx->sh_desc_fin_dma);
	अगर (!edesc)
		वापस -ENOMEM;

	desc = edesc->hw_desc;

	edesc->sec4_sg_bytes = sec4_sg_bytes;

	ret = ctx_map_to_sec4_sg(jrdev, state, ctx->ctx_len,
				 edesc->sec4_sg, DMA_BIसूचीECTIONAL);
	अगर (ret)
		जाओ unmap_ctx;

	ret = buf_map_to_sec4_sg(jrdev, edesc->sec4_sg + 1, state);
	अगर (ret)
		जाओ unmap_ctx;

	sg_to_sec4_set_last(edesc->sec4_sg + (buflen ? 1 : 0));

	edesc->sec4_sg_dma = dma_map_single(jrdev, edesc->sec4_sg,
					    sec4_sg_bytes, DMA_TO_DEVICE);
	अगर (dma_mapping_error(jrdev, edesc->sec4_sg_dma)) अणु
		dev_err(jrdev, "unable to map S/G table\n");
		ret = -ENOMEM;
		जाओ unmap_ctx;
	पूर्ण

	append_seq_in_ptr(desc, edesc->sec4_sg_dma, ctx->ctx_len + buflen,
			  LDST_SGF);
	append_seq_out_ptr(desc, state->ctx_dma, digestsize, 0);

	prपूर्णांक_hex_dump_debug("jobdesc@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	वापस ahash_enqueue_req(jrdev, ahash_करोne_ctx_src, req,
				 digestsize, DMA_BIसूचीECTIONAL);
 unmap_ctx:
	ahash_unmap_ctx(jrdev, edesc, req, digestsize, DMA_BIसूचीECTIONAL);
	kमुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक ahash_finup_ctx(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा device *jrdev = ctx->jrdev;
	पूर्णांक buflen = state->buflen;
	u32 *desc;
	पूर्णांक sec4_sg_src_index;
	पूर्णांक src_nents, mapped_nents;
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा ahash_edesc *edesc;
	पूर्णांक ret;

	src_nents = sg_nents_क्रम_len(req->src, req->nbytes);
	अगर (src_nents < 0) अणु
		dev_err(jrdev, "Invalid number of src SG.\n");
		वापस src_nents;
	पूर्ण

	अगर (src_nents) अणु
		mapped_nents = dma_map_sg(jrdev, req->src, src_nents,
					  DMA_TO_DEVICE);
		अगर (!mapped_nents) अणु
			dev_err(jrdev, "unable to DMA map source\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		mapped_nents = 0;
	पूर्ण

	sec4_sg_src_index = 1 + (buflen ? 1 : 0);

	/* allocate space क्रम base edesc and hw desc commands, link tables */
	edesc = ahash_edesc_alloc(req, sec4_sg_src_index + mapped_nents,
				  ctx->sh_desc_fin, ctx->sh_desc_fin_dma);
	अगर (!edesc) अणु
		dma_unmap_sg(jrdev, req->src, src_nents, DMA_TO_DEVICE);
		वापस -ENOMEM;
	पूर्ण

	desc = edesc->hw_desc;

	edesc->src_nents = src_nents;

	ret = ctx_map_to_sec4_sg(jrdev, state, ctx->ctx_len,
				 edesc->sec4_sg, DMA_BIसूचीECTIONAL);
	अगर (ret)
		जाओ unmap_ctx;

	ret = buf_map_to_sec4_sg(jrdev, edesc->sec4_sg + 1, state);
	अगर (ret)
		जाओ unmap_ctx;

	ret = ahash_edesc_add_src(ctx, edesc, req, mapped_nents,
				  sec4_sg_src_index, ctx->ctx_len + buflen,
				  req->nbytes);
	अगर (ret)
		जाओ unmap_ctx;

	append_seq_out_ptr(desc, state->ctx_dma, digestsize, 0);

	prपूर्णांक_hex_dump_debug("jobdesc@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	वापस ahash_enqueue_req(jrdev, ahash_करोne_ctx_src, req,
				 digestsize, DMA_BIसूचीECTIONAL);
 unmap_ctx:
	ahash_unmap_ctx(jrdev, edesc, req, digestsize, DMA_BIसूचीECTIONAL);
	kमुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक ahash_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा device *jrdev = ctx->jrdev;
	u32 *desc;
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	पूर्णांक src_nents, mapped_nents;
	काष्ठा ahash_edesc *edesc;
	पूर्णांक ret;

	state->buf_dma = 0;

	src_nents = sg_nents_क्रम_len(req->src, req->nbytes);
	अगर (src_nents < 0) अणु
		dev_err(jrdev, "Invalid number of src SG.\n");
		वापस src_nents;
	पूर्ण

	अगर (src_nents) अणु
		mapped_nents = dma_map_sg(jrdev, req->src, src_nents,
					  DMA_TO_DEVICE);
		अगर (!mapped_nents) अणु
			dev_err(jrdev, "unable to map source for DMA\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		mapped_nents = 0;
	पूर्ण

	/* allocate space क्रम base edesc and hw desc commands, link tables */
	edesc = ahash_edesc_alloc(req, mapped_nents > 1 ? mapped_nents : 0,
				  ctx->sh_desc_digest, ctx->sh_desc_digest_dma);
	अगर (!edesc) अणु
		dma_unmap_sg(jrdev, req->src, src_nents, DMA_TO_DEVICE);
		वापस -ENOMEM;
	पूर्ण

	edesc->src_nents = src_nents;

	ret = ahash_edesc_add_src(ctx, edesc, req, mapped_nents, 0, 0,
				  req->nbytes);
	अगर (ret) अणु
		ahash_unmap(jrdev, edesc, req, digestsize);
		kमुक्त(edesc);
		वापस ret;
	पूर्ण

	desc = edesc->hw_desc;

	ret = map_seq_out_ptr_ctx(desc, jrdev, state, digestsize);
	अगर (ret) अणु
		ahash_unmap(jrdev, edesc, req, digestsize);
		kमुक्त(edesc);
		वापस -ENOMEM;
	पूर्ण

	prपूर्णांक_hex_dump_debug("jobdesc@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	वापस ahash_enqueue_req(jrdev, ahash_करोne, req, digestsize,
				 DMA_FROM_DEVICE);
पूर्ण

/* submit ahash final अगर it the first job descriptor */
अटल पूर्णांक ahash_final_no_ctx(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा device *jrdev = ctx->jrdev;
	u8 *buf = state->buf;
	पूर्णांक buflen = state->buflen;
	u32 *desc;
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा ahash_edesc *edesc;
	पूर्णांक ret;

	/* allocate space क्रम base edesc and hw desc commands, link tables */
	edesc = ahash_edesc_alloc(req, 0, ctx->sh_desc_digest,
				  ctx->sh_desc_digest_dma);
	अगर (!edesc)
		वापस -ENOMEM;

	desc = edesc->hw_desc;

	अगर (buflen) अणु
		state->buf_dma = dma_map_single(jrdev, buf, buflen,
						DMA_TO_DEVICE);
		अगर (dma_mapping_error(jrdev, state->buf_dma)) अणु
			dev_err(jrdev, "unable to map src\n");
			जाओ unmap;
		पूर्ण

		append_seq_in_ptr(desc, state->buf_dma, buflen, 0);
	पूर्ण

	ret = map_seq_out_ptr_ctx(desc, jrdev, state, digestsize);
	अगर (ret)
		जाओ unmap;

	prपूर्णांक_hex_dump_debug("jobdesc@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	वापस ahash_enqueue_req(jrdev, ahash_करोne, req,
				 digestsize, DMA_FROM_DEVICE);
 unmap:
	ahash_unmap(jrdev, edesc, req, digestsize);
	kमुक्त(edesc);
	वापस -ENOMEM;
पूर्ण

/* submit ahash update अगर it the first job descriptor after update */
अटल पूर्णांक ahash_update_no_ctx(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा device *jrdev = ctx->jrdev;
	u8 *buf = state->buf;
	पूर्णांक *buflen = &state->buflen;
	पूर्णांक *next_buflen = &state->next_buflen;
	पूर्णांक blocksize = crypto_ahash_blocksize(ahash);
	पूर्णांक in_len = *buflen + req->nbytes, to_hash;
	पूर्णांक sec4_sg_bytes, src_nents, mapped_nents;
	काष्ठा ahash_edesc *edesc;
	u32 *desc;
	पूर्णांक ret = 0;

	*next_buflen = in_len & (blocksize - 1);
	to_hash = in_len - *next_buflen;

	/*
	 * For XCBC and CMAC, अगर to_hash is multiple of block size,
	 * keep last block in पूर्णांकernal buffer
	 */
	अगर ((is_xcbc_aes(ctx->adata.algtype) ||
	     is_cmac_aes(ctx->adata.algtype)) && to_hash >= blocksize &&
	     (*next_buflen == 0)) अणु
		*next_buflen = blocksize;
		to_hash -= blocksize;
	पूर्ण

	अगर (to_hash) अणु
		पूर्णांक pad_nents;
		पूर्णांक src_len = req->nbytes - *next_buflen;

		src_nents = sg_nents_क्रम_len(req->src, src_len);
		अगर (src_nents < 0) अणु
			dev_err(jrdev, "Invalid number of src SG.\n");
			वापस src_nents;
		पूर्ण

		अगर (src_nents) अणु
			mapped_nents = dma_map_sg(jrdev, req->src, src_nents,
						  DMA_TO_DEVICE);
			अगर (!mapped_nents) अणु
				dev_err(jrdev, "unable to DMA map source\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			mapped_nents = 0;
		पूर्ण

		pad_nents = pad_sg_nents(1 + mapped_nents);
		sec4_sg_bytes = pad_nents * माप(काष्ठा sec4_sg_entry);

		/*
		 * allocate space क्रम base edesc and hw desc commands,
		 * link tables
		 */
		edesc = ahash_edesc_alloc(req, pad_nents,
					  ctx->sh_desc_update_first,
					  ctx->sh_desc_update_first_dma);
		अगर (!edesc) अणु
			dma_unmap_sg(jrdev, req->src, src_nents, DMA_TO_DEVICE);
			वापस -ENOMEM;
		पूर्ण

		edesc->src_nents = src_nents;
		edesc->sec4_sg_bytes = sec4_sg_bytes;

		ret = buf_map_to_sec4_sg(jrdev, edesc->sec4_sg, state);
		अगर (ret)
			जाओ unmap_ctx;

		sg_to_sec4_sg_last(req->src, src_len, edesc->sec4_sg + 1, 0);

		desc = edesc->hw_desc;

		edesc->sec4_sg_dma = dma_map_single(jrdev, edesc->sec4_sg,
						    sec4_sg_bytes,
						    DMA_TO_DEVICE);
		अगर (dma_mapping_error(jrdev, edesc->sec4_sg_dma)) अणु
			dev_err(jrdev, "unable to map S/G table\n");
			ret = -ENOMEM;
			जाओ unmap_ctx;
		पूर्ण

		append_seq_in_ptr(desc, edesc->sec4_sg_dma, to_hash, LDST_SGF);

		ret = map_seq_out_ptr_ctx(desc, jrdev, state, ctx->ctx_len);
		अगर (ret)
			जाओ unmap_ctx;

		prपूर्णांक_hex_dump_debug("jobdesc@"__stringअगरy(__LINE__)": ",
				     DUMP_PREFIX_ADDRESS, 16, 4, desc,
				     desc_bytes(desc), 1);

		ret = ahash_enqueue_req(jrdev, ahash_करोne_ctx_dst, req,
					ctx->ctx_len, DMA_TO_DEVICE);
		अगर ((ret != -EINPROGRESS) && (ret != -EBUSY))
			वापस ret;
		state->update = ahash_update_ctx;
		state->finup = ahash_finup_ctx;
		state->final = ahash_final_ctx;
	पूर्ण अन्यथा अगर (*next_buflen) अणु
		scatterwalk_map_and_copy(buf + *buflen, req->src, 0,
					 req->nbytes, 0);
		*buflen = *next_buflen;

		prपूर्णांक_hex_dump_debug("buf@" __stringअगरy(__LINE__)": ",
				     DUMP_PREFIX_ADDRESS, 16, 4, buf,
				     *buflen, 1);
	पूर्ण

	वापस ret;
 unmap_ctx:
	ahash_unmap_ctx(jrdev, edesc, req, ctx->ctx_len, DMA_TO_DEVICE);
	kमुक्त(edesc);
	वापस ret;
पूर्ण

/* submit ahash finup अगर it the first job descriptor after update */
अटल पूर्णांक ahash_finup_no_ctx(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा device *jrdev = ctx->jrdev;
	पूर्णांक buflen = state->buflen;
	u32 *desc;
	पूर्णांक sec4_sg_bytes, sec4_sg_src_index, src_nents, mapped_nents;
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा ahash_edesc *edesc;
	पूर्णांक ret;

	src_nents = sg_nents_क्रम_len(req->src, req->nbytes);
	अगर (src_nents < 0) अणु
		dev_err(jrdev, "Invalid number of src SG.\n");
		वापस src_nents;
	पूर्ण

	अगर (src_nents) अणु
		mapped_nents = dma_map_sg(jrdev, req->src, src_nents,
					  DMA_TO_DEVICE);
		अगर (!mapped_nents) अणु
			dev_err(jrdev, "unable to DMA map source\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		mapped_nents = 0;
	पूर्ण

	sec4_sg_src_index = 2;
	sec4_sg_bytes = (sec4_sg_src_index + mapped_nents) *
			 माप(काष्ठा sec4_sg_entry);

	/* allocate space क्रम base edesc and hw desc commands, link tables */
	edesc = ahash_edesc_alloc(req, sec4_sg_src_index + mapped_nents,
				  ctx->sh_desc_digest, ctx->sh_desc_digest_dma);
	अगर (!edesc) अणु
		dma_unmap_sg(jrdev, req->src, src_nents, DMA_TO_DEVICE);
		वापस -ENOMEM;
	पूर्ण

	desc = edesc->hw_desc;

	edesc->src_nents = src_nents;
	edesc->sec4_sg_bytes = sec4_sg_bytes;

	ret = buf_map_to_sec4_sg(jrdev, edesc->sec4_sg, state);
	अगर (ret)
		जाओ unmap;

	ret = ahash_edesc_add_src(ctx, edesc, req, mapped_nents, 1, buflen,
				  req->nbytes);
	अगर (ret) अणु
		dev_err(jrdev, "unable to map S/G table\n");
		जाओ unmap;
	पूर्ण

	ret = map_seq_out_ptr_ctx(desc, jrdev, state, digestsize);
	अगर (ret)
		जाओ unmap;

	prपूर्णांक_hex_dump_debug("jobdesc@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	वापस ahash_enqueue_req(jrdev, ahash_करोne, req,
				 digestsize, DMA_FROM_DEVICE);
 unmap:
	ahash_unmap(jrdev, edesc, req, digestsize);
	kमुक्त(edesc);
	वापस -ENOMEM;

पूर्ण

/* submit first update job descriptor after init */
अटल पूर्णांक ahash_update_first(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा device *jrdev = ctx->jrdev;
	u8 *buf = state->buf;
	पूर्णांक *buflen = &state->buflen;
	पूर्णांक *next_buflen = &state->next_buflen;
	पूर्णांक to_hash;
	पूर्णांक blocksize = crypto_ahash_blocksize(ahash);
	u32 *desc;
	पूर्णांक src_nents, mapped_nents;
	काष्ठा ahash_edesc *edesc;
	पूर्णांक ret = 0;

	*next_buflen = req->nbytes & (blocksize - 1);
	to_hash = req->nbytes - *next_buflen;

	/*
	 * For XCBC and CMAC, अगर to_hash is multiple of block size,
	 * keep last block in पूर्णांकernal buffer
	 */
	अगर ((is_xcbc_aes(ctx->adata.algtype) ||
	     is_cmac_aes(ctx->adata.algtype)) && to_hash >= blocksize &&
	     (*next_buflen == 0)) अणु
		*next_buflen = blocksize;
		to_hash -= blocksize;
	पूर्ण

	अगर (to_hash) अणु
		src_nents = sg_nents_क्रम_len(req->src,
					     req->nbytes - *next_buflen);
		अगर (src_nents < 0) अणु
			dev_err(jrdev, "Invalid number of src SG.\n");
			वापस src_nents;
		पूर्ण

		अगर (src_nents) अणु
			mapped_nents = dma_map_sg(jrdev, req->src, src_nents,
						  DMA_TO_DEVICE);
			अगर (!mapped_nents) अणु
				dev_err(jrdev, "unable to map source for DMA\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			mapped_nents = 0;
		पूर्ण

		/*
		 * allocate space क्रम base edesc and hw desc commands,
		 * link tables
		 */
		edesc = ahash_edesc_alloc(req, mapped_nents > 1 ?
					  mapped_nents : 0,
					  ctx->sh_desc_update_first,
					  ctx->sh_desc_update_first_dma);
		अगर (!edesc) अणु
			dma_unmap_sg(jrdev, req->src, src_nents, DMA_TO_DEVICE);
			वापस -ENOMEM;
		पूर्ण

		edesc->src_nents = src_nents;

		ret = ahash_edesc_add_src(ctx, edesc, req, mapped_nents, 0, 0,
					  to_hash);
		अगर (ret)
			जाओ unmap_ctx;

		desc = edesc->hw_desc;

		ret = map_seq_out_ptr_ctx(desc, jrdev, state, ctx->ctx_len);
		अगर (ret)
			जाओ unmap_ctx;

		prपूर्णांक_hex_dump_debug("jobdesc@"__stringअगरy(__LINE__)": ",
				     DUMP_PREFIX_ADDRESS, 16, 4, desc,
				     desc_bytes(desc), 1);

		ret = ahash_enqueue_req(jrdev, ahash_करोne_ctx_dst, req,
					ctx->ctx_len, DMA_TO_DEVICE);
		अगर ((ret != -EINPROGRESS) && (ret != -EBUSY))
			वापस ret;
		state->update = ahash_update_ctx;
		state->finup = ahash_finup_ctx;
		state->final = ahash_final_ctx;
	पूर्ण अन्यथा अगर (*next_buflen) अणु
		state->update = ahash_update_no_ctx;
		state->finup = ahash_finup_no_ctx;
		state->final = ahash_final_no_ctx;
		scatterwalk_map_and_copy(buf, req->src, 0,
					 req->nbytes, 0);
		*buflen = *next_buflen;

		prपूर्णांक_hex_dump_debug("buf@" __stringअगरy(__LINE__)": ",
				     DUMP_PREFIX_ADDRESS, 16, 4, buf,
				     *buflen, 1);
	पूर्ण

	वापस ret;
 unmap_ctx:
	ahash_unmap_ctx(jrdev, edesc, req, ctx->ctx_len, DMA_TO_DEVICE);
	kमुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक ahash_finup_first(काष्ठा ahash_request *req)
अणु
	वापस ahash_digest(req);
पूर्ण

अटल पूर्णांक ahash_init(काष्ठा ahash_request *req)
अणु
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);

	state->update = ahash_update_first;
	state->finup = ahash_finup_first;
	state->final = ahash_final_no_ctx;

	state->ctx_dma = 0;
	state->ctx_dma_len = 0;
	state->buf_dma = 0;
	state->buflen = 0;
	state->next_buflen = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ahash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);

	वापस state->update(req);
पूर्ण

अटल पूर्णांक ahash_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);

	वापस state->finup(req);
पूर्ण

अटल पूर्णांक ahash_final(काष्ठा ahash_request *req)
अणु
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);

	वापस state->final(req);
पूर्ण

अटल पूर्णांक ahash_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा caam_export_state *export = out;
	u8 *buf = state->buf;
	पूर्णांक len = state->buflen;

	स_नकल(export->buf, buf, len);
	स_नकल(export->caam_ctx, state->caam_ctx, माप(export->caam_ctx));
	export->buflen = len;
	export->update = state->update;
	export->final = state->final;
	export->finup = state->finup;

	वापस 0;
पूर्ण

अटल पूर्णांक ahash_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	स्थिर काष्ठा caam_export_state *export = in;

	स_रखो(state, 0, माप(*state));
	स_नकल(state->buf, export->buf, export->buflen);
	स_नकल(state->caam_ctx, export->caam_ctx, माप(state->caam_ctx));
	state->buflen = export->buflen;
	state->update = export->update;
	state->final = export->final;
	state->finup = export->finup;

	वापस 0;
पूर्ण

काष्ठा caam_hash_ढाँचा अणु
	अक्षर name[CRYPTO_MAX_ALG_NAME];
	अक्षर driver_name[CRYPTO_MAX_ALG_NAME];
	अक्षर hmac_name[CRYPTO_MAX_ALG_NAME];
	अक्षर hmac_driver_name[CRYPTO_MAX_ALG_NAME];
	अचिन्हित पूर्णांक blocksize;
	काष्ठा ahash_alg ढाँचा_ahash;
	u32 alg_type;
पूर्ण;

/* ahash descriptors */
अटल काष्ठा caam_hash_ढाँचा driver_hash[] = अणु
	अणु
		.name = "sha1",
		.driver_name = "sha1-caam",
		.hmac_name = "hmac(sha1)",
		.hmac_driver_name = "hmac-sha1-caam",
		.blocksize = SHA1_BLOCK_SIZE,
		.ढाँचा_ahash = अणु
			.init = ahash_init,
			.update = ahash_update,
			.final = ahash_final,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.export = ahash_export,
			.import = ahash_import,
			.setkey = ahash_setkey,
			.halg = अणु
				.digestsize = SHA1_DIGEST_SIZE,
				.statesize = माप(काष्ठा caam_export_state),
			पूर्ण,
		पूर्ण,
		.alg_type = OP_ALG_ALGSEL_SHA1,
	पूर्ण, अणु
		.name = "sha224",
		.driver_name = "sha224-caam",
		.hmac_name = "hmac(sha224)",
		.hmac_driver_name = "hmac-sha224-caam",
		.blocksize = SHA224_BLOCK_SIZE,
		.ढाँचा_ahash = अणु
			.init = ahash_init,
			.update = ahash_update,
			.final = ahash_final,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.export = ahash_export,
			.import = ahash_import,
			.setkey = ahash_setkey,
			.halg = अणु
				.digestsize = SHA224_DIGEST_SIZE,
				.statesize = माप(काष्ठा caam_export_state),
			पूर्ण,
		पूर्ण,
		.alg_type = OP_ALG_ALGSEL_SHA224,
	पूर्ण, अणु
		.name = "sha256",
		.driver_name = "sha256-caam",
		.hmac_name = "hmac(sha256)",
		.hmac_driver_name = "hmac-sha256-caam",
		.blocksize = SHA256_BLOCK_SIZE,
		.ढाँचा_ahash = अणु
			.init = ahash_init,
			.update = ahash_update,
			.final = ahash_final,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.export = ahash_export,
			.import = ahash_import,
			.setkey = ahash_setkey,
			.halg = अणु
				.digestsize = SHA256_DIGEST_SIZE,
				.statesize = माप(काष्ठा caam_export_state),
			पूर्ण,
		पूर्ण,
		.alg_type = OP_ALG_ALGSEL_SHA256,
	पूर्ण, अणु
		.name = "sha384",
		.driver_name = "sha384-caam",
		.hmac_name = "hmac(sha384)",
		.hmac_driver_name = "hmac-sha384-caam",
		.blocksize = SHA384_BLOCK_SIZE,
		.ढाँचा_ahash = अणु
			.init = ahash_init,
			.update = ahash_update,
			.final = ahash_final,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.export = ahash_export,
			.import = ahash_import,
			.setkey = ahash_setkey,
			.halg = अणु
				.digestsize = SHA384_DIGEST_SIZE,
				.statesize = माप(काष्ठा caam_export_state),
			पूर्ण,
		पूर्ण,
		.alg_type = OP_ALG_ALGSEL_SHA384,
	पूर्ण, अणु
		.name = "sha512",
		.driver_name = "sha512-caam",
		.hmac_name = "hmac(sha512)",
		.hmac_driver_name = "hmac-sha512-caam",
		.blocksize = SHA512_BLOCK_SIZE,
		.ढाँचा_ahash = अणु
			.init = ahash_init,
			.update = ahash_update,
			.final = ahash_final,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.export = ahash_export,
			.import = ahash_import,
			.setkey = ahash_setkey,
			.halg = अणु
				.digestsize = SHA512_DIGEST_SIZE,
				.statesize = माप(काष्ठा caam_export_state),
			पूर्ण,
		पूर्ण,
		.alg_type = OP_ALG_ALGSEL_SHA512,
	पूर्ण, अणु
		.name = "md5",
		.driver_name = "md5-caam",
		.hmac_name = "hmac(md5)",
		.hmac_driver_name = "hmac-md5-caam",
		.blocksize = MD5_BLOCK_WORDS * 4,
		.ढाँचा_ahash = अणु
			.init = ahash_init,
			.update = ahash_update,
			.final = ahash_final,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.export = ahash_export,
			.import = ahash_import,
			.setkey = ahash_setkey,
			.halg = अणु
				.digestsize = MD5_DIGEST_SIZE,
				.statesize = माप(काष्ठा caam_export_state),
			पूर्ण,
		पूर्ण,
		.alg_type = OP_ALG_ALGSEL_MD5,
	पूर्ण, अणु
		.hmac_name = "xcbc(aes)",
		.hmac_driver_name = "xcbc-aes-caam",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_ahash = अणु
			.init = ahash_init,
			.update = ahash_update,
			.final = ahash_final,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.export = ahash_export,
			.import = ahash_import,
			.setkey = axcbc_setkey,
			.halg = अणु
				.digestsize = AES_BLOCK_SIZE,
				.statesize = माप(काष्ठा caam_export_state),
			पूर्ण,
		 पूर्ण,
		.alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_XCBC_MAC,
	पूर्ण, अणु
		.hmac_name = "cmac(aes)",
		.hmac_driver_name = "cmac-aes-caam",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_ahash = अणु
			.init = ahash_init,
			.update = ahash_update,
			.final = ahash_final,
			.finup = ahash_finup,
			.digest = ahash_digest,
			.export = ahash_export,
			.import = ahash_import,
			.setkey = acmac_setkey,
			.halg = अणु
				.digestsize = AES_BLOCK_SIZE,
				.statesize = माप(काष्ठा caam_export_state),
			पूर्ण,
		 पूर्ण,
		.alg_type = OP_ALG_ALGSEL_AES | OP_ALG_AAI_CMAC,
	पूर्ण,
पूर्ण;

काष्ठा caam_hash_alg अणु
	काष्ठा list_head entry;
	पूर्णांक alg_type;
	काष्ठा ahash_alg ahash_alg;
पूर्ण;

अटल पूर्णांक caam_hash_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	काष्ठा crypto_alg *base = tfm->__crt_alg;
	काष्ठा hash_alg_common *halg =
		 container_of(base, काष्ठा hash_alg_common, base);
	काष्ठा ahash_alg *alg =
		 container_of(halg, काष्ठा ahash_alg, halg);
	काष्ठा caam_hash_alg *caam_hash =
		 container_of(alg, काष्ठा caam_hash_alg, ahash_alg);
	काष्ठा caam_hash_ctx *ctx = crypto_tfm_ctx(tfm);
	/* Sizes क्रम MDHA running digests: MD5, SHA1, 224, 256, 384, 512 */
	अटल स्थिर u8 runninglen[] = अणु HASH_MSG_LEN + MD5_DIGEST_SIZE,
					 HASH_MSG_LEN + SHA1_DIGEST_SIZE,
					 HASH_MSG_LEN + 32,
					 HASH_MSG_LEN + SHA256_DIGEST_SIZE,
					 HASH_MSG_LEN + 64,
					 HASH_MSG_LEN + SHA512_DIGEST_SIZE पूर्ण;
	स्थिर माप_प्रकार sh_desc_update_offset = दुरत्व(काष्ठा caam_hash_ctx,
						      sh_desc_update);
	dma_addr_t dma_addr;
	काष्ठा caam_drv_निजी *priv;

	/*
	 * Get a Job ring from Job Ring driver to ensure in-order
	 * crypto request processing per tfm
	 */
	ctx->jrdev = caam_jr_alloc();
	अगर (IS_ERR(ctx->jrdev)) अणु
		pr_err("Job Ring Device allocation for transform failed\n");
		वापस PTR_ERR(ctx->jrdev);
	पूर्ण

	priv = dev_get_drvdata(ctx->jrdev->parent);

	अगर (is_xcbc_aes(caam_hash->alg_type)) अणु
		ctx->dir = DMA_TO_DEVICE;
		ctx->key_dir = DMA_BIसूचीECTIONAL;
		ctx->adata.algtype = OP_TYPE_CLASS1_ALG | caam_hash->alg_type;
		ctx->ctx_len = 48;
	पूर्ण अन्यथा अगर (is_cmac_aes(caam_hash->alg_type)) अणु
		ctx->dir = DMA_TO_DEVICE;
		ctx->key_dir = DMA_NONE;
		ctx->adata.algtype = OP_TYPE_CLASS1_ALG | caam_hash->alg_type;
		ctx->ctx_len = 32;
	पूर्ण अन्यथा अणु
		अगर (priv->era >= 6) अणु
			ctx->dir = DMA_BIसूचीECTIONAL;
			ctx->key_dir = alg->setkey ? DMA_TO_DEVICE : DMA_NONE;
		पूर्ण अन्यथा अणु
			ctx->dir = DMA_TO_DEVICE;
			ctx->key_dir = DMA_NONE;
		पूर्ण
		ctx->adata.algtype = OP_TYPE_CLASS2_ALG | caam_hash->alg_type;
		ctx->ctx_len = runninglen[(ctx->adata.algtype &
					   OP_ALG_ALGSEL_SUBMASK) >>
					  OP_ALG_ALGSEL_SHIFT];
	पूर्ण

	अगर (ctx->key_dir != DMA_NONE) अणु
		ctx->adata.key_dma = dma_map_single_attrs(ctx->jrdev, ctx->key,
							  ARRAY_SIZE(ctx->key),
							  ctx->key_dir,
							  DMA_ATTR_SKIP_CPU_SYNC);
		अगर (dma_mapping_error(ctx->jrdev, ctx->adata.key_dma)) अणु
			dev_err(ctx->jrdev, "unable to map key\n");
			caam_jr_मुक्त(ctx->jrdev);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	dma_addr = dma_map_single_attrs(ctx->jrdev, ctx->sh_desc_update,
					दुरत्व(काष्ठा caam_hash_ctx, key) -
					sh_desc_update_offset,
					ctx->dir, DMA_ATTR_SKIP_CPU_SYNC);
	अगर (dma_mapping_error(ctx->jrdev, dma_addr)) अणु
		dev_err(ctx->jrdev, "unable to map shared descriptors\n");

		अगर (ctx->key_dir != DMA_NONE)
			dma_unmap_single_attrs(ctx->jrdev, ctx->adata.key_dma,
					       ARRAY_SIZE(ctx->key),
					       ctx->key_dir,
					       DMA_ATTR_SKIP_CPU_SYNC);

		caam_jr_मुक्त(ctx->jrdev);
		वापस -ENOMEM;
	पूर्ण

	ctx->sh_desc_update_dma = dma_addr;
	ctx->sh_desc_update_first_dma = dma_addr +
					दुरत्व(काष्ठा caam_hash_ctx,
						 sh_desc_update_first) -
					sh_desc_update_offset;
	ctx->sh_desc_fin_dma = dma_addr + दुरत्व(काष्ठा caam_hash_ctx,
						   sh_desc_fin) -
					sh_desc_update_offset;
	ctx->sh_desc_digest_dma = dma_addr + दुरत्व(काष्ठा caam_hash_ctx,
						      sh_desc_digest) -
					sh_desc_update_offset;

	ctx->enginectx.op.करो_one_request = ahash_करो_one_req;

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा caam_hash_state));

	/*
	 * For keyed hash algorithms shared descriptors
	 * will be created later in setkey() callback
	 */
	वापस alg->setkey ? 0 : ahash_set_sh_desc(ahash);
पूर्ण

अटल व्योम caam_hash_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा caam_hash_ctx *ctx = crypto_tfm_ctx(tfm);

	dma_unmap_single_attrs(ctx->jrdev, ctx->sh_desc_update_dma,
			       दुरत्व(काष्ठा caam_hash_ctx, key) -
			       दुरत्व(काष्ठा caam_hash_ctx, sh_desc_update),
			       ctx->dir, DMA_ATTR_SKIP_CPU_SYNC);
	अगर (ctx->key_dir != DMA_NONE)
		dma_unmap_single_attrs(ctx->jrdev, ctx->adata.key_dma,
				       ARRAY_SIZE(ctx->key), ctx->key_dir,
				       DMA_ATTR_SKIP_CPU_SYNC);
	caam_jr_मुक्त(ctx->jrdev);
पूर्ण

व्योम caam_algapi_hash_निकास(व्योम)
अणु
	काष्ठा caam_hash_alg *t_alg, *n;

	अगर (!hash_list.next)
		वापस;

	list_क्रम_each_entry_safe(t_alg, n, &hash_list, entry) अणु
		crypto_unरेजिस्टर_ahash(&t_alg->ahash_alg);
		list_del(&t_alg->entry);
		kमुक्त(t_alg);
	पूर्ण
पूर्ण

अटल काष्ठा caam_hash_alg *
caam_hash_alloc(काष्ठा caam_hash_ढाँचा *ढाँचा,
		bool keyed)
अणु
	काष्ठा caam_hash_alg *t_alg;
	काष्ठा ahash_alg *halg;
	काष्ठा crypto_alg *alg;

	t_alg = kzalloc(माप(*t_alg), GFP_KERNEL);
	अगर (!t_alg) अणु
		pr_err("failed to allocate t_alg\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	t_alg->ahash_alg = ढाँचा->ढाँचा_ahash;
	halg = &t_alg->ahash_alg;
	alg = &halg->halg.base;

	अगर (keyed) अणु
		snम_लिखो(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s",
			 ढाँचा->hmac_name);
		snम_लिखो(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
			 ढाँचा->hmac_driver_name);
	पूर्ण अन्यथा अणु
		snम_लिखो(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s",
			 ढाँचा->name);
		snम_लिखो(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
			 ढाँचा->driver_name);
		t_alg->ahash_alg.setkey = शून्य;
	पूर्ण
	alg->cra_module = THIS_MODULE;
	alg->cra_init = caam_hash_cra_init;
	alg->cra_निकास = caam_hash_cra_निकास;
	alg->cra_ctxsize = माप(काष्ठा caam_hash_ctx);
	alg->cra_priority = CAAM_CRA_PRIORITY;
	alg->cra_blocksize = ढाँचा->blocksize;
	alg->cra_alignmask = 0;
	alg->cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY;

	t_alg->alg_type = ढाँचा->alg_type;

	वापस t_alg;
पूर्ण

पूर्णांक caam_algapi_hash_init(काष्ठा device *ctrldev)
अणु
	पूर्णांक i = 0, err = 0;
	काष्ठा caam_drv_निजी *priv = dev_get_drvdata(ctrldev);
	अचिन्हित पूर्णांक md_limit = SHA512_DIGEST_SIZE;
	u32 md_inst, md_vid;

	/*
	 * Register crypto algorithms the device supports.  First, identअगरy
	 * presence and attributes of MD block.
	 */
	अगर (priv->era < 10) अणु
		md_vid = (rd_reg32(&priv->ctrl->perfmon.cha_id_ls) &
			  CHA_ID_LS_MD_MASK) >> CHA_ID_LS_MD_SHIFT;
		md_inst = (rd_reg32(&priv->ctrl->perfmon.cha_num_ls) &
			   CHA_ID_LS_MD_MASK) >> CHA_ID_LS_MD_SHIFT;
	पूर्ण अन्यथा अणु
		u32 mdha = rd_reg32(&priv->ctrl->vreg.mdha);

		md_vid = (mdha & CHA_VER_VID_MASK) >> CHA_VER_VID_SHIFT;
		md_inst = mdha & CHA_VER_NUM_MASK;
	पूर्ण

	/*
	 * Skip registration of any hashing algorithms अगर MD block
	 * is not present.
	 */
	अगर (!md_inst)
		वापस 0;

	/* Limit digest size based on LP256 */
	अगर (md_vid == CHA_VER_VID_MD_LP256)
		md_limit = SHA256_DIGEST_SIZE;

	INIT_LIST_HEAD(&hash_list);

	/* रेजिस्टर crypto algorithms the device supports */
	क्रम (i = 0; i < ARRAY_SIZE(driver_hash); i++) अणु
		काष्ठा caam_hash_alg *t_alg;
		काष्ठा caam_hash_ढाँचा *alg = driver_hash + i;

		/* If MD size is not supported by device, skip registration */
		अगर (is_mdha(alg->alg_type) &&
		    alg->ढाँचा_ahash.halg.digestsize > md_limit)
			जारी;

		/* रेजिस्टर hmac version */
		t_alg = caam_hash_alloc(alg, true);
		अगर (IS_ERR(t_alg)) अणु
			err = PTR_ERR(t_alg);
			pr_warn("%s alg allocation failed\n",
				alg->hmac_driver_name);
			जारी;
		पूर्ण

		err = crypto_रेजिस्टर_ahash(&t_alg->ahash_alg);
		अगर (err) अणु
			pr_warn("%s alg registration failed: %d\n",
				t_alg->ahash_alg.halg.base.cra_driver_name,
				err);
			kमुक्त(t_alg);
		पूर्ण अन्यथा
			list_add_tail(&t_alg->entry, &hash_list);

		अगर ((alg->alg_type & OP_ALG_ALGSEL_MASK) == OP_ALG_ALGSEL_AES)
			जारी;

		/* रेजिस्टर unkeyed version */
		t_alg = caam_hash_alloc(alg, false);
		अगर (IS_ERR(t_alg)) अणु
			err = PTR_ERR(t_alg);
			pr_warn("%s alg allocation failed\n", alg->driver_name);
			जारी;
		पूर्ण

		err = crypto_रेजिस्टर_ahash(&t_alg->ahash_alg);
		अगर (err) अणु
			pr_warn("%s alg registration failed: %d\n",
				t_alg->ahash_alg.halg.base.cra_driver_name,
				err);
			kमुक्त(t_alg);
		पूर्ण अन्यथा
			list_add_tail(&t_alg->entry, &hash_list);
	पूर्ण

	वापस err;
पूर्ण
