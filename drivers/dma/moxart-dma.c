<शैली गुरु>
/*
 * MOXA ART SoCs DMA Engine support.
 *
 * Copyright (C) 2013 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/cacheflush.h>

#समावेश "dmaengine.h"
#समावेश "virt-dma.h"

#घोषणा APB_DMA_MAX_CHANNEL			4

#घोषणा REG_OFF_ADDRESS_SOURCE			0
#घोषणा REG_OFF_ADDRESS_DEST			4
#घोषणा REG_OFF_CYCLES				8
#घोषणा REG_OFF_CTRL				12
#घोषणा REG_OFF_CHAN_SIZE			16

#घोषणा APB_DMA_ENABLE				BIT(0)
#घोषणा APB_DMA_FIN_INT_STS			BIT(1)
#घोषणा APB_DMA_FIN_INT_EN			BIT(2)
#घोषणा APB_DMA_BURST_MODE			BIT(3)
#घोषणा APB_DMA_ERR_INT_STS			BIT(4)
#घोषणा APB_DMA_ERR_INT_EN			BIT(5)

/*
 * Unset: APB
 * Set:   AHB
 */
#घोषणा APB_DMA_SOURCE_SELECT			0x40
#घोषणा APB_DMA_DEST_SELECT			0x80

#घोषणा APB_DMA_SOURCE				0x100
#घोषणा APB_DMA_DEST				0x1000

#घोषणा APB_DMA_SOURCE_MASK			0x700
#घोषणा APB_DMA_DEST_MASK			0x7000

/*
 * 000: No increment
 * 001: +1 (Burst=0), +4  (Burst=1)
 * 010: +2 (Burst=0), +8  (Burst=1)
 * 011: +4 (Burst=0), +16 (Burst=1)
 * 101: -1 (Burst=0), -4  (Burst=1)
 * 110: -2 (Burst=0), -8  (Burst=1)
 * 111: -4 (Burst=0), -16 (Burst=1)
 */
#घोषणा APB_DMA_SOURCE_INC_0			0
#घोषणा APB_DMA_SOURCE_INC_1_4			0x100
#घोषणा APB_DMA_SOURCE_INC_2_8			0x200
#घोषणा APB_DMA_SOURCE_INC_4_16			0x300
#घोषणा APB_DMA_SOURCE_DEC_1_4			0x500
#घोषणा APB_DMA_SOURCE_DEC_2_8			0x600
#घोषणा APB_DMA_SOURCE_DEC_4_16			0x700
#घोषणा APB_DMA_DEST_INC_0			0
#घोषणा APB_DMA_DEST_INC_1_4			0x1000
#घोषणा APB_DMA_DEST_INC_2_8			0x2000
#घोषणा APB_DMA_DEST_INC_4_16			0x3000
#घोषणा APB_DMA_DEST_DEC_1_4			0x5000
#घोषणा APB_DMA_DEST_DEC_2_8			0x6000
#घोषणा APB_DMA_DEST_DEC_4_16			0x7000

/*
 * Request संकेत select source/destination address क्रम DMA hardware handshake.
 *
 * The request line number is a property of the DMA controller itself,
 * e.g. MMC must always request channels where dma_slave_config->slave_id is 5.
 *
 * 0:    No request / Grant संकेत
 * 1-15: Request    / Grant संकेत
 */
#घोषणा APB_DMA_SOURCE_REQ_NO			0x1000000
#घोषणा APB_DMA_SOURCE_REQ_NO_MASK		0xf000000
#घोषणा APB_DMA_DEST_REQ_NO			0x10000
#घोषणा APB_DMA_DEST_REQ_NO_MASK		0xf0000

#घोषणा APB_DMA_DATA_WIDTH			0x100000
#घोषणा APB_DMA_DATA_WIDTH_MASK			0x300000
/*
 * Data width of transfer:
 *
 * 00: Word
 * 01: Half
 * 10: Byte
 */
#घोषणा APB_DMA_DATA_WIDTH_4			0
#घोषणा APB_DMA_DATA_WIDTH_2			0x100000
#घोषणा APB_DMA_DATA_WIDTH_1			0x200000

#घोषणा APB_DMA_CYCLES_MASK			0x00ffffff

#घोषणा MOXART_DMA_DATA_TYPE_S8			0x00
#घोषणा MOXART_DMA_DATA_TYPE_S16		0x01
#घोषणा MOXART_DMA_DATA_TYPE_S32		0x02

काष्ठा moxart_sg अणु
	dma_addr_t addr;
	uपूर्णांक32_t len;
पूर्ण;

काष्ठा moxart_desc अणु
	क्रमागत dma_transfer_direction	dma_dir;
	dma_addr_t			dev_addr;
	अचिन्हित पूर्णांक			sglen;
	अचिन्हित पूर्णांक			dma_cycles;
	काष्ठा virt_dma_desc		vd;
	uपूर्णांक8_t				es;
	काष्ठा moxart_sg		sg[];
पूर्ण;

काष्ठा moxart_chan अणु
	काष्ठा virt_dma_chan		vc;

	व्योम __iomem			*base;
	काष्ठा moxart_desc		*desc;

	काष्ठा dma_slave_config		cfg;

	bool				allocated;
	bool				error;
	पूर्णांक				ch_num;
	अचिन्हित पूर्णांक			line_reqno;
	अचिन्हित पूर्णांक			sgidx;
पूर्ण;

काष्ठा moxart_dmadev अणु
	काष्ठा dma_device		dma_slave;
	काष्ठा moxart_chan		slave_chans[APB_DMA_MAX_CHANNEL];
	अचिन्हित पूर्णांक			irq;
पूर्ण;

काष्ठा moxart_filter_data अणु
	काष्ठा moxart_dmadev		*mdc;
	काष्ठा of_phandle_args		*dma_spec;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक es_bytes[] = अणु
	[MOXART_DMA_DATA_TYPE_S8] = 1,
	[MOXART_DMA_DATA_TYPE_S16] = 2,
	[MOXART_DMA_DATA_TYPE_S32] = 4,
पूर्ण;

अटल काष्ठा device *chan2dev(काष्ठा dma_chan *chan)
अणु
	वापस &chan->dev->device;
पूर्ण

अटल अंतरभूत काष्ठा moxart_chan *to_moxart_dma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा moxart_chan, vc.chan);
पूर्ण

अटल अंतरभूत काष्ठा moxart_desc *to_moxart_dma_desc(
	काष्ठा dma_async_tx_descriptor *t)
अणु
	वापस container_of(t, काष्ठा moxart_desc, vd.tx);
पूर्ण

अटल व्योम moxart_dma_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	kमुक्त(container_of(vd, काष्ठा moxart_desc, vd));
पूर्ण

अटल पूर्णांक moxart_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा moxart_chan *ch = to_moxart_dma_chan(chan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);
	u32 ctrl;

	dev_dbg(chan2dev(chan), "%s: ch=%p\n", __func__, ch);

	spin_lock_irqsave(&ch->vc.lock, flags);

	अगर (ch->desc) अणु
		moxart_dma_desc_मुक्त(&ch->desc->vd);
		ch->desc = शून्य;
	पूर्ण

	ctrl = पढ़ोl(ch->base + REG_OFF_CTRL);
	ctrl &= ~(APB_DMA_ENABLE | APB_DMA_FIN_INT_EN | APB_DMA_ERR_INT_EN);
	ग_लिखोl(ctrl, ch->base + REG_OFF_CTRL);

	vchan_get_all_descriptors(&ch->vc, &head);
	spin_unlock_irqrestore(&ch->vc.lock, flags);
	vchan_dma_desc_मुक्त_list(&ch->vc, &head);

	वापस 0;
पूर्ण

अटल पूर्णांक moxart_slave_config(काष्ठा dma_chan *chan,
			       काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा moxart_chan *ch = to_moxart_dma_chan(chan);
	u32 ctrl;

	ch->cfg = *cfg;

	ctrl = पढ़ोl(ch->base + REG_OFF_CTRL);
	ctrl |= APB_DMA_BURST_MODE;
	ctrl &= ~(APB_DMA_DEST_MASK | APB_DMA_SOURCE_MASK);
	ctrl &= ~(APB_DMA_DEST_REQ_NO_MASK | APB_DMA_SOURCE_REQ_NO_MASK);

	चयन (ch->cfg.src_addr_width) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
		ctrl |= APB_DMA_DATA_WIDTH_1;
		अगर (ch->cfg.direction != DMA_MEM_TO_DEV)
			ctrl |= APB_DMA_DEST_INC_1_4;
		अन्यथा
			ctrl |= APB_DMA_SOURCE_INC_1_4;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		ctrl |= APB_DMA_DATA_WIDTH_2;
		अगर (ch->cfg.direction != DMA_MEM_TO_DEV)
			ctrl |= APB_DMA_DEST_INC_2_8;
		अन्यथा
			ctrl |= APB_DMA_SOURCE_INC_2_8;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		ctrl &= ~APB_DMA_DATA_WIDTH;
		अगर (ch->cfg.direction != DMA_MEM_TO_DEV)
			ctrl |= APB_DMA_DEST_INC_4_16;
		अन्यथा
			ctrl |= APB_DMA_SOURCE_INC_4_16;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ch->cfg.direction == DMA_MEM_TO_DEV) अणु
		ctrl &= ~APB_DMA_DEST_SELECT;
		ctrl |= APB_DMA_SOURCE_SELECT;
		ctrl |= (ch->line_reqno << 16 &
			 APB_DMA_DEST_REQ_NO_MASK);
	पूर्ण अन्यथा अणु
		ctrl |= APB_DMA_DEST_SELECT;
		ctrl &= ~APB_DMA_SOURCE_SELECT;
		ctrl |= (ch->line_reqno << 24 &
			 APB_DMA_SOURCE_REQ_NO_MASK);
	पूर्ण

	ग_लिखोl(ctrl, ch->base + REG_OFF_CTRL);

	वापस 0;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *moxart_prep_slave_sg(
	काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
	अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction dir,
	अचिन्हित दीर्घ tx_flags, व्योम *context)
अणु
	काष्ठा moxart_chan *ch = to_moxart_dma_chan(chan);
	काष्ठा moxart_desc *d;
	क्रमागत dma_slave_buswidth dev_width;
	dma_addr_t dev_addr;
	काष्ठा scatterlist *sgent;
	अचिन्हित पूर्णांक es;
	अचिन्हित पूर्णांक i;

	अगर (!is_slave_direction(dir)) अणु
		dev_err(chan2dev(chan), "%s: invalid DMA direction\n",
			__func__);
		वापस शून्य;
	पूर्ण

	अगर (dir == DMA_DEV_TO_MEM) अणु
		dev_addr = ch->cfg.src_addr;
		dev_width = ch->cfg.src_addr_width;
	पूर्ण अन्यथा अणु
		dev_addr = ch->cfg.dst_addr;
		dev_width = ch->cfg.dst_addr_width;
	पूर्ण

	चयन (dev_width) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
		es = MOXART_DMA_DATA_TYPE_S8;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		es = MOXART_DMA_DATA_TYPE_S16;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		es = MOXART_DMA_DATA_TYPE_S32;
		अवरोध;
	शेष:
		dev_err(chan2dev(chan), "%s: unsupported data width (%u)\n",
			__func__, dev_width);
		वापस शून्य;
	पूर्ण

	d = kzalloc(काष्ठा_size(d, sg, sg_len), GFP_ATOMIC);
	अगर (!d)
		वापस शून्य;

	d->dma_dir = dir;
	d->dev_addr = dev_addr;
	d->es = es;

	क्रम_each_sg(sgl, sgent, sg_len, i) अणु
		d->sg[i].addr = sg_dma_address(sgent);
		d->sg[i].len = sg_dma_len(sgent);
	पूर्ण

	d->sglen = sg_len;

	ch->error = 0;

	वापस vchan_tx_prep(&ch->vc, &d->vd, tx_flags);
पूर्ण

अटल काष्ठा dma_chan *moxart_of_xlate(काष्ठा of_phandle_args *dma_spec,
					काष्ठा of_dma *ofdma)
अणु
	काष्ठा moxart_dmadev *mdc = ofdma->of_dma_data;
	काष्ठा dma_chan *chan;
	काष्ठा moxart_chan *ch;

	chan = dma_get_any_slave_channel(&mdc->dma_slave);
	अगर (!chan)
		वापस शून्य;

	ch = to_moxart_dma_chan(chan);
	ch->line_reqno = dma_spec->args[0];

	वापस chan;
पूर्ण

अटल पूर्णांक moxart_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा moxart_chan *ch = to_moxart_dma_chan(chan);

	dev_dbg(chan2dev(chan), "%s: allocating channel #%u\n",
		__func__, ch->ch_num);
	ch->allocated = 1;

	वापस 0;
पूर्ण

अटल व्योम moxart_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा moxart_chan *ch = to_moxart_dma_chan(chan);

	vchan_मुक्त_chan_resources(&ch->vc);

	dev_dbg(chan2dev(chan), "%s: freeing channel #%u\n",
		__func__, ch->ch_num);
	ch->allocated = 0;
पूर्ण

अटल व्योम moxart_dma_set_params(काष्ठा moxart_chan *ch, dma_addr_t src_addr,
				  dma_addr_t dst_addr)
अणु
	ग_लिखोl(src_addr, ch->base + REG_OFF_ADDRESS_SOURCE);
	ग_लिखोl(dst_addr, ch->base + REG_OFF_ADDRESS_DEST);
पूर्ण

अटल व्योम moxart_set_transfer_params(काष्ठा moxart_chan *ch, अचिन्हित पूर्णांक len)
अणु
	काष्ठा moxart_desc *d = ch->desc;
	अचिन्हित पूर्णांक sglen_भाग = es_bytes[d->es];

	d->dma_cycles = len >> sglen_भाग;

	/*
	 * There are 4 cycles on 64 bytes copied, i.e. one cycle copies 16
	 * bytes ( when width is APB_DMAB_DATA_WIDTH_4 ).
	 */
	ग_लिखोl(d->dma_cycles, ch->base + REG_OFF_CYCLES);

	dev_dbg(chan2dev(&ch->vc.chan), "%s: set %u DMA cycles (len=%u)\n",
		__func__, d->dma_cycles, len);
पूर्ण

अटल व्योम moxart_start_dma(काष्ठा moxart_chan *ch)
अणु
	u32 ctrl;

	ctrl = पढ़ोl(ch->base + REG_OFF_CTRL);
	ctrl |= (APB_DMA_ENABLE | APB_DMA_FIN_INT_EN | APB_DMA_ERR_INT_EN);
	ग_लिखोl(ctrl, ch->base + REG_OFF_CTRL);
पूर्ण

अटल व्योम moxart_dma_start_sg(काष्ठा moxart_chan *ch, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा moxart_desc *d = ch->desc;
	काष्ठा moxart_sg *sg = ch->desc->sg + idx;

	अगर (ch->desc->dma_dir == DMA_MEM_TO_DEV)
		moxart_dma_set_params(ch, sg->addr, d->dev_addr);
	अन्यथा अगर (ch->desc->dma_dir == DMA_DEV_TO_MEM)
		moxart_dma_set_params(ch, d->dev_addr, sg->addr);

	moxart_set_transfer_params(ch, sg->len);

	moxart_start_dma(ch);
पूर्ण

अटल व्योम moxart_dma_start_desc(काष्ठा dma_chan *chan)
अणु
	काष्ठा moxart_chan *ch = to_moxart_dma_chan(chan);
	काष्ठा virt_dma_desc *vd;

	vd = vchan_next_desc(&ch->vc);

	अगर (!vd) अणु
		ch->desc = शून्य;
		वापस;
	पूर्ण

	list_del(&vd->node);

	ch->desc = to_moxart_dma_desc(&vd->tx);
	ch->sgidx = 0;

	moxart_dma_start_sg(ch, 0);
पूर्ण

अटल व्योम moxart_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा moxart_chan *ch = to_moxart_dma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ch->vc.lock, flags);
	अगर (vchan_issue_pending(&ch->vc) && !ch->desc)
		moxart_dma_start_desc(chan);
	spin_unlock_irqrestore(&ch->vc.lock, flags);
पूर्ण

अटल माप_प्रकार moxart_dma_desc_size(काष्ठा moxart_desc *d,
				   अचिन्हित पूर्णांक completed_sgs)
अणु
	अचिन्हित पूर्णांक i;
	माप_प्रकार size;

	क्रम (size = i = completed_sgs; i < d->sglen; i++)
		size += d->sg[i].len;

	वापस size;
पूर्ण

अटल माप_प्रकार moxart_dma_desc_size_in_flight(काष्ठा moxart_chan *ch)
अणु
	माप_प्रकार size;
	अचिन्हित पूर्णांक completed_cycles, cycles;

	size = moxart_dma_desc_size(ch->desc, ch->sgidx);
	cycles = पढ़ोl(ch->base + REG_OFF_CYCLES);
	completed_cycles = (ch->desc->dma_cycles - cycles);
	size -= completed_cycles << es_bytes[ch->desc->es];

	dev_dbg(chan2dev(&ch->vc.chan), "%s: size=%zu\n", __func__, size);

	वापस size;
पूर्ण

अटल क्रमागत dma_status moxart_tx_status(काष्ठा dma_chan *chan,
					dma_cookie_t cookie,
					काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा moxart_chan *ch = to_moxart_dma_chan(chan);
	काष्ठा virt_dma_desc *vd;
	काष्ठा moxart_desc *d;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;

	/*
	 * dma_cookie_status() assigns initial residue value.
	 */
	ret = dma_cookie_status(chan, cookie, txstate);

	spin_lock_irqsave(&ch->vc.lock, flags);
	vd = vchan_find_desc(&ch->vc, cookie);
	अगर (vd) अणु
		d = to_moxart_dma_desc(&vd->tx);
		txstate->residue = moxart_dma_desc_size(d, 0);
	पूर्ण अन्यथा अगर (ch->desc && ch->desc->vd.tx.cookie == cookie) अणु
		txstate->residue = moxart_dma_desc_size_in_flight(ch);
	पूर्ण
	spin_unlock_irqrestore(&ch->vc.lock, flags);

	अगर (ch->error)
		वापस DMA_ERROR;

	वापस ret;
पूर्ण

अटल व्योम moxart_dma_init(काष्ठा dma_device *dma, काष्ठा device *dev)
अणु
	dma->device_prep_slave_sg		= moxart_prep_slave_sg;
	dma->device_alloc_chan_resources	= moxart_alloc_chan_resources;
	dma->device_मुक्त_chan_resources		= moxart_मुक्त_chan_resources;
	dma->device_issue_pending		= moxart_issue_pending;
	dma->device_tx_status			= moxart_tx_status;
	dma->device_config			= moxart_slave_config;
	dma->device_terminate_all		= moxart_terminate_all;
	dma->dev				= dev;

	INIT_LIST_HEAD(&dma->channels);
पूर्ण

अटल irqवापस_t moxart_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा moxart_dmadev *mc = devid;
	काष्ठा moxart_chan *ch = &mc->slave_chans[0];
	अचिन्हित पूर्णांक i;
	u32 ctrl;

	dev_dbg(chan2dev(&ch->vc.chan), "%s\n", __func__);

	क्रम (i = 0; i < APB_DMA_MAX_CHANNEL; i++, ch++) अणु
		अगर (!ch->allocated)
			जारी;

		ctrl = पढ़ोl(ch->base + REG_OFF_CTRL);

		dev_dbg(chan2dev(&ch->vc.chan), "%s: ch=%p ch->base=%p ctrl=%x\n",
			__func__, ch, ch->base, ctrl);

		अगर (ctrl & APB_DMA_FIN_INT_STS) अणु
			ctrl &= ~APB_DMA_FIN_INT_STS;
			अगर (ch->desc) अणु
				spin_lock(&ch->vc.lock);
				अगर (++ch->sgidx < ch->desc->sglen) अणु
					moxart_dma_start_sg(ch, ch->sgidx);
				पूर्ण अन्यथा अणु
					vchan_cookie_complete(&ch->desc->vd);
					moxart_dma_start_desc(&ch->vc.chan);
				पूर्ण
				spin_unlock(&ch->vc.lock);
			पूर्ण
		पूर्ण

		अगर (ctrl & APB_DMA_ERR_INT_STS) अणु
			ctrl &= ~APB_DMA_ERR_INT_STS;
			ch->error = 1;
		पूर्ण

		ग_लिखोl(ctrl, ch->base + REG_OFF_CTRL);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक moxart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा resource *res;
	व्योम __iomem *dma_base_addr;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक irq;
	काष्ठा moxart_chan *ch;
	काष्ठा moxart_dmadev *mdc;

	mdc = devm_kzalloc(dev, माप(*mdc), GFP_KERNEL);
	अगर (!mdc)
		वापस -ENOMEM;

	irq = irq_of_parse_and_map(node, 0);
	अगर (!irq) अणु
		dev_err(dev, "no IRQ resource\n");
		वापस -EINVAL;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dma_base_addr = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(dma_base_addr))
		वापस PTR_ERR(dma_base_addr);

	dma_cap_zero(mdc->dma_slave.cap_mask);
	dma_cap_set(DMA_SLAVE, mdc->dma_slave.cap_mask);
	dma_cap_set(DMA_PRIVATE, mdc->dma_slave.cap_mask);

	moxart_dma_init(&mdc->dma_slave, dev);

	ch = &mdc->slave_chans[0];
	क्रम (i = 0; i < APB_DMA_MAX_CHANNEL; i++, ch++) अणु
		ch->ch_num = i;
		ch->base = dma_base_addr + i * REG_OFF_CHAN_SIZE;
		ch->allocated = 0;

		ch->vc.desc_मुक्त = moxart_dma_desc_मुक्त;
		vchan_init(&ch->vc, &mdc->dma_slave);

		dev_dbg(dev, "%s: chs[%d]: ch->ch_num=%u ch->base=%p\n",
			__func__, i, ch->ch_num, ch->base);
	पूर्ण

	platक्रमm_set_drvdata(pdev, mdc);

	ret = devm_request_irq(dev, irq, moxart_dma_पूर्णांकerrupt, 0,
			       "moxart-dma-engine", mdc);
	अगर (ret) अणु
		dev_err(dev, "devm_request_irq failed\n");
		वापस ret;
	पूर्ण
	mdc->irq = irq;

	ret = dma_async_device_रेजिस्टर(&mdc->dma_slave);
	अगर (ret) अणु
		dev_err(dev, "dma_async_device_register failed\n");
		वापस ret;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(node, moxart_of_xlate, mdc);
	अगर (ret) अणु
		dev_err(dev, "of_dma_controller_register failed\n");
		dma_async_device_unरेजिस्टर(&mdc->dma_slave);
		वापस ret;
	पूर्ण

	dev_dbg(dev, "%s: IRQ=%u\n", __func__, irq);

	वापस 0;
पूर्ण

अटल पूर्णांक moxart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा moxart_dmadev *m = platक्रमm_get_drvdata(pdev);

	devm_मुक्त_irq(&pdev->dev, m->irq, m);

	dma_async_device_unरेजिस्टर(&m->dma_slave);

	अगर (pdev->dev.of_node)
		of_dma_controller_मुक्त(pdev->dev.of_node);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id moxart_dma_match[] = अणु
	अणु .compatible = "moxa,moxart-dma" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, moxart_dma_match);

अटल काष्ठा platक्रमm_driver moxart_driver = अणु
	.probe	= moxart_probe,
	.हटाओ	= moxart_हटाओ,
	.driver = अणु
		.name		= "moxart-dma-engine",
		.of_match_table	= moxart_dma_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक moxart_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&moxart_driver);
पूर्ण
subsys_initcall(moxart_init);

अटल व्योम __निकास moxart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&moxart_driver);
पूर्ण
module_निकास(moxart_निकास);

MODULE_AUTHOR("Jonas Jensen <jonas.jensen@gmail.com>");
MODULE_DESCRIPTION("MOXART DMA engine driver");
MODULE_LICENSE("GPL v2");
