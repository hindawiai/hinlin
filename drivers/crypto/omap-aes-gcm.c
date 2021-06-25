<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cryptographic API.
 *
 * Support क्रम OMAP AES GCM HW acceleration.
 *
 * Copyright (c) 2016 Texas Instruments Incorporated
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/omap-dma.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <crypto/aes.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/skcipher.h>
#समावेश <crypto/पूर्णांकernal/aead.h>

#समावेश "omap-crypto.h"
#समावेश "omap-aes.h"

अटल पूर्णांक omap_aes_gcm_handle_queue(काष्ठा omap_aes_dev *dd,
				     काष्ठा aead_request *req);

अटल व्योम omap_aes_gcm_finish_req(काष्ठा omap_aes_dev *dd, पूर्णांक ret)
अणु
	काष्ठा aead_request *req = dd->aead_req;

	dd->in_sg = शून्य;
	dd->out_sg = शून्य;

	crypto_finalize_aead_request(dd->engine, req, ret);

	pm_runसमय_mark_last_busy(dd->dev);
	pm_runसमय_put_स्वतःsuspend(dd->dev);
पूर्ण

अटल व्योम omap_aes_gcm_करोne_task(काष्ठा omap_aes_dev *dd)
अणु
	u8 *tag;
	पूर्णांक alen, clen, i, ret = 0, nsg;
	काष्ठा omap_aes_reqctx *rctx;

	alen = ALIGN(dd->assoc_len, AES_BLOCK_SIZE);
	clen = ALIGN(dd->total, AES_BLOCK_SIZE);
	rctx = aead_request_ctx(dd->aead_req);

	nsg = !!(dd->assoc_len && dd->total);

	dma_sync_sg_क्रम_device(dd->dev, dd->out_sg, dd->out_sg_len,
			       DMA_FROM_DEVICE);
	dma_unmap_sg(dd->dev, dd->in_sg, dd->in_sg_len, DMA_TO_DEVICE);
	dma_unmap_sg(dd->dev, dd->out_sg, dd->out_sg_len, DMA_FROM_DEVICE);
	omap_aes_crypt_dma_stop(dd);

	omap_crypto_cleanup(dd->out_sg, dd->orig_out,
			    dd->aead_req->assoclen, dd->total,
			    FLAGS_OUT_DATA_ST_SHIFT, dd->flags);

	अगर (dd->flags & FLAGS_ENCRYPT)
		scatterwalk_map_and_copy(rctx->auth_tag,
					 dd->aead_req->dst,
					 dd->total + dd->aead_req->assoclen,
					 dd->authsize, 1);

	omap_crypto_cleanup(&dd->in_sgl[0], शून्य, 0, alen,
			    FLAGS_ASSOC_DATA_ST_SHIFT, dd->flags);

	omap_crypto_cleanup(&dd->in_sgl[nsg], शून्य, 0, clen,
			    FLAGS_IN_DATA_ST_SHIFT, dd->flags);

	अगर (!(dd->flags & FLAGS_ENCRYPT)) अणु
		tag = (u8 *)rctx->auth_tag;
		क्रम (i = 0; i < dd->authsize; i++) अणु
			अगर (tag[i]) अणु
				ret = -EBADMSG;
			पूर्ण
		पूर्ण
	पूर्ण

	omap_aes_gcm_finish_req(dd, ret);
पूर्ण

अटल पूर्णांक omap_aes_gcm_copy_buffers(काष्ठा omap_aes_dev *dd,
				     काष्ठा aead_request *req)
अणु
	पूर्णांक alen, clen, cryptlen, assoclen, ret;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	अचिन्हित पूर्णांक authlen = crypto_aead_authsize(aead);
	काष्ठा scatterlist *पंचांगp, sg_arr[2];
	पूर्णांक nsg;
	u16 flags;

	assoclen = req->assoclen;
	cryptlen = req->cryptlen;

	अगर (dd->flags & FLAGS_RFC4106_GCM)
		assoclen -= 8;

	अगर (!(dd->flags & FLAGS_ENCRYPT))
		cryptlen -= authlen;

	alen = ALIGN(assoclen, AES_BLOCK_SIZE);
	clen = ALIGN(cryptlen, AES_BLOCK_SIZE);

	nsg = !!(assoclen && cryptlen);

	omap_aes_clear_copy_flags(dd);

	sg_init_table(dd->in_sgl, nsg + 1);
	अगर (assoclen) अणु
		पंचांगp = req->src;
		ret = omap_crypto_align_sg(&पंचांगp, assoclen,
					   AES_BLOCK_SIZE, dd->in_sgl,
					   OMAP_CRYPTO_COPY_DATA |
					   OMAP_CRYPTO_ZERO_BUF |
					   OMAP_CRYPTO_FORCE_SINGLE_ENTRY,
					   FLAGS_ASSOC_DATA_ST_SHIFT,
					   &dd->flags);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (cryptlen) अणु
		पंचांगp = scatterwalk_ffwd(sg_arr, req->src, req->assoclen);

		अगर (nsg)
			sg_unmark_end(dd->in_sgl);

		ret = omap_crypto_align_sg(&पंचांगp, cryptlen,
					   AES_BLOCK_SIZE, &dd->in_sgl[nsg],
					   OMAP_CRYPTO_COPY_DATA |
					   OMAP_CRYPTO_ZERO_BUF |
					   OMAP_CRYPTO_FORCE_SINGLE_ENTRY,
					   FLAGS_IN_DATA_ST_SHIFT,
					   &dd->flags);
		अगर (ret)
			वापस ret;
	पूर्ण

	dd->in_sg = dd->in_sgl;
	dd->total = cryptlen;
	dd->assoc_len = assoclen;
	dd->authsize = authlen;

	dd->out_sg = req->dst;
	dd->orig_out = req->dst;

	dd->out_sg = scatterwalk_ffwd(sg_arr, req->dst, req->assoclen);

	flags = 0;
	अगर (req->src == req->dst || dd->out_sg == sg_arr)
		flags |= OMAP_CRYPTO_FORCE_COPY;

	अगर (cryptlen) अणु
		ret = omap_crypto_align_sg(&dd->out_sg, cryptlen,
					   AES_BLOCK_SIZE, &dd->out_sgl,
					   flags,
					   FLAGS_OUT_DATA_ST_SHIFT, &dd->flags);
		अगर (ret)
			वापस ret;
	पूर्ण

	dd->in_sg_len = sg_nents_क्रम_len(dd->in_sg, alen + clen);
	dd->out_sg_len = sg_nents_क्रम_len(dd->out_sg, clen);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_encrypt_iv(काष्ठा aead_request *req, u32 *tag, u32 *iv)
अणु
	काष्ठा omap_aes_gcm_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));

	aes_encrypt(&ctx->actx, (u8 *)tag, (u8 *)iv);
	वापस 0;
पूर्ण

व्योम omap_aes_gcm_dma_out_callback(व्योम *data)
अणु
	काष्ठा omap_aes_dev *dd = data;
	काष्ठा omap_aes_reqctx *rctx;
	पूर्णांक i, val;
	u32 *auth_tag, tag[4];

	अगर (!(dd->flags & FLAGS_ENCRYPT))
		scatterwalk_map_and_copy(tag, dd->aead_req->src,
					 dd->total + dd->aead_req->assoclen,
					 dd->authsize, 0);

	rctx = aead_request_ctx(dd->aead_req);
	auth_tag = (u32 *)rctx->auth_tag;
	क्रम (i = 0; i < 4; i++) अणु
		val = omap_aes_पढ़ो(dd, AES_REG_TAG_N(dd, i));
		auth_tag[i] = val ^ auth_tag[i];
		अगर (!(dd->flags & FLAGS_ENCRYPT))
			auth_tag[i] = auth_tag[i] ^ tag[i];
	पूर्ण

	omap_aes_gcm_करोne_task(dd);
पूर्ण

अटल पूर्णांक omap_aes_gcm_handle_queue(काष्ठा omap_aes_dev *dd,
				     काष्ठा aead_request *req)
अणु
	अगर (req)
		वापस crypto_transfer_aead_request_to_engine(dd->engine, req);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_aes_gcm_prepare_req(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा aead_request *req = container_of(areq, काष्ठा aead_request,
						base);
	काष्ठा omap_aes_reqctx *rctx = aead_request_ctx(req);
	काष्ठा omap_aes_dev *dd = rctx->dd;
	काष्ठा omap_aes_gcm_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	पूर्णांक err;

	dd->aead_req = req;

	rctx->mode &= FLAGS_MODE_MASK;
	dd->flags = (dd->flags & ~FLAGS_MODE_MASK) | rctx->mode;

	err = omap_aes_gcm_copy_buffers(dd, req);
	अगर (err)
		वापस err;

	dd->ctx = &ctx->octx;

	वापस omap_aes_ग_लिखो_ctrl(dd);
पूर्ण

अटल पूर्णांक omap_aes_gcm_crypt(काष्ठा aead_request *req, अचिन्हित दीर्घ mode)
अणु
	काष्ठा omap_aes_reqctx *rctx = aead_request_ctx(req);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	अचिन्हित पूर्णांक authlen = crypto_aead_authsize(aead);
	काष्ठा omap_aes_dev *dd;
	__be32 counter = cpu_to_be32(1);
	पूर्णांक err, assoclen;

	स_रखो(rctx->auth_tag, 0, माप(rctx->auth_tag));
	स_नकल(rctx->iv + GCM_AES_IV_SIZE, &counter, 4);

	err = करो_encrypt_iv(req, (u32 *)rctx->auth_tag, (u32 *)rctx->iv);
	अगर (err)
		वापस err;

	अगर (mode & FLAGS_RFC4106_GCM)
		assoclen = req->assoclen - 8;
	अन्यथा
		assoclen = req->assoclen;
	अगर (assoclen + req->cryptlen == 0) अणु
		scatterwalk_map_and_copy(rctx->auth_tag, req->dst, 0, authlen,
					 1);
		वापस 0;
	पूर्ण

	dd = omap_aes_find_dev(rctx);
	अगर (!dd)
		वापस -ENODEV;
	rctx->mode = mode;

	वापस omap_aes_gcm_handle_queue(dd, req);
पूर्ण

पूर्णांक omap_aes_gcm_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा omap_aes_reqctx *rctx = aead_request_ctx(req);

	स_नकल(rctx->iv, req->iv, GCM_AES_IV_SIZE);
	वापस omap_aes_gcm_crypt(req, FLAGS_ENCRYPT | FLAGS_GCM);
पूर्ण

पूर्णांक omap_aes_gcm_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा omap_aes_reqctx *rctx = aead_request_ctx(req);

	स_नकल(rctx->iv, req->iv, GCM_AES_IV_SIZE);
	वापस omap_aes_gcm_crypt(req, FLAGS_GCM);
पूर्ण

पूर्णांक omap_aes_4106gcm_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा omap_aes_gcm_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा omap_aes_reqctx *rctx = aead_request_ctx(req);

	स_नकल(rctx->iv, ctx->octx.nonce, 4);
	स_नकल(rctx->iv + 4, req->iv, 8);
	वापस crypto_ipsec_check_assoclen(req->assoclen) ?:
	       omap_aes_gcm_crypt(req, FLAGS_ENCRYPT | FLAGS_GCM |
				  FLAGS_RFC4106_GCM);
पूर्ण

पूर्णांक omap_aes_4106gcm_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा omap_aes_gcm_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा omap_aes_reqctx *rctx = aead_request_ctx(req);

	स_नकल(rctx->iv, ctx->octx.nonce, 4);
	स_नकल(rctx->iv + 4, req->iv, 8);
	वापस crypto_ipsec_check_assoclen(req->assoclen) ?:
	       omap_aes_gcm_crypt(req, FLAGS_GCM | FLAGS_RFC4106_GCM);
पूर्ण

पूर्णांक omap_aes_gcm_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा omap_aes_gcm_ctx *ctx = crypto_aead_ctx(tfm);
	पूर्णांक ret;

	ret = aes_expandkey(&ctx->actx, key, keylen);
	अगर (ret)
		वापस ret;

	स_नकल(ctx->octx.key, key, keylen);
	ctx->octx.keylen = keylen;

	वापस 0;
पूर्ण

पूर्णांक omap_aes_4106gcm_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा omap_aes_gcm_ctx *ctx = crypto_aead_ctx(tfm);
	पूर्णांक ret;

	अगर (keylen < 4)
		वापस -EINVAL;
	keylen -= 4;

	ret = aes_expandkey(&ctx->actx, key, keylen);
	अगर (ret)
		वापस ret;

	स_नकल(ctx->octx.key, key, keylen);
	स_नकल(ctx->octx.nonce, key + keylen, 4);
	ctx->octx.keylen = keylen;

	वापस 0;
पूर्ण

पूर्णांक omap_aes_gcm_setauthsize(काष्ठा crypto_aead *tfm, अचिन्हित पूर्णांक authsize)
अणु
	वापस crypto_gcm_check_authsize(authsize);
पूर्ण

पूर्णांक omap_aes_4106gcm_setauthsize(काष्ठा crypto_aead *parent,
				 अचिन्हित पूर्णांक authsize)
अणु
	वापस crypto_rfc4106_check_authsize(authsize);
पूर्ण

अटल पूर्णांक omap_aes_gcm_crypt_req(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा aead_request *req = container_of(areq, काष्ठा aead_request,
						base);
	काष्ठा omap_aes_reqctx *rctx = aead_request_ctx(req);
	काष्ठा omap_aes_dev *dd = rctx->dd;
	पूर्णांक ret = 0;

	अगर (!dd)
		वापस -ENODEV;

	अगर (dd->in_sg_len)
		ret = omap_aes_crypt_dma_start(dd);
	अन्यथा
		omap_aes_gcm_dma_out_callback(dd);

	वापस ret;
पूर्ण

पूर्णांक omap_aes_gcm_cra_init(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा omap_aes_ctx *ctx = crypto_aead_ctx(tfm);

	ctx->enginectx.op.prepare_request = omap_aes_gcm_prepare_req;
	ctx->enginectx.op.unprepare_request = शून्य;
	ctx->enginectx.op.करो_one_request = omap_aes_gcm_crypt_req;

	crypto_aead_set_reqsize(tfm, माप(काष्ठा omap_aes_reqctx));

	वापस 0;
पूर्ण
