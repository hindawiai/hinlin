<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTX CPT driver
 *
 * Copyright (C) 2019 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <crypto/aes.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/cryptd.h>
#समावेश <crypto/des.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/xts.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/sort.h>
#समावेश <linux/module.h>
#समावेश "otx_cptvf.h"
#समावेश "otx_cptvf_algs.h"
#समावेश "otx_cptvf_reqmgr.h"

#घोषणा CPT_MAX_VF_NUM	64
/* Size of salt in AES GCM mode */
#घोषणा AES_GCM_SALT_SIZE	4
/* Size of IV in AES GCM mode */
#घोषणा AES_GCM_IV_SIZE		8
/* Size of ICV (Integrity Check Value) in AES GCM mode */
#घोषणा AES_GCM_ICV_SIZE	16
/* Offset of IV in AES GCM mode */
#घोषणा AES_GCM_IV_OFFSET	8
#घोषणा CONTROL_WORD_LEN	8
#घोषणा KEY2_OFFSET		48
#घोषणा DMA_MODE_FLAG(dma_mode) \
	(((dma_mode) == OTX_CPT_DMA_GATHER_SCATTER) ? (1 << 7) : 0)

/* Truncated SHA digest size */
#घोषणा SHA1_TRUNC_DIGEST_SIZE		12
#घोषणा SHA256_TRUNC_DIGEST_SIZE	16
#घोषणा SHA384_TRUNC_DIGEST_SIZE	24
#घोषणा SHA512_TRUNC_DIGEST_SIZE	32

अटल DEFINE_MUTEX(mutex);
अटल पूर्णांक is_crypto_रेजिस्टरed;

काष्ठा cpt_device_desc अणु
	क्रमागत otx_cptpf_type pf_type;
	काष्ठा pci_dev *dev;
	पूर्णांक num_queues;
पूर्ण;

काष्ठा cpt_device_table अणु
	atomic_t count;
	काष्ठा cpt_device_desc desc[CPT_MAX_VF_NUM];
पूर्ण;

अटल काष्ठा cpt_device_table se_devices = अणु
	.count = ATOMIC_INIT(0)
पूर्ण;

अटल काष्ठा cpt_device_table ae_devices = अणु
	.count = ATOMIC_INIT(0)
पूर्ण;

अटल अंतरभूत पूर्णांक get_se_device(काष्ठा pci_dev **pdev, पूर्णांक *cpu_num)
अणु
	पूर्णांक count, ret = 0;

	count = atomic_पढ़ो(&se_devices.count);
	अगर (count < 1)
		वापस -ENODEV;

	*cpu_num = get_cpu();

	अगर (se_devices.desc[0].pf_type == OTX_CPT_SE) अणु
		/*
		 * On OcteonTX platक्रमm there is one CPT inकाष्ठाion queue bound
		 * to each VF. We get maximum perक्रमmance अगर one CPT queue
		 * is available क्रम each cpu otherwise CPT queues need to be
		 * shared between cpus.
		 */
		अगर (*cpu_num >= count)
			*cpu_num %= count;
		*pdev = se_devices.desc[*cpu_num].dev;
	पूर्ण अन्यथा अणु
		pr_err("Unknown PF type %d\n", se_devices.desc[0].pf_type);
		ret = -EINVAL;
	पूर्ण
	put_cpu();

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक validate_hmac_cipher_null(काष्ठा otx_cpt_req_info *cpt_req)
अणु
	काष्ठा otx_cpt_req_ctx *rctx;
	काष्ठा aead_request *req;
	काष्ठा crypto_aead *tfm;

	req = container_of(cpt_req->areq, काष्ठा aead_request, base);
	tfm = crypto_aead_reqtfm(req);
	rctx = aead_request_ctx(req);
	अगर (स_भेद(rctx->fctx.hmac.s.hmac_calc,
		   rctx->fctx.hmac.s.hmac_recv,
		   crypto_aead_authsize(tfm)) != 0)
		वापस -EBADMSG;

	वापस 0;
पूर्ण

अटल व्योम otx_cpt_aead_callback(पूर्णांक status, व्योम *arg1, व्योम *arg2)
अणु
	काष्ठा otx_cpt_info_buffer *cpt_info = arg2;
	काष्ठा crypto_async_request *areq = arg1;
	काष्ठा otx_cpt_req_info *cpt_req;
	काष्ठा pci_dev *pdev;

	अगर (!cpt_info)
		जाओ complete;

	cpt_req = cpt_info->req;
	अगर (!status) अणु
		/*
		 * When selected cipher is शून्य we need to manually
		 * verअगरy whether calculated hmac value matches
		 * received hmac value
		 */
		अगर (cpt_req->req_type == OTX_CPT_AEAD_ENC_DEC_शून्य_REQ &&
		    !cpt_req->is_enc)
			status = validate_hmac_cipher_null(cpt_req);
	पूर्ण
	pdev = cpt_info->pdev;
	करो_request_cleanup(pdev, cpt_info);

complete:
	अगर (areq)
		areq->complete(areq, status);
पूर्ण

अटल व्योम output_iv_copyback(काष्ठा crypto_async_request *areq)
अणु
	काष्ठा otx_cpt_req_info *req_info;
	काष्ठा skcipher_request *sreq;
	काष्ठा crypto_skcipher *stfm;
	काष्ठा otx_cpt_req_ctx *rctx;
	काष्ठा otx_cpt_enc_ctx *ctx;
	u32 start, ivsize;

	sreq = container_of(areq, काष्ठा skcipher_request, base);
	stfm = crypto_skcipher_reqtfm(sreq);
	ctx = crypto_skcipher_ctx(stfm);
	अगर (ctx->cipher_type == OTX_CPT_AES_CBC ||
	    ctx->cipher_type == OTX_CPT_DES3_CBC) अणु
		rctx = skcipher_request_ctx(sreq);
		req_info = &rctx->cpt_req;
		ivsize = crypto_skcipher_ivsize(stfm);
		start = sreq->cryptlen - ivsize;

		अगर (req_info->is_enc) अणु
			scatterwalk_map_and_copy(sreq->iv, sreq->dst, start,
						 ivsize, 0);
		पूर्ण अन्यथा अणु
			अगर (sreq->src != sreq->dst) अणु
				scatterwalk_map_and_copy(sreq->iv, sreq->src,
							 start, ivsize, 0);
			पूर्ण अन्यथा अणु
				स_नकल(sreq->iv, req_info->iv_out, ivsize);
				kमुक्त(req_info->iv_out);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम otx_cpt_skcipher_callback(पूर्णांक status, व्योम *arg1, व्योम *arg2)
अणु
	काष्ठा otx_cpt_info_buffer *cpt_info = arg2;
	काष्ठा crypto_async_request *areq = arg1;
	काष्ठा pci_dev *pdev;

	अगर (areq) अणु
		अगर (!status)
			output_iv_copyback(areq);
		अगर (cpt_info) अणु
			pdev = cpt_info->pdev;
			करो_request_cleanup(pdev, cpt_info);
		पूर्ण
		areq->complete(areq, status);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम update_input_data(काष्ठा otx_cpt_req_info *req_info,
				     काष्ठा scatterlist *inp_sg,
				     u32 nbytes, u32 *argcnt)
अणु
	req_info->req.dlen += nbytes;

	जबतक (nbytes) अणु
		u32 len = min(nbytes, inp_sg->length);
		u8 *ptr = sg_virt(inp_sg);

		req_info->in[*argcnt].vptr = (व्योम *)ptr;
		req_info->in[*argcnt].size = len;
		nbytes -= len;
		++(*argcnt);
		inp_sg = sg_next(inp_sg);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम update_output_data(काष्ठा otx_cpt_req_info *req_info,
				      काष्ठा scatterlist *outp_sg,
				      u32 offset, u32 nbytes, u32 *argcnt)
अणु
	req_info->rlen += nbytes;

	जबतक (nbytes) अणु
		u32 len = min(nbytes, outp_sg->length - offset);
		u8 *ptr = sg_virt(outp_sg);

		req_info->out[*argcnt].vptr = (व्योम *) (ptr + offset);
		req_info->out[*argcnt].size = len;
		nbytes -= len;
		++(*argcnt);
		offset = 0;
		outp_sg = sg_next(outp_sg);
	पूर्ण
पूर्ण

अटल अंतरभूत u32 create_ctx_hdr(काष्ठा skcipher_request *req, u32 enc,
				 u32 *argcnt)
अणु
	काष्ठा crypto_skcipher *stfm = crypto_skcipher_reqtfm(req);
	काष्ठा otx_cpt_req_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा otx_cpt_req_info *req_info = &rctx->cpt_req;
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(stfm);
	काष्ठा otx_cpt_enc_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा otx_cpt_fc_ctx *fctx = &rctx->fctx;
	पूर्णांक ivsize = crypto_skcipher_ivsize(stfm);
	u32 start = req->cryptlen - ivsize;
	gfp_t flags;

	flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
			GFP_KERNEL : GFP_ATOMIC;
	req_info->ctrl.s.dma_mode = OTX_CPT_DMA_GATHER_SCATTER;
	req_info->ctrl.s.se_req = OTX_CPT_SE_CORE_REQ;

	req_info->req.opcode.s.major = OTX_CPT_MAJOR_OP_FC |
				DMA_MODE_FLAG(OTX_CPT_DMA_GATHER_SCATTER);
	अगर (enc) अणु
		req_info->req.opcode.s.minor = 2;
	पूर्ण अन्यथा अणु
		req_info->req.opcode.s.minor = 3;
		अगर ((ctx->cipher_type == OTX_CPT_AES_CBC ||
		    ctx->cipher_type == OTX_CPT_DES3_CBC) &&
		    req->src == req->dst) अणु
			req_info->iv_out = kदो_स्मृति(ivsize, flags);
			अगर (!req_info->iv_out)
				वापस -ENOMEM;

			scatterwalk_map_and_copy(req_info->iv_out, req->src,
						 start, ivsize, 0);
		पूर्ण
	पूर्ण
	/* Encryption data length */
	req_info->req.param1 = req->cryptlen;
	/* Authentication data length */
	req_info->req.param2 = 0;

	fctx->enc.enc_ctrl.e.enc_cipher = ctx->cipher_type;
	fctx->enc.enc_ctrl.e.aes_key = ctx->key_type;
	fctx->enc.enc_ctrl.e.iv_source = OTX_CPT_FROM_CPTR;

	अगर (ctx->cipher_type == OTX_CPT_AES_XTS)
		स_नकल(fctx->enc.encr_key, ctx->enc_key, ctx->key_len * 2);
	अन्यथा
		स_नकल(fctx->enc.encr_key, ctx->enc_key, ctx->key_len);

	स_नकल(fctx->enc.encr_iv, req->iv, crypto_skcipher_ivsize(stfm));

	fctx->enc.enc_ctrl.flags = cpu_to_be64(fctx->enc.enc_ctrl.cflags);

	/*
	 * Storing  Packet Data Inक्रमmation in offset
	 * Control Word First 8 bytes
	 */
	req_info->in[*argcnt].vptr = (u8 *)&rctx->ctrl_word;
	req_info->in[*argcnt].size = CONTROL_WORD_LEN;
	req_info->req.dlen += CONTROL_WORD_LEN;
	++(*argcnt);

	req_info->in[*argcnt].vptr = (u8 *)fctx;
	req_info->in[*argcnt].size = माप(काष्ठा otx_cpt_fc_ctx);
	req_info->req.dlen += माप(काष्ठा otx_cpt_fc_ctx);

	++(*argcnt);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 create_input_list(काष्ठा skcipher_request *req, u32 enc,
				    u32 enc_iv_len)
अणु
	काष्ठा otx_cpt_req_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा otx_cpt_req_info *req_info = &rctx->cpt_req;
	u32 argcnt =  0;
	पूर्णांक ret;

	ret = create_ctx_hdr(req, enc, &argcnt);
	अगर (ret)
		वापस ret;

	update_input_data(req_info, req->src, req->cryptlen, &argcnt);
	req_info->incnt = argcnt;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम create_output_list(काष्ठा skcipher_request *req,
				      u32 enc_iv_len)
अणु
	काष्ठा otx_cpt_req_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा otx_cpt_req_info *req_info = &rctx->cpt_req;
	u32 argcnt = 0;

	/*
	 * OUTPUT Buffer Processing
	 * AES encryption/decryption output would be
	 * received in the following क्रमmat
	 *
	 * ------IV--------|------ENCRYPTED/DECRYPTED DATA-----|
	 * [ 16 Bytes/     [   Request Enc/Dec/ DATA Len AES CBC ]
	 */
	update_output_data(req_info, req->dst, 0, req->cryptlen, &argcnt);
	req_info->outcnt = argcnt;
पूर्ण

अटल अंतरभूत पूर्णांक cpt_enc_dec(काष्ठा skcipher_request *req, u32 enc)
अणु
	काष्ठा crypto_skcipher *stfm = crypto_skcipher_reqtfm(req);
	काष्ठा otx_cpt_req_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा otx_cpt_req_info *req_info = &rctx->cpt_req;
	u32 enc_iv_len = crypto_skcipher_ivsize(stfm);
	काष्ठा pci_dev *pdev;
	पूर्णांक status, cpu_num;

	/* Validate that request करोesn't exceed maximum CPT supported size */
	अगर (req->cryptlen > OTX_CPT_MAX_REQ_SIZE)
		वापस -E2BIG;

	/* Clear control words */
	rctx->ctrl_word.flags = 0;
	rctx->fctx.enc.enc_ctrl.flags = 0;

	status = create_input_list(req, enc, enc_iv_len);
	अगर (status)
		वापस status;
	create_output_list(req, enc_iv_len);

	status = get_se_device(&pdev, &cpu_num);
	अगर (status)
		वापस status;

	req_info->callback = (व्योम *)otx_cpt_skcipher_callback;
	req_info->areq = &req->base;
	req_info->req_type = OTX_CPT_ENC_DEC_REQ;
	req_info->is_enc = enc;
	req_info->is_trunc_hmac = false;
	req_info->ctrl.s.grp = 0;

	/*
	 * We perक्रमm an asynchronous send and once
	 * the request is completed the driver would
	 * पूर्णांकimate through रेजिस्टरed call back functions
	 */
	status = otx_cpt_करो_request(pdev, req_info, cpu_num);

	वापस status;
पूर्ण

अटल पूर्णांक otx_cpt_skcipher_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस cpt_enc_dec(req, true);
पूर्ण

अटल पूर्णांक otx_cpt_skcipher_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस cpt_enc_dec(req, false);
पूर्ण

अटल पूर्णांक otx_cpt_skcipher_xts_setkey(काष्ठा crypto_skcipher *tfm,
				       स्थिर u8 *key, u32 keylen)
अणु
	काष्ठा otx_cpt_enc_ctx *ctx = crypto_skcipher_ctx(tfm);
	स्थिर u8 *key2 = key + (keylen / 2);
	स्थिर u8 *key1 = key;
	पूर्णांक ret;

	ret = xts_check_key(crypto_skcipher_tfm(tfm), key, keylen);
	अगर (ret)
		वापस ret;
	ctx->key_len = keylen;
	स_नकल(ctx->enc_key, key1, keylen / 2);
	स_नकल(ctx->enc_key + KEY2_OFFSET, key2, keylen / 2);
	ctx->cipher_type = OTX_CPT_AES_XTS;
	चयन (ctx->key_len) अणु
	हाल 2 * AES_KEYSIZE_128:
		ctx->key_type = OTX_CPT_AES_128_BIT;
		अवरोध;
	हाल 2 * AES_KEYSIZE_256:
		ctx->key_type = OTX_CPT_AES_256_BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpt_des_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			  u32 keylen, u8 cipher_type)
अणु
	काष्ठा otx_cpt_enc_ctx *ctx = crypto_skcipher_ctx(tfm);

	अगर (keylen != DES3_EDE_KEY_SIZE)
		वापस -EINVAL;

	ctx->key_len = keylen;
	ctx->cipher_type = cipher_type;

	स_नकल(ctx->enc_key, key, keylen);

	वापस 0;
पूर्ण

अटल पूर्णांक cpt_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			  u32 keylen, u8 cipher_type)
अणु
	काष्ठा otx_cpt_enc_ctx *ctx = crypto_skcipher_ctx(tfm);

	चयन (keylen) अणु
	हाल AES_KEYSIZE_128:
		ctx->key_type = OTX_CPT_AES_128_BIT;
		अवरोध;
	हाल AES_KEYSIZE_192:
		ctx->key_type = OTX_CPT_AES_192_BIT;
		अवरोध;
	हाल AES_KEYSIZE_256:
		ctx->key_type = OTX_CPT_AES_256_BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ctx->key_len = keylen;
	ctx->cipher_type = cipher_type;

	स_नकल(ctx->enc_key, key, keylen);

	वापस 0;
पूर्ण

अटल पूर्णांक otx_cpt_skcipher_cbc_aes_setkey(काष्ठा crypto_skcipher *tfm,
					   स्थिर u8 *key, u32 keylen)
अणु
	वापस cpt_aes_setkey(tfm, key, keylen, OTX_CPT_AES_CBC);
पूर्ण

अटल पूर्णांक otx_cpt_skcipher_ecb_aes_setkey(काष्ठा crypto_skcipher *tfm,
					   स्थिर u8 *key, u32 keylen)
अणु
	वापस cpt_aes_setkey(tfm, key, keylen, OTX_CPT_AES_ECB);
पूर्ण

अटल पूर्णांक otx_cpt_skcipher_cfb_aes_setkey(काष्ठा crypto_skcipher *tfm,
					   स्थिर u8 *key, u32 keylen)
अणु
	वापस cpt_aes_setkey(tfm, key, keylen, OTX_CPT_AES_CFB);
पूर्ण

अटल पूर्णांक otx_cpt_skcipher_cbc_des3_setkey(काष्ठा crypto_skcipher *tfm,
					    स्थिर u8 *key, u32 keylen)
अणु
	वापस cpt_des_setkey(tfm, key, keylen, OTX_CPT_DES3_CBC);
पूर्ण

अटल पूर्णांक otx_cpt_skcipher_ecb_des3_setkey(काष्ठा crypto_skcipher *tfm,
					    स्थिर u8 *key, u32 keylen)
अणु
	वापस cpt_des_setkey(tfm, key, keylen, OTX_CPT_DES3_ECB);
पूर्ण

अटल पूर्णांक otx_cpt_enc_dec_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा otx_cpt_enc_ctx *ctx = crypto_skcipher_ctx(tfm);

	स_रखो(ctx, 0, माप(*ctx));
	/*
	 * Additional memory क्रम skcipher_request is
	 * allocated since the cryptd daemon uses
	 * this memory क्रम request_ctx inक्रमmation
	 */
	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा otx_cpt_req_ctx) +
					माप(काष्ठा skcipher_request));

	वापस 0;
पूर्ण

अटल पूर्णांक cpt_aead_init(काष्ठा crypto_aead *tfm, u8 cipher_type, u8 mac_type)
अणु
	काष्ठा otx_cpt_aead_ctx *ctx = crypto_aead_ctx(tfm);

	ctx->cipher_type = cipher_type;
	ctx->mac_type = mac_type;

	/*
	 * When selected cipher is शून्य we use HMAC opcode instead of
	 * FLEXICRYPTO opcode thereक्रमe we करोn't need to use HASH algorithms
	 * क्रम calculating ipad and opad
	 */
	अगर (ctx->cipher_type != OTX_CPT_CIPHER_शून्य) अणु
		चयन (ctx->mac_type) अणु
		हाल OTX_CPT_SHA1:
			ctx->hashalg = crypto_alloc_shash("sha1", 0,
							  CRYPTO_ALG_ASYNC);
			अगर (IS_ERR(ctx->hashalg))
				वापस PTR_ERR(ctx->hashalg);
			अवरोध;

		हाल OTX_CPT_SHA256:
			ctx->hashalg = crypto_alloc_shash("sha256", 0,
							  CRYPTO_ALG_ASYNC);
			अगर (IS_ERR(ctx->hashalg))
				वापस PTR_ERR(ctx->hashalg);
			अवरोध;

		हाल OTX_CPT_SHA384:
			ctx->hashalg = crypto_alloc_shash("sha384", 0,
							  CRYPTO_ALG_ASYNC);
			अगर (IS_ERR(ctx->hashalg))
				वापस PTR_ERR(ctx->hashalg);
			अवरोध;

		हाल OTX_CPT_SHA512:
			ctx->hashalg = crypto_alloc_shash("sha512", 0,
							  CRYPTO_ALG_ASYNC);
			अगर (IS_ERR(ctx->hashalg))
				वापस PTR_ERR(ctx->hashalg);
			अवरोध;
		पूर्ण
	पूर्ण

	crypto_aead_set_reqsize(tfm, माप(काष्ठा otx_cpt_req_ctx));

	वापस 0;
पूर्ण

अटल पूर्णांक otx_cpt_aead_cbc_aes_sha1_init(काष्ठा crypto_aead *tfm)
अणु
	वापस cpt_aead_init(tfm, OTX_CPT_AES_CBC, OTX_CPT_SHA1);
पूर्ण

अटल पूर्णांक otx_cpt_aead_cbc_aes_sha256_init(काष्ठा crypto_aead *tfm)
अणु
	वापस cpt_aead_init(tfm, OTX_CPT_AES_CBC, OTX_CPT_SHA256);
पूर्ण

अटल पूर्णांक otx_cpt_aead_cbc_aes_sha384_init(काष्ठा crypto_aead *tfm)
अणु
	वापस cpt_aead_init(tfm, OTX_CPT_AES_CBC, OTX_CPT_SHA384);
पूर्ण

अटल पूर्णांक otx_cpt_aead_cbc_aes_sha512_init(काष्ठा crypto_aead *tfm)
अणु
	वापस cpt_aead_init(tfm, OTX_CPT_AES_CBC, OTX_CPT_SHA512);
पूर्ण

अटल पूर्णांक otx_cpt_aead_ecb_null_sha1_init(काष्ठा crypto_aead *tfm)
अणु
	वापस cpt_aead_init(tfm, OTX_CPT_CIPHER_शून्य, OTX_CPT_SHA1);
पूर्ण

अटल पूर्णांक otx_cpt_aead_ecb_null_sha256_init(काष्ठा crypto_aead *tfm)
अणु
	वापस cpt_aead_init(tfm, OTX_CPT_CIPHER_शून्य, OTX_CPT_SHA256);
पूर्ण

अटल पूर्णांक otx_cpt_aead_ecb_null_sha384_init(काष्ठा crypto_aead *tfm)
अणु
	वापस cpt_aead_init(tfm, OTX_CPT_CIPHER_शून्य, OTX_CPT_SHA384);
पूर्ण

अटल पूर्णांक otx_cpt_aead_ecb_null_sha512_init(काष्ठा crypto_aead *tfm)
अणु
	वापस cpt_aead_init(tfm, OTX_CPT_CIPHER_शून्य, OTX_CPT_SHA512);
पूर्ण

अटल पूर्णांक otx_cpt_aead_gcm_aes_init(काष्ठा crypto_aead *tfm)
अणु
	वापस cpt_aead_init(tfm, OTX_CPT_AES_GCM, OTX_CPT_MAC_शून्य);
पूर्ण

अटल व्योम otx_cpt_aead_निकास(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा otx_cpt_aead_ctx *ctx = crypto_aead_ctx(tfm);

	kमुक्त(ctx->ipad);
	kमुक्त(ctx->opad);
	अगर (ctx->hashalg)
		crypto_मुक्त_shash(ctx->hashalg);
	kमुक्त(ctx->sdesc);
पूर्ण

/*
 * This is the Integrity Check Value validation (aka the authentication tag
 * length)
 */
अटल पूर्णांक otx_cpt_aead_set_authsize(काष्ठा crypto_aead *tfm,
				     अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा otx_cpt_aead_ctx *ctx = crypto_aead_ctx(tfm);

	चयन (ctx->mac_type) अणु
	हाल OTX_CPT_SHA1:
		अगर (authsize != SHA1_DIGEST_SIZE &&
		    authsize != SHA1_TRUNC_DIGEST_SIZE)
			वापस -EINVAL;

		अगर (authsize == SHA1_TRUNC_DIGEST_SIZE)
			ctx->is_trunc_hmac = true;
		अवरोध;

	हाल OTX_CPT_SHA256:
		अगर (authsize != SHA256_DIGEST_SIZE &&
		    authsize != SHA256_TRUNC_DIGEST_SIZE)
			वापस -EINVAL;

		अगर (authsize == SHA256_TRUNC_DIGEST_SIZE)
			ctx->is_trunc_hmac = true;
		अवरोध;

	हाल OTX_CPT_SHA384:
		अगर (authsize != SHA384_DIGEST_SIZE &&
		    authsize != SHA384_TRUNC_DIGEST_SIZE)
			वापस -EINVAL;

		अगर (authsize == SHA384_TRUNC_DIGEST_SIZE)
			ctx->is_trunc_hmac = true;
		अवरोध;

	हाल OTX_CPT_SHA512:
		अगर (authsize != SHA512_DIGEST_SIZE &&
		    authsize != SHA512_TRUNC_DIGEST_SIZE)
			वापस -EINVAL;

		अगर (authsize == SHA512_TRUNC_DIGEST_SIZE)
			ctx->is_trunc_hmac = true;
		अवरोध;

	हाल OTX_CPT_MAC_शून्य:
		अगर (ctx->cipher_type == OTX_CPT_AES_GCM) अणु
			अगर (authsize != AES_GCM_ICV_SIZE)
				वापस -EINVAL;
		पूर्ण अन्यथा
			वापस -EINVAL;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	tfm->authsize = authsize;
	वापस 0;
पूर्ण

अटल काष्ठा otx_cpt_sdesc *alloc_sdesc(काष्ठा crypto_shash *alg)
अणु
	काष्ठा otx_cpt_sdesc *sdesc;
	पूर्णांक size;

	size = माप(काष्ठा shash_desc) + crypto_shash_descsize(alg);
	sdesc = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!sdesc)
		वापस शून्य;

	sdesc->shash.tfm = alg;

	वापस sdesc;
पूर्ण

अटल अंतरभूत व्योम swap_data32(व्योम *buf, u32 len)
अणु
	cpu_to_be32_array(buf, buf, len / 4);
पूर्ण

अटल अंतरभूत व्योम swap_data64(व्योम *buf, u32 len)
अणु
	__be64 *dst = buf;
	u64 *src = buf;
	पूर्णांक i = 0;

	क्रम (i = 0 ; i < len / 8; i++, src++, dst++)
		*dst = cpu_to_be64p(src);
पूर्ण

अटल पूर्णांक copy_pad(u8 mac_type, u8 *out_pad, u8 *in_pad)
अणु
	काष्ठा sha512_state *sha512;
	काष्ठा sha256_state *sha256;
	काष्ठा sha1_state *sha1;

	चयन (mac_type) अणु
	हाल OTX_CPT_SHA1:
		sha1 = (काष्ठा sha1_state *) in_pad;
		swap_data32(sha1->state, SHA1_DIGEST_SIZE);
		स_नकल(out_pad, &sha1->state, SHA1_DIGEST_SIZE);
		अवरोध;

	हाल OTX_CPT_SHA256:
		sha256 = (काष्ठा sha256_state *) in_pad;
		swap_data32(sha256->state, SHA256_DIGEST_SIZE);
		स_नकल(out_pad, &sha256->state, SHA256_DIGEST_SIZE);
		अवरोध;

	हाल OTX_CPT_SHA384:
	हाल OTX_CPT_SHA512:
		sha512 = (काष्ठा sha512_state *) in_pad;
		swap_data64(sha512->state, SHA512_DIGEST_SIZE);
		स_नकल(out_pad, &sha512->state, SHA512_DIGEST_SIZE);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aead_hmac_init(काष्ठा crypto_aead *cipher)
अणु
	काष्ठा otx_cpt_aead_ctx *ctx = crypto_aead_ctx(cipher);
	पूर्णांक state_size = crypto_shash_statesize(ctx->hashalg);
	पूर्णांक ds = crypto_shash_digestsize(ctx->hashalg);
	पूर्णांक bs = crypto_shash_blocksize(ctx->hashalg);
	पूर्णांक authkeylen = ctx->auth_key_len;
	u8 *ipad = शून्य, *opad = शून्य;
	पूर्णांक ret = 0, icount = 0;

	ctx->sdesc = alloc_sdesc(ctx->hashalg);
	अगर (!ctx->sdesc)
		वापस -ENOMEM;

	ctx->ipad = kzalloc(bs, GFP_KERNEL);
	अगर (!ctx->ipad) अणु
		ret = -ENOMEM;
		जाओ calc_fail;
	पूर्ण

	ctx->opad = kzalloc(bs, GFP_KERNEL);
	अगर (!ctx->opad) अणु
		ret = -ENOMEM;
		जाओ calc_fail;
	पूर्ण

	ipad = kzalloc(state_size, GFP_KERNEL);
	अगर (!ipad) अणु
		ret = -ENOMEM;
		जाओ calc_fail;
	पूर्ण

	opad = kzalloc(state_size, GFP_KERNEL);
	अगर (!opad) अणु
		ret = -ENOMEM;
		जाओ calc_fail;
	पूर्ण

	अगर (authkeylen > bs) अणु
		ret = crypto_shash_digest(&ctx->sdesc->shash, ctx->key,
					  authkeylen, ipad);
		अगर (ret)
			जाओ calc_fail;

		authkeylen = ds;
	पूर्ण अन्यथा अणु
		स_नकल(ipad, ctx->key, authkeylen);
	पूर्ण

	स_रखो(ipad + authkeylen, 0, bs - authkeylen);
	स_नकल(opad, ipad, bs);

	क्रम (icount = 0; icount < bs; icount++) अणु
		ipad[icount] ^= 0x36;
		opad[icount] ^= 0x5c;
	पूर्ण

	/*
	 * Partial Hash calculated from the software
	 * algorithm is retrieved क्रम IPAD & OPAD
	 */

	/* IPAD Calculation */
	crypto_shash_init(&ctx->sdesc->shash);
	crypto_shash_update(&ctx->sdesc->shash, ipad, bs);
	crypto_shash_export(&ctx->sdesc->shash, ipad);
	ret = copy_pad(ctx->mac_type, ctx->ipad, ipad);
	अगर (ret)
		जाओ calc_fail;

	/* OPAD Calculation */
	crypto_shash_init(&ctx->sdesc->shash);
	crypto_shash_update(&ctx->sdesc->shash, opad, bs);
	crypto_shash_export(&ctx->sdesc->shash, opad);
	ret = copy_pad(ctx->mac_type, ctx->opad, opad);
	अगर (ret)
		जाओ calc_fail;

	kमुक्त(ipad);
	kमुक्त(opad);

	वापस 0;

calc_fail:
	kमुक्त(ctx->ipad);
	ctx->ipad = शून्य;
	kमुक्त(ctx->opad);
	ctx->opad = शून्य;
	kमुक्त(ipad);
	kमुक्त(opad);
	kमुक्त(ctx->sdesc);
	ctx->sdesc = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक otx_cpt_aead_cbc_aes_sha_setkey(काष्ठा crypto_aead *cipher,
					   स्थिर अचिन्हित अक्षर *key,
					   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा otx_cpt_aead_ctx *ctx = crypto_aead_ctx(cipher);
	काष्ठा crypto_authenc_key_param *param;
	पूर्णांक enckeylen = 0, authkeylen = 0;
	काष्ठा rtattr *rta = (व्योम *)key;
	पूर्णांक status = -EINVAL;

	अगर (!RTA_OK(rta, keylen))
		जाओ badkey;

	अगर (rta->rta_type != CRYPTO_AUTHENC_KEYA_PARAM)
		जाओ badkey;

	अगर (RTA_PAYLOAD(rta) < माप(*param))
		जाओ badkey;

	param = RTA_DATA(rta);
	enckeylen = be32_to_cpu(param->enckeylen);
	key += RTA_ALIGN(rta->rta_len);
	keylen -= RTA_ALIGN(rta->rta_len);
	अगर (keylen < enckeylen)
		जाओ badkey;

	अगर (keylen > OTX_CPT_MAX_KEY_SIZE)
		जाओ badkey;

	authkeylen = keylen - enckeylen;
	स_नकल(ctx->key, key, keylen);

	चयन (enckeylen) अणु
	हाल AES_KEYSIZE_128:
		ctx->key_type = OTX_CPT_AES_128_BIT;
		अवरोध;
	हाल AES_KEYSIZE_192:
		ctx->key_type = OTX_CPT_AES_192_BIT;
		अवरोध;
	हाल AES_KEYSIZE_256:
		ctx->key_type = OTX_CPT_AES_256_BIT;
		अवरोध;
	शेष:
		/* Invalid key length */
		जाओ badkey;
	पूर्ण

	ctx->enc_key_len = enckeylen;
	ctx->auth_key_len = authkeylen;

	status = aead_hmac_init(cipher);
	अगर (status)
		जाओ badkey;

	वापस 0;
badkey:
	वापस status;
पूर्ण

अटल पूर्णांक otx_cpt_aead_ecb_null_sha_setkey(काष्ठा crypto_aead *cipher,
					    स्थिर अचिन्हित अक्षर *key,
					    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा otx_cpt_aead_ctx *ctx = crypto_aead_ctx(cipher);
	काष्ठा crypto_authenc_key_param *param;
	काष्ठा rtattr *rta = (व्योम *)key;
	पूर्णांक enckeylen = 0;

	अगर (!RTA_OK(rta, keylen))
		जाओ badkey;

	अगर (rta->rta_type != CRYPTO_AUTHENC_KEYA_PARAM)
		जाओ badkey;

	अगर (RTA_PAYLOAD(rta) < माप(*param))
		जाओ badkey;

	param = RTA_DATA(rta);
	enckeylen = be32_to_cpu(param->enckeylen);
	key += RTA_ALIGN(rta->rta_len);
	keylen -= RTA_ALIGN(rta->rta_len);
	अगर (enckeylen != 0)
		जाओ badkey;

	अगर (keylen > OTX_CPT_MAX_KEY_SIZE)
		जाओ badkey;

	स_नकल(ctx->key, key, keylen);
	ctx->enc_key_len = enckeylen;
	ctx->auth_key_len = keylen;
	वापस 0;
badkey:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक otx_cpt_aead_gcm_aes_setkey(काष्ठा crypto_aead *cipher,
				       स्थिर अचिन्हित अक्षर *key,
				       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा otx_cpt_aead_ctx *ctx = crypto_aead_ctx(cipher);

	/*
	 * For aes gcm we expect to get encryption key (16, 24, 32 bytes)
	 * and salt (4 bytes)
	 */
	चयन (keylen) अणु
	हाल AES_KEYSIZE_128 + AES_GCM_SALT_SIZE:
		ctx->key_type = OTX_CPT_AES_128_BIT;
		ctx->enc_key_len = AES_KEYSIZE_128;
		अवरोध;
	हाल AES_KEYSIZE_192 + AES_GCM_SALT_SIZE:
		ctx->key_type = OTX_CPT_AES_192_BIT;
		ctx->enc_key_len = AES_KEYSIZE_192;
		अवरोध;
	हाल AES_KEYSIZE_256 + AES_GCM_SALT_SIZE:
		ctx->key_type = OTX_CPT_AES_256_BIT;
		ctx->enc_key_len = AES_KEYSIZE_256;
		अवरोध;
	शेष:
		/* Invalid key and salt length */
		वापस -EINVAL;
	पूर्ण

	/* Store encryption key and salt */
	स_नकल(ctx->key, key, keylen);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 create_aead_ctx_hdr(काष्ठा aead_request *req, u32 enc,
				      u32 *argcnt)
अणु
	काष्ठा otx_cpt_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा otx_cpt_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा otx_cpt_req_info *req_info = &rctx->cpt_req;
	काष्ठा otx_cpt_fc_ctx *fctx = &rctx->fctx;
	पूर्णांक mac_len = crypto_aead_authsize(tfm);
	पूर्णांक ds;

	rctx->ctrl_word.e.enc_data_offset = req->assoclen;

	चयन (ctx->cipher_type) अणु
	हाल OTX_CPT_AES_CBC:
		fctx->enc.enc_ctrl.e.iv_source = OTX_CPT_FROM_CPTR;
		/* Copy encryption key to context */
		स_नकल(fctx->enc.encr_key, ctx->key + ctx->auth_key_len,
		       ctx->enc_key_len);
		/* Copy IV to context */
		स_नकल(fctx->enc.encr_iv, req->iv, crypto_aead_ivsize(tfm));

		ds = crypto_shash_digestsize(ctx->hashalg);
		अगर (ctx->mac_type == OTX_CPT_SHA384)
			ds = SHA512_DIGEST_SIZE;
		अगर (ctx->ipad)
			स_नकल(fctx->hmac.e.ipad, ctx->ipad, ds);
		अगर (ctx->opad)
			स_नकल(fctx->hmac.e.opad, ctx->opad, ds);
		अवरोध;

	हाल OTX_CPT_AES_GCM:
		fctx->enc.enc_ctrl.e.iv_source = OTX_CPT_FROM_DPTR;
		/* Copy encryption key to context */
		स_नकल(fctx->enc.encr_key, ctx->key, ctx->enc_key_len);
		/* Copy salt to context */
		स_नकल(fctx->enc.encr_iv, ctx->key + ctx->enc_key_len,
		       AES_GCM_SALT_SIZE);

		rctx->ctrl_word.e.iv_offset = req->assoclen - AES_GCM_IV_OFFSET;
		अवरोध;

	शेष:
		/* Unknown cipher type */
		वापस -EINVAL;
	पूर्ण
	rctx->ctrl_word.flags = cpu_to_be64(rctx->ctrl_word.cflags);

	req_info->ctrl.s.dma_mode = OTX_CPT_DMA_GATHER_SCATTER;
	req_info->ctrl.s.se_req = OTX_CPT_SE_CORE_REQ;
	req_info->req.opcode.s.major = OTX_CPT_MAJOR_OP_FC |
				 DMA_MODE_FLAG(OTX_CPT_DMA_GATHER_SCATTER);
	अगर (enc) अणु
		req_info->req.opcode.s.minor = 2;
		req_info->req.param1 = req->cryptlen;
		req_info->req.param2 = req->cryptlen + req->assoclen;
	पूर्ण अन्यथा अणु
		req_info->req.opcode.s.minor = 3;
		req_info->req.param1 = req->cryptlen - mac_len;
		req_info->req.param2 = req->cryptlen + req->assoclen - mac_len;
	पूर्ण

	fctx->enc.enc_ctrl.e.enc_cipher = ctx->cipher_type;
	fctx->enc.enc_ctrl.e.aes_key = ctx->key_type;
	fctx->enc.enc_ctrl.e.mac_type = ctx->mac_type;
	fctx->enc.enc_ctrl.e.mac_len = mac_len;
	fctx->enc.enc_ctrl.flags = cpu_to_be64(fctx->enc.enc_ctrl.cflags);

	/*
	 * Storing Packet Data Inक्रमmation in offset
	 * Control Word First 8 bytes
	 */
	req_info->in[*argcnt].vptr = (u8 *)&rctx->ctrl_word;
	req_info->in[*argcnt].size = CONTROL_WORD_LEN;
	req_info->req.dlen += CONTROL_WORD_LEN;
	++(*argcnt);

	req_info->in[*argcnt].vptr = (u8 *)fctx;
	req_info->in[*argcnt].size = माप(काष्ठा otx_cpt_fc_ctx);
	req_info->req.dlen += माप(काष्ठा otx_cpt_fc_ctx);
	++(*argcnt);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 create_hmac_ctx_hdr(काष्ठा aead_request *req, u32 *argcnt,
				      u32 enc)
अणु
	काष्ठा otx_cpt_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा otx_cpt_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा otx_cpt_req_info *req_info = &rctx->cpt_req;

	req_info->ctrl.s.dma_mode = OTX_CPT_DMA_GATHER_SCATTER;
	req_info->ctrl.s.se_req = OTX_CPT_SE_CORE_REQ;
	req_info->req.opcode.s.major = OTX_CPT_MAJOR_OP_HMAC |
				 DMA_MODE_FLAG(OTX_CPT_DMA_GATHER_SCATTER);
	req_info->is_trunc_hmac = ctx->is_trunc_hmac;

	req_info->req.opcode.s.minor = 0;
	req_info->req.param1 = ctx->auth_key_len;
	req_info->req.param2 = ctx->mac_type << 8;

	/* Add authentication key */
	req_info->in[*argcnt].vptr = ctx->key;
	req_info->in[*argcnt].size = round_up(ctx->auth_key_len, 8);
	req_info->req.dlen += round_up(ctx->auth_key_len, 8);
	++(*argcnt);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 create_aead_input_list(काष्ठा aead_request *req, u32 enc)
अणु
	काष्ठा otx_cpt_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा otx_cpt_req_info *req_info = &rctx->cpt_req;
	u32 inputlen =  req->cryptlen + req->assoclen;
	u32 status, argcnt = 0;

	status = create_aead_ctx_hdr(req, enc, &argcnt);
	अगर (status)
		वापस status;
	update_input_data(req_info, req->src, inputlen, &argcnt);
	req_info->incnt = argcnt;

	वापस 0;
पूर्ण

अटल अंतरभूत u32 create_aead_output_list(काष्ठा aead_request *req, u32 enc,
					  u32 mac_len)
अणु
	काष्ठा otx_cpt_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा otx_cpt_req_info *req_info =  &rctx->cpt_req;
	u32 argcnt = 0, outputlen = 0;

	अगर (enc)
		outputlen = req->cryptlen +  req->assoclen + mac_len;
	अन्यथा
		outputlen = req->cryptlen + req->assoclen - mac_len;

	update_output_data(req_info, req->dst, 0, outputlen, &argcnt);
	req_info->outcnt = argcnt;

	वापस 0;
पूर्ण

अटल अंतरभूत u32 create_aead_null_input_list(काष्ठा aead_request *req,
					      u32 enc, u32 mac_len)
अणु
	काष्ठा otx_cpt_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा otx_cpt_req_info *req_info = &rctx->cpt_req;
	u32 inputlen, argcnt = 0;

	अगर (enc)
		inputlen =  req->cryptlen + req->assoclen;
	अन्यथा
		inputlen =  req->cryptlen + req->assoclen - mac_len;

	create_hmac_ctx_hdr(req, &argcnt, enc);
	update_input_data(req_info, req->src, inputlen, &argcnt);
	req_info->incnt = argcnt;

	वापस 0;
पूर्ण

अटल अंतरभूत u32 create_aead_null_output_list(काष्ठा aead_request *req,
					       u32 enc, u32 mac_len)
अणु
	काष्ठा otx_cpt_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा otx_cpt_req_info *req_info =  &rctx->cpt_req;
	काष्ठा scatterlist *dst;
	u8 *ptr = शून्य;
	पूर्णांक argcnt = 0, status, offset;
	u32 inputlen;

	अगर (enc)
		inputlen =  req->cryptlen + req->assoclen;
	अन्यथा
		inputlen =  req->cryptlen + req->assoclen - mac_len;

	/*
	 * If source and destination are dअगरferent
	 * then copy payload to destination
	 */
	अगर (req->src != req->dst) अणु

		ptr = kदो_स्मृति(inputlen, (req_info->areq->flags &
					 CRYPTO_TFM_REQ_MAY_SLEEP) ?
					 GFP_KERNEL : GFP_ATOMIC);
		अगर (!ptr) अणु
			status = -ENOMEM;
			जाओ error;
		पूर्ण

		status = sg_copy_to_buffer(req->src, sg_nents(req->src), ptr,
					   inputlen);
		अगर (status != inputlen) अणु
			status = -EINVAL;
			जाओ error_मुक्त;
		पूर्ण
		status = sg_copy_from_buffer(req->dst, sg_nents(req->dst), ptr,
					     inputlen);
		अगर (status != inputlen) अणु
			status = -EINVAL;
			जाओ error_मुक्त;
		पूर्ण
		kमुक्त(ptr);
	पूर्ण

	अगर (enc) अणु
		/*
		 * In an encryption scenario hmac needs
		 * to be appended after payload
		 */
		dst = req->dst;
		offset = inputlen;
		जबतक (offset >= dst->length) अणु
			offset -= dst->length;
			dst = sg_next(dst);
			अगर (!dst) अणु
				status = -ENOENT;
				जाओ error;
			पूर्ण
		पूर्ण

		update_output_data(req_info, dst, offset, mac_len, &argcnt);
	पूर्ण अन्यथा अणु
		/*
		 * In a decryption scenario calculated hmac क्रम received
		 * payload needs to be compare with hmac received
		 */
		status = sg_copy_buffer(req->src, sg_nents(req->src),
					rctx->fctx.hmac.s.hmac_recv, mac_len,
					inputlen, true);
		अगर (status != mac_len) अणु
			status = -EINVAL;
			जाओ error;
		पूर्ण

		req_info->out[argcnt].vptr = rctx->fctx.hmac.s.hmac_calc;
		req_info->out[argcnt].size = mac_len;
		argcnt++;
	पूर्ण

	req_info->outcnt = argcnt;
	वापस 0;

error_मुक्त:
	kमुक्त(ptr);
error:
	वापस status;
पूर्ण

अटल u32 cpt_aead_enc_dec(काष्ठा aead_request *req, u8 reg_type, u8 enc)
अणु
	काष्ठा otx_cpt_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा otx_cpt_req_info *req_info = &rctx->cpt_req;
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा pci_dev *pdev;
	u32 status, cpu_num;

	/* Clear control words */
	rctx->ctrl_word.flags = 0;
	rctx->fctx.enc.enc_ctrl.flags = 0;

	req_info->callback = otx_cpt_aead_callback;
	req_info->areq = &req->base;
	req_info->req_type = reg_type;
	req_info->is_enc = enc;
	req_info->is_trunc_hmac = false;

	चयन (reg_type) अणु
	हाल OTX_CPT_AEAD_ENC_DEC_REQ:
		status = create_aead_input_list(req, enc);
		अगर (status)
			वापस status;
		status = create_aead_output_list(req, enc,
						 crypto_aead_authsize(tfm));
		अगर (status)
			वापस status;
		अवरोध;

	हाल OTX_CPT_AEAD_ENC_DEC_शून्य_REQ:
		status = create_aead_null_input_list(req, enc,
						     crypto_aead_authsize(tfm));
		अगर (status)
			वापस status;
		status = create_aead_null_output_list(req, enc,
						crypto_aead_authsize(tfm));
		अगर (status)
			वापस status;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Validate that request करोesn't exceed maximum CPT supported size */
	अगर (req_info->req.param1 > OTX_CPT_MAX_REQ_SIZE ||
	    req_info->req.param2 > OTX_CPT_MAX_REQ_SIZE)
		वापस -E2BIG;

	status = get_se_device(&pdev, &cpu_num);
	अगर (status)
		वापस status;

	req_info->ctrl.s.grp = 0;

	status = otx_cpt_करो_request(pdev, req_info, cpu_num);
	/*
	 * We perक्रमm an asynchronous send and once
	 * the request is completed the driver would
	 * पूर्णांकimate through रेजिस्टरed call back functions
	 */
	वापस status;
पूर्ण

अटल पूर्णांक otx_cpt_aead_encrypt(काष्ठा aead_request *req)
अणु
	वापस cpt_aead_enc_dec(req, OTX_CPT_AEAD_ENC_DEC_REQ, true);
पूर्ण

अटल पूर्णांक otx_cpt_aead_decrypt(काष्ठा aead_request *req)
अणु
	वापस cpt_aead_enc_dec(req, OTX_CPT_AEAD_ENC_DEC_REQ, false);
पूर्ण

अटल पूर्णांक otx_cpt_aead_null_encrypt(काष्ठा aead_request *req)
अणु
	वापस cpt_aead_enc_dec(req, OTX_CPT_AEAD_ENC_DEC_शून्य_REQ, true);
पूर्ण

अटल पूर्णांक otx_cpt_aead_null_decrypt(काष्ठा aead_request *req)
अणु
	वापस cpt_aead_enc_dec(req, OTX_CPT_AEAD_ENC_DEC_शून्य_REQ, false);
पूर्ण

अटल काष्ठा skcipher_alg otx_cpt_skciphers[] = अणु अणु
	.base.cra_name = "xts(aes)",
	.base.cra_driver_name = "cpt_xts_aes",
	.base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize = AES_BLOCK_SIZE,
	.base.cra_ctxsize = माप(काष्ठा otx_cpt_enc_ctx),
	.base.cra_alignmask = 7,
	.base.cra_priority = 4001,
	.base.cra_module = THIS_MODULE,

	.init = otx_cpt_enc_dec_init,
	.ivsize = AES_BLOCK_SIZE,
	.min_keysize = 2 * AES_MIN_KEY_SIZE,
	.max_keysize = 2 * AES_MAX_KEY_SIZE,
	.setkey = otx_cpt_skcipher_xts_setkey,
	.encrypt = otx_cpt_skcipher_encrypt,
	.decrypt = otx_cpt_skcipher_decrypt,
पूर्ण, अणु
	.base.cra_name = "cbc(aes)",
	.base.cra_driver_name = "cpt_cbc_aes",
	.base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize = AES_BLOCK_SIZE,
	.base.cra_ctxsize = माप(काष्ठा otx_cpt_enc_ctx),
	.base.cra_alignmask = 7,
	.base.cra_priority = 4001,
	.base.cra_module = THIS_MODULE,

	.init = otx_cpt_enc_dec_init,
	.ivsize = AES_BLOCK_SIZE,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.setkey = otx_cpt_skcipher_cbc_aes_setkey,
	.encrypt = otx_cpt_skcipher_encrypt,
	.decrypt = otx_cpt_skcipher_decrypt,
पूर्ण, अणु
	.base.cra_name = "ecb(aes)",
	.base.cra_driver_name = "cpt_ecb_aes",
	.base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize = AES_BLOCK_SIZE,
	.base.cra_ctxsize = माप(काष्ठा otx_cpt_enc_ctx),
	.base.cra_alignmask = 7,
	.base.cra_priority = 4001,
	.base.cra_module = THIS_MODULE,

	.init = otx_cpt_enc_dec_init,
	.ivsize = 0,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.setkey = otx_cpt_skcipher_ecb_aes_setkey,
	.encrypt = otx_cpt_skcipher_encrypt,
	.decrypt = otx_cpt_skcipher_decrypt,
पूर्ण, अणु
	.base.cra_name = "cfb(aes)",
	.base.cra_driver_name = "cpt_cfb_aes",
	.base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize = AES_BLOCK_SIZE,
	.base.cra_ctxsize = माप(काष्ठा otx_cpt_enc_ctx),
	.base.cra_alignmask = 7,
	.base.cra_priority = 4001,
	.base.cra_module = THIS_MODULE,

	.init = otx_cpt_enc_dec_init,
	.ivsize = AES_BLOCK_SIZE,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.setkey = otx_cpt_skcipher_cfb_aes_setkey,
	.encrypt = otx_cpt_skcipher_encrypt,
	.decrypt = otx_cpt_skcipher_decrypt,
पूर्ण, अणु
	.base.cra_name = "cbc(des3_ede)",
	.base.cra_driver_name = "cpt_cbc_des3_ede",
	.base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize = DES3_EDE_BLOCK_SIZE,
	.base.cra_ctxsize = माप(काष्ठा otx_cpt_des3_ctx),
	.base.cra_alignmask = 7,
	.base.cra_priority = 4001,
	.base.cra_module = THIS_MODULE,

	.init = otx_cpt_enc_dec_init,
	.min_keysize = DES3_EDE_KEY_SIZE,
	.max_keysize = DES3_EDE_KEY_SIZE,
	.ivsize = DES_BLOCK_SIZE,
	.setkey = otx_cpt_skcipher_cbc_des3_setkey,
	.encrypt = otx_cpt_skcipher_encrypt,
	.decrypt = otx_cpt_skcipher_decrypt,
पूर्ण, अणु
	.base.cra_name = "ecb(des3_ede)",
	.base.cra_driver_name = "cpt_ecb_des3_ede",
	.base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize = DES3_EDE_BLOCK_SIZE,
	.base.cra_ctxsize = माप(काष्ठा otx_cpt_des3_ctx),
	.base.cra_alignmask = 7,
	.base.cra_priority = 4001,
	.base.cra_module = THIS_MODULE,

	.init = otx_cpt_enc_dec_init,
	.min_keysize = DES3_EDE_KEY_SIZE,
	.max_keysize = DES3_EDE_KEY_SIZE,
	.ivsize = 0,
	.setkey = otx_cpt_skcipher_ecb_des3_setkey,
	.encrypt = otx_cpt_skcipher_encrypt,
	.decrypt = otx_cpt_skcipher_decrypt,
पूर्ण पूर्ण;

अटल काष्ठा aead_alg otx_cpt_aeads[] = अणु अणु
	.base = अणु
		.cra_name = "authenc(hmac(sha1),cbc(aes))",
		.cra_driver_name = "cpt_hmac_sha1_cbc_aes",
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_ctxsize = माप(काष्ठा otx_cpt_aead_ctx),
		.cra_priority = 4001,
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.init = otx_cpt_aead_cbc_aes_sha1_init,
	.निकास = otx_cpt_aead_निकास,
	.setkey = otx_cpt_aead_cbc_aes_sha_setkey,
	.setauthsize = otx_cpt_aead_set_authsize,
	.encrypt = otx_cpt_aead_encrypt,
	.decrypt = otx_cpt_aead_decrypt,
	.ivsize = AES_BLOCK_SIZE,
	.maxauthsize = SHA1_DIGEST_SIZE,
पूर्ण, अणु
	.base = अणु
		.cra_name = "authenc(hmac(sha256),cbc(aes))",
		.cra_driver_name = "cpt_hmac_sha256_cbc_aes",
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_ctxsize = माप(काष्ठा otx_cpt_aead_ctx),
		.cra_priority = 4001,
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.init = otx_cpt_aead_cbc_aes_sha256_init,
	.निकास = otx_cpt_aead_निकास,
	.setkey = otx_cpt_aead_cbc_aes_sha_setkey,
	.setauthsize = otx_cpt_aead_set_authsize,
	.encrypt = otx_cpt_aead_encrypt,
	.decrypt = otx_cpt_aead_decrypt,
	.ivsize = AES_BLOCK_SIZE,
	.maxauthsize = SHA256_DIGEST_SIZE,
पूर्ण, अणु
	.base = अणु
		.cra_name = "authenc(hmac(sha384),cbc(aes))",
		.cra_driver_name = "cpt_hmac_sha384_cbc_aes",
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_ctxsize = माप(काष्ठा otx_cpt_aead_ctx),
		.cra_priority = 4001,
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.init = otx_cpt_aead_cbc_aes_sha384_init,
	.निकास = otx_cpt_aead_निकास,
	.setkey = otx_cpt_aead_cbc_aes_sha_setkey,
	.setauthsize = otx_cpt_aead_set_authsize,
	.encrypt = otx_cpt_aead_encrypt,
	.decrypt = otx_cpt_aead_decrypt,
	.ivsize = AES_BLOCK_SIZE,
	.maxauthsize = SHA384_DIGEST_SIZE,
पूर्ण, अणु
	.base = अणु
		.cra_name = "authenc(hmac(sha512),cbc(aes))",
		.cra_driver_name = "cpt_hmac_sha512_cbc_aes",
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_ctxsize = माप(काष्ठा otx_cpt_aead_ctx),
		.cra_priority = 4001,
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.init = otx_cpt_aead_cbc_aes_sha512_init,
	.निकास = otx_cpt_aead_निकास,
	.setkey = otx_cpt_aead_cbc_aes_sha_setkey,
	.setauthsize = otx_cpt_aead_set_authsize,
	.encrypt = otx_cpt_aead_encrypt,
	.decrypt = otx_cpt_aead_decrypt,
	.ivsize = AES_BLOCK_SIZE,
	.maxauthsize = SHA512_DIGEST_SIZE,
पूर्ण, अणु
	.base = अणु
		.cra_name = "authenc(hmac(sha1),ecb(cipher_null))",
		.cra_driver_name = "cpt_hmac_sha1_ecb_null",
		.cra_blocksize = 1,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_ctxsize = माप(काष्ठा otx_cpt_aead_ctx),
		.cra_priority = 4001,
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.init = otx_cpt_aead_ecb_null_sha1_init,
	.निकास = otx_cpt_aead_निकास,
	.setkey = otx_cpt_aead_ecb_null_sha_setkey,
	.setauthsize = otx_cpt_aead_set_authsize,
	.encrypt = otx_cpt_aead_null_encrypt,
	.decrypt = otx_cpt_aead_null_decrypt,
	.ivsize = 0,
	.maxauthsize = SHA1_DIGEST_SIZE,
पूर्ण, अणु
	.base = अणु
		.cra_name = "authenc(hmac(sha256),ecb(cipher_null))",
		.cra_driver_name = "cpt_hmac_sha256_ecb_null",
		.cra_blocksize = 1,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_ctxsize = माप(काष्ठा otx_cpt_aead_ctx),
		.cra_priority = 4001,
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.init = otx_cpt_aead_ecb_null_sha256_init,
	.निकास = otx_cpt_aead_निकास,
	.setkey = otx_cpt_aead_ecb_null_sha_setkey,
	.setauthsize = otx_cpt_aead_set_authsize,
	.encrypt = otx_cpt_aead_null_encrypt,
	.decrypt = otx_cpt_aead_null_decrypt,
	.ivsize = 0,
	.maxauthsize = SHA256_DIGEST_SIZE,
पूर्ण, अणु
	.base = अणु
		.cra_name = "authenc(hmac(sha384),ecb(cipher_null))",
		.cra_driver_name = "cpt_hmac_sha384_ecb_null",
		.cra_blocksize = 1,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_ctxsize = माप(काष्ठा otx_cpt_aead_ctx),
		.cra_priority = 4001,
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.init = otx_cpt_aead_ecb_null_sha384_init,
	.निकास = otx_cpt_aead_निकास,
	.setkey = otx_cpt_aead_ecb_null_sha_setkey,
	.setauthsize = otx_cpt_aead_set_authsize,
	.encrypt = otx_cpt_aead_null_encrypt,
	.decrypt = otx_cpt_aead_null_decrypt,
	.ivsize = 0,
	.maxauthsize = SHA384_DIGEST_SIZE,
पूर्ण, अणु
	.base = अणु
		.cra_name = "authenc(hmac(sha512),ecb(cipher_null))",
		.cra_driver_name = "cpt_hmac_sha512_ecb_null",
		.cra_blocksize = 1,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_ctxsize = माप(काष्ठा otx_cpt_aead_ctx),
		.cra_priority = 4001,
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.init = otx_cpt_aead_ecb_null_sha512_init,
	.निकास = otx_cpt_aead_निकास,
	.setkey = otx_cpt_aead_ecb_null_sha_setkey,
	.setauthsize = otx_cpt_aead_set_authsize,
	.encrypt = otx_cpt_aead_null_encrypt,
	.decrypt = otx_cpt_aead_null_decrypt,
	.ivsize = 0,
	.maxauthsize = SHA512_DIGEST_SIZE,
पूर्ण, अणु
	.base = अणु
		.cra_name = "rfc4106(gcm(aes))",
		.cra_driver_name = "cpt_rfc4106_gcm_aes",
		.cra_blocksize = 1,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_ctxsize = माप(काष्ठा otx_cpt_aead_ctx),
		.cra_priority = 4001,
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.init = otx_cpt_aead_gcm_aes_init,
	.निकास = otx_cpt_aead_निकास,
	.setkey = otx_cpt_aead_gcm_aes_setkey,
	.setauthsize = otx_cpt_aead_set_authsize,
	.encrypt = otx_cpt_aead_encrypt,
	.decrypt = otx_cpt_aead_decrypt,
	.ivsize = AES_GCM_IV_SIZE,
	.maxauthsize = AES_GCM_ICV_SIZE,
पूर्ण पूर्ण;

अटल अंतरभूत पूर्णांक is_any_alg_used(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(otx_cpt_skciphers); i++)
		अगर (refcount_पढ़ो(&otx_cpt_skciphers[i].base.cra_refcnt) != 1)
			वापस true;
	क्रम (i = 0; i < ARRAY_SIZE(otx_cpt_aeads); i++)
		अगर (refcount_पढ़ो(&otx_cpt_aeads[i].base.cra_refcnt) != 1)
			वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक cpt_रेजिस्टर_algs(व्योम)
अणु
	पूर्णांक i, err = 0;

	अगर (!IS_ENABLED(CONFIG_DM_CRYPT)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(otx_cpt_skciphers); i++)
			otx_cpt_skciphers[i].base.cra_flags &= ~CRYPTO_ALG_DEAD;

		err = crypto_रेजिस्टर_skciphers(otx_cpt_skciphers,
						ARRAY_SIZE(otx_cpt_skciphers));
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(otx_cpt_aeads); i++)
		otx_cpt_aeads[i].base.cra_flags &= ~CRYPTO_ALG_DEAD;

	err = crypto_रेजिस्टर_aeads(otx_cpt_aeads, ARRAY_SIZE(otx_cpt_aeads));
	अगर (err) अणु
		crypto_unरेजिस्टर_skciphers(otx_cpt_skciphers,
					    ARRAY_SIZE(otx_cpt_skciphers));
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cpt_unरेजिस्टर_algs(व्योम)
अणु
	crypto_unरेजिस्टर_skciphers(otx_cpt_skciphers,
				    ARRAY_SIZE(otx_cpt_skciphers));
	crypto_unरेजिस्टर_aeads(otx_cpt_aeads, ARRAY_SIZE(otx_cpt_aeads));
पूर्ण

अटल पूर्णांक compare_func(स्थिर व्योम *lptr, स्थिर व्योम *rptr)
अणु
	काष्ठा cpt_device_desc *ldesc = (काष्ठा cpt_device_desc *) lptr;
	काष्ठा cpt_device_desc *rdesc = (काष्ठा cpt_device_desc *) rptr;

	अगर (ldesc->dev->devfn < rdesc->dev->devfn)
		वापस -1;
	अगर (ldesc->dev->devfn > rdesc->dev->devfn)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम swap_func(व्योम *lptr, व्योम *rptr, पूर्णांक size)
अणु
	काष्ठा cpt_device_desc *ldesc = (काष्ठा cpt_device_desc *) lptr;
	काष्ठा cpt_device_desc *rdesc = (काष्ठा cpt_device_desc *) rptr;
	काष्ठा cpt_device_desc desc;

	desc = *ldesc;
	*ldesc = *rdesc;
	*rdesc = desc;
पूर्ण

पूर्णांक otx_cpt_crypto_init(काष्ठा pci_dev *pdev, काष्ठा module *mod,
			क्रमागत otx_cptpf_type pf_type,
			क्रमागत otx_cptvf_type engine_type,
			पूर्णांक num_queues, पूर्णांक num_devices)
अणु
	पूर्णांक ret = 0;
	पूर्णांक count;

	mutex_lock(&mutex);
	चयन (engine_type) अणु
	हाल OTX_CPT_SE_TYPES:
		count = atomic_पढ़ो(&se_devices.count);
		अगर (count >= CPT_MAX_VF_NUM) अणु
			dev_err(&pdev->dev, "No space to add a new device\n");
			ret = -ENOSPC;
			जाओ err;
		पूर्ण
		se_devices.desc[count].pf_type = pf_type;
		se_devices.desc[count].num_queues = num_queues;
		se_devices.desc[count++].dev = pdev;
		atomic_inc(&se_devices.count);

		अगर (atomic_पढ़ो(&se_devices.count) == num_devices &&
		    is_crypto_रेजिस्टरed == false) अणु
			अगर (cpt_रेजिस्टर_algs()) अणु
				dev_err(&pdev->dev,
				   "Error in registering crypto algorithms\n");
				ret =  -EINVAL;
				जाओ err;
			पूर्ण
			try_module_get(mod);
			is_crypto_रेजिस्टरed = true;
		पूर्ण
		sort(se_devices.desc, count, माप(काष्ठा cpt_device_desc),
		     compare_func, swap_func);
		अवरोध;

	हाल OTX_CPT_AE_TYPES:
		count = atomic_पढ़ो(&ae_devices.count);
		अगर (count >= CPT_MAX_VF_NUM) अणु
			dev_err(&pdev->dev, "No space to a add new device\n");
			ret = -ENOSPC;
			जाओ err;
		पूर्ण
		ae_devices.desc[count].pf_type = pf_type;
		ae_devices.desc[count].num_queues = num_queues;
		ae_devices.desc[count++].dev = pdev;
		atomic_inc(&ae_devices.count);
		sort(ae_devices.desc, count, माप(काष्ठा cpt_device_desc),
		     compare_func, swap_func);
		अवरोध;

	शेष:
		dev_err(&pdev->dev, "Unknown VF type %d\n", engine_type);
		ret = BAD_OTX_CPTVF_TYPE;
	पूर्ण
err:
	mutex_unlock(&mutex);
	वापस ret;
पूर्ण

व्योम otx_cpt_crypto_निकास(काष्ठा pci_dev *pdev, काष्ठा module *mod,
			 क्रमागत otx_cptvf_type engine_type)
अणु
	काष्ठा cpt_device_table *dev_tbl;
	bool dev_found = false;
	पूर्णांक i, j, count;

	mutex_lock(&mutex);

	dev_tbl = (engine_type == OTX_CPT_AE_TYPES) ? &ae_devices : &se_devices;
	count = atomic_पढ़ो(&dev_tbl->count);
	क्रम (i = 0; i < count; i++)
		अगर (pdev == dev_tbl->desc[i].dev) अणु
			क्रम (j = i; j < count-1; j++)
				dev_tbl->desc[j] = dev_tbl->desc[j+1];
			dev_found = true;
			अवरोध;
		पूर्ण

	अगर (!dev_found) अणु
		dev_err(&pdev->dev, "%s device not found\n", __func__);
		जाओ निकास;
	पूर्ण

	अगर (engine_type != OTX_CPT_AE_TYPES) अणु
		अगर (atomic_dec_and_test(&se_devices.count) &&
		    !is_any_alg_used()) अणु
			cpt_unरेजिस्टर_algs();
			module_put(mod);
			is_crypto_रेजिस्टरed = false;
		पूर्ण
	पूर्ण अन्यथा
		atomic_dec(&ae_devices.count);
निकास:
	mutex_unlock(&mutex);
पूर्ण
