<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AMCC SoC PPC4xx Crypto Driver
 *
 * Copyright (c) 2008 Applied Micro Circuits Corporation.
 * All rights reserved. James Hsiao <jhsiao@amcc.com>
 *
 * This file implements the Linux crypto algorithms.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/crypto.h>
#समावेश <linux/hash.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/dma-mapping.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/skcipher.h>
#समावेश "crypto4xx_reg_def.h"
#समावेश "crypto4xx_core.h"
#समावेश "crypto4xx_sa.h"

अटल व्योम set_dynamic_sa_command_0(काष्ठा dynamic_sa_ctl *sa, u32 save_h,
				     u32 save_iv, u32 ld_h, u32 ld_iv,
				     u32 hdr_proc, u32 h, u32 c, u32 pad_type,
				     u32 op_grp, u32 op, u32 dir)
अणु
	sa->sa_command_0.w = 0;
	sa->sa_command_0.bf.save_hash_state = save_h;
	sa->sa_command_0.bf.save_iv = save_iv;
	sa->sa_command_0.bf.load_hash_state = ld_h;
	sa->sa_command_0.bf.load_iv = ld_iv;
	sa->sa_command_0.bf.hdr_proc = hdr_proc;
	sa->sa_command_0.bf.hash_alg = h;
	sa->sa_command_0.bf.cipher_alg = c;
	sa->sa_command_0.bf.pad_type = pad_type & 3;
	sa->sa_command_0.bf.extend_pad = pad_type >> 2;
	sa->sa_command_0.bf.op_group = op_grp;
	sa->sa_command_0.bf.opcode = op;
	sa->sa_command_0.bf.dir = dir;
पूर्ण

अटल व्योम set_dynamic_sa_command_1(काष्ठा dynamic_sa_ctl *sa, u32 cm,
				     u32 hmac_mc, u32 cfb, u32 esn,
				     u32 sn_mask, u32 mute, u32 cp_pad,
				     u32 cp_pay, u32 cp_hdr)
अणु
	sa->sa_command_1.w = 0;
	sa->sa_command_1.bf.crypto_mode31 = (cm & 4) >> 2;
	sa->sa_command_1.bf.crypto_mode9_8 = cm & 3;
	sa->sa_command_1.bf.feedback_mode = cfb;
	sa->sa_command_1.bf.sa_rev = 1;
	sa->sa_command_1.bf.hmac_muting = hmac_mc;
	sa->sa_command_1.bf.extended_seq_num = esn;
	sa->sa_command_1.bf.seq_num_mask = sn_mask;
	sa->sa_command_1.bf.mutable_bit_proc = mute;
	sa->sa_command_1.bf.copy_pad = cp_pad;
	sa->sa_command_1.bf.copy_payload = cp_pay;
	sa->sa_command_1.bf.copy_hdr = cp_hdr;
पूर्ण

अटल अंतरभूत पूर्णांक crypto4xx_crypt(काष्ठा skcipher_request *req,
				  स्थिर अचिन्हित पूर्णांक ivlen, bool decrypt,
				  bool check_blocksize)
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(req);
	काष्ठा crypto4xx_ctx *ctx = crypto_skcipher_ctx(cipher);
	__le32 iv[AES_IV_SIZE];

	अगर (check_blocksize && !IS_ALIGNED(req->cryptlen, AES_BLOCK_SIZE))
		वापस -EINVAL;

	अगर (ivlen)
		crypto4xx_स_नकल_to_le32(iv, req->iv, ivlen);

	वापस crypto4xx_build_pd(&req->base, ctx, req->src, req->dst,
		req->cryptlen, iv, ivlen, decrypt ? ctx->sa_in : ctx->sa_out,
		ctx->sa_len, 0, शून्य);
पूर्ण

पूर्णांक crypto4xx_encrypt_noiv_block(काष्ठा skcipher_request *req)
अणु
	वापस crypto4xx_crypt(req, 0, false, true);
पूर्ण

पूर्णांक crypto4xx_encrypt_iv_stream(काष्ठा skcipher_request *req)
अणु
	वापस crypto4xx_crypt(req, AES_IV_SIZE, false, false);
पूर्ण

पूर्णांक crypto4xx_decrypt_noiv_block(काष्ठा skcipher_request *req)
अणु
	वापस crypto4xx_crypt(req, 0, true, true);
पूर्ण

पूर्णांक crypto4xx_decrypt_iv_stream(काष्ठा skcipher_request *req)
अणु
	वापस crypto4xx_crypt(req, AES_IV_SIZE, true, false);
पूर्ण

पूर्णांक crypto4xx_encrypt_iv_block(काष्ठा skcipher_request *req)
अणु
	वापस crypto4xx_crypt(req, AES_IV_SIZE, false, true);
पूर्ण

पूर्णांक crypto4xx_decrypt_iv_block(काष्ठा skcipher_request *req)
अणु
	वापस crypto4xx_crypt(req, AES_IV_SIZE, true, true);
पूर्ण

/*
 * AES Functions
 */
अटल पूर्णांक crypto4xx_setkey_aes(काष्ठा crypto_skcipher *cipher,
				स्थिर u8 *key,
				अचिन्हित पूर्णांक keylen,
				अचिन्हित अक्षर cm,
				u8 fb)
अणु
	काष्ठा crypto4xx_ctx *ctx = crypto_skcipher_ctx(cipher);
	काष्ठा dynamic_sa_ctl *sa;
	पूर्णांक    rc;

	अगर (keylen != AES_KEYSIZE_256 && keylen != AES_KEYSIZE_192 &&
	    keylen != AES_KEYSIZE_128)
		वापस -EINVAL;

	/* Create SA */
	अगर (ctx->sa_in || ctx->sa_out)
		crypto4xx_मुक्त_sa(ctx);

	rc = crypto4xx_alloc_sa(ctx, SA_AES128_LEN + (keylen-16) / 4);
	अगर (rc)
		वापस rc;

	/* Setup SA */
	sa = ctx->sa_in;

	set_dynamic_sa_command_0(sa, SA_NOT_SAVE_HASH, (cm == CRYPTO_MODE_ECB ?
				 SA_NOT_SAVE_IV : SA_SAVE_IV),
				 SA_NOT_LOAD_HASH, (cm == CRYPTO_MODE_ECB ?
				 SA_LOAD_IV_FROM_SA : SA_LOAD_IV_FROM_STATE),
				 SA_NO_HEADER_PROC, SA_HASH_ALG_शून्य,
				 SA_CIPHER_ALG_AES, SA_PAD_TYPE_ZERO,
				 SA_OP_GROUP_BASIC, SA_OPCODE_DECRYPT,
				 सूची_INBOUND);

	set_dynamic_sa_command_1(sa, cm, SA_HASH_MODE_HASH,
				 fb, SA_EXTENDED_SN_OFF,
				 SA_SEQ_MASK_OFF, SA_MC_ENABLE,
				 SA_NOT_COPY_PAD, SA_NOT_COPY_PAYLOAD,
				 SA_NOT_COPY_HDR);
	crypto4xx_स_नकल_to_le32(get_dynamic_sa_key_field(sa),
				 key, keylen);
	sa->sa_contents.w = SA_AES_CONTENTS | (keylen << 2);
	sa->sa_command_1.bf.key_len = keylen >> 3;

	स_नकल(ctx->sa_out, ctx->sa_in, ctx->sa_len * 4);
	sa = ctx->sa_out;
	sa->sa_command_0.bf.dir = सूची_OUTBOUND;
	/*
	 * SA_OPCODE_ENCRYPT is the same value as SA_OPCODE_DECRYPT.
	 * it's the सूची_(IN|OUT)BOUND that matters
	 */
	sa->sa_command_0.bf.opcode = SA_OPCODE_ENCRYPT;

	वापस 0;
पूर्ण

पूर्णांक crypto4xx_setkey_aes_cbc(काष्ठा crypto_skcipher *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस crypto4xx_setkey_aes(cipher, key, keylen, CRYPTO_MODE_CBC,
				    CRYPTO_FEEDBACK_MODE_NO_FB);
पूर्ण

पूर्णांक crypto4xx_setkey_aes_cfb(काष्ठा crypto_skcipher *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस crypto4xx_setkey_aes(cipher, key, keylen, CRYPTO_MODE_CFB,
				    CRYPTO_FEEDBACK_MODE_128BIT_CFB);
पूर्ण

पूर्णांक crypto4xx_setkey_aes_ecb(काष्ठा crypto_skcipher *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस crypto4xx_setkey_aes(cipher, key, keylen, CRYPTO_MODE_ECB,
				    CRYPTO_FEEDBACK_MODE_NO_FB);
पूर्ण

पूर्णांक crypto4xx_setkey_aes_ofb(काष्ठा crypto_skcipher *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस crypto4xx_setkey_aes(cipher, key, keylen, CRYPTO_MODE_OFB,
				    CRYPTO_FEEDBACK_MODE_64BIT_OFB);
पूर्ण

पूर्णांक crypto4xx_setkey_rfc3686(काष्ठा crypto_skcipher *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto4xx_ctx *ctx = crypto_skcipher_ctx(cipher);
	पूर्णांक rc;

	rc = crypto4xx_setkey_aes(cipher, key, keylen - CTR_RFC3686_NONCE_SIZE,
		CRYPTO_MODE_CTR, CRYPTO_FEEDBACK_MODE_NO_FB);
	अगर (rc)
		वापस rc;

	ctx->iv_nonce = cpu_to_le32p((u32 *)&key[keylen -
						 CTR_RFC3686_NONCE_SIZE]);

	वापस 0;
पूर्ण

पूर्णांक crypto4xx_rfc3686_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(req);
	काष्ठा crypto4xx_ctx *ctx = crypto_skcipher_ctx(cipher);
	__le32 iv[AES_IV_SIZE / 4] = अणु
		ctx->iv_nonce,
		cpu_to_le32p((u32 *) req->iv),
		cpu_to_le32p((u32 *) (req->iv + 4)),
		cpu_to_le32(1) पूर्ण;

	वापस crypto4xx_build_pd(&req->base, ctx, req->src, req->dst,
				  req->cryptlen, iv, AES_IV_SIZE,
				  ctx->sa_out, ctx->sa_len, 0, शून्य);
पूर्ण

पूर्णांक crypto4xx_rfc3686_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(req);
	काष्ठा crypto4xx_ctx *ctx = crypto_skcipher_ctx(cipher);
	__le32 iv[AES_IV_SIZE / 4] = अणु
		ctx->iv_nonce,
		cpu_to_le32p((u32 *) req->iv),
		cpu_to_le32p((u32 *) (req->iv + 4)),
		cpu_to_le32(1) पूर्ण;

	वापस crypto4xx_build_pd(&req->base, ctx, req->src, req->dst,
				  req->cryptlen, iv, AES_IV_SIZE,
				  ctx->sa_out, ctx->sa_len, 0, शून्य);
पूर्ण

अटल पूर्णांक
crypto4xx_ctr_crypt(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(req);
	काष्ठा crypto4xx_ctx *ctx = crypto_skcipher_ctx(cipher);
	माप_प्रकार iv_len = crypto_skcipher_ivsize(cipher);
	अचिन्हित पूर्णांक counter = be32_to_cpup((__be32 *)(req->iv + iv_len - 4));
	अचिन्हित पूर्णांक nblks = ALIGN(req->cryptlen, AES_BLOCK_SIZE) /
			AES_BLOCK_SIZE;

	/*
	 * The hardware uses only the last 32-bits as the counter जबतक the
	 * kernel tests (aes_ctr_enc_tv_ढाँचा[4] क्रम example) expect that
	 * the whole IV is a counter.  So fallback अगर the counter is going to
	 * overlow.
	 */
	अगर (counter + nblks < counter) अणु
		SYNC_SKCIPHER_REQUEST_ON_STACK(subreq, ctx->sw_cipher.cipher);
		पूर्णांक ret;

		skcipher_request_set_sync_tfm(subreq, ctx->sw_cipher.cipher);
		skcipher_request_set_callback(subreq, req->base.flags,
			शून्य, शून्य);
		skcipher_request_set_crypt(subreq, req->src, req->dst,
			req->cryptlen, req->iv);
		ret = encrypt ? crypto_skcipher_encrypt(subreq)
			: crypto_skcipher_decrypt(subreq);
		skcipher_request_zero(subreq);
		वापस ret;
	पूर्ण

	वापस encrypt ? crypto4xx_encrypt_iv_stream(req)
		       : crypto4xx_decrypt_iv_stream(req);
पूर्ण

अटल पूर्णांक crypto4xx_sk_setup_fallback(काष्ठा crypto4xx_ctx *ctx,
				       काष्ठा crypto_skcipher *cipher,
				       स्थिर u8 *key,
				       अचिन्हित पूर्णांक keylen)
अणु
	crypto_sync_skcipher_clear_flags(ctx->sw_cipher.cipher,
				    CRYPTO_TFM_REQ_MASK);
	crypto_sync_skcipher_set_flags(ctx->sw_cipher.cipher,
		crypto_skcipher_get_flags(cipher) & CRYPTO_TFM_REQ_MASK);
	वापस crypto_sync_skcipher_setkey(ctx->sw_cipher.cipher, key, keylen);
पूर्ण

पूर्णांक crypto4xx_setkey_aes_ctr(काष्ठा crypto_skcipher *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto4xx_ctx *ctx = crypto_skcipher_ctx(cipher);
	पूर्णांक rc;

	rc = crypto4xx_sk_setup_fallback(ctx, cipher, key, keylen);
	अगर (rc)
		वापस rc;

	वापस crypto4xx_setkey_aes(cipher, key, keylen,
		CRYPTO_MODE_CTR, CRYPTO_FEEDBACK_MODE_NO_FB);
पूर्ण

पूर्णांक crypto4xx_encrypt_ctr(काष्ठा skcipher_request *req)
अणु
	वापस crypto4xx_ctr_crypt(req, true);
पूर्ण

पूर्णांक crypto4xx_decrypt_ctr(काष्ठा skcipher_request *req)
अणु
	वापस crypto4xx_ctr_crypt(req, false);
पूर्ण

अटल अंतरभूत bool crypto4xx_aead_need_fallback(काष्ठा aead_request *req,
						अचिन्हित पूर्णांक len,
						bool is_ccm, bool decrypt)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);

	/* authsize has to be a multiple of 4 */
	अगर (aead->authsize & 3)
		वापस true;

	/*
	 * hardware करोes not handle हालs where plaपूर्णांकext
	 * is less than a block.
	 */
	अगर (len < AES_BLOCK_SIZE)
		वापस true;

	/* assoc len needs to be a multiple of 4 and <= 1020 */
	अगर (req->assoclen & 0x3 || req->assoclen > 1020)
		वापस true;

	/* CCM supports only counter field length of 2 and 4 bytes */
	अगर (is_ccm && !(req->iv[0] == 1 || req->iv[0] == 3))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक crypto4xx_aead_fallback(काष्ठा aead_request *req,
	काष्ठा crypto4xx_ctx *ctx, bool करो_decrypt)
अणु
	काष्ठा aead_request *subreq = aead_request_ctx(req);

	aead_request_set_tfm(subreq, ctx->sw_cipher.aead);
	aead_request_set_callback(subreq, req->base.flags,
				  req->base.complete, req->base.data);
	aead_request_set_crypt(subreq, req->src, req->dst, req->cryptlen,
			       req->iv);
	aead_request_set_ad(subreq, req->assoclen);
	वापस करो_decrypt ? crypto_aead_decrypt(subreq) :
			    crypto_aead_encrypt(subreq);
पूर्ण

अटल पूर्णांक crypto4xx_aead_setup_fallback(काष्ठा crypto4xx_ctx *ctx,
					 काष्ठा crypto_aead *cipher,
					 स्थिर u8 *key,
					 अचिन्हित पूर्णांक keylen)
अणु
	crypto_aead_clear_flags(ctx->sw_cipher.aead, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(ctx->sw_cipher.aead,
		crypto_aead_get_flags(cipher) & CRYPTO_TFM_REQ_MASK);
	वापस crypto_aead_setkey(ctx->sw_cipher.aead, key, keylen);
पूर्ण

/*
 * AES-CCM Functions
 */

पूर्णांक crypto4xx_setkey_aes_ccm(काष्ठा crypto_aead *cipher, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(cipher);
	काष्ठा crypto4xx_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा dynamic_sa_ctl *sa;
	पूर्णांक rc = 0;

	rc = crypto4xx_aead_setup_fallback(ctx, cipher, key, keylen);
	अगर (rc)
		वापस rc;

	अगर (ctx->sa_in || ctx->sa_out)
		crypto4xx_मुक्त_sa(ctx);

	rc = crypto4xx_alloc_sa(ctx, SA_AES128_CCM_LEN + (keylen - 16) / 4);
	अगर (rc)
		वापस rc;

	/* Setup SA */
	sa = (काष्ठा dynamic_sa_ctl *) ctx->sa_in;
	sa->sa_contents.w = SA_AES_CCM_CONTENTS | (keylen << 2);

	set_dynamic_sa_command_0(sa, SA_SAVE_HASH, SA_NOT_SAVE_IV,
				 SA_LOAD_HASH_FROM_SA, SA_LOAD_IV_FROM_STATE,
				 SA_NO_HEADER_PROC, SA_HASH_ALG_CBC_MAC,
				 SA_CIPHER_ALG_AES,
				 SA_PAD_TYPE_ZERO, SA_OP_GROUP_BASIC,
				 SA_OPCODE_HASH_DECRYPT, सूची_INBOUND);

	set_dynamic_sa_command_1(sa, CRYPTO_MODE_CTR, SA_HASH_MODE_HASH,
				 CRYPTO_FEEDBACK_MODE_NO_FB, SA_EXTENDED_SN_OFF,
				 SA_SEQ_MASK_OFF, SA_MC_ENABLE,
				 SA_NOT_COPY_PAD, SA_COPY_PAYLOAD,
				 SA_NOT_COPY_HDR);

	sa->sa_command_1.bf.key_len = keylen >> 3;

	crypto4xx_स_नकल_to_le32(get_dynamic_sa_key_field(sa), key, keylen);

	स_नकल(ctx->sa_out, ctx->sa_in, ctx->sa_len * 4);
	sa = (काष्ठा dynamic_sa_ctl *) ctx->sa_out;

	set_dynamic_sa_command_0(sa, SA_SAVE_HASH, SA_NOT_SAVE_IV,
				 SA_LOAD_HASH_FROM_SA, SA_LOAD_IV_FROM_STATE,
				 SA_NO_HEADER_PROC, SA_HASH_ALG_CBC_MAC,
				 SA_CIPHER_ALG_AES,
				 SA_PAD_TYPE_ZERO, SA_OP_GROUP_BASIC,
				 SA_OPCODE_ENCRYPT_HASH, सूची_OUTBOUND);

	set_dynamic_sa_command_1(sa, CRYPTO_MODE_CTR, SA_HASH_MODE_HASH,
				 CRYPTO_FEEDBACK_MODE_NO_FB, SA_EXTENDED_SN_OFF,
				 SA_SEQ_MASK_OFF, SA_MC_ENABLE,
				 SA_COPY_PAD, SA_COPY_PAYLOAD,
				 SA_NOT_COPY_HDR);

	sa->sa_command_1.bf.key_len = keylen >> 3;
	वापस 0;
पूर्ण

अटल पूर्णांक crypto4xx_crypt_aes_ccm(काष्ठा aead_request *req, bool decrypt)
अणु
	काष्ठा crypto4xx_ctx *ctx  = crypto_tfm_ctx(req->base.tfm);
	काष्ठा crypto4xx_aead_reqctx *rctx = aead_request_ctx(req);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	__le32 iv[16];
	u32 पंचांगp_sa[SA_AES128_CCM_LEN + 4];
	काष्ठा dynamic_sa_ctl *sa = (काष्ठा dynamic_sa_ctl *)पंचांगp_sa;
	अचिन्हित पूर्णांक len = req->cryptlen;

	अगर (decrypt)
		len -= crypto_aead_authsize(aead);

	अगर (crypto4xx_aead_need_fallback(req, len, true, decrypt))
		वापस crypto4xx_aead_fallback(req, ctx, decrypt);

	स_नकल(पंचांगp_sa, decrypt ? ctx->sa_in : ctx->sa_out, ctx->sa_len * 4);
	sa->sa_command_0.bf.digest_len = crypto_aead_authsize(aead) >> 2;

	अगर (req->iv[0] == 1) अणु
		/* CRYPTO_MODE_AES_ICM */
		sa->sa_command_1.bf.crypto_mode9_8 = 1;
	पूर्ण

	iv[3] = cpu_to_le32(0);
	crypto4xx_स_नकल_to_le32(iv, req->iv, 16 - (req->iv[0] + 1));

	वापस crypto4xx_build_pd(&req->base, ctx, req->src, req->dst,
				  len, iv, माप(iv),
				  sa, ctx->sa_len, req->assoclen, rctx->dst);
पूर्ण

पूर्णांक crypto4xx_encrypt_aes_ccm(काष्ठा aead_request *req)
अणु
	वापस crypto4xx_crypt_aes_ccm(req, false);
पूर्ण

पूर्णांक crypto4xx_decrypt_aes_ccm(काष्ठा aead_request *req)
अणु
	वापस crypto4xx_crypt_aes_ccm(req, true);
पूर्ण

पूर्णांक crypto4xx_setauthsize_aead(काष्ठा crypto_aead *cipher,
			       अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(cipher);
	काष्ठा crypto4xx_ctx *ctx = crypto_tfm_ctx(tfm);

	वापस crypto_aead_setauthsize(ctx->sw_cipher.aead, authsize);
पूर्ण

/*
 * AES-GCM Functions
 */

अटल पूर्णांक crypto4xx_aes_gcm_validate_keylen(अचिन्हित पूर्णांक keylen)
अणु
	चयन (keylen) अणु
	हाल 16:
	हाल 24:
	हाल 32:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक crypto4xx_compute_gcm_hash_key_sw(__le32 *hash_start, स्थिर u8 *key,
					     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_aes_ctx ctx;
	uपूर्णांक8_t src[16] = अणु 0 पूर्ण;
	पूर्णांक rc;

	rc = aes_expandkey(&ctx, key, keylen);
	अगर (rc) अणु
		pr_err("aes_expandkey() failed: %d\n", rc);
		वापस rc;
	पूर्ण

	aes_encrypt(&ctx, src, src);
	crypto4xx_स_नकल_to_le32(hash_start, src, 16);
	memzero_explicit(&ctx, माप(ctx));
	वापस 0;
पूर्ण

पूर्णांक crypto4xx_setkey_aes_gcm(काष्ठा crypto_aead *cipher,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(cipher);
	काष्ठा crypto4xx_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा dynamic_sa_ctl *sa;
	पूर्णांक    rc = 0;

	अगर (crypto4xx_aes_gcm_validate_keylen(keylen) != 0)
		वापस -EINVAL;

	rc = crypto4xx_aead_setup_fallback(ctx, cipher, key, keylen);
	अगर (rc)
		वापस rc;

	अगर (ctx->sa_in || ctx->sa_out)
		crypto4xx_मुक्त_sa(ctx);

	rc = crypto4xx_alloc_sa(ctx, SA_AES128_GCM_LEN + (keylen - 16) / 4);
	अगर (rc)
		वापस rc;

	sa  = (काष्ठा dynamic_sa_ctl *) ctx->sa_in;

	sa->sa_contents.w = SA_AES_GCM_CONTENTS | (keylen << 2);
	set_dynamic_sa_command_0(sa, SA_SAVE_HASH, SA_NOT_SAVE_IV,
				 SA_LOAD_HASH_FROM_SA, SA_LOAD_IV_FROM_STATE,
				 SA_NO_HEADER_PROC, SA_HASH_ALG_GHASH,
				 SA_CIPHER_ALG_AES, SA_PAD_TYPE_ZERO,
				 SA_OP_GROUP_BASIC, SA_OPCODE_HASH_DECRYPT,
				 सूची_INBOUND);
	set_dynamic_sa_command_1(sa, CRYPTO_MODE_CTR, SA_HASH_MODE_HASH,
				 CRYPTO_FEEDBACK_MODE_NO_FB, SA_EXTENDED_SN_OFF,
				 SA_SEQ_MASK_ON, SA_MC_DISABLE,
				 SA_NOT_COPY_PAD, SA_COPY_PAYLOAD,
				 SA_NOT_COPY_HDR);

	sa->sa_command_1.bf.key_len = keylen >> 3;

	crypto4xx_स_नकल_to_le32(get_dynamic_sa_key_field(sa),
				 key, keylen);

	rc = crypto4xx_compute_gcm_hash_key_sw(get_dynamic_sa_inner_digest(sa),
		key, keylen);
	अगर (rc) अणु
		pr_err("GCM hash key setting failed = %d\n", rc);
		जाओ err;
	पूर्ण

	स_नकल(ctx->sa_out, ctx->sa_in, ctx->sa_len * 4);
	sa = (काष्ठा dynamic_sa_ctl *) ctx->sa_out;
	sa->sa_command_0.bf.dir = सूची_OUTBOUND;
	sa->sa_command_0.bf.opcode = SA_OPCODE_ENCRYPT_HASH;

	वापस 0;
err:
	crypto4xx_मुक्त_sa(ctx);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक crypto4xx_crypt_aes_gcm(काष्ठा aead_request *req,
					  bool decrypt)
अणु
	काष्ठा crypto4xx_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा crypto4xx_aead_reqctx *rctx = aead_request_ctx(req);
	__le32 iv[4];
	अचिन्हित पूर्णांक len = req->cryptlen;

	अगर (decrypt)
		len -= crypto_aead_authsize(crypto_aead_reqtfm(req));

	अगर (crypto4xx_aead_need_fallback(req, len, false, decrypt))
		वापस crypto4xx_aead_fallback(req, ctx, decrypt);

	crypto4xx_स_नकल_to_le32(iv, req->iv, GCM_AES_IV_SIZE);
	iv[3] = cpu_to_le32(1);

	वापस crypto4xx_build_pd(&req->base, ctx, req->src, req->dst,
				  len, iv, माप(iv),
				  decrypt ? ctx->sa_in : ctx->sa_out,
				  ctx->sa_len, req->assoclen, rctx->dst);
पूर्ण

पूर्णांक crypto4xx_encrypt_aes_gcm(काष्ठा aead_request *req)
अणु
	वापस crypto4xx_crypt_aes_gcm(req, false);
पूर्ण

पूर्णांक crypto4xx_decrypt_aes_gcm(काष्ठा aead_request *req)
अणु
	वापस crypto4xx_crypt_aes_gcm(req, true);
पूर्ण

/*
 * HASH SHA1 Functions
 */
अटल पूर्णांक crypto4xx_hash_alg_init(काष्ठा crypto_tfm *tfm,
				   अचिन्हित पूर्णांक sa_len,
				   अचिन्हित अक्षर ha,
				   अचिन्हित अक्षर hm)
अणु
	काष्ठा crypto_alg *alg = tfm->__crt_alg;
	काष्ठा crypto4xx_alg *my_alg;
	काष्ठा crypto4xx_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा dynamic_sa_hash160 *sa;
	पूर्णांक rc;

	my_alg = container_of(__crypto_ahash_alg(alg), काष्ठा crypto4xx_alg,
			      alg.u.hash);
	ctx->dev   = my_alg->dev;

	/* Create SA */
	अगर (ctx->sa_in || ctx->sa_out)
		crypto4xx_मुक्त_sa(ctx);

	rc = crypto4xx_alloc_sa(ctx, sa_len);
	अगर (rc)
		वापस rc;

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा crypto4xx_ctx));
	sa = (काष्ठा dynamic_sa_hash160 *)ctx->sa_in;
	set_dynamic_sa_command_0(&sa->ctrl, SA_SAVE_HASH, SA_NOT_SAVE_IV,
				 SA_NOT_LOAD_HASH, SA_LOAD_IV_FROM_SA,
				 SA_NO_HEADER_PROC, ha, SA_CIPHER_ALG_शून्य,
				 SA_PAD_TYPE_ZERO, SA_OP_GROUP_BASIC,
				 SA_OPCODE_HASH, सूची_INBOUND);
	set_dynamic_sa_command_1(&sa->ctrl, 0, SA_HASH_MODE_HASH,
				 CRYPTO_FEEDBACK_MODE_NO_FB, SA_EXTENDED_SN_OFF,
				 SA_SEQ_MASK_OFF, SA_MC_ENABLE,
				 SA_NOT_COPY_PAD, SA_NOT_COPY_PAYLOAD,
				 SA_NOT_COPY_HDR);
	/* Need to zero hash digest in SA */
	स_रखो(sa->inner_digest, 0, माप(sa->inner_digest));
	स_रखो(sa->outer_digest, 0, माप(sa->outer_digest));

	वापस 0;
पूर्ण

पूर्णांक crypto4xx_hash_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto4xx_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	पूर्णांक ds;
	काष्ठा dynamic_sa_ctl *sa;

	sa = ctx->sa_in;
	ds = crypto_ahash_digestsize(
			__crypto_ahash_cast(req->base.tfm));
	sa->sa_command_0.bf.digest_len = ds >> 2;
	sa->sa_command_0.bf.load_hash_state = SA_LOAD_HASH_FROM_SA;

	वापस 0;
पूर्ण

पूर्णांक crypto4xx_hash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा crypto4xx_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा scatterlist dst;
	अचिन्हित पूर्णांक ds = crypto_ahash_digestsize(ahash);

	sg_init_one(&dst, req->result, ds);

	वापस crypto4xx_build_pd(&req->base, ctx, req->src, &dst,
				  req->nbytes, शून्य, 0, ctx->sa_in,
				  ctx->sa_len, 0, शून्य);
पूर्ण

पूर्णांक crypto4xx_hash_final(काष्ठा ahash_request *req)
अणु
	वापस 0;
पूर्ण

पूर्णांक crypto4xx_hash_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा crypto4xx_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा scatterlist dst;
	अचिन्हित पूर्णांक ds = crypto_ahash_digestsize(ahash);

	sg_init_one(&dst, req->result, ds);

	वापस crypto4xx_build_pd(&req->base, ctx, req->src, &dst,
				  req->nbytes, शून्य, 0, ctx->sa_in,
				  ctx->sa_len, 0, शून्य);
पूर्ण

/*
 * SHA1 Algorithm
 */
पूर्णांक crypto4xx_sha1_alg_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस crypto4xx_hash_alg_init(tfm, SA_HASH160_LEN, SA_HASH_ALG_SHA1,
				       SA_HASH_MODE_HASH);
पूर्ण
