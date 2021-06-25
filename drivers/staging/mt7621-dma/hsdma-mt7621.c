<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Copyright (C) 2015, Michael Lee <igvtee@gmail.com>
 *  MTK HSDMA support
 */

#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/reset.h>
#समावेश <linux/of_device.h>

#समावेश "virt-dma.h"

#घोषणा HSDMA_BASE_OFFSET		0x800

#घोषणा HSDMA_REG_TX_BASE		0x00
#घोषणा HSDMA_REG_TX_CNT		0x04
#घोषणा HSDMA_REG_TX_CTX		0x08
#घोषणा HSDMA_REG_TX_DTX		0x0c
#घोषणा HSDMA_REG_RX_BASE		0x100
#घोषणा HSDMA_REG_RX_CNT		0x104
#घोषणा HSDMA_REG_RX_CRX		0x108
#घोषणा HSDMA_REG_RX_DRX		0x10c
#घोषणा HSDMA_REG_INFO			0x200
#घोषणा HSDMA_REG_GLO_CFG		0x204
#घोषणा HSDMA_REG_RST_CFG		0x208
#घोषणा HSDMA_REG_DELAY_INT		0x20c
#घोषणा HSDMA_REG_FREEQ_THRES		0x210
#घोषणा HSDMA_REG_INT_STATUS		0x220
#घोषणा HSDMA_REG_INT_MASK		0x228
#घोषणा HSDMA_REG_SCH_Q01		0x280
#घोषणा HSDMA_REG_SCH_Q23		0x284

#घोषणा HSDMA_DESCS_MAX			0xfff
#घोषणा HSDMA_DESCS_NUM			8
#घोषणा HSDMA_DESCS_MASK		(HSDMA_DESCS_NUM - 1)
#घोषणा HSDMA_NEXT_DESC(x)		(((x) + 1) & HSDMA_DESCS_MASK)

/* HSDMA_REG_INFO */
#घोषणा HSDMA_INFO_INDEX_MASK		0xf
#घोषणा HSDMA_INFO_INDEX_SHIFT		24
#घोषणा HSDMA_INFO_BASE_MASK		0xff
#घोषणा HSDMA_INFO_BASE_SHIFT		16
#घोषणा HSDMA_INFO_RX_MASK		0xff
#घोषणा HSDMA_INFO_RX_SHIFT		8
#घोषणा HSDMA_INFO_TX_MASK		0xff
#घोषणा HSDMA_INFO_TX_SHIFT		0

/* HSDMA_REG_GLO_CFG */
#घोषणा HSDMA_GLO_TX_2B_OFFSET		BIT(31)
#घोषणा HSDMA_GLO_CLK_GATE		BIT(30)
#घोषणा HSDMA_GLO_BYTE_SWAP		BIT(29)
#घोषणा HSDMA_GLO_MULTI_DMA		BIT(10)
#घोषणा HSDMA_GLO_TWO_BUF		BIT(9)
#घोषणा HSDMA_GLO_32B_DESC		BIT(8)
#घोषणा HSDMA_GLO_BIG_ENDIAN		BIT(7)
#घोषणा HSDMA_GLO_TX_DONE		BIT(6)
#घोषणा HSDMA_GLO_BT_MASK		0x3
#घोषणा HSDMA_GLO_BT_SHIFT		4
#घोषणा HSDMA_GLO_RX_BUSY		BIT(3)
#घोषणा HSDMA_GLO_RX_DMA		BIT(2)
#घोषणा HSDMA_GLO_TX_BUSY		BIT(1)
#घोषणा HSDMA_GLO_TX_DMA		BIT(0)

#घोषणा HSDMA_BT_SIZE_16BYTES		(0 << HSDMA_GLO_BT_SHIFT)
#घोषणा HSDMA_BT_SIZE_32BYTES		(1 << HSDMA_GLO_BT_SHIFT)
#घोषणा HSDMA_BT_SIZE_64BYTES		(2 << HSDMA_GLO_BT_SHIFT)
#घोषणा HSDMA_BT_SIZE_128BYTES		(3 << HSDMA_GLO_BT_SHIFT)

#घोषणा HSDMA_GLO_DEFAULT		(HSDMA_GLO_MULTI_DMA | \
		HSDMA_GLO_RX_DMA | HSDMA_GLO_TX_DMA | HSDMA_BT_SIZE_32BYTES)

/* HSDMA_REG_RST_CFG */
#घोषणा HSDMA_RST_RX_SHIFT		16
#घोषणा HSDMA_RST_TX_SHIFT		0

/* HSDMA_REG_DELAY_INT */
#घोषणा HSDMA_DELAY_INT_EN		BIT(15)
#घोषणा HSDMA_DELAY_PEND_OFFSET		8
#घोषणा HSDMA_DELAY_TIME_OFFSET		0
#घोषणा HSDMA_DELAY_TX_OFFSET		16
#घोषणा HSDMA_DELAY_RX_OFFSET		0

#घोषणा HSDMA_DELAY_INIT(x)		(HSDMA_DELAY_INT_EN | \
		((x) << HSDMA_DELAY_PEND_OFFSET))
#घोषणा HSDMA_DELAY(x)			((HSDMA_DELAY_INIT(x) << \
		HSDMA_DELAY_TX_OFFSET) | HSDMA_DELAY_INIT(x))

/* HSDMA_REG_INT_STATUS */
#घोषणा HSDMA_INT_DELAY_RX_COH		BIT(31)
#घोषणा HSDMA_INT_DELAY_RX_INT		BIT(30)
#घोषणा HSDMA_INT_DELAY_TX_COH		BIT(29)
#घोषणा HSDMA_INT_DELAY_TX_INT		BIT(28)
#घोषणा HSDMA_INT_RX_MASK		0x3
#घोषणा HSDMA_INT_RX_SHIFT		16
#घोषणा HSDMA_INT_RX_Q0			BIT(16)
#घोषणा HSDMA_INT_TX_MASK		0xf
#घोषणा HSDMA_INT_TX_SHIFT		0
#घोषणा HSDMA_INT_TX_Q0			BIT(0)

/* tx/rx dma desc flags */
#घोषणा HSDMA_PLEN_MASK			0x3fff
#घोषणा HSDMA_DESC_DONE			BIT(31)
#घोषणा HSDMA_DESC_LS0			BIT(30)
#घोषणा HSDMA_DESC_PLEN0(_x)		(((_x) & HSDMA_PLEN_MASK) << 16)
#घोषणा HSDMA_DESC_TAG			BIT(15)
#घोषणा HSDMA_DESC_LS1			BIT(14)
#घोषणा HSDMA_DESC_PLEN1(_x)		((_x) & HSDMA_PLEN_MASK)

/* align 4 bytes */
#घोषणा HSDMA_ALIGN_SIZE		3
/* align size 128bytes */
#घोषणा HSDMA_MAX_PLEN			0x3f80

काष्ठा hsdma_desc अणु
	u32 addr0;
	u32 flags;
	u32 addr1;
	u32 unused;
पूर्ण;

काष्ठा mtk_hsdma_sg अणु
	dma_addr_t src_addr;
	dma_addr_t dst_addr;
	u32 len;
पूर्ण;

काष्ठा mtk_hsdma_desc अणु
	काष्ठा virt_dma_desc vdesc;
	अचिन्हित पूर्णांक num_sgs;
	काष्ठा mtk_hsdma_sg sg[1];
पूर्ण;

काष्ठा mtk_hsdma_chan अणु
	काष्ठा virt_dma_chan vchan;
	अचिन्हित पूर्णांक id;
	dma_addr_t desc_addr;
	पूर्णांक tx_idx;
	पूर्णांक rx_idx;
	काष्ठा hsdma_desc *tx_ring;
	काष्ठा hsdma_desc *rx_ring;
	काष्ठा mtk_hsdma_desc *desc;
	अचिन्हित पूर्णांक next_sg;
पूर्ण;

काष्ठा mtk_hsdam_engine अणु
	काष्ठा dma_device ddev;
	काष्ठा device_dma_parameters dma_parms;
	व्योम __iomem *base;
	काष्ठा tasklet_काष्ठा task;
	अस्थिर अचिन्हित दीर्घ chan_issued;

	काष्ठा mtk_hsdma_chan chan[1];
पूर्ण;

अटल अंतरभूत काष्ठा mtk_hsdam_engine *mtk_hsdma_chan_get_dev(
		काष्ठा mtk_hsdma_chan *chan)
अणु
	वापस container_of(chan->vchan.chan.device, काष्ठा mtk_hsdam_engine,
			ddev);
पूर्ण

अटल अंतरभूत काष्ठा mtk_hsdma_chan *to_mtk_hsdma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा mtk_hsdma_chan, vchan.chan);
पूर्ण

अटल अंतरभूत काष्ठा mtk_hsdma_desc *to_mtk_hsdma_desc(
		काष्ठा virt_dma_desc *vdesc)
अणु
	वापस container_of(vdesc, काष्ठा mtk_hsdma_desc, vdesc);
पूर्ण

अटल अंतरभूत u32 mtk_hsdma_पढ़ो(काष्ठा mtk_hsdam_engine *hsdma, u32 reg)
अणु
	वापस पढ़ोl(hsdma->base + reg);
पूर्ण

अटल अंतरभूत व्योम mtk_hsdma_ग_लिखो(काष्ठा mtk_hsdam_engine *hsdma,
				   अचिन्हित पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, hsdma->base + reg);
पूर्ण

अटल व्योम mtk_hsdma_reset_chan(काष्ठा mtk_hsdam_engine *hsdma,
				 काष्ठा mtk_hsdma_chan *chan)
अणु
	chan->tx_idx = 0;
	chan->rx_idx = HSDMA_DESCS_NUM - 1;

	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_TX_CTX, chan->tx_idx);
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_RX_CRX, chan->rx_idx);

	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_RST_CFG,
			0x1 << (chan->id + HSDMA_RST_TX_SHIFT));
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_RST_CFG,
			0x1 << (chan->id + HSDMA_RST_RX_SHIFT));
पूर्ण

अटल व्योम hsdma_dump_reg(काष्ठा mtk_hsdam_engine *hsdma)
अणु
	dev_dbg(hsdma->ddev.dev,
		"tbase %08x, tcnt %08x, tctx %08x, tdtx: %08x, rbase %08x, rcnt %08x, rctx %08x, rdtx %08x\n",
		mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_TX_BASE),
		mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_TX_CNT),
		mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_TX_CTX),
		mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_TX_DTX),
		mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_RX_BASE),
		mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_RX_CNT),
		mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_RX_CRX),
		mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_RX_DRX));

	dev_dbg(hsdma->ddev.dev,
		"info %08x, glo %08x, delay %08x, intr_stat %08x, intr_mask %08x\n",
		mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_INFO),
		mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_GLO_CFG),
		mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_DELAY_INT),
		mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_INT_STATUS),
		mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_INT_MASK));
पूर्ण

अटल व्योम hsdma_dump_desc(काष्ठा mtk_hsdam_engine *hsdma,
			    काष्ठा mtk_hsdma_chan *chan)
अणु
	काष्ठा hsdma_desc *tx_desc;
	काष्ठा hsdma_desc *rx_desc;
	पूर्णांक i;

	dev_dbg(hsdma->ddev.dev, "tx idx: %d, rx idx: %d\n",
		chan->tx_idx, chan->rx_idx);

	क्रम (i = 0; i < HSDMA_DESCS_NUM; i++) अणु
		tx_desc = &chan->tx_ring[i];
		rx_desc = &chan->rx_ring[i];

		dev_dbg(hsdma->ddev.dev,
			"%d tx addr0: %08x, flags %08x, tx addr1: %08x, rx addr0 %08x, flags %08x\n",
			i, tx_desc->addr0, tx_desc->flags,
			tx_desc->addr1, rx_desc->addr0, rx_desc->flags);
	पूर्ण
पूर्ण

अटल व्योम mtk_hsdma_reset(काष्ठा mtk_hsdam_engine *hsdma,
			    काष्ठा mtk_hsdma_chan *chan)
अणु
	पूर्णांक i;

	/* disable dma */
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_GLO_CFG, 0);

	/* disable पूर्णांकr */
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_INT_MASK, 0);

	/* init desc value */
	क्रम (i = 0; i < HSDMA_DESCS_NUM; i++) अणु
		chan->tx_ring[i].addr0 = 0;
		chan->tx_ring[i].flags = HSDMA_DESC_LS0 | HSDMA_DESC_DONE;
	पूर्ण
	क्रम (i = 0; i < HSDMA_DESCS_NUM; i++) अणु
		chan->rx_ring[i].addr0 = 0;
		chan->rx_ring[i].flags = 0;
	पूर्ण

	/* reset */
	mtk_hsdma_reset_chan(hsdma, chan);

	/* enable पूर्णांकr */
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_INT_MASK, HSDMA_INT_RX_Q0);

	/* enable dma */
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_GLO_CFG, HSDMA_GLO_DEFAULT);
पूर्ण

अटल पूर्णांक mtk_hsdma_terminate_all(काष्ठा dma_chan *c)
अणु
	काष्ठा mtk_hsdma_chan *chan = to_mtk_hsdma_chan(c);
	काष्ठा mtk_hsdam_engine *hsdma = mtk_hsdma_chan_get_dev(chan);
	अचिन्हित दीर्घ समयout;
	LIST_HEAD(head);

	spin_lock_bh(&chan->vchan.lock);
	chan->desc = शून्य;
	clear_bit(chan->id, &hsdma->chan_issued);
	vchan_get_all_descriptors(&chan->vchan, &head);
	spin_unlock_bh(&chan->vchan.lock);

	vchan_dma_desc_मुक्त_list(&chan->vchan, &head);

	/* रुको dma transfer complete */
	समयout = jअगरfies + msecs_to_jअगरfies(2000);
	जबतक (mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_GLO_CFG) &
			(HSDMA_GLO_RX_BUSY | HSDMA_GLO_TX_BUSY)) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			hsdma_dump_desc(hsdma, chan);
			mtk_hsdma_reset(hsdma, chan);
			dev_err(hsdma->ddev.dev, "timeout, reset it\n");
			अवरोध;
		पूर्ण
		cpu_relax();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hsdma_start_transfer(काष्ठा mtk_hsdam_engine *hsdma,
				    काष्ठा mtk_hsdma_chan *chan)
अणु
	dma_addr_t src, dst;
	माप_प्रकार len, tlen;
	काष्ठा hsdma_desc *tx_desc, *rx_desc;
	काष्ठा mtk_hsdma_sg *sg;
	अचिन्हित पूर्णांक i;
	पूर्णांक rx_idx;

	sg = &chan->desc->sg[0];
	len = sg->len;
	chan->desc->num_sgs = DIV_ROUND_UP(len, HSDMA_MAX_PLEN);

	/* tx desc */
	src = sg->src_addr;
	क्रम (i = 0; i < chan->desc->num_sgs; i++) अणु
		tx_desc = &chan->tx_ring[chan->tx_idx];

		अगर (len > HSDMA_MAX_PLEN)
			tlen = HSDMA_MAX_PLEN;
		अन्यथा
			tlen = len;

		अगर (i & 0x1) अणु
			tx_desc->addr1 = src;
			tx_desc->flags |= HSDMA_DESC_PLEN1(tlen);
		पूर्ण अन्यथा अणु
			tx_desc->addr0 = src;
			tx_desc->flags = HSDMA_DESC_PLEN0(tlen);

			/* update index */
			chan->tx_idx = HSDMA_NEXT_DESC(chan->tx_idx);
		पूर्ण

		src += tlen;
		len -= tlen;
	पूर्ण
	अगर (i & 0x1)
		tx_desc->flags |= HSDMA_DESC_LS0;
	अन्यथा
		tx_desc->flags |= HSDMA_DESC_LS1;

	/* rx desc */
	rx_idx = HSDMA_NEXT_DESC(chan->rx_idx);
	len = sg->len;
	dst = sg->dst_addr;
	क्रम (i = 0; i < chan->desc->num_sgs; i++) अणु
		rx_desc = &chan->rx_ring[rx_idx];
		अगर (len > HSDMA_MAX_PLEN)
			tlen = HSDMA_MAX_PLEN;
		अन्यथा
			tlen = len;

		rx_desc->addr0 = dst;
		rx_desc->flags = HSDMA_DESC_PLEN0(tlen);

		dst += tlen;
		len -= tlen;

		/* update index */
		rx_idx = HSDMA_NEXT_DESC(rx_idx);
	पूर्ण

	/* make sure desc and index all up to date */
	wmb();
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_TX_CTX, chan->tx_idx);

	वापस 0;
पूर्ण

अटल पूर्णांक gdma_next_desc(काष्ठा mtk_hsdma_chan *chan)
अणु
	काष्ठा virt_dma_desc *vdesc;

	vdesc = vchan_next_desc(&chan->vchan);
	अगर (!vdesc) अणु
		chan->desc = शून्य;
		वापस 0;
	पूर्ण
	chan->desc = to_mtk_hsdma_desc(vdesc);
	chan->next_sg = 0;

	वापस 1;
पूर्ण

अटल व्योम mtk_hsdma_chan_करोne(काष्ठा mtk_hsdam_engine *hsdma,
				काष्ठा mtk_hsdma_chan *chan)
अणु
	काष्ठा mtk_hsdma_desc *desc;
	पूर्णांक chan_issued;

	chan_issued = 0;
	spin_lock_bh(&chan->vchan.lock);
	desc = chan->desc;
	अगर (likely(desc)) अणु
		अगर (chan->next_sg == desc->num_sgs) अणु
			list_del(&desc->vdesc.node);
			vchan_cookie_complete(&desc->vdesc);
			chan_issued = gdma_next_desc(chan);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(hsdma->ddev.dev, "no desc to complete\n");
	पूर्ण

	अगर (chan_issued)
		set_bit(chan->id, &hsdma->chan_issued);
	spin_unlock_bh(&chan->vchan.lock);
पूर्ण

अटल irqवापस_t mtk_hsdma_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा mtk_hsdam_engine *hsdma = devid;
	u32 status;

	status = mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_INT_STATUS);
	अगर (unlikely(!status))
		वापस IRQ_NONE;

	अगर (likely(status & HSDMA_INT_RX_Q0))
		tasklet_schedule(&hsdma->task);
	अन्यथा
		dev_dbg(hsdma->ddev.dev, "unhandle irq status %08x\n", status);
	/* clean पूर्णांकr bits */
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_INT_STATUS, status);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mtk_hsdma_issue_pending(काष्ठा dma_chan *c)
अणु
	काष्ठा mtk_hsdma_chan *chan = to_mtk_hsdma_chan(c);
	काष्ठा mtk_hsdam_engine *hsdma = mtk_hsdma_chan_get_dev(chan);

	spin_lock_bh(&chan->vchan.lock);
	अगर (vchan_issue_pending(&chan->vchan) && !chan->desc) अणु
		अगर (gdma_next_desc(chan)) अणु
			set_bit(chan->id, &hsdma->chan_issued);
			tasklet_schedule(&hsdma->task);
		पूर्ण अन्यथा अणु
			dev_dbg(hsdma->ddev.dev, "no desc to issue\n");
		पूर्ण
	पूर्ण
	spin_unlock_bh(&chan->vchan.lock);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *mtk_hsdma_prep_dma_स_नकल(
		काष्ठा dma_chan *c, dma_addr_t dest, dma_addr_t src,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mtk_hsdma_chan *chan = to_mtk_hsdma_chan(c);
	काष्ठा mtk_hsdma_desc *desc;

	अगर (len <= 0)
		वापस शून्य;

	desc = kzalloc(माप(*desc), GFP_ATOMIC);
	अगर (!desc) अणु
		dev_err(c->device->dev, "alloc memcpy decs error\n");
		वापस शून्य;
	पूर्ण

	desc->sg[0].src_addr = src;
	desc->sg[0].dst_addr = dest;
	desc->sg[0].len = len;

	वापस vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
पूर्ण

अटल क्रमागत dma_status mtk_hsdma_tx_status(काष्ठा dma_chan *c,
					   dma_cookie_t cookie,
					   काष्ठा dma_tx_state *state)
अणु
	वापस dma_cookie_status(c, cookie, state);
पूर्ण

अटल व्योम mtk_hsdma_मुक्त_chan_resources(काष्ठा dma_chan *c)
अणु
	vchan_मुक्त_chan_resources(to_virt_chan(c));
पूर्ण

अटल व्योम mtk_hsdma_desc_मुक्त(काष्ठा virt_dma_desc *vdesc)
अणु
	kमुक्त(container_of(vdesc, काष्ठा mtk_hsdma_desc, vdesc));
पूर्ण

अटल व्योम mtk_hsdma_tx(काष्ठा mtk_hsdam_engine *hsdma)
अणु
	काष्ठा mtk_hsdma_chan *chan;

	अगर (test_and_clear_bit(0, &hsdma->chan_issued)) अणु
		chan = &hsdma->chan[0];
		अगर (chan->desc)
			mtk_hsdma_start_transfer(hsdma, chan);
		अन्यथा
			dev_dbg(hsdma->ddev.dev, "chan 0 no desc to issue\n");
	पूर्ण
पूर्ण

अटल व्योम mtk_hsdma_rx(काष्ठा mtk_hsdam_engine *hsdma)
अणु
	काष्ठा mtk_hsdma_chan *chan;
	पूर्णांक next_idx, drx_idx, cnt;

	chan = &hsdma->chan[0];
	next_idx = HSDMA_NEXT_DESC(chan->rx_idx);
	drx_idx = mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_RX_DRX);

	cnt = (drx_idx - next_idx) & HSDMA_DESCS_MASK;
	अगर (!cnt)
		वापस;

	chan->next_sg += cnt;
	chan->rx_idx = (chan->rx_idx + cnt) & HSDMA_DESCS_MASK;

	/* update rx crx */
	wmb();
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_RX_CRX, chan->rx_idx);

	mtk_hsdma_chan_करोne(hsdma, chan);
पूर्ण

अटल व्योम mtk_hsdma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mtk_hsdam_engine *hsdma = from_tasklet(hsdma, t, task);

	mtk_hsdma_rx(hsdma);
	mtk_hsdma_tx(hsdma);
पूर्ण

अटल पूर्णांक mtk_hsdam_alloc_desc(काष्ठा mtk_hsdam_engine *hsdma,
				काष्ठा mtk_hsdma_chan *chan)
अणु
	पूर्णांक i;

	chan->tx_ring = dma_alloc_coherent(hsdma->ddev.dev,
					   2 * HSDMA_DESCS_NUM *
					   माप(*chan->tx_ring),
			&chan->desc_addr, GFP_ATOMIC | __GFP_ZERO);
	अगर (!chan->tx_ring)
		जाओ no_mem;

	chan->rx_ring = &chan->tx_ring[HSDMA_DESCS_NUM];

	/* init tx ring value */
	क्रम (i = 0; i < HSDMA_DESCS_NUM; i++)
		chan->tx_ring[i].flags = HSDMA_DESC_LS0 | HSDMA_DESC_DONE;

	वापस 0;
no_mem:
	वापस -ENOMEM;
पूर्ण

अटल व्योम mtk_hsdam_मुक्त_desc(काष्ठा mtk_hsdam_engine *hsdma,
				काष्ठा mtk_hsdma_chan *chan)
अणु
	अगर (chan->tx_ring) अणु
		dma_मुक्त_coherent(hsdma->ddev.dev,
				  2 * HSDMA_DESCS_NUM * माप(*chan->tx_ring),
				  chan->tx_ring, chan->desc_addr);
		chan->tx_ring = शून्य;
		chan->rx_ring = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_hsdma_init(काष्ठा mtk_hsdam_engine *hsdma)
अणु
	काष्ठा mtk_hsdma_chan *chan;
	पूर्णांक ret;
	u32 reg;

	/* init desc */
	chan = &hsdma->chan[0];
	ret = mtk_hsdam_alloc_desc(hsdma, chan);
	अगर (ret)
		वापस ret;

	/* tx */
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_TX_BASE, chan->desc_addr);
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_TX_CNT, HSDMA_DESCS_NUM);
	/* rx */
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_RX_BASE, chan->desc_addr +
			(माप(काष्ठा hsdma_desc) * HSDMA_DESCS_NUM));
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_RX_CNT, HSDMA_DESCS_NUM);
	/* reset */
	mtk_hsdma_reset_chan(hsdma, chan);

	/* enable rx पूर्णांकr */
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_INT_MASK, HSDMA_INT_RX_Q0);

	/* enable dma */
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_GLO_CFG, HSDMA_GLO_DEFAULT);

	/* hardware info */
	reg = mtk_hsdma_पढ़ो(hsdma, HSDMA_REG_INFO);
	dev_info(hsdma->ddev.dev, "rx: %d, tx: %d\n",
		 (reg >> HSDMA_INFO_RX_SHIFT) & HSDMA_INFO_RX_MASK,
		 (reg >> HSDMA_INFO_TX_SHIFT) & HSDMA_INFO_TX_MASK);

	hsdma_dump_reg(hsdma);

	वापस ret;
पूर्ण

अटल व्योम mtk_hsdma_uninit(काष्ठा mtk_hsdam_engine *hsdma)
अणु
	काष्ठा mtk_hsdma_chan *chan;

	/* disable dma */
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_GLO_CFG, 0);

	/* disable पूर्णांकr */
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_INT_MASK, 0);

	/* मुक्त desc */
	chan = &hsdma->chan[0];
	mtk_hsdam_मुक्त_desc(hsdma, chan);

	/* tx */
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_TX_BASE, 0);
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_TX_CNT, 0);
	/* rx */
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_RX_BASE, 0);
	mtk_hsdma_ग_लिखो(hsdma, HSDMA_REG_RX_CNT, 0);
	/* reset */
	mtk_hsdma_reset_chan(hsdma, chan);
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_hsdma_of_match[] = अणु
	अणु .compatible = "mediatek,mt7621-hsdma" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक mtk_hsdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा mtk_hsdma_chan *chan;
	काष्ठा mtk_hsdam_engine *hsdma;
	काष्ठा dma_device *dd;
	पूर्णांक ret;
	पूर्णांक irq;
	व्योम __iomem *base;

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	match = of_match_device(mtk_hsdma_of_match, &pdev->dev);
	अगर (!match)
		वापस -EINVAL;

	hsdma = devm_kzalloc(&pdev->dev, माप(*hsdma), GFP_KERNEL);
	अगर (!hsdma)
		वापस -EINVAL;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);
	hsdma->base = base + HSDMA_BASE_OFFSET;
	tasklet_setup(&hsdma->task, mtk_hsdma_tasklet);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;
	ret = devm_request_irq(&pdev->dev, irq, mtk_hsdma_irq,
			       0, dev_name(&pdev->dev), hsdma);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request irq\n");
		वापस ret;
	पूर्ण

	device_reset(&pdev->dev);

	dd = &hsdma->ddev;
	dma_cap_set(DMA_MEMCPY, dd->cap_mask);
	dd->copy_align = HSDMA_ALIGN_SIZE;
	dd->device_मुक्त_chan_resources = mtk_hsdma_मुक्त_chan_resources;
	dd->device_prep_dma_स_नकल = mtk_hsdma_prep_dma_स_नकल;
	dd->device_terminate_all = mtk_hsdma_terminate_all;
	dd->device_tx_status = mtk_hsdma_tx_status;
	dd->device_issue_pending = mtk_hsdma_issue_pending;
	dd->dev = &pdev->dev;
	dd->dev->dma_parms = &hsdma->dma_parms;
	dma_set_max_seg_size(dd->dev, HSDMA_MAX_PLEN);
	INIT_LIST_HEAD(&dd->channels);

	chan = &hsdma->chan[0];
	chan->id = 0;
	chan->vchan.desc_मुक्त = mtk_hsdma_desc_मुक्त;
	vchan_init(&chan->vchan, dd);

	/* init hardware */
	ret = mtk_hsdma_init(hsdma);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to alloc ring descs\n");
		वापस ret;
	पूर्ण

	ret = dma_async_device_रेजिस्टर(dd);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register dma device\n");
		जाओ err_uninit_hsdma;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
					 of_dma_xlate_by_chan_id, hsdma);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register of dma controller\n");
		जाओ err_unरेजिस्टर;
	पूर्ण

	platक्रमm_set_drvdata(pdev, hsdma);

	वापस 0;

err_unरेजिस्टर:
	dma_async_device_unरेजिस्टर(dd);
err_uninit_hsdma:
	mtk_hsdma_uninit(hsdma);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_hsdma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_hsdam_engine *hsdma = platक्रमm_get_drvdata(pdev);

	mtk_hsdma_uninit(hsdma);

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&hsdma->ddev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mtk_hsdma_driver = अणु
	.probe = mtk_hsdma_probe,
	.हटाओ = mtk_hsdma_हटाओ,
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = mtk_hsdma_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mtk_hsdma_driver);

MODULE_AUTHOR("Michael Lee <igvtee@gmail.com>");
MODULE_DESCRIPTION("MTK HSDMA driver");
MODULE_LICENSE("GPL v2");
