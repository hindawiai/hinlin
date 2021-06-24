<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 - 2015 Linaro Ltd.
 * Copyright (c) 2013 HiSilicon Limited.
 */
#समावेश <linux/sched.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/of_dma.h>

#समावेश "virt-dma.h"

#घोषणा DRIVER_NAME		"k3-dma"
#घोषणा DMA_MAX_SIZE		0x1ffc
#घोषणा DMA_CYCLIC_MAX_PERIOD	0x1000
#घोषणा LLI_BLOCK_SIZE		(4 * PAGE_SIZE)

#घोषणा INT_STAT		0x00
#घोषणा INT_TC1			0x04
#घोषणा INT_TC2			0x08
#घोषणा INT_ERR1		0x0c
#घोषणा INT_ERR2		0x10
#घोषणा INT_TC1_MASK		0x18
#घोषणा INT_TC2_MASK		0x1c
#घोषणा INT_ERR1_MASK		0x20
#घोषणा INT_ERR2_MASK		0x24
#घोषणा INT_TC1_RAW		0x600
#घोषणा INT_TC2_RAW		0x608
#घोषणा INT_ERR1_RAW		0x610
#घोषणा INT_ERR2_RAW		0x618
#घोषणा CH_PRI			0x688
#घोषणा CH_STAT			0x690
#घोषणा CX_CUR_CNT		0x704
#घोषणा CX_LLI			0x800
#घोषणा CX_CNT1			0x80c
#घोषणा CX_CNT0			0x810
#घोषणा CX_SRC			0x814
#घोषणा CX_DST			0x818
#घोषणा CX_CFG			0x81c

#घोषणा CX_LLI_CHAIN_EN		0x2
#घोषणा CX_CFG_EN		0x1
#घोषणा CX_CFG_NODEIRQ		BIT(1)
#घोषणा CX_CFG_MEM2PER		(0x1 << 2)
#घोषणा CX_CFG_PER2MEM		(0x2 << 2)
#घोषणा CX_CFG_SRCINCR		(0x1 << 31)
#घोषणा CX_CFG_DSTINCR		(0x1 << 30)

काष्ठा k3_desc_hw अणु
	u32 lli;
	u32 reserved[3];
	u32 count;
	u32 saddr;
	u32 daddr;
	u32 config;
पूर्ण __aligned(32);

काष्ठा k3_dma_desc_sw अणु
	काष्ठा virt_dma_desc	vd;
	dma_addr_t		desc_hw_lli;
	माप_प्रकार			desc_num;
	माप_प्रकार			size;
	काष्ठा k3_desc_hw	*desc_hw;
पूर्ण;

काष्ठा k3_dma_phy;

काष्ठा k3_dma_chan अणु
	u32			ccfg;
	काष्ठा virt_dma_chan	vc;
	काष्ठा k3_dma_phy	*phy;
	काष्ठा list_head	node;
	dma_addr_t		dev_addr;
	क्रमागत dma_status		status;
	bool			cyclic;
	काष्ठा dma_slave_config	slave_config;
पूर्ण;

काष्ठा k3_dma_phy अणु
	u32			idx;
	व्योम __iomem		*base;
	काष्ठा k3_dma_chan	*vchan;
	काष्ठा k3_dma_desc_sw	*ds_run;
	काष्ठा k3_dma_desc_sw	*ds_करोne;
पूर्ण;

काष्ठा k3_dma_dev अणु
	काष्ठा dma_device	slave;
	व्योम __iomem		*base;
	काष्ठा tasklet_काष्ठा	task;
	spinlock_t		lock;
	काष्ठा list_head	chan_pending;
	काष्ठा k3_dma_phy	*phy;
	काष्ठा k3_dma_chan	*chans;
	काष्ठा clk		*clk;
	काष्ठा dma_pool		*pool;
	u32			dma_channels;
	u32			dma_requests;
	u32			dma_channel_mask;
	अचिन्हित पूर्णांक		irq;
पूर्ण;


#घोषणा K3_FLAG_NOCLK	BIT(1)

काष्ठा k3dma_soc_data अणु
	अचिन्हित दीर्घ flags;
पूर्ण;


#घोषणा to_k3_dma(dmadev) container_of(dmadev, काष्ठा k3_dma_dev, slave)

अटल पूर्णांक k3_dma_config_ग_लिखो(काष्ठा dma_chan *chan,
			       क्रमागत dma_transfer_direction dir,
			       काष्ठा dma_slave_config *cfg);

अटल काष्ठा k3_dma_chan *to_k3_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा k3_dma_chan, vc.chan);
पूर्ण

अटल व्योम k3_dma_छोड़ो_dma(काष्ठा k3_dma_phy *phy, bool on)
अणु
	u32 val = 0;

	अगर (on) अणु
		val = पढ़ोl_relaxed(phy->base + CX_CFG);
		val |= CX_CFG_EN;
		ग_लिखोl_relaxed(val, phy->base + CX_CFG);
	पूर्ण अन्यथा अणु
		val = पढ़ोl_relaxed(phy->base + CX_CFG);
		val &= ~CX_CFG_EN;
		ग_लिखोl_relaxed(val, phy->base + CX_CFG);
	पूर्ण
पूर्ण

अटल व्योम k3_dma_terminate_chan(काष्ठा k3_dma_phy *phy, काष्ठा k3_dma_dev *d)
अणु
	u32 val = 0;

	k3_dma_छोड़ो_dma(phy, false);

	val = 0x1 << phy->idx;
	ग_लिखोl_relaxed(val, d->base + INT_TC1_RAW);
	ग_लिखोl_relaxed(val, d->base + INT_TC2_RAW);
	ग_लिखोl_relaxed(val, d->base + INT_ERR1_RAW);
	ग_लिखोl_relaxed(val, d->base + INT_ERR2_RAW);
पूर्ण

अटल व्योम k3_dma_set_desc(काष्ठा k3_dma_phy *phy, काष्ठा k3_desc_hw *hw)
अणु
	ग_लिखोl_relaxed(hw->lli, phy->base + CX_LLI);
	ग_लिखोl_relaxed(hw->count, phy->base + CX_CNT0);
	ग_लिखोl_relaxed(hw->saddr, phy->base + CX_SRC);
	ग_लिखोl_relaxed(hw->daddr, phy->base + CX_DST);
	ग_लिखोl_relaxed(hw->config, phy->base + CX_CFG);
पूर्ण

अटल u32 k3_dma_get_curr_cnt(काष्ठा k3_dma_dev *d, काष्ठा k3_dma_phy *phy)
अणु
	u32 cnt = 0;

	cnt = पढ़ोl_relaxed(d->base + CX_CUR_CNT + phy->idx * 0x10);
	cnt &= 0xffff;
	वापस cnt;
पूर्ण

अटल u32 k3_dma_get_curr_lli(काष्ठा k3_dma_phy *phy)
अणु
	वापस पढ़ोl_relaxed(phy->base + CX_LLI);
पूर्ण

अटल u32 k3_dma_get_chan_stat(काष्ठा k3_dma_dev *d)
अणु
	वापस पढ़ोl_relaxed(d->base + CH_STAT);
पूर्ण

अटल व्योम k3_dma_enable_dma(काष्ठा k3_dma_dev *d, bool on)
अणु
	अगर (on) अणु
		/* set same priority */
		ग_लिखोl_relaxed(0x0, d->base + CH_PRI);

		/* unmask irq */
		ग_लिखोl_relaxed(0xffff, d->base + INT_TC1_MASK);
		ग_लिखोl_relaxed(0xffff, d->base + INT_TC2_MASK);
		ग_लिखोl_relaxed(0xffff, d->base + INT_ERR1_MASK);
		ग_लिखोl_relaxed(0xffff, d->base + INT_ERR2_MASK);
	पूर्ण अन्यथा अणु
		/* mask irq */
		ग_लिखोl_relaxed(0x0, d->base + INT_TC1_MASK);
		ग_लिखोl_relaxed(0x0, d->base + INT_TC2_MASK);
		ग_लिखोl_relaxed(0x0, d->base + INT_ERR1_MASK);
		ग_लिखोl_relaxed(0x0, d->base + INT_ERR2_MASK);
	पूर्ण
पूर्ण

अटल irqवापस_t k3_dma_पूर्णांक_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा k3_dma_dev *d = (काष्ठा k3_dma_dev *)dev_id;
	काष्ठा k3_dma_phy *p;
	काष्ठा k3_dma_chan *c;
	u32 stat = पढ़ोl_relaxed(d->base + INT_STAT);
	u32 tc1  = पढ़ोl_relaxed(d->base + INT_TC1);
	u32 tc2  = पढ़ोl_relaxed(d->base + INT_TC2);
	u32 err1 = पढ़ोl_relaxed(d->base + INT_ERR1);
	u32 err2 = पढ़ोl_relaxed(d->base + INT_ERR2);
	u32 i, irq_chan = 0;

	जबतक (stat) अणु
		i = __ffs(stat);
		stat &= ~BIT(i);
		अगर (likely(tc1 & BIT(i)) || (tc2 & BIT(i))) अणु

			p = &d->phy[i];
			c = p->vchan;
			अगर (c && (tc1 & BIT(i))) अणु
				spin_lock(&c->vc.lock);
				अगर (p->ds_run != शून्य) अणु
					vchan_cookie_complete(&p->ds_run->vd);
					p->ds_करोne = p->ds_run;
					p->ds_run = शून्य;
				पूर्ण
				spin_unlock(&c->vc.lock);
			पूर्ण
			अगर (c && (tc2 & BIT(i))) अणु
				spin_lock(&c->vc.lock);
				अगर (p->ds_run != शून्य)
					vchan_cyclic_callback(&p->ds_run->vd);
				spin_unlock(&c->vc.lock);
			पूर्ण
			irq_chan |= BIT(i);
		पूर्ण
		अगर (unlikely((err1 & BIT(i)) || (err2 & BIT(i))))
			dev_warn(d->slave.dev, "DMA ERR\n");
	पूर्ण

	ग_लिखोl_relaxed(irq_chan, d->base + INT_TC1_RAW);
	ग_लिखोl_relaxed(irq_chan, d->base + INT_TC2_RAW);
	ग_लिखोl_relaxed(err1, d->base + INT_ERR1_RAW);
	ग_लिखोl_relaxed(err2, d->base + INT_ERR2_RAW);

	अगर (irq_chan)
		tasklet_schedule(&d->task);

	अगर (irq_chan || err1 || err2)
		वापस IRQ_HANDLED;

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक k3_dma_start_txd(काष्ठा k3_dma_chan *c)
अणु
	काष्ठा k3_dma_dev *d = to_k3_dma(c->vc.chan.device);
	काष्ठा virt_dma_desc *vd = vchan_next_desc(&c->vc);

	अगर (!c->phy)
		वापस -EAGAIN;

	अगर (BIT(c->phy->idx) & k3_dma_get_chan_stat(d))
		वापस -EAGAIN;

	/* Aव्योम losing track of  ds_run अगर a transaction is in flight */
	अगर (c->phy->ds_run)
		वापस -EAGAIN;

	अगर (vd) अणु
		काष्ठा k3_dma_desc_sw *ds =
			container_of(vd, काष्ठा k3_dma_desc_sw, vd);
		/*
		 * fetch and हटाओ request from vc->desc_issued
		 * so vc->desc_issued only contains desc pending
		 */
		list_del(&ds->vd.node);

		c->phy->ds_run = ds;
		c->phy->ds_करोne = शून्य;
		/* start dma */
		k3_dma_set_desc(c->phy, &ds->desc_hw[0]);
		वापस 0;
	पूर्ण
	c->phy->ds_run = शून्य;
	c->phy->ds_करोne = शून्य;
	वापस -EAGAIN;
पूर्ण

अटल व्योम k3_dma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा k3_dma_dev *d = from_tasklet(d, t, task);
	काष्ठा k3_dma_phy *p;
	काष्ठा k3_dma_chan *c, *cn;
	अचिन्हित pch, pch_alloc = 0;

	/* check new dma request of running channel in vc->desc_issued */
	list_क्रम_each_entry_safe(c, cn, &d->slave.channels, vc.chan.device_node) अणु
		spin_lock_irq(&c->vc.lock);
		p = c->phy;
		अगर (p && p->ds_करोne) अणु
			अगर (k3_dma_start_txd(c)) अणु
				/* No current txd associated with this channel */
				dev_dbg(d->slave.dev, "pchan %u: free\n", p->idx);
				/* Mark this channel मुक्त */
				c->phy = शून्य;
				p->vchan = शून्य;
			पूर्ण
		पूर्ण
		spin_unlock_irq(&c->vc.lock);
	पूर्ण

	/* check new channel request in d->chan_pending */
	spin_lock_irq(&d->lock);
	क्रम (pch = 0; pch < d->dma_channels; pch++) अणु
		अगर (!(d->dma_channel_mask & (1 << pch)))
			जारी;

		p = &d->phy[pch];

		अगर (p->vchan == शून्य && !list_empty(&d->chan_pending)) अणु
			c = list_first_entry(&d->chan_pending,
				काष्ठा k3_dma_chan, node);
			/* हटाओ from d->chan_pending */
			list_del_init(&c->node);
			pch_alloc |= 1 << pch;
			/* Mark this channel allocated */
			p->vchan = c;
			c->phy = p;
			dev_dbg(d->slave.dev, "pchan %u: alloc vchan %p\n", pch, &c->vc);
		पूर्ण
	पूर्ण
	spin_unlock_irq(&d->lock);

	क्रम (pch = 0; pch < d->dma_channels; pch++) अणु
		अगर (!(d->dma_channel_mask & (1 << pch)))
			जारी;

		अगर (pch_alloc & (1 << pch)) अणु
			p = &d->phy[pch];
			c = p->vchan;
			अगर (c) अणु
				spin_lock_irq(&c->vc.lock);
				k3_dma_start_txd(c);
				spin_unlock_irq(&c->vc.lock);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम k3_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा k3_dma_chan *c = to_k3_chan(chan);
	काष्ठा k3_dma_dev *d = to_k3_dma(chan->device);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&d->lock, flags);
	list_del_init(&c->node);
	spin_unlock_irqrestore(&d->lock, flags);

	vchan_मुक्त_chan_resources(&c->vc);
	c->ccfg = 0;
पूर्ण

अटल क्रमागत dma_status k3_dma_tx_status(काष्ठा dma_chan *chan,
	dma_cookie_t cookie, काष्ठा dma_tx_state *state)
अणु
	काष्ठा k3_dma_chan *c = to_k3_chan(chan);
	काष्ठा k3_dma_dev *d = to_k3_dma(chan->device);
	काष्ठा k3_dma_phy *p;
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;
	क्रमागत dma_status ret;
	माप_प्रकार bytes = 0;

	ret = dma_cookie_status(&c->vc.chan, cookie, state);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	spin_lock_irqsave(&c->vc.lock, flags);
	p = c->phy;
	ret = c->status;

	/*
	 * If the cookie is on our issue queue, then the residue is
	 * its total size.
	 */
	vd = vchan_find_desc(&c->vc, cookie);
	अगर (vd && !c->cyclic) अणु
		bytes = container_of(vd, काष्ठा k3_dma_desc_sw, vd)->size;
	पूर्ण अन्यथा अगर ((!p) || (!p->ds_run)) अणु
		bytes = 0;
	पूर्ण अन्यथा अणु
		काष्ठा k3_dma_desc_sw *ds = p->ds_run;
		u32 clli = 0, index = 0;

		bytes = k3_dma_get_curr_cnt(d, p);
		clli = k3_dma_get_curr_lli(p);
		index = ((clli - ds->desc_hw_lli) /
				माप(काष्ठा k3_desc_hw)) + 1;
		क्रम (; index < ds->desc_num; index++) अणु
			bytes += ds->desc_hw[index].count;
			/* end of lli */
			अगर (!ds->desc_hw[index].lli)
				अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&c->vc.lock, flags);
	dma_set_residue(state, bytes);
	वापस ret;
पूर्ण

अटल व्योम k3_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा k3_dma_chan *c = to_k3_chan(chan);
	काष्ठा k3_dma_dev *d = to_k3_dma(chan->device);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&c->vc.lock, flags);
	/* add request to vc->desc_issued */
	अगर (vchan_issue_pending(&c->vc)) अणु
		spin_lock(&d->lock);
		अगर (!c->phy) अणु
			अगर (list_empty(&c->node)) अणु
				/* अगर new channel, add chan_pending */
				list_add_tail(&c->node, &d->chan_pending);
				/* check in tasklet */
				tasklet_schedule(&d->task);
				dev_dbg(d->slave.dev, "vchan %p: issued\n", &c->vc);
			पूर्ण
		पूर्ण
		spin_unlock(&d->lock);
	पूर्ण अन्यथा
		dev_dbg(d->slave.dev, "vchan %p: nothing to issue\n", &c->vc);
	spin_unlock_irqrestore(&c->vc.lock, flags);
पूर्ण

अटल व्योम k3_dma_fill_desc(काष्ठा k3_dma_desc_sw *ds, dma_addr_t dst,
			dma_addr_t src, माप_प्रकार len, u32 num, u32 ccfg)
अणु
	अगर (num != ds->desc_num - 1)
		ds->desc_hw[num].lli = ds->desc_hw_lli + (num + 1) *
			माप(काष्ठा k3_desc_hw);

	ds->desc_hw[num].lli |= CX_LLI_CHAIN_EN;
	ds->desc_hw[num].count = len;
	ds->desc_hw[num].saddr = src;
	ds->desc_hw[num].daddr = dst;
	ds->desc_hw[num].config = ccfg;
पूर्ण

अटल काष्ठा k3_dma_desc_sw *k3_dma_alloc_desc_resource(पूर्णांक num,
							काष्ठा dma_chan *chan)
अणु
	काष्ठा k3_dma_chan *c = to_k3_chan(chan);
	काष्ठा k3_dma_desc_sw *ds;
	काष्ठा k3_dma_dev *d = to_k3_dma(chan->device);
	पूर्णांक lli_limit = LLI_BLOCK_SIZE / माप(काष्ठा k3_desc_hw);

	अगर (num > lli_limit) अणु
		dev_dbg(chan->device->dev, "vch %p: sg num %d exceed max %d\n",
			&c->vc, num, lli_limit);
		वापस शून्य;
	पूर्ण

	ds = kzalloc(माप(*ds), GFP_NOWAIT);
	अगर (!ds)
		वापस शून्य;

	ds->desc_hw = dma_pool_zalloc(d->pool, GFP_NOWAIT, &ds->desc_hw_lli);
	अगर (!ds->desc_hw) अणु
		dev_dbg(chan->device->dev, "vch %p: dma alloc fail\n", &c->vc);
		kमुक्त(ds);
		वापस शून्य;
	पूर्ण
	ds->desc_num = num;
	वापस ds;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *k3_dma_prep_स_नकल(
	काष्ठा dma_chan *chan,	dma_addr_t dst, dma_addr_t src,
	माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा k3_dma_chan *c = to_k3_chan(chan);
	काष्ठा k3_dma_desc_sw *ds;
	माप_प्रकार copy = 0;
	पूर्णांक num = 0;

	अगर (!len)
		वापस शून्य;

	num = DIV_ROUND_UP(len, DMA_MAX_SIZE);

	ds = k3_dma_alloc_desc_resource(num, chan);
	अगर (!ds)
		वापस शून्य;

	c->cyclic = 0;
	ds->size = len;
	num = 0;

	अगर (!c->ccfg) अणु
		/* शेष is memtomem, without calling device_config */
		c->ccfg = CX_CFG_SRCINCR | CX_CFG_DSTINCR | CX_CFG_EN;
		c->ccfg |= (0xf << 20) | (0xf << 24);	/* burst = 16 */
		c->ccfg |= (0x3 << 12) | (0x3 << 16);	/* width = 64 bit */
	पूर्ण

	करो अणु
		copy = min_t(माप_प्रकार, len, DMA_MAX_SIZE);
		k3_dma_fill_desc(ds, dst, src, copy, num++, c->ccfg);

		src += copy;
		dst += copy;
		len -= copy;
	पूर्ण जबतक (len);

	ds->desc_hw[num-1].lli = 0;	/* end of link */
	वापस vchan_tx_prep(&c->vc, &ds->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *k3_dma_prep_slave_sg(
	काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sglen,
	क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा k3_dma_chan *c = to_k3_chan(chan);
	काष्ठा k3_dma_desc_sw *ds;
	माप_प्रकार len, avail, total = 0;
	काष्ठा scatterlist *sg;
	dma_addr_t addr, src = 0, dst = 0;
	पूर्णांक num = sglen, i;

	अगर (sgl == शून्य)
		वापस शून्य;

	c->cyclic = 0;

	क्रम_each_sg(sgl, sg, sglen, i) अणु
		avail = sg_dma_len(sg);
		अगर (avail > DMA_MAX_SIZE)
			num += DIV_ROUND_UP(avail, DMA_MAX_SIZE) - 1;
	पूर्ण

	ds = k3_dma_alloc_desc_resource(num, chan);
	अगर (!ds)
		वापस शून्य;
	num = 0;
	k3_dma_config_ग_लिखो(chan, dir, &c->slave_config);

	क्रम_each_sg(sgl, sg, sglen, i) अणु
		addr = sg_dma_address(sg);
		avail = sg_dma_len(sg);
		total += avail;

		करो अणु
			len = min_t(माप_प्रकार, avail, DMA_MAX_SIZE);

			अगर (dir == DMA_MEM_TO_DEV) अणु
				src = addr;
				dst = c->dev_addr;
			पूर्ण अन्यथा अगर (dir == DMA_DEV_TO_MEM) अणु
				src = c->dev_addr;
				dst = addr;
			पूर्ण

			k3_dma_fill_desc(ds, dst, src, len, num++, c->ccfg);

			addr += len;
			avail -= len;
		पूर्ण जबतक (avail);
	पूर्ण

	ds->desc_hw[num-1].lli = 0;	/* end of link */
	ds->size = total;
	वापस vchan_tx_prep(&c->vc, &ds->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
k3_dma_prep_dma_cyclic(काष्ठा dma_chan *chan, dma_addr_t buf_addr,
		       माप_प्रकार buf_len, माप_प्रकार period_len,
		       क्रमागत dma_transfer_direction dir,
		       अचिन्हित दीर्घ flags)
अणु
	काष्ठा k3_dma_chan *c = to_k3_chan(chan);
	काष्ठा k3_dma_desc_sw *ds;
	माप_प्रकार len, avail, total = 0;
	dma_addr_t addr, src = 0, dst = 0;
	पूर्णांक num = 1, since = 0;
	माप_प्रकार modulo = DMA_CYCLIC_MAX_PERIOD;
	u32 en_tc2 = 0;

	dev_dbg(chan->device->dev, "%s: buf %pad, dst %pad, buf len %zu, period_len = %zu, dir %d\n",
	       __func__, &buf_addr, &to_k3_chan(chan)->dev_addr,
	       buf_len, period_len, (पूर्णांक)dir);

	avail = buf_len;
	अगर (avail > modulo)
		num += DIV_ROUND_UP(avail, modulo) - 1;

	ds = k3_dma_alloc_desc_resource(num, chan);
	अगर (!ds)
		वापस शून्य;

	c->cyclic = 1;
	addr = buf_addr;
	avail = buf_len;
	total = avail;
	num = 0;
	k3_dma_config_ग_लिखो(chan, dir, &c->slave_config);

	अगर (period_len < modulo)
		modulo = period_len;

	करो अणु
		len = min_t(माप_प्रकार, avail, modulo);

		अगर (dir == DMA_MEM_TO_DEV) अणु
			src = addr;
			dst = c->dev_addr;
		पूर्ण अन्यथा अगर (dir == DMA_DEV_TO_MEM) अणु
			src = c->dev_addr;
			dst = addr;
		पूर्ण
		since += len;
		अगर (since >= period_len) अणु
			/* descriptor asks क्रम TC2 पूर्णांकerrupt on completion */
			en_tc2 = CX_CFG_NODEIRQ;
			since -= period_len;
		पूर्ण अन्यथा
			en_tc2 = 0;

		k3_dma_fill_desc(ds, dst, src, len, num++, c->ccfg | en_tc2);

		addr += len;
		avail -= len;
	पूर्ण जबतक (avail);

	/* "Cyclic" == end of link poपूर्णांकs back to start of link */
	ds->desc_hw[num - 1].lli |= ds->desc_hw_lli;

	ds->size = total;

	वापस vchan_tx_prep(&c->vc, &ds->vd, flags);
पूर्ण

अटल पूर्णांक k3_dma_config(काष्ठा dma_chan *chan,
			 काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा k3_dma_chan *c = to_k3_chan(chan);

	स_नकल(&c->slave_config, cfg, माप(*cfg));

	वापस 0;
पूर्ण

अटल पूर्णांक k3_dma_config_ग_लिखो(काष्ठा dma_chan *chan,
			       क्रमागत dma_transfer_direction dir,
			       काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा k3_dma_chan *c = to_k3_chan(chan);
	u32 maxburst = 0, val = 0;
	क्रमागत dma_slave_buswidth width = DMA_SLAVE_BUSWIDTH_UNDEFINED;

	अगर (dir == DMA_DEV_TO_MEM) अणु
		c->ccfg = CX_CFG_DSTINCR;
		c->dev_addr = cfg->src_addr;
		maxburst = cfg->src_maxburst;
		width = cfg->src_addr_width;
	पूर्ण अन्यथा अगर (dir == DMA_MEM_TO_DEV) अणु
		c->ccfg = CX_CFG_SRCINCR;
		c->dev_addr = cfg->dst_addr;
		maxburst = cfg->dst_maxburst;
		width = cfg->dst_addr_width;
	पूर्ण
	चयन (width) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
	हाल DMA_SLAVE_BUSWIDTH_8_BYTES:
		val =  __ffs(width);
		अवरोध;
	शेष:
		val = 3;
		अवरोध;
	पूर्ण
	c->ccfg |= (val << 12) | (val << 16);

	अगर ((maxburst == 0) || (maxburst > 16))
		val = 15;
	अन्यथा
		val = maxburst - 1;
	c->ccfg |= (val << 20) | (val << 24);
	c->ccfg |= CX_CFG_MEM2PER | CX_CFG_EN;

	/* specअगरic request line */
	c->ccfg |= c->vc.chan.chan_id << 4;

	वापस 0;
पूर्ण

अटल व्योम k3_dma_मुक्त_desc(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा k3_dma_desc_sw *ds =
		container_of(vd, काष्ठा k3_dma_desc_sw, vd);
	काष्ठा k3_dma_dev *d = to_k3_dma(vd->tx.chan->device);

	dma_pool_मुक्त(d->pool, ds->desc_hw, ds->desc_hw_lli);
	kमुक्त(ds);
पूर्ण

अटल पूर्णांक k3_dma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा k3_dma_chan *c = to_k3_chan(chan);
	काष्ठा k3_dma_dev *d = to_k3_dma(chan->device);
	काष्ठा k3_dma_phy *p = c->phy;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	dev_dbg(d->slave.dev, "vchan %p: terminate all\n", &c->vc);

	/* Prevent this channel being scheduled */
	spin_lock(&d->lock);
	list_del_init(&c->node);
	spin_unlock(&d->lock);

	/* Clear the tx descriptor lists */
	spin_lock_irqsave(&c->vc.lock, flags);
	vchan_get_all_descriptors(&c->vc, &head);
	अगर (p) अणु
		/* vchan is asचिन्हित to a pchan - stop the channel */
		k3_dma_terminate_chan(p, d);
		c->phy = शून्य;
		p->vchan = शून्य;
		अगर (p->ds_run) अणु
			vchan_terminate_vdesc(&p->ds_run->vd);
			p->ds_run = शून्य;
		पूर्ण
		p->ds_करोne = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&c->vc.lock, flags);
	vchan_dma_desc_मुक्त_list(&c->vc, &head);

	वापस 0;
पूर्ण

अटल व्योम k3_dma_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा k3_dma_chan *c = to_k3_chan(chan);

	vchan_synchronize(&c->vc);
पूर्ण

अटल पूर्णांक k3_dma_transfer_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा k3_dma_chan *c = to_k3_chan(chan);
	काष्ठा k3_dma_dev *d = to_k3_dma(chan->device);
	काष्ठा k3_dma_phy *p = c->phy;

	dev_dbg(d->slave.dev, "vchan %p: pause\n", &c->vc);
	अगर (c->status == DMA_IN_PROGRESS) अणु
		c->status = DMA_PAUSED;
		अगर (p) अणु
			k3_dma_छोड़ो_dma(p, false);
		पूर्ण अन्यथा अणु
			spin_lock(&d->lock);
			list_del_init(&c->node);
			spin_unlock(&d->lock);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक k3_dma_transfer_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा k3_dma_chan *c = to_k3_chan(chan);
	काष्ठा k3_dma_dev *d = to_k3_dma(chan->device);
	काष्ठा k3_dma_phy *p = c->phy;
	अचिन्हित दीर्घ flags;

	dev_dbg(d->slave.dev, "vchan %p: resume\n", &c->vc);
	spin_lock_irqsave(&c->vc.lock, flags);
	अगर (c->status == DMA_PAUSED) अणु
		c->status = DMA_IN_PROGRESS;
		अगर (p) अणु
			k3_dma_छोड़ो_dma(p, true);
		पूर्ण अन्यथा अगर (!list_empty(&c->vc.desc_issued)) अणु
			spin_lock(&d->lock);
			list_add_tail(&c->node, &d->chan_pending);
			spin_unlock(&d->lock);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&c->vc.lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा k3dma_soc_data k3_v1_dma_data = अणु
	.flags = 0,
पूर्ण;

अटल स्थिर काष्ठा k3dma_soc_data asp_v1_dma_data = अणु
	.flags = K3_FLAG_NOCLK,
पूर्ण;

अटल स्थिर काष्ठा of_device_id k3_pdma_dt_ids[] = अणु
	अणु .compatible = "hisilicon,k3-dma-1.0",
	  .data = &k3_v1_dma_data
	पूर्ण,
	अणु .compatible = "hisilicon,hisi-pcm-asp-dma-1.0",
	  .data = &asp_v1_dma_data
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, k3_pdma_dt_ids);

अटल काष्ठा dma_chan *k3_of_dma_simple_xlate(काष्ठा of_phandle_args *dma_spec,
						काष्ठा of_dma *ofdma)
अणु
	काष्ठा k3_dma_dev *d = ofdma->of_dma_data;
	अचिन्हित पूर्णांक request = dma_spec->args[0];

	अगर (request >= d->dma_requests)
		वापस शून्य;

	वापस dma_get_slave_channel(&(d->chans[request].vc.chan));
पूर्ण

अटल पूर्णांक k3_dma_probe(काष्ठा platक्रमm_device *op)
अणु
	स्थिर काष्ठा k3dma_soc_data *soc_data;
	काष्ठा k3_dma_dev *d;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक i, ret, irq = 0;

	d = devm_kzalloc(&op->dev, माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	soc_data = device_get_match_data(&op->dev);
	अगर (!soc_data)
		वापस -EINVAL;

	d->base = devm_platक्रमm_ioremap_resource(op, 0);
	अगर (IS_ERR(d->base))
		वापस PTR_ERR(d->base);

	of_id = of_match_device(k3_pdma_dt_ids, &op->dev);
	अगर (of_id) अणु
		of_property_पढ़ो_u32((&op->dev)->of_node,
				"dma-channels", &d->dma_channels);
		of_property_पढ़ो_u32((&op->dev)->of_node,
				"dma-requests", &d->dma_requests);
		ret = of_property_पढ़ो_u32((&op->dev)->of_node,
				"dma-channel-mask", &d->dma_channel_mask);
		अगर (ret) अणु
			dev_warn(&op->dev,
				 "dma-channel-mask doesn't exist, considering all as available.\n");
			d->dma_channel_mask = (u32)~0UL;
		पूर्ण
	पूर्ण

	अगर (!(soc_data->flags & K3_FLAG_NOCLK)) अणु
		d->clk = devm_clk_get(&op->dev, शून्य);
		अगर (IS_ERR(d->clk)) अणु
			dev_err(&op->dev, "no dma clk\n");
			वापस PTR_ERR(d->clk);
		पूर्ण
	पूर्ण

	irq = platक्रमm_get_irq(op, 0);
	ret = devm_request_irq(&op->dev, irq,
			k3_dma_पूर्णांक_handler, 0, DRIVER_NAME, d);
	अगर (ret)
		वापस ret;

	d->irq = irq;

	/* A DMA memory pool क्रम LLIs, align on 32-byte boundary */
	d->pool = dmam_pool_create(DRIVER_NAME, &op->dev,
					LLI_BLOCK_SIZE, 32, 0);
	अगर (!d->pool)
		वापस -ENOMEM;

	/* init phy channel */
	d->phy = devm_kसुस्मृति(&op->dev,
		d->dma_channels, माप(काष्ठा k3_dma_phy), GFP_KERNEL);
	अगर (d->phy == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < d->dma_channels; i++) अणु
		काष्ठा k3_dma_phy *p;

		अगर (!(d->dma_channel_mask & BIT(i)))
			जारी;

		p = &d->phy[i];
		p->idx = i;
		p->base = d->base + i * 0x40;
	पूर्ण

	INIT_LIST_HEAD(&d->slave.channels);
	dma_cap_set(DMA_SLAVE, d->slave.cap_mask);
	dma_cap_set(DMA_MEMCPY, d->slave.cap_mask);
	dma_cap_set(DMA_CYCLIC, d->slave.cap_mask);
	d->slave.dev = &op->dev;
	d->slave.device_मुक्त_chan_resources = k3_dma_मुक्त_chan_resources;
	d->slave.device_tx_status = k3_dma_tx_status;
	d->slave.device_prep_dma_स_नकल = k3_dma_prep_स_नकल;
	d->slave.device_prep_slave_sg = k3_dma_prep_slave_sg;
	d->slave.device_prep_dma_cyclic = k3_dma_prep_dma_cyclic;
	d->slave.device_issue_pending = k3_dma_issue_pending;
	d->slave.device_config = k3_dma_config;
	d->slave.device_छोड़ो = k3_dma_transfer_छोड़ो;
	d->slave.device_resume = k3_dma_transfer_resume;
	d->slave.device_terminate_all = k3_dma_terminate_all;
	d->slave.device_synchronize = k3_dma_synchronize;
	d->slave.copy_align = DMAENGINE_ALIGN_8_BYTES;

	/* init भव channel */
	d->chans = devm_kसुस्मृति(&op->dev,
		d->dma_requests, माप(काष्ठा k3_dma_chan), GFP_KERNEL);
	अगर (d->chans == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < d->dma_requests; i++) अणु
		काष्ठा k3_dma_chan *c = &d->chans[i];

		c->status = DMA_IN_PROGRESS;
		INIT_LIST_HEAD(&c->node);
		c->vc.desc_मुक्त = k3_dma_मुक्त_desc;
		vchan_init(&c->vc, &d->slave);
	पूर्ण

	/* Enable घड़ी beक्रमe accessing रेजिस्टरs */
	ret = clk_prepare_enable(d->clk);
	अगर (ret < 0) अणु
		dev_err(&op->dev, "clk_prepare_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

	k3_dma_enable_dma(d, true);

	ret = dma_async_device_रेजिस्टर(&d->slave);
	अगर (ret)
		जाओ dma_async_रेजिस्टर_fail;

	ret = of_dma_controller_रेजिस्टर((&op->dev)->of_node,
					k3_of_dma_simple_xlate, d);
	अगर (ret)
		जाओ of_dma_रेजिस्टर_fail;

	spin_lock_init(&d->lock);
	INIT_LIST_HEAD(&d->chan_pending);
	tasklet_setup(&d->task, k3_dma_tasklet);
	platक्रमm_set_drvdata(op, d);
	dev_info(&op->dev, "initialized\n");

	वापस 0;

of_dma_रेजिस्टर_fail:
	dma_async_device_unरेजिस्टर(&d->slave);
dma_async_रेजिस्टर_fail:
	clk_disable_unprepare(d->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक k3_dma_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा k3_dma_chan *c, *cn;
	काष्ठा k3_dma_dev *d = platक्रमm_get_drvdata(op);

	dma_async_device_unरेजिस्टर(&d->slave);
	of_dma_controller_मुक्त((&op->dev)->of_node);

	devm_मुक्त_irq(&op->dev, d->irq, d);

	list_क्रम_each_entry_safe(c, cn, &d->slave.channels, vc.chan.device_node) अणु
		list_del(&c->vc.chan.device_node);
		tasklet_समाप्त(&c->vc.task);
	पूर्ण
	tasklet_समाप्त(&d->task);
	clk_disable_unprepare(d->clk);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक k3_dma_suspend_dev(काष्ठा device *dev)
अणु
	काष्ठा k3_dma_dev *d = dev_get_drvdata(dev);
	u32 stat = 0;

	stat = k3_dma_get_chan_stat(d);
	अगर (stat) अणु
		dev_warn(d->slave.dev,
			"chan %d is running fail to suspend\n", stat);
		वापस -1;
	पूर्ण
	k3_dma_enable_dma(d, false);
	clk_disable_unprepare(d->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक k3_dma_resume_dev(काष्ठा device *dev)
अणु
	काष्ठा k3_dma_dev *d = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	ret = clk_prepare_enable(d->clk);
	अगर (ret < 0) अणु
		dev_err(d->slave.dev, "clk_prepare_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण
	k3_dma_enable_dma(d, true);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(k3_dma_pmops, k3_dma_suspend_dev, k3_dma_resume_dev);

अटल काष्ठा platक्रमm_driver k3_pdma_driver = अणु
	.driver		= अणु
		.name	= DRIVER_NAME,
		.pm	= &k3_dma_pmops,
		.of_match_table = k3_pdma_dt_ids,
	पूर्ण,
	.probe		= k3_dma_probe,
	.हटाओ		= k3_dma_हटाओ,
पूर्ण;

module_platक्रमm_driver(k3_pdma_driver);

MODULE_DESCRIPTION("HiSilicon k3 DMA Driver");
MODULE_ALIAS("platform:k3dma");
MODULE_LICENSE("GPL v2");
