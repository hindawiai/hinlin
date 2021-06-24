<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Crypto acceleration support क्रम Rockchip RK3288
 *
 * Copyright (c) 2015, Fuzhou Rockchip Electronics Co., Ltd
 *
 * Author: Zain Wang <zain.wang@rock-chips.com>
 *
 * Some ideas are from marvell-cesa.c and s5p-sss.c driver.
 */
#समावेश <linux/device.h>
#समावेश "rk3288_crypto.h"

#घोषणा RK_CRYPTO_DEC			BIT(0)

अटल व्योम rk_crypto_complete(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	अगर (base->complete)
		base->complete(base, err);
पूर्ण

अटल पूर्णांक rk_handle_req(काष्ठा rk_crypto_info *dev,
			 काष्ठा skcipher_request *req)
अणु
	अगर (!IS_ALIGNED(req->cryptlen, dev->align_size))
		वापस -EINVAL;
	अन्यथा
		वापस dev->enqueue(dev, &req->base);
पूर्ण

अटल पूर्णांक rk_aes_setkey(काष्ठा crypto_skcipher *cipher,
			 स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(cipher);
	काष्ठा rk_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	अगर (keylen != AES_KEYSIZE_128 && keylen != AES_KEYSIZE_192 &&
	    keylen != AES_KEYSIZE_256)
		वापस -EINVAL;
	ctx->keylen = keylen;
	स_नकल_toio(ctx->dev->reg + RK_CRYPTO_AES_KEY_0, key, keylen);
	वापस 0;
पूर्ण

अटल पूर्णांक rk_des_setkey(काष्ठा crypto_skcipher *cipher,
			 स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(cipher);
	पूर्णांक err;

	err = verअगरy_skcipher_des_key(cipher, key);
	अगर (err)
		वापस err;

	ctx->keylen = keylen;
	स_नकल_toio(ctx->dev->reg + RK_CRYPTO_TDES_KEY1_0, key, keylen);
	वापस 0;
पूर्ण

अटल पूर्णांक rk_tdes_setkey(काष्ठा crypto_skcipher *cipher,
			  स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(cipher);
	पूर्णांक err;

	err = verअगरy_skcipher_des3_key(cipher, key);
	अगर (err)
		वापस err;

	ctx->keylen = keylen;
	स_नकल_toio(ctx->dev->reg + RK_CRYPTO_TDES_KEY1_0, key, keylen);
	वापस 0;
पूर्ण

अटल पूर्णांक rk_aes_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा rk_crypto_info *dev = ctx->dev;

	ctx->mode = RK_CRYPTO_AES_ECB_MODE;
	वापस rk_handle_req(dev, req);
पूर्ण

अटल पूर्णांक rk_aes_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा rk_crypto_info *dev = ctx->dev;

	ctx->mode = RK_CRYPTO_AES_ECB_MODE | RK_CRYPTO_DEC;
	वापस rk_handle_req(dev, req);
पूर्ण

अटल पूर्णांक rk_aes_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा rk_crypto_info *dev = ctx->dev;

	ctx->mode = RK_CRYPTO_AES_CBC_MODE;
	वापस rk_handle_req(dev, req);
पूर्ण

अटल पूर्णांक rk_aes_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा rk_crypto_info *dev = ctx->dev;

	ctx->mode = RK_CRYPTO_AES_CBC_MODE | RK_CRYPTO_DEC;
	वापस rk_handle_req(dev, req);
पूर्ण

अटल पूर्णांक rk_des_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा rk_crypto_info *dev = ctx->dev;

	ctx->mode = 0;
	वापस rk_handle_req(dev, req);
पूर्ण

अटल पूर्णांक rk_des_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा rk_crypto_info *dev = ctx->dev;

	ctx->mode = RK_CRYPTO_DEC;
	वापस rk_handle_req(dev, req);
पूर्ण

अटल पूर्णांक rk_des_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा rk_crypto_info *dev = ctx->dev;

	ctx->mode = RK_CRYPTO_TDES_CHAINMODE_CBC;
	वापस rk_handle_req(dev, req);
पूर्ण

अटल पूर्णांक rk_des_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा rk_crypto_info *dev = ctx->dev;

	ctx->mode = RK_CRYPTO_TDES_CHAINMODE_CBC | RK_CRYPTO_DEC;
	वापस rk_handle_req(dev, req);
पूर्ण

अटल पूर्णांक rk_des3_ede_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा rk_crypto_info *dev = ctx->dev;

	ctx->mode = RK_CRYPTO_TDES_SELECT;
	वापस rk_handle_req(dev, req);
पूर्ण

अटल पूर्णांक rk_des3_ede_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा rk_crypto_info *dev = ctx->dev;

	ctx->mode = RK_CRYPTO_TDES_SELECT | RK_CRYPTO_DEC;
	वापस rk_handle_req(dev, req);
पूर्ण

अटल पूर्णांक rk_des3_ede_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा rk_crypto_info *dev = ctx->dev;

	ctx->mode = RK_CRYPTO_TDES_SELECT | RK_CRYPTO_TDES_CHAINMODE_CBC;
	वापस rk_handle_req(dev, req);
पूर्ण

अटल पूर्णांक rk_des3_ede_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा rk_crypto_info *dev = ctx->dev;

	ctx->mode = RK_CRYPTO_TDES_SELECT | RK_CRYPTO_TDES_CHAINMODE_CBC |
		    RK_CRYPTO_DEC;
	वापस rk_handle_req(dev, req);
पूर्ण

अटल व्योम rk_ablk_hw_init(काष्ठा rk_crypto_info *dev)
अणु
	काष्ठा skcipher_request *req =
		skcipher_request_cast(dev->async_req);
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(cipher);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(cipher);
	u32 ivsize, block, conf_reg = 0;

	block = crypto_tfm_alg_blocksize(tfm);
	ivsize = crypto_skcipher_ivsize(cipher);

	अगर (block == DES_BLOCK_SIZE) अणु
		ctx->mode |= RK_CRYPTO_TDES_FIFO_MODE |
			     RK_CRYPTO_TDES_BYTESWAP_KEY |
			     RK_CRYPTO_TDES_BYTESWAP_IV;
		CRYPTO_WRITE(dev, RK_CRYPTO_TDES_CTRL, ctx->mode);
		स_नकल_toio(dev->reg + RK_CRYPTO_TDES_IV_0, req->iv, ivsize);
		conf_reg = RK_CRYPTO_DESSEL;
	पूर्ण अन्यथा अणु
		ctx->mode |= RK_CRYPTO_AES_FIFO_MODE |
			     RK_CRYPTO_AES_KEY_CHANGE |
			     RK_CRYPTO_AES_BYTESWAP_KEY |
			     RK_CRYPTO_AES_BYTESWAP_IV;
		अगर (ctx->keylen == AES_KEYSIZE_192)
			ctx->mode |= RK_CRYPTO_AES_192BIT_key;
		अन्यथा अगर (ctx->keylen == AES_KEYSIZE_256)
			ctx->mode |= RK_CRYPTO_AES_256BIT_key;
		CRYPTO_WRITE(dev, RK_CRYPTO_AES_CTRL, ctx->mode);
		स_नकल_toio(dev->reg + RK_CRYPTO_AES_IV_0, req->iv, ivsize);
	पूर्ण
	conf_reg |= RK_CRYPTO_BYTESWAP_BTFIFO |
		    RK_CRYPTO_BYTESWAP_BRFIFO;
	CRYPTO_WRITE(dev, RK_CRYPTO_CONF, conf_reg);
	CRYPTO_WRITE(dev, RK_CRYPTO_INTENA,
		     RK_CRYPTO_BCDMA_ERR_ENA | RK_CRYPTO_BCDMA_DONE_ENA);
पूर्ण

अटल व्योम crypto_dma_start(काष्ठा rk_crypto_info *dev)
अणु
	CRYPTO_WRITE(dev, RK_CRYPTO_BRDMAS, dev->addr_in);
	CRYPTO_WRITE(dev, RK_CRYPTO_BRDMAL, dev->count / 4);
	CRYPTO_WRITE(dev, RK_CRYPTO_BTDMAS, dev->addr_out);
	CRYPTO_WRITE(dev, RK_CRYPTO_CTRL, RK_CRYPTO_BLOCK_START |
		     _SBF(RK_CRYPTO_BLOCK_START, 16));
पूर्ण

अटल पूर्णांक rk_set_data_start(काष्ठा rk_crypto_info *dev)
अणु
	पूर्णांक err;
	काष्ठा skcipher_request *req =
		skcipher_request_cast(dev->async_req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	u32 ivsize = crypto_skcipher_ivsize(tfm);
	u8 *src_last_blk = page_address(sg_page(dev->sg_src)) +
		dev->sg_src->offset + dev->sg_src->length - ivsize;

	/* Store the iv that need to be updated in chain mode.
	 * And update the IV buffer to contain the next IV क्रम decryption mode.
	 */
	अगर (ctx->mode & RK_CRYPTO_DEC) अणु
		स_नकल(ctx->iv, src_last_blk, ivsize);
		sg_pcopy_to_buffer(dev->first, dev->src_nents, req->iv,
				   ivsize, dev->total - ivsize);
	पूर्ण

	err = dev->load_data(dev, dev->sg_src, dev->sg_dst);
	अगर (!err)
		crypto_dma_start(dev);
	वापस err;
पूर्ण

अटल पूर्णांक rk_ablk_start(काष्ठा rk_crypto_info *dev)
अणु
	काष्ठा skcipher_request *req =
		skcipher_request_cast(dev->async_req);
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	dev->left_bytes = req->cryptlen;
	dev->total = req->cryptlen;
	dev->sg_src = req->src;
	dev->first = req->src;
	dev->src_nents = sg_nents(req->src);
	dev->sg_dst = req->dst;
	dev->dst_nents = sg_nents(req->dst);
	dev->aligned = 1;

	spin_lock_irqsave(&dev->lock, flags);
	rk_ablk_hw_init(dev);
	err = rk_set_data_start(dev);
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस err;
पूर्ण

अटल व्योम rk_iv_copyback(काष्ठा rk_crypto_info *dev)
अणु
	काष्ठा skcipher_request *req =
		skcipher_request_cast(dev->async_req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	u32 ivsize = crypto_skcipher_ivsize(tfm);

	/* Update the IV buffer to contain the next IV क्रम encryption mode. */
	अगर (!(ctx->mode & RK_CRYPTO_DEC)) अणु
		अगर (dev->aligned) अणु
			स_नकल(req->iv, sg_virt(dev->sg_dst) +
				dev->sg_dst->length - ivsize, ivsize);
		पूर्ण अन्यथा अणु
			स_नकल(req->iv, dev->addr_vir +
				dev->count - ivsize, ivsize);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rk_update_iv(काष्ठा rk_crypto_info *dev)
अणु
	काष्ठा skcipher_request *req =
		skcipher_request_cast(dev->async_req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	u32 ivsize = crypto_skcipher_ivsize(tfm);
	u8 *new_iv = शून्य;

	अगर (ctx->mode & RK_CRYPTO_DEC) अणु
		new_iv = ctx->iv;
	पूर्ण अन्यथा अणु
		new_iv = page_address(sg_page(dev->sg_dst)) +
			 dev->sg_dst->offset + dev->sg_dst->length - ivsize;
	पूर्ण

	अगर (ivsize == DES_BLOCK_SIZE)
		स_नकल_toio(dev->reg + RK_CRYPTO_TDES_IV_0, new_iv, ivsize);
	अन्यथा अगर (ivsize == AES_BLOCK_SIZE)
		स_नकल_toio(dev->reg + RK_CRYPTO_AES_IV_0, new_iv, ivsize);
पूर्ण

/* वापस:
 *	true	some err was occurred
 *	fault	no err, जारी
 */
अटल पूर्णांक rk_ablk_rx(काष्ठा rk_crypto_info *dev)
अणु
	पूर्णांक err = 0;
	काष्ठा skcipher_request *req =
		skcipher_request_cast(dev->async_req);

	dev->unload_data(dev);
	अगर (!dev->aligned) अणु
		अगर (!sg_pcopy_from_buffer(req->dst, dev->dst_nents,
					  dev->addr_vir, dev->count,
					  dev->total - dev->left_bytes -
					  dev->count)) अणु
			err = -EINVAL;
			जाओ out_rx;
		पूर्ण
	पूर्ण
	अगर (dev->left_bytes) अणु
		rk_update_iv(dev);
		अगर (dev->aligned) अणु
			अगर (sg_is_last(dev->sg_src)) अणु
				dev_err(dev->dev, "[%s:%d] Lack of data\n",
					__func__, __LINE__);
				err = -ENOMEM;
				जाओ out_rx;
			पूर्ण
			dev->sg_src = sg_next(dev->sg_src);
			dev->sg_dst = sg_next(dev->sg_dst);
		पूर्ण
		err = rk_set_data_start(dev);
	पूर्ण अन्यथा अणु
		rk_iv_copyback(dev);
		/* here show the calculation is over without any err */
		dev->complete(dev->async_req, 0);
		tasklet_schedule(&dev->queue_task);
	पूर्ण
out_rx:
	वापस err;
पूर्ण

अटल पूर्णांक rk_ablk_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा rk_crypto_पंचांगp *algt;

	algt = container_of(alg, काष्ठा rk_crypto_पंचांगp, alg.skcipher);

	ctx->dev = algt->dev;
	ctx->dev->align_size = crypto_tfm_alg_alignmask(crypto_skcipher_tfm(tfm)) + 1;
	ctx->dev->start = rk_ablk_start;
	ctx->dev->update = rk_ablk_rx;
	ctx->dev->complete = rk_crypto_complete;
	ctx->dev->addr_vir = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);

	वापस ctx->dev->addr_vir ? ctx->dev->enable_clk(ctx->dev) : -ENOMEM;
पूर्ण

अटल व्योम rk_ablk_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा rk_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);

	मुक्त_page((अचिन्हित दीर्घ)ctx->dev->addr_vir);
	ctx->dev->disable_clk(ctx->dev);
पूर्ण

काष्ठा rk_crypto_पंचांगp rk_ecb_aes_alg = अणु
	.type = ALG_TYPE_CIPHER,
	.alg.skcipher = अणु
		.base.cra_name		= "ecb(aes)",
		.base.cra_driver_name	= "ecb-aes-rk",
		.base.cra_priority	= 300,
		.base.cra_flags		= CRYPTO_ALG_ASYNC,
		.base.cra_blocksize	= AES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा rk_cipher_ctx),
		.base.cra_alignmask	= 0x0f,
		.base.cra_module	= THIS_MODULE,

		.init			= rk_ablk_init_tfm,
		.निकास			= rk_ablk_निकास_tfm,
		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.setkey			= rk_aes_setkey,
		.encrypt		= rk_aes_ecb_encrypt,
		.decrypt		= rk_aes_ecb_decrypt,
	पूर्ण
पूर्ण;

काष्ठा rk_crypto_पंचांगp rk_cbc_aes_alg = अणु
	.type = ALG_TYPE_CIPHER,
	.alg.skcipher = अणु
		.base.cra_name		= "cbc(aes)",
		.base.cra_driver_name	= "cbc-aes-rk",
		.base.cra_priority	= 300,
		.base.cra_flags		= CRYPTO_ALG_ASYNC,
		.base.cra_blocksize	= AES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा rk_cipher_ctx),
		.base.cra_alignmask	= 0x0f,
		.base.cra_module	= THIS_MODULE,

		.init			= rk_ablk_init_tfm,
		.निकास			= rk_ablk_निकास_tfm,
		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BLOCK_SIZE,
		.setkey			= rk_aes_setkey,
		.encrypt		= rk_aes_cbc_encrypt,
		.decrypt		= rk_aes_cbc_decrypt,
	पूर्ण
पूर्ण;

काष्ठा rk_crypto_पंचांगp rk_ecb_des_alg = अणु
	.type = ALG_TYPE_CIPHER,
	.alg.skcipher = अणु
		.base.cra_name		= "ecb(des)",
		.base.cra_driver_name	= "ecb-des-rk",
		.base.cra_priority	= 300,
		.base.cra_flags		= CRYPTO_ALG_ASYNC,
		.base.cra_blocksize	= DES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा rk_cipher_ctx),
		.base.cra_alignmask	= 0x07,
		.base.cra_module	= THIS_MODULE,

		.init			= rk_ablk_init_tfm,
		.निकास			= rk_ablk_निकास_tfm,
		.min_keysize		= DES_KEY_SIZE,
		.max_keysize		= DES_KEY_SIZE,
		.setkey			= rk_des_setkey,
		.encrypt		= rk_des_ecb_encrypt,
		.decrypt		= rk_des_ecb_decrypt,
	पूर्ण
पूर्ण;

काष्ठा rk_crypto_पंचांगp rk_cbc_des_alg = अणु
	.type = ALG_TYPE_CIPHER,
	.alg.skcipher = अणु
		.base.cra_name		= "cbc(des)",
		.base.cra_driver_name	= "cbc-des-rk",
		.base.cra_priority	= 300,
		.base.cra_flags		= CRYPTO_ALG_ASYNC,
		.base.cra_blocksize	= DES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा rk_cipher_ctx),
		.base.cra_alignmask	= 0x07,
		.base.cra_module	= THIS_MODULE,

		.init			= rk_ablk_init_tfm,
		.निकास			= rk_ablk_निकास_tfm,
		.min_keysize		= DES_KEY_SIZE,
		.max_keysize		= DES_KEY_SIZE,
		.ivsize			= DES_BLOCK_SIZE,
		.setkey			= rk_des_setkey,
		.encrypt		= rk_des_cbc_encrypt,
		.decrypt		= rk_des_cbc_decrypt,
	पूर्ण
पूर्ण;

काष्ठा rk_crypto_पंचांगp rk_ecb_des3_ede_alg = अणु
	.type = ALG_TYPE_CIPHER,
	.alg.skcipher = अणु
		.base.cra_name		= "ecb(des3_ede)",
		.base.cra_driver_name	= "ecb-des3-ede-rk",
		.base.cra_priority	= 300,
		.base.cra_flags		= CRYPTO_ALG_ASYNC,
		.base.cra_blocksize	= DES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा rk_cipher_ctx),
		.base.cra_alignmask	= 0x07,
		.base.cra_module	= THIS_MODULE,

		.init			= rk_ablk_init_tfm,
		.निकास			= rk_ablk_निकास_tfm,
		.min_keysize		= DES3_EDE_KEY_SIZE,
		.max_keysize		= DES3_EDE_KEY_SIZE,
		.ivsize			= DES_BLOCK_SIZE,
		.setkey			= rk_tdes_setkey,
		.encrypt		= rk_des3_ede_ecb_encrypt,
		.decrypt		= rk_des3_ede_ecb_decrypt,
	पूर्ण
पूर्ण;

काष्ठा rk_crypto_पंचांगp rk_cbc_des3_ede_alg = अणु
	.type = ALG_TYPE_CIPHER,
	.alg.skcipher = अणु
		.base.cra_name		= "cbc(des3_ede)",
		.base.cra_driver_name	= "cbc-des3-ede-rk",
		.base.cra_priority	= 300,
		.base.cra_flags		= CRYPTO_ALG_ASYNC,
		.base.cra_blocksize	= DES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा rk_cipher_ctx),
		.base.cra_alignmask	= 0x07,
		.base.cra_module	= THIS_MODULE,

		.init			= rk_ablk_init_tfm,
		.निकास			= rk_ablk_निकास_tfm,
		.min_keysize		= DES3_EDE_KEY_SIZE,
		.max_keysize		= DES3_EDE_KEY_SIZE,
		.ivsize			= DES_BLOCK_SIZE,
		.setkey			= rk_tdes_setkey,
		.encrypt		= rk_des3_ede_cbc_encrypt,
		.decrypt		= rk_des3_ede_cbc_decrypt,
	पूर्ण
पूर्ण;
