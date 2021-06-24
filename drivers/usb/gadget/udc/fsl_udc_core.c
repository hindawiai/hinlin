<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2004-2007,2011-2012 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Author: Li Yang <leoli@मुक्तscale.com>
 *         Jiang Bo <tanya.jiang@मुक्तscale.com>
 *
 * Description:
 * Freescale high-speed USB SOC DR module device controller driver.
 * This can be found on MPC8349E/MPC8313E/MPC5121E cpus.
 * The driver is previously named as mpc_udc.  Based on bare board
 * code from Dave Liu and Shlomi Gridish.
 */

#अघोषित VERBOSE

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/dma.h>

#समावेश "fsl_usb2_udc.h"

#घोषणा	DRIVER_DESC	"Freescale High-Speed USB SOC Device Controller driver"
#घोषणा	DRIVER_AUTHOR	"Li Yang/Jiang Bo"
#घोषणा	DRIVER_VERSION	"Apr 20, 2007"

#घोषणा	DMA_ADDR_INVALID	(~(dma_addr_t)0)

अटल स्थिर अक्षर driver_name[] = "fsl-usb2-udc";

अटल काष्ठा usb_dr_device __iomem *dr_regs;

अटल काष्ठा usb_sys_पूर्णांकerface __iomem *usb_sys_regs;

/* it is initialized in probe()  */
अटल काष्ठा fsl_udc *udc_controller = शून्य;

अटल स्थिर काष्ठा usb_endpoपूर्णांक_descriptor
fsl_ep0_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	0,
	.bmAttributes =		USB_ENDPOINT_XFER_CONTROL,
	.wMaxPacketSize =	USB_MAX_CTRL_PAYLOAD,
पूर्ण;

अटल व्योम fsl_ep_fअगरo_flush(काष्ठा usb_ep *_ep);

#अगर_घोषित CONFIG_PPC32
/*
 * On some SoCs, the USB controller रेजिस्टरs can be big or little endian,
 * depending on the version of the chip. In order to be able to run the
 * same kernel binary on 2 dअगरferent versions of an SoC, the BE/LE decision
 * must be made at run समय. _fsl_पढ़ोl and fsl_ग_लिखोl are poपूर्णांकers to the
 * BE or LE पढ़ोl() and ग_लिखोl() functions, and fsl_पढ़ोl() and fsl_ग_लिखोl()
 * call through those poपूर्णांकers. Platक्रमm code क्रम SoCs that have BE USB
 * रेजिस्टरs should set pdata->big_endian_mmio flag.
 *
 * This also applies to controller-to-cpu accessors क्रम the USB descriptors,
 * since their endianness is also SoC dependant. Platक्रमm code क्रम SoCs that
 * have BE USB descriptors should set pdata->big_endian_desc flag.
 */
अटल u32 _fsl_पढ़ोl_be(स्थिर अचिन्हित __iomem *p)
अणु
	वापस in_be32(p);
पूर्ण

अटल u32 _fsl_पढ़ोl_le(स्थिर अचिन्हित __iomem *p)
अणु
	वापस in_le32(p);
पूर्ण

अटल व्योम _fsl_ग_लिखोl_be(u32 v, अचिन्हित __iomem *p)
अणु
	out_be32(p, v);
पूर्ण

अटल व्योम _fsl_ग_लिखोl_le(u32 v, अचिन्हित __iomem *p)
अणु
	out_le32(p, v);
पूर्ण

अटल u32 (*_fsl_पढ़ोl)(स्थिर अचिन्हित __iomem *p);
अटल व्योम (*_fsl_ग_लिखोl)(u32 v, अचिन्हित __iomem *p);

#घोषणा fsl_पढ़ोl(p)		(*_fsl_पढ़ोl)((p))
#घोषणा fsl_ग_लिखोl(v, p)	(*_fsl_ग_लिखोl)((v), (p))

अटल अंतरभूत व्योम fsl_set_accessors(काष्ठा fsl_usb2_platक्रमm_data *pdata)
अणु
	अगर (pdata->big_endian_mmio) अणु
		_fsl_पढ़ोl = _fsl_पढ़ोl_be;
		_fsl_ग_लिखोl = _fsl_ग_लिखोl_be;
	पूर्ण अन्यथा अणु
		_fsl_पढ़ोl = _fsl_पढ़ोl_le;
		_fsl_ग_लिखोl = _fsl_ग_लिखोl_le;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 cpu_to_hc32(स्थिर u32 x)
अणु
	वापस udc_controller->pdata->big_endian_desc
		? (__क्रमce u32)cpu_to_be32(x)
		: (__क्रमce u32)cpu_to_le32(x);
पूर्ण

अटल अंतरभूत u32 hc32_to_cpu(स्थिर u32 x)
अणु
	वापस udc_controller->pdata->big_endian_desc
		? be32_to_cpu((__क्रमce __be32)x)
		: le32_to_cpu((__क्रमce __le32)x);
पूर्ण
#अन्यथा /* !CONFIG_PPC32 */
अटल अंतरभूत व्योम fsl_set_accessors(काष्ठा fsl_usb2_platक्रमm_data *pdata) अणुपूर्ण

#घोषणा fsl_पढ़ोl(addr)		पढ़ोl(addr)
#घोषणा fsl_ग_लिखोl(val32, addr) ग_लिखोl(val32, addr)
#घोषणा cpu_to_hc32(x)		cpu_to_le32(x)
#घोषणा hc32_to_cpu(x)		le32_to_cpu(x)
#पूर्ण_अगर /* CONFIG_PPC32 */

/********************************************************************
 *	Internal Used Function
********************************************************************/
/*-----------------------------------------------------------------
 * करोne() - retire a request; caller blocked irqs
 * @status : request status to be set, only works when
 *	request is still in progress.
 *--------------------------------------------------------------*/
अटल व्योम करोne(काष्ठा fsl_ep *ep, काष्ठा fsl_req *req, पूर्णांक status)
__releases(ep->udc->lock)
__acquires(ep->udc->lock)
अणु
	काष्ठा fsl_udc *udc = शून्य;
	अचिन्हित अक्षर stopped = ep->stopped;
	काष्ठा ep_td_काष्ठा *curr_td, *next_td;
	पूर्णांक j;

	udc = (काष्ठा fsl_udc *)ep->udc;
	/* Removed the req from fsl_ep->queue */
	list_del_init(&req->queue);

	/* req.status should be set as -EINPROGRESS in ep_queue() */
	अगर (req->req.status == -EINPROGRESS)
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	/* Free dtd क्रम the request */
	next_td = req->head;
	क्रम (j = 0; j < req->dtd_count; j++) अणु
		curr_td = next_td;
		अगर (j != req->dtd_count - 1) अणु
			next_td = curr_td->next_td_virt;
		पूर्ण
		dma_pool_मुक्त(udc->td_pool, curr_td, curr_td->td_dma);
	पूर्ण

	usb_gadget_unmap_request(&ep->udc->gadget, &req->req, ep_is_in(ep));

	अगर (status && (status != -ESHUTDOWN))
		VDBG("complete %s req %p stat %d len %u/%u",
			ep->ep.name, &req->req, status,
			req->req.actual, req->req.length);

	ep->stopped = 1;

	spin_unlock(&ep->udc->lock);

	usb_gadget_giveback_request(&ep->ep, &req->req);

	spin_lock(&ep->udc->lock);
	ep->stopped = stopped;
पूर्ण

/*-----------------------------------------------------------------
 * nuke(): delete all requests related to this ep
 * called with spinlock held
 *--------------------------------------------------------------*/
अटल व्योम nuke(काष्ठा fsl_ep *ep, पूर्णांक status)
अणु
	ep->stopped = 1;

	/* Flush fअगरo */
	fsl_ep_fअगरo_flush(&ep->ep);

	/* Whether this eq has request linked */
	जबतक (!list_empty(&ep->queue)) अणु
		काष्ठा fsl_req *req = शून्य;

		req = list_entry(ep->queue.next, काष्ठा fsl_req, queue);
		करोne(ep, req, status);
	पूर्ण
पूर्ण

/*------------------------------------------------------------------
	Internal Hardware related function
 ------------------------------------------------------------------*/

अटल पूर्णांक dr_controller_setup(काष्ठा fsl_udc *udc)
अणु
	अचिन्हित पूर्णांक पंचांगp, portctrl, ep_num;
	अचिन्हित पूर्णांक max_no_of_ep;
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित दीर्घ समयout;

#घोषणा FSL_UDC_RESET_TIMEOUT 1000

	/* Config PHY पूर्णांकerface */
	portctrl = fsl_पढ़ोl(&dr_regs->portsc1);
	portctrl &= ~(PORTSCX_PHY_TYPE_SEL | PORTSCX_PORT_WIDTH);
	चयन (udc->phy_mode) अणु
	हाल FSL_USB2_PHY_ULPI:
		अगर (udc->pdata->have_sysअगर_regs) अणु
			अगर (udc->pdata->controller_ver) अणु
				/* controller version 1.6 or above */
				ctrl = __raw_पढ़ोl(&usb_sys_regs->control);
				ctrl &= ~USB_CTRL_UTMI_PHY_EN;
				ctrl |= USB_CTRL_USB_EN;
				__raw_ग_लिखोl(ctrl, &usb_sys_regs->control);
			पूर्ण
		पूर्ण
		portctrl |= PORTSCX_PTS_ULPI;
		अवरोध;
	हाल FSL_USB2_PHY_UTMI_WIDE:
		portctrl |= PORTSCX_PTW_16BIT;
		fallthrough;
	हाल FSL_USB2_PHY_UTMI:
	हाल FSL_USB2_PHY_UTMI_DUAL:
		अगर (udc->pdata->have_sysअगर_regs) अणु
			अगर (udc->pdata->controller_ver) अणु
				/* controller version 1.6 or above */
				ctrl = __raw_पढ़ोl(&usb_sys_regs->control);
				ctrl |= (USB_CTRL_UTMI_PHY_EN |
					USB_CTRL_USB_EN);
				__raw_ग_लिखोl(ctrl, &usb_sys_regs->control);
				mdelay(FSL_UTMI_PHY_DLY); /* Delay क्रम UTMI
					PHY CLK to become stable - 10ms*/
			पूर्ण
		पूर्ण
		portctrl |= PORTSCX_PTS_UTMI;
		अवरोध;
	हाल FSL_USB2_PHY_SERIAL:
		portctrl |= PORTSCX_PTS_FSLS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	fsl_ग_लिखोl(portctrl, &dr_regs->portsc1);

	/* Stop and reset the usb controller */
	पंचांगp = fsl_पढ़ोl(&dr_regs->usbcmd);
	पंचांगp &= ~USB_CMD_RUN_STOP;
	fsl_ग_लिखोl(पंचांगp, &dr_regs->usbcmd);

	पंचांगp = fsl_पढ़ोl(&dr_regs->usbcmd);
	पंचांगp |= USB_CMD_CTRL_RESET;
	fsl_ग_लिखोl(पंचांगp, &dr_regs->usbcmd);

	/* Wait क्रम reset to complete */
	समयout = jअगरfies + FSL_UDC_RESET_TIMEOUT;
	जबतक (fsl_पढ़ोl(&dr_regs->usbcmd) & USB_CMD_CTRL_RESET) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			ERR("udc reset timeout!\n");
			वापस -ETIMEDOUT;
		पूर्ण
		cpu_relax();
	पूर्ण

	/* Set the controller as device mode */
	पंचांगp = fsl_पढ़ोl(&dr_regs->usbmode);
	पंचांगp &= ~USB_MODE_CTRL_MODE_MASK;	/* clear mode bits */
	पंचांगp |= USB_MODE_CTRL_MODE_DEVICE;
	/* Disable Setup Lockout */
	पंचांगp |= USB_MODE_SETUP_LOCK_OFF;
	अगर (udc->pdata->es)
		पंचांगp |= USB_MODE_ES;
	fsl_ग_लिखोl(पंचांगp, &dr_regs->usbmode);

	/* Clear the setup status */
	fsl_ग_लिखोl(0, &dr_regs->usbsts);

	पंचांगp = udc->ep_qh_dma;
	पंचांगp &= USB_EP_LIST_ADDRESS_MASK;
	fsl_ग_लिखोl(पंचांगp, &dr_regs->endpoपूर्णांकlistaddr);

	VDBG("vir[qh_base] is %p phy[qh_base] is 0x%8x reg is 0x%8x",
		udc->ep_qh, (पूर्णांक)पंचांगp,
		fsl_पढ़ोl(&dr_regs->endpoपूर्णांकlistaddr));

	max_no_of_ep = (0x0000001F & fsl_पढ़ोl(&dr_regs->dccparams));
	क्रम (ep_num = 1; ep_num < max_no_of_ep; ep_num++) अणु
		पंचांगp = fsl_पढ़ोl(&dr_regs->endptctrl[ep_num]);
		पंचांगp &= ~(EPCTRL_TX_TYPE | EPCTRL_RX_TYPE);
		पंचांगp |= (EPCTRL_EP_TYPE_BULK << EPCTRL_TX_EP_TYPE_SHIFT)
		| (EPCTRL_EP_TYPE_BULK << EPCTRL_RX_EP_TYPE_SHIFT);
		fsl_ग_लिखोl(पंचांगp, &dr_regs->endptctrl[ep_num]);
	पूर्ण
	/* Config control enable i/o output, cpu endian रेजिस्टर */
#अगर_अघोषित CONFIG_ARCH_MXC
	अगर (udc->pdata->have_sysअगर_regs) अणु
		ctrl = __raw_पढ़ोl(&usb_sys_regs->control);
		ctrl |= USB_CTRL_IOENB;
		__raw_ग_लिखोl(ctrl, &usb_sys_regs->control);
	पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PPC32) && !defined(CONFIG_NOT_COHERENT_CACHE)
	/* Turn on cache snooping hardware, since some PowerPC platक्रमms
	 * wholly rely on hardware to deal with cache coherent. */

	अगर (udc->pdata->have_sysअगर_regs) अणु
		/* Setup Snooping क्रम all the 4GB space */
		पंचांगp = SNOOP_SIZE_2GB;	/* starts from 0x0, size 2G */
		__raw_ग_लिखोl(पंचांगp, &usb_sys_regs->snoop1);
		पंचांगp |= 0x80000000;	/* starts from 0x8000000, size 2G */
		__raw_ग_लिखोl(पंचांगp, &usb_sys_regs->snoop2);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* Enable DR irq and set controller to run state */
अटल व्योम dr_controller_run(काष्ठा fsl_udc *udc)
अणु
	u32 temp;

	/* Enable DR irq reg */
	temp = USB_INTR_INT_EN | USB_INTR_ERR_INT_EN
		| USB_INTR_PTC_DETECT_EN | USB_INTR_RESET_EN
		| USB_INTR_DEVICE_SUSPEND | USB_INTR_SYS_ERR_EN;

	fsl_ग_लिखोl(temp, &dr_regs->usbपूर्णांकr);

	/* Clear stopped bit */
	udc->stopped = 0;

	/* Set the controller as device mode */
	temp = fsl_पढ़ोl(&dr_regs->usbmode);
	temp |= USB_MODE_CTRL_MODE_DEVICE;
	fsl_ग_लिखोl(temp, &dr_regs->usbmode);

	/* Set controller to Run */
	temp = fsl_पढ़ोl(&dr_regs->usbcmd);
	temp |= USB_CMD_RUN_STOP;
	fsl_ग_लिखोl(temp, &dr_regs->usbcmd);
पूर्ण

अटल व्योम dr_controller_stop(काष्ठा fsl_udc *udc)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	pr_debug("%s\n", __func__);

	/* अगर we're in OTG mode, and the Host is currently using the port,
	 * stop now and करोn't rip the controller out from under the
	 * ehci driver
	 */
	अगर (udc->gadget.is_otg) अणु
		अगर (!(fsl_पढ़ोl(&dr_regs->otgsc) & OTGSC_STS_USB_ID)) अणु
			pr_debug("udc: Leaving early\n");
			वापस;
		पूर्ण
	पूर्ण

	/* disable all INTR */
	fsl_ग_लिखोl(0, &dr_regs->usbपूर्णांकr);

	/* Set stopped bit क्रम isr */
	udc->stopped = 1;

	/* disable IO output */
/*	usb_sys_regs->control = 0; */

	/* set controller to Stop */
	पंचांगp = fsl_पढ़ोl(&dr_regs->usbcmd);
	पंचांगp &= ~USB_CMD_RUN_STOP;
	fsl_ग_लिखोl(पंचांगp, &dr_regs->usbcmd);
पूर्ण

अटल व्योम dr_ep_setup(अचिन्हित अक्षर ep_num, अचिन्हित अक्षर dir,
			अचिन्हित अक्षर ep_type)
अणु
	अचिन्हित पूर्णांक पंचांगp_epctrl = 0;

	पंचांगp_epctrl = fsl_पढ़ोl(&dr_regs->endptctrl[ep_num]);
	अगर (dir) अणु
		अगर (ep_num)
			पंचांगp_epctrl |= EPCTRL_TX_DATA_TOGGLE_RST;
		पंचांगp_epctrl |= EPCTRL_TX_ENABLE;
		पंचांगp_epctrl &= ~EPCTRL_TX_TYPE;
		पंचांगp_epctrl |= ((अचिन्हित पूर्णांक)(ep_type)
				<< EPCTRL_TX_EP_TYPE_SHIFT);
	पूर्ण अन्यथा अणु
		अगर (ep_num)
			पंचांगp_epctrl |= EPCTRL_RX_DATA_TOGGLE_RST;
		पंचांगp_epctrl |= EPCTRL_RX_ENABLE;
		पंचांगp_epctrl &= ~EPCTRL_RX_TYPE;
		पंचांगp_epctrl |= ((अचिन्हित पूर्णांक)(ep_type)
				<< EPCTRL_RX_EP_TYPE_SHIFT);
	पूर्ण

	fsl_ग_लिखोl(पंचांगp_epctrl, &dr_regs->endptctrl[ep_num]);
पूर्ण

अटल व्योम
dr_ep_change_stall(अचिन्हित अक्षर ep_num, अचिन्हित अक्षर dir, पूर्णांक value)
अणु
	u32 पंचांगp_epctrl = 0;

	पंचांगp_epctrl = fsl_पढ़ोl(&dr_regs->endptctrl[ep_num]);

	अगर (value) अणु
		/* set the stall bit */
		अगर (dir)
			पंचांगp_epctrl |= EPCTRL_TX_EP_STALL;
		अन्यथा
			पंचांगp_epctrl |= EPCTRL_RX_EP_STALL;
	पूर्ण अन्यथा अणु
		/* clear the stall bit and reset data toggle */
		अगर (dir) अणु
			पंचांगp_epctrl &= ~EPCTRL_TX_EP_STALL;
			पंचांगp_epctrl |= EPCTRL_TX_DATA_TOGGLE_RST;
		पूर्ण अन्यथा अणु
			पंचांगp_epctrl &= ~EPCTRL_RX_EP_STALL;
			पंचांगp_epctrl |= EPCTRL_RX_DATA_TOGGLE_RST;
		पूर्ण
	पूर्ण
	fsl_ग_लिखोl(पंचांगp_epctrl, &dr_regs->endptctrl[ep_num]);
पूर्ण

/* Get stall status of a specअगरic ep
   Return: 0: not stalled; 1:stalled */
अटल पूर्णांक dr_ep_get_stall(अचिन्हित अक्षर ep_num, अचिन्हित अक्षर dir)
अणु
	u32 epctrl;

	epctrl = fsl_पढ़ोl(&dr_regs->endptctrl[ep_num]);
	अगर (dir)
		वापस (epctrl & EPCTRL_TX_EP_STALL) ? 1 : 0;
	अन्यथा
		वापस (epctrl & EPCTRL_RX_EP_STALL) ? 1 : 0;
पूर्ण

/********************************************************************
	Internal Structure Build up functions
********************************************************************/

/*------------------------------------------------------------------
* काष्ठा_ep_qh_setup(): set the Endpoपूर्णांक Capabilites field of QH
 * @zlt: Zero Length Termination Select (1: disable; 0: enable)
 * @mult: Mult field
 ------------------------------------------------------------------*/
अटल व्योम काष्ठा_ep_qh_setup(काष्ठा fsl_udc *udc, अचिन्हित अक्षर ep_num,
		अचिन्हित अक्षर dir, अचिन्हित अक्षर ep_type,
		अचिन्हित पूर्णांक max_pkt_len,
		अचिन्हित पूर्णांक zlt, अचिन्हित अक्षर mult)
अणु
	काष्ठा ep_queue_head *p_QH = &udc->ep_qh[2 * ep_num + dir];
	अचिन्हित पूर्णांक पंचांगp = 0;

	/* set the Endpoपूर्णांक Capabilites in QH */
	चयन (ep_type) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		/* Interrupt On Setup (IOS). क्रम control ep  */
		पंचांगp = (max_pkt_len << EP_QUEUE_HEAD_MAX_PKT_LEN_POS)
			| EP_QUEUE_HEAD_IOS;
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		पंचांगp = (max_pkt_len << EP_QUEUE_HEAD_MAX_PKT_LEN_POS)
			| (mult << EP_QUEUE_HEAD_MULT_POS);
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
	हाल USB_ENDPOINT_XFER_INT:
		पंचांगp = max_pkt_len << EP_QUEUE_HEAD_MAX_PKT_LEN_POS;
		अवरोध;
	शेष:
		VDBG("error ep type is %d", ep_type);
		वापस;
	पूर्ण
	अगर (zlt)
		पंचांगp |= EP_QUEUE_HEAD_ZLT_SEL;

	p_QH->max_pkt_length = cpu_to_hc32(पंचांगp);
	p_QH->next_dtd_ptr = 1;
	p_QH->size_ioc_पूर्णांक_sts = 0;
पूर्ण

/* Setup qh काष्ठाure and ep रेजिस्टर क्रम ep0. */
अटल व्योम ep0_setup(काष्ठा fsl_udc *udc)
अणु
	/* the initialization of an ep includes: fields in QH, Regs,
	 * fsl_ep काष्ठा */
	काष्ठा_ep_qh_setup(udc, 0, USB_RECV, USB_ENDPOINT_XFER_CONTROL,
			USB_MAX_CTRL_PAYLOAD, 0, 0);
	काष्ठा_ep_qh_setup(udc, 0, USB_SEND, USB_ENDPOINT_XFER_CONTROL,
			USB_MAX_CTRL_PAYLOAD, 0, 0);
	dr_ep_setup(0, USB_RECV, USB_ENDPOINT_XFER_CONTROL);
	dr_ep_setup(0, USB_SEND, USB_ENDPOINT_XFER_CONTROL);

	वापस;

पूर्ण

/***********************************************************************
		Endpoपूर्णांक Management Functions
***********************************************************************/

/*-------------------------------------------------------------------------
 * when configurations are set, or when पूर्णांकerface settings change
 * क्रम example the करो_set_पूर्णांकerface() in gadget layer,
 * the driver will enable or disable the relevant endpoपूर्णांकs
 * ep0 करोesn't use this routine. It is always enabled.
-------------------------------------------------------------------------*/
अटल पूर्णांक fsl_ep_enable(काष्ठा usb_ep *_ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा fsl_udc *udc = शून्य;
	काष्ठा fsl_ep *ep = शून्य;
	अचिन्हित लघु max = 0;
	अचिन्हित अक्षर mult = 0, zlt;
	पूर्णांक retval = -EINVAL;
	अचिन्हित दीर्घ flags = 0;

	ep = container_of(_ep, काष्ठा fsl_ep, ep);

	/* catch various bogus parameters */
	अगर (!_ep || !desc
			|| (desc->bDescriptorType != USB_DT_ENDPOINT))
		वापस -EINVAL;

	udc = ep->udc;

	अगर (!udc->driver || (udc->gadget.speed == USB_SPEED_UNKNOWN))
		वापस -ESHUTDOWN;

	max = usb_endpoपूर्णांक_maxp(desc);

	/* Disable स्वतःmatic zlp generation.  Driver is responsible to indicate
	 * explicitly through req->req.zero.  This is needed to enable multi-td
	 * request. */
	zlt = 1;

	/* Assume the max packet size from gadget is always correct */
	चयन (desc->bmAttributes & 0x03) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
	हाल USB_ENDPOINT_XFER_BULK:
	हाल USB_ENDPOINT_XFER_INT:
		/* mult = 0.  Execute N Transactions as demonstrated by
		 * the USB variable length packet protocol where N is
		 * computed using the Maximum Packet Length (dQH) and
		 * the Total Bytes field (dTD) */
		mult = 0;
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		/* Calculate transactions needed क्रम high bandwidth iso */
		mult = usb_endpoपूर्णांक_maxp_mult(desc);
		/* 3 transactions at most */
		अगर (mult > 3)
			जाओ en_करोne;
		अवरोध;
	शेष:
		जाओ en_करोne;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);
	ep->ep.maxpacket = max;
	ep->ep.desc = desc;
	ep->stopped = 0;

	/* Controller related setup */
	/* Init EPx Queue Head (Ep Capabilites field in QH
	 * according to max, zlt, mult) */
	काष्ठा_ep_qh_setup(udc, (अचिन्हित अक्षर) ep_index(ep),
			(अचिन्हित अक्षर) ((desc->bEndpoपूर्णांकAddress & USB_सूची_IN)
					?  USB_SEND : USB_RECV),
			(अचिन्हित अक्षर) (desc->bmAttributes
					& USB_ENDPOINT_XFERTYPE_MASK),
			max, zlt, mult);

	/* Init endpoपूर्णांक ctrl रेजिस्टर */
	dr_ep_setup((अचिन्हित अक्षर) ep_index(ep),
			(अचिन्हित अक्षर) ((desc->bEndpoपूर्णांकAddress & USB_सूची_IN)
					? USB_SEND : USB_RECV),
			(अचिन्हित अक्षर) (desc->bmAttributes
					& USB_ENDPOINT_XFERTYPE_MASK));

	spin_unlock_irqrestore(&udc->lock, flags);
	retval = 0;

	VDBG("enabled %s (ep%d%s) maxpacket %d",ep->ep.name,
			ep->ep.desc->bEndpoपूर्णांकAddress & 0x0f,
			(desc->bEndpoपूर्णांकAddress & USB_सूची_IN)
				? "in" : "out", max);
en_करोne:
	वापस retval;
पूर्ण

/*---------------------------------------------------------------------
 * @ep : the ep being unconfigured. May not be ep0
 * Any pending and uncomplete req will complete with status (-ESHUTDOWN)
*---------------------------------------------------------------------*/
अटल पूर्णांक fsl_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा fsl_udc *udc = शून्य;
	काष्ठा fsl_ep *ep = शून्य;
	अचिन्हित दीर्घ flags = 0;
	u32 epctrl;
	पूर्णांक ep_num;

	ep = container_of(_ep, काष्ठा fsl_ep, ep);
	अगर (!_ep || !ep->ep.desc) अणु
		VDBG("%s not enabled", _ep ? ep->ep.name : शून्य);
		वापस -EINVAL;
	पूर्ण

	/* disable ep on controller */
	ep_num = ep_index(ep);
	epctrl = fsl_पढ़ोl(&dr_regs->endptctrl[ep_num]);
	अगर (ep_is_in(ep)) अणु
		epctrl &= ~(EPCTRL_TX_ENABLE | EPCTRL_TX_TYPE);
		epctrl |= EPCTRL_EP_TYPE_BULK << EPCTRL_TX_EP_TYPE_SHIFT;
	पूर्ण अन्यथा अणु
		epctrl &= ~(EPCTRL_RX_ENABLE | EPCTRL_TX_TYPE);
		epctrl |= EPCTRL_EP_TYPE_BULK << EPCTRL_RX_EP_TYPE_SHIFT;
	पूर्ण
	fsl_ग_लिखोl(epctrl, &dr_regs->endptctrl[ep_num]);

	udc = (काष्ठा fsl_udc *)ep->udc;
	spin_lock_irqsave(&udc->lock, flags);

	/* nuke all pending requests (करोes flush) */
	nuke(ep, -ESHUTDOWN);

	ep->ep.desc = शून्य;
	ep->stopped = 1;
	spin_unlock_irqrestore(&udc->lock, flags);

	VDBG("disabled %s OK", _ep->name);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------
 * allocate a request object used by this endpoपूर्णांक
 * the मुख्य operation is to insert the req->queue to the eq->queue
 * Returns the request, or null अगर one could not be allocated
*---------------------------------------------------------------------*/
अटल काष्ठा usb_request *
fsl_alloc_request(काष्ठा usb_ep *_ep, gfp_t gfp_flags)
अणु
	काष्ठा fsl_req *req = शून्य;

	req = kzalloc(माप *req, gfp_flags);
	अगर (!req)
		वापस शून्य;

	req->req.dma = DMA_ADDR_INVALID;
	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

अटल व्योम fsl_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा fsl_req *req = शून्य;

	req = container_of(_req, काष्ठा fsl_req, req);

	अगर (_req)
		kमुक्त(req);
पूर्ण

/* Actually add a dTD chain to an empty dQH and let go */
अटल व्योम fsl_prime_ep(काष्ठा fsl_ep *ep, काष्ठा ep_td_काष्ठा *td)
अणु
	काष्ठा ep_queue_head *qh = get_qh_by_ep(ep);

	/* Write dQH next poपूर्णांकer and terminate bit to 0 */
	qh->next_dtd_ptr = cpu_to_hc32(td->td_dma
			& EP_QUEUE_HEAD_NEXT_POINTER_MASK);

	/* Clear active and halt bit */
	qh->size_ioc_पूर्णांक_sts &= cpu_to_hc32(~(EP_QUEUE_HEAD_STATUS_ACTIVE
					| EP_QUEUE_HEAD_STATUS_HALT));

	/* Ensure that updates to the QH will occur beक्रमe priming. */
	wmb();

	/* Prime endpoपूर्णांक by writing correct bit to ENDPTPRIME */
	fsl_ग_लिखोl(ep_is_in(ep) ? (1 << (ep_index(ep) + 16))
			: (1 << (ep_index(ep))), &dr_regs->endpoपूर्णांकprime);
पूर्ण

/* Add dTD chain to the dQH of an EP */
अटल व्योम fsl_queue_td(काष्ठा fsl_ep *ep, काष्ठा fsl_req *req)
अणु
	u32 temp, biपंचांगask, पंचांगp_stat;

	/* VDBG("QH addr Register 0x%8x", dr_regs->endpoपूर्णांकlistaddr);
	VDBG("ep_qh[%d] addr is 0x%8x", i, (u32)&(ep->udc->ep_qh[i])); */

	biपंचांगask = ep_is_in(ep)
		? (1 << (ep_index(ep) + 16))
		: (1 << (ep_index(ep)));

	/* check अगर the pipe is empty */
	अगर (!(list_empty(&ep->queue)) && !(ep_index(ep) == 0)) अणु
		/* Add td to the end */
		काष्ठा fsl_req *lastreq;
		lastreq = list_entry(ep->queue.prev, काष्ठा fsl_req, queue);
		lastreq->tail->next_td_ptr =
			cpu_to_hc32(req->head->td_dma & DTD_ADDR_MASK);
		/* Ensure dTD's next dtd poपूर्णांकer to be updated */
		wmb();
		/* Read prime bit, अगर 1 जाओ करोne */
		अगर (fsl_पढ़ोl(&dr_regs->endpoपूर्णांकprime) & biपंचांगask)
			वापस;

		करो अणु
			/* Set ATDTW bit in USBCMD */
			temp = fsl_पढ़ोl(&dr_regs->usbcmd);
			fsl_ग_लिखोl(temp | USB_CMD_ATDTW, &dr_regs->usbcmd);

			/* Read correct status bit */
			पंचांगp_stat = fsl_पढ़ोl(&dr_regs->endptstatus) & biपंचांगask;

		पूर्ण जबतक (!(fsl_पढ़ोl(&dr_regs->usbcmd) & USB_CMD_ATDTW));

		/* Write ATDTW bit to 0 */
		temp = fsl_पढ़ोl(&dr_regs->usbcmd);
		fsl_ग_लिखोl(temp & ~USB_CMD_ATDTW, &dr_regs->usbcmd);

		अगर (पंचांगp_stat)
			वापस;
	पूर्ण

	fsl_prime_ep(ep, req->head);
पूर्ण

/* Fill in the dTD काष्ठाure
 * @req: request that the transfer beदीर्घs to
 * @length: वापस actually data length of the dTD
 * @dma: वापस dma address of the dTD
 * @is_last: वापस flag अगर it is the last dTD of the request
 * वापस: poपूर्णांकer to the built dTD */
अटल काष्ठा ep_td_काष्ठा *fsl_build_dtd(काष्ठा fsl_req *req, अचिन्हित *length,
		dma_addr_t *dma, पूर्णांक *is_last, gfp_t gfp_flags)
अणु
	u32 swap_temp;
	काष्ठा ep_td_काष्ठा *dtd;

	/* how big will this transfer be? */
	*length = min(req->req.length - req->req.actual,
			(अचिन्हित)EP_MAX_LENGTH_TRANSFER);

	dtd = dma_pool_alloc(udc_controller->td_pool, gfp_flags, dma);
	अगर (dtd == शून्य)
		वापस dtd;

	dtd->td_dma = *dma;
	/* Clear reserved field */
	swap_temp = hc32_to_cpu(dtd->size_ioc_sts);
	swap_temp &= ~DTD_RESERVED_FIELDS;
	dtd->size_ioc_sts = cpu_to_hc32(swap_temp);

	/* Init all of buffer page poपूर्णांकers */
	swap_temp = (u32) (req->req.dma + req->req.actual);
	dtd->buff_ptr0 = cpu_to_hc32(swap_temp);
	dtd->buff_ptr1 = cpu_to_hc32(swap_temp + 0x1000);
	dtd->buff_ptr2 = cpu_to_hc32(swap_temp + 0x2000);
	dtd->buff_ptr3 = cpu_to_hc32(swap_temp + 0x3000);
	dtd->buff_ptr4 = cpu_to_hc32(swap_temp + 0x4000);

	req->req.actual += *length;

	/* zlp is needed अगर req->req.zero is set */
	अगर (req->req.zero) अणु
		अगर (*length == 0 || (*length % req->ep->ep.maxpacket) != 0)
			*is_last = 1;
		अन्यथा
			*is_last = 0;
	पूर्ण अन्यथा अगर (req->req.length == req->req.actual)
		*is_last = 1;
	अन्यथा
		*is_last = 0;

	अगर ((*is_last) == 0)
		VDBG("multi-dtd request!");
	/* Fill in the transfer size; set active bit */
	swap_temp = ((*length << DTD_LENGTH_BIT_POS) | DTD_STATUS_ACTIVE);

	/* Enable पूर्णांकerrupt क्रम the last dtd of a request */
	अगर (*is_last && !req->req.no_पूर्णांकerrupt)
		swap_temp |= DTD_IOC;

	dtd->size_ioc_sts = cpu_to_hc32(swap_temp);

	mb();

	VDBG("length = %d address= 0x%x", *length, (पूर्णांक)*dma);

	वापस dtd;
पूर्ण

/* Generate dtd chain क्रम a request */
अटल पूर्णांक fsl_req_to_dtd(काष्ठा fsl_req *req, gfp_t gfp_flags)
अणु
	अचिन्हित	count;
	पूर्णांक		is_last;
	पूर्णांक		is_first =1;
	काष्ठा ep_td_काष्ठा	*last_dtd = शून्य, *dtd;
	dma_addr_t dma;

	करो अणु
		dtd = fsl_build_dtd(req, &count, &dma, &is_last, gfp_flags);
		अगर (dtd == शून्य)
			वापस -ENOMEM;

		अगर (is_first) अणु
			is_first = 0;
			req->head = dtd;
		पूर्ण अन्यथा अणु
			last_dtd->next_td_ptr = cpu_to_hc32(dma);
			last_dtd->next_td_virt = dtd;
		पूर्ण
		last_dtd = dtd;

		req->dtd_count++;
	पूर्ण जबतक (!is_last);

	dtd->next_td_ptr = cpu_to_hc32(DTD_NEXT_TERMINATE);

	req->tail = dtd;

	वापस 0;
पूर्ण

/* queues (submits) an I/O request to an endpoपूर्णांक */
अटल पूर्णांक
fsl_ep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req, gfp_t gfp_flags)
अणु
	काष्ठा fsl_ep *ep = container_of(_ep, काष्ठा fsl_ep, ep);
	काष्ठा fsl_req *req = container_of(_req, काष्ठा fsl_req, req);
	काष्ठा fsl_udc *udc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* catch various bogus parameters */
	अगर (!_req || !req->req.complete || !req->req.buf
			|| !list_empty(&req->queue)) अणु
		VDBG("%s, bad params", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (unlikely(!_ep || !ep->ep.desc)) अणु
		VDBG("%s, bad ep", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (usb_endpoपूर्णांक_xfer_isoc(ep->ep.desc)) अणु
		अगर (req->req.length > ep->ep.maxpacket)
			वापस -EMSGSIZE;
	पूर्ण

	udc = ep->udc;
	अगर (!udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	req->ep = ep;

	ret = usb_gadget_map_request(&ep->udc->gadget, &req->req, ep_is_in(ep));
	अगर (ret)
		वापस ret;

	req->req.status = -EINPROGRESS;
	req->req.actual = 0;
	req->dtd_count = 0;

	/* build dtds and push them to device queue */
	अगर (!fsl_req_to_dtd(req, gfp_flags)) अणु
		spin_lock_irqsave(&udc->lock, flags);
		fsl_queue_td(ep, req);
	पूर्ण अन्यथा अणु
		वापस -ENOMEM;
	पूर्ण

	/* irq handler advances the queue */
	अगर (req != शून्य)
		list_add_tail(&req->queue, &ep->queue);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/* dequeues (cancels, unlinks) an I/O request from an endpoपूर्णांक */
अटल पूर्णांक fsl_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा fsl_ep *ep = container_of(_ep, काष्ठा fsl_ep, ep);
	काष्ठा fsl_req *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक ep_num, stopped, ret = 0;
	u32 epctrl;

	अगर (!_ep || !_req)
		वापस -EINVAL;

	spin_lock_irqsave(&ep->udc->lock, flags);
	stopped = ep->stopped;

	/* Stop the ep beक्रमe we deal with the queue */
	ep->stopped = 1;
	ep_num = ep_index(ep);
	epctrl = fsl_पढ़ोl(&dr_regs->endptctrl[ep_num]);
	अगर (ep_is_in(ep))
		epctrl &= ~EPCTRL_TX_ENABLE;
	अन्यथा
		epctrl &= ~EPCTRL_RX_ENABLE;
	fsl_ग_लिखोl(epctrl, &dr_regs->endptctrl[ep_num]);

	/* make sure it's actually queued on this endpoपूर्णांक */
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->req == _req)
			अवरोध;
	पूर्ण
	अगर (&req->req != _req) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* The request is in progress, or completed but not dequeued */
	अगर (ep->queue.next == &req->queue) अणु
		_req->status = -ECONNRESET;
		fsl_ep_fअगरo_flush(_ep);	/* flush current transfer */

		/* The request isn't the last request in this ep queue */
		अगर (req->queue.next != &ep->queue) अणु
			काष्ठा fsl_req *next_req;

			next_req = list_entry(req->queue.next, काष्ठा fsl_req,
					queue);

			/* prime with dTD of next request */
			fsl_prime_ep(ep, next_req->head);
		पूर्ण
	/* The request hasn't been processed, patch up the TD chain */
	पूर्ण अन्यथा अणु
		काष्ठा fsl_req *prev_req;

		prev_req = list_entry(req->queue.prev, काष्ठा fsl_req, queue);
		prev_req->tail->next_td_ptr = req->tail->next_td_ptr;
	पूर्ण

	करोne(ep, req, -ECONNRESET);

	/* Enable EP */
out:	epctrl = fsl_पढ़ोl(&dr_regs->endptctrl[ep_num]);
	अगर (ep_is_in(ep))
		epctrl |= EPCTRL_TX_ENABLE;
	अन्यथा
		epctrl |= EPCTRL_RX_ENABLE;
	fsl_ग_लिखोl(epctrl, &dr_regs->endptctrl[ep_num]);
	ep->stopped = stopped;

	spin_unlock_irqrestore(&ep->udc->lock, flags);
	वापस ret;
पूर्ण

/*-------------------------------------------------------------------------*/

/*-----------------------------------------------------------------
 * modअगरy the endpoपूर्णांक halt feature
 * @ep: the non-isochronous endpoपूर्णांक being stalled
 * @value: 1--set halt  0--clear halt
 * Returns zero, or a negative error code.
*----------------------------------------------------------------*/
अटल पूर्णांक fsl_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा fsl_ep *ep = शून्य;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक status = -EOPNOTSUPP;	/* operation not supported */
	अचिन्हित अक्षर ep_dir = 0, ep_num = 0;
	काष्ठा fsl_udc *udc = शून्य;

	ep = container_of(_ep, काष्ठा fsl_ep, ep);
	udc = ep->udc;
	अगर (!_ep || !ep->ep.desc) अणु
		status = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (usb_endpoपूर्णांक_xfer_isoc(ep->ep.desc)) अणु
		status = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/* Attempt to halt IN ep will fail अगर any transfer requests
	 * are still queue */
	अगर (value && ep_is_in(ep) && !list_empty(&ep->queue)) अणु
		status = -EAGAIN;
		जाओ out;
	पूर्ण

	status = 0;
	ep_dir = ep_is_in(ep) ? USB_SEND : USB_RECV;
	ep_num = (अचिन्हित अक्षर)(ep_index(ep));
	spin_lock_irqsave(&ep->udc->lock, flags);
	dr_ep_change_stall(ep_num, ep_dir, value);
	spin_unlock_irqrestore(&ep->udc->lock, flags);

	अगर (ep_index(ep) == 0) अणु
		udc->ep0_state = WAIT_FOR_SETUP;
		udc->ep0_dir = 0;
	पूर्ण
out:
	VDBG(" %s %s halt stat %d", ep->ep.name,
			value ?  "set" : "clear", status);

	वापस status;
पूर्ण

अटल पूर्णांक fsl_ep_fअगरo_status(काष्ठा usb_ep *_ep)
अणु
	काष्ठा fsl_ep *ep;
	काष्ठा fsl_udc *udc;
	पूर्णांक size = 0;
	u32 biपंचांगask;
	काष्ठा ep_queue_head *qh;

	अगर (!_ep || !_ep->desc || !(_ep->desc->bEndpoपूर्णांकAddress&0xF))
		वापस -ENODEV;

	ep = container_of(_ep, काष्ठा fsl_ep, ep);

	udc = (काष्ठा fsl_udc *)ep->udc;

	अगर (!udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	qh = get_qh_by_ep(ep);

	biपंचांगask = (ep_is_in(ep)) ? (1 << (ep_index(ep) + 16)) :
	    (1 << (ep_index(ep)));

	अगर (fsl_पढ़ोl(&dr_regs->endptstatus) & biपंचांगask)
		size = (qh->size_ioc_पूर्णांक_sts & DTD_PACKET_SIZE)
		    >> DTD_LENGTH_BIT_POS;

	pr_debug("%s %u\n", __func__, size);
	वापस size;
पूर्ण

अटल व्योम fsl_ep_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	काष्ठा fsl_ep *ep;
	पूर्णांक ep_num, ep_dir;
	u32 bits;
	अचिन्हित दीर्घ समयout;
#घोषणा FSL_UDC_FLUSH_TIMEOUT 1000

	अगर (!_ep) अणु
		वापस;
	पूर्ण अन्यथा अणु
		ep = container_of(_ep, काष्ठा fsl_ep, ep);
		अगर (!ep->ep.desc)
			वापस;
	पूर्ण
	ep_num = ep_index(ep);
	ep_dir = ep_is_in(ep) ? USB_SEND : USB_RECV;

	अगर (ep_num == 0)
		bits = (1 << 16) | 1;
	अन्यथा अगर (ep_dir == USB_SEND)
		bits = 1 << (16 + ep_num);
	अन्यथा
		bits = 1 << ep_num;

	समयout = jअगरfies + FSL_UDC_FLUSH_TIMEOUT;
	करो अणु
		fsl_ग_लिखोl(bits, &dr_regs->endptflush);

		/* Wait until flush complete */
		जबतक (fsl_पढ़ोl(&dr_regs->endptflush)) अणु
			अगर (समय_after(jअगरfies, समयout)) अणु
				ERR("ep flush timeout\n");
				वापस;
			पूर्ण
			cpu_relax();
		पूर्ण
		/* See अगर we need to flush again */
	पूर्ण जबतक (fsl_पढ़ोl(&dr_regs->endptstatus) & bits);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops fsl_ep_ops = अणु
	.enable = fsl_ep_enable,
	.disable = fsl_ep_disable,

	.alloc_request = fsl_alloc_request,
	.मुक्त_request = fsl_मुक्त_request,

	.queue = fsl_ep_queue,
	.dequeue = fsl_ep_dequeue,

	.set_halt = fsl_ep_set_halt,
	.fअगरo_status = fsl_ep_fअगरo_status,
	.fअगरo_flush = fsl_ep_fअगरo_flush,	/* flush fअगरo */
पूर्ण;

/*-------------------------------------------------------------------------
		Gadget Driver Layer Operations
-------------------------------------------------------------------------*/

/*----------------------------------------------------------------------
 * Get the current frame number (from DR frame_index Reg )
 *----------------------------------------------------------------------*/
अटल पूर्णांक fsl_get_frame(काष्ठा usb_gadget *gadget)
अणु
	वापस (पूर्णांक)(fsl_पढ़ोl(&dr_regs->frindex) & USB_FRINDEX_MASKS);
पूर्ण

/*-----------------------------------------------------------------------
 * Tries to wake up the host connected to this gadget
 -----------------------------------------------------------------------*/
अटल पूर्णांक fsl_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा fsl_udc *udc = container_of(gadget, काष्ठा fsl_udc, gadget);
	u32 portsc;

	/* Remote wakeup feature not enabled by host */
	अगर (!udc->remote_wakeup)
		वापस -ENOTSUPP;

	portsc = fsl_पढ़ोl(&dr_regs->portsc1);
	/* not suspended? */
	अगर (!(portsc & PORTSCX_PORT_SUSPEND))
		वापस 0;
	/* trigger क्रमce resume */
	portsc |= PORTSCX_PORT_FORCE_RESUME;
	fsl_ग_लिखोl(portsc, &dr_regs->portsc1);
	वापस 0;
पूर्ण

अटल पूर्णांक can_pullup(काष्ठा fsl_udc *udc)
अणु
	वापस udc->driver && udc->softconnect && udc->vbus_active;
पूर्ण

/* Notअगरy controller that VBUS is घातered, Called by whatever
   detects VBUS sessions */
अटल पूर्णांक fsl_vbus_session(काष्ठा usb_gadget *gadget, पूर्णांक is_active)
अणु
	काष्ठा fsl_udc	*udc;
	अचिन्हित दीर्घ	flags;

	udc = container_of(gadget, काष्ठा fsl_udc, gadget);
	spin_lock_irqsave(&udc->lock, flags);
	VDBG("VBUS %s", is_active ? "on" : "off");
	udc->vbus_active = (is_active != 0);
	अगर (can_pullup(udc))
		fsl_ग_लिखोl((fsl_पढ़ोl(&dr_regs->usbcmd) | USB_CMD_RUN_STOP),
				&dr_regs->usbcmd);
	अन्यथा
		fsl_ग_लिखोl((fsl_पढ़ोl(&dr_regs->usbcmd) & ~USB_CMD_RUN_STOP),
				&dr_regs->usbcmd);
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

/* स्थिरrain controller's VBUS घातer usage
 * This call is used by gadget drivers during SET_CONFIGURATION calls,
 * reporting how much घातer the device may consume.  For example, this
 * could affect how quickly batteries are reअक्षरged.
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
अटल पूर्णांक fsl_vbus_draw(काष्ठा usb_gadget *gadget, अचिन्हित mA)
अणु
	काष्ठा fsl_udc *udc;

	udc = container_of(gadget, काष्ठा fsl_udc, gadget);
	अगर (!IS_ERR_OR_शून्य(udc->transceiver))
		वापस usb_phy_set_घातer(udc->transceiver, mA);
	वापस -ENOTSUPP;
पूर्ण

/* Change Data+ pullup status
 * this func is used by usb_gadget_connect/disconnect
 */
अटल पूर्णांक fsl_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा fsl_udc *udc;

	udc = container_of(gadget, काष्ठा fsl_udc, gadget);

	अगर (!udc->vbus_active)
		वापस -EOPNOTSUPP;

	udc->softconnect = (is_on != 0);
	अगर (can_pullup(udc))
		fsl_ग_लिखोl((fsl_पढ़ोl(&dr_regs->usbcmd) | USB_CMD_RUN_STOP),
				&dr_regs->usbcmd);
	अन्यथा
		fsl_ग_लिखोl((fsl_पढ़ोl(&dr_regs->usbcmd) & ~USB_CMD_RUN_STOP),
				&dr_regs->usbcmd);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक fsl_udc_stop(काष्ठा usb_gadget *g);

अटल स्थिर काष्ठा usb_gadget_ops fsl_gadget_ops = अणु
	.get_frame = fsl_get_frame,
	.wakeup = fsl_wakeup,
/*	.set_selfघातered = fsl_set_selfघातered,	*/ /* Always selfघातered */
	.vbus_session = fsl_vbus_session,
	.vbus_draw = fsl_vbus_draw,
	.pullup = fsl_pullup,
	.udc_start = fsl_udc_start,
	.udc_stop = fsl_udc_stop,
पूर्ण;

/*
 * Empty complete function used by this driver to fill in the req->complete
 * field when creating a request since the complete field is mandatory.
 */
अटल व्योम fsl_noop_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req) अणु पूर्ण

/* Set protocol stall on ep0, protocol stall will स्वतःmatically be cleared
   on new transaction */
अटल व्योम ep0stall(काष्ठा fsl_udc *udc)
अणु
	u32 पंचांगp;

	/* must set tx and rx to stall at the same समय */
	पंचांगp = fsl_पढ़ोl(&dr_regs->endptctrl[0]);
	पंचांगp |= EPCTRL_TX_EP_STALL | EPCTRL_RX_EP_STALL;
	fsl_ग_लिखोl(पंचांगp, &dr_regs->endptctrl[0]);
	udc->ep0_state = WAIT_FOR_SETUP;
	udc->ep0_dir = 0;
पूर्ण

/* Prime a status phase क्रम ep0 */
अटल पूर्णांक ep0_prime_status(काष्ठा fsl_udc *udc, पूर्णांक direction)
अणु
	काष्ठा fsl_req *req = udc->status_req;
	काष्ठा fsl_ep *ep;
	पूर्णांक ret;

	अगर (direction == EP_सूची_IN)
		udc->ep0_dir = USB_सूची_IN;
	अन्यथा
		udc->ep0_dir = USB_सूची_OUT;

	ep = &udc->eps[0];
	अगर (udc->ep0_state != DATA_STATE_XMIT)
		udc->ep0_state = WAIT_FOR_OUT_STATUS;

	req->ep = ep;
	req->req.length = 0;
	req->req.status = -EINPROGRESS;
	req->req.actual = 0;
	req->req.complete = fsl_noop_complete;
	req->dtd_count = 0;

	ret = usb_gadget_map_request(&ep->udc->gadget, &req->req, ep_is_in(ep));
	अगर (ret)
		वापस ret;

	अगर (fsl_req_to_dtd(req, GFP_ATOMIC) == 0)
		fsl_queue_td(ep, req);
	अन्यथा
		वापस -ENOMEM;

	list_add_tail(&req->queue, &ep->queue);

	वापस 0;
पूर्ण

अटल व्योम udc_reset_ep_queue(काष्ठा fsl_udc *udc, u8 pipe)
अणु
	काष्ठा fsl_ep *ep = get_ep_by_pipe(udc, pipe);

	अगर (ep->ep.name)
		nuke(ep, -ESHUTDOWN);
पूर्ण

/*
 * ch9 Set address
 */
अटल व्योम ch9setaddress(काष्ठा fsl_udc *udc, u16 value, u16 index, u16 length)
अणु
	/* Save the new address to device काष्ठा */
	udc->device_address = (u8) value;
	/* Update usb state */
	udc->usb_state = USB_STATE_ADDRESS;
	/* Status phase */
	अगर (ep0_prime_status(udc, EP_सूची_IN))
		ep0stall(udc);
पूर्ण

/*
 * ch9 Get status
 */
अटल व्योम ch9माला_लोtatus(काष्ठा fsl_udc *udc, u8 request_type, u16 value,
		u16 index, u16 length)
अणु
	u16 पंचांगp = 0;		/* Status, cpu endian */
	काष्ठा fsl_req *req;
	काष्ठा fsl_ep *ep;
	पूर्णांक ret;

	ep = &udc->eps[0];

	अगर ((request_type & USB_RECIP_MASK) == USB_RECIP_DEVICE) अणु
		/* Get device status */
		पंचांगp = udc->gadget.is_selfघातered;
		पंचांगp |= udc->remote_wakeup << USB_DEVICE_REMOTE_WAKEUP;
	पूर्ण अन्यथा अगर ((request_type & USB_RECIP_MASK) == USB_RECIP_INTERFACE) अणु
		/* Get पूर्णांकerface status */
		/* We करोn't have पूर्णांकerface inक्रमmation in udc driver */
		पंचांगp = 0;
	पूर्ण अन्यथा अगर ((request_type & USB_RECIP_MASK) == USB_RECIP_ENDPOINT) अणु
		/* Get endpoपूर्णांक status */
		काष्ठा fsl_ep *target_ep;

		target_ep = get_ep_by_pipe(udc, get_pipe_by_windex(index));

		/* stall अगर endpoपूर्णांक करोesn't exist */
		अगर (!target_ep->ep.desc)
			जाओ stall;
		पंचांगp = dr_ep_get_stall(ep_index(target_ep), ep_is_in(target_ep))
				<< USB_ENDPOINT_HALT;
	पूर्ण

	udc->ep0_dir = USB_सूची_IN;
	/* Borrow the per device status_req */
	req = udc->status_req;
	/* Fill in the reqest काष्ठाure */
	*((u16 *) req->req.buf) = cpu_to_le16(पंचांगp);

	req->ep = ep;
	req->req.length = 2;
	req->req.status = -EINPROGRESS;
	req->req.actual = 0;
	req->req.complete = fsl_noop_complete;
	req->dtd_count = 0;

	ret = usb_gadget_map_request(&ep->udc->gadget, &req->req, ep_is_in(ep));
	अगर (ret)
		जाओ stall;

	/* prime the data phase */
	अगर ((fsl_req_to_dtd(req, GFP_ATOMIC) == 0))
		fsl_queue_td(ep, req);
	अन्यथा			/* no mem */
		जाओ stall;

	list_add_tail(&req->queue, &ep->queue);
	udc->ep0_state = DATA_STATE_XMIT;
	अगर (ep0_prime_status(udc, EP_सूची_OUT))
		ep0stall(udc);

	वापस;
stall:
	ep0stall(udc);
पूर्ण

अटल व्योम setup_received_irq(काष्ठा fsl_udc *udc,
		काष्ठा usb_ctrlrequest *setup)
__releases(udc->lock)
__acquires(udc->lock)
अणु
	u16 wValue = le16_to_cpu(setup->wValue);
	u16 wIndex = le16_to_cpu(setup->wIndex);
	u16 wLength = le16_to_cpu(setup->wLength);

	udc_reset_ep_queue(udc, 0);

	/* We process some stardard setup requests here */
	चयन (setup->bRequest) अणु
	हाल USB_REQ_GET_STATUS:
		/* Data+Status phase from udc */
		अगर ((setup->bRequestType & (USB_सूची_IN | USB_TYPE_MASK))
					!= (USB_सूची_IN | USB_TYPE_STANDARD))
			अवरोध;
		ch9माला_लोtatus(udc, setup->bRequestType, wValue, wIndex, wLength);
		वापस;

	हाल USB_REQ_SET_ADDRESS:
		/* Status phase from udc */
		अगर (setup->bRequestType != (USB_सूची_OUT | USB_TYPE_STANDARD
						| USB_RECIP_DEVICE))
			अवरोध;
		ch9setaddress(udc, wValue, wIndex, wLength);
		वापस;

	हाल USB_REQ_CLEAR_FEATURE:
	हाल USB_REQ_SET_FEATURE:
		/* Status phase from udc */
	अणु
		पूर्णांक rc = -EOPNOTSUPP;
		u16 ptc = 0;

		अगर ((setup->bRequestType & (USB_RECIP_MASK | USB_TYPE_MASK))
				== (USB_RECIP_ENDPOINT | USB_TYPE_STANDARD)) अणु
			पूर्णांक pipe = get_pipe_by_windex(wIndex);
			काष्ठा fsl_ep *ep;

			अगर (wValue != 0 || wLength != 0 || pipe >= udc->max_ep)
				अवरोध;
			ep = get_ep_by_pipe(udc, pipe);

			spin_unlock(&udc->lock);
			rc = fsl_ep_set_halt(&ep->ep,
					(setup->bRequest == USB_REQ_SET_FEATURE)
						? 1 : 0);
			spin_lock(&udc->lock);

		पूर्ण अन्यथा अगर ((setup->bRequestType & (USB_RECIP_MASK
				| USB_TYPE_MASK)) == (USB_RECIP_DEVICE
				| USB_TYPE_STANDARD)) अणु
			/* Note: The driver has not include OTG support yet.
			 * This will be set when OTG support is added */
			अगर (wValue == USB_DEVICE_TEST_MODE)
				ptc = wIndex >> 8;
			अन्यथा अगर (gadget_is_otg(&udc->gadget)) अणु
				अगर (setup->bRequest ==
				    USB_DEVICE_B_HNP_ENABLE)
					udc->gadget.b_hnp_enable = 1;
				अन्यथा अगर (setup->bRequest ==
					 USB_DEVICE_A_HNP_SUPPORT)
					udc->gadget.a_hnp_support = 1;
				अन्यथा अगर (setup->bRequest ==
					 USB_DEVICE_A_ALT_HNP_SUPPORT)
					udc->gadget.a_alt_hnp_support = 1;
			पूर्ण
			rc = 0;
		पूर्ण अन्यथा
			अवरोध;

		अगर (rc == 0) अणु
			अगर (ep0_prime_status(udc, EP_सूची_IN))
				ep0stall(udc);
		पूर्ण
		अगर (ptc) अणु
			u32 पंचांगp;

			mdelay(10);
			पंचांगp = fsl_पढ़ोl(&dr_regs->portsc1) | (ptc << 16);
			fsl_ग_लिखोl(पंचांगp, &dr_regs->portsc1);
			prपूर्णांकk(KERN_INFO "udc: switch to test mode %d.\n", ptc);
		पूर्ण

		वापस;
	पूर्ण

	शेष:
		अवरोध;
	पूर्ण

	/* Requests handled by gadget */
	अगर (wLength) अणु
		/* Data phase from gadget, status phase from udc */
		udc->ep0_dir = (setup->bRequestType & USB_सूची_IN)
				?  USB_सूची_IN : USB_सूची_OUT;
		spin_unlock(&udc->lock);
		अगर (udc->driver->setup(&udc->gadget,
				&udc->local_setup_buff) < 0)
			ep0stall(udc);
		spin_lock(&udc->lock);
		udc->ep0_state = (setup->bRequestType & USB_सूची_IN)
				?  DATA_STATE_XMIT : DATA_STATE_RECV;
		/*
		 * If the data stage is IN, send status prime immediately.
		 * See 2.0 Spec chapter 8.5.3.3 क्रम detail.
		 */
		अगर (udc->ep0_state == DATA_STATE_XMIT)
			अगर (ep0_prime_status(udc, EP_सूची_OUT))
				ep0stall(udc);

	पूर्ण अन्यथा अणु
		/* No data phase, IN status from gadget */
		udc->ep0_dir = USB_सूची_IN;
		spin_unlock(&udc->lock);
		अगर (udc->driver->setup(&udc->gadget,
				&udc->local_setup_buff) < 0)
			ep0stall(udc);
		spin_lock(&udc->lock);
		udc->ep0_state = WAIT_FOR_OUT_STATUS;
	पूर्ण
पूर्ण

/* Process request क्रम Data or Status phase of ep0
 * prime status phase अगर needed */
अटल व्योम ep0_req_complete(काष्ठा fsl_udc *udc, काष्ठा fsl_ep *ep0,
		काष्ठा fsl_req *req)
अणु
	अगर (udc->usb_state == USB_STATE_ADDRESS) अणु
		/* Set the new address */
		u32 new_address = (u32) udc->device_address;
		fsl_ग_लिखोl(new_address << USB_DEVICE_ADDRESS_BIT_POS,
				&dr_regs->deviceaddr);
	पूर्ण

	करोne(ep0, req, 0);

	चयन (udc->ep0_state) अणु
	हाल DATA_STATE_XMIT:
		/* alपढ़ोy primed at setup_received_irq */
		udc->ep0_state = WAIT_FOR_OUT_STATUS;
		अवरोध;
	हाल DATA_STATE_RECV:
		/* send status phase */
		अगर (ep0_prime_status(udc, EP_सूची_IN))
			ep0stall(udc);
		अवरोध;
	हाल WAIT_FOR_OUT_STATUS:
		udc->ep0_state = WAIT_FOR_SETUP;
		अवरोध;
	हाल WAIT_FOR_SETUP:
		ERR("Unexpected ep0 packets\n");
		अवरोध;
	शेष:
		ep0stall(udc);
		अवरोध;
	पूर्ण
पूर्ण

/* Tripwire mechanism to ensure a setup packet payload is extracted without
 * being corrupted by another incoming setup packet */
अटल व्योम tripwire_handler(काष्ठा fsl_udc *udc, u8 ep_num, u8 *buffer_ptr)
अणु
	u32 temp;
	काष्ठा ep_queue_head *qh;
	काष्ठा fsl_usb2_platक्रमm_data *pdata = udc->pdata;

	qh = &udc->ep_qh[ep_num * 2 + EP_सूची_OUT];

	/* Clear bit in ENDPTSETUPSTAT */
	temp = fsl_पढ़ोl(&dr_regs->endptsetupstat);
	fsl_ग_लिखोl(temp | (1 << ep_num), &dr_regs->endptsetupstat);

	/* जबतक a hazard exists when setup package arrives */
	करो अणु
		/* Set Setup Tripwire */
		temp = fsl_पढ़ोl(&dr_regs->usbcmd);
		fsl_ग_लिखोl(temp | USB_CMD_SUTW, &dr_regs->usbcmd);

		/* Copy the setup packet to local buffer */
		अगर (pdata->le_setup_buf) अणु
			u32 *p = (u32 *)buffer_ptr;
			u32 *s = (u32 *)qh->setup_buffer;

			/* Convert little endian setup buffer to CPU endian */
			*p++ = le32_to_cpu(*s++);
			*p = le32_to_cpu(*s);
		पूर्ण अन्यथा अणु
			स_नकल(buffer_ptr, (u8 *) qh->setup_buffer, 8);
		पूर्ण
	पूर्ण जबतक (!(fsl_पढ़ोl(&dr_regs->usbcmd) & USB_CMD_SUTW));

	/* Clear Setup Tripwire */
	temp = fsl_पढ़ोl(&dr_regs->usbcmd);
	fsl_ग_लिखोl(temp & ~USB_CMD_SUTW, &dr_regs->usbcmd);
पूर्ण

/* process-ep_req(): मुक्त the completed Tds क्रम this req */
अटल पूर्णांक process_ep_req(काष्ठा fsl_udc *udc, पूर्णांक pipe,
		काष्ठा fsl_req *curr_req)
अणु
	काष्ठा ep_td_काष्ठा *curr_td;
	पूर्णांक	actual, reमुख्यing_length, j, पंचांगp;
	पूर्णांक	status = 0;
	पूर्णांक	errors = 0;
	काष्ठा  ep_queue_head *curr_qh = &udc->ep_qh[pipe];
	पूर्णांक direction = pipe % 2;

	curr_td = curr_req->head;
	actual = curr_req->req.length;

	क्रम (j = 0; j < curr_req->dtd_count; j++) अणु
		reमुख्यing_length = (hc32_to_cpu(curr_td->size_ioc_sts)
					& DTD_PACKET_SIZE)
				>> DTD_LENGTH_BIT_POS;
		actual -= reमुख्यing_length;

		errors = hc32_to_cpu(curr_td->size_ioc_sts);
		अगर (errors & DTD_ERROR_MASK) अणु
			अगर (errors & DTD_STATUS_HALTED) अणु
				ERR("dTD error %08x QH=%d\n", errors, pipe);
				/* Clear the errors and Halt condition */
				पंचांगp = hc32_to_cpu(curr_qh->size_ioc_पूर्णांक_sts);
				पंचांगp &= ~errors;
				curr_qh->size_ioc_पूर्णांक_sts = cpu_to_hc32(पंचांगp);
				status = -EPIPE;
				/* FIXME: जारी with next queued TD? */

				अवरोध;
			पूर्ण
			अगर (errors & DTD_STATUS_DATA_BUFF_ERR) अणु
				VDBG("Transfer overflow");
				status = -EPROTO;
				अवरोध;
			पूर्ण अन्यथा अगर (errors & DTD_STATUS_TRANSACTION_ERR) अणु
				VDBG("ISO error");
				status = -EILSEQ;
				अवरोध;
			पूर्ण अन्यथा
				ERR("Unknown error has occurred (0x%x)!\n",
					errors);

		पूर्ण अन्यथा अगर (hc32_to_cpu(curr_td->size_ioc_sts)
				& DTD_STATUS_ACTIVE) अणु
			VDBG("Request not complete");
			status = REQ_UNCOMPLETE;
			वापस status;
		पूर्ण अन्यथा अगर (reमुख्यing_length) अणु
			अगर (direction) अणु
				VDBG("Transmit dTD remaining length not zero");
				status = -EPROTO;
				अवरोध;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			VDBG("dTD transmitted successful");
		पूर्ण

		अगर (j != curr_req->dtd_count - 1)
			curr_td = (काष्ठा ep_td_काष्ठा *)curr_td->next_td_virt;
	पूर्ण

	अगर (status)
		वापस status;

	curr_req->req.actual = actual;

	वापस 0;
पूर्ण

/* Process a DTD completion पूर्णांकerrupt */
अटल व्योम dtd_complete_irq(काष्ठा fsl_udc *udc)
अणु
	u32 bit_pos;
	पूर्णांक i, ep_num, direction, bit_mask, status;
	काष्ठा fsl_ep *curr_ep;
	काष्ठा fsl_req *curr_req, *temp_req;

	/* Clear the bits in the रेजिस्टर */
	bit_pos = fsl_पढ़ोl(&dr_regs->endptcomplete);
	fsl_ग_लिखोl(bit_pos, &dr_regs->endptcomplete);

	अगर (!bit_pos)
		वापस;

	क्रम (i = 0; i < udc->max_ep; i++) अणु
		ep_num = i >> 1;
		direction = i % 2;

		bit_mask = 1 << (ep_num + 16 * direction);

		अगर (!(bit_pos & bit_mask))
			जारी;

		curr_ep = get_ep_by_pipe(udc, i);

		/* If the ep is configured */
		अगर (!curr_ep->ep.name) अणु
			WARNING("Invalid EP?");
			जारी;
		पूर्ण

		/* process the req queue until an uncomplete request */
		list_क्रम_each_entry_safe(curr_req, temp_req, &curr_ep->queue,
				queue) अणु
			status = process_ep_req(udc, i, curr_req);

			VDBG("status of process_ep_req= %d, ep = %d",
					status, ep_num);
			अगर (status == REQ_UNCOMPLETE)
				अवरोध;
			/* ग_लिखो back status to req */
			curr_req->req.status = status;

			अगर (ep_num == 0) अणु
				ep0_req_complete(udc, curr_ep, curr_req);
				अवरोध;
			पूर्ण अन्यथा
				करोne(curr_ep, curr_req, status);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत usb_device_speed portscx_device_speed(u32 reg)
अणु
	चयन (reg & PORTSCX_PORT_SPEED_MASK) अणु
	हाल PORTSCX_PORT_SPEED_HIGH:
		वापस USB_SPEED_HIGH;
	हाल PORTSCX_PORT_SPEED_FULL:
		वापस USB_SPEED_FULL;
	हाल PORTSCX_PORT_SPEED_LOW:
		वापस USB_SPEED_LOW;
	शेष:
		वापस USB_SPEED_UNKNOWN;
	पूर्ण
पूर्ण

/* Process a port change पूर्णांकerrupt */
अटल व्योम port_change_irq(काष्ठा fsl_udc *udc)
अणु
	अगर (udc->bus_reset)
		udc->bus_reset = 0;

	/* Bus resetting is finished */
	अगर (!(fsl_पढ़ोl(&dr_regs->portsc1) & PORTSCX_PORT_RESET))
		/* Get the speed */
		udc->gadget.speed =
			portscx_device_speed(fsl_पढ़ोl(&dr_regs->portsc1));

	/* Update USB state */
	अगर (!udc->resume_state)
		udc->usb_state = USB_STATE_DEFAULT;
पूर्ण

/* Process suspend पूर्णांकerrupt */
अटल व्योम suspend_irq(काष्ठा fsl_udc *udc)
अणु
	udc->resume_state = udc->usb_state;
	udc->usb_state = USB_STATE_SUSPENDED;

	/* report suspend to the driver, serial.c करोes not support this */
	अगर (udc->driver->suspend)
		udc->driver->suspend(&udc->gadget);
पूर्ण

अटल व्योम bus_resume(काष्ठा fsl_udc *udc)
अणु
	udc->usb_state = udc->resume_state;
	udc->resume_state = 0;

	/* report resume to the driver, serial.c करोes not support this */
	अगर (udc->driver->resume)
		udc->driver->resume(&udc->gadget);
पूर्ण

/* Clear up all ep queues */
अटल पूर्णांक reset_queues(काष्ठा fsl_udc *udc, bool bus_reset)
अणु
	u8 pipe;

	क्रम (pipe = 0; pipe < udc->max_pipes; pipe++)
		udc_reset_ep_queue(udc, pipe);

	/* report disconnect; the driver is alपढ़ोy quiesced */
	spin_unlock(&udc->lock);
	अगर (bus_reset)
		usb_gadget_udc_reset(&udc->gadget, udc->driver);
	अन्यथा
		udc->driver->disconnect(&udc->gadget);
	spin_lock(&udc->lock);

	वापस 0;
पूर्ण

/* Process reset पूर्णांकerrupt */
अटल व्योम reset_irq(काष्ठा fsl_udc *udc)
अणु
	u32 temp;
	अचिन्हित दीर्घ समयout;

	/* Clear the device address */
	temp = fsl_पढ़ोl(&dr_regs->deviceaddr);
	fsl_ग_लिखोl(temp & ~USB_DEVICE_ADDRESS_MASK, &dr_regs->deviceaddr);

	udc->device_address = 0;

	/* Clear usb state */
	udc->resume_state = 0;
	udc->ep0_dir = 0;
	udc->ep0_state = WAIT_FOR_SETUP;
	udc->remote_wakeup = 0;	/* शेष to 0 on reset */
	udc->gadget.b_hnp_enable = 0;
	udc->gadget.a_hnp_support = 0;
	udc->gadget.a_alt_hnp_support = 0;

	/* Clear all the setup token semaphores */
	temp = fsl_पढ़ोl(&dr_regs->endptsetupstat);
	fsl_ग_लिखोl(temp, &dr_regs->endptsetupstat);

	/* Clear all the endpoपूर्णांक complete status bits */
	temp = fsl_पढ़ोl(&dr_regs->endptcomplete);
	fsl_ग_लिखोl(temp, &dr_regs->endptcomplete);

	समयout = jअगरfies + 100;
	जबतक (fsl_पढ़ोl(&dr_regs->endpoपूर्णांकprime)) अणु
		/* Wait until all endptprime bits cleared */
		अगर (समय_after(jअगरfies, समयout)) अणु
			ERR("Timeout for reset\n");
			अवरोध;
		पूर्ण
		cpu_relax();
	पूर्ण

	/* Write 1s to the flush रेजिस्टर */
	fsl_ग_लिखोl(0xffffffff, &dr_regs->endptflush);

	अगर (fsl_पढ़ोl(&dr_regs->portsc1) & PORTSCX_PORT_RESET) अणु
		VDBG("Bus reset");
		/* Bus is reseting */
		udc->bus_reset = 1;
		/* Reset all the queues, include XD, dTD, EP queue
		 * head and TR Queue */
		reset_queues(udc, true);
		udc->usb_state = USB_STATE_DEFAULT;
	पूर्ण अन्यथा अणु
		VDBG("Controller reset");
		/* initialize usb hw reg except क्रम regs क्रम EP, not
		 * touch usbपूर्णांकr reg */
		dr_controller_setup(udc);

		/* Reset all पूर्णांकernal used Queues */
		reset_queues(udc, false);

		ep0_setup(udc);

		/* Enable DR IRQ reg, Set Run bit, change udc state */
		dr_controller_run(udc);
		udc->usb_state = USB_STATE_ATTACHED;
	पूर्ण
पूर्ण

/*
 * USB device controller पूर्णांकerrupt handler
 */
अटल irqवापस_t fsl_udc_irq(पूर्णांक irq, व्योम *_udc)
अणु
	काष्ठा fsl_udc *udc = _udc;
	u32 irq_src;
	irqवापस_t status = IRQ_NONE;
	अचिन्हित दीर्घ flags;

	/* Disable ISR क्रम OTG host mode */
	अगर (udc->stopped)
		वापस IRQ_NONE;
	spin_lock_irqsave(&udc->lock, flags);
	irq_src = fsl_पढ़ोl(&dr_regs->usbsts) & fsl_पढ़ोl(&dr_regs->usbपूर्णांकr);
	/* Clear notअगरication bits */
	fsl_ग_लिखोl(irq_src, &dr_regs->usbsts);

	/* VDBG("irq_src [0x%8x]", irq_src); */

	/* Need to resume? */
	अगर (udc->usb_state == USB_STATE_SUSPENDED)
		अगर ((fsl_पढ़ोl(&dr_regs->portsc1) & PORTSCX_PORT_SUSPEND) == 0)
			bus_resume(udc);

	/* USB Interrupt */
	अगर (irq_src & USB_STS_INT) अणु
		VDBG("Packet int");
		/* Setup package, we only support ep0 as control ep */
		अगर (fsl_पढ़ोl(&dr_regs->endptsetupstat) & EP_SETUP_STATUS_EP0) अणु
			tripwire_handler(udc, 0,
					(u8 *) (&udc->local_setup_buff));
			setup_received_irq(udc, &udc->local_setup_buff);
			status = IRQ_HANDLED;
		पूर्ण

		/* completion of dtd */
		अगर (fsl_पढ़ोl(&dr_regs->endptcomplete)) अणु
			dtd_complete_irq(udc);
			status = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	/* SOF (क्रम ISO transfer) */
	अगर (irq_src & USB_STS_SOF) अणु
		status = IRQ_HANDLED;
	पूर्ण

	/* Port Change */
	अगर (irq_src & USB_STS_PORT_CHANGE) अणु
		port_change_irq(udc);
		status = IRQ_HANDLED;
	पूर्ण

	/* Reset Received */
	अगर (irq_src & USB_STS_RESET) अणु
		VDBG("reset int");
		reset_irq(udc);
		status = IRQ_HANDLED;
	पूर्ण

	/* Sleep Enable (Suspend) */
	अगर (irq_src & USB_STS_SUSPEND) अणु
		suspend_irq(udc);
		status = IRQ_HANDLED;
	पूर्ण

	अगर (irq_src & (USB_STS_ERR | USB_STS_SYS_ERR)) अणु
		VDBG("Error IRQ %x", irq_src);
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस status;
पूर्ण

/*----------------------------------------------------------------*
 * Hook to gadget drivers
 * Called by initialization code of gadget drivers
*----------------------------------------------------------------*/
अटल पूर्णांक fsl_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ flags = 0;

	/* lock is needed but whether should use this lock or another */
	spin_lock_irqsave(&udc_controller->lock, flags);

	driver->driver.bus = शून्य;
	/* hook up the driver */
	udc_controller->driver = driver;
	spin_unlock_irqrestore(&udc_controller->lock, flags);
	g->is_selfघातered = 1;

	अगर (!IS_ERR_OR_शून्य(udc_controller->transceiver)) अणु
		/* Suspend the controller until OTG enable it */
		udc_controller->stopped = 1;
		prपूर्णांकk(KERN_INFO "Suspend udc for OTG auto detect\n");

		/* connect to bus through transceiver */
		अगर (!IS_ERR_OR_शून्य(udc_controller->transceiver)) अणु
			retval = otg_set_peripheral(
					udc_controller->transceiver->otg,
						    &udc_controller->gadget);
			अगर (retval < 0) अणु
				ERR("can't bind to transceiver\n");
				udc_controller->driver = शून्य;
				वापस retval;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Enable DR IRQ reg and set USBCMD reg Run bit */
		dr_controller_run(udc_controller);
		udc_controller->usb_state = USB_STATE_ATTACHED;
		udc_controller->ep0_state = WAIT_FOR_SETUP;
		udc_controller->ep0_dir = 0;
	पूर्ण

	वापस retval;
पूर्ण

/* Disconnect from gadget driver */
अटल पूर्णांक fsl_udc_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा fsl_ep *loop_ep;
	अचिन्हित दीर्घ flags;

	अगर (!IS_ERR_OR_शून्य(udc_controller->transceiver))
		otg_set_peripheral(udc_controller->transceiver->otg, शून्य);

	/* stop DR, disable पूर्णांकr */
	dr_controller_stop(udc_controller);

	/* in fact, no needed */
	udc_controller->usb_state = USB_STATE_ATTACHED;
	udc_controller->ep0_state = WAIT_FOR_SETUP;
	udc_controller->ep0_dir = 0;

	/* stand operation */
	spin_lock_irqsave(&udc_controller->lock, flags);
	udc_controller->gadget.speed = USB_SPEED_UNKNOWN;
	nuke(&udc_controller->eps[0], -ESHUTDOWN);
	list_क्रम_each_entry(loop_ep, &udc_controller->gadget.ep_list,
			ep.ep_list)
		nuke(loop_ep, -ESHUTDOWN);
	spin_unlock_irqrestore(&udc_controller->lock, flags);

	udc_controller->driver = शून्य;

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------
		PROC File System Support
-------------------------------------------------------------------------*/
#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS

#समावेश <linux/seq_file.h>

अटल स्थिर अक्षर proc_filename[] = "driver/fsl_usb2_udc";

अटल पूर्णांक fsl_proc_पढ़ो(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	u32 पंचांगp_reg;
	काष्ठा fsl_ep *ep = शून्य;
	काष्ठा fsl_req *req;

	काष्ठा fsl_udc *udc = udc_controller;

	spin_lock_irqsave(&udc->lock, flags);

	/* ------basic driver inक्रमmation ---- */
	seq_म_लिखो(m,
			DRIVER_DESC "\n"
			"%s version: %s\n"
			"Gadget driver: %s\n\n",
			driver_name, DRIVER_VERSION,
			udc->driver ? udc->driver->driver.name : "(none)");

	/* ------ DR Registers ----- */
	पंचांगp_reg = fsl_पढ़ोl(&dr_regs->usbcmd);
	seq_म_लिखो(m,
			"USBCMD reg:\n"
			"SetupTW: %d\n"
			"Run/Stop: %s\n\n",
			(पंचांगp_reg & USB_CMD_SUTW) ? 1 : 0,
			(पंचांगp_reg & USB_CMD_RUN_STOP) ? "Run" : "Stop");

	पंचांगp_reg = fsl_पढ़ोl(&dr_regs->usbsts);
	seq_म_लिखो(m,
			"USB Status Reg:\n"
			"Dr Suspend: %d Reset Received: %d System Error: %s "
			"USB Error Interrupt: %s\n\n",
			(पंचांगp_reg & USB_STS_SUSPEND) ? 1 : 0,
			(पंचांगp_reg & USB_STS_RESET) ? 1 : 0,
			(पंचांगp_reg & USB_STS_SYS_ERR) ? "Err" : "Normal",
			(पंचांगp_reg & USB_STS_ERR) ? "Err detected" : "No err");

	पंचांगp_reg = fsl_पढ़ोl(&dr_regs->usbपूर्णांकr);
	seq_म_लिखो(m,
			"USB Interrupt Enable Reg:\n"
			"Sleep Enable: %d SOF Received Enable: %d "
			"Reset Enable: %d\n"
			"System Error Enable: %d "
			"Port Change Detected Enable: %d\n"
			"USB Error Intr Enable: %d USB Intr Enable: %d\n\n",
			(पंचांगp_reg & USB_INTR_DEVICE_SUSPEND) ? 1 : 0,
			(पंचांगp_reg & USB_INTR_SOF_EN) ? 1 : 0,
			(पंचांगp_reg & USB_INTR_RESET_EN) ? 1 : 0,
			(पंचांगp_reg & USB_INTR_SYS_ERR_EN) ? 1 : 0,
			(पंचांगp_reg & USB_INTR_PTC_DETECT_EN) ? 1 : 0,
			(पंचांगp_reg & USB_INTR_ERR_INT_EN) ? 1 : 0,
			(पंचांगp_reg & USB_INTR_INT_EN) ? 1 : 0);

	पंचांगp_reg = fsl_पढ़ोl(&dr_regs->frindex);
	seq_म_लिखो(m,
			"USB Frame Index Reg: Frame Number is 0x%x\n\n",
			(पंचांगp_reg & USB_FRINDEX_MASKS));

	पंचांगp_reg = fsl_पढ़ोl(&dr_regs->deviceaddr);
	seq_म_लिखो(m,
			"USB Device Address Reg: Device Addr is 0x%x\n\n",
			(पंचांगp_reg & USB_DEVICE_ADDRESS_MASK));

	पंचांगp_reg = fsl_पढ़ोl(&dr_regs->endpoपूर्णांकlistaddr);
	seq_म_लिखो(m,
			"USB Endpoint List Address Reg: "
			"Device Addr is 0x%x\n\n",
			(पंचांगp_reg & USB_EP_LIST_ADDRESS_MASK));

	पंचांगp_reg = fsl_पढ़ोl(&dr_regs->portsc1);
	seq_म_लिखो(m,
		"USB Port Status&Control Reg:\n"
		"Port Transceiver Type : %s Port Speed: %s\n"
		"PHY Low Power Suspend: %s Port Reset: %s "
		"Port Suspend Mode: %s\n"
		"Over-current Change: %s "
		"Port Enable/Disable Change: %s\n"
		"Port Enabled/Disabled: %s "
		"Current Connect Status: %s\n\n", ( अणु
			स्थिर अक्षर *s;
			चयन (पंचांगp_reg & PORTSCX_PTS_FSLS) अणु
			हाल PORTSCX_PTS_UTMI:
				s = "UTMI"; अवरोध;
			हाल PORTSCX_PTS_ULPI:
				s = "ULPI "; अवरोध;
			हाल PORTSCX_PTS_FSLS:
				s = "FS/LS Serial"; अवरोध;
			शेष:
				s = "None"; अवरोध;
			पूर्ण
			s;पूर्ण ),
		usb_speed_string(portscx_device_speed(पंचांगp_reg)),
		(पंचांगp_reg & PORTSCX_PHY_LOW_POWER_SPD) ?
		"Normal PHY mode" : "Low power mode",
		(पंचांगp_reg & PORTSCX_PORT_RESET) ? "In Reset" :
		"Not in Reset",
		(पंचांगp_reg & PORTSCX_PORT_SUSPEND) ? "In " : "Not in",
		(पंचांगp_reg & PORTSCX_OVER_CURRENT_CHG) ? "Dected" :
		"No",
		(पंचांगp_reg & PORTSCX_PORT_EN_DIS_CHANGE) ? "Disable" :
		"Not change",
		(पंचांगp_reg & PORTSCX_PORT_ENABLE) ? "Enable" :
		"Not correct",
		(पंचांगp_reg & PORTSCX_CURRENT_CONNECT_STATUS) ?
		"Attached" : "Not-Att");

	पंचांगp_reg = fsl_पढ़ोl(&dr_regs->usbmode);
	seq_म_लिखो(m,
			"USB Mode Reg: Controller Mode is: %s\n\n", ( अणु
				स्थिर अक्षर *s;
				चयन (पंचांगp_reg & USB_MODE_CTRL_MODE_HOST) अणु
				हाल USB_MODE_CTRL_MODE_IDLE:
					s = "Idle"; अवरोध;
				हाल USB_MODE_CTRL_MODE_DEVICE:
					s = "Device Controller"; अवरोध;
				हाल USB_MODE_CTRL_MODE_HOST:
					s = "Host Controller"; अवरोध;
				शेष:
					s = "None"; अवरोध;
				पूर्ण
				s;
			पूर्ण ));

	पंचांगp_reg = fsl_पढ़ोl(&dr_regs->endptsetupstat);
	seq_म_लिखो(m,
			"Endpoint Setup Status Reg: SETUP on ep 0x%x\n\n",
			(पंचांगp_reg & EP_SETUP_STATUS_MASK));

	क्रम (i = 0; i < udc->max_ep / 2; i++) अणु
		पंचांगp_reg = fsl_पढ़ोl(&dr_regs->endptctrl[i]);
		seq_म_लिखो(m, "EP Ctrl Reg [0x%x]: = [0x%x]\n", i, पंचांगp_reg);
	पूर्ण
	पंचांगp_reg = fsl_पढ़ोl(&dr_regs->endpoपूर्णांकprime);
	seq_म_लिखो(m, "EP Prime Reg = [0x%x]\n\n", पंचांगp_reg);

#अगर_अघोषित CONFIG_ARCH_MXC
	अगर (udc->pdata->have_sysअगर_regs) अणु
		पंचांगp_reg = usb_sys_regs->snoop1;
		seq_म_लिखो(m, "Snoop1 Reg : = [0x%x]\n\n", पंचांगp_reg);

		पंचांगp_reg = usb_sys_regs->control;
		seq_म_लिखो(m, "General Control Reg : = [0x%x]\n\n", पंचांगp_reg);
	पूर्ण
#पूर्ण_अगर

	/* ------fsl_udc, fsl_ep, fsl_request काष्ठाure inक्रमmation ----- */
	ep = &udc->eps[0];
	seq_म_लिखो(m, "For %s Maxpkt is 0x%x index is 0x%x\n",
			ep->ep.name, ep_maxpacket(ep), ep_index(ep));

	अगर (list_empty(&ep->queue)) अणु
		seq_माला_दो(m, "its req queue is empty\n\n");
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(req, &ep->queue, queue) अणु
			seq_म_लिखो(m,
				"req %p actual 0x%x length 0x%x buf %p\n",
				&req->req, req->req.actual,
				req->req.length, req->req.buf);
		पूर्ण
	पूर्ण
	/* other gadget->eplist ep */
	list_क्रम_each_entry(ep, &udc->gadget.ep_list, ep.ep_list) अणु
		अगर (ep->ep.desc) अणु
			seq_म_लिखो(m,
					"\nFor %s Maxpkt is 0x%x "
					"index is 0x%x\n",
					ep->ep.name, ep_maxpacket(ep),
					ep_index(ep));

			अगर (list_empty(&ep->queue)) अणु
				seq_माला_दो(m, "its req queue is empty\n\n");
			पूर्ण अन्यथा अणु
				list_क्रम_each_entry(req, &ep->queue, queue) अणु
					seq_म_लिखो(m,
						"req %p actual 0x%x length "
						"0x%x  buf %p\n",
						&req->req, req->req.actual,
						req->req.length, req->req.buf);
				पूर्ण	/* end क्रम each_entry of ep req */
			पूर्ण	/* end क्रम अन्यथा */
		पूर्ण	/* end क्रम अगर(ep->queue) */
	पूर्ण	/* end (ep->desc) */

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

#घोषणा create_proc_file() \
	proc_create_single(proc_filename, 0, शून्य, fsl_proc_पढ़ो)
#घोषणा हटाओ_proc_file()	हटाओ_proc_entry(proc_filename, शून्य)

#अन्यथा				/* !CONFIG_USB_GADGET_DEBUG_खाताS */

#घोषणा create_proc_file()	करो अणुपूर्ण जबतक (0)
#घोषणा हटाओ_proc_file()	करो अणुपूर्ण जबतक (0)

#पूर्ण_अगर				/* CONFIG_USB_GADGET_DEBUG_खाताS */

/*-------------------------------------------------------------------------*/

/* Release udc काष्ठाures */
अटल व्योम fsl_udc_release(काष्ठा device *dev)
अणु
	complete(udc_controller->करोne);
	dma_मुक्त_coherent(dev->parent, udc_controller->ep_qh_size,
			udc_controller->ep_qh, udc_controller->ep_qh_dma);
	kमुक्त(udc_controller);
पूर्ण

/******************************************************************
	Internal काष्ठाure setup functions
*******************************************************************/
/*------------------------------------------------------------------
 * init resource क्रम global controller called by fsl_udc_probe()
 * On success the udc handle is initialized, on failure it is
 * unchanged (reset).
 * Return 0 on success and -1 on allocation failure
 ------------------------------------------------------------------*/
अटल पूर्णांक काष्ठा_udc_setup(काष्ठा fsl_udc *udc,
		काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_usb2_platक्रमm_data *pdata;
	माप_प्रकार size;

	pdata = dev_get_platdata(&pdev->dev);
	udc->phy_mode = pdata->phy_mode;

	udc->eps = kसुस्मृति(udc->max_ep, माप(काष्ठा fsl_ep), GFP_KERNEL);
	अगर (!udc->eps) अणु
		ERR("kmalloc udc endpoint status failed\n");
		जाओ eps_alloc_failed;
	पूर्ण

	/* initialized QHs, take care of alignment */
	size = udc->max_ep * माप(काष्ठा ep_queue_head);
	अगर (size < QH_ALIGNMENT)
		size = QH_ALIGNMENT;
	अन्यथा अगर ((size % QH_ALIGNMENT) != 0) अणु
		size += QH_ALIGNMENT + 1;
		size &= ~(QH_ALIGNMENT - 1);
	पूर्ण
	udc->ep_qh = dma_alloc_coherent(&pdev->dev, size,
					&udc->ep_qh_dma, GFP_KERNEL);
	अगर (!udc->ep_qh) अणु
		ERR("malloc QHs for udc failed\n");
		जाओ ep_queue_alloc_failed;
	पूर्ण

	udc->ep_qh_size = size;

	/* Initialize ep0 status request काष्ठाure */
	/* FIXME: fsl_alloc_request() ignores ep argument */
	udc->status_req = container_of(fsl_alloc_request(शून्य, GFP_KERNEL),
			काष्ठा fsl_req, req);
	अगर (!udc->status_req) अणु
		ERR("kzalloc for udc status request failed\n");
		जाओ udc_status_alloc_failed;
	पूर्ण

	/* allocate a small amount of memory to get valid address */
	udc->status_req->req.buf = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!udc->status_req->req.buf) अणु
		ERR("kzalloc for udc request buffer failed\n");
		जाओ udc_req_buf_alloc_failed;
	पूर्ण

	udc->resume_state = USB_STATE_NOTATTACHED;
	udc->usb_state = USB_STATE_POWERED;
	udc->ep0_dir = 0;
	udc->remote_wakeup = 0;	/* शेष to 0 on reset */

	वापस 0;

udc_req_buf_alloc_failed:
	kमुक्त(udc->status_req);
udc_status_alloc_failed:
	kमुक्त(udc->ep_qh);
	udc->ep_qh_size = 0;
ep_queue_alloc_failed:
	kमुक्त(udc->eps);
eps_alloc_failed:
	udc->phy_mode = 0;
	वापस -1;

पूर्ण

/*----------------------------------------------------------------
 * Setup the fsl_ep काष्ठा क्रम eps
 * Link fsl_ep->ep to gadget->ep_list
 * ep0out is not used so करो nothing here
 * ep0in should be taken care
 *--------------------------------------------------------------*/
अटल पूर्णांक काष्ठा_ep_setup(काष्ठा fsl_udc *udc, अचिन्हित अक्षर index,
		अक्षर *name, पूर्णांक link)
अणु
	काष्ठा fsl_ep *ep = &udc->eps[index];

	ep->udc = udc;
	म_नकल(ep->name, name);
	ep->ep.name = ep->name;

	ep->ep.ops = &fsl_ep_ops;
	ep->stopped = 0;

	अगर (index == 0) अणु
		ep->ep.caps.type_control = true;
	पूर्ण अन्यथा अणु
		ep->ep.caps.type_iso = true;
		ep->ep.caps.type_bulk = true;
		ep->ep.caps.type_पूर्णांक = true;
	पूर्ण

	अगर (index & 1)
		ep->ep.caps.dir_in = true;
	अन्यथा
		ep->ep.caps.dir_out = true;

	/* क्रम ep0: maxP defined in desc
	 * क्रम other eps, maxP is set by epस्वतःconfig() called by gadget layer
	 */
	usb_ep_set_maxpacket_limit(&ep->ep, (अचिन्हित लघु) ~0);

	/* the queue lists any req क्रम this ep */
	INIT_LIST_HEAD(&ep->queue);

	/* gagdet.ep_list used क्रम ep_स्वतःconfig so no ep0 */
	अगर (link)
		list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);
	ep->gadget = &udc->gadget;
	ep->qh = &udc->ep_qh[index];

	वापस 0;
पूर्ण

/* Driver probe function
 * all initialization operations implemented here except enabling usb_पूर्णांकr reg
 * board setup should have been करोne in the platक्रमm code
 */
अटल पूर्णांक fsl_udc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_usb2_platक्रमm_data *pdata;
	काष्ठा resource *res;
	पूर्णांक ret = -ENODEV;
	अचिन्हित पूर्णांक i;
	u32 dccparams;

	udc_controller = kzalloc(माप(काष्ठा fsl_udc), GFP_KERNEL);
	अगर (udc_controller == शून्य)
		वापस -ENOMEM;

	pdata = dev_get_platdata(&pdev->dev);
	udc_controller->pdata = pdata;
	spin_lock_init(&udc_controller->lock);
	udc_controller->stopped = 1;

#अगर_घोषित CONFIG_USB_OTG
	अगर (pdata->operating_mode == FSL_USB2_DR_OTG) अणु
		udc_controller->transceiver = usb_get_phy(USB_PHY_TYPE_USB2);
		अगर (IS_ERR_OR_शून्य(udc_controller->transceiver)) अणु
			ERR("Can't find OTG driver!\n");
			ret = -ENODEV;
			जाओ err_kमुक्त;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -ENXIO;
		जाओ err_kमुक्त;
	पूर्ण

	अगर (pdata->operating_mode == FSL_USB2_DR_DEVICE) अणु
		अगर (!request_mem_region(res->start, resource_size(res),
					driver_name)) अणु
			ERR("request mem region for %s failed\n", pdev->name);
			ret = -EBUSY;
			जाओ err_kमुक्त;
		पूर्ण
	पूर्ण

	dr_regs = ioremap(res->start, resource_size(res));
	अगर (!dr_regs) अणु
		ret = -ENOMEM;
		जाओ err_release_mem_region;
	पूर्ण

	pdata->regs = (व्योम __iomem *)dr_regs;

	/*
	 * करो platक्रमm specअगरic init: check the घड़ी, grab/config pins, etc.
	 */
	अगर (pdata->init && pdata->init(pdev)) अणु
		ret = -ENODEV;
		जाओ err_iounmap_noclk;
	पूर्ण

	/* Set accessors only after pdata->init() ! */
	fsl_set_accessors(pdata);

#अगर_अघोषित CONFIG_ARCH_MXC
	अगर (pdata->have_sysअगर_regs)
		usb_sys_regs = (व्योम *)dr_regs + USB_DR_SYS_OFFSET;
#पूर्ण_अगर

	/* Initialize USB घड़ीs */
	ret = fsl_udc_clk_init(pdev);
	अगर (ret < 0)
		जाओ err_iounmap_noclk;

	/* Read Device Controller Capability Parameters रेजिस्टर */
	dccparams = fsl_पढ़ोl(&dr_regs->dccparams);
	अगर (!(dccparams & DCCPARAMS_DC)) अणु
		ERR("This SOC doesn't support device role\n");
		ret = -ENODEV;
		जाओ err_iounmap;
	पूर्ण
	/* Get max device endpoपूर्णांकs */
	/* DEN is bidirectional ep number, max_ep द्विगुनs the number */
	udc_controller->max_ep = (dccparams & DCCPARAMS_DEN_MASK) * 2;

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret <= 0) अणु
		ret = ret ? : -ENODEV;
		जाओ err_iounmap;
	पूर्ण
	udc_controller->irq = ret;

	ret = request_irq(udc_controller->irq, fsl_udc_irq, IRQF_SHARED,
			driver_name, udc_controller);
	अगर (ret != 0) अणु
		ERR("cannot request irq %d err %d\n",
				udc_controller->irq, ret);
		जाओ err_iounmap;
	पूर्ण

	/* Initialize the udc काष्ठाure including QH member and other member */
	अगर (काष्ठा_udc_setup(udc_controller, pdev)) अणु
		ERR("Can't initialize udc data structure\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_irq;
	पूर्ण

	अगर (IS_ERR_OR_शून्य(udc_controller->transceiver)) अणु
		/* initialize usb hw reg except क्रम regs क्रम EP,
		 * leave usbपूर्णांकr reg untouched */
		dr_controller_setup(udc_controller);
	पूर्ण

	ret = fsl_udc_clk_finalize(pdev);
	अगर (ret)
		जाओ err_मुक्त_irq;

	/* Setup gadget काष्ठाure */
	udc_controller->gadget.ops = &fsl_gadget_ops;
	udc_controller->gadget.max_speed = USB_SPEED_HIGH;
	udc_controller->gadget.ep0 = &udc_controller->eps[0].ep;
	INIT_LIST_HEAD(&udc_controller->gadget.ep_list);
	udc_controller->gadget.speed = USB_SPEED_UNKNOWN;
	udc_controller->gadget.name = driver_name;

	/* Setup gadget.dev and रेजिस्टर with kernel */
	dev_set_name(&udc_controller->gadget.dev, "gadget");
	udc_controller->gadget.dev.of_node = pdev->dev.of_node;

	अगर (!IS_ERR_OR_शून्य(udc_controller->transceiver))
		udc_controller->gadget.is_otg = 1;

	/* setup QH and epctrl क्रम ep0 */
	ep0_setup(udc_controller);

	/* setup udc->eps[] क्रम ep0 */
	काष्ठा_ep_setup(udc_controller, 0, "ep0", 0);
	/* क्रम ep0: the desc defined here;
	 * क्रम other eps, gadget layer called ep_enable with defined desc
	 */
	udc_controller->eps[0].ep.desc = &fsl_ep0_desc;
	usb_ep_set_maxpacket_limit(&udc_controller->eps[0].ep,
				   USB_MAX_CTRL_PAYLOAD);

	/* setup the udc->eps[] क्रम non-control endpoपूर्णांकs and link
	 * to gadget.ep_list */
	क्रम (i = 1; i < (पूर्णांक)(udc_controller->max_ep / 2); i++) अणु
		अक्षर name[14];

		प्र_लिखो(name, "ep%dout", i);
		काष्ठा_ep_setup(udc_controller, i * 2, name, 1);
		प्र_लिखो(name, "ep%din", i);
		काष्ठा_ep_setup(udc_controller, i * 2 + 1, name, 1);
	पूर्ण

	/* use dma_pool क्रम TD management */
	udc_controller->td_pool = dma_pool_create("udc_td", &pdev->dev,
			माप(काष्ठा ep_td_काष्ठा),
			DTD_ALIGNMENT, UDC_DMA_BOUNDARY);
	अगर (udc_controller->td_pool == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_irq;
	पूर्ण

	ret = usb_add_gadget_udc_release(&pdev->dev, &udc_controller->gadget,
			fsl_udc_release);
	अगर (ret)
		जाओ err_del_udc;

	create_proc_file();
	वापस 0;

err_del_udc:
	dma_pool_destroy(udc_controller->td_pool);
err_मुक्त_irq:
	मुक्त_irq(udc_controller->irq, udc_controller);
err_iounmap:
	अगर (pdata->निकास)
		pdata->निकास(pdev);
	fsl_udc_clk_release();
err_iounmap_noclk:
	iounmap(dr_regs);
err_release_mem_region:
	अगर (pdata->operating_mode == FSL_USB2_DR_DEVICE)
		release_mem_region(res->start, resource_size(res));
err_kमुक्त:
	kमुक्त(udc_controller);
	udc_controller = शून्य;
	वापस ret;
पूर्ण

/* Driver removal function
 * Free resources and finish pending transactions
 */
अटल पूर्णांक fsl_udc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	काष्ठा fsl_usb2_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);

	DECLARE_COMPLETION_ONSTACK(करोne);

	अगर (!udc_controller)
		वापस -ENODEV;

	udc_controller->करोne = &करोne;
	usb_del_gadget_udc(&udc_controller->gadget);

	fsl_udc_clk_release();

	/* DR has been stopped in usb_gadget_unरेजिस्टर_driver() */
	हटाओ_proc_file();

	/* Free allocated memory */
	kमुक्त(udc_controller->status_req->req.buf);
	kमुक्त(udc_controller->status_req);
	kमुक्त(udc_controller->eps);

	dma_pool_destroy(udc_controller->td_pool);
	मुक्त_irq(udc_controller->irq, udc_controller);
	iounmap(dr_regs);
	अगर (res && (pdata->operating_mode == FSL_USB2_DR_DEVICE))
		release_mem_region(res->start, resource_size(res));

	/* मुक्त udc --रुको क्रम the release() finished */
	रुको_क्रम_completion(&करोne);

	/*
	 * करो platक्रमm specअगरic un-initialization:
	 * release iomux pins, etc.
	 */
	अगर (pdata->निकास)
		pdata->निकास(pdev);

	वापस 0;
पूर्ण

/*-----------------------------------------------------------------
 * Modअगरy Power management attributes
 * Used by OTG statemachine to disable gadget temporarily
 -----------------------------------------------------------------*/
अटल पूर्णांक fsl_udc_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	dr_controller_stop(udc_controller);
	वापस 0;
पूर्ण

/*-----------------------------------------------------------------
 * Invoked on USB resume. May be called in_पूर्णांकerrupt.
 * Here we start the DR controller and enable the irq
 *-----------------------------------------------------------------*/
अटल पूर्णांक fsl_udc_resume(काष्ठा platक्रमm_device *pdev)
अणु
	/* Enable DR irq reg and set controller Run */
	अगर (udc_controller->stopped) अणु
		dr_controller_setup(udc_controller);
		dr_controller_run(udc_controller);
	पूर्ण
	udc_controller->usb_state = USB_STATE_ATTACHED;
	udc_controller->ep0_state = WAIT_FOR_SETUP;
	udc_controller->ep0_dir = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_udc_otg_suspend(काष्ठा device *dev, pm_message_t state)
अणु
	काष्ठा fsl_udc *udc = udc_controller;
	u32 mode, usbcmd;

	mode = fsl_पढ़ोl(&dr_regs->usbmode) & USB_MODE_CTRL_MODE_MASK;

	pr_debug("%s(): mode 0x%x stopped %d\n", __func__, mode, udc->stopped);

	/*
	 * If the controller is alपढ़ोy stopped, then this must be a
	 * PM suspend.  Remember this fact, so that we will leave the
	 * controller stopped at PM resume समय.
	 */
	अगर (udc->stopped) अणु
		pr_debug("gadget already stopped, leaving early\n");
		udc->alपढ़ोy_stopped = 1;
		वापस 0;
	पूर्ण

	अगर (mode != USB_MODE_CTRL_MODE_DEVICE) अणु
		pr_debug("gadget not in device mode, leaving early\n");
		वापस 0;
	पूर्ण

	/* stop the controller */
	usbcmd = fsl_पढ़ोl(&dr_regs->usbcmd) & ~USB_CMD_RUN_STOP;
	fsl_ग_लिखोl(usbcmd, &dr_regs->usbcmd);

	udc->stopped = 1;

	pr_info("USB Gadget suspended\n");

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_udc_otg_resume(काष्ठा device *dev)
अणु
	pr_debug("%s(): stopped %d  already_stopped %d\n", __func__,
		 udc_controller->stopped, udc_controller->alपढ़ोy_stopped);

	/*
	 * If the controller was stopped at suspend समय, then
	 * करोn't resume it now.
	 */
	अगर (udc_controller->alपढ़ोy_stopped) अणु
		udc_controller->alपढ़ोy_stopped = 0;
		pr_debug("gadget was already stopped, leaving early\n");
		वापस 0;
	पूर्ण

	pr_info("USB Gadget resume\n");

	वापस fsl_udc_resume(शून्य);
पूर्ण
/*-------------------------------------------------------------------------
	Register entry poपूर्णांक क्रम the peripheral controller driver
--------------------------------------------------------------------------*/
अटल स्थिर काष्ठा platक्रमm_device_id fsl_udc_devtype[] = अणु
	अणु
		.name = "imx-udc-mx27",
	पूर्ण, अणु
		.name = "imx-udc-mx51",
	पूर्ण, अणु
		.name = "fsl-usb2-udc",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, fsl_udc_devtype);
अटल काष्ठा platक्रमm_driver udc_driver = अणु
	.हटाओ		= fsl_udc_हटाओ,
	/* Just क्रम FSL i.mx SoC currently */
	.id_table	= fsl_udc_devtype,
	/* these suspend and resume are not usb suspend and resume */
	.suspend	= fsl_udc_suspend,
	.resume		= fsl_udc_resume,
	.driver		= अणु
			.name = driver_name,
			/* udc suspend/resume called from OTG driver */
			.suspend = fsl_udc_otg_suspend,
			.resume  = fsl_udc_otg_resume,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(udc_driver, fsl_udc_probe);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:fsl-usb2-udc");
