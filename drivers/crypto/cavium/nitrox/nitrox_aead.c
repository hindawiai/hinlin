<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/crypto.h>
#समावेश <linux/rtnetlink.h>

#समावेश <crypto/aead.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/des.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/gcm.h>

#समावेश "nitrox_dev.h"
#समावेश "nitrox_common.h"
#समावेश "nitrox_req.h"

#घोषणा GCM_AES_SALT_SIZE	4

जोड़ gph_p3 अणु
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		u16 iv_offset : 8;
		u16 auth_offset	: 8;
#अन्यथा
		u16 auth_offset	: 8;
		u16 iv_offset : 8;
#पूर्ण_अगर
	पूर्ण;
	u16 param;
पूर्ण;

अटल पूर्णांक nitrox_aes_gcm_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	पूर्णांक aes_keylen;
	काष्ठा nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);
	काष्ठा flexi_crypto_context *fctx;
	जोड़ fc_ctx_flags flags;

	aes_keylen = flexi_aes_keylen(keylen);
	अगर (aes_keylen < 0)
		वापस -EINVAL;

	/* fill crypto context */
	fctx = nctx->u.fctx;
	flags.fu = be64_to_cpu(fctx->flags.f);
	flags.w0.aes_keylen = aes_keylen;
	fctx->flags.f = cpu_to_be64(flags.fu);

	/* copy enc key to context */
	स_रखो(&fctx->crypto, 0, माप(fctx->crypto));
	स_नकल(fctx->crypto.u.key, key, keylen);

	वापस 0;
पूर्ण

अटल पूर्णांक nitrox_aead_setauthsize(काष्ठा crypto_aead *aead,
				   अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);
	काष्ठा flexi_crypto_context *fctx = nctx->u.fctx;
	जोड़ fc_ctx_flags flags;

	flags.fu = be64_to_cpu(fctx->flags.f);
	flags.w0.mac_len = authsize;
	fctx->flags.f = cpu_to_be64(flags.fu);

	aead->authsize = authsize;

	वापस 0;
पूर्ण

अटल पूर्णांक nitrox_aes_gcm_setauthsize(काष्ठा crypto_aead *aead,
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

	वापस nitrox_aead_setauthsize(aead, authsize);
पूर्ण

अटल पूर्णांक alloc_src_sglist(काष्ठा nitrox_kcrypt_request *nkreq,
			    काष्ठा scatterlist *src, अक्षर *iv, पूर्णांक ivsize,
			    पूर्णांक buflen)
अणु
	पूर्णांक nents = sg_nents_क्रम_len(src, buflen);
	पूर्णांक ret;

	अगर (nents < 0)
		वापस nents;

	/* IV entry */
	nents += 1;
	/* Allocate buffer to hold IV and input scatterlist array */
	ret = alloc_src_req_buf(nkreq, nents, ivsize);
	अगर (ret)
		वापस ret;

	nitrox_creq_copy_iv(nkreq->src, iv, ivsize);
	nitrox_creq_set_src_sg(nkreq, nents, ivsize, src, buflen);

	वापस 0;
पूर्ण

अटल पूर्णांक alloc_dst_sglist(काष्ठा nitrox_kcrypt_request *nkreq,
			    काष्ठा scatterlist *dst, पूर्णांक ivsize, पूर्णांक buflen)
अणु
	पूर्णांक nents = sg_nents_क्रम_len(dst, buflen);
	पूर्णांक ret;

	अगर (nents < 0)
		वापस nents;

	/* IV, ORH, COMPLETION entries */
	nents += 3;
	/* Allocate buffer to hold ORH, COMPLETION and output scatterlist
	 * array
	 */
	ret = alloc_dst_req_buf(nkreq, nents);
	अगर (ret)
		वापस ret;

	nitrox_creq_set_orh(nkreq);
	nitrox_creq_set_comp(nkreq);
	nitrox_creq_set_dst_sg(nkreq, nents, ivsize, dst, buflen);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_src_sglist(काष्ठा nitrox_kcrypt_request *nkreq)
अणु
	kमुक्त(nkreq->src);
पूर्ण

अटल व्योम मुक्त_dst_sglist(काष्ठा nitrox_kcrypt_request *nkreq)
अणु
	kमुक्त(nkreq->dst);
पूर्ण

अटल पूर्णांक nitrox_set_creq(काष्ठा nitrox_aead_rctx *rctx)
अणु
	काष्ठा se_crypto_request *creq = &rctx->nkreq.creq;
	जोड़ gph_p3 param3;
	पूर्णांक ret;

	creq->flags = rctx->flags;
	creq->gfp = (rctx->flags & CRYPTO_TFM_REQ_MAY_SLEEP) ? GFP_KERNEL :
							       GFP_ATOMIC;

	creq->ctrl.value = 0;
	creq->opcode = FLEXI_CRYPTO_ENCRYPT_HMAC;
	creq->ctrl.s.arg = rctx->ctrl_arg;

	creq->gph.param0 = cpu_to_be16(rctx->cryptlen);
	creq->gph.param1 = cpu_to_be16(rctx->cryptlen + rctx->assoclen);
	creq->gph.param2 = cpu_to_be16(rctx->ivsize + rctx->assoclen);
	param3.iv_offset = 0;
	param3.auth_offset = rctx->ivsize;
	creq->gph.param3 = cpu_to_be16(param3.param);

	creq->ctx_handle = rctx->ctx_handle;
	creq->ctrl.s.ctxl = माप(काष्ठा flexi_crypto_context);

	ret = alloc_src_sglist(&rctx->nkreq, rctx->src, rctx->iv, rctx->ivsize,
			       rctx->srclen);
	अगर (ret)
		वापस ret;

	ret = alloc_dst_sglist(&rctx->nkreq, rctx->dst, rctx->ivsize,
			       rctx->dstlen);
	अगर (ret) अणु
		मुक्त_src_sglist(&rctx->nkreq);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nitrox_aead_callback(व्योम *arg, पूर्णांक err)
अणु
	काष्ठा aead_request *areq = arg;
	काष्ठा nitrox_aead_rctx *rctx = aead_request_ctx(areq);

	मुक्त_src_sglist(&rctx->nkreq);
	मुक्त_dst_sglist(&rctx->nkreq);
	अगर (err) अणु
		pr_err_ratelimited("request failed status 0x%0x\n", err);
		err = -EINVAL;
	पूर्ण

	areq->base.complete(&areq->base, err);
पूर्ण

अटल अंतरभूत bool nitrox_aes_gcm_assoclen_supported(अचिन्हित पूर्णांक assoclen)
अणु
	अगर (assoclen <= 512)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक nitrox_aes_gcm_enc(काष्ठा aead_request *areq)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(areq);
	काष्ठा nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);
	काष्ठा nitrox_aead_rctx *rctx = aead_request_ctx(areq);
	काष्ठा se_crypto_request *creq = &rctx->nkreq.creq;
	काष्ठा flexi_crypto_context *fctx = nctx->u.fctx;
	पूर्णांक ret;

	अगर (!nitrox_aes_gcm_assoclen_supported(areq->assoclen))
		वापस -EINVAL;

	स_नकल(fctx->crypto.iv, areq->iv, GCM_AES_SALT_SIZE);

	rctx->cryptlen = areq->cryptlen;
	rctx->assoclen = areq->assoclen;
	rctx->srclen = areq->assoclen + areq->cryptlen;
	rctx->dstlen = rctx->srclen + aead->authsize;
	rctx->iv = &areq->iv[GCM_AES_SALT_SIZE];
	rctx->ivsize = GCM_AES_IV_SIZE - GCM_AES_SALT_SIZE;
	rctx->flags = areq->base.flags;
	rctx->ctx_handle = nctx->u.ctx_handle;
	rctx->src = areq->src;
	rctx->dst = areq->dst;
	rctx->ctrl_arg = ENCRYPT;
	ret = nitrox_set_creq(rctx);
	अगर (ret)
		वापस ret;

	/* send the crypto request */
	वापस nitrox_process_se_request(nctx->ndev, creq, nitrox_aead_callback,
					 areq);
पूर्ण

अटल पूर्णांक nitrox_aes_gcm_dec(काष्ठा aead_request *areq)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(areq);
	काष्ठा nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);
	काष्ठा nitrox_aead_rctx *rctx = aead_request_ctx(areq);
	काष्ठा se_crypto_request *creq = &rctx->nkreq.creq;
	काष्ठा flexi_crypto_context *fctx = nctx->u.fctx;
	पूर्णांक ret;

	अगर (!nitrox_aes_gcm_assoclen_supported(areq->assoclen))
		वापस -EINVAL;

	स_नकल(fctx->crypto.iv, areq->iv, GCM_AES_SALT_SIZE);

	rctx->cryptlen = areq->cryptlen - aead->authsize;
	rctx->assoclen = areq->assoclen;
	rctx->srclen = areq->cryptlen + areq->assoclen;
	rctx->dstlen = rctx->srclen - aead->authsize;
	rctx->iv = &areq->iv[GCM_AES_SALT_SIZE];
	rctx->ivsize = GCM_AES_IV_SIZE - GCM_AES_SALT_SIZE;
	rctx->flags = areq->base.flags;
	rctx->ctx_handle = nctx->u.ctx_handle;
	rctx->src = areq->src;
	rctx->dst = areq->dst;
	rctx->ctrl_arg = DECRYPT;
	ret = nitrox_set_creq(rctx);
	अगर (ret)
		वापस ret;

	/* send the crypto request */
	वापस nitrox_process_se_request(nctx->ndev, creq, nitrox_aead_callback,
					 areq);
पूर्ण

अटल पूर्णांक nitrox_aead_init(काष्ठा crypto_aead *aead)
अणु
	काष्ठा nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);
	काष्ठा crypto_ctx_hdr *chdr;

	/* get the first device */
	nctx->ndev = nitrox_get_first_device();
	अगर (!nctx->ndev)
		वापस -ENODEV;

	/* allocate nitrox crypto context */
	chdr = crypto_alloc_context(nctx->ndev);
	अगर (!chdr) अणु
		nitrox_put_device(nctx->ndev);
		वापस -ENOMEM;
	पूर्ण
	nctx->chdr = chdr;
	nctx->u.ctx_handle = (uपूर्णांकptr_t)((u8 *)chdr->vaddr +
					 माप(काष्ठा ctx_hdr));
	nctx->u.fctx->flags.f = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक nitrox_gcm_common_init(काष्ठा crypto_aead *aead)
अणु
	पूर्णांक ret;
	काष्ठा nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);
	जोड़ fc_ctx_flags *flags;

	ret = nitrox_aead_init(aead);
	अगर (ret)
		वापस ret;

	flags = &nctx->u.fctx->flags;
	flags->w0.cipher_type = CIPHER_AES_GCM;
	flags->w0.hash_type = AUTH_शून्य;
	flags->w0.iv_source = IV_FROM_DPTR;
	/* ask microcode to calculate ipad/opad */
	flags->w0.auth_input_type = 1;
	flags->f = cpu_to_be64(flags->fu);

	वापस 0;
पूर्ण

अटल पूर्णांक nitrox_aes_gcm_init(काष्ठा crypto_aead *aead)
अणु
	पूर्णांक ret;

	ret = nitrox_gcm_common_init(aead);
	अगर (ret)
		वापस ret;

	crypto_aead_set_reqsize(aead,
				माप(काष्ठा aead_request) +
					माप(काष्ठा nitrox_aead_rctx));

	वापस 0;
पूर्ण

अटल व्योम nitrox_aead_निकास(काष्ठा crypto_aead *aead)
अणु
	काष्ठा nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);

	/* मुक्त the nitrox crypto context */
	अगर (nctx->u.ctx_handle) अणु
		काष्ठा flexi_crypto_context *fctx = nctx->u.fctx;

		memzero_explicit(&fctx->crypto, माप(काष्ठा crypto_keys));
		memzero_explicit(&fctx->auth, माप(काष्ठा auth_keys));
		crypto_मुक्त_context((व्योम *)nctx->chdr);
	पूर्ण
	nitrox_put_device(nctx->ndev);

	nctx->u.ctx_handle = 0;
	nctx->ndev = शून्य;
पूर्ण

अटल पूर्णांक nitrox_rfc4106_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);
	काष्ठा flexi_crypto_context *fctx = nctx->u.fctx;
	पूर्णांक ret;

	अगर (keylen < GCM_AES_SALT_SIZE)
		वापस -EINVAL;

	keylen -= GCM_AES_SALT_SIZE;
	ret = nitrox_aes_gcm_setkey(aead, key, keylen);
	अगर (ret)
		वापस ret;

	स_नकल(fctx->crypto.iv, key + keylen, GCM_AES_SALT_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक nitrox_rfc4106_setauthsize(काष्ठा crypto_aead *aead,
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

	वापस nitrox_aead_setauthsize(aead, authsize);
पूर्ण

अटल पूर्णांक nitrox_rfc4106_set_aead_rctx_sglist(काष्ठा aead_request *areq)
अणु
	काष्ठा nitrox_rfc4106_rctx *rctx = aead_request_ctx(areq);
	काष्ठा nitrox_aead_rctx *aead_rctx = &rctx->base;
	अचिन्हित पूर्णांक assoclen = areq->assoclen - GCM_RFC4106_IV_SIZE;
	काष्ठा scatterlist *sg;

	अगर (areq->assoclen != 16 && areq->assoclen != 20)
		वापस -EINVAL;

	scatterwalk_map_and_copy(rctx->assoc, areq->src, 0, assoclen, 0);
	sg_init_table(rctx->src, 3);
	sg_set_buf(rctx->src, rctx->assoc, assoclen);
	sg = scatterwalk_ffwd(rctx->src + 1, areq->src, areq->assoclen);
	अगर (sg != rctx->src + 1)
		sg_chain(rctx->src, 2, sg);

	अगर (areq->src != areq->dst) अणु
		sg_init_table(rctx->dst, 3);
		sg_set_buf(rctx->dst, rctx->assoc, assoclen);
		sg = scatterwalk_ffwd(rctx->dst + 1, areq->dst, areq->assoclen);
		अगर (sg != rctx->dst + 1)
			sg_chain(rctx->dst, 2, sg);
	पूर्ण

	aead_rctx->src = rctx->src;
	aead_rctx->dst = (areq->src == areq->dst) ? rctx->src : rctx->dst;

	वापस 0;
पूर्ण

अटल व्योम nitrox_rfc4106_callback(व्योम *arg, पूर्णांक err)
अणु
	काष्ठा aead_request *areq = arg;
	काष्ठा nitrox_rfc4106_rctx *rctx = aead_request_ctx(areq);
	काष्ठा nitrox_kcrypt_request *nkreq = &rctx->base.nkreq;

	मुक्त_src_sglist(nkreq);
	मुक्त_dst_sglist(nkreq);
	अगर (err) अणु
		pr_err_ratelimited("request failed status 0x%0x\n", err);
		err = -EINVAL;
	पूर्ण

	areq->base.complete(&areq->base, err);
पूर्ण

अटल पूर्णांक nitrox_rfc4106_enc(काष्ठा aead_request *areq)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(areq);
	काष्ठा nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);
	काष्ठा nitrox_rfc4106_rctx *rctx = aead_request_ctx(areq);
	काष्ठा nitrox_aead_rctx *aead_rctx = &rctx->base;
	काष्ठा se_crypto_request *creq = &aead_rctx->nkreq.creq;
	पूर्णांक ret;

	aead_rctx->cryptlen = areq->cryptlen;
	aead_rctx->assoclen = areq->assoclen - GCM_RFC4106_IV_SIZE;
	aead_rctx->srclen = aead_rctx->assoclen + aead_rctx->cryptlen;
	aead_rctx->dstlen = aead_rctx->srclen + aead->authsize;
	aead_rctx->iv = areq->iv;
	aead_rctx->ivsize = GCM_RFC4106_IV_SIZE;
	aead_rctx->flags = areq->base.flags;
	aead_rctx->ctx_handle = nctx->u.ctx_handle;
	aead_rctx->ctrl_arg = ENCRYPT;

	ret = nitrox_rfc4106_set_aead_rctx_sglist(areq);
	अगर (ret)
		वापस ret;

	ret = nitrox_set_creq(aead_rctx);
	अगर (ret)
		वापस ret;

	/* send the crypto request */
	वापस nitrox_process_se_request(nctx->ndev, creq,
					 nitrox_rfc4106_callback, areq);
पूर्ण

अटल पूर्णांक nitrox_rfc4106_dec(काष्ठा aead_request *areq)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(areq);
	काष्ठा nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);
	काष्ठा nitrox_rfc4106_rctx *rctx = aead_request_ctx(areq);
	काष्ठा nitrox_aead_rctx *aead_rctx = &rctx->base;
	काष्ठा se_crypto_request *creq = &aead_rctx->nkreq.creq;
	पूर्णांक ret;

	aead_rctx->cryptlen = areq->cryptlen - aead->authsize;
	aead_rctx->assoclen = areq->assoclen - GCM_RFC4106_IV_SIZE;
	aead_rctx->srclen =
		areq->cryptlen - GCM_RFC4106_IV_SIZE + areq->assoclen;
	aead_rctx->dstlen = aead_rctx->srclen - aead->authsize;
	aead_rctx->iv = areq->iv;
	aead_rctx->ivsize = GCM_RFC4106_IV_SIZE;
	aead_rctx->flags = areq->base.flags;
	aead_rctx->ctx_handle = nctx->u.ctx_handle;
	aead_rctx->ctrl_arg = DECRYPT;

	ret = nitrox_rfc4106_set_aead_rctx_sglist(areq);
	अगर (ret)
		वापस ret;

	ret = nitrox_set_creq(aead_rctx);
	अगर (ret)
		वापस ret;

	/* send the crypto request */
	वापस nitrox_process_se_request(nctx->ndev, creq,
					 nitrox_rfc4106_callback, areq);
पूर्ण

अटल पूर्णांक nitrox_rfc4106_init(काष्ठा crypto_aead *aead)
अणु
	पूर्णांक ret;

	ret = nitrox_gcm_common_init(aead);
	अगर (ret)
		वापस ret;

	crypto_aead_set_reqsize(aead, माप(काष्ठा aead_request) +
				माप(काष्ठा nitrox_rfc4106_rctx));

	वापस 0;
पूर्ण

अटल काष्ठा aead_alg nitrox_aeads[] = अणु अणु
	.base = अणु
		.cra_name = "gcm(aes)",
		.cra_driver_name = "n5_aes_gcm",
		.cra_priority = PRIO,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = 1,
		.cra_ctxsize = माप(काष्ठा nitrox_crypto_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.setkey = nitrox_aes_gcm_setkey,
	.setauthsize = nitrox_aes_gcm_setauthsize,
	.encrypt = nitrox_aes_gcm_enc,
	.decrypt = nitrox_aes_gcm_dec,
	.init = nitrox_aes_gcm_init,
	.निकास = nitrox_aead_निकास,
	.ivsize = GCM_AES_IV_SIZE,
	.maxauthsize = AES_BLOCK_SIZE,
पूर्ण, अणु
	.base = अणु
		.cra_name = "rfc4106(gcm(aes))",
		.cra_driver_name = "n5_rfc4106",
		.cra_priority = PRIO,
		.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = 1,
		.cra_ctxsize = माप(काष्ठा nitrox_crypto_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
	पूर्ण,
	.setkey = nitrox_rfc4106_setkey,
	.setauthsize = nitrox_rfc4106_setauthsize,
	.encrypt = nitrox_rfc4106_enc,
	.decrypt = nitrox_rfc4106_dec,
	.init = nitrox_rfc4106_init,
	.निकास = nitrox_aead_निकास,
	.ivsize = GCM_RFC4106_IV_SIZE,
	.maxauthsize = AES_BLOCK_SIZE,
पूर्ण पूर्ण;

पूर्णांक nitrox_रेजिस्टर_aeads(व्योम)
अणु
	वापस crypto_रेजिस्टर_aeads(nitrox_aeads, ARRAY_SIZE(nitrox_aeads));
पूर्ण

व्योम nitrox_unरेजिस्टर_aeads(व्योम)
अणु
	crypto_unरेजिस्टर_aeads(nitrox_aeads, ARRAY_SIZE(nitrox_aeads));
पूर्ण
