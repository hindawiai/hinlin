<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Analog Devices AXI-DMAC core
 *
 * Copyright 2013-2019 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/fpga/adi-axi-common.h>

#समावेश <dt-bindings/dma/axi-dmac.h>

#समावेश "dmaengine.h"
#समावेश "virt-dma.h"

/*
 * The AXI-DMAC is a soft IP core that is used in FPGA designs. The core has
 * various instantiation parameters which decided the exact feature set support
 * by the core.
 *
 * Each channel of the core has a source पूर्णांकerface and a destination पूर्णांकerface.
 * The number of channels and the type of the channel पूर्णांकerfaces is selected at
 * configuration समय. A पूर्णांकerface can either be a connected to a central memory
 * पूर्णांकerconnect, which allows access to प्रणाली memory, or it can be connected to
 * a dedicated bus which is directly connected to a data port on a peripheral.
 * Given that those are configuration options of the core that are selected when
 * it is instantiated this means that they can not be changed by software at
 * runसमय. By extension this means that each channel is uni-directional. It can
 * either be device to memory or memory to device, but not both. Also since the
 * device side is a dedicated data bus only connected to a single peripheral
 * there is no address than can or needs to be configured क्रम the device side.
 */

#घोषणा AXI_DMAC_REG_INTERFACE_DESC	0x10
#घोषणा   AXI_DMAC_DMA_SRC_TYPE_MSK	GENMASK(13, 12)
#घोषणा   AXI_DMAC_DMA_SRC_TYPE_GET(x)	FIELD_GET(AXI_DMAC_DMA_SRC_TYPE_MSK, x)
#घोषणा   AXI_DMAC_DMA_SRC_WIDTH_MSK	GENMASK(11, 8)
#घोषणा   AXI_DMAC_DMA_SRC_WIDTH_GET(x)	FIELD_GET(AXI_DMAC_DMA_SRC_WIDTH_MSK, x)
#घोषणा   AXI_DMAC_DMA_DST_TYPE_MSK	GENMASK(5, 4)
#घोषणा   AXI_DMAC_DMA_DST_TYPE_GET(x)	FIELD_GET(AXI_DMAC_DMA_DST_TYPE_MSK, x)
#घोषणा   AXI_DMAC_DMA_DST_WIDTH_MSK	GENMASK(3, 0)
#घोषणा   AXI_DMAC_DMA_DST_WIDTH_GET(x)	FIELD_GET(AXI_DMAC_DMA_DST_WIDTH_MSK, x)

#घोषणा AXI_DMAC_REG_IRQ_MASK		0x80
#घोषणा AXI_DMAC_REG_IRQ_PENDING	0x84
#घोषणा AXI_DMAC_REG_IRQ_SOURCE		0x88

#घोषणा AXI_DMAC_REG_CTRL		0x400
#घोषणा AXI_DMAC_REG_TRANSFER_ID	0x404
#घोषणा AXI_DMAC_REG_START_TRANSFER	0x408
#घोषणा AXI_DMAC_REG_FLAGS		0x40c
#घोषणा AXI_DMAC_REG_DEST_ADDRESS	0x410
#घोषणा AXI_DMAC_REG_SRC_ADDRESS	0x414
#घोषणा AXI_DMAC_REG_X_LENGTH		0x418
#घोषणा AXI_DMAC_REG_Y_LENGTH		0x41c
#घोषणा AXI_DMAC_REG_DEST_STRIDE	0x420
#घोषणा AXI_DMAC_REG_SRC_STRIDE		0x424
#घोषणा AXI_DMAC_REG_TRANSFER_DONE	0x428
#घोषणा AXI_DMAC_REG_ACTIVE_TRANSFER_ID 0x42c
#घोषणा AXI_DMAC_REG_STATUS		0x430
#घोषणा AXI_DMAC_REG_CURRENT_SRC_ADDR	0x434
#घोषणा AXI_DMAC_REG_CURRENT_DEST_ADDR	0x438
#घोषणा AXI_DMAC_REG_PARTIAL_XFER_LEN	0x44c
#घोषणा AXI_DMAC_REG_PARTIAL_XFER_ID	0x450

#घोषणा AXI_DMAC_CTRL_ENABLE		BIT(0)
#घोषणा AXI_DMAC_CTRL_PAUSE		BIT(1)

#घोषणा AXI_DMAC_IRQ_SOT		BIT(0)
#घोषणा AXI_DMAC_IRQ_EOT		BIT(1)

#घोषणा AXI_DMAC_FLAG_CYCLIC		BIT(0)
#घोषणा AXI_DMAC_FLAG_LAST		BIT(1)
#घोषणा AXI_DMAC_FLAG_PARTIAL_REPORT	BIT(2)

#घोषणा AXI_DMAC_FLAG_PARTIAL_XFER_DONE BIT(31)

/* The maximum ID allocated by the hardware is 31 */
#घोषणा AXI_DMAC_SG_UNUSED 32U

काष्ठा axi_dmac_sg अणु
	dma_addr_t src_addr;
	dma_addr_t dest_addr;
	अचिन्हित पूर्णांक x_len;
	अचिन्हित पूर्णांक y_len;
	अचिन्हित पूर्णांक dest_stride;
	अचिन्हित पूर्णांक src_stride;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक partial_len;
	bool schedule_when_मुक्त;
पूर्ण;

काष्ठा axi_dmac_desc अणु
	काष्ठा virt_dma_desc vdesc;
	bool cyclic;
	bool have_partial_xfer;

	अचिन्हित पूर्णांक num_submitted;
	अचिन्हित पूर्णांक num_completed;
	अचिन्हित पूर्णांक num_sgs;
	काष्ठा axi_dmac_sg sg[];
पूर्ण;

काष्ठा axi_dmac_chan अणु
	काष्ठा virt_dma_chan vchan;

	काष्ठा axi_dmac_desc *next_desc;
	काष्ठा list_head active_descs;
	क्रमागत dma_transfer_direction direction;

	अचिन्हित पूर्णांक src_width;
	अचिन्हित पूर्णांक dest_width;
	अचिन्हित पूर्णांक src_type;
	अचिन्हित पूर्णांक dest_type;

	अचिन्हित पूर्णांक max_length;
	अचिन्हित पूर्णांक address_align_mask;
	अचिन्हित पूर्णांक length_align_mask;

	bool hw_partial_xfer;
	bool hw_cyclic;
	bool hw_2d;
पूर्ण;

काष्ठा axi_dmac अणु
	व्योम __iomem *base;
	पूर्णांक irq;

	काष्ठा clk *clk;

	काष्ठा dma_device dma_dev;
	काष्ठा axi_dmac_chan chan;
पूर्ण;

अटल काष्ठा axi_dmac *chan_to_axi_dmac(काष्ठा axi_dmac_chan *chan)
अणु
	वापस container_of(chan->vchan.chan.device, काष्ठा axi_dmac,
		dma_dev);
पूर्ण

अटल काष्ठा axi_dmac_chan *to_axi_dmac_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा axi_dmac_chan, vchan.chan);
पूर्ण

अटल काष्ठा axi_dmac_desc *to_axi_dmac_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	वापस container_of(vdesc, काष्ठा axi_dmac_desc, vdesc);
पूर्ण

अटल व्योम axi_dmac_ग_लिखो(काष्ठा axi_dmac *axi_dmac, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl(val, axi_dmac->base + reg);
पूर्ण

अटल पूर्णांक axi_dmac_पढ़ो(काष्ठा axi_dmac *axi_dmac, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(axi_dmac->base + reg);
पूर्ण

अटल पूर्णांक axi_dmac_src_is_mem(काष्ठा axi_dmac_chan *chan)
अणु
	वापस chan->src_type == AXI_DMAC_BUS_TYPE_AXI_MM;
पूर्ण

अटल पूर्णांक axi_dmac_dest_is_mem(काष्ठा axi_dmac_chan *chan)
अणु
	वापस chan->dest_type == AXI_DMAC_BUS_TYPE_AXI_MM;
पूर्ण

अटल bool axi_dmac_check_len(काष्ठा axi_dmac_chan *chan, अचिन्हित पूर्णांक len)
अणु
	अगर (len == 0)
		वापस false;
	अगर ((len & chan->length_align_mask) != 0) /* Not aligned */
		वापस false;
	वापस true;
पूर्ण

अटल bool axi_dmac_check_addr(काष्ठा axi_dmac_chan *chan, dma_addr_t addr)
अणु
	अगर ((addr & chan->address_align_mask) != 0) /* Not aligned */
		वापस false;
	वापस true;
पूर्ण

अटल व्योम axi_dmac_start_transfer(काष्ठा axi_dmac_chan *chan)
अणु
	काष्ठा axi_dmac *dmac = chan_to_axi_dmac(chan);
	काष्ठा virt_dma_desc *vdesc;
	काष्ठा axi_dmac_desc *desc;
	काष्ठा axi_dmac_sg *sg;
	अचिन्हित पूर्णांक flags = 0;
	अचिन्हित पूर्णांक val;

	val = axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_START_TRANSFER);
	अगर (val) /* Queue is full, रुको क्रम the next SOT IRQ */
		वापस;

	desc = chan->next_desc;

	अगर (!desc) अणु
		vdesc = vchan_next_desc(&chan->vchan);
		अगर (!vdesc)
			वापस;
		list_move_tail(&vdesc->node, &chan->active_descs);
		desc = to_axi_dmac_desc(vdesc);
	पूर्ण
	sg = &desc->sg[desc->num_submitted];

	/* Alपढ़ोy queued in cyclic mode. Wait क्रम it to finish */
	अगर (sg->id != AXI_DMAC_SG_UNUSED) अणु
		sg->schedule_when_मुक्त = true;
		वापस;
	पूर्ण

	desc->num_submitted++;
	अगर (desc->num_submitted == desc->num_sgs ||
	    desc->have_partial_xfer) अणु
		अगर (desc->cyclic)
			desc->num_submitted = 0; /* Start again */
		अन्यथा
			chan->next_desc = शून्य;
		flags |= AXI_DMAC_FLAG_LAST;
	पूर्ण अन्यथा अणु
		chan->next_desc = desc;
	पूर्ण

	sg->id = axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_TRANSFER_ID);

	अगर (axi_dmac_dest_is_mem(chan)) अणु
		axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_DEST_ADDRESS, sg->dest_addr);
		axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_DEST_STRIDE, sg->dest_stride);
	पूर्ण

	अगर (axi_dmac_src_is_mem(chan)) अणु
		axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_SRC_ADDRESS, sg->src_addr);
		axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_SRC_STRIDE, sg->src_stride);
	पूर्ण

	/*
	 * If the hardware supports cyclic transfers and there is no callback to
	 * call and only a single segment, enable hw cyclic mode to aव्योम
	 * unnecessary पूर्णांकerrupts.
	 */
	अगर (chan->hw_cyclic && desc->cyclic && !desc->vdesc.tx.callback &&
		desc->num_sgs == 1)
		flags |= AXI_DMAC_FLAG_CYCLIC;

	अगर (chan->hw_partial_xfer)
		flags |= AXI_DMAC_FLAG_PARTIAL_REPORT;

	axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_X_LENGTH, sg->x_len - 1);
	axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_Y_LENGTH, sg->y_len - 1);
	axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_FLAGS, flags);
	axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_START_TRANSFER, 1);
पूर्ण

अटल काष्ठा axi_dmac_desc *axi_dmac_active_desc(काष्ठा axi_dmac_chan *chan)
अणु
	वापस list_first_entry_or_null(&chan->active_descs,
		काष्ठा axi_dmac_desc, vdesc.node);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक axi_dmac_total_sg_bytes(काष्ठा axi_dmac_chan *chan,
	काष्ठा axi_dmac_sg *sg)
अणु
	अगर (chan->hw_2d)
		वापस sg->x_len * sg->y_len;
	अन्यथा
		वापस sg->x_len;
पूर्ण

अटल व्योम axi_dmac_dequeue_partial_xfers(काष्ठा axi_dmac_chan *chan)
अणु
	काष्ठा axi_dmac *dmac = chan_to_axi_dmac(chan);
	काष्ठा axi_dmac_desc *desc;
	काष्ठा axi_dmac_sg *sg;
	u32 xfer_करोne, len, id, i;
	bool found_sg;

	करो अणु
		len = axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_PARTIAL_XFER_LEN);
		id  = axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_PARTIAL_XFER_ID);

		found_sg = false;
		list_क्रम_each_entry(desc, &chan->active_descs, vdesc.node) अणु
			क्रम (i = 0; i < desc->num_sgs; i++) अणु
				sg = &desc->sg[i];
				अगर (sg->id == AXI_DMAC_SG_UNUSED)
					जारी;
				अगर (sg->id == id) अणु
					desc->have_partial_xfer = true;
					sg->partial_len = len;
					found_sg = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (found_sg)
				अवरोध;
		पूर्ण

		अगर (found_sg) अणु
			dev_dbg(dmac->dma_dev.dev,
				"Found partial segment id=%u, len=%u\n",
				id, len);
		पूर्ण अन्यथा अणु
			dev_warn(dmac->dma_dev.dev,
				 "Not found partial segment id=%u, len=%u\n",
				 id, len);
		पूर्ण

		/* Check अगर we have any more partial transfers */
		xfer_करोne = axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_TRANSFER_DONE);
		xfer_करोne = !(xfer_करोne & AXI_DMAC_FLAG_PARTIAL_XFER_DONE);

	पूर्ण जबतक (!xfer_करोne);
पूर्ण

अटल व्योम axi_dmac_compute_residue(काष्ठा axi_dmac_chan *chan,
	काष्ठा axi_dmac_desc *active)
अणु
	काष्ठा dmaengine_result *rslt = &active->vdesc.tx_result;
	अचिन्हित पूर्णांक start = active->num_completed - 1;
	काष्ठा axi_dmac_sg *sg;
	अचिन्हित पूर्णांक i, total;

	rslt->result = DMA_TRANS_NOERROR;
	rslt->residue = 0;

	/*
	 * We get here अगर the last completed segment is partial, which
	 * means we can compute the residue from that segment onwards
	 */
	क्रम (i = start; i < active->num_sgs; i++) अणु
		sg = &active->sg[i];
		total = axi_dmac_total_sg_bytes(chan, sg);
		rslt->residue += (total - sg->partial_len);
	पूर्ण
पूर्ण

अटल bool axi_dmac_transfer_करोne(काष्ठा axi_dmac_chan *chan,
	अचिन्हित पूर्णांक completed_transfers)
अणु
	काष्ठा axi_dmac_desc *active;
	काष्ठा axi_dmac_sg *sg;
	bool start_next = false;

	active = axi_dmac_active_desc(chan);
	अगर (!active)
		वापस false;

	अगर (chan->hw_partial_xfer &&
	    (completed_transfers & AXI_DMAC_FLAG_PARTIAL_XFER_DONE))
		axi_dmac_dequeue_partial_xfers(chan);

	करो अणु
		sg = &active->sg[active->num_completed];
		अगर (sg->id == AXI_DMAC_SG_UNUSED) /* Not yet submitted */
			अवरोध;
		अगर (!(BIT(sg->id) & completed_transfers))
			अवरोध;
		active->num_completed++;
		sg->id = AXI_DMAC_SG_UNUSED;
		अगर (sg->schedule_when_मुक्त) अणु
			sg->schedule_when_मुक्त = false;
			start_next = true;
		पूर्ण

		अगर (sg->partial_len)
			axi_dmac_compute_residue(chan, active);

		अगर (active->cyclic)
			vchan_cyclic_callback(&active->vdesc);

		अगर (active->num_completed == active->num_sgs ||
		    sg->partial_len) अणु
			अगर (active->cyclic) अणु
				active->num_completed = 0; /* wrap around */
			पूर्ण अन्यथा अणु
				list_del(&active->vdesc.node);
				vchan_cookie_complete(&active->vdesc);
				active = axi_dmac_active_desc(chan);
			पूर्ण
		पूर्ण
	पूर्ण जबतक (active);

	वापस start_next;
पूर्ण

अटल irqवापस_t axi_dmac_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा axi_dmac *dmac = devid;
	अचिन्हित पूर्णांक pending;
	bool start_next = false;

	pending = axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_IRQ_PENDING);
	अगर (!pending)
		वापस IRQ_NONE;

	axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_IRQ_PENDING, pending);

	spin_lock(&dmac->chan.vchan.lock);
	/* One or more transfers have finished */
	अगर (pending & AXI_DMAC_IRQ_EOT) अणु
		अचिन्हित पूर्णांक completed;

		completed = axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_TRANSFER_DONE);
		start_next = axi_dmac_transfer_करोne(&dmac->chan, completed);
	पूर्ण
	/* Space has become available in the descriptor queue */
	अगर ((pending & AXI_DMAC_IRQ_SOT) || start_next)
		axi_dmac_start_transfer(&dmac->chan);
	spin_unlock(&dmac->chan.vchan.lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक axi_dmac_terminate_all(काष्ठा dma_chan *c)
अणु
	काष्ठा axi_dmac_chan *chan = to_axi_dmac_chan(c);
	काष्ठा axi_dmac *dmac = chan_to_axi_dmac(chan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&chan->vchan.lock, flags);
	axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_CTRL, 0);
	chan->next_desc = शून्य;
	vchan_get_all_descriptors(&chan->vchan, &head);
	list_splice_tail_init(&chan->active_descs, &head);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	vchan_dma_desc_मुक्त_list(&chan->vchan, &head);

	वापस 0;
पूर्ण

अटल व्योम axi_dmac_synchronize(काष्ठा dma_chan *c)
अणु
	काष्ठा axi_dmac_chan *chan = to_axi_dmac_chan(c);

	vchan_synchronize(&chan->vchan);
पूर्ण

अटल व्योम axi_dmac_issue_pending(काष्ठा dma_chan *c)
अणु
	काष्ठा axi_dmac_chan *chan = to_axi_dmac_chan(c);
	काष्ठा axi_dmac *dmac = chan_to_axi_dmac(chan);
	अचिन्हित दीर्घ flags;

	axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_CTRL, AXI_DMAC_CTRL_ENABLE);

	spin_lock_irqsave(&chan->vchan.lock, flags);
	अगर (vchan_issue_pending(&chan->vchan))
		axi_dmac_start_transfer(chan);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
पूर्ण

अटल काष्ठा axi_dmac_desc *axi_dmac_alloc_desc(अचिन्हित पूर्णांक num_sgs)
अणु
	काष्ठा axi_dmac_desc *desc;
	अचिन्हित पूर्णांक i;

	desc = kzalloc(काष्ठा_size(desc, sg, num_sgs), GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	क्रम (i = 0; i < num_sgs; i++)
		desc->sg[i].id = AXI_DMAC_SG_UNUSED;

	desc->num_sgs = num_sgs;

	वापस desc;
पूर्ण

अटल काष्ठा axi_dmac_sg *axi_dmac_fill_linear_sg(काष्ठा axi_dmac_chan *chan,
	क्रमागत dma_transfer_direction direction, dma_addr_t addr,
	अचिन्हित पूर्णांक num_periods, अचिन्हित पूर्णांक period_len,
	काष्ठा axi_dmac_sg *sg)
अणु
	अचिन्हित पूर्णांक num_segments, i;
	अचिन्हित पूर्णांक segment_size;
	अचिन्हित पूर्णांक len;

	/* Split पूर्णांकo multiple equally sized segments अगर necessary */
	num_segments = DIV_ROUND_UP(period_len, chan->max_length);
	segment_size = DIV_ROUND_UP(period_len, num_segments);
	/* Take care of alignment */
	segment_size = ((segment_size - 1) | chan->length_align_mask) + 1;

	क्रम (i = 0; i < num_periods; i++) अणु
		len = period_len;

		जबतक (len > segment_size) अणु
			अगर (direction == DMA_DEV_TO_MEM)
				sg->dest_addr = addr;
			अन्यथा
				sg->src_addr = addr;
			sg->x_len = segment_size;
			sg->y_len = 1;
			sg++;
			addr += segment_size;
			len -= segment_size;
		पूर्ण

		अगर (direction == DMA_DEV_TO_MEM)
			sg->dest_addr = addr;
		अन्यथा
			sg->src_addr = addr;
		sg->x_len = len;
		sg->y_len = 1;
		sg++;
		addr += len;
	पूर्ण

	वापस sg;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *axi_dmac_prep_slave_sg(
	काष्ठा dma_chan *c, काष्ठा scatterlist *sgl,
	अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
	अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा axi_dmac_chan *chan = to_axi_dmac_chan(c);
	काष्ठा axi_dmac_desc *desc;
	काष्ठा axi_dmac_sg *dsg;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक num_sgs;
	अचिन्हित पूर्णांक i;

	अगर (direction != chan->direction)
		वापस शून्य;

	num_sgs = 0;
	क्रम_each_sg(sgl, sg, sg_len, i)
		num_sgs += DIV_ROUND_UP(sg_dma_len(sg), chan->max_length);

	desc = axi_dmac_alloc_desc(num_sgs);
	अगर (!desc)
		वापस शून्य;

	dsg = desc->sg;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		अगर (!axi_dmac_check_addr(chan, sg_dma_address(sg)) ||
		    !axi_dmac_check_len(chan, sg_dma_len(sg))) अणु
			kमुक्त(desc);
			वापस शून्य;
		पूर्ण

		dsg = axi_dmac_fill_linear_sg(chan, direction, sg_dma_address(sg), 1,
			sg_dma_len(sg), dsg);
	पूर्ण

	desc->cyclic = false;

	वापस vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *axi_dmac_prep_dma_cyclic(
	काष्ठा dma_chan *c, dma_addr_t buf_addr, माप_प्रकार buf_len,
	माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा axi_dmac_chan *chan = to_axi_dmac_chan(c);
	काष्ठा axi_dmac_desc *desc;
	अचिन्हित पूर्णांक num_periods, num_segments;

	अगर (direction != chan->direction)
		वापस शून्य;

	अगर (!axi_dmac_check_len(chan, buf_len) ||
	    !axi_dmac_check_addr(chan, buf_addr))
		वापस शून्य;

	अगर (period_len == 0 || buf_len % period_len)
		वापस शून्य;

	num_periods = buf_len / period_len;
	num_segments = DIV_ROUND_UP(period_len, chan->max_length);

	desc = axi_dmac_alloc_desc(num_periods * num_segments);
	अगर (!desc)
		वापस शून्य;

	axi_dmac_fill_linear_sg(chan, direction, buf_addr, num_periods,
		period_len, desc->sg);

	desc->cyclic = true;

	वापस vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *axi_dmac_prep_पूर्णांकerleaved(
	काष्ठा dma_chan *c, काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा axi_dmac_chan *chan = to_axi_dmac_chan(c);
	काष्ठा axi_dmac_desc *desc;
	माप_प्रकार dst_icg, src_icg;

	अगर (xt->frame_size != 1)
		वापस शून्य;

	अगर (xt->dir != chan->direction)
		वापस शून्य;

	अगर (axi_dmac_src_is_mem(chan)) अणु
		अगर (!xt->src_inc || !axi_dmac_check_addr(chan, xt->src_start))
			वापस शून्य;
	पूर्ण

	अगर (axi_dmac_dest_is_mem(chan)) अणु
		अगर (!xt->dst_inc || !axi_dmac_check_addr(chan, xt->dst_start))
			वापस शून्य;
	पूर्ण

	dst_icg = dmaengine_get_dst_icg(xt, &xt->sgl[0]);
	src_icg = dmaengine_get_src_icg(xt, &xt->sgl[0]);

	अगर (chan->hw_2d) अणु
		अगर (!axi_dmac_check_len(chan, xt->sgl[0].size) ||
		    xt->numf == 0)
			वापस शून्य;
		अगर (xt->sgl[0].size + dst_icg > chan->max_length ||
		    xt->sgl[0].size + src_icg > chan->max_length)
			वापस शून्य;
	पूर्ण अन्यथा अणु
		अगर (dst_icg != 0 || src_icg != 0)
			वापस शून्य;
		अगर (chan->max_length / xt->sgl[0].size < xt->numf)
			वापस शून्य;
		अगर (!axi_dmac_check_len(chan, xt->sgl[0].size * xt->numf))
			वापस शून्य;
	पूर्ण

	desc = axi_dmac_alloc_desc(1);
	अगर (!desc)
		वापस शून्य;

	अगर (axi_dmac_src_is_mem(chan)) अणु
		desc->sg[0].src_addr = xt->src_start;
		desc->sg[0].src_stride = xt->sgl[0].size + src_icg;
	पूर्ण

	अगर (axi_dmac_dest_is_mem(chan)) अणु
		desc->sg[0].dest_addr = xt->dst_start;
		desc->sg[0].dest_stride = xt->sgl[0].size + dst_icg;
	पूर्ण

	अगर (chan->hw_2d) अणु
		desc->sg[0].x_len = xt->sgl[0].size;
		desc->sg[0].y_len = xt->numf;
	पूर्ण अन्यथा अणु
		desc->sg[0].x_len = xt->sgl[0].size * xt->numf;
		desc->sg[0].y_len = 1;
	पूर्ण

	अगर (flags & DMA_CYCLIC)
		desc->cyclic = true;

	वापस vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
पूर्ण

अटल व्योम axi_dmac_मुक्त_chan_resources(काष्ठा dma_chan *c)
अणु
	vchan_मुक्त_chan_resources(to_virt_chan(c));
पूर्ण

अटल व्योम axi_dmac_desc_मुक्त(काष्ठा virt_dma_desc *vdesc)
अणु
	kमुक्त(container_of(vdesc, काष्ठा axi_dmac_desc, vdesc));
पूर्ण

अटल bool axi_dmac_regmap_rdwr(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AXI_DMAC_REG_IRQ_MASK:
	हाल AXI_DMAC_REG_IRQ_SOURCE:
	हाल AXI_DMAC_REG_IRQ_PENDING:
	हाल AXI_DMAC_REG_CTRL:
	हाल AXI_DMAC_REG_TRANSFER_ID:
	हाल AXI_DMAC_REG_START_TRANSFER:
	हाल AXI_DMAC_REG_FLAGS:
	हाल AXI_DMAC_REG_DEST_ADDRESS:
	हाल AXI_DMAC_REG_SRC_ADDRESS:
	हाल AXI_DMAC_REG_X_LENGTH:
	हाल AXI_DMAC_REG_Y_LENGTH:
	हाल AXI_DMAC_REG_DEST_STRIDE:
	हाल AXI_DMAC_REG_SRC_STRIDE:
	हाल AXI_DMAC_REG_TRANSFER_DONE:
	हाल AXI_DMAC_REG_ACTIVE_TRANSFER_ID:
	हाल AXI_DMAC_REG_STATUS:
	हाल AXI_DMAC_REG_CURRENT_SRC_ADDR:
	हाल AXI_DMAC_REG_CURRENT_DEST_ADDR:
	हाल AXI_DMAC_REG_PARTIAL_XFER_LEN:
	हाल AXI_DMAC_REG_PARTIAL_XFER_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config axi_dmac_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = AXI_DMAC_REG_PARTIAL_XFER_ID,
	.पढ़ोable_reg = axi_dmac_regmap_rdwr,
	.ग_लिखोable_reg = axi_dmac_regmap_rdwr,
पूर्ण;

अटल व्योम axi_dmac_adjust_chan_params(काष्ठा axi_dmac_chan *chan)
अणु
	chan->address_align_mask = max(chan->dest_width, chan->src_width) - 1;

	अगर (axi_dmac_dest_is_mem(chan) && axi_dmac_src_is_mem(chan))
		chan->direction = DMA_MEM_TO_MEM;
	अन्यथा अगर (!axi_dmac_dest_is_mem(chan) && axi_dmac_src_is_mem(chan))
		chan->direction = DMA_MEM_TO_DEV;
	अन्यथा अगर (axi_dmac_dest_is_mem(chan) && !axi_dmac_src_is_mem(chan))
		chan->direction = DMA_DEV_TO_MEM;
	अन्यथा
		chan->direction = DMA_DEV_TO_DEV;
पूर्ण

/*
 * The configuration stored in the devicetree matches the configuration
 * parameters of the peripheral instance and allows the driver to know which
 * features are implemented and how it should behave.
 */
अटल पूर्णांक axi_dmac_parse_chan_dt(काष्ठा device_node *of_chan,
	काष्ठा axi_dmac_chan *chan)
अणु
	u32 val;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(of_chan, "reg", &val);
	अगर (ret)
		वापस ret;

	/* We only support 1 channel क्रम now */
	अगर (val != 0)
		वापस -EINVAL;

	ret = of_property_पढ़ो_u32(of_chan, "adi,source-bus-type", &val);
	अगर (ret)
		वापस ret;
	अगर (val > AXI_DMAC_BUS_TYPE_FIFO)
		वापस -EINVAL;
	chan->src_type = val;

	ret = of_property_पढ़ो_u32(of_chan, "adi,destination-bus-type", &val);
	अगर (ret)
		वापस ret;
	अगर (val > AXI_DMAC_BUS_TYPE_FIFO)
		वापस -EINVAL;
	chan->dest_type = val;

	ret = of_property_पढ़ो_u32(of_chan, "adi,source-bus-width", &val);
	अगर (ret)
		वापस ret;
	chan->src_width = val / 8;

	ret = of_property_पढ़ो_u32(of_chan, "adi,destination-bus-width", &val);
	अगर (ret)
		वापस ret;
	chan->dest_width = val / 8;

	axi_dmac_adjust_chan_params(chan);

	वापस 0;
पूर्ण

अटल पूर्णांक axi_dmac_parse_dt(काष्ठा device *dev, काष्ठा axi_dmac *dmac)
अणु
	काष्ठा device_node *of_channels, *of_chan;
	पूर्णांक ret;

	of_channels = of_get_child_by_name(dev->of_node, "adi,channels");
	अगर (of_channels == शून्य)
		वापस -ENODEV;

	क्रम_each_child_of_node(of_channels, of_chan) अणु
		ret = axi_dmac_parse_chan_dt(of_chan, &dmac->chan);
		अगर (ret) अणु
			of_node_put(of_chan);
			of_node_put(of_channels);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	of_node_put(of_channels);

	वापस 0;
पूर्ण

अटल पूर्णांक axi_dmac_पढ़ो_chan_config(काष्ठा device *dev, काष्ठा axi_dmac *dmac)
अणु
	काष्ठा axi_dmac_chan *chan = &dmac->chan;
	अचिन्हित पूर्णांक val, desc;

	desc = axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_INTERFACE_DESC);
	अगर (desc == 0) अणु
		dev_err(dev, "DMA interface register reads zero\n");
		वापस -EFAULT;
	पूर्ण

	val = AXI_DMAC_DMA_SRC_TYPE_GET(desc);
	अगर (val > AXI_DMAC_BUS_TYPE_FIFO) अणु
		dev_err(dev, "Invalid source bus type read: %d\n", val);
		वापस -EINVAL;
	पूर्ण
	chan->src_type = val;

	val = AXI_DMAC_DMA_DST_TYPE_GET(desc);
	अगर (val > AXI_DMAC_BUS_TYPE_FIFO) अणु
		dev_err(dev, "Invalid destination bus type read: %d\n", val);
		वापस -EINVAL;
	पूर्ण
	chan->dest_type = val;

	val = AXI_DMAC_DMA_SRC_WIDTH_GET(desc);
	अगर (val == 0) अणु
		dev_err(dev, "Source bus width is zero\n");
		वापस -EINVAL;
	पूर्ण
	/* widths are stored in log2 */
	chan->src_width = 1 << val;

	val = AXI_DMAC_DMA_DST_WIDTH_GET(desc);
	अगर (val == 0) अणु
		dev_err(dev, "Destination bus width is zero\n");
		वापस -EINVAL;
	पूर्ण
	chan->dest_width = 1 << val;

	axi_dmac_adjust_chan_params(chan);

	वापस 0;
पूर्ण

अटल पूर्णांक axi_dmac_detect_caps(काष्ठा axi_dmac *dmac, अचिन्हित पूर्णांक version)
अणु
	काष्ठा axi_dmac_chan *chan = &dmac->chan;

	axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_FLAGS, AXI_DMAC_FLAG_CYCLIC);
	अगर (axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_FLAGS) == AXI_DMAC_FLAG_CYCLIC)
		chan->hw_cyclic = true;

	axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_Y_LENGTH, 1);
	अगर (axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_Y_LENGTH) == 1)
		chan->hw_2d = true;

	axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_X_LENGTH, 0xffffffff);
	chan->max_length = axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_X_LENGTH);
	अगर (chan->max_length != अच_पूर्णांक_उच्च)
		chan->max_length++;

	axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_DEST_ADDRESS, 0xffffffff);
	अगर (axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_DEST_ADDRESS) == 0 &&
	    chan->dest_type == AXI_DMAC_BUS_TYPE_AXI_MM) अणु
		dev_err(dmac->dma_dev.dev,
			"Destination memory-mapped interface not supported.");
		वापस -ENODEV;
	पूर्ण

	axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_SRC_ADDRESS, 0xffffffff);
	अगर (axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_SRC_ADDRESS) == 0 &&
	    chan->src_type == AXI_DMAC_BUS_TYPE_AXI_MM) अणु
		dev_err(dmac->dma_dev.dev,
			"Source memory-mapped interface not supported.");
		वापस -ENODEV;
	पूर्ण

	अगर (version >= ADI_AXI_PCORE_VER(4, 2, 'a'))
		chan->hw_partial_xfer = true;

	अगर (version >= ADI_AXI_PCORE_VER(4, 1, 'a')) अणु
		axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_X_LENGTH, 0x00);
		chan->length_align_mask =
			axi_dmac_पढ़ो(dmac, AXI_DMAC_REG_X_LENGTH);
	पूर्ण अन्यथा अणु
		chan->length_align_mask = chan->address_align_mask;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axi_dmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dma_device *dma_dev;
	काष्ठा axi_dmac *dmac;
	काष्ठा resource *res;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक version;
	पूर्णांक ret;

	dmac = devm_kzalloc(&pdev->dev, माप(*dmac), GFP_KERNEL);
	अगर (!dmac)
		वापस -ENOMEM;

	dmac->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dmac->irq < 0)
		वापस dmac->irq;
	अगर (dmac->irq == 0)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dmac->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dmac->base))
		वापस PTR_ERR(dmac->base);

	dmac->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dmac->clk))
		वापस PTR_ERR(dmac->clk);

	ret = clk_prepare_enable(dmac->clk);
	अगर (ret < 0)
		वापस ret;

	version = axi_dmac_पढ़ो(dmac, ADI_AXI_REG_VERSION);

	अगर (version >= ADI_AXI_PCORE_VER(4, 3, 'a'))
		ret = axi_dmac_पढ़ो_chan_config(&pdev->dev, dmac);
	अन्यथा
		ret = axi_dmac_parse_dt(&pdev->dev, dmac);

	अगर (ret < 0)
		जाओ err_clk_disable;

	INIT_LIST_HEAD(&dmac->chan.active_descs);

	dma_set_max_seg_size(&pdev->dev, अच_पूर्णांक_उच्च);

	dma_dev = &dmac->dma_dev;
	dma_cap_set(DMA_SLAVE, dma_dev->cap_mask);
	dma_cap_set(DMA_CYCLIC, dma_dev->cap_mask);
	dma_cap_set(DMA_INTERLEAVE, dma_dev->cap_mask);
	dma_dev->device_मुक्त_chan_resources = axi_dmac_मुक्त_chan_resources;
	dma_dev->device_tx_status = dma_cookie_status;
	dma_dev->device_issue_pending = axi_dmac_issue_pending;
	dma_dev->device_prep_slave_sg = axi_dmac_prep_slave_sg;
	dma_dev->device_prep_dma_cyclic = axi_dmac_prep_dma_cyclic;
	dma_dev->device_prep_पूर्णांकerleaved_dma = axi_dmac_prep_पूर्णांकerleaved;
	dma_dev->device_terminate_all = axi_dmac_terminate_all;
	dma_dev->device_synchronize = axi_dmac_synchronize;
	dma_dev->dev = &pdev->dev;
	dma_dev->chancnt = 1;
	dma_dev->src_addr_widths = BIT(dmac->chan.src_width);
	dma_dev->dst_addr_widths = BIT(dmac->chan.dest_width);
	dma_dev->directions = BIT(dmac->chan.direction);
	dma_dev->residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;
	INIT_LIST_HEAD(&dma_dev->channels);

	dmac->chan.vchan.desc_मुक्त = axi_dmac_desc_मुक्त;
	vchan_init(&dmac->chan.vchan, dma_dev);

	ret = axi_dmac_detect_caps(dmac, version);
	अगर (ret)
		जाओ err_clk_disable;

	dma_dev->copy_align = (dmac->chan.address_align_mask + 1);

	axi_dmac_ग_लिखो(dmac, AXI_DMAC_REG_IRQ_MASK, 0x00);

	ret = dma_async_device_रेजिस्टर(dma_dev);
	अगर (ret)
		जाओ err_clk_disable;

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
		of_dma_xlate_by_chan_id, dma_dev);
	अगर (ret)
		जाओ err_unरेजिस्टर_device;

	ret = request_irq(dmac->irq, axi_dmac_पूर्णांकerrupt_handler, IRQF_SHARED,
		dev_name(&pdev->dev), dmac);
	अगर (ret)
		जाओ err_unरेजिस्टर_of;

	platक्रमm_set_drvdata(pdev, dmac);

	regmap = devm_regmap_init_mmio(&pdev->dev, dmac->base,
		 &axi_dmac_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		जाओ err_मुक्त_irq;
	पूर्ण

	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(dmac->irq, dmac);
err_unरेजिस्टर_of:
	of_dma_controller_मुक्त(pdev->dev.of_node);
err_unरेजिस्टर_device:
	dma_async_device_unरेजिस्टर(&dmac->dma_dev);
err_clk_disable:
	clk_disable_unprepare(dmac->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक axi_dmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axi_dmac *dmac = platक्रमm_get_drvdata(pdev);

	of_dma_controller_मुक्त(pdev->dev.of_node);
	मुक्त_irq(dmac->irq, dmac);
	tasklet_समाप्त(&dmac->chan.vchan.task);
	dma_async_device_unरेजिस्टर(&dmac->dma_dev);
	clk_disable_unprepare(dmac->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id axi_dmac_of_match_table[] = अणु
	अणु .compatible = "adi,axi-dmac-1.00.a" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, axi_dmac_of_match_table);

अटल काष्ठा platक्रमm_driver axi_dmac_driver = अणु
	.driver = अणु
		.name = "dma-axi-dmac",
		.of_match_table = axi_dmac_of_match_table,
	पूर्ण,
	.probe = axi_dmac_probe,
	.हटाओ = axi_dmac_हटाओ,
पूर्ण;
module_platक्रमm_driver(axi_dmac_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("DMA controller driver for the AXI-DMAC controller");
MODULE_LICENSE("GPL v2");
