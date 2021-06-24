<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Copyright (C) 2016 Cavium, Inc.
 */

#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/xts.h>
#समावेश <linux/crypto.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/scatterlist.h>

#समावेश "cptvf.h"
#समावेश "cptvf_algs.h"

काष्ठा cpt_device_handle अणु
	व्योम *cdev[MAX_DEVICES];
	u32 dev_count;
पूर्ण;

अटल काष्ठा cpt_device_handle dev_handle;

अटल व्योम cvm_callback(u32 status, व्योम *arg)
अणु
	काष्ठा crypto_async_request *req = (काष्ठा crypto_async_request *)arg;

	req->complete(req, !status);
पूर्ण

अटल अंतरभूत व्योम update_input_iv(काष्ठा cpt_request_info *req_info,
				   u8 *iv, u32 enc_iv_len,
				   u32 *argcnt)
अणु
	/* Setting the iv inक्रमmation */
	req_info->in[*argcnt].vptr = (व्योम *)iv;
	req_info->in[*argcnt].size = enc_iv_len;
	req_info->req.dlen += enc_iv_len;

	++(*argcnt);
पूर्ण

अटल अंतरभूत व्योम update_output_iv(काष्ठा cpt_request_info *req_info,
				    u8 *iv, u32 enc_iv_len,
				    u32 *argcnt)
अणु
	/* Setting the iv inक्रमmation */
	req_info->out[*argcnt].vptr = (व्योम *)iv;
	req_info->out[*argcnt].size = enc_iv_len;
	req_info->rlen += enc_iv_len;

	++(*argcnt);
पूर्ण

अटल अंतरभूत व्योम update_input_data(काष्ठा cpt_request_info *req_info,
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
		++inp_sg;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम update_output_data(काष्ठा cpt_request_info *req_info,
				      काष्ठा scatterlist *outp_sg,
				      u32 nbytes, u32 *argcnt)
अणु
	req_info->rlen += nbytes;

	जबतक (nbytes) अणु
		u32 len = min(nbytes, outp_sg->length);
		u8 *ptr = sg_virt(outp_sg);

		req_info->out[*argcnt].vptr = (व्योम *)ptr;
		req_info->out[*argcnt].size = len;
		nbytes -= len;
		++(*argcnt);
		++outp_sg;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 create_ctx_hdr(काष्ठा skcipher_request *req, u32 enc,
				 u32 *argcnt)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा cvm_enc_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा cvm_req_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा fc_context *fctx = &rctx->fctx;
	u32 enc_iv_len = crypto_skcipher_ivsize(tfm);
	काष्ठा cpt_request_info *req_info = &rctx->cpt_req;
	__be64 *ctrl_flags = शून्य;
	__be64 *offset_control;

	req_info->ctrl.s.grp = 0;
	req_info->ctrl.s.dma_mode = DMA_GATHER_SCATTER;
	req_info->ctrl.s.se_req = SE_CORE_REQ;

	req_info->req.opcode.s.major = MAJOR_OP_FC |
					DMA_MODE_FLAG(DMA_GATHER_SCATTER);
	अगर (enc)
		req_info->req.opcode.s.minor = 2;
	अन्यथा
		req_info->req.opcode.s.minor = 3;

	req_info->req.param1 = req->cryptlen; /* Encryption Data length */
	req_info->req.param2 = 0; /*Auth data length */

	fctx->enc.enc_ctrl.e.enc_cipher = ctx->cipher_type;
	fctx->enc.enc_ctrl.e.aes_key = ctx->key_type;
	fctx->enc.enc_ctrl.e.iv_source = FROM_DPTR;

	अगर (ctx->cipher_type == AES_XTS)
		स_नकल(fctx->enc.encr_key, ctx->enc_key, ctx->key_len * 2);
	अन्यथा
		स_नकल(fctx->enc.encr_key, ctx->enc_key, ctx->key_len);
	ctrl_flags = (__be64 *)&fctx->enc.enc_ctrl.flags;
	*ctrl_flags = cpu_to_be64(fctx->enc.enc_ctrl.flags);

	offset_control = (__be64 *)&rctx->control_word;
	*offset_control = cpu_to_be64(((u64)(enc_iv_len) << 16));
	/* Storing  Packet Data Inक्रमmation in offset
	 * Control Word First 8 bytes
	 */
	req_info->in[*argcnt].vptr = (u8 *)offset_control;
	req_info->in[*argcnt].size = CONTROL_WORD_LEN;
	req_info->req.dlen += CONTROL_WORD_LEN;
	++(*argcnt);

	req_info->in[*argcnt].vptr = (u8 *)fctx;
	req_info->in[*argcnt].size = माप(काष्ठा fc_context);
	req_info->req.dlen += माप(काष्ठा fc_context);

	++(*argcnt);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 create_input_list(काष्ठा skcipher_request  *req, u32 enc,
				    u32 enc_iv_len)
अणु
	काष्ठा cvm_req_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा cpt_request_info *req_info = &rctx->cpt_req;
	u32 argcnt =  0;

	create_ctx_hdr(req, enc, &argcnt);
	update_input_iv(req_info, req->iv, enc_iv_len, &argcnt);
	update_input_data(req_info, req->src, req->cryptlen, &argcnt);
	req_info->incnt = argcnt;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम store_cb_info(काष्ठा skcipher_request *req,
				 काष्ठा cpt_request_info *req_info)
अणु
	req_info->callback = (व्योम *)cvm_callback;
	req_info->callback_arg = (व्योम *)&req->base;
पूर्ण

अटल अंतरभूत व्योम create_output_list(काष्ठा skcipher_request *req,
				      u32 enc_iv_len)
अणु
	काष्ठा cvm_req_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा cpt_request_info *req_info = &rctx->cpt_req;
	u32 argcnt = 0;

	/* OUTPUT Buffer Processing
	 * AES encryption/decryption output would be
	 * received in the following क्रमmat
	 *
	 * ------IV--------|------ENCRYPTED/DECRYPTED DATA-----|
	 * [ 16 Bytes/     [   Request Enc/Dec/ DATA Len AES CBC ]
	 */
	/* Reading IV inक्रमmation */
	update_output_iv(req_info, req->iv, enc_iv_len, &argcnt);
	update_output_data(req_info, req->dst, req->cryptlen, &argcnt);
	req_info->outcnt = argcnt;
पूर्ण

अटल अंतरभूत पूर्णांक cvm_enc_dec(काष्ठा skcipher_request *req, u32 enc)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा cvm_req_ctx *rctx = skcipher_request_ctx(req);
	u32 enc_iv_len = crypto_skcipher_ivsize(tfm);
	काष्ठा fc_context *fctx = &rctx->fctx;
	काष्ठा cpt_request_info *req_info = &rctx->cpt_req;
	व्योम *cdev = शून्य;
	पूर्णांक status;

	स_रखो(req_info, 0, माप(काष्ठा cpt_request_info));
	req_info->may_sleep = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) != 0;
	स_रखो(fctx, 0, माप(काष्ठा fc_context));
	create_input_list(req, enc, enc_iv_len);
	create_output_list(req, enc_iv_len);
	store_cb_info(req, req_info);
	cdev = dev_handle.cdev[smp_processor_id()];
	status = cptvf_करो_request(cdev, req_info);
	/* We perक्रमm an asynchronous send and once
	 * the request is completed the driver would
	 * पूर्णांकimate through  रेजिस्टरed call back functions
	 */

	अगर (status)
		वापस status;
	अन्यथा
		वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक cvm_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस cvm_enc_dec(req, true);
पूर्ण

अटल पूर्णांक cvm_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस cvm_enc_dec(req, false);
पूर्ण

अटल पूर्णांक cvm_xts_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
		   u32 keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(cipher);
	काष्ठा cvm_enc_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक err;
	स्थिर u8 *key1 = key;
	स्थिर u8 *key2 = key + (keylen / 2);

	err = xts_check_key(tfm, key, keylen);
	अगर (err)
		वापस err;
	ctx->key_len = keylen;
	स_नकल(ctx->enc_key, key1, keylen / 2);
	स_नकल(ctx->enc_key + KEY2_OFFSET, key2, keylen / 2);
	ctx->cipher_type = AES_XTS;
	चयन (ctx->key_len) अणु
	हाल 32:
		ctx->key_type = AES_128_BIT;
		अवरोध;
	हाल 64:
		ctx->key_type = AES_256_BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cvm_validate_keylen(काष्ठा cvm_enc_ctx *ctx, u32 keylen)
अणु
	अगर ((keylen == 16) || (keylen == 24) || (keylen == 32)) अणु
		ctx->key_len = keylen;
		चयन (ctx->key_len) अणु
		हाल 16:
			ctx->key_type = AES_128_BIT;
			अवरोध;
		हाल 24:
			ctx->key_type = AES_192_BIT;
			अवरोध;
		हाल 32:
			ctx->key_type = AES_256_BIT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (ctx->cipher_type == DES3_CBC)
			ctx->key_type = 0;

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cvm_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
		      u32 keylen, u8 cipher_type)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(cipher);
	काष्ठा cvm_enc_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->cipher_type = cipher_type;
	अगर (!cvm_validate_keylen(ctx, keylen)) अणु
		स_नकल(ctx->enc_key, key, keylen);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक cvm_cbc_aes_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			      u32 keylen)
अणु
	वापस cvm_setkey(cipher, key, keylen, AES_CBC);
पूर्ण

अटल पूर्णांक cvm_ecb_aes_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			      u32 keylen)
अणु
	वापस cvm_setkey(cipher, key, keylen, AES_ECB);
पूर्ण

अटल पूर्णांक cvm_cfb_aes_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			      u32 keylen)
अणु
	वापस cvm_setkey(cipher, key, keylen, AES_CFB);
पूर्ण

अटल पूर्णांक cvm_cbc_des3_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			       u32 keylen)
अणु
	वापस verअगरy_skcipher_des3_key(cipher, key) ?:
	       cvm_setkey(cipher, key, keylen, DES3_CBC);
पूर्ण

अटल पूर्णांक cvm_ecb_des3_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			       u32 keylen)
अणु
	वापस verअगरy_skcipher_des3_key(cipher, key) ?:
	       cvm_setkey(cipher, key, keylen, DES3_ECB);
पूर्ण

अटल पूर्णांक cvm_enc_dec_init(काष्ठा crypto_skcipher *tfm)
अणु
	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा cvm_req_ctx));

	वापस 0;
पूर्ण

अटल काष्ठा skcipher_alg algs[] = अणु अणु
	.base.cra_flags		= CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा cvm_enc_ctx),
	.base.cra_alignmask	= 7,
	.base.cra_priority	= 4001,
	.base.cra_name		= "xts(aes)",
	.base.cra_driver_name	= "cavium-xts-aes",
	.base.cra_module	= THIS_MODULE,

	.ivsize			= AES_BLOCK_SIZE,
	.min_keysize		= 2 * AES_MIN_KEY_SIZE,
	.max_keysize		= 2 * AES_MAX_KEY_SIZE,
	.setkey			= cvm_xts_setkey,
	.encrypt		= cvm_encrypt,
	.decrypt		= cvm_decrypt,
	.init			= cvm_enc_dec_init,
पूर्ण, अणु
	.base.cra_flags		= CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा cvm_enc_ctx),
	.base.cra_alignmask	= 7,
	.base.cra_priority	= 4001,
	.base.cra_name		= "cbc(aes)",
	.base.cra_driver_name	= "cavium-cbc-aes",
	.base.cra_module	= THIS_MODULE,

	.ivsize			= AES_BLOCK_SIZE,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= cvm_cbc_aes_setkey,
	.encrypt		= cvm_encrypt,
	.decrypt		= cvm_decrypt,
	.init			= cvm_enc_dec_init,
पूर्ण, अणु
	.base.cra_flags		= CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा cvm_enc_ctx),
	.base.cra_alignmask	= 7,
	.base.cra_priority	= 4001,
	.base.cra_name		= "ecb(aes)",
	.base.cra_driver_name	= "cavium-ecb-aes",
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= cvm_ecb_aes_setkey,
	.encrypt		= cvm_encrypt,
	.decrypt		= cvm_decrypt,
	.init			= cvm_enc_dec_init,
पूर्ण, अणु
	.base.cra_flags		= CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा cvm_enc_ctx),
	.base.cra_alignmask	= 7,
	.base.cra_priority	= 4001,
	.base.cra_name		= "cfb(aes)",
	.base.cra_driver_name	= "cavium-cfb-aes",
	.base.cra_module	= THIS_MODULE,

	.ivsize			= AES_BLOCK_SIZE,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= cvm_cfb_aes_setkey,
	.encrypt		= cvm_encrypt,
	.decrypt		= cvm_decrypt,
	.init			= cvm_enc_dec_init,
पूर्ण, अणु
	.base.cra_flags		= CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize	= DES3_EDE_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा cvm_des3_ctx),
	.base.cra_alignmask	= 7,
	.base.cra_priority	= 4001,
	.base.cra_name		= "cbc(des3_ede)",
	.base.cra_driver_name	= "cavium-cbc-des3_ede",
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= DES3_EDE_KEY_SIZE,
	.max_keysize		= DES3_EDE_KEY_SIZE,
	.ivsize			= DES_BLOCK_SIZE,
	.setkey			= cvm_cbc_des3_setkey,
	.encrypt		= cvm_encrypt,
	.decrypt		= cvm_decrypt,
	.init			= cvm_enc_dec_init,
पूर्ण, अणु
	.base.cra_flags		= CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_ALLOCATES_MEMORY,
	.base.cra_blocksize	= DES3_EDE_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा cvm_des3_ctx),
	.base.cra_alignmask	= 7,
	.base.cra_priority	= 4001,
	.base.cra_name		= "ecb(des3_ede)",
	.base.cra_driver_name	= "cavium-ecb-des3_ede",
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= DES3_EDE_KEY_SIZE,
	.max_keysize		= DES3_EDE_KEY_SIZE,
	.ivsize			= DES_BLOCK_SIZE,
	.setkey			= cvm_ecb_des3_setkey,
	.encrypt		= cvm_encrypt,
	.decrypt		= cvm_decrypt,
	.init			= cvm_enc_dec_init,
पूर्ण पूर्ण;

अटल अंतरभूत पूर्णांक cav_रेजिस्टर_algs(व्योम)
अणु
	वापस crypto_रेजिस्टर_skciphers(algs, ARRAY_SIZE(algs));
पूर्ण

अटल अंतरभूत व्योम cav_unरेजिस्टर_algs(व्योम)
अणु
	crypto_unरेजिस्टर_skciphers(algs, ARRAY_SIZE(algs));
पूर्ण

पूर्णांक cvm_crypto_init(काष्ठा cpt_vf *cptvf)
अणु
	काष्ठा pci_dev *pdev = cptvf->pdev;
	u32 dev_count;

	dev_count = dev_handle.dev_count;
	dev_handle.cdev[dev_count] = cptvf;
	dev_handle.dev_count++;

	अगर (dev_count == 3) अणु
		अगर (cav_रेजिस्टर_algs()) अणु
			dev_err(&pdev->dev, "Error in registering crypto algorithms\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम cvm_crypto_निकास(व्योम)
अणु
	u32 dev_count;

	dev_count = --dev_handle.dev_count;
	अगर (!dev_count)
		cav_unरेजिस्टर_algs();
पूर्ण
