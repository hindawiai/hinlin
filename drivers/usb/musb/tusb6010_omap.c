<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TUSB6010 USB 2.0 OTG Dual Role controller OMAP DMA पूर्णांकerface
 *
 * Copyright (C) 2006 Nokia Corporation
 * Tony Lindgren <tony@atomide.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/usb.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmaengine.h>

#समावेश "musb_core.h"
#समावेश "tusb6010.h"

#घोषणा to_chdat(c)		((काष्ठा tusb_omap_dma_ch *)(c)->निजी_data)

#घोषणा MAX_DMAREQ		5	/* REVISIT: Really 6, but req5 not OK */

काष्ठा tusb_dma_data अणु
	s8			dmareq;
	काष्ठा dma_chan		*chan;
पूर्ण;

काष्ठा tusb_omap_dma_ch अणु
	काष्ठा musb		*musb;
	व्योम __iomem		*tbase;
	अचिन्हित दीर्घ		phys_offset;
	पूर्णांक			epnum;
	u8			tx;
	काष्ठा musb_hw_ep	*hw_ep;

	काष्ठा tusb_dma_data	*dma_data;

	काष्ठा tusb_omap_dma	*tusb_dma;

	dma_addr_t		dma_addr;

	u32			len;
	u16			packet_sz;
	u16			transfer_packet_sz;
	u32			transfer_len;
	u32			completed_len;
पूर्ण;

काष्ठा tusb_omap_dma अणु
	काष्ठा dma_controller		controller;
	व्योम __iomem			*tbase;

	काष्ठा tusb_dma_data		dma_pool[MAX_DMAREQ];
	अचिन्हित			multichannel:1;
पूर्ण;

/*
 * Allocate dmareq0 to the current channel unless it's alपढ़ोy taken
 */
अटल अंतरभूत पूर्णांक tusb_omap_use_shared_dmareq(काष्ठा tusb_omap_dma_ch *chdat)
अणु
	u32		reg = musb_पढ़ोl(chdat->tbase, TUSB_DMA_EP_MAP);

	अगर (reg != 0) अणु
		dev_dbg(chdat->musb->controller, "ep%i dmareq0 is busy for ep%i\n",
			chdat->epnum, reg & 0xf);
		वापस -EAGAIN;
	पूर्ण

	अगर (chdat->tx)
		reg = (1 << 4) | chdat->epnum;
	अन्यथा
		reg = chdat->epnum;

	musb_ग_लिखोl(chdat->tbase, TUSB_DMA_EP_MAP, reg);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम tusb_omap_मुक्त_shared_dmareq(काष्ठा tusb_omap_dma_ch *chdat)
अणु
	u32		reg = musb_पढ़ोl(chdat->tbase, TUSB_DMA_EP_MAP);

	अगर ((reg & 0xf) != chdat->epnum) अणु
		prपूर्णांकk(KERN_ERR "ep%i trying to release dmareq0 for ep%i\n",
			chdat->epnum, reg & 0xf);
		वापस;
	पूर्ण
	musb_ग_लिखोl(chdat->tbase, TUSB_DMA_EP_MAP, 0);
पूर्ण

/*
 * See also musb_dma_completion in plat_uds.c and musb_g_[tx|rx]() in
 * musb_gadget.c.
 */
अटल व्योम tusb_omap_dma_cb(व्योम *data)
अणु
	काष्ठा dma_channel	*channel = (काष्ठा dma_channel *)data;
	काष्ठा tusb_omap_dma_ch	*chdat = to_chdat(channel);
	काष्ठा tusb_omap_dma	*tusb_dma = chdat->tusb_dma;
	काष्ठा musb		*musb = chdat->musb;
	काष्ठा device		*dev = musb->controller;
	काष्ठा musb_hw_ep	*hw_ep = chdat->hw_ep;
	व्योम __iomem		*ep_conf = hw_ep->conf;
	व्योम __iomem		*mbase = musb->mregs;
	अचिन्हित दीर्घ		reमुख्यing, flags, pio;

	spin_lock_irqsave(&musb->lock, flags);

	dev_dbg(musb->controller, "ep%i %s dma callback\n",
		chdat->epnum, chdat->tx ? "tx" : "rx");

	अगर (chdat->tx)
		reमुख्यing = musb_पढ़ोl(ep_conf, TUSB_EP_TX_OFFSET);
	अन्यथा
		reमुख्यing = musb_पढ़ोl(ep_conf, TUSB_EP_RX_OFFSET);

	reमुख्यing = TUSB_EP_CONFIG_XFR_SIZE(reमुख्यing);

	/* HW issue #10: XFR_SIZE may get corrupt on DMA (both async & sync) */
	अगर (unlikely(reमुख्यing > chdat->transfer_len)) अणु
		dev_dbg(musb->controller, "Corrupt %s XFR_SIZE: 0x%08lx\n",
			chdat->tx ? "tx" : "rx", reमुख्यing);
		reमुख्यing = 0;
	पूर्ण

	channel->actual_len = chdat->transfer_len - reमुख्यing;
	pio = chdat->len - channel->actual_len;

	dev_dbg(musb->controller, "DMA remaining %lu/%u\n", reमुख्यing, chdat->transfer_len);

	/* Transfer reमुख्यing 1 - 31 bytes */
	अगर (pio > 0 && pio < 32) अणु
		u8	*buf;

		dev_dbg(musb->controller, "Using PIO for remaining %lu bytes\n", pio);
		buf = phys_to_virt((u32)chdat->dma_addr) + chdat->transfer_len;
		अगर (chdat->tx) अणु
			dma_unmap_single(dev, chdat->dma_addr,
						chdat->transfer_len,
						DMA_TO_DEVICE);
			musb_ग_लिखो_fअगरo(hw_ep, pio, buf);
		पूर्ण अन्यथा अणु
			dma_unmap_single(dev, chdat->dma_addr,
						chdat->transfer_len,
						DMA_FROM_DEVICE);
			musb_पढ़ो_fअगरo(hw_ep, pio, buf);
		पूर्ण
		channel->actual_len += pio;
	पूर्ण

	अगर (!tusb_dma->multichannel)
		tusb_omap_मुक्त_shared_dmareq(chdat);

	channel->status = MUSB_DMA_STATUS_FREE;

	musb_dma_completion(musb, chdat->epnum, chdat->tx);

	/* We must terminate लघु tx transfers manually by setting TXPKTRDY.
	 * REVISIT: This same problem may occur with other MUSB dma as well.
	 * Easy to test with g_ether by pinging the MUSB board with ping -s54.
	 */
	अगर ((chdat->transfer_len < chdat->packet_sz)
			|| (chdat->transfer_len % chdat->packet_sz != 0)) अणु
		u16	csr;

		अगर (chdat->tx) अणु
			dev_dbg(musb->controller, "terminating short tx packet\n");
			musb_ep_select(mbase, chdat->epnum);
			csr = musb_पढ़ोw(hw_ep->regs, MUSB_TXCSR);
			csr |= MUSB_TXCSR_MODE | MUSB_TXCSR_TXPKTRDY
				| MUSB_TXCSR_P_WZC_BITS;
			musb_ग_लिखोw(hw_ep->regs, MUSB_TXCSR, csr);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&musb->lock, flags);
पूर्ण

अटल पूर्णांक tusb_omap_dma_program(काष्ठा dma_channel *channel, u16 packet_sz,
				u8 rndis_mode, dma_addr_t dma_addr, u32 len)
अणु
	काष्ठा tusb_omap_dma_ch		*chdat = to_chdat(channel);
	काष्ठा tusb_omap_dma		*tusb_dma = chdat->tusb_dma;
	काष्ठा musb			*musb = chdat->musb;
	काष्ठा device			*dev = musb->controller;
	काष्ठा musb_hw_ep		*hw_ep = chdat->hw_ep;
	व्योम __iomem			*mbase = musb->mregs;
	व्योम __iomem			*ep_conf = hw_ep->conf;
	dma_addr_t			fअगरo_addr = hw_ep->fअगरo_sync;
	u32				dma_reमुख्यing;
	u16				csr;
	u32				psize;
	काष्ठा tusb_dma_data		*dma_data;
	काष्ठा dma_async_tx_descriptor	*dma_desc;
	काष्ठा dma_slave_config		dma_cfg;
	क्रमागत dma_transfer_direction	dma_dir;
	u32				port_winकरोw;
	पूर्णांक				ret;

	अगर (unlikely(dma_addr & 0x1) || (len < 32) || (len > packet_sz))
		वापस false;

	/*
	 * HW issue #10: Async dma will eventually corrupt the XFR_SIZE
	 * रेजिस्टर which will cause missed DMA पूर्णांकerrupt. We could try to
	 * use a समयr क्रम the callback, but it is unsafe as the XFR_SIZE
	 * रेजिस्टर is corrupt, and we won't know अगर the DMA worked.
	 */
	अगर (dma_addr & 0x2)
		वापस false;

	/*
	 * Because of HW issue #10, it seems like mixing sync DMA and async
	 * PIO access can confuse the DMA. Make sure XFR_SIZE is reset beक्रमe
	 * using the channel क्रम DMA.
	 */
	अगर (chdat->tx)
		dma_reमुख्यing = musb_पढ़ोl(ep_conf, TUSB_EP_TX_OFFSET);
	अन्यथा
		dma_reमुख्यing = musb_पढ़ोl(ep_conf, TUSB_EP_RX_OFFSET);

	dma_reमुख्यing = TUSB_EP_CONFIG_XFR_SIZE(dma_reमुख्यing);
	अगर (dma_reमुख्यing) अणु
		dev_dbg(musb->controller, "Busy %s dma, not using: %08x\n",
			chdat->tx ? "tx" : "rx", dma_reमुख्यing);
		वापस false;
	पूर्ण

	chdat->transfer_len = len & ~0x1f;

	अगर (len < packet_sz)
		chdat->transfer_packet_sz = chdat->transfer_len;
	अन्यथा
		chdat->transfer_packet_sz = packet_sz;

	dma_data = chdat->dma_data;
	अगर (!tusb_dma->multichannel) अणु
		अगर (tusb_omap_use_shared_dmareq(chdat) != 0) अणु
			dev_dbg(musb->controller, "could not get dma for ep%i\n", chdat->epnum);
			वापस false;
		पूर्ण
		अगर (dma_data->dmareq < 0) अणु
			/* REVISIT: This should get blocked earlier, happens
			 * with MSC ErrorRecoveryTest
			 */
			WARN_ON(1);
			वापस false;
		पूर्ण
	पूर्ण

	chdat->packet_sz = packet_sz;
	chdat->len = len;
	channel->actual_len = 0;
	chdat->dma_addr = dma_addr;
	channel->status = MUSB_DMA_STATUS_BUSY;

	/* Since we're recycling dma areas, we need to clean or invalidate */
	अगर (chdat->tx) अणु
		dma_dir = DMA_MEM_TO_DEV;
		dma_map_single(dev, phys_to_virt(dma_addr), len,
				DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		dma_dir = DMA_DEV_TO_MEM;
		dma_map_single(dev, phys_to_virt(dma_addr), len,
				DMA_FROM_DEVICE);
	पूर्ण

	स_रखो(&dma_cfg, 0, माप(dma_cfg));

	/* Use 16-bit transfer अगर dma_addr is not 32-bit aligned */
	अगर ((dma_addr & 0x3) == 0) अणु
		dma_cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		dma_cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		port_winकरोw = 8;
	पूर्ण अन्यथा अणु
		dma_cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		dma_cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		port_winकरोw = 16;

		fअगरo_addr = hw_ep->fअगरo_async;
	पूर्ण

	dev_dbg(musb->controller,
		"ep%i %s dma: %pad len: %u(%u) packet_sz: %i(%i)\n",
		chdat->epnum, chdat->tx ? "tx" : "rx", &dma_addr,
		chdat->transfer_len, len, chdat->transfer_packet_sz, packet_sz);

	dma_cfg.src_addr = fअगरo_addr;
	dma_cfg.dst_addr = fअगरo_addr;
	dma_cfg.src_port_winकरोw_size = port_winकरोw;
	dma_cfg.src_maxburst = port_winकरोw;
	dma_cfg.dst_port_winकरोw_size = port_winकरोw;
	dma_cfg.dst_maxburst = port_winकरोw;

	ret = dmaengine_slave_config(dma_data->chan, &dma_cfg);
	अगर (ret) अणु
		dev_err(musb->controller, "DMA slave config failed: %d\n", ret);
		वापस false;
	पूर्ण

	dma_desc = dmaengine_prep_slave_single(dma_data->chan, dma_addr,
					chdat->transfer_len, dma_dir,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!dma_desc) अणु
		dev_err(musb->controller, "DMA prep_slave_single failed\n");
		वापस false;
	पूर्ण

	dma_desc->callback = tusb_omap_dma_cb;
	dma_desc->callback_param = channel;
	dmaengine_submit(dma_desc);

	dev_dbg(musb->controller,
		"ep%i %s using %i-bit %s dma from %pad to %pad\n",
		chdat->epnum, chdat->tx ? "tx" : "rx",
		dma_cfg.src_addr_width * 8,
		((dma_addr & 0x3) == 0) ? "sync" : "async",
		(dma_dir == DMA_MEM_TO_DEV) ? &dma_addr : &fअगरo_addr,
		(dma_dir == DMA_MEM_TO_DEV) ? &fअगरo_addr : &dma_addr);

	/*
	 * Prepare MUSB क्रम DMA transfer
	 */
	musb_ep_select(mbase, chdat->epnum);
	अगर (chdat->tx) अणु
		csr = musb_पढ़ोw(hw_ep->regs, MUSB_TXCSR);
		csr |= (MUSB_TXCSR_AUTOSET | MUSB_TXCSR_DMAENAB
			| MUSB_TXCSR_DMAMODE | MUSB_TXCSR_MODE);
		csr &= ~MUSB_TXCSR_P_UNDERRUN;
		musb_ग_लिखोw(hw_ep->regs, MUSB_TXCSR, csr);
	पूर्ण अन्यथा अणु
		csr = musb_पढ़ोw(hw_ep->regs, MUSB_RXCSR);
		csr |= MUSB_RXCSR_DMAENAB;
		csr &= ~(MUSB_RXCSR_AUTOCLEAR | MUSB_RXCSR_DMAMODE);
		musb_ग_लिखोw(hw_ep->regs, MUSB_RXCSR,
			csr | MUSB_RXCSR_P_WZC_BITS);
	पूर्ण

	/* Start DMA transfer */
	dma_async_issue_pending(dma_data->chan);

	अगर (chdat->tx) अणु
		/* Send transfer_packet_sz packets at a समय */
		psize = musb_पढ़ोl(ep_conf, TUSB_EP_MAX_PACKET_SIZE_OFFSET);
		psize &= ~0x7ff;
		psize |= chdat->transfer_packet_sz;
		musb_ग_लिखोl(ep_conf, TUSB_EP_MAX_PACKET_SIZE_OFFSET, psize);

		musb_ग_लिखोl(ep_conf, TUSB_EP_TX_OFFSET,
			TUSB_EP_CONFIG_XFR_SIZE(chdat->transfer_len));
	पूर्ण अन्यथा अणु
		/* Receive transfer_packet_sz packets at a समय */
		psize = musb_पढ़ोl(ep_conf, TUSB_EP_MAX_PACKET_SIZE_OFFSET);
		psize &= ~(0x7ff << 16);
		psize |= (chdat->transfer_packet_sz << 16);
		musb_ग_लिखोl(ep_conf, TUSB_EP_MAX_PACKET_SIZE_OFFSET, psize);

		musb_ग_लिखोl(ep_conf, TUSB_EP_RX_OFFSET,
			TUSB_EP_CONFIG_XFR_SIZE(chdat->transfer_len));
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक tusb_omap_dma_पात(काष्ठा dma_channel *channel)
अणु
	काष्ठा tusb_omap_dma_ch	*chdat = to_chdat(channel);

	अगर (chdat->dma_data)
		dmaengine_terminate_all(chdat->dma_data->chan);

	channel->status = MUSB_DMA_STATUS_FREE;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक tusb_omap_dma_allocate_dmareq(काष्ठा tusb_omap_dma_ch *chdat)
अणु
	u32		reg = musb_पढ़ोl(chdat->tbase, TUSB_DMA_EP_MAP);
	पूर्णांक		i, dmareq_nr = -1;

	क्रम (i = 0; i < MAX_DMAREQ; i++) अणु
		पूर्णांक cur = (reg & (0xf << (i * 5))) >> (i * 5);
		अगर (cur == 0) अणु
			dmareq_nr = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (dmareq_nr == -1)
		वापस -EAGAIN;

	reg |= (chdat->epnum << (dmareq_nr * 5));
	अगर (chdat->tx)
		reg |= ((1 << 4) << (dmareq_nr * 5));
	musb_ग_लिखोl(chdat->tbase, TUSB_DMA_EP_MAP, reg);

	chdat->dma_data = &chdat->tusb_dma->dma_pool[dmareq_nr];

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम tusb_omap_dma_मुक्त_dmareq(काष्ठा tusb_omap_dma_ch *chdat)
अणु
	u32 reg;

	अगर (!chdat || !chdat->dma_data || chdat->dma_data->dmareq < 0)
		वापस;

	reg = musb_पढ़ोl(chdat->tbase, TUSB_DMA_EP_MAP);
	reg &= ~(0x1f << (chdat->dma_data->dmareq * 5));
	musb_ग_लिखोl(chdat->tbase, TUSB_DMA_EP_MAP, reg);

	chdat->dma_data = शून्य;
पूर्ण

अटल काष्ठा dma_channel *dma_channel_pool[MAX_DMAREQ];

अटल काष्ठा dma_channel *
tusb_omap_dma_allocate(काष्ठा dma_controller *c,
		काष्ठा musb_hw_ep *hw_ep,
		u8 tx)
अणु
	पूर्णांक ret, i;
	काष्ठा tusb_omap_dma	*tusb_dma;
	काष्ठा musb		*musb;
	काष्ठा dma_channel	*channel = शून्य;
	काष्ठा tusb_omap_dma_ch	*chdat = शून्य;
	काष्ठा tusb_dma_data	*dma_data = शून्य;

	tusb_dma = container_of(c, काष्ठा tusb_omap_dma, controller);
	musb = tusb_dma->controller.musb;

	/* REVISIT: Why करोes dmareq5 not work? */
	अगर (hw_ep->epnum == 0) अणु
		dev_dbg(musb->controller, "Not allowing DMA for ep0 %s\n", tx ? "tx" : "rx");
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < MAX_DMAREQ; i++) अणु
		काष्ठा dma_channel *ch = dma_channel_pool[i];
		अगर (ch->status == MUSB_DMA_STATUS_UNKNOWN) अणु
			ch->status = MUSB_DMA_STATUS_FREE;
			channel = ch;
			chdat = ch->निजी_data;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!channel)
		वापस शून्य;

	chdat->musb = tusb_dma->controller.musb;
	chdat->tbase = tusb_dma->tbase;
	chdat->hw_ep = hw_ep;
	chdat->epnum = hw_ep->epnum;
	chdat->completed_len = 0;
	chdat->tusb_dma = tusb_dma;
	अगर (tx)
		chdat->tx = 1;
	अन्यथा
		chdat->tx = 0;

	channel->max_len = 0x7fffffff;
	channel->desired_mode = 0;
	channel->actual_len = 0;

	अगर (!chdat->dma_data) अणु
		अगर (tusb_dma->multichannel) अणु
			ret = tusb_omap_dma_allocate_dmareq(chdat);
			अगर (ret != 0)
				जाओ मुक्त_dmareq;
		पूर्ण अन्यथा अणु
			chdat->dma_data = &tusb_dma->dma_pool[0];
		पूर्ण
	पूर्ण

	dma_data = chdat->dma_data;

	dev_dbg(musb->controller, "ep%i %s dma: %s dmareq%i\n",
		chdat->epnum,
		chdat->tx ? "tx" : "rx",
		tusb_dma->multichannel ? "shared" : "dedicated",
		dma_data->dmareq);

	वापस channel;

मुक्त_dmareq:
	tusb_omap_dma_मुक्त_dmareq(chdat);

	dev_dbg(musb->controller, "ep%i: Could not get a DMA channel\n", chdat->epnum);
	channel->status = MUSB_DMA_STATUS_UNKNOWN;

	वापस शून्य;
पूर्ण

अटल व्योम tusb_omap_dma_release(काष्ठा dma_channel *channel)
अणु
	काष्ठा tusb_omap_dma_ch	*chdat = to_chdat(channel);
	काष्ठा musb		*musb = chdat->musb;

	dev_dbg(musb->controller, "Release for ep%i\n", chdat->epnum);

	channel->status = MUSB_DMA_STATUS_UNKNOWN;

	dmaengine_terminate_sync(chdat->dma_data->chan);
	tusb_omap_dma_मुक्त_dmareq(chdat);

	channel = शून्य;
पूर्ण

व्योम tusb_dma_controller_destroy(काष्ठा dma_controller *c)
अणु
	काष्ठा tusb_omap_dma	*tusb_dma;
	पूर्णांक			i;

	tusb_dma = container_of(c, काष्ठा tusb_omap_dma, controller);
	क्रम (i = 0; i < MAX_DMAREQ; i++) अणु
		काष्ठा dma_channel *ch = dma_channel_pool[i];
		अगर (ch) अणु
			kमुक्त(ch->निजी_data);
			kमुक्त(ch);
		पूर्ण

		/* Free up the DMA channels */
		अगर (tusb_dma && tusb_dma->dma_pool[i].chan)
			dma_release_channel(tusb_dma->dma_pool[i].chan);
	पूर्ण

	kमुक्त(tusb_dma);
पूर्ण
EXPORT_SYMBOL_GPL(tusb_dma_controller_destroy);

अटल पूर्णांक tusb_omap_allocate_dma_pool(काष्ठा tusb_omap_dma *tusb_dma)
अणु
	काष्ठा musb *musb = tusb_dma->controller.musb;
	पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < MAX_DMAREQ; i++) अणु
		काष्ठा tusb_dma_data *dma_data = &tusb_dma->dma_pool[i];

		/*
		 * Request DMA channels:
		 * - one channel in हाल of non multichannel mode
		 * - MAX_DMAREQ number of channels in multichannel mode
		 */
		अगर (i == 0 || tusb_dma->multichannel) अणु
			अक्षर ch_name[8];

			प्र_लिखो(ch_name, "dmareq%d", i);
			dma_data->chan = dma_request_chan(musb->controller,
							  ch_name);
			अगर (IS_ERR(dma_data->chan)) अणु
				dev_err(musb->controller,
					"Failed to request %s\n", ch_name);
				ret = PTR_ERR(dma_data->chan);
				जाओ dma_error;
			पूर्ण

			dma_data->dmareq = i;
		पूर्ण अन्यथा अणु
			dma_data->dmareq = -1;
		पूर्ण
	पूर्ण

	वापस 0;

dma_error:
	क्रम (; i >= 0; i--) अणु
		काष्ठा tusb_dma_data *dma_data = &tusb_dma->dma_pool[i];

		अगर (dma_data->dmareq >= 0)
			dma_release_channel(dma_data->chan);
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा dma_controller *
tusb_dma_controller_create(काष्ठा musb *musb, व्योम __iomem *base)
अणु
	व्योम __iomem		*tbase = musb->ctrl_base;
	काष्ठा tusb_omap_dma	*tusb_dma;
	पूर्णांक			i;

	/* REVISIT: Get dmareq lines used from board-*.c */

	musb_ग_लिखोl(musb->ctrl_base, TUSB_DMA_INT_MASK, 0x7fffffff);
	musb_ग_लिखोl(musb->ctrl_base, TUSB_DMA_EP_MAP, 0);

	musb_ग_लिखोl(tbase, TUSB_DMA_REQ_CONF,
		TUSB_DMA_REQ_CONF_BURST_SIZE(2)
		| TUSB_DMA_REQ_CONF_DMA_REQ_EN(0x3f)
		| TUSB_DMA_REQ_CONF_DMA_REQ_ASSER(2));

	tusb_dma = kzalloc(माप(काष्ठा tusb_omap_dma), GFP_KERNEL);
	अगर (!tusb_dma)
		जाओ out;

	tusb_dma->controller.musb = musb;
	tusb_dma->tbase = musb->ctrl_base;

	tusb_dma->controller.channel_alloc = tusb_omap_dma_allocate;
	tusb_dma->controller.channel_release = tusb_omap_dma_release;
	tusb_dma->controller.channel_program = tusb_omap_dma_program;
	tusb_dma->controller.channel_पात = tusb_omap_dma_पात;

	अगर (musb->tusb_revision >= TUSB_REV_30)
		tusb_dma->multichannel = 1;

	क्रम (i = 0; i < MAX_DMAREQ; i++) अणु
		काष्ठा dma_channel	*ch;
		काष्ठा tusb_omap_dma_ch	*chdat;

		ch = kzalloc(माप(काष्ठा dma_channel), GFP_KERNEL);
		अगर (!ch)
			जाओ cleanup;

		dma_channel_pool[i] = ch;

		chdat = kzalloc(माप(काष्ठा tusb_omap_dma_ch), GFP_KERNEL);
		अगर (!chdat)
			जाओ cleanup;

		ch->status = MUSB_DMA_STATUS_UNKNOWN;
		ch->निजी_data = chdat;
	पूर्ण

	अगर (tusb_omap_allocate_dma_pool(tusb_dma))
		जाओ cleanup;

	वापस &tusb_dma->controller;

cleanup:
	musb_dma_controller_destroy(&tusb_dma->controller);
out:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(tusb_dma_controller_create);
