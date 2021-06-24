<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * MAX3420 Device Controller driver क्रम USB.
 *
 * Author: Jaswinder Singh Brar <jaswinder.singh@linaro.org>
 * (C) Copyright 2019-2020 Linaro Ltd
 *
 * Based on:
 *	o MAX3420E datasheet
 *		https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX3420E.pdf
 *	o MAX342अणु0,1पूर्णE Programming Guides
 *		https://pdfserv.maximपूर्णांकegrated.com/en/an/AN3598.pdf
 *		https://pdfserv.maximपूर्णांकegrated.com/en/an/AN3785.pdf
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/gpio/consumer.h>

#घोषणा MAX3420_MAX_EPS		4
#घोषणा MAX3420_EP_MAX_PACKET		64  /* Same क्रम all Endpoपूर्णांकs */
#घोषणा MAX3420_EPNAME_SIZE		16  /* Buffer size क्रम endpoपूर्णांक name */

#घोषणा MAX3420_ACKSTAT		BIT(0)

#घोषणा MAX3420_SPI_सूची_RD	0	/* पढ़ो रेजिस्टर from MAX3420 */
#घोषणा MAX3420_SPI_सूची_WR	1	/* ग_लिखो रेजिस्टर to MAX3420 */

/* SPI commands: */
#घोषणा MAX3420_SPI_सूची_SHIFT	1
#घोषणा MAX3420_SPI_REG_SHIFT	3

#घोषणा MAX3420_REG_EP0FIFO	0
#घोषणा MAX3420_REG_EP1FIFO	1
#घोषणा MAX3420_REG_EP2FIFO	2
#घोषणा MAX3420_REG_EP3FIFO	3
#घोषणा MAX3420_REG_SUDFIFO	4
#घोषणा MAX3420_REG_EP0BC	5
#घोषणा MAX3420_REG_EP1BC	6
#घोषणा MAX3420_REG_EP2BC	7
#घोषणा MAX3420_REG_EP3BC	8

#घोषणा MAX3420_REG_EPSTALLS	9
	#घोषणा ACKSTAT		BIT(6)
	#घोषणा STLSTAT		BIT(5)
	#घोषणा STLEP3IN	BIT(4)
	#घोषणा STLEP2IN	BIT(3)
	#घोषणा STLEP1OUT	BIT(2)
	#घोषणा STLEP0OUT	BIT(1)
	#घोषणा STLEP0IN	BIT(0)

#घोषणा MAX3420_REG_CLRTOGS	10
	#घोषणा EP3DISAB	BIT(7)
	#घोषणा EP2DISAB	BIT(6)
	#घोषणा EP1DISAB	BIT(5)
	#घोषणा CTGEP3IN	BIT(4)
	#घोषणा CTGEP2IN	BIT(3)
	#घोषणा CTGEP1OUT	BIT(2)

#घोषणा MAX3420_REG_EPIRQ	11
#घोषणा MAX3420_REG_EPIEN	12
	#घोषणा SUDAVIRQ	BIT(5)
	#घोषणा IN3BAVIRQ	BIT(4)
	#घोषणा IN2BAVIRQ	BIT(3)
	#घोषणा OUT1DAVIRQ	BIT(2)
	#घोषणा OUT0DAVIRQ	BIT(1)
	#घोषणा IN0BAVIRQ	BIT(0)

#घोषणा MAX3420_REG_USBIRQ	13
#घोषणा MAX3420_REG_USBIEN	14
	#घोषणा OSCOKIRQ	BIT(0)
	#घोषणा RWUDNIRQ	BIT(1)
	#घोषणा BUSACTIRQ	BIT(2)
	#घोषणा URESIRQ		BIT(3)
	#घोषणा SUSPIRQ		BIT(4)
	#घोषणा NOVBUSIRQ	BIT(5)
	#घोषणा VBUSIRQ		BIT(6)
	#घोषणा URESDNIRQ	BIT(7)

#घोषणा MAX3420_REG_USBCTL	15
	#घोषणा HOSCSTEN	BIT(7)
	#घोषणा VBGATE		BIT(6)
	#घोषणा CHIPRES		BIT(5)
	#घोषणा PWRDOWN		BIT(4)
	#घोषणा CONNECT		BIT(3)
	#घोषणा SIGRWU		BIT(2)

#घोषणा MAX3420_REG_CPUCTL	16
	#घोषणा IE		BIT(0)

#घोषणा MAX3420_REG_PINCTL	17
	#घोषणा EP3INAK		BIT(7)
	#घोषणा EP2INAK		BIT(6)
	#घोषणा EP0INAK		BIT(5)
	#घोषणा FDUPSPI		BIT(4)
	#घोषणा INTLEVEL	BIT(3)
	#घोषणा POSINT		BIT(2)
	#घोषणा GPXB		BIT(1)
	#घोषणा GPXA		BIT(0)

#घोषणा MAX3420_REG_REVISION	18

#घोषणा MAX3420_REG_FNADDR	19
	#घोषणा FNADDR_MASK	0x7f

#घोषणा MAX3420_REG_IOPINS	20
#घोषणा MAX3420_REG_IOPINS2	21
#घोषणा MAX3420_REG_GPINIRQ	22
#घोषणा MAX3420_REG_GPINIEN	23
#घोषणा MAX3420_REG_GPINPOL	24
#घोषणा MAX3420_REG_HIRQ	25
#घोषणा MAX3420_REG_HIEN	26
#घोषणा MAX3420_REG_MODE	27
#घोषणा MAX3420_REG_PERADDR	28
#घोषणा MAX3420_REG_HCTL	29
#घोषणा MAX3420_REG_HXFR	30
#घोषणा MAX3420_REG_HRSL	31

#घोषणा ENABLE_IRQ	BIT(0)
#घोषणा IOPIN_UPDATE	BIT(1)
#घोषणा REMOTE_WAKEUP	BIT(2)
#घोषणा CONNECT_HOST	GENMASK(4, 3)
#घोषणा	HCONNECT	(1 << 3)
#घोषणा	HDISCONNECT	(3 << 3)
#घोषणा UDC_START	GENMASK(6, 5)
#घोषणा	START		(1 << 5)
#घोषणा	STOP		(3 << 5)
#घोषणा ENABLE_EP	GENMASK(8, 7)
#घोषणा	ENABLE		(1 << 7)
#घोषणा	DISABLE		(3 << 7)
#घोषणा STALL_EP	GENMASK(10, 9)
#घोषणा	STALL		(1 << 9)
#घोषणा	UNSTALL		(3 << 9)

#घोषणा MAX3420_CMD(c)		FIELD_PREP(GENMASK(7, 3), c)
#घोषणा MAX3420_SPI_CMD_RD(c)	(MAX3420_CMD(c) | (0 << 1))
#घोषणा MAX3420_SPI_CMD_WR(c)	(MAX3420_CMD(c) | (1 << 1))

काष्ठा max3420_req अणु
	काष्ठा usb_request usb_req;
	काष्ठा list_head queue;
	काष्ठा max3420_ep *ep;
पूर्ण;

काष्ठा max3420_ep अणु
	काष्ठा usb_ep ep_usb;
	काष्ठा max3420_udc *udc;
	काष्ठा list_head queue;
	अक्षर name[MAX3420_EPNAME_SIZE];
	अचिन्हित पूर्णांक maxpacket;
	spinlock_t lock;
	पूर्णांक halted;
	u32 toकरो;
	पूर्णांक id;
पूर्ण;

काष्ठा max3420_udc अणु
	काष्ठा usb_gadget gadget;
	काष्ठा max3420_ep ep[MAX3420_MAX_EPS];
	काष्ठा usb_gadget_driver *driver;
	काष्ठा task_काष्ठा *thपढ़ो_task;
	पूर्णांक remote_wkp, is_selfघातered;
	bool vbus_active, softconnect;
	काष्ठा usb_ctrlrequest setup;
	काष्ठा mutex spi_bus_mutex;
	काष्ठा max3420_req ep0req;
	काष्ठा spi_device *spi;
	काष्ठा device *dev;
	spinlock_t lock;
	bool suspended;
	u8 ep0buf[64];
	u32 toकरो;
पूर्ण;

#घोषणा to_max3420_req(r)	container_of((r), काष्ठा max3420_req, usb_req)
#घोषणा to_max3420_ep(e)	container_of((e), काष्ठा max3420_ep, ep_usb)
#घोषणा to_udc(g)		container_of((g), काष्ठा max3420_udc, gadget)

#घोषणा DRIVER_DESC     "MAX3420 USB Device-Mode Driver"
अटल स्थिर अक्षर driver_name[] = "max3420-udc";

/* Control endpoपूर्णांक configuration.*/
अटल स्थिर काष्ठा usb_endpoपूर्णांक_descriptor ep0_desc = अणु
	.bEndpoपूर्णांकAddress	= USB_सूची_OUT,
	.bmAttributes		= USB_ENDPOINT_XFER_CONTROL,
	.wMaxPacketSize		= cpu_to_le16(MAX3420_EP_MAX_PACKET),
पूर्ण;

अटल व्योम spi_ack_ctrl(काष्ठा max3420_udc *udc)
अणु
	काष्ठा spi_device *spi = udc->spi;
	काष्ठा spi_transfer transfer;
	काष्ठा spi_message msg;
	u8 txdata[1];

	स_रखो(&transfer, 0, माप(transfer));

	spi_message_init(&msg);

	txdata[0] = MAX3420_ACKSTAT;
	transfer.tx_buf = txdata;
	transfer.len = 1;

	spi_message_add_tail(&transfer, &msg);
	spi_sync(spi, &msg);
पूर्ण

अटल u8 spi_rd8_ack(काष्ठा max3420_udc *udc, u8 reg, पूर्णांक actstat)
अणु
	काष्ठा spi_device *spi = udc->spi;
	काष्ठा spi_transfer transfer;
	काष्ठा spi_message msg;
	u8 txdata[2], rxdata[2];

	स_रखो(&transfer, 0, माप(transfer));

	spi_message_init(&msg);

	txdata[0] = MAX3420_SPI_CMD_RD(reg) | (actstat ? MAX3420_ACKSTAT : 0);
	transfer.tx_buf = txdata;
	transfer.rx_buf = rxdata;
	transfer.len = 2;

	spi_message_add_tail(&transfer, &msg);
	spi_sync(spi, &msg);

	वापस rxdata[1];
पूर्ण

अटल u8 spi_rd8(काष्ठा max3420_udc *udc, u8 reg)
अणु
	वापस spi_rd8_ack(udc, reg, 0);
पूर्ण

अटल व्योम spi_wr8_ack(काष्ठा max3420_udc *udc, u8 reg, u8 val, पूर्णांक actstat)
अणु
	काष्ठा spi_device *spi = udc->spi;
	काष्ठा spi_transfer transfer;
	काष्ठा spi_message msg;
	u8 txdata[2];

	स_रखो(&transfer, 0, माप(transfer));

	spi_message_init(&msg);

	txdata[0] = MAX3420_SPI_CMD_WR(reg) | (actstat ? MAX3420_ACKSTAT : 0);
	txdata[1] = val;

	transfer.tx_buf = txdata;
	transfer.len = 2;

	spi_message_add_tail(&transfer, &msg);
	spi_sync(spi, &msg);
पूर्ण

अटल व्योम spi_wr8(काष्ठा max3420_udc *udc, u8 reg, u8 val)
अणु
	spi_wr8_ack(udc, reg, val, 0);
पूर्ण

अटल व्योम spi_rd_buf(काष्ठा max3420_udc *udc, u8 reg, व्योम *buf, u8 len)
अणु
	काष्ठा spi_device *spi = udc->spi;
	काष्ठा spi_transfer transfer;
	काष्ठा spi_message msg;
	u8 local_buf[MAX3420_EP_MAX_PACKET + 1] = अणुपूर्ण;

	स_रखो(&transfer, 0, माप(transfer));

	spi_message_init(&msg);

	local_buf[0] = MAX3420_SPI_CMD_RD(reg);
	transfer.tx_buf = &local_buf[0];
	transfer.rx_buf = &local_buf[0];
	transfer.len = len + 1;

	spi_message_add_tail(&transfer, &msg);
	spi_sync(spi, &msg);

	स_नकल(buf, &local_buf[1], len);
पूर्ण

अटल व्योम spi_wr_buf(काष्ठा max3420_udc *udc, u8 reg, व्योम *buf, u8 len)
अणु
	काष्ठा spi_device *spi = udc->spi;
	काष्ठा spi_transfer transfer;
	काष्ठा spi_message msg;
	u8 local_buf[MAX3420_EP_MAX_PACKET + 1] = अणुपूर्ण;

	स_रखो(&transfer, 0, माप(transfer));

	spi_message_init(&msg);

	local_buf[0] = MAX3420_SPI_CMD_WR(reg);
	स_नकल(&local_buf[1], buf, len);

	transfer.tx_buf = local_buf;
	transfer.len = len + 1;

	spi_message_add_tail(&transfer, &msg);
	spi_sync(spi, &msg);
पूर्ण

अटल पूर्णांक spi_max3420_enable(काष्ठा max3420_ep *ep)
अणु
	काष्ठा max3420_udc *udc = ep->udc;
	अचिन्हित दीर्घ flags;
	u8 epdis, epien;
	पूर्णांक toकरो;

	spin_lock_irqsave(&ep->lock, flags);
	toकरो = ep->toकरो & ENABLE_EP;
	ep->toकरो &= ~ENABLE_EP;
	spin_unlock_irqrestore(&ep->lock, flags);

	अगर (!toकरो || ep->id == 0)
		वापस false;

	epien = spi_rd8(udc, MAX3420_REG_EPIEN);
	epdis = spi_rd8(udc, MAX3420_REG_CLRTOGS);

	अगर (toकरो == ENABLE) अणु
		epdis &= ~BIT(ep->id + 4);
		epien |= BIT(ep->id + 1);
	पूर्ण अन्यथा अणु
		epdis |= BIT(ep->id + 4);
		epien &= ~BIT(ep->id + 1);
	पूर्ण

	spi_wr8(udc, MAX3420_REG_CLRTOGS, epdis);
	spi_wr8(udc, MAX3420_REG_EPIEN, epien);

	वापस true;
पूर्ण

अटल पूर्णांक spi_max3420_stall(काष्ठा max3420_ep *ep)
अणु
	काष्ठा max3420_udc *udc = ep->udc;
	अचिन्हित दीर्घ flags;
	u8 epstalls;
	पूर्णांक toकरो;

	spin_lock_irqsave(&ep->lock, flags);
	toकरो = ep->toकरो & STALL_EP;
	ep->toकरो &= ~STALL_EP;
	spin_unlock_irqrestore(&ep->lock, flags);

	अगर (!toकरो || ep->id == 0)
		वापस false;

	epstalls = spi_rd8(udc, MAX3420_REG_EPSTALLS);
	अगर (toकरो == STALL) अणु
		ep->halted = 1;
		epstalls |= BIT(ep->id + 1);
	पूर्ण अन्यथा अणु
		u8 clrtogs;

		ep->halted = 0;
		epstalls &= ~BIT(ep->id + 1);
		clrtogs = spi_rd8(udc, MAX3420_REG_CLRTOGS);
		clrtogs |= BIT(ep->id + 1);
		spi_wr8(udc, MAX3420_REG_CLRTOGS, clrtogs);
	पूर्ण
	spi_wr8(udc, MAX3420_REG_EPSTALLS, epstalls | ACKSTAT);

	वापस true;
पूर्ण

अटल पूर्णांक spi_max3420_rwkup(काष्ठा max3420_udc *udc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक wake_remote;
	u8 usbctl;

	spin_lock_irqsave(&udc->lock, flags);
	wake_remote = udc->toकरो & REMOTE_WAKEUP;
	udc->toकरो &= ~REMOTE_WAKEUP;
	spin_unlock_irqrestore(&udc->lock, flags);

	अगर (!wake_remote || !udc->suspended)
		वापस false;

	/* Set Remote-WkUp Signal*/
	usbctl = spi_rd8(udc, MAX3420_REG_USBCTL);
	usbctl |= SIGRWU;
	spi_wr8(udc, MAX3420_REG_USBCTL, usbctl);

	msleep_पूर्णांकerruptible(5);

	/* Clear Remote-WkUp Signal*/
	usbctl = spi_rd8(udc, MAX3420_REG_USBCTL);
	usbctl &= ~SIGRWU;
	spi_wr8(udc, MAX3420_REG_USBCTL, usbctl);

	udc->suspended = false;

	वापस true;
पूर्ण

अटल व्योम max3420_nuke(काष्ठा max3420_ep *ep, पूर्णांक status);
अटल व्योम __max3420_stop(काष्ठा max3420_udc *udc)
अणु
	u8 val;
	पूर्णांक i;

	/* clear all pending requests */
	क्रम (i = 1; i < MAX3420_MAX_EPS; i++)
		max3420_nuke(&udc->ep[i], -ECONNRESET);

	/* Disable IRQ to CPU */
	spi_wr8(udc, MAX3420_REG_CPUCTL, 0);

	val = spi_rd8(udc, MAX3420_REG_USBCTL);
	val |= PWRDOWN;
	अगर (udc->is_selfघातered)
		val &= ~HOSCSTEN;
	अन्यथा
		val |= HOSCSTEN;
	spi_wr8(udc, MAX3420_REG_USBCTL, val);
पूर्ण

अटल व्योम __max3420_start(काष्ठा max3420_udc *udc)
अणु
	u8 val;

	/* Need this delay अगर bus-घातered,
	 * but even क्रम self-घातered it helps stability
	 */
	msleep_पूर्णांकerruptible(250);

	/* configure SPI */
	spi_wr8(udc, MAX3420_REG_PINCTL, FDUPSPI);

	/* Chip Reset */
	spi_wr8(udc, MAX3420_REG_USBCTL, CHIPRES);
	msleep_पूर्णांकerruptible(5);
	spi_wr8(udc, MAX3420_REG_USBCTL, 0);

	/* Poll क्रम OSC to stabilize */
	जबतक (1) अणु
		val = spi_rd8(udc, MAX3420_REG_USBIRQ);
		अगर (val & OSCOKIRQ)
			अवरोध;
		cond_resched();
	पूर्ण

	/* Enable PULL-UP only when Vbus detected */
	val = spi_rd8(udc, MAX3420_REG_USBCTL);
	val |= VBGATE | CONNECT;
	spi_wr8(udc, MAX3420_REG_USBCTL, val);

	val = URESDNIRQ | URESIRQ;
	अगर (udc->is_selfघातered)
		val |= NOVBUSIRQ;
	spi_wr8(udc, MAX3420_REG_USBIEN, val);

	/* Enable only EP0 पूर्णांकerrupts */
	val = IN0BAVIRQ | OUT0DAVIRQ | SUDAVIRQ;
	spi_wr8(udc, MAX3420_REG_EPIEN, val);

	/* Enable IRQ to CPU */
	spi_wr8(udc, MAX3420_REG_CPUCTL, IE);
पूर्ण

अटल पूर्णांक max3420_start(काष्ठा max3420_udc *udc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक toकरो;

	spin_lock_irqsave(&udc->lock, flags);
	toकरो = udc->toकरो & UDC_START;
	udc->toकरो &= ~UDC_START;
	spin_unlock_irqrestore(&udc->lock, flags);

	अगर (!toकरो)
		वापस false;

	अगर (udc->vbus_active && udc->softconnect)
		__max3420_start(udc);
	अन्यथा
		__max3420_stop(udc);

	वापस true;
पूर्ण

अटल irqवापस_t max3420_vbus_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा max3420_udc *udc = dev_id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);
	/* its a vbus change पूर्णांकerrupt */
	udc->vbus_active = !udc->vbus_active;
	udc->toकरो |= UDC_START;
	usb_udc_vbus_handler(&udc->gadget, udc->vbus_active);
	usb_gadget_set_state(&udc->gadget, udc->vbus_active
			     ? USB_STATE_POWERED : USB_STATE_NOTATTACHED);
	spin_unlock_irqrestore(&udc->lock, flags);

	अगर (udc->thपढ़ो_task &&
	    udc->thपढ़ो_task->state != TASK_RUNNING)
		wake_up_process(udc->thपढ़ो_task);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t max3420_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा max3420_udc *udc = dev_id;
	काष्ठा spi_device *spi = udc->spi;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);
	अगर ((udc->toकरो & ENABLE_IRQ) == 0) अणु
		disable_irq_nosync(spi->irq);
		udc->toकरो |= ENABLE_IRQ;
	पूर्ण
	spin_unlock_irqrestore(&udc->lock, flags);

	अगर (udc->thपढ़ो_task &&
	    udc->thपढ़ो_task->state != TASK_RUNNING)
		wake_up_process(udc->thपढ़ो_task);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम max3420_माला_लोtatus(काष्ठा max3420_udc *udc)
अणु
	काष्ठा max3420_ep *ep;
	u16 status = 0;

	चयन (udc->setup.bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		/* Get device status */
		status = udc->gadget.is_selfघातered << USB_DEVICE_SELF_POWERED;
		status |= (udc->remote_wkp << USB_DEVICE_REMOTE_WAKEUP);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		अगर (udc->driver->setup(&udc->gadget, &udc->setup) < 0)
			जाओ stall;
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		ep = &udc->ep[udc->setup.wIndex & USB_ENDPOINT_NUMBER_MASK];
		अगर (udc->setup.wIndex & USB_सूची_IN) अणु
			अगर (!ep->ep_usb.caps.dir_in)
				जाओ stall;
		पूर्ण अन्यथा अणु
			अगर (!ep->ep_usb.caps.dir_out)
				जाओ stall;
		पूर्ण
		अगर (ep->halted)
			status = 1 << USB_ENDPOINT_HALT;
		अवरोध;
	शेष:
		जाओ stall;
	पूर्ण

	status = cpu_to_le16(status);
	spi_wr_buf(udc, MAX3420_REG_EP0FIFO, &status, 2);
	spi_wr8_ack(udc, MAX3420_REG_EP0BC, 2, 1);
	वापस;
stall:
	dev_err(udc->dev, "Can't respond to getstatus request\n");
	spi_wr8(udc, MAX3420_REG_EPSTALLS, STLEP0IN | STLEP0OUT | STLSTAT);
पूर्ण

अटल व्योम max3420_set_clear_feature(काष्ठा max3420_udc *udc)
अणु
	काष्ठा max3420_ep *ep;
	पूर्णांक set = udc->setup.bRequest == USB_REQ_SET_FEATURE;
	अचिन्हित दीर्घ flags;
	पूर्णांक id;

	चयन (udc->setup.bRequestType) अणु
	हाल USB_RECIP_DEVICE:
		अगर (udc->setup.wValue != USB_DEVICE_REMOTE_WAKEUP)
			अवरोध;

		अगर (udc->setup.bRequest == USB_REQ_SET_FEATURE)
			udc->remote_wkp = 1;
		अन्यथा
			udc->remote_wkp = 0;

		वापस spi_ack_ctrl(udc);

	हाल USB_RECIP_ENDPOINT:
		अगर (udc->setup.wValue != USB_ENDPOINT_HALT)
			अवरोध;

		id = udc->setup.wIndex & USB_ENDPOINT_NUMBER_MASK;
		ep = &udc->ep[id];

		spin_lock_irqsave(&ep->lock, flags);
		ep->toकरो &= ~STALL_EP;
		अगर (set)
			ep->toकरो |= STALL;
		अन्यथा
			ep->toकरो |= UNSTALL;
		spin_unlock_irqrestore(&ep->lock, flags);

		spi_max3420_stall(ep);
		वापस;
	शेष:
		अवरोध;
	पूर्ण

	dev_err(udc->dev, "Can't respond to SET/CLEAR FEATURE\n");
	spi_wr8(udc, MAX3420_REG_EPSTALLS, STLEP0IN | STLEP0OUT | STLSTAT);
पूर्ण

अटल व्योम max3420_handle_setup(काष्ठा max3420_udc *udc)
अणु
	काष्ठा usb_ctrlrequest setup;

	spi_rd_buf(udc, MAX3420_REG_SUDFIFO, (व्योम *)&setup, 8);

	udc->setup = setup;
	udc->setup.wValue = cpu_to_le16(setup.wValue);
	udc->setup.wIndex = cpu_to_le16(setup.wIndex);
	udc->setup.wLength = cpu_to_le16(setup.wLength);

	चयन (udc->setup.bRequest) अणु
	हाल USB_REQ_GET_STATUS:
		/* Data+Status phase क्रमm udc */
		अगर ((udc->setup.bRequestType &
				(USB_सूची_IN | USB_TYPE_MASK)) !=
				(USB_सूची_IN | USB_TYPE_STANDARD)) अणु
			अवरोध;
		पूर्ण
		वापस max3420_माला_लोtatus(udc);
	हाल USB_REQ_SET_ADDRESS:
		/* Status phase from udc */
		अगर (udc->setup.bRequestType != (USB_सूची_OUT |
				USB_TYPE_STANDARD | USB_RECIP_DEVICE)) अणु
			अवरोध;
		पूर्ण
		spi_rd8_ack(udc, MAX3420_REG_FNADDR, 1);
		dev_dbg(udc->dev, "Assigned Address=%d\n", udc->setup.wValue);
		वापस;
	हाल USB_REQ_CLEAR_FEATURE:
	हाल USB_REQ_SET_FEATURE:
		/* Requests with no data phase, status phase from udc */
		अगर ((udc->setup.bRequestType & USB_TYPE_MASK)
				!= USB_TYPE_STANDARD)
			अवरोध;
		वापस max3420_set_clear_feature(udc);
	शेष:
		अवरोध;
	पूर्ण

	अगर (udc->driver->setup(&udc->gadget, &setup) < 0) अणु
		/* Stall EP0 */
		spi_wr8(udc, MAX3420_REG_EPSTALLS,
			STLEP0IN | STLEP0OUT | STLSTAT);
	पूर्ण
पूर्ण

अटल व्योम max3420_req_करोne(काष्ठा max3420_req *req, पूर्णांक status)
अणु
	काष्ठा max3420_ep *ep = req->ep;
	काष्ठा max3420_udc *udc = ep->udc;

	अगर (req->usb_req.status == -EINPROGRESS)
		req->usb_req.status = status;
	अन्यथा
		status = req->usb_req.status;

	अगर (status && status != -ESHUTDOWN)
		dev_err(udc->dev, "%s done %p, status %d\n",
			ep->ep_usb.name, req, status);

	अगर (req->usb_req.complete)
		req->usb_req.complete(&ep->ep_usb, &req->usb_req);
पूर्ण

अटल पूर्णांक max3420_करो_data(काष्ठा max3420_udc *udc, पूर्णांक ep_id, पूर्णांक in)
अणु
	काष्ठा max3420_ep *ep = &udc->ep[ep_id];
	काष्ठा max3420_req *req;
	पूर्णांक करोne, length, psz;
	व्योम *buf;

	अगर (list_empty(&ep->queue))
		वापस false;

	req = list_first_entry(&ep->queue, काष्ठा max3420_req, queue);
	buf = req->usb_req.buf + req->usb_req.actual;

	psz = ep->ep_usb.maxpacket;
	length = req->usb_req.length - req->usb_req.actual;
	length = min(length, psz);

	अगर (length == 0) अणु
		करोne = 1;
		जाओ xfer_करोne;
	पूर्ण

	करोne = 0;
	अगर (in) अणु
		prefetch(buf);
		spi_wr_buf(udc, MAX3420_REG_EP0FIFO + ep_id, buf, length);
		spi_wr8(udc, MAX3420_REG_EP0BC + ep_id, length);
		अगर (length < psz)
			करोne = 1;
	पूर्ण अन्यथा अणु
		psz = spi_rd8(udc, MAX3420_REG_EP0BC + ep_id);
		length = min(length, psz);
		prefetchw(buf);
		spi_rd_buf(udc, MAX3420_REG_EP0FIFO + ep_id, buf, length);
		अगर (length < ep->ep_usb.maxpacket)
			करोne = 1;
	पूर्ण

	req->usb_req.actual += length;

	अगर (req->usb_req.actual == req->usb_req.length)
		करोne = 1;

xfer_करोne:
	अगर (करोne) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&ep->lock, flags);
		list_del_init(&req->queue);
		spin_unlock_irqrestore(&ep->lock, flags);

		अगर (ep_id == 0)
			spi_ack_ctrl(udc);

		max3420_req_करोne(req, 0);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक max3420_handle_irqs(काष्ठा max3420_udc *udc)
अणु
	u8 epien, epirq, usbirq, usbien, reg[4];
	bool ret = false;

	spi_rd_buf(udc, MAX3420_REG_EPIRQ, reg, 4);
	epirq = reg[0];
	epien = reg[1];
	usbirq = reg[2];
	usbien = reg[3];

	usbirq &= usbien;
	epirq &= epien;

	अगर (epirq & SUDAVIRQ) अणु
		spi_wr8(udc, MAX3420_REG_EPIRQ, SUDAVIRQ);
		max3420_handle_setup(udc);
		वापस true;
	पूर्ण

	अगर (usbirq & VBUSIRQ) अणु
		spi_wr8(udc, MAX3420_REG_USBIRQ, VBUSIRQ);
		dev_dbg(udc->dev, "Cable plugged in\n");
		वापस true;
	पूर्ण

	अगर (usbirq & NOVBUSIRQ) अणु
		spi_wr8(udc, MAX3420_REG_USBIRQ, NOVBUSIRQ);
		dev_dbg(udc->dev, "Cable pulled out\n");
		वापस true;
	पूर्ण

	अगर (usbirq & URESIRQ) अणु
		spi_wr8(udc, MAX3420_REG_USBIRQ, URESIRQ);
		dev_dbg(udc->dev, "USB Reset - Start\n");
		वापस true;
	पूर्ण

	अगर (usbirq & URESDNIRQ) अणु
		spi_wr8(udc, MAX3420_REG_USBIRQ, URESDNIRQ);
		dev_dbg(udc->dev, "USB Reset - END\n");
		spi_wr8(udc, MAX3420_REG_USBIEN, URESDNIRQ | URESIRQ);
		spi_wr8(udc, MAX3420_REG_EPIEN, SUDAVIRQ | IN0BAVIRQ
			| OUT0DAVIRQ);
		वापस true;
	पूर्ण

	अगर (usbirq & SUSPIRQ) अणु
		spi_wr8(udc, MAX3420_REG_USBIRQ, SUSPIRQ);
		dev_dbg(udc->dev, "USB Suspend - Enter\n");
		udc->suspended = true;
		वापस true;
	पूर्ण

	अगर (usbirq & BUSACTIRQ) अणु
		spi_wr8(udc, MAX3420_REG_USBIRQ, BUSACTIRQ);
		dev_dbg(udc->dev, "USB Suspend - Exit\n");
		udc->suspended = false;
		वापस true;
	पूर्ण

	अगर (usbirq & RWUDNIRQ) अणु
		spi_wr8(udc, MAX3420_REG_USBIRQ, RWUDNIRQ);
		dev_dbg(udc->dev, "Asked Host to wakeup\n");
		वापस true;
	पूर्ण

	अगर (usbirq & OSCOKIRQ) अणु
		spi_wr8(udc, MAX3420_REG_USBIRQ, OSCOKIRQ);
		dev_dbg(udc->dev, "Osc stabilized, start work\n");
		वापस true;
	पूर्ण

	अगर (epirq & OUT0DAVIRQ && max3420_करो_data(udc, 0, 0)) अणु
		spi_wr8_ack(udc, MAX3420_REG_EPIRQ, OUT0DAVIRQ, 1);
		ret = true;
	पूर्ण

	अगर (epirq & IN0BAVIRQ && max3420_करो_data(udc, 0, 1))
		ret = true;

	अगर (epirq & OUT1DAVIRQ && max3420_करो_data(udc, 1, 0)) अणु
		spi_wr8_ack(udc, MAX3420_REG_EPIRQ, OUT1DAVIRQ, 1);
		ret = true;
	पूर्ण

	अगर (epirq & IN2BAVIRQ && max3420_करो_data(udc, 2, 1))
		ret = true;

	अगर (epirq & IN3BAVIRQ && max3420_करो_data(udc, 3, 1))
		ret = true;

	वापस ret;
पूर्ण

अटल पूर्णांक max3420_thपढ़ो(व्योम *dev_id)
अणु
	काष्ठा max3420_udc *udc = dev_id;
	काष्ठा spi_device *spi = udc->spi;
	पूर्णांक i, loop_again = 1;
	अचिन्हित दीर्घ flags;

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (!loop_again) अणु
			kसमय_प्रकार kt = ns_to_kसमय(1000 * 1000 * 250); /* 250ms */

			set_current_state(TASK_INTERRUPTIBLE);

			spin_lock_irqsave(&udc->lock, flags);
			अगर (udc->toकरो & ENABLE_IRQ) अणु
				enable_irq(spi->irq);
				udc->toकरो &= ~ENABLE_IRQ;
			पूर्ण
			spin_unlock_irqrestore(&udc->lock, flags);

			schedule_hrसमयout(&kt, HRTIMER_MODE_REL);
		पूर्ण
		loop_again = 0;

		mutex_lock(&udc->spi_bus_mutex);

		/* If bus-vbus_active and disconnected */
		अगर (!udc->vbus_active || !udc->softconnect)
			जाओ loop;

		अगर (max3420_start(udc)) अणु
			loop_again = 1;
			जाओ loop;
		पूर्ण

		अगर (max3420_handle_irqs(udc)) अणु
			loop_again = 1;
			जाओ loop;
		पूर्ण

		अगर (spi_max3420_rwkup(udc)) अणु
			loop_again = 1;
			जाओ loop;
		पूर्ण

		max3420_करो_data(udc, 0, 1); /* get करोne with the EP0 ZLP */

		क्रम (i = 1; i < MAX3420_MAX_EPS; i++) अणु
			काष्ठा max3420_ep *ep = &udc->ep[i];

			अगर (spi_max3420_enable(ep))
				loop_again = 1;
			अगर (spi_max3420_stall(ep))
				loop_again = 1;
		पूर्ण
loop:
		mutex_unlock(&udc->spi_bus_mutex);
	पूर्ण

	set_current_state(TASK_RUNNING);
	dev_info(udc->dev, "SPI thread exiting\n");
	वापस 0;
पूर्ण

अटल पूर्णांक max3420_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक stall)
अणु
	काष्ठा max3420_ep *ep = to_max3420_ep(_ep);
	काष्ठा max3420_udc *udc = ep->udc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ep->lock, flags);

	ep->toकरो &= ~STALL_EP;
	अगर (stall)
		ep->toकरो |= STALL;
	अन्यथा
		ep->toकरो |= UNSTALL;

	spin_unlock_irqrestore(&ep->lock, flags);

	wake_up_process(udc->thपढ़ो_task);

	dev_dbg(udc->dev, "%sStall %s\n", stall ? "" : "Un", ep->name);
	वापस 0;
पूर्ण

अटल पूर्णांक __max3420_ep_enable(काष्ठा max3420_ep *ep,
			       स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	अचिन्हित पूर्णांक maxp = usb_endpoपूर्णांक_maxp(desc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ep->lock, flags);
	ep->ep_usb.desc = desc;
	ep->ep_usb.maxpacket = maxp;

	ep->toकरो &= ~ENABLE_EP;
	ep->toकरो |= ENABLE;
	spin_unlock_irqrestore(&ep->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक max3420_ep_enable(काष्ठा usb_ep *_ep,
			     स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा max3420_ep *ep = to_max3420_ep(_ep);
	काष्ठा max3420_udc *udc = ep->udc;

	__max3420_ep_enable(ep, desc);

	wake_up_process(udc->thपढ़ो_task);

	वापस 0;
पूर्ण

अटल व्योम max3420_nuke(काष्ठा max3420_ep *ep, पूर्णांक status)
अणु
	काष्ठा max3420_req *req, *r;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ep->lock, flags);

	list_क्रम_each_entry_safe(req, r, &ep->queue, queue) अणु
		list_del_init(&req->queue);

		spin_unlock_irqrestore(&ep->lock, flags);
		max3420_req_करोne(req, status);
		spin_lock_irqsave(&ep->lock, flags);
	पूर्ण

	spin_unlock_irqrestore(&ep->lock, flags);
पूर्ण

अटल व्योम __max3420_ep_disable(काष्ठा max3420_ep *ep)
अणु
	काष्ठा max3420_udc *udc = ep->udc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ep->lock, flags);

	ep->ep_usb.desc = शून्य;

	ep->toकरो &= ~ENABLE_EP;
	ep->toकरो |= DISABLE;

	spin_unlock_irqrestore(&ep->lock, flags);

	dev_dbg(udc->dev, "Disabled %s\n", ep->name);
पूर्ण

अटल पूर्णांक max3420_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा max3420_ep *ep = to_max3420_ep(_ep);
	काष्ठा max3420_udc *udc = ep->udc;

	max3420_nuke(ep, -ESHUTDOWN);

	__max3420_ep_disable(ep);

	wake_up_process(udc->thपढ़ो_task);

	वापस 0;
पूर्ण

अटल काष्ठा usb_request *max3420_alloc_request(काष्ठा usb_ep *_ep,
						 gfp_t gfp_flags)
अणु
	काष्ठा max3420_ep *ep = to_max3420_ep(_ep);
	काष्ठा max3420_req *req;

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;

	req->ep = ep;

	वापस &req->usb_req;
पूर्ण

अटल व्योम max3420_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	kमुक्त(to_max3420_req(_req));
पूर्ण

अटल पूर्णांक max3420_ep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
			    gfp_t ignored)
अणु
	काष्ठा max3420_req *req = to_max3420_req(_req);
	काष्ठा max3420_ep *ep  = to_max3420_ep(_ep);
	काष्ठा max3420_udc *udc = ep->udc;
	अचिन्हित दीर्घ flags;

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	spin_lock_irqsave(&ep->lock, flags);
	list_add_tail(&req->queue, &ep->queue);
	spin_unlock_irqrestore(&ep->lock, flags);

	wake_up_process(udc->thपढ़ो_task);
	वापस 0;
पूर्ण

अटल पूर्णांक max3420_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा max3420_req *t, *req = to_max3420_req(_req);
	काष्ठा max3420_ep *ep = to_max3420_ep(_ep);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ep->lock, flags);

	/* Pluck the descriptor from queue */
	list_क्रम_each_entry(t, &ep->queue, queue)
		अगर (t == req) अणु
			list_del_init(&req->queue);
			अवरोध;
		पूर्ण

	spin_unlock_irqrestore(&ep->lock, flags);

	अगर (t == req)
		max3420_req_करोne(req, -ECONNRESET);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops max3420_ep_ops = अणु
	.enable		= max3420_ep_enable,
	.disable	= max3420_ep_disable,
	.alloc_request	= max3420_alloc_request,
	.मुक्त_request	= max3420_मुक्त_request,
	.queue		= max3420_ep_queue,
	.dequeue	= max3420_ep_dequeue,
	.set_halt	= max3420_ep_set_halt,
पूर्ण;

अटल पूर्णांक max3420_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा max3420_udc *udc = to_udc(gadget);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	spin_lock_irqsave(&udc->lock, flags);

	/* Only अगर wakeup allowed by host */
	अगर (udc->remote_wkp) अणु
		udc->toकरो |= REMOTE_WAKEUP;
		ret = 0;
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);

	अगर (udc->thपढ़ो_task &&
	    udc->thपढ़ो_task->state != TASK_RUNNING)
		wake_up_process(udc->thपढ़ो_task);
	वापस ret;
पूर्ण

अटल पूर्णांक max3420_udc_start(काष्ठा usb_gadget *gadget,
			     काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा max3420_udc *udc = to_udc(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);
	/* hook up the driver */
	driver->driver.bus = शून्य;
	udc->driver = driver;
	udc->gadget.speed = USB_SPEED_FULL;

	udc->gadget.is_selfघातered = udc->is_selfघातered;
	udc->remote_wkp = 0;
	udc->softconnect = true;
	udc->toकरो |= UDC_START;
	spin_unlock_irqrestore(&udc->lock, flags);

	अगर (udc->thपढ़ो_task &&
	    udc->thपढ़ो_task->state != TASK_RUNNING)
		wake_up_process(udc->thपढ़ो_task);

	वापस 0;
पूर्ण

अटल पूर्णांक max3420_udc_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा max3420_udc *udc = to_udc(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);
	udc->is_selfघातered = udc->gadget.is_selfघातered;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->driver = शून्य;
	udc->softconnect = false;
	udc->toकरो |= UDC_START;
	spin_unlock_irqrestore(&udc->lock, flags);

	अगर (udc->thपढ़ो_task &&
	    udc->thपढ़ो_task->state != TASK_RUNNING)
		wake_up_process(udc->thपढ़ो_task);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops max3420_udc_ops = अणु
	.udc_start	= max3420_udc_start,
	.udc_stop	= max3420_udc_stop,
	.wakeup		= max3420_wakeup,
पूर्ण;

अटल व्योम max3420_eps_init(काष्ठा max3420_udc *udc)
अणु
	पूर्णांक idx;

	INIT_LIST_HEAD(&udc->gadget.ep_list);

	क्रम (idx = 0; idx < MAX3420_MAX_EPS; idx++) अणु
		काष्ठा max3420_ep *ep = &udc->ep[idx];

		spin_lock_init(&ep->lock);
		INIT_LIST_HEAD(&ep->queue);

		ep->udc = udc;
		ep->id = idx;
		ep->halted = 0;
		ep->maxpacket = 0;
		ep->ep_usb.name = ep->name;
		ep->ep_usb.ops = &max3420_ep_ops;
		usb_ep_set_maxpacket_limit(&ep->ep_usb, MAX3420_EP_MAX_PACKET);

		अगर (idx == 0) अणु /* For EP0 */
			ep->ep_usb.desc = &ep0_desc;
			ep->ep_usb.maxpacket = usb_endpoपूर्णांक_maxp(&ep0_desc);
			ep->ep_usb.caps.type_control = true;
			ep->ep_usb.caps.dir_in = true;
			ep->ep_usb.caps.dir_out = true;
			snम_लिखो(ep->name, MAX3420_EPNAME_SIZE, "ep0");
			जारी;
		पूर्ण

		अगर (idx == 1) अणु /* EP1 is OUT */
			ep->ep_usb.caps.dir_in = false;
			ep->ep_usb.caps.dir_out = true;
			snम_लिखो(ep->name, MAX3420_EPNAME_SIZE, "ep1-bulk-out");
		पूर्ण अन्यथा अणु /* EP2 & EP3 are IN */
			ep->ep_usb.caps.dir_in = true;
			ep->ep_usb.caps.dir_out = false;
			snम_लिखो(ep->name, MAX3420_EPNAME_SIZE,
				 "ep%d-bulk-in", idx);
		पूर्ण
		ep->ep_usb.caps.type_iso = false;
		ep->ep_usb.caps.type_पूर्णांक = false;
		ep->ep_usb.caps.type_bulk = true;

		list_add_tail(&ep->ep_usb.ep_list,
			      &udc->gadget.ep_list);
	पूर्ण
पूर्ण

अटल पूर्णांक max3420_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा max3420_udc *udc;
	पूर्णांक err, irq;
	u8 reg[8];

	अगर (spi->master->flags & SPI_MASTER_HALF_DUPLEX) अणु
		dev_err(&spi->dev, "UDC needs full duplex to work\n");
		वापस -EINVAL;
	पूर्ण

	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 8;

	err = spi_setup(spi);
	अगर (err) अणु
		dev_err(&spi->dev, "Unable to setup SPI bus\n");
		वापस -EFAULT;
	पूर्ण

	udc = devm_kzalloc(&spi->dev, माप(*udc), GFP_KERNEL);
	अगर (!udc)
		वापस -ENOMEM;

	udc->spi = spi;

	udc->remote_wkp = 0;

	/* Setup gadget काष्ठाure */
	udc->gadget.ops = &max3420_udc_ops;
	udc->gadget.max_speed = USB_SPEED_FULL;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->gadget.ep0 = &udc->ep[0].ep_usb;
	udc->gadget.name = driver_name;

	spin_lock_init(&udc->lock);
	mutex_init(&udc->spi_bus_mutex);

	udc->ep0req.ep = &udc->ep[0];
	udc->ep0req.usb_req.buf = udc->ep0buf;
	INIT_LIST_HEAD(&udc->ep0req.queue);

	/* setup Endpoपूर्णांकs */
	max3420_eps_init(udc);

	/* configure SPI */
	spi_rd_buf(udc, MAX3420_REG_EPIRQ, reg, 8);
	spi_wr8(udc, MAX3420_REG_PINCTL, FDUPSPI);

	err = usb_add_gadget_udc(&spi->dev, &udc->gadget);
	अगर (err)
		वापस err;

	udc->dev = &udc->gadget.dev;

	spi_set_drvdata(spi, udc);

	irq = of_irq_get_byname(spi->dev.of_node, "udc");
	err = devm_request_irq(&spi->dev, irq, max3420_irq_handler, 0,
			       "max3420", udc);
	अगर (err < 0)
		वापस err;

	udc->thपढ़ो_task = kthपढ़ो_create(max3420_thपढ़ो, udc,
					  "max3420-thread");
	अगर (IS_ERR(udc->thपढ़ो_task))
		वापस PTR_ERR(udc->thपढ़ो_task);

	irq = of_irq_get_byname(spi->dev.of_node, "vbus");
	अगर (irq <= 0) अणु /* no vbus irq implies self-घातered design */
		udc->is_selfघातered = 1;
		udc->vbus_active = true;
		udc->toकरो |= UDC_START;
		usb_udc_vbus_handler(&udc->gadget, udc->vbus_active);
		usb_gadget_set_state(&udc->gadget, USB_STATE_POWERED);
		max3420_start(udc);
	पूर्ण अन्यथा अणु
		udc->is_selfघातered = 0;
		/* Detect current vbus status */
		spi_rd_buf(udc, MAX3420_REG_EPIRQ, reg, 8);
		अगर (reg[7] != 0xff)
			udc->vbus_active = true;

		err = devm_request_irq(&spi->dev, irq,
				       max3420_vbus_handler, 0, "vbus", udc);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max3420_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा max3420_udc *udc = spi_get_drvdata(spi);
	अचिन्हित दीर्घ flags;

	usb_del_gadget_udc(&udc->gadget);

	spin_lock_irqsave(&udc->lock, flags);

	kthपढ़ो_stop(udc->thपढ़ो_task);

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id max3420_udc_of_match[] = अणु
	अणु .compatible = "maxim,max3420-udc"पूर्ण,
	अणु .compatible = "maxim,max3421-udc"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max3420_udc_of_match);

अटल काष्ठा spi_driver max3420_driver = अणु
	.driver = अणु
		.name = "max3420-udc",
		.of_match_table = of_match_ptr(max3420_udc_of_match),
	पूर्ण,
	.probe = max3420_probe,
	.हटाओ = max3420_हटाओ,
पूर्ण;

module_spi_driver(max3420_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Jassi Brar <jaswinder.singh@linaro.org>");
MODULE_LICENSE("GPL");
