<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  drivers/usb/gadget/emxx_udc.c
 *     EMXX FCD (Function Controller Driver) क्रम USB.
 *
 *  Copyright (C) 2010 Renesas Electronics Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/clk.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/device.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>

#समावेश <linux/irq.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "emxx_udc.h"

#घोषणा	DRIVER_DESC	"EMXX UDC driver"
#घोषणा	DMA_ADDR_INVALID	(~(dma_addr_t)0)

अटल काष्ठा gpio_desc *vbus_gpio;
अटल पूर्णांक vbus_irq;

अटल स्थिर अक्षर	driver_name[] = "emxx_udc";

/*===========================================================================*/
/* Prototype */
अटल व्योम _nbu2ss_ep_dma_पात(काष्ठा nbu2ss_udc *, काष्ठा nbu2ss_ep *);
अटल व्योम _nbu2ss_ep0_enable(काष्ठा nbu2ss_udc *);
/*अटल व्योम _nbu2ss_ep0_disable(काष्ठा nbu2ss_udc *);*/
अटल व्योम _nbu2ss_ep_करोne(काष्ठा nbu2ss_ep *, काष्ठा nbu2ss_req *, पूर्णांक);
अटल व्योम _nbu2ss_set_test_mode(काष्ठा nbu2ss_udc *, u32 mode);
अटल व्योम _nbu2ss_endpoपूर्णांक_toggle_reset(काष्ठा nbu2ss_udc *udc, u8 ep_adrs);

अटल पूर्णांक _nbu2ss_pullup(काष्ठा nbu2ss_udc *, पूर्णांक);
अटल व्योम _nbu2ss_fअगरo_flush(काष्ठा nbu2ss_udc *, काष्ठा nbu2ss_ep *);

/*===========================================================================*/
/* Macro */
#घोषणा	_nbu2ss_zero_len_pkt(udc, epnum)	\
	_nbu2ss_ep_in_end(udc, epnum, 0, 0)

/*===========================================================================*/
/* Global */
अटल काष्ठा nbu2ss_udc udc_controller;

/*-------------------------------------------------------------------------*/
/* Read */
अटल अंतरभूत u32 _nbu2ss_पढ़ोl(व्योम __iomem *address)
अणु
	वापस __raw_पढ़ोl(address);
पूर्ण

/*-------------------------------------------------------------------------*/
/* Write */
अटल अंतरभूत व्योम _nbu2ss_ग_लिखोl(व्योम __iomem *address, u32 udata)
अणु
	__raw_ग_लिखोl(udata, address);
पूर्ण

/*-------------------------------------------------------------------------*/
/* Set Bit */
अटल अंतरभूत व्योम _nbu2ss_bitset(व्योम __iomem *address, u32 udata)
अणु
	u32	reg_dt = __raw_पढ़ोl(address) | (udata);

	__raw_ग_लिखोl(reg_dt, address);
पूर्ण

/*-------------------------------------------------------------------------*/
/* Clear Bit */
अटल अंतरभूत व्योम _nbu2ss_bitclr(व्योम __iomem *address, u32 udata)
अणु
	u32	reg_dt = __raw_पढ़ोl(address) & ~(udata);

	__raw_ग_लिखोl(reg_dt, address);
पूर्ण

#अगर_घोषित UDC_DEBUG_DUMP
/*-------------------------------------------------------------------------*/
अटल व्योम _nbu2ss_dump_रेजिस्टर(काष्ठा nbu2ss_udc *udc)
अणु
	पूर्णांक		i;
	u32 reg_data;

	pr_info("=== %s()\n", __func__);

	अगर (!udc) अणु
		pr_err("%s udc == NULL\n", __func__);
		वापस;
	पूर्ण

	spin_unlock(&udc->lock);

	dev_dbg(&udc->dev, "\n-USB REG-\n");
	क्रम (i = 0x0 ; i < USB_BASE_SIZE ; i += 16) अणु
		reg_data = _nbu2ss_पढ़ोl(IO_ADDRESS(USB_BASE_ADDRESS + i));
		dev_dbg(&udc->dev, "USB%04x =%08x", i, (पूर्णांक)reg_data);

		reg_data = _nbu2ss_पढ़ोl(IO_ADDRESS(USB_BASE_ADDRESS + i + 4));
		dev_dbg(&udc->dev, " %08x", (पूर्णांक)reg_data);

		reg_data = _nbu2ss_पढ़ोl(IO_ADDRESS(USB_BASE_ADDRESS + i + 8));
		dev_dbg(&udc->dev, " %08x", (पूर्णांक)reg_data);

		reg_data = _nbu2ss_पढ़ोl(IO_ADDRESS(USB_BASE_ADDRESS + i + 12));
		dev_dbg(&udc->dev, " %08x\n", (पूर्णांक)reg_data);
	पूर्ण

	spin_lock(&udc->lock);
पूर्ण
#पूर्ण_अगर /* UDC_DEBUG_DUMP */

/*-------------------------------------------------------------------------*/
/* Endpoपूर्णांक 0 Callback (Complete) */
अटल व्योम _nbu2ss_ep0_complete(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	u8		recipient;
	u16		selector;
	u16		wIndex;
	u32		test_mode;
	काष्ठा usb_ctrlrequest	*p_ctrl;
	काष्ठा nbu2ss_udc *udc;

	अगर (!_ep || !_req)
		वापस;

	udc = (काष्ठा nbu2ss_udc *)_req->context;
	p_ctrl = &udc->ctrl;
	अगर ((p_ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) अणु
		अगर (p_ctrl->bRequest == USB_REQ_SET_FEATURE) अणु
			/*-------------------------------------------------*/
			/* SET_FEATURE */
			recipient = (u8)(p_ctrl->bRequestType & USB_RECIP_MASK);
			selector  = le16_to_cpu(p_ctrl->wValue);
			अगर ((recipient == USB_RECIP_DEVICE) &&
			    (selector == USB_DEVICE_TEST_MODE)) अणु
				wIndex = le16_to_cpu(p_ctrl->wIndex);
				test_mode = (u32)(wIndex >> 8);
				_nbu2ss_set_test_mode(udc, test_mode);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
/* Initialization usb_request */
अटल व्योम _nbu2ss_create_ep0_packet(काष्ठा nbu2ss_udc *udc,
				      व्योम *p_buf, अचिन्हित पूर्णांक length)
अणु
	udc->ep0_req.req.buf		= p_buf;
	udc->ep0_req.req.length		= length;
	udc->ep0_req.req.dma		= 0;
	udc->ep0_req.req.zero		= true;
	udc->ep0_req.req.complete	= _nbu2ss_ep0_complete;
	udc->ep0_req.req.status		= -EINPROGRESS;
	udc->ep0_req.req.context	= udc;
	udc->ep0_req.req.actual		= 0;
पूर्ण

/*-------------------------------------------------------------------------*/
/* Acquisition of the first address of RAM(FIFO) */
अटल u32 _nbu2ss_get_begin_ram_address(काष्ठा nbu2ss_udc *udc)
अणु
	u32		num, buf_type;
	u32		data, last_ram_adr, use_ram_size;

	काष्ठा ep_regs __iomem *p_ep_regs;

	last_ram_adr = (D_RAM_SIZE_CTRL / माप(u32)) * 2;
	use_ram_size = 0;

	क्रम (num = 0; num < NUM_ENDPOINTS - 1; num++) अणु
		p_ep_regs = &udc->p_regs->EP_REGS[num];
		data = _nbu2ss_पढ़ोl(&p_ep_regs->EP_PCKT_ADRS);
		buf_type = _nbu2ss_पढ़ोl(&p_ep_regs->EP_CONTROL) & EPN_BUF_TYPE;
		अगर (buf_type == 0) अणु
			/* Single Buffer */
			use_ram_size += (data & EPN_MPKT) / माप(u32);
		पूर्ण अन्यथा अणु
			/* Double Buffer */
			use_ram_size += ((data & EPN_MPKT) / माप(u32)) * 2;
		पूर्ण

		अगर ((data >> 16) > last_ram_adr)
			last_ram_adr = data >> 16;
	पूर्ण

	वापस last_ram_adr + use_ram_size;
पूर्ण

/*-------------------------------------------------------------------------*/
/* Conकाष्ठाion of Endpoपूर्णांक */
अटल पूर्णांक _nbu2ss_ep_init(काष्ठा nbu2ss_udc *udc, काष्ठा nbu2ss_ep *ep)
अणु
	u32		num;
	u32		data;
	u32		begin_adrs;

	अगर (ep->epnum == 0)
		वापस	-EINVAL;

	num = ep->epnum - 1;

	/*-------------------------------------------------------------*/
	/* RAM Transfer Address */
	begin_adrs = _nbu2ss_get_begin_ram_address(udc);
	data = (begin_adrs << 16) | ep->ep.maxpacket;
	_nbu2ss_ग_लिखोl(&udc->p_regs->EP_REGS[num].EP_PCKT_ADRS, data);

	/*-------------------------------------------------------------*/
	/* Interrupt Enable */
	data = 1 << (ep->epnum + 8);
	_nbu2ss_bitset(&udc->p_regs->USB_INT_ENA, data);

	/*-------------------------------------------------------------*/
	/* Endpoपूर्णांक Type(Mode) */
	/*   Bulk, Interrupt, ISO */
	चयन (ep->ep_type) अणु
	हाल USB_ENDPOINT_XFER_BULK:
		data = EPN_BULK;
		अवरोध;

	हाल USB_ENDPOINT_XFER_INT:
		data = EPN_BUF_SINGLE | EPN_INTERRUPT;
		अवरोध;

	हाल USB_ENDPOINT_XFER_ISOC:
		data = EPN_ISO;
		अवरोध;

	शेष:
		data = 0;
		अवरोध;
	पूर्ण

	_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);
	_nbu2ss_endpoपूर्णांक_toggle_reset(udc, (ep->epnum | ep->direct));

	अगर (ep->direct == USB_सूची_OUT) अणु
		/*---------------------------------------------------------*/
		/* OUT */
		data = EPN_EN | EPN_BCLR | EPN_सूची0;
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_ONAK | EPN_OSTL_EN | EPN_OSTL;
		_nbu2ss_bitclr(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_OUT_EN | EPN_OUT_END_EN;
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_INT_ENA, data);
	पूर्ण अन्यथा अणु
		/*---------------------------------------------------------*/
		/* IN */
		data = EPN_EN | EPN_BCLR | EPN_AUTO;
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_ISTL;
		_nbu2ss_bitclr(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_IN_EN | EPN_IN_END_EN;
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_INT_ENA, data);
	पूर्ण

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
/* Release of Endpoपूर्णांक */
अटल पूर्णांक _nbu2ss_epn_निकास(काष्ठा nbu2ss_udc *udc, काष्ठा nbu2ss_ep *ep)
अणु
	u32		num;
	u32		data;

	अगर ((ep->epnum == 0) || (udc->vbus_active == 0))
		वापस	-EINVAL;

	num = ep->epnum - 1;

	/*-------------------------------------------------------------*/
	/* RAM Transfer Address */
	_nbu2ss_ग_लिखोl(&udc->p_regs->EP_REGS[num].EP_PCKT_ADRS, 0);

	/*-------------------------------------------------------------*/
	/* Interrupt Disable */
	data = 1 << (ep->epnum + 8);
	_nbu2ss_bitclr(&udc->p_regs->USB_INT_ENA, data);

	अगर (ep->direct == USB_सूची_OUT) अणु
		/*---------------------------------------------------------*/
		/* OUT */
		data = EPN_ONAK | EPN_BCLR;
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_EN | EPN_सूची0;
		_nbu2ss_bitclr(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_OUT_EN | EPN_OUT_END_EN;
		_nbu2ss_bitclr(&udc->p_regs->EP_REGS[num].EP_INT_ENA, data);
	पूर्ण अन्यथा अणु
		/*---------------------------------------------------------*/
		/* IN */
		data = EPN_BCLR;
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_EN | EPN_AUTO;
		_nbu2ss_bitclr(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);

		data = EPN_IN_EN | EPN_IN_END_EN;
		_nbu2ss_bitclr(&udc->p_regs->EP_REGS[num].EP_INT_ENA, data);
	पूर्ण

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
/* DMA setting (without Endpoपूर्णांक 0) */
अटल व्योम _nbu2ss_ep_dma_init(काष्ठा nbu2ss_udc *udc, काष्ठा nbu2ss_ep *ep)
अणु
	u32		num;
	u32		data;

	data = _nbu2ss_पढ़ोl(&udc->p_regs->USBSSCONF);
	अगर (((ep->epnum == 0) || (data & (1 << ep->epnum)) == 0))
		वापस;		/* Not Support DMA */

	num = ep->epnum - 1;

	अगर (ep->direct == USB_सूची_OUT) अणु
		/*---------------------------------------------------------*/
		/* OUT */
		data = ep->ep.maxpacket;
		_nbu2ss_ग_लिखोl(&udc->p_regs->EP_DCR[num].EP_DCR2, data);

		/*---------------------------------------------------------*/
		/* Transfer Direct */
		data = DCR1_EPN_सूची0;
		_nbu2ss_bitset(&udc->p_regs->EP_DCR[num].EP_DCR1, data);

		/*---------------------------------------------------------*/
		/* DMA Mode etc. */
		data = EPN_STOP_MODE | EPN_STOP_SET  | EPN_DMAMODE0;
		_nbu2ss_ग_लिखोl(&udc->p_regs->EP_REGS[num].EP_DMA_CTRL, data);
	पूर्ण अन्यथा अणु
		/*---------------------------------------------------------*/
		/* IN */
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_CONTROL, EPN_AUTO);

		/*---------------------------------------------------------*/
		/* DMA Mode etc. */
		data = EPN_BURST_SET | EPN_DMAMODE0;
		_nbu2ss_ग_लिखोl(&udc->p_regs->EP_REGS[num].EP_DMA_CTRL, data);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
/* DMA setting release */
अटल व्योम _nbu2ss_ep_dma_निकास(काष्ठा nbu2ss_udc *udc, काष्ठा nbu2ss_ep *ep)
अणु
	u32		num;
	u32		data;
	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	अगर (udc->vbus_active == 0)
		वापस;		/* VBUS OFF */

	data = _nbu2ss_पढ़ोl(&preg->USBSSCONF);
	अगर ((ep->epnum == 0) || ((data & (1 << ep->epnum)) == 0))
		वापस;		/* Not Support DMA */

	num = ep->epnum - 1;

	_nbu2ss_ep_dma_पात(udc, ep);

	अगर (ep->direct == USB_सूची_OUT) अणु
		/*---------------------------------------------------------*/
		/* OUT */
		_nbu2ss_ग_लिखोl(&preg->EP_DCR[num].EP_DCR2, 0);
		_nbu2ss_bitclr(&preg->EP_DCR[num].EP_DCR1, DCR1_EPN_सूची0);
		_nbu2ss_ग_लिखोl(&preg->EP_REGS[num].EP_DMA_CTRL, 0);
	पूर्ण अन्यथा अणु
		/*---------------------------------------------------------*/
		/* IN */
		_nbu2ss_bitclr(&preg->EP_REGS[num].EP_CONTROL, EPN_AUTO);
		_nbu2ss_ग_लिखोl(&preg->EP_REGS[num].EP_DMA_CTRL, 0);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
/* Abort DMA */
अटल व्योम _nbu2ss_ep_dma_पात(काष्ठा nbu2ss_udc *udc, काष्ठा nbu2ss_ep *ep)
अणु
	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	_nbu2ss_bitclr(&preg->EP_DCR[ep->epnum - 1].EP_DCR1, DCR1_EPN_REQEN);
	mdelay(DMA_DISABLE_TIME);	/* DCR1_EPN_REQEN Clear */
	_nbu2ss_bitclr(&preg->EP_REGS[ep->epnum - 1].EP_DMA_CTRL, EPN_DMA_EN);
पूर्ण

/*-------------------------------------------------------------------------*/
/* Start IN Transfer */
अटल व्योम _nbu2ss_ep_in_end(काष्ठा nbu2ss_udc *udc,
			      u32 epnum, u32 data32, u32 length)
अणु
	u32		data;
	u32		num;
	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	अगर (length >= माप(u32))
		वापस;

	अगर (epnum == 0) अणु
		_nbu2ss_bitclr(&preg->EP0_CONTROL, EP0_AUTO);

		/* Writing of 1-4 bytes */
		अगर (length)
			_nbu2ss_ग_लिखोl(&preg->EP0_WRITE, data32);

		data = ((length << 5) & EP0_DW) | EP0_DEND;
		_nbu2ss_ग_लिखोl(&preg->EP0_CONTROL, data);

		_nbu2ss_bitset(&preg->EP0_CONTROL, EP0_AUTO);
	पूर्ण अन्यथा अणु
		num = epnum - 1;

		_nbu2ss_bitclr(&preg->EP_REGS[num].EP_CONTROL, EPN_AUTO);

		/* Writing of 1-4 bytes */
		अगर (length)
			_nbu2ss_ग_लिखोl(&preg->EP_REGS[num].EP_WRITE, data32);

		data = (((length) << 5) & EPN_DW) | EPN_DEND;
		_nbu2ss_bitset(&preg->EP_REGS[num].EP_CONTROL, data);

		_nbu2ss_bitset(&preg->EP_REGS[num].EP_CONTROL, EPN_AUTO);
	पूर्ण
पूर्ण

#अगर_घोषित USE_DMA
/*-------------------------------------------------------------------------*/
अटल व्योम _nbu2ss_dma_map_single(काष्ठा nbu2ss_udc *udc,
				   काष्ठा nbu2ss_ep *ep,
				   काष्ठा nbu2ss_req *req, u8 direct)
अणु
	अगर (req->req.dma == DMA_ADDR_INVALID) अणु
		अगर (req->unaligned) अणु
			req->req.dma = ep->phys_buf;
		पूर्ण अन्यथा अणु
			req->req.dma = dma_map_single(udc->gadget.dev.parent,
						      req->req.buf,
						      req->req.length,
						      (direct == USB_सूची_IN)
						      ? DMA_TO_DEVICE
						      : DMA_FROM_DEVICE);
		पूर्ण
		req->mapped = 1;
	पूर्ण अन्यथा अणु
		अगर (!req->unaligned)
			dma_sync_single_क्रम_device(udc->gadget.dev.parent,
						   req->req.dma,
						   req->req.length,
						   (direct == USB_सूची_IN)
						   ? DMA_TO_DEVICE
						   : DMA_FROM_DEVICE);

		req->mapped = 0;
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम _nbu2ss_dma_unmap_single(काष्ठा nbu2ss_udc *udc,
				     काष्ठा nbu2ss_ep *ep,
				     काष्ठा nbu2ss_req *req, u8 direct)
अणु
	u8		data[4];
	u8		*p;
	u32		count = 0;

	अगर (direct == USB_सूची_OUT) अणु
		count = req->req.actual % 4;
		अगर (count) अणु
			p = req->req.buf;
			p += (req->req.actual - count);
			स_नकल(data, p, count);
		पूर्ण
	पूर्ण

	अगर (req->mapped) अणु
		अगर (req->unaligned) अणु
			अगर (direct == USB_सूची_OUT)
				स_नकल(req->req.buf, ep->virt_buf,
				       req->req.actual & 0xfffffffc);
		पूर्ण अन्यथा अणु
			dma_unmap_single(udc->gadget.dev.parent,
					 req->req.dma, req->req.length,
				(direct == USB_सूची_IN)
				? DMA_TO_DEVICE
				: DMA_FROM_DEVICE);
		पूर्ण
		req->req.dma = DMA_ADDR_INVALID;
		req->mapped = 0;
	पूर्ण अन्यथा अणु
		अगर (!req->unaligned)
			dma_sync_single_क्रम_cpu(udc->gadget.dev.parent,
						req->req.dma, req->req.length,
				(direct == USB_सूची_IN)
				? DMA_TO_DEVICE
				: DMA_FROM_DEVICE);
	पूर्ण

	अगर (count) अणु
		p = req->req.buf;
		p += (req->req.actual - count);
		स_नकल(p, data, count);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/
/* Endpoपूर्णांक 0 OUT Transfer (PIO) */
अटल पूर्णांक ep0_out_pio(काष्ठा nbu2ss_udc *udc, u8 *buf, u32 length)
अणु
	u32		i;
	u32 numपढ़ोs = length / माप(u32);
	जोड़ usb_reg_access *buf32 = (जोड़ usb_reg_access *)buf;

	अगर (!numपढ़ोs)
		वापस 0;

	/* PIO Read */
	क्रम (i = 0; i < numपढ़ोs; i++) अणु
		buf32->dw = _nbu2ss_पढ़ोl(&udc->p_regs->EP0_READ);
		buf32++;
	पूर्ण

	वापस  numपढ़ोs * माप(u32);
पूर्ण

/*-------------------------------------------------------------------------*/
/* Endpoपूर्णांक 0 OUT Transfer (PIO, OverBytes) */
अटल पूर्णांक ep0_out_overbytes(काष्ठा nbu2ss_udc *udc, u8 *p_buf, u32 length)
अणु
	u32		i;
	u32		i_पढ़ो_size = 0;
	जोड़ usb_reg_access  temp_32;
	जोड़ usb_reg_access  *p_buf_32 = (जोड़ usb_reg_access *)p_buf;

	अगर ((length > 0) && (length < माप(u32))) अणु
		temp_32.dw = _nbu2ss_पढ़ोl(&udc->p_regs->EP0_READ);
		क्रम (i = 0 ; i < length ; i++)
			p_buf_32->byte.DATA[i] = temp_32.byte.DATA[i];
		i_पढ़ो_size += length;
	पूर्ण

	वापस i_पढ़ो_size;
पूर्ण

/*-------------------------------------------------------------------------*/
/* Endpoपूर्णांक 0 IN Transfer (PIO) */
अटल पूर्णांक EP0_in_PIO(काष्ठा nbu2ss_udc *udc, u8 *p_buf, u32 length)
अणु
	u32		i;
	u32		i_max_length   = EP0_PACKETSIZE;
	u32		i_word_length  = 0;
	u32		i_ग_लिखो_length = 0;
	जोड़ usb_reg_access  *p_buf_32 = (जोड़ usb_reg_access *)p_buf;

	/*------------------------------------------------------------*/
	/* Transfer Length */
	अगर (i_max_length < length)
		i_word_length = i_max_length / माप(u32);
	अन्यथा
		i_word_length = length / माप(u32);

	/*------------------------------------------------------------*/
	/* PIO */
	क्रम (i = 0; i < i_word_length; i++) अणु
		_nbu2ss_ग_लिखोl(&udc->p_regs->EP0_WRITE, p_buf_32->dw);
		p_buf_32++;
		i_ग_लिखो_length += माप(u32);
	पूर्ण

	वापस i_ग_लिखो_length;
पूर्ण

/*-------------------------------------------------------------------------*/
/* Endpoपूर्णांक 0 IN Transfer (PIO, OverBytes) */
अटल पूर्णांक ep0_in_overbytes(काष्ठा nbu2ss_udc *udc,
			    u8 *p_buf,
			    u32 i_reमुख्य_size)
अणु
	u32		i;
	जोड़ usb_reg_access  temp_32;
	जोड़ usb_reg_access  *p_buf_32 = (जोड़ usb_reg_access *)p_buf;

	अगर ((i_reमुख्य_size > 0) && (i_reमुख्य_size < माप(u32))) अणु
		क्रम (i = 0 ; i < i_reमुख्य_size ; i++)
			temp_32.byte.DATA[i] = p_buf_32->byte.DATA[i];
		_nbu2ss_ep_in_end(udc, 0, temp_32.dw, i_reमुख्य_size);

		वापस i_reमुख्य_size;
	पूर्ण

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
/* Transfer शून्य Packet (Epnकरोपूर्णांक 0) */
अटल पूर्णांक EP0_send_शून्य(काष्ठा nbu2ss_udc *udc, bool pid_flag)
अणु
	u32		data;

	data = _nbu2ss_पढ़ोl(&udc->p_regs->EP0_CONTROL);
	data &= ~(u32)EP0_INAK;

	अगर (pid_flag)
		data |= (EP0_INAK_EN | EP0_PIDCLR | EP0_DEND);
	अन्यथा
		data |= (EP0_INAK_EN | EP0_DEND);

	_nbu2ss_ग_लिखोl(&udc->p_regs->EP0_CONTROL, data);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
/* Receive शून्य Packet (Endpoपूर्णांक 0) */
अटल पूर्णांक EP0_receive_शून्य(काष्ठा nbu2ss_udc *udc, bool pid_flag)
अणु
	u32		data;

	data = _nbu2ss_पढ़ोl(&udc->p_regs->EP0_CONTROL);
	data &= ~(u32)EP0_ONAK;

	अगर (pid_flag)
		data |= EP0_PIDCLR;

	_nbu2ss_ग_लिखोl(&udc->p_regs->EP0_CONTROL, data);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_ep0_in_transfer(काष्ठा nbu2ss_udc *udc,
				   काष्ठा nbu2ss_req *req)
अणु
	u8		*p_buffer;			/* IN Data Buffer */
	u32		data;
	u32		i_reमुख्य_size = 0;
	पूर्णांक		result = 0;

	/*-------------------------------------------------------------*/
	/* End confirmation */
	अगर (req->req.actual == req->req.length) अणु
		अगर ((req->req.actual % EP0_PACKETSIZE) == 0) अणु
			अगर (req->zero) अणु
				req->zero = false;
				EP0_send_शून्य(udc, false);
				वापस 1;
			पूर्ण
		पूर्ण

		वापस 0;		/* Transfer End */
	पूर्ण

	/*-------------------------------------------------------------*/
	/* NAK release */
	data = _nbu2ss_पढ़ोl(&udc->p_regs->EP0_CONTROL);
	data |= EP0_INAK_EN;
	data &= ~(u32)EP0_INAK;
	_nbu2ss_ग_लिखोl(&udc->p_regs->EP0_CONTROL, data);

	i_reमुख्य_size = req->req.length - req->req.actual;
	p_buffer = (u8 *)req->req.buf;
	p_buffer += req->req.actual;

	/*-------------------------------------------------------------*/
	/* Data transfer */
	result = EP0_in_PIO(udc, p_buffer, i_reमुख्य_size);

	req->भाग_len = result;
	i_reमुख्य_size -= result;

	अगर (i_reमुख्य_size == 0) अणु
		EP0_send_शून्य(udc, false);
		वापस result;
	पूर्ण

	अगर ((i_reमुख्य_size < माप(u32)) && (result != EP0_PACKETSIZE)) अणु
		p_buffer += result;
		result += ep0_in_overbytes(udc, p_buffer, i_reमुख्य_size);
		req->भाग_len = result;
	पूर्ण

	वापस result;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_ep0_out_transfer(काष्ठा nbu2ss_udc *udc,
				    काष्ठा nbu2ss_req *req)
अणु
	u8		*p_buffer;
	u32		i_reमुख्य_size;
	u32		i_recv_length;
	पूर्णांक		result = 0;
	पूर्णांक		f_rcv_zero;

	/*-------------------------------------------------------------*/
	/* Receive data confirmation */
	i_recv_length = _nbu2ss_पढ़ोl(&udc->p_regs->EP0_LENGTH) & EP0_LDATA;
	अगर (i_recv_length != 0) अणु
		f_rcv_zero = 0;

		i_reमुख्य_size = req->req.length - req->req.actual;
		p_buffer = (u8 *)req->req.buf;
		p_buffer += req->req.actual;

		result = ep0_out_pio(udc, p_buffer
					, min(i_reमुख्य_size, i_recv_length));
		अगर (result < 0)
			वापस result;

		req->req.actual += result;
		i_recv_length -= result;

		अगर ((i_recv_length > 0) && (i_recv_length < माप(u32))) अणु
			p_buffer += result;
			i_reमुख्य_size -= result;

			result = ep0_out_overbytes(udc, p_buffer
					, min(i_reमुख्य_size, i_recv_length));
			req->req.actual += result;
		पूर्ण
	पूर्ण अन्यथा अणु
		f_rcv_zero = 1;
	पूर्ण

	/*-------------------------------------------------------------*/
	/* End confirmation */
	अगर (req->req.actual == req->req.length) अणु
		अगर ((req->req.actual % EP0_PACKETSIZE) == 0) अणु
			अगर (req->zero) अणु
				req->zero = false;
				EP0_receive_शून्य(udc, false);
				वापस 1;
			पूर्ण
		पूर्ण

		वापस 0;		/* Transfer End */
	पूर्ण

	अगर ((req->req.actual % EP0_PACKETSIZE) != 0)
		वापस 0;		/* Short Packet Transfer End */

	अगर (req->req.actual > req->req.length) अणु
		dev_err(udc->dev, " *** Overrun Error\n");
		वापस -EOVERFLOW;
	पूर्ण

	अगर (f_rcv_zero != 0) अणु
		i_reमुख्य_size = _nbu2ss_पढ़ोl(&udc->p_regs->EP0_CONTROL);
		अगर (i_reमुख्य_size & EP0_ONAK) अणु
			/*---------------------------------------------------*/
			/* NACK release */
			_nbu2ss_bitclr(&udc->p_regs->EP0_CONTROL, EP0_ONAK);
		पूर्ण
		result = 1;
	पूर्ण

	वापस result;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_out_dma(काष्ठा nbu2ss_udc *udc, काष्ठा nbu2ss_req *req,
			   u32 num, u32 length)
अणु
	dma_addr_t	p_buffer;
	u32		mpkt;
	u32		lmpkt;
	u32		dmacnt;
	u32		burst = 1;
	u32		data;
	पूर्णांक		result;
	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	अगर (req->dma_flag)
		वापस 1;		/* DMA is क्रमwarded */

	req->dma_flag = true;
	p_buffer = req->req.dma;
	p_buffer += req->req.actual;

	/* DMA Address */
	_nbu2ss_ग_लिखोl(&preg->EP_DCR[num].EP_TADR, (u32)p_buffer);

	/* Number of transfer packets */
	mpkt = _nbu2ss_पढ़ोl(&preg->EP_REGS[num].EP_PCKT_ADRS) & EPN_MPKT;
	dmacnt = length / mpkt;
	lmpkt = (length % mpkt) & ~(u32)0x03;

	अगर (dmacnt > DMA_MAX_COUNT) अणु
		dmacnt = DMA_MAX_COUNT;
		lmpkt = 0;
	पूर्ण अन्यथा अगर (lmpkt != 0) अणु
		अगर (dmacnt == 0)
			burst = 0;	/* Burst OFF */
		dmacnt++;
	पूर्ण

	data = mpkt | (lmpkt << 16);
	_nbu2ss_ग_लिखोl(&preg->EP_DCR[num].EP_DCR2, data);

	data = ((dmacnt & 0xff) << 16) | DCR1_EPN_सूची0 | DCR1_EPN_REQEN;
	_nbu2ss_ग_लिखोl(&preg->EP_DCR[num].EP_DCR1, data);

	अगर (burst == 0) अणु
		_nbu2ss_ग_लिखोl(&preg->EP_REGS[num].EP_LEN_DCNT, 0);
		_nbu2ss_bitclr(&preg->EP_REGS[num].EP_DMA_CTRL, EPN_BURST_SET);
	पूर्ण अन्यथा अणु
		_nbu2ss_ग_लिखोl(&preg->EP_REGS[num].EP_LEN_DCNT
				, (dmacnt << 16));
		_nbu2ss_bitset(&preg->EP_REGS[num].EP_DMA_CTRL, EPN_BURST_SET);
	पूर्ण
	_nbu2ss_bitset(&preg->EP_REGS[num].EP_DMA_CTRL, EPN_DMA_EN);

	result = length & ~(u32)0x03;
	req->भाग_len = result;

	वापस result;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_epn_out_pio(काष्ठा nbu2ss_udc *udc, काष्ठा nbu2ss_ep *ep,
			       काष्ठा nbu2ss_req *req, u32 length)
अणु
	u8		*p_buffer;
	u32		i;
	u32		data;
	u32		i_word_length;
	जोड़ usb_reg_access	temp_32;
	जोड़ usb_reg_access	*p_buf_32;
	पूर्णांक		result = 0;
	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	अगर (req->dma_flag)
		वापस 1;		/* DMA is क्रमwarded */

	अगर (length == 0)
		वापस 0;

	p_buffer = (u8 *)req->req.buf;
	p_buf_32 = (जोड़ usb_reg_access *)(p_buffer + req->req.actual);

	i_word_length = length / माप(u32);
	अगर (i_word_length > 0) अणु
		/*---------------------------------------------------------*/
		/* Copy of every four bytes */
		क्रम (i = 0; i < i_word_length; i++) अणु
			p_buf_32->dw =
			_nbu2ss_पढ़ोl(&preg->EP_REGS[ep->epnum - 1].EP_READ);
			p_buf_32++;
		पूर्ण
		result = i_word_length * माप(u32);
	पूर्ण

	data = length - result;
	अगर (data > 0) अणु
		/*---------------------------------------------------------*/
		/* Copy of fraction byte */
		temp_32.dw =
			_nbu2ss_पढ़ोl(&preg->EP_REGS[ep->epnum - 1].EP_READ);
		क्रम (i = 0 ; i < data ; i++)
			p_buf_32->byte.DATA[i] = temp_32.byte.DATA[i];
		result += data;
	पूर्ण

	req->req.actual += result;

	अगर ((req->req.actual == req->req.length) ||
	    ((req->req.actual % ep->ep.maxpacket) != 0)) अणु
		result = 0;
	पूर्ण

	वापस result;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_epn_out_data(काष्ठा nbu2ss_udc *udc, काष्ठा nbu2ss_ep *ep,
				काष्ठा nbu2ss_req *req, u32 data_size)
अणु
	u32		num;
	u32		i_buf_size;
	पूर्णांक		nret = 1;

	अगर (ep->epnum == 0)
		वापस -EINVAL;

	num = ep->epnum - 1;

	i_buf_size = min((req->req.length - req->req.actual), data_size);

	अगर ((ep->ep_type != USB_ENDPOINT_XFER_INT) && (req->req.dma != 0) &&
	    (i_buf_size  >= माप(u32))) अणु
		nret = _nbu2ss_out_dma(udc, req, num, i_buf_size);
	पूर्ण अन्यथा अणु
		i_buf_size = min_t(u32, i_buf_size, ep->ep.maxpacket);
		nret = _nbu2ss_epn_out_pio(udc, ep, req, i_buf_size);
	पूर्ण

	वापस nret;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_epn_out_transfer(काष्ठा nbu2ss_udc *udc,
				    काष्ठा nbu2ss_ep *ep,
				    काष्ठा nbu2ss_req *req)
अणु
	u32		num;
	u32		i_recv_length;
	पूर्णांक		result = 1;
	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	अगर (ep->epnum == 0)
		वापस -EINVAL;

	num = ep->epnum - 1;

	/*-------------------------------------------------------------*/
	/* Receive Length */
	i_recv_length =
		_nbu2ss_पढ़ोl(&preg->EP_REGS[num].EP_LEN_DCNT) & EPN_LDATA;

	अगर (i_recv_length != 0) अणु
		result = _nbu2ss_epn_out_data(udc, ep, req, i_recv_length);
		अगर (i_recv_length < ep->ep.maxpacket) अणु
			अगर (i_recv_length == result) अणु
				req->req.actual += result;
				result = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((req->req.actual == req->req.length) ||
		    ((req->req.actual % ep->ep.maxpacket) != 0)) अणु
			result = 0;
		पूर्ण
	पूर्ण

	अगर (result == 0) अणु
		अगर ((req->req.actual % ep->ep.maxpacket) == 0) अणु
			अगर (req->zero) अणु
				req->zero = false;
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (req->req.actual > req->req.length) अणु
		dev_err(udc->dev, " Overrun Error\n");
		dev_err(udc->dev, " actual = %d, length = %d\n",
			req->req.actual, req->req.length);
		result = -EOVERFLOW;
	पूर्ण

	वापस result;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_in_dma(काष्ठा nbu2ss_udc *udc, काष्ठा nbu2ss_ep *ep,
			  काष्ठा nbu2ss_req *req, u32 num, u32 length)
अणु
	dma_addr_t	p_buffer;
	u32		mpkt;		/* MaxPacketSize */
	u32		lmpkt;		/* Last Packet Data Size */
	u32		dmacnt;		/* IN Data Size */
	u32		i_ग_लिखो_length;
	u32		data;
	पूर्णांक		result = -EINVAL;
	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	अगर (req->dma_flag)
		वापस 1;		/* DMA is क्रमwarded */

#अगर_घोषित USE_DMA
	अगर (req->req.actual == 0)
		_nbu2ss_dma_map_single(udc, ep, req, USB_सूची_IN);
#पूर्ण_अगर
	req->dma_flag = true;

	/* MAX Packet Size */
	mpkt = _nbu2ss_पढ़ोl(&preg->EP_REGS[num].EP_PCKT_ADRS) & EPN_MPKT;

	अगर ((DMA_MAX_COUNT * mpkt) < length)
		i_ग_लिखो_length = DMA_MAX_COUNT * mpkt;
	अन्यथा
		i_ग_लिखो_length = length;

	/*------------------------------------------------------------*/
	/* Number of transmission packets */
	अगर (mpkt < i_ग_लिखो_length) अणु
		dmacnt = i_ग_लिखो_length / mpkt;
		lmpkt  = (i_ग_लिखो_length % mpkt) & ~(u32)0x3;
		अगर (lmpkt != 0)
			dmacnt++;
		अन्यथा
			lmpkt = mpkt & ~(u32)0x3;

	पूर्ण अन्यथा अणु
		dmacnt = 1;
		lmpkt  = i_ग_लिखो_length & ~(u32)0x3;
	पूर्ण

	/* Packet setting */
	data = mpkt | (lmpkt << 16);
	_nbu2ss_ग_लिखोl(&preg->EP_DCR[num].EP_DCR2, data);

	/* Address setting */
	p_buffer = req->req.dma;
	p_buffer += req->req.actual;
	_nbu2ss_ग_लिखोl(&preg->EP_DCR[num].EP_TADR, (u32)p_buffer);

	/* Packet and DMA setting */
	data = ((dmacnt & 0xff) << 16) | DCR1_EPN_REQEN;
	_nbu2ss_ग_लिखोl(&preg->EP_DCR[num].EP_DCR1, data);

	/* Packet setting of EPC */
	data = dmacnt << 16;
	_nbu2ss_ग_लिखोl(&preg->EP_REGS[num].EP_LEN_DCNT, data);

	/*DMA setting of EPC */
	_nbu2ss_bitset(&preg->EP_REGS[num].EP_DMA_CTRL, EPN_DMA_EN);

	result = i_ग_लिखो_length & ~(u32)0x3;
	req->भाग_len = result;

	वापस result;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_epn_in_pio(काष्ठा nbu2ss_udc *udc, काष्ठा nbu2ss_ep *ep,
			      काष्ठा nbu2ss_req *req, u32 length)
अणु
	u8		*p_buffer;
	u32		i;
	u32		data;
	u32		i_word_length;
	जोड़ usb_reg_access	temp_32;
	जोड़ usb_reg_access	*p_buf_32 = शून्य;
	पूर्णांक		result = 0;
	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	अगर (req->dma_flag)
		वापस 1;		/* DMA is क्रमwarded */

	अगर (length > 0) अणु
		p_buffer = (u8 *)req->req.buf;
		p_buf_32 = (जोड़ usb_reg_access *)(p_buffer + req->req.actual);

		i_word_length = length / माप(u32);
		अगर (i_word_length > 0) अणु
			क्रम (i = 0; i < i_word_length; i++) अणु
				_nbu2ss_ग_लिखोl(
					&preg->EP_REGS[ep->epnum - 1].EP_WRITE,
					p_buf_32->dw);

				p_buf_32++;
			पूर्ण
			result = i_word_length * माप(u32);
		पूर्ण
	पूर्ण

	अगर (result != ep->ep.maxpacket) अणु
		data = length - result;
		temp_32.dw = 0;
		क्रम (i = 0 ; i < data ; i++)
			temp_32.byte.DATA[i] = p_buf_32->byte.DATA[i];

		_nbu2ss_ep_in_end(udc, ep->epnum, temp_32.dw, data);
		result += data;
	पूर्ण

	req->भाग_len = result;

	वापस result;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_epn_in_data(काष्ठा nbu2ss_udc *udc, काष्ठा nbu2ss_ep *ep,
			       काष्ठा nbu2ss_req *req, u32 data_size)
अणु
	u32		num;
	पूर्णांक		nret = 1;

	अगर (ep->epnum == 0)
		वापस -EINVAL;

	num = ep->epnum - 1;

	अगर ((ep->ep_type != USB_ENDPOINT_XFER_INT) && (req->req.dma != 0) &&
	    (data_size >= माप(u32))) अणु
		nret = _nbu2ss_in_dma(udc, ep, req, num, data_size);
	पूर्ण अन्यथा अणु
		data_size = min_t(u32, data_size, ep->ep.maxpacket);
		nret = _nbu2ss_epn_in_pio(udc, ep, req, data_size);
	पूर्ण

	वापस nret;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_epn_in_transfer(काष्ठा nbu2ss_udc *udc,
				   काष्ठा nbu2ss_ep *ep, काष्ठा nbu2ss_req *req)
अणु
	u32		num;
	u32		i_buf_size;
	पूर्णांक		result = 0;
	u32		status;

	अगर (ep->epnum == 0)
		वापस -EINVAL;

	num = ep->epnum - 1;

	status = _nbu2ss_पढ़ोl(&udc->p_regs->EP_REGS[num].EP_STATUS);

	/*-------------------------------------------------------------*/
	/* State confirmation of FIFO */
	अगर (req->req.actual == 0) अणु
		अगर ((status & EPN_IN_EMPTY) == 0)
			वापस 1;	/* Not Empty */

	पूर्ण अन्यथा अणु
		अगर ((status & EPN_IN_FULL) != 0)
			वापस 1;	/* Not Empty */
	पूर्ण

	/*-------------------------------------------------------------*/
	/* Start transfer */
	i_buf_size = req->req.length - req->req.actual;
	अगर (i_buf_size > 0)
		result = _nbu2ss_epn_in_data(udc, ep, req, i_buf_size);
	अन्यथा अगर (req->req.length == 0)
		_nbu2ss_zero_len_pkt(udc, ep->epnum);

	वापस result;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_start_transfer(काष्ठा nbu2ss_udc *udc,
				  काष्ठा nbu2ss_ep *ep,
				  काष्ठा nbu2ss_req *req,
				  bool	bflag)
अणु
	पूर्णांक		nret = -EINVAL;

	req->dma_flag = false;
	req->भाग_len = 0;

	अगर (req->req.length == 0) अणु
		req->zero = false;
	पूर्ण अन्यथा अणु
		अगर ((req->req.length % ep->ep.maxpacket) == 0)
			req->zero = req->req.zero;
		अन्यथा
			req->zero = false;
	पूर्ण

	अगर (ep->epnum == 0) अणु
		/* EP0 */
		चयन (udc->ep0state) अणु
		हाल EP0_IN_DATA_PHASE:
			nret = _nbu2ss_ep0_in_transfer(udc, req);
			अवरोध;

		हाल EP0_OUT_DATA_PHASE:
			nret = _nbu2ss_ep0_out_transfer(udc, req);
			अवरोध;

		हाल EP0_IN_STATUS_PHASE:
			nret = EP0_send_शून्य(udc, true);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* EPN */
		अगर (ep->direct == USB_सूची_OUT) अणु
			/* OUT */
			अगर (!bflag)
				nret = _nbu2ss_epn_out_transfer(udc, ep, req);
		पूर्ण अन्यथा अणु
			/* IN */
			nret = _nbu2ss_epn_in_transfer(udc, ep, req);
		पूर्ण
	पूर्ण

	वापस nret;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम _nbu2ss_restert_transfer(काष्ठा nbu2ss_ep *ep)
अणु
	u32		length;
	bool	bflag = false;
	काष्ठा nbu2ss_req *req;

	req = list_first_entry_or_null(&ep->queue, काष्ठा nbu2ss_req, queue);
	अगर (!req)
		वापस;

	अगर (ep->epnum > 0) अणु
		length = _nbu2ss_पढ़ोl(
			&ep->udc->p_regs->EP_REGS[ep->epnum - 1].EP_LEN_DCNT);

		length &= EPN_LDATA;
		अगर (length < ep->ep.maxpacket)
			bflag = true;
	पूर्ण

	_nbu2ss_start_transfer(ep->udc, ep, req, bflag);
पूर्ण

/*-------------------------------------------------------------------------*/
/*	Endpoपूर्णांक Toggle Reset */
अटल व्योम _nbu2ss_endpoपूर्णांक_toggle_reset(काष्ठा nbu2ss_udc *udc, u8 ep_adrs)
अणु
	u8		num;
	u32		data;

	अगर ((ep_adrs == 0) || (ep_adrs == 0x80))
		वापस;

	num = (ep_adrs & 0x7F) - 1;

	अगर (ep_adrs & USB_सूची_IN)
		data = EPN_IPIDCLR;
	अन्यथा
		data = EPN_BCLR | EPN_OPIDCLR;

	_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_CONTROL, data);
पूर्ण

/*-------------------------------------------------------------------------*/
/*	Endpoपूर्णांक STALL set */
अटल व्योम _nbu2ss_set_endpoपूर्णांक_stall(काष्ठा nbu2ss_udc *udc,
				       u8 ep_adrs, bool bstall)
अणु
	u8		num, epnum;
	u32		data;
	काष्ठा nbu2ss_ep *ep;
	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	अगर ((ep_adrs == 0) || (ep_adrs == 0x80)) अणु
		अगर (bstall) अणु
			/* Set STALL */
			_nbu2ss_bitset(&preg->EP0_CONTROL, EP0_STL);
		पूर्ण अन्यथा अणु
			/* Clear STALL */
			_nbu2ss_bitclr(&preg->EP0_CONTROL, EP0_STL);
		पूर्ण
	पूर्ण अन्यथा अणु
		epnum = ep_adrs & USB_ENDPOINT_NUMBER_MASK;
		num = epnum - 1;
		ep = &udc->ep[epnum];

		अगर (bstall) अणु
			/* Set STALL */
			ep->halted = true;

			अगर (ep_adrs & USB_सूची_IN)
				data = EPN_BCLR | EPN_ISTL;
			अन्यथा
				data = EPN_OSTL_EN | EPN_OSTL;

			_nbu2ss_bitset(&preg->EP_REGS[num].EP_CONTROL, data);
		पूर्ण अन्यथा अणु
			अगर (ep_adrs & USB_सूची_IN) अणु
				_nbu2ss_bitclr(&preg->EP_REGS[num].EP_CONTROL
						, EPN_ISTL);
			पूर्ण अन्यथा अणु
				data =
				_nbu2ss_पढ़ोl(&preg->EP_REGS[num].EP_CONTROL);

				data &= ~EPN_OSTL;
				data |= EPN_OSTL_EN;

				_nbu2ss_ग_लिखोl(&preg->EP_REGS[num].EP_CONTROL
						, data);
			पूर्ण

			/* Clear STALL */
			ep->stalled = false;
			अगर (ep->halted) अणु
				ep->halted = false;
				_nbu2ss_restert_transfer(ep);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम _nbu2ss_set_test_mode(काष्ठा nbu2ss_udc *udc, u32 mode)
अणु
	u32		data;

	अगर (mode > MAX_TEST_MODE_NUM)
		वापस;

	dev_info(udc->dev, "SET FEATURE : test mode = %d\n", mode);

	data = _nbu2ss_पढ़ोl(&udc->p_regs->USB_CONTROL);
	data &= ~TEST_FORCE_ENABLE;
	data |= mode << TEST_MODE_SHIFT;

	_nbu2ss_ग_लिखोl(&udc->p_regs->USB_CONTROL, data);
	_nbu2ss_bitset(&udc->p_regs->TEST_CONTROL, CS_TESTMODEEN);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_set_feature_device(काष्ठा nbu2ss_udc *udc,
				      u16 selector, u16 wIndex)
अणु
	पूर्णांक	result = -EOPNOTSUPP;

	चयन (selector) अणु
	हाल USB_DEVICE_REMOTE_WAKEUP:
		अगर (wIndex == 0x0000) अणु
			udc->remote_wakeup = U2F_ENABLE;
			result = 0;
		पूर्ण
		अवरोध;

	हाल USB_DEVICE_TEST_MODE:
		wIndex >>= 8;
		अगर (wIndex <= MAX_TEST_MODE_NUM)
			result = 0;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_get_ep_stall(काष्ठा nbu2ss_udc *udc, u8 ep_adrs)
अणु
	u8		epnum;
	u32		data = 0, bit_data;
	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	epnum = ep_adrs & ~USB_ENDPOINT_सूची_MASK;
	अगर (epnum == 0) अणु
		data = _nbu2ss_पढ़ोl(&preg->EP0_CONTROL);
		bit_data = EP0_STL;

	पूर्ण अन्यथा अणु
		data = _nbu2ss_पढ़ोl(&preg->EP_REGS[epnum - 1].EP_CONTROL);
		अगर ((data & EPN_EN) == 0)
			वापस -1;

		अगर (ep_adrs & USB_ENDPOINT_सूची_MASK)
			bit_data = EPN_ISTL;
		अन्यथा
			bit_data = EPN_OSTL;
	पूर्ण

	अगर ((data & bit_data) == 0)
		वापस 0;
	वापस 1;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत पूर्णांक _nbu2ss_req_feature(काष्ठा nbu2ss_udc *udc, bool bset)
अणु
	u8	recipient = (u8)(udc->ctrl.bRequestType & USB_RECIP_MASK);
	u8	direction = (u8)(udc->ctrl.bRequestType & USB_सूची_IN);
	u16	selector  = le16_to_cpu(udc->ctrl.wValue);
	u16	wIndex    = le16_to_cpu(udc->ctrl.wIndex);
	u8	ep_adrs;
	पूर्णांक	result = -EOPNOTSUPP;

	अगर ((udc->ctrl.wLength != 0x0000) ||
	    (direction != USB_सूची_OUT)) अणु
		वापस -EINVAL;
	पूर्ण

	चयन (recipient) अणु
	हाल USB_RECIP_DEVICE:
		अगर (bset)
			result =
			_nbu2ss_set_feature_device(udc, selector, wIndex);
		अवरोध;

	हाल USB_RECIP_ENDPOINT:
		अगर (0x0000 == (wIndex & 0xFF70)) अणु
			अगर (selector == USB_ENDPOINT_HALT) अणु
				ep_adrs = wIndex & 0xFF;
				अगर (!bset) अणु
					_nbu2ss_endpoपूर्णांक_toggle_reset(udc,
								      ep_adrs);
				पूर्ण

				_nbu2ss_set_endpoपूर्णांक_stall(udc, ep_adrs, bset);

				result = 0;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (result >= 0)
		_nbu2ss_create_ep0_packet(udc, udc->ep0_buf, 0);

	वापस result;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत क्रमागत usb_device_speed _nbu2ss_get_speed(काष्ठा nbu2ss_udc *udc)
अणु
	u32		data;
	क्रमागत usb_device_speed speed = USB_SPEED_FULL;

	data = _nbu2ss_पढ़ोl(&udc->p_regs->USB_STATUS);
	अगर (data & HIGH_SPEED)
		speed = USB_SPEED_HIGH;

	वापस speed;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम _nbu2ss_epn_set_stall(काष्ठा nbu2ss_udc *udc,
				  काष्ठा nbu2ss_ep *ep)
अणु
	u8	ep_adrs;
	u32	regdata;
	पूर्णांक	limit_cnt = 0;

	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	अगर (ep->direct == USB_सूची_IN) अणु
		क्रम (limit_cnt = 0
			; limit_cnt < IN_DATA_EMPTY_COUNT
			; limit_cnt++) अणु
			regdata = _nbu2ss_पढ़ोl(
				&preg->EP_REGS[ep->epnum - 1].EP_STATUS);

			अगर ((regdata & EPN_IN_DATA) == 0)
				अवरोध;

			mdelay(1);
		पूर्ण
	पूर्ण

	ep_adrs = ep->epnum | ep->direct;
	_nbu2ss_set_endpoपूर्णांक_stall(udc, ep_adrs, 1);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक std_req_get_status(काष्ठा nbu2ss_udc *udc)
अणु
	u32	length;
	u16	status_data = 0;
	u8	recipient = (u8)(udc->ctrl.bRequestType & USB_RECIP_MASK);
	u8	direction = (u8)(udc->ctrl.bRequestType & USB_सूची_IN);
	u8	ep_adrs;
	पूर्णांक	result = -EINVAL;

	अगर ((udc->ctrl.wValue != 0x0000) || (direction != USB_सूची_IN))
		वापस result;

	length =
		min_t(u16, le16_to_cpu(udc->ctrl.wLength), माप(status_data));
	चयन (recipient) अणु
	हाल USB_RECIP_DEVICE:
		अगर (udc->ctrl.wIndex == 0x0000) अणु
			अगर (udc->gadget.is_selfघातered)
				status_data |= BIT(USB_DEVICE_SELF_POWERED);

			अगर (udc->remote_wakeup)
				status_data |= BIT(USB_DEVICE_REMOTE_WAKEUP);

			result = 0;
		पूर्ण
		अवरोध;

	हाल USB_RECIP_ENDPOINT:
		अगर (0x0000 == (le16_to_cpu(udc->ctrl.wIndex) & 0xFF70)) अणु
			ep_adrs = (u8)(le16_to_cpu(udc->ctrl.wIndex) & 0xFF);
			result = _nbu2ss_get_ep_stall(udc, ep_adrs);

			अगर (result > 0)
				status_data |= BIT(USB_ENDPOINT_HALT);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (result >= 0) अणु
		स_नकल(udc->ep0_buf, &status_data, length);
		_nbu2ss_create_ep0_packet(udc, udc->ep0_buf, length);
		_nbu2ss_ep0_in_transfer(udc, &udc->ep0_req);

	पूर्ण अन्यथा अणु
		dev_err(udc->dev, " Error GET_STATUS\n");
	पूर्ण

	वापस result;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक std_req_clear_feature(काष्ठा nbu2ss_udc *udc)
अणु
	वापस _nbu2ss_req_feature(udc, false);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक std_req_set_feature(काष्ठा nbu2ss_udc *udc)
अणु
	वापस _nbu2ss_req_feature(udc, true);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक std_req_set_address(काष्ठा nbu2ss_udc *udc)
अणु
	पूर्णांक		result = 0;
	u32		wValue = le16_to_cpu(udc->ctrl.wValue);

	अगर ((udc->ctrl.bRequestType != 0x00)	||
	    (udc->ctrl.wIndex != 0x0000)	||
		(udc->ctrl.wLength != 0x0000)) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (wValue != (wValue & 0x007F))
		वापस -EINVAL;

	wValue <<= USB_ADRS_SHIFT;

	_nbu2ss_ग_लिखोl(&udc->p_regs->USB_ADDRESS, wValue);
	_nbu2ss_create_ep0_packet(udc, udc->ep0_buf, 0);

	वापस result;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक std_req_set_configuration(काष्ठा nbu2ss_udc *udc)
अणु
	u32 config_value = (u32)(le16_to_cpu(udc->ctrl.wValue) & 0x00ff);

	अगर ((udc->ctrl.wIndex != 0x0000)	||
	    (udc->ctrl.wLength != 0x0000)	||
		(udc->ctrl.bRequestType != 0x00)) अणु
		वापस -EINVAL;
	पूर्ण

	udc->curr_config = config_value;

	अगर (config_value > 0) अणु
		_nbu2ss_bitset(&udc->p_regs->USB_CONTROL, CONF);
		udc->devstate = USB_STATE_CONFIGURED;

	पूर्ण अन्यथा अणु
		_nbu2ss_bitclr(&udc->p_regs->USB_CONTROL, CONF);
		udc->devstate = USB_STATE_ADDRESS;
	पूर्ण

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत व्योम _nbu2ss_पढ़ो_request_data(काष्ठा nbu2ss_udc *udc, u32 *pdata)
अणु
	*pdata = _nbu2ss_पढ़ोl(&udc->p_regs->SETUP_DATA0);
	pdata++;
	*pdata = _nbu2ss_पढ़ोl(&udc->p_regs->SETUP_DATA1);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत पूर्णांक _nbu2ss_decode_request(काष्ठा nbu2ss_udc *udc)
अणु
	bool			bcall_back = true;
	पूर्णांक			nret = -EINVAL;
	काष्ठा usb_ctrlrequest	*p_ctrl;

	p_ctrl = &udc->ctrl;
	_nbu2ss_पढ़ो_request_data(udc, (u32 *)p_ctrl);

	/* ep0 state control */
	अगर (p_ctrl->wLength == 0) अणु
		udc->ep0state = EP0_IN_STATUS_PHASE;

	पूर्ण अन्यथा अणु
		अगर (p_ctrl->bRequestType & USB_सूची_IN)
			udc->ep0state = EP0_IN_DATA_PHASE;
		अन्यथा
			udc->ep0state = EP0_OUT_DATA_PHASE;
	पूर्ण

	अगर ((p_ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) अणु
		चयन (p_ctrl->bRequest) अणु
		हाल USB_REQ_GET_STATUS:
			nret = std_req_get_status(udc);
			bcall_back = false;
			अवरोध;

		हाल USB_REQ_CLEAR_FEATURE:
			nret = std_req_clear_feature(udc);
			bcall_back = false;
			अवरोध;

		हाल USB_REQ_SET_FEATURE:
			nret = std_req_set_feature(udc);
			bcall_back = false;
			अवरोध;

		हाल USB_REQ_SET_ADDRESS:
			nret = std_req_set_address(udc);
			bcall_back = false;
			अवरोध;

		हाल USB_REQ_SET_CONFIGURATION:
			nret = std_req_set_configuration(udc);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!bcall_back) अणु
		अगर (udc->ep0state == EP0_IN_STATUS_PHASE) अणु
			अगर (nret >= 0) अणु
				/*--------------------------------------*/
				/* Status Stage */
				nret = EP0_send_शून्य(udc, true);
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		spin_unlock(&udc->lock);
		nret = udc->driver->setup(&udc->gadget, &udc->ctrl);
		spin_lock(&udc->lock);
	पूर्ण

	अगर (nret < 0)
		udc->ep0state = EP0_IDLE;

	वापस nret;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत पूर्णांक _nbu2ss_ep0_in_data_stage(काष्ठा nbu2ss_udc *udc)
अणु
	पूर्णांक			nret;
	काष्ठा nbu2ss_req	*req;
	काष्ठा nbu2ss_ep	*ep = &udc->ep[0];

	req = list_first_entry_or_null(&ep->queue, काष्ठा nbu2ss_req, queue);
	अगर (!req)
		req = &udc->ep0_req;

	req->req.actual += req->भाग_len;
	req->भाग_len = 0;

	nret = _nbu2ss_ep0_in_transfer(udc, req);
	अगर (nret == 0) अणु
		udc->ep0state = EP0_OUT_STATUS_PAHSE;
		EP0_receive_शून्य(udc, true);
	पूर्ण

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत पूर्णांक _nbu2ss_ep0_out_data_stage(काष्ठा nbu2ss_udc *udc)
अणु
	पूर्णांक			nret;
	काष्ठा nbu2ss_req	*req;
	काष्ठा nbu2ss_ep	*ep = &udc->ep[0];

	req = list_first_entry_or_null(&ep->queue, काष्ठा nbu2ss_req, queue);
	अगर (!req)
		req = &udc->ep0_req;

	nret = _nbu2ss_ep0_out_transfer(udc, req);
	अगर (nret == 0) अणु
		udc->ep0state = EP0_IN_STATUS_PHASE;
		EP0_send_शून्य(udc, true);

	पूर्ण अन्यथा अगर (nret < 0) अणु
		_nbu2ss_bitset(&udc->p_regs->EP0_CONTROL, EP0_BCLR);
		req->req.status = nret;
	पूर्ण

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत पूर्णांक _nbu2ss_ep0_status_stage(काष्ठा nbu2ss_udc *udc)
अणु
	काष्ठा nbu2ss_req	*req;
	काष्ठा nbu2ss_ep	*ep = &udc->ep[0];

	req = list_first_entry_or_null(&ep->queue, काष्ठा nbu2ss_req, queue);
	अगर (!req) अणु
		req = &udc->ep0_req;
		अगर (req->req.complete)
			req->req.complete(&ep->ep, &req->req);

	पूर्ण अन्यथा अणु
		अगर (req->req.complete)
			_nbu2ss_ep_करोne(ep, req, 0);
	पूर्ण

	udc->ep0state = EP0_IDLE;

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत व्योम _nbu2ss_ep0_पूर्णांक(काष्ठा nbu2ss_udc *udc)
अणु
	पूर्णांक		i;
	u32		status;
	u32		पूर्णांकr;
	पूर्णांक		nret = -1;

	status = _nbu2ss_पढ़ोl(&udc->p_regs->EP0_STATUS);
	पूर्णांकr = status & EP0_STATUS_RW_BIT;
	_nbu2ss_ग_लिखोl(&udc->p_regs->EP0_STATUS, ~पूर्णांकr);

	status &= (SETUP_INT | EP0_IN_INT | EP0_OUT_INT
			| STG_END_INT | EP0_OUT_शून्य_INT);

	अगर (status == 0) अणु
		dev_info(udc->dev, "%s Not Decode Interrupt\n", __func__);
		dev_info(udc->dev, "EP0_STATUS = 0x%08x\n", पूर्णांकr);
		वापस;
	पूर्ण

	अगर (udc->gadget.speed == USB_SPEED_UNKNOWN)
		udc->gadget.speed = _nbu2ss_get_speed(udc);

	क्रम (i = 0; i < EP0_END_XFER; i++) अणु
		चयन (udc->ep0state) अणु
		हाल EP0_IDLE:
			अगर (status & SETUP_INT) अणु
				status = 0;
				nret = _nbu2ss_decode_request(udc);
			पूर्ण
			अवरोध;

		हाल EP0_IN_DATA_PHASE:
			अगर (status & EP0_IN_INT) अणु
				status &= ~EP0_IN_INT;
				nret = _nbu2ss_ep0_in_data_stage(udc);
			पूर्ण
			अवरोध;

		हाल EP0_OUT_DATA_PHASE:
			अगर (status & EP0_OUT_INT) अणु
				status &= ~EP0_OUT_INT;
				nret = _nbu2ss_ep0_out_data_stage(udc);
			पूर्ण
			अवरोध;

		हाल EP0_IN_STATUS_PHASE:
			अगर ((status & STG_END_INT) || (status & SETUP_INT)) अणु
				status &= ~(STG_END_INT | EP0_IN_INT);
				nret = _nbu2ss_ep0_status_stage(udc);
			पूर्ण
			अवरोध;

		हाल EP0_OUT_STATUS_PAHSE:
			अगर ((status & STG_END_INT) || (status & SETUP_INT) ||
			    (status & EP0_OUT_शून्य_INT)) अणु
				status &= ~(STG_END_INT
						| EP0_OUT_INT
						| EP0_OUT_शून्य_INT);

				nret = _nbu2ss_ep0_status_stage(udc);
			पूर्ण

			अवरोध;

		शेष:
			status = 0;
			अवरोध;
		पूर्ण

		अगर (status == 0)
			अवरोध;
	पूर्ण

	अगर (nret < 0) अणु
		/* Send Stall */
		_nbu2ss_set_endpoपूर्णांक_stall(udc, 0, true);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम _nbu2ss_ep_करोne(काष्ठा nbu2ss_ep *ep,
			    काष्ठा nbu2ss_req *req,
			    पूर्णांक status)
अणु
	काष्ठा nbu2ss_udc *udc = ep->udc;

	list_del_init(&req->queue);

	अगर (status == -ECONNRESET)
		_nbu2ss_fअगरo_flush(udc, ep);

	अगर (likely(req->req.status == -EINPROGRESS))
		req->req.status = status;

	अगर (ep->stalled) अणु
		_nbu2ss_epn_set_stall(udc, ep);
	पूर्ण अन्यथा अणु
		अगर (!list_empty(&ep->queue))
			_nbu2ss_restert_transfer(ep);
	पूर्ण

#अगर_घोषित USE_DMA
	अगर ((ep->direct == USB_सूची_OUT) && (ep->epnum > 0) &&
	    (req->req.dma != 0))
		_nbu2ss_dma_unmap_single(udc, ep, req, USB_सूची_OUT);
#पूर्ण_अगर

	spin_unlock(&udc->lock);
	req->req.complete(&ep->ep, &req->req);
	spin_lock(&udc->lock);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत व्योम _nbu2ss_epn_in_पूर्णांक(काष्ठा nbu2ss_udc *udc,
				      काष्ठा nbu2ss_ep *ep,
				      काष्ठा nbu2ss_req *req)
अणु
	पूर्णांक	result = 0;
	u32	status;

	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	अगर (req->dma_flag)
		वापस;		/* DMA is क्रमwarded */

	req->req.actual += req->भाग_len;
	req->भाग_len = 0;

	अगर (req->req.actual != req->req.length) अणु
		/*---------------------------------------------------------*/
		/* reमुख्यder of data */
		result = _nbu2ss_epn_in_transfer(udc, ep, req);

	पूर्ण अन्यथा अणु
		अगर (req->zero && ((req->req.actual % ep->ep.maxpacket) == 0)) अणु
			status =
			_nbu2ss_पढ़ोl(&preg->EP_REGS[ep->epnum - 1].EP_STATUS);

			अगर ((status & EPN_IN_FULL) == 0) अणु
				/*-----------------------------------------*/
				/* 0 Length Packet */
				req->zero = false;
				_nbu2ss_zero_len_pkt(udc, ep->epnum);
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण

	अगर (result <= 0) अणु
		/*---------------------------------------------------------*/
		/* Complete */
		_nbu2ss_ep_करोne(ep, req, result);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत व्योम _nbu2ss_epn_out_पूर्णांक(काष्ठा nbu2ss_udc *udc,
				       काष्ठा nbu2ss_ep *ep,
				       काष्ठा nbu2ss_req *req)
अणु
	पूर्णांक	result;

	result = _nbu2ss_epn_out_transfer(udc, ep, req);
	अगर (result <= 0)
		_nbu2ss_ep_करोne(ep, req, result);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत व्योम _nbu2ss_epn_in_dma_पूर्णांक(काष्ठा nbu2ss_udc *udc,
					  काष्ठा nbu2ss_ep *ep,
					  काष्ठा nbu2ss_req *req)
अणु
	u32		mpkt;
	u32		size;
	काष्ठा usb_request *preq;

	preq = &req->req;

	अगर (!req->dma_flag)
		वापस;

	preq->actual += req->भाग_len;
	req->भाग_len = 0;
	req->dma_flag = false;

#अगर_घोषित USE_DMA
	_nbu2ss_dma_unmap_single(udc, ep, req, USB_सूची_IN);
#पूर्ण_अगर

	अगर (preq->actual != preq->length) अणु
		_nbu2ss_epn_in_transfer(udc, ep, req);
	पूर्ण अन्यथा अणु
		mpkt = ep->ep.maxpacket;
		size = preq->actual % mpkt;
		अगर (size > 0) अणु
			अगर (((preq->actual & 0x03) == 0) && (size < mpkt))
				_nbu2ss_ep_in_end(udc, ep->epnum, 0, 0);
		पूर्ण अन्यथा अणु
			_nbu2ss_epn_in_पूर्णांक(udc, ep, req);
		पूर्ण
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत व्योम _nbu2ss_epn_out_dma_पूर्णांक(काष्ठा nbu2ss_udc *udc,
					   काष्ठा nbu2ss_ep *ep,
					   काष्ठा nbu2ss_req *req)
अणु
	पूर्णांक		i;
	u32		num;
	u32		dmacnt, ep_dmacnt;
	u32		mpkt;
	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	num = ep->epnum - 1;

	अगर (req->req.actual == req->req.length) अणु
		अगर ((req->req.length % ep->ep.maxpacket) && !req->zero) अणु
			req->भाग_len = 0;
			req->dma_flag = false;
			_nbu2ss_ep_करोne(ep, req, 0);
			वापस;
		पूर्ण
	पूर्ण

	ep_dmacnt = _nbu2ss_पढ़ोl(&preg->EP_REGS[num].EP_LEN_DCNT)
		 & EPN_DMACNT;
	ep_dmacnt >>= 16;

	क्रम (i = 0; i < EPC_PLL_LOCK_COUNT; i++) अणु
		dmacnt = _nbu2ss_पढ़ोl(&preg->EP_DCR[num].EP_DCR1)
			 & DCR1_EPN_DMACNT;
		dmacnt >>= 16;
		अगर (ep_dmacnt == dmacnt)
			अवरोध;
	पूर्ण

	_nbu2ss_bitclr(&preg->EP_DCR[num].EP_DCR1, DCR1_EPN_REQEN);

	अगर (dmacnt != 0) अणु
		mpkt = ep->ep.maxpacket;
		अगर ((req->भाग_len % mpkt) == 0)
			req->भाग_len -= mpkt * dmacnt;
	पूर्ण

	अगर ((req->req.actual % ep->ep.maxpacket) > 0) अणु
		अगर (req->req.actual == req->भाग_len) अणु
			req->भाग_len = 0;
			req->dma_flag = false;
			_nbu2ss_ep_करोne(ep, req, 0);
			वापस;
		पूर्ण
	पूर्ण

	req->req.actual += req->भाग_len;
	req->भाग_len = 0;
	req->dma_flag = false;

	_nbu2ss_epn_out_पूर्णांक(udc, ep, req);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत व्योम _nbu2ss_epn_पूर्णांक(काष्ठा nbu2ss_udc *udc, u32 epnum)
अणु
	u32	num;
	u32	status;

	काष्ठा nbu2ss_req	*req;
	काष्ठा nbu2ss_ep	*ep = &udc->ep[epnum];

	num = epnum - 1;

	/* Interrupt Status */
	status = _nbu2ss_पढ़ोl(&udc->p_regs->EP_REGS[num].EP_STATUS);

	/* Interrupt Clear */
	_nbu2ss_ग_लिखोl(&udc->p_regs->EP_REGS[num].EP_STATUS, ~status);

	req = list_first_entry_or_null(&ep->queue, काष्ठा nbu2ss_req, queue);
	अगर (!req) अणु
		/* pr_warn("=== %s(%d) req == NULL\n", __func__, epnum); */
		वापस;
	पूर्ण

	अगर (status & EPN_OUT_END_INT) अणु
		status &= ~EPN_OUT_INT;
		_nbu2ss_epn_out_dma_पूर्णांक(udc, ep, req);
	पूर्ण

	अगर (status & EPN_OUT_INT)
		_nbu2ss_epn_out_पूर्णांक(udc, ep, req);

	अगर (status & EPN_IN_END_INT) अणु
		status &= ~EPN_IN_INT;
		_nbu2ss_epn_in_dma_पूर्णांक(udc, ep, req);
	पूर्ण

	अगर (status & EPN_IN_INT)
		_nbu2ss_epn_in_पूर्णांक(udc, ep, req);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत व्योम _nbu2ss_ep_पूर्णांक(काष्ठा nbu2ss_udc *udc, u32 epnum)
अणु
	अगर (epnum == 0)
		_nbu2ss_ep0_पूर्णांक(udc);
	अन्यथा
		_nbu2ss_epn_पूर्णांक(udc, epnum);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम _nbu2ss_ep0_enable(काष्ठा nbu2ss_udc *udc)
अणु
	_nbu2ss_bitset(&udc->p_regs->EP0_CONTROL, (EP0_AUTO | EP0_BCLR));
	_nbu2ss_ग_लिखोl(&udc->p_regs->EP0_INT_ENA, EP0_INT_EN_BIT);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_nuke(काष्ठा nbu2ss_udc *udc,
			काष्ठा nbu2ss_ep *ep,
			पूर्णांक status)
अणु
	काष्ठा nbu2ss_req *req, *n;

	/* Endpoपूर्णांक Disable */
	_nbu2ss_epn_निकास(udc, ep);

	/* DMA Disable */
	_nbu2ss_ep_dma_निकास(udc, ep);

	अगर (list_empty(&ep->queue))
		वापस 0;

	/* called with irqs blocked */
	list_क्रम_each_entry_safe(req, n, &ep->queue, queue) अणु
		_nbu2ss_ep_करोne(ep, req, status);
	पूर्ण

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम _nbu2ss_quiesce(काष्ठा nbu2ss_udc *udc)
अणु
	काष्ठा nbu2ss_ep	*ep;

	udc->gadget.speed = USB_SPEED_UNKNOWN;

	_nbu2ss_nuke(udc, &udc->ep[0], -ESHUTDOWN);

	/* Endpoपूर्णांक n */
	list_क्रम_each_entry(ep, &udc->gadget.ep_list, ep.ep_list) अणु
		_nbu2ss_nuke(udc, ep, -ESHUTDOWN);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_pullup(काष्ठा nbu2ss_udc *udc, पूर्णांक is_on)
अणु
	u32	reg_dt;

	अगर (udc->vbus_active == 0)
		वापस -ESHUTDOWN;

	अगर (is_on) अणु
		/* D+ Pullup */
		अगर (udc->driver) अणु
			reg_dt = (_nbu2ss_पढ़ोl(&udc->p_regs->USB_CONTROL)
				| PUE2) & ~(u32)CONNECTB;

			_nbu2ss_ग_लिखोl(&udc->p_regs->USB_CONTROL, reg_dt);
		पूर्ण

	पूर्ण अन्यथा अणु
		/* D+ Pullकरोwn */
		reg_dt = (_nbu2ss_पढ़ोl(&udc->p_regs->USB_CONTROL) | CONNECTB)
			& ~(u32)PUE2;

		_nbu2ss_ग_लिखोl(&udc->p_regs->USB_CONTROL, reg_dt);
		udc->gadget.speed = USB_SPEED_UNKNOWN;
	पूर्ण

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम _nbu2ss_fअगरo_flush(काष्ठा nbu2ss_udc *udc, काष्ठा nbu2ss_ep *ep)
अणु
	काष्ठा fc_regs __iomem *p = udc->p_regs;

	अगर (udc->vbus_active == 0)
		वापस;

	अगर (ep->epnum == 0) अणु
		/* EP0 */
		_nbu2ss_bitset(&p->EP0_CONTROL, EP0_BCLR);

	पूर्ण अन्यथा अणु
		/* EPN */
		_nbu2ss_ep_dma_पात(udc, ep);
		_nbu2ss_bitset(&p->EP_REGS[ep->epnum - 1].EP_CONTROL, EPN_BCLR);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक _nbu2ss_enable_controller(काष्ठा nbu2ss_udc *udc)
अणु
	पूर्णांक	रुकोcnt = 0;

	अगर (udc->udc_enabled)
		वापस 0;

	/* Reset */
	_nbu2ss_bitset(&udc->p_regs->EPCTR, (सूचीPD | EPC_RST));
	udelay(EPC_RST_DISABLE_TIME);	/* 1us रुको */

	_nbu2ss_bitclr(&udc->p_regs->EPCTR, सूचीPD);
	mdelay(EPC_सूचीPD_DISABLE_TIME);	/* 1ms रुको */

	_nbu2ss_bitclr(&udc->p_regs->EPCTR, EPC_RST);

	_nbu2ss_ग_लिखोl(&udc->p_regs->AHBSCTR, WAIT_MODE);

	_nbu2ss_ग_लिखोl(&udc->p_regs->AHBMCTR,
		       HBUSREQ_MODE | HTRANS_MODE | WBURST_TYPE);

	जबतक (!(_nbu2ss_पढ़ोl(&udc->p_regs->EPCTR) & PLL_LOCK)) अणु
		रुकोcnt++;
		udelay(1);	/* 1us रुको */
		अगर (रुकोcnt == EPC_PLL_LOCK_COUNT) अणु
			dev_err(udc->dev, "*** Reset Cancel failed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	_nbu2ss_bitset(&udc->p_regs->UTMI_CHARACTER_1, USB_SQUSET);

	_nbu2ss_bitset(&udc->p_regs->USB_CONTROL, (INT_SEL | SOF_RCV));

	/* EP0 */
	_nbu2ss_ep0_enable(udc);

	/* USB Interrupt Enable */
	_nbu2ss_bitset(&udc->p_regs->USB_INT_ENA, USB_INT_EN_BIT);

	udc->udc_enabled = true;

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम _nbu2ss_reset_controller(काष्ठा nbu2ss_udc *udc)
अणु
	_nbu2ss_bitset(&udc->p_regs->EPCTR, EPC_RST);
	_nbu2ss_bitclr(&udc->p_regs->EPCTR, EPC_RST);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम _nbu2ss_disable_controller(काष्ठा nbu2ss_udc *udc)
अणु
	अगर (udc->udc_enabled) अणु
		udc->udc_enabled = false;
		_nbu2ss_reset_controller(udc);
		_nbu2ss_bitset(&udc->p_regs->EPCTR, (सूचीPD | EPC_RST));
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत व्योम _nbu2ss_check_vbus(काष्ठा nbu2ss_udc *udc)
अणु
	पूर्णांक	nret;
	u32	reg_dt;

	/* chattering */
	mdelay(VBUS_CHATTERING_MDELAY);		/* रुको (ms) */

	/* VBUS ON Check*/
	reg_dt = gpiod_get_value(vbus_gpio);
	अगर (reg_dt == 0) अणु
		udc->linux_suspended = 0;

		_nbu2ss_reset_controller(udc);
		dev_info(udc->dev, " ----- VBUS OFF\n");

		अगर (udc->vbus_active == 1) अणु
			/* VBUS OFF */
			udc->vbus_active = 0;
			अगर (udc->usb_suspended) अणु
				udc->usb_suspended = 0;
				/* _nbu2ss_reset_controller(udc); */
			पूर्ण
			udc->devstate = USB_STATE_NOTATTACHED;

			_nbu2ss_quiesce(udc);
			अगर (udc->driver) अणु
				spin_unlock(&udc->lock);
				udc->driver->disconnect(&udc->gadget);
				spin_lock(&udc->lock);
			पूर्ण

			_nbu2ss_disable_controller(udc);
		पूर्ण
	पूर्ण अन्यथा अणु
		mdelay(5);		/* रुको (5ms) */
		reg_dt = gpiod_get_value(vbus_gpio);
		अगर (reg_dt == 0)
			वापस;

		dev_info(udc->dev, " ----- VBUS ON\n");

		अगर (udc->linux_suspended)
			वापस;

		अगर (udc->vbus_active == 0) अणु
			/* VBUS ON */
			udc->vbus_active = 1;
			udc->devstate = USB_STATE_POWERED;

			nret = _nbu2ss_enable_controller(udc);
			अगर (nret < 0) अणु
				_nbu2ss_disable_controller(udc);
				udc->vbus_active = 0;
				वापस;
			पूर्ण

			_nbu2ss_pullup(udc, 1);

#अगर_घोषित UDC_DEBUG_DUMP
			_nbu2ss_dump_रेजिस्टर(udc);
#पूर्ण_अगर /* UDC_DEBUG_DUMP */

		पूर्ण अन्यथा अणु
			अगर (udc->devstate == USB_STATE_POWERED)
				_nbu2ss_pullup(udc, 1);
		पूर्ण
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत व्योम _nbu2ss_पूर्णांक_bus_reset(काष्ठा nbu2ss_udc *udc)
अणु
	udc->devstate		= USB_STATE_DEFAULT;
	udc->remote_wakeup	= 0;

	_nbu2ss_quiesce(udc);

	udc->ep0state = EP0_IDLE;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत व्योम _nbu2ss_पूर्णांक_usb_resume(काष्ठा nbu2ss_udc *udc)
अणु
	अगर (udc->usb_suspended == 1) अणु
		udc->usb_suspended = 0;
		अगर (udc->driver && udc->driver->resume) अणु
			spin_unlock(&udc->lock);
			udc->driver->resume(&udc->gadget);
			spin_lock(&udc->lock);
		पूर्ण
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
अटल अंतरभूत व्योम _nbu2ss_पूर्णांक_usb_suspend(काष्ठा nbu2ss_udc *udc)
अणु
	u32	reg_dt;

	अगर (udc->usb_suspended == 0) अणु
		reg_dt = gpiod_get_value(vbus_gpio);

		अगर (reg_dt == 0)
			वापस;

		udc->usb_suspended = 1;
		अगर (udc->driver && udc->driver->suspend) अणु
			spin_unlock(&udc->lock);
			udc->driver->suspend(&udc->gadget);
			spin_lock(&udc->lock);
		पूर्ण

		_nbu2ss_bitset(&udc->p_regs->USB_CONTROL, SUSPEND);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
/* VBUS (GPIO153) Interrupt */
अटल irqवापस_t _nbu2ss_vbus_irq(पूर्णांक irq, व्योम *_udc)
अणु
	काष्ठा nbu2ss_udc	*udc = (काष्ठा nbu2ss_udc *)_udc;

	spin_lock(&udc->lock);
	_nbu2ss_check_vbus(udc);
	spin_unlock(&udc->lock);

	वापस IRQ_HANDLED;
पूर्ण

/*-------------------------------------------------------------------------*/
/* Interrupt (udc) */
अटल irqवापस_t _nbu2ss_udc_irq(पूर्णांक irq, व्योम *_udc)
अणु
	u8	suspend_flag = 0;
	u32	status;
	u32	epnum, पूर्णांक_bit;

	काष्ठा nbu2ss_udc	*udc = (काष्ठा nbu2ss_udc *)_udc;
	काष्ठा fc_regs __iomem *preg = udc->p_regs;

	अगर (gpiod_get_value(vbus_gpio) == 0) अणु
		_nbu2ss_ग_लिखोl(&preg->USB_INT_STA, ~USB_INT_STA_RW);
		_nbu2ss_ग_लिखोl(&preg->USB_INT_ENA, 0);
		वापस IRQ_HANDLED;
	पूर्ण

	spin_lock(&udc->lock);

	क्रम (;;) अणु
		अगर (gpiod_get_value(vbus_gpio) == 0) अणु
			_nbu2ss_ग_लिखोl(&preg->USB_INT_STA, ~USB_INT_STA_RW);
			_nbu2ss_ग_लिखोl(&preg->USB_INT_ENA, 0);
			status = 0;
		पूर्ण अन्यथा अणु
			status = _nbu2ss_पढ़ोl(&preg->USB_INT_STA);
		पूर्ण

		अगर (status == 0)
			अवरोध;

		_nbu2ss_ग_लिखोl(&preg->USB_INT_STA, ~(status & USB_INT_STA_RW));

		अगर (status & USB_RST_INT) अणु
			/* USB Reset */
			_nbu2ss_पूर्णांक_bus_reset(udc);
		पूर्ण

		अगर (status & RSUM_INT) अणु
			/* Resume */
			_nbu2ss_पूर्णांक_usb_resume(udc);
		पूर्ण

		अगर (status & SPND_INT) अणु
			/* Suspend */
			suspend_flag = 1;
		पूर्ण

		अगर (status & EPN_INT) अणु
			/* EP INT */
			पूर्णांक_bit = status >> 8;

			क्रम (epnum = 0; epnum < NUM_ENDPOINTS; epnum++) अणु
				अगर (0x01 & पूर्णांक_bit)
					_nbu2ss_ep_पूर्णांक(udc, epnum);

				पूर्णांक_bit >>= 1;

				अगर (पूर्णांक_bit == 0)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (suspend_flag)
		_nbu2ss_पूर्णांक_usb_suspend(udc);

	spin_unlock(&udc->lock);

	वापस IRQ_HANDLED;
पूर्ण

/*-------------------------------------------------------------------------*/
/* usb_ep_ops */
अटल पूर्णांक nbu2ss_ep_enable(काष्ठा usb_ep *_ep,
			    स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	u8		ep_type;
	अचिन्हित दीर्घ	flags;

	काष्ठा nbu2ss_ep	*ep;
	काष्ठा nbu2ss_udc	*udc;

	अगर (!_ep || !desc) अणु
		pr_err(" *** %s, bad param\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ep = container_of(_ep, काष्ठा nbu2ss_ep, ep);
	अगर (!ep->udc) अणु
		pr_err(" *** %s, ep == NULL !!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ep_type = usb_endpoपूर्णांक_type(desc);
	अगर ((ep_type == USB_ENDPOINT_XFER_CONTROL) ||
	    (ep_type == USB_ENDPOINT_XFER_ISOC)) अणु
		pr_err(" *** %s, bat bmAttributes\n", __func__);
		वापस -EINVAL;
	पूर्ण

	udc = ep->udc;
	अगर (udc->vbus_active == 0)
		वापस -ESHUTDOWN;

	अगर ((!udc->driver) || (udc->gadget.speed == USB_SPEED_UNKNOWN)) अणु
		dev_err(ep->udc->dev, " *** %s, udc !!\n", __func__);
		वापस -ESHUTDOWN;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);

	ep->desc = desc;
	ep->epnum = usb_endpoपूर्णांक_num(desc);
	ep->direct = desc->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK;
	ep->ep_type = ep_type;
	ep->wedged = 0;
	ep->halted = false;
	ep->stalled = false;

	ep->ep.maxpacket = le16_to_cpu(desc->wMaxPacketSize);

	/* DMA setting */
	_nbu2ss_ep_dma_init(udc, ep);

	/* Endpoपूर्णांक setting */
	_nbu2ss_ep_init(udc, ep);

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा nbu2ss_ep	*ep;
	काष्ठा nbu2ss_udc	*udc;
	अचिन्हित दीर्घ		flags;

	अगर (!_ep) अणु
		pr_err(" *** %s, bad param\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ep = container_of(_ep, काष्ठा nbu2ss_ep, ep);
	अगर (!ep->udc) अणु
		pr_err("udc: *** %s, ep == NULL !!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	udc = ep->udc;
	अगर (udc->vbus_active == 0)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&udc->lock, flags);
	_nbu2ss_nuke(udc, ep, -EINPROGRESS);		/* dequeue request */
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल काष्ठा usb_request *nbu2ss_ep_alloc_request(काष्ठा usb_ep *ep,
						   gfp_t gfp_flags)
अणु
	काष्ठा nbu2ss_req *req;

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;

#अगर_घोषित USE_DMA
	req->req.dma = DMA_ADDR_INVALID;
#पूर्ण_अगर
	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम nbu2ss_ep_मुक्त_request(काष्ठा usb_ep *_ep,
				   काष्ठा usb_request *_req)
अणु
	काष्ठा nbu2ss_req *req;

	अगर (_req) अणु
		req = container_of(_req, काष्ठा nbu2ss_req, req);

		kमुक्त(req);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_ep_queue(काष्ठा usb_ep *_ep,
			   काष्ठा usb_request *_req, gfp_t gfp_flags)
अणु
	काष्ठा nbu2ss_req	*req;
	काष्ठा nbu2ss_ep	*ep;
	काष्ठा nbu2ss_udc	*udc;
	अचिन्हित दीर्घ		flags;
	bool			bflag;
	पूर्णांक			result = -EINVAL;

	/* catch various bogus parameters */
	अगर (!_ep || !_req) अणु
		अगर (!_ep)
			pr_err("udc: %s --- _ep == NULL\n", __func__);

		अगर (!_req)
			pr_err("udc: %s --- _req == NULL\n", __func__);

		वापस -EINVAL;
	पूर्ण

	req = container_of(_req, काष्ठा nbu2ss_req, req);
	अगर (unlikely(!_req->complete ||
		     !_req->buf ||
		     !list_empty(&req->queue))) अणु
		अगर (!_req->complete)
			pr_err("udc: %s --- !_req->complete\n", __func__);

		अगर (!_req->buf)
			pr_err("udc:%s --- !_req->buf\n", __func__);

		अगर (!list_empty(&req->queue))
			pr_err("%s --- !list_empty(&req->queue)\n", __func__);

		वापस -EINVAL;
	पूर्ण

	ep = container_of(_ep, काष्ठा nbu2ss_ep, ep);
	udc = ep->udc;

	अगर (udc->vbus_active == 0) अणु
		dev_info(udc->dev, "Can't ep_queue (VBUS OFF)\n");
		वापस -ESHUTDOWN;
	पूर्ण

	अगर (unlikely(!udc->driver)) अणु
		dev_err(udc->dev, "%s, bogus device state %p\n", __func__,
			udc->driver);
		वापस -ESHUTDOWN;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);

#अगर_घोषित USE_DMA
	अगर ((uपूर्णांकptr_t)req->req.buf & 0x3)
		req->unaligned = true;
	अन्यथा
		req->unaligned = false;

	अगर (req->unaligned) अणु
		अगर (!ep->virt_buf)
			ep->virt_buf = dma_alloc_coherent(udc->dev, PAGE_SIZE,
							  &ep->phys_buf,
							  GFP_ATOMIC | GFP_DMA);
		अगर (ep->epnum > 0)  अणु
			अगर (ep->direct == USB_सूची_IN)
				स_नकल(ep->virt_buf, req->req.buf,
				       req->req.length);
		पूर्ण
	पूर्ण

	अगर ((ep->epnum > 0) && (ep->direct == USB_सूची_OUT) &&
	    (req->req.dma != 0))
		_nbu2ss_dma_map_single(udc, ep, req, USB_सूची_OUT);
#पूर्ण_अगर

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	bflag = list_empty(&ep->queue);
	list_add_tail(&req->queue, &ep->queue);

	अगर (bflag && !ep->stalled) अणु
		result = _nbu2ss_start_transfer(udc, ep, req, false);
		अगर (result < 0) अणु
			dev_err(udc->dev, " *** %s, result = %d\n", __func__,
				result);
			list_del(&req->queue);
		पूर्ण अन्यथा अगर ((ep->epnum > 0) && (ep->direct == USB_सूची_OUT)) अणु
#अगर_घोषित USE_DMA
			अगर (req->req.length < 4 &&
			    req->req.length == req->req.actual)
#अन्यथा
			अगर (req->req.length == req->req.actual)
#पूर्ण_अगर
				_nbu2ss_ep_करोne(ep, req, result);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा nbu2ss_req	*req;
	काष्ठा nbu2ss_ep	*ep;
	काष्ठा nbu2ss_udc	*udc;
	अचिन्हित दीर्घ flags;

	/* catch various bogus parameters */
	अगर (!_ep || !_req) अणु
		/* pr_err("%s, bad param(1)\n", __func__); */
		वापस -EINVAL;
	पूर्ण

	ep = container_of(_ep, काष्ठा nbu2ss_ep, ep);

	udc = ep->udc;
	अगर (!udc)
		वापस -EINVAL;

	spin_lock_irqsave(&udc->lock, flags);

	/* make sure it's actually queued on this endpoपूर्णांक */
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->req == _req) अणु
			_nbu2ss_ep_करोne(ep, req, -ECONNRESET);
			spin_unlock_irqrestore(&udc->lock, flags);
			वापस 0;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);

	pr_debug("%s no queue(EINVAL)\n", __func__);

	वापस -EINVAL;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	u8		ep_adrs;
	अचिन्हित दीर्घ	flags;

	काष्ठा nbu2ss_ep	*ep;
	काष्ठा nbu2ss_udc	*udc;

	अगर (!_ep) अणु
		pr_err("%s, bad param\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ep = container_of(_ep, काष्ठा nbu2ss_ep, ep);

	udc = ep->udc;
	अगर (!udc) अणु
		dev_err(ep->udc->dev, " *** %s, bad udc\n", __func__);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);

	ep_adrs = ep->epnum | ep->direct;
	अगर (value == 0) अणु
		_nbu2ss_set_endpoपूर्णांक_stall(udc, ep_adrs, value);
		ep->stalled = false;
	पूर्ण अन्यथा अणु
		अगर (list_empty(&ep->queue))
			_nbu2ss_epn_set_stall(udc, ep);
		अन्यथा
			ep->stalled = true;
	पूर्ण

	अगर (value == 0)
		ep->wedged = 0;

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक nbu2ss_ep_set_wedge(काष्ठा usb_ep *_ep)
अणु
	वापस nbu2ss_ep_set_halt(_ep, 1);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_ep_fअगरo_status(काष्ठा usb_ep *_ep)
अणु
	u32		data;
	काष्ठा nbu2ss_ep	*ep;
	काष्ठा nbu2ss_udc	*udc;
	अचिन्हित दीर्घ		flags;
	काष्ठा fc_regs	__iomem *preg;

	अगर (!_ep) अणु
		pr_err("%s, bad param\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ep = container_of(_ep, काष्ठा nbu2ss_ep, ep);

	udc = ep->udc;
	अगर (!udc) अणु
		dev_err(ep->udc->dev, "%s, bad udc\n", __func__);
		वापस -EINVAL;
	पूर्ण

	preg = udc->p_regs;

	data = gpiod_get_value(vbus_gpio);
	अगर (data == 0)
		वापस -EINVAL;

	spin_lock_irqsave(&udc->lock, flags);

	अगर (ep->epnum == 0) अणु
		data = _nbu2ss_पढ़ोl(&preg->EP0_LENGTH) & EP0_LDATA;

	पूर्ण अन्यथा अणु
		data = _nbu2ss_पढ़ोl(&preg->EP_REGS[ep->epnum - 1].EP_LEN_DCNT)
			& EPN_LDATA;
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम  nbu2ss_ep_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	u32			data;
	काष्ठा nbu2ss_ep	*ep;
	काष्ठा nbu2ss_udc	*udc;
	अचिन्हित दीर्घ		flags;

	अगर (!_ep) अणु
		pr_err("udc: %s, bad param\n", __func__);
		वापस;
	पूर्ण

	ep = container_of(_ep, काष्ठा nbu2ss_ep, ep);

	udc = ep->udc;
	अगर (!udc) अणु
		dev_err(ep->udc->dev, "%s, bad udc\n", __func__);
		वापस;
	पूर्ण

	data = gpiod_get_value(vbus_gpio);
	अगर (data == 0)
		वापस;

	spin_lock_irqsave(&udc->lock, flags);
	_nbu2ss_fअगरo_flush(udc, ep);
	spin_unlock_irqrestore(&udc->lock, flags);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल स्थिर काष्ठा usb_ep_ops nbu2ss_ep_ops = अणु
	.enable		= nbu2ss_ep_enable,
	.disable	= nbu2ss_ep_disable,

	.alloc_request	= nbu2ss_ep_alloc_request,
	.मुक्त_request	= nbu2ss_ep_मुक्त_request,

	.queue		= nbu2ss_ep_queue,
	.dequeue	= nbu2ss_ep_dequeue,

	.set_halt	= nbu2ss_ep_set_halt,
	.set_wedge	= nbu2ss_ep_set_wedge,

	.fअगरo_status	= nbu2ss_ep_fअगरo_status,
	.fअगरo_flush	= nbu2ss_ep_fअगरo_flush,
पूर्ण;

/*-------------------------------------------------------------------------*/
/* usb_gadget_ops */

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_gad_get_frame(काष्ठा usb_gadget *pgadget)
अणु
	u32			data;
	काष्ठा nbu2ss_udc	*udc;

	अगर (!pgadget) अणु
		pr_err("udc: %s, bad param\n", __func__);
		वापस -EINVAL;
	पूर्ण

	udc = container_of(pgadget, काष्ठा nbu2ss_udc, gadget);
	data = gpiod_get_value(vbus_gpio);
	अगर (data == 0)
		वापस -EINVAL;

	वापस _nbu2ss_पढ़ोl(&udc->p_regs->USB_ADDRESS) & FRAME;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_gad_wakeup(काष्ठा usb_gadget *pgadget)
अणु
	पूर्णांक	i;
	u32	data;

	काष्ठा nbu2ss_udc	*udc;

	अगर (!pgadget) अणु
		pr_err("%s, bad param\n", __func__);
		वापस -EINVAL;
	पूर्ण

	udc = container_of(pgadget, काष्ठा nbu2ss_udc, gadget);

	data = gpiod_get_value(vbus_gpio);
	अगर (data == 0) अणु
		dev_warn(&pgadget->dev, "VBUS LEVEL = %d\n", data);
		वापस -EINVAL;
	पूर्ण

	_nbu2ss_bitset(&udc->p_regs->EPCTR, PLL_RESUME);

	क्रम (i = 0; i < EPC_PLL_LOCK_COUNT; i++) अणु
		data = _nbu2ss_पढ़ोl(&udc->p_regs->EPCTR);

		अगर (data & PLL_LOCK)
			अवरोध;
	पूर्ण

	_nbu2ss_bitclr(&udc->p_regs->EPCTR, PLL_RESUME);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_gad_set_selfघातered(काष्ठा usb_gadget *pgadget,
				      पूर्णांक is_selfघातered)
अणु
	काष्ठा nbu2ss_udc       *udc;
	अचिन्हित दीर्घ		flags;

	अगर (!pgadget) अणु
		pr_err("%s, bad param\n", __func__);
		वापस -EINVAL;
	पूर्ण

	udc = container_of(pgadget, काष्ठा nbu2ss_udc, gadget);

	spin_lock_irqsave(&udc->lock, flags);
	pgadget->is_selfघातered = (is_selfघातered != 0);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_gad_vbus_session(काष्ठा usb_gadget *pgadget, पूर्णांक is_active)
अणु
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_gad_vbus_draw(काष्ठा usb_gadget *pgadget, अचिन्हित पूर्णांक mA)
अणु
	काष्ठा nbu2ss_udc	*udc;
	अचिन्हित दीर्घ		flags;

	अगर (!pgadget) अणु
		pr_err("%s, bad param\n", __func__);
		वापस -EINVAL;
	पूर्ण

	udc = container_of(pgadget, काष्ठा nbu2ss_udc, gadget);

	spin_lock_irqsave(&udc->lock, flags);
	udc->mA = mA;
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_gad_pullup(काष्ठा usb_gadget *pgadget, पूर्णांक is_on)
अणु
	काष्ठा nbu2ss_udc	*udc;
	अचिन्हित दीर्घ		flags;

	अगर (!pgadget) अणु
		pr_err("%s, bad param\n", __func__);
		वापस -EINVAL;
	पूर्ण

	udc = container_of(pgadget, काष्ठा nbu2ss_udc, gadget);

	अगर (!udc->driver) अणु
		pr_warn("%s, Not Regist Driver\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (udc->vbus_active == 0)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&udc->lock, flags);
	_nbu2ss_pullup(udc, is_on);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_gad_ioctl(काष्ठा usb_gadget *pgadget,
			    अचिन्हित पूर्णांक code, अचिन्हित दीर्घ param)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops nbu2ss_gadget_ops = अणु
	.get_frame		= nbu2ss_gad_get_frame,
	.wakeup			= nbu2ss_gad_wakeup,
	.set_selfघातered	= nbu2ss_gad_set_selfघातered,
	.vbus_session		= nbu2ss_gad_vbus_session,
	.vbus_draw		= nbu2ss_gad_vbus_draw,
	.pullup			= nbu2ss_gad_pullup,
	.ioctl			= nbu2ss_gad_ioctl,
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा usb_ep_caps caps;
पूर्ण ep_info[NUM_ENDPOINTS] = अणु
#घोषणा EP_INFO(_name, _caps) \
	अणु \
		.name = _name, \
		.caps = _caps, \
	पूर्ण

	EP_INFO("ep0",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTROL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep1-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep2-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep3in-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep4-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep5-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep6-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep7-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep8in-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep9-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("epa-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("epb-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("epc-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("epdin-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_सूची_IN)),

#अघोषित EP_INFO
पूर्ण;

/*-------------------------------------------------------------------------*/
अटल व्योम nbu2ss_drv_ep_init(काष्ठा nbu2ss_udc *udc)
अणु
	पूर्णांक	i;

	INIT_LIST_HEAD(&udc->gadget.ep_list);
	udc->gadget.ep0 = &udc->ep[0].ep;

	क्रम (i = 0; i < NUM_ENDPOINTS; i++) अणु
		काष्ठा nbu2ss_ep *ep = &udc->ep[i];

		ep->udc = udc;
		ep->desc = शून्य;

		ep->ep.driver_data = शून्य;
		ep->ep.name = ep_info[i].name;
		ep->ep.caps = ep_info[i].caps;
		ep->ep.ops = &nbu2ss_ep_ops;

		usb_ep_set_maxpacket_limit(&ep->ep,
					   i == 0 ? EP0_PACKETSIZE
					   : EP_PACKETSIZE);

		list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);
		INIT_LIST_HEAD(&ep->queue);
	पूर्ण

	list_del_init(&udc->ep[0].ep.ep_list);
पूर्ण

/*-------------------------------------------------------------------------*/
/* platक्रमm_driver */
अटल पूर्णांक nbu2ss_drv_contest_init(काष्ठा platक्रमm_device *pdev,
				   काष्ठा nbu2ss_udc *udc)
अणु
	spin_lock_init(&udc->lock);
	udc->dev = &pdev->dev;

	udc->gadget.is_selfघातered = 1;
	udc->devstate = USB_STATE_NOTATTACHED;
	udc->pdev = pdev;
	udc->mA = 0;

	udc->pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);

	/* init Endpoपूर्णांक */
	nbu2ss_drv_ep_init(udc);

	/* init Gadget */
	udc->gadget.ops = &nbu2ss_gadget_ops;
	udc->gadget.ep0 = &udc->ep[0].ep;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->gadget.name = driver_name;
	/* udc->gadget.is_dualspeed = 1; */

	device_initialize(&udc->gadget.dev);

	dev_set_name(&udc->gadget.dev, "gadget");
	udc->gadget.dev.parent = &pdev->dev;
	udc->gadget.dev.dma_mask = pdev->dev.dma_mask;

	वापस 0;
पूर्ण

/*
 *	probe - binds to the platक्रमm device
 */
अटल पूर्णांक nbu2ss_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक status;
	काष्ठा nbu2ss_udc *udc;
	पूर्णांक irq;
	व्योम __iomem *mmio_base;

	udc = &udc_controller;
	स_रखो(udc, 0, माप(काष्ठा nbu2ss_udc));

	platक्रमm_set_drvdata(pdev, udc);

	/* require I/O memory and IRQ to be provided as resources */
	mmio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mmio_base))
		वापस PTR_ERR(mmio_base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	status = devm_request_irq(&pdev->dev, irq, _nbu2ss_udc_irq,
				  0, driver_name, udc);

	/* IO Memory */
	udc->p_regs = (काष्ठा fc_regs __iomem *)mmio_base;

	/* USB Function Controller Interrupt */
	अगर (status != 0) अणु
		dev_err(udc->dev, "request_irq(USB_UDC_IRQ_1) failed\n");
		वापस status;
	पूर्ण

	/* Driver Initialization */
	status = nbu2ss_drv_contest_init(pdev, udc);
	अगर (status < 0) अणु
		/* Error */
		वापस status;
	पूर्ण

	/* VBUS Interrupt */
	vbus_irq = gpiod_to_irq(vbus_gpio);
	irq_set_irq_type(vbus_irq, IRQ_TYPE_EDGE_BOTH);
	status = request_irq(vbus_irq,
			     _nbu2ss_vbus_irq, IRQF_SHARED, driver_name, udc);

	अगर (status != 0) अणु
		dev_err(udc->dev, "request_irq(vbus_irq) failed\n");
		वापस status;
	पूर्ण

	वापस status;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम nbu2ss_drv_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nbu2ss_udc	*udc;

	udc = platक्रमm_get_drvdata(pdev);
	अगर (!udc)
		वापस;

	_nbu2ss_disable_controller(udc);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nbu2ss_udc	*udc;
	काष्ठा nbu2ss_ep	*ep;
	पूर्णांक	i;

	udc = &udc_controller;

	क्रम (i = 0; i < NUM_ENDPOINTS; i++) अणु
		ep = &udc->ep[i];
		अगर (ep->virt_buf)
			dma_मुक्त_coherent(udc->dev, PAGE_SIZE, (व्योम *)ep->virt_buf,
					  ep->phys_buf);
	पूर्ण

	/* Interrupt Handler - Release */
	मुक्त_irq(vbus_irq, udc);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_drv_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा nbu2ss_udc	*udc;

	udc = platक्रमm_get_drvdata(pdev);
	अगर (!udc)
		वापस 0;

	अगर (udc->vbus_active) अणु
		udc->vbus_active = 0;
		udc->devstate = USB_STATE_NOTATTACHED;
		udc->linux_suspended = 1;

		अगर (udc->usb_suspended) अणु
			udc->usb_suspended = 0;
			_nbu2ss_reset_controller(udc);
		पूर्ण

		_nbu2ss_quiesce(udc);
	पूर्ण
	_nbu2ss_disable_controller(udc);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक nbu2ss_drv_resume(काष्ठा platक्रमm_device *pdev)
अणु
	u32	data;
	काष्ठा nbu2ss_udc	*udc;

	udc = platक्रमm_get_drvdata(pdev);
	अगर (!udc)
		वापस 0;

	data = gpiod_get_value(vbus_gpio);
	अगर (data) अणु
		udc->vbus_active = 1;
		udc->devstate = USB_STATE_POWERED;
		_nbu2ss_enable_controller(udc);
		_nbu2ss_pullup(udc, 1);
	पूर्ण

	udc->linux_suspended = 0;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver udc_driver = अणु
	.probe		= nbu2ss_drv_probe,
	.shutकरोwn	= nbu2ss_drv_shutकरोwn,
	.हटाओ		= nbu2ss_drv_हटाओ,
	.suspend	= nbu2ss_drv_suspend,
	.resume		= nbu2ss_drv_resume,
	.driver		= अणु
		.name	= driver_name,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(udc_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Renesas Electronics Corporation");
MODULE_LICENSE("GPL");
