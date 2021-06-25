<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of STM32 Crypto driver क्रम Linux.
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author(s): Lionel DEBIEVE <lionel.debieve@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/crypto.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <crypto/engine.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/md5.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

#घोषणा HASH_CR				0x00
#घोषणा HASH_DIN			0x04
#घोषणा HASH_STR			0x08
#घोषणा HASH_IMR			0x20
#घोषणा HASH_SR				0x24
#घोषणा HASH_CSR(x)			(0x0F8 + ((x) * 0x04))
#घोषणा HASH_HREG(x)			(0x310 + ((x) * 0x04))
#घोषणा HASH_HWCFGR			0x3F0
#घोषणा HASH_VER			0x3F4
#घोषणा HASH_ID				0x3F8

/* Control Register */
#घोषणा HASH_CR_INIT			BIT(2)
#घोषणा HASH_CR_DMAE			BIT(3)
#घोषणा HASH_CR_DATATYPE_POS		4
#घोषणा HASH_CR_MODE			BIT(6)
#घोषणा HASH_CR_MDMAT			BIT(13)
#घोषणा HASH_CR_DMAA			BIT(14)
#घोषणा HASH_CR_LKEY			BIT(16)

#घोषणा HASH_CR_ALGO_SHA1		0x0
#घोषणा HASH_CR_ALGO_MD5		0x80
#घोषणा HASH_CR_ALGO_SHA224		0x40000
#घोषणा HASH_CR_ALGO_SHA256		0x40080

/* Interrupt */
#घोषणा HASH_DINIE			BIT(0)
#घोषणा HASH_DCIE			BIT(1)

/* Interrupt Mask */
#घोषणा HASH_MASK_CALC_COMPLETION	BIT(0)
#घोषणा HASH_MASK_DATA_INPUT		BIT(1)

/* Context swap रेजिस्टर */
#घोषणा HASH_CSR_REGISTER_NUMBER	53

/* Status Flags */
#घोषणा HASH_SR_DATA_INPUT_READY	BIT(0)
#घोषणा HASH_SR_OUTPUT_READY		BIT(1)
#घोषणा HASH_SR_DMA_ACTIVE		BIT(2)
#घोषणा HASH_SR_BUSY			BIT(3)

/* STR Register */
#घोषणा HASH_STR_NBLW_MASK		GENMASK(4, 0)
#घोषणा HASH_STR_DCAL			BIT(8)

#घोषणा HASH_FLAGS_INIT			BIT(0)
#घोषणा HASH_FLAGS_OUTPUT_READY		BIT(1)
#घोषणा HASH_FLAGS_CPU			BIT(2)
#घोषणा HASH_FLAGS_DMA_READY		BIT(3)
#घोषणा HASH_FLAGS_DMA_ACTIVE		BIT(4)
#घोषणा HASH_FLAGS_HMAC_INIT		BIT(5)
#घोषणा HASH_FLAGS_HMAC_FINAL		BIT(6)
#घोषणा HASH_FLAGS_HMAC_KEY		BIT(7)

#घोषणा HASH_FLAGS_FINAL		BIT(15)
#घोषणा HASH_FLAGS_FINUP		BIT(16)
#घोषणा HASH_FLAGS_ALGO_MASK		GENMASK(21, 18)
#घोषणा HASH_FLAGS_MD5			BIT(18)
#घोषणा HASH_FLAGS_SHA1			BIT(19)
#घोषणा HASH_FLAGS_SHA224		BIT(20)
#घोषणा HASH_FLAGS_SHA256		BIT(21)
#घोषणा HASH_FLAGS_ERRORS		BIT(22)
#घोषणा HASH_FLAGS_HMAC			BIT(23)

#घोषणा HASH_OP_UPDATE			1
#घोषणा HASH_OP_FINAL			2

क्रमागत sपंचांग32_hash_data_क्रमmat अणु
	HASH_DATA_32_BITS		= 0x0,
	HASH_DATA_16_BITS		= 0x1,
	HASH_DATA_8_BITS		= 0x2,
	HASH_DATA_1_BIT			= 0x3
पूर्ण;

#घोषणा HASH_BUFLEN			256
#घोषणा HASH_LONG_KEY			64
#घोषणा HASH_MAX_KEY_SIZE		(SHA256_BLOCK_SIZE * 8)
#घोषणा HASH_QUEUE_LENGTH		16
#घोषणा HASH_DMA_THRESHOLD		50

#घोषणा HASH_AUTOSUSPEND_DELAY		50

काष्ठा sपंचांग32_hash_ctx अणु
	काष्ठा crypto_engine_ctx enginectx;
	काष्ठा sपंचांग32_hash_dev	*hdev;
	अचिन्हित दीर्घ		flags;

	u8			key[HASH_MAX_KEY_SIZE];
	पूर्णांक			keylen;
पूर्ण;

काष्ठा sपंचांग32_hash_request_ctx अणु
	काष्ठा sपंचांग32_hash_dev	*hdev;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		op;

	u8 digest[SHA256_DIGEST_SIZE] __aligned(माप(u32));
	माप_प्रकार			digcnt;
	माप_प्रकार			bufcnt;
	माप_प्रकार			buflen;

	/* DMA */
	काष्ठा scatterlist	*sg;
	अचिन्हित पूर्णांक		offset;
	अचिन्हित पूर्णांक		total;
	काष्ठा scatterlist	sg_key;

	dma_addr_t		dma_addr;
	माप_प्रकार			dma_ct;
	पूर्णांक			nents;

	u8			data_type;

	u8 buffer[HASH_BUFLEN] __aligned(माप(u32));

	/* Export Context */
	u32			*hw_context;
पूर्ण;

काष्ठा sपंचांग32_hash_algs_info अणु
	काष्ठा ahash_alg	*algs_list;
	माप_प्रकार			size;
पूर्ण;

काष्ठा sपंचांग32_hash_pdata अणु
	काष्ठा sपंचांग32_hash_algs_info	*algs_info;
	माप_प्रकार				algs_info_size;
पूर्ण;

काष्ठा sपंचांग32_hash_dev अणु
	काष्ठा list_head	list;
	काष्ठा device		*dev;
	काष्ठा clk		*clk;
	काष्ठा reset_control	*rst;
	व्योम __iomem		*io_base;
	phys_addr_t		phys_base;
	u32			dma_mode;
	u32			dma_maxburst;

	काष्ठा ahash_request	*req;
	काष्ठा crypto_engine	*engine;

	पूर्णांक			err;
	अचिन्हित दीर्घ		flags;

	काष्ठा dma_chan		*dma_lch;
	काष्ठा completion	dma_completion;

	स्थिर काष्ठा sपंचांग32_hash_pdata	*pdata;
पूर्ण;

काष्ठा sपंचांग32_hash_drv अणु
	काष्ठा list_head	dev_list;
	spinlock_t		lock; /* List protection access */
पूर्ण;

अटल काष्ठा sपंचांग32_hash_drv sपंचांग32_hash = अणु
	.dev_list = LIST_HEAD_INIT(sपंचांग32_hash.dev_list),
	.lock = __SPIN_LOCK_UNLOCKED(sपंचांग32_hash.lock),
पूर्ण;

अटल व्योम sपंचांग32_hash_dma_callback(व्योम *param);

अटल अंतरभूत u32 sपंचांग32_hash_पढ़ो(काष्ठा sपंचांग32_hash_dev *hdev, u32 offset)
अणु
	वापस पढ़ोl_relaxed(hdev->io_base + offset);
पूर्ण

अटल अंतरभूत व्योम sपंचांग32_hash_ग_लिखो(काष्ठा sपंचांग32_hash_dev *hdev,
				    u32 offset, u32 value)
अणु
	ग_लिखोl_relaxed(value, hdev->io_base + offset);
पूर्ण

अटल अंतरभूत पूर्णांक sपंचांग32_hash_रुको_busy(काष्ठा sपंचांग32_hash_dev *hdev)
अणु
	u32 status;

	वापस पढ़ोl_relaxed_poll_समयout(hdev->io_base + HASH_SR, status,
				   !(status & HASH_SR_BUSY), 10, 10000);
पूर्ण

अटल व्योम sपंचांग32_hash_set_nblw(काष्ठा sपंचांग32_hash_dev *hdev, पूर्णांक length)
अणु
	u32 reg;

	reg = sपंचांग32_hash_पढ़ो(hdev, HASH_STR);
	reg &= ~(HASH_STR_NBLW_MASK);
	reg |= (8U * ((length) % 4U));
	sपंचांग32_hash_ग_लिखो(hdev, HASH_STR, reg);
पूर्ण

अटल पूर्णांक sपंचांग32_hash_ग_लिखो_key(काष्ठा sपंचांग32_hash_dev *hdev)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(hdev->req);
	काष्ठा sपंचांग32_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	u32 reg;
	पूर्णांक keylen = ctx->keylen;
	व्योम *key = ctx->key;

	अगर (keylen) अणु
		sपंचांग32_hash_set_nblw(hdev, keylen);

		जबतक (keylen > 0) अणु
			sपंचांग32_hash_ग_लिखो(hdev, HASH_DIN, *(u32 *)key);
			keylen -= 4;
			key += 4;
		पूर्ण

		reg = sपंचांग32_hash_पढ़ो(hdev, HASH_STR);
		reg |= HASH_STR_DCAL;
		sपंचांग32_hash_ग_लिखो(hdev, HASH_STR, reg);

		वापस -EINPROGRESS;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_hash_ग_लिखो_ctrl(काष्ठा sपंचांग32_hash_dev *hdev)
अणु
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(hdev->req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(hdev->req);
	काष्ठा sपंचांग32_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	u32 reg = HASH_CR_INIT;

	अगर (!(hdev->flags & HASH_FLAGS_INIT)) अणु
		चयन (rctx->flags & HASH_FLAGS_ALGO_MASK) अणु
		हाल HASH_FLAGS_MD5:
			reg |= HASH_CR_ALGO_MD5;
			अवरोध;
		हाल HASH_FLAGS_SHA1:
			reg |= HASH_CR_ALGO_SHA1;
			अवरोध;
		हाल HASH_FLAGS_SHA224:
			reg |= HASH_CR_ALGO_SHA224;
			अवरोध;
		हाल HASH_FLAGS_SHA256:
			reg |= HASH_CR_ALGO_SHA256;
			अवरोध;
		शेष:
			reg |= HASH_CR_ALGO_MD5;
		पूर्ण

		reg |= (rctx->data_type << HASH_CR_DATATYPE_POS);

		अगर (rctx->flags & HASH_FLAGS_HMAC) अणु
			hdev->flags |= HASH_FLAGS_HMAC;
			reg |= HASH_CR_MODE;
			अगर (ctx->keylen > HASH_LONG_KEY)
				reg |= HASH_CR_LKEY;
		पूर्ण

		sपंचांग32_hash_ग_लिखो(hdev, HASH_IMR, HASH_DCIE);

		sपंचांग32_hash_ग_लिखो(hdev, HASH_CR, reg);

		hdev->flags |= HASH_FLAGS_INIT;

		dev_dbg(hdev->dev, "Write Control %x\n", reg);
	पूर्ण
पूर्ण

अटल व्योम sपंचांग32_hash_append_sg(काष्ठा sपंचांग32_hash_request_ctx *rctx)
अणु
	माप_प्रकार count;

	जबतक ((rctx->bufcnt < rctx->buflen) && rctx->total) अणु
		count = min(rctx->sg->length - rctx->offset, rctx->total);
		count = min(count, rctx->buflen - rctx->bufcnt);

		अगर (count <= 0) अणु
			अगर ((rctx->sg->length == 0) && !sg_is_last(rctx->sg)) अणु
				rctx->sg = sg_next(rctx->sg);
				जारी;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण

		scatterwalk_map_and_copy(rctx->buffer + rctx->bufcnt, rctx->sg,
					 rctx->offset, count, 0);

		rctx->bufcnt += count;
		rctx->offset += count;
		rctx->total -= count;

		अगर (rctx->offset == rctx->sg->length) अणु
			rctx->sg = sg_next(rctx->sg);
			अगर (rctx->sg)
				rctx->offset = 0;
			अन्यथा
				rctx->total = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_hash_xmit_cpu(काष्ठा sपंचांग32_hash_dev *hdev,
			       स्थिर u8 *buf, माप_प्रकार length, पूर्णांक final)
अणु
	अचिन्हित पूर्णांक count, len32;
	स्थिर u32 *buffer = (स्थिर u32 *)buf;
	u32 reg;

	अगर (final)
		hdev->flags |= HASH_FLAGS_FINAL;

	len32 = DIV_ROUND_UP(length, माप(u32));

	dev_dbg(hdev->dev, "%s: length: %zd, final: %x len32 %i\n",
		__func__, length, final, len32);

	hdev->flags |= HASH_FLAGS_CPU;

	sपंचांग32_hash_ग_लिखो_ctrl(hdev);

	अगर (sपंचांग32_hash_रुको_busy(hdev))
		वापस -ETIMEDOUT;

	अगर ((hdev->flags & HASH_FLAGS_HMAC) &&
	    (!(hdev->flags & HASH_FLAGS_HMAC_KEY))) अणु
		hdev->flags |= HASH_FLAGS_HMAC_KEY;
		sपंचांग32_hash_ग_लिखो_key(hdev);
		अगर (sपंचांग32_hash_रुको_busy(hdev))
			वापस -ETIMEDOUT;
	पूर्ण

	क्रम (count = 0; count < len32; count++)
		sपंचांग32_hash_ग_लिखो(hdev, HASH_DIN, buffer[count]);

	अगर (final) अणु
		sपंचांग32_hash_set_nblw(hdev, length);
		reg = sपंचांग32_hash_पढ़ो(hdev, HASH_STR);
		reg |= HASH_STR_DCAL;
		sपंचांग32_hash_ग_लिखो(hdev, HASH_STR, reg);
		अगर (hdev->flags & HASH_FLAGS_HMAC) अणु
			अगर (sपंचांग32_hash_रुको_busy(hdev))
				वापस -ETIMEDOUT;
			sपंचांग32_hash_ग_लिखो_key(hdev);
		पूर्ण
		वापस -EINPROGRESS;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_update_cpu(काष्ठा sपंचांग32_hash_dev *hdev)
अणु
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(hdev->req);
	पूर्णांक bufcnt, err = 0, final;

	dev_dbg(hdev->dev, "%s flags %lx\n", __func__, rctx->flags);

	final = (rctx->flags & HASH_FLAGS_FINUP);

	जबतक ((rctx->total >= rctx->buflen) ||
	       (rctx->bufcnt + rctx->total >= rctx->buflen)) अणु
		sपंचांग32_hash_append_sg(rctx);
		bufcnt = rctx->bufcnt;
		rctx->bufcnt = 0;
		err = sपंचांग32_hash_xmit_cpu(hdev, rctx->buffer, bufcnt, 0);
	पूर्ण

	sपंचांग32_hash_append_sg(rctx);

	अगर (final) अणु
		bufcnt = rctx->bufcnt;
		rctx->bufcnt = 0;
		err = sपंचांग32_hash_xmit_cpu(hdev, rctx->buffer, bufcnt,
					  (rctx->flags & HASH_FLAGS_FINUP));
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_xmit_dma(काष्ठा sपंचांग32_hash_dev *hdev,
			       काष्ठा scatterlist *sg, पूर्णांक length, पूर्णांक mdma)
अणु
	काष्ठा dma_async_tx_descriptor *in_desc;
	dma_cookie_t cookie;
	u32 reg;
	पूर्णांक err;

	in_desc = dmaengine_prep_slave_sg(hdev->dma_lch, sg, 1,
					  DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT |
					  DMA_CTRL_ACK);
	अगर (!in_desc) अणु
		dev_err(hdev->dev, "dmaengine_prep_slave error\n");
		वापस -ENOMEM;
	पूर्ण

	reinit_completion(&hdev->dma_completion);
	in_desc->callback = sपंचांग32_hash_dma_callback;
	in_desc->callback_param = hdev;

	hdev->flags |= HASH_FLAGS_FINAL;
	hdev->flags |= HASH_FLAGS_DMA_ACTIVE;

	reg = sपंचांग32_hash_पढ़ो(hdev, HASH_CR);

	अगर (mdma)
		reg |= HASH_CR_MDMAT;
	अन्यथा
		reg &= ~HASH_CR_MDMAT;

	reg |= HASH_CR_DMAE;

	sपंचांग32_hash_ग_लिखो(hdev, HASH_CR, reg);

	sपंचांग32_hash_set_nblw(hdev, length);

	cookie = dmaengine_submit(in_desc);
	err = dma_submit_error(cookie);
	अगर (err)
		वापस -ENOMEM;

	dma_async_issue_pending(hdev->dma_lch);

	अगर (!रुको_क्रम_completion_समयout(&hdev->dma_completion,
					 msecs_to_jअगरfies(100)))
		err = -ETIMEDOUT;

	अगर (dma_async_is_tx_complete(hdev->dma_lch, cookie,
				     शून्य, शून्य) != DMA_COMPLETE)
		err = -ETIMEDOUT;

	अगर (err) अणु
		dev_err(hdev->dev, "DMA Error %i\n", err);
		dmaengine_terminate_all(hdev->dma_lch);
		वापस err;
	पूर्ण

	वापस -EINPROGRESS;
पूर्ण

अटल व्योम sपंचांग32_hash_dma_callback(व्योम *param)
अणु
	काष्ठा sपंचांग32_hash_dev *hdev = param;

	complete(&hdev->dma_completion);

	hdev->flags |= HASH_FLAGS_DMA_READY;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_hmac_dma_send(काष्ठा sपंचांग32_hash_dev *hdev)
अणु
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(hdev->req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(hdev->req);
	काष्ठा sपंचांग32_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	पूर्णांक err;

	अगर (ctx->keylen < HASH_DMA_THRESHOLD || (hdev->dma_mode == 1)) अणु
		err = sपंचांग32_hash_ग_लिखो_key(hdev);
		अगर (sपंचांग32_hash_रुको_busy(hdev))
			वापस -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		अगर (!(hdev->flags & HASH_FLAGS_HMAC_KEY))
			sg_init_one(&rctx->sg_key, ctx->key,
				    ALIGN(ctx->keylen, माप(u32)));

		rctx->dma_ct = dma_map_sg(hdev->dev, &rctx->sg_key, 1,
					  DMA_TO_DEVICE);
		अगर (rctx->dma_ct == 0) अणु
			dev_err(hdev->dev, "dma_map_sg error\n");
			वापस -ENOMEM;
		पूर्ण

		err = sपंचांग32_hash_xmit_dma(hdev, &rctx->sg_key, ctx->keylen, 0);

		dma_unmap_sg(hdev->dev, &rctx->sg_key, 1, DMA_TO_DEVICE);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_dma_init(काष्ठा sपंचांग32_hash_dev *hdev)
अणु
	काष्ठा dma_slave_config dma_conf;
	काष्ठा dma_chan *chan;
	पूर्णांक err;

	स_रखो(&dma_conf, 0, माप(dma_conf));

	dma_conf.direction = DMA_MEM_TO_DEV;
	dma_conf.dst_addr = hdev->phys_base + HASH_DIN;
	dma_conf.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	dma_conf.src_maxburst = hdev->dma_maxburst;
	dma_conf.dst_maxburst = hdev->dma_maxburst;
	dma_conf.device_fc = false;

	chan = dma_request_chan(hdev->dev, "in");
	अगर (IS_ERR(chan))
		वापस PTR_ERR(chan);

	hdev->dma_lch = chan;

	err = dmaengine_slave_config(hdev->dma_lch, &dma_conf);
	अगर (err) अणु
		dma_release_channel(hdev->dma_lch);
		hdev->dma_lch = शून्य;
		dev_err(hdev->dev, "Couldn't configure DMA slave.\n");
		वापस err;
	पूर्ण

	init_completion(&hdev->dma_completion);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_dma_send(काष्ठा sपंचांग32_hash_dev *hdev)
अणु
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(hdev->req);
	काष्ठा scatterlist sg[1], *tsg;
	पूर्णांक err = 0, len = 0, reg, ncp = 0;
	अचिन्हित पूर्णांक i;
	u32 *buffer = (व्योम *)rctx->buffer;

	rctx->sg = hdev->req->src;
	rctx->total = hdev->req->nbytes;

	rctx->nents = sg_nents(rctx->sg);

	अगर (rctx->nents < 0)
		वापस -EINVAL;

	sपंचांग32_hash_ग_लिखो_ctrl(hdev);

	अगर (hdev->flags & HASH_FLAGS_HMAC) अणु
		err = sपंचांग32_hash_hmac_dma_send(hdev);
		अगर (err != -EINPROGRESS)
			वापस err;
	पूर्ण

	क्रम_each_sg(rctx->sg, tsg, rctx->nents, i) अणु
		len = sg->length;

		sg[0] = *tsg;
		अगर (sg_is_last(sg)) अणु
			अगर (hdev->dma_mode == 1) अणु
				len = (ALIGN(sg->length, 16) - 16);

				ncp = sg_pcopy_to_buffer(
					rctx->sg, rctx->nents,
					rctx->buffer, sg->length - len,
					rctx->total - sg->length + len);

				sg->length = len;
			पूर्ण अन्यथा अणु
				अगर (!(IS_ALIGNED(sg->length, माप(u32)))) अणु
					len = sg->length;
					sg->length = ALIGN(sg->length,
							   माप(u32));
				पूर्ण
			पूर्ण
		पूर्ण

		rctx->dma_ct = dma_map_sg(hdev->dev, sg, 1,
					  DMA_TO_DEVICE);
		अगर (rctx->dma_ct == 0) अणु
			dev_err(hdev->dev, "dma_map_sg error\n");
			वापस -ENOMEM;
		पूर्ण

		err = sपंचांग32_hash_xmit_dma(hdev, sg, len,
					  !sg_is_last(sg));

		dma_unmap_sg(hdev->dev, sg, 1, DMA_TO_DEVICE);

		अगर (err == -ENOMEM)
			वापस err;
	पूर्ण

	अगर (hdev->dma_mode == 1) अणु
		अगर (sपंचांग32_hash_रुको_busy(hdev))
			वापस -ETIMEDOUT;
		reg = sपंचांग32_hash_पढ़ो(hdev, HASH_CR);
		reg &= ~HASH_CR_DMAE;
		reg |= HASH_CR_DMAA;
		sपंचांग32_hash_ग_लिखो(hdev, HASH_CR, reg);

		अगर (ncp) अणु
			स_रखो(buffer + ncp, 0,
			       DIV_ROUND_UP(ncp, माप(u32)) - ncp);
			ग_लिखोsl(hdev->io_base + HASH_DIN, buffer,
				DIV_ROUND_UP(ncp, माप(u32)));
		पूर्ण
		sपंचांग32_hash_set_nblw(hdev, ncp);
		reg = sपंचांग32_hash_पढ़ो(hdev, HASH_STR);
		reg |= HASH_STR_DCAL;
		sपंचांग32_hash_ग_लिखो(hdev, HASH_STR, reg);
		err = -EINPROGRESS;
	पूर्ण

	अगर (hdev->flags & HASH_FLAGS_HMAC) अणु
		अगर (sपंचांग32_hash_रुको_busy(hdev))
			वापस -ETIMEDOUT;
		err = sपंचांग32_hash_hmac_dma_send(hdev);
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा sपंचांग32_hash_dev *sपंचांग32_hash_find_dev(काष्ठा sपंचांग32_hash_ctx *ctx)
अणु
	काष्ठा sपंचांग32_hash_dev *hdev = शून्य, *पंचांगp;

	spin_lock_bh(&sपंचांग32_hash.lock);
	अगर (!ctx->hdev) अणु
		list_क्रम_each_entry(पंचांगp, &sपंचांग32_hash.dev_list, list) अणु
			hdev = पंचांगp;
			अवरोध;
		पूर्ण
		ctx->hdev = hdev;
	पूर्ण अन्यथा अणु
		hdev = ctx->hdev;
	पूर्ण

	spin_unlock_bh(&sपंचांग32_hash.lock);

	वापस hdev;
पूर्ण

अटल bool sपंचांग32_hash_dma_aligned_data(काष्ठा ahash_request *req)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा sपंचांग32_hash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	काष्ठा sपंचांग32_hash_dev *hdev = sपंचांग32_hash_find_dev(ctx);
	पूर्णांक i;

	अगर (req->nbytes <= HASH_DMA_THRESHOLD)
		वापस false;

	अगर (sg_nents(req->src) > 1) अणु
		अगर (hdev->dma_mode == 1)
			वापस false;
		क्रम_each_sg(req->src, sg, sg_nents(req->src), i) अणु
			अगर ((!IS_ALIGNED(sg->length, माप(u32))) &&
			    (!sg_is_last(sg)))
				वापस false;
		पूर्ण
	पूर्ण

	अगर (req->src->offset % 4)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा sपंचांग32_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा sपंचांग32_hash_dev *hdev = sपंचांग32_hash_find_dev(ctx);

	rctx->hdev = hdev;

	rctx->flags = HASH_FLAGS_CPU;

	rctx->digcnt = crypto_ahash_digestsize(tfm);
	चयन (rctx->digcnt) अणु
	हाल MD5_DIGEST_SIZE:
		rctx->flags |= HASH_FLAGS_MD5;
		अवरोध;
	हाल SHA1_DIGEST_SIZE:
		rctx->flags |= HASH_FLAGS_SHA1;
		अवरोध;
	हाल SHA224_DIGEST_SIZE:
		rctx->flags |= HASH_FLAGS_SHA224;
		अवरोध;
	हाल SHA256_DIGEST_SIZE:
		rctx->flags |= HASH_FLAGS_SHA256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rctx->bufcnt = 0;
	rctx->buflen = HASH_BUFLEN;
	rctx->total = 0;
	rctx->offset = 0;
	rctx->data_type = HASH_DATA_8_BITS;

	स_रखो(rctx->buffer, 0, HASH_BUFLEN);

	अगर (ctx->flags & HASH_FLAGS_HMAC)
		rctx->flags |= HASH_FLAGS_HMAC;

	dev_dbg(hdev->dev, "%s Flags %lx\n", __func__, rctx->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_update_req(काष्ठा sपंचांग32_hash_dev *hdev)
अणु
	वापस sपंचांग32_hash_update_cpu(hdev);
पूर्ण

अटल पूर्णांक sपंचांग32_hash_final_req(काष्ठा sपंचांग32_hash_dev *hdev)
अणु
	काष्ठा ahash_request *req = hdev->req;
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(req);
	पूर्णांक err;
	पूर्णांक buflen = rctx->bufcnt;

	rctx->bufcnt = 0;

	अगर (!(rctx->flags & HASH_FLAGS_CPU))
		err = sपंचांग32_hash_dma_send(hdev);
	अन्यथा
		err = sपंचांग32_hash_xmit_cpu(hdev, rctx->buffer, buflen, 1);


	वापस err;
पूर्ण

अटल व्योम sपंचांग32_hash_copy_hash(काष्ठा ahash_request *req)
अणु
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(req);
	__be32 *hash = (व्योम *)rctx->digest;
	अचिन्हित पूर्णांक i, hashsize;

	चयन (rctx->flags & HASH_FLAGS_ALGO_MASK) अणु
	हाल HASH_FLAGS_MD5:
		hashsize = MD5_DIGEST_SIZE;
		अवरोध;
	हाल HASH_FLAGS_SHA1:
		hashsize = SHA1_DIGEST_SIZE;
		अवरोध;
	हाल HASH_FLAGS_SHA224:
		hashsize = SHA224_DIGEST_SIZE;
		अवरोध;
	हाल HASH_FLAGS_SHA256:
		hashsize = SHA256_DIGEST_SIZE;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	क्रम (i = 0; i < hashsize / माप(u32); i++)
		hash[i] = cpu_to_be32(sपंचांग32_hash_पढ़ो(rctx->hdev,
						      HASH_HREG(i)));
पूर्ण

अटल पूर्णांक sपंचांग32_hash_finish(काष्ठा ahash_request *req)
अणु
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(req);

	अगर (!req->result)
		वापस -EINVAL;

	स_नकल(req->result, rctx->digest, rctx->digcnt);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_hash_finish_req(काष्ठा ahash_request *req, पूर्णांक err)
अणु
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा sपंचांग32_hash_dev *hdev = rctx->hdev;

	अगर (!err && (HASH_FLAGS_FINAL & hdev->flags)) अणु
		sपंचांग32_hash_copy_hash(req);
		err = sपंचांग32_hash_finish(req);
		hdev->flags &= ~(HASH_FLAGS_FINAL | HASH_FLAGS_CPU |
				 HASH_FLAGS_INIT | HASH_FLAGS_DMA_READY |
				 HASH_FLAGS_OUTPUT_READY | HASH_FLAGS_HMAC |
				 HASH_FLAGS_HMAC_INIT | HASH_FLAGS_HMAC_FINAL |
				 HASH_FLAGS_HMAC_KEY);
	पूर्ण अन्यथा अणु
		rctx->flags |= HASH_FLAGS_ERRORS;
	पूर्ण

	pm_runसमय_mark_last_busy(hdev->dev);
	pm_runसमय_put_स्वतःsuspend(hdev->dev);

	crypto_finalize_hash_request(hdev->engine, req, err);
पूर्ण

अटल पूर्णांक sपंचांग32_hash_hw_init(काष्ठा sपंचांग32_hash_dev *hdev,
			      काष्ठा sपंचांग32_hash_request_ctx *rctx)
अणु
	pm_runसमय_resume_and_get(hdev->dev);

	अगर (!(HASH_FLAGS_INIT & hdev->flags)) अणु
		sपंचांग32_hash_ग_लिखो(hdev, HASH_CR, HASH_CR_INIT);
		sपंचांग32_hash_ग_लिखो(hdev, HASH_STR, 0);
		sपंचांग32_hash_ग_लिखो(hdev, HASH_DIN, 0);
		sपंचांग32_hash_ग_लिखो(hdev, HASH_IMR, 0);
		hdev->err = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_one_request(काष्ठा crypto_engine *engine, व्योम *areq);
अटल पूर्णांक sपंचांग32_hash_prepare_req(काष्ठा crypto_engine *engine, व्योम *areq);

अटल पूर्णांक sपंचांग32_hash_handle_queue(काष्ठा sपंचांग32_hash_dev *hdev,
				   काष्ठा ahash_request *req)
अणु
	वापस crypto_transfer_hash_request_to_engine(hdev->engine, req);
पूर्ण

अटल पूर्णांक sपंचांग32_hash_prepare_req(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा ahash_request *req = container_of(areq, काष्ठा ahash_request,
						 base);
	काष्ठा sपंचांग32_hash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	काष्ठा sपंचांग32_hash_dev *hdev = sपंचांग32_hash_find_dev(ctx);
	काष्ठा sपंचांग32_hash_request_ctx *rctx;

	अगर (!hdev)
		वापस -ENODEV;

	hdev->req = req;

	rctx = ahash_request_ctx(req);

	dev_dbg(hdev->dev, "processing new req, op: %lu, nbytes %d\n",
		rctx->op, req->nbytes);

	वापस sपंचांग32_hash_hw_init(hdev, rctx);
पूर्ण

अटल पूर्णांक sपंचांग32_hash_one_request(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा ahash_request *req = container_of(areq, काष्ठा ahash_request,
						 base);
	काष्ठा sपंचांग32_hash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	काष्ठा sपंचांग32_hash_dev *hdev = sपंचांग32_hash_find_dev(ctx);
	काष्ठा sपंचांग32_hash_request_ctx *rctx;
	पूर्णांक err = 0;

	अगर (!hdev)
		वापस -ENODEV;

	hdev->req = req;

	rctx = ahash_request_ctx(req);

	अगर (rctx->op == HASH_OP_UPDATE)
		err = sपंचांग32_hash_update_req(hdev);
	अन्यथा अगर (rctx->op == HASH_OP_FINAL)
		err = sपंचांग32_hash_final_req(hdev);

	अगर (err != -EINPROGRESS)
	/* करोne task will not finish it, so करो it here */
		sपंचांग32_hash_finish_req(req, err);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_enqueue(काष्ठा ahash_request *req, अचिन्हित पूर्णांक op)
अणु
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा sपंचांग32_hash_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा sपंचांग32_hash_dev *hdev = ctx->hdev;

	rctx->op = op;

	वापस sपंचांग32_hash_handle_queue(hdev, req);
पूर्ण

अटल पूर्णांक sपंचांग32_hash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(req);

	अगर (!req->nbytes || !(rctx->flags & HASH_FLAGS_CPU))
		वापस 0;

	rctx->total = req->nbytes;
	rctx->sg = req->src;
	rctx->offset = 0;

	अगर ((rctx->bufcnt + rctx->total < rctx->buflen)) अणु
		sपंचांग32_hash_append_sg(rctx);
		वापस 0;
	पूर्ण

	वापस sपंचांग32_hash_enqueue(req, HASH_OP_UPDATE);
पूर्ण

अटल पूर्णांक sपंचांग32_hash_final(काष्ठा ahash_request *req)
अणु
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(req);

	rctx->flags |= HASH_FLAGS_FINUP;

	वापस sपंचांग32_hash_enqueue(req, HASH_OP_FINAL);
पूर्ण

अटल पूर्णांक sपंचांग32_hash_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा sपंचांग32_hash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	काष्ठा sपंचांग32_hash_dev *hdev = sपंचांग32_hash_find_dev(ctx);
	पूर्णांक err1, err2;

	rctx->flags |= HASH_FLAGS_FINUP;

	अगर (hdev->dma_lch && sपंचांग32_hash_dma_aligned_data(req))
		rctx->flags &= ~HASH_FLAGS_CPU;

	err1 = sपंचांग32_hash_update(req);

	अगर (err1 == -EINPROGRESS || err1 == -EBUSY)
		वापस err1;

	/*
	 * final() has to be always called to cleanup resources
	 * even अगर update() failed, except EINPROGRESS
	 */
	err2 = sपंचांग32_hash_final(req);

	वापस err1 ?: err2;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_digest(काष्ठा ahash_request *req)
अणु
	वापस sपंचांग32_hash_init(req) ?: sपंचांग32_hash_finup(req);
पूर्ण

अटल पूर्णांक sपंचांग32_hash_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा sपंचांग32_hash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	काष्ठा sपंचांग32_hash_dev *hdev = sपंचांग32_hash_find_dev(ctx);
	u32 *preg;
	अचिन्हित पूर्णांक i;

	pm_runसमय_resume_and_get(hdev->dev);

	जबतक ((sपंचांग32_hash_पढ़ो(hdev, HASH_SR) & HASH_SR_BUSY))
		cpu_relax();

	rctx->hw_context = kदो_स्मृति_array(3 + HASH_CSR_REGISTER_NUMBER,
					 माप(u32),
					 GFP_KERNEL);

	preg = rctx->hw_context;

	*preg++ = sपंचांग32_hash_पढ़ो(hdev, HASH_IMR);
	*preg++ = sपंचांग32_hash_पढ़ो(hdev, HASH_STR);
	*preg++ = sपंचांग32_hash_पढ़ो(hdev, HASH_CR);
	क्रम (i = 0; i < HASH_CSR_REGISTER_NUMBER; i++)
		*preg++ = sपंचांग32_hash_पढ़ो(hdev, HASH_CSR(i));

	pm_runसमय_mark_last_busy(hdev->dev);
	pm_runसमय_put_स्वतःsuspend(hdev->dev);

	स_नकल(out, rctx, माप(*rctx));

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा sपंचांग32_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा sपंचांग32_hash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	काष्ठा sपंचांग32_hash_dev *hdev = sपंचांग32_hash_find_dev(ctx);
	स्थिर u32 *preg = in;
	u32 reg;
	अचिन्हित पूर्णांक i;

	स_नकल(rctx, in, माप(*rctx));

	preg = rctx->hw_context;

	pm_runसमय_resume_and_get(hdev->dev);

	sपंचांग32_hash_ग_लिखो(hdev, HASH_IMR, *preg++);
	sपंचांग32_hash_ग_लिखो(hdev, HASH_STR, *preg++);
	sपंचांग32_hash_ग_लिखो(hdev, HASH_CR, *preg);
	reg = *preg++ | HASH_CR_INIT;
	sपंचांग32_hash_ग_लिखो(hdev, HASH_CR, reg);

	क्रम (i = 0; i < HASH_CSR_REGISTER_NUMBER; i++)
		sपंचांग32_hash_ग_लिखो(hdev, HASH_CSR(i), *preg++);

	pm_runसमय_mark_last_busy(hdev->dev);
	pm_runसमय_put_स्वतःsuspend(hdev->dev);

	kमुक्त(rctx->hw_context);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_setkey(काष्ठा crypto_ahash *tfm,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा sपंचांग32_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	अगर (keylen <= HASH_MAX_KEY_SIZE) अणु
		स_नकल(ctx->key, key, keylen);
		ctx->keylen = keylen;
	पूर्ण अन्यथा अणु
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_cra_init_algs(काष्ठा crypto_tfm *tfm,
				    स्थिर अक्षर *algs_hmac_name)
अणु
	काष्ठा sपंचांग32_hash_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा sपंचांग32_hash_request_ctx));

	ctx->keylen = 0;

	अगर (algs_hmac_name)
		ctx->flags |= HASH_FLAGS_HMAC;

	ctx->enginectx.op.करो_one_request = sपंचांग32_hash_one_request;
	ctx->enginectx.op.prepare_request = sपंचांग32_hash_prepare_req;
	ctx->enginectx.op.unprepare_request = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस sपंचांग32_hash_cra_init_algs(tfm, शून्य);
पूर्ण

अटल पूर्णांक sपंचांग32_hash_cra_md5_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस sपंचांग32_hash_cra_init_algs(tfm, "md5");
पूर्ण

अटल पूर्णांक sपंचांग32_hash_cra_sha1_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस sपंचांग32_hash_cra_init_algs(tfm, "sha1");
पूर्ण

अटल पूर्णांक sपंचांग32_hash_cra_sha224_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस sपंचांग32_hash_cra_init_algs(tfm, "sha224");
पूर्ण

अटल पूर्णांक sपंचांग32_hash_cra_sha256_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस sपंचांग32_hash_cra_init_algs(tfm, "sha256");
पूर्ण

अटल irqवापस_t sपंचांग32_hash_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sपंचांग32_hash_dev *hdev = dev_id;

	अगर (HASH_FLAGS_CPU & hdev->flags) अणु
		अगर (HASH_FLAGS_OUTPUT_READY & hdev->flags) अणु
			hdev->flags &= ~HASH_FLAGS_OUTPUT_READY;
			जाओ finish;
		पूर्ण
	पूर्ण अन्यथा अगर (HASH_FLAGS_DMA_READY & hdev->flags) अणु
		अगर (HASH_FLAGS_DMA_ACTIVE & hdev->flags) अणु
			hdev->flags &= ~HASH_FLAGS_DMA_ACTIVE;
				जाओ finish;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;

finish:
	/* Finish current request */
	sपंचांग32_hash_finish_req(hdev->req, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sपंचांग32_hash_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sपंचांग32_hash_dev *hdev = dev_id;
	u32 reg;

	reg = sपंचांग32_hash_पढ़ो(hdev, HASH_SR);
	अगर (reg & HASH_SR_OUTPUT_READY) अणु
		reg &= ~HASH_SR_OUTPUT_READY;
		sपंचांग32_hash_ग_लिखो(hdev, HASH_SR, reg);
		hdev->flags |= HASH_FLAGS_OUTPUT_READY;
		/* Disable IT*/
		sपंचांग32_hash_ग_लिखो(hdev, HASH_IMR, 0);
		वापस IRQ_WAKE_THREAD;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल काष्ठा ahash_alg algs_md5_sha1[] = अणु
	अणु
		.init = sपंचांग32_hash_init,
		.update = sपंचांग32_hash_update,
		.final = sपंचांग32_hash_final,
		.finup = sपंचांग32_hash_finup,
		.digest = sपंचांग32_hash_digest,
		.export = sपंचांग32_hash_export,
		.import = sपंचांग32_hash_import,
		.halg = अणु
			.digestsize = MD5_DIGEST_SIZE,
			.statesize = माप(काष्ठा sपंचांग32_hash_request_ctx),
			.base = अणु
				.cra_name = "md5",
				.cra_driver_name = "stm32-md5",
				.cra_priority = 200,
				.cra_flags = CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = MD5_HMAC_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sपंचांग32_hash_ctx),
				.cra_alignmask = 3,
				.cra_init = sपंचांग32_hash_cra_init,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.init = sपंचांग32_hash_init,
		.update = sपंचांग32_hash_update,
		.final = sपंचांग32_hash_final,
		.finup = sपंचांग32_hash_finup,
		.digest = sपंचांग32_hash_digest,
		.export = sपंचांग32_hash_export,
		.import = sपंचांग32_hash_import,
		.setkey = sपंचांग32_hash_setkey,
		.halg = अणु
			.digestsize = MD5_DIGEST_SIZE,
			.statesize = माप(काष्ठा sपंचांग32_hash_request_ctx),
			.base = अणु
				.cra_name = "hmac(md5)",
				.cra_driver_name = "stm32-hmac-md5",
				.cra_priority = 200,
				.cra_flags = CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = MD5_HMAC_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sपंचांग32_hash_ctx),
				.cra_alignmask = 3,
				.cra_init = sपंचांग32_hash_cra_md5_init,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.init = sपंचांग32_hash_init,
		.update = sपंचांग32_hash_update,
		.final = sपंचांग32_hash_final,
		.finup = sपंचांग32_hash_finup,
		.digest = sपंचांग32_hash_digest,
		.export = sपंचांग32_hash_export,
		.import = sपंचांग32_hash_import,
		.halg = अणु
			.digestsize = SHA1_DIGEST_SIZE,
			.statesize = माप(काष्ठा sपंचांग32_hash_request_ctx),
			.base = अणु
				.cra_name = "sha1",
				.cra_driver_name = "stm32-sha1",
				.cra_priority = 200,
				.cra_flags = CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sपंचांग32_hash_ctx),
				.cra_alignmask = 3,
				.cra_init = sपंचांग32_hash_cra_init,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.init = sपंचांग32_hash_init,
		.update = sपंचांग32_hash_update,
		.final = sपंचांग32_hash_final,
		.finup = sपंचांग32_hash_finup,
		.digest = sपंचांग32_hash_digest,
		.export = sपंचांग32_hash_export,
		.import = sपंचांग32_hash_import,
		.setkey = sपंचांग32_hash_setkey,
		.halg = अणु
			.digestsize = SHA1_DIGEST_SIZE,
			.statesize = माप(काष्ठा sपंचांग32_hash_request_ctx),
			.base = अणु
				.cra_name = "hmac(sha1)",
				.cra_driver_name = "stm32-hmac-sha1",
				.cra_priority = 200,
				.cra_flags = CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sपंचांग32_hash_ctx),
				.cra_alignmask = 3,
				.cra_init = sपंचांग32_hash_cra_sha1_init,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा ahash_alg algs_sha224_sha256[] = अणु
	अणु
		.init = sपंचांग32_hash_init,
		.update = sपंचांग32_hash_update,
		.final = sपंचांग32_hash_final,
		.finup = sपंचांग32_hash_finup,
		.digest = sपंचांग32_hash_digest,
		.export = sपंचांग32_hash_export,
		.import = sपंचांग32_hash_import,
		.halg = अणु
			.digestsize = SHA224_DIGEST_SIZE,
			.statesize = माप(काष्ठा sपंचांग32_hash_request_ctx),
			.base = अणु
				.cra_name = "sha224",
				.cra_driver_name = "stm32-sha224",
				.cra_priority = 200,
				.cra_flags = CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA224_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sपंचांग32_hash_ctx),
				.cra_alignmask = 3,
				.cra_init = sपंचांग32_hash_cra_init,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.init = sपंचांग32_hash_init,
		.update = sपंचांग32_hash_update,
		.final = sपंचांग32_hash_final,
		.finup = sपंचांग32_hash_finup,
		.digest = sपंचांग32_hash_digest,
		.setkey = sपंचांग32_hash_setkey,
		.export = sपंचांग32_hash_export,
		.import = sपंचांग32_hash_import,
		.halg = अणु
			.digestsize = SHA224_DIGEST_SIZE,
			.statesize = माप(काष्ठा sपंचांग32_hash_request_ctx),
			.base = अणु
				.cra_name = "hmac(sha224)",
				.cra_driver_name = "stm32-hmac-sha224",
				.cra_priority = 200,
				.cra_flags = CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA224_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sपंचांग32_hash_ctx),
				.cra_alignmask = 3,
				.cra_init = sपंचांग32_hash_cra_sha224_init,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.init = sपंचांग32_hash_init,
		.update = sपंचांग32_hash_update,
		.final = sपंचांग32_hash_final,
		.finup = sपंचांग32_hash_finup,
		.digest = sपंचांग32_hash_digest,
		.export = sपंचांग32_hash_export,
		.import = sपंचांग32_hash_import,
		.halg = अणु
			.digestsize = SHA256_DIGEST_SIZE,
			.statesize = माप(काष्ठा sपंचांग32_hash_request_ctx),
			.base = अणु
				.cra_name = "sha256",
				.cra_driver_name = "stm32-sha256",
				.cra_priority = 200,
				.cra_flags = CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sपंचांग32_hash_ctx),
				.cra_alignmask = 3,
				.cra_init = sपंचांग32_hash_cra_init,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.init = sपंचांग32_hash_init,
		.update = sपंचांग32_hash_update,
		.final = sपंचांग32_hash_final,
		.finup = sपंचांग32_hash_finup,
		.digest = sपंचांग32_hash_digest,
		.export = sपंचांग32_hash_export,
		.import = sपंचांग32_hash_import,
		.setkey = sपंचांग32_hash_setkey,
		.halg = अणु
			.digestsize = SHA256_DIGEST_SIZE,
			.statesize = माप(काष्ठा sपंचांग32_hash_request_ctx),
			.base = अणु
				.cra_name = "hmac(sha256)",
				.cra_driver_name = "stm32-hmac-sha256",
				.cra_priority = 200,
				.cra_flags = CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sपंचांग32_hash_ctx),
				.cra_alignmask = 3,
				.cra_init = sपंचांग32_hash_cra_sha256_init,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांग32_hash_रेजिस्टर_algs(काष्ठा sपंचांग32_hash_dev *hdev)
अणु
	अचिन्हित पूर्णांक i, j;
	पूर्णांक err;

	क्रम (i = 0; i < hdev->pdata->algs_info_size; i++) अणु
		क्रम (j = 0; j < hdev->pdata->algs_info[i].size; j++) अणु
			err = crypto_रेजिस्टर_ahash(
				&hdev->pdata->algs_info[i].algs_list[j]);
			अगर (err)
				जाओ err_algs;
		पूर्ण
	पूर्ण

	वापस 0;
err_algs:
	dev_err(hdev->dev, "Algo %d : %d failed\n", i, j);
	क्रम (; i--; ) अणु
		क्रम (; j--;)
			crypto_unरेजिस्टर_ahash(
				&hdev->pdata->algs_info[i].algs_list[j]);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_unरेजिस्टर_algs(काष्ठा sपंचांग32_hash_dev *hdev)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < hdev->pdata->algs_info_size; i++) अणु
		क्रम (j = 0; j < hdev->pdata->algs_info[i].size; j++)
			crypto_unरेजिस्टर_ahash(
				&hdev->pdata->algs_info[i].algs_list[j]);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sपंचांग32_hash_algs_info sपंचांग32_hash_algs_info_sपंचांग32f4[] = अणु
	अणु
		.algs_list	= algs_md5_sha1,
		.size		= ARRAY_SIZE(algs_md5_sha1),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_hash_pdata sपंचांग32_hash_pdata_sपंचांग32f4 = अणु
	.algs_info	= sपंचांग32_hash_algs_info_sपंचांग32f4,
	.algs_info_size	= ARRAY_SIZE(sपंचांग32_hash_algs_info_sपंचांग32f4),
पूर्ण;

अटल काष्ठा sपंचांग32_hash_algs_info sपंचांग32_hash_algs_info_sपंचांग32f7[] = अणु
	अणु
		.algs_list	= algs_md5_sha1,
		.size		= ARRAY_SIZE(algs_md5_sha1),
	पूर्ण,
	अणु
		.algs_list	= algs_sha224_sha256,
		.size		= ARRAY_SIZE(algs_sha224_sha256),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_hash_pdata sपंचांग32_hash_pdata_sपंचांग32f7 = अणु
	.algs_info	= sपंचांग32_hash_algs_info_sपंचांग32f7,
	.algs_info_size	= ARRAY_SIZE(sपंचांग32_hash_algs_info_sपंचांग32f7),
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_hash_of_match[] = अणु
	अणु
		.compatible = "st,stm32f456-hash",
		.data = &sपंचांग32_hash_pdata_sपंचांग32f4,
	पूर्ण,
	अणु
		.compatible = "st,stm32f756-hash",
		.data = &sपंचांग32_hash_pdata_sपंचांग32f7,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, sपंचांग32_hash_of_match);

अटल पूर्णांक sपंचांग32_hash_get_of_match(काष्ठा sपंचांग32_hash_dev *hdev,
				   काष्ठा device *dev)
अणु
	hdev->pdata = of_device_get_match_data(dev);
	अगर (!hdev->pdata) अणु
		dev_err(dev, "no compatible OF match\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(dev->of_node, "dma-maxburst",
				 &hdev->dma_maxburst)) अणु
		dev_info(dev, "dma-maxburst not specified, using 0\n");
		hdev->dma_maxburst = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_hash_dev *hdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	hdev = devm_kzalloc(dev, माप(*hdev), GFP_KERNEL);
	अगर (!hdev)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hdev->io_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(hdev->io_base))
		वापस PTR_ERR(hdev->io_base);

	hdev->phys_base = res->start;

	ret = sपंचांग32_hash_get_of_match(hdev, dev);
	अगर (ret)
		वापस ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(dev, irq, sपंचांग32_hash_irq_handler,
					sपंचांग32_hash_irq_thपढ़ो, IRQF_ONESHOT,
					dev_name(dev), hdev);
	अगर (ret) अणु
		dev_err(dev, "Cannot grab IRQ\n");
		वापस ret;
	पूर्ण

	hdev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(hdev->clk))
		वापस dev_err_probe(dev, PTR_ERR(hdev->clk),
				     "failed to get clock for hash\n");

	ret = clk_prepare_enable(hdev->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable hash clock (%d)\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(dev, HASH_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(dev);

	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	hdev->rst = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(hdev->rst)) अणु
		अगर (PTR_ERR(hdev->rst) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ err_reset;
		पूर्ण
	पूर्ण अन्यथा अणु
		reset_control_निश्चित(hdev->rst);
		udelay(2);
		reset_control_deनिश्चित(hdev->rst);
	पूर्ण

	hdev->dev = dev;

	platक्रमm_set_drvdata(pdev, hdev);

	ret = sपंचांग32_hash_dma_init(hdev);
	चयन (ret) अणु
	हाल 0:
		अवरोध;
	हाल -ENOENT:
		dev_dbg(dev, "DMA mode not available\n");
		अवरोध;
	शेष:
		जाओ err_dma;
	पूर्ण

	spin_lock(&sपंचांग32_hash.lock);
	list_add_tail(&hdev->list, &sपंचांग32_hash.dev_list);
	spin_unlock(&sपंचांग32_hash.lock);

	/* Initialize crypto engine */
	hdev->engine = crypto_engine_alloc_init(dev, 1);
	अगर (!hdev->engine) अणु
		ret = -ENOMEM;
		जाओ err_engine;
	पूर्ण

	ret = crypto_engine_start(hdev->engine);
	अगर (ret)
		जाओ err_engine_start;

	hdev->dma_mode = sपंचांग32_hash_पढ़ो(hdev, HASH_HWCFGR);

	/* Register algos */
	ret = sपंचांग32_hash_रेजिस्टर_algs(hdev);
	अगर (ret)
		जाओ err_algs;

	dev_info(dev, "Init HASH done HW ver %x DMA mode %u\n",
		 sपंचांग32_hash_पढ़ो(hdev, HASH_VER), hdev->dma_mode);

	pm_runसमय_put_sync(dev);

	वापस 0;

err_algs:
err_engine_start:
	crypto_engine_निकास(hdev->engine);
err_engine:
	spin_lock(&sपंचांग32_hash.lock);
	list_del(&hdev->list);
	spin_unlock(&sपंचांग32_hash.lock);
err_dma:
	अगर (hdev->dma_lch)
		dma_release_channel(hdev->dma_lch);
err_reset:
	pm_runसमय_disable(dev);
	pm_runसमय_put_noidle(dev);

	clk_disable_unprepare(hdev->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_hash_dev *hdev;
	पूर्णांक ret;

	hdev = platक्रमm_get_drvdata(pdev);
	अगर (!hdev)
		वापस -ENODEV;

	ret = pm_runसमय_resume_and_get(hdev->dev);
	अगर (ret < 0)
		वापस ret;

	sपंचांग32_hash_unरेजिस्टर_algs(hdev);

	crypto_engine_निकास(hdev->engine);

	spin_lock(&sपंचांग32_hash.lock);
	list_del(&hdev->list);
	spin_unlock(&sपंचांग32_hash.lock);

	अगर (hdev->dma_lch)
		dma_release_channel(hdev->dma_lch);

	pm_runसमय_disable(hdev->dev);
	pm_runसमय_put_noidle(hdev->dev);

	clk_disable_unprepare(hdev->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sपंचांग32_hash_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_hash_dev *hdev = dev_get_drvdata(dev);

	clk_disable_unprepare(hdev->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_hash_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_hash_dev *hdev = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(hdev->clk);
	अगर (ret) अणु
		dev_err(hdev->dev, "Failed to prepare_enable clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_hash_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(sपंचांग32_hash_runसमय_suspend,
			   sपंचांग32_hash_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sपंचांग32_hash_driver = अणु
	.probe		= sपंचांग32_hash_probe,
	.हटाओ		= sपंचांग32_hash_हटाओ,
	.driver		= अणु
		.name	= "stm32-hash",
		.pm = &sपंचांग32_hash_pm_ops,
		.of_match_table	= sपंचांग32_hash_of_match,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(sपंचांग32_hash_driver);

MODULE_DESCRIPTION("STM32 SHA1/224/256 & MD5 (HMAC) hw accelerator driver");
MODULE_AUTHOR("Lionel Debieve <lionel.debieve@st.com>");
MODULE_LICENSE("GPL v2");
