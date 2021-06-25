<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * udc.c - ChipIdea UDC driver
 *
 * Copyright (C) 2008 Chipidea - MIPS Technologies, Inc. All rights reserved.
 *
 * Author: David Lopo
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/err.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg-fsm.h>
#समावेश <linux/usb/chipidea.h>

#समावेश "ci.h"
#समावेश "udc.h"
#समावेश "bits.h"
#समावेश "otg.h"
#समावेश "otg_fsm.h"
#समावेश "trace.h"

/* control endpoपूर्णांक description */
अटल स्थिर काष्ठा usb_endpoपूर्णांक_descriptor
ctrl_endpt_out_desc = अणु
	.bLength         = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress = USB_सूची_OUT,
	.bmAttributes    = USB_ENDPOINT_XFER_CONTROL,
	.wMaxPacketSize  = cpu_to_le16(CTRL_PAYLOAD_MAX),
पूर्ण;

अटल स्थिर काष्ठा usb_endpoपूर्णांक_descriptor
ctrl_endpt_in_desc = अणु
	.bLength         = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress = USB_सूची_IN,
	.bmAttributes    = USB_ENDPOINT_XFER_CONTROL,
	.wMaxPacketSize  = cpu_to_le16(CTRL_PAYLOAD_MAX),
पूर्ण;

/**
 * hw_ep_bit: calculates the bit number
 * @num: endpoपूर्णांक number
 * @dir: endpoपूर्णांक direction
 *
 * This function वापसs bit number
 */
अटल अंतरभूत पूर्णांक hw_ep_bit(पूर्णांक num, पूर्णांक dir)
अणु
	वापस num + ((dir == TX) ? 16 : 0);
पूर्ण

अटल अंतरभूत पूर्णांक ep_to_bit(काष्ठा ci_hdrc *ci, पूर्णांक n)
अणु
	पूर्णांक fill = 16 - ci->hw_ep_max / 2;

	अगर (n >= ci->hw_ep_max / 2)
		n += fill;

	वापस n;
पूर्ण

/**
 * hw_device_state: enables/disables पूर्णांकerrupts (execute without पूर्णांकerruption)
 * @ci: the controller
 * @dma: 0 => disable, !0 => enable and set dma engine
 *
 * This function वापसs an error code
 */
अटल पूर्णांक hw_device_state(काष्ठा ci_hdrc *ci, u32 dma)
अणु
	अगर (dma) अणु
		hw_ग_लिखो(ci, OP_ENDPTLISTADDR, ~0, dma);
		/* पूर्णांकerrupt, error, port change, reset, sleep/suspend */
		hw_ग_लिखो(ci, OP_USBINTR, ~0,
			     USBi_UI|USBi_UEI|USBi_PCI|USBi_URI|USBi_SLI);
	पूर्ण अन्यथा अणु
		hw_ग_लिखो(ci, OP_USBINTR, ~0, 0);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * hw_ep_flush: flush endpoपूर्णांक fअगरo (execute without पूर्णांकerruption)
 * @ci: the controller
 * @num: endpoपूर्णांक number
 * @dir: endpoपूर्णांक direction
 *
 * This function वापसs an error code
 */
अटल पूर्णांक hw_ep_flush(काष्ठा ci_hdrc *ci, पूर्णांक num, पूर्णांक dir)
अणु
	पूर्णांक n = hw_ep_bit(num, dir);

	करो अणु
		/* flush any pending transfer */
		hw_ग_लिखो(ci, OP_ENDPTFLUSH, ~0, BIT(n));
		जबतक (hw_पढ़ो(ci, OP_ENDPTFLUSH, BIT(n)))
			cpu_relax();
	पूर्ण जबतक (hw_पढ़ो(ci, OP_ENDPTSTAT, BIT(n)));

	वापस 0;
पूर्ण

/**
 * hw_ep_disable: disables endpoपूर्णांक (execute without पूर्णांकerruption)
 * @ci: the controller
 * @num: endpoपूर्णांक number
 * @dir: endpoपूर्णांक direction
 *
 * This function वापसs an error code
 */
अटल पूर्णांक hw_ep_disable(काष्ठा ci_hdrc *ci, पूर्णांक num, पूर्णांक dir)
अणु
	hw_ग_लिखो(ci, OP_ENDPTCTRL + num,
		 (dir == TX) ? ENDPTCTRL_TXE : ENDPTCTRL_RXE, 0);
	वापस 0;
पूर्ण

/**
 * hw_ep_enable: enables endpoपूर्णांक (execute without पूर्णांकerruption)
 * @ci: the controller
 * @num:  endpoपूर्णांक number
 * @dir:  endpoपूर्णांक direction
 * @type: endpoपूर्णांक type
 *
 * This function वापसs an error code
 */
अटल पूर्णांक hw_ep_enable(काष्ठा ci_hdrc *ci, पूर्णांक num, पूर्णांक dir, पूर्णांक type)
अणु
	u32 mask, data;

	अगर (dir == TX) अणु
		mask  = ENDPTCTRL_TXT;  /* type    */
		data  = type << __ffs(mask);

		mask |= ENDPTCTRL_TXS;  /* unstall */
		mask |= ENDPTCTRL_TXR;  /* reset data toggle */
		data |= ENDPTCTRL_TXR;
		mask |= ENDPTCTRL_TXE;  /* enable  */
		data |= ENDPTCTRL_TXE;
	पूर्ण अन्यथा अणु
		mask  = ENDPTCTRL_RXT;  /* type    */
		data  = type << __ffs(mask);

		mask |= ENDPTCTRL_RXS;  /* unstall */
		mask |= ENDPTCTRL_RXR;  /* reset data toggle */
		data |= ENDPTCTRL_RXR;
		mask |= ENDPTCTRL_RXE;  /* enable  */
		data |= ENDPTCTRL_RXE;
	पूर्ण
	hw_ग_लिखो(ci, OP_ENDPTCTRL + num, mask, data);
	वापस 0;
पूर्ण

/**
 * hw_ep_get_halt: वापस endpoपूर्णांक halt status
 * @ci: the controller
 * @num: endpoपूर्णांक number
 * @dir: endpoपूर्णांक direction
 *
 * This function वापसs 1 अगर endpoपूर्णांक halted
 */
अटल पूर्णांक hw_ep_get_halt(काष्ठा ci_hdrc *ci, पूर्णांक num, पूर्णांक dir)
अणु
	u32 mask = (dir == TX) ? ENDPTCTRL_TXS : ENDPTCTRL_RXS;

	वापस hw_पढ़ो(ci, OP_ENDPTCTRL + num, mask) ? 1 : 0;
पूर्ण

/**
 * hw_ep_prime: primes endpoपूर्णांक (execute without पूर्णांकerruption)
 * @ci: the controller
 * @num:     endpoपूर्णांक number
 * @dir:     endpoपूर्णांक direction
 * @is_ctrl: true अगर control endpoपूर्णांक
 *
 * This function वापसs an error code
 */
अटल पूर्णांक hw_ep_prime(काष्ठा ci_hdrc *ci, पूर्णांक num, पूर्णांक dir, पूर्णांक is_ctrl)
अणु
	पूर्णांक n = hw_ep_bit(num, dir);

	/* Synchronize beक्रमe ep prime */
	wmb();

	अगर (is_ctrl && dir == RX && hw_पढ़ो(ci, OP_ENDPTSETUPSTAT, BIT(num)))
		वापस -EAGAIN;

	hw_ग_लिखो(ci, OP_ENDPTPRIME, ~0, BIT(n));

	जबतक (hw_पढ़ो(ci, OP_ENDPTPRIME, BIT(n)))
		cpu_relax();
	अगर (is_ctrl && dir == RX && hw_पढ़ो(ci, OP_ENDPTSETUPSTAT, BIT(num)))
		वापस -EAGAIN;

	/* status shoult be tested according with manual but it करोesn't work */
	वापस 0;
पूर्ण

/**
 * hw_ep_set_halt: configures ep halt & resets data toggle after clear (execute
 *                 without पूर्णांकerruption)
 * @ci: the controller
 * @num:   endpoपूर्णांक number
 * @dir:   endpoपूर्णांक direction
 * @value: true => stall, false => unstall
 *
 * This function वापसs an error code
 */
अटल पूर्णांक hw_ep_set_halt(काष्ठा ci_hdrc *ci, पूर्णांक num, पूर्णांक dir, पूर्णांक value)
अणु
	अगर (value != 0 && value != 1)
		वापस -EINVAL;

	करो अणु
		क्रमागत ci_hw_regs reg = OP_ENDPTCTRL + num;
		u32 mask_xs = (dir == TX) ? ENDPTCTRL_TXS : ENDPTCTRL_RXS;
		u32 mask_xr = (dir == TX) ? ENDPTCTRL_TXR : ENDPTCTRL_RXR;

		/* data toggle - reserved क्रम EP0 but it's in ESS */
		hw_ग_लिखो(ci, reg, mask_xs|mask_xr,
			  value ? mask_xs : mask_xr);
	पूर्ण जबतक (value != hw_ep_get_halt(ci, num, dir));

	वापस 0;
पूर्ण

/**
 * hw_is_port_high_speed: test अगर port is high speed
 * @ci: the controller
 *
 * This function वापसs true अगर high speed port
 */
अटल पूर्णांक hw_port_is_high_speed(काष्ठा ci_hdrc *ci)
अणु
	वापस ci->hw_bank.lpm ? hw_पढ़ो(ci, OP_DEVLC, DEVLC_PSPD) :
		hw_पढ़ो(ci, OP_PORTSC, PORTSC_HSP);
पूर्ण

/**
 * hw_test_and_clear_complete: test & clear complete status (execute without
 *                             पूर्णांकerruption)
 * @ci: the controller
 * @n: endpoपूर्णांक number
 *
 * This function वापसs complete status
 */
अटल पूर्णांक hw_test_and_clear_complete(काष्ठा ci_hdrc *ci, पूर्णांक n)
अणु
	n = ep_to_bit(ci, n);
	वापस hw_test_and_clear(ci, OP_ENDPTCOMPLETE, BIT(n));
पूर्ण

/**
 * hw_test_and_clear_पूर्णांकr_active: test & clear active पूर्णांकerrupts (execute
 *                                without पूर्णांकerruption)
 * @ci: the controller
 *
 * This function वापसs active पूर्णांकerrutps
 */
अटल u32 hw_test_and_clear_पूर्णांकr_active(काष्ठा ci_hdrc *ci)
अणु
	u32 reg = hw_पढ़ो_पूर्णांकr_status(ci) & hw_पढ़ो_पूर्णांकr_enable(ci);

	hw_ग_लिखो(ci, OP_USBSTS, ~0, reg);
	वापस reg;
पूर्ण

/**
 * hw_test_and_clear_setup_guard: test & clear setup guard (execute without
 *                                पूर्णांकerruption)
 * @ci: the controller
 *
 * This function वापसs guard value
 */
अटल पूर्णांक hw_test_and_clear_setup_guard(काष्ठा ci_hdrc *ci)
अणु
	वापस hw_test_and_ग_लिखो(ci, OP_USBCMD, USBCMD_SUTW, 0);
पूर्ण

/**
 * hw_test_and_set_setup_guard: test & set setup guard (execute without
 *                              पूर्णांकerruption)
 * @ci: the controller
 *
 * This function वापसs guard value
 */
अटल पूर्णांक hw_test_and_set_setup_guard(काष्ठा ci_hdrc *ci)
अणु
	वापस hw_test_and_ग_लिखो(ci, OP_USBCMD, USBCMD_SUTW, USBCMD_SUTW);
पूर्ण

/**
 * hw_usb_set_address: configures USB address (execute without पूर्णांकerruption)
 * @ci: the controller
 * @value: new USB address
 *
 * This function explicitly sets the address, without the "USBADRA" (advance)
 * feature, which is not supported by older versions of the controller.
 */
अटल व्योम hw_usb_set_address(काष्ठा ci_hdrc *ci, u8 value)
अणु
	hw_ग_लिखो(ci, OP_DEVICEADDR, DEVICEADDR_USBADR,
		 value << __ffs(DEVICEADDR_USBADR));
पूर्ण

/**
 * hw_usb_reset: restart device after a bus reset (execute without
 *               पूर्णांकerruption)
 * @ci: the controller
 *
 * This function वापसs an error code
 */
अटल पूर्णांक hw_usb_reset(काष्ठा ci_hdrc *ci)
अणु
	hw_usb_set_address(ci, 0);

	/* ESS flushes only at end?!? */
	hw_ग_लिखो(ci, OP_ENDPTFLUSH,    ~0, ~0);

	/* clear setup token semaphores */
	hw_ग_लिखो(ci, OP_ENDPTSETUPSTAT, 0,  0);

	/* clear complete status */
	hw_ग_लिखो(ci, OP_ENDPTCOMPLETE,  0,  0);

	/* रुको until all bits cleared */
	जबतक (hw_पढ़ो(ci, OP_ENDPTPRIME, ~0))
		udelay(10);             /* not RTOS मित्रly */

	/* reset all endpoपूर्णांकs ? */

	/* reset पूर्णांकernal status and रुको क्रम further inकाष्ठाions
	   no need to verअगरy the port reset status (ESS करोes it) */

	वापस 0;
पूर्ण

/******************************************************************************
 * UTIL block
 *****************************************************************************/

अटल पूर्णांक add_td_to_list(काष्ठा ci_hw_ep *hwep, काष्ठा ci_hw_req *hwreq,
			अचिन्हित पूर्णांक length, काष्ठा scatterlist *s)
अणु
	पूर्णांक i;
	u32 temp;
	काष्ठा td_node *lastnode, *node = kzalloc(माप(काष्ठा td_node),
						  GFP_ATOMIC);

	अगर (node == शून्य)
		वापस -ENOMEM;

	node->ptr = dma_pool_zalloc(hwep->td_pool, GFP_ATOMIC, &node->dma);
	अगर (node->ptr == शून्य) अणु
		kमुक्त(node);
		वापस -ENOMEM;
	पूर्ण

	node->ptr->token = cpu_to_le32(length << __ffs(TD_TOTAL_BYTES));
	node->ptr->token &= cpu_to_le32(TD_TOTAL_BYTES);
	node->ptr->token |= cpu_to_le32(TD_STATUS_ACTIVE);
	अगर (hwep->type == USB_ENDPOINT_XFER_ISOC && hwep->dir == TX) अणु
		u32 mul = hwreq->req.length / hwep->ep.maxpacket;

		अगर (hwreq->req.length == 0
				|| hwreq->req.length % hwep->ep.maxpacket)
			mul++;
		node->ptr->token |= cpu_to_le32(mul << __ffs(TD_MULTO));
	पूर्ण

	अगर (s) अणु
		temp = (u32) (sg_dma_address(s) + hwreq->req.actual);
		node->td_reमुख्यing_size = CI_MAX_BUF_SIZE - length;
	पूर्ण अन्यथा अणु
		temp = (u32) (hwreq->req.dma + hwreq->req.actual);
	पूर्ण

	अगर (length) अणु
		node->ptr->page[0] = cpu_to_le32(temp);
		क्रम (i = 1; i < TD_PAGE_COUNT; i++) अणु
			u32 page = temp + i * CI_HDRC_PAGE_SIZE;
			page &= ~TD_RESERVED_MASK;
			node->ptr->page[i] = cpu_to_le32(page);
		पूर्ण
	पूर्ण

	hwreq->req.actual += length;

	अगर (!list_empty(&hwreq->tds)) अणु
		/* get the last entry */
		lastnode = list_entry(hwreq->tds.prev,
				काष्ठा td_node, td);
		lastnode->ptr->next = cpu_to_le32(node->dma);
	पूर्ण

	INIT_LIST_HEAD(&node->td);
	list_add_tail(&node->td, &hwreq->tds);

	वापस 0;
पूर्ण

/**
 * _usb_addr: calculates endpoपूर्णांक address from direction & number
 * @ep:  endpoपूर्णांक
 */
अटल अंतरभूत u8 _usb_addr(काष्ठा ci_hw_ep *ep)
अणु
	वापस ((ep->dir == TX) ? USB_ENDPOINT_सूची_MASK : 0) | ep->num;
पूर्ण

अटल पूर्णांक prepare_td_क्रम_non_sg(काष्ठा ci_hw_ep *hwep,
		काष्ठा ci_hw_req *hwreq)
अणु
	अचिन्हित पूर्णांक rest = hwreq->req.length;
	पूर्णांक pages = TD_PAGE_COUNT;
	पूर्णांक ret = 0;

	अगर (rest == 0) अणु
		ret = add_td_to_list(hwep, hwreq, 0, शून्य);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/*
	 * The first buffer could be not page aligned.
	 * In that हाल we have to span पूर्णांकo one extra td.
	 */
	अगर (hwreq->req.dma % PAGE_SIZE)
		pages--;

	जबतक (rest > 0) अणु
		अचिन्हित पूर्णांक count = min(hwreq->req.length - hwreq->req.actual,
			(अचिन्हित पूर्णांक)(pages * CI_HDRC_PAGE_SIZE));

		ret = add_td_to_list(hwep, hwreq, count, शून्य);
		अगर (ret < 0)
			वापस ret;

		rest -= count;
	पूर्ण

	अगर (hwreq->req.zero && hwreq->req.length && hwep->dir == TX
	    && (hwreq->req.length % hwep->ep.maxpacket == 0)) अणु
		ret = add_td_to_list(hwep, hwreq, 0, शून्य);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक prepare_td_per_sg(काष्ठा ci_hw_ep *hwep, काष्ठा ci_hw_req *hwreq,
		काष्ठा scatterlist *s)
अणु
	अचिन्हित पूर्णांक rest = sg_dma_len(s);
	पूर्णांक ret = 0;

	hwreq->req.actual = 0;
	जबतक (rest > 0) अणु
		अचिन्हित पूर्णांक count = min_t(अचिन्हित पूर्णांक, rest,
				CI_MAX_BUF_SIZE);

		ret = add_td_to_list(hwep, hwreq, count, s);
		अगर (ret < 0)
			वापस ret;

		rest -= count;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ci_add_buffer_entry(काष्ठा td_node *node, काष्ठा scatterlist *s)
अणु
	पूर्णांक empty_td_slot_index = (CI_MAX_BUF_SIZE - node->td_reमुख्यing_size)
			/ CI_HDRC_PAGE_SIZE;
	पूर्णांक i;
	u32 token;

	token = le32_to_cpu(node->ptr->token) + (sg_dma_len(s) << __ffs(TD_TOTAL_BYTES));
	node->ptr->token = cpu_to_le32(token);

	क्रम (i = empty_td_slot_index; i < TD_PAGE_COUNT; i++) अणु
		u32 page = (u32) sg_dma_address(s) +
			(i - empty_td_slot_index) * CI_HDRC_PAGE_SIZE;

		page &= ~TD_RESERVED_MASK;
		node->ptr->page[i] = cpu_to_le32(page);
	पूर्ण
पूर्ण

अटल पूर्णांक prepare_td_क्रम_sg(काष्ठा ci_hw_ep *hwep, काष्ठा ci_hw_req *hwreq)
अणु
	काष्ठा usb_request *req = &hwreq->req;
	काष्ठा scatterlist *s = req->sg;
	पूर्णांक ret = 0, i = 0;
	काष्ठा td_node *node = शून्य;

	अगर (!s || req->zero || req->length == 0) अणु
		dev_err(hwep->ci->dev, "not supported operation for sg\n");
		वापस -EINVAL;
	पूर्ण

	जबतक (i++ < req->num_mapped_sgs) अणु
		अगर (sg_dma_address(s) % PAGE_SIZE) अणु
			dev_err(hwep->ci->dev, "not page aligned sg buffer\n");
			वापस -EINVAL;
		पूर्ण

		अगर (node && (node->td_reमुख्यing_size >= sg_dma_len(s))) अणु
			ci_add_buffer_entry(node, s);
			node->td_reमुख्यing_size -= sg_dma_len(s);
		पूर्ण अन्यथा अणु
			ret = prepare_td_per_sg(hwep, hwreq, s);
			अगर (ret)
				वापस ret;

			node = list_entry(hwreq->tds.prev,
				काष्ठा td_node, td);
		पूर्ण

		s = sg_next(s);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * _hardware_enqueue: configures a request at hardware level
 * @hwep:   endpoपूर्णांक
 * @hwreq:  request
 *
 * This function वापसs an error code
 */
अटल पूर्णांक _hardware_enqueue(काष्ठा ci_hw_ep *hwep, काष्ठा ci_hw_req *hwreq)
अणु
	काष्ठा ci_hdrc *ci = hwep->ci;
	पूर्णांक ret = 0;
	काष्ठा td_node *firstnode, *lastnode;

	/* करोn't queue twice */
	अगर (hwreq->req.status == -EALREADY)
		वापस -EALREADY;

	hwreq->req.status = -EALREADY;

	ret = usb_gadget_map_request_by_dev(ci->dev->parent,
					    &hwreq->req, hwep->dir);
	अगर (ret)
		वापस ret;

	अगर (hwreq->req.num_mapped_sgs)
		ret = prepare_td_क्रम_sg(hwep, hwreq);
	अन्यथा
		ret = prepare_td_क्रम_non_sg(hwep, hwreq);

	अगर (ret)
		वापस ret;

	lastnode = list_entry(hwreq->tds.prev,
		काष्ठा td_node, td);

	lastnode->ptr->next = cpu_to_le32(TD_TERMINATE);
	अगर (!hwreq->req.no_पूर्णांकerrupt)
		lastnode->ptr->token |= cpu_to_le32(TD_IOC);

	list_क्रम_each_entry_safe(firstnode, lastnode, &hwreq->tds, td)
		trace_ci_prepare_td(hwep, hwreq, firstnode);

	firstnode = list_first_entry(&hwreq->tds, काष्ठा td_node, td);

	wmb();

	hwreq->req.actual = 0;
	अगर (!list_empty(&hwep->qh.queue)) अणु
		काष्ठा ci_hw_req *hwreqprev;
		पूर्णांक n = hw_ep_bit(hwep->num, hwep->dir);
		पूर्णांक पंचांगp_stat;
		काष्ठा td_node *prevlastnode;
		u32 next = firstnode->dma & TD_ADDR_MASK;

		hwreqprev = list_entry(hwep->qh.queue.prev,
				काष्ठा ci_hw_req, queue);
		prevlastnode = list_entry(hwreqprev->tds.prev,
				काष्ठा td_node, td);

		prevlastnode->ptr->next = cpu_to_le32(next);
		wmb();
		अगर (hw_पढ़ो(ci, OP_ENDPTPRIME, BIT(n)))
			जाओ करोne;
		करो अणु
			hw_ग_लिखो(ci, OP_USBCMD, USBCMD_ATDTW, USBCMD_ATDTW);
			पंचांगp_stat = hw_पढ़ो(ci, OP_ENDPTSTAT, BIT(n));
		पूर्ण जबतक (!hw_पढ़ो(ci, OP_USBCMD, USBCMD_ATDTW));
		hw_ग_लिखो(ci, OP_USBCMD, USBCMD_ATDTW, 0);
		अगर (पंचांगp_stat)
			जाओ करोne;
	पूर्ण

	/*  QH configuration */
	hwep->qh.ptr->td.next = cpu_to_le32(firstnode->dma);
	hwep->qh.ptr->td.token &=
		cpu_to_le32(~(TD_STATUS_HALTED|TD_STATUS_ACTIVE));

	अगर (hwep->type == USB_ENDPOINT_XFER_ISOC && hwep->dir == RX) अणु
		u32 mul = hwreq->req.length / hwep->ep.maxpacket;

		अगर (hwreq->req.length == 0
				|| hwreq->req.length % hwep->ep.maxpacket)
			mul++;
		hwep->qh.ptr->cap |= cpu_to_le32(mul << __ffs(QH_MULT));
	पूर्ण

	ret = hw_ep_prime(ci, hwep->num, hwep->dir,
			   hwep->type == USB_ENDPOINT_XFER_CONTROL);
करोne:
	वापस ret;
पूर्ण

/**
 * मुक्त_pending_td: हटाओ a pending request क्रम the endpoपूर्णांक
 * @hwep: endpoपूर्णांक
 */
अटल व्योम मुक्त_pending_td(काष्ठा ci_hw_ep *hwep)
अणु
	काष्ठा td_node *pending = hwep->pending_td;

	dma_pool_मुक्त(hwep->td_pool, pending->ptr, pending->dma);
	hwep->pending_td = शून्य;
	kमुक्त(pending);
पूर्ण

अटल पूर्णांक reprime_dtd(काष्ठा ci_hdrc *ci, काष्ठा ci_hw_ep *hwep,
					   काष्ठा td_node *node)
अणु
	hwep->qh.ptr->td.next = cpu_to_le32(node->dma);
	hwep->qh.ptr->td.token &=
		cpu_to_le32(~(TD_STATUS_HALTED | TD_STATUS_ACTIVE));

	वापस hw_ep_prime(ci, hwep->num, hwep->dir,
				hwep->type == USB_ENDPOINT_XFER_CONTROL);
पूर्ण

/**
 * _hardware_dequeue: handles a request at hardware level
 * @hwep: endpoपूर्णांक
 * @hwreq:  request
 *
 * This function वापसs an error code
 */
अटल पूर्णांक _hardware_dequeue(काष्ठा ci_hw_ep *hwep, काष्ठा ci_hw_req *hwreq)
अणु
	u32 पंचांगptoken;
	काष्ठा td_node *node, *पंचांगpnode;
	अचिन्हित reमुख्यing_length;
	अचिन्हित actual = hwreq->req.length;
	काष्ठा ci_hdrc *ci = hwep->ci;

	अगर (hwreq->req.status != -EALREADY)
		वापस -EINVAL;

	hwreq->req.status = 0;

	list_क्रम_each_entry_safe(node, पंचांगpnode, &hwreq->tds, td) अणु
		पंचांगptoken = le32_to_cpu(node->ptr->token);
		trace_ci_complete_td(hwep, hwreq, node);
		अगर ((TD_STATUS_ACTIVE & पंचांगptoken) != 0) अणु
			पूर्णांक n = hw_ep_bit(hwep->num, hwep->dir);

			अगर (ci->rev == CI_REVISION_24)
				अगर (!hw_पढ़ो(ci, OP_ENDPTSTAT, BIT(n)))
					reprime_dtd(ci, hwep, node);
			hwreq->req.status = -EALREADY;
			वापस -EBUSY;
		पूर्ण

		reमुख्यing_length = (पंचांगptoken & TD_TOTAL_BYTES);
		reमुख्यing_length >>= __ffs(TD_TOTAL_BYTES);
		actual -= reमुख्यing_length;

		hwreq->req.status = पंचांगptoken & TD_STATUS;
		अगर ((TD_STATUS_HALTED & hwreq->req.status)) अणु
			hwreq->req.status = -EPIPE;
			अवरोध;
		पूर्ण अन्यथा अगर ((TD_STATUS_DT_ERR & hwreq->req.status)) अणु
			hwreq->req.status = -EPROTO;
			अवरोध;
		पूर्ण अन्यथा अगर ((TD_STATUS_TR_ERR & hwreq->req.status)) अणु
			hwreq->req.status = -EILSEQ;
			अवरोध;
		पूर्ण

		अगर (reमुख्यing_length) अणु
			अगर (hwep->dir == TX) अणु
				hwreq->req.status = -EPROTO;
				अवरोध;
			पूर्ण
		पूर्ण
		/*
		 * As the hardware could still address the मुक्तd td
		 * which will run the udc unusable, the cleanup of the
		 * td has to be delayed by one.
		 */
		अगर (hwep->pending_td)
			मुक्त_pending_td(hwep);

		hwep->pending_td = node;
		list_del_init(&node->td);
	पूर्ण

	usb_gadget_unmap_request_by_dev(hwep->ci->dev->parent,
					&hwreq->req, hwep->dir);

	hwreq->req.actual += actual;

	अगर (hwreq->req.status)
		वापस hwreq->req.status;

	वापस hwreq->req.actual;
पूर्ण

/**
 * _ep_nuke: dequeues all endpoपूर्णांक requests
 * @hwep: endpoपूर्णांक
 *
 * This function वापसs an error code
 * Caller must hold lock
 */
अटल पूर्णांक _ep_nuke(काष्ठा ci_hw_ep *hwep)
__releases(hwep->lock)
__acquires(hwep->lock)
अणु
	काष्ठा td_node *node, *पंचांगpnode;
	अगर (hwep == शून्य)
		वापस -EINVAL;

	hw_ep_flush(hwep->ci, hwep->num, hwep->dir);

	जबतक (!list_empty(&hwep->qh.queue)) अणु

		/* pop oldest request */
		काष्ठा ci_hw_req *hwreq = list_entry(hwep->qh.queue.next,
						     काष्ठा ci_hw_req, queue);

		list_क्रम_each_entry_safe(node, पंचांगpnode, &hwreq->tds, td) अणु
			dma_pool_मुक्त(hwep->td_pool, node->ptr, node->dma);
			list_del_init(&node->td);
			node->ptr = शून्य;
			kमुक्त(node);
		पूर्ण

		list_del_init(&hwreq->queue);
		hwreq->req.status = -ESHUTDOWN;

		अगर (hwreq->req.complete != शून्य) अणु
			spin_unlock(hwep->lock);
			usb_gadget_giveback_request(&hwep->ep, &hwreq->req);
			spin_lock(hwep->lock);
		पूर्ण
	पूर्ण

	अगर (hwep->pending_td)
		मुक्त_pending_td(hwep);

	वापस 0;
पूर्ण

अटल पूर्णांक _ep_set_halt(काष्ठा usb_ep *ep, पूर्णांक value, bool check_transfer)
अणु
	काष्ठा ci_hw_ep *hwep = container_of(ep, काष्ठा ci_hw_ep, ep);
	पूर्णांक direction, retval = 0;
	अचिन्हित दीर्घ flags;

	अगर (ep == शून्य || hwep->ep.desc == शून्य)
		वापस -EINVAL;

	अगर (usb_endpoपूर्णांक_xfer_isoc(hwep->ep.desc))
		वापस -EOPNOTSUPP;

	spin_lock_irqsave(hwep->lock, flags);

	अगर (value && hwep->dir == TX && check_transfer &&
		!list_empty(&hwep->qh.queue) &&
			!usb_endpoपूर्णांक_xfer_control(hwep->ep.desc)) अणु
		spin_unlock_irqrestore(hwep->lock, flags);
		वापस -EAGAIN;
	पूर्ण

	direction = hwep->dir;
	करो अणु
		retval |= hw_ep_set_halt(hwep->ci, hwep->num, hwep->dir, value);

		अगर (!value)
			hwep->wedge = 0;

		अगर (hwep->type == USB_ENDPOINT_XFER_CONTROL)
			hwep->dir = (hwep->dir == TX) ? RX : TX;

	पूर्ण जबतक (hwep->dir != direction);

	spin_unlock_irqrestore(hwep->lock, flags);
	वापस retval;
पूर्ण


/**
 * _gadget_stop_activity: stops all USB activity, flushes & disables all endpts
 * @gadget: gadget
 *
 * This function वापसs an error code
 */
अटल पूर्णांक _gadget_stop_activity(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usb_ep *ep;
	काष्ठा ci_hdrc    *ci = container_of(gadget, काष्ठा ci_hdrc, gadget);
	अचिन्हित दीर्घ flags;

	/* flush all endpoपूर्णांकs */
	gadget_क्रम_each_ep(ep, gadget) अणु
		usb_ep_fअगरo_flush(ep);
	पूर्ण
	usb_ep_fअगरo_flush(&ci->ep0out->ep);
	usb_ep_fअगरo_flush(&ci->ep0in->ep);

	/* make sure to disable all endpoपूर्णांकs */
	gadget_क्रम_each_ep(ep, gadget) अणु
		usb_ep_disable(ep);
	पूर्ण

	अगर (ci->status != शून्य) अणु
		usb_ep_मुक्त_request(&ci->ep0in->ep, ci->status);
		ci->status = शून्य;
	पूर्ण

	spin_lock_irqsave(&ci->lock, flags);
	ci->gadget.speed = USB_SPEED_UNKNOWN;
	ci->remote_wakeup = 0;
	ci->suspended = 0;
	spin_unlock_irqrestore(&ci->lock, flags);

	वापस 0;
पूर्ण

/******************************************************************************
 * ISR block
 *****************************************************************************/
/**
 * isr_reset_handler: USB reset पूर्णांकerrupt handler
 * @ci: UDC device
 *
 * This function resets USB engine after a bus reset occurred
 */
अटल व्योम isr_reset_handler(काष्ठा ci_hdrc *ci)
__releases(ci->lock)
__acquires(ci->lock)
अणु
	पूर्णांक retval;

	spin_unlock(&ci->lock);
	अगर (ci->gadget.speed != USB_SPEED_UNKNOWN)
		usb_gadget_udc_reset(&ci->gadget, ci->driver);

	retval = _gadget_stop_activity(&ci->gadget);
	अगर (retval)
		जाओ करोne;

	retval = hw_usb_reset(ci);
	अगर (retval)
		जाओ करोne;

	ci->status = usb_ep_alloc_request(&ci->ep0in->ep, GFP_ATOMIC);
	अगर (ci->status == शून्य)
		retval = -ENOMEM;

करोne:
	spin_lock(&ci->lock);

	अगर (retval)
		dev_err(ci->dev, "error: %i\n", retval);
पूर्ण

/**
 * isr_get_status_complete: get_status request complete function
 * @ep:  endpoपूर्णांक
 * @req: request handled
 *
 * Caller must release lock
 */
अटल व्योम isr_get_status_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	अगर (ep == शून्य || req == शून्य)
		वापस;

	kमुक्त(req->buf);
	usb_ep_मुक्त_request(ep, req);
पूर्ण

/**
 * _ep_queue: queues (submits) an I/O request to an endpoपूर्णांक
 * @ep:        endpoपूर्णांक
 * @req:       request
 * @gfp_flags: GFP flags (not used)
 *
 * Caller must hold lock
 * This function वापसs an error code
 */
अटल पूर्णांक _ep_queue(काष्ठा usb_ep *ep, काष्ठा usb_request *req,
		    gfp_t __maybe_unused gfp_flags)
अणु
	काष्ठा ci_hw_ep  *hwep  = container_of(ep,  काष्ठा ci_hw_ep, ep);
	काष्ठा ci_hw_req *hwreq = container_of(req, काष्ठा ci_hw_req, req);
	काष्ठा ci_hdrc *ci = hwep->ci;
	पूर्णांक retval = 0;

	अगर (ep == शून्य || req == शून्य || hwep->ep.desc == शून्य)
		वापस -EINVAL;

	अगर (hwep->type == USB_ENDPOINT_XFER_CONTROL) अणु
		अगर (req->length)
			hwep = (ci->ep0_dir == RX) ?
			       ci->ep0out : ci->ep0in;
		अगर (!list_empty(&hwep->qh.queue)) अणु
			_ep_nuke(hwep);
			dev_warn(hwep->ci->dev, "endpoint ctrl %X nuked\n",
				 _usb_addr(hwep));
		पूर्ण
	पूर्ण

	अगर (usb_endpoपूर्णांक_xfer_isoc(hwep->ep.desc) &&
	    hwreq->req.length > hwep->ep.mult * hwep->ep.maxpacket) अणु
		dev_err(hwep->ci->dev, "request length too big for isochronous\n");
		वापस -EMSGSIZE;
	पूर्ण

	/* first nuke then test link, e.g. previous status has not sent */
	अगर (!list_empty(&hwreq->queue)) अणु
		dev_err(hwep->ci->dev, "request already in queue\n");
		वापस -EBUSY;
	पूर्ण

	/* push request */
	hwreq->req.status = -EINPROGRESS;
	hwreq->req.actual = 0;

	retval = _hardware_enqueue(hwep, hwreq);

	अगर (retval == -EALREADY)
		retval = 0;
	अगर (!retval)
		list_add_tail(&hwreq->queue, &hwep->qh.queue);

	वापस retval;
पूर्ण

/**
 * isr_get_status_response: get_status request response
 * @ci: ci काष्ठा
 * @setup: setup request packet
 *
 * This function वापसs an error code
 */
अटल पूर्णांक isr_get_status_response(काष्ठा ci_hdrc *ci,
				   काष्ठा usb_ctrlrequest *setup)
__releases(hwep->lock)
__acquires(hwep->lock)
अणु
	काष्ठा ci_hw_ep *hwep = ci->ep0in;
	काष्ठा usb_request *req = शून्य;
	gfp_t gfp_flags = GFP_ATOMIC;
	पूर्णांक dir, num, retval;

	अगर (hwep == शून्य || setup == शून्य)
		वापस -EINVAL;

	spin_unlock(hwep->lock);
	req = usb_ep_alloc_request(&hwep->ep, gfp_flags);
	spin_lock(hwep->lock);
	अगर (req == शून्य)
		वापस -ENOMEM;

	req->complete = isr_get_status_complete;
	req->length   = 2;
	req->buf      = kzalloc(req->length, gfp_flags);
	अगर (req->buf == शून्य) अणु
		retval = -ENOMEM;
		जाओ err_मुक्त_req;
	पूर्ण

	अगर ((setup->bRequestType & USB_RECIP_MASK) == USB_RECIP_DEVICE) अणु
		*(u16 *)req->buf = (ci->remote_wakeup << 1) |
			ci->gadget.is_selfघातered;
	पूर्ण अन्यथा अगर ((setup->bRequestType & USB_RECIP_MASK) \
		   == USB_RECIP_ENDPOINT) अणु
		dir = (le16_to_cpu(setup->wIndex) & USB_ENDPOINT_सूची_MASK) ?
			TX : RX;
		num =  le16_to_cpu(setup->wIndex) & USB_ENDPOINT_NUMBER_MASK;
		*(u16 *)req->buf = hw_ep_get_halt(ci, num, dir);
	पूर्ण
	/* अन्यथा करो nothing; reserved क्रम future use */

	retval = _ep_queue(&hwep->ep, req, gfp_flags);
	अगर (retval)
		जाओ err_मुक्त_buf;

	वापस 0;

 err_मुक्त_buf:
	kमुक्त(req->buf);
 err_मुक्त_req:
	spin_unlock(hwep->lock);
	usb_ep_मुक्त_request(&hwep->ep, req);
	spin_lock(hwep->lock);
	वापस retval;
पूर्ण

/**
 * isr_setup_status_complete: setup_status request complete function
 * @ep:  endpoपूर्णांक
 * @req: request handled
 *
 * Caller must release lock. Put the port in test mode अगर test mode
 * feature is selected.
 */
अटल व्योम
isr_setup_status_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा ci_hdrc *ci = req->context;
	अचिन्हित दीर्घ flags;

	अगर (ci->setaddr) अणु
		hw_usb_set_address(ci, ci->address);
		ci->setaddr = false;
		अगर (ci->address)
			usb_gadget_set_state(&ci->gadget, USB_STATE_ADDRESS);
	पूर्ण

	spin_lock_irqsave(&ci->lock, flags);
	अगर (ci->test_mode)
		hw_port_test_set(ci, ci->test_mode);
	spin_unlock_irqrestore(&ci->lock, flags);
पूर्ण

/**
 * isr_setup_status_phase: queues the status phase of a setup transation
 * @ci: ci काष्ठा
 *
 * This function वापसs an error code
 */
अटल पूर्णांक isr_setup_status_phase(काष्ठा ci_hdrc *ci)
अणु
	काष्ठा ci_hw_ep *hwep;

	/*
	 * Unexpected USB controller behavior, caused by bad संकेत पूर्णांकegrity
	 * or ground reference problems, can lead to isr_setup_status_phase
	 * being called with ci->status equal to शून्य.
	 * If this situation occurs, you should review your USB hardware design.
	 */
	अगर (WARN_ON_ONCE(!ci->status))
		वापस -EPIPE;

	hwep = (ci->ep0_dir == TX) ? ci->ep0out : ci->ep0in;
	ci->status->context = ci;
	ci->status->complete = isr_setup_status_complete;

	वापस _ep_queue(&hwep->ep, ci->status, GFP_ATOMIC);
पूर्ण

/**
 * isr_tr_complete_low: transaction complete low level handler
 * @hwep: endpoपूर्णांक
 *
 * This function वापसs an error code
 * Caller must hold lock
 */
अटल पूर्णांक isr_tr_complete_low(काष्ठा ci_hw_ep *hwep)
__releases(hwep->lock)
__acquires(hwep->lock)
अणु
	काष्ठा ci_hw_req *hwreq, *hwreqtemp;
	काष्ठा ci_hw_ep *hweptemp = hwep;
	पूर्णांक retval = 0;

	list_क्रम_each_entry_safe(hwreq, hwreqtemp, &hwep->qh.queue,
			queue) अणु
		retval = _hardware_dequeue(hwep, hwreq);
		अगर (retval < 0)
			अवरोध;
		list_del_init(&hwreq->queue);
		अगर (hwreq->req.complete != शून्य) अणु
			spin_unlock(hwep->lock);
			अगर ((hwep->type == USB_ENDPOINT_XFER_CONTROL) &&
					hwreq->req.length)
				hweptemp = hwep->ci->ep0in;
			usb_gadget_giveback_request(&hweptemp->ep, &hwreq->req);
			spin_lock(hwep->lock);
		पूर्ण
	पूर्ण

	अगर (retval == -EBUSY)
		retval = 0;

	वापस retval;
पूर्ण

अटल पूर्णांक otg_a_alt_hnp_support(काष्ठा ci_hdrc *ci)
अणु
	dev_warn(&ci->gadget.dev,
		"connect the device to an alternate port if you want HNP\n");
	वापस isr_setup_status_phase(ci);
पूर्ण

/**
 * isr_setup_packet_handler: setup packet handler
 * @ci: UDC descriptor
 *
 * This function handles setup packet 
 */
अटल व्योम isr_setup_packet_handler(काष्ठा ci_hdrc *ci)
__releases(ci->lock)
__acquires(ci->lock)
अणु
	काष्ठा ci_hw_ep *hwep = &ci->ci_hw_ep[0];
	काष्ठा usb_ctrlrequest req;
	पूर्णांक type, num, dir, err = -EINVAL;
	u8 पंचांगode = 0;

	/*
	 * Flush data and handshake transactions of previous
	 * setup packet.
	 */
	_ep_nuke(ci->ep0out);
	_ep_nuke(ci->ep0in);

	/* पढ़ो_setup_packet */
	करो अणु
		hw_test_and_set_setup_guard(ci);
		स_नकल(&req, &hwep->qh.ptr->setup, माप(req));
	पूर्ण जबतक (!hw_test_and_clear_setup_guard(ci));

	type = req.bRequestType;

	ci->ep0_dir = (type & USB_सूची_IN) ? TX : RX;

	चयन (req.bRequest) अणु
	हाल USB_REQ_CLEAR_FEATURE:
		अगर (type == (USB_सूची_OUT|USB_RECIP_ENDPOINT) &&
				le16_to_cpu(req.wValue) ==
				USB_ENDPOINT_HALT) अणु
			अगर (req.wLength != 0)
				अवरोध;
			num  = le16_to_cpu(req.wIndex);
			dir = (num & USB_ENDPOINT_सूची_MASK) ? TX : RX;
			num &= USB_ENDPOINT_NUMBER_MASK;
			अगर (dir == TX)
				num += ci->hw_ep_max / 2;
			अगर (!ci->ci_hw_ep[num].wedge) अणु
				spin_unlock(&ci->lock);
				err = usb_ep_clear_halt(
					&ci->ci_hw_ep[num].ep);
				spin_lock(&ci->lock);
				अगर (err)
					अवरोध;
			पूर्ण
			err = isr_setup_status_phase(ci);
		पूर्ण अन्यथा अगर (type == (USB_सूची_OUT|USB_RECIP_DEVICE) &&
				le16_to_cpu(req.wValue) ==
				USB_DEVICE_REMOTE_WAKEUP) अणु
			अगर (req.wLength != 0)
				अवरोध;
			ci->remote_wakeup = 0;
			err = isr_setup_status_phase(ci);
		पूर्ण अन्यथा अणु
			जाओ delegate;
		पूर्ण
		अवरोध;
	हाल USB_REQ_GET_STATUS:
		अगर ((type != (USB_सूची_IN|USB_RECIP_DEVICE) ||
			le16_to_cpu(req.wIndex) == OTG_STS_SELECTOR) &&
		    type != (USB_सूची_IN|USB_RECIP_ENDPOINT) &&
		    type != (USB_सूची_IN|USB_RECIP_INTERFACE))
			जाओ delegate;
		अगर (le16_to_cpu(req.wLength) != 2 ||
		    le16_to_cpu(req.wValue)  != 0)
			अवरोध;
		err = isr_get_status_response(ci, &req);
		अवरोध;
	हाल USB_REQ_SET_ADDRESS:
		अगर (type != (USB_सूची_OUT|USB_RECIP_DEVICE))
			जाओ delegate;
		अगर (le16_to_cpu(req.wLength) != 0 ||
		    le16_to_cpu(req.wIndex)  != 0)
			अवरोध;
		ci->address = (u8)le16_to_cpu(req.wValue);
		ci->setaddr = true;
		err = isr_setup_status_phase(ci);
		अवरोध;
	हाल USB_REQ_SET_FEATURE:
		अगर (type == (USB_सूची_OUT|USB_RECIP_ENDPOINT) &&
				le16_to_cpu(req.wValue) ==
				USB_ENDPOINT_HALT) अणु
			अगर (req.wLength != 0)
				अवरोध;
			num  = le16_to_cpu(req.wIndex);
			dir = (num & USB_ENDPOINT_सूची_MASK) ? TX : RX;
			num &= USB_ENDPOINT_NUMBER_MASK;
			अगर (dir == TX)
				num += ci->hw_ep_max / 2;

			spin_unlock(&ci->lock);
			err = _ep_set_halt(&ci->ci_hw_ep[num].ep, 1, false);
			spin_lock(&ci->lock);
			अगर (!err)
				isr_setup_status_phase(ci);
		पूर्ण अन्यथा अगर (type == (USB_सूची_OUT|USB_RECIP_DEVICE)) अणु
			अगर (req.wLength != 0)
				अवरोध;
			चयन (le16_to_cpu(req.wValue)) अणु
			हाल USB_DEVICE_REMOTE_WAKEUP:
				ci->remote_wakeup = 1;
				err = isr_setup_status_phase(ci);
				अवरोध;
			हाल USB_DEVICE_TEST_MODE:
				पंचांगode = le16_to_cpu(req.wIndex) >> 8;
				चयन (पंचांगode) अणु
				हाल USB_TEST_J:
				हाल USB_TEST_K:
				हाल USB_TEST_SE0_NAK:
				हाल USB_TEST_PACKET:
				हाल USB_TEST_FORCE_ENABLE:
					ci->test_mode = पंचांगode;
					err = isr_setup_status_phase(
							ci);
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
				अवरोध;
			हाल USB_DEVICE_B_HNP_ENABLE:
				अगर (ci_otg_is_fsm_mode(ci)) अणु
					ci->gadget.b_hnp_enable = 1;
					err = isr_setup_status_phase(
							ci);
				पूर्ण
				अवरोध;
			हाल USB_DEVICE_A_ALT_HNP_SUPPORT:
				अगर (ci_otg_is_fsm_mode(ci))
					err = otg_a_alt_hnp_support(ci);
				अवरोध;
			हाल USB_DEVICE_A_HNP_SUPPORT:
				अगर (ci_otg_is_fsm_mode(ci)) अणु
					ci->gadget.a_hnp_support = 1;
					err = isr_setup_status_phase(
							ci);
				पूर्ण
				अवरोध;
			शेष:
				जाओ delegate;
			पूर्ण
		पूर्ण अन्यथा अणु
			जाओ delegate;
		पूर्ण
		अवरोध;
	शेष:
delegate:
		अगर (req.wLength == 0)   /* no data phase */
			ci->ep0_dir = TX;

		spin_unlock(&ci->lock);
		err = ci->driver->setup(&ci->gadget, &req);
		spin_lock(&ci->lock);
		अवरोध;
	पूर्ण

	अगर (err < 0) अणु
		spin_unlock(&ci->lock);
		अगर (_ep_set_halt(&hwep->ep, 1, false))
			dev_err(ci->dev, "error: _ep_set_halt\n");
		spin_lock(&ci->lock);
	पूर्ण
पूर्ण

/**
 * isr_tr_complete_handler: transaction complete पूर्णांकerrupt handler
 * @ci: UDC descriptor
 *
 * This function handles traffic events
 */
अटल व्योम isr_tr_complete_handler(काष्ठा ci_hdrc *ci)
__releases(ci->lock)
__acquires(ci->lock)
अणु
	अचिन्हित i;
	पूर्णांक err;

	क्रम (i = 0; i < ci->hw_ep_max; i++) अणु
		काष्ठा ci_hw_ep *hwep  = &ci->ci_hw_ep[i];

		अगर (hwep->ep.desc == शून्य)
			जारी;   /* not configured */

		अगर (hw_test_and_clear_complete(ci, i)) अणु
			err = isr_tr_complete_low(hwep);
			अगर (hwep->type == USB_ENDPOINT_XFER_CONTROL) अणु
				अगर (err > 0)   /* needs status phase */
					err = isr_setup_status_phase(ci);
				अगर (err < 0) अणु
					spin_unlock(&ci->lock);
					अगर (_ep_set_halt(&hwep->ep, 1, false))
						dev_err(ci->dev,
						"error: _ep_set_halt\n");
					spin_lock(&ci->lock);
				पूर्ण
			पूर्ण
		पूर्ण

		/* Only handle setup packet below */
		अगर (i == 0 &&
			hw_test_and_clear(ci, OP_ENDPTSETUPSTAT, BIT(0)))
			isr_setup_packet_handler(ci);
	पूर्ण
पूर्ण

/******************************************************************************
 * ENDPT block
 *****************************************************************************/
/*
 * ep_enable: configure endpoपूर्णांक, making it usable
 *
 * Check usb_ep_enable() at "usb_gadget.h" क्रम details
 */
अटल पूर्णांक ep_enable(काष्ठा usb_ep *ep,
		     स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा ci_hw_ep *hwep = container_of(ep, काष्ठा ci_hw_ep, ep);
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ flags;
	u32 cap = 0;

	अगर (ep == शून्य || desc == शून्य)
		वापस -EINVAL;

	spin_lock_irqsave(hwep->lock, flags);

	/* only पूर्णांकernal SW should enable ctrl endpts */

	अगर (!list_empty(&hwep->qh.queue)) अणु
		dev_warn(hwep->ci->dev, "enabling a non-empty endpoint!\n");
		spin_unlock_irqrestore(hwep->lock, flags);
		वापस -EBUSY;
	पूर्ण

	hwep->ep.desc = desc;

	hwep->dir  = usb_endpoपूर्णांक_dir_in(desc) ? TX : RX;
	hwep->num  = usb_endpoपूर्णांक_num(desc);
	hwep->type = usb_endpoपूर्णांक_type(desc);

	hwep->ep.maxpacket = usb_endpoपूर्णांक_maxp(desc);
	hwep->ep.mult = usb_endpoपूर्णांक_maxp_mult(desc);

	अगर (hwep->type == USB_ENDPOINT_XFER_CONTROL)
		cap |= QH_IOS;

	cap |= QH_ZLT;
	cap |= (hwep->ep.maxpacket << __ffs(QH_MAX_PKT)) & QH_MAX_PKT;
	/*
	 * For ISO-TX, we set mult at QH as the largest value, and use
	 * MultO at TD as real mult value.
	 */
	अगर (hwep->type == USB_ENDPOINT_XFER_ISOC && hwep->dir == TX)
		cap |= 3 << __ffs(QH_MULT);

	hwep->qh.ptr->cap = cpu_to_le32(cap);

	hwep->qh.ptr->td.next |= cpu_to_le32(TD_TERMINATE);   /* needed? */

	अगर (hwep->num != 0 && hwep->type == USB_ENDPOINT_XFER_CONTROL) अणु
		dev_err(hwep->ci->dev, "Set control xfer at non-ep0\n");
		retval = -EINVAL;
	पूर्ण

	/*
	 * Enable endpoपूर्णांकs in the HW other than ep0 as ep0
	 * is always enabled
	 */
	अगर (hwep->num)
		retval |= hw_ep_enable(hwep->ci, hwep->num, hwep->dir,
				       hwep->type);

	spin_unlock_irqrestore(hwep->lock, flags);
	वापस retval;
पूर्ण

/*
 * ep_disable: endpoपूर्णांक is no दीर्घer usable
 *
 * Check usb_ep_disable() at "usb_gadget.h" क्रम details
 */
अटल पूर्णांक ep_disable(काष्ठा usb_ep *ep)
अणु
	काष्ठा ci_hw_ep *hwep = container_of(ep, काष्ठा ci_hw_ep, ep);
	पूर्णांक direction, retval = 0;
	अचिन्हित दीर्घ flags;

	अगर (ep == शून्य)
		वापस -EINVAL;
	अन्यथा अगर (hwep->ep.desc == शून्य)
		वापस -EBUSY;

	spin_lock_irqsave(hwep->lock, flags);
	अगर (hwep->ci->gadget.speed == USB_SPEED_UNKNOWN) अणु
		spin_unlock_irqrestore(hwep->lock, flags);
		वापस 0;
	पूर्ण

	/* only पूर्णांकernal SW should disable ctrl endpts */

	direction = hwep->dir;
	करो अणु
		retval |= _ep_nuke(hwep);
		retval |= hw_ep_disable(hwep->ci, hwep->num, hwep->dir);

		अगर (hwep->type == USB_ENDPOINT_XFER_CONTROL)
			hwep->dir = (hwep->dir == TX) ? RX : TX;

	पूर्ण जबतक (hwep->dir != direction);

	hwep->ep.desc = शून्य;

	spin_unlock_irqrestore(hwep->lock, flags);
	वापस retval;
पूर्ण

/*
 * ep_alloc_request: allocate a request object to use with this endpoपूर्णांक
 *
 * Check usb_ep_alloc_request() at "usb_gadget.h" क्रम details
 */
अटल काष्ठा usb_request *ep_alloc_request(काष्ठा usb_ep *ep, gfp_t gfp_flags)
अणु
	काष्ठा ci_hw_req *hwreq = शून्य;

	अगर (ep == शून्य)
		वापस शून्य;

	hwreq = kzalloc(माप(काष्ठा ci_hw_req), gfp_flags);
	अगर (hwreq != शून्य) अणु
		INIT_LIST_HEAD(&hwreq->queue);
		INIT_LIST_HEAD(&hwreq->tds);
	पूर्ण

	वापस (hwreq == शून्य) ? शून्य : &hwreq->req;
पूर्ण

/*
 * ep_मुक्त_request: मुक्तs a request object
 *
 * Check usb_ep_मुक्त_request() at "usb_gadget.h" क्रम details
 */
अटल व्योम ep_मुक्त_request(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा ci_hw_ep  *hwep  = container_of(ep,  काष्ठा ci_hw_ep, ep);
	काष्ठा ci_hw_req *hwreq = container_of(req, काष्ठा ci_hw_req, req);
	काष्ठा td_node *node, *पंचांगpnode;
	अचिन्हित दीर्घ flags;

	अगर (ep == शून्य || req == शून्य) अणु
		वापस;
	पूर्ण अन्यथा अगर (!list_empty(&hwreq->queue)) अणु
		dev_err(hwep->ci->dev, "freeing queued request\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(hwep->lock, flags);

	list_क्रम_each_entry_safe(node, पंचांगpnode, &hwreq->tds, td) अणु
		dma_pool_मुक्त(hwep->td_pool, node->ptr, node->dma);
		list_del_init(&node->td);
		node->ptr = शून्य;
		kमुक्त(node);
	पूर्ण

	kमुक्त(hwreq);

	spin_unlock_irqrestore(hwep->lock, flags);
पूर्ण

/*
 * ep_queue: queues (submits) an I/O request to an endpoपूर्णांक
 *
 * Check usb_ep_queue()* at usb_gadget.h" क्रम details
 */
अटल पूर्णांक ep_queue(काष्ठा usb_ep *ep, काष्ठा usb_request *req,
		    gfp_t __maybe_unused gfp_flags)
अणु
	काष्ठा ci_hw_ep  *hwep  = container_of(ep,  काष्ठा ci_hw_ep, ep);
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ flags;

	अगर (ep == शून्य || req == शून्य || hwep->ep.desc == शून्य)
		वापस -EINVAL;

	spin_lock_irqsave(hwep->lock, flags);
	अगर (hwep->ci->gadget.speed == USB_SPEED_UNKNOWN) अणु
		spin_unlock_irqrestore(hwep->lock, flags);
		वापस 0;
	पूर्ण
	retval = _ep_queue(ep, req, gfp_flags);
	spin_unlock_irqrestore(hwep->lock, flags);
	वापस retval;
पूर्ण

/*
 * ep_dequeue: dequeues (cancels, unlinks) an I/O request from an endpoपूर्णांक
 *
 * Check usb_ep_dequeue() at "usb_gadget.h" क्रम details
 */
अटल पूर्णांक ep_dequeue(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा ci_hw_ep  *hwep  = container_of(ep,  काष्ठा ci_hw_ep, ep);
	काष्ठा ci_hw_req *hwreq = container_of(req, काष्ठा ci_hw_req, req);
	अचिन्हित दीर्घ flags;
	काष्ठा td_node *node, *पंचांगpnode;

	अगर (ep == शून्य || req == शून्य || hwreq->req.status != -EALREADY ||
		hwep->ep.desc == शून्य || list_empty(&hwreq->queue) ||
		list_empty(&hwep->qh.queue))
		वापस -EINVAL;

	spin_lock_irqsave(hwep->lock, flags);
	अगर (hwep->ci->gadget.speed != USB_SPEED_UNKNOWN)
		hw_ep_flush(hwep->ci, hwep->num, hwep->dir);

	list_क्रम_each_entry_safe(node, पंचांगpnode, &hwreq->tds, td) अणु
		dma_pool_मुक्त(hwep->td_pool, node->ptr, node->dma);
		list_del(&node->td);
		kमुक्त(node);
	पूर्ण

	/* pop request */
	list_del_init(&hwreq->queue);

	usb_gadget_unmap_request(&hwep->ci->gadget, req, hwep->dir);

	req->status = -ECONNRESET;

	अगर (hwreq->req.complete != शून्य) अणु
		spin_unlock(hwep->lock);
		usb_gadget_giveback_request(&hwep->ep, &hwreq->req);
		spin_lock(hwep->lock);
	पूर्ण

	spin_unlock_irqrestore(hwep->lock, flags);
	वापस 0;
पूर्ण

/*
 * ep_set_halt: sets the endpoपूर्णांक halt feature
 *
 * Check usb_ep_set_halt() at "usb_gadget.h" क्रम details
 */
अटल पूर्णांक ep_set_halt(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	वापस _ep_set_halt(ep, value, true);
पूर्ण

/*
 * ep_set_wedge: sets the halt feature and ignores clear requests
 *
 * Check usb_ep_set_wedge() at "usb_gadget.h" क्रम details
 */
अटल पूर्णांक ep_set_wedge(काष्ठा usb_ep *ep)
अणु
	काष्ठा ci_hw_ep *hwep = container_of(ep, काष्ठा ci_hw_ep, ep);
	अचिन्हित दीर्घ flags;

	अगर (ep == शून्य || hwep->ep.desc == शून्य)
		वापस -EINVAL;

	spin_lock_irqsave(hwep->lock, flags);
	hwep->wedge = 1;
	spin_unlock_irqrestore(hwep->lock, flags);

	वापस usb_ep_set_halt(ep);
पूर्ण

/*
 * ep_fअगरo_flush: flushes contents of a fअगरo
 *
 * Check usb_ep_fअगरo_flush() at "usb_gadget.h" क्रम details
 */
अटल व्योम ep_fअगरo_flush(काष्ठा usb_ep *ep)
अणु
	काष्ठा ci_hw_ep *hwep = container_of(ep, काष्ठा ci_hw_ep, ep);
	अचिन्हित दीर्घ flags;

	अगर (ep == शून्य) अणु
		dev_err(hwep->ci->dev, "%02X: -EINVAL\n", _usb_addr(hwep));
		वापस;
	पूर्ण

	spin_lock_irqsave(hwep->lock, flags);
	अगर (hwep->ci->gadget.speed == USB_SPEED_UNKNOWN) अणु
		spin_unlock_irqrestore(hwep->lock, flags);
		वापस;
	पूर्ण

	hw_ep_flush(hwep->ci, hwep->num, hwep->dir);

	spin_unlock_irqrestore(hwep->lock, flags);
पूर्ण

/*
 * Endpoपूर्णांक-specअगरic part of the API to the USB controller hardware
 * Check "usb_gadget.h" क्रम details
 */
अटल स्थिर काष्ठा usb_ep_ops usb_ep_ops = अणु
	.enable	       = ep_enable,
	.disable       = ep_disable,
	.alloc_request = ep_alloc_request,
	.मुक्त_request  = ep_मुक्त_request,
	.queue	       = ep_queue,
	.dequeue       = ep_dequeue,
	.set_halt      = ep_set_halt,
	.set_wedge     = ep_set_wedge,
	.fअगरo_flush    = ep_fअगरo_flush,
पूर्ण;

/******************************************************************************
 * GADGET block
 *****************************************************************************/
/*
 * ci_hdrc_gadget_connect: caller makes sure gadget driver is binded
 */
अटल व्योम ci_hdrc_gadget_connect(काष्ठा usb_gadget *_gadget, पूर्णांक is_active)
अणु
	काष्ठा ci_hdrc *ci = container_of(_gadget, काष्ठा ci_hdrc, gadget);

	अगर (is_active) अणु
		pm_runसमय_get_sync(ci->dev);
		hw_device_reset(ci);
		spin_lock_irq(&ci->lock);
		अगर (ci->driver) अणु
			hw_device_state(ci, ci->ep0out->qh.dma);
			usb_gadget_set_state(_gadget, USB_STATE_POWERED);
			spin_unlock_irq(&ci->lock);
			usb_udc_vbus_handler(_gadget, true);
		पूर्ण अन्यथा अणु
			spin_unlock_irq(&ci->lock);
		पूर्ण
	पूर्ण अन्यथा अणु
		usb_udc_vbus_handler(_gadget, false);
		अगर (ci->driver)
			ci->driver->disconnect(&ci->gadget);
		hw_device_state(ci, 0);
		अगर (ci->platdata->notअगरy_event)
			ci->platdata->notअगरy_event(ci,
			CI_HDRC_CONTROLLER_STOPPED_EVENT);
		_gadget_stop_activity(&ci->gadget);
		pm_runसमय_put_sync(ci->dev);
		usb_gadget_set_state(_gadget, USB_STATE_NOTATTACHED);
	पूर्ण
पूर्ण

अटल पूर्णांक ci_udc_vbus_session(काष्ठा usb_gadget *_gadget, पूर्णांक is_active)
अणु
	काष्ठा ci_hdrc *ci = container_of(_gadget, काष्ठा ci_hdrc, gadget);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&ci->lock, flags);
	ci->vbus_active = is_active;
	spin_unlock_irqrestore(&ci->lock, flags);

	अगर (ci->usb_phy)
		usb_phy_set_अक्षरger_state(ci->usb_phy, is_active ?
			USB_CHARGER_PRESENT : USB_CHARGER_ABSENT);

	अगर (ci->platdata->notअगरy_event)
		ret = ci->platdata->notअगरy_event(ci,
				CI_HDRC_CONTROLLER_VBUS_EVENT);

	अगर (ci->driver)
		ci_hdrc_gadget_connect(_gadget, is_active);

	वापस ret;
पूर्ण

अटल पूर्णांक ci_udc_wakeup(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा ci_hdrc *ci = container_of(_gadget, काष्ठा ci_hdrc, gadget);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&ci->lock, flags);
	अगर (ci->gadget.speed == USB_SPEED_UNKNOWN) अणु
		spin_unlock_irqrestore(&ci->lock, flags);
		वापस 0;
	पूर्ण
	अगर (!ci->remote_wakeup) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	अगर (!hw_पढ़ो(ci, OP_PORTSC, PORTSC_SUSP)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	hw_ग_लिखो(ci, OP_PORTSC, PORTSC_FPR, PORTSC_FPR);
out:
	spin_unlock_irqrestore(&ci->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक ci_udc_vbus_draw(काष्ठा usb_gadget *_gadget, अचिन्हित ma)
अणु
	काष्ठा ci_hdrc *ci = container_of(_gadget, काष्ठा ci_hdrc, gadget);

	अगर (ci->usb_phy)
		वापस usb_phy_set_घातer(ci->usb_phy, ma);
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक ci_udc_selfघातered(काष्ठा usb_gadget *_gadget, पूर्णांक is_on)
अणु
	काष्ठा ci_hdrc *ci = container_of(_gadget, काष्ठा ci_hdrc, gadget);
	काष्ठा ci_hw_ep *hwep = ci->ep0in;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(hwep->lock, flags);
	_gadget->is_selfघातered = (is_on != 0);
	spin_unlock_irqrestore(hwep->lock, flags);

	वापस 0;
पूर्ण

/* Change Data+ pullup status
 * this func is used by usb_gadget_connect/disconnect
 */
अटल पूर्णांक ci_udc_pullup(काष्ठा usb_gadget *_gadget, पूर्णांक is_on)
अणु
	काष्ठा ci_hdrc *ci = container_of(_gadget, काष्ठा ci_hdrc, gadget);

	/*
	 * Data+ pullup controlled by OTG state machine in OTG fsm mode;
	 * and करोn't touch Data+ in host mode क्रम dual role config.
	 */
	अगर (ci_otg_is_fsm_mode(ci) || ci->role == CI_ROLE_HOST)
		वापस 0;

	pm_runसमय_get_sync(ci->dev);
	अगर (is_on)
		hw_ग_लिखो(ci, OP_USBCMD, USBCMD_RS, USBCMD_RS);
	अन्यथा
		hw_ग_लिखो(ci, OP_USBCMD, USBCMD_RS, 0);
	pm_runसमय_put_sync(ci->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ci_udc_start(काष्ठा usb_gadget *gadget,
			 काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक ci_udc_stop(काष्ठा usb_gadget *gadget);

/* Match ISOC IN from the highest endpoपूर्णांक */
अटल काष्ठा usb_ep *ci_udc_match_ep(काष्ठा usb_gadget *gadget,
			      काष्ठा usb_endpoपूर्णांक_descriptor *desc,
			      काष्ठा usb_ss_ep_comp_descriptor *comp_desc)
अणु
	काष्ठा ci_hdrc *ci = container_of(gadget, काष्ठा ci_hdrc, gadget);
	काष्ठा usb_ep *ep;

	अगर (usb_endpoपूर्णांक_xfer_isoc(desc) && usb_endpoपूर्णांक_dir_in(desc)) अणु
		list_क्रम_each_entry_reverse(ep, &ci->gadget.ep_list, ep_list) अणु
			अगर (ep->caps.dir_in && !ep->claimed)
				वापस ep;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Device operations part of the API to the USB controller hardware,
 * which करोn't involve endpoपूर्णांकs (or i/o)
 * Check  "usb_gadget.h" क्रम details
 */
अटल स्थिर काष्ठा usb_gadget_ops usb_gadget_ops = अणु
	.vbus_session	= ci_udc_vbus_session,
	.wakeup		= ci_udc_wakeup,
	.set_selfघातered	= ci_udc_selfघातered,
	.pullup		= ci_udc_pullup,
	.vbus_draw	= ci_udc_vbus_draw,
	.udc_start	= ci_udc_start,
	.udc_stop	= ci_udc_stop,
	.match_ep 	= ci_udc_match_ep,
पूर्ण;

अटल पूर्णांक init_eps(काष्ठा ci_hdrc *ci)
अणु
	पूर्णांक retval = 0, i, j;

	क्रम (i = 0; i < ci->hw_ep_max/2; i++)
		क्रम (j = RX; j <= TX; j++) अणु
			पूर्णांक k = i + j * ci->hw_ep_max/2;
			काष्ठा ci_hw_ep *hwep = &ci->ci_hw_ep[k];

			scnम_लिखो(hwep->name, माप(hwep->name), "ep%i%s", i,
					(j == TX)  ? "in" : "out");

			hwep->ci          = ci;
			hwep->lock         = &ci->lock;
			hwep->td_pool      = ci->td_pool;

			hwep->ep.name      = hwep->name;
			hwep->ep.ops       = &usb_ep_ops;

			अगर (i == 0) अणु
				hwep->ep.caps.type_control = true;
			पूर्ण अन्यथा अणु
				hwep->ep.caps.type_iso = true;
				hwep->ep.caps.type_bulk = true;
				hwep->ep.caps.type_पूर्णांक = true;
			पूर्ण

			अगर (j == TX)
				hwep->ep.caps.dir_in = true;
			अन्यथा
				hwep->ep.caps.dir_out = true;

			/*
			 * क्रम ep0: maxP defined in desc, क्रम other
			 * eps, maxP is set by epस्वतःconfig() called
			 * by gadget layer
			 */
			usb_ep_set_maxpacket_limit(&hwep->ep, (अचिन्हित लघु)~0);

			INIT_LIST_HEAD(&hwep->qh.queue);
			hwep->qh.ptr = dma_pool_zalloc(ci->qh_pool, GFP_KERNEL,
						       &hwep->qh.dma);
			अगर (hwep->qh.ptr == शून्य)
				retval = -ENOMEM;

			/*
			 * set up लघुhands क्रम ep0 out and in endpoपूर्णांकs,
			 * करोn't add to gadget's ep_list
			 */
			अगर (i == 0) अणु
				अगर (j == RX)
					ci->ep0out = hwep;
				अन्यथा
					ci->ep0in = hwep;

				usb_ep_set_maxpacket_limit(&hwep->ep, CTRL_PAYLOAD_MAX);
				जारी;
			पूर्ण

			list_add_tail(&hwep->ep.ep_list, &ci->gadget.ep_list);
		पूर्ण

	वापस retval;
पूर्ण

अटल व्योम destroy_eps(काष्ठा ci_hdrc *ci)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ci->hw_ep_max; i++) अणु
		काष्ठा ci_hw_ep *hwep = &ci->ci_hw_ep[i];

		अगर (hwep->pending_td)
			मुक्त_pending_td(hwep);
		dma_pool_मुक्त(ci->qh_pool, hwep->qh.ptr, hwep->qh.dma);
	पूर्ण
पूर्ण

/**
 * ci_udc_start: रेजिस्टर a gadget driver
 * @gadget: our gadget
 * @driver: the driver being रेजिस्टरed
 *
 * Interrupts are enabled here.
 */
अटल पूर्णांक ci_udc_start(काष्ठा usb_gadget *gadget,
			 काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा ci_hdrc *ci = container_of(gadget, काष्ठा ci_hdrc, gadget);
	पूर्णांक retval;

	अगर (driver->disconnect == शून्य)
		वापस -EINVAL;

	ci->ep0out->ep.desc = &ctrl_endpt_out_desc;
	retval = usb_ep_enable(&ci->ep0out->ep);
	अगर (retval)
		वापस retval;

	ci->ep0in->ep.desc = &ctrl_endpt_in_desc;
	retval = usb_ep_enable(&ci->ep0in->ep);
	अगर (retval)
		वापस retval;

	ci->driver = driver;

	/* Start otg fsm क्रम B-device */
	अगर (ci_otg_is_fsm_mode(ci) && ci->fsm.id) अणु
		ci_hdrc_otg_fsm_start(ci);
		वापस retval;
	पूर्ण

	अगर (ci->vbus_active)
		ci_hdrc_gadget_connect(gadget, 1);
	अन्यथा
		usb_udc_vbus_handler(&ci->gadget, false);

	वापस retval;
पूर्ण

अटल व्योम ci_udc_stop_क्रम_otg_fsm(काष्ठा ci_hdrc *ci)
अणु
	अगर (!ci_otg_is_fsm_mode(ci))
		वापस;

	mutex_lock(&ci->fsm.lock);
	अगर (ci->fsm.otg->state == OTG_STATE_A_PERIPHERAL) अणु
		ci->fsm.a_bidl_adis_पंचांगout = 1;
		ci_hdrc_otg_fsm_start(ci);
	पूर्ण अन्यथा अगर (ci->fsm.otg->state == OTG_STATE_B_PERIPHERAL) अणु
		ci->fsm.protocol = PROTO_UNDEF;
		ci->fsm.otg->state = OTG_STATE_UNDEFINED;
	पूर्ण
	mutex_unlock(&ci->fsm.lock);
पूर्ण

/*
 * ci_udc_stop: unरेजिस्टर a gadget driver
 */
अटल पूर्णांक ci_udc_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा ci_hdrc *ci = container_of(gadget, काष्ठा ci_hdrc, gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ci->lock, flags);
	ci->driver = शून्य;

	अगर (ci->vbus_active) अणु
		hw_device_state(ci, 0);
		spin_unlock_irqrestore(&ci->lock, flags);
		अगर (ci->platdata->notअगरy_event)
			ci->platdata->notअगरy_event(ci,
			CI_HDRC_CONTROLLER_STOPPED_EVENT);
		_gadget_stop_activity(&ci->gadget);
		spin_lock_irqsave(&ci->lock, flags);
		pm_runसमय_put(ci->dev);
	पूर्ण

	spin_unlock_irqrestore(&ci->lock, flags);

	ci_udc_stop_क्रम_otg_fsm(ci);
	वापस 0;
पूर्ण

/******************************************************************************
 * BUS block
 *****************************************************************************/
/*
 * udc_irq: ci पूर्णांकerrupt handler
 *
 * This function वापसs IRQ_HANDLED अगर the IRQ has been handled
 * It locks access to रेजिस्टरs
 */
अटल irqवापस_t udc_irq(काष्ठा ci_hdrc *ci)
अणु
	irqवापस_t retval;
	u32 पूर्णांकr;

	अगर (ci == शून्य)
		वापस IRQ_HANDLED;

	spin_lock(&ci->lock);

	अगर (ci->platdata->flags & CI_HDRC_REGS_SHARED) अणु
		अगर (hw_पढ़ो(ci, OP_USBMODE, USBMODE_CM) !=
				USBMODE_CM_DC) अणु
			spin_unlock(&ci->lock);
			वापस IRQ_NONE;
		पूर्ण
	पूर्ण
	पूर्णांकr = hw_test_and_clear_पूर्णांकr_active(ci);

	अगर (पूर्णांकr) अणु
		/* order defines priority - करो NOT change it */
		अगर (USBi_URI & पूर्णांकr)
			isr_reset_handler(ci);

		अगर (USBi_PCI & पूर्णांकr) अणु
			ci->gadget.speed = hw_port_is_high_speed(ci) ?
				USB_SPEED_HIGH : USB_SPEED_FULL;
			अगर (ci->suspended) अणु
				अगर (ci->driver->resume) अणु
					spin_unlock(&ci->lock);
					ci->driver->resume(&ci->gadget);
					spin_lock(&ci->lock);
				पूर्ण
				ci->suspended = 0;
				usb_gadget_set_state(&ci->gadget,
						ci->resume_state);
			पूर्ण
		पूर्ण

		अगर (USBi_UI  & पूर्णांकr)
			isr_tr_complete_handler(ci);

		अगर ((USBi_SLI & पूर्णांकr) && !(ci->suspended)) अणु
			ci->suspended = 1;
			ci->resume_state = ci->gadget.state;
			अगर (ci->gadget.speed != USB_SPEED_UNKNOWN &&
			    ci->driver->suspend) अणु
				spin_unlock(&ci->lock);
				ci->driver->suspend(&ci->gadget);
				spin_lock(&ci->lock);
			पूर्ण
			usb_gadget_set_state(&ci->gadget,
					USB_STATE_SUSPENDED);
		पूर्ण
		retval = IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		retval = IRQ_NONE;
	पूर्ण
	spin_unlock(&ci->lock);

	वापस retval;
पूर्ण

/**
 * udc_start: initialize gadget role
 * @ci: chipidea controller
 */
अटल पूर्णांक udc_start(काष्ठा ci_hdrc *ci)
अणु
	काष्ठा device *dev = ci->dev;
	काष्ठा usb_otg_caps *otg_caps = &ci->platdata->ci_otg_caps;
	पूर्णांक retval = 0;

	ci->gadget.ops          = &usb_gadget_ops;
	ci->gadget.speed        = USB_SPEED_UNKNOWN;
	ci->gadget.max_speed    = USB_SPEED_HIGH;
	ci->gadget.name         = ci->platdata->name;
	ci->gadget.otg_caps	= otg_caps;
	ci->gadget.sg_supported = 1;
	ci->gadget.irq		= ci->irq;

	अगर (ci->platdata->flags & CI_HDRC_REQUIRES_ALIGNED_DMA)
		ci->gadget.quirk_aव्योमs_skb_reserve = 1;

	अगर (ci->is_otg && (otg_caps->hnp_support || otg_caps->srp_support ||
						otg_caps->adp_support))
		ci->gadget.is_otg = 1;

	INIT_LIST_HEAD(&ci->gadget.ep_list);

	/* alloc resources */
	ci->qh_pool = dma_pool_create("ci_hw_qh", dev->parent,
				       माप(काष्ठा ci_hw_qh),
				       64, CI_HDRC_PAGE_SIZE);
	अगर (ci->qh_pool == शून्य)
		वापस -ENOMEM;

	ci->td_pool = dma_pool_create("ci_hw_td", dev->parent,
				       माप(काष्ठा ci_hw_td),
				       64, CI_HDRC_PAGE_SIZE);
	अगर (ci->td_pool == शून्य) अणु
		retval = -ENOMEM;
		जाओ मुक्त_qh_pool;
	पूर्ण

	retval = init_eps(ci);
	अगर (retval)
		जाओ मुक्त_pools;

	ci->gadget.ep0 = &ci->ep0in->ep;

	retval = usb_add_gadget_udc(dev, &ci->gadget);
	अगर (retval)
		जाओ destroy_eps;

	वापस retval;

destroy_eps:
	destroy_eps(ci);
मुक्त_pools:
	dma_pool_destroy(ci->td_pool);
मुक्त_qh_pool:
	dma_pool_destroy(ci->qh_pool);
	वापस retval;
पूर्ण

/*
 * ci_hdrc_gadget_destroy: parent हटाओ must call this to हटाओ UDC
 *
 * No पूर्णांकerrupts active, the IRQ has been released
 */
व्योम ci_hdrc_gadget_destroy(काष्ठा ci_hdrc *ci)
अणु
	अगर (!ci->roles[CI_ROLE_GADGET])
		वापस;

	usb_del_gadget_udc(&ci->gadget);

	destroy_eps(ci);

	dma_pool_destroy(ci->td_pool);
	dma_pool_destroy(ci->qh_pool);
पूर्ण

अटल पूर्णांक udc_id_चयन_क्रम_device(काष्ठा ci_hdrc *ci)
अणु
	अगर (ci->platdata->pins_device)
		pinctrl_select_state(ci->platdata->pctl,
				     ci->platdata->pins_device);

	अगर (ci->is_otg)
		/* Clear and enable BSV irq */
		hw_ग_लिखो_otgsc(ci, OTGSC_BSVIS | OTGSC_BSVIE,
					OTGSC_BSVIS | OTGSC_BSVIE);

	वापस 0;
पूर्ण

अटल व्योम udc_id_चयन_क्रम_host(काष्ठा ci_hdrc *ci)
अणु
	/*
	 * host करोesn't care B_SESSION_VALID event
	 * so clear and disbale BSV irq
	 */
	अगर (ci->is_otg)
		hw_ग_लिखो_otgsc(ci, OTGSC_BSVIE | OTGSC_BSVIS, OTGSC_BSVIS);

	ci->vbus_active = 0;

	अगर (ci->platdata->pins_device && ci->platdata->pins_शेष)
		pinctrl_select_state(ci->platdata->pctl,
				     ci->platdata->pins_शेष);
पूर्ण

/**
 * ci_hdrc_gadget_init - initialize device related bits
 * @ci: the controller
 *
 * This function initializes the gadget, अगर the device is "device capable".
 */
पूर्णांक ci_hdrc_gadget_init(काष्ठा ci_hdrc *ci)
अणु
	काष्ठा ci_role_driver *rdrv;
	पूर्णांक ret;

	अगर (!hw_पढ़ो(ci, CAP_DCCPARAMS, DCCPARAMS_DC))
		वापस -ENXIO;

	rdrv = devm_kzalloc(ci->dev, माप(*rdrv), GFP_KERNEL);
	अगर (!rdrv)
		वापस -ENOMEM;

	rdrv->start	= udc_id_चयन_क्रम_device;
	rdrv->stop	= udc_id_चयन_क्रम_host;
	rdrv->irq	= udc_irq;
	rdrv->name	= "gadget";

	ret = udc_start(ci);
	अगर (!ret)
		ci->roles[CI_ROLE_GADGET] = rdrv;

	वापस ret;
पूर्ण
