<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/usb/musb/ux500_dma.c
 *
 * U8500 DMA support code
 *
 * Copyright (C) 2009 STMicroelectronics
 * Copyright (C) 2011 ST-Ericsson SA
 * Authors:
 *	Mian Yousaf Kaukab <mian.yousaf.kaukab@stericsson.com>
 *	Praveena Nadahally <praveen.nadahally@stericsson.com>
 *	Rajaram Regupathy <ragupathy.rajaram@stericsson.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/pfn.h>
#समावेश <linux/sizes.h>
#समावेश <linux/platक्रमm_data/usb-musb-ux500.h>
#समावेश "musb_core.h"

अटल स्थिर अक्षर *iep_chan_names[] = अणु "iep_1_9", "iep_2_10", "iep_3_11", "iep_4_12",
					"iep_5_13", "iep_6_14", "iep_7_15", "iep_8" पूर्ण;
अटल स्थिर अक्षर *oep_chan_names[] = अणु "oep_1_9", "oep_2_10", "oep_3_11", "oep_4_12",
					"oep_5_13", "oep_6_14", "oep_7_15", "oep_8" पूर्ण;

काष्ठा ux500_dma_channel अणु
	काष्ठा dma_channel channel;
	काष्ठा ux500_dma_controller *controller;
	काष्ठा musb_hw_ep *hw_ep;
	काष्ठा dma_chan *dma_chan;
	अचिन्हित पूर्णांक cur_len;
	dma_cookie_t cookie;
	u8 ch_num;
	u8 is_tx;
	u8 is_allocated;
पूर्ण;

काष्ठा ux500_dma_controller अणु
	काष्ठा dma_controller controller;
	काष्ठा ux500_dma_channel rx_channel[UX500_MUSB_DMA_NUM_RX_TX_CHANNELS];
	काष्ठा ux500_dma_channel tx_channel[UX500_MUSB_DMA_NUM_RX_TX_CHANNELS];
	व्योम *निजी_data;
	dma_addr_t phy_base;
पूर्ण;

/* Work function invoked from DMA callback to handle rx transfers. */
अटल व्योम ux500_dma_callback(व्योम *निजी_data)
अणु
	काष्ठा dma_channel *channel = निजी_data;
	काष्ठा ux500_dma_channel *ux500_channel = channel->निजी_data;
	काष्ठा musb_hw_ep       *hw_ep = ux500_channel->hw_ep;
	काष्ठा musb *musb = hw_ep->musb;
	अचिन्हित दीर्घ flags;

	dev_dbg(musb->controller, "DMA rx transfer done on hw_ep=%d\n",
		hw_ep->epnum);

	spin_lock_irqsave(&musb->lock, flags);
	ux500_channel->channel.actual_len = ux500_channel->cur_len;
	ux500_channel->channel.status = MUSB_DMA_STATUS_FREE;
	musb_dma_completion(musb, hw_ep->epnum, ux500_channel->is_tx);
	spin_unlock_irqrestore(&musb->lock, flags);

पूर्ण

अटल bool ux500_configure_channel(काष्ठा dma_channel *channel,
				u16 packet_sz, u8 mode,
				dma_addr_t dma_addr, u32 len)
अणु
	काष्ठा ux500_dma_channel *ux500_channel = channel->निजी_data;
	काष्ठा musb_hw_ep *hw_ep = ux500_channel->hw_ep;
	काष्ठा dma_chan *dma_chan = ux500_channel->dma_chan;
	काष्ठा dma_async_tx_descriptor *dma_desc;
	क्रमागत dma_transfer_direction direction;
	काष्ठा scatterlist sg;
	काष्ठा dma_slave_config slave_conf;
	क्रमागत dma_slave_buswidth addr_width;
	काष्ठा musb *musb = ux500_channel->controller->निजी_data;
	dma_addr_t usb_fअगरo_addr = (musb->io.fअगरo_offset(hw_ep->epnum) +
					ux500_channel->controller->phy_base);

	dev_dbg(musb->controller,
		"packet_sz=%d, mode=%d, dma_addr=0x%llx, len=%d is_tx=%d\n",
		packet_sz, mode, (अचिन्हित दीर्घ दीर्घ) dma_addr,
		len, ux500_channel->is_tx);

	ux500_channel->cur_len = len;

	sg_init_table(&sg, 1);
	sg_set_page(&sg, pfn_to_page(PFN_DOWN(dma_addr)), len,
					    offset_in_page(dma_addr));
	sg_dma_address(&sg) = dma_addr;
	sg_dma_len(&sg) = len;

	direction = ux500_channel->is_tx ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;
	addr_width = (len & 0x3) ? DMA_SLAVE_BUSWIDTH_1_BYTE :
					DMA_SLAVE_BUSWIDTH_4_BYTES;

	slave_conf.direction = direction;
	slave_conf.src_addr = usb_fअगरo_addr;
	slave_conf.src_addr_width = addr_width;
	slave_conf.src_maxburst = 16;
	slave_conf.dst_addr = usb_fअगरo_addr;
	slave_conf.dst_addr_width = addr_width;
	slave_conf.dst_maxburst = 16;
	slave_conf.device_fc = false;

	dmaengine_slave_config(dma_chan, &slave_conf);

	dma_desc = dmaengine_prep_slave_sg(dma_chan, &sg, 1, direction,
					     DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!dma_desc)
		वापस false;

	dma_desc->callback = ux500_dma_callback;
	dma_desc->callback_param = channel;
	ux500_channel->cookie = dma_desc->tx_submit(dma_desc);

	dma_async_issue_pending(dma_chan);

	वापस true;
पूर्ण

अटल काष्ठा dma_channel *ux500_dma_channel_allocate(काष्ठा dma_controller *c,
				काष्ठा musb_hw_ep *hw_ep, u8 is_tx)
अणु
	काष्ठा ux500_dma_controller *controller = container_of(c,
			काष्ठा ux500_dma_controller, controller);
	काष्ठा ux500_dma_channel *ux500_channel = शून्य;
	काष्ठा musb *musb = controller->निजी_data;
	u8 ch_num = hw_ep->epnum - 1;

	/* 8 DMA channels (0 - 7). Each DMA channel can only be allocated
	 * to specअगरied hw_ep. For example DMA channel 0 can only be allocated
	 * to hw_ep 1 and 9.
	 */
	अगर (ch_num > 7)
		ch_num -= 8;

	अगर (ch_num >= UX500_MUSB_DMA_NUM_RX_TX_CHANNELS)
		वापस शून्य;

	ux500_channel = is_tx ? &(controller->tx_channel[ch_num]) :
				&(controller->rx_channel[ch_num]) ;

	/* Check अगर channel is alपढ़ोy used. */
	अगर (ux500_channel->is_allocated)
		वापस शून्य;

	ux500_channel->hw_ep = hw_ep;
	ux500_channel->is_allocated = 1;

	dev_dbg(musb->controller, "hw_ep=%d, is_tx=0x%x, channel=%d\n",
		hw_ep->epnum, is_tx, ch_num);

	वापस &(ux500_channel->channel);
पूर्ण

अटल व्योम ux500_dma_channel_release(काष्ठा dma_channel *channel)
अणु
	काष्ठा ux500_dma_channel *ux500_channel = channel->निजी_data;
	काष्ठा musb *musb = ux500_channel->controller->निजी_data;

	dev_dbg(musb->controller, "channel=%d\n", ux500_channel->ch_num);

	अगर (ux500_channel->is_allocated) अणु
		ux500_channel->is_allocated = 0;
		channel->status = MUSB_DMA_STATUS_FREE;
		channel->actual_len = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ux500_dma_is_compatible(काष्ठा dma_channel *channel,
		u16 maxpacket, व्योम *buf, u32 length)
अणु
	अगर ((maxpacket & 0x3)		||
		((अचिन्हित दीर्घ पूर्णांक) buf & 0x3)	||
		(length < 512)		||
		(length & 0x3))
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल पूर्णांक ux500_dma_channel_program(काष्ठा dma_channel *channel,
				u16 packet_sz, u8 mode,
				dma_addr_t dma_addr, u32 len)
अणु
	पूर्णांक ret;

	BUG_ON(channel->status == MUSB_DMA_STATUS_UNKNOWN ||
		channel->status == MUSB_DMA_STATUS_BUSY);

	channel->status = MUSB_DMA_STATUS_BUSY;
	channel->actual_len = 0;
	ret = ux500_configure_channel(channel, packet_sz, mode, dma_addr, len);
	अगर (!ret)
		channel->status = MUSB_DMA_STATUS_FREE;

	वापस ret;
पूर्ण

अटल पूर्णांक ux500_dma_channel_पात(काष्ठा dma_channel *channel)
अणु
	काष्ठा ux500_dma_channel *ux500_channel = channel->निजी_data;
	काष्ठा ux500_dma_controller *controller = ux500_channel->controller;
	काष्ठा musb *musb = controller->निजी_data;
	व्योम __iomem *epio = musb->endpoपूर्णांकs[ux500_channel->hw_ep->epnum].regs;
	u16 csr;

	dev_dbg(musb->controller, "channel=%d, is_tx=%d\n",
		ux500_channel->ch_num, ux500_channel->is_tx);

	अगर (channel->status == MUSB_DMA_STATUS_BUSY) अणु
		अगर (ux500_channel->is_tx) अणु
			csr = musb_पढ़ोw(epio, MUSB_TXCSR);
			csr &= ~(MUSB_TXCSR_AUTOSET |
				 MUSB_TXCSR_DMAENAB |
				 MUSB_TXCSR_DMAMODE);
			musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
		पूर्ण अन्यथा अणु
			csr = musb_पढ़ोw(epio, MUSB_RXCSR);
			csr &= ~(MUSB_RXCSR_AUTOCLEAR |
				 MUSB_RXCSR_DMAENAB |
				 MUSB_RXCSR_DMAMODE);
			musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
		पूर्ण

		dmaengine_terminate_all(ux500_channel->dma_chan);
		channel->status = MUSB_DMA_STATUS_FREE;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ux500_dma_controller_stop(काष्ठा ux500_dma_controller *controller)
अणु
	काष्ठा ux500_dma_channel *ux500_channel;
	काष्ठा dma_channel *channel;
	u8 ch_num;

	क्रम (ch_num = 0; ch_num < UX500_MUSB_DMA_NUM_RX_TX_CHANNELS; ch_num++) अणु
		channel = &controller->rx_channel[ch_num].channel;
		ux500_channel = channel->निजी_data;

		ux500_dma_channel_release(channel);

		अगर (ux500_channel->dma_chan)
			dma_release_channel(ux500_channel->dma_chan);
	पूर्ण

	क्रम (ch_num = 0; ch_num < UX500_MUSB_DMA_NUM_RX_TX_CHANNELS; ch_num++) अणु
		channel = &controller->tx_channel[ch_num].channel;
		ux500_channel = channel->निजी_data;

		ux500_dma_channel_release(channel);

		अगर (ux500_channel->dma_chan)
			dma_release_channel(ux500_channel->dma_chan);
	पूर्ण
पूर्ण

अटल पूर्णांक ux500_dma_controller_start(काष्ठा ux500_dma_controller *controller)
अणु
	काष्ठा ux500_dma_channel *ux500_channel = शून्य;
	काष्ठा musb *musb = controller->निजी_data;
	काष्ठा device *dev = musb->controller;
	काष्ठा musb_hdrc_platक्रमm_data *plat = dev_get_platdata(dev);
	काष्ठा ux500_musb_board_data *data;
	काष्ठा dma_channel *dma_channel = शून्य;
	अक्षर **chan_names;
	u32 ch_num;
	u8 dir;
	u8 is_tx = 0;

	व्योम **param_array;
	काष्ठा ux500_dma_channel *channel_array;
	dma_cap_mask_t mask;

	अगर (!plat) अणु
		dev_err(musb->controller, "No platform data\n");
		वापस -EINVAL;
	पूर्ण

	data = plat->board_data;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	/* Prepare the loop क्रम RX channels */
	channel_array = controller->rx_channel;
	param_array = data ? data->dma_rx_param_array : शून्य;
	chan_names = (अक्षर **)iep_chan_names;

	क्रम (dir = 0; dir < 2; dir++) अणु
		क्रम (ch_num = 0;
		     ch_num < UX500_MUSB_DMA_NUM_RX_TX_CHANNELS;
		     ch_num++) अणु
			ux500_channel = &channel_array[ch_num];
			ux500_channel->controller = controller;
			ux500_channel->ch_num = ch_num;
			ux500_channel->is_tx = is_tx;

			dma_channel = &(ux500_channel->channel);
			dma_channel->निजी_data = ux500_channel;
			dma_channel->status = MUSB_DMA_STATUS_FREE;
			dma_channel->max_len = SZ_16M;

			ux500_channel->dma_chan =
				dma_request_chan(dev, chan_names[ch_num]);

			अगर (IS_ERR(ux500_channel->dma_chan))
				ux500_channel->dma_chan =
					dma_request_channel(mask,
							    data ?
							    data->dma_filter :
							    शून्य,
							    param_array ?
							    param_array[ch_num] :
							    शून्य);

			अगर (!ux500_channel->dma_chan) अणु
				ERR("Dma pipe allocation error dir=%d ch=%d\n",
					dir, ch_num);

				/* Release alपढ़ोy allocated channels */
				ux500_dma_controller_stop(controller);

				वापस -EBUSY;
			पूर्ण

		पूर्ण

		/* Prepare the loop क्रम TX channels */
		channel_array = controller->tx_channel;
		param_array = data ? data->dma_tx_param_array : शून्य;
		chan_names = (अक्षर **)oep_chan_names;
		is_tx = 1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ux500_dma_controller_destroy(काष्ठा dma_controller *c)
अणु
	काष्ठा ux500_dma_controller *controller = container_of(c,
			काष्ठा ux500_dma_controller, controller);

	ux500_dma_controller_stop(controller);
	kमुक्त(controller);
पूर्ण
EXPORT_SYMBOL_GPL(ux500_dma_controller_destroy);

काष्ठा dma_controller *
ux500_dma_controller_create(काष्ठा musb *musb, व्योम __iomem *base)
अणु
	काष्ठा ux500_dma_controller *controller;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(musb->controller);
	काष्ठा resource	*iomem;
	पूर्णांक ret;

	controller = kzalloc(माप(*controller), GFP_KERNEL);
	अगर (!controller)
		जाओ kzalloc_fail;

	controller->निजी_data = musb;

	/* Save physical address क्रम DMA controller. */
	iomem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!iomem) अणु
		dev_err(musb->controller, "no memory resource defined\n");
		जाओ plat_get_fail;
	पूर्ण

	controller->phy_base = (dma_addr_t) iomem->start;

	controller->controller.channel_alloc = ux500_dma_channel_allocate;
	controller->controller.channel_release = ux500_dma_channel_release;
	controller->controller.channel_program = ux500_dma_channel_program;
	controller->controller.channel_पात = ux500_dma_channel_पात;
	controller->controller.is_compatible = ux500_dma_is_compatible;

	ret = ux500_dma_controller_start(controller);
	अगर (ret)
		जाओ plat_get_fail;
	वापस &controller->controller;

plat_get_fail:
	kमुक्त(controller);
kzalloc_fail:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ux500_dma_controller_create);
