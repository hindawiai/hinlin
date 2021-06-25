<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/hmac.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/xts.h>
#समावेश <linux/dma-mapping.h>
#समावेश "adf_accel_devices.h"
#समावेश "adf_transport.h"
#समावेश "adf_common_drv.h"
#समावेश "qat_crypto.h"
#समावेश "icp_qat_hw.h"
#समावेश "icp_qat_fw.h"
#समावेश "icp_qat_fw_la.h"

#घोषणा QAT_AES_HW_CONFIG_ENC(alg, mode) \
	ICP_QAT_HW_CIPHER_CONFIG_BUILD(mode, alg, \
				       ICP_QAT_HW_CIPHER_NO_CONVERT, \
				       ICP_QAT_HW_CIPHER_ENCRYPT)

#घोषणा QAT_AES_HW_CONFIG_DEC(alg, mode) \
	ICP_QAT_HW_CIPHER_CONFIG_BUILD(mode, alg, \
				       ICP_QAT_HW_CIPHER_KEY_CONVERT, \
				       ICP_QAT_HW_CIPHER_DECRYPT)

#घोषणा QAT_AES_HW_CONFIG_DEC_NO_CONV(alg, mode) \
	ICP_QAT_HW_CIPHER_CONFIG_BUILD(mode, alg, \
				       ICP_QAT_HW_CIPHER_NO_CONVERT, \
				       ICP_QAT_HW_CIPHER_DECRYPT)

#घोषणा HW_CAP_AES_V2(accel_dev) \
	(GET_HW_DATA(accel_dev)->accel_capabilities_mask & \
	 ICP_ACCEL_CAPABILITIES_AES_V2)

अटल DEFINE_MUTEX(algs_lock);
अटल अचिन्हित पूर्णांक active_devs;

काष्ठा qat_alg_buf अणु
	u32 len;
	u32 resrvd;
	u64 addr;
पूर्ण __packed;

काष्ठा qat_alg_buf_list अणु
	u64 resrvd;
	u32 num_bufs;
	u32 num_mapped_bufs;
	काष्ठा qat_alg_buf bufers[];
पूर्ण __packed __aligned(64);

/* Common content descriptor */
काष्ठा qat_alg_cd अणु
	जोड़ अणु
		काष्ठा qat_enc अणु /* Encrypt content desc */
			काष्ठा icp_qat_hw_cipher_algo_blk cipher;
			काष्ठा icp_qat_hw_auth_algo_blk hash;
		पूर्ण qat_enc_cd;
		काष्ठा qat_dec अणु /* Decrypt content desc */
			काष्ठा icp_qat_hw_auth_algo_blk hash;
			काष्ठा icp_qat_hw_cipher_algo_blk cipher;
		पूर्ण qat_dec_cd;
	पूर्ण;
पूर्ण __aligned(64);

काष्ठा qat_alg_aead_ctx अणु
	काष्ठा qat_alg_cd *enc_cd;
	काष्ठा qat_alg_cd *dec_cd;
	dma_addr_t enc_cd_paddr;
	dma_addr_t dec_cd_paddr;
	काष्ठा icp_qat_fw_la_bulk_req enc_fw_req;
	काष्ठा icp_qat_fw_la_bulk_req dec_fw_req;
	काष्ठा crypto_shash *hash_tfm;
	क्रमागत icp_qat_hw_auth_algo qat_hash_alg;
	काष्ठा qat_crypto_instance *inst;
	जोड़ अणु
		काष्ठा sha1_state sha1;
		काष्ठा sha256_state sha256;
		काष्ठा sha512_state sha512;
	पूर्ण;
	अक्षर ipad[SHA512_BLOCK_SIZE]; /* sufficient क्रम SHA-1/SHA-256 as well */
	अक्षर opad[SHA512_BLOCK_SIZE];
पूर्ण;

काष्ठा qat_alg_skcipher_ctx अणु
	काष्ठा icp_qat_hw_cipher_algo_blk *enc_cd;
	काष्ठा icp_qat_hw_cipher_algo_blk *dec_cd;
	dma_addr_t enc_cd_paddr;
	dma_addr_t dec_cd_paddr;
	काष्ठा icp_qat_fw_la_bulk_req enc_fw_req;
	काष्ठा icp_qat_fw_la_bulk_req dec_fw_req;
	काष्ठा qat_crypto_instance *inst;
	काष्ठा crypto_skcipher *ftfm;
	काष्ठा crypto_cipher *tweak;
	bool fallback;
	पूर्णांक mode;
पूर्ण;

अटल पूर्णांक qat_get_पूर्णांकer_state_size(क्रमागत icp_qat_hw_auth_algo qat_hash_alg)
अणु
	चयन (qat_hash_alg) अणु
	हाल ICP_QAT_HW_AUTH_ALGO_SHA1:
		वापस ICP_QAT_HW_SHA1_STATE1_SZ;
	हाल ICP_QAT_HW_AUTH_ALGO_SHA256:
		वापस ICP_QAT_HW_SHA256_STATE1_SZ;
	हाल ICP_QAT_HW_AUTH_ALGO_SHA512:
		वापस ICP_QAT_HW_SHA512_STATE1_SZ;
	शेष:
		वापस -EFAULT;
	पूर्ण
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक qat_alg_करो_precomputes(काष्ठा icp_qat_hw_auth_algo_blk *hash,
				  काष्ठा qat_alg_aead_ctx *ctx,
				  स्थिर u8 *auth_key,
				  अचिन्हित पूर्णांक auth_keylen)
अणु
	SHASH_DESC_ON_STACK(shash, ctx->hash_tfm);
	पूर्णांक block_size = crypto_shash_blocksize(ctx->hash_tfm);
	पूर्णांक digest_size = crypto_shash_digestsize(ctx->hash_tfm);
	__be32 *hash_state_out;
	__be64 *hash512_state_out;
	पूर्णांक i, offset;

	स_रखो(ctx->ipad, 0, block_size);
	स_रखो(ctx->opad, 0, block_size);
	shash->tfm = ctx->hash_tfm;

	अगर (auth_keylen > block_size) अणु
		पूर्णांक ret = crypto_shash_digest(shash, auth_key,
					      auth_keylen, ctx->ipad);
		अगर (ret)
			वापस ret;

		स_नकल(ctx->opad, ctx->ipad, digest_size);
	पूर्ण अन्यथा अणु
		स_नकल(ctx->ipad, auth_key, auth_keylen);
		स_नकल(ctx->opad, auth_key, auth_keylen);
	पूर्ण

	क्रम (i = 0; i < block_size; i++) अणु
		अक्षर *ipad_ptr = ctx->ipad + i;
		अक्षर *opad_ptr = ctx->opad + i;
		*ipad_ptr ^= HMAC_IPAD_VALUE;
		*opad_ptr ^= HMAC_OPAD_VALUE;
	पूर्ण

	अगर (crypto_shash_init(shash))
		वापस -EFAULT;

	अगर (crypto_shash_update(shash, ctx->ipad, block_size))
		वापस -EFAULT;

	hash_state_out = (__be32 *)hash->sha.state1;
	hash512_state_out = (__be64 *)hash_state_out;

	चयन (ctx->qat_hash_alg) अणु
	हाल ICP_QAT_HW_AUTH_ALGO_SHA1:
		अगर (crypto_shash_export(shash, &ctx->sha1))
			वापस -EFAULT;
		क्रम (i = 0; i < digest_size >> 2; i++, hash_state_out++)
			*hash_state_out = cpu_to_be32(ctx->sha1.state[i]);
		अवरोध;
	हाल ICP_QAT_HW_AUTH_ALGO_SHA256:
		अगर (crypto_shash_export(shash, &ctx->sha256))
			वापस -EFAULT;
		क्रम (i = 0; i < digest_size >> 2; i++, hash_state_out++)
			*hash_state_out = cpu_to_be32(ctx->sha256.state[i]);
		अवरोध;
	हाल ICP_QAT_HW_AUTH_ALGO_SHA512:
		अगर (crypto_shash_export(shash, &ctx->sha512))
			वापस -EFAULT;
		क्रम (i = 0; i < digest_size >> 3; i++, hash512_state_out++)
			*hash512_state_out = cpu_to_be64(ctx->sha512.state[i]);
		अवरोध;
	शेष:
		वापस -EFAULT;
	पूर्ण

	अगर (crypto_shash_init(shash))
		वापस -EFAULT;

	अगर (crypto_shash_update(shash, ctx->opad, block_size))
		वापस -EFAULT;

	offset = round_up(qat_get_पूर्णांकer_state_size(ctx->qat_hash_alg), 8);
	अगर (offset < 0)
		वापस -EFAULT;

	hash_state_out = (__be32 *)(hash->sha.state1 + offset);
	hash512_state_out = (__be64 *)hash_state_out;

	चयन (ctx->qat_hash_alg) अणु
	हाल ICP_QAT_HW_AUTH_ALGO_SHA1:
		अगर (crypto_shash_export(shash, &ctx->sha1))
			वापस -EFAULT;
		क्रम (i = 0; i < digest_size >> 2; i++, hash_state_out++)
			*hash_state_out = cpu_to_be32(ctx->sha1.state[i]);
		अवरोध;
	हाल ICP_QAT_HW_AUTH_ALGO_SHA256:
		अगर (crypto_shash_export(shash, &ctx->sha256))
			वापस -EFAULT;
		क्रम (i = 0; i < digest_size >> 2; i++, hash_state_out++)
			*hash_state_out = cpu_to_be32(ctx->sha256.state[i]);
		अवरोध;
	हाल ICP_QAT_HW_AUTH_ALGO_SHA512:
		अगर (crypto_shash_export(shash, &ctx->sha512))
			वापस -EFAULT;
		क्रम (i = 0; i < digest_size >> 3; i++, hash512_state_out++)
			*hash512_state_out = cpu_to_be64(ctx->sha512.state[i]);
		अवरोध;
	शेष:
		वापस -EFAULT;
	पूर्ण
	memzero_explicit(ctx->ipad, block_size);
	memzero_explicit(ctx->opad, block_size);
	वापस 0;
पूर्ण

अटल व्योम qat_alg_init_common_hdr(काष्ठा icp_qat_fw_comn_req_hdr *header)
अणु
	header->hdr_flags =
		ICP_QAT_FW_COMN_HDR_FLAGS_BUILD(ICP_QAT_FW_COMN_REQ_FLAG_SET);
	header->service_type = ICP_QAT_FW_COMN_REQ_CPM_FW_LA;
	header->comn_req_flags =
		ICP_QAT_FW_COMN_FLAGS_BUILD(QAT_COMN_CD_FLD_TYPE_64BIT_ADR,
					    QAT_COMN_PTR_TYPE_SGL);
	ICP_QAT_FW_LA_PARTIAL_SET(header->serv_specअगर_flags,
				  ICP_QAT_FW_LA_PARTIAL_NONE);
	ICP_QAT_FW_LA_CIPH_IV_FLD_FLAG_SET(header->serv_specअगर_flags,
					   ICP_QAT_FW_CIPH_IV_16BYTE_DATA);
	ICP_QAT_FW_LA_PROTO_SET(header->serv_specअगर_flags,
				ICP_QAT_FW_LA_NO_PROTO);
	ICP_QAT_FW_LA_UPDATE_STATE_SET(header->serv_specअगर_flags,
				       ICP_QAT_FW_LA_NO_UPDATE_STATE);
पूर्ण

अटल पूर्णांक qat_alg_aead_init_enc_session(काष्ठा crypto_aead *aead_tfm,
					 पूर्णांक alg,
					 काष्ठा crypto_authenc_keys *keys,
					 पूर्णांक mode)
अणु
	काष्ठा qat_alg_aead_ctx *ctx = crypto_aead_ctx(aead_tfm);
	अचिन्हित पूर्णांक digestsize = crypto_aead_authsize(aead_tfm);
	काष्ठा qat_enc *enc_ctx = &ctx->enc_cd->qat_enc_cd;
	काष्ठा icp_qat_hw_cipher_algo_blk *cipher = &enc_ctx->cipher;
	काष्ठा icp_qat_hw_auth_algo_blk *hash =
		(काष्ठा icp_qat_hw_auth_algo_blk *)((अक्षर *)enc_ctx +
		माप(काष्ठा icp_qat_hw_auth_setup) + keys->enckeylen);
	काष्ठा icp_qat_fw_la_bulk_req *req_पंचांगpl = &ctx->enc_fw_req;
	काष्ठा icp_qat_fw_comn_req_hdr_cd_pars *cd_pars = &req_पंचांगpl->cd_pars;
	काष्ठा icp_qat_fw_comn_req_hdr *header = &req_पंचांगpl->comn_hdr;
	व्योम *ptr = &req_पंचांगpl->cd_ctrl;
	काष्ठा icp_qat_fw_cipher_cd_ctrl_hdr *cipher_cd_ctrl = ptr;
	काष्ठा icp_qat_fw_auth_cd_ctrl_hdr *hash_cd_ctrl = ptr;

	/* CD setup */
	cipher->aes.cipher_config.val = QAT_AES_HW_CONFIG_ENC(alg, mode);
	स_नकल(cipher->aes.key, keys->enckey, keys->enckeylen);
	hash->sha.inner_setup.auth_config.config =
		ICP_QAT_HW_AUTH_CONFIG_BUILD(ICP_QAT_HW_AUTH_MODE1,
					     ctx->qat_hash_alg, digestsize);
	hash->sha.inner_setup.auth_counter.counter =
		cpu_to_be32(crypto_shash_blocksize(ctx->hash_tfm));

	अगर (qat_alg_करो_precomputes(hash, ctx, keys->authkey, keys->authkeylen))
		वापस -EFAULT;

	/* Request setup */
	qat_alg_init_common_hdr(header);
	header->service_cmd_id = ICP_QAT_FW_LA_CMD_CIPHER_HASH;
	ICP_QAT_FW_LA_DIGEST_IN_BUFFER_SET(header->serv_specअगर_flags,
					   ICP_QAT_FW_LA_DIGEST_IN_BUFFER);
	ICP_QAT_FW_LA_RET_AUTH_SET(header->serv_specअगर_flags,
				   ICP_QAT_FW_LA_RET_AUTH_RES);
	ICP_QAT_FW_LA_CMP_AUTH_SET(header->serv_specअगर_flags,
				   ICP_QAT_FW_LA_NO_CMP_AUTH_RES);
	cd_pars->u.s.content_desc_addr = ctx->enc_cd_paddr;
	cd_pars->u.s.content_desc_params_sz = माप(काष्ठा qat_alg_cd) >> 3;

	/* Cipher CD config setup */
	cipher_cd_ctrl->cipher_key_sz = keys->enckeylen >> 3;
	cipher_cd_ctrl->cipher_state_sz = AES_BLOCK_SIZE >> 3;
	cipher_cd_ctrl->cipher_cfg_offset = 0;
	ICP_QAT_FW_COMN_CURR_ID_SET(cipher_cd_ctrl, ICP_QAT_FW_SLICE_CIPHER);
	ICP_QAT_FW_COMN_NEXT_ID_SET(cipher_cd_ctrl, ICP_QAT_FW_SLICE_AUTH);
	/* Auth CD config setup */
	hash_cd_ctrl->hash_cfg_offset = ((अक्षर *)hash - (अक्षर *)cipher) >> 3;
	hash_cd_ctrl->hash_flags = ICP_QAT_FW_AUTH_HDR_FLAG_NO_NESTED;
	hash_cd_ctrl->inner_res_sz = digestsize;
	hash_cd_ctrl->final_sz = digestsize;

	चयन (ctx->qat_hash_alg) अणु
	हाल ICP_QAT_HW_AUTH_ALGO_SHA1:
		hash_cd_ctrl->inner_state1_sz =
			round_up(ICP_QAT_HW_SHA1_STATE1_SZ, 8);
		hash_cd_ctrl->inner_state2_sz =
			round_up(ICP_QAT_HW_SHA1_STATE2_SZ, 8);
		अवरोध;
	हाल ICP_QAT_HW_AUTH_ALGO_SHA256:
		hash_cd_ctrl->inner_state1_sz = ICP_QAT_HW_SHA256_STATE1_SZ;
		hash_cd_ctrl->inner_state2_sz = ICP_QAT_HW_SHA256_STATE2_SZ;
		अवरोध;
	हाल ICP_QAT_HW_AUTH_ALGO_SHA512:
		hash_cd_ctrl->inner_state1_sz = ICP_QAT_HW_SHA512_STATE1_SZ;
		hash_cd_ctrl->inner_state2_sz = ICP_QAT_HW_SHA512_STATE2_SZ;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	hash_cd_ctrl->inner_state2_offset = hash_cd_ctrl->hash_cfg_offset +
			((माप(काष्ठा icp_qat_hw_auth_setup) +
			 round_up(hash_cd_ctrl->inner_state1_sz, 8)) >> 3);
	ICP_QAT_FW_COMN_CURR_ID_SET(hash_cd_ctrl, ICP_QAT_FW_SLICE_AUTH);
	ICP_QAT_FW_COMN_NEXT_ID_SET(hash_cd_ctrl, ICP_QAT_FW_SLICE_DRAM_WR);
	वापस 0;
पूर्ण

अटल पूर्णांक qat_alg_aead_init_dec_session(काष्ठा crypto_aead *aead_tfm,
					 पूर्णांक alg,
					 काष्ठा crypto_authenc_keys *keys,
					 पूर्णांक mode)
अणु
	काष्ठा qat_alg_aead_ctx *ctx = crypto_aead_ctx(aead_tfm);
	अचिन्हित पूर्णांक digestsize = crypto_aead_authsize(aead_tfm);
	काष्ठा qat_dec *dec_ctx = &ctx->dec_cd->qat_dec_cd;
	काष्ठा icp_qat_hw_auth_algo_blk *hash = &dec_ctx->hash;
	काष्ठा icp_qat_hw_cipher_algo_blk *cipher =
		(काष्ठा icp_qat_hw_cipher_algo_blk *)((अक्षर *)dec_ctx +
		माप(काष्ठा icp_qat_hw_auth_setup) +
		roundup(crypto_shash_digestsize(ctx->hash_tfm), 8) * 2);
	काष्ठा icp_qat_fw_la_bulk_req *req_पंचांगpl = &ctx->dec_fw_req;
	काष्ठा icp_qat_fw_comn_req_hdr_cd_pars *cd_pars = &req_पंचांगpl->cd_pars;
	काष्ठा icp_qat_fw_comn_req_hdr *header = &req_पंचांगpl->comn_hdr;
	व्योम *ptr = &req_पंचांगpl->cd_ctrl;
	काष्ठा icp_qat_fw_cipher_cd_ctrl_hdr *cipher_cd_ctrl = ptr;
	काष्ठा icp_qat_fw_auth_cd_ctrl_hdr *hash_cd_ctrl = ptr;
	काष्ठा icp_qat_fw_la_auth_req_params *auth_param =
		(काष्ठा icp_qat_fw_la_auth_req_params *)
		((अक्षर *)&req_पंचांगpl->serv_specअगर_rqpars +
		माप(काष्ठा icp_qat_fw_la_cipher_req_params));

	/* CD setup */
	cipher->aes.cipher_config.val = QAT_AES_HW_CONFIG_DEC(alg, mode);
	स_नकल(cipher->aes.key, keys->enckey, keys->enckeylen);
	hash->sha.inner_setup.auth_config.config =
		ICP_QAT_HW_AUTH_CONFIG_BUILD(ICP_QAT_HW_AUTH_MODE1,
					     ctx->qat_hash_alg,
					     digestsize);
	hash->sha.inner_setup.auth_counter.counter =
		cpu_to_be32(crypto_shash_blocksize(ctx->hash_tfm));

	अगर (qat_alg_करो_precomputes(hash, ctx, keys->authkey, keys->authkeylen))
		वापस -EFAULT;

	/* Request setup */
	qat_alg_init_common_hdr(header);
	header->service_cmd_id = ICP_QAT_FW_LA_CMD_HASH_CIPHER;
	ICP_QAT_FW_LA_DIGEST_IN_BUFFER_SET(header->serv_specअगर_flags,
					   ICP_QAT_FW_LA_DIGEST_IN_BUFFER);
	ICP_QAT_FW_LA_RET_AUTH_SET(header->serv_specअगर_flags,
				   ICP_QAT_FW_LA_NO_RET_AUTH_RES);
	ICP_QAT_FW_LA_CMP_AUTH_SET(header->serv_specअगर_flags,
				   ICP_QAT_FW_LA_CMP_AUTH_RES);
	cd_pars->u.s.content_desc_addr = ctx->dec_cd_paddr;
	cd_pars->u.s.content_desc_params_sz = माप(काष्ठा qat_alg_cd) >> 3;

	/* Cipher CD config setup */
	cipher_cd_ctrl->cipher_key_sz = keys->enckeylen >> 3;
	cipher_cd_ctrl->cipher_state_sz = AES_BLOCK_SIZE >> 3;
	cipher_cd_ctrl->cipher_cfg_offset =
		(माप(काष्ठा icp_qat_hw_auth_setup) +
		 roundup(crypto_shash_digestsize(ctx->hash_tfm), 8) * 2) >> 3;
	ICP_QAT_FW_COMN_CURR_ID_SET(cipher_cd_ctrl, ICP_QAT_FW_SLICE_CIPHER);
	ICP_QAT_FW_COMN_NEXT_ID_SET(cipher_cd_ctrl, ICP_QAT_FW_SLICE_DRAM_WR);

	/* Auth CD config setup */
	hash_cd_ctrl->hash_cfg_offset = 0;
	hash_cd_ctrl->hash_flags = ICP_QAT_FW_AUTH_HDR_FLAG_NO_NESTED;
	hash_cd_ctrl->inner_res_sz = digestsize;
	hash_cd_ctrl->final_sz = digestsize;

	चयन (ctx->qat_hash_alg) अणु
	हाल ICP_QAT_HW_AUTH_ALGO_SHA1:
		hash_cd_ctrl->inner_state1_sz =
			round_up(ICP_QAT_HW_SHA1_STATE1_SZ, 8);
		hash_cd_ctrl->inner_state2_sz =
			round_up(ICP_QAT_HW_SHA1_STATE2_SZ, 8);
		अवरोध;
	हाल ICP_QAT_HW_AUTH_ALGO_SHA256:
		hash_cd_ctrl->inner_state1_sz = ICP_QAT_HW_SHA256_STATE1_SZ;
		hash_cd_ctrl->inner_state2_sz = ICP_QAT_HW_SHA256_STATE2_SZ;
		अवरोध;
	हाल ICP_QAT_HW_AUTH_ALGO_SHA512:
		hash_cd_ctrl->inner_state1_sz = ICP_QAT_HW_SHA512_STATE1_SZ;
		hash_cd_ctrl->inner_state2_sz = ICP_QAT_HW_SHA512_STATE2_SZ;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	hash_cd_ctrl->inner_state2_offset = hash_cd_ctrl->hash_cfg_offset +
			((माप(काष्ठा icp_qat_hw_auth_setup) +
			 round_up(hash_cd_ctrl->inner_state1_sz, 8)) >> 3);
	auth_param->auth_res_sz = digestsize;
	ICP_QAT_FW_COMN_CURR_ID_SET(hash_cd_ctrl, ICP_QAT_FW_SLICE_AUTH);
	ICP_QAT_FW_COMN_NEXT_ID_SET(hash_cd_ctrl, ICP_QAT_FW_SLICE_CIPHER);
	वापस 0;
पूर्ण

अटल व्योम qat_alg_skcipher_init_com(काष्ठा qat_alg_skcipher_ctx *ctx,
				      काष्ठा icp_qat_fw_la_bulk_req *req,
				      काष्ठा icp_qat_hw_cipher_algo_blk *cd,
				      स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा icp_qat_fw_comn_req_hdr_cd_pars *cd_pars = &req->cd_pars;
	काष्ठा icp_qat_fw_comn_req_hdr *header = &req->comn_hdr;
	काष्ठा icp_qat_fw_cipher_cd_ctrl_hdr *cd_ctrl = (व्योम *)&req->cd_ctrl;
	bool aes_v2_capable = HW_CAP_AES_V2(ctx->inst->accel_dev);
	पूर्णांक mode = ctx->mode;

	qat_alg_init_common_hdr(header);
	header->service_cmd_id = ICP_QAT_FW_LA_CMD_CIPHER;
	cd_pars->u.s.content_desc_params_sz =
				माप(काष्ठा icp_qat_hw_cipher_algo_blk) >> 3;

	अगर (aes_v2_capable && mode == ICP_QAT_HW_CIPHER_XTS_MODE) अणु
		ICP_QAT_FW_LA_SLICE_TYPE_SET(header->serv_specअगर_flags,
					     ICP_QAT_FW_LA_USE_UCS_SLICE_TYPE);

		/* Store both XTS keys in CD, only the first key is sent
		 * to the HW, the second key is used क्रम tweak calculation
		 */
		स_नकल(cd->ucs_aes.key, key, keylen);
		keylen = keylen / 2;
	पूर्ण अन्यथा अगर (aes_v2_capable && mode == ICP_QAT_HW_CIPHER_CTR_MODE) अणु
		ICP_QAT_FW_LA_SLICE_TYPE_SET(header->serv_specअगर_flags,
					     ICP_QAT_FW_LA_USE_UCS_SLICE_TYPE);
		keylen = round_up(keylen, 16);
		स_नकल(cd->ucs_aes.key, key, keylen);
	पूर्ण अन्यथा अणु
		स_नकल(cd->aes.key, key, keylen);
	पूर्ण

	/* Cipher CD config setup */
	cd_ctrl->cipher_key_sz = keylen >> 3;
	cd_ctrl->cipher_state_sz = AES_BLOCK_SIZE >> 3;
	cd_ctrl->cipher_cfg_offset = 0;
	ICP_QAT_FW_COMN_CURR_ID_SET(cd_ctrl, ICP_QAT_FW_SLICE_CIPHER);
	ICP_QAT_FW_COMN_NEXT_ID_SET(cd_ctrl, ICP_QAT_FW_SLICE_DRAM_WR);
पूर्ण

अटल व्योम qat_alg_skcipher_init_enc(काष्ठा qat_alg_skcipher_ctx *ctx,
				      पूर्णांक alg, स्थिर u8 *key,
				      अचिन्हित पूर्णांक keylen, पूर्णांक mode)
अणु
	काष्ठा icp_qat_hw_cipher_algo_blk *enc_cd = ctx->enc_cd;
	काष्ठा icp_qat_fw_la_bulk_req *req = &ctx->enc_fw_req;
	काष्ठा icp_qat_fw_comn_req_hdr_cd_pars *cd_pars = &req->cd_pars;

	qat_alg_skcipher_init_com(ctx, req, enc_cd, key, keylen);
	cd_pars->u.s.content_desc_addr = ctx->enc_cd_paddr;
	enc_cd->aes.cipher_config.val = QAT_AES_HW_CONFIG_ENC(alg, mode);
पूर्ण

अटल व्योम qat_alg_xts_reverse_key(स्थिर u8 *key_क्रमward, अचिन्हित पूर्णांक keylen,
				    u8 *key_reverse)
अणु
	काष्ठा crypto_aes_ctx aes_expanded;
	पूर्णांक nrounds;
	u8 *key;

	aes_expandkey(&aes_expanded, key_क्रमward, keylen);
	अगर (keylen == AES_KEYSIZE_128) अणु
		nrounds = 10;
		key = (u8 *)aes_expanded.key_enc + (AES_BLOCK_SIZE * nrounds);
		स_नकल(key_reverse, key, AES_BLOCK_SIZE);
	पूर्ण अन्यथा अणु
		/* AES_KEYSIZE_256 */
		nrounds = 14;
		key = (u8 *)aes_expanded.key_enc + (AES_BLOCK_SIZE * nrounds);
		स_नकल(key_reverse, key, AES_BLOCK_SIZE);
		स_नकल(key_reverse + AES_BLOCK_SIZE, key - AES_BLOCK_SIZE,
		       AES_BLOCK_SIZE);
	पूर्ण
पूर्ण

अटल व्योम qat_alg_skcipher_init_dec(काष्ठा qat_alg_skcipher_ctx *ctx,
				      पूर्णांक alg, स्थिर u8 *key,
				      अचिन्हित पूर्णांक keylen, पूर्णांक mode)
अणु
	काष्ठा icp_qat_hw_cipher_algo_blk *dec_cd = ctx->dec_cd;
	काष्ठा icp_qat_fw_la_bulk_req *req = &ctx->dec_fw_req;
	काष्ठा icp_qat_fw_comn_req_hdr_cd_pars *cd_pars = &req->cd_pars;
	bool aes_v2_capable = HW_CAP_AES_V2(ctx->inst->accel_dev);

	qat_alg_skcipher_init_com(ctx, req, dec_cd, key, keylen);
	cd_pars->u.s.content_desc_addr = ctx->dec_cd_paddr;

	अगर (aes_v2_capable && mode == ICP_QAT_HW_CIPHER_XTS_MODE) अणु
		/* Key reversing not supported, set no convert */
		dec_cd->aes.cipher_config.val =
				QAT_AES_HW_CONFIG_DEC_NO_CONV(alg, mode);

		/* In-place key reversal */
		qat_alg_xts_reverse_key(dec_cd->ucs_aes.key, keylen / 2,
					dec_cd->ucs_aes.key);
	पूर्ण अन्यथा अगर (mode != ICP_QAT_HW_CIPHER_CTR_MODE) अणु
		dec_cd->aes.cipher_config.val =
					QAT_AES_HW_CONFIG_DEC(alg, mode);
	पूर्ण अन्यथा अणु
		dec_cd->aes.cipher_config.val =
					QAT_AES_HW_CONFIG_ENC(alg, mode);
	पूर्ण
पूर्ण

अटल पूर्णांक qat_alg_validate_key(पूर्णांक key_len, पूर्णांक *alg, पूर्णांक mode)
अणु
	अगर (mode != ICP_QAT_HW_CIPHER_XTS_MODE) अणु
		चयन (key_len) अणु
		हाल AES_KEYSIZE_128:
			*alg = ICP_QAT_HW_CIPHER_ALGO_AES128;
			अवरोध;
		हाल AES_KEYSIZE_192:
			*alg = ICP_QAT_HW_CIPHER_ALGO_AES192;
			अवरोध;
		हाल AES_KEYSIZE_256:
			*alg = ICP_QAT_HW_CIPHER_ALGO_AES256;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (key_len) अणु
		हाल AES_KEYSIZE_128 << 1:
			*alg = ICP_QAT_HW_CIPHER_ALGO_AES128;
			अवरोध;
		हाल AES_KEYSIZE_256 << 1:
			*alg = ICP_QAT_HW_CIPHER_ALGO_AES256;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qat_alg_aead_init_sessions(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
				      अचिन्हित पूर्णांक keylen,  पूर्णांक mode)
अणु
	काष्ठा crypto_authenc_keys keys;
	पूर्णांक alg;

	अगर (crypto_authenc_extractkeys(&keys, key, keylen))
		जाओ bad_key;

	अगर (qat_alg_validate_key(keys.enckeylen, &alg, mode))
		जाओ bad_key;

	अगर (qat_alg_aead_init_enc_session(tfm, alg, &keys, mode))
		जाओ error;

	अगर (qat_alg_aead_init_dec_session(tfm, alg, &keys, mode))
		जाओ error;

	memzero_explicit(&keys, माप(keys));
	वापस 0;
bad_key:
	memzero_explicit(&keys, माप(keys));
	वापस -EINVAL;
error:
	memzero_explicit(&keys, माप(keys));
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक qat_alg_skcipher_init_sessions(काष्ठा qat_alg_skcipher_ctx *ctx,
					  स्थिर u8 *key,
					  अचिन्हित पूर्णांक keylen,
					  पूर्णांक mode)
अणु
	पूर्णांक alg;

	अगर (qat_alg_validate_key(keylen, &alg, mode))
		वापस -EINVAL;

	qat_alg_skcipher_init_enc(ctx, alg, key, keylen, mode);
	qat_alg_skcipher_init_dec(ctx, alg, key, keylen, mode);
	वापस 0;
पूर्ण

अटल पूर्णांक qat_alg_aead_rekey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा qat_alg_aead_ctx *ctx = crypto_aead_ctx(tfm);

	स_रखो(ctx->enc_cd, 0, माप(*ctx->enc_cd));
	स_रखो(ctx->dec_cd, 0, माप(*ctx->dec_cd));
	स_रखो(&ctx->enc_fw_req, 0, माप(ctx->enc_fw_req));
	स_रखो(&ctx->dec_fw_req, 0, माप(ctx->dec_fw_req));

	वापस qat_alg_aead_init_sessions(tfm, key, keylen,
					  ICP_QAT_HW_CIPHER_CBC_MODE);
पूर्ण

अटल पूर्णांक qat_alg_aead_newkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा qat_alg_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा qat_crypto_instance *inst = शून्य;
	पूर्णांक node = get_current_node();
	काष्ठा device *dev;
	पूर्णांक ret;

	inst = qat_crypto_get_instance_node(node);
	अगर (!inst)
		वापस -EINVAL;
	dev = &GET_DEV(inst->accel_dev);
	ctx->inst = inst;
	ctx->enc_cd = dma_alloc_coherent(dev, माप(*ctx->enc_cd),
					 &ctx->enc_cd_paddr,
					 GFP_ATOMIC);
	अगर (!ctx->enc_cd) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_inst;
	पूर्ण
	ctx->dec_cd = dma_alloc_coherent(dev, माप(*ctx->dec_cd),
					 &ctx->dec_cd_paddr,
					 GFP_ATOMIC);
	अगर (!ctx->dec_cd) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_enc;
	पूर्ण

	ret = qat_alg_aead_init_sessions(tfm, key, keylen,
					 ICP_QAT_HW_CIPHER_CBC_MODE);
	अगर (ret)
		जाओ out_मुक्त_all;

	वापस 0;

out_मुक्त_all:
	स_रखो(ctx->dec_cd, 0, माप(काष्ठा qat_alg_cd));
	dma_मुक्त_coherent(dev, माप(काष्ठा qat_alg_cd),
			  ctx->dec_cd, ctx->dec_cd_paddr);
	ctx->dec_cd = शून्य;
out_मुक्त_enc:
	स_रखो(ctx->enc_cd, 0, माप(काष्ठा qat_alg_cd));
	dma_मुक्त_coherent(dev, माप(काष्ठा qat_alg_cd),
			  ctx->enc_cd, ctx->enc_cd_paddr);
	ctx->enc_cd = शून्य;
out_मुक्त_inst:
	ctx->inst = शून्य;
	qat_crypto_put_instance(inst);
	वापस ret;
पूर्ण

अटल पूर्णांक qat_alg_aead_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा qat_alg_aead_ctx *ctx = crypto_aead_ctx(tfm);

	अगर (ctx->enc_cd)
		वापस qat_alg_aead_rekey(tfm, key, keylen);
	अन्यथा
		वापस qat_alg_aead_newkey(tfm, key, keylen);
पूर्ण

अटल व्योम qat_alg_मुक्त_bufl(काष्ठा qat_crypto_instance *inst,
			      काष्ठा qat_crypto_request *qat_req)
अणु
	काष्ठा device *dev = &GET_DEV(inst->accel_dev);
	काष्ठा qat_alg_buf_list *bl = qat_req->buf.bl;
	काष्ठा qat_alg_buf_list *blout = qat_req->buf.blout;
	dma_addr_t blp = qat_req->buf.blp;
	dma_addr_t blpout = qat_req->buf.bloutp;
	माप_प्रकार sz = qat_req->buf.sz;
	माप_प्रकार sz_out = qat_req->buf.sz_out;
	पूर्णांक i;

	क्रम (i = 0; i < bl->num_bufs; i++)
		dma_unmap_single(dev, bl->bufers[i].addr,
				 bl->bufers[i].len, DMA_BIसूचीECTIONAL);

	dma_unmap_single(dev, blp, sz, DMA_TO_DEVICE);
	kमुक्त(bl);
	अगर (blp != blpout) अणु
		/* If out of place operation dma unmap only data */
		पूर्णांक bufless = blout->num_bufs - blout->num_mapped_bufs;

		क्रम (i = bufless; i < blout->num_bufs; i++) अणु
			dma_unmap_single(dev, blout->bufers[i].addr,
					 blout->bufers[i].len,
					 DMA_BIसूचीECTIONAL);
		पूर्ण
		dma_unmap_single(dev, blpout, sz_out, DMA_TO_DEVICE);
		kमुक्त(blout);
	पूर्ण
पूर्ण

अटल पूर्णांक qat_alg_sgl_to_bufl(काष्ठा qat_crypto_instance *inst,
			       काष्ठा scatterlist *sgl,
			       काष्ठा scatterlist *sglout,
			       काष्ठा qat_crypto_request *qat_req)
अणु
	काष्ठा device *dev = &GET_DEV(inst->accel_dev);
	पूर्णांक i, sg_nctr = 0;
	पूर्णांक n = sg_nents(sgl);
	काष्ठा qat_alg_buf_list *bufl;
	काष्ठा qat_alg_buf_list *buflout = शून्य;
	dma_addr_t blp = DMA_MAPPING_ERROR;
	dma_addr_t bloutp = DMA_MAPPING_ERROR;
	काष्ठा scatterlist *sg;
	माप_प्रकार sz_out, sz = काष्ठा_size(bufl, bufers, n + 1);

	अगर (unlikely(!n))
		वापस -EINVAL;

	bufl = kzalloc_node(sz, GFP_ATOMIC,
			    dev_to_node(&GET_DEV(inst->accel_dev)));
	अगर (unlikely(!bufl))
		वापस -ENOMEM;

	क्रम_each_sg(sgl, sg, n, i)
		bufl->bufers[i].addr = DMA_MAPPING_ERROR;

	क्रम_each_sg(sgl, sg, n, i) अणु
		पूर्णांक y = sg_nctr;

		अगर (!sg->length)
			जारी;

		bufl->bufers[y].addr = dma_map_single(dev, sg_virt(sg),
						      sg->length,
						      DMA_BIसूचीECTIONAL);
		bufl->bufers[y].len = sg->length;
		अगर (unlikely(dma_mapping_error(dev, bufl->bufers[y].addr)))
			जाओ err_in;
		sg_nctr++;
	पूर्ण
	bufl->num_bufs = sg_nctr;
	blp = dma_map_single(dev, bufl, sz, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, blp)))
		जाओ err_in;
	qat_req->buf.bl = bufl;
	qat_req->buf.blp = blp;
	qat_req->buf.sz = sz;
	/* Handle out of place operation */
	अगर (sgl != sglout) अणु
		काष्ठा qat_alg_buf *bufers;

		n = sg_nents(sglout);
		sz_out = काष्ठा_size(buflout, bufers, n + 1);
		sg_nctr = 0;
		buflout = kzalloc_node(sz_out, GFP_ATOMIC,
				       dev_to_node(&GET_DEV(inst->accel_dev)));
		अगर (unlikely(!buflout))
			जाओ err_in;

		bufers = buflout->bufers;
		क्रम_each_sg(sglout, sg, n, i)
			bufers[i].addr = DMA_MAPPING_ERROR;

		क्रम_each_sg(sglout, sg, n, i) अणु
			पूर्णांक y = sg_nctr;

			अगर (!sg->length)
				जारी;

			bufers[y].addr = dma_map_single(dev, sg_virt(sg),
							sg->length,
							DMA_BIसूचीECTIONAL);
			अगर (unlikely(dma_mapping_error(dev, bufers[y].addr)))
				जाओ err_out;
			bufers[y].len = sg->length;
			sg_nctr++;
		पूर्ण
		buflout->num_bufs = sg_nctr;
		buflout->num_mapped_bufs = sg_nctr;
		bloutp = dma_map_single(dev, buflout, sz_out, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(dev, bloutp)))
			जाओ err_out;
		qat_req->buf.blout = buflout;
		qat_req->buf.bloutp = bloutp;
		qat_req->buf.sz_out = sz_out;
	पूर्ण अन्यथा अणु
		/* Otherwise set the src and dst to the same address */
		qat_req->buf.bloutp = qat_req->buf.blp;
		qat_req->buf.sz_out = 0;
	पूर्ण
	वापस 0;

err_out:
	अगर (!dma_mapping_error(dev, bloutp))
		dma_unmap_single(dev, bloutp, sz_out, DMA_TO_DEVICE);

	n = sg_nents(sglout);
	क्रम (i = 0; i < n; i++)
		अगर (!dma_mapping_error(dev, buflout->bufers[i].addr))
			dma_unmap_single(dev, buflout->bufers[i].addr,
					 buflout->bufers[i].len,
					 DMA_BIसूचीECTIONAL);
	kमुक्त(buflout);

err_in:
	अगर (!dma_mapping_error(dev, blp))
		dma_unmap_single(dev, blp, sz, DMA_TO_DEVICE);

	n = sg_nents(sgl);
	क्रम (i = 0; i < n; i++)
		अगर (!dma_mapping_error(dev, bufl->bufers[i].addr))
			dma_unmap_single(dev, bufl->bufers[i].addr,
					 bufl->bufers[i].len,
					 DMA_BIसूचीECTIONAL);

	kमुक्त(bufl);

	dev_err(dev, "Failed to map buf for dma\n");
	वापस -ENOMEM;
पूर्ण

अटल व्योम qat_aead_alg_callback(काष्ठा icp_qat_fw_la_resp *qat_resp,
				  काष्ठा qat_crypto_request *qat_req)
अणु
	काष्ठा qat_alg_aead_ctx *ctx = qat_req->aead_ctx;
	काष्ठा qat_crypto_instance *inst = ctx->inst;
	काष्ठा aead_request *areq = qat_req->aead_req;
	u8 stat_filed = qat_resp->comn_resp.comn_status;
	पूर्णांक res = 0, qat_res = ICP_QAT_FW_COMN_RESP_CRYPTO_STAT_GET(stat_filed);

	qat_alg_मुक्त_bufl(inst, qat_req);
	अगर (unlikely(qat_res != ICP_QAT_FW_COMN_STATUS_FLAG_OK))
		res = -EBADMSG;
	areq->base.complete(&areq->base, res);
पूर्ण

अटल व्योम qat_alg_update_iv_ctr_mode(काष्ठा qat_crypto_request *qat_req)
अणु
	काष्ठा skcipher_request *sreq = qat_req->skcipher_req;
	u64 iv_lo_prev;
	u64 iv_lo;
	u64 iv_hi;

	स_नकल(qat_req->iv, sreq->iv, AES_BLOCK_SIZE);

	iv_lo = be64_to_cpu(qat_req->iv_lo);
	iv_hi = be64_to_cpu(qat_req->iv_hi);

	iv_lo_prev = iv_lo;
	iv_lo += DIV_ROUND_UP(sreq->cryptlen, AES_BLOCK_SIZE);
	अगर (iv_lo < iv_lo_prev)
		iv_hi++;

	qat_req->iv_lo = cpu_to_be64(iv_lo);
	qat_req->iv_hi = cpu_to_be64(iv_hi);
पूर्ण

अटल व्योम qat_alg_update_iv_cbc_mode(काष्ठा qat_crypto_request *qat_req)
अणु
	काष्ठा skcipher_request *sreq = qat_req->skcipher_req;
	पूर्णांक offset = sreq->cryptlen - AES_BLOCK_SIZE;
	काष्ठा scatterlist *sgl;

	अगर (qat_req->encryption)
		sgl = sreq->dst;
	अन्यथा
		sgl = sreq->src;

	scatterwalk_map_and_copy(qat_req->iv, sgl, offset, AES_BLOCK_SIZE, 0);
पूर्ण

अटल व्योम qat_alg_update_iv(काष्ठा qat_crypto_request *qat_req)
अणु
	काष्ठा qat_alg_skcipher_ctx *ctx = qat_req->skcipher_ctx;
	काष्ठा device *dev = &GET_DEV(ctx->inst->accel_dev);

	चयन (ctx->mode) अणु
	हाल ICP_QAT_HW_CIPHER_CTR_MODE:
		qat_alg_update_iv_ctr_mode(qat_req);
		अवरोध;
	हाल ICP_QAT_HW_CIPHER_CBC_MODE:
		qat_alg_update_iv_cbc_mode(qat_req);
		अवरोध;
	हाल ICP_QAT_HW_CIPHER_XTS_MODE:
		अवरोध;
	शेष:
		dev_warn(dev, "Unsupported IV update for cipher mode %d\n",
			 ctx->mode);
	पूर्ण
पूर्ण

अटल व्योम qat_skcipher_alg_callback(काष्ठा icp_qat_fw_la_resp *qat_resp,
				      काष्ठा qat_crypto_request *qat_req)
अणु
	काष्ठा qat_alg_skcipher_ctx *ctx = qat_req->skcipher_ctx;
	काष्ठा qat_crypto_instance *inst = ctx->inst;
	काष्ठा skcipher_request *sreq = qat_req->skcipher_req;
	u8 stat_filed = qat_resp->comn_resp.comn_status;
	पूर्णांक res = 0, qat_res = ICP_QAT_FW_COMN_RESP_CRYPTO_STAT_GET(stat_filed);

	qat_alg_मुक्त_bufl(inst, qat_req);
	अगर (unlikely(qat_res != ICP_QAT_FW_COMN_STATUS_FLAG_OK))
		res = -EINVAL;

	अगर (qat_req->encryption)
		qat_alg_update_iv(qat_req);

	स_नकल(sreq->iv, qat_req->iv, AES_BLOCK_SIZE);

	sreq->base.complete(&sreq->base, res);
पूर्ण

व्योम qat_alg_callback(व्योम *resp)
अणु
	काष्ठा icp_qat_fw_la_resp *qat_resp = resp;
	काष्ठा qat_crypto_request *qat_req =
				(व्योम *)(__क्रमce दीर्घ)qat_resp->opaque_data;

	qat_req->cb(qat_resp, qat_req);
पूर्ण

अटल पूर्णांक qat_alg_aead_dec(काष्ठा aead_request *areq)
अणु
	काष्ठा crypto_aead *aead_tfm = crypto_aead_reqtfm(areq);
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(aead_tfm);
	काष्ठा qat_alg_aead_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा qat_crypto_request *qat_req = aead_request_ctx(areq);
	काष्ठा icp_qat_fw_la_cipher_req_params *cipher_param;
	काष्ठा icp_qat_fw_la_auth_req_params *auth_param;
	काष्ठा icp_qat_fw_la_bulk_req *msg;
	पूर्णांक digst_size = crypto_aead_authsize(aead_tfm);
	पूर्णांक ret, ctr = 0;
	u32 cipher_len;

	cipher_len = areq->cryptlen - digst_size;
	अगर (cipher_len % AES_BLOCK_SIZE != 0)
		वापस -EINVAL;

	ret = qat_alg_sgl_to_bufl(ctx->inst, areq->src, areq->dst, qat_req);
	अगर (unlikely(ret))
		वापस ret;

	msg = &qat_req->req;
	*msg = ctx->dec_fw_req;
	qat_req->aead_ctx = ctx;
	qat_req->aead_req = areq;
	qat_req->cb = qat_aead_alg_callback;
	qat_req->req.comn_mid.opaque_data = (u64)(__क्रमce दीर्घ)qat_req;
	qat_req->req.comn_mid.src_data_addr = qat_req->buf.blp;
	qat_req->req.comn_mid.dest_data_addr = qat_req->buf.bloutp;
	cipher_param = (व्योम *)&qat_req->req.serv_specअगर_rqpars;
	cipher_param->cipher_length = cipher_len;
	cipher_param->cipher_offset = areq->assoclen;
	स_नकल(cipher_param->u.cipher_IV_array, areq->iv, AES_BLOCK_SIZE);
	auth_param = (व्योम *)((u8 *)cipher_param + माप(*cipher_param));
	auth_param->auth_off = 0;
	auth_param->auth_len = areq->assoclen + cipher_param->cipher_length;
	करो अणु
		ret = adf_send_message(ctx->inst->sym_tx, (u32 *)msg);
	पूर्ण जबतक (ret == -EAGAIN && ctr++ < 10);

	अगर (ret == -EAGAIN) अणु
		qat_alg_मुक्त_bufl(ctx->inst, qat_req);
		वापस -EBUSY;
	पूर्ण
	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक qat_alg_aead_enc(काष्ठा aead_request *areq)
अणु
	काष्ठा crypto_aead *aead_tfm = crypto_aead_reqtfm(areq);
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(aead_tfm);
	काष्ठा qat_alg_aead_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा qat_crypto_request *qat_req = aead_request_ctx(areq);
	काष्ठा icp_qat_fw_la_cipher_req_params *cipher_param;
	काष्ठा icp_qat_fw_la_auth_req_params *auth_param;
	काष्ठा icp_qat_fw_la_bulk_req *msg;
	u8 *iv = areq->iv;
	पूर्णांक ret, ctr = 0;

	अगर (areq->cryptlen % AES_BLOCK_SIZE != 0)
		वापस -EINVAL;

	ret = qat_alg_sgl_to_bufl(ctx->inst, areq->src, areq->dst, qat_req);
	अगर (unlikely(ret))
		वापस ret;

	msg = &qat_req->req;
	*msg = ctx->enc_fw_req;
	qat_req->aead_ctx = ctx;
	qat_req->aead_req = areq;
	qat_req->cb = qat_aead_alg_callback;
	qat_req->req.comn_mid.opaque_data = (u64)(__क्रमce दीर्घ)qat_req;
	qat_req->req.comn_mid.src_data_addr = qat_req->buf.blp;
	qat_req->req.comn_mid.dest_data_addr = qat_req->buf.bloutp;
	cipher_param = (व्योम *)&qat_req->req.serv_specअगर_rqpars;
	auth_param = (व्योम *)((u8 *)cipher_param + माप(*cipher_param));

	स_नकल(cipher_param->u.cipher_IV_array, iv, AES_BLOCK_SIZE);
	cipher_param->cipher_length = areq->cryptlen;
	cipher_param->cipher_offset = areq->assoclen;

	auth_param->auth_off = 0;
	auth_param->auth_len = areq->assoclen + areq->cryptlen;

	करो अणु
		ret = adf_send_message(ctx->inst->sym_tx, (u32 *)msg);
	पूर्ण जबतक (ret == -EAGAIN && ctr++ < 10);

	अगर (ret == -EAGAIN) अणु
		qat_alg_मुक्त_bufl(ctx->inst, qat_req);
		वापस -EBUSY;
	पूर्ण
	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक qat_alg_skcipher_rekey(काष्ठा qat_alg_skcipher_ctx *ctx,
				  स्थिर u8 *key, अचिन्हित पूर्णांक keylen,
				  पूर्णांक mode)
अणु
	स_रखो(ctx->enc_cd, 0, माप(*ctx->enc_cd));
	स_रखो(ctx->dec_cd, 0, माप(*ctx->dec_cd));
	स_रखो(&ctx->enc_fw_req, 0, माप(ctx->enc_fw_req));
	स_रखो(&ctx->dec_fw_req, 0, माप(ctx->dec_fw_req));

	वापस qat_alg_skcipher_init_sessions(ctx, key, keylen, mode);
पूर्ण

अटल पूर्णांक qat_alg_skcipher_newkey(काष्ठा qat_alg_skcipher_ctx *ctx,
				   स्थिर u8 *key, अचिन्हित पूर्णांक keylen,
				   पूर्णांक mode)
अणु
	काष्ठा qat_crypto_instance *inst = शून्य;
	काष्ठा device *dev;
	पूर्णांक node = get_current_node();
	पूर्णांक ret;

	inst = qat_crypto_get_instance_node(node);
	अगर (!inst)
		वापस -EINVAL;
	dev = &GET_DEV(inst->accel_dev);
	ctx->inst = inst;
	ctx->enc_cd = dma_alloc_coherent(dev, माप(*ctx->enc_cd),
					 &ctx->enc_cd_paddr,
					 GFP_ATOMIC);
	अगर (!ctx->enc_cd) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_instance;
	पूर्ण
	ctx->dec_cd = dma_alloc_coherent(dev, माप(*ctx->dec_cd),
					 &ctx->dec_cd_paddr,
					 GFP_ATOMIC);
	अगर (!ctx->dec_cd) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_enc;
	पूर्ण

	ret = qat_alg_skcipher_init_sessions(ctx, key, keylen, mode);
	अगर (ret)
		जाओ out_मुक्त_all;

	वापस 0;

out_मुक्त_all:
	स_रखो(ctx->dec_cd, 0, माप(*ctx->dec_cd));
	dma_मुक्त_coherent(dev, माप(*ctx->dec_cd),
			  ctx->dec_cd, ctx->dec_cd_paddr);
	ctx->dec_cd = शून्य;
out_मुक्त_enc:
	स_रखो(ctx->enc_cd, 0, माप(*ctx->enc_cd));
	dma_मुक्त_coherent(dev, माप(*ctx->enc_cd),
			  ctx->enc_cd, ctx->enc_cd_paddr);
	ctx->enc_cd = शून्य;
out_मुक्त_instance:
	ctx->inst = शून्य;
	qat_crypto_put_instance(inst);
	वापस ret;
पूर्ण

अटल पूर्णांक qat_alg_skcipher_setkey(काष्ठा crypto_skcipher *tfm,
				   स्थिर u8 *key, अचिन्हित पूर्णांक keylen,
				   पूर्णांक mode)
अणु
	काष्ठा qat_alg_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);

	ctx->mode = mode;

	अगर (ctx->enc_cd)
		वापस qat_alg_skcipher_rekey(ctx, key, keylen, mode);
	अन्यथा
		वापस qat_alg_skcipher_newkey(ctx, key, keylen, mode);
पूर्ण

अटल पूर्णांक qat_alg_skcipher_cbc_setkey(काष्ठा crypto_skcipher *tfm,
				       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस qat_alg_skcipher_setkey(tfm, key, keylen,
				       ICP_QAT_HW_CIPHER_CBC_MODE);
पूर्ण

अटल पूर्णांक qat_alg_skcipher_ctr_setkey(काष्ठा crypto_skcipher *tfm,
				       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस qat_alg_skcipher_setkey(tfm, key, keylen,
				       ICP_QAT_HW_CIPHER_CTR_MODE);
पूर्ण

अटल पूर्णांक qat_alg_skcipher_xts_setkey(काष्ठा crypto_skcipher *tfm,
				       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा qat_alg_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक ret;

	ret = xts_verअगरy_key(tfm, key, keylen);
	अगर (ret)
		वापस ret;

	अगर (keylen >> 1 == AES_KEYSIZE_192) अणु
		ret = crypto_skcipher_setkey(ctx->ftfm, key, keylen);
		अगर (ret)
			वापस ret;

		ctx->fallback = true;

		वापस 0;
	पूर्ण

	ctx->fallback = false;

	ret = qat_alg_skcipher_setkey(tfm, key, keylen,
				      ICP_QAT_HW_CIPHER_XTS_MODE);
	अगर (ret)
		वापस ret;

	अगर (HW_CAP_AES_V2(ctx->inst->accel_dev))
		ret = crypto_cipher_setkey(ctx->tweak, key + (keylen / 2),
					   keylen / 2);

	वापस ret;
पूर्ण

अटल व्योम qat_alg_set_req_iv(काष्ठा qat_crypto_request *qat_req)
अणु
	काष्ठा icp_qat_fw_la_cipher_req_params *cipher_param;
	काष्ठा qat_alg_skcipher_ctx *ctx = qat_req->skcipher_ctx;
	bool aes_v2_capable = HW_CAP_AES_V2(ctx->inst->accel_dev);
	u8 *iv = qat_req->skcipher_req->iv;

	cipher_param = (व्योम *)&qat_req->req.serv_specअगर_rqpars;

	अगर (aes_v2_capable && ctx->mode == ICP_QAT_HW_CIPHER_XTS_MODE)
		crypto_cipher_encrypt_one(ctx->tweak,
					  (u8 *)cipher_param->u.cipher_IV_array,
					  iv);
	अन्यथा
		स_नकल(cipher_param->u.cipher_IV_array, iv, AES_BLOCK_SIZE);
पूर्ण

अटल पूर्णांक qat_alg_skcipher_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *stfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(stfm);
	काष्ठा qat_alg_skcipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा qat_crypto_request *qat_req = skcipher_request_ctx(req);
	काष्ठा icp_qat_fw_la_cipher_req_params *cipher_param;
	काष्ठा icp_qat_fw_la_bulk_req *msg;
	पूर्णांक ret, ctr = 0;

	अगर (req->cryptlen == 0)
		वापस 0;

	ret = qat_alg_sgl_to_bufl(ctx->inst, req->src, req->dst, qat_req);
	अगर (unlikely(ret))
		वापस ret;

	msg = &qat_req->req;
	*msg = ctx->enc_fw_req;
	qat_req->skcipher_ctx = ctx;
	qat_req->skcipher_req = req;
	qat_req->cb = qat_skcipher_alg_callback;
	qat_req->req.comn_mid.opaque_data = (u64)(__क्रमce दीर्घ)qat_req;
	qat_req->req.comn_mid.src_data_addr = qat_req->buf.blp;
	qat_req->req.comn_mid.dest_data_addr = qat_req->buf.bloutp;
	qat_req->encryption = true;
	cipher_param = (व्योम *)&qat_req->req.serv_specअगर_rqpars;
	cipher_param->cipher_length = req->cryptlen;
	cipher_param->cipher_offset = 0;

	qat_alg_set_req_iv(qat_req);

	करो अणु
		ret = adf_send_message(ctx->inst->sym_tx, (u32 *)msg);
	पूर्ण जबतक (ret == -EAGAIN && ctr++ < 10);

	अगर (ret == -EAGAIN) अणु
		qat_alg_मुक्त_bufl(ctx->inst, qat_req);
		वापस -EBUSY;
	पूर्ण
	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक qat_alg_skcipher_blk_encrypt(काष्ठा skcipher_request *req)
अणु
	अगर (req->cryptlen % AES_BLOCK_SIZE != 0)
		वापस -EINVAL;

	वापस qat_alg_skcipher_encrypt(req);
पूर्ण

अटल पूर्णांक qat_alg_skcipher_xts_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *stfm = crypto_skcipher_reqtfm(req);
	काष्ठा qat_alg_skcipher_ctx *ctx = crypto_skcipher_ctx(stfm);
	काष्ठा skcipher_request *nreq = skcipher_request_ctx(req);

	अगर (req->cryptlen < XTS_BLOCK_SIZE)
		वापस -EINVAL;

	अगर (ctx->fallback) अणु
		स_नकल(nreq, req, माप(*req));
		skcipher_request_set_tfm(nreq, ctx->ftfm);
		वापस crypto_skcipher_encrypt(nreq);
	पूर्ण

	वापस qat_alg_skcipher_encrypt(req);
पूर्ण

अटल पूर्णांक qat_alg_skcipher_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *stfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(stfm);
	काष्ठा qat_alg_skcipher_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा qat_crypto_request *qat_req = skcipher_request_ctx(req);
	काष्ठा icp_qat_fw_la_cipher_req_params *cipher_param;
	काष्ठा icp_qat_fw_la_bulk_req *msg;
	पूर्णांक ret, ctr = 0;

	अगर (req->cryptlen == 0)
		वापस 0;

	ret = qat_alg_sgl_to_bufl(ctx->inst, req->src, req->dst, qat_req);
	अगर (unlikely(ret))
		वापस ret;

	msg = &qat_req->req;
	*msg = ctx->dec_fw_req;
	qat_req->skcipher_ctx = ctx;
	qat_req->skcipher_req = req;
	qat_req->cb = qat_skcipher_alg_callback;
	qat_req->req.comn_mid.opaque_data = (u64)(__क्रमce दीर्घ)qat_req;
	qat_req->req.comn_mid.src_data_addr = qat_req->buf.blp;
	qat_req->req.comn_mid.dest_data_addr = qat_req->buf.bloutp;
	qat_req->encryption = false;
	cipher_param = (व्योम *)&qat_req->req.serv_specअगर_rqpars;
	cipher_param->cipher_length = req->cryptlen;
	cipher_param->cipher_offset = 0;

	qat_alg_set_req_iv(qat_req);
	qat_alg_update_iv(qat_req);

	करो अणु
		ret = adf_send_message(ctx->inst->sym_tx, (u32 *)msg);
	पूर्ण जबतक (ret == -EAGAIN && ctr++ < 10);

	अगर (ret == -EAGAIN) अणु
		qat_alg_मुक्त_bufl(ctx->inst, qat_req);
		वापस -EBUSY;
	पूर्ण
	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक qat_alg_skcipher_blk_decrypt(काष्ठा skcipher_request *req)
अणु
	अगर (req->cryptlen % AES_BLOCK_SIZE != 0)
		वापस -EINVAL;

	वापस qat_alg_skcipher_decrypt(req);
पूर्ण

अटल पूर्णांक qat_alg_skcipher_xts_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *stfm = crypto_skcipher_reqtfm(req);
	काष्ठा qat_alg_skcipher_ctx *ctx = crypto_skcipher_ctx(stfm);
	काष्ठा skcipher_request *nreq = skcipher_request_ctx(req);

	अगर (req->cryptlen < XTS_BLOCK_SIZE)
		वापस -EINVAL;

	अगर (ctx->fallback) अणु
		स_नकल(nreq, req, माप(*req));
		skcipher_request_set_tfm(nreq, ctx->ftfm);
		वापस crypto_skcipher_decrypt(nreq);
	पूर्ण

	वापस qat_alg_skcipher_decrypt(req);
पूर्ण

अटल पूर्णांक qat_alg_aead_init(काष्ठा crypto_aead *tfm,
			     क्रमागत icp_qat_hw_auth_algo hash,
			     स्थिर अक्षर *hash_name)
अणु
	काष्ठा qat_alg_aead_ctx *ctx = crypto_aead_ctx(tfm);

	ctx->hash_tfm = crypto_alloc_shash(hash_name, 0, 0);
	अगर (IS_ERR(ctx->hash_tfm))
		वापस PTR_ERR(ctx->hash_tfm);
	ctx->qat_hash_alg = hash;
	crypto_aead_set_reqsize(tfm, माप(काष्ठा qat_crypto_request));
	वापस 0;
पूर्ण

अटल पूर्णांक qat_alg_aead_sha1_init(काष्ठा crypto_aead *tfm)
अणु
	वापस qat_alg_aead_init(tfm, ICP_QAT_HW_AUTH_ALGO_SHA1, "sha1");
पूर्ण

अटल पूर्णांक qat_alg_aead_sha256_init(काष्ठा crypto_aead *tfm)
अणु
	वापस qat_alg_aead_init(tfm, ICP_QAT_HW_AUTH_ALGO_SHA256, "sha256");
पूर्ण

अटल पूर्णांक qat_alg_aead_sha512_init(काष्ठा crypto_aead *tfm)
अणु
	वापस qat_alg_aead_init(tfm, ICP_QAT_HW_AUTH_ALGO_SHA512, "sha512");
पूर्ण

अटल व्योम qat_alg_aead_निकास(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा qat_alg_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा qat_crypto_instance *inst = ctx->inst;
	काष्ठा device *dev;

	crypto_मुक्त_shash(ctx->hash_tfm);

	अगर (!inst)
		वापस;

	dev = &GET_DEV(inst->accel_dev);
	अगर (ctx->enc_cd) अणु
		स_रखो(ctx->enc_cd, 0, माप(काष्ठा qat_alg_cd));
		dma_मुक्त_coherent(dev, माप(काष्ठा qat_alg_cd),
				  ctx->enc_cd, ctx->enc_cd_paddr);
	पूर्ण
	अगर (ctx->dec_cd) अणु
		स_रखो(ctx->dec_cd, 0, माप(काष्ठा qat_alg_cd));
		dma_मुक्त_coherent(dev, माप(काष्ठा qat_alg_cd),
				  ctx->dec_cd, ctx->dec_cd_paddr);
	पूर्ण
	qat_crypto_put_instance(inst);
पूर्ण

अटल पूर्णांक qat_alg_skcipher_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा qat_crypto_request));
	वापस 0;
पूर्ण

अटल पूर्णांक qat_alg_skcipher_init_xts_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा qat_alg_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक reqsize;

	ctx->ftfm = crypto_alloc_skcipher("xts(aes)", 0,
					  CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(ctx->ftfm))
		वापस PTR_ERR(ctx->ftfm);

	ctx->tweak = crypto_alloc_cipher("aes", 0, 0);
	अगर (IS_ERR(ctx->tweak)) अणु
		crypto_मुक्त_skcipher(ctx->ftfm);
		वापस PTR_ERR(ctx->tweak);
	पूर्ण

	reqsize = max(माप(काष्ठा qat_crypto_request),
		      माप(काष्ठा skcipher_request) +
		      crypto_skcipher_reqsize(ctx->ftfm));
	crypto_skcipher_set_reqsize(tfm, reqsize);

	वापस 0;
पूर्ण

अटल व्योम qat_alg_skcipher_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा qat_alg_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा qat_crypto_instance *inst = ctx->inst;
	काष्ठा device *dev;

	अगर (!inst)
		वापस;

	dev = &GET_DEV(inst->accel_dev);
	अगर (ctx->enc_cd) अणु
		स_रखो(ctx->enc_cd, 0,
		       माप(काष्ठा icp_qat_hw_cipher_algo_blk));
		dma_मुक्त_coherent(dev,
				  माप(काष्ठा icp_qat_hw_cipher_algo_blk),
				  ctx->enc_cd, ctx->enc_cd_paddr);
	पूर्ण
	अगर (ctx->dec_cd) अणु
		स_रखो(ctx->dec_cd, 0,
		       माप(काष्ठा icp_qat_hw_cipher_algo_blk));
		dma_मुक्त_coherent(dev,
				  माप(काष्ठा icp_qat_hw_cipher_algo_blk),
				  ctx->dec_cd, ctx->dec_cd_paddr);
	पूर्ण
	qat_crypto_put_instance(inst);
पूर्ण

अटल व्योम qat_alg_skcipher_निकास_xts_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा qat_alg_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);

	अगर (ctx->ftfm)
		crypto_मुक्त_skcipher(ctx->ftfm);

	अगर (ctx->tweak)
		crypto_मुक्त_cipher(ctx->tweak);

	qat_alg_skcipher_निकास_tfm(tfm);
पूर्ण

अटल काष्ठा aead_alg qat_aeads[] = अणु अणु
	.base = अणु
		.cra_name = "authenc(hmac(sha1),cbc(aes))",
		.cra_driver_name = "qat_aes_cbc_hmac_sha1",
		.cra_priority = 4001,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा qat_alg_aead_ctx),
		.cra_module = THIS_MODULE,
	पूर्ण,
	.init = qat_alg_aead_sha1_init,
	.निकास = qat_alg_aead_निकास,
	.setkey = qat_alg_aead_setkey,
	.decrypt = qat_alg_aead_dec,
	.encrypt = qat_alg_aead_enc,
	.ivsize = AES_BLOCK_SIZE,
	.maxauthsize = SHA1_DIGEST_SIZE,
पूर्ण, अणु
	.base = अणु
		.cra_name = "authenc(hmac(sha256),cbc(aes))",
		.cra_driver_name = "qat_aes_cbc_hmac_sha256",
		.cra_priority = 4001,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा qat_alg_aead_ctx),
		.cra_module = THIS_MODULE,
	पूर्ण,
	.init = qat_alg_aead_sha256_init,
	.निकास = qat_alg_aead_निकास,
	.setkey = qat_alg_aead_setkey,
	.decrypt = qat_alg_aead_dec,
	.encrypt = qat_alg_aead_enc,
	.ivsize = AES_BLOCK_SIZE,
	.maxauthsize = SHA256_DIGEST_SIZE,
पूर्ण, अणु
	.base = अणु
		.cra_name = "authenc(hmac(sha512),cbc(aes))",
		.cra_driver_name = "qat_aes_cbc_hmac_sha512",
		.cra_priority = 4001,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा qat_alg_aead_ctx),
		.cra_module = THIS_MODULE,
	पूर्ण,
	.init = qat_alg_aead_sha512_init,
	.निकास = qat_alg_aead_निकास,
	.setkey = qat_alg_aead_setkey,
	.decrypt = qat_alg_aead_dec,
	.encrypt = qat_alg_aead_enc,
	.ivsize = AES_BLOCK_SIZE,
	.maxauthsize = SHA512_DIGEST_SIZE,
पूर्ण पूर्ण;

अटल काष्ठा skcipher_alg qat_skciphers[] = अणु अणु
	.base.cra_name = "cbc(aes)",
	.base.cra_driver_name = "qat_aes_cbc",
	.base.cra_priority = 4001,
	.base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize = AES_BLOCK_SIZE,
	.base.cra_ctxsize = माप(काष्ठा qat_alg_skcipher_ctx),
	.base.cra_alignmask = 0,
	.base.cra_module = THIS_MODULE,

	.init = qat_alg_skcipher_init_tfm,
	.निकास = qat_alg_skcipher_निकास_tfm,
	.setkey = qat_alg_skcipher_cbc_setkey,
	.decrypt = qat_alg_skcipher_blk_decrypt,
	.encrypt = qat_alg_skcipher_blk_encrypt,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BLOCK_SIZE,
पूर्ण, अणु
	.base.cra_name = "ctr(aes)",
	.base.cra_driver_name = "qat_aes_ctr",
	.base.cra_priority = 4001,
	.base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize = 1,
	.base.cra_ctxsize = माप(काष्ठा qat_alg_skcipher_ctx),
	.base.cra_alignmask = 0,
	.base.cra_module = THIS_MODULE,

	.init = qat_alg_skcipher_init_tfm,
	.निकास = qat_alg_skcipher_निकास_tfm,
	.setkey = qat_alg_skcipher_ctr_setkey,
	.decrypt = qat_alg_skcipher_decrypt,
	.encrypt = qat_alg_skcipher_encrypt,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BLOCK_SIZE,
पूर्ण, अणु
	.base.cra_name = "xts(aes)",
	.base.cra_driver_name = "qat_aes_xts",
	.base.cra_priority = 4001,
	.base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_NEED_FALLBACK |
			  CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize = AES_BLOCK_SIZE,
	.base.cra_ctxsize = माप(काष्ठा qat_alg_skcipher_ctx),
	.base.cra_alignmask = 0,
	.base.cra_module = THIS_MODULE,

	.init = qat_alg_skcipher_init_xts_tfm,
	.निकास = qat_alg_skcipher_निकास_xts_tfm,
	.setkey = qat_alg_skcipher_xts_setkey,
	.decrypt = qat_alg_skcipher_xts_decrypt,
	.encrypt = qat_alg_skcipher_xts_encrypt,
	.min_keysize = 2 * AES_MIN_KEY_SIZE,
	.max_keysize = 2 * AES_MAX_KEY_SIZE,
	.ivsize = AES_BLOCK_SIZE,
पूर्ण पूर्ण;

पूर्णांक qat_algs_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&algs_lock);
	अगर (++active_devs != 1)
		जाओ unlock;

	ret = crypto_रेजिस्टर_skciphers(qat_skciphers,
					ARRAY_SIZE(qat_skciphers));
	अगर (ret)
		जाओ unlock;

	ret = crypto_रेजिस्टर_aeads(qat_aeads, ARRAY_SIZE(qat_aeads));
	अगर (ret)
		जाओ unreg_algs;

unlock:
	mutex_unlock(&algs_lock);
	वापस ret;

unreg_algs:
	crypto_unरेजिस्टर_skciphers(qat_skciphers, ARRAY_SIZE(qat_skciphers));
	जाओ unlock;
पूर्ण

व्योम qat_algs_unरेजिस्टर(व्योम)
अणु
	mutex_lock(&algs_lock);
	अगर (--active_devs != 0)
		जाओ unlock;

	crypto_unरेजिस्टर_aeads(qat_aeads, ARRAY_SIZE(qat_aeads));
	crypto_unरेजिस्टर_skciphers(qat_skciphers, ARRAY_SIZE(qat_skciphers));

unlock:
	mutex_unlock(&algs_lock);
पूर्ण
