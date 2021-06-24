<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/gcm.h>
#समावेश <linux/rtnetlink.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश "cc_driver.h"
#समावेश "cc_buffer_mgr.h"
#समावेश "cc_aead.h"
#समावेश "cc_request_mgr.h"
#समावेश "cc_hash.h"
#समावेश "cc_sram_mgr.h"

#घोषणा ढाँचा_aead	ढाँचा_u.aead

#घोषणा MAX_AEAD_SETKEY_SEQ 12
#घोषणा MAX_AEAD_PROCESS_SEQ 23

#घोषणा MAX_HMAC_DIGEST_SIZE (SHA256_DIGEST_SIZE)
#घोषणा MAX_HMAC_BLOCK_SIZE (SHA256_BLOCK_SIZE)

#घोषणा MAX_NONCE_SIZE CTR_RFC3686_NONCE_SIZE

काष्ठा cc_aead_handle अणु
	u32 sram_workspace_addr;
	काष्ठा list_head aead_list;
पूर्ण;

काष्ठा cc_hmac_s अणु
	u8 *padded_authkey;
	u8 *ipad_opad; /* IPAD, OPAD*/
	dma_addr_t padded_authkey_dma_addr;
	dma_addr_t ipad_opad_dma_addr;
पूर्ण;

काष्ठा cc_xcbc_s अणु
	u8 *xcbc_keys; /* K1,K2,K3 */
	dma_addr_t xcbc_keys_dma_addr;
पूर्ण;

काष्ठा cc_aead_ctx अणु
	काष्ठा cc_drvdata *drvdata;
	u8 ctr_nonce[MAX_NONCE_SIZE]; /* used क्रम ctr3686 iv and aes ccm */
	u8 *enckey;
	dma_addr_t enckey_dma_addr;
	जोड़ अणु
		काष्ठा cc_hmac_s hmac;
		काष्ठा cc_xcbc_s xcbc;
	पूर्ण auth_state;
	अचिन्हित पूर्णांक enc_keylen;
	अचिन्हित पूर्णांक auth_keylen;
	अचिन्हित पूर्णांक authsize; /* Actual (reduced?) size of the MAC/ICv */
	अचिन्हित पूर्णांक hash_len;
	क्रमागत drv_cipher_mode cipher_mode;
	क्रमागत cc_flow_mode flow_mode;
	क्रमागत drv_hash_mode auth_mode;
पूर्ण;

अटल व्योम cc_aead_निकास(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	dev_dbg(dev, "Clearing context @%p for %s\n", crypto_aead_ctx(tfm),
		crypto_tfm_alg_name(&tfm->base));

	/* Unmap enckey buffer */
	अगर (ctx->enckey) अणु
		dma_मुक्त_coherent(dev, AES_MAX_KEY_SIZE, ctx->enckey,
				  ctx->enckey_dma_addr);
		dev_dbg(dev, "Freed enckey DMA buffer enckey_dma_addr=%pad\n",
			&ctx->enckey_dma_addr);
		ctx->enckey_dma_addr = 0;
		ctx->enckey = शून्य;
	पूर्ण

	अगर (ctx->auth_mode == DRV_HASH_XCBC_MAC) अणु /* XCBC authetication */
		काष्ठा cc_xcbc_s *xcbc = &ctx->auth_state.xcbc;

		अगर (xcbc->xcbc_keys) अणु
			dma_मुक्त_coherent(dev, CC_AES_128_BIT_KEY_SIZE * 3,
					  xcbc->xcbc_keys,
					  xcbc->xcbc_keys_dma_addr);
		पूर्ण
		dev_dbg(dev, "Freed xcbc_keys DMA buffer xcbc_keys_dma_addr=%pad\n",
			&xcbc->xcbc_keys_dma_addr);
		xcbc->xcbc_keys_dma_addr = 0;
		xcbc->xcbc_keys = शून्य;
	पूर्ण अन्यथा अगर (ctx->auth_mode != DRV_HASH_शून्य) अणु /* HMAC auth. */
		काष्ठा cc_hmac_s *hmac = &ctx->auth_state.hmac;

		अगर (hmac->ipad_opad) अणु
			dma_मुक्त_coherent(dev, 2 * MAX_HMAC_DIGEST_SIZE,
					  hmac->ipad_opad,
					  hmac->ipad_opad_dma_addr);
			dev_dbg(dev, "Freed ipad_opad DMA buffer ipad_opad_dma_addr=%pad\n",
				&hmac->ipad_opad_dma_addr);
			hmac->ipad_opad_dma_addr = 0;
			hmac->ipad_opad = शून्य;
		पूर्ण
		अगर (hmac->padded_authkey) अणु
			dma_मुक्त_coherent(dev, MAX_HMAC_BLOCK_SIZE,
					  hmac->padded_authkey,
					  hmac->padded_authkey_dma_addr);
			dev_dbg(dev, "Freed padded_authkey DMA buffer padded_authkey_dma_addr=%pad\n",
				&hmac->padded_authkey_dma_addr);
			hmac->padded_authkey_dma_addr = 0;
			hmac->padded_authkey = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक cc_get_aead_hash_len(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);

	वापस cc_get_शेष_hash_len(ctx->drvdata);
पूर्ण

अटल पूर्णांक cc_aead_init(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_alg *alg = crypto_aead_alg(tfm);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा cc_crypto_alg *cc_alg =
			container_of(alg, काष्ठा cc_crypto_alg, aead_alg);
	काष्ठा device *dev = drvdata_to_dev(cc_alg->drvdata);

	dev_dbg(dev, "Initializing context @%p for %s\n", ctx,
		crypto_tfm_alg_name(&tfm->base));

	/* Initialize modes in instance */
	ctx->cipher_mode = cc_alg->cipher_mode;
	ctx->flow_mode = cc_alg->flow_mode;
	ctx->auth_mode = cc_alg->auth_mode;
	ctx->drvdata = cc_alg->drvdata;
	crypto_aead_set_reqsize(tfm, माप(काष्ठा aead_req_ctx));

	/* Allocate key buffer, cache line aligned */
	ctx->enckey = dma_alloc_coherent(dev, AES_MAX_KEY_SIZE,
					 &ctx->enckey_dma_addr, GFP_KERNEL);
	अगर (!ctx->enckey) अणु
		dev_err(dev, "Failed allocating key buffer\n");
		जाओ init_failed;
	पूर्ण
	dev_dbg(dev, "Allocated enckey buffer in context ctx->enckey=@%p\n",
		ctx->enckey);

	/* Set शेष authlen value */

	अगर (ctx->auth_mode == DRV_HASH_XCBC_MAC) अणु /* XCBC authetication */
		काष्ठा cc_xcbc_s *xcbc = &ctx->auth_state.xcbc;
		स्थिर अचिन्हित पूर्णांक key_size = CC_AES_128_BIT_KEY_SIZE * 3;

		/* Allocate dma-coherent buffer क्रम XCBC's K1+K2+K3 */
		/* (and temporary क्रम user key - up to 256b) */
		xcbc->xcbc_keys = dma_alloc_coherent(dev, key_size,
						     &xcbc->xcbc_keys_dma_addr,
						     GFP_KERNEL);
		अगर (!xcbc->xcbc_keys) अणु
			dev_err(dev, "Failed allocating buffer for XCBC keys\n");
			जाओ init_failed;
		पूर्ण
	पूर्ण अन्यथा अगर (ctx->auth_mode != DRV_HASH_शून्य) अणु /* HMAC authentication */
		काष्ठा cc_hmac_s *hmac = &ctx->auth_state.hmac;
		स्थिर अचिन्हित पूर्णांक digest_size = 2 * MAX_HMAC_DIGEST_SIZE;
		dma_addr_t *pkey_dma = &hmac->padded_authkey_dma_addr;

		/* Allocate dma-coherent buffer क्रम IPAD + OPAD */
		hmac->ipad_opad = dma_alloc_coherent(dev, digest_size,
						     &hmac->ipad_opad_dma_addr,
						     GFP_KERNEL);

		अगर (!hmac->ipad_opad) अणु
			dev_err(dev, "Failed allocating IPAD/OPAD buffer\n");
			जाओ init_failed;
		पूर्ण

		dev_dbg(dev, "Allocated authkey buffer in context ctx->authkey=@%p\n",
			hmac->ipad_opad);

		hmac->padded_authkey = dma_alloc_coherent(dev,
							  MAX_HMAC_BLOCK_SIZE,
							  pkey_dma,
							  GFP_KERNEL);

		अगर (!hmac->padded_authkey) अणु
			dev_err(dev, "failed to allocate padded_authkey\n");
			जाओ init_failed;
		पूर्ण
	पूर्ण अन्यथा अणु
		ctx->auth_state.hmac.ipad_opad = शून्य;
		ctx->auth_state.hmac.padded_authkey = शून्य;
	पूर्ण
	ctx->hash_len = cc_get_aead_hash_len(tfm);

	वापस 0;

init_failed:
	cc_aead_निकास(tfm);
	वापस -ENOMEM;
पूर्ण

अटल व्योम cc_aead_complete(काष्ठा device *dev, व्योम *cc_req, पूर्णांक err)
अणु
	काष्ठा aead_request *areq = (काष्ठा aead_request *)cc_req;
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(areq);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(cc_req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);

	/* BACKLOG notअगरication */
	अगर (err == -EINPROGRESS)
		जाओ करोne;

	cc_unmap_aead_request(dev, areq);

	/* Restore ordinary iv poपूर्णांकer */
	areq->iv = areq_ctx->backup_iv;

	अगर (err)
		जाओ करोne;

	अगर (areq_ctx->gen_ctx.op_type == DRV_CRYPTO_सूचीECTION_DECRYPT) अणु
		अगर (स_भेद(areq_ctx->mac_buf, areq_ctx->icv_virt_addr,
			   ctx->authsize) != 0) अणु
			dev_dbg(dev, "Payload authentication failure, (auth-size=%d, cipher=%d)\n",
				ctx->authsize, ctx->cipher_mode);
			/* In हाल of payload authentication failure, MUST NOT
			 * revealed the decrypted message --> zero its memory.
			 */
			sg_zero_buffer(areq->dst, sg_nents(areq->dst),
				       areq->cryptlen, areq->assoclen);
			err = -EBADMSG;
		पूर्ण
	/*ENCRYPT*/
	पूर्ण अन्यथा अगर (areq_ctx->is_icv_fragmented) अणु
		u32 skip = areq->cryptlen + areq_ctx->dst_offset;

		cc_copy_sg_portion(dev, areq_ctx->mac_buf, areq_ctx->dst_sgl,
				   skip, (skip + ctx->authsize),
				   CC_SG_FROM_BUF);
	पूर्ण
करोne:
	aead_request_complete(areq, err);
पूर्ण

अटल अचिन्हित पूर्णांक xcbc_setkey(काष्ठा cc_hw_desc *desc,
				काष्ठा cc_aead_ctx *ctx)
अणु
	/* Load the AES key */
	hw_desc_init(&desc[0]);
	/* We are using क्रम the source/user key the same buffer
	 * as क्रम the output keys, * because after this key loading it
	 * is not needed anymore
	 */
	set_din_type(&desc[0], DMA_DLLI,
		     ctx->auth_state.xcbc.xcbc_keys_dma_addr, ctx->auth_keylen,
		     NS_BIT);
	set_cipher_mode(&desc[0], DRV_CIPHER_ECB);
	set_cipher_config0(&desc[0], DRV_CRYPTO_सूचीECTION_ENCRYPT);
	set_key_size_aes(&desc[0], ctx->auth_keylen);
	set_flow_mode(&desc[0], S_DIN_to_AES);
	set_setup_mode(&desc[0], SETUP_LOAD_KEY0);

	hw_desc_init(&desc[1]);
	set_din_स्थिर(&desc[1], 0x01010101, CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[1], DIN_AES_DOUT);
	set_करोut_dlli(&desc[1], ctx->auth_state.xcbc.xcbc_keys_dma_addr,
		      AES_KEYSIZE_128, NS_BIT, 0);

	hw_desc_init(&desc[2]);
	set_din_स्थिर(&desc[2], 0x02020202, CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[2], DIN_AES_DOUT);
	set_करोut_dlli(&desc[2], (ctx->auth_state.xcbc.xcbc_keys_dma_addr
					 + AES_KEYSIZE_128),
			      AES_KEYSIZE_128, NS_BIT, 0);

	hw_desc_init(&desc[3]);
	set_din_स्थिर(&desc[3], 0x03030303, CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[3], DIN_AES_DOUT);
	set_करोut_dlli(&desc[3], (ctx->auth_state.xcbc.xcbc_keys_dma_addr
					  + 2 * AES_KEYSIZE_128),
			      AES_KEYSIZE_128, NS_BIT, 0);

	वापस 4;
पूर्ण

अटल अचिन्हित पूर्णांक hmac_setkey(काष्ठा cc_hw_desc *desc,
				काष्ठा cc_aead_ctx *ctx)
अणु
	अचिन्हित पूर्णांक hmac_pad_स्थिर[2] = अणु HMAC_IPAD_CONST, HMAC_OPAD_CONST पूर्ण;
	अचिन्हित पूर्णांक digest_ofs = 0;
	अचिन्हित पूर्णांक hash_mode = (ctx->auth_mode == DRV_HASH_SHA1) ?
			DRV_HASH_HW_SHA1 : DRV_HASH_HW_SHA256;
	अचिन्हित पूर्णांक digest_size = (ctx->auth_mode == DRV_HASH_SHA1) ?
			CC_SHA1_DIGEST_SIZE : CC_SHA256_DIGEST_SIZE;
	काष्ठा cc_hmac_s *hmac = &ctx->auth_state.hmac;

	अचिन्हित पूर्णांक idx = 0;
	पूर्णांक i;

	/* calc derived HMAC key */
	क्रम (i = 0; i < 2; i++) अणु
		/* Load hash initial state */
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], hash_mode);
		set_din_sram(&desc[idx],
			     cc_larval_digest_addr(ctx->drvdata,
						   ctx->auth_mode),
			     digest_size);
		set_flow_mode(&desc[idx], S_DIN_to_HASH);
		set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
		idx++;

		/* Load the hash current length*/
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], hash_mode);
		set_din_स्थिर(&desc[idx], 0, ctx->hash_len);
		set_flow_mode(&desc[idx], S_DIN_to_HASH);
		set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
		idx++;

		/* Prepare ipad key */
		hw_desc_init(&desc[idx]);
		set_xor_val(&desc[idx], hmac_pad_स्थिर[i]);
		set_cipher_mode(&desc[idx], hash_mode);
		set_flow_mode(&desc[idx], S_DIN_to_HASH);
		set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
		idx++;

		/* Perक्रमm HASH update */
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DLLI,
			     hmac->padded_authkey_dma_addr,
			     SHA256_BLOCK_SIZE, NS_BIT);
		set_cipher_mode(&desc[idx], hash_mode);
		set_xor_active(&desc[idx]);
		set_flow_mode(&desc[idx], DIN_HASH);
		idx++;

		/* Get the digset */
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], hash_mode);
		set_करोut_dlli(&desc[idx],
			      (hmac->ipad_opad_dma_addr + digest_ofs),
			      digest_size, NS_BIT, 0);
		set_flow_mode(&desc[idx], S_HASH_to_DOUT);
		set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
		set_cipher_config1(&desc[idx], HASH_PADDING_DISABLED);
		idx++;

		digest_ofs += digest_size;
	पूर्ण

	वापस idx;
पूर्ण

अटल पूर्णांक validate_keys_sizes(काष्ठा cc_aead_ctx *ctx)
अणु
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	dev_dbg(dev, "enc_keylen=%u  authkeylen=%u\n",
		ctx->enc_keylen, ctx->auth_keylen);

	चयन (ctx->auth_mode) अणु
	हाल DRV_HASH_SHA1:
	हाल DRV_HASH_SHA256:
		अवरोध;
	हाल DRV_HASH_XCBC_MAC:
		अगर (ctx->auth_keylen != AES_KEYSIZE_128 &&
		    ctx->auth_keylen != AES_KEYSIZE_192 &&
		    ctx->auth_keylen != AES_KEYSIZE_256)
			वापस -ENOTSUPP;
		अवरोध;
	हाल DRV_HASH_शून्य: /* Not authenc (e.g., CCM) - no auth_key) */
		अगर (ctx->auth_keylen > 0)
			वापस -EINVAL;
		अवरोध;
	शेष:
		dev_dbg(dev, "Invalid auth_mode=%d\n", ctx->auth_mode);
		वापस -EINVAL;
	पूर्ण
	/* Check cipher key size */
	अगर (ctx->flow_mode == S_DIN_to_DES) अणु
		अगर (ctx->enc_keylen != DES3_EDE_KEY_SIZE) अणु
			dev_dbg(dev, "Invalid cipher(3DES) key size: %u\n",
				ctx->enc_keylen);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु /* Default assumed to be AES ciphers */
		अगर (ctx->enc_keylen != AES_KEYSIZE_128 &&
		    ctx->enc_keylen != AES_KEYSIZE_192 &&
		    ctx->enc_keylen != AES_KEYSIZE_256) अणु
			dev_dbg(dev, "Invalid cipher(AES) key size: %u\n",
				ctx->enc_keylen);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0; /* All tests of keys sizes passed */
पूर्ण

/* This function prepers the user key so it can pass to the hmac processing
 * (copy to पूर्णांकenral buffer or hash in हाल of key दीर्घer than block
 */
अटल पूर्णांक cc_get_plain_hmac_key(काष्ठा crypto_aead *tfm, स्थिर u8 *authkey,
				 अचिन्हित पूर्णांक keylen)
अणु
	dma_addr_t key_dma_addr = 0;
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	u32 larval_addr;
	काष्ठा cc_crypto_req cc_req = अणुपूर्ण;
	अचिन्हित पूर्णांक blocksize;
	अचिन्हित पूर्णांक digestsize;
	अचिन्हित पूर्णांक hashmode;
	अचिन्हित पूर्णांक idx = 0;
	पूर्णांक rc = 0;
	u8 *key = शून्य;
	काष्ठा cc_hw_desc desc[MAX_AEAD_SETKEY_SEQ];
	dma_addr_t padded_authkey_dma_addr =
		ctx->auth_state.hmac.padded_authkey_dma_addr;

	चयन (ctx->auth_mode) अणु /* auth_key required and >0 */
	हाल DRV_HASH_SHA1:
		blocksize = SHA1_BLOCK_SIZE;
		digestsize = SHA1_DIGEST_SIZE;
		hashmode = DRV_HASH_HW_SHA1;
		अवरोध;
	हाल DRV_HASH_SHA256:
	शेष:
		blocksize = SHA256_BLOCK_SIZE;
		digestsize = SHA256_DIGEST_SIZE;
		hashmode = DRV_HASH_HW_SHA256;
	पूर्ण

	अगर (keylen != 0) अणु

		key = kmemdup(authkey, keylen, GFP_KERNEL);
		अगर (!key)
			वापस -ENOMEM;

		key_dma_addr = dma_map_single(dev, key, keylen, DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, key_dma_addr)) अणु
			dev_err(dev, "Mapping key va=0x%p len=%u for DMA failed\n",
				key, keylen);
			kमुक्त_sensitive(key);
			वापस -ENOMEM;
		पूर्ण
		अगर (keylen > blocksize) अणु
			/* Load hash initial state */
			hw_desc_init(&desc[idx]);
			set_cipher_mode(&desc[idx], hashmode);
			larval_addr = cc_larval_digest_addr(ctx->drvdata,
							    ctx->auth_mode);
			set_din_sram(&desc[idx], larval_addr, digestsize);
			set_flow_mode(&desc[idx], S_DIN_to_HASH);
			set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
			idx++;

			/* Load the hash current length*/
			hw_desc_init(&desc[idx]);
			set_cipher_mode(&desc[idx], hashmode);
			set_din_स्थिर(&desc[idx], 0, ctx->hash_len);
			set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
			set_flow_mode(&desc[idx], S_DIN_to_HASH);
			set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
			idx++;

			hw_desc_init(&desc[idx]);
			set_din_type(&desc[idx], DMA_DLLI,
				     key_dma_addr, keylen, NS_BIT);
			set_flow_mode(&desc[idx], DIN_HASH);
			idx++;

			/* Get hashed key */
			hw_desc_init(&desc[idx]);
			set_cipher_mode(&desc[idx], hashmode);
			set_करोut_dlli(&desc[idx], padded_authkey_dma_addr,
				      digestsize, NS_BIT, 0);
			set_flow_mode(&desc[idx], S_HASH_to_DOUT);
			set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
			set_cipher_config1(&desc[idx], HASH_PADDING_DISABLED);
			set_cipher_config0(&desc[idx],
					   HASH_DIGEST_RESULT_LITTLE_ENDIAN);
			idx++;

			hw_desc_init(&desc[idx]);
			set_din_स्थिर(&desc[idx], 0, (blocksize - digestsize));
			set_flow_mode(&desc[idx], BYPASS);
			set_करोut_dlli(&desc[idx], (padded_authkey_dma_addr +
				      digestsize), (blocksize - digestsize),
				      NS_BIT, 0);
			idx++;
		पूर्ण अन्यथा अणु
			hw_desc_init(&desc[idx]);
			set_din_type(&desc[idx], DMA_DLLI, key_dma_addr,
				     keylen, NS_BIT);
			set_flow_mode(&desc[idx], BYPASS);
			set_करोut_dlli(&desc[idx], padded_authkey_dma_addr,
				      keylen, NS_BIT, 0);
			idx++;

			अगर ((blocksize - keylen) != 0) अणु
				hw_desc_init(&desc[idx]);
				set_din_स्थिर(&desc[idx], 0,
					      (blocksize - keylen));
				set_flow_mode(&desc[idx], BYPASS);
				set_करोut_dlli(&desc[idx],
					      (padded_authkey_dma_addr +
					       keylen),
					      (blocksize - keylen), NS_BIT, 0);
				idx++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		hw_desc_init(&desc[idx]);
		set_din_स्थिर(&desc[idx], 0, (blocksize - keylen));
		set_flow_mode(&desc[idx], BYPASS);
		set_करोut_dlli(&desc[idx], padded_authkey_dma_addr,
			      blocksize, NS_BIT, 0);
		idx++;
	पूर्ण

	rc = cc_send_sync_request(ctx->drvdata, &cc_req, desc, idx);
	अगर (rc)
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);

	अगर (key_dma_addr)
		dma_unmap_single(dev, key_dma_addr, keylen, DMA_TO_DEVICE);

	kमुक्त_sensitive(key);

	वापस rc;
पूर्ण

अटल पूर्णांक cc_aead_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			  अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा cc_crypto_req cc_req = अणुपूर्ण;
	काष्ठा cc_hw_desc desc[MAX_AEAD_SETKEY_SEQ];
	अचिन्हित पूर्णांक seq_len = 0;
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	स्थिर u8 *enckey, *authkey;
	पूर्णांक rc;

	dev_dbg(dev, "Setting key in context @%p for %s. key=%p keylen=%u\n",
		ctx, crypto_tfm_alg_name(crypto_aead_tfm(tfm)), key, keylen);

	/* STAT_PHASE_0: Init and sanity checks */

	अगर (ctx->auth_mode != DRV_HASH_शून्य) अणु /* authenc() alg. */
		काष्ठा crypto_authenc_keys keys;

		rc = crypto_authenc_extractkeys(&keys, key, keylen);
		अगर (rc)
			वापस rc;
		enckey = keys.enckey;
		authkey = keys.authkey;
		ctx->enc_keylen = keys.enckeylen;
		ctx->auth_keylen = keys.authkeylen;

		अगर (ctx->cipher_mode == DRV_CIPHER_CTR) अणु
			/* the nonce is stored in bytes at end of key */
			अगर (ctx->enc_keylen <
			    (AES_MIN_KEY_SIZE + CTR_RFC3686_NONCE_SIZE))
				वापस -EINVAL;
			/* Copy nonce from last 4 bytes in CTR key to
			 *  first 4 bytes in CTR IV
			 */
			स_नकल(ctx->ctr_nonce, enckey + ctx->enc_keylen -
			       CTR_RFC3686_NONCE_SIZE, CTR_RFC3686_NONCE_SIZE);
			/* Set CTR key size */
			ctx->enc_keylen -= CTR_RFC3686_NONCE_SIZE;
		पूर्ण
	पूर्ण अन्यथा अणु /* non-authenc - has just one key */
		enckey = key;
		authkey = शून्य;
		ctx->enc_keylen = keylen;
		ctx->auth_keylen = 0;
	पूर्ण

	rc = validate_keys_sizes(ctx);
	अगर (rc)
		वापस rc;

	/* STAT_PHASE_1: Copy key to ctx */

	/* Get key material */
	स_नकल(ctx->enckey, enckey, ctx->enc_keylen);
	अगर (ctx->enc_keylen == 24)
		स_रखो(ctx->enckey + 24, 0, CC_AES_KEY_SIZE_MAX - 24);
	अगर (ctx->auth_mode == DRV_HASH_XCBC_MAC) अणु
		स_नकल(ctx->auth_state.xcbc.xcbc_keys, authkey,
		       ctx->auth_keylen);
	पूर्ण अन्यथा अगर (ctx->auth_mode != DRV_HASH_शून्य) अणु /* HMAC */
		rc = cc_get_plain_hmac_key(tfm, authkey, ctx->auth_keylen);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* STAT_PHASE_2: Create sequence */

	चयन (ctx->auth_mode) अणु
	हाल DRV_HASH_SHA1:
	हाल DRV_HASH_SHA256:
		seq_len = hmac_setkey(desc, ctx);
		अवरोध;
	हाल DRV_HASH_XCBC_MAC:
		seq_len = xcbc_setkey(desc, ctx);
		अवरोध;
	हाल DRV_HASH_शून्य: /* non-authenc modes, e.g., CCM */
		अवरोध; /* No auth. key setup */
	शेष:
		dev_err(dev, "Unsupported authenc (%d)\n", ctx->auth_mode);
		वापस -ENOTSUPP;
	पूर्ण

	/* STAT_PHASE_3: Submit sequence to HW */

	अगर (seq_len > 0) अणु /* For CCM there is no sequence to setup the key */
		rc = cc_send_sync_request(ctx->drvdata, &cc_req, desc, seq_len);
		अगर (rc) अणु
			dev_err(dev, "send_request() failed (rc=%d)\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण

	/* Update STAT_PHASE_3 */
	वापस rc;
पूर्ण

अटल पूर्णांक cc_des3_aead_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
			       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_authenc_keys keys;
	पूर्णांक err;

	err = crypto_authenc_extractkeys(&keys, key, keylen);
	अगर (unlikely(err))
		वापस err;

	err = verअगरy_aead_des3_key(aead, keys.enckey, keys.enckeylen) ?:
	      cc_aead_setkey(aead, key, keylen);

	memzero_explicit(&keys, माप(keys));
	वापस err;
पूर्ण

अटल पूर्णांक cc_rfc4309_ccm_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);

	अगर (keylen < 3)
		वापस -EINVAL;

	keylen -= 3;
	स_नकल(ctx->ctr_nonce, key + keylen, 3);

	वापस cc_aead_setkey(tfm, key, keylen);
पूर्ण

अटल पूर्णांक cc_aead_setauthsize(काष्ठा crypto_aead *authenc,
			       अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(authenc);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	/* Unsupported auth. sizes */
	अगर (authsize == 0 ||
	    authsize > crypto_aead_maxauthsize(authenc)) अणु
		वापस -ENOTSUPP;
	पूर्ण

	ctx->authsize = authsize;
	dev_dbg(dev, "authlen=%d\n", ctx->authsize);

	वापस 0;
पूर्ण

अटल पूर्णांक cc_rfc4309_ccm_setauthsize(काष्ठा crypto_aead *authenc,
				      अचिन्हित पूर्णांक authsize)
अणु
	चयन (authsize) अणु
	हाल 8:
	हाल 12:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस cc_aead_setauthsize(authenc, authsize);
पूर्ण

अटल पूर्णांक cc_ccm_setauthsize(काष्ठा crypto_aead *authenc,
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
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस cc_aead_setauthsize(authenc, authsize);
पूर्ण

अटल व्योम cc_set_assoc_desc(काष्ठा aead_request *areq, अचिन्हित पूर्णांक flow_mode,
			      काष्ठा cc_hw_desc desc[], अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(areq);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(areq);
	क्रमागत cc_req_dma_buf_type assoc_dma_type = areq_ctx->assoc_buff_type;
	अचिन्हित पूर्णांक idx = *seq_size;
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	चयन (assoc_dma_type) अणु
	हाल CC_DMA_BUF_DLLI:
		dev_dbg(dev, "ASSOC buffer type DLLI\n");
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DLLI, sg_dma_address(areq->src),
			     areq_ctx->assoclen, NS_BIT);
		set_flow_mode(&desc[idx], flow_mode);
		अगर (ctx->auth_mode == DRV_HASH_XCBC_MAC &&
		    areq_ctx->cryptlen > 0)
			set_din_not_last_indication(&desc[idx]);
		अवरोध;
	हाल CC_DMA_BUF_MLLI:
		dev_dbg(dev, "ASSOC buffer type MLLI\n");
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_MLLI, areq_ctx->assoc.sram_addr,
			     areq_ctx->assoc.mlli_nents, NS_BIT);
		set_flow_mode(&desc[idx], flow_mode);
		अगर (ctx->auth_mode == DRV_HASH_XCBC_MAC &&
		    areq_ctx->cryptlen > 0)
			set_din_not_last_indication(&desc[idx]);
		अवरोध;
	हाल CC_DMA_BUF_शून्य:
	शेष:
		dev_err(dev, "Invalid ASSOC buffer type\n");
	पूर्ण

	*seq_size = (++idx);
पूर्ण

अटल व्योम cc_proc_authen_desc(काष्ठा aead_request *areq,
				अचिन्हित पूर्णांक flow_mode,
				काष्ठा cc_hw_desc desc[],
				अचिन्हित पूर्णांक *seq_size, पूर्णांक direct)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(areq);
	क्रमागत cc_req_dma_buf_type data_dma_type = areq_ctx->data_buff_type;
	अचिन्हित पूर्णांक idx = *seq_size;
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(areq);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	चयन (data_dma_type) अणु
	हाल CC_DMA_BUF_DLLI:
	अणु
		काष्ठा scatterlist *cipher =
			(direct == DRV_CRYPTO_सूचीECTION_ENCRYPT) ?
			areq_ctx->dst_sgl : areq_ctx->src_sgl;

		अचिन्हित पूर्णांक offset =
			(direct == DRV_CRYPTO_सूचीECTION_ENCRYPT) ?
			areq_ctx->dst_offset : areq_ctx->src_offset;
		dev_dbg(dev, "AUTHENC: SRC/DST buffer type DLLI\n");
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DLLI,
			     (sg_dma_address(cipher) + offset),
			     areq_ctx->cryptlen, NS_BIT);
		set_flow_mode(&desc[idx], flow_mode);
		अवरोध;
	पूर्ण
	हाल CC_DMA_BUF_MLLI:
	अणु
		/* DOUBLE-PASS flow (as शेष)
		 * assoc. + iv + data -compact in one table
		 * अगर assoclen is ZERO only IV perक्रमm
		 */
		u32 mlli_addr = areq_ctx->assoc.sram_addr;
		u32 mlli_nents = areq_ctx->assoc.mlli_nents;

		अगर (areq_ctx->is_single_pass) अणु
			अगर (direct == DRV_CRYPTO_सूचीECTION_ENCRYPT) अणु
				mlli_addr = areq_ctx->dst.sram_addr;
				mlli_nents = areq_ctx->dst.mlli_nents;
			पूर्ण अन्यथा अणु
				mlli_addr = areq_ctx->src.sram_addr;
				mlli_nents = areq_ctx->src.mlli_nents;
			पूर्ण
		पूर्ण

		dev_dbg(dev, "AUTHENC: SRC/DST buffer type MLLI\n");
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_MLLI, mlli_addr, mlli_nents,
			     NS_BIT);
		set_flow_mode(&desc[idx], flow_mode);
		अवरोध;
	पूर्ण
	हाल CC_DMA_BUF_शून्य:
	शेष:
		dev_err(dev, "AUTHENC: Invalid SRC/DST buffer type\n");
	पूर्ण

	*seq_size = (++idx);
पूर्ण

अटल व्योम cc_proc_cipher_desc(काष्ठा aead_request *areq,
				अचिन्हित पूर्णांक flow_mode,
				काष्ठा cc_hw_desc desc[],
				अचिन्हित पूर्णांक *seq_size)
अणु
	अचिन्हित पूर्णांक idx = *seq_size;
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(areq);
	क्रमागत cc_req_dma_buf_type data_dma_type = areq_ctx->data_buff_type;
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(areq);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	अगर (areq_ctx->cryptlen == 0)
		वापस; /*null processing*/

	चयन (data_dma_type) अणु
	हाल CC_DMA_BUF_DLLI:
		dev_dbg(dev, "CIPHER: SRC/DST buffer type DLLI\n");
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DLLI,
			     (sg_dma_address(areq_ctx->src_sgl) +
			      areq_ctx->src_offset), areq_ctx->cryptlen,
			      NS_BIT);
		set_करोut_dlli(&desc[idx],
			      (sg_dma_address(areq_ctx->dst_sgl) +
			       areq_ctx->dst_offset),
			      areq_ctx->cryptlen, NS_BIT, 0);
		set_flow_mode(&desc[idx], flow_mode);
		अवरोध;
	हाल CC_DMA_BUF_MLLI:
		dev_dbg(dev, "CIPHER: SRC/DST buffer type MLLI\n");
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_MLLI, areq_ctx->src.sram_addr,
			     areq_ctx->src.mlli_nents, NS_BIT);
		set_करोut_mlli(&desc[idx], areq_ctx->dst.sram_addr,
			      areq_ctx->dst.mlli_nents, NS_BIT, 0);
		set_flow_mode(&desc[idx], flow_mode);
		अवरोध;
	हाल CC_DMA_BUF_शून्य:
	शेष:
		dev_err(dev, "CIPHER: Invalid SRC/DST buffer type\n");
	पूर्ण

	*seq_size = (++idx);
पूर्ण

अटल व्योम cc_proc_digest_desc(काष्ठा aead_request *req,
				काष्ठा cc_hw_desc desc[],
				अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_req_ctx *req_ctx = aead_request_ctx(req);
	अचिन्हित पूर्णांक idx = *seq_size;
	अचिन्हित पूर्णांक hash_mode = (ctx->auth_mode == DRV_HASH_SHA1) ?
				DRV_HASH_HW_SHA1 : DRV_HASH_HW_SHA256;
	पूर्णांक direct = req_ctx->gen_ctx.op_type;

	/* Get final ICV result */
	अगर (direct == DRV_CRYPTO_सूचीECTION_ENCRYPT) अणु
		hw_desc_init(&desc[idx]);
		set_flow_mode(&desc[idx], S_HASH_to_DOUT);
		set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
		set_करोut_dlli(&desc[idx], req_ctx->icv_dma_addr, ctx->authsize,
			      NS_BIT, 1);
		set_queue_last_ind(ctx->drvdata, &desc[idx]);
		अगर (ctx->auth_mode == DRV_HASH_XCBC_MAC) अणु
			set_aes_not_hash_mode(&desc[idx]);
			set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
		पूर्ण अन्यथा अणु
			set_cipher_config0(&desc[idx],
					   HASH_DIGEST_RESULT_LITTLE_ENDIAN);
			set_cipher_mode(&desc[idx], hash_mode);
		पूर्ण
	पूर्ण अन्यथा अणु /*Decrypt*/
		/* Get ICV out from hardware */
		hw_desc_init(&desc[idx]);
		set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
		set_flow_mode(&desc[idx], S_HASH_to_DOUT);
		set_करोut_dlli(&desc[idx], req_ctx->mac_buf_dma_addr,
			      ctx->authsize, NS_BIT, 1);
		set_queue_last_ind(ctx->drvdata, &desc[idx]);
		set_cipher_config0(&desc[idx],
				   HASH_DIGEST_RESULT_LITTLE_ENDIAN);
		set_cipher_config1(&desc[idx], HASH_PADDING_DISABLED);
		अगर (ctx->auth_mode == DRV_HASH_XCBC_MAC) अणु
			set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
			set_aes_not_hash_mode(&desc[idx]);
		पूर्ण अन्यथा अणु
			set_cipher_mode(&desc[idx], hash_mode);
		पूर्ण
	पूर्ण

	*seq_size = (++idx);
पूर्ण

अटल व्योम cc_set_cipher_desc(काष्ठा aead_request *req,
			       काष्ठा cc_hw_desc desc[],
			       अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_req_ctx *req_ctx = aead_request_ctx(req);
	अचिन्हित पूर्णांक hw_iv_size = req_ctx->hw_iv_size;
	अचिन्हित पूर्णांक idx = *seq_size;
	पूर्णांक direct = req_ctx->gen_ctx.op_type;

	/* Setup cipher state */
	hw_desc_init(&desc[idx]);
	set_cipher_config0(&desc[idx], direct);
	set_flow_mode(&desc[idx], ctx->flow_mode);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->gen_ctx.iv_dma_addr,
		     hw_iv_size, NS_BIT);
	अगर (ctx->cipher_mode == DRV_CIPHER_CTR)
		set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
	अन्यथा
		set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	set_cipher_mode(&desc[idx], ctx->cipher_mode);
	idx++;

	/* Setup enc. key */
	hw_desc_init(&desc[idx]);
	set_cipher_config0(&desc[idx], direct);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_flow_mode(&desc[idx], ctx->flow_mode);
	अगर (ctx->flow_mode == S_DIN_to_AES) अणु
		set_din_type(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr,
			     ((ctx->enc_keylen == 24) ? CC_AES_KEY_SIZE_MAX :
			      ctx->enc_keylen), NS_BIT);
		set_key_size_aes(&desc[idx], ctx->enc_keylen);
	पूर्ण अन्यथा अणु
		set_din_type(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr,
			     ctx->enc_keylen, NS_BIT);
		set_key_size_des(&desc[idx], ctx->enc_keylen);
	पूर्ण
	set_cipher_mode(&desc[idx], ctx->cipher_mode);
	idx++;

	*seq_size = idx;
पूर्ण

अटल व्योम cc_proc_cipher(काष्ठा aead_request *req, काष्ठा cc_hw_desc desc[],
			   अचिन्हित पूर्णांक *seq_size, अचिन्हित पूर्णांक data_flow_mode)
अणु
	काष्ठा aead_req_ctx *req_ctx = aead_request_ctx(req);
	पूर्णांक direct = req_ctx->gen_ctx.op_type;
	अचिन्हित पूर्णांक idx = *seq_size;

	अगर (req_ctx->cryptlen == 0)
		वापस; /*null processing*/

	cc_set_cipher_desc(req, desc, &idx);
	cc_proc_cipher_desc(req, data_flow_mode, desc, &idx);
	अगर (direct == DRV_CRYPTO_सूचीECTION_ENCRYPT) अणु
		/* We must रुको क्रम DMA to ग_लिखो all cipher */
		hw_desc_init(&desc[idx]);
		set_din_no_dma(&desc[idx], 0, 0xfffff0);
		set_करोut_no_dma(&desc[idx], 0, 0, 1);
		idx++;
	पूर्ण

	*seq_size = idx;
पूर्ण

अटल व्योम cc_set_hmac_desc(काष्ठा aead_request *req, काष्ठा cc_hw_desc desc[],
			     अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	अचिन्हित पूर्णांक hash_mode = (ctx->auth_mode == DRV_HASH_SHA1) ?
				DRV_HASH_HW_SHA1 : DRV_HASH_HW_SHA256;
	अचिन्हित पूर्णांक digest_size = (ctx->auth_mode == DRV_HASH_SHA1) ?
				CC_SHA1_DIGEST_SIZE : CC_SHA256_DIGEST_SIZE;
	अचिन्हित पूर्णांक idx = *seq_size;

	/* Loading hash ipad xor key state */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], hash_mode);
	set_din_type(&desc[idx], DMA_DLLI,
		     ctx->auth_state.hmac.ipad_opad_dma_addr, digest_size,
		     NS_BIT);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Load init. digest len (64 bytes) */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], hash_mode);
	set_din_sram(&desc[idx], cc_digest_len_addr(ctx->drvdata, hash_mode),
		     ctx->hash_len);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	*seq_size = idx;
पूर्ण

अटल व्योम cc_set_xcbc_desc(काष्ठा aead_request *req, काष्ठा cc_hw_desc desc[],
			     अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	अचिन्हित पूर्णांक idx = *seq_size;

	/* Loading MAC state */
	hw_desc_init(&desc[idx]);
	set_din_स्थिर(&desc[idx], 0, CC_AES_BLOCK_SIZE);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	/* Setup XCBC MAC K1 */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI,
		     ctx->auth_state.xcbc.xcbc_keys_dma_addr,
		     AES_KEYSIZE_128, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	/* Setup XCBC MAC K2 */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI,
		     (ctx->auth_state.xcbc.xcbc_keys_dma_addr +
		      AES_KEYSIZE_128), AES_KEYSIZE_128, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
	set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	/* Setup XCBC MAC K3 */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI,
		     (ctx->auth_state.xcbc.xcbc_keys_dma_addr +
		      2 * AES_KEYSIZE_128), AES_KEYSIZE_128, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE2);
	set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	*seq_size = idx;
पूर्ण

अटल व्योम cc_proc_header_desc(काष्ठा aead_request *req,
				काष्ठा cc_hw_desc desc[],
				अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	अचिन्हित पूर्णांक idx = *seq_size;

	/* Hash associated data */
	अगर (areq_ctx->assoclen > 0)
		cc_set_assoc_desc(req, DIN_HASH, desc, &idx);

	/* Hash IV */
	*seq_size = idx;
पूर्ण

अटल व्योम cc_proc_scheme_desc(काष्ठा aead_request *req,
				काष्ठा cc_hw_desc desc[],
				अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा cc_aead_handle *aead_handle = ctx->drvdata->aead_handle;
	अचिन्हित पूर्णांक hash_mode = (ctx->auth_mode == DRV_HASH_SHA1) ?
				DRV_HASH_HW_SHA1 : DRV_HASH_HW_SHA256;
	अचिन्हित पूर्णांक digest_size = (ctx->auth_mode == DRV_HASH_SHA1) ?
				CC_SHA1_DIGEST_SIZE : CC_SHA256_DIGEST_SIZE;
	अचिन्हित पूर्णांक idx = *seq_size;

	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], hash_mode);
	set_करोut_sram(&desc[idx], aead_handle->sram_workspace_addr,
		      ctx->hash_len);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE1);
	set_cipher_करो(&desc[idx], DO_PAD);
	idx++;

	/* Get final ICV result */
	hw_desc_init(&desc[idx]);
	set_करोut_sram(&desc[idx], aead_handle->sram_workspace_addr,
		      digest_size);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	set_cipher_config0(&desc[idx], HASH_DIGEST_RESULT_LITTLE_ENDIAN);
	set_cipher_mode(&desc[idx], hash_mode);
	idx++;

	/* Loading hash opad xor key state */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], hash_mode);
	set_din_type(&desc[idx], DMA_DLLI,
		     (ctx->auth_state.hmac.ipad_opad_dma_addr + digest_size),
		     digest_size, NS_BIT);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Load init. digest len (64 bytes) */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], hash_mode);
	set_din_sram(&desc[idx], cc_digest_len_addr(ctx->drvdata, hash_mode),
		     ctx->hash_len);
	set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	/* Perक्रमm HASH update */
	hw_desc_init(&desc[idx]);
	set_din_sram(&desc[idx], aead_handle->sram_workspace_addr,
		     digest_size);
	set_flow_mode(&desc[idx], DIN_HASH);
	idx++;

	*seq_size = idx;
पूर्ण

अटल व्योम cc_mlli_to_sram(काष्ठा aead_request *req,
			    काष्ठा cc_hw_desc desc[], अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा aead_req_ctx *req_ctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	अगर ((req_ctx->assoc_buff_type == CC_DMA_BUF_MLLI ||
	    req_ctx->data_buff_type == CC_DMA_BUF_MLLI ||
	    !req_ctx->is_single_pass) && req_ctx->mlli_params.mlli_len) अणु
		dev_dbg(dev, "Copy-to-sram: mlli_dma=%08x, mlli_size=%u\n",
			ctx->drvdata->mlli_sram_addr,
			req_ctx->mlli_params.mlli_len);
		/* Copy MLLI table host-to-sram */
		hw_desc_init(&desc[*seq_size]);
		set_din_type(&desc[*seq_size], DMA_DLLI,
			     req_ctx->mlli_params.mlli_dma_addr,
			     req_ctx->mlli_params.mlli_len, NS_BIT);
		set_करोut_sram(&desc[*seq_size],
			      ctx->drvdata->mlli_sram_addr,
			      req_ctx->mlli_params.mlli_len);
		set_flow_mode(&desc[*seq_size], BYPASS);
		(*seq_size)++;
	पूर्ण
पूर्ण

अटल क्रमागत cc_flow_mode cc_get_data_flow(क्रमागत drv_crypto_direction direct,
					  क्रमागत cc_flow_mode setup_flow_mode,
					  bool is_single_pass)
अणु
	क्रमागत cc_flow_mode data_flow_mode;

	अगर (direct == DRV_CRYPTO_सूचीECTION_ENCRYPT) अणु
		अगर (setup_flow_mode == S_DIN_to_AES)
			data_flow_mode = is_single_pass ?
				AES_to_HASH_and_DOUT : DIN_AES_DOUT;
		अन्यथा
			data_flow_mode = is_single_pass ?
				DES_to_HASH_and_DOUT : DIN_DES_DOUT;
	पूर्ण अन्यथा अणु /* Decrypt */
		अगर (setup_flow_mode == S_DIN_to_AES)
			data_flow_mode = is_single_pass ?
				AES_and_HASH : DIN_AES_DOUT;
		अन्यथा
			data_flow_mode = is_single_pass ?
				DES_and_HASH : DIN_DES_DOUT;
	पूर्ण

	वापस data_flow_mode;
पूर्ण

अटल व्योम cc_hmac_authenc(काष्ठा aead_request *req, काष्ठा cc_hw_desc desc[],
			    अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_req_ctx *req_ctx = aead_request_ctx(req);
	पूर्णांक direct = req_ctx->gen_ctx.op_type;
	अचिन्हित पूर्णांक data_flow_mode =
		cc_get_data_flow(direct, ctx->flow_mode,
				 req_ctx->is_single_pass);

	अगर (req_ctx->is_single_pass) अणु
		/*
		 * Single-pass flow
		 */
		cc_set_hmac_desc(req, desc, seq_size);
		cc_set_cipher_desc(req, desc, seq_size);
		cc_proc_header_desc(req, desc, seq_size);
		cc_proc_cipher_desc(req, data_flow_mode, desc, seq_size);
		cc_proc_scheme_desc(req, desc, seq_size);
		cc_proc_digest_desc(req, desc, seq_size);
		वापस;
	पूर्ण

	/*
	 * Double-pass flow
	 * Fallback क्रम unsupported single-pass modes,
	 * i.e. using assoc. data of non-word-multiple
	 */
	अगर (direct == DRV_CRYPTO_सूचीECTION_ENCRYPT) अणु
		/* encrypt first.. */
		cc_proc_cipher(req, desc, seq_size, data_flow_mode);
		/* authenc after..*/
		cc_set_hmac_desc(req, desc, seq_size);
		cc_proc_authen_desc(req, DIN_HASH, desc, seq_size, direct);
		cc_proc_scheme_desc(req, desc, seq_size);
		cc_proc_digest_desc(req, desc, seq_size);

	पूर्ण अन्यथा अणु /*DECRYPT*/
		/* authenc first..*/
		cc_set_hmac_desc(req, desc, seq_size);
		cc_proc_authen_desc(req, DIN_HASH, desc, seq_size, direct);
		cc_proc_scheme_desc(req, desc, seq_size);
		/* decrypt after.. */
		cc_proc_cipher(req, desc, seq_size, data_flow_mode);
		/* पढ़ो the digest result with setting the completion bit
		 * must be after the cipher operation
		 */
		cc_proc_digest_desc(req, desc, seq_size);
	पूर्ण
पूर्ण

अटल व्योम
cc_xcbc_authenc(काष्ठा aead_request *req, काष्ठा cc_hw_desc desc[],
		अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_req_ctx *req_ctx = aead_request_ctx(req);
	पूर्णांक direct = req_ctx->gen_ctx.op_type;
	अचिन्हित पूर्णांक data_flow_mode =
		cc_get_data_flow(direct, ctx->flow_mode,
				 req_ctx->is_single_pass);

	अगर (req_ctx->is_single_pass) अणु
		/*
		 * Single-pass flow
		 */
		cc_set_xcbc_desc(req, desc, seq_size);
		cc_set_cipher_desc(req, desc, seq_size);
		cc_proc_header_desc(req, desc, seq_size);
		cc_proc_cipher_desc(req, data_flow_mode, desc, seq_size);
		cc_proc_digest_desc(req, desc, seq_size);
		वापस;
	पूर्ण

	/*
	 * Double-pass flow
	 * Fallback क्रम unsupported single-pass modes,
	 * i.e. using assoc. data of non-word-multiple
	 */
	अगर (direct == DRV_CRYPTO_सूचीECTION_ENCRYPT) अणु
		/* encrypt first.. */
		cc_proc_cipher(req, desc, seq_size, data_flow_mode);
		/* authenc after.. */
		cc_set_xcbc_desc(req, desc, seq_size);
		cc_proc_authen_desc(req, DIN_HASH, desc, seq_size, direct);
		cc_proc_digest_desc(req, desc, seq_size);
	पूर्ण अन्यथा अणु /*DECRYPT*/
		/* authenc first.. */
		cc_set_xcbc_desc(req, desc, seq_size);
		cc_proc_authen_desc(req, DIN_HASH, desc, seq_size, direct);
		/* decrypt after..*/
		cc_proc_cipher(req, desc, seq_size, data_flow_mode);
		/* पढ़ो the digest result with setting the completion bit
		 * must be after the cipher operation
		 */
		cc_proc_digest_desc(req, desc, seq_size);
	पूर्ण
पूर्ण

अटल पूर्णांक validate_data_size(काष्ठा cc_aead_ctx *ctx,
			      क्रमागत drv_crypto_direction direct,
			      काष्ठा aead_request *req)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	अचिन्हित पूर्णांक assoclen = areq_ctx->assoclen;
	अचिन्हित पूर्णांक cipherlen = (direct == DRV_CRYPTO_सूचीECTION_DECRYPT) ?
			(req->cryptlen - ctx->authsize) : req->cryptlen;

	अगर (direct == DRV_CRYPTO_सूचीECTION_DECRYPT &&
	    req->cryptlen < ctx->authsize)
		जाओ data_size_err;

	areq_ctx->is_single_pass = true; /*शेषed to fast flow*/

	चयन (ctx->flow_mode) अणु
	हाल S_DIN_to_AES:
		अगर (ctx->cipher_mode == DRV_CIPHER_CBC &&
		    !IS_ALIGNED(cipherlen, AES_BLOCK_SIZE))
			जाओ data_size_err;
		अगर (ctx->cipher_mode == DRV_CIPHER_CCM)
			अवरोध;
		अगर (ctx->cipher_mode == DRV_CIPHER_GCTR) अणु
			अगर (areq_ctx->plaपूर्णांकext_authenticate_only)
				areq_ctx->is_single_pass = false;
			अवरोध;
		पूर्ण

		अगर (!IS_ALIGNED(assoclen, माप(u32)))
			areq_ctx->is_single_pass = false;

		अगर (ctx->cipher_mode == DRV_CIPHER_CTR &&
		    !IS_ALIGNED(cipherlen, माप(u32)))
			areq_ctx->is_single_pass = false;

		अवरोध;
	हाल S_DIN_to_DES:
		अगर (!IS_ALIGNED(cipherlen, DES_BLOCK_SIZE))
			जाओ data_size_err;
		अगर (!IS_ALIGNED(assoclen, DES_BLOCK_SIZE))
			areq_ctx->is_single_pass = false;
		अवरोध;
	शेष:
		dev_err(dev, "Unexpected flow mode (%d)\n", ctx->flow_mode);
		जाओ data_size_err;
	पूर्ण

	वापस 0;

data_size_err:
	वापस -EINVAL;
पूर्ण

अटल अचिन्हित पूर्णांक क्रमmat_ccm_a0(u8 *pa0_buff, u32 header_size)
अणु
	अचिन्हित पूर्णांक len = 0;

	अगर (header_size == 0)
		वापस 0;

	अगर (header_size < ((1UL << 16) - (1UL << 8))) अणु
		len = 2;

		pa0_buff[0] = (header_size >> 8) & 0xFF;
		pa0_buff[1] = header_size & 0xFF;
	पूर्ण अन्यथा अणु
		len = 6;

		pa0_buff[0] = 0xFF;
		pa0_buff[1] = 0xFE;
		pa0_buff[2] = (header_size >> 24) & 0xFF;
		pa0_buff[3] = (header_size >> 16) & 0xFF;
		pa0_buff[4] = (header_size >> 8) & 0xFF;
		pa0_buff[5] = header_size & 0xFF;
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक set_msg_len(u8 *block, अचिन्हित पूर्णांक msglen, अचिन्हित पूर्णांक csize)
अणु
	__be32 data;

	स_रखो(block, 0, csize);
	block += csize;

	अगर (csize >= 4)
		csize = 4;
	अन्यथा अगर (msglen > (1 << (8 * csize)))
		वापस -EOVERFLOW;

	data = cpu_to_be32(msglen);
	स_नकल(block - csize, (u8 *)&data + 4 - csize, csize);

	वापस 0;
पूर्ण

अटल पूर्णांक cc_ccm(काष्ठा aead_request *req, काष्ठा cc_hw_desc desc[],
		  अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_req_ctx *req_ctx = aead_request_ctx(req);
	अचिन्हित पूर्णांक idx = *seq_size;
	अचिन्हित पूर्णांक cipher_flow_mode;
	dma_addr_t mac_result;

	अगर (req_ctx->gen_ctx.op_type == DRV_CRYPTO_सूचीECTION_DECRYPT) अणु
		cipher_flow_mode = AES_to_HASH_and_DOUT;
		mac_result = req_ctx->mac_buf_dma_addr;
	पूर्ण अन्यथा अणु /* Encrypt */
		cipher_flow_mode = AES_and_HASH;
		mac_result = req_ctx->icv_dma_addr;
	पूर्ण

	/* load key */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CTR);
	set_din_type(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr,
		     ((ctx->enc_keylen == 24) ?  CC_AES_KEY_SIZE_MAX :
		      ctx->enc_keylen), NS_BIT);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* load ctr state */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CTR);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_din_type(&desc[idx], DMA_DLLI,
		     req_ctx->gen_ctx.iv_dma_addr, AES_BLOCK_SIZE, NS_BIT);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* load MAC key */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CBC_MAC);
	set_din_type(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr,
		     ((ctx->enc_keylen == 24) ?  CC_AES_KEY_SIZE_MAX :
		      ctx->enc_keylen), NS_BIT);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	/* load MAC state */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CBC_MAC);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->mac_buf_dma_addr,
		     AES_BLOCK_SIZE, NS_BIT);
	set_cipher_config0(&desc[idx], DESC_सूचीECTION_ENCRYPT_ENCRYPT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	/* process assoc data */
	अगर (req_ctx->assoclen > 0) अणु
		cc_set_assoc_desc(req, DIN_HASH, desc, &idx);
	पूर्ण अन्यथा अणु
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DLLI,
			     sg_dma_address(&req_ctx->ccm_adata_sg),
			     AES_BLOCK_SIZE + req_ctx->ccm_hdr_size, NS_BIT);
		set_flow_mode(&desc[idx], DIN_HASH);
		idx++;
	पूर्ण

	/* process the cipher */
	अगर (req_ctx->cryptlen)
		cc_proc_cipher_desc(req, cipher_flow_mode, desc, &idx);

	/* Read temporal MAC */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CBC_MAC);
	set_करोut_dlli(&desc[idx], req_ctx->mac_buf_dma_addr, ctx->authsize,
		      NS_BIT, 0);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	set_cipher_config0(&desc[idx], HASH_DIGEST_RESULT_LITTLE_ENDIAN);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	/* load AES-CTR state (क्रम last MAC calculation)*/
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CTR);
	set_cipher_config0(&desc[idx], DRV_CRYPTO_सूचीECTION_ENCRYPT);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->ccm_iv0_dma_addr,
		     AES_BLOCK_SIZE, NS_BIT);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	hw_desc_init(&desc[idx]);
	set_din_no_dma(&desc[idx], 0, 0xfffff0);
	set_करोut_no_dma(&desc[idx], 0, 0, 1);
	idx++;

	/* encrypt the "T" value and store MAC in mac_state */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->mac_buf_dma_addr,
		     ctx->authsize, NS_BIT);
	set_करोut_dlli(&desc[idx], mac_result, ctx->authsize, NS_BIT, 1);
	set_queue_last_ind(ctx->drvdata, &desc[idx]);
	set_flow_mode(&desc[idx], DIN_AES_DOUT);
	idx++;

	*seq_size = idx;
	वापस 0;
पूर्ण

अटल पूर्णांक config_ccm_adata(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	काष्ठा aead_req_ctx *req_ctx = aead_request_ctx(req);
	//अचिन्हित पूर्णांक size_of_a = 0, rem_a_size = 0;
	अचिन्हित पूर्णांक lp = req->iv[0];
	/* Note: The code assume that req->iv[0] alपढ़ोy contains the value
	 * of L' of RFC3610
	 */
	अचिन्हित पूर्णांक l = lp + 1;  /* This is L' of RFC 3610. */
	अचिन्हित पूर्णांक m = ctx->authsize;  /* This is M' of RFC 3610. */
	u8 *b0 = req_ctx->ccm_config + CCM_B0_OFFSET;
	u8 *a0 = req_ctx->ccm_config + CCM_A0_OFFSET;
	u8 *ctr_count_0 = req_ctx->ccm_config + CCM_CTR_COUNT_0_OFFSET;
	अचिन्हित पूर्णांक cryptlen = (req_ctx->gen_ctx.op_type ==
				 DRV_CRYPTO_सूचीECTION_ENCRYPT) ?
				req->cryptlen :
				(req->cryptlen - ctx->authsize);
	पूर्णांक rc;

	स_रखो(req_ctx->mac_buf, 0, AES_BLOCK_SIZE);
	स_रखो(req_ctx->ccm_config, 0, AES_BLOCK_SIZE * 3);

	/* taken from crypto/ccm.c */
	/* 2 <= L <= 8, so 1 <= L' <= 7. */
	अगर (l < 2 || l > 8) अणु
		dev_dbg(dev, "illegal iv value %X\n", req->iv[0]);
		वापस -EINVAL;
	पूर्ण
	स_नकल(b0, req->iv, AES_BLOCK_SIZE);

	/* क्रमmat control info per RFC 3610 and
	 * NIST Special Publication 800-38C
	 */
	*b0 |= (8 * ((m - 2) / 2));
	अगर (req_ctx->assoclen > 0)
		*b0 |= 64;  /* Enable bit 6 अगर Adata exists. */

	rc = set_msg_len(b0 + 16 - l, cryptlen, l);  /* Write L'. */
	अगर (rc) अणु
		dev_err(dev, "message len overflow detected");
		वापस rc;
	पूर्ण
	 /* END of "taken from crypto/ccm.c" */

	/* l(a) - size of associated data. */
	req_ctx->ccm_hdr_size = क्रमmat_ccm_a0(a0, req_ctx->assoclen);

	स_रखो(req->iv + 15 - req->iv[0], 0, req->iv[0] + 1);
	req->iv[15] = 1;

	स_नकल(ctr_count_0, req->iv, AES_BLOCK_SIZE);
	ctr_count_0[15] = 0;

	वापस 0;
पूर्ण

अटल व्योम cc_proc_rfc4309_ccm(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);

	/* L' */
	स_रखो(areq_ctx->ctr_iv, 0, AES_BLOCK_SIZE);
	/* For RFC 4309, always use 4 bytes क्रम message length
	 * (at most 2^32-1 bytes).
	 */
	areq_ctx->ctr_iv[0] = 3;

	/* In RFC 4309 there is an 11-bytes nonce+IV part,
	 * that we build here.
	 */
	स_नकल(areq_ctx->ctr_iv + CCM_BLOCK_NONCE_OFFSET, ctx->ctr_nonce,
	       CCM_BLOCK_NONCE_SIZE);
	स_नकल(areq_ctx->ctr_iv + CCM_BLOCK_IV_OFFSET, req->iv,
	       CCM_BLOCK_IV_SIZE);
	req->iv = areq_ctx->ctr_iv;
पूर्ण

अटल व्योम cc_set_ghash_desc(काष्ठा aead_request *req,
			      काष्ठा cc_hw_desc desc[], अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_req_ctx *req_ctx = aead_request_ctx(req);
	अचिन्हित पूर्णांक idx = *seq_size;

	/* load key to AES*/
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_ECB);
	set_cipher_config0(&desc[idx], DRV_CRYPTO_सूचीECTION_ENCRYPT);
	set_din_type(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr,
		     ctx->enc_keylen, NS_BIT);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* process one zero block to generate hkey */
	hw_desc_init(&desc[idx]);
	set_din_स्थिर(&desc[idx], 0x0, AES_BLOCK_SIZE);
	set_करोut_dlli(&desc[idx], req_ctx->hkey_dma_addr, AES_BLOCK_SIZE,
		      NS_BIT, 0);
	set_flow_mode(&desc[idx], DIN_AES_DOUT);
	idx++;

	/* Memory Barrier */
	hw_desc_init(&desc[idx]);
	set_din_no_dma(&desc[idx], 0, 0xfffff0);
	set_करोut_no_dma(&desc[idx], 0, 0, 1);
	idx++;

	/* Load GHASH subkey */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->hkey_dma_addr,
		     AES_BLOCK_SIZE, NS_BIT);
	set_करोut_no_dma(&desc[idx], 0, 0, 1);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_HASH_HW_GHASH);
	set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	/* Configure Hash Engine to work with GHASH.
	 * Since it was not possible to extend HASH submodes to add GHASH,
	 * The following command is necessary in order to
	 * select GHASH (according to HW designers)
	 */
	hw_desc_init(&desc[idx]);
	set_din_no_dma(&desc[idx], 0, 0xfffff0);
	set_करोut_no_dma(&desc[idx], 0, 0, 1);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_HASH_HW_GHASH);
	set_cipher_करो(&desc[idx], 1); //1=AES_SK RKEK
	set_cipher_config0(&desc[idx], DRV_CRYPTO_सूचीECTION_ENCRYPT);
	set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	/* Load GHASH initial STATE (which is 0). (क्रम any hash there is an
	 * initial state)
	 */
	hw_desc_init(&desc[idx]);
	set_din_स्थिर(&desc[idx], 0x0, AES_BLOCK_SIZE);
	set_करोut_no_dma(&desc[idx], 0, 0, 1);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_HASH_HW_GHASH);
	set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	*seq_size = idx;
पूर्ण

अटल व्योम cc_set_gctr_desc(काष्ठा aead_request *req, काष्ठा cc_hw_desc desc[],
			     अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_req_ctx *req_ctx = aead_request_ctx(req);
	अचिन्हित पूर्णांक idx = *seq_size;

	/* load key to AES*/
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_GCTR);
	set_cipher_config0(&desc[idx], DRV_CRYPTO_सूचीECTION_ENCRYPT);
	set_din_type(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr,
		     ctx->enc_keylen, NS_BIT);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	अगर (req_ctx->cryptlen && !req_ctx->plaपूर्णांकext_authenticate_only) अणु
		/* load AES/CTR initial CTR value inc by 2*/
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], DRV_CIPHER_GCTR);
		set_key_size_aes(&desc[idx], ctx->enc_keylen);
		set_din_type(&desc[idx], DMA_DLLI,
			     req_ctx->gcm_iv_inc2_dma_addr, AES_BLOCK_SIZE,
			     NS_BIT);
		set_cipher_config0(&desc[idx], DRV_CRYPTO_सूचीECTION_ENCRYPT);
		set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
		set_flow_mode(&desc[idx], S_DIN_to_AES);
		idx++;
	पूर्ण

	*seq_size = idx;
पूर्ण

अटल व्योम cc_proc_gcm_result(काष्ठा aead_request *req,
			       काष्ठा cc_hw_desc desc[],
			       अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_req_ctx *req_ctx = aead_request_ctx(req);
	dma_addr_t mac_result;
	अचिन्हित पूर्णांक idx = *seq_size;

	अगर (req_ctx->gen_ctx.op_type == DRV_CRYPTO_सूचीECTION_DECRYPT) अणु
		mac_result = req_ctx->mac_buf_dma_addr;
	पूर्ण अन्यथा अणु /* Encrypt */
		mac_result = req_ctx->icv_dma_addr;
	पूर्ण

	/* process(ghash) gcm_block_len */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->gcm_block_len_dma_addr,
		     AES_BLOCK_SIZE, NS_BIT);
	set_flow_mode(&desc[idx], DIN_HASH);
	idx++;

	/* Store GHASH state after GHASH(Associated Data + Cipher +LenBlock) */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_HASH_HW_GHASH);
	set_din_no_dma(&desc[idx], 0, 0xfffff0);
	set_करोut_dlli(&desc[idx], req_ctx->mac_buf_dma_addr, AES_BLOCK_SIZE,
		      NS_BIT, 0);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	set_aes_not_hash_mode(&desc[idx]);

	idx++;

	/* load AES/CTR initial CTR value inc by 1*/
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_GCTR);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->gcm_iv_inc1_dma_addr,
		     AES_BLOCK_SIZE, NS_BIT);
	set_cipher_config0(&desc[idx], DRV_CRYPTO_सूचीECTION_ENCRYPT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Memory Barrier */
	hw_desc_init(&desc[idx]);
	set_din_no_dma(&desc[idx], 0, 0xfffff0);
	set_करोut_no_dma(&desc[idx], 0, 0, 1);
	idx++;

	/* process GCTR on stored GHASH and store MAC in mac_state*/
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_GCTR);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->mac_buf_dma_addr,
		     AES_BLOCK_SIZE, NS_BIT);
	set_करोut_dlli(&desc[idx], mac_result, ctx->authsize, NS_BIT, 1);
	set_queue_last_ind(ctx->drvdata, &desc[idx]);
	set_flow_mode(&desc[idx], DIN_AES_DOUT);
	idx++;

	*seq_size = idx;
पूर्ण

अटल पूर्णांक cc_gcm(काष्ठा aead_request *req, काष्ठा cc_hw_desc desc[],
		  अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा aead_req_ctx *req_ctx = aead_request_ctx(req);
	अचिन्हित पूर्णांक cipher_flow_mode;

	//in RFC4543 no data to encrypt. just copy data from src to dest.
	अगर (req_ctx->plaपूर्णांकext_authenticate_only) अणु
		cc_proc_cipher_desc(req, BYPASS, desc, seq_size);
		cc_set_ghash_desc(req, desc, seq_size);
		/* process(ghash) assoc data */
		cc_set_assoc_desc(req, DIN_HASH, desc, seq_size);
		cc_set_gctr_desc(req, desc, seq_size);
		cc_proc_gcm_result(req, desc, seq_size);
		वापस 0;
	पूर्ण

	अगर (req_ctx->gen_ctx.op_type == DRV_CRYPTO_सूचीECTION_DECRYPT) अणु
		cipher_flow_mode = AES_and_HASH;
	पूर्ण अन्यथा अणु /* Encrypt */
		cipher_flow_mode = AES_to_HASH_and_DOUT;
	पूर्ण

	// क्रम gcm and rfc4106.
	cc_set_ghash_desc(req, desc, seq_size);
	/* process(ghash) assoc data */
	अगर (req_ctx->assoclen > 0)
		cc_set_assoc_desc(req, DIN_HASH, desc, seq_size);
	cc_set_gctr_desc(req, desc, seq_size);
	/* process(gctr+ghash) */
	अगर (req_ctx->cryptlen)
		cc_proc_cipher_desc(req, cipher_flow_mode, desc, seq_size);
	cc_proc_gcm_result(req, desc, seq_size);

	वापस 0;
पूर्ण

अटल पूर्णांक config_gcm_context(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_req_ctx *req_ctx = aead_request_ctx(req);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	अचिन्हित पूर्णांक cryptlen = (req_ctx->gen_ctx.op_type ==
				 DRV_CRYPTO_सूचीECTION_ENCRYPT) ?
				req->cryptlen :
				(req->cryptlen - ctx->authsize);
	__be32 counter = cpu_to_be32(2);

	dev_dbg(dev, "%s() cryptlen = %d, req_ctx->assoclen = %d ctx->authsize = %d\n",
		__func__, cryptlen, req_ctx->assoclen, ctx->authsize);

	स_रखो(req_ctx->hkey, 0, AES_BLOCK_SIZE);

	स_रखो(req_ctx->mac_buf, 0, AES_BLOCK_SIZE);

	स_नकल(req->iv + 12, &counter, 4);
	स_नकल(req_ctx->gcm_iv_inc2, req->iv, 16);

	counter = cpu_to_be32(1);
	स_नकल(req->iv + 12, &counter, 4);
	स_नकल(req_ctx->gcm_iv_inc1, req->iv, 16);

	अगर (!req_ctx->plaपूर्णांकext_authenticate_only) अणु
		__be64 temp64;

		temp64 = cpu_to_be64(req_ctx->assoclen * 8);
		स_नकल(&req_ctx->gcm_len_block.len_a, &temp64, माप(temp64));
		temp64 = cpu_to_be64(cryptlen * 8);
		स_नकल(&req_ctx->gcm_len_block.len_c, &temp64, 8);
	पूर्ण अन्यथा अणु
		/* rfc4543=>  all data(AAD,IV,Plain) are considered additional
		 * data that is nothing is encrypted.
		 */
		__be64 temp64;

		temp64 = cpu_to_be64((req_ctx->assoclen + cryptlen) * 8);
		स_नकल(&req_ctx->gcm_len_block.len_a, &temp64, माप(temp64));
		temp64 = 0;
		स_नकल(&req_ctx->gcm_len_block.len_c, &temp64, 8);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cc_proc_rfc4_gcm(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);

	स_नकल(areq_ctx->ctr_iv + GCM_BLOCK_RFC4_NONCE_OFFSET,
	       ctx->ctr_nonce, GCM_BLOCK_RFC4_NONCE_SIZE);
	स_नकल(areq_ctx->ctr_iv + GCM_BLOCK_RFC4_IV_OFFSET, req->iv,
	       GCM_BLOCK_RFC4_IV_SIZE);
	req->iv = areq_ctx->ctr_iv;
पूर्ण

अटल पूर्णांक cc_proc_aead(काष्ठा aead_request *req,
			क्रमागत drv_crypto_direction direct)
अणु
	पूर्णांक rc = 0;
	पूर्णांक seq_len = 0;
	काष्ठा cc_hw_desc desc[MAX_AEAD_PROCESS_SEQ];
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);
	काष्ठा cc_crypto_req cc_req = अणुपूर्ण;

	dev_dbg(dev, "%s context=%p req=%p iv=%p src=%p src_ofs=%d dst=%p dst_ofs=%d cryptolen=%d\n",
		((direct == DRV_CRYPTO_सूचीECTION_ENCRYPT) ? "Enc" : "Dec"),
		ctx, req, req->iv, sg_virt(req->src), req->src->offset,
		sg_virt(req->dst), req->dst->offset, req->cryptlen);

	/* STAT_PHASE_0: Init and sanity checks */

	/* Check data length according to mode */
	अगर (validate_data_size(ctx, direct, req)) अणु
		dev_err(dev, "Unsupported crypt/assoc len %d/%d.\n",
			req->cryptlen, areq_ctx->assoclen);
		वापस -EINVAL;
	पूर्ण

	/* Setup request काष्ठाure */
	cc_req.user_cb = cc_aead_complete;
	cc_req.user_arg = req;

	/* Setup request context */
	areq_ctx->gen_ctx.op_type = direct;
	areq_ctx->req_authsize = ctx->authsize;
	areq_ctx->cipher_mode = ctx->cipher_mode;

	/* STAT_PHASE_1: Map buffers */

	अगर (ctx->cipher_mode == DRV_CIPHER_CTR) अणु
		/* Build CTR IV - Copy nonce from last 4 bytes in
		 * CTR key to first 4 bytes in CTR IV
		 */
		स_नकल(areq_ctx->ctr_iv, ctx->ctr_nonce,
		       CTR_RFC3686_NONCE_SIZE);
		स_नकल(areq_ctx->ctr_iv + CTR_RFC3686_NONCE_SIZE, req->iv,
		       CTR_RFC3686_IV_SIZE);
		/* Initialize counter portion of counter block */
		*(__be32 *)(areq_ctx->ctr_iv + CTR_RFC3686_NONCE_SIZE +
			    CTR_RFC3686_IV_SIZE) = cpu_to_be32(1);

		/* Replace with counter iv */
		req->iv = areq_ctx->ctr_iv;
		areq_ctx->hw_iv_size = CTR_RFC3686_BLOCK_SIZE;
	पूर्ण अन्यथा अगर ((ctx->cipher_mode == DRV_CIPHER_CCM) ||
		   (ctx->cipher_mode == DRV_CIPHER_GCTR)) अणु
		areq_ctx->hw_iv_size = AES_BLOCK_SIZE;
		अगर (areq_ctx->ctr_iv != req->iv) अणु
			स_नकल(areq_ctx->ctr_iv, req->iv,
			       crypto_aead_ivsize(tfm));
			req->iv = areq_ctx->ctr_iv;
		पूर्ण
	पूर्ण  अन्यथा अणु
		areq_ctx->hw_iv_size = crypto_aead_ivsize(tfm);
	पूर्ण

	अगर (ctx->cipher_mode == DRV_CIPHER_CCM) अणु
		rc = config_ccm_adata(req);
		अगर (rc) अणु
			dev_dbg(dev, "config_ccm_adata() returned with a failure %d!",
				rc);
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		areq_ctx->ccm_hdr_size = ccm_header_size_null;
	पूर्ण

	अगर (ctx->cipher_mode == DRV_CIPHER_GCTR) अणु
		rc = config_gcm_context(req);
		अगर (rc) अणु
			dev_dbg(dev, "config_gcm_context() returned with a failure %d!",
				rc);
			जाओ निकास;
		पूर्ण
	पूर्ण

	rc = cc_map_aead_request(ctx->drvdata, req);
	अगर (rc) अणु
		dev_err(dev, "map_request() failed\n");
		जाओ निकास;
	पूर्ण

	/* STAT_PHASE_2: Create sequence */

	/* Load MLLI tables to SRAM अगर necessary */
	cc_mlli_to_sram(req, desc, &seq_len);

	चयन (ctx->auth_mode) अणु
	हाल DRV_HASH_SHA1:
	हाल DRV_HASH_SHA256:
		cc_hmac_authenc(req, desc, &seq_len);
		अवरोध;
	हाल DRV_HASH_XCBC_MAC:
		cc_xcbc_authenc(req, desc, &seq_len);
		अवरोध;
	हाल DRV_HASH_शून्य:
		अगर (ctx->cipher_mode == DRV_CIPHER_CCM)
			cc_ccm(req, desc, &seq_len);
		अगर (ctx->cipher_mode == DRV_CIPHER_GCTR)
			cc_gcm(req, desc, &seq_len);
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported authenc (%d)\n", ctx->auth_mode);
		cc_unmap_aead_request(dev, req);
		rc = -ENOTSUPP;
		जाओ निकास;
	पूर्ण

	/* STAT_PHASE_3: Lock HW and push sequence */

	rc = cc_send_request(ctx->drvdata, &cc_req, desc, seq_len, &req->base);

	अगर (rc != -EINPROGRESS && rc != -EBUSY) अणु
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);
		cc_unmap_aead_request(dev, req);
	पूर्ण

निकास:
	वापस rc;
पूर्ण

अटल पूर्णांक cc_aead_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	पूर्णांक rc;

	स_रखो(areq_ctx, 0, माप(*areq_ctx));

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->assoclen = req->assoclen;

	rc = cc_proc_aead(req, DRV_CRYPTO_सूचीECTION_ENCRYPT);
	अगर (rc != -EINPROGRESS && rc != -EBUSY)
		req->iv = areq_ctx->backup_iv;

	वापस rc;
पूर्ण

अटल पूर्णांक cc_rfc4309_ccm_encrypt(काष्ठा aead_request *req)
अणु
	/* Very similar to cc_aead_encrypt() above. */

	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	पूर्णांक rc;

	rc = crypto_ipsec_check_assoclen(req->assoclen);
	अगर (rc)
		जाओ out;

	स_रखो(areq_ctx, 0, माप(*areq_ctx));

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->assoclen = req->assoclen - CCM_BLOCK_IV_SIZE;

	cc_proc_rfc4309_ccm(req);

	rc = cc_proc_aead(req, DRV_CRYPTO_सूचीECTION_ENCRYPT);
	अगर (rc != -EINPROGRESS && rc != -EBUSY)
		req->iv = areq_ctx->backup_iv;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक cc_aead_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	पूर्णांक rc;

	स_रखो(areq_ctx, 0, माप(*areq_ctx));

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->assoclen = req->assoclen;

	rc = cc_proc_aead(req, DRV_CRYPTO_सूचीECTION_DECRYPT);
	अगर (rc != -EINPROGRESS && rc != -EBUSY)
		req->iv = areq_ctx->backup_iv;

	वापस rc;
पूर्ण

अटल पूर्णांक cc_rfc4309_ccm_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	पूर्णांक rc;

	rc = crypto_ipsec_check_assoclen(req->assoclen);
	अगर (rc)
		जाओ out;

	स_रखो(areq_ctx, 0, माप(*areq_ctx));

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->assoclen = req->assoclen - CCM_BLOCK_IV_SIZE;

	cc_proc_rfc4309_ccm(req);

	rc = cc_proc_aead(req, DRV_CRYPTO_सूचीECTION_DECRYPT);
	अगर (rc != -EINPROGRESS && rc != -EBUSY)
		req->iv = areq_ctx->backup_iv;

out:
	वापस rc;
पूर्ण

अटल पूर्णांक cc_rfc4106_gcm_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	dev_dbg(dev, "%s()  keylen %d, key %p\n", __func__, keylen, key);

	अगर (keylen < 4)
		वापस -EINVAL;

	keylen -= 4;
	स_नकल(ctx->ctr_nonce, key + keylen, 4);

	वापस cc_aead_setkey(tfm, key, keylen);
पूर्ण

अटल पूर्णांक cc_rfc4543_gcm_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	dev_dbg(dev, "%s()  keylen %d, key %p\n", __func__, keylen, key);

	अगर (keylen < 4)
		वापस -EINVAL;

	keylen -= 4;
	स_नकल(ctx->ctr_nonce, key + keylen, 4);

	वापस cc_aead_setkey(tfm, key, keylen);
पूर्ण

अटल पूर्णांक cc_gcm_setauthsize(काष्ठा crypto_aead *authenc,
			      अचिन्हित पूर्णांक authsize)
अणु
	चयन (authsize) अणु
	हाल 4:
	हाल 8:
	हाल 12:
	हाल 13:
	हाल 14:
	हाल 15:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस cc_aead_setauthsize(authenc, authsize);
पूर्ण

अटल पूर्णांक cc_rfc4106_gcm_setauthsize(काष्ठा crypto_aead *authenc,
				      अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(authenc);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	dev_dbg(dev, "authsize %d\n", authsize);

	चयन (authsize) अणु
	हाल 8:
	हाल 12:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस cc_aead_setauthsize(authenc, authsize);
पूर्ण

अटल पूर्णांक cc_rfc4543_gcm_setauthsize(काष्ठा crypto_aead *authenc,
				      अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा cc_aead_ctx *ctx = crypto_aead_ctx(authenc);
	काष्ठा device *dev = drvdata_to_dev(ctx->drvdata);

	dev_dbg(dev, "authsize %d\n", authsize);

	अगर (authsize != 16)
		वापस -EINVAL;

	वापस cc_aead_setauthsize(authenc, authsize);
पूर्ण

अटल पूर्णांक cc_rfc4106_gcm_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	पूर्णांक rc;

	rc = crypto_ipsec_check_assoclen(req->assoclen);
	अगर (rc)
		जाओ out;

	स_रखो(areq_ctx, 0, माप(*areq_ctx));

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->assoclen = req->assoclen - GCM_BLOCK_RFC4_IV_SIZE;

	cc_proc_rfc4_gcm(req);

	rc = cc_proc_aead(req, DRV_CRYPTO_सूचीECTION_ENCRYPT);
	अगर (rc != -EINPROGRESS && rc != -EBUSY)
		req->iv = areq_ctx->backup_iv;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक cc_rfc4543_gcm_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	पूर्णांक rc;

	rc = crypto_ipsec_check_assoclen(req->assoclen);
	अगर (rc)
		जाओ out;

	स_रखो(areq_ctx, 0, माप(*areq_ctx));

	//plaपूर्णांकext is not encryped with rfc4543
	areq_ctx->plaपूर्णांकext_authenticate_only = true;

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->assoclen = req->assoclen;

	cc_proc_rfc4_gcm(req);

	rc = cc_proc_aead(req, DRV_CRYPTO_सूचीECTION_ENCRYPT);
	अगर (rc != -EINPROGRESS && rc != -EBUSY)
		req->iv = areq_ctx->backup_iv;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक cc_rfc4106_gcm_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	पूर्णांक rc;

	rc = crypto_ipsec_check_assoclen(req->assoclen);
	अगर (rc)
		जाओ out;

	स_रखो(areq_ctx, 0, माप(*areq_ctx));

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->assoclen = req->assoclen - GCM_BLOCK_RFC4_IV_SIZE;

	cc_proc_rfc4_gcm(req);

	rc = cc_proc_aead(req, DRV_CRYPTO_सूचीECTION_DECRYPT);
	अगर (rc != -EINPROGRESS && rc != -EBUSY)
		req->iv = areq_ctx->backup_iv;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक cc_rfc4543_gcm_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	पूर्णांक rc;

	rc = crypto_ipsec_check_assoclen(req->assoclen);
	अगर (rc)
		जाओ out;

	स_रखो(areq_ctx, 0, माप(*areq_ctx));

	//plaपूर्णांकext is not decryped with rfc4543
	areq_ctx->plaपूर्णांकext_authenticate_only = true;

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->assoclen = req->assoclen;

	cc_proc_rfc4_gcm(req);

	rc = cc_proc_aead(req, DRV_CRYPTO_सूचीECTION_DECRYPT);
	अगर (rc != -EINPROGRESS && rc != -EBUSY)
		req->iv = areq_ctx->backup_iv;
out:
	वापस rc;
पूर्ण

/* aead alg */
अटल काष्ठा cc_alg_ढाँचा aead_algs[] = अणु
	अणु
		.name = "authenc(hmac(sha1),cbc(aes))",
		.driver_name = "authenc-hmac-sha1-cbc-aes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_aead = अणु
			.setkey = cc_aead_setkey,
			.setauthsize = cc_aead_setauthsize,
			.encrypt = cc_aead_encrypt,
			.decrypt = cc_aead_decrypt,
			.init = cc_aead_init,
			.निकास = cc_aead_निकास,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_CBC,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = DRV_HASH_SHA1,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "authenc(hmac(sha1),cbc(des3_ede))",
		.driver_name = "authenc-hmac-sha1-cbc-des3-ccree",
		.blocksize = DES3_EDE_BLOCK_SIZE,
		.ढाँचा_aead = अणु
			.setkey = cc_des3_aead_setkey,
			.setauthsize = cc_aead_setauthsize,
			.encrypt = cc_aead_encrypt,
			.decrypt = cc_aead_decrypt,
			.init = cc_aead_init,
			.निकास = cc_aead_निकास,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_CBC,
		.flow_mode = S_DIN_to_DES,
		.auth_mode = DRV_HASH_SHA1,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "authenc(hmac(sha256),cbc(aes))",
		.driver_name = "authenc-hmac-sha256-cbc-aes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_aead = अणु
			.setkey = cc_aead_setkey,
			.setauthsize = cc_aead_setauthsize,
			.encrypt = cc_aead_encrypt,
			.decrypt = cc_aead_decrypt,
			.init = cc_aead_init,
			.निकास = cc_aead_निकास,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_CBC,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = DRV_HASH_SHA256,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "authenc(hmac(sha256),cbc(des3_ede))",
		.driver_name = "authenc-hmac-sha256-cbc-des3-ccree",
		.blocksize = DES3_EDE_BLOCK_SIZE,
		.ढाँचा_aead = अणु
			.setkey = cc_des3_aead_setkey,
			.setauthsize = cc_aead_setauthsize,
			.encrypt = cc_aead_encrypt,
			.decrypt = cc_aead_decrypt,
			.init = cc_aead_init,
			.निकास = cc_aead_निकास,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_CBC,
		.flow_mode = S_DIN_to_DES,
		.auth_mode = DRV_HASH_SHA256,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "authenc(xcbc(aes),cbc(aes))",
		.driver_name = "authenc-xcbc-aes-cbc-aes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_aead = अणु
			.setkey = cc_aead_setkey,
			.setauthsize = cc_aead_setauthsize,
			.encrypt = cc_aead_encrypt,
			.decrypt = cc_aead_decrypt,
			.init = cc_aead_init,
			.निकास = cc_aead_निकास,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_CBC,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = DRV_HASH_XCBC_MAC,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "authenc(hmac(sha1),rfc3686(ctr(aes)))",
		.driver_name = "authenc-hmac-sha1-rfc3686-ctr-aes-ccree",
		.blocksize = 1,
		.ढाँचा_aead = अणु
			.setkey = cc_aead_setkey,
			.setauthsize = cc_aead_setauthsize,
			.encrypt = cc_aead_encrypt,
			.decrypt = cc_aead_decrypt,
			.init = cc_aead_init,
			.निकास = cc_aead_निकास,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_CTR,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = DRV_HASH_SHA1,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "authenc(hmac(sha256),rfc3686(ctr(aes)))",
		.driver_name = "authenc-hmac-sha256-rfc3686-ctr-aes-ccree",
		.blocksize = 1,
		.ढाँचा_aead = अणु
			.setkey = cc_aead_setkey,
			.setauthsize = cc_aead_setauthsize,
			.encrypt = cc_aead_encrypt,
			.decrypt = cc_aead_decrypt,
			.init = cc_aead_init,
			.निकास = cc_aead_निकास,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_CTR,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = DRV_HASH_SHA256,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "authenc(xcbc(aes),rfc3686(ctr(aes)))",
		.driver_name = "authenc-xcbc-aes-rfc3686-ctr-aes-ccree",
		.blocksize = 1,
		.ढाँचा_aead = अणु
			.setkey = cc_aead_setkey,
			.setauthsize = cc_aead_setauthsize,
			.encrypt = cc_aead_encrypt,
			.decrypt = cc_aead_decrypt,
			.init = cc_aead_init,
			.निकास = cc_aead_निकास,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_CTR,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = DRV_HASH_XCBC_MAC,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "ccm(aes)",
		.driver_name = "ccm-aes-ccree",
		.blocksize = 1,
		.ढाँचा_aead = अणु
			.setkey = cc_aead_setkey,
			.setauthsize = cc_ccm_setauthsize,
			.encrypt = cc_aead_encrypt,
			.decrypt = cc_aead_decrypt,
			.init = cc_aead_init,
			.निकास = cc_aead_निकास,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_CCM,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = DRV_HASH_शून्य,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "rfc4309(ccm(aes))",
		.driver_name = "rfc4309-ccm-aes-ccree",
		.blocksize = 1,
		.ढाँचा_aead = अणु
			.setkey = cc_rfc4309_ccm_setkey,
			.setauthsize = cc_rfc4309_ccm_setauthsize,
			.encrypt = cc_rfc4309_ccm_encrypt,
			.decrypt = cc_rfc4309_ccm_decrypt,
			.init = cc_aead_init,
			.निकास = cc_aead_निकास,
			.ivsize = CCM_BLOCK_IV_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_CCM,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = DRV_HASH_शून्य,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "gcm(aes)",
		.driver_name = "gcm-aes-ccree",
		.blocksize = 1,
		.ढाँचा_aead = अणु
			.setkey = cc_aead_setkey,
			.setauthsize = cc_gcm_setauthsize,
			.encrypt = cc_aead_encrypt,
			.decrypt = cc_aead_decrypt,
			.init = cc_aead_init,
			.निकास = cc_aead_निकास,
			.ivsize = 12,
			.maxauthsize = AES_BLOCK_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_GCTR,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = DRV_HASH_शून्य,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "rfc4106(gcm(aes))",
		.driver_name = "rfc4106-gcm-aes-ccree",
		.blocksize = 1,
		.ढाँचा_aead = अणु
			.setkey = cc_rfc4106_gcm_setkey,
			.setauthsize = cc_rfc4106_gcm_setauthsize,
			.encrypt = cc_rfc4106_gcm_encrypt,
			.decrypt = cc_rfc4106_gcm_decrypt,
			.init = cc_aead_init,
			.निकास = cc_aead_निकास,
			.ivsize = GCM_BLOCK_RFC4_IV_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_GCTR,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = DRV_HASH_शून्य,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "rfc4543(gcm(aes))",
		.driver_name = "rfc4543-gcm-aes-ccree",
		.blocksize = 1,
		.ढाँचा_aead = अणु
			.setkey = cc_rfc4543_gcm_setkey,
			.setauthsize = cc_rfc4543_gcm_setauthsize,
			.encrypt = cc_rfc4543_gcm_encrypt,
			.decrypt = cc_rfc4543_gcm_decrypt,
			.init = cc_aead_init,
			.निकास = cc_aead_निकास,
			.ivsize = GCM_BLOCK_RFC4_IV_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_GCTR,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = DRV_HASH_शून्य,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
पूर्ण;

अटल काष्ठा cc_crypto_alg *cc_create_aead_alg(काष्ठा cc_alg_ढाँचा *पंचांगpl,
						काष्ठा device *dev)
अणु
	काष्ठा cc_crypto_alg *t_alg;
	काष्ठा aead_alg *alg;

	t_alg = devm_kzalloc(dev, माप(*t_alg), GFP_KERNEL);
	अगर (!t_alg)
		वापस ERR_PTR(-ENOMEM);

	alg = &पंचांगpl->ढाँचा_aead;

	snम_लिखो(alg->base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", पंचांगpl->name);
	snम_लिखो(alg->base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 पंचांगpl->driver_name);
	alg->base.cra_module = THIS_MODULE;
	alg->base.cra_priority = CC_CRA_PRIO;

	alg->base.cra_ctxsize = माप(काष्ठा cc_aead_ctx);
	alg->base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_KERN_DRIVER_ONLY;
	alg->base.cra_blocksize = पंचांगpl->blocksize;
	alg->init = cc_aead_init;
	alg->निकास = cc_aead_निकास;

	t_alg->aead_alg = *alg;

	t_alg->cipher_mode = पंचांगpl->cipher_mode;
	t_alg->flow_mode = पंचांगpl->flow_mode;
	t_alg->auth_mode = पंचांगpl->auth_mode;

	वापस t_alg;
पूर्ण

पूर्णांक cc_aead_मुक्त(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_crypto_alg *t_alg, *n;
	काष्ठा cc_aead_handle *aead_handle = drvdata->aead_handle;

	/* Remove रेजिस्टरed algs */
	list_क्रम_each_entry_safe(t_alg, n, &aead_handle->aead_list, entry) अणु
		crypto_unरेजिस्टर_aead(&t_alg->aead_alg);
		list_del(&t_alg->entry);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cc_aead_alloc(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_aead_handle *aead_handle;
	काष्ठा cc_crypto_alg *t_alg;
	पूर्णांक rc = -ENOMEM;
	पूर्णांक alg;
	काष्ठा device *dev = drvdata_to_dev(drvdata);

	aead_handle = devm_kदो_स्मृति(dev, माप(*aead_handle), GFP_KERNEL);
	अगर (!aead_handle) अणु
		rc = -ENOMEM;
		जाओ fail0;
	पूर्ण

	INIT_LIST_HEAD(&aead_handle->aead_list);
	drvdata->aead_handle = aead_handle;

	aead_handle->sram_workspace_addr = cc_sram_alloc(drvdata,
							 MAX_HMAC_DIGEST_SIZE);

	अगर (aead_handle->sram_workspace_addr == शून्य_SRAM_ADDR) अणु
		rc = -ENOMEM;
		जाओ fail1;
	पूर्ण

	/* Linux crypto */
	क्रम (alg = 0; alg < ARRAY_SIZE(aead_algs); alg++) अणु
		अगर ((aead_algs[alg].min_hw_rev > drvdata->hw_rev) ||
		    !(drvdata->std_bodies & aead_algs[alg].std_body))
			जारी;

		t_alg = cc_create_aead_alg(&aead_algs[alg], dev);
		अगर (IS_ERR(t_alg)) अणु
			rc = PTR_ERR(t_alg);
			dev_err(dev, "%s alg allocation failed\n",
				aead_algs[alg].driver_name);
			जाओ fail1;
		पूर्ण
		t_alg->drvdata = drvdata;
		rc = crypto_रेजिस्टर_aead(&t_alg->aead_alg);
		अगर (rc) अणु
			dev_err(dev, "%s alg registration failed\n",
				t_alg->aead_alg.base.cra_driver_name);
			जाओ fail1;
		पूर्ण

		list_add_tail(&t_alg->entry, &aead_handle->aead_list);
		dev_dbg(dev, "Registered %s\n",
			t_alg->aead_alg.base.cra_driver_name);
	पूर्ण

	वापस 0;

fail1:
	cc_aead_मुक्त(drvdata);
fail0:
	वापस rc;
पूर्ण
