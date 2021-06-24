<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2014 Emilio Lथकpez
 * Emilio Lथकpez <emilio@elopez.com.ar>
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "virt-dma.h"

/** Common macros to normal and dedicated DMA रेजिस्टरs **/

#घोषणा SUN4I_DMA_CFG_LOADING			BIT(31)
#घोषणा SUN4I_DMA_CFG_DST_DATA_WIDTH(width)	((width) << 25)
#घोषणा SUN4I_DMA_CFG_DST_BURST_LENGTH(len)	((len) << 23)
#घोषणा SUN4I_DMA_CFG_DST_ADDR_MODE(mode)	((mode) << 21)
#घोषणा SUN4I_DMA_CFG_DST_DRQ_TYPE(type)	((type) << 16)
#घोषणा SUN4I_DMA_CFG_SRC_DATA_WIDTH(width)	((width) << 9)
#घोषणा SUN4I_DMA_CFG_SRC_BURST_LENGTH(len)	((len) << 7)
#घोषणा SUN4I_DMA_CFG_SRC_ADDR_MODE(mode)	((mode) << 5)
#घोषणा SUN4I_DMA_CFG_SRC_DRQ_TYPE(type)	(type)

/** Normal DMA रेजिस्टर values **/

/* Normal DMA source/destination data request type values */
#घोषणा SUN4I_NDMA_DRQ_TYPE_SDRAM		0x16
#घोषणा SUN4I_NDMA_DRQ_TYPE_LIMIT		(0x1F + 1)

/** Normal DMA रेजिस्टर layout **/

/* Dedicated DMA source/destination address mode values */
#घोषणा SUN4I_NDMA_ADDR_MODE_LINEAR		0
#घोषणा SUN4I_NDMA_ADDR_MODE_IO			1

/* Normal DMA configuration रेजिस्टर layout */
#घोषणा SUN4I_NDMA_CFG_CONT_MODE		BIT(30)
#घोषणा SUN4I_NDMA_CFG_WAIT_STATE(n)		((n) << 27)
#घोषणा SUN4I_NDMA_CFG_DST_NON_SECURE		BIT(22)
#घोषणा SUN4I_NDMA_CFG_BYTE_COUNT_MODE_REMAIN	BIT(15)
#घोषणा SUN4I_NDMA_CFG_SRC_NON_SECURE		BIT(6)

/** Dedicated DMA रेजिस्टर values **/

/* Dedicated DMA source/destination address mode values */
#घोषणा SUN4I_DDMA_ADDR_MODE_LINEAR		0
#घोषणा SUN4I_DDMA_ADDR_MODE_IO			1
#घोषणा SUN4I_DDMA_ADDR_MODE_HORIZONTAL_PAGE	2
#घोषणा SUN4I_DDMA_ADDR_MODE_VERTICAL_PAGE	3

/* Dedicated DMA source/destination data request type values */
#घोषणा SUN4I_DDMA_DRQ_TYPE_SDRAM		0x1
#घोषणा SUN4I_DDMA_DRQ_TYPE_LIMIT		(0x1F + 1)

/** Dedicated DMA रेजिस्टर layout **/

/* Dedicated DMA configuration रेजिस्टर layout */
#घोषणा SUN4I_DDMA_CFG_BUSY			BIT(30)
#घोषणा SUN4I_DDMA_CFG_CONT_MODE		BIT(29)
#घोषणा SUN4I_DDMA_CFG_DST_NON_SECURE		BIT(28)
#घोषणा SUN4I_DDMA_CFG_BYTE_COUNT_MODE_REMAIN	BIT(15)
#घोषणा SUN4I_DDMA_CFG_SRC_NON_SECURE		BIT(12)

/* Dedicated DMA parameter रेजिस्टर layout */
#घोषणा SUN4I_DDMA_PARA_DST_DATA_BLK_SIZE(n)	(((n) - 1) << 24)
#घोषणा SUN4I_DDMA_PARA_DST_WAIT_CYCLES(n)	(((n) - 1) << 16)
#घोषणा SUN4I_DDMA_PARA_SRC_DATA_BLK_SIZE(n)	(((n) - 1) << 8)
#घोषणा SUN4I_DDMA_PARA_SRC_WAIT_CYCLES(n)	(((n) - 1) << 0)

/** DMA रेजिस्टर offsets **/

/* General रेजिस्टर offsets */
#घोषणा SUN4I_DMA_IRQ_ENABLE_REG		0x0
#घोषणा SUN4I_DMA_IRQ_PENDING_STATUS_REG	0x4

/* Normal DMA रेजिस्टर offsets */
#घोषणा SUN4I_NDMA_CHANNEL_REG_BASE(n)		(0x100 + (n) * 0x20)
#घोषणा SUN4I_NDMA_CFG_REG			0x0
#घोषणा SUN4I_NDMA_SRC_ADDR_REG			0x4
#घोषणा SUN4I_NDMA_DST_ADDR_REG		0x8
#घोषणा SUN4I_NDMA_BYTE_COUNT_REG		0xC

/* Dedicated DMA रेजिस्टर offsets */
#घोषणा SUN4I_DDMA_CHANNEL_REG_BASE(n)		(0x300 + (n) * 0x20)
#घोषणा SUN4I_DDMA_CFG_REG			0x0
#घोषणा SUN4I_DDMA_SRC_ADDR_REG			0x4
#घोषणा SUN4I_DDMA_DST_ADDR_REG		0x8
#घोषणा SUN4I_DDMA_BYTE_COUNT_REG		0xC
#घोषणा SUN4I_DDMA_PARA_REG			0x18

/** DMA Driver **/

/*
 * Normal DMA has 8 channels, and Dedicated DMA has another 8, so
 * that's 16 channels. As for endpoints, there's 29 and 21
 * respectively. Given that the Normal DMA endpoपूर्णांकs (other than
 * SDRAM) can be used as tx/rx, we need 78 vchans in total
 */
#घोषणा SUN4I_NDMA_NR_MAX_CHANNELS	8
#घोषणा SUN4I_DDMA_NR_MAX_CHANNELS	8
#घोषणा SUN4I_DMA_NR_MAX_CHANNELS					\
	(SUN4I_NDMA_NR_MAX_CHANNELS + SUN4I_DDMA_NR_MAX_CHANNELS)
#घोषणा SUN4I_NDMA_NR_MAX_VCHANS	(29 * 2 - 1)
#घोषणा SUN4I_DDMA_NR_MAX_VCHANS	21
#घोषणा SUN4I_DMA_NR_MAX_VCHANS						\
	(SUN4I_NDMA_NR_MAX_VCHANS + SUN4I_DDMA_NR_MAX_VCHANS)

/* This set of SUN4I_DDMA timing parameters were found experimentally जबतक
 * working with the SPI driver and seem to make it behave correctly */
#घोषणा SUN4I_DDMA_MAGIC_SPI_PARAMETERS \
	(SUN4I_DDMA_PARA_DST_DATA_BLK_SIZE(1) |			\
	 SUN4I_DDMA_PARA_SRC_DATA_BLK_SIZE(1) |				\
	 SUN4I_DDMA_PARA_DST_WAIT_CYCLES(2) |				\
	 SUN4I_DDMA_PARA_SRC_WAIT_CYCLES(2))

काष्ठा sun4i_dma_pchan अणु
	/* Register base of channel */
	व्योम __iomem			*base;
	/* vchan currently being serviced */
	काष्ठा sun4i_dma_vchan		*vchan;
	/* Is this a dedicated pchan? */
	पूर्णांक				is_dedicated;
पूर्ण;

काष्ठा sun4i_dma_vchan अणु
	काष्ठा virt_dma_chan		vc;
	काष्ठा dma_slave_config		cfg;
	काष्ठा sun4i_dma_pchan		*pchan;
	काष्ठा sun4i_dma_promise	*processing;
	काष्ठा sun4i_dma_contract	*contract;
	u8				endpoपूर्णांक;
	पूर्णांक				is_dedicated;
पूर्ण;

काष्ठा sun4i_dma_promise अणु
	u32				cfg;
	u32				para;
	dma_addr_t			src;
	dma_addr_t			dst;
	माप_प्रकार				len;
	काष्ठा list_head		list;
पूर्ण;

/* A contract is a set of promises */
काष्ठा sun4i_dma_contract अणु
	काष्ठा virt_dma_desc		vd;
	काष्ठा list_head		demands;
	काष्ठा list_head		completed_demands;
	पूर्णांक				is_cyclic;
पूर्ण;

काष्ठा sun4i_dma_dev अणु
	DECLARE_BITMAP(pchans_used, SUN4I_DMA_NR_MAX_CHANNELS);
	काष्ठा dma_device		slave;
	काष्ठा sun4i_dma_pchan		*pchans;
	काष्ठा sun4i_dma_vchan		*vchans;
	व्योम __iomem			*base;
	काष्ठा clk			*clk;
	पूर्णांक				irq;
	spinlock_t			lock;
पूर्ण;

अटल काष्ठा sun4i_dma_dev *to_sun4i_dma_dev(काष्ठा dma_device *dev)
अणु
	वापस container_of(dev, काष्ठा sun4i_dma_dev, slave);
पूर्ण

अटल काष्ठा sun4i_dma_vchan *to_sun4i_dma_vchan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा sun4i_dma_vchan, vc.chan);
पूर्ण

अटल काष्ठा sun4i_dma_contract *to_sun4i_dma_contract(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा sun4i_dma_contract, vd);
पूर्ण

अटल काष्ठा device *chan2dev(काष्ठा dma_chan *chan)
अणु
	वापस &chan->dev->device;
पूर्ण

अटल पूर्णांक convert_burst(u32 maxburst)
अणु
	अगर (maxburst > 8)
		वापस -EINVAL;

	/* 1 -> 0, 4 -> 1, 8 -> 2 */
	वापस (maxburst >> 2);
पूर्ण

अटल पूर्णांक convert_buswidth(क्रमागत dma_slave_buswidth addr_width)
अणु
	अगर (addr_width > DMA_SLAVE_BUSWIDTH_4_BYTES)
		वापस -EINVAL;

	/* 8 (1 byte) -> 0, 16 (2 bytes) -> 1, 32 (4 bytes) -> 2 */
	वापस (addr_width >> 1);
पूर्ण

अटल व्योम sun4i_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);

	vchan_मुक्त_chan_resources(&vchan->vc);
पूर्ण

अटल काष्ठा sun4i_dma_pchan *find_and_use_pchan(काष्ठा sun4i_dma_dev *priv,
						  काष्ठा sun4i_dma_vchan *vchan)
अणु
	काष्ठा sun4i_dma_pchan *pchan = शून्य, *pchans = priv->pchans;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, max;

	/*
	 * pchans 0-SUN4I_NDMA_NR_MAX_CHANNELS are normal, and
	 * SUN4I_NDMA_NR_MAX_CHANNELS+ are dedicated ones
	 */
	अगर (vchan->is_dedicated) अणु
		i = SUN4I_NDMA_NR_MAX_CHANNELS;
		max = SUN4I_DMA_NR_MAX_CHANNELS;
	पूर्ण अन्यथा अणु
		i = 0;
		max = SUN4I_NDMA_NR_MAX_CHANNELS;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	क्रम_each_clear_bit_from(i, priv->pchans_used, max) अणु
		pchan = &pchans[i];
		pchan->vchan = vchan;
		set_bit(i, priv->pchans_used);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस pchan;
पूर्ण

अटल व्योम release_pchan(काष्ठा sun4i_dma_dev *priv,
			  काष्ठा sun4i_dma_pchan *pchan)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक nr = pchan - priv->pchans;

	spin_lock_irqsave(&priv->lock, flags);

	pchan->vchan = शून्य;
	clear_bit(nr, priv->pchans_used);

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम configure_pchan(काष्ठा sun4i_dma_pchan *pchan,
			    काष्ठा sun4i_dma_promise *d)
अणु
	/*
	 * Configure addresses and misc parameters depending on type
	 * SUN4I_DDMA has an extra field with timing parameters
	 */
	अगर (pchan->is_dedicated) अणु
		ग_लिखोl_relaxed(d->src, pchan->base + SUN4I_DDMA_SRC_ADDR_REG);
		ग_लिखोl_relaxed(d->dst, pchan->base + SUN4I_DDMA_DST_ADDR_REG);
		ग_लिखोl_relaxed(d->len, pchan->base + SUN4I_DDMA_BYTE_COUNT_REG);
		ग_लिखोl_relaxed(d->para, pchan->base + SUN4I_DDMA_PARA_REG);
		ग_लिखोl_relaxed(d->cfg, pchan->base + SUN4I_DDMA_CFG_REG);
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(d->src, pchan->base + SUN4I_NDMA_SRC_ADDR_REG);
		ग_लिखोl_relaxed(d->dst, pchan->base + SUN4I_NDMA_DST_ADDR_REG);
		ग_लिखोl_relaxed(d->len, pchan->base + SUN4I_NDMA_BYTE_COUNT_REG);
		ग_लिखोl_relaxed(d->cfg, pchan->base + SUN4I_NDMA_CFG_REG);
	पूर्ण
पूर्ण

अटल व्योम set_pchan_पूर्णांकerrupt(काष्ठा sun4i_dma_dev *priv,
				काष्ठा sun4i_dma_pchan *pchan,
				पूर्णांक half, पूर्णांक end)
अणु
	u32 reg;
	पूर्णांक pchan_number = pchan - priv->pchans;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	reg = पढ़ोl_relaxed(priv->base + SUN4I_DMA_IRQ_ENABLE_REG);

	अगर (half)
		reg |= BIT(pchan_number * 2);
	अन्यथा
		reg &= ~BIT(pchan_number * 2);

	अगर (end)
		reg |= BIT(pchan_number * 2 + 1);
	अन्यथा
		reg &= ~BIT(pchan_number * 2 + 1);

	ग_लिखोl_relaxed(reg, priv->base + SUN4I_DMA_IRQ_ENABLE_REG);

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

/*
 * Execute pending operations on a vchan
 *
 * When given a vchan, this function will try to acquire a suitable
 * pchan and, अगर successful, will configure it to fulfill a promise
 * from the next pending contract.
 *
 * This function must be called with &vchan->vc.lock held.
 */
अटल पूर्णांक __execute_vchan_pending(काष्ठा sun4i_dma_dev *priv,
				   काष्ठा sun4i_dma_vchan *vchan)
अणु
	काष्ठा sun4i_dma_promise *promise = शून्य;
	काष्ठा sun4i_dma_contract *contract = शून्य;
	काष्ठा sun4i_dma_pchan *pchan;
	काष्ठा virt_dma_desc *vd;
	पूर्णांक ret;

	lockdep_निश्चित_held(&vchan->vc.lock);

	/* We need a pchan to करो anything, so secure one अगर available */
	pchan = find_and_use_pchan(priv, vchan);
	अगर (!pchan)
		वापस -EBUSY;

	/*
	 * Channel endpoपूर्णांकs must not be repeated, so अगर this vchan
	 * has alपढ़ोy submitted some work, we can't करो anything अन्यथा
	 */
	अगर (vchan->processing) अणु
		dev_dbg(chan2dev(&vchan->vc.chan),
			"processing something to this endpoint already\n");
		ret = -EBUSY;
		जाओ release_pchan;
	पूर्ण

	करो अणु
		/* Figure out which contract we're working with today */
		vd = vchan_next_desc(&vchan->vc);
		अगर (!vd) अणु
			dev_dbg(chan2dev(&vchan->vc.chan),
				"No pending contract found");
			ret = 0;
			जाओ release_pchan;
		पूर्ण

		contract = to_sun4i_dma_contract(vd);
		अगर (list_empty(&contract->demands)) अणु
			/* The contract has been completed so mark it as such */
			list_del(&contract->vd.node);
			vchan_cookie_complete(&contract->vd);
			dev_dbg(chan2dev(&vchan->vc.chan),
				"Empty contract found and marked complete");
		पूर्ण
	पूर्ण जबतक (list_empty(&contract->demands));

	/* Now find out what we need to करो */
	promise = list_first_entry(&contract->demands,
				   काष्ठा sun4i_dma_promise, list);
	vchan->processing = promise;

	/* ... and make it reality */
	अगर (promise) अणु
		vchan->contract = contract;
		vchan->pchan = pchan;
		set_pchan_पूर्णांकerrupt(priv, pchan, contract->is_cyclic, 1);
		configure_pchan(pchan, promise);
	पूर्ण

	वापस 0;

release_pchan:
	release_pchan(priv, pchan);
	वापस ret;
पूर्ण

अटल पूर्णांक sanitize_config(काष्ठा dma_slave_config *sconfig,
			   क्रमागत dma_transfer_direction direction)
अणु
	चयन (direction) अणु
	हाल DMA_MEM_TO_DEV:
		अगर ((sconfig->dst_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED) ||
		    !sconfig->dst_maxburst)
			वापस -EINVAL;

		अगर (sconfig->src_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED)
			sconfig->src_addr_width = sconfig->dst_addr_width;

		अगर (!sconfig->src_maxburst)
			sconfig->src_maxburst = sconfig->dst_maxburst;

		अवरोध;

	हाल DMA_DEV_TO_MEM:
		अगर ((sconfig->src_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED) ||
		    !sconfig->src_maxburst)
			वापस -EINVAL;

		अगर (sconfig->dst_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED)
			sconfig->dst_addr_width = sconfig->src_addr_width;

		अगर (!sconfig->dst_maxburst)
			sconfig->dst_maxburst = sconfig->src_maxburst;

		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Generate a promise, to be used in a normal DMA contract.
 *
 * A NDMA promise contains all the inक्रमmation required to program the
 * normal part of the DMA Engine and get data copied. A non-executed
 * promise will live in the demands list on a contract. Once it has been
 * completed, it will be moved to the completed demands list क्रम later मुक्तing.
 * All linked promises will be मुक्तd when the corresponding contract is मुक्तd
 */
अटल काष्ठा sun4i_dma_promise *
generate_ndma_promise(काष्ठा dma_chan *chan, dma_addr_t src, dma_addr_t dest,
		      माप_प्रकार len, काष्ठा dma_slave_config *sconfig,
		      क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा sun4i_dma_promise *promise;
	पूर्णांक ret;

	ret = sanitize_config(sconfig, direction);
	अगर (ret)
		वापस शून्य;

	promise = kzalloc(माप(*promise), GFP_NOWAIT);
	अगर (!promise)
		वापस शून्य;

	promise->src = src;
	promise->dst = dest;
	promise->len = len;
	promise->cfg = SUN4I_DMA_CFG_LOADING |
		SUN4I_NDMA_CFG_BYTE_COUNT_MODE_REMAIN;

	dev_dbg(chan2dev(chan),
		"src burst %d, dst burst %d, src buswidth %d, dst buswidth %d",
		sconfig->src_maxburst, sconfig->dst_maxburst,
		sconfig->src_addr_width, sconfig->dst_addr_width);

	/* Source burst */
	ret = convert_burst(sconfig->src_maxburst);
	अगर (ret < 0)
		जाओ fail;
	promise->cfg |= SUN4I_DMA_CFG_SRC_BURST_LENGTH(ret);

	/* Destination burst */
	ret = convert_burst(sconfig->dst_maxburst);
	अगर (ret < 0)
		जाओ fail;
	promise->cfg |= SUN4I_DMA_CFG_DST_BURST_LENGTH(ret);

	/* Source bus width */
	ret = convert_buswidth(sconfig->src_addr_width);
	अगर (ret < 0)
		जाओ fail;
	promise->cfg |= SUN4I_DMA_CFG_SRC_DATA_WIDTH(ret);

	/* Destination bus width */
	ret = convert_buswidth(sconfig->dst_addr_width);
	अगर (ret < 0)
		जाओ fail;
	promise->cfg |= SUN4I_DMA_CFG_DST_DATA_WIDTH(ret);

	वापस promise;

fail:
	kमुक्त(promise);
	वापस शून्य;
पूर्ण

/*
 * Generate a promise, to be used in a dedicated DMA contract.
 *
 * A DDMA promise contains all the inक्रमmation required to program the
 * Dedicated part of the DMA Engine and get data copied. A non-executed
 * promise will live in the demands list on a contract. Once it has been
 * completed, it will be moved to the completed demands list क्रम later मुक्तing.
 * All linked promises will be मुक्तd when the corresponding contract is मुक्तd
 */
अटल काष्ठा sun4i_dma_promise *
generate_ddma_promise(काष्ठा dma_chan *chan, dma_addr_t src, dma_addr_t dest,
		      माप_प्रकार len, काष्ठा dma_slave_config *sconfig)
अणु
	काष्ठा sun4i_dma_promise *promise;
	पूर्णांक ret;

	promise = kzalloc(माप(*promise), GFP_NOWAIT);
	अगर (!promise)
		वापस शून्य;

	promise->src = src;
	promise->dst = dest;
	promise->len = len;
	promise->cfg = SUN4I_DMA_CFG_LOADING |
		SUN4I_DDMA_CFG_BYTE_COUNT_MODE_REMAIN;

	/* Source burst */
	ret = convert_burst(sconfig->src_maxburst);
	अगर (ret < 0)
		जाओ fail;
	promise->cfg |= SUN4I_DMA_CFG_SRC_BURST_LENGTH(ret);

	/* Destination burst */
	ret = convert_burst(sconfig->dst_maxburst);
	अगर (ret < 0)
		जाओ fail;
	promise->cfg |= SUN4I_DMA_CFG_DST_BURST_LENGTH(ret);

	/* Source bus width */
	ret = convert_buswidth(sconfig->src_addr_width);
	अगर (ret < 0)
		जाओ fail;
	promise->cfg |= SUN4I_DMA_CFG_SRC_DATA_WIDTH(ret);

	/* Destination bus width */
	ret = convert_buswidth(sconfig->dst_addr_width);
	अगर (ret < 0)
		जाओ fail;
	promise->cfg |= SUN4I_DMA_CFG_DST_DATA_WIDTH(ret);

	वापस promise;

fail:
	kमुक्त(promise);
	वापस शून्य;
पूर्ण

/*
 * Generate a contract
 *
 * Contracts function as DMA descriptors. As our hardware करोes not support
 * linked lists, we need to implement SG via software. We use a contract
 * to hold all the pieces of the request and process them serially one
 * after another. Each piece is represented as a promise.
 */
अटल काष्ठा sun4i_dma_contract *generate_dma_contract(व्योम)
अणु
	काष्ठा sun4i_dma_contract *contract;

	contract = kzalloc(माप(*contract), GFP_NOWAIT);
	अगर (!contract)
		वापस शून्य;

	INIT_LIST_HEAD(&contract->demands);
	INIT_LIST_HEAD(&contract->completed_demands);

	वापस contract;
पूर्ण

/*
 * Get next promise on a cyclic transfer
 *
 * Cyclic contracts contain a series of promises which are executed on a
 * loop. This function वापसs the next promise from a cyclic contract,
 * so it can be programmed पूर्णांकo the hardware.
 */
अटल काष्ठा sun4i_dma_promise *
get_next_cyclic_promise(काष्ठा sun4i_dma_contract *contract)
अणु
	काष्ठा sun4i_dma_promise *promise;

	promise = list_first_entry_or_null(&contract->demands,
					   काष्ठा sun4i_dma_promise, list);
	अगर (!promise) अणु
		list_splice_init(&contract->completed_demands,
				 &contract->demands);
		promise = list_first_entry(&contract->demands,
					   काष्ठा sun4i_dma_promise, list);
	पूर्ण

	वापस promise;
पूर्ण

/*
 * Free a contract and all its associated promises
 */
अटल व्योम sun4i_dma_मुक्त_contract(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा sun4i_dma_contract *contract = to_sun4i_dma_contract(vd);
	काष्ठा sun4i_dma_promise *promise, *पंचांगp;

	/* Free all the demands and completed demands */
	list_क्रम_each_entry_safe(promise, पंचांगp, &contract->demands, list)
		kमुक्त(promise);

	list_क्रम_each_entry_safe(promise, पंचांगp, &contract->completed_demands, list)
		kमुक्त(promise);

	kमुक्त(contract);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
sun4i_dma_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dest,
			  dma_addr_t src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	काष्ठा dma_slave_config *sconfig = &vchan->cfg;
	काष्ठा sun4i_dma_promise *promise;
	काष्ठा sun4i_dma_contract *contract;

	contract = generate_dma_contract();
	अगर (!contract)
		वापस शून्य;

	/*
	 * We can only करो the copy to bus aligned addresses, so
	 * choose the best one so we get decent perक्रमmance. We also
	 * maximize the burst size क्रम this same reason.
	 */
	sconfig->src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	sconfig->dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	sconfig->src_maxburst = 8;
	sconfig->dst_maxburst = 8;

	अगर (vchan->is_dedicated)
		promise = generate_ddma_promise(chan, src, dest, len, sconfig);
	अन्यथा
		promise = generate_ndma_promise(chan, src, dest, len, sconfig,
						DMA_MEM_TO_MEM);

	अगर (!promise) अणु
		kमुक्त(contract);
		वापस शून्य;
	पूर्ण

	/* Configure स_नकल mode */
	अगर (vchan->is_dedicated) अणु
		promise->cfg |= SUN4I_DMA_CFG_SRC_DRQ_TYPE(SUN4I_DDMA_DRQ_TYPE_SDRAM) |
				SUN4I_DMA_CFG_DST_DRQ_TYPE(SUN4I_DDMA_DRQ_TYPE_SDRAM);
	पूर्ण अन्यथा अणु
		promise->cfg |= SUN4I_DMA_CFG_SRC_DRQ_TYPE(SUN4I_NDMA_DRQ_TYPE_SDRAM) |
				SUN4I_DMA_CFG_DST_DRQ_TYPE(SUN4I_NDMA_DRQ_TYPE_SDRAM);
	पूर्ण

	/* Fill the contract with our only promise */
	list_add_tail(&promise->list, &contract->demands);

	/* And add it to the vchan */
	वापस vchan_tx_prep(&vchan->vc, &contract->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
sun4i_dma_prep_dma_cyclic(काष्ठा dma_chan *chan, dma_addr_t buf, माप_प्रकार len,
			  माप_प्रकार period_len, क्रमागत dma_transfer_direction dir,
			  अचिन्हित दीर्घ flags)
अणु
	काष्ठा sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	काष्ठा dma_slave_config *sconfig = &vchan->cfg;
	काष्ठा sun4i_dma_promise *promise;
	काष्ठा sun4i_dma_contract *contract;
	dma_addr_t src, dest;
	u32 endpoपूर्णांकs;
	पूर्णांक nr_periods, offset, plength, i;
	u8 ram_type, io_mode, linear_mode;

	अगर (!is_slave_direction(dir)) अणु
		dev_err(chan2dev(chan), "Invalid DMA direction\n");
		वापस शून्य;
	पूर्ण

	contract = generate_dma_contract();
	अगर (!contract)
		वापस शून्य;

	contract->is_cyclic = 1;

	अगर (vchan->is_dedicated) अणु
		io_mode = SUN4I_DDMA_ADDR_MODE_IO;
		linear_mode = SUN4I_DDMA_ADDR_MODE_LINEAR;
		ram_type = SUN4I_DDMA_DRQ_TYPE_SDRAM;
	पूर्ण अन्यथा अणु
		io_mode = SUN4I_NDMA_ADDR_MODE_IO;
		linear_mode = SUN4I_NDMA_ADDR_MODE_LINEAR;
		ram_type = SUN4I_NDMA_DRQ_TYPE_SDRAM;
	पूर्ण

	अगर (dir == DMA_MEM_TO_DEV) अणु
		src = buf;
		dest = sconfig->dst_addr;
		endpoपूर्णांकs = SUN4I_DMA_CFG_DST_DRQ_TYPE(vchan->endpoपूर्णांक) |
			    SUN4I_DMA_CFG_DST_ADDR_MODE(io_mode) |
			    SUN4I_DMA_CFG_SRC_DRQ_TYPE(ram_type) |
			    SUN4I_DMA_CFG_SRC_ADDR_MODE(linear_mode);
	पूर्ण अन्यथा अणु
		src = sconfig->src_addr;
		dest = buf;
		endpoपूर्णांकs = SUN4I_DMA_CFG_DST_DRQ_TYPE(ram_type) |
			    SUN4I_DMA_CFG_DST_ADDR_MODE(linear_mode) |
			    SUN4I_DMA_CFG_SRC_DRQ_TYPE(vchan->endpoपूर्णांक) |
			    SUN4I_DMA_CFG_SRC_ADDR_MODE(io_mode);
	पूर्ण

	/*
	 * We will be using half करोne पूर्णांकerrupts to make two periods
	 * out of a promise, so we need to program the DMA engine less
	 * often
	 */

	/*
	 * The engine can पूर्णांकerrupt on half-transfer, so we can use
	 * this feature to program the engine half as often as अगर we
	 * didn't use it (keep in mind the hardware doesn't support
	 * linked lists).
	 *
	 * Say you have a set of periods (| marks the start/end, I क्रम
	 * पूर्णांकerrupt, P क्रम programming the engine to करो a new
	 * transfer), the easy but slow way would be to करो
	 *
	 *  |---|---|---|---| (periods / promises)
	 *  P  I,P I,P I,P  I
	 *
	 * Using half transfer पूर्णांकerrupts you can करो
	 *
	 *  |-------|-------| (promises as configured on hw)
	 *  |---|---|---|---| (periods)
	 *  P   I  I,P  I   I
	 *
	 * Which requires half the engine programming क्रम the same
	 * functionality.
	 */
	nr_periods = DIV_ROUND_UP(len / period_len, 2);
	क्रम (i = 0; i < nr_periods; i++) अणु
		/* Calculate the offset in the buffer and the length needed */
		offset = i * period_len * 2;
		plength = min((len - offset), (period_len * 2));
		अगर (dir == DMA_MEM_TO_DEV)
			src = buf + offset;
		अन्यथा
			dest = buf + offset;

		/* Make the promise */
		अगर (vchan->is_dedicated)
			promise = generate_ddma_promise(chan, src, dest,
							plength, sconfig);
		अन्यथा
			promise = generate_ndma_promise(chan, src, dest,
							plength, sconfig, dir);

		अगर (!promise) अणु
			/* TODO: should we मुक्त everything? */
			वापस शून्य;
		पूर्ण
		promise->cfg |= endpoपूर्णांकs;

		/* Then add it to the contract */
		list_add_tail(&promise->list, &contract->demands);
	पूर्ण

	/* And add it to the vchan */
	वापस vchan_tx_prep(&vchan->vc, &contract->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
sun4i_dma_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
			अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction dir,
			अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	काष्ठा dma_slave_config *sconfig = &vchan->cfg;
	काष्ठा sun4i_dma_promise *promise;
	काष्ठा sun4i_dma_contract *contract;
	u8 ram_type, io_mode, linear_mode;
	काष्ठा scatterlist *sg;
	dma_addr_t srcaddr, dstaddr;
	u32 endpoपूर्णांकs, para;
	पूर्णांक i;

	अगर (!sgl)
		वापस शून्य;

	अगर (!is_slave_direction(dir)) अणु
		dev_err(chan2dev(chan), "Invalid DMA direction\n");
		वापस शून्य;
	पूर्ण

	contract = generate_dma_contract();
	अगर (!contract)
		वापस शून्य;

	अगर (vchan->is_dedicated) अणु
		io_mode = SUN4I_DDMA_ADDR_MODE_IO;
		linear_mode = SUN4I_DDMA_ADDR_MODE_LINEAR;
		ram_type = SUN4I_DDMA_DRQ_TYPE_SDRAM;
	पूर्ण अन्यथा अणु
		io_mode = SUN4I_NDMA_ADDR_MODE_IO;
		linear_mode = SUN4I_NDMA_ADDR_MODE_LINEAR;
		ram_type = SUN4I_NDMA_DRQ_TYPE_SDRAM;
	पूर्ण

	अगर (dir == DMA_MEM_TO_DEV)
		endpoपूर्णांकs = SUN4I_DMA_CFG_DST_DRQ_TYPE(vchan->endpoपूर्णांक) |
			    SUN4I_DMA_CFG_DST_ADDR_MODE(io_mode) |
			    SUN4I_DMA_CFG_SRC_DRQ_TYPE(ram_type) |
			    SUN4I_DMA_CFG_SRC_ADDR_MODE(linear_mode);
	अन्यथा
		endpoपूर्णांकs = SUN4I_DMA_CFG_DST_DRQ_TYPE(ram_type) |
			    SUN4I_DMA_CFG_DST_ADDR_MODE(linear_mode) |
			    SUN4I_DMA_CFG_SRC_DRQ_TYPE(vchan->endpoपूर्णांक) |
			    SUN4I_DMA_CFG_SRC_ADDR_MODE(io_mode);

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		/* Figure out addresses */
		अगर (dir == DMA_MEM_TO_DEV) अणु
			srcaddr = sg_dma_address(sg);
			dstaddr = sconfig->dst_addr;
		पूर्ण अन्यथा अणु
			srcaddr = sconfig->src_addr;
			dstaddr = sg_dma_address(sg);
		पूर्ण

		/*
		 * These are the magic DMA engine timings that keep SPI going.
		 * I haven't seen any पूर्णांकerface on DMAEngine to configure
		 * timings, and so far they seem to work क्रम everything we
		 * support, so I've kept them here. I don't know अगर other
		 * devices need dअगरferent timings because, as usual, we only
		 * have the "para" bitfield meanings, but no comment on what
		 * the values should be when करोing a certain operation :|
		 */
		para = SUN4I_DDMA_MAGIC_SPI_PARAMETERS;

		/* And make a suitable promise */
		अगर (vchan->is_dedicated)
			promise = generate_ddma_promise(chan, srcaddr, dstaddr,
							sg_dma_len(sg),
							sconfig);
		अन्यथा
			promise = generate_ndma_promise(chan, srcaddr, dstaddr,
							sg_dma_len(sg),
							sconfig, dir);

		अगर (!promise)
			वापस शून्य; /* TODO: should we मुक्त everything? */

		promise->cfg |= endpoपूर्णांकs;
		promise->para = para;

		/* Then add it to the contract */
		list_add_tail(&promise->list, &contract->demands);
	पूर्ण

	/*
	 * Once we've got all the promises पढ़ोy, add the contract
	 * to the pending list on the vchan
	 */
	वापस vchan_tx_prep(&vchan->vc, &contract->vd, flags);
पूर्ण

अटल पूर्णांक sun4i_dma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा sun4i_dma_dev *priv = to_sun4i_dma_dev(chan->device);
	काष्ठा sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	काष्ठा sun4i_dma_pchan *pchan = vchan->pchan;
	LIST_HEAD(head);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vchan->vc.lock, flags);
	vchan_get_all_descriptors(&vchan->vc, &head);
	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	/*
	 * Clearing the configuration रेजिस्टर will halt the pchan. Interrupts
	 * may still trigger, so करोn't क्रमget to disable them.
	 */
	अगर (pchan) अणु
		अगर (pchan->is_dedicated)
			ग_लिखोl(0, pchan->base + SUN4I_DDMA_CFG_REG);
		अन्यथा
			ग_लिखोl(0, pchan->base + SUN4I_NDMA_CFG_REG);
		set_pchan_पूर्णांकerrupt(priv, pchan, 0, 0);
		release_pchan(priv, pchan);
	पूर्ण

	spin_lock_irqsave(&vchan->vc.lock, flags);
	/* Clear these so the vchan is usable again */
	vchan->processing = शून्य;
	vchan->pchan = शून्य;
	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	vchan_dma_desc_मुक्त_list(&vchan->vc, &head);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_dma_config(काष्ठा dma_chan *chan,
			    काष्ठा dma_slave_config *config)
अणु
	काष्ठा sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);

	स_नकल(&vchan->cfg, config, माप(*config));

	वापस 0;
पूर्ण

अटल काष्ठा dma_chan *sun4i_dma_of_xlate(काष्ठा of_phandle_args *dma_spec,
					   काष्ठा of_dma *ofdma)
अणु
	काष्ठा sun4i_dma_dev *priv = ofdma->of_dma_data;
	काष्ठा sun4i_dma_vchan *vchan;
	काष्ठा dma_chan *chan;
	u8 is_dedicated = dma_spec->args[0];
	u8 endpoपूर्णांक = dma_spec->args[1];

	/* Check अगर type is Normal or Dedicated */
	अगर (is_dedicated != 0 && is_dedicated != 1)
		वापस शून्य;

	/* Make sure the endpoपूर्णांक looks sane */
	अगर ((is_dedicated && endpoपूर्णांक >= SUN4I_DDMA_DRQ_TYPE_LIMIT) ||
	    (!is_dedicated && endpoपूर्णांक >= SUN4I_NDMA_DRQ_TYPE_LIMIT))
		वापस शून्य;

	chan = dma_get_any_slave_channel(&priv->slave);
	अगर (!chan)
		वापस शून्य;

	/* Assign the endpoपूर्णांक to the vchan */
	vchan = to_sun4i_dma_vchan(chan);
	vchan->is_dedicated = is_dedicated;
	vchan->endpoपूर्णांक = endpoपूर्णांक;

	वापस chan;
पूर्ण

अटल क्रमागत dma_status sun4i_dma_tx_status(काष्ठा dma_chan *chan,
					   dma_cookie_t cookie,
					   काष्ठा dma_tx_state *state)
अणु
	काष्ठा sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	काष्ठा sun4i_dma_pchan *pchan = vchan->pchan;
	काष्ठा sun4i_dma_contract *contract;
	काष्ठा sun4i_dma_promise *promise;
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;
	क्रमागत dma_status ret;
	माप_प्रकार bytes = 0;

	ret = dma_cookie_status(chan, cookie, state);
	अगर (!state || (ret == DMA_COMPLETE))
		वापस ret;

	spin_lock_irqsave(&vchan->vc.lock, flags);
	vd = vchan_find_desc(&vchan->vc, cookie);
	अगर (!vd)
		जाओ निकास;
	contract = to_sun4i_dma_contract(vd);

	list_क्रम_each_entry(promise, &contract->demands, list)
		bytes += promise->len;

	/*
	 * The hardware is configured to वापस the reमुख्यing byte
	 * quantity. If possible, replace the first listed element's
	 * full size with the actual reमुख्यing amount
	 */
	promise = list_first_entry_or_null(&contract->demands,
					   काष्ठा sun4i_dma_promise, list);
	अगर (promise && pchan) अणु
		bytes -= promise->len;
		अगर (pchan->is_dedicated)
			bytes += पढ़ोl(pchan->base + SUN4I_DDMA_BYTE_COUNT_REG);
		अन्यथा
			bytes += पढ़ोl(pchan->base + SUN4I_NDMA_BYTE_COUNT_REG);
	पूर्ण

निकास:

	dma_set_residue(state, bytes);
	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	वापस ret;
पूर्ण

अटल व्योम sun4i_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा sun4i_dma_dev *priv = to_sun4i_dma_dev(chan->device);
	काष्ठा sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vchan->vc.lock, flags);

	/*
	 * If there are pending transactions क्रम this vchan, push one of
	 * them पूर्णांकo the engine to get the ball rolling.
	 */
	अगर (vchan_issue_pending(&vchan->vc))
		__execute_vchan_pending(priv, vchan);

	spin_unlock_irqrestore(&vchan->vc.lock, flags);
पूर्ण

अटल irqवापस_t sun4i_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun4i_dma_dev *priv = dev_id;
	काष्ठा sun4i_dma_pchan *pchans = priv->pchans, *pchan;
	काष्ठा sun4i_dma_vchan *vchan;
	काष्ठा sun4i_dma_contract *contract;
	काष्ठा sun4i_dma_promise *promise;
	अचिन्हित दीर्घ pendirq, irqs, disableirqs;
	पूर्णांक bit, i, मुक्त_room, allow_mitigation = 1;

	pendirq = पढ़ोl_relaxed(priv->base + SUN4I_DMA_IRQ_PENDING_STATUS_REG);

handle_pending:

	disableirqs = 0;
	मुक्त_room = 0;

	क्रम_each_set_bit(bit, &pendirq, 32) अणु
		pchan = &pchans[bit >> 1];
		vchan = pchan->vchan;
		अगर (!vchan) /* a terminated channel may still पूर्णांकerrupt */
			जारी;
		contract = vchan->contract;

		/*
		 * Disable the IRQ and मुक्त the pchan अगर it's an end
		 * पूर्णांकerrupt (odd bit)
		 */
		अगर (bit & 1) अणु
			spin_lock(&vchan->vc.lock);

			/*
			 * Move the promise पूर्णांकo the completed list now that
			 * we're करोne with it
			 */
			list_del(&vchan->processing->list);
			list_add_tail(&vchan->processing->list,
				      &contract->completed_demands);

			/*
			 * Cyclic DMA transfers are special:
			 * - There's always something we can dispatch
			 * - We need to run the callback
			 * - Latency is very important, as this is used by audio
			 * We thereक्रमe just cycle through the list and dispatch
			 * whatever we have here, reusing the pchan. There's
			 * no need to run the thपढ़ो after this.
			 *
			 * For non-cyclic transfers we need to look around,
			 * so we can program some more work, or notअगरy the
			 * client that their transfers have been completed.
			 */
			अगर (contract->is_cyclic) अणु
				promise = get_next_cyclic_promise(contract);
				vchan->processing = promise;
				configure_pchan(pchan, promise);
				vchan_cyclic_callback(&contract->vd);
			पूर्ण अन्यथा अणु
				vchan->processing = शून्य;
				vchan->pchan = शून्य;

				मुक्त_room = 1;
				disableirqs |= BIT(bit);
				release_pchan(priv, pchan);
			पूर्ण

			spin_unlock(&vchan->vc.lock);
		पूर्ण अन्यथा अणु
			/* Half करोne पूर्णांकerrupt */
			अगर (contract->is_cyclic)
				vchan_cyclic_callback(&contract->vd);
			अन्यथा
				disableirqs |= BIT(bit);
		पूर्ण
	पूर्ण

	/* Disable the IRQs क्रम events we handled */
	spin_lock(&priv->lock);
	irqs = पढ़ोl_relaxed(priv->base + SUN4I_DMA_IRQ_ENABLE_REG);
	ग_लिखोl_relaxed(irqs & ~disableirqs,
		       priv->base + SUN4I_DMA_IRQ_ENABLE_REG);
	spin_unlock(&priv->lock);

	/* Writing 1 to the pending field will clear the pending पूर्णांकerrupt */
	ग_लिखोl_relaxed(pendirq, priv->base + SUN4I_DMA_IRQ_PENDING_STATUS_REG);

	/*
	 * If a pchan was मुक्तd, we may be able to schedule something अन्यथा,
	 * so have a look around
	 */
	अगर (मुक्त_room) अणु
		क्रम (i = 0; i < SUN4I_DMA_NR_MAX_VCHANS; i++) अणु
			vchan = &priv->vchans[i];
			spin_lock(&vchan->vc.lock);
			__execute_vchan_pending(priv, vchan);
			spin_unlock(&vchan->vc.lock);
		पूर्ण
	पूर्ण

	/*
	 * Handle newer पूर्णांकerrupts अगर some showed up, but only करो it once
	 * to aव्योम a too दीर्घ a loop
	 */
	अगर (allow_mitigation) अणु
		pendirq = पढ़ोl_relaxed(priv->base +
					SUN4I_DMA_IRQ_PENDING_STATUS_REG);
		अगर (pendirq) अणु
			allow_mitigation = 0;
			जाओ handle_pending;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sun4i_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_dma_dev *priv;
	काष्ठा resource *res;
	पूर्णांक i, j, ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->irq = platक्रमm_get_irq(pdev, 0);
	अगर (priv->irq < 0)
		वापस priv->irq;

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(&pdev->dev, "No clock specified\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);
	spin_lock_init(&priv->lock);

	dma_cap_zero(priv->slave.cap_mask);
	dma_cap_set(DMA_PRIVATE, priv->slave.cap_mask);
	dma_cap_set(DMA_MEMCPY, priv->slave.cap_mask);
	dma_cap_set(DMA_CYCLIC, priv->slave.cap_mask);
	dma_cap_set(DMA_SLAVE, priv->slave.cap_mask);

	INIT_LIST_HEAD(&priv->slave.channels);
	priv->slave.device_मुक्त_chan_resources	= sun4i_dma_मुक्त_chan_resources;
	priv->slave.device_tx_status		= sun4i_dma_tx_status;
	priv->slave.device_issue_pending	= sun4i_dma_issue_pending;
	priv->slave.device_prep_slave_sg	= sun4i_dma_prep_slave_sg;
	priv->slave.device_prep_dma_स_नकल	= sun4i_dma_prep_dma_स_नकल;
	priv->slave.device_prep_dma_cyclic	= sun4i_dma_prep_dma_cyclic;
	priv->slave.device_config		= sun4i_dma_config;
	priv->slave.device_terminate_all	= sun4i_dma_terminate_all;
	priv->slave.copy_align			= 2;
	priv->slave.src_addr_widths		= BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
						  BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
						  BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	priv->slave.dst_addr_widths		= BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
						  BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
						  BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	priv->slave.directions			= BIT(DMA_DEV_TO_MEM) |
						  BIT(DMA_MEM_TO_DEV);
	priv->slave.residue_granularity		= DMA_RESIDUE_GRANULARITY_BURST;

	priv->slave.dev = &pdev->dev;

	priv->pchans = devm_kसुस्मृति(&pdev->dev, SUN4I_DMA_NR_MAX_CHANNELS,
				    माप(काष्ठा sun4i_dma_pchan), GFP_KERNEL);
	priv->vchans = devm_kसुस्मृति(&pdev->dev, SUN4I_DMA_NR_MAX_VCHANS,
				    माप(काष्ठा sun4i_dma_vchan), GFP_KERNEL);
	अगर (!priv->vchans || !priv->pchans)
		वापस -ENOMEM;

	/*
	 * [0..SUN4I_NDMA_NR_MAX_CHANNELS) are normal pchans, and
	 * [SUN4I_NDMA_NR_MAX_CHANNELS..SUN4I_DMA_NR_MAX_CHANNELS) are
	 * dedicated ones
	 */
	क्रम (i = 0; i < SUN4I_NDMA_NR_MAX_CHANNELS; i++)
		priv->pchans[i].base = priv->base +
			SUN4I_NDMA_CHANNEL_REG_BASE(i);

	क्रम (j = 0; i < SUN4I_DMA_NR_MAX_CHANNELS; i++, j++) अणु
		priv->pchans[i].base = priv->base +
			SUN4I_DDMA_CHANNEL_REG_BASE(j);
		priv->pchans[i].is_dedicated = 1;
	पूर्ण

	क्रम (i = 0; i < SUN4I_DMA_NR_MAX_VCHANS; i++) अणु
		काष्ठा sun4i_dma_vchan *vchan = &priv->vchans[i];

		spin_lock_init(&vchan->vc.lock);
		vchan->vc.desc_मुक्त = sun4i_dma_मुक्त_contract;
		vchan_init(&vchan->vc, &priv->slave);
	पूर्ण

	ret = clk_prepare_enable(priv->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't enable the clock\n");
		वापस ret;
	पूर्ण

	/*
	 * Make sure the IRQs are all disabled and accounted क्रम. The bootloader
	 * likes to leave these dirty
	 */
	ग_लिखोl(0, priv->base + SUN4I_DMA_IRQ_ENABLE_REG);
	ग_लिखोl(0xFFFFFFFF, priv->base + SUN4I_DMA_IRQ_PENDING_STATUS_REG);

	ret = devm_request_irq(&pdev->dev, priv->irq, sun4i_dma_पूर्णांकerrupt,
			       0, dev_name(&pdev->dev), priv);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot request IRQ\n");
		जाओ err_clk_disable;
	पूर्ण

	ret = dma_async_device_रेजिस्टर(&priv->slave);
	अगर (ret) अणु
		dev_warn(&pdev->dev, "Failed to register DMA engine device\n");
		जाओ err_clk_disable;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node, sun4i_dma_of_xlate,
					 priv);
	अगर (ret) अणु
		dev_err(&pdev->dev, "of_dma_controller_register failed\n");
		जाओ err_dma_unरेजिस्टर;
	पूर्ण

	dev_dbg(&pdev->dev, "Successfully probed SUN4I_DMA\n");

	वापस 0;

err_dma_unरेजिस्टर:
	dma_async_device_unरेजिस्टर(&priv->slave);
err_clk_disable:
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_dma_dev *priv = platक्रमm_get_drvdata(pdev);

	/* Disable IRQ so no more work is scheduled */
	disable_irq(priv->irq);

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&priv->slave);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun4i_dma_match[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-dma" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_dma_match);

अटल काष्ठा platक्रमm_driver sun4i_dma_driver = अणु
	.probe	= sun4i_dma_probe,
	.हटाओ	= sun4i_dma_हटाओ,
	.driver	= अणु
		.name		= "sun4i-dma",
		.of_match_table	= sun4i_dma_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sun4i_dma_driver);

MODULE_DESCRIPTION("Allwinner A10 Dedicated DMA Controller Driver");
MODULE_AUTHOR("Emilio Lथकpez <emilio@elopez.com.ar>");
MODULE_LICENSE("GPL");
