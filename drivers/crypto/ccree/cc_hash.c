<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/md5.h>
#समावेश <crypto/sm3.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

#समावेश "cc_driver.h"
#समावेश "cc_request_mgr.h"
#समावेश "cc_buffer_mgr.h"
#समावेश "cc_hash.h"
#समावेश "cc_sram_mgr.h"

#घोषणा CC_MAX_HASH_SEQ_LEN 12
#घोषणा CC_MAX_OPAD_KEYS_SIZE CC_MAX_HASH_BLCK_SIZE
#घोषणा CC_SM3_HASH_LEN_SIZE 8

काष्ठा cc_hash_handle अणु
	u32 digest_len_sram_addr;	/* स्थिर value in SRAM*/
	u32 larval_digest_sram_addr;   /* स्थिर value in SRAM */
	काष्ठा list_head hash_list;
पूर्ण;

अटल स्थिर u32 cc_digest_len_init[] = अणु
	0x00000040, 0x00000000, 0x00000000, 0x00000000 पूर्ण;
अटल स्थिर u32 cc_md5_init[] = अणु
	SHA1_H3, SHA1_H2, SHA1_H1, SHA1_H0 पूर्ण;
अटल स्थिर u32 cc_sha1_init[] = अणु
	SHA1_H4, SHA1_H3, SHA1_H2, SHA1_H1, SHA1_H0 पूर्ण;
अटल स्थिर u32 cc_sha224_init[] = अणु
	SHA224_H7, SHA224_H6, SHA224_H5, SHA224_H4,
	SHA224_H3, SHA224_H2, SHA224_H1, SHA224_H0 पूर्ण;
अटल स्थिर u32 cc_sha256_init[] = अणु
	SHA256_H7, SHA256_H6, SHA256_H5, SHA256_H4,
	SHA256_H3, SHA256_H2, SHA256_H1, SHA256_H0 पूर्ण;
अटल स्थिर u32 cc_digest_len_sha512_init[] = अणु
	0x00000080, 0x00000000, 0x00000000, 0x00000000 पूर्ण;

/*
 * Due to the way the HW works, every द्विगुन word in the SHA384 and SHA512
 * larval hashes must be stored in hi/lo order
 */
#घोषणा hilo(x)	upper_32_bits(x), lower_32_bits(x)
अटल स्थिर u32 cc_sha384_init[] = अणु
	hilo(SHA384_H7), hilo(SHA384_H6), hilo(SHA384_H5), hilo(SHA384_H4),
	hilo(SHA384_H3), hilo(SHA384_H2), hilo(SHA384_H1), hilo(SHA384_H0) पूर्ण;
अटल स्थिर u32 cc_sha512_init[] = अणु
	hilo(SHA512_H7), hilo(SHA512_H6), hilo(SHA512_H5), hilo(SHA512_H4),
	hilo(SHA512_H3), hilo(SHA512_H2), hilo(SHA512_H1), hilo(SHA512_H0) पूर्ण;

अटल स्थिर u32 cc_sm3_init[] = अणु
	SM3_IVH, SM3_IVG, SM3_IVF, SM3_IVE,
	SM3_IVD, SM3_IVC, SM3_IVB, SM3_IVA पूर्ण;

अटल व्योम cc_setup_xcbc(काष्ठा ahash_request *areq, काष्ठा cc_hw_desc desc[],
			  अचिन्हित पूर्णांक *seq_size);

अटल व्योम cc_setup_cmac(काष्ठा ahash_request *areq, काष्ठा cc_hw_desc desc[],
			  अचिन्हित पूर्णांक *seq_size);

अटल स्थिर व्योम *cc_larval_digest(काष्ठा device *dev, u32 mode);

काष्ठा cc_hash_alg अणु
	काष्ठा list_head entry;
	पूर्णांक hash_mode;
	पूर्णांक hw_mode;
	पूर्णांक पूर्णांकer_digestsize;
	काष्ठा cc_drvdata *drvdata;
	काष्ठा ahash_alg ahash_alg;
पूर्ण;

काष्ठा hash_key_req_ctx अणु
	u32 keylen;
	dma_addr_t key_dma_addr;
	u8 *key;
पूर्ण;

/* hash per-session context */
काष्ठा cc_hash_ctx अणु
	काष्ठा cc_drvdata *drvdata;
	/* holds the origin digest; the digest after "setkey" अगर HMAC,*
	 * the initial digest अगर HASH.
	 */
	u8 digest_buff[CC_MAX_HASH_DIGEST_SIZE]  ____cacheline_aligned;
	u8 opad_पंचांगp_keys_buff[CC_MAX_OPAD_KEYS_SIZE]  ____cacheline_aligned;

	dma_addr_t opad_पंचांगp_keys_dma_addr  ____cacheline_aligned;
	dma_addr_t digest_buff_dma_addr;
	/* use क्रम hmac with key large then mode block size */
	काष्ठा hash_key_req_ctx key_params;
	पूर्णांक hash_mode;
	पूर्णांक hw_mode;
	पूर्णांक पूर्णांकer_digestsize;
	अचिन्हित पूर्णांक hash_len;
	काष्ठा completion setkey_comp;
	bool is_hmac;
पूर्ण;

अटल व्योम cc_set_desc(काष्ठा ahash_req_ctx *areq_ctx, काष्ठा cc_hash_ctx *ctx,
			अचिन्हित पूर्णांक flow_mode, काष्ठा cc_hw_desc desc[],
			bool is_not_last_data, अचिन्हित पूर्णांक *seq_size);

अटल व्योम cc_set_endianity(u32 mode, काष्ठा cc_hw_desc *desc)
अणु
	अगर (mode == DRV_HASH_MD5 || mode == DRV_HASH_SHA384 ||
	    mode == DRV_HASH_SHA512) अणु
		set_bytes_swap(desc, 1);
	पूर्ण अन्यथा अणु
		set_cipher_config0(desc, HASH_DIGEST_RESULT_LITTLE_ENDIAN);
	पूर्ण
पूर्ण

अटल पूर्णांक cc_map_result(काष्ठा device *dev, काष्ठा ahash_req_ctx *state,
			 अचिन्हित पूर्णांक digestsize)
अणु
	state->digest_result_dma_addr =
		dma_map_single(dev, state->digest_result_buff,
			       digestsize, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, state->digest_result_dma_addr)) अणु
		dev_err(dev, "Mapping digest result buffer %u B for DMA failed\n",
			digestsize);
		वापस -ENOMEM;
	पूर्ण
	dev_dbg(dev, "Mapped digest result buffer %u B at va=%pK to dma=%pad\n",
		digestsize, state->digest_result_buff,
		&state->digest_result_dma_addr);

	वापस 0;
पूर्ण

अटल व्योम cc_init_req(काष्ठा device *dev, काष्ठा ahash_req_ctx *state,
			काष्ठा cc_hash_ctx *ctx)
अणु
	bool is_hmac = ctx->is_hmac;

	स_रखो(state, 0, माप(*state));

	अगर (is_hmac) अणु
		अगर (ctx->hw_mode != DRV_CIPHER_XCBC_MAC &&
		    ctx->hw_mode != DRV_CIPHER_CMAC) अणु
			dma_sync_single_क्रम_cpu(dev, ctx->digest_buff_dma_addr,
						ctx->पूर्णांकer_digestsize,
						DMA_BIसूचीECTIONAL);

			स_नकल(state->digest_buff, ctx->digest_buff,
			       ctx->पूर्णांकer_digestsize);
			अगर (ctx->hash_mode == DRV_HASH_SHA512 ||
			    ctx->hash_mode == DRV_HASH_SHA384)
				स_नकल(state->digest_bytes_len,
				       cc_digest_len_sha512_init,
				       ctx->hash_len);
			अन्यथा
				स_नकल(state->digest_bytes_len,
				       cc_digest_len_init,
				       ctx->hash_len);
		पूर्ण

		अगर (ctx->hash_mode != DRV_HASH_शून्य) अणु
			dma_sync_single_क्रम_cpu(dev,
						ctx->opad_पंचांगp_keys_dma_addr,
						ctx->पूर्णांकer_digestsize,
						DMA_BIसूचीECTIONAL);
			स_नकल(state->opad_digest_buff,
			       ctx->opad_पंचांगp_keys_buff, ctx->पूर्णांकer_digestsize);
		पूर्ण
	पूर्ण अन्यथा अणु /*hash*/
		/* Copy the initial digests अगर hash flow. */
		स्थिर व्योम *larval = cc_larval_digest(dev, ctx->hash_mode);

		स_नकल(state->digest_buff, larval, ctx->पूर्णांकer_digestsize);
	पूर्ण
पूर्ण

अटल पूर्णांक cc_map_req(काष्ठा device *dev, काष्ठा ahash_req_ctx *state,
		      काष्ठा cc_hash_ctx *ctx)
अणु
	bool is_hmac = ctx->is_hmac;

	state->digest_buff_dma_addr =
		dma_map_single(dev, state->digest_buff,
			       ctx->पूर्णांकer_digestsize, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, state->digest_buff_dma_addr)) अणु
		dev_err(dev, "Mapping digest len %d B at va=%pK for DMA failed\n",
			ctx->पूर्णांकer_digestsize, state->digest_buff);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(dev, "Mapped digest %d B at va=%pK to dma=%pad\n",
		ctx->पूर्णांकer_digestsize, state->digest_buff,
		&state->digest_buff_dma_addr);

	अगर (ctx->hw_mode != DRV_CIPHER_XCBC_MAC) अणु
		state->digest_bytes_len_dma_addr =
			dma_map_single(dev, state->digest_bytes_len,
				       HASH_MAX_LEN_SIZE, DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(dev, state->digest_bytes_len_dma_addr)) अणु
			dev_err(dev, "Mapping digest len %u B at va=%pK for DMA failed\n",
				HASH_MAX_LEN_SIZE, state->digest_bytes_len);
			जाओ unmap_digest_buf;
		पूर्ण
		dev_dbg(dev, "Mapped digest len %u B at va=%pK to dma=%pad\n",
			HASH_MAX_LEN_SIZE, state->digest_bytes_len,
			&state->digest_bytes_len_dma_addr);
	पूर्ण

	अगर (is_hmac && ctx->hash_mode != DRV_HASH_शून्य) अणु
		state->opad_digest_dma_addr =
			dma_map_single(dev, state->opad_digest_buff,
				       ctx->पूर्णांकer_digestsize,
				       DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(dev, state->opad_digest_dma_addr)) अणु
			dev_err(dev, "Mapping opad digest %d B at va=%pK for DMA failed\n",
				ctx->पूर्णांकer_digestsize,
				state->opad_digest_buff);
			जाओ unmap_digest_len;
		पूर्ण
		dev_dbg(dev, "Mapped opad digest %d B at va=%pK to dma=%pad\n",
			ctx->पूर्णांकer_digestsize, state->opad_digest_buff,
			&state->opad_digest_dma_addr);
	पूर्ण

	वापस 0;

unmap_digest_len:
	अगर (state->digest_bytes_len_dma_addr) अणु
		dma_unmap_single(dev, state->digest_bytes_len_dma_addr,
				 HASH_MAX_LEN_SIZE, DMA_BIसूचीECTIONAL);
		state->digest_bytes_len_dma_addr = 0;
	पूर्ण
unmap_digest_buf:
	अगर (state->digest_buff_dma_addr) अणु
		dma_unmap_single(dev, state->digest_buff_dma_addr,
				 ctx->पूर्णांकer_digestsize, DMA_BIसूचीECTIONAL);
		state->digest_buff_dma_addr = 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम cc_unmap_req(काष्ठा device *dev, काष्ठा ahash_req_ctx *state,
			 काष्ठा cc_hash_ctx *ctx)
अणु
	अगर (state->digest_buff_dma_addr) अणु
		dma_unmap_single(dev, state->digest_buff_dma_addr,
				 ctx->पूर्णांकer_digestsize, DMA_BIसूचीECTIONAL);
		dev_dbg(dev, "Unmapped digest-buffer: digest_buff_dma_addr=%pad\n",
			&state->digest_buff_dma_addr);
		state->digest_buff_dma_addr = 0;
	पूर्ण
	अगर (state->digest_bytes_len_dma_addr) अणु
		dma_unmap_single(dev, state->digest_bytes_len_dma_addr,
				 HASH_MAX_LEN_SIZE, DMA_BIसूचीECTIONAL);
		dev_dbg(dev, "Unmapped digest-bytes-len buffer: digest_bytes_len_dma_addr=%pad\n",
			&state->digest_bytes_len_dma_addr);
		state->digest_bytes_len_dma_addr = 0;
	पूर्ण
	अगर (state->opad_digest_dma_addr) अणु
		dma_unmap_single(dev, state->opad_digest_dma_addr,
				 ctx->पूर्णांकer_digestsize, DMA_BIसूचीECTIONAL);
		dev_dbg(dev, "Unmapped opad-digest: opad_digest_dma_addr=%pad\n",
			&state->opad_digest_dma_addr);
		state->opad_digest_dma_addr = 0;
	पूर्ण
पूर्ण

अटल व्योम cc_unmap_result(काष्ठा device *dev, काष्ठा ahash_req_ctx *state,
			    अचिन्हित पूर्णांक digestsize, u8 *result)
अणु
	अगर (state->digest_result_dma_addr) अणु
		dma_unmap_single(dev, state->digest_result_dma_addr, digestsize,
				 DMA_BIसूचीECTIONAL);
		dev_dbg(dev, "unmpa digest result buffer va (%pK) pa (%pad) len %u\n",
			state->digest_result_buff,
			&state->digest_result_dma_addr, digestsize);
		स_नकल(result, state->digest_result_buff, digestsize);
	पूर्ण
	state->digest_result_dma_addr = 0;
पूर्ण

अटल व्योम cc_update_complete(काष्ठा device *dev, व्योम *cc_req, पूर्णांक err)
अणु
	काष्ठा ahash_request *req = (काष्ठा ahash_request *)cc_req;
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	dev_dbg(dev, "req=%pK\n", req);

	अगर (err != -EINPROGRESS) अणु
		/* Not a BACKLOG notअगरication */
		cc_unmap_hash_request(dev, state, req->src, false);
		cc_unmap_req(dev, state, ctx);
	पूर्ण

	ahash_request_complete(req, err);
पूर्ण

अटल व्योम cc_digest_complete(काष्ठा device *dev, व्योम *cc_req, पूर्णांक err)
अणु
	काष्ठा ahash_request *req = (काष्ठा ahash_request *)cc_req;
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	u32 digestsize = crypto_ahash_digestsize(tfm);

	dev_dbg(dev, "req=%pK\n", req);

	अगर (err != -EINPROGRESS) अणु
		/* Not a BACKLOG notअगरication */
		cc_unmap_hash_request(dev, state, req->src, false);
		cc_unmap_result(dev, state, digestsize, req->result);
		cc_unmap_req(dev, state, ctx);
	पूर्ण

	ahash_request_complete(req, err);
पूर्ण

अटल व्योम cc_hash_complete(काष्ठा device *dev, व्योम *cc_req, पूर्णांक err)
अणु
	काष्ठा ahash_request *req = (काष्ठा ahash_request *)cc_req;
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	u32 digestsize = crypto_ahash_digestsize(tfm);

	dev_dbg(dev, "req=%pK\n", req);

	अगर (err != -EINPROGRESS) अणु
		/* Not a BACKLOG notअगरication */
		cc_unmap_hash_request(dev, state, req->src, false);
		cc_unmap_result(dev, state, digestsize, req->result);
		cc_unmap_req(dev, state, ctx);
	पूर्ण

	ahash_request_complete(req, err);
पूर्ण

अटल पूर्णांक cc_fin_result(काष्ठा cc_hw_desc *desc, काष्ठा ahash_request *req,
			 पूर्णांक idx)
अणु
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	u32 digestsize = crypto_ahash_digestsize(tfm);

	/* Get final MAC result */
	hw_desc_init(&desc[idx]);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_करोut_dlli(&desc[idx], state->digest_result_dma_addr, digestsize,
		      NS_BIT, 1);
	set_queue_last_ind(ctx->drvdata, &desc[idx]);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	set_cipher_config1(&desc[idx], HASH_PADDING_DISABLED);
	cc_set_endianity(ctx->hash_mode, &desc[idx]);
	idx++;

	वापस idx;
पूर्ण

अटल पूर्णांक cc_fin_hmac(काष्ठा cc_hw_desc *desc, काष्ठा ahash_request *req,
		       पूर्णांक idx)
अणु
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	u32 digestsize = crypto_ahash_digestsize(tfm);

	/* store the hash digest result in the context */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], ctx->hw_mode);
	set_करोut_dlli(&desc[idx], state->digest_buff_dma_addr, digestsize,
		      NS_BIT, 0);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	cc_set_endianity(ctx->hash_mode, &desc[idx]);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	idx++;

	/* Loading hash opad xor key state */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], ctx->hw_mode);
	set_din_type(&desc[idx], DMA_DLLI, state->opad_digest_dma_addr,
		     ctx->पूर्णांकer_digestsize, NS_BIT);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Load the hash current length */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], ctx->hw_mode);
	set_din_sram(&desc[idx],
		     cc_digest_len_addr(ctx->drvdata, ctx->hash_mode),
		     ctx->hash_len);
	set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	/* Memory Barrier: रुको क्रम IPAD/OPAD axi ग_लिखो to complete */
	hw_desc_init(&desc[idx]);
	set_din_no_dma(&desc[idx], 0, 0xfffff0);
	set_करोut_no_dma(&desc[idx], 0, 0, 1);
	idx++;

	/* Perक्रमm HASH update */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr,
		     digestsize, NS_BIT);
	set_flow_mode(&desc[idx], DIN_HASH);
	idx++;

	वापस idx;
पूर्ण

अटल पूर्णांक cc_hash_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	u32 digestsize = crypto_ahash_digestsize(tfm);
	काष्ठा scatterlist *src = req->src;
	अचिन्हित पूर्णांक nbytes = req->nbytes;
	u8 *result = req->result;
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	bool is_hmac = ctx->is_hmac;
	काष्ठा cc_crypto_req cc_req = अणुपूर्ण;
	काष्ठा cc_hw_desc desc[CC_MAX_HASH_SEQ_LEN];
	u32 larval_digest_addr;
	पूर्णांक idx = 0;
	पूर्णांक rc = 0;
	gfp_t flags = cc_gfp_flags(&req->base);

	dev_dbg(dev, "===== %s-digest (%d) ====\n", is_hmac ? "hmac" : "hash",
		nbytes);

	cc_init_req(dev, state, ctx);

	अगर (cc_map_req(dev, state, ctx)) अणु
		dev_err(dev, "map_ahash_source() failed\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (cc_map_result(dev, state, digestsize)) अणु
		dev_err(dev, "map_ahash_digest() failed\n");
		cc_unmap_req(dev, state, ctx);
		वापस -ENOMEM;
	पूर्ण

	अगर (cc_map_hash_request_final(ctx->drvdata, state, src, nbytes, 1,
				      flags)) अणु
		dev_err(dev, "map_ahash_request_final() failed\n");
		cc_unmap_result(dev, state, digestsize, result);
		cc_unmap_req(dev, state, ctx);
		वापस -ENOMEM;
	पूर्ण

	/* Setup request काष्ठाure */
	cc_req.user_cb = cc_digest_complete;
	cc_req.user_arg = req;

	/* If HMAC then load hash IPAD xor key, अगर HASH then load initial
	 * digest
	 */
	hw_desc_init(&desc[idx]);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	अगर (is_hmac) अणु
		set_din_type(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr,
			     ctx->पूर्णांकer_digestsize, NS_BIT);
	पूर्ण अन्यथा अणु
		larval_digest_addr = cc_larval_digest_addr(ctx->drvdata,
							   ctx->hash_mode);
		set_din_sram(&desc[idx], larval_digest_addr,
			     ctx->पूर्णांकer_digestsize);
	पूर्ण
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Load the hash current length */
	hw_desc_init(&desc[idx]);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);

	अगर (is_hmac) अणु
		set_din_type(&desc[idx], DMA_DLLI,
			     state->digest_bytes_len_dma_addr,
			     ctx->hash_len, NS_BIT);
	पूर्ण अन्यथा अणु
		set_din_स्थिर(&desc[idx], 0, ctx->hash_len);
		अगर (nbytes)
			set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
		अन्यथा
			set_cipher_करो(&desc[idx], DO_PAD);
	पूर्ण
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	cc_set_desc(state, ctx, DIN_HASH, desc, false, &idx);

	अगर (is_hmac) अणु
		/* HW last hash block padding (aka. "DO_PAD") */
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], ctx->hw_mode);
		set_करोut_dlli(&desc[idx], state->digest_buff_dma_addr,
			      ctx->hash_len, NS_BIT, 0);
		set_flow_mode(&desc[idx], S_HASH_to_DOUT);
		set_setup_mode(&desc[idx], SETUP_WRITE_STATE1);
		set_cipher_करो(&desc[idx], DO_PAD);
		idx++;

		idx = cc_fin_hmac(desc, req, idx);
	पूर्ण

	idx = cc_fin_result(desc, req, idx);

	rc = cc_send_request(ctx->drvdata, &cc_req, desc, idx, &req->base);
	अगर (rc != -EINPROGRESS && rc != -EBUSY) अणु
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);
		cc_unmap_hash_request(dev, state, src, true);
		cc_unmap_result(dev, state, digestsize, result);
		cc_unmap_req(dev, state, ctx);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक cc_restore_hash(काष्ठा cc_hw_desc *desc, काष्ठा cc_hash_ctx *ctx,
			   काष्ठा ahash_req_ctx *state, अचिन्हित पूर्णांक idx)
अणु
	/* Restore hash digest */
	hw_desc_init(&desc[idx]);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_din_type(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr,
		     ctx->पूर्णांकer_digestsize, NS_BIT);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Restore hash current length */
	hw_desc_init(&desc[idx]);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_cipher_config1(&desc[idx], HASH_PADDING_DISABLED);
	set_din_type(&desc[idx], DMA_DLLI, state->digest_bytes_len_dma_addr,
		     ctx->hash_len, NS_BIT);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	cc_set_desc(state, ctx, DIN_HASH, desc, false, &idx);

	वापस idx;
पूर्ण

अटल पूर्णांक cc_hash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	अचिन्हित पूर्णांक block_size = crypto_tfm_alg_blocksize(&tfm->base);
	काष्ठा scatterlist *src = req->src;
	अचिन्हित पूर्णांक nbytes = req->nbytes;
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	काष्ठा cc_crypto_req cc_req = अणुपूर्ण;
	काष्ठा cc_hw_desc desc[CC_MAX_HASH_SEQ_LEN];
	u32 idx = 0;
	पूर्णांक rc;
	gfp_t flags = cc_gfp_flags(&req->base);

	dev_dbg(dev, "===== %s-update (%d) ====\n", ctx->is_hmac ?
		"hmac" : "hash", nbytes);

	अगर (nbytes == 0) अणु
		/* no real updates required */
		वापस 0;
	पूर्ण

	rc = cc_map_hash_request_update(ctx->drvdata, state, src, nbytes,
					block_size, flags);
	अगर (rc) अणु
		अगर (rc == 1) अणु
			dev_dbg(dev, " data size not require HW update %x\n",
				nbytes);
			/* No hardware updates are required */
			वापस 0;
		पूर्ण
		dev_err(dev, "map_ahash_request_update() failed\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (cc_map_req(dev, state, ctx)) अणु
		dev_err(dev, "map_ahash_source() failed\n");
		cc_unmap_hash_request(dev, state, src, true);
		वापस -EINVAL;
	पूर्ण

	/* Setup request काष्ठाure */
	cc_req.user_cb = cc_update_complete;
	cc_req.user_arg = req;

	idx = cc_restore_hash(desc, ctx, state, idx);

	/* store the hash digest result in context */
	hw_desc_init(&desc[idx]);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_करोut_dlli(&desc[idx], state->digest_buff_dma_addr,
		      ctx->पूर्णांकer_digestsize, NS_BIT, 0);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	idx++;

	/* store current hash length in context */
	hw_desc_init(&desc[idx]);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_करोut_dlli(&desc[idx], state->digest_bytes_len_dma_addr,
		      ctx->hash_len, NS_BIT, 1);
	set_queue_last_ind(ctx->drvdata, &desc[idx]);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE1);
	idx++;

	rc = cc_send_request(ctx->drvdata, &cc_req, desc, idx, &req->base);
	अगर (rc != -EINPROGRESS && rc != -EBUSY) अणु
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);
		cc_unmap_hash_request(dev, state, src, true);
		cc_unmap_req(dev, state, ctx);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक cc_करो_finup(काष्ठा ahash_request *req, bool update)
अणु
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	u32 digestsize = crypto_ahash_digestsize(tfm);
	काष्ठा scatterlist *src = req->src;
	अचिन्हित पूर्णांक nbytes = req->nbytes;
	u8 *result = req->result;
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	bool is_hmac = ctx->is_hmac;
	काष्ठा cc_crypto_req cc_req = अणुपूर्ण;
	काष्ठा cc_hw_desc desc[CC_MAX_HASH_SEQ_LEN];
	अचिन्हित पूर्णांक idx = 0;
	पूर्णांक rc;
	gfp_t flags = cc_gfp_flags(&req->base);

	dev_dbg(dev, "===== %s-%s (%d) ====\n", is_hmac ? "hmac" : "hash",
		update ? "finup" : "final", nbytes);

	अगर (cc_map_req(dev, state, ctx)) अणु
		dev_err(dev, "map_ahash_source() failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cc_map_hash_request_final(ctx->drvdata, state, src, nbytes, update,
				      flags)) अणु
		dev_err(dev, "map_ahash_request_final() failed\n");
		cc_unmap_req(dev, state, ctx);
		वापस -ENOMEM;
	पूर्ण
	अगर (cc_map_result(dev, state, digestsize)) अणु
		dev_err(dev, "map_ahash_digest() failed\n");
		cc_unmap_hash_request(dev, state, src, true);
		cc_unmap_req(dev, state, ctx);
		वापस -ENOMEM;
	पूर्ण

	/* Setup request काष्ठाure */
	cc_req.user_cb = cc_hash_complete;
	cc_req.user_arg = req;

	idx = cc_restore_hash(desc, ctx, state, idx);

	/* Pad the hash */
	hw_desc_init(&desc[idx]);
	set_cipher_करो(&desc[idx], DO_PAD);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_करोut_dlli(&desc[idx], state->digest_bytes_len_dma_addr,
		      ctx->hash_len, NS_BIT, 0);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE1);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	idx++;

	अगर (is_hmac)
		idx = cc_fin_hmac(desc, req, idx);

	idx = cc_fin_result(desc, req, idx);

	rc = cc_send_request(ctx->drvdata, &cc_req, desc, idx, &req->base);
	अगर (rc != -EINPROGRESS && rc != -EBUSY) अणु
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);
		cc_unmap_hash_request(dev, state, src, true);
		cc_unmap_result(dev, state, digestsize, result);
		cc_unmap_req(dev, state, ctx);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक cc_hash_finup(काष्ठा ahash_request *req)
अणु
	वापस cc_करो_finup(req, true);
पूर्ण


अटल पूर्णांक cc_hash_final(काष्ठा ahash_request *req)
अणु
	वापस cc_करो_finup(req, false);
पूर्ण

अटल पूर्णांक cc_hash_init(काष्ठा ahash_request *req)
अणु
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	dev_dbg(dev, "===== init (%d) ====\n", req->nbytes);

	cc_init_req(dev, state, ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक cc_hash_setkey(काष्ठा crypto_ahash *ahash, स्थिर u8 *key,
			  अचिन्हित पूर्णांक keylen)
अणु
	अचिन्हित पूर्णांक hmac_pad_स्थिर[2] = अणु HMAC_IPAD_CONST, HMAC_OPAD_CONST पूर्ण;
	काष्ठा cc_crypto_req cc_req = अणुपूर्ण;
	काष्ठा cc_hash_ctx *ctx = शून्य;
	पूर्णांक blocksize = 0;
	पूर्णांक digestsize = 0;
	पूर्णांक i, idx = 0, rc = 0;
	काष्ठा cc_hw_desc desc[CC_MAX_HASH_SEQ_LEN];
	u32 larval_addr;
	काष्ठा device *dev;

	ctx = crypto_ahash_ctx(ahash);
	dev = drvdata_to_dev(ctx->drvdata);
	dev_dbg(dev, "start keylen: %d", keylen);

	blocksize = crypto_tfm_alg_blocksize(&ahash->base);
	digestsize = crypto_ahash_digestsize(ahash);

	larval_addr = cc_larval_digest_addr(ctx->drvdata, ctx->hash_mode);

	/* The keylen value distinguishes HASH in हाल keylen is ZERO bytes,
	 * any NON-ZERO value utilizes HMAC flow
	 */
	ctx->key_params.keylen = keylen;
	ctx->key_params.key_dma_addr = 0;
	ctx->is_hmac = true;
	ctx->key_params.key = शून्य;

	अगर (keylen) अणु
		ctx->key_params.key = kmemdup(key, keylen, GFP_KERNEL);
		अगर (!ctx->key_params.key)
			वापस -ENOMEM;

		ctx->key_params.key_dma_addr =
			dma_map_single(dev, ctx->key_params.key, keylen,
				       DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, ctx->key_params.key_dma_addr)) अणु
			dev_err(dev, "Mapping key va=0x%p len=%u for DMA failed\n",
				ctx->key_params.key, keylen);
			kमुक्त_sensitive(ctx->key_params.key);
			वापस -ENOMEM;
		पूर्ण
		dev_dbg(dev, "mapping key-buffer: key_dma_addr=%pad keylen=%u\n",
			&ctx->key_params.key_dma_addr, ctx->key_params.keylen);

		अगर (keylen > blocksize) अणु
			/* Load hash initial state */
			hw_desc_init(&desc[idx]);
			set_cipher_mode(&desc[idx], ctx->hw_mode);
			set_din_sram(&desc[idx], larval_addr,
				     ctx->पूर्णांकer_digestsize);
			set_flow_mode(&desc[idx], S_DIN_to_HASH);
			set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
			idx++;

			/* Load the hash current length*/
			hw_desc_init(&desc[idx]);
			set_cipher_mode(&desc[idx], ctx->hw_mode);
			set_din_स्थिर(&desc[idx], 0, ctx->hash_len);
			set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
			set_flow_mode(&desc[idx], S_DIN_to_HASH);
			set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
			idx++;

			hw_desc_init(&desc[idx]);
			set_din_type(&desc[idx], DMA_DLLI,
				     ctx->key_params.key_dma_addr, keylen,
				     NS_BIT);
			set_flow_mode(&desc[idx], DIN_HASH);
			idx++;

			/* Get hashed key */
			hw_desc_init(&desc[idx]);
			set_cipher_mode(&desc[idx], ctx->hw_mode);
			set_करोut_dlli(&desc[idx], ctx->opad_पंचांगp_keys_dma_addr,
				      digestsize, NS_BIT, 0);
			set_flow_mode(&desc[idx], S_HASH_to_DOUT);
			set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
			set_cipher_config1(&desc[idx], HASH_PADDING_DISABLED);
			cc_set_endianity(ctx->hash_mode, &desc[idx]);
			idx++;

			hw_desc_init(&desc[idx]);
			set_din_स्थिर(&desc[idx], 0, (blocksize - digestsize));
			set_flow_mode(&desc[idx], BYPASS);
			set_करोut_dlli(&desc[idx],
				      (ctx->opad_पंचांगp_keys_dma_addr +
				       digestsize),
				      (blocksize - digestsize), NS_BIT, 0);
			idx++;
		पूर्ण अन्यथा अणु
			hw_desc_init(&desc[idx]);
			set_din_type(&desc[idx], DMA_DLLI,
				     ctx->key_params.key_dma_addr, keylen,
				     NS_BIT);
			set_flow_mode(&desc[idx], BYPASS);
			set_करोut_dlli(&desc[idx], ctx->opad_पंचांगp_keys_dma_addr,
				      keylen, NS_BIT, 0);
			idx++;

			अगर ((blocksize - keylen)) अणु
				hw_desc_init(&desc[idx]);
				set_din_स्थिर(&desc[idx], 0,
					      (blocksize - keylen));
				set_flow_mode(&desc[idx], BYPASS);
				set_करोut_dlli(&desc[idx],
					      (ctx->opad_पंचांगp_keys_dma_addr +
					       keylen), (blocksize - keylen),
					      NS_BIT, 0);
				idx++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		hw_desc_init(&desc[idx]);
		set_din_स्थिर(&desc[idx], 0, blocksize);
		set_flow_mode(&desc[idx], BYPASS);
		set_करोut_dlli(&desc[idx], (ctx->opad_पंचांगp_keys_dma_addr),
			      blocksize, NS_BIT, 0);
		idx++;
	पूर्ण

	rc = cc_send_sync_request(ctx->drvdata, &cc_req, desc, idx);
	अगर (rc) अणु
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);
		जाओ out;
	पूर्ण

	/* calc derived HMAC key */
	क्रम (idx = 0, i = 0; i < 2; i++) अणु
		/* Load hash initial state */
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], ctx->hw_mode);
		set_din_sram(&desc[idx], larval_addr, ctx->पूर्णांकer_digestsize);
		set_flow_mode(&desc[idx], S_DIN_to_HASH);
		set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
		idx++;

		/* Load the hash current length*/
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], ctx->hw_mode);
		set_din_स्थिर(&desc[idx], 0, ctx->hash_len);
		set_flow_mode(&desc[idx], S_DIN_to_HASH);
		set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
		idx++;

		/* Prepare ipad key */
		hw_desc_init(&desc[idx]);
		set_xor_val(&desc[idx], hmac_pad_स्थिर[i]);
		set_cipher_mode(&desc[idx], ctx->hw_mode);
		set_flow_mode(&desc[idx], S_DIN_to_HASH);
		set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
		idx++;

		/* Perक्रमm HASH update */
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DLLI, ctx->opad_पंचांगp_keys_dma_addr,
			     blocksize, NS_BIT);
		set_cipher_mode(&desc[idx], ctx->hw_mode);
		set_xor_active(&desc[idx]);
		set_flow_mode(&desc[idx], DIN_HASH);
		idx++;

		/* Get the IPAD/OPAD xor key (Note, IPAD is the initial digest
		 * of the first HASH "update" state)
		 */
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], ctx->hw_mode);
		अगर (i > 0) /* Not first iteration */
			set_करोut_dlli(&desc[idx], ctx->opad_पंचांगp_keys_dma_addr,
				      ctx->पूर्णांकer_digestsize, NS_BIT, 0);
		अन्यथा /* First iteration */
			set_करोut_dlli(&desc[idx], ctx->digest_buff_dma_addr,
				      ctx->पूर्णांकer_digestsize, NS_BIT, 0);
		set_flow_mode(&desc[idx], S_HASH_to_DOUT);
		set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
		idx++;
	पूर्ण

	rc = cc_send_sync_request(ctx->drvdata, &cc_req, desc, idx);

out:
	अगर (ctx->key_params.key_dma_addr) अणु
		dma_unmap_single(dev, ctx->key_params.key_dma_addr,
				 ctx->key_params.keylen, DMA_TO_DEVICE);
		dev_dbg(dev, "Unmapped key-buffer: key_dma_addr=%pad keylen=%u\n",
			&ctx->key_params.key_dma_addr, ctx->key_params.keylen);
	पूर्ण

	kमुक्त_sensitive(ctx->key_params.key);

	वापस rc;
पूर्ण

अटल पूर्णांक cc_xcbc_setkey(काष्ठा crypto_ahash *ahash,
			  स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cc_crypto_req cc_req = अणुपूर्ण;
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक idx = 0;
	काष्ठा cc_hw_desc desc[CC_MAX_HASH_SEQ_LEN];

	dev_dbg(dev, "===== setkey (%d) ====\n", keylen);

	चयन (keylen) अणु
	हाल AES_KEYSIZE_128:
	हाल AES_KEYSIZE_192:
	हाल AES_KEYSIZE_256:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ctx->key_params.keylen = keylen;

	ctx->key_params.key = kmemdup(key, keylen, GFP_KERNEL);
	अगर (!ctx->key_params.key)
		वापस -ENOMEM;

	ctx->key_params.key_dma_addr =
		dma_map_single(dev, ctx->key_params.key, keylen, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, ctx->key_params.key_dma_addr)) अणु
		dev_err(dev, "Mapping key va=0x%p len=%u for DMA failed\n",
			key, keylen);
		kमुक्त_sensitive(ctx->key_params.key);
		वापस -ENOMEM;
	पूर्ण
	dev_dbg(dev, "mapping key-buffer: key_dma_addr=%pad keylen=%u\n",
		&ctx->key_params.key_dma_addr, ctx->key_params.keylen);

	ctx->is_hmac = true;
	/* 1. Load the AES key */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, ctx->key_params.key_dma_addr,
		     keylen, NS_BIT);
	set_cipher_mode(&desc[idx], DRV_CIPHER_ECB);
	set_cipher_config0(&desc[idx], DRV_CRYPTO_सूचीECTION_ENCRYPT);
	set_key_size_aes(&desc[idx], keylen);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	hw_desc_init(&desc[idx]);
	set_din_स्थिर(&desc[idx], 0x01010101, CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], DIN_AES_DOUT);
	set_करोut_dlli(&desc[idx],
		      (ctx->opad_पंचांगp_keys_dma_addr + XCBC_MAC_K1_OFFSET),
		      CC_AES_128_BIT_KEY_SIZE, NS_BIT, 0);
	idx++;

	hw_desc_init(&desc[idx]);
	set_din_स्थिर(&desc[idx], 0x02020202, CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], DIN_AES_DOUT);
	set_करोut_dlli(&desc[idx],
		      (ctx->opad_पंचांगp_keys_dma_addr + XCBC_MAC_K2_OFFSET),
		      CC_AES_128_BIT_KEY_SIZE, NS_BIT, 0);
	idx++;

	hw_desc_init(&desc[idx]);
	set_din_स्थिर(&desc[idx], 0x03030303, CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], DIN_AES_DOUT);
	set_करोut_dlli(&desc[idx],
		      (ctx->opad_पंचांगp_keys_dma_addr + XCBC_MAC_K3_OFFSET),
		      CC_AES_128_BIT_KEY_SIZE, NS_BIT, 0);
	idx++;

	rc = cc_send_sync_request(ctx->drvdata, &cc_req, desc, idx);

	dma_unmap_single(dev, ctx->key_params.key_dma_addr,
			 ctx->key_params.keylen, DMA_TO_DEVICE);
	dev_dbg(dev, "Unmapped key-buffer: key_dma_addr=%pad keylen=%u\n",
		&ctx->key_params.key_dma_addr, ctx->key_params.keylen);

	kमुक्त_sensitive(ctx->key_params.key);

	वापस rc;
पूर्ण

अटल पूर्णांक cc_cmac_setkey(काष्ठा crypto_ahash *ahash,
			  स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	dev_dbg(dev, "===== setkey (%d) ====\n", keylen);

	ctx->is_hmac = true;

	चयन (keylen) अणु
	हाल AES_KEYSIZE_128:
	हाल AES_KEYSIZE_192:
	हाल AES_KEYSIZE_256:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ctx->key_params.keylen = keylen;

	/* STAT_PHASE_1: Copy key to ctx */

	dma_sync_single_क्रम_cpu(dev, ctx->opad_पंचांगp_keys_dma_addr,
				keylen, DMA_TO_DEVICE);

	स_नकल(ctx->opad_पंचांगp_keys_buff, key, keylen);
	अगर (keylen == 24) अणु
		स_रखो(ctx->opad_पंचांगp_keys_buff + 24, 0,
		       CC_AES_KEY_SIZE_MAX - 24);
	पूर्ण

	dma_sync_single_क्रम_device(dev, ctx->opad_पंचांगp_keys_dma_addr,
				   keylen, DMA_TO_DEVICE);

	ctx->key_params.keylen = keylen;

	वापस 0;
पूर्ण

अटल व्योम cc_मुक्त_ctx(काष्ठा cc_hash_ctx *ctx)
अणु
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	अगर (ctx->digest_buff_dma_addr) अणु
		dma_unmap_single(dev, ctx->digest_buff_dma_addr,
				 माप(ctx->digest_buff), DMA_BIसूचीECTIONAL);
		dev_dbg(dev, "Unmapped digest-buffer: digest_buff_dma_addr=%pad\n",
			&ctx->digest_buff_dma_addr);
		ctx->digest_buff_dma_addr = 0;
	पूर्ण
	अगर (ctx->opad_पंचांगp_keys_dma_addr) अणु
		dma_unmap_single(dev, ctx->opad_पंचांगp_keys_dma_addr,
				 माप(ctx->opad_पंचांगp_keys_buff),
				 DMA_BIसूचीECTIONAL);
		dev_dbg(dev, "Unmapped opad-digest: opad_tmp_keys_dma_addr=%pad\n",
			&ctx->opad_पंचांगp_keys_dma_addr);
		ctx->opad_पंचांगp_keys_dma_addr = 0;
	पूर्ण

	ctx->key_params.keylen = 0;
पूर्ण

अटल पूर्णांक cc_alloc_ctx(काष्ठा cc_hash_ctx *ctx)
अणु
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	ctx->key_params.keylen = 0;

	ctx->digest_buff_dma_addr =
		dma_map_single(dev, ctx->digest_buff, माप(ctx->digest_buff),
			       DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, ctx->digest_buff_dma_addr)) अणु
		dev_err(dev, "Mapping digest len %zu B at va=%pK for DMA failed\n",
			माप(ctx->digest_buff), ctx->digest_buff);
		जाओ fail;
	पूर्ण
	dev_dbg(dev, "Mapped digest %zu B at va=%pK to dma=%pad\n",
		माप(ctx->digest_buff), ctx->digest_buff,
		&ctx->digest_buff_dma_addr);

	ctx->opad_पंचांगp_keys_dma_addr =
		dma_map_single(dev, ctx->opad_पंचांगp_keys_buff,
			       माप(ctx->opad_पंचांगp_keys_buff),
			       DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, ctx->opad_पंचांगp_keys_dma_addr)) अणु
		dev_err(dev, "Mapping opad digest %zu B at va=%pK for DMA failed\n",
			माप(ctx->opad_पंचांगp_keys_buff),
			ctx->opad_पंचांगp_keys_buff);
		जाओ fail;
	पूर्ण
	dev_dbg(dev, "Mapped opad_tmp_keys %zu B at va=%pK to dma=%pad\n",
		माप(ctx->opad_पंचांगp_keys_buff), ctx->opad_पंचांगp_keys_buff,
		&ctx->opad_पंचांगp_keys_dma_addr);

	ctx->is_hmac = false;
	वापस 0;

fail:
	cc_मुक्त_ctx(ctx);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक cc_get_hash_len(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा cc_hash_ctx *ctx = crypto_tfm_ctx(tfm);

	अगर (ctx->hash_mode == DRV_HASH_SM3)
		वापस CC_SM3_HASH_LEN_SIZE;
	अन्यथा
		वापस cc_get_शेष_hash_len(ctx->drvdata);
पूर्ण

अटल पूर्णांक cc_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा cc_hash_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा hash_alg_common *hash_alg_common =
		container_of(tfm->__crt_alg, काष्ठा hash_alg_common, base);
	काष्ठा ahash_alg *ahash_alg =
		container_of(hash_alg_common, काष्ठा ahash_alg, halg);
	काष्ठा cc_hash_alg *cc_alg =
			container_of(ahash_alg, काष्ठा cc_hash_alg, ahash_alg);

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा ahash_req_ctx));

	ctx->hash_mode = cc_alg->hash_mode;
	ctx->hw_mode = cc_alg->hw_mode;
	ctx->पूर्णांकer_digestsize = cc_alg->पूर्णांकer_digestsize;
	ctx->drvdata = cc_alg->drvdata;
	ctx->hash_len = cc_get_hash_len(tfm);
	वापस cc_alloc_ctx(ctx);
पूर्ण

अटल व्योम cc_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा cc_hash_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	dev_dbg(dev, "cc_cra_exit");
	cc_मुक्त_ctx(ctx);
पूर्ण

अटल पूर्णांक cc_mac_update(काष्ठा ahash_request *req)
अणु
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	अचिन्हित पूर्णांक block_size = crypto_tfm_alg_blocksize(&tfm->base);
	काष्ठा cc_crypto_req cc_req = अणुपूर्ण;
	काष्ठा cc_hw_desc desc[CC_MAX_HASH_SEQ_LEN];
	पूर्णांक rc;
	u32 idx = 0;
	gfp_t flags = cc_gfp_flags(&req->base);

	अगर (req->nbytes == 0) अणु
		/* no real updates required */
		वापस 0;
	पूर्ण

	state->xcbc_count++;

	rc = cc_map_hash_request_update(ctx->drvdata, state, req->src,
					req->nbytes, block_size, flags);
	अगर (rc) अणु
		अगर (rc == 1) अणु
			dev_dbg(dev, " data size not require HW update %x\n",
				req->nbytes);
			/* No hardware updates are required */
			वापस 0;
		पूर्ण
		dev_err(dev, "map_ahash_request_update() failed\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (cc_map_req(dev, state, ctx)) अणु
		dev_err(dev, "map_ahash_source() failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->hw_mode == DRV_CIPHER_XCBC_MAC)
		cc_setup_xcbc(req, desc, &idx);
	अन्यथा
		cc_setup_cmac(req, desc, &idx);

	cc_set_desc(state, ctx, DIN_AES_DOUT, desc, true, &idx);

	/* store the hash digest result in context */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], ctx->hw_mode);
	set_करोut_dlli(&desc[idx], state->digest_buff_dma_addr,
		      ctx->पूर्णांकer_digestsize, NS_BIT, 1);
	set_queue_last_ind(ctx->drvdata, &desc[idx]);
	set_flow_mode(&desc[idx], S_AES_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	idx++;

	/* Setup request काष्ठाure */
	cc_req.user_cb = cc_update_complete;
	cc_req.user_arg = req;

	rc = cc_send_request(ctx->drvdata, &cc_req, desc, idx, &req->base);
	अगर (rc != -EINPROGRESS && rc != -EBUSY) अणु
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);
		cc_unmap_hash_request(dev, state, req->src, true);
		cc_unmap_req(dev, state, ctx);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक cc_mac_final(काष्ठा ahash_request *req)
अणु
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	काष्ठा cc_crypto_req cc_req = अणुपूर्ण;
	काष्ठा cc_hw_desc desc[CC_MAX_HASH_SEQ_LEN];
	पूर्णांक idx = 0;
	पूर्णांक rc = 0;
	u32 key_size, key_len;
	u32 digestsize = crypto_ahash_digestsize(tfm);
	gfp_t flags = cc_gfp_flags(&req->base);
	u32 rem_cnt = *cc_hash_buf_cnt(state);

	अगर (ctx->hw_mode == DRV_CIPHER_XCBC_MAC) अणु
		key_size = CC_AES_128_BIT_KEY_SIZE;
		key_len  = CC_AES_128_BIT_KEY_SIZE;
	पूर्ण अन्यथा अणु
		key_size = (ctx->key_params.keylen == 24) ? AES_MAX_KEY_SIZE :
			ctx->key_params.keylen;
		key_len =  ctx->key_params.keylen;
	पूर्ण

	dev_dbg(dev, "===== final  xcbc reminder (%d) ====\n", rem_cnt);

	अगर (cc_map_req(dev, state, ctx)) अणु
		dev_err(dev, "map_ahash_source() failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cc_map_hash_request_final(ctx->drvdata, state, req->src,
				      req->nbytes, 0, flags)) अणु
		dev_err(dev, "map_ahash_request_final() failed\n");
		cc_unmap_req(dev, state, ctx);
		वापस -ENOMEM;
	पूर्ण

	अगर (cc_map_result(dev, state, digestsize)) अणु
		dev_err(dev, "map_ahash_digest() failed\n");
		cc_unmap_hash_request(dev, state, req->src, true);
		cc_unmap_req(dev, state, ctx);
		वापस -ENOMEM;
	पूर्ण

	/* Setup request काष्ठाure */
	cc_req.user_cb = cc_hash_complete;
	cc_req.user_arg = req;

	अगर (state->xcbc_count && rem_cnt == 0) अणु
		/* Load key क्रम ECB decryption */
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], DRV_CIPHER_ECB);
		set_cipher_config0(&desc[idx], DRV_CRYPTO_सूचीECTION_DECRYPT);
		set_din_type(&desc[idx], DMA_DLLI,
			     (ctx->opad_पंचांगp_keys_dma_addr + XCBC_MAC_K1_OFFSET),
			     key_size, NS_BIT);
		set_key_size_aes(&desc[idx], key_len);
		set_flow_mode(&desc[idx], S_DIN_to_AES);
		set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
		idx++;

		/* Initiate decryption of block state to previous
		 * block_state-XOR-M[n]
		 */
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr,
			     CC_AES_BLOCK_SIZE, NS_BIT);
		set_करोut_dlli(&desc[idx], state->digest_buff_dma_addr,
			      CC_AES_BLOCK_SIZE, NS_BIT, 0);
		set_flow_mode(&desc[idx], DIN_AES_DOUT);
		idx++;

		/* Memory Barrier: रुको क्रम axi ग_लिखो to complete */
		hw_desc_init(&desc[idx]);
		set_din_no_dma(&desc[idx], 0, 0xfffff0);
		set_करोut_no_dma(&desc[idx], 0, 0, 1);
		idx++;
	पूर्ण

	अगर (ctx->hw_mode == DRV_CIPHER_XCBC_MAC)
		cc_setup_xcbc(req, desc, &idx);
	अन्यथा
		cc_setup_cmac(req, desc, &idx);

	अगर (state->xcbc_count == 0) अणु
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], ctx->hw_mode);
		set_key_size_aes(&desc[idx], key_len);
		set_cmac_size0_mode(&desc[idx]);
		set_flow_mode(&desc[idx], S_DIN_to_AES);
		idx++;
	पूर्ण अन्यथा अगर (rem_cnt > 0) अणु
		cc_set_desc(state, ctx, DIN_AES_DOUT, desc, false, &idx);
	पूर्ण अन्यथा अणु
		hw_desc_init(&desc[idx]);
		set_din_स्थिर(&desc[idx], 0x00, CC_AES_BLOCK_SIZE);
		set_flow_mode(&desc[idx], DIN_AES_DOUT);
		idx++;
	पूर्ण

	/* Get final MAC result */
	hw_desc_init(&desc[idx]);
	set_करोut_dlli(&desc[idx], state->digest_result_dma_addr,
		      digestsize, NS_BIT, 1);
	set_queue_last_ind(ctx->drvdata, &desc[idx]);
	set_flow_mode(&desc[idx], S_AES_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	set_cipher_mode(&desc[idx], ctx->hw_mode);
	idx++;

	rc = cc_send_request(ctx->drvdata, &cc_req, desc, idx, &req->base);
	अगर (rc != -EINPROGRESS && rc != -EBUSY) अणु
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);
		cc_unmap_hash_request(dev, state, req->src, true);
		cc_unmap_result(dev, state, digestsize, req->result);
		cc_unmap_req(dev, state, ctx);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक cc_mac_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	काष्ठा cc_crypto_req cc_req = अणुपूर्ण;
	काष्ठा cc_hw_desc desc[CC_MAX_HASH_SEQ_LEN];
	पूर्णांक idx = 0;
	पूर्णांक rc = 0;
	u32 key_len = 0;
	u32 digestsize = crypto_ahash_digestsize(tfm);
	gfp_t flags = cc_gfp_flags(&req->base);

	dev_dbg(dev, "===== finup xcbc(%d) ====\n", req->nbytes);
	अगर (state->xcbc_count > 0 && req->nbytes == 0) अणु
		dev_dbg(dev, "No data to update. Call to fdx_mac_final\n");
		वापस cc_mac_final(req);
	पूर्ण

	अगर (cc_map_req(dev, state, ctx)) अणु
		dev_err(dev, "map_ahash_source() failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cc_map_hash_request_final(ctx->drvdata, state, req->src,
				      req->nbytes, 1, flags)) अणु
		dev_err(dev, "map_ahash_request_final() failed\n");
		cc_unmap_req(dev, state, ctx);
		वापस -ENOMEM;
	पूर्ण
	अगर (cc_map_result(dev, state, digestsize)) अणु
		dev_err(dev, "map_ahash_digest() failed\n");
		cc_unmap_hash_request(dev, state, req->src, true);
		cc_unmap_req(dev, state, ctx);
		वापस -ENOMEM;
	पूर्ण

	/* Setup request काष्ठाure */
	cc_req.user_cb = cc_hash_complete;
	cc_req.user_arg = req;

	अगर (ctx->hw_mode == DRV_CIPHER_XCBC_MAC) अणु
		key_len = CC_AES_128_BIT_KEY_SIZE;
		cc_setup_xcbc(req, desc, &idx);
	पूर्ण अन्यथा अणु
		key_len = ctx->key_params.keylen;
		cc_setup_cmac(req, desc, &idx);
	पूर्ण

	अगर (req->nbytes == 0) अणु
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], ctx->hw_mode);
		set_key_size_aes(&desc[idx], key_len);
		set_cmac_size0_mode(&desc[idx]);
		set_flow_mode(&desc[idx], S_DIN_to_AES);
		idx++;
	पूर्ण अन्यथा अणु
		cc_set_desc(state, ctx, DIN_AES_DOUT, desc, false, &idx);
	पूर्ण

	/* Get final MAC result */
	hw_desc_init(&desc[idx]);
	set_करोut_dlli(&desc[idx], state->digest_result_dma_addr,
		      digestsize, NS_BIT, 1);
	set_queue_last_ind(ctx->drvdata, &desc[idx]);
	set_flow_mode(&desc[idx], S_AES_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	set_cipher_mode(&desc[idx], ctx->hw_mode);
	idx++;

	rc = cc_send_request(ctx->drvdata, &cc_req, desc, idx, &req->base);
	अगर (rc != -EINPROGRESS && rc != -EBUSY) अणु
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);
		cc_unmap_hash_request(dev, state, req->src, true);
		cc_unmap_result(dev, state, digestsize, req->result);
		cc_unmap_req(dev, state, ctx);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक cc_mac_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	u32 digestsize = crypto_ahash_digestsize(tfm);
	काष्ठा cc_crypto_req cc_req = अणुपूर्ण;
	काष्ठा cc_hw_desc desc[CC_MAX_HASH_SEQ_LEN];
	u32 key_len;
	अचिन्हित पूर्णांक idx = 0;
	पूर्णांक rc;
	gfp_t flags = cc_gfp_flags(&req->base);

	dev_dbg(dev, "===== -digest mac (%d) ====\n",  req->nbytes);

	cc_init_req(dev, state, ctx);

	अगर (cc_map_req(dev, state, ctx)) अणु
		dev_err(dev, "map_ahash_source() failed\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (cc_map_result(dev, state, digestsize)) अणु
		dev_err(dev, "map_ahash_digest() failed\n");
		cc_unmap_req(dev, state, ctx);
		वापस -ENOMEM;
	पूर्ण

	अगर (cc_map_hash_request_final(ctx->drvdata, state, req->src,
				      req->nbytes, 1, flags)) अणु
		dev_err(dev, "map_ahash_request_final() failed\n");
		cc_unmap_req(dev, state, ctx);
		वापस -ENOMEM;
	पूर्ण

	/* Setup request काष्ठाure */
	cc_req.user_cb = cc_digest_complete;
	cc_req.user_arg = req;

	अगर (ctx->hw_mode == DRV_CIPHER_XCBC_MAC) अणु
		key_len = CC_AES_128_BIT_KEY_SIZE;
		cc_setup_xcbc(req, desc, &idx);
	पूर्ण अन्यथा अणु
		key_len = ctx->key_params.keylen;
		cc_setup_cmac(req, desc, &idx);
	पूर्ण

	अगर (req->nbytes == 0) अणु
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], ctx->hw_mode);
		set_key_size_aes(&desc[idx], key_len);
		set_cmac_size0_mode(&desc[idx]);
		set_flow_mode(&desc[idx], S_DIN_to_AES);
		idx++;
	पूर्ण अन्यथा अणु
		cc_set_desc(state, ctx, DIN_AES_DOUT, desc, false, &idx);
	पूर्ण

	/* Get final MAC result */
	hw_desc_init(&desc[idx]);
	set_करोut_dlli(&desc[idx], state->digest_result_dma_addr,
		      CC_AES_BLOCK_SIZE, NS_BIT, 1);
	set_queue_last_ind(ctx->drvdata, &desc[idx]);
	set_flow_mode(&desc[idx], S_AES_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_cipher_mode(&desc[idx], ctx->hw_mode);
	idx++;

	rc = cc_send_request(ctx->drvdata, &cc_req, desc, idx, &req->base);
	अगर (rc != -EINPROGRESS && rc != -EBUSY) अणु
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);
		cc_unmap_hash_request(dev, state, req->src, true);
		cc_unmap_result(dev, state, digestsize, req->result);
		cc_unmap_req(dev, state, ctx);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक cc_hash_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	u8 *curr_buff = cc_hash_buf(state);
	u32 curr_buff_cnt = *cc_hash_buf_cnt(state);
	स्थिर u32 पंचांगp = CC_EXPORT_MAGIC;

	स_नकल(out, &पंचांगp, माप(u32));
	out += माप(u32);

	स_नकल(out, state->digest_buff, ctx->पूर्णांकer_digestsize);
	out += ctx->पूर्णांकer_digestsize;

	स_नकल(out, state->digest_bytes_len, ctx->hash_len);
	out += ctx->hash_len;

	स_नकल(out, &curr_buff_cnt, माप(u32));
	out += माप(u32);

	स_नकल(out, curr_buff, curr_buff_cnt);

	वापस 0;
पूर्ण

अटल पूर्णांक cc_hash_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(req);
	u32 पंचांगp;

	स_नकल(&पंचांगp, in, माप(u32));
	अगर (पंचांगp != CC_EXPORT_MAGIC)
		वापस -EINVAL;
	in += माप(u32);

	cc_init_req(dev, state, ctx);

	स_नकल(state->digest_buff, in, ctx->पूर्णांकer_digestsize);
	in += ctx->पूर्णांकer_digestsize;

	स_नकल(state->digest_bytes_len, in, ctx->hash_len);
	in += ctx->hash_len;

	/* Sanity check the data as much as possible */
	स_नकल(&पंचांगp, in, माप(u32));
	अगर (पंचांगp > CC_MAX_HASH_BLCK_SIZE)
		वापस -EINVAL;
	in += माप(u32);

	state->buf_cnt[0] = पंचांगp;
	स_नकल(state->buffers[0], in, पंचांगp);

	वापस 0;
पूर्ण

काष्ठा cc_hash_ढाँचा अणु
	अक्षर name[CRYPTO_MAX_ALG_NAME];
	अक्षर driver_name[CRYPTO_MAX_ALG_NAME];
	अक्षर mac_name[CRYPTO_MAX_ALG_NAME];
	अक्षर mac_driver_name[CRYPTO_MAX_ALG_NAME];
	अचिन्हित पूर्णांक blocksize;
	bool is_mac;
	bool synchronize;
	काष्ठा ahash_alg ढाँचा_ahash;
	पूर्णांक hash_mode;
	पूर्णांक hw_mode;
	पूर्णांक पूर्णांकer_digestsize;
	काष्ठा cc_drvdata *drvdata;
	u32 min_hw_rev;
	क्रमागत cc_std_body std_body;
पूर्ण;

#घोषणा CC_STATE_SIZE(_x) \
	((_x) + HASH_MAX_LEN_SIZE + CC_MAX_HASH_BLCK_SIZE + (2 * माप(u32)))

/* hash descriptors */
अटल काष्ठा cc_hash_ढाँचा driver_hash[] = अणु
	//Asynchronize hash ढाँचा
	अणु
		.name = "sha1",
		.driver_name = "sha1-ccree",
		.mac_name = "hmac(sha1)",
		.mac_driver_name = "hmac-sha1-ccree",
		.blocksize = SHA1_BLOCK_SIZE,
		.is_mac = true,
		.synchronize = false,
		.ढाँचा_ahash = अणु
			.init = cc_hash_init,
			.update = cc_hash_update,
			.final = cc_hash_final,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.export = cc_hash_export,
			.import = cc_hash_import,
			.setkey = cc_hash_setkey,
			.halg = अणु
				.digestsize = SHA1_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(SHA1_DIGEST_SIZE),
			पूर्ण,
		पूर्ण,
		.hash_mode = DRV_HASH_SHA1,
		.hw_mode = DRV_HASH_HW_SHA1,
		.पूर्णांकer_digestsize = SHA1_DIGEST_SIZE,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "sha256",
		.driver_name = "sha256-ccree",
		.mac_name = "hmac(sha256)",
		.mac_driver_name = "hmac-sha256-ccree",
		.blocksize = SHA256_BLOCK_SIZE,
		.is_mac = true,
		.ढाँचा_ahash = अणु
			.init = cc_hash_init,
			.update = cc_hash_update,
			.final = cc_hash_final,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.export = cc_hash_export,
			.import = cc_hash_import,
			.setkey = cc_hash_setkey,
			.halg = अणु
				.digestsize = SHA256_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(SHA256_DIGEST_SIZE)
			पूर्ण,
		पूर्ण,
		.hash_mode = DRV_HASH_SHA256,
		.hw_mode = DRV_HASH_HW_SHA256,
		.पूर्णांकer_digestsize = SHA256_DIGEST_SIZE,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "sha224",
		.driver_name = "sha224-ccree",
		.mac_name = "hmac(sha224)",
		.mac_driver_name = "hmac-sha224-ccree",
		.blocksize = SHA224_BLOCK_SIZE,
		.is_mac = true,
		.ढाँचा_ahash = अणु
			.init = cc_hash_init,
			.update = cc_hash_update,
			.final = cc_hash_final,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.export = cc_hash_export,
			.import = cc_hash_import,
			.setkey = cc_hash_setkey,
			.halg = अणु
				.digestsize = SHA224_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(SHA256_DIGEST_SIZE),
			पूर्ण,
		पूर्ण,
		.hash_mode = DRV_HASH_SHA224,
		.hw_mode = DRV_HASH_HW_SHA256,
		.पूर्णांकer_digestsize = SHA256_DIGEST_SIZE,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "sha384",
		.driver_name = "sha384-ccree",
		.mac_name = "hmac(sha384)",
		.mac_driver_name = "hmac-sha384-ccree",
		.blocksize = SHA384_BLOCK_SIZE,
		.is_mac = true,
		.ढाँचा_ahash = अणु
			.init = cc_hash_init,
			.update = cc_hash_update,
			.final = cc_hash_final,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.export = cc_hash_export,
			.import = cc_hash_import,
			.setkey = cc_hash_setkey,
			.halg = अणु
				.digestsize = SHA384_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(SHA512_DIGEST_SIZE),
			पूर्ण,
		पूर्ण,
		.hash_mode = DRV_HASH_SHA384,
		.hw_mode = DRV_HASH_HW_SHA512,
		.पूर्णांकer_digestsize = SHA512_DIGEST_SIZE,
		.min_hw_rev = CC_HW_REV_712,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "sha512",
		.driver_name = "sha512-ccree",
		.mac_name = "hmac(sha512)",
		.mac_driver_name = "hmac-sha512-ccree",
		.blocksize = SHA512_BLOCK_SIZE,
		.is_mac = true,
		.ढाँचा_ahash = अणु
			.init = cc_hash_init,
			.update = cc_hash_update,
			.final = cc_hash_final,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.export = cc_hash_export,
			.import = cc_hash_import,
			.setkey = cc_hash_setkey,
			.halg = अणु
				.digestsize = SHA512_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(SHA512_DIGEST_SIZE),
			पूर्ण,
		पूर्ण,
		.hash_mode = DRV_HASH_SHA512,
		.hw_mode = DRV_HASH_HW_SHA512,
		.पूर्णांकer_digestsize = SHA512_DIGEST_SIZE,
		.min_hw_rev = CC_HW_REV_712,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "md5",
		.driver_name = "md5-ccree",
		.mac_name = "hmac(md5)",
		.mac_driver_name = "hmac-md5-ccree",
		.blocksize = MD5_HMAC_BLOCK_SIZE,
		.is_mac = true,
		.ढाँचा_ahash = अणु
			.init = cc_hash_init,
			.update = cc_hash_update,
			.final = cc_hash_final,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.export = cc_hash_export,
			.import = cc_hash_import,
			.setkey = cc_hash_setkey,
			.halg = अणु
				.digestsize = MD5_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(MD5_DIGEST_SIZE),
			पूर्ण,
		पूर्ण,
		.hash_mode = DRV_HASH_MD5,
		.hw_mode = DRV_HASH_HW_MD5,
		.पूर्णांकer_digestsize = MD5_DIGEST_SIZE,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "sm3",
		.driver_name = "sm3-ccree",
		.blocksize = SM3_BLOCK_SIZE,
		.is_mac = false,
		.ढाँचा_ahash = अणु
			.init = cc_hash_init,
			.update = cc_hash_update,
			.final = cc_hash_final,
			.finup = cc_hash_finup,
			.digest = cc_hash_digest,
			.export = cc_hash_export,
			.import = cc_hash_import,
			.setkey = cc_hash_setkey,
			.halg = अणु
				.digestsize = SM3_DIGEST_SIZE,
				.statesize = CC_STATE_SIZE(SM3_DIGEST_SIZE),
			पूर्ण,
		पूर्ण,
		.hash_mode = DRV_HASH_SM3,
		.hw_mode = DRV_HASH_HW_SM3,
		.पूर्णांकer_digestsize = SM3_DIGEST_SIZE,
		.min_hw_rev = CC_HW_REV_713,
		.std_body = CC_STD_OSCCA,
	पूर्ण,
	अणु
		.mac_name = "xcbc(aes)",
		.mac_driver_name = "xcbc-aes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.is_mac = true,
		.ढाँचा_ahash = अणु
			.init = cc_hash_init,
			.update = cc_mac_update,
			.final = cc_mac_final,
			.finup = cc_mac_finup,
			.digest = cc_mac_digest,
			.setkey = cc_xcbc_setkey,
			.export = cc_hash_export,
			.import = cc_hash_import,
			.halg = अणु
				.digestsize = AES_BLOCK_SIZE,
				.statesize = CC_STATE_SIZE(AES_BLOCK_SIZE),
			पूर्ण,
		पूर्ण,
		.hash_mode = DRV_HASH_शून्य,
		.hw_mode = DRV_CIPHER_XCBC_MAC,
		.पूर्णांकer_digestsize = AES_BLOCK_SIZE,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.mac_name = "cmac(aes)",
		.mac_driver_name = "cmac-aes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.is_mac = true,
		.ढाँचा_ahash = अणु
			.init = cc_hash_init,
			.update = cc_mac_update,
			.final = cc_mac_final,
			.finup = cc_mac_finup,
			.digest = cc_mac_digest,
			.setkey = cc_cmac_setkey,
			.export = cc_hash_export,
			.import = cc_hash_import,
			.halg = अणु
				.digestsize = AES_BLOCK_SIZE,
				.statesize = CC_STATE_SIZE(AES_BLOCK_SIZE),
			पूर्ण,
		पूर्ण,
		.hash_mode = DRV_HASH_शून्य,
		.hw_mode = DRV_CIPHER_CMAC,
		.पूर्णांकer_digestsize = AES_BLOCK_SIZE,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
पूर्ण;

अटल काष्ठा cc_hash_alg *cc_alloc_hash_alg(काष्ठा cc_hash_ढाँचा *ढाँचा,
					     काष्ठा device *dev, bool keyed)
अणु
	काष्ठा cc_hash_alg *t_crypto_alg;
	काष्ठा crypto_alg *alg;
	काष्ठा ahash_alg *halg;

	t_crypto_alg = devm_kzalloc(dev, माप(*t_crypto_alg), GFP_KERNEL);
	अगर (!t_crypto_alg)
		वापस ERR_PTR(-ENOMEM);

	t_crypto_alg->ahash_alg = ढाँचा->ढाँचा_ahash;
	halg = &t_crypto_alg->ahash_alg;
	alg = &halg->halg.base;

	अगर (keyed) अणु
		snम_लिखो(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s",
			 ढाँचा->mac_name);
		snम_लिखो(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
			 ढाँचा->mac_driver_name);
	पूर्ण अन्यथा अणु
		halg->setkey = शून्य;
		snम_लिखो(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s",
			 ढाँचा->name);
		snम_लिखो(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
			 ढाँचा->driver_name);
	पूर्ण
	alg->cra_module = THIS_MODULE;
	alg->cra_ctxsize = माप(काष्ठा cc_hash_ctx);
	alg->cra_priority = CC_CRA_PRIO;
	alg->cra_blocksize = ढाँचा->blocksize;
	alg->cra_alignmask = 0;
	alg->cra_निकास = cc_cra_निकास;

	alg->cra_init = cc_cra_init;
	alg->cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_KERN_DRIVER_ONLY;

	t_crypto_alg->hash_mode = ढाँचा->hash_mode;
	t_crypto_alg->hw_mode = ढाँचा->hw_mode;
	t_crypto_alg->पूर्णांकer_digestsize = ढाँचा->पूर्णांकer_digestsize;

	वापस t_crypto_alg;
पूर्ण

अटल पूर्णांक cc_init_copy_sram(काष्ठा cc_drvdata *drvdata, स्थिर u32 *data,
			     अचिन्हित पूर्णांक size, u32 *sram_buff_ofs)
अणु
	काष्ठा cc_hw_desc larval_seq[CC_DIGEST_SIZE_MAX / माप(u32)];
	अचिन्हित पूर्णांक larval_seq_len = 0;
	पूर्णांक rc;

	cc_set_sram_desc(data, *sram_buff_ofs, size / माप(*data),
			 larval_seq, &larval_seq_len);
	rc = send_request_init(drvdata, larval_seq, larval_seq_len);
	अगर (rc)
		वापस rc;

	*sram_buff_ofs += size;
	वापस 0;
पूर्ण

पूर्णांक cc_init_hash_sram(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_hash_handle *hash_handle = drvdata->hash_handle;
	u32 sram_buff_ofs = hash_handle->digest_len_sram_addr;
	bool large_sha_supported = (drvdata->hw_rev >= CC_HW_REV_712);
	bool sm3_supported = (drvdata->hw_rev >= CC_HW_REV_713);
	पूर्णांक rc = 0;

	/* Copy-to-sram digest-len */
	rc = cc_init_copy_sram(drvdata, cc_digest_len_init,
			       माप(cc_digest_len_init), &sram_buff_ofs);
	अगर (rc)
		जाओ init_digest_स्थिर_err;

	अगर (large_sha_supported) अणु
		/* Copy-to-sram digest-len क्रम sha384/512 */
		rc = cc_init_copy_sram(drvdata, cc_digest_len_sha512_init,
				       माप(cc_digest_len_sha512_init),
				       &sram_buff_ofs);
		अगर (rc)
			जाओ init_digest_स्थिर_err;
	पूर्ण

	/* The initial digests offset */
	hash_handle->larval_digest_sram_addr = sram_buff_ofs;

	/* Copy-to-sram initial SHA* digests */
	rc = cc_init_copy_sram(drvdata, cc_md5_init, माप(cc_md5_init),
			       &sram_buff_ofs);
	अगर (rc)
		जाओ init_digest_स्थिर_err;

	rc = cc_init_copy_sram(drvdata, cc_sha1_init, माप(cc_sha1_init),
			       &sram_buff_ofs);
	अगर (rc)
		जाओ init_digest_स्थिर_err;

	rc = cc_init_copy_sram(drvdata, cc_sha224_init, माप(cc_sha224_init),
			       &sram_buff_ofs);
	अगर (rc)
		जाओ init_digest_स्थिर_err;

	rc = cc_init_copy_sram(drvdata, cc_sha256_init, माप(cc_sha256_init),
			       &sram_buff_ofs);
	अगर (rc)
		जाओ init_digest_स्थिर_err;

	अगर (sm3_supported) अणु
		rc = cc_init_copy_sram(drvdata, cc_sm3_init,
				       माप(cc_sm3_init), &sram_buff_ofs);
		अगर (rc)
			जाओ init_digest_स्थिर_err;
	पूर्ण

	अगर (large_sha_supported) अणु
		rc = cc_init_copy_sram(drvdata, cc_sha384_init,
				       माप(cc_sha384_init), &sram_buff_ofs);
		अगर (rc)
			जाओ init_digest_स्थिर_err;

		rc = cc_init_copy_sram(drvdata, cc_sha512_init,
				       माप(cc_sha512_init), &sram_buff_ofs);
		अगर (rc)
			जाओ init_digest_स्थिर_err;
	पूर्ण

init_digest_स्थिर_err:
	वापस rc;
पूर्ण

पूर्णांक cc_hash_alloc(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_hash_handle *hash_handle;
	u32 sram_buff;
	u32 sram_माप_प्रकारo_alloc;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	पूर्णांक rc = 0;
	पूर्णांक alg;

	hash_handle = devm_kzalloc(dev, माप(*hash_handle), GFP_KERNEL);
	अगर (!hash_handle)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&hash_handle->hash_list);
	drvdata->hash_handle = hash_handle;

	sram_माप_प्रकारo_alloc = माप(cc_digest_len_init) +
			माप(cc_md5_init) +
			माप(cc_sha1_init) +
			माप(cc_sha224_init) +
			माप(cc_sha256_init);

	अगर (drvdata->hw_rev >= CC_HW_REV_713)
		sram_माप_प्रकारo_alloc += माप(cc_sm3_init);

	अगर (drvdata->hw_rev >= CC_HW_REV_712)
		sram_माप_प्रकारo_alloc += माप(cc_digest_len_sha512_init) +
			माप(cc_sha384_init) + माप(cc_sha512_init);

	sram_buff = cc_sram_alloc(drvdata, sram_माप_प्रकारo_alloc);
	अगर (sram_buff == शून्य_SRAM_ADDR) अणु
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* The initial digest-len offset */
	hash_handle->digest_len_sram_addr = sram_buff;

	/*must be set beक्रमe the alg registration as it is being used there*/
	rc = cc_init_hash_sram(drvdata);
	अगर (rc) अणु
		dev_err(dev, "Init digest CONST failed (rc=%d)\n", rc);
		जाओ fail;
	पूर्ण

	/* ahash registration */
	क्रम (alg = 0; alg < ARRAY_SIZE(driver_hash); alg++) अणु
		काष्ठा cc_hash_alg *t_alg;
		पूर्णांक hw_mode = driver_hash[alg].hw_mode;

		/* Check that the HW revision and variants are suitable */
		अगर ((driver_hash[alg].min_hw_rev > drvdata->hw_rev) ||
		    !(drvdata->std_bodies & driver_hash[alg].std_body))
			जारी;

		अगर (driver_hash[alg].is_mac) अणु
			/* रेजिस्टर hmac version */
			t_alg = cc_alloc_hash_alg(&driver_hash[alg], dev, true);
			अगर (IS_ERR(t_alg)) अणु
				rc = PTR_ERR(t_alg);
				dev_err(dev, "%s alg allocation failed\n",
					driver_hash[alg].driver_name);
				जाओ fail;
			पूर्ण
			t_alg->drvdata = drvdata;

			rc = crypto_रेजिस्टर_ahash(&t_alg->ahash_alg);
			अगर (rc) अणु
				dev_err(dev, "%s alg registration failed\n",
					driver_hash[alg].driver_name);
				जाओ fail;
			पूर्ण

			list_add_tail(&t_alg->entry, &hash_handle->hash_list);
		पूर्ण
		अगर (hw_mode == DRV_CIPHER_XCBC_MAC ||
		    hw_mode == DRV_CIPHER_CMAC)
			जारी;

		/* रेजिस्टर hash version */
		t_alg = cc_alloc_hash_alg(&driver_hash[alg], dev, false);
		अगर (IS_ERR(t_alg)) अणु
			rc = PTR_ERR(t_alg);
			dev_err(dev, "%s alg allocation failed\n",
				driver_hash[alg].driver_name);
			जाओ fail;
		पूर्ण
		t_alg->drvdata = drvdata;

		rc = crypto_रेजिस्टर_ahash(&t_alg->ahash_alg);
		अगर (rc) अणु
			dev_err(dev, "%s alg registration failed\n",
				driver_hash[alg].driver_name);
			जाओ fail;
		पूर्ण

		list_add_tail(&t_alg->entry, &hash_handle->hash_list);
	पूर्ण

	वापस 0;

fail:
	cc_hash_मुक्त(drvdata);
	वापस rc;
पूर्ण

पूर्णांक cc_hash_मुक्त(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_hash_alg *t_hash_alg, *hash_n;
	काष्ठा cc_hash_handle *hash_handle = drvdata->hash_handle;

	list_क्रम_each_entry_safe(t_hash_alg, hash_n, &hash_handle->hash_list,
				 entry) अणु
		crypto_unरेजिस्टर_ahash(&t_hash_alg->ahash_alg);
		list_del(&t_hash_alg->entry);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cc_setup_xcbc(काष्ठा ahash_request *areq, काष्ठा cc_hw_desc desc[],
			  अचिन्हित पूर्णांक *seq_size)
अणु
	अचिन्हित पूर्णांक idx = *seq_size;
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	/* Setup XCBC MAC K1 */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, (ctx->opad_पंचांगp_keys_dma_addr +
					    XCBC_MAC_K1_OFFSET),
		     CC_AES_128_BIT_KEY_SIZE, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_hash_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC, ctx->hash_mode);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Setup XCBC MAC K2 */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI,
		     (ctx->opad_पंचांगp_keys_dma_addr + XCBC_MAC_K2_OFFSET),
		     CC_AES_128_BIT_KEY_SIZE, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
	set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Setup XCBC MAC K3 */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI,
		     (ctx->opad_पंचांगp_keys_dma_addr + XCBC_MAC_K3_OFFSET),
		     CC_AES_128_BIT_KEY_SIZE, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE2);
	set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Loading MAC state */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr,
		     CC_AES_BLOCK_SIZE, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;
	*seq_size = idx;
पूर्ण

अटल व्योम cc_setup_cmac(काष्ठा ahash_request *areq, काष्ठा cc_hw_desc desc[],
			  अचिन्हित पूर्णांक *seq_size)
अणु
	अचिन्हित पूर्णांक idx = *seq_size;
	काष्ठा ahash_req_ctx *state = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	/* Setup CMAC Key */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, ctx->opad_पंचांगp_keys_dma_addr,
		     ((ctx->key_params.keylen == 24) ? AES_MAX_KEY_SIZE :
		      ctx->key_params.keylen), NS_BIT);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CMAC);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], ctx->key_params.keylen);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Load MAC state */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr,
		     CC_AES_BLOCK_SIZE, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CMAC);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], ctx->key_params.keylen);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;
	*seq_size = idx;
पूर्ण

अटल व्योम cc_set_desc(काष्ठा ahash_req_ctx *areq_ctx,
			काष्ठा cc_hash_ctx *ctx, अचिन्हित पूर्णांक flow_mode,
			काष्ठा cc_hw_desc desc[], bool is_not_last_data,
			अचिन्हित पूर्णांक *seq_size)
अणु
	अचिन्हित पूर्णांक idx = *seq_size;
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	अगर (areq_ctx->data_dma_buf_type == CC_DMA_BUF_DLLI) अणु
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DLLI,
			     sg_dma_address(areq_ctx->curr_sg),
			     areq_ctx->curr_sg->length, NS_BIT);
		set_flow_mode(&desc[idx], flow_mode);
		idx++;
	पूर्ण अन्यथा अणु
		अगर (areq_ctx->data_dma_buf_type == CC_DMA_BUF_शून्य) अणु
			dev_dbg(dev, " NULL mode\n");
			/* nothing to build */
			वापस;
		पूर्ण
		/* bypass */
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DLLI,
			     areq_ctx->mlli_params.mlli_dma_addr,
			     areq_ctx->mlli_params.mlli_len, NS_BIT);
		set_करोut_sram(&desc[idx], ctx->drvdata->mlli_sram_addr,
			      areq_ctx->mlli_params.mlli_len);
		set_flow_mode(&desc[idx], BYPASS);
		idx++;
		/* process */
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_MLLI,
			     ctx->drvdata->mlli_sram_addr,
			     areq_ctx->mlli_nents, NS_BIT);
		set_flow_mode(&desc[idx], flow_mode);
		idx++;
	पूर्ण
	अगर (is_not_last_data)
		set_din_not_last_indication(&desc[(idx - 1)]);
	/* वापस updated desc sequence size */
	*seq_size = idx;
पूर्ण

अटल स्थिर व्योम *cc_larval_digest(काष्ठा device *dev, u32 mode)
अणु
	चयन (mode) अणु
	हाल DRV_HASH_MD5:
		वापस cc_md5_init;
	हाल DRV_HASH_SHA1:
		वापस cc_sha1_init;
	हाल DRV_HASH_SHA224:
		वापस cc_sha224_init;
	हाल DRV_HASH_SHA256:
		वापस cc_sha256_init;
	हाल DRV_HASH_SHA384:
		वापस cc_sha384_init;
	हाल DRV_HASH_SHA512:
		वापस cc_sha512_init;
	हाल DRV_HASH_SM3:
		वापस cc_sm3_init;
	शेष:
		dev_err(dev, "Invalid hash mode (%d)\n", mode);
		वापस cc_md5_init;
	पूर्ण
पूर्ण

/**
 * cc_larval_digest_addr() - Get the address of the initial digest in SRAM
 * according to the given hash mode
 *
 * @drvdata: Associated device driver context
 * @mode: The Hash mode. Supported modes: MD5/SHA1/SHA224/SHA256
 *
 * Return:
 * The address of the initial digest in SRAM
 */
u32 cc_larval_digest_addr(व्योम *drvdata, u32 mode)
अणु
	काष्ठा cc_drvdata *_drvdata = (काष्ठा cc_drvdata *)drvdata;
	काष्ठा cc_hash_handle *hash_handle = _drvdata->hash_handle;
	काष्ठा device *dev = drvdata_to_dev(_drvdata);
	bool sm3_supported = (_drvdata->hw_rev >= CC_HW_REV_713);
	u32 addr;

	चयन (mode) अणु
	हाल DRV_HASH_शून्य:
		अवरोध; /*Ignore*/
	हाल DRV_HASH_MD5:
		वापस (hash_handle->larval_digest_sram_addr);
	हाल DRV_HASH_SHA1:
		वापस (hash_handle->larval_digest_sram_addr +
			माप(cc_md5_init));
	हाल DRV_HASH_SHA224:
		वापस (hash_handle->larval_digest_sram_addr +
			माप(cc_md5_init) +
			माप(cc_sha1_init));
	हाल DRV_HASH_SHA256:
		वापस (hash_handle->larval_digest_sram_addr +
			माप(cc_md5_init) +
			माप(cc_sha1_init) +
			माप(cc_sha224_init));
	हाल DRV_HASH_SM3:
		वापस (hash_handle->larval_digest_sram_addr +
			माप(cc_md5_init) +
			माप(cc_sha1_init) +
			माप(cc_sha224_init) +
			माप(cc_sha256_init));
	हाल DRV_HASH_SHA384:
		addr = (hash_handle->larval_digest_sram_addr +
			माप(cc_md5_init) +
			माप(cc_sha1_init) +
			माप(cc_sha224_init) +
			माप(cc_sha256_init));
		अगर (sm3_supported)
			addr += माप(cc_sm3_init);
		वापस addr;
	हाल DRV_HASH_SHA512:
		addr = (hash_handle->larval_digest_sram_addr +
			माप(cc_md5_init) +
			माप(cc_sha1_init) +
			माप(cc_sha224_init) +
			माप(cc_sha256_init) +
			माप(cc_sha384_init));
		अगर (sm3_supported)
			addr += माप(cc_sm3_init);
		वापस addr;
	शेष:
		dev_err(dev, "Invalid hash mode (%d)\n", mode);
	पूर्ण

	/*This is valid wrong value to aव्योम kernel crash*/
	वापस hash_handle->larval_digest_sram_addr;
पूर्ण

u32 cc_digest_len_addr(व्योम *drvdata, u32 mode)
अणु
	काष्ठा cc_drvdata *_drvdata = (काष्ठा cc_drvdata *)drvdata;
	काष्ठा cc_hash_handle *hash_handle = _drvdata->hash_handle;
	u32 digest_len_addr = hash_handle->digest_len_sram_addr;

	चयन (mode) अणु
	हाल DRV_HASH_SHA1:
	हाल DRV_HASH_SHA224:
	हाल DRV_HASH_SHA256:
	हाल DRV_HASH_MD5:
		वापस digest_len_addr;
	हाल DRV_HASH_SHA384:
	हाल DRV_HASH_SHA512:
		वापस  digest_len_addr + माप(cc_digest_len_init);
	शेष:
		वापस digest_len_addr; /*to aव्योम kernel crash*/
	पूर्ण
पूर्ण
