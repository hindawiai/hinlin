<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Crypto acceleration support क्रम Rockchip RK3288
 *
 * Copyright (c) 2015, Fuzhou Rockchip Electronics Co., Ltd
 *
 * Author: Zain Wang <zain.wang@rock-chips.com>
 *
 * Some ideas are from marvell/cesa.c and s5p-sss.c driver.
 */
#समावेश <linux/device.h>
#समावेश "rk3288_crypto.h"

/*
 * IC can not process zero message hash,
 * so we put the fixed hash out when met zero message.
 */

अटल पूर्णांक zero_message_process(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	पूर्णांक rk_digest_size = crypto_ahash_digestsize(tfm);

	चयन (rk_digest_size) अणु
	हाल SHA1_DIGEST_SIZE:
		स_नकल(req->result, sha1_zero_message_hash, rk_digest_size);
		अवरोध;
	हाल SHA256_DIGEST_SIZE:
		स_नकल(req->result, sha256_zero_message_hash, rk_digest_size);
		अवरोध;
	हाल MD5_DIGEST_SIZE:
		स_नकल(req->result, md5_zero_message_hash, rk_digest_size);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rk_ahash_crypto_complete(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	अगर (base->complete)
		base->complete(base, err);
पूर्ण

अटल व्योम rk_ahash_reg_init(काष्ठा rk_crypto_info *dev)
अणु
	काष्ठा ahash_request *req = ahash_request_cast(dev->async_req);
	काष्ठा rk_ahash_rctx *rctx = ahash_request_ctx(req);
	पूर्णांक reg_status;

	reg_status = CRYPTO_READ(dev, RK_CRYPTO_CTRL) |
		     RK_CRYPTO_HASH_FLUSH | _SBF(0xffff, 16);
	CRYPTO_WRITE(dev, RK_CRYPTO_CTRL, reg_status);

	reg_status = CRYPTO_READ(dev, RK_CRYPTO_CTRL);
	reg_status &= (~RK_CRYPTO_HASH_FLUSH);
	reg_status |= _SBF(0xffff, 16);
	CRYPTO_WRITE(dev, RK_CRYPTO_CTRL, reg_status);

	स_रखो_io(dev->reg + RK_CRYPTO_HASH_DOUT_0, 0, 32);

	CRYPTO_WRITE(dev, RK_CRYPTO_INTENA, RK_CRYPTO_HRDMA_ERR_ENA |
					    RK_CRYPTO_HRDMA_DONE_ENA);

	CRYPTO_WRITE(dev, RK_CRYPTO_INTSTS, RK_CRYPTO_HRDMA_ERR_INT |
					    RK_CRYPTO_HRDMA_DONE_INT);

	CRYPTO_WRITE(dev, RK_CRYPTO_HASH_CTRL, rctx->mode |
					       RK_CRYPTO_HASH_SWAP_DO);

	CRYPTO_WRITE(dev, RK_CRYPTO_CONF, RK_CRYPTO_BYTESWAP_HRFIFO |
					  RK_CRYPTO_BYTESWAP_BRFIFO |
					  RK_CRYPTO_BYTESWAP_BTFIFO);

	CRYPTO_WRITE(dev, RK_CRYPTO_HASH_MSG_LEN, dev->total);
पूर्ण

अटल पूर्णांक rk_ahash_init(काष्ठा ahash_request *req)
अणु
	काष्ठा rk_ahash_rctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा rk_ahash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback_tfm);
	rctx->fallback_req.base.flags = req->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_init(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक rk_ahash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा rk_ahash_rctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा rk_ahash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback_tfm);
	rctx->fallback_req.base.flags = req->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.nbytes = req->nbytes;
	rctx->fallback_req.src = req->src;

	वापस crypto_ahash_update(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक rk_ahash_final(काष्ठा ahash_request *req)
अणु
	काष्ठा rk_ahash_rctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा rk_ahash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback_tfm);
	rctx->fallback_req.base.flags = req->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.result = req->result;

	वापस crypto_ahash_final(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक rk_ahash_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा rk_ahash_rctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा rk_ahash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback_tfm);
	rctx->fallback_req.base.flags = req->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;

	rctx->fallback_req.nbytes = req->nbytes;
	rctx->fallback_req.src = req->src;
	rctx->fallback_req.result = req->result;

	वापस crypto_ahash_finup(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक rk_ahash_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा rk_ahash_rctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा rk_ahash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback_tfm);
	rctx->fallback_req.base.flags = req->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_import(&rctx->fallback_req, in);
पूर्ण

अटल पूर्णांक rk_ahash_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा rk_ahash_rctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा rk_ahash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback_tfm);
	rctx->fallback_req.base.flags = req->base.flags &
					CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_export(&rctx->fallback_req, out);
पूर्ण

अटल पूर्णांक rk_ahash_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा rk_ahash_ctx *tctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा rk_crypto_info *dev = tctx->dev;

	अगर (!req->nbytes)
		वापस zero_message_process(req);
	अन्यथा
		वापस dev->enqueue(dev, &req->base);
पूर्ण

अटल व्योम crypto_ahash_dma_start(काष्ठा rk_crypto_info *dev)
अणु
	CRYPTO_WRITE(dev, RK_CRYPTO_HRDMAS, dev->addr_in);
	CRYPTO_WRITE(dev, RK_CRYPTO_HRDMAL, (dev->count + 3) / 4);
	CRYPTO_WRITE(dev, RK_CRYPTO_CTRL, RK_CRYPTO_HASH_START |
					  (RK_CRYPTO_HASH_START << 16));
पूर्ण

अटल पूर्णांक rk_ahash_set_data_start(काष्ठा rk_crypto_info *dev)
अणु
	पूर्णांक err;

	err = dev->load_data(dev, dev->sg_src, शून्य);
	अगर (!err)
		crypto_ahash_dma_start(dev);
	वापस err;
पूर्ण

अटल पूर्णांक rk_ahash_start(काष्ठा rk_crypto_info *dev)
अणु
	काष्ठा ahash_request *req = ahash_request_cast(dev->async_req);
	काष्ठा crypto_ahash *tfm;
	काष्ठा rk_ahash_rctx *rctx;

	dev->total = req->nbytes;
	dev->left_bytes = req->nbytes;
	dev->aligned = 0;
	dev->align_size = 4;
	dev->sg_dst = शून्य;
	dev->sg_src = req->src;
	dev->first = req->src;
	dev->src_nents = sg_nents(req->src);
	rctx = ahash_request_ctx(req);
	rctx->mode = 0;

	tfm = crypto_ahash_reqtfm(req);
	चयन (crypto_ahash_digestsize(tfm)) अणु
	हाल SHA1_DIGEST_SIZE:
		rctx->mode = RK_CRYPTO_HASH_SHA1;
		अवरोध;
	हाल SHA256_DIGEST_SIZE:
		rctx->mode = RK_CRYPTO_HASH_SHA256;
		अवरोध;
	हाल MD5_DIGEST_SIZE:
		rctx->mode = RK_CRYPTO_HASH_MD5;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rk_ahash_reg_init(dev);
	वापस rk_ahash_set_data_start(dev);
पूर्ण

अटल पूर्णांक rk_ahash_crypto_rx(काष्ठा rk_crypto_info *dev)
अणु
	पूर्णांक err = 0;
	काष्ठा ahash_request *req = ahash_request_cast(dev->async_req);
	काष्ठा crypto_ahash *tfm;

	dev->unload_data(dev);
	अगर (dev->left_bytes) अणु
		अगर (dev->aligned) अणु
			अगर (sg_is_last(dev->sg_src)) अणु
				dev_warn(dev->dev, "[%s:%d], Lack of data\n",
					 __func__, __LINE__);
				err = -ENOMEM;
				जाओ out_rx;
			पूर्ण
			dev->sg_src = sg_next(dev->sg_src);
		पूर्ण
		err = rk_ahash_set_data_start(dev);
	पूर्ण अन्यथा अणु
		/*
		 * it will take some समय to process date after last dma
		 * transmission.
		 *
		 * रुकोing समय is relative with the last date len,
		 * so cannot set a fixed समय here.
		 * 10us makes प्रणाली not call here frequently wasting
		 * efficiency, and make it response quickly when dma
		 * complete.
		 */
		जबतक (!CRYPTO_READ(dev, RK_CRYPTO_HASH_STS))
			udelay(10);

		tfm = crypto_ahash_reqtfm(req);
		स_नकल_fromio(req->result, dev->reg + RK_CRYPTO_HASH_DOUT_0,
			      crypto_ahash_digestsize(tfm));
		dev->complete(dev->async_req, 0);
		tasklet_schedule(&dev->queue_task);
	पूर्ण

out_rx:
	वापस err;
पूर्ण

अटल पूर्णांक rk_cra_hash_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा rk_ahash_ctx *tctx = crypto_tfm_ctx(tfm);
	काष्ठा rk_crypto_पंचांगp *algt;
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->__crt_alg);

	स्थिर अक्षर *alg_name = crypto_tfm_alg_name(tfm);

	algt = container_of(alg, काष्ठा rk_crypto_पंचांगp, alg.hash);

	tctx->dev = algt->dev;
	tctx->dev->addr_vir = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!tctx->dev->addr_vir) अणु
		dev_err(tctx->dev->dev, "failed to kmalloc for addr_vir\n");
		वापस -ENOMEM;
	पूर्ण
	tctx->dev->start = rk_ahash_start;
	tctx->dev->update = rk_ahash_crypto_rx;
	tctx->dev->complete = rk_ahash_crypto_complete;

	/* क्रम fallback */
	tctx->fallback_tfm = crypto_alloc_ahash(alg_name, 0,
					       CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(tctx->fallback_tfm)) अणु
		dev_err(tctx->dev->dev, "Could not load fallback driver.\n");
		वापस PTR_ERR(tctx->fallback_tfm);
	पूर्ण
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा rk_ahash_rctx) +
				 crypto_ahash_reqsize(tctx->fallback_tfm));

	वापस tctx->dev->enable_clk(tctx->dev);
पूर्ण

अटल व्योम rk_cra_hash_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा rk_ahash_ctx *tctx = crypto_tfm_ctx(tfm);

	मुक्त_page((अचिन्हित दीर्घ)tctx->dev->addr_vir);
	वापस tctx->dev->disable_clk(tctx->dev);
पूर्ण

काष्ठा rk_crypto_पंचांगp rk_ahash_sha1 = अणु
	.type = ALG_TYPE_HASH,
	.alg.hash = अणु
		.init = rk_ahash_init,
		.update = rk_ahash_update,
		.final = rk_ahash_final,
		.finup = rk_ahash_finup,
		.export = rk_ahash_export,
		.import = rk_ahash_import,
		.digest = rk_ahash_digest,
		.halg = अणु
			 .digestsize = SHA1_DIGEST_SIZE,
			 .statesize = माप(काष्ठा sha1_state),
			 .base = अणु
				  .cra_name = "sha1",
				  .cra_driver_name = "rk-sha1",
				  .cra_priority = 300,
				  .cra_flags = CRYPTO_ALG_ASYNC |
					       CRYPTO_ALG_NEED_FALLBACK,
				  .cra_blocksize = SHA1_BLOCK_SIZE,
				  .cra_ctxsize = माप(काष्ठा rk_ahash_ctx),
				  .cra_alignmask = 3,
				  .cra_init = rk_cra_hash_init,
				  .cra_निकास = rk_cra_hash_निकास,
				  .cra_module = THIS_MODULE,
				  पूर्ण
			 पूर्ण
	पूर्ण
पूर्ण;

काष्ठा rk_crypto_पंचांगp rk_ahash_sha256 = अणु
	.type = ALG_TYPE_HASH,
	.alg.hash = अणु
		.init = rk_ahash_init,
		.update = rk_ahash_update,
		.final = rk_ahash_final,
		.finup = rk_ahash_finup,
		.export = rk_ahash_export,
		.import = rk_ahash_import,
		.digest = rk_ahash_digest,
		.halg = अणु
			 .digestsize = SHA256_DIGEST_SIZE,
			 .statesize = माप(काष्ठा sha256_state),
			 .base = अणु
				  .cra_name = "sha256",
				  .cra_driver_name = "rk-sha256",
				  .cra_priority = 300,
				  .cra_flags = CRYPTO_ALG_ASYNC |
					       CRYPTO_ALG_NEED_FALLBACK,
				  .cra_blocksize = SHA256_BLOCK_SIZE,
				  .cra_ctxsize = माप(काष्ठा rk_ahash_ctx),
				  .cra_alignmask = 3,
				  .cra_init = rk_cra_hash_init,
				  .cra_निकास = rk_cra_hash_निकास,
				  .cra_module = THIS_MODULE,
				  पूर्ण
			 पूर्ण
	पूर्ण
पूर्ण;

काष्ठा rk_crypto_पंचांगp rk_ahash_md5 = अणु
	.type = ALG_TYPE_HASH,
	.alg.hash = अणु
		.init = rk_ahash_init,
		.update = rk_ahash_update,
		.final = rk_ahash_final,
		.finup = rk_ahash_finup,
		.export = rk_ahash_export,
		.import = rk_ahash_import,
		.digest = rk_ahash_digest,
		.halg = अणु
			 .digestsize = MD5_DIGEST_SIZE,
			 .statesize = माप(काष्ठा md5_state),
			 .base = अणु
				  .cra_name = "md5",
				  .cra_driver_name = "rk-md5",
				  .cra_priority = 300,
				  .cra_flags = CRYPTO_ALG_ASYNC |
					       CRYPTO_ALG_NEED_FALLBACK,
				  .cra_blocksize = SHA1_BLOCK_SIZE,
				  .cra_ctxsize = माप(काष्ठा rk_ahash_ctx),
				  .cra_alignmask = 3,
				  .cra_init = rk_cra_hash_init,
				  .cra_निकास = rk_cra_hash_निकास,
				  .cra_module = THIS_MODULE,
				  पूर्ण
			पूर्ण
	पूर्ण
पूर्ण;
