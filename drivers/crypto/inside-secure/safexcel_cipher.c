<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Marvell
 *
 * Antoine Tenart <antoine.tenart@मुक्त-electrons.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/chacha.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/ghash.h>
#समावेश <crypto/poly1305.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sm3.h>
#समावेश <crypto/sm4.h>
#समावेश <crypto/xts.h>
#समावेश <crypto/skcipher.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश "safexcel.h"

क्रमागत safexcel_cipher_direction अणु
	SAFEXCEL_ENCRYPT,
	SAFEXCEL_DECRYPT,
पूर्ण;

क्रमागत safexcel_cipher_alg अणु
	SAFEXCEL_DES,
	SAFEXCEL_3DES,
	SAFEXCEL_AES,
	SAFEXCEL_CHACHA20,
	SAFEXCEL_SM4,
पूर्ण;

काष्ठा safexcel_cipher_ctx अणु
	काष्ठा safexcel_context base;
	काष्ठा safexcel_crypto_priv *priv;

	u32 mode;
	क्रमागत safexcel_cipher_alg alg;
	u8 aead; /* !=0=AEAD, 2=IPSec ESP AEAD, 3=IPsec ESP GMAC */
	u8 xcm;  /* 0=authenc, 1=GCM, 2 reserved क्रम CCM */
	u8 aadskip;
	u8 blocksz;
	u32 ivmask;
	u32 ctrinit;

	__le32 key[16];
	u32 nonce;
	अचिन्हित पूर्णांक key_len, xts;

	/* All the below is AEAD specअगरic */
	u32 hash_alg;
	u32 state_sz;

	काष्ठा crypto_cipher *hkaes;
	काष्ठा crypto_aead *fback;
पूर्ण;

काष्ठा safexcel_cipher_req अणु
	क्रमागत safexcel_cipher_direction direction;
	/* Number of result descriptors associated to the request */
	अचिन्हित पूर्णांक rdescs;
	bool needs_inv;
	पूर्णांक  nr_src, nr_dst;
पूर्ण;

अटल पूर्णांक safexcel_skcipher_iv(काष्ठा safexcel_cipher_ctx *ctx, u8 *iv,
				काष्ठा safexcel_command_desc *cdesc)
अणु
	अगर (ctx->mode == CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD) अणु
		cdesc->control_data.options |= EIP197_OPTION_4_TOKEN_IV_CMD;
		/* 32 bit nonce */
		cdesc->control_data.token[0] = ctx->nonce;
		/* 64 bit IV part */
		स_नकल(&cdesc->control_data.token[1], iv, 8);
		/* 32 bit counter, start at 0 or 1 (big endian!) */
		cdesc->control_data.token[3] =
			(__क्रमce u32)cpu_to_be32(ctx->ctrinit);
		वापस 4;
	पूर्ण
	अगर (ctx->alg == SAFEXCEL_CHACHA20) अणु
		cdesc->control_data.options |= EIP197_OPTION_4_TOKEN_IV_CMD;
		/* 96 bit nonce part */
		स_नकल(&cdesc->control_data.token[0], &iv[4], 12);
		/* 32 bit counter */
		cdesc->control_data.token[3] = *(u32 *)iv;
		वापस 4;
	पूर्ण

	cdesc->control_data.options |= ctx->ivmask;
	स_नकल(cdesc->control_data.token, iv, ctx->blocksz);
	वापस ctx->blocksz / माप(u32);
पूर्ण

अटल व्योम safexcel_skcipher_token(काष्ठा safexcel_cipher_ctx *ctx, u8 *iv,
				    काष्ठा safexcel_command_desc *cdesc,
				    काष्ठा safexcel_token *atoken,
				    u32 length)
अणु
	काष्ठा safexcel_token *token;
	पूर्णांक ivlen;

	ivlen = safexcel_skcipher_iv(ctx, iv, cdesc);
	अगर (ivlen == 4) अणु
		/* No space in cdesc, inकाष्ठाion moves to atoken */
		cdesc->additional_cdata_size = 1;
		token = atoken;
	पूर्ण अन्यथा अणु
		/* Everything fits in cdesc */
		token = (काष्ठा safexcel_token *)(cdesc->control_data.token + 2);
		/* Need to pad with NOP */
		eip197_noop_token(&token[1]);
	पूर्ण

	token->opcode = EIP197_TOKEN_OPCODE_सूचीECTION;
	token->packet_length = length;
	token->stat = EIP197_TOKEN_STAT_LAST_PACKET |
		      EIP197_TOKEN_STAT_LAST_HASH;
	token->inकाष्ठाions = EIP197_TOKEN_INS_LAST |
			      EIP197_TOKEN_INS_TYPE_CRYPTO |
			      EIP197_TOKEN_INS_TYPE_OUTPUT;
पूर्ण

अटल व्योम safexcel_aead_iv(काष्ठा safexcel_cipher_ctx *ctx, u8 *iv,
			     काष्ठा safexcel_command_desc *cdesc)
अणु
	अगर (ctx->mode == CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD ||
	    ctx->aead & EIP197_AEAD_TYPE_IPSEC_ESP) अणु /* _ESP and _ESP_GMAC */
		/* 32 bit nonce */
		cdesc->control_data.token[0] = ctx->nonce;
		/* 64 bit IV part */
		स_नकल(&cdesc->control_data.token[1], iv, 8);
		/* 32 bit counter, start at 0 or 1 (big endian!) */
		cdesc->control_data.token[3] =
			(__क्रमce u32)cpu_to_be32(ctx->ctrinit);
		वापस;
	पूर्ण
	अगर (ctx->xcm == EIP197_XCM_MODE_GCM || ctx->alg == SAFEXCEL_CHACHA20) अणु
		/* 96 bit IV part */
		स_नकल(&cdesc->control_data.token[0], iv, 12);
		/* 32 bit counter, start at 0 or 1 (big endian!) */
		cdesc->control_data.token[3] =
			(__क्रमce u32)cpu_to_be32(ctx->ctrinit);
		वापस;
	पूर्ण
	/* CBC */
	स_नकल(cdesc->control_data.token, iv, ctx->blocksz);
पूर्ण

अटल व्योम safexcel_aead_token(काष्ठा safexcel_cipher_ctx *ctx, u8 *iv,
				काष्ठा safexcel_command_desc *cdesc,
				काष्ठा safexcel_token *atoken,
				क्रमागत safexcel_cipher_direction direction,
				u32 cryptlen, u32 assoclen, u32 digestsize)
अणु
	काष्ठा safexcel_token *aadref;
	पूर्णांक atoksize = 2; /* Start with minimum size */
	पूर्णांक assocadj = assoclen - ctx->aadskip, aadalign;

	/* Always 4 dwords of embedded IV  क्रम AEAD modes */
	cdesc->control_data.options |= EIP197_OPTION_4_TOKEN_IV_CMD;

	अगर (direction == SAFEXCEL_DECRYPT)
		cryptlen -= digestsize;

	अगर (unlikely(ctx->xcm == EIP197_XCM_MODE_CCM)) अणु
		/* Conकाष्ठा IV block B0 क्रम the CBC-MAC */
		u8 *final_iv = (u8 *)cdesc->control_data.token;
		u8 *cbcmaciv = (u8 *)&atoken[1];
		__le32 *aadlen = (__le32 *)&atoken[5];

		अगर (ctx->aead == EIP197_AEAD_TYPE_IPSEC_ESP) अणु
			/* Length + nonce */
			cdesc->control_data.token[0] = ctx->nonce;
			/* Fixup flags byte */
			*(__le32 *)cbcmaciv =
				cpu_to_le32(ctx->nonce |
					    ((assocadj > 0) << 6) |
					    ((digestsize - 2) << 2));
			/* 64 bit IV part */
			स_नकल(&cdesc->control_data.token[1], iv, 8);
			स_नकल(cbcmaciv + 4, iv, 8);
			/* Start counter at 0 */
			cdesc->control_data.token[3] = 0;
			/* Message length */
			*(__be32 *)(cbcmaciv + 12) = cpu_to_be32(cryptlen);
		पूर्ण अन्यथा अणु
			/* Variable length IV part */
			स_नकल(final_iv, iv, 15 - iv[0]);
			स_नकल(cbcmaciv, iv, 15 - iv[0]);
			/* Start variable length counter at 0 */
			स_रखो(final_iv + 15 - iv[0], 0, iv[0] + 1);
			स_रखो(cbcmaciv + 15 - iv[0], 0, iv[0] - 1);
			/* fixup flags byte */
			cbcmaciv[0] |= ((assocadj > 0) << 6) |
				       ((digestsize - 2) << 2);
			/* insert lower 2 bytes of message length */
			cbcmaciv[14] = cryptlen >> 8;
			cbcmaciv[15] = cryptlen & 255;
		पूर्ण

		atoken->opcode = EIP197_TOKEN_OPCODE_INSERT;
		atoken->packet_length = AES_BLOCK_SIZE +
					((assocadj > 0) << 1);
		atoken->stat = 0;
		atoken->inकाष्ठाions = EIP197_TOKEN_INS_ORIGIN_TOKEN |
				       EIP197_TOKEN_INS_TYPE_HASH;

		अगर (likely(assocadj)) अणु
			*aadlen = cpu_to_le32((assocadj >> 8) |
					      (assocadj & 255) << 8);
			atoken += 6;
			atoksize += 7;
		पूर्ण अन्यथा अणु
			atoken += 5;
			atoksize += 6;
		पूर्ण

		/* Process AAD data */
		aadref = atoken;
		atoken->opcode = EIP197_TOKEN_OPCODE_सूचीECTION;
		atoken->packet_length = assocadj;
		atoken->stat = 0;
		atoken->inकाष्ठाions = EIP197_TOKEN_INS_TYPE_HASH;
		atoken++;

		/* For CCM only, align AAD data towards hash engine */
		atoken->opcode = EIP197_TOKEN_OPCODE_INSERT;
		aadalign = (assocadj + 2) & 15;
		atoken->packet_length = assocadj && aadalign ?
						16 - aadalign :
						0;
		अगर (likely(cryptlen)) अणु
			atoken->stat = 0;
			atoken->inकाष्ठाions = EIP197_TOKEN_INS_TYPE_HASH;
		पूर्ण अन्यथा अणु
			atoken->stat = EIP197_TOKEN_STAT_LAST_HASH;
			atoken->inकाष्ठाions = EIP197_TOKEN_INS_LAST |
					       EIP197_TOKEN_INS_TYPE_HASH;
		पूर्ण
	पूर्ण अन्यथा अणु
		safexcel_aead_iv(ctx, iv, cdesc);

		/* Process AAD data */
		aadref = atoken;
		atoken->opcode = EIP197_TOKEN_OPCODE_सूचीECTION;
		atoken->packet_length = assocadj;
		atoken->stat = EIP197_TOKEN_STAT_LAST_HASH;
		atoken->inकाष्ठाions = EIP197_TOKEN_INS_LAST |
				       EIP197_TOKEN_INS_TYPE_HASH;
	पूर्ण
	atoken++;

	अगर (ctx->aead == EIP197_AEAD_TYPE_IPSEC_ESP) अणु
		/* For ESP mode (and not GMAC), skip over the IV */
		atoken->opcode = EIP197_TOKEN_OPCODE_सूचीECTION;
		atoken->packet_length = EIP197_AEAD_IPSEC_IV_SIZE;
		atoken->stat = 0;
		atoken->inकाष्ठाions = 0;
		atoken++;
		atoksize++;
	पूर्ण अन्यथा अगर (unlikely(ctx->alg == SAFEXCEL_CHACHA20 &&
			    direction == SAFEXCEL_DECRYPT)) अणु
		/* Poly-chacha decryption needs a dummy NOP here ... */
		atoken->opcode = EIP197_TOKEN_OPCODE_INSERT;
		atoken->packet_length = 16; /* According to Op Manual */
		atoken->stat = 0;
		atoken->inकाष्ठाions = 0;
		atoken++;
		atoksize++;
	पूर्ण

	अगर  (ctx->xcm) अणु
		/* For GCM and CCM, obtain enc(Y0) */
		atoken->opcode = EIP197_TOKEN_OPCODE_INSERT_REMRES;
		atoken->packet_length = 0;
		atoken->stat = 0;
		atoken->inकाष्ठाions = AES_BLOCK_SIZE;
		atoken++;

		atoken->opcode = EIP197_TOKEN_OPCODE_INSERT;
		atoken->packet_length = AES_BLOCK_SIZE;
		atoken->stat = 0;
		atoken->inकाष्ठाions = EIP197_TOKEN_INS_TYPE_OUTPUT |
				       EIP197_TOKEN_INS_TYPE_CRYPTO;
		atoken++;
		atoksize += 2;
	पूर्ण

	अगर (likely(cryptlen || ctx->alg == SAFEXCEL_CHACHA20)) अणु
		/* Fixup stat field क्रम AAD direction inकाष्ठाion */
		aadref->stat = 0;

		/* Process crypto data */
		atoken->opcode = EIP197_TOKEN_OPCODE_सूचीECTION;
		atoken->packet_length = cryptlen;

		अगर (unlikely(ctx->aead == EIP197_AEAD_TYPE_IPSEC_ESP_GMAC)) अणु
			/* Fixup inकाष्ठाion field क्रम AAD dir inकाष्ठाion */
			aadref->inकाष्ठाions = EIP197_TOKEN_INS_TYPE_HASH;

			/* Do not send to crypt engine in हाल of GMAC */
			atoken->inकाष्ठाions = EIP197_TOKEN_INS_LAST |
					       EIP197_TOKEN_INS_TYPE_HASH |
					       EIP197_TOKEN_INS_TYPE_OUTPUT;
		पूर्ण अन्यथा अणु
			atoken->inकाष्ठाions = EIP197_TOKEN_INS_LAST |
					       EIP197_TOKEN_INS_TYPE_CRYPTO |
					       EIP197_TOKEN_INS_TYPE_HASH |
					       EIP197_TOKEN_INS_TYPE_OUTPUT;
		पूर्ण

		cryptlen &= 15;
		अगर (unlikely(ctx->xcm == EIP197_XCM_MODE_CCM && cryptlen)) अणु
			atoken->stat = 0;
			/* For CCM only, pad crypto data to the hash engine */
			atoken++;
			atoksize++;
			atoken->opcode = EIP197_TOKEN_OPCODE_INSERT;
			atoken->packet_length = 16 - cryptlen;
			atoken->stat = EIP197_TOKEN_STAT_LAST_HASH;
			atoken->inकाष्ठाions = EIP197_TOKEN_INS_TYPE_HASH;
		पूर्ण अन्यथा अणु
			atoken->stat = EIP197_TOKEN_STAT_LAST_HASH;
		पूर्ण
		atoken++;
		atoksize++;
	पूर्ण

	अगर (direction == SAFEXCEL_ENCRYPT) अणु
		/* Append ICV */
		atoken->opcode = EIP197_TOKEN_OPCODE_INSERT;
		atoken->packet_length = digestsize;
		atoken->stat = EIP197_TOKEN_STAT_LAST_HASH |
			       EIP197_TOKEN_STAT_LAST_PACKET;
		atoken->inकाष्ठाions = EIP197_TOKEN_INS_TYPE_OUTPUT |
				       EIP197_TOKEN_INS_INSERT_HASH_DIGEST;
	पूर्ण अन्यथा अणु
		/* Extract ICV */
		atoken->opcode = EIP197_TOKEN_OPCODE_RETRIEVE;
		atoken->packet_length = digestsize;
		atoken->stat = EIP197_TOKEN_STAT_LAST_HASH |
			       EIP197_TOKEN_STAT_LAST_PACKET;
		atoken->inकाष्ठाions = EIP197_TOKEN_INS_INSERT_HASH_DIGEST;
		atoken++;
		atoksize++;

		/* Verअगरy ICV */
		atoken->opcode = EIP197_TOKEN_OPCODE_VERIFY;
		atoken->packet_length = digestsize |
					EIP197_TOKEN_HASH_RESULT_VERIFY;
		atoken->stat = EIP197_TOKEN_STAT_LAST_HASH |
			       EIP197_TOKEN_STAT_LAST_PACKET;
		atoken->inकाष्ठाions = EIP197_TOKEN_INS_TYPE_OUTPUT;
	पूर्ण

	/* Fixup length of the token in the command descriptor */
	cdesc->additional_cdata_size = atoksize;
पूर्ण

अटल पूर्णांक safexcel_skcipher_aes_setkey(काष्ठा crypto_skcipher *ctfm,
					स्थिर u8 *key, अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(ctfm);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	काष्ठा crypto_aes_ctx aes;
	पूर्णांक ret, i;

	ret = aes_expandkey(&aes, key, len);
	अगर (ret)
		वापस ret;

	अगर (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma) अणु
		क्रम (i = 0; i < len / माप(u32); i++) अणु
			अगर (le32_to_cpu(ctx->key[i]) != aes.key_enc[i]) अणु
				ctx->base.needs_inv = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < len / माप(u32); i++)
		ctx->key[i] = cpu_to_le32(aes.key_enc[i]);

	ctx->key_len = len;

	memzero_explicit(&aes, माप(aes));
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_aead_setkey(काष्ठा crypto_aead *ctfm, स्थिर u8 *key,
				अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(ctfm);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	काष्ठा crypto_authenc_keys keys;
	काष्ठा crypto_aes_ctx aes;
	पूर्णांक err = -EINVAL, i;
	स्थिर अक्षर *alg;

	अगर (unlikely(crypto_authenc_extractkeys(&keys, key, len)))
		जाओ badkey;

	अगर (ctx->mode == CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD) अणु
		/* Must have at least space क्रम the nonce here */
		अगर (unlikely(keys.enckeylen < CTR_RFC3686_NONCE_SIZE))
			जाओ badkey;
		/* last 4 bytes of key are the nonce! */
		ctx->nonce = *(u32 *)(keys.enckey + keys.enckeylen -
				      CTR_RFC3686_NONCE_SIZE);
		/* exclude the nonce here */
		keys.enckeylen -= CTR_RFC3686_NONCE_SIZE;
	पूर्ण

	/* Encryption key */
	चयन (ctx->alg) अणु
	हाल SAFEXCEL_DES:
		err = verअगरy_aead_des_key(ctfm, keys.enckey, keys.enckeylen);
		अगर (unlikely(err))
			जाओ badkey;
		अवरोध;
	हाल SAFEXCEL_3DES:
		err = verअगरy_aead_des3_key(ctfm, keys.enckey, keys.enckeylen);
		अगर (unlikely(err))
			जाओ badkey;
		अवरोध;
	हाल SAFEXCEL_AES:
		err = aes_expandkey(&aes, keys.enckey, keys.enckeylen);
		अगर (unlikely(err))
			जाओ badkey;
		अवरोध;
	हाल SAFEXCEL_SM4:
		अगर (unlikely(keys.enckeylen != SM4_KEY_SIZE))
			जाओ badkey;
		अवरोध;
	शेष:
		dev_err(priv->dev, "aead: unsupported cipher algorithm\n");
		जाओ badkey;
	पूर्ण

	अगर (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma) अणु
		क्रम (i = 0; i < keys.enckeylen / माप(u32); i++) अणु
			अगर (le32_to_cpu(ctx->key[i]) !=
			    ((u32 *)keys.enckey)[i]) अणु
				ctx->base.needs_inv = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Auth key */
	चयन (ctx->hash_alg) अणु
	हाल CONTEXT_CONTROL_CRYPTO_ALG_SHA1:
		alg = "safexcel-sha1";
		अवरोध;
	हाल CONTEXT_CONTROL_CRYPTO_ALG_SHA224:
		alg = "safexcel-sha224";
		अवरोध;
	हाल CONTEXT_CONTROL_CRYPTO_ALG_SHA256:
		alg = "safexcel-sha256";
		अवरोध;
	हाल CONTEXT_CONTROL_CRYPTO_ALG_SHA384:
		alg = "safexcel-sha384";
		अवरोध;
	हाल CONTEXT_CONTROL_CRYPTO_ALG_SHA512:
		alg = "safexcel-sha512";
		अवरोध;
	हाल CONTEXT_CONTROL_CRYPTO_ALG_SM3:
		alg = "safexcel-sm3";
		अवरोध;
	शेष:
		dev_err(priv->dev, "aead: unsupported hash algorithm\n");
		जाओ badkey;
	पूर्ण

	अगर (safexcel_hmac_setkey(&ctx->base, keys.authkey, keys.authkeylen,
				 alg, ctx->state_sz))
		जाओ badkey;

	/* Now copy the keys पूर्णांकo the context */
	क्रम (i = 0; i < keys.enckeylen / माप(u32); i++)
		ctx->key[i] = cpu_to_le32(((u32 *)keys.enckey)[i]);
	ctx->key_len = keys.enckeylen;

	memzero_explicit(&keys, माप(keys));
	वापस 0;

badkey:
	memzero_explicit(&keys, माप(keys));
	वापस err;
पूर्ण

अटल पूर्णांक safexcel_context_control(काष्ठा safexcel_cipher_ctx *ctx,
				    काष्ठा crypto_async_request *async,
				    काष्ठा safexcel_cipher_req *sreq,
				    काष्ठा safexcel_command_desc *cdesc)
अणु
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	पूर्णांक ctrl_size = ctx->key_len / माप(u32);

	cdesc->control_data.control1 = ctx->mode;

	अगर (ctx->aead) अणु
		/* Take in account the ipad+opad digests */
		अगर (ctx->xcm) अणु
			ctrl_size += ctx->state_sz / माप(u32);
			cdesc->control_data.control0 =
				CONTEXT_CONTROL_KEY_EN |
				CONTEXT_CONTROL_DIGEST_XCM |
				ctx->hash_alg |
				CONTEXT_CONTROL_SIZE(ctrl_size);
		पूर्ण अन्यथा अगर (ctx->alg == SAFEXCEL_CHACHA20) अणु
			/* Chacha20-Poly1305 */
			cdesc->control_data.control0 =
				CONTEXT_CONTROL_KEY_EN |
				CONTEXT_CONTROL_CRYPTO_ALG_CHACHA20 |
				(sreq->direction == SAFEXCEL_ENCRYPT ?
					CONTEXT_CONTROL_TYPE_ENCRYPT_HASH_OUT :
					CONTEXT_CONTROL_TYPE_HASH_DECRYPT_IN) |
				ctx->hash_alg |
				CONTEXT_CONTROL_SIZE(ctrl_size);
			वापस 0;
		पूर्ण अन्यथा अणु
			ctrl_size += ctx->state_sz / माप(u32) * 2;
			cdesc->control_data.control0 =
				CONTEXT_CONTROL_KEY_EN |
				CONTEXT_CONTROL_DIGEST_HMAC |
				ctx->hash_alg |
				CONTEXT_CONTROL_SIZE(ctrl_size);
		पूर्ण

		अगर (sreq->direction == SAFEXCEL_ENCRYPT &&
		    (ctx->xcm == EIP197_XCM_MODE_CCM ||
		     ctx->aead == EIP197_AEAD_TYPE_IPSEC_ESP_GMAC))
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_TYPE_HASH_ENCRYPT_OUT;
		अन्यथा अगर (sreq->direction == SAFEXCEL_ENCRYPT)
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_TYPE_ENCRYPT_HASH_OUT;
		अन्यथा अगर (ctx->xcm == EIP197_XCM_MODE_CCM)
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_TYPE_DECRYPT_HASH_IN;
		अन्यथा
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_TYPE_HASH_DECRYPT_IN;
	पूर्ण अन्यथा अणु
		अगर (sreq->direction == SAFEXCEL_ENCRYPT)
			cdesc->control_data.control0 =
				CONTEXT_CONTROL_TYPE_CRYPTO_OUT |
				CONTEXT_CONTROL_KEY_EN |
				CONTEXT_CONTROL_SIZE(ctrl_size);
		अन्यथा
			cdesc->control_data.control0 =
				CONTEXT_CONTROL_TYPE_CRYPTO_IN |
				CONTEXT_CONTROL_KEY_EN |
				CONTEXT_CONTROL_SIZE(ctrl_size);
	पूर्ण

	अगर (ctx->alg == SAFEXCEL_DES) अणु
		cdesc->control_data.control0 |=
			CONTEXT_CONTROL_CRYPTO_ALG_DES;
	पूर्ण अन्यथा अगर (ctx->alg == SAFEXCEL_3DES) अणु
		cdesc->control_data.control0 |=
			CONTEXT_CONTROL_CRYPTO_ALG_3DES;
	पूर्ण अन्यथा अगर (ctx->alg == SAFEXCEL_AES) अणु
		चयन (ctx->key_len >> ctx->xts) अणु
		हाल AES_KEYSIZE_128:
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_CRYPTO_ALG_AES128;
			अवरोध;
		हाल AES_KEYSIZE_192:
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_CRYPTO_ALG_AES192;
			अवरोध;
		हाल AES_KEYSIZE_256:
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_CRYPTO_ALG_AES256;
			अवरोध;
		शेष:
			dev_err(priv->dev, "aes keysize not supported: %u\n",
				ctx->key_len >> ctx->xts);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (ctx->alg == SAFEXCEL_CHACHA20) अणु
		cdesc->control_data.control0 |=
			CONTEXT_CONTROL_CRYPTO_ALG_CHACHA20;
	पूर्ण अन्यथा अगर (ctx->alg == SAFEXCEL_SM4) अणु
		cdesc->control_data.control0 |=
			CONTEXT_CONTROL_CRYPTO_ALG_SM4;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_handle_req_result(काष्ठा safexcel_crypto_priv *priv, पूर्णांक ring,
				      काष्ठा crypto_async_request *async,
				      काष्ठा scatterlist *src,
				      काष्ठा scatterlist *dst,
				      अचिन्हित पूर्णांक cryptlen,
				      काष्ठा safexcel_cipher_req *sreq,
				      bool *should_complete, पूर्णांक *ret)
अणु
	काष्ठा skcipher_request *areq = skcipher_request_cast(async);
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(areq);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा safexcel_result_desc *rdesc;
	पूर्णांक ndesc = 0;

	*ret = 0;

	अगर (unlikely(!sreq->rdescs))
		वापस 0;

	जबतक (sreq->rdescs--) अणु
		rdesc = safexcel_ring_next_rptr(priv, &priv->ring[ring].rdr);
		अगर (IS_ERR(rdesc)) अणु
			dev_err(priv->dev,
				"cipher: result: could not retrieve the result descriptor\n");
			*ret = PTR_ERR(rdesc);
			अवरोध;
		पूर्ण

		अगर (likely(!*ret))
			*ret = safexcel_rdesc_check_errors(priv, rdesc);

		ndesc++;
	पूर्ण

	safexcel_complete(priv, ring);

	अगर (src == dst) अणु
		dma_unmap_sg(priv->dev, src, sreq->nr_src, DMA_BIसूचीECTIONAL);
	पूर्ण अन्यथा अणु
		dma_unmap_sg(priv->dev, src, sreq->nr_src, DMA_TO_DEVICE);
		dma_unmap_sg(priv->dev, dst, sreq->nr_dst, DMA_FROM_DEVICE);
	पूर्ण

	/*
	 * Update IV in req from last crypto output word क्रम CBC modes
	 */
	अगर ((!ctx->aead) && (ctx->mode == CONTEXT_CONTROL_CRYPTO_MODE_CBC) &&
	    (sreq->direction == SAFEXCEL_ENCRYPT)) अणु
		/* For encrypt take the last output word */
		sg_pcopy_to_buffer(dst, sreq->nr_dst, areq->iv,
				   crypto_skcipher_ivsize(skcipher),
				   (cryptlen -
				    crypto_skcipher_ivsize(skcipher)));
	पूर्ण

	*should_complete = true;

	वापस ndesc;
पूर्ण

अटल पूर्णांक safexcel_send_req(काष्ठा crypto_async_request *base, पूर्णांक ring,
			     काष्ठा safexcel_cipher_req *sreq,
			     काष्ठा scatterlist *src, काष्ठा scatterlist *dst,
			     अचिन्हित पूर्णांक cryptlen, अचिन्हित पूर्णांक assoclen,
			     अचिन्हित पूर्णांक digestsize, u8 *iv, पूर्णांक *commands,
			     पूर्णांक *results)
अणु
	काष्ठा skcipher_request *areq = skcipher_request_cast(base);
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(areq);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(base->tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	काष्ठा safexcel_command_desc *cdesc;
	काष्ठा safexcel_command_desc *first_cdesc = शून्य;
	काष्ठा safexcel_result_desc *rdesc, *first_rdesc = शून्य;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक totlen;
	अचिन्हित पूर्णांक totlen_src = cryptlen + assoclen;
	अचिन्हित पूर्णांक totlen_dst = totlen_src;
	काष्ठा safexcel_token *atoken;
	पूर्णांक n_cdesc = 0, n_rdesc = 0;
	पूर्णांक queued, i, ret = 0;
	bool first = true;

	sreq->nr_src = sg_nents_क्रम_len(src, totlen_src);

	अगर (ctx->aead) अणु
		/*
		 * AEAD has auth tag appended to output क्रम encrypt and
		 * हटाओd from the output क्रम decrypt!
		 */
		अगर (sreq->direction == SAFEXCEL_DECRYPT)
			totlen_dst -= digestsize;
		अन्यथा
			totlen_dst += digestsize;

		स_नकल(ctx->base.ctxr->data + ctx->key_len / माप(u32),
		       &ctx->base.ipad, ctx->state_sz);
		अगर (!ctx->xcm)
			स_नकल(ctx->base.ctxr->data + (ctx->key_len +
			       ctx->state_sz) / माप(u32), &ctx->base.opad,
			       ctx->state_sz);
	पूर्ण अन्यथा अगर ((ctx->mode == CONTEXT_CONTROL_CRYPTO_MODE_CBC) &&
		   (sreq->direction == SAFEXCEL_DECRYPT)) अणु
		/*
		 * Save IV from last crypto input word क्रम CBC modes in decrypt
		 * direction. Need to करो this first in हाल of inplace operation
		 * as it will be overwritten.
		 */
		sg_pcopy_to_buffer(src, sreq->nr_src, areq->iv,
				   crypto_skcipher_ivsize(skcipher),
				   (totlen_src -
				    crypto_skcipher_ivsize(skcipher)));
	पूर्ण

	sreq->nr_dst = sg_nents_क्रम_len(dst, totlen_dst);

	/*
	 * Remember actual input length, source buffer length may be
	 * updated in हाल of अंतरभूत operation below.
	 */
	totlen = totlen_src;
	queued = totlen_src;

	अगर (src == dst) अणु
		sreq->nr_src = max(sreq->nr_src, sreq->nr_dst);
		sreq->nr_dst = sreq->nr_src;
		अगर (unlikely((totlen_src || totlen_dst) &&
		    (sreq->nr_src <= 0))) अणु
			dev_err(priv->dev, "In-place buffer not large enough (need %d bytes)!",
				max(totlen_src, totlen_dst));
			वापस -EINVAL;
		पूर्ण
		dma_map_sg(priv->dev, src, sreq->nr_src, DMA_BIसूचीECTIONAL);
	पूर्ण अन्यथा अणु
		अगर (unlikely(totlen_src && (sreq->nr_src <= 0))) अणु
			dev_err(priv->dev, "Source buffer not large enough (need %d bytes)!",
				totlen_src);
			वापस -EINVAL;
		पूर्ण
		dma_map_sg(priv->dev, src, sreq->nr_src, DMA_TO_DEVICE);

		अगर (unlikely(totlen_dst && (sreq->nr_dst <= 0))) अणु
			dev_err(priv->dev, "Dest buffer not large enough (need %d bytes)!",
				totlen_dst);
			dma_unmap_sg(priv->dev, src, sreq->nr_src,
				     DMA_TO_DEVICE);
			वापस -EINVAL;
		पूर्ण
		dma_map_sg(priv->dev, dst, sreq->nr_dst, DMA_FROM_DEVICE);
	पूर्ण

	स_नकल(ctx->base.ctxr->data, ctx->key, ctx->key_len);

	अगर (!totlen) अणु
		/*
		 * The EIP97 cannot deal with zero length input packets!
		 * So stuff a dummy command descriptor indicating a 1 byte
		 * (dummy) input packet, using the context record as source.
		 */
		first_cdesc = safexcel_add_cdesc(priv, ring,
						 1, 1, ctx->base.ctxr_dma,
						 1, 1, ctx->base.ctxr_dma,
						 &atoken);
		अगर (IS_ERR(first_cdesc)) अणु
			/* No space left in the command descriptor ring */
			ret = PTR_ERR(first_cdesc);
			जाओ cdesc_rollback;
		पूर्ण
		n_cdesc = 1;
		जाओ skip_cdesc;
	पूर्ण

	/* command descriptors */
	क्रम_each_sg(src, sg, sreq->nr_src, i) अणु
		पूर्णांक len = sg_dma_len(sg);

		/* Do not overflow the request */
		अगर (queued < len)
			len = queued;

		cdesc = safexcel_add_cdesc(priv, ring, !n_cdesc,
					   !(queued - len),
					   sg_dma_address(sg), len, totlen,
					   ctx->base.ctxr_dma, &atoken);
		अगर (IS_ERR(cdesc)) अणु
			/* No space left in the command descriptor ring */
			ret = PTR_ERR(cdesc);
			जाओ cdesc_rollback;
		पूर्ण

		अगर (!n_cdesc)
			first_cdesc = cdesc;

		n_cdesc++;
		queued -= len;
		अगर (!queued)
			अवरोध;
	पूर्ण
skip_cdesc:
	/* Add context control words and token to first command descriptor */
	safexcel_context_control(ctx, base, sreq, first_cdesc);
	अगर (ctx->aead)
		safexcel_aead_token(ctx, iv, first_cdesc, atoken,
				    sreq->direction, cryptlen,
				    assoclen, digestsize);
	अन्यथा
		safexcel_skcipher_token(ctx, iv, first_cdesc, atoken,
					cryptlen);

	/* result descriptors */
	क्रम_each_sg(dst, sg, sreq->nr_dst, i) अणु
		bool last = (i == sreq->nr_dst - 1);
		u32 len = sg_dma_len(sg);

		/* only allow the part of the buffer we know we need */
		अगर (len > totlen_dst)
			len = totlen_dst;
		अगर (unlikely(!len))
			अवरोध;
		totlen_dst -= len;

		/* skip over AAD space in buffer - not written */
		अगर (assoclen) अणु
			अगर (assoclen >= len) अणु
				assoclen -= len;
				जारी;
			पूर्ण
			rdesc = safexcel_add_rdesc(priv, ring, first, last,
						   sg_dma_address(sg) +
						   assoclen,
						   len - assoclen);
			assoclen = 0;
		पूर्ण अन्यथा अणु
			rdesc = safexcel_add_rdesc(priv, ring, first, last,
						   sg_dma_address(sg),
						   len);
		पूर्ण
		अगर (IS_ERR(rdesc)) अणु
			/* No space left in the result descriptor ring */
			ret = PTR_ERR(rdesc);
			जाओ rdesc_rollback;
		पूर्ण
		अगर (first) अणु
			first_rdesc = rdesc;
			first = false;
		पूर्ण
		n_rdesc++;
	पूर्ण

	अगर (unlikely(first)) अणु
		/*
		 * Special हाल: AEAD decrypt with only AAD data.
		 * In this हाल there is NO output data from the engine,
		 * but the engine still needs a result descriptor!
		 * Create a dummy one just क्रम catching the result token.
		 */
		rdesc = safexcel_add_rdesc(priv, ring, true, true, 0, 0);
		अगर (IS_ERR(rdesc)) अणु
			/* No space left in the result descriptor ring */
			ret = PTR_ERR(rdesc);
			जाओ rdesc_rollback;
		पूर्ण
		first_rdesc = rdesc;
		n_rdesc = 1;
	पूर्ण

	safexcel_rdr_req_set(priv, ring, first_rdesc, base);

	*commands = n_cdesc;
	*results = n_rdesc;
	वापस 0;

rdesc_rollback:
	क्रम (i = 0; i < n_rdesc; i++)
		safexcel_ring_rollback_wptr(priv, &priv->ring[ring].rdr);
cdesc_rollback:
	क्रम (i = 0; i < n_cdesc; i++)
		safexcel_ring_rollback_wptr(priv, &priv->ring[ring].cdr);

	अगर (src == dst) अणु
		dma_unmap_sg(priv->dev, src, sreq->nr_src, DMA_BIसूचीECTIONAL);
	पूर्ण अन्यथा अणु
		dma_unmap_sg(priv->dev, src, sreq->nr_src, DMA_TO_DEVICE);
		dma_unmap_sg(priv->dev, dst, sreq->nr_dst, DMA_FROM_DEVICE);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक safexcel_handle_inv_result(काष्ठा safexcel_crypto_priv *priv,
				      पूर्णांक ring,
				      काष्ठा crypto_async_request *base,
				      काष्ठा safexcel_cipher_req *sreq,
				      bool *should_complete, पूर्णांक *ret)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(base->tfm);
	काष्ठा safexcel_result_desc *rdesc;
	पूर्णांक ndesc = 0, enq_ret;

	*ret = 0;

	अगर (unlikely(!sreq->rdescs))
		वापस 0;

	जबतक (sreq->rdescs--) अणु
		rdesc = safexcel_ring_next_rptr(priv, &priv->ring[ring].rdr);
		अगर (IS_ERR(rdesc)) अणु
			dev_err(priv->dev,
				"cipher: invalidate: could not retrieve the result descriptor\n");
			*ret = PTR_ERR(rdesc);
			अवरोध;
		पूर्ण

		अगर (likely(!*ret))
			*ret = safexcel_rdesc_check_errors(priv, rdesc);

		ndesc++;
	पूर्ण

	safexcel_complete(priv, ring);

	अगर (ctx->base.निकास_inv) अणु
		dma_pool_मुक्त(priv->context_pool, ctx->base.ctxr,
			      ctx->base.ctxr_dma);

		*should_complete = true;

		वापस ndesc;
	पूर्ण

	ring = safexcel_select_ring(priv);
	ctx->base.ring = ring;

	spin_lock_bh(&priv->ring[ring].queue_lock);
	enq_ret = crypto_enqueue_request(&priv->ring[ring].queue, base);
	spin_unlock_bh(&priv->ring[ring].queue_lock);

	अगर (enq_ret != -EINPROGRESS)
		*ret = enq_ret;

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	*should_complete = false;

	वापस ndesc;
पूर्ण

अटल पूर्णांक safexcel_skcipher_handle_result(काष्ठा safexcel_crypto_priv *priv,
					   पूर्णांक ring,
					   काष्ठा crypto_async_request *async,
					   bool *should_complete, पूर्णांक *ret)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(async);
	काष्ठा safexcel_cipher_req *sreq = skcipher_request_ctx(req);
	पूर्णांक err;

	अगर (sreq->needs_inv) अणु
		sreq->needs_inv = false;
		err = safexcel_handle_inv_result(priv, ring, async, sreq,
						 should_complete, ret);
	पूर्ण अन्यथा अणु
		err = safexcel_handle_req_result(priv, ring, async, req->src,
						 req->dst, req->cryptlen, sreq,
						 should_complete, ret);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक safexcel_aead_handle_result(काष्ठा safexcel_crypto_priv *priv,
				       पूर्णांक ring,
				       काष्ठा crypto_async_request *async,
				       bool *should_complete, पूर्णांक *ret)
अणु
	काष्ठा aead_request *req = aead_request_cast(async);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा safexcel_cipher_req *sreq = aead_request_ctx(req);
	पूर्णांक err;

	अगर (sreq->needs_inv) अणु
		sreq->needs_inv = false;
		err = safexcel_handle_inv_result(priv, ring, async, sreq,
						 should_complete, ret);
	पूर्ण अन्यथा अणु
		err = safexcel_handle_req_result(priv, ring, async, req->src,
						 req->dst,
						 req->cryptlen + crypto_aead_authsize(tfm),
						 sreq, should_complete, ret);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक safexcel_cipher_send_inv(काष्ठा crypto_async_request *base,
				    पूर्णांक ring, पूर्णांक *commands, पूर्णांक *results)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(base->tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	पूर्णांक ret;

	ret = safexcel_invalidate_cache(base, priv, ctx->base.ctxr_dma, ring);
	अगर (unlikely(ret))
		वापस ret;

	*commands = 1;
	*results = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_skcipher_send(काष्ठा crypto_async_request *async, पूर्णांक ring,
				  पूर्णांक *commands, पूर्णांक *results)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(async);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा safexcel_cipher_req *sreq = skcipher_request_ctx(req);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	पूर्णांक ret;

	BUG_ON(!(priv->flags & EIP197_TRC_CACHE) && sreq->needs_inv);

	अगर (sreq->needs_inv) अणु
		ret = safexcel_cipher_send_inv(async, ring, commands, results);
	पूर्ण अन्यथा अणु
		काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
		u8 input_iv[AES_BLOCK_SIZE];

		/*
		 * Save input IV in हाल of CBC decrypt mode
		 * Will be overwritten with output IV prior to use!
		 */
		स_नकल(input_iv, req->iv, crypto_skcipher_ivsize(skcipher));

		ret = safexcel_send_req(async, ring, sreq, req->src,
					req->dst, req->cryptlen, 0, 0, input_iv,
					commands, results);
	पूर्ण

	sreq->rdescs = *results;
	वापस ret;
पूर्ण

अटल पूर्णांक safexcel_aead_send(काष्ठा crypto_async_request *async, पूर्णांक ring,
			      पूर्णांक *commands, पूर्णांक *results)
अणु
	काष्ठा aead_request *req = aead_request_cast(async);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा safexcel_cipher_req *sreq = aead_request_ctx(req);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	पूर्णांक ret;

	BUG_ON(!(priv->flags & EIP197_TRC_CACHE) && sreq->needs_inv);

	अगर (sreq->needs_inv)
		ret = safexcel_cipher_send_inv(async, ring, commands, results);
	अन्यथा
		ret = safexcel_send_req(async, ring, sreq, req->src, req->dst,
					req->cryptlen, req->assoclen,
					crypto_aead_authsize(tfm), req->iv,
					commands, results);
	sreq->rdescs = *results;
	वापस ret;
पूर्ण

अटल पूर्णांक safexcel_cipher_निकास_inv(काष्ठा crypto_tfm *tfm,
				    काष्ठा crypto_async_request *base,
				    काष्ठा safexcel_cipher_req *sreq,
				    काष्ठा safexcel_inv_result *result)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	पूर्णांक ring = ctx->base.ring;

	init_completion(&result->completion);

	ctx = crypto_tfm_ctx(base->tfm);
	ctx->base.निकास_inv = true;
	sreq->needs_inv = true;

	spin_lock_bh(&priv->ring[ring].queue_lock);
	crypto_enqueue_request(&priv->ring[ring].queue, base);
	spin_unlock_bh(&priv->ring[ring].queue_lock);

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	रुको_क्रम_completion(&result->completion);

	अगर (result->error) अणु
		dev_warn(priv->dev,
			"cipher: sync: invalidate: completion error %d\n",
			 result->error);
		वापस result->error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_skcipher_निकास_inv(काष्ठा crypto_tfm *tfm)
अणु
	EIP197_REQUEST_ON_STACK(req, skcipher, EIP197_SKCIPHER_REQ_SIZE);
	काष्ठा safexcel_cipher_req *sreq = skcipher_request_ctx(req);
	काष्ठा safexcel_inv_result result = अणुपूर्ण;

	स_रखो(req, 0, माप(काष्ठा skcipher_request));

	skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				      safexcel_inv_complete, &result);
	skcipher_request_set_tfm(req, __crypto_skcipher_cast(tfm));

	वापस safexcel_cipher_निकास_inv(tfm, &req->base, sreq, &result);
पूर्ण

अटल पूर्णांक safexcel_aead_निकास_inv(काष्ठा crypto_tfm *tfm)
अणु
	EIP197_REQUEST_ON_STACK(req, aead, EIP197_AEAD_REQ_SIZE);
	काष्ठा safexcel_cipher_req *sreq = aead_request_ctx(req);
	काष्ठा safexcel_inv_result result = अणुपूर्ण;

	स_रखो(req, 0, माप(काष्ठा aead_request));

	aead_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				  safexcel_inv_complete, &result);
	aead_request_set_tfm(req, __crypto_aead_cast(tfm));

	वापस safexcel_cipher_निकास_inv(tfm, &req->base, sreq, &result);
पूर्ण

अटल पूर्णांक safexcel_queue_req(काष्ठा crypto_async_request *base,
			काष्ठा safexcel_cipher_req *sreq,
			क्रमागत safexcel_cipher_direction dir)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(base->tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	पूर्णांक ret, ring;

	sreq->needs_inv = false;
	sreq->direction = dir;

	अगर (ctx->base.ctxr) अणु
		अगर (priv->flags & EIP197_TRC_CACHE && ctx->base.needs_inv) अणु
			sreq->needs_inv = true;
			ctx->base.needs_inv = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		ctx->base.ring = safexcel_select_ring(priv);
		ctx->base.ctxr = dma_pool_zalloc(priv->context_pool,
						 EIP197_GFP_FLAGS(*base),
						 &ctx->base.ctxr_dma);
		अगर (!ctx->base.ctxr)
			वापस -ENOMEM;
	पूर्ण

	ring = ctx->base.ring;

	spin_lock_bh(&priv->ring[ring].queue_lock);
	ret = crypto_enqueue_request(&priv->ring[ring].queue, base);
	spin_unlock_bh(&priv->ring[ring].queue_lock);

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	वापस ret;
पूर्ण

अटल पूर्णांक safexcel_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस safexcel_queue_req(&req->base, skcipher_request_ctx(req),
			SAFEXCEL_ENCRYPT);
पूर्ण

अटल पूर्णांक safexcel_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस safexcel_queue_req(&req->base, skcipher_request_ctx(req),
			SAFEXCEL_DECRYPT);
पूर्ण

अटल पूर्णांक safexcel_skcipher_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_alg_ढाँचा *पंचांगpl =
		container_of(tfm->__crt_alg, काष्ठा safexcel_alg_ढाँचा,
			     alg.skcipher.base);

	crypto_skcipher_set_reqsize(__crypto_skcipher_cast(tfm),
				    माप(काष्ठा safexcel_cipher_req));

	ctx->base.priv = पंचांगpl->priv;

	ctx->base.send = safexcel_skcipher_send;
	ctx->base.handle_result = safexcel_skcipher_handle_result;
	ctx->ivmask = EIP197_OPTION_4_TOKEN_IV_CMD;
	ctx->ctrinit = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_cipher_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	memzero_explicit(ctx->key, माप(ctx->key));

	/* context not allocated, skip invalidation */
	अगर (!ctx->base.ctxr)
		वापस -ENOMEM;

	memzero_explicit(ctx->base.ctxr->data, माप(ctx->base.ctxr->data));
	वापस 0;
पूर्ण

अटल व्योम safexcel_skcipher_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	पूर्णांक ret;

	अगर (safexcel_cipher_cra_निकास(tfm))
		वापस;

	अगर (priv->flags & EIP197_TRC_CACHE) अणु
		ret = safexcel_skcipher_निकास_inv(tfm);
		अगर (ret)
			dev_warn(priv->dev, "skcipher: invalidation error %d\n",
				 ret);
	पूर्ण अन्यथा अणु
		dma_pool_मुक्त(priv->context_pool, ctx->base.ctxr,
			      ctx->base.ctxr_dma);
	पूर्ण
पूर्ण

अटल व्योम safexcel_aead_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	पूर्णांक ret;

	अगर (safexcel_cipher_cra_निकास(tfm))
		वापस;

	अगर (priv->flags & EIP197_TRC_CACHE) अणु
		ret = safexcel_aead_निकास_inv(tfm);
		अगर (ret)
			dev_warn(priv->dev, "aead: invalidation error %d\n",
				 ret);
	पूर्ण अन्यथा अणु
		dma_pool_मुक्त(priv->context_pool, ctx->base.ctxr,
			      ctx->base.ctxr_dma);
	पूर्ण
पूर्ण

अटल पूर्णांक safexcel_skcipher_aes_ecb_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_AES;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_ECB;
	ctx->blocksz = 0;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_ecb_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_AES,
	.alg.skcipher = अणु
		.setkey = safexcel_skcipher_aes_setkey,
		.encrypt = safexcel_encrypt,
		.decrypt = safexcel_decrypt,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.base = अणु
			.cra_name = "ecb(aes)",
			.cra_driver_name = "safexcel-ecb-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_aes_ecb_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_skcipher_aes_cbc_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_AES;
	ctx->blocksz = AES_BLOCK_SIZE;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CBC;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_cbc_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_AES,
	.alg.skcipher = अणु
		.setkey = safexcel_skcipher_aes_setkey,
		.encrypt = safexcel_encrypt,
		.decrypt = safexcel_decrypt,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
		.base = अणु
			.cra_name = "cbc(aes)",
			.cra_driver_name = "safexcel-cbc-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_aes_cbc_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_skcipher_aes_cfb_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_AES;
	ctx->blocksz = AES_BLOCK_SIZE;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CFB;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_cfb_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_AES_XFB,
	.alg.skcipher = अणु
		.setkey = safexcel_skcipher_aes_setkey,
		.encrypt = safexcel_encrypt,
		.decrypt = safexcel_decrypt,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
		.base = अणु
			.cra_name = "cfb(aes)",
			.cra_driver_name = "safexcel-cfb-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_aes_cfb_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_skcipher_aes_ofb_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_AES;
	ctx->blocksz = AES_BLOCK_SIZE;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_OFB;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_ofb_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_AES_XFB,
	.alg.skcipher = अणु
		.setkey = safexcel_skcipher_aes_setkey,
		.encrypt = safexcel_encrypt,
		.decrypt = safexcel_decrypt,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
		.base = अणु
			.cra_name = "ofb(aes)",
			.cra_driver_name = "safexcel-ofb-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_aes_ofb_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_skcipher_aesctr_setkey(काष्ठा crypto_skcipher *ctfm,
					   स्थिर u8 *key, अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(ctfm);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	काष्ठा crypto_aes_ctx aes;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक keylen;

	/* last 4 bytes of key are the nonce! */
	ctx->nonce = *(u32 *)(key + len - CTR_RFC3686_NONCE_SIZE);
	/* exclude the nonce here */
	keylen = len - CTR_RFC3686_NONCE_SIZE;
	ret = aes_expandkey(&aes, key, keylen);
	अगर (ret)
		वापस ret;

	अगर (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma) अणु
		क्रम (i = 0; i < keylen / माप(u32); i++) अणु
			अगर (le32_to_cpu(ctx->key[i]) != aes.key_enc[i]) अणु
				ctx->base.needs_inv = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < keylen / माप(u32); i++)
		ctx->key[i] = cpu_to_le32(aes.key_enc[i]);

	ctx->key_len = keylen;

	memzero_explicit(&aes, माप(aes));
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_skcipher_aes_ctr_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_AES;
	ctx->blocksz = AES_BLOCK_SIZE;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_ctr_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_AES,
	.alg.skcipher = अणु
		.setkey = safexcel_skcipher_aesctr_setkey,
		.encrypt = safexcel_encrypt,
		.decrypt = safexcel_decrypt,
		/* Add nonce size */
		.min_keysize = AES_MIN_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
		.ivsize = CTR_RFC3686_IV_SIZE,
		.base = अणु
			.cra_name = "rfc3686(ctr(aes))",
			.cra_driver_name = "safexcel-ctr-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_aes_ctr_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_des_setkey(काष्ठा crypto_skcipher *ctfm, स्थिर u8 *key,
			       अचिन्हित पूर्णांक len)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_skcipher_ctx(ctfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	पूर्णांक ret;

	ret = verअगरy_skcipher_des_key(ctfm, key);
	अगर (ret)
		वापस ret;

	/* अगर context निकासs and key changed, need to invalidate it */
	अगर (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma)
		अगर (स_भेद(ctx->key, key, len))
			ctx->base.needs_inv = true;

	स_नकल(ctx->key, key, len);
	ctx->key_len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_skcipher_des_cbc_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_DES;
	ctx->blocksz = DES_BLOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CBC;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_cbc_des = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_DES,
	.alg.skcipher = अणु
		.setkey = safexcel_des_setkey,
		.encrypt = safexcel_encrypt,
		.decrypt = safexcel_decrypt,
		.min_keysize = DES_KEY_SIZE,
		.max_keysize = DES_KEY_SIZE,
		.ivsize = DES_BLOCK_SIZE,
		.base = अणु
			.cra_name = "cbc(des)",
			.cra_driver_name = "safexcel-cbc-des",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_des_cbc_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_skcipher_des_ecb_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_DES;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_ECB;
	ctx->blocksz = 0;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_ecb_des = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_DES,
	.alg.skcipher = अणु
		.setkey = safexcel_des_setkey,
		.encrypt = safexcel_encrypt,
		.decrypt = safexcel_decrypt,
		.min_keysize = DES_KEY_SIZE,
		.max_keysize = DES_KEY_SIZE,
		.base = अणु
			.cra_name = "ecb(des)",
			.cra_driver_name = "safexcel-ecb-des",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_des_ecb_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_des3_ede_setkey(काष्ठा crypto_skcipher *ctfm,
				   स्थिर u8 *key, अचिन्हित पूर्णांक len)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_skcipher_ctx(ctfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	पूर्णांक err;

	err = verअगरy_skcipher_des3_key(ctfm, key);
	अगर (err)
		वापस err;

	/* अगर context निकासs and key changed, need to invalidate it */
	अगर (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma)
		अगर (स_भेद(ctx->key, key, len))
			ctx->base.needs_inv = true;

	स_नकल(ctx->key, key, len);
	ctx->key_len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_skcipher_des3_cbc_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_3DES;
	ctx->blocksz = DES3_EDE_BLOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CBC;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_cbc_des3_ede = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_DES,
	.alg.skcipher = अणु
		.setkey = safexcel_des3_ede_setkey,
		.encrypt = safexcel_encrypt,
		.decrypt = safexcel_decrypt,
		.min_keysize = DES3_EDE_KEY_SIZE,
		.max_keysize = DES3_EDE_KEY_SIZE,
		.ivsize = DES3_EDE_BLOCK_SIZE,
		.base = अणु
			.cra_name = "cbc(des3_ede)",
			.cra_driver_name = "safexcel-cbc-des3_ede",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_des3_cbc_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_skcipher_des3_ecb_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_3DES;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_ECB;
	ctx->blocksz = 0;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_ecb_des3_ede = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_DES,
	.alg.skcipher = अणु
		.setkey = safexcel_des3_ede_setkey,
		.encrypt = safexcel_encrypt,
		.decrypt = safexcel_decrypt,
		.min_keysize = DES3_EDE_KEY_SIZE,
		.max_keysize = DES3_EDE_KEY_SIZE,
		.base = अणु
			.cra_name = "ecb(des3_ede)",
			.cra_driver_name = "safexcel-ecb-des3_ede",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_des3_ecb_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा safexcel_cipher_req *creq = aead_request_ctx(req);

	वापस safexcel_queue_req(&req->base, creq, SAFEXCEL_ENCRYPT);
पूर्ण

अटल पूर्णांक safexcel_aead_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा safexcel_cipher_req *creq = aead_request_ctx(req);

	वापस safexcel_queue_req(&req->base, creq, SAFEXCEL_DECRYPT);
पूर्ण

अटल पूर्णांक safexcel_aead_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_alg_ढाँचा *पंचांगpl =
		container_of(tfm->__crt_alg, काष्ठा safexcel_alg_ढाँचा,
			     alg.aead.base);

	crypto_aead_set_reqsize(__crypto_aead_cast(tfm),
				माप(काष्ठा safexcel_cipher_req));

	ctx->base.priv = पंचांगpl->priv;

	ctx->alg  = SAFEXCEL_AES; /* शेष */
	ctx->blocksz = AES_BLOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_4_TOKEN_IV_CMD;
	ctx->ctrinit = 1;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CBC; /* शेष */
	ctx->aead = true;
	ctx->base.send = safexcel_aead_send;
	ctx->base.handle_result = safexcel_aead_handle_result;
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_aead_sha1_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_cra_init(tfm);
	ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA1;
	ctx->state_sz = SHA1_DIGEST_SIZE;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha1_cbc_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_SHA1,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = AES_BLOCK_SIZE,
		.maxauthsize = SHA1_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha1),cbc(aes))",
			.cra_driver_name = "safexcel-authenc-hmac-sha1-cbc-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha1_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha256_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_cra_init(tfm);
	ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA256;
	ctx->state_sz = SHA256_DIGEST_SIZE;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha256_cbc_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_SHA2_256,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = AES_BLOCK_SIZE,
		.maxauthsize = SHA256_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha256),cbc(aes))",
			.cra_driver_name = "safexcel-authenc-hmac-sha256-cbc-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha256_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha224_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_cra_init(tfm);
	ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA224;
	ctx->state_sz = SHA256_DIGEST_SIZE;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha224_cbc_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_SHA2_256,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = AES_BLOCK_SIZE,
		.maxauthsize = SHA224_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha224),cbc(aes))",
			.cra_driver_name = "safexcel-authenc-hmac-sha224-cbc-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha224_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha512_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_cra_init(tfm);
	ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA512;
	ctx->state_sz = SHA512_DIGEST_SIZE;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha512_cbc_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_SHA2_512,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = AES_BLOCK_SIZE,
		.maxauthsize = SHA512_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha512),cbc(aes))",
			.cra_driver_name = "safexcel-authenc-hmac-sha512-cbc-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha512_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha384_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_cra_init(tfm);
	ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA384;
	ctx->state_sz = SHA512_DIGEST_SIZE;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha384_cbc_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_SHA2_512,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = AES_BLOCK_SIZE,
		.maxauthsize = SHA384_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha384),cbc(aes))",
			.cra_driver_name = "safexcel-authenc-hmac-sha384-cbc-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha384_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha1_des3_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha1_cra_init(tfm);
	ctx->alg = SAFEXCEL_3DES; /* override शेष */
	ctx->blocksz = DES3_EDE_BLOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha1_cbc_des3_ede = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_DES | SAFEXCEL_ALG_SHA1,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = DES3_EDE_BLOCK_SIZE,
		.maxauthsize = SHA1_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha1),cbc(des3_ede))",
			.cra_driver_name = "safexcel-authenc-hmac-sha1-cbc-des3_ede",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha1_des3_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha256_des3_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha256_cra_init(tfm);
	ctx->alg = SAFEXCEL_3DES; /* override शेष */
	ctx->blocksz = DES3_EDE_BLOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha256_cbc_des3_ede = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_DES | SAFEXCEL_ALG_SHA2_256,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = DES3_EDE_BLOCK_SIZE,
		.maxauthsize = SHA256_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha256),cbc(des3_ede))",
			.cra_driver_name = "safexcel-authenc-hmac-sha256-cbc-des3_ede",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha256_des3_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha224_des3_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha224_cra_init(tfm);
	ctx->alg = SAFEXCEL_3DES; /* override शेष */
	ctx->blocksz = DES3_EDE_BLOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha224_cbc_des3_ede = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_DES | SAFEXCEL_ALG_SHA2_256,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = DES3_EDE_BLOCK_SIZE,
		.maxauthsize = SHA224_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha224),cbc(des3_ede))",
			.cra_driver_name = "safexcel-authenc-hmac-sha224-cbc-des3_ede",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha224_des3_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha512_des3_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha512_cra_init(tfm);
	ctx->alg = SAFEXCEL_3DES; /* override शेष */
	ctx->blocksz = DES3_EDE_BLOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha512_cbc_des3_ede = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_DES | SAFEXCEL_ALG_SHA2_512,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = DES3_EDE_BLOCK_SIZE,
		.maxauthsize = SHA512_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha512),cbc(des3_ede))",
			.cra_driver_name = "safexcel-authenc-hmac-sha512-cbc-des3_ede",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha512_des3_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha384_des3_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha384_cra_init(tfm);
	ctx->alg = SAFEXCEL_3DES; /* override शेष */
	ctx->blocksz = DES3_EDE_BLOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha384_cbc_des3_ede = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_DES | SAFEXCEL_ALG_SHA2_512,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = DES3_EDE_BLOCK_SIZE,
		.maxauthsize = SHA384_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha384),cbc(des3_ede))",
			.cra_driver_name = "safexcel-authenc-hmac-sha384-cbc-des3_ede",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha384_des3_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha1_des_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha1_cra_init(tfm);
	ctx->alg = SAFEXCEL_DES; /* override शेष */
	ctx->blocksz = DES_BLOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha1_cbc_des = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_DES | SAFEXCEL_ALG_SHA1,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = DES_BLOCK_SIZE,
		.maxauthsize = SHA1_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha1),cbc(des))",
			.cra_driver_name = "safexcel-authenc-hmac-sha1-cbc-des",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha1_des_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha256_des_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha256_cra_init(tfm);
	ctx->alg = SAFEXCEL_DES; /* override शेष */
	ctx->blocksz = DES_BLOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha256_cbc_des = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_DES | SAFEXCEL_ALG_SHA2_256,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = DES_BLOCK_SIZE,
		.maxauthsize = SHA256_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha256),cbc(des))",
			.cra_driver_name = "safexcel-authenc-hmac-sha256-cbc-des",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha256_des_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha224_des_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha224_cra_init(tfm);
	ctx->alg = SAFEXCEL_DES; /* override शेष */
	ctx->blocksz = DES_BLOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha224_cbc_des = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_DES | SAFEXCEL_ALG_SHA2_256,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = DES_BLOCK_SIZE,
		.maxauthsize = SHA224_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha224),cbc(des))",
			.cra_driver_name = "safexcel-authenc-hmac-sha224-cbc-des",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha224_des_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha512_des_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha512_cra_init(tfm);
	ctx->alg = SAFEXCEL_DES; /* override शेष */
	ctx->blocksz = DES_BLOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha512_cbc_des = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_DES | SAFEXCEL_ALG_SHA2_512,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = DES_BLOCK_SIZE,
		.maxauthsize = SHA512_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha512),cbc(des))",
			.cra_driver_name = "safexcel-authenc-hmac-sha512-cbc-des",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha512_des_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha384_des_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha384_cra_init(tfm);
	ctx->alg = SAFEXCEL_DES; /* override शेष */
	ctx->blocksz = DES_BLOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha384_cbc_des = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_DES | SAFEXCEL_ALG_SHA2_512,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = DES_BLOCK_SIZE,
		.maxauthsize = SHA384_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha384),cbc(des))",
			.cra_driver_name = "safexcel-authenc-hmac-sha384-cbc-des",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha384_des_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha1_ctr_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha1_cra_init(tfm);
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD; /* override शेष */
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha1_ctr_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_SHA1,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = CTR_RFC3686_IV_SIZE,
		.maxauthsize = SHA1_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha1),rfc3686(ctr(aes)))",
			.cra_driver_name = "safexcel-authenc-hmac-sha1-ctr-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha1_ctr_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha256_ctr_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha256_cra_init(tfm);
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD; /* override शेष */
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha256_ctr_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_SHA2_256,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = CTR_RFC3686_IV_SIZE,
		.maxauthsize = SHA256_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha256),rfc3686(ctr(aes)))",
			.cra_driver_name = "safexcel-authenc-hmac-sha256-ctr-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha256_ctr_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha224_ctr_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha224_cra_init(tfm);
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD; /* override शेष */
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha224_ctr_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_SHA2_256,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = CTR_RFC3686_IV_SIZE,
		.maxauthsize = SHA224_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha224),rfc3686(ctr(aes)))",
			.cra_driver_name = "safexcel-authenc-hmac-sha224-ctr-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha224_ctr_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha512_ctr_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha512_cra_init(tfm);
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD; /* override शेष */
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha512_ctr_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_SHA2_512,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = CTR_RFC3686_IV_SIZE,
		.maxauthsize = SHA512_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha512),rfc3686(ctr(aes)))",
			.cra_driver_name = "safexcel-authenc-hmac-sha512-ctr-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha512_ctr_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sha384_ctr_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha384_cra_init(tfm);
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD; /* override शेष */
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha384_ctr_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_SHA2_512,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = CTR_RFC3686_IV_SIZE,
		.maxauthsize = SHA384_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha384),rfc3686(ctr(aes)))",
			.cra_driver_name = "safexcel-authenc-hmac-sha384-ctr-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sha384_ctr_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_skcipher_aesxts_setkey(काष्ठा crypto_skcipher *ctfm,
					   स्थिर u8 *key, अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(ctfm);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	काष्ठा crypto_aes_ctx aes;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक keylen;

	/* Check क्रम illegal XTS keys */
	ret = xts_verअगरy_key(ctfm, key, len);
	अगर (ret)
		वापस ret;

	/* Only half of the key data is cipher key */
	keylen = (len >> 1);
	ret = aes_expandkey(&aes, key, keylen);
	अगर (ret)
		वापस ret;

	अगर (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma) अणु
		क्रम (i = 0; i < keylen / माप(u32); i++) अणु
			अगर (le32_to_cpu(ctx->key[i]) != aes.key_enc[i]) अणु
				ctx->base.needs_inv = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < keylen / माप(u32); i++)
		ctx->key[i] = cpu_to_le32(aes.key_enc[i]);

	/* The other half is the tweak key */
	ret = aes_expandkey(&aes, (u8 *)(key + keylen), keylen);
	अगर (ret)
		वापस ret;

	अगर (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma) अणु
		क्रम (i = 0; i < keylen / माप(u32); i++) अणु
			अगर (le32_to_cpu(ctx->key[i + keylen / माप(u32)]) !=
			    aes.key_enc[i]) अणु
				ctx->base.needs_inv = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < keylen / माप(u32); i++)
		ctx->key[i + keylen / माप(u32)] =
			cpu_to_le32(aes.key_enc[i]);

	ctx->key_len = keylen << 1;

	memzero_explicit(&aes, माप(aes));
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_skcipher_aes_xts_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_AES;
	ctx->blocksz = AES_BLOCK_SIZE;
	ctx->xts  = 1;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_XTS;
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_encrypt_xts(काष्ठा skcipher_request *req)
अणु
	अगर (req->cryptlen < XTS_BLOCK_SIZE)
		वापस -EINVAL;
	वापस safexcel_queue_req(&req->base, skcipher_request_ctx(req),
				  SAFEXCEL_ENCRYPT);
पूर्ण

अटल पूर्णांक safexcel_decrypt_xts(काष्ठा skcipher_request *req)
अणु
	अगर (req->cryptlen < XTS_BLOCK_SIZE)
		वापस -EINVAL;
	वापस safexcel_queue_req(&req->base, skcipher_request_ctx(req),
				  SAFEXCEL_DECRYPT);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_xts_aes = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_AES_XTS,
	.alg.skcipher = अणु
		.setkey = safexcel_skcipher_aesxts_setkey,
		.encrypt = safexcel_encrypt_xts,
		.decrypt = safexcel_decrypt_xts,
		/* XTS actually uses 2 AES keys glued together */
		.min_keysize = AES_MIN_KEY_SIZE * 2,
		.max_keysize = AES_MAX_KEY_SIZE * 2,
		.ivsize = XTS_BLOCK_SIZE,
		.base = अणु
			.cra_name = "xts(aes)",
			.cra_driver_name = "safexcel-xts-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = XTS_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_aes_xts_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_gcm_setkey(काष्ठा crypto_aead *ctfm, स्थिर u8 *key,
				    अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(ctfm);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	काष्ठा crypto_aes_ctx aes;
	u32 hashkey[AES_BLOCK_SIZE >> 2];
	पूर्णांक ret, i;

	ret = aes_expandkey(&aes, key, len);
	अगर (ret) अणु
		memzero_explicit(&aes, माप(aes));
		वापस ret;
	पूर्ण

	अगर (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma) अणु
		क्रम (i = 0; i < len / माप(u32); i++) अणु
			अगर (le32_to_cpu(ctx->key[i]) != aes.key_enc[i]) अणु
				ctx->base.needs_inv = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < len / माप(u32); i++)
		ctx->key[i] = cpu_to_le32(aes.key_enc[i]);

	ctx->key_len = len;

	/* Compute hash key by encrypting zeroes with cipher key */
	crypto_cipher_clear_flags(ctx->hkaes, CRYPTO_TFM_REQ_MASK);
	crypto_cipher_set_flags(ctx->hkaes, crypto_aead_get_flags(ctfm) &
				CRYPTO_TFM_REQ_MASK);
	ret = crypto_cipher_setkey(ctx->hkaes, key, len);
	अगर (ret)
		वापस ret;

	स_रखो(hashkey, 0, AES_BLOCK_SIZE);
	crypto_cipher_encrypt_one(ctx->hkaes, (u8 *)hashkey, (u8 *)hashkey);

	अगर (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma) अणु
		क्रम (i = 0; i < AES_BLOCK_SIZE / माप(u32); i++) अणु
			अगर (be32_to_cpu(ctx->base.ipad.be[i]) != hashkey[i]) अणु
				ctx->base.needs_inv = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < AES_BLOCK_SIZE / माप(u32); i++)
		ctx->base.ipad.be[i] = cpu_to_be32(hashkey[i]);

	memzero_explicit(hashkey, AES_BLOCK_SIZE);
	memzero_explicit(&aes, माप(aes));
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_aead_gcm_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_cra_init(tfm);
	ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_GHASH;
	ctx->state_sz = GHASH_BLOCK_SIZE;
	ctx->xcm = EIP197_XCM_MODE_GCM;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_XCM; /* override शेष */

	ctx->hkaes = crypto_alloc_cipher("aes", 0, 0);
	वापस PTR_ERR_OR_ZERO(ctx->hkaes);
पूर्ण

अटल व्योम safexcel_aead_gcm_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_cipher(ctx->hkaes);
	safexcel_aead_cra_निकास(tfm);
पूर्ण

अटल पूर्णांक safexcel_aead_gcm_setauthsize(काष्ठा crypto_aead *tfm,
					 अचिन्हित पूर्णांक authsize)
अणु
	वापस crypto_gcm_check_authsize(authsize);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_gcm = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_GHASH,
	.alg.aead = अणु
		.setkey = safexcel_aead_gcm_setkey,
		.setauthsize = safexcel_aead_gcm_setauthsize,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = GCM_AES_IV_SIZE,
		.maxauthsize = GHASH_DIGEST_SIZE,
		.base = अणु
			.cra_name = "gcm(aes)",
			.cra_driver_name = "safexcel-gcm-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_gcm_cra_init,
			.cra_निकास = safexcel_aead_gcm_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_ccm_setkey(काष्ठा crypto_aead *ctfm, स्थिर u8 *key,
				    अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(ctfm);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	काष्ठा crypto_aes_ctx aes;
	पूर्णांक ret, i;

	ret = aes_expandkey(&aes, key, len);
	अगर (ret) अणु
		memzero_explicit(&aes, माप(aes));
		वापस ret;
	पूर्ण

	अगर (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma) अणु
		क्रम (i = 0; i < len / माप(u32); i++) अणु
			अगर (le32_to_cpu(ctx->key[i]) != aes.key_enc[i]) अणु
				ctx->base.needs_inv = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < len / माप(u32); i++) अणु
		ctx->key[i] = cpu_to_le32(aes.key_enc[i]);
		ctx->base.ipad.be[i + 2 * AES_BLOCK_SIZE / माप(u32)] =
			cpu_to_be32(aes.key_enc[i]);
	पूर्ण

	ctx->key_len = len;
	ctx->state_sz = 2 * AES_BLOCK_SIZE + len;

	अगर (len == AES_KEYSIZE_192)
		ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_XCBC192;
	अन्यथा अगर (len == AES_KEYSIZE_256)
		ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_XCBC256;
	अन्यथा
		ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_XCBC128;

	memzero_explicit(&aes, माप(aes));
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_aead_ccm_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_cra_init(tfm);
	ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_XCBC128;
	ctx->state_sz = 3 * AES_BLOCK_SIZE;
	ctx->xcm = EIP197_XCM_MODE_CCM;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_XCM; /* override शेष */
	ctx->ctrinit = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_aead_ccm_setauthsize(काष्ठा crypto_aead *tfm,
					 अचिन्हित पूर्णांक authsize)
अणु
	/* Borrowed from crypto/ccm.c */
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

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_ccm_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा safexcel_cipher_req *creq = aead_request_ctx(req);

	अगर (req->iv[0] < 1 || req->iv[0] > 7)
		वापस -EINVAL;

	वापस safexcel_queue_req(&req->base, creq, SAFEXCEL_ENCRYPT);
पूर्ण

अटल पूर्णांक safexcel_ccm_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा safexcel_cipher_req *creq = aead_request_ctx(req);

	अगर (req->iv[0] < 1 || req->iv[0] > 7)
		वापस -EINVAL;

	वापस safexcel_queue_req(&req->base, creq, SAFEXCEL_DECRYPT);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_ccm = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_CBC_MAC_ALL,
	.alg.aead = अणु
		.setkey = safexcel_aead_ccm_setkey,
		.setauthsize = safexcel_aead_ccm_setauthsize,
		.encrypt = safexcel_ccm_encrypt,
		.decrypt = safexcel_ccm_decrypt,
		.ivsize = AES_BLOCK_SIZE,
		.maxauthsize = AES_BLOCK_SIZE,
		.base = अणु
			.cra_name = "ccm(aes)",
			.cra_driver_name = "safexcel-ccm-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_ccm_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम safexcel_chacha20_setkey(काष्ठा safexcel_cipher_ctx *ctx,
				     स्थिर u8 *key)
अणु
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;

	अगर (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma)
		अगर (स_भेद(ctx->key, key, CHACHA_KEY_SIZE))
			ctx->base.needs_inv = true;

	स_नकल(ctx->key, key, CHACHA_KEY_SIZE);
	ctx->key_len = CHACHA_KEY_SIZE;
पूर्ण

अटल पूर्णांक safexcel_skcipher_chacha20_setkey(काष्ठा crypto_skcipher *ctfm,
					     स्थिर u8 *key, अचिन्हित पूर्णांक len)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_skcipher_ctx(ctfm);

	अगर (len != CHACHA_KEY_SIZE)
		वापस -EINVAL;

	safexcel_chacha20_setkey(ctx, key);

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_skcipher_chacha20_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_CHACHA20;
	ctx->ctrinit = 0;
	ctx->mode = CONTEXT_CONTROL_CHACHA20_MODE_256_32;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_chacha20 = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_CHACHA20,
	.alg.skcipher = अणु
		.setkey = safexcel_skcipher_chacha20_setkey,
		.encrypt = safexcel_encrypt,
		.decrypt = safexcel_decrypt,
		.min_keysize = CHACHA_KEY_SIZE,
		.max_keysize = CHACHA_KEY_SIZE,
		.ivsize = CHACHA_IV_SIZE,
		.base = अणु
			.cra_name = "chacha20",
			.cra_driver_name = "safexcel-chacha20",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_chacha20_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_chachapoly_setkey(काष्ठा crypto_aead *ctfm,
				    स्थिर u8 *key, अचिन्हित पूर्णांक len)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_aead_ctx(ctfm);

	अगर (ctx->aead  == EIP197_AEAD_TYPE_IPSEC_ESP &&
	    len > EIP197_AEAD_IPSEC_NONCE_SIZE) अणु
		/* ESP variant has nonce appended to key */
		len -= EIP197_AEAD_IPSEC_NONCE_SIZE;
		ctx->nonce = *(u32 *)(key + len);
	पूर्ण
	अगर (len != CHACHA_KEY_SIZE)
		वापस -EINVAL;

	safexcel_chacha20_setkey(ctx, key);

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_aead_chachapoly_setauthsize(काष्ठा crypto_aead *tfm,
					 अचिन्हित पूर्णांक authsize)
अणु
	अगर (authsize != POLY1305_DIGEST_SIZE)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_aead_chachapoly_crypt(काष्ठा aead_request *req,
					  क्रमागत safexcel_cipher_direction dir)
अणु
	काष्ठा safexcel_cipher_req *creq = aead_request_ctx(req);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(aead);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा aead_request *subreq = aead_request_ctx(req);
	u32 key[CHACHA_KEY_SIZE / माप(u32) + 1];
	पूर्णांक ret = 0;

	/*
	 * Instead of wasting समय detecting umpteen silly corner हालs,
	 * just dump all "small" requests to the fallback implementation.
	 * HW would not be faster on such small requests anyway.
	 */
	अगर (likely((ctx->aead != EIP197_AEAD_TYPE_IPSEC_ESP ||
		    req->assoclen >= EIP197_AEAD_IPSEC_IV_SIZE) &&
		   req->cryptlen > POLY1305_DIGEST_SIZE)) अणु
		वापस safexcel_queue_req(&req->base, creq, dir);
	पूर्ण

	/* HW cannot करो full (AAD+payload) zero length, use fallback */
	स_नकल(key, ctx->key, CHACHA_KEY_SIZE);
	अगर (ctx->aead == EIP197_AEAD_TYPE_IPSEC_ESP) अणु
		/* ESP variant has nonce appended to the key */
		key[CHACHA_KEY_SIZE / माप(u32)] = ctx->nonce;
		ret = crypto_aead_setkey(ctx->fback, (u8 *)key,
					 CHACHA_KEY_SIZE +
					 EIP197_AEAD_IPSEC_NONCE_SIZE);
	पूर्ण अन्यथा अणु
		ret = crypto_aead_setkey(ctx->fback, (u8 *)key,
					 CHACHA_KEY_SIZE);
	पूर्ण
	अगर (ret) अणु
		crypto_aead_clear_flags(aead, CRYPTO_TFM_REQ_MASK);
		crypto_aead_set_flags(aead, crypto_aead_get_flags(ctx->fback) &
					    CRYPTO_TFM_REQ_MASK);
		वापस ret;
	पूर्ण

	aead_request_set_tfm(subreq, ctx->fback);
	aead_request_set_callback(subreq, req->base.flags, req->base.complete,
				  req->base.data);
	aead_request_set_crypt(subreq, req->src, req->dst, req->cryptlen,
			       req->iv);
	aead_request_set_ad(subreq, req->assoclen);

	वापस (dir ==  SAFEXCEL_ENCRYPT) ?
		crypto_aead_encrypt(subreq) :
		crypto_aead_decrypt(subreq);
पूर्ण

अटल पूर्णांक safexcel_aead_chachapoly_encrypt(काष्ठा aead_request *req)
अणु
	वापस safexcel_aead_chachapoly_crypt(req, SAFEXCEL_ENCRYPT);
पूर्ण

अटल पूर्णांक safexcel_aead_chachapoly_decrypt(काष्ठा aead_request *req)
अणु
	वापस safexcel_aead_chachapoly_crypt(req, SAFEXCEL_DECRYPT);
पूर्ण

अटल पूर्णांक safexcel_aead_fallback_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_aead *aead = __crypto_aead_cast(tfm);
	काष्ठा aead_alg *alg = crypto_aead_alg(aead);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_cra_init(tfm);

	/* Allocate fallback implementation */
	ctx->fback = crypto_alloc_aead(alg->base.cra_name, 0,
				       CRYPTO_ALG_ASYNC |
				       CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(ctx->fback))
		वापस PTR_ERR(ctx->fback);

	crypto_aead_set_reqsize(aead, max(माप(काष्ठा safexcel_cipher_req),
					  माप(काष्ठा aead_request) +
					  crypto_aead_reqsize(ctx->fback)));

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_aead_chachapoly_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_fallback_cra_init(tfm);
	ctx->alg  = SAFEXCEL_CHACHA20;
	ctx->mode = CONTEXT_CONTROL_CHACHA20_MODE_256_32 |
		    CONTEXT_CONTROL_CHACHA20_MODE_CALC_OTK;
	ctx->ctrinit = 0;
	ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_POLY1305;
	ctx->state_sz = 0; /* Precomputed by HW */
	वापस 0;
पूर्ण

अटल व्योम safexcel_aead_fallback_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_aead(ctx->fback);
	safexcel_aead_cra_निकास(tfm);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_chachapoly = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_CHACHA20 | SAFEXCEL_ALG_POLY1305,
	.alg.aead = अणु
		.setkey = safexcel_aead_chachapoly_setkey,
		.setauthsize = safexcel_aead_chachapoly_setauthsize,
		.encrypt = safexcel_aead_chachapoly_encrypt,
		.decrypt = safexcel_aead_chachapoly_decrypt,
		.ivsize = CHACHAPOLY_IV_SIZE,
		.maxauthsize = POLY1305_DIGEST_SIZE,
		.base = अणु
			.cra_name = "rfc7539(chacha20,poly1305)",
			.cra_driver_name = "safexcel-chacha20-poly1305",
			/* +1 to put it above HW chacha + SW poly */
			.cra_priority = SAFEXCEL_CRA_PRIORITY + 1,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY |
				     CRYPTO_ALG_NEED_FALLBACK,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_chachapoly_cra_init,
			.cra_निकास = safexcel_aead_fallback_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_chachapolyesp_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक ret;

	ret = safexcel_aead_chachapoly_cra_init(tfm);
	ctx->aead  = EIP197_AEAD_TYPE_IPSEC_ESP;
	ctx->aadskip = EIP197_AEAD_IPSEC_IV_SIZE;
	वापस ret;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_chachapoly_esp = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_CHACHA20 | SAFEXCEL_ALG_POLY1305,
	.alg.aead = अणु
		.setkey = safexcel_aead_chachapoly_setkey,
		.setauthsize = safexcel_aead_chachapoly_setauthsize,
		.encrypt = safexcel_aead_chachapoly_encrypt,
		.decrypt = safexcel_aead_chachapoly_decrypt,
		.ivsize = CHACHAPOLY_IV_SIZE - EIP197_AEAD_IPSEC_NONCE_SIZE,
		.maxauthsize = POLY1305_DIGEST_SIZE,
		.base = अणु
			.cra_name = "rfc7539esp(chacha20,poly1305)",
			.cra_driver_name = "safexcel-chacha20-poly1305-esp",
			/* +1 to put it above HW chacha + SW poly */
			.cra_priority = SAFEXCEL_CRA_PRIORITY + 1,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY |
				     CRYPTO_ALG_NEED_FALLBACK,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_chachapolyesp_cra_init,
			.cra_निकास = safexcel_aead_fallback_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_skcipher_sm4_setkey(काष्ठा crypto_skcipher *ctfm,
					स्थिर u8 *key, अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(ctfm);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;

	अगर (len != SM4_KEY_SIZE)
		वापस -EINVAL;

	अगर (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma)
		अगर (स_भेद(ctx->key, key, SM4_KEY_SIZE))
			ctx->base.needs_inv = true;

	स_नकल(ctx->key, key, SM4_KEY_SIZE);
	ctx->key_len = SM4_KEY_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_sm4_blk_encrypt(काष्ठा skcipher_request *req)
अणु
	/* Workaround क्रम HW bug: EIP96 4.3 करोes not report blocksize error */
	अगर (req->cryptlen & (SM4_BLOCK_SIZE - 1))
		वापस -EINVAL;
	अन्यथा
		वापस safexcel_queue_req(&req->base, skcipher_request_ctx(req),
					  SAFEXCEL_ENCRYPT);
पूर्ण

अटल पूर्णांक safexcel_sm4_blk_decrypt(काष्ठा skcipher_request *req)
अणु
	/* Workaround क्रम HW bug: EIP96 4.3 करोes not report blocksize error */
	अगर (req->cryptlen & (SM4_BLOCK_SIZE - 1))
		वापस -EINVAL;
	अन्यथा
		वापस safexcel_queue_req(&req->base, skcipher_request_ctx(req),
					  SAFEXCEL_DECRYPT);
पूर्ण

अटल पूर्णांक safexcel_skcipher_sm4_ecb_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_SM4;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_ECB;
	ctx->blocksz = 0;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_ecb_sm4 = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_SM4,
	.alg.skcipher = अणु
		.setkey = safexcel_skcipher_sm4_setkey,
		.encrypt = safexcel_sm4_blk_encrypt,
		.decrypt = safexcel_sm4_blk_decrypt,
		.min_keysize = SM4_KEY_SIZE,
		.max_keysize = SM4_KEY_SIZE,
		.base = अणु
			.cra_name = "ecb(sm4)",
			.cra_driver_name = "safexcel-ecb-sm4",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = SM4_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_sm4_ecb_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_skcipher_sm4_cbc_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_SM4;
	ctx->blocksz = SM4_BLOCK_SIZE;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CBC;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_cbc_sm4 = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_SM4,
	.alg.skcipher = अणु
		.setkey = safexcel_skcipher_sm4_setkey,
		.encrypt = safexcel_sm4_blk_encrypt,
		.decrypt = safexcel_sm4_blk_decrypt,
		.min_keysize = SM4_KEY_SIZE,
		.max_keysize = SM4_KEY_SIZE,
		.ivsize = SM4_BLOCK_SIZE,
		.base = अणु
			.cra_name = "cbc(sm4)",
			.cra_driver_name = "safexcel-cbc-sm4",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = SM4_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_sm4_cbc_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_skcipher_sm4_ofb_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_SM4;
	ctx->blocksz = SM4_BLOCK_SIZE;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_OFB;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_ofb_sm4 = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_SM4 | SAFEXCEL_ALG_AES_XFB,
	.alg.skcipher = अणु
		.setkey = safexcel_skcipher_sm4_setkey,
		.encrypt = safexcel_encrypt,
		.decrypt = safexcel_decrypt,
		.min_keysize = SM4_KEY_SIZE,
		.max_keysize = SM4_KEY_SIZE,
		.ivsize = SM4_BLOCK_SIZE,
		.base = अणु
			.cra_name = "ofb(sm4)",
			.cra_driver_name = "safexcel-ofb-sm4",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_sm4_ofb_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_skcipher_sm4_cfb_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_SM4;
	ctx->blocksz = SM4_BLOCK_SIZE;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CFB;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_cfb_sm4 = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_SM4 | SAFEXCEL_ALG_AES_XFB,
	.alg.skcipher = अणु
		.setkey = safexcel_skcipher_sm4_setkey,
		.encrypt = safexcel_encrypt,
		.decrypt = safexcel_decrypt,
		.min_keysize = SM4_KEY_SIZE,
		.max_keysize = SM4_KEY_SIZE,
		.ivsize = SM4_BLOCK_SIZE,
		.base = अणु
			.cra_name = "cfb(sm4)",
			.cra_driver_name = "safexcel-cfb-sm4",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_sm4_cfb_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_skcipher_sm4ctr_setkey(काष्ठा crypto_skcipher *ctfm,
					   स्थिर u8 *key, अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(ctfm);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	/* last 4 bytes of key are the nonce! */
	ctx->nonce = *(u32 *)(key + len - CTR_RFC3686_NONCE_SIZE);
	/* exclude the nonce here */
	len -= CTR_RFC3686_NONCE_SIZE;

	वापस safexcel_skcipher_sm4_setkey(ctfm, key, len);
पूर्ण

अटल पूर्णांक safexcel_skcipher_sm4_ctr_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_SM4;
	ctx->blocksz = SM4_BLOCK_SIZE;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_ctr_sm4 = अणु
	.type = SAFEXCEL_ALG_TYPE_SKCIPHER,
	.algo_mask = SAFEXCEL_ALG_SM4,
	.alg.skcipher = अणु
		.setkey = safexcel_skcipher_sm4ctr_setkey,
		.encrypt = safexcel_encrypt,
		.decrypt = safexcel_decrypt,
		/* Add nonce size */
		.min_keysize = SM4_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
		.max_keysize = SM4_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
		.ivsize = CTR_RFC3686_IV_SIZE,
		.base = अणु
			.cra_name = "rfc3686(ctr(sm4))",
			.cra_driver_name = "safexcel-ctr-sm4",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_skcipher_sm4_ctr_cra_init,
			.cra_निकास = safexcel_skcipher_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sm4_blk_encrypt(काष्ठा aead_request *req)
अणु
	/* Workaround क्रम HW bug: EIP96 4.3 करोes not report blocksize error */
	अगर (req->cryptlen & (SM4_BLOCK_SIZE - 1))
		वापस -EINVAL;

	वापस safexcel_queue_req(&req->base, aead_request_ctx(req),
				  SAFEXCEL_ENCRYPT);
पूर्ण

अटल पूर्णांक safexcel_aead_sm4_blk_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);

	/* Workaround क्रम HW bug: EIP96 4.3 करोes not report blocksize error */
	अगर ((req->cryptlen - crypto_aead_authsize(tfm)) & (SM4_BLOCK_SIZE - 1))
		वापस -EINVAL;

	वापस safexcel_queue_req(&req->base, aead_request_ctx(req),
				  SAFEXCEL_DECRYPT);
पूर्ण

अटल पूर्णांक safexcel_aead_sm4cbc_sha1_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_cra_init(tfm);
	ctx->alg = SAFEXCEL_SM4;
	ctx->blocksz = SM4_BLOCK_SIZE;
	ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA1;
	ctx->state_sz = SHA1_DIGEST_SIZE;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha1_cbc_sm4 = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_SM4 | SAFEXCEL_ALG_SHA1,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_sm4_blk_encrypt,
		.decrypt = safexcel_aead_sm4_blk_decrypt,
		.ivsize = SM4_BLOCK_SIZE,
		.maxauthsize = SHA1_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha1),cbc(sm4))",
			.cra_driver_name = "safexcel-authenc-hmac-sha1-cbc-sm4",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = SM4_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sm4cbc_sha1_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_fallback_setkey(काष्ठा crypto_aead *ctfm,
					 स्थिर u8 *key, अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(ctfm);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	/* Keep fallback cipher synchronized */
	वापस crypto_aead_setkey(ctx->fback, (u8 *)key, len) ?:
	       safexcel_aead_setkey(ctfm, key, len);
पूर्ण

अटल पूर्णांक safexcel_aead_fallback_setauthsize(काष्ठा crypto_aead *ctfm,
					      अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(ctfm);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	/* Keep fallback cipher synchronized */
	वापस crypto_aead_setauthsize(ctx->fback, authsize);
पूर्ण

अटल पूर्णांक safexcel_aead_fallback_crypt(काष्ठा aead_request *req,
					क्रमागत safexcel_cipher_direction dir)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(aead);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा aead_request *subreq = aead_request_ctx(req);

	aead_request_set_tfm(subreq, ctx->fback);
	aead_request_set_callback(subreq, req->base.flags, req->base.complete,
				  req->base.data);
	aead_request_set_crypt(subreq, req->src, req->dst, req->cryptlen,
			       req->iv);
	aead_request_set_ad(subreq, req->assoclen);

	वापस (dir ==  SAFEXCEL_ENCRYPT) ?
		crypto_aead_encrypt(subreq) :
		crypto_aead_decrypt(subreq);
पूर्ण

अटल पूर्णांक safexcel_aead_sm4cbc_sm3_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा safexcel_cipher_req *creq = aead_request_ctx(req);

	/* Workaround क्रम HW bug: EIP96 4.3 करोes not report blocksize error */
	अगर (req->cryptlen & (SM4_BLOCK_SIZE - 1))
		वापस -EINVAL;
	अन्यथा अगर (req->cryptlen || req->assoclen) /* If input length > 0 only */
		वापस safexcel_queue_req(&req->base, creq, SAFEXCEL_ENCRYPT);

	/* HW cannot करो full (AAD+payload) zero length, use fallback */
	वापस safexcel_aead_fallback_crypt(req, SAFEXCEL_ENCRYPT);
पूर्ण

अटल पूर्णांक safexcel_aead_sm4cbc_sm3_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा safexcel_cipher_req *creq = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);

	/* Workaround क्रम HW bug: EIP96 4.3 करोes not report blocksize error */
	अगर ((req->cryptlen - crypto_aead_authsize(tfm)) & (SM4_BLOCK_SIZE - 1))
		वापस -EINVAL;
	अन्यथा अगर (req->cryptlen > crypto_aead_authsize(tfm) || req->assoclen)
		/* If input length > 0 only */
		वापस safexcel_queue_req(&req->base, creq, SAFEXCEL_DECRYPT);

	/* HW cannot करो full (AAD+payload) zero length, use fallback */
	वापस safexcel_aead_fallback_crypt(req, SAFEXCEL_DECRYPT);
पूर्ण

अटल पूर्णांक safexcel_aead_sm4cbc_sm3_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_fallback_cra_init(tfm);
	ctx->alg = SAFEXCEL_SM4;
	ctx->blocksz = SM4_BLOCK_SIZE;
	ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_SM3;
	ctx->state_sz = SM3_DIGEST_SIZE;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sm3_cbc_sm4 = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_SM4 | SAFEXCEL_ALG_SM3,
	.alg.aead = अणु
		.setkey = safexcel_aead_fallback_setkey,
		.setauthsize = safexcel_aead_fallback_setauthsize,
		.encrypt = safexcel_aead_sm4cbc_sm3_encrypt,
		.decrypt = safexcel_aead_sm4cbc_sm3_decrypt,
		.ivsize = SM4_BLOCK_SIZE,
		.maxauthsize = SM3_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sm3),cbc(sm4))",
			.cra_driver_name = "safexcel-authenc-hmac-sm3-cbc-sm4",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY |
				     CRYPTO_ALG_NEED_FALLBACK,
			.cra_blocksize = SM4_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sm4cbc_sm3_cra_init,
			.cra_निकास = safexcel_aead_fallback_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sm4ctr_sha1_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sm4cbc_sha1_cra_init(tfm);
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sha1_ctr_sm4 = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_SM4 | SAFEXCEL_ALG_SHA1,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = CTR_RFC3686_IV_SIZE,
		.maxauthsize = SHA1_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sha1),rfc3686(ctr(sm4)))",
			.cra_driver_name = "safexcel-authenc-hmac-sha1-ctr-sm4",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sm4ctr_sha1_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_aead_sm4ctr_sm3_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sm4cbc_sm3_cra_init(tfm);
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD;
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_authenc_hmac_sm3_ctr_sm4 = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_SM4 | SAFEXCEL_ALG_SM3,
	.alg.aead = अणु
		.setkey = safexcel_aead_setkey,
		.encrypt = safexcel_aead_encrypt,
		.decrypt = safexcel_aead_decrypt,
		.ivsize = CTR_RFC3686_IV_SIZE,
		.maxauthsize = SM3_DIGEST_SIZE,
		.base = अणु
			.cra_name = "authenc(hmac(sm3),rfc3686(ctr(sm4)))",
			.cra_driver_name = "safexcel-authenc-hmac-sm3-ctr-sm4",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_aead_sm4ctr_sm3_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_rfc4106_gcm_setkey(काष्ठा crypto_aead *ctfm, स्थिर u8 *key,
				       अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(ctfm);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	/* last 4 bytes of key are the nonce! */
	ctx->nonce = *(u32 *)(key + len - CTR_RFC3686_NONCE_SIZE);

	len -= CTR_RFC3686_NONCE_SIZE;
	वापस safexcel_aead_gcm_setkey(ctfm, key, len);
पूर्ण

अटल पूर्णांक safexcel_rfc4106_gcm_setauthsize(काष्ठा crypto_aead *tfm,
					    अचिन्हित पूर्णांक authsize)
अणु
	वापस crypto_rfc4106_check_authsize(authsize);
पूर्ण

अटल पूर्णांक safexcel_rfc4106_encrypt(काष्ठा aead_request *req)
अणु
	वापस crypto_ipsec_check_assoclen(req->assoclen) ?:
	       safexcel_aead_encrypt(req);
पूर्ण

अटल पूर्णांक safexcel_rfc4106_decrypt(काष्ठा aead_request *req)
अणु
	वापस crypto_ipsec_check_assoclen(req->assoclen) ?:
	       safexcel_aead_decrypt(req);
पूर्ण

अटल पूर्णांक safexcel_rfc4106_gcm_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक ret;

	ret = safexcel_aead_gcm_cra_init(tfm);
	ctx->aead  = EIP197_AEAD_TYPE_IPSEC_ESP;
	ctx->aadskip = EIP197_AEAD_IPSEC_IV_SIZE;
	वापस ret;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_rfc4106_gcm = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_GHASH,
	.alg.aead = अणु
		.setkey = safexcel_rfc4106_gcm_setkey,
		.setauthsize = safexcel_rfc4106_gcm_setauthsize,
		.encrypt = safexcel_rfc4106_encrypt,
		.decrypt = safexcel_rfc4106_decrypt,
		.ivsize = GCM_RFC4106_IV_SIZE,
		.maxauthsize = GHASH_DIGEST_SIZE,
		.base = अणु
			.cra_name = "rfc4106(gcm(aes))",
			.cra_driver_name = "safexcel-rfc4106-gcm-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_rfc4106_gcm_cra_init,
			.cra_निकास = safexcel_aead_gcm_cra_निकास,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_rfc4543_gcm_setauthsize(काष्ठा crypto_aead *tfm,
					    अचिन्हित पूर्णांक authsize)
अणु
	अगर (authsize != GHASH_DIGEST_SIZE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_rfc4543_gcm_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक ret;

	ret = safexcel_aead_gcm_cra_init(tfm);
	ctx->aead  = EIP197_AEAD_TYPE_IPSEC_ESP_GMAC;
	वापस ret;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_rfc4543_gcm = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_GHASH,
	.alg.aead = अणु
		.setkey = safexcel_rfc4106_gcm_setkey,
		.setauthsize = safexcel_rfc4543_gcm_setauthsize,
		.encrypt = safexcel_rfc4106_encrypt,
		.decrypt = safexcel_rfc4106_decrypt,
		.ivsize = GCM_RFC4543_IV_SIZE,
		.maxauthsize = GHASH_DIGEST_SIZE,
		.base = अणु
			.cra_name = "rfc4543(gcm(aes))",
			.cra_driver_name = "safexcel-rfc4543-gcm-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_rfc4543_gcm_cra_init,
			.cra_निकास = safexcel_aead_gcm_cra_निकास,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_rfc4309_ccm_setkey(काष्ठा crypto_aead *ctfm, स्थिर u8 *key,
				       अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(ctfm);
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	/* First byte of the nonce = L = always 3 क्रम RFC4309 (4 byte ctr) */
	*(u8 *)&ctx->nonce = EIP197_AEAD_IPSEC_COUNTER_SIZE - 1;
	/* last 3 bytes of key are the nonce! */
	स_नकल((u8 *)&ctx->nonce + 1, key + len -
	       EIP197_AEAD_IPSEC_CCM_NONCE_SIZE,
	       EIP197_AEAD_IPSEC_CCM_NONCE_SIZE);

	len -= EIP197_AEAD_IPSEC_CCM_NONCE_SIZE;
	वापस safexcel_aead_ccm_setkey(ctfm, key, len);
पूर्ण

अटल पूर्णांक safexcel_rfc4309_ccm_setauthsize(काष्ठा crypto_aead *tfm,
					    अचिन्हित पूर्णांक authsize)
अणु
	/* Borrowed from crypto/ccm.c */
	चयन (authsize) अणु
	हाल 8:
	हाल 12:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_rfc4309_ccm_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा safexcel_cipher_req *creq = aead_request_ctx(req);

	/* Borrowed from crypto/ccm.c */
	अगर (req->assoclen != 16 && req->assoclen != 20)
		वापस -EINVAL;

	वापस safexcel_queue_req(&req->base, creq, SAFEXCEL_ENCRYPT);
पूर्ण

अटल पूर्णांक safexcel_rfc4309_ccm_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा safexcel_cipher_req *creq = aead_request_ctx(req);

	/* Borrowed from crypto/ccm.c */
	अगर (req->assoclen != 16 && req->assoclen != 20)
		वापस -EINVAL;

	वापस safexcel_queue_req(&req->base, creq, SAFEXCEL_DECRYPT);
पूर्ण

अटल पूर्णांक safexcel_rfc4309_ccm_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक ret;

	ret = safexcel_aead_ccm_cra_init(tfm);
	ctx->aead  = EIP197_AEAD_TYPE_IPSEC_ESP;
	ctx->aadskip = EIP197_AEAD_IPSEC_IV_SIZE;
	वापस ret;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_rfc4309_ccm = अणु
	.type = SAFEXCEL_ALG_TYPE_AEAD,
	.algo_mask = SAFEXCEL_ALG_AES | SAFEXCEL_ALG_CBC_MAC_ALL,
	.alg.aead = अणु
		.setkey = safexcel_rfc4309_ccm_setkey,
		.setauthsize = safexcel_rfc4309_ccm_setauthsize,
		.encrypt = safexcel_rfc4309_ccm_encrypt,
		.decrypt = safexcel_rfc4309_ccm_decrypt,
		.ivsize = EIP197_AEAD_IPSEC_IV_SIZE,
		.maxauthsize = AES_BLOCK_SIZE,
		.base = अणु
			.cra_name = "rfc4309(ccm(aes))",
			.cra_driver_name = "safexcel-rfc4309-ccm-aes",
			.cra_priority = SAFEXCEL_CRA_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा safexcel_cipher_ctx),
			.cra_alignmask = 0,
			.cra_init = safexcel_rfc4309_ccm_cra_init,
			.cra_निकास = safexcel_aead_cra_निकास,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;
