<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Freescale QUICC Engine USB Host Controller Driver
 *
 * Copyright (c) Freescale Semicondutor, Inc. 2006.
 *               Shlomi Gridish <gridish@मुक्तscale.com>
 *               Jerry Huang <Chang-Ming.Huang@मुक्तscale.com>
 * Copyright (c) Logic Product Development, Inc. 2007
 *               Peter Barada <peterb@logicpd.com>
 * Copyright (c) MontaVista Software, Inc. 2008.
 *               Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <soc/fsl/qe/qe.h>
#समावेश <यंत्र/fsl_gपंचांग.h>
#समावेश "fhci.h"

व्योम fhci_start_sof_समयr(काष्ठा fhci_hcd *fhci)
अणु
	fhci_dbg(fhci, "-> %s\n", __func__);

	/* clear frame_n */
	out_be16(&fhci->pram->frame_num, 0);

	out_be16(&fhci->regs->usb_ussft, 0);
	setbits8(&fhci->regs->usb_usmod, USB_MODE_SFTE);

	fhci_dbg(fhci, "<- %s\n", __func__);
पूर्ण

व्योम fhci_stop_sof_समयr(काष्ठा fhci_hcd *fhci)
अणु
	fhci_dbg(fhci, "-> %s\n", __func__);

	clrbits8(&fhci->regs->usb_usmod, USB_MODE_SFTE);
	gपंचांग_stop_समयr16(fhci->समयr);

	fhci_dbg(fhci, "<- %s\n", __func__);
पूर्ण

u16 fhci_get_sof_समयr_count(काष्ठा fhci_usb *usb)
अणु
	वापस be16_to_cpu(in_be16(&usb->fhci->regs->usb_ussft) / 12);
पूर्ण

/* initialize the endpoपूर्णांक zero */
अटल u32 endpoपूर्णांक_zero_init(काष्ठा fhci_usb *usb,
			      क्रमागत fhci_mem_alloc data_mem,
			      u32 ring_len)
अणु
	u32 rc;

	rc = fhci_create_ep(usb, data_mem, ring_len);
	अगर (rc)
		वापस rc;

	/* inilialize endpoपूर्णांक रेजिस्टरs */
	fhci_init_ep_रेजिस्टरs(usb, usb->ep0, data_mem);

	वापस 0;
पूर्ण

/* enable the USB पूर्णांकerrupts */
व्योम fhci_usb_enable_पूर्णांकerrupt(काष्ठा fhci_usb *usb)
अणु
	काष्ठा fhci_hcd *fhci = usb->fhci;

	अगर (usb->पूर्णांकr_nesting_cnt == 1) अणु
		/* initialize the USB पूर्णांकerrupt */
		enable_irq(fhci_to_hcd(fhci)->irq);

		/* initialize the event रेजिस्टर and mask रेजिस्टर */
		out_be16(&usb->fhci->regs->usb_usber, 0xffff);
		out_be16(&usb->fhci->regs->usb_usbmr, usb->saved_msk);

		/* enable the समयr पूर्णांकerrupts */
		enable_irq(fhci->समयr->irq);
	पूर्ण अन्यथा अगर (usb->पूर्णांकr_nesting_cnt > 1)
		fhci_info(fhci, "unbalanced USB interrupts nesting\n");
	usb->पूर्णांकr_nesting_cnt--;
पूर्ण

/* disable the usb पूर्णांकerrupt */
व्योम fhci_usb_disable_पूर्णांकerrupt(काष्ठा fhci_usb *usb)
अणु
	काष्ठा fhci_hcd *fhci = usb->fhci;

	अगर (usb->पूर्णांकr_nesting_cnt == 0) अणु
		/* disable the समयr पूर्णांकerrupt */
		disable_irq_nosync(fhci->समयr->irq);

		/* disable the usb पूर्णांकerrupt */
		disable_irq_nosync(fhci_to_hcd(fhci)->irq);
		out_be16(&usb->fhci->regs->usb_usbmr, 0);
	पूर्ण
	usb->पूर्णांकr_nesting_cnt++;
पूर्ण

/* enable the USB controller */
अटल u32 fhci_usb_enable(काष्ठा fhci_hcd *fhci)
अणु
	काष्ठा fhci_usb *usb = fhci->usb_lld;

	out_be16(&usb->fhci->regs->usb_usber, 0xffff);
	out_be16(&usb->fhci->regs->usb_usbmr, usb->saved_msk);
	setbits8(&usb->fhci->regs->usb_usmod, USB_MODE_EN);

	mdelay(100);

	वापस 0;
पूर्ण

/* disable the USB controller */
अटल u32 fhci_usb_disable(काष्ठा fhci_hcd *fhci)
अणु
	काष्ठा fhci_usb *usb = fhci->usb_lld;

	fhci_usb_disable_पूर्णांकerrupt(usb);
	fhci_port_disable(fhci);

	/* disable the usb controller */
	अगर (usb->port_status == FHCI_PORT_FULL ||
			usb->port_status == FHCI_PORT_LOW)
		fhci_device_disconnected_पूर्णांकerrupt(fhci);

	clrbits8(&usb->fhci->regs->usb_usmod, USB_MODE_EN);

	वापस 0;
पूर्ण

/* check the bus state by polling the QE bit on the IO ports */
पूर्णांक fhci_ioports_check_bus_state(काष्ठा fhci_hcd *fhci)
अणु
	u8 bits = 0;

	/* check USBOE,अगर transmitting,निकास */
	अगर (!gpio_get_value(fhci->gpios[GPIO_USBOE]))
		वापस -1;

	/* check USBRP */
	अगर (gpio_get_value(fhci->gpios[GPIO_USBRP]))
		bits |= 0x2;

	/* check USBRN */
	अगर (gpio_get_value(fhci->gpios[GPIO_USBRN]))
		bits |= 0x1;

	वापस bits;
पूर्ण

अटल व्योम fhci_mem_मुक्त(काष्ठा fhci_hcd *fhci)
अणु
	काष्ठा ed *ed;
	काष्ठा ed *next_ed;
	काष्ठा td *td;
	काष्ठा td *next_td;

	list_क्रम_each_entry_safe(ed, next_ed, &fhci->empty_eds, node) अणु
		list_del(&ed->node);
		kमुक्त(ed);
	पूर्ण

	list_क्रम_each_entry_safe(td, next_td, &fhci->empty_tds, node) अणु
		list_del(&td->node);
		kमुक्त(td);
	पूर्ण

	kमुक्त(fhci->vroot_hub);
	fhci->vroot_hub = शून्य;

	kमुक्त(fhci->hc_list);
	fhci->hc_list = शून्य;
पूर्ण

अटल पूर्णांक fhci_mem_init(काष्ठा fhci_hcd *fhci)
अणु
	पूर्णांक i;

	fhci->hc_list = kzalloc(माप(*fhci->hc_list), GFP_KERNEL);
	अगर (!fhci->hc_list)
		जाओ err;

	INIT_LIST_HEAD(&fhci->hc_list->ctrl_list);
	INIT_LIST_HEAD(&fhci->hc_list->bulk_list);
	INIT_LIST_HEAD(&fhci->hc_list->iso_list);
	INIT_LIST_HEAD(&fhci->hc_list->पूर्णांकr_list);
	INIT_LIST_HEAD(&fhci->hc_list->करोne_list);

	fhci->vroot_hub = kzalloc(माप(*fhci->vroot_hub), GFP_KERNEL);
	अगर (!fhci->vroot_hub)
		जाओ err;

	INIT_LIST_HEAD(&fhci->empty_eds);
	INIT_LIST_HEAD(&fhci->empty_tds);

	/* initialize work queue to handle करोne list */
	fhci_tasklet.data = (अचिन्हित दीर्घ)fhci;
	fhci->process_करोne_task = &fhci_tasklet;

	क्रम (i = 0; i < MAX_TDS; i++) अणु
		काष्ठा td *td;

		td = kदो_स्मृति(माप(*td), GFP_KERNEL);
		अगर (!td)
			जाओ err;
		fhci_recycle_empty_td(fhci, td);
	पूर्ण
	क्रम (i = 0; i < MAX_EDS; i++) अणु
		काष्ठा ed *ed;

		ed = kदो_स्मृति(माप(*ed), GFP_KERNEL);
		अगर (!ed)
			जाओ err;
		fhci_recycle_empty_ed(fhci, ed);
	पूर्ण

	fhci->active_urbs = 0;
	वापस 0;
err:
	fhci_mem_मुक्त(fhci);
	वापस -ENOMEM;
पूर्ण

/* destroy the fhci_usb काष्ठाure */
अटल व्योम fhci_usb_मुक्त(व्योम *lld)
अणु
	काष्ठा fhci_usb *usb = lld;
	काष्ठा fhci_hcd *fhci;

	अगर (usb) अणु
		fhci = usb->fhci;
		fhci_config_transceiver(fhci, FHCI_PORT_POWER_OFF);
		fhci_ep0_मुक्त(usb);
		kमुक्त(usb->actual_frame);
		kमुक्त(usb);
	पूर्ण
पूर्ण

/* initialize the USB */
अटल पूर्णांक fhci_usb_init(काष्ठा fhci_hcd *fhci)
अणु
	काष्ठा fhci_usb *usb = fhci->usb_lld;

	स_रखो_io(usb->fhci->pram, 0, FHCI_PRAM_SIZE);

	usb->port_status = FHCI_PORT_DISABLED;
	usb->max_frame_usage = FRAME_TIME_USAGE;
	usb->sw_transaction_समय = SW_FIX_TIME_BETWEEN_TRANSACTION;

	usb->actual_frame = kzalloc(माप(*usb->actual_frame), GFP_KERNEL);
	अगर (!usb->actual_frame) अणु
		fhci_usb_मुक्त(usb);
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&usb->actual_frame->tds_list);

	/* initializing रेजिस्टरs on chip, clear frame number */
	out_be16(&fhci->pram->frame_num, 0);

	/* clear rx state */
	out_be32(&fhci->pram->rx_state, 0);

	/* set mask रेजिस्टर */
	usb->saved_msk = (USB_E_TXB_MASK |
			  USB_E_TXE1_MASK |
			  USB_E_IDLE_MASK |
			  USB_E_RESET_MASK | USB_E_SFT_MASK | USB_E_MSF_MASK);

	out_8(&usb->fhci->regs->usb_usmod, USB_MODE_HOST | USB_MODE_EN);

	/* clearing the mask रेजिस्टर */
	out_be16(&usb->fhci->regs->usb_usbmr, 0);

	/* initialing the event रेजिस्टर */
	out_be16(&usb->fhci->regs->usb_usber, 0xffff);

	अगर (endpoपूर्णांक_zero_init(usb, DEFAULT_DATA_MEM, DEFAULT_RING_LEN) != 0) अणु
		fhci_usb_मुक्त(usb);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* initialize the fhci_usb काष्ठा and the corresponding data staruct */
अटल काष्ठा fhci_usb *fhci_create_lld(काष्ठा fhci_hcd *fhci)
अणु
	काष्ठा fhci_usb *usb;

	/* allocate memory क्रम SCC data काष्ठाure */
	usb = kzalloc(माप(*usb), GFP_KERNEL);
	अगर (!usb)
		वापस शून्य;

	usb->fhci = fhci;
	usb->hc_list = fhci->hc_list;
	usb->vroot_hub = fhci->vroot_hub;

	usb->transfer_confirm = fhci_transfer_confirm_callback;

	वापस usb;
पूर्ण

अटल पूर्णांक fhci_start(काष्ठा usb_hcd *hcd)
अणु
	पूर्णांक ret;
	काष्ठा fhci_hcd *fhci = hcd_to_fhci(hcd);

	ret = fhci_mem_init(fhci);
	अगर (ret) अणु
		fhci_err(fhci, "failed to allocate memory\n");
		जाओ err;
	पूर्ण

	fhci->usb_lld = fhci_create_lld(fhci);
	अगर (!fhci->usb_lld) अणु
		fhci_err(fhci, "low level driver config failed\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = fhci_usb_init(fhci);
	अगर (ret) अणु
		fhci_err(fhci, "low level driver initialize failed\n");
		जाओ err;
	पूर्ण

	spin_lock_init(&fhci->lock);

	/* connect the भव root hub */
	fhci->vroot_hub->dev_num = 1;	/* this field may be needed to fix */
	fhci->vroot_hub->hub.wHubStatus = 0;
	fhci->vroot_hub->hub.wHubChange = 0;
	fhci->vroot_hub->port.wPortStatus = 0;
	fhci->vroot_hub->port.wPortChange = 0;

	hcd->state = HC_STATE_RUNNING;

	/*
	 * From here on, hub_wq concurrently accesses the root
	 * hub; drivers will be talking to क्रमागतerated devices.
	 * (On restart paths, hub_wq alपढ़ोy knows about the root
	 * hub and could find work as soon as we wrote FLAG_CF.)
	 *
	 * Beक्रमe this poपूर्णांक the HC was idle/पढ़ोy.  After, hub_wq
	 * and device drivers may start it running.
	 */
	fhci_usb_enable(fhci);
	वापस 0;
err:
	fhci_mem_मुक्त(fhci);
	वापस ret;
पूर्ण

अटल व्योम fhci_stop(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा fhci_hcd *fhci = hcd_to_fhci(hcd);

	fhci_usb_disable_पूर्णांकerrupt(fhci->usb_lld);
	fhci_usb_disable(fhci);

	fhci_usb_मुक्त(fhci->usb_lld);
	fhci->usb_lld = शून्य;
	fhci_mem_मुक्त(fhci);
पूर्ण

अटल पूर्णांक fhci_urb_enqueue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
			    gfp_t mem_flags)
अणु
	काष्ठा fhci_hcd *fhci = hcd_to_fhci(hcd);
	u32 pipe = urb->pipe;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक size = 0;
	काष्ठा urb_priv *urb_priv;
	अचिन्हित दीर्घ flags;

	चयन (usb_pipetype(pipe)) अणु
	हाल PIPE_CONTROL:
		/* 1 td fro setup,1 क्रम ack */
		size = 2;
		fallthrough;
	हाल PIPE_BULK:
		/* one td क्रम every 4096 bytes(can be up to 8k) */
		size += urb->transfer_buffer_length / 4096;
		/* ...add क्रम any reमुख्यing bytes... */
		अगर ((urb->transfer_buffer_length % 4096) != 0)
			size++;
		/* ..and maybe a zero length packet to wrap it up */
		अगर (size == 0)
			size++;
		अन्यथा अगर ((urb->transfer_flags & URB_ZERO_PACKET) != 0
			 && (urb->transfer_buffer_length
			     % usb_maxpacket(urb->dev, pipe,
					     usb_pipeout(pipe))) != 0)
			size++;
		अवरोध;
	हाल PIPE_ISOCHRONOUS:
		size = urb->number_of_packets;
		अगर (size <= 0)
			वापस -EINVAL;
		क्रम (i = 0; i < urb->number_of_packets; i++) अणु
			urb->iso_frame_desc[i].actual_length = 0;
			urb->iso_frame_desc[i].status = (u32) (-EXDEV);
		पूर्ण
		अवरोध;
	हाल PIPE_INTERRUPT:
		size = 1;
	पूर्ण

	/* allocate the निजी part of the URB */
	urb_priv = kzalloc(माप(*urb_priv), mem_flags);
	अगर (!urb_priv)
		वापस -ENOMEM;

	/* allocate the निजी part of the URB */
	urb_priv->tds = kसुस्मृति(size, माप(*urb_priv->tds), mem_flags);
	अगर (!urb_priv->tds) अणु
		kमुक्त(urb_priv);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&fhci->lock, flags);

	ret = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (ret)
		जाओ err;

	/* fill the निजी part of the URB */
	urb_priv->num_of_tds = size;

	urb->status = -EINPROGRESS;
	urb->actual_length = 0;
	urb->error_count = 0;
	urb->hcpriv = urb_priv;

	fhci_queue_urb(fhci, urb);
err:
	अगर (ret) अणु
		kमुक्त(urb_priv->tds);
		kमुक्त(urb_priv);
	पूर्ण
	spin_unlock_irqrestore(&fhci->lock, flags);
	वापस ret;
पूर्ण

/* dequeue FHCI URB */
अटल पूर्णांक fhci_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा fhci_hcd *fhci = hcd_to_fhci(hcd);
	काष्ठा fhci_usb *usb = fhci->usb_lld;
	पूर्णांक ret = -EINVAL;
	अचिन्हित दीर्घ flags;

	अगर (!urb || !urb->dev || !urb->dev->bus)
		जाओ out;

	spin_lock_irqsave(&fhci->lock, flags);

	ret = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (ret)
		जाओ out2;

	अगर (usb->port_status != FHCI_PORT_DISABLED) अणु
		काष्ठा urb_priv *urb_priv;

		/*
		 * flag the urb's data क्रम deletion in some upcoming
		 * SF पूर्णांकerrupt's delete list processing
		 */
		urb_priv = urb->hcpriv;

		अगर (!urb_priv || (urb_priv->state == URB_DEL))
			जाओ out2;

		urb_priv->state = URB_DEL;

		/* alपढ़ोy pending? */
		urb_priv->ed->state = FHCI_ED_URB_DEL;
	पूर्ण अन्यथा अणु
		fhci_urb_complete_मुक्त(fhci, urb);
	पूर्ण

out2:
	spin_unlock_irqrestore(&fhci->lock, flags);
out:
	वापस ret;
पूर्ण

अटल व्योम fhci_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd,
				  काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा fhci_hcd *fhci;
	काष्ठा ed *ed;
	अचिन्हित दीर्घ flags;

	fhci = hcd_to_fhci(hcd);
	spin_lock_irqsave(&fhci->lock, flags);
	ed = ep->hcpriv;
	अगर (ed) अणु
		जबतक (ed->td_head != शून्य) अणु
			काष्ठा td *td = fhci_हटाओ_td_from_ed(ed);
			fhci_urb_complete_मुक्त(fhci, td->urb);
		पूर्ण
		fhci_recycle_empty_ed(fhci, ed);
		ep->hcpriv = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&fhci->lock, flags);
पूर्ण

अटल पूर्णांक fhci_get_frame_number(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा fhci_hcd *fhci = hcd_to_fhci(hcd);

	वापस get_frame_num(fhci);
पूर्ण

अटल स्थिर काष्ठा hc_driver fhci_driver = अणु
	.description = "fsl,usb-fhci",
	.product_desc = "FHCI HOST Controller",
	.hcd_priv_size = माप(काष्ठा fhci_hcd),

	/* generic hardware linkage */
	.irq = fhci_irq,
	.flags = HCD_DMA | HCD_USB11 | HCD_MEMORY,

	/* basic lअगरecycle operation */
	.start = fhci_start,
	.stop = fhci_stop,

	/* managing i/o requests and associated device resources */
	.urb_enqueue = fhci_urb_enqueue,
	.urb_dequeue = fhci_urb_dequeue,
	.endpoपूर्णांक_disable = fhci_endpoपूर्णांक_disable,

	/* scheduling support */
	.get_frame_number = fhci_get_frame_number,

	/* root hub support */
	.hub_status_data = fhci_hub_status_data,
	.hub_control = fhci_hub_control,
पूर्ण;

अटल पूर्णांक of_fhci_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा usb_hcd *hcd;
	काष्ठा fhci_hcd *fhci;
	काष्ठा resource usb_regs;
	अचिन्हित दीर्घ pram_addr;
	अचिन्हित पूर्णांक usb_irq;
	स्थिर अक्षर *sprop;
	स्थिर u32 *iprop;
	पूर्णांक size;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक j;

	अगर (usb_disabled())
		वापस -ENODEV;

	sprop = of_get_property(node, "mode", शून्य);
	अगर (sprop && म_भेद(sprop, "host"))
		वापस -ENODEV;

	hcd = usb_create_hcd(&fhci_driver, dev, dev_name(dev));
	अगर (!hcd) अणु
		dev_err(dev, "could not create hcd\n");
		वापस -ENOMEM;
	पूर्ण

	fhci = hcd_to_fhci(hcd);
	hcd->self.controller = dev;
	dev_set_drvdata(dev, hcd);

	iprop = of_get_property(node, "hub-power-budget", &size);
	अगर (iprop && size == माप(*iprop))
		hcd->घातer_budget = *iprop;

	/* FHCI रेजिस्टरs. */
	ret = of_address_to_resource(node, 0, &usb_regs);
	अगर (ret) अणु
		dev_err(dev, "could not get regs\n");
		जाओ err_regs;
	पूर्ण

	hcd->regs = ioremap(usb_regs.start, resource_size(&usb_regs));
	अगर (!hcd->regs) अणु
		dev_err(dev, "could not ioremap regs\n");
		ret = -ENOMEM;
		जाओ err_regs;
	पूर्ण
	fhci->regs = hcd->regs;

	/* Parameter RAM. */
	iprop = of_get_property(node, "reg", &size);
	अगर (!iprop || size < माप(*iprop) * 4) अणु
		dev_err(dev, "can't get pram offset\n");
		ret = -EINVAL;
		जाओ err_pram;
	पूर्ण

	pram_addr = cpm_muram_alloc(FHCI_PRAM_SIZE, 64);
	अगर (IS_ERR_VALUE(pram_addr)) अणु
		dev_err(dev, "failed to allocate usb pram\n");
		ret = -ENOMEM;
		जाओ err_pram;
	पूर्ण

	qe_issue_cmd(QE_ASSIGN_PAGE_TO_DEVICE, QE_CR_SUBBLOCK_USB,
		     QE_CR_PROTOCOL_UNSPECIFIED, pram_addr);
	fhci->pram = cpm_muram_addr(pram_addr);

	/* GPIOs and pins */
	क्रम (i = 0; i < NUM_GPIOS; i++) अणु
		पूर्णांक gpio;
		क्रमागत of_gpio_flags flags;

		gpio = of_get_gpio_flags(node, i, &flags);
		fhci->gpios[i] = gpio;
		fhci->alow_gpios[i] = flags & OF_GPIO_ACTIVE_LOW;

		अगर (!gpio_is_valid(gpio)) अणु
			अगर (i < GPIO_SPEED) अणु
				dev_err(dev, "incorrect GPIO%d: %d\n",
					i, gpio);
				जाओ err_gpios;
			पूर्ण अन्यथा अणु
				dev_info(dev, "assuming board doesn't have "
					"%s gpio\n", i == GPIO_SPEED ?
					"speed" : "power");
				जारी;
			पूर्ण
		पूर्ण

		ret = gpio_request(gpio, dev_name(dev));
		अगर (ret) अणु
			dev_err(dev, "failed to request gpio %d", i);
			जाओ err_gpios;
		पूर्ण

		अगर (i >= GPIO_SPEED) अणु
			ret = gpio_direction_output(gpio, 0);
			अगर (ret) अणु
				dev_err(dev, "failed to set gpio %d as "
					"an output\n", i);
				i++;
				जाओ err_gpios;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (j = 0; j < NUM_PINS; j++) अणु
		fhci->pins[j] = qe_pin_request(node, j);
		अगर (IS_ERR(fhci->pins[j])) अणु
			ret = PTR_ERR(fhci->pins[j]);
			dev_err(dev, "can't get pin %d: %d\n", j, ret);
			जाओ err_pins;
		पूर्ण
	पूर्ण

	/* Frame limit समयr and its पूर्णांकerrupt. */
	fhci->समयr = gपंचांग_get_समयr16();
	अगर (IS_ERR(fhci->समयr)) अणु
		ret = PTR_ERR(fhci->समयr);
		dev_err(dev, "failed to request qe timer: %i", ret);
		जाओ err_get_समयr;
	पूर्ण

	ret = request_irq(fhci->समयr->irq, fhci_frame_limit_समयr_irq,
			  0, "qe timer (usb)", hcd);
	अगर (ret) अणु
		dev_err(dev, "failed to request timer irq");
		जाओ err_समयr_irq;
	पूर्ण

	/* USB Host पूर्णांकerrupt. */
	usb_irq = irq_of_parse_and_map(node, 0);
	अगर (usb_irq == NO_IRQ) अणु
		dev_err(dev, "could not get usb irq\n");
		ret = -EINVAL;
		जाओ err_usb_irq;
	पूर्ण

	/* Clocks. */
	sprop = of_get_property(node, "fsl,fullspeed-clock", शून्य);
	अगर (sprop) अणु
		fhci->fullspeed_clk = qe_घड़ी_source(sprop);
		अगर (fhci->fullspeed_clk == QE_CLK_DUMMY) अणु
			dev_err(dev, "wrong fullspeed-clock\n");
			ret = -EINVAL;
			जाओ err_घड़ीs;
		पूर्ण
	पूर्ण

	sprop = of_get_property(node, "fsl,lowspeed-clock", शून्य);
	अगर (sprop) अणु
		fhci->lowspeed_clk = qe_घड़ी_source(sprop);
		अगर (fhci->lowspeed_clk == QE_CLK_DUMMY) अणु
			dev_err(dev, "wrong lowspeed-clock\n");
			ret = -EINVAL;
			जाओ err_घड़ीs;
		पूर्ण
	पूर्ण

	अगर (fhci->fullspeed_clk == QE_CLK_NONE &&
			fhci->lowspeed_clk == QE_CLK_NONE) अणु
		dev_err(dev, "no clocks specified\n");
		ret = -EINVAL;
		जाओ err_घड़ीs;
	पूर्ण

	dev_info(dev, "at 0x%p, irq %d\n", hcd->regs, usb_irq);

	fhci_config_transceiver(fhci, FHCI_PORT_POWER_OFF);

	/* Start with full-speed, अगर possible. */
	अगर (fhci->fullspeed_clk != QE_CLK_NONE) अणु
		fhci_config_transceiver(fhci, FHCI_PORT_FULL);
		qe_usb_घड़ी_set(fhci->fullspeed_clk, USB_CLOCK);
	पूर्ण अन्यथा अणु
		fhci_config_transceiver(fhci, FHCI_PORT_LOW);
		qe_usb_घड़ी_set(fhci->lowspeed_clk, USB_CLOCK >> 3);
	पूर्ण

	/* Clear and disable any pending पूर्णांकerrupts. */
	out_be16(&fhci->regs->usb_usber, 0xffff);
	out_be16(&fhci->regs->usb_usbmr, 0);

	ret = usb_add_hcd(hcd, usb_irq, 0);
	अगर (ret < 0)
		जाओ err_add_hcd;

	device_wakeup_enable(hcd->self.controller);

	fhci_dfs_create(fhci);

	वापस 0;

err_add_hcd:
err_घड़ीs:
	irq_dispose_mapping(usb_irq);
err_usb_irq:
	मुक्त_irq(fhci->समयr->irq, hcd);
err_समयr_irq:
	gपंचांग_put_समयr16(fhci->समयr);
err_get_समयr:
err_pins:
	जबतक (--j >= 0)
		qe_pin_मुक्त(fhci->pins[j]);
err_gpios:
	जबतक (--i >= 0) अणु
		अगर (gpio_is_valid(fhci->gpios[i]))
			gpio_मुक्त(fhci->gpios[i]);
	पूर्ण
	cpm_muram_मुक्त(pram_addr);
err_pram:
	iounmap(hcd->regs);
err_regs:
	usb_put_hcd(hcd);
	वापस ret;
पूर्ण

अटल पूर्णांक fhci_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा fhci_hcd *fhci = hcd_to_fhci(hcd);
	पूर्णांक i;
	पूर्णांक j;

	usb_हटाओ_hcd(hcd);
	मुक्त_irq(fhci->समयr->irq, hcd);
	gपंचांग_put_समयr16(fhci->समयr);
	cpm_muram_मुक्त(cpm_muram_offset(fhci->pram));
	क्रम (i = 0; i < NUM_GPIOS; i++) अणु
		अगर (!gpio_is_valid(fhci->gpios[i]))
			जारी;
		gpio_मुक्त(fhci->gpios[i]);
	पूर्ण
	क्रम (j = 0; j < NUM_PINS; j++)
		qe_pin_मुक्त(fhci->pins[j]);
	fhci_dfs_destroy(fhci);
	usb_put_hcd(hcd);
	वापस 0;
पूर्ण

अटल पूर्णांक of_fhci_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	वापस fhci_हटाओ(&ofdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_fhci_match[] = अणु
	अणु .compatible = "fsl,mpc8323-qe-usb", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_fhci_match);

अटल काष्ठा platक्रमm_driver of_fhci_driver = अणु
	.driver = अणु
		.name = "fsl,usb-fhci",
		.of_match_table = of_fhci_match,
	पूर्ण,
	.probe		= of_fhci_probe,
	.हटाओ		= of_fhci_हटाओ,
पूर्ण;

module_platक्रमm_driver(of_fhci_driver);

MODULE_DESCRIPTION("USB Freescale Host Controller Interface Driver");
MODULE_AUTHOR("Shlomi Gridish <gridish@freescale.com>, "
	      "Jerry Huang <Chang-Ming.Huang@freescale.com>, "
	      "Anton Vorontsov <avorontsov@ru.mvista.com>");
MODULE_LICENSE("GPL");
