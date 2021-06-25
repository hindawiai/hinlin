<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas USB DMA Controller Driver
 *
 * Copyright (C) 2015 Renesas Electronics Corporation
 *
 * based on rcar-dmac.c
 * Copyright (C) 2014 Renesas Electronics Inc.
 * Author: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "../dmaengine.h"
#समावेश "../virt-dma.h"

/*
 * काष्ठा usb_dmac_sg - Descriptor क्रम a hardware transfer
 * @mem_addr: memory address
 * @size: transfer size in bytes
 */
काष्ठा usb_dmac_sg अणु
	dma_addr_t mem_addr;
	u32 size;
पूर्ण;

/*
 * काष्ठा usb_dmac_desc - USB DMA Transfer Descriptor
 * @vd: base भव channel DMA transaction descriptor
 * @direction: direction of the DMA transfer
 * @sg_allocated_len: length of allocated sg
 * @sg_len: length of sg
 * @sg_index: index of sg
 * @residue: residue after the DMAC completed a transfer
 * @node: node क्रम desc_got and desc_मुक्तd
 * @करोne_cookie: cookie after the DMAC completed a transfer
 * @sg: inक्रमmation क्रम the transfer
 */
काष्ठा usb_dmac_desc अणु
	काष्ठा virt_dma_desc vd;
	क्रमागत dma_transfer_direction direction;
	अचिन्हित पूर्णांक sg_allocated_len;
	अचिन्हित पूर्णांक sg_len;
	अचिन्हित पूर्णांक sg_index;
	u32 residue;
	काष्ठा list_head node;
	dma_cookie_t करोne_cookie;
	काष्ठा usb_dmac_sg sg[];
पूर्ण;

#घोषणा to_usb_dmac_desc(vd)	container_of(vd, काष्ठा usb_dmac_desc, vd)

/*
 * काष्ठा usb_dmac_chan - USB DMA Controller Channel
 * @vc: base भव DMA channel object
 * @iomem: channel I/O memory base
 * @index: index of this channel in the controller
 * @irq: irq number of this channel
 * @desc: the current descriptor
 * @descs_allocated: number of descriptors allocated
 * @desc_got: got descriptors
 * @desc_मुक्तd: मुक्तd descriptors after the DMAC completed a transfer
 */
काष्ठा usb_dmac_chan अणु
	काष्ठा virt_dma_chan vc;
	व्योम __iomem *iomem;
	अचिन्हित पूर्णांक index;
	पूर्णांक irq;
	काष्ठा usb_dmac_desc *desc;
	पूर्णांक descs_allocated;
	काष्ठा list_head desc_got;
	काष्ठा list_head desc_मुक्तd;
पूर्ण;

#घोषणा to_usb_dmac_chan(c) container_of(c, काष्ठा usb_dmac_chan, vc.chan)

/*
 * काष्ठा usb_dmac - USB DMA Controller
 * @engine: base DMA engine object
 * @dev: the hardware device
 * @iomem: remapped I/O memory base
 * @n_channels: number of available channels
 * @channels: array of DMAC channels
 */
काष्ठा usb_dmac अणु
	काष्ठा dma_device engine;
	काष्ठा device *dev;
	व्योम __iomem *iomem;

	अचिन्हित पूर्णांक n_channels;
	काष्ठा usb_dmac_chan *channels;
पूर्ण;

#घोषणा to_usb_dmac(d)		container_of(d, काष्ठा usb_dmac, engine)

/* -----------------------------------------------------------------------------
 * Registers
 */

#घोषणा USB_DMAC_CHAN_OFFSET(i)		(0x20 + 0x20 * (i))

#घोषणा USB_DMASWR			0x0008
#घोषणा USB_DMASWR_SWR			(1 << 0)
#घोषणा USB_DMAOR			0x0060
#घोषणा USB_DMAOR_AE			(1 << 1)
#घोषणा USB_DMAOR_DME			(1 << 0)

#घोषणा USB_DMASAR			0x0000
#घोषणा USB_DMADAR			0x0004
#घोषणा USB_DMATCR			0x0008
#घोषणा USB_DMATCR_MASK			0x00ffffff
#घोषणा USB_DMACHCR			0x0014
#घोषणा USB_DMACHCR_FTE			(1 << 24)
#घोषणा USB_DMACHCR_शून्यE		(1 << 16)
#घोषणा USB_DMACHCR_शून्य		(1 << 12)
#घोषणा USB_DMACHCR_TS_8B		((0 << 7) | (0 << 6))
#घोषणा USB_DMACHCR_TS_16B		((0 << 7) | (1 << 6))
#घोषणा USB_DMACHCR_TS_32B		((1 << 7) | (0 << 6))
#घोषणा USB_DMACHCR_IE			(1 << 5)
#घोषणा USB_DMACHCR_SP			(1 << 2)
#घोषणा USB_DMACHCR_TE			(1 << 1)
#घोषणा USB_DMACHCR_DE			(1 << 0)
#घोषणा USB_DMATEND			0x0018

/* Hardcode the xfer_shअगरt to 5 (32bytes) */
#घोषणा USB_DMAC_XFER_SHIFT	5
#घोषणा USB_DMAC_XFER_SIZE	(1 << USB_DMAC_XFER_SHIFT)
#घोषणा USB_DMAC_CHCR_TS	USB_DMACHCR_TS_32B
#घोषणा USB_DMAC_SLAVE_BUSWIDTH	DMA_SLAVE_BUSWIDTH_32_BYTES

/* क्रम descriptors */
#घोषणा USB_DMAC_INITIAL_NR_DESC	16
#घोषणा USB_DMAC_INITIAL_NR_SG		8

/* -----------------------------------------------------------------------------
 * Device access
 */

अटल व्योम usb_dmac_ग_लिखो(काष्ठा usb_dmac *dmac, u32 reg, u32 data)
अणु
	ग_लिखोl(data, dmac->iomem + reg);
पूर्ण

अटल u32 usb_dmac_पढ़ो(काष्ठा usb_dmac *dmac, u32 reg)
अणु
	वापस पढ़ोl(dmac->iomem + reg);
पूर्ण

अटल u32 usb_dmac_chan_पढ़ो(काष्ठा usb_dmac_chan *chan, u32 reg)
अणु
	वापस पढ़ोl(chan->iomem + reg);
पूर्ण

अटल व्योम usb_dmac_chan_ग_लिखो(काष्ठा usb_dmac_chan *chan, u32 reg, u32 data)
अणु
	ग_लिखोl(data, chan->iomem + reg);
पूर्ण

/* -----------------------------------------------------------------------------
 * Initialization and configuration
 */

अटल bool usb_dmac_chan_is_busy(काष्ठा usb_dmac_chan *chan)
अणु
	u32 chcr = usb_dmac_chan_पढ़ो(chan, USB_DMACHCR);

	वापस (chcr & (USB_DMACHCR_DE | USB_DMACHCR_TE)) == USB_DMACHCR_DE;
पूर्ण

अटल u32 usb_dmac_calc_tend(u32 size)
अणु
	/*
	 * Please refer to the Figure "Example of Final Transaction Valid
	 * Data Transfer Enable (EDTEN) Setting" in the data sheet.
	 */
	वापस 0xffffffff << (32 - (size % USB_DMAC_XFER_SIZE ?	:
						USB_DMAC_XFER_SIZE));
पूर्ण

/* This function is alपढ़ोy held by vc.lock */
अटल व्योम usb_dmac_chan_start_sg(काष्ठा usb_dmac_chan *chan,
				   अचिन्हित पूर्णांक index)
अणु
	काष्ठा usb_dmac_desc *desc = chan->desc;
	काष्ठा usb_dmac_sg *sg = desc->sg + index;
	dma_addr_t src_addr = 0, dst_addr = 0;

	WARN_ON_ONCE(usb_dmac_chan_is_busy(chan));

	अगर (desc->direction == DMA_DEV_TO_MEM)
		dst_addr = sg->mem_addr;
	अन्यथा
		src_addr = sg->mem_addr;

	dev_dbg(chan->vc.chan.device->dev,
		"chan%u: queue sg %p: %u@%pad -> %pad\n",
		chan->index, sg, sg->size, &src_addr, &dst_addr);

	usb_dmac_chan_ग_लिखो(chan, USB_DMASAR, src_addr & 0xffffffff);
	usb_dmac_chan_ग_लिखो(chan, USB_DMADAR, dst_addr & 0xffffffff);
	usb_dmac_chan_ग_लिखो(chan, USB_DMATCR,
			    DIV_ROUND_UP(sg->size, USB_DMAC_XFER_SIZE));
	usb_dmac_chan_ग_लिखो(chan, USB_DMATEND, usb_dmac_calc_tend(sg->size));

	usb_dmac_chan_ग_लिखो(chan, USB_DMACHCR, USB_DMAC_CHCR_TS |
			USB_DMACHCR_शून्यE | USB_DMACHCR_IE | USB_DMACHCR_DE);
पूर्ण

/* This function is alपढ़ोy held by vc.lock */
अटल व्योम usb_dmac_chan_start_desc(काष्ठा usb_dmac_chan *chan)
अणु
	काष्ठा virt_dma_desc *vd;

	vd = vchan_next_desc(&chan->vc);
	अगर (!vd) अणु
		chan->desc = शून्य;
		वापस;
	पूर्ण

	/*
	 * Remove this request from vc->desc_issued. Otherwise, this driver
	 * will get the previous value from vchan_next_desc() after a transfer
	 * was completed.
	 */
	list_del(&vd->node);

	chan->desc = to_usb_dmac_desc(vd);
	chan->desc->sg_index = 0;
	usb_dmac_chan_start_sg(chan, 0);
पूर्ण

अटल पूर्णांक usb_dmac_init(काष्ठा usb_dmac *dmac)
अणु
	u16 dmaor;

	/* Clear all channels and enable the DMAC globally. */
	usb_dmac_ग_लिखो(dmac, USB_DMAOR, USB_DMAOR_DME);

	dmaor = usb_dmac_पढ़ो(dmac, USB_DMAOR);
	अगर ((dmaor & (USB_DMAOR_AE | USB_DMAOR_DME)) != USB_DMAOR_DME) अणु
		dev_warn(dmac->dev, "DMAOR initialization failed.\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Descriptors allocation and मुक्त
 */
अटल पूर्णांक usb_dmac_desc_alloc(काष्ठा usb_dmac_chan *chan, अचिन्हित पूर्णांक sg_len,
			       gfp_t gfp)
अणु
	काष्ठा usb_dmac_desc *desc;
	अचिन्हित दीर्घ flags;

	desc = kzalloc(काष्ठा_size(desc, sg, sg_len), gfp);
	अगर (!desc)
		वापस -ENOMEM;

	desc->sg_allocated_len = sg_len;
	INIT_LIST_HEAD(&desc->node);

	spin_lock_irqsave(&chan->vc.lock, flags);
	list_add_tail(&desc->node, &chan->desc_मुक्तd);
	spin_unlock_irqrestore(&chan->vc.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम usb_dmac_desc_मुक्त(काष्ठा usb_dmac_chan *chan)
अणु
	काष्ठा usb_dmac_desc *desc, *_desc;
	LIST_HEAD(list);

	list_splice_init(&chan->desc_मुक्तd, &list);
	list_splice_init(&chan->desc_got, &list);

	list_क्रम_each_entry_safe(desc, _desc, &list, node) अणु
		list_del(&desc->node);
		kमुक्त(desc);
	पूर्ण
	chan->descs_allocated = 0;
पूर्ण

अटल काष्ठा usb_dmac_desc *usb_dmac_desc_get(काष्ठा usb_dmac_chan *chan,
					       अचिन्हित पूर्णांक sg_len, gfp_t gfp)
अणु
	काष्ठा usb_dmac_desc *desc = शून्य;
	अचिन्हित दीर्घ flags;

	/* Get a मुक्तd descritpor */
	spin_lock_irqsave(&chan->vc.lock, flags);
	list_क्रम_each_entry(desc, &chan->desc_मुक्तd, node) अणु
		अगर (sg_len <= desc->sg_allocated_len) अणु
			list_move_tail(&desc->node, &chan->desc_got);
			spin_unlock_irqrestore(&chan->vc.lock, flags);
			वापस desc;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&chan->vc.lock, flags);

	/* Allocate a new descriptor */
	अगर (!usb_dmac_desc_alloc(chan, sg_len, gfp)) अणु
		/* If allocated the desc, it was added to tail of the list */
		spin_lock_irqsave(&chan->vc.lock, flags);
		desc = list_last_entry(&chan->desc_मुक्तd, काष्ठा usb_dmac_desc,
				       node);
		list_move_tail(&desc->node, &chan->desc_got);
		spin_unlock_irqrestore(&chan->vc.lock, flags);
		वापस desc;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम usb_dmac_desc_put(काष्ठा usb_dmac_chan *chan,
			      काष्ठा usb_dmac_desc *desc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->vc.lock, flags);
	list_move_tail(&desc->node, &chan->desc_मुक्तd);
	spin_unlock_irqrestore(&chan->vc.lock, flags);
पूर्ण

/* -----------------------------------------------------------------------------
 * Stop and reset
 */

अटल व्योम usb_dmac_soft_reset(काष्ठा usb_dmac_chan *uchan)
अणु
	काष्ठा dma_chan *chan = &uchan->vc.chan;
	काष्ठा usb_dmac *dmac = to_usb_dmac(chan->device);
	पूर्णांक i;

	/* Don't issue soft reset अगर any one of channels is busy */
	क्रम (i = 0; i < dmac->n_channels; ++i) अणु
		अगर (usb_dmac_chan_is_busy(uchan))
			वापस;
	पूर्ण

	usb_dmac_ग_लिखो(dmac, USB_DMAOR, 0);
	usb_dmac_ग_लिखो(dmac, USB_DMASWR, USB_DMASWR_SWR);
	udelay(100);
	usb_dmac_ग_लिखो(dmac, USB_DMASWR, 0);
	usb_dmac_ग_लिखो(dmac, USB_DMAOR, 1);
पूर्ण

अटल व्योम usb_dmac_chan_halt(काष्ठा usb_dmac_chan *chan)
अणु
	u32 chcr = usb_dmac_chan_पढ़ो(chan, USB_DMACHCR);

	chcr &= ~(USB_DMACHCR_IE | USB_DMACHCR_TE | USB_DMACHCR_DE);
	usb_dmac_chan_ग_लिखो(chan, USB_DMACHCR, chcr);

	usb_dmac_soft_reset(chan);
पूर्ण

अटल व्योम usb_dmac_stop(काष्ठा usb_dmac *dmac)
अणु
	usb_dmac_ग_लिखो(dmac, USB_DMAOR, 0);
पूर्ण

/* -----------------------------------------------------------------------------
 * DMA engine operations
 */

अटल पूर्णांक usb_dmac_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	पूर्णांक ret;

	जबतक (uchan->descs_allocated < USB_DMAC_INITIAL_NR_DESC) अणु
		ret = usb_dmac_desc_alloc(uchan, USB_DMAC_INITIAL_NR_SG,
					  GFP_KERNEL);
		अगर (ret < 0) अणु
			usb_dmac_desc_मुक्त(uchan);
			वापस ret;
		पूर्ण
		uchan->descs_allocated++;
	पूर्ण

	वापस pm_runसमय_get_sync(chan->device->dev);
पूर्ण

अटल व्योम usb_dmac_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	अचिन्हित दीर्घ flags;

	/* Protect against ISR */
	spin_lock_irqsave(&uchan->vc.lock, flags);
	usb_dmac_chan_halt(uchan);
	spin_unlock_irqrestore(&uchan->vc.lock, flags);

	usb_dmac_desc_मुक्त(uchan);
	vchan_मुक्त_chan_resources(&uchan->vc);

	pm_runसमय_put(chan->device->dev);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
usb_dmac_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		       अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction dir,
		       अचिन्हित दीर्घ dma_flags, व्योम *context)
अणु
	काष्ठा usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	काष्ठा usb_dmac_desc *desc;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	अगर (!sg_len) अणु
		dev_warn(chan->device->dev,
			 "%s: bad parameter: len=%d\n", __func__, sg_len);
		वापस शून्य;
	पूर्ण

	desc = usb_dmac_desc_get(uchan, sg_len, GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	desc->direction = dir;
	desc->sg_len = sg_len;
	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		desc->sg[i].mem_addr = sg_dma_address(sg);
		desc->sg[i].size = sg_dma_len(sg);
	पूर्ण

	वापस vchan_tx_prep(&uchan->vc, &desc->vd, dma_flags);
पूर्ण

अटल पूर्णांक usb_dmac_chan_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	काष्ठा usb_dmac_desc *desc, *_desc;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);
	LIST_HEAD(list);

	spin_lock_irqsave(&uchan->vc.lock, flags);
	usb_dmac_chan_halt(uchan);
	vchan_get_all_descriptors(&uchan->vc, &head);
	अगर (uchan->desc)
		uchan->desc = शून्य;
	list_splice_init(&uchan->desc_got, &list);
	list_क्रम_each_entry_safe(desc, _desc, &list, node)
		list_move_tail(&desc->node, &uchan->desc_मुक्तd);
	spin_unlock_irqrestore(&uchan->vc.lock, flags);
	vchan_dma_desc_मुक्त_list(&uchan->vc, &head);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक usb_dmac_get_current_residue(काष्ठा usb_dmac_chan *chan,
						 काष्ठा usb_dmac_desc *desc,
						 पूर्णांक sg_index)
अणु
	काष्ठा usb_dmac_sg *sg = desc->sg + sg_index;
	u32 mem_addr = sg->mem_addr & 0xffffffff;
	अचिन्हित पूर्णांक residue = sg->size;

	/*
	 * We cannot use USB_DMATCR to calculate residue because USB_DMATCR
	 * has unsuited value to calculate.
	 */
	अगर (desc->direction == DMA_DEV_TO_MEM)
		residue -= usb_dmac_chan_पढ़ो(chan, USB_DMADAR) - mem_addr;
	अन्यथा
		residue -= usb_dmac_chan_पढ़ो(chan, USB_DMASAR) - mem_addr;

	वापस residue;
पूर्ण

अटल u32 usb_dmac_chan_get_residue_अगर_complete(काष्ठा usb_dmac_chan *chan,
						 dma_cookie_t cookie)
अणु
	काष्ठा usb_dmac_desc *desc;
	u32 residue = 0;

	list_क्रम_each_entry_reverse(desc, &chan->desc_मुक्तd, node) अणु
		अगर (desc->करोne_cookie == cookie) अणु
			residue = desc->residue;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस residue;
पूर्ण

अटल u32 usb_dmac_chan_get_residue(काष्ठा usb_dmac_chan *chan,
				     dma_cookie_t cookie)
अणु
	u32 residue = 0;
	काष्ठा virt_dma_desc *vd;
	काष्ठा usb_dmac_desc *desc = chan->desc;
	पूर्णांक i;

	अगर (!desc) अणु
		vd = vchan_find_desc(&chan->vc, cookie);
		अगर (!vd)
			वापस 0;
		desc = to_usb_dmac_desc(vd);
	पूर्ण

	/* Compute the size of all usb_dmac_sg still to be transferred */
	क्रम (i = desc->sg_index + 1; i < desc->sg_len; i++)
		residue += desc->sg[i].size;

	/* Add the residue क्रम the current sg */
	residue += usb_dmac_get_current_residue(chan, desc, desc->sg_index);

	वापस residue;
पूर्ण

अटल क्रमागत dma_status usb_dmac_tx_status(काष्ठा dma_chan *chan,
					  dma_cookie_t cookie,
					  काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	क्रमागत dma_status status;
	अचिन्हित पूर्णांक residue = 0;
	अचिन्हित दीर्घ flags;

	status = dma_cookie_status(chan, cookie, txstate);
	/* a client driver will get residue after DMA_COMPLETE */
	अगर (!txstate)
		वापस status;

	spin_lock_irqsave(&uchan->vc.lock, flags);
	अगर (status == DMA_COMPLETE)
		residue = usb_dmac_chan_get_residue_अगर_complete(uchan, cookie);
	अन्यथा
		residue = usb_dmac_chan_get_residue(uchan, cookie);
	spin_unlock_irqrestore(&uchan->vc.lock, flags);

	dma_set_residue(txstate, residue);

	वापस status;
पूर्ण

अटल व्योम usb_dmac_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&uchan->vc.lock, flags);
	अगर (vchan_issue_pending(&uchan->vc) && !uchan->desc)
		usb_dmac_chan_start_desc(uchan);
	spin_unlock_irqrestore(&uchan->vc.lock, flags);
पूर्ण

अटल व्योम usb_dmac_virt_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा usb_dmac_desc *desc = to_usb_dmac_desc(vd);
	काष्ठा usb_dmac_chan *chan = to_usb_dmac_chan(vd->tx.chan);

	usb_dmac_desc_put(chan, desc);
पूर्ण

/* -----------------------------------------------------------------------------
 * IRQ handling
 */

अटल व्योम usb_dmac_isr_transfer_end(काष्ठा usb_dmac_chan *chan)
अणु
	काष्ठा usb_dmac_desc *desc = chan->desc;

	BUG_ON(!desc);

	अगर (++desc->sg_index < desc->sg_len) अणु
		usb_dmac_chan_start_sg(chan, desc->sg_index);
	पूर्ण अन्यथा अणु
		desc->residue = usb_dmac_get_current_residue(chan, desc,
							desc->sg_index - 1);
		desc->करोne_cookie = desc->vd.tx.cookie;
		desc->vd.tx_result.result = DMA_TRANS_NOERROR;
		desc->vd.tx_result.residue = desc->residue;
		vchan_cookie_complete(&desc->vd);

		/* Restart the next transfer अगर this driver has a next desc */
		usb_dmac_chan_start_desc(chan);
	पूर्ण
पूर्ण

अटल irqवापस_t usb_dmac_isr_channel(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा usb_dmac_chan *chan = dev;
	irqवापस_t ret = IRQ_NONE;
	u32 mask = 0;
	u32 chcr;
	bool xfer_end = false;

	spin_lock(&chan->vc.lock);

	chcr = usb_dmac_chan_पढ़ो(chan, USB_DMACHCR);
	अगर (chcr & (USB_DMACHCR_TE | USB_DMACHCR_SP)) अणु
		mask |= USB_DMACHCR_DE | USB_DMACHCR_TE | USB_DMACHCR_SP;
		अगर (chcr & USB_DMACHCR_DE)
			xfer_end = true;
		ret |= IRQ_HANDLED;
	पूर्ण
	अगर (chcr & USB_DMACHCR_शून्य) अणु
		/* An पूर्णांकerruption of TE will happen after we set FTE */
		mask |= USB_DMACHCR_शून्य;
		chcr |= USB_DMACHCR_FTE;
		ret |= IRQ_HANDLED;
	पूर्ण
	अगर (mask)
		usb_dmac_chan_ग_लिखो(chan, USB_DMACHCR, chcr & ~mask);

	अगर (xfer_end)
		usb_dmac_isr_transfer_end(chan);

	spin_unlock(&chan->vc.lock);

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * OF xlate and channel filter
 */

अटल bool usb_dmac_chan_filter(काष्ठा dma_chan *chan, व्योम *arg)
अणु
	काष्ठा usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	काष्ठा of_phandle_args *dma_spec = arg;

	/* USB-DMAC should be used with fixed usb controller's FIFO */
	अगर (uchan->index != dma_spec->args[0])
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा dma_chan *usb_dmac_of_xlate(काष्ठा of_phandle_args *dma_spec,
					  काष्ठा of_dma *ofdma)
अणु
	काष्ठा dma_chan *chan;
	dma_cap_mask_t mask;

	अगर (dma_spec->args_count != 1)
		वापस शून्य;

	/* Only slave DMA channels can be allocated via DT */
	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	chan = __dma_request_channel(&mask, usb_dmac_chan_filter, dma_spec,
				     ofdma->of_node);
	अगर (!chan)
		वापस शून्य;

	वापस chan;
पूर्ण

/* -----------------------------------------------------------------------------
 * Power management
 */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक usb_dmac_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_dmac *dmac = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < dmac->n_channels; ++i) अणु
		अगर (!dmac->channels[i].iomem)
			अवरोध;
		usb_dmac_chan_halt(&dmac->channels[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usb_dmac_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_dmac *dmac = dev_get_drvdata(dev);

	वापस usb_dmac_init(dmac);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops usb_dmac_pm = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				      pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(usb_dmac_runसमय_suspend, usb_dmac_runसमय_resume,
			   शून्य)
पूर्ण;

/* -----------------------------------------------------------------------------
 * Probe and हटाओ
 */

अटल पूर्णांक usb_dmac_chan_probe(काष्ठा usb_dmac *dmac,
			       काष्ठा usb_dmac_chan *uchan,
			       अचिन्हित पूर्णांक index)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dmac->dev);
	अक्षर pdev_irqname[5];
	अक्षर *irqname;
	पूर्णांक ret;

	uchan->index = index;
	uchan->iomem = dmac->iomem + USB_DMAC_CHAN_OFFSET(index);

	/* Request the channel पूर्णांकerrupt. */
	प्र_लिखो(pdev_irqname, "ch%u", index);
	uchan->irq = platक्रमm_get_irq_byname(pdev, pdev_irqname);
	अगर (uchan->irq < 0)
		वापस -ENODEV;

	irqname = devm_kaप्र_लिखो(dmac->dev, GFP_KERNEL, "%s:%u",
				 dev_name(dmac->dev), index);
	अगर (!irqname)
		वापस -ENOMEM;

	ret = devm_request_irq(dmac->dev, uchan->irq, usb_dmac_isr_channel,
			       IRQF_SHARED, irqname, uchan);
	अगर (ret) अणु
		dev_err(dmac->dev, "failed to request IRQ %u (%d)\n",
			uchan->irq, ret);
		वापस ret;
	पूर्ण

	uchan->vc.desc_मुक्त = usb_dmac_virt_desc_मुक्त;
	vchan_init(&uchan->vc, &dmac->engine);
	INIT_LIST_HEAD(&uchan->desc_मुक्तd);
	INIT_LIST_HEAD(&uchan->desc_got);

	वापस 0;
पूर्ण

अटल पूर्णांक usb_dmac_parse_of(काष्ठा device *dev, काष्ठा usb_dmac *dmac)
अणु
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "dma-channels", &dmac->n_channels);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to read dma-channels property\n");
		वापस ret;
	पूर्ण

	अगर (dmac->n_channels <= 0 || dmac->n_channels >= 100) अणु
		dev_err(dev, "invalid number of channels %u\n",
			dmac->n_channels);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usb_dmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर क्रमागत dma_slave_buswidth widths = USB_DMAC_SLAVE_BUSWIDTH;
	काष्ठा dma_device *engine;
	काष्ठा usb_dmac *dmac;
	काष्ठा resource *mem;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	dmac = devm_kzalloc(&pdev->dev, माप(*dmac), GFP_KERNEL);
	अगर (!dmac)
		वापस -ENOMEM;

	dmac->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, dmac);

	ret = usb_dmac_parse_of(&pdev->dev, dmac);
	अगर (ret < 0)
		वापस ret;

	dmac->channels = devm_kसुस्मृति(&pdev->dev, dmac->n_channels,
				      माप(*dmac->channels), GFP_KERNEL);
	अगर (!dmac->channels)
		वापस -ENOMEM;

	/* Request resources. */
	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dmac->iomem = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(dmac->iomem))
		वापस PTR_ERR(dmac->iomem);

	/* Enable runसमय PM and initialize the device. */
	pm_runसमय_enable(&pdev->dev);
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "runtime PM get sync failed (%d)\n", ret);
		जाओ error_pm;
	पूर्ण

	ret = usb_dmac_init(dmac);

	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to reset device\n");
		जाओ error;
	पूर्ण

	/* Initialize the channels. */
	INIT_LIST_HEAD(&dmac->engine.channels);

	क्रम (i = 0; i < dmac->n_channels; ++i) अणु
		ret = usb_dmac_chan_probe(dmac, &dmac->channels[i], i);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	/* Register the DMAC as a DMA provider क्रम DT. */
	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node, usb_dmac_of_xlate,
					 शून्य);
	अगर (ret < 0)
		जाओ error;

	/*
	 * Register the DMA engine device.
	 *
	 * Default transfer size of 32 bytes requires 32-byte alignment.
	 */
	engine = &dmac->engine;
	dma_cap_set(DMA_SLAVE, engine->cap_mask);

	engine->dev = &pdev->dev;

	engine->src_addr_widths = widths;
	engine->dst_addr_widths = widths;
	engine->directions = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	engine->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

	engine->device_alloc_chan_resources = usb_dmac_alloc_chan_resources;
	engine->device_मुक्त_chan_resources = usb_dmac_मुक्त_chan_resources;
	engine->device_prep_slave_sg = usb_dmac_prep_slave_sg;
	engine->device_terminate_all = usb_dmac_chan_terminate_all;
	engine->device_tx_status = usb_dmac_tx_status;
	engine->device_issue_pending = usb_dmac_issue_pending;

	ret = dma_async_device_रेजिस्टर(engine);
	अगर (ret < 0)
		जाओ error;

	pm_runसमय_put(&pdev->dev);
	वापस 0;

error:
	of_dma_controller_मुक्त(pdev->dev.of_node);
	pm_runसमय_put(&pdev->dev);
error_pm:
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल व्योम usb_dmac_chan_हटाओ(काष्ठा usb_dmac *dmac,
				 काष्ठा usb_dmac_chan *uchan)
अणु
	usb_dmac_chan_halt(uchan);
	devm_मुक्त_irq(dmac->dev, uchan->irq, uchan);
पूर्ण

अटल पूर्णांक usb_dmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_dmac *dmac = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < dmac->n_channels; ++i)
		usb_dmac_chan_हटाओ(dmac, &dmac->channels[i]);
	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&dmac->engine);

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम usb_dmac_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_dmac *dmac = platक्रमm_get_drvdata(pdev);

	usb_dmac_stop(dmac);
पूर्ण

अटल स्थिर काष्ठा of_device_id usb_dmac_of_ids[] = अणु
	अणु .compatible = "renesas,usb-dmac", पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, usb_dmac_of_ids);

अटल काष्ठा platक्रमm_driver usb_dmac_driver = अणु
	.driver		= अणु
		.pm	= &usb_dmac_pm,
		.name	= "usb-dmac",
		.of_match_table = usb_dmac_of_ids,
	पूर्ण,
	.probe		= usb_dmac_probe,
	.हटाओ		= usb_dmac_हटाओ,
	.shutकरोwn	= usb_dmac_shutकरोwn,
पूर्ण;

module_platक्रमm_driver(usb_dmac_driver);

MODULE_DESCRIPTION("Renesas USB DMA Controller Driver");
MODULE_AUTHOR("Yoshihiro Shimoda <yoshihiro.shimoda.uh@renesas.com>");
MODULE_LICENSE("GPL v2");
