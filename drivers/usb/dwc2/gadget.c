<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://armlinux.simtec.co.uk/
 *
 * S3C USB2.0 High-speed / OtG driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mutex.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/phy.h>
#समावेश <linux/usb/composite.h>


#समावेश "core.h"
#समावेश "hw.h"

/* conversion functions */
अटल अंतरभूत काष्ठा dwc2_hsotg_req *our_req(काष्ठा usb_request *req)
अणु
	वापस container_of(req, काष्ठा dwc2_hsotg_req, req);
पूर्ण

अटल अंतरभूत काष्ठा dwc2_hsotg_ep *our_ep(काष्ठा usb_ep *ep)
अणु
	वापस container_of(ep, काष्ठा dwc2_hsotg_ep, ep);
पूर्ण

अटल अंतरभूत काष्ठा dwc2_hsotg *to_hsotg(काष्ठा usb_gadget *gadget)
अणु
	वापस container_of(gadget, काष्ठा dwc2_hsotg, gadget);
पूर्ण

अटल अंतरभूत व्योम dwc2_set_bit(काष्ठा dwc2_hsotg *hsotg, u32 offset, u32 val)
अणु
	dwc2_ग_लिखोl(hsotg, dwc2_पढ़ोl(hsotg, offset) | val, offset);
पूर्ण

अटल अंतरभूत व्योम dwc2_clear_bit(काष्ठा dwc2_hsotg *hsotg, u32 offset, u32 val)
अणु
	dwc2_ग_लिखोl(hsotg, dwc2_पढ़ोl(hsotg, offset) & ~val, offset);
पूर्ण

अटल अंतरभूत काष्ठा dwc2_hsotg_ep *index_to_ep(काष्ठा dwc2_hsotg *hsotg,
						u32 ep_index, u32 dir_in)
अणु
	अगर (dir_in)
		वापस hsotg->eps_in[ep_index];
	अन्यथा
		वापस hsotg->eps_out[ep_index];
पूर्ण

/* क्रमward declaration of functions */
अटल व्योम dwc2_hsotg_dump(काष्ठा dwc2_hsotg *hsotg);

/**
 * using_dma - वापस the DMA status of the driver.
 * @hsotg: The driver state.
 *
 * Return true अगर we're using DMA.
 *
 * Currently, we have the DMA support code worked पूर्णांकo everywhere
 * that needs it, but the AMBA DMA implementation in the hardware can
 * only DMA from 32bit aligned addresses. This means that gadमाला_लो such
 * as the CDC Ethernet cannot work as they often pass packets which are
 * not 32bit aligned.
 *
 * Unक्रमtunately the choice to use DMA or not is global to the controller
 * and seems to be only settable when the controller is being put through
 * a core reset. This means we either need to fix the gadमाला_लो to take
 * account of DMA alignment, or add bounce buffers (yuerk).
 *
 * g_using_dma is set depending on dts flag.
 */
अटल अंतरभूत bool using_dma(काष्ठा dwc2_hsotg *hsotg)
अणु
	वापस hsotg->params.g_dma;
पूर्ण

/*
 * using_desc_dma - वापस the descriptor DMA status of the driver.
 * @hsotg: The driver state.
 *
 * Return true अगर we're using descriptor DMA.
 */
अटल अंतरभूत bool using_desc_dma(काष्ठा dwc2_hsotg *hsotg)
अणु
	वापस hsotg->params.g_dma_desc;
पूर्ण

/**
 * dwc2_gadget_incr_frame_num - Increments the targeted frame number.
 * @hs_ep: The endpoपूर्णांक
 *
 * This function will also check अगर the frame number overruns DSTS_SOFFN_LIMIT.
 * If an overrun occurs it will wrap the value and set the frame_overrun flag.
 */
अटल अंतरभूत व्योम dwc2_gadget_incr_frame_num(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	hs_ep->target_frame += hs_ep->पूर्णांकerval;
	अगर (hs_ep->target_frame > DSTS_SOFFN_LIMIT) अणु
		hs_ep->frame_overrun = true;
		hs_ep->target_frame &= DSTS_SOFFN_LIMIT;
	पूर्ण अन्यथा अणु
		hs_ep->frame_overrun = false;
	पूर्ण
पूर्ण

/**
 * dwc2_gadget_dec_frame_num_by_one - Decrements the targeted frame number
 *                                    by one.
 * @hs_ep: The endpoपूर्णांक.
 *
 * This function used in service पूर्णांकerval based scheduling flow to calculate
 * descriptor frame number filed value. For service पूर्णांकerval mode frame
 * number in descriptor should poपूर्णांक to last (u)frame in the पूर्णांकerval.
 *
 */
अटल अंतरभूत व्योम dwc2_gadget_dec_frame_num_by_one(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	अगर (hs_ep->target_frame)
		hs_ep->target_frame -= 1;
	अन्यथा
		hs_ep->target_frame = DSTS_SOFFN_LIMIT;
पूर्ण

/**
 * dwc2_hsotg_en_gsपूर्णांक - enable one or more of the general पूर्णांकerrupt
 * @hsotg: The device state
 * @पूर्णांकs: A biपंचांगask of the पूर्णांकerrupts to enable
 */
अटल व्योम dwc2_hsotg_en_gsपूर्णांक(काष्ठा dwc2_hsotg *hsotg, u32 पूर्णांकs)
अणु
	u32 gsपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
	u32 new_gsपूर्णांकmsk;

	new_gsपूर्णांकmsk = gsपूर्णांकmsk | पूर्णांकs;

	अगर (new_gsपूर्णांकmsk != gsपूर्णांकmsk) अणु
		dev_dbg(hsotg->dev, "gsintmsk now 0x%08x\n", new_gsपूर्णांकmsk);
		dwc2_ग_लिखोl(hsotg, new_gsपूर्णांकmsk, GINTMSK);
	पूर्ण
पूर्ण

/**
 * dwc2_hsotg_disable_gsपूर्णांक - disable one or more of the general पूर्णांकerrupt
 * @hsotg: The device state
 * @पूर्णांकs: A biपंचांगask of the पूर्णांकerrupts to enable
 */
अटल व्योम dwc2_hsotg_disable_gsपूर्णांक(काष्ठा dwc2_hsotg *hsotg, u32 पूर्णांकs)
अणु
	u32 gsपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
	u32 new_gsपूर्णांकmsk;

	new_gsपूर्णांकmsk = gsपूर्णांकmsk & ~पूर्णांकs;

	अगर (new_gsपूर्णांकmsk != gsपूर्णांकmsk)
		dwc2_ग_लिखोl(hsotg, new_gsपूर्णांकmsk, GINTMSK);
पूर्ण

/**
 * dwc2_hsotg_ctrl_epपूर्णांक - enable/disable an endpoपूर्णांक irq
 * @hsotg: The device state
 * @ep: The endpoपूर्णांक index
 * @dir_in: True अगर direction is in.
 * @en: The enable value, true to enable
 *
 * Set or clear the mask क्रम an inभागidual endpoपूर्णांक's पूर्णांकerrupt
 * request.
 */
अटल व्योम dwc2_hsotg_ctrl_epपूर्णांक(काष्ठा dwc2_hsotg *hsotg,
				  अचिन्हित पूर्णांक ep, अचिन्हित पूर्णांक dir_in,
				 अचिन्हित पूर्णांक en)
अणु
	अचिन्हित दीर्घ flags;
	u32 bit = 1 << ep;
	u32 daपूर्णांक;

	अगर (!dir_in)
		bit <<= 16;

	local_irq_save(flags);
	daपूर्णांक = dwc2_पढ़ोl(hsotg, DAINTMSK);
	अगर (en)
		daपूर्णांक |= bit;
	अन्यथा
		daपूर्णांक &= ~bit;
	dwc2_ग_लिखोl(hsotg, daपूर्णांक, DAINTMSK);
	local_irq_restore(flags);
पूर्ण

/**
 * dwc2_hsotg_tx_fअगरo_count - वापस count of TX FIFOs in device mode
 *
 * @hsotg: Programming view of the DWC_otg controller
 */
पूर्णांक dwc2_hsotg_tx_fअगरo_count(काष्ठा dwc2_hsotg *hsotg)
अणु
	अगर (hsotg->hw_params.en_multiple_tx_fअगरo)
		/* In dedicated FIFO mode we need count of IN EPs */
		वापस hsotg->hw_params.num_dev_in_eps;
	अन्यथा
		/* In shared FIFO mode we need count of Periodic IN EPs */
		वापस hsotg->hw_params.num_dev_perio_in_ep;
पूर्ण

/**
 * dwc2_hsotg_tx_fअगरo_total_depth - वापस total FIFO depth available क्रम
 * device mode TX FIFOs
 *
 * @hsotg: Programming view of the DWC_otg controller
 */
पूर्णांक dwc2_hsotg_tx_fअगरo_total_depth(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक addr;
	पूर्णांक tx_addr_max;
	u32 np_tx_fअगरo_size;

	np_tx_fअगरo_size = min_t(u32, hsotg->hw_params.dev_nperio_tx_fअगरo_size,
				hsotg->params.g_np_tx_fअगरo_size);

	/* Get Endpoपूर्णांक Info Control block size in DWORDs. */
	tx_addr_max = hsotg->hw_params.total_fअगरo_size;

	addr = hsotg->params.g_rx_fअगरo_size + np_tx_fअगरo_size;
	अगर (tx_addr_max <= addr)
		वापस 0;

	वापस tx_addr_max - addr;
पूर्ण

/**
 * dwc2_gadget_wkup_alert_handler - Handler क्रम WKUP_ALERT पूर्णांकerrupt
 *
 * @hsotg: Programming view of the DWC_otg controller
 *
 */
अटल व्योम dwc2_gadget_wkup_alert_handler(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 gपूर्णांकsts2;
	u32 gपूर्णांकmsk2;

	gपूर्णांकsts2 = dwc2_पढ़ोl(hsotg, GINTSTS2);
	gपूर्णांकmsk2 = dwc2_पढ़ोl(hsotg, GINTMSK2);
	gपूर्णांकsts2 &= gपूर्णांकmsk2;

	अगर (gपूर्णांकsts2 & GINTSTS2_WKUP_ALERT_INT) अणु
		dev_dbg(hsotg->dev, "%s: Wkup_Alert_Int\n", __func__);
		dwc2_set_bit(hsotg, GINTSTS2, GINTSTS2_WKUP_ALERT_INT);
		dwc2_set_bit(hsotg, DCTL, DCTL_RMTWKUPSIG);
	पूर्ण
पूर्ण

/**
 * dwc2_hsotg_tx_fअगरo_average_depth - वापसs average depth of device mode
 * TX FIFOs
 *
 * @hsotg: Programming view of the DWC_otg controller
 */
पूर्णांक dwc2_hsotg_tx_fअगरo_average_depth(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक tx_fअगरo_count;
	पूर्णांक tx_fअगरo_depth;

	tx_fअगरo_depth = dwc2_hsotg_tx_fअगरo_total_depth(hsotg);

	tx_fअगरo_count = dwc2_hsotg_tx_fअगरo_count(hsotg);

	अगर (!tx_fअगरo_count)
		वापस tx_fअगरo_depth;
	अन्यथा
		वापस tx_fअगरo_depth / tx_fअगरo_count;
पूर्ण

/**
 * dwc2_hsotg_init_fअगरo - initialise non-periodic FIFOs
 * @hsotg: The device instance.
 */
अटल व्योम dwc2_hsotg_init_fअगरo(काष्ठा dwc2_hsotg *hsotg)
अणु
	अचिन्हित पूर्णांक ep;
	अचिन्हित पूर्णांक addr;
	पूर्णांक समयout;

	u32 val;
	u32 *txfsz = hsotg->params.g_tx_fअगरo_size;

	/* Reset fअगरo map अगर not correctly cleared during previous session */
	WARN_ON(hsotg->fअगरo_map);
	hsotg->fअगरo_map = 0;

	/* set RX/NPTX FIFO sizes */
	dwc2_ग_लिखोl(hsotg, hsotg->params.g_rx_fअगरo_size, GRXFSIZ);
	dwc2_ग_लिखोl(hsotg, (hsotg->params.g_rx_fअगरo_size <<
		    FIFOSIZE_STARTADDR_SHIFT) |
		    (hsotg->params.g_np_tx_fअगरo_size << FIFOSIZE_DEPTH_SHIFT),
		    GNPTXFSIZ);

	/*
	 * arange all the rest of the TX FIFOs, as some versions of this
	 * block have overlapping शेष addresses. This also ensures
	 * that अगर the settings have been changed, then they are set to
	 * known values.
	 */

	/* start at the end of the GNPTXFSIZ, rounded up */
	addr = hsotg->params.g_rx_fअगरo_size + hsotg->params.g_np_tx_fअगरo_size;

	/*
	 * Configure fअगरos sizes from provided configuration and assign
	 * them to endpoपूर्णांकs dynamically according to maxpacket size value of
	 * given endpoपूर्णांक.
	 */
	क्रम (ep = 1; ep < MAX_EPS_CHANNELS; ep++) अणु
		अगर (!txfsz[ep])
			जारी;
		val = addr;
		val |= txfsz[ep] << FIFOSIZE_DEPTH_SHIFT;
		WARN_ONCE(addr + txfsz[ep] > hsotg->fअगरo_mem,
			  "insufficient fifo memory");
		addr += txfsz[ep];

		dwc2_ग_लिखोl(hsotg, val, DPTXFSIZN(ep));
		val = dwc2_पढ़ोl(hsotg, DPTXFSIZN(ep));
	पूर्ण

	dwc2_ग_लिखोl(hsotg, hsotg->hw_params.total_fअगरo_size |
		    addr << GDFIFOCFG_EPINFOBASE_SHIFT,
		    GDFIFOCFG);
	/*
	 * according to p428 of the design guide, we need to ensure that
	 * all fअगरos are flushed beक्रमe continuing
	 */

	dwc2_ग_लिखोl(hsotg, GRSTCTL_TXFNUM(0x10) | GRSTCTL_TXFFLSH |
	       GRSTCTL_RXFFLSH, GRSTCTL);

	/* रुको until the fअगरos are both flushed */
	समयout = 100;
	जबतक (1) अणु
		val = dwc2_पढ़ोl(hsotg, GRSTCTL);

		अगर ((val & (GRSTCTL_TXFFLSH | GRSTCTL_RXFFLSH)) == 0)
			अवरोध;

		अगर (--समयout == 0) अणु
			dev_err(hsotg->dev,
				"%s: timeout flushing fifos (GRSTCTL=%08x)\n",
				__func__, val);
			अवरोध;
		पूर्ण

		udelay(1);
	पूर्ण

	dev_dbg(hsotg->dev, "FIFOs reset, timeout at %d\n", समयout);
पूर्ण

/**
 * dwc2_hsotg_ep_alloc_request - allocate USB rerequest काष्ठाure
 * @ep: USB endpoपूर्णांक to allocate request क्रम.
 * @flags: Allocation flags
 *
 * Allocate a new USB request काष्ठाure appropriate क्रम the specअगरied endpoपूर्णांक
 */
अटल काष्ठा usb_request *dwc2_hsotg_ep_alloc_request(काष्ठा usb_ep *ep,
						       gfp_t flags)
अणु
	काष्ठा dwc2_hsotg_req *req;

	req = kzalloc(माप(*req), flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

/**
 * is_ep_periodic - वापस true अगर the endpoपूर्णांक is in periodic mode.
 * @hs_ep: The endpoपूर्णांक to query.
 *
 * Returns true अगर the endpoपूर्णांक is in periodic mode, meaning it is being
 * used क्रम an Interrupt or ISO transfer.
 */
अटल अंतरभूत पूर्णांक is_ep_periodic(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	वापस hs_ep->periodic;
पूर्ण

/**
 * dwc2_hsotg_unmap_dma - unmap the DMA memory being used क्रम the request
 * @hsotg: The device state.
 * @hs_ep: The endpoपूर्णांक क्रम the request
 * @hs_req: The request being processed.
 *
 * This is the reverse of dwc2_hsotg_map_dma(), called क्रम the completion
 * of a request to ensure the buffer is पढ़ोy क्रम access by the caller.
 */
अटल व्योम dwc2_hsotg_unmap_dma(काष्ठा dwc2_hsotg *hsotg,
				 काष्ठा dwc2_hsotg_ep *hs_ep,
				काष्ठा dwc2_hsotg_req *hs_req)
अणु
	काष्ठा usb_request *req = &hs_req->req;

	usb_gadget_unmap_request(&hsotg->gadget, req, hs_ep->map_dir);
पूर्ण

/*
 * dwc2_gadget_alloc_ctrl_desc_chains - allocate DMA descriptor chains
 * क्रम Control endpoपूर्णांक
 * @hsotg: The device state.
 *
 * This function will allocate 4 descriptor chains क्रम EP 0: 2 क्रम
 * Setup stage, per one क्रम IN and OUT data/status transactions.
 */
अटल पूर्णांक dwc2_gadget_alloc_ctrl_desc_chains(काष्ठा dwc2_hsotg *hsotg)
अणु
	hsotg->setup_desc[0] =
		dmam_alloc_coherent(hsotg->dev,
				    माप(काष्ठा dwc2_dma_desc),
				    &hsotg->setup_desc_dma[0],
				    GFP_KERNEL);
	अगर (!hsotg->setup_desc[0])
		जाओ fail;

	hsotg->setup_desc[1] =
		dmam_alloc_coherent(hsotg->dev,
				    माप(काष्ठा dwc2_dma_desc),
				    &hsotg->setup_desc_dma[1],
				    GFP_KERNEL);
	अगर (!hsotg->setup_desc[1])
		जाओ fail;

	hsotg->ctrl_in_desc =
		dmam_alloc_coherent(hsotg->dev,
				    माप(काष्ठा dwc2_dma_desc),
				    &hsotg->ctrl_in_desc_dma,
				    GFP_KERNEL);
	अगर (!hsotg->ctrl_in_desc)
		जाओ fail;

	hsotg->ctrl_out_desc =
		dmam_alloc_coherent(hsotg->dev,
				    माप(काष्ठा dwc2_dma_desc),
				    &hsotg->ctrl_out_desc_dma,
				    GFP_KERNEL);
	अगर (!hsotg->ctrl_out_desc)
		जाओ fail;

	वापस 0;

fail:
	वापस -ENOMEM;
पूर्ण

/**
 * dwc2_hsotg_ग_लिखो_fअगरo - ग_लिखो packet Data to the TxFIFO
 * @hsotg: The controller state.
 * @hs_ep: The endpoपूर्णांक we're going to ग_लिखो क्रम.
 * @hs_req: The request to ग_लिखो data क्रम.
 *
 * This is called when the TxFIFO has some space in it to hold a new
 * transmission and we have something to give it. The actual setup of
 * the data size is करोne अन्यथाwhere, so all we have to करो is to actually
 * ग_लिखो the data.
 *
 * The वापस value is zero अगर there is more space (or nothing was करोne)
 * otherwise -ENOSPC is वापसed अगर the FIFO space was used up.
 *
 * This routine is only needed क्रम PIO
 */
अटल पूर्णांक dwc2_hsotg_ग_लिखो_fअगरo(काष्ठा dwc2_hsotg *hsotg,
				 काष्ठा dwc2_hsotg_ep *hs_ep,
				काष्ठा dwc2_hsotg_req *hs_req)
अणु
	bool periodic = is_ep_periodic(hs_ep);
	u32 gnptxsts = dwc2_पढ़ोl(hsotg, GNPTXSTS);
	पूर्णांक buf_pos = hs_req->req.actual;
	पूर्णांक to_ग_लिखो = hs_ep->size_loaded;
	व्योम *data;
	पूर्णांक can_ग_लिखो;
	पूर्णांक pkt_round;
	पूर्णांक max_transfer;

	to_ग_लिखो -= (buf_pos - hs_ep->last_load);

	/* अगर there's nothing to ग_लिखो, get out early */
	अगर (to_ग_लिखो == 0)
		वापस 0;

	अगर (periodic && !hsotg->dedicated_fअगरos) अणु
		u32 epsize = dwc2_पढ़ोl(hsotg, DIEPTSIZ(hs_ep->index));
		पूर्णांक size_left;
		पूर्णांक size_करोne;

		/*
		 * work out how much data was loaded so we can calculate
		 * how much data is left in the fअगरo.
		 */

		size_left = DXEPTSIZ_XFERSIZE_GET(epsize);

		/*
		 * अगर shared fअगरo, we cannot ग_लिखो anything until the
		 * previous data has been completely sent.
		 */
		अगर (hs_ep->fअगरo_load != 0) अणु
			dwc2_hsotg_en_gsपूर्णांक(hsotg, GINTSTS_PTXFEMP);
			वापस -ENOSPC;
		पूर्ण

		dev_dbg(hsotg->dev, "%s: left=%d, load=%d, fifo=%d, size %d\n",
			__func__, size_left,
			hs_ep->size_loaded, hs_ep->fअगरo_load, hs_ep->fअगरo_size);

		/* how much of the data has moved */
		size_करोne = hs_ep->size_loaded - size_left;

		/* how much data is left in the fअगरo */
		can_ग_लिखो = hs_ep->fअगरo_load - size_करोne;
		dev_dbg(hsotg->dev, "%s: => can_write1=%d\n",
			__func__, can_ग_लिखो);

		can_ग_लिखो = hs_ep->fअगरo_size - can_ग_लिखो;
		dev_dbg(hsotg->dev, "%s: => can_write2=%d\n",
			__func__, can_ग_लिखो);

		अगर (can_ग_लिखो <= 0) अणु
			dwc2_hsotg_en_gsपूर्णांक(hsotg, GINTSTS_PTXFEMP);
			वापस -ENOSPC;
		पूर्ण
	पूर्ण अन्यथा अगर (hsotg->dedicated_fअगरos && hs_ep->index != 0) अणु
		can_ग_लिखो = dwc2_पढ़ोl(hsotg,
				       DTXFSTS(hs_ep->fअगरo_index));

		can_ग_लिखो &= 0xffff;
		can_ग_लिखो *= 4;
	पूर्ण अन्यथा अणु
		अगर (GNPTXSTS_NP_TXQ_SPC_AVAIL_GET(gnptxsts) == 0) अणु
			dev_dbg(hsotg->dev,
				"%s: no queue slots available (0x%08x)\n",
				__func__, gnptxsts);

			dwc2_hsotg_en_gsपूर्णांक(hsotg, GINTSTS_NPTXFEMP);
			वापस -ENOSPC;
		पूर्ण

		can_ग_लिखो = GNPTXSTS_NP_TXF_SPC_AVAIL_GET(gnptxsts);
		can_ग_लिखो *= 4;	/* fअगरo size is in 32bit quantities. */
	पूर्ण

	max_transfer = hs_ep->ep.maxpacket * hs_ep->mc;

	dev_dbg(hsotg->dev, "%s: GNPTXSTS=%08x, can=%d, to=%d, max_transfer %d\n",
		__func__, gnptxsts, can_ग_लिखो, to_ग_लिखो, max_transfer);

	/*
	 * limit to 512 bytes of data, it seems at least on the non-periodic
	 * FIFO, requests of >512 cause the endpoपूर्णांक to get stuck with a
	 * fragment of the end of the transfer in it.
	 */
	अगर (can_ग_लिखो > 512 && !periodic)
		can_ग_लिखो = 512;

	/*
	 * limit the ग_लिखो to one max-packet size worth of data, but allow
	 * the transfer to वापस that it did not run out of fअगरo space
	 * करोing it.
	 */
	अगर (to_ग_लिखो > max_transfer) अणु
		to_ग_लिखो = max_transfer;

		/* it's needed only when we करो not use dedicated fअगरos */
		अगर (!hsotg->dedicated_fअगरos)
			dwc2_hsotg_en_gsपूर्णांक(hsotg,
					    periodic ? GINTSTS_PTXFEMP :
					   GINTSTS_NPTXFEMP);
	पूर्ण

	/* see अगर we can ग_लिखो data */

	अगर (to_ग_लिखो > can_ग_लिखो) अणु
		to_ग_लिखो = can_ग_लिखो;
		pkt_round = to_ग_लिखो % max_transfer;

		/*
		 * Round the ग_लिखो करोwn to an
		 * exact number of packets.
		 *
		 * Note, we करो not currently check to see अगर we can ever
		 * ग_लिखो a full packet or not to the FIFO.
		 */

		अगर (pkt_round)
			to_ग_लिखो -= pkt_round;

		/*
		 * enable correct FIFO पूर्णांकerrupt to alert us when there
		 * is more room left.
		 */

		/* it's needed only when we करो not use dedicated fअगरos */
		अगर (!hsotg->dedicated_fअगरos)
			dwc2_hsotg_en_gsपूर्णांक(hsotg,
					    periodic ? GINTSTS_PTXFEMP :
					   GINTSTS_NPTXFEMP);
	पूर्ण

	dev_dbg(hsotg->dev, "write %d/%d, can_write %d, done %d\n",
		to_ग_लिखो, hs_req->req.length, can_ग_लिखो, buf_pos);

	अगर (to_ग_लिखो <= 0)
		वापस -ENOSPC;

	hs_req->req.actual = buf_pos + to_ग_लिखो;
	hs_ep->total_data += to_ग_लिखो;

	अगर (periodic)
		hs_ep->fअगरo_load += to_ग_लिखो;

	to_ग_लिखो = DIV_ROUND_UP(to_ग_लिखो, 4);
	data = hs_req->req.buf + buf_pos;

	dwc2_ग_लिखोl_rep(hsotg, EPFIFO(hs_ep->index), data, to_ग_लिखो);

	वापस (to_ग_लिखो >= can_ग_लिखो) ? -ENOSPC : 0;
पूर्ण

/**
 * get_ep_limit - get the maximum data legnth क्रम this endpoपूर्णांक
 * @hs_ep: The endpoपूर्णांक
 *
 * Return the maximum data that can be queued in one go on a given endpoपूर्णांक
 * so that transfers that are too दीर्घ can be split.
 */
अटल अचिन्हित पूर्णांक get_ep_limit(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	पूर्णांक index = hs_ep->index;
	अचिन्हित पूर्णांक maxsize;
	अचिन्हित पूर्णांक maxpkt;

	अगर (index != 0) अणु
		maxsize = DXEPTSIZ_XFERSIZE_LIMIT + 1;
		maxpkt = DXEPTSIZ_PKTCNT_LIMIT + 1;
	पूर्ण अन्यथा अणु
		maxsize = 64 + 64;
		अगर (hs_ep->dir_in)
			maxpkt = DIEPTSIZ0_PKTCNT_LIMIT + 1;
		अन्यथा
			maxpkt = 2;
	पूर्ण

	/* we made the स्थिरant loading easier above by using +1 */
	maxpkt--;
	maxsize--;

	/*
	 * स्थिरrain by packet count अगर maxpkts*pktsize is greater
	 * than the length रेजिस्टर size.
	 */

	अगर ((maxpkt * hs_ep->ep.maxpacket) < maxsize)
		maxsize = maxpkt * hs_ep->ep.maxpacket;

	वापस maxsize;
पूर्ण

/**
 * dwc2_hsotg_पढ़ो_frameno - पढ़ो current frame number
 * @hsotg: The device instance
 *
 * Return the current frame number
 */
अटल u32 dwc2_hsotg_पढ़ो_frameno(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 dsts;

	dsts = dwc2_पढ़ोl(hsotg, DSTS);
	dsts &= DSTS_SOFFN_MASK;
	dsts >>= DSTS_SOFFN_SHIFT;

	वापस dsts;
पूर्ण

/**
 * dwc2_gadget_get_chain_limit - get the maximum data payload value of the
 * DMA descriptor chain prepared क्रम specअगरic endpoपूर्णांक
 * @hs_ep: The endpoपूर्णांक
 *
 * Return the maximum data that can be queued in one go on a given endpoपूर्णांक
 * depending on its descriptor chain capacity so that transfers that
 * are too दीर्घ can be split.
 */
अटल अचिन्हित पूर्णांक dwc2_gadget_get_chain_limit(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc = hs_ep->ep.desc;
	पूर्णांक is_isoc = hs_ep->isochronous;
	अचिन्हित पूर्णांक maxsize;
	u32 mps = hs_ep->ep.maxpacket;
	पूर्णांक dir_in = hs_ep->dir_in;

	अगर (is_isoc)
		maxsize = (hs_ep->dir_in ? DEV_DMA_ISOC_TX_NBYTES_LIMIT :
					   DEV_DMA_ISOC_RX_NBYTES_LIMIT) *
					   MAX_DMA_DESC_NUM_HS_ISOC;
	अन्यथा
		maxsize = DEV_DMA_NBYTES_LIMIT * MAX_DMA_DESC_NUM_GENERIC;

	/* Interrupt OUT EP with mps not multiple of 4 */
	अगर (hs_ep->index)
		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(ep_desc) && !dir_in && (mps % 4))
			maxsize = mps * MAX_DMA_DESC_NUM_GENERIC;

	वापस maxsize;
पूर्ण

/*
 * dwc2_gadget_get_desc_params - get DMA descriptor parameters.
 * @hs_ep: The endpoपूर्णांक
 * @mask: RX/TX bytes mask to be defined
 *
 * Returns maximum data payload क्रम one descriptor after analyzing endpoपूर्णांक
 * अक्षरacteristics.
 * DMA descriptor transfer bytes limit depends on EP type:
 * Control out - MPS,
 * Isochronous - descriptor rx/tx bytes bitfield limit,
 * Control In/Bulk/Interrupt - multiple of mps. This will allow to not
 * have concatenations from various descriptors within one packet.
 * Interrupt OUT - अगर mps not multiple of 4 then a single packet corresponds
 * to a single descriptor.
 *
 * Selects corresponding mask क्रम RX/TX bytes as well.
 */
अटल u32 dwc2_gadget_get_desc_params(काष्ठा dwc2_hsotg_ep *hs_ep, u32 *mask)
अणु
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc = hs_ep->ep.desc;
	u32 mps = hs_ep->ep.maxpacket;
	पूर्णांक dir_in = hs_ep->dir_in;
	u32 desc_size = 0;

	अगर (!hs_ep->index && !dir_in) अणु
		desc_size = mps;
		*mask = DEV_DMA_NBYTES_MASK;
	पूर्ण अन्यथा अगर (hs_ep->isochronous) अणु
		अगर (dir_in) अणु
			desc_size = DEV_DMA_ISOC_TX_NBYTES_LIMIT;
			*mask = DEV_DMA_ISOC_TX_NBYTES_MASK;
		पूर्ण अन्यथा अणु
			desc_size = DEV_DMA_ISOC_RX_NBYTES_LIMIT;
			*mask = DEV_DMA_ISOC_RX_NBYTES_MASK;
		पूर्ण
	पूर्ण अन्यथा अणु
		desc_size = DEV_DMA_NBYTES_LIMIT;
		*mask = DEV_DMA_NBYTES_MASK;

		/* Round करोwn desc_size to be mps multiple */
		desc_size -= desc_size % mps;
	पूर्ण

	/* Interrupt OUT EP with mps not multiple of 4 */
	अगर (hs_ep->index)
		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(ep_desc) && !dir_in && (mps % 4)) अणु
			desc_size = mps;
			*mask = DEV_DMA_NBYTES_MASK;
		पूर्ण

	वापस desc_size;
पूर्ण

अटल व्योम dwc2_gadget_fill_nonisoc_xfer_ddma_one(काष्ठा dwc2_hsotg_ep *hs_ep,
						 काष्ठा dwc2_dma_desc **desc,
						 dma_addr_t dma_buff,
						 अचिन्हित पूर्णांक len,
						 bool true_last)
अणु
	पूर्णांक dir_in = hs_ep->dir_in;
	u32 mps = hs_ep->ep.maxpacket;
	u32 maxsize = 0;
	u32 offset = 0;
	u32 mask = 0;
	पूर्णांक i;

	maxsize = dwc2_gadget_get_desc_params(hs_ep, &mask);

	hs_ep->desc_count = (len / maxsize) +
				((len % maxsize) ? 1 : 0);
	अगर (len == 0)
		hs_ep->desc_count = 1;

	क्रम (i = 0; i < hs_ep->desc_count; ++i) अणु
		(*desc)->status = 0;
		(*desc)->status |= (DEV_DMA_BUFF_STS_HBUSY
				 << DEV_DMA_BUFF_STS_SHIFT);

		अगर (len > maxsize) अणु
			अगर (!hs_ep->index && !dir_in)
				(*desc)->status |= (DEV_DMA_L | DEV_DMA_IOC);

			(*desc)->status |=
				maxsize << DEV_DMA_NBYTES_SHIFT & mask;
			(*desc)->buf = dma_buff + offset;

			len -= maxsize;
			offset += maxsize;
		पूर्ण अन्यथा अणु
			अगर (true_last)
				(*desc)->status |= (DEV_DMA_L | DEV_DMA_IOC);

			अगर (dir_in)
				(*desc)->status |= (len % mps) ? DEV_DMA_SHORT :
					((hs_ep->send_zlp && true_last) ?
					DEV_DMA_SHORT : 0);

			(*desc)->status |=
				len << DEV_DMA_NBYTES_SHIFT & mask;
			(*desc)->buf = dma_buff + offset;
		पूर्ण

		(*desc)->status &= ~DEV_DMA_BUFF_STS_MASK;
		(*desc)->status |= (DEV_DMA_BUFF_STS_HREADY
				 << DEV_DMA_BUFF_STS_SHIFT);
		(*desc)++;
	पूर्ण
पूर्ण

/*
 * dwc2_gadget_config_nonisoc_xfer_ddma - prepare non ISOC DMA desc chain.
 * @hs_ep: The endpoपूर्णांक
 * @ureq: Request to transfer
 * @offset: offset in bytes
 * @len: Length of the transfer
 *
 * This function will iterate over descriptor chain and fill its entries
 * with corresponding inक्रमmation based on transfer data.
 */
अटल व्योम dwc2_gadget_config_nonisoc_xfer_ddma(काष्ठा dwc2_hsotg_ep *hs_ep,
						 dma_addr_t dma_buff,
						 अचिन्हित पूर्णांक len)
अणु
	काष्ठा usb_request *ureq = शून्य;
	काष्ठा dwc2_dma_desc *desc = hs_ep->desc_list;
	काष्ठा scatterlist *sg;
	पूर्णांक i;
	u8 desc_count = 0;

	अगर (hs_ep->req)
		ureq = &hs_ep->req->req;

	/* non-DMA sg buffer */
	अगर (!ureq || !ureq->num_sgs) अणु
		dwc2_gadget_fill_nonisoc_xfer_ddma_one(hs_ep, &desc,
			dma_buff, len, true);
		वापस;
	पूर्ण

	/* DMA sg buffer */
	क्रम_each_sg(ureq->sg, sg, ureq->num_sgs, i) अणु
		dwc2_gadget_fill_nonisoc_xfer_ddma_one(hs_ep, &desc,
			sg_dma_address(sg) + sg->offset, sg_dma_len(sg),
			sg_is_last(sg));
		desc_count += hs_ep->desc_count;
	पूर्ण

	hs_ep->desc_count = desc_count;
पूर्ण

/*
 * dwc2_gadget_fill_isoc_desc - fills next isochronous descriptor in chain.
 * @hs_ep: The isochronous endpoपूर्णांक.
 * @dma_buff: usb requests dma buffer.
 * @len: usb request transfer length.
 *
 * Fills next मुक्त descriptor with the data of the arrived usb request,
 * frame info, sets Last and IOC bits increments next_desc. If filled
 * descriptor is not the first one, हटाओs L bit from the previous descriptor
 * status.
 */
अटल पूर्णांक dwc2_gadget_fill_isoc_desc(काष्ठा dwc2_hsotg_ep *hs_ep,
				      dma_addr_t dma_buff, अचिन्हित पूर्णांक len)
अणु
	काष्ठा dwc2_dma_desc *desc;
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;
	u32 index;
	u32 mask = 0;
	u8 pid = 0;

	dwc2_gadget_get_desc_params(hs_ep, &mask);

	index = hs_ep->next_desc;
	desc = &hs_ep->desc_list[index];

	/* Check अगर descriptor chain full */
	अगर ((desc->status >> DEV_DMA_BUFF_STS_SHIFT) ==
	    DEV_DMA_BUFF_STS_HREADY) अणु
		dev_dbg(hsotg->dev, "%s: desc chain full\n", __func__);
		वापस 1;
	पूर्ण

	/* Clear L bit of previous desc अगर more than one entries in the chain */
	अगर (hs_ep->next_desc)
		hs_ep->desc_list[index - 1].status &= ~DEV_DMA_L;

	dev_dbg(hsotg->dev, "%s: Filling ep %d, dir %s isoc desc # %d\n",
		__func__, hs_ep->index, hs_ep->dir_in ? "in" : "out", index);

	desc->status = 0;
	desc->status |= (DEV_DMA_BUFF_STS_HBUSY	<< DEV_DMA_BUFF_STS_SHIFT);

	desc->buf = dma_buff;
	desc->status |= (DEV_DMA_L | DEV_DMA_IOC |
			 ((len << DEV_DMA_NBYTES_SHIFT) & mask));

	अगर (hs_ep->dir_in) अणु
		अगर (len)
			pid = DIV_ROUND_UP(len, hs_ep->ep.maxpacket);
		अन्यथा
			pid = 1;
		desc->status |= ((pid << DEV_DMA_ISOC_PID_SHIFT) &
				 DEV_DMA_ISOC_PID_MASK) |
				((len % hs_ep->ep.maxpacket) ?
				 DEV_DMA_SHORT : 0) |
				((hs_ep->target_frame <<
				  DEV_DMA_ISOC_FRNUM_SHIFT) &
				 DEV_DMA_ISOC_FRNUM_MASK);
	पूर्ण

	desc->status &= ~DEV_DMA_BUFF_STS_MASK;
	desc->status |= (DEV_DMA_BUFF_STS_HREADY << DEV_DMA_BUFF_STS_SHIFT);

	/* Increment frame number by पूर्णांकerval क्रम IN */
	अगर (hs_ep->dir_in)
		dwc2_gadget_incr_frame_num(hs_ep);

	/* Update index of last configured entry in the chain */
	hs_ep->next_desc++;
	अगर (hs_ep->next_desc >= MAX_DMA_DESC_NUM_HS_ISOC)
		hs_ep->next_desc = 0;

	वापस 0;
पूर्ण

/*
 * dwc2_gadget_start_isoc_ddma - start isochronous transfer in DDMA
 * @hs_ep: The isochronous endpoपूर्णांक.
 *
 * Prepare descriptor chain क्रम isochronous endpoपूर्णांकs. Afterwards
 * ग_लिखो DMA address to HW and enable the endpoपूर्णांक.
 */
अटल व्योम dwc2_gadget_start_isoc_ddma(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;
	काष्ठा dwc2_hsotg_req *hs_req, *treq;
	पूर्णांक index = hs_ep->index;
	पूर्णांक ret;
	पूर्णांक i;
	u32 dma_reg;
	u32 depctl;
	u32 ctrl;
	काष्ठा dwc2_dma_desc *desc;

	अगर (list_empty(&hs_ep->queue)) अणु
		hs_ep->target_frame = TARGET_FRAME_INITIAL;
		dev_dbg(hsotg->dev, "%s: No requests in queue\n", __func__);
		वापस;
	पूर्ण

	/* Initialize descriptor chain by Host Busy status */
	क्रम (i = 0; i < MAX_DMA_DESC_NUM_HS_ISOC; i++) अणु
		desc = &hs_ep->desc_list[i];
		desc->status = 0;
		desc->status |= (DEV_DMA_BUFF_STS_HBUSY
				    << DEV_DMA_BUFF_STS_SHIFT);
	पूर्ण

	hs_ep->next_desc = 0;
	list_क्रम_each_entry_safe(hs_req, treq, &hs_ep->queue, queue) अणु
		dma_addr_t dma_addr = hs_req->req.dma;

		अगर (hs_req->req.num_sgs) अणु
			WARN_ON(hs_req->req.num_sgs > 1);
			dma_addr = sg_dma_address(hs_req->req.sg);
		पूर्ण
		ret = dwc2_gadget_fill_isoc_desc(hs_ep, dma_addr,
						 hs_req->req.length);
		अगर (ret)
			अवरोध;
	पूर्ण

	hs_ep->compl_desc = 0;
	depctl = hs_ep->dir_in ? DIEPCTL(index) : DOEPCTL(index);
	dma_reg = hs_ep->dir_in ? DIEPDMA(index) : DOEPDMA(index);

	/* ग_लिखो descriptor chain address to control रेजिस्टर */
	dwc2_ग_लिखोl(hsotg, hs_ep->desc_list_dma, dma_reg);

	ctrl = dwc2_पढ़ोl(hsotg, depctl);
	ctrl |= DXEPCTL_EPENA | DXEPCTL_CNAK;
	dwc2_ग_लिखोl(hsotg, ctrl, depctl);
पूर्ण

/**
 * dwc2_hsotg_start_req - start a USB request from an endpoपूर्णांक's queue
 * @hsotg: The controller state.
 * @hs_ep: The endpoपूर्णांक to process a request क्रम
 * @hs_req: The request to start.
 * @continuing: True अगर we are करोing more क्रम the current request.
 *
 * Start the given request running by setting the endpoपूर्णांक रेजिस्टरs
 * appropriately, and writing any data to the FIFOs.
 */
अटल व्योम dwc2_hsotg_start_req(काष्ठा dwc2_hsotg *hsotg,
				 काष्ठा dwc2_hsotg_ep *hs_ep,
				काष्ठा dwc2_hsotg_req *hs_req,
				bool continuing)
अणु
	काष्ठा usb_request *ureq = &hs_req->req;
	पूर्णांक index = hs_ep->index;
	पूर्णांक dir_in = hs_ep->dir_in;
	u32 epctrl_reg;
	u32 epsize_reg;
	u32 epsize;
	u32 ctrl;
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक packets;
	अचिन्हित पूर्णांक maxreq;
	अचिन्हित पूर्णांक dma_reg;

	अगर (index != 0) अणु
		अगर (hs_ep->req && !continuing) अणु
			dev_err(hsotg->dev, "%s: active request\n", __func__);
			WARN_ON(1);
			वापस;
		पूर्ण अन्यथा अगर (hs_ep->req != hs_req && continuing) अणु
			dev_err(hsotg->dev,
				"%s: continue different req\n", __func__);
			WARN_ON(1);
			वापस;
		पूर्ण
	पूर्ण

	dma_reg = dir_in ? DIEPDMA(index) : DOEPDMA(index);
	epctrl_reg = dir_in ? DIEPCTL(index) : DOEPCTL(index);
	epsize_reg = dir_in ? DIEPTSIZ(index) : DOEPTSIZ(index);

	dev_dbg(hsotg->dev, "%s: DxEPCTL=0x%08x, ep %d, dir %s\n",
		__func__, dwc2_पढ़ोl(hsotg, epctrl_reg), index,
		hs_ep->dir_in ? "in" : "out");

	/* If endpoपूर्णांक is stalled, we will restart request later */
	ctrl = dwc2_पढ़ोl(hsotg, epctrl_reg);

	अगर (index && ctrl & DXEPCTL_STALL) अणु
		dev_warn(hsotg->dev, "%s: ep%d is stalled\n", __func__, index);
		वापस;
	पूर्ण

	length = ureq->length - ureq->actual;
	dev_dbg(hsotg->dev, "ureq->length:%d ureq->actual:%d\n",
		ureq->length, ureq->actual);

	अगर (!using_desc_dma(hsotg))
		maxreq = get_ep_limit(hs_ep);
	अन्यथा
		maxreq = dwc2_gadget_get_chain_limit(hs_ep);

	अगर (length > maxreq) अणु
		पूर्णांक round = maxreq % hs_ep->ep.maxpacket;

		dev_dbg(hsotg->dev, "%s: length %d, max-req %d, r %d\n",
			__func__, length, maxreq, round);

		/* round करोwn to multiple of packets */
		अगर (round)
			maxreq -= round;

		length = maxreq;
	पूर्ण

	अगर (length)
		packets = DIV_ROUND_UP(length, hs_ep->ep.maxpacket);
	अन्यथा
		packets = 1;	/* send one packet अगर length is zero. */

	अगर (dir_in && index != 0)
		अगर (hs_ep->isochronous)
			epsize = DXEPTSIZ_MC(packets);
		अन्यथा
			epsize = DXEPTSIZ_MC(1);
	अन्यथा
		epsize = 0;

	/*
	 * zero length packet should be programmed on its own and should not
	 * be counted in DIEPTSIZ.PktCnt with other packets.
	 */
	अगर (dir_in && ureq->zero && !continuing) अणु
		/* Test अगर zlp is actually required. */
		अगर ((ureq->length >= hs_ep->ep.maxpacket) &&
		    !(ureq->length % hs_ep->ep.maxpacket))
			hs_ep->send_zlp = 1;
	पूर्ण

	epsize |= DXEPTSIZ_PKTCNT(packets);
	epsize |= DXEPTSIZ_XFERSIZE(length);

	dev_dbg(hsotg->dev, "%s: %d@%d/%d, 0x%08x => 0x%08x\n",
		__func__, packets, length, ureq->length, epsize, epsize_reg);

	/* store the request as the current one we're करोing */
	hs_ep->req = hs_req;

	अगर (using_desc_dma(hsotg)) अणु
		u32 offset = 0;
		u32 mps = hs_ep->ep.maxpacket;

		/* Adjust length: EP0 - MPS, other OUT EPs - multiple of MPS */
		अगर (!dir_in) अणु
			अगर (!index)
				length = mps;
			अन्यथा अगर (length % mps)
				length += (mps - (length % mps));
		पूर्ण

		अगर (continuing)
			offset = ureq->actual;

		/* Fill DDMA chain entries */
		dwc2_gadget_config_nonisoc_xfer_ddma(hs_ep, ureq->dma + offset,
						     length);

		/* ग_लिखो descriptor chain address to control रेजिस्टर */
		dwc2_ग_लिखोl(hsotg, hs_ep->desc_list_dma, dma_reg);

		dev_dbg(hsotg->dev, "%s: %08x pad => 0x%08x\n",
			__func__, (u32)hs_ep->desc_list_dma, dma_reg);
	पूर्ण अन्यथा अणु
		/* ग_लिखो size / packets */
		dwc2_ग_लिखोl(hsotg, epsize, epsize_reg);

		अगर (using_dma(hsotg) && !continuing && (length != 0)) अणु
			/*
			 * ग_लिखो DMA address to control रेजिस्टर, buffer
			 * alपढ़ोy synced by dwc2_hsotg_ep_queue().
			 */

			dwc2_ग_लिखोl(hsotg, ureq->dma, dma_reg);

			dev_dbg(hsotg->dev, "%s: %pad => 0x%08x\n",
				__func__, &ureq->dma, dma_reg);
		पूर्ण
	पूर्ण

	अगर (hs_ep->isochronous && hs_ep->पूर्णांकerval == 1) अणु
		hs_ep->target_frame = dwc2_hsotg_पढ़ो_frameno(hsotg);
		dwc2_gadget_incr_frame_num(hs_ep);

		अगर (hs_ep->target_frame & 0x1)
			ctrl |= DXEPCTL_SETODDFR;
		अन्यथा
			ctrl |= DXEPCTL_SETEVENFR;
	पूर्ण

	ctrl |= DXEPCTL_EPENA;	/* ensure ep enabled */

	dev_dbg(hsotg->dev, "ep0 state:%d\n", hsotg->ep0_state);

	/* For Setup request करो not clear NAK */
	अगर (!(index == 0 && hsotg->ep0_state == DWC2_EP0_SETUP))
		ctrl |= DXEPCTL_CNAK;	/* clear NAK set by core */

	dev_dbg(hsotg->dev, "%s: DxEPCTL=0x%08x\n", __func__, ctrl);
	dwc2_ग_लिखोl(hsotg, ctrl, epctrl_reg);

	/*
	 * set these, it seems that DMA support increments past the end
	 * of the packet buffer so we need to calculate the length from
	 * this inक्रमmation.
	 */
	hs_ep->size_loaded = length;
	hs_ep->last_load = ureq->actual;

	अगर (dir_in && !using_dma(hsotg)) अणु
		/* set these anyway, we may need them क्रम non-periodic in */
		hs_ep->fअगरo_load = 0;

		dwc2_hsotg_ग_लिखो_fअगरo(hsotg, hs_ep, hs_req);
	पूर्ण

	/*
	 * Note, trying to clear the NAK here causes problems with transmit
	 * on the S3C6400 ending up with the TXFIFO becoming full.
	 */

	/* check ep is enabled */
	अगर (!(dwc2_पढ़ोl(hsotg, epctrl_reg) & DXEPCTL_EPENA))
		dev_dbg(hsotg->dev,
			"ep%d: failed to become enabled (DXEPCTL=0x%08x)?\n",
			 index, dwc2_पढ़ोl(hsotg, epctrl_reg));

	dev_dbg(hsotg->dev, "%s: DXEPCTL=0x%08x\n",
		__func__, dwc2_पढ़ोl(hsotg, epctrl_reg));

	/* enable ep पूर्णांकerrupts */
	dwc2_hsotg_ctrl_epपूर्णांक(hsotg, hs_ep->index, hs_ep->dir_in, 1);
पूर्ण

/**
 * dwc2_hsotg_map_dma - map the DMA memory being used क्रम the request
 * @hsotg: The device state.
 * @hs_ep: The endpoपूर्णांक the request is on.
 * @req: The request being processed.
 *
 * We've been asked to queue a request, so ensure that the memory buffer
 * is correctly setup क्रम DMA. If we've been passed an extant DMA address
 * then ensure the buffer has been synced to memory. If our buffer has no
 * DMA memory, then we map the memory and mark our request to allow us to
 * cleanup on completion.
 */
अटल पूर्णांक dwc2_hsotg_map_dma(काष्ठा dwc2_hsotg *hsotg,
			      काष्ठा dwc2_hsotg_ep *hs_ep,
			     काष्ठा usb_request *req)
अणु
	पूर्णांक ret;

	hs_ep->map_dir = hs_ep->dir_in;
	ret = usb_gadget_map_request(&hsotg->gadget, req, hs_ep->dir_in);
	अगर (ret)
		जाओ dma_error;

	वापस 0;

dma_error:
	dev_err(hsotg->dev, "%s: failed to map buffer %p, %d bytes\n",
		__func__, req->buf, req->length);

	वापस -EIO;
पूर्ण

अटल पूर्णांक dwc2_hsotg_handle_unaligned_buf_start(काष्ठा dwc2_hsotg *hsotg,
						 काष्ठा dwc2_hsotg_ep *hs_ep,
						 काष्ठा dwc2_hsotg_req *hs_req)
अणु
	व्योम *req_buf = hs_req->req.buf;

	/* If dma is not being used or buffer is aligned */
	अगर (!using_dma(hsotg) || !((दीर्घ)req_buf & 3))
		वापस 0;

	WARN_ON(hs_req->saved_req_buf);

	dev_dbg(hsotg->dev, "%s: %s: buf=%p length=%d\n", __func__,
		hs_ep->ep.name, req_buf, hs_req->req.length);

	hs_req->req.buf = kदो_स्मृति(hs_req->req.length, GFP_ATOMIC);
	अगर (!hs_req->req.buf) अणु
		hs_req->req.buf = req_buf;
		dev_err(hsotg->dev,
			"%s: unable to allocate memory for bounce buffer\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	/* Save actual buffer */
	hs_req->saved_req_buf = req_buf;

	अगर (hs_ep->dir_in)
		स_नकल(hs_req->req.buf, req_buf, hs_req->req.length);
	वापस 0;
पूर्ण

अटल व्योम
dwc2_hsotg_handle_unaligned_buf_complete(काष्ठा dwc2_hsotg *hsotg,
					 काष्ठा dwc2_hsotg_ep *hs_ep,
					 काष्ठा dwc2_hsotg_req *hs_req)
अणु
	/* If dma is not being used or buffer was aligned */
	अगर (!using_dma(hsotg) || !hs_req->saved_req_buf)
		वापस;

	dev_dbg(hsotg->dev, "%s: %s: status=%d actual-length=%d\n", __func__,
		hs_ep->ep.name, hs_req->req.status, hs_req->req.actual);

	/* Copy data from bounce buffer on successful out transfer */
	अगर (!hs_ep->dir_in && !hs_req->req.status)
		स_नकल(hs_req->saved_req_buf, hs_req->req.buf,
		       hs_req->req.actual);

	/* Free bounce buffer */
	kमुक्त(hs_req->req.buf);

	hs_req->req.buf = hs_req->saved_req_buf;
	hs_req->saved_req_buf = शून्य;
पूर्ण

/**
 * dwc2_gadget_target_frame_elapsed - Checks target frame
 * @hs_ep: The driver endpoपूर्णांक to check
 *
 * Returns 1 अगर targeted frame elapsed. If वापसed 1 then we need to drop
 * corresponding transfer.
 */
अटल bool dwc2_gadget_target_frame_elapsed(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;
	u32 target_frame = hs_ep->target_frame;
	u32 current_frame = hsotg->frame_number;
	bool frame_overrun = hs_ep->frame_overrun;

	अगर (!frame_overrun && current_frame >= target_frame)
		वापस true;

	अगर (frame_overrun && current_frame >= target_frame &&
	    ((current_frame - target_frame) < DSTS_SOFFN_LIMIT / 2))
		वापस true;

	वापस false;
पूर्ण

/*
 * dwc2_gadget_set_ep0_desc_chain - Set EP's desc chain poपूर्णांकers
 * @hsotg: The driver state
 * @hs_ep: the ep descriptor chain is क्रम
 *
 * Called to update EP0 काष्ठाure's poपूर्णांकers depend on stage of
 * control transfer.
 */
अटल पूर्णांक dwc2_gadget_set_ep0_desc_chain(काष्ठा dwc2_hsotg *hsotg,
					  काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	चयन (hsotg->ep0_state) अणु
	हाल DWC2_EP0_SETUP:
	हाल DWC2_EP0_STATUS_OUT:
		hs_ep->desc_list = hsotg->setup_desc[0];
		hs_ep->desc_list_dma = hsotg->setup_desc_dma[0];
		अवरोध;
	हाल DWC2_EP0_DATA_IN:
	हाल DWC2_EP0_STATUS_IN:
		hs_ep->desc_list = hsotg->ctrl_in_desc;
		hs_ep->desc_list_dma = hsotg->ctrl_in_desc_dma;
		अवरोध;
	हाल DWC2_EP0_DATA_OUT:
		hs_ep->desc_list = hsotg->ctrl_out_desc;
		hs_ep->desc_list_dma = hsotg->ctrl_out_desc_dma;
		अवरोध;
	शेष:
		dev_err(hsotg->dev, "invalid EP 0 state in queue %d\n",
			hsotg->ep0_state);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc2_hsotg_ep_queue(काष्ठा usb_ep *ep, काष्ठा usb_request *req,
			       gfp_t gfp_flags)
अणु
	काष्ठा dwc2_hsotg_req *hs_req = our_req(req);
	काष्ठा dwc2_hsotg_ep *hs_ep = our_ep(ep);
	काष्ठा dwc2_hsotg *hs = hs_ep->parent;
	bool first;
	पूर्णांक ret;
	u32 maxsize = 0;
	u32 mask = 0;


	dev_dbg(hs->dev, "%s: req %p: %d@%p, noi=%d, zero=%d, snok=%d\n",
		ep->name, req, req->length, req->buf, req->no_पूर्णांकerrupt,
		req->zero, req->लघु_not_ok);

	/* Prevent new request submission when controller is suspended */
	अगर (hs->lx_state != DWC2_L0) अणु
		dev_dbg(hs->dev, "%s: submit request only in active state\n",
			__func__);
		वापस -EAGAIN;
	पूर्ण

	/* initialise status of the request */
	INIT_LIST_HEAD(&hs_req->queue);
	req->actual = 0;
	req->status = -EINPROGRESS;

	/* Don't queue ISOC request अगर length greater than mps*mc */
	अगर (hs_ep->isochronous &&
	    req->length > (hs_ep->mc * hs_ep->ep.maxpacket)) अणु
		dev_err(hs->dev, "req length > maxpacket*mc\n");
		वापस -EINVAL;
	पूर्ण

	/* In DDMA mode क्रम ISOC's don't queue request अगर length greater
	 * than descriptor limits.
	 */
	अगर (using_desc_dma(hs) && hs_ep->isochronous) अणु
		maxsize = dwc2_gadget_get_desc_params(hs_ep, &mask);
		अगर (hs_ep->dir_in && req->length > maxsize) अणु
			dev_err(hs->dev, "wrong length %d (maxsize=%d)\n",
				req->length, maxsize);
			वापस -EINVAL;
		पूर्ण

		अगर (!hs_ep->dir_in && req->length > hs_ep->ep.maxpacket) अणु
			dev_err(hs->dev, "ISOC OUT: wrong length %d (mps=%d)\n",
				req->length, hs_ep->ep.maxpacket);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = dwc2_hsotg_handle_unaligned_buf_start(hs, hs_ep, hs_req);
	अगर (ret)
		वापस ret;

	/* अगर we're using DMA, sync the buffers as necessary */
	अगर (using_dma(hs)) अणु
		ret = dwc2_hsotg_map_dma(hs, hs_ep, req);
		अगर (ret)
			वापस ret;
	पूर्ण
	/* If using descriptor DMA configure EP0 descriptor chain poपूर्णांकers */
	अगर (using_desc_dma(hs) && !hs_ep->index) अणु
		ret = dwc2_gadget_set_ep0_desc_chain(hs, hs_ep);
		अगर (ret)
			वापस ret;
	पूर्ण

	first = list_empty(&hs_ep->queue);
	list_add_tail(&hs_req->queue, &hs_ep->queue);

	/*
	 * Handle DDMA isochronous transfers separately - just add new entry
	 * to the descriptor chain.
	 * Transfer will be started once SW माला_लो either one of NAK or
	 * OutTknEpDis पूर्णांकerrupts.
	 */
	अगर (using_desc_dma(hs) && hs_ep->isochronous) अणु
		अगर (hs_ep->target_frame != TARGET_FRAME_INITIAL) अणु
			dma_addr_t dma_addr = hs_req->req.dma;

			अगर (hs_req->req.num_sgs) अणु
				WARN_ON(hs_req->req.num_sgs > 1);
				dma_addr = sg_dma_address(hs_req->req.sg);
			पूर्ण
			dwc2_gadget_fill_isoc_desc(hs_ep, dma_addr,
						   hs_req->req.length);
		पूर्ण
		वापस 0;
	पूर्ण

	/* Change EP direction अगर status phase request is after data out */
	अगर (!hs_ep->index && !req->length && !hs_ep->dir_in &&
	    hs->ep0_state == DWC2_EP0_DATA_OUT)
		hs_ep->dir_in = 1;

	अगर (first) अणु
		अगर (!hs_ep->isochronous) अणु
			dwc2_hsotg_start_req(hs, hs_ep, hs_req, false);
			वापस 0;
		पूर्ण

		/* Update current frame number value. */
		hs->frame_number = dwc2_hsotg_पढ़ो_frameno(hs);
		जबतक (dwc2_gadget_target_frame_elapsed(hs_ep)) अणु
			dwc2_gadget_incr_frame_num(hs_ep);
			/* Update current frame number value once more as it
			 * changes here.
			 */
			hs->frame_number = dwc2_hsotg_पढ़ो_frameno(hs);
		पूर्ण

		अगर (hs_ep->target_frame != TARGET_FRAME_INITIAL)
			dwc2_hsotg_start_req(hs, hs_ep, hs_req, false);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dwc2_hsotg_ep_queue_lock(काष्ठा usb_ep *ep, काष्ठा usb_request *req,
				    gfp_t gfp_flags)
अणु
	काष्ठा dwc2_hsotg_ep *hs_ep = our_ep(ep);
	काष्ठा dwc2_hsotg *hs = hs_ep->parent;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&hs->lock, flags);
	ret = dwc2_hsotg_ep_queue(ep, req, gfp_flags);
	spin_unlock_irqrestore(&hs->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम dwc2_hsotg_ep_मुक्त_request(काष्ठा usb_ep *ep,
				       काष्ठा usb_request *req)
अणु
	काष्ठा dwc2_hsotg_req *hs_req = our_req(req);

	kमुक्त(hs_req);
पूर्ण

/**
 * dwc2_hsotg_complete_oursetup - setup completion callback
 * @ep: The endpoपूर्णांक the request was on.
 * @req: The request completed.
 *
 * Called on completion of any requests the driver itself
 * submitted that need cleaning up.
 */
अटल व्योम dwc2_hsotg_complete_oursetup(काष्ठा usb_ep *ep,
					 काष्ठा usb_request *req)
अणु
	काष्ठा dwc2_hsotg_ep *hs_ep = our_ep(ep);
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;

	dev_dbg(hsotg->dev, "%s: ep %p, req %p\n", __func__, ep, req);

	dwc2_hsotg_ep_मुक्त_request(ep, req);
पूर्ण

/**
 * ep_from_windex - convert control wIndex value to endpoपूर्णांक
 * @hsotg: The driver state.
 * @windex: The control request wIndex field (in host order).
 *
 * Convert the given wIndex पूर्णांकo a poपूर्णांकer to an driver endpoपूर्णांक
 * काष्ठाure, or वापस शून्य अगर it is not a valid endpoपूर्णांक.
 */
अटल काष्ठा dwc2_hsotg_ep *ep_from_windex(काष्ठा dwc2_hsotg *hsotg,
					    u32 windex)
अणु
	पूर्णांक dir = (windex & USB_सूची_IN) ? 1 : 0;
	पूर्णांक idx = windex & 0x7F;

	अगर (windex >= 0x100)
		वापस शून्य;

	अगर (idx > hsotg->num_of_eps)
		वापस शून्य;

	वापस index_to_ep(hsotg, idx, dir);
पूर्ण

/**
 * dwc2_hsotg_set_test_mode - Enable usb Test Modes
 * @hsotg: The driver state.
 * @tesपंचांगode: requested usb test mode
 * Enable usb Test Mode requested by the Host.
 */
पूर्णांक dwc2_hsotg_set_test_mode(काष्ठा dwc2_hsotg *hsotg, पूर्णांक tesपंचांगode)
अणु
	पूर्णांक dctl = dwc2_पढ़ोl(hsotg, DCTL);

	dctl &= ~DCTL_TSTCTL_MASK;
	चयन (tesपंचांगode) अणु
	हाल USB_TEST_J:
	हाल USB_TEST_K:
	हाल USB_TEST_SE0_NAK:
	हाल USB_TEST_PACKET:
	हाल USB_TEST_FORCE_ENABLE:
		dctl |= tesपंचांगode << DCTL_TSTCTL_SHIFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	dwc2_ग_लिखोl(hsotg, dctl, DCTL);
	वापस 0;
पूर्ण

/**
 * dwc2_hsotg_send_reply - send reply to control request
 * @hsotg: The device state
 * @ep: Endpoपूर्णांक 0
 * @buff: Buffer क्रम request
 * @length: Length of reply.
 *
 * Create a request and queue it on the given endpoपूर्णांक. This is useful as
 * an पूर्णांकernal method of sending replies to certain control requests, etc.
 */
अटल पूर्णांक dwc2_hsotg_send_reply(काष्ठा dwc2_hsotg *hsotg,
				 काष्ठा dwc2_hsotg_ep *ep,
				व्योम *buff,
				पूर्णांक length)
अणु
	काष्ठा usb_request *req;
	पूर्णांक ret;

	dev_dbg(hsotg->dev, "%s: buff %p, len %d\n", __func__, buff, length);

	req = dwc2_hsotg_ep_alloc_request(&ep->ep, GFP_ATOMIC);
	hsotg->ep0_reply = req;
	अगर (!req) अणु
		dev_warn(hsotg->dev, "%s: cannot alloc req\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	req->buf = hsotg->ep0_buff;
	req->length = length;
	/*
	 * zero flag is क्रम sending zlp in DATA IN stage. It has no impact on
	 * STATUS stage.
	 */
	req->zero = 0;
	req->complete = dwc2_hsotg_complete_oursetup;

	अगर (length)
		स_नकल(req->buf, buff, length);

	ret = dwc2_hsotg_ep_queue(&ep->ep, req, GFP_ATOMIC);
	अगर (ret) अणु
		dev_warn(hsotg->dev, "%s: cannot queue req\n", __func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dwc2_hsotg_process_req_status - process request GET_STATUS
 * @hsotg: The device state
 * @ctrl: USB control request
 */
अटल पूर्णांक dwc2_hsotg_process_req_status(काष्ठा dwc2_hsotg *hsotg,
					 काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा dwc2_hsotg_ep *ep0 = hsotg->eps_out[0];
	काष्ठा dwc2_hsotg_ep *ep;
	__le16 reply;
	u16 status;
	पूर्णांक ret;

	dev_dbg(hsotg->dev, "%s: USB_REQ_GET_STATUS\n", __func__);

	अगर (!ep0->dir_in) अणु
		dev_warn(hsotg->dev, "%s: direction out?\n", __func__);
		वापस -EINVAL;
	पूर्ण

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		status = hsotg->gadget.is_selfघातered <<
			 USB_DEVICE_SELF_POWERED;
		status |= hsotg->remote_wakeup_allowed <<
			  USB_DEVICE_REMOTE_WAKEUP;
		reply = cpu_to_le16(status);
		अवरोध;

	हाल USB_RECIP_INTERFACE:
		/* currently, the data result should be zero */
		reply = cpu_to_le16(0);
		अवरोध;

	हाल USB_RECIP_ENDPOINT:
		ep = ep_from_windex(hsotg, le16_to_cpu(ctrl->wIndex));
		अगर (!ep)
			वापस -ENOENT;

		reply = cpu_to_le16(ep->halted ? 1 : 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	अगर (le16_to_cpu(ctrl->wLength) != 2)
		वापस -EINVAL;

	ret = dwc2_hsotg_send_reply(hsotg, ep0, &reply, 2);
	अगर (ret) अणु
		dev_err(hsotg->dev, "%s: failed to send reply\n", __func__);
		वापस ret;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक dwc2_hsotg_ep_sethalt(काष्ठा usb_ep *ep, पूर्णांक value, bool now);

/**
 * get_ep_head - वापस the first request on the endpoपूर्णांक
 * @hs_ep: The controller endpoपूर्णांक to get
 *
 * Get the first request on the endpoपूर्णांक.
 */
अटल काष्ठा dwc2_hsotg_req *get_ep_head(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	वापस list_first_entry_or_null(&hs_ep->queue, काष्ठा dwc2_hsotg_req,
					queue);
पूर्ण

/**
 * dwc2_gadget_start_next_request - Starts next request from ep queue
 * @hs_ep: Endpoपूर्णांक काष्ठाure
 *
 * If queue is empty and EP is ISOC-OUT - unmasks OUTTKNEPDIS which is masked
 * in its handler. Hence we need to unmask it here to be able to करो
 * resynchronization.
 */
अटल व्योम dwc2_gadget_start_next_request(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	u32 mask;
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;
	पूर्णांक dir_in = hs_ep->dir_in;
	काष्ठा dwc2_hsotg_req *hs_req;
	u32 epmsk_reg = dir_in ? DIEPMSK : DOEPMSK;

	अगर (!list_empty(&hs_ep->queue)) अणु
		hs_req = get_ep_head(hs_ep);
		dwc2_hsotg_start_req(hsotg, hs_ep, hs_req, false);
		वापस;
	पूर्ण
	अगर (!hs_ep->isochronous)
		वापस;

	अगर (dir_in) अणु
		dev_dbg(hsotg->dev, "%s: No more ISOC-IN requests\n",
			__func__);
	पूर्ण अन्यथा अणु
		dev_dbg(hsotg->dev, "%s: No more ISOC-OUT requests\n",
			__func__);
		mask = dwc2_पढ़ोl(hsotg, epmsk_reg);
		mask |= DOEPMSK_OUTTKNEPDISMSK;
		dwc2_ग_लिखोl(hsotg, mask, epmsk_reg);
	पूर्ण
पूर्ण

/**
 * dwc2_hsotg_process_req_feature - process request अणुSET,CLEARपूर्ण_FEATURE
 * @hsotg: The device state
 * @ctrl: USB control request
 */
अटल पूर्णांक dwc2_hsotg_process_req_feature(काष्ठा dwc2_hsotg *hsotg,
					  काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा dwc2_hsotg_ep *ep0 = hsotg->eps_out[0];
	काष्ठा dwc2_hsotg_req *hs_req;
	bool set = (ctrl->bRequest == USB_REQ_SET_FEATURE);
	काष्ठा dwc2_hsotg_ep *ep;
	पूर्णांक ret;
	bool halted;
	u32 recip;
	u32 wValue;
	u32 wIndex;

	dev_dbg(hsotg->dev, "%s: %s_FEATURE\n",
		__func__, set ? "SET" : "CLEAR");

	wValue = le16_to_cpu(ctrl->wValue);
	wIndex = le16_to_cpu(ctrl->wIndex);
	recip = ctrl->bRequestType & USB_RECIP_MASK;

	चयन (recip) अणु
	हाल USB_RECIP_DEVICE:
		चयन (wValue) अणु
		हाल USB_DEVICE_REMOTE_WAKEUP:
			अगर (set)
				hsotg->remote_wakeup_allowed = 1;
			अन्यथा
				hsotg->remote_wakeup_allowed = 0;
			अवरोध;

		हाल USB_DEVICE_TEST_MODE:
			अगर ((wIndex & 0xff) != 0)
				वापस -EINVAL;
			अगर (!set)
				वापस -EINVAL;

			hsotg->test_mode = wIndex >> 8;
			अवरोध;
		शेष:
			वापस -ENOENT;
		पूर्ण

		ret = dwc2_hsotg_send_reply(hsotg, ep0, शून्य, 0);
		अगर (ret) अणु
			dev_err(hsotg->dev,
				"%s: failed to send reply\n", __func__);
			वापस ret;
		पूर्ण
		अवरोध;

	हाल USB_RECIP_ENDPOINT:
		ep = ep_from_windex(hsotg, wIndex);
		अगर (!ep) अणु
			dev_dbg(hsotg->dev, "%s: no endpoint for 0x%04x\n",
				__func__, wIndex);
			वापस -ENOENT;
		पूर्ण

		चयन (wValue) अणु
		हाल USB_ENDPOINT_HALT:
			halted = ep->halted;

			dwc2_hsotg_ep_sethalt(&ep->ep, set, true);

			ret = dwc2_hsotg_send_reply(hsotg, ep0, शून्य, 0);
			अगर (ret) अणु
				dev_err(hsotg->dev,
					"%s: failed to send reply\n", __func__);
				वापस ret;
			पूर्ण

			/*
			 * we have to complete all requests क्रम ep अगर it was
			 * halted, and the halt was cleared by CLEAR_FEATURE
			 */

			अगर (!set && halted) अणु
				/*
				 * If we have request in progress,
				 * then complete it
				 */
				अगर (ep->req) अणु
					hs_req = ep->req;
					ep->req = शून्य;
					list_del_init(&hs_req->queue);
					अगर (hs_req->req.complete) अणु
						spin_unlock(&hsotg->lock);
						usb_gadget_giveback_request(
							&ep->ep, &hs_req->req);
						spin_lock(&hsotg->lock);
					पूर्ण
				पूर्ण

				/* If we have pending request, then start it */
				अगर (!ep->req)
					dwc2_gadget_start_next_request(ep);
			पूर्ण

			अवरोध;

		शेष:
			वापस -ENOENT;
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम dwc2_hsotg_enqueue_setup(काष्ठा dwc2_hsotg *hsotg);

/**
 * dwc2_hsotg_stall_ep0 - stall ep0
 * @hsotg: The device state
 *
 * Set stall क्रम ep0 as response क्रम setup request.
 */
अटल व्योम dwc2_hsotg_stall_ep0(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_hsotg_ep *ep0 = hsotg->eps_out[0];
	u32 reg;
	u32 ctrl;

	dev_dbg(hsotg->dev, "ep0 stall (dir=%d)\n", ep0->dir_in);
	reg = (ep0->dir_in) ? DIEPCTL0 : DOEPCTL0;

	/*
	 * DxEPCTL_Stall will be cleared by EP once it has
	 * taken effect, so no need to clear later.
	 */

	ctrl = dwc2_पढ़ोl(hsotg, reg);
	ctrl |= DXEPCTL_STALL;
	ctrl |= DXEPCTL_CNAK;
	dwc2_ग_लिखोl(hsotg, ctrl, reg);

	dev_dbg(hsotg->dev,
		"written DXEPCTL=0x%08x to %08x (DXEPCTL=0x%08x)\n",
		ctrl, reg, dwc2_पढ़ोl(hsotg, reg));

	 /*
	  * complete won't be called, so we enqueue
	  * setup request here
	  */
	 dwc2_hsotg_enqueue_setup(hsotg);
पूर्ण

/**
 * dwc2_hsotg_process_control - process a control request
 * @hsotg: The device state
 * @ctrl: The control request received
 *
 * The controller has received the SETUP phase of a control request, and
 * needs to work out what to करो next (and whether to pass it on to the
 * gadget driver).
 */
अटल व्योम dwc2_hsotg_process_control(काष्ठा dwc2_hsotg *hsotg,
				       काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा dwc2_hsotg_ep *ep0 = hsotg->eps_out[0];
	पूर्णांक ret = 0;
	u32 dcfg;

	dev_dbg(hsotg->dev,
		"ctrl Type=%02x, Req=%02x, V=%04x, I=%04x, L=%04x\n",
		ctrl->bRequestType, ctrl->bRequest, ctrl->wValue,
		ctrl->wIndex, ctrl->wLength);

	अगर (ctrl->wLength == 0) अणु
		ep0->dir_in = 1;
		hsotg->ep0_state = DWC2_EP0_STATUS_IN;
	पूर्ण अन्यथा अगर (ctrl->bRequestType & USB_सूची_IN) अणु
		ep0->dir_in = 1;
		hsotg->ep0_state = DWC2_EP0_DATA_IN;
	पूर्ण अन्यथा अणु
		ep0->dir_in = 0;
		hsotg->ep0_state = DWC2_EP0_DATA_OUT;
	पूर्ण

	अगर ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) अणु
		चयन (ctrl->bRequest) अणु
		हाल USB_REQ_SET_ADDRESS:
			hsotg->connected = 1;
			dcfg = dwc2_पढ़ोl(hsotg, DCFG);
			dcfg &= ~DCFG_DEVADDR_MASK;
			dcfg |= (le16_to_cpu(ctrl->wValue) <<
				 DCFG_DEVADDR_SHIFT) & DCFG_DEVADDR_MASK;
			dwc2_ग_लिखोl(hsotg, dcfg, DCFG);

			dev_info(hsotg->dev, "new address %d\n", ctrl->wValue);

			ret = dwc2_hsotg_send_reply(hsotg, ep0, शून्य, 0);
			वापस;

		हाल USB_REQ_GET_STATUS:
			ret = dwc2_hsotg_process_req_status(hsotg, ctrl);
			अवरोध;

		हाल USB_REQ_CLEAR_FEATURE:
		हाल USB_REQ_SET_FEATURE:
			ret = dwc2_hsotg_process_req_feature(hsotg, ctrl);
			अवरोध;
		पूर्ण
	पूर्ण

	/* as a fallback, try delivering it to the driver to deal with */

	अगर (ret == 0 && hsotg->driver) अणु
		spin_unlock(&hsotg->lock);
		ret = hsotg->driver->setup(&hsotg->gadget, ctrl);
		spin_lock(&hsotg->lock);
		अगर (ret < 0)
			dev_dbg(hsotg->dev, "driver->setup() ret %d\n", ret);
	पूर्ण

	hsotg->delayed_status = false;
	अगर (ret == USB_GADGET_DELAYED_STATUS)
		hsotg->delayed_status = true;

	/*
	 * the request is either unhandlable, or is not क्रमmatted correctly
	 * so respond with a STALL क्रम the status stage to indicate failure.
	 */

	अगर (ret < 0)
		dwc2_hsotg_stall_ep0(hsotg);
पूर्ण

/**
 * dwc2_hsotg_complete_setup - completion of a setup transfer
 * @ep: The endpoपूर्णांक the request was on.
 * @req: The request completed.
 *
 * Called on completion of any requests the driver itself submitted क्रम
 * EP0 setup packets
 */
अटल व्योम dwc2_hsotg_complete_setup(काष्ठा usb_ep *ep,
				      काष्ठा usb_request *req)
अणु
	काष्ठा dwc2_hsotg_ep *hs_ep = our_ep(ep);
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;

	अगर (req->status < 0) अणु
		dev_dbg(hsotg->dev, "%s: failed %d\n", __func__, req->status);
		वापस;
	पूर्ण

	spin_lock(&hsotg->lock);
	अगर (req->actual == 0)
		dwc2_hsotg_enqueue_setup(hsotg);
	अन्यथा
		dwc2_hsotg_process_control(hsotg, req->buf);
	spin_unlock(&hsotg->lock);
पूर्ण

/**
 * dwc2_hsotg_enqueue_setup - start a request क्रम EP0 packets
 * @hsotg: The device state.
 *
 * Enqueue a request on EP0 अगर necessary to received any SETUP packets
 * received from the host.
 */
अटल व्योम dwc2_hsotg_enqueue_setup(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा usb_request *req = hsotg->ctrl_req;
	काष्ठा dwc2_hsotg_req *hs_req = our_req(req);
	पूर्णांक ret;

	dev_dbg(hsotg->dev, "%s: queueing setup request\n", __func__);

	req->zero = 0;
	req->length = 8;
	req->buf = hsotg->ctrl_buff;
	req->complete = dwc2_hsotg_complete_setup;

	अगर (!list_empty(&hs_req->queue)) अणु
		dev_dbg(hsotg->dev, "%s already queued???\n", __func__);
		वापस;
	पूर्ण

	hsotg->eps_out[0]->dir_in = 0;
	hsotg->eps_out[0]->send_zlp = 0;
	hsotg->ep0_state = DWC2_EP0_SETUP;

	ret = dwc2_hsotg_ep_queue(&hsotg->eps_out[0]->ep, req, GFP_ATOMIC);
	अगर (ret < 0) अणु
		dev_err(hsotg->dev, "%s: failed queue (%d)\n", __func__, ret);
		/*
		 * Don't think there's much we can करो other than watch the
		 * driver fail.
		 */
	पूर्ण
पूर्ण

अटल व्योम dwc2_hsotg_program_zlp(काष्ठा dwc2_hsotg *hsotg,
				   काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	u32 ctrl;
	u8 index = hs_ep->index;
	u32 epctl_reg = hs_ep->dir_in ? DIEPCTL(index) : DOEPCTL(index);
	u32 epsiz_reg = hs_ep->dir_in ? DIEPTSIZ(index) : DOEPTSIZ(index);

	अगर (hs_ep->dir_in)
		dev_dbg(hsotg->dev, "Sending zero-length packet on ep%d\n",
			index);
	अन्यथा
		dev_dbg(hsotg->dev, "Receiving zero-length packet on ep%d\n",
			index);
	अगर (using_desc_dma(hsotg)) अणु
		/* Not specअगरic buffer needed क्रम ep0 ZLP */
		dma_addr_t dma = hs_ep->desc_list_dma;

		अगर (!index)
			dwc2_gadget_set_ep0_desc_chain(hsotg, hs_ep);

		dwc2_gadget_config_nonisoc_xfer_ddma(hs_ep, dma, 0);
	पूर्ण अन्यथा अणु
		dwc2_ग_लिखोl(hsotg, DXEPTSIZ_MC(1) | DXEPTSIZ_PKTCNT(1) |
			    DXEPTSIZ_XFERSIZE(0),
			    epsiz_reg);
	पूर्ण

	ctrl = dwc2_पढ़ोl(hsotg, epctl_reg);
	ctrl |= DXEPCTL_CNAK;  /* clear NAK set by core */
	ctrl |= DXEPCTL_EPENA; /* ensure ep enabled */
	ctrl |= DXEPCTL_USBACTEP;
	dwc2_ग_लिखोl(hsotg, ctrl, epctl_reg);
पूर्ण

/**
 * dwc2_hsotg_complete_request - complete a request given to us
 * @hsotg: The device state.
 * @hs_ep: The endpoपूर्णांक the request was on.
 * @hs_req: The request to complete.
 * @result: The result code (0 => Ok, otherwise त्रुटि_सं)
 *
 * The given request has finished, so call the necessary completion
 * अगर it has one and then look to see अगर we can start a new request
 * on the endpoपूर्णांक.
 *
 * Note, expects the ep to alपढ़ोy be locked as appropriate.
 */
अटल व्योम dwc2_hsotg_complete_request(काष्ठा dwc2_hsotg *hsotg,
					काष्ठा dwc2_hsotg_ep *hs_ep,
				       काष्ठा dwc2_hsotg_req *hs_req,
				       पूर्णांक result)
अणु
	अगर (!hs_req) अणु
		dev_dbg(hsotg->dev, "%s: nothing to complete?\n", __func__);
		वापस;
	पूर्ण

	dev_dbg(hsotg->dev, "complete: ep %p %s, req %p, %d => %p\n",
		hs_ep, hs_ep->ep.name, hs_req, result, hs_req->req.complete);

	/*
	 * only replace the status अगर we've not alपढ़ोy set an error
	 * from a previous transaction
	 */

	अगर (hs_req->req.status == -EINPROGRESS)
		hs_req->req.status = result;

	अगर (using_dma(hsotg))
		dwc2_hsotg_unmap_dma(hsotg, hs_ep, hs_req);

	dwc2_hsotg_handle_unaligned_buf_complete(hsotg, hs_ep, hs_req);

	hs_ep->req = शून्य;
	list_del_init(&hs_req->queue);

	/*
	 * call the complete request with the locks off, just in हाल the
	 * request tries to queue more work क्रम this endpoपूर्णांक.
	 */

	अगर (hs_req->req.complete) अणु
		spin_unlock(&hsotg->lock);
		usb_gadget_giveback_request(&hs_ep->ep, &hs_req->req);
		spin_lock(&hsotg->lock);
	पूर्ण

	/* In DDMA करोn't need to proceed to starting of next ISOC request */
	अगर (using_desc_dma(hsotg) && hs_ep->isochronous)
		वापस;

	/*
	 * Look to see अगर there is anything अन्यथा to करो. Note, the completion
	 * of the previous request may have caused a new request to be started
	 * so be careful when करोing this.
	 */

	अगर (!hs_ep->req && result >= 0)
		dwc2_gadget_start_next_request(hs_ep);
पूर्ण

/*
 * dwc2_gadget_complete_isoc_request_ddma - complete an isoc request in DDMA
 * @hs_ep: The endpoपूर्णांक the request was on.
 *
 * Get first request from the ep queue, determine descriptor on which complete
 * happened. SW discovers which descriptor currently in use by HW, adjusts
 * dma_address and calculates index of completed descriptor based on the value
 * of DEPDMA रेजिस्टर. Update actual length of request, giveback to gadget.
 */
अटल व्योम dwc2_gadget_complete_isoc_request_ddma(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;
	काष्ठा dwc2_hsotg_req *hs_req;
	काष्ठा usb_request *ureq;
	u32 desc_sts;
	u32 mask;

	desc_sts = hs_ep->desc_list[hs_ep->compl_desc].status;

	/* Process only descriptors with buffer status set to DMA करोne */
	जबतक ((desc_sts & DEV_DMA_BUFF_STS_MASK) >>
		DEV_DMA_BUFF_STS_SHIFT == DEV_DMA_BUFF_STS_DMADONE) अणु

		hs_req = get_ep_head(hs_ep);
		अगर (!hs_req) अणु
			dev_warn(hsotg->dev, "%s: ISOC EP queue empty\n", __func__);
			वापस;
		पूर्ण
		ureq = &hs_req->req;

		/* Check completion status */
		अगर ((desc_sts & DEV_DMA_STS_MASK) >> DEV_DMA_STS_SHIFT ==
			DEV_DMA_STS_SUCC) अणु
			mask = hs_ep->dir_in ? DEV_DMA_ISOC_TX_NBYTES_MASK :
				DEV_DMA_ISOC_RX_NBYTES_MASK;
			ureq->actual = ureq->length - ((desc_sts & mask) >>
				DEV_DMA_ISOC_NBYTES_SHIFT);

			/* Adjust actual len क्रम ISOC Out अगर len is
			 * not align of 4
			 */
			अगर (!hs_ep->dir_in && ureq->length & 0x3)
				ureq->actual += 4 - (ureq->length & 0x3);

			/* Set actual frame number क्रम completed transfers */
			ureq->frame_number =
				(desc_sts & DEV_DMA_ISOC_FRNUM_MASK) >>
				DEV_DMA_ISOC_FRNUM_SHIFT;
		पूर्ण

		dwc2_hsotg_complete_request(hsotg, hs_ep, hs_req, 0);

		hs_ep->compl_desc++;
		अगर (hs_ep->compl_desc > (MAX_DMA_DESC_NUM_HS_ISOC - 1))
			hs_ep->compl_desc = 0;
		desc_sts = hs_ep->desc_list[hs_ep->compl_desc].status;
	पूर्ण
पूर्ण

/*
 * dwc2_gadget_handle_isoc_bna - handle BNA पूर्णांकerrupt क्रम ISOC.
 * @hs_ep: The isochronous endpoपूर्णांक.
 *
 * If EP ISOC OUT then need to flush RX FIFO to हटाओ source of BNA
 * पूर्णांकerrupt. Reset target frame and next_desc to allow to start
 * ISOC's on NAK पूर्णांकerrupt क्रम IN direction or on OUTTKNEPDIS
 * पूर्णांकerrupt क्रम OUT direction.
 */
अटल व्योम dwc2_gadget_handle_isoc_bna(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;

	अगर (!hs_ep->dir_in)
		dwc2_flush_rx_fअगरo(hsotg);
	dwc2_hsotg_complete_request(hsotg, hs_ep, get_ep_head(hs_ep), 0);

	hs_ep->target_frame = TARGET_FRAME_INITIAL;
	hs_ep->next_desc = 0;
	hs_ep->compl_desc = 0;
पूर्ण

/**
 * dwc2_hsotg_rx_data - receive data from the FIFO क्रम an endpoपूर्णांक
 * @hsotg: The device state.
 * @ep_idx: The endpoपूर्णांक index क्रम the data
 * @size: The size of data in the fअगरo, in bytes
 *
 * The FIFO status shows there is data to पढ़ो from the FIFO क्रम a given
 * endpoपूर्णांक, so sort out whether we need to पढ़ो the data पूर्णांकo a request
 * that has been made क्रम that endpoपूर्णांक.
 */
अटल व्योम dwc2_hsotg_rx_data(काष्ठा dwc2_hsotg *hsotg, पूर्णांक ep_idx, पूर्णांक size)
अणु
	काष्ठा dwc2_hsotg_ep *hs_ep = hsotg->eps_out[ep_idx];
	काष्ठा dwc2_hsotg_req *hs_req = hs_ep->req;
	पूर्णांक to_पढ़ो;
	पूर्णांक max_req;
	पूर्णांक पढ़ो_ptr;

	अगर (!hs_req) अणु
		u32 epctl = dwc2_पढ़ोl(hsotg, DOEPCTL(ep_idx));
		पूर्णांक ptr;

		dev_dbg(hsotg->dev,
			"%s: FIFO %d bytes on ep%d but no req (DXEPCTl=0x%08x)\n",
			 __func__, size, ep_idx, epctl);

		/* dump the data from the FIFO, we've nothing we can करो */
		क्रम (ptr = 0; ptr < size; ptr += 4)
			(व्योम)dwc2_पढ़ोl(hsotg, EPFIFO(ep_idx));

		वापस;
	पूर्ण

	to_पढ़ो = size;
	पढ़ो_ptr = hs_req->req.actual;
	max_req = hs_req->req.length - पढ़ो_ptr;

	dev_dbg(hsotg->dev, "%s: read %d/%d, done %d/%d\n",
		__func__, to_पढ़ो, max_req, पढ़ो_ptr, hs_req->req.length);

	अगर (to_पढ़ो > max_req) अणु
		/*
		 * more data appeared than we where willing
		 * to deal with in this request.
		 */

		/* currently we करोn't deal this */
		WARN_ON_ONCE(1);
	पूर्ण

	hs_ep->total_data += to_पढ़ो;
	hs_req->req.actual += to_पढ़ो;
	to_पढ़ो = DIV_ROUND_UP(to_पढ़ो, 4);

	/*
	 * note, we might over-ग_लिखो the buffer end by 3 bytes depending on
	 * alignment of the data.
	 */
	dwc2_पढ़ोl_rep(hsotg, EPFIFO(ep_idx),
		       hs_req->req.buf + पढ़ो_ptr, to_पढ़ो);
पूर्ण

/**
 * dwc2_hsotg_ep0_zlp - send/receive zero-length packet on control endpoपूर्णांक
 * @hsotg: The device instance
 * @dir_in: If IN zlp
 *
 * Generate a zero-length IN packet request क्रम terminating a SETUP
 * transaction.
 *
 * Note, since we करोn't ग_लिखो any data to the TxFIFO, then it is
 * currently believed that we करो not need to रुको क्रम any space in
 * the TxFIFO.
 */
अटल व्योम dwc2_hsotg_ep0_zlp(काष्ठा dwc2_hsotg *hsotg, bool dir_in)
अणु
	/* eps_out[0] is used in both directions */
	hsotg->eps_out[0]->dir_in = dir_in;
	hsotg->ep0_state = dir_in ? DWC2_EP0_STATUS_IN : DWC2_EP0_STATUS_OUT;

	dwc2_hsotg_program_zlp(hsotg, hsotg->eps_out[0]);
पूर्ण

अटल व्योम dwc2_hsotg_change_ep_iso_parity(काष्ठा dwc2_hsotg *hsotg,
					    u32 epctl_reg)
अणु
	u32 ctrl;

	ctrl = dwc2_पढ़ोl(hsotg, epctl_reg);
	अगर (ctrl & DXEPCTL_खातापूर्णRNUM)
		ctrl |= DXEPCTL_SETEVENFR;
	अन्यथा
		ctrl |= DXEPCTL_SETODDFR;
	dwc2_ग_लिखोl(hsotg, ctrl, epctl_reg);
पूर्ण

/*
 * dwc2_gadget_get_xfersize_ddma - get transferred bytes amount from desc
 * @hs_ep - The endpoपूर्णांक on which transfer went
 *
 * Iterate over endpoपूर्णांकs descriptor chain and get info on bytes reमुख्यed
 * in DMA descriptors after transfer has completed. Used क्रम non isoc EPs.
 */
अटल अचिन्हित पूर्णांक dwc2_gadget_get_xfersize_ddma(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc = hs_ep->ep.desc;
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;
	अचिन्हित पूर्णांक bytes_rem = 0;
	अचिन्हित पूर्णांक bytes_rem_correction = 0;
	काष्ठा dwc2_dma_desc *desc = hs_ep->desc_list;
	पूर्णांक i;
	u32 status;
	u32 mps = hs_ep->ep.maxpacket;
	पूर्णांक dir_in = hs_ep->dir_in;

	अगर (!desc)
		वापस -EINVAL;

	/* Interrupt OUT EP with mps not multiple of 4 */
	अगर (hs_ep->index)
		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(ep_desc) && !dir_in && (mps % 4))
			bytes_rem_correction = 4 - (mps % 4);

	क्रम (i = 0; i < hs_ep->desc_count; ++i) अणु
		status = desc->status;
		bytes_rem += status & DEV_DMA_NBYTES_MASK;
		bytes_rem -= bytes_rem_correction;

		अगर (status & DEV_DMA_STS_MASK)
			dev_err(hsotg->dev, "descriptor %d closed with %x\n",
				i, status & DEV_DMA_STS_MASK);

		अगर (status & DEV_DMA_L)
			अवरोध;

		desc++;
	पूर्ण

	वापस bytes_rem;
पूर्ण

/**
 * dwc2_hsotg_handle_outकरोne - handle receiving OutDone/SetupDone from RXFIFO
 * @hsotg: The device instance
 * @epnum: The endpoपूर्णांक received from
 *
 * The RXFIFO has delivered an OutDone event, which means that the data
 * transfer क्रम an OUT endpoपूर्णांक has been completed, either by a लघु
 * packet or by the finish of a transfer.
 */
अटल व्योम dwc2_hsotg_handle_outकरोne(काष्ठा dwc2_hsotg *hsotg, पूर्णांक epnum)
अणु
	u32 epsize = dwc2_पढ़ोl(hsotg, DOEPTSIZ(epnum));
	काष्ठा dwc2_hsotg_ep *hs_ep = hsotg->eps_out[epnum];
	काष्ठा dwc2_hsotg_req *hs_req = hs_ep->req;
	काष्ठा usb_request *req = &hs_req->req;
	अचिन्हित पूर्णांक size_left = DXEPTSIZ_XFERSIZE_GET(epsize);
	पूर्णांक result = 0;

	अगर (!hs_req) अणु
		dev_dbg(hsotg->dev, "%s: no request active\n", __func__);
		वापस;
	पूर्ण

	अगर (epnum == 0 && hsotg->ep0_state == DWC2_EP0_STATUS_OUT) अणु
		dev_dbg(hsotg->dev, "zlp packet received\n");
		dwc2_hsotg_complete_request(hsotg, hs_ep, hs_req, 0);
		dwc2_hsotg_enqueue_setup(hsotg);
		वापस;
	पूर्ण

	अगर (using_desc_dma(hsotg))
		size_left = dwc2_gadget_get_xfersize_ddma(hs_ep);

	अगर (using_dma(hsotg)) अणु
		अचिन्हित पूर्णांक size_करोne;

		/*
		 * Calculate the size of the transfer by checking how much
		 * is left in the endpoपूर्णांक size रेजिस्टर and then working it
		 * out from the amount we loaded क्रम the transfer.
		 *
		 * We need to करो this as DMA poपूर्णांकers are always 32bit aligned
		 * so may overshoot/undershoot the transfer.
		 */

		size_करोne = hs_ep->size_loaded - size_left;
		size_करोne += hs_ep->last_load;

		req->actual = size_करोne;
	पूर्ण

	/* अगर there is more request to करो, schedule new transfer */
	अगर (req->actual < req->length && size_left == 0) अणु
		dwc2_hsotg_start_req(hsotg, hs_ep, hs_req, true);
		वापस;
	पूर्ण

	अगर (req->actual < req->length && req->लघु_not_ok) अणु
		dev_dbg(hsotg->dev, "%s: got %d/%d (short not ok) => error\n",
			__func__, req->actual, req->length);

		/*
		 * toकरो - what should we वापस here? there's no one अन्यथा
		 * even bothering to check the status.
		 */
	पूर्ण

	/* DDMA IN status phase will start from StsPhseRcvd पूर्णांकerrupt */
	अगर (!using_desc_dma(hsotg) && epnum == 0 &&
	    hsotg->ep0_state == DWC2_EP0_DATA_OUT) अणु
		/* Move to STATUS IN */
		अगर (!hsotg->delayed_status)
			dwc2_hsotg_ep0_zlp(hsotg, true);
	पूर्ण

	/*
	 * Slave mode OUT transfers करो not go through XferComplete so
	 * adjust the ISOC parity here.
	 */
	अगर (!using_dma(hsotg)) अणु
		अगर (hs_ep->isochronous && hs_ep->पूर्णांकerval == 1)
			dwc2_hsotg_change_ep_iso_parity(hsotg, DOEPCTL(epnum));
		अन्यथा अगर (hs_ep->isochronous && hs_ep->पूर्णांकerval > 1)
			dwc2_gadget_incr_frame_num(hs_ep);
	पूर्ण

	/* Set actual frame number क्रम completed transfers */
	अगर (!using_desc_dma(hsotg) && hs_ep->isochronous)
		req->frame_number = hsotg->frame_number;

	dwc2_hsotg_complete_request(hsotg, hs_ep, hs_req, result);
पूर्ण

/**
 * dwc2_hsotg_handle_rx - RX FIFO has data
 * @hsotg: The device instance
 *
 * The IRQ handler has detected that the RX FIFO has some data in it
 * that requires processing, so find out what is in there and करो the
 * appropriate पढ़ो.
 *
 * The RXFIFO is a true FIFO, the packets coming out are still in packet
 * chunks, so अगर you have x packets received on an endpoपूर्णांक you'll get x
 * FIFO events delivered, each with a packet's worth of data in it.
 *
 * When using DMA, we should not be processing events from the RXFIFO
 * as the actual data should be sent to the memory directly and we turn
 * on the completion पूर्णांकerrupts to get notअगरications of transfer completion.
 */
अटल व्योम dwc2_hsotg_handle_rx(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 grxstsr = dwc2_पढ़ोl(hsotg, GRXSTSP);
	u32 epnum, status, size;

	WARN_ON(using_dma(hsotg));

	epnum = grxstsr & GRXSTS_EPNUM_MASK;
	status = grxstsr & GRXSTS_PKTSTS_MASK;

	size = grxstsr & GRXSTS_BYTECNT_MASK;
	size >>= GRXSTS_BYTECNT_SHIFT;

	dev_dbg(hsotg->dev, "%s: GRXSTSP=0x%08x (%d@%d)\n",
		__func__, grxstsr, size, epnum);

	चयन ((status & GRXSTS_PKTSTS_MASK) >> GRXSTS_PKTSTS_SHIFT) अणु
	हाल GRXSTS_PKTSTS_GLOBALOUTNAK:
		dev_dbg(hsotg->dev, "GLOBALOUTNAK\n");
		अवरोध;

	हाल GRXSTS_PKTSTS_OUTDONE:
		dev_dbg(hsotg->dev, "OutDone (Frame=0x%08x)\n",
			dwc2_hsotg_पढ़ो_frameno(hsotg));

		अगर (!using_dma(hsotg))
			dwc2_hsotg_handle_outकरोne(hsotg, epnum);
		अवरोध;

	हाल GRXSTS_PKTSTS_SETUPDONE:
		dev_dbg(hsotg->dev,
			"SetupDone (Frame=0x%08x, DOPEPCTL=0x%08x)\n",
			dwc2_hsotg_पढ़ो_frameno(hsotg),
			dwc2_पढ़ोl(hsotg, DOEPCTL(0)));
		/*
		 * Call dwc2_hsotg_handle_outकरोne here अगर it was not called from
		 * GRXSTS_PKTSTS_OUTDONE. That is, अगर the core didn't
		 * generate GRXSTS_PKTSTS_OUTDONE क्रम setup packet.
		 */
		अगर (hsotg->ep0_state == DWC2_EP0_SETUP)
			dwc2_hsotg_handle_outकरोne(hsotg, epnum);
		अवरोध;

	हाल GRXSTS_PKTSTS_OUTRX:
		dwc2_hsotg_rx_data(hsotg, epnum, size);
		अवरोध;

	हाल GRXSTS_PKTSTS_SETUPRX:
		dev_dbg(hsotg->dev,
			"SetupRX (Frame=0x%08x, DOPEPCTL=0x%08x)\n",
			dwc2_hsotg_पढ़ो_frameno(hsotg),
			dwc2_पढ़ोl(hsotg, DOEPCTL(0)));

		WARN_ON(hsotg->ep0_state != DWC2_EP0_SETUP);

		dwc2_hsotg_rx_data(hsotg, epnum, size);
		अवरोध;

	शेष:
		dev_warn(hsotg->dev, "%s: unknown status %08x\n",
			 __func__, grxstsr);

		dwc2_hsotg_dump(hsotg);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * dwc2_hsotg_ep0_mps - turn max packet size पूर्णांकo रेजिस्टर setting
 * @mps: The maximum packet size in bytes.
 */
अटल u32 dwc2_hsotg_ep0_mps(अचिन्हित पूर्णांक mps)
अणु
	चयन (mps) अणु
	हाल 64:
		वापस D0EPCTL_MPS_64;
	हाल 32:
		वापस D0EPCTL_MPS_32;
	हाल 16:
		वापस D0EPCTL_MPS_16;
	हाल 8:
		वापस D0EPCTL_MPS_8;
	पूर्ण

	/* bad max packet size, warn and वापस invalid result */
	WARN_ON(1);
	वापस (u32)-1;
पूर्ण

/**
 * dwc2_hsotg_set_ep_maxpacket - set endpoपूर्णांक's max-packet field
 * @hsotg: The driver state.
 * @ep: The index number of the endpoपूर्णांक
 * @mps: The maximum packet size in bytes
 * @mc: The multicount value
 * @dir_in: True अगर direction is in.
 *
 * Configure the maximum packet size क्रम the given endpoपूर्णांक, updating
 * the hardware control रेजिस्टरs to reflect this.
 */
अटल व्योम dwc2_hsotg_set_ep_maxpacket(काष्ठा dwc2_hsotg *hsotg,
					अचिन्हित पूर्णांक ep, अचिन्हित पूर्णांक mps,
					अचिन्हित पूर्णांक mc, अचिन्हित पूर्णांक dir_in)
अणु
	काष्ठा dwc2_hsotg_ep *hs_ep;
	u32 reg;

	hs_ep = index_to_ep(hsotg, ep, dir_in);
	अगर (!hs_ep)
		वापस;

	अगर (ep == 0) अणु
		u32 mps_bytes = mps;

		/* EP0 is a special हाल */
		mps = dwc2_hsotg_ep0_mps(mps_bytes);
		अगर (mps > 3)
			जाओ bad_mps;
		hs_ep->ep.maxpacket = mps_bytes;
		hs_ep->mc = 1;
	पूर्ण अन्यथा अणु
		अगर (mps > 1024)
			जाओ bad_mps;
		hs_ep->mc = mc;
		अगर (mc > 3)
			जाओ bad_mps;
		hs_ep->ep.maxpacket = mps;
	पूर्ण

	अगर (dir_in) अणु
		reg = dwc2_पढ़ोl(hsotg, DIEPCTL(ep));
		reg &= ~DXEPCTL_MPS_MASK;
		reg |= mps;
		dwc2_ग_लिखोl(hsotg, reg, DIEPCTL(ep));
	पूर्ण अन्यथा अणु
		reg = dwc2_पढ़ोl(hsotg, DOEPCTL(ep));
		reg &= ~DXEPCTL_MPS_MASK;
		reg |= mps;
		dwc2_ग_लिखोl(hsotg, reg, DOEPCTL(ep));
	पूर्ण

	वापस;

bad_mps:
	dev_err(hsotg->dev, "ep%d: bad mps of %d\n", ep, mps);
पूर्ण

/**
 * dwc2_hsotg_txfअगरo_flush - flush Tx FIFO
 * @hsotg: The driver state
 * @idx: The index क्रम the endpoपूर्णांक (0..15)
 */
अटल व्योम dwc2_hsotg_txfअगरo_flush(काष्ठा dwc2_hsotg *hsotg, अचिन्हित पूर्णांक idx)
अणु
	dwc2_ग_लिखोl(hsotg, GRSTCTL_TXFNUM(idx) | GRSTCTL_TXFFLSH,
		    GRSTCTL);

	/* रुको until the fअगरo is flushed */
	अगर (dwc2_hsotg_रुको_bit_clear(hsotg, GRSTCTL, GRSTCTL_TXFFLSH, 100))
		dev_warn(hsotg->dev, "%s: timeout flushing fifo GRSTCTL_TXFFLSH\n",
			 __func__);
पूर्ण

/**
 * dwc2_hsotg_trytx - check to see अगर anything needs transmitting
 * @hsotg: The driver state
 * @hs_ep: The driver endpoपूर्णांक to check.
 *
 * Check to see अगर there is a request that has data to send, and अगर so
 * make an attempt to ग_लिखो data पूर्णांकo the FIFO.
 */
अटल पूर्णांक dwc2_hsotg_trytx(काष्ठा dwc2_hsotg *hsotg,
			    काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	काष्ठा dwc2_hsotg_req *hs_req = hs_ep->req;

	अगर (!hs_ep->dir_in || !hs_req) अणु
		/**
		 * अगर request is not enqueued, we disable पूर्णांकerrupts
		 * क्रम endpoपूर्णांकs, excepting ep0
		 */
		अगर (hs_ep->index != 0)
			dwc2_hsotg_ctrl_epपूर्णांक(hsotg, hs_ep->index,
					      hs_ep->dir_in, 0);
		वापस 0;
	पूर्ण

	अगर (hs_req->req.actual < hs_req->req.length) अणु
		dev_dbg(hsotg->dev, "trying to write more for ep%d\n",
			hs_ep->index);
		वापस dwc2_hsotg_ग_लिखो_fअगरo(hsotg, hs_ep, hs_req);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dwc2_hsotg_complete_in - complete IN transfer
 * @hsotg: The device state.
 * @hs_ep: The endpoपूर्णांक that has just completed.
 *
 * An IN transfer has been completed, update the transfer's state and then
 * call the relevant completion routines.
 */
अटल व्योम dwc2_hsotg_complete_in(काष्ठा dwc2_hsotg *hsotg,
				   काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	काष्ठा dwc2_hsotg_req *hs_req = hs_ep->req;
	u32 epsize = dwc2_पढ़ोl(hsotg, DIEPTSIZ(hs_ep->index));
	पूर्णांक size_left, size_करोne;

	अगर (!hs_req) अणु
		dev_dbg(hsotg->dev, "XferCompl but no req\n");
		वापस;
	पूर्ण

	/* Finish ZLP handling क्रम IN EP0 transactions */
	अगर (hs_ep->index == 0 && hsotg->ep0_state == DWC2_EP0_STATUS_IN) अणु
		dev_dbg(hsotg->dev, "zlp packet sent\n");

		/*
		 * While send zlp क्रम DWC2_EP0_STATUS_IN EP direction was
		 * changed to IN. Change back to complete OUT transfer request
		 */
		hs_ep->dir_in = 0;

		dwc2_hsotg_complete_request(hsotg, hs_ep, hs_req, 0);
		अगर (hsotg->test_mode) अणु
			पूर्णांक ret;

			ret = dwc2_hsotg_set_test_mode(hsotg, hsotg->test_mode);
			अगर (ret < 0) अणु
				dev_dbg(hsotg->dev, "Invalid Test #%d\n",
					hsotg->test_mode);
				dwc2_hsotg_stall_ep0(hsotg);
				वापस;
			पूर्ण
		पूर्ण
		dwc2_hsotg_enqueue_setup(hsotg);
		वापस;
	पूर्ण

	/*
	 * Calculate the size of the transfer by checking how much is left
	 * in the endpoपूर्णांक size रेजिस्टर and then working it out from
	 * the amount we loaded क्रम the transfer.
	 *
	 * We करो this even क्रम DMA, as the transfer may have incremented
	 * past the end of the buffer (DMA transfers are always 32bit
	 * aligned).
	 */
	अगर (using_desc_dma(hsotg)) अणु
		size_left = dwc2_gadget_get_xfersize_ddma(hs_ep);
		अगर (size_left < 0)
			dev_err(hsotg->dev, "error parsing DDMA results %d\n",
				size_left);
	पूर्ण अन्यथा अणु
		size_left = DXEPTSIZ_XFERSIZE_GET(epsize);
	पूर्ण

	size_करोne = hs_ep->size_loaded - size_left;
	size_करोne += hs_ep->last_load;

	अगर (hs_req->req.actual != size_करोne)
		dev_dbg(hsotg->dev, "%s: adjusting size done %d => %d\n",
			__func__, hs_req->req.actual, size_करोne);

	hs_req->req.actual = size_करोne;
	dev_dbg(hsotg->dev, "req->length:%d req->actual:%d req->zero:%d\n",
		hs_req->req.length, hs_req->req.actual, hs_req->req.zero);

	अगर (!size_left && hs_req->req.actual < hs_req->req.length) अणु
		dev_dbg(hsotg->dev, "%s trying more for req...\n", __func__);
		dwc2_hsotg_start_req(hsotg, hs_ep, hs_req, true);
		वापस;
	पूर्ण

	/* Zlp क्रम all endpoपूर्णांकs, क्रम ep0 only in DATA IN stage */
	अगर (hs_ep->send_zlp) अणु
		dwc2_hsotg_program_zlp(hsotg, hs_ep);
		hs_ep->send_zlp = 0;
		/* transfer will be completed on next complete पूर्णांकerrupt */
		वापस;
	पूर्ण

	अगर (hs_ep->index == 0 && hsotg->ep0_state == DWC2_EP0_DATA_IN) अणु
		/* Move to STATUS OUT */
		dwc2_hsotg_ep0_zlp(hsotg, false);
		वापस;
	पूर्ण

	dwc2_hsotg_complete_request(hsotg, hs_ep, hs_req, 0);
पूर्ण

/**
 * dwc2_gadget_पढ़ो_ep_पूर्णांकerrupts - पढ़ोs पूर्णांकerrupts क्रम given ep
 * @hsotg: The device state.
 * @idx: Index of ep.
 * @dir_in: Endpoपूर्णांक direction 1-in 0-out.
 *
 * Reads क्रम endpoपूर्णांक with given index and direction, by masking
 * epपूर्णांक_reg with coresponding mask.
 */
अटल u32 dwc2_gadget_पढ़ो_ep_पूर्णांकerrupts(काष्ठा dwc2_hsotg *hsotg,
					  अचिन्हित पूर्णांक idx, पूर्णांक dir_in)
अणु
	u32 epmsk_reg = dir_in ? DIEPMSK : DOEPMSK;
	u32 epपूर्णांक_reg = dir_in ? DIEPINT(idx) : DOEPINT(idx);
	u32 पूर्णांकs;
	u32 mask;
	u32 diepempmsk;

	mask = dwc2_पढ़ोl(hsotg, epmsk_reg);
	diepempmsk = dwc2_पढ़ोl(hsotg, DIEPEMPMSK);
	mask |= ((diepempmsk >> idx) & 0x1) ? DIEPMSK_TXFIFOEMPTY : 0;
	mask |= DXEPINT_SETUP_RCVD;

	पूर्णांकs = dwc2_पढ़ोl(hsotg, epपूर्णांक_reg);
	पूर्णांकs &= mask;
	वापस पूर्णांकs;
पूर्ण

/**
 * dwc2_gadget_handle_ep_disabled - handle DXEPINT_EPDISBLD
 * @hs_ep: The endpoपूर्णांक on which पूर्णांकerrupt is निश्चितed.
 *
 * This पूर्णांकerrupt indicates that the endpoपूर्णांक has been disabled per the
 * application's request.
 *
 * For IN endpoपूर्णांकs flushes txfअगरo, in हाल of BULK clears DCTL_CGNPINNAK,
 * in हाल of ISOC completes current request.
 *
 * For ISOC-OUT endpoपूर्णांकs completes expired requests. If there is reमुख्यing
 * request starts it.
 */
अटल व्योम dwc2_gadget_handle_ep_disabled(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;
	काष्ठा dwc2_hsotg_req *hs_req;
	अचिन्हित अक्षर idx = hs_ep->index;
	पूर्णांक dir_in = hs_ep->dir_in;
	u32 epctl_reg = dir_in ? DIEPCTL(idx) : DOEPCTL(idx);
	पूर्णांक dctl = dwc2_पढ़ोl(hsotg, DCTL);

	dev_dbg(hsotg->dev, "%s: EPDisbld\n", __func__);

	अगर (dir_in) अणु
		पूर्णांक epctl = dwc2_पढ़ोl(hsotg, epctl_reg);

		dwc2_hsotg_txfअगरo_flush(hsotg, hs_ep->fअगरo_index);

		अगर (hs_ep->isochronous) अणु
			dwc2_hsotg_complete_in(hsotg, hs_ep);
			वापस;
		पूर्ण

		अगर ((epctl & DXEPCTL_STALL) && (epctl & DXEPCTL_EPTYPE_BULK)) अणु
			पूर्णांक dctl = dwc2_पढ़ोl(hsotg, DCTL);

			dctl |= DCTL_CGNPINNAK;
			dwc2_ग_लिखोl(hsotg, dctl, DCTL);
		पूर्ण
		वापस;
	पूर्ण

	अगर (dctl & DCTL_GOUTNAKSTS) अणु
		dctl |= DCTL_CGOUTNAK;
		dwc2_ग_लिखोl(hsotg, dctl, DCTL);
	पूर्ण

	अगर (!hs_ep->isochronous)
		वापस;

	अगर (list_empty(&hs_ep->queue)) अणु
		dev_dbg(hsotg->dev, "%s: complete_ep 0x%p, ep->queue empty!\n",
			__func__, hs_ep);
		वापस;
	पूर्ण

	करो अणु
		hs_req = get_ep_head(hs_ep);
		अगर (hs_req)
			dwc2_hsotg_complete_request(hsotg, hs_ep, hs_req,
						    -ENODATA);
		dwc2_gadget_incr_frame_num(hs_ep);
		/* Update current frame number value. */
		hsotg->frame_number = dwc2_hsotg_पढ़ो_frameno(hsotg);
	पूर्ण जबतक (dwc2_gadget_target_frame_elapsed(hs_ep));

	dwc2_gadget_start_next_request(hs_ep);
पूर्ण

/**
 * dwc2_gadget_handle_out_token_ep_disabled - handle DXEPINT_OUTTKNEPDIS
 * @ep: The endpoपूर्णांक on which पूर्णांकerrupt is निश्चितed.
 *
 * This is starting poपूर्णांक क्रम ISOC-OUT transfer, synchronization करोne with
 * first out token received from host जबतक corresponding EP is disabled.
 *
 * Device करोes not know initial frame in which out token will come. For this
 * HW generates OUTTKNEPDIS - out token is received जबतक EP is disabled. Upon
 * getting this पूर्णांकerrupt SW starts calculation क्रम next transfer frame.
 */
अटल व्योम dwc2_gadget_handle_out_token_ep_disabled(काष्ठा dwc2_hsotg_ep *ep)
अणु
	काष्ठा dwc2_hsotg *hsotg = ep->parent;
	पूर्णांक dir_in = ep->dir_in;
	u32 करोepmsk;

	अगर (dir_in || !ep->isochronous)
		वापस;

	अगर (using_desc_dma(hsotg)) अणु
		अगर (ep->target_frame == TARGET_FRAME_INITIAL) अणु
			/* Start first ISO Out */
			ep->target_frame = hsotg->frame_number;
			dwc2_gadget_start_isoc_ddma(ep);
		पूर्ण
		वापस;
	पूर्ण

	अगर (ep->पूर्णांकerval > 1 &&
	    ep->target_frame == TARGET_FRAME_INITIAL) अणु
		u32 ctrl;

		ep->target_frame = hsotg->frame_number;
		dwc2_gadget_incr_frame_num(ep);

		ctrl = dwc2_पढ़ोl(hsotg, DOEPCTL(ep->index));
		अगर (ep->target_frame & 0x1)
			ctrl |= DXEPCTL_SETODDFR;
		अन्यथा
			ctrl |= DXEPCTL_SETEVENFR;

		dwc2_ग_लिखोl(hsotg, ctrl, DOEPCTL(ep->index));
	पूर्ण

	dwc2_gadget_start_next_request(ep);
	करोepmsk = dwc2_पढ़ोl(hsotg, DOEPMSK);
	करोepmsk &= ~DOEPMSK_OUTTKNEPDISMSK;
	dwc2_ग_लिखोl(hsotg, करोepmsk, DOEPMSK);
पूर्ण

/**
 * dwc2_gadget_handle_nak - handle NAK पूर्णांकerrupt
 * @hs_ep: The endpoपूर्णांक on which पूर्णांकerrupt is निश्चितed.
 *
 * This is starting poपूर्णांक क्रम ISOC-IN transfer, synchronization करोne with
 * first IN token received from host जबतक corresponding EP is disabled.
 *
 * Device करोes not know when first one token will arrive from host. On first
 * token arrival HW generates 2 पूर्णांकerrupts: 'in token received while FIFO empty'
 * and 'NAK'. NAK पूर्णांकerrupt क्रम ISOC-IN means that token has arrived and ZLP was
 * sent in response to that as there was no data in FIFO. SW is basing on this
 * पूर्णांकerrupt to obtain frame in which token has come and then based on the
 * पूर्णांकerval calculates next frame क्रम transfer.
 */
अटल व्योम dwc2_gadget_handle_nak(काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;
	पूर्णांक dir_in = hs_ep->dir_in;

	अगर (!dir_in || !hs_ep->isochronous)
		वापस;

	अगर (hs_ep->target_frame == TARGET_FRAME_INITIAL) अणु

		अगर (using_desc_dma(hsotg)) अणु
			hs_ep->target_frame = hsotg->frame_number;
			dwc2_gadget_incr_frame_num(hs_ep);

			/* In service पूर्णांकerval mode target_frame must
			 * be set to last (u)frame of the service पूर्णांकerval.
			 */
			अगर (hsotg->params.service_पूर्णांकerval) अणु
				/* Set target_frame to the first (u)frame of
				 * the service पूर्णांकerval
				 */
				hs_ep->target_frame &= ~hs_ep->पूर्णांकerval + 1;

				/* Set target_frame to the last (u)frame of
				 * the service पूर्णांकerval
				 */
				dwc2_gadget_incr_frame_num(hs_ep);
				dwc2_gadget_dec_frame_num_by_one(hs_ep);
			पूर्ण

			dwc2_gadget_start_isoc_ddma(hs_ep);
			वापस;
		पूर्ण

		hs_ep->target_frame = hsotg->frame_number;
		अगर (hs_ep->पूर्णांकerval > 1) अणु
			u32 ctrl = dwc2_पढ़ोl(hsotg,
					      DIEPCTL(hs_ep->index));
			अगर (hs_ep->target_frame & 0x1)
				ctrl |= DXEPCTL_SETODDFR;
			अन्यथा
				ctrl |= DXEPCTL_SETEVENFR;

			dwc2_ग_लिखोl(hsotg, ctrl, DIEPCTL(hs_ep->index));
		पूर्ण

		dwc2_hsotg_complete_request(hsotg, hs_ep,
					    get_ep_head(hs_ep), 0);
	पूर्ण

	अगर (!using_desc_dma(hsotg))
		dwc2_gadget_incr_frame_num(hs_ep);
पूर्ण

/**
 * dwc2_hsotg_epपूर्णांक - handle an in/out endpoपूर्णांक पूर्णांकerrupt
 * @hsotg: The driver state
 * @idx: The index क्रम the endpoपूर्णांक (0..15)
 * @dir_in: Set अगर this is an IN endpoपूर्णांक
 *
 * Process and clear any पूर्णांकerrupt pending क्रम an inभागidual endpoपूर्णांक
 */
अटल व्योम dwc2_hsotg_epपूर्णांक(काष्ठा dwc2_hsotg *hsotg, अचिन्हित पूर्णांक idx,
			     पूर्णांक dir_in)
अणु
	काष्ठा dwc2_hsotg_ep *hs_ep = index_to_ep(hsotg, idx, dir_in);
	u32 epपूर्णांक_reg = dir_in ? DIEPINT(idx) : DOEPINT(idx);
	u32 epctl_reg = dir_in ? DIEPCTL(idx) : DOEPCTL(idx);
	u32 epsiz_reg = dir_in ? DIEPTSIZ(idx) : DOEPTSIZ(idx);
	u32 पूर्णांकs;

	पूर्णांकs = dwc2_gadget_पढ़ो_ep_पूर्णांकerrupts(hsotg, idx, dir_in);

	/* Clear endpoपूर्णांक पूर्णांकerrupts */
	dwc2_ग_लिखोl(hsotg, पूर्णांकs, epपूर्णांक_reg);

	अगर (!hs_ep) अणु
		dev_err(hsotg->dev, "%s:Interrupt for unconfigured ep%d(%s)\n",
			__func__, idx, dir_in ? "in" : "out");
		वापस;
	पूर्ण

	dev_dbg(hsotg->dev, "%s: ep%d(%s) DxEPINT=0x%08x\n",
		__func__, idx, dir_in ? "in" : "out", पूर्णांकs);

	/* Don't process XferCompl पूर्णांकerrupt अगर it is a setup packet */
	अगर (idx == 0 && (पूर्णांकs & (DXEPINT_SETUP | DXEPINT_SETUP_RCVD)))
		पूर्णांकs &= ~DXEPINT_XFERCOMPL;

	/*
	 * Don't process XferCompl पूर्णांकerrupt in DDMA अगर EP0 is still in SETUP
	 * stage and xfercomplete was generated without SETUP phase करोne
	 * पूर्णांकerrupt. SW should parse received setup packet only after host's
	 * निकास from setup phase of control transfer.
	 */
	अगर (using_desc_dma(hsotg) && idx == 0 && !hs_ep->dir_in &&
	    hsotg->ep0_state == DWC2_EP0_SETUP && !(पूर्णांकs & DXEPINT_SETUP))
		पूर्णांकs &= ~DXEPINT_XFERCOMPL;

	अगर (पूर्णांकs & DXEPINT_XFERCOMPL) अणु
		dev_dbg(hsotg->dev,
			"%s: XferCompl: DxEPCTL=0x%08x, DXEPTSIZ=%08x\n",
			__func__, dwc2_पढ़ोl(hsotg, epctl_reg),
			dwc2_पढ़ोl(hsotg, epsiz_reg));

		/* In DDMA handle isochronous requests separately */
		अगर (using_desc_dma(hsotg) && hs_ep->isochronous) अणु
			/* XferCompl set aदीर्घ with BNA */
			अगर (!(पूर्णांकs & DXEPINT_BNAINTR))
				dwc2_gadget_complete_isoc_request_ddma(hs_ep);
		पूर्ण अन्यथा अगर (dir_in) अणु
			/*
			 * We get OutDone from the FIFO, so we only
			 * need to look at completing IN requests here
			 * अगर operating slave mode
			 */
			अगर (hs_ep->isochronous && hs_ep->पूर्णांकerval > 1)
				dwc2_gadget_incr_frame_num(hs_ep);

			dwc2_hsotg_complete_in(hsotg, hs_ep);
			अगर (पूर्णांकs & DXEPINT_NAKINTRPT)
				पूर्णांकs &= ~DXEPINT_NAKINTRPT;

			अगर (idx == 0 && !hs_ep->req)
				dwc2_hsotg_enqueue_setup(hsotg);
		पूर्ण अन्यथा अगर (using_dma(hsotg)) अणु
			/*
			 * We're using DMA, we need to fire an OutDone here
			 * as we ignore the RXFIFO.
			 */
			अगर (hs_ep->isochronous && hs_ep->पूर्णांकerval > 1)
				dwc2_gadget_incr_frame_num(hs_ep);

			dwc2_hsotg_handle_outकरोne(hsotg, idx);
		पूर्ण
	पूर्ण

	अगर (पूर्णांकs & DXEPINT_EPDISBLD)
		dwc2_gadget_handle_ep_disabled(hs_ep);

	अगर (पूर्णांकs & DXEPINT_OUTTKNEPDIS)
		dwc2_gadget_handle_out_token_ep_disabled(hs_ep);

	अगर (पूर्णांकs & DXEPINT_NAKINTRPT)
		dwc2_gadget_handle_nak(hs_ep);

	अगर (पूर्णांकs & DXEPINT_AHBERR)
		dev_dbg(hsotg->dev, "%s: AHBErr\n", __func__);

	अगर (पूर्णांकs & DXEPINT_SETUP) अणु  /* Setup or Timeout */
		dev_dbg(hsotg->dev, "%s: Setup/Timeout\n",  __func__);

		अगर (using_dma(hsotg) && idx == 0) अणु
			/*
			 * this is the notअगरication we've received a
			 * setup packet. In non-DMA mode we'd get this
			 * from the RXFIFO, instead we need to process
			 * the setup here.
			 */

			अगर (dir_in)
				WARN_ON_ONCE(1);
			अन्यथा
				dwc2_hsotg_handle_outकरोne(hsotg, 0);
		पूर्ण
	पूर्ण

	अगर (पूर्णांकs & DXEPINT_STSPHSERCVD) अणु
		dev_dbg(hsotg->dev, "%s: StsPhseRcvd\n", __func__);

		/* Safety check EP0 state when STSPHSERCVD निश्चितed */
		अगर (hsotg->ep0_state == DWC2_EP0_DATA_OUT) अणु
			/* Move to STATUS IN क्रम DDMA */
			अगर (using_desc_dma(hsotg)) अणु
				अगर (!hsotg->delayed_status)
					dwc2_hsotg_ep0_zlp(hsotg, true);
				अन्यथा
				/* In हाल of 3 stage Control Write with delayed
				 * status, when Status IN transfer started
				 * beक्रमe STSPHSERCVD निश्चितed, NAKSTS bit not
				 * cleared by CNAK in dwc2_hsotg_start_req()
				 * function. Clear now NAKSTS to allow complete
				 * transfer.
				 */
					dwc2_set_bit(hsotg, DIEPCTL(0),
						     DXEPCTL_CNAK);
			पूर्ण
		पूर्ण

	पूर्ण

	अगर (पूर्णांकs & DXEPINT_BACK2BACKSETUP)
		dev_dbg(hsotg->dev, "%s: B2BSetup/INEPNakEff\n", __func__);

	अगर (पूर्णांकs & DXEPINT_BNAINTR) अणु
		dev_dbg(hsotg->dev, "%s: BNA interrupt\n", __func__);
		अगर (hs_ep->isochronous)
			dwc2_gadget_handle_isoc_bna(hs_ep);
	पूर्ण

	अगर (dir_in && !hs_ep->isochronous) अणु
		/* not sure अगर this is important, but we'll clear it anyway */
		अगर (पूर्णांकs & DXEPINT_INTKNTXFEMP) अणु
			dev_dbg(hsotg->dev, "%s: ep%d: INTknTXFEmpMsk\n",
				__func__, idx);
		पूर्ण

		/* this probably means something bad is happening */
		अगर (पूर्णांकs & DXEPINT_INTKNEPMIS) अणु
			dev_warn(hsotg->dev, "%s: ep%d: INTknEP\n",
				 __func__, idx);
		पूर्ण

		/* FIFO has space or is empty (see GAHBCFG) */
		अगर (hsotg->dedicated_fअगरos &&
		    पूर्णांकs & DXEPINT_TXFEMP) अणु
			dev_dbg(hsotg->dev, "%s: ep%d: TxFIFOEmpty\n",
				__func__, idx);
			अगर (!using_dma(hsotg))
				dwc2_hsotg_trytx(hsotg, hs_ep);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * dwc2_hsotg_irq_क्रमागतकरोne - Handle EnumDone पूर्णांकerrupt (क्रमागतeration करोne)
 * @hsotg: The device state.
 *
 * Handle updating the device settings after the क्रमागतeration phase has
 * been completed.
 */
अटल व्योम dwc2_hsotg_irq_क्रमागतकरोne(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 dsts = dwc2_पढ़ोl(hsotg, DSTS);
	पूर्णांक ep0_mps = 0, ep_mps = 8;

	/*
	 * This should संकेत the finish of the क्रमागतeration phase
	 * of the USB handshaking, so we should now know what rate
	 * we connected at.
	 */

	dev_dbg(hsotg->dev, "EnumDone (DSTS=0x%08x)\n", dsts);

	/*
	 * note, since we're limited by the size of transfer on EP0, and
	 * it seems IN transfers must be a even number of packets we करो
	 * not advertise a 64byte MPS on EP0.
	 */

	/* catch both EnumSpd_FS and EnumSpd_FS48 */
	चयन ((dsts & DSTS_ENUMSPD_MASK) >> DSTS_ENUMSPD_SHIFT) अणु
	हाल DSTS_ENUMSPD_FS:
	हाल DSTS_ENUMSPD_FS48:
		hsotg->gadget.speed = USB_SPEED_FULL;
		ep0_mps = EP0_MPS_LIMIT;
		ep_mps = 1023;
		अवरोध;

	हाल DSTS_ENUMSPD_HS:
		hsotg->gadget.speed = USB_SPEED_HIGH;
		ep0_mps = EP0_MPS_LIMIT;
		ep_mps = 1024;
		अवरोध;

	हाल DSTS_ENUMSPD_LS:
		hsotg->gadget.speed = USB_SPEED_LOW;
		ep0_mps = 8;
		ep_mps = 8;
		/*
		 * note, we करोn't actually support LS in this driver at the
		 * moment, and the करोcumentation seems to imply that it isn't
		 * supported by the PHYs on some of the devices.
		 */
		अवरोध;
	पूर्ण
	dev_info(hsotg->dev, "new device is %s\n",
		 usb_speed_string(hsotg->gadget.speed));

	/*
	 * we should now know the maximum packet size क्रम an
	 * endpoपूर्णांक, so set the endpoपूर्णांकs to a शेष value.
	 */

	अगर (ep0_mps) अणु
		पूर्णांक i;
		/* Initialize ep0 क्रम both in and out directions */
		dwc2_hsotg_set_ep_maxpacket(hsotg, 0, ep0_mps, 0, 1);
		dwc2_hsotg_set_ep_maxpacket(hsotg, 0, ep0_mps, 0, 0);
		क्रम (i = 1; i < hsotg->num_of_eps; i++) अणु
			अगर (hsotg->eps_in[i])
				dwc2_hsotg_set_ep_maxpacket(hsotg, i, ep_mps,
							    0, 1);
			अगर (hsotg->eps_out[i])
				dwc2_hsotg_set_ep_maxpacket(hsotg, i, ep_mps,
							    0, 0);
		पूर्ण
	पूर्ण

	/* ensure after क्रमागतeration our EP0 is active */

	dwc2_hsotg_enqueue_setup(hsotg);

	dev_dbg(hsotg->dev, "EP0: DIEPCTL0=0x%08x, DOEPCTL0=0x%08x\n",
		dwc2_पढ़ोl(hsotg, DIEPCTL0),
		dwc2_पढ़ोl(hsotg, DOEPCTL0));
पूर्ण

/**
 * समाप्त_all_requests - हटाओ all requests from the endpoपूर्णांक's queue
 * @hsotg: The device state.
 * @ep: The endpoपूर्णांक the requests may be on.
 * @result: The result code to use.
 *
 * Go through the requests on the given endpoपूर्णांक and mark them
 * completed with the given result code.
 */
अटल व्योम समाप्त_all_requests(काष्ठा dwc2_hsotg *hsotg,
			      काष्ठा dwc2_hsotg_ep *ep,
			      पूर्णांक result)
अणु
	अचिन्हित पूर्णांक size;

	ep->req = शून्य;

	जबतक (!list_empty(&ep->queue)) अणु
		काष्ठा dwc2_hsotg_req *req = get_ep_head(ep);

		dwc2_hsotg_complete_request(hsotg, ep, req, result);
	पूर्ण

	अगर (!hsotg->dedicated_fअगरos)
		वापस;
	size = (dwc2_पढ़ोl(hsotg, DTXFSTS(ep->fअगरo_index)) & 0xffff) * 4;
	अगर (size < ep->fअगरo_size)
		dwc2_hsotg_txfअगरo_flush(hsotg, ep->fअगरo_index);
पूर्ण

/**
 * dwc2_hsotg_disconnect - disconnect service
 * @hsotg: The device state.
 *
 * The device has been disconnected. Remove all current
 * transactions and संकेत the gadget driver that this
 * has happened.
 */
व्योम dwc2_hsotg_disconnect(काष्ठा dwc2_hsotg *hsotg)
अणु
	अचिन्हित पूर्णांक ep;

	अगर (!hsotg->connected)
		वापस;

	hsotg->connected = 0;
	hsotg->test_mode = 0;

	/* all endpoपूर्णांकs should be shutकरोwn */
	क्रम (ep = 0; ep < hsotg->num_of_eps; ep++) अणु
		अगर (hsotg->eps_in[ep])
			समाप्त_all_requests(hsotg, hsotg->eps_in[ep],
					  -ESHUTDOWN);
		अगर (hsotg->eps_out[ep])
			समाप्त_all_requests(hsotg, hsotg->eps_out[ep],
					  -ESHUTDOWN);
	पूर्ण

	call_gadget(hsotg, disconnect);
	hsotg->lx_state = DWC2_L3;

	usb_gadget_set_state(&hsotg->gadget, USB_STATE_NOTATTACHED);
पूर्ण

/**
 * dwc2_hsotg_irq_fअगरoempty - TX FIFO empty पूर्णांकerrupt handler
 * @hsotg: The device state:
 * @periodic: True अगर this is a periodic FIFO पूर्णांकerrupt
 */
अटल व्योम dwc2_hsotg_irq_fअगरoempty(काष्ठा dwc2_hsotg *hsotg, bool periodic)
अणु
	काष्ठा dwc2_hsotg_ep *ep;
	पूर्णांक epno, ret;

	/* look through क्रम any more data to transmit */
	क्रम (epno = 0; epno < hsotg->num_of_eps; epno++) अणु
		ep = index_to_ep(hsotg, epno, 1);

		अगर (!ep)
			जारी;

		अगर (!ep->dir_in)
			जारी;

		अगर ((periodic && !ep->periodic) ||
		    (!periodic && ep->periodic))
			जारी;

		ret = dwc2_hsotg_trytx(hsotg, ep);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
पूर्ण

/* IRQ flags which will trigger a retry around the IRQ loop */
#घोषणा IRQ_RETRY_MASK (GINTSTS_NPTXFEMP | \
			GINTSTS_PTXFEMP |  \
			GINTSTS_RXFLVL)

अटल पूर्णांक dwc2_hsotg_ep_disable(काष्ठा usb_ep *ep);
/**
 * dwc2_hsotg_core_init - issue softreset to the core
 * @hsotg: The device state
 * @is_usb_reset: Usb resetting flag
 *
 * Issue a soft reset to the core, and aरुको the core finishing it.
 */
व्योम dwc2_hsotg_core_init_disconnected(काष्ठा dwc2_hsotg *hsotg,
				       bool is_usb_reset)
अणु
	u32 पूर्णांकmsk;
	u32 val;
	u32 usbcfg;
	u32 dcfg = 0;
	पूर्णांक ep;

	/* Kill any ep0 requests as controller will be reinitialized */
	समाप्त_all_requests(hsotg, hsotg->eps_out[0], -ECONNRESET);

	अगर (!is_usb_reset) अणु
		अगर (dwc2_core_reset(hsotg, true))
			वापस;
	पूर्ण अन्यथा अणु
		/* all endpoपूर्णांकs should be shutकरोwn */
		क्रम (ep = 1; ep < hsotg->num_of_eps; ep++) अणु
			अगर (hsotg->eps_in[ep])
				dwc2_hsotg_ep_disable(&hsotg->eps_in[ep]->ep);
			अगर (hsotg->eps_out[ep])
				dwc2_hsotg_ep_disable(&hsotg->eps_out[ep]->ep);
		पूर्ण
	पूर्ण

	/*
	 * we must now enable ep0 पढ़ोy क्रम host detection and then
	 * set configuration.
	 */

	/* keep other bits untouched (so e.g. क्रमced modes are not lost) */
	usbcfg = dwc2_पढ़ोl(hsotg, GUSBCFG);
	usbcfg &= ~GUSBCFG_TOUTCAL_MASK;
	usbcfg |= GUSBCFG_TOUTCAL(7);

	/* हटाओ the HNP/SRP and set the PHY */
	usbcfg &= ~(GUSBCFG_SRPCAP | GUSBCFG_HNPCAP);
        dwc2_ग_लिखोl(hsotg, usbcfg, GUSBCFG);

	dwc2_phy_init(hsotg, true);

	dwc2_hsotg_init_fअगरo(hsotg);

	अगर (!is_usb_reset)
		dwc2_set_bit(hsotg, DCTL, DCTL_SFTDISCON);

	dcfg |= DCFG_EPMISCNT(1);

	चयन (hsotg->params.speed) अणु
	हाल DWC2_SPEED_PARAM_LOW:
		dcfg |= DCFG_DEVSPD_LS;
		अवरोध;
	हाल DWC2_SPEED_PARAM_FULL:
		अगर (hsotg->params.phy_type == DWC2_PHY_TYPE_PARAM_FS)
			dcfg |= DCFG_DEVSPD_FS48;
		अन्यथा
			dcfg |= DCFG_DEVSPD_FS;
		अवरोध;
	शेष:
		dcfg |= DCFG_DEVSPD_HS;
	पूर्ण

	अगर (hsotg->params.ipg_isoc_en)
		dcfg |= DCFG_IPG_ISOC_SUPPORDED;

	dwc2_ग_लिखोl(hsotg, dcfg,  DCFG);

	/* Clear any pending OTG पूर्णांकerrupts */
	dwc2_ग_लिखोl(hsotg, 0xffffffff, GOTGINT);

	/* Clear any pending पूर्णांकerrupts */
	dwc2_ग_लिखोl(hsotg, 0xffffffff, GINTSTS);
	पूर्णांकmsk = GINTSTS_ERLYSUSP | GINTSTS_SESSREQINT |
		GINTSTS_GOUTNAKEFF | GINTSTS_GINNAKEFF |
		GINTSTS_USBRST | GINTSTS_RESETDET |
		GINTSTS_ENUMDONE | GINTSTS_OTGINT |
		GINTSTS_USBSUSP | GINTSTS_WKUPINT |
		GINTSTS_LPMTRANRCVD;

	अगर (!using_desc_dma(hsotg))
		पूर्णांकmsk |= GINTSTS_INCOMPL_SOIN | GINTSTS_INCOMPL_SOOUT;

	अगर (!hsotg->params.बाह्यal_id_pin_ctl)
		पूर्णांकmsk |= GINTSTS_CONIDSTSCHNG;

	dwc2_ग_लिखोl(hsotg, पूर्णांकmsk, GINTMSK);

	अगर (using_dma(hsotg)) अणु
		dwc2_ग_लिखोl(hsotg, GAHBCFG_GLBL_INTR_EN | GAHBCFG_DMA_EN |
			    hsotg->params.ahbcfg,
			    GAHBCFG);

		/* Set DDMA mode support in the core अगर needed */
		अगर (using_desc_dma(hsotg))
			dwc2_set_bit(hsotg, DCFG, DCFG_DESCDMA_EN);

	पूर्ण अन्यथा अणु
		dwc2_ग_लिखोl(hsotg, ((hsotg->dedicated_fअगरos) ?
						(GAHBCFG_NP_TXF_EMP_LVL |
						 GAHBCFG_P_TXF_EMP_LVL) : 0) |
			    GAHBCFG_GLBL_INTR_EN, GAHBCFG);
	पूर्ण

	/*
	 * If INTknTXFEmpMsk is enabled, it's important to disable ep पूर्णांकerrupts
	 * when we have no data to transfer. Otherwise we get being flooded by
	 * पूर्णांकerrupts.
	 */

	dwc2_ग_लिखोl(hsotg, ((hsotg->dedicated_fअगरos && !using_dma(hsotg)) ?
		DIEPMSK_TXFIFOEMPTY | DIEPMSK_INTKNTXFEMPMSK : 0) |
		DIEPMSK_EPDISBLDMSK | DIEPMSK_XFERCOMPLMSK |
		DIEPMSK_TIMEOUTMSK | DIEPMSK_AHBERRMSK,
		DIEPMSK);

	/*
	 * करोn't need XferCompl, we get that from RXFIFO in slave mode. In
	 * DMA mode we may need this and StsPhseRcvd.
	 */
	dwc2_ग_लिखोl(hsotg, (using_dma(hsotg) ? (DIEPMSK_XFERCOMPLMSK |
		DOEPMSK_STSPHSERCVDMSK) : 0) |
		DOEPMSK_EPDISBLDMSK | DOEPMSK_AHBERRMSK |
		DOEPMSK_SETUPMSK,
		DOEPMSK);

	/* Enable BNA पूर्णांकerrupt क्रम DDMA */
	अगर (using_desc_dma(hsotg)) अणु
		dwc2_set_bit(hsotg, DOEPMSK, DOEPMSK_BNAMSK);
		dwc2_set_bit(hsotg, DIEPMSK, DIEPMSK_BNAININTRMSK);
	पूर्ण

	/* Enable Service Interval mode अगर supported */
	अगर (using_desc_dma(hsotg) && hsotg->params.service_पूर्णांकerval)
		dwc2_set_bit(hsotg, DCTL, DCTL_SERVICE_INTERVAL_SUPPORTED);

	dwc2_ग_लिखोl(hsotg, 0, DAINTMSK);

	dev_dbg(hsotg->dev, "EP0: DIEPCTL0=0x%08x, DOEPCTL0=0x%08x\n",
		dwc2_पढ़ोl(hsotg, DIEPCTL0),
		dwc2_पढ़ोl(hsotg, DOEPCTL0));

	/* enable in and out endpoपूर्णांक पूर्णांकerrupts */
	dwc2_hsotg_en_gsपूर्णांक(hsotg, GINTSTS_OEPINT | GINTSTS_IEPINT);

	/*
	 * Enable the RXFIFO when in slave mode, as this is how we collect
	 * the data. In DMA mode, we get events from the FIFO but also
	 * things we cannot process, so करो not use it.
	 */
	अगर (!using_dma(hsotg))
		dwc2_hsotg_en_gsपूर्णांक(hsotg, GINTSTS_RXFLVL);

	/* Enable पूर्णांकerrupts क्रम EP0 in and out */
	dwc2_hsotg_ctrl_epपूर्णांक(hsotg, 0, 0, 1);
	dwc2_hsotg_ctrl_epपूर्णांक(hsotg, 0, 1, 1);

	अगर (!is_usb_reset) अणु
		dwc2_set_bit(hsotg, DCTL, DCTL_PWRONPRGDONE);
		udelay(10);  /* see खोलोiboot */
		dwc2_clear_bit(hsotg, DCTL, DCTL_PWRONPRGDONE);
	पूर्ण

	dev_dbg(hsotg->dev, "DCTL=0x%08x\n", dwc2_पढ़ोl(hsotg, DCTL));

	/*
	 * DxEPCTL_USBActEp says RO in manual, but seems to be set by
	 * writing to the EPCTL रेजिस्टर..
	 */

	/* set to पढ़ो 1 8byte packet */
	dwc2_ग_लिखोl(hsotg, DXEPTSIZ_MC(1) | DXEPTSIZ_PKTCNT(1) |
	       DXEPTSIZ_XFERSIZE(8), DOEPTSIZ0);

	dwc2_ग_लिखोl(hsotg, dwc2_hsotg_ep0_mps(hsotg->eps_out[0]->ep.maxpacket) |
	       DXEPCTL_CNAK | DXEPCTL_EPENA |
	       DXEPCTL_USBACTEP,
	       DOEPCTL0);

	/* enable, but करोn't activate EP0in */
	dwc2_ग_लिखोl(hsotg, dwc2_hsotg_ep0_mps(hsotg->eps_out[0]->ep.maxpacket) |
	       DXEPCTL_USBACTEP, DIEPCTL0);

	/* clear global NAKs */
	val = DCTL_CGOUTNAK | DCTL_CGNPINNAK;
	अगर (!is_usb_reset)
		val |= DCTL_SFTDISCON;
	dwc2_set_bit(hsotg, DCTL, val);

	/* configure the core to support LPM */
	dwc2_gadget_init_lpm(hsotg);

	/* program GREFCLK रेजिस्टर अगर needed */
	अगर (using_desc_dma(hsotg) && hsotg->params.service_पूर्णांकerval)
		dwc2_gadget_program_ref_clk(hsotg);

	/* must be at-least 3ms to allow bus to see disconnect */
	mdelay(3);

	hsotg->lx_state = DWC2_L0;

	dwc2_hsotg_enqueue_setup(hsotg);

	dev_dbg(hsotg->dev, "EP0: DIEPCTL0=0x%08x, DOEPCTL0=0x%08x\n",
		dwc2_पढ़ोl(hsotg, DIEPCTL0),
		dwc2_पढ़ोl(hsotg, DOEPCTL0));
पूर्ण

व्योम dwc2_hsotg_core_disconnect(काष्ठा dwc2_hsotg *hsotg)
अणु
	/* set the soft-disconnect bit */
	dwc2_set_bit(hsotg, DCTL, DCTL_SFTDISCON);
पूर्ण

व्योम dwc2_hsotg_core_connect(काष्ठा dwc2_hsotg *hsotg)
अणु
	/* हटाओ the soft-disconnect and let's go */
	dwc2_clear_bit(hsotg, DCTL, DCTL_SFTDISCON);
पूर्ण

/**
 * dwc2_gadget_handle_incomplete_isoc_in - handle incomplete ISO IN Interrupt.
 * @hsotg: The device state:
 *
 * This पूर्णांकerrupt indicates one of the following conditions occurred जबतक
 * transmitting an ISOC transaction.
 * - Corrupted IN Token क्रम ISOC EP.
 * - Packet not complete in FIFO.
 *
 * The following actions will be taken:
 * - Determine the EP
 * - Disable EP; when 'Endpoint Disabled' पूर्णांकerrupt is received Flush FIFO
 */
अटल व्योम dwc2_gadget_handle_incomplete_isoc_in(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_hsotg_ep *hs_ep;
	u32 epctrl;
	u32 daपूर्णांकmsk;
	u32 idx;

	dev_dbg(hsotg->dev, "Incomplete isoc in interrupt received:\n");

	daपूर्णांकmsk = dwc2_पढ़ोl(hsotg, DAINTMSK);

	क्रम (idx = 1; idx < hsotg->num_of_eps; idx++) अणु
		hs_ep = hsotg->eps_in[idx];
		/* Proceed only unmasked ISOC EPs */
		अगर ((BIT(idx) & ~daपूर्णांकmsk) || !hs_ep->isochronous)
			जारी;

		epctrl = dwc2_पढ़ोl(hsotg, DIEPCTL(idx));
		अगर ((epctrl & DXEPCTL_EPENA) &&
		    dwc2_gadget_target_frame_elapsed(hs_ep)) अणु
			epctrl |= DXEPCTL_SNAK;
			epctrl |= DXEPCTL_EPDIS;
			dwc2_ग_लिखोl(hsotg, epctrl, DIEPCTL(idx));
		पूर्ण
	पूर्ण

	/* Clear पूर्णांकerrupt */
	dwc2_ग_लिखोl(hsotg, GINTSTS_INCOMPL_SOIN, GINTSTS);
पूर्ण

/**
 * dwc2_gadget_handle_incomplete_isoc_out - handle incomplete ISO OUT Interrupt
 * @hsotg: The device state:
 *
 * This पूर्णांकerrupt indicates one of the following conditions occurred जबतक
 * transmitting an ISOC transaction.
 * - Corrupted OUT Token क्रम ISOC EP.
 * - Packet not complete in FIFO.
 *
 * The following actions will be taken:
 * - Determine the EP
 * - Set DCTL_SGOUTNAK and unmask GOUTNAKEFF अगर target frame elapsed.
 */
अटल व्योम dwc2_gadget_handle_incomplete_isoc_out(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 gपूर्णांकsts;
	u32 gपूर्णांकmsk;
	u32 daपूर्णांकmsk;
	u32 epctrl;
	काष्ठा dwc2_hsotg_ep *hs_ep;
	पूर्णांक idx;

	dev_dbg(hsotg->dev, "%s: GINTSTS_INCOMPL_SOOUT\n", __func__);

	daपूर्णांकmsk = dwc2_पढ़ोl(hsotg, DAINTMSK);
	daपूर्णांकmsk >>= DAINT_OUTEP_SHIFT;

	क्रम (idx = 1; idx < hsotg->num_of_eps; idx++) अणु
		hs_ep = hsotg->eps_out[idx];
		/* Proceed only unmasked ISOC EPs */
		अगर ((BIT(idx) & ~daपूर्णांकmsk) || !hs_ep->isochronous)
			जारी;

		epctrl = dwc2_पढ़ोl(hsotg, DOEPCTL(idx));
		अगर ((epctrl & DXEPCTL_EPENA) &&
		    dwc2_gadget_target_frame_elapsed(hs_ep)) अणु
			/* Unmask GOUTNAKEFF पूर्णांकerrupt */
			gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
			gपूर्णांकmsk |= GINTSTS_GOUTNAKEFF;
			dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);

			gपूर्णांकsts = dwc2_पढ़ोl(hsotg, GINTSTS);
			अगर (!(gपूर्णांकsts & GINTSTS_GOUTNAKEFF)) अणु
				dwc2_set_bit(hsotg, DCTL, DCTL_SGOUTNAK);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Clear पूर्णांकerrupt */
	dwc2_ग_लिखोl(hsotg, GINTSTS_INCOMPL_SOOUT, GINTSTS);
पूर्ण

/**
 * dwc2_hsotg_irq - handle device पूर्णांकerrupt
 * @irq: The IRQ number triggered
 * @pw: The pw value when रेजिस्टरed the handler.
 */
अटल irqवापस_t dwc2_hsotg_irq(पूर्णांक irq, व्योम *pw)
अणु
	काष्ठा dwc2_hsotg *hsotg = pw;
	पूर्णांक retry_count = 8;
	u32 gपूर्णांकsts;
	u32 gपूर्णांकmsk;

	अगर (!dwc2_is_device_mode(hsotg))
		वापस IRQ_NONE;

	spin_lock(&hsotg->lock);
irq_retry:
	gपूर्णांकsts = dwc2_पढ़ोl(hsotg, GINTSTS);
	gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);

	dev_dbg(hsotg->dev, "%s: %08x %08x (%08x) retry %d\n",
		__func__, gपूर्णांकsts, gपूर्णांकsts & gपूर्णांकmsk, gपूर्णांकmsk, retry_count);

	gपूर्णांकsts &= gपूर्णांकmsk;

	अगर (gपूर्णांकsts & GINTSTS_RESETDET) अणु
		dev_dbg(hsotg->dev, "%s: USBRstDet\n", __func__);

		dwc2_ग_लिखोl(hsotg, GINTSTS_RESETDET, GINTSTS);

		/* This event must be used only अगर controller is suspended */
		अगर (hsotg->in_ppd && hsotg->lx_state == DWC2_L2)
			dwc2_निकास_partial_घातer_करोwn(hsotg, 0, true);

		hsotg->lx_state = DWC2_L0;
	पूर्ण

	अगर (gपूर्णांकsts & (GINTSTS_USBRST | GINTSTS_RESETDET)) अणु
		u32 usb_status = dwc2_पढ़ोl(hsotg, GOTGCTL);
		u32 connected = hsotg->connected;

		dev_dbg(hsotg->dev, "%s: USBRst\n", __func__);
		dev_dbg(hsotg->dev, "GNPTXSTS=%08x\n",
			dwc2_पढ़ोl(hsotg, GNPTXSTS));

		dwc2_ग_लिखोl(hsotg, GINTSTS_USBRST, GINTSTS);

		/* Report disconnection अगर it is not alपढ़ोy करोne. */
		dwc2_hsotg_disconnect(hsotg);

		/* Reset device address to zero */
		dwc2_clear_bit(hsotg, DCFG, DCFG_DEVADDR_MASK);

		अगर (usb_status & GOTGCTL_BSESVLD && connected)
			dwc2_hsotg_core_init_disconnected(hsotg, true);
	पूर्ण

	अगर (gपूर्णांकsts & GINTSTS_ENUMDONE) अणु
		dwc2_ग_लिखोl(hsotg, GINTSTS_ENUMDONE, GINTSTS);

		dwc2_hsotg_irq_क्रमागतकरोne(hsotg);
	पूर्ण

	अगर (gपूर्णांकsts & (GINTSTS_OEPINT | GINTSTS_IEPINT)) अणु
		u32 daपूर्णांक = dwc2_पढ़ोl(hsotg, DAINT);
		u32 daपूर्णांकmsk = dwc2_पढ़ोl(hsotg, DAINTMSK);
		u32 daपूर्णांक_out, daपूर्णांक_in;
		पूर्णांक ep;

		daपूर्णांक &= daपूर्णांकmsk;
		daपूर्णांक_out = daपूर्णांक >> DAINT_OUTEP_SHIFT;
		daपूर्णांक_in = daपूर्णांक & ~(daपूर्णांक_out << DAINT_OUTEP_SHIFT);

		dev_dbg(hsotg->dev, "%s: daint=%08x\n", __func__, daपूर्णांक);

		क्रम (ep = 0; ep < hsotg->num_of_eps && daपूर्णांक_out;
						ep++, daपूर्णांक_out >>= 1) अणु
			अगर (daपूर्णांक_out & 1)
				dwc2_hsotg_epपूर्णांक(hsotg, ep, 0);
		पूर्ण

		क्रम (ep = 0; ep < hsotg->num_of_eps  && daपूर्णांक_in;
						ep++, daपूर्णांक_in >>= 1) अणु
			अगर (daपूर्णांक_in & 1)
				dwc2_hsotg_epपूर्णांक(hsotg, ep, 1);
		पूर्ण
	पूर्ण

	/* check both FIFOs */

	अगर (gपूर्णांकsts & GINTSTS_NPTXFEMP) अणु
		dev_dbg(hsotg->dev, "NPTxFEmp\n");

		/*
		 * Disable the पूर्णांकerrupt to stop it happening again
		 * unless one of these endpoपूर्णांक routines decides that
		 * it needs re-enabling
		 */

		dwc2_hsotg_disable_gsपूर्णांक(hsotg, GINTSTS_NPTXFEMP);
		dwc2_hsotg_irq_fअगरoempty(hsotg, false);
	पूर्ण

	अगर (gपूर्णांकsts & GINTSTS_PTXFEMP) अणु
		dev_dbg(hsotg->dev, "PTxFEmp\n");

		/* See note in GINTSTS_NPTxFEmp */

		dwc2_hsotg_disable_gsपूर्णांक(hsotg, GINTSTS_PTXFEMP);
		dwc2_hsotg_irq_fअगरoempty(hsotg, true);
	पूर्ण

	अगर (gपूर्णांकsts & GINTSTS_RXFLVL) अणु
		/*
		 * note, since GINTSTS_RxFLvl द्विगुनs as FIFO-not-empty,
		 * we need to retry dwc2_hsotg_handle_rx अगर this is still
		 * set.
		 */

		dwc2_hsotg_handle_rx(hsotg);
	पूर्ण

	अगर (gपूर्णांकsts & GINTSTS_ERLYSUSP) अणु
		dev_dbg(hsotg->dev, "GINTSTS_ErlySusp\n");
		dwc2_ग_लिखोl(hsotg, GINTSTS_ERLYSUSP, GINTSTS);
	पूर्ण

	/*
	 * these next two seem to crop-up occasionally causing the core
	 * to shutकरोwn the USB transfer, so try clearing them and logging
	 * the occurrence.
	 */

	अगर (gपूर्णांकsts & GINTSTS_GOUTNAKEFF) अणु
		u8 idx;
		u32 epctrl;
		u32 gपूर्णांकmsk;
		u32 daपूर्णांकmsk;
		काष्ठा dwc2_hsotg_ep *hs_ep;

		daपूर्णांकmsk = dwc2_पढ़ोl(hsotg, DAINTMSK);
		daपूर्णांकmsk >>= DAINT_OUTEP_SHIFT;
		/* Mask this पूर्णांकerrupt */
		gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
		gपूर्णांकmsk &= ~GINTSTS_GOUTNAKEFF;
		dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);

		dev_dbg(hsotg->dev, "GOUTNakEff triggered\n");
		क्रम (idx = 1; idx < hsotg->num_of_eps; idx++) अणु
			hs_ep = hsotg->eps_out[idx];
			/* Proceed only unmasked ISOC EPs */
			अगर (BIT(idx) & ~daपूर्णांकmsk)
				जारी;

			epctrl = dwc2_पढ़ोl(hsotg, DOEPCTL(idx));

			//ISOC Ep's only
			अगर ((epctrl & DXEPCTL_EPENA) && hs_ep->isochronous) अणु
				epctrl |= DXEPCTL_SNAK;
				epctrl |= DXEPCTL_EPDIS;
				dwc2_ग_लिखोl(hsotg, epctrl, DOEPCTL(idx));
				जारी;
			पूर्ण

			//Non-ISOC EP's
			अगर (hs_ep->halted) अणु
				अगर (!(epctrl & DXEPCTL_EPENA))
					epctrl |= DXEPCTL_EPENA;
				epctrl |= DXEPCTL_EPDIS;
				epctrl |= DXEPCTL_STALL;
				dwc2_ग_लिखोl(hsotg, epctrl, DOEPCTL(idx));
			पूर्ण
		पूर्ण

		/* This पूर्णांकerrupt bit is cleared in DXEPINT_EPDISBLD handler */
	पूर्ण

	अगर (gपूर्णांकsts & GINTSTS_GINNAKEFF) अणु
		dev_info(hsotg->dev, "GINNakEff triggered\n");

		dwc2_set_bit(hsotg, DCTL, DCTL_CGNPINNAK);

		dwc2_hsotg_dump(hsotg);
	पूर्ण

	अगर (gपूर्णांकsts & GINTSTS_INCOMPL_SOIN)
		dwc2_gadget_handle_incomplete_isoc_in(hsotg);

	अगर (gपूर्णांकsts & GINTSTS_INCOMPL_SOOUT)
		dwc2_gadget_handle_incomplete_isoc_out(hsotg);

	/*
	 * अगर we've had fअगरo events, we should try and go around the
	 * loop again to see अगर there's any poपूर्णांक in वापसing yet.
	 */

	अगर (gपूर्णांकsts & IRQ_RETRY_MASK && --retry_count > 0)
		जाओ irq_retry;

	/* Check WKUP_ALERT पूर्णांकerrupt*/
	अगर (hsotg->params.service_पूर्णांकerval)
		dwc2_gadget_wkup_alert_handler(hsotg);

	spin_unlock(&hsotg->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम dwc2_hsotg_ep_stop_xfr(काष्ठा dwc2_hsotg *hsotg,
				   काष्ठा dwc2_hsotg_ep *hs_ep)
अणु
	u32 epctrl_reg;
	u32 epपूर्णांक_reg;

	epctrl_reg = hs_ep->dir_in ? DIEPCTL(hs_ep->index) :
		DOEPCTL(hs_ep->index);
	epपूर्णांक_reg = hs_ep->dir_in ? DIEPINT(hs_ep->index) :
		DOEPINT(hs_ep->index);

	dev_dbg(hsotg->dev, "%s: stopping transfer on %s\n", __func__,
		hs_ep->name);

	अगर (hs_ep->dir_in) अणु
		अगर (hsotg->dedicated_fअगरos || hs_ep->periodic) अणु
			dwc2_set_bit(hsotg, epctrl_reg, DXEPCTL_SNAK);
			/* Wait क्रम Nak effect */
			अगर (dwc2_hsotg_रुको_bit_set(hsotg, epपूर्णांक_reg,
						    DXEPINT_INEPNAKEFF, 100))
				dev_warn(hsotg->dev,
					 "%s: timeout DIEPINT.NAKEFF\n",
					 __func__);
		पूर्ण अन्यथा अणु
			dwc2_set_bit(hsotg, DCTL, DCTL_SGNPINNAK);
			/* Wait क्रम Nak effect */
			अगर (dwc2_hsotg_रुको_bit_set(hsotg, GINTSTS,
						    GINTSTS_GINNAKEFF, 100))
				dev_warn(hsotg->dev,
					 "%s: timeout GINTSTS.GINNAKEFF\n",
					 __func__);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(dwc2_पढ़ोl(hsotg, GINTSTS) & GINTSTS_GOUTNAKEFF))
			dwc2_set_bit(hsotg, DCTL, DCTL_SGOUTNAK);

		/* Wait क्रम global nak to take effect */
		अगर (dwc2_hsotg_रुको_bit_set(hsotg, GINTSTS,
					    GINTSTS_GOUTNAKEFF, 100))
			dev_warn(hsotg->dev, "%s: timeout GINTSTS.GOUTNAKEFF\n",
				 __func__);
	पूर्ण

	/* Disable ep */
	dwc2_set_bit(hsotg, epctrl_reg, DXEPCTL_EPDIS | DXEPCTL_SNAK);

	/* Wait क्रम ep to be disabled */
	अगर (dwc2_hsotg_रुको_bit_set(hsotg, epपूर्णांक_reg, DXEPINT_EPDISBLD, 100))
		dev_warn(hsotg->dev,
			 "%s: timeout DOEPCTL.EPDisable\n", __func__);

	/* Clear EPDISBLD पूर्णांकerrupt */
	dwc2_set_bit(hsotg, epपूर्णांक_reg, DXEPINT_EPDISBLD);

	अगर (hs_ep->dir_in) अणु
		अचिन्हित लघु fअगरo_index;

		अगर (hsotg->dedicated_fअगरos || hs_ep->periodic)
			fअगरo_index = hs_ep->fअगरo_index;
		अन्यथा
			fअगरo_index = 0;

		/* Flush TX FIFO */
		dwc2_flush_tx_fअगरo(hsotg, fअगरo_index);

		/* Clear Global In NP NAK in Shared FIFO क्रम non periodic ep */
		अगर (!hsotg->dedicated_fअगरos && !hs_ep->periodic)
			dwc2_set_bit(hsotg, DCTL, DCTL_CGNPINNAK);

	पूर्ण अन्यथा अणु
		/* Remove global NAKs */
		dwc2_set_bit(hsotg, DCTL, DCTL_CGOUTNAK);
	पूर्ण
पूर्ण

/**
 * dwc2_hsotg_ep_enable - enable the given endpoपूर्णांक
 * @ep: The USB endpपूर्णांक to configure
 * @desc: The USB endpoपूर्णांक descriptor to configure with.
 *
 * This is called from the USB gadget code's usb_ep_enable().
 */
अटल पूर्णांक dwc2_hsotg_ep_enable(काष्ठा usb_ep *ep,
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा dwc2_hsotg_ep *hs_ep = our_ep(ep);
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक index = hs_ep->index;
	u32 epctrl_reg;
	u32 epctrl;
	u32 mps;
	u32 mc;
	u32 mask;
	अचिन्हित पूर्णांक dir_in;
	अचिन्हित पूर्णांक i, val, size;
	पूर्णांक ret = 0;
	अचिन्हित अक्षर ep_type;
	पूर्णांक desc_num;

	dev_dbg(hsotg->dev,
		"%s: ep %s: a 0x%02x, attr 0x%02x, mps 0x%04x, intr %d\n",
		__func__, ep->name, desc->bEndpoपूर्णांकAddress, desc->bmAttributes,
		desc->wMaxPacketSize, desc->bInterval);

	/* not to be called क्रम EP0 */
	अगर (index == 0) अणु
		dev_err(hsotg->dev, "%s: called for EP 0\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dir_in = (desc->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK) ? 1 : 0;
	अगर (dir_in != hs_ep->dir_in) अणु
		dev_err(hsotg->dev, "%s: direction mismatch!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ep_type = desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;
	mps = usb_endpoपूर्णांक_maxp(desc);
	mc = usb_endpoपूर्णांक_maxp_mult(desc);

	/* ISOC IN in DDMA supported bInterval up to 10 */
	अगर (using_desc_dma(hsotg) && ep_type == USB_ENDPOINT_XFER_ISOC &&
	    dir_in && desc->bInterval > 10) अणु
		dev_err(hsotg->dev,
			"%s: ISOC IN, DDMA: bInterval>10 not supported!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* High bandwidth ISOC OUT in DDMA not supported */
	अगर (using_desc_dma(hsotg) && ep_type == USB_ENDPOINT_XFER_ISOC &&
	    !dir_in && mc > 1) अणु
		dev_err(hsotg->dev,
			"%s: ISOC OUT, DDMA: HB not supported!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* note, we handle this here instead of dwc2_hsotg_set_ep_maxpacket */

	epctrl_reg = dir_in ? DIEPCTL(index) : DOEPCTL(index);
	epctrl = dwc2_पढ़ोl(hsotg, epctrl_reg);

	dev_dbg(hsotg->dev, "%s: read DxEPCTL=0x%08x from 0x%08x\n",
		__func__, epctrl, epctrl_reg);

	अगर (using_desc_dma(hsotg) && ep_type == USB_ENDPOINT_XFER_ISOC)
		desc_num = MAX_DMA_DESC_NUM_HS_ISOC;
	अन्यथा
		desc_num = MAX_DMA_DESC_NUM_GENERIC;

	/* Allocate DMA descriptor chain क्रम non-ctrl endpoपूर्णांकs */
	अगर (using_desc_dma(hsotg) && !hs_ep->desc_list) अणु
		hs_ep->desc_list = dmam_alloc_coherent(hsotg->dev,
			desc_num * माप(काष्ठा dwc2_dma_desc),
			&hs_ep->desc_list_dma, GFP_ATOMIC);
		अगर (!hs_ep->desc_list) अणु
			ret = -ENOMEM;
			जाओ error2;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&hsotg->lock, flags);

	epctrl &= ~(DXEPCTL_EPTYPE_MASK | DXEPCTL_MPS_MASK);
	epctrl |= DXEPCTL_MPS(mps);

	/*
	 * mark the endpoपूर्णांक as active, otherwise the core may ignore
	 * transactions entirely क्रम this endpoपूर्णांक
	 */
	epctrl |= DXEPCTL_USBACTEP;

	/* update the endpoपूर्णांक state */
	dwc2_hsotg_set_ep_maxpacket(hsotg, hs_ep->index, mps, mc, dir_in);

	/* शेष, set to non-periodic */
	hs_ep->isochronous = 0;
	hs_ep->periodic = 0;
	hs_ep->halted = 0;
	hs_ep->पूर्णांकerval = desc->bInterval;

	चयन (ep_type) अणु
	हाल USB_ENDPOINT_XFER_ISOC:
		epctrl |= DXEPCTL_EPTYPE_ISO;
		epctrl |= DXEPCTL_SETEVENFR;
		hs_ep->isochronous = 1;
		hs_ep->पूर्णांकerval = 1 << (desc->bInterval - 1);
		hs_ep->target_frame = TARGET_FRAME_INITIAL;
		hs_ep->next_desc = 0;
		hs_ep->compl_desc = 0;
		अगर (dir_in) अणु
			hs_ep->periodic = 1;
			mask = dwc2_पढ़ोl(hsotg, DIEPMSK);
			mask |= DIEPMSK_NAKMSK;
			dwc2_ग_लिखोl(hsotg, mask, DIEPMSK);
		पूर्ण अन्यथा अणु
			mask = dwc2_पढ़ोl(hsotg, DOEPMSK);
			mask |= DOEPMSK_OUTTKNEPDISMSK;
			dwc2_ग_लिखोl(hsotg, mask, DOEPMSK);
		पूर्ण
		अवरोध;

	हाल USB_ENDPOINT_XFER_BULK:
		epctrl |= DXEPCTL_EPTYPE_BULK;
		अवरोध;

	हाल USB_ENDPOINT_XFER_INT:
		अगर (dir_in)
			hs_ep->periodic = 1;

		अगर (hsotg->gadget.speed == USB_SPEED_HIGH)
			hs_ep->पूर्णांकerval = 1 << (desc->bInterval - 1);

		epctrl |= DXEPCTL_EPTYPE_INTERRUPT;
		अवरोध;

	हाल USB_ENDPOINT_XFER_CONTROL:
		epctrl |= DXEPCTL_EPTYPE_CONTROL;
		अवरोध;
	पूर्ण

	/*
	 * अगर the hardware has dedicated fअगरos, we must give each IN EP
	 * a unique tx-fअगरo even अगर it is non-periodic.
	 */
	अगर (dir_in && hsotg->dedicated_fअगरos) अणु
		अचिन्हित fअगरo_count = dwc2_hsotg_tx_fअगरo_count(hsotg);
		u32 fअगरo_index = 0;
		u32 fअगरo_size = अच_पूर्णांक_उच्च;

		size = hs_ep->ep.maxpacket * hs_ep->mc;
		क्रम (i = 1; i <= fअगरo_count; ++i) अणु
			अगर (hsotg->fअगरo_map & (1 << i))
				जारी;
			val = dwc2_पढ़ोl(hsotg, DPTXFSIZN(i));
			val = (val >> FIFOSIZE_DEPTH_SHIFT) * 4;
			अगर (val < size)
				जारी;
			/* Search क्रम smallest acceptable fअगरo */
			अगर (val < fअगरo_size) अणु
				fअगरo_size = val;
				fअगरo_index = i;
			पूर्ण
		पूर्ण
		अगर (!fअगरo_index) अणु
			dev_err(hsotg->dev,
				"%s: No suitable fifo found\n", __func__);
			ret = -ENOMEM;
			जाओ error1;
		पूर्ण
		epctrl &= ~(DXEPCTL_TXFNUM_LIMIT << DXEPCTL_TXFNUM_SHIFT);
		hsotg->fअगरo_map |= 1 << fअगरo_index;
		epctrl |= DXEPCTL_TXFNUM(fअगरo_index);
		hs_ep->fअगरo_index = fअगरo_index;
		hs_ep->fअगरo_size = fअगरo_size;
	पूर्ण

	/* क्रम non control endpoपूर्णांकs, set PID to D0 */
	अगर (index && !hs_ep->isochronous)
		epctrl |= DXEPCTL_SETD0PID;

	/* WA क्रम Full speed ISOC IN in DDMA mode.
	 * By Clear NAK status of EP, core will send ZLP
	 * to IN token and निश्चित NAK पूर्णांकerrupt relying
	 * on TxFIFO status only
	 */

	अगर (hsotg->gadget.speed == USB_SPEED_FULL &&
	    hs_ep->isochronous && dir_in) अणु
		/* The WA applies only to core versions from 2.72a
		 * to 4.00a (including both). Also क्रम FS_IOT_1.00a
		 * and HS_IOT_1.00a.
		 */
		u32 gsnpsid = dwc2_पढ़ोl(hsotg, GSNPSID);

		अगर ((gsnpsid >= DWC2_CORE_REV_2_72a &&
		     gsnpsid <= DWC2_CORE_REV_4_00a) ||
		     gsnpsid == DWC2_FS_IOT_REV_1_00a ||
		     gsnpsid == DWC2_HS_IOT_REV_1_00a)
			epctrl |= DXEPCTL_CNAK;
	पूर्ण

	dev_dbg(hsotg->dev, "%s: write DxEPCTL=0x%08x\n",
		__func__, epctrl);

	dwc2_ग_लिखोl(hsotg, epctrl, epctrl_reg);
	dev_dbg(hsotg->dev, "%s: read DxEPCTL=0x%08x\n",
		__func__, dwc2_पढ़ोl(hsotg, epctrl_reg));

	/* enable the endpoपूर्णांक पूर्णांकerrupt */
	dwc2_hsotg_ctrl_epपूर्णांक(hsotg, index, dir_in, 1);

error1:
	spin_unlock_irqrestore(&hsotg->lock, flags);

error2:
	अगर (ret && using_desc_dma(hsotg) && hs_ep->desc_list) अणु
		dmam_मुक्त_coherent(hsotg->dev, desc_num *
			माप(काष्ठा dwc2_dma_desc),
			hs_ep->desc_list, hs_ep->desc_list_dma);
		hs_ep->desc_list = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * dwc2_hsotg_ep_disable - disable given endpoपूर्णांक
 * @ep: The endpoपूर्णांक to disable.
 */
अटल पूर्णांक dwc2_hsotg_ep_disable(काष्ठा usb_ep *ep)
अणु
	काष्ठा dwc2_hsotg_ep *hs_ep = our_ep(ep);
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;
	पूर्णांक dir_in = hs_ep->dir_in;
	पूर्णांक index = hs_ep->index;
	u32 epctrl_reg;
	u32 ctrl;

	dev_dbg(hsotg->dev, "%s(ep %p)\n", __func__, ep);

	अगर (ep == &hsotg->eps_out[0]->ep) अणु
		dev_err(hsotg->dev, "%s: called for ep0\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (hsotg->op_state != OTG_STATE_B_PERIPHERAL) अणु
		dev_err(hsotg->dev, "%s: called in host mode?\n", __func__);
		वापस -EINVAL;
	पूर्ण

	epctrl_reg = dir_in ? DIEPCTL(index) : DOEPCTL(index);

	ctrl = dwc2_पढ़ोl(hsotg, epctrl_reg);

	अगर (ctrl & DXEPCTL_EPENA)
		dwc2_hsotg_ep_stop_xfr(hsotg, hs_ep);

	ctrl &= ~DXEPCTL_EPENA;
	ctrl &= ~DXEPCTL_USBACTEP;
	ctrl |= DXEPCTL_SNAK;

	dev_dbg(hsotg->dev, "%s: DxEPCTL=0x%08x\n", __func__, ctrl);
	dwc2_ग_लिखोl(hsotg, ctrl, epctrl_reg);

	/* disable endpoपूर्णांक पूर्णांकerrupts */
	dwc2_hsotg_ctrl_epपूर्णांक(hsotg, hs_ep->index, hs_ep->dir_in, 0);

	/* terminate all requests with shutकरोwn */
	समाप्त_all_requests(hsotg, hs_ep, -ESHUTDOWN);

	hsotg->fअगरo_map &= ~(1 << hs_ep->fअगरo_index);
	hs_ep->fअगरo_index = 0;
	hs_ep->fअगरo_size = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक dwc2_hsotg_ep_disable_lock(काष्ठा usb_ep *ep)
अणु
	काष्ठा dwc2_hsotg_ep *hs_ep = our_ep(ep);
	काष्ठा dwc2_hsotg *hsotg = hs_ep->parent;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&hsotg->lock, flags);
	ret = dwc2_hsotg_ep_disable(ep);
	spin_unlock_irqrestore(&hsotg->lock, flags);
	वापस ret;
पूर्ण

/**
 * on_list - check request is on the given endpoपूर्णांक
 * @ep: The endpoपूर्णांक to check.
 * @test: The request to test अगर it is on the endpoपूर्णांक.
 */
अटल bool on_list(काष्ठा dwc2_hsotg_ep *ep, काष्ठा dwc2_hsotg_req *test)
अणु
	काष्ठा dwc2_hsotg_req *req, *treq;

	list_क्रम_each_entry_safe(req, treq, &ep->queue, queue) अणु
		अगर (req == test)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * dwc2_hsotg_ep_dequeue - dequeue given endpoपूर्णांक
 * @ep: The endpoपूर्णांक to dequeue.
 * @req: The request to be हटाओd from a queue.
 */
अटल पूर्णांक dwc2_hsotg_ep_dequeue(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा dwc2_hsotg_req *hs_req = our_req(req);
	काष्ठा dwc2_hsotg_ep *hs_ep = our_ep(ep);
	काष्ठा dwc2_hsotg *hs = hs_ep->parent;
	अचिन्हित दीर्घ flags;

	dev_dbg(hs->dev, "ep_dequeue(%p,%p)\n", ep, req);

	spin_lock_irqsave(&hs->lock, flags);

	अगर (!on_list(hs_ep, hs_req)) अणु
		spin_unlock_irqrestore(&hs->lock, flags);
		वापस -EINVAL;
	पूर्ण

	/* Dequeue alपढ़ोy started request */
	अगर (req == &hs_ep->req->req)
		dwc2_hsotg_ep_stop_xfr(hs, hs_ep);

	dwc2_hsotg_complete_request(hs, hs_ep, hs_req, -ECONNRESET);
	spin_unlock_irqrestore(&hs->lock, flags);

	वापस 0;
पूर्ण

/**
 * dwc2_hsotg_ep_sethalt - set halt on a given endpoपूर्णांक
 * @ep: The endpoपूर्णांक to set halt.
 * @value: Set or unset the halt.
 * @now: If true, stall the endpoपूर्णांक now. Otherwise वापस -EAGAIN अगर
 *       the endpoपूर्णांक is busy processing requests.
 *
 * We need to stall the endpoपूर्णांक immediately अगर request comes from set_feature
 * protocol command handler.
 */
अटल पूर्णांक dwc2_hsotg_ep_sethalt(काष्ठा usb_ep *ep, पूर्णांक value, bool now)
अणु
	काष्ठा dwc2_hsotg_ep *hs_ep = our_ep(ep);
	काष्ठा dwc2_hsotg *hs = hs_ep->parent;
	पूर्णांक index = hs_ep->index;
	u32 epreg;
	u32 epctl;
	u32 xfertype;

	dev_info(hs->dev, "%s(ep %p %s, %d)\n", __func__, ep, ep->name, value);

	अगर (index == 0) अणु
		अगर (value)
			dwc2_hsotg_stall_ep0(hs);
		अन्यथा
			dev_warn(hs->dev,
				 "%s: can't clear halt on ep0\n", __func__);
		वापस 0;
	पूर्ण

	अगर (hs_ep->isochronous) अणु
		dev_err(hs->dev, "%s is Isochronous Endpoint\n", ep->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!now && value && !list_empty(&hs_ep->queue)) अणु
		dev_dbg(hs->dev, "%s request is pending, cannot halt\n",
			ep->name);
		वापस -EAGAIN;
	पूर्ण

	अगर (hs_ep->dir_in) अणु
		epreg = DIEPCTL(index);
		epctl = dwc2_पढ़ोl(hs, epreg);

		अगर (value) अणु
			epctl |= DXEPCTL_STALL | DXEPCTL_SNAK;
			अगर (epctl & DXEPCTL_EPENA)
				epctl |= DXEPCTL_EPDIS;
		पूर्ण अन्यथा अणु
			epctl &= ~DXEPCTL_STALL;
			xfertype = epctl & DXEPCTL_EPTYPE_MASK;
			अगर (xfertype == DXEPCTL_EPTYPE_BULK ||
			    xfertype == DXEPCTL_EPTYPE_INTERRUPT)
				epctl |= DXEPCTL_SETD0PID;
		पूर्ण
		dwc2_ग_लिखोl(hs, epctl, epreg);
	पूर्ण अन्यथा अणु
		epreg = DOEPCTL(index);
		epctl = dwc2_पढ़ोl(hs, epreg);

		अगर (value) अणु
			अगर (!(dwc2_पढ़ोl(hs, GINTSTS) & GINTSTS_GOUTNAKEFF))
				dwc2_set_bit(hs, DCTL, DCTL_SGOUTNAK);
			// STALL bit will be set in GOUTNAKEFF पूर्णांकerrupt handler
		पूर्ण अन्यथा अणु
			epctl &= ~DXEPCTL_STALL;
			xfertype = epctl & DXEPCTL_EPTYPE_MASK;
			अगर (xfertype == DXEPCTL_EPTYPE_BULK ||
			    xfertype == DXEPCTL_EPTYPE_INTERRUPT)
				epctl |= DXEPCTL_SETD0PID;
			dwc2_ग_लिखोl(hs, epctl, epreg);
		पूर्ण
	पूर्ण

	hs_ep->halted = value;
	वापस 0;
पूर्ण

/**
 * dwc2_hsotg_ep_sethalt_lock - set halt on a given endpoपूर्णांक with lock held
 * @ep: The endpoपूर्णांक to set halt.
 * @value: Set or unset the halt.
 */
अटल पूर्णांक dwc2_hsotg_ep_sethalt_lock(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	काष्ठा dwc2_hsotg_ep *hs_ep = our_ep(ep);
	काष्ठा dwc2_hsotg *hs = hs_ep->parent;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&hs->lock, flags);
	ret = dwc2_hsotg_ep_sethalt(ep, value, false);
	spin_unlock_irqrestore(&hs->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops dwc2_hsotg_ep_ops = अणु
	.enable		= dwc2_hsotg_ep_enable,
	.disable	= dwc2_hsotg_ep_disable_lock,
	.alloc_request	= dwc2_hsotg_ep_alloc_request,
	.मुक्त_request	= dwc2_hsotg_ep_मुक्त_request,
	.queue		= dwc2_hsotg_ep_queue_lock,
	.dequeue	= dwc2_hsotg_ep_dequeue,
	.set_halt	= dwc2_hsotg_ep_sethalt_lock,
	/* note, करोn't believe we have any call क्रम the fअगरo routines */
पूर्ण;

/**
 * dwc2_hsotg_init - initialize the usb core
 * @hsotg: The driver state
 */
अटल व्योम dwc2_hsotg_init(काष्ठा dwc2_hsotg *hsotg)
अणु
	/* unmask subset of endpoपूर्णांक पूर्णांकerrupts */

	dwc2_ग_लिखोl(hsotg, DIEPMSK_TIMEOUTMSK | DIEPMSK_AHBERRMSK |
		    DIEPMSK_EPDISBLDMSK | DIEPMSK_XFERCOMPLMSK,
		    DIEPMSK);

	dwc2_ग_लिखोl(hsotg, DOEPMSK_SETUPMSK | DOEPMSK_AHBERRMSK |
		    DOEPMSK_EPDISBLDMSK | DOEPMSK_XFERCOMPLMSK,
		    DOEPMSK);

	dwc2_ग_लिखोl(hsotg, 0, DAINTMSK);

	/* Be in disconnected state until gadget is रेजिस्टरed */
	dwc2_set_bit(hsotg, DCTL, DCTL_SFTDISCON);

	/* setup fअगरos */

	dev_dbg(hsotg->dev, "GRXFSIZ=0x%08x, GNPTXFSIZ=0x%08x\n",
		dwc2_पढ़ोl(hsotg, GRXFSIZ),
		dwc2_पढ़ोl(hsotg, GNPTXFSIZ));

	dwc2_hsotg_init_fअगरo(hsotg);

	अगर (using_dma(hsotg))
		dwc2_set_bit(hsotg, GAHBCFG, GAHBCFG_DMA_EN);
पूर्ण

/**
 * dwc2_hsotg_udc_start - prepare the udc क्रम work
 * @gadget: The usb gadget state
 * @driver: The usb gadget driver
 *
 * Perक्रमm initialization to prepare udc device and driver
 * to work.
 */
अटल पूर्णांक dwc2_hsotg_udc_start(काष्ठा usb_gadget *gadget,
				काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा dwc2_hsotg *hsotg = to_hsotg(gadget);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!hsotg) अणु
		pr_err("%s: called with no device\n", __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (!driver) अणु
		dev_err(hsotg->dev, "%s: no driver\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (driver->max_speed < USB_SPEED_FULL)
		dev_err(hsotg->dev, "%s: bad speed\n", __func__);

	अगर (!driver->setup) अणु
		dev_err(hsotg->dev, "%s: missing entry points\n", __func__);
		वापस -EINVAL;
	पूर्ण

	WARN_ON(hsotg->driver);

	driver->driver.bus = शून्य;
	hsotg->driver = driver;
	hsotg->gadget.dev.of_node = hsotg->dev->of_node;
	hsotg->gadget.speed = USB_SPEED_UNKNOWN;

	अगर (hsotg->dr_mode == USB_DR_MODE_PERIPHERAL) अणु
		ret = dwc2_lowlevel_hw_enable(hsotg);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(hsotg->uphy))
		otg_set_peripheral(hsotg->uphy->otg, &hsotg->gadget);

	spin_lock_irqsave(&hsotg->lock, flags);
	अगर (dwc2_hw_is_device(hsotg)) अणु
		dwc2_hsotg_init(hsotg);
		dwc2_hsotg_core_init_disconnected(hsotg, false);
	पूर्ण

	hsotg->enabled = 0;
	spin_unlock_irqrestore(&hsotg->lock, flags);

	gadget->sg_supported = using_desc_dma(hsotg);
	dev_info(hsotg->dev, "bound driver %s\n", driver->driver.name);

	वापस 0;

err:
	hsotg->driver = शून्य;
	वापस ret;
पूर्ण

/**
 * dwc2_hsotg_udc_stop - stop the udc
 * @gadget: The usb gadget state
 *
 * Stop udc hw block and stay tunned क्रम future transmissions
 */
अटल पूर्णांक dwc2_hsotg_udc_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा dwc2_hsotg *hsotg = to_hsotg(gadget);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ep;

	अगर (!hsotg)
		वापस -ENODEV;

	/* all endpoपूर्णांकs should be shutकरोwn */
	क्रम (ep = 1; ep < hsotg->num_of_eps; ep++) अणु
		अगर (hsotg->eps_in[ep])
			dwc2_hsotg_ep_disable_lock(&hsotg->eps_in[ep]->ep);
		अगर (hsotg->eps_out[ep])
			dwc2_hsotg_ep_disable_lock(&hsotg->eps_out[ep]->ep);
	पूर्ण

	spin_lock_irqsave(&hsotg->lock, flags);

	hsotg->driver = शून्य;
	hsotg->gadget.speed = USB_SPEED_UNKNOWN;
	hsotg->enabled = 0;

	spin_unlock_irqrestore(&hsotg->lock, flags);

	अगर (!IS_ERR_OR_शून्य(hsotg->uphy))
		otg_set_peripheral(hsotg->uphy->otg, शून्य);

	अगर (hsotg->dr_mode == USB_DR_MODE_PERIPHERAL)
		dwc2_lowlevel_hw_disable(hsotg);

	वापस 0;
पूर्ण

/**
 * dwc2_hsotg_gadget_getframe - पढ़ो the frame number
 * @gadget: The usb gadget state
 *
 * Read the अणुmicroपूर्ण frame number
 */
अटल पूर्णांक dwc2_hsotg_gadget_getframe(काष्ठा usb_gadget *gadget)
अणु
	वापस dwc2_hsotg_पढ़ो_frameno(to_hsotg(gadget));
पूर्ण

/**
 * dwc2_hsotg_set_selfघातered - set अगर device is self/bus घातered
 * @gadget: The usb gadget state
 * @is_selfघातered: Whether the device is self-घातered
 *
 * Set अगर the device is self or bus घातered.
 */
अटल पूर्णांक dwc2_hsotg_set_selfघातered(काष्ठा usb_gadget *gadget,
				      पूर्णांक is_selfघातered)
अणु
	काष्ठा dwc2_hsotg *hsotg = to_hsotg(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hsotg->lock, flags);
	gadget->is_selfघातered = !!is_selfघातered;
	spin_unlock_irqrestore(&hsotg->lock, flags);

	वापस 0;
पूर्ण

/**
 * dwc2_hsotg_pullup - connect/disconnect the USB PHY
 * @gadget: The usb gadget state
 * @is_on: Current state of the USB PHY
 *
 * Connect/Disconnect the USB PHY pullup
 */
अटल पूर्णांक dwc2_hsotg_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा dwc2_hsotg *hsotg = to_hsotg(gadget);
	अचिन्हित दीर्घ flags = 0;

	dev_dbg(hsotg->dev, "%s: is_on: %d op_state: %d\n", __func__, is_on,
		hsotg->op_state);

	/* Don't modअगरy pullup state जबतक in host mode */
	अगर (hsotg->op_state != OTG_STATE_B_PERIPHERAL) अणु
		hsotg->enabled = is_on;
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&hsotg->lock, flags);
	अगर (is_on) अणु
		hsotg->enabled = 1;
		dwc2_hsotg_core_init_disconnected(hsotg, false);
		/* Enable ACG feature in device mode,अगर supported */
		dwc2_enable_acg(hsotg);
		dwc2_hsotg_core_connect(hsotg);
	पूर्ण अन्यथा अणु
		dwc2_hsotg_core_disconnect(hsotg);
		dwc2_hsotg_disconnect(hsotg);
		hsotg->enabled = 0;
	पूर्ण

	hsotg->gadget.speed = USB_SPEED_UNKNOWN;
	spin_unlock_irqrestore(&hsotg->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc2_hsotg_vbus_session(काष्ठा usb_gadget *gadget, पूर्णांक is_active)
अणु
	काष्ठा dwc2_hsotg *hsotg = to_hsotg(gadget);
	अचिन्हित दीर्घ flags;

	dev_dbg(hsotg->dev, "%s: is_active: %d\n", __func__, is_active);
	spin_lock_irqsave(&hsotg->lock, flags);

	/*
	 * If controller is in partial घातer करोwn state, it must निकास from
	 * that state beक्रमe being initialized / de-initialized
	 */
	अगर (hsotg->lx_state == DWC2_L2 && hsotg->in_ppd)
		/*
		 * No need to check the वापस value as
		 * रेजिस्टरs are not being restored.
		 */
		dwc2_निकास_partial_घातer_करोwn(hsotg, 0, false);

	अगर (is_active) अणु
		hsotg->op_state = OTG_STATE_B_PERIPHERAL;

		dwc2_hsotg_core_init_disconnected(hsotg, false);
		अगर (hsotg->enabled) अणु
			/* Enable ACG feature in device mode,अगर supported */
			dwc2_enable_acg(hsotg);
			dwc2_hsotg_core_connect(hsotg);
		पूर्ण
	पूर्ण अन्यथा अणु
		dwc2_hsotg_core_disconnect(hsotg);
		dwc2_hsotg_disconnect(hsotg);
	पूर्ण

	spin_unlock_irqrestore(&hsotg->lock, flags);
	वापस 0;
पूर्ण

/**
 * dwc2_hsotg_vbus_draw - report bMaxPower field
 * @gadget: The usb gadget state
 * @mA: Amount of current
 *
 * Report how much घातer the device may consume to the phy.
 */
अटल पूर्णांक dwc2_hsotg_vbus_draw(काष्ठा usb_gadget *gadget, अचिन्हित पूर्णांक mA)
अणु
	काष्ठा dwc2_hsotg *hsotg = to_hsotg(gadget);

	अगर (IS_ERR_OR_शून्य(hsotg->uphy))
		वापस -ENOTSUPP;
	वापस usb_phy_set_घातer(hsotg->uphy, mA);
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops dwc2_hsotg_gadget_ops = अणु
	.get_frame	= dwc2_hsotg_gadget_getframe,
	.set_selfघातered	= dwc2_hsotg_set_selfघातered,
	.udc_start		= dwc2_hsotg_udc_start,
	.udc_stop		= dwc2_hsotg_udc_stop,
	.pullup                 = dwc2_hsotg_pullup,
	.vbus_session		= dwc2_hsotg_vbus_session,
	.vbus_draw		= dwc2_hsotg_vbus_draw,
पूर्ण;

/**
 * dwc2_hsotg_initep - initialise a single endpoपूर्णांक
 * @hsotg: The device state.
 * @hs_ep: The endpoपूर्णांक to be initialised.
 * @epnum: The endpoपूर्णांक number
 * @dir_in: True अगर direction is in.
 *
 * Initialise the given endpoपूर्णांक (as part of the probe and device state
 * creation) to give to the gadget driver. Setup the endpoपूर्णांक name, any
 * direction inक्रमmation and other state that may be required.
 */
अटल व्योम dwc2_hsotg_initep(काष्ठा dwc2_hsotg *hsotg,
			      काष्ठा dwc2_hsotg_ep *hs_ep,
				       पूर्णांक epnum,
				       bool dir_in)
अणु
	अक्षर *dir;

	अगर (epnum == 0)
		dir = "";
	अन्यथा अगर (dir_in)
		dir = "in";
	अन्यथा
		dir = "out";

	hs_ep->dir_in = dir_in;
	hs_ep->index = epnum;

	snम_लिखो(hs_ep->name, माप(hs_ep->name), "ep%d%s", epnum, dir);

	INIT_LIST_HEAD(&hs_ep->queue);
	INIT_LIST_HEAD(&hs_ep->ep.ep_list);

	/* add to the list of endpoपूर्णांकs known by the gadget driver */
	अगर (epnum)
		list_add_tail(&hs_ep->ep.ep_list, &hsotg->gadget.ep_list);

	hs_ep->parent = hsotg;
	hs_ep->ep.name = hs_ep->name;

	अगर (hsotg->params.speed == DWC2_SPEED_PARAM_LOW)
		usb_ep_set_maxpacket_limit(&hs_ep->ep, 8);
	अन्यथा
		usb_ep_set_maxpacket_limit(&hs_ep->ep,
					   epnum ? 1024 : EP0_MPS_LIMIT);
	hs_ep->ep.ops = &dwc2_hsotg_ep_ops;

	अगर (epnum == 0) अणु
		hs_ep->ep.caps.type_control = true;
	पूर्ण अन्यथा अणु
		अगर (hsotg->params.speed != DWC2_SPEED_PARAM_LOW) अणु
			hs_ep->ep.caps.type_iso = true;
			hs_ep->ep.caps.type_bulk = true;
		पूर्ण
		hs_ep->ep.caps.type_पूर्णांक = true;
	पूर्ण

	अगर (dir_in)
		hs_ep->ep.caps.dir_in = true;
	अन्यथा
		hs_ep->ep.caps.dir_out = true;

	/*
	 * अगर we're using dma, we need to set the next-endpoपूर्णांक poपूर्णांकer
	 * to be something valid.
	 */

	अगर (using_dma(hsotg)) अणु
		u32 next = DXEPCTL_NEXTEP((epnum + 1) % 15);

		अगर (dir_in)
			dwc2_ग_लिखोl(hsotg, next, DIEPCTL(epnum));
		अन्यथा
			dwc2_ग_लिखोl(hsotg, next, DOEPCTL(epnum));
	पूर्ण
पूर्ण

/**
 * dwc2_hsotg_hw_cfg - पढ़ो HW configuration रेजिस्टरs
 * @hsotg: Programming view of the DWC_otg controller
 *
 * Read the USB core HW configuration रेजिस्टरs
 */
अटल पूर्णांक dwc2_hsotg_hw_cfg(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 cfg;
	u32 ep_type;
	u32 i;

	/* check hardware configuration */

	hsotg->num_of_eps = hsotg->hw_params.num_dev_ep;

	/* Add ep0 */
	hsotg->num_of_eps++;

	hsotg->eps_in[0] = devm_kzalloc(hsotg->dev,
					माप(काष्ठा dwc2_hsotg_ep),
					GFP_KERNEL);
	अगर (!hsotg->eps_in[0])
		वापस -ENOMEM;
	/* Same dwc2_hsotg_ep is used in both directions क्रम ep0 */
	hsotg->eps_out[0] = hsotg->eps_in[0];

	cfg = hsotg->hw_params.dev_ep_dirs;
	क्रम (i = 1, cfg >>= 2; i < hsotg->num_of_eps; i++, cfg >>= 2) अणु
		ep_type = cfg & 3;
		/* Direction in or both */
		अगर (!(ep_type & 2)) अणु
			hsotg->eps_in[i] = devm_kzalloc(hsotg->dev,
				माप(काष्ठा dwc2_hsotg_ep), GFP_KERNEL);
			अगर (!hsotg->eps_in[i])
				वापस -ENOMEM;
		पूर्ण
		/* Direction out or both */
		अगर (!(ep_type & 1)) अणु
			hsotg->eps_out[i] = devm_kzalloc(hsotg->dev,
				माप(काष्ठा dwc2_hsotg_ep), GFP_KERNEL);
			अगर (!hsotg->eps_out[i])
				वापस -ENOMEM;
		पूर्ण
	पूर्ण

	hsotg->fअगरo_mem = hsotg->hw_params.total_fअगरo_size;
	hsotg->dedicated_fअगरos = hsotg->hw_params.en_multiple_tx_fअगरo;

	dev_info(hsotg->dev, "EPs: %d, %s fifos, %d entries in SPRAM\n",
		 hsotg->num_of_eps,
		 hsotg->dedicated_fअगरos ? "dedicated" : "shared",
		 hsotg->fअगरo_mem);
	वापस 0;
पूर्ण

/**
 * dwc2_hsotg_dump - dump state of the udc
 * @hsotg: Programming view of the DWC_otg controller
 *
 */
अटल व्योम dwc2_hsotg_dump(काष्ठा dwc2_hsotg *hsotg)
अणु
#अगर_घोषित DEBUG
	काष्ठा device *dev = hsotg->dev;
	u32 val;
	पूर्णांक idx;

	dev_info(dev, "DCFG=0x%08x, DCTL=0x%08x, DIEPMSK=%08x\n",
		 dwc2_पढ़ोl(hsotg, DCFG), dwc2_पढ़ोl(hsotg, DCTL),
		 dwc2_पढ़ोl(hsotg, DIEPMSK));

	dev_info(dev, "GAHBCFG=0x%08x, GHWCFG1=0x%08x\n",
		 dwc2_पढ़ोl(hsotg, GAHBCFG), dwc2_पढ़ोl(hsotg, GHWCFG1));

	dev_info(dev, "GRXFSIZ=0x%08x, GNPTXFSIZ=0x%08x\n",
		 dwc2_पढ़ोl(hsotg, GRXFSIZ), dwc2_पढ़ोl(hsotg, GNPTXFSIZ));

	/* show periodic fअगरo settings */

	क्रम (idx = 1; idx < hsotg->num_of_eps; idx++) अणु
		val = dwc2_पढ़ोl(hsotg, DPTXFSIZN(idx));
		dev_info(dev, "DPTx[%d] FSize=%d, StAddr=0x%08x\n", idx,
			 val >> FIFOSIZE_DEPTH_SHIFT,
			 val & FIFOSIZE_STARTADDR_MASK);
	पूर्ण

	क्रम (idx = 0; idx < hsotg->num_of_eps; idx++) अणु
		dev_info(dev,
			 "ep%d-in: EPCTL=0x%08x, SIZ=0x%08x, DMA=0x%08x\n", idx,
			 dwc2_पढ़ोl(hsotg, DIEPCTL(idx)),
			 dwc2_पढ़ोl(hsotg, DIEPTSIZ(idx)),
			 dwc2_पढ़ोl(hsotg, DIEPDMA(idx)));

		val = dwc2_पढ़ोl(hsotg, DOEPCTL(idx));
		dev_info(dev,
			 "ep%d-out: EPCTL=0x%08x, SIZ=0x%08x, DMA=0x%08x\n",
			 idx, dwc2_पढ़ोl(hsotg, DOEPCTL(idx)),
			 dwc2_पढ़ोl(hsotg, DOEPTSIZ(idx)),
			 dwc2_पढ़ोl(hsotg, DOEPDMA(idx)));
	पूर्ण

	dev_info(dev, "DVBUSDIS=0x%08x, DVBUSPULSE=%08x\n",
		 dwc2_पढ़ोl(hsotg, DVBUSDIS), dwc2_पढ़ोl(hsotg, DVBUSPULSE));
#पूर्ण_अगर
पूर्ण

/**
 * dwc2_gadget_init - init function क्रम gadget
 * @hsotg: Programming view of the DWC_otg controller
 *
 */
पूर्णांक dwc2_gadget_init(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा device *dev = hsotg->dev;
	पूर्णांक epnum;
	पूर्णांक ret;

	/* Dump fअगरo inक्रमmation */
	dev_dbg(dev, "NonPeriodic TXFIFO size: %d\n",
		hsotg->params.g_np_tx_fअगरo_size);
	dev_dbg(dev, "RXFIFO size: %d\n", hsotg->params.g_rx_fअगरo_size);

	hsotg->gadget.max_speed = USB_SPEED_HIGH;
	hsotg->gadget.ops = &dwc2_hsotg_gadget_ops;
	hsotg->gadget.name = dev_name(dev);
	hsotg->remote_wakeup_allowed = 0;

	अगर (hsotg->params.lpm)
		hsotg->gadget.lpm_capable = true;

	अगर (hsotg->dr_mode == USB_DR_MODE_OTG)
		hsotg->gadget.is_otg = 1;
	अन्यथा अगर (hsotg->dr_mode == USB_DR_MODE_PERIPHERAL)
		hsotg->op_state = OTG_STATE_B_PERIPHERAL;

	ret = dwc2_hsotg_hw_cfg(hsotg);
	अगर (ret) अणु
		dev_err(hsotg->dev, "Hardware configuration failed: %d\n", ret);
		वापस ret;
	पूर्ण

	hsotg->ctrl_buff = devm_kzalloc(hsotg->dev,
			DWC2_CTRL_BUFF_SIZE, GFP_KERNEL);
	अगर (!hsotg->ctrl_buff)
		वापस -ENOMEM;

	hsotg->ep0_buff = devm_kzalloc(hsotg->dev,
			DWC2_CTRL_BUFF_SIZE, GFP_KERNEL);
	अगर (!hsotg->ep0_buff)
		वापस -ENOMEM;

	अगर (using_desc_dma(hsotg)) अणु
		ret = dwc2_gadget_alloc_ctrl_desc_chains(hsotg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = devm_request_irq(hsotg->dev, hsotg->irq, dwc2_hsotg_irq,
			       IRQF_SHARED, dev_name(hsotg->dev), hsotg);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot claim IRQ for gadget\n");
		वापस ret;
	पूर्ण

	/* hsotg->num_of_eps holds number of EPs other than ep0 */

	अगर (hsotg->num_of_eps == 0) अणु
		dev_err(dev, "wrong number of EPs (zero)\n");
		वापस -EINVAL;
	पूर्ण

	/* setup endpoपूर्णांक inक्रमmation */

	INIT_LIST_HEAD(&hsotg->gadget.ep_list);
	hsotg->gadget.ep0 = &hsotg->eps_out[0]->ep;

	/* allocate EP0 request */

	hsotg->ctrl_req = dwc2_hsotg_ep_alloc_request(&hsotg->eps_out[0]->ep,
						     GFP_KERNEL);
	अगर (!hsotg->ctrl_req) अणु
		dev_err(dev, "failed to allocate ctrl req\n");
		वापस -ENOMEM;
	पूर्ण

	/* initialise the endpoपूर्णांकs now the core has been initialised */
	क्रम (epnum = 0; epnum < hsotg->num_of_eps; epnum++) अणु
		अगर (hsotg->eps_in[epnum])
			dwc2_hsotg_initep(hsotg, hsotg->eps_in[epnum],
					  epnum, 1);
		अगर (hsotg->eps_out[epnum])
			dwc2_hsotg_initep(hsotg, hsotg->eps_out[epnum],
					  epnum, 0);
	पूर्ण

	dwc2_hsotg_dump(hsotg);

	वापस 0;
पूर्ण

/**
 * dwc2_hsotg_हटाओ - हटाओ function क्रम hsotg driver
 * @hsotg: Programming view of the DWC_otg controller
 *
 */
पूर्णांक dwc2_hsotg_हटाओ(काष्ठा dwc2_hsotg *hsotg)
अणु
	usb_del_gadget_udc(&hsotg->gadget);
	dwc2_hsotg_ep_मुक्त_request(&hsotg->eps_out[0]->ep, hsotg->ctrl_req);

	वापस 0;
पूर्ण

पूर्णांक dwc2_hsotg_suspend(काष्ठा dwc2_hsotg *hsotg)
अणु
	अचिन्हित दीर्घ flags;

	अगर (hsotg->lx_state != DWC2_L0)
		वापस 0;

	अगर (hsotg->driver) अणु
		पूर्णांक ep;

		dev_info(hsotg->dev, "suspending usb gadget %s\n",
			 hsotg->driver->driver.name);

		spin_lock_irqsave(&hsotg->lock, flags);
		अगर (hsotg->enabled)
			dwc2_hsotg_core_disconnect(hsotg);
		dwc2_hsotg_disconnect(hsotg);
		hsotg->gadget.speed = USB_SPEED_UNKNOWN;
		spin_unlock_irqrestore(&hsotg->lock, flags);

		क्रम (ep = 0; ep < hsotg->num_of_eps; ep++) अणु
			अगर (hsotg->eps_in[ep])
				dwc2_hsotg_ep_disable_lock(&hsotg->eps_in[ep]->ep);
			अगर (hsotg->eps_out[ep])
				dwc2_hsotg_ep_disable_lock(&hsotg->eps_out[ep]->ep);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dwc2_hsotg_resume(काष्ठा dwc2_hsotg *hsotg)
अणु
	अचिन्हित दीर्घ flags;

	अगर (hsotg->lx_state == DWC2_L2)
		वापस 0;

	अगर (hsotg->driver) अणु
		dev_info(hsotg->dev, "resuming usb gadget %s\n",
			 hsotg->driver->driver.name);

		spin_lock_irqsave(&hsotg->lock, flags);
		dwc2_hsotg_core_init_disconnected(hsotg, false);
		अगर (hsotg->enabled) अणु
			/* Enable ACG feature in device mode,अगर supported */
			dwc2_enable_acg(hsotg);
			dwc2_hsotg_core_connect(hsotg);
		पूर्ण
		spin_unlock_irqrestore(&hsotg->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dwc2_backup_device_रेजिस्टरs() - Backup controller device रेजिस्टरs.
 * When suspending usb bus, रेजिस्टरs needs to be backuped
 * अगर controller घातer is disabled once suspended.
 *
 * @hsotg: Programming view of the DWC_otg controller
 */
पूर्णांक dwc2_backup_device_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_dregs_backup *dr;
	पूर्णांक i;

	dev_dbg(hsotg->dev, "%s\n", __func__);

	/* Backup dev regs */
	dr = &hsotg->dr_backup;

	dr->dcfg = dwc2_पढ़ोl(hsotg, DCFG);
	dr->dctl = dwc2_पढ़ोl(hsotg, DCTL);
	dr->daपूर्णांकmsk = dwc2_पढ़ोl(hsotg, DAINTMSK);
	dr->diepmsk = dwc2_पढ़ोl(hsotg, DIEPMSK);
	dr->करोepmsk = dwc2_पढ़ोl(hsotg, DOEPMSK);

	क्रम (i = 0; i < hsotg->num_of_eps; i++) अणु
		/* Backup IN EPs */
		dr->diepctl[i] = dwc2_पढ़ोl(hsotg, DIEPCTL(i));

		/* Ensure DATA PID is correctly configured */
		अगर (dr->diepctl[i] & DXEPCTL_DPID)
			dr->diepctl[i] |= DXEPCTL_SETD1PID;
		अन्यथा
			dr->diepctl[i] |= DXEPCTL_SETD0PID;

		dr->dieptsiz[i] = dwc2_पढ़ोl(hsotg, DIEPTSIZ(i));
		dr->diepdma[i] = dwc2_पढ़ोl(hsotg, DIEPDMA(i));

		/* Backup OUT EPs */
		dr->करोepctl[i] = dwc2_पढ़ोl(hsotg, DOEPCTL(i));

		/* Ensure DATA PID is correctly configured */
		अगर (dr->करोepctl[i] & DXEPCTL_DPID)
			dr->करोepctl[i] |= DXEPCTL_SETD1PID;
		अन्यथा
			dr->करोepctl[i] |= DXEPCTL_SETD0PID;

		dr->करोeptsiz[i] = dwc2_पढ़ोl(hsotg, DOEPTSIZ(i));
		dr->करोepdma[i] = dwc2_पढ़ोl(hsotg, DOEPDMA(i));
		dr->dtxfsiz[i] = dwc2_पढ़ोl(hsotg, DPTXFSIZN(i));
	पूर्ण
	dr->valid = true;
	वापस 0;
पूर्ण

/**
 * dwc2_restore_device_रेजिस्टरs() - Restore controller device रेजिस्टरs.
 * When resuming usb bus, device रेजिस्टरs needs to be restored
 * अगर controller घातer were disabled.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @remote_wakeup: Indicates whether resume is initiated by Device or Host.
 *
 * Return: 0 अगर successful, negative error code otherwise
 */
पूर्णांक dwc2_restore_device_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg, पूर्णांक remote_wakeup)
अणु
	काष्ठा dwc2_dregs_backup *dr;
	पूर्णांक i;

	dev_dbg(hsotg->dev, "%s\n", __func__);

	/* Restore dev regs */
	dr = &hsotg->dr_backup;
	अगर (!dr->valid) अणु
		dev_err(hsotg->dev, "%s: no device registers to restore\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	dr->valid = false;

	अगर (!remote_wakeup)
		dwc2_ग_लिखोl(hsotg, dr->dctl, DCTL);

	dwc2_ग_लिखोl(hsotg, dr->daपूर्णांकmsk, DAINTMSK);
	dwc2_ग_लिखोl(hsotg, dr->diepmsk, DIEPMSK);
	dwc2_ग_लिखोl(hsotg, dr->करोepmsk, DOEPMSK);

	क्रम (i = 0; i < hsotg->num_of_eps; i++) अणु
		/* Restore IN EPs */
		dwc2_ग_लिखोl(hsotg, dr->dieptsiz[i], DIEPTSIZ(i));
		dwc2_ग_लिखोl(hsotg, dr->diepdma[i], DIEPDMA(i));
		dwc2_ग_लिखोl(hsotg, dr->करोeptsiz[i], DOEPTSIZ(i));
		/** WA क्रम enabled EPx's IN in DDMA mode. On entering to
		 * hibernation wrong value पढ़ो and saved from DIEPDMAx,
		 * as result BNA पूर्णांकerrupt निश्चितed on hibernation निकास
		 * by restoring from saved area.
		 */
		अगर (hsotg->params.g_dma_desc &&
		    (dr->diepctl[i] & DXEPCTL_EPENA))
			dr->diepdma[i] = hsotg->eps_in[i]->desc_list_dma;
		dwc2_ग_लिखोl(hsotg, dr->dtxfsiz[i], DPTXFSIZN(i));
		dwc2_ग_लिखोl(hsotg, dr->diepctl[i], DIEPCTL(i));
		/* Restore OUT EPs */
		dwc2_ग_लिखोl(hsotg, dr->करोeptsiz[i], DOEPTSIZ(i));
		/* WA क्रम enabled EPx's OUT in DDMA mode. On entering to
		 * hibernation wrong value पढ़ो and saved from DOEPDMAx,
		 * as result BNA पूर्णांकerrupt निश्चितed on hibernation निकास
		 * by restoring from saved area.
		 */
		अगर (hsotg->params.g_dma_desc &&
		    (dr->करोepctl[i] & DXEPCTL_EPENA))
			dr->करोepdma[i] = hsotg->eps_out[i]->desc_list_dma;
		dwc2_ग_लिखोl(hsotg, dr->करोepdma[i], DOEPDMA(i));
		dwc2_ग_लिखोl(hsotg, dr->करोepctl[i], DOEPCTL(i));
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dwc2_gadget_init_lpm - Configure the core to support LPM in device mode
 *
 * @hsotg: Programming view of DWC_otg controller
 *
 */
व्योम dwc2_gadget_init_lpm(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 val;

	अगर (!hsotg->params.lpm)
		वापस;

	val = GLPMCFG_LPMCAP | GLPMCFG_APPL1RES;
	val |= hsotg->params.hird_threshold_en ? GLPMCFG_HIRD_THRES_EN : 0;
	val |= hsotg->params.lpm_घड़ी_gating ? GLPMCFG_ENBLSLPM : 0;
	val |= hsotg->params.hird_threshold << GLPMCFG_HIRD_THRES_SHIFT;
	val |= hsotg->params.besl ? GLPMCFG_ENBESL : 0;
	val |= GLPMCFG_LPM_REJECT_CTRL_CONTROL;
	val |= GLPMCFG_LPM_ACCEPT_CTRL_ISOC;
	dwc2_ग_लिखोl(hsotg, val, GLPMCFG);
	dev_dbg(hsotg->dev, "GLPMCFG=0x%08x\n", dwc2_पढ़ोl(hsotg, GLPMCFG));

	/* Unmask WKUP_ALERT Interrupt */
	अगर (hsotg->params.service_पूर्णांकerval)
		dwc2_set_bit(hsotg, GINTMSK2, GINTMSK2_WKUP_ALERT_INT_MSK);
पूर्ण

/**
 * dwc2_gadget_program_ref_clk - Program GREFCLK रेजिस्टर in device mode
 *
 * @hsotg: Programming view of DWC_otg controller
 *
 */
व्योम dwc2_gadget_program_ref_clk(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 val = 0;

	val |= GREFCLK_REF_CLK_MODE;
	val |= hsotg->params.ref_clk_per << GREFCLK_REFCLKPER_SHIFT;
	val |= hsotg->params.sof_cnt_wkup_alert <<
	       GREFCLK_SOF_CNT_WKUP_ALERT_SHIFT;

	dwc2_ग_लिखोl(hsotg, val, GREFCLK);
	dev_dbg(hsotg->dev, "GREFCLK=0x%08x\n", dwc2_पढ़ोl(hsotg, GREFCLK));
पूर्ण

/**
 * dwc2_gadget_enter_hibernation() - Put controller in Hibernation.
 *
 * @hsotg: Programming view of the DWC_otg controller
 *
 * Return non-zero अगर failed to enter to hibernation.
 */
पूर्णांक dwc2_gadget_enter_hibernation(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 gpwrdn;
	पूर्णांक ret = 0;

	/* Change to L2(suspend) state */
	hsotg->lx_state = DWC2_L2;
	dev_dbg(hsotg->dev, "Start of hibernation completed\n");
	ret = dwc2_backup_global_रेजिस्टरs(hsotg);
	अगर (ret) अणु
		dev_err(hsotg->dev, "%s: failed to backup global registers\n",
			__func__);
		वापस ret;
	पूर्ण
	ret = dwc2_backup_device_रेजिस्टरs(hsotg);
	अगर (ret) अणु
		dev_err(hsotg->dev, "%s: failed to backup device registers\n",
			__func__);
		वापस ret;
	पूर्ण

	gpwrdn = GPWRDN_PWRDNRSTN;
	gpwrdn |= GPWRDN_PMUACTV;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Set flag to indicate that we are in hibernation */
	hsotg->hibernated = 1;

	/* Enable पूर्णांकerrupts from wake up logic */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn |= GPWRDN_PMUINTSEL;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Unmask device mode पूर्णांकerrupts in GPWRDN */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn |= GPWRDN_RST_DET_MSK;
	gpwrdn |= GPWRDN_LNSTSCHG_MSK;
	gpwrdn |= GPWRDN_STS_CHGINT_MSK;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Enable Power Down Clamp */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn |= GPWRDN_PWRDNCLMP;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Switch off VDD */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn |= GPWRDN_PWRDNSWTCH;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	/* Save gpwrdn रेजिस्टर क्रम further usage अगर stschng पूर्णांकerrupt */
	hsotg->gr_backup.gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	dev_dbg(hsotg->dev, "Hibernation completed\n");

	वापस ret;
पूर्ण

/**
 * dwc2_gadget_निकास_hibernation()
 * This function is क्रम निकासing from Device mode hibernation by host initiated
 * resume/reset and device initiated remote-wakeup.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @rem_wakeup: indicates whether resume is initiated by Device or Host.
 * @reset: indicates whether resume is initiated by Reset.
 *
 * Return non-zero अगर failed to निकास from hibernation.
 */
पूर्णांक dwc2_gadget_निकास_hibernation(काष्ठा dwc2_hsotg *hsotg,
				 पूर्णांक rem_wakeup, पूर्णांक reset)
अणु
	u32 pcgcctl;
	u32 gpwrdn;
	u32 dctl;
	पूर्णांक ret = 0;
	काष्ठा dwc2_gregs_backup *gr;
	काष्ठा dwc2_dregs_backup *dr;

	gr = &hsotg->gr_backup;
	dr = &hsotg->dr_backup;

	अगर (!hsotg->hibernated) अणु
		dev_dbg(hsotg->dev, "Already exited from Hibernation\n");
		वापस 1;
	पूर्ण
	dev_dbg(hsotg->dev,
		"%s: called with rem_wakeup = %d reset = %d\n",
		__func__, rem_wakeup, reset);

	dwc2_hib_restore_common(hsotg, rem_wakeup, 0);

	अगर (!reset) अणु
		/* Clear all pending पूर्णांकerupts */
		dwc2_ग_लिखोl(hsotg, 0xffffffff, GINTSTS);
	पूर्ण

	/* De-निश्चित Restore */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn &= ~GPWRDN_RESTORE;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);
	udelay(10);

	अगर (!rem_wakeup) अणु
		pcgcctl = dwc2_पढ़ोl(hsotg, PCGCTL);
		pcgcctl &= ~PCGCTL_RSTPDWNMODULE;
		dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
	पूर्ण

	/* Restore GUSBCFG, DCFG and DCTL */
	dwc2_ग_लिखोl(hsotg, gr->gusbcfg, GUSBCFG);
	dwc2_ग_लिखोl(hsotg, dr->dcfg, DCFG);
	dwc2_ग_लिखोl(hsotg, dr->dctl, DCTL);

	/* On USB Reset, reset device address to zero */
	अगर (reset)
		dwc2_clear_bit(hsotg, DCFG, DCFG_DEVADDR_MASK);

	/* De-निश्चित Wakeup Logic */
	gpwrdn = dwc2_पढ़ोl(hsotg, GPWRDN);
	gpwrdn &= ~GPWRDN_PMUACTV;
	dwc2_ग_लिखोl(hsotg, gpwrdn, GPWRDN);

	अगर (rem_wakeup) अणु
		udelay(10);
		/* Start Remote Wakeup Signaling */
		dwc2_ग_लिखोl(hsotg, dr->dctl | DCTL_RMTWKUPSIG, DCTL);
	पूर्ण अन्यथा अणु
		udelay(50);
		/* Set Device programming करोne bit */
		dctl = dwc2_पढ़ोl(hsotg, DCTL);
		dctl |= DCTL_PWRONPRGDONE;
		dwc2_ग_लिखोl(hsotg, dctl, DCTL);
	पूर्ण
	/* Wait क्रम पूर्णांकerrupts which must be cleared */
	mdelay(2);
	/* Clear all pending पूर्णांकerupts */
	dwc2_ग_लिखोl(hsotg, 0xffffffff, GINTSTS);

	/* Restore global रेजिस्टरs */
	ret = dwc2_restore_global_रेजिस्टरs(hsotg);
	अगर (ret) अणु
		dev_err(hsotg->dev, "%s: failed to restore registers\n",
			__func__);
		वापस ret;
	पूर्ण

	/* Restore device रेजिस्टरs */
	ret = dwc2_restore_device_रेजिस्टरs(hsotg, rem_wakeup);
	अगर (ret) अणु
		dev_err(hsotg->dev, "%s: failed to restore device registers\n",
			__func__);
		वापस ret;
	पूर्ण

	अगर (rem_wakeup) अणु
		mdelay(10);
		dctl = dwc2_पढ़ोl(hsotg, DCTL);
		dctl &= ~DCTL_RMTWKUPSIG;
		dwc2_ग_लिखोl(hsotg, dctl, DCTL);
	पूर्ण

	hsotg->hibernated = 0;
	hsotg->lx_state = DWC2_L0;
	dev_dbg(hsotg->dev, "Hibernation recovery completes here\n");

	वापस ret;
पूर्ण

/**
 * dwc2_gadget_enter_partial_घातer_करोwn() - Put controller in partial
 * घातer करोwn.
 *
 * @hsotg: Programming view of the DWC_otg controller
 *
 * Return: non-zero अगर failed to enter device partial घातer करोwn.
 *
 * This function is क्रम entering device mode partial घातer करोwn.
 */
पूर्णांक dwc2_gadget_enter_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 pcgcctl;
	पूर्णांक ret = 0;

	dev_dbg(hsotg->dev, "Entering device partial power down started.\n");

	/* Backup all रेजिस्टरs */
	ret = dwc2_backup_global_रेजिस्टरs(hsotg);
	अगर (ret) अणु
		dev_err(hsotg->dev, "%s: failed to backup global registers\n",
			__func__);
		वापस ret;
	पूर्ण

	ret = dwc2_backup_device_रेजिस्टरs(hsotg);
	अगर (ret) अणु
		dev_err(hsotg->dev, "%s: failed to backup device registers\n",
			__func__);
		वापस ret;
	पूर्ण

	/*
	 * Clear any pending पूर्णांकerrupts since dwc2 will not be able to
	 * clear them after entering partial_घातer_करोwn.
	 */
	dwc2_ग_लिखोl(hsotg, 0xffffffff, GINTSTS);

	/* Put the controller in low घातer state */
	pcgcctl = dwc2_पढ़ोl(hsotg, PCGCTL);

	pcgcctl |= PCGCTL_PWRCLMP;
	dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
	udelay(5);

	pcgcctl |= PCGCTL_RSTPDWNMODULE;
	dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);
	udelay(5);

	pcgcctl |= PCGCTL_STOPPCLK;
	dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);

	/* Set in_ppd flag to 1 as here core enters suspend. */
	hsotg->in_ppd = 1;
	hsotg->lx_state = DWC2_L2;

	dev_dbg(hsotg->dev, "Entering device partial power down completed.\n");

	वापस ret;
पूर्ण

/*
 * dwc2_gadget_निकास_partial_घातer_करोwn() - Exit controller from device partial
 * घातer करोwn.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @restore: indicates whether need to restore the रेजिस्टरs or not.
 *
 * Return: non-zero अगर failed to निकास device partial घातer करोwn.
 *
 * This function is क्रम निकासing from device mode partial घातer करोwn.
 */
पूर्णांक dwc2_gadget_निकास_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg,
					bool restore)
अणु
	u32 pcgcctl;
	u32 dctl;
	काष्ठा dwc2_dregs_backup *dr;
	पूर्णांक ret = 0;

	dr = &hsotg->dr_backup;

	dev_dbg(hsotg->dev, "Exiting device partial Power Down started.\n");

	pcgcctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgcctl &= ~PCGCTL_STOPPCLK;
	dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);

	pcgcctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgcctl &= ~PCGCTL_PWRCLMP;
	dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);

	pcgcctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgcctl &= ~PCGCTL_RSTPDWNMODULE;
	dwc2_ग_लिखोl(hsotg, pcgcctl, PCGCTL);

	udelay(100);
	अगर (restore) अणु
		ret = dwc2_restore_global_रेजिस्टरs(hsotg);
		अगर (ret) अणु
			dev_err(hsotg->dev, "%s: failed to restore registers\n",
				__func__);
			वापस ret;
		पूर्ण
		/* Restore DCFG */
		dwc2_ग_लिखोl(hsotg, dr->dcfg, DCFG);

		ret = dwc2_restore_device_रेजिस्टरs(hsotg, 0);
		अगर (ret) अणु
			dev_err(hsotg->dev, "%s: failed to restore device registers\n",
				__func__);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Set the Power-On Programming करोne bit */
	dctl = dwc2_पढ़ोl(hsotg, DCTL);
	dctl |= DCTL_PWRONPRGDONE;
	dwc2_ग_लिखोl(hsotg, dctl, DCTL);

	/* Set in_ppd flag to 0 as here core निकासs from suspend. */
	hsotg->in_ppd = 0;
	hsotg->lx_state = DWC2_L0;

	dev_dbg(hsotg->dev, "Exiting device partial Power Down completed.\n");
	वापस ret;
पूर्ण

/**
 * dwc2_gadget_enter_घड़ी_gating() - Put controller in घड़ी gating.
 *
 * @hsotg: Programming view of the DWC_otg controller
 *
 * Return: non-zero अगर failed to enter device partial घातer करोwn.
 *
 * This function is क्रम entering device mode घड़ी gating.
 */
व्योम dwc2_gadget_enter_घड़ी_gating(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 pcgctl;

	dev_dbg(hsotg->dev, "Entering device clock gating.\n");

	/* Set the Phy Clock bit as suspend is received. */
	pcgctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgctl |= PCGCTL_STOPPCLK;
	dwc2_ग_लिखोl(hsotg, pcgctl, PCGCTL);
	udelay(5);

	/* Set the Gate hclk as suspend is received. */
	pcgctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgctl |= PCGCTL_GATEHCLK;
	dwc2_ग_लिखोl(hsotg, pcgctl, PCGCTL);
	udelay(5);

	hsotg->lx_state = DWC2_L2;
	hsotg->bus_suspended = true;
पूर्ण

/*
 * dwc2_gadget_निकास_घड़ी_gating() - Exit controller from device घड़ी gating.
 *
 * @hsotg: Programming view of the DWC_otg controller
 * @rem_wakeup: indicates whether remote wake up is enabled.
 *
 * This function is क्रम निकासing from device mode घड़ी gating.
 */
व्योम dwc2_gadget_निकास_घड़ी_gating(काष्ठा dwc2_hsotg *hsotg, पूर्णांक rem_wakeup)
अणु
	u32 pcgctl;
	u32 dctl;

	dev_dbg(hsotg->dev, "Exiting device clock gating.\n");

	/* Clear the Gate hclk. */
	pcgctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgctl &= ~PCGCTL_GATEHCLK;
	dwc2_ग_लिखोl(hsotg, pcgctl, PCGCTL);
	udelay(5);

	/* Phy Clock bit. */
	pcgctl = dwc2_पढ़ोl(hsotg, PCGCTL);
	pcgctl &= ~PCGCTL_STOPPCLK;
	dwc2_ग_लिखोl(hsotg, pcgctl, PCGCTL);
	udelay(5);

	अगर (rem_wakeup) अणु
		/* Set Remote Wakeup Signaling */
		dctl = dwc2_पढ़ोl(hsotg, DCTL);
		dctl |= DCTL_RMTWKUPSIG;
		dwc2_ग_लिखोl(hsotg, dctl, DCTL);
	पूर्ण

	/* Change to L0 state */
	call_gadget(hsotg, resume);
	hsotg->lx_state = DWC2_L0;
	hsotg->bus_suspended = false;
पूर्ण
