<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम OMAP DES and Triple DES HW acceleration.
 *
 * Copyright (c) 2013 Texas Instruments Incorporated
 * Author: Joel Fernandes <joelf@ti.com>
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#अगर_घोषित DEBUG
#घोषणा prn(num) prपूर्णांकk(#num "=%d\n", num)
#घोषणा prx(num) prपूर्णांकk(#num "=%x\n", num)
#अन्यथा
#घोषणा prn(num) करो अणु पूर्ण जबतक (0)
#घोषणा prx(num)  करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

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
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/engine.h>

#समावेश "omap-crypto.h"

#घोषणा DST_MAXBURST			2

#घोषणा DES_BLOCK_WORDS		(DES_BLOCK_SIZE >> 2)

#घोषणा _calc_walked(inout) (dd->inout##_walk.offset - dd->inout##_sg->offset)

#घोषणा DES_REG_KEY(dd, x)		((dd)->pdata->key_ofs - \
						((x ^ 0x01) * 0x04))

#घोषणा DES_REG_IV(dd, x)		((dd)->pdata->iv_ofs + ((x) * 0x04))

#घोषणा DES_REG_CTRL(dd)		((dd)->pdata->ctrl_ofs)
#घोषणा DES_REG_CTRL_CBC		BIT(4)
#घोषणा DES_REG_CTRL_TDES		BIT(3)
#घोषणा DES_REG_CTRL_सूचीECTION		BIT(2)
#घोषणा DES_REG_CTRL_INPUT_READY	BIT(1)
#घोषणा DES_REG_CTRL_OUTPUT_READY	BIT(0)

#घोषणा DES_REG_DATA_N(dd, x)		((dd)->pdata->data_ofs + ((x) * 0x04))

#घोषणा DES_REG_REV(dd)			((dd)->pdata->rev_ofs)

#घोषणा DES_REG_MASK(dd)		((dd)->pdata->mask_ofs)

#घोषणा DES_REG_LENGTH_N(x)		(0x24 + ((x) * 0x04))

#घोषणा DES_REG_IRQ_STATUS(dd)         ((dd)->pdata->irq_status_ofs)
#घोषणा DES_REG_IRQ_ENABLE(dd)         ((dd)->pdata->irq_enable_ofs)
#घोषणा DES_REG_IRQ_DATA_IN            BIT(1)
#घोषणा DES_REG_IRQ_DATA_OUT           BIT(2)

#घोषणा FLAGS_MODE_MASK		0x000f
#घोषणा FLAGS_ENCRYPT		BIT(0)
#घोषणा FLAGS_CBC		BIT(1)
#घोषणा FLAGS_INIT		BIT(4)
#घोषणा FLAGS_BUSY		BIT(6)

#घोषणा DEFAULT_AUTOSUSPEND_DELAY	1000

#घोषणा FLAGS_IN_DATA_ST_SHIFT	8
#घोषणा FLAGS_OUT_DATA_ST_SHIFT	10

काष्ठा omap_des_ctx अणु
	काष्ठा crypto_engine_ctx enginectx;
	काष्ठा omap_des_dev *dd;

	पूर्णांक		keylen;
	__le32		key[(3 * DES_KEY_SIZE) / माप(u32)];
	अचिन्हित दीर्घ	flags;
पूर्ण;

काष्ठा omap_des_reqctx अणु
	अचिन्हित दीर्घ mode;
पूर्ण;

#घोषणा OMAP_DES_QUEUE_LENGTH	1
#घोषणा OMAP_DES_CACHE_SIZE	0

काष्ठा omap_des_algs_info अणु
	काष्ठा skcipher_alg	*algs_list;
	अचिन्हित पूर्णांक		size;
	अचिन्हित पूर्णांक		रेजिस्टरed;
पूर्ण;

काष्ठा omap_des_pdata अणु
	काष्ठा omap_des_algs_info	*algs_info;
	अचिन्हित पूर्णांक	algs_info_size;

	व्योम		(*trigger)(काष्ठा omap_des_dev *dd, पूर्णांक length);

	u32		key_ofs;
	u32		iv_ofs;
	u32		ctrl_ofs;
	u32		data_ofs;
	u32		rev_ofs;
	u32		mask_ofs;
	u32             irq_enable_ofs;
	u32             irq_status_ofs;

	u32		dma_enable_in;
	u32		dma_enable_out;
	u32		dma_start;

	u32		major_mask;
	u32		major_shअगरt;
	u32		minor_mask;
	u32		minor_shअगरt;
पूर्ण;

काष्ठा omap_des_dev अणु
	काष्ठा list_head	list;
	अचिन्हित दीर्घ		phys_base;
	व्योम __iomem		*io_base;
	काष्ठा omap_des_ctx	*ctx;
	काष्ठा device		*dev;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			err;

	काष्ठा tasklet_काष्ठा	करोne_task;

	काष्ठा skcipher_request	*req;
	काष्ठा crypto_engine		*engine;
	/*
	 * total is used by PIO mode क्रम book keeping so पूर्णांकroduce
	 * variable total_save as need it to calc page_order
	 */
	माप_प्रकार                          total;
	माप_प्रकार                          total_save;

	काष्ठा scatterlist		*in_sg;
	काष्ठा scatterlist		*out_sg;

	/* Buffers क्रम copying क्रम unaligned हालs */
	काष्ठा scatterlist		in_sgl;
	काष्ठा scatterlist		out_sgl;
	काष्ठा scatterlist		*orig_out;

	काष्ठा scatter_walk		in_walk;
	काष्ठा scatter_walk		out_walk;
	काष्ठा dma_chan		*dma_lch_in;
	काष्ठा dma_chan		*dma_lch_out;
	पूर्णांक			in_sg_len;
	पूर्णांक			out_sg_len;
	पूर्णांक			pio_only;
	स्थिर काष्ठा omap_des_pdata	*pdata;
पूर्ण;

/* keep रेजिस्टरed devices data here */
अटल LIST_HEAD(dev_list);
अटल DEFINE_SPINLOCK(list_lock);

#अगर_घोषित DEBUG
#घोषणा omap_des_पढ़ो(dd, offset)                               \
	(अणु                                                              \
	 पूर्णांक _पढ़ो_ret;                                          \
	 _पढ़ो_ret = __raw_पढ़ोl(dd->io_base + offset);          \
	 pr_err("omap_des_read(" #offset "=%#x)= %#x\n",       \
		 offset, _पढ़ो_ret);                            \
	 _पढ़ो_ret;                                              \
	 पूर्ण)
#अन्यथा
अटल अंतरभूत u32 omap_des_पढ़ो(काष्ठा omap_des_dev *dd, u32 offset)
अणु
	वापस __raw_पढ़ोl(dd->io_base + offset);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित DEBUG
#घोषणा omap_des_ग_लिखो(dd, offset, value)                               \
	करो अणु                                                            \
		pr_err("omap_des_write(" #offset "=%#x) value=%#x\n", \
				offset, value);                                \
		__raw_ग_लिखोl(value, dd->io_base + offset);              \
	पूर्ण जबतक (0)
#अन्यथा
अटल अंतरभूत व्योम omap_des_ग_लिखो(काष्ठा omap_des_dev *dd, u32 offset,
		u32 value)
अणु
	__raw_ग_लिखोl(value, dd->io_base + offset);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम omap_des_ग_लिखो_mask(काष्ठा omap_des_dev *dd, u32 offset,
					u32 value, u32 mask)
अणु
	u32 val;

	val = omap_des_पढ़ो(dd, offset);
	val &= ~mask;
	val |= value;
	omap_des_ग_लिखो(dd, offset, val);
पूर्ण

अटल व्योम omap_des_ग_लिखो_n(काष्ठा omap_des_dev *dd, u32 offset,
					u32 *value, पूर्णांक count)
अणु
	क्रम (; count--; value++, offset += 4)
		omap_des_ग_लिखो(dd, offset, *value);
पूर्ण

अटल पूर्णांक omap_des_hw_init(काष्ठा omap_des_dev *dd)
अणु
	पूर्णांक err;

	/*
	 * घड़ीs are enabled when request starts and disabled when finished.
	 * It may be दीर्घ delays between requests.
	 * Device might go to off mode to save घातer.
	 */
	err = pm_runसमय_get_sync(dd->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_noidle(dd->dev);
		dev_err(dd->dev, "%s: failed to get_sync(%d)\n", __func__, err);
		वापस err;
	पूर्ण

	अगर (!(dd->flags & FLAGS_INIT)) अणु
		dd->flags |= FLAGS_INIT;
		dd->err = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_des_ग_लिखो_ctrl(काष्ठा omap_des_dev *dd)
अणु
	अचिन्हित पूर्णांक key32;
	पूर्णांक i, err;
	u32 val = 0, mask = 0;

	err = omap_des_hw_init(dd);
	अगर (err)
		वापस err;

	key32 = dd->ctx->keylen / माप(u32);

	/* it seems a key should always be set even अगर it has not changed */
	क्रम (i = 0; i < key32; i++) अणु
		omap_des_ग_लिखो(dd, DES_REG_KEY(dd, i),
			       __le32_to_cpu(dd->ctx->key[i]));
	पूर्ण

	अगर ((dd->flags & FLAGS_CBC) && dd->req->iv)
		omap_des_ग_लिखो_n(dd, DES_REG_IV(dd, 0), (व्योम *)dd->req->iv, 2);

	अगर (dd->flags & FLAGS_CBC)
		val |= DES_REG_CTRL_CBC;
	अगर (dd->flags & FLAGS_ENCRYPT)
		val |= DES_REG_CTRL_सूचीECTION;
	अगर (key32 == 6)
		val |= DES_REG_CTRL_TDES;

	mask |= DES_REG_CTRL_CBC | DES_REG_CTRL_सूचीECTION | DES_REG_CTRL_TDES;

	omap_des_ग_लिखो_mask(dd, DES_REG_CTRL(dd), val, mask);

	वापस 0;
पूर्ण

अटल व्योम omap_des_dma_trigger_omap4(काष्ठा omap_des_dev *dd, पूर्णांक length)
अणु
	u32 mask, val;

	omap_des_ग_लिखो(dd, DES_REG_LENGTH_N(0), length);

	val = dd->pdata->dma_start;

	अगर (dd->dma_lch_out != शून्य)
		val |= dd->pdata->dma_enable_out;
	अगर (dd->dma_lch_in != शून्य)
		val |= dd->pdata->dma_enable_in;

	mask = dd->pdata->dma_enable_out | dd->pdata->dma_enable_in |
	       dd->pdata->dma_start;

	omap_des_ग_लिखो_mask(dd, DES_REG_MASK(dd), val, mask);
पूर्ण

अटल व्योम omap_des_dma_stop(काष्ठा omap_des_dev *dd)
अणु
	u32 mask;

	mask = dd->pdata->dma_enable_out | dd->pdata->dma_enable_in |
	       dd->pdata->dma_start;

	omap_des_ग_लिखो_mask(dd, DES_REG_MASK(dd), 0, mask);
पूर्ण

अटल काष्ठा omap_des_dev *omap_des_find_dev(काष्ठा omap_des_ctx *ctx)
अणु
	काष्ठा omap_des_dev *dd = शून्य, *पंचांगp;

	spin_lock_bh(&list_lock);
	अगर (!ctx->dd) अणु
		list_क्रम_each_entry(पंचांगp, &dev_list, list) अणु
			/* FIXME: take fist available des core */
			dd = पंचांगp;
			अवरोध;
		पूर्ण
		ctx->dd = dd;
	पूर्ण अन्यथा अणु
		/* alपढ़ोy found beक्रमe */
		dd = ctx->dd;
	पूर्ण
	spin_unlock_bh(&list_lock);

	वापस dd;
पूर्ण

अटल व्योम omap_des_dma_out_callback(व्योम *data)
अणु
	काष्ठा omap_des_dev *dd = data;

	/* dma_lch_out - completed */
	tasklet_schedule(&dd->करोne_task);
पूर्ण

अटल पूर्णांक omap_des_dma_init(काष्ठा omap_des_dev *dd)
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

अटल व्योम omap_des_dma_cleanup(काष्ठा omap_des_dev *dd)
अणु
	अगर (dd->pio_only)
		वापस;

	dma_release_channel(dd->dma_lch_out);
	dma_release_channel(dd->dma_lch_in);
पूर्ण

अटल पूर्णांक omap_des_crypt_dma(काष्ठा crypto_tfm *tfm,
		काष्ठा scatterlist *in_sg, काष्ठा scatterlist *out_sg,
		पूर्णांक in_sg_len, पूर्णांक out_sg_len)
अणु
	काष्ठा omap_des_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा omap_des_dev *dd = ctx->dd;
	काष्ठा dma_async_tx_descriptor *tx_in, *tx_out;
	काष्ठा dma_slave_config cfg;
	पूर्णांक ret;

	अगर (dd->pio_only) अणु
		scatterwalk_start(&dd->in_walk, dd->in_sg);
		scatterwalk_start(&dd->out_walk, dd->out_sg);

		/* Enable DATAIN पूर्णांकerrupt and let it take
		   care of the rest */
		omap_des_ग_लिखो(dd, DES_REG_IRQ_ENABLE(dd), 0x2);
		वापस 0;
	पूर्ण

	dma_sync_sg_क्रम_device(dd->dev, dd->in_sg, in_sg_len, DMA_TO_DEVICE);

	स_रखो(&cfg, 0, माप(cfg));

	cfg.src_addr = dd->phys_base + DES_REG_DATA_N(dd, 0);
	cfg.dst_addr = dd->phys_base + DES_REG_DATA_N(dd, 0);
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

	/* OUT */
	ret = dmaengine_slave_config(dd->dma_lch_out, &cfg);
	अगर (ret) अणु
		dev_err(dd->dev, "can't configure OUT dmaengine slave: %d\n",
			ret);
		वापस ret;
	पूर्ण

	tx_out = dmaengine_prep_slave_sg(dd->dma_lch_out, out_sg, out_sg_len,
					DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!tx_out) अणु
		dev_err(dd->dev, "OUT prep_slave_sg() failed\n");
		वापस -EINVAL;
	पूर्ण

	tx_out->callback = omap_des_dma_out_callback;
	tx_out->callback_param = dd;

	dmaengine_submit(tx_in);
	dmaengine_submit(tx_out);

	dma_async_issue_pending(dd->dma_lch_in);
	dma_async_issue_pending(dd->dma_lch_out);

	/* start DMA */
	dd->pdata->trigger(dd, dd->total);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_des_crypt_dma_start(काष्ठा omap_des_dev *dd)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(
					crypto_skcipher_reqtfm(dd->req));
	पूर्णांक err;

	pr_debug("total: %zd\n", dd->total);

	अगर (!dd->pio_only) अणु
		err = dma_map_sg(dd->dev, dd->in_sg, dd->in_sg_len,
				 DMA_TO_DEVICE);
		अगर (!err) अणु
			dev_err(dd->dev, "dma_map_sg() error\n");
			वापस -EINVAL;
		पूर्ण

		err = dma_map_sg(dd->dev, dd->out_sg, dd->out_sg_len,
				 DMA_FROM_DEVICE);
		अगर (!err) अणु
			dev_err(dd->dev, "dma_map_sg() error\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	err = omap_des_crypt_dma(tfm, dd->in_sg, dd->out_sg, dd->in_sg_len,
				 dd->out_sg_len);
	अगर (err && !dd->pio_only) अणु
		dma_unmap_sg(dd->dev, dd->in_sg, dd->in_sg_len, DMA_TO_DEVICE);
		dma_unmap_sg(dd->dev, dd->out_sg, dd->out_sg_len,
			     DMA_FROM_DEVICE);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम omap_des_finish_req(काष्ठा omap_des_dev *dd, पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = dd->req;

	pr_debug("err: %d\n", err);

	crypto_finalize_skcipher_request(dd->engine, req, err);

	pm_runसमय_mark_last_busy(dd->dev);
	pm_runसमय_put_स्वतःsuspend(dd->dev);
पूर्ण

अटल पूर्णांक omap_des_crypt_dma_stop(काष्ठा omap_des_dev *dd)
अणु
	pr_debug("total: %zd\n", dd->total);

	omap_des_dma_stop(dd);

	dmaengine_terminate_all(dd->dma_lch_in);
	dmaengine_terminate_all(dd->dma_lch_out);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_des_handle_queue(काष्ठा omap_des_dev *dd,
				 काष्ठा skcipher_request *req)
अणु
	अगर (req)
		वापस crypto_transfer_skcipher_request_to_engine(dd->engine, req);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_des_prepare_req(काष्ठा crypto_engine *engine,
				व्योम *areq)
अणु
	काष्ठा skcipher_request *req = container_of(areq, काष्ठा skcipher_request, base);
	काष्ठा omap_des_ctx *ctx = crypto_skcipher_ctx(
			crypto_skcipher_reqtfm(req));
	काष्ठा omap_des_dev *dd = omap_des_find_dev(ctx);
	काष्ठा omap_des_reqctx *rctx;
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

	ret = omap_crypto_align_sg(&dd->in_sg, dd->total, DES_BLOCK_SIZE,
				   &dd->in_sgl, flags,
				   FLAGS_IN_DATA_ST_SHIFT, &dd->flags);
	अगर (ret)
		वापस ret;

	ret = omap_crypto_align_sg(&dd->out_sg, dd->total, DES_BLOCK_SIZE,
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

	rctx = skcipher_request_ctx(req);
	ctx = crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	rctx->mode &= FLAGS_MODE_MASK;
	dd->flags = (dd->flags & ~FLAGS_MODE_MASK) | rctx->mode;

	dd->ctx = ctx;
	ctx->dd = dd;

	वापस omap_des_ग_लिखो_ctrl(dd);
पूर्ण

अटल पूर्णांक omap_des_crypt_req(काष्ठा crypto_engine *engine,
			      व्योम *areq)
अणु
	काष्ठा skcipher_request *req = container_of(areq, काष्ठा skcipher_request, base);
	काष्ठा omap_des_ctx *ctx = crypto_skcipher_ctx(
			crypto_skcipher_reqtfm(req));
	काष्ठा omap_des_dev *dd = omap_des_find_dev(ctx);

	अगर (!dd)
		वापस -ENODEV;

	वापस omap_des_crypt_dma_start(dd);
पूर्ण

अटल व्योम omap_des_करोne_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा omap_des_dev *dd = (काष्ठा omap_des_dev *)data;
	पूर्णांक i;

	pr_debug("enter done_task\n");

	अगर (!dd->pio_only) अणु
		dma_sync_sg_क्रम_device(dd->dev, dd->out_sg, dd->out_sg_len,
				       DMA_FROM_DEVICE);
		dma_unmap_sg(dd->dev, dd->in_sg, dd->in_sg_len, DMA_TO_DEVICE);
		dma_unmap_sg(dd->dev, dd->out_sg, dd->out_sg_len,
			     DMA_FROM_DEVICE);
		omap_des_crypt_dma_stop(dd);
	पूर्ण

	omap_crypto_cleanup(&dd->in_sgl, शून्य, 0, dd->total_save,
			    FLAGS_IN_DATA_ST_SHIFT, dd->flags);

	omap_crypto_cleanup(&dd->out_sgl, dd->orig_out, 0, dd->total_save,
			    FLAGS_OUT_DATA_ST_SHIFT, dd->flags);

	अगर ((dd->flags & FLAGS_CBC) && dd->req->iv)
		क्रम (i = 0; i < 2; i++)
			((u32 *)dd->req->iv)[i] =
				omap_des_पढ़ो(dd, DES_REG_IV(dd, i));

	omap_des_finish_req(dd, 0);

	pr_debug("exit\n");
पूर्ण

अटल पूर्णांक omap_des_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ mode)
अणु
	काष्ठा omap_des_ctx *ctx = crypto_skcipher_ctx(
			crypto_skcipher_reqtfm(req));
	काष्ठा omap_des_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा omap_des_dev *dd;

	pr_debug("nbytes: %d, enc: %d, cbc: %d\n", req->cryptlen,
		 !!(mode & FLAGS_ENCRYPT),
		 !!(mode & FLAGS_CBC));

	अगर (!req->cryptlen)
		वापस 0;

	अगर (!IS_ALIGNED(req->cryptlen, DES_BLOCK_SIZE))
		वापस -EINVAL;

	dd = omap_des_find_dev(ctx);
	अगर (!dd)
		वापस -ENODEV;

	rctx->mode = mode;

	वापस omap_des_handle_queue(dd, req);
पूर्ण

/* ********************** ALG API ************************************ */

अटल पूर्णांक omap_des_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा omap_des_ctx *ctx = crypto_skcipher_ctx(cipher);
	पूर्णांक err;

	pr_debug("enter, keylen: %d\n", keylen);

	err = verअगरy_skcipher_des_key(cipher, key);
	अगर (err)
		वापस err;

	स_नकल(ctx->key, key, keylen);
	ctx->keylen = keylen;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_des3_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा omap_des_ctx *ctx = crypto_skcipher_ctx(cipher);
	पूर्णांक err;

	pr_debug("enter, keylen: %d\n", keylen);

	err = verअगरy_skcipher_des3_key(cipher, key);
	अगर (err)
		वापस err;

	स_नकल(ctx->key, key, keylen);
	ctx->keylen = keylen;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_des_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस omap_des_crypt(req, FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक omap_des_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस omap_des_crypt(req, 0);
पूर्ण

अटल पूर्णांक omap_des_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस omap_des_crypt(req, FLAGS_ENCRYPT | FLAGS_CBC);
पूर्ण

अटल पूर्णांक omap_des_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस omap_des_crypt(req, FLAGS_CBC);
पूर्ण

अटल पूर्णांक omap_des_prepare_req(काष्ठा crypto_engine *engine,
				व्योम *areq);
अटल पूर्णांक omap_des_crypt_req(काष्ठा crypto_engine *engine,
			      व्योम *areq);

अटल पूर्णांक omap_des_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा omap_des_ctx *ctx = crypto_skcipher_ctx(tfm);

	pr_debug("enter\n");

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा omap_des_reqctx));

	ctx->enginectx.op.prepare_request = omap_des_prepare_req;
	ctx->enginectx.op.unprepare_request = शून्य;
	ctx->enginectx.op.करो_one_request = omap_des_crypt_req;

	वापस 0;
पूर्ण

/* ********************** ALGS ************************************ */

अटल काष्ठा skcipher_alg algs_ecb_cbc[] = अणु
अणु
	.base.cra_name		= "ecb(des)",
	.base.cra_driver_name	= "ecb-des-omap",
	.base.cra_priority	= 100,
	.base.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_ASYNC,
	.base.cra_blocksize	= DES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा omap_des_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= DES_KEY_SIZE,
	.max_keysize		= DES_KEY_SIZE,
	.setkey			= omap_des_setkey,
	.encrypt		= omap_des_ecb_encrypt,
	.decrypt		= omap_des_ecb_decrypt,
	.init			= omap_des_init_tfm,
पूर्ण,
अणु
	.base.cra_name		= "cbc(des)",
	.base.cra_driver_name	= "cbc-des-omap",
	.base.cra_priority	= 100,
	.base.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_ASYNC,
	.base.cra_blocksize	= DES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा omap_des_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= DES_KEY_SIZE,
	.max_keysize		= DES_KEY_SIZE,
	.ivsize			= DES_BLOCK_SIZE,
	.setkey			= omap_des_setkey,
	.encrypt		= omap_des_cbc_encrypt,
	.decrypt		= omap_des_cbc_decrypt,
	.init			= omap_des_init_tfm,
पूर्ण,
अणु
	.base.cra_name		= "ecb(des3_ede)",
	.base.cra_driver_name	= "ecb-des3-omap",
	.base.cra_priority	= 100,
	.base.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_ASYNC,
	.base.cra_blocksize	= DES3_EDE_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा omap_des_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= DES3_EDE_KEY_SIZE,
	.max_keysize		= DES3_EDE_KEY_SIZE,
	.setkey			= omap_des3_setkey,
	.encrypt		= omap_des_ecb_encrypt,
	.decrypt		= omap_des_ecb_decrypt,
	.init			= omap_des_init_tfm,
पूर्ण,
अणु
	.base.cra_name		= "cbc(des3_ede)",
	.base.cra_driver_name	= "cbc-des3-omap",
	.base.cra_priority	= 100,
	.base.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_ASYNC,
	.base.cra_blocksize	= DES3_EDE_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा omap_des_ctx),
	.base.cra_module	= THIS_MODULE,

	.min_keysize		= DES3_EDE_KEY_SIZE,
	.max_keysize		= DES3_EDE_KEY_SIZE,
	.ivsize			= DES3_EDE_BLOCK_SIZE,
	.setkey			= omap_des3_setkey,
	.encrypt		= omap_des_cbc_encrypt,
	.decrypt		= omap_des_cbc_decrypt,
	.init			= omap_des_init_tfm,
पूर्ण
पूर्ण;

अटल काष्ठा omap_des_algs_info omap_des_algs_info_ecb_cbc[] = अणु
	अणु
		.algs_list	= algs_ecb_cbc,
		.size		= ARRAY_SIZE(algs_ecb_cbc),
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा omap_des_pdata omap_des_pdata_omap4 = अणु
	.algs_info	= omap_des_algs_info_ecb_cbc,
	.algs_info_size	= ARRAY_SIZE(omap_des_algs_info_ecb_cbc),
	.trigger	= omap_des_dma_trigger_omap4,
	.key_ofs	= 0x14,
	.iv_ofs		= 0x18,
	.ctrl_ofs	= 0x20,
	.data_ofs	= 0x28,
	.rev_ofs	= 0x30,
	.mask_ofs	= 0x34,
	.irq_status_ofs = 0x3c,
	.irq_enable_ofs = 0x40,
	.dma_enable_in	= BIT(5),
	.dma_enable_out	= BIT(6),
	.major_mask	= 0x0700,
	.major_shअगरt	= 8,
	.minor_mask	= 0x003f,
	.minor_shअगरt	= 0,
पूर्ण;

अटल irqवापस_t omap_des_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा omap_des_dev *dd = dev_id;
	u32 status, i;
	u32 *src, *dst;

	status = omap_des_पढ़ो(dd, DES_REG_IRQ_STATUS(dd));
	अगर (status & DES_REG_IRQ_DATA_IN) अणु
		omap_des_ग_लिखो(dd, DES_REG_IRQ_ENABLE(dd), 0x0);

		BUG_ON(!dd->in_sg);

		BUG_ON(_calc_walked(in) > dd->in_sg->length);

		src = sg_virt(dd->in_sg) + _calc_walked(in);

		क्रम (i = 0; i < DES_BLOCK_WORDS; i++) अणु
			omap_des_ग_लिखो(dd, DES_REG_DATA_N(dd, i), *src);

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
		status &= ~DES_REG_IRQ_DATA_IN;
		omap_des_ग_लिखो(dd, DES_REG_IRQ_STATUS(dd), status);

		/* Enable DATA_OUT पूर्णांकerrupt */
		omap_des_ग_लिखो(dd, DES_REG_IRQ_ENABLE(dd), 0x4);

	पूर्ण अन्यथा अगर (status & DES_REG_IRQ_DATA_OUT) अणु
		omap_des_ग_लिखो(dd, DES_REG_IRQ_ENABLE(dd), 0x0);

		BUG_ON(!dd->out_sg);

		BUG_ON(_calc_walked(out) > dd->out_sg->length);

		dst = sg_virt(dd->out_sg) + _calc_walked(out);

		क्रम (i = 0; i < DES_BLOCK_WORDS; i++) अणु
			*dst = omap_des_पढ़ो(dd, DES_REG_DATA_N(dd, i));
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

		BUG_ON(dd->total < DES_BLOCK_SIZE);

		dd->total -= DES_BLOCK_SIZE;

		/* Clear IRQ status */
		status &= ~DES_REG_IRQ_DATA_OUT;
		omap_des_ग_लिखो(dd, DES_REG_IRQ_STATUS(dd), status);

		अगर (!dd->total)
			/* All bytes पढ़ो! */
			tasklet_schedule(&dd->करोne_task);
		अन्यथा
			/* Enable DATA_IN पूर्णांकerrupt क्रम next block */
			omap_des_ग_लिखो(dd, DES_REG_IRQ_ENABLE(dd), 0x2);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा of_device_id omap_des_of_match[] = अणु
	अणु
		.compatible	= "ti,omap4-des",
		.data		= &omap_des_pdata_omap4,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_des_of_match);

अटल पूर्णांक omap_des_get_of(काष्ठा omap_des_dev *dd,
		काष्ठा platक्रमm_device *pdev)
अणु

	dd->pdata = of_device_get_match_data(&pdev->dev);
	अगर (!dd->pdata) अणु
		dev_err(&pdev->dev, "no compatible OF match\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक omap_des_get_of(काष्ठा omap_des_dev *dd,
		काष्ठा device *dev)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक omap_des_get_pdev(काष्ठा omap_des_dev *dd,
		काष्ठा platक्रमm_device *pdev)
अणु
	/* non-DT devices get pdata from pdev */
	dd->pdata = pdev->dev.platक्रमm_data;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_des_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा omap_des_dev *dd;
	काष्ठा skcipher_alg *algp;
	काष्ठा resource *res;
	पूर्णांक err = -ENOMEM, i, j, irq = -1;
	u32 reg;

	dd = devm_kzalloc(dev, माप(काष्ठा omap_des_dev), GFP_KERNEL);
	अगर (dd == शून्य) अणु
		dev_err(dev, "unable to alloc data struct.\n");
		जाओ err_data;
	पूर्ण
	dd->dev = dev;
	platक्रमm_set_drvdata(pdev, dd);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "no MEM resource info\n");
		जाओ err_res;
	पूर्ण

	err = (dev->of_node) ? omap_des_get_of(dd, pdev) :
			       omap_des_get_pdev(dd, pdev);
	अगर (err)
		जाओ err_res;

	dd->io_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(dd->io_base)) अणु
		err = PTR_ERR(dd->io_base);
		जाओ err_res;
	पूर्ण
	dd->phys_base = res->start;

	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, DEFAULT_AUTOSUSPEND_DELAY);

	pm_runसमय_enable(dev);
	err = pm_runसमय_get_sync(dev);
	अगर (err < 0) अणु
		pm_runसमय_put_noidle(dev);
		dev_err(dd->dev, "%s: failed to get_sync(%d)\n", __func__, err);
		जाओ err_get;
	पूर्ण

	omap_des_dma_stop(dd);

	reg = omap_des_पढ़ो(dd, DES_REG_REV(dd));

	pm_runसमय_put_sync(dev);

	dev_info(dev, "OMAP DES hw accel rev: %u.%u\n",
		 (reg & dd->pdata->major_mask) >> dd->pdata->major_shअगरt,
		 (reg & dd->pdata->minor_mask) >> dd->pdata->minor_shअगरt);

	tasklet_init(&dd->करोne_task, omap_des_करोne_task, (अचिन्हित दीर्घ)dd);

	err = omap_des_dma_init(dd);
	अगर (err == -EPROBE_DEFER) अणु
		जाओ err_irq;
	पूर्ण अन्यथा अगर (err && DES_REG_IRQ_STATUS(dd) && DES_REG_IRQ_ENABLE(dd)) अणु
		dd->pio_only = 1;

		irq = platक्रमm_get_irq(pdev, 0);
		अगर (irq < 0) अणु
			err = irq;
			जाओ err_irq;
		पूर्ण

		err = devm_request_irq(dev, irq, omap_des_irq, 0,
				dev_name(dev), dd);
		अगर (err) अणु
			dev_err(dev, "Unable to grab omap-des IRQ\n");
			जाओ err_irq;
		पूर्ण
	पूर्ण


	INIT_LIST_HEAD(&dd->list);
	spin_lock(&list_lock);
	list_add_tail(&dd->list, &dev_list);
	spin_unlock(&list_lock);

	/* Initialize des crypto engine */
	dd->engine = crypto_engine_alloc_init(dev, 1);
	अगर (!dd->engine) अणु
		err = -ENOMEM;
		जाओ err_engine;
	पूर्ण

	err = crypto_engine_start(dd->engine);
	अगर (err)
		जाओ err_engine;

	क्रम (i = 0; i < dd->pdata->algs_info_size; i++) अणु
		क्रम (j = 0; j < dd->pdata->algs_info[i].size; j++) अणु
			algp = &dd->pdata->algs_info[i].algs_list[j];

			pr_debug("reg alg: %s\n", algp->base.cra_name);

			err = crypto_रेजिस्टर_skcipher(algp);
			अगर (err)
				जाओ err_algs;

			dd->pdata->algs_info[i].रेजिस्टरed++;
		पूर्ण
	पूर्ण

	वापस 0;

err_algs:
	क्रम (i = dd->pdata->algs_info_size - 1; i >= 0; i--)
		क्रम (j = dd->pdata->algs_info[i].रेजिस्टरed - 1; j >= 0; j--)
			crypto_unरेजिस्टर_skcipher(
					&dd->pdata->algs_info[i].algs_list[j]);

err_engine:
	अगर (dd->engine)
		crypto_engine_निकास(dd->engine);

	omap_des_dma_cleanup(dd);
err_irq:
	tasklet_समाप्त(&dd->करोne_task);
err_get:
	pm_runसमय_disable(dev);
err_res:
	dd = शून्य;
err_data:
	dev_err(dev, "initialization failed.\n");
	वापस err;
पूर्ण

अटल पूर्णांक omap_des_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_des_dev *dd = platक्रमm_get_drvdata(pdev);
	पूर्णांक i, j;

	अगर (!dd)
		वापस -ENODEV;

	spin_lock(&list_lock);
	list_del(&dd->list);
	spin_unlock(&list_lock);

	क्रम (i = dd->pdata->algs_info_size - 1; i >= 0; i--)
		क्रम (j = dd->pdata->algs_info[i].रेजिस्टरed - 1; j >= 0; j--)
			crypto_unरेजिस्टर_skcipher(
					&dd->pdata->algs_info[i].algs_list[j]);

	tasklet_समाप्त(&dd->करोne_task);
	omap_des_dma_cleanup(dd);
	pm_runसमय_disable(dd->dev);
	dd = शून्य;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक omap_des_suspend(काष्ठा device *dev)
अणु
	pm_runसमय_put_sync(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_des_resume(काष्ठा device *dev)
अणु
	पूर्णांक err;

	err = pm_runसमय_get_sync(dev);
	अगर (err < 0) अणु
		pm_runसमय_put_noidle(dev);
		dev_err(dev, "%s: failed to get_sync(%d)\n", __func__, err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(omap_des_pm_ops, omap_des_suspend, omap_des_resume);

अटल काष्ठा platक्रमm_driver omap_des_driver = अणु
	.probe	= omap_des_probe,
	.हटाओ	= omap_des_हटाओ,
	.driver	= अणु
		.name	= "omap-des",
		.pm	= &omap_des_pm_ops,
		.of_match_table	= of_match_ptr(omap_des_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omap_des_driver);

MODULE_DESCRIPTION("OMAP DES hw acceleration support.");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Joel Fernandes <joelf@ti.com>");
