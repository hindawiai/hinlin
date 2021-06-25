<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MUSB OTG driver - support क्रम Mentor's DMA controller
 *
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2007 by Texas Instruments
 */
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश "musb_core.h"
#समावेश "musb_dma.h"

#घोषणा MUSB_HSDMA_CHANNEL_OFFSET(_bchannel, _offset)		\
		(MUSB_HSDMA_BASE + (_bchannel << 4) + _offset)

#घोषणा musb_पढ़ो_hsdma_addr(mbase, bchannel)	\
	musb_पढ़ोl(mbase,	\
		   MUSB_HSDMA_CHANNEL_OFFSET(bchannel, MUSB_HSDMA_ADDRESS))

#घोषणा musb_ग_लिखो_hsdma_addr(mbase, bchannel, addr) \
	musb_ग_लिखोl(mbase, \
		    MUSB_HSDMA_CHANNEL_OFFSET(bchannel, MUSB_HSDMA_ADDRESS), \
		    addr)

#घोषणा musb_पढ़ो_hsdma_count(mbase, bchannel)	\
	musb_पढ़ोl(mbase,	\
		   MUSB_HSDMA_CHANNEL_OFFSET(bchannel, MUSB_HSDMA_COUNT))

#घोषणा musb_ग_लिखो_hsdma_count(mbase, bchannel, len) \
	musb_ग_लिखोl(mbase, \
		    MUSB_HSDMA_CHANNEL_OFFSET(bchannel, MUSB_HSDMA_COUNT), \
		    len)
/* control रेजिस्टर (16-bit): */
#घोषणा MUSB_HSDMA_ENABLE_SHIFT		0
#घोषणा MUSB_HSDMA_TRANSMIT_SHIFT	1
#घोषणा MUSB_HSDMA_MODE1_SHIFT		2
#घोषणा MUSB_HSDMA_IRQENABLE_SHIFT	3
#घोषणा MUSB_HSDMA_ENDPOINT_SHIFT	4
#घोषणा MUSB_HSDMA_BUSERROR_SHIFT	8
#घोषणा MUSB_HSDMA_BURSTMODE_SHIFT	9
#घोषणा MUSB_HSDMA_BURSTMODE		(3 << MUSB_HSDMA_BURSTMODE_SHIFT)
#घोषणा MUSB_HSDMA_BURSTMODE_UNSPEC	0
#घोषणा MUSB_HSDMA_BURSTMODE_INCR4	1
#घोषणा MUSB_HSDMA_BURSTMODE_INCR8	2
#घोषणा MUSB_HSDMA_BURSTMODE_INCR16	3

#घोषणा MUSB_HSDMA_CHANNELS		8

काष्ठा musb_dma_controller;

काष्ठा musb_dma_channel अणु
	काष्ठा dma_channel		channel;
	काष्ठा musb_dma_controller	*controller;
	u32				start_addr;
	u32				len;
	u16				max_packet_sz;
	u8				idx;
	u8				epnum;
	u8				transmit;
पूर्ण;

काष्ठा musb_dma_controller अणु
	काष्ठा dma_controller		controller;
	काष्ठा musb_dma_channel		channel[MUSB_HSDMA_CHANNELS];
	व्योम				*निजी_data;
	व्योम __iomem			*base;
	u8				channel_count;
	u8				used_channels;
	पूर्णांक				irq;
पूर्ण;

अटल व्योम dma_channel_release(काष्ठा dma_channel *channel);

अटल व्योम dma_controller_stop(काष्ठा musb_dma_controller *controller)
अणु
	काष्ठा musb *musb = controller->निजी_data;
	काष्ठा dma_channel *channel;
	u8 bit;

	अगर (controller->used_channels != 0) अणु
		dev_err(musb->controller,
			"Stopping DMA controller while channel active\n");

		क्रम (bit = 0; bit < MUSB_HSDMA_CHANNELS; bit++) अणु
			अगर (controller->used_channels & (1 << bit)) अणु
				channel = &controller->channel[bit].channel;
				dma_channel_release(channel);

				अगर (!controller->used_channels)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा dma_channel *dma_channel_allocate(काष्ठा dma_controller *c,
				काष्ठा musb_hw_ep *hw_ep, u8 transmit)
अणु
	काष्ठा musb_dma_controller *controller = container_of(c,
			काष्ठा musb_dma_controller, controller);
	काष्ठा musb_dma_channel *musb_channel = शून्य;
	काष्ठा dma_channel *channel = शून्य;
	u8 bit;

	क्रम (bit = 0; bit < MUSB_HSDMA_CHANNELS; bit++) अणु
		अगर (!(controller->used_channels & (1 << bit))) अणु
			controller->used_channels |= (1 << bit);
			musb_channel = &(controller->channel[bit]);
			musb_channel->controller = controller;
			musb_channel->idx = bit;
			musb_channel->epnum = hw_ep->epnum;
			musb_channel->transmit = transmit;
			channel = &(musb_channel->channel);
			channel->निजी_data = musb_channel;
			channel->status = MUSB_DMA_STATUS_FREE;
			channel->max_len = 0x100000;
			/* Tx => mode 1; Rx => mode 0 */
			channel->desired_mode = transmit;
			channel->actual_len = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस channel;
पूर्ण

अटल व्योम dma_channel_release(काष्ठा dma_channel *channel)
अणु
	काष्ठा musb_dma_channel *musb_channel = channel->निजी_data;

	channel->actual_len = 0;
	musb_channel->start_addr = 0;
	musb_channel->len = 0;

	musb_channel->controller->used_channels &=
		~(1 << musb_channel->idx);

	channel->status = MUSB_DMA_STATUS_UNKNOWN;
पूर्ण

अटल व्योम configure_channel(काष्ठा dma_channel *channel,
				u16 packet_sz, u8 mode,
				dma_addr_t dma_addr, u32 len)
अणु
	काष्ठा musb_dma_channel *musb_channel = channel->निजी_data;
	काष्ठा musb_dma_controller *controller = musb_channel->controller;
	काष्ठा musb *musb = controller->निजी_data;
	व्योम __iomem *mbase = controller->base;
	u8 bchannel = musb_channel->idx;
	u16 csr = 0;

	musb_dbg(musb, "%p, pkt_sz %d, addr %pad, len %d, mode %d",
			channel, packet_sz, &dma_addr, len, mode);

	अगर (mode) अणु
		csr |= 1 << MUSB_HSDMA_MODE1_SHIFT;
		BUG_ON(len < packet_sz);
	पूर्ण
	csr |= MUSB_HSDMA_BURSTMODE_INCR16
				<< MUSB_HSDMA_BURSTMODE_SHIFT;

	csr |= (musb_channel->epnum << MUSB_HSDMA_ENDPOINT_SHIFT)
		| (1 << MUSB_HSDMA_ENABLE_SHIFT)
		| (1 << MUSB_HSDMA_IRQENABLE_SHIFT)
		| (musb_channel->transmit
				? (1 << MUSB_HSDMA_TRANSMIT_SHIFT)
				: 0);

	/* address/count */
	musb_ग_लिखो_hsdma_addr(mbase, bchannel, dma_addr);
	musb_ग_लिखो_hsdma_count(mbase, bchannel, len);

	/* control (this should start things) */
	musb_ग_लिखोw(mbase,
		MUSB_HSDMA_CHANNEL_OFFSET(bchannel, MUSB_HSDMA_CONTROL),
		csr);
पूर्ण

अटल पूर्णांक dma_channel_program(काष्ठा dma_channel *channel,
				u16 packet_sz, u8 mode,
				dma_addr_t dma_addr, u32 len)
अणु
	काष्ठा musb_dma_channel *musb_channel = channel->निजी_data;
	काष्ठा musb_dma_controller *controller = musb_channel->controller;
	काष्ठा musb *musb = controller->निजी_data;

	musb_dbg(musb, "ep%d-%s pkt_sz %d, dma_addr %pad length %d, mode %d",
		musb_channel->epnum,
		musb_channel->transmit ? "Tx" : "Rx",
		packet_sz, &dma_addr, len, mode);

	BUG_ON(channel->status == MUSB_DMA_STATUS_UNKNOWN ||
		channel->status == MUSB_DMA_STATUS_BUSY);

	/*
	 * The DMA engine in RTL1.8 and above cannot handle
	 * DMA addresses that are not aligned to a 4 byte boundary.
	 * It ends up masking the last two bits of the address
	 * programmed in DMA_ADDR.
	 *
	 * Fail such DMA transfers, so that the backup PIO mode
	 * can carry out the transfer
	 */
	अगर ((musb->hwvers >= MUSB_HWVERS_1800) && (dma_addr % 4))
		वापस false;

	channel->actual_len = 0;
	musb_channel->start_addr = dma_addr;
	musb_channel->len = len;
	musb_channel->max_packet_sz = packet_sz;
	channel->status = MUSB_DMA_STATUS_BUSY;

	configure_channel(channel, packet_sz, mode, dma_addr, len);

	वापस true;
पूर्ण

अटल पूर्णांक dma_channel_पात(काष्ठा dma_channel *channel)
अणु
	काष्ठा musb_dma_channel *musb_channel = channel->निजी_data;
	व्योम __iomem *mbase = musb_channel->controller->base;
	काष्ठा musb *musb = musb_channel->controller->निजी_data;

	u8 bchannel = musb_channel->idx;
	पूर्णांक offset;
	u16 csr;

	अगर (channel->status == MUSB_DMA_STATUS_BUSY) अणु
		अगर (musb_channel->transmit) अणु
			offset = musb->io.ep_offset(musb_channel->epnum,
						MUSB_TXCSR);

			/*
			 * The programming guide says that we must clear
			 * the DMAENAB bit beक्रमe the DMAMODE bit...
			 */
			csr = musb_पढ़ोw(mbase, offset);
			csr &= ~(MUSB_TXCSR_AUTOSET | MUSB_TXCSR_DMAENAB);
			musb_ग_लिखोw(mbase, offset, csr);
			csr &= ~MUSB_TXCSR_DMAMODE;
			musb_ग_लिखोw(mbase, offset, csr);
		पूर्ण अन्यथा अणु
			offset = musb->io.ep_offset(musb_channel->epnum,
						MUSB_RXCSR);

			csr = musb_पढ़ोw(mbase, offset);
			csr &= ~(MUSB_RXCSR_AUTOCLEAR |
				 MUSB_RXCSR_DMAENAB |
				 MUSB_RXCSR_DMAMODE);
			musb_ग_लिखोw(mbase, offset, csr);
		पूर्ण

		musb_ग_लिखोw(mbase,
			MUSB_HSDMA_CHANNEL_OFFSET(bchannel, MUSB_HSDMA_CONTROL),
			0);
		musb_ग_लिखो_hsdma_addr(mbase, bchannel, 0);
		musb_ग_लिखो_hsdma_count(mbase, bchannel, 0);
		channel->status = MUSB_DMA_STATUS_FREE;
	पूर्ण

	वापस 0;
पूर्ण

irqवापस_t dma_controller_irq(पूर्णांक irq, व्योम *निजी_data)
अणु
	काष्ठा musb_dma_controller *controller = निजी_data;
	काष्ठा musb *musb = controller->निजी_data;
	काष्ठा musb_dma_channel *musb_channel;
	काष्ठा dma_channel *channel;

	व्योम __iomem *mbase = controller->base;

	irqवापस_t retval = IRQ_NONE;

	अचिन्हित दीर्घ flags;

	u8 bchannel;
	u8 पूर्णांक_hsdma;

	u32 addr, count;
	u16 csr;

	spin_lock_irqsave(&musb->lock, flags);

	पूर्णांक_hsdma = musb_clearb(mbase, MUSB_HSDMA_INTR);

	अगर (!पूर्णांक_hsdma) अणु
		musb_dbg(musb, "spurious DMA irq");

		क्रम (bchannel = 0; bchannel < MUSB_HSDMA_CHANNELS; bchannel++) अणु
			musb_channel = (काष्ठा musb_dma_channel *)
					&(controller->channel[bchannel]);
			channel = &musb_channel->channel;
			अगर (channel->status == MUSB_DMA_STATUS_BUSY) अणु
				count = musb_पढ़ो_hsdma_count(mbase, bchannel);

				अगर (count == 0)
					पूर्णांक_hsdma |= (1 << bchannel);
			पूर्ण
		पूर्ण

		musb_dbg(musb, "int_hsdma = 0x%x", पूर्णांक_hsdma);

		अगर (!पूर्णांक_hsdma)
			जाओ करोne;
	पूर्ण

	क्रम (bchannel = 0; bchannel < MUSB_HSDMA_CHANNELS; bchannel++) अणु
		अगर (पूर्णांक_hsdma & (1 << bchannel)) अणु
			musb_channel = (काष्ठा musb_dma_channel *)
					&(controller->channel[bchannel]);
			channel = &musb_channel->channel;

			csr = musb_पढ़ोw(mbase,
					MUSB_HSDMA_CHANNEL_OFFSET(bchannel,
							MUSB_HSDMA_CONTROL));

			अगर (csr & (1 << MUSB_HSDMA_BUSERROR_SHIFT)) अणु
				musb_channel->channel.status =
					MUSB_DMA_STATUS_BUS_ABORT;
			पूर्ण अन्यथा अणु
				addr = musb_पढ़ो_hsdma_addr(mbase,
						bchannel);
				channel->actual_len = addr
					- musb_channel->start_addr;

				musb_dbg(musb, "ch %p, 0x%x -> 0x%x (%zu / %d) %s",
					channel, musb_channel->start_addr,
					addr, channel->actual_len,
					musb_channel->len,
					(channel->actual_len
						< musb_channel->len) ?
					"=> reconfig 0" : "=> complete");

				channel->status = MUSB_DMA_STATUS_FREE;

				/* completed */
				अगर (musb_channel->transmit &&
					(!channel->desired_mode ||
					(channel->actual_len %
					    musb_channel->max_packet_sz))) अणु
					u8  epnum  = musb_channel->epnum;
					पूर्णांक offset = musb->io.ep_offset(epnum,
								    MUSB_TXCSR);
					u16 txcsr;

					/*
					 * The programming guide says that we
					 * must clear DMAENAB beक्रमe DMAMODE.
					 */
					musb_ep_select(mbase, epnum);
					txcsr = musb_पढ़ोw(mbase, offset);
					अगर (channel->desired_mode == 1) अणु
						txcsr &= ~(MUSB_TXCSR_DMAENAB
							| MUSB_TXCSR_AUTOSET);
						musb_ग_लिखोw(mbase, offset, txcsr);
						/* Send out the packet */
						txcsr &= ~MUSB_TXCSR_DMAMODE;
						txcsr |= MUSB_TXCSR_DMAENAB;
					पूर्ण
					txcsr |=  MUSB_TXCSR_TXPKTRDY;
					musb_ग_लिखोw(mbase, offset, txcsr);
				पूर्ण
				musb_dma_completion(musb, musb_channel->epnum,
						    musb_channel->transmit);
			पूर्ण
		पूर्ण
	पूर्ण

	retval = IRQ_HANDLED;
करोne:
	spin_unlock_irqrestore(&musb->lock, flags);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(dma_controller_irq);

व्योम musbhs_dma_controller_destroy(काष्ठा dma_controller *c)
अणु
	काष्ठा musb_dma_controller *controller = container_of(c,
			काष्ठा musb_dma_controller, controller);

	dma_controller_stop(controller);

	अगर (controller->irq)
		मुक्त_irq(controller->irq, c);

	kमुक्त(controller);
पूर्ण
EXPORT_SYMBOL_GPL(musbhs_dma_controller_destroy);

अटल काष्ठा musb_dma_controller *
dma_controller_alloc(काष्ठा musb *musb, व्योम __iomem *base)
अणु
	काष्ठा musb_dma_controller *controller;

	controller = kzalloc(माप(*controller), GFP_KERNEL);
	अगर (!controller)
		वापस शून्य;

	controller->channel_count = MUSB_HSDMA_CHANNELS;
	controller->निजी_data = musb;
	controller->base = base;

	controller->controller.channel_alloc = dma_channel_allocate;
	controller->controller.channel_release = dma_channel_release;
	controller->controller.channel_program = dma_channel_program;
	controller->controller.channel_पात = dma_channel_पात;
	वापस controller;
पूर्ण

काष्ठा dma_controller *
musbhs_dma_controller_create(काष्ठा musb *musb, व्योम __iomem *base)
अणु
	काष्ठा musb_dma_controller *controller;
	काष्ठा device *dev = musb->controller;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक irq = platक्रमm_get_irq_byname(pdev, "dma");

	अगर (irq <= 0) अणु
		dev_err(dev, "No DMA interrupt line!\n");
		वापस शून्य;
	पूर्ण

	controller = dma_controller_alloc(musb, base);
	अगर (!controller)
		वापस शून्य;

	अगर (request_irq(irq, dma_controller_irq, 0,
			dev_name(musb->controller), controller)) अणु
		dev_err(dev, "request_irq %d failed!\n", irq);
		musb_dma_controller_destroy(&controller->controller);

		वापस शून्य;
	पूर्ण

	controller->irq = irq;

	वापस &controller->controller;
पूर्ण
EXPORT_SYMBOL_GPL(musbhs_dma_controller_create);

काष्ठा dma_controller *
musbhs_dma_controller_create_noirq(काष्ठा musb *musb, व्योम __iomem *base)
अणु
	काष्ठा musb_dma_controller *controller;

	controller = dma_controller_alloc(musb, base);
	अगर (!controller)
		वापस शून्य;

	वापस &controller->controller;
पूर्ण
EXPORT_SYMBOL_GPL(musbhs_dma_controller_create_noirq);
