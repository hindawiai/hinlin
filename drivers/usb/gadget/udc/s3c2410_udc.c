<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * linux/drivers/usb/gadget/s3c2410_udc.c
 *
 * Samsung S3C24xx series on-chip full speed USB device controllers
 *
 * Copyright (C) 2004-2007 Herbert Pथघtzl - Arnaud Patard
 *	Additional cleanups by Ben Dooks <ben-linux@fluff.org>
 */

#घोषणा pr_fmt(fmt) "s3c2410_udc: " fmt

#समावेश <linux/module.h>
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
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/prefetch.h>
#समावेश <linux/पन.स>

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/usb.h>
#समावेश <linux/usb/gadget.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/platक्रमm_data/usb-s3c2410_udc.h>

#समावेश "s3c2410_udc.h"
#समावेश "s3c2410_udc_regs.h"

#घोषणा DRIVER_DESC	"S3C2410 USB Device Controller Gadget"
#घोषणा DRIVER_AUTHOR	"Herbert Pथघtzl <herbert@13thfloor.at>, " \
			"Arnaud Patard <arnaud.patard@rtp-net.org>"

अटल स्थिर अक्षर		gadget_name[] = "s3c2410_udc";
अटल स्थिर अक्षर		driver_desc[] = DRIVER_DESC;

अटल काष्ठा s3c2410_udc	*the_controller;
अटल काष्ठा clk		*udc_घड़ी;
अटल काष्ठा clk		*usb_bus_घड़ी;
अटल व्योम __iomem		*base_addr;
अटल पूर्णांक			irq_usbd;
अटल काष्ठा dentry		*s3c2410_udc_debugfs_root;

अटल अंतरभूत u32 udc_पढ़ो(u32 reg)
अणु
	वापस पढ़ोb(base_addr + reg);
पूर्ण

अटल अंतरभूत व्योम udc_ग_लिखो(u32 value, u32 reg)
अणु
	ग_लिखोb(value, base_addr + reg);
पूर्ण

अटल अंतरभूत व्योम udc_ग_लिखोb(व्योम __iomem *base, u32 value, u32 reg)
अणु
	ग_लिखोb(value, base + reg);
पूर्ण

अटल काष्ठा s3c2410_udc_mach_info *udc_info;

/*************************** DEBUG FUNCTION ***************************/
#घोषणा DEBUG_NORMAL	1
#घोषणा DEBUG_VERBOSE	2

#अगर_घोषित CONFIG_USB_S3C2410_DEBUG
#घोषणा USB_S3C2410_DEBUG_LEVEL 0

अटल uपूर्णांक32_t s3c2410_ticks = 0;

__म_लिखो(2, 3)
अटल व्योम dprपूर्णांकk(पूर्णांक level, स्थिर अक्षर *fmt, ...)
अणु
	अटल दीर्घ prevticks;
	अटल पूर्णांक invocation;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (level > USB_S3C2410_DEBUG_LEVEL)
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (s3c2410_ticks != prevticks) अणु
		prevticks = s3c2410_ticks;
		invocation = 0;
	पूर्ण

	pr_debug("%1lu.%02d USB: %pV", prevticks, invocation++, &vaf);

	बहु_पूर्ण(args);
पूर्ण
#अन्यथा
__म_लिखो(2, 3)
अटल व्योम dprपूर्णांकk(पूर्णांक level, स्थिर अक्षर *fmt, ...)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक s3c2410_udc_debugfs_show(काष्ठा seq_file *m, व्योम *p)
अणु
	u32 addr_reg, pwr_reg, ep_पूर्णांक_reg, usb_पूर्णांक_reg;
	u32 ep_पूर्णांक_en_reg, usb_पूर्णांक_en_reg, ep0_csr;
	u32 ep1_i_csr1, ep1_i_csr2, ep1_o_csr1, ep1_o_csr2;
	u32 ep2_i_csr1, ep2_i_csr2, ep2_o_csr1, ep2_o_csr2;

	addr_reg       = udc_पढ़ो(S3C2410_UDC_FUNC_ADDR_REG);
	pwr_reg        = udc_पढ़ो(S3C2410_UDC_PWR_REG);
	ep_पूर्णांक_reg     = udc_पढ़ो(S3C2410_UDC_EP_INT_REG);
	usb_पूर्णांक_reg    = udc_पढ़ो(S3C2410_UDC_USB_INT_REG);
	ep_पूर्णांक_en_reg  = udc_पढ़ो(S3C2410_UDC_EP_INT_EN_REG);
	usb_पूर्णांक_en_reg = udc_पढ़ो(S3C2410_UDC_USB_INT_EN_REG);
	udc_ग_लिखो(0, S3C2410_UDC_INDEX_REG);
	ep0_csr        = udc_पढ़ो(S3C2410_UDC_IN_CSR1_REG);
	udc_ग_लिखो(1, S3C2410_UDC_INDEX_REG);
	ep1_i_csr1     = udc_पढ़ो(S3C2410_UDC_IN_CSR1_REG);
	ep1_i_csr2     = udc_पढ़ो(S3C2410_UDC_IN_CSR2_REG);
	ep1_o_csr1     = udc_पढ़ो(S3C2410_UDC_IN_CSR1_REG);
	ep1_o_csr2     = udc_पढ़ो(S3C2410_UDC_IN_CSR2_REG);
	udc_ग_लिखो(2, S3C2410_UDC_INDEX_REG);
	ep2_i_csr1     = udc_पढ़ो(S3C2410_UDC_IN_CSR1_REG);
	ep2_i_csr2     = udc_पढ़ो(S3C2410_UDC_IN_CSR2_REG);
	ep2_o_csr1     = udc_पढ़ो(S3C2410_UDC_IN_CSR1_REG);
	ep2_o_csr2     = udc_पढ़ो(S3C2410_UDC_IN_CSR2_REG);

	seq_म_लिखो(m, "FUNC_ADDR_REG  : 0x%04X\n"
		 "PWR_REG        : 0x%04X\n"
		 "EP_INT_REG     : 0x%04X\n"
		 "USB_INT_REG    : 0x%04X\n"
		 "EP_INT_EN_REG  : 0x%04X\n"
		 "USB_INT_EN_REG : 0x%04X\n"
		 "EP0_CSR        : 0x%04X\n"
		 "EP1_I_CSR1     : 0x%04X\n"
		 "EP1_I_CSR2     : 0x%04X\n"
		 "EP1_O_CSR1     : 0x%04X\n"
		 "EP1_O_CSR2     : 0x%04X\n"
		 "EP2_I_CSR1     : 0x%04X\n"
		 "EP2_I_CSR2     : 0x%04X\n"
		 "EP2_O_CSR1     : 0x%04X\n"
		 "EP2_O_CSR2     : 0x%04X\n",
			addr_reg, pwr_reg, ep_पूर्णांक_reg, usb_पूर्णांक_reg,
			ep_पूर्णांक_en_reg, usb_पूर्णांक_en_reg, ep0_csr,
			ep1_i_csr1, ep1_i_csr2, ep1_o_csr1, ep1_o_csr2,
			ep2_i_csr1, ep2_i_csr2, ep2_o_csr1, ep2_o_csr2
		);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(s3c2410_udc_debugfs);

/* io macros */

अटल अंतरभूत व्योम s3c2410_udc_clear_ep0_opr(व्योम __iomem *base)
अणु
	udc_ग_लिखोb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	udc_ग_लिखोb(base, S3C2410_UDC_EP0_CSR_SOPKTRDY,
			S3C2410_UDC_EP0_CSR_REG);
पूर्ण

अटल अंतरभूत व्योम s3c2410_udc_clear_ep0_sst(व्योम __iomem *base)
अणु
	udc_ग_लिखोb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	ग_लिखोb(0x00, base + S3C2410_UDC_EP0_CSR_REG);
पूर्ण

अटल अंतरभूत व्योम s3c2410_udc_clear_ep0_se(व्योम __iomem *base)
अणु
	udc_ग_लिखोb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	udc_ग_लिखोb(base, S3C2410_UDC_EP0_CSR_SSE, S3C2410_UDC_EP0_CSR_REG);
पूर्ण

अटल अंतरभूत व्योम s3c2410_udc_set_ep0_ipr(व्योम __iomem *base)
अणु
	udc_ग_लिखोb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	udc_ग_लिखोb(base, S3C2410_UDC_EP0_CSR_IPKRDY, S3C2410_UDC_EP0_CSR_REG);
पूर्ण

अटल अंतरभूत व्योम s3c2410_udc_set_ep0_de(व्योम __iomem *base)
अणु
	udc_ग_लिखोb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	udc_ग_लिखोb(base, S3C2410_UDC_EP0_CSR_DE, S3C2410_UDC_EP0_CSR_REG);
पूर्ण

अंतरभूत व्योम s3c2410_udc_set_ep0_ss(व्योम __iomem *b)
अणु
	udc_ग_लिखोb(b, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	udc_ग_लिखोb(b, S3C2410_UDC_EP0_CSR_SENDSTL, S3C2410_UDC_EP0_CSR_REG);
पूर्ण

अटल अंतरभूत व्योम s3c2410_udc_set_ep0_de_out(व्योम __iomem *base)
अणु
	udc_ग_लिखोb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);

	udc_ग_लिखोb(base, (S3C2410_UDC_EP0_CSR_SOPKTRDY
				| S3C2410_UDC_EP0_CSR_DE),
			S3C2410_UDC_EP0_CSR_REG);
पूर्ण

अटल अंतरभूत व्योम s3c2410_udc_set_ep0_de_in(व्योम __iomem *base)
अणु
	udc_ग_लिखोb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	udc_ग_लिखोb(base, (S3C2410_UDC_EP0_CSR_IPKRDY
			| S3C2410_UDC_EP0_CSR_DE),
		S3C2410_UDC_EP0_CSR_REG);
पूर्ण

/*------------------------- I/O ----------------------------------*/

/*
 *	s3c2410_udc_करोne
 */
अटल व्योम s3c2410_udc_करोne(काष्ठा s3c2410_ep *ep,
		काष्ठा s3c2410_request *req, पूर्णांक status)
अणु
	अचिन्हित halted = ep->halted;

	list_del_init(&req->queue);

	अगर (likely(req->req.status == -EINPROGRESS))
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	ep->halted = 1;
	usb_gadget_giveback_request(&ep->ep, &req->req);
	ep->halted = halted;
पूर्ण

अटल व्योम s3c2410_udc_nuke(काष्ठा s3c2410_udc *udc,
		काष्ठा s3c2410_ep *ep, पूर्णांक status)
अणु
	जबतक (!list_empty(&ep->queue)) अणु
		काष्ठा s3c2410_request *req;
		req = list_entry(ep->queue.next, काष्ठा s3c2410_request,
				queue);
		s3c2410_udc_करोne(ep, req, status);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक s3c2410_udc_fअगरo_count_out(व्योम)
अणु
	पूर्णांक पंचांगp;

	पंचांगp = udc_पढ़ो(S3C2410_UDC_OUT_FIFO_CNT2_REG) << 8;
	पंचांगp |= udc_पढ़ो(S3C2410_UDC_OUT_FIFO_CNT1_REG);
	वापस पंचांगp;
पूर्ण

/*
 *	s3c2410_udc_ग_लिखो_packet
 */
अटल अंतरभूत पूर्णांक s3c2410_udc_ग_लिखो_packet(पूर्णांक fअगरo,
		काष्ठा s3c2410_request *req,
		अचिन्हित max)
अणु
	अचिन्हित len = min(req->req.length - req->req.actual, max);
	u8 *buf = req->req.buf + req->req.actual;

	prefetch(buf);

	dprपूर्णांकk(DEBUG_VERBOSE, "%s %d %d %d %d\n", __func__,
		req->req.actual, req->req.length, len, req->req.actual + len);

	req->req.actual += len;

	udelay(5);
	ग_लिखोsb(base_addr + fअगरo, buf, len);
	वापस len;
पूर्ण

/*
 *	s3c2410_udc_ग_लिखो_fअगरo
 *
 * वापस:  0 = still running, 1 = completed, negative = त्रुटि_सं
 */
अटल पूर्णांक s3c2410_udc_ग_लिखो_fअगरo(काष्ठा s3c2410_ep *ep,
		काष्ठा s3c2410_request *req)
अणु
	अचिन्हित	count;
	पूर्णांक		is_last;
	u32		idx;
	पूर्णांक		fअगरo_reg;
	u32		ep_csr;

	idx = ep->bEndpoपूर्णांकAddress & 0x7F;
	चयन (idx) अणु
	शेष:
		idx = 0;
		fallthrough;
	हाल 0:
		fअगरo_reg = S3C2410_UDC_EP0_FIFO_REG;
		अवरोध;
	हाल 1:
		fअगरo_reg = S3C2410_UDC_EP1_FIFO_REG;
		अवरोध;
	हाल 2:
		fअगरo_reg = S3C2410_UDC_EP2_FIFO_REG;
		अवरोध;
	हाल 3:
		fअगरo_reg = S3C2410_UDC_EP3_FIFO_REG;
		अवरोध;
	हाल 4:
		fअगरo_reg = S3C2410_UDC_EP4_FIFO_REG;
		अवरोध;
	पूर्ण

	count = s3c2410_udc_ग_लिखो_packet(fअगरo_reg, req, ep->ep.maxpacket);

	/* last packet is often लघु (someबार a zlp) */
	अगर (count != ep->ep.maxpacket)
		is_last = 1;
	अन्यथा अगर (req->req.length != req->req.actual || req->req.zero)
		is_last = 0;
	अन्यथा
		is_last = 2;

	/* Only ep0 debug messages are पूर्णांकeresting */
	अगर (idx == 0)
		dprपूर्णांकk(DEBUG_NORMAL,
			"Written ep%d %d.%d of %d b [last %d,z %d]\n",
			idx, count, req->req.actual, req->req.length,
			is_last, req->req.zero);

	अगर (is_last) अणु
		/* The order is important. It prevents sending 2 packets
		 * at the same समय */

		अगर (idx == 0) अणु
			/* Reset संकेत => no need to say 'data sent' */
			अगर (!(udc_पढ़ो(S3C2410_UDC_USB_INT_REG)
					& S3C2410_UDC_USBINT_RESET))
				s3c2410_udc_set_ep0_de_in(base_addr);
			ep->dev->ep0state = EP0_IDLE;
		पूर्ण अन्यथा अणु
			udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
			ep_csr = udc_पढ़ो(S3C2410_UDC_IN_CSR1_REG);
			udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
			udc_ग_लिखो(ep_csr | S3C2410_UDC_ICSR1_PKTRDY,
					S3C2410_UDC_IN_CSR1_REG);
		पूर्ण

		s3c2410_udc_करोne(ep, req, 0);
		is_last = 1;
	पूर्ण अन्यथा अणु
		अगर (idx == 0) अणु
			/* Reset संकेत => no need to say 'data sent' */
			अगर (!(udc_पढ़ो(S3C2410_UDC_USB_INT_REG)
					& S3C2410_UDC_USBINT_RESET))
				s3c2410_udc_set_ep0_ipr(base_addr);
		पूर्ण अन्यथा अणु
			udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
			ep_csr = udc_पढ़ो(S3C2410_UDC_IN_CSR1_REG);
			udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
			udc_ग_लिखो(ep_csr | S3C2410_UDC_ICSR1_PKTRDY,
					S3C2410_UDC_IN_CSR1_REG);
		पूर्ण
	पूर्ण

	वापस is_last;
पूर्ण

अटल अंतरभूत पूर्णांक s3c2410_udc_पढ़ो_packet(पूर्णांक fअगरo, u8 *buf,
		काष्ठा s3c2410_request *req, अचिन्हित avail)
अणु
	अचिन्हित len;

	len = min(req->req.length - req->req.actual, avail);
	req->req.actual += len;

	पढ़ोsb(fअगरo + base_addr, buf, len);
	वापस len;
पूर्ण

/*
 * वापस:  0 = still running, 1 = queue empty, negative = त्रुटि_सं
 */
अटल पूर्णांक s3c2410_udc_पढ़ो_fअगरo(काष्ठा s3c2410_ep *ep,
				 काष्ठा s3c2410_request *req)
अणु
	u8		*buf;
	u32		ep_csr;
	अचिन्हित	bufferspace;
	पूर्णांक		is_last = 1;
	अचिन्हित	avail;
	पूर्णांक		fअगरo_count = 0;
	u32		idx;
	पूर्णांक		fअगरo_reg;

	idx = ep->bEndpoपूर्णांकAddress & 0x7F;

	चयन (idx) अणु
	शेष:
		idx = 0;
		fallthrough;
	हाल 0:
		fअगरo_reg = S3C2410_UDC_EP0_FIFO_REG;
		अवरोध;
	हाल 1:
		fअगरo_reg = S3C2410_UDC_EP1_FIFO_REG;
		अवरोध;
	हाल 2:
		fअगरo_reg = S3C2410_UDC_EP2_FIFO_REG;
		अवरोध;
	हाल 3:
		fअगरo_reg = S3C2410_UDC_EP3_FIFO_REG;
		अवरोध;
	हाल 4:
		fअगरo_reg = S3C2410_UDC_EP4_FIFO_REG;
		अवरोध;
	पूर्ण

	अगर (!req->req.length)
		वापस 1;

	buf = req->req.buf + req->req.actual;
	bufferspace = req->req.length - req->req.actual;
	अगर (!bufferspace) अणु
		dprपूर्णांकk(DEBUG_NORMAL, "%s: buffer full!\n", __func__);
		वापस -1;
	पूर्ण

	udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);

	fअगरo_count = s3c2410_udc_fअगरo_count_out();
	dprपूर्णांकk(DEBUG_NORMAL, "%s fifo count : %d\n", __func__, fअगरo_count);

	अगर (fअगरo_count > ep->ep.maxpacket)
		avail = ep->ep.maxpacket;
	अन्यथा
		avail = fअगरo_count;

	fअगरo_count = s3c2410_udc_पढ़ो_packet(fअगरo_reg, buf, req, avail);

	/* checking this with ep0 is not accurate as we alपढ़ोy
	 * पढ़ो a control request
	 **/
	अगर (idx != 0 && fअगरo_count < ep->ep.maxpacket) अणु
		is_last = 1;
		/* overflowed this request?  flush extra data */
		अगर (fअगरo_count != avail)
			req->req.status = -EOVERFLOW;
	पूर्ण अन्यथा अणु
		is_last = (req->req.length <= req->req.actual) ? 1 : 0;
	पूर्ण

	udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
	fअगरo_count = s3c2410_udc_fअगरo_count_out();

	/* Only ep0 debug messages are पूर्णांकeresting */
	अगर (idx == 0)
		dprपूर्णांकk(DEBUG_VERBOSE, "%s fifo count : %d [last %d]\n",
			__func__, fअगरo_count, is_last);

	अगर (is_last) अणु
		अगर (idx == 0) अणु
			s3c2410_udc_set_ep0_de_out(base_addr);
			ep->dev->ep0state = EP0_IDLE;
		पूर्ण अन्यथा अणु
			udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
			ep_csr = udc_पढ़ो(S3C2410_UDC_OUT_CSR1_REG);
			udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
			udc_ग_लिखो(ep_csr & ~S3C2410_UDC_OCSR1_PKTRDY,
					S3C2410_UDC_OUT_CSR1_REG);
		पूर्ण

		s3c2410_udc_करोne(ep, req, 0);
	पूर्ण अन्यथा अणु
		अगर (idx == 0) अणु
			s3c2410_udc_clear_ep0_opr(base_addr);
		पूर्ण अन्यथा अणु
			udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
			ep_csr = udc_पढ़ो(S3C2410_UDC_OUT_CSR1_REG);
			udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
			udc_ग_लिखो(ep_csr & ~S3C2410_UDC_OCSR1_PKTRDY,
					S3C2410_UDC_OUT_CSR1_REG);
		पूर्ण
	पूर्ण

	वापस is_last;
पूर्ण

अटल पूर्णांक s3c2410_udc_पढ़ो_fअगरo_crq(काष्ठा usb_ctrlrequest *crq)
अणु
	अचिन्हित अक्षर *outbuf = (अचिन्हित अक्षर *)crq;
	पूर्णांक bytes_पढ़ो = 0;

	udc_ग_लिखो(0, S3C2410_UDC_INDEX_REG);

	bytes_पढ़ो = s3c2410_udc_fअगरo_count_out();

	dprपूर्णांकk(DEBUG_NORMAL, "%s: fifo_count=%d\n", __func__, bytes_पढ़ो);

	अगर (bytes_पढ़ो > माप(काष्ठा usb_ctrlrequest))
		bytes_पढ़ो = माप(काष्ठा usb_ctrlrequest);

	पढ़ोsb(S3C2410_UDC_EP0_FIFO_REG + base_addr, outbuf, bytes_पढ़ो);

	dprपूर्णांकk(DEBUG_VERBOSE, "%s: len=%d %02x:%02x {%x,%x,%x}\n", __func__,
		bytes_पढ़ो, crq->bRequest, crq->bRequestType,
		crq->wValue, crq->wIndex, crq->wLength);

	वापस bytes_पढ़ो;
पूर्ण

अटल पूर्णांक s3c2410_udc_get_status(काष्ठा s3c2410_udc *dev,
		काष्ठा usb_ctrlrequest *crq)
अणु
	u16 status = 0;
	u8 ep_num = crq->wIndex & 0x7F;
	u8 is_in = crq->wIndex & USB_सूची_IN;

	चयन (crq->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_INTERFACE:
		अवरोध;

	हाल USB_RECIP_DEVICE:
		status = dev->devstatus;
		अवरोध;

	हाल USB_RECIP_ENDPOINT:
		अगर (ep_num > 4 || crq->wLength > 2)
			वापस 1;

		अगर (ep_num == 0) अणु
			udc_ग_लिखो(0, S3C2410_UDC_INDEX_REG);
			status = udc_पढ़ो(S3C2410_UDC_IN_CSR1_REG);
			status = status & S3C2410_UDC_EP0_CSR_SENDSTL;
		पूर्ण अन्यथा अणु
			udc_ग_लिखो(ep_num, S3C2410_UDC_INDEX_REG);
			अगर (is_in) अणु
				status = udc_पढ़ो(S3C2410_UDC_IN_CSR1_REG);
				status = status & S3C2410_UDC_ICSR1_SENDSTL;
			पूर्ण अन्यथा अणु
				status = udc_पढ़ो(S3C2410_UDC_OUT_CSR1_REG);
				status = status & S3C2410_UDC_OCSR1_SENDSTL;
			पूर्ण
		पूर्ण

		status = status ? 1 : 0;
		अवरोध;

	शेष:
		वापस 1;
	पूर्ण

	/* Seems to be needed to get it working. ouch :( */
	udelay(5);
	udc_ग_लिखो(status & 0xFF, S3C2410_UDC_EP0_FIFO_REG);
	udc_ग_लिखो(status >> 8, S3C2410_UDC_EP0_FIFO_REG);
	s3c2410_udc_set_ep0_de_in(base_addr);

	वापस 0;
पूर्ण
/*------------------------- usb state machine -------------------------------*/
अटल पूर्णांक s3c2410_udc_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value);

अटल व्योम s3c2410_udc_handle_ep0_idle(काष्ठा s3c2410_udc *dev,
					काष्ठा s3c2410_ep *ep,
					काष्ठा usb_ctrlrequest *crq,
					u32 ep0csr)
अणु
	पूर्णांक len, ret, पंचांगp;

	/* start control request? */
	अगर (!(ep0csr & S3C2410_UDC_EP0_CSR_OPKRDY))
		वापस;

	s3c2410_udc_nuke(dev, ep, -EPROTO);

	len = s3c2410_udc_पढ़ो_fअगरo_crq(crq);
	अगर (len != माप(*crq)) अणु
		dprपूर्णांकk(DEBUG_NORMAL, "setup begin: fifo READ ERROR"
			" wanted %d bytes got %d. Stalling out...\n",
			माप(*crq), len);
		s3c2410_udc_set_ep0_ss(base_addr);
		वापस;
	पूर्ण

	dprपूर्णांकk(DEBUG_NORMAL, "bRequest = %d bRequestType %d wLength = %d\n",
		crq->bRequest, crq->bRequestType, crq->wLength);

	/* cope with स्वतःmagic क्रम some standard requests. */
	dev->req_std = (crq->bRequestType & USB_TYPE_MASK)
		== USB_TYPE_STANDARD;
	dev->req_config = 0;
	dev->req_pending = 1;

	चयन (crq->bRequest) अणु
	हाल USB_REQ_SET_CONFIGURATION:
		dprपूर्णांकk(DEBUG_NORMAL, "USB_REQ_SET_CONFIGURATION ...\n");

		अगर (crq->bRequestType == USB_RECIP_DEVICE) अणु
			dev->req_config = 1;
			s3c2410_udc_set_ep0_de_out(base_addr);
		पूर्ण
		अवरोध;

	हाल USB_REQ_SET_INTERFACE:
		dprपूर्णांकk(DEBUG_NORMAL, "USB_REQ_SET_INTERFACE ...\n");

		अगर (crq->bRequestType == USB_RECIP_INTERFACE) अणु
			dev->req_config = 1;
			s3c2410_udc_set_ep0_de_out(base_addr);
		पूर्ण
		अवरोध;

	हाल USB_REQ_SET_ADDRESS:
		dprपूर्णांकk(DEBUG_NORMAL, "USB_REQ_SET_ADDRESS ...\n");

		अगर (crq->bRequestType == USB_RECIP_DEVICE) अणु
			पंचांगp = crq->wValue & 0x7F;
			dev->address = पंचांगp;
			udc_ग_लिखो((पंचांगp | S3C2410_UDC_FUNCADDR_UPDATE),
					S3C2410_UDC_FUNC_ADDR_REG);
			s3c2410_udc_set_ep0_de_out(base_addr);
			वापस;
		पूर्ण
		अवरोध;

	हाल USB_REQ_GET_STATUS:
		dprपूर्णांकk(DEBUG_NORMAL, "USB_REQ_GET_STATUS ...\n");
		s3c2410_udc_clear_ep0_opr(base_addr);

		अगर (dev->req_std) अणु
			अगर (!s3c2410_udc_get_status(dev, crq))
				वापस;
		पूर्ण
		अवरोध;

	हाल USB_REQ_CLEAR_FEATURE:
		s3c2410_udc_clear_ep0_opr(base_addr);

		अगर (crq->bRequestType != USB_RECIP_ENDPOINT)
			अवरोध;

		अगर (crq->wValue != USB_ENDPOINT_HALT || crq->wLength != 0)
			अवरोध;

		s3c2410_udc_set_halt(&dev->ep[crq->wIndex & 0x7f].ep, 0);
		s3c2410_udc_set_ep0_de_out(base_addr);
		वापस;

	हाल USB_REQ_SET_FEATURE:
		s3c2410_udc_clear_ep0_opr(base_addr);

		अगर (crq->bRequestType != USB_RECIP_ENDPOINT)
			अवरोध;

		अगर (crq->wValue != USB_ENDPOINT_HALT || crq->wLength != 0)
			अवरोध;

		s3c2410_udc_set_halt(&dev->ep[crq->wIndex & 0x7f].ep, 1);
		s3c2410_udc_set_ep0_de_out(base_addr);
		वापस;

	शेष:
		s3c2410_udc_clear_ep0_opr(base_addr);
		अवरोध;
	पूर्ण

	अगर (crq->bRequestType & USB_सूची_IN)
		dev->ep0state = EP0_IN_DATA_PHASE;
	अन्यथा
		dev->ep0state = EP0_OUT_DATA_PHASE;

	अगर (!dev->driver)
		वापस;

	/* deliver the request to the gadget driver */
	ret = dev->driver->setup(&dev->gadget, crq);
	अगर (ret < 0) अणु
		अगर (dev->req_config) अणु
			dprपूर्णांकk(DEBUG_NORMAL, "config change %02x fail %d?\n",
				crq->bRequest, ret);
			वापस;
		पूर्ण

		अगर (ret == -EOPNOTSUPP)
			dprपूर्णांकk(DEBUG_NORMAL, "Operation not supported\n");
		अन्यथा
			dprपूर्णांकk(DEBUG_NORMAL,
				"dev->driver->setup failed. (%d)\n", ret);

		udelay(5);
		s3c2410_udc_set_ep0_ss(base_addr);
		s3c2410_udc_set_ep0_de_out(base_addr);
		dev->ep0state = EP0_IDLE;
		/* deferred i/o == no response yet */
	पूर्ण अन्यथा अगर (dev->req_pending) अणु
		dprपूर्णांकk(DEBUG_VERBOSE, "dev->req_pending... what now?\n");
		dev->req_pending = 0;
	पूर्ण

	dprपूर्णांकk(DEBUG_VERBOSE, "ep0state %s\n", ep0states[dev->ep0state]);
पूर्ण

अटल व्योम s3c2410_udc_handle_ep0(काष्ठा s3c2410_udc *dev)
अणु
	u32			ep0csr;
	काष्ठा s3c2410_ep	*ep = &dev->ep[0];
	काष्ठा s3c2410_request	*req;
	काष्ठा usb_ctrlrequest	crq;

	अगर (list_empty(&ep->queue))
		req = शून्य;
	अन्यथा
		req = list_entry(ep->queue.next, काष्ठा s3c2410_request, queue);

	/* We make the assumption that S3C2410_UDC_IN_CSR1_REG equal to
	 * S3C2410_UDC_EP0_CSR_REG when index is zero */

	udc_ग_लिखो(0, S3C2410_UDC_INDEX_REG);
	ep0csr = udc_पढ़ो(S3C2410_UDC_IN_CSR1_REG);

	dprपूर्णांकk(DEBUG_NORMAL, "ep0csr %x ep0state %s\n",
		ep0csr, ep0states[dev->ep0state]);

	/* clear stall status */
	अगर (ep0csr & S3C2410_UDC_EP0_CSR_SENTSTL) अणु
		s3c2410_udc_nuke(dev, ep, -EPIPE);
		dprपूर्णांकk(DEBUG_NORMAL, "... clear SENT_STALL ...\n");
		s3c2410_udc_clear_ep0_sst(base_addr);
		dev->ep0state = EP0_IDLE;
		वापस;
	पूर्ण

	/* clear setup end */
	अगर (ep0csr & S3C2410_UDC_EP0_CSR_SE) अणु
		dprपूर्णांकk(DEBUG_NORMAL, "... serviced SETUP_END ...\n");
		s3c2410_udc_nuke(dev, ep, 0);
		s3c2410_udc_clear_ep0_se(base_addr);
		dev->ep0state = EP0_IDLE;
	पूर्ण

	चयन (dev->ep0state) अणु
	हाल EP0_IDLE:
		s3c2410_udc_handle_ep0_idle(dev, ep, &crq, ep0csr);
		अवरोध;

	हाल EP0_IN_DATA_PHASE:			/* GET_DESCRIPTOR etc */
		dprपूर्णांकk(DEBUG_NORMAL, "EP0_IN_DATA_PHASE ... what now?\n");
		अगर (!(ep0csr & S3C2410_UDC_EP0_CSR_IPKRDY) && req)
			s3c2410_udc_ग_लिखो_fअगरo(ep, req);
		अवरोध;

	हाल EP0_OUT_DATA_PHASE:		/* SET_DESCRIPTOR etc */
		dprपूर्णांकk(DEBUG_NORMAL, "EP0_OUT_DATA_PHASE ... what now?\n");
		अगर ((ep0csr & S3C2410_UDC_EP0_CSR_OPKRDY) && req)
			s3c2410_udc_पढ़ो_fअगरo(ep, req);
		अवरोध;

	हाल EP0_END_XFER:
		dprपूर्णांकk(DEBUG_NORMAL, "EP0_END_XFER ... what now?\n");
		dev->ep0state = EP0_IDLE;
		अवरोध;

	हाल EP0_STALL:
		dprपूर्णांकk(DEBUG_NORMAL, "EP0_STALL ... what now?\n");
		dev->ep0state = EP0_IDLE;
		अवरोध;
	पूर्ण
पूर्ण

/*
 *	handle_ep - Manage I/O endpoपूर्णांकs
 */

अटल व्योम s3c2410_udc_handle_ep(काष्ठा s3c2410_ep *ep)
अणु
	काष्ठा s3c2410_request	*req;
	पूर्णांक			is_in = ep->bEndpoपूर्णांकAddress & USB_सूची_IN;
	u32			ep_csr1;
	u32			idx;

	अगर (likely(!list_empty(&ep->queue)))
		req = list_entry(ep->queue.next,
				काष्ठा s3c2410_request, queue);
	अन्यथा
		req = शून्य;

	idx = ep->bEndpoपूर्णांकAddress & 0x7F;

	अगर (is_in) अणु
		udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
		ep_csr1 = udc_पढ़ो(S3C2410_UDC_IN_CSR1_REG);
		dprपूर्णांकk(DEBUG_VERBOSE, "ep%01d write csr:%02x %d\n",
			idx, ep_csr1, req ? 1 : 0);

		अगर (ep_csr1 & S3C2410_UDC_ICSR1_SENTSTL) अणु
			dprपूर्णांकk(DEBUG_VERBOSE, "st\n");
			udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
			udc_ग_लिखो(ep_csr1 & ~S3C2410_UDC_ICSR1_SENTSTL,
					S3C2410_UDC_IN_CSR1_REG);
			वापस;
		पूर्ण

		अगर (!(ep_csr1 & S3C2410_UDC_ICSR1_PKTRDY) && req)
			s3c2410_udc_ग_लिखो_fअगरo(ep, req);
	पूर्ण अन्यथा अणु
		udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
		ep_csr1 = udc_पढ़ो(S3C2410_UDC_OUT_CSR1_REG);
		dprपूर्णांकk(DEBUG_VERBOSE, "ep%01d rd csr:%02x\n", idx, ep_csr1);

		अगर (ep_csr1 & S3C2410_UDC_OCSR1_SENTSTL) अणु
			udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
			udc_ग_लिखो(ep_csr1 & ~S3C2410_UDC_OCSR1_SENTSTL,
					S3C2410_UDC_OUT_CSR1_REG);
			वापस;
		पूर्ण

		अगर ((ep_csr1 & S3C2410_UDC_OCSR1_PKTRDY) && req)
			s3c2410_udc_पढ़ो_fअगरo(ep, req);
	पूर्ण
पूर्ण

/*
 *	s3c2410_udc_irq - पूर्णांकerrupt handler
 */
अटल irqवापस_t s3c2410_udc_irq(पूर्णांक dummy, व्योम *_dev)
अणु
	काष्ठा s3c2410_udc *dev = _dev;
	पूर्णांक usb_status;
	पूर्णांक usbd_status;
	पूर्णांक pwr_reg;
	पूर्णांक ep0csr;
	पूर्णांक i;
	u32 idx, idx2;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);

	/* Driver connected ? */
	अगर (!dev->driver) अणु
		/* Clear पूर्णांकerrupts */
		udc_ग_लिखो(udc_पढ़ो(S3C2410_UDC_USB_INT_REG),
				S3C2410_UDC_USB_INT_REG);
		udc_ग_लिखो(udc_पढ़ो(S3C2410_UDC_EP_INT_REG),
				S3C2410_UDC_EP_INT_REG);
	पूर्ण

	/* Save index */
	idx = udc_पढ़ो(S3C2410_UDC_INDEX_REG);

	/* Read status रेजिस्टरs */
	usb_status = udc_पढ़ो(S3C2410_UDC_USB_INT_REG);
	usbd_status = udc_पढ़ो(S3C2410_UDC_EP_INT_REG);
	pwr_reg = udc_पढ़ो(S3C2410_UDC_PWR_REG);

	udc_ग_लिखोb(base_addr, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	ep0csr = udc_पढ़ो(S3C2410_UDC_IN_CSR1_REG);

	dprपूर्णांकk(DEBUG_NORMAL, "usbs=%02x, usbds=%02x, pwr=%02x ep0csr=%02x\n",
		usb_status, usbd_status, pwr_reg, ep0csr);

	/*
	 * Now, handle पूर्णांकerrupts. There's two types :
	 * - Reset, Resume, Suspend coming -> usb_पूर्णांक_reg
	 * - EP -> ep_पूर्णांक_reg
	 */

	/* RESET */
	अगर (usb_status & S3C2410_UDC_USBINT_RESET) अणु
		/* two kind of reset :
		 * - reset start -> pwr reg = 8
		 * - reset end   -> pwr reg = 0
		 **/
		dprपूर्णांकk(DEBUG_NORMAL, "USB reset csr %x pwr %x\n",
			ep0csr, pwr_reg);

		dev->gadget.speed = USB_SPEED_UNKNOWN;
		udc_ग_लिखो(0x00, S3C2410_UDC_INDEX_REG);
		udc_ग_लिखो((dev->ep[0].ep.maxpacket & 0x7ff) >> 3,
				S3C2410_UDC_MAXP_REG);
		dev->address = 0;

		dev->ep0state = EP0_IDLE;
		dev->gadget.speed = USB_SPEED_FULL;

		/* clear पूर्णांकerrupt */
		udc_ग_लिखो(S3C2410_UDC_USBINT_RESET,
				S3C2410_UDC_USB_INT_REG);

		udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	/* RESUME */
	अगर (usb_status & S3C2410_UDC_USBINT_RESUME) अणु
		dprपूर्णांकk(DEBUG_NORMAL, "USB resume\n");

		/* clear पूर्णांकerrupt */
		udc_ग_लिखो(S3C2410_UDC_USBINT_RESUME,
				S3C2410_UDC_USB_INT_REG);

		अगर (dev->gadget.speed != USB_SPEED_UNKNOWN
				&& dev->driver
				&& dev->driver->resume)
			dev->driver->resume(&dev->gadget);
	पूर्ण

	/* SUSPEND */
	अगर (usb_status & S3C2410_UDC_USBINT_SUSPEND) अणु
		dprपूर्णांकk(DEBUG_NORMAL, "USB suspend\n");

		/* clear पूर्णांकerrupt */
		udc_ग_लिखो(S3C2410_UDC_USBINT_SUSPEND,
				S3C2410_UDC_USB_INT_REG);

		अगर (dev->gadget.speed != USB_SPEED_UNKNOWN
				&& dev->driver
				&& dev->driver->suspend)
			dev->driver->suspend(&dev->gadget);

		dev->ep0state = EP0_IDLE;
	पूर्ण

	/* EP */
	/* control traffic */
	/* check on ep0csr != 0 is not a good idea as clearing in_pkt_पढ़ोy
	 * generate an पूर्णांकerrupt
	 */
	अगर (usbd_status & S3C2410_UDC_INT_EP0) अणु
		dprपूर्णांकk(DEBUG_VERBOSE, "USB ep0 irq\n");
		/* Clear the पूर्णांकerrupt bit by setting it to 1 */
		udc_ग_लिखो(S3C2410_UDC_INT_EP0, S3C2410_UDC_EP_INT_REG);
		s3c2410_udc_handle_ep0(dev);
	पूर्ण

	/* endpoपूर्णांक data transfers */
	क्रम (i = 1; i < S3C2410_ENDPOINTS; i++) अणु
		u32 पंचांगp = 1 << i;
		अगर (usbd_status & पंचांगp) अणु
			dprपूर्णांकk(DEBUG_VERBOSE, "USB ep%d irq\n", i);

			/* Clear the पूर्णांकerrupt bit by setting it to 1 */
			udc_ग_लिखो(पंचांगp, S3C2410_UDC_EP_INT_REG);
			s3c2410_udc_handle_ep(&dev->ep[i]);
		पूर्ण
	पूर्ण

	/* what अन्यथा causes this पूर्णांकerrupt? a receive! who is it? */
	अगर (!usb_status && !usbd_status && !pwr_reg && !ep0csr) अणु
		क्रम (i = 1; i < S3C2410_ENDPOINTS; i++) अणु
			idx2 = udc_पढ़ो(S3C2410_UDC_INDEX_REG);
			udc_ग_लिखो(i, S3C2410_UDC_INDEX_REG);

			अगर (udc_पढ़ो(S3C2410_UDC_OUT_CSR1_REG) & 0x1)
				s3c2410_udc_handle_ep(&dev->ep[i]);

			/* restore index */
			udc_ग_लिखो(idx2, S3C2410_UDC_INDEX_REG);
		पूर्ण
	पूर्ण

	dprपूर्णांकk(DEBUG_VERBOSE, "irq: %d s3c2410_udc_done.\n", irq_usbd);

	/* Restore old index */
	udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण
/*------------------------- s3c2410_ep_ops ----------------------------------*/

अटल अंतरभूत काष्ठा s3c2410_ep *to_s3c2410_ep(काष्ठा usb_ep *ep)
अणु
	वापस container_of(ep, काष्ठा s3c2410_ep, ep);
पूर्ण

अटल अंतरभूत काष्ठा s3c2410_udc *to_s3c2410_udc(काष्ठा usb_gadget *gadget)
अणु
	वापस container_of(gadget, काष्ठा s3c2410_udc, gadget);
पूर्ण

अटल अंतरभूत काष्ठा s3c2410_request *to_s3c2410_req(काष्ठा usb_request *req)
अणु
	वापस container_of(req, काष्ठा s3c2410_request, req);
पूर्ण

/*
 *	s3c2410_udc_ep_enable
 */
अटल पूर्णांक s3c2410_udc_ep_enable(काष्ठा usb_ep *_ep,
				 स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा s3c2410_udc	*dev;
	काष्ठा s3c2410_ep	*ep;
	u32			max, पंचांगp;
	अचिन्हित दीर्घ		flags;
	u32			csr1, csr2;
	u32			पूर्णांक_en_reg;

	ep = to_s3c2410_ep(_ep);

	अगर (!_ep || !desc
			|| _ep->name == ep0name
			|| desc->bDescriptorType != USB_DT_ENDPOINT)
		वापस -EINVAL;

	dev = ep->dev;
	अगर (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	max = usb_endpoपूर्णांक_maxp(desc);

	local_irq_save(flags);
	_ep->maxpacket = max;
	ep->ep.desc = desc;
	ep->halted = 0;
	ep->bEndpoपूर्णांकAddress = desc->bEndpoपूर्णांकAddress;

	/* set max packet */
	udc_ग_लिखो(ep->num, S3C2410_UDC_INDEX_REG);
	udc_ग_लिखो(max >> 3, S3C2410_UDC_MAXP_REG);

	/* set type, direction, address; reset fअगरo counters */
	अगर (desc->bEndpoपूर्णांकAddress & USB_सूची_IN) अणु
		csr1 = S3C2410_UDC_ICSR1_FFLUSH|S3C2410_UDC_ICSR1_CLRDT;
		csr2 = S3C2410_UDC_ICSR2_MODEIN|S3C2410_UDC_ICSR2_DMAIEN;

		udc_ग_लिखो(ep->num, S3C2410_UDC_INDEX_REG);
		udc_ग_लिखो(csr1, S3C2410_UDC_IN_CSR1_REG);
		udc_ग_लिखो(ep->num, S3C2410_UDC_INDEX_REG);
		udc_ग_लिखो(csr2, S3C2410_UDC_IN_CSR2_REG);
	पूर्ण अन्यथा अणु
		/* करोn't flush in fअगरo or it will cause endpoपूर्णांक पूर्णांकerrupt */
		csr1 = S3C2410_UDC_ICSR1_CLRDT;
		csr2 = S3C2410_UDC_ICSR2_DMAIEN;

		udc_ग_लिखो(ep->num, S3C2410_UDC_INDEX_REG);
		udc_ग_लिखो(csr1, S3C2410_UDC_IN_CSR1_REG);
		udc_ग_लिखो(ep->num, S3C2410_UDC_INDEX_REG);
		udc_ग_लिखो(csr2, S3C2410_UDC_IN_CSR2_REG);

		csr1 = S3C2410_UDC_OCSR1_FFLUSH | S3C2410_UDC_OCSR1_CLRDT;
		csr2 = S3C2410_UDC_OCSR2_DMAIEN;

		udc_ग_लिखो(ep->num, S3C2410_UDC_INDEX_REG);
		udc_ग_लिखो(csr1, S3C2410_UDC_OUT_CSR1_REG);
		udc_ग_लिखो(ep->num, S3C2410_UDC_INDEX_REG);
		udc_ग_लिखो(csr2, S3C2410_UDC_OUT_CSR2_REG);
	पूर्ण

	/* enable irqs */
	पूर्णांक_en_reg = udc_पढ़ो(S3C2410_UDC_EP_INT_EN_REG);
	udc_ग_लिखो(पूर्णांक_en_reg | (1 << ep->num), S3C2410_UDC_EP_INT_EN_REG);

	/* prपूर्णांक some debug message */
	पंचांगp = desc->bEndpoपूर्णांकAddress;
	dprपूर्णांकk(DEBUG_NORMAL, "enable %s(%d) ep%x%s-blk max %02x\n",
		 _ep->name, ep->num, पंचांगp,
		 desc->bEndpoपूर्णांकAddress & USB_सूची_IN ? "in" : "out", max);

	local_irq_restore(flags);
	s3c2410_udc_set_halt(_ep, 0);

	वापस 0;
पूर्ण

/*
 * s3c2410_udc_ep_disable
 */
अटल पूर्णांक s3c2410_udc_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा s3c2410_ep *ep = to_s3c2410_ep(_ep);
	अचिन्हित दीर्घ flags;
	u32 पूर्णांक_en_reg;

	अगर (!_ep || !ep->ep.desc) अणु
		dprपूर्णांकk(DEBUG_NORMAL, "%s not enabled\n",
			_ep ? ep->ep.name : शून्य);
		वापस -EINVAL;
	पूर्ण

	local_irq_save(flags);

	dprपूर्णांकk(DEBUG_NORMAL, "ep_disable: %s\n", _ep->name);

	ep->ep.desc = शून्य;
	ep->halted = 1;

	s3c2410_udc_nuke(ep->dev, ep, -ESHUTDOWN);

	/* disable irqs */
	पूर्णांक_en_reg = udc_पढ़ो(S3C2410_UDC_EP_INT_EN_REG);
	udc_ग_लिखो(पूर्णांक_en_reg & ~(1<<ep->num), S3C2410_UDC_EP_INT_EN_REG);

	local_irq_restore(flags);

	dprपूर्णांकk(DEBUG_NORMAL, "%s disabled\n", _ep->name);

	वापस 0;
पूर्ण

/*
 * s3c2410_udc_alloc_request
 */
अटल काष्ठा usb_request *
s3c2410_udc_alloc_request(काष्ठा usb_ep *_ep, gfp_t mem_flags)
अणु
	काष्ठा s3c2410_request *req;

	dprपूर्णांकk(DEBUG_VERBOSE, "%s(%p,%d)\n", __func__, _ep, mem_flags);

	अगर (!_ep)
		वापस शून्य;

	req = kzalloc(माप(काष्ठा s3c2410_request), mem_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);
	वापस &req->req;
पूर्ण

/*
 * s3c2410_udc_मुक्त_request
 */
अटल व्योम
s3c2410_udc_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा s3c2410_ep	*ep = to_s3c2410_ep(_ep);
	काष्ठा s3c2410_request	*req = to_s3c2410_req(_req);

	dprपूर्णांकk(DEBUG_VERBOSE, "%s(%p,%p)\n", __func__, _ep, _req);

	अगर (!ep || !_req || (!ep->ep.desc && _ep->name != ep0name))
		वापस;

	WARN_ON(!list_empty(&req->queue));
	kमुक्त(req);
पूर्ण

/*
 *	s3c2410_udc_queue
 */
अटल पूर्णांक s3c2410_udc_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
		gfp_t gfp_flags)
अणु
	काष्ठा s3c2410_request	*req = to_s3c2410_req(_req);
	काष्ठा s3c2410_ep	*ep = to_s3c2410_ep(_ep);
	काष्ठा s3c2410_udc	*dev;
	u32			ep_csr = 0;
	पूर्णांक			fअगरo_count = 0;
	अचिन्हित दीर्घ		flags;

	अगर (unlikely(!_ep || (!ep->ep.desc && ep->ep.name != ep0name))) अणु
		dprपूर्णांकk(DEBUG_NORMAL, "%s: invalid args\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dev = ep->dev;
	अगर (unlikely(!dev->driver
			|| dev->gadget.speed == USB_SPEED_UNKNOWN)) अणु
		वापस -ESHUTDOWN;
	पूर्ण

	local_irq_save(flags);

	अगर (unlikely(!_req || !_req->complete
			|| !_req->buf || !list_empty(&req->queue))) अणु
		अगर (!_req)
			dprपूर्णांकk(DEBUG_NORMAL, "%s: 1 X X X\n", __func__);
		अन्यथा अणु
			dprपूर्णांकk(DEBUG_NORMAL, "%s: 0 %01d %01d %01d\n",
				__func__, !_req->complete, !_req->buf,
				!list_empty(&req->queue));
		पूर्ण

		local_irq_restore(flags);
		वापस -EINVAL;
	पूर्ण

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	dprपूर्णांकk(DEBUG_VERBOSE, "%s: ep%x len %d\n",
		 __func__, ep->bEndpoपूर्णांकAddress, _req->length);

	अगर (ep->bEndpoपूर्णांकAddress) अणु
		udc_ग_लिखो(ep->bEndpoपूर्णांकAddress & 0x7F, S3C2410_UDC_INDEX_REG);

		ep_csr = udc_पढ़ो((ep->bEndpoपूर्णांकAddress & USB_सूची_IN)
				? S3C2410_UDC_IN_CSR1_REG
				: S3C2410_UDC_OUT_CSR1_REG);
		fअगरo_count = s3c2410_udc_fअगरo_count_out();
	पूर्ण अन्यथा अणु
		udc_ग_लिखो(0, S3C2410_UDC_INDEX_REG);
		ep_csr = udc_पढ़ो(S3C2410_UDC_IN_CSR1_REG);
		fअगरo_count = s3c2410_udc_fअगरo_count_out();
	पूर्ण

	/* kickstart this i/o queue? */
	अगर (list_empty(&ep->queue) && !ep->halted) अणु
		अगर (ep->bEndpoपूर्णांकAddress == 0 /* ep0 */) अणु
			चयन (dev->ep0state) अणु
			हाल EP0_IN_DATA_PHASE:
				अगर (!(ep_csr&S3C2410_UDC_EP0_CSR_IPKRDY)
						&& s3c2410_udc_ग_लिखो_fअगरo(ep,
							req)) अणु
					dev->ep0state = EP0_IDLE;
					req = शून्य;
				पूर्ण
				अवरोध;

			हाल EP0_OUT_DATA_PHASE:
				अगर ((!_req->length)
					|| ((ep_csr & S3C2410_UDC_OCSR1_PKTRDY)
						&& s3c2410_udc_पढ़ो_fअगरo(ep,
							req))) अणु
					dev->ep0state = EP0_IDLE;
					req = शून्य;
				पूर्ण
				अवरोध;

			शेष:
				local_irq_restore(flags);
				वापस -EL2HLT;
			पूर्ण
		पूर्ण अन्यथा अगर ((ep->bEndpoपूर्णांकAddress & USB_सूची_IN) != 0
				&& (!(ep_csr&S3C2410_UDC_OCSR1_PKTRDY))
				&& s3c2410_udc_ग_लिखो_fअगरo(ep, req)) अणु
			req = शून्य;
		पूर्ण अन्यथा अगर ((ep_csr & S3C2410_UDC_OCSR1_PKTRDY)
				&& fअगरo_count
				&& s3c2410_udc_पढ़ो_fअगरo(ep, req)) अणु
			req = शून्य;
		पूर्ण
	पूर्ण

	/* pio or dma irq handler advances the queue. */
	अगर (likely(req))
		list_add_tail(&req->queue, &ep->queue);

	local_irq_restore(flags);

	dprपूर्णांकk(DEBUG_VERBOSE, "%s ok\n", __func__);
	वापस 0;
पूर्ण

/*
 *	s3c2410_udc_dequeue
 */
अटल पूर्णांक s3c2410_udc_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा s3c2410_ep	*ep = to_s3c2410_ep(_ep);
	पूर्णांक			retval = -EINVAL;
	अचिन्हित दीर्घ		flags;
	काष्ठा s3c2410_request	*req = शून्य;

	dprपूर्णांकk(DEBUG_VERBOSE, "%s(%p,%p)\n", __func__, _ep, _req);

	अगर (!the_controller->driver)
		वापस -ESHUTDOWN;

	अगर (!_ep || !_req)
		वापस retval;

	local_irq_save(flags);

	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->req == _req) अणु
			list_del_init(&req->queue);
			_req->status = -ECONNRESET;
			retval = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (retval == 0) अणु
		dprपूर्णांकk(DEBUG_VERBOSE,
			"dequeued req %p from %s, len %d buf %p\n",
			req, _ep->name, _req->length, _req->buf);

		s3c2410_udc_करोne(ep, req, -ECONNRESET);
	पूर्ण

	local_irq_restore(flags);
	वापस retval;
पूर्ण

/*
 * s3c2410_udc_set_halt
 */
अटल पूर्णांक s3c2410_udc_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा s3c2410_ep	*ep = to_s3c2410_ep(_ep);
	u32			ep_csr = 0;
	अचिन्हित दीर्घ		flags;
	u32			idx;

	अगर (unlikely(!_ep || (!ep->ep.desc && ep->ep.name != ep0name))) अणु
		dprपूर्णांकk(DEBUG_NORMAL, "%s: inval 2\n", __func__);
		वापस -EINVAL;
	पूर्ण

	local_irq_save(flags);

	idx = ep->bEndpoपूर्णांकAddress & 0x7F;

	अगर (idx == 0) अणु
		s3c2410_udc_set_ep0_ss(base_addr);
		s3c2410_udc_set_ep0_de_out(base_addr);
	पूर्ण अन्यथा अणु
		udc_ग_लिखो(idx, S3C2410_UDC_INDEX_REG);
		ep_csr = udc_पढ़ो((ep->bEndpoपूर्णांकAddress & USB_सूची_IN)
				? S3C2410_UDC_IN_CSR1_REG
				: S3C2410_UDC_OUT_CSR1_REG);

		अगर ((ep->bEndpoपूर्णांकAddress & USB_सूची_IN) != 0) अणु
			अगर (value)
				udc_ग_लिखो(ep_csr | S3C2410_UDC_ICSR1_SENDSTL,
					S3C2410_UDC_IN_CSR1_REG);
			अन्यथा अणु
				ep_csr &= ~S3C2410_UDC_ICSR1_SENDSTL;
				udc_ग_लिखो(ep_csr, S3C2410_UDC_IN_CSR1_REG);
				ep_csr |= S3C2410_UDC_ICSR1_CLRDT;
				udc_ग_लिखो(ep_csr, S3C2410_UDC_IN_CSR1_REG);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (value)
				udc_ग_लिखो(ep_csr | S3C2410_UDC_OCSR1_SENDSTL,
					S3C2410_UDC_OUT_CSR1_REG);
			अन्यथा अणु
				ep_csr &= ~S3C2410_UDC_OCSR1_SENDSTL;
				udc_ग_लिखो(ep_csr, S3C2410_UDC_OUT_CSR1_REG);
				ep_csr |= S3C2410_UDC_OCSR1_CLRDT;
				udc_ग_लिखो(ep_csr, S3C2410_UDC_OUT_CSR1_REG);
			पूर्ण
		पूर्ण
	पूर्ण

	ep->halted = value ? 1 : 0;
	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops s3c2410_ep_ops = अणु
	.enable		= s3c2410_udc_ep_enable,
	.disable	= s3c2410_udc_ep_disable,

	.alloc_request	= s3c2410_udc_alloc_request,
	.मुक्त_request	= s3c2410_udc_मुक्त_request,

	.queue		= s3c2410_udc_queue,
	.dequeue	= s3c2410_udc_dequeue,

	.set_halt	= s3c2410_udc_set_halt,
पूर्ण;

/*------------------------- usb_gadget_ops ----------------------------------*/

/*
 *	s3c2410_udc_get_frame
 */
अटल पूर्णांक s3c2410_udc_get_frame(काष्ठा usb_gadget *_gadget)
अणु
	पूर्णांक पंचांगp;

	dprपूर्णांकk(DEBUG_VERBOSE, "%s()\n", __func__);

	पंचांगp = udc_पढ़ो(S3C2410_UDC_FRAME_NUM2_REG) << 8;
	पंचांगp |= udc_पढ़ो(S3C2410_UDC_FRAME_NUM1_REG);
	वापस पंचांगp;
पूर्ण

/*
 *	s3c2410_udc_wakeup
 */
अटल पूर्णांक s3c2410_udc_wakeup(काष्ठा usb_gadget *_gadget)
अणु
	dprपूर्णांकk(DEBUG_NORMAL, "%s()\n", __func__);
	वापस 0;
पूर्ण

/*
 *	s3c2410_udc_set_selfघातered
 */
अटल पूर्णांक s3c2410_udc_set_selfघातered(काष्ठा usb_gadget *gadget, पूर्णांक value)
अणु
	काष्ठा s3c2410_udc *udc = to_s3c2410_udc(gadget);

	dprपूर्णांकk(DEBUG_NORMAL, "%s()\n", __func__);

	gadget->is_selfघातered = (value != 0);
	अगर (value)
		udc->devstatus |= (1 << USB_DEVICE_SELF_POWERED);
	अन्यथा
		udc->devstatus &= ~(1 << USB_DEVICE_SELF_POWERED);

	वापस 0;
पूर्ण

अटल व्योम s3c2410_udc_disable(काष्ठा s3c2410_udc *dev);
अटल व्योम s3c2410_udc_enable(काष्ठा s3c2410_udc *dev);

अटल पूर्णांक s3c2410_udc_set_pullup(काष्ठा s3c2410_udc *udc, पूर्णांक is_on)
अणु
	dprपूर्णांकk(DEBUG_NORMAL, "%s()\n", __func__);

	अगर (udc_info && (udc_info->udc_command ||
		gpio_is_valid(udc_info->pullup_pin))) अणु

		अगर (is_on)
			s3c2410_udc_enable(udc);
		अन्यथा अणु
			अगर (udc->gadget.speed != USB_SPEED_UNKNOWN) अणु
				अगर (udc->driver && udc->driver->disconnect)
					udc->driver->disconnect(&udc->gadget);

			पूर्ण
			s3c2410_udc_disable(udc);
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2410_udc_vbus_session(काष्ठा usb_gadget *gadget, पूर्णांक is_active)
अणु
	काष्ठा s3c2410_udc *udc = to_s3c2410_udc(gadget);

	dprपूर्णांकk(DEBUG_NORMAL, "%s()\n", __func__);

	udc->vbus = (is_active != 0);
	s3c2410_udc_set_pullup(udc, is_active);
	वापस 0;
पूर्ण

अटल पूर्णांक s3c2410_udc_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा s3c2410_udc *udc = to_s3c2410_udc(gadget);

	dprपूर्णांकk(DEBUG_NORMAL, "%s()\n", __func__);

	s3c2410_udc_set_pullup(udc, is_on);
	वापस 0;
पूर्ण

अटल irqवापस_t s3c2410_udc_vbus_irq(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा s3c2410_udc	*dev = _dev;
	अचिन्हित पूर्णांक		value;

	dprपूर्णांकk(DEBUG_NORMAL, "%s()\n", __func__);

	value = gpio_get_value(udc_info->vbus_pin) ? 1 : 0;
	अगर (udc_info->vbus_pin_inverted)
		value = !value;

	अगर (value != dev->vbus)
		s3c2410_udc_vbus_session(&dev->gadget, value);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक s3c2410_vbus_draw(काष्ठा usb_gadget *_gadget, अचिन्हित ma)
अणु
	dprपूर्णांकk(DEBUG_NORMAL, "%s()\n", __func__);

	अगर (udc_info && udc_info->vbus_draw) अणु
		udc_info->vbus_draw(ma);
		वापस 0;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक s3c2410_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक s3c2410_udc_stop(काष्ठा usb_gadget *g);

अटल स्थिर काष्ठा usb_gadget_ops s3c2410_ops = अणु
	.get_frame		= s3c2410_udc_get_frame,
	.wakeup			= s3c2410_udc_wakeup,
	.set_selfघातered	= s3c2410_udc_set_selfघातered,
	.pullup			= s3c2410_udc_pullup,
	.vbus_session		= s3c2410_udc_vbus_session,
	.vbus_draw		= s3c2410_vbus_draw,
	.udc_start		= s3c2410_udc_start,
	.udc_stop		= s3c2410_udc_stop,
पूर्ण;

अटल व्योम s3c2410_udc_command(क्रमागत s3c2410_udc_cmd_e cmd)
अणु
	अगर (!udc_info)
		वापस;

	अगर (udc_info->udc_command) अणु
		udc_info->udc_command(cmd);
	पूर्ण अन्यथा अगर (gpio_is_valid(udc_info->pullup_pin)) अणु
		पूर्णांक value;

		चयन (cmd) अणु
		हाल S3C2410_UDC_P_ENABLE:
			value = 1;
			अवरोध;
		हाल S3C2410_UDC_P_DISABLE:
			value = 0;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		value ^= udc_info->pullup_pin_inverted;

		gpio_set_value(udc_info->pullup_pin, value);
	पूर्ण
पूर्ण

/*------------------------- gadget driver handling---------------------------*/
/*
 * s3c2410_udc_disable
 */
अटल व्योम s3c2410_udc_disable(काष्ठा s3c2410_udc *dev)
अणु
	dprपूर्णांकk(DEBUG_NORMAL, "%s()\n", __func__);

	/* Disable all पूर्णांकerrupts */
	udc_ग_लिखो(0x00, S3C2410_UDC_USB_INT_EN_REG);
	udc_ग_लिखो(0x00, S3C2410_UDC_EP_INT_EN_REG);

	/* Clear the पूर्णांकerrupt रेजिस्टरs */
	udc_ग_लिखो(S3C2410_UDC_USBINT_RESET
				| S3C2410_UDC_USBINT_RESUME
				| S3C2410_UDC_USBINT_SUSPEND,
			S3C2410_UDC_USB_INT_REG);

	udc_ग_लिखो(0x1F, S3C2410_UDC_EP_INT_REG);

	/* Good bye, cruel world */
	s3c2410_udc_command(S3C2410_UDC_P_DISABLE);

	/* Set speed to unknown */
	dev->gadget.speed = USB_SPEED_UNKNOWN;
पूर्ण

/*
 * s3c2410_udc_reinit
 */
अटल व्योम s3c2410_udc_reinit(काष्ठा s3c2410_udc *dev)
अणु
	u32 i;

	/* device/ep0 records init */
	INIT_LIST_HEAD(&dev->gadget.ep_list);
	INIT_LIST_HEAD(&dev->gadget.ep0->ep_list);
	dev->ep0state = EP0_IDLE;

	क्रम (i = 0; i < S3C2410_ENDPOINTS; i++) अणु
		काष्ठा s3c2410_ep *ep = &dev->ep[i];

		अगर (i != 0)
			list_add_tail(&ep->ep.ep_list, &dev->gadget.ep_list);

		ep->dev = dev;
		ep->ep.desc = शून्य;
		ep->halted = 0;
		INIT_LIST_HEAD(&ep->queue);
		usb_ep_set_maxpacket_limit(&ep->ep, ep->ep.maxpacket);
	पूर्ण
पूर्ण

/*
 * s3c2410_udc_enable
 */
अटल व्योम s3c2410_udc_enable(काष्ठा s3c2410_udc *dev)
अणु
	पूर्णांक i;

	dprपूर्णांकk(DEBUG_NORMAL, "s3c2410_udc_enable called\n");

	/* dev->gadget.speed = USB_SPEED_UNKNOWN; */
	dev->gadget.speed = USB_SPEED_FULL;

	/* Set MAXP क्रम all endpoपूर्णांकs */
	क्रम (i = 0; i < S3C2410_ENDPOINTS; i++) अणु
		udc_ग_लिखो(i, S3C2410_UDC_INDEX_REG);
		udc_ग_लिखो((dev->ep[i].ep.maxpacket & 0x7ff) >> 3,
				S3C2410_UDC_MAXP_REG);
	पूर्ण

	/* Set शेष घातer state */
	udc_ग_लिखो(DEFAULT_POWER_STATE, S3C2410_UDC_PWR_REG);

	/* Enable reset and suspend पूर्णांकerrupt पूर्णांकerrupts */
	udc_ग_लिखो(S3C2410_UDC_USBINT_RESET | S3C2410_UDC_USBINT_SUSPEND,
			S3C2410_UDC_USB_INT_EN_REG);

	/* Enable ep0 पूर्णांकerrupt */
	udc_ग_लिखो(S3C2410_UDC_INT_EP0, S3C2410_UDC_EP_INT_EN_REG);

	/* समय to say "hello, world" */
	s3c2410_udc_command(S3C2410_UDC_P_ENABLE);
पूर्ण

अटल पूर्णांक s3c2410_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा s3c2410_udc *udc = to_s3c2410(g);

	dprपूर्णांकk(DEBUG_NORMAL, "%s() '%s'\n", __func__, driver->driver.name);

	/* Hook the driver */
	udc->driver = driver;

	/* Enable udc */
	s3c2410_udc_enable(udc);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2410_udc_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा s3c2410_udc *udc = to_s3c2410(g);

	udc->driver = शून्य;

	/* Disable udc */
	s3c2410_udc_disable(udc);

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------*/
अटल काष्ठा s3c2410_udc memory = अणु
	.gadget = अणु
		.ops		= &s3c2410_ops,
		.ep0		= &memory.ep[0].ep,
		.name		= gadget_name,
		.dev = अणु
			.init_name	= "gadget",
		पूर्ण,
	पूर्ण,

	/* control endpoपूर्णांक */
	.ep[0] = अणु
		.num		= 0,
		.ep = अणु
			.name		= ep0name,
			.ops		= &s3c2410_ep_ops,
			.maxpacket	= EP0_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTROL,
						USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.dev		= &memory,
	पूर्ण,

	/* first group of endpoपूर्णांकs */
	.ep[1] = अणु
		.num		= 1,
		.ep = अणु
			.name		= "ep1-bulk",
			.ops		= &s3c2410_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
						USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= EP_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = 1,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
	पूर्ण,
	.ep[2] = अणु
		.num		= 2,
		.ep = अणु
			.name		= "ep2-bulk",
			.ops		= &s3c2410_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
						USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= EP_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = 2,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
	पूर्ण,
	.ep[3] = अणु
		.num		= 3,
		.ep = अणु
			.name		= "ep3-bulk",
			.ops		= &s3c2410_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
						USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= EP_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = 3,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
	पूर्ण,
	.ep[4] = अणु
		.num		= 4,
		.ep = अणु
			.name		= "ep4-bulk",
			.ops		= &s3c2410_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
						USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= EP_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = 4,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
	पूर्ण

पूर्ण;

/*
 *	probe - binds to the platक्रमm device
 */
अटल पूर्णांक s3c2410_udc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c2410_udc *udc = &memory;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक retval;
	पूर्णांक irq;

	dev_dbg(dev, "%s()\n", __func__);

	usb_bus_घड़ी = clk_get(शून्य, "usb-bus-gadget");
	अगर (IS_ERR(usb_bus_घड़ी)) अणु
		dev_err(dev, "failed to get usb bus clock source\n");
		वापस PTR_ERR(usb_bus_घड़ी);
	पूर्ण

	clk_prepare_enable(usb_bus_घड़ी);

	udc_घड़ी = clk_get(शून्य, "usb-device");
	अगर (IS_ERR(udc_घड़ी)) अणु
		dev_err(dev, "failed to get udc clock source\n");
		retval = PTR_ERR(udc_घड़ी);
		जाओ err_usb_bus_clk;
	पूर्ण

	clk_prepare_enable(udc_घड़ी);

	mdelay(10);

	dev_dbg(dev, "got and enabled clocks\n");

	अगर (म_भेदन(pdev->name, "s3c2440", 7) == 0) अणु
		dev_info(dev, "S3C2440: increasing FIFO to 128 bytes\n");
		memory.ep[1].fअगरo_size = S3C2440_EP_FIFO_SIZE;
		memory.ep[2].fअगरo_size = S3C2440_EP_FIFO_SIZE;
		memory.ep[3].fअगरo_size = S3C2440_EP_FIFO_SIZE;
		memory.ep[4].fअगरo_size = S3C2440_EP_FIFO_SIZE;
	पूर्ण

	spin_lock_init(&udc->lock);
	udc_info = dev_get_platdata(&pdev->dev);

	base_addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base_addr)) अणु
		retval = PTR_ERR(base_addr);
		जाओ err_udc_clk;
	पूर्ण

	the_controller = udc;
	platक्रमm_set_drvdata(pdev, udc);

	s3c2410_udc_disable(udc);
	s3c2410_udc_reinit(udc);

	irq_usbd = platक्रमm_get_irq(pdev, 0);

	/* irq setup after old hardware state is cleaned up */
	retval = request_irq(irq_usbd, s3c2410_udc_irq,
			     0, gadget_name, udc);

	अगर (retval != 0) अणु
		dev_err(dev, "cannot get irq %i, err %d\n", irq_usbd, retval);
		retval = -EBUSY;
		जाओ err_udc_clk;
	पूर्ण

	dev_dbg(dev, "got irq %i\n", irq_usbd);

	अगर (udc_info && udc_info->vbus_pin > 0) अणु
		retval = gpio_request(udc_info->vbus_pin, "udc vbus");
		अगर (retval < 0) अणु
			dev_err(dev, "cannot claim vbus pin\n");
			जाओ err_पूर्णांक;
		पूर्ण

		irq = gpio_to_irq(udc_info->vbus_pin);
		अगर (irq < 0) अणु
			dev_err(dev, "no irq for gpio vbus pin\n");
			retval = irq;
			जाओ err_gpio_claim;
		पूर्ण

		retval = request_irq(irq, s3c2410_udc_vbus_irq,
				     IRQF_TRIGGER_RISING
				     | IRQF_TRIGGER_FALLING | IRQF_SHARED,
				     gadget_name, udc);

		अगर (retval != 0) अणु
			dev_err(dev, "can't get vbus irq %d, err %d\n",
				irq, retval);
			retval = -EBUSY;
			जाओ err_gpio_claim;
		पूर्ण

		dev_dbg(dev, "got irq %i\n", irq);
	पूर्ण अन्यथा अणु
		udc->vbus = 1;
	पूर्ण

	अगर (udc_info && !udc_info->udc_command &&
		gpio_is_valid(udc_info->pullup_pin)) अणु

		retval = gpio_request_one(udc_info->pullup_pin,
				udc_info->vbus_pin_inverted ?
				GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW,
				"udc pullup");
		अगर (retval)
			जाओ err_vbus_irq;
	पूर्ण

	retval = usb_add_gadget_udc(&pdev->dev, &udc->gadget);
	अगर (retval)
		जाओ err_add_udc;

	udc->regs_info = debugfs_create_file("registers", S_IRUGO,
					     s3c2410_udc_debugfs_root, udc,
					     &s3c2410_udc_debugfs_fops);

	dev_dbg(dev, "probe ok\n");

	वापस 0;

err_add_udc:
	अगर (udc_info && !udc_info->udc_command &&
			gpio_is_valid(udc_info->pullup_pin))
		gpio_मुक्त(udc_info->pullup_pin);
err_vbus_irq:
	अगर (udc_info && udc_info->vbus_pin > 0)
		मुक्त_irq(gpio_to_irq(udc_info->vbus_pin), udc);
err_gpio_claim:
	अगर (udc_info && udc_info->vbus_pin > 0)
		gpio_मुक्त(udc_info->vbus_pin);
err_पूर्णांक:
	मुक्त_irq(irq_usbd, udc);
err_udc_clk:
	clk_disable_unprepare(udc_घड़ी);
	clk_put(udc_घड़ी);
	udc_घड़ी = शून्य;
err_usb_bus_clk:
	clk_disable_unprepare(usb_bus_घड़ी);
	clk_put(usb_bus_घड़ी);
	usb_bus_घड़ी = शून्य;

	वापस retval;
पूर्ण

/*
 *	s3c2410_udc_हटाओ
 */
अटल पूर्णांक s3c2410_udc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c2410_udc *udc = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक irq;

	dev_dbg(&pdev->dev, "%s()\n", __func__);

	अगर (udc->driver)
		वापस -EBUSY;

	usb_del_gadget_udc(&udc->gadget);
	debugfs_हटाओ(udc->regs_info);

	अगर (udc_info && !udc_info->udc_command &&
		gpio_is_valid(udc_info->pullup_pin))
		gpio_मुक्त(udc_info->pullup_pin);

	अगर (udc_info && udc_info->vbus_pin > 0) अणु
		irq = gpio_to_irq(udc_info->vbus_pin);
		मुक्त_irq(irq, udc);
	पूर्ण

	मुक्त_irq(irq_usbd, udc);

	अगर (!IS_ERR(udc_घड़ी) && udc_घड़ी != शून्य) अणु
		clk_disable_unprepare(udc_घड़ी);
		clk_put(udc_घड़ी);
		udc_घड़ी = शून्य;
	पूर्ण

	अगर (!IS_ERR(usb_bus_घड़ी) && usb_bus_घड़ी != शून्य) अणु
		clk_disable_unprepare(usb_bus_घड़ी);
		clk_put(usb_bus_घड़ी);
		usb_bus_घड़ी = शून्य;
	पूर्ण

	dev_dbg(&pdev->dev, "%s: remove ok\n", __func__);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक
s3c2410_udc_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t message)
अणु
	s3c2410_udc_command(S3C2410_UDC_P_DISABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2410_udc_resume(काष्ठा platक्रमm_device *pdev)
अणु
	s3c2410_udc_command(S3C2410_UDC_P_ENABLE);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा s3c2410_udc_suspend	शून्य
#घोषणा s3c2410_udc_resume	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा platक्रमm_device_id s3c_udc_ids[] = अणु
	अणु "s3c2410-usbgadget", पूर्ण,
	अणु "s3c2440-usbgadget", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s3c_udc_ids);

अटल काष्ठा platक्रमm_driver udc_driver_24x0 = अणु
	.driver		= अणु
		.name	= "s3c24x0-usbgadget",
	पूर्ण,
	.probe		= s3c2410_udc_probe,
	.हटाओ		= s3c2410_udc_हटाओ,
	.suspend	= s3c2410_udc_suspend,
	.resume		= s3c2410_udc_resume,
	.id_table	= s3c_udc_ids,
पूर्ण;

अटल पूर्णांक __init udc_init(व्योम)
अणु
	पूर्णांक retval;

	dprपूर्णांकk(DEBUG_NORMAL, "%s\n", gadget_name);

	s3c2410_udc_debugfs_root = debugfs_create_dir(gadget_name,
						      usb_debug_root);

	retval = platक्रमm_driver_रेजिस्टर(&udc_driver_24x0);
	अगर (retval)
		जाओ err;

	वापस 0;

err:
	debugfs_हटाओ(s3c2410_udc_debugfs_root);
	वापस retval;
पूर्ण

अटल व्योम __निकास udc_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&udc_driver_24x0);
	debugfs_हटाओ_recursive(s3c2410_udc_debugfs_root);
पूर्ण

module_init(udc_init);
module_निकास(udc_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
