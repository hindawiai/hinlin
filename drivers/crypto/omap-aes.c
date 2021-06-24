<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cryptographic API.
 *
 * Support क्रम OMAP AES HW acceleration.
 *
 * Copyright (c) 2010 Nokia Corporation
 * Author: Dmitry Kasatkin <dmitry.kasatkin@nokia.com>
 * Copyright (c) 2011 Texas Instruments Incorporated
 */

#घोषणा pr_fmt(fmt) "%20s: " fmt, __func__
#घोषणा prn(num) pr_debug(#num "=%d\n", num)
#घोषणा prx(num) pr_debug(#num "=%x\n", num)

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>
#समावेश <linux/crypto.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/engine.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/पूर्णांकernal/aead.h>

#समावेश "omap-crypto.h"
#समावेश "omap-aes.h"

/* keep रेजिस्टरed devices data here */
अटल LIST_HEAD(dev_list);
अटल DEFINE_SPINLOCK(list_lock);

अटल पूर्णांक aes_fallback_sz = 200;

#अगर_घोषित DEBUG
#घोषणा omap_aes_पढ़ो(dd, offset)				\
(अणु								\
	पूर्णांक _पढ़ो_ret;						\
	_पढ़ो_ret = __raw_पढ़ोl(dd->io_base + offset);		\
	pr_debug("omap_aes_read(" #offset "=%#x)= %#x\n",	\
		 offset, _पढ़ो_ret);				\
	_पढ़ो_ret;						\
पूर्ण)
#अन्यथा
अंतरभूत u32 omap_aes_पढ़ो(काष्ठा omap_aes_dev *dd, u32 offset)
अणु
	वापस __raw_पढ़ोl(dd->io_base + offset);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित DEBUG
#घोषणा omap_aes_ग_लिखो(dd, offset, value)				\
	करो अणु								\
		pr_debug("omap_aes_write(" #offset "=%#x) value=%#x\n",	\
			 offset, value);				\
		__raw_ग_लिखोl(value, dd->io_base + offset);		\
	पूर्ण जबतक (0)
#अन्यथा
अंतरभूत व्योम omap_aes_ग_लिखो(काष्ठा omap_aes_dev *dd, u32 offset,
				  u32 value)
अणु
	__raw_ग_लिखोl(value, dd->io_base + offset);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम omap_aes_ग_लिखो_mask(काष्ठा omap_aes_dev *dd, u32 offset,
					u32 value, u32 mask)
अणु
	u32 val;

	val = omap_aes_पढ़ो(dd, offset);
	val &= ~mask;
	val |= value;
	omap_aes_ग_लिखो(dd, offset, val);
पूर्ण

अटल व्योम omap_aes_ग_लिखो_n(काष्ठा omap_aes_dev *dd, u32 offset,
					u32 *value, पूर्णांक count)
अणु
	क्रम (; count--; value++, offset += 4)
		omap_aes_ग_लिखो(dd, offset, *value);
पूर्ण

अटल पूर्णांक omap_aes_hw_init(काष्ठा omap_aes_dev *dd)
अणु
	पूर्णांक err;

	अगर (!(dd->flags & FLAGS_INIT)) अणु
		dd->flags |= FLAGS_INIT;
		dd->err = 0;
	पूर्ण

	err = pm_runसमय_resume_and_get(dd->dev);
	अगर (err < 0) अणु
		dev_err(dd->dev, "failed to get sync: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम omap_aes_clear_copy_flags(काष्ठा omap_aes_dev *dd)
अणु
	dd->flags &= ~(OMAP_CRYPTO_COPY_MASK << FLAGS_IN_DATA_ST_SHIFT);
	dd->flags &= ~(OMAP_CRYPTO_COPY_MASK << FLAGS_OUT_DATA_ST_SHIFT);
	dd->flags &= ~(OMAP_CRYPTO_COPY_MASK << FLAGS_ASSOC_DATA_ST_SHIFT);
पूर्ण

पूर्णांक omap_aes_ग_लिखो_ctrl(काष्ठा omap_aes_dev *dd)
अणु
	काष्ठा omap_aes_reqctx *rctx;
	अचिन्हित पूर्णांक key32;
	पूर्णांक i, err;
	u32 val;

	err = omap_aes_hw_init(dd);
	अगर (err)
		वापस err;

	key32 = dd->ctx->keylen / माप(u32);

	/* RESET the key as previous HASH keys should not get affected*/
	अगर (dd->flags & FLAGS_GCM)
		क्रम (i = 0; i < 0x40; i = i + 4)
			omap_aes_ग_लिखो(dd, i, 0x0);

	क्रम (i = 0; i < key32; i++) अणु
		omap_aes_ग_लिखो(dd, AES_REG_KEY(dd, i),
			       (__क्रमce u32)cpu_to_le32(dd->ctx->key[i]));
	पूर्ण

	अगर ((dd->flags & (FLAGS_CBC | FLAGS_CTR)) && dd->req->iv)
		omap_aes_ग_लिखो_n(dd, AES_REG_IV(dd, 0), (व्योम *)dd->req->iv, 4);

	अगर ((dd->flags & (FLAGS_GCM)) && dd->aead_req->iv) अणु
		rctx = aead_request_ctx(dd->aead_req);
		omap_aes_ग_लिखो_n(dd, AES_REG_IV(dd, 0), (u32 *)rctx->iv, 4);
	पूर्ण

	val = FLD_VAL(((dd->ctx->keylen >> 3) - 1), 4, 3);
	अगर (dd->flags & FLAGS_CBC)
		val |= AES_REG_CTRL_CBC;

	अगर (dd->flags & (FLAGS_CTR | FLAGS_GCM))
		val |= AES_REG_CTRL_CTR | AES_REG_CTRL_CTR_WIDTH_128;

	अगर (dd->flags & FLAGS_GCM)
		val |= AES_REG_CTRL_GCM;

	अगर (dd->flags & FLAGS_ENCRYPT)
		val |= AES_REG_CTRL_सूचीECTION;

	omap_aes_ग_लिखो_mask(dd, AES_REG_CTRL(dd), val, AES_REG_CTRL_MASK);

	वापस 0;
पूर्ण

अटल व्योम omap_aes_dma_trigger_omap2(काष्ठा omap_aes_dev *dd, पूर्णांक length)
अणु
	u32 mask, val;

	val = dd->pdata->dma_start;

	अगर (dd->dma_lch_out != शून्य)
		val |= dd->pdata->dma_enable_out;
	अगर (dd->dma_lch_in != शून्य)
		val |= dd->pdata->dma_enable_in;

	mask = dd->pdata->dma_enable_out | dd->pdata->dma_enable_in |
	       dd->pdata->dma_start;

	omap_aes_ग_लिखो_mask(dd, AES_REG_MASK(dd), val, mask);

पूर्ण

अटल व्योम omap_aes_dma_trigger_omap4(काष्ठा omap_aes_dev *dd, पूर्णांक length)
अणु
	omap_aes_ग_लिखो(dd, AES_REG_LENGTH_N(0), length);
	omap_aes_ग_लिखो(dd, AES_REG_LENGTH_N(1), 0);
	अगर (dd->flags & FLAGS_GCM)
		omap_aes_ग_लिखो(dd, AES_REG_A_LEN, dd->assoc_len);

	omap_aes_dma_trigger_omap2(dd, length);
पूर्ण

अटल व्योम omap_aes_dma_stop(काष्ठा omap_aes_dev *dd)
अणु
	u32 mask;

	mask = dd->pdata->dma_enable_out | dd->pdata->dma_enable_in |
	       dd->pdata->dma_start;

	omap_aes_ग_लिखो_mask(dd, AES_REG_MASK(dd), 0, mask);
पूर्ण

काष्ठा omap_aes_dev *omap_aes_find_dev(काष्ठा omap_aes_reqctx *rctx)
अणु
	काष्ठा omap_aes_dev *dd;

	spin_lock_bh(&list_lock);
	dd = list_first_entry(&dev_list, काष्ठा omap_aes_dev, list);
	list_move_tail(&dd->list, &dev_list);
	rctx->dd = dd;
	spin_unlock_bh(&list_lock);

	वापस dd;
पूर्ण

अटल व्योम omap_aes_dma_out_callback(व्योम *data)
अणु
	काष्ठा omap_aes_dev *dd = data;

	/* dma_lch_out - completed */
	tasklet_schedule(&dd->करोne_task);
पूर्ण

अटल पूर्णांक omap_aes_dma_init(काष्ठा omap_aes_dev *dd)
अणु
	पूर्णांक err;

	dd->dma_lch_out = शून्य;
	dd->dma_lch_in = शून्य;

	dd->dma_lch_in = dma_request_chan(dd->dev, "rx");
	अगर (IS_ERR(dd->dma_lch_in)) अणु
		dev_err(dd->dev, "Unable to request in DMA channel\n");
		वापस PTR_ERR(dd->dma_lch_in);
	पूर्ण

	dd->dma_lch_out = dma_request_chan(dd->dev, "tx");
	अगर (IS_ERR(dd->dma_lch_out)) अणु
		dev_err(dd->dev, "Unable to request out DMA channel\n");
		err = PTR_ERR(dd->dma_lch_out);
		जाओ err_dma_out;
	पूर्ण

	वापस 0;

err_dma_out:
	dma_release_channel(dd->dma_lch_in);

	वापस err;
पूर्ण

अटल व्योम omap_aes_dma_cleanup(काष्ठा omap_aes_dev *dd)
अणु
	अगर (dd->pio_only)
		वापस;

	dma_release_channel(dd->dma_lch_out);
	dma_release_channel(dd->dma_lch_in);
पूर्ण

अटल पूर्णांक omap_aes_crypt_dma(काष्ठा omap_aes_dev *dd,
			      काष्ठा scatterlist *in_sg,
			      काष्ठा scatterlist *out_sg,
			      पूर्णांक in_sg_len, पूर्णांक out_sg_len)
अणु
	काष्ठा dma_async_tx_descriptor *tx_in, *tx_out = शून्य, *cb_desc;
	काष्ठा dma_slave_config cfg;
	पूर्णांक ret;

	अगर (dd->pio_only) अणु
		scatterwalk_start(&dd->in_walk, dd->in_sg);
		अगर (out_sg_len)
			scatterwalk_start(&dd->out_walk, dd->out_sg);

		/* Enable DATAIN पूर्णांकerrupt and let it take
		   care of the rest */
		omap_aes_ग_लिखो(dd, AES_REG_IRQ_ENABLE(dd), 0x2);
		वापस 0;
	पूर्ण

	dma_sync_sg_क्रम_device(dd->dev, dd->in_sg, in_sg_len, DMA_TO_DEVICE);

	स_रखो(&cfg, 0, माप(cfg));

	cfg.src_addr = dd->phys_base + AES_REG_DATA_N(dd, 0);
	cfg.dst_addr = dd->phys_base + AES_REG_DATA_N(dd, 0);
	cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	cfg.src_maxburst = DST_MAXBURST;
	cfg.dst_maxburst = DST_MAXBURST;

	/* IN */
	ret = dmaengine_slave_config(dd->dma_lch_in, &cfg);
	अगर (ret) अणु
		dev_err(dd->dev, "can't configure IN dmaengine slave: %d\n",
			ret);
		वापस ret;
	पूर्ण

	tx_in = dmaengine_prep_slave_sg(dd->dma_lch_in, in_sg, in_sg_len,
					DMA_MEM_TO_DEV,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!tx_in) अणु
		dev_err(dd->dev, "IN prep_slave_sg() failed\n");
		वापस -EINVAL;
	पूर्ण

	/* No callback necessary */
	tx_in->callback_param = dd;
	tx_in->callback = शून्य;

	/* OUT */
	अगर (out_sg_len) अणु
		ret = dmaengine_slave_config(dd->dma_lch_out, &cfg);
		अगर (ret) अणु
			dev_err(dd->dev, "can't configure OUT dmaengine slave: %d\n",
				ret);
			वापस ret;
		पूर्ण

		tx_out = dmaengine_prep_slave_sg(dd->dma_lch_out, out_sg,
						 out_sg_len,
						 DMA_DEV_TO_MEM,
						 DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!tx_out) अणु
			dev_err(dd->dev, "OUT prep_slave_sg() failed\n");
			वापस -EINVAL;
		पूर्ण

		cb_desc = tx_out;
	पूर्ण अन्यथा अणु
		cb_desc = tx_in;
	पूर्ण

	अगर (dd->flags & FLAGS_GCM)
		cb_desc->callback = omap_aes_gcm_dma_out_callback;
	अन्यथा
		cb_desc->callback = omap_aes_dma_out_callback;
	cb_desc->callback_param = dd;


	dmaengine_submit(tx_in);
	अगर (tx_out)
		dmaengine_submit(tx_out);

	dma_async_issue_pending(dd->dma_lch_in);
	अगर (out_sg_len)
		dma_async_issue_pending(dd->dma_lch_out);

	/* start DMA */
	dd->pdata->trigger(dd, dd->total);

	वापस 0;
पूर्ण

पूर्णांक omap_aes_crypt_dma_start(काष्ठा omap_aes_dev *dd)
अणु
	पूर्णांक err;

	pr_debug("total: %zu\n", dd->total);

	अगर (!dd->pio_only) अणु
		err = dma_map_sg(dd->dev, dd->in_sg, dd->in_sg_len,
				 DMA_TO_DEVICE);
		अगर (!err) अणु
			dev_err(dd->dev, "dma_map_sg() error\n");
			वापस -EINVAL;
		पूर्ण

		अगर (dd->out_sg_len) अणु
			err = dma_map_sg(dd->dev, dd->out_sg, dd->out_sg_len,
					 DMA_FROM_DEVICE);
			अगर (!err) अणु
				dev_err(dd->dev, "dma_map_sg() error\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	err = omap_aes_crypt_dma(dd, dd->in_sg, dd->out_sg, dd->in_sg_len,
				 dd->out_sg_len);
	अगर (err && !dd->pio_only) अणु
		dma_unmap_sg(dd->dev, dd->in_sg, dd->in_sg_len, DMA_TO_DEVICE);
		अगर (dd->out_sg_len)
			dma_unmap_sg(dd->dev, dd->out_sg, dd->out_sg_len,
				     DMA_FROM_DEVICE);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम omap_aes_finish_req(काष्ठा omap_aes_dev *dd, पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = dd->req;

	pr_debug("err: %d\n", err);

	crypto_finalize_skcipher_request(dd->engine, req, err);

	pm_runसमय_mark_last_busy(dd->dev);
	pm_runसमय_put_स्वतःsuspend(dd->dev);
पूर्ण

पूर्णांक omap_aes_crypt_dma_stop(काष्ठा omap_aes_dev *dd)
अणु
	pr_debug("total: %zu\n", dd->total);

	omap_aes_dma_stop(dd);


	वापस 0;
पूर्ण

अटल पूर्णांक omap_aes_handle_queue(काष्ठा omap_aes_dev *dd,
				 काष्ठा skcipher_request *req)
अणु
	अगर (req)
		वापस crypto_transfer_skcipher_request_to_engine(dd->engine, req);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_aes_prepare_req(काष्ठा crypto_engine *engine,
				व्योम *areq)
अणु
	काष्ठा skcipher_request *req = container_of(areq, काष्ठा skcipher_request, base);
	काष्ठा omap_aes_ctx *ctx = crypto_skcipher_ctx(
			crypto_skcipher_reqtfm(req));
	काष्ठा omap_aes_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा omap_aes_dev *dd = rctx->dd;
	पूर्णांक ret;
	u16 flags;

	अगर (!dd)
		वापस -ENODEV;

	/* assign new request to device */
	dd->req = req;
	dd->total = req->cryptlen;
	dd->total_save = req->cryptlen;
	dd->in_sg = req->src;
	dd->out_sg = req->dst;
	dd->orig_out = req->dst;

	flags = OMAP_CRYPTO_COPY_DATA;
	अगर (req->src == req->dst)
		flags |= OMAP_CRYPTO_FORCE_COPY;

	ret = omap_crypto_align_sg(&dd->in_sg, dd->total, AES_BLOCK_SIZE,
				   dd->in_sgl, flags,
				   FLAGS_IN_DATA_ST_SHIFT, &dd->flags);
	अगर (ret)
		वापस ret;

	ret = omap_crypto_align_sg(&dd->out_sg, dd->total, AES_BLOCK_SIZE,
				   &dd->out_sgl, 0,
				   FLAGS_OUT_DATA_ST_SHIFT, &dd->flags);
	अगर (ret)
		वापस ret;

	dd->in_sg_len = sg_nents_क्रम_len(dd->in_sg, dd->total);
	अगर (dd->in_sg_len < 0)
		वापस dd->in_sg_len;

	dd->out_sg_len = sg_nents_क्रम_len(dd->out_sg, dd->total);
	अगर (dd->out_sg_len < 0)
		वापस dd->out_sg_len;

	rctx->mode &= FLAGS_MODE_MASK;
	dd->flags = (dd->flags & ~FLAGS_MODE_MASK) | rctx->mode;

	dd->ctx = ctx;
	rctx->dd = dd;

	वापस omap_aes_ग_लिखो_ctrl(dd);
पूर्ण

अटल पूर्णांक omap_aes_crypt_req(काष्ठा crypto_engine *engine,
			      व्योम *areq)
अणु
	काष्ठा skcipher_request *req = container_of(areq, काष्ठा skcipher_request, base);
	काष्ठा omap_aes_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा omap_aes_dev *dd = rctx->dd;

	अगर (!dd)
		वापस -ENODEV;

	वापस omap_aes_crypt_dma_start(dd);
पूर्ण

अटल व्योम omap_aes_copy_ivout(काष्ठा omap_aes_dev *dd, u8 *ivbuf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		((u32 *)ivbuf)[i] = omap_aes_पढ़ो(dd, AES_REG_IV(dd, i));
पूर्ण

अटल व्योम omap_aes_करोne_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा omap_aes_dev *dd = (काष्ठा omap_aes_dev *)data;

	pr_debug("enter done_task\n");

	अगर (!dd->pio_only) अणु
		dma_sync_sg_क्रम_device(dd->dev, dd->out_sg, dd->out_sg_len,
				       DMA_FROM_DEVICE);
		dma_unmap_sg(dd->dev, dd->in_sg, dd->in_sg_len, DMA_TO_DEVICE);
		dma_unmap_sg(dd->dev, dd->out_sg, dd->out_sg_len,
			     DMA_FROM_DEVICE);
		omap_aes_crypt_dma_stop(dd);
	पूर्ण

	omap_crypto_cleanup(dd->in_sg, शून्य, 0, dd->total_save,
			    FLAGS_IN_DATA_ST_SHIFT, dd->flags);

	omap_crypto_cleanup(dd->out_sg, dd->orig_out, 0, dd->total_save,
			    FLAGS_OUT_DATA_ST_SHIFT, dd->flags);

	/* Update IV output */
	अगर (dd->flags & (FLAGS_CBC | FLAGS_CTR))
		omap_aes_copy_ivout(dd, dd->req->iv);

	omap_aes_finish_req(dd, 0);

	pr_debug("exit\n");
पूर्ण

अटल पूर्णांक omap_aes_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ mode)
अणु
	काष्ठा omap_aes_ctx *ctx = crypto_skcipher_ctx(
			crypto_skcipher_reqtfm(req));
	काष्ठा omap_aes_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा omap_aes_dev *dd;
	पूर्णांक ret;

	अगर ((req->cryptlen % AES_BLOCK_SIZE) && !(mode & FLAGS_CTR))
		वापस -EINVAL;

	pr_debug("nbytes: %d, enc: %d, cbc: %d\n", req->cryptlen,
		  !!(mode & FLAGS_ENCRYPT),
		  !!(mode & FLAGS_CBC));

	अगर (req->cryptlen < aes_fallback_sz) अणु
		skcipher_request_set_tfm(&rctx->fallback_req, ctx->fallback);
		skcipher_request_set_callback(&rctx->fallback_req,
					      req->base.flags,
					      req->base.complete,
					      req->base.data);
		skcipher_request_set_crypt(&rctx->fallback_req, req->src,
					   req->dst, req->cryptlen, req->iv);

		अगर (mode & FLAGS_ENCRYPT)
			ret = crypto_skcipher_encrypt(&rctx->fallback_req);
		अन्यथा
			ret = crypto_skcipher_decrypt(&rctx->fallback_req);
		वापस ret;
	पूर्ण
	dd = omap_aes_find_dev(rctx);
	अगर (!dd)
		वापस -ENODEV;

	rctx->mode = mode;

	वापस omap_aes_handle_queue(dd, req);
पूर्ण

/* ********************** ALG API ************************************ */

अटल पूर्णांक omap_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा omap_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक ret;

	अगर (keylen != AES_KEYSIZE_128 && keylen != AES_KEYSIZE_192 &&
		   keylen != AES_KEYSIZE_256)
		वापस -EINVAL;

	pr_debug("enter, keylen: %d\n", keylen);

	स_नकल(ctx->key, key, keylen);
	ctx->keylen = keylen;

	crypto_skcipher_clear_flags(ctx->fallback, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(ctx->fallback, tfm->base.crt_flags &
						 CRYPTO_TFM_REQ_MASK);

	ret = crypto_skcipher_setkey(ctx->fallback, key, keylen);
	अगर (!ret)
		वापस 0;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_aes_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस omap_aes_crypt(req, FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक omap_aes_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस omap_aes_crypt(req, 0);
पूर्ण

अटल पूर्णांक omap_aes_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस omap_aes_crypt(req, FLAGS_ENCRYPT | FLAGS_CBC);
पूर्ण

अटल पूर्णांक omap_aes_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस omap_aes_crypt(req, FLAGS_CBC);
पूर्ण

अटल पूर्णांक omap_aes_ctr_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस omap_aes_crypt(req, FLAGS_ENCRYPT | FLAGS_CTR);
पूर्ण

अटल पूर्णांक omap_aes_ctr_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस omap_aes_crypt(req, FLAGS_CTR);
पूर्ण

अटल पूर्णांक omap_aes_prepare_req(काष्ठा crypto_engine *engine,
				व्योम *req);
अटल पूर्णांक omap_aes_crypt_req(काष्ठा crypto_engine *engine,
			      व्योम *req);

अटल पूर्णांक omap_aes_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	स्थिर अक्षर *name = crypto_tfm_alg_name(&tfm->base);
	काष्ठा omap_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *blk;

	blk = crypto_alloc_skcipher(name, 0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(blk))
		वापस PTR_ERR(blk);

	ctx->fallback = blk;

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा omap_aes_reqctx) +
					 crypto_skcipher_reqsize(blk));

	ctx->enginectx.op.prepare_request = omap_aes_prepare_req;
	ctx->enginectx.op.unprepare_request = शून्य;
	ctx->enginectx.op.करो_one_request = omap_aes_crypt_req;

	वापस 0;
पूर्ण

अटल व्योम omap_aes_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा omap_aes_ctx *ctx = crypto_skcipher_ctx(tfm);

	अगर (ctx->fallback)
		crypto_मुक्त_skcipher(ctx->fallback);

	ctx->fallback = शून्य;
पूर्ण

/* ********************** ALGS ************************************ */

अटल काष्ठा skcipher_alg algs_ecb_cbc[] = अणु
अणु
	.base.cra_name		= "ecb(aes)",
	.base.cra_driver_name	= "ecb-aes-omap",
	.base.cra_priority	= 300,
	.base.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_NEED_FALLBACK,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा omap_aes_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= omap_aes_setkey,
	.encrypt		= omap_aes_ecb_encrypt,
	.decrypt		= omap_aes_ecb_decrypt,
	.init			= omap_aes_init_tfm,
	.निकास			= omap_aes_निकास_tfm,
पूर्ण,
अणु
	.base.cra_name		= "cbc(aes)",
	.base.cra_driver_name	= "cbc-aes-omap",
	.base.cra_priority	= 300,
	.base.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_NEED_FALLBACK,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा omap_aes_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.setkey			= omap_aes_setkey,
	.encrypt		= omap_aes_cbc_encrypt,
	.decrypt		= omap_aes_cbc_decrypt,
	.init			= omap_aes_init_tfm,
	.निकास			= omap_aes_निकास_tfm,
पूर्ण
पूर्ण;

अटल काष्ठा skcipher_alg algs_ctr[] = अणु
अणु
	.base.cra_name		= "ctr(aes)",
	.base.cra_driver_name	= "ctr-aes-omap",
	.base.cra_priority	= 300,
	.base.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_NEED_FALLBACK,
	.base.cra_blocksize	= 1,
	.base.cra_ctxsize	= माप(काष्ठा omap_aes_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.setkey			= omap_aes_setkey,
	.encrypt		= omap_aes_ctr_encrypt,
	.decrypt		= omap_aes_ctr_decrypt,
	.init			= omap_aes_init_tfm,
	.निकास			= omap_aes_निकास_tfm,
पूर्ण
पूर्ण;

अटल काष्ठा omap_aes_algs_info omap_aes_algs_info_ecb_cbc[] = अणु
	अणु
		.algs_list	= algs_ecb_cbc,
		.size		= ARRAY_SIZE(algs_ecb_cbc),
	पूर्ण,
पूर्ण;

अटल काष्ठा aead_alg algs_aead_gcm[] = अणु
अणु
	.base = अणु
		.cra_name		= "gcm(aes)",
		.cra_driver_name	= "gcm-aes-omap",
		.cra_priority		= 300,
		.cra_flags		= CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_KERN_DRIVER_ONLY,
		.cra_blocksize		= 1,
		.cra_ctxsize		= माप(काष्ठा omap_aes_gcm_ctx),
		.cra_alignmask		= 0xf,
		.cra_module		= THIS_MODULE,
	पूर्ण,
	.init		= omap_aes_gcm_cra_init,
	.ivsize		= GCM_AES_IV_SIZE,
	.maxauthsize	= AES_BLOCK_SIZE,
	.setkey		= omap_aes_gcm_setkey,
	.setauthsize	= omap_aes_gcm_setauthsize,
	.encrypt	= omap_aes_gcm_encrypt,
	.decrypt	= omap_aes_gcm_decrypt,
पूर्ण,
अणु
	.base = अणु
		.cra_name		= "rfc4106(gcm(aes))",
		.cra_driver_name	= "rfc4106-gcm-aes-omap",
		.cra_priority		= 300,
		.cra_flags		= CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_KERN_DRIVER_ONLY,
		.cra_blocksize		= 1,
		.cra_ctxsize		= माप(काष्ठा omap_aes_gcm_ctx),
		.cra_alignmask		= 0xf,
		.cra_module		= THIS_MODULE,
	पूर्ण,
	.init		= omap_aes_gcm_cra_init,
	.maxauthsize	= AES_BLOCK_SIZE,
	.ivsize		= GCM_RFC4106_IV_SIZE,
	.setkey		= omap_aes_4106gcm_setkey,
	.setauthsize	= omap_aes_4106gcm_setauthsize,
	.encrypt	= omap_aes_4106gcm_encrypt,
	.decrypt	= omap_aes_4106gcm_decrypt,
पूर्ण,
पूर्ण;

अटल काष्ठा omap_aes_aead_algs omap_aes_aead_info = अणु
	.algs_list	=	algs_aead_gcm,
	.size		=	ARRAY_SIZE(algs_aead_gcm),
पूर्ण;

अटल स्थिर काष्ठा omap_aes_pdata omap_aes_pdata_omap2 = अणु
	.algs_info	= omap_aes_algs_info_ecb_cbc,
	.algs_info_size	= ARRAY_SIZE(omap_aes_algs_info_ecb_cbc),
	.trigger	= omap_aes_dma_trigger_omap2,
	.key_ofs	= 0x1c,
	.iv_ofs		= 0x20,
	.ctrl_ofs	= 0x30,
	.data_ofs	= 0x34,
	.rev_ofs	= 0x44,
	.mask_ofs	= 0x48,
	.dma_enable_in	= BIT(2),
	.dma_enable_out	= BIT(3),
	.dma_start	= BIT(5),
	.major_mask	= 0xf0,
	.major_shअगरt	= 4,
	.minor_mask	= 0x0f,
	.minor_shअगरt	= 0,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल काष्ठा omap_aes_algs_info omap_aes_algs_info_ecb_cbc_ctr[] = अणु
	अणु
		.algs_list	= algs_ecb_cbc,
		.size		= ARRAY_SIZE(algs_ecb_cbc),
	पूर्ण,
	अणु
		.algs_list	= algs_ctr,
		.size		= ARRAY_SIZE(algs_ctr),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_aes_pdata omap_aes_pdata_omap3 = अणु
	.algs_info	= omap_aes_algs_info_ecb_cbc_ctr,
	.algs_info_size	= ARRAY_SIZE(omap_aes_algs_info_ecb_cbc_ctr),
	.trigger	= omap_aes_dma_trigger_omap2,
	.key_ofs	= 0x1c,
	.iv_ofs		= 0x20,
	.ctrl_ofs	= 0x30,
	.data_ofs	= 0x34,
	.rev_ofs	= 0x44,
	.mask_ofs	= 0x48,
	.dma_enable_in	= BIT(2),
	.dma_enable_out	= BIT(3),
	.dma_start	= BIT(5),
	.major_mask	= 0xf0,
	.major_shअगरt	= 4,
	.minor_mask	= 0x0f,
	.minor_shअगरt	= 0,
पूर्ण;

अटल स्थिर काष्ठा omap_aes_pdata omap_aes_pdata_omap4 = अणु
	.algs_info	= omap_aes_algs_info_ecb_cbc_ctr,
	.algs_info_size	= ARRAY_SIZE(omap_aes_algs_info_ecb_cbc_ctr),
	.aead_algs_info	= &omap_aes_aead_info,
	.trigger	= omap_aes_dma_trigger_omap4,
	.key_ofs	= 0x3c,
	.iv_ofs		= 0x40,
	.ctrl_ofs	= 0x50,
	.data_ofs	= 0x60,
	.rev_ofs	= 0x80,
	.mask_ofs	= 0x84,
	.irq_status_ofs = 0x8c,
	.irq_enable_ofs = 0x90,
	.dma_enable_in	= BIT(5),
	.dma_enable_out	= BIT(6),
	.major_mask	= 0x0700,
	.major_shअगरt	= 8,
	.minor_mask	= 0x003f,
	.minor_shअगरt	= 0,
पूर्ण;

अटल irqवापस_t omap_aes_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा omap_aes_dev *dd = dev_id;
	u32 status, i;
	u32 *src, *dst;

	status = omap_aes_पढ़ो(dd, AES_REG_IRQ_STATUS(dd));
	अगर (status & AES_REG_IRQ_DATA_IN) अणु
		omap_aes_ग_लिखो(dd, AES_REG_IRQ_ENABLE(dd), 0x0);

		BUG_ON(!dd->in_sg);

		BUG_ON(_calc_walked(in) > dd->in_sg->length);

		src = sg_virt(dd->in_sg) + _calc_walked(in);

		क्रम (i = 0; i < AES_BLOCK_WORDS; i++) अणु
			omap_aes_ग_लिखो(dd, AES_REG_DATA_N(dd, i), *src);

			scatterwalk_advance(&dd->in_walk, 4);
			अगर (dd->in_sg->length == _calc_walked(in)) अणु
				dd->in_sg = sg_next(dd->in_sg);
				अगर (dd->in_sg) अणु
					scatterwalk_start(&dd->in_walk,
							  dd->in_sg);
					src = sg_virt(dd->in_sg) +
					      _calc_walked(in);
				पूर्ण
			पूर्ण अन्यथा अणु
				src++;
			पूर्ण
		पूर्ण

		/* Clear IRQ status */
		status &= ~AES_REG_IRQ_DATA_IN;
		omap_aes_ग_लिखो(dd, AES_REG_IRQ_STATUS(dd), status);

		/* Enable DATA_OUT पूर्णांकerrupt */
		omap_aes_ग_लिखो(dd, AES_REG_IRQ_ENABLE(dd), 0x4);

	पूर्ण अन्यथा अगर (status & AES_REG_IRQ_DATA_OUT) अणु
		omap_aes_ग_लिखो(dd, AES_REG_IRQ_ENABLE(dd), 0x0);

		BUG_ON(!dd->out_sg);

		BUG_ON(_calc_walked(out) > dd->out_sg->length);

		dst = sg_virt(dd->out_sg) + _calc_walked(out);

		क्रम (i = 0; i < AES_BLOCK_WORDS; i++) अणु
			*dst = omap_aes_पढ़ो(dd, AES_REG_DATA_N(dd, i));
			scatterwalk_advance(&dd->out_walk, 4);
			अगर (dd->out_sg->length == _calc_walked(out)) अणु
				dd->out_sg = sg_next(dd->out_sg);
				अगर (dd->out_sg) अणु
					scatterwalk_start(&dd->out_walk,
							  dd->out_sg);
					dst = sg_virt(dd->out_sg) +
					      _calc_walked(out);
				पूर्ण
			पूर्ण अन्यथा अणु
				dst++;
			पूर्ण
		पूर्ण

		dd->total -= min_t(माप_प्रकार, AES_BLOCK_SIZE, dd->total);

		/* Clear IRQ status */
		status &= ~AES_REG_IRQ_DATA_OUT;
		omap_aes_ग_लिखो(dd, AES_REG_IRQ_STATUS(dd), status);

		अगर (!dd->total)
			/* All bytes पढ़ो! */
			tasklet_schedule(&dd->करोne_task);
		अन्यथा
			/* Enable DATA_IN पूर्णांकerrupt क्रम next block */
			omap_aes_ग_लिखो(dd, AES_REG_IRQ_ENABLE(dd), 0x2);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा of_device_id omap_aes_of_match[] = अणु
	अणु
		.compatible	= "ti,omap2-aes",
		.data		= &omap_aes_pdata_omap2,
	पूर्ण,
	अणु
		.compatible	= "ti,omap3-aes",
		.data		= &omap_aes_pdata_omap3,
	पूर्ण,
	अणु
		.compatible	= "ti,omap4-aes",
		.data		= &omap_aes_pdata_omap4,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_aes_of_match);

अटल पूर्णांक omap_aes_get_res_of(काष्ठा omap_aes_dev *dd,
		काष्ठा device *dev, काष्ठा resource *res)
अणु
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक err = 0;

	dd->pdata = of_device_get_match_data(dev);
	अगर (!dd->pdata) अणु
		dev_err(dev, "no compatible OF match\n");
		err = -EINVAL;
		जाओ err;
	पूर्ण

	err = of_address_to_resource(node, 0, res);
	अगर (err < 0) अणु
		dev_err(dev, "can't translate OF node address\n");
		err = -EINVAL;
		जाओ err;
	पूर्ण

err:
	वापस err;
पूर्ण
#अन्यथा
अटल स्थिर काष्ठा of_device_id omap_aes_of_match[] = अणु
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक omap_aes_get_res_of(काष्ठा omap_aes_dev *dd,
		काष्ठा device *dev, काष्ठा resource *res)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक omap_aes_get_res_pdev(काष्ठा omap_aes_dev *dd,
		काष्ठा platक्रमm_device *pdev, काष्ठा resource *res)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *r;
	पूर्णांक err = 0;

	/* Get the base address */
	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(dev, "no MEM resource info\n");
		err = -ENODEV;
		जाओ err;
	पूर्ण
	स_नकल(res, r, माप(*res));

	/* Only OMAP2/3 can be non-DT */
	dd->pdata = &omap_aes_pdata_omap2;

err:
	वापस err;
पूर्ण

अटल sमाप_प्रकार fallback_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", aes_fallback_sz);
पूर्ण

अटल sमाप_प्रकार fallback_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	sमाप_प्रकार status;
	दीर्घ value;

	status = kम_से_दीर्घ(buf, 0, &value);
	अगर (status)
		वापस status;

	/* HW accelerator only works with buffers > 9 */
	अगर (value < 9) अणु
		dev_err(dev, "minimum fallback size 9\n");
		वापस -EINVAL;
	पूर्ण

	aes_fallback_sz = value;

	वापस size;
पूर्ण

अटल sमाप_प्रकार queue_len_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा omap_aes_dev *dd = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", dd->engine->queue.max_qlen);
पूर्ण

अटल sमाप_प्रकार queue_len_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार size)
अणु
	काष्ठा omap_aes_dev *dd;
	sमाप_प्रकार status;
	दीर्घ value;
	अचिन्हित दीर्घ flags;

	status = kम_से_दीर्घ(buf, 0, &value);
	अगर (status)
		वापस status;

	अगर (value < 1)
		वापस -EINVAL;

	/*
	 * Changing the queue size in fly is safe, अगर size becomes smaller
	 * than current size, it will just not accept new entries until
	 * it has shrank enough.
	 */
	spin_lock_bh(&list_lock);
	list_क्रम_each_entry(dd, &dev_list, list) अणु
		spin_lock_irqsave(&dd->lock, flags);
		dd->engine->queue.max_qlen = value;
		dd->aead_queue.base.max_qlen = value;
		spin_unlock_irqrestore(&dd->lock, flags);
	पूर्ण
	spin_unlock_bh(&list_lock);

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(queue_len);
अटल DEVICE_ATTR_RW(fallback);

अटल काष्ठा attribute *omap_aes_attrs[] = अणु
	&dev_attr_queue_len.attr,
	&dev_attr_fallback.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group omap_aes_attr_group = अणु
	.attrs = omap_aes_attrs,
पूर्ण;

अटल पूर्णांक omap_aes_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा omap_aes_dev *dd;
	काष्ठा skcipher_alg *algp;
	काष्ठा aead_alg *aalg;
	काष्ठा resource res;
	पूर्णांक err = -ENOMEM, i, j, irq = -1;
	u32 reg;

	dd = devm_kzalloc(dev, माप(काष्ठा omap_aes_dev), GFP_KERNEL);
	अगर (dd == शून्य) अणु
		dev_err(dev, "unable to alloc data struct.\n");
		जाओ err_data;
	पूर्ण
	dd->dev = dev;
	platक्रमm_set_drvdata(pdev, dd);

	aead_init_queue(&dd->aead_queue, OMAP_AES_QUEUE_LENGTH);

	err = (dev->of_node) ? omap_aes_get_res_of(dd, dev, &res) :
			       omap_aes_get_res_pdev(dd, pdev, &res);
	अगर (err)
		जाओ err_res;

	dd->io_base = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(dd->io_base)) अणु
		err = PTR_ERR(dd->io_base);
		जाओ err_res;
	पूर्ण
	dd->phys_base = res.start;

	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, DEFAULT_AUTOSUSPEND_DELAY);

	pm_runसमय_enable(dev);
	err = pm_runसमय_resume_and_get(dev);
	अगर (err < 0) अणु
		dev_err(dev, "%s: failed to get_sync(%d)\n",
			__func__, err);
		जाओ err_pm_disable;
	पूर्ण

	omap_aes_dma_stop(dd);

	reg = omap_aes_पढ़ो(dd, AES_REG_REV(dd));

	pm_runसमय_put_sync(dev);

	dev_info(dev, "OMAP AES hw accel rev: %u.%u\n",
		 (reg & dd->pdata->major_mask) >> dd->pdata->major_shअगरt,
		 (reg & dd->pdata->minor_mask) >> dd->pdata->minor_shअगरt);

	tasklet_init(&dd->करोne_task, omap_aes_करोne_task, (अचिन्हित दीर्घ)dd);

	err = omap_aes_dma_init(dd);
	अगर (err == -EPROBE_DEFER) अणु
		जाओ err_irq;
	पूर्ण अन्यथा अगर (err && AES_REG_IRQ_STATUS(dd) && AES_REG_IRQ_ENABLE(dd)) अणु
		dd->pio_only = 1;

		irq = platक्रमm_get_irq(pdev, 0);
		अगर (irq < 0) अणु
			err = irq;
			जाओ err_irq;
		पूर्ण

		err = devm_request_irq(dev, irq, omap_aes_irq, 0,
				dev_name(dev), dd);
		अगर (err) अणु
			dev_err(dev, "Unable to grab omap-aes IRQ\n");
			जाओ err_irq;
		पूर्ण
	पूर्ण

	spin_lock_init(&dd->lock);

	INIT_LIST_HEAD(&dd->list);
	spin_lock(&list_lock);
	list_add_tail(&dd->list, &dev_list);
	spin_unlock(&list_lock);

	/* Initialize crypto engine */
	dd->engine = crypto_engine_alloc_init(dev, 1);
	अगर (!dd->engine) अणु
		err = -ENOMEM;
		जाओ err_engine;
	पूर्ण

	err = crypto_engine_start(dd->engine);
	अगर (err)
		जाओ err_engine;

	क्रम (i = 0; i < dd->pdata->algs_info_size; i++) अणु
		अगर (!dd->pdata->algs_info[i].रेजिस्टरed) अणु
			क्रम (j = 0; j < dd->pdata->algs_info[i].size; j++) अणु
				algp = &dd->pdata->algs_info[i].algs_list[j];

				pr_debug("reg alg: %s\n", algp->base.cra_name);

				err = crypto_रेजिस्टर_skcipher(algp);
				अगर (err)
					जाओ err_algs;

				dd->pdata->algs_info[i].रेजिस्टरed++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (dd->pdata->aead_algs_info &&
	    !dd->pdata->aead_algs_info->रेजिस्टरed) अणु
		क्रम (i = 0; i < dd->pdata->aead_algs_info->size; i++) अणु
			aalg = &dd->pdata->aead_algs_info->algs_list[i];

			pr_debug("reg alg: %s\n", aalg->base.cra_name);

			err = crypto_रेजिस्टर_aead(aalg);
			अगर (err)
				जाओ err_aead_algs;

			dd->pdata->aead_algs_info->रेजिस्टरed++;
		पूर्ण
	पूर्ण

	err = sysfs_create_group(&dev->kobj, &omap_aes_attr_group);
	अगर (err) अणु
		dev_err(dev, "could not create sysfs device attrs\n");
		जाओ err_aead_algs;
	पूर्ण

	वापस 0;
err_aead_algs:
	क्रम (i = dd->pdata->aead_algs_info->रेजिस्टरed - 1; i >= 0; i--) अणु
		aalg = &dd->pdata->aead_algs_info->algs_list[i];
		crypto_unरेजिस्टर_aead(aalg);
	पूर्ण
err_algs:
	क्रम (i = dd->pdata->algs_info_size - 1; i >= 0; i--)
		क्रम (j = dd->pdata->algs_info[i].रेजिस्टरed - 1; j >= 0; j--)
			crypto_unरेजिस्टर_skcipher(
					&dd->pdata->algs_info[i].algs_list[j]);

err_engine:
	अगर (dd->engine)
		crypto_engine_निकास(dd->engine);

	omap_aes_dma_cleanup(dd);
err_irq:
	tasklet_समाप्त(&dd->करोne_task);
err_pm_disable:
	pm_runसमय_disable(dev);
err_res:
	dd = शून्य;
err_data:
	dev_err(dev, "initialization failed.\n");
	वापस err;
पूर्ण

अटल पूर्णांक omap_aes_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_aes_dev *dd = platक्रमm_get_drvdata(pdev);
	काष्ठा aead_alg *aalg;
	पूर्णांक i, j;

	अगर (!dd)
		वापस -ENODEV;

	spin_lock(&list_lock);
	list_del(&dd->list);
	spin_unlock(&list_lock);

	क्रम (i = dd->pdata->algs_info_size - 1; i >= 0; i--)
		क्रम (j = dd->pdata->algs_info[i].रेजिस्टरed - 1; j >= 0; j--) अणु
			crypto_unरेजिस्टर_skcipher(
					&dd->pdata->algs_info[i].algs_list[j]);
			dd->pdata->algs_info[i].रेजिस्टरed--;
		पूर्ण

	क्रम (i = dd->pdata->aead_algs_info->रेजिस्टरed - 1; i >= 0; i--) अणु
		aalg = &dd->pdata->aead_algs_info->algs_list[i];
		crypto_unरेजिस्टर_aead(aalg);
		dd->pdata->aead_algs_info->रेजिस्टरed--;

	पूर्ण

	crypto_engine_निकास(dd->engine);

	tasklet_समाप्त(&dd->करोne_task);
	omap_aes_dma_cleanup(dd);
	pm_runसमय_disable(dd->dev);

	sysfs_हटाओ_group(&dd->dev->kobj, &omap_aes_attr_group);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक omap_aes_suspend(काष्ठा device *dev)
अणु
	pm_runसमय_put_sync(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_aes_resume(काष्ठा device *dev)
अणु
	pm_runसमय_resume_and_get(dev);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(omap_aes_pm_ops, omap_aes_suspend, omap_aes_resume);

अटल काष्ठा platक्रमm_driver omap_aes_driver = अणु
	.probe	= omap_aes_probe,
	.हटाओ	= omap_aes_हटाओ,
	.driver	= अणु
		.name	= "omap-aes",
		.pm	= &omap_aes_pm_ops,
		.of_match_table	= omap_aes_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omap_aes_driver);

MODULE_DESCRIPTION("OMAP AES hw acceleration support.");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Dmitry Kasatkin");

