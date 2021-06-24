<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005-2006 by Texas Instruments
 *
 * This file implements a DMA  पूर्णांकerface using TI's CPPI DMA.
 * For now it's DaVinci-only, but CPPI isn't specअगरic to DaVinci or USB.
 * The TUSB6020, using VLYNQ, has CPPI that looks much like DaVinci.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश "musb_core.h"
#समावेश "musb_debug.h"
#समावेश "cppi_dma.h"
#समावेश "davinci.h"


/* CPPI DMA status 7-mar-2006:
 *
 * - See musb_अणुhost,gadgetपूर्ण.c क्रम more info
 *
 * - Correct RX DMA generally क्रमces the engine पूर्णांकo irq-per-packet mode,
 *   which can easily saturate the CPU under non-mass-storage loads.
 *
 * NOTES 24-aug-2006 (2.6.18-rc4):
 *
 * - peripheral RXDMA wedged in a test with packets of length 512/512/1.
 *   evidently after the 1 byte packet was received and acked, the queue
 *   of BDs got garbaged so it wouldn't empty the fअगरo.  (rxcsr 0x2003,
 *   and RX DMA0: 4 left, 80000000 8feff880, 8feff860 8feff860; 8f321401
 *   004001ff 00000001 .. 8feff860)  Host was just getting NAKed on tx
 *   of its next (512 byte) packet.  IRQ issues?
 *
 * REVISIT:  the "transfer DMA" glue between CPPI and USB fअगरos will
 * evidently also directly update the RX and TX CSRs ... so audit all
 * host and peripheral side DMA code to aव्योम CSR access after DMA has
 * been started.
 */

/* REVISIT now we can aव्योम pपुनः_स्मृतिating these descriptors; or
 * more simply, चयन to a global मुक्तlist not per-channel ones.
 * Note: at full speed, 64 descriptors == 4K bulk data.
 */
#घोषणा NUM_TXCHAN_BD       64
#घोषणा NUM_RXCHAN_BD       64

अटल अंतरभूत व्योम cpu_drain_ग_लिखोbuffer(व्योम)
अणु
	wmb();
#अगर_घोषित	CONFIG_CPU_ARM926T
	/* REVISIT this "should not be needed",
	 * but lack of it sure seemed to hurt ...
	 */
	यंत्र("mcr p15, 0, r0, c7, c10, 4 @ drain write buffer\n");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत काष्ठा cppi_descriptor *cppi_bd_alloc(काष्ठा cppi_channel *c)
अणु
	काष्ठा cppi_descriptor	*bd = c->मुक्तlist;

	अगर (bd)
		c->मुक्तlist = bd->next;
	वापस bd;
पूर्ण

अटल अंतरभूत व्योम
cppi_bd_मुक्त(काष्ठा cppi_channel *c, काष्ठा cppi_descriptor *bd)
अणु
	अगर (!bd)
		वापस;
	bd->next = c->मुक्तlist;
	c->मुक्तlist = bd;
पूर्ण

/*
 *  Start DMA controller
 *
 *  Initialize the DMA controller as necessary.
 */

/* zero out entire rx state RAM entry क्रम the channel */
अटल व्योम cppi_reset_rx(काष्ठा cppi_rx_stateram __iomem *rx)
अणु
	musb_ग_लिखोl(&rx->rx_skipbytes, 0, 0);
	musb_ग_लिखोl(&rx->rx_head, 0, 0);
	musb_ग_लिखोl(&rx->rx_sop, 0, 0);
	musb_ग_लिखोl(&rx->rx_current, 0, 0);
	musb_ग_लिखोl(&rx->rx_buf_current, 0, 0);
	musb_ग_लिखोl(&rx->rx_len_len, 0, 0);
	musb_ग_लिखोl(&rx->rx_cnt_cnt, 0, 0);
पूर्ण

/* zero out entire tx state RAM entry क्रम the channel */
अटल व्योम cppi_reset_tx(काष्ठा cppi_tx_stateram __iomem *tx, u32 ptr)
अणु
	musb_ग_लिखोl(&tx->tx_head, 0, 0);
	musb_ग_लिखोl(&tx->tx_buf, 0, 0);
	musb_ग_लिखोl(&tx->tx_current, 0, 0);
	musb_ग_लिखोl(&tx->tx_buf_current, 0, 0);
	musb_ग_लिखोl(&tx->tx_info, 0, 0);
	musb_ग_लिखोl(&tx->tx_rem_len, 0, 0);
	/* musb_ग_लिखोl(&tx->tx_dummy, 0, 0); */
	musb_ग_लिखोl(&tx->tx_complete, 0, ptr);
पूर्ण

अटल व्योम cppi_pool_init(काष्ठा cppi *cppi, काष्ठा cppi_channel *c)
अणु
	पूर्णांक	j;

	/* initialize channel fields */
	c->head = शून्य;
	c->tail = शून्य;
	c->last_processed = शून्य;
	c->channel.status = MUSB_DMA_STATUS_UNKNOWN;
	c->controller = cppi;
	c->is_rndis = 0;
	c->मुक्तlist = शून्य;

	/* build the BD Free list क्रम the channel */
	क्रम (j = 0; j < NUM_TXCHAN_BD + 1; j++) अणु
		काष्ठा cppi_descriptor	*bd;
		dma_addr_t		dma;

		bd = dma_pool_alloc(cppi->pool, GFP_KERNEL, &dma);
		bd->dma = dma;
		cppi_bd_मुक्त(c, bd);
	पूर्ण
पूर्ण

अटल पूर्णांक cppi_channel_पात(काष्ठा dma_channel *);

अटल व्योम cppi_pool_मुक्त(काष्ठा cppi_channel *c)
अणु
	काष्ठा cppi		*cppi = c->controller;
	काष्ठा cppi_descriptor	*bd;

	(व्योम) cppi_channel_पात(&c->channel);
	c->channel.status = MUSB_DMA_STATUS_UNKNOWN;
	c->controller = शून्य;

	/* मुक्त all its bds */
	bd = c->last_processed;
	करो अणु
		अगर (bd)
			dma_pool_मुक्त(cppi->pool, bd, bd->dma);
		bd = cppi_bd_alloc(c);
	पूर्ण जबतक (bd);
	c->last_processed = शून्य;
पूर्ण

अटल व्योम cppi_controller_start(काष्ठा cppi *controller)
अणु
	व्योम __iomem	*tibase;
	पूर्णांक		i;

	/* करो whatever is necessary to start controller */
	क्रम (i = 0; i < ARRAY_SIZE(controller->tx); i++) अणु
		controller->tx[i].transmit = true;
		controller->tx[i].index = i;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(controller->rx); i++) अणु
		controller->rx[i].transmit = false;
		controller->rx[i].index = i;
	पूर्ण

	/* setup BD list on a per channel basis */
	क्रम (i = 0; i < ARRAY_SIZE(controller->tx); i++)
		cppi_pool_init(controller, controller->tx + i);
	क्रम (i = 0; i < ARRAY_SIZE(controller->rx); i++)
		cppi_pool_init(controller, controller->rx + i);

	tibase =  controller->tibase;
	INIT_LIST_HEAD(&controller->tx_complete);

	/* initialise tx/rx channel head poपूर्णांकers to zero */
	क्रम (i = 0; i < ARRAY_SIZE(controller->tx); i++) अणु
		काष्ठा cppi_channel	*tx_ch = controller->tx + i;
		काष्ठा cppi_tx_stateram __iomem *tx;

		INIT_LIST_HEAD(&tx_ch->tx_complete);

		tx = tibase + DAVINCI_TXCPPI_STATERAM_OFFSET(i);
		tx_ch->state_ram = tx;
		cppi_reset_tx(tx, 0);
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(controller->rx); i++) अणु
		काष्ठा cppi_channel	*rx_ch = controller->rx + i;
		काष्ठा cppi_rx_stateram __iomem *rx;

		INIT_LIST_HEAD(&rx_ch->tx_complete);

		rx = tibase + DAVINCI_RXCPPI_STATERAM_OFFSET(i);
		rx_ch->state_ram = rx;
		cppi_reset_rx(rx);
	पूर्ण

	/* enable inभागidual cppi channels */
	musb_ग_लिखोl(tibase, DAVINCI_TXCPPI_INTENAB_REG,
			DAVINCI_DMA_ALL_CHANNELS_ENABLE);
	musb_ग_लिखोl(tibase, DAVINCI_RXCPPI_INTENAB_REG,
			DAVINCI_DMA_ALL_CHANNELS_ENABLE);

	/* enable tx/rx CPPI control */
	musb_ग_लिखोl(tibase, DAVINCI_TXCPPI_CTRL_REG, DAVINCI_DMA_CTRL_ENABLE);
	musb_ग_लिखोl(tibase, DAVINCI_RXCPPI_CTRL_REG, DAVINCI_DMA_CTRL_ENABLE);

	/* disable RNDIS mode, also host rx RNDIS स्वतःrequest */
	musb_ग_लिखोl(tibase, DAVINCI_RNDIS_REG, 0);
	musb_ग_लिखोl(tibase, DAVINCI_AUTOREQ_REG, 0);
पूर्ण

/*
 *  Stop DMA controller
 *
 *  De-Init the DMA controller as necessary.
 */

अटल व्योम cppi_controller_stop(काष्ठा cppi *controller)
अणु
	व्योम __iomem		*tibase;
	पूर्णांक			i;
	काष्ठा musb		*musb;

	musb = controller->controller.musb;

	tibase = controller->tibase;
	/* DISABLE INDIVIDUAL CHANNEL Interrupts */
	musb_ग_लिखोl(tibase, DAVINCI_TXCPPI_INTCLR_REG,
			DAVINCI_DMA_ALL_CHANNELS_ENABLE);
	musb_ग_लिखोl(tibase, DAVINCI_RXCPPI_INTCLR_REG,
			DAVINCI_DMA_ALL_CHANNELS_ENABLE);

	musb_dbg(musb, "Tearing down RX and TX Channels");
	क्रम (i = 0; i < ARRAY_SIZE(controller->tx); i++) अणु
		/* FIXME reकाष्ठाure of txdma to use bds like rxdma */
		controller->tx[i].last_processed = शून्य;
		cppi_pool_मुक्त(controller->tx + i);
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(controller->rx); i++)
		cppi_pool_मुक्त(controller->rx + i);

	/* in Tx Case proper tearकरोwn is supported. We resort to disabling
	 * Tx/Rx CPPI after cleanup of Tx channels. Beक्रमe TX tearकरोwn is
	 * complete TX CPPI cannot be disabled.
	 */
	/*disable tx/rx cppi */
	musb_ग_लिखोl(tibase, DAVINCI_TXCPPI_CTRL_REG, DAVINCI_DMA_CTRL_DISABLE);
	musb_ग_लिखोl(tibase, DAVINCI_RXCPPI_CTRL_REG, DAVINCI_DMA_CTRL_DISABLE);
पूर्ण

/* While dma channel is allocated, we only want the core irqs active
 * क्रम fault reports, otherwise we'd get irqs that we don't care about.
 * Except क्रम TX irqs, where dma करोne != fअगरo empty and reusable ...
 *
 * NOTE: करोcs करोn't say either way, but irq masking **enables** irqs.
 *
 * REVISIT same issue applies to pure PIO usage too, and non-cppi dma...
 */
अटल अंतरभूत व्योम core_rxirq_disable(व्योम __iomem *tibase, अचिन्हित epnum)
अणु
	musb_ग_लिखोl(tibase, DAVINCI_USB_INT_MASK_CLR_REG, 1 << (epnum + 8));
पूर्ण

अटल अंतरभूत व्योम core_rxirq_enable(व्योम __iomem *tibase, अचिन्हित epnum)
अणु
	musb_ग_लिखोl(tibase, DAVINCI_USB_INT_MASK_SET_REG, 1 << (epnum + 8));
पूर्ण


/*
 * Allocate a CPPI Channel क्रम DMA.  With CPPI, channels are bound to
 * each transfer direction of a non-control endpoपूर्णांक, so allocating
 * (and deallocating) is mostly a way to notice bad housekeeping on
 * the software side.  We assume the irqs are always active.
 */
अटल काष्ठा dma_channel *
cppi_channel_allocate(काष्ठा dma_controller *c,
		काष्ठा musb_hw_ep *ep, u8 transmit)
अणु
	काष्ठा cppi		*controller;
	u8			index;
	काष्ठा cppi_channel	*cppi_ch;
	व्योम __iomem		*tibase;
	काष्ठा musb		*musb;

	controller = container_of(c, काष्ठा cppi, controller);
	tibase = controller->tibase;
	musb = c->musb;

	/* ep0 करोesn't use DMA; remember cppi indices are 0..N-1 */
	index = ep->epnum - 1;

	/* वापस the corresponding CPPI Channel Handle, and
	 * probably disable the non-CPPI irq until we need it.
	 */
	अगर (transmit) अणु
		अगर (index >= ARRAY_SIZE(controller->tx)) अणु
			musb_dbg(musb, "no %cX%d CPPI channel", 'T', index);
			वापस शून्य;
		पूर्ण
		cppi_ch = controller->tx + index;
	पूर्ण अन्यथा अणु
		अगर (index >= ARRAY_SIZE(controller->rx)) अणु
			musb_dbg(musb, "no %cX%d CPPI channel", 'R', index);
			वापस शून्य;
		पूर्ण
		cppi_ch = controller->rx + index;
		core_rxirq_disable(tibase, ep->epnum);
	पूर्ण

	/* REVISIT make this an error later once the same driver code works
	 * with the other DMA engine too
	 */
	अगर (cppi_ch->hw_ep)
		musb_dbg(musb, "re-allocating DMA%d %cX channel %p",
				index, transmit ? 'T' : 'R', cppi_ch);
	cppi_ch->hw_ep = ep;
	cppi_ch->channel.status = MUSB_DMA_STATUS_FREE;
	cppi_ch->channel.max_len = 0x7fffffff;

	musb_dbg(musb, "Allocate CPPI%d %cX", index, transmit ? 'T' : 'R');
	वापस &cppi_ch->channel;
पूर्ण

/* Release a CPPI Channel.  */
अटल व्योम cppi_channel_release(काष्ठा dma_channel *channel)
अणु
	काष्ठा cppi_channel	*c;
	व्योम __iomem		*tibase;

	/* REVISIT:  क्रम paranoia, check state and पात अगर needed... */

	c = container_of(channel, काष्ठा cppi_channel, channel);
	tibase = c->controller->tibase;
	अगर (!c->hw_ep)
		musb_dbg(c->controller->controller.musb,
			"releasing idle DMA channel %p", c);
	अन्यथा अगर (!c->transmit)
		core_rxirq_enable(tibase, c->index + 1);

	/* क्रम now, leave its cppi IRQ enabled (we won't trigger it) */
	c->hw_ep = शून्य;
	channel->status = MUSB_DMA_STATUS_UNKNOWN;
पूर्ण

/* Context: controller irqlocked */
अटल व्योम
cppi_dump_rx(पूर्णांक level, काष्ठा cppi_channel *c, स्थिर अक्षर *tag)
अणु
	व्योम __iomem			*base = c->controller->mregs;
	काष्ठा cppi_rx_stateram __iomem	*rx = c->state_ram;

	musb_ep_select(base, c->index + 1);

	musb_dbg(c->controller->controller.musb,
		"RX DMA%d%s: %d left, csr %04x, "
		"%08x H%08x S%08x C%08x, "
		"B%08x L%08x %08x .. %08x",
		c->index, tag,
		musb_पढ़ोl(c->controller->tibase,
			DAVINCI_RXCPPI_BUFCNT0_REG + 4 * c->index),
		musb_पढ़ोw(c->hw_ep->regs, MUSB_RXCSR),

		musb_पढ़ोl(&rx->rx_skipbytes, 0),
		musb_पढ़ोl(&rx->rx_head, 0),
		musb_पढ़ोl(&rx->rx_sop, 0),
		musb_पढ़ोl(&rx->rx_current, 0),

		musb_पढ़ोl(&rx->rx_buf_current, 0),
		musb_पढ़ोl(&rx->rx_len_len, 0),
		musb_पढ़ोl(&rx->rx_cnt_cnt, 0),
		musb_पढ़ोl(&rx->rx_complete, 0)
		);
पूर्ण

/* Context: controller irqlocked */
अटल व्योम
cppi_dump_tx(पूर्णांक level, काष्ठा cppi_channel *c, स्थिर अक्षर *tag)
अणु
	व्योम __iomem			*base = c->controller->mregs;
	काष्ठा cppi_tx_stateram __iomem	*tx = c->state_ram;

	musb_ep_select(base, c->index + 1);

	musb_dbg(c->controller->controller.musb,
		"TX DMA%d%s: csr %04x, "
		"H%08x S%08x C%08x %08x, "
		"F%08x L%08x .. %08x",
		c->index, tag,
		musb_पढ़ोw(c->hw_ep->regs, MUSB_TXCSR),

		musb_पढ़ोl(&tx->tx_head, 0),
		musb_पढ़ोl(&tx->tx_buf, 0),
		musb_पढ़ोl(&tx->tx_current, 0),
		musb_पढ़ोl(&tx->tx_buf_current, 0),

		musb_पढ़ोl(&tx->tx_info, 0),
		musb_पढ़ोl(&tx->tx_rem_len, 0),
		/* dummy/unused word 6 */
		musb_पढ़ोl(&tx->tx_complete, 0)
		);
पूर्ण

/* Context: controller irqlocked */
अटल अंतरभूत व्योम
cppi_rndis_update(काष्ठा cppi_channel *c, पूर्णांक is_rx,
		व्योम __iomem *tibase, पूर्णांक is_rndis)
अणु
	/* we may need to change the rndis flag क्रम this cppi channel */
	अगर (c->is_rndis != is_rndis) अणु
		u32	value = musb_पढ़ोl(tibase, DAVINCI_RNDIS_REG);
		u32	temp = 1 << (c->index);

		अगर (is_rx)
			temp <<= 16;
		अगर (is_rndis)
			value |= temp;
		अन्यथा
			value &= ~temp;
		musb_ग_लिखोl(tibase, DAVINCI_RNDIS_REG, value);
		c->is_rndis = is_rndis;
	पूर्ण
पूर्ण

अटल व्योम cppi_dump_rxbd(स्थिर अक्षर *tag, काष्ठा cppi_descriptor *bd)
अणु
	pr_debug("RXBD/%s %08x: "
			"nxt %08x buf %08x off.blen %08x opt.plen %08x\n",
			tag, bd->dma,
			bd->hw_next, bd->hw_bufp, bd->hw_off_len,
			bd->hw_options);
पूर्ण

अटल व्योम cppi_dump_rxq(पूर्णांक level, स्थिर अक्षर *tag, काष्ठा cppi_channel *rx)
अणु
	काष्ठा cppi_descriptor	*bd;

	cppi_dump_rx(level, rx, tag);
	अगर (rx->last_processed)
		cppi_dump_rxbd("last", rx->last_processed);
	क्रम (bd = rx->head; bd; bd = bd->next)
		cppi_dump_rxbd("active", bd);
पूर्ण


/* NOTE:  DaVinci स्वतःreq is ignored except क्रम host side "RNDIS" mode RX;
 * so we won't ever use it (see "CPPI RX Woes" below).
 */
अटल अंतरभूत पूर्णांक cppi_स्वतःreq_update(काष्ठा cppi_channel *rx,
		व्योम __iomem *tibase, पूर्णांक onepacket, अचिन्हित n_bds)
अणु
	u32	val;

#अगर_घोषित	RNDIS_RX_IS_USABLE
	u32	पंचांगp;
	/* निश्चित(is_host_active(musb)) */

	/* start from "AutoReq never" */
	पंचांगp = musb_पढ़ोl(tibase, DAVINCI_AUTOREQ_REG);
	val = पंचांगp & ~((0x3) << (rx->index * 2));

	/* HCD arranged reqpkt क्रम packet #1.  we arrange पूर्णांक
	 * क्रम all but the last one, maybe in two segments.
	 */
	अगर (!onepacket) अणु
#अगर 0
		/* use two segments, स्वतःreq "all" then the last "never" */
		val |= ((0x3) << (rx->index * 2));
		n_bds--;
#अन्यथा
		/* one segment, स्वतःreq "all-but-last" */
		val |= ((0x1) << (rx->index * 2));
#पूर्ण_अगर
	पूर्ण

	अगर (val != पंचांगp) अणु
		पूर्णांक n = 100;

		/* make sure that स्वतःreq is updated beक्रमe continuing */
		musb_ग_लिखोl(tibase, DAVINCI_AUTOREQ_REG, val);
		करो अणु
			पंचांगp = musb_पढ़ोl(tibase, DAVINCI_AUTOREQ_REG);
			अगर (पंचांगp == val)
				अवरोध;
			cpu_relax();
		पूर्ण जबतक (n-- > 0);
	पूर्ण
#पूर्ण_अगर

	/* REQPKT is turned off after each segment */
	अगर (n_bds && rx->channel.actual_len) अणु
		व्योम __iomem	*regs = rx->hw_ep->regs;

		val = musb_पढ़ोw(regs, MUSB_RXCSR);
		अगर (!(val & MUSB_RXCSR_H_REQPKT)) अणु
			val |= MUSB_RXCSR_H_REQPKT | MUSB_RXCSR_H_WZC_BITS;
			musb_ग_लिखोw(regs, MUSB_RXCSR, val);
			/* flush ग_लिखोbuffer */
			val = musb_पढ़ोw(regs, MUSB_RXCSR);
		पूर्ण
	पूर्ण
	वापस n_bds;
पूर्ण


/* Buffer enqueuing Logic:
 *
 *  - RX builds new queues each समय, to help handle routine "early
 *    termination" हालs (faults, including errors and लघु पढ़ोs)
 *    more correctly.
 *
 *  - क्रम now, TX reuses the same queue of BDs every समय
 *
 * REVISIT दीर्घ term, we want a normal dynamic model.
 * ... the goal will be to append to the
 * existing queue, processing completed "dma buffers" (segments) on the fly.
 *
 * Otherwise we क्रमce an IRQ latency between requests, which slows us a lot
 * (especially in "transparent" dma).  Unक्रमtunately that model seems to be
 * inherent in the DMA model from the Mentor code, except in the rare हाल
 * of transfers big enough (~128+ KB) that we could append "middle" segments
 * in the TX paths.  (RX can't करो this, see below.)
 *
 * That's true even in the CPPI- मित्रly iso हाल, where most urbs have
 * several small segments provided in a group and where the "packet at a time"
 * "transparent" DMA model is always correct, even on the RX side.
 */

/*
 * CPPI TX:
 * ========
 * TX is a lot more reasonable than RX; it करोesn't need to run in
 * irq-per-packet mode very often.  RNDIS mode seems to behave too
 * (except how it handles the exactly-N-packets हाल).  Building a
 * txdma queue with multiple requests (urb or usb_request) looks
 * like it would work ... but fault handling would need much testing.
 *
 * The मुख्य issue with TX mode RNDIS relates to transfer lengths that
 * are an exact multiple of the packet length.  It appears that there's
 * a hiccup in that हाल (maybe the DMA completes beक्रमe the ZLP माला_लो
 * written?) boiling करोwn to not being able to rely on CPPI writing any
 * terminating zero length packet beक्रमe the next transfer is written.
 * So that's punted to PIO; better yet, gadget drivers can aव्योम it.
 *
 * Plus, there's allegedly an unकरोcumented स्थिरraपूर्णांक that rndis transfer
 * length be a multiple of 64 bytes ... but the chip करोesn't act that
 * way, and we really करोn't _want_ that behavior anyway.
 *
 * On TX, "transparent" mode works ... although experiments have shown
 * problems trying to use the SOP/EOP bits in dअगरferent USB packets.
 *
 * REVISIT try to handle terminating zero length packets using CPPI
 * instead of करोing it by PIO after an IRQ.  (Meanजबतक, make Ethernet
 * links aव्योम that issue by क्रमcing them to aव्योम zlps.)
 */
अटल व्योम
cppi_next_tx_segment(काष्ठा musb *musb, काष्ठा cppi_channel *tx)
अणु
	अचिन्हित		maxpacket = tx->maxpacket;
	dma_addr_t		addr = tx->buf_dma + tx->offset;
	माप_प्रकार			length = tx->buf_len - tx->offset;
	काष्ठा cppi_descriptor	*bd;
	अचिन्हित		n_bds;
	अचिन्हित		i;
	काष्ठा cppi_tx_stateram	__iomem *tx_ram = tx->state_ram;
	पूर्णांक			rndis;

	/* TX can use the CPPI "rndis" mode, where we can probably fit this
	 * transfer in one BD and one IRQ.  The only समय we would NOT want
	 * to use it is when hardware स्थिरraपूर्णांकs prevent it, or अगर we'd
	 * trigger the "send a ZLP?" confusion.
	 */
	rndis = (maxpacket & 0x3f) == 0
		&& length > maxpacket
		&& length < 0xffff
		&& (length % maxpacket) != 0;

	अगर (rndis) अणु
		maxpacket = length;
		n_bds = 1;
	पूर्ण अन्यथा अणु
		अगर (length)
			n_bds = DIV_ROUND_UP(length, maxpacket);
		अन्यथा
			n_bds = 1;
		n_bds = min(n_bds, (अचिन्हित) NUM_TXCHAN_BD);
		length = min(n_bds * maxpacket, length);
	पूर्ण

	musb_dbg(musb, "TX DMA%d, pktSz %d %s bds %d dma 0x%llx len %u",
			tx->index,
			maxpacket,
			rndis ? "rndis" : "transparent",
			n_bds,
			(अचिन्हित दीर्घ दीर्घ)addr, length);

	cppi_rndis_update(tx, 0, musb->ctrl_base, rndis);

	/* assuming here that channel_program is called during
	 * transfer initiation ... current code मुख्यtains state
	 * क्रम one outstanding request only (no queues, not even
	 * the implicit ones of an iso urb).
	 */

	bd = tx->मुक्तlist;
	tx->head = bd;
	tx->last_processed = शून्य;

	/* FIXME use BD pool like RX side करोes, and just queue
	 * the minimum number क्रम this request.
	 */

	/* Prepare queue of BDs first, then hand it to hardware.
	 * All BDs except maybe the last should be of full packet
	 * size; क्रम RNDIS there _is_ only that last packet.
	 */
	क्रम (i = 0; i < n_bds; ) अणु
		अगर (++i < n_bds && bd->next)
			bd->hw_next = bd->next->dma;
		अन्यथा
			bd->hw_next = 0;

		bd->hw_bufp = tx->buf_dma + tx->offset;

		/* FIXME set EOP only on the last packet,
		 * SOP only on the first ... aव्योम IRQs
		 */
		अगर ((tx->offset + maxpacket) <= tx->buf_len) अणु
			tx->offset += maxpacket;
			bd->hw_off_len = maxpacket;
			bd->hw_options = CPPI_SOP_SET | CPPI_EOP_SET
				| CPPI_OWN_SET | maxpacket;
		पूर्ण अन्यथा अणु
			/* only this one may be a partial USB Packet */
			u32		partial_len;

			partial_len = tx->buf_len - tx->offset;
			tx->offset = tx->buf_len;
			bd->hw_off_len = partial_len;

			bd->hw_options = CPPI_SOP_SET | CPPI_EOP_SET
				| CPPI_OWN_SET | partial_len;
			अगर (partial_len == 0)
				bd->hw_options |= CPPI_ZERO_SET;
		पूर्ण

		musb_dbg(musb, "TXBD %p: nxt %08x buf %08x len %04x opt %08x",
				bd, bd->hw_next, bd->hw_bufp,
				bd->hw_off_len, bd->hw_options);

		/* update the last BD enqueued to the list */
		tx->tail = bd;
		bd = bd->next;
	पूर्ण

	/* BDs live in DMA-coherent memory, but ग_लिखोs might be pending */
	cpu_drain_ग_लिखोbuffer();

	/* Write to the HeadPtr in state RAM to trigger */
	musb_ग_लिखोl(&tx_ram->tx_head, 0, (u32)tx->मुक्तlist->dma);

	cppi_dump_tx(5, tx, "/S");
पूर्ण

/*
 * CPPI RX Woes:
 * =============
 * Consider a 1KB bulk RX buffer in two scenarios:  (a) it's fed two 300 byte
 * packets back-to-back, and (b) it's fed two 512 byte packets back-to-back.
 * (Full speed transfers have similar scenarios.)
 *
 * The correct behavior क्रम Linux is that (a) fills the buffer with 300 bytes,
 * and the next packet goes पूर्णांकo a buffer that's queued later; जबतक (b) fills
 * the buffer with 1024 bytes.  How to करो that with CPPI?
 *
 * - RX queues in "rndis" mode -- one single BD -- handle (a) correctly, but
 *   (b) loses **BADLY** because nothing (!) happens when that second packet
 *   fills the buffer, much less when a third one arrives.  (Which makes this
 *   not a "true" RNDIS mode.  In the RNDIS protocol लघु-packet termination
 *   is optional, and it's fine अगर peripherals -- not hosts! -- pad messages
 *   out to end-of-buffer.  Standard PCI host controller DMA descriptors
 *   implement that mode by शेष ... which is no accident.)
 *
 * - RX queues in "transparent" mode -- two BDs with 512 bytes each -- have
 *   converse problems:  (b) is handled right, but (a) loses badly.  CPPI RX
 *   ignores SOP/EOP markings and processes both of those BDs; so both packets
 *   are loaded पूर्णांकo the buffer (with a 212 byte gap between them), and the next
 *   buffer queued will NOT get its 300 bytes of data. (It seems like SOP/EOP
 *   are पूर्णांकended as outमाला_दो क्रम RX queues, not inमाला_दो...)
 *
 * - A variant of "transparent" mode -- one BD at a समय -- is the only way to
 *   reliably make both हालs work, with software handling both हालs correctly
 *   and at the signअगरicant penalty of needing an IRQ per packet.  (The lack of
 *   I/O overlap can be slightly ameliorated by enabling द्विगुन buffering.)
 *
 * So how to get rid of IRQ-per-packet?  The transparent multi-BD हाल could
 * be used in special हालs like mass storage, which sets URB_SHORT_NOT_OK
 * (or maybe its peripheral side counterpart) to flag (a) scenarios as errors
 * with guaranteed driver level fault recovery and scrubbing out what's left
 * of that garbaged datastream.
 *
 * But there seems to be no way to identअगरy the हालs where CPPI RNDIS mode
 * is appropriate -- which करो NOT include RNDIS host drivers, but करो include
 * the CDC Ethernet driver! -- and the करोcumentation is incomplete/wrong.
 * So we can't _ever_ use RX RNDIS mode ... except by using a heuristic
 * that applies best on the peripheral side (and which could fail rudely).
 *
 * Leaving only "transparent" mode; we aव्योम multi-bd modes in almost all
 * हालs other than mass storage class.  Otherwise we're correct but slow,
 * since CPPI penalizes our need क्रम a "true RNDIS" शेष mode.
 */


/* Heuristic, पूर्णांकended to kick in क्रम ethernet/rndis peripheral ONLY
 *
 * IFF
 *  (a)	peripheral mode ... since rndis peripherals could pad their
 *	ग_लिखोs to hosts, causing i/o failure; or we'd have to cope with
 *	a largely unknowable variety of host side protocol variants
 *  (b)	and लघु पढ़ोs are NOT errors ... since full पढ़ोs would
 *	cause those same i/o failures
 *  (c)	and पढ़ो length is
 *	- less than 64KB (max per cppi descriptor)
 *	- not a multiple of 4096 (g_zero शेष, full पढ़ोs typical)
 *	- N (>1) packets दीर्घ, ditto (full पढ़ोs not EXPECTED)
 * THEN
 *   try rx rndis mode
 *
 * Cost of heuristic failing:  RXDMA wedges at the end of transfers that
 * fill out the whole buffer.  Buggy host side usb network drivers could
 * trigger that, but "in the field" such bugs seem to be all but unknown.
 *
 * So this module parameter lets the heuristic be disabled.  When using
 * gadgetfs, the heuristic will probably need to be disabled.
 */
अटल bool cppi_rx_rndis = 1;

module_param(cppi_rx_rndis, bool, 0);
MODULE_PARM_DESC(cppi_rx_rndis, "enable/disable RX RNDIS heuristic");


/**
 * cppi_next_rx_segment - dma पढ़ो क्रम the next chunk of a buffer
 * @musb: the controller
 * @rx: dma channel
 * @onepacket: true unless caller treats लघु पढ़ोs as errors, and
 *	perक्रमms fault recovery above usbcore.
 * Context: controller irqlocked
 *
 * See above notes about why we can't use multi-BD RX queues except in
 * rare हालs (mass storage class), and can never use the hardware "rndis"
 * mode (since it's not a "true" RNDIS mode) with complete safety..
 *
 * It's ESSENTIAL that callers specअगरy "onepacket" mode unless they kick in
 * code to recover from corrupted datastreams after each लघु transfer.
 */
अटल व्योम
cppi_next_rx_segment(काष्ठा musb *musb, काष्ठा cppi_channel *rx, पूर्णांक onepacket)
अणु
	अचिन्हित		maxpacket = rx->maxpacket;
	dma_addr_t		addr = rx->buf_dma + rx->offset;
	माप_प्रकार			length = rx->buf_len - rx->offset;
	काष्ठा cppi_descriptor	*bd, *tail;
	अचिन्हित		n_bds;
	अचिन्हित		i;
	व्योम __iomem		*tibase = musb->ctrl_base;
	पूर्णांक			is_rndis = 0;
	काष्ठा cppi_rx_stateram	__iomem *rx_ram = rx->state_ram;
	काष्ठा cppi_descriptor	*d;

	अगर (onepacket) अणु
		/* almost every USB driver, host or peripheral side */
		n_bds = 1;

		/* maybe apply the heuristic above */
		अगर (cppi_rx_rndis
				&& is_peripheral_active(musb)
				&& length > maxpacket
				&& (length & ~0xffff) == 0
				&& (length & 0x0fff) != 0
				&& (length & (maxpacket - 1)) == 0) अणु
			maxpacket = length;
			is_rndis = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* भवly nothing except mass storage class */
		अगर (length > 0xffff) अणु
			n_bds = 0xffff / maxpacket;
			length = n_bds * maxpacket;
		पूर्ण अन्यथा अणु
			n_bds = DIV_ROUND_UP(length, maxpacket);
		पूर्ण
		अगर (n_bds == 1)
			onepacket = 1;
		अन्यथा
			n_bds = min(n_bds, (अचिन्हित) NUM_RXCHAN_BD);
	पूर्ण

	/* In host mode, स्वतःrequest logic can generate some IN tokens; it's
	 * tricky since we can't leave REQPKT set in RXCSR after the transfer
	 * finishes. So:  multipacket transfers involve two or more segments.
	 * And always at least two IRQs ... RNDIS mode is not an option.
	 */
	अगर (is_host_active(musb))
		n_bds = cppi_स्वतःreq_update(rx, tibase, onepacket, n_bds);

	cppi_rndis_update(rx, 1, musb->ctrl_base, is_rndis);

	length = min(n_bds * maxpacket, length);

	musb_dbg(musb, "RX DMA%d seg, maxp %d %s bds %d (cnt %d) "
			"dma 0x%llx len %u %u/%u",
			rx->index, maxpacket,
			onepacket
				? (is_rndis ? "rndis" : "onepacket")
				: "multipacket",
			n_bds,
			musb_पढ़ोl(tibase,
				DAVINCI_RXCPPI_BUFCNT0_REG + (rx->index * 4))
					& 0xffff,
			(अचिन्हित दीर्घ दीर्घ)addr, length,
			rx->channel.actual_len, rx->buf_len);

	/* only queue one segment at a समय, since the hardware prevents
	 * correct queue shutकरोwn after unexpected लघु packets
	 */
	bd = cppi_bd_alloc(rx);
	rx->head = bd;

	/* Build BDs क्रम all packets in this segment */
	क्रम (i = 0, tail = शून्य; bd && i < n_bds; i++, tail = bd) अणु
		u32	bd_len;

		अगर (i) अणु
			bd = cppi_bd_alloc(rx);
			अगर (!bd)
				अवरोध;
			tail->next = bd;
			tail->hw_next = bd->dma;
		पूर्ण
		bd->hw_next = 0;

		/* all but the last packet will be maxpacket size */
		अगर (maxpacket < length)
			bd_len = maxpacket;
		अन्यथा
			bd_len = length;

		bd->hw_bufp = addr;
		addr += bd_len;
		rx->offset += bd_len;

		bd->hw_off_len = (0 /*offset*/ << 16) + bd_len;
		bd->buflen = bd_len;

		bd->hw_options = CPPI_OWN_SET | (i == 0 ? length : 0);
		length -= bd_len;
	पूर्ण

	/* we always expect at least one reusable BD! */
	अगर (!tail) अणु
		WARNING("rx dma%d -- no BDs? need %d\n", rx->index, n_bds);
		वापस;
	पूर्ण अन्यथा अगर (i < n_bds)
		WARNING("rx dma%d -- only %d of %d BDs\n", rx->index, i, n_bds);

	tail->next = शून्य;
	tail->hw_next = 0;

	bd = rx->head;
	rx->tail = tail;

	/* लघु पढ़ोs and other faults should terminate this entire
	 * dma segment.  we want one "dma packet" per dma segment, not
	 * one per USB packet, terminating the whole queue at once...
	 * NOTE that current hardware seems to ignore SOP and EOP.
	 */
	bd->hw_options |= CPPI_SOP_SET;
	tail->hw_options |= CPPI_EOP_SET;

	क्रम (d = rx->head; d; d = d->next)
		cppi_dump_rxbd("S", d);

	/* in हाल the preceding transfer left some state... */
	tail = rx->last_processed;
	अगर (tail) अणु
		tail->next = bd;
		tail->hw_next = bd->dma;
	पूर्ण

	core_rxirq_enable(tibase, rx->index + 1);

	/* BDs live in DMA-coherent memory, but ग_लिखोs might be pending */
	cpu_drain_ग_लिखोbuffer();

	/* REVISIT specs say to ग_लिखो this AFTER the BUFCNT रेजिस्टर
	 * below ... but that loses badly.
	 */
	musb_ग_लिखोl(&rx_ram->rx_head, 0, bd->dma);

	/* bufferCount must be at least 3, and zeroes on completion
	 * unless it underflows below zero, or stops at two, or keeps
	 * growing ... grr.
	 */
	i = musb_पढ़ोl(tibase,
			DAVINCI_RXCPPI_BUFCNT0_REG + (rx->index * 4))
			& 0xffff;

	अगर (!i)
		musb_ग_लिखोl(tibase,
			DAVINCI_RXCPPI_BUFCNT0_REG + (rx->index * 4),
			n_bds + 2);
	अन्यथा अगर (n_bds > (i - 3))
		musb_ग_लिखोl(tibase,
			DAVINCI_RXCPPI_BUFCNT0_REG + (rx->index * 4),
			n_bds - (i - 3));

	i = musb_पढ़ोl(tibase,
			DAVINCI_RXCPPI_BUFCNT0_REG + (rx->index * 4))
			& 0xffff;
	अगर (i < (2 + n_bds)) अणु
		musb_dbg(musb, "bufcnt%d underrun - %d (for %d)",
					rx->index, i, n_bds);
		musb_ग_लिखोl(tibase,
			DAVINCI_RXCPPI_BUFCNT0_REG + (rx->index * 4),
			n_bds + 2);
	पूर्ण

	cppi_dump_rx(4, rx, "/S");
पूर्ण

/**
 * cppi_channel_program - program channel क्रम data transfer
 * @ch: the channel
 * @maxpacket: max packet size
 * @mode: For RX, 1 unless the usb protocol driver promised to treat
 *	all लघु पढ़ोs as errors and kick in high level fault recovery.
 *	For TX, ignored because of RNDIS mode races/glitches.
 * @dma_addr: dma address of buffer
 * @len: length of buffer
 * Context: controller irqlocked
 */
अटल पूर्णांक cppi_channel_program(काष्ठा dma_channel *ch,
		u16 maxpacket, u8 mode,
		dma_addr_t dma_addr, u32 len)
अणु
	काष्ठा cppi_channel	*cppi_ch;
	काष्ठा cppi		*controller;
	काष्ठा musb		*musb;

	cppi_ch = container_of(ch, काष्ठा cppi_channel, channel);
	controller = cppi_ch->controller;
	musb = controller->controller.musb;

	चयन (ch->status) अणु
	हाल MUSB_DMA_STATUS_BUS_ABORT:
	हाल MUSB_DMA_STATUS_CORE_ABORT:
		/* fault irq handler should have handled cleanup */
		WARNING("%cX DMA%d not cleaned up after abort!\n",
				cppi_ch->transmit ? 'T' : 'R',
				cppi_ch->index);
		/* WARN_ON(1); */
		अवरोध;
	हाल MUSB_DMA_STATUS_BUSY:
		WARNING("program active channel?  %cX DMA%d\n",
				cppi_ch->transmit ? 'T' : 'R',
				cppi_ch->index);
		/* WARN_ON(1); */
		अवरोध;
	हाल MUSB_DMA_STATUS_UNKNOWN:
		musb_dbg(musb, "%cX DMA%d not allocated!",
				cppi_ch->transmit ? 'T' : 'R',
				cppi_ch->index);
		fallthrough;
	हाल MUSB_DMA_STATUS_FREE:
		अवरोध;
	पूर्ण

	ch->status = MUSB_DMA_STATUS_BUSY;

	/* set transfer parameters, then queue up its first segment */
	cppi_ch->buf_dma = dma_addr;
	cppi_ch->offset = 0;
	cppi_ch->maxpacket = maxpacket;
	cppi_ch->buf_len = len;
	cppi_ch->channel.actual_len = 0;

	/* TX channel? or RX? */
	अगर (cppi_ch->transmit)
		cppi_next_tx_segment(musb, cppi_ch);
	अन्यथा
		cppi_next_rx_segment(musb, cppi_ch, mode);

	वापस true;
पूर्ण

अटल bool cppi_rx_scan(काष्ठा cppi *cppi, अचिन्हित ch)
अणु
	काष्ठा cppi_channel		*rx = &cppi->rx[ch];
	काष्ठा cppi_rx_stateram __iomem	*state = rx->state_ram;
	काष्ठा cppi_descriptor		*bd;
	काष्ठा cppi_descriptor		*last = rx->last_processed;
	bool				completed = false;
	bool				acked = false;
	पूर्णांक				i;
	dma_addr_t			safe2ack;
	व्योम __iomem			*regs = rx->hw_ep->regs;
	काष्ठा musb			*musb = cppi->controller.musb;

	cppi_dump_rx(6, rx, "/K");

	bd = last ? last->next : rx->head;
	अगर (!bd)
		वापस false;

	/* run through all completed BDs */
	क्रम (i = 0, safe2ack = musb_पढ़ोl(&state->rx_complete, 0);
			(safe2ack || completed) && bd && i < NUM_RXCHAN_BD;
			i++, bd = bd->next) अणु
		u16	len;

		/* catch latest BD ग_लिखोs from CPPI */
		rmb();
		अगर (!completed && (bd->hw_options & CPPI_OWN_SET))
			अवरोध;

		musb_dbg(musb, "C/RXBD %llx: nxt %08x buf %08x "
			"off.len %08x opt.len %08x (%d)",
			(अचिन्हित दीर्घ दीर्घ)bd->dma, bd->hw_next, bd->hw_bufp,
			bd->hw_off_len, bd->hw_options,
			rx->channel.actual_len);

		/* actual packet received length */
		अगर ((bd->hw_options & CPPI_SOP_SET) && !completed)
			len = bd->hw_off_len & CPPI_RECV_PKTLEN_MASK;
		अन्यथा
			len = 0;

		अगर (bd->hw_options & CPPI_EOQ_MASK)
			completed = true;

		अगर (!completed && len < bd->buflen) अणु
			/* NOTE:  when we get a लघु packet, RXCSR_H_REQPKT
			 * must have been cleared, and no more DMA packets may
			 * active be in the queue... TI करोcs didn't say, but
			 * CPPI ignores those BDs even though OWN is still set.
			 */
			completed = true;
			musb_dbg(musb, "rx short %d/%d (%d)",
					len, bd->buflen,
					rx->channel.actual_len);
		पूर्ण

		/* If we got here, we expect to ack at least one BD; meanजबतक
		 * CPPI may completing other BDs जबतक we scan this list...
		 *
		 * RACE: we can notice OWN cleared beक्रमe CPPI उठाओs the
		 * matching irq by writing that BD as the completion poपूर्णांकer.
		 * In such हालs, stop scanning and रुको क्रम the irq, aव्योमing
		 * lost acks and states where BD ownership is unclear.
		 */
		अगर (bd->dma == safe2ack) अणु
			musb_ग_लिखोl(&state->rx_complete, 0, safe2ack);
			safe2ack = musb_पढ़ोl(&state->rx_complete, 0);
			acked = true;
			अगर (bd->dma == safe2ack)
				safe2ack = 0;
		पूर्ण

		rx->channel.actual_len += len;

		cppi_bd_मुक्त(rx, last);
		last = bd;

		/* stop scanning on end-of-segment */
		अगर (bd->hw_next == 0)
			completed = true;
	पूर्ण
	rx->last_processed = last;

	/* dma पात, lost ack, or ... */
	अगर (!acked && last) अणु
		पूर्णांक	csr;

		अगर (safe2ack == 0 || safe2ack == rx->last_processed->dma)
			musb_ग_लिखोl(&state->rx_complete, 0, safe2ack);
		अगर (safe2ack == 0) अणु
			cppi_bd_मुक्त(rx, last);
			rx->last_processed = शून्य;

			/* अगर we land here on the host side, H_REQPKT will
			 * be clear and we need to restart the queue...
			 */
			WARN_ON(rx->head);
		पूर्ण
		musb_ep_select(cppi->mregs, rx->index + 1);
		csr = musb_पढ़ोw(regs, MUSB_RXCSR);
		अगर (csr & MUSB_RXCSR_DMAENAB) अणु
			musb_dbg(musb, "list%d %p/%p, last %llx%s, csr %04x",
				rx->index,
				rx->head, rx->tail,
				rx->last_processed
					? (अचिन्हित दीर्घ दीर्घ)
						rx->last_processed->dma
					: 0,
				completed ? ", completed" : "",
				csr);
			cppi_dump_rxq(4, "/what?", rx);
		पूर्ण
	पूर्ण
	अगर (!completed) अणु
		पूर्णांक	csr;

		rx->head = bd;

		/* REVISIT seems like "autoreq all but EOP" करोesn't...
		 * setting it here "should" be racey, but seems to work
		 */
		csr = musb_पढ़ोw(rx->hw_ep->regs, MUSB_RXCSR);
		अगर (is_host_active(cppi->controller.musb)
				&& bd
				&& !(csr & MUSB_RXCSR_H_REQPKT)) अणु
			csr |= MUSB_RXCSR_H_REQPKT;
			musb_ग_लिखोw(regs, MUSB_RXCSR,
					MUSB_RXCSR_H_WZC_BITS | csr);
			csr = musb_पढ़ोw(rx->hw_ep->regs, MUSB_RXCSR);
		पूर्ण
	पूर्ण अन्यथा अणु
		rx->head = शून्य;
		rx->tail = शून्य;
	पूर्ण

	cppi_dump_rx(6, rx, completed ? "/completed" : "/cleaned");
	वापस completed;
पूर्ण

irqवापस_t cppi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा musb		*musb = dev_id;
	काष्ठा cppi		*cppi;
	व्योम __iomem		*tibase;
	काष्ठा musb_hw_ep	*hw_ep = शून्य;
	u32			rx, tx;
	पूर्णांक			i, index;
	अचिन्हित दीर्घ		flags;

	cppi = container_of(musb->dma_controller, काष्ठा cppi, controller);
	अगर (cppi->irq)
		spin_lock_irqsave(&musb->lock, flags);

	tibase = musb->ctrl_base;

	tx = musb_पढ़ोl(tibase, DAVINCI_TXCPPI_MASKED_REG);
	rx = musb_पढ़ोl(tibase, DAVINCI_RXCPPI_MASKED_REG);

	अगर (!tx && !rx) अणु
		अगर (cppi->irq)
			spin_unlock_irqrestore(&musb->lock, flags);
		वापस IRQ_NONE;
	पूर्ण

	musb_dbg(musb, "CPPI IRQ Tx%x Rx%x", tx, rx);

	/* process TX channels */
	क्रम (index = 0; tx; tx = tx >> 1, index++) अणु
		काष्ठा cppi_channel		*tx_ch;
		काष्ठा cppi_tx_stateram __iomem	*tx_ram;
		bool				completed = false;
		काष्ठा cppi_descriptor		*bd;

		अगर (!(tx & 1))
			जारी;

		tx_ch = cppi->tx + index;
		tx_ram = tx_ch->state_ram;

		/* FIXME  need a cppi_tx_scan() routine, which
		 * can also be called from पात code
		 */

		cppi_dump_tx(5, tx_ch, "/E");

		bd = tx_ch->head;

		/*
		 * If Head is null then this could mean that a पात पूर्णांकerrupt
		 * that needs to be acknowledged.
		 */
		अगर (शून्य == bd) अणु
			musb_dbg(musb, "null BD");
			musb_ग_लिखोl(&tx_ram->tx_complete, 0, 0);
			जारी;
		पूर्ण

		/* run through all completed BDs */
		क्रम (i = 0; !completed && bd && i < NUM_TXCHAN_BD;
				i++, bd = bd->next) अणु
			u16	len;

			/* catch latest BD ग_लिखोs from CPPI */
			rmb();
			अगर (bd->hw_options & CPPI_OWN_SET)
				अवरोध;

			musb_dbg(musb, "C/TXBD %p n %x b %x off %x opt %x",
					bd, bd->hw_next, bd->hw_bufp,
					bd->hw_off_len, bd->hw_options);

			len = bd->hw_off_len & CPPI_BUFFER_LEN_MASK;
			tx_ch->channel.actual_len += len;

			tx_ch->last_processed = bd;

			/* ग_लिखो completion रेजिस्टर to acknowledge
			 * processing of completed BDs, and possibly
			 * release the IRQ; EOQ might not be set ...
			 *
			 * REVISIT use the same ack strategy as rx
			 *
			 * REVISIT have observed bit 18 set; huh??
			 */
			/* अगर ((bd->hw_options & CPPI_EOQ_MASK)) */
				musb_ग_लिखोl(&tx_ram->tx_complete, 0, bd->dma);

			/* stop scanning on end-of-segment */
			अगर (bd->hw_next == 0)
				completed = true;
		पूर्ण

		/* on end of segment, maybe go to next one */
		अगर (completed) अणु
			/* cppi_dump_tx(4, tx_ch, "/complete"); */

			/* transfer more, or report completion */
			अगर (tx_ch->offset >= tx_ch->buf_len) अणु
				tx_ch->head = शून्य;
				tx_ch->tail = शून्य;
				tx_ch->channel.status = MUSB_DMA_STATUS_FREE;

				hw_ep = tx_ch->hw_ep;

				musb_dma_completion(musb, index + 1, 1);

			पूर्ण अन्यथा अणु
				/* Bigger transfer than we could fit in
				 * that first batch of descriptors...
				 */
				cppi_next_tx_segment(musb, tx_ch);
			पूर्ण
		पूर्ण अन्यथा
			tx_ch->head = bd;
	पूर्ण

	/* Start processing the RX block */
	क्रम (index = 0; rx; rx = rx >> 1, index++) अणु

		अगर (rx & 1) अणु
			काष्ठा cppi_channel		*rx_ch;

			rx_ch = cppi->rx + index;

			/* let incomplete dma segments finish */
			अगर (!cppi_rx_scan(cppi, index))
				जारी;

			/* start another dma segment अगर needed */
			अगर (rx_ch->channel.actual_len != rx_ch->buf_len
					&& rx_ch->channel.actual_len
						== rx_ch->offset) अणु
				cppi_next_rx_segment(musb, rx_ch, 1);
				जारी;
			पूर्ण

			/* all segments completed! */
			rx_ch->channel.status = MUSB_DMA_STATUS_FREE;

			hw_ep = rx_ch->hw_ep;

			core_rxirq_disable(tibase, index + 1);
			musb_dma_completion(musb, index + 1, 0);
		पूर्ण
	पूर्ण

	/* ग_लिखो to CPPI EOI रेजिस्टर to re-enable पूर्णांकerrupts */
	musb_ग_लिखोl(tibase, DAVINCI_CPPI_EOI_REG, 0);

	अगर (cppi->irq)
		spin_unlock_irqrestore(&musb->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(cppi_पूर्णांकerrupt);

/* Instantiate a software object representing a DMA controller. */
काष्ठा dma_controller *
cppi_dma_controller_create(काष्ठा musb *musb, व्योम __iomem *mregs)
अणु
	काष्ठा cppi		*controller;
	काष्ठा device		*dev = musb->controller;
	काष्ठा platक्रमm_device	*pdev = to_platक्रमm_device(dev);
	पूर्णांक			irq = platक्रमm_get_irq_byname(pdev, "dma");

	controller = kzalloc(माप *controller, GFP_KERNEL);
	अगर (!controller)
		वापस शून्य;

	controller->mregs = mregs;
	controller->tibase = mregs - DAVINCI_BASE_OFFSET;

	controller->controller.musb = musb;
	controller->controller.channel_alloc = cppi_channel_allocate;
	controller->controller.channel_release = cppi_channel_release;
	controller->controller.channel_program = cppi_channel_program;
	controller->controller.channel_पात = cppi_channel_पात;

	/* NOTE: allocating from on-chip SRAM would give the least
	 * contention क्रम memory access, अगर that ever matters here.
	 */

	/* setup BufferPool */
	controller->pool = dma_pool_create("cppi",
			controller->controller.musb->controller,
			माप(काष्ठा cppi_descriptor),
			CPPI_DESCRIPTOR_ALIGN, 0);
	अगर (!controller->pool) अणु
		kमुक्त(controller);
		वापस शून्य;
	पूर्ण

	अगर (irq > 0) अणु
		अगर (request_irq(irq, cppi_पूर्णांकerrupt, 0, "cppi-dma", musb)) अणु
			dev_err(dev, "request_irq %d failed!\n", irq);
			musb_dma_controller_destroy(&controller->controller);
			वापस शून्य;
		पूर्ण
		controller->irq = irq;
	पूर्ण

	cppi_controller_start(controller);
	वापस &controller->controller;
पूर्ण
EXPORT_SYMBOL_GPL(cppi_dma_controller_create);

/*
 *  Destroy a previously-instantiated DMA controller.
 */
व्योम cppi_dma_controller_destroy(काष्ठा dma_controller *c)
अणु
	काष्ठा cppi	*cppi;

	cppi = container_of(c, काष्ठा cppi, controller);

	cppi_controller_stop(cppi);

	अगर (cppi->irq)
		मुक्त_irq(cppi->irq, cppi->controller.musb);

	/* निश्चित:  caller stopped the controller first */
	dma_pool_destroy(cppi->pool);

	kमुक्त(cppi);
पूर्ण
EXPORT_SYMBOL_GPL(cppi_dma_controller_destroy);

/*
 * Context: controller irqlocked, endpoपूर्णांक selected
 */
अटल पूर्णांक cppi_channel_पात(काष्ठा dma_channel *channel)
अणु
	काष्ठा cppi_channel	*cppi_ch;
	काष्ठा cppi		*controller;
	व्योम __iomem		*mbase;
	व्योम __iomem		*tibase;
	व्योम __iomem		*regs;
	u32			value;
	काष्ठा cppi_descriptor	*queue;

	cppi_ch = container_of(channel, काष्ठा cppi_channel, channel);

	controller = cppi_ch->controller;

	चयन (channel->status) अणु
	हाल MUSB_DMA_STATUS_BUS_ABORT:
	हाल MUSB_DMA_STATUS_CORE_ABORT:
		/* from RX or TX fault irq handler */
	हाल MUSB_DMA_STATUS_BUSY:
		/* the hardware needs shutting करोwn */
		regs = cppi_ch->hw_ep->regs;
		अवरोध;
	हाल MUSB_DMA_STATUS_UNKNOWN:
	हाल MUSB_DMA_STATUS_FREE:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!cppi_ch->transmit && cppi_ch->head)
		cppi_dump_rxq(3, "/abort", cppi_ch);

	mbase = controller->mregs;
	tibase = controller->tibase;

	queue = cppi_ch->head;
	cppi_ch->head = शून्य;
	cppi_ch->tail = शून्य;

	/* REVISIT should rely on caller having करोne this,
	 * and caller should rely on us not changing it.
	 * peripheral code is safe ... check host too.
	 */
	musb_ep_select(mbase, cppi_ch->index + 1);

	अगर (cppi_ch->transmit) अणु
		काष्ठा cppi_tx_stateram __iomem *tx_ram;
		/* REVISIT put समयouts on these controller handshakes */

		cppi_dump_tx(6, cppi_ch, " (teardown)");

		/* tearकरोwn DMA engine then usb core */
		करो अणु
			value = musb_पढ़ोl(tibase, DAVINCI_TXCPPI_TEAR_REG);
		पूर्ण जबतक (!(value & CPPI_TEAR_READY));
		musb_ग_लिखोl(tibase, DAVINCI_TXCPPI_TEAR_REG, cppi_ch->index);

		tx_ram = cppi_ch->state_ram;
		करो अणु
			value = musb_पढ़ोl(&tx_ram->tx_complete, 0);
		पूर्ण जबतक (0xFFFFFFFC != value);

		/* FIXME clean up the transfer state ... here?
		 * the completion routine should get called with
		 * an appropriate status code.
		 */

		value = musb_पढ़ोw(regs, MUSB_TXCSR);
		value &= ~MUSB_TXCSR_DMAENAB;
		value |= MUSB_TXCSR_FLUSHFIFO;
		musb_ग_लिखोw(regs, MUSB_TXCSR, value);
		musb_ग_लिखोw(regs, MUSB_TXCSR, value);

		/*
		 * 1. Write to completion Ptr value 0x1(bit 0 set)
		 *    (ग_लिखो back mode)
		 * 2. Wait क्रम पात पूर्णांकerrupt and then put the channel in
		 *    compare mode by writing 1 to the tx_complete रेजिस्टर.
		 */
		cppi_reset_tx(tx_ram, 1);
		cppi_ch->head = शून्य;
		musb_ग_लिखोl(&tx_ram->tx_complete, 0, 1);
		cppi_dump_tx(5, cppi_ch, " (done teardown)");

		/* REVISIT tx side _should_ clean up the same way
		 * as the RX side ... this करोes no cleanup at all!
		 */

	पूर्ण अन्यथा /* RX */ अणु
		u16			csr;

		/* NOTE: करोcs करोn't guarantee any of this works ...  we
		 * expect that अगर the usb core stops telling the cppi core
		 * to pull more data from it, then it'll be safe to flush
		 * current RX DMA state अगरf any pending fअगरo transfer is करोne.
		 */

		core_rxirq_disable(tibase, cppi_ch->index + 1);

		/* क्रम host, ensure ReqPkt is never set again */
		अगर (is_host_active(cppi_ch->controller->controller.musb)) अणु
			value = musb_पढ़ोl(tibase, DAVINCI_AUTOREQ_REG);
			value &= ~((0x3) << (cppi_ch->index * 2));
			musb_ग_लिखोl(tibase, DAVINCI_AUTOREQ_REG, value);
		पूर्ण

		csr = musb_पढ़ोw(regs, MUSB_RXCSR);

		/* क्रम host, clear (just) ReqPkt at end of current packet(s) */
		अगर (is_host_active(cppi_ch->controller->controller.musb)) अणु
			csr |= MUSB_RXCSR_H_WZC_BITS;
			csr &= ~MUSB_RXCSR_H_REQPKT;
		पूर्ण अन्यथा
			csr |= MUSB_RXCSR_P_WZC_BITS;

		/* clear dma enable */
		csr &= ~(MUSB_RXCSR_DMAENAB);
		musb_ग_लिखोw(regs, MUSB_RXCSR, csr);
		csr = musb_पढ़ोw(regs, MUSB_RXCSR);

		/* Quiesce: रुको क्रम current dma to finish (अगर not cleanup).
		 * We can't use bit zero of stateram->rx_sop, since that
		 * refers to an entire "DMA packet" not just emptying the
		 * current fअगरo.  Most segments need multiple usb packets.
		 */
		अगर (channel->status == MUSB_DMA_STATUS_BUSY)
			udelay(50);

		/* scan the current list, reporting any data that was
		 * transferred and acking any IRQ
		 */
		cppi_rx_scan(controller, cppi_ch->index);

		/* clobber the existing state once it's idle
		 *
		 * NOTE:  arguably, we should also रुको क्रम all the other
		 * RX channels to quiesce (how??) and then temporarily
		 * disable RXCPPI_CTRL_REG ... but it seems that we can
		 * rely on the controller restarting from state ram, with
		 * only RXCPPI_BUFCNT state being bogus.  BUFCNT will
		 * correct itself after the next DMA transfer though.
		 *
		 * REVISIT करोes using rndis mode change that?
		 */
		cppi_reset_rx(cppi_ch->state_ram);

		/* next DMA request _should_ load cppi head ptr */

		/* ... we करोn't "free" that list, only mutate it in place.  */
		cppi_dump_rx(5, cppi_ch, " (done abort)");

		/* clean up previously pending bds */
		cppi_bd_मुक्त(cppi_ch, cppi_ch->last_processed);
		cppi_ch->last_processed = शून्य;

		जबतक (queue) अणु
			काष्ठा cppi_descriptor	*पंचांगp = queue->next;

			cppi_bd_मुक्त(cppi_ch, queue);
			queue = पंचांगp;
		पूर्ण
	पूर्ण

	channel->status = MUSB_DMA_STATUS_FREE;
	cppi_ch->buf_dma = 0;
	cppi_ch->offset = 0;
	cppi_ch->buf_len = 0;
	cppi_ch->maxpacket = 0;
	वापस 0;
पूर्ण

/* TBD Queries:
 *
 * Power Management ... probably turn off cppi during suspend, restart;
 * check state ram?  Clocking is presumably shared with usb core.
 */
