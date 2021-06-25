<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cryptographic API.
 *
 * Support क्रम ATMEL DES/TDES HW acceleration.
 *
 * Copyright (c) 2012 Eukrथऊa Electromatique - ATMEL
 * Author: Nicolas Royer <nicolas@eukrea.com>
 *
 * Some ideas are from omap-aes.c drivers.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश "atmel-tdes-regs.h"

#घोषणा ATMEL_TDES_PRIORITY	300

/* TDES flags  */
/* Reserve bits [17:16], [13:12], [2:0] क्रम AES Mode Register */
#घोषणा TDES_FLAGS_ENCRYPT	TDES_MR_CYPHER_ENC
#घोषणा TDES_FLAGS_OPMODE_MASK	(TDES_MR_OPMOD_MASK | TDES_MR_CFBS_MASK)
#घोषणा TDES_FLAGS_ECB		TDES_MR_OPMOD_ECB
#घोषणा TDES_FLAGS_CBC		TDES_MR_OPMOD_CBC
#घोषणा TDES_FLAGS_OFB		TDES_MR_OPMOD_OFB
#घोषणा TDES_FLAGS_CFB64	(TDES_MR_OPMOD_CFB | TDES_MR_CFBS_64b)
#घोषणा TDES_FLAGS_CFB32	(TDES_MR_OPMOD_CFB | TDES_MR_CFBS_32b)
#घोषणा TDES_FLAGS_CFB16	(TDES_MR_OPMOD_CFB | TDES_MR_CFBS_16b)
#घोषणा TDES_FLAGS_CFB8		(TDES_MR_OPMOD_CFB | TDES_MR_CFBS_8b)

#घोषणा TDES_FLAGS_MODE_MASK	(TDES_FLAGS_OPMODE_MASK | TDES_FLAGS_ENCRYPT)

#घोषणा TDES_FLAGS_INIT		BIT(3)
#घोषणा TDES_FLAGS_FAST		BIT(4)
#घोषणा TDES_FLAGS_BUSY		BIT(5)
#घोषणा TDES_FLAGS_DMA		BIT(6)

#घोषणा ATMEL_TDES_QUEUE_LENGTH	50

#घोषणा CFB8_BLOCK_SIZE		1
#घोषणा CFB16_BLOCK_SIZE	2
#घोषणा CFB32_BLOCK_SIZE	4

काष्ठा aपंचांगel_tdes_caps अणु
	bool	has_dma;
	u32		has_cfb_3keys;
पूर्ण;

काष्ठा aपंचांगel_tdes_dev;

काष्ठा aपंचांगel_tdes_ctx अणु
	काष्ठा aपंचांगel_tdes_dev *dd;

	पूर्णांक		keylen;
	u32		key[DES3_EDE_KEY_SIZE / माप(u32)];
	अचिन्हित दीर्घ	flags;

	u16		block_size;
पूर्ण;

काष्ठा aपंचांगel_tdes_reqctx अणु
	अचिन्हित दीर्घ mode;
	u8 lastc[DES_BLOCK_SIZE];
पूर्ण;

काष्ठा aपंचांगel_tdes_dma अणु
	काष्ठा dma_chan			*chan;
	काष्ठा dma_slave_config dma_conf;
पूर्ण;

काष्ठा aपंचांगel_tdes_dev अणु
	काष्ठा list_head	list;
	अचिन्हित दीर्घ		phys_base;
	व्योम __iomem		*io_base;

	काष्ठा aपंचांगel_tdes_ctx	*ctx;
	काष्ठा device		*dev;
	काष्ठा clk			*iclk;
	पूर्णांक					irq;

	अचिन्हित दीर्घ		flags;

	spinlock_t		lock;
	काष्ठा crypto_queue	queue;

	काष्ठा tasklet_काष्ठा	करोne_task;
	काष्ठा tasklet_काष्ठा	queue_task;

	काष्ठा skcipher_request	*req;
	माप_प्रकार				total;

	काष्ठा scatterlist	*in_sg;
	अचिन्हित पूर्णांक		nb_in_sg;
	माप_प्रकार				in_offset;
	काष्ठा scatterlist	*out_sg;
	अचिन्हित पूर्णांक		nb_out_sg;
	माप_प्रकार				out_offset;

	माप_प्रकार	buflen;
	माप_प्रकार	dma_size;

	व्योम	*buf_in;
	पूर्णांक		dma_in;
	dma_addr_t	dma_addr_in;
	काष्ठा aपंचांगel_tdes_dma	dma_lch_in;

	व्योम	*buf_out;
	पूर्णांक		dma_out;
	dma_addr_t	dma_addr_out;
	काष्ठा aपंचांगel_tdes_dma	dma_lch_out;

	काष्ठा aपंचांगel_tdes_caps	caps;

	u32	hw_version;
पूर्ण;

काष्ठा aपंचांगel_tdes_drv अणु
	काष्ठा list_head	dev_list;
	spinlock_t		lock;
पूर्ण;

अटल काष्ठा aपंचांगel_tdes_drv aपंचांगel_tdes = अणु
	.dev_list = LIST_HEAD_INIT(aपंचांगel_tdes.dev_list),
	.lock = __SPIN_LOCK_UNLOCKED(aपंचांगel_tdes.lock),
पूर्ण;

अटल पूर्णांक aपंचांगel_tdes_sg_copy(काष्ठा scatterlist **sg, माप_प्रकार *offset,
			व्योम *buf, माप_प्रकार buflen, माप_प्रकार total, पूर्णांक out)
अणु
	माप_प्रकार count, off = 0;

	जबतक (buflen && total) अणु
		count = min((*sg)->length - *offset, total);
		count = min(count, buflen);

		अगर (!count)
			वापस off;

		scatterwalk_map_and_copy(buf + off, *sg, *offset, count, out);

		off += count;
		buflen -= count;
		*offset += count;
		total -= count;

		अगर (*offset == (*sg)->length) अणु
			*sg = sg_next(*sg);
			अगर (*sg)
				*offset = 0;
			अन्यथा
				total = 0;
		पूर्ण
	पूर्ण

	वापस off;
पूर्ण

अटल अंतरभूत u32 aपंचांगel_tdes_पढ़ो(काष्ठा aपंचांगel_tdes_dev *dd, u32 offset)
अणु
	वापस पढ़ोl_relaxed(dd->io_base + offset);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_tdes_ग_लिखो(काष्ठा aपंचांगel_tdes_dev *dd,
					u32 offset, u32 value)
अणु
	ग_लिखोl_relaxed(value, dd->io_base + offset);
पूर्ण

अटल व्योम aपंचांगel_tdes_ग_लिखो_n(काष्ठा aपंचांगel_tdes_dev *dd, u32 offset,
			       स्थिर u32 *value, पूर्णांक count)
अणु
	क्रम (; count--; value++, offset += 4)
		aपंचांगel_tdes_ग_लिखो(dd, offset, *value);
पूर्ण

अटल काष्ठा aपंचांगel_tdes_dev *aपंचांगel_tdes_find_dev(काष्ठा aपंचांगel_tdes_ctx *ctx)
अणु
	काष्ठा aपंचांगel_tdes_dev *tdes_dd = शून्य;
	काष्ठा aपंचांगel_tdes_dev *पंचांगp;

	spin_lock_bh(&aपंचांगel_tdes.lock);
	अगर (!ctx->dd) अणु
		list_क्रम_each_entry(पंचांगp, &aपंचांगel_tdes.dev_list, list) अणु
			tdes_dd = पंचांगp;
			अवरोध;
		पूर्ण
		ctx->dd = tdes_dd;
	पूर्ण अन्यथा अणु
		tdes_dd = ctx->dd;
	पूर्ण
	spin_unlock_bh(&aपंचांगel_tdes.lock);

	वापस tdes_dd;
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_hw_init(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	पूर्णांक err;

	err = clk_prepare_enable(dd->iclk);
	अगर (err)
		वापस err;

	अगर (!(dd->flags & TDES_FLAGS_INIT)) अणु
		aपंचांगel_tdes_ग_लिखो(dd, TDES_CR, TDES_CR_SWRST);
		dd->flags |= TDES_FLAGS_INIT;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक aपंचांगel_tdes_get_version(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	वापस aपंचांगel_tdes_पढ़ो(dd, TDES_HW_VERSION) & 0x00000fff;
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_hw_version_init(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	पूर्णांक err;

	err = aपंचांगel_tdes_hw_init(dd);
	अगर (err)
		वापस err;

	dd->hw_version = aपंचांगel_tdes_get_version(dd);

	dev_info(dd->dev,
			"version: 0x%x\n", dd->hw_version);

	clk_disable_unprepare(dd->iclk);

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_tdes_dma_callback(व्योम *data)
अणु
	काष्ठा aपंचांगel_tdes_dev *dd = data;

	/* dma_lch_out - completed */
	tasklet_schedule(&dd->करोne_task);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_ग_लिखो_ctrl(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	पूर्णांक err;
	u32 valmr = TDES_MR_SMOD_PDC;

	err = aपंचांगel_tdes_hw_init(dd);

	अगर (err)
		वापस err;

	अगर (!dd->caps.has_dma)
		aपंचांगel_tdes_ग_लिखो(dd, TDES_PTCR,
			TDES_PTCR_TXTDIS | TDES_PTCR_RXTDIS);

	/* MR रेजिस्टर must be set beक्रमe IV रेजिस्टरs */
	अगर (dd->ctx->keylen > (DES_KEY_SIZE << 1)) अणु
		valmr |= TDES_MR_KEYMOD_3KEY;
		valmr |= TDES_MR_TDESMOD_TDES;
	पूर्ण अन्यथा अगर (dd->ctx->keylen > DES_KEY_SIZE) अणु
		valmr |= TDES_MR_KEYMOD_2KEY;
		valmr |= TDES_MR_TDESMOD_TDES;
	पूर्ण अन्यथा अणु
		valmr |= TDES_MR_TDESMOD_DES;
	पूर्ण

	valmr |= dd->flags & TDES_FLAGS_MODE_MASK;

	aपंचांगel_tdes_ग_लिखो(dd, TDES_MR, valmr);

	aपंचांगel_tdes_ग_लिखो_n(dd, TDES_KEY1W1R, dd->ctx->key,
						dd->ctx->keylen >> 2);

	अगर (dd->req->iv && (valmr & TDES_MR_OPMOD_MASK) != TDES_MR_OPMOD_ECB)
		aपंचांगel_tdes_ग_लिखो_n(dd, TDES_IV1R, (व्योम *)dd->req->iv, 2);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_crypt_pdc_stop(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	पूर्णांक err = 0;
	माप_प्रकार count;

	aपंचांगel_tdes_ग_लिखो(dd, TDES_PTCR, TDES_PTCR_TXTDIS|TDES_PTCR_RXTDIS);

	अगर (dd->flags & TDES_FLAGS_FAST) अणु
		dma_unmap_sg(dd->dev, dd->out_sg, 1, DMA_FROM_DEVICE);
		dma_unmap_sg(dd->dev, dd->in_sg, 1, DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		dma_sync_single_क्रम_device(dd->dev, dd->dma_addr_out,
					   dd->dma_size, DMA_FROM_DEVICE);

		/* copy data */
		count = aपंचांगel_tdes_sg_copy(&dd->out_sg, &dd->out_offset,
				dd->buf_out, dd->buflen, dd->dma_size, 1);
		अगर (count != dd->dma_size) अणु
			err = -EINVAL;
			pr_err("not all data converted: %zu\n", count);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_buff_init(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	पूर्णांक err = -ENOMEM;

	dd->buf_in = (व्योम *)__get_मुक्त_pages(GFP_KERNEL, 0);
	dd->buf_out = (व्योम *)__get_मुक्त_pages(GFP_KERNEL, 0);
	dd->buflen = PAGE_SIZE;
	dd->buflen &= ~(DES_BLOCK_SIZE - 1);

	अगर (!dd->buf_in || !dd->buf_out) अणु
		dev_err(dd->dev, "unable to alloc pages.\n");
		जाओ err_alloc;
	पूर्ण

	/* MAP here */
	dd->dma_addr_in = dma_map_single(dd->dev, dd->buf_in,
					dd->buflen, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dd->dev, dd->dma_addr_in)) अणु
		dev_err(dd->dev, "dma %zd bytes error\n", dd->buflen);
		err = -EINVAL;
		जाओ err_map_in;
	पूर्ण

	dd->dma_addr_out = dma_map_single(dd->dev, dd->buf_out,
					dd->buflen, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dd->dev, dd->dma_addr_out)) अणु
		dev_err(dd->dev, "dma %zd bytes error\n", dd->buflen);
		err = -EINVAL;
		जाओ err_map_out;
	पूर्ण

	वापस 0;

err_map_out:
	dma_unmap_single(dd->dev, dd->dma_addr_in, dd->buflen,
		DMA_TO_DEVICE);
err_map_in:
err_alloc:
	मुक्त_page((अचिन्हित दीर्घ)dd->buf_out);
	मुक्त_page((अचिन्हित दीर्घ)dd->buf_in);
	अगर (err)
		pr_err("error: %d\n", err);
	वापस err;
पूर्ण

अटल व्योम aपंचांगel_tdes_buff_cleanup(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	dma_unmap_single(dd->dev, dd->dma_addr_out, dd->buflen,
			 DMA_FROM_DEVICE);
	dma_unmap_single(dd->dev, dd->dma_addr_in, dd->buflen,
		DMA_TO_DEVICE);
	मुक्त_page((अचिन्हित दीर्घ)dd->buf_out);
	मुक्त_page((अचिन्हित दीर्घ)dd->buf_in);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_crypt_pdc(काष्ठा aपंचांगel_tdes_dev *dd,
				dma_addr_t dma_addr_in,
				dma_addr_t dma_addr_out, पूर्णांक length)
अणु
	काष्ठा aपंचांगel_tdes_reqctx *rctx = skcipher_request_ctx(dd->req);
	पूर्णांक len32;

	dd->dma_size = length;

	अगर (!(dd->flags & TDES_FLAGS_FAST)) अणु
		dma_sync_single_क्रम_device(dd->dev, dma_addr_in, length,
					   DMA_TO_DEVICE);
	पूर्ण

	चयन (rctx->mode & TDES_FLAGS_OPMODE_MASK) अणु
	हाल TDES_FLAGS_CFB8:
		len32 = DIV_ROUND_UP(length, माप(u8));
		अवरोध;

	हाल TDES_FLAGS_CFB16:
		len32 = DIV_ROUND_UP(length, माप(u16));
		अवरोध;

	शेष:
		len32 = DIV_ROUND_UP(length, माप(u32));
		अवरोध;
	पूर्ण

	aपंचांगel_tdes_ग_लिखो(dd, TDES_PTCR, TDES_PTCR_TXTDIS|TDES_PTCR_RXTDIS);
	aपंचांगel_tdes_ग_लिखो(dd, TDES_TPR, dma_addr_in);
	aपंचांगel_tdes_ग_लिखो(dd, TDES_TCR, len32);
	aपंचांगel_tdes_ग_लिखो(dd, TDES_RPR, dma_addr_out);
	aपंचांगel_tdes_ग_लिखो(dd, TDES_RCR, len32);

	/* Enable Interrupt */
	aपंचांगel_tdes_ग_लिखो(dd, TDES_IER, TDES_INT_ENDRX);

	/* Start DMA transfer */
	aपंचांगel_tdes_ग_लिखो(dd, TDES_PTCR, TDES_PTCR_TXTEN | TDES_PTCR_RXTEN);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_crypt_dma(काष्ठा aपंचांगel_tdes_dev *dd,
				dma_addr_t dma_addr_in,
				dma_addr_t dma_addr_out, पूर्णांक length)
अणु
	काष्ठा aपंचांगel_tdes_reqctx *rctx = skcipher_request_ctx(dd->req);
	काष्ठा scatterlist sg[2];
	काष्ठा dma_async_tx_descriptor	*in_desc, *out_desc;
	क्रमागत dma_slave_buswidth addr_width;

	dd->dma_size = length;

	अगर (!(dd->flags & TDES_FLAGS_FAST)) अणु
		dma_sync_single_क्रम_device(dd->dev, dma_addr_in, length,
					   DMA_TO_DEVICE);
	पूर्ण

	चयन (rctx->mode & TDES_FLAGS_OPMODE_MASK) अणु
	हाल TDES_FLAGS_CFB8:
		addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		अवरोध;

	हाल TDES_FLAGS_CFB16:
		addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		अवरोध;

	शेष:
		addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		अवरोध;
	पूर्ण

	dd->dma_lch_in.dma_conf.dst_addr_width = addr_width;
	dd->dma_lch_out.dma_conf.src_addr_width = addr_width;

	dmaengine_slave_config(dd->dma_lch_in.chan, &dd->dma_lch_in.dma_conf);
	dmaengine_slave_config(dd->dma_lch_out.chan, &dd->dma_lch_out.dma_conf);

	dd->flags |= TDES_FLAGS_DMA;

	sg_init_table(&sg[0], 1);
	sg_dma_address(&sg[0]) = dma_addr_in;
	sg_dma_len(&sg[0]) = length;

	sg_init_table(&sg[1], 1);
	sg_dma_address(&sg[1]) = dma_addr_out;
	sg_dma_len(&sg[1]) = length;

	in_desc = dmaengine_prep_slave_sg(dd->dma_lch_in.chan, &sg[0],
				1, DMA_MEM_TO_DEV,
				DMA_PREP_INTERRUPT  |  DMA_CTRL_ACK);
	अगर (!in_desc)
		वापस -EINVAL;

	out_desc = dmaengine_prep_slave_sg(dd->dma_lch_out.chan, &sg[1],
				1, DMA_DEV_TO_MEM,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!out_desc)
		वापस -EINVAL;

	out_desc->callback = aपंचांगel_tdes_dma_callback;
	out_desc->callback_param = dd;

	dmaengine_submit(out_desc);
	dma_async_issue_pending(dd->dma_lch_out.chan);

	dmaengine_submit(in_desc);
	dma_async_issue_pending(dd->dma_lch_in.chan);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_crypt_start(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	पूर्णांक err, fast = 0, in, out;
	माप_प्रकार count;
	dma_addr_t addr_in, addr_out;

	अगर ((!dd->in_offset) && (!dd->out_offset)) अणु
		/* check क्रम alignment */
		in = IS_ALIGNED((u32)dd->in_sg->offset, माप(u32)) &&
			IS_ALIGNED(dd->in_sg->length, dd->ctx->block_size);
		out = IS_ALIGNED((u32)dd->out_sg->offset, माप(u32)) &&
			IS_ALIGNED(dd->out_sg->length, dd->ctx->block_size);
		fast = in && out;

		अगर (sg_dma_len(dd->in_sg) != sg_dma_len(dd->out_sg))
			fast = 0;
	पूर्ण


	अगर (fast)  अणु
		count = min_t(माप_प्रकार, dd->total, sg_dma_len(dd->in_sg));
		count = min_t(माप_प्रकार, count, sg_dma_len(dd->out_sg));

		err = dma_map_sg(dd->dev, dd->in_sg, 1, DMA_TO_DEVICE);
		अगर (!err) अणु
			dev_err(dd->dev, "dma_map_sg() error\n");
			वापस -EINVAL;
		पूर्ण

		err = dma_map_sg(dd->dev, dd->out_sg, 1,
				DMA_FROM_DEVICE);
		अगर (!err) अणु
			dev_err(dd->dev, "dma_map_sg() error\n");
			dma_unmap_sg(dd->dev, dd->in_sg, 1,
				DMA_TO_DEVICE);
			वापस -EINVAL;
		पूर्ण

		addr_in = sg_dma_address(dd->in_sg);
		addr_out = sg_dma_address(dd->out_sg);

		dd->flags |= TDES_FLAGS_FAST;

	पूर्ण अन्यथा अणु
		/* use cache buffers */
		count = aपंचांगel_tdes_sg_copy(&dd->in_sg, &dd->in_offset,
				dd->buf_in, dd->buflen, dd->total, 0);

		addr_in = dd->dma_addr_in;
		addr_out = dd->dma_addr_out;

		dd->flags &= ~TDES_FLAGS_FAST;
	पूर्ण

	dd->total -= count;

	अगर (dd->caps.has_dma)
		err = aपंचांगel_tdes_crypt_dma(dd, addr_in, addr_out, count);
	अन्यथा
		err = aपंचांगel_tdes_crypt_pdc(dd, addr_in, addr_out, count);

	अगर (err && (dd->flags & TDES_FLAGS_FAST)) अणु
		dma_unmap_sg(dd->dev, dd->in_sg, 1, DMA_TO_DEVICE);
		dma_unmap_sg(dd->dev, dd->out_sg, 1, DMA_TO_DEVICE);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम
aपंचांगel_tdes_set_iv_as_last_ciphertext_block(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	काष्ठा skcipher_request *req = dd->req;
	काष्ठा aपंचांगel_tdes_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);

	अगर (req->cryptlen < ivsize)
		वापस;

	अगर (rctx->mode & TDES_FLAGS_ENCRYPT) अणु
		scatterwalk_map_and_copy(req->iv, req->dst,
					 req->cryptlen - ivsize, ivsize, 0);
	पूर्ण अन्यथा अणु
		अगर (req->src == req->dst)
			स_नकल(req->iv, rctx->lastc, ivsize);
		अन्यथा
			scatterwalk_map_and_copy(req->iv, req->src,
						 req->cryptlen - ivsize,
						 ivsize, 0);
	पूर्ण
पूर्ण

अटल व्योम aपंचांगel_tdes_finish_req(काष्ठा aपंचांगel_tdes_dev *dd, पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = dd->req;
	काष्ठा aपंचांगel_tdes_reqctx *rctx = skcipher_request_ctx(req);

	clk_disable_unprepare(dd->iclk);

	dd->flags &= ~TDES_FLAGS_BUSY;

	अगर (!err && (rctx->mode & TDES_FLAGS_OPMODE_MASK) != TDES_FLAGS_ECB)
		aपंचांगel_tdes_set_iv_as_last_ciphertext_block(dd);

	req->base.complete(&req->base, err);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_handle_queue(काष्ठा aपंचांगel_tdes_dev *dd,
			       काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_async_request *async_req, *backlog;
	काष्ठा aपंचांगel_tdes_ctx *ctx;
	काष्ठा aपंचांगel_tdes_reqctx *rctx;
	अचिन्हित दीर्घ flags;
	पूर्णांक err, ret = 0;

	spin_lock_irqsave(&dd->lock, flags);
	अगर (req)
		ret = crypto_enqueue_request(&dd->queue, &req->base);
	अगर (dd->flags & TDES_FLAGS_BUSY) अणु
		spin_unlock_irqrestore(&dd->lock, flags);
		वापस ret;
	पूर्ण
	backlog = crypto_get_backlog(&dd->queue);
	async_req = crypto_dequeue_request(&dd->queue);
	अगर (async_req)
		dd->flags |= TDES_FLAGS_BUSY;
	spin_unlock_irqrestore(&dd->lock, flags);

	अगर (!async_req)
		वापस ret;

	अगर (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	req = skcipher_request_cast(async_req);

	/* assign new request to device */
	dd->req = req;
	dd->total = req->cryptlen;
	dd->in_offset = 0;
	dd->in_sg = req->src;
	dd->out_offset = 0;
	dd->out_sg = req->dst;

	rctx = skcipher_request_ctx(req);
	ctx = crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	rctx->mode &= TDES_FLAGS_MODE_MASK;
	dd->flags = (dd->flags & ~TDES_FLAGS_MODE_MASK) | rctx->mode;
	dd->ctx = ctx;
	ctx->dd = dd;

	err = aपंचांगel_tdes_ग_लिखो_ctrl(dd);
	अगर (!err)
		err = aपंचांगel_tdes_crypt_start(dd);
	अगर (err) अणु
		/* des_task will not finish it, so करो it here */
		aपंचांगel_tdes_finish_req(dd, err);
		tasklet_schedule(&dd->queue_task);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_crypt_dma_stop(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	पूर्णांक err = -EINVAL;
	माप_प्रकार count;

	अगर (dd->flags & TDES_FLAGS_DMA) अणु
		err = 0;
		अगर  (dd->flags & TDES_FLAGS_FAST) अणु
			dma_unmap_sg(dd->dev, dd->out_sg, 1, DMA_FROM_DEVICE);
			dma_unmap_sg(dd->dev, dd->in_sg, 1, DMA_TO_DEVICE);
		पूर्ण अन्यथा अणु
			dma_sync_single_क्रम_device(dd->dev, dd->dma_addr_out,
				dd->dma_size, DMA_FROM_DEVICE);

			/* copy data */
			count = aपंचांगel_tdes_sg_copy(&dd->out_sg, &dd->out_offset,
				dd->buf_out, dd->buflen, dd->dma_size, 1);
			अगर (count != dd->dma_size) अणु
				err = -EINVAL;
				pr_err("not all data converted: %zu\n", count);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ mode)
अणु
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा aपंचांगel_tdes_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा aपंचांगel_tdes_reqctx *rctx = skcipher_request_ctx(req);

	चयन (mode & TDES_FLAGS_OPMODE_MASK) अणु
	हाल TDES_FLAGS_CFB8:
		अगर (!IS_ALIGNED(req->cryptlen, CFB8_BLOCK_SIZE)) अणु
			pr_err("request size is not exact amount of CFB8 blocks\n");
			वापस -EINVAL;
		पूर्ण
		ctx->block_size = CFB8_BLOCK_SIZE;
		अवरोध;

	हाल TDES_FLAGS_CFB16:
		अगर (!IS_ALIGNED(req->cryptlen, CFB16_BLOCK_SIZE)) अणु
			pr_err("request size is not exact amount of CFB16 blocks\n");
			वापस -EINVAL;
		पूर्ण
		ctx->block_size = CFB16_BLOCK_SIZE;
		अवरोध;

	हाल TDES_FLAGS_CFB32:
		अगर (!IS_ALIGNED(req->cryptlen, CFB32_BLOCK_SIZE)) अणु
			pr_err("request size is not exact amount of CFB32 blocks\n");
			वापस -EINVAL;
		पूर्ण
		ctx->block_size = CFB32_BLOCK_SIZE;
		अवरोध;

	शेष:
		अगर (!IS_ALIGNED(req->cryptlen, DES_BLOCK_SIZE)) अणु
			pr_err("request size is not exact amount of DES blocks\n");
			वापस -EINVAL;
		पूर्ण
		ctx->block_size = DES_BLOCK_SIZE;
		अवरोध;
	पूर्ण

	rctx->mode = mode;

	अगर ((mode & TDES_FLAGS_OPMODE_MASK) != TDES_FLAGS_ECB &&
	    !(mode & TDES_FLAGS_ENCRYPT) && req->src == req->dst) अणु
		अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);

		अगर (req->cryptlen >= ivsize)
			scatterwalk_map_and_copy(rctx->lastc, req->src,
						 req->cryptlen - ivsize,
						 ivsize, 0);
	पूर्ण

	वापस aपंचांगel_tdes_handle_queue(ctx->dd, req);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_dma_init(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	पूर्णांक ret;

	/* Try to grab 2 DMA channels */
	dd->dma_lch_in.chan = dma_request_chan(dd->dev, "tx");
	अगर (IS_ERR(dd->dma_lch_in.chan)) अणु
		ret = PTR_ERR(dd->dma_lch_in.chan);
		जाओ err_dma_in;
	पूर्ण

	dd->dma_lch_in.dma_conf.dst_addr = dd->phys_base +
		TDES_IDATA1R;
	dd->dma_lch_in.dma_conf.src_maxburst = 1;
	dd->dma_lch_in.dma_conf.src_addr_width =
		DMA_SLAVE_BUSWIDTH_4_BYTES;
	dd->dma_lch_in.dma_conf.dst_maxburst = 1;
	dd->dma_lch_in.dma_conf.dst_addr_width =
		DMA_SLAVE_BUSWIDTH_4_BYTES;
	dd->dma_lch_in.dma_conf.device_fc = false;

	dd->dma_lch_out.chan = dma_request_chan(dd->dev, "rx");
	अगर (IS_ERR(dd->dma_lch_out.chan)) अणु
		ret = PTR_ERR(dd->dma_lch_out.chan);
		जाओ err_dma_out;
	पूर्ण

	dd->dma_lch_out.dma_conf.src_addr = dd->phys_base +
		TDES_ODATA1R;
	dd->dma_lch_out.dma_conf.src_maxburst = 1;
	dd->dma_lch_out.dma_conf.src_addr_width =
		DMA_SLAVE_BUSWIDTH_4_BYTES;
	dd->dma_lch_out.dma_conf.dst_maxburst = 1;
	dd->dma_lch_out.dma_conf.dst_addr_width =
		DMA_SLAVE_BUSWIDTH_4_BYTES;
	dd->dma_lch_out.dma_conf.device_fc = false;

	वापस 0;

err_dma_out:
	dma_release_channel(dd->dma_lch_in.chan);
err_dma_in:
	dev_err(dd->dev, "no DMA channel available\n");
	वापस ret;
पूर्ण

अटल व्योम aपंचांगel_tdes_dma_cleanup(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	dma_release_channel(dd->dma_lch_in.chan);
	dma_release_channel(dd->dma_lch_out.chan);
पूर्ण

अटल पूर्णांक aपंचांगel_des_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा aपंचांगel_tdes_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err;

	err = verअगरy_skcipher_des_key(tfm, key);
	अगर (err)
		वापस err;

	स_नकल(ctx->key, key, keylen);
	ctx->keylen = keylen;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा aपंचांगel_tdes_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err;

	err = verअगरy_skcipher_des3_key(tfm, key);
	अगर (err)
		वापस err;

	स_नकल(ctx->key, key, keylen);
	ctx->keylen = keylen;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_ECB | TDES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_ECB);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_CBC | TDES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_CBC);
पूर्ण
अटल पूर्णांक aपंचांगel_tdes_cfb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_CFB64 | TDES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_cfb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_CFB64);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_cfb8_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_CFB8 | TDES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_cfb8_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_CFB8);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_cfb16_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_CFB16 | TDES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_cfb16_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_CFB16);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_cfb32_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_CFB32 | TDES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_cfb32_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_CFB32);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_ofb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_OFB | TDES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_ofb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_tdes_crypt(req, TDES_FLAGS_OFB);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा aपंचांगel_tdes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा aपंचांगel_tdes_dev *dd;

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा aपंचांगel_tdes_reqctx));

	dd = aपंचांगel_tdes_find_dev(ctx);
	अगर (!dd)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_tdes_skcipher_alg_init(काष्ठा skcipher_alg *alg)
अणु
	alg->base.cra_priority = ATMEL_TDES_PRIORITY;
	alg->base.cra_flags = CRYPTO_ALG_ASYNC;
	alg->base.cra_ctxsize = माप(काष्ठा aपंचांगel_tdes_ctx);
	alg->base.cra_module = THIS_MODULE;

	alg->init = aपंचांगel_tdes_init_tfm;
पूर्ण

अटल काष्ठा skcipher_alg tdes_algs[] = अणु
अणु
	.base.cra_name		= "ecb(des)",
	.base.cra_driver_name	= "atmel-ecb-des",
	.base.cra_blocksize	= DES_BLOCK_SIZE,
	.base.cra_alignmask	= 0x7,

	.min_keysize		= DES_KEY_SIZE,
	.max_keysize		= DES_KEY_SIZE,
	.setkey			= aपंचांगel_des_setkey,
	.encrypt		= aपंचांगel_tdes_ecb_encrypt,
	.decrypt		= aपंचांगel_tdes_ecb_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "cbc(des)",
	.base.cra_driver_name	= "atmel-cbc-des",
	.base.cra_blocksize	= DES_BLOCK_SIZE,
	.base.cra_alignmask	= 0x7,

	.min_keysize		= DES_KEY_SIZE,
	.max_keysize		= DES_KEY_SIZE,
	.ivsize			= DES_BLOCK_SIZE,
	.setkey			= aपंचांगel_des_setkey,
	.encrypt		= aपंचांगel_tdes_cbc_encrypt,
	.decrypt		= aपंचांगel_tdes_cbc_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "cfb(des)",
	.base.cra_driver_name	= "atmel-cfb-des",
	.base.cra_blocksize	= DES_BLOCK_SIZE,
	.base.cra_alignmask	= 0x7,

	.min_keysize		= DES_KEY_SIZE,
	.max_keysize		= DES_KEY_SIZE,
	.ivsize			= DES_BLOCK_SIZE,
	.setkey			= aपंचांगel_des_setkey,
	.encrypt		= aपंचांगel_tdes_cfb_encrypt,
	.decrypt		= aपंचांगel_tdes_cfb_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "cfb8(des)",
	.base.cra_driver_name	= "atmel-cfb8-des",
	.base.cra_blocksize	= CFB8_BLOCK_SIZE,
	.base.cra_alignmask	= 0,

	.min_keysize		= DES_KEY_SIZE,
	.max_keysize		= DES_KEY_SIZE,
	.ivsize			= DES_BLOCK_SIZE,
	.setkey			= aपंचांगel_des_setkey,
	.encrypt		= aपंचांगel_tdes_cfb8_encrypt,
	.decrypt		= aपंचांगel_tdes_cfb8_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "cfb16(des)",
	.base.cra_driver_name	= "atmel-cfb16-des",
	.base.cra_blocksize	= CFB16_BLOCK_SIZE,
	.base.cra_alignmask	= 0x1,

	.min_keysize		= DES_KEY_SIZE,
	.max_keysize		= DES_KEY_SIZE,
	.ivsize			= DES_BLOCK_SIZE,
	.setkey			= aपंचांगel_des_setkey,
	.encrypt		= aपंचांगel_tdes_cfb16_encrypt,
	.decrypt		= aपंचांगel_tdes_cfb16_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "cfb32(des)",
	.base.cra_driver_name	= "atmel-cfb32-des",
	.base.cra_blocksize	= CFB32_BLOCK_SIZE,
	.base.cra_alignmask	= 0x3,

	.min_keysize		= DES_KEY_SIZE,
	.max_keysize		= DES_KEY_SIZE,
	.ivsize			= DES_BLOCK_SIZE,
	.setkey			= aपंचांगel_des_setkey,
	.encrypt		= aपंचांगel_tdes_cfb32_encrypt,
	.decrypt		= aपंचांगel_tdes_cfb32_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "ofb(des)",
	.base.cra_driver_name	= "atmel-ofb-des",
	.base.cra_blocksize	= DES_BLOCK_SIZE,
	.base.cra_alignmask	= 0x7,

	.min_keysize		= DES_KEY_SIZE,
	.max_keysize		= DES_KEY_SIZE,
	.ivsize			= DES_BLOCK_SIZE,
	.setkey			= aपंचांगel_des_setkey,
	.encrypt		= aपंचांगel_tdes_ofb_encrypt,
	.decrypt		= aपंचांगel_tdes_ofb_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "ecb(des3_ede)",
	.base.cra_driver_name	= "atmel-ecb-tdes",
	.base.cra_blocksize	= DES_BLOCK_SIZE,
	.base.cra_alignmask	= 0x7,

	.min_keysize		= DES3_EDE_KEY_SIZE,
	.max_keysize		= DES3_EDE_KEY_SIZE,
	.setkey			= aपंचांगel_tdes_setkey,
	.encrypt		= aपंचांगel_tdes_ecb_encrypt,
	.decrypt		= aपंचांगel_tdes_ecb_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "cbc(des3_ede)",
	.base.cra_driver_name	= "atmel-cbc-tdes",
	.base.cra_blocksize	= DES_BLOCK_SIZE,
	.base.cra_alignmask	= 0x7,

	.min_keysize		= DES3_EDE_KEY_SIZE,
	.max_keysize		= DES3_EDE_KEY_SIZE,
	.setkey			= aपंचांगel_tdes_setkey,
	.encrypt		= aपंचांगel_tdes_cbc_encrypt,
	.decrypt		= aपंचांगel_tdes_cbc_decrypt,
	.ivsize			= DES_BLOCK_SIZE,
पूर्ण,
अणु
	.base.cra_name		= "ofb(des3_ede)",
	.base.cra_driver_name	= "atmel-ofb-tdes",
	.base.cra_blocksize	= DES_BLOCK_SIZE,
	.base.cra_alignmask	= 0x7,

	.min_keysize		= DES3_EDE_KEY_SIZE,
	.max_keysize		= DES3_EDE_KEY_SIZE,
	.setkey			= aपंचांगel_tdes_setkey,
	.encrypt		= aपंचांगel_tdes_ofb_encrypt,
	.decrypt		= aपंचांगel_tdes_ofb_decrypt,
	.ivsize			= DES_BLOCK_SIZE,
पूर्ण,
पूर्ण;

अटल व्योम aपंचांगel_tdes_queue_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा aपंचांगel_tdes_dev *dd = (काष्ठा aपंचांगel_tdes_dev *)data;

	aपंचांगel_tdes_handle_queue(dd, शून्य);
पूर्ण

अटल व्योम aपंचांगel_tdes_करोne_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा aपंचांगel_tdes_dev *dd = (काष्ठा aपंचांगel_tdes_dev *) data;
	पूर्णांक err;

	अगर (!(dd->flags & TDES_FLAGS_DMA))
		err = aपंचांगel_tdes_crypt_pdc_stop(dd);
	अन्यथा
		err = aपंचांगel_tdes_crypt_dma_stop(dd);

	अगर (dd->total && !err) अणु
		अगर (dd->flags & TDES_FLAGS_FAST) अणु
			dd->in_sg = sg_next(dd->in_sg);
			dd->out_sg = sg_next(dd->out_sg);
			अगर (!dd->in_sg || !dd->out_sg)
				err = -EINVAL;
		पूर्ण
		अगर (!err)
			err = aपंचांगel_tdes_crypt_start(dd);
		अगर (!err)
			वापस; /* DMA started. Not fininishing. */
	पूर्ण

	aपंचांगel_tdes_finish_req(dd, err);
	aपंचांगel_tdes_handle_queue(dd, शून्य);
पूर्ण

अटल irqवापस_t aपंचांगel_tdes_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aपंचांगel_tdes_dev *tdes_dd = dev_id;
	u32 reg;

	reg = aपंचांगel_tdes_पढ़ो(tdes_dd, TDES_ISR);
	अगर (reg & aपंचांगel_tdes_पढ़ो(tdes_dd, TDES_IMR)) अणु
		aपंचांगel_tdes_ग_लिखो(tdes_dd, TDES_IDR, reg);
		अगर (TDES_FLAGS_BUSY & tdes_dd->flags)
			tasklet_schedule(&tdes_dd->करोne_task);
		अन्यथा
			dev_warn(tdes_dd->dev, "TDES interrupt when no active requests.\n");
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल व्योम aपंचांगel_tdes_unरेजिस्टर_algs(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tdes_algs); i++)
		crypto_unरेजिस्टर_skcipher(&tdes_algs[i]);
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_रेजिस्टर_algs(काष्ठा aपंचांगel_tdes_dev *dd)
अणु
	पूर्णांक err, i, j;

	क्रम (i = 0; i < ARRAY_SIZE(tdes_algs); i++) अणु
		aपंचांगel_tdes_skcipher_alg_init(&tdes_algs[i]);

		err = crypto_रेजिस्टर_skcipher(&tdes_algs[i]);
		अगर (err)
			जाओ err_tdes_algs;
	पूर्ण

	वापस 0;

err_tdes_algs:
	क्रम (j = 0; j < i; j++)
		crypto_unरेजिस्टर_skcipher(&tdes_algs[j]);

	वापस err;
पूर्ण

अटल व्योम aपंचांगel_tdes_get_cap(काष्ठा aपंचांगel_tdes_dev *dd)
अणु

	dd->caps.has_dma = 0;
	dd->caps.has_cfb_3keys = 0;

	/* keep only major version number */
	चयन (dd->hw_version & 0xf00) अणु
	हाल 0x700:
		dd->caps.has_dma = 1;
		dd->caps.has_cfb_3keys = 1;
		अवरोध;
	हाल 0x600:
		अवरोध;
	शेष:
		dev_warn(dd->dev,
				"Unmanaged tdes version, set minimum capabilities\n");
		अवरोध;
	पूर्ण
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id aपंचांगel_tdes_dt_ids[] = अणु
	अणु .compatible = "atmel,at91sam9g46-tdes" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_tdes_dt_ids);
#पूर्ण_अगर

अटल पूर्णांक aपंचांगel_tdes_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_tdes_dev *tdes_dd;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *tdes_res;
	पूर्णांक err;

	tdes_dd = devm_kदो_स्मृति(&pdev->dev, माप(*tdes_dd), GFP_KERNEL);
	अगर (!tdes_dd)
		वापस -ENOMEM;

	tdes_dd->dev = dev;

	platक्रमm_set_drvdata(pdev, tdes_dd);

	INIT_LIST_HEAD(&tdes_dd->list);
	spin_lock_init(&tdes_dd->lock);

	tasklet_init(&tdes_dd->करोne_task, aपंचांगel_tdes_करोne_task,
					(अचिन्हित दीर्घ)tdes_dd);
	tasklet_init(&tdes_dd->queue_task, aपंचांगel_tdes_queue_task,
					(अचिन्हित दीर्घ)tdes_dd);

	crypto_init_queue(&tdes_dd->queue, ATMEL_TDES_QUEUE_LENGTH);

	/* Get the base address */
	tdes_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!tdes_res) अणु
		dev_err(dev, "no MEM resource info\n");
		err = -ENODEV;
		जाओ err_tasklet_समाप्त;
	पूर्ण
	tdes_dd->phys_base = tdes_res->start;

	/* Get the IRQ */
	tdes_dd->irq = platक्रमm_get_irq(pdev,  0);
	अगर (tdes_dd->irq < 0) अणु
		err = tdes_dd->irq;
		जाओ err_tasklet_समाप्त;
	पूर्ण

	err = devm_request_irq(&pdev->dev, tdes_dd->irq, aपंचांगel_tdes_irq,
			       IRQF_SHARED, "atmel-tdes", tdes_dd);
	अगर (err) अणु
		dev_err(dev, "unable to request tdes irq.\n");
		जाओ err_tasklet_समाप्त;
	पूर्ण

	/* Initializing the घड़ी */
	tdes_dd->iclk = devm_clk_get(&pdev->dev, "tdes_clk");
	अगर (IS_ERR(tdes_dd->iclk)) अणु
		dev_err(dev, "clock initialization failed.\n");
		err = PTR_ERR(tdes_dd->iclk);
		जाओ err_tasklet_समाप्त;
	पूर्ण

	tdes_dd->io_base = devm_ioremap_resource(&pdev->dev, tdes_res);
	अगर (IS_ERR(tdes_dd->io_base)) अणु
		err = PTR_ERR(tdes_dd->io_base);
		जाओ err_tasklet_समाप्त;
	पूर्ण

	err = aपंचांगel_tdes_hw_version_init(tdes_dd);
	अगर (err)
		जाओ err_tasklet_समाप्त;

	aपंचांगel_tdes_get_cap(tdes_dd);

	err = aपंचांगel_tdes_buff_init(tdes_dd);
	अगर (err)
		जाओ err_tasklet_समाप्त;

	अगर (tdes_dd->caps.has_dma) अणु
		err = aपंचांगel_tdes_dma_init(tdes_dd);
		अगर (err)
			जाओ err_buff_cleanup;

		dev_info(dev, "using %s, %s for DMA transfers\n",
				dma_chan_name(tdes_dd->dma_lch_in.chan),
				dma_chan_name(tdes_dd->dma_lch_out.chan));
	पूर्ण

	spin_lock(&aपंचांगel_tdes.lock);
	list_add_tail(&tdes_dd->list, &aपंचांगel_tdes.dev_list);
	spin_unlock(&aपंचांगel_tdes.lock);

	err = aपंचांगel_tdes_रेजिस्टर_algs(tdes_dd);
	अगर (err)
		जाओ err_algs;

	dev_info(dev, "Atmel DES/TDES\n");

	वापस 0;

err_algs:
	spin_lock(&aपंचांगel_tdes.lock);
	list_del(&tdes_dd->list);
	spin_unlock(&aपंचांगel_tdes.lock);
	अगर (tdes_dd->caps.has_dma)
		aपंचांगel_tdes_dma_cleanup(tdes_dd);
err_buff_cleanup:
	aपंचांगel_tdes_buff_cleanup(tdes_dd);
err_tasklet_समाप्त:
	tasklet_समाप्त(&tdes_dd->करोne_task);
	tasklet_समाप्त(&tdes_dd->queue_task);

	वापस err;
पूर्ण

अटल पूर्णांक aपंचांगel_tdes_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_tdes_dev *tdes_dd;

	tdes_dd = platक्रमm_get_drvdata(pdev);
	अगर (!tdes_dd)
		वापस -ENODEV;
	spin_lock(&aपंचांगel_tdes.lock);
	list_del(&tdes_dd->list);
	spin_unlock(&aपंचांगel_tdes.lock);

	aपंचांगel_tdes_unरेजिस्टर_algs(tdes_dd);

	tasklet_समाप्त(&tdes_dd->करोne_task);
	tasklet_समाप्त(&tdes_dd->queue_task);

	अगर (tdes_dd->caps.has_dma)
		aपंचांगel_tdes_dma_cleanup(tdes_dd);

	aपंचांगel_tdes_buff_cleanup(tdes_dd);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aपंचांगel_tdes_driver = अणु
	.probe		= aपंचांगel_tdes_probe,
	.हटाओ		= aपंचांगel_tdes_हटाओ,
	.driver		= अणु
		.name	= "atmel_tdes",
		.of_match_table = of_match_ptr(aपंचांगel_tdes_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(aपंचांगel_tdes_driver);

MODULE_DESCRIPTION("Atmel DES/TDES hw acceleration support.");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Nicolas Royer - Eukrथऊa Electromatique");
