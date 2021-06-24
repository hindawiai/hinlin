<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Keem Bay OCS AES Crypto Driver.
 *
 * Copyright (C) 2018-2020 Intel Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/crypto.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#समावेश <crypto/aes.h>
#समावेश <crypto/engine.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/scatterwalk.h>

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश "ocs-aes.h"

#घोषणा KMB_OCS_PRIORITY	350
#घोषणा DRV_NAME		"keembay-ocs-aes"

#घोषणा OCS_AES_MIN_KEY_SIZE	16
#घोषणा OCS_AES_MAX_KEY_SIZE	32
#घोषणा OCS_AES_KEYSIZE_128	16
#घोषणा OCS_AES_KEYSIZE_192	24
#घोषणा OCS_AES_KEYSIZE_256	32
#घोषणा OCS_SM4_KEY_SIZE	16

/**
 * काष्ठा ocs_aes_tctx - OCS AES Transक्रमm context
 * @engine_ctx:		Engine context.
 * @aes_dev:		The OCS AES device.
 * @key:		AES/SM4 key.
 * @key_len:		The length (in bytes) of @key.
 * @cipher:		OCS cipher to use (either AES or SM4).
 * @sw_cipher:		The cipher to use as fallback.
 * @use_fallback:	Whether or not fallback cipher should be used.
 */
काष्ठा ocs_aes_tctx अणु
	काष्ठा crypto_engine_ctx engine_ctx;
	काष्ठा ocs_aes_dev *aes_dev;
	u8 key[OCS_AES_KEYSIZE_256];
	अचिन्हित पूर्णांक key_len;
	क्रमागत ocs_cipher cipher;
	जोड़ अणु
		काष्ठा crypto_sync_skcipher *sk;
		काष्ठा crypto_aead *aead;
	पूर्ण sw_cipher;
	bool use_fallback;
पूर्ण;

/**
 * काष्ठा ocs_aes_rctx - OCS AES Request context.
 * @inकाष्ठाion:	Inकाष्ठाion to be executed (encrypt / decrypt).
 * @mode:		Mode to use (ECB, CBC, CTR, CCm, GCM, CTS)
 * @src_nents:		Number of source SG entries.
 * @dst_nents:		Number of destination SG entries.
 * @src_dma_count:	The number of DMA-mapped entries of the source SG.
 * @dst_dma_count:	The number of DMA-mapped entries of the destination SG.
 * @in_place:		Whether or not this is an in place request, i.e.,
 *			src_sg == dst_sg.
 * @src_dll:		OCS DMA linked list क्रम input data.
 * @dst_dll:		OCS DMA linked list क्रम output data.
 * @last_ct_blk:	Buffer to hold last cipher text block (only used in CBC
 *			mode).
 * @cts_swap:		Whether or not CTS swap must be perक्रमmed.
 * @aad_src_dll:	OCS DMA linked list क्रम input AAD data.
 * @aad_dst_dll:	OCS DMA linked list क्रम output AAD data.
 * @in_tag:		Buffer to hold input encrypted tag (only used क्रम
 *			CCM/GCM decrypt).
 * @out_tag:		Buffer to hold output encrypted / decrypted tag (only
 *			used क्रम GCM encrypt / decrypt).
 */
काष्ठा ocs_aes_rctx अणु
	/* Fields common across all modes. */
	क्रमागत ocs_inकाष्ठाion	inकाष्ठाion;
	क्रमागत ocs_mode		mode;
	पूर्णांक			src_nents;
	पूर्णांक			dst_nents;
	पूर्णांक			src_dma_count;
	पूर्णांक			dst_dma_count;
	bool			in_place;
	काष्ठा ocs_dll_desc	src_dll;
	काष्ठा ocs_dll_desc	dst_dll;

	/* CBC specअगरic */
	u8			last_ct_blk[AES_BLOCK_SIZE];

	/* CTS specअगरic */
	पूर्णांक			cts_swap;

	/* CCM/GCM specअगरic */
	काष्ठा ocs_dll_desc	aad_src_dll;
	काष्ठा ocs_dll_desc	aad_dst_dll;
	u8			in_tag[AES_BLOCK_SIZE];

	/* GCM specअगरic */
	u8			out_tag[AES_BLOCK_SIZE];
पूर्ण;

/* Driver data. */
काष्ठा ocs_aes_drv अणु
	काष्ठा list_head dev_list;
	spinlock_t lock;	/* Protects dev_list. */
पूर्ण;

अटल काष्ठा ocs_aes_drv ocs_aes = अणु
	.dev_list = LIST_HEAD_INIT(ocs_aes.dev_list),
	.lock = __SPIN_LOCK_UNLOCKED(ocs_aes.lock),
पूर्ण;

अटल काष्ठा ocs_aes_dev *kmb_ocs_aes_find_dev(काष्ठा ocs_aes_tctx *tctx)
अणु
	काष्ठा ocs_aes_dev *aes_dev;

	spin_lock(&ocs_aes.lock);

	अगर (tctx->aes_dev) अणु
		aes_dev = tctx->aes_dev;
		जाओ निकास;
	पूर्ण

	/* Only a single OCS device available */
	aes_dev = list_first_entry(&ocs_aes.dev_list, काष्ठा ocs_aes_dev, list);
	tctx->aes_dev = aes_dev;

निकास:
	spin_unlock(&ocs_aes.lock);

	वापस aes_dev;
पूर्ण

/*
 * Ensure key is 128-bit or 256-bit क्रम AES or 128-bit क्रम SM4 and an actual
 * key is being passed in.
 *
 * Return: 0 अगर key is valid, -EINVAL otherwise.
 */
अटल पूर्णांक check_key(स्थिर u8 *in_key, माप_प्रकार key_len, क्रमागत ocs_cipher cipher)
अणु
	अगर (!in_key)
		वापस -EINVAL;

	/* For AES, only 128-byte or 256-byte keys are supported. */
	अगर (cipher == OCS_AES && (key_len == OCS_AES_KEYSIZE_128 ||
				  key_len == OCS_AES_KEYSIZE_256))
		वापस 0;

	/* For SM4, only 128-byte keys are supported. */
	अगर (cipher == OCS_SM4 && key_len == OCS_AES_KEYSIZE_128)
		वापस 0;

	/* Everything अन्यथा is unsupported. */
	वापस -EINVAL;
पूर्ण

/* Save key पूर्णांकo transक्रमmation context. */
अटल पूर्णांक save_key(काष्ठा ocs_aes_tctx *tctx, स्थिर u8 *in_key, माप_प्रकार key_len,
		    क्रमागत ocs_cipher cipher)
अणु
	पूर्णांक ret;

	ret = check_key(in_key, key_len, cipher);
	अगर (ret)
		वापस ret;

	स_नकल(tctx->key, in_key, key_len);
	tctx->key_len = key_len;
	tctx->cipher = cipher;

	वापस 0;
पूर्ण

/* Set key क्रम symmetric cypher. */
अटल पूर्णांक kmb_ocs_sk_set_key(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			      माप_प्रकार key_len, क्रमागत ocs_cipher cipher)
अणु
	काष्ठा ocs_aes_tctx *tctx = crypto_skcipher_ctx(tfm);

	/* Fallback is used क्रम AES with 192-bit key. */
	tctx->use_fallback = (cipher == OCS_AES &&
			      key_len == OCS_AES_KEYSIZE_192);

	अगर (!tctx->use_fallback)
		वापस save_key(tctx, in_key, key_len, cipher);

	crypto_sync_skcipher_clear_flags(tctx->sw_cipher.sk,
					 CRYPTO_TFM_REQ_MASK);
	crypto_sync_skcipher_set_flags(tctx->sw_cipher.sk,
				       tfm->base.crt_flags &
				       CRYPTO_TFM_REQ_MASK);

	वापस crypto_sync_skcipher_setkey(tctx->sw_cipher.sk, in_key, key_len);
पूर्ण

/* Set key क्रम AEAD cipher. */
अटल पूर्णांक kmb_ocs_aead_set_key(काष्ठा crypto_aead *tfm, स्थिर u8 *in_key,
				माप_प्रकार key_len, क्रमागत ocs_cipher cipher)
अणु
	काष्ठा ocs_aes_tctx *tctx = crypto_aead_ctx(tfm);

	/* Fallback is used क्रम AES with 192-bit key. */
	tctx->use_fallback = (cipher == OCS_AES &&
			      key_len == OCS_AES_KEYSIZE_192);

	अगर (!tctx->use_fallback)
		वापस save_key(tctx, in_key, key_len, cipher);

	crypto_aead_clear_flags(tctx->sw_cipher.aead, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(tctx->sw_cipher.aead,
			      crypto_aead_get_flags(tfm) & CRYPTO_TFM_REQ_MASK);

	वापस crypto_aead_setkey(tctx->sw_cipher.aead, in_key, key_len);
पूर्ण

/* Swap two AES blocks in SG lists. */
अटल व्योम sg_swap_blocks(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents,
			   off_t blk1_offset, off_t blk2_offset)
अणु
	u8 पंचांगp_buf1[AES_BLOCK_SIZE], पंचांगp_buf2[AES_BLOCK_SIZE];

	/*
	 * No easy way to copy within sg list, so copy both blocks to temporary
	 * buffers first.
	 */
	sg_pcopy_to_buffer(sgl, nents, पंचांगp_buf1, AES_BLOCK_SIZE, blk1_offset);
	sg_pcopy_to_buffer(sgl, nents, पंचांगp_buf2, AES_BLOCK_SIZE, blk2_offset);
	sg_pcopy_from_buffer(sgl, nents, पंचांगp_buf1, AES_BLOCK_SIZE, blk2_offset);
	sg_pcopy_from_buffer(sgl, nents, पंचांगp_buf2, AES_BLOCK_SIZE, blk1_offset);
पूर्ण

/* Initialize request context to शेष values. */
अटल व्योम ocs_aes_init_rctx(काष्ठा ocs_aes_rctx *rctx)
अणु
	/* Zero everything. */
	स_रखो(rctx, 0, माप(*rctx));

	/* Set initial value क्रम DMA addresses. */
	rctx->src_dll.dma_addr = DMA_MAPPING_ERROR;
	rctx->dst_dll.dma_addr = DMA_MAPPING_ERROR;
	rctx->aad_src_dll.dma_addr = DMA_MAPPING_ERROR;
	rctx->aad_dst_dll.dma_addr = DMA_MAPPING_ERROR;
पूर्ण

अटल पूर्णांक kmb_ocs_sk_validate_input(काष्ठा skcipher_request *req,
				     क्रमागत ocs_mode mode)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	पूर्णांक iv_size = crypto_skcipher_ivsize(tfm);

	चयन (mode) अणु
	हाल OCS_MODE_ECB:
		/* Ensure input length is multiple of block size */
		अगर (req->cryptlen % AES_BLOCK_SIZE != 0)
			वापस -EINVAL;

		वापस 0;

	हाल OCS_MODE_CBC:
		/* Ensure input length is multiple of block size */
		अगर (req->cryptlen % AES_BLOCK_SIZE != 0)
			वापस -EINVAL;

		/* Ensure IV is present and block size in length */
		अगर (!req->iv || iv_size != AES_BLOCK_SIZE)
			वापस -EINVAL;
		/*
		 * NOTE: Since req->cryptlen == 0 हाल was alपढ़ोy handled in
		 * kmb_ocs_sk_common(), the above two conditions also guarantee
		 * that: cryptlen >= iv_size
		 */
		वापस 0;

	हाल OCS_MODE_CTR:
		/* Ensure IV is present and block size in length */
		अगर (!req->iv || iv_size != AES_BLOCK_SIZE)
			वापस -EINVAL;
		वापस 0;

	हाल OCS_MODE_CTS:
		/* Ensure input length >= block size */
		अगर (req->cryptlen < AES_BLOCK_SIZE)
			वापस -EINVAL;

		/* Ensure IV is present and block size in length */
		अगर (!req->iv || iv_size != AES_BLOCK_SIZE)
			वापस -EINVAL;

		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Called by encrypt() / decrypt() skcipher functions.
 *
 * Use fallback अगर needed, otherwise initialize context and enqueue request
 * पूर्णांकo engine.
 */
अटल पूर्णांक kmb_ocs_sk_common(काष्ठा skcipher_request *req,
			     क्रमागत ocs_cipher cipher,
			     क्रमागत ocs_inकाष्ठाion inकाष्ठाion,
			     क्रमागत ocs_mode mode)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ocs_aes_rctx *rctx = skcipher_request_ctx(req);
	काष्ठा ocs_aes_tctx *tctx = crypto_skcipher_ctx(tfm);
	काष्ठा ocs_aes_dev *aes_dev;
	पूर्णांक rc;

	अगर (tctx->use_fallback) अणु
		SYNC_SKCIPHER_REQUEST_ON_STACK(subreq, tctx->sw_cipher.sk);

		skcipher_request_set_sync_tfm(subreq, tctx->sw_cipher.sk);
		skcipher_request_set_callback(subreq, req->base.flags, शून्य,
					      शून्य);
		skcipher_request_set_crypt(subreq, req->src, req->dst,
					   req->cryptlen, req->iv);

		अगर (inकाष्ठाion == OCS_ENCRYPT)
			rc = crypto_skcipher_encrypt(subreq);
		अन्यथा
			rc = crypto_skcipher_decrypt(subreq);

		skcipher_request_zero(subreq);

		वापस rc;
	पूर्ण

	/*
	 * If cryptlen == 0, no processing needed क्रम ECB, CBC and CTR.
	 *
	 * For CTS जारी: kmb_ocs_sk_validate_input() will वापस -EINVAL.
	 */
	अगर (!req->cryptlen && mode != OCS_MODE_CTS)
		वापस 0;

	rc = kmb_ocs_sk_validate_input(req, mode);
	अगर (rc)
		वापस rc;

	aes_dev = kmb_ocs_aes_find_dev(tctx);
	अगर (!aes_dev)
		वापस -ENODEV;

	अगर (cipher != tctx->cipher)
		वापस -EINVAL;

	ocs_aes_init_rctx(rctx);
	rctx->inकाष्ठाion = inकाष्ठाion;
	rctx->mode = mode;

	वापस crypto_transfer_skcipher_request_to_engine(aes_dev->engine, req);
पूर्ण

अटल व्योम cleanup_ocs_dma_linked_list(काष्ठा device *dev,
					काष्ठा ocs_dll_desc *dll)
अणु
	अगर (dll->vaddr)
		dma_मुक्त_coherent(dev, dll->size, dll->vaddr, dll->dma_addr);
	dll->vaddr = शून्य;
	dll->size = 0;
	dll->dma_addr = DMA_MAPPING_ERROR;
पूर्ण

अटल व्योम kmb_ocs_sk_dma_cleanup(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ocs_aes_rctx *rctx = skcipher_request_ctx(req);
	काष्ठा ocs_aes_tctx *tctx = crypto_skcipher_ctx(tfm);
	काष्ठा device *dev = tctx->aes_dev->dev;

	अगर (rctx->src_dma_count) अणु
		dma_unmap_sg(dev, req->src, rctx->src_nents, DMA_TO_DEVICE);
		rctx->src_dma_count = 0;
	पूर्ण

	अगर (rctx->dst_dma_count) अणु
		dma_unmap_sg(dev, req->dst, rctx->dst_nents, rctx->in_place ?
							     DMA_BIसूचीECTIONAL :
							     DMA_FROM_DEVICE);
		rctx->dst_dma_count = 0;
	पूर्ण

	/* Clean up OCS DMA linked lists */
	cleanup_ocs_dma_linked_list(dev, &rctx->src_dll);
	cleanup_ocs_dma_linked_list(dev, &rctx->dst_dll);
पूर्ण

अटल पूर्णांक kmb_ocs_sk_prepare_inplace(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ocs_aes_rctx *rctx = skcipher_request_ctx(req);
	काष्ठा ocs_aes_tctx *tctx = crypto_skcipher_ctx(tfm);
	पूर्णांक iv_size = crypto_skcipher_ivsize(tfm);
	पूर्णांक rc;

	/*
	 * For CBC decrypt, save last block (iv) to last_ct_blk buffer.
	 *
	 * Note: अगर we are here, we alपढ़ोy checked that cryptlen >= iv_size
	 * and iv_size == AES_BLOCK_SIZE (i.e., the size of last_ct_blk); see
	 * kmb_ocs_sk_validate_input().
	 */
	अगर (rctx->mode == OCS_MODE_CBC && rctx->inकाष्ठाion == OCS_DECRYPT)
		scatterwalk_map_and_copy(rctx->last_ct_blk, req->src,
					 req->cryptlen - iv_size, iv_size, 0);

	/* For CTS decrypt, swap last two blocks, अगर needed. */
	अगर (rctx->cts_swap && rctx->inकाष्ठाion == OCS_DECRYPT)
		sg_swap_blocks(req->dst, rctx->dst_nents,
			       req->cryptlen - AES_BLOCK_SIZE,
			       req->cryptlen - (2 * AES_BLOCK_SIZE));

	/* src and dst buffers are the same, use bidirectional DMA mapping. */
	rctx->dst_dma_count = dma_map_sg(tctx->aes_dev->dev, req->dst,
					 rctx->dst_nents, DMA_BIसूचीECTIONAL);
	अगर (rctx->dst_dma_count == 0) अणु
		dev_err(tctx->aes_dev->dev, "Failed to map destination sg\n");
		वापस -ENOMEM;
	पूर्ण

	/* Create DST linked list */
	rc = ocs_create_linked_list_from_sg(tctx->aes_dev, req->dst,
					    rctx->dst_dma_count, &rctx->dst_dll,
					    req->cryptlen, 0);
	अगर (rc)
		वापस rc;
	/*
	 * If descriptor creation was successful, set the src_dll.dma_addr to
	 * the value of dst_dll.dma_addr, as we करो in-place AES operation on
	 * the src.
	 */
	rctx->src_dll.dma_addr = rctx->dst_dll.dma_addr;

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_ocs_sk_prepare_notinplace(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ocs_aes_rctx *rctx = skcipher_request_ctx(req);
	काष्ठा ocs_aes_tctx *tctx = crypto_skcipher_ctx(tfm);
	पूर्णांक rc;

	rctx->src_nents =  sg_nents_क्रम_len(req->src, req->cryptlen);
	अगर (rctx->src_nents < 0)
		वापस -EBADMSG;

	/* Map SRC SG. */
	rctx->src_dma_count = dma_map_sg(tctx->aes_dev->dev, req->src,
					 rctx->src_nents, DMA_TO_DEVICE);
	अगर (rctx->src_dma_count == 0) अणु
		dev_err(tctx->aes_dev->dev, "Failed to map source sg\n");
		वापस -ENOMEM;
	पूर्ण

	/* Create SRC linked list */
	rc = ocs_create_linked_list_from_sg(tctx->aes_dev, req->src,
					    rctx->src_dma_count, &rctx->src_dll,
					    req->cryptlen, 0);
	अगर (rc)
		वापस rc;

	/* Map DST SG. */
	rctx->dst_dma_count = dma_map_sg(tctx->aes_dev->dev, req->dst,
					 rctx->dst_nents, DMA_FROM_DEVICE);
	अगर (rctx->dst_dma_count == 0) अणु
		dev_err(tctx->aes_dev->dev, "Failed to map destination sg\n");
		वापस -ENOMEM;
	पूर्ण

	/* Create DST linked list */
	rc = ocs_create_linked_list_from_sg(tctx->aes_dev, req->dst,
					    rctx->dst_dma_count, &rctx->dst_dll,
					    req->cryptlen, 0);
	अगर (rc)
		वापस rc;

	/* If this is not a CTS decrypt operation with swapping, we are करोne. */
	अगर (!(rctx->cts_swap && rctx->inकाष्ठाion == OCS_DECRYPT))
		वापस 0;

	/*
	 * Otherwise, we have to copy src to dst (as we cannot modअगरy src).
	 * Use OCS AES bypass mode to copy src to dst via DMA.
	 *
	 * NOTE: क्रम anything other than small data sizes this is rather
	 * inefficient.
	 */
	rc = ocs_aes_bypass_op(tctx->aes_dev, rctx->dst_dll.dma_addr,
			       rctx->src_dll.dma_addr, req->cryptlen);
	अगर (rc)
		वापस rc;

	/*
	 * Now dst == src, so clean up what we did so far and use in_place
	 * logic.
	 */
	kmb_ocs_sk_dma_cleanup(req);
	rctx->in_place = true;

	वापस kmb_ocs_sk_prepare_inplace(req);
पूर्ण

अटल पूर्णांक kmb_ocs_sk_run(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ocs_aes_rctx *rctx = skcipher_request_ctx(req);
	काष्ठा ocs_aes_tctx *tctx = crypto_skcipher_ctx(tfm);
	काष्ठा ocs_aes_dev *aes_dev = tctx->aes_dev;
	पूर्णांक iv_size = crypto_skcipher_ivsize(tfm);
	पूर्णांक rc;

	rctx->dst_nents = sg_nents_क्रम_len(req->dst, req->cryptlen);
	अगर (rctx->dst_nents < 0)
		वापस -EBADMSG;

	/*
	 * If 2 blocks or greater, and multiple of block size swap last two
	 * blocks to be compatible with other crypto API CTS implementations:
	 * OCS mode uses CBC-CS2, whereas other crypto API implementations use
	 * CBC-CS3.
	 * CBC-CS2 and CBC-CS3 defined by:
	 * https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialखुलाation800-38a-add.pdf
	 */
	rctx->cts_swap = (rctx->mode == OCS_MODE_CTS &&
			  req->cryptlen > AES_BLOCK_SIZE &&
			  req->cryptlen % AES_BLOCK_SIZE == 0);

	rctx->in_place = (req->src == req->dst);

	अगर (rctx->in_place)
		rc = kmb_ocs_sk_prepare_inplace(req);
	अन्यथा
		rc = kmb_ocs_sk_prepare_notinplace(req);

	अगर (rc)
		जाओ error;

	rc = ocs_aes_op(aes_dev, rctx->mode, tctx->cipher, rctx->inकाष्ठाion,
			rctx->dst_dll.dma_addr, rctx->src_dll.dma_addr,
			req->cryptlen, req->iv, iv_size);
	अगर (rc)
		जाओ error;

	/* Clean-up DMA beक्रमe further processing output. */
	kmb_ocs_sk_dma_cleanup(req);

	/* For CTS Encrypt, swap last 2 blocks, अगर needed. */
	अगर (rctx->cts_swap && rctx->inकाष्ठाion == OCS_ENCRYPT) अणु
		sg_swap_blocks(req->dst, rctx->dst_nents,
			       req->cryptlen - AES_BLOCK_SIZE,
			       req->cryptlen - (2 * AES_BLOCK_SIZE));
		वापस 0;
	पूर्ण

	/* For CBC copy IV to req->IV. */
	अगर (rctx->mode == OCS_MODE_CBC) अणु
		/* CBC encrypt हाल. */
		अगर (rctx->inकाष्ठाion == OCS_ENCRYPT) अणु
			scatterwalk_map_and_copy(req->iv, req->dst,
						 req->cryptlen - iv_size,
						 iv_size, 0);
			वापस 0;
		पूर्ण
		/* CBC decrypt हाल. */
		अगर (rctx->in_place)
			स_नकल(req->iv, rctx->last_ct_blk, iv_size);
		अन्यथा
			scatterwalk_map_and_copy(req->iv, req->src,
						 req->cryptlen - iv_size,
						 iv_size, 0);
		वापस 0;
	पूर्ण
	/* For all other modes there's nothing to करो. */

	वापस 0;

error:
	kmb_ocs_sk_dma_cleanup(req);

	वापस rc;
पूर्ण

अटल पूर्णांक kmb_ocs_aead_validate_input(काष्ठा aead_request *req,
				       क्रमागत ocs_inकाष्ठाion inकाष्ठाion,
				       क्रमागत ocs_mode mode)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	पूर्णांक tag_size = crypto_aead_authsize(tfm);
	पूर्णांक iv_size = crypto_aead_ivsize(tfm);

	/* For decrypt crytplen == len(PT) + len(tag). */
	अगर (inकाष्ठाion == OCS_DECRYPT && req->cryptlen < tag_size)
		वापस -EINVAL;

	/* IV is mandatory. */
	अगर (!req->iv)
		वापस -EINVAL;

	चयन (mode) अणु
	हाल OCS_MODE_GCM:
		अगर (iv_size != GCM_AES_IV_SIZE)
			वापस -EINVAL;

		वापस 0;

	हाल OCS_MODE_CCM:
		/* Ensure IV is present and block size in length */
		अगर (iv_size != AES_BLOCK_SIZE)
			वापस -EINVAL;

		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Called by encrypt() / decrypt() aead functions.
 *
 * Use fallback अगर needed, otherwise initialize context and enqueue request
 * पूर्णांकo engine.
 */
अटल पूर्णांक kmb_ocs_aead_common(काष्ठा aead_request *req,
			       क्रमागत ocs_cipher cipher,
			       क्रमागत ocs_inकाष्ठाion inकाष्ठाion,
			       क्रमागत ocs_mode mode)
अणु
	काष्ठा ocs_aes_tctx *tctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा ocs_aes_rctx *rctx = aead_request_ctx(req);
	काष्ठा ocs_aes_dev *dd;
	पूर्णांक rc;

	अगर (tctx->use_fallback) अणु
		काष्ठा aead_request *subreq = aead_request_ctx(req);

		aead_request_set_tfm(subreq, tctx->sw_cipher.aead);
		aead_request_set_callback(subreq, req->base.flags,
					  req->base.complete, req->base.data);
		aead_request_set_crypt(subreq, req->src, req->dst,
				       req->cryptlen, req->iv);
		aead_request_set_ad(subreq, req->assoclen);
		rc = crypto_aead_setauthsize(tctx->sw_cipher.aead,
					     crypto_aead_authsize(crypto_aead_reqtfm(req)));
		अगर (rc)
			वापस rc;

		वापस (inकाष्ठाion == OCS_ENCRYPT) ?
		       crypto_aead_encrypt(subreq) :
		       crypto_aead_decrypt(subreq);
	पूर्ण

	rc = kmb_ocs_aead_validate_input(req, inकाष्ठाion, mode);
	अगर (rc)
		वापस rc;

	dd = kmb_ocs_aes_find_dev(tctx);
	अगर (!dd)
		वापस -ENODEV;

	अगर (cipher != tctx->cipher)
		वापस -EINVAL;

	ocs_aes_init_rctx(rctx);
	rctx->inकाष्ठाion = inकाष्ठाion;
	rctx->mode = mode;

	वापस crypto_transfer_aead_request_to_engine(dd->engine, req);
पूर्ण

अटल व्योम kmb_ocs_aead_dma_cleanup(काष्ठा aead_request *req)
अणु
	काष्ठा ocs_aes_tctx *tctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा ocs_aes_rctx *rctx = aead_request_ctx(req);
	काष्ठा device *dev = tctx->aes_dev->dev;

	अगर (rctx->src_dma_count) अणु
		dma_unmap_sg(dev, req->src, rctx->src_nents, DMA_TO_DEVICE);
		rctx->src_dma_count = 0;
	पूर्ण

	अगर (rctx->dst_dma_count) अणु
		dma_unmap_sg(dev, req->dst, rctx->dst_nents, rctx->in_place ?
							     DMA_BIसूचीECTIONAL :
							     DMA_FROM_DEVICE);
		rctx->dst_dma_count = 0;
	पूर्ण
	/* Clean up OCS DMA linked lists */
	cleanup_ocs_dma_linked_list(dev, &rctx->src_dll);
	cleanup_ocs_dma_linked_list(dev, &rctx->dst_dll);
	cleanup_ocs_dma_linked_list(dev, &rctx->aad_src_dll);
	cleanup_ocs_dma_linked_list(dev, &rctx->aad_dst_dll);
पूर्ण

/**
 * kmb_ocs_aead_dma_prepare() - Do DMA mapping क्रम AEAD processing.
 * @req:		The AEAD request being processed.
 * @src_dll_size:	Where to store the length of the data mapped पूर्णांकo the
 *			src_dll OCS DMA list.
 *
 * Do the following:
 * - DMA map req->src and req->dst
 * - Initialize the following OCS DMA linked lists: rctx->src_dll,
 *   rctx->dst_dll, rctx->aad_src_dll and rxtc->aad_dst_dll.
 *
 * Return: 0 on success, negative error code otherwise.
 */
अटल पूर्णांक kmb_ocs_aead_dma_prepare(काष्ठा aead_request *req, u32 *src_dll_size)
अणु
	काष्ठा ocs_aes_tctx *tctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	स्थिर पूर्णांक tag_size = crypto_aead_authsize(crypto_aead_reqtfm(req));
	काष्ठा ocs_aes_rctx *rctx = aead_request_ctx(req);
	u32 in_size;	/* The length of the data to be mapped by src_dll. */
	u32 out_size;	/* The length of the data to be mapped by dst_dll. */
	u32 dst_size;	/* The length of the data in dst_sg. */
	पूर्णांक rc;

	/* Get number of entries in input data SG list. */
	rctx->src_nents = sg_nents_क्रम_len(req->src,
					   req->assoclen + req->cryptlen);
	अगर (rctx->src_nents < 0)
		वापस -EBADMSG;

	अगर (rctx->inकाष्ठाion == OCS_DECRYPT) अणु
		/*
		 * For decrypt:
		 * - src sg list is:		AAD|CT|tag
		 * - dst sg list expects:	AAD|PT
		 *
		 * in_size == len(CT); out_size == len(PT)
		 */

		/* req->cryptlen includes both CT and tag. */
		in_size = req->cryptlen - tag_size;

		/* out_size = PT size == CT size */
		out_size = in_size;

		/* len(dst_sg) == len(AAD) + len(PT) */
		dst_size = req->assoclen + out_size;

		/*
		 * Copy tag from source SG list to 'in_tag' buffer.
		 *
		 * Note: this needs to be करोne here, beक्रमe DMA mapping src_sg.
		 */
		sg_pcopy_to_buffer(req->src, rctx->src_nents, rctx->in_tag,
				   tag_size, req->assoclen + in_size);

	पूर्ण अन्यथा अणु /* OCS_ENCRYPT */
		/*
		 * For encrypt:
		 *	src sg list is:		AAD|PT
		 *	dst sg list expects:	AAD|CT|tag
		 */
		/* in_size == len(PT) */
		in_size = req->cryptlen;

		/*
		 * In CCM mode the OCS engine appends the tag to the ciphertext,
		 * but in GCM mode the tag must be पढ़ो from the tag रेजिस्टरs
		 * and appended manually below
		 */
		out_size = (rctx->mode == OCS_MODE_CCM) ? in_size + tag_size :
							  in_size;
		/* len(dst_sg) == len(AAD) + len(CT) + len(tag) */
		dst_size = req->assoclen + in_size + tag_size;
	पूर्ण
	*src_dll_size = in_size;

	/* Get number of entries in output data SG list. */
	rctx->dst_nents = sg_nents_क्रम_len(req->dst, dst_size);
	अगर (rctx->dst_nents < 0)
		वापस -EBADMSG;

	rctx->in_place = (req->src == req->dst) ? 1 : 0;

	/* Map destination; use bidirectional mapping क्रम in-place हाल. */
	rctx->dst_dma_count = dma_map_sg(tctx->aes_dev->dev, req->dst,
					 rctx->dst_nents,
					 rctx->in_place ? DMA_BIसूचीECTIONAL :
							  DMA_FROM_DEVICE);
	अगर (rctx->dst_dma_count == 0 && rctx->dst_nents != 0) अणु
		dev_err(tctx->aes_dev->dev, "Failed to map destination sg\n");
		वापस -ENOMEM;
	पूर्ण

	/* Create AAD DST list: maps dst[0:AAD_SIZE-1]. */
	rc = ocs_create_linked_list_from_sg(tctx->aes_dev, req->dst,
					    rctx->dst_dma_count,
					    &rctx->aad_dst_dll, req->assoclen,
					    0);
	अगर (rc)
		वापस rc;

	/* Create DST list: maps dst[AAD_SIZE:out_size] */
	rc = ocs_create_linked_list_from_sg(tctx->aes_dev, req->dst,
					    rctx->dst_dma_count, &rctx->dst_dll,
					    out_size, req->assoclen);
	अगर (rc)
		वापस rc;

	अगर (rctx->in_place) अणु
		/* If this is not CCM encrypt, we are करोne. */
		अगर (!(rctx->mode == OCS_MODE_CCM &&
		      rctx->inकाष्ठाion == OCS_ENCRYPT)) अणु
			/*
			 * SRC and DST are the same, so re-use the same DMA
			 * addresses (to aव्योम allocating new DMA lists
			 * identical to the dst ones).
			 */
			rctx->src_dll.dma_addr = rctx->dst_dll.dma_addr;
			rctx->aad_src_dll.dma_addr = rctx->aad_dst_dll.dma_addr;

			वापस 0;
		पूर्ण
		/*
		 * For CCM encrypt the input and output linked lists contain
		 * dअगरferent amounts of data, so, we need to create dअगरferent
		 * SRC and AAD SRC lists, even क्रम the in-place हाल.
		 */
		rc = ocs_create_linked_list_from_sg(tctx->aes_dev, req->dst,
						    rctx->dst_dma_count,
						    &rctx->aad_src_dll,
						    req->assoclen, 0);
		अगर (rc)
			वापस rc;
		rc = ocs_create_linked_list_from_sg(tctx->aes_dev, req->dst,
						    rctx->dst_dma_count,
						    &rctx->src_dll, in_size,
						    req->assoclen);
		अगर (rc)
			वापस rc;

		वापस 0;
	पूर्ण
	/* Not in-place हाल. */

	/* Map source SG. */
	rctx->src_dma_count = dma_map_sg(tctx->aes_dev->dev, req->src,
					 rctx->src_nents, DMA_TO_DEVICE);
	अगर (rctx->src_dma_count == 0 && rctx->src_nents != 0) अणु
		dev_err(tctx->aes_dev->dev, "Failed to map source sg\n");
		वापस -ENOMEM;
	पूर्ण

	/* Create AAD SRC list. */
	rc = ocs_create_linked_list_from_sg(tctx->aes_dev, req->src,
					    rctx->src_dma_count,
					    &rctx->aad_src_dll,
					    req->assoclen, 0);
	अगर (rc)
		वापस rc;

	/* Create SRC list. */
	rc = ocs_create_linked_list_from_sg(tctx->aes_dev, req->src,
					    rctx->src_dma_count,
					    &rctx->src_dll, in_size,
					    req->assoclen);
	अगर (rc)
		वापस rc;

	अगर (req->assoclen == 0)
		वापस 0;

	/* Copy AAD from src sg to dst sg using OCS DMA. */
	rc = ocs_aes_bypass_op(tctx->aes_dev, rctx->aad_dst_dll.dma_addr,
			       rctx->aad_src_dll.dma_addr, req->cryptlen);
	अगर (rc)
		dev_err(tctx->aes_dev->dev,
			"Failed to copy source AAD to destination AAD\n");

	वापस rc;
पूर्ण

अटल पूर्णांक kmb_ocs_aead_run(काष्ठा aead_request *req)
अणु
	काष्ठा ocs_aes_tctx *tctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	स्थिर पूर्णांक tag_size = crypto_aead_authsize(crypto_aead_reqtfm(req));
	काष्ठा ocs_aes_rctx *rctx = aead_request_ctx(req);
	u32 in_size;	/* The length of the data mapped by src_dll. */
	पूर्णांक rc;

	rc = kmb_ocs_aead_dma_prepare(req, &in_size);
	अगर (rc)
		जाओ निकास;

	/* For CCM, we just call the OCS processing and we are करोne. */
	अगर (rctx->mode == OCS_MODE_CCM) अणु
		rc = ocs_aes_ccm_op(tctx->aes_dev, tctx->cipher,
				    rctx->inकाष्ठाion, rctx->dst_dll.dma_addr,
				    rctx->src_dll.dma_addr, in_size,
				    req->iv,
				    rctx->aad_src_dll.dma_addr, req->assoclen,
				    rctx->in_tag, tag_size);
		जाओ निकास;
	पूर्ण
	/* GCM हाल; invoke OCS processing. */
	rc = ocs_aes_gcm_op(tctx->aes_dev, tctx->cipher,
			    rctx->inकाष्ठाion,
			    rctx->dst_dll.dma_addr,
			    rctx->src_dll.dma_addr, in_size,
			    req->iv,
			    rctx->aad_src_dll.dma_addr, req->assoclen,
			    rctx->out_tag, tag_size);
	अगर (rc)
		जाओ निकास;

	/* For GCM decrypt, we have to compare in_tag with out_tag. */
	अगर (rctx->inकाष्ठाion == OCS_DECRYPT) अणु
		rc = स_भेद(rctx->in_tag, rctx->out_tag, tag_size) ?
		     -EBADMSG : 0;
		जाओ निकास;
	पूर्ण

	/* For GCM encrypt, we must manually copy out_tag to DST sg. */

	/* Clean-up must be called beक्रमe the sg_pcopy_from_buffer() below. */
	kmb_ocs_aead_dma_cleanup(req);

	/* Copy tag to destination sg after AAD and CT. */
	sg_pcopy_from_buffer(req->dst, rctx->dst_nents, rctx->out_tag,
			     tag_size, req->assoclen + req->cryptlen);

	/* Return directly as DMA cleanup alपढ़ोy करोne. */
	वापस 0;

निकास:
	kmb_ocs_aead_dma_cleanup(req);

	वापस rc;
पूर्ण

अटल पूर्णांक kmb_ocs_aes_sk_करो_one_request(काष्ठा crypto_engine *engine,
					 व्योम *areq)
अणु
	काष्ठा skcipher_request *req =
			container_of(areq, काष्ठा skcipher_request, base);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ocs_aes_tctx *tctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err;

	अगर (!tctx->aes_dev) अणु
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	err = ocs_aes_set_key(tctx->aes_dev, tctx->key_len, tctx->key,
			      tctx->cipher);
	अगर (err)
		जाओ निकास;

	err = kmb_ocs_sk_run(req);

निकास:
	crypto_finalize_skcipher_request(engine, req, err);

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_ocs_aes_aead_करो_one_request(काष्ठा crypto_engine *engine,
					   व्योम *areq)
अणु
	काष्ठा aead_request *req = container_of(areq,
						काष्ठा aead_request, base);
	काष्ठा ocs_aes_tctx *tctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	पूर्णांक err;

	अगर (!tctx->aes_dev)
		वापस -ENODEV;

	err = ocs_aes_set_key(tctx->aes_dev, tctx->key_len, tctx->key,
			      tctx->cipher);
	अगर (err)
		जाओ निकास;

	err = kmb_ocs_aead_run(req);

निकास:
	crypto_finalize_aead_request(tctx->aes_dev->engine, req, err);

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_ocs_aes_set_key(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			       अचिन्हित पूर्णांक key_len)
अणु
	वापस kmb_ocs_sk_set_key(tfm, in_key, key_len, OCS_AES);
पूर्ण

अटल पूर्णांक kmb_ocs_aes_aead_set_key(काष्ठा crypto_aead *tfm, स्थिर u8 *in_key,
				    अचिन्हित पूर्णांक key_len)
अणु
	वापस kmb_ocs_aead_set_key(tfm, in_key, key_len, OCS_AES);
पूर्ण

#अगर_घोषित CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_ECB
अटल पूर्णांक kmb_ocs_aes_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_AES, OCS_ENCRYPT, OCS_MODE_ECB);
पूर्ण

अटल पूर्णांक kmb_ocs_aes_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_AES, OCS_DECRYPT, OCS_MODE_ECB);
पूर्ण
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_ECB */

अटल पूर्णांक kmb_ocs_aes_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_AES, OCS_ENCRYPT, OCS_MODE_CBC);
पूर्ण

अटल पूर्णांक kmb_ocs_aes_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_AES, OCS_DECRYPT, OCS_MODE_CBC);
पूर्ण

अटल पूर्णांक kmb_ocs_aes_ctr_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_AES, OCS_ENCRYPT, OCS_MODE_CTR);
पूर्ण

अटल पूर्णांक kmb_ocs_aes_ctr_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_AES, OCS_DECRYPT, OCS_MODE_CTR);
पूर्ण

#अगर_घोषित CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_CTS
अटल पूर्णांक kmb_ocs_aes_cts_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_AES, OCS_ENCRYPT, OCS_MODE_CTS);
पूर्ण

अटल पूर्णांक kmb_ocs_aes_cts_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_AES, OCS_DECRYPT, OCS_MODE_CTS);
पूर्ण
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_CTS */

अटल पूर्णांक kmb_ocs_aes_gcm_encrypt(काष्ठा aead_request *req)
अणु
	वापस kmb_ocs_aead_common(req, OCS_AES, OCS_ENCRYPT, OCS_MODE_GCM);
पूर्ण

अटल पूर्णांक kmb_ocs_aes_gcm_decrypt(काष्ठा aead_request *req)
अणु
	वापस kmb_ocs_aead_common(req, OCS_AES, OCS_DECRYPT, OCS_MODE_GCM);
पूर्ण

अटल पूर्णांक kmb_ocs_aes_ccm_encrypt(काष्ठा aead_request *req)
अणु
	वापस kmb_ocs_aead_common(req, OCS_AES, OCS_ENCRYPT, OCS_MODE_CCM);
पूर्ण

अटल पूर्णांक kmb_ocs_aes_ccm_decrypt(काष्ठा aead_request *req)
अणु
	वापस kmb_ocs_aead_common(req, OCS_AES, OCS_DECRYPT, OCS_MODE_CCM);
पूर्ण

अटल पूर्णांक kmb_ocs_sm4_set_key(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			       अचिन्हित पूर्णांक key_len)
अणु
	वापस kmb_ocs_sk_set_key(tfm, in_key, key_len, OCS_SM4);
पूर्ण

अटल पूर्णांक kmb_ocs_sm4_aead_set_key(काष्ठा crypto_aead *tfm, स्थिर u8 *in_key,
				    अचिन्हित पूर्णांक key_len)
अणु
	वापस kmb_ocs_aead_set_key(tfm, in_key, key_len, OCS_SM4);
पूर्ण

#अगर_घोषित CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_ECB
अटल पूर्णांक kmb_ocs_sm4_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_SM4, OCS_ENCRYPT, OCS_MODE_ECB);
पूर्ण

अटल पूर्णांक kmb_ocs_sm4_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_SM4, OCS_DECRYPT, OCS_MODE_ECB);
पूर्ण
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_ECB */

अटल पूर्णांक kmb_ocs_sm4_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_SM4, OCS_ENCRYPT, OCS_MODE_CBC);
पूर्ण

अटल पूर्णांक kmb_ocs_sm4_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_SM4, OCS_DECRYPT, OCS_MODE_CBC);
पूर्ण

अटल पूर्णांक kmb_ocs_sm4_ctr_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_SM4, OCS_ENCRYPT, OCS_MODE_CTR);
पूर्ण

अटल पूर्णांक kmb_ocs_sm4_ctr_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_SM4, OCS_DECRYPT, OCS_MODE_CTR);
पूर्ण

#अगर_घोषित CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_CTS
अटल पूर्णांक kmb_ocs_sm4_cts_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_SM4, OCS_ENCRYPT, OCS_MODE_CTS);
पूर्ण

अटल पूर्णांक kmb_ocs_sm4_cts_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस kmb_ocs_sk_common(req, OCS_SM4, OCS_DECRYPT, OCS_MODE_CTS);
पूर्ण
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_CTS */

अटल पूर्णांक kmb_ocs_sm4_gcm_encrypt(काष्ठा aead_request *req)
अणु
	वापस kmb_ocs_aead_common(req, OCS_SM4, OCS_ENCRYPT, OCS_MODE_GCM);
पूर्ण

अटल पूर्णांक kmb_ocs_sm4_gcm_decrypt(काष्ठा aead_request *req)
अणु
	वापस kmb_ocs_aead_common(req, OCS_SM4, OCS_DECRYPT, OCS_MODE_GCM);
पूर्ण

अटल पूर्णांक kmb_ocs_sm4_ccm_encrypt(काष्ठा aead_request *req)
अणु
	वापस kmb_ocs_aead_common(req, OCS_SM4, OCS_ENCRYPT, OCS_MODE_CCM);
पूर्ण

अटल पूर्णांक kmb_ocs_sm4_ccm_decrypt(काष्ठा aead_request *req)
अणु
	वापस kmb_ocs_aead_common(req, OCS_SM4, OCS_DECRYPT, OCS_MODE_CCM);
पूर्ण

अटल अंतरभूत पूर्णांक ocs_common_init(काष्ठा ocs_aes_tctx *tctx)
अणु
	tctx->engine_ctx.op.prepare_request = शून्य;
	tctx->engine_ctx.op.करो_one_request = kmb_ocs_aes_sk_करो_one_request;
	tctx->engine_ctx.op.unprepare_request = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक ocs_aes_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	स्थिर अक्षर *alg_name = crypto_tfm_alg_name(&tfm->base);
	काष्ठा ocs_aes_tctx *tctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_sync_skcipher *blk;

	/* set fallback cipher in हाल it will be needed */
	blk = crypto_alloc_sync_skcipher(alg_name, 0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(blk))
		वापस PTR_ERR(blk);

	tctx->sw_cipher.sk = blk;

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा ocs_aes_rctx));

	वापस ocs_common_init(tctx);
पूर्ण

अटल पूर्णांक ocs_sm4_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा ocs_aes_tctx *tctx = crypto_skcipher_ctx(tfm);

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा ocs_aes_rctx));

	वापस ocs_common_init(tctx);
पूर्ण

अटल अंतरभूत व्योम clear_key(काष्ठा ocs_aes_tctx *tctx)
अणु
	memzero_explicit(tctx->key, OCS_AES_KEYSIZE_256);

	/* Zero key रेजिस्टरs अगर set */
	अगर (tctx->aes_dev)
		ocs_aes_set_key(tctx->aes_dev, OCS_AES_KEYSIZE_256,
				tctx->key, OCS_AES);
पूर्ण

अटल व्योम ocs_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा ocs_aes_tctx *tctx = crypto_skcipher_ctx(tfm);

	clear_key(tctx);

	अगर (tctx->sw_cipher.sk) अणु
		crypto_मुक्त_sync_skcipher(tctx->sw_cipher.sk);
		tctx->sw_cipher.sk = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक ocs_common_aead_init(काष्ठा ocs_aes_tctx *tctx)
अणु
	tctx->engine_ctx.op.prepare_request = शून्य;
	tctx->engine_ctx.op.करो_one_request = kmb_ocs_aes_aead_करो_one_request;
	tctx->engine_ctx.op.unprepare_request = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक ocs_aes_aead_cra_init(काष्ठा crypto_aead *tfm)
अणु
	स्थिर अक्षर *alg_name = crypto_tfm_alg_name(&tfm->base);
	काष्ठा ocs_aes_tctx *tctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_aead *blk;

	/* Set fallback cipher in हाल it will be needed */
	blk = crypto_alloc_aead(alg_name, 0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(blk))
		वापस PTR_ERR(blk);

	tctx->sw_cipher.aead = blk;

	crypto_aead_set_reqsize(tfm,
				max(माप(काष्ठा ocs_aes_rctx),
				    (माप(काष्ठा aead_request) +
				     crypto_aead_reqsize(tctx->sw_cipher.aead))));

	वापस ocs_common_aead_init(tctx);
पूर्ण

अटल पूर्णांक kmb_ocs_aead_ccm_setauthsize(काष्ठा crypto_aead *tfm,
					अचिन्हित पूर्णांक authsize)
अणु
	चयन (authsize) अणु
	हाल 4:
	हाल 6:
	हाल 8:
	हाल 10:
	हाल 12:
	हाल 14:
	हाल 16:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक kmb_ocs_aead_gcm_setauthsize(काष्ठा crypto_aead *tfm,
					अचिन्हित पूर्णांक authsize)
अणु
	वापस crypto_gcm_check_authsize(authsize);
पूर्ण

अटल पूर्णांक ocs_sm4_aead_cra_init(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा ocs_aes_tctx *tctx = crypto_aead_ctx(tfm);

	crypto_aead_set_reqsize(tfm, माप(काष्ठा ocs_aes_rctx));

	वापस ocs_common_aead_init(tctx);
पूर्ण

अटल व्योम ocs_aead_cra_निकास(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा ocs_aes_tctx *tctx = crypto_aead_ctx(tfm);

	clear_key(tctx);

	अगर (tctx->sw_cipher.aead) अणु
		crypto_मुक्त_aead(tctx->sw_cipher.aead);
		tctx->sw_cipher.aead = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा skcipher_alg algs[] = अणु
#अगर_घोषित CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_ECB
	अणु
		.base.cra_name = "ecb(aes)",
		.base.cra_driver_name = "ecb-aes-keembay-ocs",
		.base.cra_priority = KMB_OCS_PRIORITY,
		.base.cra_flags = CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_NEED_FALLBACK,
		.base.cra_blocksize = AES_BLOCK_SIZE,
		.base.cra_ctxsize = माप(काष्ठा ocs_aes_tctx),
		.base.cra_module = THIS_MODULE,
		.base.cra_alignmask = 0,

		.min_keysize = OCS_AES_MIN_KEY_SIZE,
		.max_keysize = OCS_AES_MAX_KEY_SIZE,
		.setkey = kmb_ocs_aes_set_key,
		.encrypt = kmb_ocs_aes_ecb_encrypt,
		.decrypt = kmb_ocs_aes_ecb_decrypt,
		.init = ocs_aes_init_tfm,
		.निकास = ocs_निकास_tfm,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_ECB */
	अणु
		.base.cra_name = "cbc(aes)",
		.base.cra_driver_name = "cbc-aes-keembay-ocs",
		.base.cra_priority = KMB_OCS_PRIORITY,
		.base.cra_flags = CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_NEED_FALLBACK,
		.base.cra_blocksize = AES_BLOCK_SIZE,
		.base.cra_ctxsize = माप(काष्ठा ocs_aes_tctx),
		.base.cra_module = THIS_MODULE,
		.base.cra_alignmask = 0,

		.min_keysize = OCS_AES_MIN_KEY_SIZE,
		.max_keysize = OCS_AES_MAX_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
		.setkey = kmb_ocs_aes_set_key,
		.encrypt = kmb_ocs_aes_cbc_encrypt,
		.decrypt = kmb_ocs_aes_cbc_decrypt,
		.init = ocs_aes_init_tfm,
		.निकास = ocs_निकास_tfm,
	पूर्ण,
	अणु
		.base.cra_name = "ctr(aes)",
		.base.cra_driver_name = "ctr-aes-keembay-ocs",
		.base.cra_priority = KMB_OCS_PRIORITY,
		.base.cra_flags = CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_NEED_FALLBACK,
		.base.cra_blocksize = 1,
		.base.cra_ctxsize = माप(काष्ठा ocs_aes_tctx),
		.base.cra_module = THIS_MODULE,
		.base.cra_alignmask = 0,

		.min_keysize = OCS_AES_MIN_KEY_SIZE,
		.max_keysize = OCS_AES_MAX_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
		.setkey = kmb_ocs_aes_set_key,
		.encrypt = kmb_ocs_aes_ctr_encrypt,
		.decrypt = kmb_ocs_aes_ctr_decrypt,
		.init = ocs_aes_init_tfm,
		.निकास = ocs_निकास_tfm,
	पूर्ण,
#अगर_घोषित CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_CTS
	अणु
		.base.cra_name = "cts(cbc(aes))",
		.base.cra_driver_name = "cts-aes-keembay-ocs",
		.base.cra_priority = KMB_OCS_PRIORITY,
		.base.cra_flags = CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_NEED_FALLBACK,
		.base.cra_blocksize = AES_BLOCK_SIZE,
		.base.cra_ctxsize = माप(काष्ठा ocs_aes_tctx),
		.base.cra_module = THIS_MODULE,
		.base.cra_alignmask = 0,

		.min_keysize = OCS_AES_MIN_KEY_SIZE,
		.max_keysize = OCS_AES_MAX_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
		.setkey = kmb_ocs_aes_set_key,
		.encrypt = kmb_ocs_aes_cts_encrypt,
		.decrypt = kmb_ocs_aes_cts_decrypt,
		.init = ocs_aes_init_tfm,
		.निकास = ocs_निकास_tfm,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_CTS */
#अगर_घोषित CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_ECB
	अणु
		.base.cra_name = "ecb(sm4)",
		.base.cra_driver_name = "ecb-sm4-keembay-ocs",
		.base.cra_priority = KMB_OCS_PRIORITY,
		.base.cra_flags = CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_KERN_DRIVER_ONLY,
		.base.cra_blocksize = AES_BLOCK_SIZE,
		.base.cra_ctxsize = माप(काष्ठा ocs_aes_tctx),
		.base.cra_module = THIS_MODULE,
		.base.cra_alignmask = 0,

		.min_keysize = OCS_SM4_KEY_SIZE,
		.max_keysize = OCS_SM4_KEY_SIZE,
		.setkey = kmb_ocs_sm4_set_key,
		.encrypt = kmb_ocs_sm4_ecb_encrypt,
		.decrypt = kmb_ocs_sm4_ecb_decrypt,
		.init = ocs_sm4_init_tfm,
		.निकास = ocs_निकास_tfm,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_ECB */
	अणु
		.base.cra_name = "cbc(sm4)",
		.base.cra_driver_name = "cbc-sm4-keembay-ocs",
		.base.cra_priority = KMB_OCS_PRIORITY,
		.base.cra_flags = CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_KERN_DRIVER_ONLY,
		.base.cra_blocksize = AES_BLOCK_SIZE,
		.base.cra_ctxsize = माप(काष्ठा ocs_aes_tctx),
		.base.cra_module = THIS_MODULE,
		.base.cra_alignmask = 0,

		.min_keysize = OCS_SM4_KEY_SIZE,
		.max_keysize = OCS_SM4_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
		.setkey = kmb_ocs_sm4_set_key,
		.encrypt = kmb_ocs_sm4_cbc_encrypt,
		.decrypt = kmb_ocs_sm4_cbc_decrypt,
		.init = ocs_sm4_init_tfm,
		.निकास = ocs_निकास_tfm,
	पूर्ण,
	अणु
		.base.cra_name = "ctr(sm4)",
		.base.cra_driver_name = "ctr-sm4-keembay-ocs",
		.base.cra_priority = KMB_OCS_PRIORITY,
		.base.cra_flags = CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_KERN_DRIVER_ONLY,
		.base.cra_blocksize = 1,
		.base.cra_ctxsize = माप(काष्ठा ocs_aes_tctx),
		.base.cra_module = THIS_MODULE,
		.base.cra_alignmask = 0,

		.min_keysize = OCS_SM4_KEY_SIZE,
		.max_keysize = OCS_SM4_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
		.setkey = kmb_ocs_sm4_set_key,
		.encrypt = kmb_ocs_sm4_ctr_encrypt,
		.decrypt = kmb_ocs_sm4_ctr_decrypt,
		.init = ocs_sm4_init_tfm,
		.निकास = ocs_निकास_tfm,
	पूर्ण,
#अगर_घोषित CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_CTS
	अणु
		.base.cra_name = "cts(cbc(sm4))",
		.base.cra_driver_name = "cts-sm4-keembay-ocs",
		.base.cra_priority = KMB_OCS_PRIORITY,
		.base.cra_flags = CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_KERN_DRIVER_ONLY,
		.base.cra_blocksize = AES_BLOCK_SIZE,
		.base.cra_ctxsize = माप(काष्ठा ocs_aes_tctx),
		.base.cra_module = THIS_MODULE,
		.base.cra_alignmask = 0,

		.min_keysize = OCS_SM4_KEY_SIZE,
		.max_keysize = OCS_SM4_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
		.setkey = kmb_ocs_sm4_set_key,
		.encrypt = kmb_ocs_sm4_cts_encrypt,
		.decrypt = kmb_ocs_sm4_cts_decrypt,
		.init = ocs_sm4_init_tfm,
		.निकास = ocs_निकास_tfm,
	पूर्ण
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_CTS */
पूर्ण;

अटल काष्ठा aead_alg algs_aead[] = अणु
	अणु
		.base = अणु
			.cra_name = "gcm(aes)",
			.cra_driver_name = "gcm-aes-keembay-ocs",
			.cra_priority = KMB_OCS_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_KERN_DRIVER_ONLY |
				     CRYPTO_ALG_NEED_FALLBACK,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा ocs_aes_tctx),
			.cra_alignmask = 0,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.init = ocs_aes_aead_cra_init,
		.निकास = ocs_aead_cra_निकास,
		.ivsize = GCM_AES_IV_SIZE,
		.maxauthsize = AES_BLOCK_SIZE,
		.setauthsize = kmb_ocs_aead_gcm_setauthsize,
		.setkey = kmb_ocs_aes_aead_set_key,
		.encrypt = kmb_ocs_aes_gcm_encrypt,
		.decrypt = kmb_ocs_aes_gcm_decrypt,
	पूर्ण,
	अणु
		.base = अणु
			.cra_name = "ccm(aes)",
			.cra_driver_name = "ccm-aes-keembay-ocs",
			.cra_priority = KMB_OCS_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_KERN_DRIVER_ONLY |
				     CRYPTO_ALG_NEED_FALLBACK,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा ocs_aes_tctx),
			.cra_alignmask = 0,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.init = ocs_aes_aead_cra_init,
		.निकास = ocs_aead_cra_निकास,
		.ivsize = AES_BLOCK_SIZE,
		.maxauthsize = AES_BLOCK_SIZE,
		.setauthsize = kmb_ocs_aead_ccm_setauthsize,
		.setkey = kmb_ocs_aes_aead_set_key,
		.encrypt = kmb_ocs_aes_ccm_encrypt,
		.decrypt = kmb_ocs_aes_ccm_decrypt,
	पूर्ण,
	अणु
		.base = अणु
			.cra_name = "gcm(sm4)",
			.cra_driver_name = "gcm-sm4-keembay-ocs",
			.cra_priority = KMB_OCS_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा ocs_aes_tctx),
			.cra_alignmask = 0,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.init = ocs_sm4_aead_cra_init,
		.निकास = ocs_aead_cra_निकास,
		.ivsize = GCM_AES_IV_SIZE,
		.maxauthsize = AES_BLOCK_SIZE,
		.setauthsize = kmb_ocs_aead_gcm_setauthsize,
		.setkey = kmb_ocs_sm4_aead_set_key,
		.encrypt = kmb_ocs_sm4_gcm_encrypt,
		.decrypt = kmb_ocs_sm4_gcm_decrypt,
	पूर्ण,
	अणु
		.base = अणु
			.cra_name = "ccm(sm4)",
			.cra_driver_name = "ccm-sm4-keembay-ocs",
			.cra_priority = KMB_OCS_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा ocs_aes_tctx),
			.cra_alignmask = 0,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.init = ocs_sm4_aead_cra_init,
		.निकास = ocs_aead_cra_निकास,
		.ivsize = AES_BLOCK_SIZE,
		.maxauthsize = AES_BLOCK_SIZE,
		.setauthsize = kmb_ocs_aead_ccm_setauthsize,
		.setkey = kmb_ocs_sm4_aead_set_key,
		.encrypt = kmb_ocs_sm4_ccm_encrypt,
		.decrypt = kmb_ocs_sm4_ccm_decrypt,
	पूर्ण
पूर्ण;

अटल व्योम unरेजिस्टर_aes_algs(काष्ठा ocs_aes_dev *aes_dev)
अणु
	crypto_unरेजिस्टर_aeads(algs_aead, ARRAY_SIZE(algs_aead));
	crypto_unरेजिस्टर_skciphers(algs, ARRAY_SIZE(algs));
पूर्ण

अटल पूर्णांक रेजिस्टर_aes_algs(काष्ठा ocs_aes_dev *aes_dev)
अणु
	पूर्णांक ret;

	/*
	 * If any algorithm fails to रेजिस्टर, all preceding algorithms that
	 * were successfully रेजिस्टरed will be स्वतःmatically unरेजिस्टरed.
	 */
	ret = crypto_रेजिस्टर_aeads(algs_aead, ARRAY_SIZE(algs_aead));
	अगर (ret)
		वापस ret;

	ret = crypto_रेजिस्टर_skciphers(algs, ARRAY_SIZE(algs));
	अगर (ret)
		crypto_unरेजिस्टर_aeads(algs_aead, ARRAY_SIZE(algs));

	वापस ret;
पूर्ण

/* Device tree driver match. */
अटल स्थिर काष्ठा of_device_id kmb_ocs_aes_of_match[] = अणु
	अणु
		.compatible = "intel,keembay-ocs-aes",
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक kmb_ocs_aes_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ocs_aes_dev *aes_dev;

	aes_dev = platक्रमm_get_drvdata(pdev);
	अगर (!aes_dev)
		वापस -ENODEV;

	unरेजिस्टर_aes_algs(aes_dev);

	spin_lock(&ocs_aes.lock);
	list_del(&aes_dev->list);
	spin_unlock(&ocs_aes.lock);

	crypto_engine_निकास(aes_dev->engine);

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_ocs_aes_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ocs_aes_dev *aes_dev;
	काष्ठा resource *aes_mem;
	पूर्णांक rc;

	aes_dev = devm_kzalloc(dev, माप(*aes_dev), GFP_KERNEL);
	अगर (!aes_dev)
		वापस -ENOMEM;

	aes_dev->dev = dev;

	platक्रमm_set_drvdata(pdev, aes_dev);

	rc = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (rc) अणु
		dev_err(dev, "Failed to set 32 bit dma mask %d\n", rc);
		वापस rc;
	पूर्ण

	/* Get base रेजिस्टर address. */
	aes_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!aes_mem) अणु
		dev_err(dev, "Could not retrieve io mem resource\n");
		वापस -ENODEV;
	पूर्ण

	aes_dev->base_reg = devm_ioremap_resource(&pdev->dev, aes_mem);
	अगर (IS_ERR(aes_dev->base_reg))
		वापस PTR_ERR(aes_dev->base_reg);

	/* Get and request IRQ */
	aes_dev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (aes_dev->irq < 0)
		वापस aes_dev->irq;

	rc = devm_request_thपढ़ोed_irq(dev, aes_dev->irq, ocs_aes_irq_handler,
				       शून्य, 0, "keembay-ocs-aes", aes_dev);
	अगर (rc < 0) अणु
		dev_err(dev, "Could not request IRQ\n");
		वापस rc;
	पूर्ण

	INIT_LIST_HEAD(&aes_dev->list);
	spin_lock(&ocs_aes.lock);
	list_add_tail(&aes_dev->list, &ocs_aes.dev_list);
	spin_unlock(&ocs_aes.lock);

	init_completion(&aes_dev->irq_completion);

	/* Initialize crypto engine */
	aes_dev->engine = crypto_engine_alloc_init(dev, true);
	अगर (!aes_dev->engine) अणु
		rc = -ENOMEM;
		जाओ list_del;
	पूर्ण

	rc = crypto_engine_start(aes_dev->engine);
	अगर (rc) अणु
		dev_err(dev, "Could not start crypto engine\n");
		जाओ cleanup;
	पूर्ण

	rc = रेजिस्टर_aes_algs(aes_dev);
	अगर (rc) अणु
		dev_err(dev,
			"Could not register OCS algorithms with Crypto API\n");
		जाओ cleanup;
	पूर्ण

	वापस 0;

cleanup:
	crypto_engine_निकास(aes_dev->engine);
list_del:
	spin_lock(&ocs_aes.lock);
	list_del(&aes_dev->list);
	spin_unlock(&ocs_aes.lock);

	वापस rc;
पूर्ण

/* The OCS driver is a platक्रमm device. */
अटल काष्ठा platक्रमm_driver kmb_ocs_aes_driver = अणु
	.probe = kmb_ocs_aes_probe,
	.हटाओ = kmb_ocs_aes_हटाओ,
	.driver = अणु
			.name = DRV_NAME,
			.of_match_table = kmb_ocs_aes_of_match,
		पूर्ण,
पूर्ण;

module_platक्रमm_driver(kmb_ocs_aes_driver);

MODULE_DESCRIPTION("Intel Keem Bay Offload and Crypto Subsystem (OCS) AES/SM4 Driver");
MODULE_LICENSE("GPL");

MODULE_ALIAS_CRYPTO("cbc-aes-keembay-ocs");
MODULE_ALIAS_CRYPTO("ctr-aes-keembay-ocs");
MODULE_ALIAS_CRYPTO("gcm-aes-keembay-ocs");
MODULE_ALIAS_CRYPTO("ccm-aes-keembay-ocs");

MODULE_ALIAS_CRYPTO("cbc-sm4-keembay-ocs");
MODULE_ALIAS_CRYPTO("ctr-sm4-keembay-ocs");
MODULE_ALIAS_CRYPTO("gcm-sm4-keembay-ocs");
MODULE_ALIAS_CRYPTO("ccm-sm4-keembay-ocs");

#अगर_घोषित CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_ECB
MODULE_ALIAS_CRYPTO("ecb-aes-keembay-ocs");
MODULE_ALIAS_CRYPTO("ecb-sm4-keembay-ocs");
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_ECB */

#अगर_घोषित CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_CTS
MODULE_ALIAS_CRYPTO("cts-aes-keembay-ocs");
MODULE_ALIAS_CRYPTO("cts-sm4-keembay-ocs");
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_KEEMBAY_OCS_AES_SM4_CTS */
