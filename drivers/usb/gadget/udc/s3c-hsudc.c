<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* linux/drivers/usb/gadget/s3c-hsudc.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * S3C24XX USB 2.0 High-speed USB controller gadget driver
 *
 * The S3C24XX USB 2.0 high-speed USB controller supports upto 9 endpoपूर्णांकs.
 * Each endpoपूर्णांक can be configured as either in or out endpoपूर्णांक. Endpoपूर्णांकs
 * can be configured क्रम Bulk or Interrupt transfer mode.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/platक्रमm_data/s3c-hsudc.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा S3C_HSUDC_REG(x)	(x)

/* Non-Indexed Registers */
#घोषणा S3C_IR				S3C_HSUDC_REG(0x00) /* Index Register */
#घोषणा S3C_EIR				S3C_HSUDC_REG(0x04) /* EP Intr Status */
#घोषणा S3C_EIR_EP0			(1<<0)
#घोषणा S3C_EIER			S3C_HSUDC_REG(0x08) /* EP Intr Enable */
#घोषणा S3C_FAR				S3C_HSUDC_REG(0x0c) /* Gadget Address */
#घोषणा S3C_FNR				S3C_HSUDC_REG(0x10) /* Frame Number */
#घोषणा S3C_EDR				S3C_HSUDC_REG(0x14) /* EP Direction */
#घोषणा S3C_TR				S3C_HSUDC_REG(0x18) /* Test Register */
#घोषणा S3C_SSR				S3C_HSUDC_REG(0x1c) /* System Status */
#घोषणा S3C_SSR_DTZIEN_EN		(0xff8f)
#घोषणा S3C_SSR_ERR			(0xff80)
#घोषणा S3C_SSR_VBUSON			(1 << 8)
#घोषणा S3C_SSR_HSP			(1 << 4)
#घोषणा S3C_SSR_SDE			(1 << 3)
#घोषणा S3C_SSR_RESUME			(1 << 2)
#घोषणा S3C_SSR_SUSPEND			(1 << 1)
#घोषणा S3C_SSR_RESET			(1 << 0)
#घोषणा S3C_SCR				S3C_HSUDC_REG(0x20) /* System Control */
#घोषणा S3C_SCR_DTZIEN_EN		(1 << 14)
#घोषणा S3C_SCR_RRD_EN			(1 << 5)
#घोषणा S3C_SCR_SUS_EN			(1 << 1)
#घोषणा S3C_SCR_RST_EN			(1 << 0)
#घोषणा S3C_EP0SR			S3C_HSUDC_REG(0x24) /* EP0 Status */
#घोषणा S3C_EP0SR_EP0_LWO		(1 << 6)
#घोषणा S3C_EP0SR_STALL			(1 << 4)
#घोषणा S3C_EP0SR_TX_SUCCESS		(1 << 1)
#घोषणा S3C_EP0SR_RX_SUCCESS		(1 << 0)
#घोषणा S3C_EP0CR			S3C_HSUDC_REG(0x28) /* EP0 Control */
#घोषणा S3C_BR(_x)			S3C_HSUDC_REG(0x60 + (_x * 4))

/* Indexed Registers */
#घोषणा S3C_ESR				S3C_HSUDC_REG(0x2c) /* EPn Status */
#घोषणा S3C_ESR_FLUSH			(1 << 6)
#घोषणा S3C_ESR_STALL			(1 << 5)
#घोषणा S3C_ESR_LWO			(1 << 4)
#घोषणा S3C_ESR_PSIF_ONE		(1 << 2)
#घोषणा S3C_ESR_PSIF_TWO		(2 << 2)
#घोषणा S3C_ESR_TX_SUCCESS		(1 << 1)
#घोषणा S3C_ESR_RX_SUCCESS		(1 << 0)
#घोषणा S3C_ECR				S3C_HSUDC_REG(0x30) /* EPn Control */
#घोषणा S3C_ECR_DUEN			(1 << 7)
#घोषणा S3C_ECR_FLUSH			(1 << 6)
#घोषणा S3C_ECR_STALL			(1 << 1)
#घोषणा S3C_ECR_IEMS			(1 << 0)
#घोषणा S3C_BRCR			S3C_HSUDC_REG(0x34) /* Read Count */
#घोषणा S3C_BWCR			S3C_HSUDC_REG(0x38) /* Write Count */
#घोषणा S3C_MPR				S3C_HSUDC_REG(0x3c) /* Max Pkt Size */

#घोषणा WAIT_FOR_SETUP			(0)
#घोषणा DATA_STATE_XMIT			(1)
#घोषणा DATA_STATE_RECV			(2)

अटल स्थिर अक्षर * स्थिर s3c_hsudc_supply_names[] = अणु
	"vdda",		/* analog phy supply, 3.3V */
	"vddi",		/* digital phy supply, 1.2V */
	"vddosc",	/* oscillator supply, 1.8V - 3.3V */
पूर्ण;

/**
 * काष्ठा s3c_hsudc_ep - Endpoपूर्णांक representation used by driver.
 * @ep: USB gadget layer representation of device endpoपूर्णांक.
 * @name: Endpoपूर्णांक name (as required by ep स्वतःconfiguration).
 * @dev: Reference to the device controller to which this EP beदीर्घs.
 * @desc: Endpoपूर्णांक descriptor obtained from the gadget driver.
 * @queue: Transfer request queue क्रम the endpoपूर्णांक.
 * @stopped: Maपूर्णांकains state of endpoपूर्णांक, set अगर EP is halted.
 * @bEndpoपूर्णांकAddress: EP address (including direction bit).
 * @fअगरo: Base address of EP FIFO.
 */
काष्ठा s3c_hsudc_ep अणु
	काष्ठा usb_ep ep;
	अक्षर name[20];
	काष्ठा s3c_hsudc *dev;
	काष्ठा list_head queue;
	u8 stopped;
	u8 wedge;
	u8 bEndpoपूर्णांकAddress;
	व्योम __iomem *fअगरo;
पूर्ण;

/**
 * काष्ठा s3c_hsudc_req - Driver encapsulation of USB gadget transfer request.
 * @req: Reference to USB gadget transfer request.
 * @queue: Used क्रम inserting this request to the endpoपूर्णांक request queue.
 */
काष्ठा s3c_hsudc_req अणु
	काष्ठा usb_request req;
	काष्ठा list_head queue;
पूर्ण;

/**
 * काष्ठा s3c_hsudc - Driver's असलtraction of the device controller.
 * @gadget: Instance of usb_gadget which is referenced by gadget driver.
 * @driver: Reference to currenty active gadget driver.
 * @dev: The device reference used by probe function.
 * @lock: Lock to synchronize the usage of Endpoपूर्णांकs (EP's are indexed).
 * @regs: Remapped base address of controller's रेजिस्टर space.
 * irq: IRQ number used by the controller.
 * uclk: Reference to the controller घड़ी.
 * ep0state: Current state of EP0.
 * ep: List of endpoपूर्णांकs supported by the controller.
 */
काष्ठा s3c_hsudc अणु
	काष्ठा usb_gadget gadget;
	काष्ठा usb_gadget_driver *driver;
	काष्ठा device *dev;
	काष्ठा s3c24xx_hsudc_platdata *pd;
	काष्ठा usb_phy *transceiver;
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(s3c_hsudc_supply_names)];
	spinlock_t lock;
	व्योम __iomem *regs;
	पूर्णांक irq;
	काष्ठा clk *uclk;
	पूर्णांक ep0state;
	काष्ठा s3c_hsudc_ep ep[];
पूर्ण;

#घोषणा ep_maxpacket(_ep)	((_ep)->ep.maxpacket)
#घोषणा ep_is_in(_ep)		((_ep)->bEndpoपूर्णांकAddress & USB_सूची_IN)
#घोषणा ep_index(_ep)		((_ep)->bEndpoपूर्णांकAddress & \
					USB_ENDPOINT_NUMBER_MASK)

अटल स्थिर अक्षर driver_name[] = "s3c-udc";
अटल स्थिर अक्षर ep0name[] = "ep0-control";

अटल अंतरभूत काष्ठा s3c_hsudc_req *our_req(काष्ठा usb_request *req)
अणु
	वापस container_of(req, काष्ठा s3c_hsudc_req, req);
पूर्ण

अटल अंतरभूत काष्ठा s3c_hsudc_ep *our_ep(काष्ठा usb_ep *ep)
अणु
	वापस container_of(ep, काष्ठा s3c_hsudc_ep, ep);
पूर्ण

अटल अंतरभूत काष्ठा s3c_hsudc *to_hsudc(काष्ठा usb_gadget *gadget)
अणु
	वापस container_of(gadget, काष्ठा s3c_hsudc, gadget);
पूर्ण

अटल अंतरभूत व्योम set_index(काष्ठा s3c_hsudc *hsudc, पूर्णांक ep_addr)
अणु
	ep_addr &= USB_ENDPOINT_NUMBER_MASK;
	ग_लिखोl(ep_addr, hsudc->regs + S3C_IR);
पूर्ण

अटल अंतरभूत व्योम __orr32(व्योम __iomem *ptr, u32 val)
अणु
	ग_लिखोl(पढ़ोl(ptr) | val, ptr);
पूर्ण

/**
 * s3c_hsudc_complete_request - Complete a transfer request.
 * @hsep: Endpoपूर्णांक to which the request beदीर्घs.
 * @hsreq: Transfer request to be completed.
 * @status: Transfer completion status क्रम the transfer request.
 */
अटल व्योम s3c_hsudc_complete_request(काष्ठा s3c_hsudc_ep *hsep,
				काष्ठा s3c_hsudc_req *hsreq, पूर्णांक status)
अणु
	अचिन्हित पूर्णांक stopped = hsep->stopped;
	काष्ठा s3c_hsudc *hsudc = hsep->dev;

	list_del_init(&hsreq->queue);
	hsreq->req.status = status;

	अगर (!ep_index(hsep)) अणु
		hsudc->ep0state = WAIT_FOR_SETUP;
		hsep->bEndpoपूर्णांकAddress &= ~USB_सूची_IN;
	पूर्ण

	hsep->stopped = 1;
	spin_unlock(&hsudc->lock);
	usb_gadget_giveback_request(&hsep->ep, &hsreq->req);
	spin_lock(&hsudc->lock);
	hsep->stopped = stopped;
पूर्ण

/**
 * s3c_hsudc_nuke_ep - Terminate all requests queued क्रम a endpoपूर्णांक.
 * @hsep: Endpoपूर्णांक क्रम which queued requests have to be terminated.
 * @status: Transfer completion status क्रम the transfer request.
 */
अटल व्योम s3c_hsudc_nuke_ep(काष्ठा s3c_hsudc_ep *hsep, पूर्णांक status)
अणु
	काष्ठा s3c_hsudc_req *hsreq;

	जबतक (!list_empty(&hsep->queue)) अणु
		hsreq = list_entry(hsep->queue.next,
				काष्ठा s3c_hsudc_req, queue);
		s3c_hsudc_complete_request(hsep, hsreq, status);
	पूर्ण
पूर्ण

/**
 * s3c_hsudc_stop_activity - Stop activity on all endpoपूर्णांकs.
 * @hsudc: Device controller क्रम which EP activity is to be stopped.
 *
 * All the endpoपूर्णांकs are stopped and any pending transfer requests अगर any on
 * the endpoपूर्णांक are terminated.
 */
अटल व्योम s3c_hsudc_stop_activity(काष्ठा s3c_hsudc *hsudc)
अणु
	काष्ठा s3c_hsudc_ep *hsep;
	पूर्णांक epnum;

	hsudc->gadget.speed = USB_SPEED_UNKNOWN;

	क्रम (epnum = 0; epnum < hsudc->pd->epnum; epnum++) अणु
		hsep = &hsudc->ep[epnum];
		hsep->stopped = 1;
		s3c_hsudc_nuke_ep(hsep, -ESHUTDOWN);
	पूर्ण
पूर्ण

/**
 * s3c_hsudc_पढ़ो_setup_pkt - Read the received setup packet from EP0 fअगरo.
 * @hsudc: Device controller from which setup packet is to be पढ़ो.
 * @buf: The buffer पूर्णांकo which the setup packet is पढ़ो.
 *
 * The setup packet received in the EP0 fअगरo is पढ़ो and stored पूर्णांकo a
 * given buffer address.
 */

अटल व्योम s3c_hsudc_पढ़ो_setup_pkt(काष्ठा s3c_hsudc *hsudc, u16 *buf)
अणु
	पूर्णांक count;

	count = पढ़ोl(hsudc->regs + S3C_BRCR);
	जबतक (count--)
		*buf++ = (u16)पढ़ोl(hsudc->regs + S3C_BR(0));

	ग_लिखोl(S3C_EP0SR_RX_SUCCESS, hsudc->regs + S3C_EP0SR);
पूर्ण

/**
 * s3c_hsudc_ग_लिखो_fअगरo - Write next chunk of transfer data to EP fअगरo.
 * @hsep: Endpoपूर्णांक to which the data is to be written.
 * @hsreq: Transfer request from which the next chunk of data is written.
 *
 * Write the next chunk of data from a transfer request to the endpoपूर्णांक FIFO.
 * If the transfer request completes, 1 is वापसed, otherwise 0 is वापसed.
 */
अटल पूर्णांक s3c_hsudc_ग_लिखो_fअगरo(काष्ठा s3c_hsudc_ep *hsep,
				काष्ठा s3c_hsudc_req *hsreq)
अणु
	u16 *buf;
	u32 max = ep_maxpacket(hsep);
	u32 count, length;
	bool is_last;
	व्योम __iomem *fअगरo = hsep->fअगरo;

	buf = hsreq->req.buf + hsreq->req.actual;
	prefetch(buf);

	length = hsreq->req.length - hsreq->req.actual;
	length = min(length, max);
	hsreq->req.actual += length;

	ग_लिखोl(length, hsep->dev->regs + S3C_BWCR);
	क्रम (count = 0; count < length; count += 2)
		ग_लिखोl(*buf++, fअगरo);

	अगर (count != max) अणु
		is_last = true;
	पूर्ण अन्यथा अणु
		अगर (hsreq->req.length != hsreq->req.actual || hsreq->req.zero)
			is_last = false;
		अन्यथा
			is_last = true;
	पूर्ण

	अगर (is_last) अणु
		s3c_hsudc_complete_request(hsep, hsreq, 0);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * s3c_hsudc_पढ़ो_fअगरo - Read the next chunk of data from EP fअगरo.
 * @hsep: Endpoपूर्णांक from which the data is to be पढ़ो.
 * @hsreq: Transfer request to which the next chunk of data पढ़ो is written.
 *
 * Read the next chunk of data from the endpoपूर्णांक FIFO and a ग_लिखो it to the
 * transfer request buffer. If the transfer request completes, 1 is वापसed,
 * otherwise 0 is वापसed.
 */
अटल पूर्णांक s3c_hsudc_पढ़ो_fअगरo(काष्ठा s3c_hsudc_ep *hsep,
				काष्ठा s3c_hsudc_req *hsreq)
अणु
	काष्ठा s3c_hsudc *hsudc = hsep->dev;
	u32 csr, offset;
	u16 *buf, word;
	u32 buflen, rcnt, rlen;
	व्योम __iomem *fअगरo = hsep->fअगरo;
	u32 is_लघु = 0;

	offset = (ep_index(hsep)) ? S3C_ESR : S3C_EP0SR;
	csr = पढ़ोl(hsudc->regs + offset);
	अगर (!(csr & S3C_ESR_RX_SUCCESS))
		वापस -EINVAL;

	buf = hsreq->req.buf + hsreq->req.actual;
	prefetchw(buf);
	buflen = hsreq->req.length - hsreq->req.actual;

	rcnt = पढ़ोl(hsudc->regs + S3C_BRCR);
	rlen = (csr & S3C_ESR_LWO) ? (rcnt * 2 - 1) : (rcnt * 2);

	hsreq->req.actual += min(rlen, buflen);
	is_लघु = (rlen < hsep->ep.maxpacket);

	जबतक (rcnt-- != 0) अणु
		word = (u16)पढ़ोl(fअगरo);
		अगर (buflen) अणु
			*buf++ = word;
			buflen--;
		पूर्ण अन्यथा अणु
			hsreq->req.status = -EOVERFLOW;
		पूर्ण
	पूर्ण

	ग_लिखोl(S3C_ESR_RX_SUCCESS, hsudc->regs + offset);

	अगर (is_लघु || hsreq->req.actual == hsreq->req.length) अणु
		s3c_hsudc_complete_request(hsep, hsreq, 0);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * s3c_hsudc_epin_पूर्णांकr - Handle in-endpoपूर्णांक पूर्णांकerrupt.
 * @hsudc - Device controller क्रम which the पूर्णांकerrupt is to be handled.
 * @ep_idx - Endpoपूर्णांक number on which an पूर्णांकerrupt is pending.
 *
 * Handles पूर्णांकerrupt क्रम a in-endpoपूर्णांक. The पूर्णांकerrupts that are handled are
 * stall and data transmit complete पूर्णांकerrupt.
 */
अटल व्योम s3c_hsudc_epin_पूर्णांकr(काष्ठा s3c_hsudc *hsudc, u32 ep_idx)
अणु
	काष्ठा s3c_hsudc_ep *hsep = &hsudc->ep[ep_idx];
	काष्ठा s3c_hsudc_req *hsreq;
	u32 csr;

	csr = पढ़ोl(hsudc->regs + S3C_ESR);
	अगर (csr & S3C_ESR_STALL) अणु
		ग_लिखोl(S3C_ESR_STALL, hsudc->regs + S3C_ESR);
		वापस;
	पूर्ण

	अगर (csr & S3C_ESR_TX_SUCCESS) अणु
		ग_लिखोl(S3C_ESR_TX_SUCCESS, hsudc->regs + S3C_ESR);
		अगर (list_empty(&hsep->queue))
			वापस;

		hsreq = list_entry(hsep->queue.next,
				काष्ठा s3c_hsudc_req, queue);
		अगर ((s3c_hsudc_ग_लिखो_fअगरo(hsep, hsreq) == 0) &&
				(csr & S3C_ESR_PSIF_TWO))
			s3c_hsudc_ग_लिखो_fअगरo(hsep, hsreq);
	पूर्ण
पूर्ण

/**
 * s3c_hsudc_epout_पूर्णांकr - Handle out-endpoपूर्णांक पूर्णांकerrupt.
 * @hsudc - Device controller क्रम which the पूर्णांकerrupt is to be handled.
 * @ep_idx - Endpoपूर्णांक number on which an पूर्णांकerrupt is pending.
 *
 * Handles पूर्णांकerrupt क्रम a out-endpoपूर्णांक. The पूर्णांकerrupts that are handled are
 * stall, flush and data पढ़ोy पूर्णांकerrupt.
 */
अटल व्योम s3c_hsudc_epout_पूर्णांकr(काष्ठा s3c_hsudc *hsudc, u32 ep_idx)
अणु
	काष्ठा s3c_hsudc_ep *hsep = &hsudc->ep[ep_idx];
	काष्ठा s3c_hsudc_req *hsreq;
	u32 csr;

	csr = पढ़ोl(hsudc->regs + S3C_ESR);
	अगर (csr & S3C_ESR_STALL) अणु
		ग_लिखोl(S3C_ESR_STALL, hsudc->regs + S3C_ESR);
		वापस;
	पूर्ण

	अगर (csr & S3C_ESR_FLUSH) अणु
		__orr32(hsudc->regs + S3C_ECR, S3C_ECR_FLUSH);
		वापस;
	पूर्ण

	अगर (csr & S3C_ESR_RX_SUCCESS) अणु
		अगर (list_empty(&hsep->queue))
			वापस;

		hsreq = list_entry(hsep->queue.next,
				काष्ठा s3c_hsudc_req, queue);
		अगर (((s3c_hsudc_पढ़ो_fअगरo(hsep, hsreq)) == 0) &&
				(csr & S3C_ESR_PSIF_TWO))
			s3c_hsudc_पढ़ो_fअगरo(hsep, hsreq);
	पूर्ण
पूर्ण

/** s3c_hsudc_set_halt - Set or clear a endpoपूर्णांक halt.
 * @_ep: Endpoपूर्णांक on which halt has to be set or cleared.
 * @value: 1 क्रम setting halt on endpoपूर्णांक, 0 to clear halt.
 *
 * Set or clear endpoपूर्णांक halt. If halt is set, the endpoपूर्णांक is stopped.
 * If halt is cleared, क्रम in-endpoपूर्णांकs, अगर there are any pending
 * transfer requests, transfers are started.
 */
अटल पूर्णांक s3c_hsudc_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा s3c_hsudc_ep *hsep = our_ep(_ep);
	काष्ठा s3c_hsudc *hsudc = hsep->dev;
	काष्ठा s3c_hsudc_req *hsreq;
	अचिन्हित दीर्घ irqflags;
	u32 ecr;
	u32 offset;

	अगर (value && ep_is_in(hsep) && !list_empty(&hsep->queue))
		वापस -EAGAIN;

	spin_lock_irqsave(&hsudc->lock, irqflags);
	set_index(hsudc, ep_index(hsep));
	offset = (ep_index(hsep)) ? S3C_ECR : S3C_EP0CR;
	ecr = पढ़ोl(hsudc->regs + offset);

	अगर (value) अणु
		ecr |= S3C_ECR_STALL;
		अगर (ep_index(hsep))
			ecr |= S3C_ECR_FLUSH;
		hsep->stopped = 1;
	पूर्ण अन्यथा अणु
		ecr &= ~S3C_ECR_STALL;
		hsep->stopped = hsep->wedge = 0;
	पूर्ण
	ग_लिखोl(ecr, hsudc->regs + offset);

	अगर (ep_is_in(hsep) && !list_empty(&hsep->queue) && !value) अणु
		hsreq = list_entry(hsep->queue.next,
			काष्ठा s3c_hsudc_req, queue);
		अगर (hsreq)
			s3c_hsudc_ग_लिखो_fअगरo(hsep, hsreq);
	पूर्ण

	spin_unlock_irqrestore(&hsudc->lock, irqflags);
	वापस 0;
पूर्ण

/** s3c_hsudc_set_wedge - Sets the halt feature with the clear requests ignored
 * @_ep: Endpoपूर्णांक on which wedge has to be set.
 *
 * Sets the halt feature with the clear requests ignored.
 */
अटल पूर्णांक s3c_hsudc_set_wedge(काष्ठा usb_ep *_ep)
अणु
	काष्ठा s3c_hsudc_ep *hsep = our_ep(_ep);

	अगर (!hsep)
		वापस -EINVAL;

	hsep->wedge = 1;
	वापस usb_ep_set_halt(_ep);
पूर्ण

/** s3c_hsudc_handle_reqfeat - Handle set feature or clear feature requests.
 * @_ep: Device controller on which the set/clear feature needs to be handled.
 * @ctrl: Control request as received on the endpoपूर्णांक 0.
 *
 * Handle set feature or clear feature control requests on the control endpoपूर्णांक.
 */
अटल पूर्णांक s3c_hsudc_handle_reqfeat(काष्ठा s3c_hsudc *hsudc,
					काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा s3c_hsudc_ep *hsep;
	bool set = (ctrl->bRequest == USB_REQ_SET_FEATURE);
	u8 ep_num = ctrl->wIndex & USB_ENDPOINT_NUMBER_MASK;

	अगर (ctrl->bRequestType == USB_RECIP_ENDPOINT) अणु
		hsep = &hsudc->ep[ep_num];
		चयन (le16_to_cpu(ctrl->wValue)) अणु
		हाल USB_ENDPOINT_HALT:
			अगर (set || !hsep->wedge)
				s3c_hsudc_set_halt(&hsep->ep, set);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

/**
 * s3c_hsudc_process_req_status - Handle get status control request.
 * @hsudc: Device controller on which get status request has be handled.
 * @ctrl: Control request as received on the endpoपूर्णांक 0.
 *
 * Handle get status control request received on control endpoपूर्णांक.
 */
अटल व्योम s3c_hsudc_process_req_status(काष्ठा s3c_hsudc *hsudc,
					काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा s3c_hsudc_ep *hsep0 = &hsudc->ep[0];
	काष्ठा s3c_hsudc_req hsreq;
	काष्ठा s3c_hsudc_ep *hsep;
	__le16 reply;
	u8 epnum;

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		reply = cpu_to_le16(0);
		अवरोध;

	हाल USB_RECIP_INTERFACE:
		reply = cpu_to_le16(0);
		अवरोध;

	हाल USB_RECIP_ENDPOINT:
		epnum = le16_to_cpu(ctrl->wIndex) & USB_ENDPOINT_NUMBER_MASK;
		hsep = &hsudc->ep[epnum];
		reply = cpu_to_le16(hsep->stopped ? 1 : 0);
		अवरोध;
	पूर्ण

	INIT_LIST_HEAD(&hsreq.queue);
	hsreq.req.length = 2;
	hsreq.req.buf = &reply;
	hsreq.req.actual = 0;
	hsreq.req.complete = शून्य;
	s3c_hsudc_ग_लिखो_fअगरo(hsep0, &hsreq);
पूर्ण

/**
 * s3c_hsudc_process_setup - Process control request received on endpoपूर्णांक 0.
 * @hsudc: Device controller on which control request has been received.
 *
 * Read the control request received on endpoपूर्णांक 0, decode it and handle
 * the request.
 */
अटल व्योम s3c_hsudc_process_setup(काष्ठा s3c_hsudc *hsudc)
अणु
	काष्ठा s3c_hsudc_ep *hsep = &hsudc->ep[0];
	काष्ठा usb_ctrlrequest ctrl = अणु0पूर्ण;
	पूर्णांक ret;

	s3c_hsudc_nuke_ep(hsep, -EPROTO);
	s3c_hsudc_पढ़ो_setup_pkt(hsudc, (u16 *)&ctrl);

	अगर (ctrl.bRequestType & USB_सूची_IN) अणु
		hsep->bEndpoपूर्णांकAddress |= USB_सूची_IN;
		hsudc->ep0state = DATA_STATE_XMIT;
	पूर्ण अन्यथा अणु
		hsep->bEndpoपूर्णांकAddress &= ~USB_सूची_IN;
		hsudc->ep0state = DATA_STATE_RECV;
	पूर्ण

	चयन (ctrl.bRequest) अणु
	हाल USB_REQ_SET_ADDRESS:
		अगर (ctrl.bRequestType != (USB_TYPE_STANDARD | USB_RECIP_DEVICE))
			अवरोध;
		hsudc->ep0state = WAIT_FOR_SETUP;
		वापस;

	हाल USB_REQ_GET_STATUS:
		अगर ((ctrl.bRequestType & USB_TYPE_MASK) != USB_TYPE_STANDARD)
			अवरोध;
		s3c_hsudc_process_req_status(hsudc, &ctrl);
		वापस;

	हाल USB_REQ_SET_FEATURE:
	हाल USB_REQ_CLEAR_FEATURE:
		अगर ((ctrl.bRequestType & USB_TYPE_MASK) != USB_TYPE_STANDARD)
			अवरोध;
		s3c_hsudc_handle_reqfeat(hsudc, &ctrl);
		hsudc->ep0state = WAIT_FOR_SETUP;
		वापस;
	पूर्ण

	अगर (hsudc->driver) अणु
		spin_unlock(&hsudc->lock);
		ret = hsudc->driver->setup(&hsudc->gadget, &ctrl);
		spin_lock(&hsudc->lock);

		अगर (ctrl.bRequest == USB_REQ_SET_CONFIGURATION) अणु
			hsep->bEndpoपूर्णांकAddress &= ~USB_सूची_IN;
			hsudc->ep0state = WAIT_FOR_SETUP;
		पूर्ण

		अगर (ret < 0) अणु
			dev_err(hsudc->dev, "setup failed, returned %d\n",
						ret);
			s3c_hsudc_set_halt(&hsep->ep, 1);
			hsudc->ep0state = WAIT_FOR_SETUP;
			hsep->bEndpoपूर्णांकAddress &= ~USB_सूची_IN;
		पूर्ण
	पूर्ण
पूर्ण

/** s3c_hsudc_handle_ep0_पूर्णांकr - Handle endpoपूर्णांक 0 पूर्णांकerrupt.
 * @hsudc: Device controller on which endpoपूर्णांक 0 पूर्णांकerrupt has occured.
 *
 * Handle endpoपूर्णांक 0 पूर्णांकerrupt when it occurs. EP0 पूर्णांकerrupt could occur
 * when a stall handshake is sent to host or data is sent/received on
 * endpoपूर्णांक 0.
 */
अटल व्योम s3c_hsudc_handle_ep0_पूर्णांकr(काष्ठा s3c_hsudc *hsudc)
अणु
	काष्ठा s3c_hsudc_ep *hsep = &hsudc->ep[0];
	काष्ठा s3c_hsudc_req *hsreq;
	u32 csr = पढ़ोl(hsudc->regs + S3C_EP0SR);
	u32 ecr;

	अगर (csr & S3C_EP0SR_STALL) अणु
		ecr = पढ़ोl(hsudc->regs + S3C_EP0CR);
		ecr &= ~(S3C_ECR_STALL | S3C_ECR_FLUSH);
		ग_लिखोl(ecr, hsudc->regs + S3C_EP0CR);

		ग_लिखोl(S3C_EP0SR_STALL, hsudc->regs + S3C_EP0SR);
		hsep->stopped = 0;

		s3c_hsudc_nuke_ep(hsep, -ECONNABORTED);
		hsudc->ep0state = WAIT_FOR_SETUP;
		hsep->bEndpoपूर्णांकAddress &= ~USB_सूची_IN;
		वापस;
	पूर्ण

	अगर (csr & S3C_EP0SR_TX_SUCCESS) अणु
		ग_लिखोl(S3C_EP0SR_TX_SUCCESS, hsudc->regs + S3C_EP0SR);
		अगर (ep_is_in(hsep)) अणु
			अगर (list_empty(&hsep->queue))
				वापस;

			hsreq = list_entry(hsep->queue.next,
					काष्ठा s3c_hsudc_req, queue);
			s3c_hsudc_ग_लिखो_fअगरo(hsep, hsreq);
		पूर्ण
	पूर्ण

	अगर (csr & S3C_EP0SR_RX_SUCCESS) अणु
		अगर (hsudc->ep0state == WAIT_FOR_SETUP)
			s3c_hsudc_process_setup(hsudc);
		अन्यथा अणु
			अगर (!ep_is_in(hsep)) अणु
				अगर (list_empty(&hsep->queue))
					वापस;
				hsreq = list_entry(hsep->queue.next,
					काष्ठा s3c_hsudc_req, queue);
				s3c_hsudc_पढ़ो_fअगरo(hsep, hsreq);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * s3c_hsudc_ep_enable - Enable a endpoपूर्णांक.
 * @_ep: The endpoपूर्णांक to be enabled.
 * @desc: Endpoपूर्णांक descriptor.
 *
 * Enables a endpoपूर्णांक when called from the gadget driver. Endpoपूर्णांक stall अगर
 * any is cleared, transfer type is configured and endpoपूर्णांक पूर्णांकerrupt is
 * enabled.
 */
अटल पूर्णांक s3c_hsudc_ep_enable(काष्ठा usb_ep *_ep,
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा s3c_hsudc_ep *hsep;
	काष्ठा s3c_hsudc *hsudc;
	अचिन्हित दीर्घ flags;
	u32 ecr = 0;

	hsep = our_ep(_ep);
	अगर (!_ep || !desc || _ep->name == ep0name
		|| desc->bDescriptorType != USB_DT_ENDPOINT
		|| hsep->bEndpoपूर्णांकAddress != desc->bEndpoपूर्णांकAddress
		|| ep_maxpacket(hsep) < usb_endpoपूर्णांक_maxp(desc))
		वापस -EINVAL;

	अगर ((desc->bmAttributes == USB_ENDPOINT_XFER_BULK
		&& usb_endpoपूर्णांक_maxp(desc) != ep_maxpacket(hsep))
		|| !desc->wMaxPacketSize)
		वापस -दुस्फल;

	hsudc = hsep->dev;
	अगर (!hsudc->driver || hsudc->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&hsudc->lock, flags);

	set_index(hsudc, hsep->bEndpoपूर्णांकAddress);
	ecr |= ((usb_endpoपूर्णांक_xfer_पूर्णांक(desc)) ? S3C_ECR_IEMS : S3C_ECR_DUEN);
	ग_लिखोl(ecr, hsudc->regs + S3C_ECR);

	hsep->stopped = hsep->wedge = 0;
	hsep->ep.desc = desc;
	hsep->ep.maxpacket = usb_endpoपूर्णांक_maxp(desc);

	s3c_hsudc_set_halt(_ep, 0);
	__set_bit(ep_index(hsep), hsudc->regs + S3C_EIER);

	spin_unlock_irqrestore(&hsudc->lock, flags);
	वापस 0;
पूर्ण

/**
 * s3c_hsudc_ep_disable - Disable a endpoपूर्णांक.
 * @_ep: The endpoपूर्णांक to be disabled.
 * @desc: Endpoपूर्णांक descriptor.
 *
 * Disables a endpoपूर्णांक when called from the gadget driver.
 */
अटल पूर्णांक s3c_hsudc_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा s3c_hsudc_ep *hsep = our_ep(_ep);
	काष्ठा s3c_hsudc *hsudc = hsep->dev;
	अचिन्हित दीर्घ flags;

	अगर (!_ep || !hsep->ep.desc)
		वापस -EINVAL;

	spin_lock_irqsave(&hsudc->lock, flags);

	set_index(hsudc, hsep->bEndpoपूर्णांकAddress);
	__clear_bit(ep_index(hsep), hsudc->regs + S3C_EIER);

	s3c_hsudc_nuke_ep(hsep, -ESHUTDOWN);

	hsep->ep.desc = शून्य;
	hsep->stopped = 1;

	spin_unlock_irqrestore(&hsudc->lock, flags);
	वापस 0;
पूर्ण

/**
 * s3c_hsudc_alloc_request - Allocate a new request.
 * @_ep: Endpoपूर्णांक क्रम which request is allocated (not used).
 * @gfp_flags: Flags used क्रम the allocation.
 *
 * Allocates a single transfer request काष्ठाure when called from gadget driver.
 */
अटल काष्ठा usb_request *s3c_hsudc_alloc_request(काष्ठा usb_ep *_ep,
						gfp_t gfp_flags)
अणु
	काष्ठा s3c_hsudc_req *hsreq;

	hsreq = kzalloc(माप(*hsreq), gfp_flags);
	अगर (!hsreq)
		वापस शून्य;

	INIT_LIST_HEAD(&hsreq->queue);
	वापस &hsreq->req;
पूर्ण

/**
 * s3c_hsudc_मुक्त_request - Deallocate a request.
 * @ep: Endpoपूर्णांक क्रम which request is deallocated (not used).
 * @_req: Request to be deallocated.
 *
 * Allocates a single transfer request काष्ठाure when called from gadget driver.
 */
अटल व्योम s3c_hsudc_मुक्त_request(काष्ठा usb_ep *ep, काष्ठा usb_request *_req)
अणु
	काष्ठा s3c_hsudc_req *hsreq;

	hsreq = our_req(_req);
	WARN_ON(!list_empty(&hsreq->queue));
	kमुक्त(hsreq);
पूर्ण

/**
 * s3c_hsudc_queue - Queue a transfer request क्रम the endpoपूर्णांक.
 * @_ep: Endpoपूर्णांक क्रम which the request is queued.
 * @_req: Request to be queued.
 * @gfp_flags: Not used.
 *
 * Start or enqueue a request क्रम a endpoपूर्णांक when called from gadget driver.
 */
अटल पूर्णांक s3c_hsudc_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
			gfp_t gfp_flags)
अणु
	काष्ठा s3c_hsudc_req *hsreq;
	काष्ठा s3c_hsudc_ep *hsep;
	काष्ठा s3c_hsudc *hsudc;
	अचिन्हित दीर्घ flags;
	u32 offset;
	u32 csr;

	hsreq = our_req(_req);
	अगर ((!_req || !_req->complete || !_req->buf ||
		!list_empty(&hsreq->queue)))
		वापस -EINVAL;

	hsep = our_ep(_ep);
	hsudc = hsep->dev;
	अगर (!hsudc->driver || hsudc->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&hsudc->lock, flags);
	set_index(hsudc, hsep->bEndpoपूर्णांकAddress);

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	अगर (!ep_index(hsep) && _req->length == 0) अणु
		hsudc->ep0state = WAIT_FOR_SETUP;
		s3c_hsudc_complete_request(hsep, hsreq, 0);
		spin_unlock_irqrestore(&hsudc->lock, flags);
		वापस 0;
	पूर्ण

	अगर (list_empty(&hsep->queue) && !hsep->stopped) अणु
		offset = (ep_index(hsep)) ? S3C_ESR : S3C_EP0SR;
		अगर (ep_is_in(hsep)) अणु
			csr = पढ़ोl(hsudc->regs + offset);
			अगर (!(csr & S3C_ESR_TX_SUCCESS) &&
				(s3c_hsudc_ग_लिखो_fअगरo(hsep, hsreq) == 1))
				hsreq = शून्य;
		पूर्ण अन्यथा अणु
			csr = पढ़ोl(hsudc->regs + offset);
			अगर ((csr & S3C_ESR_RX_SUCCESS)
				   && (s3c_hsudc_पढ़ो_fअगरo(hsep, hsreq) == 1))
				hsreq = शून्य;
		पूर्ण
	पूर्ण

	अगर (hsreq)
		list_add_tail(&hsreq->queue, &hsep->queue);

	spin_unlock_irqrestore(&hsudc->lock, flags);
	वापस 0;
पूर्ण

/**
 * s3c_hsudc_dequeue - Dequeue a transfer request from an endpoपूर्णांक.
 * @_ep: Endpoपूर्णांक from which the request is dequeued.
 * @_req: Request to be dequeued.
 *
 * Dequeue a request from a endpoपूर्णांक when called from gadget driver.
 */
अटल पूर्णांक s3c_hsudc_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा s3c_hsudc_ep *hsep = our_ep(_ep);
	काष्ठा s3c_hsudc *hsudc = hsep->dev;
	काष्ठा s3c_hsudc_req *hsreq;
	अचिन्हित दीर्घ flags;

	hsep = our_ep(_ep);
	अगर (!_ep || hsep->ep.name == ep0name)
		वापस -EINVAL;

	spin_lock_irqsave(&hsudc->lock, flags);

	list_क्रम_each_entry(hsreq, &hsep->queue, queue) अणु
		अगर (&hsreq->req == _req)
			अवरोध;
	पूर्ण
	अगर (&hsreq->req != _req) अणु
		spin_unlock_irqrestore(&hsudc->lock, flags);
		वापस -EINVAL;
	पूर्ण

	set_index(hsudc, hsep->bEndpoपूर्णांकAddress);
	s3c_hsudc_complete_request(hsep, hsreq, -ECONNRESET);

	spin_unlock_irqrestore(&hsudc->lock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops s3c_hsudc_ep_ops = अणु
	.enable = s3c_hsudc_ep_enable,
	.disable = s3c_hsudc_ep_disable,
	.alloc_request = s3c_hsudc_alloc_request,
	.मुक्त_request = s3c_hsudc_मुक्त_request,
	.queue = s3c_hsudc_queue,
	.dequeue = s3c_hsudc_dequeue,
	.set_halt = s3c_hsudc_set_halt,
	.set_wedge = s3c_hsudc_set_wedge,
पूर्ण;

/**
 * s3c_hsudc_initep - Initialize a endpoपूर्णांक to शेष state.
 * @hsudc - Reference to the device controller.
 * @hsep - Endpoपूर्णांक to be initialized.
 * @epnum - Address to be asचिन्हित to the endpoपूर्णांक.
 *
 * Initialize a endpoपूर्णांक with शेष configuration.
 */
अटल व्योम s3c_hsudc_initep(काष्ठा s3c_hsudc *hsudc,
				काष्ठा s3c_hsudc_ep *hsep, पूर्णांक epnum)
अणु
	अक्षर *dir;

	अगर ((epnum % 2) == 0) अणु
		dir = "out";
	पूर्ण अन्यथा अणु
		dir = "in";
		hsep->bEndpoपूर्णांकAddress = USB_सूची_IN;
	पूर्ण

	hsep->bEndpoपूर्णांकAddress |= epnum;
	अगर (epnum)
		snम_लिखो(hsep->name, माप(hsep->name), "ep%d%s", epnum, dir);
	अन्यथा
		snम_लिखो(hsep->name, माप(hsep->name), "%s", ep0name);

	INIT_LIST_HEAD(&hsep->queue);
	INIT_LIST_HEAD(&hsep->ep.ep_list);
	अगर (epnum)
		list_add_tail(&hsep->ep.ep_list, &hsudc->gadget.ep_list);

	hsep->dev = hsudc;
	hsep->ep.name = hsep->name;
	usb_ep_set_maxpacket_limit(&hsep->ep, epnum ? 512 : 64);
	hsep->ep.ops = &s3c_hsudc_ep_ops;
	hsep->fअगरo = hsudc->regs + S3C_BR(epnum);
	hsep->ep.desc = शून्य;
	hsep->stopped = 0;
	hsep->wedge = 0;

	अगर (epnum == 0) अणु
		hsep->ep.caps.type_control = true;
		hsep->ep.caps.dir_in = true;
		hsep->ep.caps.dir_out = true;
	पूर्ण अन्यथा अणु
		hsep->ep.caps.type_iso = true;
		hsep->ep.caps.type_bulk = true;
		hsep->ep.caps.type_पूर्णांक = true;
	पूर्ण

	अगर (epnum & 1)
		hsep->ep.caps.dir_in = true;
	अन्यथा
		hsep->ep.caps.dir_out = true;

	set_index(hsudc, epnum);
	ग_लिखोl(hsep->ep.maxpacket, hsudc->regs + S3C_MPR);
पूर्ण

/**
 * s3c_hsudc_setup_ep - Configure all endpoपूर्णांकs to शेष state.
 * @hsudc: Reference to device controller.
 *
 * Configures all endpoपूर्णांकs to शेष state.
 */
अटल व्योम s3c_hsudc_setup_ep(काष्ठा s3c_hsudc *hsudc)
अणु
	पूर्णांक epnum;

	hsudc->ep0state = WAIT_FOR_SETUP;
	INIT_LIST_HEAD(&hsudc->gadget.ep_list);
	क्रम (epnum = 0; epnum < hsudc->pd->epnum; epnum++)
		s3c_hsudc_initep(hsudc, &hsudc->ep[epnum], epnum);
पूर्ण

/**
 * s3c_hsudc_reconfig - Reconfigure the device controller to शेष state.
 * @hsudc: Reference to device controller.
 *
 * Reconfigures the device controller रेजिस्टरs to a शेष state.
 */
अटल व्योम s3c_hsudc_reconfig(काष्ठा s3c_hsudc *hsudc)
अणु
	ग_लिखोl(0xAA, hsudc->regs + S3C_EDR);
	ग_लिखोl(1, hsudc->regs + S3C_EIER);
	ग_लिखोl(0, hsudc->regs + S3C_TR);
	ग_लिखोl(S3C_SCR_DTZIEN_EN | S3C_SCR_RRD_EN | S3C_SCR_SUS_EN |
			S3C_SCR_RST_EN, hsudc->regs + S3C_SCR);
	ग_लिखोl(0, hsudc->regs + S3C_EP0CR);

	s3c_hsudc_setup_ep(hsudc);
पूर्ण

/**
 * s3c_hsudc_irq - Interrupt handler क्रम device controller.
 * @irq: Not used.
 * @_dev: Reference to the device controller.
 *
 * Interrupt handler क्रम the device controller. This handler handles controller
 * पूर्णांकerrupts and endpoपूर्णांक पूर्णांकerrupts.
 */
अटल irqवापस_t s3c_hsudc_irq(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा s3c_hsudc *hsudc = _dev;
	काष्ठा s3c_hsudc_ep *hsep;
	u32 ep_पूर्णांकr;
	u32 sys_status;
	u32 ep_idx;

	spin_lock(&hsudc->lock);

	sys_status = पढ़ोl(hsudc->regs + S3C_SSR);
	ep_पूर्णांकr = पढ़ोl(hsudc->regs + S3C_EIR) & 0x3FF;

	अगर (!ep_पूर्णांकr && !(sys_status & S3C_SSR_DTZIEN_EN)) अणु
		spin_unlock(&hsudc->lock);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (sys_status) अणु
		अगर (sys_status & S3C_SSR_VBUSON)
			ग_लिखोl(S3C_SSR_VBUSON, hsudc->regs + S3C_SSR);

		अगर (sys_status & S3C_SSR_ERR)
			ग_लिखोl(S3C_SSR_ERR, hsudc->regs + S3C_SSR);

		अगर (sys_status & S3C_SSR_SDE) अणु
			ग_लिखोl(S3C_SSR_SDE, hsudc->regs + S3C_SSR);
			hsudc->gadget.speed = (sys_status & S3C_SSR_HSP) ?
				USB_SPEED_HIGH : USB_SPEED_FULL;
		पूर्ण

		अगर (sys_status & S3C_SSR_SUSPEND) अणु
			ग_लिखोl(S3C_SSR_SUSPEND, hsudc->regs + S3C_SSR);
			अगर (hsudc->gadget.speed != USB_SPEED_UNKNOWN
				&& hsudc->driver && hsudc->driver->suspend)
				hsudc->driver->suspend(&hsudc->gadget);
		पूर्ण

		अगर (sys_status & S3C_SSR_RESUME) अणु
			ग_लिखोl(S3C_SSR_RESUME, hsudc->regs + S3C_SSR);
			अगर (hsudc->gadget.speed != USB_SPEED_UNKNOWN
				&& hsudc->driver && hsudc->driver->resume)
				hsudc->driver->resume(&hsudc->gadget);
		पूर्ण

		अगर (sys_status & S3C_SSR_RESET) अणु
			ग_लिखोl(S3C_SSR_RESET, hsudc->regs + S3C_SSR);
			क्रम (ep_idx = 0; ep_idx < hsudc->pd->epnum; ep_idx++) अणु
				hsep = &hsudc->ep[ep_idx];
				hsep->stopped = 1;
				s3c_hsudc_nuke_ep(hsep, -ECONNRESET);
			पूर्ण
			s3c_hsudc_reconfig(hsudc);
			hsudc->ep0state = WAIT_FOR_SETUP;
		पूर्ण
	पूर्ण

	अगर (ep_पूर्णांकr & S3C_EIR_EP0) अणु
		ग_लिखोl(S3C_EIR_EP0, hsudc->regs + S3C_EIR);
		set_index(hsudc, 0);
		s3c_hsudc_handle_ep0_पूर्णांकr(hsudc);
	पूर्ण

	ep_पूर्णांकr >>= 1;
	ep_idx = 1;
	जबतक (ep_पूर्णांकr) अणु
		अगर (ep_पूर्णांकr & 1)  अणु
			hsep = &hsudc->ep[ep_idx];
			set_index(hsudc, ep_idx);
			ग_लिखोl(1 << ep_idx, hsudc->regs + S3C_EIR);
			अगर (ep_is_in(hsep))
				s3c_hsudc_epin_पूर्णांकr(hsudc, ep_idx);
			अन्यथा
				s3c_hsudc_epout_पूर्णांकr(hsudc, ep_idx);
		पूर्ण
		ep_पूर्णांकr >>= 1;
		ep_idx++;
	पूर्ण

	spin_unlock(&hsudc->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक s3c_hsudc_start(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा s3c_hsudc *hsudc = to_hsudc(gadget);
	पूर्णांक ret;

	अगर (!driver
		|| driver->max_speed < USB_SPEED_FULL
		|| !driver->setup)
		वापस -EINVAL;

	अगर (!hsudc)
		वापस -ENODEV;

	अगर (hsudc->driver)
		वापस -EBUSY;

	hsudc->driver = driver;

	ret = regulator_bulk_enable(ARRAY_SIZE(hsudc->supplies),
				    hsudc->supplies);
	अगर (ret != 0) अणु
		dev_err(hsudc->dev, "failed to enable supplies: %d\n", ret);
		जाओ err_supplies;
	पूर्ण

	/* connect to bus through transceiver */
	अगर (!IS_ERR_OR_शून्य(hsudc->transceiver)) अणु
		ret = otg_set_peripheral(hsudc->transceiver->otg,
					&hsudc->gadget);
		अगर (ret) अणु
			dev_err(hsudc->dev, "%s: can't bind to transceiver\n",
					hsudc->gadget.name);
			जाओ err_otg;
		पूर्ण
	पूर्ण

	enable_irq(hsudc->irq);
	s3c_hsudc_reconfig(hsudc);

	pm_runसमय_get_sync(hsudc->dev);

	अगर (hsudc->pd->phy_init)
		hsudc->pd->phy_init();
	अगर (hsudc->pd->gpio_init)
		hsudc->pd->gpio_init();

	वापस 0;
err_otg:
	regulator_bulk_disable(ARRAY_SIZE(hsudc->supplies), hsudc->supplies);
err_supplies:
	hsudc->driver = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक s3c_hsudc_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा s3c_hsudc *hsudc = to_hsudc(gadget);
	अचिन्हित दीर्घ flags;

	अगर (!hsudc)
		वापस -ENODEV;

	spin_lock_irqsave(&hsudc->lock, flags);
	hsudc->gadget.speed = USB_SPEED_UNKNOWN;
	अगर (hsudc->pd->phy_uninit)
		hsudc->pd->phy_uninit();

	pm_runसमय_put(hsudc->dev);

	अगर (hsudc->pd->gpio_uninit)
		hsudc->pd->gpio_uninit();
	s3c_hsudc_stop_activity(hsudc);
	spin_unlock_irqrestore(&hsudc->lock, flags);

	अगर (!IS_ERR_OR_शून्य(hsudc->transceiver))
		(व्योम) otg_set_peripheral(hsudc->transceiver->otg, शून्य);

	disable_irq(hsudc->irq);

	regulator_bulk_disable(ARRAY_SIZE(hsudc->supplies), hsudc->supplies);
	hsudc->driver = शून्य;

	वापस 0;
पूर्ण

अटल अंतरभूत u32 s3c_hsudc_पढ़ो_frameno(काष्ठा s3c_hsudc *hsudc)
अणु
	वापस पढ़ोl(hsudc->regs + S3C_FNR) & 0x3FF;
पूर्ण

अटल पूर्णांक s3c_hsudc_gadget_getframe(काष्ठा usb_gadget *gadget)
अणु
	वापस s3c_hsudc_पढ़ो_frameno(to_hsudc(gadget));
पूर्ण

अटल पूर्णांक s3c_hsudc_vbus_draw(काष्ठा usb_gadget *gadget, अचिन्हित mA)
अणु
	काष्ठा s3c_hsudc *hsudc = to_hsudc(gadget);

	अगर (!hsudc)
		वापस -ENODEV;

	अगर (!IS_ERR_OR_शून्य(hsudc->transceiver))
		वापस usb_phy_set_घातer(hsudc->transceiver, mA);

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops s3c_hsudc_gadget_ops = अणु
	.get_frame	= s3c_hsudc_gadget_getframe,
	.udc_start	= s3c_hsudc_start,
	.udc_stop	= s3c_hsudc_stop,
	.vbus_draw	= s3c_hsudc_vbus_draw,
पूर्ण;

अटल पूर्णांक s3c_hsudc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा s3c_hsudc *hsudc;
	काष्ठा s3c24xx_hsudc_platdata *pd = dev_get_platdata(&pdev->dev);
	पूर्णांक ret, i;

	hsudc = devm_kzalloc(&pdev->dev, माप(काष्ठा s3c_hsudc) +
			माप(काष्ठा s3c_hsudc_ep) * pd->epnum,
			GFP_KERNEL);
	अगर (!hsudc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, dev);
	hsudc->dev = dev;
	hsudc->pd = dev_get_platdata(&pdev->dev);

	hsudc->transceiver = usb_get_phy(USB_PHY_TYPE_USB2);

	क्रम (i = 0; i < ARRAY_SIZE(hsudc->supplies); i++)
		hsudc->supplies[i].supply = s3c_hsudc_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(hsudc->supplies),
				 hsudc->supplies);
	अगर (ret != 0) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to request supplies: %d\n", ret);
		जाओ err_supplies;
	पूर्ण

	hsudc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hsudc->regs)) अणु
		ret = PTR_ERR(hsudc->regs);
		जाओ err_res;
	पूर्ण

	spin_lock_init(&hsudc->lock);

	hsudc->gadget.max_speed = USB_SPEED_HIGH;
	hsudc->gadget.ops = &s3c_hsudc_gadget_ops;
	hsudc->gadget.name = dev_name(dev);
	hsudc->gadget.ep0 = &hsudc->ep[0].ep;
	hsudc->gadget.is_otg = 0;
	hsudc->gadget.is_a_peripheral = 0;
	hsudc->gadget.speed = USB_SPEED_UNKNOWN;

	s3c_hsudc_setup_ep(hsudc);

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ err_res;
	hsudc->irq = ret;

	ret = devm_request_irq(&pdev->dev, hsudc->irq, s3c_hsudc_irq, 0,
				driver_name, hsudc);
	अगर (ret < 0) अणु
		dev_err(dev, "irq request failed\n");
		जाओ err_res;
	पूर्ण

	hsudc->uclk = devm_clk_get(&pdev->dev, "usb-device");
	अगर (IS_ERR(hsudc->uclk)) अणु
		dev_err(dev, "failed to find usb-device clock source\n");
		ret = PTR_ERR(hsudc->uclk);
		जाओ err_res;
	पूर्ण
	clk_enable(hsudc->uclk);

	local_irq_disable();

	disable_irq(hsudc->irq);
	local_irq_enable();

	ret = usb_add_gadget_udc(&pdev->dev, &hsudc->gadget);
	अगर (ret)
		जाओ err_add_udc;

	pm_runसमय_enable(dev);

	वापस 0;
err_add_udc:
	clk_disable(hsudc->uclk);
err_res:
	अगर (!IS_ERR_OR_शून्य(hsudc->transceiver))
		usb_put_phy(hsudc->transceiver);

err_supplies:
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver s3c_hsudc_driver = अणु
	.driver		= अणु
		.name	= "s3c-hsudc",
	पूर्ण,
	.probe		= s3c_hsudc_probe,
पूर्ण;

module_platक्रमm_driver(s3c_hsudc_driver);

MODULE_DESCRIPTION("Samsung S3C24XX USB high-speed controller driver");
MODULE_AUTHOR("Thomas Abraham <thomas.ab@samsung.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:s3c-hsudc");
