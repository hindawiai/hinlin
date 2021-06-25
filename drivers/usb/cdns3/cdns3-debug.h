<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Cadence USBSS DRD Driver.
 * Debug header file.
 *
 * Copyright (C) 2018-2019 Cadence.
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 */
#अगर_अघोषित __LINUX_CDNS3_DEBUG
#घोषणा __LINUX_CDNS3_DEBUG

#समावेश "core.h"

अटल अंतरभूत अक्षर *cdns3_decode_usb_irq(अक्षर *str,
					 क्रमागत usb_device_speed speed,
					 u32 usb_ists)
अणु
	पूर्णांक ret;

	ret = प्र_लिखो(str, "IRQ %08x = ", usb_ists);

	अगर (usb_ists & (USB_ISTS_CON2I | USB_ISTS_CONI)) अणु
		ret += प्र_लिखो(str + ret, "Connection %s\n",
			       usb_speed_string(speed));
	पूर्ण
	अगर (usb_ists & USB_ISTS_DIS2I || usb_ists & USB_ISTS_DISI)
		ret += प्र_लिखो(str + ret, "Disconnection ");
	अगर (usb_ists & USB_ISTS_L2ENTI)
		ret += प्र_लिखो(str + ret, "suspended ");
	अगर (usb_ists & USB_ISTS_L1ENTI)
		ret += प्र_लिखो(str + ret, "L1 enter ");
	अगर (usb_ists & USB_ISTS_L1EXTI)
		ret += प्र_लिखो(str + ret, "L1 exit ");
	अगर (usb_ists & USB_ISTS_L2ENTI)
		ret += प्र_लिखो(str + ret, "L2 enter ");
	अगर (usb_ists & USB_ISTS_L2EXTI)
		ret += प्र_लिखो(str + ret, "L2 exit ");
	अगर (usb_ists & USB_ISTS_U3EXTI)
		ret += प्र_लिखो(str + ret, "U3 exit ");
	अगर (usb_ists & USB_ISTS_UWRESI)
		ret += प्र_लिखो(str + ret, "Warm Reset ");
	अगर (usb_ists & USB_ISTS_UHRESI)
		ret += प्र_लिखो(str + ret, "Hot Reset ");
	अगर (usb_ists & USB_ISTS_U2RESI)
		ret += प्र_लिखो(str + ret, "Reset");

	वापस str;
पूर्ण

अटल अंतरभूत  अक्षर *cdns3_decode_ep_irq(अक्षर *str,
					 u32 ep_sts,
					 स्थिर अक्षर *ep_name)
अणु
	पूर्णांक ret;

	ret = प्र_लिखो(str, "IRQ for %s: %08x ", ep_name, ep_sts);

	अगर (ep_sts & EP_STS_SETUP)
		ret += प्र_लिखो(str + ret, "SETUP ");
	अगर (ep_sts & EP_STS_IOC)
		ret += प्र_लिखो(str + ret, "IOC ");
	अगर (ep_sts & EP_STS_ISP)
		ret += प्र_लिखो(str + ret, "ISP ");
	अगर (ep_sts & EP_STS_DESCMIS)
		ret += प्र_लिखो(str + ret, "DESCMIS ");
	अगर (ep_sts & EP_STS_STREAMR)
		ret += प्र_लिखो(str + ret, "STREAMR ");
	अगर (ep_sts & EP_STS_MD_EXIT)
		ret += प्र_लिखो(str + ret, "MD_EXIT ");
	अगर (ep_sts & EP_STS_TRBERR)
		ret += प्र_लिखो(str + ret, "TRBERR ");
	अगर (ep_sts & EP_STS_NRDY)
		ret += प्र_लिखो(str + ret, "NRDY ");
	अगर (ep_sts & EP_STS_PRIME)
		ret += प्र_लिखो(str + ret, "PRIME ");
	अगर (ep_sts & EP_STS_SIDERR)
		ret += प्र_लिखो(str + ret, "SIDERRT ");
	अगर (ep_sts & EP_STS_OUTSMM)
		ret += प्र_लिखो(str + ret, "OUTSMM ");
	अगर (ep_sts & EP_STS_ISOERR)
		ret += प्र_लिखो(str + ret, "ISOERR ");
	अगर (ep_sts & EP_STS_IOT)
		ret += प्र_लिखो(str + ret, "IOT ");

	वापस str;
पूर्ण

अटल अंतरभूत अक्षर *cdns3_decode_epx_irq(अक्षर *str,
					 अक्षर *ep_name,
					 u32 ep_sts)
अणु
	वापस cdns3_decode_ep_irq(str, ep_sts, ep_name);
पूर्ण

अटल अंतरभूत अक्षर *cdns3_decode_ep0_irq(अक्षर *str,
					 पूर्णांक dir,
					 u32 ep_sts)
अणु
	वापस cdns3_decode_ep_irq(str, ep_sts,
				   dir ? "ep0IN" : "ep0OUT");
पूर्ण

/**
 * Debug a transfer ring.
 *
 * Prपूर्णांकs out all TRBs in the endpoपूर्णांक ring, even those after the Link TRB.
 *.
 */
अटल अंतरभूत अक्षर *cdns3_dbg_ring(काष्ठा cdns3_endpoपूर्णांक *priv_ep,
				   काष्ठा cdns3_trb *ring, अक्षर *str)
अणु
	dma_addr_t addr = priv_ep->trb_pool_dma;
	काष्ठा cdns3_trb *trb;
	पूर्णांक trb_per_sector;
	पूर्णांक ret = 0;
	पूर्णांक i;

	trb_per_sector = GET_TRBS_PER_SEGMENT(priv_ep->type);

	trb = &priv_ep->trb_pool[priv_ep->dequeue];
	ret += प्र_लिखो(str + ret, "\n\t\tRing contents for %s:", priv_ep->name);

	ret += प्र_लिखो(str + ret,
		       "\n\t\tRing deq index: %d, trb: %p (virt), 0x%llx (dma)\n",
		       priv_ep->dequeue, trb,
		       (अचिन्हित दीर्घ दीर्घ)cdns3_trb_virt_to_dma(priv_ep, trb));

	trb = &priv_ep->trb_pool[priv_ep->enqueue];
	ret += प्र_लिखो(str + ret,
		       "\t\tRing enq index: %d, trb: %p (virt), 0x%llx (dma)\n",
		       priv_ep->enqueue, trb,
		       (अचिन्हित दीर्घ दीर्घ)cdns3_trb_virt_to_dma(priv_ep, trb));

	ret += प्र_लिखो(str + ret,
		       "\t\tfree trbs: %d, CCS=%d, PCS=%d\n",
		       priv_ep->मुक्त_trbs, priv_ep->ccs, priv_ep->pcs);

	अगर (trb_per_sector > TRBS_PER_SEGMENT)
		trb_per_sector = TRBS_PER_SEGMENT;

	अगर (trb_per_sector > TRBS_PER_SEGMENT) अणु
		प्र_लिखो(str + ret, "\t\tTransfer ring %d too big\n",
			trb_per_sector);
		वापस str;
	पूर्ण

	क्रम (i = 0; i < trb_per_sector; ++i) अणु
		trb = &ring[i];
		ret += प्र_लिखो(str + ret,
			"\t\t@%pad %08x %08x %08x\n", &addr,
			le32_to_cpu(trb->buffer),
			le32_to_cpu(trb->length),
			le32_to_cpu(trb->control));
		addr += माप(*trb);
	पूर्ण

	वापस str;
पूर्ण

#पूर्ण_अगर /*__LINUX_CDNS3_DEBUG*/
