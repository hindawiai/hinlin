<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Xilinx USB peripheral controller driver
 *
 * Copyright (C) 2004 by Thomas Rathbone
 * Copyright (C) 2005 by HP Lअसल
 * Copyright (C) 2005 by David Brownell
 * Copyright (C) 2010 - 2014 Xilinx, Inc.
 *
 * Some parts of this driver code is based on the driver क्रम at91-series
 * USB peripheral controller (at91_udc.c).
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>

/* Register offsets क्रम the USB device.*/
#घोषणा XUSB_EP0_CONFIG_OFFSET		0x0000  /* EP0 Config Reg Offset */
#घोषणा XUSB_SETUP_PKT_ADDR_OFFSET	0x0080  /* Setup Packet Address */
#घोषणा XUSB_ADDRESS_OFFSET		0x0100  /* Address Register */
#घोषणा XUSB_CONTROL_OFFSET		0x0104  /* Control Register */
#घोषणा XUSB_STATUS_OFFSET		0x0108  /* Status Register */
#घोषणा XUSB_FRAMENUM_OFFSET		0x010C	/* Frame Number Register */
#घोषणा XUSB_IER_OFFSET			0x0110	/* Interrupt Enable Register */
#घोषणा XUSB_BUFFREADY_OFFSET		0x0114	/* Buffer Ready Register */
#घोषणा XUSB_TESTMODE_OFFSET		0x0118	/* Test Mode Register */
#घोषणा XUSB_DMA_RESET_OFFSET		0x0200  /* DMA Soft Reset Register */
#घोषणा XUSB_DMA_CONTROL_OFFSET		0x0204	/* DMA Control Register */
#घोषणा XUSB_DMA_DSAR_ADDR_OFFSET	0x0208	/* DMA source Address Reg */
#घोषणा XUSB_DMA_DDAR_ADDR_OFFSET	0x020C	/* DMA destination Addr Reg */
#घोषणा XUSB_DMA_LENGTH_OFFSET		0x0210	/* DMA Length Register */
#घोषणा XUSB_DMA_STATUS_OFFSET		0x0214	/* DMA Status Register */

/* Endpoपूर्णांक Configuration Space offsets */
#घोषणा XUSB_EP_CFGSTATUS_OFFSET	0x00	/* Endpoपूर्णांक Config Status  */
#घोषणा XUSB_EP_BUF0COUNT_OFFSET	0x08	/* Buffer 0 Count */
#घोषणा XUSB_EP_BUF1COUNT_OFFSET	0x0C	/* Buffer 1 Count */

#घोषणा XUSB_CONTROL_USB_READY_MASK	0x80000000 /* USB पढ़ोy Mask */
#घोषणा XUSB_CONTROL_USB_RMTWAKE_MASK	0x40000000 /* Remote wake up mask */

/* Interrupt रेजिस्टर related masks.*/
#घोषणा XUSB_STATUS_GLOBAL_INTR_MASK	0x80000000 /* Global Intr Enable */
#घोषणा XUSB_STATUS_DMADONE_MASK	0x04000000 /* DMA करोne Mask */
#घोषणा XUSB_STATUS_DMAERR_MASK		0x02000000 /* DMA Error Mask */
#घोषणा XUSB_STATUS_DMABUSY_MASK	0x80000000 /* DMA Error Mask */
#घोषणा XUSB_STATUS_RESUME_MASK		0x01000000 /* USB Resume Mask */
#घोषणा XUSB_STATUS_RESET_MASK		0x00800000 /* USB Reset Mask */
#घोषणा XUSB_STATUS_SUSPEND_MASK	0x00400000 /* USB Suspend Mask */
#घोषणा XUSB_STATUS_DISCONNECT_MASK	0x00200000 /* USB Disconnect Mask */
#घोषणा XUSB_STATUS_FIFO_BUFF_RDY_MASK	0x00100000 /* FIFO Buff Ready Mask */
#घोषणा XUSB_STATUS_FIFO_BUFF_FREE_MASK	0x00080000 /* FIFO Buff Free Mask */
#घोषणा XUSB_STATUS_SETUP_PACKET_MASK	0x00040000 /* Setup packet received */
#घोषणा XUSB_STATUS_EP1_BUFF2_COMP_MASK	0x00000200 /* EP 1 Buff 2 Processed */
#घोषणा XUSB_STATUS_EP1_BUFF1_COMP_MASK	0x00000002 /* EP 1 Buff 1 Processed */
#घोषणा XUSB_STATUS_EP0_BUFF2_COMP_MASK	0x00000100 /* EP 0 Buff 2 Processed */
#घोषणा XUSB_STATUS_EP0_BUFF1_COMP_MASK	0x00000001 /* EP 0 Buff 1 Processed */
#घोषणा XUSB_STATUS_HIGH_SPEED_MASK	0x00010000 /* USB Speed Mask */
/* Suspend,Reset,Suspend and Disconnect Mask */
#घोषणा XUSB_STATUS_INTR_EVENT_MASK	0x01E00000
/* Buffers  completion Mask */
#घोषणा XUSB_STATUS_INTR_BUFF_COMP_ALL_MASK	0x0000FEFF
/* Mask क्रम buffer 0 and buffer 1 completion क्रम all Endpoपूर्णांकs */
#घोषणा XUSB_STATUS_INTR_BUFF_COMP_SHIFT_MASK	0x00000101
#घोषणा XUSB_STATUS_EP_BUFF2_SHIFT	8	   /* EP buffer offset */

/* Endpoपूर्णांक Configuration Status Register */
#घोषणा XUSB_EP_CFG_VALID_MASK		0x80000000 /* Endpoपूर्णांक Valid bit */
#घोषणा XUSB_EP_CFG_STALL_MASK		0x40000000 /* Endpoपूर्णांक Stall bit */
#घोषणा XUSB_EP_CFG_DATA_TOGGLE_MASK	0x08000000 /* Endpoपूर्णांक Data toggle */

/* USB device specअगरic global configuration स्थिरants.*/
#घोषणा XUSB_MAX_ENDPOINTS		8	/* Maximum End Poपूर्णांकs */
#घोषणा XUSB_EP_NUMBER_ZERO		0	/* End poपूर्णांक Zero */
/* DPRAM is the source address क्रम DMA transfer */
#घोषणा XUSB_DMA_READ_FROM_DPRAM	0x80000000
#घोषणा XUSB_DMA_DMASR_BUSY		0x80000000 /* DMA busy */
#घोषणा XUSB_DMA_DMASR_ERROR		0x40000000 /* DMA Error */
/*
 * When this bit is set, the DMA buffer पढ़ोy bit is set by hardware upon
 * DMA transfer completion.
 */
#घोषणा XUSB_DMA_BRR_CTRL		0x40000000 /* DMA buख_पढ़ोy ctrl bit */
/* Phase States */
#घोषणा SETUP_PHASE			0x0000	/* Setup Phase */
#घोषणा DATA_PHASE			0x0001  /* Data Phase */
#घोषणा STATUS_PHASE			0x0002  /* Status Phase */

#घोषणा EP0_MAX_PACKET		64 /* Endpoपूर्णांक 0 maximum packet length */
#घोषणा STATUSBUFF_SIZE		2  /* Buffer size क्रम GET_STATUS command */
#घोषणा EPNAME_SIZE		4  /* Buffer size क्रम endpoपूर्णांक name */

/* container_of helper macros */
#घोषणा to_udc(g)	 container_of((g), काष्ठा xusb_udc, gadget)
#घोषणा to_xusb_ep(ep)	 container_of((ep), काष्ठा xusb_ep, ep_usb)
#घोषणा to_xusb_req(req) container_of((req), काष्ठा xusb_req, usb_req)

/**
 * काष्ठा xusb_req - Xilinx USB device request काष्ठाure
 * @usb_req: Linux usb request काष्ठाure
 * @queue: usb device request queue
 * @ep: poपूर्णांकer to xusb_endpoपूर्णांक काष्ठाure
 */
काष्ठा xusb_req अणु
	काष्ठा usb_request usb_req;
	काष्ठा list_head queue;
	काष्ठा xusb_ep *ep;
पूर्ण;

/**
 * काष्ठा xusb_ep - USB end poपूर्णांक काष्ठाure.
 * @ep_usb: usb endpoपूर्णांक instance
 * @queue: endpoपूर्णांक message queue
 * @udc: xilinx usb peripheral driver instance poपूर्णांकer
 * @desc: poपूर्णांकer to the usb endpoपूर्णांक descriptor
 * @rambase: the endpoपूर्णांक buffer address
 * @offset: the endpoपूर्णांक रेजिस्टर offset value
 * @name: name of the endpoपूर्णांक
 * @epnumber: endpoपूर्णांक number
 * @maxpacket: maximum packet size the endpoपूर्णांक can store
 * @buffer0count: the size of the packet recieved in the first buffer
 * @buffer1count: the size of the packet received in the second buffer
 * @curbufnum: current buffer of endpoपूर्णांक that will be processed next
 * @buffer0पढ़ोy: the busy state of first buffer
 * @buffer1पढ़ोy: the busy state of second buffer
 * @is_in: endpoपूर्णांक direction (IN or OUT)
 * @is_iso: endpoपूर्णांक type(isochronous or non isochronous)
 */
काष्ठा xusb_ep अणु
	काष्ठा usb_ep ep_usb;
	काष्ठा list_head queue;
	काष्ठा xusb_udc *udc;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc;
	u32  rambase;
	u32  offset;
	अक्षर name[4];
	u16  epnumber;
	u16  maxpacket;
	u16  buffer0count;
	u16  buffer1count;
	u8   curbufnum;
	bool buffer0पढ़ोy;
	bool buffer1पढ़ोy;
	bool is_in;
	bool is_iso;
पूर्ण;

/**
 * काष्ठा xusb_udc -  USB peripheral driver काष्ठाure
 * @gadget: USB gadget driver instance
 * @ep: an array of endpoपूर्णांक काष्ठाures
 * @driver: poपूर्णांकer to the usb gadget driver instance
 * @setup: usb_ctrlrequest काष्ठाure क्रम control requests
 * @req: poपूर्णांकer to dummy request क्रम get status command
 * @dev: poपूर्णांकer to device काष्ठाure in gadget
 * @usb_state: device in suspended state or not
 * @remote_wkp: remote wakeup enabled by host
 * @setupseqtx: tx status
 * @setupseqrx: rx status
 * @addr: the usb device base address
 * @lock: instance of spinlock
 * @dma_enabled: flag indicating whether the dma is included in the प्रणाली
 * @पढ़ो_fn: function poपूर्णांकer to पढ़ो device रेजिस्टरs
 * @ग_लिखो_fn: function poपूर्णांकer to ग_लिखो to device रेजिस्टरs
 */
काष्ठा xusb_udc अणु
	काष्ठा usb_gadget gadget;
	काष्ठा xusb_ep ep[8];
	काष्ठा usb_gadget_driver *driver;
	काष्ठा usb_ctrlrequest setup;
	काष्ठा xusb_req *req;
	काष्ठा device *dev;
	u32 usb_state;
	u32 remote_wkp;
	u32 setupseqtx;
	u32 setupseqrx;
	व्योम __iomem *addr;
	spinlock_t lock;
	bool dma_enabled;

	अचिन्हित पूर्णांक (*पढ़ो_fn)(व्योम __iomem *);
	व्योम (*ग_लिखो_fn)(व्योम __iomem *, u32, u32);
पूर्ण;

/* Endpoपूर्णांक buffer start addresses in the core */
अटल u32 rambase[8] = अणु 0x22, 0x1000, 0x1100, 0x1200, 0x1300, 0x1400, 0x1500,
			  0x1600 पूर्ण;

अटल स्थिर अक्षर driver_name[] = "xilinx-udc";
अटल स्थिर अक्षर ep0name[] = "ep0";

/* Control endpoपूर्णांक configuration.*/
अटल स्थिर काष्ठा usb_endpoपूर्णांक_descriptor config_bulk_out_desc = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress	= USB_सूची_OUT,
	.bmAttributes		= USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize		= cpu_to_le16(EP0_MAX_PACKET),
पूर्ण;

/**
 * xudc_ग_लिखो32 - little endian ग_लिखो to device रेजिस्टरs
 * @addr: base addr of device रेजिस्टरs
 * @offset: रेजिस्टर offset
 * @val: data to be written
 */
अटल व्योम xudc_ग_लिखो32(व्योम __iomem *addr, u32 offset, u32 val)
अणु
	ioग_लिखो32(val, addr + offset);
पूर्ण

/**
 * xudc_पढ़ो32 - little endian पढ़ो from device रेजिस्टरs
 * @addr: addr of device रेजिस्टर
 * Return: value at addr
 */
अटल अचिन्हित पूर्णांक xudc_पढ़ो32(व्योम __iomem *addr)
अणु
	वापस ioपढ़ो32(addr);
पूर्ण

/**
 * xudc_ग_लिखो32_be - big endian ग_लिखो to device रेजिस्टरs
 * @addr: base addr of device रेजिस्टरs
 * @offset: रेजिस्टर offset
 * @val: data to be written
 */
अटल व्योम xudc_ग_लिखो32_be(व्योम __iomem *addr, u32 offset, u32 val)
अणु
	ioग_लिखो32be(val, addr + offset);
पूर्ण

/**
 * xudc_पढ़ो32_be - big endian पढ़ो from device रेजिस्टरs
 * @addr: addr of device रेजिस्टर
 * Return: value at addr
 */
अटल अचिन्हित पूर्णांक xudc_पढ़ो32_be(व्योम __iomem *addr)
अणु
	वापस ioपढ़ो32be(addr);
पूर्ण

/**
 * xudc_wrstatus - Sets up the usb device status stages.
 * @udc: poपूर्णांकer to the usb device controller काष्ठाure.
 */
अटल व्योम xudc_wrstatus(काष्ठा xusb_udc *udc)
अणु
	काष्ठा xusb_ep *ep0 = &udc->ep[XUSB_EP_NUMBER_ZERO];
	u32 epcfgreg;

	epcfgreg = udc->पढ़ो_fn(udc->addr + ep0->offset)|
				XUSB_EP_CFG_DATA_TOGGLE_MASK;
	udc->ग_लिखो_fn(udc->addr, ep0->offset, epcfgreg);
	udc->ग_लिखो_fn(udc->addr, ep0->offset + XUSB_EP_BUF0COUNT_OFFSET, 0);
	udc->ग_लिखो_fn(udc->addr, XUSB_BUFFREADY_OFFSET, 1);
पूर्ण

/**
 * xudc_epconfig - Configures the given endpoपूर्णांक.
 * @ep: poपूर्णांकer to the usb device endpoपूर्णांक काष्ठाure.
 * @udc: poपूर्णांकer to the usb peripheral controller काष्ठाure.
 *
 * This function configures a specअगरic endpoपूर्णांक with the given configuration
 * data.
 */
अटल व्योम xudc_epconfig(काष्ठा xusb_ep *ep, काष्ठा xusb_udc *udc)
अणु
	u32 epcfgreg;

	/*
	 * Configure the end poपूर्णांक direction, type, Max Packet Size and the
	 * EP buffer location.
	 */
	epcfgreg = ((ep->is_in << 29) | (ep->is_iso << 28) |
		   (ep->ep_usb.maxpacket << 15) | (ep->rambase));
	udc->ग_लिखो_fn(udc->addr, ep->offset, epcfgreg);

	/* Set the Buffer count and the Buffer पढ़ोy bits.*/
	udc->ग_लिखो_fn(udc->addr, ep->offset + XUSB_EP_BUF0COUNT_OFFSET,
		      ep->buffer0count);
	udc->ग_लिखो_fn(udc->addr, ep->offset + XUSB_EP_BUF1COUNT_OFFSET,
		      ep->buffer1count);
	अगर (ep->buffer0पढ़ोy)
		udc->ग_लिखो_fn(udc->addr, XUSB_BUFFREADY_OFFSET,
			      1 << ep->epnumber);
	अगर (ep->buffer1पढ़ोy)
		udc->ग_लिखो_fn(udc->addr, XUSB_BUFFREADY_OFFSET,
			      1 << (ep->epnumber + XUSB_STATUS_EP_BUFF2_SHIFT));
पूर्ण

/**
 * xudc_start_dma - Starts DMA transfer.
 * @ep: poपूर्णांकer to the usb device endpoपूर्णांक काष्ठाure.
 * @src: DMA source address.
 * @dst: DMA destination address.
 * @length: number of bytes to transfer.
 *
 * Return: 0 on success, error code on failure
 *
 * This function starts DMA transfer by writing to DMA source,
 * destination and lenth रेजिस्टरs.
 */
अटल पूर्णांक xudc_start_dma(काष्ठा xusb_ep *ep, dma_addr_t src,
			  dma_addr_t dst, u32 length)
अणु
	काष्ठा xusb_udc *udc = ep->udc;
	पूर्णांक rc = 0;
	u32 समयout = 500;
	u32 reg;

	/*
	 * Set the addresses in the DMA source and
	 * destination रेजिस्टरs and then set the length
	 * पूर्णांकo the DMA length रेजिस्टर.
	 */
	udc->ग_लिखो_fn(udc->addr, XUSB_DMA_DSAR_ADDR_OFFSET, src);
	udc->ग_लिखो_fn(udc->addr, XUSB_DMA_DDAR_ADDR_OFFSET, dst);
	udc->ग_लिखो_fn(udc->addr, XUSB_DMA_LENGTH_OFFSET, length);

	/*
	 * Wait till DMA transaction is complete and
	 * check whether the DMA transaction was
	 * successful.
	 */
	करो अणु
		reg = udc->पढ़ो_fn(udc->addr + XUSB_DMA_STATUS_OFFSET);
		अगर (!(reg &  XUSB_DMA_DMASR_BUSY))
			अवरोध;

		/*
		 * We can't sleep here, because it's also called from
		 * पूर्णांकerrupt context.
		 */
		समयout--;
		अगर (!समयout) अणु
			dev_err(udc->dev, "DMA timeout\n");
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(1);
	पूर्ण जबतक (1);

	अगर ((udc->पढ़ो_fn(udc->addr + XUSB_DMA_STATUS_OFFSET) &
			  XUSB_DMA_DMASR_ERROR) == XUSB_DMA_DMASR_ERROR)अणु
		dev_err(udc->dev, "DMA Error\n");
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * xudc_dma_send - Sends IN data using DMA.
 * @ep: poपूर्णांकer to the usb device endpoपूर्णांक काष्ठाure.
 * @req: poपूर्णांकer to the usb request काष्ठाure.
 * @buffer: poपूर्णांकer to data to be sent.
 * @length: number of bytes to send.
 *
 * Return: 0 on success, -EAGAIN अगर no buffer is मुक्त and error
 *	   code on failure.
 *
 * This function sends data using DMA.
 */
अटल पूर्णांक xudc_dma_send(काष्ठा xusb_ep *ep, काष्ठा xusb_req *req,
			 u8 *buffer, u32 length)
अणु
	u32 *eprambase;
	dma_addr_t src;
	dma_addr_t dst;
	काष्ठा xusb_udc *udc = ep->udc;

	src = req->usb_req.dma + req->usb_req.actual;
	अगर (req->usb_req.length)
		dma_sync_single_क्रम_device(udc->dev, src,
					   length, DMA_TO_DEVICE);
	अगर (!ep->curbufnum && !ep->buffer0पढ़ोy) अणु
		/* Get the Buffer address and copy the transmit data.*/
		eprambase = (u32 __क्रमce *)(udc->addr + ep->rambase);
		dst = virt_to_phys(eprambase);
		udc->ग_लिखो_fn(udc->addr, ep->offset +
			      XUSB_EP_BUF0COUNT_OFFSET, length);
		udc->ग_लिखो_fn(udc->addr, XUSB_DMA_CONTROL_OFFSET,
			      XUSB_DMA_BRR_CTRL | (1 << ep->epnumber));
		ep->buffer0पढ़ोy = 1;
		ep->curbufnum = 1;
	पूर्ण अन्यथा अगर (ep->curbufnum && !ep->buffer1पढ़ोy) अणु
		/* Get the Buffer address and copy the transmit data.*/
		eprambase = (u32 __क्रमce *)(udc->addr + ep->rambase +
			     ep->ep_usb.maxpacket);
		dst = virt_to_phys(eprambase);
		udc->ग_लिखो_fn(udc->addr, ep->offset +
			      XUSB_EP_BUF1COUNT_OFFSET, length);
		udc->ग_लिखो_fn(udc->addr, XUSB_DMA_CONTROL_OFFSET,
			      XUSB_DMA_BRR_CTRL | (1 << (ep->epnumber +
			      XUSB_STATUS_EP_BUFF2_SHIFT)));
		ep->buffer1पढ़ोy = 1;
		ep->curbufnum = 0;
	पूर्ण अन्यथा अणु
		/* None of ping pong buffers are पढ़ोy currently .*/
		वापस -EAGAIN;
	पूर्ण

	वापस xudc_start_dma(ep, src, dst, length);
पूर्ण

/**
 * xudc_dma_receive - Receives OUT data using DMA.
 * @ep: poपूर्णांकer to the usb device endpoपूर्णांक काष्ठाure.
 * @req: poपूर्णांकer to the usb request काष्ठाure.
 * @buffer: poपूर्णांकer to storage buffer of received data.
 * @length: number of bytes to receive.
 *
 * Return: 0 on success, -EAGAIN अगर no buffer is मुक्त and error
 *	   code on failure.
 *
 * This function receives data using DMA.
 */
अटल पूर्णांक xudc_dma_receive(काष्ठा xusb_ep *ep, काष्ठा xusb_req *req,
			    u8 *buffer, u32 length)
अणु
	u32 *eprambase;
	dma_addr_t src;
	dma_addr_t dst;
	काष्ठा xusb_udc *udc = ep->udc;

	dst = req->usb_req.dma + req->usb_req.actual;
	अगर (!ep->curbufnum && !ep->buffer0पढ़ोy) अणु
		/* Get the Buffer address and copy the transmit data */
		eprambase = (u32 __क्रमce *)(udc->addr + ep->rambase);
		src = virt_to_phys(eprambase);
		udc->ग_लिखो_fn(udc->addr, XUSB_DMA_CONTROL_OFFSET,
			      XUSB_DMA_BRR_CTRL | XUSB_DMA_READ_FROM_DPRAM |
			      (1 << ep->epnumber));
		ep->buffer0पढ़ोy = 1;
		ep->curbufnum = 1;
	पूर्ण अन्यथा अगर (ep->curbufnum && !ep->buffer1पढ़ोy) अणु
		/* Get the Buffer address and copy the transmit data */
		eprambase = (u32 __क्रमce *)(udc->addr +
			     ep->rambase + ep->ep_usb.maxpacket);
		src = virt_to_phys(eprambase);
		udc->ग_लिखो_fn(udc->addr, XUSB_DMA_CONTROL_OFFSET,
			      XUSB_DMA_BRR_CTRL | XUSB_DMA_READ_FROM_DPRAM |
			      (1 << (ep->epnumber +
			      XUSB_STATUS_EP_BUFF2_SHIFT)));
		ep->buffer1पढ़ोy = 1;
		ep->curbufnum = 0;
	पूर्ण अन्यथा अणु
		/* None of the ping-pong buffers are पढ़ोy currently */
		वापस -EAGAIN;
	पूर्ण

	वापस xudc_start_dma(ep, src, dst, length);
पूर्ण

/**
 * xudc_eptxrx - Transmits or receives data to or from an endpoपूर्णांक.
 * @ep: poपूर्णांकer to the usb endpoपूर्णांक configuration काष्ठाure.
 * @req: poपूर्णांकer to the usb request काष्ठाure.
 * @bufferptr: poपूर्णांकer to buffer containing the data to be sent.
 * @bufferlen: The number of data bytes to be sent.
 *
 * Return: 0 on success, -EAGAIN अगर no buffer is मुक्त.
 *
 * This function copies the transmit/receive data to/from the end poपूर्णांक buffer
 * and enables the buffer क्रम transmission/reception.
 */
अटल पूर्णांक xudc_eptxrx(काष्ठा xusb_ep *ep, काष्ठा xusb_req *req,
		       u8 *bufferptr, u32 bufferlen)
अणु
	u32 *eprambase;
	u32 bytestosend;
	पूर्णांक rc = 0;
	काष्ठा xusb_udc *udc = ep->udc;

	bytestosend = bufferlen;
	अगर (udc->dma_enabled) अणु
		अगर (ep->is_in)
			rc = xudc_dma_send(ep, req, bufferptr, bufferlen);
		अन्यथा
			rc = xudc_dma_receive(ep, req, bufferptr, bufferlen);
		वापस rc;
	पूर्ण
	/* Put the transmit buffer पूर्णांकo the correct ping-pong buffer.*/
	अगर (!ep->curbufnum && !ep->buffer0पढ़ोy) अणु
		/* Get the Buffer address and copy the transmit data.*/
		eprambase = (u32 __क्रमce *)(udc->addr + ep->rambase);
		अगर (ep->is_in) अणु
			स_नकल(eprambase, bufferptr, bytestosend);
			udc->ग_लिखो_fn(udc->addr, ep->offset +
				      XUSB_EP_BUF0COUNT_OFFSET, bufferlen);
		पूर्ण अन्यथा अणु
			स_नकल(bufferptr, eprambase, bytestosend);
		पूर्ण
		/*
		 * Enable the buffer क्रम transmission.
		 */
		udc->ग_लिखो_fn(udc->addr, XUSB_BUFFREADY_OFFSET,
			      1 << ep->epnumber);
		ep->buffer0पढ़ोy = 1;
		ep->curbufnum = 1;
	पूर्ण अन्यथा अगर (ep->curbufnum && !ep->buffer1पढ़ोy) अणु
		/* Get the Buffer address and copy the transmit data.*/
		eprambase = (u32 __क्रमce *)(udc->addr + ep->rambase +
			     ep->ep_usb.maxpacket);
		अगर (ep->is_in) अणु
			स_नकल(eprambase, bufferptr, bytestosend);
			udc->ग_लिखो_fn(udc->addr, ep->offset +
				      XUSB_EP_BUF1COUNT_OFFSET, bufferlen);
		पूर्ण अन्यथा अणु
			स_नकल(bufferptr, eprambase, bytestosend);
		पूर्ण
		/*
		 * Enable the buffer क्रम transmission.
		 */
		udc->ग_लिखो_fn(udc->addr, XUSB_BUFFREADY_OFFSET,
			      1 << (ep->epnumber + XUSB_STATUS_EP_BUFF2_SHIFT));
		ep->buffer1पढ़ोy = 1;
		ep->curbufnum = 0;
	पूर्ण अन्यथा अणु
		/* None of the ping-pong buffers are पढ़ोy currently */
		वापस -EAGAIN;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * xudc_करोne - Exeutes the endpoपूर्णांक data transfer completion tasks.
 * @ep: poपूर्णांकer to the usb device endpoपूर्णांक काष्ठाure.
 * @req: poपूर्णांकer to the usb request काष्ठाure.
 * @status: Status of the data transfer.
 *
 * Deletes the message from the queue and updates data transfer completion
 * status.
 */
अटल व्योम xudc_करोne(काष्ठा xusb_ep *ep, काष्ठा xusb_req *req, पूर्णांक status)
अणु
	काष्ठा xusb_udc *udc = ep->udc;

	list_del_init(&req->queue);

	अगर (req->usb_req.status == -EINPROGRESS)
		req->usb_req.status = status;
	अन्यथा
		status = req->usb_req.status;

	अगर (status && status != -ESHUTDOWN)
		dev_dbg(udc->dev, "%s done %p, status %d\n",
			ep->ep_usb.name, req, status);
	/* unmap request अगर DMA is present*/
	अगर (udc->dma_enabled && ep->epnumber && req->usb_req.length)
		usb_gadget_unmap_request(&udc->gadget, &req->usb_req,
					 ep->is_in);

	अगर (req->usb_req.complete) अणु
		spin_unlock(&udc->lock);
		req->usb_req.complete(&ep->ep_usb, &req->usb_req);
		spin_lock(&udc->lock);
	पूर्ण
पूर्ण

/**
 * xudc_पढ़ो_fअगरo - Reads the data from the given endpoपूर्णांक buffer.
 * @ep: poपूर्णांकer to the usb device endpoपूर्णांक काष्ठाure.
 * @req: poपूर्णांकer to the usb request काष्ठाure.
 *
 * Return: 0 अगर request is completed and -EAGAIN अगर not completed.
 *
 * Pulls OUT packet data from the endpoपूर्णांक buffer.
 */
अटल पूर्णांक xudc_पढ़ो_fअगरo(काष्ठा xusb_ep *ep, काष्ठा xusb_req *req)
अणु
	u8 *buf;
	u32 is_लघु, count, bufferspace;
	u8 bufoffset;
	u8 two_pkts = 0;
	पूर्णांक ret;
	पूर्णांक retval = -EAGAIN;
	काष्ठा xusb_udc *udc = ep->udc;

	अगर (ep->buffer0पढ़ोy && ep->buffer1पढ़ोy) अणु
		dev_dbg(udc->dev, "Packet NOT ready!\n");
		वापस retval;
	पूर्ण
top:
	अगर (ep->curbufnum)
		bufoffset = XUSB_EP_BUF1COUNT_OFFSET;
	अन्यथा
		bufoffset = XUSB_EP_BUF0COUNT_OFFSET;

	count = udc->पढ़ो_fn(udc->addr + ep->offset + bufoffset);

	अगर (!ep->buffer0पढ़ोy && !ep->buffer1पढ़ोy)
		two_pkts = 1;

	buf = req->usb_req.buf + req->usb_req.actual;
	prefetchw(buf);
	bufferspace = req->usb_req.length - req->usb_req.actual;
	is_लघु = count < ep->ep_usb.maxpacket;

	अगर (unlikely(!bufferspace)) अणु
		/*
		 * This happens when the driver's buffer
		 * is smaller than what the host sent.
		 * discard the extra data.
		 */
		अगर (req->usb_req.status != -EOVERFLOW)
			dev_dbg(udc->dev, "%s overflow %d\n",
				ep->ep_usb.name, count);
		req->usb_req.status = -EOVERFLOW;
		xudc_करोne(ep, req, -EOVERFLOW);
		वापस 0;
	पूर्ण

	ret = xudc_eptxrx(ep, req, buf, count);
	चयन (ret) अणु
	हाल 0:
		req->usb_req.actual += min(count, bufferspace);
		dev_dbg(udc->dev, "read %s, %d bytes%s req %p %d/%d\n",
			ep->ep_usb.name, count, is_लघु ? "/S" : "", req,
			req->usb_req.actual, req->usb_req.length);
		bufferspace -= count;
		/* Completion */
		अगर ((req->usb_req.actual == req->usb_req.length) || is_लघु) अणु
			अगर (udc->dma_enabled && req->usb_req.length)
				dma_sync_single_क्रम_cpu(udc->dev,
							req->usb_req.dma,
							req->usb_req.actual,
							DMA_FROM_DEVICE);
			xudc_करोne(ep, req, 0);
			वापस 0;
		पूर्ण
		अगर (two_pkts) अणु
			two_pkts = 0;
			जाओ top;
		पूर्ण
		अवरोध;
	हाल -EAGAIN:
		dev_dbg(udc->dev, "receive busy\n");
		अवरोध;
	हाल -EINVAL:
	हाल -ETIMEDOUT:
		/* DMA error, dequeue the request */
		xudc_करोne(ep, req, -ECONNRESET);
		retval = 0;
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण

/**
 * xudc_ग_लिखो_fअगरo - Writes data पूर्णांकo the given endpoपूर्णांक buffer.
 * @ep: poपूर्णांकer to the usb device endpoपूर्णांक काष्ठाure.
 * @req: poपूर्णांकer to the usb request काष्ठाure.
 *
 * Return: 0 अगर request is completed and -EAGAIN अगर not completed.
 *
 * Loads endpoपूर्णांक buffer क्रम an IN packet.
 */
अटल पूर्णांक xudc_ग_लिखो_fअगरo(काष्ठा xusb_ep *ep, काष्ठा xusb_req *req)
अणु
	u32 max;
	u32 length;
	पूर्णांक ret;
	पूर्णांक retval = -EAGAIN;
	काष्ठा xusb_udc *udc = ep->udc;
	पूर्णांक is_last, is_लघु = 0;
	u8 *buf;

	max = le16_to_cpu(ep->desc->wMaxPacketSize);
	buf = req->usb_req.buf + req->usb_req.actual;
	prefetch(buf);
	length = req->usb_req.length - req->usb_req.actual;
	length = min(length, max);

	ret = xudc_eptxrx(ep, req, buf, length);
	चयन (ret) अणु
	हाल 0:
		req->usb_req.actual += length;
		अगर (unlikely(length != max)) अणु
			is_last = is_लघु = 1;
		पूर्ण अन्यथा अणु
			अगर (likely(req->usb_req.length !=
				   req->usb_req.actual) || req->usb_req.zero)
				is_last = 0;
			अन्यथा
				is_last = 1;
		पूर्ण
		dev_dbg(udc->dev, "%s: wrote %s %d bytes%s%s %d left %p\n",
			__func__, ep->ep_usb.name, length, is_last ? "/L" : "",
			is_लघु ? "/S" : "",
			req->usb_req.length - req->usb_req.actual, req);
		/* completion */
		अगर (is_last) अणु
			xudc_करोne(ep, req, 0);
			retval = 0;
		पूर्ण
		अवरोध;
	हाल -EAGAIN:
		dev_dbg(udc->dev, "Send busy\n");
		अवरोध;
	हाल -EINVAL:
	हाल -ETIMEDOUT:
		/* DMA error, dequeue the request */
		xudc_करोne(ep, req, -ECONNRESET);
		retval = 0;
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण

/**
 * xudc_nuke - Cleans up the data transfer message list.
 * @ep: poपूर्णांकer to the usb device endpoपूर्णांक काष्ठाure.
 * @status: Status of the data transfer.
 */
अटल व्योम xudc_nuke(काष्ठा xusb_ep *ep, पूर्णांक status)
अणु
	काष्ठा xusb_req *req;

	जबतक (!list_empty(&ep->queue)) अणु
		req = list_first_entry(&ep->queue, काष्ठा xusb_req, queue);
		xudc_करोne(ep, req, status);
	पूर्ण
पूर्ण

/**
 * xudc_ep_set_halt - Stalls/unstalls the given endpoपूर्णांक.
 * @_ep: poपूर्णांकer to the usb device endpoपूर्णांक काष्ठाure.
 * @value: value to indicate stall/unstall.
 *
 * Return: 0 क्रम success and error value on failure
 */
अटल पूर्णांक xudc_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा xusb_ep *ep = to_xusb_ep(_ep);
	काष्ठा xusb_udc *udc;
	अचिन्हित दीर्घ flags;
	u32 epcfgreg;

	अगर (!_ep || (!ep->desc && ep->epnumber)) अणु
		pr_debug("%s: bad ep or descriptor\n", __func__);
		वापस -EINVAL;
	पूर्ण
	udc = ep->udc;

	अगर (ep->is_in && (!list_empty(&ep->queue)) && value) अणु
		dev_dbg(udc->dev, "requests pending can't halt\n");
		वापस -EAGAIN;
	पूर्ण

	अगर (ep->buffer0पढ़ोy || ep->buffer1पढ़ोy) अणु
		dev_dbg(udc->dev, "HW buffers busy can't halt\n");
		वापस -EAGAIN;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);

	अगर (value) अणु
		/* Stall the device.*/
		epcfgreg = udc->पढ़ो_fn(udc->addr + ep->offset);
		epcfgreg |= XUSB_EP_CFG_STALL_MASK;
		udc->ग_लिखो_fn(udc->addr, ep->offset, epcfgreg);
	पूर्ण अन्यथा अणु
		/* Unstall the device.*/
		epcfgreg = udc->पढ़ो_fn(udc->addr + ep->offset);
		epcfgreg &= ~XUSB_EP_CFG_STALL_MASK;
		udc->ग_लिखो_fn(udc->addr, ep->offset, epcfgreg);
		अगर (ep->epnumber) अणु
			/* Reset the toggle bit.*/
			epcfgreg = udc->पढ़ो_fn(ep->udc->addr + ep->offset);
			epcfgreg &= ~XUSB_EP_CFG_DATA_TOGGLE_MASK;
			udc->ग_लिखो_fn(udc->addr, ep->offset, epcfgreg);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

/**
 * xudc_ep_enable - Enables the given endpoपूर्णांक.
 * @ep: poपूर्णांकer to the xusb endpoपूर्णांक काष्ठाure.
 * @desc: poपूर्णांकer to usb endpoपूर्णांक descriptor.
 *
 * Return: 0 क्रम success and error value on failure
 */
अटल पूर्णांक __xudc_ep_enable(काष्ठा xusb_ep *ep,
			    स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा xusb_udc *udc = ep->udc;
	u32 पंचांगp;
	u32 epcfg;
	u32 ier;
	u16 maxpacket;

	ep->is_in = ((desc->bEndpoपूर्णांकAddress & USB_सूची_IN) != 0);
	/* Bit 3...0:endpoपूर्णांक number */
	ep->epnumber = (desc->bEndpoपूर्णांकAddress & 0x0f);
	ep->desc = desc;
	ep->ep_usb.desc = desc;
	पंचांगp = desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;
	ep->ep_usb.maxpacket = maxpacket = le16_to_cpu(desc->wMaxPacketSize);

	चयन (पंचांगp) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		dev_dbg(udc->dev, "only one control endpoint\n");
		/* NON- ISO */
		ep->is_iso = 0;
		वापस -EINVAL;
	हाल USB_ENDPOINT_XFER_INT:
		/* NON- ISO */
		ep->is_iso = 0;
		अगर (maxpacket > 64) अणु
			dev_dbg(udc->dev, "bogus maxpacket %d\n", maxpacket);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		/* NON- ISO */
		ep->is_iso = 0;
		अगर (!(is_घातer_of_2(maxpacket) && maxpacket >= 8 &&
				maxpacket <= 512)) अणु
			dev_dbg(udc->dev, "bogus maxpacket %d\n", maxpacket);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		/* ISO */
		ep->is_iso = 1;
		अवरोध;
	पूर्ण

	ep->buffer0पढ़ोy = false;
	ep->buffer1पढ़ोy = false;
	ep->curbufnum = 0;
	ep->rambase = rambase[ep->epnumber];
	xudc_epconfig(ep, udc);

	dev_dbg(udc->dev, "Enable Endpoint %d max pkt is %d\n",
		ep->epnumber, maxpacket);

	/* Enable the End poपूर्णांक.*/
	epcfg = udc->पढ़ो_fn(udc->addr + ep->offset);
	epcfg |= XUSB_EP_CFG_VALID_MASK;
	udc->ग_लिखो_fn(udc->addr, ep->offset, epcfg);
	अगर (ep->epnumber)
		ep->rambase <<= 2;

	/* Enable buffer completion पूर्णांकerrupts क्रम endpoपूर्णांक */
	ier = udc->पढ़ो_fn(udc->addr + XUSB_IER_OFFSET);
	ier |= (XUSB_STATUS_INTR_BUFF_COMP_SHIFT_MASK << ep->epnumber);
	udc->ग_लिखो_fn(udc->addr, XUSB_IER_OFFSET, ier);

	/* क्रम OUT endpoपूर्णांक set buffers पढ़ोy to receive */
	अगर (ep->epnumber && !ep->is_in) अणु
		udc->ग_लिखो_fn(udc->addr, XUSB_BUFFREADY_OFFSET,
			      1 << ep->epnumber);
		ep->buffer0पढ़ोy = true;
		udc->ग_लिखो_fn(udc->addr, XUSB_BUFFREADY_OFFSET,
			     (1 << (ep->epnumber +
			      XUSB_STATUS_EP_BUFF2_SHIFT)));
		ep->buffer1पढ़ोy = true;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * xudc_ep_enable - Enables the given endpoपूर्णांक.
 * @_ep: poपूर्णांकer to the usb endpoपूर्णांक काष्ठाure.
 * @desc: poपूर्णांकer to usb endpoपूर्णांक descriptor.
 *
 * Return: 0 क्रम success and error value on failure
 */
अटल पूर्णांक xudc_ep_enable(काष्ठा usb_ep *_ep,
			  स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा xusb_ep *ep;
	काष्ठा xusb_udc *udc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!_ep || !desc || desc->bDescriptorType != USB_DT_ENDPOINT) अणु
		pr_debug("%s: bad ep or descriptor\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ep = to_xusb_ep(_ep);
	udc = ep->udc;

	अगर (!udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN) अणु
		dev_dbg(udc->dev, "bogus device state\n");
		वापस -ESHUTDOWN;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);
	ret = __xudc_ep_enable(ep, desc);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस ret;
पूर्ण

/**
 * xudc_ep_disable - Disables the given endpoपूर्णांक.
 * @_ep: poपूर्णांकer to the usb endpoपूर्णांक काष्ठाure.
 *
 * Return: 0 क्रम success and error value on failure
 */
अटल पूर्णांक xudc_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा xusb_ep *ep;
	अचिन्हित दीर्घ flags;
	u32 epcfg;
	काष्ठा xusb_udc *udc;

	अगर (!_ep) अणु
		pr_debug("%s: invalid ep\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ep = to_xusb_ep(_ep);
	udc = ep->udc;

	spin_lock_irqsave(&udc->lock, flags);

	xudc_nuke(ep, -ESHUTDOWN);

	/* Restore the endpoपूर्णांक's pristine config */
	ep->desc = शून्य;
	ep->ep_usb.desc = शून्य;

	dev_dbg(udc->dev, "USB Ep %d disable\n ", ep->epnumber);
	/* Disable the endpoपूर्णांक.*/
	epcfg = udc->पढ़ो_fn(udc->addr + ep->offset);
	epcfg &= ~XUSB_EP_CFG_VALID_MASK;
	udc->ग_लिखो_fn(udc->addr, ep->offset, epcfg);

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

/**
 * xudc_ep_alloc_request - Initializes the request queue.
 * @_ep: poपूर्णांकer to the usb endpoपूर्णांक काष्ठाure.
 * @gfp_flags: Flags related to the request call.
 *
 * Return: poपूर्णांकer to request काष्ठाure on success and a शून्य on failure.
 */
अटल काष्ठा usb_request *xudc_ep_alloc_request(काष्ठा usb_ep *_ep,
						 gfp_t gfp_flags)
अणु
	काष्ठा xusb_ep *ep = to_xusb_ep(_ep);
	काष्ठा xusb_req *req;

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;

	req->ep = ep;
	INIT_LIST_HEAD(&req->queue);
	वापस &req->usb_req;
पूर्ण

/**
 * xudc_मुक्त_request - Releases the request from queue.
 * @_ep: poपूर्णांकer to the usb device endpoपूर्णांक काष्ठाure.
 * @_req: poपूर्णांकer to the usb request काष्ठाure.
 */
अटल व्योम xudc_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा xusb_req *req = to_xusb_req(_req);

	kमुक्त(req);
पूर्ण

/**
 * xudc_ep0_queue - Adds the request to endpoपूर्णांक 0 queue.
 * @ep0: poपूर्णांकer to the xusb endpoपूर्णांक 0 काष्ठाure.
 * @req: poपूर्णांकer to the xusb request काष्ठाure.
 *
 * Return: 0 क्रम success and error value on failure
 */
अटल पूर्णांक __xudc_ep0_queue(काष्ठा xusb_ep *ep0, काष्ठा xusb_req *req)
अणु
	काष्ठा xusb_udc *udc = ep0->udc;
	u32 length;
	u8 *corebuf;

	अगर (!udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN) अणु
		dev_dbg(udc->dev, "%s, bogus device state\n", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (!list_empty(&ep0->queue)) अणु
		dev_dbg(udc->dev, "%s:ep0 busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	req->usb_req.status = -EINPROGRESS;
	req->usb_req.actual = 0;

	list_add_tail(&req->queue, &ep0->queue);

	अगर (udc->setup.bRequestType & USB_सूची_IN) अणु
		prefetch(req->usb_req.buf);
		length = req->usb_req.length;
		corebuf = (व्योम __क्रमce *) ((ep0->rambase << 2) +
			   udc->addr);
		length = req->usb_req.actual = min_t(u32, length,
						     EP0_MAX_PACKET);
		स_नकल(corebuf, req->usb_req.buf, length);
		udc->ग_लिखो_fn(udc->addr, XUSB_EP_BUF0COUNT_OFFSET, length);
		udc->ग_लिखो_fn(udc->addr, XUSB_BUFFREADY_OFFSET, 1);
	पूर्ण अन्यथा अणु
		अगर (udc->setup.wLength) अणु
			/* Enable EP0 buffer to receive data */
			udc->ग_लिखो_fn(udc->addr, XUSB_EP_BUF0COUNT_OFFSET, 0);
			udc->ग_लिखो_fn(udc->addr, XUSB_BUFFREADY_OFFSET, 1);
		पूर्ण अन्यथा अणु
			xudc_wrstatus(udc);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * xudc_ep0_queue - Adds the request to endpoपूर्णांक 0 queue.
 * @_ep: poपूर्णांकer to the usb endpoपूर्णांक 0 काष्ठाure.
 * @_req: poपूर्णांकer to the usb request काष्ठाure.
 * @gfp_flags: Flags related to the request call.
 *
 * Return: 0 क्रम success and error value on failure
 */
अटल पूर्णांक xudc_ep0_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
			  gfp_t gfp_flags)
अणु
	काष्ठा xusb_req *req	= to_xusb_req(_req);
	काष्ठा xusb_ep	*ep0	= to_xusb_ep(_ep);
	काष्ठा xusb_udc *udc	= ep0->udc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&udc->lock, flags);
	ret = __xudc_ep0_queue(ep0, req);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस ret;
पूर्ण

/**
 * xudc_ep_queue - Adds the request to endpoपूर्णांक queue.
 * @_ep: poपूर्णांकer to the usb endpoपूर्णांक काष्ठाure.
 * @_req: poपूर्णांकer to the usb request काष्ठाure.
 * @gfp_flags: Flags related to the request call.
 *
 * Return: 0 क्रम success and error value on failure
 */
अटल पूर्णांक xudc_ep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
			 gfp_t gfp_flags)
अणु
	काष्ठा xusb_req *req = to_xusb_req(_req);
	काष्ठा xusb_ep	*ep  = to_xusb_ep(_ep);
	काष्ठा xusb_udc *udc = ep->udc;
	पूर्णांक  ret;
	अचिन्हित दीर्घ flags;

	अगर (!ep->desc) अणु
		dev_dbg(udc->dev, "%s: queuing request to disabled %s\n",
			__func__, ep->name);
		वापस -ESHUTDOWN;
	पूर्ण

	अगर (!udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN) अणु
		dev_dbg(udc->dev, "%s, bogus device state\n", __func__);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	अगर (udc->dma_enabled) अणु
		ret = usb_gadget_map_request(&udc->gadget, &req->usb_req,
					     ep->is_in);
		अगर (ret) अणु
			dev_dbg(udc->dev, "gadget_map failed ep%d\n",
				ep->epnumber);
			spin_unlock_irqrestore(&udc->lock, flags);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	अगर (list_empty(&ep->queue)) अणु
		अगर (ep->is_in) अणु
			dev_dbg(udc->dev, "xudc_write_fifo from ep_queue\n");
			अगर (!xudc_ग_लिखो_fअगरo(ep, req))
				req = शून्य;
		पूर्ण अन्यथा अणु
			dev_dbg(udc->dev, "xudc_read_fifo from ep_queue\n");
			अगर (!xudc_पढ़ो_fअगरo(ep, req))
				req = शून्य;
		पूर्ण
	पूर्ण

	अगर (req != शून्य)
		list_add_tail(&req->queue, &ep->queue);

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

/**
 * xudc_ep_dequeue - Removes the request from the queue.
 * @_ep: poपूर्णांकer to the usb device endpoपूर्णांक काष्ठाure.
 * @_req: poपूर्णांकer to the usb request काष्ठाure.
 *
 * Return: 0 क्रम success and error value on failure
 */
अटल पूर्णांक xudc_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा xusb_ep *ep	= to_xusb_ep(_ep);
	काष्ठा xusb_req *req	= to_xusb_req(_req);
	काष्ठा xusb_udc *udc	= ep->udc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);
	/* Make sure it's actually queued on this endpoपूर्णांक */
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->usb_req == _req)
			अवरोध;
	पूर्ण
	अगर (&req->usb_req != _req) अणु
		spin_unlock_irqrestore(&udc->lock, flags);
		वापस -EINVAL;
	पूर्ण
	xudc_करोne(ep, req, -ECONNRESET);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/**
 * xudc_ep0_enable - Enables the given endpoपूर्णांक.
 * @ep: poपूर्णांकer to the usb endpoपूर्णांक काष्ठाure.
 * @desc: poपूर्णांकer to usb endpoपूर्णांक descriptor.
 *
 * Return: error always.
 *
 * endpoपूर्णांक 0 enable should not be called by gadget layer.
 */
अटल पूर्णांक xudc_ep0_enable(काष्ठा usb_ep *ep,
			   स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	वापस -EINVAL;
पूर्ण

/**
 * xudc_ep0_disable - Disables the given endpoपूर्णांक.
 * @ep: poपूर्णांकer to the usb endpoपूर्णांक काष्ठाure.
 *
 * Return: error always.
 *
 * endpoपूर्णांक 0 disable should not be called by gadget layer.
 */
अटल पूर्णांक xudc_ep0_disable(काष्ठा usb_ep *ep)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops xusb_ep0_ops = अणु
	.enable		= xudc_ep0_enable,
	.disable	= xudc_ep0_disable,
	.alloc_request	= xudc_ep_alloc_request,
	.मुक्त_request	= xudc_मुक्त_request,
	.queue		= xudc_ep0_queue,
	.dequeue	= xudc_ep_dequeue,
	.set_halt	= xudc_ep_set_halt,
पूर्ण;

अटल स्थिर काष्ठा usb_ep_ops xusb_ep_ops = अणु
	.enable		= xudc_ep_enable,
	.disable	= xudc_ep_disable,
	.alloc_request	= xudc_ep_alloc_request,
	.मुक्त_request	= xudc_मुक्त_request,
	.queue		= xudc_ep_queue,
	.dequeue	= xudc_ep_dequeue,
	.set_halt	= xudc_ep_set_halt,
पूर्ण;

/**
 * xudc_get_frame - Reads the current usb frame number.
 * @gadget: poपूर्णांकer to the usb gadget काष्ठाure.
 *
 * Return: current frame number क्रम success and error value on failure.
 */
अटल पूर्णांक xudc_get_frame(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा xusb_udc *udc;
	पूर्णांक frame;

	अगर (!gadget)
		वापस -ENODEV;

	udc = to_udc(gadget);
	frame = udc->पढ़ो_fn(udc->addr + XUSB_FRAMENUM_OFFSET);
	वापस frame;
पूर्ण

/**
 * xudc_wakeup - Send remote wakeup संकेत to host
 * @gadget: poपूर्णांकer to the usb gadget काष्ठाure.
 *
 * Return: 0 on success and error on failure
 */
अटल पूर्णांक xudc_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा xusb_udc *udc = to_udc(gadget);
	u32 crtlreg;
	पूर्णांक status = -EINVAL;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);

	/* Remote wake up not enabled by host */
	अगर (!udc->remote_wkp)
		जाओ करोne;

	crtlreg = udc->पढ़ो_fn(udc->addr + XUSB_CONTROL_OFFSET);
	crtlreg |= XUSB_CONTROL_USB_RMTWAKE_MASK;
	/* set remote wake up bit */
	udc->ग_लिखो_fn(udc->addr, XUSB_CONTROL_OFFSET, crtlreg);
	/*
	 * रुको क्रम a जबतक and reset remote wake up bit since this bit
	 * is not cleared by HW after sending remote wakeup to host.
	 */
	mdelay(2);

	crtlreg &= ~XUSB_CONTROL_USB_RMTWAKE_MASK;
	udc->ग_लिखो_fn(udc->addr, XUSB_CONTROL_OFFSET, crtlreg);
	status = 0;
करोne:
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस status;
पूर्ण

/**
 * xudc_pullup - start/stop USB traffic
 * @gadget: poपूर्णांकer to the usb gadget काष्ठाure.
 * @is_on: flag to start or stop
 *
 * Return: 0 always
 *
 * This function starts/stops SIE engine of IP based on is_on.
 */
अटल पूर्णांक xudc_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा xusb_udc *udc = to_udc(gadget);
	अचिन्हित दीर्घ flags;
	u32 crtlreg;

	spin_lock_irqsave(&udc->lock, flags);

	crtlreg = udc->पढ़ो_fn(udc->addr + XUSB_CONTROL_OFFSET);
	अगर (is_on)
		crtlreg |= XUSB_CONTROL_USB_READY_MASK;
	अन्यथा
		crtlreg &= ~XUSB_CONTROL_USB_READY_MASK;

	udc->ग_लिखो_fn(udc->addr, XUSB_CONTROL_OFFSET, crtlreg);

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/**
 * xudc_eps_init - initialize endpoपूर्णांकs.
 * @udc: poपूर्णांकer to the usb device controller काष्ठाure.
 */
अटल व्योम xudc_eps_init(काष्ठा xusb_udc *udc)
अणु
	u32 ep_number;

	INIT_LIST_HEAD(&udc->gadget.ep_list);

	क्रम (ep_number = 0; ep_number < XUSB_MAX_ENDPOINTS; ep_number++) अणु
		काष्ठा xusb_ep *ep = &udc->ep[ep_number];

		अगर (ep_number) अणु
			list_add_tail(&ep->ep_usb.ep_list,
				      &udc->gadget.ep_list);
			usb_ep_set_maxpacket_limit(&ep->ep_usb,
						  (अचिन्हित लघु) ~0);
			snम_लिखो(ep->name, EPNAME_SIZE, "ep%d", ep_number);
			ep->ep_usb.name = ep->name;
			ep->ep_usb.ops = &xusb_ep_ops;

			ep->ep_usb.caps.type_iso = true;
			ep->ep_usb.caps.type_bulk = true;
			ep->ep_usb.caps.type_पूर्णांक = true;
		पूर्ण अन्यथा अणु
			ep->ep_usb.name = ep0name;
			usb_ep_set_maxpacket_limit(&ep->ep_usb, EP0_MAX_PACKET);
			ep->ep_usb.ops = &xusb_ep0_ops;

			ep->ep_usb.caps.type_control = true;
		पूर्ण

		ep->ep_usb.caps.dir_in = true;
		ep->ep_usb.caps.dir_out = true;

		ep->udc = udc;
		ep->epnumber = ep_number;
		ep->desc = शून्य;
		/*
		 * The configuration रेजिस्टर address offset between
		 * each endpoपूर्णांक is 0x10.
		 */
		ep->offset = XUSB_EP0_CONFIG_OFFSET + (ep_number * 0x10);
		ep->is_in = 0;
		ep->is_iso = 0;
		ep->maxpacket = 0;
		xudc_epconfig(ep, udc);

		/* Initialize one queue per endpoपूर्णांक */
		INIT_LIST_HEAD(&ep->queue);
	पूर्ण
पूर्ण

/**
 * xudc_stop_activity - Stops any further activity on the device.
 * @udc: poपूर्णांकer to the usb device controller काष्ठाure.
 */
अटल व्योम xudc_stop_activity(काष्ठा xusb_udc *udc)
अणु
	पूर्णांक i;
	काष्ठा xusb_ep *ep;

	क्रम (i = 0; i < XUSB_MAX_ENDPOINTS; i++) अणु
		ep = &udc->ep[i];
		xudc_nuke(ep, -ESHUTDOWN);
	पूर्ण
पूर्ण

/**
 * xudc_start - Starts the device.
 * @gadget: poपूर्णांकer to the usb gadget काष्ठाure
 * @driver: poपूर्णांकer to gadget driver काष्ठाure
 *
 * Return: zero on success and error on failure
 */
अटल पूर्णांक xudc_start(काष्ठा usb_gadget *gadget,
		      काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा xusb_udc *udc	= to_udc(gadget);
	काष्ठा xusb_ep *ep0	= &udc->ep[XUSB_EP_NUMBER_ZERO];
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc = &config_bulk_out_desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&udc->lock, flags);

	अगर (udc->driver) अणु
		dev_err(udc->dev, "%s is already bound to %s\n",
			udc->gadget.name, udc->driver->driver.name);
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	/* hook up the driver */
	udc->driver = driver;
	udc->gadget.speed = driver->max_speed;

	/* Enable the control endpoपूर्णांक. */
	ret = __xudc_ep_enable(ep0, desc);

	/* Set device address and remote wakeup to 0 */
	udc->ग_लिखो_fn(udc->addr, XUSB_ADDRESS_OFFSET, 0);
	udc->remote_wkp = 0;
err:
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस ret;
पूर्ण

/**
 * xudc_stop - stops the device.
 * @gadget: poपूर्णांकer to the usb gadget काष्ठाure
 *
 * Return: zero always
 */
अटल पूर्णांक xudc_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा xusb_udc *udc = to_udc(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);

	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->driver = शून्य;

	/* Set device address and remote wakeup to 0 */
	udc->ग_लिखो_fn(udc->addr, XUSB_ADDRESS_OFFSET, 0);
	udc->remote_wkp = 0;

	xudc_stop_activity(udc);

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops xusb_udc_ops = अणु
	.get_frame	= xudc_get_frame,
	.wakeup		= xudc_wakeup,
	.pullup		= xudc_pullup,
	.udc_start	= xudc_start,
	.udc_stop	= xudc_stop,
पूर्ण;

/**
 * xudc_clear_stall_all_ep - clears stall of every endpoपूर्णांक.
 * @udc: poपूर्णांकer to the udc काष्ठाure.
 */
अटल व्योम xudc_clear_stall_all_ep(काष्ठा xusb_udc *udc)
अणु
	काष्ठा xusb_ep *ep;
	u32 epcfgreg;
	पूर्णांक i;

	क्रम (i = 0; i < XUSB_MAX_ENDPOINTS; i++) अणु
		ep = &udc->ep[i];
		epcfgreg = udc->पढ़ो_fn(udc->addr + ep->offset);
		epcfgreg &= ~XUSB_EP_CFG_STALL_MASK;
		udc->ग_लिखो_fn(udc->addr, ep->offset, epcfgreg);
		अगर (ep->epnumber) अणु
			/* Reset the toggle bit.*/
			epcfgreg = udc->पढ़ो_fn(udc->addr + ep->offset);
			epcfgreg &= ~XUSB_EP_CFG_DATA_TOGGLE_MASK;
			udc->ग_लिखो_fn(udc->addr, ep->offset, epcfgreg);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * xudc_startup_handler - The usb device controller पूर्णांकerrupt handler.
 * @udc: poपूर्णांकer to the udc काष्ठाure.
 * @पूर्णांकrstatus: The mask value containing the पूर्णांकerrupt sources.
 *
 * This function handles the RESET,SUSPEND,RESUME and DISCONNECT पूर्णांकerrupts.
 */
अटल व्योम xudc_startup_handler(काष्ठा xusb_udc *udc, u32 पूर्णांकrstatus)
अणु
	u32 पूर्णांकrreg;

	अगर (पूर्णांकrstatus & XUSB_STATUS_RESET_MASK) अणु

		dev_dbg(udc->dev, "Reset\n");

		अगर (पूर्णांकrstatus & XUSB_STATUS_HIGH_SPEED_MASK)
			udc->gadget.speed = USB_SPEED_HIGH;
		अन्यथा
			udc->gadget.speed = USB_SPEED_FULL;

		xudc_stop_activity(udc);
		xudc_clear_stall_all_ep(udc);
		udc->ग_लिखो_fn(udc->addr, XUSB_TESTMODE_OFFSET, 0);

		/* Set device address and remote wakeup to 0 */
		udc->ग_लिखो_fn(udc->addr, XUSB_ADDRESS_OFFSET, 0);
		udc->remote_wkp = 0;

		/* Enable the suspend, resume and disconnect */
		पूर्णांकrreg = udc->पढ़ो_fn(udc->addr + XUSB_IER_OFFSET);
		पूर्णांकrreg |= XUSB_STATUS_SUSPEND_MASK | XUSB_STATUS_RESUME_MASK |
			   XUSB_STATUS_DISCONNECT_MASK;
		udc->ग_लिखो_fn(udc->addr, XUSB_IER_OFFSET, पूर्णांकrreg);
	पूर्ण
	अगर (पूर्णांकrstatus & XUSB_STATUS_SUSPEND_MASK) अणु

		dev_dbg(udc->dev, "Suspend\n");

		/* Enable the reset, resume and disconnect */
		पूर्णांकrreg = udc->पढ़ो_fn(udc->addr + XUSB_IER_OFFSET);
		पूर्णांकrreg |= XUSB_STATUS_RESET_MASK | XUSB_STATUS_RESUME_MASK |
			   XUSB_STATUS_DISCONNECT_MASK;
		udc->ग_लिखो_fn(udc->addr, XUSB_IER_OFFSET, पूर्णांकrreg);

		udc->usb_state = USB_STATE_SUSPENDED;

		अगर (udc->driver->suspend) अणु
			spin_unlock(&udc->lock);
			udc->driver->suspend(&udc->gadget);
			spin_lock(&udc->lock);
		पूर्ण
	पूर्ण
	अगर (पूर्णांकrstatus & XUSB_STATUS_RESUME_MASK) अणु
		bool condition = (udc->usb_state != USB_STATE_SUSPENDED);

		dev_WARN_ONCE(udc->dev, condition,
				"Resume IRQ while not suspended\n");

		dev_dbg(udc->dev, "Resume\n");

		/* Enable the reset, suspend and disconnect */
		पूर्णांकrreg = udc->पढ़ो_fn(udc->addr + XUSB_IER_OFFSET);
		पूर्णांकrreg |= XUSB_STATUS_RESET_MASK | XUSB_STATUS_SUSPEND_MASK |
			   XUSB_STATUS_DISCONNECT_MASK;
		udc->ग_लिखो_fn(udc->addr, XUSB_IER_OFFSET, पूर्णांकrreg);

		udc->usb_state = 0;

		अगर (udc->driver->resume) अणु
			spin_unlock(&udc->lock);
			udc->driver->resume(&udc->gadget);
			spin_lock(&udc->lock);
		पूर्ण
	पूर्ण
	अगर (पूर्णांकrstatus & XUSB_STATUS_DISCONNECT_MASK) अणु

		dev_dbg(udc->dev, "Disconnect\n");

		/* Enable the reset, resume and suspend */
		पूर्णांकrreg = udc->पढ़ो_fn(udc->addr + XUSB_IER_OFFSET);
		पूर्णांकrreg |= XUSB_STATUS_RESET_MASK | XUSB_STATUS_RESUME_MASK |
			   XUSB_STATUS_SUSPEND_MASK;
		udc->ग_लिखो_fn(udc->addr, XUSB_IER_OFFSET, पूर्णांकrreg);

		अगर (udc->driver && udc->driver->disconnect) अणु
			spin_unlock(&udc->lock);
			udc->driver->disconnect(&udc->gadget);
			spin_lock(&udc->lock);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * xudc_ep0_stall - Stall endpoपूर्णांक zero.
 * @udc: poपूर्णांकer to the udc काष्ठाure.
 *
 * This function stalls endpoपूर्णांक zero.
 */
अटल व्योम xudc_ep0_stall(काष्ठा xusb_udc *udc)
अणु
	u32 epcfgreg;
	काष्ठा xusb_ep *ep0 = &udc->ep[XUSB_EP_NUMBER_ZERO];

	epcfgreg = udc->पढ़ो_fn(udc->addr + ep0->offset);
	epcfgreg |= XUSB_EP_CFG_STALL_MASK;
	udc->ग_लिखो_fn(udc->addr, ep0->offset, epcfgreg);
पूर्ण

/**
 * xudc_setaddress - executes SET_ADDRESS command
 * @udc: poपूर्णांकer to the udc काष्ठाure.
 *
 * This function executes USB SET_ADDRESS command
 */
अटल व्योम xudc_setaddress(काष्ठा xusb_udc *udc)
अणु
	काष्ठा xusb_ep *ep0	= &udc->ep[0];
	काष्ठा xusb_req *req	= udc->req;
	पूर्णांक ret;

	req->usb_req.length = 0;
	ret = __xudc_ep0_queue(ep0, req);
	अगर (ret == 0)
		वापस;

	dev_err(udc->dev, "Can't respond to SET ADDRESS request\n");
	xudc_ep0_stall(udc);
पूर्ण

/**
 * xudc_माला_लोtatus - executes GET_STATUS command
 * @udc: poपूर्णांकer to the udc काष्ठाure.
 *
 * This function executes USB GET_STATUS command
 */
अटल व्योम xudc_माला_लोtatus(काष्ठा xusb_udc *udc)
अणु
	काष्ठा xusb_ep *ep0	= &udc->ep[0];
	काष्ठा xusb_req *req	= udc->req;
	काष्ठा xusb_ep *target_ep;
	u16 status = 0;
	u32 epcfgreg;
	पूर्णांक epnum;
	u32 halt;
	पूर्णांक ret;

	चयन (udc->setup.bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		/* Get device status */
		status = 1 << USB_DEVICE_SELF_POWERED;
		अगर (udc->remote_wkp)
			status |= (1 << USB_DEVICE_REMOTE_WAKEUP);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		epnum = udc->setup.wIndex & USB_ENDPOINT_NUMBER_MASK;
		target_ep = &udc->ep[epnum];
		epcfgreg = udc->पढ़ो_fn(udc->addr + target_ep->offset);
		halt = epcfgreg & XUSB_EP_CFG_STALL_MASK;
		अगर (udc->setup.wIndex & USB_सूची_IN) अणु
			अगर (!target_ep->is_in)
				जाओ stall;
		पूर्ण अन्यथा अणु
			अगर (target_ep->is_in)
				जाओ stall;
		पूर्ण
		अगर (halt)
			status = 1 << USB_ENDPOINT_HALT;
		अवरोध;
	शेष:
		जाओ stall;
	पूर्ण

	req->usb_req.length = 2;
	*(u16 *)req->usb_req.buf = cpu_to_le16(status);
	ret = __xudc_ep0_queue(ep0, req);
	अगर (ret == 0)
		वापस;
stall:
	dev_err(udc->dev, "Can't respond to getstatus request\n");
	xudc_ep0_stall(udc);
पूर्ण

/**
 * xudc_set_clear_feature - Executes the set feature and clear feature commands.
 * @udc: poपूर्णांकer to the usb device controller काष्ठाure.
 *
 * Processes the SET_FEATURE and CLEAR_FEATURE commands.
 */
अटल व्योम xudc_set_clear_feature(काष्ठा xusb_udc *udc)
अणु
	काष्ठा xusb_ep *ep0	= &udc->ep[0];
	काष्ठा xusb_req *req	= udc->req;
	काष्ठा xusb_ep *target_ep;
	u8 endpoपूर्णांक;
	u8 outinbit;
	u32 epcfgreg;
	पूर्णांक flag = (udc->setup.bRequest == USB_REQ_SET_FEATURE ? 1 : 0);
	पूर्णांक ret;

	चयन (udc->setup.bRequestType) अणु
	हाल USB_RECIP_DEVICE:
		चयन (udc->setup.wValue) अणु
		हाल USB_DEVICE_TEST_MODE:
			/*
			 * The Test Mode will be executed
			 * after the status phase.
			 */
			अवरोध;
		हाल USB_DEVICE_REMOTE_WAKEUP:
			अगर (flag)
				udc->remote_wkp = 1;
			अन्यथा
				udc->remote_wkp = 0;
			अवरोध;
		शेष:
			xudc_ep0_stall(udc);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		अगर (!udc->setup.wValue) अणु
			endpoपूर्णांक = udc->setup.wIndex & USB_ENDPOINT_NUMBER_MASK;
			target_ep = &udc->ep[endpoपूर्णांक];
			outinbit = udc->setup.wIndex & USB_ENDPOINT_सूची_MASK;
			outinbit = outinbit >> 7;

			/* Make sure direction matches.*/
			अगर (outinbit != target_ep->is_in) अणु
				xudc_ep0_stall(udc);
				वापस;
			पूर्ण
			epcfgreg = udc->पढ़ो_fn(udc->addr + target_ep->offset);
			अगर (!endpoपूर्णांक) अणु
				/* Clear the stall.*/
				epcfgreg &= ~XUSB_EP_CFG_STALL_MASK;
				udc->ग_लिखो_fn(udc->addr,
					      target_ep->offset, epcfgreg);
			पूर्ण अन्यथा अणु
				अगर (flag) अणु
					epcfgreg |= XUSB_EP_CFG_STALL_MASK;
					udc->ग_लिखो_fn(udc->addr,
						      target_ep->offset,
						      epcfgreg);
				पूर्ण अन्यथा अणु
					/* Unstall the endpoपूर्णांक.*/
					epcfgreg &= ~(XUSB_EP_CFG_STALL_MASK |
						XUSB_EP_CFG_DATA_TOGGLE_MASK);
					udc->ग_लिखो_fn(udc->addr,
						      target_ep->offset,
						      epcfgreg);
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		xudc_ep0_stall(udc);
		वापस;
	पूर्ण

	req->usb_req.length = 0;
	ret = __xudc_ep0_queue(ep0, req);
	अगर (ret == 0)
		वापस;

	dev_err(udc->dev, "Can't respond to SET/CLEAR FEATURE\n");
	xudc_ep0_stall(udc);
पूर्ण

/**
 * xudc_handle_setup - Processes the setup packet.
 * @udc: poपूर्णांकer to the usb device controller काष्ठाure.
 *
 * Process setup packet and delegate to gadget layer.
 */
अटल व्योम xudc_handle_setup(काष्ठा xusb_udc *udc)
	__must_hold(&udc->lock)
अणु
	काष्ठा xusb_ep *ep0 = &udc->ep[0];
	काष्ठा usb_ctrlrequest setup;
	u32 *ep0rambase;

	/* Load up the chapter 9 command buffer.*/
	ep0rambase = (u32 __क्रमce *) (udc->addr + XUSB_SETUP_PKT_ADDR_OFFSET);
	स_नकल(&setup, ep0rambase, 8);

	udc->setup = setup;
	udc->setup.wValue = cpu_to_le16(setup.wValue);
	udc->setup.wIndex = cpu_to_le16(setup.wIndex);
	udc->setup.wLength = cpu_to_le16(setup.wLength);

	/* Clear previous requests */
	xudc_nuke(ep0, -ECONNRESET);

	अगर (udc->setup.bRequestType & USB_सूची_IN) अणु
		/* Execute the get command.*/
		udc->setupseqrx = STATUS_PHASE;
		udc->setupseqtx = DATA_PHASE;
	पूर्ण अन्यथा अणु
		/* Execute the put command.*/
		udc->setupseqrx = DATA_PHASE;
		udc->setupseqtx = STATUS_PHASE;
	पूर्ण

	चयन (udc->setup.bRequest) अणु
	हाल USB_REQ_GET_STATUS:
		/* Data+Status phase क्रमm udc */
		अगर ((udc->setup.bRequestType &
				(USB_सूची_IN | USB_TYPE_MASK)) !=
				(USB_सूची_IN | USB_TYPE_STANDARD))
			अवरोध;
		xudc_माला_लोtatus(udc);
		वापस;
	हाल USB_REQ_SET_ADDRESS:
		/* Status phase from udc */
		अगर (udc->setup.bRequestType != (USB_सूची_OUT |
				USB_TYPE_STANDARD | USB_RECIP_DEVICE))
			अवरोध;
		xudc_setaddress(udc);
		वापस;
	हाल USB_REQ_CLEAR_FEATURE:
	हाल USB_REQ_SET_FEATURE:
		/* Requests with no data phase, status phase from udc */
		अगर ((udc->setup.bRequestType & USB_TYPE_MASK)
				!= USB_TYPE_STANDARD)
			अवरोध;
		xudc_set_clear_feature(udc);
		वापस;
	शेष:
		अवरोध;
	पूर्ण

	spin_unlock(&udc->lock);
	अगर (udc->driver->setup(&udc->gadget, &setup) < 0)
		xudc_ep0_stall(udc);
	spin_lock(&udc->lock);
पूर्ण

/**
 * xudc_ep0_out - Processes the endpoपूर्णांक 0 OUT token.
 * @udc: poपूर्णांकer to the usb device controller काष्ठाure.
 */
अटल व्योम xudc_ep0_out(काष्ठा xusb_udc *udc)
अणु
	काष्ठा xusb_ep *ep0 = &udc->ep[0];
	काष्ठा xusb_req *req;
	u8 *ep0rambase;
	अचिन्हित पूर्णांक bytes_to_rx;
	व्योम *buffer;

	req = list_first_entry(&ep0->queue, काष्ठा xusb_req, queue);

	चयन (udc->setupseqrx) अणु
	हाल STATUS_PHASE:
		/*
		 * This resets both state machines क्रम the next
		 * Setup packet.
		 */
		udc->setupseqrx = SETUP_PHASE;
		udc->setupseqtx = SETUP_PHASE;
		req->usb_req.actual = req->usb_req.length;
		xudc_करोne(ep0, req, 0);
		अवरोध;
	हाल DATA_PHASE:
		bytes_to_rx = udc->पढ़ो_fn(udc->addr +
					   XUSB_EP_BUF0COUNT_OFFSET);
		/* Copy the data to be received from the DPRAM. */
		ep0rambase = (u8 __क्रमce *) (udc->addr +
			     (ep0->rambase << 2));
		buffer = req->usb_req.buf + req->usb_req.actual;
		req->usb_req.actual = req->usb_req.actual + bytes_to_rx;
		स_नकल(buffer, ep0rambase, bytes_to_rx);

		अगर (req->usb_req.length == req->usb_req.actual) अणु
			/* Data transfer completed get पढ़ोy क्रम Status stage */
			xudc_wrstatus(udc);
		पूर्ण अन्यथा अणु
			/* Enable EP0 buffer to receive data */
			udc->ग_लिखो_fn(udc->addr, XUSB_EP_BUF0COUNT_OFFSET, 0);
			udc->ग_लिखो_fn(udc->addr, XUSB_BUFFREADY_OFFSET, 1);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * xudc_ep0_in - Processes the endpoपूर्णांक 0 IN token.
 * @udc: poपूर्णांकer to the usb device controller काष्ठाure.
 */
अटल व्योम xudc_ep0_in(काष्ठा xusb_udc *udc)
अणु
	काष्ठा xusb_ep *ep0 = &udc->ep[0];
	काष्ठा xusb_req *req;
	अचिन्हित पूर्णांक bytes_to_tx;
	व्योम *buffer;
	u32 epcfgreg;
	u16 count = 0;
	u16 length;
	u8 *ep0rambase;
	u8 test_mode = udc->setup.wIndex >> 8;

	req = list_first_entry(&ep0->queue, काष्ठा xusb_req, queue);
	bytes_to_tx = req->usb_req.length - req->usb_req.actual;

	चयन (udc->setupseqtx) अणु
	हाल STATUS_PHASE:
		चयन (udc->setup.bRequest) अणु
		हाल USB_REQ_SET_ADDRESS:
			/* Set the address of the device.*/
			udc->ग_लिखो_fn(udc->addr, XUSB_ADDRESS_OFFSET,
				      udc->setup.wValue);
			अवरोध;
		हाल USB_REQ_SET_FEATURE:
			अगर (udc->setup.bRequestType ==
					USB_RECIP_DEVICE) अणु
				अगर (udc->setup.wValue ==
						USB_DEVICE_TEST_MODE)
					udc->ग_लिखो_fn(udc->addr,
						      XUSB_TESTMODE_OFFSET,
						      test_mode);
			पूर्ण
			अवरोध;
		पूर्ण
		req->usb_req.actual = req->usb_req.length;
		xudc_करोne(ep0, req, 0);
		अवरोध;
	हाल DATA_PHASE:
		अगर (!bytes_to_tx) अणु
			/*
			 * We're करोne with data transfer, next
			 * will be zero length OUT with data toggle of
			 * 1. Setup data_toggle.
			 */
			epcfgreg = udc->पढ़ो_fn(udc->addr + ep0->offset);
			epcfgreg |= XUSB_EP_CFG_DATA_TOGGLE_MASK;
			udc->ग_लिखो_fn(udc->addr, ep0->offset, epcfgreg);
			udc->setupseqtx = STATUS_PHASE;
		पूर्ण अन्यथा अणु
			length = count = min_t(u32, bytes_to_tx,
					       EP0_MAX_PACKET);
			/* Copy the data to be transmitted पूर्णांकo the DPRAM. */
			ep0rambase = (u8 __क्रमce *) (udc->addr +
				     (ep0->rambase << 2));
			buffer = req->usb_req.buf + req->usb_req.actual;
			req->usb_req.actual = req->usb_req.actual + length;
			स_नकल(ep0rambase, buffer, length);
		पूर्ण
		udc->ग_लिखो_fn(udc->addr, XUSB_EP_BUF0COUNT_OFFSET, count);
		udc->ग_लिखो_fn(udc->addr, XUSB_BUFFREADY_OFFSET, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * xudc_ctrl_ep_handler - Endpoपूर्णांक 0 पूर्णांकerrupt handler.
 * @udc: poपूर्णांकer to the udc काष्ठाure.
 * @पूर्णांकrstatus:	It's the mask value क्रम the पूर्णांकerrupt sources on endpoपूर्णांक 0.
 *
 * Processes the commands received during क्रमागतeration phase.
 */
अटल व्योम xudc_ctrl_ep_handler(काष्ठा xusb_udc *udc, u32 पूर्णांकrstatus)
अणु

	अगर (पूर्णांकrstatus & XUSB_STATUS_SETUP_PACKET_MASK) अणु
		xudc_handle_setup(udc);
	पूर्ण अन्यथा अणु
		अगर (पूर्णांकrstatus & XUSB_STATUS_FIFO_BUFF_RDY_MASK)
			xudc_ep0_out(udc);
		अन्यथा अगर (पूर्णांकrstatus & XUSB_STATUS_FIFO_BUFF_FREE_MASK)
			xudc_ep0_in(udc);
	पूर्ण
पूर्ण

/**
 * xudc_nonctrl_ep_handler - Non control endpoपूर्णांक पूर्णांकerrupt handler.
 * @udc: poपूर्णांकer to the udc काष्ठाure.
 * @epnum: End poपूर्णांक number क्रम which the पूर्णांकerrupt is to be processed
 * @पूर्णांकrstatus:	mask value क्रम पूर्णांकerrupt sources of endpoपूर्णांकs other
 *		than endpoपूर्णांक 0.
 *
 * Processes the buffer completion पूर्णांकerrupts.
 */
अटल व्योम xudc_nonctrl_ep_handler(काष्ठा xusb_udc *udc, u8 epnum,
				    u32 पूर्णांकrstatus)
अणु

	काष्ठा xusb_req *req;
	काष्ठा xusb_ep *ep;

	ep = &udc->ep[epnum];
	/* Process the End poपूर्णांक पूर्णांकerrupts.*/
	अगर (पूर्णांकrstatus & (XUSB_STATUS_EP0_BUFF1_COMP_MASK << epnum))
		ep->buffer0पढ़ोy = 0;
	अगर (पूर्णांकrstatus & (XUSB_STATUS_EP0_BUFF2_COMP_MASK << epnum))
		ep->buffer1पढ़ोy = false;

	अगर (list_empty(&ep->queue))
		वापस;

	req = list_first_entry(&ep->queue, काष्ठा xusb_req, queue);

	अगर (ep->is_in)
		xudc_ग_लिखो_fअगरo(ep, req);
	अन्यथा
		xudc_पढ़ो_fअगरo(ep, req);
पूर्ण

/**
 * xudc_irq - The मुख्य पूर्णांकerrupt handler.
 * @irq: The पूर्णांकerrupt number.
 * @_udc: poपूर्णांकer to the usb device controller काष्ठाure.
 *
 * Return: IRQ_HANDLED after the पूर्णांकerrupt is handled.
 */
अटल irqवापस_t xudc_irq(पूर्णांक irq, व्योम *_udc)
अणु
	काष्ठा xusb_udc *udc = _udc;
	u32 पूर्णांकrstatus;
	u32 ier;
	u8 index;
	u32 bufपूर्णांकr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);

	/*
	 * Event पूर्णांकerrupts are level sensitive hence first disable
	 * IER, पढ़ो ISR and figure out active पूर्णांकerrupts.
	 */
	ier = udc->पढ़ो_fn(udc->addr + XUSB_IER_OFFSET);
	ier &= ~XUSB_STATUS_INTR_EVENT_MASK;
	udc->ग_लिखो_fn(udc->addr, XUSB_IER_OFFSET, ier);

	/* Read the Interrupt Status Register.*/
	पूर्णांकrstatus = udc->पढ़ो_fn(udc->addr + XUSB_STATUS_OFFSET);

	/* Call the handler क्रम the event पूर्णांकerrupt.*/
	अगर (पूर्णांकrstatus & XUSB_STATUS_INTR_EVENT_MASK) अणु
		/*
		 * Check अगर there is any action to be करोne क्रम :
		 * - USB Reset received अणुXUSB_STATUS_RESET_MASKपूर्ण
		 * - USB Suspend received अणुXUSB_STATUS_SUSPEND_MASKपूर्ण
		 * - USB Resume received अणुXUSB_STATUS_RESUME_MASKपूर्ण
		 * - USB Disconnect received अणुXUSB_STATUS_DISCONNECT_MASKपूर्ण
		 */
		xudc_startup_handler(udc, पूर्णांकrstatus);
	पूर्ण

	/* Check the buffer completion पूर्णांकerrupts */
	अगर (पूर्णांकrstatus & XUSB_STATUS_INTR_BUFF_COMP_ALL_MASK) अणु
		/* Enable Reset, Suspend, Resume and Disconnect  */
		ier = udc->पढ़ो_fn(udc->addr + XUSB_IER_OFFSET);
		ier |= XUSB_STATUS_INTR_EVENT_MASK;
		udc->ग_लिखो_fn(udc->addr, XUSB_IER_OFFSET, ier);

		अगर (पूर्णांकrstatus & XUSB_STATUS_EP0_BUFF1_COMP_MASK)
			xudc_ctrl_ep_handler(udc, पूर्णांकrstatus);

		क्रम (index = 1; index < 8; index++) अणु
			bufपूर्णांकr = ((पूर्णांकrstatus &
				  (XUSB_STATUS_EP1_BUFF1_COMP_MASK <<
				  (index - 1))) || (पूर्णांकrstatus &
				  (XUSB_STATUS_EP1_BUFF2_COMP_MASK <<
				  (index - 1))));
			अगर (bufपूर्णांकr) अणु
				xudc_nonctrl_ep_handler(udc, index,
							पूर्णांकrstatus);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * xudc_probe - The device probe function क्रम driver initialization.
 * @pdev: poपूर्णांकer to the platक्रमm device काष्ठाure.
 *
 * Return: 0 क्रम success and error value on failure
 */
अटल पूर्णांक xudc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *res;
	काष्ठा xusb_udc *udc;
	पूर्णांक irq;
	पूर्णांक ret;
	u32 ier;
	u8 *buff;

	udc = devm_kzalloc(&pdev->dev, माप(*udc), GFP_KERNEL);
	अगर (!udc)
		वापस -ENOMEM;

	/* Create a dummy request क्रम GET_STATUS, SET_ADDRESS */
	udc->req = devm_kzalloc(&pdev->dev, माप(काष्ठा xusb_req),
				GFP_KERNEL);
	अगर (!udc->req)
		वापस -ENOMEM;

	buff = devm_kzalloc(&pdev->dev, STATUSBUFF_SIZE, GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;

	udc->req->usb_req.buf = buff;

	/* Map the रेजिस्टरs */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	udc->addr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(udc->addr))
		वापस PTR_ERR(udc->addr);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	ret = devm_request_irq(&pdev->dev, irq, xudc_irq, 0,
			       dev_name(&pdev->dev), udc);
	अगर (ret < 0) अणु
		dev_dbg(&pdev->dev, "unable to request irq %d", irq);
		जाओ fail;
	पूर्ण

	udc->dma_enabled = of_property_पढ़ो_bool(np, "xlnx,has-builtin-dma");

	/* Setup gadget काष्ठाure */
	udc->gadget.ops = &xusb_udc_ops;
	udc->gadget.max_speed = USB_SPEED_HIGH;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->gadget.ep0 = &udc->ep[XUSB_EP_NUMBER_ZERO].ep_usb;
	udc->gadget.name = driver_name;

	spin_lock_init(&udc->lock);

	/* Check क्रम IP endianness */
	udc->ग_लिखो_fn = xudc_ग_लिखो32_be;
	udc->पढ़ो_fn = xudc_पढ़ो32_be;
	udc->ग_लिखो_fn(udc->addr, XUSB_TESTMODE_OFFSET, USB_TEST_J);
	अगर ((udc->पढ़ो_fn(udc->addr + XUSB_TESTMODE_OFFSET))
			!= USB_TEST_J) अणु
		udc->ग_लिखो_fn = xudc_ग_लिखो32;
		udc->पढ़ो_fn = xudc_पढ़ो32;
	पूर्ण
	udc->ग_लिखो_fn(udc->addr, XUSB_TESTMODE_OFFSET, 0);

	xudc_eps_init(udc);

	/* Set device address to 0.*/
	udc->ग_लिखो_fn(udc->addr, XUSB_ADDRESS_OFFSET, 0);

	ret = usb_add_gadget_udc(&pdev->dev, &udc->gadget);
	अगर (ret)
		जाओ fail;

	udc->dev = &udc->gadget.dev;

	/* Enable the पूर्णांकerrupts.*/
	ier = XUSB_STATUS_GLOBAL_INTR_MASK | XUSB_STATUS_INTR_EVENT_MASK |
	      XUSB_STATUS_FIFO_BUFF_RDY_MASK | XUSB_STATUS_FIFO_BUFF_FREE_MASK |
	      XUSB_STATUS_SETUP_PACKET_MASK |
	      XUSB_STATUS_INTR_BUFF_COMP_ALL_MASK;

	udc->ग_लिखो_fn(udc->addr, XUSB_IER_OFFSET, ier);

	platक्रमm_set_drvdata(pdev, udc);

	dev_vdbg(&pdev->dev, "%s at 0x%08X mapped to %p %s\n",
		 driver_name, (u32)res->start, udc->addr,
		 udc->dma_enabled ? "with DMA" : "without DMA");

	वापस 0;
fail:
	dev_err(&pdev->dev, "probe failed, %d\n", ret);
	वापस ret;
पूर्ण

/**
 * xudc_हटाओ - Releases the resources allocated during the initialization.
 * @pdev: poपूर्णांकer to the platक्रमm device काष्ठाure.
 *
 * Return: 0 always
 */
अटल पूर्णांक xudc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xusb_udc *udc = platक्रमm_get_drvdata(pdev);

	usb_del_gadget_udc(&udc->gadget);

	वापस 0;
पूर्ण

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id usb_of_match[] = अणु
	अणु .compatible = "xlnx,usb2-device-4.00.a", पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, usb_of_match);

अटल काष्ठा platक्रमm_driver xudc_driver = अणु
	.driver = अणु
		.name = driver_name,
		.of_match_table = usb_of_match,
	पूर्ण,
	.probe = xudc_probe,
	.हटाओ = xudc_हटाओ,
पूर्ण;

module_platक्रमm_driver(xudc_driver);

MODULE_DESCRIPTION("Xilinx udc driver");
MODULE_AUTHOR("Xilinx, Inc");
MODULE_LICENSE("GPL");
