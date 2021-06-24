<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx ZynqMP AES Driver.
 * Copyright (c) 2020 Xilinx Inc.
 */

#समावेश <crypto/aes.h>
#समावेश <crypto/engine.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/scatterwalk.h>

#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/firmware/xlnx-zynqmp.h>

#घोषणा ZYNQMP_DMA_BIT_MASK	32U

#घोषणा ZYNQMP_AES_KEY_SIZE		AES_KEYSIZE_256
#घोषणा ZYNQMP_AES_AUTH_SIZE		16U
#घोषणा ZYNQMP_KEY_SRC_SEL_KEY_LEN	1U
#घोषणा ZYNQMP_AES_BLK_SIZE		1U
#घोषणा ZYNQMP_AES_MIN_INPUT_BLK_SIZE	4U
#घोषणा ZYNQMP_AES_WORD_LEN		4U

#घोषणा ZYNQMP_AES_GCM_TAG_MISMATCH_ERR		0x01
#घोषणा ZYNQMP_AES_WRONG_KEY_SRC_ERR		0x13
#घोषणा ZYNQMP_AES_PUF_NOT_PROGRAMMED		0xE300

क्रमागत zynqmp_aead_op अणु
	ZYNQMP_AES_DECRYPT = 0,
	ZYNQMP_AES_ENCRYPT
पूर्ण;

क्रमागत zynqmp_aead_keysrc अणु
	ZYNQMP_AES_KUP_KEY = 0,
	ZYNQMP_AES_DEV_KEY,
	ZYNQMP_AES_PUF_KEY
पूर्ण;

काष्ठा zynqmp_aead_drv_ctx अणु
	जोड़ अणु
		काष्ठा aead_alg aead;
	पूर्ण alg;
	काष्ठा device *dev;
	काष्ठा crypto_engine *engine;
पूर्ण;

काष्ठा zynqmp_aead_hw_req अणु
	u64 src;
	u64 iv;
	u64 key;
	u64 dst;
	u64 size;
	u64 op;
	u64 keysrc;
पूर्ण;

काष्ठा zynqmp_aead_tfm_ctx अणु
	काष्ठा crypto_engine_ctx engine_ctx;
	काष्ठा device *dev;
	u8 key[ZYNQMP_AES_KEY_SIZE];
	u8 *iv;
	u32 keylen;
	u32 authsize;
	क्रमागत zynqmp_aead_keysrc keysrc;
	काष्ठा crypto_aead *fbk_cipher;
पूर्ण;

काष्ठा zynqmp_aead_req_ctx अणु
	क्रमागत zynqmp_aead_op op;
पूर्ण;

अटल पूर्णांक zynqmp_aes_aead_cipher(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा zynqmp_aead_tfm_ctx *tfm_ctx = crypto_aead_ctx(aead);
	काष्ठा zynqmp_aead_req_ctx *rq_ctx = aead_request_ctx(req);
	काष्ठा device *dev = tfm_ctx->dev;
	काष्ठा zynqmp_aead_hw_req *hwreq;
	dma_addr_t dma_addr_data, dma_addr_hw_req;
	अचिन्हित पूर्णांक data_size;
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;
	माप_प्रकार dma_size;
	अक्षर *kbuf;
	पूर्णांक err;

	अगर (tfm_ctx->keysrc == ZYNQMP_AES_KUP_KEY)
		dma_size = req->cryptlen + ZYNQMP_AES_KEY_SIZE
			   + GCM_AES_IV_SIZE;
	अन्यथा
		dma_size = req->cryptlen + GCM_AES_IV_SIZE;

	kbuf = dma_alloc_coherent(dev, dma_size, &dma_addr_data, GFP_KERNEL);
	अगर (!kbuf)
		वापस -ENOMEM;

	hwreq = dma_alloc_coherent(dev, माप(काष्ठा zynqmp_aead_hw_req),
				   &dma_addr_hw_req, GFP_KERNEL);
	अगर (!hwreq) अणु
		dma_मुक्त_coherent(dev, dma_size, kbuf, dma_addr_data);
		वापस -ENOMEM;
	पूर्ण

	data_size = req->cryptlen;
	scatterwalk_map_and_copy(kbuf, req->src, 0, req->cryptlen, 0);
	स_नकल(kbuf + data_size, req->iv, GCM_AES_IV_SIZE);

	hwreq->src = dma_addr_data;
	hwreq->dst = dma_addr_data;
	hwreq->iv = hwreq->src + data_size;
	hwreq->keysrc = tfm_ctx->keysrc;
	hwreq->op = rq_ctx->op;

	अगर (hwreq->op == ZYNQMP_AES_ENCRYPT)
		hwreq->size = data_size;
	अन्यथा
		hwreq->size = data_size - ZYNQMP_AES_AUTH_SIZE;

	अगर (hwreq->keysrc == ZYNQMP_AES_KUP_KEY) अणु
		स_नकल(kbuf + data_size + GCM_AES_IV_SIZE,
		       tfm_ctx->key, ZYNQMP_AES_KEY_SIZE);

		hwreq->key = hwreq->src + data_size + GCM_AES_IV_SIZE;
	पूर्ण अन्यथा अणु
		hwreq->key = 0;
	पूर्ण

	ret = zynqmp_pm_aes_engine(dma_addr_hw_req, &status);

	अगर (ret) अणु
		dev_err(dev, "ERROR: AES PM API failed\n");
		err = ret;
	पूर्ण अन्यथा अगर (status) अणु
		चयन (status) अणु
		हाल ZYNQMP_AES_GCM_TAG_MISMATCH_ERR:
			dev_err(dev, "ERROR: Gcm Tag mismatch\n");
			अवरोध;
		हाल ZYNQMP_AES_WRONG_KEY_SRC_ERR:
			dev_err(dev, "ERROR: Wrong KeySrc, enable secure mode\n");
			अवरोध;
		हाल ZYNQMP_AES_PUF_NOT_PROGRAMMED:
			dev_err(dev, "ERROR: PUF is not registered\n");
			अवरोध;
		शेष:
			dev_err(dev, "ERROR: Unknown error\n");
			अवरोध;
		पूर्ण
		err = -status;
	पूर्ण अन्यथा अणु
		अगर (hwreq->op == ZYNQMP_AES_ENCRYPT)
			data_size = data_size + ZYNQMP_AES_AUTH_SIZE;
		अन्यथा
			data_size = data_size - ZYNQMP_AES_AUTH_SIZE;

		sg_copy_from_buffer(req->dst, sg_nents(req->dst),
				    kbuf, data_size);
		err = 0;
	पूर्ण

	अगर (kbuf) अणु
		memzero_explicit(kbuf, dma_size);
		dma_मुक्त_coherent(dev, dma_size, kbuf, dma_addr_data);
	पूर्ण
	अगर (hwreq) अणु
		memzero_explicit(hwreq, माप(काष्ठा zynqmp_aead_hw_req));
		dma_मुक्त_coherent(dev, माप(काष्ठा zynqmp_aead_hw_req),
				  hwreq, dma_addr_hw_req);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक zynqmp_fallback_check(काष्ठा zynqmp_aead_tfm_ctx *tfm_ctx,
				 काष्ठा aead_request *req)
अणु
	पूर्णांक need_fallback = 0;
	काष्ठा zynqmp_aead_req_ctx *rq_ctx = aead_request_ctx(req);

	अगर (tfm_ctx->authsize != ZYNQMP_AES_AUTH_SIZE)
		need_fallback = 1;

	अगर (tfm_ctx->keysrc == ZYNQMP_AES_KUP_KEY &&
	    tfm_ctx->keylen != ZYNQMP_AES_KEY_SIZE) अणु
		need_fallback = 1;
	पूर्ण
	अगर (req->assoclen != 0 ||
	    req->cryptlen < ZYNQMP_AES_MIN_INPUT_BLK_SIZE) अणु
		need_fallback = 1;
	पूर्ण
	अगर ((req->cryptlen % ZYNQMP_AES_WORD_LEN) != 0)
		need_fallback = 1;

	अगर (rq_ctx->op == ZYNQMP_AES_DECRYPT &&
	    req->cryptlen <= ZYNQMP_AES_AUTH_SIZE) अणु
		need_fallback = 1;
	पूर्ण
	वापस need_fallback;
पूर्ण

अटल पूर्णांक zynqmp_handle_aes_req(काष्ठा crypto_engine *engine,
				 व्योम *req)
अणु
	काष्ठा aead_request *areq =
				container_of(req, काष्ठा aead_request, base);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा zynqmp_aead_tfm_ctx *tfm_ctx = crypto_aead_ctx(aead);
	काष्ठा zynqmp_aead_req_ctx *rq_ctx = aead_request_ctx(areq);
	काष्ठा aead_request *subreq = aead_request_ctx(req);
	पूर्णांक need_fallback;
	पूर्णांक err;

	need_fallback = zynqmp_fallback_check(tfm_ctx, areq);

	अगर (need_fallback) अणु
		aead_request_set_tfm(subreq, tfm_ctx->fbk_cipher);

		aead_request_set_callback(subreq, areq->base.flags,
					  शून्य, शून्य);
		aead_request_set_crypt(subreq, areq->src, areq->dst,
				       areq->cryptlen, areq->iv);
		aead_request_set_ad(subreq, areq->assoclen);
		अगर (rq_ctx->op == ZYNQMP_AES_ENCRYPT)
			err = crypto_aead_encrypt(subreq);
		अन्यथा
			err = crypto_aead_decrypt(subreq);
	पूर्ण अन्यथा अणु
		err = zynqmp_aes_aead_cipher(areq);
	पूर्ण

	crypto_finalize_aead_request(engine, areq, err);
	वापस 0;
पूर्ण

अटल पूर्णांक zynqmp_aes_aead_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
				  अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(aead);
	काष्ठा zynqmp_aead_tfm_ctx *tfm_ctx =
			(काष्ठा zynqmp_aead_tfm_ctx *)crypto_tfm_ctx(tfm);
	अचिन्हित अक्षर keysrc;

	अगर (keylen == ZYNQMP_KEY_SRC_SEL_KEY_LEN) अणु
		keysrc = *key;
		अगर (keysrc == ZYNQMP_AES_KUP_KEY ||
		    keysrc == ZYNQMP_AES_DEV_KEY ||
		    keysrc == ZYNQMP_AES_PUF_KEY) अणु
			tfm_ctx->keysrc = (क्रमागत zynqmp_aead_keysrc)keysrc;
		पूर्ण अन्यथा अणु
			tfm_ctx->keylen = keylen;
		पूर्ण
	पूर्ण अन्यथा अणु
		tfm_ctx->keylen = keylen;
		अगर (keylen == ZYNQMP_AES_KEY_SIZE) अणु
			tfm_ctx->keysrc = ZYNQMP_AES_KUP_KEY;
			स_नकल(tfm_ctx->key, key, keylen);
		पूर्ण
	पूर्ण

	tfm_ctx->fbk_cipher->base.crt_flags &= ~CRYPTO_TFM_REQ_MASK;
	tfm_ctx->fbk_cipher->base.crt_flags |= (aead->base.crt_flags &
					CRYPTO_TFM_REQ_MASK);

	वापस crypto_aead_setkey(tfm_ctx->fbk_cipher, key, keylen);
पूर्ण

अटल पूर्णांक zynqmp_aes_aead_setauthsize(काष्ठा crypto_aead *aead,
				       अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(aead);
	काष्ठा zynqmp_aead_tfm_ctx *tfm_ctx =
			(काष्ठा zynqmp_aead_tfm_ctx *)crypto_tfm_ctx(tfm);

	tfm_ctx->authsize = authsize;
	वापस crypto_aead_setauthsize(tfm_ctx->fbk_cipher, authsize);
पूर्ण

अटल पूर्णांक zynqmp_aes_aead_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा zynqmp_aead_drv_ctx *drv_ctx;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा aead_alg *alg = crypto_aead_alg(aead);
	काष्ठा zynqmp_aead_req_ctx *rq_ctx = aead_request_ctx(req);

	rq_ctx->op = ZYNQMP_AES_ENCRYPT;
	drv_ctx = container_of(alg, काष्ठा zynqmp_aead_drv_ctx, alg.aead);

	वापस crypto_transfer_aead_request_to_engine(drv_ctx->engine, req);
पूर्ण

अटल पूर्णांक zynqmp_aes_aead_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा zynqmp_aead_drv_ctx *drv_ctx;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा aead_alg *alg = crypto_aead_alg(aead);
	काष्ठा zynqmp_aead_req_ctx *rq_ctx = aead_request_ctx(req);

	rq_ctx->op = ZYNQMP_AES_DECRYPT;
	drv_ctx = container_of(alg, काष्ठा zynqmp_aead_drv_ctx, alg.aead);

	वापस crypto_transfer_aead_request_to_engine(drv_ctx->engine, req);
पूर्ण

अटल पूर्णांक zynqmp_aes_aead_init(काष्ठा crypto_aead *aead)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(aead);
	काष्ठा zynqmp_aead_tfm_ctx *tfm_ctx =
		(काष्ठा zynqmp_aead_tfm_ctx *)crypto_tfm_ctx(tfm);
	काष्ठा zynqmp_aead_drv_ctx *drv_ctx;
	काष्ठा aead_alg *alg = crypto_aead_alg(aead);

	drv_ctx = container_of(alg, काष्ठा zynqmp_aead_drv_ctx, alg.aead);
	tfm_ctx->dev = drv_ctx->dev;

	tfm_ctx->engine_ctx.op.करो_one_request = zynqmp_handle_aes_req;
	tfm_ctx->engine_ctx.op.prepare_request = शून्य;
	tfm_ctx->engine_ctx.op.unprepare_request = शून्य;

	tfm_ctx->fbk_cipher = crypto_alloc_aead(drv_ctx->alg.aead.base.cra_name,
						0,
						CRYPTO_ALG_NEED_FALLBACK);

	अगर (IS_ERR(tfm_ctx->fbk_cipher)) अणु
		pr_err("%s() Error: failed to allocate fallback for %s\n",
		       __func__, drv_ctx->alg.aead.base.cra_name);
		वापस PTR_ERR(tfm_ctx->fbk_cipher);
	पूर्ण

	crypto_aead_set_reqsize(aead,
				max(माप(काष्ठा zynqmp_aead_req_ctx),
				    माप(काष्ठा aead_request) +
				    crypto_aead_reqsize(tfm_ctx->fbk_cipher)));
	वापस 0;
पूर्ण

अटल व्योम zynqmp_aes_aead_निकास(काष्ठा crypto_aead *aead)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(aead);
	काष्ठा zynqmp_aead_tfm_ctx *tfm_ctx =
			(काष्ठा zynqmp_aead_tfm_ctx *)crypto_tfm_ctx(tfm);

	अगर (tfm_ctx->fbk_cipher) अणु
		crypto_मुक्त_aead(tfm_ctx->fbk_cipher);
		tfm_ctx->fbk_cipher = शून्य;
	पूर्ण
	memzero_explicit(tfm_ctx, माप(काष्ठा zynqmp_aead_tfm_ctx));
पूर्ण

अटल काष्ठा zynqmp_aead_drv_ctx aes_drv_ctx = अणु
	.alg.aead = अणु
		.setkey		= zynqmp_aes_aead_setkey,
		.setauthsize	= zynqmp_aes_aead_setauthsize,
		.encrypt	= zynqmp_aes_aead_encrypt,
		.decrypt	= zynqmp_aes_aead_decrypt,
		.init		= zynqmp_aes_aead_init,
		.निकास		= zynqmp_aes_aead_निकास,
		.ivsize		= GCM_AES_IV_SIZE,
		.maxauthsize	= ZYNQMP_AES_AUTH_SIZE,
		.base = अणु
		.cra_name		= "gcm(aes)",
		.cra_driver_name	= "xilinx-zynqmp-aes-gcm",
		.cra_priority		= 200,
		.cra_flags		= CRYPTO_ALG_TYPE_AEAD |
					  CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_ALLOCATES_MEMORY |
					  CRYPTO_ALG_KERN_DRIVER_ONLY |
					  CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= ZYNQMP_AES_BLK_SIZE,
		.cra_ctxsize		= माप(काष्ठा zynqmp_aead_tfm_ctx),
		.cra_module		= THIS_MODULE,
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक zynqmp_aes_aead_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक err;

	/* ZynqMP AES driver supports only one instance */
	अगर (!aes_drv_ctx.dev)
		aes_drv_ctx.dev = dev;
	अन्यथा
		वापस -ENODEV;

	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(ZYNQMP_DMA_BIT_MASK));
	अगर (err < 0) अणु
		dev_err(dev, "No usable DMA configuration\n");
		वापस err;
	पूर्ण

	aes_drv_ctx.engine = crypto_engine_alloc_init(dev, 1);
	अगर (!aes_drv_ctx.engine) अणु
		dev_err(dev, "Cannot alloc AES engine\n");
		err = -ENOMEM;
		जाओ err_engine;
	पूर्ण

	err = crypto_engine_start(aes_drv_ctx.engine);
	अगर (err) अणु
		dev_err(dev, "Cannot start AES engine\n");
		जाओ err_engine;
	पूर्ण

	err = crypto_रेजिस्टर_aead(&aes_drv_ctx.alg.aead);
	अगर (err < 0) अणु
		dev_err(dev, "Failed to register AEAD alg.\n");
		जाओ err_aead;
	पूर्ण
	वापस 0;

err_aead:
	crypto_unरेजिस्टर_aead(&aes_drv_ctx.alg.aead);

err_engine:
	अगर (aes_drv_ctx.engine)
		crypto_engine_निकास(aes_drv_ctx.engine);

	वापस err;
पूर्ण

अटल पूर्णांक zynqmp_aes_aead_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	crypto_engine_निकास(aes_drv_ctx.engine);
	crypto_unरेजिस्टर_aead(&aes_drv_ctx.alg.aead);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zynqmp_aes_dt_ids[] = अणु
	अणु .compatible = "xlnx,zynqmp-aes" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, zynqmp_aes_dt_ids);

अटल काष्ठा platक्रमm_driver zynqmp_aes_driver = अणु
	.probe	= zynqmp_aes_aead_probe,
	.हटाओ = zynqmp_aes_aead_हटाओ,
	.driver = अणु
		.name		= "zynqmp-aes",
		.of_match_table = zynqmp_aes_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(zynqmp_aes_driver);
MODULE_LICENSE("GPL");
