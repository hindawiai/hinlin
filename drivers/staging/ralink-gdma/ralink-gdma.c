<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  GDMA4740 DMAC support
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

#घोषणा GDMA_REG_SRC_ADDR(x)		(0x00 + (x) * 0x10)
#घोषणा GDMA_REG_DST_ADDR(x)		(0x04 + (x) * 0x10)

#घोषणा GDMA_REG_CTRL0(x)		(0x08 + (x) * 0x10)
#घोषणा GDMA_REG_CTRL0_TX_MASK		0xffff
#घोषणा GDMA_REG_CTRL0_TX_SHIFT		16
#घोषणा GDMA_REG_CTRL0_CURR_MASK	0xff
#घोषणा GDMA_REG_CTRL0_CURR_SHIFT	8
#घोषणा	GDMA_REG_CTRL0_SRC_ADDR_FIXED	BIT(7)
#घोषणा GDMA_REG_CTRL0_DST_ADDR_FIXED	BIT(6)
#घोषणा GDMA_REG_CTRL0_BURST_MASK	0x7
#घोषणा GDMA_REG_CTRL0_BURST_SHIFT	3
#घोषणा	GDMA_REG_CTRL0_DONE_INT		BIT(2)
#घोषणा	GDMA_REG_CTRL0_ENABLE		BIT(1)
#घोषणा GDMA_REG_CTRL0_SW_MODE          BIT(0)

#घोषणा GDMA_REG_CTRL1(x)		(0x0c + (x) * 0x10)
#घोषणा GDMA_REG_CTRL1_SEG_MASK		0xf
#घोषणा GDMA_REG_CTRL1_SEG_SHIFT	22
#घोषणा GDMA_REG_CTRL1_REQ_MASK		0x3f
#घोषणा GDMA_REG_CTRL1_SRC_REQ_SHIFT	16
#घोषणा GDMA_REG_CTRL1_DST_REQ_SHIFT	8
#घोषणा GDMA_REG_CTRL1_NEXT_MASK	0x1f
#घोषणा GDMA_REG_CTRL1_NEXT_SHIFT	3
#घोषणा GDMA_REG_CTRL1_COHERENT		BIT(2)
#घोषणा GDMA_REG_CTRL1_FAIL		BIT(1)
#घोषणा GDMA_REG_CTRL1_MASK		BIT(0)

#घोषणा GDMA_REG_UNMASK_INT		0x200
#घोषणा GDMA_REG_DONE_INT		0x204

#घोषणा GDMA_REG_GCT			0x220
#घोषणा GDMA_REG_GCT_CHAN_MASK		0x3
#घोषणा GDMA_REG_GCT_CHAN_SHIFT		3
#घोषणा GDMA_REG_GCT_VER_MASK		0x3
#घोषणा GDMA_REG_GCT_VER_SHIFT		1
#घोषणा GDMA_REG_GCT_ARBIT_RR		BIT(0)

#घोषणा GDMA_REG_REQSTS			0x2a0
#घोषणा GDMA_REG_ACKSTS			0x2a4
#घोषणा GDMA_REG_FINSTS			0x2a8

/* क्रम RT305X gdma रेजिस्टरs */
#घोषणा GDMA_RT305X_CTRL0_REQ_MASK	0xf
#घोषणा GDMA_RT305X_CTRL0_SRC_REQ_SHIFT	12
#घोषणा GDMA_RT305X_CTRL0_DST_REQ_SHIFT	8

#घोषणा GDMA_RT305X_CTRL1_FAIL		BIT(4)
#घोषणा GDMA_RT305X_CTRL1_NEXT_MASK	0x7
#घोषणा GDMA_RT305X_CTRL1_NEXT_SHIFT	1

#घोषणा GDMA_RT305X_STATUS_INT		0x80
#घोषणा GDMA_RT305X_STATUS_SIGNAL	0x84
#घोषणा GDMA_RT305X_GCT			0x88

/* क्रम MT7621 gdma रेजिस्टरs */
#घोषणा GDMA_REG_PERF_START(x)		(0x230 + (x) * 0x8)
#घोषणा GDMA_REG_PERF_END(x)		(0x234 + (x) * 0x8)

क्रमागत gdma_dma_transfer_size अणु
	GDMA_TRANSFER_SIZE_4BYTE	= 0,
	GDMA_TRANSFER_SIZE_8BYTE	= 1,
	GDMA_TRANSFER_SIZE_16BYTE	= 2,
	GDMA_TRANSFER_SIZE_32BYTE	= 3,
	GDMA_TRANSFER_SIZE_64BYTE	= 4,
पूर्ण;

काष्ठा gdma_dma_sg अणु
	dma_addr_t src_addr;
	dma_addr_t dst_addr;
	u32 len;
पूर्ण;

काष्ठा gdma_dma_desc अणु
	काष्ठा virt_dma_desc vdesc;

	क्रमागत dma_transfer_direction direction;
	bool cyclic;

	u32 residue;
	अचिन्हित पूर्णांक num_sgs;
	काष्ठा gdma_dma_sg sg[];
पूर्ण;

काष्ठा gdma_dmaengine_chan अणु
	काष्ठा virt_dma_chan vchan;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक slave_id;

	dma_addr_t fअगरo_addr;
	क्रमागत gdma_dma_transfer_size burst_size;

	काष्ठा gdma_dma_desc *desc;
	अचिन्हित पूर्णांक next_sg;
पूर्ण;

काष्ठा gdma_dma_dev अणु
	काष्ठा dma_device ddev;
	काष्ठा device_dma_parameters dma_parms;
	काष्ठा gdma_data *data;
	व्योम __iomem *base;
	काष्ठा tasklet_काष्ठा task;
	अस्थिर अचिन्हित दीर्घ chan_issued;
	atomic_t cnt;

	काष्ठा gdma_dmaengine_chan chan[];
पूर्ण;

काष्ठा gdma_data अणु
	पूर्णांक chancnt;
	u32 करोne_पूर्णांक_reg;
	व्योम (*init)(काष्ठा gdma_dma_dev *dma_dev);
	पूर्णांक (*start_transfer)(काष्ठा gdma_dmaengine_chan *chan);
पूर्ण;

अटल काष्ठा gdma_dma_dev *gdma_dma_chan_get_dev(
	काष्ठा gdma_dmaengine_chan *chan)
अणु
	वापस container_of(chan->vchan.chan.device, काष्ठा gdma_dma_dev,
		ddev);
पूर्ण

अटल काष्ठा gdma_dmaengine_chan *to_gdma_dma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा gdma_dmaengine_chan, vchan.chan);
पूर्ण

अटल काष्ठा gdma_dma_desc *to_gdma_dma_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	वापस container_of(vdesc, काष्ठा gdma_dma_desc, vdesc);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t gdma_dma_पढ़ो(काष्ठा gdma_dma_dev *dma_dev,
				     अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(dma_dev->base + reg);
पूर्ण

अटल अंतरभूत व्योम gdma_dma_ग_लिखो(काष्ठा gdma_dma_dev *dma_dev,
				  अचिन्हित पूर्णांक reg, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, dma_dev->base + reg);
पूर्ण

अटल क्रमागत gdma_dma_transfer_size gdma_dma_maxburst(u32 maxburst)
अणु
	अगर (maxburst < 2)
		वापस GDMA_TRANSFER_SIZE_4BYTE;
	अन्यथा अगर (maxburst < 4)
		वापस GDMA_TRANSFER_SIZE_8BYTE;
	अन्यथा अगर (maxburst < 8)
		वापस GDMA_TRANSFER_SIZE_16BYTE;
	अन्यथा अगर (maxburst < 16)
		वापस GDMA_TRANSFER_SIZE_32BYTE;
	अन्यथा
		वापस GDMA_TRANSFER_SIZE_64BYTE;
पूर्ण

अटल पूर्णांक gdma_dma_config(काष्ठा dma_chan *c,
			   काष्ठा dma_slave_config *config)
अणु
	काष्ठा gdma_dmaengine_chan *chan = to_gdma_dma_chan(c);
	काष्ठा gdma_dma_dev *dma_dev = gdma_dma_chan_get_dev(chan);

	अगर (config->device_fc) अणु
		dev_err(dma_dev->ddev.dev, "not support flow controller\n");
		वापस -EINVAL;
	पूर्ण

	चयन (config->direction) अणु
	हाल DMA_MEM_TO_DEV:
		अगर (config->dst_addr_width != DMA_SLAVE_BUSWIDTH_4_BYTES) अणु
			dev_err(dma_dev->ddev.dev, "only support 4 byte buswidth\n");
			वापस -EINVAL;
		पूर्ण
		chan->slave_id = config->slave_id;
		chan->fअगरo_addr = config->dst_addr;
		chan->burst_size = gdma_dma_maxburst(config->dst_maxburst);
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		अगर (config->src_addr_width != DMA_SLAVE_BUSWIDTH_4_BYTES) अणु
			dev_err(dma_dev->ddev.dev, "only support 4 byte buswidth\n");
			वापस -EINVAL;
		पूर्ण
		chan->slave_id = config->slave_id;
		chan->fअगरo_addr = config->src_addr;
		chan->burst_size = gdma_dma_maxburst(config->src_maxburst);
		अवरोध;
	शेष:
		dev_err(dma_dev->ddev.dev, "direction type %d error\n",
			config->direction);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gdma_dma_terminate_all(काष्ठा dma_chan *c)
अणु
	काष्ठा gdma_dmaengine_chan *chan = to_gdma_dma_chan(c);
	काष्ठा gdma_dma_dev *dma_dev = gdma_dma_chan_get_dev(chan);
	अचिन्हित दीर्घ flags, समयout;
	LIST_HEAD(head);
	पूर्णांक i = 0;

	spin_lock_irqsave(&chan->vchan.lock, flags);
	chan->desc = शून्य;
	clear_bit(chan->id, &dma_dev->chan_issued);
	vchan_get_all_descriptors(&chan->vchan, &head);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	vchan_dma_desc_मुक्त_list(&chan->vchan, &head);

	/* रुको dma transfer complete */
	समयout = jअगरfies + msecs_to_jअगरfies(5000);
	जबतक (gdma_dma_पढ़ो(dma_dev, GDMA_REG_CTRL0(chan->id)) &
			GDMA_REG_CTRL0_ENABLE) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			dev_err(dma_dev->ddev.dev, "chan %d wait timeout\n",
				chan->id);
			/* restore to init value */
			gdma_dma_ग_लिखो(dma_dev, GDMA_REG_CTRL0(chan->id), 0);
			अवरोध;
		पूर्ण
		cpu_relax();
		i++;
	पूर्ण

	अगर (i)
		dev_dbg(dma_dev->ddev.dev, "terminate chan %d loops %d\n",
			chan->id, i);

	वापस 0;
पूर्ण

अटल व्योम rt305x_dump_reg(काष्ठा gdma_dma_dev *dma_dev, पूर्णांक id)
अणु
	dev_dbg(dma_dev->ddev.dev, "chan %d, src %08x, dst %08x, ctr0 %08x, ctr1 %08x, intr %08x, signal %08x\n",
		id,
		gdma_dma_पढ़ो(dma_dev, GDMA_REG_SRC_ADDR(id)),
		gdma_dma_पढ़ो(dma_dev, GDMA_REG_DST_ADDR(id)),
		gdma_dma_पढ़ो(dma_dev, GDMA_REG_CTRL0(id)),
		gdma_dma_पढ़ो(dma_dev, GDMA_REG_CTRL1(id)),
		gdma_dma_पढ़ो(dma_dev, GDMA_RT305X_STATUS_INT),
		gdma_dma_पढ़ो(dma_dev, GDMA_RT305X_STATUS_SIGNAL));
पूर्ण

अटल पूर्णांक rt305x_gdma_start_transfer(काष्ठा gdma_dmaengine_chan *chan)
अणु
	काष्ठा gdma_dma_dev *dma_dev = gdma_dma_chan_get_dev(chan);
	dma_addr_t src_addr, dst_addr;
	काष्ठा gdma_dma_sg *sg;
	u32 ctrl0, ctrl1;

	/* verअगरy chan is alपढ़ोy stopped */
	ctrl0 = gdma_dma_पढ़ो(dma_dev, GDMA_REG_CTRL0(chan->id));
	अगर (unlikely(ctrl0 & GDMA_REG_CTRL0_ENABLE)) अणु
		dev_err(dma_dev->ddev.dev, "chan %d is start(%08x).\n",
			chan->id, ctrl0);
		rt305x_dump_reg(dma_dev, chan->id);
		वापस -EINVAL;
	पूर्ण

	sg = &chan->desc->sg[chan->next_sg];
	अगर (chan->desc->direction == DMA_MEM_TO_DEV) अणु
		src_addr = sg->src_addr;
		dst_addr = chan->fअगरo_addr;
		ctrl0 = GDMA_REG_CTRL0_DST_ADDR_FIXED |
			(8 << GDMA_RT305X_CTRL0_SRC_REQ_SHIFT) |
			(chan->slave_id << GDMA_RT305X_CTRL0_DST_REQ_SHIFT);
	पूर्ण अन्यथा अगर (chan->desc->direction == DMA_DEV_TO_MEM) अणु
		src_addr = chan->fअगरo_addr;
		dst_addr = sg->dst_addr;
		ctrl0 = GDMA_REG_CTRL0_SRC_ADDR_FIXED |
			(chan->slave_id << GDMA_RT305X_CTRL0_SRC_REQ_SHIFT) |
			(8 << GDMA_RT305X_CTRL0_DST_REQ_SHIFT);
	पूर्ण अन्यथा अगर (chan->desc->direction == DMA_MEM_TO_MEM) अणु
		/*
		 * TODO: स_नकल function have bugs. someसमय it will copy
		 * more 8 bytes data when using dmatest verअगरy.
		 */
		src_addr = sg->src_addr;
		dst_addr = sg->dst_addr;
		ctrl0 = GDMA_REG_CTRL0_SW_MODE |
			(8 << GDMA_REG_CTRL1_SRC_REQ_SHIFT) |
			(8 << GDMA_REG_CTRL1_DST_REQ_SHIFT);
	पूर्ण अन्यथा अणु
		dev_err(dma_dev->ddev.dev, "direction type %d error\n",
			chan->desc->direction);
		वापस -EINVAL;
	पूर्ण

	ctrl0 |= (sg->len << GDMA_REG_CTRL0_TX_SHIFT) |
		 (chan->burst_size << GDMA_REG_CTRL0_BURST_SHIFT) |
		 GDMA_REG_CTRL0_DONE_INT | GDMA_REG_CTRL0_ENABLE;
	ctrl1 = chan->id << GDMA_REG_CTRL1_NEXT_SHIFT;

	chan->next_sg++;
	gdma_dma_ग_लिखो(dma_dev, GDMA_REG_SRC_ADDR(chan->id), src_addr);
	gdma_dma_ग_लिखो(dma_dev, GDMA_REG_DST_ADDR(chan->id), dst_addr);
	gdma_dma_ग_लिखो(dma_dev, GDMA_REG_CTRL1(chan->id), ctrl1);

	/* make sure next_sg is update */
	wmb();
	gdma_dma_ग_लिखो(dma_dev, GDMA_REG_CTRL0(chan->id), ctrl0);

	वापस 0;
पूर्ण

अटल व्योम rt3883_dump_reg(काष्ठा gdma_dma_dev *dma_dev, पूर्णांक id)
अणु
	dev_dbg(dma_dev->ddev.dev, "chan %d, src %08x, dst %08x, ctr0 %08x, ctr1 %08x, unmask %08x, done %08x, req %08x, ack %08x, fin %08x\n",
		id,
		gdma_dma_पढ़ो(dma_dev, GDMA_REG_SRC_ADDR(id)),
		gdma_dma_पढ़ो(dma_dev, GDMA_REG_DST_ADDR(id)),
		gdma_dma_पढ़ो(dma_dev, GDMA_REG_CTRL0(id)),
		gdma_dma_पढ़ो(dma_dev, GDMA_REG_CTRL1(id)),
		gdma_dma_पढ़ो(dma_dev, GDMA_REG_UNMASK_INT),
		gdma_dma_पढ़ो(dma_dev, GDMA_REG_DONE_INT),
		gdma_dma_पढ़ो(dma_dev, GDMA_REG_REQSTS),
		gdma_dma_पढ़ो(dma_dev, GDMA_REG_ACKSTS),
		gdma_dma_पढ़ो(dma_dev, GDMA_REG_FINSTS));
पूर्ण

अटल पूर्णांक rt3883_gdma_start_transfer(काष्ठा gdma_dmaengine_chan *chan)
अणु
	काष्ठा gdma_dma_dev *dma_dev = gdma_dma_chan_get_dev(chan);
	dma_addr_t src_addr, dst_addr;
	काष्ठा gdma_dma_sg *sg;
	u32 ctrl0, ctrl1;

	/* verअगरy chan is alपढ़ोy stopped */
	ctrl0 = gdma_dma_पढ़ो(dma_dev, GDMA_REG_CTRL0(chan->id));
	अगर (unlikely(ctrl0 & GDMA_REG_CTRL0_ENABLE)) अणु
		dev_err(dma_dev->ddev.dev, "chan %d is start(%08x).\n",
			chan->id, ctrl0);
		rt3883_dump_reg(dma_dev, chan->id);
		वापस -EINVAL;
	पूर्ण

	sg = &chan->desc->sg[chan->next_sg];
	अगर (chan->desc->direction == DMA_MEM_TO_DEV) अणु
		src_addr = sg->src_addr;
		dst_addr = chan->fअगरo_addr;
		ctrl0 = GDMA_REG_CTRL0_DST_ADDR_FIXED;
		ctrl1 = (32 << GDMA_REG_CTRL1_SRC_REQ_SHIFT) |
			(chan->slave_id << GDMA_REG_CTRL1_DST_REQ_SHIFT);
	पूर्ण अन्यथा अगर (chan->desc->direction == DMA_DEV_TO_MEM) अणु
		src_addr = chan->fअगरo_addr;
		dst_addr = sg->dst_addr;
		ctrl0 = GDMA_REG_CTRL0_SRC_ADDR_FIXED;
		ctrl1 = (chan->slave_id << GDMA_REG_CTRL1_SRC_REQ_SHIFT) |
			(32 << GDMA_REG_CTRL1_DST_REQ_SHIFT) |
			GDMA_REG_CTRL1_COHERENT;
	पूर्ण अन्यथा अगर (chan->desc->direction == DMA_MEM_TO_MEM) अणु
		src_addr = sg->src_addr;
		dst_addr = sg->dst_addr;
		ctrl0 = GDMA_REG_CTRL0_SW_MODE;
		ctrl1 = (32 << GDMA_REG_CTRL1_SRC_REQ_SHIFT) |
			(32 << GDMA_REG_CTRL1_DST_REQ_SHIFT) |
			GDMA_REG_CTRL1_COHERENT;
	पूर्ण अन्यथा अणु
		dev_err(dma_dev->ddev.dev, "direction type %d error\n",
			chan->desc->direction);
		वापस -EINVAL;
	पूर्ण

	ctrl0 |= (sg->len << GDMA_REG_CTRL0_TX_SHIFT) |
		 (chan->burst_size << GDMA_REG_CTRL0_BURST_SHIFT) |
		 GDMA_REG_CTRL0_DONE_INT | GDMA_REG_CTRL0_ENABLE;
	ctrl1 |= chan->id << GDMA_REG_CTRL1_NEXT_SHIFT;

	chan->next_sg++;
	gdma_dma_ग_लिखो(dma_dev, GDMA_REG_SRC_ADDR(chan->id), src_addr);
	gdma_dma_ग_लिखो(dma_dev, GDMA_REG_DST_ADDR(chan->id), dst_addr);
	gdma_dma_ग_लिखो(dma_dev, GDMA_REG_CTRL1(chan->id), ctrl1);

	/* make sure next_sg is update */
	wmb();
	gdma_dma_ग_लिखो(dma_dev, GDMA_REG_CTRL0(chan->id), ctrl0);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gdma_start_transfer(काष्ठा gdma_dma_dev *dma_dev,
				      काष्ठा gdma_dmaengine_chan *chan)
अणु
	वापस dma_dev->data->start_transfer(chan);
पूर्ण

अटल पूर्णांक gdma_next_desc(काष्ठा gdma_dmaengine_chan *chan)
अणु
	काष्ठा virt_dma_desc *vdesc;

	vdesc = vchan_next_desc(&chan->vchan);
	अगर (!vdesc) अणु
		chan->desc = शून्य;
		वापस 0;
	पूर्ण
	chan->desc = to_gdma_dma_desc(vdesc);
	chan->next_sg = 0;

	वापस 1;
पूर्ण

अटल व्योम gdma_dma_chan_irq(काष्ठा gdma_dma_dev *dma_dev,
			      काष्ठा gdma_dmaengine_chan *chan)
अणु
	काष्ठा gdma_dma_desc *desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक chan_issued;

	chan_issued = 0;
	spin_lock_irqsave(&chan->vchan.lock, flags);
	desc = chan->desc;
	अगर (desc) अणु
		अगर (desc->cyclic) अणु
			vchan_cyclic_callback(&desc->vdesc);
			अगर (chan->next_sg == desc->num_sgs)
				chan->next_sg = 0;
			chan_issued = 1;
		पूर्ण अन्यथा अणु
			desc->residue -= desc->sg[chan->next_sg - 1].len;
			अगर (chan->next_sg == desc->num_sgs) अणु
				list_del(&desc->vdesc.node);
				vchan_cookie_complete(&desc->vdesc);
				chan_issued = gdma_next_desc(chan);
			पूर्ण अन्यथा अणु
				chan_issued = 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(dma_dev->ddev.dev, "chan %d no desc to complete\n",
			chan->id);
	पूर्ण
	अगर (chan_issued)
		set_bit(chan->id, &dma_dev->chan_issued);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
पूर्ण

अटल irqवापस_t gdma_dma_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा gdma_dma_dev *dma_dev = devid;
	u32 करोne, करोne_reg;
	अचिन्हित पूर्णांक i;

	करोne_reg = dma_dev->data->करोne_पूर्णांक_reg;
	करोne = gdma_dma_पढ़ो(dma_dev, करोne_reg);
	अगर (unlikely(!करोne))
		वापस IRQ_NONE;

	/* clean करोne bits */
	gdma_dma_ग_लिखो(dma_dev, करोne_reg, करोne);

	i = 0;
	जबतक (करोne) अणु
		अगर (करोne & 0x1) अणु
			gdma_dma_chan_irq(dma_dev, &dma_dev->chan[i]);
			atomic_dec(&dma_dev->cnt);
		पूर्ण
		करोne >>= 1;
		i++;
	पूर्ण

	/* start only have work to करो */
	अगर (dma_dev->chan_issued)
		tasklet_schedule(&dma_dev->task);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम gdma_dma_issue_pending(काष्ठा dma_chan *c)
अणु
	काष्ठा gdma_dmaengine_chan *chan = to_gdma_dma_chan(c);
	काष्ठा gdma_dma_dev *dma_dev = gdma_dma_chan_get_dev(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->vchan.lock, flags);
	अगर (vchan_issue_pending(&chan->vchan) && !chan->desc) अणु
		अगर (gdma_next_desc(chan)) अणु
			set_bit(chan->id, &dma_dev->chan_issued);
			tasklet_schedule(&dma_dev->task);
		पूर्ण अन्यथा अणु
			dev_dbg(dma_dev->ddev.dev, "chan %d no desc to issue\n",
				chan->id);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *gdma_dma_prep_slave_sg(
		काष्ठा dma_chan *c, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा gdma_dmaengine_chan *chan = to_gdma_dma_chan(c);
	काष्ठा gdma_dma_desc *desc;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;

	desc = kzalloc(काष्ठा_size(desc, sg, sg_len), GFP_ATOMIC);
	अगर (!desc) अणु
		dev_err(c->device->dev, "alloc sg decs error\n");
		वापस शून्य;
	पूर्ण
	desc->residue = 0;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		अगर (direction == DMA_MEM_TO_DEV) अणु
			desc->sg[i].src_addr = sg_dma_address(sg);
		पूर्ण अन्यथा अगर (direction == DMA_DEV_TO_MEM) अणु
			desc->sg[i].dst_addr = sg_dma_address(sg);
		पूर्ण अन्यथा अणु
			dev_err(c->device->dev, "direction type %d error\n",
				direction);
			जाओ मुक्त_desc;
		पूर्ण

		अगर (unlikely(sg_dma_len(sg) > GDMA_REG_CTRL0_TX_MASK)) अणु
			dev_err(c->device->dev, "sg len too large %d\n",
				sg_dma_len(sg));
			जाओ मुक्त_desc;
		पूर्ण
		desc->sg[i].len = sg_dma_len(sg);
		desc->residue += sg_dma_len(sg);
	पूर्ण

	desc->num_sgs = sg_len;
	desc->direction = direction;
	desc->cyclic = false;

	वापस vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);

मुक्त_desc:
	kमुक्त(desc);
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *gdma_dma_prep_dma_स_नकल(
		काष्ठा dma_chan *c, dma_addr_t dest, dma_addr_t src,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा gdma_dmaengine_chan *chan = to_gdma_dma_chan(c);
	काष्ठा gdma_dma_desc *desc;
	अचिन्हित पूर्णांक num_periods, i;
	माप_प्रकार xfer_count;

	अगर (len <= 0)
		वापस शून्य;

	chan->burst_size = gdma_dma_maxburst(len >> 2);

	xfer_count = GDMA_REG_CTRL0_TX_MASK;
	num_periods = DIV_ROUND_UP(len, xfer_count);

	desc = kzalloc(काष्ठा_size(desc, sg, num_periods), GFP_ATOMIC);
	अगर (!desc) अणु
		dev_err(c->device->dev, "alloc memcpy decs error\n");
		वापस शून्य;
	पूर्ण
	desc->residue = len;

	क्रम (i = 0; i < num_periods; i++) अणु
		desc->sg[i].src_addr = src;
		desc->sg[i].dst_addr = dest;
		अगर (len > xfer_count)
			desc->sg[i].len = xfer_count;
		अन्यथा
			desc->sg[i].len = len;
		src += desc->sg[i].len;
		dest += desc->sg[i].len;
		len -= desc->sg[i].len;
	पूर्ण

	desc->num_sgs = num_periods;
	desc->direction = DMA_MEM_TO_MEM;
	desc->cyclic = false;

	वापस vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *gdma_dma_prep_dma_cyclic(
	काष्ठा dma_chan *c, dma_addr_t buf_addr, माप_प्रकार buf_len,
	माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा gdma_dmaengine_chan *chan = to_gdma_dma_chan(c);
	काष्ठा gdma_dma_desc *desc;
	अचिन्हित पूर्णांक num_periods, i;

	अगर (buf_len % period_len)
		वापस शून्य;

	अगर (period_len > GDMA_REG_CTRL0_TX_MASK) अणु
		dev_err(c->device->dev, "cyclic len too large %d\n",
			period_len);
		वापस शून्य;
	पूर्ण

	num_periods = buf_len / period_len;
	desc = kzalloc(काष्ठा_size(desc, sg, num_periods), GFP_ATOMIC);
	अगर (!desc) अणु
		dev_err(c->device->dev, "alloc cyclic decs error\n");
		वापस शून्य;
	पूर्ण
	desc->residue = buf_len;

	क्रम (i = 0; i < num_periods; i++) अणु
		अगर (direction == DMA_MEM_TO_DEV) अणु
			desc->sg[i].src_addr = buf_addr;
		पूर्ण अन्यथा अगर (direction == DMA_DEV_TO_MEM) अणु
			desc->sg[i].dst_addr = buf_addr;
		पूर्ण अन्यथा अणु
			dev_err(c->device->dev, "direction type %d error\n",
				direction);
			जाओ मुक्त_desc;
		पूर्ण
		desc->sg[i].len = period_len;
		buf_addr += period_len;
	पूर्ण

	desc->num_sgs = num_periods;
	desc->direction = direction;
	desc->cyclic = true;

	वापस vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);

मुक्त_desc:
	kमुक्त(desc);
	वापस शून्य;
पूर्ण

अटल क्रमागत dma_status gdma_dma_tx_status(काष्ठा dma_chan *c,
					  dma_cookie_t cookie,
					  काष्ठा dma_tx_state *state)
अणु
	काष्ठा gdma_dmaengine_chan *chan = to_gdma_dma_chan(c);
	काष्ठा virt_dma_desc *vdesc;
	क्रमागत dma_status status;
	अचिन्हित दीर्घ flags;
	काष्ठा gdma_dma_desc *desc;

	status = dma_cookie_status(c, cookie, state);
	अगर (status == DMA_COMPLETE || !state)
		वापस status;

	spin_lock_irqsave(&chan->vchan.lock, flags);
	desc = chan->desc;
	अगर (desc && (cookie == desc->vdesc.tx.cookie)) अणु
		/*
		 * We never update edesc->residue in the cyclic हाल, so we
		 * can tell the reमुख्यing room to the end of the circular
		 * buffer.
		 */
		अगर (desc->cyclic)
			state->residue = desc->residue -
				((chan->next_sg - 1) * desc->sg[0].len);
		अन्यथा
			state->residue = desc->residue;
	पूर्ण अन्यथा अणु
		vdesc = vchan_find_desc(&chan->vchan, cookie);
		अगर (vdesc)
			state->residue = to_gdma_dma_desc(vdesc)->residue;
	पूर्ण
	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	dev_dbg(c->device->dev, "tx residue %d bytes\n", state->residue);

	वापस status;
पूर्ण

अटल व्योम gdma_dma_मुक्त_chan_resources(काष्ठा dma_chan *c)
अणु
	vchan_मुक्त_chan_resources(to_virt_chan(c));
पूर्ण

अटल व्योम gdma_dma_desc_मुक्त(काष्ठा virt_dma_desc *vdesc)
अणु
	kमुक्त(container_of(vdesc, काष्ठा gdma_dma_desc, vdesc));
पूर्ण

अटल व्योम gdma_dma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा gdma_dma_dev *dma_dev = from_tasklet(dma_dev, t, task);
	काष्ठा gdma_dmaengine_chan *chan;
	अटल अचिन्हित पूर्णांक last_chan;
	अचिन्हित पूर्णांक i, chan_mask;

	/* record last chan to round robin all chans */
	i = last_chan;
	chan_mask = dma_dev->data->chancnt - 1;
	करो अणु
		/*
		 * on mt7621. when verअगरy with dmatest with all
		 * channel is enable. we need to limit only two
		 * channel is working at the same समय. otherwise the
		 * data will have problem.
		 */
		अगर (atomic_पढ़ो(&dma_dev->cnt) >= 2) अणु
			last_chan = i;
			अवरोध;
		पूर्ण

		अगर (test_and_clear_bit(i, &dma_dev->chan_issued)) अणु
			chan = &dma_dev->chan[i];
			अगर (chan->desc) अणु
				atomic_inc(&dma_dev->cnt);
				gdma_start_transfer(dma_dev, chan);
			पूर्ण अन्यथा अणु
				dev_dbg(dma_dev->ddev.dev,
					"chan %d no desc to issue\n",
					chan->id);
			पूर्ण
			अगर (!dma_dev->chan_issued)
				अवरोध;
		पूर्ण

		i = (i + 1) & chan_mask;
	पूर्ण जबतक (i != last_chan);
पूर्ण

अटल व्योम rt305x_gdma_init(काष्ठा gdma_dma_dev *dma_dev)
अणु
	u32 gct;

	/* all chans round robin */
	gdma_dma_ग_लिखो(dma_dev, GDMA_RT305X_GCT, GDMA_REG_GCT_ARBIT_RR);

	gct = gdma_dma_पढ़ो(dma_dev, GDMA_RT305X_GCT);
	dev_info(dma_dev->ddev.dev, "revision: %d, channels: %d\n",
		 (gct >> GDMA_REG_GCT_VER_SHIFT) & GDMA_REG_GCT_VER_MASK,
		 8 << ((gct >> GDMA_REG_GCT_CHAN_SHIFT) &
			GDMA_REG_GCT_CHAN_MASK));
पूर्ण

अटल व्योम rt3883_gdma_init(काष्ठा gdma_dma_dev *dma_dev)
अणु
	u32 gct;

	/* all chans round robin */
	gdma_dma_ग_लिखो(dma_dev, GDMA_REG_GCT, GDMA_REG_GCT_ARBIT_RR);

	gct = gdma_dma_पढ़ो(dma_dev, GDMA_REG_GCT);
	dev_info(dma_dev->ddev.dev, "revision: %d, channels: %d\n",
		 (gct >> GDMA_REG_GCT_VER_SHIFT) & GDMA_REG_GCT_VER_MASK,
		 8 << ((gct >> GDMA_REG_GCT_CHAN_SHIFT) &
			GDMA_REG_GCT_CHAN_MASK));
पूर्ण

अटल काष्ठा gdma_data rt305x_gdma_data = अणु
	.chancnt = 8,
	.करोne_पूर्णांक_reg = GDMA_RT305X_STATUS_INT,
	.init = rt305x_gdma_init,
	.start_transfer = rt305x_gdma_start_transfer,
पूर्ण;

अटल काष्ठा gdma_data rt3883_gdma_data = अणु
	.chancnt = 16,
	.करोne_पूर्णांक_reg = GDMA_REG_DONE_INT,
	.init = rt3883_gdma_init,
	.start_transfer = rt3883_gdma_start_transfer,
पूर्ण;

अटल स्थिर काष्ठा of_device_id gdma_of_match_table[] = अणु
	अणु .compatible = "ralink,rt305x-gdma", .data = &rt305x_gdma_data पूर्ण,
	अणु .compatible = "ralink,rt3883-gdma", .data = &rt3883_gdma_data पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gdma_of_match_table);

अटल पूर्णांक gdma_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा gdma_dmaengine_chan *chan;
	काष्ठा gdma_dma_dev *dma_dev;
	काष्ठा dma_device *dd;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक irq;
	व्योम __iomem *base;
	काष्ठा gdma_data *data;

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	match = of_match_device(gdma_of_match_table, &pdev->dev);
	अगर (!match)
		वापस -EINVAL;
	data = (काष्ठा gdma_data *)match->data;

	dma_dev = devm_kzalloc(&pdev->dev,
			       काष्ठा_size(dma_dev, chan, data->chancnt),
			       GFP_KERNEL);
	अगर (!dma_dev)
		वापस -EINVAL;
	dma_dev->data = data;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);
	dma_dev->base = base;
	tasklet_setup(&dma_dev->task, gdma_dma_tasklet);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;
	ret = devm_request_irq(&pdev->dev, irq, gdma_dma_irq,
			       0, dev_name(&pdev->dev), dma_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request irq\n");
		वापस ret;
	पूर्ण

	ret = device_reset(&pdev->dev);
	अगर (ret)
		dev_err(&pdev->dev, "failed to reset: %d\n", ret);

	dd = &dma_dev->ddev;
	dma_cap_set(DMA_MEMCPY, dd->cap_mask);
	dma_cap_set(DMA_SLAVE, dd->cap_mask);
	dma_cap_set(DMA_CYCLIC, dd->cap_mask);
	dd->device_मुक्त_chan_resources = gdma_dma_मुक्त_chan_resources;
	dd->device_prep_dma_स_नकल = gdma_dma_prep_dma_स_नकल;
	dd->device_prep_slave_sg = gdma_dma_prep_slave_sg;
	dd->device_prep_dma_cyclic = gdma_dma_prep_dma_cyclic;
	dd->device_config = gdma_dma_config;
	dd->device_terminate_all = gdma_dma_terminate_all;
	dd->device_tx_status = gdma_dma_tx_status;
	dd->device_issue_pending = gdma_dma_issue_pending;

	dd->src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	dd->dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	dd->directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	dd->residue_granularity = DMA_RESIDUE_GRANULARITY_SEGMENT;

	dd->dev = &pdev->dev;
	dd->dev->dma_parms = &dma_dev->dma_parms;
	dma_set_max_seg_size(dd->dev, GDMA_REG_CTRL0_TX_MASK);
	INIT_LIST_HEAD(&dd->channels);

	क्रम (i = 0; i < data->chancnt; i++) अणु
		chan = &dma_dev->chan[i];
		chan->id = i;
		chan->vchan.desc_मुक्त = gdma_dma_desc_मुक्त;
		vchan_init(&chan->vchan, dd);
	पूर्ण

	/* init hardware */
	data->init(dma_dev);

	ret = dma_async_device_रेजिस्टर(dd);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register dma device\n");
		वापस ret;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
					 of_dma_xlate_by_chan_id, dma_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register of dma controller\n");
		जाओ err_unरेजिस्टर;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dma_dev);

	वापस 0;

err_unरेजिस्टर:
	dma_async_device_unरेजिस्टर(dd);
	वापस ret;
पूर्ण

अटल पूर्णांक gdma_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gdma_dma_dev *dma_dev = platक्रमm_get_drvdata(pdev);

	tasklet_समाप्त(&dma_dev->task);
	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&dma_dev->ddev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver gdma_dma_driver = अणु
	.probe = gdma_dma_probe,
	.हटाओ = gdma_dma_हटाओ,
	.driver = अणु
		.name = "gdma-rt2880",
		.of_match_table = gdma_of_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(gdma_dma_driver);

MODULE_DESCRIPTION("Ralink/MTK DMA driver");
MODULE_LICENSE("GPL v2");
