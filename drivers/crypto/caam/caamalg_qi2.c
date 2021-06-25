<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Copyright 2015-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2019 NXP
 */

#समावेश "compat.h"
#समावेश "regs.h"
#समावेश "caamalg_qi2.h"
#समावेश "dpseci_cmd.h"
#समावेश "desc_constr.h"
#समावेश "error.h"
#समावेश "sg_sw_sec4.h"
#समावेश "sg_sw_qm2.h"
#समावेश "key_gen.h"
#समावेश "caamalg_desc.h"
#समावेश "caamhash_desc.h"
#समावेश "dpseci-debugfs.h"
#समावेश <linux/fsl/mc.h>
#समावेश <soc/fsl/dpaa2-पन.स>
#समावेश <soc/fsl/dpaa2-fd.h>
#समावेश <crypto/xts.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा CAAM_CRA_PRIORITY	2000

/* max key is sum of AES_MAX_KEY_SIZE, max split key size */
#घोषणा CAAM_MAX_KEY_SIZE	(AES_MAX_KEY_SIZE + CTR_RFC3686_NONCE_SIZE + \
				 SHA512_DIGEST_SIZE * 2)

/*
 * This is a a cache of buffers, from which the users of CAAM QI driver
 * can allocate लघु buffers. It's speedier than करोing kदो_स्मृति on the hotpath.
 * NOTE: A more elegant solution would be to have some headroom in the frames
 *       being processed. This can be added by the dpaa2-eth driver. This would
 *       pose a problem क्रम userspace application processing which cannot
 *       know of this limitation. So क्रम now, this will work.
 * NOTE: The memcache is SMP-safe. No need to handle spinlocks in-here
 */
अटल काष्ठा kmem_cache *qi_cache;

काष्ठा caam_alg_entry अणु
	काष्ठा device *dev;
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

/**
 * काष्ठा caam_ctx - per-session context
 * @flc: Flow Contexts array
 * @key:  [authentication key], encryption key
 * @flc_dma: I/O भव addresses of the Flow Contexts
 * @key_dma: I/O भव address of the key
 * @dir: DMA direction क्रम mapping key and Flow Contexts
 * @dev: dpseci device
 * @adata: authentication algorithm details
 * @cdata: encryption algorithm details
 * @authsize: authentication tag (a.k.a. ICV / MAC) size
 * @xts_key_fallback: true अगर fallback tfm needs to be used due
 *		      to unsupported xts key lengths
 * @fallback: xts fallback tfm
 */
काष्ठा caam_ctx अणु
	काष्ठा caam_flc flc[NUM_OP];
	u8 key[CAAM_MAX_KEY_SIZE];
	dma_addr_t flc_dma[NUM_OP];
	dma_addr_t key_dma;
	क्रमागत dma_data_direction dir;
	काष्ठा device *dev;
	काष्ठा alginfo adata;
	काष्ठा alginfo cdata;
	अचिन्हित पूर्णांक authsize;
	bool xts_key_fallback;
	काष्ठा crypto_skcipher *fallback;
पूर्ण;

अटल व्योम *dpaa2_caam_iova_to_virt(काष्ठा dpaa2_caam_priv *priv,
				     dma_addr_t iova_addr)
अणु
	phys_addr_t phys_addr;

	phys_addr = priv->करोमुख्य ? iommu_iova_to_phys(priv->करोमुख्य, iova_addr) :
				   iova_addr;

	वापस phys_to_virt(phys_addr);
पूर्ण

/*
 * qi_cache_zalloc - Allocate buffers from CAAM-QI cache
 *
 * Allocate data on the hotpath. Instead of using kzalloc, one can use the
 * services of the CAAM QI memory cache (backed by kmem_cache). The buffers
 * will have a size of CAAM_QI_MEMCACHE_SIZE, which should be sufficient क्रम
 * hosting 16 SG entries.
 *
 * @flags - flags that would be used क्रम the equivalent kदो_स्मृति(..) call
 *
 * Returns a poपूर्णांकer to a retrieved buffer on success or शून्य on failure.
 */
अटल अंतरभूत व्योम *qi_cache_zalloc(gfp_t flags)
अणु
	वापस kmem_cache_zalloc(qi_cache, flags);
पूर्ण

/*
 * qi_cache_मुक्त - Frees buffers allocated from CAAM-QI cache
 *
 * @obj - buffer previously allocated by qi_cache_zalloc
 *
 * No checking is being करोne, the call is a passthrough call to
 * kmem_cache_मुक्त(...)
 */
अटल अंतरभूत व्योम qi_cache_मुक्त(व्योम *obj)
अणु
	kmem_cache_मुक्त(qi_cache, obj);
पूर्ण

अटल काष्ठा caam_request *to_caam_req(काष्ठा crypto_async_request *areq)
अणु
	चयन (crypto_tfm_alg_type(areq->tfm)) अणु
	हाल CRYPTO_ALG_TYPE_SKCIPHER:
		वापस skcipher_request_ctx(skcipher_request_cast(areq));
	हाल CRYPTO_ALG_TYPE_AEAD:
		वापस aead_request_ctx(container_of(areq, काष्ठा aead_request,
						     base));
	हाल CRYPTO_ALG_TYPE_AHASH:
		वापस ahash_request_ctx(ahash_request_cast(areq));
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण
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

अटल पूर्णांक aead_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_aead_alg *alg = container_of(crypto_aead_alg(aead),
						 typeof(*alg), aead);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	काष्ठा device *dev = ctx->dev;
	काष्ठा dpaa2_caam_priv *priv = dev_get_drvdata(dev);
	काष्ठा caam_flc *flc;
	u32 *desc;
	u32 ctx1_iv_off = 0;
	u32 *nonce = शून्य;
	अचिन्हित पूर्णांक data_len[2];
	u32 inl_mask;
	स्थिर bool ctr_mode = ((ctx->cdata.algtype & OP_ALG_AAI_MASK) ==
			       OP_ALG_AAI_CTR_MOD128);
	स्थिर bool is_rfc3686 = alg->caam.rfc3686;

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

	/* aead_encrypt shared descriptor */
	अगर (desc_अंतरभूत_query((alg->caam.geniv ? DESC_QI_AEAD_GIVENC_LEN :
						 DESC_QI_AEAD_ENC_LEN) +
			      (is_rfc3686 ? DESC_AEAD_CTR_RFC3686_LEN : 0),
			      DESC_JOB_IO_LEN, data_len, &inl_mask,
			      ARRAY_SIZE(data_len)) < 0)
		वापस -EINVAL;

	ctx->adata.key_अंतरभूत = !!(inl_mask & 1);
	ctx->cdata.key_अंतरभूत = !!(inl_mask & 2);

	flc = &ctx->flc[ENCRYPT];
	desc = flc->sh_desc;

	अगर (alg->caam.geniv)
		cnstr_shdsc_aead_givencap(desc, &ctx->cdata, &ctx->adata,
					  ivsize, ctx->authsize, is_rfc3686,
					  nonce, ctx1_iv_off, true,
					  priv->sec_attr.era);
	अन्यथा
		cnstr_shdsc_aead_encap(desc, &ctx->cdata, &ctx->adata,
				       ivsize, ctx->authsize, is_rfc3686, nonce,
				       ctx1_iv_off, true, priv->sec_attr.era);

	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[ENCRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

	/* aead_decrypt shared descriptor */
	अगर (desc_अंतरभूत_query(DESC_QI_AEAD_DEC_LEN +
			      (is_rfc3686 ? DESC_AEAD_CTR_RFC3686_LEN : 0),
			      DESC_JOB_IO_LEN, data_len, &inl_mask,
			      ARRAY_SIZE(data_len)) < 0)
		वापस -EINVAL;

	ctx->adata.key_अंतरभूत = !!(inl_mask & 1);
	ctx->cdata.key_अंतरभूत = !!(inl_mask & 2);

	flc = &ctx->flc[DECRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_aead_decap(desc, &ctx->cdata, &ctx->adata,
			       ivsize, ctx->authsize, alg->caam.geniv,
			       is_rfc3686, nonce, ctx1_iv_off, true,
			       priv->sec_attr.era);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[DECRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

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
	काष्ठा device *dev = ctx->dev;
	काष्ठा crypto_authenc_keys keys;

	अगर (crypto_authenc_extractkeys(&keys, key, keylen) != 0)
		जाओ badkey;

	dev_dbg(dev, "keylen %d enckeylen %d authkeylen %d\n",
		keys.authkeylen + keys.enckeylen, keys.enckeylen,
		keys.authkeylen);
	prपूर्णांक_hex_dump_debug("key in @" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);

	ctx->adata.keylen = keys.authkeylen;
	ctx->adata.keylen_pad = split_key_len(ctx->adata.algtype &
					      OP_ALG_ALGSEL_MASK);

	अगर (ctx->adata.keylen_pad + keys.enckeylen > CAAM_MAX_KEY_SIZE)
		जाओ badkey;

	स_नकल(ctx->key, keys.authkey, keys.authkeylen);
	स_नकल(ctx->key + ctx->adata.keylen_pad, keys.enckey, keys.enckeylen);
	dma_sync_single_क्रम_device(dev, ctx->key_dma, ctx->adata.keylen_pad +
				   keys.enckeylen, ctx->dir);
	prपूर्णांक_hex_dump_debug("ctx.key@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, ctx->key,
			     ctx->adata.keylen_pad + keys.enckeylen, 1);

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
		जाओ out;

	err = -EINVAL;
	अगर (keys.enckeylen != DES3_EDE_KEY_SIZE)
		जाओ out;

	err = crypto_des3_ede_verअगरy_key(crypto_aead_tfm(aead), keys.enckey) ?:
	      aead_setkey(aead, key, keylen);

out:
	memzero_explicit(&keys, माप(keys));
	वापस err;
पूर्ण

अटल काष्ठा aead_edesc *aead_edesc_alloc(काष्ठा aead_request *req,
					   bool encrypt)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_request *req_ctx = aead_request_ctx(req);
	काष्ठा dpaa2_fl_entry *in_fle = &req_ctx->fd_flt[1];
	काष्ठा dpaa2_fl_entry *out_fle = &req_ctx->fd_flt[0];
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा caam_aead_alg *alg = container_of(crypto_aead_alg(aead),
						 typeof(*alg), aead);
	काष्ठा device *dev = ctx->dev;
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		      GFP_KERNEL : GFP_ATOMIC;
	पूर्णांक src_nents, mapped_src_nents, dst_nents = 0, mapped_dst_nents = 0;
	पूर्णांक src_len, dst_len = 0;
	काष्ठा aead_edesc *edesc;
	dma_addr_t qm_sg_dma, iv_dma = 0;
	पूर्णांक ivsize = 0;
	अचिन्हित पूर्णांक authsize = ctx->authsize;
	पूर्णांक qm_sg_index = 0, qm_sg_nents = 0, qm_sg_bytes;
	पूर्णांक in_len, out_len;
	काष्ठा dpaa2_sg_entry *sg_table;

	/* allocate space क्रम base edesc, link tables and IV */
	edesc = qi_cache_zalloc(GFP_DMA | flags);
	अगर (unlikely(!edesc)) अणु
		dev_err(dev, "could not allocate extended descriptor\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (unlikely(req->dst != req->src)) अणु
		src_len = req->assoclen + req->cryptlen;
		dst_len = src_len + (encrypt ? authsize : (-authsize));

		src_nents = sg_nents_क्रम_len(req->src, src_len);
		अगर (unlikely(src_nents < 0)) अणु
			dev_err(dev, "Insufficient bytes (%d) in src S/G\n",
				src_len);
			qi_cache_मुक्त(edesc);
			वापस ERR_PTR(src_nents);
		पूर्ण

		dst_nents = sg_nents_क्रम_len(req->dst, dst_len);
		अगर (unlikely(dst_nents < 0)) अणु
			dev_err(dev, "Insufficient bytes (%d) in dst S/G\n",
				dst_len);
			qi_cache_मुक्त(edesc);
			वापस ERR_PTR(dst_nents);
		पूर्ण

		अगर (src_nents) अणु
			mapped_src_nents = dma_map_sg(dev, req->src, src_nents,
						      DMA_TO_DEVICE);
			अगर (unlikely(!mapped_src_nents)) अणु
				dev_err(dev, "unable to map source\n");
				qi_cache_मुक्त(edesc);
				वापस ERR_PTR(-ENOMEM);
			पूर्ण
		पूर्ण अन्यथा अणु
			mapped_src_nents = 0;
		पूर्ण

		अगर (dst_nents) अणु
			mapped_dst_nents = dma_map_sg(dev, req->dst, dst_nents,
						      DMA_FROM_DEVICE);
			अगर (unlikely(!mapped_dst_nents)) अणु
				dev_err(dev, "unable to map destination\n");
				dma_unmap_sg(dev, req->src, src_nents,
					     DMA_TO_DEVICE);
				qi_cache_मुक्त(edesc);
				वापस ERR_PTR(-ENOMEM);
			पूर्ण
		पूर्ण अन्यथा अणु
			mapped_dst_nents = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		src_len = req->assoclen + req->cryptlen +
			  (encrypt ? authsize : 0);

		src_nents = sg_nents_क्रम_len(req->src, src_len);
		अगर (unlikely(src_nents < 0)) अणु
			dev_err(dev, "Insufficient bytes (%d) in src S/G\n",
				src_len);
			qi_cache_मुक्त(edesc);
			वापस ERR_PTR(src_nents);
		पूर्ण

		mapped_src_nents = dma_map_sg(dev, req->src, src_nents,
					      DMA_BIसूचीECTIONAL);
		अगर (unlikely(!mapped_src_nents)) अणु
			dev_err(dev, "unable to map source\n");
			qi_cache_मुक्त(edesc);
			वापस ERR_PTR(-ENOMEM);
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
	qm_sg_nents = 1 + !!ivsize + mapped_src_nents;
	अगर (mapped_dst_nents > 1)
		qm_sg_nents += pad_sg_nents(mapped_dst_nents);
	अन्यथा अगर ((req->src == req->dst) && (mapped_src_nents > 1))
		qm_sg_nents = max(pad_sg_nents(qm_sg_nents),
				  1 + !!ivsize +
				  pad_sg_nents(mapped_src_nents));
	अन्यथा
		qm_sg_nents = pad_sg_nents(qm_sg_nents);

	sg_table = &edesc->sgt[0];
	qm_sg_bytes = qm_sg_nents * माप(*sg_table);
	अगर (unlikely(दुरत्व(काष्ठा aead_edesc, sgt) + qm_sg_bytes + ivsize >
		     CAAM_QI_MEMCACHE_SIZE)) अणु
		dev_err(dev, "No space for %d S/G entries and/or %dB IV\n",
			qm_sg_nents, ivsize);
		caam_unmap(dev, req->src, req->dst, src_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		qi_cache_मुक्त(edesc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (ivsize) अणु
		u8 *iv = (u8 *)(sg_table + qm_sg_nents);

		/* Make sure IV is located in a DMAable area */
		स_नकल(iv, req->iv, ivsize);

		iv_dma = dma_map_single(dev, iv, ivsize, DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, iv_dma)) अणु
			dev_err(dev, "unable to map IV\n");
			caam_unmap(dev, req->src, req->dst, src_nents,
				   dst_nents, 0, 0, DMA_NONE, 0, 0);
			qi_cache_मुक्त(edesc);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	edesc->src_nents = src_nents;
	edesc->dst_nents = dst_nents;
	edesc->iv_dma = iv_dma;

	अगर ((alg->caam.class1_alg_type & OP_ALG_ALGSEL_MASK) ==
	    OP_ALG_ALGSEL_CHACHA20 && ivsize != CHACHAPOLY_IV_SIZE)
		/*
		 * The associated data comes alपढ़ोy with the IV but we need
		 * to skip it when we authenticate or encrypt...
		 */
		edesc->assoclen = cpu_to_caam32(req->assoclen - ivsize);
	अन्यथा
		edesc->assoclen = cpu_to_caam32(req->assoclen);
	edesc->assoclen_dma = dma_map_single(dev, &edesc->assoclen, 4,
					     DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, edesc->assoclen_dma)) अणु
		dev_err(dev, "unable to map assoclen\n");
		caam_unmap(dev, req->src, req->dst, src_nents, dst_nents,
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

	qm_sg_dma = dma_map_single(dev, sg_table, qm_sg_bytes, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, qm_sg_dma)) अणु
		dev_err(dev, "unable to map S/G table\n");
		dma_unmap_single(dev, edesc->assoclen_dma, 4, DMA_TO_DEVICE);
		caam_unmap(dev, req->src, req->dst, src_nents, dst_nents,
			   iv_dma, ivsize, DMA_TO_DEVICE, 0, 0);
		qi_cache_मुक्त(edesc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	edesc->qm_sg_dma = qm_sg_dma;
	edesc->qm_sg_bytes = qm_sg_bytes;

	out_len = req->assoclen + req->cryptlen +
		  (encrypt ? ctx->authsize : (-ctx->authsize));
	in_len = 4 + ivsize + req->assoclen + req->cryptlen;

	स_रखो(&req_ctx->fd_flt, 0, माप(req_ctx->fd_flt));
	dpaa2_fl_set_final(in_fle, true);
	dpaa2_fl_set_क्रमmat(in_fle, dpaa2_fl_sg);
	dpaa2_fl_set_addr(in_fle, qm_sg_dma);
	dpaa2_fl_set_len(in_fle, in_len);

	अगर (req->dst == req->src) अणु
		अगर (mapped_src_nents == 1) अणु
			dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_single);
			dpaa2_fl_set_addr(out_fle, sg_dma_address(req->src));
		पूर्ण अन्यथा अणु
			dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_sg);
			dpaa2_fl_set_addr(out_fle, qm_sg_dma +
					  (1 + !!ivsize) * माप(*sg_table));
		पूर्ण
	पूर्ण अन्यथा अगर (!mapped_dst_nents) अणु
		/*
		 * crypto engine requires the output entry to be present when
		 * "frame list" FD is used.
		 * Since engine करोes not support FMT=2'b11 (unused entry type),
		 * leaving out_fle zeroized is the best option.
		 */
		जाओ skip_out_fle;
	पूर्ण अन्यथा अगर (mapped_dst_nents == 1) अणु
		dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_single);
		dpaa2_fl_set_addr(out_fle, sg_dma_address(req->dst));
	पूर्ण अन्यथा अणु
		dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_sg);
		dpaa2_fl_set_addr(out_fle, qm_sg_dma + qm_sg_index *
				  माप(*sg_table));
	पूर्ण

	dpaa2_fl_set_len(out_fle, out_len);

skip_out_fle:
	वापस edesc;
पूर्ण

अटल पूर्णांक chachapoly_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	काष्ठा device *dev = ctx->dev;
	काष्ठा caam_flc *flc;
	u32 *desc;

	अगर (!ctx->cdata.keylen || !ctx->authsize)
		वापस 0;

	flc = &ctx->flc[ENCRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_chachapoly(desc, &ctx->cdata, &ctx->adata, ivsize,
			       ctx->authsize, true, true);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[ENCRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

	flc = &ctx->flc[DECRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_chachapoly(desc, &ctx->cdata, &ctx->adata, ivsize,
			       ctx->authsize, false, true);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[DECRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

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

अटल पूर्णांक gcm_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *dev = ctx->dev;
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	काष्ठा caam_flc *flc;
	u32 *desc;
	पूर्णांक rem_bytes = CAAM_DESC_BYTES_MAX - DESC_JOB_IO_LEN -
			ctx->cdata.keylen;

	अगर (!ctx->cdata.keylen || !ctx->authsize)
		वापस 0;

	/*
	 * AES GCM encrypt shared descriptor
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

	flc = &ctx->flc[ENCRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_gcm_encap(desc, &ctx->cdata, ivsize, ctx->authsize, true);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[ENCRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_QI_GCM_DEC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
		ctx->cdata.key_virt = ctx->key;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	flc = &ctx->flc[DECRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_gcm_decap(desc, &ctx->cdata, ivsize, ctx->authsize, true);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[DECRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

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
	काष्ठा device *dev = ctx->dev;
	पूर्णांक ret;

	ret = aes_check_keylen(keylen);
	अगर (ret)
		वापस ret;
	prपूर्णांक_hex_dump_debug("key in @" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);

	स_नकल(ctx->key, key, keylen);
	dma_sync_single_क्रम_device(dev, ctx->key_dma, keylen, ctx->dir);
	ctx->cdata.keylen = keylen;

	वापस gcm_set_sh_desc(aead);
पूर्ण

अटल पूर्णांक rfc4106_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *dev = ctx->dev;
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	काष्ठा caam_flc *flc;
	u32 *desc;
	पूर्णांक rem_bytes = CAAM_DESC_BYTES_MAX - DESC_JOB_IO_LEN -
			ctx->cdata.keylen;

	अगर (!ctx->cdata.keylen || !ctx->authsize)
		वापस 0;

	ctx->cdata.key_virt = ctx->key;

	/*
	 * RFC4106 encrypt shared descriptor
	 * Job Descriptor and Shared Descriptor
	 * must fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_QI_RFC4106_ENC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	flc = &ctx->flc[ENCRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_rfc4106_encap(desc, &ctx->cdata, ivsize, ctx->authsize,
				  true);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[ENCRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_QI_RFC4106_DEC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	flc = &ctx->flc[DECRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_rfc4106_decap(desc, &ctx->cdata, ivsize, ctx->authsize,
				  true);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[DECRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

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
	काष्ठा device *dev = ctx->dev;
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
	dma_sync_single_क्रम_device(dev, ctx->key_dma, ctx->cdata.keylen,
				   ctx->dir);

	वापस rfc4106_set_sh_desc(aead);
पूर्ण

अटल पूर्णांक rfc4543_set_sh_desc(काष्ठा crypto_aead *aead)
अणु
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा device *dev = ctx->dev;
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(aead);
	काष्ठा caam_flc *flc;
	u32 *desc;
	पूर्णांक rem_bytes = CAAM_DESC_BYTES_MAX - DESC_JOB_IO_LEN -
			ctx->cdata.keylen;

	अगर (!ctx->cdata.keylen || !ctx->authsize)
		वापस 0;

	ctx->cdata.key_virt = ctx->key;

	/*
	 * RFC4543 encrypt shared descriptor
	 * Job Descriptor and Shared Descriptor
	 * must fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_QI_RFC4543_ENC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	flc = &ctx->flc[ENCRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_rfc4543_encap(desc, &ctx->cdata, ivsize, ctx->authsize,
				  true);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[ENCRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit पूर्णांकo the 64-word Descriptor h/w Buffer
	 */
	अगर (rem_bytes >= DESC_QI_RFC4543_DEC_LEN) अणु
		ctx->cdata.key_अंतरभूत = true;
	पूर्ण अन्यथा अणु
		ctx->cdata.key_अंतरभूत = false;
		ctx->cdata.key_dma = ctx->key_dma;
	पूर्ण

	flc = &ctx->flc[DECRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_rfc4543_decap(desc, &ctx->cdata, ivsize, ctx->authsize,
				  true);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[DECRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

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
	काष्ठा device *dev = ctx->dev;
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
	dma_sync_single_क्रम_device(dev, ctx->key_dma, ctx->cdata.keylen,
				   ctx->dir);

	वापस rfc4543_set_sh_desc(aead);
पूर्ण

अटल पूर्णांक skcipher_setkey(काष्ठा crypto_skcipher *skcipher, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen, स्थिर u32 ctx1_iv_off)
अणु
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा caam_skcipher_alg *alg =
		container_of(crypto_skcipher_alg(skcipher),
			     काष्ठा caam_skcipher_alg, skcipher);
	काष्ठा device *dev = ctx->dev;
	काष्ठा caam_flc *flc;
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);
	u32 *desc;
	स्थिर bool is_rfc3686 = alg->caam.rfc3686;

	prपूर्णांक_hex_dump_debug("key in @" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);

	ctx->cdata.keylen = keylen;
	ctx->cdata.key_virt = key;
	ctx->cdata.key_अंतरभूत = true;

	/* skcipher_encrypt shared descriptor */
	flc = &ctx->flc[ENCRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_skcipher_encap(desc, &ctx->cdata, ivsize, is_rfc3686,
				   ctx1_iv_off);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[ENCRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

	/* skcipher_decrypt shared descriptor */
	flc = &ctx->flc[DECRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_skcipher_decap(desc, &ctx->cdata, ivsize, is_rfc3686,
				   ctx1_iv_off);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[DECRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

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

अटल पूर्णांक chacha20_skcipher_setkey(काष्ठा crypto_skcipher *skcipher,
				    स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	अगर (keylen != CHACHA_KEY_SIZE)
		वापस -EINVAL;

	वापस skcipher_setkey(skcipher, key, keylen, 0);
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
	काष्ठा device *dev = ctx->dev;
	काष्ठा dpaa2_caam_priv *priv = dev_get_drvdata(dev);
	काष्ठा caam_flc *flc;
	u32 *desc;
	पूर्णांक err;

	err = xts_verअगरy_key(skcipher, key, keylen);
	अगर (err) अणु
		dev_dbg(dev, "key size mismatch\n");
		वापस err;
	पूर्ण

	अगर (keylen != 2 * AES_KEYSIZE_128 && keylen != 2 * AES_KEYSIZE_256)
		ctx->xts_key_fallback = true;

	अगर (priv->sec_attr.era <= 8 || ctx->xts_key_fallback) अणु
		err = crypto_skcipher_setkey(ctx->fallback, key, keylen);
		अगर (err)
			वापस err;
	पूर्ण

	ctx->cdata.keylen = keylen;
	ctx->cdata.key_virt = key;
	ctx->cdata.key_अंतरभूत = true;

	/* xts_skcipher_encrypt shared descriptor */
	flc = &ctx->flc[ENCRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_xts_skcipher_encap(desc, &ctx->cdata);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[ENCRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

	/* xts_skcipher_decrypt shared descriptor */
	flc = &ctx->flc[DECRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_xts_skcipher_decap(desc, &ctx->cdata);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(dev, ctx->flc_dma[DECRYPT],
				   माप(flc->flc) + desc_bytes(desc),
				   ctx->dir);

	वापस 0;
पूर्ण

अटल काष्ठा skcipher_edesc *skcipher_edesc_alloc(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा caam_request *req_ctx = skcipher_request_ctx(req);
	काष्ठा dpaa2_fl_entry *in_fle = &req_ctx->fd_flt[1];
	काष्ठा dpaa2_fl_entry *out_fle = &req_ctx->fd_flt[0];
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा device *dev = ctx->dev;
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	पूर्णांक src_nents, mapped_src_nents, dst_nents = 0, mapped_dst_nents = 0;
	काष्ठा skcipher_edesc *edesc;
	dma_addr_t iv_dma;
	u8 *iv;
	पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);
	पूर्णांक dst_sg_idx, qm_sg_ents, qm_sg_bytes;
	काष्ठा dpaa2_sg_entry *sg_table;

	src_nents = sg_nents_क्रम_len(req->src, req->cryptlen);
	अगर (unlikely(src_nents < 0)) अणु
		dev_err(dev, "Insufficient bytes (%d) in src S/G\n",
			req->cryptlen);
		वापस ERR_PTR(src_nents);
	पूर्ण

	अगर (unlikely(req->dst != req->src)) अणु
		dst_nents = sg_nents_क्रम_len(req->dst, req->cryptlen);
		अगर (unlikely(dst_nents < 0)) अणु
			dev_err(dev, "Insufficient bytes (%d) in dst S/G\n",
				req->cryptlen);
			वापस ERR_PTR(dst_nents);
		पूर्ण

		mapped_src_nents = dma_map_sg(dev, req->src, src_nents,
					      DMA_TO_DEVICE);
		अगर (unlikely(!mapped_src_nents)) अणु
			dev_err(dev, "unable to map source\n");
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		mapped_dst_nents = dma_map_sg(dev, req->dst, dst_nents,
					      DMA_FROM_DEVICE);
		अगर (unlikely(!mapped_dst_nents)) अणु
			dev_err(dev, "unable to map destination\n");
			dma_unmap_sg(dev, req->src, src_nents, DMA_TO_DEVICE);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण अन्यथा अणु
		mapped_src_nents = dma_map_sg(dev, req->src, src_nents,
					      DMA_BIसूचीECTIONAL);
		अगर (unlikely(!mapped_src_nents)) अणु
			dev_err(dev, "unable to map source\n");
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

	qm_sg_bytes = qm_sg_ents * माप(काष्ठा dpaa2_sg_entry);
	अगर (unlikely(दुरत्व(काष्ठा skcipher_edesc, sgt) + qm_sg_bytes +
		     ivsize > CAAM_QI_MEMCACHE_SIZE)) अणु
		dev_err(dev, "No space for %d S/G entries and/or %dB IV\n",
			qm_sg_ents, ivsize);
		caam_unmap(dev, req->src, req->dst, src_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* allocate space क्रम base edesc, link tables and IV */
	edesc = qi_cache_zalloc(GFP_DMA | flags);
	अगर (unlikely(!edesc)) अणु
		dev_err(dev, "could not allocate extended descriptor\n");
		caam_unmap(dev, req->src, req->dst, src_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* Make sure IV is located in a DMAable area */
	sg_table = &edesc->sgt[0];
	iv = (u8 *)(sg_table + qm_sg_ents);
	स_नकल(iv, req->iv, ivsize);

	iv_dma = dma_map_single(dev, iv, ivsize, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, iv_dma)) अणु
		dev_err(dev, "unable to map IV\n");
		caam_unmap(dev, req->src, req->dst, src_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		qi_cache_मुक्त(edesc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	edesc->src_nents = src_nents;
	edesc->dst_nents = dst_nents;
	edesc->iv_dma = iv_dma;
	edesc->qm_sg_bytes = qm_sg_bytes;

	dma_to_qm_sg_one(sg_table, iv_dma, ivsize, 0);
	sg_to_qm_sg(req->src, req->cryptlen, sg_table + 1, 0);

	अगर (req->src != req->dst)
		sg_to_qm_sg(req->dst, req->cryptlen, sg_table + dst_sg_idx, 0);

	dma_to_qm_sg_one(sg_table + dst_sg_idx + mapped_dst_nents, iv_dma,
			 ivsize, 0);

	edesc->qm_sg_dma = dma_map_single(dev, sg_table, edesc->qm_sg_bytes,
					  DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, edesc->qm_sg_dma)) अणु
		dev_err(dev, "unable to map S/G table\n");
		caam_unmap(dev, req->src, req->dst, src_nents, dst_nents,
			   iv_dma, ivsize, DMA_BIसूचीECTIONAL, 0, 0);
		qi_cache_मुक्त(edesc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	स_रखो(&req_ctx->fd_flt, 0, माप(req_ctx->fd_flt));
	dpaa2_fl_set_final(in_fle, true);
	dpaa2_fl_set_len(in_fle, req->cryptlen + ivsize);
	dpaa2_fl_set_len(out_fle, req->cryptlen + ivsize);

	dpaa2_fl_set_क्रमmat(in_fle, dpaa2_fl_sg);
	dpaa2_fl_set_addr(in_fle, edesc->qm_sg_dma);

	dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_sg);

	अगर (req->src == req->dst)
		dpaa2_fl_set_addr(out_fle, edesc->qm_sg_dma +
				  माप(*sg_table));
	अन्यथा
		dpaa2_fl_set_addr(out_fle, edesc->qm_sg_dma + dst_sg_idx *
				  माप(*sg_table));

	वापस edesc;
पूर्ण

अटल व्योम aead_unmap(काष्ठा device *dev, काष्ठा aead_edesc *edesc,
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

अटल व्योम aead_encrypt_करोne(व्योम *cbk_ctx, u32 status)
अणु
	काष्ठा crypto_async_request *areq = cbk_ctx;
	काष्ठा aead_request *req = container_of(areq, काष्ठा aead_request,
						base);
	काष्ठा caam_request *req_ctx = to_caam_req(areq);
	काष्ठा aead_edesc *edesc = req_ctx->edesc;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	पूर्णांक ecode = 0;

	dev_dbg(ctx->dev, "%s %d: err 0x%x\n", __func__, __LINE__, status);

	अगर (unlikely(status))
		ecode = caam_qi2_strstatus(ctx->dev, status);

	aead_unmap(ctx->dev, edesc, req);
	qi_cache_मुक्त(edesc);
	aead_request_complete(req, ecode);
पूर्ण

अटल व्योम aead_decrypt_करोne(व्योम *cbk_ctx, u32 status)
अणु
	काष्ठा crypto_async_request *areq = cbk_ctx;
	काष्ठा aead_request *req = container_of(areq, काष्ठा aead_request,
						base);
	काष्ठा caam_request *req_ctx = to_caam_req(areq);
	काष्ठा aead_edesc *edesc = req_ctx->edesc;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	पूर्णांक ecode = 0;

	dev_dbg(ctx->dev, "%s %d: err 0x%x\n", __func__, __LINE__, status);

	अगर (unlikely(status))
		ecode = caam_qi2_strstatus(ctx->dev, status);

	aead_unmap(ctx->dev, edesc, req);
	qi_cache_मुक्त(edesc);
	aead_request_complete(req, ecode);
पूर्ण

अटल पूर्णांक aead_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा aead_edesc *edesc;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा caam_request *caam_req = aead_request_ctx(req);
	पूर्णांक ret;

	/* allocate extended descriptor */
	edesc = aead_edesc_alloc(req, true);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	caam_req->flc = &ctx->flc[ENCRYPT];
	caam_req->flc_dma = ctx->flc_dma[ENCRYPT];
	caam_req->cbk = aead_encrypt_करोne;
	caam_req->ctx = &req->base;
	caam_req->edesc = edesc;
	ret = dpaa2_caam_enqueue(ctx->dev, caam_req);
	अगर (ret != -EINPROGRESS &&
	    !(ret == -EBUSY && req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)) अणु
		aead_unmap(ctx->dev, edesc, req);
		qi_cache_मुक्त(edesc);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aead_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा aead_edesc *edesc;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा caam_request *caam_req = aead_request_ctx(req);
	पूर्णांक ret;

	/* allocate extended descriptor */
	edesc = aead_edesc_alloc(req, false);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	caam_req->flc = &ctx->flc[DECRYPT];
	caam_req->flc_dma = ctx->flc_dma[DECRYPT];
	caam_req->cbk = aead_decrypt_करोne;
	caam_req->ctx = &req->base;
	caam_req->edesc = edesc;
	ret = dpaa2_caam_enqueue(ctx->dev, caam_req);
	अगर (ret != -EINPROGRESS &&
	    !(ret == -EBUSY && req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)) अणु
		aead_unmap(ctx->dev, edesc, req);
		qi_cache_मुक्त(edesc);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ipsec_gcm_encrypt(काष्ठा aead_request *req)
अणु
	वापस crypto_ipsec_check_assoclen(req->assoclen) ? : aead_encrypt(req);
पूर्ण

अटल पूर्णांक ipsec_gcm_decrypt(काष्ठा aead_request *req)
अणु
	वापस crypto_ipsec_check_assoclen(req->assoclen) ? : aead_decrypt(req);
पूर्ण

अटल व्योम skcipher_encrypt_करोne(व्योम *cbk_ctx, u32 status)
अणु
	काष्ठा crypto_async_request *areq = cbk_ctx;
	काष्ठा skcipher_request *req = skcipher_request_cast(areq);
	काष्ठा caam_request *req_ctx = to_caam_req(areq);
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा skcipher_edesc *edesc = req_ctx->edesc;
	पूर्णांक ecode = 0;
	पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);

	dev_dbg(ctx->dev, "%s %d: err 0x%x\n", __func__, __LINE__, status);

	अगर (unlikely(status))
		ecode = caam_qi2_strstatus(ctx->dev, status);

	prपूर्णांक_hex_dump_debug("dstiv  @" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, req->iv,
			     edesc->src_nents > 1 ? 100 : ivsize, 1);
	caam_dump_sg("dst    @" __stringअगरy(__LINE__)": ",
		     DUMP_PREFIX_ADDRESS, 16, 4, req->dst,
		     edesc->dst_nents > 1 ? 100 : req->cryptlen, 1);

	skcipher_unmap(ctx->dev, edesc, req);

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

अटल व्योम skcipher_decrypt_करोne(व्योम *cbk_ctx, u32 status)
अणु
	काष्ठा crypto_async_request *areq = cbk_ctx;
	काष्ठा skcipher_request *req = skcipher_request_cast(areq);
	काष्ठा caam_request *req_ctx = to_caam_req(areq);
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा skcipher_edesc *edesc = req_ctx->edesc;
	पूर्णांक ecode = 0;
	पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);

	dev_dbg(ctx->dev, "%s %d: err 0x%x\n", __func__, __LINE__, status);

	अगर (unlikely(status))
		ecode = caam_qi2_strstatus(ctx->dev, status);

	prपूर्णांक_hex_dump_debug("dstiv  @" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, req->iv,
			     edesc->src_nents > 1 ? 100 : ivsize, 1);
	caam_dump_sg("dst    @" __stringअगरy(__LINE__)": ",
		     DUMP_PREFIX_ADDRESS, 16, 4, req->dst,
		     edesc->dst_nents > 1 ? 100 : req->cryptlen, 1);

	skcipher_unmap(ctx->dev, edesc, req);

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

अटल अंतरभूत bool xts_skcipher_ivsize(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);

	वापस !!get_unaligned((u64 *)(req->iv + (ivsize / 2)));
पूर्ण

अटल पूर्णांक skcipher_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा skcipher_edesc *edesc;
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा caam_request *caam_req = skcipher_request_ctx(req);
	काष्ठा dpaa2_caam_priv *priv = dev_get_drvdata(ctx->dev);
	पूर्णांक ret;

	/*
	 * XTS is expected to वापस an error even क्रम input length = 0
	 * Note that the हाल input length < block size will be caught during
	 * HW offloading and वापस an error.
	 */
	अगर (!req->cryptlen && !ctx->fallback)
		वापस 0;

	अगर (ctx->fallback && ((priv->sec_attr.era <= 8 && xts_skcipher_ivsize(req)) ||
			      ctx->xts_key_fallback)) अणु
		skcipher_request_set_tfm(&caam_req->fallback_req, ctx->fallback);
		skcipher_request_set_callback(&caam_req->fallback_req,
					      req->base.flags,
					      req->base.complete,
					      req->base.data);
		skcipher_request_set_crypt(&caam_req->fallback_req, req->src,
					   req->dst, req->cryptlen, req->iv);

		वापस crypto_skcipher_encrypt(&caam_req->fallback_req);
	पूर्ण

	/* allocate extended descriptor */
	edesc = skcipher_edesc_alloc(req);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	caam_req->flc = &ctx->flc[ENCRYPT];
	caam_req->flc_dma = ctx->flc_dma[ENCRYPT];
	caam_req->cbk = skcipher_encrypt_करोne;
	caam_req->ctx = &req->base;
	caam_req->edesc = edesc;
	ret = dpaa2_caam_enqueue(ctx->dev, caam_req);
	अगर (ret != -EINPROGRESS &&
	    !(ret == -EBUSY && req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)) अणु
		skcipher_unmap(ctx->dev, edesc, req);
		qi_cache_मुक्त(edesc);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक skcipher_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा skcipher_edesc *edesc;
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा caam_request *caam_req = skcipher_request_ctx(req);
	काष्ठा dpaa2_caam_priv *priv = dev_get_drvdata(ctx->dev);
	पूर्णांक ret;

	/*
	 * XTS is expected to वापस an error even क्रम input length = 0
	 * Note that the हाल input length < block size will be caught during
	 * HW offloading and वापस an error.
	 */
	अगर (!req->cryptlen && !ctx->fallback)
		वापस 0;

	अगर (ctx->fallback && ((priv->sec_attr.era <= 8 && xts_skcipher_ivsize(req)) ||
			      ctx->xts_key_fallback)) अणु
		skcipher_request_set_tfm(&caam_req->fallback_req, ctx->fallback);
		skcipher_request_set_callback(&caam_req->fallback_req,
					      req->base.flags,
					      req->base.complete,
					      req->base.data);
		skcipher_request_set_crypt(&caam_req->fallback_req, req->src,
					   req->dst, req->cryptlen, req->iv);

		वापस crypto_skcipher_decrypt(&caam_req->fallback_req);
	पूर्ण

	/* allocate extended descriptor */
	edesc = skcipher_edesc_alloc(req);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	caam_req->flc = &ctx->flc[DECRYPT];
	caam_req->flc_dma = ctx->flc_dma[DECRYPT];
	caam_req->cbk = skcipher_decrypt_करोne;
	caam_req->ctx = &req->base;
	caam_req->edesc = edesc;
	ret = dpaa2_caam_enqueue(ctx->dev, caam_req);
	अगर (ret != -EINPROGRESS &&
	    !(ret == -EBUSY && req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)) अणु
		skcipher_unmap(ctx->dev, edesc, req);
		qi_cache_मुक्त(edesc);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक caam_cra_init(काष्ठा caam_ctx *ctx, काष्ठा caam_alg_entry *caam,
			 bool uses_dkp)
अणु
	dma_addr_t dma_addr;
	पूर्णांक i;

	/* copy descriptor header ढाँचा value */
	ctx->cdata.algtype = OP_TYPE_CLASS1_ALG | caam->class1_alg_type;
	ctx->adata.algtype = OP_TYPE_CLASS2_ALG | caam->class2_alg_type;

	ctx->dev = caam->dev;
	ctx->dir = uses_dkp ? DMA_BIसूचीECTIONAL : DMA_TO_DEVICE;

	dma_addr = dma_map_single_attrs(ctx->dev, ctx->flc,
					दुरत्व(काष्ठा caam_ctx, flc_dma),
					ctx->dir, DMA_ATTR_SKIP_CPU_SYNC);
	अगर (dma_mapping_error(ctx->dev, dma_addr)) अणु
		dev_err(ctx->dev, "unable to map key, shared descriptors\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < NUM_OP; i++)
		ctx->flc_dma[i] = dma_addr + i * माप(ctx->flc[i]);
	ctx->key_dma = dma_addr + NUM_OP * माप(ctx->flc[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक caam_cra_init_skcipher(काष्ठा crypto_skcipher *tfm)
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
			dev_err(caam_alg->caam.dev,
				"Failed to allocate %s fallback: %ld\n",
				tfm_name, PTR_ERR(fallback));
			वापस PTR_ERR(fallback);
		पूर्ण

		ctx->fallback = fallback;
		crypto_skcipher_set_reqsize(tfm, माप(काष्ठा caam_request) +
					    crypto_skcipher_reqsize(fallback));
	पूर्ण अन्यथा अणु
		crypto_skcipher_set_reqsize(tfm, माप(काष्ठा caam_request));
	पूर्ण

	ret = caam_cra_init(ctx, &caam_alg->caam, false);
	अगर (ret && ctx->fallback)
		crypto_मुक्त_skcipher(ctx->fallback);

	वापस ret;
पूर्ण

अटल पूर्णांक caam_cra_init_aead(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_alg *alg = crypto_aead_alg(tfm);
	काष्ठा caam_aead_alg *caam_alg = container_of(alg, typeof(*caam_alg),
						      aead);

	crypto_aead_set_reqsize(tfm, माप(काष्ठा caam_request));
	वापस caam_cra_init(crypto_aead_ctx(tfm), &caam_alg->caam,
			     !caam_alg->caam.nodkp);
पूर्ण

अटल व्योम caam_निकास_common(काष्ठा caam_ctx *ctx)
अणु
	dma_unmap_single_attrs(ctx->dev, ctx->flc_dma[0],
			       दुरत्व(काष्ठा caam_ctx, flc_dma), ctx->dir,
			       DMA_ATTR_SKIP_CPU_SYNC);
पूर्ण

अटल व्योम caam_cra_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा caam_ctx *ctx = crypto_skcipher_ctx(tfm);

	अगर (ctx->fallback)
		crypto_मुक्त_skcipher(ctx->fallback);
	caam_निकास_common(ctx);
पूर्ण

अटल व्योम caam_cra_निकास_aead(काष्ठा crypto_aead *tfm)
अणु
	caam_निकास_common(crypto_aead_ctx(tfm));
पूर्ण

अटल काष्ठा caam_skcipher_alg driver_algs[] = अणु
	अणु
		.skcipher = अणु
			.base = अणु
				.cra_name = "cbc(aes)",
				.cra_driver_name = "cbc-aes-caam-qi2",
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
				.cra_driver_name = "cbc-3des-caam-qi2",
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
				.cra_driver_name = "cbc-des-caam-qi2",
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
				.cra_driver_name = "ctr-aes-caam-qi2",
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
				.cra_driver_name = "rfc3686-ctr-aes-caam-qi2",
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
				.cra_driver_name = "xts-aes-caam-qi2",
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
				.cra_name = "chacha20",
				.cra_driver_name = "chacha20-caam-qi2",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = chacha20_skcipher_setkey,
			.encrypt = skcipher_encrypt,
			.decrypt = skcipher_decrypt,
			.min_keysize = CHACHA_KEY_SIZE,
			.max_keysize = CHACHA_KEY_SIZE,
			.ivsize = CHACHA_IV_SIZE,
		पूर्ण,
		.caam.class1_alg_type = OP_ALG_ALGSEL_CHACHA20,
	पूर्ण,
पूर्ण;

अटल काष्ठा caam_aead_alg driver_aeads[] = अणु
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "rfc4106(gcm(aes))",
				.cra_driver_name = "rfc4106-gcm-aes-caam-qi2",
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
				.cra_driver_name = "rfc4543-gcm-aes-caam-qi2",
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
				.cra_driver_name = "gcm-aes-caam-qi2",
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
						   "cbc-aes-caam-qi2",
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
						   "cbc-aes-caam-qi2",
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
						   "cbc-aes-caam-qi2",
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
						   "hmac-sha1-cbc-aes-caam-qi2",
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
						   "cbc-aes-caam-qi2",
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
						   "hmac-sha224-cbc-aes-caam-qi2",
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
						   "cbc-aes-caam-qi2",
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
						   "caam-qi2",
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
						   "cbc-aes-caam-qi2",
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
						   "caam-qi2",
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
						   "cbc-aes-caam-qi2",
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
						   "caam-qi2",
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
						   "cbc-des3_ede-caam-qi2",
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
						   "cbc-des3_ede-caam-qi2",
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
						   "cbc-des3_ede-caam-qi2",
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
						   "cbc-des3_ede-caam-qi2",
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
						   "cbc-des3_ede-caam-qi2",
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
						   "cbc-des3_ede-caam-qi2",
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
						   "cbc-des3_ede-caam-qi2",
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
						   "cbc-des3_ede-caam-qi2",
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
						   "cbc-des3_ede-caam-qi2",
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
						   "cbc-des3_ede-caam-qi2",
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
						   "cbc-des3_ede-caam-qi2",
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
						   "cbc-des3_ede-caam-qi2",
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
						   "cbc-des-caam-qi2",
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
						   "cbc-des-caam-qi2",
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
						   "cbc-des-caam-qi2",
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
						   "hmac-sha1-cbc-des-caam-qi2",
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
						   "cbc-des-caam-qi2",
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
						   "caam-qi2",
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
						   "cbc-des-caam-qi2",
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
						   "caam-qi2",
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
						   "cbc-des-caam-qi2",
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
						   "caam-qi2",
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
						   "cbc-des-caam-qi2",
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
						   "caam-qi2",
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
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(md5),"
					    "rfc3686(ctr(aes)))",
				.cra_driver_name = "authenc-hmac-md5-"
						   "rfc3686-ctr-aes-caam-qi2",
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
						   "rfc3686-ctr-aes-caam-qi2",
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
						   "rfc3686-ctr-aes-caam-qi2",
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
						   "rfc3686-ctr-aes-caam-qi2",
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
						   "rfc3686-ctr-aes-caam-qi2",
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
						   "rfc3686-ctr-aes-caam-qi2",
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
						   "rfc3686-ctr-aes-caam-qi2",
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
						   "rfc3686-ctr-aes-caam-qi2",
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
						   "rfc3686-ctr-aes-caam-qi2",
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
						   "rfc3686-ctr-aes-caam-qi2",
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
				.cra_name = "rfc7539(chacha20,poly1305)",
				.cra_driver_name = "rfc7539-chacha20-poly1305-"
						   "caam-qi2",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = chachapoly_setkey,
			.setauthsize = chachapoly_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
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
						   "poly1305-caam-qi2",
				.cra_blocksize = 1,
			पूर्ण,
			.setkey = chachapoly_setkey,
			.setauthsize = chachapoly_setauthsize,
			.encrypt = aead_encrypt,
			.decrypt = aead_decrypt,
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
	अणु
		.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha512),"
					    "rfc3686(ctr(aes)))",
				.cra_driver_name = "authenc-hmac-sha512-"
						   "rfc3686-ctr-aes-caam-qi2",
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
						   "rfc3686-ctr-aes-caam-qi2",
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
पूर्ण;

अटल व्योम caam_skcipher_alg_init(काष्ठा caam_skcipher_alg *t_alg)
अणु
	काष्ठा skcipher_alg *alg = &t_alg->skcipher;

	alg->base.cra_module = THIS_MODULE;
	alg->base.cra_priority = CAAM_CRA_PRIORITY;
	alg->base.cra_ctxsize = माप(काष्ठा caam_ctx);
	alg->base.cra_flags |= (CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY |
			      CRYPTO_ALG_KERN_DRIVER_ONLY);

	alg->init = caam_cra_init_skcipher;
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

	alg->init = caam_cra_init_aead;
	alg->निकास = caam_cra_निकास_aead;
पूर्ण

/* max hash key is max split key size */
#घोषणा CAAM_MAX_HASH_KEY_SIZE		(SHA512_DIGEST_SIZE * 2)

#घोषणा CAAM_MAX_HASH_BLOCK_SIZE	SHA512_BLOCK_SIZE

/* caam context sizes क्रम hashes: running digest + 8 */
#घोषणा HASH_MSG_LEN			8
#घोषणा MAX_CTX_LEN			(HASH_MSG_LEN + SHA512_DIGEST_SIZE)

क्रमागत hash_optype अणु
	UPDATE = 0,
	UPDATE_FIRST,
	FINALIZE,
	DIGEST,
	HASH_NUM_OP
पूर्ण;

/**
 * काष्ठा caam_hash_ctx - ahash per-session context
 * @flc: Flow Contexts array
 * @key: authentication key
 * @flc_dma: I/O भव addresses of the Flow Contexts
 * @dev: dpseci device
 * @ctx_len: size of Context Register
 * @adata: hashing algorithm details
 */
काष्ठा caam_hash_ctx अणु
	काष्ठा caam_flc flc[HASH_NUM_OP];
	u8 key[CAAM_MAX_HASH_BLOCK_SIZE] ____cacheline_aligned;
	dma_addr_t flc_dma[HASH_NUM_OP];
	काष्ठा device *dev;
	पूर्णांक ctx_len;
	काष्ठा alginfo adata;
पूर्ण;

/* ahash state */
काष्ठा caam_hash_state अणु
	काष्ठा caam_request caam_req;
	dma_addr_t buf_dma;
	dma_addr_t ctx_dma;
	पूर्णांक ctx_dma_len;
	u8 buf[CAAM_MAX_HASH_BLOCK_SIZE] ____cacheline_aligned;
	पूर्णांक buflen;
	पूर्णांक next_buflen;
	u8 caam_ctx[MAX_CTX_LEN] ____cacheline_aligned;
	पूर्णांक (*update)(काष्ठा ahash_request *req);
	पूर्णांक (*final)(काष्ठा ahash_request *req);
	पूर्णांक (*finup)(काष्ठा ahash_request *req);
पूर्ण;

काष्ठा caam_export_state अणु
	u8 buf[CAAM_MAX_HASH_BLOCK_SIZE];
	u8 caam_ctx[MAX_CTX_LEN];
	पूर्णांक buflen;
	पूर्णांक (*update)(काष्ठा ahash_request *req);
	पूर्णांक (*final)(काष्ठा ahash_request *req);
	पूर्णांक (*finup)(काष्ठा ahash_request *req);
पूर्ण;

/* Map current buffer in state (अगर length > 0) and put it in link table */
अटल अंतरभूत पूर्णांक buf_map_to_qm_sg(काष्ठा device *dev,
				   काष्ठा dpaa2_sg_entry *qm_sg,
				   काष्ठा caam_hash_state *state)
अणु
	पूर्णांक buflen = state->buflen;

	अगर (!buflen)
		वापस 0;

	state->buf_dma = dma_map_single(dev, state->buf, buflen,
					DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, state->buf_dma)) अणु
		dev_err(dev, "unable to map buf\n");
		state->buf_dma = 0;
		वापस -ENOMEM;
	पूर्ण

	dma_to_qm_sg_one(qm_sg, state->buf_dma, buflen, 0);

	वापस 0;
पूर्ण

/* Map state->caam_ctx, and add it to link table */
अटल अंतरभूत पूर्णांक ctx_map_to_qm_sg(काष्ठा device *dev,
				   काष्ठा caam_hash_state *state, पूर्णांक ctx_len,
				   काष्ठा dpaa2_sg_entry *qm_sg, u32 flag)
अणु
	state->ctx_dma_len = ctx_len;
	state->ctx_dma = dma_map_single(dev, state->caam_ctx, ctx_len, flag);
	अगर (dma_mapping_error(dev, state->ctx_dma)) अणु
		dev_err(dev, "unable to map ctx\n");
		state->ctx_dma = 0;
		वापस -ENOMEM;
	पूर्ण

	dma_to_qm_sg_one(qm_sg, state->ctx_dma, ctx_len, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ahash_set_sh_desc(काष्ठा crypto_ahash *ahash)
अणु
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा dpaa2_caam_priv *priv = dev_get_drvdata(ctx->dev);
	काष्ठा caam_flc *flc;
	u32 *desc;

	/* ahash_update shared descriptor */
	flc = &ctx->flc[UPDATE];
	desc = flc->sh_desc;
	cnstr_shdsc_ahash(desc, &ctx->adata, OP_ALG_AS_UPDATE, ctx->ctx_len,
			  ctx->ctx_len, true, priv->sec_attr.era);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(ctx->dev, ctx->flc_dma[UPDATE],
				   desc_bytes(desc), DMA_BIसूचीECTIONAL);
	prपूर्णांक_hex_dump_debug("ahash update shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	/* ahash_update_first shared descriptor */
	flc = &ctx->flc[UPDATE_FIRST];
	desc = flc->sh_desc;
	cnstr_shdsc_ahash(desc, &ctx->adata, OP_ALG_AS_INIT, ctx->ctx_len,
			  ctx->ctx_len, false, priv->sec_attr.era);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(ctx->dev, ctx->flc_dma[UPDATE_FIRST],
				   desc_bytes(desc), DMA_BIसूचीECTIONAL);
	prपूर्णांक_hex_dump_debug("ahash update first shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	/* ahash_final shared descriptor */
	flc = &ctx->flc[FINALIZE];
	desc = flc->sh_desc;
	cnstr_shdsc_ahash(desc, &ctx->adata, OP_ALG_AS_FINALIZE, digestsize,
			  ctx->ctx_len, true, priv->sec_attr.era);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(ctx->dev, ctx->flc_dma[FINALIZE],
				   desc_bytes(desc), DMA_BIसूचीECTIONAL);
	prपूर्णांक_hex_dump_debug("ahash final shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	/* ahash_digest shared descriptor */
	flc = &ctx->flc[DIGEST];
	desc = flc->sh_desc;
	cnstr_shdsc_ahash(desc, &ctx->adata, OP_ALG_AS_INITFINAL, digestsize,
			  ctx->ctx_len, false, priv->sec_attr.era);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_क्रम_device(ctx->dev, ctx->flc_dma[DIGEST],
				   desc_bytes(desc), DMA_BIसूचीECTIONAL);
	prपूर्णांक_hex_dump_debug("ahash digest shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	वापस 0;
पूर्ण

काष्ठा split_key_sh_result अणु
	काष्ठा completion completion;
	पूर्णांक err;
	काष्ठा device *dev;
पूर्ण;

अटल व्योम split_key_sh_करोne(व्योम *cbk_ctx, u32 err)
अणु
	काष्ठा split_key_sh_result *res = cbk_ctx;

	dev_dbg(res->dev, "%s %d: err 0x%x\n", __func__, __LINE__, err);

	res->err = err ? caam_qi2_strstatus(res->dev, err) : 0;
	complete(&res->completion);
पूर्ण

/* Digest hash size अगर it is too large */
अटल पूर्णांक hash_digest_key(काष्ठा caam_hash_ctx *ctx, u32 *keylen, u8 *key,
			   u32 digestsize)
अणु
	काष्ठा caam_request *req_ctx;
	u32 *desc;
	काष्ठा split_key_sh_result result;
	dma_addr_t key_dma;
	काष्ठा caam_flc *flc;
	dma_addr_t flc_dma;
	पूर्णांक ret = -ENOMEM;
	काष्ठा dpaa2_fl_entry *in_fle, *out_fle;

	req_ctx = kzalloc(माप(*req_ctx), GFP_KERNEL | GFP_DMA);
	अगर (!req_ctx)
		वापस -ENOMEM;

	in_fle = &req_ctx->fd_flt[1];
	out_fle = &req_ctx->fd_flt[0];

	flc = kzalloc(माप(*flc), GFP_KERNEL | GFP_DMA);
	अगर (!flc)
		जाओ err_flc;

	key_dma = dma_map_single(ctx->dev, key, *keylen, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(ctx->dev, key_dma)) अणु
		dev_err(ctx->dev, "unable to map key memory\n");
		जाओ err_key_dma;
	पूर्ण

	desc = flc->sh_desc;

	init_sh_desc(desc, 0);

	/* descriptor to perक्रमm unkeyed hash on key_in */
	append_operation(desc, ctx->adata.algtype | OP_ALG_ENCRYPT |
			 OP_ALG_AS_INITFINAL);
	append_seq_fअगरo_load(desc, *keylen, FIFOLD_CLASS_CLASS2 |
			     FIFOLD_TYPE_LAST2 | FIFOLD_TYPE_MSG);
	append_seq_store(desc, digestsize, LDST_CLASS_2_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);

	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	flc_dma = dma_map_single(ctx->dev, flc, माप(flc->flc) +
				 desc_bytes(desc), DMA_TO_DEVICE);
	अगर (dma_mapping_error(ctx->dev, flc_dma)) अणु
		dev_err(ctx->dev, "unable to map shared descriptor\n");
		जाओ err_flc_dma;
	पूर्ण

	dpaa2_fl_set_final(in_fle, true);
	dpaa2_fl_set_क्रमmat(in_fle, dpaa2_fl_single);
	dpaa2_fl_set_addr(in_fle, key_dma);
	dpaa2_fl_set_len(in_fle, *keylen);
	dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_single);
	dpaa2_fl_set_addr(out_fle, key_dma);
	dpaa2_fl_set_len(out_fle, digestsize);

	prपूर्णांक_hex_dump_debug("key_in@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key, *keylen, 1);
	prपूर्णांक_hex_dump_debug("shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	result.err = 0;
	init_completion(&result.completion);
	result.dev = ctx->dev;

	req_ctx->flc = flc;
	req_ctx->flc_dma = flc_dma;
	req_ctx->cbk = split_key_sh_करोne;
	req_ctx->ctx = &result;

	ret = dpaa2_caam_enqueue(ctx->dev, req_ctx);
	अगर (ret == -EINPROGRESS) अणु
		/* in progress */
		रुको_क्रम_completion(&result.completion);
		ret = result.err;
		prपूर्णांक_hex_dump_debug("digested key@" __stringअगरy(__LINE__)": ",
				     DUMP_PREFIX_ADDRESS, 16, 4, key,
				     digestsize, 1);
	पूर्ण

	dma_unmap_single(ctx->dev, flc_dma, माप(flc->flc) + desc_bytes(desc),
			 DMA_TO_DEVICE);
err_flc_dma:
	dma_unmap_single(ctx->dev, key_dma, *keylen, DMA_BIसूचीECTIONAL);
err_key_dma:
	kमुक्त(flc);
err_flc:
	kमुक्त(req_ctx);

	*keylen = digestsize;

	वापस ret;
पूर्ण

अटल पूर्णांक ahash_setkey(काष्ठा crypto_ahash *ahash, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	अचिन्हित पूर्णांक blocksize = crypto_tfm_alg_blocksize(&ahash->base);
	अचिन्हित पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	पूर्णांक ret;
	u8 *hashed_key = शून्य;

	dev_dbg(ctx->dev, "keylen %d blocksize %d\n", keylen, blocksize);

	अगर (keylen > blocksize) अणु
		hashed_key = kmemdup(key, keylen, GFP_KERNEL | GFP_DMA);
		अगर (!hashed_key)
			वापस -ENOMEM;
		ret = hash_digest_key(ctx, &keylen, hashed_key, digestsize);
		अगर (ret)
			जाओ bad_मुक्त_key;
		key = hashed_key;
	पूर्ण

	ctx->adata.keylen = keylen;
	ctx->adata.keylen_pad = split_key_len(ctx->adata.algtype &
					      OP_ALG_ALGSEL_MASK);
	अगर (ctx->adata.keylen_pad > CAAM_MAX_HASH_KEY_SIZE)
		जाओ bad_मुक्त_key;

	ctx->adata.key_virt = key;
	ctx->adata.key_अंतरभूत = true;

	/*
	 * In हाल |user key| > |derived key|, using DKP<imm,imm> would result
	 * in invalid opcodes (last bytes of user key) in the resulting
	 * descriptor. Use DKP<ptr,imm> instead => both भव and dma key
	 * addresses are needed.
	 */
	अगर (keylen > ctx->adata.keylen_pad) अणु
		स_नकल(ctx->key, key, keylen);
		dma_sync_single_क्रम_device(ctx->dev, ctx->adata.key_dma,
					   ctx->adata.keylen_pad,
					   DMA_TO_DEVICE);
	पूर्ण

	ret = ahash_set_sh_desc(ahash);
	kमुक्त(hashed_key);
	वापस ret;
bad_मुक्त_key:
	kमुक्त(hashed_key);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम ahash_unmap(काष्ठा device *dev, काष्ठा ahash_edesc *edesc,
			       काष्ठा ahash_request *req)
अणु
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);

	अगर (edesc->src_nents)
		dma_unmap_sg(dev, req->src, edesc->src_nents, DMA_TO_DEVICE);

	अगर (edesc->qm_sg_bytes)
		dma_unmap_single(dev, edesc->qm_sg_dma, edesc->qm_sg_bytes,
				 DMA_TO_DEVICE);

	अगर (state->buf_dma) अणु
		dma_unmap_single(dev, state->buf_dma, state->buflen,
				 DMA_TO_DEVICE);
		state->buf_dma = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ahash_unmap_ctx(काष्ठा device *dev,
				   काष्ठा ahash_edesc *edesc,
				   काष्ठा ahash_request *req, u32 flag)
अणु
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);

	अगर (state->ctx_dma) अणु
		dma_unmap_single(dev, state->ctx_dma, state->ctx_dma_len, flag);
		state->ctx_dma = 0;
	पूर्ण
	ahash_unmap(dev, edesc, req);
पूर्ण

अटल व्योम ahash_करोne(व्योम *cbk_ctx, u32 status)
अणु
	काष्ठा crypto_async_request *areq = cbk_ctx;
	काष्ठा ahash_request *req = ahash_request_cast(areq);
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा ahash_edesc *edesc = state->caam_req.edesc;
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	पूर्णांक ecode = 0;

	dev_dbg(ctx->dev, "%s %d: err 0x%x\n", __func__, __LINE__, status);

	अगर (unlikely(status))
		ecode = caam_qi2_strstatus(ctx->dev, status);

	ahash_unmap_ctx(ctx->dev, edesc, req, DMA_FROM_DEVICE);
	स_नकल(req->result, state->caam_ctx, digestsize);
	qi_cache_मुक्त(edesc);

	prपूर्णांक_hex_dump_debug("ctx@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, state->caam_ctx,
			     ctx->ctx_len, 1);

	req->base.complete(&req->base, ecode);
पूर्ण

अटल व्योम ahash_करोne_bi(व्योम *cbk_ctx, u32 status)
अणु
	काष्ठा crypto_async_request *areq = cbk_ctx;
	काष्ठा ahash_request *req = ahash_request_cast(areq);
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा ahash_edesc *edesc = state->caam_req.edesc;
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	पूर्णांक ecode = 0;

	dev_dbg(ctx->dev, "%s %d: err 0x%x\n", __func__, __LINE__, status);

	अगर (unlikely(status))
		ecode = caam_qi2_strstatus(ctx->dev, status);

	ahash_unmap_ctx(ctx->dev, edesc, req, DMA_BIसूचीECTIONAL);
	qi_cache_मुक्त(edesc);

	scatterwalk_map_and_copy(state->buf, req->src,
				 req->nbytes - state->next_buflen,
				 state->next_buflen, 0);
	state->buflen = state->next_buflen;

	prपूर्णांक_hex_dump_debug("buf@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, state->buf,
			     state->buflen, 1);

	prपूर्णांक_hex_dump_debug("ctx@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, state->caam_ctx,
			     ctx->ctx_len, 1);
	अगर (req->result)
		prपूर्णांक_hex_dump_debug("result@" __stringअगरy(__LINE__)": ",
				     DUMP_PREFIX_ADDRESS, 16, 4, req->result,
				     crypto_ahash_digestsize(ahash), 1);

	req->base.complete(&req->base, ecode);
पूर्ण

अटल व्योम ahash_करोne_ctx_src(व्योम *cbk_ctx, u32 status)
अणु
	काष्ठा crypto_async_request *areq = cbk_ctx;
	काष्ठा ahash_request *req = ahash_request_cast(areq);
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा ahash_edesc *edesc = state->caam_req.edesc;
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	पूर्णांक ecode = 0;

	dev_dbg(ctx->dev, "%s %d: err 0x%x\n", __func__, __LINE__, status);

	अगर (unlikely(status))
		ecode = caam_qi2_strstatus(ctx->dev, status);

	ahash_unmap_ctx(ctx->dev, edesc, req, DMA_BIसूचीECTIONAL);
	स_नकल(req->result, state->caam_ctx, digestsize);
	qi_cache_मुक्त(edesc);

	prपूर्णांक_hex_dump_debug("ctx@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, state->caam_ctx,
			     ctx->ctx_len, 1);

	req->base.complete(&req->base, ecode);
पूर्ण

अटल व्योम ahash_करोne_ctx_dst(व्योम *cbk_ctx, u32 status)
अणु
	काष्ठा crypto_async_request *areq = cbk_ctx;
	काष्ठा ahash_request *req = ahash_request_cast(areq);
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा ahash_edesc *edesc = state->caam_req.edesc;
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	पूर्णांक ecode = 0;

	dev_dbg(ctx->dev, "%s %d: err 0x%x\n", __func__, __LINE__, status);

	अगर (unlikely(status))
		ecode = caam_qi2_strstatus(ctx->dev, status);

	ahash_unmap_ctx(ctx->dev, edesc, req, DMA_FROM_DEVICE);
	qi_cache_मुक्त(edesc);

	scatterwalk_map_and_copy(state->buf, req->src,
				 req->nbytes - state->next_buflen,
				 state->next_buflen, 0);
	state->buflen = state->next_buflen;

	prपूर्णांक_hex_dump_debug("buf@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, state->buf,
			     state->buflen, 1);

	prपूर्णांक_hex_dump_debug("ctx@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, state->caam_ctx,
			     ctx->ctx_len, 1);
	अगर (req->result)
		prपूर्णांक_hex_dump_debug("result@" __stringअगरy(__LINE__)": ",
				     DUMP_PREFIX_ADDRESS, 16, 4, req->result,
				     crypto_ahash_digestsize(ahash), 1);

	req->base.complete(&req->base, ecode);
पूर्ण

अटल पूर्णांक ahash_update_ctx(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा caam_request *req_ctx = &state->caam_req;
	काष्ठा dpaa2_fl_entry *in_fle = &req_ctx->fd_flt[1];
	काष्ठा dpaa2_fl_entry *out_fle = &req_ctx->fd_flt[0];
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		      GFP_KERNEL : GFP_ATOMIC;
	u8 *buf = state->buf;
	पूर्णांक *buflen = &state->buflen;
	पूर्णांक *next_buflen = &state->next_buflen;
	पूर्णांक in_len = *buflen + req->nbytes, to_hash;
	पूर्णांक src_nents, mapped_nents, qm_sg_bytes, qm_sg_src_index;
	काष्ठा ahash_edesc *edesc;
	पूर्णांक ret = 0;

	*next_buflen = in_len & (crypto_tfm_alg_blocksize(&ahash->base) - 1);
	to_hash = in_len - *next_buflen;

	अगर (to_hash) अणु
		काष्ठा dpaa2_sg_entry *sg_table;
		पूर्णांक src_len = req->nbytes - *next_buflen;

		src_nents = sg_nents_क्रम_len(req->src, src_len);
		अगर (src_nents < 0) अणु
			dev_err(ctx->dev, "Invalid number of src SG.\n");
			वापस src_nents;
		पूर्ण

		अगर (src_nents) अणु
			mapped_nents = dma_map_sg(ctx->dev, req->src, src_nents,
						  DMA_TO_DEVICE);
			अगर (!mapped_nents) अणु
				dev_err(ctx->dev, "unable to DMA map source\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			mapped_nents = 0;
		पूर्ण

		/* allocate space क्रम base edesc and link tables */
		edesc = qi_cache_zalloc(GFP_DMA | flags);
		अगर (!edesc) अणु
			dma_unmap_sg(ctx->dev, req->src, src_nents,
				     DMA_TO_DEVICE);
			वापस -ENOMEM;
		पूर्ण

		edesc->src_nents = src_nents;
		qm_sg_src_index = 1 + (*buflen ? 1 : 0);
		qm_sg_bytes = pad_sg_nents(qm_sg_src_index + mapped_nents) *
			      माप(*sg_table);
		sg_table = &edesc->sgt[0];

		ret = ctx_map_to_qm_sg(ctx->dev, state, ctx->ctx_len, sg_table,
				       DMA_BIसूचीECTIONAL);
		अगर (ret)
			जाओ unmap_ctx;

		ret = buf_map_to_qm_sg(ctx->dev, sg_table + 1, state);
		अगर (ret)
			जाओ unmap_ctx;

		अगर (mapped_nents) अणु
			sg_to_qm_sg_last(req->src, src_len,
					 sg_table + qm_sg_src_index, 0);
		पूर्ण अन्यथा अणु
			dpaa2_sg_set_final(sg_table + qm_sg_src_index - 1,
					   true);
		पूर्ण

		edesc->qm_sg_dma = dma_map_single(ctx->dev, sg_table,
						  qm_sg_bytes, DMA_TO_DEVICE);
		अगर (dma_mapping_error(ctx->dev, edesc->qm_sg_dma)) अणु
			dev_err(ctx->dev, "unable to map S/G table\n");
			ret = -ENOMEM;
			जाओ unmap_ctx;
		पूर्ण
		edesc->qm_sg_bytes = qm_sg_bytes;

		स_रखो(&req_ctx->fd_flt, 0, माप(req_ctx->fd_flt));
		dpaa2_fl_set_final(in_fle, true);
		dpaa2_fl_set_क्रमmat(in_fle, dpaa2_fl_sg);
		dpaa2_fl_set_addr(in_fle, edesc->qm_sg_dma);
		dpaa2_fl_set_len(in_fle, ctx->ctx_len + to_hash);
		dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_single);
		dpaa2_fl_set_addr(out_fle, state->ctx_dma);
		dpaa2_fl_set_len(out_fle, ctx->ctx_len);

		req_ctx->flc = &ctx->flc[UPDATE];
		req_ctx->flc_dma = ctx->flc_dma[UPDATE];
		req_ctx->cbk = ahash_करोne_bi;
		req_ctx->ctx = &req->base;
		req_ctx->edesc = edesc;

		ret = dpaa2_caam_enqueue(ctx->dev, req_ctx);
		अगर (ret != -EINPROGRESS &&
		    !(ret == -EBUSY &&
		      req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG))
			जाओ unmap_ctx;
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
	ahash_unmap_ctx(ctx->dev, edesc, req, DMA_BIसूचीECTIONAL);
	qi_cache_मुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक ahash_final_ctx(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा caam_request *req_ctx = &state->caam_req;
	काष्ठा dpaa2_fl_entry *in_fle = &req_ctx->fd_flt[1];
	काष्ठा dpaa2_fl_entry *out_fle = &req_ctx->fd_flt[0];
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		      GFP_KERNEL : GFP_ATOMIC;
	पूर्णांक buflen = state->buflen;
	पूर्णांक qm_sg_bytes;
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा ahash_edesc *edesc;
	काष्ठा dpaa2_sg_entry *sg_table;
	पूर्णांक ret;

	/* allocate space क्रम base edesc and link tables */
	edesc = qi_cache_zalloc(GFP_DMA | flags);
	अगर (!edesc)
		वापस -ENOMEM;

	qm_sg_bytes = pad_sg_nents(1 + (buflen ? 1 : 0)) * माप(*sg_table);
	sg_table = &edesc->sgt[0];

	ret = ctx_map_to_qm_sg(ctx->dev, state, ctx->ctx_len, sg_table,
			       DMA_BIसूचीECTIONAL);
	अगर (ret)
		जाओ unmap_ctx;

	ret = buf_map_to_qm_sg(ctx->dev, sg_table + 1, state);
	अगर (ret)
		जाओ unmap_ctx;

	dpaa2_sg_set_final(sg_table + (buflen ? 1 : 0), true);

	edesc->qm_sg_dma = dma_map_single(ctx->dev, sg_table, qm_sg_bytes,
					  DMA_TO_DEVICE);
	अगर (dma_mapping_error(ctx->dev, edesc->qm_sg_dma)) अणु
		dev_err(ctx->dev, "unable to map S/G table\n");
		ret = -ENOMEM;
		जाओ unmap_ctx;
	पूर्ण
	edesc->qm_sg_bytes = qm_sg_bytes;

	स_रखो(&req_ctx->fd_flt, 0, माप(req_ctx->fd_flt));
	dpaa2_fl_set_final(in_fle, true);
	dpaa2_fl_set_क्रमmat(in_fle, dpaa2_fl_sg);
	dpaa2_fl_set_addr(in_fle, edesc->qm_sg_dma);
	dpaa2_fl_set_len(in_fle, ctx->ctx_len + buflen);
	dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_single);
	dpaa2_fl_set_addr(out_fle, state->ctx_dma);
	dpaa2_fl_set_len(out_fle, digestsize);

	req_ctx->flc = &ctx->flc[FINALIZE];
	req_ctx->flc_dma = ctx->flc_dma[FINALIZE];
	req_ctx->cbk = ahash_करोne_ctx_src;
	req_ctx->ctx = &req->base;
	req_ctx->edesc = edesc;

	ret = dpaa2_caam_enqueue(ctx->dev, req_ctx);
	अगर (ret == -EINPROGRESS ||
	    (ret == -EBUSY && req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG))
		वापस ret;

unmap_ctx:
	ahash_unmap_ctx(ctx->dev, edesc, req, DMA_BIसूचीECTIONAL);
	qi_cache_मुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक ahash_finup_ctx(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा caam_request *req_ctx = &state->caam_req;
	काष्ठा dpaa2_fl_entry *in_fle = &req_ctx->fd_flt[1];
	काष्ठा dpaa2_fl_entry *out_fle = &req_ctx->fd_flt[0];
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		      GFP_KERNEL : GFP_ATOMIC;
	पूर्णांक buflen = state->buflen;
	पूर्णांक qm_sg_bytes, qm_sg_src_index;
	पूर्णांक src_nents, mapped_nents;
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा ahash_edesc *edesc;
	काष्ठा dpaa2_sg_entry *sg_table;
	पूर्णांक ret;

	src_nents = sg_nents_क्रम_len(req->src, req->nbytes);
	अगर (src_nents < 0) अणु
		dev_err(ctx->dev, "Invalid number of src SG.\n");
		वापस src_nents;
	पूर्ण

	अगर (src_nents) अणु
		mapped_nents = dma_map_sg(ctx->dev, req->src, src_nents,
					  DMA_TO_DEVICE);
		अगर (!mapped_nents) अणु
			dev_err(ctx->dev, "unable to DMA map source\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		mapped_nents = 0;
	पूर्ण

	/* allocate space क्रम base edesc and link tables */
	edesc = qi_cache_zalloc(GFP_DMA | flags);
	अगर (!edesc) अणु
		dma_unmap_sg(ctx->dev, req->src, src_nents, DMA_TO_DEVICE);
		वापस -ENOMEM;
	पूर्ण

	edesc->src_nents = src_nents;
	qm_sg_src_index = 1 + (buflen ? 1 : 0);
	qm_sg_bytes = pad_sg_nents(qm_sg_src_index + mapped_nents) *
		      माप(*sg_table);
	sg_table = &edesc->sgt[0];

	ret = ctx_map_to_qm_sg(ctx->dev, state, ctx->ctx_len, sg_table,
			       DMA_BIसूचीECTIONAL);
	अगर (ret)
		जाओ unmap_ctx;

	ret = buf_map_to_qm_sg(ctx->dev, sg_table + 1, state);
	अगर (ret)
		जाओ unmap_ctx;

	sg_to_qm_sg_last(req->src, req->nbytes, sg_table + qm_sg_src_index, 0);

	edesc->qm_sg_dma = dma_map_single(ctx->dev, sg_table, qm_sg_bytes,
					  DMA_TO_DEVICE);
	अगर (dma_mapping_error(ctx->dev, edesc->qm_sg_dma)) अणु
		dev_err(ctx->dev, "unable to map S/G table\n");
		ret = -ENOMEM;
		जाओ unmap_ctx;
	पूर्ण
	edesc->qm_sg_bytes = qm_sg_bytes;

	स_रखो(&req_ctx->fd_flt, 0, माप(req_ctx->fd_flt));
	dpaa2_fl_set_final(in_fle, true);
	dpaa2_fl_set_क्रमmat(in_fle, dpaa2_fl_sg);
	dpaa2_fl_set_addr(in_fle, edesc->qm_sg_dma);
	dpaa2_fl_set_len(in_fle, ctx->ctx_len + buflen + req->nbytes);
	dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_single);
	dpaa2_fl_set_addr(out_fle, state->ctx_dma);
	dpaa2_fl_set_len(out_fle, digestsize);

	req_ctx->flc = &ctx->flc[FINALIZE];
	req_ctx->flc_dma = ctx->flc_dma[FINALIZE];
	req_ctx->cbk = ahash_करोne_ctx_src;
	req_ctx->ctx = &req->base;
	req_ctx->edesc = edesc;

	ret = dpaa2_caam_enqueue(ctx->dev, req_ctx);
	अगर (ret == -EINPROGRESS ||
	    (ret == -EBUSY && req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG))
		वापस ret;

unmap_ctx:
	ahash_unmap_ctx(ctx->dev, edesc, req, DMA_BIसूचीECTIONAL);
	qi_cache_मुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक ahash_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा caam_request *req_ctx = &state->caam_req;
	काष्ठा dpaa2_fl_entry *in_fle = &req_ctx->fd_flt[1];
	काष्ठा dpaa2_fl_entry *out_fle = &req_ctx->fd_flt[0];
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		      GFP_KERNEL : GFP_ATOMIC;
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	पूर्णांक src_nents, mapped_nents;
	काष्ठा ahash_edesc *edesc;
	पूर्णांक ret = -ENOMEM;

	state->buf_dma = 0;

	src_nents = sg_nents_क्रम_len(req->src, req->nbytes);
	अगर (src_nents < 0) अणु
		dev_err(ctx->dev, "Invalid number of src SG.\n");
		वापस src_nents;
	पूर्ण

	अगर (src_nents) अणु
		mapped_nents = dma_map_sg(ctx->dev, req->src, src_nents,
					  DMA_TO_DEVICE);
		अगर (!mapped_nents) अणु
			dev_err(ctx->dev, "unable to map source for DMA\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		mapped_nents = 0;
	पूर्ण

	/* allocate space क्रम base edesc and link tables */
	edesc = qi_cache_zalloc(GFP_DMA | flags);
	अगर (!edesc) अणु
		dma_unmap_sg(ctx->dev, req->src, src_nents, DMA_TO_DEVICE);
		वापस ret;
	पूर्ण

	edesc->src_nents = src_nents;
	स_रखो(&req_ctx->fd_flt, 0, माप(req_ctx->fd_flt));

	अगर (mapped_nents > 1) अणु
		पूर्णांक qm_sg_bytes;
		काष्ठा dpaa2_sg_entry *sg_table = &edesc->sgt[0];

		qm_sg_bytes = pad_sg_nents(mapped_nents) * माप(*sg_table);
		sg_to_qm_sg_last(req->src, req->nbytes, sg_table, 0);
		edesc->qm_sg_dma = dma_map_single(ctx->dev, sg_table,
						  qm_sg_bytes, DMA_TO_DEVICE);
		अगर (dma_mapping_error(ctx->dev, edesc->qm_sg_dma)) अणु
			dev_err(ctx->dev, "unable to map S/G table\n");
			जाओ unmap;
		पूर्ण
		edesc->qm_sg_bytes = qm_sg_bytes;
		dpaa2_fl_set_क्रमmat(in_fle, dpaa2_fl_sg);
		dpaa2_fl_set_addr(in_fle, edesc->qm_sg_dma);
	पूर्ण अन्यथा अणु
		dpaa2_fl_set_क्रमmat(in_fle, dpaa2_fl_single);
		dpaa2_fl_set_addr(in_fle, sg_dma_address(req->src));
	पूर्ण

	state->ctx_dma_len = digestsize;
	state->ctx_dma = dma_map_single(ctx->dev, state->caam_ctx, digestsize,
					DMA_FROM_DEVICE);
	अगर (dma_mapping_error(ctx->dev, state->ctx_dma)) अणु
		dev_err(ctx->dev, "unable to map ctx\n");
		state->ctx_dma = 0;
		जाओ unmap;
	पूर्ण

	dpaa2_fl_set_final(in_fle, true);
	dpaa2_fl_set_len(in_fle, req->nbytes);
	dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_single);
	dpaa2_fl_set_addr(out_fle, state->ctx_dma);
	dpaa2_fl_set_len(out_fle, digestsize);

	req_ctx->flc = &ctx->flc[DIGEST];
	req_ctx->flc_dma = ctx->flc_dma[DIGEST];
	req_ctx->cbk = ahash_करोne;
	req_ctx->ctx = &req->base;
	req_ctx->edesc = edesc;
	ret = dpaa2_caam_enqueue(ctx->dev, req_ctx);
	अगर (ret == -EINPROGRESS ||
	    (ret == -EBUSY && req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG))
		वापस ret;

unmap:
	ahash_unmap_ctx(ctx->dev, edesc, req, DMA_FROM_DEVICE);
	qi_cache_मुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक ahash_final_no_ctx(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा caam_request *req_ctx = &state->caam_req;
	काष्ठा dpaa2_fl_entry *in_fle = &req_ctx->fd_flt[1];
	काष्ठा dpaa2_fl_entry *out_fle = &req_ctx->fd_flt[0];
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		      GFP_KERNEL : GFP_ATOMIC;
	u8 *buf = state->buf;
	पूर्णांक buflen = state->buflen;
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा ahash_edesc *edesc;
	पूर्णांक ret = -ENOMEM;

	/* allocate space क्रम base edesc and link tables */
	edesc = qi_cache_zalloc(GFP_DMA | flags);
	अगर (!edesc)
		वापस ret;

	अगर (buflen) अणु
		state->buf_dma = dma_map_single(ctx->dev, buf, buflen,
						DMA_TO_DEVICE);
		अगर (dma_mapping_error(ctx->dev, state->buf_dma)) अणु
			dev_err(ctx->dev, "unable to map src\n");
			जाओ unmap;
		पूर्ण
	पूर्ण

	state->ctx_dma_len = digestsize;
	state->ctx_dma = dma_map_single(ctx->dev, state->caam_ctx, digestsize,
					DMA_FROM_DEVICE);
	अगर (dma_mapping_error(ctx->dev, state->ctx_dma)) अणु
		dev_err(ctx->dev, "unable to map ctx\n");
		state->ctx_dma = 0;
		जाओ unmap;
	पूर्ण

	स_रखो(&req_ctx->fd_flt, 0, माप(req_ctx->fd_flt));
	dpaa2_fl_set_final(in_fle, true);
	/*
	 * crypto engine requires the input entry to be present when
	 * "frame list" FD is used.
	 * Since engine करोes not support FMT=2'b11 (unused entry type), leaving
	 * in_fle zeroized (except क्रम "Final" flag) is the best option.
	 */
	अगर (buflen) अणु
		dpaa2_fl_set_क्रमmat(in_fle, dpaa2_fl_single);
		dpaa2_fl_set_addr(in_fle, state->buf_dma);
		dpaa2_fl_set_len(in_fle, buflen);
	पूर्ण
	dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_single);
	dpaa2_fl_set_addr(out_fle, state->ctx_dma);
	dpaa2_fl_set_len(out_fle, digestsize);

	req_ctx->flc = &ctx->flc[DIGEST];
	req_ctx->flc_dma = ctx->flc_dma[DIGEST];
	req_ctx->cbk = ahash_करोne;
	req_ctx->ctx = &req->base;
	req_ctx->edesc = edesc;

	ret = dpaa2_caam_enqueue(ctx->dev, req_ctx);
	अगर (ret == -EINPROGRESS ||
	    (ret == -EBUSY && req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG))
		वापस ret;

unmap:
	ahash_unmap_ctx(ctx->dev, edesc, req, DMA_FROM_DEVICE);
	qi_cache_मुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक ahash_update_no_ctx(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा caam_request *req_ctx = &state->caam_req;
	काष्ठा dpaa2_fl_entry *in_fle = &req_ctx->fd_flt[1];
	काष्ठा dpaa2_fl_entry *out_fle = &req_ctx->fd_flt[0];
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		      GFP_KERNEL : GFP_ATOMIC;
	u8 *buf = state->buf;
	पूर्णांक *buflen = &state->buflen;
	पूर्णांक *next_buflen = &state->next_buflen;
	पूर्णांक in_len = *buflen + req->nbytes, to_hash;
	पूर्णांक qm_sg_bytes, src_nents, mapped_nents;
	काष्ठा ahash_edesc *edesc;
	पूर्णांक ret = 0;

	*next_buflen = in_len & (crypto_tfm_alg_blocksize(&ahash->base) - 1);
	to_hash = in_len - *next_buflen;

	अगर (to_hash) अणु
		काष्ठा dpaa2_sg_entry *sg_table;
		पूर्णांक src_len = req->nbytes - *next_buflen;

		src_nents = sg_nents_क्रम_len(req->src, src_len);
		अगर (src_nents < 0) अणु
			dev_err(ctx->dev, "Invalid number of src SG.\n");
			वापस src_nents;
		पूर्ण

		अगर (src_nents) अणु
			mapped_nents = dma_map_sg(ctx->dev, req->src, src_nents,
						  DMA_TO_DEVICE);
			अगर (!mapped_nents) अणु
				dev_err(ctx->dev, "unable to DMA map source\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			mapped_nents = 0;
		पूर्ण

		/* allocate space क्रम base edesc and link tables */
		edesc = qi_cache_zalloc(GFP_DMA | flags);
		अगर (!edesc) अणु
			dma_unmap_sg(ctx->dev, req->src, src_nents,
				     DMA_TO_DEVICE);
			वापस -ENOMEM;
		पूर्ण

		edesc->src_nents = src_nents;
		qm_sg_bytes = pad_sg_nents(1 + mapped_nents) *
			      माप(*sg_table);
		sg_table = &edesc->sgt[0];

		ret = buf_map_to_qm_sg(ctx->dev, sg_table, state);
		अगर (ret)
			जाओ unmap_ctx;

		sg_to_qm_sg_last(req->src, src_len, sg_table + 1, 0);

		edesc->qm_sg_dma = dma_map_single(ctx->dev, sg_table,
						  qm_sg_bytes, DMA_TO_DEVICE);
		अगर (dma_mapping_error(ctx->dev, edesc->qm_sg_dma)) अणु
			dev_err(ctx->dev, "unable to map S/G table\n");
			ret = -ENOMEM;
			जाओ unmap_ctx;
		पूर्ण
		edesc->qm_sg_bytes = qm_sg_bytes;

		state->ctx_dma_len = ctx->ctx_len;
		state->ctx_dma = dma_map_single(ctx->dev, state->caam_ctx,
						ctx->ctx_len, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(ctx->dev, state->ctx_dma)) अणु
			dev_err(ctx->dev, "unable to map ctx\n");
			state->ctx_dma = 0;
			ret = -ENOMEM;
			जाओ unmap_ctx;
		पूर्ण

		स_रखो(&req_ctx->fd_flt, 0, माप(req_ctx->fd_flt));
		dpaa2_fl_set_final(in_fle, true);
		dpaa2_fl_set_क्रमmat(in_fle, dpaa2_fl_sg);
		dpaa2_fl_set_addr(in_fle, edesc->qm_sg_dma);
		dpaa2_fl_set_len(in_fle, to_hash);
		dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_single);
		dpaa2_fl_set_addr(out_fle, state->ctx_dma);
		dpaa2_fl_set_len(out_fle, ctx->ctx_len);

		req_ctx->flc = &ctx->flc[UPDATE_FIRST];
		req_ctx->flc_dma = ctx->flc_dma[UPDATE_FIRST];
		req_ctx->cbk = ahash_करोne_ctx_dst;
		req_ctx->ctx = &req->base;
		req_ctx->edesc = edesc;

		ret = dpaa2_caam_enqueue(ctx->dev, req_ctx);
		अगर (ret != -EINPROGRESS &&
		    !(ret == -EBUSY &&
		      req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG))
			जाओ unmap_ctx;

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
	ahash_unmap_ctx(ctx->dev, edesc, req, DMA_TO_DEVICE);
	qi_cache_मुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक ahash_finup_no_ctx(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा caam_request *req_ctx = &state->caam_req;
	काष्ठा dpaa2_fl_entry *in_fle = &req_ctx->fd_flt[1];
	काष्ठा dpaa2_fl_entry *out_fle = &req_ctx->fd_flt[0];
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		      GFP_KERNEL : GFP_ATOMIC;
	पूर्णांक buflen = state->buflen;
	पूर्णांक qm_sg_bytes, src_nents, mapped_nents;
	पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	काष्ठा ahash_edesc *edesc;
	काष्ठा dpaa2_sg_entry *sg_table;
	पूर्णांक ret = -ENOMEM;

	src_nents = sg_nents_क्रम_len(req->src, req->nbytes);
	अगर (src_nents < 0) अणु
		dev_err(ctx->dev, "Invalid number of src SG.\n");
		वापस src_nents;
	पूर्ण

	अगर (src_nents) अणु
		mapped_nents = dma_map_sg(ctx->dev, req->src, src_nents,
					  DMA_TO_DEVICE);
		अगर (!mapped_nents) अणु
			dev_err(ctx->dev, "unable to DMA map source\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		mapped_nents = 0;
	पूर्ण

	/* allocate space क्रम base edesc and link tables */
	edesc = qi_cache_zalloc(GFP_DMA | flags);
	अगर (!edesc) अणु
		dma_unmap_sg(ctx->dev, req->src, src_nents, DMA_TO_DEVICE);
		वापस ret;
	पूर्ण

	edesc->src_nents = src_nents;
	qm_sg_bytes = pad_sg_nents(2 + mapped_nents) * माप(*sg_table);
	sg_table = &edesc->sgt[0];

	ret = buf_map_to_qm_sg(ctx->dev, sg_table, state);
	अगर (ret)
		जाओ unmap;

	sg_to_qm_sg_last(req->src, req->nbytes, sg_table + 1, 0);

	edesc->qm_sg_dma = dma_map_single(ctx->dev, sg_table, qm_sg_bytes,
					  DMA_TO_DEVICE);
	अगर (dma_mapping_error(ctx->dev, edesc->qm_sg_dma)) अणु
		dev_err(ctx->dev, "unable to map S/G table\n");
		ret = -ENOMEM;
		जाओ unmap;
	पूर्ण
	edesc->qm_sg_bytes = qm_sg_bytes;

	state->ctx_dma_len = digestsize;
	state->ctx_dma = dma_map_single(ctx->dev, state->caam_ctx, digestsize,
					DMA_FROM_DEVICE);
	अगर (dma_mapping_error(ctx->dev, state->ctx_dma)) अणु
		dev_err(ctx->dev, "unable to map ctx\n");
		state->ctx_dma = 0;
		ret = -ENOMEM;
		जाओ unmap;
	पूर्ण

	स_रखो(&req_ctx->fd_flt, 0, माप(req_ctx->fd_flt));
	dpaa2_fl_set_final(in_fle, true);
	dpaa2_fl_set_क्रमmat(in_fle, dpaa2_fl_sg);
	dpaa2_fl_set_addr(in_fle, edesc->qm_sg_dma);
	dpaa2_fl_set_len(in_fle, buflen + req->nbytes);
	dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_single);
	dpaa2_fl_set_addr(out_fle, state->ctx_dma);
	dpaa2_fl_set_len(out_fle, digestsize);

	req_ctx->flc = &ctx->flc[DIGEST];
	req_ctx->flc_dma = ctx->flc_dma[DIGEST];
	req_ctx->cbk = ahash_करोne;
	req_ctx->ctx = &req->base;
	req_ctx->edesc = edesc;
	ret = dpaa2_caam_enqueue(ctx->dev, req_ctx);
	अगर (ret != -EINPROGRESS &&
	    !(ret == -EBUSY && req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG))
		जाओ unmap;

	वापस ret;
unmap:
	ahash_unmap_ctx(ctx->dev, edesc, req, DMA_FROM_DEVICE);
	qi_cache_मुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक ahash_update_first(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा caam_hash_state *state = ahash_request_ctx(req);
	काष्ठा caam_request *req_ctx = &state->caam_req;
	काष्ठा dpaa2_fl_entry *in_fle = &req_ctx->fd_flt[1];
	काष्ठा dpaa2_fl_entry *out_fle = &req_ctx->fd_flt[0];
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		      GFP_KERNEL : GFP_ATOMIC;
	u8 *buf = state->buf;
	पूर्णांक *buflen = &state->buflen;
	पूर्णांक *next_buflen = &state->next_buflen;
	पूर्णांक to_hash;
	पूर्णांक src_nents, mapped_nents;
	काष्ठा ahash_edesc *edesc;
	पूर्णांक ret = 0;

	*next_buflen = req->nbytes & (crypto_tfm_alg_blocksize(&ahash->base) -
				      1);
	to_hash = req->nbytes - *next_buflen;

	अगर (to_hash) अणु
		काष्ठा dpaa2_sg_entry *sg_table;
		पूर्णांक src_len = req->nbytes - *next_buflen;

		src_nents = sg_nents_क्रम_len(req->src, src_len);
		अगर (src_nents < 0) अणु
			dev_err(ctx->dev, "Invalid number of src SG.\n");
			वापस src_nents;
		पूर्ण

		अगर (src_nents) अणु
			mapped_nents = dma_map_sg(ctx->dev, req->src, src_nents,
						  DMA_TO_DEVICE);
			अगर (!mapped_nents) अणु
				dev_err(ctx->dev, "unable to map source for DMA\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			mapped_nents = 0;
		पूर्ण

		/* allocate space क्रम base edesc and link tables */
		edesc = qi_cache_zalloc(GFP_DMA | flags);
		अगर (!edesc) अणु
			dma_unmap_sg(ctx->dev, req->src, src_nents,
				     DMA_TO_DEVICE);
			वापस -ENOMEM;
		पूर्ण

		edesc->src_nents = src_nents;
		sg_table = &edesc->sgt[0];

		स_रखो(&req_ctx->fd_flt, 0, माप(req_ctx->fd_flt));
		dpaa2_fl_set_final(in_fle, true);
		dpaa2_fl_set_len(in_fle, to_hash);

		अगर (mapped_nents > 1) अणु
			पूर्णांक qm_sg_bytes;

			sg_to_qm_sg_last(req->src, src_len, sg_table, 0);
			qm_sg_bytes = pad_sg_nents(mapped_nents) *
				      माप(*sg_table);
			edesc->qm_sg_dma = dma_map_single(ctx->dev, sg_table,
							  qm_sg_bytes,
							  DMA_TO_DEVICE);
			अगर (dma_mapping_error(ctx->dev, edesc->qm_sg_dma)) अणु
				dev_err(ctx->dev, "unable to map S/G table\n");
				ret = -ENOMEM;
				जाओ unmap_ctx;
			पूर्ण
			edesc->qm_sg_bytes = qm_sg_bytes;
			dpaa2_fl_set_क्रमmat(in_fle, dpaa2_fl_sg);
			dpaa2_fl_set_addr(in_fle, edesc->qm_sg_dma);
		पूर्ण अन्यथा अणु
			dpaa2_fl_set_क्रमmat(in_fle, dpaa2_fl_single);
			dpaa2_fl_set_addr(in_fle, sg_dma_address(req->src));
		पूर्ण

		state->ctx_dma_len = ctx->ctx_len;
		state->ctx_dma = dma_map_single(ctx->dev, state->caam_ctx,
						ctx->ctx_len, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(ctx->dev, state->ctx_dma)) अणु
			dev_err(ctx->dev, "unable to map ctx\n");
			state->ctx_dma = 0;
			ret = -ENOMEM;
			जाओ unmap_ctx;
		पूर्ण

		dpaa2_fl_set_क्रमmat(out_fle, dpaa2_fl_single);
		dpaa2_fl_set_addr(out_fle, state->ctx_dma);
		dpaa2_fl_set_len(out_fle, ctx->ctx_len);

		req_ctx->flc = &ctx->flc[UPDATE_FIRST];
		req_ctx->flc_dma = ctx->flc_dma[UPDATE_FIRST];
		req_ctx->cbk = ahash_करोne_ctx_dst;
		req_ctx->ctx = &req->base;
		req_ctx->edesc = edesc;

		ret = dpaa2_caam_enqueue(ctx->dev, req_ctx);
		अगर (ret != -EINPROGRESS &&
		    !(ret == -EBUSY && req->base.flags &
		      CRYPTO_TFM_REQ_MAY_BACKLOG))
			जाओ unmap_ctx;

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
	ahash_unmap_ctx(ctx->dev, edesc, req, DMA_TO_DEVICE);
	qi_cache_मुक्त(edesc);
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
		.driver_name = "sha1-caam-qi2",
		.hmac_name = "hmac(sha1)",
		.hmac_driver_name = "hmac-sha1-caam-qi2",
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
		.driver_name = "sha224-caam-qi2",
		.hmac_name = "hmac(sha224)",
		.hmac_driver_name = "hmac-sha224-caam-qi2",
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
		.driver_name = "sha256-caam-qi2",
		.hmac_name = "hmac(sha256)",
		.hmac_driver_name = "hmac-sha256-caam-qi2",
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
		.driver_name = "sha384-caam-qi2",
		.hmac_name = "hmac(sha384)",
		.hmac_driver_name = "hmac-sha384-caam-qi2",
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
		.driver_name = "sha512-caam-qi2",
		.hmac_name = "hmac(sha512)",
		.hmac_driver_name = "hmac-sha512-caam-qi2",
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
		.driver_name = "md5-caam-qi2",
		.hmac_name = "hmac(md5)",
		.hmac_driver_name = "hmac-md5-caam-qi2",
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
	पूर्ण
पूर्ण;

काष्ठा caam_hash_alg अणु
	काष्ठा list_head entry;
	काष्ठा device *dev;
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
	dma_addr_t dma_addr;
	पूर्णांक i;

	ctx->dev = caam_hash->dev;

	अगर (alg->setkey) अणु
		ctx->adata.key_dma = dma_map_single_attrs(ctx->dev, ctx->key,
							  ARRAY_SIZE(ctx->key),
							  DMA_TO_DEVICE,
							  DMA_ATTR_SKIP_CPU_SYNC);
		अगर (dma_mapping_error(ctx->dev, ctx->adata.key_dma)) अणु
			dev_err(ctx->dev, "unable to map key\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	dma_addr = dma_map_single_attrs(ctx->dev, ctx->flc, माप(ctx->flc),
					DMA_BIसूचीECTIONAL,
					DMA_ATTR_SKIP_CPU_SYNC);
	अगर (dma_mapping_error(ctx->dev, dma_addr)) अणु
		dev_err(ctx->dev, "unable to map shared descriptors\n");
		अगर (ctx->adata.key_dma)
			dma_unmap_single_attrs(ctx->dev, ctx->adata.key_dma,
					       ARRAY_SIZE(ctx->key),
					       DMA_TO_DEVICE,
					       DMA_ATTR_SKIP_CPU_SYNC);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < HASH_NUM_OP; i++)
		ctx->flc_dma[i] = dma_addr + i * माप(ctx->flc[i]);

	/* copy descriptor header ढाँचा value */
	ctx->adata.algtype = OP_TYPE_CLASS2_ALG | caam_hash->alg_type;

	ctx->ctx_len = runninglen[(ctx->adata.algtype &
				   OP_ALG_ALGSEL_SUBMASK) >>
				  OP_ALG_ALGSEL_SHIFT];

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

	dma_unmap_single_attrs(ctx->dev, ctx->flc_dma[0], माप(ctx->flc),
			       DMA_BIसूचीECTIONAL, DMA_ATTR_SKIP_CPU_SYNC);
	अगर (ctx->adata.key_dma)
		dma_unmap_single_attrs(ctx->dev, ctx->adata.key_dma,
				       ARRAY_SIZE(ctx->key), DMA_TO_DEVICE,
				       DMA_ATTR_SKIP_CPU_SYNC);
पूर्ण

अटल काष्ठा caam_hash_alg *caam_hash_alloc(काष्ठा device *dev,
	काष्ठा caam_hash_ढाँचा *ढाँचा, bool keyed)
अणु
	काष्ठा caam_hash_alg *t_alg;
	काष्ठा ahash_alg *halg;
	काष्ठा crypto_alg *alg;

	t_alg = kzalloc(माप(*t_alg), GFP_KERNEL);
	अगर (!t_alg)
		वापस ERR_PTR(-ENOMEM);

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
	t_alg->dev = dev;

	वापस t_alg;
पूर्ण

अटल व्योम dpaa2_caam_fqdan_cb(काष्ठा dpaa2_io_notअगरication_ctx *nctx)
अणु
	काष्ठा dpaa2_caam_priv_per_cpu *ppriv;

	ppriv = container_of(nctx, काष्ठा dpaa2_caam_priv_per_cpu, nctx);
	napi_schedule_irqoff(&ppriv->napi);
पूर्ण

अटल पूर्णांक __cold dpaa2_dpseci_dpio_setup(काष्ठा dpaa2_caam_priv *priv)
अणु
	काष्ठा device *dev = priv->dev;
	काष्ठा dpaa2_io_notअगरication_ctx *nctx;
	काष्ठा dpaa2_caam_priv_per_cpu *ppriv;
	पूर्णांक err, i = 0, cpu;

	क्रम_each_online_cpu(cpu) अणु
		ppriv = per_cpu_ptr(priv->ppriv, cpu);
		ppriv->priv = priv;
		nctx = &ppriv->nctx;
		nctx->is_cdan = 0;
		nctx->id = ppriv->rsp_fqid;
		nctx->desired_cpu = cpu;
		nctx->cb = dpaa2_caam_fqdan_cb;

		/* Register notअगरication callbacks */
		ppriv->dpio = dpaa2_io_service_select(cpu);
		err = dpaa2_io_service_रेजिस्टर(ppriv->dpio, nctx, dev);
		अगर (unlikely(err)) अणु
			dev_dbg(dev, "No affine DPIO for cpu %d\n", cpu);
			nctx->cb = शून्य;
			/*
			 * If no affine DPIO क्रम this core, there's probably
			 * none available क्रम next cores either. Signal we want
			 * to retry later, in हाल the DPIO devices weren't
			 * probed yet.
			 */
			err = -EPROBE_DEFER;
			जाओ err;
		पूर्ण

		ppriv->store = dpaa2_io_store_create(DPAA2_CAAM_STORE_SIZE,
						     dev);
		अगर (unlikely(!ppriv->store)) अणु
			dev_err(dev, "dpaa2_io_store_create() failed\n");
			err = -ENOMEM;
			जाओ err;
		पूर्ण

		अगर (++i == priv->num_pairs)
			अवरोध;
	पूर्ण

	वापस 0;

err:
	क्रम_each_online_cpu(cpu) अणु
		ppriv = per_cpu_ptr(priv->ppriv, cpu);
		अगर (!ppriv->nctx.cb)
			अवरोध;
		dpaa2_io_service_deरेजिस्टर(ppriv->dpio, &ppriv->nctx, dev);
	पूर्ण

	क्रम_each_online_cpu(cpu) अणु
		ppriv = per_cpu_ptr(priv->ppriv, cpu);
		अगर (!ppriv->store)
			अवरोध;
		dpaa2_io_store_destroy(ppriv->store);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम __cold dpaa2_dpseci_dpio_मुक्त(काष्ठा dpaa2_caam_priv *priv)
अणु
	काष्ठा dpaa2_caam_priv_per_cpu *ppriv;
	पूर्णांक i = 0, cpu;

	क्रम_each_online_cpu(cpu) अणु
		ppriv = per_cpu_ptr(priv->ppriv, cpu);
		dpaa2_io_service_deरेजिस्टर(ppriv->dpio, &ppriv->nctx,
					    priv->dev);
		dpaa2_io_store_destroy(ppriv->store);

		अगर (++i == priv->num_pairs)
			वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa2_dpseci_bind(काष्ठा dpaa2_caam_priv *priv)
अणु
	काष्ठा dpseci_rx_queue_cfg rx_queue_cfg;
	काष्ठा device *dev = priv->dev;
	काष्ठा fsl_mc_device *ls_dev = to_fsl_mc_device(dev);
	काष्ठा dpaa2_caam_priv_per_cpu *ppriv;
	पूर्णांक err = 0, i = 0, cpu;

	/* Configure Rx queues */
	क्रम_each_online_cpu(cpu) अणु
		ppriv = per_cpu_ptr(priv->ppriv, cpu);

		rx_queue_cfg.options = DPSECI_QUEUE_OPT_DEST |
				       DPSECI_QUEUE_OPT_USER_CTX;
		rx_queue_cfg.order_preservation_en = 0;
		rx_queue_cfg.dest_cfg.dest_type = DPSECI_DEST_DPIO;
		rx_queue_cfg.dest_cfg.dest_id = ppriv->nctx.dpio_id;
		/*
		 * Rx priority (WQ) करोesn't really matter, since we use
		 * pull mode, i.e. अस्थिर dequeues from specअगरic FQs
		 */
		rx_queue_cfg.dest_cfg.priority = 0;
		rx_queue_cfg.user_ctx = ppriv->nctx.qman64;

		err = dpseci_set_rx_queue(priv->mc_io, 0, ls_dev->mc_handle, i,
					  &rx_queue_cfg);
		अगर (err) अणु
			dev_err(dev, "dpseci_set_rx_queue() failed with err %d\n",
				err);
			वापस err;
		पूर्ण

		अगर (++i == priv->num_pairs)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम dpaa2_dpseci_congestion_मुक्त(काष्ठा dpaa2_caam_priv *priv)
अणु
	काष्ठा device *dev = priv->dev;

	अगर (!priv->cscn_mem)
		वापस;

	dma_unmap_single(dev, priv->cscn_dma, DPAA2_CSCN_SIZE, DMA_FROM_DEVICE);
	kमुक्त(priv->cscn_mem);
पूर्ण

अटल व्योम dpaa2_dpseci_मुक्त(काष्ठा dpaa2_caam_priv *priv)
अणु
	काष्ठा device *dev = priv->dev;
	काष्ठा fsl_mc_device *ls_dev = to_fsl_mc_device(dev);
	पूर्णांक err;

	अगर (DPSECI_VER(priv->major_ver, priv->minor_ver) > DPSECI_VER(5, 3)) अणु
		err = dpseci_reset(priv->mc_io, 0, ls_dev->mc_handle);
		अगर (err)
			dev_err(dev, "dpseci_reset() failed\n");
	पूर्ण

	dpaa2_dpseci_congestion_मुक्त(priv);
	dpseci_बंद(priv->mc_io, 0, ls_dev->mc_handle);
पूर्ण

अटल व्योम dpaa2_caam_process_fd(काष्ठा dpaa2_caam_priv *priv,
				  स्थिर काष्ठा dpaa2_fd *fd)
अणु
	काष्ठा caam_request *req;
	u32 fd_err;

	अगर (dpaa2_fd_get_क्रमmat(fd) != dpaa2_fd_list) अणु
		dev_err(priv->dev, "Only Frame List FD format is supported!\n");
		वापस;
	पूर्ण

	fd_err = dpaa2_fd_get_ctrl(fd) & FD_CTRL_ERR_MASK;
	अगर (unlikely(fd_err))
		dev_err_ratelimited(priv->dev, "FD error: %08x\n", fd_err);

	/*
	 * FD[ADDR] is guaranteed to be valid, irrespective of errors reported
	 * in FD[ERR] or FD[FRC].
	 */
	req = dpaa2_caam_iova_to_virt(priv, dpaa2_fd_get_addr(fd));
	dma_unmap_single(priv->dev, req->fd_flt_dma, माप(req->fd_flt),
			 DMA_BIसूचीECTIONAL);
	req->cbk(req->ctx, dpaa2_fd_get_frc(fd));
पूर्ण

अटल पूर्णांक dpaa2_caam_pull_fq(काष्ठा dpaa2_caam_priv_per_cpu *ppriv)
अणु
	पूर्णांक err;

	/* Retry जबतक portal is busy */
	करो अणु
		err = dpaa2_io_service_pull_fq(ppriv->dpio, ppriv->rsp_fqid,
					       ppriv->store);
	पूर्ण जबतक (err == -EBUSY);

	अगर (unlikely(err))
		dev_err(ppriv->priv->dev, "dpaa2_io_service_pull err %d", err);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_caam_store_consume(काष्ठा dpaa2_caam_priv_per_cpu *ppriv)
अणु
	काष्ठा dpaa2_dq *dq;
	पूर्णांक cleaned = 0, is_last;

	करो अणु
		dq = dpaa2_io_store_next(ppriv->store, &is_last);
		अगर (unlikely(!dq)) अणु
			अगर (unlikely(!is_last)) अणु
				dev_dbg(ppriv->priv->dev,
					"FQ %d returned no valid frames\n",
					ppriv->rsp_fqid);
				/*
				 * MUST retry until we get some sort of
				 * valid response token (be it "empty dequeue"
				 * or a valid frame).
				 */
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		/* Process FD */
		dpaa2_caam_process_fd(ppriv->priv, dpaa2_dq_fd(dq));
		cleaned++;
	पूर्ण जबतक (!is_last);

	वापस cleaned;
पूर्ण

अटल पूर्णांक dpaa2_dpseci_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा dpaa2_caam_priv_per_cpu *ppriv;
	काष्ठा dpaa2_caam_priv *priv;
	पूर्णांक err, cleaned = 0, store_cleaned;

	ppriv = container_of(napi, काष्ठा dpaa2_caam_priv_per_cpu, napi);
	priv = ppriv->priv;

	अगर (unlikely(dpaa2_caam_pull_fq(ppriv)))
		वापस 0;

	करो अणु
		store_cleaned = dpaa2_caam_store_consume(ppriv);
		cleaned += store_cleaned;

		अगर (store_cleaned == 0 ||
		    cleaned > budget - DPAA2_CAAM_STORE_SIZE)
			अवरोध;

		/* Try to dequeue some more */
		err = dpaa2_caam_pull_fq(ppriv);
		अगर (unlikely(err))
			अवरोध;
	पूर्ण जबतक (1);

	अगर (cleaned < budget) अणु
		napi_complete_करोne(napi, cleaned);
		err = dpaa2_io_service_rearm(ppriv->dpio, &ppriv->nctx);
		अगर (unlikely(err))
			dev_err(priv->dev, "Notification rearm failed: %d\n",
				err);
	पूर्ण

	वापस cleaned;
पूर्ण

अटल पूर्णांक dpaa2_dpseci_congestion_setup(काष्ठा dpaa2_caam_priv *priv,
					 u16 token)
अणु
	काष्ठा dpseci_congestion_notअगरication_cfg cong_notअगर_cfg = अणु 0 पूर्ण;
	काष्ठा device *dev = priv->dev;
	पूर्णांक err;

	/*
	 * Congestion group feature supported starting with DPSECI API v5.1
	 * and only when object has been created with this capability.
	 */
	अगर ((DPSECI_VER(priv->major_ver, priv->minor_ver) < DPSECI_VER(5, 1)) ||
	    !(priv->dpseci_attr.options & DPSECI_OPT_HAS_CG))
		वापस 0;

	priv->cscn_mem = kzalloc(DPAA2_CSCN_SIZE + DPAA2_CSCN_ALIGN,
				 GFP_KERNEL | GFP_DMA);
	अगर (!priv->cscn_mem)
		वापस -ENOMEM;

	priv->cscn_mem_aligned = PTR_ALIGN(priv->cscn_mem, DPAA2_CSCN_ALIGN);
	priv->cscn_dma = dma_map_single(dev, priv->cscn_mem_aligned,
					DPAA2_CSCN_SIZE, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, priv->cscn_dma)) अणु
		dev_err(dev, "Error mapping CSCN memory area\n");
		err = -ENOMEM;
		जाओ err_dma_map;
	पूर्ण

	cong_notअगर_cfg.units = DPSECI_CONGESTION_UNIT_BYTES;
	cong_notअगर_cfg.threshold_entry = DPAA2_SEC_CONG_ENTRY_THRESH;
	cong_notअगर_cfg.threshold_निकास = DPAA2_SEC_CONG_EXIT_THRESH;
	cong_notअगर_cfg.message_ctx = (uपूर्णांकptr_t)priv;
	cong_notअगर_cfg.message_iova = priv->cscn_dma;
	cong_notअगर_cfg.notअगरication_mode = DPSECI_CGN_MODE_WRITE_MEM_ON_ENTER |
					DPSECI_CGN_MODE_WRITE_MEM_ON_EXIT |
					DPSECI_CGN_MODE_COHERENT_WRITE;

	err = dpseci_set_congestion_notअगरication(priv->mc_io, 0, token,
						 &cong_notअगर_cfg);
	अगर (err) अणु
		dev_err(dev, "dpseci_set_congestion_notification failed\n");
		जाओ err_set_cong;
	पूर्ण

	वापस 0;

err_set_cong:
	dma_unmap_single(dev, priv->cscn_dma, DPAA2_CSCN_SIZE, DMA_FROM_DEVICE);
err_dma_map:
	kमुक्त(priv->cscn_mem);

	वापस err;
पूर्ण

अटल पूर्णांक __cold dpaa2_dpseci_setup(काष्ठा fsl_mc_device *ls_dev)
अणु
	काष्ठा device *dev = &ls_dev->dev;
	काष्ठा dpaa2_caam_priv *priv;
	काष्ठा dpaa2_caam_priv_per_cpu *ppriv;
	पूर्णांक err, cpu;
	u8 i;

	priv = dev_get_drvdata(dev);

	priv->dev = dev;
	priv->dpsec_id = ls_dev->obj_desc.id;

	/* Get a handle क्रम the DPSECI this पूर्णांकerface is associate with */
	err = dpseci_खोलो(priv->mc_io, 0, priv->dpsec_id, &ls_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpseci_open() failed: %d\n", err);
		जाओ err_खोलो;
	पूर्ण

	err = dpseci_get_api_version(priv->mc_io, 0, &priv->major_ver,
				     &priv->minor_ver);
	अगर (err) अणु
		dev_err(dev, "dpseci_get_api_version() failed\n");
		जाओ err_get_vers;
	पूर्ण

	dev_info(dev, "dpseci v%d.%d\n", priv->major_ver, priv->minor_ver);

	अगर (DPSECI_VER(priv->major_ver, priv->minor_ver) > DPSECI_VER(5, 3)) अणु
		err = dpseci_reset(priv->mc_io, 0, ls_dev->mc_handle);
		अगर (err) अणु
			dev_err(dev, "dpseci_reset() failed\n");
			जाओ err_get_vers;
		पूर्ण
	पूर्ण

	err = dpseci_get_attributes(priv->mc_io, 0, ls_dev->mc_handle,
				    &priv->dpseci_attr);
	अगर (err) अणु
		dev_err(dev, "dpseci_get_attributes() failed\n");
		जाओ err_get_vers;
	पूर्ण

	err = dpseci_get_sec_attr(priv->mc_io, 0, ls_dev->mc_handle,
				  &priv->sec_attr);
	अगर (err) अणु
		dev_err(dev, "dpseci_get_sec_attr() failed\n");
		जाओ err_get_vers;
	पूर्ण

	err = dpaa2_dpseci_congestion_setup(priv, ls_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "setup_congestion() failed\n");
		जाओ err_get_vers;
	पूर्ण

	priv->num_pairs = min(priv->dpseci_attr.num_rx_queues,
			      priv->dpseci_attr.num_tx_queues);
	अगर (priv->num_pairs > num_online_cpus()) अणु
		dev_warn(dev, "%d queues won't be used\n",
			 priv->num_pairs - num_online_cpus());
		priv->num_pairs = num_online_cpus();
	पूर्ण

	क्रम (i = 0; i < priv->dpseci_attr.num_rx_queues; i++) अणु
		err = dpseci_get_rx_queue(priv->mc_io, 0, ls_dev->mc_handle, i,
					  &priv->rx_queue_attr[i]);
		अगर (err) अणु
			dev_err(dev, "dpseci_get_rx_queue() failed\n");
			जाओ err_get_rx_queue;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < priv->dpseci_attr.num_tx_queues; i++) अणु
		err = dpseci_get_tx_queue(priv->mc_io, 0, ls_dev->mc_handle, i,
					  &priv->tx_queue_attr[i]);
		अगर (err) अणु
			dev_err(dev, "dpseci_get_tx_queue() failed\n");
			जाओ err_get_rx_queue;
		पूर्ण
	पूर्ण

	i = 0;
	क्रम_each_online_cpu(cpu) अणु
		u8 j;

		j = i % priv->num_pairs;

		ppriv = per_cpu_ptr(priv->ppriv, cpu);
		ppriv->req_fqid = priv->tx_queue_attr[j].fqid;

		/*
		 * Allow all cores to enqueue, जबतक only some of them
		 * will take part in dequeuing.
		 */
		अगर (++i > priv->num_pairs)
			जारी;

		ppriv->rsp_fqid = priv->rx_queue_attr[j].fqid;
		ppriv->prio = j;

		dev_dbg(dev, "pair %d: rx queue %d, tx queue %d\n", j,
			priv->rx_queue_attr[j].fqid,
			priv->tx_queue_attr[j].fqid);

		ppriv->net_dev.dev = *dev;
		INIT_LIST_HEAD(&ppriv->net_dev.napi_list);
		netअगर_napi_add(&ppriv->net_dev, &ppriv->napi, dpaa2_dpseci_poll,
			       DPAA2_CAAM_NAPI_WEIGHT);
	पूर्ण

	वापस 0;

err_get_rx_queue:
	dpaa2_dpseci_congestion_मुक्त(priv);
err_get_vers:
	dpseci_बंद(priv->mc_io, 0, ls_dev->mc_handle);
err_खोलो:
	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_dpseci_enable(काष्ठा dpaa2_caam_priv *priv)
अणु
	काष्ठा device *dev = priv->dev;
	काष्ठा fsl_mc_device *ls_dev = to_fsl_mc_device(dev);
	काष्ठा dpaa2_caam_priv_per_cpu *ppriv;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_pairs; i++) अणु
		ppriv = per_cpu_ptr(priv->ppriv, i);
		napi_enable(&ppriv->napi);
	पूर्ण

	वापस dpseci_enable(priv->mc_io, 0, ls_dev->mc_handle);
पूर्ण

अटल पूर्णांक __cold dpaa2_dpseci_disable(काष्ठा dpaa2_caam_priv *priv)
अणु
	काष्ठा device *dev = priv->dev;
	काष्ठा dpaa2_caam_priv_per_cpu *ppriv;
	काष्ठा fsl_mc_device *ls_dev = to_fsl_mc_device(dev);
	पूर्णांक i, err = 0, enabled;

	err = dpseci_disable(priv->mc_io, 0, ls_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpseci_disable() failed\n");
		वापस err;
	पूर्ण

	err = dpseci_is_enabled(priv->mc_io, 0, ls_dev->mc_handle, &enabled);
	अगर (err) अणु
		dev_err(dev, "dpseci_is_enabled() failed\n");
		वापस err;
	पूर्ण

	dev_dbg(dev, "disable: %s\n", enabled ? "false" : "true");

	क्रम (i = 0; i < priv->num_pairs; i++) अणु
		ppriv = per_cpu_ptr(priv->ppriv, i);
		napi_disable(&ppriv->napi);
		netअगर_napi_del(&ppriv->napi);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा list_head hash_list;

अटल पूर्णांक dpaa2_caam_probe(काष्ठा fsl_mc_device *dpseci_dev)
अणु
	काष्ठा device *dev;
	काष्ठा dpaa2_caam_priv *priv;
	पूर्णांक i, err = 0;
	bool रेजिस्टरed = false;

	/*
	 * There is no way to get CAAM endianness - there is no direct रेजिस्टर
	 * space access and MC f/w करोes not provide this attribute.
	 * All DPAA2-based SoCs have little endian CAAM, thus hard-code this
	 * property.
	 */
	caam_little_end = true;

	caam_imx = false;

	dev = &dpseci_dev->dev;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(dev, priv);

	priv->करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);

	qi_cache = kmem_cache_create("dpaa2_caamqicache", CAAM_QI_MEMCACHE_SIZE,
				     0, SLAB_CACHE_DMA, शून्य);
	अगर (!qi_cache) अणु
		dev_err(dev, "Can't allocate SEC cache\n");
		वापस -ENOMEM;
	पूर्ण

	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(49));
	अगर (err) अणु
		dev_err(dev, "dma_set_mask_and_coherent() failed\n");
		जाओ err_dma_mask;
	पूर्ण

	/* Obtain a MC portal */
	err = fsl_mc_portal_allocate(dpseci_dev, 0, &priv->mc_io);
	अगर (err) अणु
		अगर (err == -ENXIO)
			err = -EPROBE_DEFER;
		अन्यथा
			dev_err(dev, "MC portal allocation failed\n");

		जाओ err_dma_mask;
	पूर्ण

	priv->ppriv = alloc_percpu(*priv->ppriv);
	अगर (!priv->ppriv) अणु
		dev_err(dev, "alloc_percpu() failed\n");
		err = -ENOMEM;
		जाओ err_alloc_ppriv;
	पूर्ण

	/* DPSECI initialization */
	err = dpaa2_dpseci_setup(dpseci_dev);
	अगर (err) अणु
		dev_err(dev, "dpaa2_dpseci_setup() failed\n");
		जाओ err_dpseci_setup;
	पूर्ण

	/* DPIO */
	err = dpaa2_dpseci_dpio_setup(priv);
	अगर (err) अणु
		dev_err_probe(dev, err, "dpaa2_dpseci_dpio_setup() failed\n");
		जाओ err_dpio_setup;
	पूर्ण

	/* DPSECI binding to DPIO */
	err = dpaa2_dpseci_bind(priv);
	अगर (err) अणु
		dev_err(dev, "dpaa2_dpseci_bind() failed\n");
		जाओ err_bind;
	पूर्ण

	/* DPSECI enable */
	err = dpaa2_dpseci_enable(priv);
	अगर (err) अणु
		dev_err(dev, "dpaa2_dpseci_enable() failed\n");
		जाओ err_bind;
	पूर्ण

	dpaa2_dpseci_debugfs_init(priv);

	/* रेजिस्टर crypto algorithms the device supports */
	क्रम (i = 0; i < ARRAY_SIZE(driver_algs); i++) अणु
		काष्ठा caam_skcipher_alg *t_alg = driver_algs + i;
		u32 alg_sel = t_alg->caam.class1_alg_type & OP_ALG_ALGSEL_MASK;

		/* Skip DES algorithms अगर not supported by device */
		अगर (!priv->sec_attr.des_acc_num &&
		    (alg_sel == OP_ALG_ALGSEL_3DES ||
		     alg_sel == OP_ALG_ALGSEL_DES))
			जारी;

		/* Skip AES algorithms अगर not supported by device */
		अगर (!priv->sec_attr.aes_acc_num &&
		    alg_sel == OP_ALG_ALGSEL_AES)
			जारी;

		/* Skip CHACHA20 algorithms अगर not supported by device */
		अगर (alg_sel == OP_ALG_ALGSEL_CHACHA20 &&
		    !priv->sec_attr.ccha_acc_num)
			जारी;

		t_alg->caam.dev = dev;
		caam_skcipher_alg_init(t_alg);

		err = crypto_रेजिस्टर_skcipher(&t_alg->skcipher);
		अगर (err) अणु
			dev_warn(dev, "%s alg registration failed: %d\n",
				 t_alg->skcipher.base.cra_driver_name, err);
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

		/* Skip DES algorithms अगर not supported by device */
		अगर (!priv->sec_attr.des_acc_num &&
		    (c1_alg_sel == OP_ALG_ALGSEL_3DES ||
		     c1_alg_sel == OP_ALG_ALGSEL_DES))
			जारी;

		/* Skip AES algorithms अगर not supported by device */
		अगर (!priv->sec_attr.aes_acc_num &&
		    c1_alg_sel == OP_ALG_ALGSEL_AES)
			जारी;

		/* Skip CHACHA20 algorithms अगर not supported by device */
		अगर (c1_alg_sel == OP_ALG_ALGSEL_CHACHA20 &&
		    !priv->sec_attr.ccha_acc_num)
			जारी;

		/* Skip POLY1305 algorithms अगर not supported by device */
		अगर (c2_alg_sel == OP_ALG_ALGSEL_POLY1305 &&
		    !priv->sec_attr.ptha_acc_num)
			जारी;

		/*
		 * Skip algorithms requiring message digests
		 * अगर MD not supported by device.
		 */
		अगर ((c2_alg_sel & ~OP_ALG_ALGSEL_SUBMASK) == 0x40 &&
		    !priv->sec_attr.md_acc_num)
			जारी;

		t_alg->caam.dev = dev;
		caam_aead_alg_init(t_alg);

		err = crypto_रेजिस्टर_aead(&t_alg->aead);
		अगर (err) अणु
			dev_warn(dev, "%s alg registration failed: %d\n",
				 t_alg->aead.base.cra_driver_name, err);
			जारी;
		पूर्ण

		t_alg->रेजिस्टरed = true;
		रेजिस्टरed = true;
	पूर्ण
	अगर (रेजिस्टरed)
		dev_info(dev, "algorithms registered in /proc/crypto\n");

	/* रेजिस्टर hash algorithms the device supports */
	INIT_LIST_HEAD(&hash_list);

	/*
	 * Skip registration of any hashing algorithms अगर MD block
	 * is not present.
	 */
	अगर (!priv->sec_attr.md_acc_num)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(driver_hash); i++) अणु
		काष्ठा caam_hash_alg *t_alg;
		काष्ठा caam_hash_ढाँचा *alg = driver_hash + i;

		/* रेजिस्टर hmac version */
		t_alg = caam_hash_alloc(dev, alg, true);
		अगर (IS_ERR(t_alg)) अणु
			err = PTR_ERR(t_alg);
			dev_warn(dev, "%s hash alg allocation failed: %d\n",
				 alg->hmac_driver_name, err);
			जारी;
		पूर्ण

		err = crypto_रेजिस्टर_ahash(&t_alg->ahash_alg);
		अगर (err) अणु
			dev_warn(dev, "%s alg registration failed: %d\n",
				 t_alg->ahash_alg.halg.base.cra_driver_name,
				 err);
			kमुक्त(t_alg);
		पूर्ण अन्यथा अणु
			list_add_tail(&t_alg->entry, &hash_list);
		पूर्ण

		/* रेजिस्टर unkeyed version */
		t_alg = caam_hash_alloc(dev, alg, false);
		अगर (IS_ERR(t_alg)) अणु
			err = PTR_ERR(t_alg);
			dev_warn(dev, "%s alg allocation failed: %d\n",
				 alg->driver_name, err);
			जारी;
		पूर्ण

		err = crypto_रेजिस्टर_ahash(&t_alg->ahash_alg);
		अगर (err) अणु
			dev_warn(dev, "%s alg registration failed: %d\n",
				 t_alg->ahash_alg.halg.base.cra_driver_name,
				 err);
			kमुक्त(t_alg);
		पूर्ण अन्यथा अणु
			list_add_tail(&t_alg->entry, &hash_list);
		पूर्ण
	पूर्ण
	अगर (!list_empty(&hash_list))
		dev_info(dev, "hash algorithms registered in /proc/crypto\n");

	वापस err;

err_bind:
	dpaa2_dpseci_dpio_मुक्त(priv);
err_dpio_setup:
	dpaa2_dpseci_मुक्त(priv);
err_dpseci_setup:
	मुक्त_percpu(priv->ppriv);
err_alloc_ppriv:
	fsl_mc_portal_मुक्त(priv->mc_io);
err_dma_mask:
	kmem_cache_destroy(qi_cache);

	वापस err;
पूर्ण

अटल पूर्णांक __cold dpaa2_caam_हटाओ(काष्ठा fsl_mc_device *ls_dev)
अणु
	काष्ठा device *dev;
	काष्ठा dpaa2_caam_priv *priv;
	पूर्णांक i;

	dev = &ls_dev->dev;
	priv = dev_get_drvdata(dev);

	dpaa2_dpseci_debugfs_निकास(priv);

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

	अगर (hash_list.next) अणु
		काष्ठा caam_hash_alg *t_hash_alg, *p;

		list_क्रम_each_entry_safe(t_hash_alg, p, &hash_list, entry) अणु
			crypto_unरेजिस्टर_ahash(&t_hash_alg->ahash_alg);
			list_del(&t_hash_alg->entry);
			kमुक्त(t_hash_alg);
		पूर्ण
	पूर्ण

	dpaa2_dpseci_disable(priv);
	dpaa2_dpseci_dpio_मुक्त(priv);
	dpaa2_dpseci_मुक्त(priv);
	मुक्त_percpu(priv->ppriv);
	fsl_mc_portal_मुक्त(priv->mc_io);
	kmem_cache_destroy(qi_cache);

	वापस 0;
पूर्ण

पूर्णांक dpaa2_caam_enqueue(काष्ठा device *dev, काष्ठा caam_request *req)
अणु
	काष्ठा dpaa2_fd fd;
	काष्ठा dpaa2_caam_priv *priv = dev_get_drvdata(dev);
	काष्ठा dpaa2_caam_priv_per_cpu *ppriv;
	पूर्णांक err = 0, i;

	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	अगर (priv->cscn_mem) अणु
		dma_sync_single_क्रम_cpu(priv->dev, priv->cscn_dma,
					DPAA2_CSCN_SIZE,
					DMA_FROM_DEVICE);
		अगर (unlikely(dpaa2_cscn_state_congested(priv->cscn_mem_aligned))) अणु
			dev_dbg_ratelimited(dev, "Dropping request\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	dpaa2_fl_set_flc(&req->fd_flt[1], req->flc_dma);

	req->fd_flt_dma = dma_map_single(dev, req->fd_flt, माप(req->fd_flt),
					 DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, req->fd_flt_dma)) अणु
		dev_err(dev, "DMA mapping error for QI enqueue request\n");
		जाओ err_out;
	पूर्ण

	स_रखो(&fd, 0, माप(fd));
	dpaa2_fd_set_क्रमmat(&fd, dpaa2_fd_list);
	dpaa2_fd_set_addr(&fd, req->fd_flt_dma);
	dpaa2_fd_set_len(&fd, dpaa2_fl_get_len(&req->fd_flt[1]));
	dpaa2_fd_set_flc(&fd, req->flc_dma);

	ppriv = this_cpu_ptr(priv->ppriv);
	क्रम (i = 0; i < (priv->dpseci_attr.num_tx_queues << 1); i++) अणु
		err = dpaa2_io_service_enqueue_fq(ppriv->dpio, ppriv->req_fqid,
						  &fd);
		अगर (err != -EBUSY)
			अवरोध;

		cpu_relax();
	पूर्ण

	अगर (unlikely(err)) अणु
		dev_err_ratelimited(dev, "Error enqueuing frame: %d\n", err);
		जाओ err_out;
	पूर्ण

	वापस -EINPROGRESS;

err_out:
	dma_unmap_single(dev, req->fd_flt_dma, माप(req->fd_flt),
			 DMA_BIसूचीECTIONAL);
	वापस -EIO;
पूर्ण
EXPORT_SYMBOL(dpaa2_caam_enqueue);

अटल स्थिर काष्ठा fsl_mc_device_id dpaa2_caam_match_id_table[] = अणु
	अणु
		.venकरोr = FSL_MC_VENDOR_FREESCALE,
		.obj_type = "dpseci",
	पूर्ण,
	अणु .venकरोr = 0x0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(fslmc, dpaa2_caam_match_id_table);

अटल काष्ठा fsl_mc_driver dpaa2_caam_driver = अणु
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.owner		= THIS_MODULE,
	पूर्ण,
	.probe		= dpaa2_caam_probe,
	.हटाओ		= dpaa2_caam_हटाओ,
	.match_id_table = dpaa2_caam_match_id_table
पूर्ण;

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Freescale Semiconductor, Inc");
MODULE_DESCRIPTION("Freescale DPAA2 CAAM Driver");

module_fsl_mc_driver(dpaa2_caam_driver);
