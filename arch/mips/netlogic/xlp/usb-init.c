<शैली गुरु>
/*
 * Copyright (c) 2003-2012 Broadcom Corporation
 * All Rights Reserved
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the Broadcom
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY BROADCOM ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL BROADCOM OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/xlp-hal/iomap.h>
#समावेश <यंत्र/netlogic/xlp-hal/xlp.h>

/*
 * USB glue logic रेजिस्टरs, used only during initialization
 */
#घोषणा USB_CTL_0			0x01
#घोषणा USB_PHY_0			0x0A
#घोषणा USB_PHY_RESET			0x01
#घोषणा USB_PHY_PORT_RESET_0		0x10
#घोषणा USB_PHY_PORT_RESET_1		0x20
#घोषणा USB_CONTROLLER_RESET		0x01
#घोषणा USB_INT_STATUS			0x0E
#घोषणा USB_INT_EN			0x0F
#घोषणा USB_PHY_INTERRUPT_EN		0x01
#घोषणा USB_OHCI_INTERRUPT_EN		0x02
#घोषणा USB_OHCI_INTERRUPT1_EN		0x04
#घोषणा USB_OHCI_INTERRUPT2_EN		0x08
#घोषणा USB_CTRL_INTERRUPT_EN		0x10

#घोषणा nlm_पढ़ो_usb_reg(b, r)			nlm_पढ़ो_reg(b, r)
#घोषणा nlm_ग_लिखो_usb_reg(b, r, v)		nlm_ग_लिखो_reg(b, r, v)
#घोषणा nlm_get_usb_pcibase(node, inst)		\
	nlm_pcicfg_base(XLP_IO_USB_OFFSET(node, inst))
#घोषणा nlm_get_usb_regbase(node, inst)		\
	(nlm_get_usb_pcibase(node, inst) + XLP_IO_PCI_HDRSZ)

अटल व्योम nlm_usb_पूर्णांकr_en(पूर्णांक node, पूर्णांक port)
अणु
	uपूर्णांक32_t val;
	uपूर्णांक64_t port_addr;

	port_addr = nlm_get_usb_regbase(node, port);
	val = nlm_पढ़ो_usb_reg(port_addr, USB_INT_EN);
	val = USB_CTRL_INTERRUPT_EN  | USB_OHCI_INTERRUPT_EN |
		USB_OHCI_INTERRUPT1_EN | USB_OHCI_INTERRUPT2_EN;
	nlm_ग_लिखो_usb_reg(port_addr, USB_INT_EN, val);
पूर्ण

अटल व्योम nlm_usb_hw_reset(पूर्णांक node, पूर्णांक port)
अणु
	uपूर्णांक64_t port_addr;
	uपूर्णांक32_t val;

	/* reset USB phy */
	port_addr = nlm_get_usb_regbase(node, port);
	val = nlm_पढ़ो_usb_reg(port_addr, USB_PHY_0);
	val &= ~(USB_PHY_RESET | USB_PHY_PORT_RESET_0 | USB_PHY_PORT_RESET_1);
	nlm_ग_लिखो_usb_reg(port_addr, USB_PHY_0, val);

	mdelay(100);
	val = nlm_पढ़ो_usb_reg(port_addr, USB_CTL_0);
	val &= ~(USB_CONTROLLER_RESET);
	val |= 0x4;
	nlm_ग_लिखो_usb_reg(port_addr, USB_CTL_0, val);
पूर्ण

अटल पूर्णांक __init nlm_platक्रमm_usb_init(व्योम)
अणु
	अगर (cpu_is_xlpii())
		वापस 0;

	pr_info("Initializing USB Interface\n");
	nlm_usb_hw_reset(0, 0);
	nlm_usb_hw_reset(0, 3);

	/* Enable PHY पूर्णांकerrupts */
	nlm_usb_पूर्णांकr_en(0, 0);
	nlm_usb_पूर्णांकr_en(0, 3);

	वापस 0;
पूर्ण

arch_initcall(nlm_platक्रमm_usb_init);

अटल u64 xlp_usb_dmamask = ~(u32)0;

/* Fixup the IRQ क्रम USB devices which is exist on XLP SOC PCIE bus */
अटल व्योम nlm_usb_fixup_final(काष्ठा pci_dev *dev)
अणु
	dev->dev.dma_mask		= &xlp_usb_dmamask;
	dev->dev.coherent_dma_mask	= DMA_BIT_MASK(32);
	चयन (dev->devfn) अणु
	हाल 0x10:
		dev->irq = PIC_EHCI_0_IRQ;
		अवरोध;
	हाल 0x11:
		dev->irq = PIC_OHCI_0_IRQ;
		अवरोध;
	हाल 0x12:
		dev->irq = PIC_OHCI_1_IRQ;
		अवरोध;
	हाल 0x13:
		dev->irq = PIC_EHCI_1_IRQ;
		अवरोध;
	हाल 0x14:
		dev->irq = PIC_OHCI_2_IRQ;
		अवरोध;
	हाल 0x15:
		dev->irq = PIC_OHCI_3_IRQ;
		अवरोध;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_NETLOGIC, PCI_DEVICE_ID_NLM_EHCI,
		nlm_usb_fixup_final);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_NETLOGIC, PCI_DEVICE_ID_NLM_OHCI,
		nlm_usb_fixup_final);
