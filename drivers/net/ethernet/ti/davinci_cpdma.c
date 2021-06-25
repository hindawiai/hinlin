<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments CPDMA Driver
 *
 * Copyright (C) 2010 Texas Instruments
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/genभाग.स>
#समावेश "davinci_cpdma.h"

/* DMA Registers */
#घोषणा CPDMA_TXIDVER		0x00
#घोषणा CPDMA_TXCONTROL		0x04
#घोषणा CPDMA_TXTEARDOWN	0x08
#घोषणा CPDMA_RXIDVER		0x10
#घोषणा CPDMA_RXCONTROL		0x14
#घोषणा CPDMA_SOFTRESET		0x1c
#घोषणा CPDMA_RXTEARDOWN	0x18
#घोषणा CPDMA_TX_PRI0_RATE	0x30
#घोषणा CPDMA_TXINTSTATRAW	0x80
#घोषणा CPDMA_TXINTSTATMASKED	0x84
#घोषणा CPDMA_TXINTMASKSET	0x88
#घोषणा CPDMA_TXINTMASKCLEAR	0x8c
#घोषणा CPDMA_MACINVECTOR	0x90
#घोषणा CPDMA_MACEOIVECTOR	0x94
#घोषणा CPDMA_RXINTSTATRAW	0xa0
#घोषणा CPDMA_RXINTSTATMASKED	0xa4
#घोषणा CPDMA_RXINTMASKSET	0xa8
#घोषणा CPDMA_RXINTMASKCLEAR	0xac
#घोषणा CPDMA_DMAINTSTATRAW	0xb0
#घोषणा CPDMA_DMAINTSTATMASKED	0xb4
#घोषणा CPDMA_DMAINTMASKSET	0xb8
#घोषणा CPDMA_DMAINTMASKCLEAR	0xbc
#घोषणा CPDMA_DMAINT_HOSTERR	BIT(1)

/* the following exist only अगर has_ext_regs is set */
#घोषणा CPDMA_DMACONTROL	0x20
#घोषणा CPDMA_DMASTATUS		0x24
#घोषणा CPDMA_RXBUFFOFS		0x28
#घोषणा CPDMA_EM_CONTROL	0x2c

/* Descriptor mode bits */
#घोषणा CPDMA_DESC_SOP		BIT(31)
#घोषणा CPDMA_DESC_EOP		BIT(30)
#घोषणा CPDMA_DESC_OWNER	BIT(29)
#घोषणा CPDMA_DESC_EOQ		BIT(28)
#घोषणा CPDMA_DESC_TD_COMPLETE	BIT(27)
#घोषणा CPDMA_DESC_PASS_CRC	BIT(26)
#घोषणा CPDMA_DESC_TO_PORT_EN	BIT(20)
#घोषणा CPDMA_TO_PORT_SHIFT	16
#घोषणा CPDMA_DESC_PORT_MASK	(BIT(18) | BIT(17) | BIT(16))
#घोषणा CPDMA_DESC_CRC_LEN	4

#घोषणा CPDMA_TEARDOWN_VALUE	0xfffffffc

#घोषणा CPDMA_MAX_RLIM_CNT	16384

काष्ठा cpdma_desc अणु
	/* hardware fields */
	u32			hw_next;
	u32			hw_buffer;
	u32			hw_len;
	u32			hw_mode;
	/* software fields */
	व्योम			*sw_token;
	u32			sw_buffer;
	u32			sw_len;
पूर्ण;

काष्ठा cpdma_desc_pool अणु
	phys_addr_t		phys;
	dma_addr_t		hw_addr;
	व्योम __iomem		*iomap;		/* ioremap map */
	व्योम			*cpumap;	/* dma_alloc map */
	पूर्णांक			desc_size, mem_size;
	पूर्णांक			num_desc;
	काष्ठा device		*dev;
	काष्ठा gen_pool		*gen_pool;
पूर्ण;

क्रमागत cpdma_state अणु
	CPDMA_STATE_IDLE,
	CPDMA_STATE_ACTIVE,
	CPDMA_STATE_TEARDOWN,
पूर्ण;

काष्ठा cpdma_ctlr अणु
	क्रमागत cpdma_state	state;
	काष्ठा cpdma_params	params;
	काष्ठा device		*dev;
	काष्ठा cpdma_desc_pool	*pool;
	spinlock_t		lock;
	काष्ठा cpdma_chan	*channels[2 * CPDMA_MAX_CHANNELS];
	पूर्णांक chan_num;
	पूर्णांक			num_rx_desc; /* RX descriptors number */
	पूर्णांक			num_tx_desc; /* TX descriptors number */
पूर्ण;

काष्ठा cpdma_chan अणु
	काष्ठा cpdma_desc __iomem	*head, *tail;
	व्योम __iomem			*hdp, *cp, *rxमुक्त;
	क्रमागत cpdma_state		state;
	काष्ठा cpdma_ctlr		*ctlr;
	पूर्णांक				chan_num;
	spinlock_t			lock;
	पूर्णांक				count;
	u32				desc_num;
	u32				mask;
	cpdma_handler_fn		handler;
	क्रमागत dma_data_direction		dir;
	काष्ठा cpdma_chan_stats		stats;
	/* offsets पूर्णांकo dmaregs */
	पूर्णांक	पूर्णांक_set, पूर्णांक_clear, td;
	पूर्णांक				weight;
	u32				rate_factor;
	u32				rate;
पूर्ण;

काष्ठा cpdma_control_info अणु
	u32		reg;
	u32		shअगरt, mask;
	पूर्णांक		access;
#घोषणा ACCESS_RO	BIT(0)
#घोषणा ACCESS_WO	BIT(1)
#घोषणा ACCESS_RW	(ACCESS_RO | ACCESS_WO)
पूर्ण;

काष्ठा submit_info अणु
	काष्ठा cpdma_chan *chan;
	पूर्णांक directed;
	व्योम *token;
	व्योम *data_virt;
	dma_addr_t data_dma;
	पूर्णांक len;
पूर्ण;

अटल काष्ठा cpdma_control_info controls[] = अणु
	[CPDMA_TX_RLIM]		  = अणुCPDMA_DMACONTROL,	8,  0xffff, ACCESS_RWपूर्ण,
	[CPDMA_CMD_IDLE]	  = अणुCPDMA_DMACONTROL,	3,  1,      ACCESS_WOपूर्ण,
	[CPDMA_COPY_ERROR_FRAMES] = अणुCPDMA_DMACONTROL,	4,  1,      ACCESS_RWपूर्ण,
	[CPDMA_RX_OFF_LEN_UPDATE] = अणुCPDMA_DMACONTROL,	2,  1,      ACCESS_RWपूर्ण,
	[CPDMA_RX_OWNERSHIP_FLIP] = अणुCPDMA_DMACONTROL,	1,  1,      ACCESS_RWपूर्ण,
	[CPDMA_TX_PRIO_FIXED]	  = अणुCPDMA_DMACONTROL,	0,  1,      ACCESS_RWपूर्ण,
	[CPDMA_STAT_IDLE]	  = अणुCPDMA_DMASTATUS,	31, 1,      ACCESS_ROपूर्ण,
	[CPDMA_STAT_TX_ERR_CODE]  = अणुCPDMA_DMASTATUS,	20, 0xf,    ACCESS_RWपूर्ण,
	[CPDMA_STAT_TX_ERR_CHAN]  = अणुCPDMA_DMASTATUS,	16, 0x7,    ACCESS_RWपूर्ण,
	[CPDMA_STAT_RX_ERR_CODE]  = अणुCPDMA_DMASTATUS,	12, 0xf,    ACCESS_RWपूर्ण,
	[CPDMA_STAT_RX_ERR_CHAN]  = अणुCPDMA_DMASTATUS,	8,  0x7,    ACCESS_RWपूर्ण,
	[CPDMA_RX_BUFFER_OFFSET]  = अणुCPDMA_RXBUFFOFS,	0,  0xffff, ACCESS_RWपूर्ण,
पूर्ण;

#घोषणा tx_chan_num(chan)	(chan)
#घोषणा rx_chan_num(chan)	((chan) + CPDMA_MAX_CHANNELS)
#घोषणा is_rx_chan(chan)	((chan)->chan_num >= CPDMA_MAX_CHANNELS)
#घोषणा is_tx_chan(chan)	(!is_rx_chan(chan))
#घोषणा __chan_linear(chan_num)	((chan_num) & (CPDMA_MAX_CHANNELS - 1))
#घोषणा chan_linear(chan)	__chan_linear((chan)->chan_num)

/* The following make access to common cpdma_ctlr params more पढ़ोable */
#घोषणा dmaregs		params.dmaregs
#घोषणा num_chan	params.num_chan

/* various accessors */
#घोषणा dma_reg_पढ़ो(ctlr, ofs)		पढ़ोl((ctlr)->dmaregs + (ofs))
#घोषणा chan_पढ़ो(chan, fld)		पढ़ोl((chan)->fld)
#घोषणा desc_पढ़ो(desc, fld)		पढ़ोl(&(desc)->fld)
#घोषणा dma_reg_ग_लिखो(ctlr, ofs, v)	ग_लिखोl(v, (ctlr)->dmaregs + (ofs))
#घोषणा chan_ग_लिखो(chan, fld, v)	ग_लिखोl(v, (chan)->fld)
#घोषणा desc_ग_लिखो(desc, fld, v)	ग_लिखोl((u32)(v), &(desc)->fld)

#घोषणा cpdma_desc_to_port(chan, mode, directed)			\
	करो अणु								\
		अगर (!is_rx_chan(chan) && ((directed == 1) ||		\
					  (directed == 2)))		\
			mode |= (CPDMA_DESC_TO_PORT_EN |		\
				 (directed << CPDMA_TO_PORT_SHIFT));	\
	पूर्ण जबतक (0)

#घोषणा CPDMA_DMA_EXT_MAP		BIT(16)

अटल व्योम cpdma_desc_pool_destroy(काष्ठा cpdma_ctlr *ctlr)
अणु
	काष्ठा cpdma_desc_pool *pool = ctlr->pool;

	अगर (!pool)
		वापस;

	WARN(gen_pool_size(pool->gen_pool) != gen_pool_avail(pool->gen_pool),
	     "cpdma_desc_pool size %zd != avail %zd",
	     gen_pool_size(pool->gen_pool),
	     gen_pool_avail(pool->gen_pool));
	अगर (pool->cpumap)
		dma_मुक्त_coherent(ctlr->dev, pool->mem_size, pool->cpumap,
				  pool->phys);
पूर्ण

/*
 * Utility स्थिरructs क्रम a cpdma descriptor pool.  Some devices (e.g. davinci
 * emac) have dedicated on-chip memory क्रम these descriptors.  Some other
 * devices (e.g. cpsw चयनes) use plain old memory.  Descriptor pools
 * असलtract out these details
 */
अटल पूर्णांक cpdma_desc_pool_create(काष्ठा cpdma_ctlr *ctlr)
अणु
	काष्ठा cpdma_params *cpdma_params = &ctlr->params;
	काष्ठा cpdma_desc_pool *pool;
	पूर्णांक ret = -ENOMEM;

	pool = devm_kzalloc(ctlr->dev, माप(*pool), GFP_KERNEL);
	अगर (!pool)
		जाओ gen_pool_create_fail;
	ctlr->pool = pool;

	pool->mem_size	= cpdma_params->desc_mem_size;
	pool->desc_size	= ALIGN(माप(काष्ठा cpdma_desc),
				cpdma_params->desc_align);
	pool->num_desc	= pool->mem_size / pool->desc_size;

	अगर (cpdma_params->descs_pool_size) अणु
		/* recalculate memory size required cpdma descriptor pool
		 * basing on number of descriptors specअगरied by user and
		 * अगर memory size > CPPI पूर्णांकernal RAM size (desc_mem_size)
		 * then चयन to use DDR
		 */
		pool->num_desc = cpdma_params->descs_pool_size;
		pool->mem_size = pool->desc_size * pool->num_desc;
		अगर (pool->mem_size > cpdma_params->desc_mem_size)
			cpdma_params->desc_mem_phys = 0;
	पूर्ण

	pool->gen_pool = devm_gen_pool_create(ctlr->dev, ilog2(pool->desc_size),
					      -1, "cpdma");
	अगर (IS_ERR(pool->gen_pool)) अणु
		ret = PTR_ERR(pool->gen_pool);
		dev_err(ctlr->dev, "pool create failed %d\n", ret);
		जाओ gen_pool_create_fail;
	पूर्ण

	अगर (cpdma_params->desc_mem_phys) अणु
		pool->phys  = cpdma_params->desc_mem_phys;
		pool->iomap = devm_ioremap(ctlr->dev, pool->phys,
					   pool->mem_size);
		pool->hw_addr = cpdma_params->desc_hw_addr;
	पूर्ण अन्यथा अणु
		pool->cpumap = dma_alloc_coherent(ctlr->dev,  pool->mem_size,
						  &pool->hw_addr, GFP_KERNEL);
		pool->iomap = (व्योम __iomem __क्रमce *)pool->cpumap;
		pool->phys = pool->hw_addr; /* assumes no IOMMU, करोn't use this value */
	पूर्ण

	अगर (!pool->iomap)
		जाओ gen_pool_create_fail;

	ret = gen_pool_add_virt(pool->gen_pool, (अचिन्हित दीर्घ)pool->iomap,
				pool->phys, pool->mem_size, -1);
	अगर (ret < 0) अणु
		dev_err(ctlr->dev, "pool add failed %d\n", ret);
		जाओ gen_pool_add_virt_fail;
	पूर्ण

	वापस 0;

gen_pool_add_virt_fail:
	cpdma_desc_pool_destroy(ctlr);
gen_pool_create_fail:
	ctlr->pool = शून्य;
	वापस ret;
पूर्ण

अटल अंतरभूत dma_addr_t desc_phys(काष्ठा cpdma_desc_pool *pool,
		  काष्ठा cpdma_desc __iomem *desc)
अणु
	अगर (!desc)
		वापस 0;
	वापस pool->hw_addr + (__क्रमce दीर्घ)desc - (__क्रमce दीर्घ)pool->iomap;
पूर्ण

अटल अंतरभूत काष्ठा cpdma_desc __iomem *
desc_from_phys(काष्ठा cpdma_desc_pool *pool, dma_addr_t dma)
अणु
	वापस dma ? pool->iomap + dma - pool->hw_addr : शून्य;
पूर्ण

अटल काष्ठा cpdma_desc __iomem *
cpdma_desc_alloc(काष्ठा cpdma_desc_pool *pool)
अणु
	वापस (काष्ठा cpdma_desc __iomem *)
		gen_pool_alloc(pool->gen_pool, pool->desc_size);
पूर्ण

अटल व्योम cpdma_desc_मुक्त(काष्ठा cpdma_desc_pool *pool,
			    काष्ठा cpdma_desc __iomem *desc, पूर्णांक num_desc)
अणु
	gen_pool_मुक्त(pool->gen_pool, (अचिन्हित दीर्घ)desc, pool->desc_size);
पूर्ण

अटल पूर्णांक _cpdma_control_set(काष्ठा cpdma_ctlr *ctlr, पूर्णांक control, पूर्णांक value)
अणु
	काष्ठा cpdma_control_info *info = &controls[control];
	u32 val;

	अगर (!ctlr->params.has_ext_regs)
		वापस -ENOTSUPP;

	अगर (ctlr->state != CPDMA_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (control < 0 || control >= ARRAY_SIZE(controls))
		वापस -ENOENT;

	अगर ((info->access & ACCESS_WO) != ACCESS_WO)
		वापस -EPERM;

	val  = dma_reg_पढ़ो(ctlr, info->reg);
	val &= ~(info->mask << info->shअगरt);
	val |= (value & info->mask) << info->shअगरt;
	dma_reg_ग_लिखो(ctlr, info->reg, val);

	वापस 0;
पूर्ण

अटल पूर्णांक _cpdma_control_get(काष्ठा cpdma_ctlr *ctlr, पूर्णांक control)
अणु
	काष्ठा cpdma_control_info *info = &controls[control];
	पूर्णांक ret;

	अगर (!ctlr->params.has_ext_regs)
		वापस -ENOTSUPP;

	अगर (ctlr->state != CPDMA_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (control < 0 || control >= ARRAY_SIZE(controls))
		वापस -ENOENT;

	अगर ((info->access & ACCESS_RO) != ACCESS_RO)
		वापस -EPERM;

	ret = (dma_reg_पढ़ो(ctlr, info->reg) >> info->shअगरt) & info->mask;
	वापस ret;
पूर्ण

/* cpdma_chan_set_chan_shaper - set shaper क्रम a channel
 * Has to be called under ctlr lock
 */
अटल पूर्णांक cpdma_chan_set_chan_shaper(काष्ठा cpdma_chan *chan)
अणु
	काष्ठा cpdma_ctlr *ctlr = chan->ctlr;
	u32 rate_reg;
	u32 rmask;
	पूर्णांक ret;

	अगर (!chan->rate)
		वापस 0;

	rate_reg = CPDMA_TX_PRI0_RATE + 4 * chan->chan_num;
	dma_reg_ग_लिखो(ctlr, rate_reg, chan->rate_factor);

	rmask = _cpdma_control_get(ctlr, CPDMA_TX_RLIM);
	rmask |= chan->mask;

	ret = _cpdma_control_set(ctlr, CPDMA_TX_RLIM, rmask);
	वापस ret;
पूर्ण

अटल पूर्णांक cpdma_chan_on(काष्ठा cpdma_chan *chan)
अणु
	काष्ठा cpdma_ctlr *ctlr = chan->ctlr;
	काष्ठा cpdma_desc_pool	*pool = ctlr->pool;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);
	अगर (chan->state != CPDMA_STATE_IDLE) अणु
		spin_unlock_irqrestore(&chan->lock, flags);
		वापस -EBUSY;
	पूर्ण
	अगर (ctlr->state != CPDMA_STATE_ACTIVE) अणु
		spin_unlock_irqrestore(&chan->lock, flags);
		वापस -EINVAL;
	पूर्ण
	dma_reg_ग_लिखो(ctlr, chan->पूर्णांक_set, chan->mask);
	chan->state = CPDMA_STATE_ACTIVE;
	अगर (chan->head) अणु
		chan_ग_लिखो(chan, hdp, desc_phys(pool, chan->head));
		अगर (chan->rxमुक्त)
			chan_ग_लिखो(chan, rxमुक्त, chan->count);
	पूर्ण

	spin_unlock_irqrestore(&chan->lock, flags);
	वापस 0;
पूर्ण

/* cpdma_chan_fit_rate - set rate क्रम a channel and check अगर it's possible.
 * rmask - mask of rate limited channels
 * Returns min rate in Kb/s
 */
अटल पूर्णांक cpdma_chan_fit_rate(काष्ठा cpdma_chan *ch, u32 rate,
			       u32 *rmask, पूर्णांक *prio_mode)
अणु
	काष्ठा cpdma_ctlr *ctlr = ch->ctlr;
	काष्ठा cpdma_chan *chan;
	u32 old_rate = ch->rate;
	u32 new_rmask = 0;
	पूर्णांक rlim = 0;
	पूर्णांक i;

	क्रम (i = tx_chan_num(0); i < tx_chan_num(CPDMA_MAX_CHANNELS); i++) अणु
		chan = ctlr->channels[i];
		अगर (!chan)
			जारी;

		अगर (chan == ch)
			chan->rate = rate;

		अगर (chan->rate) अणु
			rlim = 1;
			new_rmask |= chan->mask;
			जारी;
		पूर्ण

		अगर (rlim)
			जाओ err;
	पूर्ण

	*rmask = new_rmask;
	*prio_mode = rlim;
	वापस 0;

err:
	ch->rate = old_rate;
	dev_err(ctlr->dev, "Upper cpdma ch%d is not rate limited\n",
		chan->chan_num);
	वापस -EINVAL;
पूर्ण

अटल u32 cpdma_chan_set_factors(काष्ठा cpdma_ctlr *ctlr,
				  काष्ठा cpdma_chan *ch)
अणु
	u32 delta = अच_पूर्णांक_उच्च, prev_delta = अच_पूर्णांक_उच्च, best_delta = अच_पूर्णांक_उच्च;
	u32 best_send_cnt = 0, best_idle_cnt = 0;
	u32 new_rate, best_rate = 0, rate_reg;
	u64 send_cnt, idle_cnt;
	u32 min_send_cnt, freq;
	u64 भागident, भागisor;

	अगर (!ch->rate) अणु
		ch->rate_factor = 0;
		जाओ set_factor;
	पूर्ण

	freq = ctlr->params.bus_freq_mhz * 1000 * 32;
	अगर (!freq) अणु
		dev_err(ctlr->dev, "The bus frequency is not set\n");
		वापस -EINVAL;
	पूर्ण

	min_send_cnt = freq - ch->rate;
	send_cnt = DIV_ROUND_UP(min_send_cnt, ch->rate);
	जबतक (send_cnt <= CPDMA_MAX_RLIM_CNT) अणु
		भागident = ch->rate * send_cnt;
		भागisor = min_send_cnt;
		idle_cnt = DIV_ROUND_CLOSEST_ULL(भागident, भागisor);

		भागident = freq * idle_cnt;
		भागisor = idle_cnt + send_cnt;
		new_rate = DIV_ROUND_CLOSEST_ULL(भागident, भागisor);

		delta = new_rate >= ch->rate ? new_rate - ch->rate : delta;
		अगर (delta < best_delta) अणु
			best_delta = delta;
			best_send_cnt = send_cnt;
			best_idle_cnt = idle_cnt;
			best_rate = new_rate;

			अगर (!delta)
				अवरोध;
		पूर्ण

		अगर (prev_delta >= delta) अणु
			prev_delta = delta;
			send_cnt++;
			जारी;
		पूर्ण

		idle_cnt++;
		भागident = freq * idle_cnt;
		send_cnt = DIV_ROUND_CLOSEST_ULL(भागident, ch->rate);
		send_cnt -= idle_cnt;
		prev_delta = अच_पूर्णांक_उच्च;
	पूर्ण

	ch->rate = best_rate;
	ch->rate_factor = best_send_cnt | (best_idle_cnt << 16);

set_factor:
	rate_reg = CPDMA_TX_PRI0_RATE + 4 * ch->chan_num;
	dma_reg_ग_लिखो(ctlr, rate_reg, ch->rate_factor);
	वापस 0;
पूर्ण

काष्ठा cpdma_ctlr *cpdma_ctlr_create(काष्ठा cpdma_params *params)
अणु
	काष्ठा cpdma_ctlr *ctlr;

	ctlr = devm_kzalloc(params->dev, माप(*ctlr), GFP_KERNEL);
	अगर (!ctlr)
		वापस शून्य;

	ctlr->state = CPDMA_STATE_IDLE;
	ctlr->params = *params;
	ctlr->dev = params->dev;
	ctlr->chan_num = 0;
	spin_lock_init(&ctlr->lock);

	अगर (cpdma_desc_pool_create(ctlr))
		वापस शून्य;
	/* split pool equally between RX/TX by शेष */
	ctlr->num_tx_desc = ctlr->pool->num_desc / 2;
	ctlr->num_rx_desc = ctlr->pool->num_desc - ctlr->num_tx_desc;

	अगर (WARN_ON(ctlr->num_chan > CPDMA_MAX_CHANNELS))
		ctlr->num_chan = CPDMA_MAX_CHANNELS;
	वापस ctlr;
पूर्ण

पूर्णांक cpdma_ctlr_start(काष्ठा cpdma_ctlr *ctlr)
अणु
	काष्ठा cpdma_chan *chan;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, prio_mode;

	spin_lock_irqsave(&ctlr->lock, flags);
	अगर (ctlr->state != CPDMA_STATE_IDLE) अणु
		spin_unlock_irqrestore(&ctlr->lock, flags);
		वापस -EBUSY;
	पूर्ण

	अगर (ctlr->params.has_soft_reset) अणु
		अचिन्हित समयout = 10 * 100;

		dma_reg_ग_लिखो(ctlr, CPDMA_SOFTRESET, 1);
		जबतक (समयout) अणु
			अगर (dma_reg_पढ़ो(ctlr, CPDMA_SOFTRESET) == 0)
				अवरोध;
			udelay(10);
			समयout--;
		पूर्ण
		WARN_ON(!समयout);
	पूर्ण

	क्रम (i = 0; i < ctlr->num_chan; i++) अणु
		ग_लिखोl(0, ctlr->params.txhdp + 4 * i);
		ग_लिखोl(0, ctlr->params.rxhdp + 4 * i);
		ग_लिखोl(0, ctlr->params.txcp + 4 * i);
		ग_लिखोl(0, ctlr->params.rxcp + 4 * i);
	पूर्ण

	dma_reg_ग_लिखो(ctlr, CPDMA_RXINTMASKCLEAR, 0xffffffff);
	dma_reg_ग_लिखो(ctlr, CPDMA_TXINTMASKCLEAR, 0xffffffff);

	dma_reg_ग_लिखो(ctlr, CPDMA_TXCONTROL, 1);
	dma_reg_ग_लिखो(ctlr, CPDMA_RXCONTROL, 1);

	ctlr->state = CPDMA_STATE_ACTIVE;

	prio_mode = 0;
	क्रम (i = 0; i < ARRAY_SIZE(ctlr->channels); i++) अणु
		chan = ctlr->channels[i];
		अगर (chan) अणु
			cpdma_chan_set_chan_shaper(chan);
			cpdma_chan_on(chan);

			/* off prio mode अगर all tx channels are rate limited */
			अगर (is_tx_chan(chan) && !chan->rate)
				prio_mode = 1;
		पूर्ण
	पूर्ण

	_cpdma_control_set(ctlr, CPDMA_TX_PRIO_FIXED, prio_mode);
	_cpdma_control_set(ctlr, CPDMA_RX_BUFFER_OFFSET, 0);

	spin_unlock_irqrestore(&ctlr->lock, flags);
	वापस 0;
पूर्ण

पूर्णांक cpdma_ctlr_stop(काष्ठा cpdma_ctlr *ctlr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&ctlr->lock, flags);
	अगर (ctlr->state != CPDMA_STATE_ACTIVE) अणु
		spin_unlock_irqrestore(&ctlr->lock, flags);
		वापस -EINVAL;
	पूर्ण

	ctlr->state = CPDMA_STATE_TEARDOWN;
	spin_unlock_irqrestore(&ctlr->lock, flags);

	क्रम (i = 0; i < ARRAY_SIZE(ctlr->channels); i++) अणु
		अगर (ctlr->channels[i])
			cpdma_chan_stop(ctlr->channels[i]);
	पूर्ण

	spin_lock_irqsave(&ctlr->lock, flags);
	dma_reg_ग_लिखो(ctlr, CPDMA_RXINTMASKCLEAR, 0xffffffff);
	dma_reg_ग_लिखो(ctlr, CPDMA_TXINTMASKCLEAR, 0xffffffff);

	dma_reg_ग_लिखो(ctlr, CPDMA_TXCONTROL, 0);
	dma_reg_ग_लिखो(ctlr, CPDMA_RXCONTROL, 0);

	ctlr->state = CPDMA_STATE_IDLE;

	spin_unlock_irqrestore(&ctlr->lock, flags);
	वापस 0;
पूर्ण

पूर्णांक cpdma_ctlr_destroy(काष्ठा cpdma_ctlr *ctlr)
अणु
	पूर्णांक ret = 0, i;

	अगर (!ctlr)
		वापस -EINVAL;

	अगर (ctlr->state != CPDMA_STATE_IDLE)
		cpdma_ctlr_stop(ctlr);

	क्रम (i = 0; i < ARRAY_SIZE(ctlr->channels); i++)
		cpdma_chan_destroy(ctlr->channels[i]);

	cpdma_desc_pool_destroy(ctlr);
	वापस ret;
पूर्ण

पूर्णांक cpdma_ctlr_पूर्णांक_ctrl(काष्ठा cpdma_ctlr *ctlr, bool enable)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&ctlr->lock, flags);
	अगर (ctlr->state != CPDMA_STATE_ACTIVE) अणु
		spin_unlock_irqrestore(&ctlr->lock, flags);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ctlr->channels); i++) अणु
		अगर (ctlr->channels[i])
			cpdma_chan_पूर्णांक_ctrl(ctlr->channels[i], enable);
	पूर्ण

	spin_unlock_irqrestore(&ctlr->lock, flags);
	वापस 0;
पूर्ण

व्योम cpdma_ctlr_eoi(काष्ठा cpdma_ctlr *ctlr, u32 value)
अणु
	dma_reg_ग_लिखो(ctlr, CPDMA_MACEOIVECTOR, value);
पूर्ण

u32 cpdma_ctrl_rxchs_state(काष्ठा cpdma_ctlr *ctlr)
अणु
	वापस dma_reg_पढ़ो(ctlr, CPDMA_RXINTSTATMASKED);
पूर्ण

u32 cpdma_ctrl_txchs_state(काष्ठा cpdma_ctlr *ctlr)
अणु
	वापस dma_reg_पढ़ो(ctlr, CPDMA_TXINTSTATMASKED);
पूर्ण

अटल व्योम cpdma_chan_set_descs(काष्ठा cpdma_ctlr *ctlr,
				 पूर्णांक rx, पूर्णांक desc_num,
				 पूर्णांक per_ch_desc)
अणु
	काष्ठा cpdma_chan *chan, *most_chan = शून्य;
	पूर्णांक desc_cnt = desc_num;
	पूर्णांक most_dnum = 0;
	पूर्णांक min, max, i;

	अगर (!desc_num)
		वापस;

	अगर (rx) अणु
		min = rx_chan_num(0);
		max = rx_chan_num(CPDMA_MAX_CHANNELS);
	पूर्ण अन्यथा अणु
		min = tx_chan_num(0);
		max = tx_chan_num(CPDMA_MAX_CHANNELS);
	पूर्ण

	क्रम (i = min; i < max; i++) अणु
		chan = ctlr->channels[i];
		अगर (!chan)
			जारी;

		अगर (chan->weight)
			chan->desc_num = (chan->weight * desc_num) / 100;
		अन्यथा
			chan->desc_num = per_ch_desc;

		desc_cnt -= chan->desc_num;

		अगर (most_dnum < chan->desc_num) अणु
			most_dnum = chan->desc_num;
			most_chan = chan;
		पूर्ण
	पूर्ण
	/* use reमुख्यs */
	अगर (most_chan)
		most_chan->desc_num += desc_cnt;
पूर्ण

/*
 * cpdma_chan_split_pool - Splits ctrl pool between all channels.
 * Has to be called under ctlr lock
 */
अटल पूर्णांक cpdma_chan_split_pool(काष्ठा cpdma_ctlr *ctlr)
अणु
	पूर्णांक tx_per_ch_desc = 0, rx_per_ch_desc = 0;
	पूर्णांक मुक्त_rx_num = 0, मुक्त_tx_num = 0;
	पूर्णांक rx_weight = 0, tx_weight = 0;
	पूर्णांक tx_desc_num, rx_desc_num;
	काष्ठा cpdma_chan *chan;
	पूर्णांक i;

	अगर (!ctlr->chan_num)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(ctlr->channels); i++) अणु
		chan = ctlr->channels[i];
		अगर (!chan)
			जारी;

		अगर (is_rx_chan(chan)) अणु
			अगर (!chan->weight)
				मुक्त_rx_num++;
			rx_weight += chan->weight;
		पूर्ण अन्यथा अणु
			अगर (!chan->weight)
				मुक्त_tx_num++;
			tx_weight += chan->weight;
		पूर्ण
	पूर्ण

	अगर (rx_weight > 100 || tx_weight > 100)
		वापस -EINVAL;

	tx_desc_num = ctlr->num_tx_desc;
	rx_desc_num = ctlr->num_rx_desc;

	अगर (मुक्त_tx_num) अणु
		tx_per_ch_desc = tx_desc_num - (tx_weight * tx_desc_num) / 100;
		tx_per_ch_desc /= मुक्त_tx_num;
	पूर्ण
	अगर (मुक्त_rx_num) अणु
		rx_per_ch_desc = rx_desc_num - (rx_weight * rx_desc_num) / 100;
		rx_per_ch_desc /= मुक्त_rx_num;
	पूर्ण

	cpdma_chan_set_descs(ctlr, 0, tx_desc_num, tx_per_ch_desc);
	cpdma_chan_set_descs(ctlr, 1, rx_desc_num, rx_per_ch_desc);

	वापस 0;
पूर्ण


/* cpdma_chan_set_weight - set weight of a channel in percentage.
 * Tx and Rx channels have separate weights. That is 100% क्रम RX
 * and 100% क्रम Tx. The weight is used to split cpdma resources
 * in correct proportion required by the channels, including number
 * of descriptors. The channel rate is not enough to know the
 * weight of a channel as the maximum rate of an पूर्णांकerface is needed.
 * If weight = 0, then channel uses rest of descriptors leaved by
 * weighted channels.
 */
पूर्णांक cpdma_chan_set_weight(काष्ठा cpdma_chan *ch, पूर्णांक weight)
अणु
	काष्ठा cpdma_ctlr *ctlr = ch->ctlr;
	अचिन्हित दीर्घ flags, ch_flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ctlr->lock, flags);
	spin_lock_irqsave(&ch->lock, ch_flags);
	अगर (ch->weight == weight) अणु
		spin_unlock_irqrestore(&ch->lock, ch_flags);
		spin_unlock_irqrestore(&ctlr->lock, flags);
		वापस 0;
	पूर्ण
	ch->weight = weight;
	spin_unlock_irqrestore(&ch->lock, ch_flags);

	/* re-split pool using new channel weight */
	ret = cpdma_chan_split_pool(ctlr);
	spin_unlock_irqrestore(&ctlr->lock, flags);
	वापस ret;
पूर्ण

/* cpdma_chan_get_min_rate - get minimum allowed rate क्रम channel
 * Should be called beक्रमe cpdma_chan_set_rate.
 * Returns min rate in Kb/s
 */
u32 cpdma_chan_get_min_rate(काष्ठा cpdma_ctlr *ctlr)
अणु
	अचिन्हित पूर्णांक भागident, भागisor;

	भागident = ctlr->params.bus_freq_mhz * 32 * 1000;
	भागisor = 1 + CPDMA_MAX_RLIM_CNT;

	वापस DIV_ROUND_UP(भागident, भागisor);
पूर्ण

/* cpdma_chan_set_rate - limits bandwidth क्रम transmit channel.
 * The bandwidth * limited channels have to be in order beginning from lowest.
 * ch - transmit channel the bandwidth is configured क्रम
 * rate - bandwidth in Kb/s, अगर 0 - then off shaper
 */
पूर्णांक cpdma_chan_set_rate(काष्ठा cpdma_chan *ch, u32 rate)
अणु
	अचिन्हित दीर्घ flags, ch_flags;
	काष्ठा cpdma_ctlr *ctlr;
	पूर्णांक ret, prio_mode;
	u32 rmask;

	अगर (!ch || !is_tx_chan(ch))
		वापस -EINVAL;

	अगर (ch->rate == rate)
		वापस rate;

	ctlr = ch->ctlr;
	spin_lock_irqsave(&ctlr->lock, flags);
	spin_lock_irqsave(&ch->lock, ch_flags);

	ret = cpdma_chan_fit_rate(ch, rate, &rmask, &prio_mode);
	अगर (ret)
		जाओ err;

	ret = cpdma_chan_set_factors(ctlr, ch);
	अगर (ret)
		जाओ err;

	spin_unlock_irqrestore(&ch->lock, ch_flags);

	/* on shapers */
	_cpdma_control_set(ctlr, CPDMA_TX_RLIM, rmask);
	_cpdma_control_set(ctlr, CPDMA_TX_PRIO_FIXED, prio_mode);
	spin_unlock_irqrestore(&ctlr->lock, flags);
	वापस ret;

err:
	spin_unlock_irqrestore(&ch->lock, ch_flags);
	spin_unlock_irqrestore(&ctlr->lock, flags);
	वापस ret;
पूर्ण

u32 cpdma_chan_get_rate(काष्ठा cpdma_chan *ch)
अणु
	अचिन्हित दीर्घ flags;
	u32 rate;

	spin_lock_irqsave(&ch->lock, flags);
	rate = ch->rate;
	spin_unlock_irqrestore(&ch->lock, flags);

	वापस rate;
पूर्ण

काष्ठा cpdma_chan *cpdma_chan_create(काष्ठा cpdma_ctlr *ctlr, पूर्णांक chan_num,
				     cpdma_handler_fn handler, पूर्णांक rx_type)
अणु
	पूर्णांक offset = chan_num * 4;
	काष्ठा cpdma_chan *chan;
	अचिन्हित दीर्घ flags;

	chan_num = rx_type ? rx_chan_num(chan_num) : tx_chan_num(chan_num);

	अगर (__chan_linear(chan_num) >= ctlr->num_chan)
		वापस ERR_PTR(-EINVAL);

	chan = devm_kzalloc(ctlr->dev, माप(*chan), GFP_KERNEL);
	अगर (!chan)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_irqsave(&ctlr->lock, flags);
	अगर (ctlr->channels[chan_num]) अणु
		spin_unlock_irqrestore(&ctlr->lock, flags);
		devm_kमुक्त(ctlr->dev, chan);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	chan->ctlr	= ctlr;
	chan->state	= CPDMA_STATE_IDLE;
	chan->chan_num	= chan_num;
	chan->handler	= handler;
	chan->rate	= 0;
	chan->weight	= 0;

	अगर (is_rx_chan(chan)) अणु
		chan->hdp	= ctlr->params.rxhdp + offset;
		chan->cp	= ctlr->params.rxcp + offset;
		chan->rxमुक्त	= ctlr->params.rxमुक्त + offset;
		chan->पूर्णांक_set	= CPDMA_RXINTMASKSET;
		chan->पूर्णांक_clear	= CPDMA_RXINTMASKCLEAR;
		chan->td	= CPDMA_RXTEARDOWN;
		chan->dir	= DMA_FROM_DEVICE;
	पूर्ण अन्यथा अणु
		chan->hdp	= ctlr->params.txhdp + offset;
		chan->cp	= ctlr->params.txcp + offset;
		chan->पूर्णांक_set	= CPDMA_TXINTMASKSET;
		chan->पूर्णांक_clear	= CPDMA_TXINTMASKCLEAR;
		chan->td	= CPDMA_TXTEARDOWN;
		chan->dir	= DMA_TO_DEVICE;
	पूर्ण
	chan->mask = BIT(chan_linear(chan));

	spin_lock_init(&chan->lock);

	ctlr->channels[chan_num] = chan;
	ctlr->chan_num++;

	cpdma_chan_split_pool(ctlr);

	spin_unlock_irqrestore(&ctlr->lock, flags);
	वापस chan;
पूर्ण

पूर्णांक cpdma_chan_get_rx_buf_num(काष्ठा cpdma_chan *chan)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक desc_num;

	spin_lock_irqsave(&chan->lock, flags);
	desc_num = chan->desc_num;
	spin_unlock_irqrestore(&chan->lock, flags);

	वापस desc_num;
पूर्ण

पूर्णांक cpdma_chan_destroy(काष्ठा cpdma_chan *chan)
अणु
	काष्ठा cpdma_ctlr *ctlr;
	अचिन्हित दीर्घ flags;

	अगर (!chan)
		वापस -EINVAL;
	ctlr = chan->ctlr;

	spin_lock_irqsave(&ctlr->lock, flags);
	अगर (chan->state != CPDMA_STATE_IDLE)
		cpdma_chan_stop(chan);
	ctlr->channels[chan->chan_num] = शून्य;
	ctlr->chan_num--;
	devm_kमुक्त(ctlr->dev, chan);
	cpdma_chan_split_pool(ctlr);

	spin_unlock_irqrestore(&ctlr->lock, flags);
	वापस 0;
पूर्ण

पूर्णांक cpdma_chan_get_stats(काष्ठा cpdma_chan *chan,
			 काष्ठा cpdma_chan_stats *stats)
अणु
	अचिन्हित दीर्घ flags;
	अगर (!chan)
		वापस -EINVAL;
	spin_lock_irqsave(&chan->lock, flags);
	स_नकल(stats, &chan->stats, माप(*stats));
	spin_unlock_irqrestore(&chan->lock, flags);
	वापस 0;
पूर्ण

अटल व्योम __cpdma_chan_submit(काष्ठा cpdma_chan *chan,
				काष्ठा cpdma_desc __iomem *desc)
अणु
	काष्ठा cpdma_ctlr		*ctlr = chan->ctlr;
	काष्ठा cpdma_desc __iomem	*prev = chan->tail;
	काष्ठा cpdma_desc_pool		*pool = ctlr->pool;
	dma_addr_t			desc_dma;
	u32				mode;

	desc_dma = desc_phys(pool, desc);

	/* simple हाल - idle channel */
	अगर (!chan->head) अणु
		chan->stats.head_enqueue++;
		chan->head = desc;
		chan->tail = desc;
		अगर (chan->state == CPDMA_STATE_ACTIVE)
			chan_ग_लिखो(chan, hdp, desc_dma);
		वापस;
	पूर्ण

	/* first chain the descriptor at the tail of the list */
	desc_ग_लिखो(prev, hw_next, desc_dma);
	chan->tail = desc;
	chan->stats.tail_enqueue++;

	/* next check अगर EOQ has been triggered alपढ़ोy */
	mode = desc_पढ़ो(prev, hw_mode);
	अगर (((mode & (CPDMA_DESC_EOQ | CPDMA_DESC_OWNER)) == CPDMA_DESC_EOQ) &&
	    (chan->state == CPDMA_STATE_ACTIVE)) अणु
		desc_ग_लिखो(prev, hw_mode, mode & ~CPDMA_DESC_EOQ);
		chan_ग_लिखो(chan, hdp, desc_dma);
		chan->stats.misqueued++;
	पूर्ण
पूर्ण

अटल पूर्णांक cpdma_chan_submit_si(काष्ठा submit_info *si)
अणु
	काष्ठा cpdma_chan		*chan = si->chan;
	काष्ठा cpdma_ctlr		*ctlr = chan->ctlr;
	पूर्णांक				len = si->len;
	काष्ठा cpdma_desc __iomem	*desc;
	dma_addr_t			buffer;
	u32				mode;
	पूर्णांक				ret;

	अगर (chan->count >= chan->desc_num)	अणु
		chan->stats.desc_alloc_fail++;
		वापस -ENOMEM;
	पूर्ण

	desc = cpdma_desc_alloc(ctlr->pool);
	अगर (!desc) अणु
		chan->stats.desc_alloc_fail++;
		वापस -ENOMEM;
	पूर्ण

	अगर (len < ctlr->params.min_packet_size) अणु
		len = ctlr->params.min_packet_size;
		chan->stats.runt_transmit_buff++;
	पूर्ण

	mode = CPDMA_DESC_OWNER | CPDMA_DESC_SOP | CPDMA_DESC_EOP;
	cpdma_desc_to_port(chan, mode, si->directed);

	अगर (si->data_dma) अणु
		buffer = si->data_dma;
		dma_sync_single_क्रम_device(ctlr->dev, buffer, len, chan->dir);
	पूर्ण अन्यथा अणु
		buffer = dma_map_single(ctlr->dev, si->data_virt, len, chan->dir);
		ret = dma_mapping_error(ctlr->dev, buffer);
		अगर (ret) अणु
			cpdma_desc_मुक्त(ctlr->pool, desc, 1);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Relaxed IO accessors can be used here as there is पढ़ो barrier
	 * at the end of ग_लिखो sequence.
	 */
	ग_लिखोl_relaxed(0, &desc->hw_next);
	ग_लिखोl_relaxed(buffer, &desc->hw_buffer);
	ग_लिखोl_relaxed(len, &desc->hw_len);
	ग_लिखोl_relaxed(mode | len, &desc->hw_mode);
	ग_लिखोl_relaxed((uपूर्णांकptr_t)si->token, &desc->sw_token);
	ग_लिखोl_relaxed(buffer, &desc->sw_buffer);
	ग_लिखोl_relaxed(si->data_dma ? len | CPDMA_DMA_EXT_MAP : len,
		       &desc->sw_len);
	desc_पढ़ो(desc, sw_len);

	__cpdma_chan_submit(chan, desc);

	अगर (chan->state == CPDMA_STATE_ACTIVE && chan->rxमुक्त)
		chan_ग_लिखो(chan, rxमुक्त, 1);

	chan->count++;
	वापस 0;
पूर्ण

पूर्णांक cpdma_chan_idle_submit(काष्ठा cpdma_chan *chan, व्योम *token, व्योम *data,
			   पूर्णांक len, पूर्णांक directed)
अणु
	काष्ठा submit_info si;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	si.chan = chan;
	si.token = token;
	si.data_virt = data;
	si.data_dma = 0;
	si.len = len;
	si.directed = directed;

	spin_lock_irqsave(&chan->lock, flags);
	अगर (chan->state == CPDMA_STATE_TEARDOWN) अणु
		spin_unlock_irqrestore(&chan->lock, flags);
		वापस -EINVAL;
	पूर्ण

	ret = cpdma_chan_submit_si(&si);
	spin_unlock_irqrestore(&chan->lock, flags);
	वापस ret;
पूर्ण

पूर्णांक cpdma_chan_idle_submit_mapped(काष्ठा cpdma_chan *chan, व्योम *token,
				  dma_addr_t data, पूर्णांक len, पूर्णांक directed)
अणु
	काष्ठा submit_info si;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	si.chan = chan;
	si.token = token;
	si.data_virt = शून्य;
	si.data_dma = data;
	si.len = len;
	si.directed = directed;

	spin_lock_irqsave(&chan->lock, flags);
	अगर (chan->state == CPDMA_STATE_TEARDOWN) अणु
		spin_unlock_irqrestore(&chan->lock, flags);
		वापस -EINVAL;
	पूर्ण

	ret = cpdma_chan_submit_si(&si);
	spin_unlock_irqrestore(&chan->lock, flags);
	वापस ret;
पूर्ण

पूर्णांक cpdma_chan_submit(काष्ठा cpdma_chan *chan, व्योम *token, व्योम *data,
		      पूर्णांक len, पूर्णांक directed)
अणु
	काष्ठा submit_info si;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	si.chan = chan;
	si.token = token;
	si.data_virt = data;
	si.data_dma = 0;
	si.len = len;
	si.directed = directed;

	spin_lock_irqsave(&chan->lock, flags);
	अगर (chan->state != CPDMA_STATE_ACTIVE) अणु
		spin_unlock_irqrestore(&chan->lock, flags);
		वापस -EINVAL;
	पूर्ण

	ret = cpdma_chan_submit_si(&si);
	spin_unlock_irqrestore(&chan->lock, flags);
	वापस ret;
पूर्ण

पूर्णांक cpdma_chan_submit_mapped(काष्ठा cpdma_chan *chan, व्योम *token,
			     dma_addr_t data, पूर्णांक len, पूर्णांक directed)
अणु
	काष्ठा submit_info si;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	si.chan = chan;
	si.token = token;
	si.data_virt = शून्य;
	si.data_dma = data;
	si.len = len;
	si.directed = directed;

	spin_lock_irqsave(&chan->lock, flags);
	अगर (chan->state != CPDMA_STATE_ACTIVE) अणु
		spin_unlock_irqrestore(&chan->lock, flags);
		वापस -EINVAL;
	पूर्ण

	ret = cpdma_chan_submit_si(&si);
	spin_unlock_irqrestore(&chan->lock, flags);
	वापस ret;
पूर्ण

bool cpdma_check_मुक्त_tx_desc(काष्ठा cpdma_chan *chan)
अणु
	काष्ठा cpdma_ctlr	*ctlr = chan->ctlr;
	काष्ठा cpdma_desc_pool	*pool = ctlr->pool;
	bool			मुक्त_tx_desc;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&chan->lock, flags);
	मुक्त_tx_desc = (chan->count < chan->desc_num) &&
			 gen_pool_avail(pool->gen_pool);
	spin_unlock_irqrestore(&chan->lock, flags);
	वापस मुक्त_tx_desc;
पूर्ण

अटल व्योम __cpdma_chan_मुक्त(काष्ठा cpdma_chan *chan,
			      काष्ठा cpdma_desc __iomem *desc,
			      पूर्णांक outlen, पूर्णांक status)
अणु
	काष्ठा cpdma_ctlr		*ctlr = chan->ctlr;
	काष्ठा cpdma_desc_pool		*pool = ctlr->pool;
	dma_addr_t			buff_dma;
	पूर्णांक				origlen;
	uपूर्णांकptr_t			token;

	token      = desc_पढ़ो(desc, sw_token);
	origlen    = desc_पढ़ो(desc, sw_len);

	buff_dma   = desc_पढ़ो(desc, sw_buffer);
	अगर (origlen & CPDMA_DMA_EXT_MAP) अणु
		origlen &= ~CPDMA_DMA_EXT_MAP;
		dma_sync_single_क्रम_cpu(ctlr->dev, buff_dma, origlen,
					chan->dir);
	पूर्ण अन्यथा अणु
		dma_unmap_single(ctlr->dev, buff_dma, origlen, chan->dir);
	पूर्ण

	cpdma_desc_मुक्त(pool, desc, 1);
	(*chan->handler)((व्योम *)token, outlen, status);
पूर्ण

अटल पूर्णांक __cpdma_chan_process(काष्ठा cpdma_chan *chan)
अणु
	काष्ठा cpdma_ctlr		*ctlr = chan->ctlr;
	काष्ठा cpdma_desc __iomem	*desc;
	पूर्णांक				status, outlen;
	पूर्णांक				cb_status = 0;
	काष्ठा cpdma_desc_pool		*pool = ctlr->pool;
	dma_addr_t			desc_dma;
	अचिन्हित दीर्घ			flags;

	spin_lock_irqsave(&chan->lock, flags);

	desc = chan->head;
	अगर (!desc) अणु
		chan->stats.empty_dequeue++;
		status = -ENOENT;
		जाओ unlock_ret;
	पूर्ण
	desc_dma = desc_phys(pool, desc);

	status	= desc_पढ़ो(desc, hw_mode);
	outlen	= status & 0x7ff;
	अगर (status & CPDMA_DESC_OWNER) अणु
		chan->stats.busy_dequeue++;
		status = -EBUSY;
		जाओ unlock_ret;
	पूर्ण

	अगर (status & CPDMA_DESC_PASS_CRC)
		outlen -= CPDMA_DESC_CRC_LEN;

	status	= status & (CPDMA_DESC_EOQ | CPDMA_DESC_TD_COMPLETE |
			    CPDMA_DESC_PORT_MASK | CPDMA_RX_VLAN_ENCAP);

	chan->head = desc_from_phys(pool, desc_पढ़ो(desc, hw_next));
	chan_ग_लिखो(chan, cp, desc_dma);
	chan->count--;
	chan->stats.good_dequeue++;

	अगर ((status & CPDMA_DESC_EOQ) && chan->head) अणु
		chan->stats.requeue++;
		chan_ग_लिखो(chan, hdp, desc_phys(pool, chan->head));
	पूर्ण

	spin_unlock_irqrestore(&chan->lock, flags);
	अगर (unlikely(status & CPDMA_DESC_TD_COMPLETE))
		cb_status = -ENOSYS;
	अन्यथा
		cb_status = status;

	__cpdma_chan_मुक्त(chan, desc, outlen, cb_status);
	वापस status;

unlock_ret:
	spin_unlock_irqrestore(&chan->lock, flags);
	वापस status;
पूर्ण

पूर्णांक cpdma_chan_process(काष्ठा cpdma_chan *chan, पूर्णांक quota)
अणु
	पूर्णांक used = 0, ret = 0;

	अगर (chan->state != CPDMA_STATE_ACTIVE)
		वापस -EINVAL;

	जबतक (used < quota) अणु
		ret = __cpdma_chan_process(chan);
		अगर (ret < 0)
			अवरोध;
		used++;
	पूर्ण
	वापस used;
पूर्ण

पूर्णांक cpdma_chan_start(काष्ठा cpdma_chan *chan)
अणु
	काष्ठा cpdma_ctlr *ctlr = chan->ctlr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ctlr->lock, flags);
	ret = cpdma_chan_set_chan_shaper(chan);
	spin_unlock_irqrestore(&ctlr->lock, flags);
	अगर (ret)
		वापस ret;

	ret = cpdma_chan_on(chan);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक cpdma_chan_stop(काष्ठा cpdma_chan *chan)
अणु
	काष्ठा cpdma_ctlr	*ctlr = chan->ctlr;
	काष्ठा cpdma_desc_pool	*pool = ctlr->pool;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			ret;
	अचिन्हित		समयout;

	spin_lock_irqsave(&chan->lock, flags);
	अगर (chan->state == CPDMA_STATE_TEARDOWN) अणु
		spin_unlock_irqrestore(&chan->lock, flags);
		वापस -EINVAL;
	पूर्ण

	chan->state = CPDMA_STATE_TEARDOWN;
	dma_reg_ग_लिखो(ctlr, chan->पूर्णांक_clear, chan->mask);

	/* trigger tearकरोwn */
	dma_reg_ग_लिखो(ctlr, chan->td, chan_linear(chan));

	/* रुको क्रम tearकरोwn complete */
	समयout = 100 * 100; /* 100 ms */
	जबतक (समयout) अणु
		u32 cp = chan_पढ़ो(chan, cp);
		अगर ((cp & CPDMA_TEARDOWN_VALUE) == CPDMA_TEARDOWN_VALUE)
			अवरोध;
		udelay(10);
		समयout--;
	पूर्ण
	WARN_ON(!समयout);
	chan_ग_लिखो(chan, cp, CPDMA_TEARDOWN_VALUE);

	/* handle completed packets */
	spin_unlock_irqrestore(&chan->lock, flags);
	करो अणु
		ret = __cpdma_chan_process(chan);
		अगर (ret < 0)
			अवरोध;
	पूर्ण जबतक ((ret & CPDMA_DESC_TD_COMPLETE) == 0);
	spin_lock_irqsave(&chan->lock, flags);

	/* reमुख्यing packets haven't been tx/rx'ed, clean them up */
	जबतक (chan->head) अणु
		काष्ठा cpdma_desc __iomem *desc = chan->head;
		dma_addr_t next_dma;

		next_dma = desc_पढ़ो(desc, hw_next);
		chan->head = desc_from_phys(pool, next_dma);
		chan->count--;
		chan->stats.tearकरोwn_dequeue++;

		/* issue callback without locks held */
		spin_unlock_irqrestore(&chan->lock, flags);
		__cpdma_chan_मुक्त(chan, desc, 0, -ENOSYS);
		spin_lock_irqsave(&chan->lock, flags);
	पूर्ण

	chan->state = CPDMA_STATE_IDLE;
	spin_unlock_irqrestore(&chan->lock, flags);
	वापस 0;
पूर्ण

पूर्णांक cpdma_chan_पूर्णांक_ctrl(काष्ठा cpdma_chan *chan, bool enable)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);
	अगर (chan->state != CPDMA_STATE_ACTIVE) अणु
		spin_unlock_irqrestore(&chan->lock, flags);
		वापस -EINVAL;
	पूर्ण

	dma_reg_ग_लिखो(chan->ctlr, enable ? chan->पूर्णांक_set : chan->पूर्णांक_clear,
		      chan->mask);
	spin_unlock_irqrestore(&chan->lock, flags);

	वापस 0;
पूर्ण

पूर्णांक cpdma_control_get(काष्ठा cpdma_ctlr *ctlr, पूर्णांक control)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ctlr->lock, flags);
	ret = _cpdma_control_get(ctlr, control);
	spin_unlock_irqrestore(&ctlr->lock, flags);

	वापस ret;
पूर्ण

पूर्णांक cpdma_control_set(काष्ठा cpdma_ctlr *ctlr, पूर्णांक control, पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ctlr->lock, flags);
	ret = _cpdma_control_set(ctlr, control, value);
	spin_unlock_irqrestore(&ctlr->lock, flags);

	वापस ret;
पूर्ण

पूर्णांक cpdma_get_num_rx_descs(काष्ठा cpdma_ctlr *ctlr)
अणु
	वापस ctlr->num_rx_desc;
पूर्ण

पूर्णांक cpdma_get_num_tx_descs(काष्ठा cpdma_ctlr *ctlr)
अणु
	वापस ctlr->num_tx_desc;
पूर्ण

पूर्णांक cpdma_set_num_rx_descs(काष्ठा cpdma_ctlr *ctlr, पूर्णांक num_rx_desc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक temp, ret;

	spin_lock_irqsave(&ctlr->lock, flags);

	temp = ctlr->num_rx_desc;
	ctlr->num_rx_desc = num_rx_desc;
	ctlr->num_tx_desc = ctlr->pool->num_desc - ctlr->num_rx_desc;
	ret = cpdma_chan_split_pool(ctlr);
	अगर (ret) अणु
		ctlr->num_rx_desc = temp;
		ctlr->num_tx_desc = ctlr->pool->num_desc - ctlr->num_rx_desc;
	पूर्ण

	spin_unlock_irqrestore(&ctlr->lock, flags);

	वापस ret;
पूर्ण
