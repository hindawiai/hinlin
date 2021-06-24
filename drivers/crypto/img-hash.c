<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Imagination Technologies
 * Authors:  Will Thomas, James Hartley
 *
 *	Interface काष्ठाure taken from omap-sham driver
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/md5.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>

#घोषणा CR_RESET			0
#घोषणा CR_RESET_SET			1
#घोषणा CR_RESET_UNSET			0

#घोषणा CR_MESSAGE_LENGTH_H		0x4
#घोषणा CR_MESSAGE_LENGTH_L		0x8

#घोषणा CR_CONTROL			0xc
#घोषणा CR_CONTROL_BYTE_ORDER_3210	0
#घोषणा CR_CONTROL_BYTE_ORDER_0123	1
#घोषणा CR_CONTROL_BYTE_ORDER_2310	2
#घोषणा CR_CONTROL_BYTE_ORDER_1032	3
#घोषणा CR_CONTROL_BYTE_ORDER_SHIFT	8
#घोषणा CR_CONTROL_ALGO_MD5	0
#घोषणा CR_CONTROL_ALGO_SHA1	1
#घोषणा CR_CONTROL_ALGO_SHA224	2
#घोषणा CR_CONTROL_ALGO_SHA256	3

#घोषणा CR_INTSTAT			0x10
#घोषणा CR_INTENAB			0x14
#घोषणा CR_INTCLEAR			0x18
#घोषणा CR_INT_RESULTS_AVAILABLE	BIT(0)
#घोषणा CR_INT_NEW_RESULTS_SET		BIT(1)
#घोषणा CR_INT_RESULT_READ_ERR		BIT(2)
#घोषणा CR_INT_MESSAGE_WRITE_ERROR	BIT(3)
#घोषणा CR_INT_STATUS			BIT(8)

#घोषणा CR_RESULT_QUEUE		0x1c
#घोषणा CR_RSD0				0x40
#घोषणा CR_CORE_REV			0x50
#घोषणा CR_CORE_DES1		0x60
#घोषणा CR_CORE_DES2		0x70

#घोषणा DRIVER_FLAGS_BUSY		BIT(0)
#घोषणा DRIVER_FLAGS_FINAL		BIT(1)
#घोषणा DRIVER_FLAGS_DMA_ACTIVE		BIT(2)
#घोषणा DRIVER_FLAGS_OUTPUT_READY	BIT(3)
#घोषणा DRIVER_FLAGS_INIT		BIT(4)
#घोषणा DRIVER_FLAGS_CPU		BIT(5)
#घोषणा DRIVER_FLAGS_DMA_READY		BIT(6)
#घोषणा DRIVER_FLAGS_ERROR		BIT(7)
#घोषणा DRIVER_FLAGS_SG			BIT(8)
#घोषणा DRIVER_FLAGS_SHA1		BIT(18)
#घोषणा DRIVER_FLAGS_SHA224		BIT(19)
#घोषणा DRIVER_FLAGS_SHA256		BIT(20)
#घोषणा DRIVER_FLAGS_MD5		BIT(21)

#घोषणा IMG_HASH_QUEUE_LENGTH		20
#घोषणा IMG_HASH_DMA_BURST		4
#घोषणा IMG_HASH_DMA_THRESHOLD		64

#अगर_घोषित __LITTLE_ENDIAN
#घोषणा IMG_HASH_BYTE_ORDER		CR_CONTROL_BYTE_ORDER_3210
#अन्यथा
#घोषणा IMG_HASH_BYTE_ORDER		CR_CONTROL_BYTE_ORDER_0123
#पूर्ण_अगर

काष्ठा img_hash_dev;

काष्ठा img_hash_request_ctx अणु
	काष्ठा img_hash_dev	*hdev;
	u8 digest[SHA256_DIGEST_SIZE] __aligned(माप(u32));
	अचिन्हित दीर्घ		flags;
	माप_प्रकार			digsize;

	dma_addr_t		dma_addr;
	माप_प्रकार			dma_ct;

	/* sg root */
	काष्ठा scatterlist	*sgfirst;
	/* walk state */
	काष्ठा scatterlist	*sg;
	माप_प्रकार			nents;
	माप_प्रकार			offset;
	अचिन्हित पूर्णांक		total;
	माप_प्रकार			sent;

	अचिन्हित दीर्घ		op;

	माप_प्रकार			bufcnt;
	काष्ठा ahash_request	fallback_req;

	/* Zero length buffer must reमुख्य last member of काष्ठा */
	u8 buffer[] __aligned(माप(u32));
पूर्ण;

काष्ठा img_hash_ctx अणु
	काष्ठा img_hash_dev	*hdev;
	अचिन्हित दीर्घ		flags;
	काष्ठा crypto_ahash	*fallback;
पूर्ण;

काष्ठा img_hash_dev अणु
	काष्ठा list_head	list;
	काष्ठा device		*dev;
	काष्ठा clk		*hash_clk;
	काष्ठा clk		*sys_clk;
	व्योम __iomem		*io_base;

	phys_addr_t		bus_addr;
	व्योम __iomem		*cpu_addr;

	spinlock_t		lock;
	पूर्णांक			err;
	काष्ठा tasklet_काष्ठा	करोne_task;
	काष्ठा tasklet_काष्ठा	dma_task;

	अचिन्हित दीर्घ		flags;
	काष्ठा crypto_queue	queue;
	काष्ठा ahash_request	*req;

	काष्ठा dma_chan		*dma_lch;
पूर्ण;

काष्ठा img_hash_drv अणु
	काष्ठा list_head dev_list;
	spinlock_t lock;
पूर्ण;

अटल काष्ठा img_hash_drv img_hash = अणु
	.dev_list = LIST_HEAD_INIT(img_hash.dev_list),
	.lock = __SPIN_LOCK_UNLOCKED(img_hash.lock),
पूर्ण;

अटल अंतरभूत u32 img_hash_पढ़ो(काष्ठा img_hash_dev *hdev, u32 offset)
अणु
	वापस पढ़ोl_relaxed(hdev->io_base + offset);
पूर्ण

अटल अंतरभूत व्योम img_hash_ग_लिखो(काष्ठा img_hash_dev *hdev,
				  u32 offset, u32 value)
अणु
	ग_लिखोl_relaxed(value, hdev->io_base + offset);
पूर्ण

अटल अंतरभूत u32 img_hash_पढ़ो_result_queue(काष्ठा img_hash_dev *hdev)
अणु
	वापस be32_to_cpu(img_hash_पढ़ो(hdev, CR_RESULT_QUEUE));
पूर्ण

अटल व्योम img_hash_start(काष्ठा img_hash_dev *hdev, bool dma)
अणु
	काष्ठा img_hash_request_ctx *ctx = ahash_request_ctx(hdev->req);
	u32 cr = IMG_HASH_BYTE_ORDER << CR_CONTROL_BYTE_ORDER_SHIFT;

	अगर (ctx->flags & DRIVER_FLAGS_MD5)
		cr |= CR_CONTROL_ALGO_MD5;
	अन्यथा अगर (ctx->flags & DRIVER_FLAGS_SHA1)
		cr |= CR_CONTROL_ALGO_SHA1;
	अन्यथा अगर (ctx->flags & DRIVER_FLAGS_SHA224)
		cr |= CR_CONTROL_ALGO_SHA224;
	अन्यथा अगर (ctx->flags & DRIVER_FLAGS_SHA256)
		cr |= CR_CONTROL_ALGO_SHA256;
	dev_dbg(hdev->dev, "Starting hash process\n");
	img_hash_ग_लिखो(hdev, CR_CONTROL, cr);

	/*
	 * The hardware block requires two cycles between writing the control
	 * रेजिस्टर and writing the first word of data in non DMA mode, to
	 * ensure the first data ग_लिखो is not grouped in burst with the control
	 * रेजिस्टर ग_लिखो a पढ़ो is issued to 'flush' the bus.
	 */
	अगर (!dma)
		img_hash_पढ़ो(hdev, CR_CONTROL);
पूर्ण

अटल पूर्णांक img_hash_xmit_cpu(काष्ठा img_hash_dev *hdev, स्थिर u8 *buf,
			     माप_प्रकार length, पूर्णांक final)
अणु
	u32 count, len32;
	स्थिर u32 *buffer = (स्थिर u32 *)buf;

	dev_dbg(hdev->dev, "xmit_cpu:  length: %zu bytes\n", length);

	अगर (final)
		hdev->flags |= DRIVER_FLAGS_FINAL;

	len32 = DIV_ROUND_UP(length, माप(u32));

	क्रम (count = 0; count < len32; count++)
		ग_लिखोl_relaxed(buffer[count], hdev->cpu_addr);

	वापस -EINPROGRESS;
पूर्ण

अटल व्योम img_hash_dma_callback(व्योम *data)
अणु
	काष्ठा img_hash_dev *hdev = (काष्ठा img_hash_dev *)data;
	काष्ठा img_hash_request_ctx *ctx = ahash_request_ctx(hdev->req);

	अगर (ctx->bufcnt) अणु
		img_hash_xmit_cpu(hdev, ctx->buffer, ctx->bufcnt, 0);
		ctx->bufcnt = 0;
	पूर्ण
	अगर (ctx->sg)
		tasklet_schedule(&hdev->dma_task);
पूर्ण

अटल पूर्णांक img_hash_xmit_dma(काष्ठा img_hash_dev *hdev, काष्ठा scatterlist *sg)
अणु
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा img_hash_request_ctx *ctx = ahash_request_ctx(hdev->req);

	ctx->dma_ct = dma_map_sg(hdev->dev, sg, 1, DMA_TO_DEVICE);
	अगर (ctx->dma_ct == 0) अणु
		dev_err(hdev->dev, "Invalid DMA sg\n");
		hdev->err = -EINVAL;
		वापस -EINVAL;
	पूर्ण

	desc = dmaengine_prep_slave_sg(hdev->dma_lch,
				       sg,
				       ctx->dma_ct,
				       DMA_MEM_TO_DEV,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		dev_err(hdev->dev, "Null DMA descriptor\n");
		hdev->err = -EINVAL;
		dma_unmap_sg(hdev->dev, sg, 1, DMA_TO_DEVICE);
		वापस -EINVAL;
	पूर्ण
	desc->callback = img_hash_dma_callback;
	desc->callback_param = hdev;
	dmaengine_submit(desc);
	dma_async_issue_pending(hdev->dma_lch);

	वापस 0;
पूर्ण

अटल पूर्णांक img_hash_ग_लिखो_via_cpu(काष्ठा img_hash_dev *hdev)
अणु
	काष्ठा img_hash_request_ctx *ctx = ahash_request_ctx(hdev->req);

	ctx->bufcnt = sg_copy_to_buffer(hdev->req->src, sg_nents(ctx->sg),
					ctx->buffer, hdev->req->nbytes);

	ctx->total = hdev->req->nbytes;
	ctx->bufcnt = 0;

	hdev->flags |= (DRIVER_FLAGS_CPU | DRIVER_FLAGS_FINAL);

	img_hash_start(hdev, false);

	वापस img_hash_xmit_cpu(hdev, ctx->buffer, ctx->total, 1);
पूर्ण

अटल पूर्णांक img_hash_finish(काष्ठा ahash_request *req)
अणु
	काष्ठा img_hash_request_ctx *ctx = ahash_request_ctx(req);

	अगर (!req->result)
		वापस -EINVAL;

	स_नकल(req->result, ctx->digest, ctx->digsize);

	वापस 0;
पूर्ण

अटल व्योम img_hash_copy_hash(काष्ठा ahash_request *req)
अणु
	काष्ठा img_hash_request_ctx *ctx = ahash_request_ctx(req);
	u32 *hash = (u32 *)ctx->digest;
	पूर्णांक i;

	क्रम (i = (ctx->digsize / माप(u32)) - 1; i >= 0; i--)
		hash[i] = img_hash_पढ़ो_result_queue(ctx->hdev);
पूर्ण

अटल व्योम img_hash_finish_req(काष्ठा ahash_request *req, पूर्णांक err)
अणु
	काष्ठा img_hash_request_ctx *ctx = ahash_request_ctx(req);
	काष्ठा img_hash_dev *hdev =  ctx->hdev;

	अगर (!err) अणु
		img_hash_copy_hash(req);
		अगर (DRIVER_FLAGS_FINAL & hdev->flags)
			err = img_hash_finish(req);
	पूर्ण अन्यथा अणु
		dev_warn(hdev->dev, "Hash failed with error %d\n", err);
		ctx->flags |= DRIVER_FLAGS_ERROR;
	पूर्ण

	hdev->flags &= ~(DRIVER_FLAGS_DMA_READY | DRIVER_FLAGS_OUTPUT_READY |
		DRIVER_FLAGS_CPU | DRIVER_FLAGS_BUSY | DRIVER_FLAGS_FINAL);

	अगर (req->base.complete)
		req->base.complete(&req->base, err);
पूर्ण

अटल पूर्णांक img_hash_ग_लिखो_via_dma(काष्ठा img_hash_dev *hdev)
अणु
	काष्ठा img_hash_request_ctx *ctx = ahash_request_ctx(hdev->req);

	img_hash_start(hdev, true);

	dev_dbg(hdev->dev, "xmit dma size: %d\n", ctx->total);

	अगर (!ctx->total)
		hdev->flags |= DRIVER_FLAGS_FINAL;

	hdev->flags |= DRIVER_FLAGS_DMA_ACTIVE | DRIVER_FLAGS_FINAL;

	tasklet_schedule(&hdev->dma_task);

	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक img_hash_dma_init(काष्ठा img_hash_dev *hdev)
अणु
	काष्ठा dma_slave_config dma_conf;
	पूर्णांक err;

	hdev->dma_lch = dma_request_chan(hdev->dev, "tx");
	अगर (IS_ERR(hdev->dma_lch)) अणु
		dev_err(hdev->dev, "Couldn't acquire a slave DMA channel.\n");
		वापस PTR_ERR(hdev->dma_lch);
	पूर्ण
	dma_conf.direction = DMA_MEM_TO_DEV;
	dma_conf.dst_addr = hdev->bus_addr;
	dma_conf.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	dma_conf.dst_maxburst = IMG_HASH_DMA_BURST;
	dma_conf.device_fc = false;

	err = dmaengine_slave_config(hdev->dma_lch,  &dma_conf);
	अगर (err) अणु
		dev_err(hdev->dev, "Couldn't configure DMA slave.\n");
		dma_release_channel(hdev->dma_lch);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम img_hash_dma_task(अचिन्हित दीर्घ d)
अणु
	काष्ठा img_hash_dev *hdev = (काष्ठा img_hash_dev *)d;
	काष्ठा img_hash_request_ctx *ctx = ahash_request_ctx(hdev->req);
	u8 *addr;
	माप_प्रकार nbytes, bleft, wsend, len, tbc;
	काष्ठा scatterlist tsg;

	अगर (!hdev->req || !ctx->sg)
		वापस;

	addr = sg_virt(ctx->sg);
	nbytes = ctx->sg->length - ctx->offset;

	/*
	 * The hash accelerator करोes not support a data valid mask. This means
	 * that अगर each dma (i.e. per page) is not a multiple of 4 bytes, the
	 * padding bytes in the last word written by that dma would erroneously
	 * be included in the hash. To aव्योम this we round करोwn the transfer,
	 * and add the excess to the start of the next dma. It करोes not matter
	 * that the final dma may not be a multiple of 4 bytes as the hashing
	 * block is programmed to accept the correct number of bytes.
	 */

	bleft = nbytes % 4;
	wsend = (nbytes / 4);

	अगर (wsend) अणु
		sg_init_one(&tsg, addr + ctx->offset, wsend * 4);
		अगर (img_hash_xmit_dma(hdev, &tsg)) अणु
			dev_err(hdev->dev, "DMA failed, falling back to CPU");
			ctx->flags |= DRIVER_FLAGS_CPU;
			hdev->err = 0;
			img_hash_xmit_cpu(hdev, addr + ctx->offset,
					  wsend * 4, 0);
			ctx->sent += wsend * 4;
			wsend = 0;
		पूर्ण अन्यथा अणु
			ctx->sent += wsend * 4;
		पूर्ण
	पूर्ण

	अगर (bleft) अणु
		ctx->bufcnt = sg_pcopy_to_buffer(ctx->sgfirst, ctx->nents,
						 ctx->buffer, bleft, ctx->sent);
		tbc = 0;
		ctx->sg = sg_next(ctx->sg);
		जबतक (ctx->sg && (ctx->bufcnt < 4)) अणु
			len = ctx->sg->length;
			अगर (likely(len > (4 - ctx->bufcnt)))
				len = 4 - ctx->bufcnt;
			tbc = sg_pcopy_to_buffer(ctx->sgfirst, ctx->nents,
						 ctx->buffer + ctx->bufcnt, len,
					ctx->sent + ctx->bufcnt);
			ctx->bufcnt += tbc;
			अगर (tbc >= ctx->sg->length) अणु
				ctx->sg = sg_next(ctx->sg);
				tbc = 0;
			पूर्ण
		पूर्ण

		ctx->sent += ctx->bufcnt;
		ctx->offset = tbc;

		अगर (!wsend)
			img_hash_dma_callback(hdev);
	पूर्ण अन्यथा अणु
		ctx->offset = 0;
		ctx->sg = sg_next(ctx->sg);
	पूर्ण
पूर्ण

अटल पूर्णांक img_hash_ग_लिखो_via_dma_stop(काष्ठा img_hash_dev *hdev)
अणु
	काष्ठा img_hash_request_ctx *ctx = ahash_request_ctx(hdev->req);

	अगर (ctx->flags & DRIVER_FLAGS_SG)
		dma_unmap_sg(hdev->dev, ctx->sg, ctx->dma_ct, DMA_TO_DEVICE);

	वापस 0;
पूर्ण

अटल पूर्णांक img_hash_process_data(काष्ठा img_hash_dev *hdev)
अणु
	काष्ठा ahash_request *req = hdev->req;
	काष्ठा img_hash_request_ctx *ctx = ahash_request_ctx(req);
	पूर्णांक err = 0;

	ctx->bufcnt = 0;

	अगर (req->nbytes >= IMG_HASH_DMA_THRESHOLD) अणु
		dev_dbg(hdev->dev, "process data request(%d bytes) using DMA\n",
			req->nbytes);
		err = img_hash_ग_लिखो_via_dma(hdev);
	पूर्ण अन्यथा अणु
		dev_dbg(hdev->dev, "process data request(%d bytes) using CPU\n",
			req->nbytes);
		err = img_hash_ग_लिखो_via_cpu(hdev);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक img_hash_hw_init(काष्ठा img_hash_dev *hdev)
अणु
	अचिन्हित दीर्घ दीर्घ nbits;
	u32 u, l;

	img_hash_ग_लिखो(hdev, CR_RESET, CR_RESET_SET);
	img_hash_ग_लिखो(hdev, CR_RESET, CR_RESET_UNSET);
	img_hash_ग_लिखो(hdev, CR_INTENAB, CR_INT_NEW_RESULTS_SET);

	nbits = (u64)hdev->req->nbytes << 3;
	u = nbits >> 32;
	l = nbits;
	img_hash_ग_लिखो(hdev, CR_MESSAGE_LENGTH_H, u);
	img_hash_ग_लिखो(hdev, CR_MESSAGE_LENGTH_L, l);

	अगर (!(DRIVER_FLAGS_INIT & hdev->flags)) अणु
		hdev->flags |= DRIVER_FLAGS_INIT;
		hdev->err = 0;
	पूर्ण
	dev_dbg(hdev->dev, "hw initialized, nbits: %llx\n", nbits);
	वापस 0;
पूर्ण

अटल पूर्णांक img_hash_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा img_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा img_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback);
	rctx->fallback_req.base.flags =	req->base.flags
		& CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_init(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक img_hash_handle_queue(काष्ठा img_hash_dev *hdev,
				 काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_async_request *async_req, *backlog;
	काष्ठा img_hash_request_ctx *ctx;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0, res = 0;

	spin_lock_irqsave(&hdev->lock, flags);

	अगर (req)
		res = ahash_enqueue_request(&hdev->queue, req);

	अगर (DRIVER_FLAGS_BUSY & hdev->flags) अणु
		spin_unlock_irqrestore(&hdev->lock, flags);
		वापस res;
	पूर्ण

	backlog = crypto_get_backlog(&hdev->queue);
	async_req = crypto_dequeue_request(&hdev->queue);
	अगर (async_req)
		hdev->flags |= DRIVER_FLAGS_BUSY;

	spin_unlock_irqrestore(&hdev->lock, flags);

	अगर (!async_req)
		वापस res;

	अगर (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	req = ahash_request_cast(async_req);
	hdev->req = req;

	ctx = ahash_request_ctx(req);

	dev_info(hdev->dev, "processing req, op: %lu, bytes: %d\n",
		 ctx->op, req->nbytes);

	err = img_hash_hw_init(hdev);

	अगर (!err)
		err = img_hash_process_data(hdev);

	अगर (err != -EINPROGRESS) अणु
		/* करोne_task will not finish so करो it here */
		img_hash_finish_req(req, err);
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक img_hash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा img_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा img_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback);
	rctx->fallback_req.base.flags = req->base.flags
		& CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.nbytes = req->nbytes;
	rctx->fallback_req.src = req->src;

	वापस crypto_ahash_update(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक img_hash_final(काष्ठा ahash_request *req)
अणु
	काष्ठा img_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा img_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback);
	rctx->fallback_req.base.flags = req->base.flags
		& CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.result = req->result;

	वापस crypto_ahash_final(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक img_hash_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा img_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा img_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback);
	rctx->fallback_req.base.flags = req->base.flags
		& CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.nbytes = req->nbytes;
	rctx->fallback_req.src = req->src;
	rctx->fallback_req.result = req->result;

	वापस crypto_ahash_finup(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक img_hash_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा img_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा img_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback);
	rctx->fallback_req.base.flags = req->base.flags
		& CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_import(&rctx->fallback_req, in);
पूर्ण

अटल पूर्णांक img_hash_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा img_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा img_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback);
	rctx->fallback_req.base.flags = req->base.flags
		& CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_export(&rctx->fallback_req, out);
पूर्ण

अटल पूर्णांक img_hash_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा img_hash_ctx *tctx = crypto_ahash_ctx(tfm);
	काष्ठा img_hash_request_ctx *ctx = ahash_request_ctx(req);
	काष्ठा img_hash_dev *hdev = शून्य;
	काष्ठा img_hash_dev *पंचांगp;
	पूर्णांक err;

	spin_lock(&img_hash.lock);
	अगर (!tctx->hdev) अणु
		list_क्रम_each_entry(पंचांगp, &img_hash.dev_list, list) अणु
			hdev = पंचांगp;
			अवरोध;
		पूर्ण
		tctx->hdev = hdev;

	पूर्ण अन्यथा अणु
		hdev = tctx->hdev;
	पूर्ण

	spin_unlock(&img_hash.lock);
	ctx->hdev = hdev;
	ctx->flags = 0;
	ctx->digsize = crypto_ahash_digestsize(tfm);

	चयन (ctx->digsize) अणु
	हाल SHA1_DIGEST_SIZE:
		ctx->flags |= DRIVER_FLAGS_SHA1;
		अवरोध;
	हाल SHA256_DIGEST_SIZE:
		ctx->flags |= DRIVER_FLAGS_SHA256;
		अवरोध;
	हाल SHA224_DIGEST_SIZE:
		ctx->flags |= DRIVER_FLAGS_SHA224;
		अवरोध;
	हाल MD5_DIGEST_SIZE:
		ctx->flags |= DRIVER_FLAGS_MD5;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ctx->bufcnt = 0;
	ctx->offset = 0;
	ctx->sent = 0;
	ctx->total = req->nbytes;
	ctx->sg = req->src;
	ctx->sgfirst = req->src;
	ctx->nents = sg_nents(ctx->sg);

	err = img_hash_handle_queue(tctx->hdev, req);

	वापस err;
पूर्ण

अटल पूर्णांक img_hash_cra_init(काष्ठा crypto_tfm *tfm, स्थिर अक्षर *alg_name)
अणु
	काष्ठा img_hash_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक err = -ENOMEM;

	ctx->fallback = crypto_alloc_ahash(alg_name, 0,
					   CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(ctx->fallback)) अणु
		pr_err("img_hash: Could not load fallback driver.\n");
		err = PTR_ERR(ctx->fallback);
		जाओ err;
	पूर्ण
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा img_hash_request_ctx) +
				 crypto_ahash_reqsize(ctx->fallback) +
				 IMG_HASH_DMA_THRESHOLD);

	वापस 0;

err:
	वापस err;
पूर्ण

अटल पूर्णांक img_hash_cra_md5_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस img_hash_cra_init(tfm, "md5-generic");
पूर्ण

अटल पूर्णांक img_hash_cra_sha1_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस img_hash_cra_init(tfm, "sha1-generic");
पूर्ण

अटल पूर्णांक img_hash_cra_sha224_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस img_hash_cra_init(tfm, "sha224-generic");
पूर्ण

अटल पूर्णांक img_hash_cra_sha256_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस img_hash_cra_init(tfm, "sha256-generic");
पूर्ण

अटल व्योम img_hash_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा img_hash_ctx *tctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_ahash(tctx->fallback);
पूर्ण

अटल irqवापस_t img_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा img_hash_dev *hdev = dev_id;
	u32 reg;

	reg = img_hash_पढ़ो(hdev, CR_INTSTAT);
	img_hash_ग_लिखो(hdev, CR_INTCLEAR, reg);

	अगर (reg & CR_INT_NEW_RESULTS_SET) अणु
		dev_dbg(hdev->dev, "IRQ CR_INT_NEW_RESULTS_SET\n");
		अगर (DRIVER_FLAGS_BUSY & hdev->flags) अणु
			hdev->flags |= DRIVER_FLAGS_OUTPUT_READY;
			अगर (!(DRIVER_FLAGS_CPU & hdev->flags))
				hdev->flags |= DRIVER_FLAGS_DMA_READY;
			tasklet_schedule(&hdev->करोne_task);
		पूर्ण अन्यथा अणु
			dev_warn(hdev->dev,
				 "HASH interrupt when no active requests.\n");
		पूर्ण
	पूर्ण अन्यथा अगर (reg & CR_INT_RESULTS_AVAILABLE) अणु
		dev_warn(hdev->dev,
			 "IRQ triggered before the hash had completed\n");
	पूर्ण अन्यथा अगर (reg & CR_INT_RESULT_READ_ERR) अणु
		dev_warn(hdev->dev,
			 "Attempt to read from an empty result queue\n");
	पूर्ण अन्यथा अगर (reg & CR_INT_MESSAGE_WRITE_ERROR) अणु
		dev_warn(hdev->dev,
			 "Data written before the hardware was configured\n");
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा ahash_alg img_algs[] = अणु
	अणु
		.init = img_hash_init,
		.update = img_hash_update,
		.final = img_hash_final,
		.finup = img_hash_finup,
		.export = img_hash_export,
		.import = img_hash_import,
		.digest = img_hash_digest,
		.halg = अणु
			.digestsize = MD5_DIGEST_SIZE,
			.statesize = माप(काष्ठा md5_state),
			.base = अणु
				.cra_name = "md5",
				.cra_driver_name = "img-md5",
				.cra_priority = 300,
				.cra_flags =
				CRYPTO_ALG_ASYNC |
				CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = MD5_HMAC_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा img_hash_ctx),
				.cra_init = img_hash_cra_md5_init,
				.cra_निकास = img_hash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.init = img_hash_init,
		.update = img_hash_update,
		.final = img_hash_final,
		.finup = img_hash_finup,
		.export = img_hash_export,
		.import = img_hash_import,
		.digest = img_hash_digest,
		.halg = अणु
			.digestsize = SHA1_DIGEST_SIZE,
			.statesize = माप(काष्ठा sha1_state),
			.base = अणु
				.cra_name = "sha1",
				.cra_driver_name = "img-sha1",
				.cra_priority = 300,
				.cra_flags =
				CRYPTO_ALG_ASYNC |
				CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा img_hash_ctx),
				.cra_init = img_hash_cra_sha1_init,
				.cra_निकास = img_hash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.init = img_hash_init,
		.update = img_hash_update,
		.final = img_hash_final,
		.finup = img_hash_finup,
		.export = img_hash_export,
		.import = img_hash_import,
		.digest = img_hash_digest,
		.halg = अणु
			.digestsize = SHA224_DIGEST_SIZE,
			.statesize = माप(काष्ठा sha256_state),
			.base = अणु
				.cra_name = "sha224",
				.cra_driver_name = "img-sha224",
				.cra_priority = 300,
				.cra_flags =
				CRYPTO_ALG_ASYNC |
				CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA224_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा img_hash_ctx),
				.cra_init = img_hash_cra_sha224_init,
				.cra_निकास = img_hash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.init = img_hash_init,
		.update = img_hash_update,
		.final = img_hash_final,
		.finup = img_hash_finup,
		.export = img_hash_export,
		.import = img_hash_import,
		.digest = img_hash_digest,
		.halg = अणु
			.digestsize = SHA256_DIGEST_SIZE,
			.statesize = माप(काष्ठा sha256_state),
			.base = अणु
				.cra_name = "sha256",
				.cra_driver_name = "img-sha256",
				.cra_priority = 300,
				.cra_flags =
				CRYPTO_ALG_ASYNC |
				CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा img_hash_ctx),
				.cra_init = img_hash_cra_sha256_init,
				.cra_निकास = img_hash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक img_रेजिस्टर_algs(काष्ठा img_hash_dev *hdev)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < ARRAY_SIZE(img_algs); i++) अणु
		err = crypto_रेजिस्टर_ahash(&img_algs[i]);
		अगर (err)
			जाओ err_reg;
	पूर्ण
	वापस 0;

err_reg:
	क्रम (; i--; )
		crypto_unरेजिस्टर_ahash(&img_algs[i]);

	वापस err;
पूर्ण

अटल पूर्णांक img_unरेजिस्टर_algs(काष्ठा img_hash_dev *hdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(img_algs); i++)
		crypto_unरेजिस्टर_ahash(&img_algs[i]);
	वापस 0;
पूर्ण

अटल व्योम img_hash_करोne_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा img_hash_dev *hdev = (काष्ठा img_hash_dev *)data;
	पूर्णांक err = 0;

	अगर (hdev->err == -EINVAL) अणु
		err = hdev->err;
		जाओ finish;
	पूर्ण

	अगर (!(DRIVER_FLAGS_BUSY & hdev->flags)) अणु
		img_hash_handle_queue(hdev, शून्य);
		वापस;
	पूर्ण

	अगर (DRIVER_FLAGS_CPU & hdev->flags) अणु
		अगर (DRIVER_FLAGS_OUTPUT_READY & hdev->flags) अणु
			hdev->flags &= ~DRIVER_FLAGS_OUTPUT_READY;
			जाओ finish;
		पूर्ण
	पूर्ण अन्यथा अगर (DRIVER_FLAGS_DMA_READY & hdev->flags) अणु
		अगर (DRIVER_FLAGS_DMA_ACTIVE & hdev->flags) अणु
			hdev->flags &= ~DRIVER_FLAGS_DMA_ACTIVE;
			img_hash_ग_लिखो_via_dma_stop(hdev);
			अगर (hdev->err) अणु
				err = hdev->err;
				जाओ finish;
			पूर्ण
		पूर्ण
		अगर (DRIVER_FLAGS_OUTPUT_READY & hdev->flags) अणु
			hdev->flags &= ~(DRIVER_FLAGS_DMA_READY |
					DRIVER_FLAGS_OUTPUT_READY);
			जाओ finish;
		पूर्ण
	पूर्ण
	वापस;

finish:
	img_hash_finish_req(hdev->req, err);
पूर्ण

अटल स्थिर काष्ठा of_device_id img_hash_match[] = अणु
	अणु .compatible = "img,hash-accelerator" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, img_hash_match);

अटल पूर्णांक img_hash_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा img_hash_dev *hdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *hash_res;
	पूर्णांक	irq;
	पूर्णांक err;

	hdev = devm_kzalloc(dev, माप(*hdev), GFP_KERNEL);
	अगर (hdev == शून्य)
		वापस -ENOMEM;

	spin_lock_init(&hdev->lock);

	hdev->dev = dev;

	platक्रमm_set_drvdata(pdev, hdev);

	INIT_LIST_HEAD(&hdev->list);

	tasklet_init(&hdev->करोne_task, img_hash_करोne_task, (अचिन्हित दीर्घ)hdev);
	tasklet_init(&hdev->dma_task, img_hash_dma_task, (अचिन्हित दीर्घ)hdev);

	crypto_init_queue(&hdev->queue, IMG_HASH_QUEUE_LENGTH);

	/* Register bank */
	hdev->io_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hdev->io_base)) अणु
		err = PTR_ERR(hdev->io_base);
		जाओ res_err;
	पूर्ण

	/* Write port (DMA or CPU) */
	hash_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	hdev->cpu_addr = devm_ioremap_resource(dev, hash_res);
	अगर (IS_ERR(hdev->cpu_addr)) अणु
		err = PTR_ERR(hdev->cpu_addr);
		जाओ res_err;
	पूर्ण
	hdev->bus_addr = hash_res->start;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		err = irq;
		जाओ res_err;
	पूर्ण

	err = devm_request_irq(dev, irq, img_irq_handler, 0,
			       dev_name(dev), hdev);
	अगर (err) अणु
		dev_err(dev, "unable to request irq\n");
		जाओ res_err;
	पूर्ण
	dev_dbg(dev, "using IRQ channel %d\n", irq);

	hdev->hash_clk = devm_clk_get(&pdev->dev, "hash");
	अगर (IS_ERR(hdev->hash_clk)) अणु
		dev_err(dev, "clock initialization failed.\n");
		err = PTR_ERR(hdev->hash_clk);
		जाओ res_err;
	पूर्ण

	hdev->sys_clk = devm_clk_get(&pdev->dev, "sys");
	अगर (IS_ERR(hdev->sys_clk)) अणु
		dev_err(dev, "clock initialization failed.\n");
		err = PTR_ERR(hdev->sys_clk);
		जाओ res_err;
	पूर्ण

	err = clk_prepare_enable(hdev->hash_clk);
	अगर (err)
		जाओ res_err;

	err = clk_prepare_enable(hdev->sys_clk);
	अगर (err)
		जाओ clk_err;

	err = img_hash_dma_init(hdev);
	अगर (err)
		जाओ dma_err;

	dev_dbg(dev, "using %s for DMA transfers\n",
		dma_chan_name(hdev->dma_lch));

	spin_lock(&img_hash.lock);
	list_add_tail(&hdev->list, &img_hash.dev_list);
	spin_unlock(&img_hash.lock);

	err = img_रेजिस्टर_algs(hdev);
	अगर (err)
		जाओ err_algs;
	dev_info(dev, "Img MD5/SHA1/SHA224/SHA256 Hardware accelerator initialized\n");

	वापस 0;

err_algs:
	spin_lock(&img_hash.lock);
	list_del(&hdev->list);
	spin_unlock(&img_hash.lock);
	dma_release_channel(hdev->dma_lch);
dma_err:
	clk_disable_unprepare(hdev->sys_clk);
clk_err:
	clk_disable_unprepare(hdev->hash_clk);
res_err:
	tasklet_समाप्त(&hdev->करोne_task);
	tasklet_समाप्त(&hdev->dma_task);

	वापस err;
पूर्ण

अटल पूर्णांक img_hash_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा img_hash_dev *hdev;

	hdev = platक्रमm_get_drvdata(pdev);
	spin_lock(&img_hash.lock);
	list_del(&hdev->list);
	spin_unlock(&img_hash.lock);

	img_unरेजिस्टर_algs(hdev);

	tasklet_समाप्त(&hdev->करोne_task);
	tasklet_समाप्त(&hdev->dma_task);

	dma_release_channel(hdev->dma_lch);

	clk_disable_unprepare(hdev->hash_clk);
	clk_disable_unprepare(hdev->sys_clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक img_hash_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_hash_dev *hdev = dev_get_drvdata(dev);

	clk_disable_unprepare(hdev->hash_clk);
	clk_disable_unprepare(hdev->sys_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक img_hash_resume(काष्ठा device *dev)
अणु
	काष्ठा img_hash_dev *hdev = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(hdev->hash_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(hdev->sys_clk);
	अगर (ret) अणु
		clk_disable_unprepare(hdev->hash_clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops img_hash_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(img_hash_suspend, img_hash_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver img_hash_driver = अणु
	.probe		= img_hash_probe,
	.हटाओ		= img_hash_हटाओ,
	.driver		= अणु
		.name	= "img-hash-accelerator",
		.pm	= &img_hash_pm_ops,
		.of_match_table	= of_match_ptr(img_hash_match),
	पूर्ण
पूर्ण;
module_platक्रमm_driver(img_hash_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Imgtec SHA1/224/256 & MD5 hw accelerator driver");
MODULE_AUTHOR("Will Thomas.");
MODULE_AUTHOR("James Hartley <james.hartley@imgtec.com>");
