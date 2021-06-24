<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/xts.h>
#समावेश <crypto/sm4.h>
#समावेश <crypto/scatterwalk.h>

#समावेश "cc_driver.h"
#समावेश "cc_lli_defs.h"
#समावेश "cc_buffer_mgr.h"
#समावेश "cc_cipher.h"
#समावेश "cc_request_mgr.h"

#घोषणा MAX_SKCIPHER_SEQ_LEN 6

#घोषणा ढाँचा_skcipher	ढाँचा_u.skcipher

काष्ठा cc_user_key_info अणु
	u8 *key;
	dma_addr_t key_dma_addr;
पूर्ण;

काष्ठा cc_hw_key_info अणु
	क्रमागत cc_hw_crypto_key key1_slot;
	क्रमागत cc_hw_crypto_key key2_slot;
पूर्ण;

काष्ठा cc_cpp_key_info अणु
	u8 slot;
	क्रमागत cc_cpp_alg alg;
पूर्ण;

क्रमागत cc_key_type अणु
	CC_UNPROTECTED_KEY,		/* User key */
	CC_HW_PROTECTED_KEY,		/* HW (FDE) key */
	CC_POLICY_PROTECTED_KEY,	/* CPP key */
	CC_INVALID_PROTECTED_KEY	/* Invalid key */
पूर्ण;

काष्ठा cc_cipher_ctx अणु
	काष्ठा cc_drvdata *drvdata;
	पूर्णांक keylen;
	पूर्णांक cipher_mode;
	पूर्णांक flow_mode;
	अचिन्हित पूर्णांक flags;
	क्रमागत cc_key_type key_type;
	काष्ठा cc_user_key_info user;
	जोड़ अणु
		काष्ठा cc_hw_key_info hw;
		काष्ठा cc_cpp_key_info cpp;
	पूर्ण;
	काष्ठा crypto_shash *shash_tfm;
	काष्ठा crypto_skcipher *fallback_tfm;
	bool fallback_on;
पूर्ण;

अटल व्योम cc_cipher_complete(काष्ठा device *dev, व्योम *cc_req, पूर्णांक err);

अटल अंतरभूत क्रमागत cc_key_type cc_key_type(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);

	वापस ctx_p->key_type;
पूर्ण

अटल पूर्णांक validate_keys_sizes(काष्ठा cc_cipher_ctx *ctx_p, u32 size)
अणु
	चयन (ctx_p->flow_mode) अणु
	हाल S_DIN_to_AES:
		चयन (size) अणु
		हाल CC_AES_128_BIT_KEY_SIZE:
		हाल CC_AES_192_BIT_KEY_SIZE:
			अगर (ctx_p->cipher_mode != DRV_CIPHER_XTS)
				वापस 0;
			अवरोध;
		हाल CC_AES_256_BIT_KEY_SIZE:
			वापस 0;
		हाल (CC_AES_192_BIT_KEY_SIZE * 2):
		हाल (CC_AES_256_BIT_KEY_SIZE * 2):
			अगर (ctx_p->cipher_mode == DRV_CIPHER_XTS ||
			    ctx_p->cipher_mode == DRV_CIPHER_ESSIV)
				वापस 0;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल S_DIN_to_DES:
		अगर (size == DES3_EDE_KEY_SIZE || size == DES_KEY_SIZE)
			वापस 0;
		अवरोध;
	हाल S_DIN_to_SM4:
		अगर (size == SM4_KEY_SIZE)
			वापस 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक validate_data_size(काष्ठा cc_cipher_ctx *ctx_p,
			      अचिन्हित पूर्णांक size)
अणु
	चयन (ctx_p->flow_mode) अणु
	हाल S_DIN_to_AES:
		चयन (ctx_p->cipher_mode) अणु
		हाल DRV_CIPHER_XTS:
		हाल DRV_CIPHER_CBC_CTS:
			अगर (size >= AES_BLOCK_SIZE)
				वापस 0;
			अवरोध;
		हाल DRV_CIPHER_OFB:
		हाल DRV_CIPHER_CTR:
				वापस 0;
		हाल DRV_CIPHER_ECB:
		हाल DRV_CIPHER_CBC:
		हाल DRV_CIPHER_ESSIV:
			अगर (IS_ALIGNED(size, AES_BLOCK_SIZE))
				वापस 0;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल S_DIN_to_DES:
		अगर (IS_ALIGNED(size, DES_BLOCK_SIZE))
			वापस 0;
		अवरोध;
	हाल S_DIN_to_SM4:
		चयन (ctx_p->cipher_mode) अणु
		हाल DRV_CIPHER_CTR:
			वापस 0;
		हाल DRV_CIPHER_ECB:
		हाल DRV_CIPHER_CBC:
			अगर (IS_ALIGNED(size, SM4_BLOCK_SIZE))
				वापस 0;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cc_cipher_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	काष्ठा cc_crypto_alg *cc_alg =
			container_of(tfm->__crt_alg, काष्ठा cc_crypto_alg,
				     skcipher_alg.base);
	काष्ठा device *dev = drvdata_to_dev(cc_alg->drvdata);
	अचिन्हित पूर्णांक max_key_buf_size = cc_alg->skcipher_alg.max_keysize;
	अचिन्हित पूर्णांक fallback_req_size = 0;

	dev_dbg(dev, "Initializing context @%p for %s\n", ctx_p,
		crypto_tfm_alg_name(tfm));

	ctx_p->cipher_mode = cc_alg->cipher_mode;
	ctx_p->flow_mode = cc_alg->flow_mode;
	ctx_p->drvdata = cc_alg->drvdata;

	अगर (ctx_p->cipher_mode == DRV_CIPHER_ESSIV) अणु
		स्थिर अक्षर *name = crypto_tfm_alg_name(tfm);

		/* Alloc hash tfm क्रम essiv */
		ctx_p->shash_tfm = crypto_alloc_shash("sha256", 0, 0);
		अगर (IS_ERR(ctx_p->shash_tfm)) अणु
			dev_err(dev, "Error allocating hash tfm for ESSIV.\n");
			वापस PTR_ERR(ctx_p->shash_tfm);
		पूर्ण
		max_key_buf_size <<= 1;

		/* Alloc fallabck tfm or essiv when key size != 256 bit */
		ctx_p->fallback_tfm =
			crypto_alloc_skcipher(name, 0, CRYPTO_ALG_NEED_FALLBACK | CRYPTO_ALG_ASYNC);

		अगर (IS_ERR(ctx_p->fallback_tfm)) अणु
			/* Note we're still allowing registration with no fallback since it's
			 * better to have most modes supported than none at all.
			 */
			dev_warn(dev, "Error allocating fallback algo %s. Some modes may be available.\n",
			       name);
			ctx_p->fallback_tfm = शून्य;
		पूर्ण अन्यथा अणु
			fallback_req_size = crypto_skcipher_reqsize(ctx_p->fallback_tfm);
		पूर्ण
	पूर्ण

	crypto_skcipher_set_reqsize(__crypto_skcipher_cast(tfm),
				    माप(काष्ठा cipher_req_ctx) + fallback_req_size);

	/* Allocate key buffer, cache line aligned */
	ctx_p->user.key = kzalloc(max_key_buf_size, GFP_KERNEL);
	अगर (!ctx_p->user.key)
		जाओ मुक्त_fallback;

	dev_dbg(dev, "Allocated key buffer in context. key=@%p\n",
		ctx_p->user.key);

	/* Map key buffer */
	ctx_p->user.key_dma_addr = dma_map_single(dev, ctx_p->user.key,
						  max_key_buf_size,
						  DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, ctx_p->user.key_dma_addr)) अणु
		dev_err(dev, "Mapping Key %u B at va=%pK for DMA failed\n",
			max_key_buf_size, ctx_p->user.key);
		जाओ मुक्त_key;
	पूर्ण
	dev_dbg(dev, "Mapped key %u B at va=%pK to dma=%pad\n",
		max_key_buf_size, ctx_p->user.key, &ctx_p->user.key_dma_addr);

	वापस 0;

मुक्त_key:
	kमुक्त(ctx_p->user.key);
मुक्त_fallback:
	crypto_मुक्त_skcipher(ctx_p->fallback_tfm);
	crypto_मुक्त_shash(ctx_p->shash_tfm);

	वापस -ENOMEM;
पूर्ण

अटल व्योम cc_cipher_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_alg *alg = tfm->__crt_alg;
	काष्ठा cc_crypto_alg *cc_alg =
			container_of(alg, काष्ठा cc_crypto_alg,
				     skcipher_alg.base);
	अचिन्हित पूर्णांक max_key_buf_size = cc_alg->skcipher_alg.max_keysize;
	काष्ठा cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx_p->drvdata);

	dev_dbg(dev, "Clearing context @%p for %s\n",
		crypto_tfm_ctx(tfm), crypto_tfm_alg_name(tfm));

	अगर (ctx_p->cipher_mode == DRV_CIPHER_ESSIV) अणु
		/* Free hash tfm क्रम essiv */
		crypto_मुक्त_shash(ctx_p->shash_tfm);
		ctx_p->shash_tfm = शून्य;
		crypto_मुक्त_skcipher(ctx_p->fallback_tfm);
		ctx_p->fallback_tfm = शून्य;
	पूर्ण

	/* Unmap key buffer */
	dma_unmap_single(dev, ctx_p->user.key_dma_addr, max_key_buf_size,
			 DMA_TO_DEVICE);
	dev_dbg(dev, "Unmapped key buffer key_dma_addr=%pad\n",
		&ctx_p->user.key_dma_addr);

	/* Free key buffer in context */
	kमुक्त_sensitive(ctx_p->user.key);
	dev_dbg(dev, "Free key buffer in context. key=@%p\n", ctx_p->user.key);
पूर्ण

काष्ठा tdes_keys अणु
	u8	key1[DES_KEY_SIZE];
	u8	key2[DES_KEY_SIZE];
	u8	key3[DES_KEY_SIZE];
पूर्ण;

अटल क्रमागत cc_hw_crypto_key cc_slot_to_hw_key(u8 slot_num)
अणु
	चयन (slot_num) अणु
	हाल 0:
		वापस KFDE0_KEY;
	हाल 1:
		वापस KFDE1_KEY;
	हाल 2:
		वापस KFDE2_KEY;
	हाल 3:
		वापस KFDE3_KEY;
	पूर्ण
	वापस END_OF_KEYS;
पूर्ण

अटल u8 cc_slot_to_cpp_key(u8 slot_num)
अणु
	वापस (slot_num - CC_FIRST_CPP_KEY_SLOT);
पूर्ण

अटल अंतरभूत क्रमागत cc_key_type cc_slot_to_key_type(u8 slot_num)
अणु
	अगर (slot_num >= CC_FIRST_HW_KEY_SLOT && slot_num <= CC_LAST_HW_KEY_SLOT)
		वापस CC_HW_PROTECTED_KEY;
	अन्यथा अगर (slot_num >=  CC_FIRST_CPP_KEY_SLOT &&
		 slot_num <=  CC_LAST_CPP_KEY_SLOT)
		वापस CC_POLICY_PROTECTED_KEY;
	अन्यथा
		वापस CC_INVALID_PROTECTED_KEY;
पूर्ण

अटल पूर्णांक cc_cipher_sethkey(काष्ठा crypto_skcipher *sktfm, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(sktfm);
	काष्ठा cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx_p->drvdata);
	काष्ठा cc_hkey_info hki;

	dev_dbg(dev, "Setting HW key in context @%p for %s. keylen=%u\n",
		ctx_p, crypto_tfm_alg_name(tfm), keylen);
	dump_byte_array("key", key, keylen);

	/* STAT_PHASE_0: Init and sanity checks */

	/* This check the size of the रक्षित key token */
	अगर (keylen != माप(hki)) अणु
		dev_err(dev, "Unsupported protected key size %d.\n", keylen);
		वापस -EINVAL;
	पूर्ण

	स_नकल(&hki, key, keylen);

	/* The real key len क्रम crypto op is the size of the HW key
	 * referenced by the HW key slot, not the hardware key token
	 */
	keylen = hki.keylen;

	अगर (validate_keys_sizes(ctx_p, keylen)) अणु
		dev_dbg(dev, "Unsupported key size %d.\n", keylen);
		वापस -EINVAL;
	पूर्ण

	ctx_p->keylen = keylen;
	ctx_p->fallback_on = false;

	चयन (cc_slot_to_key_type(hki.hw_key1)) अणु
	हाल CC_HW_PROTECTED_KEY:
		अगर (ctx_p->flow_mode == S_DIN_to_SM4) अणु
			dev_err(dev, "Only AES HW protected keys are supported\n");
			वापस -EINVAL;
		पूर्ण

		ctx_p->hw.key1_slot = cc_slot_to_hw_key(hki.hw_key1);
		अगर (ctx_p->hw.key1_slot == END_OF_KEYS) अणु
			dev_err(dev, "Unsupported hw key1 number (%d)\n",
				hki.hw_key1);
			वापस -EINVAL;
		पूर्ण

		अगर (ctx_p->cipher_mode == DRV_CIPHER_XTS ||
		    ctx_p->cipher_mode == DRV_CIPHER_ESSIV) अणु
			अगर (hki.hw_key1 == hki.hw_key2) अणु
				dev_err(dev, "Illegal hw key numbers (%d,%d)\n",
					hki.hw_key1, hki.hw_key2);
				वापस -EINVAL;
			पूर्ण

			ctx_p->hw.key2_slot = cc_slot_to_hw_key(hki.hw_key2);
			अगर (ctx_p->hw.key2_slot == END_OF_KEYS) अणु
				dev_err(dev, "Unsupported hw key2 number (%d)\n",
					hki.hw_key2);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		ctx_p->key_type = CC_HW_PROTECTED_KEY;
		dev_dbg(dev, "HW protected key  %d/%d set\n.",
			ctx_p->hw.key1_slot, ctx_p->hw.key2_slot);
		अवरोध;

	हाल CC_POLICY_PROTECTED_KEY:
		अगर (ctx_p->drvdata->hw_rev < CC_HW_REV_713) अणु
			dev_err(dev, "CPP keys not supported in this hardware revision.\n");
			वापस -EINVAL;
		पूर्ण

		अगर (ctx_p->cipher_mode != DRV_CIPHER_CBC &&
		    ctx_p->cipher_mode != DRV_CIPHER_CTR) अणु
			dev_err(dev, "CPP keys only supported in CBC or CTR modes.\n");
			वापस -EINVAL;
		पूर्ण

		ctx_p->cpp.slot = cc_slot_to_cpp_key(hki.hw_key1);
		अगर (ctx_p->flow_mode == S_DIN_to_AES)
			ctx_p->cpp.alg = CC_CPP_AES;
		अन्यथा /* Must be SM4 since due to sethkey registration */
			ctx_p->cpp.alg = CC_CPP_SM4;
		ctx_p->key_type = CC_POLICY_PROTECTED_KEY;
		dev_dbg(dev, "policy protected key alg: %d slot: %d.\n",
			ctx_p->cpp.alg, ctx_p->cpp.slot);
		अवरोध;

	शेष:
		dev_err(dev, "Unsupported protected key (%d)\n", hki.hw_key1);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cc_cipher_setkey(काष्ठा crypto_skcipher *sktfm, स्थिर u8 *key,
			    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(sktfm);
	काष्ठा cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx_p->drvdata);
	काष्ठा cc_crypto_alg *cc_alg =
			container_of(tfm->__crt_alg, काष्ठा cc_crypto_alg,
				     skcipher_alg.base);
	अचिन्हित पूर्णांक max_key_buf_size = cc_alg->skcipher_alg.max_keysize;

	dev_dbg(dev, "Setting key in context @%p for %s. keylen=%u\n",
		ctx_p, crypto_tfm_alg_name(tfm), keylen);
	dump_byte_array("key", key, keylen);

	/* STAT_PHASE_0: Init and sanity checks */

	अगर (validate_keys_sizes(ctx_p, keylen)) अणु
		dev_dbg(dev, "Invalid key size %d.\n", keylen);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx_p->cipher_mode == DRV_CIPHER_ESSIV) अणु

		/* We only support 256 bit ESSIV-CBC-AES keys */
		अगर (keylen != AES_KEYSIZE_256)  अणु
			अचिन्हित पूर्णांक flags = crypto_tfm_get_flags(tfm) & CRYPTO_TFM_REQ_MASK;

			अगर (likely(ctx_p->fallback_tfm)) अणु
				ctx_p->fallback_on = true;
				crypto_skcipher_clear_flags(ctx_p->fallback_tfm,
							    CRYPTO_TFM_REQ_MASK);
				crypto_skcipher_clear_flags(ctx_p->fallback_tfm, flags);
				वापस crypto_skcipher_setkey(ctx_p->fallback_tfm, key, keylen);
			पूर्ण

			dev_dbg(dev, "Unsupported key size %d and no fallback.\n", keylen);
			वापस -EINVAL;
		पूर्ण

		/* Internal ESSIV key buffer is द्विगुन sized */
		max_key_buf_size <<= 1;
	पूर्ण

	ctx_p->fallback_on = false;
	ctx_p->key_type = CC_UNPROTECTED_KEY;

	/*
	 * Verअगरy DES weak keys
	 * Note that we're dropping the expanded key since the
	 * HW करोes the expansion on its own.
	 */
	अगर (ctx_p->flow_mode == S_DIN_to_DES) अणु
		अगर ((keylen == DES3_EDE_KEY_SIZE &&
		     verअगरy_skcipher_des3_key(sktfm, key)) ||
		    verअगरy_skcipher_des_key(sktfm, key)) अणु
			dev_dbg(dev, "weak DES key");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (ctx_p->cipher_mode == DRV_CIPHER_XTS &&
	    xts_check_key(tfm, key, keylen)) अणु
		dev_dbg(dev, "weak XTS key");
		वापस -EINVAL;
	पूर्ण

	/* STAT_PHASE_1: Copy key to ctx */
	dma_sync_single_क्रम_cpu(dev, ctx_p->user.key_dma_addr,
				max_key_buf_size, DMA_TO_DEVICE);

	स_नकल(ctx_p->user.key, key, keylen);

	अगर (ctx_p->cipher_mode == DRV_CIPHER_ESSIV) अणु
		/* sha256 क्रम key2 - use sw implementation */
		पूर्णांक err;

		err = crypto_shash_tfm_digest(ctx_p->shash_tfm,
					      ctx_p->user.key, keylen,
					      ctx_p->user.key + keylen);
		अगर (err) अणु
			dev_err(dev, "Failed to hash ESSIV key.\n");
			वापस err;
		पूर्ण

		keylen <<= 1;
	पूर्ण
	dma_sync_single_क्रम_device(dev, ctx_p->user.key_dma_addr,
				   max_key_buf_size, DMA_TO_DEVICE);
	ctx_p->keylen = keylen;

	dev_dbg(dev, "return safely");
	वापस 0;
पूर्ण

अटल पूर्णांक cc_out_setup_mode(काष्ठा cc_cipher_ctx *ctx_p)
अणु
	चयन (ctx_p->flow_mode) अणु
	हाल S_DIN_to_AES:
		वापस S_AES_to_DOUT;
	हाल S_DIN_to_DES:
		वापस S_DES_to_DOUT;
	हाल S_DIN_to_SM4:
		वापस S_SM4_to_DOUT;
	शेष:
		वापस ctx_p->flow_mode;
	पूर्ण
पूर्ण

अटल व्योम cc_setup_पढ़ोiv_desc(काष्ठा crypto_tfm *tfm,
				 काष्ठा cipher_req_ctx *req_ctx,
				 अचिन्हित पूर्णांक ivsize, काष्ठा cc_hw_desc desc[],
				 अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx_p->drvdata);
	पूर्णांक cipher_mode = ctx_p->cipher_mode;
	पूर्णांक flow_mode = cc_out_setup_mode(ctx_p);
	पूर्णांक direction = req_ctx->gen_ctx.op_type;
	dma_addr_t iv_dma_addr = req_ctx->gen_ctx.iv_dma_addr;

	अगर (ctx_p->key_type == CC_POLICY_PROTECTED_KEY)
		वापस;

	चयन (cipher_mode) अणु
	हाल DRV_CIPHER_ECB:
		अवरोध;
	हाल DRV_CIPHER_CBC:
	हाल DRV_CIPHER_CBC_CTS:
	हाल DRV_CIPHER_CTR:
	हाल DRV_CIPHER_OFB:
		/* Read next IV */
		hw_desc_init(&desc[*seq_size]);
		set_करोut_dlli(&desc[*seq_size], iv_dma_addr, ivsize, NS_BIT, 1);
		set_cipher_config0(&desc[*seq_size], direction);
		set_flow_mode(&desc[*seq_size], flow_mode);
		set_cipher_mode(&desc[*seq_size], cipher_mode);
		अगर (cipher_mode == DRV_CIPHER_CTR ||
		    cipher_mode == DRV_CIPHER_OFB) अणु
			set_setup_mode(&desc[*seq_size], SETUP_WRITE_STATE1);
		पूर्ण अन्यथा अणु
			set_setup_mode(&desc[*seq_size], SETUP_WRITE_STATE0);
		पूर्ण
		set_queue_last_ind(ctx_p->drvdata, &desc[*seq_size]);
		(*seq_size)++;
		अवरोध;
	हाल DRV_CIPHER_XTS:
	हाल DRV_CIPHER_ESSIV:
		/*  IV */
		hw_desc_init(&desc[*seq_size]);
		set_setup_mode(&desc[*seq_size], SETUP_WRITE_STATE1);
		set_cipher_mode(&desc[*seq_size], cipher_mode);
		set_cipher_config0(&desc[*seq_size], direction);
		set_flow_mode(&desc[*seq_size], flow_mode);
		set_करोut_dlli(&desc[*seq_size], iv_dma_addr, CC_AES_BLOCK_SIZE,
			     NS_BIT, 1);
		set_queue_last_ind(ctx_p->drvdata, &desc[*seq_size]);
		(*seq_size)++;
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported cipher mode (%d)\n", cipher_mode);
	पूर्ण
पूर्ण


अटल व्योम cc_setup_state_desc(काष्ठा crypto_tfm *tfm,
				 काष्ठा cipher_req_ctx *req_ctx,
				 अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक nbytes,
				 काष्ठा cc_hw_desc desc[],
				 अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx_p->drvdata);
	पूर्णांक cipher_mode = ctx_p->cipher_mode;
	पूर्णांक flow_mode = ctx_p->flow_mode;
	पूर्णांक direction = req_ctx->gen_ctx.op_type;
	dma_addr_t iv_dma_addr = req_ctx->gen_ctx.iv_dma_addr;

	चयन (cipher_mode) अणु
	हाल DRV_CIPHER_ECB:
		अवरोध;
	हाल DRV_CIPHER_CBC:
	हाल DRV_CIPHER_CBC_CTS:
	हाल DRV_CIPHER_CTR:
	हाल DRV_CIPHER_OFB:
		/* Load IV */
		hw_desc_init(&desc[*seq_size]);
		set_din_type(&desc[*seq_size], DMA_DLLI, iv_dma_addr, ivsize,
			     NS_BIT);
		set_cipher_config0(&desc[*seq_size], direction);
		set_flow_mode(&desc[*seq_size], flow_mode);
		set_cipher_mode(&desc[*seq_size], cipher_mode);
		अगर (cipher_mode == DRV_CIPHER_CTR ||
		    cipher_mode == DRV_CIPHER_OFB) अणु
			set_setup_mode(&desc[*seq_size], SETUP_LOAD_STATE1);
		पूर्ण अन्यथा अणु
			set_setup_mode(&desc[*seq_size], SETUP_LOAD_STATE0);
		पूर्ण
		(*seq_size)++;
		अवरोध;
	हाल DRV_CIPHER_XTS:
	हाल DRV_CIPHER_ESSIV:
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported cipher mode (%d)\n", cipher_mode);
	पूर्ण
पूर्ण


अटल व्योम cc_setup_xex_state_desc(काष्ठा crypto_tfm *tfm,
				 काष्ठा cipher_req_ctx *req_ctx,
				 अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक nbytes,
				 काष्ठा cc_hw_desc desc[],
				 अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx_p->drvdata);
	पूर्णांक cipher_mode = ctx_p->cipher_mode;
	पूर्णांक flow_mode = ctx_p->flow_mode;
	पूर्णांक direction = req_ctx->gen_ctx.op_type;
	dma_addr_t key_dma_addr = ctx_p->user.key_dma_addr;
	अचिन्हित पूर्णांक key_len = (ctx_p->keylen / 2);
	dma_addr_t iv_dma_addr = req_ctx->gen_ctx.iv_dma_addr;
	अचिन्हित पूर्णांक key_offset = key_len;

	चयन (cipher_mode) अणु
	हाल DRV_CIPHER_ECB:
		अवरोध;
	हाल DRV_CIPHER_CBC:
	हाल DRV_CIPHER_CBC_CTS:
	हाल DRV_CIPHER_CTR:
	हाल DRV_CIPHER_OFB:
		अवरोध;
	हाल DRV_CIPHER_XTS:
	हाल DRV_CIPHER_ESSIV:

		अगर (cipher_mode == DRV_CIPHER_ESSIV)
			key_len = SHA256_DIGEST_SIZE;

		/* load XEX key */
		hw_desc_init(&desc[*seq_size]);
		set_cipher_mode(&desc[*seq_size], cipher_mode);
		set_cipher_config0(&desc[*seq_size], direction);
		अगर (cc_key_type(tfm) == CC_HW_PROTECTED_KEY) अणु
			set_hw_crypto_key(&desc[*seq_size],
					  ctx_p->hw.key2_slot);
		पूर्ण अन्यथा अणु
			set_din_type(&desc[*seq_size], DMA_DLLI,
				     (key_dma_addr + key_offset),
				     key_len, NS_BIT);
		पूर्ण
		set_xex_data_unit_size(&desc[*seq_size], nbytes);
		set_flow_mode(&desc[*seq_size], S_DIN_to_AES2);
		set_key_size_aes(&desc[*seq_size], key_len);
		set_setup_mode(&desc[*seq_size], SETUP_LOAD_XEX_KEY);
		(*seq_size)++;

		/* Load IV */
		hw_desc_init(&desc[*seq_size]);
		set_setup_mode(&desc[*seq_size], SETUP_LOAD_STATE1);
		set_cipher_mode(&desc[*seq_size], cipher_mode);
		set_cipher_config0(&desc[*seq_size], direction);
		set_key_size_aes(&desc[*seq_size], key_len);
		set_flow_mode(&desc[*seq_size], flow_mode);
		set_din_type(&desc[*seq_size], DMA_DLLI, iv_dma_addr,
			     CC_AES_BLOCK_SIZE, NS_BIT);
		(*seq_size)++;
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported cipher mode (%d)\n", cipher_mode);
	पूर्ण
पूर्ण

अटल पूर्णांक cc_out_flow_mode(काष्ठा cc_cipher_ctx *ctx_p)
अणु
	चयन (ctx_p->flow_mode) अणु
	हाल S_DIN_to_AES:
		वापस DIN_AES_DOUT;
	हाल S_DIN_to_DES:
		वापस DIN_DES_DOUT;
	हाल S_DIN_to_SM4:
		वापस DIN_SM4_DOUT;
	शेष:
		वापस ctx_p->flow_mode;
	पूर्ण
पूर्ण

अटल व्योम cc_setup_key_desc(काष्ठा crypto_tfm *tfm,
			      काष्ठा cipher_req_ctx *req_ctx,
			      अचिन्हित पूर्णांक nbytes, काष्ठा cc_hw_desc desc[],
			      अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx_p->drvdata);
	पूर्णांक cipher_mode = ctx_p->cipher_mode;
	पूर्णांक flow_mode = ctx_p->flow_mode;
	पूर्णांक direction = req_ctx->gen_ctx.op_type;
	dma_addr_t key_dma_addr = ctx_p->user.key_dma_addr;
	अचिन्हित पूर्णांक key_len = ctx_p->keylen;
	अचिन्हित पूर्णांक din_size;

	चयन (cipher_mode) अणु
	हाल DRV_CIPHER_CBC:
	हाल DRV_CIPHER_CBC_CTS:
	हाल DRV_CIPHER_CTR:
	हाल DRV_CIPHER_OFB:
	हाल DRV_CIPHER_ECB:
		/* Load key */
		hw_desc_init(&desc[*seq_size]);
		set_cipher_mode(&desc[*seq_size], cipher_mode);
		set_cipher_config0(&desc[*seq_size], direction);

		अगर (cc_key_type(tfm) == CC_POLICY_PROTECTED_KEY) अणु
			/* We use the AES key size coding क्रम all CPP algs */
			set_key_size_aes(&desc[*seq_size], key_len);
			set_cpp_crypto_key(&desc[*seq_size], ctx_p->cpp.slot);
			flow_mode = cc_out_flow_mode(ctx_p);
		पूर्ण अन्यथा अणु
			अगर (flow_mode == S_DIN_to_AES) अणु
				अगर (cc_key_type(tfm) == CC_HW_PROTECTED_KEY) अणु
					set_hw_crypto_key(&desc[*seq_size],
							  ctx_p->hw.key1_slot);
				पूर्ण अन्यथा अणु
					/* CC_POLICY_UNPROTECTED_KEY
					 * Invalid keys are filtered out in
					 * sethkey()
					 */
					din_size = (key_len == 24) ?
						AES_MAX_KEY_SIZE : key_len;

					set_din_type(&desc[*seq_size], DMA_DLLI,
						     key_dma_addr, din_size,
						     NS_BIT);
				पूर्ण
				set_key_size_aes(&desc[*seq_size], key_len);
			पूर्ण अन्यथा अणु
				/*des*/
				set_din_type(&desc[*seq_size], DMA_DLLI,
					     key_dma_addr, key_len, NS_BIT);
				set_key_size_des(&desc[*seq_size], key_len);
			पूर्ण
			set_setup_mode(&desc[*seq_size], SETUP_LOAD_KEY0);
		पूर्ण
		set_flow_mode(&desc[*seq_size], flow_mode);
		(*seq_size)++;
		अवरोध;
	हाल DRV_CIPHER_XTS:
	हाल DRV_CIPHER_ESSIV:
		/* Load AES key */
		hw_desc_init(&desc[*seq_size]);
		set_cipher_mode(&desc[*seq_size], cipher_mode);
		set_cipher_config0(&desc[*seq_size], direction);
		अगर (cc_key_type(tfm) == CC_HW_PROTECTED_KEY) अणु
			set_hw_crypto_key(&desc[*seq_size],
					  ctx_p->hw.key1_slot);
		पूर्ण अन्यथा अणु
			set_din_type(&desc[*seq_size], DMA_DLLI, key_dma_addr,
				     (key_len / 2), NS_BIT);
		पूर्ण
		set_key_size_aes(&desc[*seq_size], (key_len / 2));
		set_flow_mode(&desc[*seq_size], flow_mode);
		set_setup_mode(&desc[*seq_size], SETUP_LOAD_KEY0);
		(*seq_size)++;
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported cipher mode (%d)\n", cipher_mode);
	पूर्ण
पूर्ण

अटल व्योम cc_setup_mlli_desc(काष्ठा crypto_tfm *tfm,
			       काष्ठा cipher_req_ctx *req_ctx,
			       काष्ठा scatterlist *dst, काष्ठा scatterlist *src,
			       अचिन्हित पूर्णांक nbytes, व्योम *areq,
			       काष्ठा cc_hw_desc desc[], अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx_p->drvdata);

	अगर (req_ctx->dma_buf_type == CC_DMA_BUF_MLLI) अणु
		/* bypass */
		dev_dbg(dev, " bypass params addr %pad length 0x%X addr 0x%08X\n",
			&req_ctx->mlli_params.mlli_dma_addr,
			req_ctx->mlli_params.mlli_len,
			ctx_p->drvdata->mlli_sram_addr);
		hw_desc_init(&desc[*seq_size]);
		set_din_type(&desc[*seq_size], DMA_DLLI,
			     req_ctx->mlli_params.mlli_dma_addr,
			     req_ctx->mlli_params.mlli_len, NS_BIT);
		set_करोut_sram(&desc[*seq_size],
			      ctx_p->drvdata->mlli_sram_addr,
			      req_ctx->mlli_params.mlli_len);
		set_flow_mode(&desc[*seq_size], BYPASS);
		(*seq_size)++;
	पूर्ण
पूर्ण

अटल व्योम cc_setup_flow_desc(काष्ठा crypto_tfm *tfm,
			       काष्ठा cipher_req_ctx *req_ctx,
			       काष्ठा scatterlist *dst, काष्ठा scatterlist *src,
			       अचिन्हित पूर्णांक nbytes, काष्ठा cc_hw_desc desc[],
			       अचिन्हित पूर्णांक *seq_size)
अणु
	काष्ठा cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx_p->drvdata);
	अचिन्हित पूर्णांक flow_mode = cc_out_flow_mode(ctx_p);
	bool last_desc = (ctx_p->key_type == CC_POLICY_PROTECTED_KEY ||
			  ctx_p->cipher_mode == DRV_CIPHER_ECB);

	/* Process */
	अगर (req_ctx->dma_buf_type == CC_DMA_BUF_DLLI) अणु
		dev_dbg(dev, " data params addr %pad length 0x%X\n",
			&sg_dma_address(src), nbytes);
		dev_dbg(dev, " data params addr %pad length 0x%X\n",
			&sg_dma_address(dst), nbytes);
		hw_desc_init(&desc[*seq_size]);
		set_din_type(&desc[*seq_size], DMA_DLLI, sg_dma_address(src),
			     nbytes, NS_BIT);
		set_करोut_dlli(&desc[*seq_size], sg_dma_address(dst),
			      nbytes, NS_BIT, (!last_desc ? 0 : 1));
		अगर (last_desc)
			set_queue_last_ind(ctx_p->drvdata, &desc[*seq_size]);

		set_flow_mode(&desc[*seq_size], flow_mode);
		(*seq_size)++;
	पूर्ण अन्यथा अणु
		hw_desc_init(&desc[*seq_size]);
		set_din_type(&desc[*seq_size], DMA_MLLI,
			     ctx_p->drvdata->mlli_sram_addr,
			     req_ctx->in_mlli_nents, NS_BIT);
		अगर (req_ctx->out_nents == 0) अणु
			dev_dbg(dev, " din/dout params addr 0x%08X addr 0x%08X\n",
				ctx_p->drvdata->mlli_sram_addr,
				ctx_p->drvdata->mlli_sram_addr);
			set_करोut_mlli(&desc[*seq_size],
				      ctx_p->drvdata->mlli_sram_addr,
				      req_ctx->in_mlli_nents, NS_BIT,
				      (!last_desc ? 0 : 1));
		पूर्ण अन्यथा अणु
			dev_dbg(dev, " din/dout params addr 0x%08X addr 0x%08X\n",
				ctx_p->drvdata->mlli_sram_addr,
				ctx_p->drvdata->mlli_sram_addr +
				(u32)LLI_ENTRY_BYTE_SIZE * req_ctx->in_nents);
			set_करोut_mlli(&desc[*seq_size],
				      (ctx_p->drvdata->mlli_sram_addr +
				       (LLI_ENTRY_BYTE_SIZE *
					req_ctx->in_mlli_nents)),
				      req_ctx->out_mlli_nents, NS_BIT,
				      (!last_desc ? 0 : 1));
		पूर्ण
		अगर (last_desc)
			set_queue_last_ind(ctx_p->drvdata, &desc[*seq_size]);

		set_flow_mode(&desc[*seq_size], flow_mode);
		(*seq_size)++;
	पूर्ण
पूर्ण

अटल व्योम cc_cipher_complete(काष्ठा device *dev, व्योम *cc_req, पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = (काष्ठा skcipher_request *)cc_req;
	काष्ठा scatterlist *dst = req->dst;
	काष्ठा scatterlist *src = req->src;
	काष्ठा cipher_req_ctx *req_ctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *sk_tfm = crypto_skcipher_reqtfm(req);
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(sk_tfm);

	अगर (err != -EINPROGRESS) अणु
		/* Not a BACKLOG notअगरication */
		cc_unmap_cipher_request(dev, req_ctx, ivsize, src, dst);
		स_नकल(req->iv, req_ctx->iv, ivsize);
		kमुक्त_sensitive(req_ctx->iv);
	पूर्ण

	skcipher_request_complete(req, err);
पूर्ण

अटल पूर्णांक cc_cipher_process(काष्ठा skcipher_request *req,
			     क्रमागत drv_crypto_direction direction)
अणु
	काष्ठा crypto_skcipher *sk_tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(sk_tfm);
	काष्ठा cipher_req_ctx *req_ctx = skcipher_request_ctx(req);
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(sk_tfm);
	काष्ठा scatterlist *dst = req->dst;
	काष्ठा scatterlist *src = req->src;
	अचिन्हित पूर्णांक nbytes = req->cryptlen;
	व्योम *iv = req->iv;
	काष्ठा cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	काष्ठा device *dev = drvdata_to_dev(ctx_p->drvdata);
	काष्ठा cc_hw_desc desc[MAX_SKCIPHER_SEQ_LEN];
	काष्ठा cc_crypto_req cc_req = अणुपूर्ण;
	पूर्णांक rc;
	अचिन्हित पूर्णांक seq_len = 0;
	gfp_t flags = cc_gfp_flags(&req->base);

	dev_dbg(dev, "%s req=%p iv=%p nbytes=%d\n",
		((direction == DRV_CRYPTO_सूचीECTION_ENCRYPT) ?
		"Encrypt" : "Decrypt"), req, iv, nbytes);

	/* STAT_PHASE_0: Init and sanity checks */

	अगर (validate_data_size(ctx_p, nbytes)) अणु
		dev_dbg(dev, "Unsupported data size %d.\n", nbytes);
		rc = -EINVAL;
		जाओ निकास_process;
	पूर्ण
	अगर (nbytes == 0) अणु
		/* No data to process is valid */
		rc = 0;
		जाओ निकास_process;
	पूर्ण

	अगर (ctx_p->fallback_on) अणु
		काष्ठा skcipher_request *subreq = skcipher_request_ctx(req);

		*subreq = *req;
		skcipher_request_set_tfm(subreq, ctx_p->fallback_tfm);
		अगर (direction == DRV_CRYPTO_सूचीECTION_ENCRYPT)
			वापस crypto_skcipher_encrypt(subreq);
		अन्यथा
			वापस crypto_skcipher_decrypt(subreq);
	पूर्ण

	/* The IV we are handed may be allocated from the stack so
	 * we must copy it to a DMAable buffer beक्रमe use.
	 */
	req_ctx->iv = kmemdup(iv, ivsize, flags);
	अगर (!req_ctx->iv) अणु
		rc = -ENOMEM;
		जाओ निकास_process;
	पूर्ण

	/* Setup request काष्ठाure */
	cc_req.user_cb = cc_cipher_complete;
	cc_req.user_arg = req;

	/* Setup CPP operation details */
	अगर (ctx_p->key_type == CC_POLICY_PROTECTED_KEY) अणु
		cc_req.cpp.is_cpp = true;
		cc_req.cpp.alg = ctx_p->cpp.alg;
		cc_req.cpp.slot = ctx_p->cpp.slot;
	पूर्ण

	/* Setup request context */
	req_ctx->gen_ctx.op_type = direction;

	/* STAT_PHASE_1: Map buffers */

	rc = cc_map_cipher_request(ctx_p->drvdata, req_ctx, ivsize, nbytes,
				      req_ctx->iv, src, dst, flags);
	अगर (rc) अणु
		dev_err(dev, "map_request() failed\n");
		जाओ निकास_process;
	पूर्ण

	/* STAT_PHASE_2: Create sequence */

	/* Setup state (IV)  */
	cc_setup_state_desc(tfm, req_ctx, ivsize, nbytes, desc, &seq_len);
	/* Setup MLLI line, अगर needed */
	cc_setup_mlli_desc(tfm, req_ctx, dst, src, nbytes, req, desc, &seq_len);
	/* Setup key */
	cc_setup_key_desc(tfm, req_ctx, nbytes, desc, &seq_len);
	/* Setup state (IV and XEX key)  */
	cc_setup_xex_state_desc(tfm, req_ctx, ivsize, nbytes, desc, &seq_len);
	/* Data processing */
	cc_setup_flow_desc(tfm, req_ctx, dst, src, nbytes, desc, &seq_len);
	/* Read next IV */
	cc_setup_पढ़ोiv_desc(tfm, req_ctx, ivsize, desc, &seq_len);

	/* STAT_PHASE_3: Lock HW and push sequence */

	rc = cc_send_request(ctx_p->drvdata, &cc_req, desc, seq_len,
			     &req->base);
	अगर (rc != -EINPROGRESS && rc != -EBUSY) अणु
		/* Failed to send the request or request completed
		 * synchronously
		 */
		cc_unmap_cipher_request(dev, req_ctx, ivsize, src, dst);
	पूर्ण

निकास_process:
	अगर (rc != -EINPROGRESS && rc != -EBUSY) अणु
		kमुक्त_sensitive(req_ctx->iv);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक cc_cipher_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा cipher_req_ctx *req_ctx = skcipher_request_ctx(req);

	स_रखो(req_ctx, 0, माप(*req_ctx));

	वापस cc_cipher_process(req, DRV_CRYPTO_सूचीECTION_ENCRYPT);
पूर्ण

अटल पूर्णांक cc_cipher_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा cipher_req_ctx *req_ctx = skcipher_request_ctx(req);

	स_रखो(req_ctx, 0, माप(*req_ctx));

	वापस cc_cipher_process(req, DRV_CRYPTO_सूचीECTION_DECRYPT);
पूर्ण

/* Block cipher alg */
अटल स्थिर काष्ठा cc_alg_ढाँचा skcipher_algs[] = अणु
	अणु
		.name = "xts(paes)",
		.driver_name = "xts-paes-ccree",
		.blocksize = 1,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_sethkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_XTS,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
		.sec_func = true,
	पूर्ण,
	अणु
		.name = "essiv(cbc(paes),sha256)",
		.driver_name = "essiv-paes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_sethkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_ESSIV,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_712,
		.std_body = CC_STD_NIST,
		.sec_func = true,
	पूर्ण,
	अणु
		.name = "ecb(paes)",
		.driver_name = "ecb-paes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_sethkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = 0,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_ECB,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_712,
		.std_body = CC_STD_NIST,
		.sec_func = true,
	पूर्ण,
	अणु
		.name = "cbc(paes)",
		.driver_name = "cbc-paes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_sethkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_CBC,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_712,
		.std_body = CC_STD_NIST,
		.sec_func = true,
	पूर्ण,
	अणु
		.name = "ofb(paes)",
		.driver_name = "ofb-paes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_sethkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_OFB,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_712,
		.std_body = CC_STD_NIST,
		.sec_func = true,
	पूर्ण,
	अणु
		.name = "cts(cbc(paes))",
		.driver_name = "cts-cbc-paes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_sethkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_CBC_CTS,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_712,
		.std_body = CC_STD_NIST,
		.sec_func = true,
	पूर्ण,
	अणु
		.name = "ctr(paes)",
		.driver_name = "ctr-paes-ccree",
		.blocksize = 1,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_sethkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_CTR,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_712,
		.std_body = CC_STD_NIST,
		.sec_func = true,
	पूर्ण,
	अणु
		/* See https://www.mail-archive.com/linux-crypto@vger.kernel.org/msg40576.hपंचांगl
		 * क्रम the reason why this dअगरfers from the generic
		 * implementation.
		 */
		.name = "xts(aes)",
		.driver_name = "xts-aes-ccree",
		.blocksize = 1,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE * 2,
			.max_keysize = AES_MAX_KEY_SIZE * 2,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_XTS,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "essiv(cbc(aes),sha256)",
		.driver_name = "essiv-aes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_ESSIV,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_712,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "ecb(aes)",
		.driver_name = "ecb-aes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = 0,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_ECB,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "cbc(aes)",
		.driver_name = "cbc-aes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
		पूर्ण,
		.cipher_mode = DRV_CIPHER_CBC,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "ofb(aes)",
		.driver_name = "ofb-aes-ccree",
		.blocksize = 1,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_OFB,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "cts(cbc(aes))",
		.driver_name = "cts-cbc-aes-ccree",
		.blocksize = AES_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_CBC_CTS,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "ctr(aes)",
		.driver_name = "ctr-aes-ccree",
		.blocksize = 1,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_CTR,
		.flow_mode = S_DIN_to_AES,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "cbc(des3_ede)",
		.driver_name = "cbc-3des-ccree",
		.blocksize = DES3_EDE_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_CBC,
		.flow_mode = S_DIN_to_DES,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "ecb(des3_ede)",
		.driver_name = "ecb-3des-ccree",
		.blocksize = DES3_EDE_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = 0,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_ECB,
		.flow_mode = S_DIN_to_DES,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "cbc(des)",
		.driver_name = "cbc-des-ccree",
		.blocksize = DES_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = DES_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_CBC,
		.flow_mode = S_DIN_to_DES,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "ecb(des)",
		.driver_name = "ecb-des-ccree",
		.blocksize = DES_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = 0,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_ECB,
		.flow_mode = S_DIN_to_DES,
		.min_hw_rev = CC_HW_REV_630,
		.std_body = CC_STD_NIST,
	पूर्ण,
	अणु
		.name = "cbc(sm4)",
		.driver_name = "cbc-sm4-ccree",
		.blocksize = SM4_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = SM4_KEY_SIZE,
			.max_keysize = SM4_KEY_SIZE,
			.ivsize = SM4_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_CBC,
		.flow_mode = S_DIN_to_SM4,
		.min_hw_rev = CC_HW_REV_713,
		.std_body = CC_STD_OSCCA,
	पूर्ण,
	अणु
		.name = "ecb(sm4)",
		.driver_name = "ecb-sm4-ccree",
		.blocksize = SM4_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = SM4_KEY_SIZE,
			.max_keysize = SM4_KEY_SIZE,
			.ivsize = 0,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_ECB,
		.flow_mode = S_DIN_to_SM4,
		.min_hw_rev = CC_HW_REV_713,
		.std_body = CC_STD_OSCCA,
	पूर्ण,
	अणु
		.name = "ctr(sm4)",
		.driver_name = "ctr-sm4-ccree",
		.blocksize = 1,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_setkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = SM4_KEY_SIZE,
			.max_keysize = SM4_KEY_SIZE,
			.ivsize = SM4_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_CTR,
		.flow_mode = S_DIN_to_SM4,
		.min_hw_rev = CC_HW_REV_713,
		.std_body = CC_STD_OSCCA,
	पूर्ण,
	अणु
		.name = "cbc(psm4)",
		.driver_name = "cbc-psm4-ccree",
		.blocksize = SM4_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_sethkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = SM4_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_CBC,
		.flow_mode = S_DIN_to_SM4,
		.min_hw_rev = CC_HW_REV_713,
		.std_body = CC_STD_OSCCA,
		.sec_func = true,
	पूर्ण,
	अणु
		.name = "ctr(psm4)",
		.driver_name = "ctr-psm4-ccree",
		.blocksize = SM4_BLOCK_SIZE,
		.ढाँचा_skcipher = अणु
			.setkey = cc_cipher_sethkey,
			.encrypt = cc_cipher_encrypt,
			.decrypt = cc_cipher_decrypt,
			.min_keysize = CC_HW_KEY_SIZE,
			.max_keysize = CC_HW_KEY_SIZE,
			.ivsize = SM4_BLOCK_SIZE,
			पूर्ण,
		.cipher_mode = DRV_CIPHER_CTR,
		.flow_mode = S_DIN_to_SM4,
		.min_hw_rev = CC_HW_REV_713,
		.std_body = CC_STD_OSCCA,
		.sec_func = true,
	पूर्ण,
पूर्ण;

अटल काष्ठा cc_crypto_alg *cc_create_alg(स्थिर काष्ठा cc_alg_ढाँचा *पंचांगpl,
					   काष्ठा device *dev)
अणु
	काष्ठा cc_crypto_alg *t_alg;
	काष्ठा skcipher_alg *alg;

	t_alg = devm_kzalloc(dev, माप(*t_alg), GFP_KERNEL);
	अगर (!t_alg)
		वापस ERR_PTR(-ENOMEM);

	alg = &t_alg->skcipher_alg;

	स_नकल(alg, &पंचांगpl->ढाँचा_skcipher, माप(*alg));

	snम_लिखो(alg->base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", पंचांगpl->name);
	snम_लिखो(alg->base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 पंचांगpl->driver_name);
	alg->base.cra_module = THIS_MODULE;
	alg->base.cra_priority = CC_CRA_PRIO;
	alg->base.cra_blocksize = पंचांगpl->blocksize;
	alg->base.cra_alignmask = 0;
	alg->base.cra_ctxsize = माप(काष्ठा cc_cipher_ctx);

	alg->base.cra_init = cc_cipher_init;
	alg->base.cra_निकास = cc_cipher_निकास;
	alg->base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_KERN_DRIVER_ONLY;

	t_alg->cipher_mode = पंचांगpl->cipher_mode;
	t_alg->flow_mode = पंचांगpl->flow_mode;

	वापस t_alg;
पूर्ण

पूर्णांक cc_cipher_मुक्त(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_crypto_alg *t_alg, *n;

	/* Remove रेजिस्टरed algs */
	list_क्रम_each_entry_safe(t_alg, n, &drvdata->alg_list, entry) अणु
		crypto_unरेजिस्टर_skcipher(&t_alg->skcipher_alg);
		list_del(&t_alg->entry);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cc_cipher_alloc(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_crypto_alg *t_alg;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	पूर्णांक rc = -ENOMEM;
	पूर्णांक alg;

	INIT_LIST_HEAD(&drvdata->alg_list);

	/* Linux crypto */
	dev_dbg(dev, "Number of algorithms = %zu\n",
		ARRAY_SIZE(skcipher_algs));
	क्रम (alg = 0; alg < ARRAY_SIZE(skcipher_algs); alg++) अणु
		अगर ((skcipher_algs[alg].min_hw_rev > drvdata->hw_rev) ||
		    !(drvdata->std_bodies & skcipher_algs[alg].std_body) ||
		    (drvdata->sec_disabled && skcipher_algs[alg].sec_func))
			जारी;

		dev_dbg(dev, "creating %s\n", skcipher_algs[alg].driver_name);
		t_alg = cc_create_alg(&skcipher_algs[alg], dev);
		अगर (IS_ERR(t_alg)) अणु
			rc = PTR_ERR(t_alg);
			dev_err(dev, "%s alg allocation failed\n",
				skcipher_algs[alg].driver_name);
			जाओ fail0;
		पूर्ण
		t_alg->drvdata = drvdata;

		dev_dbg(dev, "registering %s\n",
			skcipher_algs[alg].driver_name);
		rc = crypto_रेजिस्टर_skcipher(&t_alg->skcipher_alg);
		dev_dbg(dev, "%s alg registration rc = %x\n",
			t_alg->skcipher_alg.base.cra_driver_name, rc);
		अगर (rc) अणु
			dev_err(dev, "%s alg registration failed\n",
				t_alg->skcipher_alg.base.cra_driver_name);
			जाओ fail0;
		पूर्ण

		list_add_tail(&t_alg->entry, &drvdata->alg_list);
		dev_dbg(dev, "Registered %s\n",
			t_alg->skcipher_alg.base.cra_driver_name);
	पूर्ण
	वापस 0;

fail0:
	cc_cipher_मुक्त(drvdata);
	वापस rc;
पूर्ण
