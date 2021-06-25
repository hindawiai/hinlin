<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/sizes.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>

#समावेश "cppi_dma.h"
#समावेश "musb_core.h"
#समावेश "musb_trace.h"

#घोषणा RNDIS_REG(x) (0x80 + ((x - 1) * 4))

#घोषणा EP_MODE_AUTOREQ_NONE		0
#घोषणा EP_MODE_AUTOREQ_ALL_NEOP	1
#घोषणा EP_MODE_AUTOREQ_ALWAYS		3

#घोषणा EP_MODE_DMA_TRANSPARENT		0
#घोषणा EP_MODE_DMA_RNDIS		1
#घोषणा EP_MODE_DMA_GEN_RNDIS		3

#घोषणा USB_CTRL_TX_MODE	0x70
#घोषणा USB_CTRL_RX_MODE	0x74
#घोषणा USB_CTRL_AUTOREQ	0xd0
#घोषणा USB_TDOWN		0xd8

#घोषणा MUSB_DMA_NUM_CHANNELS 15

#घोषणा DA8XX_USB_MODE		0x10
#घोषणा DA8XX_USB_AUTOREQ	0x14
#घोषणा DA8XX_USB_TEARDOWN	0x1c

#घोषणा DA8XX_DMA_NUM_CHANNELS 4

काष्ठा cppi41_dma_controller अणु
	काष्ठा dma_controller controller;
	काष्ठा cppi41_dma_channel *rx_channel;
	काष्ठा cppi41_dma_channel *tx_channel;
	काष्ठा hrसमयr early_tx;
	काष्ठा list_head early_tx_list;
	u32 rx_mode;
	u32 tx_mode;
	u32 स्वतः_req;

	u32 tकरोwn_reg;
	u32 स्वतःreq_reg;

	व्योम (*set_dma_mode)(काष्ठा cppi41_dma_channel *cppi41_channel,
			     अचिन्हित पूर्णांक mode);
	u8 num_channels;
पूर्ण;

अटल व्योम save_rx_toggle(काष्ठा cppi41_dma_channel *cppi41_channel)
अणु
	u16 csr;
	u8 toggle;

	अगर (cppi41_channel->is_tx)
		वापस;
	अगर (!is_host_active(cppi41_channel->controller->controller.musb))
		वापस;

	csr = musb_पढ़ोw(cppi41_channel->hw_ep->regs, MUSB_RXCSR);
	toggle = csr & MUSB_RXCSR_H_DATATOGGLE ? 1 : 0;

	cppi41_channel->usb_toggle = toggle;
पूर्ण

अटल व्योम update_rx_toggle(काष्ठा cppi41_dma_channel *cppi41_channel)
अणु
	काष्ठा musb_hw_ep *hw_ep = cppi41_channel->hw_ep;
	काष्ठा musb *musb = hw_ep->musb;
	u16 csr;
	u8 toggle;

	अगर (cppi41_channel->is_tx)
		वापस;
	अगर (!is_host_active(musb))
		वापस;

	musb_ep_select(musb->mregs, hw_ep->epnum);
	csr = musb_पढ़ोw(hw_ep->regs, MUSB_RXCSR);
	toggle = csr & MUSB_RXCSR_H_DATATOGGLE ? 1 : 0;

	/*
	 * AM335x Advisory 1.0.13: Due to पूर्णांकernal synchronisation error the
	 * data toggle may reset from DATA1 to DATA0 during receiving data from
	 * more than one endpoपूर्णांक.
	 */
	अगर (!toggle && toggle == cppi41_channel->usb_toggle) अणु
		csr |= MUSB_RXCSR_H_DATATOGGLE | MUSB_RXCSR_H_WR_DATATOGGLE;
		musb_ग_लिखोw(cppi41_channel->hw_ep->regs, MUSB_RXCSR, csr);
		musb_dbg(musb, "Restoring DATA1 toggle.");
	पूर्ण

	cppi41_channel->usb_toggle = toggle;
पूर्ण

अटल bool musb_is_tx_fअगरo_empty(काष्ठा musb_hw_ep *hw_ep)
अणु
	u8		epnum = hw_ep->epnum;
	काष्ठा musb	*musb = hw_ep->musb;
	व्योम __iomem	*epio = musb->endpoपूर्णांकs[epnum].regs;
	u16		csr;

	musb_ep_select(musb->mregs, hw_ep->epnum);
	csr = musb_पढ़ोw(epio, MUSB_TXCSR);
	अगर (csr & MUSB_TXCSR_TXPKTRDY)
		वापस false;
	वापस true;
पूर्ण

अटल व्योम cppi41_dma_callback(व्योम *निजी_data,
				स्थिर काष्ठा dmaengine_result *result);

अटल व्योम cppi41_trans_करोne(काष्ठा cppi41_dma_channel *cppi41_channel)
अणु
	काष्ठा musb_hw_ep *hw_ep = cppi41_channel->hw_ep;
	काष्ठा musb *musb = hw_ep->musb;
	व्योम __iomem *epio = hw_ep->regs;
	u16 csr;

	अगर (!cppi41_channel->prog_len ||
	    (cppi41_channel->channel.status == MUSB_DMA_STATUS_FREE)) अणु

		/* करोne, complete */
		cppi41_channel->channel.actual_len =
			cppi41_channel->transferred;
		cppi41_channel->channel.status = MUSB_DMA_STATUS_FREE;
		cppi41_channel->channel.rx_packet_करोne = true;

		/*
		 * transmit ZLP using PIO mode क्रम transfers which size is
		 * multiple of EP packet size.
		 */
		अगर (cppi41_channel->tx_zlp && (cppi41_channel->transferred %
					cppi41_channel->packet_sz) == 0) अणु
			musb_ep_select(musb->mregs, hw_ep->epnum);
			csr = MUSB_TXCSR_MODE | MUSB_TXCSR_TXPKTRDY;
			musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
		पूर्ण

		trace_musb_cppi41_करोne(cppi41_channel);
		musb_dma_completion(musb, hw_ep->epnum, cppi41_channel->is_tx);
	पूर्ण अन्यथा अणु
		/* next iteration, reload */
		काष्ठा dma_chan *dc = cppi41_channel->dc;
		काष्ठा dma_async_tx_descriptor *dma_desc;
		क्रमागत dma_transfer_direction direction;
		u32 reमुख्य_bytes;

		cppi41_channel->buf_addr += cppi41_channel->packet_sz;

		reमुख्य_bytes = cppi41_channel->total_len;
		reमुख्य_bytes -= cppi41_channel->transferred;
		reमुख्य_bytes = min(reमुख्य_bytes, cppi41_channel->packet_sz);
		cppi41_channel->prog_len = reमुख्य_bytes;

		direction = cppi41_channel->is_tx ? DMA_MEM_TO_DEV
			: DMA_DEV_TO_MEM;
		dma_desc = dmaengine_prep_slave_single(dc,
				cppi41_channel->buf_addr,
				reमुख्य_bytes,
				direction,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (WARN_ON(!dma_desc))
			वापस;

		dma_desc->callback_result = cppi41_dma_callback;
		dma_desc->callback_param = &cppi41_channel->channel;
		cppi41_channel->cookie = dma_desc->tx_submit(dma_desc);
		trace_musb_cppi41_cont(cppi41_channel);
		dma_async_issue_pending(dc);

		अगर (!cppi41_channel->is_tx) अणु
			musb_ep_select(musb->mregs, hw_ep->epnum);
			csr = musb_पढ़ोw(epio, MUSB_RXCSR);
			csr |= MUSB_RXCSR_H_REQPKT;
			musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
		पूर्ण
	पूर्ण
पूर्ण

अटल क्रमागत hrसमयr_restart cppi41_recheck_tx_req(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा cppi41_dma_controller *controller;
	काष्ठा cppi41_dma_channel *cppi41_channel, *n;
	काष्ठा musb *musb;
	अचिन्हित दीर्घ flags;
	क्रमागत hrसमयr_restart ret = HRTIMER_NORESTART;

	controller = container_of(समयr, काष्ठा cppi41_dma_controller,
			early_tx);
	musb = controller->controller.musb;

	spin_lock_irqsave(&musb->lock, flags);
	list_क्रम_each_entry_safe(cppi41_channel, n, &controller->early_tx_list,
			tx_check) अणु
		bool empty;
		काष्ठा musb_hw_ep *hw_ep = cppi41_channel->hw_ep;

		empty = musb_is_tx_fअगरo_empty(hw_ep);
		अगर (empty) अणु
			list_del_init(&cppi41_channel->tx_check);
			cppi41_trans_करोne(cppi41_channel);
		पूर्ण
	पूर्ण

	अगर (!list_empty(&controller->early_tx_list) &&
	    !hrसमयr_is_queued(&controller->early_tx)) अणु
		ret = HRTIMER_RESTART;
		hrसमयr_क्रमward_now(&controller->early_tx, 20 * NSEC_PER_USEC);
	पूर्ण

	spin_unlock_irqrestore(&musb->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम cppi41_dma_callback(व्योम *निजी_data,
				स्थिर काष्ठा dmaengine_result *result)
अणु
	काष्ठा dma_channel *channel = निजी_data;
	काष्ठा cppi41_dma_channel *cppi41_channel = channel->निजी_data;
	काष्ठा musb_hw_ep *hw_ep = cppi41_channel->hw_ep;
	काष्ठा cppi41_dma_controller *controller;
	काष्ठा musb *musb = hw_ep->musb;
	अचिन्हित दीर्घ flags;
	काष्ठा dma_tx_state txstate;
	u32 transferred;
	पूर्णांक is_hs = 0;
	bool empty;

	controller = cppi41_channel->controller;
	अगर (controller->controller.dma_callback)
		controller->controller.dma_callback(&controller->controller);

	अगर (result->result == DMA_TRANS_ABORTED)
		वापस;

	spin_lock_irqsave(&musb->lock, flags);

	dmaengine_tx_status(cppi41_channel->dc, cppi41_channel->cookie,
			&txstate);
	transferred = cppi41_channel->prog_len - txstate.residue;
	cppi41_channel->transferred += transferred;

	trace_musb_cppi41_gb(cppi41_channel);
	update_rx_toggle(cppi41_channel);

	अगर (cppi41_channel->transferred == cppi41_channel->total_len ||
			transferred < cppi41_channel->packet_sz)
		cppi41_channel->prog_len = 0;

	अगर (cppi41_channel->is_tx) अणु
		u8 type;

		अगर (is_host_active(musb))
			type = hw_ep->out_qh->type;
		अन्यथा
			type = hw_ep->ep_in.type;

		अगर (type == USB_ENDPOINT_XFER_ISOC)
			/*
			 * Don't use the early-TX-पूर्णांकerrupt workaround below
			 * क्रम Isoch transfter. Since Isoch are periodic
			 * transfer, by the समय the next transfer is
			 * scheduled, the current one should be करोne alपढ़ोy.
			 *
			 * This aव्योमs audio playback underrun issue.
			 */
			empty = true;
		अन्यथा
			empty = musb_is_tx_fअगरo_empty(hw_ep);
	पूर्ण

	अगर (!cppi41_channel->is_tx || empty) अणु
		cppi41_trans_करोne(cppi41_channel);
		जाओ out;
	पूर्ण

	/*
	 * On AM335x it has been observed that the TX पूर्णांकerrupt fires
	 * too early that means the TXFIFO is not yet empty but the DMA
	 * engine says that it is करोne with the transfer. We करोn't
	 * receive a FIFO empty पूर्णांकerrupt so the only thing we can करो is
	 * to poll क्रम the bit. On HS it usually takes 2us, on FS around
	 * 110us - 150us depending on the transfer size.
	 * We spin on HS (no दीर्घer than than 25us and setup a समयr on
	 * FS to check क्रम the bit and complete the transfer.
	 */
	अगर (is_host_active(musb)) अणु
		अगर (musb->port1_status & USB_PORT_STAT_HIGH_SPEED)
			is_hs = 1;
	पूर्ण अन्यथा अणु
		अगर (musb->g.speed == USB_SPEED_HIGH)
			is_hs = 1;
	पूर्ण
	अगर (is_hs) अणु
		अचिन्हित रुको = 25;

		करो अणु
			empty = musb_is_tx_fअगरo_empty(hw_ep);
			अगर (empty) अणु
				cppi41_trans_करोne(cppi41_channel);
				जाओ out;
			पूर्ण
			रुको--;
			अगर (!रुको)
				अवरोध;
			cpu_relax();
		पूर्ण जबतक (1);
	पूर्ण
	list_add_tail(&cppi41_channel->tx_check,
			&controller->early_tx_list);
	अगर (!hrसमयr_is_queued(&controller->early_tx)) अणु
		अचिन्हित दीर्घ usecs = cppi41_channel->total_len / 10;

		hrसमयr_start_range_ns(&controller->early_tx,
				       usecs * NSEC_PER_USEC,
				       20 * NSEC_PER_USEC,
				       HRTIMER_MODE_REL);
	पूर्ण

out:
	spin_unlock_irqrestore(&musb->lock, flags);
पूर्ण

अटल u32 update_ep_mode(अचिन्हित ep, अचिन्हित mode, u32 old)
अणु
	अचिन्हित shअगरt;

	shअगरt = (ep - 1) * 2;
	old &= ~(3 << shअगरt);
	old |= mode << shअगरt;
	वापस old;
पूर्ण

अटल व्योम cppi41_set_dma_mode(काष्ठा cppi41_dma_channel *cppi41_channel,
		अचिन्हित mode)
अणु
	काष्ठा cppi41_dma_controller *controller = cppi41_channel->controller;
	काष्ठा musb *musb = controller->controller.musb;
	u32 port;
	u32 new_mode;
	u32 old_mode;

	अगर (cppi41_channel->is_tx)
		old_mode = controller->tx_mode;
	अन्यथा
		old_mode = controller->rx_mode;
	port = cppi41_channel->port_num;
	new_mode = update_ep_mode(port, mode, old_mode);

	अगर (new_mode == old_mode)
		वापस;
	अगर (cppi41_channel->is_tx) अणु
		controller->tx_mode = new_mode;
		musb_ग_लिखोl(musb->ctrl_base, USB_CTRL_TX_MODE, new_mode);
	पूर्ण अन्यथा अणु
		controller->rx_mode = new_mode;
		musb_ग_लिखोl(musb->ctrl_base, USB_CTRL_RX_MODE, new_mode);
	पूर्ण
पूर्ण

अटल व्योम da8xx_set_dma_mode(काष्ठा cppi41_dma_channel *cppi41_channel,
		अचिन्हित पूर्णांक mode)
अणु
	काष्ठा cppi41_dma_controller *controller = cppi41_channel->controller;
	काष्ठा musb *musb = controller->controller.musb;
	अचिन्हित पूर्णांक shअगरt;
	u32 port;
	u32 new_mode;
	u32 old_mode;

	old_mode = controller->tx_mode;
	port = cppi41_channel->port_num;

	shअगरt = (port - 1) * 4;
	अगर (!cppi41_channel->is_tx)
		shअगरt += 16;
	new_mode = old_mode & ~(3 << shअगरt);
	new_mode |= mode << shअगरt;

	अगर (new_mode == old_mode)
		वापस;
	controller->tx_mode = new_mode;
	musb_ग_लिखोl(musb->ctrl_base, DA8XX_USB_MODE, new_mode);
पूर्ण


अटल व्योम cppi41_set_स्वतःreq_mode(काष्ठा cppi41_dma_channel *cppi41_channel,
		अचिन्हित mode)
अणु
	काष्ठा cppi41_dma_controller *controller = cppi41_channel->controller;
	u32 port;
	u32 new_mode;
	u32 old_mode;

	old_mode = controller->स्वतः_req;
	port = cppi41_channel->port_num;
	new_mode = update_ep_mode(port, mode, old_mode);

	अगर (new_mode == old_mode)
		वापस;
	controller->स्वतः_req = new_mode;
	musb_ग_लिखोl(controller->controller.musb->ctrl_base,
		    controller->स्वतःreq_reg, new_mode);
पूर्ण

अटल bool cppi41_configure_channel(काष्ठा dma_channel *channel,
				u16 packet_sz, u8 mode,
				dma_addr_t dma_addr, u32 len)
अणु
	काष्ठा cppi41_dma_channel *cppi41_channel = channel->निजी_data;
	काष्ठा cppi41_dma_controller *controller = cppi41_channel->controller;
	काष्ठा dma_chan *dc = cppi41_channel->dc;
	काष्ठा dma_async_tx_descriptor *dma_desc;
	क्रमागत dma_transfer_direction direction;
	काष्ठा musb *musb = cppi41_channel->controller->controller.musb;
	अचिन्हित use_gen_rndis = 0;

	cppi41_channel->buf_addr = dma_addr;
	cppi41_channel->total_len = len;
	cppi41_channel->transferred = 0;
	cppi41_channel->packet_sz = packet_sz;
	cppi41_channel->tx_zlp = (cppi41_channel->is_tx && mode) ? 1 : 0;

	/*
	 * Due to AM335x' Advisory 1.0.13 we are not allowed to transfer more
	 * than max packet size at a समय.
	 */
	अगर (cppi41_channel->is_tx)
		use_gen_rndis = 1;

	अगर (use_gen_rndis) अणु
		/* RNDIS mode */
		अगर (len > packet_sz) अणु
			musb_ग_लिखोl(musb->ctrl_base,
				RNDIS_REG(cppi41_channel->port_num), len);
			/* gen rndis */
			controller->set_dma_mode(cppi41_channel,
					EP_MODE_DMA_GEN_RNDIS);

			/* स्वतः req */
			cppi41_set_स्वतःreq_mode(cppi41_channel,
					EP_MODE_AUTOREQ_ALL_NEOP);
		पूर्ण अन्यथा अणु
			musb_ग_लिखोl(musb->ctrl_base,
					RNDIS_REG(cppi41_channel->port_num), 0);
			controller->set_dma_mode(cppi41_channel,
					EP_MODE_DMA_TRANSPARENT);
			cppi41_set_स्वतःreq_mode(cppi41_channel,
					EP_MODE_AUTOREQ_NONE);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* fallback mode */
		controller->set_dma_mode(cppi41_channel,
				EP_MODE_DMA_TRANSPARENT);
		cppi41_set_स्वतःreq_mode(cppi41_channel, EP_MODE_AUTOREQ_NONE);
		len = min_t(u32, packet_sz, len);
	पूर्ण
	cppi41_channel->prog_len = len;
	direction = cppi41_channel->is_tx ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;
	dma_desc = dmaengine_prep_slave_single(dc, dma_addr, len, direction,
			DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!dma_desc)
		वापस false;

	dma_desc->callback_result = cppi41_dma_callback;
	dma_desc->callback_param = channel;
	cppi41_channel->cookie = dma_desc->tx_submit(dma_desc);
	cppi41_channel->channel.rx_packet_करोne = false;

	trace_musb_cppi41_config(cppi41_channel);

	save_rx_toggle(cppi41_channel);
	dma_async_issue_pending(dc);
	वापस true;
पूर्ण

अटल काष्ठा dma_channel *cppi41_dma_channel_allocate(काष्ठा dma_controller *c,
				काष्ठा musb_hw_ep *hw_ep, u8 is_tx)
अणु
	काष्ठा cppi41_dma_controller *controller = container_of(c,
			काष्ठा cppi41_dma_controller, controller);
	काष्ठा cppi41_dma_channel *cppi41_channel = शून्य;
	u8 ch_num = hw_ep->epnum - 1;

	अगर (ch_num >= controller->num_channels)
		वापस शून्य;

	अगर (is_tx)
		cppi41_channel = &controller->tx_channel[ch_num];
	अन्यथा
		cppi41_channel = &controller->rx_channel[ch_num];

	अगर (!cppi41_channel->dc)
		वापस शून्य;

	अगर (cppi41_channel->is_allocated)
		वापस शून्य;

	cppi41_channel->hw_ep = hw_ep;
	cppi41_channel->is_allocated = 1;

	trace_musb_cppi41_alloc(cppi41_channel);
	वापस &cppi41_channel->channel;
पूर्ण

अटल व्योम cppi41_dma_channel_release(काष्ठा dma_channel *channel)
अणु
	काष्ठा cppi41_dma_channel *cppi41_channel = channel->निजी_data;

	trace_musb_cppi41_मुक्त(cppi41_channel);
	अगर (cppi41_channel->is_allocated) अणु
		cppi41_channel->is_allocated = 0;
		channel->status = MUSB_DMA_STATUS_FREE;
		channel->actual_len = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक cppi41_dma_channel_program(काष्ठा dma_channel *channel,
				u16 packet_sz, u8 mode,
				dma_addr_t dma_addr, u32 len)
अणु
	पूर्णांक ret;
	काष्ठा cppi41_dma_channel *cppi41_channel = channel->निजी_data;
	पूर्णांक hb_mult = 0;

	BUG_ON(channel->status == MUSB_DMA_STATUS_UNKNOWN ||
		channel->status == MUSB_DMA_STATUS_BUSY);

	अगर (is_host_active(cppi41_channel->controller->controller.musb)) अणु
		अगर (cppi41_channel->is_tx)
			hb_mult = cppi41_channel->hw_ep->out_qh->hb_mult;
		अन्यथा
			hb_mult = cppi41_channel->hw_ep->in_qh->hb_mult;
	पूर्ण

	channel->status = MUSB_DMA_STATUS_BUSY;
	channel->actual_len = 0;

	अगर (hb_mult)
		packet_sz = hb_mult * (packet_sz & 0x7FF);

	ret = cppi41_configure_channel(channel, packet_sz, mode, dma_addr, len);
	अगर (!ret)
		channel->status = MUSB_DMA_STATUS_FREE;

	वापस ret;
पूर्ण

अटल पूर्णांक cppi41_is_compatible(काष्ठा dma_channel *channel, u16 maxpacket,
		व्योम *buf, u32 length)
अणु
	काष्ठा cppi41_dma_channel *cppi41_channel = channel->निजी_data;
	काष्ठा cppi41_dma_controller *controller = cppi41_channel->controller;
	काष्ठा musb *musb = controller->controller.musb;

	अगर (is_host_active(musb)) अणु
		WARN_ON(1);
		वापस 1;
	पूर्ण
	अगर (cppi41_channel->hw_ep->ep_in.type != USB_ENDPOINT_XFER_BULK)
		वापस 0;
	अगर (cppi41_channel->is_tx)
		वापस 1;
	/* AM335x Advisory 1.0.13. No workaround क्रम device RX mode */
	वापस 0;
पूर्ण

अटल पूर्णांक cppi41_dma_channel_पात(काष्ठा dma_channel *channel)
अणु
	काष्ठा cppi41_dma_channel *cppi41_channel = channel->निजी_data;
	काष्ठा cppi41_dma_controller *controller = cppi41_channel->controller;
	काष्ठा musb *musb = controller->controller.musb;
	व्योम __iomem *epio = cppi41_channel->hw_ep->regs;
	पूर्णांक tdbit;
	पूर्णांक ret;
	अचिन्हित is_tx;
	u16 csr;

	is_tx = cppi41_channel->is_tx;
	trace_musb_cppi41_पात(cppi41_channel);

	अगर (cppi41_channel->channel.status == MUSB_DMA_STATUS_FREE)
		वापस 0;

	list_del_init(&cppi41_channel->tx_check);
	अगर (is_tx) अणु
		csr = musb_पढ़ोw(epio, MUSB_TXCSR);
		csr &= ~MUSB_TXCSR_DMAENAB;
		musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
	पूर्ण अन्यथा अणु
		cppi41_set_स्वतःreq_mode(cppi41_channel, EP_MODE_AUTOREQ_NONE);

		/* delay to drain to cppi dma pipeline क्रम isoch */
		udelay(250);

		csr = musb_पढ़ोw(epio, MUSB_RXCSR);
		csr &= ~(MUSB_RXCSR_H_REQPKT | MUSB_RXCSR_DMAENAB);
		musb_ग_लिखोw(epio, MUSB_RXCSR, csr);

		/* रुको to drain cppi dma pipe line */
		udelay(50);

		csr = musb_पढ़ोw(epio, MUSB_RXCSR);
		अगर (csr & MUSB_RXCSR_RXPKTRDY) अणु
			csr |= MUSB_RXCSR_FLUSHFIFO;
			musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
			musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
		पूर्ण
	पूर्ण

	/* DA8xx Advisory 2.3.27: रुको 250 ms beक्रमe to start the tearकरोwn */
	अगर (musb->ops->quirks & MUSB_DA8XX)
		mdelay(250);

	tdbit = 1 << cppi41_channel->port_num;
	अगर (is_tx)
		tdbit <<= 16;

	करो अणु
		अगर (is_tx)
			musb_ग_लिखोl(musb->ctrl_base, controller->tकरोwn_reg,
				    tdbit);
		ret = dmaengine_terminate_all(cppi41_channel->dc);
	पूर्ण जबतक (ret == -EAGAIN);

	अगर (is_tx) अणु
		musb_ग_लिखोl(musb->ctrl_base, controller->tकरोwn_reg, tdbit);

		csr = musb_पढ़ोw(epio, MUSB_TXCSR);
		अगर (csr & MUSB_TXCSR_TXPKTRDY) अणु
			csr |= MUSB_TXCSR_FLUSHFIFO;
			musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
		पूर्ण
	पूर्ण

	cppi41_channel->channel.status = MUSB_DMA_STATUS_FREE;
	वापस 0;
पूर्ण

अटल व्योम cppi41_release_all_dma_chans(काष्ठा cppi41_dma_controller *ctrl)
अणु
	काष्ठा dma_chan *dc;
	पूर्णांक i;

	क्रम (i = 0; i < ctrl->num_channels; i++) अणु
		dc = ctrl->tx_channel[i].dc;
		अगर (dc)
			dma_release_channel(dc);
		dc = ctrl->rx_channel[i].dc;
		अगर (dc)
			dma_release_channel(dc);
	पूर्ण
पूर्ण

अटल व्योम cppi41_dma_controller_stop(काष्ठा cppi41_dma_controller *controller)
अणु
	cppi41_release_all_dma_chans(controller);
पूर्ण

अटल पूर्णांक cppi41_dma_controller_start(काष्ठा cppi41_dma_controller *controller)
अणु
	काष्ठा musb *musb = controller->controller.musb;
	काष्ठा device *dev = musb->controller;
	काष्ठा device_node *np = dev->parent->of_node;
	काष्ठा cppi41_dma_channel *cppi41_channel;
	पूर्णांक count;
	पूर्णांक i;
	पूर्णांक ret;

	count = of_property_count_strings(np, "dma-names");
	अगर (count < 0)
		वापस count;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा dma_chan *dc;
		काष्ठा dma_channel *musb_dma;
		स्थिर अक्षर *str;
		अचिन्हित is_tx;
		अचिन्हित पूर्णांक port;

		ret = of_property_पढ़ो_string_index(np, "dma-names", i, &str);
		अगर (ret)
			जाओ err;
		अगर (strstarts(str, "tx"))
			is_tx = 1;
		अन्यथा अगर (strstarts(str, "rx"))
			is_tx = 0;
		अन्यथा अणु
			dev_err(dev, "Wrong dmatype %s\n", str);
			जाओ err;
		पूर्ण
		ret = kstrtouपूर्णांक(str + 2, 0, &port);
		अगर (ret)
			जाओ err;

		ret = -EINVAL;
		अगर (port > controller->num_channels || !port)
			जाओ err;
		अगर (is_tx)
			cppi41_channel = &controller->tx_channel[port - 1];
		अन्यथा
			cppi41_channel = &controller->rx_channel[port - 1];

		cppi41_channel->controller = controller;
		cppi41_channel->port_num = port;
		cppi41_channel->is_tx = is_tx;
		INIT_LIST_HEAD(&cppi41_channel->tx_check);

		musb_dma = &cppi41_channel->channel;
		musb_dma->निजी_data = cppi41_channel;
		musb_dma->status = MUSB_DMA_STATUS_FREE;
		musb_dma->max_len = SZ_4M;

		dc = dma_request_chan(dev->parent, str);
		अगर (IS_ERR(dc)) अणु
			ret = PTR_ERR(dc);
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to request %s: %d.\n",
					str, ret);
			जाओ err;
		पूर्ण

		cppi41_channel->dc = dc;
	पूर्ण
	वापस 0;
err:
	cppi41_release_all_dma_chans(controller);
	वापस ret;
पूर्ण

व्योम cppi41_dma_controller_destroy(काष्ठा dma_controller *c)
अणु
	काष्ठा cppi41_dma_controller *controller = container_of(c,
			काष्ठा cppi41_dma_controller, controller);

	hrसमयr_cancel(&controller->early_tx);
	cppi41_dma_controller_stop(controller);
	kमुक्त(controller->rx_channel);
	kमुक्त(controller->tx_channel);
	kमुक्त(controller);
पूर्ण
EXPORT_SYMBOL_GPL(cppi41_dma_controller_destroy);

काष्ठा dma_controller *
cppi41_dma_controller_create(काष्ठा musb *musb, व्योम __iomem *base)
अणु
	काष्ठा cppi41_dma_controller *controller;
	पूर्णांक channel_size;
	पूर्णांक ret = 0;

	अगर (!musb->controller->parent->of_node) अणु
		dev_err(musb->controller, "Need DT for the DMA engine.\n");
		वापस शून्य;
	पूर्ण

	controller = kzalloc(माप(*controller), GFP_KERNEL);
	अगर (!controller)
		जाओ kzalloc_fail;

	hrसमयr_init(&controller->early_tx, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	controller->early_tx.function = cppi41_recheck_tx_req;
	INIT_LIST_HEAD(&controller->early_tx_list);

	controller->controller.channel_alloc = cppi41_dma_channel_allocate;
	controller->controller.channel_release = cppi41_dma_channel_release;
	controller->controller.channel_program = cppi41_dma_channel_program;
	controller->controller.channel_पात = cppi41_dma_channel_पात;
	controller->controller.is_compatible = cppi41_is_compatible;
	controller->controller.musb = musb;

	अगर (musb->ops->quirks & MUSB_DA8XX) अणु
		controller->tकरोwn_reg = DA8XX_USB_TEARDOWN;
		controller->स्वतःreq_reg = DA8XX_USB_AUTOREQ;
		controller->set_dma_mode = da8xx_set_dma_mode;
		controller->num_channels = DA8XX_DMA_NUM_CHANNELS;
	पूर्ण अन्यथा अणु
		controller->tकरोwn_reg = USB_TDOWN;
		controller->स्वतःreq_reg = USB_CTRL_AUTOREQ;
		controller->set_dma_mode = cppi41_set_dma_mode;
		controller->num_channels = MUSB_DMA_NUM_CHANNELS;
	पूर्ण

	channel_size = controller->num_channels *
			माप(काष्ठा cppi41_dma_channel);
	controller->rx_channel = kzalloc(channel_size, GFP_KERNEL);
	अगर (!controller->rx_channel)
		जाओ rx_channel_alloc_fail;
	controller->tx_channel = kzalloc(channel_size, GFP_KERNEL);
	अगर (!controller->tx_channel)
		जाओ tx_channel_alloc_fail;

	ret = cppi41_dma_controller_start(controller);
	अगर (ret)
		जाओ plat_get_fail;
	वापस &controller->controller;

plat_get_fail:
	kमुक्त(controller->tx_channel);
tx_channel_alloc_fail:
	kमुक्त(controller->rx_channel);
rx_channel_alloc_fail:
	kमुक्त(controller);
kzalloc_fail:
	अगर (ret == -EPROBE_DEFER)
		वापस ERR_PTR(ret);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cppi41_dma_controller_create);
