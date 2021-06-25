<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * bdc_udc.c - BRCM BDC USB3.0 device controller gagdet ops
 *
 * Copyright (C) 2014 Broadcom Corporation
 *
 * Author: Ashwini Pahuja
 *
 * Based on drivers under drivers/usb/gadget/udc/
 */
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/pm.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "bdc.h"
#समावेश "bdc_ep.h"
#समावेश "bdc_cmd.h"
#समावेश "bdc_dbg.h"

अटल स्थिर काष्ठा usb_gadget_ops bdc_gadget_ops;

अटल स्थिर अक्षर * स्थिर conn_speed_str[] =  अणु
	"Not connected",
	"Full Speed",
	"Low Speed",
	"High Speed",
	"Super Speed",
पूर्ण;

/* EP0 initial descripror */
अटल काष्ठा usb_endpoपूर्णांक_descriptor bdc_gadget_ep0_desc = अणु
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bmAttributes = USB_ENDPOINT_XFER_CONTROL,
	.bEndpoपूर्णांकAddress = 0,
	.wMaxPacketSize	= cpu_to_le16(EP0_MAX_PKT_SIZE),
पूर्ण;

/* Advance the srr dqp मुख्यtained by SW */
अटल व्योम srr_dqp_index_advc(काष्ठा bdc *bdc, u32 srr_num)
अणु
	काष्ठा srr *srr;

	srr = &bdc->srr;
	dev_dbg_ratelimited(bdc->dev, "srr->dqp_index:%d\n", srr->dqp_index);
	srr->dqp_index++;
	/* rollback to 0 अगर we are past the last */
	अगर (srr->dqp_index == NUM_SR_ENTRIES)
		srr->dqp_index = 0;
पूर्ण

/* connect sr */
अटल व्योम bdc_uspc_connected(काष्ठा bdc *bdc)
अणु
	u32 speed, temp;
	u32 usppms;
	पूर्णांक ret;

	temp = bdc_पढ़ोl(bdc->regs, BDC_USPC);
	speed = BDC_PSP(temp);
	dev_dbg(bdc->dev, "%s speed=%x\n", __func__, speed);
	चयन (speed) अणु
	हाल BDC_SPEED_SS:
		bdc_gadget_ep0_desc.wMaxPacketSize =
						cpu_to_le16(EP0_MAX_PKT_SIZE);
		bdc->gadget.ep0->maxpacket = EP0_MAX_PKT_SIZE;
		bdc->gadget.speed = USB_SPEED_SUPER;
		/* Enable U1T in SS mode */
		usppms =  bdc_पढ़ोl(bdc->regs, BDC_USPPMS);
		usppms &= ~BDC_U1T(0xff);
		usppms |= BDC_U1T(U1_TIMEOUT);
		usppms |= BDC_PORT_W1S;
		bdc_ग_लिखोl(bdc->regs, BDC_USPPMS, usppms);
		अवरोध;

	हाल BDC_SPEED_HS:
		bdc_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(64);
		bdc->gadget.ep0->maxpacket = 64;
		bdc->gadget.speed = USB_SPEED_HIGH;
		अवरोध;

	हाल BDC_SPEED_FS:
		bdc_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(64);
		bdc->gadget.ep0->maxpacket = 64;
		bdc->gadget.speed = USB_SPEED_FULL;
		अवरोध;

	हाल BDC_SPEED_LS:
		bdc_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(8);
		bdc->gadget.ep0->maxpacket = 8;
		bdc->gadget.speed = USB_SPEED_LOW;
		अवरोध;
	शेष:
		dev_err(bdc->dev, "UNDEFINED SPEED\n");
		वापस;
	पूर्ण
	dev_dbg(bdc->dev, "connected at %s\n", conn_speed_str[speed]);
	/* Now we know the speed, configure ep0 */
	bdc->bdc_ep_array[1]->desc = &bdc_gadget_ep0_desc;
	ret = bdc_config_ep(bdc, bdc->bdc_ep_array[1]);
	अगर (ret)
		dev_err(bdc->dev, "EP0 config failed\n");
	bdc->bdc_ep_array[1]->usb_ep.desc = &bdc_gadget_ep0_desc;
	bdc->bdc_ep_array[1]->flags |= BDC_EP_ENABLED;
	usb_gadget_set_state(&bdc->gadget, USB_STATE_DEFAULT);
पूर्ण

/* device got disconnected */
अटल व्योम bdc_uspc_disconnected(काष्ठा bdc *bdc, bool reinit)
अणु
	काष्ठा bdc_ep *ep;

	dev_dbg(bdc->dev, "%s\n", __func__);
	/*
	 * Only stop ep0 from here, rest of the endpoपूर्णांकs will be disabled
	 * from gadget_disconnect
	 */
	ep = bdc->bdc_ep_array[1];
	अगर (ep && (ep->flags & BDC_EP_ENABLED))
		/* अगर enabled then stop and हटाओ requests */
		bdc_ep_disable(ep);

	अगर (bdc->gadget_driver && bdc->gadget_driver->disconnect) अणु
		spin_unlock(&bdc->lock);
		bdc->gadget_driver->disconnect(&bdc->gadget);
		spin_lock(&bdc->lock);
	पूर्ण
	/* Set Unknown speed */
	bdc->gadget.speed = USB_SPEED_UNKNOWN;
	bdc->devstatus &= DEVSTATUS_CLEAR;
	bdc->delayed_status = false;
	bdc->reinit = reinit;
	bdc->test_mode = false;
पूर्ण

/* TNotअगरy wkaeup समयr */
अटल व्योम bdc_func_wake_समयr(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bdc *bdc = container_of(work, काष्ठा bdc, func_wake_notअगरy.work);
	अचिन्हित दीर्घ flags;

	dev_dbg(bdc->dev, "%s\n", __func__);
	spin_lock_irqsave(&bdc->lock, flags);
	/*
	 * Check अगर host has started transferring on endpoपूर्णांकs
	 * FUNC_WAKE_ISSUED is cleared when transfer has started after resume
	 */
	अगर (bdc->devstatus & FUNC_WAKE_ISSUED) अणु
		dev_dbg(bdc->dev, "FUNC_WAKE_ISSUED FLAG IS STILL SET\n");
		/* flag is still set, so again send func wake */
		bdc_function_wake_fh(bdc, 0);
		schedule_delayed_work(&bdc->func_wake_notअगरy,
						msecs_to_jअगरfies(BDC_TNOTIFY));
	पूर्ण
	spin_unlock_irqrestore(&bdc->lock, flags);
पूर्ण

/* handler क्रम Link state change condition */
अटल व्योम handle_link_state_change(काष्ठा bdc *bdc, u32 uspc)
अणु
	u32 link_state;

	dev_dbg(bdc->dev, "Link state change");
	link_state = BDC_PST(uspc);
	चयन (link_state) अणु
	हाल BDC_LINK_STATE_U3:
		अगर ((bdc->gadget.speed != USB_SPEED_UNKNOWN) &&
						bdc->gadget_driver->suspend) अणु
			dev_dbg(bdc->dev, "Entered Suspend mode\n");
			spin_unlock(&bdc->lock);
			bdc->devstatus |= DEVICE_SUSPENDED;
			bdc->gadget_driver->suspend(&bdc->gadget);
			spin_lock(&bdc->lock);
		पूर्ण
		अवरोध;
	हाल BDC_LINK_STATE_U0:
		अगर (bdc->devstatus & REMOTE_WAKEUP_ISSUED) अणु
			bdc->devstatus &= ~REMOTE_WAKEUP_ISSUED;
			अगर (bdc->gadget.speed == USB_SPEED_SUPER) अणु
				bdc_function_wake_fh(bdc, 0);
				bdc->devstatus |= FUNC_WAKE_ISSUED;
				/*
				 * Start a Notअगरication समयr and check अगर the
				 * Host transferred anything on any of the EPs,
				 * अगर not then send function wake again every
				 * TNotअगरication secs until host initiates
				 * transfer to BDC, USB3 spec Table 8.13
				 */
				schedule_delayed_work(
						&bdc->func_wake_notअगरy,
						msecs_to_jअगरfies(BDC_TNOTIFY));
				dev_dbg(bdc->dev, "sched func_wake_notify\n");
			पूर्ण
		पूर्ण
		अवरोध;

	हाल BDC_LINK_STATE_RESUME:
		dev_dbg(bdc->dev, "Resumed from Suspend\n");
		अगर (bdc->devstatus & DEVICE_SUSPENDED) अणु
			bdc->gadget_driver->resume(&bdc->gadget);
			bdc->devstatus &= ~DEVICE_SUSPENDED;
		पूर्ण
		अवरोध;
	शेष:
		dev_dbg(bdc->dev, "link state:%d\n", link_state);
	पूर्ण
पूर्ण

/* something changes on upstream port, handle it here */
व्योम bdc_sr_uspc(काष्ठा bdc *bdc, काष्ठा bdc_sr *sreport)
अणु
	u32 clear_flags = 0;
	u32 uspc;
	bool connected = false;
	bool disconn = false;

	uspc = bdc_पढ़ोl(bdc->regs, BDC_USPC);
	dev_dbg(bdc->dev, "%s uspc=0x%08x\n", __func__, uspc);

	/* Port connect changed */
	अगर (uspc & BDC_PCC) अणु
		/* Vbus not present, and not connected to Downstream port */
		अगर ((uspc & BDC_VBC) && !(uspc & BDC_VBS) && !(uspc & BDC_PCS))
			disconn = true;
		अन्यथा अगर ((uspc & BDC_PCS) && !BDC_PST(uspc))
			connected = true;
		clear_flags |= BDC_PCC;
	पूर्ण

	/* Change in VBus and VBus is present */
	अगर ((uspc & BDC_VBC) && (uspc & BDC_VBS)) अणु
		अगर (bdc->pullup) अणु
			dev_dbg(bdc->dev, "Do a softconnect\n");
			/* Attached state, करो a softconnect */
			bdc_softconn(bdc);
			usb_gadget_set_state(&bdc->gadget, USB_STATE_POWERED);
		पूर्ण
		clear_flags |= BDC_VBC;
	पूर्ण अन्यथा अगर ((uspc & BDC_PRS) || (uspc & BDC_PRC) || disconn) अणु
		/* Hot reset, warm reset, 2.0 bus reset or disconn */
		dev_dbg(bdc->dev, "Port reset or disconn\n");
		bdc_uspc_disconnected(bdc, disconn);
		clear_flags |= BDC_PRC;
	पूर्ण अन्यथा अगर ((uspc & BDC_PSC) && (uspc & BDC_PCS)) अणु
		/* Change in Link state */
		handle_link_state_change(bdc, uspc);
		clear_flags |= BDC_PSC;
	पूर्ण

	/*
	 * In SS we might not have PRC bit set beक्रमe connection, but in 2.0
	 * the PRC bit is set beक्रमe connection, so moving this condition out
	 * of bus reset to handle both SS/2.0 speeds.
	 */
	अगर (connected) अणु
		/* This is the connect event क्रम U0/L0 */
		dev_dbg(bdc->dev, "Connected\n");
		bdc_uspc_connected(bdc);
		bdc->devstatus &= ~(DEVICE_SUSPENDED);
	पूर्ण
	uspc = bdc_पढ़ोl(bdc->regs, BDC_USPC);
	uspc &= (~BDC_USPSC_RW);
	dev_dbg(bdc->dev, "uspc=%x\n", uspc);
	bdc_ग_लिखोl(bdc->regs, BDC_USPC, clear_flags);
पूर्ण

/* Main पूर्णांकerrupt handler क्रम bdc */
अटल irqवापस_t bdc_udc_पूर्णांकerrupt(पूर्णांक irq, व्योम *_bdc)
अणु
	u32 eqp_index, dqp_index, sr_type, srr_पूर्णांक;
	काष्ठा bdc_sr *sreport;
	काष्ठा bdc *bdc = _bdc;
	u32 status;
	पूर्णांक ret;

	spin_lock(&bdc->lock);
	status = bdc_पढ़ोl(bdc->regs, BDC_BDCSC);
	अगर (!(status & BDC_GIP)) अणु
		spin_unlock(&bdc->lock);
		वापस IRQ_NONE;
	पूर्ण
	srr_पूर्णांक = bdc_पढ़ोl(bdc->regs, BDC_SRRINT(0));
	/* Check अगर the SRR IP bit it set? */
	अगर (!(srr_पूर्णांक & BDC_SRR_IP)) अणु
		dev_warn(bdc->dev, "Global irq pending but SRR IP is 0\n");
		spin_unlock(&bdc->lock);
		वापस IRQ_NONE;
	पूर्ण
	eqp_index = BDC_SRR_EPI(srr_पूर्णांक);
	dqp_index = BDC_SRR_DPI(srr_पूर्णांक);
	dev_dbg(bdc->dev,
			"%s eqp_index=%d dqp_index=%d  srr.dqp_index=%d\n\n",
			 __func__, eqp_index, dqp_index, bdc->srr.dqp_index);

	/* check क्रम ring empty condition */
	अगर (eqp_index == dqp_index) अणु
		dev_dbg(bdc->dev, "SRR empty?\n");
		spin_unlock(&bdc->lock);
		वापस IRQ_HANDLED;
	पूर्ण

	जबतक (bdc->srr.dqp_index != eqp_index) अणु
		sreport = &bdc->srr.sr_bds[bdc->srr.dqp_index];
		/* sreport is पढ़ो beक्रमe using it */
		rmb();
		sr_type = le32_to_cpu(sreport->offset[3]) & BD_TYPE_BITMASK;
		dev_dbg_ratelimited(bdc->dev, "sr_type=%d\n", sr_type);
		चयन (sr_type) अणु
		हाल SR_XSF:
			bdc->sr_handler[0](bdc, sreport);
			अवरोध;

		हाल SR_USPC:
			bdc->sr_handler[1](bdc, sreport);
			अवरोध;
		शेष:
			dev_warn(bdc->dev, "SR:%d not handled\n", sr_type);
		पूर्ण
		/* Advance the srr dqp index */
		srr_dqp_index_advc(bdc, 0);
	पूर्ण
	/* update the hw dequeue poपूर्णांकer */
	srr_पूर्णांक = bdc_पढ़ोl(bdc->regs, BDC_SRRINT(0));
	srr_पूर्णांक &= ~BDC_SRR_DPI_MASK;
	srr_पूर्णांक &= ~(BDC_SRR_RWS|BDC_SRR_RST|BDC_SRR_ISR);
	srr_पूर्णांक |= ((bdc->srr.dqp_index) << 16);
	srr_पूर्णांक |= BDC_SRR_IP;
	bdc_ग_लिखोl(bdc->regs, BDC_SRRINT(0), srr_पूर्णांक);
	srr_पूर्णांक = bdc_पढ़ोl(bdc->regs, BDC_SRRINT(0));
	अगर (bdc->reinit) अणु
		ret = bdc_reinit(bdc);
		अगर (ret)
			dev_err(bdc->dev, "err in bdc reinit\n");
	पूर्ण

	spin_unlock(&bdc->lock);

	वापस IRQ_HANDLED;
पूर्ण

/* Gadget ops */
अटल पूर्णांक bdc_udc_start(काष्ठा usb_gadget *gadget,
				काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा bdc *bdc = gadget_to_bdc(gadget);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	dev_dbg(bdc->dev, "%s()\n", __func__);
	spin_lock_irqsave(&bdc->lock, flags);
	अगर (bdc->gadget_driver) अणु
		dev_err(bdc->dev, "%s is already bound to %s\n",
			bdc->gadget.name,
			bdc->gadget_driver->driver.name);
		ret = -EBUSY;
		जाओ err;
	पूर्ण
	/*
	 * Run the controller from here and when BDC is connected to
	 * Host then driver will receive a USPC SR with VBUS present
	 * and then driver will करो a softconnect.
	 */
	ret = bdc_run(bdc);
	अगर (ret) अणु
		dev_err(bdc->dev, "%s bdc run fail\n", __func__);
		जाओ err;
	पूर्ण
	bdc->gadget_driver = driver;
	bdc->gadget.dev.driver = &driver->driver;
err:
	spin_unlock_irqrestore(&bdc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक bdc_udc_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा bdc *bdc = gadget_to_bdc(gadget);
	अचिन्हित दीर्घ flags;

	dev_dbg(bdc->dev, "%s()\n", __func__);
	spin_lock_irqsave(&bdc->lock, flags);
	bdc_stop(bdc);
	bdc->gadget_driver = शून्य;
	bdc->gadget.dev.driver = शून्य;
	spin_unlock_irqrestore(&bdc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक bdc_udc_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा bdc *bdc = gadget_to_bdc(gadget);
	अचिन्हित दीर्घ flags;
	u32 uspc;

	dev_dbg(bdc->dev, "%s() is_on:%d\n", __func__, is_on);
	अगर (!gadget)
		वापस -EINVAL;

	spin_lock_irqsave(&bdc->lock, flags);
	अगर (!is_on) अणु
		bdc_softdisconn(bdc);
		bdc->pullup = false;
	पूर्ण अन्यथा अणु
		/*
		 * For a self घातered device, we need to रुको till we receive
		 * a VBUS change and Vbus present event, then अगर pullup flag
		 * is set, then only we present the Termपूर्णांकation.
		 */
		bdc->pullup = true;
		/*
		 * Check अगर BDC is alपढ़ोy connected to Host i.e Vbus=1,
		 * अगर yes, then present TERM now, this is typical क्रम bus
		 * घातered devices.
		 */
		uspc = bdc_पढ़ोl(bdc->regs, BDC_USPC);
		अगर (uspc & BDC_VBS)
			bdc_softconn(bdc);
	पूर्ण
	spin_unlock_irqrestore(&bdc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक bdc_udc_set_selfघातered(काष्ठा usb_gadget *gadget,
		पूर्णांक is_self)
अणु
	काष्ठा bdc		*bdc = gadget_to_bdc(gadget);
	अचिन्हित दीर्घ           flags;

	dev_dbg(bdc->dev, "%s()\n", __func__);
	gadget->is_selfघातered = (is_self != 0);
	spin_lock_irqsave(&bdc->lock, flags);
	अगर (!is_self)
		bdc->devstatus |= 1 << USB_DEVICE_SELF_POWERED;
	अन्यथा
		bdc->devstatus &= ~(1 << USB_DEVICE_SELF_POWERED);

	spin_unlock_irqrestore(&bdc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक bdc_udc_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा bdc *bdc = gadget_to_bdc(gadget);
	अचिन्हित दीर्घ		flags;
	u8	link_state;
	u32	uspc;
	पूर्णांक ret = 0;

	dev_dbg(bdc->dev,
		"%s() bdc->devstatus=%08x\n",
		__func__, bdc->devstatus);

	अगर (!(bdc->devstatus & REMOTE_WAKE_ENABLE))
		वापस  -EOPNOTSUPP;

	spin_lock_irqsave(&bdc->lock, flags);
	uspc = bdc_पढ़ोl(bdc->regs, BDC_USPC);
	link_state = BDC_PST(uspc);
	dev_dbg(bdc->dev, "link_state =%d portsc=%x", link_state, uspc);
	अगर (link_state != BDC_LINK_STATE_U3) अणु
		dev_warn(bdc->dev,
			"can't wakeup from link state %d\n",
			link_state);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (bdc->gadget.speed == USB_SPEED_SUPER)
		bdc->devstatus |= REMOTE_WAKEUP_ISSUED;

	uspc &= ~BDC_PST_MASK;
	uspc &= (~BDC_USPSC_RW);
	uspc |=  BDC_PST(BDC_LINK_STATE_U0);
	uspc |=  BDC_SWS;
	bdc_ग_लिखोl(bdc->regs, BDC_USPC, uspc);
	uspc = bdc_पढ़ोl(bdc->regs, BDC_USPC);
	link_state = BDC_PST(uspc);
	dev_dbg(bdc->dev, "link_state =%d portsc=%x", link_state, uspc);
out:
	spin_unlock_irqrestore(&bdc->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops bdc_gadget_ops = अणु
	.wakeup = bdc_udc_wakeup,
	.set_selfघातered = bdc_udc_set_selfघातered,
	.pullup = bdc_udc_pullup,
	.udc_start = bdc_udc_start,
	.udc_stop = bdc_udc_stop,
पूर्ण;

/* Init the gadget पूर्णांकerface and रेजिस्टर the udc */
पूर्णांक bdc_udc_init(काष्ठा bdc *bdc)
अणु
	u32 temp;
	पूर्णांक ret;

	dev_dbg(bdc->dev, "%s()\n", __func__);
	bdc->gadget.ops = &bdc_gadget_ops;
	bdc->gadget.max_speed = USB_SPEED_SUPER;
	bdc->gadget.speed = USB_SPEED_UNKNOWN;
	bdc->gadget.dev.parent = bdc->dev;

	bdc->gadget.sg_supported = false;


	bdc->gadget.name = BRCM_BDC_NAME;
	ret = devm_request_irq(bdc->dev, bdc->irq, bdc_udc_पूर्णांकerrupt,
				IRQF_SHARED, BRCM_BDC_NAME, bdc);
	अगर (ret) अणु
		dev_err(bdc->dev,
			"failed to request irq #%d %d\n",
			bdc->irq, ret);
		वापस ret;
	पूर्ण

	ret = bdc_init_ep(bdc);
	अगर (ret) अणु
		dev_err(bdc->dev, "bdc init ep fail: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = usb_add_gadget_udc(bdc->dev, &bdc->gadget);
	अगर (ret) अणु
		dev_err(bdc->dev, "failed to register udc\n");
		जाओ err0;
	पूर्ण
	usb_gadget_set_state(&bdc->gadget, USB_STATE_NOTATTACHED);
	bdc->bdc_ep_array[1]->desc = &bdc_gadget_ep0_desc;
	/*
	 * Allocate bd list क्रम ep0 only, ep0 will be enabled on connect
	 * status report when the speed is known
	 */
	ret = bdc_ep_enable(bdc->bdc_ep_array[1]);
	अगर (ret) अणु
		dev_err(bdc->dev, "fail to enable %s\n",
						bdc->bdc_ep_array[1]->name);
		जाओ err1;
	पूर्ण
	INIT_DELAYED_WORK(&bdc->func_wake_notअगरy, bdc_func_wake_समयr);
	/* Enable Interrupts */
	temp = bdc_पढ़ोl(bdc->regs, BDC_BDCSC);
	temp |= BDC_GIE;
	bdc_ग_लिखोl(bdc->regs, BDC_BDCSC, temp);
	वापस 0;
err1:
	usb_del_gadget_udc(&bdc->gadget);
err0:
	bdc_मुक्त_ep(bdc);

	वापस ret;
पूर्ण

व्योम bdc_udc_निकास(काष्ठा bdc *bdc)
अणु
	अचिन्हित दीर्घ flags;

	dev_dbg(bdc->dev, "%s()\n", __func__);
	spin_lock_irqsave(&bdc->lock, flags);
	bdc_ep_disable(bdc->bdc_ep_array[1]);
	spin_unlock_irqrestore(&bdc->lock, flags);

	usb_del_gadget_udc(&bdc->gadget);
	bdc_मुक्त_ep(bdc);
पूर्ण
